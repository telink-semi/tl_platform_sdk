/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */


 // for faking dcd_event_xfer_complete

#include "msc_device.h"
#include "../../common/tusb_verify.h"
#include "../../device/dcd.h"
#include "../../device/usbd_pvt.h"
//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
enum
{
  MSC_STAGE_CMD  = 0,
  MSC_STAGE_DATA,
  MSC_STAGE_STATUS,
  MSC_STAGE_STATUS_SENT
};

typedef struct
{
  // TODO optimize alignment
  msc_cbw_t cbw;
  msc_csw_t csw;

  unsigned char  itf_num;
  unsigned char  ep_in;
  unsigned char  ep_out;

  // Bulk Only Transfer (BOT) Protocol
  unsigned char  stage;
  unsigned int total_len;
  unsigned int xferred_len; // numbered of bytes transferred so far in the Data Stage

  // Sense Response Data
  unsigned char sense_key;
  unsigned char add_sense_code;
  unsigned char add_sense_qualifier;
}mscd_interface_t;

static mscd_interface_t _mscd_itf;
__attribute__((aligned(4)))  unsigned char _mscd_buf[CFG_TUD_MSC_EP_BUFSIZE];

//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+
static int proc_builtin_scsi(unsigned char lun, unsigned char const scsi_cmd[16], unsigned char* buffer, unsigned int bufsize);
static void proc_read10_cmd(unsigned char rhport, mscd_interface_t* p_msc);
static void proc_write10_cmd(unsigned char rhport, mscd_interface_t* p_msc);

static inline unsigned int rdwr10_get_lba(unsigned char const command[])
{
  // use offsetof to avoid pointer to the odd/unaligned address
  unsigned int const lba = tu_unaligned_read32(command + offsetof(scsi_write10_t, lba));

  // lba is in Big Endian
  return tu_ntohl(lba);
}

static inline unsigned short rdwr10_get_blockcount(unsigned char const command[])
{
  // use offsetof to avoid pointer to the odd/misaligned address
  unsigned short const block_count = tu_unaligned_read16(command + offsetof(scsi_write10_t, block_count));

  // block count is in Big Endian
  return tu_ntohs(block_count);
}


//--------------------------------------------------------------------+
// APPLICATION API
//--------------------------------------------------------------------+
bool tud_msc_set_sense(unsigned char lun, unsigned char sense_key, unsigned char add_sense_code, unsigned char add_sense_qualifier)
{
  (void) lun;

  _mscd_itf.sense_key           = sense_key;
  _mscd_itf.add_sense_code      = add_sense_code;
  _mscd_itf.add_sense_qualifier = add_sense_qualifier;

  return true;
}

//--------------------------------------------------------------------+
// USBD Driver API
//--------------------------------------------------------------------+
void mscd_init(void)
{
  tu_memclr(&_mscd_itf, sizeof(mscd_interface_t));
}

void mscd_reset(unsigned char rhport)
{
  (void) rhport;
  tu_memclr(&_mscd_itf, sizeof(mscd_interface_t));
}

unsigned short mscd_open(unsigned char rhport, tusb_desc_interface_t const * itf_desc, unsigned short max_len)
{
    (void) max_len;
  // only support SCSI's BOT protocol
  // msc driver length is fixed
  unsigned short const drv_len = sizeof(tusb_desc_interface_t) + 2*sizeof(tusb_desc_endpoint_t);

  // Max length mus be at least 1 interface + 2 endpoints
  mscd_interface_t * p_msc = &_mscd_itf;
  p_msc->itf_num = itf_desc->bInterfaceNumber;

  // Open endpoint pair
  usbd_open_edpt_pair(rhport, tu_desc_next(itf_desc), 2, TUSB_XFER_BULK, &p_msc->ep_out, &p_msc->ep_in);

  // Prepare for Command Block Wrapper
  if ( !usbd_edpt_xfer(rhport, p_msc->ep_out, (unsigned char*) &p_msc->cbw, sizeof(msc_cbw_t)) )
  {
    while(1);
  }

  return drv_len;
}

bool mscd_xfer_cb(unsigned char rhport, unsigned char ep_addr, xfer_result_t event, unsigned int xferred_bytes)
{
    (void)event;
  mscd_interface_t* p_msc = &_mscd_itf;
  msc_cbw_t const * p_cbw = &p_msc->cbw;
  msc_csw_t       * p_csw = &p_msc->csw;

  switch (p_msc->stage)
  {
    case MSC_STAGE_CMD:
      //------------- new CBW received -------------//
      // Complete IN while waiting for CMD is usually Status of previous SCSI op, ignore it
      if(ep_addr != p_msc->ep_out) return true;

      p_csw->signature    = MSC_CSW_SIGNATURE;
      p_csw->tag          = p_cbw->tag;
      p_csw->data_residue = 0;

      /*------------- Parse command and prepare DATA -------------*/
      p_msc->stage = MSC_STAGE_DATA;
      p_msc->total_len = p_cbw->total_bytes;
      p_msc->xferred_len = 0;

      if (SCSI_CMD_READ_10 == p_cbw->command[0])
      {
         /* if ( tud_msc_read10_start_cb )*/ tud_msc_read10_start_cb(p_cbw->lun, rdwr10_get_lba(p_cbw->command), p_cbw->total_bytes);
          proc_read10_cmd(rhport, p_msc);
      }
      else if (SCSI_CMD_WRITE_10 == p_cbw->command[0])
      {
          /*if ( tud_msc_write10_start_cb )*/ tud_msc_write10_start_cb(p_cbw->lun, rdwr10_get_lba(p_cbw->command), p_cbw->total_bytes);
          proc_write10_cmd(rhport, p_msc);
      }
      else
      {
        // For other SCSI commands
        // 1. OUT : queue transfer (invoke app callback after done)
        // 2. IN & Zero: Process if is built-in, else Invoke app callback. Skip DATA if zero length
        if ( (p_cbw->total_bytes > 0 ) && !tu_bit_test(p_cbw->dir, 7) )
        {
          // queue transfer
          usbd_edpt_xfer(rhport, p_msc->ep_out, _mscd_buf, p_msc->total_len);
        }else
        {
          int resplen;

          // First process if it is a built-in commands
          resplen = proc_builtin_scsi(p_cbw->lun, p_cbw->command, _mscd_buf, sizeof(_mscd_buf));

          // Not built-in, invoke user callback
          if ( (resplen < 0) && (p_msc->sense_key == 0) )
          {
            resplen = tud_msc_scsi_cb(p_cbw->lun, p_cbw->command, _mscd_buf, p_msc->total_len);
          }

          if ( resplen < 0 )
          {
            p_msc->total_len = 0;
            p_csw->status = MSC_CSW_STATUS_FAILED;
            p_msc->stage = MSC_STAGE_STATUS;

            // failed but senskey is not set: default to Illegal Request
            if ( p_msc->sense_key == 0 ) tud_msc_set_sense(p_cbw->lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00);

            // Stall bulk In if needed
            if (p_cbw->total_bytes) usbd_edpt_stall(rhport, p_msc->ep_in);
          }
          else
          {
            p_msc->total_len = (unsigned int) resplen;
            p_csw->status = MSC_CSW_STATUS_PASSED;

            if (p_msc->total_len)
            {
              usbd_edpt_xfer(rhport, p_msc->ep_in, _mscd_buf, p_msc->total_len);
            }else
            {
              p_msc->stage = MSC_STAGE_STATUS;
            }
          }
        }
      }
    break;

    case MSC_STAGE_DATA:
      // OUT transfer, invoke callback if needed
      if ( !tu_bit_test(p_cbw->dir, 7) )
      {
        if ( SCSI_CMD_WRITE_10 != p_cbw->command[0] )
        {
          int cb_result = tud_msc_scsi_cb(p_cbw->lun, p_cbw->command, _mscd_buf, p_msc->total_len);

          if ( cb_result < 0 )
          {
            p_csw->status = MSC_CSW_STATUS_FAILED;
            tud_msc_set_sense(p_cbw->lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00); // Sense = Invalid Command Operation
          }else
          {
            p_csw->status = MSC_CSW_STATUS_PASSED;
          }
        }
        else
        {
          unsigned short const block_sz = p_cbw->total_bytes / rdwr10_get_blockcount(p_cbw->command);

          // Adjust lba with transferred bytes
          unsigned int const lba = rdwr10_get_lba(p_cbw->command) + (p_msc->xferred_len / block_sz);

          // Application can consume smaller bytes
          int nbytes = tud_msc_write10_cb(p_cbw->lun, lba, p_msc->xferred_len % block_sz, _mscd_buf, xferred_bytes);

          if ( nbytes < 0 )
          {
            // negative means error -> skip to status phase, status in CSW set to failed
            p_csw->data_residue = p_cbw->total_bytes - p_msc->xferred_len;
            p_csw->status       = MSC_CSW_STATUS_FAILED;
            p_msc->stage        = MSC_STAGE_STATUS;

            tud_msc_set_sense(p_cbw->lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00); // Sense = Invalid Command Operation
            break;
          }else
          {
            // Application consume less than what we got (including zero)
            if ( nbytes < (int) xferred_bytes )
            {
              if ( nbytes > 0 )
              {
                p_msc->xferred_len += nbytes;
                memmove(_mscd_buf, _mscd_buf+nbytes, xferred_bytes-nbytes);
              }

              // simulate an transfer complete with adjusted parameters --> this driver callback will fired again
              dcd_event_xfer_complete(rhport, p_msc->ep_out, xferred_bytes-nbytes, XFER_RESULT_SUCCESS, false);

              return true; // skip the rest
            }
            else
            {
              // Application consume all bytes in our buffer. Nothing to do, process with normal flow
            }
          }
        }
      }

      // Accumulate data so far
      p_msc->xferred_len += xferred_bytes;

      if ( p_msc->xferred_len >= p_msc->total_len )
      {
        // Data Stage is complete
        p_msc->stage = MSC_STAGE_STATUS;
      }
      else
      {
        // READ10 & WRITE10 Can be executed with large bulk of data e.g write 8K bytes (several flash write)
        // We break it into multiple smaller command whose data size is up to CFG_TUD_MSC_EP_BUFSIZE
        if (SCSI_CMD_READ_10 == p_cbw->command[0])
        {
          proc_read10_cmd(rhport, p_msc);
        }
        else if (SCSI_CMD_WRITE_10 == p_cbw->command[0])
        {
          proc_write10_cmd(rhport, p_msc);
        }else
        {
          // No other command take more than one transfer yet -> unlikely error
          TU_BREAKPOINT();
        }
      }
    break;

    case MSC_STAGE_STATUS:
      // processed immediately after this switch, supposedly to be empty
    break;

    case MSC_STAGE_STATUS_SENT:
      // Wait for the Status phase to complete
      if( (ep_addr == p_msc->ep_in) && (xferred_bytes == sizeof(msc_csw_t)) )
      {
        // Invoke complete callback if defined
        // Note: There is racing issue with samd51 + qspi flash testing with arduino
        // if complete_cb() is invoked after queuing the status.
        switch(p_cbw->command[0])
        {
          case SCSI_CMD_READ_10:
           // if ( tud_msc_read10_complete_cb ) tud_msc_read10_complete_cb(p_cbw->lun);
          break;

          case SCSI_CMD_WRITE_10:
          //  if ( tud_msc_write10_complete_cb ) tud_msc_write10_complete_cb(p_cbw->lun);
          break;

          default:
         // if ( tud_msc_scsi_complete_cb ) tud_msc_scsi_complete_cb(p_cbw->lun, p_cbw->command);
          break;
        }

        // Move to default CMD stage
        p_msc->stage = MSC_STAGE_CMD;

        // Queue for the next CBW
        usbd_edpt_xfer(rhport, p_msc->ep_out, (unsigned char*) &p_msc->cbw, sizeof(msc_cbw_t));
      }
    break;

    default : break;
  }

  if ( p_msc->stage == MSC_STAGE_STATUS )
  {
    // Either endpoints is stalled, need to wait until it is cleared by host
   if ( usbd_edpt_stalled(rhport,  p_msc->ep_in) || usbd_edpt_stalled(rhport,  p_msc->ep_out) )
    {
      // simulate an transfer complete with adjusted parameters --> this driver callback will fired again
      // and response with status phase after halted endpoints are cleared.
      // note: use ep_out to prevent confusing with STATUS complete
      dcd_event_xfer_complete(rhport, p_msc->ep_out, 0, XFER_RESULT_SUCCESS, false);
   }
   else
    {
    //  // Move to Status Sent stage
      p_msc->stage = MSC_STAGE_STATUS_SENT;

      // Send SCSI Status
      usbd_edpt_xfer(rhport, p_msc->ep_in , (unsigned char*) &p_msc->csw, sizeof(msc_csw_t));
    }
  }

  return true;
}

/*------------------------------------------------------------------*/
/* SCSI Command Process
 *------------------------------------------------------------------*/

// return response's length (copied to buffer). Negative if it is not an built-in command or indicate Failed status (CSW)
// In case of a failed status, sense key must be set for reason of failure
static int proc_builtin_scsi(unsigned char lun, unsigned char const scsi_cmd[16], unsigned char* buffer, unsigned int bufsize)
{
  (void) bufsize; // TODO refractor later
  int resplen;

  switch ( scsi_cmd[0] )
  {
    case SCSI_CMD_TEST_UNIT_READY:
      resplen = 0;
      if ( !tud_msc_test_unit_ready_cb(lun) )
      {
        // Failed status response
        resplen = - 1;

        // If sense key is not set by callback, default to Logical Unit Not Ready, Cause Not Reportable
        if ( _mscd_itf.sense_key == 0 ) tud_msc_set_sense(lun, SCSI_SENSE_NOT_READY, 0x04, 0x00);
      }
    break;

    case SCSI_CMD_START_STOP_UNIT:
      resplen = 0;

     //if (tud_msc_start_stop_cb)
      //{
        scsi_start_stop_unit_t const * start_stop = (scsi_start_stop_unit_t const *) scsi_cmd;
        if ( !tud_msc_start_stop_cb(lun, start_stop->power_condition, start_stop->start, start_stop->load_eject) )
        {
           //Failed status response
          resplen = - 1;

         //  If sense key is not set by callback, default to Logical Unit Not Ready, Cause Not Reportable
          if ( _mscd_itf.sense_key == 0 ) tud_msc_set_sense(lun, SCSI_SENSE_NOT_READY, 0x04, 0x00);
        }
      //}
    break;

    case SCSI_CMD_READ_CAPACITY_10:
    {
      unsigned int block_count;
      unsigned int block_size;
      unsigned short block_size_u16;

      tud_msc_capacity_cb(lun, &block_count, &block_size_u16);
      block_size = (unsigned int) block_size_u16;

      // Invalid block size/count from callback, possibly unit is not ready
      // stall this request, set sense key to NOT READY
      if (block_count == 0 || block_size == 0)
      {
        resplen = -1;

        // If sense key is not set by callback, default to Logical Unit Not Ready, Cause Not Reportable
        if ( _mscd_itf.sense_key == 0 ) tud_msc_set_sense(lun, SCSI_SENSE_NOT_READY, 0x04, 0x00);
      }else
      {
        scsi_read_capacity10_resp_t read_capa10;

        read_capa10.last_lba = tu_htonl(block_count-1);
        read_capa10.block_size = tu_htonl(block_size);

        resplen = sizeof(read_capa10);
        memcpy(buffer, &read_capa10, resplen);
      }
    }
    break;

    case SCSI_CMD_READ_FORMAT_CAPACITY:
    {
      scsi_read_format_capacity_data_t read_fmt_capa =
      {
          .list_length     = 8,
          .block_num       = 0,
          .descriptor_type = 2, // formatted media
          .block_size_u16  = 0
      };

      unsigned int block_count;
      unsigned short block_size;

      tud_msc_capacity_cb(lun, &block_count, &block_size);

      // Invalid block size/count from callback, possibly unit is not ready
      // stall this request, set sense key to NOT READY
      if (block_count == 0 || block_size == 0)
      {
        resplen = -1;

        // If sense key is not set by callback, default to Logical Unit Not Ready, Cause Not Reportable
        if ( _mscd_itf.sense_key == 0 ) tud_msc_set_sense(lun, SCSI_SENSE_NOT_READY, 0x04, 0x00);
      }else
      {
        read_fmt_capa.block_num = tu_htonl(block_count);
        read_fmt_capa.block_size_u16 = tu_htons(block_size);

        resplen = sizeof(read_fmt_capa);
        memcpy(buffer, &read_fmt_capa, resplen);
      }
    }
    break;

    case SCSI_CMD_INQUIRY:
    {
      scsi_inquiry_resp_t inquiry_rsp =
      {
          .is_removable         = 1,
          .version              = 2,
          .response_data_format = 2,
      };

       //vendor_id, product_id, product_rev is space padded string
      memset(inquiry_rsp.vendor_id  , ' ', sizeof(inquiry_rsp.vendor_id));
      memset(inquiry_rsp.product_id , ' ', sizeof(inquiry_rsp.product_id));
      memset(inquiry_rsp.product_rev, ' ', sizeof(inquiry_rsp.product_rev));

      tud_msc_inquiry_cb(lun, inquiry_rsp.vendor_id, inquiry_rsp.product_id, inquiry_rsp.product_rev);

      resplen = sizeof(inquiry_rsp);
      memcpy(buffer, &inquiry_rsp, resplen);
    }
    break;

    case SCSI_CMD_MODE_SENSE_6:
    {
      scsi_mode_sense6_resp_t mode_resp =
      {
          .data_len = 3,
          .medium_type = 0,
          .write_protected = false,
          .reserved = 0,
          .block_descriptor_len = 0  // no block descriptor are included
      };

      bool writable = true;
      //if (tud_msc_is_writable_cb) {
      //   writable = tud_msc_is_writable_cb(lun);
     // }
      mode_resp.write_protected = !writable;

      resplen = sizeof(mode_resp);
      memcpy(buffer, &mode_resp, resplen);
    }
    break;

    case SCSI_CMD_REQUEST_SENSE:
    {
      scsi_sense_fixed_resp_t sense_rsp =
      {
          .response_code = 0x70,
          .valid         = 1
      };

      sense_rsp.add_sense_len = sizeof(scsi_sense_fixed_resp_t) - 8;

      sense_rsp.sense_key           = _mscd_itf.sense_key;
      sense_rsp.add_sense_code      = _mscd_itf.add_sense_code;
      sense_rsp.add_sense_qualifier = _mscd_itf.add_sense_qualifier;

      resplen = sizeof(sense_rsp);
      memcpy(buffer, &sense_rsp, resplen);

      // Clear sense data after copy
      tud_msc_set_sense(lun, 0, 0, 0);
    }
    break;

    default: resplen = -1; break;
  }

  return resplen;
}

static void proc_read10_cmd(unsigned char rhport, mscd_interface_t* p_msc)
{
  msc_cbw_t const * p_cbw = &p_msc->cbw;
  msc_csw_t       * p_csw = &p_msc->csw;

  unsigned short const block_cnt = rdwr10_get_blockcount(p_cbw->command);

  unsigned short const block_sz = p_cbw->total_bytes / block_cnt;

  // Adjust lba with transferred bytes
  unsigned int const lba = rdwr10_get_lba(p_cbw->command) + (p_msc->xferred_len / block_sz);

  // remaining bytes capped at class buffer
  int nbytes = (int) tu_min32(sizeof(_mscd_buf), p_cbw->total_bytes-p_msc->xferred_len);

  // Application can consume smaller bytes
  nbytes = tud_msc_read10_cb(p_cbw->lun, lba, p_msc->xferred_len % block_sz, _mscd_buf, (unsigned int) nbytes);

  if ( nbytes < 0 )
  {
    // negative means error -> pipe is stalled & status in CSW set to failed
    p_csw->data_residue = p_cbw->total_bytes - p_msc->xferred_len;
    p_csw->status       = MSC_CSW_STATUS_FAILED;

    tud_msc_set_sense(p_cbw->lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00); // Sense = Invalid Command Operation
    usbd_edpt_stall(rhport, p_msc->ep_in);
  }
  else if ( nbytes == 0 )
  {
    // zero means not ready -> simulate an transfer complete so that this driver callback will fired again
    dcd_event_xfer_complete(rhport, p_msc->ep_in, 0, XFER_RESULT_SUCCESS, false);
  }
  else
  {
    usbd_edpt_xfer(rhport, p_msc->ep_in, _mscd_buf, nbytes);
  }
}

static void proc_write10_cmd(unsigned char rhport, mscd_interface_t* p_msc)
{
  msc_cbw_t const * p_cbw = &p_msc->cbw;
  bool writable = true;
 // if (tud_msc_is_writable_cb) {
 //   writable = tud_msc_is_writable_cb(p_cbw->lun);
 // }
  if (!writable) {
    msc_csw_t* p_csw = &p_msc->csw;
    p_csw->data_residue = p_cbw->total_bytes;
    p_csw->status       = MSC_CSW_STATUS_FAILED;

    tud_msc_set_sense(p_cbw->lun, SCSI_SENSE_DATA_PROTECT, 0x27, 0x00); // Sense = Write protected
    usbd_edpt_stall(rhport, p_msc->ep_out);
    return;
  }

  // remaining bytes capped at class buffer
  int nbytes = (int) tu_min32(sizeof(_mscd_buf), p_cbw->total_bytes-p_msc->xferred_len);

  // Write10 callback will be called later when usb transfer complete
  usbd_edpt_xfer(rhport, p_msc->ep_out, _mscd_buf, nbytes);
}

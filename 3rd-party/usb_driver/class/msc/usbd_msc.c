/*
 * Copyright (c) 2022, sakumisu
 * Copyright (c) 2024, zhihong chen
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This driver is based on the 1.4.1 version of class/msc/usbd_msc.h
 * but has been rewritten to be easier to read and use.
 */

/**************************** include header *********************************/
#include "usbd_msc.h"
#include "usbd_cdc_acm.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/
#define MSC_OUT_EP_IDX 0
#define MSC_IN_EP_IDX  1

#define MSC_REQ_RESET       0xFF
#define MSC_REQ_GET_MAX_LUN 0xFE

#define BOT_CBW_SIGNATURE 0x43425355
#define BOT_CSW_SIGNATURE 0x53425355

#define INQUIRY_PAGE00_LEN            7
#define REQUEST_SENSE_DATA_LEN        0x12
#define SCSI_RESP_FIXED_SENSEDATA_LEN 18 /* Minimum size */
#define SCSI_RESP_INQUIRY_LEN         36 /* Minimum size */

#define BOT_CBW_SIZEOF 31
#define BOT_CSW_SIZEOF 13

/* CSW Status Definitions */
#define CSW_STS_CMD_PASSED  0x00
#define CSW_STS_CMD_FAILED  0x01
#define CSW_STS_PHASE_ERROR 0x02

/* SCSI Commands */
#define SCSI_TEST_UNIT_READY        0x00
#define SCSI_REQUEST_SENSE          0x03
#define SCSI_INQUIRY                0x12
#define SCSI_MODE_SENSE6            0x1a
#define SCSI_START_STOP_UNIT        0x1b
#define SCSI_PREVENT_MEDIAREMOVAL   0x1e
#define SCSI_READ_FORMAT_CAPACITIES 0x23
#define SCSI_READ_CAPACITY10        0x25
#define SCSI_READ10                 0x28
#define SCSI_WRITE10                0x2a
#define SCSI_VERIFY10               0x2f
#define SCSI_MODE_SENSE10           0x5A
#define SCSI_READ12                 0xa8
#define SCSI_WRITE12                0xaa

/* Hardware Error KCQ values */
#define SCSI_KCQHE_WRITE_FAULT        0x040300
#define SCSI_KCQHE_UREINRESERVED_AREA 0x041100

/* Illegal Request KCQ values */
#define SCSI_KCQIR_INVALID_CMD          0x052000
#define SCSI_KCQIR_LBA_OUTOF_RANGE      0x052100
#define SCSI_KCQIR_INVALID_FIELD_IN_CBA 0x052400

/**************************** type definition ********************************/

/**************************** function declear *******************************/
static usb_status_t msc_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len);
static usb_status_t msc_scsi_process_write(uint32_t nbytes);
static usb_status_t msc_scsi_process_read(void);

/************************* variable definition *******************************/
static usbd_msc_class_t usbd_msc_handle = {
    .ep[0] = {
        0,
        NULL,
    },
    .ep[1] = {
        0,
        NULL,
    },
    .cb = NULL,
    .intf_cb = {
        msc_class_intf_req_handler,
        NULL,
        NULL,
    },
};

USB_MEM_ALIGNX struct bot_cbw msc_bot_cbw;
USB_MEM_ALIGNX struct bot_csw msc_bot_csw;
USB_MEM_ALIGNX usbd_msc_t usbd_msc;
uint8_t msc_error_flag = 0;

/********************** function implementation ******************************/
static usb_status_t msc_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    switch (req->bRequest) {
    case MSC_REQ_RESET:
        if (req->wValue == 0 && req->wIndex == 0) {
            usbd_msc.status = MSC_READ_CBW;
        } else {
            return USB_ERROR;
        }
        break;

    case MSC_REQ_GET_MAX_LUN:
        if (req->wValue == 0 && req->wLength == 1) {
            (*data)[0] = usbd_msc.maxlun;
            *len = 1;
        } else {
            if (msc_error_flag == 0) {
                msc_error_flag = 1;
            }
            return USB_ERROR;
        }
        if (msc_error_flag >= 1) {
            usbd_open_endpoint(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr, 512, USB_ENDPOINT_TYPE_BULK);
            usbd_open_endpoint(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, 512, USB_ENDPOINT_TYPE_BULK);
            usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, (uint8_t *)&msc_bot_cbw, BOT_CBW_SIZEOF);
        }
        break;

    default:
        USB_LOG_ERR("Unhandled MSC Class bRequest 0x%02x\r\n", req->bRequest);
        return USB_ERROR;
    }
    return USB_OK;
}

static usb_status_t msc_notify_handler(usbd_event_t event)
{
    switch (event) {
    case USBD_EVENT_RESET:
        usbd_msc.status = MSC_READ_CBW;
        break;

    case USBD_EVENT_CONFIGURED:
        usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, (uint8_t *)&msc_bot_cbw, BOT_CBW_SIZEOF);
        break;

    default:
        break;
    }
    return USB_OK;
}

/**
* @brief  msc_send_csw
*         Send the Command Status Wrapper
* @param  pdev: device instance
* @param  status : CSW status
* @retval None
*/
static void msc_send_csw(uint8_t status)
{
    msc_bot_csw.dSignature = BOT_CSW_SIGNATURE;
    msc_bot_csw.bStatus = status;

    /* updating the State Machine , so that we wait CSW when this
     * transfer is complete, ie when we get a bulk in callback
     */
    usbd_msc.status = MSC_WAIT_CSW;

    usbd_ep_tx(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr, (uint8_t *)&msc_bot_csw, sizeof(struct bot_csw));
}

static void msc_send_info(uint8_t *buffer, uint8_t size)
{
    size = USB_MIN(size, msc_bot_cbw.dDataLength);

    /* updating the State Machine , so that we send CSW when this
     * transfer is complete, ie when we get a bulk in callback
     */
    usbd_msc.status = MSC_SEND_CSW;

    usbd_ep_tx(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr, buffer, size);

    msc_bot_csw.dDataResidue -= size;
    msc_bot_csw.bStatus = CSW_STS_CMD_PASSED;
}

/**
* @brief  msc_scsi_set_sensedata
*         Load the last error code in the error list
* @param  sKey: Sense Key
* @param  ASC: Additional Sense Code
* @retval none

*/
static void msc_scsi_set_sensedata(uint32_t KCQ)
{
    usbd_msc.sKey = (uint8_t)(KCQ >> 16);
    usbd_msc.ASC = (uint8_t)(KCQ >> 8);
    usbd_msc.ASQ = (uint8_t)(KCQ);
}

/**
* @brief  msc_scsi_check_addressrange
*         Check address range
* @param  lun: Logical unit number
* @param  blk_offset: first block address
* @param  blk_nbr: number of block to be processed
* @retval status
*/
static usb_status_t msc_scsi_check_addressrange(uint8_t lun, uint32_t blk_offset, uint16_t blk_nbr)
{
    if ((blk_offset + blk_nbr) > usbd_msc.blk_nbr[lun]) {
        msc_scsi_set_sensedata(SCSI_KCQIR_LBA_OUTOF_RANGE);
        USB_LOG_ERR("LBA out of range\r\n");
        return USB_ERROR;
    }
    return USB_OK;
}

/**
* @brief  msc_scsi_testunitready
*         Process SCSI Test Unit Ready Command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_testunitready(uint8_t **data, uint32_t *len)
{
    if (msc_bot_cbw.dDataLength != 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }
    *data = NULL;
    *len = 0;
    return USB_OK;
}

/**
* @brief  msc_scsi_request_sense
*         Process Request Sense command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_request_sense(uint8_t **data, uint32_t *len)
{
    uint8_t data_len = SCSI_RESP_FIXED_SENSEDATA_LEN;
    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    if (msc_bot_cbw.cb[4] < SCSI_RESP_FIXED_SENSEDATA_LEN) {
        data_len = msc_bot_cbw.cb[4];
    }

    (*data)[0] = 0x70;
    (*data)[1] = 0x00;
    (*data)[2] = usbd_msc.sKey; /* Sense Key */
    (*data)[3] = 0x00;
    (*data)[4] = 0x00;
    (*data)[5] = 0x00;
    (*data)[6] = 0x00;
    (*data)[7] = REQUEST_SENSE_DATA_LEN - 8;
    (*data)[8] = 0x00;
    (*data)[9] = 0x00;
    (*data)[10] = 0x00;
    (*data)[11] = 0x00;
    (*data)[12] = usbd_msc.ASC; /* Additional Sense Code */
    (*data)[13] = usbd_msc.ASQ; /* Additional Sense Request */
    (*data)[14] = 0x00;
    (*data)[15] = 0x00;
    (*data)[16] = 0x00;
    (*data)[17] = 0x00;
    *len = data_len;
    return USB_OK;
}

/**
* @brief  msc_scsi_inquiry
*         Process Inquiry command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_inquiry(uint8_t **data, uint32_t *len)
{
    uint8_t data_len = SCSI_RESP_INQUIRY_LEN;

    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    if ((msc_bot_cbw.cb[1] & 0x01U) != 0U) {
        if (msc_bot_cbw.cb[2] == 0U) {
            (*data)[0] = 0x00;
            (*data)[1] = 0x00;
            (*data)[2] = 0x00;
            (*data)[3] = (INQUIRY_PAGE00_LEN - 4);
            (*data)[4] = 0x00;
            (*data)[5] = 0x80;
            (*data)[6] = 0x83;
            data_len = INQUIRY_PAGE00_LEN;
        } else if (msc_bot_cbw.cb[2] == 0x80U) {
            (*data)[0] = 0x00;
            (*data)[1] = 0x80;
            (*data)[2] = 0x00;
            (*data)[3] = 0x08;
            (*data)[4] = 0x20; /* Put Product Serial number */
            (*data)[5] = 0x20;
            (*data)[6] = 0x20;
            (*data)[7] = 0x20;
            data_len = 0x08;
        } else {
            msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
            return USB_ERROR;
        }
    } else {
        if (msc_bot_cbw.cb[4] < SCSI_RESP_INQUIRY_LEN) {
            data_len = msc_bot_cbw.cb[4];
        }
        if (usbd_msc_handle.cb && usbd_msc_handle.cb->pinquiry) {
            data_len = USBD_STD_INQUIRY_LENGTH;
            memcpy(*data, (uint8_t *)(usbd_msc_handle.cb->pinquiry), data_len);
        }
    }

    *len = data_len;
    return USB_OK;
}

/**
* @brief  msc_scsi_startstopunit
*         Process Start Stop Unit command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_startstopunit(uint8_t **data, uint32_t *len)
{
    if (msc_bot_cbw.dDataLength != 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }
    *data = NULL;
    *len = 0;
    return USB_OK;
}

static usb_status_t msc_scsi_preventallowmediaremoval(uint8_t **data, uint32_t *len)
{
    if (msc_bot_cbw.dDataLength != 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }
    *data = NULL;
    *len = 0;
    return USB_OK;
}

/**
* @brief  msc_scsi_mode_sense6
*         Process Mode Sense6 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_mode_sense6(uint8_t **data, uint32_t *len)
{
    uint8_t data_len = 4;
    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    if (msc_bot_cbw.cb[4] < 4) {
        data_len = msc_bot_cbw.cb[4];
    }

    (*data)[0] = 0x03;
    (*data)[1] = 0x00;
    (*data)[2] = 0x00;
    (*data)[3] = 0x00;
    (*data)[4] = 0x00;
    (*data)[5] = 0x00;
    (*data)[6] = 0x00;
    (*data)[7] = 0x00;

    if (usbd_msc_handle.cb->is_writeprotected(msc_bot_cbw.bLUN) != USB_OK) {
        (*data)[2] = 0x80;
        data_len = 8;
    }
    *len = data_len;
    return USB_OK;
}

/**
* @brief  msc_scsi_mode_sense10
*         Process Mode Sense10 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_mode_sense10(uint8_t **data, uint32_t *len)
{
    uint8_t data_len = 27;
    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    if (msc_bot_cbw.cb[8] < 27) {
        data_len = msc_bot_cbw.cb[8];
    }

    (*data)[0] = 0x00;
    (*data)[1] = 0x26;
    (*data)[2] = 0x00;
    (*data)[3] = 0x00;
    (*data)[4] = 0x00;
    (*data)[5] = 0x00;
    (*data)[6] = 0x00;
    (*data)[7] = 0x00;
    (*data)[8] = 0x08;
    (*data)[9] = 0x12;
    (*data)[10] = 0x00;
    (*data)[11] = 0x00;
    (*data)[12] = 0x00;
    (*data)[13] = 0x00;
    (*data)[14] = 0x00;
    (*data)[15] = 0x00;
    (*data)[16] = 0x00;
    (*data)[17] = 0x00;
    (*data)[18] = 0x00;
    (*data)[19] = 0x00;
    (*data)[20] = 0x00;
    (*data)[21] = 0x00;
    (*data)[22] = 0x00;
    (*data)[23] = 0x00;
    (*data)[24] = 0x00;
    (*data)[25] = 0x00;
    (*data)[26] = 0x00;
    *len = data_len;
    return USB_OK;
}

/**
* @brief  msc_scsi_read_formatcapacity
*         Process Read Format Capacity command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_read_formatcapacity(uint8_t **data, uint32_t *len)
{
    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }
    (*data)[0] = 0x00;
    (*data)[1] = 0x00;
    (*data)[2] = 0x00;
    (*data)[3] = 0x08; /* Capacity List Length */
    (*data)[4] = (uint8_t)((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] >> 24) & 0xff);
    (*data)[5] = (uint8_t)((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] >> 16) & 0xff);
    (*data)[6] = (uint8_t)((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] >> 8) & 0xff);
    (*data)[7] = (uint8_t)((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] >> 0) & 0xff);
    (*data)[8] = 0x02; /* Descriptor Code: Formatted Media */
    (*data)[9] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 16) & 0xff);
    (*data)[10] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 8) & 0xff);
    (*data)[11] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 0) & 0xff);
    *len = 12;
    return USB_OK;
}

/**
* @brief  msc_scsi_read_capacity10
*         Process Read Capacity 10 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_read_capacity10(uint8_t **data, uint32_t *len)
{
    if (msc_bot_cbw.dDataLength == 0U) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }
    (*data)[0] = (uint8_t)(((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] - 1) >> 24) & 0xff),
    (*data)[1] = (uint8_t)(((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] - 1) >> 16) & 0xff),
    (*data)[2] = (uint8_t)(((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] - 1) >> 8) & 0xff),
    (*data)[3] = (uint8_t)(((usbd_msc.blk_nbr[msc_bot_cbw.bLUN] - 1) >> 0) & 0xff),
    (*data)[4] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 24) & 0xff),
    (*data)[5] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 16) & 0xff),
    (*data)[6] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 8) & 0xff),
    (*data)[7] = (uint8_t)((usbd_msc.blk_size[msc_bot_cbw.bLUN] >> 0) & 0xff),
    *len = 8;
    return USB_OK;
}

/**
* @brief  msc_scsi_read10
*         Process Read10 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_read10(uint8_t **data, uint32_t *len)
{
    (void)data;
    (void)len;
    if (((msc_bot_cbw.bmFlags & 0x80U) != 0x80U) || (msc_bot_cbw.dDataLength == 0U)) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    usbd_msc.blk_addr = USB_GET_BE32(&msc_bot_cbw.cb[2]);
    usbd_msc.blk_len = USB_GET_BE16(&msc_bot_cbw.cb[7]);

    if (msc_scsi_check_addressrange(msc_bot_cbw.bLUN, usbd_msc.blk_addr, usbd_msc.blk_len) != USB_OK) {
        return USB_ERROR;
    }

    if (msc_bot_cbw.dDataLength != (usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN])) {
        USB_LOG_ERR("10scsi_blk_len does not match with dDataLength\r\n");
        return USB_ERROR;
    }
    usbd_msc.status = MSC_DATA_IN;

    return msc_scsi_process_read();
}

/**
* @brief  msc_scsi_read12
*         Process Read12 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_read12(uint8_t **data, uint32_t *len)
{
    (void)data;
    (void)len;
    if (((msc_bot_cbw.bmFlags & 0x80U) != 0x80U) || (msc_bot_cbw.dDataLength == 0U)) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    usbd_msc.blk_addr = USB_GET_BE32(&msc_bot_cbw.cb[2]);
    usbd_msc.blk_len = USB_GET_BE32(&msc_bot_cbw.cb[6]);

    if (msc_scsi_check_addressrange(msc_bot_cbw.bLUN, usbd_msc.blk_addr, usbd_msc.blk_len) != USB_OK) {
        return USB_ERROR;
    }

    if (msc_bot_cbw.dDataLength != (usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN])) {
        USB_LOG_ERR("12scsi_blk_len does not match with dDataLength\r\n");
        return USB_ERROR;
    }
    usbd_msc.status = MSC_DATA_IN;
    return msc_scsi_process_read();
}

/**
* @brief  msc_scsi_write10
*         Process Write10 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_write10(uint8_t **data, uint32_t *len)
{
    (void)data;
    (void)len;
    uint32_t data_len = 0;

    if (((msc_bot_cbw.bmFlags & 0x80U) != 0x00U) || (msc_bot_cbw.dDataLength == 0U)) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    usbd_msc.blk_addr = USB_GET_BE32(&msc_bot_cbw.cb[2]);
    usbd_msc.blk_len = USB_GET_BE16(&msc_bot_cbw.cb[7]);
    data_len = usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN];
    if (msc_scsi_check_addressrange(msc_bot_cbw.bLUN, usbd_msc.blk_addr, usbd_msc.blk_len) != USB_OK) {
        return USB_ERROR;
    }

    if (msc_bot_cbw.dDataLength != data_len) {
        return USB_ERROR;
    }
    usbd_msc.status = MSC_DATA_OUT;
    data_len = USB_MIN(data_len, USB_CFG_MSC_BUF_SIZE);
    usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, usbd_msc.buffer, data_len);
    return USB_OK;
}

/**
* @brief  msc_scsi_write12
*         Process Write12 command
* @param  lun: Logical unit number
* @param  params: Command parameters
* @retval status
*/
static usb_status_t msc_scsi_write12(uint8_t **data, uint32_t *len)
{
    (void)data;
    (void)len;
    uint32_t data_len = 0;

    if (((msc_bot_cbw.bmFlags & 0x80U) != 0x00U) || (msc_bot_cbw.dDataLength == 0U)) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    usbd_msc.blk_addr = USB_GET_BE32(&msc_bot_cbw.cb[2]);
    usbd_msc.blk_len = USB_GET_BE32(&msc_bot_cbw.cb[6]);
    data_len = usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN];
    if (msc_scsi_check_addressrange(msc_bot_cbw.bLUN, usbd_msc.blk_addr, usbd_msc.blk_len) != USB_OK) {
        return USB_ERROR;
    }

    if (msc_bot_cbw.dDataLength != data_len) {
        return USB_ERROR;
    }
    usbd_msc.status = MSC_DATA_OUT;
    data_len = USB_MIN(data_len, USB_CFG_MSC_BUF_SIZE);
    usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, usbd_msc.buffer, data_len);
    return USB_OK;
}

/**
* @brief  msc_scsi_process_read
*         Handle Read Process
* @param  lun: Logical unit number
* @retval status
*/
static usb_status_t msc_scsi_process_read(void)
{
    uint32_t transfer_len;

    transfer_len = USB_MIN(usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN], USB_CFG_MSC_BUF_SIZE);

    if (usbd_msc_handle.cb && usbd_msc_handle.cb->read) {
        if (usbd_msc_handle.cb->read(msc_bot_cbw.bLUN, usbd_msc.buffer, usbd_msc.blk_addr, transfer_len) != 0) {
            msc_scsi_set_sensedata(SCSI_KCQHE_UREINRESERVED_AREA);
            return USB_ERROR;
        }
    }

    usbd_msc.blk_addr += (transfer_len / usbd_msc.blk_size[msc_bot_cbw.bLUN]);
    usbd_msc.blk_len -= (transfer_len / usbd_msc.blk_size[msc_bot_cbw.bLUN]);
    msc_bot_csw.dDataResidue -= transfer_len;

    if (usbd_msc.blk_len == 0) {
        usbd_msc.status = MSC_SEND_CSW;
    }

    usbd_ep_tx(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr, usbd_msc.buffer, transfer_len);

    return USB_OK;
}

/**
* @brief  msc_scsi_process_write
*         Handle Write Process
* @param  lun: Logical unit number
* @retval status
*/
static usb_status_t msc_scsi_process_write(uint32_t nbytes)
{
    uint32_t data_len = 0;

    if (usbd_msc_handle.cb && usbd_msc_handle.cb->write) {
        if (usbd_msc_handle.cb->write(msc_bot_cbw.bLUN, usbd_msc.buffer, usbd_msc.blk_addr, nbytes) != 0) {
            msc_scsi_set_sensedata(SCSI_KCQHE_WRITE_FAULT);
            return USB_ERROR;
        }
    }

    usbd_msc.blk_addr += (nbytes / usbd_msc.blk_size[msc_bot_cbw.bLUN]);
    usbd_msc.blk_len -= (nbytes / usbd_msc.blk_size[msc_bot_cbw.bLUN]);
    msc_bot_csw.dDataResidue -= nbytes;

    if (usbd_msc.blk_len == 0) {
        msc_send_csw(CSW_STS_CMD_PASSED);
    } else {
        data_len = USB_MIN(usbd_msc.blk_len * usbd_msc.blk_size[msc_bot_cbw.bLUN], USB_CFG_MSC_BUF_SIZE);
        usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, usbd_msc.buffer, data_len);
    }

    return USB_OK;
}

/**
* @brief  msc_scsi_cbw_decode
*         Decode the CBW command and set the BOT state machine accordingtly  
* @param  nbytes: data length
* @retval None
*/
static usb_status_t msc_scsi_cbw_decode(uint32_t nbytes)
{
    uint8_t *pbuf = usbd_msc.buffer;
    uint32_t len_send = 0;
    usb_status_t ret = USB_ERROR;

    if (nbytes != sizeof(struct bot_cbw)) {
        USB_LOG_ERR("size != sizeof(cbw)\r\n");
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    }

    msc_bot_csw.dTag = msc_bot_cbw.dTag;
    msc_bot_csw.dDataResidue = msc_bot_cbw.dDataLength;

    if ((msc_bot_cbw.dSignature != BOT_CBW_SIGNATURE) || (msc_bot_cbw.bCBLength < 1) || (msc_bot_cbw.bCBLength > 16)) {
        msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
        return USB_ERROR;
    } else {
        pbuf = usbd_msc.buffer;
        switch (msc_bot_cbw.cb[0]) {
        case SCSI_TEST_UNIT_READY:
            ret = msc_scsi_testunitready(&pbuf, &len_send);
            break;
        case SCSI_REQUEST_SENSE:
            ret = msc_scsi_request_sense(&pbuf, &len_send);
            break;
        case SCSI_INQUIRY:
            ret = msc_scsi_inquiry(&pbuf, &len_send);
            break;
        case SCSI_START_STOP_UNIT:
            ret = msc_scsi_startstopunit(&pbuf, &len_send);
            break;
        case SCSI_PREVENT_MEDIAREMOVAL:
            ret = msc_scsi_preventallowmediaremoval(&pbuf, &len_send);
            break;
        case SCSI_MODE_SENSE6:
            ret = msc_scsi_mode_sense6(&pbuf, &len_send);
            break;
        case SCSI_MODE_SENSE10:
            ret = msc_scsi_mode_sense10(&pbuf, &len_send);
            break;
        case SCSI_READ_FORMAT_CAPACITIES:
            ret = msc_scsi_read_formatcapacity(&pbuf, &len_send);
            break;
        case SCSI_READ_CAPACITY10:
            ret = msc_scsi_read_capacity10(&pbuf, &len_send);
            break;
        case SCSI_READ10:
            ret = msc_scsi_read10(NULL, 0);
            break;
        case SCSI_READ12:
            ret = msc_scsi_read12(NULL, 0);
            break;
        case SCSI_WRITE10:
            ret = msc_scsi_write10(NULL, 0);
            break;
        case SCSI_WRITE12:
            ret = msc_scsi_write12(NULL, 0);
            break;
        case SCSI_VERIFY10:
            //ret = SCSI_verify10(NULL, 0);
            ret = USB_ERROR;
            break;

        default:
            msc_scsi_set_sensedata(SCSI_KCQIR_INVALID_FIELD_IN_CBA);
            USB_LOG_ERR("unsupported cmd:0x%02x\r\n", msc_bot_cbw.cb[0]);
            ret = USB_ERROR;
            break;
        }
    }
    if (ret == USB_OK) {
        if (usbd_msc.status == MSC_READ_CBW) {
            if (len_send) {
                msc_send_info(pbuf, len_send);
            } else {
                msc_send_csw(CSW_STS_CMD_PASSED);
            }
        }
    }
    return ret;
}

/**
* @brief  msc_dataout
*         handle data OUT Stage
* @param  ep: endpoint index
* @param  nbytes: data length
* @retval status
*/
static usb_status_t msc_dataout(uint8_t ep, uint32_t nbytes)
{
    (void)ep;
    switch (usbd_msc.status) {
    case MSC_READ_CBW:
        if (msc_error_flag == 1) {
            if (msc_bot_cbw.dSignature != BOT_CBW_SIGNATURE || nbytes != BOT_CBW_SIZEOF) {
                if ((msc_bot_cbw.bmFlags == 0) && (msc_bot_cbw.dDataLength != 0)) {
                    usbd_set_ep_stall(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr);
                }
                usbd_set_ep_stall(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr);
                usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, (uint8_t *)&msc_bot_cbw, BOT_CBW_SIZEOF);
                USB_LOG_ERR("Command:0x%02x decode err\r\n", msc_bot_cbw.cb[0]);
                return USB_ERROR;
            }
            // if (msc_bot_cbw.cb[0] == 0x12 && msc_bot_cbw.dDataLength == 36 && msc_bot_cbw.bmFlags == 0x80)
            // {
            //     usbd_set_ep_stall(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr);
            //     return USB_ERROR;
            // }
        }
        if (msc_scsi_cbw_decode(nbytes) == USB_ERROR) {
            if ((msc_bot_cbw.bmFlags == 0) && (msc_bot_cbw.dDataLength != 0)) {
                usbd_set_ep_stall(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr);
            }
            usbd_set_ep_stall(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr);
            usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, (uint8_t *)&msc_bot_cbw, BOT_CBW_SIZEOF);
            USB_LOG_ERR("Command:0x%02x decode err\r\n", msc_bot_cbw.cb[0]);
            if (msc_error_flag == 1) {
                usbd_close_endpoint(usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr);
            }
            return USB_ERROR;
        }
        break;

    case MSC_DATA_OUT:
        switch (msc_bot_cbw.cb[0]) {
        case SCSI_WRITE10:
        case SCSI_WRITE12:
            if (msc_scsi_process_write(nbytes) == USB_ERROR) {
                msc_send_csw(CSW_STS_CMD_FAILED);
            }
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
    return USB_OK;
}

/**
* @brief  msc_datain
*         handle data IN Stage
* @param  ep: endpoint index
* @param  nbytes: data length
* @retval status
*/
static usb_status_t msc_datain(uint8_t ep, uint32_t nbytes)
{
    (void)ep;
    (void)nbytes;
    switch (usbd_msc.status) {
    case MSC_DATA_IN:
        switch (msc_bot_cbw.cb[0]) {
        case SCSI_READ10:
        case SCSI_READ12:
            if (msc_scsi_process_read() == USB_ERROR) {
                msc_send_csw(CSW_STS_CMD_FAILED); /* send fail status to host,and the host will retry */
                return USB_ERROR;
            }
            break;

        default:
            break;
        }
        break;

    case MSC_SEND_CSW:
        msc_send_csw(CSW_STS_CMD_PASSED);
        break;

    case MSC_WAIT_CSW:
        usbd_msc.status = MSC_READ_CBW;
        usbd_ep_preparerx(usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr, (uint8_t *)&msc_bot_cbw, BOT_CBW_SIZEOF);
        break;

    default:
        break;
    }
    return USB_OK;
}

/**
 * @brief  usb msc callback register
 * @param  cb \ref usbd_msc_class_callback_t
 * @param  in_ep: endpoint number
 * @retval None
 */
void usbd_msc_class_init(uint8_t out_ep, uint8_t in_ep)
{
    usbd_notify_register(msc_notify_handler);

    usbd_msc_handle.ep[MSC_OUT_EP_IDX].ep_addr = out_ep;
    usbd_msc_handle.ep[MSC_OUT_EP_IDX].cb = msc_dataout;
    usbd_msc_handle.ep[MSC_IN_EP_IDX].ep_addr = in_ep;
    usbd_msc_handle.ep[MSC_IN_EP_IDX].cb = msc_datain;

    usbd_endpoint_register(out_ep, msc_dataout);
    usbd_endpoint_register(in_ep, msc_datain);

    memset((uint8_t *)&usbd_msc, 0, sizeof(usbd_msc_t));

    if (usbd_msc_handle.cb && usbd_msc_handle.cb->get_maxlun) {
        usbd_msc.maxlun = usbd_msc_handle.cb->get_maxlun();
    }
    for (uint8_t i = 0u; i <= usbd_msc.maxlun; i++) {
        if (usbd_msc_handle.cb && usbd_msc_handle.cb->init) {
            usbd_msc_handle.cb->init(i);
        }
        if (usbd_msc_handle.cb && usbd_msc_handle.cb->get_capacity) {
            usbd_msc_handle.cb->get_capacity(i, &usbd_msc.blk_nbr[i], &usbd_msc.blk_size[i]);
        }
        if (USB_CFG_MSC_BUF_SIZE % usbd_msc.blk_size[i]) {
            USB_LOG_ERR("USB_CFG_MSC_BUF_SIZE must be a multiple of block size\r\n");
            while (1) {
            }
        }
    }
}

/**
 * @brief  usb msc callback register
 * @param  cb \ref usbd_msc_cb_t
 * @retval None
 */
void usbd_msc_cb_register(usbd_msc_cb_t *cb)
{
    usbd_msc_handle.cb = cb;
}

/**
 * @brief  usb msc callback unregister
 * @param  None
 * @retval None
 */
void usbd_msc_cb_unregister(void)
{
    usbd_msc_handle.cb = NULL;
}

/**
 * @brief  get usb msc class interface callback
 * @param  None
 * @retval None
 */
usbd_intf_cb_t *usbd_msc_get_inf_cb(void)
{
    return &(usbd_msc_handle.intf_cb);
}

#endif
#endif

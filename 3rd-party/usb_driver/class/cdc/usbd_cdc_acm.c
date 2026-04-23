/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This driver is based on the 1.4.1 version of class/cdc/usbd_cdc_acm.c
 * but has been rewritten to be easier to read and use.
 */

/**************************** include header *********************************/
#include "usbd_cdc_acm.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/
/* CDC class-specific request codes */
/* (usbcdc11.pdf, 6.2, Table 46) */
/* see Table 45 for info about the specific requests. */
#define CDC_REQ_SEND_ENCAPSULATED_COMMAND      0x00
#define CDC_REQ_GET_ENCAPSULATED_RESPONSE      0x01
#define CDC_REQ_SET_COMM_FEATURE               0x02
#define CDC_REQ_GET_COMM_FEATURE               0x03
#define CDC_REQ_CLEAR_COMM_FEATURE             0x04
#define CDC_REQ_SET_AUX_LINE_STATE             0x10
#define CDC_REQ_SET_HOOK_STATE                 0x11
#define CDC_REQ_PULSE_SETUP                    0x12
#define CDC_REQ_SEND_PULSE                     0x13
#define CDC_REQ_SET_PULSE_TIME                 0x14
#define CDC_REQ_RING_AUX_JACK                  0x15
#define CDC_REQ_SET_LINE_CODING                0x20
#define CDC_REQ_GET_LINE_CODING                0x21
#define CDC_REQ_SET_CONTROL_LINE_STATE         0x22
#define CDC_REQ_SEND_BREAK                     0x23
#define CDC_REQ_SET_RINGER_PARAMS              0x30
#define CDC_REQ_GET_RINGER_PARAMS              0x31
#define CDC_REQ_SET_OPERATION_PARAMS           0x32
#define CDC_REQ_GET_OPERATION_PARAMS           0x33
#define CDC_REQ_SET_LINE_PARAMS                0x34
#define CDC_REQ_GET_LINE_PARAMS                0x35
#define CDC_REQ_DIAL_DIGITS                    0x36
#define CDC_REQ_SET_UNIT_PARAMETER             0x37
#define CDC_REQ_GET_UNIT_PARAMETER             0x38
#define CDC_REQ_CLEAR_UNIT_PARAMETER           0x39
#define CDC_REQ_GET_PROFILE                    0x3A
#define CDC_REQ_SET_ETHERNET_MULTICAST_FILTERS 0x40
#define CDC_REQ_SET_ETHERNET_PMP_FILTER        0x41
#define CDC_REQ_GET_ETHERNET_PMP_FILTER        0x42
#define CDC_REQ_SET_ETHERNET_PACKET_FILTER     0x43
#define CDC_REQ_GET_ETHERNET_STATISTIC         0x44
#define CDC_REQ_SET_ATM_DATA_FORMAT            0x50
#define CDC_REQ_GET_ATM_DEVICE_STATISTICS      0x51
#define CDC_REQ_SET_ATM_DEFAULT_VC             0x52
#define CDC_REQ_GET_ATM_VC_STATISTICS          0x53
#define CDC_REQ_GET_NTB_PARAMETERS             0x80
#define CDC_REQ_GET_NET_ADDRESS                0x81
#define CDC_REQ_SET_NET_ADDRESS                0x82
#define CDC_REQ_GET_NTB_FORMAT                 0x83
#define CDC_REQ_SET_NTB_FORMAT                 0x84
#define CDC_REQ_GET_NTB_INPUT_SIZE             0x85
#define CDC_REQ_SET_NTB_INPUT_SIZE             0x86
#define CDC_REQ_GET_MAX_DATAGRAM_SIZE          0x87
#define CDC_REQ_SET_MAX_DATAGRAM_SIZE          0x88
#define CDC_REQ_GET_CRC_MODE                   0x89
#define CDC_REQ_SET_CRC_MODE                   0x90

/**************************** type definition ********************************/

/************************* variable definition *******************************/

/**************************** function declear *******************************/
static usb_status_t usbd_acm_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len);

/************************* variable declear *******************************/
uint8_t CmdBuff[16];

static usbd_acm_class_t usbd_acm_handle = {
    .cb = NULL,
    .intf_cb = {
        usbd_acm_class_intf_req_handler,
        NULL,
        NULL,
    },
};

/********************** function implementation ******************************/
/**
 * @brief  usbd_acm_class_intf_req_handler
 *         Handle the CDC specific requests
 * @param  req: usb requests
 * @param  data: data
 * @param  len: data Length
 * @retval status
*/
static usb_status_t usbd_acm_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    uint8_t cdc_dtr = 0;
    uint8_t cdc_rtr = 0;
    uint8_t interface_num = USB_LOBYTE(req->wIndex);
    cdc_line_coding_t line_coding;

    switch (req->bRequest) {
    case CDC_REQ_SET_LINE_CODING:
        memset(CmdBuff, 0, 16);
        memcpy(&line_coding, *data, *len);
        if (usbd_acm_handle.cb && usbd_acm_handle.cb->set_line_coding) {
            usbd_acm_handle.cb->set_line_coding(line_coding);
        }
        break;

    case CDC_REQ_GET_LINE_CODING:
        if (usbd_acm_handle.cb && usbd_acm_handle.cb->get_line_coding) {
            usbd_acm_handle.cb->get_line_coding(&line_coding);
        }
        memcpy(*data, &line_coding, 7);
        *len = 7;
        break;

    case CDC_REQ_SET_CONTROL_LINE_STATE:
        cdc_dtr = (req->wValue & 0x0001);
        cdc_rtr = (req->wValue & 0x0002);
        if (usbd_acm_handle.cb && usbd_acm_handle.cb->set_dtr) {
            usbd_acm_handle.cb->set_dtr(cdc_dtr);
        }
        if (usbd_acm_handle.cb && usbd_acm_handle.cb->set_rts) {
            usbd_acm_handle.cb->set_rts(cdc_rtr);
        }
        break;

    case CDC_REQ_SEND_BREAK:
        if (usbd_acm_handle.cb && usbd_acm_handle.cb->send_break) {
            usbd_acm_handle.cb->send_break(interface_num);
        }
        break;

    default:
        USB_LOG_ERR("CDC Class bRequest error: 0x%02x\r\n", req->bRequest);
        return USB_ERROR;
    }

    return USB_OK;
}

/**
 * @brief  usbd acm callback register
 * @param  cb \ref usbd_acm_cb_t
 * @retval None
 */
void usbd_acm_cb_register(usbd_acm_cb_t *cb)
{
    usbd_acm_handle.cb = cb;
}

/**
 * @brief  usbd acm callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
void usbd_acm_cb_unregister(uint8_t intf_index)
{
    (void)intf_index;
    usbd_acm_handle.cb = NULL;
}

/**
 * @brief  get usbd cdc class interface callback
 * @param  None
 * @retval None
 */
usbd_intf_cb_t *usbd_acm_get_inf_cb(void)
{
    return &(usbd_acm_handle.intf_cb);
}

#endif
#endif

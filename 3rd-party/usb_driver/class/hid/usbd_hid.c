/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\hid\usbd_hid.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "usbd_hid.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/
/* HID Class Specific Requests (HID 7.2) */
#define HID_REQ_GET_REPORT   0x01
#define HID_REQ_GET_IDLE     0x02
#define HID_REQ_GET_PROTOCOL 0x03
#define HID_REQ_SET_REPORT   0x09
#define HID_REQ_SET_IDLE     0x0A
#define HID_REQ_SET_PROTOCOL 0x0B

/**************************** type definition ********************************/

/************************* variable definition *******************************/

/**************************** function declear *******************************/
static usb_status_t usbd_hid_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len);

/************************* variable declear *******************************/
static usbd_hid_class_t usbd_hid_handle = {
    /* hid handle */
    .cb = NULL,
    .intf_cb = {
        usbd_hid_class_intf_req_handler,
        NULL,
        NULL,
    }
};

/********************** function implementation ******************************/
/**
 * @brief  usbd_hid_class_intf_req_handler
 *         Handle the CDC specific requests
 * @param  req: usb requests
 * @param  data: data
 * @param  len: data Length
 * @retval status
 */
static usb_status_t usbd_hid_class_intf_req_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    uint8_t interface_num = USB_LOBYTE(req->wIndex);

    switch ((uint8_t)req->bRequest) {
    case HID_REQ_SET_REPORT:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->set_report) {
            usbd_hid_handle.cb->set_report(interface_num, USB_LOBYTE(req->wValue), USB_HIBYTE(req->wValue), *data, *len);
        }
        break;

    case HID_REQ_GET_REPORT:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->get_report) {
            usbd_hid_handle.cb->get_report(interface_num, USB_LOBYTE(req->wValue), USB_HIBYTE(req->wValue), data, len);
        }
        break;

    case HID_REQ_SET_IDLE:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->set_idle) {
            usbd_hid_handle.cb->set_idle(interface_num, USB_LOBYTE(req->wValue), USB_HIBYTE(req->wValue));
        }
        //*len = 1;
        break;

    case HID_REQ_GET_IDLE:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->get_idle) {
            (*data)[0] = usbd_hid_handle.cb->get_idle(interface_num, USB_LOBYTE(req->wValue));
        }
        *len = 1;
        break;

    case HID_REQ_SET_PROTOCOL:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->set_protocol) {
            usbd_hid_handle.cb->set_protocol(interface_num, USB_LOBYTE(req->wValue));
        }
        break;

    case HID_REQ_GET_PROTOCOL:
        if (usbd_hid_handle.cb && usbd_hid_handle.cb->get_protocol) {
            (*data)[0] = usbd_hid_handle.cb->get_protocol(interface_num);
        }
        *len = 1;
        break;

    default:
        USB_LOG_ERR("HID Class bRequest error: 0x%02x\r\n", req->bRequest);
        return USB_ERROR;
    }

    return USB_OK;
}

/**
 * @brief  usb hid callback register
 * @param  cb \ref usbd_hid_cb_t
 * @retval None
 */
void usbd_hid_cb_register(usbd_hid_cb_t *cb)
{
    usbd_hid_handle.cb = cb;
}

/**
 * @brief  usb hid callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
void usbd_hid_cb_unregister(uint8_t intf_index)
{
    (void)intf_index;
    usbd_hid_handle.cb = NULL;
}

/**
 * @brief  get usb hid class interface callback
 * @param  None
 * @retval None
 */
usbd_intf_cb_t *usbd_hid_get_inf_cb(void)
{
    return &(usbd_hid_handle.intf_cb);
}

#endif
#endif

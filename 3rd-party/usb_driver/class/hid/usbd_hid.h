/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\hid\usbd_hid.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header for usbd_hid.c file.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_HID_H__
#define __USBD_HID_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "usbd_core.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
typedef struct {
    void (*get_report)(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t **data, uint32_t *len);
    uint8_t (*get_idle)(uint8_t intf, uint8_t report_id);
    uint8_t (*get_protocol)(uint8_t intf);
    void (*set_report)(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint32_t report_len);
    void (*set_idle)(uint8_t intf, uint8_t report_id, uint8_t duration);
    void (*set_protocol)(uint8_t intf, uint8_t protocol);
} usbd_hid_cb_t;

typedef struct {
    const usbd_hid_cb_t *cb;
    usbd_intf_cb_t intf_cb;
} usbd_hid_class_t;

/************************* variable definition *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usb hid callback register
 * @param  cb \ref usbd_hid_cb_t
 * @retval None
 */
extern void usbd_hid_cb_register(usbd_hid_cb_t *cb);
/**
 * @brief  usb hid callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
extern void usbd_hid_cb_unregister(uint8_t intf_index);
/**
 * @brief  get usb hid class interface callback
 * @param  None
 * @retval None
 */
extern usbd_intf_cb_t *usbd_hid_get_inf_cb(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

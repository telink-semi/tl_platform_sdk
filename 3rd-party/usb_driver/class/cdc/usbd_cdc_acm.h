/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\cdc\usbd_cdc_acm.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: please add your description
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_CDC_ACM_H__
#define __USBD_CDC_ACM_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "usbd_core.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
/* Line coding structure for GET_LINE_CODING / SET_LINE_CODING class requests*/
/* Format of the data returned when a GetLineCoding request is received */
/* (usbcdc11.pdf, 6.2.13) */
typedef struct {
    uint32_t bitrate;   /* Data terminal rate in bits per second */
    uint8_t format;     /* Number of stop bits */
    uint8_t paritytype; /* Parity bit type */
    uint8_t datatbits;  /* Number of data bits */
} cdc_line_coding_t;

typedef struct {
    void (*set_line_coding)(cdc_line_coding_t line_coding);
    void (*get_line_coding)(cdc_line_coding_t *line_coding);
    void (*set_dtr)(uint8_t dtr);
    void (*set_rts)(uint8_t rts);
    void (*send_break)(uint8_t intf);
} usbd_acm_cb_t;

typedef struct {
    const usbd_acm_cb_t *cb;
    usbd_intf_cb_t intf_cb;
} usbd_acm_class_t;

/************************* variable definition *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usbd acm callback register
 * @param  cb \ref usbd_acm_cb_t
 * @retval None
 */
extern void usbd_acm_cb_register(usbd_acm_cb_t *cb);
/**
 * @brief  usbd acm callback unregister
 * @param  intf_index: interface index
 * @retval None
 */
extern void usbd_acm_cb_unregister(uint8_t intf_index);
/**
 * @brief  get usbd cdc class interface callback
 * @param  None
 * @retval None
 */
extern usbd_intf_cb_t *usbd_acm_get_inf_cb(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

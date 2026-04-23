/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\drv_dcd.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header file for usb.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USB_DCD_H__
#define __USB_DCD_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "usb_conf.h"
#include "usb_regs.h"
#include "usb_defines.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
typedef usb_status_t (*ep_callback_t)(uint8_t ep, uint32_t len);

/* Endpoint state */
typedef struct {
    uint16_t maxpacket; /* Endpoint max packet size */
    uint8_t type;       /* Endpoint type */
    uint8_t res_1;
    /* transaction level variables */
    uint8_t *xfer_buff;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
    /* endpoint callback */
    ep_callback_t cb;
} usb_otg_ep_t;

typedef struct {
    uint32_t stall_flag;
    /** Setup packet */
    __attribute__((aligned(32))) usb_setup_req_t rx_setup_packet;
    usb_otg_ep_t in_ep[USB_CFG_DEVICE_EP_NUM];  /*!< IN endpoint parameters*/
    usb_otg_ep_t out_ep[USB_CFG_DEVICE_EP_NUM]; /*!< OUT endpoint parameters */
} usb_dcd_t;

typedef struct {
    /** token test */
    uint8_t token_flag;
    uint8_t stall_flag;
    uint16_t cnt;
} usb_dcd_token_t;

typedef struct {
    void (*dataout_stage)(usb_setup_req_t *req, uint32_t len);
    void (*datain_stage)(usb_setup_req_t *req, uint32_t len);
    void (*setup_stage)(usb_setup_req_t *req);
    void (*reset)(void);
    void (*sof)(void);
    void (*suspend)(void);
    void (*resume)(void);
    void (*dev_connected)(void);
    void (*dev_disconnected)(void);
} usb_dcd_int_cb_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usb endpoint register
 * @param  ep_addr : endpoint addr
 * @param  cb : \ref ep_callback_t
 * @retval None
 */
extern void usbd_endpoint_register(uint8_t ep_addr, ep_callback_t cb);
/**
 * @brief  usb endpoint unregister
 * @param  ep_addr : endpoint addr
 * @retval None
 */
extern void usbd_endpoint_unregister(uint8_t ep_addr);
/**
* @brief  usbd_core_init: Initializes the USB_OTG controller registers
*         for device mode
* @param  None
* @retval status
*/
extern void usbd_core_init(void);
/**
* @brief  usb device init
*         Initializes the device stack and load the class driver
* @param  None
* @retval None
*/
extern void usb_dc_init(void);
/**
* @brief  usb device deinit
*         Initializes the device stack and load the class driver
* @param  None
* @retval None
*/
extern void usb_dc_deinit(void);
/**
* @brief  Transmit data over USB
* @param epnum: endpoint address
* @param pbuf: pointer to Tx buffer
* @param buf_len: data length
* status
*/
extern usb_status_t usbd_ep_tx(uint8_t epnum, uint8_t *pbuf, uint32_t len);
/**
* @brief  usbd_ep_preparerx
* @param epnum: endpoint address
* @param pbuf: pointer to Rx buffer
* @param buf_len: data length
* status
*/
extern usb_status_t usbd_ep_preparerx(uint8_t epnum, uint8_t *pbuf, uint32_t len);
/**
* @brief  usbd_set_ep_stall : Set the EP STALL
* @param  epnum : endpoint address
* @retval status
*/
extern void usbd_set_ep_stall(uint8_t epnum);
/**
* @brief  Clear the EP STALL
* @param  epnum : endpoint address
* @retval status
*/
extern void usbd_clear_ep_stall(uint8_t epnum);
/**
* @brief  get the EP stall status
* @param  epnum : endpoint address
* @retval status
*/
extern usb_status_t usbd_ep_is_stalled(uint8_t epnum);
/**
* @brief  This Function set USB device address
* @param  address: new device address
* status
*/
extern void usbd_set_device_address(uint8_t addr);
/**
* @brief  Disconnect device (disable internal pull-up)
* @param  None
* @retval None
*/
extern void usbd_disconnect(void);
/**
* @brief  set an EP
* @param  epnum : Endpoint
* status
*/
extern usb_status_t usbd_enable_ep(uint8_t epnum);
/**
* @brief  Configure an EP
* @param  epnum : Endpoint
* @param  ep_mps : Endpoint maxpacket
* @param  ep_type : Endpoint type
* status
*/
extern usb_status_t usbd_open_endpoint(uint8_t epnum, uint16_t ep_mps, uint8_t ep_type);
/**
* @brief  called when an EP is disabled
* @param  epnum: endpoint address
* status
*/
extern usb_status_t usbd_close_endpoint(uint8_t epnum);
/**
* @brief  usbd_isr_handler
*         handles all USB Interrupts
* @param  None
* @retval None
*/
extern void usbd_isr_handler(void);
/**
* @brief  active remote wakeup signalling
* @param  low_power
* @retval None
*/
extern void usbd_active_remotewakeup(uint8_t low_power);

#ifdef USB_CFG_DEVICE_TEST_ENABLE
/**
 * @brief Usb execute test mode
 * @param test_mode: usb test mode
 * @retval None
 */
void usbd_set_test_mode(uint8_t test_mode);
#endif
/**
* @brief  get endpoint maxpacket
* @param  epnum : end point number
* @retval : maxpacket
*/
extern uint16_t usbd_get_ep_mps(uint8_t epnum);
/**
* @brief  last packet is MPS multiple, so send ZLP packet
* @param  epnum : end point number
* @param  len : data length
* @retval : tx status
*/
extern usb_status_t usbd_bulk_send_zlp(uint8_t epnum, uint32_t len);
/**
 * @brief  get usbd interface callback
 * @param  None
 * @retval address of usbd_int_fops
 */
extern usb_dcd_int_cb_t *usbd_get_int_fops(void);

/**
* @brief  configures EPO to receive SETUP packets
* @param  psetup: device instance
* @retval None
*/
extern void usbd_read_setup_packet(void);

/**
* @brief  get the Transfer Completed Interrupt (XferCompl)
* @param  None
* @retval status
*/
extern uint8_t usbd_get_ep0_XferCompl(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __USB_CORE_H__ */

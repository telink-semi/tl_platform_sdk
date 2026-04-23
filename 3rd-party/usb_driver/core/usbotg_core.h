/*
 * @FilePath: \epm_driver\third_party\usb_driver\core\usbotg_core.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBOTG_CORE__
#define __USBOTG_CORE__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "drv_otg.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
typedef struct {
    uint32_t (*usr_usbd_init)(void);
    uint32_t (*usr_usbd_app)(void);
    uint32_t (*usr_usbh_init)(void);
    uint32_t (*usr_usbh_app)(void);
} usb_otg_cb_t;

typedef struct {
    uint8_t mode;
    usb_otg_cb_t cb;
} usb_otg_core_t;

/************************* variable definition *******************************/

/**************************** function declear *******************************/

/********************** function implementation ******************************/
/**
 * @brief  usb class interface register
 * @param  cb \ref usbd_hid_cb_t
 * @retval None
 */
extern void usb_otg_cb_register(usb_otg_cb_t *cb);
/**
 * @brief  usb class interface unregister
 * @param  None
 * @retval None
 */
extern void usb_otg_cb_unregister(void);
/**
* @brief  otg init
*
* @param  none
* @return none
* @note   none
*/
extern void usb_otg_init(void);
/**
* @brief  handles the Connector ID Status Change Interrupt
*         USB Host core main state machine process
* @param  None
* @retval None
*/
extern void usb_otg_process(void);

#endif

#ifdef __cplusplus
}
#endif

#endif //__USB_OTG_CORE__

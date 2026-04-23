/*
 * @FilePath: \epm_driver\third_party\usb_driver\core\usbotg_core.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "usbotg_core.h"
#include "drv_usb_glue.h"
#include "usbd_core.h"
#if defined(USB_CFG_USE_HOST_MODE)
#include "usbh_core.h"
#endif

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE)

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/************************* variable definition *******************************/
USB_MEM_ALIGNX usb_otg_core_t usb_otg_core;

/**************************** function declear *******************************/

/********************** function implementation ******************************/
/**
 * @brief  usb class interface register
 * @param  cb \ref usbd_hid_cb_t
 * @retval None
 */
void usb_otg_cb_register(usb_otg_cb_t *cb)
{
    usb_otg_core.cb.usr_usbd_app = cb->usr_usbd_app;
    usb_otg_core.cb.usr_usbd_init = cb->usr_usbd_init;
    usb_otg_core.cb.usr_usbh_app = cb->usr_usbh_app;
    usb_otg_core.cb.usr_usbh_init = cb->usr_usbh_init;
}

/**
 * @brief  usb class interface unregister
 * @param  None
 * @retval None
 */
void usb_otg_cb_unregister(void)
{
    usb_otg_core.cb.usr_usbd_app = NULL;
    usb_otg_core.cb.usr_usbd_init = NULL;
    usb_otg_core.cb.usr_usbh_app = NULL;
    usb_otg_core.cb.usr_usbh_init = NULL;
}

/**
* @brief  otg init
*
* @param  none
* @return none
* @note   none
*/
void usb_otg_init(void)
{
    usb_low_level_init();

    usb_otg_set_currentmode(USB_OTG_MODE);

    usb_otg_core.mode = USB_OTG_MODE;
    usb_otg_enable_int();
}

/**
* @brief  handles the Connector ID Status Change Interrupt
*         USB Host core main state machine process
* @param  None
* @retval None
*/
void usb_otg_process(void)
{
    static uint8_t conidsts = USB_OTG_MODE;
    uint8_t idsts = usb_otg_getconidsts();

    if (idsts != conidsts) {
        conidsts = idsts;
        switch (conidsts) {
        case USB_MODEA:
            USB_LOG_INFO("MODEA(USB Host) \r\n");
            if (usb_otg_core.mode == USB_DEVICE_MODE) {
                usbd_disconnect();
                usbd_deinit();
            }
            /* host init */
            if (usb_otg_core.cb.usr_usbh_init != NULL) {
                usb_otg_core.mode = USB_HOST_MODE;
                usb_otg_core.cb.usr_usbh_init();
            }
            break;

        case USB_MODEB:
            USB_LOG_INFO("MODEB(USB Device) \r\n");
            if (usb_otg_core.mode == USB_HOST_MODE) {
                usb_drive_vbus(0);
                usbh_deinit();
            }
            /* device init */
            if (usb_otg_core.cb.usr_usbd_init != NULL) {
                usb_otg_core.mode = USB_DEVICE_MODE;
                usb_otg_core.cb.usr_usbd_init();
            }
            break;
        }
    }

    switch (usb_otg_core.mode) {
    case USB_OTG_MODE:
        /* app */
        break;

    case USB_DEVICE_MODE:
        /* app */
        if (usb_otg_core.cb.usr_usbd_app != NULL) {
            usb_otg_core.cb.usr_usbd_app();
        }
        break;

    case USB_HOST_MODE:
        /* app */
        if (usb_otg_core.cb.usr_usbh_app != NULL) {
            usb_otg_core.cb.usr_usbh_app();
        }
        break;
    }
}

#endif
#endif

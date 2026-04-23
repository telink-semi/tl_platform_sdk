/*
 * @FilePath: \epm_driver\third_party\usb_driver\core\usbd_core.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:54
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_CORE_H__
#define __USBD_CORE_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "drv_dcd.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define STR_DESC_ID_LANGID    (0x00)
#define STR_DESC_ID_MFC       (0x01)
#define STR_DESC_ID_PRODUCT   (0x02)
#define STR_DESC_ID_SERIALNUM (0x03)
#define STR_DESC_ID_INF_CFG   (0x04)
#define STR_DESC_ID_INTERFACE (0x05)
//usb audio class string Descriptor
#define STR_DESC_ID_IN_STREARM     (0x06)
#define STR_DESC_ID_OUT_STREARM    (0x07)
#define STR_DESC_ID_IN_TERMINAL    (0x08)
#define STR_DESC_ID_OUT_TERMINAL   (0x09)
#define STR_DESC_ID_FEATUREUNIT    (0x0a)
#define STR_DESC_ID_PROCESSINGUNIT (0x0b)
#define STR_DESC_ID_EXTENSIONUNIT  (0x0c)
#define STR_DESC_ID_CLOCKSOURCE    (0x0D)

/**************************** type definition ********************************/
typedef enum {
    DESCR_ID_DEVICE = 0,
    DESCR_ID_CONFIG,
    DESCR_ID_OTHER_SPEED_CFG,
    DESCR_ID_DEVQLF,
    DESCR_ID_HID_REPORT,
    DESCR_ID_LANGID_STR,
    DESCR_ID_MANUFACTURER_STR,
    DESCR_ID_PRODUCT_STR,
    DESCR_ID_SERIAL_STR,
    DESCR_ID_CFG_STR,
    DESCR_ID_INTERFACE_STR,
    DESCR_ID_IN_STREARM_STR,
    DESCR_ID_OUT_STREARM_STR,
    DESCR_ID_IN_TERMINAL_STR,
    DESCR_ID_OUT_TERMINAL_STR,
    DESCR_ID_FEATUREUNIT_STR,
    DESCR_ID_PROCESSINGUNIT_STR,
    DESCR_ID_EXTENSIONUNIT_STR,
    DESCR_ID_CLOCKSOURCE_STR,
} usbd_descr_sel_t;

typedef enum {
    USBD_EVENT_RESET = 0,      /** USB reset */
    USBD_EVENT_CONFIGURED = 1, /** USB configuration done */
} usbd_event_t;

typedef usb_status_t (*notify_cb_t)(usbd_event_t event);

typedef struct {
    usb_status_t (*reset)(void);
    usb_status_t (*sof)(void);
    usb_status_t (*connected)(void);
    usb_status_t (*disconnected)(void);
    usb_status_t (*suspend)(void);
    usb_status_t (*resume)(void);
    usb_status_t (*configured)(void);
    usb_status_t (*open)(uint16_t intf_num, uint16_t alt_set);
    usb_status_t (*close)(uint16_t intf_num, uint16_t alt_set);
    usb_status_t (*set_remote_wakeup)(void);
    usb_status_t (*clear_remote_wakeup)(void);
    usb_status_t (*init)(void);
    usb_status_t (*deinit)(void);
} usbd_usr_cb_t;

typedef struct {
    uint32_t len;
    uint8_t *descr;
} usb_descr_t;

typedef struct {
    usb_descr_t device_descriptor;
    usb_descr_t lang_id_str_descriptor;
    usb_descr_t manufacturer_str_descriptor;
    usb_descr_t product_str_descriptor;
    usb_descr_t serial_str_descriptor;
    usb_descr_t configuration_str_descriptor;
    usb_descr_t interface_str_descriptor;
    usb_descr_t in_strearm_str_descriptor;
    usb_descr_t out_strearm_str_descriptor;
    usb_descr_t in_terminal_str_descriptor;
    usb_descr_t out_terminal_str_descriptor;
    usb_descr_t featureunit_str_descriptor;
    usb_descr_t processingunit_str_descriptor;
    usb_descr_t extensionunit_str_descriptor;
    usb_descr_t clocksource_str_descriptor;
    usb_descr_t config_descriptor;
    usb_descr_t other_config_descriptor;
    usb_descr_t devqlf_descriptor;
    usb_descr_t hid_report_descriptor;
} usbd_descr_t;

typedef struct {
    usb_status_t (*interface_cb)(usb_setup_req_t *req, uint8_t **data, uint32_t *len);
    usb_status_t (*endpoint_cb)(usb_setup_req_t *req, uint8_t **data, uint32_t *len);
    usb_status_t (*vendor_cb)(usb_setup_req_t *req, uint8_t **data, uint32_t *len);
} usbd_intf_cb_t;

typedef struct {
    usbd_intf_cb_t cb[16];
    uint32_t amount;
} class_intf_t;

typedef struct {
    /** Currently selected configuration */
    volatile uint8_t config;
    uint8_t address;
    uint8_t connection_status;
    uint8_t remote_wakeup_support;
    uint8_t remote_wakeup_enabled;
    uint8_t is_suspend;
    uint8_t altset;
    uint8_t res_1;
    /** Zero length packet flag of control transfer */
    uint8_t zlp_flag;
    uint8_t test_mode;
    uint16_t res_2;
    /** Currently selected configuration */
    uint16_t self_powered;
    uint16_t low_power;
    /** Pointer to data buffer */
    USB_MEM_ALIGNX uint8_t *ep0_buf;
    /** Remaining bytes in buffer */
    uint32_t ep0_buf_residue;
    /** Total length of control transfer */
    uint32_t ep0_buf_size;

    /** Buffer used for storing standard, class and vendor request data */
    USB_MEM_ALIGNX uint8_t data_buff[USB_CFG_DEVICE_REQ_BUF_LEN];

    class_intf_t class_intf;
    usbd_usr_cb_t *user_cb;
    notify_cb_t class_event_cb;
    usbd_descr_t descr;
} usbd_core_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usb device handle init
 * @param  None
 * @retval None
 */
extern void usbd_handle_init(void);
/**
 * @brief  usb device init
 * @param  None
 * @retval None
 */
extern void usbd_init(void);
/**
 * @brief  usb device deinit
 * @param  None
 * @retval None
 */
extern void usbd_deinit(void);
/**
 * @brief  usb class interface register
 * @param  cb \ref usbd_hid_cb_t
 * @param  num: endpoint number
 * @retval None
 */
extern void usbd_class_intf_register(usbd_intf_cb_t *cb, uint8_t num);
/**
 * @brief  usb class interface unregister
 * @param  num: interface index
 * @retval None
 */
extern void usbd_class_intf_unregister(uint8_t num);
/**
 * @brief  usb user cb register
 * @param  cb : \ref usbd_usr_cb_t
 * @retval None
 */
extern void usbd_user_cb_register(usbd_usr_cb_t *cb);
/**
 * @brief  usb user cb unregister
 * @param  None
 * @retval None
 */
extern void usbd_user_cb_unregister(void);
/**
 * @brief  usb notify register
 * @param  cb : \ref notify_cb_t
 * @retval None
 */
extern void usbd_notify_register(notify_cb_t cb);
/**
 * @brief  usb notify unregister
 * @param  param
 * @retval None
 */
extern void usbd_notify_unregister(void);
/**
 * @brief  usb device descriptor register
 * @param  sel : \ref usbd_descr_sel_t
 * @param  descr : device descriptor
 * @param  len : Length of device descriptor
 * @retval None
 */
extern void usbd_desc_register(usbd_descr_sel_t sel, uint8_t *descr, uint16_t len);
/**
 * @brief  usb device descriptor unregister
 * @param  sel : \ref usbd_descr_sel_t
 * @retval None
 */
extern void usbd_desc_unregister(usbd_descr_sel_t sel);
/**
* @brief  last packet is MPS multiple, so send ZLP packet
* @param  None
* @retval : suspend status
*/
extern uint8_t usb_device_is_suspend(void);
/**
* @brief  get init status
* @param  None
* @retval : init status
*/
uint8_t usb_device_is_init(void);
/**
* @brief  get wakeup status
* @param  None
* @retval : wakeup status
*/
extern usb_status_t usbd_wakeup_host(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CORE_H */

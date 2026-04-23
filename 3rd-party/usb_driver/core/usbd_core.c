/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This driver is based on the 1.4.1 version of core/usbd_core.c
 * but has been rewritten to be easier to read and use.
 */

/**************************** include header *********************************/
#include "usbd_core.h"
#include "drv_usb_glue.h"
#ifdef USB_CFG_USE_OTG_MODE
#include "usbotg_core.h"
#endif

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/

/**************************** function declear *******************************/
static void usbd_class_event_handler(usbd_event_t event);

static void usbd_ep0_datain_stage(usb_setup_req_t *req, uint32_t len);
static void usbd_ep0_dataout_stage(usb_setup_req_t *req, uint32_t len);
static void usbd_ep0_setup_stage(usb_setup_req_t *req);
static void usbd_reset_handler(void);
static void usbd_sof_handler(void);
static void usbd_suspend_handler(void);
static void usbd_resume_handler(void);
static void usbd_connect_handler(void);
static void usbd_disconnect_handler(void);

/**************************** type definition ********************************/

/************************* variable definition *******************************/
USB_MEM_ALIGNX usbd_core_t usb_dev_core;

/********************** function implementation ******************************/
/**
 * @brief  usb device handle init
 * @param  None
 * @retval None
 */
void usbd_handle_init(void)
{
    memset((usbd_core_t *)((unsigned int)(&usb_dev_core)), 0, sizeof(usbd_core_t));
}

/**
 * @brief  usb device init
 * @param  None
 * @retval None
 */
void usbd_init(void)
{
    /* Init call back */
    usb_dcd_int_cb_t *int_fops = usbd_get_int_fops();
    int_fops->datain_stage = &usbd_ep0_datain_stage;
    int_fops->dataout_stage = &usbd_ep0_dataout_stage;
    int_fops->setup_stage = &usbd_ep0_setup_stage;
    int_fops->reset = &usbd_reset_handler;
    int_fops->sof = &usbd_sof_handler;
    int_fops->suspend = &usbd_suspend_handler;
    int_fops->resume = &usbd_resume_handler;
    int_fops->dev_connected = &usbd_connect_handler;
    int_fops->dev_disconnected = &usbd_disconnect_handler;

    /* set USB OTG core params */
    /* initialize device cfg following its address */
#ifdef USB_CFG_LOW_PWR_MGMT_SUPPORT
    usb_dev_core.low_power = 1;
#endif
    usb_dev_core.address = 0;

    usb_dc_init();
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->init) {
        usb_dev_core.user_cb->init();
    }
}

/**
 * @brief  usb device deinit
 * @param  None
 * @retval None
 */
void usbd_deinit(void)
{
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->deinit) {
        usb_dev_core.user_cb->deinit();
    }
    usb_dc_deinit();
}

/**
 * @brief  usb class interface register
 * @param  cb \ref usbd_hid_cb_t
 * @retval None
 */
void usbd_class_intf_register(usbd_intf_cb_t *cb, uint8_t num)
{
    usb_dev_core.class_intf.cb[num].interface_cb = cb->interface_cb;
    usb_dev_core.class_intf.cb[num].endpoint_cb = cb->endpoint_cb;
    usb_dev_core.class_intf.cb[num].vendor_cb = cb->vendor_cb;
    usb_dev_core.class_intf.amount++;
}

/**
 * @brief  usb class interface unregister
 * @param  num: interface index
 * @retval None
 */
void usbd_class_intf_unregister(uint8_t num)
{
    usb_dev_core.class_intf.cb[num].interface_cb = NULL;
    usb_dev_core.class_intf.cb[num].endpoint_cb = NULL;
    usb_dev_core.class_intf.cb[num].vendor_cb = NULL;
    if (usb_dev_core.class_intf.amount) {
        usb_dev_core.class_intf.amount--;
    }
}

/**
 * @brief  usb event register
 * @param  cb : \ref usbd_usr_cb_t
 * @retval None
 */
void usbd_user_cb_register(usbd_usr_cb_t *cb)
{
    usb_dev_core.user_cb = cb;
}

/**
 * @brief  usb event unregister
 * @param  None
 * @retval None
 */
void usbd_user_cb_unregister(void)
{
    usb_dev_core.user_cb = NULL;
}

/**
 * @brief  usb notify register
 * @param  cb : \ref notify_cb_t
 * @retval None
 */
void usbd_notify_register(notify_cb_t cb)
{
    usb_dev_core.class_event_cb = cb;
}

/**
 * @brief  usb notify unregister
 * @param  None
 * @retval None
 */
void usbd_notify_unregister(void)
{
    usb_dev_core.class_event_cb = NULL;
}

/**
 * @brief  usb device descriptor register
 * @param  sel : \ref usbd_descr_sel_t
 * @param  descr : device descriptor
 * @param  len : Length of device descriptor
 * @retval None
 */
void usbd_desc_register(usbd_descr_sel_t sel, uint8_t *descr, uint16_t len)
{
    switch ((uint16_t)sel) {
    case DESCR_ID_DEVICE:
        usb_dev_core.descr.device_descriptor.len = len;
        usb_dev_core.descr.device_descriptor.descr = descr;
        break;

    case DESCR_ID_LANGID_STR:
        usb_dev_core.descr.lang_id_str_descriptor.len = len;
        usb_dev_core.descr.lang_id_str_descriptor.descr = descr;
        break;

    case DESCR_ID_MANUFACTURER_STR:
        usb_dev_core.descr.manufacturer_str_descriptor.len = len;
        usb_dev_core.descr.manufacturer_str_descriptor.descr = descr;
        break;

    case DESCR_ID_PRODUCT_STR:
        usb_dev_core.descr.product_str_descriptor.len = len;
        usb_dev_core.descr.product_str_descriptor.descr = descr;
        break;

    case DESCR_ID_SERIAL_STR:
        usb_dev_core.descr.serial_str_descriptor.len = len;
        usb_dev_core.descr.serial_str_descriptor.descr = descr;
        break;

    case DESCR_ID_CFG_STR:
        usb_dev_core.descr.configuration_str_descriptor.len = len;
        usb_dev_core.descr.configuration_str_descriptor.descr = descr;
        break;

    case DESCR_ID_INTERFACE_STR:
        usb_dev_core.descr.interface_str_descriptor.len = len;
        usb_dev_core.descr.interface_str_descriptor.descr = descr;
        break;

    case DESCR_ID_IN_STREARM_STR:
        usb_dev_core.descr.in_strearm_str_descriptor.len = len;
        usb_dev_core.descr.in_strearm_str_descriptor.descr = descr;
        break;

    case DESCR_ID_OUT_STREARM_STR:
        usb_dev_core.descr.out_strearm_str_descriptor.len = len;
        usb_dev_core.descr.out_strearm_str_descriptor.descr = descr;
        break;

    case DESCR_ID_IN_TERMINAL_STR:
        usb_dev_core.descr.in_terminal_str_descriptor.len = len;
        usb_dev_core.descr.in_terminal_str_descriptor.descr = descr;
        break;

    case DESCR_ID_OUT_TERMINAL_STR:
        usb_dev_core.descr.out_terminal_str_descriptor.len = len;
        usb_dev_core.descr.out_terminal_str_descriptor.descr = descr;
        break;

    case DESCR_ID_FEATUREUNIT_STR:
        usb_dev_core.descr.featureunit_str_descriptor.len = len;
        usb_dev_core.descr.featureunit_str_descriptor.descr = descr;
        break;

    case DESCR_ID_PROCESSINGUNIT_STR:
        usb_dev_core.descr.processingunit_str_descriptor.len = len;
        usb_dev_core.descr.processingunit_str_descriptor.descr = descr;
        break;

    case DESCR_ID_EXTENSIONUNIT_STR:
        usb_dev_core.descr.extensionunit_str_descriptor.len = len;
        usb_dev_core.descr.extensionunit_str_descriptor.descr = descr;
        break;

    case DESCR_ID_CLOCKSOURCE_STR:
        usb_dev_core.descr.clocksource_str_descriptor.len = len;
        usb_dev_core.descr.clocksource_str_descriptor.descr = descr;
        break;

    case DESCR_ID_CONFIG:
        usb_dev_core.descr.config_descriptor.len = len;
        usb_dev_core.descr.config_descriptor.descr = descr;
        break;

    case DESCR_ID_OTHER_SPEED_CFG:
        usb_dev_core.descr.other_config_descriptor.len = len;
        usb_dev_core.descr.other_config_descriptor.descr = descr;
        break;

    case DESCR_ID_DEVQLF:
        usb_dev_core.descr.devqlf_descriptor.len = len;
        usb_dev_core.descr.devqlf_descriptor.descr = descr;
        break;

    case DESCR_ID_HID_REPORT:
        usb_dev_core.descr.hid_report_descriptor.len = len;
        usb_dev_core.descr.hid_report_descriptor.descr = descr;
        break;
    }
}

/**
 * @brief  usb device descriptor unregister
 * @param  sel : \ref usbd_descr_sel_t
 * @retval None
 */
void usbd_desc_unregister(usbd_descr_sel_t sel)
{
    switch ((uint16_t)sel) {
    case DESCR_ID_DEVICE:
        usb_dev_core.descr.device_descriptor.len = 0;
        usb_dev_core.descr.device_descriptor.descr = NULL;
        break;

    case DESCR_ID_LANGID_STR:
        usb_dev_core.descr.lang_id_str_descriptor.len = 0;
        usb_dev_core.descr.lang_id_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_MANUFACTURER_STR:
        usb_dev_core.descr.manufacturer_str_descriptor.len = 0;
        usb_dev_core.descr.manufacturer_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_PRODUCT_STR:
        usb_dev_core.descr.product_str_descriptor.len = 0;
        usb_dev_core.descr.product_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_SERIAL_STR:
        usb_dev_core.descr.serial_str_descriptor.len = 0;
        usb_dev_core.descr.serial_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_CFG_STR:
        usb_dev_core.descr.configuration_str_descriptor.len = 0;
        usb_dev_core.descr.configuration_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_INTERFACE_STR:
        usb_dev_core.descr.interface_str_descriptor.len = 0;
        usb_dev_core.descr.interface_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_IN_STREARM_STR:
        usb_dev_core.descr.in_strearm_str_descriptor.len = 0;
        usb_dev_core.descr.in_strearm_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_OUT_STREARM_STR:
        usb_dev_core.descr.out_strearm_str_descriptor.len = 0;
        usb_dev_core.descr.out_strearm_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_IN_TERMINAL_STR:
        usb_dev_core.descr.in_terminal_str_descriptor.len = 0;
        usb_dev_core.descr.in_terminal_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_OUT_TERMINAL_STR:
        usb_dev_core.descr.out_terminal_str_descriptor.len = 0;
        usb_dev_core.descr.out_terminal_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_FEATUREUNIT_STR:
        usb_dev_core.descr.featureunit_str_descriptor.len = 0;
        usb_dev_core.descr.featureunit_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_PROCESSINGUNIT_STR:
        usb_dev_core.descr.processingunit_str_descriptor.len = 0;
        usb_dev_core.descr.processingunit_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_EXTENSIONUNIT_STR:
        usb_dev_core.descr.extensionunit_str_descriptor.len = 0;
        usb_dev_core.descr.extensionunit_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_CLOCKSOURCE_STR:
        usb_dev_core.descr.clocksource_str_descriptor.len = 0;
        usb_dev_core.descr.clocksource_str_descriptor.descr = NULL;
        break;

    case DESCR_ID_CONFIG:
        usb_dev_core.descr.config_descriptor.len = 0;
        usb_dev_core.descr.config_descriptor.descr = NULL;
        break;

    case DESCR_ID_OTHER_SPEED_CFG:
        usb_dev_core.descr.other_config_descriptor.len = 0;
        usb_dev_core.descr.other_config_descriptor.descr = NULL;
        break;

    case DESCR_ID_DEVQLF:
        usb_dev_core.descr.devqlf_descriptor.len = 0;
        usb_dev_core.descr.devqlf_descriptor.descr = NULL;
        break;
    }
}

/**
 * @brief  usbd_get_device_descr
 *         Convert Ascii string into unicode one
 * @param  sel : \ref usbd_descr_sel_t
 * @param  length : descriptor length
 * @retval status
 */
static usb_status_t usbd_get_device_descr(usbd_descr_sel_t sel, uint8_t **data, uint32_t *len)
{
    if (0 == *len) {
        return USB_ERROR;
    }
    switch ((uint16_t)sel) {
    case DESCR_ID_DEVICE:
        *len = usb_dev_core.descr.device_descriptor.len;
        *data = (uint8_t *)usb_dev_core.descr.device_descriptor.descr;
        break;

    case DESCR_ID_LANGID_STR:
        *len = usb_dev_core.descr.lang_id_str_descriptor.len;
        *data = usb_dev_core.descr.lang_id_str_descriptor.descr;
        break;

    case DESCR_ID_MANUFACTURER_STR:
        *len = usb_dev_core.descr.manufacturer_str_descriptor.len;
        *data = usb_dev_core.descr.manufacturer_str_descriptor.descr;
        break;

    case DESCR_ID_PRODUCT_STR:
        *len = usb_dev_core.descr.product_str_descriptor.len;
        *data = usb_dev_core.descr.product_str_descriptor.descr;
        break;

    case DESCR_ID_SERIAL_STR:
        *len = usb_dev_core.descr.serial_str_descriptor.len;
        *data = usb_dev_core.descr.serial_str_descriptor.descr;
        break;

    case DESCR_ID_CFG_STR:
        *len = usb_dev_core.descr.configuration_str_descriptor.len;
        *data = usb_dev_core.descr.configuration_str_descriptor.descr;
        break;

    case DESCR_ID_INTERFACE_STR:
        *len = usb_dev_core.descr.interface_str_descriptor.len;
        *data = usb_dev_core.descr.interface_str_descriptor.descr;
        break;

    case DESCR_ID_IN_STREARM_STR:
        *len = usb_dev_core.descr.in_strearm_str_descriptor.len;
        *data = usb_dev_core.descr.in_strearm_str_descriptor.descr;
        break;

    case DESCR_ID_OUT_STREARM_STR:
        *len = usb_dev_core.descr.out_strearm_str_descriptor.len;
        *data = usb_dev_core.descr.out_strearm_str_descriptor.descr;
        break;

    case DESCR_ID_IN_TERMINAL_STR:
        *len = usb_dev_core.descr.in_terminal_str_descriptor.len;
        *data = usb_dev_core.descr.in_terminal_str_descriptor.descr;
        break;

    case DESCR_ID_OUT_TERMINAL_STR:
        *len = usb_dev_core.descr.out_terminal_str_descriptor.len;
        *data = usb_dev_core.descr.out_terminal_str_descriptor.descr;
        break;

    case DESCR_ID_FEATUREUNIT_STR:
        *len = usb_dev_core.descr.featureunit_str_descriptor.len;
        *data = usb_dev_core.descr.featureunit_str_descriptor.descr;
        break;

    case DESCR_ID_PROCESSINGUNIT_STR:
        *len = usb_dev_core.descr.processingunit_str_descriptor.len;
        *data = usb_dev_core.descr.processingunit_str_descriptor.descr;
        break;

    case DESCR_ID_EXTENSIONUNIT_STR:
        *len = usb_dev_core.descr.extensionunit_str_descriptor.len;
        *data = usb_dev_core.descr.extensionunit_str_descriptor.descr;
        break;

    case DESCR_ID_CLOCKSOURCE_STR:
        *len = usb_dev_core.descr.clocksource_str_descriptor.len;
        *data = usb_dev_core.descr.clocksource_str_descriptor.descr;
        break;

    case DESCR_ID_CONFIG:
        *len = usb_dev_core.descr.config_descriptor.len;
        *data = usb_dev_core.descr.config_descriptor.descr;
        break;

    case DESCR_ID_OTHER_SPEED_CFG:
        *len = usb_dev_core.descr.other_config_descriptor.len;
        *data = usb_dev_core.descr.other_config_descriptor.descr;
        break;

    case DESCR_ID_DEVQLF:
        *len = usb_dev_core.descr.devqlf_descriptor.len;
        *data = usb_dev_core.descr.devqlf_descriptor.descr;
        break;
    }
    if (NULL == *data) {
        return USB_ERROR;
    }
    return USB_OK;
}

/**
* @brief  usbd_get_descriptor
*         Handle Get Descriptor requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_get_descriptor(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    usb_status_t ret = USB_OK;

    switch (req->wValue >> 8) {
    case USB_DESC_TYPE_DEVICE:
        ret = usbd_get_device_descr(DESCR_ID_DEVICE, data, len);
        break;

    case USB_DESC_TYPE_CONFIGURATION:
        ret = usbd_get_device_descr(DESCR_ID_CONFIG, data, len);
        usb_dev_core.self_powered = ((*data)[7] & USB_CONFIG_POWERED_MASK) ? 1 : 0;
        usb_dev_core.remote_wakeup_support = ((*data)[7] & USB_CONFIG_REMOTE_WAKEUP) ? true : false;
        break;

    case USB_DESC_TYPE_STRING:
        switch ((uint8_t)(req->wValue)) {
        case STR_DESC_ID_LANGID:
            ret = usbd_get_device_descr(DESCR_ID_LANGID_STR, data, len);
            break;

        case STR_DESC_ID_MFC:
            ret = usbd_get_device_descr(DESCR_ID_MANUFACTURER_STR, data, len);
            break;

        case STR_DESC_ID_PRODUCT:
            ret = usbd_get_device_descr(DESCR_ID_PRODUCT_STR, data, len);
            break;

        case STR_DESC_ID_SERIALNUM:
            ret = usbd_get_device_descr(DESCR_ID_SERIAL_STR, data, len);
            break;

        case STR_DESC_ID_INF_CFG:
            ret = usbd_get_device_descr(DESCR_ID_CFG_STR, data, len);
            break;

        case STR_DESC_ID_INTERFACE:
            ret = usbd_get_device_descr(DESCR_ID_INTERFACE_STR, data, len);
            break;

        case STR_DESC_ID_IN_STREARM:
            ret = usbd_get_device_descr(DESCR_ID_IN_STREARM_STR, data, len);
            break;

        case STR_DESC_ID_OUT_STREARM:
            ret = usbd_get_device_descr(DESCR_ID_OUT_STREARM_STR, data, len);
            break;

        case STR_DESC_ID_IN_TERMINAL:
            ret = usbd_get_device_descr(DESCR_ID_IN_TERMINAL_STR, data, len);
            break;

        case STR_DESC_ID_OUT_TERMINAL:
            ret = usbd_get_device_descr(DESCR_ID_OUT_TERMINAL_STR, data, len);
            break;

        case STR_DESC_ID_FEATUREUNIT:
            ret = usbd_get_device_descr(DESCR_ID_FEATUREUNIT_STR, data, len);
            break;

        case STR_DESC_ID_PROCESSINGUNIT:
            ret = usbd_get_device_descr(DESCR_ID_PROCESSINGUNIT_STR, data, len);
            break;

        case STR_DESC_ID_EXTENSIONUNIT:
            ret = usbd_get_device_descr(DESCR_ID_EXTENSIONUNIT_STR, data, len);
            break;

        case STR_DESC_ID_CLOCKSOURCE:
            ret = usbd_get_device_descr(DESCR_ID_CLOCKSOURCE_STR, data, len);
            break;

        default:
            ret = USB_ERROR;
            break;
        }
        break;

    case USB_DESC_TYPE_DEVICE_QUALIFIER:
        ret = usbd_get_device_descr(DESCR_ID_DEVQLF, data, len);
        *len = 0x0A;
        break;

    case USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION:
        ret = usbd_get_device_descr(DESCR_ID_OTHER_SPEED_CFG, data, len);
        break;

    default:
        ret = USB_ERROR;
        break;
    }
    return ret;
}

/**
* @brief  usbd_set_config
*         Handle Set device configuration request
* @param  config_index: config_index Configuration index
* @retval status
*/
static usb_status_t usbd_set_config(uint8_t config_index)
{
    usb_epdesc_t *ep;
    uint32_t descr_len = 0;
    usb_status_t ret = USB_OK;
    uint8_t cur_config = 0xFF;
    uint8_t cur_alt_setting = 0xFF;
    uint32_t current_descr_len = 0;
    uint8_t *pdescr = (uint8_t *)usb_dev_core.descr.config_descriptor.descr;

    while (pdescr[DESC_bLength] != 0U) {
        switch (pdescr[DESC_bDescriptorType]) {
        case USB_DESC_TYPE_INTERFACE:
            cur_alt_setting = pdescr[INTF_DESC_bAlternateSetting];
            break;

        case USB_DESC_TYPE_CONFIGURATION:
            cur_config = pdescr[CONF_DESC_bConfigurationValue];
            if (cur_config == config_index) {
                ret = USB_OK;
                current_descr_len = 0;
                descr_len = (pdescr[CONF_DESC_wTotalLength]) | (pdescr[CONF_DESC_wTotalLength + 1] << 8);
            }
            break;

        case USB_DESC_TYPE_ENDPOINT:
            if ((cur_config != config_index) || (cur_alt_setting != 0)) {
                break;
            }
            ep = (usb_epdesc_t *)pdescr;
            ret = usbd_open_endpoint(ep->bEndpointAddress, ep->wMaxPacketSize, USB_GET_ENDPOINT_TYPE(ep->bmAttributes));
            break;

        default:
            break;
        }

        pdescr += pdescr[DESC_bLength];
        current_descr_len += pdescr[DESC_bLength];
        if (current_descr_len >= descr_len && descr_len) {
            break;
        }
    }

    return ret;
}

/**
* @brief  usbd_set_feature
*         Handle Set device feature request
* @param  req: usb request
* @retval None
*/
static void usbd_set_feature(usb_setup_req_t *req)
{
    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP) {
        usb_dev_core.remote_wakeup_enabled = 1;
        if (usb_dev_core.user_cb && usb_dev_core.user_cb->set_remote_wakeup) {
            usb_dev_core.user_cb->set_remote_wakeup();
        }
    } else if (req->wValue == USB_FEATURE_TEST_MODE) {
#ifdef USB_CFG_DEVICE_TEST_ENABLE
        usb_dev_core.test_mode = USB_HIBYTE(req->wIndex);
#endif
    }
}

/**
* @brief  usbd_clr_feature
*         Handle clear device feature request
* @param  req: usb request
* @retval None
*/
static void usbd_clr_feature(usb_setup_req_t *req)
{
    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP) {
        usb_dev_core.remote_wakeup_enabled = 0;
        if (usb_dev_core.user_cb && usb_dev_core.user_cb->clear_remote_wakeup) {
            usb_dev_core.user_cb->clear_remote_wakeup();
        }
    } else if (req->wValue == USB_FEATURE_TEST_MODE) {
#ifdef USB_CFG_DEVICE_TEST_ENABLE
        usb_dev_core.test_mode = USB_HIBYTE(req->wIndex);
#endif
    }
}

/**
* @brief  usbd_std_device_req
*         Handle standard usb device requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_std_device_req(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    usb_status_t ret = USB_OK;
    uint8_t value = (uint8_t)(req->wValue);

    switch (req->bRequest) {
    case USB_REQ_GET_DESCRIPTOR:
        ret = usbd_get_descriptor(req, data, len);
        break;

    case USB_REQ_SET_ADDRESS:
        usb_dev_core.address = value;
        usbd_set_device_address(usb_dev_core.address);
        *len = 0;
        break;

    case USB_REQ_SET_CONFIGURATION:
        if (value == 0) {
            usb_dev_core.config = 0;
        } else if (usbd_set_config(value) == USB_ERROR) {
            ret = USB_ERROR;
        } else {
            usb_dev_core.config = value;
            usb_dev_core.is_suspend = 0;
            /* Upon set config call usr call back */
            usbd_class_event_handler(USBD_EVENT_CONFIGURED);
            if (usb_dev_core.user_cb && usb_dev_core.user_cb->configured) {
                usb_dev_core.user_cb->configured();
            }
        }
        *len = 0;
        break;

    case USB_REQ_GET_CONFIGURATION:
        (*data)[0] = usb_dev_core.config;
        *len = 1;
        break;

    case USB_REQ_GET_STATUS:
        /* bit 0: self-powered */
        /* bit 1: remote wakeup */
        (*data)[0] = 0x00;
        if (usb_dev_core.self_powered) {
            (*data)[0] |= USB_GET_STS_SELF_POWERED;
        }
        if (usb_dev_core.remote_wakeup_enabled) {
            (*data)[0] |= USB_GET_STS_REMOTE_WAKEUP;
        }
        (*data)[1] = 0x00;
        *len = 2;
        break;

    case USB_REQ_SET_FEATURE:
        usbd_set_feature(req);
        *len = 0;
        break;

    case USB_REQ_CLEAR_FEATURE:
        usbd_clr_feature(req);
        *len = 0;
        break;

    default:
        ret = USB_ERROR;
        break;
    }

    return ret;
}

/**
 * @brief set USB interface
 *
 * @param iface Interface index
 * @param alt_setting  Alternate setting number
 *
 * @return true if successfully configured false if error or unconfigured
 */
static usb_status_t usbd_set_interface(uint8_t iface, uint16_t alt_setting)
{
    usb_epdesc_t *ep;
    usb_epdesc_t *ep_desc;
    uint32_t descr_len = 0;
    uint8_t *if_desc = NULL;
    uint8_t cur_iface = 0xFF;
    usb_status_t ret = USB_ERROR;
    uint8_t cur_alt_setting = 0xFF;
    uint32_t current_descr_len = 0;
    uint8_t *pdescr = (uint8_t *)usb_dev_core.descr.config_descriptor.descr;

    while (pdescr[DESC_bLength] != 0U) {
        switch (pdescr[DESC_bDescriptorType]) {
        case USB_DESC_TYPE_CONFIGURATION:
            current_descr_len = 0;
            descr_len = (pdescr[CONF_DESC_wTotalLength]) | (pdescr[CONF_DESC_wTotalLength + 1] << 8);
            break;

        case USB_DESC_TYPE_INTERFACE:
            /* remember current alternate setting */
            cur_alt_setting = pdescr[INTF_DESC_bAlternateSetting];
            cur_iface = pdescr[INTF_DESC_bInterfaceNumber];
            if (cur_iface == iface && cur_alt_setting == alt_setting) {
                if_desc = (void *)pdescr;
            }
            break;

        case USB_DESC_TYPE_ENDPOINT:
            if (cur_iface == iface) {
                ep_desc = (usb_epdesc_t *)pdescr;
                if (alt_setting == 0) {
                    ret = usbd_close_endpoint(ep_desc->bEndpointAddress);
                    goto find_end;
                } else if (cur_alt_setting == alt_setting) {
                    ep = (usb_epdesc_t *)pdescr;
                    ret = usbd_open_endpoint(ep->bEndpointAddress, ep->wMaxPacketSize, USB_GET_ENDPOINT_TYPE(ep->bmAttributes));
                    goto find_end;
                }
            }
            break;

        default:
            break;
        }

        /* skip to next descriptor */
        pdescr += pdescr[DESC_bLength];
        current_descr_len += pdescr[DESC_bLength];
        if (current_descr_len >= descr_len && descr_len) {
            break;
        }
    }

find_end:
    if (((usb_infdesc_t *)if_desc)->bAlternateSetting) {
        if (usb_dev_core.user_cb && usb_dev_core.user_cb->open) {
            usb_dev_core.user_cb->open(((usb_infdesc_t *)if_desc)->bInterfaceNumber, alt_setting);
        }
    } else {
        if (usb_dev_core.user_cb && usb_dev_core.user_cb->close) {
            usb_dev_core.user_cb->close(((usb_infdesc_t *)if_desc)->bInterfaceNumber, alt_setting);
        }
    }

    return ret;
}

/**
* @brief  usbd_std_interface_req
*         Handle standard usb interface requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_std_interface_req(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    usb_status_t ret = USB_OK;
    uint8_t type = USB_HIBYTE(req->wValue);
    uint8_t intf_num = USB_LOBYTE(req->wIndex);
    uint32_t descr_len = 0;
    uint32_t current_descr_len = 0;
    uint8_t cur_iface = 0xFF;
    uint8_t *pdescr = (uint8_t *)usb_dev_core.descr.config_descriptor.descr;

    if (usb_dev_core.config == 0) {
        return USB_ERROR;
    }

    switch (req->bRequest) {
    case USB_REQ_GET_STATUS:
        (*data)[0] = 0x00;
        (*data)[1] = 0x00;
        *len = 2;
        break;

    case USB_REQ_GET_DESCRIPTOR:
        if (type == USB_DESC_TYPE_HID) {
            while (pdescr[DESC_bLength] != 0U) {
                switch (pdescr[DESC_bDescriptorType]) {
                case USB_DESC_TYPE_CONFIGURATION:
                    current_descr_len = 0;
                    descr_len = (pdescr[CONF_DESC_wTotalLength]) | (pdescr[CONF_DESC_wTotalLength + 1] << 8);
                    break;

                case USB_DESC_TYPE_INTERFACE:
                    cur_iface = pdescr[INTF_DESC_bInterfaceNumber];
                    break;

                case 0x21:
                    if (cur_iface == intf_num) {
                        *data = (uint8_t *)pdescr;
                        *len = pdescr[DESC_bLength];
                        return USB_OK;
                    }
                    break;

                default:
                    break;
                }
                pdescr += pdescr[DESC_bLength];
                current_descr_len += pdescr[DESC_bLength];
                if (current_descr_len >= descr_len && descr_len) {
                    break;
                }
            }
        } else if (type == USB_DESC_TYPE_HID_REPORT) {
            if (usb_dev_core.descr.hid_report_descriptor.descr && usb_dev_core.descr.hid_report_descriptor.len) {
                *data = (uint8_t *)usb_dev_core.descr.hid_report_descriptor.descr;
                *len = usb_dev_core.descr.hid_report_descriptor.len;
                return ret;
            }
        }
        ret = USB_ERROR;
        break;

    case USB_REQ_GET_INTERFACE:
        (*data)[0] = usb_dev_core.altset;
        *len = 1;
        break;

    case USB_REQ_SET_INTERFACE:
        usb_dev_core.altset = (uint8_t)(req->wValue);
        usbd_set_interface(req->wIndex, req->wValue);
        *len = 0;
        break;

    default:
        ret = USB_ERROR;
        break;
    }

    return ret;
}

/**
* @brief  usbd_std_endpoint_req
*         Handle standard usb endpoint requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_std_endpoint_req(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    usb_status_t ret = USB_OK;
    uint8_t ep = USB_LOBYTE(req->wIndex);

    if (usb_dev_core.config == 0) {
        return USB_ERROR;
    }

    switch (req->bRequest) {
    case USB_REQ_SET_FEATURE:
        if (req->wValue == USB_FEATURE_ENDPOINT_HALT) {
            usbd_set_ep_stall(ep);
            //USB_LOG_INFO("ep:%02x set halt\r\n", ep);
        } else {
            ret = USB_ERROR;
        }
        *len = 0;
        break;

    case USB_REQ_CLEAR_FEATURE:
        if (req->wValue == USB_FEATURE_ENDPOINT_HALT) {
            usbd_clear_ep_stall(ep);
            //USB_LOG_INFO("ep:%02x clear halt\r\n", ep);
            break;
        } else {
            ret = USB_ERROR;
        }
        *len = 0;
        break;

    case USB_REQ_GET_STATUS:
        if (usbd_ep_is_stalled(ep) == USB_OK) {
            (*data)[0] = 0x01;
        } else {
            (*data)[0] = 0x00;
        }
        (*data)[1] = 0x00;
        *len = 2;
        break;

    default:
        ret = USB_ERROR;
        break;
    }

    return ret;
}

/**
* @brief  usbd_std_endpoint_req
*         Handle standard usb endpoint requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_class_req(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    if ((req->bmRequestType & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_INTERFACE) {
        for (uint8_t i = 0; i < usb_dev_core.class_intf.amount; i++) {
            if (usb_dev_core.class_intf.cb[i].interface_cb && (i == (req->wIndex & 0xFF))) {
                return usb_dev_core.class_intf.cb[i].interface_cb(req, data, len);
            }
        }
    } else if ((req->bmRequestType & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_ENDPOINT) {
        for (uint8_t i = 0; i < usb_dev_core.class_intf.amount; i++) {
            if (usb_dev_core.class_intf.cb[i].endpoint_cb) {
                return usb_dev_core.class_intf.cb[i].endpoint_cb(req, data, len);
            }
        }
    } else {
        for (uint8_t i = 0; i < usb_dev_core.class_intf.amount; i++) {
            if (usb_dev_core.class_intf.cb[i].interface_cb && (i == (req->wIndex & 0xFF))) {
                return usb_dev_core.class_intf.cb[i].interface_cb(req, data, len);
            }
        }
    }
    return USB_ERROR;
}

/**
* @brief  usbd_std_endpoint_req
*         Handle standard usb endpoint requests
* @param  req: usb request
* @retval status
*/
static usb_status_t usbd_vendor_req(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    for (uint8_t i = 0; i < usb_dev_core.class_intf.amount; i++) {
        if (usb_dev_core.class_intf.cb[i].vendor_cb && (usb_dev_core.class_intf.cb[i].vendor_cb(req, data, len) == 0)) {
            return USB_OK;
        }
    }
    return USB_ERROR;
}

/**
* @brief  usbd_setup_stage
*         Handle the setup stage
* @param  req: setup The setup packet
* @param  data: Data buffer
* @param  len: Pointer to data length
* @retval status
*/
static usb_status_t usbd_setup_stage_handler(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    usb_status_t ret = USB_OK;
    switch (req->bmRequestType & USB_REQ_TYPE_MASK) {
    case USB_REQ_STANDARD:
        switch (req->bmRequestType & USB_REQ_RECIPIENT_MASK) {
        case USB_REQ_RECIPIENT_DEVICE:
            ret = usbd_std_device_req(req, data, len);
            break;

        case USB_REQ_RECIPIENT_INTERFACE:
            ret = usbd_std_interface_req(req, data, len);
            break;

        case USB_REQ_RECIPIENT_ENDPOINT:
            ret = usbd_std_endpoint_req(req, data, len);
            break;

        default:
            ret = USB_ERROR;
            break;
        }
        break;

    case USB_REQ_CLASS:
        ret = usbd_class_req(req, data, len);
        break;

    case USB_REQ_VENDOR:
        ret = usbd_vendor_req(req, data, len);
        break;

    default:
        ret = USB_ERROR;
        break;
    }
    return ret;
}

static void usbd_ep0_datain_stage(usb_setup_req_t *req, uint32_t len)
{
    usb_dev_core.ep0_buf += len;
    usb_dev_core.ep0_buf_residue -= len;

    if (usb_dev_core.ep0_buf_residue != 0) {
        usbd_ep_tx(USB_CTL_IN_EP0, usb_dev_core.ep0_buf, usb_dev_core.ep0_buf_residue);
    } else {
        if (usb_dev_core.zlp_flag) {
            usb_dev_core.zlp_flag = 0;
            usbd_ep_tx(USB_CTL_IN_EP0, NULL, 0);
        } else {
            if (req->wLength && ((req->bmRequestType & USB_REQ_DIR_MASK) == USB_REQ_DIR_IN)) {
                usbd_ep_preparerx(USB_CTL_OUT_EP0, NULL, 0);
            }
            usbd_set_ep_stall(USB_CTL_IN_EP0);
        }
#ifdef USB_CFG_DEVICE_TEST_ENABLE
        if (usb_dev_core.test_mode) {
            usbd_set_test_mode(usb_dev_core.test_mode);
            usb_dev_core.test_mode = 0;
        }
#endif
    }
}

static void usbd_ep0_dataout_stage(usb_setup_req_t *req, uint32_t len)
{
    if (len > 0) {
        usb_dev_core.ep0_buf += len;
        usb_dev_core.ep0_buf_residue -= len;
        if (usb_dev_core.ep0_buf_residue == 0) {
            usb_dev_core.ep0_buf = (uint8_t *)((unsigned int)(usb_dev_core.data_buff));
            uint8_t *converted_ptr = (uint8_t *)((unsigned int)(usb_dev_core.ep0_buf));
            if (usbd_setup_stage_handler(req, &converted_ptr, (uint32_t *)((unsigned int)(&(usb_dev_core.ep0_buf_size)))) != USB_OK) {
                usbd_set_ep_stall(USB_CTL_IN_EP0);
                return;
            }
            usbd_ep_tx(USB_CTL_IN_EP0, NULL, 0);
        } else {
            usbd_ep_preparerx(USB_CTL_OUT_EP0, usb_dev_core.ep0_buf, usb_dev_core.ep0_buf_residue);
        }
    }
}

static void usbd_class_event_handler(usbd_event_t event)
{
    if (usb_dev_core.class_event_cb) {
        usb_dev_core.class_event_cb(event);
    }
}

static void usbd_ep0_setup_stage(usb_setup_req_t *req)
{
    uint8_t *buf = NULL;

    if (req->wLength > USB_CFG_DEVICE_REQ_BUF_LEN) {
        if ((req->bmRequestType & USB_REQ_DIR_MASK) == USB_REQ_DIR_OUT) {
            USB_LOG_ERR("Request buffer too small\r\n");
            usbd_set_ep_stall(USB_CTL_IN_EP0);
            return;
        }
    }

    usb_dev_core.ep0_buf = (uint8_t *)((unsigned int)(usb_dev_core.data_buff));
    usb_dev_core.ep0_buf_residue = req->wLength;
    usb_dev_core.ep0_buf_size = req->wLength;
    usb_dev_core.zlp_flag = 0;
    buf = usb_dev_core.ep0_buf;

    if (req->wLength && ((req->bmRequestType & USB_REQ_DIR_MASK) == USB_REQ_DIR_OUT)) {
        usbd_ep_preparerx(USB_CTL_OUT_EP0, usb_dev_core.ep0_buf, req->wLength);
        return;
    }

    if (usbd_setup_stage_handler(req, &buf, (uint32_t *)((unsigned int)(&(usb_dev_core.ep0_buf_size)))) != USB_OK) {
        usbd_set_ep_stall(USB_CTL_IN_EP0);
        usbd_set_ep_stall(USB_CTL_OUT_EP0);
        usbd_read_setup_packet();
        return;
    }

    usb_dev_core.ep0_buf_residue = USB_MIN(usb_dev_core.ep0_buf_size, req->wLength);
    if (usb_dev_core.ep0_buf_residue > USB_CFG_DEVICE_REQ_BUF_LEN) {
        USB_LOG_ERR("Request buffer too small\r\n");
        usbd_set_ep_stall(USB_CTL_IN_EP0);
        return;
    }

    if (buf != usb_dev_core.ep0_buf) {
        memcpy(usb_dev_core.ep0_buf, buf, usb_dev_core.ep0_buf_residue);
    }

    usbd_ep_tx(USB_CTL_IN_EP0, usb_dev_core.ep0_buf, usb_dev_core.ep0_buf_residue);

    if ((req->wLength > usb_dev_core.ep0_buf_size) && (!(usb_dev_core.ep0_buf_size % USB_CTL_EP_MPS))) {
        usb_dev_core.zlp_flag = 1;
    }
}

/**
* @brief  usbd_reset
*         Handle Reset event
* @param  None
* @retval None
*/
static void usbd_reset_handler(void)
{
    usbd_set_device_address(0);
    usb_dev_core.address = 0;
    usb_dev_core.config = 0;

    /* Open EP0 IN */
    usbd_open_endpoint(USB_CTL_IN_EP0, USB_CTL_EP_MPS, USB_ENDPOINT_TYPE_CONTROL);

    /* Open EP0 OUT */
    usbd_open_endpoint(USB_CTL_OUT_EP0, USB_CTL_EP_MPS, USB_ENDPOINT_TYPE_CONTROL);
    usbd_class_event_handler(USBD_EVENT_RESET);
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->reset) {
        usb_dev_core.user_cb->reset();
    }
}

/**
* @brief  usbd_reset
*         Handle Reset event
* @param  None
* @retval None
*/
static void usbd_sof_handler(void)
{
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->sof) {
        usb_dev_core.user_cb->sof();
    }
}

/**
* @brief  usbd_resume
*         Handle Resume event
* @param  None
* @retval None
*/
static void usbd_resume_handler(void)
{
    usb_dev_core.is_suspend = 0;
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->resume) {
        usb_dev_core.user_cb->resume();
    }
}

/**
* @brief  usbd_suspend
*         Handle Suspend event
* @param  None
* @retval None
*/
static void usbd_suspend_handler(void)
{
    usb_dev_core.is_suspend = 1;
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->suspend) {
        usb_dev_core.user_cb->suspend();
    }
}

/**
* @brief  usbd_connected
*         Handle device connection event
* @param  None
* @retval None
*/
static void usbd_connect_handler(void)
{
    usb_dev_core.connection_status = 1;
    if (usb_dev_core.user_cb && usb_dev_core.user_cb->connected) {
        usb_dev_core.user_cb->connected();
    }
}

/**
* @brief  Handle device disconnection event
* @param  None
* @retval None
*/
static void usbd_disconnect_handler(void)
{
    usb_dev_core.connection_status = 0;

    usbd_deinit();
#ifndef USB_CFG_IP_CONIDSTS_ENABLE
#ifdef USB_CFG_USE_OTG_MODE
    usb_otg_init();
#endif
#endif
}

/**
* @brief  get suspend status
* @param  None
* @retval suspend status
*/
uint8_t usb_device_is_suspend(void)
{
    return usb_dev_core.is_suspend;
}

/**
* @brief  get init status
* @param  None
* @retval init status
*/
uint8_t usb_device_is_init(void)
{
    return usb_dev_core.config;
}

/**
* @brief  get wakeup status
* @param  None
* @retval wakeup status
*/
usb_status_t usbd_wakeup_host(void)
{
    if (usb_dev_core.remote_wakeup_support && usb_dev_core.remote_wakeup_enabled && usb_dev_core.is_suspend) {
        USB_LOG_INFO("active remotewakeup.\r\n");
        usbd_active_remotewakeup(usb_dev_core.low_power);
        return USB_OK;
    } else {
        if (usb_dev_core.remote_wakeup_support == 0) {
            USB_LOG_ERR("device does not support remote wakeup\r\n");
        }
        if (usb_dev_core.remote_wakeup_enabled == 0) {
            USB_LOG_ERR("device remote wakeup is not enabled\r\n");
        }
        if (usb_dev_core.is_suspend == 0) {
            USB_LOG_ERR("device is not in suspend state\r\n");
        }
        return USB_ERROR;
    }
}

#endif
#endif

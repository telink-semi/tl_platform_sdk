/********************************************************************************************************
 * @file    usbd_mouse.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
/*
 * @FilePath: \epm_driver\demo\usb2.0\usbd_mouse\usbd_mouse.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "common.h"
#if (USB_DEMO_TYPE == USB_MOUSE)
#include "usbd_mouse.h"
#include "usbd_hid.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/************************* variable definition *******************************/
/* USB Standard Device Descriptor */
uint8_t usbd_hid_dev_desc[] = {
    0x12,                 /* bLength */
    USB_DESC_TYPE_DEVICE, /* bDescriptorType */
    0x00,                 /* bcdUSB2.0 */
    0x02,
    0x00,                 /* bDeviceClass */
    0x00,                 /* bDeviceSubClass */
    0x00,                 /* bDeviceProtocol */
    USB_CTL_EP_MPS,       /* bMaxPacketSize */
    USB_LOBYTE(USBD_VID), /* idVendor */
    USB_HIBYTE(USBD_VID), /* idVendor */
    USB_LOBYTE(USBD_PID), /* idVendor */
    USB_HIBYTE(USBD_PID), /* idVendor */
    0x00,                 /* bcdDevice rel. 2.00 */
    0x02,
    STR_DESC_ID_MFC,       /* Index of manufacturer string */
    STR_DESC_ID_PRODUCT,   /* Index of product string */
    STR_DESC_ID_SERIALNUM, /* Index of serial number string */
    USBD_CFG_MAX_NUM       /* bNumConfigurations */
}; /* USB_DeviceDescriptor */

/* USB manufacturerstr Device Descriptor */
uint8_t usbd_hid_manufacturerstr_desc[] = {
    0x26,                 /* bLength */
    USB_DESC_TYPE_STRING, /* bDescriptorType */
    'E',
    0x00,
    'x',
    0x00,
    'p',
    0x00,
    'a',
    0x00,
    'n',
    0x00,
    's',
    0x00,
    'e',
    0x00,
    ' ',
    0x00,
    'T',
    0x00,
    'e',
    0x00,
    'c',
    0x00,
    'h',
    0x00,
    'n',
    0x00,
    'o',
    0x00,
    'l',
    0x00,
    'o',
    0x00,
    'g',
    0x00,
    'y',
    0x00,
};

/* USB productstr Device Descriptor */
uint8_t usbd_hid_productstr_desc[] = {
    0x26,                 /* bLength */
    USB_DESC_TYPE_STRING, /* bDescriptorType */
    'E',
    0x00,
    'x',
    0x00,
    'p',
    0x00,
    'a',
    0x00,
    'n',
    0x00,
    's',
    0x00,
    'e',
    0x00,
    ' ',
    0x00,
    'T',
    0x00,
    'e',
    0x00,
    'c',
    0x00,
    'h',
    0x00,
    'n',
    0x00,
    'o',
    0x00,
    'l',
    0x00,
    'o',
    0x00,
    'g',
    0x00,
    'y',
    0x00,
};

/* USB productstr Device Descriptor */
uint8_t usbd_hid_serialstr_desc[] = {
    0x1a,                 /* bLength */
    USB_DESC_TYPE_STRING, /* bDescriptorType */
    '3',
    0x00,
    '7',
    0x00,
    '7',
    0x00,
    'D',
    0x00,
    '3',
    0x00,
    '6',
    0x00,
    '7',
    0x00,
    '0',
    0x00,
    '3',
    0x00,
    '5',
    0x00,
    '3',
    0x00,
    '2',
    0x00,
};

uint8_t usbd_hid_cfg_desc[] = {
    0x09, /* bLength: Configuration Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,
    USB_CONFIG_DESC_SIZE,
    0x00,
    0x01, /* bNumInterfaces: 2 interfaces */
    0x01, /* bConfigurationValue: */
    0x00, /* iConfiguration: */
    0xE0, /* bmAttributes: */
    0x32, /* MaxPower 100 mA */

    /*Interface Descriptor */
    0x09,                    /* bLength: Interface Descriptor size */
    USB_DESC_TYPE_INTERFACE, /* bDescriptorType: Interface */
    /* Interface descriptor type */
    0x00, /* bInterfaceNumber: Number of Interface */
    0x00, /* bAlternateSetting: Alternate setting */
    0x01, /* bNumEndpoints: One endpoints used */
    0x03, /* bInterfaceClass: Communication Interface Class */
    0x01, /* bInterfaceSubClass: Abstract Control Model */
    0x02, /* bInterfaceProtocol: Common AT commands */
    0x00, /* iInterface: */

    /*HID Descriptor*/
    0x09,              /* bFunctionLength */
    USB_DESC_TYPE_HID, /* bDescriptorType: CUSTOM_HID */
    0x11,              /* bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number */
    0x01,              /* bMasterInterface: Communication class interface */
    0x00,              /* bCountryCode: Hardware target country */
    0x01,              /* bNumDescriptors: Number of CUSTOM_HID class descriptors to follow */
    0x22,              /* bDescriptorType */
    0x4A,              /* wItemLength: Total length of Report descriptor */
    0x00,

    /*Endpoint OUT Descriptor*/
    0x07,                   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT, /* bDescriptorType: Endpoint */
    CUSTOM_HID_IN_EP,       /* bEndpointAddress */
    0x03,                   /* bmAttributes: Bulk */
    0x04,                   /* wMaxPacketSize: */
    0x00,
    0x0a, /* bInterval: ignore for Bulk transfer */
};

/* USB Standard Device Descriptor */
uint8_t usbd_hid_dev_qualifier_desc[] = { 0x0a, USB_DESC_TYPE_DEVICE_QUALIFIER, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00 };

/* USB Standard Device Descriptor */
uint8_t usbd_hid_string_lang_id[] = {
    USB_LANGID_INIT(USBD_LANGID_STRING),
};

/*!< hid mouse report descriptor */
static uint8_t hid_mouse_report_desc[] = {
    0x05,
    0x01, /* Usage Page (Generic Desktop Ctrls) */
    0x09,
    0x02, /* Usage (Mouse) */
    0xA1,
    0x01, /* Collection (Application) */
    0x09,
    0x01, /* Usage (Pointer) */

    0xA1,
    0x00, /* Collection (Physical) */
    0x05,
    0x09, /* Usage Page (Button) */
    0x19,
    0x01, /* Usage Minimum (0x01) */
    0x29,
    0x03, /* Usage Maximum (0x03) */

    0x15,
    0x00, /* Logical Minimum (0) */
    0x25,
    0x01, /* Logical Maximum (1) */
    0x95,
    0x03, /* Report Count (3) */
    0x75,
    0x01, /* Report Size (1) */

    0x81,
    0x02, /* Input (Data,Var,Abs) */
    0x95,
    0x01, /* Report Count (1) */
    0x75,
    0x05, /* Report Size (5) */
    0x81,
    0x01, /* Input (Const,Array,Abs) */

    0x05,
    0x01, /* Usage Page (Generic Desktop Ctrls) */
    0x09,
    0x30, /* Usage (X) */
    0x09,
    0x31, /* Usage (Y) */
    0x09,
    0x38, /* Usage (Wheel) */

    0x15,
    0x81, /* Logical Minimum (-127) */
    0x25,
    0x7F, /* Logical Maximum (127) */
    0x75,
    0x08, /* Report Size (8) */
    0x95,
    0x03, /* Report Count (3) */

    0x81,
    0x06, /* Input (Data,Var,Rel) */
    0xC0, /* End Collection */
    0x09,
    0x3C, /* Usage (Motion Wakeup) */
    0x05,
    0xFF, /* Usage Page (Reserved 0xFF) */

    0x09,
    0x01, /* Usage (0x01) */
    0x15,
    0x00, /* Logical Minimum (0) */
    0x25,
    0x01, /* Logical Maximum (1) */
    0x75,
    0x01, /* Report Size (1) */

    0x95,
    0x02, /* Report Count (2) */
    0xB1,
    0x22, /* Feature (Data,Var,Abs,NoWrp) */
    0x75,
    0x06, /* Report Size (6) */
    0x95,
    0x01, /* Report Count (1) */
    0xB1,
    0x01, /* Feature (Const,Array,Abs,NoWrp) */
    0xC0  /* End Collection */
};

/*!< mouse report struct */
struct hid_mouse {
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t wheel;
};

/*!< mouse report */
static USB_MEM_ALIGNX struct hid_mouse mouse_cfg;

volatile uint8_t usb_tx_flag = 1;
volatile uint8_t usb_test_flag = 0;

static usb_status_t usbd_usr_reset_cb(void);
static usb_status_t usbd_usr_sof_cb(void);
static usb_status_t usbd_usr_connected_cb(void);
static usb_status_t usbd_usr_disconnected_cb(void);
static usb_status_t usbd_usr_suspend_cb(void);
static usb_status_t usbd_usr_resume_cb(void);
static usb_status_t usbd_usr_configured_cb(void);
static usb_status_t usbd_usr_open_cb(uint16_t intf_num, uint16_t alt_set);
static usb_status_t usbd_usr_close_cb(uint16_t intf_num, uint16_t alt_set);
static usb_status_t usbd_usr_set_remote_wakeup_cb(void);
static usb_status_t usbd_usr_clear_remote_wakeup_cb(void);

static void usbd_hid_get_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t **data, uint32_t *len);
static uint8_t usbd_hid_get_idle(uint8_t intf, uint8_t report_id);
static uint8_t usbd_hid_get_protocol(uint8_t intf);
static void usbd_hid_set_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint32_t report_len);
static void usbd_hid_set_idle(uint8_t intf, uint8_t report_id, uint8_t duration);
static void usbd_hid_set_protocol(uint8_t intf, uint8_t protocol);

usbd_usr_cb_t user_cb = {
    usbd_usr_reset_cb,
    usbd_usr_sof_cb,
    usbd_usr_connected_cb,
    usbd_usr_disconnected_cb,
    usbd_usr_suspend_cb,
    usbd_usr_resume_cb,
    usbd_usr_configured_cb,
    usbd_usr_open_cb,
    usbd_usr_close_cb,
    usbd_usr_set_remote_wakeup_cb,
    usbd_usr_clear_remote_wakeup_cb,
    NULL,
    NULL,
};

usbd_hid_cb_t usbd_hid_cb = {
    usbd_hid_get_report,
    usbd_hid_get_idle,
    usbd_hid_get_protocol,
    usbd_hid_set_report,
    usbd_hid_set_idle,
    usbd_hid_set_protocol,
};

uint8_t hid_idle = 0;
uint8_t hid_protocol = 0;

/************************* variable declear *******************************/

/**************************** function declear *******************************/

/********************** function implementation ******************************/
static usb_status_t usbd_usr_reset_cb(void)
{
    soc_printf("interface reset.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_sof_cb(void)
{
    //soc_printf("sof.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_connected_cb(void)
{
    soc_printf("USB Device Connected.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_disconnected_cb(void)
{
    soc_printf("USB Device Disconnected.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_open_cb(uint16_t intf_num, uint16_t alt_set)
{
    (void)intf_num;
    (void)alt_set;
    soc_printf("OPEN\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_close_cb(uint16_t intf_num, uint16_t alt_set)
{
    (void)alt_set;
    (void)intf_num;
    soc_printf("CLOSE\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_resume_cb(void)
{
    soc_printf("Device Resumed in Idle Mode.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_suspend_cb(void)
{
    soc_printf("Device In suspend mode\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_configured_cb(void)
{
    soc_printf("set configuration.\r\n");
    return USB_OK;
}

static usb_status_t usbd_usr_set_remote_wakeup_cb(void)
{
    return USB_OK;
}

static usb_status_t usbd_usr_clear_remote_wakeup_cb(void)
{
    return USB_OK;
}

/*
 * Appendix G: HID Request Support Requirements
 *
 * The following table enumerates the requests that need to be supported by various types of HID class devices.
 * Device type     GetReport   SetReport   GetIdle     SetIdle     GetProtocol SetProtocol
 * ------------------------------------------------------------------------------------------
 * Boot Mouse      Required    Optional    Optional    Optional    Required    Required
 * Non-Boot Mouse  Required    Optional    Optional    Optional    Optional    Optional
 * Boot Keyboard   Required    Optional    Required    Required    Required    Required
 * Non-Boot Keybrd Required    Optional    Required    Required    Optional    Optional
 * Other Device    Required    Optional    Optional    Optional    Optional    Optional
 */
static void usbd_hid_get_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t **data, uint32_t *len)
{
    (void)intf;
    (void)report_type;
    if (report_id == 0x23) {
        *len = 32;
        (*data)[0] = 0x23;
    } else if (report_id == 0x24) {
        *len = 64;
        (*data)[0] = 0x24;
    } else if (report_id == 0x10) {
        *len = 2;
        (*data)[0] = 0x10;
    }
}

static uint8_t usbd_hid_get_idle(uint8_t intf, uint8_t report_id)
{
    (void)intf;
    (void)report_id;
    return hid_idle;
}

static uint8_t usbd_hid_get_protocol(uint8_t intf)
{
    (void)intf;
    return hid_protocol;
}

static void usbd_hid_set_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint32_t report_len)
{
    (void)intf;
    (void)report_id;
    (void)report_type;
    (void)report;
    (void)report_len;
}

static void usbd_hid_set_idle(uint8_t intf, uint8_t report_id, uint8_t duration)
{
    (void)intf;
    (void)report_id;
    hid_idle = duration;
}

static void usbd_hid_set_protocol(uint8_t intf, uint8_t protocol)
{
    (void)intf;
    //(void)protocol;
    hid_protocol = protocol;
}

/**
 * @brief  usbd_hid_in
 *         Handles the hid IN data stage.
 * @param  epnum: endpoint number
 * @param  len: data Length
 * @retval status
 */
static usb_status_t usbd_hid_in(uint8_t epnum, uint32_t len)
{
    (void)epnum;
    (void)len;
    usb_tx_flag = 1;
    return USB_OK;
}

void usbd_mouse_init(void)
{
    usbd_handle_init();

    /*!< init mouse report data */
    mouse_cfg.buttons = 0;
    mouse_cfg.wheel = 0;
    mouse_cfg.x = 0;
    mouse_cfg.y = 0;

    usbd_desc_register(DESCR_ID_DEVICE, usbd_hid_dev_desc, sizeof(usbd_hid_dev_desc));
    usbd_desc_register(DESCR_ID_MANUFACTURER_STR, usbd_hid_manufacturerstr_desc, sizeof(usbd_hid_manufacturerstr_desc));
    usbd_desc_register(DESCR_ID_PRODUCT_STR, usbd_hid_productstr_desc, sizeof(usbd_hid_productstr_desc));
    usbd_desc_register(DESCR_ID_SERIAL_STR, usbd_hid_serialstr_desc, sizeof(usbd_hid_serialstr_desc));
    usbd_desc_register(DESCR_ID_CONFIG, usbd_hid_cfg_desc, sizeof(usbd_hid_cfg_desc));
    usbd_desc_register(DESCR_ID_DEVQLF, usbd_hid_dev_qualifier_desc, sizeof(usbd_hid_dev_qualifier_desc));
    usbd_desc_register(DESCR_ID_LANGID_STR, usbd_hid_string_lang_id, sizeof(usbd_hid_string_lang_id));
    usbd_desc_register(DESCR_ID_HID_REPORT, hid_mouse_report_desc, sizeof(hid_mouse_report_desc));

    usbd_user_cb_register(&user_cb);

    usbd_endpoint_register(CUSTOM_HID_IN_EP, usbd_hid_in);

    usbd_class_intf_register(usbd_hid_get_inf_cb(), 0);

    usbd_hid_cb_register(&usbd_hid_cb);

    usbd_init();
}

#define CURSOR_STEP  2U
#define CURSOR_WIDTH 20U

void draw_circle(uint8_t *buf)
{
    static uint32_t move_cnt = 0;
    static uint8_t step_x_y = 0;
    static int8_t x = 0, y = 0;

    move_cnt++;
    if (move_cnt > CURSOR_WIDTH) {
        step_x_y++;
        step_x_y = step_x_y % 4;
        move_cnt = 0;
    }
    switch (step_x_y) {
    case 0: {
        y = 0;
        x = CURSOR_STEP;
    } break;

    case 1: {
        x = 0;
        y = CURSOR_STEP;
    } break;

    case 2: {
        y = 0;
        x = (int8_t)(-CURSOR_STEP);
    } break;

    case 3: {
        x = 0;
        y = (int8_t)(-CURSOR_STEP);
    } break;
    }

    buf[0] = 0;
    buf[1] = x;
    buf[2] = y;
    buf[3] = 0;
}

/* https://cps-check.com/cn/polling-rate-check */
void usbd_mouse_test(void)
{
    int counter = 0;
    if (usb_test_flag) {
        drv_delay_ms(500);
        //usb_test_flag = 0;
        while (counter < 1000) {
            usb_tx_flag = 0;
            draw_circle((uint8_t *)&mouse_cfg);
            int ret = usbd_ep_tx(CUSTOM_HID_IN_EP, (uint8_t *)&mouse_cfg, 4);
            if (ret < 0) {
                soc_printf("usbd_ep_tx error!\n");
                return;
            }
            while (usb_tx_flag == 0) {
            }
            counter++;
        }
    }
}

#endif
#endif

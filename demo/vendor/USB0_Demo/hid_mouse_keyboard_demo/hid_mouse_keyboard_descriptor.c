/********************************************************************************************************
 * @file    hid_mouse_keyboard_descriptor.c
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
#include "common.h"
#if (USB_DEMO_TYPE == USB_MOUSE_KEYBOARD)
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tl_usb/core/usbd_core.h"
#include "hid_mouse_keyboard_descriptor.h"

/* keyboard */
unsigned char desc_hid_report0[] = {
    0x05,
    0x01,
    0x09,
    0x06,
    0xA1,
    0x01,
    0x05,
    0x07,
    0x19,
    0xE0,
    0x29,
    0xE7,
    0x15,
    0x00,
    0x25,
    0x01,
    0x95,
    0x08,
    0x75,
    0x01,
    0x81,
    0x02,
    0x81,
    0x03,
    0x95,
    0x05,
    0x05,
    0x08,
    0x19,
    0x01,
    0x29,
    0x05,
    0x91,
    0x02,
    0x95,
    0x01,
    0x75,
    0x03,
    0x91,
    0x01,
    0x95,
    0x06,
    0x75,
    0x08,
    0x15,
    0x00,
    0x26,
    0xA4,
    0x00,
    0x05,
    0x07,
    0x19,
    0x00,
    0x2A,
    0xA4,
    0x00,
    0x81,
    0x00,
    0xC0,
};

/* mouse */
unsigned char desc_hid_report1[] = {
    0x05,
    0x01,
    0x09,
    0x02,
    0xA1,
    0x01,
    0x85,
    0x01,
    0x09,
    0x01,
    0xA1,
    0x00,
    0x05,
    0x09,
    0x19,
    0x01,
    0x29,
    0x05,
    0x15,
    0x00,
    0x25,
    0x01,
    0x95,
    0x05,
    0x75,
    0x01,
    0x81,
    0x02,
    0x95,
    0x01,
    0x75,
    0x03,
    0x81,
    0x01,
    0x05,
    0x01,
    0x09,
    0x30,
    0x09,
    0x31,
    0x15,
    0x81,
    0x25,
    0x7F,
    0x75,
    0x08,
    0x95,
    0x02,
    0x81,
    0x06,
    0x09,
    0x38,
    0x15,
    0x81,
    0x25,
    0x7F,
    0x75,
    0x08,
    0x95,
    0x01,
    0x81,
    0x06,
    0xC0,
    0xC0,
    0x05,
    0x0C,
    0x09,
    0x01,
    0xA1,
    0x01,
    0x85,
    0x03,
    0x75,
    0x10,
    0x95,
    0x02,
    0x15,
    0x01,
    0x26,
    0x9C,
    0x02,
    0x19,
    0x01,
    0x2A,
    0x8C,
    0x02,
    0x81,
    0x00,
    0xC0,
    0x05,
    0x01,
    0x09,
    0x80,
    0xA1,
    0x01,
    0x85,
    0x04,
    0x75,
    0x02,
    0x95,
    0x01,
    0x15,
    0x01,
    0x25,
    0x03,
    0x09,
    0x82,
    0x09,
    0x81,
    0x09,
    0x83,
    0x81,
    0x60,
    0x75,
    0x06,
    0x81,
    0x03,
    0xC0,
    0x05,
    0x01,
    0x09,
    0x00,
    0xA1,
    0x01,
    0x85,
    0x05,
    0x06,
    0x00,
    0xFF,
    0x09,
    0x01,
    0x15,
    0x81,
    0x25,
    0x7F,
    0x75,
    0x08,
    0x95,
    0x07,
    0xB1,
    0x02,
    0xC0,
};

unsigned char device_desc[] = {
    0x12,
    USB_DESC_DEVICE,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    U16_LOW_BYTE(ID_VENDOR),
    U16_HIGH_BYTE(ID_VENDOR),
    U16_LOW_BYTE(ID_PRODUCT),
    U16_HIGH_BYTE(ID_PRODUCT),
    U16_LOW_BYTE(ID_VERSION),
    U16_HIGH_BYTE(ID_VERSION),
    0x01,
    0x02,
    0x03,
    0x01,
};

unsigned char *usbd_get_device_descriptor(unsigned char bus)
{
    (void)bus;
    return (unsigned char *)&device_desc;
}

unsigned char config_desc[] = {
    0x09,
    USB_DESC_CONFIGURATION,
    0x3B,
    0x00,
    0x02,
    0x01,
    0x00,
    0xA0,
    0x19,
    0x09,
    USB_DESC_INTERFACE,
    0x00,
    0x00,
    0x01,
    0x03,
    0x01,
    0x01,
    0x00,
    0x09,
    0x21,
    0x11,
    0x01,
    0x21,
    0x01,
    0x22,
    U16_LOW_BYTE(sizeof(desc_hid_report0)),
    U16_HIGH_BYTE(sizeof(desc_hid_report0)),
    0x07,
    USB_DESC_ENDPOINT,
    HID_KEYBOARD_IN_ENDPOINT_ADDRESS,
    0x03,
    U16_LOW_BYTE(HID_KEYBOARD_IN_ENDPOINT_SIZE),
    U16_HIGH_BYTE(HID_KEYBOARD_IN_ENDPOINT_SIZE),
    HID_KEYBOARD_IN_ENDPOINT_INTERVAL,
    0x09,
    0x04,
    0x01,
    0x00,
    0x01,
    0x03,
    0x01,
    0x02,
    0x00,
    0x09,
    0x21,
    0x11,
    0x01,
    0x21,
    0x01,
    0x22,
    U16_LOW_BYTE(sizeof(desc_hid_report1)),
    U16_HIGH_BYTE(sizeof(desc_hid_report1)),
    0x07,
    USB_DESC_ENDPOINT,
    HID_MOUSE_IN_ENDPOINT_ADDRESS,
    0x03,
    U16_LOW_BYTE(HID_MOUSE_IN_ENDPOINT_ADDRESS),
    U16_HIGH_BYTE(HID_MOUSE_IN_ENDPOINT_ADDRESS),
    HID_MOUSE_IN_ENDPOINT_INTERVAL,
};

unsigned char *usbd_get_config_descriptor(unsigned char bus)
{
    (void)bus;
    return (unsigned char *)&config_desc;
}

unsigned char device_qualifier[] = {
    0x0a,
    USB_DESC_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
};

unsigned char *usbd_get_device_qualifier_descriptor(unsigned char bus)
{
    (void)bus;

    return device_qualifier;
}

// this example use the same configuration for both high and full speed mode
unsigned char other_speed_config[] = {
    0x09,
    USB_DESC_CONFIGURATION,
    0x3B,
    0x00,
    0x02,
    0x01,
    0x00,
    0xA0,
    0x19,
    0x09,
    USB_DESC_INTERFACE,
    0x00,
    0x00,
    0x01,
    0x03,
    0x01,
    0x01,
    0x00,
    0x09,
    0x21,
    0x11,
    0x01,
    0x21,
    0x01,
    0x22,
    U16_LOW_BYTE(sizeof(desc_hid_report0)),
    U16_HIGH_BYTE(sizeof(desc_hid_report0)),
    0x07,
    USB_DESC_ENDPOINT,
    HID_KEYBOARD_IN_ENDPOINT_ADDRESS,
    0x03,
    U16_LOW_BYTE(HID_KEYBOARD_IN_ENDPOINT_SIZE),
    U16_HIGH_BYTE(HID_KEYBOARD_IN_ENDPOINT_SIZE),
    HID_KEYBOARD_IN_ENDPOINT_INTERVAL,
    0x09,
    0x04,
    0x01,
    0x00,
    0x01,
    0x03,
    0x01,
    0x02,
    0x00,
    0x09,
    0x21,
    0x11,
    0x01,
    0x21,
    0x01,
    0x22,
    U16_LOW_BYTE(sizeof(desc_hid_report1)),
    U16_HIGH_BYTE(sizeof(desc_hid_report1)),
    0x07,
    USB_DESC_ENDPOINT,
    HID_MOUSE_IN_ENDPOINT_ADDRESS,
    0x03,
    U16_LOW_BYTE(HID_MOUSE_IN_ENDPOINT_ADDRESS),
    U16_HIGH_BYTE(HID_MOUSE_IN_ENDPOINT_ADDRESS),
    HID_MOUSE_IN_ENDPOINT_INTERVAL,
};

unsigned char *usbd_get_other_speed_configuration_descriptor(unsigned char bus, unsigned char index)
{
    (void)bus;
    (void)index;

    other_speed_config[1] = USB_DESC_OTHER_SPEED_CONFIG;

    return other_speed_config;
}

char const *string_desc_arr[] = {
    (const char[]){0x09, 0x04},
    STRING_VENDOR,
    STRING_PRODUCT,
    STRING_SERIAL,
};

static unsigned short _desc_str[64 + 1];

unsigned char *usbd_get_string_descriptor(unsigned char bus, unsigned char index)
{
    (void)bus;
    (void)index;
    unsigned short chr_count;

    switch (index) {
    case 0:
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
        break;

    default:
        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) {
            return NULL;
        }

        const char *str = string_desc_arr[index];

        // Cap at max char
        chr_count              = strlen(str);
        size_t const max_count = sizeof(_desc_str) / sizeof(_desc_str[0]) - 1; // -1 for string type
        if (chr_count > max_count) {
            chr_count = max_count;
        }

        // Convert ASCII string into UTF-16
        for (size_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
        break;
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t)((USB_DESC_STRING << 8) | (2 * chr_count + 2));

    return (unsigned char *)_desc_str;
}

unsigned char *usbd_hid_get_report_descriptor(unsigned char bus, unsigned char intf, unsigned short *len)
{
    (void)bus;
    (void)intf;
    (void)len;
    unsigned char *ptr = 0;

    if (intf == 0) {
        *len = sizeof(desc_hid_report0);
        ptr = desc_hid_report0;
    } else if (intf == 1) {
        *len = sizeof(desc_hid_report1);
        ptr = desc_hid_report1;
    }

    return ptr;
}
#endif

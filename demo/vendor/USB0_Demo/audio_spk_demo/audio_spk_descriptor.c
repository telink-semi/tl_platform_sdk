/********************************************************************************************************
 * @file    audio_spk_descriptor.c
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
#if (USB_DEMO_TYPE == USB_SPEAKER)
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tl_usb/core/usbd_core.h"
#include "audio_spk_descriptor.h"

unsigned char device_desc[] = {
    0x12,
    0x01,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x8A,
    0x24,
    0x06,
    0x80,
    0x00,
    0x01,
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
    0x02,
    0x6E,
    0x00,
    0x02,
    0x01,
    0x00,
    0x80,
    0x19,
    0x09,
    0x04,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,
    0x09,
    0x24,
    0x01,
    0x00,
    0x01,
    0x28,
    0x00,
    0x01,
    0x01,
    0x0C,
    0x24,
    0x02,
    0x01,
    0x01,
    0x01,
    0x00,
    0x02,
    0x03,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x24,
    0x06,
    0x02,
    0x01,
    0x01,
    0x03,
    0x00,
    0x00,
    0x00,
    0x09,
    0x24,
    0x03,
    0x03,
    0x01,
    0x03,
    0x00,
    0x02,
    0x00,
    0x09,
    0x04,
    0x01,
    0x00,
    0x00,
    0x01,
    0x02,
    0x00,
    0x00,
    0x09,
    0x04,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x00,
    0x00,
    0x07,
    0x24,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x0B,
    0x24,
    0x02,
    0x01,
    0x02,
    0x02,
    0x10,
    0x01,
    0x80,
    0x3E,
    0x00,
    0x09,
    0x05,
    0x06,
    0x09,
    0x40,
    0x00,
    0x04,
    0x00,
    0x00,
    0x07,
    0x25,
    0x01,
    0x81,
    0x00,
    0x00,
    0x00,
};

unsigned char *usbd_get_config_descriptor(unsigned char bus)
{
    (void)bus;
    return (unsigned char *)&config_desc;
}

unsigned char device_qualifier[] = {0x0a, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00};

unsigned char *usbd_get_device_qualifier_descriptor(unsigned char bus)
{
    (void)bus;

    return device_qualifier;
}

// this example use the same configuration for both high and full speed mode
unsigned char other_speed_config[] = {
    0x09,
    0x02,
    0x6E,
    0x00,
    0x02,
    0x01,
    0x00,
    0x80,
    0x19,
    0x09,
    0x04,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,
    0x09,
    0x24,
    0x01,
    0x00,
    0x01,
    0x28,
    0x00,
    0x01,
    0x01,
    0x0C,
    0x24,
    0x02,
    0x01,
    0x01,
    0x01,
    0x00,
    0x02,
    0x03,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x24,
    0x06,
    0x02,
    0x01,
    0x01,
    0x03,
    0x00,
    0x00,
    0x00,
    0x09,
    0x24,
    0x03,
    0x03,
    0x01,
    0x03,
    0x00,
    0x02,
    0x00,
    0x09,
    0x04,
    0x01,
    0x00,
    0x00,
    0x01,
    0x02,
    0x00,
    0x00,
    0x09,
    0x04,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x00,
    0x00,
    0x07,
    0x24,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x0B,
    0x24,
    0x02,
    0x01,
    0x02,
    0x02,
    0x10,
    0x01,
    0x80,
    0x3E,
    0x00,
    0x09,
    0x05,
    0x06,
    0x09,
    0x40,
    0x00,
    0x01,
    0x00,
    0x00,
    0x07,
    0x25,
    0x01,
    0x81,
    0x00,
    0x00,
    0x00,
};

unsigned char *usbd_get_other_speed_configuration_descriptor(unsigned char bus, unsigned char index)
{
    (void)bus;
    (void)index;

    other_speed_config[1] = USB_DESC_OTHER_SPEED_CONFIG;

    return other_speed_config;
}

char const *string_desc_arr[] = {
    (const char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
    "usbtst sim", // 1: Manufacturer
    "usbtst sim spk", // 2: Product
    "12345678", // 3: Serials will use unique ID if possible
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
#endif

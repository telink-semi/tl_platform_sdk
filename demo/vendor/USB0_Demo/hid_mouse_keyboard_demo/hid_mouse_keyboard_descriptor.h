/********************************************************************************************************
 * @file    hid_mouse_keyboard_descriptor.h
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
#ifndef __HID_MOUSE_KEYBOARD_DESCRIPTOR_H__
#define __HID_MOUSE_KEYBOARD_DESCRIPTOR_H__

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define USB_HIGH_SPEED_EN 1

#define ID_VENDOR  0x248a
#define ID_PRODUCT 0x8006
#define ID_VERSION 0x0100

#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink KM"
#define STRING_SERIAL  "KM demo"

#define HID_KEYBOARD_IN_ENDPOINT_ADDRESS  0x81
#define HID_KEYBOARD_IN_ENDPOINT_SIZE     0x10
#define HID_KEYBOARD_IN_ENDPOINT_INTERVAL 0x01

#define HID_MOUSE_IN_ENDPOINT_ADDRESS  0x82
#define HID_MOUDE_IN_ENDPOINT_SIZE     0x08
#define HID_MOUSE_IN_ENDPOINT_INTERVAL 0x01

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif // __HID_MOUSE_KEYBOARD_DESCRIPTOR_H__

/********************************************************************************************************
 * @file    cdc_descriptor.h
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
#ifndef __CDC_DESCRIPTOR_H__
#define __CDC_DESCRIPTOR_H__

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define USB_HIGH_SPEED_EN 1

#define ID_VENDOR  0x248a
#define ID_PRODUCT 0x8002
#define ID_VERSION 0x0100

#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink CDC"
#define STRING_SERIAL  "CDC demo"

#define CDC_DATA_IN_ENDPOINT_ADDRESS  0x84
#define CDC_DATA_OUT_ENDPOINT_ADDRESS 0x05

#if USB_HIGH_SPEED_EN
#define CDC_DATA_IN_ENDPOINT_SIZE     0x200
#define CDC_DATA_OUT_ENDPOINT_SIZE    0x200
#else
#define CDC_DATA_IN_ENDPOINT_SIZE     0x40
#define CDC_DATA_OUT_ENDPOINT_SIZE    0x40
#endif

#define CDC_NOTIFICATION_IN_ENDPOINT_ADDRESS 0x82
#define CDC_NOTIFICATION_IN_ENDPOINT_SIZE    0x08

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif // __CDC_DESCRIPTOR_H__

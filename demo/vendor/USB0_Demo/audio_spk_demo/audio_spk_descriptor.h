/********************************************************************************************************
 * @file    audio_spk_descriptor.h
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
#ifndef __AUDIO_SPK_DESCRIPTOR_H__
#define __AUDIO_SPK_DESCRIPTOR_H__

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define USB_HIGH_SPEED_EN 0

#define ID_VENDOR  0x248a
#define ID_PRODUCT 0x8006
#define ID_VERSION 0x0100

#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink SPK"
#define STRING_SERIAL  "SPK demo"

#define AUDIO_SPK_OUT_ENDPOINT_ADDRESS 0x06

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif // __AUDIO_SPK_DESCRIPTOR_H__

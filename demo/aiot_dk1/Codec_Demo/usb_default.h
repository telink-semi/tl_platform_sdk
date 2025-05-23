/********************************************************************************************************
 * @file    usb_default.h
 *
 * @brief   This is the header file for TL7518/TL721X/TL321X
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#pragma once
//////////// product  Information  //////////////////////////////


#define FLOW_NO_S               1

#define MS_OS_DESCRIPTOR_ENABLE 0
#define APPLICATION_DONGLE      1
#if (APPLICATION_DONGLE)

#ifndef USB_PRINTER_ENABLE
#define USB_PRINTER_ENABLE 0
#endif

#ifndef USB_MOUSE_ENABLE
#define USB_MOUSE_ENABLE 0
#endif

#ifndef USB_KEYBOARD_ENABLE
#define USB_KEYBOARD_ENABLE 0
#endif

#ifndef USB_MIC_ENABLE
#define USB_MIC_ENABLE 0
#endif

#ifndef USB_SPEAKER_ENABLE
#define USB_SPEAKER_ENABLE 0
#endif

#ifndef USB_CDC_ENABLE
#define USB_CDC_ENABLE 0
#endif

#ifndef USB_SOMATIC_ENABLE
#define USB_SOMATIC_ENABLE 0 //  when USB_SOMATIC_ENABLE, USB_EDP_PRINTER_OUT disable
#endif

#ifndef USB_CUSTOM_HID_REPORT
#define USB_CUSTOM_HID_REPORT 0
#endif

#ifndef USB_MASS_STORAGE_ENABLE
#define USB_MASS_STORAGE_ENABLE 0
#endif


#endif

#define USB_ENUM_IN_INTERRUPT 0 /* 1: usb enumeration in interrupt, 0: usb enumeration in main_loop. */

#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
#define USB_PHYSICAL_EDP_CDC_IN  USB_EDP4_IN  /* physical in endpoint */
#define USB_PHYSICAL_EDP_CDC_OUT USB_EDP5_OUT /* physical out endpoint */
#else
/* control endpoint size config. */
#define USB_CTR_ENDPOINT_SIZE 64 /* 8/16/32/64 */
#define USB_CTR_SIZE                \
    (USB_CTR_ENDPOINT_SIZE == 64) ? \
        SIZE_64_BYTE :              \
        ((USB_CTR_ENDPOINT_SIZE == 32) ? SIZE_32_BYTE : ((USB_CTR_ENDPOINT_SIZE == 16) ? SIZE_16_BYTE : ((USB_CTR_ENDPOINT_SIZE == 8) ? SIZE_8_BYTE : SIZE_64_BYTE)))

#define USB_MAP_EN               0 /* 1:usb map function enable, 0:usb map function disable. */

#define USB_PHYSICAL_EDP_CDC_IN  USB_EDP4_IN  /* physical in endpoint */
#define USB_PHYSICAL_EDP_CDC_OUT USB_EDP5_OUT /* physical out endpoint */

#if (USB_MAP_EN == 1)
#define CDC_RX_EPNUM USB_EDP5_OUT /* logical in endpoint */
#define CDC_TX_EPNUM USB_EDP5_OUT /* logical out endpoint */
#else
#define CDC_RX_EPNUM USB_PHYSICAL_EDP_CDC_OUT /* USB_MAP_EN = 0, logical endpoint is the same as the physical endpoint */
#define CDC_TX_EPNUM USB_PHYSICAL_EDP_CDC_IN  /* USB_MAP_EN = 0, logical endpoint is the same as the physical endpoint*/
#endif

#endif

/* control endpoint size default is 8 bytes. */
#ifndef USB_CTR_ENDPOINT_SIZE
#define USB_CTR_ENDPOINT_SIZE 8
#endif

//////////////////// Audio /////////////////////////////////////

#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
#define MIC_RESOLUTION_BIT  16
#define MIC_SAMPLE_RATE     48000 //set sample for mic
#define MIC_CHANNEL_COUNT   1     //1 or 2

#define MIC_ENCODER_ENABLE  0

#define SPK_RESOLUTION_BIT  16
#define SPK_CHANNEL_COUNT   2
#define SPEAKER_SAMPLE_RATE 48000

#endif


#define ID_VENDOR 0x248a // for report

#if (USB_CDC_ENABLE)
#define ID_PRODUCT 0x8002
#else
#if (USB_PRINTER_ENABLE)
#define ID_PRODUCT 0x5320
#else
#define ID_PRODUCT 0x8006
#endif
#endif

#define ID_VERSION              0x0100

#define TO_STRING(x)            #x
#define EXPAND_AND_TO_STRING(x) TO_STRING(x)

#if (USB_CDC_ENABLE)
/**
 * @brief  If the string is longer than 32, the program takes only the first 32 characters, and the subsequent strings will be handled in the same way.
 * @note
 *         - Longer strings can be supported by modifying the length of the usb_desc_str array.
 */
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink CDC"
#define STRING_SERIAL  "CDC demo"
#endif

#if (USB_MOUSE_ENABLE & (!USB_KEYBOARD_ENABLE))
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink Mouse"
#define STRING_SERIAL  "Mouse demo"
#endif

#if ((!USB_MOUSE_ENABLE) & USB_KEYBOARD_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Tek Keyboard"
#define STRING_SERIAL  "Keyboard demo"
#endif

#if ((USB_MOUSE_ENABLE) & USB_KEYBOARD_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink KM"
#define STRING_SERIAL  "KM demo"
#endif

#if (USB_MIC_ENABLE) && (!USB_SPEAKER_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink MIC_" EXPAND_AND_TO_STRING(MIC_SAMPLE_RATE) "-" EXPAND_AND_TO_STRING(MIC_CHANNEL_COUNT)
#define STRING_SERIAL  "MIC demo"
#endif

#if (!USB_MIC_ENABLE) && (USB_SPEAKER_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink SPK_" EXPAND_AND_TO_STRING(SPEAKER_SAMPLE_RATE) "-" EXPAND_AND_TO_STRING(SPK_CHANNEL_COUNT)
#define STRING_SERIAL  "SPK demo"
#endif

#if (USB_MIC_ENABLE && USB_SPEAKER_ENABLE)
#define STRING_VENDOR "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT                                                                                                                                                          \
    "Telink_MIC_SPK_" EXPAND_AND_TO_STRING(MIC_SAMPLE_RATE) "-" EXPAND_AND_TO_STRING(MIC_CHANNEL_COUNT) "_" EXPAND_AND_TO_STRING(SPEAKER_SAMPLE_RATE) "-" EXPAND_AND_TO_STRING( \
        SPK_CHANNEL_COUNT)
#define STRING_SERIAL "MIC_SPK demo"
#endif

#if (USB_MASS_STORAGE_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink MASS_STORAGE"
#define STRING_SERIAL  "MS Demo"
#endif

#if (USB_PRINTER_ENABLE)
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "USB DevSys"
#define STRING_SERIAL  "USB DevSys"
#endif

#if ((!(USB_MIC_ENABLE || USB_SPEAKER_ENABLE)) && (!USB_KEYBOARD_ENABLE) && (!USB_MOUSE_ENABLE) && (!USB_CDC_ENABLE) && (!USB_MASS_STORAGE_ENABLE) && (!USB_PRINTER_ENABLE))
#define STRING_VENDOR  "Telink Semi-conductor Ltd, Co"
#define STRING_PRODUCT "Telink No Product"
#define STRING_SERIAL  "USB demo"
#endif


///////////////////  USB   /////////////////////////////////
#ifndef IRQ_USB_PWDN_ENABLE
#define IRQ_USB_PWDN_ENABLE 0
#endif


#ifndef USB_PRINTER_ENABLE
#define USB_PRINTER_ENABLE 0
#endif
#ifndef USB_SPEAKER_ENABLE
#define USB_SPEAKER_ENABLE 0
#endif
#ifndef USB_MIC_ENABLE
#define USB_MIC_ENABLE 0
#endif
#ifndef USB_MOUSE_ENABLE
#define USB_MOUSE_ENABLE 0
#endif
#ifndef USB_KEYBOARD_ENABLE
#define USB_KEYBOARD_ENABLE 0
#endif
#ifndef USB_SOMATIC_ENABLE
#define USB_SOMATIC_ENABLE 0
#endif
#ifndef USB_CUSTOM_HID_REPORT
#define USB_CUSTOM_HID_REPORT 0
#endif
#ifndef USB_AUDIO_441K_ENABLE
#define USB_AUDIO_441K_ENABLE 0
#endif
#ifndef USB_MASS_STORAGE_ENABLE
#define USB_MASS_STORAGE_ENABLE 0
#endif

#ifndef MIC_CHANNEL_COUNT
#define MIC_CHANNEL_COUNT 1
#endif

#ifndef USB_DESCRIPTOR_CONFIGURATION_FOR_KM_DONGLE
#define USB_DESCRIPTOR_CONFIGURATION_FOR_KM_DONGLE 0
#endif

#ifndef USB_ID_AND_STRING_CUSTOM
#define USB_ID_AND_STRING_CUSTOM 0
#endif

#define KEYBOARD_RESENT_MAX_CNT      3
#define KEYBOARD_REPEAT_CHECK_TIME   300000 // in us
#define KEYBOARD_REPEAT_INTERVAL     100000 // in us
#define KEYBOARD_SCAN_INTERVAL       16000  // in us
#define MOUSE_SCAN_INTERVAL          8000   // in us
#define SOMATIC_SCAN_INTERVAL        8000

#define USB_KEYBOARD_POLL_INTERVAL   10 // in ms    USB_KEYBOARD_POLL_INTERVAL < KEYBOARD_SCAN_INTERVAL to ensure PC no missing key
#define USB_MOUSE_POLL_INTERVAL      4  // in ms
#define USB_SOMATIC_POLL_INTERVAL    8  // in ms

#define USB_KEYBOARD_RELEASE_TIMEOUT (450000) // in us
#define USB_MOUSE_RELEASE_TIMEOUT    (200000) // in us
#define USB_SOMATIC_RELEASE_TIMEOUT  (200000) // in us

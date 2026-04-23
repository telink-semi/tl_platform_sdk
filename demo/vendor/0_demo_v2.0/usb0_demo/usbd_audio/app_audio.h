/********************************************************************************************************
 * @file    app_audio.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
 * @FilePath: \epm_driver\demo\usb2.0\usbd_audio_hs_v2\app_audio.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header for app_audio.c file.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __APP_AUDIO_H__
#define __APP_AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/**************************** include header *********************************/
#include "common.h"
#if (USB_DEMO_TYPE == USB_MIC_SPK)
#include "usbd_core.h"
#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define USBD_VID 0x2d99
#define USBD_PID 0xe032

#define USBD_LANGID_STRING 0x409

#define AUDIO_OUT_EP 0x03
#define AUDIO_IN_EP  0x83

#define HID_OUT_EP 0x01
#define HID_IN_EP  0x81

#define USBD_AUDIO_FREQ    48000
#define USBD_AUDIO_WIDTH   16
#define USBD_AUDIO_CHANNEL 2

#define USBD_MIC_FREQ    48000
#define USBD_MIC_WIDTH   16
#define USBD_MIC_CHANNEL 2

//#define UAC_OUT_PACKET_LEN (uint32_t)(((USBD_AUDIO_FREQ * (USBD_AUDIO_WIDTH / 8) * USBD_AUDIO_CHANNEL) / 1000))
//#define UAC_IN_PACKET_LEN  (uint32_t)(((USBD_MIC_FREQ * (USBD_MIC_WIDTH / 8) * USBD_MIC_CHANNEL) / 1000))
#define UAC_OUT_PACKET_LEN (48)
#define UAC_IN_PACKET_LEN  (24)

#define UAC_OUT_PACKET_NUM     10
#define UAC_IN_PACKET_NUM      10
#define SPEAKER_TOTAL_BUF_SIZE ((uint32_t)(UAC_OUT_PACKET_LEN * UAC_OUT_PACKET_NUM))
#define MIC_TOTAL_BUF_SIZE     ((uint32_t)(UAC_IN_PACKET_LEN * UAC_IN_PACKET_NUM))

#define CODEC_ADC_PORT (AUDIO_ADC_CH_0)
#define CODEC_DAC_PORT (AUDIO_DAC_CH_STEREO)

/**************************** type definition ********************************/

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
extern void usbd_audio_init(void);

#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

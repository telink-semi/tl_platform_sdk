/********************************************************************************************************
 * @file    usbd_mouse.h
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
 * @FilePath: \epm_driver\demo\usb2.0\usbd_mouse\usbd_mouse.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header for usbd_mouse.c file.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_MOUSE_H__
#define __USBD_MOUSE_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "common.h"
#if (USB_DEMO_TYPE == USB_MOUSE)
#include "usbd_core.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define USBD_VID 0x0483
#define USBD_PID 0x572B

#define USBD_LANGID_STRING 0x409

#define USB_CONFIG_DESC_SIZE (34)

#define USBD_CFG_MAX_NUM (1)

#define CUSTOM_HID_IN_EP (0x81) /* EP1 for data IN */

/**************************** type definition ********************************/

/************************* variable definition *******************************/

/**************************** function declear *******************************/
extern void usbd_mouse_init(void);
extern void usbd_mouse_test(void);

#endif

#ifdef __cplusplus
}
#endif

#endif
#endif

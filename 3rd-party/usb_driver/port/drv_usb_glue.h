/*******************************************************************************************************
 *
 * @file    drv_usb_glue.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
 * @FilePath: \epm_driver\driver\inc\drv_usb_glue.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header file for usb.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __DRV_USB_GLUE_H__
#define __DRV_USB_GLUE_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/*************************** macro definition ********************************/
#define USB_DMA_ADDR_OFFSET    (0x40000000UL)
#define USB_DMA_BUFF_ADDR_MASK (0xf0000000UL)

/**************************** type definition ********************************/

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
  * @brief  usb_drive_vbus
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */
extern void usb_drive_vbus(uint8_t state);
/**
* @brief  Read the Connector status of ConID through software
* @param  none
* @retval conidsts. USB_MODEA or USB_MODEB
*/
extern uint8_t usb_get_conidsts(void);
/**
* @brief  usb init
*
* @param  none
* @return none
* @note   none
*/
extern void usb_low_level_init(void);
/**
* @brief  usb deinit
*
* @param  none
* @return none
* @note   none
*/
extern void usb_low_level_deinit(void);
/**
* @brief  get mclk0 freq
*
* @param  none
* @return freq
* @note   none
*/
extern uint32_t usb_mclk0_g_freq(void);
/**
* @brief  This function provides delay time in milli sec
*
* @param  usec: Value of delay required in microsecond
* @return none
* @note   none
*/
extern void usb_delay_us(uint32_t usec);
/**
* @brief  This function provides delay time in milli sec
*
* @param  msec: Value of delay required in milli sec
* @return none
* @note   none
*/
extern void usb_delay_ms(uint32_t msec);

/**
* @brief  Initialize core registers address.
* @param  None
* @retval None
*/
extern void usb_regs_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __USB_CORE_H__ */

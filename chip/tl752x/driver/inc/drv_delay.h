/*******************************************************************************************************
 *
 * @file    drv_delay.h
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
#ifndef __DRV_DELAY_H__
#define __DRV_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"

extern void drv_delay_us(uint32_t us);
extern void drv_delay_ms(uint32_t ms);
extern uint32_t drv_delay_get_tick(void);
extern void drv_delay_increase_tick(void);

#ifdef __cplusplus
}
#endif

#endif
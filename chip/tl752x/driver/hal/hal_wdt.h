/********************************************************************************************************
 * @file    hal_wdt.h
 *
 * @brief   This is the header file for tl752x
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

#ifndef _HAL_WDT_H_
#define _HAL_WDT_H_

#include "bit.h"
#include "compiler.h"
#include "tl_chip.h"
#include "inc/drv_wdt.h"

void wd_32k_start(void);

void wd_32k_stop(void);

void wd_32k_init(void);

void wd_32k_deinit(wdt_handle_t *hwdt);

void wd_32k_clear(void);

void wd_32k_set_interval_ms( unsigned int timeout_ms);

unsigned char wd_32k_get_status(void);

void wd_32k_clear_status(void);

unsigned int wd_32k_get_tick(void);



#endif

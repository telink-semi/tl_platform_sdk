/*******************************************************************************************************
 *
 * @file    core.h
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
#ifndef _CORE_H_
#define _CORE_H_

#include "tl_chip.h"
#include "compiler.h"

/**
 * @brief       This function performs to set delay time by cclk tick.
 * @param[in]   core_cclk_tick - Number of ticks in cclk
 * @return      none
 */
_attribute_ram_code_sec_noinline_ void core_cclk_delay_tick(unsigned long long core_cclk_tick);

#endif

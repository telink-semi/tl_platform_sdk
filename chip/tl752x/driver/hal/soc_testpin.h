/********************************************************************************************************
 * @file    soc_testpin.h
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


#ifndef __SOC_TESTPIN_H__
#define __SOC_TESTPIN_H__

#include "tl_chip.h"

/**
 * @brief  output the selected clock with PA2.
 * @param  clk_type @ref cpr_dbg_clk_src_t.
 *        This parameter can be one of the following values:
 *            @arg CPR_DBG_CLK_SRC_MCLK0_G:
 *            @arg CPR_DBG_CLK_SRC_RC32K:
 *            @arg CPR_DBG_CLK_SRC_CODEC_6P144:
 *            @arg CPR_DBG_CLK_SRC_USB_PLL_12M:
 * @param  div, clk div value, the value range from 0 to 0xff
 */
extern void soc_testpin_clk_config(uint32_t clk_type, uint32_t div);

#endif

/********************************************************************************************************
 * @file    dpr_reg.h
 *
 * @brief   This is the header file for tl753x
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
#ifndef DPR_REG_H
#define DPR_REG_H
#include "soc.h"

#define DPR_BASE_ADDR (0x80140600)

#define reg_dpr_sts         REG_ADDR8(DPR_BASE_ADDR + 0x00)
#define reg_dpr_mode        REG_ADDR8(DPR_BASE_ADDR + 0x01)
#define reg_dpr_nxt_wait    REG_ADDR8(DPR_BASE_ADDR + 0x02)
#define reg_dpr_chn_en      REG_ADDR8(DPR_BASE_ADDR + 0x03)

#define reg_dpr_r_chn_cnt(i)   REG_ADDR16(DPR_BASE_ADDR + 0x40 + (i) * 2)

#endif


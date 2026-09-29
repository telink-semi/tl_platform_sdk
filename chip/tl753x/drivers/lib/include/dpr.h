/********************************************************************************************************
 * @file    dpr.h
 *
 * @brief   This is the header file for tl753x
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#ifndef DPR_H_
#define DPR_H_

#include "compiler.h"
#include "reg_include/register.h"

/**********************************************************************************************************************
 *                                         global constants                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           global macro                                                             *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                         global data type                                                           *
 *********************************************************************************************************************/
#define DPR_CHN_DEFAULT             0xcc    /* default channel 2/3/6/7 for tl753x */

/**********************************************************************************************************************
 *                                     global variable declaration                                                    *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                      global function prototype                                                     *
 *********************************************************************************************************************/
static _always_inline void dpr_trigger(void)
{
    reg_dpr_sts = 0x5;
}

static _always_inline void dpr_chn_enable(unsigned char chn_msk)
{
    reg_dpr_chn_en = chn_msk;
}

static _always_inline unsigned short dpr_r_chn_cnt_get(unsigned char chn)
{
    return (reg_dpr_r_chn_cnt(chn) & 0x3ff);
}

void dpr_init(void);

#endif

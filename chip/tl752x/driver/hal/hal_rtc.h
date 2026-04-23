/********************************************************************************************************
 * @file    hal_rtc.h
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

#ifndef _HAL_RTC_H_
#define _HAL_RTC_H_

#include "bit.h"
#include "compiler.h"

#include "driver.h"

static _always_inline void rtc_int_enable(void)
{
    SET_BIT(RTC->CCR, RTC_RTC_IEN);
}

static _always_inline void rtc_int_disable(void)
{
    CLEAR_BIT(RTC->CCR, RTC_RTC_IEN);
}

static _always_inline void rtc_wrap_enable(void)
{
    SET_BIT(RTC->CCR, RTC_RTC_WEN);
}

static _always_inline void rtc_wrap_disable(void)
{
    CLEAR_BIT(RTC->CCR, RTC_RTC_WEN);
}

static _always_inline void rtc_set_match_count(unsigned int val)
{
    WRITE_REG(RTC->CMR, val);
}

static _always_inline unsigned int rtc_get_val(void)
{
    return READ_REG(RTC->CCVR);
}

static _always_inline unsigned int rtc_get_intr_status(void)
{
    return READ_REG(RTC->STAT);
}

static _always_inline void rtc_reset(void)
{
    __DRV_CPR_RTC_CLK_DISABLE();
    __DRV_PMU_RTC_CLK_DISABLE();
}

void rtc_start_cnt(void);

#endif

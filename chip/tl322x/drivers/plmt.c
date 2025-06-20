/********************************************************************************************************
 * @file    plmt.c
 *
 * @brief   This is the source file for tl322x
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "plmt.h"

/**
 * @brief The mtime default frequency is 32k rc.
 *
 */
static volatile unsigned long mtime_clock_source = 0;

#if !defined(MCU_CORE_TL322X_N22) /* In CLIC mode, the MIE register is hardwired to zero. */
/**
 * @brief     This function servers to config d25f mtime clk source.
 * @param[in] src
 *              - CLK_32K_RC select 32k rc as the mtime clock source.
 *              - CLK_32K_XTAL select 32k xtal as the mtime clock source.
 * @return    none
 * @note      The source of mtime comes from 32K (set by the clock_32k_init interface), so mtimer clk is 32K.
 *            mtime precision is determined by the source.
 *            The source of mtime for other chip vendors may not be the same as telink.
 */
void mtime_clk_init(clk_32k_type_e src)
{
    reg_clk_en1 |= FLD_CLK1_MACHINETIME; //d25f mtimer clk is enabled by default
    if (src == CLK_32K_RC) {
        mtime_clock_source = 32000;      //CLK_32K_RC select 32k rc as the mtime clock source.   (clk=32000).
    } else {
        mtime_clock_source = 32768;      //CLK_32K_XTAL select 32k xtal as the mtime clock source. (clk=32768).
    }
}
#else
/**
 * @brief     This function servers to config n22 mtime clk source.
 *
 * @param[in] src
 *              - CLK_32K_RC select 32k rc as the mtime clock source.
 *              - CLK_32K_XTAL select 32k xtal as the mtime clock source.
 * @return    none
 * @note      The source of mtime comes from 32K (set by the clock_32k_init interface) and then doubled, so mtimer is 64K.
 *            mtime precision is determined by the source.
 *            The source of mtime for other chip vendors may not be the same as telink.
 */
void mtime_clk_init(clk_32k_type_e src)
{
    if (src == CLK_32K_RC) {
        mtime_clock_source = 64000; // CLK_32K_RC select 32k rc as the mtime clock source.     (clk=32000*2).
    } else {
        mtime_clock_source = 65536; // CLK_32K_XTAL select 32k xtal as the mtime clock source.  (clk=32768*2).
    }
}

#endif
/**
 * @brief     This function servers to get mtime value.
 * @return    The value of mtime
 */
_attribute_ram_code_sec_ unsigned long long mtime_get_value(void)
{
    while (1) {
        /* mtime is 64 bits, but mcu is 32bits, need to read twice and ensure that the high 32 bits no carry */
        unsigned int high_value = reg_mtime_high;
        unsigned int low_value  = reg_mtime_low;
        /* if no carry return immediately, else return next tick value */
        if (high_value == reg_mtime_high) {
            return ((unsigned long long)high_value << 32) | low_value;
        }
    }
}

/**
 * @brief     This function servers to set mtime value.
 * @param[in] value - The value of mtime.
 * @return    none
 */
_attribute_ram_code_sec_ void mtime_set_value(unsigned long long value)
{
    unsigned int high_value = (value >> 32) & 0xffffffff;
    unsigned int low_value  = value & 0xffffffff;

    reg_mtime_low  = 0;         /* sure no temporary values */
    reg_mtime_high = high_value;
    reg_mtime_low  = low_value; /* truly new values */
}

/**
 * @brief     This function servers to set mtimecmp value.
 * @param[in] value - The value of mtimecmp.
 * @return    none
 */
_attribute_ram_code_sec_ void mtime_set_cmp_value(unsigned long long value)
{
    unsigned int high_value = (value >> 32) & 0xffffffff;
    unsigned int low_value  = value & 0xffffffff;

    /* avoid spuriously generating an interrupt */
    reg_mtimecmp_low  = 0xffffffff; /* no smaller than old value */
    reg_mtimecmp_high = high_value; /* no smaller than old value */
    reg_mtimecmp_low  = low_value;  /* new value */
}

/**
 * @brief     This function servers to set the mtime trigger time.
 * @param[in] period_ms - The mtime trigger time, unit is millisecond.
 * @return    none
 */
_attribute_ram_code_sec_ void mtime_set_interval_ms(unsigned long long period_ms)
{
    mtime_set_cmp_value(mtime_get_value() + mtime_clock_source * period_ms / 1000);
}

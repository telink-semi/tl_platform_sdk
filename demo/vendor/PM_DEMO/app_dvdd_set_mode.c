/********************************************************************************************************
 * @file    app_dvdd_set_mode.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#include "compiler.h"

#if PM_SET_DVDD_MODE
volatile unsigned long                               pm_cal_24mrc_counter = 0;

void user_init(void)
{
    #if defined(MCU_CORE_TL7518)
    //Upward Voltage
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P9_CONFG, DMA8, D25F, 1000);
    CCLK_192M_HCLK_192M_PCLK_48M_MSPI_48M;    

    #elif defined(MCU_CORE_TL721X)
    pm_set_probe_vol_to_pd3(VDD_RAM);    
    //Upward Voltage
    pm_set_dvdd(CORE_0P9V_SRAM_0P9V_BB_0P9V, DMA1, 1000);
    PLL_240M_CCLK_240M_HCLK_120M_PCLK_120M_MSPI_48M;    

    #elif defined(MCU_CORE_TL751X)
    //Upward Voltage
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P9V, 1000);
    PLL_192M_D25F_DSP_192M_HCLK_96M_PCLK_48M_MSPI_48M_WT_12M;

    #elif defined(MCU_CORE_TL322X)
    //Upward Voltage
    pm_set_dig_ldo(DIG_VOL_1V1_MODE, 1000);
    PLL_192M_D25F_192M_HCLK_N22_96M_PCLK_96M_MSPI_48M;
    #endif    

    clock_cal_24m_rc();

    // init the LED pin, for indication
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_set_high_level(LED1);
    delay_ms(1000);
}

void main_loop(void)
{
    gpio_set_low_level(LED1);
    delay_ms(500);

    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER, stimer_get_tick() + 1000 * SYSTEM_TIMER_TICK_1MS);

    gpio_set_high_level(LED1);
    delay_ms(500);

    //(note: enter deep or deep_ret front, must Downward Voltage)
    #if defined(MCU_CORE_TL7518)
    //Downward Voltage
    CCLK_96M_HCLK_96M_PCLK_24M_MSPI_48M;
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P8_CONFG, DMA8, D25F, 1000);

    #elif defined(MCU_CORE_TL721X)
    pm_set_probe_vol_to_pd3(VDD_RAM);
    //Downward Voltage
    PLL_240M_CCLK_120M_HCLK_60M_PCLK_60M_MSPI_48M;
    pm_set_dvdd(CORE_0P8V_SRAM_0P8V_BB_0P8V, DMA1, 1000);

    #elif defined(MCU_CORE_TL751X)
    //Downward Voltage
    PLL_192M_D25F_DSP_96M_HCLK_48M_PCLK_48M_MSPI_48M_WT_12M;
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P8V, 1000);

    #elif defined(MCU_CORE_TL322X)
    //Downward Voltage
    PLL_144M_D25F_72M_HCLK_N22_36M_PCLK_36M_MSPI_48M;
    pm_set_dig_ldo(DIG_VOL_1V_MODE, 1000);
    #endif

    gpio_set_low_level(LED1);

    pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER, stimer_get_tick() + 1000 * SYSTEM_TIMER_TICK_1MS);
}

#endif


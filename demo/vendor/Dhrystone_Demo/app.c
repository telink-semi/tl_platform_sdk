/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#define CURRENT_PER_MHZ_TEST 0
#if !defined(MCU_CORE_TL321X) || (GPIO_TEST_MODE == MANUAL_TEST_MODE)

void user_init(void)
{
    #if defined(MCU_CORE_TL321X) && (CURRENT_PER_MHZ_TEST)
        #if (CLOCK_FREQUENCY == CCLK_24M_HCLK_12M_PCLK_12M)
    PLL_192M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_12M)
    PLL_192M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_48M_PCLK_24M)
    PLL_192M_CCLK_96M_HCLK_48M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_96M_HCLK_48M_PCLK_48M_MSPI_48M;
        #endif

    gpio_shutdown(GPIO_ALL);

    for (int i = 0; i < 10; i++) {
        dhry_main();
    }
    #elif defined(MCU_CORE_TL323X) && (CURRENT_PER_MHZ_TEST)
        #if (CLOCK_FREQUENCY == CCLK_24M_HCLK_12M_PCLK_12M)
    PLL_192M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_12M)
    PLL_192M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_96M_HCLK_48M_PCLK_48M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_96M_PCLK_48M)
    PLL_192M_CCLK_96M_HCLK_96M_PCLK_48M_MSPI_48M;
        #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
        #endif
    gpio_shutdown(GPIO_ALL);

    reg_rst      = 0x96b88080;
    reg_clk_en   = 0x1e30a080;

    reg_rst_1    = 0x00800004;
    reg_clk_en_1 = 0x00800044;

    for (int i = 0; i < 10; i++) {
        dhry_main();
    }
    #elif defined(MCU_CORE_TL521X) && (CURRENT_PER_MHZ_TEST)
#if (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_24M)
    PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_12M)
    PLL_144M_CCLK_24M_HCLK_24M_PCLK_12M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_6M)
    PLL_144M_CCLK_24M_HCLK_24M_PCLK_6M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_12M_PCLK_12M)
    PLL_144M_CCLK_24M_HCLK_12M_PCLK_12M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_12M_PCLK_6M)
    PLL_144M_CCLK_24M_HCLK_12M_PCLK_6M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_48M)
    PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_24M)
    PLL_144M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_24M)
    PLL_144M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_12M)
    PLL_144M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M;
#elif (CLOCK_FREQUENCY == CCLK_72M_HCLK_72M_PCLK_72M)
    PLL_144M_CCLK_72M_HCLK_72M_PCLK_72M_MSPI_72M;
#elif (CLOCK_FREQUENCY == CCLK_72M_HCLK_72M_PCLK_36M)
    PLL_144M_CCLK_72M_HCLK_72M_PCLK_36M_MSPI_72M;
#elif (CLOCK_FREQUENCY == CCLK_72M_HCLK_36M_PCLK_18M)
    PLL_144M_CCLK_72M_HCLK_36M_PCLK_18M_MSPI_36M;
#elif (CLOCK_FREQUENCY == CCLK_36M_HCLK_36M_PCLK_18M)
    PLL_144M_CCLK_36M_HCLK_36M_PCLK_18M_MSPI_36M;
#elif (CLOCK_FREQUENCY == CCLK_144M_HCLK_72M_PCLK_36M)
    PLL_144M_CCLK_144M_HCLK_72M_PCLK_36M_MSPI_48M;
#else
    PLL_144M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
#endif
    gpio_shutdown(GPIO_ALL);

    reg_rst      = 0x96b88080;
    reg_clk_en   = 0x1e30a080;

    reg_rst_1    = 0x00800004;
    reg_clk_en_1 = 0x00800044;

    for (int i = 0; i < 10; i++) {
       dhry_main();
    }
#elif defined(MCU_CORE_TL753X) && (CURRENT_PER_MHZ_TEST)
    #if (CLOCK_FREQUENCY == CCLK_24M_HCLK_12M_PCLK_12M)
    PLL_192M_D25F_DSP_24M_HCLK_12M_PCLK_12M_MSPI_48M_WT_12M;
    #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_12M)
    PLL_192M_CCLK_48M_HCLK_24M_PCLK_12M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_24M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_24M_HCLK_24M_PCLK_24M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_24M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_24M_PCLK_24M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_24M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_24M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_96M_HCLK_48M_PCLK_48M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_96M_HCLK_96M_PCLK_48M)
    PLL_192M_CCLK_96M_HCLK_96M_PCLK_48M_MSPI_48M;
    #elif (CLOCK_FREQUENCY == CCLK_48M_HCLK_48M_PCLK_48M)
    PLL_192M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
    #endif

     gpio_shutdown(GPIO_ALL);

    reg_rst      = 0x82380880;
    reg_clk_en   = 0x02300880;
    reg_rst_1    = 0x00000000;
    reg_clk_en_1 = 0x00000040;

    for (int i = 0; i < 10; i++) {
        dhry_main();
    }

    #else
    CLOCK_INIT;
    printf("\r\n\r\n Drystone Benchmark %d Starts ...", 1);
    dhry_main();
    #endif

    printf("\r\n[dhrystone] : %6.2f\r\n", Dhrystone_DMIPS_Per_MHz);
    delay_ms(100);

    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
}

void main_loop(void)
{
    delay_ms(200);
    gpio_toggle(LED2);
}

#endif

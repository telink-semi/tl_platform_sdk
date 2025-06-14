/********************************************************************************************************
 * @file    main.c
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
#include "coremark/core_portme.h"

extern void user_init(void);
extern void main_loop(void);
extern int  main_coremark(void);

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
extern float coremark_result;

volatile unsigned int cpu_mhz; /* Note:  This gets the current main frequency of the running cores,
                                if you find that the score data is not correct you can check this parameter.*/

#define STRINGIFY(x) #x
#define COMPARE_MACROS(a, b) (strcmp(STRINGIFY(a), STRINGIFY(b)) == 0)

void n22_get_cpu_clk(void)
{
#if defined(MCU_CORE_TL751X_N22)
    cpu_mhz = 48;
#endif

#if defined(MCU_CORE_TL7518_N22)
    cpu_mhz = 48;
#endif

#if defined(MCU_CORE_TL322X_N22)
if (COMPARE_MACROS(CLOCK_INIT,PLL_192M_CCLK_192M_HCLK_D25F_N22_96M_PCLK_96M_MSPI_64M)){
    cpu_mhz = 96;
}
else if(COMPARE_MACROS(CLOCK_INIT,PLL_192M_CCLK_96M_HCLK_D25F_N22_48M_PCLK_48M_MSPI_64M)){
    cpu_mhz = 48;
}
else if(COMPARE_MACROS(CLOCK_INIT,PLL_144M_CCLK_48M_HCLK_D25F_N22_48M_PCLK_48M_MSPI_48M)){
    cpu_mhz = 48;
}
else if(COMPARE_MACROS(CLOCK_INIT,PLL_144M_CCLK_72M_HCLK_D25F_N22_36M_PCLK_36M_MSPI_48M)){
    cpu_mhz = 36;
}
else if(COMPARE_MACROS(CLOCK_INIT,PLL_192M_CCLK_64M_HCLK_D25F_N22_32M_PCLK_32M_MSPI_48M)){
    cpu_mhz = 32;
}
else if(COMPARE_MACROS(CLOCK_INIT,PLL_192M_CCLK_48M_HCLK_D25F_N22_24M_PCLK_12M_MSPI_48M)){
    cpu_mhz = 24;
}
else if(COMPARE_MACROS(CLOCK_INIT,XTAL_24M_CCLK_24M_HCLK_D25F_N22_24M_PCLK_24M_MSPI_24M)){
    cpu_mhz = 24;
}
else if(COMPARE_MACROS(CLOCK_INIT,RC_24M_CCLK_24M_HCLK_D25F_N22_24M_PCLK_24M_MSPI_24M)){
    cpu_mhz = 24;
}
#endif

 printf("cpu_mhz = %d\r\n",cpu_mhz);
}


int main(void)
{
#if !(defined(MCU_CORE_TL7518_N22) || defined(MCU_CORE_TL751X_N22)|| defined(MCU_CORE_TL322X_N22))
    PLATFORM_INIT;
    CLOCK_INIT;
#endif
    user_init();
    printf("\r\n\r\n Core Mark Starts(wait about 10s~20s...) ...\r\n");
    delay_ms(100);

#if defined(MCU_CORE_TL7518)
    #if !defined(MCU_CORE_TL7518_N22)
    cpu_mhz = sys_clk.cclk_hclk;
    #else
    n22_get_cpu_clk();
    #endif
#elif defined(MCU_CORE_TL751X)
    #if !defined(MCU_CORE_TL751X_N22)
    cpu_mhz = sys_clk.cclk_d25f_dsp;
    #else
    n22_get_cpu_clk();
    #endif
#elif defined(MCU_CORE_TL322X)
    #if !defined(MCU_CORE_TL322X_N22)
    cpu_mhz = sys_clk.cclk;
    #else
    n22_get_cpu_clk();
    #endif
#else
    cpu_mhz = sys_clk.cclk;
#endif
    main_coremark();
    printf("coremark result = %f (%dM)\r\n", coremark_result, cpu_mhz);
    printf("coremark result/clk(Mhz) = %f \r\n", (coremark_result / cpu_mhz));
    while (1) {
        main_loop();
    }

    return 0;
}

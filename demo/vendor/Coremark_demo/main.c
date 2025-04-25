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
#include "app_config.h"
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

unsigned char cpu_mhz; /* Note:  This gets the current main frequency of the running cores,
                                if you find that the score data is not correct you can check this parameter.*/

int main(void)
{
#if !(defined(MCU_CORE_TL7518_N22) || defined(MCU_CORE_TL751X_N22))
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
    cpu_mhz = sys_clk.n22_clk;
    #endif
#elif defined(MCU_CORE_TL751X)
    #if !defined(MCU_CORE_TL751X_N22)
    cpu_mhz = sys_clk.cclk;
    #else
    cpu_mhz = sys_clk.n22_clk;
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

/********************************************************************************************************
 * @file    main.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
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


extern void user_init(void);
extern void main_loop(void);

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
#if defined(MCU_CORE_TL752X_D25F)
    PLATFORM_INIT;
#if  defined(MCU_CORE_TL752X)
    pm_set_ema(PM_EMA_CFG_HIGH_FREQ);
    CLOCK_INIT;
#elif defined(MCU_CORE_TL651X)
    flash_init();
#endif
#endif
    user_init();

    while (1) {
        main_loop();
    }
    return 0;
}


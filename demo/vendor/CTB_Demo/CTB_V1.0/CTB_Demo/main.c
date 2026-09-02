/********************************************************************************************************
 * @file    main.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2023, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 * @brief       This function serves to handle the interrupt of CTB.
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void pm_irq_handler(void)
{
    if (pm_get_wakeup_src() & WAKEUP_STATUS_COMPARATOR) {
        pm_clr_irq_status(WAKEUP_STATUS_COMPARATOR);
    }
    if (pm_get_wakeup_src() & BIT(5)) {
        pm_clr_irq_status(BIT(5));
    }
}
PLIC_ISR_REGISTER(pm_irq_handler, IRQ_PM_IRQ)

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
    PLATFORM_INIT;
    CLOCK_INIT;
    user_init();

    while (1) {
        main_loop();
    }
    return 0;
}

/********************************************************************************************************
 * @file    main.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"

extern void  user_init(void);
extern void  main_loop(void);
volatile int timer_bb0_irq_cnt = 0;
volatile int timer_bb1_irq_cnt = 0;
volatile int timer_bb2_irq_cnt = 0;

_attribute_ram_code_sec_ void timer_bb_irq_handler(void)
{
#if (TIMER_BB_MODE == TIMER_BB_SYS_CLOCK_MODE)
    if (timer_bb_get_irq_status(TIMER_BB0_IRQ)) {
        timer_bb_clr_irq_status(TIMER_BB0_IRQ);
        gpio_toggle(LED2);
        timer_bb0_irq_cnt++;
    }
    if (timer_bb_get_irq_status(TIMER_BB1_IRQ)) {
        timer_bb_clr_irq_status(TIMER_BB1_IRQ);
        gpio_toggle(LED3);
        timer_bb1_irq_cnt++;
    }
    if (timer_bb_get_irq_status(TIMER_BB2_IRQ)) {
        timer_bb_clr_irq_status(TIMER_BB2_IRQ);
        gpio_toggle(LED4);
        timer_bb2_irq_cnt++;
    }
#endif
}
CLIC_ISR_REGISTER(timer_bb_irq_handler, IRQ_TIMER_BB)

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
    user_init();

    while (1) {
        main_loop();
    }

    return 0;
}

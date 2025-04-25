/********************************************************************************************************
 * @file    app.c
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
#include <printf.h>
/**************************notices******************************************
 * ********timer_bb clock use N22 clock(HCLK1) ******************/

/**
 * N22_CLK frequency is managed by D25F, D25F default configuration of  N22_CLK is 48M Hz,
 * if D25F changes its configuration, you need to change it here as well.
 */
#define N22_CLK_MHZ 48

volatile unsigned int t0;

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_function_en(LED2);
    gpio_function_en(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED1);
    gpio_output_en(LED2);
    gpio_output_en(LED3);
    gpio_output_en(LED4);

#if (TIMER_BB_MODE == TIMER_BB_SYS_CLOCK_MODE)
    clic_interrupt_vector_en(IRQ_TIMER_BB);
    clic_interrupt_enable(IRQ_TIMER_BB);
    core_interrupt_enable();

    timer_bb_set_init_tick(TIMER_BB0, 0);
    timer_bb_set_cap_tick(TIMER_BB0, 50 * N22_CLK_MHZ * 1000);
    timer_bb_set_init_tick(TIMER_BB1, 0);
    timer_bb_set_cap_tick(TIMER_BB1, 50 * N22_CLK_MHZ * 1000);
    timer_bb_set_init_tick(TIMER_BB2, 0);
    timer_bb_set_cap_tick(TIMER_BB2, 50 * N22_CLK_MHZ * 1000);

    timer_bb_set_mode(TIMER_BB0, TIMER_BB_MODE_SYSCLK);
    timer_bb_set_mode(TIMER_BB1, TIMER_BB_MODE_SYSCLK);
    timer_bb_set_mode(TIMER_BB2, TIMER_BB_MODE_SYSCLK);

    timer_bb_set_irq_mask(TIMER_BB0_IRQ);
    timer_bb_set_irq_mask(TIMER_BB1_IRQ);
    timer_bb_set_irq_mask(TIMER_BB2_IRQ);

    timer_bb_start(TIMER_BB0);
    timer_bb_start(TIMER_BB1);
    timer_bb_start(TIMER_BB2);

#elif (TIMER_BB_MODE == TIMER_BB_TICK_MODE)
    timer_bb_set_init_tick(TIMER_BB0, 0);
    timer_bb_set_cap_tick(TIMER_BB0, 0);
    timer_bb_set_mode(TIMER_BB0, TIMER_BB_MODE_TICK); //cpu clock tick.
    timer_bb_start(TIMER_BB0);

    timer_bb_set_init_tick(TIMER_BB1, 0);
    timer_bb_set_cap_tick(TIMER_BB1, 0);
    timer_bb_set_mode(TIMER_BB1, TIMER_BB_MODE_TICK); //cpu clock tick.
    timer_bb_start(TIMER_BB1);

    timer_bb_set_init_tick(TIMER_BB2, 0);
    timer_bb_set_cap_tick(TIMER_BB2, 0);
    timer_bb_set_mode(TIMER_BB2, TIMER_BB_MODE_TICK); //cpu clock tick.
    timer_bb_start(TIMER_BB2);

#endif
}

void main_loop(void)
{
#if (TIMER_BB_MODE == TIMER_BB_TICK_MODE)
    if (timer_bb_get_tick(TIMER_BB0) > 500 * N22_CLK_MHZ * 1000) {
        timer_bb_set_tick(TIMER_BB0, 0);
        gpio_toggle(LED2);
    }
    if (timer_bb_get_tick(TIMER_BB1) > 500 * N22_CLK_MHZ * 1000) {
        timer_bb_set_tick(TIMER_BB1, 0);
        gpio_toggle(LED3);
    }
    if (timer_bb_get_tick(TIMER_BB2) > 500 * N22_CLK_MHZ * 1000) {
        timer_bb_set_tick(TIMER_BB2, 0);
        gpio_toggle(LED4);
    }
#endif

    delay_ms(500);
    gpio_toggle(LED1);
}

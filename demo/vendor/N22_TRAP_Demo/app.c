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
#if ((TRAP_DEMO == INTERRUPT_NON_NESTED_DEMO) || (TRAP_DEMO == INTERRUPT_NESTED_DEMO))
void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);

    gpio_function_en(LED2);
    gpio_output_en(LED2);

    gpio_function_en(LED4);
    gpio_output_en(LED4);

    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_set_low_level(LED1);
    gpio_set_low_level(LED2);
    gpio_set_low_level(LED4);


    core_interrupt_enable();
    clic_init();
    #if (TRAP_DEMO == INTERRUPT_NESTED_DEMO)
    clic_preempt_feature_en();
    clic_set_priority(IRQ_SYSTIMER, IRQ_PRI_LEV3);
    clic_set_priority(IRQ_MTIMER, IRQ_PRI_LEV1);
    #endif
    /* stimer init. */
    clic_interrupt_enable(IRQ_SYSTIMER);
    stimer_set_irq_capture_n22(stimer_get_tick() + (SYSTEM_TIMER_TICK_1MS));
    #if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_n22(FLD_SYSTEM_IRQ_MASK_N22);
    #elif defined(MCU_CORE_TL751X)
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_N22);
    #endif

    /* 32K initialized and calibrated . If 32k is already at d25, there is no need to call it here.*/
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc();
    /* machine timer  init. */
    clic_interrupt_enable(IRQ_MTIMER); /* enable machine time interrupt */
    mtime_clk_init(CLK_32K_RC);
    mtime_set_interval_ms(1);          /* set mtime interval */
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(200);
}

_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_n22()) {
        stimer_clr_irq_status_n22();
    #elif defined(MCU_CORE_TL751X)
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_N22)) {
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_N22);
    #endif
        gpio_set_high_level(LED2);
        delay_us(300);
        gpio_set_low_level(LED2);
        stimer_set_irq_capture_n22(stimer_get_tick() + SYSTEM_TIMER_TICK_1MS);
    }
}
CLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

_attribute_ram_code_sec_ void mtime_irq_handler(void)
{
    mtime_set_interval_ms(1);
    gpio_set_high_level(LED4);
    delay_us(250);
    gpio_set_low_level(LED4);
}
CLIC_ISR_REGISTER(mtime_irq_handler, IRQ_MTIMER)


#elif (TRAP_DEMO == INTERRUPT_MTIME_DEMO)
void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);

    gpio_function_en(LED2);
    gpio_output_en(LED2);

    gpio_function_en(LED4);
    gpio_output_en(LED4);

    gpio_function_en(LED4);
    gpio_output_en(LED4);

    gpio_function_en(KEY2);
    gpio_output_en(KEY2);


    gpio_set_low_level(LED1);
    gpio_set_low_level(LED2);
    gpio_set_low_level(LED4);
    gpio_set_low_level(KEY2);

    /* machine timer belongs to the CLIC, so need to initialize the CLIC. */
    clic_init();


    /* 32K initialized and calibrated . If 32k is already at d25, there is no need to call it here.*/
    /* clock_32k_init(CLK_32K_RC);
     clock_cal_32k_rc();*/

    /* mtime clk init */
    mtime_clk_init(CLK_32K_RC);

    /* enable global interrupt */
    core_interrupt_enable();

    /* enable machine time interrupt */
    clic_interrupt_enable(IRQ_MTIMER);

    /* set mtime interval */
    mtime_set_interval_ms(500);
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1); /* indicate software is run */
}

/**
 * @brief     mtime irq handler.
 * @return    none
 */
_attribute_ram_code_sec_ void mtime_irq_handler(void)
{
    /* update the timer to specified period */
    mtime_set_interval_ms(500);
    gpio_toggle(LED4);
}
CLIC_ISR_REGISTER(mtime_irq_handler, IRQ_MTIMER)
#endif

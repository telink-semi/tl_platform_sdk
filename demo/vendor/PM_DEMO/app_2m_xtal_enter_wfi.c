/********************************************************************************************************
 * @file    app_2m_xtal_enter_wfi.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#if defined(MCU_CORE_TL322X) && (PM_DEMO_MODE == PM_2M_WFI_MODE)

void user_init(void)
{
    delay_ms(500);
    XTAL_24M_D25F_24M_HCLK_N22_24M_PCLK_24M_MSPI_24M;

    clock_cal_24m_rc();

    // init the LED pin, for indication
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_set_high_level(LED1);
    delay_ms(500);

    stimer_set_irq_capture_d25f(stimer_get_tick() + 2 * SYSTEM_TIMER_TICK_1S); //set capture tick
    stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_MASK_D25F);
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();
}

void main_loop(void)
{
    gpio_set_low_level(LED1);
    delay_ms(20);

    pm_enter_wfi_optimization(); /*65-75us*/

    //TODO:Added pll flag bit check
    /*Before use pll, must check pll flag bit */

    gpio_set_high_level(LED1);
    delay_ms(20);
}


_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    if (stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_D25F))
    {
        pm_exit_wfi_optimization(); /*79-81us*/

        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_D25F);
        stimer_set_irq_capture_d25f(stimer_get_tick() + 1 * SYSTEM_TIMER_TICK_1S);
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

#endif

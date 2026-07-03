/********************************************************************************************************
 * @file    app_stimer.c
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
#include "pem.h"

#define CAPT_DMA_CNT 200
volatile unsigned int stimer_cnt                                                      = 0;
volatile unsigned int curr_capt_val                                                   = 0;
volatile unsigned int last_capt_val                                                   = 0;
volatile unsigned int diff_capt_val[CAPT_DMA_CNT]                                     = {0};
unsigned int          stimer_capt_dma_buff[CAPT_DMA_CNT] __attribute__((aligned(4)))  = {0};
unsigned int          stimer_capt_dma0_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
unsigned int          stimer_capt_dma1_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
volatile unsigned int stimer_capt_step_val[CAPT_DMA_CNT];



_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_D25F)) {
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_D25F);
        stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
        gpio_toggle(LED1);
    }
    #else
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ)) {
        stimer_clr_irq_status(FLD_SYSTEM_IRQ);
        stimer_set_irq_capture(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
        gpio_toggle(LED1);
    }
    #endif

    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT)) {
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT);
    #else
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_CAPT)) {
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_CAPT);
    #endif
        if (stimer_cnt == 0)
        {
            #if defined(MCU_CORE_TL721X)
            gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
            #else
            gpio_clr_irq_status(GPIO_IRQ_IRQ1);
            #endif

            last_capt_val = stimer_get_input_capt_value();
            stimer_cnt++;
        }
        else if ((stimer_cnt > 0) && (stimer_cnt <= (CAPT_DMA_CNT / 2)))
        {
            #if defined(MCU_CORE_TL721X)
            gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
            #else
            gpio_clr_irq_status(GPIO_IRQ_IRQ1);
            #endif
            curr_capt_val                 = stimer_get_input_capt_value();
            diff_capt_val[stimer_cnt - 1] = curr_capt_val - last_capt_val;
            last_capt_val                 = curr_capt_val;
            stimer_cnt++;
        }
    }
    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_OVERFLOW)) {
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT);
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_OVERFLOW);
    #else
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_OVERFLOW)) {
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_CAPT);
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_OVERFLOW);
    #endif

        #if defined(MCU_CORE_TL721X)
        gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
        #else
        gpio_clr_irq_status(GPIO_IRQ_IRQ1);
        #endif

        if ((stimer_cnt > (CAPT_DMA_CNT / 2)) && (stimer_cnt <= CAPT_DMA_CNT)) {
            curr_capt_val                 = stimer_get_input_capt_value();
            diff_capt_val[stimer_cnt - 1] = curr_capt_val - last_capt_val;
            last_capt_val                 = curr_capt_val;
        }
        stimer_cnt++;
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

void pem_event_stimer_init(unsigned char pem_id, unsigned char stimer_sel)
{
    switch (stimer_sel)
    {
    #if defined(MCU_CORE_TL322X)
    case STIMER_EVENT_TRIG_POS:
        stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
        stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_MASK_D25F);
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        break;

    case STIMER_EVENT_TRIG_POS_1:
        stimer_set_irq_capture_n22(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
        stimer_set_irq_mask_n22(FLD_SYSTEM_IRQ_MASK_N22);
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        break;

    #else
    case STIMER_EVENT_TRIG_POS:
        stimer_set_irq_capture(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
        stimer_set_irq_mask(FLD_SYSTEM_IRQ_MASK);
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        break;
    #endif

    case STIMER_EVENT_CAL_TGL_PUL:
        break;

    case STIMER_EVENT_CAPT:
        pwm1_init(PWM1_PIN);
        pwm_start(FLD_PWM1_EN);
        gpio_function_en(STIMER_CAPT_PIN);
        gpio_input_en(STIMER_CAPT_PIN);
        stimer_set_input_capt_pin(STIMER_CAPT_PIN, CAPT_RISING_EDGE);
        #if defined(MCU_CORE_TL322X)
        stimer_set_irq_mask_d25f(FLD_SYSTEM_CAPT_IRQ_MASK);
        #else
        stimer_set_irq_mask(FLD_SYSTEM_CAPT_IRQ_MASK);
        #endif
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        break;

    case STIMER_EVENT_OV:
        pwm1_init(PWM1_PIN);
        pwm_start(FLD_PWM1_EN);
        gpio_function_en(STIMER_CAPT_PIN);
        gpio_input_en(STIMER_CAPT_PIN);
        stimer_set_input_capt_pin(STIMER_CAPT_PIN, CAPT_RISING_EDGE);
        #if defined(MCU_CORE_TL322X)
        stimer_set_irq_mask_d25f(FLD_SYSTEM_CAPT_IRQ_MASK | FLD_SYSTEM_OVERFLOW_IRQ_MASK);
        #else
        stimer_set_irq_mask(FLD_SYSTEM_CAPT_IRQ_MASK | FLD_SYSTEM_OVERFLOW_IRQ_MASK);
        #endif
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        break;

    default:
        break;
    }

    stimer_set_pem_event(pem_id, stimer_sel);
}

int pem_event_stimer_start(unsigned char stimer_sel)
{
    switch (stimer_sel)
    {
    #if defined(MCU_CORE_TL322X)
    case STIMER_EVENT_TRIG_POS:
        stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
        break;

    case STIMER_EVENT_TRIG_POS_1:
        stimer_set_irq_capture_n22(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
        break;

    #else
    case STIMER_EVENT_TRIG_POS:
        stimer_set_irq_capture(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
        break;
    #endif

    case STIMER_EVENT_CAL_TGL_PUL:
        break;

    case STIMER_EVENT_CAPT:
        stimer_set_input_capt_enable();
        break;

    case STIMER_EVENT_OV:
        stimer_set_input_capt_enable();
        break;

    default:
        break;
    }
    return 1;
}

void pem_task_stimer_init(unsigned char pem_id, unsigned char stimer_sel)
{
    switch (stimer_sel)
    {
    case STIMER_TASK_EN:
        stimer_disable();
        break;

    case STIMER_TASK_DIS:
        stimer_disable();
        stimer_enable(STIMER_MANUAL_MODE, 0);
        gpio_toggle(LED1);
        delay_ms(500);
        gpio_toggle(LED1);
        delay_ms(500);
        gpio_toggle(LED1);
        break;

    case STIMER_TASK_CAPT:
        #if defined(MCU_CORE_TL322X)
        stimer_set_irq_mask_d25f(FLD_SYSTEM_CAPT_IRQ_MASK);
        #else
        stimer_set_irq_mask(FLD_SYSTEM_CAPT_IRQ_MASK);
        #endif
        plic_interrupt_enable(IRQ_SYSTIMER);
        core_interrupt_enable();
        stimer_set_input_capt_enable();

        break;

    default:
        break;
    }

    stimer_set_pem_task(pem_id, stimer_sel);
}

int pem_task_stimer_mainloop(unsigned char stimer_sel)
{
    switch (stimer_sel)
    {
    case STIMER_TASK_EN:
        delay_ms(500);
        gpio_toggle(LED1);
        break;

    case STIMER_TASK_DIS:
        delay_ms(500);
        gpio_toggle(LED1);
        break;

    case STIMER_TASK_CAPT:
        break;

    default:
        break;
    }
    return 1;
}

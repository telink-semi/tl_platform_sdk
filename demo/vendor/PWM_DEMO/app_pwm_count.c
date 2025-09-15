/********************************************************************************************************
 * @file    app_pwm_count.c
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

#if (SET_PWM_MODE == PWM_COUNT)

    #if defined(MCU_CORE_B91)
        #define PWM_PIN (PWM_PWM0_PB4)
        #define PWM_ID  (get_pwmid(PWM_PIN))
    #elif defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)|| defined(MCU_CORE_TL323X)
        #define PWM_ID   PWM0_ID
        #define PWM_PIN  GPIO_FC_PB4
        #define PWM_FUNC PWM0

    #elif defined(MCU_CORE_TL7518)
        #define PWM_ID   PWM0_ID
        #define PWM_PIN  PWM_PWM0_PA0
        #define PWM_FUNC FC_PWM0

    #elif defined(MCU_CORE_TL751X)
        #define PWM_ID   PWM0_ID
        #define PWM_PIN  GPIO_FC_PB5
        #define PWM_FUNC PWM0
    #elif defined(MCU_CORE_TL322X)
        #define PWM_ID   PWM0_ID
        #define PWM_PIN  GPIO_FC_PB3
        #define PWM_FUNC PWM0
    #endif
    /*
 *  pwm_clk_source is pclk or 32K
 *  note: PWM_32K only supports continue and count modes.
 */
    #define PWM_PCLK 1
    #define PWM_32K  2 //If want to work properly in suspend mode (the wake source:32K_rc/32k_crystal), can set the PWM to use the 32K clock source.
    #define PWM_CLK  PWM_PCLK

    /*
 *  Set interrupt mode
 */
    #define COUNT_FRAME_INIT    1
    #define COUNT_PNUM_INIT     2
    #define SET_COUNT_INIT_MODE COUNT_PNUM_INIT


    #define PWM_PULSE_NUM       0x20

_attribute_ram_code_sec_ void pwm_irq_handler(void)
{
#if !defined(MCU_CORE_TL322X)
    if (pwm_get_irq_status(FLD_PWM0_PNUM_IRQ | FLD_PWM0_FRAME_DONE_IRQ)) {
        pwm_clr_irq_status(FLD_PWM0_PNUM_IRQ | FLD_PWM0_FRAME_DONE_IRQ);
#else
    if (pwm_get_irq_status(PWM_ID, FLD_PWM0_PNUM_IRQ | FLD_PWM0_FRAME_DONE_IRQ)){
        pwm_clr_irq_status(PWM_ID, FLD_PWM0_PNUM_IRQ | FLD_PWM0_FRAME_DONE_IRQ);
#endif
        gpio_toggle(LED2);
    }
}
PLIC_ISR_REGISTER(pwm_irq_handler, IRQ_PWM)

void user_init(void)
{
    delay_ms(2000);
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    #if defined(MCU_CORE_B91)
    pwm_set_pin(PWM_PIN);
    #else
    pwm_set_pin(PWM_PIN, PWM_FUNC);
    #endif

    #if (SET_COUNT_INIT_MODE == COUNT_FRAME_INIT)
        #if (!((PWM_CLK == PWM_32K) && defined(MCU_CORE_B91)))
    //In eagle count mode,using 32k clock source, PWM_FRAME_DONE_IRQ interrupt have problem,not Recommended.
    //In B92, the issue has been fixed.
#if !defined(MCU_CORE_TL322X)
    pwm_set_irq_mask(FLD_PWM0_FRAME_DONE_IRQ);
#else
    pwm_set_irq_mask(PWM_ID, FLD_PWM0_FRAME_DONE_IRQ);
#endif

    pwm_clr_irq_status(FLD_PWM0_FRAME_DONE_IRQ);

    core_interrupt_enable();

    plic_interrupt_enable(IRQ_PWM);
        #endif

    #elif (SET_COUNT_INIT_MODE == COUNT_PNUM_INIT)
        #if (!((PWM_CLK == PWM_32K) && defined(MCU_CORE_B91)))
    //In eagle count mode,using 32k clock source, PWM_PNUM_IRQ interrupt have problem,not Recommended.
    //In B92, the issue has been fixed.
#if !defined(MCU_CORE_TL322X)
    pwm_set_irq_mask(FLD_PWM0_PNUM_IRQ);
    pwm_clr_irq_status(FLD_PWM0_PNUM_IRQ);
#else
    pwm_set_irq_mask(PWM_ID, FLD_PWM0_PNUM_IRQ);
    pwm_clr_irq_status(PWM_ID, FLD_PWM0_PNUM_IRQ);
#endif

    core_interrupt_enable();

    plic_interrupt_enable(IRQ_PWM);
        #endif
    #endif


    pwm_set_pwm0_mode(PWM_COUNT_MODE);

    pwm_set_pwm0_pulse_num(PWM_PULSE_NUM);

    #if (PWM_CLK == PWM_PCLK)
    pwm_set_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / PWM_PCLK_SPEED - 1));

    pwm_set_tcmp(PWM_ID, 50 * CLOCK_PWM_CLOCK_1US);

    pwm_set_tmax(PWM_ID, 100 * CLOCK_PWM_CLOCK_1US);


    #elif (PWM_CLK == PWM_32K)

    //there are two 32K clock sources, 32K_RC and 32K_Crystal.
    //if want higher 32K clock source accuracy, need to calibrate it.
    clock_32k_init(CLK_32K_RC);

    clock_cal_32k_rc();

#if !defined(MCU_CORE_TL322X)
    pwm_32k_chn_en(PWM_CLOCK_32K_CHN_PWM0);
#else
    pwm_32k_chn_en(PWM_ID);
#endif

    pwm_set_tcmp(PWM_ID, 1 * CLOCK_PWM_32K_1MS);

    pwm_set_tmax(PWM_ID, 2 * CLOCK_PWM_32K_1MS);

    #endif
    pwm_start(FLD_PWM0_EN);
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}

#endif

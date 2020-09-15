/********************************************************************************************************
 * @file	app_pwm_count.c
 *
 * @brief	This is the source file for B91
 *
 * @author	D.M.H / Z.S.X
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#include "app_config.h"

#if(SET_PWM_MODE== PWM_COUNT)

#define PWM_PIN		(PWM_PWM0_PB4)
#define PWM_ID		(get_pwmid(PWM_PIN))

/*
 *  pwm_clk_source is pclk or 32K
 */
#define	 PWM_PCLK		       1
#define	 PWM_32K  	           2
#define  PWM_CLK             PWM_PCLK

/*
 *  Set interrupt mode
 */
#define COUNT_FRAME_INIT    1
#define COUNT_PNUM_INIT     2
#define SET_COUNT_INIT_MODE  COUNT_FRAME_INIT


#define PWM_PULSE_NUM	0x20


void pwm_irq_handler(void)
{
	if(pwm_get_irq_status(FLD_PWM0_PNUM_IRQ|FLD_PWM0_FRAME_DONE_IRQ ))
	{
	  pwm_clr_irq_status(FLD_PWM0_PNUM_IRQ|FLD_PWM0_FRAME_DONE_IRQ);

	  gpio_toggle(LED4);
	}

}


void user_init(void)
{

	delay_ms(2000);
	gpio_function_en(LED2|LED3|LED4);
    gpio_output_en(LED2|LED3|LED4);
    gpio_input_dis(LED2|LED3|LED4);

#if (PWM_CLK  == PWM_PCLK)

	#if (SET_COUNT_INIT_MODE   == COUNT_FRAME_INIT )

		pwm_set_pin(PWM_PIN);

		pwm_set_clk((unsigned char) (sys_clk.pclk*1000*1000/PWM_PCLK_SPEED-1));

		pwm_set_tcmp(PWM_ID,50 * CLOCK_PWM_CLOCK_1US);

		pwm_set_tmax(PWM_ID,100 * CLOCK_PWM_CLOCK_1US);

		pwm_set_pwm0_mode(PWM_COUNT_MODE);

		pwm_set_pwm0_pulse_num(PWM_PULSE_NUM);

		pwm_set_irq_mask(FLD_PWM0_FRAME_DONE_IRQ);

		pwm_clr_irq_status(FLD_PWM0_FRAME_DONE_IRQ);

		core_interrupt_enable();

		plic_interrupt_enable(IRQ16_PWM);

		pwm_start(PWM_ID);

	#elif (SET_COUNT_INIT_MODE   == COUNT_PNUM_INIT)

		pwm_set_pin(PWM_PIN);

		pwm_set_clk((unsigned char) (sys_clk.pclk*1000*1000/PWM_PCLK_SPEED-1));

		pwm_set_tcmp(PWM_ID,50 * CLOCK_PWM_CLOCK_1US);

		pwm_set_tmax(PWM_ID,100 * CLOCK_PWM_CLOCK_1US);

		pwm_set_pwm0_mode(PWM_COUNT_MODE);

		pwm_set_pwm0_pulse_num(PWM_PULSE_NUM);

		pwm_set_irq_mask(FLD_PWM0_PNUM_IRQ);

		pwm_clr_irq_status(FLD_PWM0_PNUM_IRQ );

		core_interrupt_enable();

		plic_interrupt_enable(IRQ16_PWM);

		pwm_start(PWM_ID);
	 #endif

#elif(PWM_CLK  == PWM_32K)

	pwm_set_pin(PWM_PIN);

    pwm_32k_chn_en(PWM_CLOCK_32K_CHN_PWM0);

    pwm_set_pwm0_pulse_num(PWM_PULSE_NUM);

    pwm_set_tcmp(PWM_ID,1 * CLOCK_PWM_32K_1MS);

    pwm_set_tmax(PWM_ID,2 * CLOCK_PWM_32K_1MS);

    pwm_set_pwm0_mode(PWM_COUNT_MODE);

    pwm_start(PWM_ID);

#endif
}


void main_loop(void)
{
	 delay_ms(500);
	 gpio_toggle(LED1);
}

#endif

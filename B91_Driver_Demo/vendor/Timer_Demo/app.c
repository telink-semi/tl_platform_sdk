/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91
 *
 * @author	Driver Group
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
/**************************notices******************************************
 * ********timer clock use APB clock ******************/
#define TIMER_MODE_GPIO_TRIGGER_TICK    0x01
volatile unsigned int t0;


void user_init(void)
{
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);

#if (TIMER_MODE == TIMER_SYS_CLOCK_MODE)
	plic_interrupt_enable(IRQ4_TIMER0);
	plic_interrupt_enable(IRQ3_TIMER1);
	core_interrupt_enable();
	timer_set_init_tick(TIMER0,0);
	timer_set_cap_tick(TIMER0,50*sys_clk.pclk*1000);
	timer_set_init_tick(TIMER1,0);
	timer_set_cap_tick(TIMER1,50*sys_clk.pclk*1000);
	timer_set_mode(TIMER0, TIMER_MODE_SYSCLK);
	timer_set_mode(TIMER1, TIMER_MODE_SYSCLK);
	timer_start(TIMER1);
	timer_start(TIMER0);

#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

	core_interrupt_enable();
	plic_interrupt_enable(IRQ4_TIMER0);
	plic_interrupt_enable(IRQ3_TIMER1);

	gpio_function_en(GPIO_PA2|GPIO_PA3);
	gpio_output_en(GPIO_PA2|GPIO_PA3);
	gpio_set_low_level(GPIO_PA2|GPIO_PA3);

	/****  timer0 POL_RISING  SW1 link PA2  **/
	timer_gpio_init(TIMER0, SW1,POL_RISING);
	timer_set_init_tick(TIMER0,0);
	timer_set_cap_tick(TIMER0,TIMER_MODE_GPIO_TRIGGER_TICK);
	timer_set_mode(TIMER0, TIMER_MODE_GPIO_TRIGGER);
	timer_start(TIMER0);

	/****  timer1  POL_RISING  SW2 link PA3  **/
	timer_gpio_init(TIMER1, SW2,POL_RISING);
	timer_set_init_tick(TIMER1,0);
	timer_set_cap_tick(TIMER1,TIMER_MODE_GPIO_TRIGGER_TICK);
	timer_set_mode(TIMER1, TIMER_MODE_GPIO_TRIGGER);
	timer_start(TIMER1);

#elif(TIMER_MODE == TIMER_GPIO_WIDTH_MODE)

	core_interrupt_enable();
	plic_interrupt_enable(IRQ4_TIMER0);
	plic_interrupt_enable(IRQ3_TIMER1);

	gpio_function_en(GPIO_PA2|GPIO_PA3);
	gpio_output_en(GPIO_PA2|GPIO_PA3);

	/****  timer0 POL_FALLING  SW1 link PA2  **/
	gpio_set_high_level(GPIO_PA2);
	delay_ms(50);
	timer_gpio_init(TIMER0, SW1, POL_FALLING);
	timer_set_init_tick(TIMER0,0);
	timer_set_cap_tick(TIMER0,0);
	timer_set_mode(TIMER0, TIMER_MODE_GPIO_WIDTH);
	timer_start(TIMER0);
	gpio_set_low_level(GPIO_PA2);
	delay_ms(250);
	gpio_set_high_level(GPIO_PA2);

	/****  timer1  POL_RISING  SW2 link PA3  **/
	gpio_set_low_level(GPIO_PA3);
	delay_ms(50);
	timer_gpio_init(TIMER1, SW2, POL_RISING);
	timer_set_init_tick(TIMER1,0);
	timer_set_cap_tick(TIMER1,0);
	timer_set_mode(TIMER1, TIMER_MODE_GPIO_WIDTH);
	timer_start(TIMER1);
	gpio_set_high_level(GPIO_PA3);
	delay_ms(250);
	gpio_set_low_level(GPIO_PA3);

#elif(TIMER_MODE == TIMER_TICK_MODE)
	timer_set_init_tick(TIMER0,0);
	timer_set_cap_tick(TIMER0,0);
	timer_set_mode(TIMER0, TIMER_MODE_TICK);//cpu clock tick.
	timer_start(TIMER0);

#elif(TIMER_MODE == TIMER_WATCHDOG_MODE)

	wd_set_interval_ms(1000);
	wd_start();

#endif
}


void main_loop(void)
{
#if(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

	gpio_toggle(GPIO_PA2|GPIO_PA3);

#elif(TIMER_MODE == TIMER_TICK_MODE)

	if(timer0_get_tick() > 500 * sys_clk.pclk*1000)
	{
		timer0_set_tick(0);
		gpio_toggle(LED2|LED3);
	}

#endif

#if(TIMER_MODE == TIMER_WATCHDOG_MODE)

	delay_ms(990);
	wd_clear_cnt();
	gpio_toggle(LED2);

#else

	delay_ms(500);
	gpio_toggle(LED1);

#endif
}


/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91m
 *
 * @author	Driver Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#include "app_config.h"

void user_init()
{
#if(MCU_CORE_B91|MCU_CORE_B92)
	delay_ms(2000);

#if(GPIO_MODE == GPIO_HIGH_RESISTOR)
	gpio_shutdown(GPIO_ALL);//set all gpio as high resistor except sws and mspi

#else
	gpio_function_en(LED1);
	gpio_function_en(LED2);
	gpio_function_en(LED3);
	gpio_function_en(LED4);

	gpio_output_en(LED1);
	gpio_output_en(LED2);
	gpio_output_en(LED3);
	gpio_output_en(LED4);

	/*
	 * Button matrix table:
	 * 			KEY3	KEY4
	 * 	KEY1	SW2		SW3
	 * 	KEY2	SW4		SW5
	 */
	gpio_function_en(KEY3);
	gpio_output_en(KEY3);
	gpio_set_low_level(KEY3);

	gpio_function_en(KEY1);
	gpio_output_dis(KEY1);
	gpio_input_en(KEY1);
	gpio_set_up_down_res(KEY1, GPIO_PIN_PULLUP_10K);

	core_interrupt_enable();

#if (GPIO_MODE == GPIO_IRQ )
	 /****GPIO_IRQ POL_FALLING   Press SW2 to connect KEY1 and KEY3 to trigger an interrupt. **/
    //if disable gpio interrupt,choose disable gpio mask , use interface gpio_clr_irq_mask instead of gpio_irq_dis,if use gpio_irq_dis,may generate a false interrupt.
	gpio_set_irq(KEY1, INTR_FALLING_EDGE);	//When SW2 is pressed, the falling edge triggers the interrupt.
	plic_interrupt_enable(IRQ25_GPIO);

#elif(GPIO_MODE == GPIO_IRQ_RSIC0)
	/****GPIO_IRQ_RSIC0  POL_FALLING   Press SW2 to connect KEY1 and KEY3 to trigger an interrupt. **/
	//if disable gpio2risc0 interrupt,choose disable gpio2risc0 mask , use interface gpio_clr_irq_mask instead of gpio_gpio2risc0_irq_dis,if use gpio_gpio2risc0_irq_dis,may generate a false interrupt..
	gpio_set_gpio2risc0_irq(KEY1,INTR_FALLING_EDGE);	//When SW2 is pressed, the falling edge triggers the interrupt.
	plic_interrupt_enable(IRQ26_GPIO2RISC0);

#elif(GPIO_MODE == GPIO_IRQ_RSIC1)
	/****GPIO_IRQ_RSIC1  POL_FALLING   Press SW2 to connect KEY1 and KEY3 to trigger an interrupt. **/
	//if disable gpio2risc1 interrupt,choose disable gpio2risc1 mask , use interface gpio_clr_irq_mask instead of gpio_gpio2risc1_irq_dis,if use gpio_gpio2risc1_irq_dis,may generate a false interrupt.
	gpio_set_gpio2risc1_irq(KEY1,INTR_FALLING_EDGE);	//When SW2 is pressed, the falling edge triggers the interrupt.
	plic_interrupt_enable(IRQ27_GPIO2RISC1);

#elif((GPIO_MODE == GPIO_SEL_IRQ_SRC)&&(MCU_CORE_B92))
	/*Note : the use method of 8 new GPIO irq source :
	 * First ,you can choose a gpio group,like gpio GPIO_GROUP_A,8 GPIO in all.
	 * Second,the 8 gpio you choose corresponding to the 8 gpio irq source respectively.for example,irq source0-GPIO_PA0,irq source1-GPIO-PA1......
	 * Attention:Once you choose a gpio-group,you can only use the gpio as irq_source in this group.And you should obey the rule of correspondence.
	 */
	gpio_set_src_irq_group(KEY1>>8);
	gpio_set_src_irq(KEY1,INTR_FALLING_EDGE);	//When SW2 is pressed, the falling edge triggers the interrupt.
	plic_interrupt_enable(IRQ34_GPIO_SRC0 + BIT_LOW_BIT(KEY1&0x00ff));
#endif
#endif
#endif
}
/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
	delay_ms(200);
}





/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for B91m
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
#include "app_config.h"
#include "printf.h"


volatile unsigned int cnt_while = 0;

/**
 * @brief		This function serves to initialize the LPC used by CTB.
 * @param[in] 	none
 * @return 		none
 */
void ctb_lpc_init(void)
{
	lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_PB0);//Select the reference voltage of CTB as the reference voltage of LPC.
	lpc_set_input_chn(LPC_INPUT_PB7);//Select the output voltage of CTB as the input of LPC.
	lpc_set_scaling_coeff(LPC_SCALING_PER100);
	lpc_power_on();
	lpc_set_diff_mode();
}


void user_init()
{
	gpio_shutdown(GPIO_ALL);

	gpio_function_en(LED1);
	gpio_function_en(LED2);
	gpio_function_en(LED3);
	gpio_function_en(LED4);

	gpio_output_en(LED1);
	gpio_output_en(LED2);
	gpio_output_en(LED3);
	gpio_output_en(LED4);

	gpio_input_dis(LED1);
	gpio_input_dis(LED2);
	gpio_input_dis(LED3);
	gpio_input_dis(LED4);

	gpio_set_low_level(LED1);
	gpio_set_low_level(LED2);
	gpio_set_low_level(LED3);
	gpio_set_low_level(LED4);

	ctb_init();
	ctb_lpc_init();

	core_interrupt_enable();
	plic_interrupt_enable(IRQ45_PM_IRQ);

}

void main_loop (void)
{
	if(ctb_get_irq_status(CTB_CHANNEL_1))
	{
		gpio_set_high_level(LED2);
		delay_ms(500);
		gpio_set_low_level(LED2);
	}
	if(ctb_get_irq_status(CTB_CHANNEL_2))
	{
		gpio_set_high_level(LED3);
		delay_ms(500);
		gpio_set_low_level(LED3);
	}
	if(ctb_get_irq_status(CTB_CHANNEL_3))
	{
		gpio_set_high_level(LED4);
		delay_ms(500);
		gpio_set_low_level(LED4);
	}
	if(ctb_get_irq_status(CTB_CHANNEL_4))
	{
		gpio_set_high_level(LED1);
		gpio_set_high_level(LED2);
		delay_ms(500);
		gpio_set_low_level(LED1);
		gpio_set_low_level(LED2);
	}
	if(ctb_get_irq_status(CTB_CHANNEL_5))
	{
		gpio_set_high_level(LED2);
		gpio_set_high_level(LED3);
		delay_ms(500);
		gpio_set_low_level(LED2);
		gpio_set_low_level(LED3);
			}
	if(ctb_get_irq_status(CTB_CHANNEL_6))
	{
		gpio_set_high_level(LED3);
		gpio_set_high_level(LED4);
		delay_ms(500);
		gpio_set_low_level(LED3);
		gpio_set_low_level(LED4);
	}
	if(ctb_get_irq_status(CTB_CHANNEL_7))
	{
		gpio_set_high_level(LED1);
		gpio_set_high_level(LED4);
		delay_ms(500);
		gpio_set_low_level(LED1);
		gpio_set_low_level(LED4);
	}
}







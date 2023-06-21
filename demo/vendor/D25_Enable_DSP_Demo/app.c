/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for B91m
 *
 * @author  Driver Group
 * @date    2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

volatile unsigned int  val_m0_to_m2_word0 = 0x01234567;
volatile unsigned int  val_m0_to_m2_word1 = 0x89abcdef;
volatile unsigned int  val_m2_to_m0_word[2]={0};
void user_init()
{
	gpio_function_en(LED1);
	gpio_output_en(LED1);
	gpio_set_low_level(LED1);
	gpio_function_en(LED2);
	gpio_output_en(LED2);
	gpio_set_low_level(LED2);

	//enable dsp
	sys_dsp_init();
	//enable MAILBOX_DSP_TO_D25 irq
	mailbox_set_irq_mask(FLD_MAILBOX_M2_TO_M0_IRQ);
	plic_interrupt_enable(IRQ49_IRQ_MAILBOX_DSP_TO_D25);
	core_interrupt_enable();
}
void main_loop(void)
{
	delay_ms(500);
	gpio_toggle(LED1);
	msg_m0_to_m2_word0=val_m0_to_m2_word0;
	msg_m0_to_m2_word1=val_m0_to_m2_word1;
}

_attribute_ram_code_sec_noinline_  void mailbox_dsp_to_d25_irq_handler(void)
{
	if( mailbox_get_irq_status(FLD_MAILBOX_M2_TO_M0_IRQ))
	{
		mailbox_clr_irq_status(FLD_MAILBOX_M2_TO_M0_IRQ);
		val_m2_to_m0_word[0] = msg_m2_to_m0_word0;
		val_m2_to_m0_word[1] = msg_m2_to_m0_word1;
		if((val_m2_to_m0_word[0] == val_m0_to_m2_word0) && (val_m2_to_m0_word[1] == val_m0_to_m2_word1))
		{
			gpio_set_low_level(LED2);
		}
		else
		{
			gpio_set_high_level(LED2);//error
		}
	}
}

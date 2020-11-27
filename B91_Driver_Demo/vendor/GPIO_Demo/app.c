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

void user_init()
{
	delay_ms(2000);
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
#if (GPIO_MODE == GPIO_IRQ )
	  /****GPIO_IRQ POL_FALLING   SW1 link PA2**/
	gpio_function_en(GPIO_PA2);
	gpio_output_en(GPIO_PA2);
	gpio_function_en(SW1);
	gpio_output_dis(SW1);
	gpio_input_en(SW1);
	gpio_set_up_down_res(SW1, GPIO_PIN_PULLUP_10K);
	core_interrupt_enable();
	gpio_set_irq(SW1, INTR_FALLING_EDGE);
	gpio_irq_en(SW1);
	plic_interrupt_enable(IRQ25_GPIO);

#elif(GPIO_MODE == GPIO_IRQ_RSIC0)
	/****GPIO_IRQ_RSIC0  POL_FALLING   SW1 link PA2**/
	gpio_function_en(GPIO_PA2);
	gpio_output_en(GPIO_PA2);
	gpio_function_en(SW1);
	gpio_output_dis(SW1);
	gpio_input_en(SW1);
	gpio_set_up_down_res(SW1, GPIO_PIN_PULLUP_10K);
	core_interrupt_enable();
	gpio_set_gpio2risc0_irq(SW1,INTR_FALLING_EDGE);
	gpio_gpio2risc0_irq_en(SW1);
	plic_interrupt_enable(IRQ26_GPIO2RISC0);


#elif(GPIO_MODE == GPIO_IRQ_RSIC1)
	/****GPIO_IRQ_RSIC1  POL_FALLING   SW1 link PA2**/
	gpio_function_en(GPIO_PA2);
	gpio_output_en(GPIO_PA2);
	gpio_input_dis(GPIO_PA2);
	gpio_output_dis(SW1);
	gpio_input_en(SW1);
	gpio_function_en(SW1);
	gpio_set_up_down_res(SW1, GPIO_PIN_PULLUP_10K);
	core_interrupt_enable();
	gpio_gpio2risc1_irq_en(SW1);
	gpio_set_gpio2risc1_irq(SW1,INTR_FALLING_EDGE);
	gpio_gpio2risc1_irq_en(SW1);
	plic_interrupt_enable(IRQ27_GPIO2RISC1);
#elif(GPIO_MODE == GPIO_HIGH_RESISTOR)
	gpio_shutdown(GPIO_ALL);//set all gpio as high resistor except sws and mspi
#endif
}
/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
	delay_ms(200);
	gpio_toggle(GPIO_PA2);
	delay_ms(200);
	gpio_toggle(LED1);

}





/********************************************************************************************************
 * @file	main.c
 *
 * @brief	This is the source file for B91
 *
 * @author	D.M.H / X.P.C
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


extern void user_init();
extern void main_loop (void);
volatile unsigned int gpio_irq_cnt=0,gpio_irq_rsic0_cnt=0,gpio_irq_rsic1_cnt=0;

/**
 * @brief		This function serves to handle the interrupt of MCU
 * @param[in] 	none
 * @return 		none
 */
#if (GPIO_MODE == GPIO_IRQ )
void gpio_irq_handler(void)
{
	gpio_toggle(LED2);
	gpio_irq_cnt++;
    reg_gpio_irq_clr |=FLD_GPIO_IRQ_CLR ;
}
#elif(GPIO_MODE == GPIO_IRQ_RSIC0)
_attribute_ram_code_sec_ void gpio_risc0_irq_handler(void)
{
	 gpio_toggle(LED3);
	 gpio_irq_rsic0_cnt++;
	reg_gpio_irq_clr |=FLD_GPIO_IRQ_GPIO2RISC0_CLR ;
}
#elif(GPIO_MODE == GPIO_IRQ_RSIC1)

_attribute_ram_code_sec_ void gpio_risc1_irq_handler(void)
{
	    gpio_toggle(LED4);
        gpio_irq_rsic1_cnt++;
		reg_gpio_irq_clr |=FLD_GPIO_IRQ_GPIO2RISC1_CLR ;
}
#endif


/**
 * @brief		This is main function
 * @param[in]	none
 * @return      none
 */
int main (void)
{
	sys_init(LDO_1P4_LDO_1P8);
	CCLK_24M_HCLK_24M_PCLK_24M;
			
	gpio_init(1);/*	You also can use the function "gpio_usr_init" to initialize the gpio,
				  *	but you must define a structure, which type is "gpio_init_s", before using it. If you
				  *	have any questions about how to use it, you might as well refer to this macro function.
				  */
	user_init();

	while (1) {
		main_loop ();
	}
	return 0;
}


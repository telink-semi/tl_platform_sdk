/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91
 *
 * @author	Z.W.H
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

unsigned char dat[5]={0};
unsigned char  mdec_test_cnt = 0;

/**
 * @brief		This function serves to handle the interrupt of MCU.
 * @return 		none.
 */
_attribute_ram_code_sec_ void pm_irq_handler(void)
{
	if(mdec_get_irq_status(FLD_WKUP_MDEC))
	{
		mdec_test_cnt = 1;
		mdec_clr_irq_status(FLD_WKUP_MDEC);
	}
}

void user_init(void)
{
	gpio_function_en(LED1|LED2);
	gpio_output_en(LED1|LED2);
	clock_cal_32k_rc();
	mdec_init(FLD_SELE_PE0);
	core_interrupt_enable();
	plic_interrupt_enable(IRQ62_PM_TM);
	mdec_clr_irq_status(FLD_WKUP_MDEC);
	mdec_reset();
}

void main_loop (void)
{
	if(mdec_test_cnt)
	{
		mdec_test_cnt = 0;
		if(mdec_read_dat(dat))
		{
			gpio_toggle(LED2);
			delay_ms(2000);
		}
	}
}


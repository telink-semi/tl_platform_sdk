/********************************************************************************************************
 * @file	main.c
 *
 * @brief	This is the source file for B91
 *
 * @author	Z.X.D / D.M.H
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

extern void user_init(void);
extern void main_loop (void);
int timer0_irq_cnt = 0;
int timer1_irq_cnt = 0;
volatile unsigned int timer0_gpio_width =0;
volatile unsigned int timer1_gpio_width =0;

void timer0_irq_handler(void)
{
#if( TIMER_MODE == TIMER_SYS_CLOCK_MODE )

	if(reg_tmr_sta & FLD_TMR_STA_TMR0)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR0;

		gpio_toggle(LED2);
		timer0_irq_cnt ++;
	}

#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

	if(reg_tmr_sta & FLD_TMR_STA_TMR0)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR0; //clear irq status

		gpio_toggle(LED2);
		timer0_irq_cnt ++;
	}

#elif(TIMER_MODE == TIMER_GPIO_WIDTH_MODE)

	if(reg_tmr_sta & FLD_TMR_STA_TMR0)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR0; //clear irq status

		timer0_gpio_width = reg_tmr0_tick;
		reg_tmr0_tick = 0;
		gpio_toggle(LED2);
	}

#endif
}

void timer1_irq_handler(void)
{
#if( TIMER_MODE == TIMER_SYS_CLOCK_MODE )

	if(reg_tmr_sta & FLD_TMR_STA_TMR1)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR1;

		gpio_toggle(LED3);
		timer1_irq_cnt ++;
	}

#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

	if(reg_tmr_sta & FLD_TMR_STA_TMR1)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR1; //clear irq status

		gpio_toggle(LED3);
		timer1_irq_cnt ++;
	}

#elif(TIMER_MODE == TIMER_GPIO_WIDTH_MODE)

	if(reg_tmr_sta & FLD_TMR_STA_TMR1)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR1; //clear irq status

		timer1_gpio_width = reg_tmr1_tick;
		reg_tmr1_tick = 0;
		gpio_toggle(LED3);
	}

#endif
}

/**
 * @brief		This is main function
 * @param[in]	none
 * @return      none
 */

extern float Dhrystone_DMIPS_Per_MHz;

int main(void)
{
	sys_init(LDO_1P4_LDO_1P8);

	//CCLK_24M_HCLK_24M_PCLK_24M;;

	CCLK_24M_HCLK_24M_PCLK_24M;;

	user_init();
	while ((read_reg8(0x10080b) & 0x7f) == 0);

	for (int i=0; i<1; i++)
	{
		printf ("\r\n\r\n Drystone Benchmark %d Starts ...", i);
		dhry_main();
	}
	printf("\r\n[dhrystone] : %6.2f\r\n",Dhrystone_DMIPS_Per_MHz);
	delay_ms (100);





	reg_usb_ep8_send_thre = 1;

	//while (1);

    while(1)
    {
    	main_loop();
    }

    return 0;
}

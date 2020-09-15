/********************************************************************************************************
 * @file	app_pm.c
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

#if(TEST_MODE == TEST_PM_MODE)

#define DEEP_32K_RC_WAKEUP_TEST      	89	//Used to test when sleeping, some pins will have abnormal sharp pulses.
#define DEEP_PAD_WAKEUP		 			6     	//#33:0.5uA
#define DEEP_RET_PAD_WAKEUP     		10		//#12:2uA  ret ldo = 1.0v PA5/PA6 low wakeup need call
												//deepsleep_dp_dm_gpio_low_wake_enable() but deep current will add about 0.1u
#define PM_MODE			     			DEEP_PAD_WAKEUP



_attribute_data_retention_sec_ u32 retention_data_test = 0;
volatile unsigned short volat_pad = 0;

void user_init(void)
{
#if(PM_MODE == DEEP_32K_RC_WAKEUP_TEST)
	delay_ms(1000);
	gpio_shutdown(GPIO_ALL);
	gpio_set_up_down_res(GPIO_PA0, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA1, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA2, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA3, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA4, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA5, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA6, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PA7, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB0, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB1, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB2, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB3, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB4, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB5, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB6, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PB7, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC0, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC1, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC2, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC3, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC4, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC5, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC6, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PC7, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE0, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE1, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE2, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE3, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE4, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE5, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE6, GPIO_PIN_PULLDOWN_100K);
	gpio_set_up_down_res(GPIO_PE7, GPIO_PIN_PULLDOWN_100K);

	clock_cal_24m_rc();
	clock_32k_init(CLK_32K_RC);
	clock_cal_32k_rc();//6.68ms
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 1000*CLOCK_16M_SYS_TIMER_CLK_1MS));
#endif


	delay_ms(1000);

	//1.init the LED pin,for indication
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4); 		//enable output
	gpio_input_dis(LED1|LED2|LED3|LED4);			//disable input
	gpio_function_en(GPIO_PA0|GPIO_PA1|GPIO_PA2|GPIO_PA3|GPIO_PA4|GPIO_PA5|GPIO_PA6);
	gpio_input_en(GPIO_PA0|GPIO_PA1|GPIO_PA2|GPIO_PA3|GPIO_PA4|GPIO_PA5|GPIO_PA6);
	gpio_function_en(GPIO_PB0|GPIO_PB1|GPIO_PB2|GPIO_PB3);
	gpio_input_en(GPIO_PB0|GPIO_PB1|GPIO_PB2|GPIO_PB3);
//	gpio_function_en(GPIO_PC0|GPIO_PC1|GPIO_PC2|GPIO_PC3);
//	gpio_input_en(GPIO_PC0|GPIO_PC1|GPIO_PC2|GPIO_PC3);
	gpio_function_en(GPIOC_ALL);
	gpio_input_en(GPIOC_ALL);
	gpio_function_en(GPIOE_ALL);
	gpio_input_en(GPIOE_ALL);

	gpio_set_high_level(LED1);
	delay_ms(10000);
	gpio_set_low_level(LED1);

#if(PM_MODE==DEEP_PAD_WAKEUP)
	/* Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC * */
	/* LED1 on, use BDT tools to write gpio pin to 0xc0218000, low first*/
	volat_pad = read_sram16(0x98000);
	pm_set_gpio_wakeup(volat_pad, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(volat_pad, GPIO_PIN_PULLDOWN_100K);
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE==DEEP_RET_PAD_WAKEUP)
	retention_data_test++;
	volat_pad = read_sram16(0x98000);
	pm_set_gpio_wakeup(volat_pad, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(volat_pad, GPIO_PIN_PULLDOWN_100K);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);

#endif

}


void main_loop(void)
{
	gpio_set_high_level(LED2);
	delay_ms(2000);
}

#endif

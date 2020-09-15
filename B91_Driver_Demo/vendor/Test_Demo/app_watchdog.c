/********************************************************************************************************
 * @file	app_watchdog.c
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

#if(TEST_MODE == TEST_WATCHDOG_MODE)

//Enter the following sleep sequence.
#define watchdog_step	1
#define deep_step		3
#define deep_ret_step	2

unsigned char poweron_buf[12];
unsigned char deep_buf[12];
unsigned char retention_buf[12];
unsigned char watchdog_buf[12];

extern void pm_update_status_info(void);

void sys_init1(power_mode_e power_mode)
{
	reg_rst 	= 0xffffffff;   //reset function will be cleared by set "1",which is different from the previous configuration
	reg_clk_en 	= 0xffffffff;
	analog_write_reg8(0x8c,0x02);//reg_xo_en_clk_ana_ana=1

	write_reg32(0x160000, 0x20000000);   //reset ceva module(power on/hardware reset will cause some bt register default value changed,
									 //need soft reset)

	analog_write_reg8(0x0a, power_mode);  //set power mode
	analog_write_reg8(0x01, 0x45);

	analog_write_reg8(0x0b, 0x78);  		//power on native 1P4 & 1P8
	analog_write_reg8(0x06,analog_read_reg8(0x06) & ~(BIT(0) | BIT(6) | BIT(7)));////ldo_bbpll_pd = 0 power on spd ldo and dig_ret_ldo

	//stimer
	analog_write_reg8(0x05,analog_read_reg8(0x05) & (~BIT(3)));        //Power up 24MHz XTL oscillator

	write_csr(NDS_MILMB,0x01);
	write_csr(NDS_MDLMB,0x80001);

	//xo_ready check should be done after Xtal manual on_off, we put it here to save code running time, code running time between
	// Xtal manual on_off and xo_ready check can be used as Xtal be stable timimg
	while( BIT(7) != (analog_read_reg8(0x88) & (BIT(7)))); //0x88<7>: xo_ready_ana
	pm_wait_bbpll_done();

	reg_system_ctrl	|= FLD_SYSTEM_32K_CAL_EN | FLD_SYSTEM_TIMER_EN ;    //enable 32k cal and stimer
}

#if 1
void user_init(void)
{
	reg_rst 	= 0xffffffff;   //reset function will be cleared by set "1",which is different from the previous configuration
	reg_clk_en 	= 0xffffffff;
	unsigned char analog_38 = analog_read_reg8(PM_ANA_REG_WD_CLR_BUF0);
	unsigned char analog_39 = analog_read_reg8(PM_ANA_REG_POWER_ON_CLR_BUF0);

	if(analog_38 & BIT(0)){
		if(analog_39 & BIT(0)){
			g_pm_status_info.mcu_status = MCU_STATUS_REBOOT_BACK;
		}else{
			g_pm_status_info.mcu_status = MCU_STATUS_POWER_ON;
		}
	}else{
		if(pm_get_deep_retention_flag()){
			g_pm_status_info.mcu_status = MCU_STATUS_DEEPRET_BACK;
		}else{
			g_pm_status_info.mcu_status = MCU_STATUS_DEEP_BACK;
		}
	}
	if(g_pm_status_info.mcu_status == MCU_STATUS_POWER_ON)	//power on
	{
		poweron_buf[0] = analog_read_reg8(0x64);	//80
		poweron_buf[1] = analog_read_reg8(0x7d);	//07
		poweron_buf[2] = analog_read_reg8(0x7e);	//00
		poweron_buf[3] = analog_read_reg8(0x7f);	//01
		poweron_buf[4] = analog_read_reg8(0x38);	//ff
		poweron_buf[5] = analog_read_reg8(0x39);	//00
		poweron_buf[6] = analog_read_reg8(0x3a);	//00
		poweron_buf[7] = analog_read_reg8(0x3b);	//00
		poweron_buf[8] = analog_read_reg8(0x3c);	//00
		poweron_buf[9] = analog_read_reg8(0x3d);	//00
		poweron_buf[10] = analog_read_reg8(0x3e);	//00
		poweron_buf[11] = analog_read_reg8(0x3f);	//0f
		sys_init1(LDO_1P4_LDO_1P8);
		pm_update_status_info();
		CCLK_24M_HCLK_24M_PCLK_24M;
		while(!read_reg32(0x140214));
		flash_erase_sector(0x30000);
		flash_write_page(0x30000,12,(unsigned char *)poweron_buf);
		analog_write_reg8(0x64,0x80);
		analog_write_reg8(0x3a,0x01);
		analog_write_reg8(0x3b,0x01);
		analog_write_reg8(0x3c,0x01);
		analog_write_reg8(0x3d,0x01);
		analog_write_reg8(0x3e,0x01);
		analog_write_reg8(0x3f,0x01);
		analog_write_reg8(0x7d,0x80);	//power on baseband
		if(watchdog_step == 1)
		{
			wd_set_interval_ms(1000,sys_clk.pclk*1000);
			wd_start();
		}else if(deep_step == 1){
			pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
		}else{
			pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
		}
	}
	else if(g_pm_status_info.mcu_status == MCU_STATUS_REBOOT_BACK)	//watchdog
	{
		watchdog_buf[0] = analog_read_reg8(0x64);	//80
		watchdog_buf[1] = analog_read_reg8(0x7d);	//80
		watchdog_buf[2] = analog_read_reg8(0x7e);	//00
		watchdog_buf[3] = analog_read_reg8(0x7f);	//01
		watchdog_buf[4] = analog_read_reg8(0x38);	//ff
		watchdog_buf[5] = analog_read_reg8(0x39);	//00
		watchdog_buf[6] = analog_read_reg8(0x3a);	//00
		watchdog_buf[7] = analog_read_reg8(0x3b);	//00
		watchdog_buf[8] = analog_read_reg8(0x3c);	//00
		watchdog_buf[9] = analog_read_reg8(0x3d);	//00
		watchdog_buf[10] = analog_read_reg8(0x3e);	//00
		watchdog_buf[11] = analog_read_reg8(0x3f);	//0f
		sys_init1(LDO_1P4_LDO_1P8);
		pm_update_status_info();
		CCLK_24M_HCLK_24M_PCLK_24M;
		while(!read_reg32(0x140214));
		if(watchdog_step == 3)
		{
			flash_read_page(0x30000,12,(unsigned char *)poweron_buf);
			flash_read_page(0x30020,12,(unsigned char *)deep_buf);
			flash_read_page(0x30030,12,(unsigned char *)retention_buf);
			gpio_function_en(LED1|LED2|LED3|LED4);	//enable gpio
			gpio_output_en(LED1|LED2|LED3|LED4); 	//enable output
			gpio_input_dis(LED1|LED2|LED3|LED4);	//disable input
		}
		else
		{
			flash_write_page(0x30010,12,(unsigned char *)watchdog_buf);
			analog_write_reg8(0x64,0x80);
			analog_write_reg8(0x3a,0x02);
			analog_write_reg8(0x3b,0x02);
			analog_write_reg8(0x3c,0x02);
			analog_write_reg8(0x3d,0x02);
			analog_write_reg8(0x3e,0x02);
			analog_write_reg8(0x3f,0x02);
			if(deep_step == (watchdog_step+1)){
				pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
			}else{
				pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
			}
		}
	}
	else if(g_pm_status_info.mcu_status == MCU_STATUS_DEEP_BACK)	//deep
	{
		deep_buf[0] = analog_read_reg8(0x64);	//86
		deep_buf[1] = analog_read_reg8(0x7d);	//86
		deep_buf[2] = analog_read_reg8(0x7e);	//30
		deep_buf[3] = analog_read_reg8(0x7f);	//01
		deep_buf[4] = analog_read_reg8(0x38);	//ff
		deep_buf[5] = analog_read_reg8(0x39);	//00
		deep_buf[6] = analog_read_reg8(0x3a);	//00
		deep_buf[7] = analog_read_reg8(0x3b);	//00
		deep_buf[8] = analog_read_reg8(0x3c);	//00
		deep_buf[9] = analog_read_reg8(0x3d);	//00
		deep_buf[10] = analog_read_reg8(0x3e);	//00
		deep_buf[11] = analog_read_reg8(0x3f);	//0f
		sys_init1(LDO_1P4_LDO_1P8);
		pm_update_status_info();
		CCLK_24M_HCLK_24M_PCLK_24M;
		while(!read_reg32(0x140214));
		if(deep_step == 3)
		{
			flash_read_page(0x30000,12,(unsigned char *)poweron_buf);
			flash_read_page(0x30010,12,(unsigned char *)watchdog_buf);
			flash_read_page(0x30030,12,(unsigned char *)retention_buf);
			gpio_function_en(LED1|LED2|LED3|LED4);	//enable gpio
			gpio_output_en(LED1|LED2|LED3|LED4); 	//enable output
			gpio_input_dis(LED1|LED2|LED3|LED4);	//disable input
		}
		else
		{
			flash_write_page(0x30020,12,(unsigned char *)deep_buf);
			analog_write_reg8(0x64,0x80);
			analog_write_reg8(0x3a,0x03);
			analog_write_reg8(0x3b,0x03);
			analog_write_reg8(0x3c,0x03);
			analog_write_reg8(0x3d,0x03);
			analog_write_reg8(0x3e,0x03);
			analog_write_reg8(0x3f,0x03);
			if(watchdog_step == (deep_step+1)){
				wd_set_interval_ms(1000,sys_clk.pclk*1000);
				wd_start();
			}else{
				pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
			}
		}
	}
	else	//deep retention
	{
		retention_buf[0] = analog_read_reg8(0x64);	//86
		retention_buf[1] = analog_read_reg8(0x7d);	//86
		retention_buf[2] = analog_read_reg8(0x7e);	//03
		retention_buf[3] = analog_read_reg8(0x7f);	//00
		retention_buf[4] = analog_read_reg8(0x38);	//ff
		retention_buf[5] = analog_read_reg8(0x39);	//00
		retention_buf[6] = analog_read_reg8(0x3a);	//00
		retention_buf[7] = analog_read_reg8(0x3b);	//00
		retention_buf[8] = analog_read_reg8(0x3c);	//00
		retention_buf[9] = analog_read_reg8(0x3d);	//00
		retention_buf[10] = analog_read_reg8(0x3e);	//00
		retention_buf[11] = analog_read_reg8(0x3f);	//0f
		sys_init1(LDO_1P4_LDO_1P8);
		pm_update_status_info();
		CCLK_24M_HCLK_24M_PCLK_24M;
		while(!read_reg32(0x140214));
		if(deep_ret_step == 3)
		{
			flash_read_page(0x30000,12,(unsigned char *)poweron_buf);
			flash_read_page(0x30010,12,(unsigned char *)watchdog_buf);
			flash_read_page(0x30020,12,(unsigned char *)deep_buf);
			gpio_function_en(LED1|LED2|LED3|LED4);	//enable gpio
			gpio_output_en(LED1|LED2|LED3|LED4); 	//enable output
			gpio_input_dis(LED1|LED2|LED3|LED4);	//disable input
		}
		else
		{
			flash_write_page(0x30030,12,(unsigned char *)retention_buf);
			analog_write_reg8(0x64,0x80);
			analog_write_reg8(0x3a,0x04);
			analog_write_reg8(0x3b,0x04);
			analog_write_reg8(0x3c,0x04);
			analog_write_reg8(0x3d,0x04);
			analog_write_reg8(0x3e,0x04);
			analog_write_reg8(0x3f,0x04);
			if(watchdog_step == (deep_ret_step+1)){
				wd_set_interval_ms(1000,sys_clk.pclk*1000);
				wd_start();
			}else{
				pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 200*CLOCK_16M_SYS_TIMER_CLK_1MS));
			}
		}
	}
}
#else
void user_init(void)
{
	sys_init1(LDO_1P4_LDO_1P8);
	CCLK_24M_HCLK_24M_PCLK_24M;
	analog_write_reg8(0x7d,0x80);	//power on baseband
	gpio_function_en(LED1|LED2|LED3|LED4);		//enable gpio
	gpio_output_en(LED1|LED2|LED3|LED4); 	//enable output
	gpio_input_dis(LED1|LED2|LED3|LED4);	//disable input
	if(0x00 != (analog_read_reg8(0x64)&0x1f))
	{
		gpio_set_high_level(LED1);
		gpio_set_high_level(LED2);
		while(1);
	}
	gpio_set_high_level(LED1);
	wd_set_interval_ms(1000,sys_clk.pclk*1000);
	wd_start();
}
#endif


void main_loop(void)
{
	delay_ms(500);
	gpio_toggle(LED1);
}

#endif

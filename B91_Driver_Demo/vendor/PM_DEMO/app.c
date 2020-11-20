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
#include "compiler.h"

unsigned char dat[5] = {0};
unsigned char result = 0;

_attribute_data_retention_sec_ unsigned int retention_data_test = 0;

void user_init(void)
{
	delay_ms(2000);

#if CURRENT_TEST
	gpio_shutdown(GPIO_ALL);
#else
	// init the LED pin, for indication
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4); 		//enable output
	gpio_input_dis(LED1|LED2|LED3|LED4);		//disable input

	gpio_set_high_level(LED1);
	delay_ms(1000);

#if ((PM_MODE == DEEP_MDEC_WAKEUP)||(PM_MODE == DEEP_RET32K_MDEC_WAKEUP)||(PM_MODE == DEEP_RET64K_MDEC_WAKEUP))
	if(((pm_get_wakeup_src()) & PM_WAKEUP_MDEC) && (CRC_OK == mdec_read_dat(dat)))
	{
		gpio_set_high_level(LED3);
		delay_ms(2000);
	}
#endif

#if ((PM_MODE == DEEP_COMPARATOR_WAKEUP)||(PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP)||(PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP))
	result = lpc_get_result();
	if(result){
		gpio_set_high_level(LED3);
	}else{
		gpio_set_low_level(LED3);
	}
	delay_ms(2000);
#endif

#endif

	//24M RC is inaccurate, and it is greatly affected by temperature, so real-time calibration is required
	//The 24M RC needs to be calibrated before the pm_sleep_wakeup function,
	//because this clock will be used to kick 24m xtal start after wake up,
	//The more accurate this time, the faster the crystal will start.Calibration cycle depends on usage
	clock_cal_24m_rc();

	//If it is timer or mdec wake up, you need to initialize 32K
#if(PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_RC_WAKEUP\
	|| PM_MODE == SUSPEND_MDEC_WAKEUP || PM_MODE == DEEP_MDEC_WAKEUP || PM_MODE == DEEP_RET32K_MDEC_WAKEUP || PM_MODE == DEEP_RET64K_MDEC_WAKEUP)
	clock_32k_init(CLK_32K_RC);
	clock_cal_32k_rc();	//6.68ms
#elif(PM_MODE == SUSPEND_32K_XTAL_WAKEUP || PM_MODE == DEEP_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET32K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET64K_32K_XTAL_WAKEUP)
	clock_32k_init(CLK_32K_XTAL);
	clock_kick_32k_xtal(100);
#endif

#if(PM_MODE == IDLE_TIMER_WAKEUP)



#elif(PM_MODE == SUSPEND_PAD_WAKEUP)	//Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
	pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);

#elif(PM_MODE == DEEP_PAD_WAKEUP)	//Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
	pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET32K_PAD_WAKEUP)
	retention_data_test++;
	pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET64K_PAD_WAKEUP)
	retention_data_test++;
	pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
	gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE==DEEP_32K_RC_WAKEUP||PM_MODE==DEEP_32K_XTAL_WAKEUP)
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (stimer_get_tick() + 4000*SYSTEM_TIMER_TICK_1MS));

#elif(PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_XTAL_WAKEUP)
	retention_data_test++;
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (stimer_get_tick() + 4000*SYSTEM_TIMER_TICK_1MS));

#elif(PM_MODE == DEEP_RET64K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_XTAL_WAKEUP)
	retention_data_test++;
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (stimer_get_tick() + 4000*SYSTEM_TIMER_TICK_1MS));

#elif(PM_MODE == SUSPEND_MDEC_WAKEUP)
	mdec_init(FLD_SELE_PE0);
	mdec_reset();
	pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);

#elif(PM_MODE == DEEP_MDEC_WAKEUP)
	mdec_init(FLD_SELE_PE0);
	mdec_reset();
	pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_MDEC, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET32K_MDEC_WAKEUP)
	retention_data_test++;
	mdec_init(FLD_SELE_PE0);
	mdec_reset();
	pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_MDEC, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET64K_MDEC_WAKEUP)
	retention_data_test++;
	mdec_init(FLD_SELE_PE0);
	mdec_reset();
	pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_MDEC, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == SUSPEND_COMPARATOR_WAKEUP)
	lpc_power_on();
	lpc_set_input_chn(LPC_INPUT_PB1);
	lpc_set_input_ref(LPC_LOWPOWER,LPC_REF_872MV);
	lpc_set_scaling_coeff(LPC_SCALING_PER50);

#elif(PM_MODE == DEEP_COMPARATOR_WAKEUP)
	lpc_power_on();
	lpc_set_input_chn(LPC_INPUT_PB1);
	lpc_set_input_ref(LPC_LOWPOWER,LPC_REF_872MV);
	lpc_set_scaling_coeff(LPC_SCALING_PER50);
	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP)
	retention_data_test++;
	lpc_power_on();
	lpc_set_input_chn(LPC_INPUT_PB1);
	lpc_set_input_ref(LPC_LOWPOWER,LPC_REF_872MV);
	lpc_set_scaling_coeff(LPC_SCALING_PER50);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP)
	retention_data_test++;
	lpc_power_on();
	lpc_set_input_chn(LPC_INPUT_PB1);
	lpc_set_input_ref(LPC_LOWPOWER,LPC_REF_872MV);
	lpc_set_scaling_coeff(LPC_SCALING_PER50);
	pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER_16M, 0);

#elif(PM_MODE == SUSPEND_CORE_WAKEUP)
	usb_set_pin_en();
	gpio_set_up_down_res(GPIO_PA5, GPIO_PIN_PULLDOWN_100K);
	write_reg8(reg_wakeup_en,0x1d);
	delay_ms(500);
	pm_set_suspend_power_cfg(PM_POWERON_USB);

#endif

}


void main_loop(void)
{
	clock_cal_24m_rc();

#if(PM_MODE == SUSPEND_PAD_WAKEUP)
	gpio_set_high_level(LED2);
	delay_ms(500);
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_PAD, PM_TICK_STIMER_16M, 0);
	gpio_set_low_level(LED2);

#elif(PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == SUSPEND_32K_XTAL_WAKEUP)
#if CURRENT_TEST
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, stimer_get_tick() + 4000*SYSTEM_TIMER_TICK_1MS);
#else
	gpio_set_high_level(LED2);
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, stimer_get_tick() + 500*SYSTEM_TIMER_TICK_1MS);
	gpio_set_low_level(LED2);
#endif

#elif(PM_MODE == SUSPEND_MDEC_WAKEUP)
	gpio_set_high_level(LED2);
	delay_ms(500);
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_MDEC, PM_TICK_STIMER_16M, 0);
	gpio_set_low_level(LED2);
	if((CRC_OK == mdec_read_dat(dat)))
	{
		gpio_toggle(LED3);
	}
	mdec_reset();

#elif(PM_MODE == SUSPEND_COMPARATOR_WAKEUP)
	gpio_set_high_level(LED2);
	delay_ms(500);
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER_16M, 0);
	gpio_set_low_level(LED2);
	if(1 == lpc_get_result())
	{
		gpio_toggle(LED3);
	}

#elif(PM_MODE == SUSPEND_CORE_WAKEUP)
	gpio_set_high_level(LED2);
	delay_ms(500);
	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_CORE, PM_TICK_STIMER_16M, 0);
	gpio_set_low_level(LED2);

#else
	gpio_set_high_level(LED2);

#endif

	delay_ms(2000);
}


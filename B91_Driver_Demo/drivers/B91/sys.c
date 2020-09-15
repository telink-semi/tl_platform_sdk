/********************************************************************************************************
 * @file	sys.c
 *
 * @brief	This is the source file for B91
 *
 * @author	B.Y
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
#include "sys.h"
#include "core.h"
#include "pm.h"
#include "compiler.h"
#include "analog.h"
#include "gpio.h"
#include "mspi.h"
#include "../../common/assert.h"

/**********************************************************************************************************************
 *                                			  local constants                                                       *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                           	local macro                                                        *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                             local data type                                                     *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                              global variable                                                       *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                              local variable                                                     *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                          local function prototype                                               *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         global function implementation                                             *
 *********************************************************************************************************************/

extern void pm_update_status_info(void);

/**
 * @brief   	This function serves to initialize system.
 * @param[in]	power_mode - power mode(LDO/DCDC/LDO_DCDC)
 * @return  	none
 */
void sys_init(power_mode_e power_mode)
{
	/**
	 * reset function will be cleared by set "1",which is different from the previous configuration.
	 * This setting turns off the TRNG and NPE modules in order to test power consumption.The current
	 * decrease about 3mA when those two modules be turn off.changed by zhiwei,confirmed by kaixin.20200828.
	 */
	reg_rst 	= 0xffbbffff;
	reg_clk_en 	= 0xffbbffff;

	analog_write_reg8(0x8c,0x02);//reg_xo_en_clk_ana_ana=1

	analog_write_reg8(0x0a, power_mode);  //set power mode
	analog_write_reg8(0x01, 0x45);

	analog_write_reg8(0x0b, 0x38);	//poweron_dft: 0x7b -> 0x38.
									//<6>:mscn_pullup_res_enb,	default:1, enable pullup resistor for mscn PAD.
									//<1>:pd_nvt_1p8,			default:1, power on native 1P4.
									//<0>:pd_nvt_1p4,			default:1, power on native 1P8.
	analog_write_reg8(0x06,analog_read_reg8(0x06) & ~(BIT(0) | BIT(6) | BIT(7)));////ldo_bbpll_pd = 0 power on spd ldo and dig_ret_ldo

	//stimer
	analog_write_reg8(0x05,analog_read_reg8(0x05) & (~BIT(3)));        //Power up 24MHz XTL oscillator
	
	write_csr(NDS_MILMB,0x01);
	write_csr(NDS_MDLMB,0x80001);

	pm_update_status_info();

	//xo_ready check should be done after Xtal manual on_off, we put it here to save code running time, code running time between
	// Xtal manual on_off and xo_ready check can be used as Xtal be stable timimg
	while( BIT(7) != (analog_read_reg8(0x88) & (BIT(7)))); //0x88<7>: xo_ready_ana
	pm_wait_bbpll_done();

	if(g_pm_status_info.mcu_status == MCU_STATUS_DEEPRET_BACK)
	{
		pm_stimer_recover();
	}
	reg_system_ctrl	|= FLD_SYSTEM_32K_CAL_EN | FLD_SYSTEM_TIMER_EN ;	//enable 32k cal and stimer. Wait for pll to stabilize before using stimer.

	//**When testing AES_demo, it was found that the timing of baseband was wrong when it was powered on, which caused some of
	//the registers of ceva to go wrong, which caused the program to run abnormally.(add by weihua zhang, confirmed by junwen 20200819)
	if(0xff == read_reg8(0x1401fd))	//A0
	{
		if(g_pm_status_info.mcu_status == MCU_STATUS_POWER_ON)	//power on
		{
			while(!read_reg32(0x140214));	//Wait for the 32k clock calibration to complete.
			pm_set_suspend_power_cfg(0x80);	//power on baseband
			pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_TIMER, PM_TICK_STIMER_16M, (sys_get_stimer_tick() + 100*CLOCK_16M_SYS_TIMER_CLK_1MS));
		}
	}
	pm_set_suspend_power_cfg(0x80);
}
/**
 * @brief      This function performs a series of operations of writing digital or analog registers
 *             according to a command table
 * @param[in]  pt - pointer to a command table containing several writing commands
 * @param[in]  size  - number of commands in the table
 * @return     number of commands are carried out
 */

int write_reg_table(const tbl_cmd_set_t * pt, int size)
{
	int l=0;

	while (l<size) {
		unsigned int  cadr = ((unsigned int)0x80000000) | pt[l].adr;
		unsigned char cdat = pt[l].dat;
		unsigned char ccmd = pt[l].cmd;
		unsigned char cvld =(ccmd & TCMD_UNDER_WR);
		ccmd &= TCMD_MASK;
		if (cvld) {
			if (ccmd == TCMD_WRITE) {
				write_reg8 (cadr, cdat);
			}
			else if (ccmd == TCMD_WAREG) {
				analog_write_reg8 (cadr, cdat);
			}
			else if (ccmd == TCMD_WAIT) {
				delay_us(pt[l].adr*256 + cdat);
			}
		}
		l++;
	}
	return size;

}

/**
 * @brief     This function performs to set delay time by us.
 * @param[in] microsec - need to delay.
 * @return    none
 */
_attribute_ram_code_sec_ void delay_us(u32 microsec)
{
	unsigned long t = sys_get_stimer_tick();
	while(!clock_time_exceed(t, microsec)){
	}
}

/**
 * @brief     This function performs to set delay time by ms.
 * @param[in] millisec - need to delay.
 * @return    none
 */
_attribute_ram_code_sec_ void delay_ms(u32 millisec)
{

	unsigned long t = sys_get_stimer_tick();
	while(!clock_time_exceed(t, millisec*1000)){
	}
}
/**********************************************************************************************************************
 *                    						local function implementation                                             *
 *********************************************************************************************************************/

/********************************************************************************************************
 * @file	dbgport.c
 *
 * @brief	This is the source file for B91
 *
 * @author	L.J.W
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
#include "dbgport.h"

void bt_dbg_set_pin(btdbg_pin_e pin)
{
	unsigned char val,v=0;
	unsigned char mask= 0;
	unsigned char n=0;
	if(pin&0xf)
	{
		v = pin&0xf;
		do{
			n++;
			v= v>>1;
		}while(v);

		mask = ((unsigned char)~(3<<((n-1)*2)));
		val = ((3<<((n-1)*2)));
	}
	else if(pin&0xf0)
	{
		v = ((pin>>4)&0xf);
		do{
			n++;
			v= v>>1;
		}while(v);

		mask = ((unsigned char)~(3<<((n-1)*2)));
		val = ((3<<((n-1)*2)));
	}
	else
	{
		while(1);
	}

	//note:  setting pad the function  must before  setting no_gpio function, cause it will lead to uart transmit extra one byte data at begin.(confirmed by minghai&sunpeng)
	reg_gpio_func_mux(pin)=(reg_gpio_func_mux(pin)& mask)|val;

	gpio_function_dis(pin);

}


void bt_dbg_set_signal(bt_signal_group_e signal_group,unsigned char signal_byte)
{
	if(signal_group&0xf000)
	{
		switch(signal_group)
		{
			case BT_DBG_SEL_DBG0:
				bt_diagcntl_diag0_setf(signal_byte);
				bt_diagcntl_diag0_en_setf(1);
				break;
			case BT_DBG_SEL_DBG1:
				bt_diagcntl_diag1_setf(signal_byte);
				bt_diagcntl_diag1_en_setf(1);
				break;
			case BT_DBG_SEL_DBG2:
				bt_diagcntl_diag2_setf(signal_byte);
				bt_diagcntl_diag2_en_setf(1);
				break;
			case BT_DBG_SEL_DBG3:
				bt_diagcntl_diag3_setf(signal_byte);
				bt_diagcntl_diag3_en_setf(1);
				break;
			default:break;
		}
		reg_bt_dbg_sel |= signal_group;
		reg_bt_dbg_sel |= BT_DBG_SEL_EN;
	}
	else
	{
		while(1);
	}
}

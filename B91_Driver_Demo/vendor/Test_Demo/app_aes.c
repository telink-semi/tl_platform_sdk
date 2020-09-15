/********************************************************************************************************
 * @file	app_aes.c
 *
 * @brief	This is the source file for B91
 *
 * @author	X.P.C
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
#if (TEST_MODE == TEST_AES_MODE)

#define CHECK_ONE_BIT		0
#define CHECK_ALL_REG		1
#define AES_TEST 			CHECK_ALL_REG

#if (AES_TEST == CHECK_ALL_REG)
#include "reg_check.h"
#endif


#define TEST_DONE           GPIO_PB4
#define RESULT				GPIO_PB5

#define RC_CAP_VALUE		0x80	//RC cap value
#define TIME_UNIT			2400

#if (AES_TEST == CHECK_ALL_REG)
#define ERR_REG_LEN_MAX		100
static volatile reg_err_s rtn_reg_err[ERR_REG_LEN_MAX];
static volatile unsigned short rtn_reg_err_index = 0;
unsigned short rtn = 0;
#endif

#if (AES_TEST == CHECK_ONE_BIT)
#define REG_CHECK_ADDR		0x16000c // 0x16000c,bit3,default value 1 	0x160030,bit2,default value 0  0x160070,bit4,default value 0
#define REG_CHECK_BIT		3		 // bit3
#define REG_CHECK_FLAG 		1		 // default value 1
#define REG_CHECK_TIMES		1000
static volatile unsigned short err_times = 0;
#endif

void delay(unsigned short n)
{
	for(volatile unsigned int i = 0; i < n * TIME_UNIT; i++)
	{
		asm("NOP");
	}
}

void pwr_down_up_BB(void)
{
	analog_write_reg8(0x7d,0x87);//power down baseband
	delay(1);
	analog_write_reg8(0x7d,0x80);//power on baseband
	delay(1);
}

#if (AES_TEST == CHECK_ONE_BIT)
unsigned char rd_byte;
unsigned short reg_bit_check(unsigned int addr, unsigned char bit, unsigned short times)
{
	unsigned short rtn = 0, i;
//	unsigned char rd_byte;
	for(i = 0; i < times; i++)
	{
		pwr_down_up_BB();
		rd_byte = (read_reg32(addr / 4 *4) >> ((addr % 4)*8)) & 0xff;
		if(((rd_byte & (1 << bit)) >> bit) != REG_CHECK_FLAG )
		{
			rtn++;
		}
	}

	return rtn;
}
#endif

#if (AES_TEST == CHECK_ALL_REG)
void reg_check_step(unsigned int base_addr, reg_check_s* r_check, unsigned short len)
{
	unsigned int r_addr, temp_addr;
	unsigned short i;
	unsigned char r_data;

	for(i = 0; i < len; i++)
	{
		temp_addr = r_check[i].addr;
		r_addr = ((temp_addr - base_addr) / 4) * 4 + base_addr;
		r_data = (read_reg32(r_addr) >> (((temp_addr - base_addr) % 4) * 8)) & 0xff;
		if(r_data != r_check[i].value && r_check[i].rw == 0)
		{
			rtn_reg_err[rtn_reg_err_index].addr = r_check[i].addr;
			rtn_reg_err[rtn_reg_err_index].value = r_check[i].value;
			rtn_reg_err[rtn_reg_err_index].value_e = r_data;
			rtn_reg_err[rtn_reg_err_index].rw = r_check[i].rw;
			rtn_reg_err_index++;
			if(rtn_reg_err_index >= ERR_REG_LEN_MAX)
				rtn_reg_err_index = 0;
			rtn += 1;
		}
	}
}

unsigned short reg_check()
{
	unsigned short len;
	//check 0x140b00
	len = sizeof(reg_0x140b00) / sizeof(reg_check_s);
	reg_check_step(0x140b00, reg_0x140b00, len);
	//check 0x140c00
	len = sizeof(reg_0x140c00) / sizeof(reg_check_s);
	reg_check_step(0x140c00, reg_0x140c00, len);
	//check 0x140e00
	len = sizeof(reg_0x140e00) / sizeof(reg_check_s);
	reg_check_step(0x140e00, reg_0x140e00, len);
	//check 0x160000
	len = sizeof(reg_0x160000) / sizeof(reg_check_s);
	reg_check_step(0x160000, reg_0x160000, len);
	//check 0x160400
	len = sizeof(reg_0x160400) / sizeof(reg_check_s);
	reg_check_step(0x160400, reg_0x160400, len);
	//check 0x160800
	len = sizeof(reg_0x160800) / sizeof(reg_check_s);
	reg_check_step(0x160800, reg_0x160800, len);

	return rtn;
}
#endif

static volatile int debug_temp = 1;
static volatile unsigned short err_times_buff[3];
void user_init()
{
//	reg_rst 	= 0xffffffff;   //reset function will be cleared by set "1",which is different from the previous configuration
//	reg_clk_en 	= 0xffffffff;
//#if 0
//	analog_write_reg32(0x52, RC_CAP_VALUE);//set RC cap value
//	analog_write_reg8(0x8c,0x02);
//#else  //use 24M XTL oscillator
//	analog_write_reg8(0x8c,0x02);
//	analog_write_reg8(0x06,analog_read_reg8(0x06) & ~(BIT(0)));//
//	analog_write_reg8(0x05,analog_read_reg8(0x05) & (~BIT(3)));//Power up 24MHz XTL oscillator
//	clock_init(PLL_CLK_192M, PAD24M, PLL_DIV8_TO_CCLK,
//			CCLK_DIV1_TO_HCLK, HCLK_DIV1_TO_PCLK, CCLK_TO_MSPI_CLK);
//	analog_write_reg32(0x52, RC_CAP_VALUE);//set RC cap value
//#endif

	sys_init(LDO_1P4_LDO_1P8);
	CCLK_24M_HCLK_24M_PCLK_24M;

	gpio_function_en(TEST_DONE | RESULT);
	gpio_output_en(TEST_DONE | RESULT);
	gpio_input_dis(TEST_DONE | RESULT);
	gpio_set_high_level(TEST_DONE | RESULT);

#if (AES_TEST == CHECK_ALL_REG)
//	pwr_down_up_BB();
	if(reg_check() == 0)
	{
		gpio_set_low_level(RESULT);
	}
#endif

#if (AES_TEST == CHECK_ONE_BIT)
#if 0
	err_times = reg_bit_check(REG_CHECK_ADDR, REG_CHECK_BIT, REG_CHECK_TIMES);
	if(err_times)
	{
		gpio_set_low_level(RESULT);
	}
#else
	delay(1);
	analog_write_reg32(0x52, 0x00);
	err_times_buff[0] = reg_bit_check(REG_CHECK_ADDR, REG_CHECK_BIT, REG_CHECK_TIMES);
	delay(1);
	analog_write_reg32(0x52, 0x80);
	err_times_buff[1] = reg_bit_check(REG_CHECK_ADDR, REG_CHECK_BIT, REG_CHECK_TIMES);
	delay(1);
	analog_write_reg32(0x52, 0xff);
	err_times_buff[2] = reg_bit_check(REG_CHECK_ADDR, REG_CHECK_BIT, REG_CHECK_TIMES);
#endif
#endif

	gpio_set_low_level(TEST_DONE);//Test end
	debug_temp = 0;
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{

}

#endif



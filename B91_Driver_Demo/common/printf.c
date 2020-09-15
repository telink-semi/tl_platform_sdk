/********************************************************************************************************
 * @file	printf.c
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
#include "types.h"
#include <stdarg.h>
#include "printf.h"


#if(DEBUG_MODE==1)

#if (DEBUG_BUS==DEBUG_USB)

__attribute__((used)) int _write(int fd, const unsigned char *buf, int size)
{


    int    i;
    for (i = 0; i < size; i++)
    {
    	#if(BLOCK_MODE)
    		while (read_reg8(USBFIFO) & 0x02);
    	#endif
        	write_reg8(EDPS_DAT, buf[i]);

     }

    return i;
}

#elif (DEBUG_BUS==DEBUG_IO)

/**
 * @brief      This function serves to foramt string by GPIO simulate uart.
 * @param[in]  byte  -  a byte need to print
 * @return     none.
 */
_attribute_ram_code_sec_noinline_  void dr_putchar(unsigned char byte){
	unsigned char j = 0;
	unsigned int t1 = 0;
	static unsigned char init_flag = 1;
	if(init_flag==1)
	{
		TX_PIN_GPIO_EN();
		TX_PIN_PULLUP_1M();
		TX_PIN_OUTPUT_EN();//Enable output

		init_flag = 0;
	}

	unsigned char tmp_bit0 = read_reg8(TX_PIN_OUTPUT_REG) & (~(DEBUG_INFO_TX_PIN & 0xff));
	unsigned char tmp_bit1 = read_reg8(TX_PIN_OUTPUT_REG) | (DEBUG_INFO_TX_PIN & 0xff);
	unsigned char bit[10] = {0};

	bit[0] = tmp_bit0;
	bit[1] = (byte & 0x01)? tmp_bit1 : tmp_bit0;
	bit[2] = ((byte>>1) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[3] = ((byte>>2) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[4] = ((byte>>3) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[5] = ((byte>>4) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[6] = ((byte>>5) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[7] = ((byte>>6) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[8] = ((byte>>7) & 0x01)? tmp_bit1 : tmp_bit0;
	bit[9] = tmp_bit1;


	for(j = 0;j<10;j++)
	{
		t1 = clock_time();//eagle stimer register
		while(!clock_time_exceed(t1, BIT_INTERVAL));

		write_reg8(TX_PIN_OUTPUT_REG,bit[j]);        //send bit0
	}
}

__attribute__((used)) int _write(int fd, const unsigned char *buf, int size)
{


    int    i;
    for (i = 0; i < size; i++){
    	dr_putchar(buf[i]);
    }
    return i;
}

#endif

#endif





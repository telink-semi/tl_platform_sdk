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

volatile unsigned char normal_tx_buffer[5] = {0xac, 0xbc, 0xcc, 0xdc, 0xec};
volatile unsigned char normal_rx_buffer[8] = {0x00};
volatile unsigned char normal_rx_buffer1[8] = {0x00};
volatile unsigned short normal_rx_hword;
volatile unsigned short normal_rx_hword1;
volatile unsigned int normal_rx_word  __attribute__((aligned(4)))= 0x00000000;

volatile unsigned int var_dma_tx_word[1] = {0xaabbccdd};
volatile unsigned int var_dma_rx_word[1] = {0x00};

volatile unsigned char var_dma_write_addr_data[8] __attribute__((aligned(4))) = {0x39, 0xbb, 0x3a, 0xcc, 0x3b, 0xdd, 0x3c, 0xee};

volatile unsigned short NN;

void user_init(void)
{
	gpio_function_en(LED1 | LED2);
	gpio_output_en(LED1 | LED2);
	gpio_set_low_level(LED2);
#if(ALG_MODE == ALG_BYTE_MODE)
	gpio_toggle(LED2);
	analog_write_reg8(0x38, 0x11);
	analog_write_reg8(0x39, 0x22);
	analog_write_reg8(0x3a, 0x33);
	analog_write_reg8(0x3b, 0x44);
	gpio_toggle(LED2);
	normal_rx_buffer[0] = analog_read_reg8(0x38);
	normal_rx_buffer[1] = analog_read_reg8(0x39);
	normal_rx_buffer[2] = analog_read_reg8(0x3a);
	normal_rx_buffer[3] = analog_read_reg8(0x3b);
	gpio_toggle(LED2);
#elif(ALG_MODE == ALG_HWORD_MODE)
	gpio_toggle(LED2);
	analog_write_reg16(0x38, 0xccdd);
	analog_write_reg16(0x3a, 0xeeff);
	gpio_toggle(LED2);
	normal_rx_hword = analog_read_reg16(0x38);
	normal_rx_hword1 = analog_read_reg16(0x3a);
	gpio_toggle(LED2);
#elif(ALG_MODE == ALG_WORD_MODE)
	gpio_toggle(LED2);
	analog_write_reg32(0x38, 0xaabbccdd);
	gpio_toggle(LED2);
	normal_rx_word=analog_read_reg32(0x38);
	gpio_toggle(LED2);
#elif(ALG_MODE == ALG_BUFF_MODE)
	gpio_toggle(LED2);
	analog_write_buff(0x38, (unsigned char *)normal_tx_buffer, 4);
	gpio_toggle(LED2);
	analog_read_buff(0x38, (unsigned char *)normal_rx_buffer, 4);
	gpio_toggle(LED2);
#elif(ALG_MODE==ALG_DMA_WORD_MODE)
	gpio_toggle(LED2);
	analog_write_reg32_dma(DMA0, 0x38, (unsigned int*)var_dma_tx_word);
	gpio_toggle(LED2);
	analog_read_reg32_dma(DMA0, 0x38, (unsigned int*)var_dma_rx_word);
	gpio_toggle(LED2);
#elif(ALG_MODE==ALG_DMA_BUFF_MODE)
	gpio_toggle(LED2);
	analog_write_buff_dma(DMA0, 0x38, (unsigned char*)normal_tx_buffer, 4);
	gpio_toggle(LED2);
	analog_read_buff_dma(DMA0, 0x38, (unsigned char*)normal_rx_buffer, 4);
	gpio_toggle(LED2);
#elif(ALG_MODE==ALG_DMA_ADDR_DATA_MODE)
	gpio_toggle(LED2);
	analog_write_addr_data_dma(DMA0, (unsigned char*)var_dma_write_addr_data, 8);
	gpio_toggle(LED2);
	normal_rx_word=analog_read_reg32(0x39);
	gpio_toggle(LED2);
#endif
}

void main_loop(void)
{
	 delay_ms(500);
	 gpio_toggle(LED1);
	 NN++;
}


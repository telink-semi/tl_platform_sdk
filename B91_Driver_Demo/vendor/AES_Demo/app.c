/********************************************************************************************************
 * @file	app.c
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
#include "app_config.h"
#define LED1            GPIO_PB4
#define LED2            GPIO_PB5
#define LED3            GPIO_PB6
#define LED4            GPIO_PB7

unsigned char sKey[16] __attribute__((aligned(4))) = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
unsigned char plaintext[16] __attribute__((aligned(4))) = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};


unsigned char ciphertext[16] __attribute__((aligned(4))) = {0};
unsigned char deciphertext[16] __attribute__((aligned(4))) = {0};

unsigned char cipher[16] __attribute__((aligned(4))) = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

volatile unsigned char irq_flag = 0;

void user_init()
{
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
	gpio_input_dis(LED1|LED2|LED3|LED4);

#if(AES_MODE == INTERRUPT_MODE)
	core_interrupt_enable();
	plic_interrupt_enable(IRQ12_ZB_DM);
	aes_set_irq_mask(FLD_CRYPT_IRQ);
#endif

}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
#if(AES_MODE == NORMAL_MODE)
	aes_encrypt(sKey, plaintext, ciphertext);

	for(unsigned char i = 0; i < 16; i++)
	{
		if(ciphertext[i] != cipher[i])
		{
			while(1);
		}
	}

	aes_decrypt(sKey, ciphertext, deciphertext);

	for(unsigned char i = 0; i < 16; i++)
	{
		if(plaintext[i] != deciphertext[i])
		{
			while(1);
		}
	}
	gpio_toggle(LED1 | LED2 | LED3 | LED4);
	delay_ms(500);
#elif(AES_MODE == INTERRUPT_MODE)

	aes_set_key_data(sKey, plaintext);

	aes_set_mode(FLD_AES_START);   //start cipher

	while(0 == irq_flag);
	aes_get_result(ciphertext);
	irq_flag = 0;

	for(unsigned char i = 0; i < 16; i++)
	{
		if(ciphertext[i] != cipher[i])
		{
			while(1);
		}
	}

	delay_ms(500);

	aes_set_key_data(sKey, ciphertext);

	aes_set_mode(FLD_AES_START | FLD_AES_MODE);   //start decipher

	while(0 == irq_flag);
	aes_get_result(deciphertext);
	irq_flag = 0;

	for(unsigned char i = 0; i < 16; i++)
	{
		if(plaintext[i] != deciphertext[i])
		{
			while(1);
		}
	}
	delay_ms(500);
#endif
}





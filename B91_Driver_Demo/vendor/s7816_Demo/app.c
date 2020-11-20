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

volatile unsigned int  s7816_irq_cnt=0;

volatile __attribute__((aligned(4))) unsigned char s7816_rx_buff_byte[S7816_RX_BUFF_LEN] ={0};
volatile __attribute__((aligned(4))) unsigned char command[5]={0x00,0x84,0x00,0x00,0x04};//the command serves to get random number.

void user_init()
{
	s7816_set_pin(S7816_RST_PIN,S7816_VCC_PIN,S7816_CLK_PIN,S7816_TRX_PIN);
	s7816_init(S7816_UART_CHN,S7816_4MHZ,F,D);

	core_interrupt_enable();
#if( S7816_UART_CHN == S7816_UART0)
	plic_interrupt_enable(IRQ19_UART0);
#elif(S7816_UART_CHN == S7816_UART1)
	plic_interrupt_enable(IRQ18_UART1);
#endif
	uart_tx_irq_trig_level(S7816_UART_CHN, 0);
	uart_rx_irq_trig_level(S7816_UART_CHN, 1);
	uart_set_irq_mask(S7816_UART_CHN, UART_RX_IRQ_MASK);

	s7816_en(S7816_UART_CHN);//enable the 7816 module
}
void main_loop (void)
{
	/*********************activate and coldReset and set trx pin***************/
	s7816_coldreset();// the coldreset accompanied by IC-CARD activate.
	delay_ms(15);
	//s7816_warmreset(); //the warmreset is required after the IC-CARD activate.
   /*******************************TX*****************************/
    for(int i=0;i<5;i++)
    {
    	s7816_send_byte(S7816_UART_CHN,command[i]);
    	//delay_ms(0.5);//extra protect time
    }
    /******************************RX****************************/
}

/**
 * @brief		This function serves to handle the interrupt of MCU
 * @param[in] 	none
 * @return 		none
 */
#if(S7816_UART_CHN == S7816_UART0)
void uart0_irq_handler(void)
{
	if(uart_get_irq_status(UART0, UART_RXBUF_IRQ_STATUS))
	{
		if(s7816_irq_cnt<=S7816_RX_BUFF_LEN)//if the rx buff is full,it won't receive data.
	    {
			s7816_rx_buff_byte[s7816_irq_cnt] = uart_read_byte(UART0);
			s7816_irq_cnt++;
		}
	}
}


#elif(S7816_UART_CHN == S7816_UART1)
void uart1_irq_handler(void)
{
	if(uart_get_irq_status(UART1, UART_RXBUF_IRQ_STATUS))
	{
		if(s7816_irq_cnt<=S7816_RX_BUFF_LEN)
	    {
			s7816_rx_buff_byte[s7816_irq_cnt] = uart_read_byte(UART1);
			s7816_irq_cnt++;
		}
	}
}
#endif



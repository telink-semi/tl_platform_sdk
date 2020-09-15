/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91
 *
 * @author	D.M.H / B.Y
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

#if (UART_MODE==UART_NDMA)

#if( FLOW_CTR==USE_CTS)
	#define STOP_VOLT   	1			//0 :Low level stops TX.  1 :High level stops TX.
#endif

#if (FLOW_CTR==USE_RTS)
	#define RTS_MODE		UART0_RTS_MODE_AUTO 		    //It can be UART_RTS_MODE_AUTO/UART_RTS_MODE_MANUAL.
	#define RTS_THRESH		5			//UART_RTS_MODE_AUTO need.It indicates RTS trigger threshold.
	#define RTS_INVERT		1			//UART_RTS_MODE_AUTO need.0 indicates RTS_pin will change from low to hign.
	#define RTS_POLARITY	0			//UART_RTS_MODE_MANUAL need. It indicates RTS_POLARITY .
#endif

#if(BASE_TX == FLOW_CTR)
#define UART0_TX_BYTE	               1
#define UART0_TX_HWORD			       2
#define UART0_TX_WORD                  3

#define UART0_TANS_MODE				   UART0_TX_BYTE//when FLOW_CTR=BASE_TX	,it will work
#endif


volatile unsigned char uart0_rx_flag=0;
volatile unsigned int  uart0_irq_cnt=0;
volatile unsigned char uart0_irq_index=0;
volatile unsigned char uart0_cts_count=0;


/////////////////////////////////////////////////////////////////
volatile unsigned char uart1_rx_flag=0;
volatile unsigned int  uart1_irq_cnt=0;
volatile unsigned char uart1_irq_index=0;
volatile unsigned char uart1_rx_buff_byte[UART0_RX_IRQ_LEN] __attribute__((aligned(4))) ={0x00};


volatile unsigned char uart0_tx_buff_byte[16 ] __attribute__((aligned(4))) ={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
volatile unsigned char uart0_rx_buff_byte[UART0_RX_IRQ_LEN] __attribute__((aligned(4))) ={0x00};

volatile unsigned short uart0_tx_buff_hword[8] __attribute__((aligned(4))) ={0x1100,0x3322,0x5544,0x7766,0x9988,0xbbaa,0xddcc,0xffee};

volatile  unsigned int uart0_tx_buff_word[4] __attribute__((aligned(4))) = {0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};

void user_init()
{
	unsigned short div;
	unsigned char bwpc;
	gpio_function_en(LED1|LED2);
	gpio_output_en(LED1|LED2); 		//enable output
	gpio_input_dis(LED1|LED2);			//disable input
#if(FLOW_CTR == BASE_TX)
	uart_set_pin(UART0_TX_PB2, UART0_RX_PB3 );// uart tx/rx pin set
	uart_cal_div_and_bwpc(115200, sys_clk.pclk*1000*1000, &div, &bwpc);
	uart_init(UART0, div, bwpc, UART_PARITY_NONE, UART_STOP_BIT_ONE);
#endif

#if( FLOW_CTR == NORMAL)
	core_interrupt_enable();
	uart_set_pin(UART0_TX_PB2, UART0_RX_PB3 );// uart tx/rx pin set
	uart_cal_div_and_bwpc(115200, sys_clk.pclk*1000*1000, &div, &bwpc);
	uart_init(UART0, div, bwpc, UART_PARITY_NONE, UART_STOP_BIT_ONE);
	plic_interrupt_enable(IRQ19_UART0);
	uart_tx_irq_trig_level(UART0, 0);
	uart_rx_irq_trig_level(UART0, 1);
	uart_set_irq_mask(UART0, UART_RX_IRQ_MASK);
	uart_set_irq_mask(UART0, UART_ERR_IRQ_MASK);

	uart_set_pin(UART1_TX_PE0, UART1_RX_PE2 );// uart tx/rx pin set
	uart_cal_div_and_bwpc(115200, sys_clk.pclk*1000*1000, &div, &bwpc);
	uart_set_dma_rx_timeout(UART1, bwpc, 12, UART_BW_MUL1);
	uart_init(UART1, div, bwpc, UART_PARITY_NONE, UART_STOP_BIT_ONE);

	plic_interrupt_enable(IRQ18_UART1);
	uart_tx_irq_trig_level(UART1, 0);
	uart_rx_irq_trig_level(UART1, 1);
	uart_set_irq_mask(UART1, UART_RX_IRQ_MASK);
	uart_set_irq_mask(UART1, UART_ERR_IRQ_MASK);

#elif( FLOW_CTR == USE_CTS)
	uart_cts_config(UART0,UART0_CTS_PA1,STOP_VOLT);
	uart_set_cts_en(UART0);
	uart_clr_irq_mask(UART0, UART_RX_IRQ_MASK | UART_TX_IRQ_MASK);
#elif( FLOW_CTR == USE_RTS)
	uart_set_rts_en(UART0);
	uart_rts_config(UART0,UART0_RTS_PA2,RTS_INVERT,UART_RTS_MODE_AUTO);
	uart_rts_trig_level_auto_mode(UART0, RTS_THRESH);
	uart_clr_irq_mask(UART0, UART_RX_IRQ_MASK | UART_TX_IRQ_MASK);
#endif

}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
	delay_ms(500);
	gpio_toggle(LED1);
#if( FLOW_CTR == BASE_TX)

#if(UART0_TANS_MODE==UART0_TX_BYTE)

	for(unsigned char i=0;i<16;i++)
	{
		uart_send_byte(UART0, uart0_tx_buff_byte[i]);
	}
	uart0_tx_buff_byte[0]++;
#elif(UART0_TANS_MODE==UART0_TX_HWORD)
	for(unsigned char i=0;i<8;i++)
	{
		uart_send_hword(UART0, uart0_tx_buff_hword[i]);
	}
	uart0_tx_buff_hword[0]++;
#elif(UART0_TANS_MODE==UART0_TX_WORD)

	for(unsigned char i=0;i<4;i++)
	{
		uart_send_word(UART0, uart0_tx_buff_word[i]);
	}
	uart0_tx_buff_word[0]++;

#endif


#elif( FLOW_CTR == NORMAL)
	if(uart0_rx_flag>0)
	{
		uart0_irq_cnt=0; //Clear uart_irq_cnt
		uart0_rx_flag=0;
		for(unsigned char i=0;i<UART0_RX_IRQ_LEN;i++)
		{

			uart_send_byte(UART0, uart0_rx_buff_byte[i]);
		}
	}

	////////////////////////////////////////////////////////////////////////
	if(uart1_rx_flag>0)
	{
		uart1_irq_cnt=0; //Clear uart_irq_cnt
		uart1_rx_flag=0;
		for(unsigned char i=0;i<UART0_RX_IRQ_LEN;i++)
		{
			uart_send_byte(UART1, uart1_rx_buff_byte[i]);
		}
	}
#elif( FLOW_CTR == USE_CTS)
	uart_send_byte(UART0, uart0_tx_buff_byte[uart0_cts_count]);
	uart0_cts_count++;
	if(uart0_cts_count == 16)
	{
		uart0_cts_count = 0;
	}
#elif( FLOW_CTR == USE_RTS)
	while(1);
#endif
}


/**
 * @brief		This function serves to handle the interrupt of MCU
 * @param[in] 	none
 * @return 		none
 */
_attribute_ram_code_sec_noinline_ void uart0_irq_handler(void)
{
#if( FLOW_CTR == NORMAL)
	if(uart_get_irq_status(UART0, UART_RXBUF_IRQ_STATUS))
	{
		if(uart0_rx_flag==0)
		{
			uart0_rx_buff_byte[uart0_irq_cnt++] = uart_read_byte(UART0);
		    if((uart0_irq_cnt%UART0_RX_IRQ_LEN==0)&&(uart0_irq_cnt!=0))
		    {
				uart0_rx_flag=1;
			}
		}
		else
		{
			uart_read_byte(UART0);
		}
	}

	if(uart_get_irq_status(UART0, UART_RX_ERR))
	{
		uart_clr_irq_status(UART0,UART_CLR_RX);
		uart_clr_rx_index(UART0);
		uart_reset(UART0);
	}
#endif
}

void uart1_irq_handler(void)
{
#if( FLOW_CTR == NORMAL)

	if(uart_get_irq_status(UART1, UART_RXBUF_IRQ_STATUS))
	{
		if(uart1_rx_flag==0)
		{
			uart1_rx_buff_byte[uart1_irq_cnt++] = uart_read_byte(UART1);
			if((uart1_irq_cnt%UART0_RX_IRQ_LEN==0)&&(uart1_irq_cnt!=0))
			{
				uart1_rx_flag=1;
			}
		}

		else
		{
			uart_read_byte(UART1);
		}
	}

	if(uart_get_irq_status(UART1, UART_RX_ERR))
	{
		uart_clr_irq_status(UART1,UART_CLR_RX);
		uart_clr_rx_index(UART1);
		uart_reset(UART1);
	}
#endif
}
#endif













/********************************************************************************************************
 * @file	app_dma.c
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

#if (UART_MODE==UART_DMA)

#if( FLOW_CTR==USE_CTS)
	#define STOP_VOLT   	1			//0 :Low level stops TX.  1 :High level stops TX.
#endif

#if (FLOW_CTR==USE_RTS)
	#define RTS_MODE		UART0_RTS_MODE_AUTO 		    //It can be UART_RTS_MODE_AUTO/UART_RTS_MODE_MANUAL.
	#define RTS_THRESH		5			//UART_RTS_MODE_AUTO need.It indicates RTS trigger threshold.
	#define RTS_INVERT		1			//UART_RTS_MODE_AUTO need.1 indicates RTS_pin will change from low to hign.
	#define RTS_POLARITY	0			//UART_RTS_MODE_MANUAL need. It indicates RTS_POLARITY .
#endif

#define UART_MASTER_DEVICE   1
#define UART_SLAVE_DEVICE    2

#define UART_DEVICE        UART_MASTER_DEVICE

#define UART_DMA_CHANNEL_RX  DMA2
#define UART_DMA_CHANNEL_TX  DMA3

#define UART_DMA_RX_IRQ_CHANNEL  FLD_DMA_CHANNEL2_IRQ
#define UART_DMA_TX_IRQ_CHANNEL  FLD_DMA_CHANNEL3_IRQ

volatile unsigned char tx_byte_buff[16] __attribute__((aligned(4))) ={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

volatile unsigned char rec_buff[32] __attribute__((aligned(4))) = {0};

volatile unsigned char uart_dma_send_flag = 1;
volatile unsigned char rev_data_len=0;

void user_init()
{
	unsigned short div;
	unsigned char bwpc;


	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4); 	//enable output
	gpio_input_dis(LED1|LED2|LED3|LED4);   //disable input

	uart_reset(UART0);
#if( UART_WIRE_MODE == UART_1WIRE_MODE)
	uart_set_rtx_pin(UART0_RX_PB3);// uart0 rtx pin set
	uart_rtx_en(UART0);
#elif(UART_WIRE_MODE == UART_2WIRE_MODE)
	uart_set_pin(UART0_TX_PB2,UART0_RX_PB3);
#endif
	uart_cal_div_and_bwpc(115200, sys_clk.pclk*1000*1000, &div, &bwpc);
	uart_set_dma_rx_timeout(UART0, bwpc, 12, UART_BW_MUL1);
	uart_init(UART0, div, bwpc, UART_PARITY_NONE, UART_STOP_BIT_ONE);

#if( FLOW_CTR ==  USE_CTS )
	uart_cts_config(UART0,UART0_CTS_PA1,STOP_VOLT);
	uart_set_cts_en(UART0);
#elif( FLOW_CTR ==   USE_RTS )
	uart_set_rts_en(UART0);
	uart_rts_config(UART0,UART0_RTS_PA2,RTS_INVERT,UART_RTS_MODE_AUTO);
	uart_rts_trig_level_auto_mode(UART0, RTS_THRESH);
#endif
	core_interrupt_enable();
	uart_set_tx_dma_config(UART0, UART_DMA_CHANNEL_TX);
	uart_set_rx_dma_config(UART0, UART_DMA_CHANNEL_RX);
	uart_clr_tx_done(UART0);
	dma_clr_irq_mask(UART_DMA_CHANNEL_TX,TC_MASK|ABT_MASK|ERR_MASK);
	dma_clr_irq_mask(UART_DMA_CHANNEL_RX,TC_MASK|ABT_MASK|ERR_MASK);
#if(CHIP_VER==CHIP_VER_A0)
	dma_set_irq_mask(UART_DMA_CHANNEL_RX, TC_MASK);
	plic_interrupt_enable(IRQ5_DMA);
#elif(CHIP_VER==CHIP_VER_A1)
	uart_set_irq_mask(UART0, UART_RXDONE_MASK);
#endif
	uart_set_irq_mask(UART0, UART_TXDONE_MASK);
	plic_interrupt_enable(IRQ19_UART0);
	uart_receive_dma(UART0, (unsigned char*)rec_buff,16);
}
void main_loop (void)
{
#if( (FLOW_CTR == NORMAL)||(FLOW_CTR ==  USE_CTS))

#if(UART_DEVICE==UART_MASTER_DEVICE)
	gpio_toggle(LED1);
	if(uart_dma_send_flag==1)
	{
		uart_send_dma(UART0, (unsigned char*)tx_byte_buff, 16);
		uart_dma_send_flag=0;
	}

#elif(UART_DEVICE==UART_SLAVE_DEVICE)
	gpio_toggle(LED1);
	delay_ms(500);
#endif
#elif(FLOW_CTR ==  USE_RTS)
    while(1);
#endif
}
#if( (FLOW_CTR == NORMAL)||(FLOW_CTR ==  USE_CTS))

_attribute_ram_code_sec_ void uart0_irq_handler(void)
{
    if(uart_get_irq_status(UART0,UART_TXDONE))
	{
    	uart_dma_send_flag=1;
		gpio_toggle(LED2);
	    uart_clr_tx_done(UART0);
	}
#if(CHIP_VER==CHIP_VER_A1)
    if(uart_get_irq_status(UART0,UART_RXDONE)) //A0-SOC can't use RX-DONE status,so this interrupt can noly used in A1-SOC.
    {
    	gpio_toggle(LED3);
    	/************************get the length of receive data****************************/
    	if(((reg_uart_status1(UART0)&FLD_UART_RBCNT)%4)==0)
    	{
    		rev_data_len=4*(0xffffff-reg_dma_size(UART_DMA_CHANNEL_RX));
    	}
    	else
    	{
    		rev_data_len=4*(0xffffff-reg_dma_size(UART_DMA_CHANNEL_RX)-1)+(reg_uart_status1(UART0)&FLD_UART_RBCNT)%4;
    	}
    	/************************cll rx_irq****************************/
    	uart_clr_irq_status(UART0,UART_CLR_RX);
    	uart_send_dma(UART0, (unsigned char*)rec_buff, rev_data_len);
    	uart_receive_dma(UART0, (unsigned char*)rec_buff,32);
    	if((uart_get_irq_status(UART0,UART_RX_ERR)))
    	{
    		uart_clr_irq_status(UART0,UART_CLR_RX);
    	}
    }
#endif
}
#if(CHIP_VER==CHIP_VER_A0)
_attribute_ram_code_sec_ void dma_irq_handler(void)
{
	if(dma_get_tc_irq_status(UART_DMA_RX_IRQ_CHANNEL))
	{
		dma_clr_tc_irq_status(UART_DMA_RX_IRQ_CHANNEL);
		gpio_toggle(LED1);
		uart_receive_dma(UART0, (unsigned char*)rec_buff,16);
		if(uart_dma_send_flag==1)
		{
			uart_send_dma(UART0, (unsigned char*)tx_byte_buff, 16);
			uart_dma_send_flag=0;
	    }
	}
}
#endif
#endif

#endif













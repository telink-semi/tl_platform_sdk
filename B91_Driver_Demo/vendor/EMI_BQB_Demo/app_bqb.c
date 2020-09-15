/********************************************************************************************************
 * @file	app_bqb.c
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
#include "BQB/bqb.h"
#if(TEST_DEMO==BQB_DEMO)

#define BQB_PA_TX_PORT     RFFE_TX_PD1
#define BQB_PA_RX_PORT     RFFE_RX_PD0
/* set uart port */
//#define BQB_UART_TX_PORT   	UART0_TX_PB2
//#define BQB_UART_RX_PORT   	UART0_RX_PB3
#define BQB_UART_BUAD	   	115200


uart_num_redef get_uart_num(uart_tx_pin_e tx_pin,uart_rx_pin_e rx_pin)
{
	uart_num_redef tx_flag = UART_NONE, rx_flag = UART_NONE;
	if(tx_pin == UART0_TX_PA3 || tx_pin == UART0_TX_PB2 || tx_pin == UART0_TX_PD2)
	{
		tx_flag = UART_NUM0;
	}
	else if(tx_pin == UART1_TX_PC6 || tx_pin == UART1_TX_PD6 || tx_pin == UART1_TX_PE0)
	{
		tx_flag = UART_NUM1;
	}
	else
	{
		return UART_NONE;
	}

	if(rx_pin == UART0_RX_PA4 || rx_pin == UART0_RX_PB3 || rx_pin == UART0_RX_PD3)
	{
		rx_flag = UART_NUM0;
	}
	else if(rx_pin == UART1_RX_PC7 || rx_pin == UART1_RX_PD7 || rx_pin == UART1_RX_PE2)
	{
		rx_flag = UART_NUM1;
	}
	else
	{
		return UART_NONE;
	}

	if(rx_flag == tx_flag)
	{
		return rx_flag;
	}
	else
	{
		return UART_NONE;
	}
}

uart_num_redef uart_setup(uart_tx_pin_e tx_pin,uart_rx_pin_e rx_pin,
			unsigned int boardrate, unsigned int sys_clk,
			uart_parity_e parity, uart_stop_bit_e stop_bit)
{
	unsigned short div = 0;
	unsigned char bwpc = 0;
	uart_num_redef uart_num = UART_NONE;
	uart_num = get_uart_num(tx_pin, rx_pin);
	if(uart_num == UART_NONE)
	{
		assert(uart_num == UART_NONE);
		return UART_NONE;
	}
	uart_set_pin(tx_pin, rx_pin);
	uart_reset(uart_num);
	uart_cal_div_and_bwpc(boardrate, sys_clk, &div, &bwpc);
	uart_set_dma_rx_timeout(uart_num, bwpc, 12, UART_BW_MUL1);
	uart_init(uart_num, div, bwpc, parity, stop_bit);

	return uart_num;
}

usr_def_u usr_def_byte;
void get_uart_port(uart_tx_pin_e* bqb_uart_tx_port, uart_rx_pin_e* bqb_uart_rx_port)
{
	unsigned char flash_size;
	flash_read_page(ADDR_FLASH_SIZE, 1, &flash_size);
	if(flash_size == 4)
	{
		flash_read_page(UART_SET_FLASH_ADDR_512K, 1, &(usr_def_byte.usr_def));
	}
	else if (flash_size == 1)
	{
		flash_read_page(UART_SET_FLASH_ADDR_128K, 1, &(usr_def_byte.usr_def));
	}
	else
	{
		flash_read_page(UART_SET_FLASH_ADDR_512K, 1, &(usr_def_byte.usr_def));
	}
	switch(usr_def_byte.uart)
	{
//	UART0
//	UART0_TX_PA3
	case 0:
		*bqb_uart_tx_port = UART0_TX_PA3;
		*bqb_uart_rx_port = UART0_RX_PA4;
		break;
	case 1:
		*bqb_uart_tx_port = UART0_TX_PA3;
		*bqb_uart_rx_port = UART0_RX_PB3;
		break;
	case 2:
		*bqb_uart_tx_port = UART0_TX_PA3;
		*bqb_uart_rx_port = UART0_RX_PD3;
		break;
//	UART0_TX_PB2
	case 3:
		*bqb_uart_tx_port = UART0_TX_PB2;
		*bqb_uart_rx_port = UART0_RX_PA4;
		break;
	case 4:
		*bqb_uart_tx_port = UART0_TX_PB2;
		*bqb_uart_rx_port = UART0_RX_PB3;
		break;
	case 5:
		*bqb_uart_tx_port = UART0_TX_PB2;
		*bqb_uart_rx_port = UART0_RX_PD3;
		break;
//	UART0_TX_PD2
	case 6:
		*bqb_uart_tx_port = UART0_TX_PD2;
		*bqb_uart_rx_port = UART0_RX_PA4;
		break;
	case 7:
		*bqb_uart_tx_port = UART0_TX_PD2;
		*bqb_uart_rx_port = UART0_RX_PB3;
		break;
	case 8:
		*bqb_uart_tx_port = UART0_TX_PD2;
		*bqb_uart_rx_port = UART0_RX_PD3;
//	UART1
//	UART1_TX_PC6
	case 9:
		*bqb_uart_tx_port = UART1_TX_PC6;
		*bqb_uart_rx_port = UART1_RX_PC7;
		break;
	case 10:
		*bqb_uart_tx_port = UART1_TX_PC6;
		*bqb_uart_rx_port = UART1_RX_PD7;
		break;
	case 11:
		*bqb_uart_tx_port = UART1_TX_PC6;
		*bqb_uart_rx_port = UART1_RX_PE2;
		break;
//	UART1_TX_PD6
	case 12:
		*bqb_uart_tx_port = UART1_TX_PD6;
		*bqb_uart_rx_port = UART1_RX_PC7;
		break;
	case 13:
		*bqb_uart_tx_port = UART1_TX_PD6;
		*bqb_uart_rx_port = UART1_RX_PD7;
		break;
	case 14:
		*bqb_uart_tx_port = UART1_TX_PD6;
		*bqb_uart_rx_port = UART1_RX_PE2;
		break;
//	UART1_TX_PE0
	case 15:
		*bqb_uart_tx_port = UART1_TX_PE0;
		*bqb_uart_rx_port = UART1_RX_PC7;
		break;
	case 16:
		*bqb_uart_tx_port = UART1_TX_PE0;
		*bqb_uart_rx_port = UART1_RX_PD7;
		break;
	case 17:
		*bqb_uart_tx_port = UART1_TX_PE0;
		*bqb_uart_rx_port = UART1_RX_PE2;
		break;
	default:
		break;
	}
}

uart_num_redef uart_using = UART_NONE;
void user_init(void)
{
//	gpio_function_en(LED1);
//	gpio_output_en(LED1); //enable output
//	gpio_input_dis(LED1);	 //disable input
//	gpio_set_high_level(LED1);         //LED On

	uart_tx_pin_e bqb_uart_tx_port = UART0_TX_PB2;
	uart_rx_pin_e bqb_uart_rx_port = UART0_RX_PB3;
	get_uart_port(&bqb_uart_tx_port, &bqb_uart_rx_port);
	uart_using = uart_setup(bqb_uart_tx_port, bqb_uart_rx_port,
							BQB_UART_BUAD,
							sys_clk.pclk*1000*1000,
							UART_PARITY_NONE, UART_STOP_BIT_ONE);
	uart_set_irq_mask(uart_using, UART_RX_IRQ_MASK);
	uart_clr_irq_mask(uart_using, UART_TX_IRQ_MASK);
	uart_rx_irq_trig_level(uart_using, 1);
	bqbtest_init();
	//SET PA PORT
//	rf_rffe_set_pin(BQB_PA_TX_PORT,BQB_PA_RX_PORT);
}

void main_loop(void)
{
	bqb_serviceloop();
}

#endif

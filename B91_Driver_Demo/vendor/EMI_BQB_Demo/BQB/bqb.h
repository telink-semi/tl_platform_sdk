/********************************************************************************************************
 * @file	bqb.h
 *
 * @brief	This is the header file for B91
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
#ifndef BQB_H_
#define BQB_H_

#include "../app_config.h"

#if(TEST_DEMO==BQB_DEMO)

/* set supporting configuration */
#define SUPPORT_CONFIGURATION	0

/* set power of Tx */
#define BQB_TX_POWER		RF_POWER_INDEX_P6p98dBm
#define ACCESS_CODE        	0x29417671

/* set configuration flash address */
#if SUPPORT_CONFIGURATION
#define ADDR_USR_DEFINITION 		0x04
#endif

/* set flash address to set internal cap value and switch internal/external cap */
#if SUPPORT_CONFIGURATION
#define CAP_SET_FLASH_ADDR_2M 		0x1fe000
#define CAP_SET_FLASH_ADDR_1M 		0xfe000
#define CAP_SET_FLASH_ADDR_512K 	0x7e000
#else
#define SWITCH_INTERNAL_CAP 		1		// 0: external cap, 1: internal cap
#define CAP_SET_FLASH_ADDR 			0xfe000 // 512K Flash: 0x7e000, 1M FLASH: 0xfe000, 2M FLASH: 0x1fe000
#endif

/* set uart port */
#define BQB_UART_TX_PORT   	UART0_TX_PB2
#define BQB_UART_RX_PORT   	UART0_RX_PB3
#define BQB_UART_BUAD	   	115200

/* set TX return result */
#define RETURN_TX_LEN_EN    0      //1: return tx length, 0:do not return tx length


/**
 *  @brief  command type for BQB Test
 */
typedef enum{
	CMD_SETUP=0,
	CMD_RX_TEST=1,
	CMD_TX_TEST=2,
	CMD_END=3,
}Test_Command_e;

/**
 *  @brief  command status for BQB Test
 */
typedef enum {
	SETUP_STATE=0x10,
	RX_STATE,
	TX_STATE,
	END_STATE
}Test_Status_e;

typedef enum
{
	UART_NUM0 = UART0,
	UART_NUM1 = UART1,
	UART_NONE,
}uart_num_redef_e;

#if SUPPORT_CONFIGURATION
/**
 *  @brief  union structure for configuration
 */
typedef union
{
	unsigned char usr_def;
	struct
	{
		unsigned char uart :5;
		unsigned char cap  :1;
		unsigned char f_size:2;
	}usr_def_t;
}usr_def_u;

/* global value for configuration */
extern usr_def_u usr_def_byte;
#endif

/* global value for uart */
extern uart_num_redef_e uart_using;

/**
 * @brief   	This function serves to initialize  BQB
 * @param[in]   flash_size - flash size: 0->512K, 1->2M, 2-0xff->1M.
 * @return  	none.
 */
void  bqbtest_init();


/**
 * @brief   This function serves to read the usrt data and execute BQB program
 * @param   none.
 * @return  none.
 */
void bqb_serviceloop (void);


/**
 * @brief     uart send data function with not DMA method.
 *            variable uart_TxIndex,it must cycle the four registers 0x90 0x91 0x92 0x93 for the design of SOC.
 *            so we need variable to remember the index.
 * @param[in] uartData - the data to be send.
 * @return    none
 */
void bqb_uart_send_byte(unsigned char uartData);

#endif

#endif /* BQB_H_ */

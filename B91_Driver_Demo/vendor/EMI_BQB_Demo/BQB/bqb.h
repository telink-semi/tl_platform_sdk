/********************************************************************************************************
 * @file	bqb.h
 *
 * @brief	This is the header file for B91
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
#ifndef BQB_H_
#define BQB_H_

#include "../app_config.h"

#if(TEST_DEMO==BQB_DEMO)

#define RETURN_TX_LEN_EN    0          			//1: return tx length, 0:not return tx length
/* set the length of preamble */
#define BQB_PREAMBLE_LEN   	6
/* set power of Tx */
#define BQB_TX_POWER		RF_POWER_INDEX_P6p98dBm
#define ACCESS_CODE        	0x29417671

#define AUTO 0

/**
 *  @brief  command type for BQB Test
 */
#define	CMD_SETUP			0
#define	CMD_RX_TEST			1
#define	CMD_TX_TEST			2
#define	CMD_END				3

/**
 *  @brief  Event type for BQB Test
 */
#define STATUS_EVENT_MASK	(0)
#define REPORT_EVENT_MASK	(BIT(15))


/**
 *  @brief  command status for BQB Test
 */
typedef enum {
	SETUP_STATE=0x10,
	RX_STATE,
	TX_STATE,
	END_STATE
}Test_Status_t;


/**
 * @brief   This function serves to initialize  BQB
 * @param   none.
 * @return  none.
 */
void  bqbtest_init(void);



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
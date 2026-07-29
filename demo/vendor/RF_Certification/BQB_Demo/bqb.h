/********************************************************************************************************
 * @file    bqb.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef BQB_H_
#define BQB_H_
#include "common.h"
#include "../common/rf_certification.h"

/**
 *  @brief  command type for BQB Test
 */
typedef enum
{
    CMD_SETUP   = 0,
    CMD_RX_TEST = 1,
    CMD_TX_TEST = 2,
    CMD_END     = 3,
} Test_Command_e;

/**
 *  @brief  command status for BQB Test
 */
typedef enum
{
    SETUP_STATE = 0x10,
    RX_STATE,
    TX_STATE,
    END_STATE
} Test_Status_e;

typedef enum
{
    UART_NUM0 = UART0,
    UART_NUM1 = UART1,
    UART_NONE,
} uart_num_redef_e;

/* global value for configuration */
extern bqb_setting_t g_bqb_setting;


/* global value for uart */
extern uart_num_redef_e uart_using;

/**
 * @brief       This function serves to initialize  BQB
 * @param[in]   flash_size - flash size: 0->512K, 1->2M, 2-0xff->1M.
 * @return      none.
 */
void bqbtest_init(void);


/**
 * @brief       This function is used for initialization of the pa pin.
 * @param        none.
 * @return      none.
 */
extern void bqb_pa_init(void);

/**
 * @brief       This function is used to set the mode of pa.
 * @param[in]    rtx:0:rx, 1:tx, other:off.
 * @return      none.
 */
extern void bqb_pa_set_mode(unsigned char rtx); //0:rx, 1:tx, other:off


/**
 * @brief   This function serves to read the uart data and execute BQB program
 * @param   none.
 * @return  none.
 */
void bqb_serviceloop(void);

/**
 * @brief     uart send data function with not DMA method.
 *            variable uart_TxIndex,it must cycle the four registers 0x90 0x91 0x92 0x93 for the design of SOC.
 *            so we need variable to remember the index.
 * @param[in] uartData - the data to be send.
 * @return    none
 */
void bqb_uart_send_byte(unsigned char uartData);


/**
 * @brief       This function is used to initialize the calibration value of rf fast settle
 * @param[in]   none.
 * @return      none.
 * @note        This function is only used when testing fast settle with BQB
 */
void bqb_fast_settle_init(void);

#endif /* BQB_H_ */

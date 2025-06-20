/********************************************************************************************************
 * @file    pc_interface.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2023, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef PC_INTERFACE_H
#define PC_INTERFACE_H

#include "driver.h"
/****************************************************************************************************************************
 * Note:
 * -1.this block of address is very safe,and it would not be interrupted because of unreasonable definition
 * by programmer or automatic allocation mechanism in processing of program. It is why we use this part of address!
 *
 * -2.a block of continuous address is created in ram,which is divided into two parts :one part is used to receive command
 * from the upper monitor,another part is used to send result waited to read by the upper monitor
 *
 * -3.In order to advance the speed of the whole system,we consider to use Multi-layer fifo to upload or download data.
 *
****************************************************************************************************************************/

/**
 * @brief  Those macro definition to save parameter and test result according to base address.
 */
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    #define PARA_BASE_ADDR 0x00000004
#elif defined(MCU_CORE_TL7518)
    #define PARA_BASE_ADDR 0x00020004 // D25
// #define PARA_BASE_ADDR    0x50020004    // N22
#elif defined(MCU_CORE_TL751X)
    #define PARA_BASE_ADDR 0x00020004 // D25
// #define PARA_BASE_ADDR    0x50020004    // N22
#elif defined(MCU_CORE_TL753X)
    #define PARA_BASE_ADDR 0x00020004 // D25
// #define PARA_BASE_ADDR    0x50020004    // N22
#elif defined(MCU_CORE_TL721X)
    #define PARA_BASE_ADDR 0x00040004
#elif defined(MCU_CORE_TL321X)
    #define PARA_BASE_ADDR 0x00068004
#elif defined(MCU_CORE_W92)
    #define PARA_BASE_ADDR 0x00020004 // D25
#elif defined(MCU_CORE_TL322X)
    #define PARA_BASE_ADDR 0x00000004
#elif defined(MCU_CORE_TL323X)
    #define PARA_BASE_ADDR 0x00000004
#endif
/*
 * Since data conflicts occur on the B85M in the form of fixed addresses,
 * the Telink RISC-V MCU is also managed in the form of dynamically allocated memory addresses in order to consider compatibility.
 * This form finds a 4-byte aligned starting address in the data area,
 * and then assigns address to each parameter according to this address.
 */
#define PARA_BUF_CHECK    (par_addr + 0x0) // save the address of par_addr to be checked by the upper monitor
#define PARA_BUF_ADDR     (par_addr + 0x4) // set the address of buffer of command from the upper monitor
#define PARA_BUF_SIZE     (par_addr + 0x8) // set the size of address of buffer of command from the upper monitor
#define PARA_BUF_CNT      (par_addr + 0x9) // set layers of fifo
#define PARA_BUF_WPTR     (par_addr + 0xa)
#define PARA_BUF_RPTR     (par_addr + 0xb)

#define RESU_BUF_ADDR     (par_addr + 0xc)  // save the result to the specified location waiting to be read by the upper monitor
#define RESU_BUF_SIZE     (par_addr + 0x10) // set the length of result buffer
#define RESU_BUF_CNT      (par_addr + 0x11) // set the layers of fifo to save result data waiting to be read by the upper monitor
#define RESU_BUF_WPTR     (par_addr + 0x12)
#define RESU_BUF_RPTR     (par_addr + 0x13)

#define COMMAND_BUFF_SIZE 64
#define COMMAND_BUFF_CNT  4
#define RESULT_BUFF_SIZE  64
#define RESULT_BUFF_CNT   4

extern unsigned char command_buff[COMMAND_BUFF_CNT][COMMAND_BUFF_SIZE];
extern unsigned char result_buff[RESULT_BUFF_CNT][RESULT_BUFF_SIZE];
extern unsigned char para_buff[COMMAND_BUFF_SIZE];

extern volatile unsigned char par_addr[20] __attribute__((aligned(4)));

/**
 * @brief       This struct define the format of command/result package.
 * @note        payload        - 60 byte.
 *              payload_length - 2 byte
 *              crc            - 2 byte
 */
typedef struct
{
    unsigned char payload[60];
    unsigned int  payload_length : 16;
    unsigned char crc[2];
} autotest_package_t, *autotest_package_t_ptr;

#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
/**
 * @brief       This function is used to convert cpu address to bus address.
 * @param[in]   addr - the addr need to be converted.
 * @return      bus_addr
 */
extern unsigned int convert_addr2bus(unsigned int addr);
#endif

/**
 * @brief       This function is used to initiate the buffer of command.
 * @param[in]   none
 * @return      none
 */
extern void para_buff_init(void);
/**
 * @brief       This function is used to get the command from the upper monitor.
 * @return      none
 */
extern unsigned int para_buff_have_data(void);
/**
 * @brief       This function is used to read command from the upper monitor.
 * @param[in]   *dest_buf - save the command to the specified location waiting to be executed.
 * @param[in]   len       - set the length of command waiting to read.
 * @return      crc_flag  - 1(CRC correct)  -1(CRC error)
 */
extern int para_buff_read(unsigned char *dest_buf, unsigned char len);
/**
 * @brief       This function is used to initiate the result buffer.
 * @param[in]   none
 * @return      none
 */
extern void result_buff_init(void);
/**
 * @brief       This function is used to clear the result buffer.
 * @return      none
 */
extern void result_buff_clear(void);
/**
 * @brief     This function performs to calculate cyclic redundancy check code.
 * @param[in] data   - data.
 * @param[in] length - the length of data.
 * @return    crc    - calculate cyclic redundancy
 */
extern unsigned short crc_16(unsigned char *buf, unsigned int len);
/**
 * @brief   This function performs to write result and send command to automatic test tool.
 * @param[in] data      - the data need to be sent.
 * @param[in] length    - the length of data.
 * @return    none
 */
extern int result_buff_write(unsigned char *data, unsigned char length);

#endif

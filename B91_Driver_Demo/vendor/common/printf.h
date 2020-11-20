/********************************************************************************************************
 * @file	printf.h
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
#pragma once
#include "../../drivers/B91/gpio.h"
#include "../../drivers/B91/stimer.h"
#include <stdio.h>
#define DEBUG_MODE	1

#if(DEBUG_MODE==1)

#define  UART_PRINT_DEBUG_ENABLE		0
#define  USB_PRINT_DEBUG_ENABLE		    1

#ifndef   DEBUG_BUS
#define   DEBUG_BUS  	UART_PRINT_DEBUG_ENABLE
#endif
/**
 * @brief      This function serves to printf string.
 * @param[in]  *format  -  format string need to print
 * @param[in]  ...   	-  variable number of data
 * @return     none.
 */
#if (DEBUG_BUS==USB_PRINT_DEBUG_ENABLE)
#define   FIFOTHRESHOLD  	4
#define   BLOCK_MODE   		0
#define   EDPS_DAT       reg_usb_ep8_dat
#define   USBFIFO        reg_usb_ep8_fifo_mode


#elif (DEBUG_BUS==UART_PRINT_DEBUG_ENABLE)

#define  PRINT_BAUD_RATE             		1000000//1M baud rate,should Not bigger than 1Mb/s
#define  DEBUG_INFO_TX_PIN           		GPIO_PA0//uart tx pin
#define  TX_PIN_OUTPUT_REG				    reg_gpio_out(DEBUG_INFO_TX_PIN)
#define	 BIT_INTERVAL	(16*1000*1000/PRINT_BAUD_RATE)

#endif
#endif


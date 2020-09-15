/********************************************************************************************************
 * @file	app_config.h
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
#pragma once

#include "../../drivers.h"
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif
//#define LED1            		GPIO_PD0
//#define LED2            		GPIO_PD1
//#define LED3            		GPIO_PD2
//#define LED4            		GPIO_PB4
//#define LED5            		GPIO_PB5
//#define LED6            		GPIO_PB6

#define TxIO     	GPIO_PD4
#define RxIO     	GPIO_PD5


#define EMI_DEMO	0
#define BQB_DEMO	1
#define TEST_DEMO	BQB_DEMO

typedef enum
{
	UART_NUM0 = UART0,
	UART_NUM1 = UART1,
	UART_NONE,
}uart_num_redef;

#define ADDR_FLASH_SIZE 		 0x24
#define UART_SET_FLASH_ADDR_128K 0x1e080
#define UART_SET_FLASH_ADDR_512K 0x77080
typedef union
{
	unsigned char usr_def;
	struct
	{
		unsigned char uart :5;
		unsigned char cap  :1;
		unsigned char 	   :2;
	};
}usr_def_u;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

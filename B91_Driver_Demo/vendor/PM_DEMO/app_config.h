/********************************************************************************************************
 * @file	app_config.h
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

#include "../../drivers.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define LED1            		GPIO_PB4
#define LED2            		GPIO_PB5
#define LED3            		GPIO_PB6
#define LED4            		GPIO_PB7

#define WAKEUP_PAD				GPIO_PA0
#define CURRENT_TEST	     	1
#define CRC_OK			     	1
#define	MDEC_MATCH_VALUE		0x02

/* IDLE MODE */
#define IDLE_TIMER_WAKEUP				1

/* SUSPEND MODE */
//The A0 version of the suspend execution process is abnormal and the program restarts.
#define SUSPEND_PAD_WAKEUP   			2	//62.1uA
#define SUSPEND_32K_RC_WAKEUP   		3	//63.7uA
#define SUSPEND_32K_XTAL_WAKEUP			4	//62.7uA
#define SUSPEND_MDEC_WAKEUP				5	//65.2uA
#define SUSPEND_COMPARATOR_WAKEUP      	6	//62.3uA
#define SUSPEND_CORE_WAKEUP      		7	//

/* DEEPSLEEP MODE */
#define DEEP_PAD_WAKEUP		 			8	//0.7uA
#define DEEP_32K_RC_WAKEUP      		9	//1.3uA
#define DEEP_32K_XTAL_WAKEUP      		10	//1.7uA
#define DEEP_MDEC_WAKEUP      			11	//1.4uA
#define DEEP_COMPARATOR_WAKEUP      	12	//1.6uA

/* DEEPSLEEP WITH RETENTION MODE */
#define DEEP_RET32K_PAD_WAKEUP     		14	//1.8uA
#define DEEP_RET32K_32K_RC_WAKEUP     	15	//2.4uA
#define DEEP_RET32K_32K_XTAL_WAKEUP     16	//2.8uA
#define DEEP_RET32K_MDEC_WAKEUP      	17	//2.6uA
#define DEEP_RET32K_COMPARATOR_WAKEUP   18	//2.8uA

#define DEEP_RET64K_PAD_WAKEUP     		20	//2.7uA
#define DEEP_RET64K_32K_RC_WAKEUP     	21	//3.2uA
#define DEEP_RET64K_32K_XTAL_WAKEUP     22	//3.7uA
#define DEEP_RET64K_MDEC_WAKEUP      	23	//3.4uA
#define DEEP_RET64K_COMPARATOR_WAKEUP   24	//3.7uA

#define PM_MODE			     			DEEP_PAD_WAKEUP


/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif


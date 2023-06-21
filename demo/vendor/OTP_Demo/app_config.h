/********************************************************************************************************
 * @file    app_config.h
 *
 * @brief   This is the header file for B91m
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#pragma once
#include "driver.h"
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#if(MCU_CORE_B91)
#define LED1            GPIO_PB4
#define LED2            GPIO_PB5
#define LED3            GPIO_PB6
#define LED4            GPIO_PB7
#elif(MCU_CORE_B92)
#define LED3            GPIO_PD0
#define LED4            GPIO_PD1
#define LED1            GPIO_PE6
#define LED2            GPIO_PE7
#elif(MCU_CORE_B95)
#define LED1            GPIO_PD0
#define LED2            GPIO_PD1
#define LED3            GPIO_PD2
#define LED4            GPIO_PD3

#define OTP_TEST_BASE_READ_WRITE        0
#define OTP_TEST_8K_SIZE                1
#define OTP_TEST_AUTO_LOAD              3
#define OTP_TEST_MANUAL_MODE            4
#define OTP_TEST_KEY_LOCK               5
#define OTP_TEST_MARGIN_READ            6
#define OTP_TEST_SHUTDOWN               7
#define OTP_TEST_ROW                    8
#define OTP_TEST_COLUMN                 9

#define OTP_TEST_MODE                   OTP_TEST_MANUAL_MODE

#endif

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

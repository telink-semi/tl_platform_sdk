/********************************************************************************************************
 * @file    common.h
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
#pragma once
#include "auto_test/dut_cmd.h"
#include "auto_test/pc_interface.h"
#include "calibration.h"
#include "printf.h"
#include <string.h>
#include "hal_driver/flash/hal_flash.h"
#include "gpio.h"

/**
    ===============================================================================
                         ##### LED and KEY #####
    ===============================================================================
    The default configuration of LEDs and KEYs match the following hardware revisions:
    B91 C1T213A20_V1_3_20200727
    B92 C1T266A20_V1_3_20220722
    TL721X C1T315A20_V1_0_20231211
    TL321X C1T335A20_V1.0_20240422
*/
#if defined(MCU_CORE_B91)
#define LED1                    GPIO_PB4
#define LED2                    GPIO_PB5
#define LED3                    GPIO_PB6
#define LED4                    GPIO_PB7
/*
 * Button matrix table:
 *          KEY3    KEY4
 *  KEY1    SW2     SW3
 *  KEY2    SW4     SW5
 */
#define KEY1                    GPIO_PC2
#define KEY2                    GPIO_PC0
#define KEY3                    GPIO_PC3
#define KEY4                    GPIO_PC1
#elif defined(MCU_CORE_B92)
#define LED3                    GPIO_PD0
#define LED4                    GPIO_PD1
#define LED1                    GPIO_PE6
#define LED2                    GPIO_PE7
/*
 * Button matrix table:
 *          KEY3    KEY4
 *  KEY1    SW2     SW3
 *  KEY2    SW4     SW5
 */
#define KEY1                    GPIO_PD2
#define KEY2                    GPIO_PD7
#define KEY3                    GPIO_PD6
#define KEY4                    GPIO_PF6
#elif defined(MCU_CORE_B931)
#define LED1                    GPIO_PD1
#define LED2                    GPIO_PD3
#define LED3                    GPIO_PD4
#define LED4                    GPIO_PD5
#define LED5                    GPIO_PD0
#define LED6                    GPIO_PD2
#define KEY1                    GPIO_PA1
#define KEY2                    GPIO_PA2
#define KEY3                    GPIO_PA3
#elif defined(MCU_CORE_TL721X)
#define LED1                    GPIO_PC3
#define LED2                    GPIO_PC2
#define LED3                    GPIO_PC1
#define LED4                    GPIO_PC0
#define KEY1                    GPIO_PD4
#define KEY2                    GPIO_PD6
#define KEY3                    GPIO_PD5
#define KEY4                    GPIO_PD7
#elif defined(MCU_CORE_TL321X)
#define LED1                    GPIO_PD0
#define LED2                    GPIO_PD1
#define LED3                    GPIO_PD2
#define LED4                    GPIO_PD3
#define KEY1                    GPIO_PD4
#define KEY2                    GPIO_PD5
#define KEY3                    GPIO_PD6
#define KEY4                    GPIO_PD7
#elif defined(MCU_CORE_W92)
#define LED1                    GPIO_PD0
#define LED2                    GPIO_PD1
#define LED3                    GPIO_PD2
#define LED4                    GPIO_PD3
#define KEY1                    GPIO_PD4
#define KEY2                    GPIO_PD5
#define KEY3                    GPIO_PD6
#define KEY4                    GPIO_PD7
#else
#define LED1                    GPIO_PD1
#define LED2                    GPIO_PD3
#define LED3                    GPIO_PD4
#define LED4                    GPIO_PD5
#define LED5                    GPIO_PD0
#define LED6                    GPIO_PD2

#define KEY1                    GPIO_PA3
#define KEY2                    GPIO_PE3
#define KEY3                    GPIO_PA0
#define KEY4                    GPIO_PF0
#endif
/**
    ===============================================================================
                         ##### platform init and clock init #####
    ===============================================================================
    flash_protect_en assignment description, the default is 1, use the following rules:
    1. By default, the application needs to enable write protection in all cases, this parameter is reserved for some internal special test cases;
    2. Some demos have the operation of writing flash, remember to remove the write protection before erasing, and add the write protection after erasing;
    3. There are some demos that do not need to add write protection, such as dut-related, internal testing;

    @note if flash protection fails, LED1 lights up long, and keeps while.
    ===============================================================================
*/
#if defined(MCU_CORE_B91)
void platform_init(power_mode_e power_mode, vbat_type_e vbat_v, cap_typedef_e cap,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(LDO_1P4_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      CCLK_24M_HCLK_24M_PCLK_24M
#endif
#elif defined(MCU_CORE_B92)
void platform_init(power_mode_e power_mode, vbat_type_e vbat_v, gpio_voltage_e gpio_v, cap_typedef_e cap,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(DCDC_1P4_DCDC_2P0, VBAT_MAX_VALUE_GREATER_THAN_3V6, GPIO_VOLTAGE_3V3, INTERNAL_CAP_XTAL24M,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      CCLK_24M_HCLK_24M_PCLK_24M
#endif
#elif defined(MCU_CORE_TL751X)
void platform_init(vbat_type_e vbat_v,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(VBAT_MAX_VALUE_GREATER_THAN_3V6,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      CCLK_96M_HCLK_96M_PCLK_24M_MSPI_48M
#endif
#elif defined(MCU_CORE_TL721X)
void platform_init(power_mode_e power_mode, vbat_type_e vbat_v, cap_typedef_e cap,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(LDO_0P94_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      PLL_240M_CCLK_120M_HCLK_60M_PCLK_60M_MSPI_48M
#endif
#elif defined(MCU_CORE_TL321X)
void platform_init(power_mode_e power_mode, vbat_type_e vbat_v, cap_typedef_e cap,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(LDO_1P25_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      PLL_192M_CCLK_96M_HCLK_48M_PCLK_24M_MSPI_48M
#endif
#elif defined(MCU_CORE_W92)
void platform_init(vbat_type_e vbat_v,unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(VBAT_MAX_VALUE_GREATER_THAN_3V6,1)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      CCLK_96M_HCLK_96M_PCLK_24M_MSPI_48M
#endif
#else
void platform_init(unsigned char flash_protect_en);
#ifndef PLATFORM_INIT
#define PLATFORM_INIT   platform_init(0)
#endif
#ifndef CLOCK_INIT
#define CLOCK_INIT      
#endif
#endif



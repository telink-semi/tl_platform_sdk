/********************************************************************************************************
 * @file    hal_gpio.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/drv_gpio.h"
/**********************************************************************************************************************
 *                                           GPIO   setting                                                            *
 *********************************************************************************************************************/
#define GPIO_PORT_ALL 0x03

#define INPUT_MODE  0x00U
#define OUTPUT_MODE 0x01U
#define FUNC_0  0
#define FUNC_1  1
#define FUNC_2  2
#define FUNC_3  3
#define FUNC_4  4
#define FUNC_5  5
#define FUNC_6  6
#define FUNC_7  7
#define FUNC_8  8
#define FUNC_9  9
#define FUNC_10 10
#define FUNC_11 11
#define FUNC_12 12
#define FUNC_13 13
#define FUNC_14 14
#define FUNC_15 15

#define INTR_DISABLE  0x00000000U
#define INTR_ENABLE   0x00000001U

#define INTR_RISEDGE   0x00000000U
#define INTR_FALLEDGE  0x00000001U

#define INTR_DEBOUNCE_DISABLE 0x00000001U
#define INTR_DEBOUNCE_ENABLE  0x00000000U

#define DRIVE_STRENGTH_2MA  0x00000020U /*!< 2mA */
#define DRIVE_STRENGTH_4MA  0x00000021U /*!< 4mA */
#define DRIVE_STRENGTH_8MA  0x00000022U /*!< 8mA */
#define DRIVE_STRENGTH_12MA 0x00000023U /*!< 12mA */

#define PULL_UP   0x00000028U
#define PULL_DOWN 0x00000024U
#define NO_PULL   0x00000020U
/************************************************************PA*******************************************************/
#ifndef PA0_FUNC
#define PA0_FUNC FUNC_0
#endif
#ifndef PA1_FUNC
#define PA1_FUNC FUNC_0
#endif
#ifndef PA2_FUNC
#define PA2_FUNC FUNC_0
#endif
#ifndef PA3_FUNC
#define PA3_FUNC FUNC_0
#endif
#ifndef PA4_FUNC
#define PA4_FUNC FUNC_0
#endif
#ifndef PA5_FUNC
#define PA5_FUNC FUNC_0
#endif
#ifndef PA6_FUNC
#define PA6_FUNC FUNC_0
#endif
#ifndef PA7_FUNC
#define PA7_FUNC FUNC_0
#endif
#ifndef PA8_FUNC
#define PA8_FUNC FUNC_0
#endif
#ifndef PA9_FUNC
#define PA9_FUNC FUNC_0
#endif
#ifndef PA10_FUNC  //sws
#define PA10_FUNC FUNC_0
#endif
#ifndef PA11_FUNC
#define PA11_FUNC FUNC_0
#endif
#ifndef PA12_FUNC
#define PA12_FUNC FUNC_0
#endif
#ifndef PA13_FUNC
#define PA13_FUNC FUNC_0
#endif
#ifndef PA14_FUNC
#define PA14_FUNC FUNC_0
#endif
#ifndef PA15_FUNC
#define PA15_FUNC FUNC_0
#endif
#ifndef PA16_FUNC
#define PA16_FUNC FUNC_0
#endif
#ifndef PA17_FUNC
#define PA17_FUNC FUNC_0
#endif
#ifndef PA18_FUNC
#define PA18_FUNC FUNC_0
#endif
#ifndef PA19_FUNC
#define PA19_FUNC FUNC_0
#endif
#ifndef PA20_FUNC
#define PA20_FUNC FUNC_0
#endif
#ifndef PA21_FUNC
#define PA21_FUNC FUNC_0
#endif
#ifndef PA22_FUNC
#define PA22_FUNC FUNC_0
#endif
#ifndef PA23_FUNC
#define PA23_FUNC FUNC_0
#endif
#ifndef PA24_FUNC
#define PA24_FUNC FUNC_0
#endif
#ifndef PA25_FUNC
#define PA25_FUNC FUNC_0
#endif
#ifndef PA26_FUNC
#define PA26_FUNC FUNC_0
#endif
#ifndef PA27_FUNC
#define PA27_FUNC FUNC_0
#endif
#ifndef PA28_FUNC
#define PA28_FUNC FUNC_0
#endif
#ifndef PA29_FUNC
#define PA29_FUNC FUNC_0
#endif
#ifndef PA30_FUNC
#define PA30_FUNC FUNC_0
#endif
#ifndef PA31_FUNC
#define PA31_FUNC FUNC_0
#endif
#ifndef PA0_DDR
#define PA0_DDR  (OUTPUT_MODE << 0)
#endif
#ifndef PA1_DDR
#define PA1_DDR  (OUTPUT_MODE << 1)
#endif
#ifndef PA2_DDR
#define PA2_DDR  (OUTPUT_MODE << 2)
#endif
#ifndef PA3_DDR
#define PA3_DDR  (OUTPUT_MODE << 3)
#endif
#ifndef PA4_DDR
#define PA4_DDR  (OUTPUT_MODE << 4)
#endif
#ifndef PA5_DDR
#define PA5_DDR  (OUTPUT_MODE << 5)
#endif
#ifndef PA6_DDR
#define PA6_DDR  (OUTPUT_MODE << 6)
#endif
#ifndef PA7_DDR
#define PA7_DDR  (OUTPUT_MODE << 7)
#endif
#ifndef PA8_DDR
#define PA8_DDR  (OUTPUT_MODE << 8)
#endif
#ifndef PA9_DDR
#define PA9_DDR  (OUTPUT_MODE << 9)
#endif
#ifndef PA10_DDR  //sws
#define PA10_DDR (INPUT_MODE << 10)
#endif
#ifndef PA11_DDR
#define PA11_DDR (OUTPUT_MODE << 11)
#endif
#ifndef PA12_DDR
#define PA12_DDR (OUTPUT_MODE << 12)
#endif
#ifndef PA13_DDR
#define PA13_DDR (OUTPUT_MODE << 13)
#endif
#ifndef PA14_DDR
#define PA14_DDR (OUTPUT_MODE << 14)
#endif
#ifndef PA15_DDR
#define PA15_DDR (OUTPUT_MODE << 15)
#endif
#ifndef PA16_DDR
#define PA16_DDR (OUTPUT_MODE << 16)
#endif
#ifndef PA17_DDR
#define PA17_DDR (OUTPUT_MODE << 17)
#endif
#ifndef PA18_DDR
#define PA18_DDR (OUTPUT_MODE << 18)
#endif
#ifndef PA19_DDR
#define PA19_DDR (OUTPUT_MODE << 19)
#endif
#ifndef PA20_DDR
#define PA20_DDR (OUTPUT_MODE << 20)
#endif
#ifndef PA21_DDR
#define PA21_DDR (OUTPUT_MODE << 21)
#endif
#ifndef PA22_DDR
#define PA22_DDR (OUTPUT_MODE << 22)
#endif
#ifndef PA23_DDR
#define PA23_DDR (OUTPUT_MODE << 23)
#endif
#ifndef PA24_DDR
#define PA24_DDR (OUTPUT_MODE << 24)
#endif
#ifndef PA25_DDR
#define PA25_DDR (OUTPUT_MODE << 25)
#endif
#ifndef PA26_DDR
#define PA26_DDR (OUTPUT_MODE << 26)
#endif
#ifndef PA27_DDR
#define PA27_DDR (OUTPUT_MODE << 27)
#endif
#ifndef PA28_DDR
#define PA28_DDR (OUTPUT_MODE << 28)
#endif
#ifndef PA29_DDR
#define PA29_DDR (OUTPUT_MODE << 29)
#endif
#ifndef PA30_DDR
#define PA30_DDR (OUTPUT_MODE << 30)
#endif
#ifndef PA31_DDR
#define PA31_DDR (OUTPUT_MODE << 31)
#endif
#ifndef PA0_DATA_STRENGTH
#define PA0_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA1_DATA_STRENGTH
#define PA1_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA2_DATA_STRENGTH
#define PA2_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA3_DATA_STRENGTH
#define PA3_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA4_DATA_STRENGTH
#define PA4_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA5_DATA_STRENGTH
#define PA5_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA6_DATA_STRENGTH
#define PA6_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA7_DATA_STRENGTH
#define PA7_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA8_DATA_STRENGTH
#define PA8_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA9_DATA_STRENGTH
#define PA9_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA10_DATA_STRENGTH  //sws
#define PA10_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA11_DATA_STRENGTH
#define PA11_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA12_DATA_STRENGTH
#define PA12_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA13_DATA_STRENGTH
#define PA13_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA14_DATA_STRENGTH
#define PA14_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA15_DATA_STRENGTH
#define PA15_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA16_DATA_STRENGTH
#define PA16_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA17_DATA_STRENGTH
#define PA17_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA18_DATA_STRENGTH
#define PA18_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA19_DATA_STRENGTH
#define PA19_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA20_DATA_STRENGTH
#define PA20_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA21_DATA_STRENGTH
#define PA21_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA22_DATA_STRENGTH
#define PA22_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA23_DATA_STRENGTH
#define PA23_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA24_DATA_STRENGTH
#define PA24_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA25_DATA_STRENGTH
#define PA25_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA26_DATA_STRENGTH
#define PA26_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA27_DATA_STRENGTH
#define PA27_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA28_DATA_STRENGTH
#define PA28_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA29_DATA_STRENGTH
#define PA29_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA30_DATA_STRENGTH
#define PA30_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA31_DATA_STRENGTH
#define PA31_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PA0_DATA_OUT
    #define PA0_DATA_OUT 0
#endif
#ifndef PA1_DATA_OUT
    #define PA1_DATA_OUT 0
#endif
#ifndef PA2_DATA_OUT
    #define PA2_DATA_OUT 0
#endif
#ifndef PA3_DATA_OUT
    #define PA3_DATA_OUT 0
#endif
#ifndef PA4_DATA_OUT
    #define PA4_DATA_OUT 0
#endif
#ifndef PA5_DATA_OUT
    #define PA5_DATA_OUT 0
#endif
#ifndef PA6_DATA_OUT
    #define PA6_DATA_OUT 0
#endif
#ifndef PA7_DATA_OUT
    #define PA7_DATA_OUT 0
#endif
#ifndef PA8_DATA_OUT
    #define PA8_DATA_OUT 0
#endif
#ifndef PA9_DATA_OUT
    #define PA9_DATA_OUT 0
#endif
#ifndef PA10_DATA_OUT  //sws
    #define PA10_DATA_OUT 0
#endif
#ifndef PA11_DATA_OUT
    #define PA11_DATA_OUT 0
#endif
#ifndef PA12_DATA_OUT
    #define PA12_DATA_OUT 0
#endif
#ifndef PA13_DATA_OUT
    #define PA13_DATA_OUT 0
#endif
#ifndef PA14_DATA_OUT
    #define PA14_DATA_OUT 0
#endif
#ifndef PA15_DATA_OUT
    #define PA15_DATA_OUT 0
#endif
#ifndef PA16_DATA_OUT
    #define PA16_DATA_OUT 0
#endif
#ifndef PA17_DATA_OUT
    #define PA17_DATA_OUT 0
#endif
#ifndef PA18_DATA_OUT
    #define PA18_DATA_OUT 0
#endif
#ifndef PA19_DATA_OUT
    #define PA19_DATA_OUT 0
#endif
#ifndef PA20_DATA_OUT
    #define PA20_DATA_OUT 0
#endif
#ifndef PA21_DATA_OUT
    #define PA21_DATA_OUT 0
#endif
#ifndef PA22_DATA_OUT
    #define PA22_DATA_OUT 0
#endif
#ifndef PA23_DATA_OUT
    #define PA23_DATA_OUT 0
#endif
#ifndef PA24_DATA_OUT
    #define PA24_DATA_OUT 0
#endif
#ifndef PA25_DATA_OUT
    #define PA25_DATA_OUT 0
#endif
#ifndef PA26_DATA_OUT
    #define PA26_DATA_OUT 0
#endif
#ifndef PA27_DATA_OUT
    #define PA27_DATA_OUT 0
#endif
#ifndef PA28_DATA_OUT
    #define PA28_DATA_OUT 0
#endif
#ifndef PA29_DATA_OUT
    #define PA29_DATA_OUT 0
#endif
#ifndef PA30_DATA_OUT
    #define PA30_DATA_OUT 0
#endif
#ifndef PA31_DATA_OUT
    #define PA31_DATA_OUT 0
#endif
#ifndef PA0_PULL
#define PA0_PULL  PULL_UP
#endif
#ifndef PA1_PULL
#define PA1_PULL  PULL_UP
#endif
#ifndef PA2_PULL
#define PA2_PULL  PULL_UP
#endif
#ifndef PA3_PULL
#define PA3_PULL  PULL_UP
#endif
#ifndef PA4_PULL
#define PA4_PULL  PULL_UP
#endif
#ifndef PA5_PULL
#define PA5_PULL  PULL_UP
#endif
#ifndef PA6_PULL
#define PA6_PULL  PULL_UP
#endif
#ifndef PA7_PULL
#define PA7_PULL  PULL_UP
#endif
#ifndef PA8_PULL
#define PA8_PULL  PULL_UP
#endif
#ifndef PA9_PULL
#define PA9_PULL  PULL_DOWN
#endif
#ifndef PA10_PULL  //sws
#define PA10_PULL PULL_UP
#endif
#ifndef PA11_PULL
#define PA11_PULL PULL_UP
#endif
#ifndef PA12_PULL
#define PA12_PULL PULL_UP
#endif
#ifndef PA13_PULL
#define PA13_PULL PULL_UP
#endif
#ifndef PA14_PULL
#define PA14_PULL PULL_UP
#endif
#ifndef PA15_PULL
#define PA15_PULL PULL_UP
#endif
#ifndef PA16_PULL
#define PA16_PULL PULL_UP
#endif
#ifndef PA17_PULL
#define PA17_PULL PULL_UP
#endif
#ifndef PA18_PULL
#define PA18_PULL PULL_UP
#endif
#ifndef PA19_PULL
#define PA19_PULL PULL_UP
#endif
#ifndef PA20_PULL
#define PA20_PULL PULL_UP
#endif
#ifndef PA21_PULL
#define PA21_PULL PULL_UP
#endif
#ifndef PA22_PULL
#define PA22_PULL PULL_UP
#endif
#ifndef PA23_PULL
#define PA23_PULL PULL_UP
#endif
#ifndef PA24_PULL
#define PA24_PULL PULL_UP
#endif
#ifndef PA25_PULL
#define PA25_PULL PULL_UP
#endif
#ifndef PA26_PULL
#define PA26_PULL PULL_UP
#endif
#ifndef PA27_PULL
#define PA27_PULL PULL_UP
#endif
#ifndef PA28_PULL
#define PA28_PULL PULL_UP
#endif
#ifndef PA29_PULL
#define PA29_PULL PULL_UP
#endif
#ifndef PA30_PULL
#define PA30_PULL PULL_UP
#endif
#ifndef PA31_PULL
#define PA31_PULL PULL_UP
#endif

/************************************************************PB*******************************************************/
#ifndef PB0_DDR
#define PB0_DDR  (OUTPUT_MODE << 0)
#endif
#ifndef PB1_DDR
#define PB1_DDR  (OUTPUT_MODE << 1)
#endif
#ifndef PB2_DDR
#define PB2_DDR  (OUTPUT_MODE << 2)
#endif
#ifndef PB3_DDR
#define PB3_DDR  (OUTPUT_MODE << 3)
#endif
#ifndef PB4_DDR
#define PB4_DDR  (OUTPUT_MODE << 4)
#endif
#ifndef PB5_DDR
#define PB5_DDR  (OUTPUT_MODE << 5)
#endif
#ifndef PB6_DDR
#define PB6_DDR  (OUTPUT_MODE << 6)
#endif
#ifndef PB7_DDR
#define PB7_DDR  (OUTPUT_MODE << 7)
#endif
#ifndef PB8_DDR
#define PB8_DDR  (OUTPUT_MODE << 8)
#endif
#ifndef PB9_DDR
#define PB9_DDR  (OUTPUT_MODE << 9)
#endif
#ifndef PB10_DDR
#define PB10_DDR (OUTPUT_MODE << 10)
#endif
#ifndef PB11_DDR
#define PB11_DDR (OUTPUT_MODE << 11)
#endif
#ifndef PB12_DDR
#define PB12_DDR (OUTPUT_MODE << 12)
#endif
#ifndef PB13_DDR
#define PB13_DDR (OUTPUT_MODE << 13)
#endif
#ifndef PB0_DATA_OUT
#define PB0_DATA_OUT 1
#endif
#ifndef PB1_DATA_OUT
#define PB1_DATA_OUT 1
#endif
#ifndef PB2_DATA_OUT
    #define PB2_DATA_OUT 1
#endif
#ifndef PB3_DATA_OUT
    #define PB3_DATA_OUT 1
#endif
#ifndef PB4_DATA_OUT
    #define PB4_DATA_OUT 0
#endif
#ifndef PB5_DATA_OUT
    #define PB5_DATA_OUT 0
#endif
#ifndef PB6_DATA_OUT
    #define PB6_DATA_OUT 0
#endif
#ifndef PB7_DATA_OUT
    #define PB7_DATA_OUT 0
#endif
#ifndef PB8_DATA_OUT
    #define PB8_DATA_OUT 0
#endif
#ifndef PB9_DATA_OUT
    #define PB9_DATA_OUT 0
#endif
#ifndef PB10_DATA_OUT
    #define PB10_DATA_OUT 1
#endif
#ifndef PB11_DATA_OUT
    #define PB11_DATA_OUT 0
#endif
#ifndef PB12_DATA_OUT
    #define PB12_DATA_OUT 0
#endif
#ifndef PB13_DATA_OUT
    #define PB13_DATA_OUT 0
#endif
#ifndef PB0_FUNC
#define PB0_FUNC FUNC_0
#endif
#ifndef PB1_FUNC
#define PB1_FUNC FUNC_0
#endif
#ifndef PB2_FUNC
#define PB2_FUNC FUNC_0
#endif
#ifndef PB3_FUNC
#define PB3_FUNC FUNC_0
#endif
#ifndef PB4_FUNC
#define PB4_FUNC FUNC_0
#endif
#ifndef PB5_FUNC
#define PB5_FUNC FUNC_0
#endif
#ifndef PB6_FUNC
#define PB6_FUNC FUNC_1
#endif
#ifndef PB7_FUNC
#define PB7_FUNC FUNC_1
#endif
#ifndef PB8_FUNC
#define PB8_FUNC FUNC_1
#endif
#ifndef PB9_FUNC
#define PB9_FUNC FUNC_1
#endif
#ifndef PB10_FUNC
#define PB10_FUNC FUNC_0
#endif
#ifndef PB11_FUNC
#define PB11_FUNC FUNC_0
#endif
#ifndef PB12_FUNC
#define PB12_FUNC FUNC_0
#endif
#ifndef PB13_FUNC
#define PB13_FUNC FUNC_0
#endif
#ifndef PB_SWIRE_FUNC
#define PB_SWIRE_FUNC FUNC_0
#endif
#ifndef PB0_DATA_STRENGTH
#define PB0_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB1_DATA_STRENGTH
#define PB1_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB2_DATA_STRENGTH
#define PB2_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB3_DATA_STRENGTH
#define PB3_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB4_DATA_STRENGTH
#define PB4_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB5_DATA_STRENGTH
#define PB5_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB6_DATA_STRENGTH
#define PB6_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB7_DATA_STRENGTH
#define PB7_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB8_DATA_STRENGTH
#define PB8_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB9_DATA_STRENGTH
#define PB9_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB10_DATA_STRENGTH
#define PB10_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB11_DATA_STRENGTH
#define PB11_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB12_DATA_STRENGTH
#define PB12_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB13_DATA_STRENGTH
#define PB13_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PB0_PULL
#define PB0_PULL  PULL_UP
#endif
#ifndef PB1_PULL
#define PB1_PULL  PULL_UP
#endif
#ifndef PB2_PULL
#define PB2_PULL  PULL_UP
#endif
#ifndef PB3_PULL
#define PB3_PULL  PULL_UP
#endif
#ifndef PB4_PULL
#define PB4_PULL  PULL_UP
#endif
#ifndef PB5_PULL
#define PB5_PULL  PULL_UP
#endif
#ifndef PB6_PULL
#define PB6_PULL  PULL_UP
#endif
#ifndef PB7_PULL
#define PB7_PULL  PULL_UP
#endif
#ifndef PB8_PULL
#define PB8_PULL  PULL_UP
#endif
#ifndef PB9_PULL
#define PB9_PULL  PULL_UP
#endif
#ifndef PB10_PULL
#define PB10_PULL PULL_UP
#endif
#ifndef PB11_PULL
#define PB11_PULL PULL_UP
#endif
#ifndef PB12_PULL
#define PB12_PULL PULL_UP
#endif
#ifndef PB13_PULL
#define PB13_PULL PULL_UP
#endif

/************************************************************PC*******************************************************/
#ifndef PC0_DDR //flash0_clk
#define PC0_DDR (INPUT_MODE << 14)
#endif
#ifndef PC2_DDR //flash0_csn
#define PC2_DDR (INPUT_MODE << 16)
#endif
#ifndef PC4_DDR //flash0_io0
#define PC4_DDR (INPUT_MODE << 18)
#endif
#ifndef PC5_DDR //flash0_io1
#define PC5_DDR (INPUT_MODE << 19)
#endif
#ifndef PC6_DDR //flash0_io2
#define PC6_DDR (INPUT_MODE << 20)
#endif
#ifndef PC7_DDR //flash0_io3
#define PC7_DDR (OUTPUT_MODE << 21)
#endif
#ifndef PC8_DDR
#define PC8_DDR (OUTPUT_MODE << 22)
#endif
#ifndef PC9_DDR
#define PC9_DDR (OUTPUT_MODE << 23)
#endif
#ifndef PC0_DATA_OUT //flash0_clk
#define PC0_DATA_OUT 0
#endif
#ifndef PC2_DATA_OUT //flash0_csn
#define PC2_DATA_OUT 0
#endif
#ifndef PC4_DATA_OUT //flash0_io0
#define PC4_DATA_OUT 0
#endif
#ifndef PC5_DATA_OUT //flash0_io1
#define PC5_DATA_OUT 0
#endif
#ifndef PC6_DATA_OUT //flash0_io2
#define PC6_DATA_OUT 0
#endif
#ifndef PC7_DATA_OUT //flash0_io3
#define PC7_DATA_OUT 0
#endif
#ifndef PC8_DATA_OUT
#define PC8_DATA_OUT 0
#endif
#ifndef PC9_DATA_OUT
#define PC9_DATA_OUT 0
#endif
#ifndef PC0_FUNC //flash0_clk
#define PC0_FUNC FUNC_0
#endif
#ifndef PC2_FUNC //flash0_csn
#define PC2_FUNC FUNC_0
#endif

#ifndef PC4_FUNC //flash0_io0
#define PC4_FUNC FUNC_0
#endif
#ifndef PC5_FUNC //flash0_io1
#define PC5_FUNC FUNC_0
#endif
#ifndef PC6_FUNC //flash0_io2
#define PC6_FUNC FUNC_0
#endif
#ifndef PC7_FUNC //flash0_io3
#define PC7_FUNC FUNC_0
#endif
#ifndef PC8_FUNC
#define PC8_FUNC FUNC_0
#endif
#ifndef PC9_FUNC
#define PC9_FUNC FUNC_0
#endif
#ifndef PC0_DATA_STRENGTH //flash0_clk
#define PC0_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC2_DATA_STRENGTH //flash0_csn
#define PC2_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC4_DATA_STRENGTH //flash0_io0
#define PC4_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC5_DATA_STRENGTH //flash0_io1
#define PC5_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC6_DATA_STRENGTH //flash0_io2
#define PC6_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC7_DATA_STRENGTH  //flash0_io3
#define PC7_DATA_STRENGTH DRIVE_STRENGTH_8MA
#endif
#ifndef PC8_DATA_STRENGTH
#define PC8_DATA_STRENGTH DRIVE_STRENGTH_12MA
#endif
#ifndef PC9_DATA_STRENGTH
#define PC9_DATA_STRENGTH DRIVE_STRENGTH_12MA
#endif
#ifndef PC0_PULL //flash0_clk
#define PC0_PULL  PULL_DOWN
#endif
#ifndef PC2_PULL //flash0_csn
#define PC2_PULL  PULL_UP
#endif
#ifndef PC4_PULL //flash0_io0
#define PC4_PULL  PULL_UP
#endif
#ifndef PC5_PULL //flash0_io1
#define PC5_PULL  PULL_UP
#endif
#ifndef PC6_PULL //flash0_io2
#define PC6_PULL  PULL_UP
#endif
#ifndef PC7_PULL //flash0_io3
#define PC7_PULL  PULL_UP
#endif
#ifndef PC8_PULL
#define PC8_PULL  PULL_UP
#endif
#ifndef PC9_PULL
#define PC9_PULL  NO_PULL
#endif


typedef enum {
    GPIO_ALL = GPIO_PORT_ALL << 8,
    GPIO_ACTIVE = 1 << 7,
    GPIO_PA0 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 0,
    GPIO_PA1 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 1,
    GPIO_PA2 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 2,
    GPIO_PA3 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 3,
    GPIO_PA4 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 4,
    GPIO_PA5 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 5,
    GPIO_PA6 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 6,
    GPIO_PA7 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 7,
    GPIO_PA8 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 8,
    GPIO_PA9 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 9,
    GPIO_PA10 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 10,
    GPIO_SWS  = GPIO_PA10,
    GPIO_PA11 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 11,
    GPIO_PA12 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 12,
    GPIO_PA13 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 13,
    GPIO_PA14 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 14,
    GPIO_PA15 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 15,
    GPIO_PA16 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 16,
    GPIO_PA17 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 17,
    GPIO_PA18 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 18,
    GPIO_PA19 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 19,
    GPIO_PA20 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 20,
    GPIO_PA21 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 21,
    GPIO_PA22 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 22,
    GPIO_PA23 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 23,
    GPIO_PA24 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 24,
    GPIO_PA25 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 25,
    GPIO_PA26 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 26,
    GPIO_PA27 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 27,
    GPIO_PA28 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 28,
    GPIO_PA29 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 29,
    GPIO_PA30 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 30,
    GPIO_PA31 = (GPIO_PORT_A << 8) + GPIO_ACTIVE + 31,
    GPIO_PB0 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 0,
    GPIO_PB1 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 1,
    GPIO_PB2 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 2,
    GPIO_PB3 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 3,
    GPIO_PB4 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 4,
    GPIO_PB5 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 5,
    GPIO_PB6 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 6,
    GPIO_PB7 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 7,
    GPIO_PB8 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 8,
    GPIO_PB9 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 9,
    GPIO_PB10 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 10,
    GPIO_PB11 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 11,
    GPIO_PB12 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 12,
    GPIO_PB13 = (GPIO_PORT_B << 8) + GPIO_ACTIVE + 13,
    GPIO_PC0 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 0,
    GPIO_PC2 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 2,
    GPIO_PC4 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 4,
    GPIO_PC5 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 5,
    GPIO_PC6 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 6,
    GPIO_PC7 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 7,
    GPIO_PC8 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 8,
    GPIO_PC9 = (GPIO_PORT_C << 8) + GPIO_ACTIVE + 9,
    GPIO_FUN_MAX,
} gpio_pin_e;


/**
 *  @brief  Define driving strength types
 */
typedef enum
{
    DRV_STRENGTH_2MA  = GPIO_ELECTRIC_2MA,
    DRV_STRENGTH_4MA  = GPIO_ELECTRIC_4MA,
    DRV_STRENGTH_8MA  = GPIO_ELECTRIC_8MA,
    DRV_STRENGTH_12MA = GPIO_ELECTRIC_12MA,
} gpio_drv_strength_e;


/**
 *  @brief  Define pull up or down types
 */
typedef enum
{
    GPIO_PIN_NO_PULL    = GPIO_NOPULL,
    GPIO_PIN_PULLDOWN   = GPIO_PULLDOWN,
    GPIO_PIN_PULLUP     = GPIO_PULLUP,
} gpio_pull_type_e;

/**
 * @brief       This function is used to enable the GPIO pin of mspi.
 * @param[in]   none.
 * @return      none.
 * @note        This interface is for internal use only.
 */
static _always_inline void gpio_set_mspi_pin_ie_en(void)
{
    SET_BIT(CPR->PC_IE_CFG, 0xf5);  /* PB_0/2/4/5/6/7 */
}

/**
 * @brief       This function is used to disable the GPIO pin of mspi.
 * @param[in]   none.
 * @return      none.
 * @note        This interface is for internal use only.
 */
static _always_inline void gpio_set_mspi_pin_ie_dis(void)
{
    CLEAR_BIT(CPR->PC_IE_CFG, 0xf5);
}

static _always_inline unsigned int gpio_get_pa_irq_status(void)
{
    return READ_REG(CPR->PA_WKUP_IRQ);
}

static _always_inline unsigned int gpio_get_pb_irq_status(void)
{
    return READ_REG(PMU->PB_WKUP_IRQ);
}

/**
 * @brief      This function enable the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function.
 * @return     none.
 */
extern void gpio_input_en(gpio_pin_e pin);

/**
 * @brief      This function enable the output function of a pin.
 * @param[in]  pin - the pin needs to set the output function.
 * @return     none.
 */
extern void gpio_output_en(gpio_pin_e pin);

/**
 * @brief      This function set the pin's output high level.
 * @param[in]  pin - the pin needs to set its output level.
 * @return     none.
 */
extern void gpio_set_high_level(gpio_pin_e pin);

/**
 * @brief      This function set the pin's output low level.
 * @param[in]  pin - the pin needs to set its output level.
 * @return     none.
 */
extern void gpio_set_low_level(gpio_pin_e pin);

/**
 * @brief     This function set a pin's IRQ , here you can choose from 8 interrupts for flexible configuration, each interrupt is independent.
 * @param[in] pin           - the pin needs to enable its IRQ.
 * @param[in] trigger_type  - gpio interrupt type.
 * @return    none.
 */
extern void gpio_set_irq(gpio_pin_e pin, gpio_int_type_t trigger_type);

/**
 * @brief     This function set a pin's pull-up/down resistor.
 * @param[in] pin - the pin needs to set its pull-up/down resistor.
 * @param[in] up_down_res - the type of the pull-up/down resistor.
 * @return    none.
 */
extern void gpio_set_up_down_res(gpio_pin_e pin, gpio_pull_type_e up_down_res);

/**
 * @brief      This function servers to enable gpio function.
 * @param[in]  pin - the selected pin.
 * @return     none.
 */
extern void gpio_function_en(gpio_pin_e pin);

/**
 * @brief      This function servers to disable gpio function.
 * @param[in]  pin - the selected pin.
 * @return     none.
 */
extern void gpio_function_dis(gpio_pin_e pin);

/**
 * @brief     This function read the pin's input level.
 * @param[in] pin - the pin needs to read its input level.
 * @return    1: the pin's input level is high.
 *            0: the pin's input level is low.
 */
extern uint32_t gpio_get_level(gpio_pin_e pin);

/**
 * @brief      This function serves to clr gpio irq status.
 * @param[in]  pin  - the irq need to clear.
 * @return     none.
 */
extern void gpio_clr_irq_status(gpio_pin_e pin);

/**
  * @brief  GPIO interrupt read
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B
  * @retval None
  */
extern uint32_t gpio_get_irq_status(gpio_pin_e pin);

/**
  * @brief  GPIO group interrupt read
  * @param  gpio_port specifies the port to be written. can be GPIO_PORT_A,GPIO_PORT_B
  * @retval None
  */
extern uint32_t gpio_get_group_irq_status(uint16_t gpio_port);

/**
 * @brief      This function set the pin's driving strength.
 * @param[in]  pin - the pin needs to set the driving strength
 * @param[in]  strength - the level of driving strength
 * @return     none
 */
extern void gpio_set_data_strength(gpio_pin_e pin, gpio_drv_strength_e strength);

/**
 * @brief      This function serves to enable gpio irq function.
 * @return     none.
 */
extern void gpio_irq_en(void);

/**
 * @brief      This function serves to disable gpio irq function.
 * @return     none.
 */
extern void gpio_irq_dis(void);

/**
 * @brief      This function serves to set the gpio-mux function.
 * @param[in]  pin      - the pin needs to set.
 * @param[in]  function - the function need to set.
 * @return     none.
 */
extern void gpio_set_mux_function(gpio_pin_e pin, uint32_t function);

/**
 * @brief     This function set the pin's output level.
 * @param[in] pin - the pin needs to set its output level
 * @param[in] value - value of the output level(1: high 0: low)
 * @return    none
 */
extern void gpio_set_level(gpio_pin_e pin, unsigned char value);

/**
 * @brief  gpio toggle in output mode.
 * @param[in]  pin - the pin needs to set the output function.
 * @retval none.
 */
extern void gpio_toggle(gpio_pin_e pin);

/**
 * @brief      This function disable the output function of a pin.
 * @param[in]  pin - the pin needs to set the output function.
 * @return     none.
 */
extern void gpio_output_dis(gpio_pin_e pin);

/**
 * @brief      This function disable the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function.
 * @return     none.
 */
extern void gpio_input_dis(gpio_pin_e pin);

/**
 * @brief      This function servers to set the specified GPIO into High-impedance state and also enable the pull-down resistor.
 *             To prevent power leakage, you need to call gpio_shutdown(GPIO_ALL) (set all gpio to high resistance, except SWS and MSPI)
 *             as front as possible in the program, and then initialize the corresponding GPIO according to the actual using situation.
 * @param[in]  pin  - select the specified GPIO.Only support GPIO_GROUPA ~GPIO_GROUPI,GPIO_GPOUPANA and GPIO_ALL.
 * @return     none.
 */
void gpio_shutdown(gpio_pin_e pin);

extern  void gpio_init(void);

#ifdef __cplusplus
}
#endif


#endif

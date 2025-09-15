/********************************************************************************************************
 * @file    adc_app_config_1v2.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C"
{
#endif
/*
 * To prevent leakage,in gpio_init(), all GPIOs are set to High-impedance and also enable the pull-down resistor except the MSPI pins and SWS:
 * before using the corresponding io, need to cancel the pull-down or redefine the function as required based on the application scenario.
 */
#if defined(MCU_CORE_TL322X)
#define  GPIO_M_CHNP_SAMPLE_SIGNAL     ADC0_GPIO_PC0P
#define  GPIO_M_CHNN_SAMPLE_SIGNAL     ADC0_GPIO_PC1N
#define  GPIO_L_CHNP_SAMPLE_SIGNAL     ADC0_GPIO_PC2P
#define  GPIO_L_CHNN_SAMPLE_SIGNAL     ADC0_GPIO_PC3N
#define  GPIO_R_CHNP_SAMPLE_SIGNAL     ADC0_GPIO_PC4P
#define  GPIO_R_CHNN_SAMPLE_SIGNAL     ADC0_GPIO_PC5N
#endif
#include "driver.h"
#define NORMAL_MODE             1
#define TEST_MODE               2 // For internal testing, users don't need to care
#define DEMO_MODE               NORMAL_MODE

#define ADC_DMA_MODE            1
#define ADC_NDMA_MODE           2

#define ADC0_MODULE   0 //ADC0
#define ADC1_MODULE   1 //ADC1
#define ADC_MODULE_SEL ADC0_MODULE

#define ADC_GPIO_SAMPLE         0
#define ADC_VBAT_SAMPLE         1
#if INTERNAL_TEST_FUNC_EN
#define ADC_TEMP_SENSOR_SAMPLE         2
#endif

#define  ADC_NO_FEATURE                         0
#if INTERNAL_TEST_FUNC_EN
#define  ADC_PEM_FEATURE                        1
#define  ADC_OVERSAMPLE_FEATURE                 2
#define  ADC_TRIGGER_FEATURE                    3
#define  ADC_TRIGGER_AND_OVERSAMPLE_FEATURE     4


#define OVERSAMPLE_AVERAGE_CNT2        0x00
#define OVERSAMPLE_AVERAGE_CNT4        0x01
#define OVERSAMPLE_AVERAGE_CNT8        0x02
#define OVERSAMPLE_AVERAGE_CNT16       0x03
#define OVERSAMPLE_AVERAGE_CNT32       0x04
#define OVERSAMPLE_AVERAGE_CNT64       0x05
#define OVERSAMPLE_AVERAGE_CNT128      0x06
#define OVERSAMPLE_AVERAGE_CNT256      0x07
#define OVERSAMPLE_AVERAGE_CNT512      0x08
#define OVERSAMPLE_AVERAGE_CNT1024     0x09
#define OVERSAMPLE_AVERAGE_CNT2048     0x0a
#define OVERSAMPLE_AVERAGE_CNT4096     0x0b

#define PEM_GPIO            4
#define PEM_SAR_ADC         10

#endif

//In NDMA mode, only M channel can be used.
#define NDMA_M_1_CHN_EN     1
//Multiple channels can be used in DMA mode.
#define DMA_M_1_CHN_EN      1//When using one channels in DMA mode, only M channel can be selected.
#if INTERNAL_TEST_FUNC_EN
#define DMA_M_L_2_CHN_EN    2//When using two channels in DMA mode, only M and L channels can be selected.
#define DMA_M_L_R_3_CHN_EN  3
#endif
    /**********************************************************************************************************************
 *                                         Users do not need to modify                                                *
 *********************************************************************************************************************/

// The maximum value is set at 10,000.
#define  ADC_SAMPLE_GROUP_CNT       8//Number of adc sample codes per channel.

#define  ADC_MODE                   ADC_NDMA_MODE

#define  ADC_FEATURE_MODE           ADC_NO_FEATURE

#if INTERNAL_TEST_FUNC_EN
#if (ADC_FEATURE_MODE == ADC_PEM_FEATURE)

#define PEM_EVENT_MODE      PEM_GPIO
#define PEM_TASK_MODE       PEM_SAR_ADC

#if PEM_TASK_MODE == PEM_SAR_ADC
#define TRIGGER_CNT         2
#endif

#elif ADC_FEATURE_MODE == ADC_TRIGGER_FEATURE
#define TRIGGER_CNT         10
#elif ADC_FEATURE_MODE == ADC_OVERSAMPLE_FEATURE || ADC_FEATURE_MODE == ADC_TRIGGER_AND_OVERSAMPLE_FEATURE

#define OVERSAMPLE_AVERAGE_CNT         OVERSAMPLE_AVERAGE_CNT8
#if ADC_FEATURE_MODE == ADC_TRIGGER_AND_OVERSAMPLE_FEATURE
#define TRIGGER_CNT         16
#endif
#endif
#endif

#if (ADC_MODE == ADC_DMA_MODE)
#define  ADC_DMA_CHN                DMA6
#define  ADC_SAMPLE_CHN_CNT         DMA_M_1_CHN_EN  //Number of channels enabled
#define  ADC_M_CHN_SAMPLE_MODE      ADC_GPIO_SAMPLE
#define  ADC_L_CHN_SAMPLE_MODE      ADC_VBAT_SAMPLE
#define  ADC_R_CHN_SAMPLE_MODE      ADC_GPIO_SAMPLE
#else
#define  ADC_SAMPLE_CHN_CNT         NDMA_M_1_CHN_EN
#define  ADC_SAMPLE_MODE            ADC_GPIO_SAMPLE
#endif

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

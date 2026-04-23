/*******************************************************************************************************
 *
 * @file    systimer.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __SYSTIMER_H__
#define __SYSTIMER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// TICK_L offsetaddress : 0x0
#define SYSTIMER_TICK_L_POS (0U)
#define SYSTIMER_TICK_L_MSK (0x1UL << SYSTIMER_TICK_L_POS) /*!< lower 32-bit of tick value*/
#define SYSTIMER_TICK_L     SYSTIMER_TICK_L_MSK

// TICK_H offsetaddress : 0x4
#define SYSTIMER_TICK_H_POS (0U)
#define SYSTIMER_TICK_H_MSK (0x1UL << SYSTIMER_TICK_H_POS) /*!< lower 32-bit of tick value*/
#define SYSTIMER_TICK_H     SYSTIMER_TICK_L_MSK

// INTR offsetaddress : 0x8
#define SYSTIMER_LEVEL_0_INTRRUPT_POS  (0U)
#define SYSTIMER_LEVEL_0_INTRRUPT_MSK  (0x1UL << SYSTIMER_LEVEL_0_INTRRUPT_POS) /*!< level 0 interrupt status and clear*/
#define SYSTIMER_LEVEL_0_INTRRUPT      SYSTIMER_LEVEL_0_INTRRUPT_MSK
#define SYSTIMER_LEVEL_0_INTRRUPT_W(X) ((X) << SYSTIMER_LEVEL_0_INTRRUPT_POS) /*!< level 0 interrupt status and clear*/

#define SYSTIMER_LEVEL_1_INTRRUPT_POS  (1U)
#define SYSTIMER_LEVEL_1_INTRRUPT_MSK  (0x1UL << SYSTIMER_LEVEL_1_INTRRUPT_POS) /*!< level 1 interrupt status and clear*/
#define SYSTIMER_LEVEL_1_INTRRUPT      SYSTIMER_LEVEL_1_INTRRUPT_MSK
#define SYSTIMER_LEVEL_1_INTRRUPT_W(X) ((X) << SYSTIMER_LEVEL_1_INTRRUPT_POS) /*!< level 1 interrupt status and clear*/

#define SYSTIMER_LEVEL_2_INTRRUPT_POS  (2U)
#define SYSTIMER_LEVEL_2_INTRRUPT_MSK  (0x1UL << SYSTIMER_LEVEL_2_INTRRUPT_POS) /*!< level 2 interrupt status and clear*/
#define SYSTIMER_LEVEL_2_INTRRUPT      SYSTIMER_LEVEL_2_INTRRUPT_MSK
#define SYSTIMER_LEVEL_2_INTRRUPT_W(X) ((X) << SYSTIMER_LEVEL_2_INTRRUPT_POS) /*!< level 2 interrupt status and clear*/

#define SYSTIMER_CALIBRATION_INTRRUPT_POS  (3U)
#define SYSTIMER_CALIBRATION_INTRRUPT_MSK  (0x1UL << SYSTIMER_CALIBRATION_INTRRUPT_POS) /*!< calibration interrupt status and clear*/
#define SYSTIMER_CALIBRATION_INTRRUPT      SYSTIMER_CALIBRATION_INTRRUPT_MSK
#define SYSTIMER_CALIBRATION_INTRRUPT_W(X) ((X) << SYSTIMER_CALIBRATION_INTRRUPT_POS) /*!< calibration interrupt status and clear*/

// CFG offsetaddress : 0x10
#define SYSTIMER_MANUAL_ENABLE_POS  (1U)
#define SYSTIMER_MANUAL_ENABLE_MSK  (0x1UL << SYSTIMER_MANUAL_ENABLE_POS) /*!< timer manual enable*/
#define SYSTIMER_MANUAL_ENABLE      SYSTIMER_MANUAL_ENABLE_MSK
#define SYSTIMER_MANUAL_ENABLE_W(X) ((X) << SYSTIMER_MANUAL_ENABLE_POS)

#define SYSTIMER_AUTO_ENABLE_POS  (2U)
#define SYSTIMER_AUTO_ENABLE_MSK  (0x1UL << SYSTIMER_AUTO_ENABLE_POS) /*!< timer auto enable*/
#define SYSTIMER_AUTO_ENABLE      SYSTIMER_AUTO_ENABLE_MSK
#define SYSTIMER_AUTO_ENABLE_W(X) ((X) << SYSTIMER_AUTO_ENABLE_POS)

#define SYSTIMER_32K_CALIBRATION_ENABLE_POS  (3U)
#define SYSTIMER_32K_CALIBRATION_ENABLE_MSK  (0x1UL << SYSTIMER_32K_CALIBRATION_ENABLE_POS) /*!< 32K calibration enable*/
#define SYSTIMER_32K_CALIBRATION_ENABLE      SYSTIMER_32K_CALIBRATION_ENABLE_MSK
#define SYSTIMER_32K_CALIBRATION_ENABLE_W(X) ((X) << SYSTIMER_32K_CALIBRATION_ENABLE_POS)

#define SYSTIMER_32K_CYCLE_CALIBRATION_POS  (4U)
#define SYSTIMER_32K_CYCLE_CALIBRATION_MSK  (0xFUL << SYSTIMER_32K_CYCLE_CALIBRATION_POS) /*!< 32K cycle for calibration:2^(16-CFG1<7:4>)*/
#define SYSTIMER_32K_CYCLE_CALIBRATION      SYSTIMER_32K_CYCLE_CALIBRATION_MSK
#define SYSTIMER_32K_CYCLE_CALIBRATION_W(X) ((X) << SYSTIMER_32K_CYCLE_CALIBRATION_POS)

#define SYSTIMER_START_32K_EDGE_ENABLE_POS  (8U)
#define SYSTIMER_START_32K_EDGE_ENABLE_MSK  (0x1UL << SYSTIMER_START_32K_EDGE_ENABLE_POS) /*!< timer tick start upon next 32K positive edge enable 0: disable 1: enable*/
#define SYSTIMER_START_32K_EDGE_ENABLE      SYSTIMER_START_32K_EDGE_ENABLE_MSK
#define SYSTIMER_START_32K_EDGE_ENABLE_W(X) ((X) << SYSTIMER_START_32K_EDGE_ENABLE_POS)

#define SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_POS  (9U)
#define SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_MSK  (0x1UL << SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_POS) /*!< timer tick value update upon 32K positive edge enable 0: disable 1: enable*/
#define SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE      SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_MSK
#define SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_W(X) ((X) << SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE_POS)

#define SYSTIMER_INTERRUPT_MASK_LEVEL0_POS  (16U)
#define SYSTIMER_INTERRUPT_MASK_LEVEL0_MSK  (0x1UL << SYSTIMER_INTERRUPT_MASK_LEVEL0_POS) /*!< interrupt mask for level 0 0: disable interrupt 1: enable interrupt*/
#define SYSTIMER_INTERRUPT_MASK_LEVEL0      SYSTIMER_INTERRUPT_MASK_LEVEL0_MSK
#define SYSTIMER_INTERRUPT_MASK_LEVEL0_W(X) ((X) << SYSTIMER_INTERRUPT_MASK_LEVEL0_POS)

#define SYSTIMER_INTERRUPT_MASK_LEVEL1_POS  (17U)
#define SYSTIMER_INTERRUPT_MASK_LEVEL1_MSK  (0x1UL << SYSTIMER_INTERRUPT_MASK_LEVEL1_POS) /*!< interrupt mask for level 1 0: disable interrupt 1: enable interrupt*/
#define SYSTIMER_INTERRUPT_MASK_LEVEL1      SYSTIMER_INTERRUPT_MASK_LEVEL1_MSK
#define SYSTIMER_INTERRUPT_MASK_LEVEL1_W(X) ((X) << SYSTIMER_INTERRUPT_MASK_LEVEL1_POS)

#define SYSTIMER_INTERRUPT_MASK_LEVEL2_POS  (18U)
#define SYSTIMER_INTERRUPT_MASK_LEVEL2_MSK  (0x1UL << SYSTIMER_INTERRUPT_MASK_LEVEL2_POS) /*!< interrupt mask for level 2 0: disable interrupt 1: enable interrupt*/
#define SYSTIMER_INTERRUPT_MASK_LEVEL2      SYSTIMER_INTERRUPT_MASK_LEVEL2_MSK
#define SYSTIMER_INTERRUPT_MASK_LEVEL2_W(X) ((X) << SYSTIMER_INTERRUPT_MASK_LEVEL2_POS)

#define SYSTIMER_INTERRUPT_MASK_CALIBRATION_POS  (19U)
#define SYSTIMER_INTERRUPT_MASK_CALIBRATION_MSK  (0x1UL << SYSTIMER_INTERRUPT_MASK_CALIBRATION_POS) /*!< calibration interrupt mask 2 0: disable interrupt 1: enable interrupt*/
#define SYSTIMER_INTERRUPT_MASK_CALIBRATION      SYSTIMER_INTERRUPT_MASK_CALIBRATION_MSK
#define SYSTIMER_INTERRUPT_MASK_CALIBRATION_W(X) ((X) << SYSTIMER_INTERRUPT_MASK_CALIBRATION_POS)

#define SYSTIMER_CPU0_DMA_INTR_POS  (20U)
#define SYSTIMER_CPU0_DMA_INTR_MSK  (0x1UL << SYSTIMER_CPU_DMA_INTR_POS) /*!< enable systimer latch upon cpu0 dma intr 0: disable 1: enable*/
#define SYSTIMER_CPU0_DMA_INTR      SYSTIMER_CPU_DMA_INTR_MSK
#define SYSTIMER_CPU0_DMA_INTR_W(X) ((X) << SYSTIMER_CPU_DMA_INTR_POS)

#define SYSTIMER_CPU2_DMA_INTR_POS  (21U)
#define SYSTIMER_CPU2_DMA_INTR_MSK  (0x1UL << SYSTIMER_CPU2_DMA_INTR_POS) /*!< enable systimer latch upon cpu2 dma intr 0: disable 1: enable*/
#define SYSTIMER_CPU2_DMA_INTR      SYSTIMER_CPU2_DMA_INTR_MSK
#define SYSTIMER_CPU2_DMA_INTR_W(X) ((X) << SYSTIMER_CPU2_DMA_INTR_POS)

#define SYSTIMER_AUDIO_DMA_INTR_POS  (22U)
#define SYSTIMER_AUDIO_DMA_INTR_MSK  (0x1UL << SYSTIMER_AUDIO_DMA_INTR_POS) /*!< enable systimer latch upon audio dma intr 0: disable 1: enable*/
#define SYSTIMER_AUDIO_DMA_INTR      SYSTIMER_AUDIO_DMA_INTR_MSK
#define SYSTIMER_AUDIO_DMA_INTR_W(X) ((X) << SYSTIMER_AUDIO_DMA_INTR_POS)

#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0_POS (24U)
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0_MSK (0x1UL << SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0_POS) /*!< enable interrupt wait for level 0*/
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0     SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0_MSK
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1_POS (25U)
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1_MSK (0x1UL << SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1_POS) /*!< enable interrupt wait for level 1*/
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1     SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1_MSK
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2_POS (26U)
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2_MSK (0x1UL << SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2_POS) /*!< enable interrupt wait for level 2*/
#define SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2     SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2_MSK

#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0_POS (28U)
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0_MSK (0x1UL << SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0_POS) /*!< enable past interrupt for level 0*/
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0     SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0_MSK
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1_POS (29U)
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1_MSK (0x1UL << SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1_POS) /*!< enable past interrupt for level 1*/
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1     SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1_MSK
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2_POS (30U)
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2_MSK (0x1UL << SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2_POS) /*!< enable past interrupt for level 2*/
#define SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2     SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2_MSK

// LVL0 offsetaddress : 0x10
#define SYSTIMER_CPU1_LEVEL_0_INTRRUPT_POS (0U)
#define SYSTIMER_CPU1_LEVEL_0_INTRRUPT_MSK (0x1UL << SYSTIMER_CPU1_LEVEL_0_INTRRUPT_POS) /*!< interrupt level 0 for CPU1*/
#define SYSTIMER_CPU1_LEVEL_0_INTRRUPT     SYSTIMER_CPU1_LEVEL_0_INTRRUPT_MSK

// LVL1 offsetaddress : 0x14
#define SYSTIMER_CPU0_LEVEL_0_INTRRUPT_POS (0U)
#define SYSTIMER_CPU0_LEVEL_0_INTRRUPT_MSK (0x1UL << SYSTIMER_CPU0_LEVEL_0_INTRRUPT_POS) /*!< interrupt level 0 for CPU0*/
#define SYSTIMER_CPU0_LEVEL_0_INTRRUPT     SYSTIMER_CPU0_LEVEL_0_INTRRUPT_MSK

// LVL2 offsetaddress : 0x18
#define SYSTIMER_CPU2_LEVEL_0_INTRRUPT_POS (0U)
#define SYSTIMER_CPU2_LEVEL_0_INTRRUPT_MSK (0x1UL << SYSTIMER_CPU2_LEVEL_0_INTRRUPT_POS) /*!< interrupt level 0 for CPU2*/
#define SYSTIMER_CPU2_LEVEL_0_INTRRUPT     SYSTIMER_CPU2_LEVEL_0_INTRRUPT_MSK

// CAL_LAT offsetaddress : 0x1C
#define SYSTIMER_CALIBRATION_RESULT_POS (0U)
#define SYSTIMER_CALIBRATION_RESULT_MSK (0x1UL << SYSTIMER_CALIBRATION_RESULT_POS) /*!< calibration result (16MHz clock cycle)*/
#define SYSTIMER_CALIBRATION_RESULT     SYSTIMER_CALIBRATION_RESULT_MSK

// TICK_LAT0 offsetaddress : 0x20
#define SYSTIMER_CPU0_DMA_INTR_VALUE_POS (0U)
#define SYSTIMER_CPU0_DMA_INTR_VALUE_MSK (0x1UL << SYSTIMER_CPU0_DMA_INTR_VALUE_POS) /*!< tick value latched upon cpu0 dma intr*/
#define SYSTIMER_CPU0_DMA_INTR_VALUE     SYSTIMER_CPU0_DMA_INTR_VALUE_MSK

// TICK_LAT1 offsetaddress : 0x20
#define SYSTIMER_CPU2_DMA_INTR_VALUE_POS (0U)
#define SYSTIMER_CPU2_DMA_INTR_VALUE_MSK (0x1UL << SYSTIMER_CPU2_DMA_INTR_VALUE_POS) /*!< tick value latched upon cpu2 dma intr*/
#define SYSTIMER_CPU2_DMA_INTR_VALUE     SYSTIMER_CPU1_DMA_INTR_VALUE_MSK

// TICK_LAT2 offsetaddress : 0x20
#define SYSTIMER_AUDIO_DMA_INTR_VALUE_POS (0U)
#define SYSTIMER_AUDIO_DMA_INTR_VALUE_MSK (0x1UL << SYSTIMER_AUDIO_DMA_INTR_VALUE_POS) /*!< tick value latched upon audio dma intr*/
#define SYSTIMER_AUDIO_DMA_INTR_VALUE     SYSTIMER_AUDIO_DMA_INTR_VALUE_MSK

typedef struct {
    volatile uint32_t TICK_L;    // offsetaddress : 0x0
    volatile uint32_t TICK_H;    // offsetaddress : 0x4
    volatile uint32_t INTR;      // offsetaddress : 0x8
    volatile uint32_t CFG;       // offsetaddress : 0xc
    volatile uint32_t LVL0;      // offsetaddress : 0x10
    volatile uint32_t LVL1;      // offsetaddress : 0x14
    volatile uint32_t LVL2;      // offsetaddress : 0x18
    volatile uint32_t CAL_LAT;   // offsetaddress : 0x1C
    volatile uint32_t TICK_LAT0; // offsetaddress : 0x20
    volatile uint32_t TICK_LAT1; // offsetaddress : 0x24
    volatile uint32_t TICK_LAT2; // offsetaddress : 0x28
} systimer_reg_t;
#ifdef __cplusplus
}
#endif
#endif

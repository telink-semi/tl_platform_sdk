/*******************************************************************************************************
 *
 * @file    pdmc.h
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
#ifndef __PDMC_H__
#define __PDMC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

// offsetaddress : 0x0000
#define PDMC_ENABLE_POS (0U)
#define PDMC_ENABLE_MSK (0x1UL << PDMC_ENABLE_POS)
#define PDMC_ENABLE     PDMC_ENABLE_MSK

// offsetaddress : 0x0004
#define PDMC_MODE_SEL_POS (0U)
#define PDMC_MODE_SEL_MSK (0x1UL << PDMC_MODE_SEL_POS)
#define PDMC_MODE_SEL     PDMC_MODE_SEL_MSK

// offsetaddress : 0x0008
#define PDMC_CLKSEL_POS (0U)
#define PDMC_CLKSEL_MSK (0x1UL << PDMC_CLKSEL_POS)
#define PDMC_CLKSEL     PDMC_CLKSEL_MSK
#define PDMC_CLKINV_POS (1U)
#define PDMC_CLKINV_MSK (0x1UL << PDMC_CLKINV_POS)
#define PDMC_CLKINV     PDMC_CLKINV_MSK

// offsetaddress : 0x000c
#define PDMC_TXFIFO_DATA_POS (0U)
#define PDMC_TXFIFO_DATA_MSK (0xFFFFFFFFUL << PDMC_TXFIFO_DATA_POS)
#define PDMC_TXFIFO_DATA     PDMC_TXFIFO_DATA_MSK

// offsetaddress : 0x0010
#define PDMC_TXFIFO_AEMPTY_POS     (0U)
#define PDMC_TXFIFO_AEMPTY_MSK     (0x1UL << PDMC_TXFIFO_AEMPTY_POS)
#define PDMC_TXFIFO_AEMPTY         PDMC_TXFIFO_AEMPTY_MSK
#define PDMC_TXFIFO_EMPTY_POS      (1U)
#define PDMC_TXFIFO_EMPTY_MSK      (0x1UL << PDMC_TXFIFO_EMPTY_POS)
#define PDMC_TXFIFO_EMPTY          PDMC_TXFIFO_EMPTY_MSK
#define PDMC_TXFIFO_AFULL_POS      (2U)
#define PDMC_TXFIFO_AFULL_MSK      (0x1UL << PDMC_TXFIFO_AFULL_POS)
#define PDMC_TXFIFO_AFULL          PDMC_TXFIFO_AFULL_MSK
#define PDMC_TXFIFO_FULL_POS       (3U)
#define PDMC_TXFIFO_FULL_MSK       (0x1UL << PDMC_TXFIFO_FULL_POS)
#define PDMC_TXFIFO_FULL           PDMC_TXFIFO_FULL_MSK
#define PDMC_TXFIFO_TXLVL_TRIG_POS (4U)
#define PDMC_TXFIFO_TXLVL_TRIG_MSK (0x1UL << PDMC_TXFIFO_TXLVL_TRIG_POS)
#define PDMC_TXFIFO_TXLVL_TRIG     PDMC_TXFIFO_TXLVL_TRIG_MSK
#define PDMC_TXFIFO_POP_ERROR_POS  (5U)
#define PDMC_TXFIFO_POP_ERROR_MSK  (0x1UL << PDMC_TXFIFO_POP_ERROR_POS)
#define PDMC_TXFIFO_POP_ERROR      PDMC_TXFIFO_POP_ERROR_MSK
#define PDMC_TXFIFO_PUSH_ERROR_POS (6U)
#define PDMC_TXFIFO_PUSH_ERROR_MSK (0x1UL << PDMC_TXFIFO_PUSH_ERROR_POS)
#define PDMC_TXFIFO_PUSH_ERROR     PDMC_TXFIFO_PUSH_ERROR_MSK
#define PDMC_TXFIFO_FLUSH_POS      (7U)
#define PDMC_TXFIFO_FLUSH_MSK      (0x1UL << PDMC_TXFIFO_FLUSH_POS)
#define PDMC_TXFIFO_FLUSH          PDMC_TXFIFO_FLUSH_MSK

// offsetaddress : 0x0014
#define PDMC_DMA_TXLVL_POS (0U)
#define PDMC_DMA_TXLVL_MSK (0xFUL << PDMC_DMA_TXLVL_POS)
#define PDMC_DMA_TXLVL     PDMC_DMA_TXLVL_MSK
#define PDMC_DMA_TX_EN_POS (8U)
#define PDMC_DMA_TX_EN_MSK (0x1UL << PDMC_DMA_TX_EN_POS)
#define PDMC_DMA_TX_EN     PDMC_DMA_TX_EN_MSK

// offsetaddress : 0x0020
#define PDMC_TXFIFO_DATA_READY_POS (0U)
#define PDMC_TXFIFO_DATA_READY_MSK (0x1UL << PDMC_TXFIFO_DATA_READY_POS)
#define PDMC_TXFIFO_DATA_READY     PDMC_TXFIFO_DATA_READY_MSK
#define PDMC_TXFIFO_OVERFLOW_POS   (1U)
#define PDMC_TXFIFO_OVERFLOW_MSK   (0x1UL << PDMC_TXFIFO_OVERFLOW_POS)
#define PDMC_TXFIFO_OVERFLOW       PDMC_TXFIFO_OVERFLOW_MSK
#define PDMC_TXFIFO_UNDERFLOW_POS  (2U)
#define PDMC_TXFIFO_UNDERFLOW_MSK  (0x1UL << PDMC_TXFIFO_UNDERFLOW_POS)
#define PDMC_TXFIFO_UNDERFLOW      PDMC_TXFIFO_UNDERFLOW_MSK

// offsetaddress : 0x0024
#define PDMC_TXFIFO_DATA_READY_RAW_POS (0U)
#define PDMC_TXFIFO_DATA_READY_RAW_MSK (0x1UL << PDMC_TXFIFO_DATA_READY_RAW_POS)
#define PDMC_TXFIFO_DATA_READY_RAW     PDMC_TXFIFO_DATA_READY_RAW_MSK
#define PDMC_TXFIFO_OVERFLOW_RAW_POS   (1U)
#define PDMC_TXFIFO_OVERFLOW_RAW_MSK   (0x1UL << PDMC_TXFIFO_OVERFLOW_RAW_POS)
#define PDMC_TXFIFO_OVERFLOW_RAW       PDMC_TXFIFO_OVERFLOW_RAW_MSK
#define PDMC_TXFIFO_UNDERFLOW_RAW_POS  (2U)
#define PDMC_TXFIFO_UNDERFLOW_RAW_MSK  (0x1UL << PDMC_TXFIFO_UNDERFLOW_RAW_POS)
#define PDMC_TXFIFO_UNDERFLOW_RAW      PDMC_TXFIFO_UNDERFLOW_RAW_MSK

// offsetaddress : 0x0028
#define PDMC_TXFIFO_DATA_READY_EN_POS (0U)
#define PDMC_TXFIFO_DATA_READY_EN_MSK (0x1UL << PDMC_TXFIFO_DATA_READY_EN_POS)
#define PDMC_TXFIFO_DATA_READY_EN     PDMC_TXFIFO_DATA_READY_EN_MSK
#define PDMC_TXFIFO_OVERFLOW_EN_POS   (1U)
#define PDMC_TXFIFO_OVERFLOW_EN_MSK   (0x1UL << PDMC_TXFIFO_OVERFLOW_EN_POS)
#define PDMC_TXFIFO_OVERFLOW_EN       PDMC_TXFIFO_OVERFLOW_EN_MSK
#define PDMC_TXFIFO_UNDERFLOW_EN_POS  (2U)
#define PDMC_TXFIFO_UNDERFLOW_EN_MSK  (0x1UL << PDMC_TXFIFO_UNDERFLOW_EN_POS)
#define PDMC_TXFIFO_UNDERFLOW_EN      PDMC_TXFIFO_UNDERFLOW_EN_MSK

/******************************* PDMC ******************************/
typedef struct pdmc_reg {
    DRV_IOM uint32_t PDMC_TRANS_EN;    /* offset 0x0000 */
    DRV_IOM uint32_t PDMC_CONFIG;      /* offset 0x0004 */
    DRV_IOM uint32_t PDMC_CLOCK_GEN;   /* offset 0x0008 */
    DRV_IOM uint32_t PDMC_TXFIFO;      /* offset 0x000C */
    DRV_IOM uint32_t PDMC_FIFO_STATUS; /* offset 0x0010 */
    DRV_IOM uint32_t PDMC_DMA_CONFIG;  /* offset 0x0014 */
    DRV_IOM uint32_t RESERVED0[2];
    DRV_IOM uint32_t PDMC_INT;     /* offset 0x0020 */
    DRV_IOM uint32_t PDMC_INT_RAW; /* offset 0x0024 */
    DRV_IOM uint32_t PDMC_INT_EN;  /* offset 0x0028 */
} pdmc_reg_t;

#ifdef __cplusplus
}
#endif

#endif

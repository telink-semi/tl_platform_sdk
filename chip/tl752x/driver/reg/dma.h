/*******************************************************************************************************
 *
 * @file    dma.h
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
#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************* DMAC ************************/
/********************  Bit definition forDMA register  *****************/
/* define controller bit for DMAC_CTL */
#define DMAC_CTL_BLOCK_TS_POS  (32U)
#define DMAC_CTL_BLOCK_TS_MASK ((uint64_t)0xFFF << DMAC_CTL_BLOCK_TS_POS)
#define DMAC_CTL_BLOCK_TS      DMAC_CTL_BLOCK_TS_MASK

#define DMAC_CTL_TT_POS  (20U)
#define DMAC_CTL_TT_MASK ((uint64_t)0x7 << DMAC_CTL_TT_POS)
#define DMAC_CTL_TT      DMAC_CTL_TT_MASK

#define DMAC_CTL_DST_SCATTER_EN_POS  (18U)
#define DMAC_CTL_DST_SCATTER_EN_MASK ((uint64_t)0x1 << DMAC_CTL_DST_SCATTER_EN_POS)
#define DMAC_CTL_DST_SCATTER_EN      DMAC_CTL_DST_SCATTER_EN_MASK

#define DMAC_CTL_SRC_GATHER_EN_POS  (17U)
#define DMAC_CTL_SRC_GATHER_EN_MASK ((uint64_t)0x1 << DMAC_CTL_SRC_GATHER_EN_POS)
#define DMAC_CTL_SRC_GATHER_EN      DMAC_CTL_SRC_GATHER_EN_MASK

#define DMAC_CTL_SRC_MSIZE_POS  (14U)
#define DMAC_CTL_SRC_MSIZE_MASK ((uint64_t)0x7 << DMAC_CTL_SRC_MSIZE_POS)
#define DMAC_CTL_SRC_MSIZE      DMAC_CTL_SRC_MSIZE_MASK

#define DMAC_CTL_DST_MSIZE_POS  (11U)
#define DMAC_CTL_DST_MSIZE_MASK ((uint64_t)0x7 << DMAC_CTL_DST_MSIZE_POS)
#define DMAC_CTL_DST_MSIZE      DMAC_CTL_DST_MSIZE_MASK

#define DMAC_CTL_SINC_POS  (9U)
#define DMAC_CTL_SINC_MASK ((uint64_t)0x3 << DMAC_CTL_SINC_POS)
#define DMAC_CTL_SINC      DMAC_CTL_SINC_MASK

#define DMAC_CTL_DINC_POS  (7U)
#define DMAC_CTL_DINC_MASK ((uint64_t)0x3 << DMAC_CTL_DINC_POS)
#define DMAC_CTL_DINC      DMAC_CTL_DINC_MASK

#define DMAC_SRC_TR_WIDTH_POS  (4U)
#define DMAC_SRC_TR_WIDTH_MASK ((uint64_t)0x7 << DMAC_SRC_TR_WIDTH_POS)
#define DMAC_SRC_TR_WIDTH      DMAC_SRC_TR_WIDTH_MASK

#define DMAC_DST_TR_WIDTH_POS  (1U)
#define DMAC_DST_TR_WIDTH_MASK ((uint64_t)0x7 << DMAC_DST_TR_WIDTH_POS)
#define DMAC_DST_TR_WIDTH      DMAC_DST_TR_WIDTH_MASK

#define DMAC_INT_EN_POS  (0U)
#define DMAC_INT_EN_MASK ((uint64_t)0x1 << DMAC_INT_EN_POS)
#define DMAC_INT_EN      DMAC_INT_EN_MASK

/* define controller bit for DMAC_CFG */
#define DMAC_DST_PER_POS  (43U)
#define DMAC_DST_PER_MASK ((uint64_t)0xF << DMAC_DST_PER_POS)
#define DMAC_DST_PER      DMAC_DST_PER_MASK

#define DMAC_SRC_PER_POS  (39U)
#define DMAC_SRC_PER_MASK ((uint64_t)0xF << DMAC_SRC_PER_POS)
#define DMAC_SRC_PER      DMAC_SRC_PER_MASK

#define DMAC_FIFO_MODE_POS  (33U)
#define DMAC_FIFO_MODE_MASK ((uint64_t)0x1 << DMAC_FIFO_MODE_POS)
#define DMAC_FIFO_MODE      DMAC_FIFO_MODE_MASK

#define DMAC_HS_SEL_SRC_POS  (11U)
#define DMAC_HS_SEL_SRC_MASK ((uint64_t)0x1 << DMAC_HS_SEL_SRC_POS)
#define DMAC_HS_SEL_SRC      DMAC_HS_SEL_SRC_MASK

#define DMAC_HS_SEL_DST_POS  (10U)
#define DMAC_HS_SEL_DST_MASK ((uint64_t)0x1 << DMAC_HS_SEL_DST_POS)
#define DMAC_HS_SEL_DST      DMAC_HS_SEL_DST_MASK

#define DMAC_CH_PRIOR_POS  (5U)
#define DMAC_CH_PRIOR_MASK ((uint64_t)0x7 << DMAC_CH_PRIOR_POS)
#define DMAC_CH_PRIOR      DMAC_CH_PRIOR_MASK

#define DMAC_CH_SUSP_POS  (8U)
#define DMAC_CH_SUSP_MASK ((uint64_t)0x1 << DMAC_CH_SUSP_POS)
#define DMAC_CH_SUSP      DMAC_CH_SUSP_MASK

#define DMAC_CH_FIFOEMPTY_POS  (9U)
#define DMAC_CH_FIFOEMPTY_MASK ((uint64_t)0x1 << DMAC_CH_FIFOEMPTY_POS)
#define DMAC_CH_FIFOEMPTY      DMAC_CH_FIFOEMPTY_MASK

#define DMAC_INTR_STATUS_TFR_POS  (0U)
#define DMAC_INTR_STATUS_TFR_MASK ((uint64_t)0x1 << DMAC_INTR_STATUS_TFR_POS)
#define DMAC_INTR_STATUS_TFR      DMAC_INTR_STATUS_TFR_MASK

#define DMAC_INTR_STATUS_BLOCK_POS  (1U)
#define DMAC_INTR_STATUS_BLOCK_MASK ((uint64_t)0x1 << DMAC_INTR_STATUS_BLOCK_POS)
#define DMAC_INTR_STATUS_BLOCK      DMAC_INTR_STATUS_BLOCK_MASK

#define DMAC_INTR_STATUS_SRCT_POS  (2U)
#define DMAC_INTR_STATUS_SRCT_MASK ((uint64_t)0x1 << DMAC_INTR_STATUS_SRCT_POS)
#define DMAC_INTR_STATUS_SRCT      DMAC_INTR_STATUS_SRCT_MASK

#define DMAC_INTR_STATUS_DSTT_POS  (3U)
#define DMAC_INTR_STATUS_DSTT_MASK ((uint64_t)0x1 << DMAC_INTR_STATUS_DSTT_POS)
#define DMAC_INTR_STATUS_DSTT      DMAC_INTR_STATUS_DSTT_MASK

#define DMAC_INTR_STATUS_ERR_POS  (4U)
#define DMAC_INTR_STATUS_ERR_MASK ((uint64_t)0x1 << DMAC_INTR_STATUS_ERR_POS)
#define DMAC_INTR_STATUS_ERR      DMAC_INTR_STATUS_ERR_MASK

#define DMAC_SRC_LLP_EN_POS  (28U)
#define DMAC_SRC_LLP_EN_MASK ((uint64_t)0x1 << DMAC_SRC_LLP_EN_POS)
#define DMAC_SRC_LLP_EN      DMAC_SRC_LLP_EN_MASK

#define DMAC_DST_LLP_EN_POS  (27U)
#define DMAC_DST_LLP_EN_MASK ((uint64_t)0x1 << DMAC_DST_LLP_EN_POS)
#define DMAC_DST_LLP_EN      DMAC_DST_LLP_EN_MASK

#define DMAC_BLOCK_TR_DONE_POS  (12U)
#define DMAC_BLOCK_TR_DONE_MASK ((uint64_t)0x1 << DMAC_BLOCK_TR_DONE_POS)
#define DMAC_BLOCK_TR_DONE DMAC_BLOCK_TR_DONE_MASK

#define DMAC_BASE_ADDRESS_OFFSET (0x2C0UL)
#define DMAC_CHANNEL_REG_SIZE    (0x58UL)
#define DMA_CHANNEL_OFFSET       (8U)

#define DMAC_FIFO_EMPTY     (1U)
#define DMAC_FIFO_NOT_EMPTY (0U)

typedef struct {
    volatile uint64_t DMAC_SAR;    /* Offset 0x000 */
    volatile uint64_t DMAC_DAR;    /* Offset 0x008 */
    volatile uint64_t DMAC_LLP;    /* Offset 0x010 */
    volatile uint64_t DMAC_CTL;    /* Offset 0x018 */
    volatile uint64_t DMAC_SSTAT;  /* Offset 0x020 */
    volatile uint64_t DMAC_DSTAT;  /* Offset 0x028 */
    volatile uint64_t DMAC_SSTART; /* Offset 0x030 */
    volatile uint64_t DMAC_DSTART; /* Offset 0x038 */
    volatile uint64_t DMAC_CFG;    /* Offset 0x040 */
    volatile uint64_t DMAC_SGR;    /* Offset 0x048 */
    volatile uint64_t DMAC_DSR;    /* Offset 0x050 */
} dmac_channel_reg_t;

typedef struct {
    volatile uint64_t DMAC_RAWTFR;        /* Offset 0x2C0 */
    volatile uint64_t DMAC_RAWBLOCK;      /* Offset 0x2C8 */
    volatile uint64_t DMAC_RAWSRCTRAN;    /* Offset 0x2D0 */
    volatile uint64_t DMAC_RAWDSTTRAN;    /* Offset 0x2D8 */
    volatile uint64_t DMAC_RAWERR;        /* Offset 0x2E0 */
    volatile uint64_t DMAC_STATUSTFR;     /* Offset 0x2E8 */
    volatile uint64_t DMAC_STATUSBLOCK;   /* Offset 0x2F0 */
    volatile uint64_t DMAC_STATUSSRCTRAN; /* Offset 0x2F8 */
    volatile uint64_t DMAC_STATUSDSTTRAN; /* Offset 0x300 */
    volatile uint64_t DMAC_STATUSERR;     /* Offset 0x308 */
    volatile uint64_t DMAC_ENTFR;         /* Offset 0x310 */
    volatile uint64_t DMAC_ENBLOCK;       /* Offset 0x318 */
    volatile uint64_t DMAC_ENSRCTRAN;     /* Offset 0x320 */
    volatile uint64_t DMAC_ENDSTTRAN;     /* Offset 0x328 */
    volatile uint64_t DMAC_ENERR;         /* Offset 0x330 */
    volatile uint64_t DMAC_CLEARTFR;      /* Offset 0x338 */
    volatile uint64_t DMAC_CLEARBLOCK;    /* Offset 0x340 */
    volatile uint64_t DMAC_CLEARSRCTRAN;  /* Offset 0x348 */
    volatile uint64_t DMAC_CLEARDSTTRAN;  /* Offset 0x350 */
    volatile uint64_t DMAC_CLEARERR;      /* Offset 0x358 */
    volatile uint64_t DMAC_STATUSINT;     /* Offset 0x360 */
    volatile uint64_t DMAC_REQSRCREG;     /* Offset 0x368 */
    volatile uint64_t DMAC_REQDSTREG;     /* Offset 0x370 */
    volatile uint64_t DMAC_SGLREQSRCREG;  /* Offset 0x378 */
    volatile uint64_t DMAC_SGLREQDSTREG;  /* Offset 0x380 */
    volatile uint64_t DMAC_LSTSRCREG;     /* Offset 0x388 */
    volatile uint64_t DMAC_LSTDSTREG;     /* Offset 0x390 */
    volatile uint64_t DMAC_CFGREG;        /* Offset 0x398 */
    volatile uint64_t DMAC_CHENREG;       /* Offset 0x3A0 */
} dmac_reg_t;

#ifdef __cplusplus
}
#endif
#endif

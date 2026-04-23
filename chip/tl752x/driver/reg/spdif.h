/*******************************************************************************************************
 *
 * @file    spdif.h
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
#ifndef __SPDIF_H__
#define __SPDIF_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/*********************  Bit definition for SPDIF register  ********************/
//offsetaddress : 0x0000
#define SPDIF_TSAMPLERATE_Pos (0U)
#define SPDIF_TSAMPLERATE_Msk (0xFFUL << SPDIF_TSAMPLERATE_Pos) /*!< Transmission sample rate. */
#define SPDIF_SFR_ENABLE_Pos  (8U)
#define SPDIF_SFR_ENABLE_Msk  (0x1UL << SPDIF_SFR_ENABLE_Pos) /*!< Bit controlling SFR block synchronous reset */
#define SPDIF_ENABLE_Pos      (9U)
#define SPDIF_ENABLE_Msk      (0x1UL << SPDIF_ENABLE_Pos) /*!< SPDIF core enable */
#define SPDIF_FIFO_ENABLE_Pos (10U)
#define SPDIF_FIFO_ENABLE_Msk (0x1UL << SPDIF_FIFO_ENABLE_Pos) /*!< FIFO enable */
#define SPDIF_CLK_ENABLE_Pos  (11U)
#define SPDIF_CLK_ENABLE_Msk  (0x1UL << SPDIF_CLK_ENABLE_Pos) /*!< Clock enable for the SPDIF core and FIFO */
#define SPDIF_TR_MODE_Pos     (12U)
#define SPDIF_TR_MODE_Msk     (0x1UL << SPDIF_TR_MODE_Pos) /*!< Direction control (transmitter - '1' / receiver - '0'). */
/*!< When '1' - check on a parity error in received sub-frame, the parityo is asserted when a parity error has been detected. When '0' - parity bit received in a sub-frame is repeated on the parityo */
#define SPDIF_PARITYCHECK_Pos (13U)
#define SPDIF_PARITYCHECK_Msk (0x1UL << SPDIF_PARITYCHECK_Pos)
/*!< When '1', a parity bit is generated inside the core and added to a transmitted sub-frame. When '0' the value from the parity bit from FIFO is transmitted in sub-frame. Sampled on the rising clock edge */
#define SPDIF_PARITYGEN_Pos (14U)
#define SPDIF_PARITYGEN_Msk (0x1UL << SPDIF_PARITYGEN_Pos)
/*!< When '1', the validity bit in received frame is checked, if it's low the frame is written, else the frame is discarded. When validitycheck is '0' the validity bit in frame isn't checked and all frames are written */
#define SPDIF_VALIDITYCHECK_Pos (15U)
#define SPDIF_VALIDITYCHECK_Msk (0x1UL << SPDIF_VALIDITYCHECK_Pos)
#define SPDIF_CHANNEL_MODE_Pos  (16U)
#define SPDIF_CHANNEL_MODE_Msk  (0x1UL << SPDIF_CHANNEL_MODE_Pos) /*!< When '1', the single-channel (monophonic) mode is forced. When '0', the two-channel (stereophonic) mode is forced */
#define SPDIF_DUPLICATE_Pos     (17U)
#define SPDIF_DUPLICATE_Msk     (0x1UL << SPDIF_DUPLICATE_Pos) /*!< This bit is valid only when working as transmitter in single-channel mode */
#define SPDIF_SETPREAMBB_Pos    (18U)
#define SPDIF_SETPREAMBB_Msk    (0x1UL << SPDIF_SETPREAMBB_Pos) /*!< This bit is valid only when working as transmitter. */
#define SPDIF_PARITY_MASK_Pos   (21U)
#define SPDIF_PARITY_MASK_Msk   (0x1UL << SPDIF_PARITY_MASK_Pos) /*!< Bit masking interrupt request generation after parityo occurred '1' (parityo state is depended on the paritycheck bit). */
#define SPDIF_UNDERR_MASK_Pos   (22U)
#define SPDIF_UNDERR_MASK_Msk   (0x1UL << SPDIF_UNDERR_MASK_Pos) /*!< Bit masking interrupt request generation after underrun error occurrence. */
#define SPDIF_OVERR_MASK_Pos    (23U)
#define SPDIF_OVERR_MASK_Msk    (0x1UL << SPDIF_OVERR_MASK_Pos) /*!< Bit masking interrupt request generation after overrun error occurrence. */
#define SPDIF_EMPTY_MASK_Pos    (24U)
#define SPDIF_EMPTY_MASK_Msk    (0x1UL << SPDIF_EMPTY_MASK_Pos) /*!< Bit masking interrupt request generation after FIFO becomes empty */
#define SPDIF_AEMPTY_MASK_Pos   (25U)
#define SPDIF_AEMPTY_MASK_Msk   (0x1UL << SPDIF_AEMPTY_MASK_Pos) /*!< Bit masking interrupt request generation after FIFO becomes almost empty */
#define SPDIF_FULL_MASK_Pos     (26U)
#define SPDIF_FULL_MASK_Msk     (0x1UL << SPDIF_FULL_MASK_Pos) /*!< Bit masking interrupt request generation after FIFO becomes full. */
#define SPDIF_AFULL_MASK_Pos    (27U)
#define SPDIF_AFULL_MASK_Msk    (0x1UL << SPDIF_AFULL_MASK_Pos) /*!< Bit masking interrupt request generation after FIFO becomes almost full */
#define SPDIF_SYNCERR_MASK_Pos  (28U)
#define SPDIF_SYNCERR_MASK_Msk  (0x1UL << SPDIF_SYNCERR_MASK_Pos) /*!< Bit masking interrupt generation after synchronization error occurrence */
#define SPDIF_LOCK_MASK_Pos     (29U)
#define SPDIF_LOCK_MASK_Msk     (0x1UL << SPDIF_LOCK_MASK_Pos) /*!< Bit masking interrupt generation after receiver becomes synchronized with input data stream (i.e. it is in lock condition). */
#define SPDIF_BEGIN_MASK_Pos    (30U)
#define SPDIF_BEGIN_MASK_Msk    (0x1UL << SPDIF_BEGIN_MASK_Pos) /*!< Bit masking interrupt generation after receiving block begin preamble. */
#define SPDIF_INTREQ_MASK_Pos   (31U)
#define SPDIF_INTREQ_MASK_Msk   (0x1UL << SPDIF_INTREQ_MASK_Pos) /*!< Bit masking all interrupt requests. */

//offsetaddress : 0x0004
#define SPDIF_RSAMPLERATE_Pos  (0U)
#define SPDIF_RSAMPLERATE_Msk  (0xFFUL << SPDIF_RSAMPLERATE_Pos) /*!< Receive sample rate. */
#define SPDIF_PREAMPLERATE_Pos (8U)
#define SPDIF_PREAMPLERATE_Msk (0x7FUL << SPDIF_PREAMPLERATE_Pos) /*!< First preamble B delay */
#define SPDIF_PARITYO_Pos      (21U)
#define SPDIF_PARITYO_Msk      (0x1UL << SPDIF_PARITYO_Pos) /*!< Parity error */
#define SPDIF_TDATA_UNDERR_Pos (22U)
#define SPDIF_TDATA_UNDERR_Msk (0x1UL << SPDIF_TDATA_UNDERR_Pos) /*!< Transmitter data underrun error. */
#define SPDIF_RDATA_OVRERR_Pos (23U)
#define SPDIF_RDATA_OVRERR_Msk (0x1UL << SPDIF_RDATA_OVRERR_Pos) /*!< Receiver data overrun error. */
#define SPDIF_FIFO_EMPTY_Pos   (24U)
#define SPDIF_FIFO_EMPTY_Msk   (0x1UL << SPDIF_FIFO_EMPTY_Pos) /*!< FIFO empty flag */
#define SPDIF_FIFO_AEMPTY_Pos  (25U)
#define SPDIF_FIFO_AEMPTY_Msk  (0x1UL << SPDIF_FIFO_AEMPTY_Pos) /*!< FIFO almost empty flag. */
#define SPDIF_FIFO_FULL_Pos    (26U)
#define SPDIF_FIFO_FULL_Msk    (0x1UL << SPDIF_FIFO_FULL_Pos) /*!< FIFO full flag */
#define SPDIF_FIFO_AFULL_Pos   (27U)
#define SPDIF_FIFO_AFULL_Msk   (0x1UL << SPDIF_FIFO_AFULL_Pos) /*!< FIFO almost full flag. */
/*!< When '1', it indicates receiver synchronization error. It is a source of an interrupt request.  Once it is set to '1' it holds its value until writing '0', even when synchronization error condition disappears. Updated on the rising clock edge. */
#define SPDIF_SYNCERR_Pos (28U)
#define SPDIF_SYNCERR_Msk (0x1UL << SPDIF_SYNCERR_Pos)
/*!< When '1', it indicates that receiver has become synchronized with input data stream (i.e. it is in lock condition). Once it is set to '1' it holds its value until writing '0' */
#define SPDIF_LOCK_Pos (29U)
#define SPDIF_LOCK_Msk (0x1UL << SPDIF_LOCK_Pos)
/*!< When '1', it indicates start of a new block in received data. It is set to '1' when sub-frame with preamble 'B' has been received and written into FIFO. Once it is set to '1' it holds its value until writing '0' */
#define SPDIF_BLOCK_BEGIN_Pos (30U)
#define SPDIF_BLOCK_BEGIN_Msk (0x1UL << SPDIF_BLOCK_BEGIN_Pos)
//offsetaddress : 0x0008
#define SPDIF_AEMPTY_THRESHOLD_Pos (0U)
#define SPDIF_AEMPTY_THRESHOLD_Msk (0x3FUL << SPDIF_AEMPTY_THRESHOLD_Pos) /*!< Determines threshold for almost empty flag in the FIFO. */
#define SPDIF_AFULL_THRESHOLD_Pos  (16U)
#define SPDIF_AFULL_THRESHOLD_Msk  (0x3FUL << SPDIF_AFULL_THRESHOLD_Pos) /*!< Determines threshold for almost full flag in the FIFO. */
#define SPDIF_DMA_EN_Pos           (22U)
#define SPDIF_DMA_EN_Msk           (0x1UL << SPDIF_DMA_EN_Pos)
#define SPDIF_CLKB_SEL_Pos         (23U)
#define SPDIF_CLKB_SEL_Msk         (0x1UL << SPDIF_CLKB_SEL_Pos)

//offsetaddress : 0x000C
#define SPDIF_FIFO_LEVEL_Pos   (0U)
#define SPDIF_FIFO_LEVEL_Msk   (0x3FUL << SPDIF_FIFO_LEVEL_Pos) /*!< Determines threshold for almost empty flag in the FIFO. */
#define SPDIF_PARITY_flag_Pos  (21U)
#define SPDIF_PARITY_flag_Msk  (0x1UL << SPDIF_PARITY_flag_Pos) /*!<  Parity flag. This bit is depended on parity_check bit. */
#define SPDIF_UNDERR_flag_Pos  (22U)
#define SPDIF_UNDERR_flag_Msk  (0x1UL << SPDIF_UNDERR_flag_Pos) /*!<  Transmitter data underrun flag. */
#define SPDIF_OVRERR_flag_Pos  (23U)
#define SPDIF_OVRERR_flag_Msk  (0x1UL << SPDIF_OVRERR_flag_Pos) /*!< Receiver data overrun error. */
#define SPDIF_EMPTY_flag_Pos   (24U)
#define SPDIF_EMPTY_flag_Msk   (0x1UL << SPDIF_EMPTY_flag_Pos) /*!< FIFO empty flag.  */
#define SPDIF_AEMPTY_flag_Pos  (25U)
#define SPDIF_AEMPTY_flag_Msk  (0x1UL << SPDIF_AEMPTY_flag_Pos) /*!< FIFO almost empty flag. */
#define SPDIF_FULL_flag_Pos    (26U)
#define SPDIF_FULL_flag_Msk    (0x1UL << SPDIF_FULL_flag_Pos) /*!< FIFO full flag. When the FIFO is full this bit is set to '1' and when FIFO full condition disappears it's cleared. */
#define SPDIF_AFULL_flag_Pos   (27U)
#define SPDIF_AFULL_flag_Msk   (0x1UL << SPDIF_AFULL_flag_Pos) /*!< FIFO almost full flag. */
#define SPDIF_SYNCERR_flag_Pos (28U)
#define SPDIF_SYNCERR_flag_Msk (0x1UL << SPDIF_SYNCERR_flag_Pos) /*!< When '1', it indicates receiver synchronization error and when synchronization error condition disappears it's cleared. */
/*!< When '1', it indicates that receiver has become synchronized with input data stream (i.e. it is in lock condition) and when synchronization is lost it's cleared. */
#define SPDIF_LOCK_flag_Pos (29U)
#define SPDIF_LOCK_flag_Msk (0x1UL << SPDIF_LOCK_flag_Pos)
/*!< When '1', it indicates that receiver has become synchronized with input data stream (i.e. it is in lock condition) and when synchronization is lost it's cleared. */
#define SPDIF_BEGIN_flag_Pos (30U)
#define SPDIF_BEGIN_flag_Msk (0x1UL << SPDIF_BEGIN_flag_Pos)
/*!< When '1', it indicates start of a new block in received data. It is set to '1' when sub-frame with preamble 'B' has been received and written into FIFO and it's cleared when next sub-frame has been received. */
#define SPDIF_RIGHT_LEFT_Pos (31U)
#define SPDIF_RIGHT_LEFT_Msk (0x1UL << SPDIF_RIGHT_LEFT_Pos)

//offsetaddress : 0x0080
#define SPDIF_FIFO_DATA_Pos (0U)
#define SPDIF_FIFO_DATA_Msk (0xFFFFFFFFUL << SPDIF_FIFO_DATA_Pos);

/******************************** SPDIF ******************************/
typedef struct {
    volatile uint32_t SPDIF_CTRL;         /* offset 0x00 */
    volatile uint32_t SPDIF_INT_REG;      /* offset 0x04 */
    volatile uint32_t SPDIF_FIFO_CTRL;    /* offset 0x08 */
    volatile uint32_t SPDIF_STAT_REG;     /* offset 0x0c */
    volatile uint32_t SPDIF_USER_DATA_L0; /* offset 0x10 */
    volatile uint32_t SPDIF_USER_DATA_L1; /* offset 0x14 */
    volatile uint32_t SPDIF_USER_DATA_L2; /* offset 0x18 */
    volatile uint32_t SPDIF_USER_DATA_L3; /* offset 0x1C */
    volatile uint32_t SPDIF_USER_DATA_L4; /* offset 0x20 */
    volatile uint32_t SPDIF_USER_DATA_L5; /* offset 0x24 */
    volatile uint32_t SPDIF_USER_DATA_H0; /* offset 0x28 */
    volatile uint32_t SPDIF_USER_DATA_H1; /* offset 0x2C */
    volatile uint32_t SPDIF_USER_DATA_H2; /* offset 0x30 */
    volatile uint32_t SPDIF_USER_DATA_H3; /* offset 0x34 */
    volatile uint32_t SPDIF_USER_DATA_H4; /* offset 0x38 */
    volatile uint32_t SPDIF_USER_DATA_H5; /* offset 0x3C */
    volatile uint32_t SPDIF_CHN_STAT_L0;  /* offset 0x40 */
    volatile uint32_t SPDIF_CHN_STAT_L1;  /* offset 0x44 */
    volatile uint32_t SPDIF_CHN_STAT_L2;  /* offset 0x48 */
    volatile uint32_t SPDIF_CHN_STAT_L3;  /* offset 0x4C */
    volatile uint32_t SPDIF_CHN_STAT_L4;  /* offset 0x50 */
    volatile uint32_t SPDIF_CHN_STAT_L5;  /* offset 0x54 */
    volatile uint32_t SPDIF_CHN_STAT_R0;  /* offset 0x58 */
    volatile uint32_t SPDIF_CHN_STAT_R1;  /* offset 0x5C */
    volatile uint32_t SPDIF_CHN_STAT_R2;  /* offset 0x60 */
    volatile uint32_t SPDIF_CHN_STAT_R3;  /* offset 0x64 */
    volatile uint32_t SPDIF_CHN_STAT_R4;  /* offset 0x68 */
    volatile uint32_t SPDIF_CHN_STAT_R5;  /* offset 0x6C */
    volatile uint32_t rev_0[(0x80 - 0x6C) / 4 - 1];
    volatile uint32_t SPDIF_FIFO_REG; /* offset 0x80 */
} spdif_reg_t;

#ifdef __cplusplus
}
#endif

#endif

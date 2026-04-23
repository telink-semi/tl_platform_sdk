/*******************************************************************************************************
 *
 * @file    pdm.h
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
#ifndef __PDM_H__
#define __PDM_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// PDM_CFG offsetaddress : 0x0000
// PDM_CFG RegResetValue : 0x00000050
#define PDM_STEREO_POS    (0U)
#define PDM_STEREO_MSK    (0x1UL << PDM_STEREO_POS) /*!< */
#define PDM_STEREO        PDM_STEREO_MSK
#define PDM_SMPLEDGE_POS  (1U)
#define PDM_SMPLEDGE_MSK  (0x1UL << PDM_SMPLEDGE_POS) /*!< */
#define PDM_SMPLEDGE      PDM_SMPLEDGE_MSK
#define PDM_PCMWD_POS     (2U)
#define PDM_PCMWD_MSK     (0x1UL << PDM_PCMWD_POS) /*!< */
#define PDM_PCMWD         PDM_PCMWD_MSK
#define PDM_STOREMODE_POS (3U)
#define PDM_STOREMODE_MSK (0x1UL << PDM_STOREMODE_POS) /*!< */
#define PDM_STOREMODE     PDM_STOREMODE_MSK
#define PDM_HPF_FC_POS    (4U)
#define PDM_HPF_FC_MSK    (0x7UL << PDM_HPF_FC_POS) /*!< */
#define PDM_HPF_FC        PDM_HPF_FC_MSK
#define PDM_HPF_EN_POS    (7U)
#define PDM_HPF_EN_MSK    (0x1UL << PDM_HPF_EN_POS) /*!< */
#define PDM_HPF_EN        PDM_HPF_EN_MSK

// PDM_ENABLE offsetaddress : 0x0004
// PDM_ENABLE RegResetValue : 0x00000000
#define PDM_PDMEN_POS (0U)
#define PDM_PDMEN_MSK (0x1UL << PDM_PDMEN_POS) /*!< PDMEN*/
#define PDM_PDMEN     PDM_PDMEN_MSK

// PDM_FIFO_CFG offsetaddress : 0x0008
// PDM_FIFO_CFG RegResetValue : 0x00000000
#define PDM_INTEN_POS   (0U)
#define PDM_INTEN_MSK   (0x1UL << PDM_INTEN_POS) /*!< */
#define PDM_INTEN       PDM_INTEN_MSK
#define PDM_DMAEN_POS   (1U)
#define PDM_DMAEN_MSK   (0x1UL << PDM_DMAEN_POS) /*!< */
#define PDM_DMAEN       PDM_DMAEN_MSK
#define PDM_TRIGLVL_POS (4U)
#define PDM_TRIGLVL_MSK (0xfUL << PDM_TRIGLVL_POS) /*!< */
#define PDM_TRIGLVL     PDM_TRIGLVL_MSK

// PDM_FIFO_INTEN offsetaddress : 0x000C
// PDM_FIFO_INTEN RegResetValue : 0x00000000
#define PDM_FIFOTRIG_POS  (0U)
#define PDM_FIFOTRIG_MSK  (0x1UL << PDM_FIFOTRIG_POS) /*!< */
#define PDM_FIFOTRIG      PDM_FIFOTRIG_MSK
#define PDM_OVERFLOW_POS  (1U)
#define PDM_OVERFLOW_MSK  (0x1UL << PDM_OVERFLOW_POS) /*!< */
#define PDM_OVERFLOW      PDM_OVERFLOW_MSK
#define PDM_UNDERFLOW_POS (2U)
#define PDM_UNDERFLOW_MSK (0x1UL << PDM_UNDERFLOW_POS) /*!< */
#define PDM_UNDERFLOW     PDM_UNDERFLOW_MSK

// PDM_FIFO_STAT offsetaddress : 0x0010
// PDM_FIFO_STAT RegResetValue : 0x00000010
#define PDM_STAT_FIFOTRIG_POS  (0U)
#define PDM_STAT_FIFOTRIG_MSK  (0x1UL << PDM_STAT_FIFOTRIG_POS) /*!< */
#define PDM_STAT_FIFOTRIG      PDM_STAT_FIFOTRIG_MSK
#define PDM_STAT_OVERFLOW_POS  (1U)
#define PDM_STAT_OVERFLOW_MSK  (0x1UL << PDM_STAT_OVERFLOW_POS) /*!< */
#define PDM_STAT_OVERFLOW      PDM_STAT_OVERFLOW_MSK
#define PDM_STAT_UNDERFLOW_POS (2U)
#define PDM_STAT_UNDERFLOW_MSK (0x1UL << PDM_STAT_UNDERFLOW_POS) /*!< */
#define PDM_STAT_UNDERFLOW     PDM_STAT_UNDERFLOW_MSK
#define PDM_STAT_FULL_POS      (3U)
#define PDM_STAT_FULL_MSK      (0x1UL << PDM_STAT_FULL_POS) /*!< */
#define PDM_STAT_FULL          PDM_STAT_FULL_MSK
#define PDM_STAT_EMPTY_POS     (4U)
#define PDM_STAT_EMPTY_MSK     (0x1UL << PDM_STAT_EMPTY_POS) /*!< */
#define PDM_STAT_EMPTY         PDM_STAT_EMPTY_MSK

// PDM_FIFO_RD offsetaddress : 0x0014
// PDM_FIFO_RD RegResetValue : 0x00000000
#define PDM_DATA_POS (0U)
#define PDM_DATA_MSK (0xffffffffUL << PDM_DATA_POS) /*!< */
#define PDM_DATA     PDM_DATA_MSK

// PDM_FIFO_LVL offsetaddress : 0x0018
// PDM_FIFO_LVL RegResetValue : 0x00000000
#define PDM_FIFOLVL_POS (0U)
#define PDM_FIFOLVL_MSK (0x1fUL << PDM_FIFOLVL_POS) /*!< */
#define PDM_FIFOLVL     PDM_FIFOLVL_MSK

typedef struct {
    volatile uint32_t PDM_CFG;        // offsetaddress : 0x0000
    volatile uint32_t PDM_ENABLE;     // offsetaddress : 0x0004
    volatile uint32_t PDM_FIFO_CFG;   // offsetaddress : 0x0008
    volatile uint32_t PDM_FIFO_INTEN; // offsetaddress : 0x000C
    volatile uint32_t PDM_FIFO_STAT;  // offsetaddress : 0x0010
    volatile uint32_t PDM_FIFO_RD;    // offsetaddress : 0x0014
    volatile uint32_t PDM_FIFO_LVL;   // offsetaddress : 0x0018
} pdm_reg_t;
#ifdef __cplusplus
}
#endif
#endif
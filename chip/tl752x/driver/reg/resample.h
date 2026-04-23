/*******************************************************************************************************
 *
 * @file    resample.h
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
#ifndef __RESAMPLE_H__
#define __RESAMPLE_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++  */
#endif       /* _cplusplus  */

#include "tl_chip.h"

//CHx_RESAMPLE_POP_DATA offsetaddress : 0x0000
#define RESAMPLE_POP_DATA_Pos (0U)
#define RESAMPLE_POP_DATA_Msk (0xffffffffUL << RESAMPLE_POP_DATA_Pos) /*!< chx_pop_data */

//CHx_RESAMPLE_PUSH_DATA offsetaddress : 0x0004
#define RESAMPLE_PUSH_DATA_Pos (0U)
#define RESAMPLE_PUSH_DATA_Msk (0xffffffffUL << RESAMPLE_PUSH_DATA_Pos) /*!< chx_push_data */

//CHx_BASE_ADDR offsetaddress : 0x0018
#define RESAMPLE_ADDR_Pos (0U)
#define RESAMPLE_ADDR_Msk (0xffffUL << RESAMPLE_ADDR_Pos) /*!< chx_addr */

//CHx_RESAMPLE_CTL offsetaddress : 0x001C
#define RESAMPLE_ENABLE_Pos            (0U)
#define RESAMPLE_ENABLE_Msk            (0x1UL << RESAMPLE_ENABLE_Pos) /*!< chx_enable */
#define RESAMPLE_RAM_DATA_SEL_Pos      (1U)
#define RESAMPLE_RAM_DATA_SEL_Msk      (0x1UL << RESAMPLE_RAM_DATA_SEL_Pos) /*!< chx_ram_data_sel 0:ram_data1 :1 ram_data2*/
#define RESAMPLE_RESAMPLE_FUNC_SEL_Pos (2U)
#define RESAMPLE_RESAMPLE_FUNC_SEL_Msk (0x1UL << RESAMPLE_RESAMPLE_FUNC_SEL_Pos) /*!< chx_resample_func_sel direct:0 interpolate:1 */
#define RESAMPLE_RESAMPLE_STYLE_Pos    (3U)
#define RESAMPLE_RESAMPLE_STYLE_Msk    (0x1UL << RESAMPLE_RESAMPLE_STYLE_Pos) /*!< chx_resample_style down:0 up:1 */
#define RESAMPLE_READY_COEF_Pos        (4U)
#define RESAMPLE_READY_COEF_Msk        (0x1UL << RESAMPLE_READY_COEF_Pos) /*!< chx_ready_coef */
#define RESAMPLE_READY_DATA_Pos        (5U)
#define RESAMPLE_READY_DATA_Msk        (0x1UL << RESAMPLE_READY_DATA_Pos) /*!< chx_ready_data */
#define RESAMPLE_CHANNEL_INDEX_Pos     (6U)
#define RESAMPLE_CHANNEL_INDEX_Msk     (0xfUL << RESAMPLE_CHANNEL_INDEX_Pos) /*!< channel_index */
#define RESAMPLE_CHANNEL_FLUSH_Pos     (10U)
#define RESAMPLE_CHANNEL_FLUSH_Msk     (0x1UL << RESAMPLE_CHANNEL_FLUSH_Pos) /*!< channel_flush */

//CHx_RESAMPLE_IN_LEN offsetaddress : 0x0020
#define RESAMPLE_IN_LEN_Pos (0U)
#define RESAMPLE_IN_LEN_Msk (0xffffUL << RESAMPLE_IN_LEN_Pos) /*!< chx_in_len */

//CHx_RESAMPLE_OUT_LEN offsetaddress : 0x0024
#define RESAMPLE_OUT_LEN_Pos (0U)
#define RESAMPLE_OUT_LEN_Msk (0xffffUL << RESAMPLE_OUT_LEN_Pos) /*!< chx_out_len */

//CHx_RESAMPLE_FILT_LEN offsetaddress : 0x0028
#define RESAMPLE_FILT_LEN_Pos (0U)
#define RESAMPLE_FILT_LEN_Msk (0xffffUL << RESAMPLE_FILT_LEN_Pos) /*!< chx_filt_len */

//CHx_RESAMPLE_INT_ADVANCE offsetaddress : 0x002C
#define RESAMPLE_INT_ADVANCE_Pos (0U)
#define RESAMPLE_INT_ADVANCE_Msk (0xffffUL << RESAMPLE_INT_ADVANCE_Pos) /*!< chx_int_advance */

//CHx_RESAMPLE_FRAC_ADVANCE offsetaddress : 0x0030
#define RESAMPLE_FRAC_ADVANCE_Pos (0U)
#define RESAMPLE_FRAC_ADVANCE_Msk (0xffffUL << RESAMPLE_FRAC_ADVANCE_Pos) /*!< chx_frac_advance */

//CHx_RESAMPLE_DEN_RATE offsetaddress : 0x0034
#define RESAMPLE_DEN_RATE_Pos (0U)
#define RESAMPLE_DEN_RATE_Msk (0xffffffffUL << RESAMPLE_DEN_RATE_Pos) /*!< chx_den_rate */

//CHx_RESAMPLE_OVERSAMPLE offsetaddress : 0x0038
#define RESAMPLE_OVERSAMPLE_Pos (0U)
#define RESAMPLE_OVERSAMPLE_Msk (0xffffUL << RESAMPLE_OVERSAMPLE_Pos) /*!< chx_oversample */

//CHx_RESAMPLE_SAMP_FRAC_NUM offsetaddress : 0x003C
#define RESAMPLE_SAMP_FRAC_NUM_Pos (0U)
#define RESAMPLE_SAMP_FRAC_NUM_Msk (0xffffffffUL << RESAMPLE_SAMP_FRAC_NUM_Pos) /*!< chx_samp_frac_num default:0 */

//CHx_RESAMPLE_LAST_SAMPLE offsetaddress : 0x0040
#define RESAMPLE_LAST_SAMPLE_Pos (0U)
#define RESAMPLE_LAST_SAMPLE_Msk (0xffffUL << RESAMPLE_LAST_SAMPLE_Pos) /*!< chx_last_sample default:0 */

//CHx_RESAMPLE_OUT_SAMPLE offsetaddress : 0x0044
#define RESAMPLE_OUT_SAMPLE_Pos (0U)
#define RESAMPLE_OUT_SAMPLE_Msk (0xffffUL << RESAMPLE_OUT_SAMPLE_Pos) /*!< chx_out_sample */

//RESAMPLE_DMA_RXCTL offsetaddress : 0x0748
#define RESAMPLE_DMA_RXLVL_Pos        (0U)
#define RESAMPLE_DMA_RXLVL_Msk        (0x7fUL << RESAMPLE_DMA_RXLVL_Pos) /*!< dma_rxlvl */
#define RESAMPLE_DMA_RXFLUSH_Pos      (7U)
#define RESAMPLE_DMA_RXFLUSH_Msk      (0x1UL << RESAMPLE_DMA_RXFLUSH_Pos) /*!< dma_rxflush */
#define RESAMPLE_DMA_RX_EN_Pos        (8U)
#define RESAMPLE_DMA_RX_EN_Msk        (0x1UL << RESAMPLE_DMA_RX_EN_Pos) /*!< dma_rx_en */
#define RESAMPLE_DMA_RXFULL_Pos       (9U)
#define RESAMPLE_DMA_RXFULL_Msk       (0x1UL << RESAMPLE_DMA_RXFULL_Pos) /*!< dma_rxfull */
#define RESAMPLE_DMA_RXAFULL_Pos      (10U)
#define RESAMPLE_DMA_RXAFULL_Msk      (0x1UL << RESAMPLE_DMA_RXAFULL_Pos) /*!< dma_rxafull */
#define RESAMPLE_DMA_RXEMPTY_Pos      (11U)
#define RESAMPLE_DMA_RXEMPTY_Msk      (0x1UL << RESAMPLE_DMA_RXEMPTY_Pos) /*!< dma_rxempty */
#define RESAMPLE_DMA_RXAEMPTY_Pos     (12U)
#define RESAMPLE_DMA_RXAEMPTY_Msk     (0x1UL << RESAMPLE_DMA_RXAEMPTY_Pos) /*!< dma_rxaempty */
#define RESAMPLE_DMA_RXLVL_TRING_Pos  (13U)
#define RESAMPLE_DMA_RXLVL_TRING_Msk  (0x1UL << RESAMPLE_DMA_RXLVL_TRING_Pos) /*!< dma_rxlvl_tring */
#define RESAMPLE_DMA_RXDATA_READY_Pos (14U)
#define RESAMPLE_DMA_RXDATA_READY_Msk (0x1UL << RESAMPLE_DMA_RXDATA_READY_Pos) /*!< dma_rxdata_ready */
#define RESAMPLE_DMA_RXUNDERFLOW_Pos  (15U)
#define RESAMPLE_DMA_RXUNDERFLOW_Msk  (0x1UL << RESAMPLE_DMA_RXUNDERFLOW_Pos) /*!< dma_rxunderflow */
#define RESAMPLE_DMA_RXOVERFLOW_Pos   (16U)
#define RESAMPLE_DMA_RXOVERFLOW_Msk   (0x1UL << RESAMPLE_DMA_RXOVERFLOW_Pos) /*!< dma_rxoverflow */
#define RESAMPLE_DMA_RX_CNT_Pos       (17U)
#define RESAMPLE_DMA_RX_CNT_Msk       (0x7fUL << RESAMPLE_DMA_RX_CNT_Pos) /*!< dma_rx_cnt */

//RESAMPLE_DMA_TXCTL offsetaddress : 0x074C
#define RESAMPLE_DMA_TXLVL_Pos        (0U)
#define RESAMPLE_DMA_TXLVL_Msk        (0x7fUL << RESAMPLE_DMA_TXLVL_Pos) /*!< dma_txlvl */
#define RESAMPLE_DMA_TXFLUSH_Pos      (7U)
#define RESAMPLE_DMA_TXFLUSH_Msk      (0x1UL << RESAMPLE_DMA_TXFLUSH_Pos) /*!< dma_txflush */
#define RESAMPLE_DMA_TX_EN_Pos        (8U)
#define RESAMPLE_DMA_TX_EN_Msk        (0x1UL << RESAMPLE_DMA_TX_EN_Pos) /*!< dma_tx_en */
#define RESAMPLE_DMA_TXFULL_Pos       (9U)
#define RESAMPLE_DMA_TXFULL_Msk       (0x1UL << RESAMPLE_DMA_TXFULL_Pos) /*!< dma_txfull */
#define RESAMPLE_DMA_TXAFULL_Pos      (10U)
#define RESAMPLE_DMA_TXAFULL_Msk      (0x1UL << RESAMPLE_DMA_TXAFULL_Pos) /*!< dma_txafull */
#define RESAMPLE_DMA_TXEMPTY_Pos      (11U)
#define RESAMPLE_DMA_TXEMPTY_Msk      (0x1UL << RESAMPLE_DMA_TXEMPTY_Pos) /*!< dma_txempty */
#define RESAMPLE_DMA_TXAEMPTY_Pos     (12U)
#define RESAMPLE_DMA_TXAEMPTY_Msk     (0x1UL << RESAMPLE_DMA_TXAEMPTY_Pos) /*!< dma_txaempty */
#define RESAMPLE_DMA_TXLVL_TRING_Pos  (13U)
#define RESAMPLE_DMA_TXLVL_TRING_Msk  (0x1UL << RESAMPLE_DMA_TXLVL_TRING_Pos) /*!< dma_txlvl_tring */
#define RESAMPLE_DMA_TXDATA_READY_Pos (14U)
#define RESAMPLE_DMA_TXDATA_READY_Msk (0x1UL << RESAMPLE_DMA_TXDATA_READY_Pos) /*!< dma_txdata_ready */
#define RESAMPLE_DMA_TXUNDERFLOW_Pos  (15U)
#define RESAMPLE_DMA_TXUNDERFLOW_Msk  (0x1UL << RESAMPLE_DMA_TXUNDERFLOW_Pos) /*!< dma_txunderflow */
#define RESAMPLE_DMA_TXOVERFLOW_Pos   (16U)
#define RESAMPLE_DMA_TXOVERFLOW_Msk   (0x1UL << RESAMPLE_DMA_TXOVERFLOW_Pos) /*!< dma_txoverflow */
#define RESAMPLE_DMA_TX_CNT_Pos       (17U)
#define RESAMPLE_DMA_TX_CNT_Msk       (0x7fUL << RESAMPLE_DMA_TX_CNT_Pos) /*!< dma_tx_cnt */

//RESAMPLE_CTL offsetaddress : 0x0750
#define RESAMPLE_PCLK_MCLK_SEL_Pos      (0U)
#define RESAMPLE_PCLK_MCLK_SEL_Msk      (0x1UL << RESAMPLE_PCLK_MCLK_SEL_Pos) /*!< pclk_mclk_sel pclk:1 mclk:0 */
#define RESAMPLE_PCLK_MCLK_SEL_AUTO_Pos (1U)
#define RESAMPLE_PCLK_MCLK_SEL_AUTO_Msk (0x1UL << RESAMPLE_PCLK_MCLK_SEL_AUTO_Pos) /*!< pclk_mclk_sel_auto disable:0 enable:1 */
#define RESAMPLE_RAM_CLK_EN_Pos         (2U)
#define RESAMPLE_RAM_CLK_EN_Msk         (0x1UL << RESAMPLE_RAM_CLK_EN_Pos) /*!< ram_clk_en disable:0 enable:1 */
#define RESAMPLE_CHANNEL_MODE_Pos       (3U)
#define RESAMPLE_CHANNEL_MODE_Msk       (0x1UL << RESAMPLE_CHANNEL_MODE_Pos) /*!< channel_mode */
#define RESAMPLE_CHANNEL_MODE2_Pos      (4U)
#define RESAMPLE_CHANNEL_MODE2_Msk      (0x3UL << RESAMPLE_CHANNEL_MODE2_Pos)

//RESAMPLE_VER offsetaddress : 0x0754
#define RESAMPLE_RESAMPLE_VERSION_Pos (0U)
#define RESAMPLE_RESAMPLE_VERSION_Msk (0xffffffffUL << RESAMPLE_RESAMPLE_VERSION_Pos)

//DMA_INTERRUPT_INT_RAW offsetaddress : 0x0F00
#define RESAMPLE_DMA_RXFULL_RAW_Pos       (0U)
#define RESAMPLE_DMA_RXFULL_RAW_Msk       (0x1UL << RESAMPLE_DMA_RXFULL_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXAFULL_RAW_Pos      (1U)
#define RESAMPLE_DMA_RXAFULL_RAW_Msk      (0x1UL << RESAMPLE_DMA_RXAFULL_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXEMPTY_RAW_Pos      (2U)
#define RESAMPLE_DMA_RXEMPTY_RAW_Msk      (0x1UL << RESAMPLE_DMA_RXEMPTY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXAEMPTY_RAW_Pos     (3U)
#define RESAMPLE_DMA_RXAEMPTY_RAW_Msk     (0x1UL << RESAMPLE_DMA_RXAEMPTY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXLVL_TRING_RAW_Pos  (4U)
#define RESAMPLE_DMA_RXLVL_TRING_RAW_Msk  (0x1UL << RESAMPLE_DMA_RXLVL_TRING_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXDATA_READY_RAW_Pos (5U)
#define RESAMPLE_DMA_RXDATA_READY_RAW_Msk (0x1UL << RESAMPLE_DMA_RXDATA_READY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXUNDERFLOW_RAW_Pos  (6U)
#define RESAMPLE_DMA_RXUNDERFLOW_RAW_Msk  (0x1UL << RESAMPLE_DMA_RXUNDERFLOW_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_RXOVERFLOW_RAW_Pos   (7U)
#define RESAMPLE_DMA_RXOVERFLOW_RAW_Msk   (0x1UL << RESAMPLE_DMA_RXOVERFLOW_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXFULL_RAW_Pos       (8U)
#define RESAMPLE_DMA_TXFULL_RAW_Msk       (0x1UL << RESAMPLE_DMA_TXFULL_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXAFULL_RAW_Pos      (9U)
#define RESAMPLE_DMA_TXAFULL_RAW_Msk      (0x1UL << RESAMPLE_DMA_TXAFULL_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXEMPTY_RAW_Pos      (10U)
#define RESAMPLE_DMA_TXEMPTY_RAW_Msk      (0x1UL << RESAMPLE_DMA_TXEMPTY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXAEMPTY_RAW_Pos     (11U)
#define RESAMPLE_DMA_TXAEMPTY_RAW_Msk     (0x1UL << RESAMPLE_DMA_TXAEMPTY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXLVL_TRING_RAW_Pos  (12U)
#define RESAMPLE_DMA_TXLVL_TRING_RAW_Msk  (0x1UL << RESAMPLE_DMA_TXLVL_TRING_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXDATA_READY_RAW_Pos (13U)
#define RESAMPLE_DMA_TXDATA_READY_RAW_Msk (0x1UL << RESAMPLE_DMA_TXDATA_READY_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXUNDERFLOW_RAW_Pos  (14U)
#define RESAMPLE_DMA_TXUNDERFLOW_RAW_Msk  (0x1UL << RESAMPLE_DMA_TXUNDERFLOW_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_DMA_TXOVERFLOW_RAW_Pos   (15U)
#define RESAMPLE_DMA_TXOVERFLOW_RAW_Msk   (0x1UL << RESAMPLE_DMA_TXOVERFLOW_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_CHANNEL_ERR_RAW_Pos      (16U)
#define RESAMPLE_CHANNEL_ERR_RAW_Msk      (0x1UL << RESAMPLE_CHANNEL_ERR_RAW_Pos) /*!< raw, default 0 */
#define RESAMPLE_FINISHED_RAW_Pos         (17U)
#define RESAMPLE_FINISHED_RAW_Msk         (0x1UL << RESAMPLE_FINISHED_RAW_Pos) /*!< raw, default 0 */

//DMA_INTERRUPT_INT_FORCE offsetaddress : 0x0F04
#define RESAMPLE_DMA_RXFULL_RAW_Pos       (0U)
#define RESAMPLE_DMA_RXFULL_RAW_Msk       (0x1UL << RESAMPLE_DMA_RXFULL_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXAFULL_RAW_Pos      (1U)
#define RESAMPLE_DMA_RXAFULL_RAW_Msk      (0x1UL << RESAMPLE_DMA_RXAFULL_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXEMPTY_RAW_Pos      (2U)
#define RESAMPLE_DMA_RXEMPTY_RAW_Msk      (0x1UL << RESAMPLE_DMA_RXEMPTY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXAEMPTY_RAW_Pos     (3U)
#define RESAMPLE_DMA_RXAEMPTY_RAW_Msk     (0x1UL << RESAMPLE_DMA_RXAEMPTY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXLVL_TRING_RAW_Pos  (4U)
#define RESAMPLE_DMA_RXLVL_TRING_RAW_Msk  (0x1UL << RESAMPLE_DMA_RXLVL_TRING_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXDATA_READY_RAW_Pos (5U)
#define RESAMPLE_DMA_RXDATA_READY_RAW_Msk (0x1UL << RESAMPLE_DMA_RXDATA_READY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXUNDERFLOW_RAW_Pos  (6U)
#define RESAMPLE_DMA_RXUNDERFLOW_RAW_Msk  (0x1UL << RESAMPLE_DMA_RXUNDERFLOW_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_RXOVERFLOW_RAW_Pos   (7U)
#define RESAMPLE_DMA_RXOVERFLOW_RAW_Msk   (0x1UL << RESAMPLE_DMA_RXOVERFLOW_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXFULL_RAW_Pos       (8U)
#define RESAMPLE_DMA_TXFULL_RAW_Msk       (0x1UL << RESAMPLE_DMA_TXFULL_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXAFULL_RAW_Pos      (9U)
#define RESAMPLE_DMA_TXAFULL_RAW_Msk      (0x1UL << RESAMPLE_DMA_TXAFULL_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXEMPTY_RAW_Pos      (10U)
#define RESAMPLE_DMA_TXEMPTY_RAW_Msk      (0x1UL << RESAMPLE_DMA_TXEMPTY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXAEMPTY_RAW_Pos     (11U)
#define RESAMPLE_DMA_TXAEMPTY_RAW_Msk     (0x1UL << RESAMPLE_DMA_TXAEMPTY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXLVL_TRING_RAW_Pos  (12U)
#define RESAMPLE_DMA_TXLVL_TRING_RAW_Msk  (0x1UL << RESAMPLE_DMA_TXLVL_TRING_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXDATA_READY_RAW_Pos (13U)
#define RESAMPLE_DMA_TXDATA_READY_RAW_Msk (0x1UL << RESAMPLE_DMA_TXDATA_READY_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXUNDERFLOW_RAW_Pos  (14U)
#define RESAMPLE_DMA_TXUNDERFLOW_RAW_Msk  (0x1UL << RESAMPLE_DMA_TXUNDERFLOW_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_DMA_TXOVERFLOW_RAW_Pos   (15U)
#define RESAMPLE_DMA_TXOVERFLOW_RAW_Msk   (0x1UL << RESAMPLE_DMA_TXOVERFLOW_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_CHANNEL_ERR_RAW_Pos      (16U)
#define RESAMPLE_CHANNEL_ERR_RAW_Msk      (0x1UL << RESAMPLE_CHANNEL_ERR_RAW_Pos) /*!< force, write 1 set, debug use */
#define RESAMPLE_FINISHED_RAW_Pos         (17U)
#define RESAMPLE_FINISHED_RAW_Msk         (0x1UL << RESAMPLE_FINISHED_RAW_Pos) /*!< force, write 1 set, debug use */

//DMA_INTERRUPT_INT_MASK offsetaddress : 0x0F08
#define RESAMPLE_DMA_RXFULL_MASK_Pos       (0U)
#define RESAMPLE_DMA_RXFULL_MASK_Msk       (0x1UL << RESAMPLE_DMA_RXFULL_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXAFULL_MASK_Pos      (1U)
#define RESAMPLE_DMA_RXAFULL_MASK_Msk      (0x1UL << RESAMPLE_DMA_RXAFULL_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXEMPTY_MASK_Pos      (2U)
#define RESAMPLE_DMA_RXEMPTY_MASK_Msk      (0x1UL << RESAMPLE_DMA_RXEMPTY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXAEMPTY_MASK_Pos     (3U)
#define RESAMPLE_DMA_RXAEMPTY_MASK_Msk     (0x1UL << RESAMPLE_DMA_RXAEMPTY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXLVL_TRING_MASK_Pos  (4U)
#define RESAMPLE_DMA_RXLVL_TRING_MASK_Msk  (0x1UL << RESAMPLE_DMA_RXLVL_TRING_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXDATA_READY_MASK_Pos (5U)
#define RESAMPLE_DMA_RXDATA_READY_MASK_Msk (0x1UL << RESAMPLE_DMA_RXDATA_READY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXUNDERFLOW_MASK_Pos  (6U)
#define RESAMPLE_DMA_RXUNDERFLOW_MASK_Msk  (0x1UL << RESAMPLE_DMA_RXUNDERFLOW_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_RXOVERFLOW_MASK_Pos   (7U)
#define RESAMPLE_DMA_RXOVERFLOW_MASK_Msk   (0x1UL << RESAMPLE_DMA_RXOVERFLOW_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXFULL_MASK_Pos       (8U)
#define RESAMPLE_DMA_TXFULL_MASK_Msk       (0x1UL << RESAMPLE_DMA_TXFULL_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXAFULL_MASK_Pos      (9U)
#define RESAMPLE_DMA_TXAFULL_MASK_Msk      (0x1UL << RESAMPLE_DMA_TXAFULL_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXEMPTY_MASK_Pos      (10U)
#define RESAMPLE_DMA_TXEMPTY_MASK_Msk      (0x1UL << RESAMPLE_DMA_TXEMPTY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXAEMPTY_MASK_Pos     (11U)
#define RESAMPLE_DMA_TXAEMPTY_MASK_Msk     (0x1UL << RESAMPLE_DMA_TXAEMPTY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXLVL_TRING_MASK_Pos  (12U)
#define RESAMPLE_DMA_TXLVL_TRING_MASK_Msk  (0x1UL << RESAMPLE_DMA_TXLVL_TRING_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXDATA_READY_MASK_Pos (13U)
#define RESAMPLE_DMA_TXDATA_READY_MASK_Msk (0x1UL << RESAMPLE_DMA_TXDATA_READY_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXUNDERFLOW_MASK_Pos  (14U)
#define RESAMPLE_DMA_TXUNDERFLOW_MASK_Msk  (0x1UL << RESAMPLE_DMA_TXUNDERFLOW_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_DMA_TXOVERFLOW_MASK_Pos   (15U)
#define RESAMPLE_DMA_TXOVERFLOW_MASK_Msk   (0x1UL << RESAMPLE_DMA_TXOVERFLOW_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_CHANNEL_ERR_MASK_Pos      (16U)
#define RESAMPLE_CHANNEL_ERR_MASK_Msk      (0x1UL << RESAMPLE_CHANNEL_ERR_MASK_Pos) /*!< mask, default 1, int off */
#define RESAMPLE_FINISHED_MASK_Pos         (17U)
#define RESAMPLE_FINISHED_MASK_Msk         (0x1UL << RESAMPLE_FINISHED_MASK_Pos) /*!< mask, default 1, int off */

//DMA_INTERRUPT_INT_STATUS offsetaddress : 0x0F0C
#define RESAMPLE_DMA_RXFULL_STATUS_Pos       (0U)
#define RESAMPLE_DMA_RXFULL_STATUS_Msk       (0x1UL << RESAMPLE_DMA_RXFULL_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXAFULL_STATUS_Pos      (1U)
#define RESAMPLE_DMA_RXAFULL_STATUS_Msk      (0x1UL << RESAMPLE_DMA_RXAFULL_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXEMPTY_STATUS_Pos      (2U)
#define RESAMPLE_DMA_RXEMPTY_STATUS_Msk      (0x1UL << RESAMPLE_DMA_RXEMPTY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXAEMPTY_STATUS_Pos     (3U)
#define RESAMPLE_DMA_RXAEMPTY_STATUS_Msk     (0x1UL << RESAMPLE_DMA_RXAEMPTY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXLVL_TRING_STATUS_Pos  (4U)
#define RESAMPLE_DMA_RXLVL_TRING_STATUS_Msk  (0x1UL << RESAMPLE_DMA_RXLVL_TRING_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXDATA_READY_STATUS_Pos (5U)
#define RESAMPLE_DMA_RXDATA_READY_STATUS_Msk (0x1UL << RESAMPLE_DMA_RXDATA_READY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXUNDERFLOW_STATUS_Pos  (6U)
#define RESAMPLE_DMA_RXUNDERFLOW_STATUS_Msk  (0x1UL << RESAMPLE_DMA_RXUNDERFLOW_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_RXOVERFLOW_STATUS_Pos   (7U)
#define RESAMPLE_DMA_RXOVERFLOW_STATUS_Msk   (0x1UL << RESAMPLE_DMA_RXOVERFLOW_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXFULL_STATUS_Pos       (8U)
#define RESAMPLE_DMA_TXFULL_STATUS_Msk       (0x1UL << RESAMPLE_DMA_TXFULL_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXAFULL_STATUS_Pos      (9U)
#define RESAMPLE_DMA_TXAFULL_STATUS_Msk      (0x1UL << RESAMPLE_DMA_TXAFULL_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXEMPTY_STATUS_Pos      (10U)
#define RESAMPLE_DMA_TXEMPTY_STATUS_Msk      (0x1UL << RESAMPLE_DMA_TXEMPTY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXAEMPTY_STATUS_Pos     (11U)
#define RESAMPLE_DMA_TXAEMPTY_STATUS_Msk     (0x1UL << RESAMPLE_DMA_TXAEMPTY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXLVL_TRING_STATUS_Pos  (12U)
#define RESAMPLE_DMA_TXLVL_TRING_STATUS_Msk  (0x1UL << RESAMPLE_DMA_TXLVL_TRING_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXDATA_READY_STATUS_Pos (13U)
#define RESAMPLE_DMA_TXDATA_READY_STATUS_Msk (0x1UL << RESAMPLE_DMA_TXDATA_READY_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_DMA_TXUNDERFLOW_STATUS_Pos  (14U)
#define RESAMPLE_DMA_TXUNDERFLOW_STATUS_Msk  (0x1UL << RESAMPLE_DMA_TXUNDERFLOW_STATUS_Pos) /*!< stauts default 0  */
#define RESAMPLE_DMA_TXOVERFLOW_STATUS_Pos   (15U)
#define RESAMPLE_DMA_TXOVERFLOW_STATUS_Msk   (0x1UL << RESAMPLE_DMA_TXOVERFLOW_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_CHANNEL_ERR_STATUS_Pos      (16U)
#define RESAMPLE_CHANNEL_ERR_STATUS_Msk      (0x1UL << RESAMPLE_CHANNEL_ERR_STATUS_Pos) /*!< stauts default 0 */
#define RESAMPLE_FINISHED_STATUS_Pos         (17U)
#define RESAMPLE_FINISHED_STATUS_Msk         (0x1UL << RESAMPLE_FINISHED_STATUS_Pos) /*!< stauts default 0 */

typedef struct {
    DRV_IOM uint32_t RESAMPLE_DMA_RXCTL; //offsetaddress : 0x0748
    DRV_IOM uint32_t RESAMPLE_DMA_TXCTL; //offsetaddress : 0x074C
    DRV_IOM uint32_t RESAMPLE_CTL;       //offsetaddress : 0x0750
    DRV_IOM uint32_t RESAMPLE_VER;       //offsetaddress : 0x0754
    DRV_IOM uint32_t rev_0[(0x0F00 - 0x0754) / 4 - 1];
    DRV_IOM uint32_t DMA_INTERRUPT_INT_RAW;    //offsetaddress : 0x0F00
    DRV_IOM uint32_t DMA_INTERRUPT_INT_FORCE;  //offsetaddress : 0x0F04
    DRV_IOM uint32_t DMA_INTERRUPT_INT_MASK;   //offsetaddress : 0x0F08
    DRV_IOM uint32_t DMA_INTERRUPT_INT_STATUS; //offsetaddress : 0x0F0C
} rsm_t;

typedef struct {
    DRV_IOM uint32_t RESAMPLE_POP_DATA;  //offsetaddress : 0x0000
    DRV_IOM uint32_t RESAMPLE_PUSH_DATA; //offsetaddress : 0x0004
    DRV_IOM uint32_t rev_0[(0x0018 - 0x0004) / 4 - 1];
    DRV_IOM uint32_t BASE_ADDR;              //offsetaddress : 0x0018
    DRV_IOM uint32_t RESAMPLE_CTL;           //offsetaddress : 0x001C
    DRV_IOM uint32_t RESAMPLE_IN_LEN;        //offsetaddress : 0x0020
    DRV_IOM uint32_t RESAMPLE_OUT_LEN;       //offsetaddress : 0x0024
    DRV_IOM uint32_t RESAMPLE_FILT_LEN;      //offsetaddress : 0x0028
    DRV_IOM uint32_t RESAMPLE_INT_ADVANCE;   //offsetaddress : 0x002C
    DRV_IOM uint32_t RESAMPLE_FRAC_ADVANCE;  //offsetaddress : 0x0030
    DRV_IOM uint32_t RESAMPLE_DEN_RATE;      //offsetaddress : 0x0034
    DRV_IOM uint32_t RESAMPLE_OVERSAMPLE;    //offsetaddress : 0x0038
    DRV_IOM uint32_t RESAMPLE_SAMP_FRAC_NUM; //offsetaddress : 0x003C
    DRV_IOM uint32_t RESAMPLE_LAST_SAMPLE;   //offsetaddress : 0x0040
    DRV_IOM uint32_t RESAMPLE_OUT_SAMPLE;    //offsetaddress : 0x0044
} rsm_channel_t;

#ifdef __cplusplus
}
#endif

#endif
/********************************************************************************************************
 * @file    audio_reg.h
 *
 * @brief   This is the header file for tl753x
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef AUDIO_REG_H
#define AUDIO_REG_H
#include "soc.h"

#define REG_AUDIO_FIFO0             0x120000
#define REG_AUDIO_FIFO1             0x120040
#define REG_AUDIO_FIFO2             0x120080
#define REG_AUDIO_FIFO3             0x1200c0
#define REG_AUDIO_FIFO_ADDR(i)      (REG_AUDIO_FIFO0 + 0x40 * (i))

#define REG_HAC_FIFO0               0x130000
#define REG_HAC_FIFO1               0x130004
#define REG_HAC_FIFO2               0x130008
#define REG_HAC_FIFO3               0x13000c
#define REG_HAC_FIFO_ADDR(i)        (REG_HAC_FIFO0 + 4 * (i))

#define REG_AUDIO_I2S0_TDM_BASE     0x148000
#define REG_AUDIO_I2S1_BASE         0x148020
#define REG_AUDIO_I2S2_BASE         0x148040
#define REG_AUDIO_I2S_ADDR(i)       (REG_AUDIO_I2S0_TDM_BASE + 0x20 * (i))

#define REG_AUDIO_SPDIF_BASE        0x148060

#define REG_AUDIO_HAC_BASE          0x1480a0

#define REG_AUDIO_MATRIX_BASE       0x148480

#define REG_AUDIO_ANC0_COEF         0x149000
#define REG_AUDIO_ANC_COEF(i)       (REG_AUDIO_ANC0_COEF + 0 * (i))

#define REG_AUDIO_ANC0_BASE         0x14c100
#define REG_AUDIO_ANC_BASE(i)       (REG_AUDIO_ANC0_BASE + 0 * (i))

#define REG_AUDIO_BZ_BASE           0x14de00

#define REG_AUDIO_CODEC_CTRL_BASE   0x14e640

#define REG_AUDIO_CLK_IRQ_CTRL_BASE 0x14e6c0

#define REG_AUDIO_CODEC0_BASE       0x14e700
#define REG_AUDIO_ASRC_COFF_BASE    0x14e800

#define REG_AUDIO_DMA_BASE          0x14ead0

/**************************************************** I2S register *****************************************************************/
#define reg_audio_i2s_cfg1(i2s) REG_ADDR8(REG_AUDIO_I2S_ADDR(i2s)) /* i2s[0-2] */

enum
{
    FLD_I2S_CLK_EN     = BIT(2),
    FLD_I2S_CLK_DIV2   = BIT(3),
    FLD_I2S_BCLK_INV_O = BIT(4),
    FLD_I2S_ADC_DCI_MS = BIT(5),
    FLD_I2S_DAC_DCI_MS = BIT(6),
};

#define reg_audio_i2s_cfg2(i2s) REG_ADDR8(REG_AUDIO_I2S_ADDR(i2s) + 0x01) /* i2s[0-2] */

enum
{
    FLD_I2S_ADC_MBCLK_LOOP = BIT(0),
    FLD_I2S_DAC_MBCLK_LOOP = BIT(1),
    FLD_I2S_FRM_INV        = BIT(2),
    FLD_I2S_Wl             = BIT_RNG(3, 4),
    FLD_I2S_FORMAT         = BIT_RNG(5, 7),                               /**< i2s1/i2s2 bit[5-6] */
};

#define reg_audio_i2s_cfg3(i2s) REG_ADDR8(REG_AUDIO_I2S_ADDR(i2s) + 0x02) /* i2s[0-2] */

enum
{
    FLD_I2S_LR_SWAP     = BIT(0),
    FLD_I2S_RX_2LINE_EN = BIT(1),
    FLD_I2S_TX_2LINE_EN = BIT(2),
    FLD_I2S_DAC_FRM_EN  = BIT(3),
    FLD_I2S_ADC_FRM_EN  = BIT(4),
    FLD_I2S_TX_DAT_SEL  = BIT(5),
    FLD_I2S_LRP         = BIT(6),
};

#define reg_audio_i2s_route(i2s) REG_ADDR8(REG_AUDIO_I2S_ADDR(i2s) + 0x03) /* i2s[0-2] */

enum
{
    FLD_I2S_MODE         = BIT_RNG(0, 1),
    FLD_I2S_PAD_BCLK_SEL = BIT(2),
    FLD_I2S_REC_BIT_SEL  = BIT(3),
    FLD_I2S_SCHEDULE_EN  = BIT(4),
};

#define reg_audio_i2s_int_pcm_num(i2s) REG_ADDR16(REG_AUDIO_I2S_ADDR(i2s) + 0x04) /* i2s[0-2] */

enum
{
    FLD_I2S_INT_PCM_NUM = BIT_RNG(0, 12),
};

#define reg_audio_i2s_dec_pcm_num(i2s) REG_ADDR16(REG_AUDIO_I2S_ADDR(i2s) + 0x06) /* i2s[0-2] */

enum
{
    FLD_I2S_DEC_PCM_NUM = BIT_RNG(0, 12),
};

#define reg_audio_i2s_pcm_clk_num(i2s) REG_ADDR8(REG_AUDIO_I2S_ADDR(i2s) + 0x08) /* i2s[0-2] */

#define reg_audio_i2s0_dac_tune        REG_ADDR8(REG_AUDIO_I2S0_TDM_BASE + 0x09)

enum
{
    FLD_I2S_DAC_TUNE_L1 = BIT_RNG(0, 3),
    FLD_I2S_DAC_TUNE_L2 = BIT_RNG(4, 7),
};

#define reg_audio_i2s0_adc_tune REG_ADDR8(REG_AUDIO_I2S0_TDM_BASE + 0x0a)

enum
{
    FLD_I2S_ADC_TUNE_L1 = BIT_RNG(0, 3),
    FLD_I2S_ADC_TUNE_L2 = BIT_RNG(4, 7),
};

#define reg_audio_i2s0_fifo_cfg REG_ADDR8(REG_AUDIO_I2S0_TDM_BASE + 0x0b)

enum
{
    FLD_I2S_TX_FIFO_LESS_L1 = BIT(0),
    FLD_I2S_TX_FIFO_LESS_L2 = BIT(1),
    FLD_I2S_TX_FIFO_MORE_L1 = BIT(2),
    FLD_I2S_TX_FIFO_MORE_L2 = BIT(3),
    FLD_I2S_RX_FIFO_LESS_L1 = BIT(4),
    FLD_I2S_RX_FIFO_LESS_L2 = BIT(5),
    FLD_I2S_RX_FIFO_MORE_L1 = BIT(6),
    FLD_I2S_RX_FIFO_MORE_L2 = BIT(7),
};

#define reg_audio_i2s_stimer_target(i2s) REG_ADDR32(REG_AUDIO_I2S_ADDR(i2s) + 0x0c) /* i2s[0-2] */

#define reg_audio_i2s0_align_cfg         REG_ADDR8(REG_AUDIO_I2S0_TDM_BASE + 0x10)

enum
{
    FLD_I2S_ALIGN_EN   = BIT(0),
    FLD_I2S_ALIGN_CTRL = BIT_RNG(1, 3),
    FLD_I2S_ALIGN_MASK = BIT(4),
    FLD_I2S_CLK_SEL    = BIT(5),
};

#define reg_audio_i2s0_tdm_cfg REG_ADDR8(REG_AUDIO_I2S0_TDM_BASE + 0x11)

enum
{
    FLD_I2S_TDM_RX_CH_NUM = BIT_RNG(0, 1),
    FLD_I2S_TDM_TX_CH_NUM = BIT_RNG(2, 3),
    FLD_I2S_TDM_MODE      = BIT_RNG(4, 5),
    FLD_I2S_TDM_SLOT      = BIT_RNG(6, 7),
};

#define reg_audio_i2s0_timer_th REG_ADDR32(REG_AUDIO_I2S0_TDM_BASE + 0x14)

/**************************************************** SPDIF register *****************************************************************/
#define reg_audio_spdif_fs_192_min1  REG_ADDR8(REG_AUDIO_SPDIF_BASE)
#define reg_audio_spdif_fs_192_min2  REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x01)
#define reg_audio_spdif_fs_192_min3  REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x02)

#define reg_audio_spdif_fs_192_max1  REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x03)
#define reg_audio_spdif_fs_192_max2  REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x04)
#define reg_audio_spdif_fs_192_max3  REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x05)

#define reg_audio_spdif_fs_96_min1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x06)
#define reg_audio_spdif_fs_96_min2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x07)
#define reg_audio_spdif_fs_96_min3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x08)

#define reg_audio_spdif_fs_96_max1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x09)
#define reg_audio_spdif_fs_96_max2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0a)
#define reg_audio_spdif_fs_96_max3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0b)

#define reg_audio_spdif_fs_48_min1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0c)
#define reg_audio_spdif_fs_48_min2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0d)
#define reg_audio_spdif_fs_48_min3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0e)

#define reg_audio_spdif_fs_48_max1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x0f)
#define reg_audio_spdif_fs_48_max2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x10)
#define reg_audio_spdif_fs_48_max3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x11)

#define reg_audio_spdif_fs_44p1_min1 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x12)
#define reg_audio_spdif_fs_44p1_min2 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x13)
#define reg_audio_spdif_fs_44p1_min3 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x14)

#define reg_audio_spdif_fs_44p1_max1 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x15)
#define reg_audio_spdif_fs_44p1_max2 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x16)
#define reg_audio_spdif_fs_44p1_max3 REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x17)

#define reg_audio_spdif_fs_32_min1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x18)
#define reg_audio_spdif_fs_32_min2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x19)
#define reg_audio_spdif_fs_32_min3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1a)

#define reg_audio_spdif_fs_32_max1   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1b)
#define reg_audio_spdif_fs_32_max2   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1c)
#define reg_audio_spdif_fs_32_max3   REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1d)

#define reg_audio_spdif_config       REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1e)

enum
{
    FLD_SPDIF_ENCODER_EN      = BIT(0),
    FLD_SPDIF_DECODER_EN      = BIT(1),
    FLD_SPDIF_PARITY_SELECT   = BIT(2),
    FLD_SPDIF_PARITY_RESULT   = BIT(3),
    FLD_SPDIF_DBG_CLK_EN      = BIT(4),
    FLD_SPDIF_RX_FMT          = BIT(5),
    FLD_SPDIF_TX_FMT          = BIT(6),
    FLD_SPDIF_PREAMBLE_SELECT = BIT(7),
};

#define reg_audio_spdif_tx_div REG_ADDR8(REG_AUDIO_SPDIF_BASE + 0x1f)

enum
{
    FLD_SPDIF_TX_DIV_NUM     = BIT_RNG(0, 4),
    FLD_SPDIF_TX_DONE_MANUAL = BIT(5), //when preamble by hardware,tx done.
};

/**************************************************** HAC register *****************************************************************/
#define reg_audio_hac_eq_asrc_en REG_ADDR8(REG_AUDIO_HAC_BASE)

enum
{
    FLD_HAC_EQ0_EN = BIT(0),
    FLD_HAC_EQ1_EN = BIT(1),
    FLD_HAC_ASRC0_EN = BIT(2),
    FLD_HAC_ASRC1_EN = BIT(3),
    FLD_HAC_EQ2_EN = BIT(4),
};

#define reg_audio_hac_eq_config_en REG_ADDR8(REG_AUDIO_HAC_BASE + 0x01)

enum
{
    FLD_HAC_EQ0_CONFIG_EN = BIT(0),
    FLD_HAC_EQ1_CONFIG_EN = BIT(1),
    FLD_HAC_EQ2_CONFIG_EN = BIT(2),
};

#define reg_audio_hac_rx_afifo_int_status REG_ADDR8(REG_AUDIO_HAC_BASE + 0x02)

enum
{
    FLD_HAC_EQ0_RX_FIFO0_INT = BIT(0),
    FLD_HAC_EQ1_RX_FIFO1_INT = BIT(1),
    FLD_HAC_ASRC0_RX_FIFO2_INT = BIT(2),
    FLD_HAC_ASRC1_RX_FIFO3_INT = BIT(3),
    FLD_HAC_EQ2_RX_FIFO4_INT = BIT(4),
};

#define reg_audio_hac_asrc_tdm_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x03)

enum
{
    FLD_HAC_ASRC0_TDM_NUM = BIT_RNG(0, 1),
    FLD_HAC_ASRC1_TDM_NUM = BIT_RNG(4, 5),
};

#define reg_audio_hac_eq_asrc_input_num(hac) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x04 + ((hac) << 1)) /* hac[0-3] */
#define reg_audio_hac_eq0_input_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x04)
#define reg_audio_hac_eq1_input_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x06)
#define reg_audio_hac_asrc0_input_num(asrc) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x08)
#define reg_audio_hac_asrc1_input_num(asrc) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x0a)
#define reg_audio_hac_eq2_input_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x14)

#define reg_audio_hac_hit_input_num_irq_clear REG_ADDR8(REG_AUDIO_HAC_BASE + 0x16)
enum
{
    FLD_HAC_EQ0_HIT_INPUT_NUM_IRQ_CLEAR = BIT(0),
    FLD_HAC_EQ1_HIT_INPUT_NUM_IRQ_CLEAR = BIT(1),
    FLD_HAC_ASRC0_HIT_INPUT_NUM_IRQ_CLEAR = BIT(2),
    FLD_HAC_ASRC1_HIT_INPUT_NUM_IRQ_CLEAR = BIT(3),
    FLD_HAC_EQ2_HIT_INPUT_NUM_IRQ_CLEAR = BIT(4),
};

#define reg_audio_hac_hit_input_num_irq_en REG_ADDR8(REG_AUDIO_HAC_BASE + 0x17)
enum
{
    FLD_HAC_EQ0_HIT_INPUT_NUM_IRQ_EN = BIT(0),
    FLD_HAC_EQ1_HIT_INPUT_NUM_IRQ_EN = BIT(1),
    FLD_HAC_ASRC0_HIT_INPUT_NUM_IRQ_EN = BIT(2),
    FLD_HAC_ASRC1_HIT_INPUT_NUM_IRQ_EN = BIT(3),
    FLD_HAC_EQ2_HIT_INPUT_NUM_IRQ_EN = BIT(4),
};

#define reg_audio_hac_asrc_frac_adv(asrc) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x0c + ((asrc) << 2)) /* asrc[0-1] */
enum
{
    FLD_HAC_ASRC_FRAC_ADV = BIT_RNG(0, 25),
};

#define reg_audio_hac_asrc_den_rate(asrc) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x1c + ((asrc) << 2)) /* hac[2-3] */
enum
{
    FLD_HAC_ASRC_DEN_RATE = BIT_RNG(0, 25),
};

#define reg_audio_hac_eq_bq_b0(eq, bq) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x24 + (bq) * 0x14 + (eq) * 0xc8) /* hac[0-2] bq[0-9] */
#define reg_audio_hac_eq_bq_b1(eq, bq) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x28 + (bq) * 0x14 + (eq) * 0xc8) /* hac[0-2] bq[0-9] */
#define reg_audio_hac_eq_bq_b2(eq, bq) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x2c + (bq) * 0x14 + (eq) * 0xc8) /* hac[0-2] bq[0-9] */
#define reg_audio_hac_eq_bq_a1(eq, bq) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x30 + (bq) * 0x14 + (eq) * 0xc8) /* hac[0-2] bq[0-9] */
#define reg_audio_hac_eq_bq_a2(eq, bq) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x34 + (bq) * 0x14 + (eq) * 0xc8) /* hac[0-2] bq[0-9] */

#define reg_audio_hac_eq0_input_cnt REG_ADDR16(REG_AUDIO_HAC_BASE + 0x27c)
#define reg_audio_hac_eq1_input_cnt REG_ADDR16(REG_AUDIO_HAC_BASE + 0x27e)
#define reg_audio_hac_eq2_input_cnt REG_ADDR16(REG_AUDIO_HAC_BASE + 0x284)

#define reg_audio_hac_asrc_input_cnt(asrc) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x280 + ((asrc) << 1)) /* asrc[0-1] */

#define reg_audio_hac_hit_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x286)
enum
{
    FLD_HAC_EQ0_HIT_NUM   = BIT(0),
    FLD_HAC_EQ1_HIT_NUM   = BIT(1),
    FLD_HAC_ASRC0_HIT_NUM = BIT(2),
    FLD_HAC_ASRC1_HIT_NUM = BIT(3),
    FLD_HAC_EQ2_HIT_NUM   = BIT(4),
};

#define reg_audio_hac_ch_txfifo_clr    REG_ADDR8(REG_AUDIO_HAC_BASE + 0x288)
enum
{
    FLD_HAC_EQ0_TXFIFO_CLR = BIT(0),
    FLD_HAC_EQ1_TXFIFO_CLR = BIT(1),
    FLD_HAC_ASRC0_TXFIFO_CLR = BIT(2),
    FLD_HAC_ASRC1_TXFIFO_CLR = BIT(3),
    FLD_HAC_EQ2_TXFIFO_CLR = BIT(4),
};

#define reg_audio_hac_mux_sel REG_ADDR8(REG_AUDIO_HAC_BASE + 0x289)
enum
{
    FLD_HAC_EQ0_INPUT_ROUTE = BIT(0),
    FLD_HAC_EQ1_INPUT_ROUTE = BIT(1),
    FLD_HAC_ASRC0_INPUT_ROUTE = BIT(2),
    FLD_HAC_ASRC1_INPUT_ROUTE = BIT(3),
    FLD_HAC_EQ2_INPUT_ROUTE = BIT(4),
};

#define reg_audio_hac_input_afifo_clr REG_ADDR8(REG_AUDIO_HAC_BASE + 0x28a)
enum
{
    FLD_HAC_EQ0_INPUT_AFIFO_CLR = BIT(0),
    FLD_HAC_EQ1_INPUT_AFIFO_CLR = BIT(1),
    FLD_HAC_ASRC0_INPUT_AFIFO_CLR = BIT(2),
    FLD_HAC_ASRC1_INPUT_AFIFO_CLR = BIT(3),
    FLD_HAC_EQ2_INPUT_AFIFO_CLR = BIT(4),
};

#define reg_audio_hac_tx_fifo_overrun REG_ADDR8(REG_AUDIO_HAC_BASE + 0x28b)

enum
{
    FLD_HAC_EQ0_OUTPUT_FIFO_OVERRUN = BIT(0),
    FLD_HAC_EQ1_OUTPUT_FIFO_OVERRUN = BIT(1),
    FLD_HAC_ASRC0_OUTPUT_FIFO_OVERRUN = BIT(2),
    FLD_HAC_ASRC1_OUTPUT_FIFO_OVERRUN = BIT(3),
    FLD_HAC_EQ2_OUTPUT_FIFO_OVERRUN = BIT(4),
};

#define reg_audio_hac_eq01_input_afifo_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x28c)    /* EQ[0-1] */
enum
{
    FLD_HAC_EQ0_INPUT_AFIFO_NUM = BIT_RNG(0, 3),
    FLD_HAC_EQ1_INPUT_AFIFO_NUM = BIT_RNG(4, 7),
};

#define reg_audio_hac_eq2_input_afifo_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x28e) /* EQ[2] */
enum
{
    FLD_HAC_EQ2_INPUT_AFIFO_NUM = BIT_RNG(0, 3),
};

#define reg_audio_hac_asrc01_input_afifo_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x28d)  /* EQ[0-1] */
enum
{
    FLD_HAC_ASRC0_INPUT_AFIFO_NUM = BIT_RNG(0, 3),
    FLD_HAC_ASRC1_INPUT_AFIFO_NUM = BIT_RNG(4, 7),
};

#define reg_audio_hac_arb_fifo_clr REG_ADDR8(REG_AUDIO_HAC_BASE + 0X290)
enum
{
    FLD_HAC_ARB_FIFO_CLR = BIT(0),
};

#define reg_audio_hac_hmst_sel REG_ADDR8(REG_AUDIO_HAC_BASE + 0x291)
enum
{
    FLD_HAC_EQ0_HMST_SEL = BIT(0),
    FLD_HAC_EQ1_HMST_SEL = BIT(1),
    FLD_HAC_ASRC0_HMST_SEL = BIT(2),
    FLD_HAC_ASRC1_HMST_SEL = BIT(3),
    FLD_HAC_EQ2_HMST_SEL = BIT(4),
};

#define reg_audio_hac_haddr_set REG_ADDR8(REG_AUDIO_HAC_BASE + 0x292)
enum
{
    FLD_HAC_EQ0_HADDR_SET = BIT(0),
    FLD_HAC_EQ1_HADDR_SET = BIT(1),
    FLD_HAC_ASRC0_HADDR_SET = BIT(2),
    FLD_HAC_ASRC1_HADDR_SET = BIT(3),
    FLD_HAC_EQ2_HADDR_SET = BIT(4),
};

#define reg_audio_hac_ch_level   REG_ADDR8(REG_AUDIO_HAC_BASE + 0x293)
enum
{
    FLD_HAC_CH_LEVEL = BIT_RNG(0, 4),
};

#define reg_audio_hac_eq0_haddr REG_ADDR32(REG_AUDIO_HAC_BASE + 0x294) /* hac[0] */
#define reg_audio_hac_eq1_haddr REG_ADDR32(REG_AUDIO_HAC_BASE + 0x298) /* hac[1] */
#define reg_audio_hac_eq2_haddr REG_ADDR32(REG_AUDIO_HAC_BASE + 0x310) /* hac[2] */
#define reg_audio_hac_eq_asrc_output_addr(hac) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x294 + ((hac) << 2)) /* hac[0-3] */

#define reg_audio_hac_asrc0_haddr REG_ADDR32(REG_AUDIO_HAC_BASE + 0x29c) /* hac[2] */
#define reg_audio_hac_asrc1_haddr REG_ADDR32(REG_AUDIO_HAC_BASE + 0x2a0) /* hac[2] */


#define reg_audio_hac_hburst     REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a4)

enum
{
    FLD_HAC_HBURST   = BIT_RNG(0, 2),
    FLD_HAC_CROSS_1K = BIT(4),
};

#define reg_audio_hac_rx_fifo_clr REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a5)

enum
{
    FLD_HAC_EQ0_RXFIFO_CLR = BIT(0),
    FLD_HAC_EQ1_RXAFIFO_CLR = BIT(1),
    FLD_HAC_ASRC0_RXFIFO_CLR = BIT(2),
    FLD_HAC_ASRC1_RXFIFO_CLR = BIT(3),
    FLD_HAC_EQ2_RXFIFO_CLR = BIT(4),
};

#define reg_audio_hac_bypass_eq_asrc REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a6)

enum
{
    FLD_HAC_BYPASS_EQ0 = BIT(0),
    FLD_HAC_BYPASS_EQ1 = BIT(1),
    FLD_HAC_BYPASS_ASRC0 = BIT(2),
    FLD_HAC_BYPASS_ASRC1 = BIT(3),
    FLD_HAC_BYPASS_EQ2 = BIT(4),
};

#define reg_audio_hac_txafifo_num REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a7)

enum
{
    FLD_HAC_TX_AFIFO_NUM = BIT_RNG(0, 4),
};

#define reg_audio_hac_rxfifo_overrun REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a8)

enum
{
    FLD_HAC_EQ0_RXFIFO_OVERRUN = BIT(0),
    FLD_HAC_EQ1_RXFIFO_OVERRUN = BIT(1),
    FLD_HAC_ASRC0_RXFIFO_OVERRUN = BIT(2),
    FLD_HAC_ASRC1_RXFIFO_OVERRUN = BIT(3),
    FLD_HAC_EQ2_RXFIFO_OVERRUN = BIT(4),
};

#define reg_audio_hac_mtrx_in_fmt_sel REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2a9)

enum
{
    FLD_HAC_MTRX_IN_FMT_SEL0 = BIT(0),
    FLD_HAC_MTRX_IN_FMT_SEL1 = BIT(1),
    FLD_HAC_MTRX_IN_FMT_SEL2 = BIT(2),
    FLD_HAC_MTRX_IN_FMT_SEL3 = BIT(3),
    FLD_HAC_MTRX_IN_FMT_SEL4 = BIT(4),
};

#define reg_audio_hac_mtrx_out_fmt_sel_l REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2aa)

enum
{
    FLD_HAC_EQ0_MTRX_OUT_FMT_SEL0 = BIT_RNG(0, 1),
    FLD_HAC_EQ1_MTRX_OUT_FMT_SEL1 = BIT_RNG(2, 3),
    FLD_HAC_ASRC0_MTRX_OUT_FMT_SEL2 = BIT_RNG(4, 5),
    FLD_HAC_ASRC1_MTRX_OUT_FMT_SEL3 = BIT_RNG(6, 7),
};

#define reg_audio_hac_ahb_dat_sel REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2ab)

enum
{
    FLD_HAC_AHB_MST_OUTPUT_DAT_FORMAT_SEL = BIT_RNG(0, 1),
    FLD_HAC_AHB_SLV_INPUT_DAT_FORMAT_SEL = BIT(2),
    FLD_HAC_EQ2_MTRX_OUT_FMT_SEL3 = BIT_RNG(0, 1),
};

#define reg_audio_hac_txfifo_rd_num(hac) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2ac + ((hac) << 1)) /* hac[0-3] */

enum
{
    FLD_HAC_TXFIFO_RD_NUM = BIT_RNG(0, 11),
};

#define reg_audio_hac_asrc_interval REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2b4)

enum
{
    FLD_HAC_INTERVAL_ASRC0 = BIT_RNG(0, 1),
    FLD_HAC_INTERVAL_ASRC1 = BIT_RNG(2, 3),
};

#define reg_audio_hac_rxafifo_thres(hac) REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2b5 + ((hac) >> 1)) /* hac[0-4] */
enum
{
    FLD_HAC_RX_AFIFO0_THRES = BIT_RNG(0, 3),
    FLD_HAC_RX_AFIFO1_THRES = BIT_RNG(4, 7),
};

#define reg_audio_hac_int_en REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2ba)

enum
{
    FLD_HAC_INT_EN = BIT_RNG(0, 4),
};

#define reg_audio_tx_fifo_num(hac) REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2bc + (hac)) /* hac[0-4] */

enum
{
    FLD_HAC_TXFIFO_NUM = BIT_RNG(0, 4),                                          /**< hac0, hac1[0-4] */
};

#define reg_audio_hac_asrc_int_adv_latch(asrc) REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2c4 + (asrc)) /* hac[2-3] */

enum
{
    FLD_HAC_ASRC_INT_ADV_LATCH = BIT_RNG(0, 6),
};

#define reg_audio_hac_asrc_int_adv(asrc) REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2ca + (asrc)) /* hac[2-3] */

enum
{
    FLD_HAC_ASRC_INT_ADV = BIT_RNG(0, 6),
};

#define reg_audio_hac_asrc_1_rd_num(asrc) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2cc + ((asrc) << 1)) /* hac[2-3] */

enum
{
    FLD_HAC_RD_1_NUM = BIT_RNG(0, 11),
};

#define reg_audio_hac_eq_asrc_rd_num(hac) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2d0 +((hac) << 1) ) /* hac[0-3] */
#define reg_audio_hac_eq0_rd_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2d0 ) /*  eq0 */
#define reg_audio_hac_eq1_rd_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2d2 ) /*  eq1 */
#define reg_audio_hac_eq2_rd_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2dc ) /*  eq2 */
#define reg_audio_hac_asrc0_rd_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2d4) /* ASRC0 */
#define reg_audio_hac_asrc1_rd_num REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2d6) /* ASRC1 */

enum
{
    FLD_HAC_RD_NUM = BIT_RNG(0, 11),
};

#define reg_audio_hac_fifo_cnt_clr REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2d8)

enum
{
    FLD_HAC_FIFO0_CNT_CLR = BIT(0),
    FLD_HAC_FIFO1_CNT_CLR = BIT(1),
    FLD_HAC_FIFO2_CNT_CLR = BIT(2),
    FLD_HAC_FIFO3_CNT_CLR = BIT(3),
    FLD_HAC_FIFO4_CNT_CLR = BIT(4),
};

#define reg_audio_hac_asrc_lag_update REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2d9)

enum
{
    FLD_HAC_ASRC0_LAG_UPDATE = BIT(0),
    FLD_HAC_ASRC1_LAG_UPDATE = BIT(1),
};

#define reg_audio_hac_to_matrix_16bit_sel REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2da)

enum
{
    FLD_HAC_16BIT_SEL = BIT_RNG(0, 4),
    FLD_HAC_4CH_ASRC1_FIRST_EN = BIT(6),
    FLD_HAC_4CH_ASRC0_FIRST_EN = BIT(7),
};

#define reg_audio_hac_ahb_master_read_en REG_ADDR8(REG_AUDIO_HAC_BASE + 0x2db)
enum
{
    FLD_HAC_AHB_MASTER_READ_EN = BIT(0),
};


#define reg_audio_hac_eq2_timeout REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2de ) /* asrc[0-4] */
#define reg_audio_hac_eq0_timeout REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2e0 ) /* asrc[0-4] */
#define reg_audio_hac_eq1_timeout REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2e2 ) /* asrc[0-4] */
#define reg_audio_hac_asrc_timeout(asrc) REG_ADDR16(REG_AUDIO_HAC_BASE + 0x2e4 + ((asrc) << 1)) /* asrc[0-4] */
enum
{
    FLD_HAC_ASRC_TIMEOUT = BIT_RNG(0, 8),
};

#define reg_audio_hac_rx_fifo_cnt(hac) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x2e8 + ((hac) << 2)) /* hac[0-3] */


#define reg_audio_hac_tx_fifo_cnt_ind(hac) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x2f8 + ((hac) << 2)) /* hac[0-4] */
enum
{
    FLD_HAC_EQ_OR_ASRC_OUTPUT_CNT = BIT_RNG(0, 23),
    FLD_HAC_EQ_OR_ASRC_INDICATE = BIT(24),
};


#define reg_audio_hac_rx_fifo4_cnt(hac) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x30c ) /* hac[0-3] */
enum
{
    FLD_HAC_RX_FIFO_CNT = BIT_RNG(0, 23),
};

#define reg_audio_hac_ahb_wr_addr(hac) REG_ADDR32(REG_AUDIO_HAC_BASE + 0x314 + ((hac) << 2)) /* hac[0-4] */

#define reg_audio_hac_asrc_eq_ahb_wr_set REG_ADDR8(REG_AUDIO_HAC_BASE + 0x328)
enum
{
    FLD_HAC_EQ0_AHB_WR_SET = BIT(0),
    FLD_HAC_EQ1_AHB_WR_SET  = BIT(1),
    FLD_HAC_ASRC0_AHB_WR_SET  = BIT(2),
    FLD_HAC_ASRC1_AHB_WR_SET  = BIT(3),
    FLD_HAC_EQ2_AHB_WR_SET  = BIT(4),
};

#define reg_audio_hac_aasrc_eq_done_irq_en REG_ADDR8(REG_AUDIO_HAC_BASE + 0x329)
enum
{
    FLD_HAC_EQ0_IRQ_EN = BIT(0),
    FLD_HAC_EQ1_IRQ_EN = BIT(1),
    FLD_HAC_ASRC0_IRQ_EN = BIT(2),
    FLD_HAC_ASRC1_IRQ_EN = BIT(3),
    FLD_HAC_EQ2_IRQ_EN = BIT(4),
};

#define reg_audio_hac_txfifo_empty REG_ADDR8(REG_AUDIO_HAC_BASE + 0x32a)
enum
{
    FLD_HAC_HAC0_TXFIFO_EMPTY  = BIT(0),
    FLD_HAC_HAC1_TXFIFO_EMPTY  = BIT(1),
    FLD_HAC_HAC2_TXFIFO_EMPTY  = BIT(2),
    FLD_HAC_HAC3_TXFIFO_EMPTY  = BIT(3),
    FLD_HAC_HAC4_TXFIFO_EMPTY  = BIT(4),
};

/**************************************************** MATRIX register *****************************************************************/
#define reg_audio_matrix_srst REG_ADDR8(REG_AUDIO_MATRIX_BASE)

enum
{
    FLD_MATRIX_I2S0_RX_SRST = BIT(0),
    FLD_MATRIX_I2S1_RX_SRST = BIT(1),
    FLD_MATRIX_I2S2_RX_SRST = BIT(2),
    FLD_MATRIX_ANC0_RX_SRST = BIT(3),
    FLD_MATRIX_ADC0_RX_SRST = BIT(4),
    FLD_MATRIX_ADC1_RX_SRST = BIT(5),
    FLD_MATRIX_ADC2_RX_SRST = BIT(6),
    FLD_MATRIX_I2S0_TX_SRST = BIT(7),
};

#define reg_audio_matrix_srst2 REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x01)

enum
{
    FLD_MATRIX_I2S1_TX_SRST  = BIT(0),
    FLD_MATRIX_I2S2_TX_SRST  = BIT(1),
    FLD_MATRIX_DAC1_SRST     = BIT(2),
    FLD_MATRIX_SDTN_SRC_SRST = BIT(3),
    FLD_MATRIX_DMIC0_RX_SRST = BIT(4),
    FLD_MATRIX_DMIC1_RX_SRST = BIT(5),
    FLD_MATRIX_DMIC2_RX_SRST = BIT(6),
    /* RVSD */
};

#define reg_audio_matrix_i2s0_rx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x02)

enum
{
    FLD_MATRIX_I2S0_RX_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_i2s0_ch01_tx_sel    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x03)
#define reg_audio_matrix_i2s0_ch23_tx_sel    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x04)
#define reg_audio_matrix_i2s0_ch45_tx_sel    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x05)
#define reg_audio_matrix_i2s0_ch67_tx_sel    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x06)
#define reg_audio_matrix_i2s0_ch_tx_sel(chn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x03 + (chn >> 1)) /* i2s0_chn[0-7] */

enum
{
    FLD_MATRIX_I2S0_EVEN_TX_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_I2S0_ODD_TX_SEL  = BIT_RNG(4, 7),
};

#define reg_audio_matrix_i2s0_tx_dma_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x07)

enum
{
    FLD_MATRIX_I2S0_TX_DMA_SEL = BIT_RNG(0, 5),
};

#define reg_audio_matrix_i2s1_tx_dma_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x08)

enum
{
    FLD_MATRIX_I2S1_TX_DMA_SEL = BIT_RNG(0, 4),
    FLD_MATRIX_I2S1_RX_SEL = BIT_RNG(5, 7),
};

#define reg_audio_matrix_i2s2_tx_dma_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x09)

enum
{
    FLD_MATRIX_I2S2_TX_DMA_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_i2s1_ch01_tx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0a)

enum
{
    FLD_MATRIX_I2S1_CH0_TX_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_I2S1_CH1_TX_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_dmic384ll_192ll_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0b)

enum
{
    FLD_MATRIX_DMIC384LL_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_DMIC192LL_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_i2s2_rx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0c)

enum
{
    FLD_MATRIX_I2S2_RX_SEL = BIT_RNG(0, 3),
};

#define reg_audio_matrix_i2s2_ch01_tx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0d)

enum
{
    FLD_MATRIX_I2S2_CH0_TX_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_I2S2_CH1_TX_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_anc0_rx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0e)

enum
{
    FLD_MATRIX_ANC0_RX_SEL    = BIT_RNG(0, 1),
    FLD_MATRIX_ANC0_RX_V2_SEL = BIT_RNG(4, 5),
};

#define reg_audio_matrix_dmic384_192_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x0f)

enum
{
    FLD_MATRIX_DMIC384_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_DMIC192_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_anc0_src_dma_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x10)

enum
{
    FLD_MATRIX_ANC0_SRC_DMA_SEL = BIT_RNG(0, 3),
};

#define reg_audio_matrix_anc1_src_dma_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x11)

enum
{
    FLD_MATRIX_DAC_DMA_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_adc768_384_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x12)

enum
{
    FLD_MATRIX_ADC768_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_ADC384_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_adc192_96_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x13)

enum
{
    FLD_MATRIX_ADC192_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_ADC96_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_adc48_dmic768_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x14)

enum
{
    FLD_MATRIX_ADC48_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_DMIC768_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_dac_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x15)

enum
{
    FLD_MATRIX_DAC_L_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_DAC_R_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_tx_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x16)

enum
{
    FLD_MATRIX_SPDIF_TX_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_USB_TX_SEL   = BIT_RNG(4, 7),
};

#define reg_audio_matrix_dmic96_32_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x17)

enum
{
    FLD_MATRIX_DMIC96_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_DMIC32_SEL = BIT_RNG(4, 7),
};

#define reg_audio_matrix_hac0_tx_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x18)
#define reg_audio_matrix_hac1_tx_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x19)
#define reg_audio_matrix_hac2_tx_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1a)
#define reg_audio_matrix_hac3_tx_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1b)
#define reg_audio_matrix_hac4_tx_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1c)
#define reg_audio_matrix_hac_tx_sel(hac) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x18 + (hac)) /* hac[0-4] */

enum
{
    FLD_MATRIX_HAC_TX_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_dmic16k48k_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1d)

enum
{
    FLD_MATRIX_DMIC16K48K_SEL = BIT_RNG(0, 3),
};

#define reg_audio_matrix_anc0_src0_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1e)

enum
{
    FLD_MATRIX_ANC0_SRC0_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_anc0_ref0_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x1f)

enum
{
    FLD_MATRIX_ANC0_REF0_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_anc0_err0_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x20)

enum
{
    FLD_MATRIX_ANC0_ERR0_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_anc0_bz_ref0_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x21)
#define reg_audio_matrix_anc0_bz_ref1_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x22)
#define reg_audio_matrix_anc0_bz_ref2_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x23)
#define reg_audio_matrix_anc0_bz_ref_sel(ref)     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x21 + (ref)) /* ref[0-2] */
enum
{
    FLD_MATRIX_ANC0_BZ_REF_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_fifo0_wr_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x24)
#define reg_audio_matrix_fifo1_wr_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x25)
#define reg_audio_matrix_fifo2_wr_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x26)
#define reg_audio_matrix_fifo3_wr_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x27)
#define reg_audio_matrix_fifo_wr_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x24 + (fifo)) /* fifo[0-3] */

enum
{
    FLD_MATRIX_FIFO_WR_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_i2s0_rx_hac01_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x28)
#define reg_audio_matrix_i2s0_rx_hac23_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x29)
#define reg_audio_matrix_i2s1_rx_hac01_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2f)
#define reg_audio_matrix_i2s1_rx_hac23_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x30)
#define reg_audio_matrix_i2s2_rx_hac01_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x36)
#define reg_audio_matrix_i2s2_rx_hac23_sel        REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x37)
#define reg_audio_matrix_i2s_rx_hac_sel(i2s, hac) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x28 + (i2s) * 7 + ((hac) >> 1)) /* i2s[0-2] hac[0-3] */

enum
{
    FLD_MATRIX_I2S_RX_HAC_EVEN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_I2S_RX_HAC_ODD_SEL  = BIT_RNG(4, 6),
};

#define reg_audio_matrix_i2s0_tx_hac2_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2a)
#define reg_audio_matrix_i2s0_tx_hac3_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2b)
#define reg_audio_matrix_i2s1_tx_hac2_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x31)
#define reg_audio_matrix_i2s1_tx_hac3_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x32)
#define reg_audio_matrix_i2s2_tx_hac2_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x38)
#define reg_audio_matrix_i2s2_tx_hac3_sel         REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x39)
#define reg_audio_matrix_i2s_tx_hac_sel(i2s, hac) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2a + (i2s) * 7 + ((hac) % 2)) /* i2s[0-2] hac[2-3] */

enum
{
    FLD_MATRIX_I2S_TX_HAC_EVEN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_I2S_TX_HAC_ODD_SEL  = BIT_RNG(4, 6),
};

#define reg_audio_matrix_i2s0_rx_anc_sel_0     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2c)
#define reg_audio_matrix_i2s1_rx_anc_sel_0     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x33)
#define reg_audio_matrix_i2s2_rx_anc_sel_0     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x3a)
#define reg_audio_matrix_i2s_rx_anc_sel_0(i2s) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2c + (i2s) * 7) /* i2s[0-2] */

enum
{
    FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_I2S_RX_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_i2s0_rx_anc_sel_1     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2d)
#define reg_audio_matrix_i2s1_rx_anc_sel_1     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x34)
#define reg_audio_matrix_i2s2_rx_anc_sel_1     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x3b)
#define reg_audio_matrix_i2s_rx_anc_sel_1(i2s) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x2d + (i2s) * 7) /* i2s[0-2] */

enum
{
    FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};


#define reg_audio_matrix_anc0_bz_err0_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x3c)
#define reg_audio_matrix_anc0_bz_err1_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x3d)
#define reg_audio_matrix_anc0_bz_err_sel(bz)     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x3c + (bz-3)) /* bz[3-4] */
enum
{
    FLD_MATRIX_ANC0_BZ_ERR_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_adc_rx_anc_sel_0     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x41)

enum
{
    FLD_MATRIX_ADC96_RX_ANC0_SRC0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC768_RX_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc_rx_anc_sel_1     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x42)

enum
{
    FLD_MATRIX_ADC768_RX_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_adc_rx_anc_sel_2     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x48)

enum
{
    FLD_MATRIX_ADC48_RX_ANC0_SRC0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC384_RX_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc_rx_anc_sel_3     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x49)

enum
{
    FLD_MATRIX_ADC384_RX_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_sdtn0123_simple_ctrl    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x4c)

enum
{
    FLD_MATRIX_SDTN01_BY_ADC_VLD = BIT(0),
    FLD_MATRIX_SDTN0_EN_SIMPLE = BIT(1),
    FLD_MATRIX_SDTN1_EN_SIMPLE = BIT(2),
    FLD_MATRIX_SDTN23_BY_ADC_VLD = BIT(4),
    FLD_MATRIX_SDTN2_EN_SIMPLE = BIT(5),
    FLD_MATRIX_SDTN3_EN_SIMPLE = BIT(6),
};

#define reg_audio_matrix_sdtn4567_simple_ctrl    REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x4d)

enum
{
    FLD_MATRIX_SDTN45_BY_ADC_VLD = BIT(0),
    FLD_MATRIX_SDTN4_EN_SIMPLE = BIT(1),
    FLD_MATRIX_SDTN5_EN_SIMPLE = BIT(2),
    FLD_MATRIX_SDTN67_BY_ADC_VLD = BIT(4),
    FLD_MATRIX_SDTN6_EN_SIMPLE = BIT(5),
    FLD_MATRIX_SDTN7_EN_SIMPLE = BIT(6),
};

#define reg_audio_matrix_adc_rx_anc_sel_4     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x4f)

enum
{
    FLD_MATRIX_ADC192_RX_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc_rx_anc_sel_5     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x50)

enum
{
    FLD_MATRIX_ADC192_RX_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_sidetone_output_bit_sel     REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x51)

enum
{
    FLD_MATRIX_SIDETONE0_OUTPUT_BIT_SEL = BIT_RNG(0, 1),
    FLD_MATRIX_SIDETONE1_OUTPUT_BIT_SEL = BIT_RNG(2, 3),
    FLD_MATRIX_SIDETONE2_OUTPUT_BIT_SEL = BIT_RNG(4, 5),
    FLD_MATRIX_SIDETONE3_OUTPUT_BIT_SEL = BIT_RNG(6, 7),
};

#define reg_audio_matrix_sdtn0_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x52)
#define reg_audio_matrix_sdtn1_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x53)
#define reg_audio_matrix_sdtn2_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x54)
#define reg_audio_matrix_sdtn3_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x55)
#define reg_audio_matrix_sdtn4_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x56)
#define reg_audio_matrix_sdtn5_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x57)
#define reg_audio_matrix_sdtn6_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x58)
#define reg_audio_matrix_sdtn7_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x59)
#define reg_audio_matrix_sdtn_sel(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x52 + (sdtn)) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_SDTN_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_i2s_sdtn0_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x5a)
#define reg_audio_matrix_i2s_sdtn1_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x5d)
#define reg_audio_matrix_i2s_sdtn2_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x60)
#define reg_audio_matrix_i2s_sdtn3_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x63)
#define reg_audio_matrix_i2s_sdtn4_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x66)
#define reg_audio_matrix_i2s_sdtn5_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x69)
#define reg_audio_matrix_i2s_sdtn6_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x6c)
#define reg_audio_matrix_i2s_sdtn7_sel      REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x6f)
#define reg_audio_matrix_i2s_sdtn_sel(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x5a + (sdtn) * 3) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_I2S0_SDTN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_I2S1_SDTN_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_i2s_adc_sdtn_sel(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x5b + (sdtn) * 3) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_I2S2_SDTN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC0_SDTN_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc_sdtn_sel(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x5c + (sdtn) * 3) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_ADC1_SDTN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC2_SDTN_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_sdtn_en REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x74)

enum
{
    FLD_MATRIX_SDTN0_EN = BIT(0),
    FLD_MATRIX_SDTN1_EN = BIT(1),
    FLD_MATRIX_SDTN2_EN = BIT(2),
    FLD_MATRIX_SDTN3_EN = BIT(3),
    FLD_MATRIX_SDTN4_EN = BIT(4),
    FLD_MATRIX_SDTN5_EN = BIT(5),
    FLD_MATRIX_SDTN6_EN = BIT(6),
    FLD_MATRIX_SDTN7_EN = BIT(7),
};

#define reg_audio_matrix_sdtn_dma_mode REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x75)

enum
{
    FLD_MATRIX_SDTN01_DMA_MODE = BIT(0),
    FLD_MATRIX_SDTN23_DMA_MODE = BIT(1),
    FLD_MATRIX_SDTN45_DMA_MODE = BIT(2),
    FLD_MATRIX_SDTN67_DMA_MODE = BIT(3),
};

#define reg_audio_matrix_sdtn_gain_adc(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x76 + ((sdtn) >> 1)) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_SDTN_EVEN_ADC = BIT_RNG(0, 3),
    FLD_MATRIX_SDTN_ODD_ADC  = BIT_RNG(4, 7),
};

#define reg_audio_matrix_sdtn_gain_dac(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x7a + ((sdtn) >> 1)) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_SDTN_EVEN_DAC = BIT_RNG(0, 3),
    FLD_MATRIX_SDTN_ODD_DAC  = BIT_RNG(4, 7),
};

#define reg_audio_matrix_sdtn_req_count(sdtns) REG_ADDR16(REG_AUDIO_MATRIX_BASE + 0x80 + (sdtns << 1)) /* sdtns[0-3] */

enum
{
    FLD_MATRIX_SDTN_REQ_COUNT = BIT_RNG(0, 15)
};

#define reg_audio_matrix_hac01_tx_dma0_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x88)
#define reg_audio_matrix_hac01_tx_dma1_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8a)
#define reg_audio_matrix_hac01_tx_dma2_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8c)
#define reg_audio_matrix_hac01_tx_dma3_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8e)
#define reg_audio_matrix_hac01_tx_dma_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x88 + (((fifo) - 1) << 1)) /* fifo[1-4] */

enum
{
    FLD_MATRIX_HAC0_TX_DMA_SEL = BIT_RNG(0, 1),
    FLD_MATRIX_HAC1_TX_DMA_SEL = BIT_RNG(4, 5),
};

#define reg_audio_matrix_hac23_tx_dma0_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x89)
#define reg_audio_matrix_hac23_tx_dma1_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8b)
#define reg_audio_matrix_hac23_tx_dma2_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8d)
#define reg_audio_matrix_hac23_tx_dma3_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x8f)
#define reg_audio_matrix_hac23_tx_dma_sel(fifo) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x89 + (((fifo) - 1) << 1)) /* fifo[1-4] */

enum
{
    FLD_MATRIX_HAC2_TX_DMA_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_HAC3_TX_DMA_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_sdtn_dma_sel(sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x90 + ((sdtn) >> 1)) /* sdtn[0-7] */

enum
{
    FLD_MATRIX_SDTN_DMA_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_tx_chn_swap REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x94)

enum
{
    FLD_MATRIX_I2S0_TX_CHN_SWAP = BIT(0),
    FLD_MATRIX_I2S1_TX_CHN_SWAP = BIT(1),
    FLD_MATRIX_I2S2_TX_CHN_SWAP = BIT(2),
    FLD_MATRIX_DAC_TX_CHN_SWAP  = BIT(3),
};

#define reg_audio_matrix_fifo_rx_hac01_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x95)

enum
{
    FLD_MATRIX_FIFO_RX_HAC0_SEL = BIT_RNG(0, 1),
    FLD_MATRIX_FIFO_RX_HAC1_SEL = BIT_RNG(4, 5),
};

#define reg_audio_matrix_fifo_rx_hac23_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x96)

enum
{
    FLD_MATRIX_FIFO_RX_HAC2_SEL = BIT_RNG(0, 3),
    FLD_MATRIX_FIFO_RX_HAC3_SEL = BIT_RNG(4, 7),
};

#define reg_audio_hac_tdm_tx_dma_ch_num REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x97)

enum
{
    FLD_HAC_TDM_TX_DMA0_CH_NUM = BIT_RNG(0, 1),
    FLD_HAC_TDM_TX_DMA1_CH_NUM = BIT_RNG(2, 3),
    FLD_HAC_TDM_TX_DMA2_CH_NUM = BIT_RNG(4, 5),
    FLD_HAC_TDM_TX_DMA3_CH_NUM = BIT_RNG(6, 7),
};

#define reg_audio_matrix_anc0_ref1_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x98)

enum
{
    FLD_MATRIX_ANC0_REF1_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_anc0_ref2_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x99)

enum
{
    FLD_MATRIX_ANC0_REF2_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_anc0_err1_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x9a)

enum
{
    FLD_MATRIX_ANC0_ERR1_SEL = BIT_RNG(0, 4),
};

#define reg_audio_matrix_i2s0_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x9e)
#define reg_audio_matrix_i2s1_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xa2)
#define reg_audio_matrix_i2s2_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xa6)
#define reg_audio_matrix_i2s_anc0_ref_sel(i2s)  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x9e + ((i2s)<<2)) /* I2S[0-2]*/

enum
{
    FLD_MATRIX_I2S_ANC0_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_I2S_ANC0_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_i2s0_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x9f)
#define reg_audio_matrix_i2s1_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xa3)
#define reg_audio_matrix_i2s2_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xa7)
#define reg_audio_matrix_i2s_anc0_err_sel(i2s)  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x9f + ((i2s)<<2)) /* I2S[0-2]*/

enum
{
    FLD_MATRIX_I2S_ANC0_ERR1_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_adc0_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xaa)
#define reg_audio_matrix_adc1_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xae)
#define reg_audio_matrix_adc2_anc0_ref_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xb2)
#define reg_audio_matrix_adc_anc0_ref_sel(adc)  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xaa + ((adc)<<2)) /* I2S[0-2]*/

enum
{
    FLD_MATRIX_ADC_ANC0_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC_ANC0_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc0_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xab)
#define reg_audio_matrix_adc1_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xaf)
#define reg_audio_matrix_adc2_anc0_err_sel REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xb3)
#define reg_audio_matrix_adc_anc0_err_sel(adc)  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xaa + ((adc)<<2)) /* I2S[0-2]*/

enum
{
    FLD_MATRIX_ADC_ANC0_ERR1_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_dmic768_anc0_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xb8)

enum
{
    FLD_MATRIX_DMIC96_ANC0_SRC0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC768_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic768_anc0_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xb9)

enum
{
    FLD_MATRIX_DMIC768_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_dmic_anc0_ref_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xbb)

enum
{
    FLD_MATRIX_DMIC768_ANC0_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC768_ANC0_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic_anc0_err_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xbc)

enum
{
    FLD_MATRIX_DMIC768_ANC0_ERR1_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_hac4_tx_dma0_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xbf)

enum
{
    FLD_MATRIX_HAC4_TX_DMA0_SEL = BIT_RNG(0, 1),
    FLD_MATRIX_HAC4_TX_DMA1_SEL = BIT_RNG(4, 5),
};

#define reg_audio_matrix_dmic384ll_anc_sell  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xc2)

enum
{
    FLD_MATRIX_DMIC16K48K_ANC0_SRC_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384LL_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384ll_anc_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xc3)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_dmic384ll_anc0_ref_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xc5)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384LL_ANC0_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384ll_anc0_err_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xc6)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_ERR1_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_dmic192ll_rx_anc_sel_0  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xcb)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192ll_rx_anc_sel_1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xcc)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_ERR0_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_dmic192ll_anc0_ref_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xce)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192LL_ANC0_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192ll_anc0_err_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xcf)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_ERR1_SEL = BIT_RNG(0, 2),
};

#define reg_audio_matrix_hac4_tx_dma23_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xd2)

enum
{
    FLD_MATRIX_HAC4_TX_DMA2_SEL = BIT_RNG(0, 1),
    FLD_MATRIX_HAC4_TX_DMA3_SEL = BIT_RNG(4, 5),
};

#define reg_audio_matrix_hac4_rx_dma_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xd3)

enum
{
    FLD_MATRIX_HAC4_RX_DMA = BIT_RNG(0, 1),
};

#define reg_audio_matrix_adc_3to5_sdtn_sel(adc, sdtn)  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xd4 + (adc-3)*4 + ((sdtn)>>2)) /* adc[3-5] sdtn[0-7] */
#define reg_audio_matrix_adc_6to12_sdtn_sel(adc, sdtn) REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x104 + ((adc-6)>>1) + ((sdtn)<<2)) /* adc[6-12], sdtn[0-7]*/

enum
{
    FLD_MATRIX_ADC_SDTN_EVEN_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC_SDTN_OOD_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc768_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe0)

enum
{
    FLD_MATRIX_ADC768_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC768_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc768_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe1)

enum
{
    FLD_MATRIX_ADC768_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC768_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc768_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe2)

enum
{
    FLD_MATRIX_ADC768_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC384_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc384_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe3)

enum
{
    FLD_MATRIX_ADC384_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC384_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc384_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe4)

enum
{
    FLD_MATRIX_ADC384_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC384_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc192_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe5)

enum
{
    FLD_MATRIX_ADC192_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC192_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc192_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe6)

enum
{
    FLD_MATRIX_ADC192_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC192_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc96_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe7)

enum
{
    FLD_MATRIX_ADC192_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC96_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc96_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe8)

enum
{
    FLD_MATRIX_ADC96_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC96_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc96_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xe9)

enum
{
    FLD_MATRIX_ADC96_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC96_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc48_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xea)

enum
{
    FLD_MATRIX_ADC48_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC48_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_adc48_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xeb)

enum
{
    FLD_MATRIX_ADC48_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_ADC48_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic768_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xec)

enum
{
    FLD_MATRIX_ADC48_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC768_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic768_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xed)

enum
{
    FLD_MATRIX_DMIC768_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC768_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic768_anc0_bz_err_sel  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xee)

enum
{
    FLD_MATRIX_DMIC768_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC768_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384ll_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xef)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384LL_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384ll_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf0)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192ll_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf1)

enum
{
    FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192LL_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192ll_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf2)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192LL_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192ll_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf3)

enum
{
    FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf4)

enum
{
    FLD_MATRIX_DMIC384_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf5)

enum
{
    FLD_MATRIX_DMIC384_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC384_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic384_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf6)

enum
{
    FLD_MATRIX_DMIC384_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf7)

enum
{
    FLD_MATRIX_DMIC192_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic192_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf8)

enum
{
    FLD_MATRIX_DMIC192_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC192_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic96_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xf9)

enum
{
    FLD_MATRIX_DMIC96_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC96_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic96_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xfa)

enum
{
    FLD_MATRIX_DMIC96_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC96_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic32_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xfb)

enum
{
    FLD_MATRIX_DMIC96_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC32_ANC0_BZ_REF0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic32_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xfc)

enum
{
    FLD_MATRIX_DMIC32_ANC0_BZ_REF1_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC32_ANC0_BZ_REF2_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic32_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xfd)

enum
{
    FLD_MATRIX_DMIC32_ANC0_BZ_ERR0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC32_ANC0_BZ_ERR1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel1  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xfe)

enum
{
    FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF0_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF1_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel2  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0xff)

enum
{
    FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF2_SEL = BIT_RNG(0, 2),
    FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR0_SEL = BIT_RNG(4, 6),
};

#define reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel3  REG_ADDR8(REG_AUDIO_MATRIX_BASE + 0x100)

enum
{
    FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR1_SEL = BIT_RNG(0, 2),
};

/**************************************************** ANC register *****************************************************************/
/* AUDIO_ANC register */
#define reg_audio_anc_wcz_iir_b0(anc, wcz, iir) REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x00 + (wcz) * 0x180 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_wcz_iir_b1(anc, wcz, iir) REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x04 + (wcz) * 0x180 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_wcz_iir_b2(anc, wcz, iir) REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x08 + (wcz) * 0x180 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_wcz_iir_a1(anc, wcz, iir) REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x10 + (wcz) * 0x180 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_wcz_iir_a2(anc, wcz, iir) REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x14 + (wcz) * 0x180 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */

#define reg_audio_anc_cz3_iir_b0(anc, iir)      REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x600 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_cz3_iir_b1(anc, iir)      REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x604 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_cz3_iir_b2(anc, iir)      REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x608 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_cz3_iir_a1(anc, iir)      REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x610 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */
#define reg_audio_anc_cz3_iir_a2(anc, iir)      REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x614 + (iir) * 0x20) /* anc[0] wcz[0-3] iir[0-11] */

#define reg_audio_anc_rz_iir_b0(anc, rz, iir)   REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x780 + (rz) * 0x180 + (iir) * 0x20) /* anc[0] rz[0-1] iir[0-11] */
#define reg_audio_anc_rz_iir_b1(anc, rz, iir)   REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x784 + (rz) * 0x180 + (iir) * 0x20) /* anc[0] rz[0-1] iir[0-11] */
#define reg_audio_anc_rz_iir_b2(anc, rz, iir)   REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x788 + (rz) * 0x180 + (iir) * 0x20) /* anc[0] rz[0-1] iir[0-11] */
#define reg_audio_anc_rz_iir_a1(anc, rz, iir)   REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x790 + (rz) * 0x180 + (iir) * 0x20) /* anc[0] rz[0-1] iir[0-11] */
#define reg_audio_anc_rz_iir_a2(anc, rz, iir)   REG_ADDR32(REG_AUDIO_ANC_COEF(anc) + 0x794 + (rz) * 0x180 + (iir) * 0x20) /* anc[0] rz[0-1] iir[0-11] */

#define reg_audio_anc_wcz_fir(anc, wcz, fir)    REG_ADDR16(REG_AUDIO_ANC_COEF(anc) + 0xa80 + (wcz) * 0x200 + ((fir) / 16) * 0x02 + ((fir) % 16) * 0x20) /* anc[0] wcz[0-3] fir[0-127] */

#define reg_audio_anc_cz3_fir(anc, fir)         REG_ADDR16(REG_AUDIO_ANC_COEF(anc) + 0x1280 + ((fir) / 16) * 0x02 + ((fir) / 16) * 0x02 + ((fir) % 16) * 0x20) /* anc[0] cz[3] fir[0-127] */

#define reg_audio_anc_rz_fir(anc, rz, fir)      REG_ADDR16(REG_AUDIO_ANC_COEF(anc) + 0x1480 + (rz) * 0x200 + ((fir) / 16) * 0x02 + ((fir) % 16) * 0x20) /* anc[0] rz[0] fir[0-127] */

#define reg_audio_anc_bz_iir_b0(bz, iir)           REG_ADDR32(REG_AUDIO_BZ_BASE + 0x00 + (bz) * 0x78 + (iir) * 0x14) /* anc[0] bz[0-4] iir[0-5] */
#define reg_audio_anc_bz_iir_b1(bz, iir)           REG_ADDR32(REG_AUDIO_BZ_BASE + 0x04 + (bz) * 0x78 + (iir) * 0x14) /* anc[0] bz[0-4] iir[0-5] */
#define reg_audio_anc_bz_iir_b2(bz, iir)           REG_ADDR32(REG_AUDIO_BZ_BASE + 0x08 + (bz) * 0x78 + (iir) * 0x14) /* anc[0] bz[0-4] iir[0-5] */
#define reg_audio_anc_bz_iir_a1(bz, iir)           REG_ADDR32(REG_AUDIO_BZ_BASE + 0x0c + (bz) * 0x78 + (iir) * 0x14) /* anc[0] bz[0-4] iir[0-5] */
#define reg_audio_anc_bz_iir_a2(bz, iir)           REG_ADDR32(REG_AUDIO_BZ_BASE + 0x10 + (bz) * 0x78 + (iir) * 0x14) /* anc[0] bz[0-4] iir[0-5] */

/* AUDIO_ANC_BASE register */
#define reg_audio_anc_config(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x00) /* anc[0] */

enum
{
    FLD_TX_FIFO_CLR_PCLK = BIT(0),
    FLD_TX_RPTR_EN       = BIT(1),
    FLD_FB_MODE_INPUT_SEL= BIT(2),
    FLD_AHB_ANC_SEL      = BIT(4),//anc update coef according to dma
    FLD_ANC_SRC_EN       = BIT(5),
    FLD_ANC_SRC_RATE_SEL = BIT(6),
    FLD_ANC_SPK_SEL      = BIT(7),
};

#define reg_audio_anc_config1(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x01) /* anc[0] */

enum
{
    FLD_ANC_FSM_STATUS           = BIT_RNG(0, 3),
    FLD_ANC_SOFT_RST_EN          = BIT(4),//soft reset resample module
    FLD_ANC_POST_DATA_CLR        = BIT(5),
};

#define reg_audio_anc_config2(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x02) /* anc[0-1] */

enum
{
    FLD_ANC_DAC_CNT_MODE = BIT_RNG(0, 1),
    FLD_ANC_ADD_CZ1_SEL  = BIT(2),
    FLD_ANC_ADD_SRC_SEL   = BIT(3),
    /*
     * 0: ref012err01; 1: ref012err0; 2: ref01err01; 3: ref01err0; 4: ref0err0;
     * 5: ref0err01; 6: ref0; 7: ref0_wz384; 8: ref0_wz384_cz256; 9: feed_back mode
     *
     */
    FLD_ANC_MODE_SEL     = BIT_RNG(4, 7),
};

#define reg_audio_anc_config3(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x03) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_TRIG_NUM = BIT_RNG(0, 4),
};

#define reg_audio_anc_ref0_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0x04) /* anc[0] */

enum
{
    FLD_ANC_REF0_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_wz0_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0x08) /* anc[0] */

enum
{
    FLD_ANC_WZ0_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_gain_shift_latch(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x0c) /* anc[0] */

enum
{
    FLD_ANC_REF0_GAIN_SHIFT_LATCH = BIT(0),
    FLD_ANC_REF1_GAIN_SHIFT_LATCH = BIT(1),
    FLD_ANC_REF2_GAIN_SHIFT_LATCH = BIT(2),
    FLD_ANC_WZ0_GAIN_SHIFT_LATCH = BIT(4),
    FLD_ANC_WZ1_GAIN_SHIFT_LATCH = BIT(5),
    FLD_ANC_WZ2_GAIN_SHIFT_LATCH = BIT(6),
};

#define reg_audio_anc_gain0_mul_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x0d) /* anc[0] */

enum
{
    FLD_ANC_GAIN0_MUL_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_iir_start(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x0e) /* anc[0] */

enum
{
    FLD_ANC_WCZ0_IIR_START  = BIT(0),
    FLD_ANC_WCZ1_IIR_START  = BIT(1),
    FLD_ANC_WCZ2_IIR_START = BIT(2),
    FLD_ANC_WCZ3_IIR_START = BIT(3),
    FLD_ANC_CZ3_IIR_START = BIT(4),
    FLD_ANC_RZ0_IIR_START = BIT(5),
    FLD_ANC_RZ1_IIR_START = BIT(6),
};

#define reg_audio_anc_fir_start(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x0f) /* anc[0] */

enum
{
    FLD_ANC_WCZ0_FIR_START  = BIT(0),
    FLD_ANC_WCZ1_FIR_START  = BIT(1),
    FLD_ANC_WCZ2_FIR_START = BIT(2),
    FLD_ANC_WCZ3_FIR_START = BIT(3),
    FLD_ANC_CZ3_FIR_START = BIT(4),
    FLD_ANC_RZ0_FIR_START = BIT(5),
    FLD_ANC_RZ1_FIR_START = BIT(6),
};

#define reg_audio_anc_hb1_coef(anc, coef1) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0x10 + ((coef1) << 2)) /* anc[0] coef1[0-20] */

enum
{
    FLD_ANC_HB1_COEF = BIT_RNG(0, 25),
};

#define reg_audio_anc_hb2_coef(anc, coef2) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0x64 + ((coef2) << 2)) /* anc[0] coef2[0-6] */

enum
{
    FLD_ANC_HB2_COEF = BIT_RNG(0, 25),
};

#define reg_audio_anc_hb3_coef(anc, coef3) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0x80 + ((coef3) << 2)) /* anc[0] coef3[0-6] */

enum
{
    FLD_ANC_HB3_COEF = BIT_RNG(0, 25),
};

#define reg_audio_anc_fmt_sel(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x9c) /* anc[0] */

enum
{
    FLD_ANC_PRE_FMT_SEL  = BIT_RNG(0, 1),
    FLD_ANC_POST_FMT_SEL = BIT_RNG(2, 3),
    FLD_ANC_PLAY_FMT_SEL = BIT_RNG(4, 5),
};

#define reg_audio_anc_fmt_sel1(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x9d) /* anc[0] */

enum
{
    FLD_ANC_SRC_FMT_SEL = BIT(0),
    FLD_ANC_REF0_FMT_SEL = BIT(1),
    FLD_ANC_REF1_FMT_SEL = BIT(2),
    FLD_ANC_REF2_FMT_SEL = BIT(3),
    FLD_ANC_ERR0_FMT_SEL = BIT(4),
    FLD_ANC_ERR1_FMT_SEL = BIT(5),
};

#define reg_audio_anc_iir_done(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x9e) /* anc[0] */

enum
{
    FLD_ANC_WCZ0_IIR_DONE  = BIT(0),
    FLD_ANC_WCZ1_IIR_DONE  = BIT(1),
    FLD_ANC_WCZ2_IIR_DONE = BIT(2),
    FLD_ANC_WCZ3_IIR_DONE = BIT(3),
    FLD_ANC_CZ3_IIR_DONE = BIT(4),
    FLD_ANC_RZ0_IIR_DONE = BIT(5),
    FLD_ANC_RZ1_IIR_DONE = BIT(6),
};

#define reg_audio_anc_fir_done(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0x9f) /* anc[0] */

enum
{
    FLD_ANC_WCZ0_FIR_DONE  = BIT(0),
    FLD_ANC_WCZ1_FIR_DONE  = BIT(1),
    FLD_ANC_WCZ2_FIR_DONE = BIT(2),
    FLD_ANC_WCZ3_FIR_DONE = BIT(3),
    FLD_ANC_CZ3_FIR_DONE = BIT(4),
    FLD_ANC_RZ0_FIR_DONE = BIT(5),
    FLD_ANC_RZ1_FIR_DONE = BIT(6),
};

#define reg_audio_anc_droop_coef(anc, d_coef) REG_ADDR16(REG_AUDIO_ANC_BASE(anc) + 0xa0 + (((d_coef)) << 1)) /* anc[0] d_coef[0-5] */

enum
{
    FLD_ANC_DROOP_COEF = BIT_RNG(0, 13),
};

#define reg_audio_anc_tx_fifo_max(anc)          REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xaa) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_MAX = BIT_RNG(0, 7),

};

#define reg_audio_coef_num_max(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xab) /* anc[0] */

enum
{
    FLD_ANC_COEF_NUM_MAX = BIT_RNG(0, 3),
};

#define reg_audio_anc_ref1_gain(anc)      REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xac) /* anc[0] */

enum
{
    FLD_ANC_REF1_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_ref2_gain(anc)         REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xb0) /* anc[0] */

enum
{
    FLD_ANC_REF2_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_postdat_fifo(anc)      REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xb4) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_CLR_HCLK  = BIT(0),
    FLD_ANC_POSTDAT_EMPTY     = BIT(4),
    FLD_ANC_POSTDAT_FULL      = BIT(5),
    FLD_ANC_POSTDAT_UNDERRUN  = BIT(6),
    FLD_ANC_POSTDAT_UNDERFLOW = BIT(7),
};

#define reg_audio_anc_txfifo_rptr(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xb5) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_RPTR = BIT_RNG(0, 7)
};

#define reg_audio_anc_txfifo_irq_st(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xb7) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_IRQ_ST = BIT(0),
    FLD_ANC_COEF_LATCH     = BIT(1),
};

#define reg_audio_anc_txfifo_th(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xb8) /* anc[0] */

enum
{
    FLD_ANC_TX_FIFO_TH = BIT_RNG(0, 7)
};

#define reg_audio_anc_gain1_mul_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xb9) /* anc[0] */

enum
{
    FLD_ANC_GAIN1_MUL_SHIFT = BIT_RNG(0, 7)
};

#define reg_audio_anc_gain2_mul_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xba) /* anc[0] */

enum
{
    FLD_ANC_GAIN2_MUL_SHIFT = BIT_RNG(0, 7)
};

#define reg_audio_anc_only_ref0(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xbb) /* anc[0] */

enum
{
    FLD_ANC_RESAMPLE_MODE_SEL = BIT_RNG(4, 6),//0:48->768;1:48->384;2:96->768;3:96->384;4:48->192;others 96->192
};

#define reg_audio_anc_ref_dc(anc, ref) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xbc + ((ref) << 2)) /* anc[0] ref[0-2]*/

enum
{
    FLD_ANC_REF_DC = BIT_RNG(0, 23),
};

#define reg_audio_anc_ref_gain_shift(anc, ref) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xbf + ((ref) << 2)) /* anc[0] ref[0-2]*/

enum
{
    FLD_ANC_REF_GAIN_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_wz1_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xc8) /* anc[0] */

enum
{
    FLD_ANC_WZ1_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_wz2_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xcc) /* anc[0] */

enum
{
    FLD_ANC_WZ2_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_cz0_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xd0) /* anc[0] */

enum
{
    FLD_ANC_CZ0_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_cz3_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xd4) /* anc[0] */

enum
{
    FLD_ANC_CZ3_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_rz_gain(anc, rz) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xd8 + ((rz) << 2)) /* anc[0] rz[0-1]*/

enum
{
    FLD_ANC_RZ_GAIN = BIT_RNG(0, 27),
};

#define reg_audio_anc_cz0_gain_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe0) /* anc[0] */

enum
{
    FLD_ANC_CZ0_GAIN_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_cz3_gain_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe1) /* anc[0] */

enum
{
    FLD_ANC_CZ3_GAIN_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_rz_gain_shift(anc, rz) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe2 + (rz)) /* anc[0] rz[0-1]*/

enum
{
    FLD_ANC_RZ_GAIN_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_cz_rz_gain_shift_latch(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe4) /* anc[0] */

enum
{
    FLD_ANC_CZ0_GAIN_SHIFT_LATCH = BIT(0),
    FLD_ANC_CZ3_GAIN_SHIFT_LATCH = BIT(1),
    FLD_ANC_RZ0_GAIN_SHIFT_LATCH = BIT(2),
    FLD_ANC_RZ1_GAIN_SHIFT_LATCH = BIT(3),
    FLD_ANC_CZ1_GAIN_SHIFT_LATCH = BIT(4),
};

#define reg_audio_anc_limiter_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe5) /* anc[0] */

enum
{
    FLD_ANC_WZ_SUM_LIMITER_SHIFT = BIT_RNG(0,1),
    FLD_ANC_CZ_SUM_LIMITER_SHIFT = BIT_RNG(2,3),
};

#define reg_audio_anc_cz1_gain_shift(anc) REG_ADDR8(REG_AUDIO_ANC_BASE(anc) + 0xe6) /* anc[0] */

enum
{
    FLD_ANC_CZ1_GAIN_SHIFT = BIT_RNG(0, 5),
};

#define reg_audio_anc_cz1_gain(anc) REG_ADDR32(REG_AUDIO_ANC_BASE(anc) + 0xe8) /* anc[0] */

enum
{
    FLD_ANC_CZ1_GAIN = BIT_RNG(0, 27),
};
/**************************************************** CODEC control register *****************************************************************/
#define reg_audio_codec_adc_fmt_l           REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x02)

enum
{
    FLD_CODEC_ADC0_768_SEL                  = BIT(0),
    FLD_CODEC_ADC0_384_SEL                  = BIT(1),
    FLD_CODEC_ADC0_192_SEL                  = BIT(2),
    FLD_CODEC_ADC0_96_SEL                   = BIT(3),
    FLD_CODEC_ADC0_48_SEL                   = BIT(4),
    FLD_CODEC_ADC1_768_SEL                  = BIT(5),
    FLD_CODEC_ADC1_384_SEL                  = BIT(6),
    FLD_CODEC_ADC1_192_SEL                  = BIT(7),
};

#define reg_audio_codec_adc_fmt_2           REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x03)

enum
{
    FLD_CODEC_ADC1_96_SEL                   = BIT(0),
    FLD_CODEC_ADC1_48_SEL                   = BIT(1),
    FLD_CODEC_ADC2_768_SEL                  = BIT(2),
    FLD_CODEC_ADC2_384_SEL                  = BIT(3),
    FLD_CODEC_ADC2_192_SEL                  = BIT(4),
    FLD_CODEC_ADC2_96_SEL                   = BIT(5),
    FLD_CODEC_ADC2_48_SEL                   = BIT(6),
};

#define reg_audio_codec_dac_fmt             REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x04)

enum
{
    FLD_CODEC_DAC0_SEL                      = BIT(0),
    FLD_CODEC_DAC1_SEL                      = BIT(1),
};

#define reg_audio_codec_adc768k_out_fmt     REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x05)

enum
{
    FLD_CODEC_ADC0_768_OUT_FMT              = BIT(0),
    FLD_CODEC_ADC1_768_OUT_FMT              = BIT(1),
    FLD_CODEC_ADC2_768_OUT_FMT              = BIT(2),
};

#define reg_audio_dmic_codec_lr_gain_ctrl   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x38)

enum
{
    FLD_CODEC_GAIN_LR                       = BIT_RNG(0,3),
};

#define reg_audio_dmic_codec_lr_low_latency_gain_ctrl   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x39)

enum
{
    FLD_CODEC_GAIN_SHIFT_LOW_LATENCY                    = BIT_RNG(0,5),
};

#define reg_audio_dmic_codec_lr_gain_shift_ctrl         REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3a)

enum
{
    FLD_CODEC_GAIN_SHIFT_LR                             = BIT_RNG(0,5),
    FLD_CODEC_CODEC_EN_LR                               = BIT(6),
    FLD_CODEC_CODEC_EN_SINGLE                           = BIT(7),
};

#define reg_audio_dmic_codec_single_gain_ctrl           REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3b)

enum
{
    FLD_CODEC_GAIN_SINGLE                               = BIT_RNG(0,3),
};

#define reg_audio_dmic_codec_single_low_latency_gain_ctrl   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3c)

enum
{
    FLD_CODEC_GAIN_SHIFT_LOW                                = BIT_RNG(0,5),
};

#define reg_audio_dmic_codec_single_gain_shift_ctrl         REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3d)

enum
{
    FLD_CODEC_GAIN_SHIFT_SINGLE                             = BIT_RNG(0,5),
    FLD_CODEC_R_NEG_LR                                      = BIT(6),
    FLD_CODEC_R_NEG_SINGLE                                  = BIT(7),
};

#define reg_audio_dmic_codec_lr_ctrl(dmic)            REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3e + (dmic)) /* dmic[0-1] */

enum
{
    FLD_CODEC_SAMPLE_SEL_LR                     = BIT(0),
    FLD_CODEC_CH_SEL_LR                         = BIT(1),
    FLD_CODEC_OUTPUT_BIT_SEL_LR                 = BIT(2),
    FLD_CODEC_OUT_SEL_LR                        = BIT_RNG(4,7),
};

#define reg_audio_dmic_codec_single_ctrl        REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x3f)

enum
{
    FLD_CODEC_SAMPLE_SEL_SINGLE                 = BIT(0),
    FLD_CODEC_CH_SEL_SINGLE                     = BIT(1),
    FLD_CODEC_OUTPUT_BIT_SEL_SINGLE             = BIT(2),
    FLD_CODEC_OUT_SEL_SINGLE                    = BIT_RNG(4,7),
};

#define reg_audio_dmic_codec_lr_cic_overrun         REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x40)

enum
{
    FLD_CODEC_DMIC_CODEC_LR_CIC_FIFO_RIGHT_OVERRUN  = BIT(0),
    FLD_CODEC_DMIC_CODEC_LR_CIC_FIFO_LEFT_OVERRUN   = BIT(1),
};

#define reg_audio_dmic_lr_data_ctrl_1                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x41)

enum
{
    FLD_CODEC_DMIC_CODEC_LR_FIR1_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_LR_FIR1_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_LR_FIR1_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_LR_FIR1_FIFO_LEFT_OVERRUN      = BIT(3),
    FLD_CODEC_DMIC_CODEC_LR_DMIC_DAT_POS                = BIT_RNG(4,7),
};

#define reg_audio_dmic_lr_data_ctrl_2                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x42)

enum
{
    FLD_CODEC_DMIC_CODEC_LR_FIR3_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_LR_FIR3_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_LR_FIR3_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_LR_FIR3_FIFO_LEFT_OVERRUN      = BIT(3),
    FLD_CODEC_DMIC_CODEC_LR_DMIC_DAT_NEG                = BIT_RNG(4,7),
};

#define reg_audio_dmic_codec_single_cic_overrun         REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x43)

enum
{
    FLD_CODEC_DMIC_CODEC_SINGLE_CIC_FIFO_RIGHT_OVERRUN  = BIT(0),
    FLD_CODEC_DMIC_CODEC_SINGLE_CIC_FIFO_LEFT_OVERRUN   = BIT(1),
};

#define reg_audio_dmic_single_data_ctrl_1                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x44)

enum
{
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR1_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR1_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR1_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR1_FIFO_LEFT_OVERRUN      = BIT(3),
    FLD_CODEC_DMIC_CODEC_SINGLE_DMIC_DAT_POS        = BIT_RNG(4,7),
};

#define reg_audio_dmic_single_data_ctrl_2                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x45)

enum
{
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR3_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR3_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR3_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR3_FIFO_LEFT_OVERRUN      = BIT(3),
    FLD_CODEC_DMIC_CODEC_SINGLE_DMIC_DAT_NEG                = BIT_RNG(4,7),
};

#define reg_audio_dmic_lr_data_ctrl_3                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x46)

enum
{
    FLD_CODEC_DMIC_CODEC_LR_FIR4_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_LR_FIR4_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_LR_FIR4_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_LR_FIR4_FIFO_LEFT_OVERRUN      = BIT(3),
};

#define reg_audio_dmic_single_data_ctrl_3                   REG_ADDR8(REG_AUDIO_CODEC_CTRL_BASE+0x47)

enum
{
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR4_FIFO_RIGHT_UNDERRUN    = BIT(0),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR4_FIFO_RIGHT_OVERRUN     = BIT(1),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR4_FIFO_LEFT_UNDERRUN     = BIT(2),
    FLD_CODEC_DMIC_CODEC_SINGLE_FIR4_FIFO_LEFT_OVERRUN      = BIT(3),
};

/**************************************************** CLK and IRQ control register *****************************************************************/
#define reg_audio_clk_en_0 REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE)

enum
{
    FLD_CLK_ACLK_EN   = BIT(0),
    FLD_CLK_I2S0_EN   = BIT(1),
    FLD_CLK_I2S1_EN   = BIT(2),
    FLD_CLK_I2S2_EN   = BIT(3),
    FLD_CLK_SPDIF_EN  = BIT(4),
    FLD_CLK_DMIC0_EN = BIT(5),
    FLD_CLK_DMIC1_EN = BIT(6),
};

#define reg_audio_clk_en_1 REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x01)

enum
{
    FLD_CLK_EQ0_EN = BIT(0),
    FLD_CLK_EQ1_EN = BIT(1),
    FLD_CLK_ASRC0_EN = BIT(2),
    FLD_CLK_ASRC1_EN = BIT(3),
    FLD_CLK_EQ3_EN = BIT(4),
    FLD_CLK_ANC0_EN = BIT(5),
};

#define reg_audio_clk_i2s_step(i2s) REG_ADDR16(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x02 + ((i2s) << 1)) /* i2s[0-2] */

enum
{
    FLD_CLK_I2S_STEP = BIT_RNG(0, 14)
};

#define reg_audio_clk_i2s_mod(i2s) REG_ADDR16(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x08 + ((i2s) << 1)) /* i2s[0-2] */

#define reg_audio_codec_adc_dac_en  REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0xe)

enum
{
    FLD_CODEC_ADC0_EN = BIT(0),
    FLD_CODEC_ADC1_EN = BIT(1),
    FLD_CODEC_ADC2_EN = BIT(2),

    FLD_CODEC_DAC0_EN = BIT(4),
    FLD_CODEC_DAC1_EN = BIT(5),
};

#define reg_audio_clk_aclk_set REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x0f)
enum
{
    FLD_CLK_ACLK_SET = BIT_RNG(0, 3)
};

#define reg_audio_clk_irq_status0  REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x10)

enum
{
    FLD_DMA_FIFO_IRQ0 = BIT(0),
    FLD_DMA_FIFO_IRQ1 = BIT(1),
    FLD_DMA_FIFO_IRQ2 = BIT(2),
    FLD_DMA_FIFO_IRQ3 = BIT(3),
    FLD_DMA_FIFO_IRQ4 = BIT(4),
    FLD_DMA_FIFO_IRQ5 = BIT(5),
    FLD_DMA_FIFO_IRQ6 = BIT(6),
    FLD_DMA_FIFO_IRQ7 = BIT(7),
};

#define reg_audio_clk_irq_status1 REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x11)

enum
{
    FLD_HAC_IRQ0 = BIT(0),
    FLD_HAC_IRQ1 = BIT(1),
    FLD_HAC_IRQ2 = BIT(2),
    FLD_HAC_IRQ3 = BIT(3),
    FLD_HAC_IRQ4 = BIT(4),
};

#define reg_audio_clk_irq_status2 REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x12)

enum
{
    FLD_HAC_HIT_NUM_IRQ_EQ0   = BIT(0),
    FLD_HAC_HIT_NUM_IRQ_EQ1   = BIT(1),
    FLD_HAC_HIT_NUM_IRQ_ASRC0 = BIT(2),
    FLD_HAC_HIT_NUM_IRQ_ASRC1 = BIT(3),
    FLD_HAC_HIT_NUM_IRQ_EQ2   = BIT(4),
    FLD_CODEC_IRQ             = BIT(5),
    FLD_HMST_RESP_IRQ         = BIT(6),
};

#define reg_audio_clk_eq_asrc_done_status REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x13)

enum
{
    FLD_EQ0_DONE_STATUS   = BIT(0),
    FLD_EQ1_DONE_STATUS   = BIT(1),
    FLD_ASRC0_DONE_STATUS = BIT(2),
    FLD_ASRC1_DONE_STATUS = BIT(3),
    FLD_EQ2_DONE_STATUS   = BIT(4),
};

#define reg_audio_clk_hmst_resp_irq_ctrl REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x14)

enum
{
    FLD_HMST_RESP_IRQ_EN  = BIT(0),
    FLD_HMST_RESP_IRQ_CLR = BIT(4),
};

#define reg_audio_codec_adc_clk_set REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x16)

enum
{
    FLD_CLK_CODEC_ADC_SET    = BIT_RNG(0, 7),
};

#define reg_audio_dmic_set REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x17)

enum
{
    FLD_CLK_DMIC_SET    = BIT_RNG(0, 3),
};

#define reg_audio_clk_rst_en_l REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x18)

enum
{
    FLD_CLK_RST_I2S0_EN    = BIT(0),
    FLD_CLK_RST_I2S1_EN    = BIT(1),
    FLD_CLK_RST_I2S2_EN    = BIT(2),
    FLD_CLK_RST_ANC0_EN    = BIT(3),
    FLD_CLK_RST_DMICIF_EN  = BIT(5),
    FLD_CLK_RST_DMIC01_EN  = BIT(6),
    FLD_CLK_RST_CODECIF_EN = BIT(7),
};

#define reg_audio_clk_rst_en_h REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x19)

enum
{
    FLD_CLK_RST_SDT0_EN   = BIT(0),
    FLD_CLK_RST_SDT1_EN   = BIT(1),
    FLD_CLK_RST_SDT2_EN   = BIT(2),
    FLD_CLK_RST_SDT3_EN   = BIT(3),
    FLD_CLK_RST_HAC_EN    = BIT(4),
    FLD_CLK_RST_SPDIF_EN  = BIT(5),
    FLD_CLK_RST_MATRIX_EN = BIT(6),
    FLD_CLK_RST_DMIC2_EN = BIT(7),
};

#define reg_audio_clk_rst_en_2 REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x1a)

enum
{
    FLD_CLK_RST_ANC0_FCLK_EN   = BIT(0),
    FLD_CLK_RST_ANC0_RSMP_N_EN = BIT(4),
};

#define reg_audio_pll_set      REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x1b)

enum
{
    FLD_ACLK_PLL_SET   = BIT(0),
    FLD_CODEC_PLL_SET  = BIT(1),
    FLD_DMIC_PLL_SET   = BIT(2),
    FLD_I2S0_PLL_SET   = BIT(3),
    FLD_I2S1_PLL_SET   = BIT(4),
    FLD_I2S2_PLL_SET   = BIT(5),
    FLD_SPDIF_PLL_SET  = BIT(6),
    FLD_ANC0_PLL_SET   = BIT(7),
};

#define reg_audio_codec_dac01_clk_set REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x1c)

enum
{
    FLD_CLK_CODEC_DAC01_SET    = BIT_RNG(0, 7),
};

#define reg_audio_codec_dac_clk_set   REG_ADDR8(REG_AUDIO_CLK_IRQ_CTRL_BASE + 0x1d)

enum
{
    FLD_CLK_CODEC_DAC_SET    = BIT_RNG(0, 7),
};
/**************************************************** CODEC0 register *****************************************************************/
#define reg_audio_codec_cfg_0           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x00)

enum
{
    FLD_CODEC_ADC0_DIG_GAIN_SEL         =  BIT_RNG(0,7),

    FLD_CODEC_ADC0_HPF_FC               = BIT_RNG(8,11),
    FLD_CODEC_ADC0_HPF_EN               = BIT(12),
    FLD_CODEC_ADC0_COEF_SEL             = BIT_RNG(13,14),
    FLD_CODEC_ADC0_RATE_SEL            = BIT_RNG(15,17), //[0]

    FLD_CODEC_ADC0_PWR_MODE             = BIT(18),
    FLD_CODEC_ADC0_TEST_MOD             = BIT(19),
    FLD_CODEC_ADC0_ENABLE               = BIT(20),
    FLD_CODEC_ADC0_ANA_ENABLE           = BIT(21),
    FLD_CODEC_ADC0_RSTN                 = BIT(22),
    FLD_CODEC_ADC1_ENABLE               = BIT(23),

    FLD_CODEC_ADC1_ANA_ENABLE           = BIT(24),
    FLD_CODEC_ADC1_RSTN                 = BIT(25),
    FLD_CODEC_ADC2_ENABLE               = BIT(26),
    FLD_CODEC_ADC2_ANA_ENABLE           = BIT(27),
    FLD_CODEC_ADC2_RSTN                 = BIT(28),
    FLD_CODEC_RESERVED                  = BIT_RNG(29,31),
};

#define reg_audio_codec_cfg_1           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x04)
enum
{
    FLD_CODEC_ADC1_DIG_GAIN_SEL         = BIT_RNG(0,7),

    FLD_CODEC_ADC1_HPF_FC               = BIT_RNG(8,11),
    FLD_CODEC_ADC1_HPF_EN               = BIT(12),
    FLD_CODEC_ADC1_COEF_SEL             = BIT_RNG(13,14),
    FLD_CODEC_ADC1_RATE_SEL            = BIT_RNG(15,17), //[0]

    FLD_CODEC_ADC1_PWR_MODE             = BIT(18),
    FLD_CODEC_ADC1_TEST_MOD             = BIT(19),
};

#define reg_audio_codec_cfg_2           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x08)
enum
{
    FLD_CODEC_ADC2_DIG_GAIN_SEL         = BIT_RNG(0,7),

    FLD_CODEC_ADC2_HPF_FC               = BIT_RNG(8,11),
    FLD_CODEC_ADC2_HPF_EN               = BIT(12),
    FLD_CODEC_ADC2_COEF_SEL             = BIT_RNG(13,14),
    FLD_CODEC_ADC2_RATE_SEL            = BIT_RNG(15,17), //[0]

    FLD_CODEC_ADC2_PWR_MODE             = BIT(18),
    FLD_CODEC_ADC2_TEST_MOD             = BIT(19),
};

#define reg_audio_codec_cfg_5           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x14)

enum
{
    FLD_CODEC_DAC0_DIG_GAIN_SEL         = BIT_RNG(0,7),

    FLD_CODEC_DAC0_COEF_SEL             = BIT_RNG(8,9),
    FLD_CODEC_DAC0_RATE_SEL             = BIT_RNG(10,12),
    FLD_CODEC_DAC0_PWR_MODE             = BIT(13),
    FLD_CODEC_DAC0_ENABLE               = BIT(14),
    FLD_CODEC_DAC0_RSTN                 = BIT(15),

    FLD_CODEC_DAC1_ENABLE               = BIT(16),
    FLD_CODEC_DAC1_RSTN                 = BIT(17),
};

#define reg_audio_dac0_pcm_offset       REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x18)

#define reg_audio_codec_cfg_7           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x1c)

enum
{
    FLD_CODEC_DAC1_DIG_GAIN_SEL         = BIT_RNG(0,7),

    FLD_CODEC_DAC1_COEF_SEL             = BIT_RNG(8,9),
    FLD_CODEC_DAC1_RATE_SEL             = BIT_RNG(10,12),
    FLD_CODEC_DAC1_PWR_MODE             = BIT(13),
};

#define reg_audio_dac1_pcm_offset       REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x20)

#define reg_audio_codec_cfg_8                 REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x24)

enum
{
    FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1  = BIT_RNG(0,3),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1    = BIT_RNG(4,7),

    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1 = BIT(8),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1 = BIT(9),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1 = BIT(10),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1    = BIT_RNG(11,14),
    FLD_CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1       = BIT(15),

    FLD_CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1      = BIT(16),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1       = BIT(17),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1   = BIT(18),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1   = BIT(19),
    FLD_CODEC_AUDIO_CODEC_REGBAK_CH1            = BIT(20),
};

#define reg_audio_codec_cfg_9                   REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x28)

enum
{
    FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2  = BIT_RNG(0,3),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2    = BIT_RNG(4,7),

    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2 = BIT(8),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2 = BIT(9),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2 = BIT(10),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2    = BIT_RNG(11,14),
    FLD_CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2       = BIT(15),

    FLD_CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2      = BIT(16),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2       = BIT(17),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2   = BIT(18),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2   = BIT(19),
    FLD_CODEC_AUDIO_CODEC_REGBAK_CH2            = BIT(20),
};

#define reg_audio_codec_cfg_10                REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x2c)

enum
{
    FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3  = BIT_RNG(0,3),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3    = BIT_RNG(4,7),

    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3 = BIT(8),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3 = BIT(9),
    FLD_CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3 = BIT(10),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3    = BIT_RNG(11,14),
    FLD_CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3       = BIT(15),

    FLD_CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3      = BIT(16),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3       = BIT(17),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3   = BIT(18),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3   = BIT(19),
    FLD_CODEC_AUDIO_CODEC_REGBAK_CH3            = BIT(20),
};

#define reg_audio_codec_cfg_13                  REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x38)

enum
{
    FLD_CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM      = BIT_RNG(0,2),
    FLD_CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM      = BIT_RNG(3,5),
    FLD_CODEC_AUDIO_CODEC_REC_LOWP_MODE         = BIT(6),
    FLD_CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE    = BIT(7),

    FLD_CODEC_AUDIO_CODEC_REC_VREFP18_ENP       = BIT(8),
    FLD_CODEC_AUDIO_CODEC_REC_VCOM_ENP          = BIT(9),
    FLD_CODEC_AUDIO_CODEC_REC_TEST_SEL          = BIT_RNG(10,11),
    FLD_CODEC_AUDIO_CODEC_REC_IB_SEL            = BIT_RNG(12,15),

    FLD_CODEC_AUDIO_CODEC_REC_SELI_VREF1P8      = BIT_RNG(16,18),
    FLD_CODEC_AUDIO_CODEC_REC_SELI_VCOM         = BIT_RNG(19,21),
    FLD_CODEC_CDC_VREF_MODE_0P8                 = BIT(22),
    FLD_CODEC_CDC_VREF_FAST_STARTUP_0P8         = BIT(23),

    FLD_CODEC_CDC_ENP_VREF_0P8                  = BIT(24),
    FLD_CODEC_CTL_R_0P8                         = BIT_RNG(25,26),
};

#define reg_audio_codec_intr_status             REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x3c)

enum
{
    FLD_CODEC_O_AUTX_IREF_OK                    = BIT(0),
    FLD_CODEC_O_AUTX_ILIM_DET                   = BIT(1),
    FLD_CODEC_TX_IREF_OK_CORE                   = BIT(2),
    FLD_CODEC_ILIM_DET_CORE                     = BIT(3),
};

#define reg_audio_codec_intr_int_raw            REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x40)

enum
{
    FLD_CODEC_O_AUTX_IREF_OK_RAW                = BIT(0),
    FLD_CODEC_O_AUTX_ILIM_DET_RAW               = BIT(1),
    FLD_CODEC_TX_IREF_OK_CORE_RAW               = BIT(2),
    FLD_CODEC_ILIM_DET_CORE_RAW                 = BIT(3),
};

#define reg_audio_codec_intr_int_force          REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x44)

enum
{
    FLD_CODEC_O_AUTX_IREF_OK_FORCE              = BIT(0),
    FLD_CODEC_O_AUTX_ILIM_DET_FORCE             = BIT(1),
    FLD_CODEC_TX_IREF_OK_CORE_FORCE             = BIT(2),
    FLD_CODEC_ILIM_DET_CORE_FORCE               = BIT(3),
};

#define reg_audio_codec_intr_int_mask           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x48)

enum
{
    FLD_CODEC_O_AUTX_IREF_OK_MASK               = BIT(0),
    FLD_CODEC_O_AUTX_ILIM_DET_MASK              = BIT(1),
    FLD_CODEC_TX_IREF_OK_CORE_MASK              = BIT(2),
    FLD_CODEC_ILIM_DET_CORE_MASK                = BIT(3),
};

#define reg_audio_codec_intr_int_status         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x4c)

enum
{
    FLD_CODEC_O_AUTX_IREF_OK_STATUS             = BIT(0),
    FLD_CODEC_O_AUTX_ILIM_DET_STATUS            = BIT(1),
    FLD_CODEC_TX_IREF_OK_CORE_STATUS            = BIT(2),
    FLD_CODEC_ILIM_DET_CORE_STATUS              = BIT(3),
};

#define reg_audio_codec_dac_cfg0              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x50)

enum
{
    FLD_CODEC_I_CFG_DEM_ED_ENA                  = BIT(0),
    FLD_CODEC_I_CFG_DEM_ED_THRESH_LOW           = BIT_RNG(1,3),
    FLD_CODEC_I_CFG_DEM_ED_THRESH_HIGH          = BIT_RNG(4,6),
    FLD_CODEC_I_CFG_DEM_ED_RLS_TIME_LOW         = BIT(7),

    FLD_CODEC_I_CFG_DEM_ED_RLS_TIME_HIGH        = BIT(8),
    FLD_CODEC_I_CFG_DEM_ENA                     = BIT(9),
    FLD_CODEC_I_CFG_DEM_DYNAMIC_PD              = BIT(10),
    FLD_CODEC_I_CFG_DEM_MUTE                    = BIT(11),
    FLD_CODEC_I_CFG_AUTX_PDB                    = BIT(12),
    FLD_CODEC_I_CFG_AUTX_LCH_DISABLE            = BIT(13),
    FLD_CODEC_I_CFG_AUTX_RCH_DISABLE            = BIT(14),
    FLD_CODEC_I_CFG_ED_DSS_ENA                  = BIT(15),

    FLD_CODEC_I_CFG_ED_DSS_THRESH               = BIT_RNG(16,23),

    FLD_CODEC_I_CFG_ED_DSS_RLS_TIME             = BIT_RNG(24,29),
};

#define reg_audio_codec_dac_cfg1              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x54)

enum
{
    FLD_CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL        = BIT_RNG(0,1),
    FLD_CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA        = BIT(2),
    FLD_CODEC_I_CFG_ED_DSS_ZCD_ENA              = BIT(3),
    FLD_CODEC_I_CFG_ED_NG_ENA                   = BIT(4),

    FLD_CODEC_I_CFG_ED_NG_THRESH                = BIT_RNG(5,12), //[0:7]
    FLD_CODEC_I_CFG_ED_NG_RLS_TIME              = BIT_RNG(13,18), //[0:5]

    FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL         = BIT_RNG(19,20),
    FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA         = BIT(21),
    FLD_CODEC_I_CFG_ED_NG_ZCD_ENA               = BIT(22),
    FLD_CODEC_I_CFG_ED_NG_FORCELOW              = BIT(23),

    FLD_CODEC_I_CFG_ED_NG_FORCEHIGH             = BIT(24),
    FLD_CODEC_I_CFG_INVERT_DSM_IN               = BIT(25),
    FLD_CODEC_I_CFG_DSM_ENA                     = BIT(26),
    FLD_CODEC_I_CFG_DSM_INJ_ENA_L               = BIT(27),
    FLD_CODEC_I_CFG_DSM_INJ_ENA_R               = BIT(28),
    FLD_CODEC_I_CFG_DSM_OBS_ENA_L               = BIT(29),
    FLD_CODEC_I_CFG_DSM_OBS_ENA_R               = BIT(30),
};

#define reg_audio_codec_dac_cfg2              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x58)

enum
{
    FLD_CODEC_I_CFG_DSS_DIGGAIN_ENA             = BIT(0),
    FLD_CODEC_I_CFG_DSS_MULTIPLY_L              = BIT_RNG(1,4),
    FLD_CODEC_I_CFG_DSS_DIVIDE_L                = BIT_RNG(5,6),

    FLD_CODEC_I_CFG_DSS_MULTIPLY_R             = BIT_RNG(7,10), //[0:3]
    FLD_CODEC_I_CFG_DSS_DIVIDE_R                = BIT_RNG(11,12),
    FLD_CODEC_I_CFG_DSS_DOUT_DLY1CYCLE          = BIT(13),
    FLD_CODEC_I_CFG_ED_DSS_LVL_DLY2AFE0         = BIT_RNG(14,15), //[0:1]

    FLD_CODEC_I_CFG_ED_DSS_LVL_DLY2AFE1         = BIT(16), //[2]
    FLD_CODEC_I_CFG_ED_DSS_FORCELOW             = BIT(17),
    FLD_CODEC_I_CFG_ED_DSS_FORCEHIGH            = BIT(18),
    FLD_CODEC_I_CFG_AUTX_GAIN_USER_L            = BIT_RNG(19,21),
    FLD_CODEC_I_CFG_AUTX_GAIN_USER_R           = BIT_RNG(22,24),

    FLD_CODEC_I_CFG_HPAMP_OFC_ENA               = BIT(25),
    FLD_CODEC_I_CFG_AUTX_OFC_ENA1               = BIT(26),
    FLD_CODEC_I_CFG_AUTX_OFC_ENA2               = BIT(27),
    FLD_CODEC_I_CFG_OFC_INIT_CNT                = BIT_RNG(28,31),
};

#define reg_audio_codec_dac_cfg3              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x5c)

enum
{
    FLD_CODEC_BGR_ENP                           = BIT(0),
    FLD_CODEC_VREF_MICBIAS_TRIM                 = BIT_RNG(1,4),
    FLD_CODEC_BIAS_TRIM                         = BIT_RNG(5,7),

    FLD_CODEC_VREF_DAC_TRIM                     = BIT_RNG(8,11),
    FLD_CODEC_MIC_BIAS_SEL                      = BIT_RNG(12,14),
    FLD_CODEC_MIC_BIAS_EN                       = BIT(15),

    FLD_CODEC_VREF_ADC_TRIM                     = BIT_RNG(17,20),
};

#define reg_audio_codec_dac_cfg4              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x60)

enum
{
    FLD_CODEC_PGOOD_CDC                         = BIT_RNG(0,2),
    FLD_CODEC_TX_MUTE_L_CORE                    = BIT(3),
    FLD_CODEC_TX_MUTE_R_CORE                    = BIT(4),
    FLD_CODEC_TX_IREF_PDB_CORE                  = BIT(5),
    FLD_CODEC_HPAMP_OFFCAL_L_CORE0              = BIT_RNG(6,7), //[0:1]

    FLD_CODEC_HPAMP_OFFCAL_L_CORE1              = BIT_RNG(8,12), //[2:6]
    FLD_CODEC_HPAMP_OFFCAL_R_CORE0              = BIT_RNG(13,15), //[0:2]

    FLD_CODEC_HPAMP_OFFCAL_R_CORE1              = BIT_RNG(16,19), //[3:6]
};

#define reg_audio_codec_dac_status              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x64)

enum
{
    FLD_CODEC_O_AUTX_OFC_DONE_R                 = BIT(0),
    FLD_CODEC_O_AUTX_OFC_DONE_L                 = BIT(1),
    FLD_CODEC_O_HPAMP_OFC_DONE_R                = BIT(2),
    FLD_CODEC_O_HPAMP_OFC_DONE_L                = BIT(3),
    FLD_CODEC_SYNC_O_AUTX_OFC_DONE_R            = BIT(4),
    FLD_CODEC_SYNC_O_AUTX_OFC_DONE_L            = BIT(5),
    FLD_CODEC_SYNC_O_HPAMP_OFC_DONE_R           = BIT(6),
    FLD_CODEC_SYNC_O_HPAMP_OFC_DONE_L           = BIT(7),
};

#define reg_audio_codec_dac_test1               REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x68)

#define reg_audio_codec_dac_test2_0             REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x6c)

#define reg_audio_codec_dac_dcrm              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x70)

enum
{
    FLD_CODEC_DAC0_HPF_FC                       = BIT_RNG(0,3),
    FLD_CODEC_DAC0_HPF_EN                       = BIT(4),

    FLD_CODEC_DAC1_HPF_FC                       = BIT_RNG(8,11),
    FLD_CODEC_DAC1_HPF_EN                       = BIT(12),
};

#define reg_audio_codec_adc0_dig_gain         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x7c)
#define reg_audio_codec_adc1_dig_gain         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x80)
#define reg_audio_codec_adc2_dig_gain         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x84)
#define reg_audio_codec_adc_dig_gain(adc)     REG_ADDR32(REG_AUDIO_CODEC0_BASE + 0x7c + ((adc) << 2)) /* adc[0-4] */

enum
{
    FLD_CODEC_ADC_DST_GAIN_INDEX                = BIT_RNG(0,7),

    FLD_CODEC_ADC_GAIN_SMOOTH_SEL               = BIT_RNG(8,10),
    FLD_CODEC_ADC_GAIN_ENABLE                   = BIT(11),
};


#define reg_audio_codec_dac0_dig_gain         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x90)
#define reg_audio_codec_dac1_dig_gain         REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x94)
#define reg_audio_codec_dac_dig_gain_0(dac)     REG_ADDR32(REG_AUDIO_CODEC0_BASE + 0x90 + ((dac) << 2)) /* dac[0-1] */

enum
{
    FLD_CODEC_DAC_DST_GAIN_INDEX                = BIT_RNG(0,7),

    FLD_CODEC_DAC_GAIN_SMOOTH_SEL               = BIT_RNG(8,10),
    FLD_CODEC_DAC_GAIN_ENABLE                   = BIT(11),
};

#define reg_audio_codec_dac_l_cfg               REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x98)

#define reg_audio_codec_dac_r_cfg               REG_ADDR32(REG_AUDIO_CODEC0_BASE+0x9c)


#define reg_audio_bp_384flt_fr_dly              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xa0)

enum
{
    FLD_CODEC_BP_384FLT_FR_DLY                  = BIT(0),
};

#define reg_audio_codec_dac_status2           REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xa4)

enum
{
    FLD_CODEC_OFCCODE_AUTXGAIN_M18DB_L          = BIT_RNG(0,7),

    FLD_CODEC_OFCCODE_AUTXGAIN_USER_L           = BIT_RNG(8,15),

    FLD_CODEC_OFCCODE_AUTXGAIN_M18DB_R          = BIT_RNG(16,23),

    FLD_CODEC_OFCCODE_AUTXGAIN_USER_R           = BIT_RNG(24,31),
};

#define reg_audio_codec_ofc_cfg1              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xa8)

enum
{
    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_CODE1_R      = BIT_RNG(0,7),

    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_CODE2_R      = BIT_RNG(8,15),

    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_CODE1_L      = BIT_RNG(16,23),

    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_CODE2_L      = BIT_RNG(24,31),
};

#define reg_audio_codec_ofc_cfg2              REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xac)

enum
{
    FLD_CODEC_I_CFG_HPAMP_OFC_FORCE_L           = BIT(0),
    FLD_CODEC_I_CFG_HPAMP_OFC_FORCE_CODE_L      = BIT_RNG(1,7),

    FLD_CODEC_I_CFG_HPAMP_OFC_FORCE_R           = BIT(8),
    FLD_CODEC_I_CFG_HPAMP_OFC_FORCE_CODE_R      = BIT_RNG(9,15),

    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_L            = BIT(16),
    FLD_CODEC_I_CFG_AUTX_OFC_FORCE_R            = BIT(17),
};

#define reg_audio_codec_dac_timer               REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xb0)

enum
{
    FLD_CODEC_I_ED_TIMER_STROBE_DIV             = BIT_RNG(0,15),
};

#define reg_audio_codec_enable_sync             REG_ADDR32(REG_AUDIO_CODEC0_BASE+0xb4)

enum
{
    FLD_CODEC_ADC_ENABLE                        = BIT(0),
    FLD_CODEC_DAC_ENABLE                        = BIT(1),
};

/**************************************************** ASRC register *****************************************************************/
#define reg_audio_asrc_drop_coef(asrc, d_coef) REG_ADDR16(REG_AUDIO_ASRC_COFF_BASE + (asrc) * 0xb0 + ((d_coef) << 1)) /* asrc[0-1], d_coef[0-8] */

enum
{
    FLD_ASRC_DROP_COEF = BIT_RNG(0, 13),
};

#define reg_audio_asrc_drop_len_mod(asrc) REG_ADDR8(REG_AUDIO_ASRC_COFF_BASE + 0x12 + (asrc) * 0xb0) /* asrc[0-1] */

enum
{
    FLD_ASRC_DROP_LEN_MOD = BIT_RNG(0, 1),                                                                                /**< 0: 9taps, 1: 13taps, 2: 17taps*/
};

#define reg_audio_asrc_hb1_coef(asrc, coef1) REG_ADDR32(REG_AUDIO_ASRC_COFF_BASE + 0x14 + (asrc) * 0xb0 + ((coef1) << 2)) /* asrc[0-1], coef1[0-31] */

enum
{
    FLD_ASRC_HB1_COEF = BIT_RNG(0, 25),
};

#define reg_audio_asrc_hb2_coef(asrc, coef2) REG_ADDR32(REG_AUDIO_ASRC_COFF_BASE + 0x94 + (asrc) * 0xb0 + ((coef2) << 2)) /* asrc[0-1], coef2[0-6] */

enum
{
    FLD_ASRC_HB2_COEF = BIT_RNG(0, 25),
};

#define reg_audio_asrc_int_next_update(asrc)  REG_ADDR8(REG_AUDIO_ASRC_COFF_BASE + 0x160 + (asrc))         /* asrc[0-3] */

#define reg_audio_asrc_frac_next_update(asrc) REG_ADDR32(REG_AUDIO_ASRC_COFF_BASE + 0x164 + ((asrc) << 2)) /* asrc[0-3] */

enum
{
    FLD_ASRC_FRAC_NEXT_UPDATE = BIT_RNG(0, 26),
};

#define reg_audio_asrc_set_int_frac REG_ADDR8(REG_AUDIO_ASRC_COFF_BASE + 0x16c)

enum
{
    FLD_ASRC_SET0_INT_FEAC = BIT(0),
    FLD_ASRC_SET1_INT_FEAC = BIT(1),
    FLD_ASRC_SET2_INT_FEAC = BIT(2),
    FLD_ASRC_SET3_INT_FEAC = BIT(3),
};

#define reg_audio_asrc_int_next_rd(asrc)  REG_ADDR8(REG_AUDIO_ASRC_COFF_BASE + 0x170 + (asrc))         /* asrc[0-3] */

#define reg_audio_asrc_frac_next_rd(asrc) REG_ADDR32(REG_AUDIO_ASRC_COFF_BASE + 0x174 + ((asrc) << 2)) /* asrc[0-3] */

enum
{
    FLD_ASRC_FRAC_NEXT_RD = BIT_RNG(0, 26),
};

/**************************************************** AUDIO DMA/FIFO register *****************************************************************/
#define reg_audio_dma_tx_fifo_trig_num(fifo) REG_ADDR8(REG_AUDIO_DMA_BASE + (fifo)) /* fifo[0-3] */

enum
{
    FLD_TX_FIFO_TRIG_NUM = BIT_RNG(0, 4),
};

#define reg_audio_dma_rx_fifo_trig_num(fifo) REG_ADDR8(REG_AUDIO_DMA_BASE + 0x04 + (fifo)) /* fifo[0-3] */

enum
{
    FLD_RX_FIFO_TRIG_NUM = BIT_RNG(0, 4),
};

#define reg_audio_dma_fifo_clr REG_ADDR8(REG_AUDIO_DMA_BASE + 0x08)

enum
{
    FLD_TX_FIFO0_CLR = BIT(0),
    FLD_TX_FIFO1_CLR = BIT(1),
    FLD_TX_FIFO2_CLR = BIT(2),
    FLD_TX_FIFO3_CLR = BIT(3),
    FLD_RX_FIFO0_CLR = BIT(4),
    FLD_RX_FIFO1_CLR = BIT(5),
    FLD_RX_FIFO2_CLR = BIT(6),
    FLD_RX_FIFO3_CLR = BIT(7),
};

#define reg_audio_dma_tx_fifo_num(fifo) REG_ADDR8(REG_AUDIO_DMA_BASE + 0x09 + (fifo)) /* fifo[0-3] */

enum
{
    FLD_TX_FIFO_NUM = BIT_RNG(0, 4),
};

#define reg_audio_dma_rx_fifo_num(fifo) REG_ADDR8(REG_AUDIO_DMA_BASE + 0x0d + (fifo)) /* fifo[0-3] */

enum
{
    FLD_RX_FIFO_NUM = BIT_RNG(0, 4),
};

#define reg_audio_dma_ptr_en REG_ADDR8(REG_AUDIO_DMA_BASE + 0x11)

enum
{
    FLD_TX_FIFO0_RPTR_EN = BIT(0),
    FLD_TX_FIFO1_RPTR_EN = BIT(1),
    FLD_TX_FIFO2_RPTR_EN = BIT(2),
    FLD_TX_FIFO3_RPTR_EN = BIT(3),
    FLD_RX_FIFO0_WPTR_EN = BIT(4),
    FLD_RX_FIFO1_WPTR_EN = BIT(5),
    FLD_RX_FIFO2_WPTR_EN = BIT(6),
    FLD_RX_FIFO3_WPTR_EN = BIT(7),
};

#define reg_audio_dma_irq_st REG_ADDR8(REG_AUDIO_DMA_BASE + 0x12)

enum
{
    FLD_TX_FIFO0_IRQ_ST = BIT(0), /**< W1C */
    FLD_TX_FIFO1_IRQ_ST = BIT(1), /**< W1C */
    FLD_TX_FIFO2_IRQ_ST = BIT(2), /**< W1C */
    FLD_TX_FIFO3_IRQ_ST = BIT(3), /**< W1C */
    FLD_RX_FIFO0_IRQ_ST = BIT(4), /**< W1C */
    FLD_RX_FIFO1_IRQ_ST = BIT(5), /**< W1C */
    FLD_RX_FIFO2_IRQ_ST = BIT(6), /**< W1C */
    FLD_RX_FIFO3_IRQ_ST = BIT(7), /**< W1C */
};

#define reg_audio_dma_irq_en REG_ADDR8(REG_AUDIO_DMA_BASE + 0x13)

enum
{
    FLD_TX_FIFO0_IRQ_EM = BIT(0),
    FLD_TX_FIFO1_IRQ_EM = BIT(1),
    FLD_TX_FIFO2_IRQ_EM = BIT(2),
    FLD_TX_FIFO3_IRQ_EM = BIT(3),
    FLD_RX_FIFO0_IRQ_EM = BIT(4),
    FLD_RX_FIFO1_IRQ_EM = BIT(5),
    FLD_RX_FIFO2_IRQ_EM = BIT(6),
    FLD_RX_FIFO3_IRQ_EM = BIT(7),
};

#define reg_audio_dma_tx_rptr(fifo)  REG_ADDR16(REG_AUDIO_DMA_BASE + 0x14 + (fifo) * 0x0c) /* fifo[0-3] */
#define reg_audio_dma_tx_max(fifo)   REG_ADDR16(REG_AUDIO_DMA_BASE + 0x16 + (fifo) * 0x0c) /* fifo[0-3] */
#define reg_audio_dma_tx_th(fifo)    REG_ADDR16(REG_AUDIO_DMA_BASE + 0x18 + (fifo) * 0x0c) /* fifo[0-3] */

#define reg_audio_dma_rx_wptr(fifo)  REG_ADDR16(REG_AUDIO_DMA_BASE + 0x1a + (fifo) * 0x0c) /* fifo[0-3] */
#define reg_audio_dma_rx_max(fifo)   REG_ADDR16(REG_AUDIO_DMA_BASE + 0x1c + (fifo) * 0x0c) /* fifo[0-3] */
#define reg_audio_dma_rx_th(fifo)    REG_ADDR16(REG_AUDIO_DMA_BASE + 0x1e + (fifo) * 0x0c) /* fifo[0-3] */

#define reg_audio_dma_txfifo_dr_mode REG_ADDR8(REG_AUDIO_DMA_BASE + 0x44)

enum
{
    FLD_TX_FIFO0_DR_MODE = BIT(0),
    FLD_TX_FIFO1_DR_MODE = BIT(1),
    FLD_TX_FIFO2_DR_MODE = BIT(2),
    FLD_TX_FIFO3_DR_MODE = BIT(3),
};

#define reg_audio_dma_fifo_status REG_ADDR8(REG_AUDIO_DMA_BASE + 0x45)

enum
{
    FLD_TX_FIFO0_UNDERRUN = BIT(0),
    FLD_TX_FIFO1_UNDERRUN = BIT(1),
    FLD_TX_FIFO2_UNDERRUN = BIT(2),
    FLD_TX_FIFO3_UNDERRUN = BIT(3),
    FLD_RX_FIFO0_OVERRUN  = BIT(4),
    FLD_RX_FIFO1_OVERRUN  = BIT(5),
    FLD_RX_FIFO2_OVERRUN  = BIT(6),
    FLD_RX_FIFO3_OVERRUN  = BIT(7),
};
#endif

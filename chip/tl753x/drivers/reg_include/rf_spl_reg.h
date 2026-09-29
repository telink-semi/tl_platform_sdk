/********************************************************************************************************
 * @file    rf_spl_reg.h
 *
 * @brief   This is the header file for tl753x
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

#ifndef RF_SPL_REG_H
#define RF_SPL_REG_H

#include "soc.h"
/* ====================== Register group base address ====================== */
#define REG_SPL_BB_BASE_ADDR 0xD4402000
#define REG_SPL_LL_BASE_ADDR 0xD4402100
#define REG_SPL_DMA_BASE_ADDR 0xD4402200

// #define REG_TL_MODEM_BASE_ADDR 0xD4170400
// #define REG_TL_RADIO_BASE_ADDR 0xD4170600
/* ========================= Register definition ========================= */


#define reg_rf_spl_mdm_cfg0        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x13C)

enum
{
    FLD_RF_SPL_DEM_DC_ALPHA_H = BIT(0),
    FLD_RF_SPL_DEM_PILOT_INTERVAL = BIT_RNG(1, 2),
    FLD_RF_SPL_FRAME_TYPE = BIT_RNG(3, 4),
    FLD_RF_SPL_FRAME_PSK_MAN_VAL = BIT_RNG(5, 6),
    FLD_RF_SPL_RX_CG_EN_MAN   = BIT(7),
};


#define reg_rf_spl_mdm_cfg1        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x13D)


#define reg_rf_spl_mdm_rx_cfg0        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x13E)

enum
{
    FLD_RF_SPL_DEM_STO_COMP = BIT_RNG(0, 4),
    FLD_RF_SPL_FRAME_PSK_MAN_EN = BIT(5),
    FLD_RF_SPL_DEM_POSTRK_EN = BIT(6),
    FLD_RF_SPL_HS_SYNC_DLY_EN = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg1        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x13F)

enum
{
    FLD_RF_SPL_PDET_PWR_THD = BIT_RNG(0, 5),
    FLD_RF_SPL_PDET_DC_DLY = BIT_RNG(6, 7),
};


#define reg_rf_spl_mdm_rx_cfg2        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x140)


#define reg_rf_spl_mdm_rx_cfg3        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x141)

enum
{
    FLD_RF_SPL_PDET_CORR_THD_H = BIT_RNG(0, 2),
    FLD_RF_SPL_PDET_DAGC_HIGH_THD = BIT_RNG(3, 7),
};


#define reg_rf_spl_mdm_rx_cfg4        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x142)

enum
{
    FLD_RF_SPL_PDET_HD_THD = BIT_RNG(0, 6),
    FLD_RF_SPL_RX_POLAR_SUPPORT_OFF = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg5        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x143)

enum
{
    FLD_RF_SPL_PDET_DAGC_DCO_THD = BIT_RNG(0, 5),
    FLD_RF_SPL_PRIVATE_MODE = BIT(6),
    FLD_RF_SPL_F34_SYNC_EXTEND_EN = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg6        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x144)

enum
{
    FLD_RF_SPL_PDET_DAGC_LOW_THD = BIT_RNG(0, 4),
    FLD_RF_SPL_PDET_SYM_OFFSET = BIT_RNG(5, 7),
};


#define reg_rf_spl_mdm_rx_cfg7        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x145)

enum
{
    FLD_RF_SPL_PDET_DAGC_RSSI_ALPHA = BIT_RNG(0, 3),
    FLD_RF_SPL_PDET_SYNC_PRE_NUM = BIT_RNG(4, 6),
    FLD_RF_SPL_GFSK_TLMDM_EN = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg8        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x146)

enum
{
    FLD_RF_SPL_PDET_DCO_DLY_CYC = BIT_RNG(0, 7),
};


#define reg_rf_spl_mdm_rx_cfg9        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x147)

enum
{
    FLD_RF_SPL_PDET_DCO_DLY_EN = BIT(0),
    FLD_RF_SPL_PDET_CORR_THD_H_19 = BIT(1),
    FLD_RF_SPL_R_RATE_DLY_SEL = BIT_RNG(2, 5),
    FLD_RF_SPL_R_TX_SPL_EN    = BIT(6),
    FLD_RF_SPL_R_TX_SPL_AUTO  = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg10        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x148)

enum
{
    FLD_RF_SPL_R_TX_LPF_SEL   = BIT(0),
    FLD_RF_SPL_R_TX_LPF2_BYPASS = BIT(1),
    FLD_RF_SPL_R_TX_LPF3_BYPASS = BIT(2),
    FLD_RF_SPL_R_TX_AAF2_BYPASS0 = BIT(3),
    FLD_RF_SPL_R_TX_AAF2_BYPASS1 = BIT(4),
    FLD_RF_SPL_R_TX_LPF_LS_EN = BIT(5),
    FLD_RF_SPL_PILOT_DC_ALPHA_H = BIT(7),
};


#define reg_rf_spl_mdm_rx_cfg11        REG_ADDR8(REG_TL_MODEM_BASE_ADDR + 0x149)

enum
{
    FLD_RF_SPL_PILOT_DC_ALPHA = BIT_RNG(0, 7),
};


#define reg_rf_spl_mode_cfg_rx1_1        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x21)

enum
{
    FLD_RF_SPL_RX_MODE        = BIT(5),
};


#define reg_rf_spl_mode_cfg_tx1_0        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x22)

enum
{
    FLD_RF_SPL_BLE_MODE_TX    = BIT(0),
};


#define reg_rf_spl_burst_cfg_txrx_0        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x28)

enum
{
    FLD_RF_SPL_CHNL_NUM       = BIT_RNG(0, 7),
};


#define reg_rf_spl_burst_cfg_txrx_1        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x29)

enum
{
    FLD_RF_SPL_CH_NUM_LL_SEL  = BIT(0),
    FLD_RF_SPL_TX_EN_PIF      = BIT(1),
    FLD_RF_SPL_RX_EN_PIF      = BIT(2),
    FLD_RF_SPL_RX_TIM_SRQ_SEL_TESQ = BIT(3),
    FLD_RF_SPL_TX_TIM_SRQ_SEL_TESQ = BIT(4),
    FLD_RF_SPL_HOLD1          = BIT_RNG(5, 7),
};

#define reg_rf_spl_mode_cfg_tx3_0        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x3C)

enum
{
    FLD_RF_SPL_TX_IQ_MODE_EN_BLE = BIT(7),
};

#define reg_rf_spl_txrx_dbg3_0        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x44)

enum
{
    FLD_RF_SPL_CHNL_FREQ_L    = BIT_RNG(1, 7),
};


#define reg_rf_spl_txrx_dbg3_1        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x45)

enum
{
    FLD_RF_SPL_CHNL_FREQ_H    = BIT_RNG(0, 4),
};

#define reg_rf_spl_hsspl_ctrl_0        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x1E0)

enum
{
    FLD_RF_SPL_RX_HS_48M_EN   = BIT(0),
    FLD_RF_SPL_RX_SPL_EN      = BIT(1),
    FLD_RF_SPL_RXC_MODE_SEL   = BIT_RNG(2, 3),
};


#define reg_rf_spl_hsspl_ctrl_1        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x1E1)

enum
{
    FLD_RF_SPL_TX_HS_48M_EN   = BIT(0),
    FLD_RF_SPL_TX_SPL_EN      = BIT(1),
    FLD_RF_SPL_TXC_MODE_SEL   = BIT_RNG(2, 3),
    FLD_RF_SPL_TX_LS_24M_EN   = BIT(4),
    FLD_RF_SPL_RX_HP_EN       = BIT(5),
    FLD_RF_SPL_TX_DOWN_SAMPLE_EN = BIT(6),
};

#define reg_rf_spl_hsspl_ctrl_2        REG_ADDR8(REG_TL_RADIO_BASE_ADDR + 0x1E2)

enum
{
    FLD_RF_SPL_RXC_MODE_OW     = BIT(0),
    FLD_RF_SPL_TRX_BPS_OW      = BIT(1),
    FLD_RF_SPL_TRX_FAST_OW     = BIT(3),
    FLD_RF_SPL_RXC_SWRST_HS_OW = BIT(7),
};

/* ========================= Register definition ========================= */
#define reg_rf_spl_txdma_adr   0xd4402000
#define reg_rf_spl_tx_buf0        REG_ADDR8(REG_SPL_BB_BASE_ADDR)

enum
{
    FLD_RF_SPL_TX_BUFFER_0    = BIT_RNG(0, 7),
};


#define reg_rf_spl_tx_buf1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x01)

enum
{
    FLD_RF_SPL_TX_BUFFER_1    = BIT_RNG(0, 7),
};


#define reg_rf_spl_tx_buf2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x02)

enum
{
    FLD_RF_SPL_TX_BUFFER_2    = BIT_RNG(0, 7),
};


#define reg_rf_spl_tx_buf3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x03)

enum
{
    FLD_RF_SPL_TX_BUFFER_3    = BIT_RNG(0, 7),
};

#define reg_rf_spl_rxdma_adr   0xd4402004
#define reg_rf_spl_rx_buf0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x04)

enum
{
    FLD_RF_SPL_RX_BUFFER_0    = BIT_RNG(0, 7),
};


#define reg_rf_spl_rx_buf1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x05)

enum
{
    FLD_RF_SPL_RX_BUFFER_1    = BIT_RNG(0, 7),
};


#define reg_rf_spl_rx_buf2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x06)

enum
{
    FLD_RF_SPL_RX_BUFFER_2    = BIT_RNG(0, 7),
};


#define reg_rf_spl_rx_buf3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x07)

enum
{
    FLD_RF_SPL_RX_BUFFER_3    = BIT_RNG(0, 7),
};


#define reg_rf_spl_soft_reset        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x08)

enum
{
    FLD_RF_SPL_R_SPL_SOFT_RST_P = BIT(0),
    FLD_RF_SPL_R_SPL_CRYPT_SOFT_RST_P = BIT(1),
    FLD_RF_SPL_R_SPL_POLAR_SOFT_RST_P = BIT(2),
    FLD_RF_SPL_R_SPL_TXFIFO_CLR_P = BIT(3),
    FLD_RF_SPL_R_SPL_RXFIFO_CLR_P = BIT(4),
    FLD_RF_SPL_R_SPL_LLRFIFO_CLR_P = BIT(5),
};


#define reg_rf_spl_frame_indicator        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x09)

enum
{
    FLD_RF_SPL_R_SPL_FRAME_1   = BIT(0),
    FLD_RF_SPL_R_SPL_FRAME_2   = BIT(1),
    FLD_RF_SPL_R_SPL_FRAME_3   = BIT(2),
    FLD_RF_SPL_R_SPL_FRAME_4   = BIT(3),
    FLD_RF_SPL_R_SPL_FRAME_ALL = BIT_RNG(0, 3),
};


#define reg_rf_spl_frame_ctrl0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0A)

enum
{
    FLD_RF_SPL_R_SPL_CTRL_TYPE = BIT_RNG(0, 4),
};


#define reg_rf_spl_frame_ctrl1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0B)

enum
{
    FLD_RF_SPL_R_SPL_SYMB_RATE = BIT_RNG(0, 1),
    FLD_RF_SPL_R_SPL_PILOT_INTERVAL = BIT_RNG(2, 3),
    FLD_RF_SPL_R_SPL_TX_SERPAR_IF = BIT(4),
    FLD_RF_SPL_R_SPL_TX_SWAP  = BIT(5),
    FLD_RF_SPL_R_SPL_RX_FOOTER_EN = BIT(6),
};


#define reg_rf_spl_trx_pldlen0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0C)

enum
{
    FLD_RF_SPL_R_SPL_TRX_PLDLEN_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_trx_pldlen1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0D)

enum
{
    FLD_RF_SPL_R_SPL_TRX_PLDLEN_H = BIT_RNG(0, 2),
};


#define reg_rf_spl_whiten_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0E)

enum
{
    FLD_RF_SPL_R_SPL_WHITEN_INIT = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_WHITEN_ENABLE = BIT(7),
};


#define reg_rf_spl_dp_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x0F)

enum
{
    FLD_RF_SPL_R_SPL_CRC_ENABLE = BIT(0),
    FLD_RF_SPL_R_SPL_CRC_TYPE = BIT(1),
    FLD_RF_SPL_R_SPL_HEC_INIT_MAN = BIT(2),
    FLD_RF_SPL_R_SPL_POLAR_ENABLE_MAN = BIT(3),
    FLD_RF_SPL_R_SPL_POLAR_ENABLE = BIT(4),
    FLD_RF_SPL_R_SPL_DP_BYPASS_EN = BIT(5),
    FLD_RF_SPL_R_SPL_POLAR_BYPASS_EN = BIT(6),
    FLD_RF_SPL_R_SPL_POLAR_AFTER_WHITEN_EN = BIT(7),
};


#define reg_rf_spl_crc_init0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x10)

enum
{
    FLD_RF_SPL_R_SPL_CRC_INIT_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_crc_init1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x11)

enum
{
    FLD_RF_SPL_R_SPL_CRC_INIT_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_crc_init2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x12)

enum
{
    FLD_RF_SPL_R_SPL_CRC_INIT_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_crc_init3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x13)

enum
{
    FLD_RF_SPL_R_SPL_CRC_INIT_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_datseg_crc_init0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x14)

enum
{
    FLD_RF_SPL_R_SPL_DATSEG_CRC_INIT_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_datseg_crc_init1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x15)

enum
{
    FLD_RF_SPL_R_SPL_DATSEG_CRC_INIT_M = BIT_RNG(0, 7),
};


#define reg_rf_spl_datseg_crc_init2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x16)

enum
{
    FLD_RF_SPL_R_SPL_DATSEG_CRC_INIT_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_hec_init0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x17)

enum
{
    FLD_RF_SPL_R_SPL_HEC_INIT_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_hec_init1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x18)

enum
{
    FLD_RF_SPL_R_SPL_HEC_INIT_M = BIT_RNG(0, 7),
};


#define reg_rf_spl_hec_init2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x19)

enum
{
    FLD_RF_SPL_R_SPL_HEC_INIT_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_llid0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1A)

enum
{
    FLD_RF_SPL_R_SPL_LLID_L   = BIT_RNG(0, 7),
};


#define reg_rf_spl_llid1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1B)

enum
{
    FLD_RF_SPL_R_SPL_LLID_M   = BIT_RNG(0, 7),
};


#define reg_rf_spl_llid2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1C)

enum
{
    FLD_RF_SPL_R_SPL_LLID_H   = BIT_RNG(0, 7),
};


#define reg_rf_spl_bch_init0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1D)

enum
{
    FLD_RF_SPL_R_SPL_BCH_INIT_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_bch_init1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1E)

enum
{
    FLD_RF_SPL_R_SPL_BCH_INIT_M1 = BIT_RNG(0, 7),
};


#define reg_rf_spl_bch_init2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x1F)

enum
{
    FLD_RF_SPL_R_SPL_BCH_INIT_M2 = BIT_RNG(0, 7),
};


#define reg_rf_spl_bch_init3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x20)

enum
{
    FLD_RF_SPL_R_SPL_BCH_INIT_M3 = BIT_RNG(0, 7),
};


#define reg_rf_spl_bch_init4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x21)

enum
{
    FLD_RF_SPL_R_SPL_BCH_INIT_H = BIT_RNG(0, 6),
};


#define reg_rf_spl_m_init        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x22)

enum
{
    FLD_RF_SPL_R_SPL_M_INIT   = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_M_INIT_EN = BIT(7),
};


#define reg_rf_spl_m_seqn        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x23)

enum
{
    FLD_RF_SPL_R_SPL_M_SEQN   = BIT_RNG(0, 2),
    FLD_RF_SPL_R_SPL_BCH_IN_ORD = BIT(3),
    FLD_RF_SPL_R_SPL_BCH_OUT_ORD = BIT(4),
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_EN = BIT(7),
};


#define reg_rf_spl_syncword_man_word0   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x24)
#define reg_rf_spl_syncword_man_word1   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x28)
#define reg_rf_spl_syncword_man0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x24)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x25)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M1 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x26)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M2 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x27)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M3 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x28)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M4 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x29)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M5 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2A)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_M6 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword_man7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2B)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_MAN_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_datseg_man0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2C)

enum
{
    FLD_RF_SPL_R_SPL_N1024_MAN = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_DATSEG_MAN_EN = BIT(7),
};


#define reg_rf_spl_datseg_man1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2D)

enum
{
    FLD_RF_SPL_R_SPL_N512_MAN = BIT_RNG(0, 1),
    FLD_RF_SPL_R_SPL_N256_MAN = BIT_RNG(2, 3),
    FLD_RF_SPL_R_SPL_N128_MAN = BIT_RNG(4, 5),
    FLD_RF_SPL_R_SPL_N64_MAN  = BIT_RNG(6, 7),
};


#define reg_rf_spl_datseg_man2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2E)

enum
{
    FLD_RF_SPL_R_SPL_K64_FINAL_MAN = BIT_RNG(0, 6),
};


#define reg_rf_spl_datseg_man3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x2F)

enum
{
    FLD_RF_SPL_R_SPL_KR_MAN_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_datseg_man4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x30)

enum
{
    FLD_RF_SPL_R_SPL_KR_MAN_H = BIT_RNG(0, 2),
};


#define reg_rf_spl_datseg_man5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x31)

enum
{
    FLD_RF_SPL_R_SPL_PAD_NUM_MAN = BIT_RNG(0, 5),
};


#define reg_rf_spl_clk_select        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x32)

enum
{
    FLD_RF_SPL_R_SPL_CLOCK_SEL = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxdma_burst        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x33)

enum
{
    FLD_RF_SPL_R_SPL_RXDMA_BURST_SIZE = BIT_RNG(0, 1),
};


#define reg_rf_spl_debug_ctrl0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x34)

enum
{
    FLD_RF_SPL_R_SPL_DBG0_SEL = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DBG0_EN  = BIT(7),
};


#define reg_rf_spl_debug_ctrl1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x35)

enum
{
    FLD_RF_SPL_R_SPL_DBG1_SEL = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DBG1_EN  = BIT(7),
};


#define reg_rf_spl_debug_ctrl2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x36)

enum
{
    FLD_RF_SPL_R_SPL_DBG2_SEL = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DBG2_EN  = BIT(7),
};


#define reg_rf_spl_debug_ctrl3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x37)

enum
{
    FLD_RF_SPL_R_SPL_DBG3_SEL = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DBG3_EN  = BIT(7),
};


#define reg_rf_spl_debug_port0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x38)

enum
{
    FLD_RF_SPL_R_SPL_DBG0     = BIT_RNG(0, 7),
};


#define reg_rf_spl_debug_port1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x39)

enum
{
    FLD_RF_SPL_R_SPL_DBG1     = BIT_RNG(0, 7),
};


#define reg_rf_spl_debug_port2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3A)

enum
{
    FLD_RF_SPL_R_SPL_DBG2     = BIT_RNG(0, 7),
};


#define reg_rf_spl_debug_port3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3B)

enum
{
    FLD_RF_SPL_R_SPL_DBG3     = BIT_RNG(0, 7),
};


#define reg_rf_spl_fifo_indicator        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3C)

enum
{
    FLD_RF_SPL_TXFIFO_FULL = BIT(0),
    FLD_RF_SPL_TXFIFO_EMPTY = BIT(1),
    FLD_RF_SPL_RXFIFO_FULL = BIT(2),
    FLD_RF_SPL_RXFIFO_EMPTY = BIT(3),
    FLD_RF_SPL_LLRFIFO_FULL = BIT(4),
    FLD_RF_SPL_LLRFIFO_EMPTY = BIT(5),
};


#define reg_rf_spl_error_indicator        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3D)

typedef enum
{
    FLD_RF_SPL_DP_CRC_ERROR = BIT(0),
    FLD_RF_SPL_DP_HEC_ERROR = BIT(1),
    FLD_RF_SPL_DP_MIC_ERROR = BIT(2),
    FLD_RF_SPL_DP_DATSEG_CRC_ERROR = BIT(3),
    FLD_RF_SPL_TXCRYPT_ERROR = BIT(4),
    FLD_RF_SPL_RXCRYPT_ERROR = BIT(5),
    FLD_RF_SPL_DP_PLDLEN_ERROR = BIT(6),
    FLD_RF_SPL_DP_MCS_ERROR = BIT(7),
}rf_spl_error_e;


#define reg_rf_spl_fsm_indicator0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3E)

enum
{
    FLD_RF_SPL_PKTCTRL_CS = BIT_RNG(0, 3),
    FLD_RF_SPL_SEGCRC_CS  = BIT_RNG(4, 5),
};


#define reg_rf_spl_fsm_indicator1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x3F)

enum
{
    FLD_RF_SPL_DP_CS      = BIT_RNG(0, 2),
    FLD_RF_SPL_POLAR_CS   = BIT_RNG(3, 7),
};


#define reg_rf_spl_syncword0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x40)

enum
{
    FLD_RF_SPL_R_SPL_SYNCGEN_START_P = BIT(0),
    FLD_RF_SPL_R_SPL_SYNCGEN_DONE_CLR_P = BIT(1),
    FLD_RF_SPL_SYNCWORD_VALID = BIT(2),
};


#define reg_rf_spl_syncword1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x41)

enum
{
    FLD_RF_SPL_SYNCWORD_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x42)

enum
{
    FLD_RF_SPL_SYNCWORD_M1 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x43)

enum
{
    FLD_RF_SPL_SYNCWORD_M2 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x44)

enum
{
    FLD_RF_SPL_SYNCWORD_M3 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x45)

enum
{
    FLD_RF_SPL_SYNCWORD_M4 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x46)

enum
{
    FLD_RF_SPL_SYNCWORD_M5 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x47)

enum
{
    FLD_RF_SPL_SYNCWORD_M6 = BIT_RNG(0, 7),
};


#define reg_rf_spl_syncword8        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x48)

enum
{
    FLD_RF_SPL_SYNCWORD_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_polar_datseg0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x49)

enum
{
    FLD_RF_SPL_N1024      = BIT_RNG(0, 6),
    FLD_RF_SPL_DATSEG_DONE = BIT(7),
};


#define reg_rf_spl_polar_datseg1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4A)

enum
{
    FLD_RF_SPL_N512       = BIT_RNG(0, 1),
    FLD_RF_SPL_N256       = BIT_RNG(2, 3),
    FLD_RF_SPL_N128       = BIT_RNG(4, 5),
    FLD_RF_SPL_N64        = BIT_RNG(6, 7),
};


#define reg_rf_spl_polar_datseg2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4B)

enum
{
    FLD_RF_SPL_K64_FINAL  = BIT_RNG(0, 6),
};


#define reg_rf_spl_polar_datseg3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4C)

enum
{
    FLD_RF_SPL_KR_L       = BIT_RNG(0, 7),
};


#define reg_rf_spl_polar_datseg4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4D)

enum
{
    FLD_RF_SPL_KR_H       = BIT_RNG(0, 2),
};


#define reg_rf_spl_polar_datseg5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4E)

enum
{
    FLD_RF_SPL_PAD_NUM    = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DATSEG_DONE_CLR_P = BIT(6),
    FLD_RF_SPL_R_SPL_DATSEG_START_P = BIT(7),
};


#define reg_rf_spl_tx_chn        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x4F)

enum
{
    FLD_RF_SPL_R_SPL_TX_CHN   = BIT_RNG(0, 2),
};


#define reg_rf_spl_preamble_ctrl0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x50)

enum
{
    FLD_RF_SPL_R_SPL_PREAMBLE_LEN_MAN = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_PREAMBLE_LEN_MAN_EN = BIT(7),
};


#define reg_rf_spl_preamble_ctrl1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x51)

enum
{
    FLD_RF_SPL_R_SPL_PREAMBLE_MAN = BIT_RNG(0, 7),
};


#define reg_rf_spl_preamble_ctrl2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x52)

enum
{
    FLD_RF_SPL_R_SPL_PREAMBLE_MAN_EN = BIT(0),
};


#define reg_rf_spl_synclen_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x53)

enum
{
    FLD_RF_SPL_R_SPL_SYNCWORD_LEN_MAN = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_SYNCWORD_LEN_MAN_EN = BIT(7),
};


#define reg_rf_spl_ctrllen_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x54)

enum
{
    FLD_RF_SPL_R_SPL_CTRLFIELD_LEN_MAN = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_CTRLFIELD_LEN_MAN_EN = BIT(7),
};


#define reg_rf_spl_datalen_ctrl0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x55)

enum
{
    FLD_RF_SPL_R_SPL_DATAFIELD_LEN_MAN_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_datalen_ctrl1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x56)

enum
{
    FLD_RF_SPL_R_SPL_DATAFIELD_LEN_MAN_H = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DATAFIELD_LEN_MAN_EN_H = BIT(7),
};


#define reg_rf_spl_trailer_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x57)

enum
{
    FLD_RF_SPL_R_SPL_TRAILER_LEN = BIT_RNG(0, 3),
    FLD_RF_SPL_R_SPL_TRAILER_EN = BIT(7),
};


#define reg_rf_spl_fh_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x58)

enum
{
    FLD_RF_SPL_R_SPL_FH_START_P = BIT(0),
    FLD_RF_SPL_R_SPL_FH_EN    = BIT(1),
    FLD_RF_SPL_R_SPL_FH_REMAP_EN = BIT(2),
    FLD_RF_SPL_R_SPL_FH_PARA2_SEL = BIT(3),
    FLD_RF_SPL_R_SPL_FH_SEL   = BIT_RNG(4, 5),
};


#define reg_rf_spl_fh_status        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x59)

enum
{
    FLD_RF_SPL_FH_STATUS  = BIT_RNG(0, 1),
    FLD_RF_SPL_R_SPL_FH_STATUS_CLR_P = BIT(7),
};


#define reg_rf_spl_fh_ch_idx        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5A)

enum
{
    FLD_RF_SPL_DATA_CH_IDX = BIT_RNG(0, 7),
};


#define reg_rf_spl_fh_map_idx        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5B)

enum
{
    FLD_RF_SPL_FH_MAPPING_IDX = BIT_RNG(0, 7),
};


#define reg_rf_spl_fh_prn         REG_ADDR16(REG_SPL_BB_BASE_ADDR + 0x5c)
#define reg_rf_spl_fh_prn0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5C)

enum
{
    FLD_RF_SPL_FH_PRN_L   = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_prn1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5D)

enum
{
    FLD_RF_SPL_FH_PRN_H   = BIT_RNG(0, 7),
};


#define reg_rf_spl_fh_slot_cnt         REG_ADDR16(REG_SPL_BB_BASE_ADDR + 0x5e)
#define reg_rf_spl_fh_slot_cnt0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5E)

enum
{
    FLD_RF_SPL_R_SPL_SLOT_CNT_L = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_slot_cnt1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x5F)

enum
{
    FLD_RF_SPL_R_SPL_SLOT_CNT_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_fh_chmap_word0   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x60)
#define reg_rf_spl_fh_chmap_word1   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x64)
#define reg_rf_spl_fh_chmap_word2   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x68)
#define reg_rf_spl_fh_chmap_word3   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x6c)
#define reg_rf_spl_fh_chmap_word4   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x70)
#define reg_rf_spl_fh_chmap_word5   REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x74)
#define reg_rf_spl_fh_chmap_byte6   REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x78)
#define reg_rf_spl_fh_chmap_hw2     REG_ADDR16(REG_SPL_BB_BASE_ADDR + 0x68)
#define reg_rf_spl_fh_chmap0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x60)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_L = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x61)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M1 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x62)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M2 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x63)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M3 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x64)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M4 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x65)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M5 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x66)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M6 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x67)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M7 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap8        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x68)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M8 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap9        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x69)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M9 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap10        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6A)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M10 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap11        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6B)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M11 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap12        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6C)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M12 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap13        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6D)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M13 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap14        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6E)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M14 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap15        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x6F)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M15 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap16        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x70)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M16 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap17        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x71)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M17 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap18        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x72)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M18 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap19        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x73)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M19 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap20        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x74)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M20 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap21        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x75)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M21 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap22        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x76)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M22 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap23        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x77)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_M23 = BIT_RNG(0, 7),
};

#define reg_rf_spl_fh_chmap24        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x78)

enum
{
    FLD_RF_SPL_R_SPL_LLCHMAP_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_ctrlfield_info0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x79)

enum
{
    FLD_RF_SPL_CTRLFIELD_INFO_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_ctrlfield_info1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7A)

enum
{
    FLD_RF_SPL_CTRLFIELD_INFO_M1 = BIT_RNG(0, 7),
};


#define reg_rf_spl_ctrlfield_info2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7B)

enum
{
    FLD_RF_SPL_CTRLFIELD_INFO_M2 = BIT_RNG(0, 7),
};


#define reg_rf_spl_ctrlfield_info3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7C)

enum
{
    FLD_RF_SPL_CTRLFIELD_INFO_M3 = BIT_RNG(0, 7),
};


#define reg_rf_spl_ctrlfield_info4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7D)

enum
{
    FLD_RF_SPL_CTRLFIELD_INFO_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_crypt_ctrl        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7E)

enum
{
    FLD_RF_SPL_R_SPL_CRYPT_ENABLE = BIT(0),
    FLD_RF_SPL_R_SPL_CRYPT_ALGO = BIT(1),
    FLD_RF_SPL_R_SPL_CRYPT_MODE = BIT(2),
    FLD_RF_SPL_R_SPL_CRYPT_DSB = BIT(3),
    FLD_RF_SPL_R_SPL_MIC_DSB  = BIT(4),
    FLD_RF_SPL_R_SPL_MST_SLV  = BIT(5),
};


#define reg_rf_spl_crypt_clkslot0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x7F)

enum
{
    FLD_RF_SPL_R_SPL_CLK_SLOT_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_crypt_clkslot1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x80)

enum
{
    FLD_RF_SPL_R_SPL_CLK_SLOT_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_crypt_clkslot2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x81)

enum
{
    FLD_RF_SPL_R_SPL_CLK_SLOT_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_crypt_clkslot3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x82)

enum
{
    FLD_RF_SPL_R_SPL_CLK_SLOT_H = BIT_RNG(0, 5),
    FLD_RF_SPL_R_SPL_DAYCOUNTER_H = BIT_RNG(6, 7),
};


#define reg_rf_spl_crypt_daycnt        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x83)

enum
{
    FLD_RF_SPL_R_SPL_DAYCOUNTER = BIT_RNG(0, 7),
};


#define reg_rf_spl_crypt_txccmcnt_word0        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x84)
#define reg_rf_spl_crypt_txccmcnt_byte1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x88)
#define reg_rf_spl_crypt_txccmcnt0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x84)
#define reg_rf_spl_crypt_txccmcnt1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x85)
#define reg_rf_spl_crypt_txccmcnt2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x86)
#define reg_rf_spl_crypt_txccmcnt3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x87)
#define reg_rf_spl_crypt_txccmcnt4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x88)

enum
{
    FLD_RF_SPL_R_SPL_TXCCMPKTCNT_H = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_TXCCMPKTCNT_AUTOINC_DSB_H = BIT(7),
};


#define reg_rf_spl_crypt_rxccmcnt_word0        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x8c)
#define reg_rf_spl_crypt_rxccmcnt_byte1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x90) 
#define reg_rf_spl_crypt_rxccmcnt0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x8C)
#define reg_rf_spl_crypt_rxccmcnt1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x8D)
#define reg_rf_spl_crypt_rxccmcnt2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x8E)
#define reg_rf_spl_crypt_rxccmcnt3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x8F)
#define reg_rf_spl_crypt_rxccmcnt4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x90)

enum
{
    FLD_RF_SPL_R_SPL_RXCCMPKTCNT_H = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_RXCCMPKTCNT_AUTOINC_DSB_H = BIT(7),
};


#define reg_rf_spl_crypt_iv_word0        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x94)
#define reg_rf_spl_crypt_iv_word1        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x98)
#define reg_rf_spl_crypt_iv0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x94)
#define reg_rf_spl_crypt_iv1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x95)
#define reg_rf_spl_crypt_iv2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x96)
#define reg_rf_spl_crypt_iv3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x97)
#define reg_rf_spl_crypt_iv4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x98)
#define reg_rf_spl_crypt_iv5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x99)
#define reg_rf_spl_crypt_iv6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9A)
#define reg_rf_spl_crypt_iv7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9B)


#define reg_rf_spl_crypt_sk_word0        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0x9c)
#define reg_rf_spl_crypt_sk_word1        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xa0)
#define reg_rf_spl_crypt_sk_word2        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xa4)
#define reg_rf_spl_crypt_sk_word3        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xa8)
#define reg_rf_spl_crypt_sk0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9C)
#define reg_rf_spl_crypt_sk1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9D)
#define reg_rf_spl_crypt_sk2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9E)
#define reg_rf_spl_crypt_sk3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0x9F)
#define reg_rf_spl_crypt_sk4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA0)
#define reg_rf_spl_crypt_sk5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA1)
#define reg_rf_spl_crypt_sk6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA2)
#define reg_rf_spl_crypt_sk7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA3)
#define reg_rf_spl_crypt_sk8        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA4)
#define reg_rf_spl_crypt_sk9        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA5)
#define reg_rf_spl_crypt_sk10        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA6)
#define reg_rf_spl_crypt_sk11        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA7)
#define reg_rf_spl_crypt_sk12        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA8)
#define reg_rf_spl_crypt_sk13        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xA9)
#define reg_rf_spl_crypt_sk14        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAA)
#define reg_rf_spl_crypt_sk15        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAB)


#define reg_rf_spl_crypt_receive_rxmic        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xac)
#define reg_rf_spl_crypt_receive_rxmic0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAC)
#define reg_rf_spl_crypt_receive_rxmic1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAD)
#define reg_rf_spl_crypt_receive_rxmic2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAE)
#define reg_rf_spl_crypt_receive_rxmic3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xAF)


#define reg_rf_spl_crypt_calculate_rxmic        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xb0)
#define reg_rf_spl_crypt_calculate_rxmic0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB0)
#define reg_rf_spl_crypt_calculate_rxmic1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB1)
#define reg_rf_spl_crypt_calculate_rxmic2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB2)
#define reg_rf_spl_crypt_calculate_rxmic3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB3)


#define reg_rf_spl_crypt_calculate_txmic        REG_ADDR32(REG_SPL_BB_BASE_ADDR + 0xb4)
#define reg_rf_spl_crypt_calculate_txmic0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB4)
#define reg_rf_spl_crypt_calculate_txmic1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB5)
#define reg_rf_spl_crypt_calculate_txmic2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB6)
#define reg_rf_spl_crypt_calculate_txmic3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB7)


#define reg_rf_spl_datseg_crc_error_table0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB8)
#define reg_rf_spl_datseg_crc_error_table1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xB9)
#define reg_rf_spl_datseg_crc_error_table2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBA)
#define reg_rf_spl_datseg_crc_error_table3        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBB)
#define reg_rf_spl_datseg_crc_error_table4        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBC)
#define reg_rf_spl_datseg_crc_error_table5        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBD)
#define reg_rf_spl_datseg_crc_error_table6        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBE)
#define reg_rf_spl_datseg_crc_error_table7        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xBF)
#define reg_rf_spl_datseg_crc_error_table8        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xC0)


#define reg_rf_spl_version        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xC4)

enum
{
    FLD_RF_SPL_R_SPL_VERSION  = BIT(0),
};


#define reg_rf_spl_test_ctrl0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xC5)

enum
{
    FLD_RF_SPL_R_SPL_TXDMA_EN = BIT(0),
    FLD_RF_SPL_R_SPL_TX_TEST_MODE_EN = BIT(1),
    FLD_RF_SPL_R_SPL_TX_TEST_INFINITE = BIT(2),
    FLD_RF_SPL_R_SPL_TX_TEST_DATA_SRC = BIT_RNG(3, 4),
};


#define reg_rf_spl_test_ctrl1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xC6)

enum
{
    FLD_RF_SPL_R_SPL_TX_TEST_DATA = BIT_RNG(0, 7),
};


#define reg_rf_spl_test_ctrl2        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xC7)

enum
{
    FLD_RF_SPL_R_SPL_TX_TEST_START_P = BIT(0),
    FLD_RF_SPL_R_SPL_TX_TEST_STOP_P = BIT(1),
};


#define reg_rf_spl_maxlen        REG_ADDR16(REG_SPL_BB_BASE_ADDR + 0xc8)

enum
{
    FLD_RF_SPL_R_SPL_PLD_MAXLEN = BIT_RNG(0, 10),
};


#define reg_rf_spl_rx_gain        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xCA)


#define reg_rf_spl_rx_rssi        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xCB)


#define reg_rf_spl_polar_pktlen        REG_ADDR16(REG_SPL_BB_BASE_ADDR + 0xcc)

enum
{
    FLD_RF_SPL_POLAR_PKTLEN = BIT_RNG(0, 13),
};


#define reg_rf_spl_empty_pkt_indicator        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xCE)

enum
{
    FLD_RF_SPL_RX_EMPTY_PKT_INDICATOR_FLAG = BIT(0),
};


#define reg_rf_spl_tx_mcs_man        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD0)

enum
{
    FLD_RF_SPL_TX_MCS_MAN = BIT_RNG(0, 3),
    FLD_RF_SPL_TX_MCS_MAN_EN = BIT(7),
};


#define reg_rf_spl_rx_mcs_man        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD1)

enum
{
    FLD_RF_SPL_RX_MCS_MAN = BIT_RNG(0, 3),
    FLD_RF_SPL_RX_MCS_MAN_EN = BIT(7),
};


#define reg_rf_spl_trx_pldlen_man_en        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD2)

enum
{
    FLD_RF_SPL_TX_PLDLEN_MAN = BIT(0),
    FLD_RF_SPL_RX_PLDLEN_MAN = BIT(1),
};


#define reg_rf_spl_rx_empty        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD3)

enum
{
    FLD_RF_SPL_RX_EMPTY_DONE_SEL = BIT(0),
    FLD_RF_SPL_RX_FIXED_PLDLEN = BIT(1),
    FLD_RF_SPL_TRX_PLDLEN_R = BIT(2),
};


#define reg_rf_spl_tx_pldlen_man0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD4)

enum
{
    FLD_RF_SPL_TX_PLDLEN_MAN0 = BIT_RNG(0, 7),
};


#define reg_rf_spl_tx_pldlen_man1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD5)

enum
{
    FLD_RF_SPL_TX_PLDLEN_MAN1 = BIT_RNG(0, 2),
};


#define reg_rf_spl_rx_pldlen_man0        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD6)

enum
{
    FLD_RF_SPL_RX_PLDLEN_MAN0 = BIT_RNG(0, 7),
};


#define reg_rf_spl_rx_pldlen_man1        REG_ADDR8(REG_SPL_BB_BASE_ADDR + 0xD7)

enum
{
    FLD_RF_SPL_RX_PLDLEN_MAN1 = BIT_RNG(0, 2),
};


#define reg_rf_spl_cmd        REG_ADDR8(REG_SPL_LL_BASE_ADDR)

enum
{
    FLD_RF_SPL_R_SPL_CMD   = BIT_RNG(0, 2),
    FLD_RF_SPL_CMD_TRIGGER = BIT(7),
};


#define reg_rf_spl_timeout_enable        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x01)

enum
{
    FLD_RF_SPL_R_SPL_TX_TIMEOUT_EN = BIT(0),
    FLD_RF_SPL_R_SPL_RX_TIMEOUT_EN = BIT(1),
    FLD_RF_SPL_R_SPL_RX_FIRST_TIMEOUT_EN = BIT(2),
    FLD_RF_SPL_R_SPL_FSM_TIMEOUT_EN = BIT(3),
};


#define reg_rf_spl_tx_settle        REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x02)


#define reg_rf_spl_tx_wait          REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x04)


#define reg_rf_spl_rx_settle        REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x06)


#define reg_rf_spl_rx_wait          REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x08)


#define reg_rf_spl_rx_timeout       REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x0a)


#define reg_rf_spl_t1_coex        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x0C)


#define reg_rf_spl_t2_coex        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x0D)


#define reg_rf_spl_rx_first_timeout_l        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x0E)
#define reg_rf_spl_rx_first_timeout_m        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x0F)
#define reg_rf_spl_rx_first_timeout_h        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x10)


#define reg_rf_spl_fsm_l        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x11)
#define reg_rf_spl_fsm_m        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x12)
#define reg_rf_spl_fsm_h        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x13)


#define reg_rf_spl_schedule_time        REG_ADDR32(REG_SPL_LL_BASE_ADDR + 0x14)


#define reg_rf_spl_func_enable        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x18)

enum
{
    FLD_RF_SPL_R_SPL_MD_EN    = BIT(0),
    FLD_RF_SPL_R_SPL_SN_EN    = BIT(1),
    FLD_RF_SPL_R_SPL_NESN_EN  = BIT(2),
    FLD_RF_SPL_R_SPL_CRC2_ERROR_EN = BIT(3),
    FLD_RF_SPL_R_SPL_TXDMA_TRIG_AUTO_EN = BIT(4),
    FLD_RF_SPL_R_SPL_CMD_SCHEDULE_EN = BIT(5),
    FLD_RF_SPL_R_SPL_RXIRQ_REPORT_ALL = BIT(6),
};


#define reg_rf_spl_sn_nesn        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x19)

enum
{
    FLD_RF_SPL_R_SPL_INIT_GTX_SN = BIT(0),
    FLD_RF_SPL_R_SPL_INIT_GTX_NESN = BIT(1),
    FLD_RF_SPL_R_SPL_INIT_GRX_SN = BIT(2),
    FLD_RF_SPL_R_SPL_INIT_GRX_NESN = BIT(3),
    FLD_RF_SPL_R_SPL_INIT_SN_EN = BIT(4),
    FLD_RF_SPL_R_SPL_INIT_NESN_EN = BIT(5),
};


#define reg_rf_spl_trx_en_man        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1A)

enum
{
    FLD_RF_SPL_R_SPL_TX_EN_MAN = BIT(0),
    FLD_RF_SPL_R_SPL_RX_EN_MAN = BIT(1),
    FLD_RF_SPL_R_SPL_RF_ON_MAN_EN = BIT(2),
    FLD_RF_SPL_R_SPL_RF_ON_MAN = BIT(3),
    FLD_RF_SPL_R_SPL_RX_ON_MAN = BIT(4),
    FLD_RF_SPL_R_SPL_TX_ON_MAN = BIT(5),
};


#define reg_rf_spl_tx_en_delay        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1B)

enum
{
    FLD_RF_SPL_R_SPL_T_TXEN_DELAY = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_TXEN_DELAY_EN = BIT(7),
};


#define reg_rf_spl_rx_en_delay        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1C)

enum
{
    FLD_RF_SPL_R_SPL_T_RXEN_DELAY = BIT_RNG(0, 6),
    FLD_RF_SPL_R_SPL_RXEN_DELAY_EN = BIT(7),
};


#define reg_rf_spl_wlan_coex        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1D)

enum
{
    FLD_RF_SPL_R_SPL_COEX_EN  = BIT(0),
    FLD_RF_SPL_R_SPL_COEX_WLAN_POL = BIT(1),
    FLD_RF_SPL_R_SPL_COEX_STATUS = BIT(2),
    FLD_RF_SPL_R_SPL_COEX_TRX_POL = BIT(3),
    FLD_RF_SPL_R_SPL_COEX_TRX_PRIO = BIT(4),
    FLD_RF_SPL_R_SPL_COEX_TX_PRIO = BIT(5),
    FLD_RF_SPL_R_SPL_COEX_RX_PRIO = BIT(6),
};


#define reg_rf_spl_tx_dp_trig_time        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1E)

enum
{
    FLD_RF_SPL_R_SPL_TX_DP_TRIG_TIME = BIT_RNG(0, 7),
};


#define reg_rf_spl_tx_dp_trig_en        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x1F)

enum
{
    FLD_RF_SPL_R_SPL_TX_DP_TRIG_EN = BIT(0),
};


#define reg_rf_spl_irq_status       REG_ADDR16(REG_SPL_LL_BASE_ADDR + 0x20)

typedef enum
{
    FLD_RF_SPL_TX_IRQ     = BIT(0),
    FLD_RF_SPL_RX_IRQ     = BIT(1),
    FLD_RF_SPL_TX_TIMEOUT_IRQ = BIT(2),
    FLD_RF_SPL_RX_TIMEOUT_IRQ = BIT(3),
    FLD_RF_SPL_RX_FIRST_TIMEOUT_IRQ = BIT(4),
    FLD_RF_SPL_FSM_TIMEOUT_IRQ = BIT(5),
    FLD_RF_SPL_RX_CRC2_ERROR_IRQ = BIT(6),
    FLD_RF_SPL_CMD_DONE_IRQ = BIT(7),
    FLD_RF_SPL_WLAN_DENY_IRQ = BIT(8),
    FLD_RF_SPL_RX_SYNC_IRQ = BIT(9),
    FLD_RF_SPL_RXCTRL_DONE_IRQ = BIT(10),
    FLD_RF_SPL_RXFIFO_FULL_IRQ = BIT(11),
    FLD_RF_SPL_HEC_ERROR_IRQ = BIT(12),
    FLD_RF_SPL_IRQ_STATUS_ALL = BIT_RNG(0, 12),
}rf_spl_irq_status_e;


#define reg_rf_spl_irq_mask        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x24)

typedef enum
{
    FLD_RF_SPL_TX_IRQ_MASK = BIT(0),
    FLD_RF_SPL_RX_IRQ_MASK = BIT(1),
    FLD_RF_SPL_TX_TIMEOUT_IRQ_MASK = BIT(2),
    FLD_RF_SPL_RX_TIMEOUT_IRQ_MASK = BIT(3),
    FLD_RF_SPL_RX_FIRST_TIMEOUT_IRQ_MASK = BIT(4),
    FLD_RF_SPL_FSM_TIMEOUT_IRQ_MASK = BIT(5),
    FLD_RF_SPL_RX_CRC2_ERROR_IRQ_MASK = BIT(6),
    FLD_RF_SPL_CMD_DONE_IRQ_MASK = BIT(7),
    FLD_RF_SPL_WLAN_DENY_IRQ_MASK = BIT(8),
    FLD_RF_SPL_RX_SYNC_IRQ_MASK = BIT(9),
    FLD_RF_SPL_RXCTRL_DONE_IRQ_MASK = BIT(10),
    FLD_RF_SPL_RXFIFO_FULL_IRQ_MASK = BIT(11),
    FLD_RF_SPL_HEC_ERROR_IRQ_MASK = BIT(12),
}rf_spl_irq_mask_e;


#define reg_rf_spl_fsm_evtctrl        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x28)

enum
{
    FLD_RF_SPL_EVENTCTRL_CS = BIT_RNG(0, 3),
};


#define reg_rf_spl_counter0        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x29)

enum
{
    FLD_RF_SPL_NAK_CNT    = BIT_RNG(0, 3),
    FLD_RF_SPL_OLD_CNT    = BIT_RNG(4, 7),
};


#define reg_rf_spl_counter1        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x2A)

enum
{
    FLD_RF_SPL_CRC_CNT    = BIT_RNG(0, 3),
};


#define reg_rf_spl_trx_field        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x2B)

enum
{
    FLD_RF_SPL_TX_MD      = BIT(0),
    FLD_RF_SPL_TX_SN      = BIT(1),
    FLD_RF_SPL_TX_NESN    = BIT(2),
    FLD_RF_SPL_RX_MD      = BIT(3),
    FLD_RF_SPL_RX_SN      = BIT(4),
    FLD_RF_SPL_RX_NESN    = BIT(5),
    FLD_RF_SPL_RX_EMPTY_PKT_FLAG = BIT(6),
    FLD_RF_SPL_TX_EMPTY_PKT_FLAG = BIT(7),
};


#define reg_rf_spl_timestamp_ctrl        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x2C)

enum
{
    FLD_RF_SPL_TXON_TIMESTAMP_EN = BIT(0),
    FLD_RF_SPL_TXEN_TIMESTAMP_EN = BIT(1),
    FLD_RF_SPL_TXDONE_TIMESTAMP_EN = BIT(2),
    FLD_RF_SPL_RXSYNC_TIMESTAMP_EN = BIT(3),
    FLD_RF_SPL_RXDONE_TIMESTAMP_EN = BIT(4),
};


#define reg_rf_spl_txstart_timestamp_0        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x30)

enum
{
    FLD_RF_SPL_TXSTART_TIMESTAMP_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_txstart_timestamp_1        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x31)

enum
{
    FLD_RF_SPL_TXSTART_TIMESTAMP_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_txstart_timestamp_2        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x32)

enum
{
    FLD_RF_SPL_TXSTART_TIMESTAMP_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_txstart_timestamp_3        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x33)

enum
{
    FLD_RF_SPL_TXSTART_TIMESTAMP_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_txdone_timestamp_0        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x34)

enum
{
    FLD_RF_SPL_TXDONE_TIMESTAMP_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_txdone_timestamp_1        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x35)

enum
{
    FLD_RF_SPL_TXDONE_TIMESTAMP_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_txdone_timestamp_2        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x36)

enum
{
    FLD_RF_SPL_TXDONE_TIMESTAMP_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_txdone_timestamp_3        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x37)

enum
{
    FLD_RF_SPL_TXDONE_TIMESTAMP_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxsync_timestamp_0        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x38)

enum
{
    FLD_RF_SPL_RXSYNC_TIMESTAMP_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxsync_timestamp_1        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x39)

enum
{
    FLD_RF_SPL_RXSYNC_TIMESTAMP_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxsync_timestamp_2        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3A)

enum
{
    FLD_RF_SPL_RXSYNC_TIMESTAMP_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxsync_timestamp_3        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3B)

enum
{
    FLD_RF_SPL_RXSYNC_TIMESTAMP_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxdone_timestamp_0        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3C)

enum
{
    FLD_RF_SPL_RXDONE_TIMESTAMP_L = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxdone_timestamp_1        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3D)

enum
{
    FLD_RF_SPL_RXDONE_TIMESTAMP_ML = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxdone_timestamp_2        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3E)

enum
{
    FLD_RF_SPL_RXDONE_TIMESTAMP_MH = BIT_RNG(0, 7),
};


#define reg_rf_spl_rxdone_timestamp_3        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x3F)

enum
{
    FLD_RF_SPL_RXDONE_TIMESTAMP_H = BIT_RNG(0, 7),
};


#define reg_rf_spl_trx_commit_ctrl        REG_ADDR8(REG_SPL_LL_BASE_ADDR + 0x40)

enum
{
    FLD_RF_SPL_R_SPL_TX_COMMIT_CTRL = BIT(0),
    FLD_RF_SPL_R_SPL_RX_COMMIT_CTRL = BIT(1),
};

///*******************************      rf spl dma registers: 0xd4170800      ******************************/

#define reg_rf_spl_dma_ctr0(i) REG_ADDR8((REG_SPL_DMA_BASE_ADDR + 0x44 + (i) * 0x14))
#define reg_rf_spl_dma_ctrl(i) REG_ADDR32(REG_SPL_DMA_BASE_ADDR + 0x44 + (i) * 0x14)

enum
{
    FLD_RF_SPL_DMA_CHANNEL_ENABLE        = BIT(0),
    FLD_RF_SPL_DMA_CHANNEL_TC_MASK       = BIT(1),
    FLD_RF_SPL_DMA_CHANNEL_ERR_MASK      = BIT(2),
    FLD_RF_SPL_DMA_CHANNEL_ABT_MASK      = BIT(3),
    FLD_RF_SPL_DMA_CHANNEL_DST_REQ_SEL   = BIT_RNG(4, 8),
    FLD_RF_SPL_DMA_CHANNEL_SRC_REQ_SEL   = BIT_RNG(9, 13),
    FLD_RF_SPL_DMA_CHANNEL_DST_ADDR_CTRL = BIT_RNG(14, 15),
    FLD_RF_SPL_DMA_CHANNEL_SRC_ADDR_CTRL = BIT_RNG(16, 17),
    FLD_RF_SPL_DMA_CHANNEL_DST_MODE      = BIT(18),
    FLD_RF_SPL_DMA_CHANNEL_SRC_MODE      = BIT(19),
    FLD_RF_SPL_DMA_CHANNEL_DST_WIDTH     = BIT_RNG(20, 21),
    FLD_RF_SPL_DMA_CHANNEL_SRC_WIDTH     = BIT_RNG(22, 23),
};

#define reg_rf_spl_dma_ctr3(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR + 0x47 + (i) * 0x14)

enum
{
    FLD_RF_SPL_DMA_SRC_BURST_SIZE = BIT_RNG(0, 2),
    FLD_RF_SPL_DMA_R_NUM_EN       = BIT(4),
    FLD_RF_SPL_DMA_PRIORITY       = BIT(5),
    FLD_RF_SPL_DMA_W_NUM_EN       = BIT(6),
    FLD_RF_SPL_DMA_AUTO_ENABLE_EN = BIT(7),
};

#define reg_rf_spl_dma_src_addr(i) REG_ADDR32(REG_SPL_DMA_BASE_ADDR + 0x48 + (i) * 0x14)
#define reg_rf_spl_dma_dst_addr(i) REG_ADDR32(REG_SPL_DMA_BASE_ADDR + 0x4c + (i) * 0x14)

#define reg_rf_spl_dma_size0(i)    REG_ADDR16(REG_SPL_DMA_BASE_ADDR + 0x50 + (i) * 0x14)

enum
{
    FLD_RF_SPL_DMA_TANS_SIZE0 = BIT_RNG(0, 15),
};

#define reg_rf_spl_dma_size1(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR + 0x52 + (i) * 0x14)

enum
{
    FLD_RF_SPL_DMA_TANS_SIZE1 = BIT_RNG(0, 5),
    FLD_RF_SPL_DMA_TANS_IDX   = BIT_RNG(6, 7),
};

#define reg_rf_spl_dma_size(i) REG_ADDR32(REG_SPL_DMA_BASE_ADDR + 0x50 + (i) * 0x14)

enum
{
    FLD_RF_SPL_DMA_TX_SIZE     = BIT_RNG(0, 21),
    FLD_RF_SPL_DMA_TX_SIZE_IDX = BIT_RNG(22, 23),
};

#define reg_rf_spl_auto_ctrl REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0x10c)

enum
{
    FLD_RF_SPL_TX_MULTI_EN     = BIT(0),
    FLD_RF_SPL_RX_MULTI_EN     = BIT(1),
    FLD_RF_SPL_CH_0_RNUM_EN_BK = BIT(2),
    FLD_RF_SPL_CH_1_RNUM_EN_BK = BIT(3),
    FLD_RF_SPL_CH1_RX_ERR_EN   = BIT(4),
    FLD_RF_SPL_DMA_REQ_D1_EN   = BIT(5),
};

#define reg_rf_spl_tx_chn_dep  REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0xf3)
#define reg_rf_spl_tx_size     REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0xf0)
#define reg_rf_spl_tx_size_h   REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0xf1)

#define reg_rf_spl_dma_rx_wptr    REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0xf4)
#define reg_rf_spl_dma_rx_rptr    REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0xf5)

#define reg_rf_spl_dma_tx_rptr(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0x101 + (i << 1))

enum
{
    FLD_RF_SPL_DMA_RPTR_MASK = BIT_RNG(0, 4),
    FLD_RF_SPL_DMA_RPTR_SET  = BIT(5),
    FLD_RF_SPL_DMA_RPTR_NEXT = BIT(6),
    FLD_RF_SPL_DMA_RPTR_CLR  = BIT(7),
};

#define reg_rf_spl_dma_tx_wptr(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0x100 + (i << 1))

enum
{
    FLD_RF_SPL_DMA_WPTR_MASK = BIT_RNG(0, 4),
};

#define reg_rf_spl_dma_tx_rptr1(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0x119 + (i << 1))
#define reg_rf_spl_dma_tx_wptr1(i) REG_ADDR8(REG_SPL_DMA_BASE_ADDR+0x118 + (i << 1))

#define reg_rf_spl_dma_rx_size_l     REG_ADDR8(REG_SPL_DMA_BASE_ADDR + 0xf6)
#define reg_rf_spl_dma_rx_size_h    REG_ADDR8(REG_SPL_DMA_BASE_ADDR + 0xf7)
#define reg_rf_spl_dma_rx_size     REG_ADDR16(REG_SPL_DMA_BASE_ADDR + 0xf6)

#define reg_rf_spl_rx_wptr_mask    REG_ADDR8(REG_SPL_DMA_BASE_ADDR + 0x10d)



#endif


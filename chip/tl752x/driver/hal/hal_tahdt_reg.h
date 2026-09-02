/********************************************************************************************************
 * @file    hal_tahdt_reg.h
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


#ifndef __HAL_TAHDT_REG_H__
#define __HAL_TAHDT_REG_H__

#include "inc/soc.h"


///*******************************      rf      ******************************/
#define RF_AHBADDR              (0x50425000UL)
#define RF_BBCTRL_BASE_ADDR     (RF_AHBADDR + 0x0000UL)
#define RF_BBPDZB_BASE_ADDR     (RF_AHBADDR + 0x0300UL)
#define RF_MDM_BASE_ADDR        (RF_AHBADDR + 0x0400UL)
#define RF_RADIO_BASE_ADDR      (RF_AHBADDR + 0x0600UL)
#define RF_DMABB_BASE_ADDR      (RF_AHBADDR + 0x0800UL)
#define RF_SC_BB_BASE_ADDR      (RF_AHBADDR + 0x0C00UL)

///*******************************      rf bb pdzb registers      ******************************/
#define reg_rf_bbpdzb_mdm_sel       REG_ADDR8(RF_BBPDZB_BASE_ADDR + 0x00)
#define reg_rf_bbpdzb_dbg_sel0      REG_ADDR8(RF_BBPDZB_BASE_ADDR + 0x02)
enum {
    FLD_TAHDT_PDZB_DBG_SPL    = BIT_RNG(0, 3),
};
#define reg_rf_bbpdzb_dbg_sel1      REG_ADDR8(RF_BBPDZB_BASE_ADDR + 0x03)
enum {
    FLD_TAHDT_PDZB_DBG_MDM  = BIT_RNG(0, 3),
    FLD_TAHDT_PDZB_DBG_MDM1 = BIT(4),
    FLD_TAHDT_PDZB_DBG_DAC  = BIT(5),
    FLD_TAHDT_PDZB_DBG_ADC  = BIT(6),
};

///*******************************      rf mdm registers      ******************************/
#define reg_tahdt_mdm_mode_ctrl_tx1_0 REG_ADDR8(RF_MDM_BASE_ADDR + 0x022)
enum {
    FLD_TAHDT_MDM_BLE_MODE_TX = BIT(0),
};
#define reg_tahdt_mdm_cfg0            REG_ADDR8(RF_MDM_BASE_ADDR + 0x13c)
enum {
    FLD_TAHDT_MDM_PILOT_INTERVAL = BIT_RNG(1, 2),
    FLD_TAHDT_MDM_FRAME_TYPE     = BIT_RNG(3, 4),
};
#define reg_tahdt_mdm_cfg1            REG_ADDR8(RF_MDM_BASE_ADDR + 0x13d)

#define reg_tahdt_mdm_rx_cfg0         REG_ADDR8(RF_MDM_BASE_ADDR + 0x13e)
#define reg_tahdt_mdm_rx_cfg1         REG_ADDR8(RF_MDM_BASE_ADDR + 0x13f)
#define reg_tahdt_mdm_rx_cfg2         REG_ADDR8(RF_MDM_BASE_ADDR + 0x140)
#define reg_tahdt_mdm_rx_cfg3         REG_ADDR8(RF_MDM_BASE_ADDR + 0x141)
#define reg_tahdt_mdm_rx_cfg4         REG_ADDR8(RF_MDM_BASE_ADDR + 0x142)
#define reg_tahdt_mdm_rx_cfg5         REG_ADDR8(RF_MDM_BASE_ADDR + 0x143)
#define reg_tahdt_mdm_rx_cfg6         REG_ADDR8(RF_MDM_BASE_ADDR + 0x144)
#define reg_tahdt_mdm_rx_cfg7         REG_ADDR8(RF_MDM_BASE_ADDR + 0x145)
#define reg_tahdt_mdm_rx_cfg8         REG_ADDR8(RF_MDM_BASE_ADDR + 0x146)
#define reg_tahdt_mdm_rx_cfg9         REG_ADDR8(RF_MDM_BASE_ADDR + 0x147)
#define reg_tahdt_mdm_rx_cfg10        REG_ADDR8(RF_MDM_BASE_ADDR + 0x148)
#define reg_tahdt_mdm_rx_cfg11        REG_ADDR8(RF_MDM_BASE_ADDR + 0x149)

///*******************************      rf mdm registers      ******************************/
#define reg_tahdt_radio_mode_cfg_rx1_1    REG_ADDR8(RF_RADIO_BASE_ADDR + 0x021)
enum {
    FLD_TAHDT_RADIO_RX_MODE = BIT(5),
};

#define reg_tahdt_radio_mode_cfg_tx1_0    REG_ADDR8(RF_RADIO_BASE_ADDR + 0x022)
enum {
    FLD_TAHDT_RADIO_BLE_MODE_TX = BIT(0),
};

#define reg_tahdt_radio_burst_cfg_txrx_0  REG_ADDR8(RF_RADIO_BASE_ADDR + 0x028)

#define reg_tahdt_radio_burst_cfg_txrx_1  REG_ADDR8(RF_RADIO_BASE_ADDR + 0x029)
enum {
    // #if defined(MCU_CORE_TL753X)
    FLD_TAHDT_RADIO_CH_NUM_LL_SEL       = BIT(0),
    // #endif
    FLD_TAHDT_RADIO_TX_EN_PIF           = BIT(1),
    FLD_TAHDT_RADIO_RX_EN_PIF           = BIT(2),
    FLD_TAHDT_RADIO_RX_TIM_SRQ_SEL_TESQ = BIT(3),
    FLD_TAHDT_RADIO_TX_TIM_SRQ_SEL_TESQ = BIT(4),
    FLD_TAHDT_RADIO_HOLD1               = BIT_RNG(5, 7),
};

#define reg_tahdt_radio_mode_cfg_tx3_0    REG_ADDR8(RF_RADIO_BASE_ADDR + 0x03c)
enum {
    FLD_TAHDT_RADIO_TX_IQ_MODE_EN_BLE = BIT(7),
};

#define reg_tahdt_radio_txrx_dbg3_0       REG_ADDR8(RF_RADIO_BASE_ADDR + 0x044)
enum {
    FLD_TAHDT_RADIO_CHNL_FREQ_L = BIT_RNG(1, 7),
};

#define reg_tahdt_radio_txrx_dbg3_1       REG_ADDR8(RF_RADIO_BASE_ADDR + 0x045)
enum {
    FLD_TAHDT_RADIO_CHNL_FREQ_H = BIT_RNG(0, 4),
};

#define reg_tahdt_radio_hsspl_ctrl0   REG_ADDR8(RF_RADIO_BASE_ADDR + 0x1e0)       
enum {
    FLD_TAHDT_RADIO_RX_HS_48M_EN = BIT(0),
    FLD_TAHDT_RADIO_RX_SPL_EN    = BIT(1),
    FLD_TAHDT_RADIO_RXC_MODE_SEL = BIT_RNG(2, 3),
};

#define reg_tahdt_radio_hsspl_ctrl1   REG_ADDR8(RF_RADIO_BASE_ADDR + 0x1e1)
enum {
    FLD_TAHDT_RADIO_TX_HS_48M_EN      = BIT(0),
    FLD_TAHDT_RADIO_TX_SPL_EN         = BIT(1),
    FLD_TAHDT_RADIO_TXC_MODE_SEL      = BIT_RNG(2, 3),
    FLD_TAHDT_RADIO_TX_LS_24M_EN      = BIT(4),
    #if defined(MCU_CORE_TL753X)
    FLD_TAHDT_RADIO_RX_HP_EN          = BIT(5),
    FLD_TAHDT_RADIO_TX_DOWN_SAMPLE_EN = BIT(6),
    #endif
};  

#define reg_tahdt_radio_hsspl_ctrl2   REG_ADDR8(RF_RADIO_BASE_ADDR + 0x1e2)
enum {
    FLD_TAHDT_RADIO_RXC_MODE_OW = BIT(0),
    FLD_TAHDT_RADIO_TRX_BPS_OW  = BIT(1),
    #if defined(MCU_CORE_TL753X)
    FLD_TAHDT_RADIO_TRX_FAST_OW = BIT(3),
    #endif
};  

///*******************************      tahdt      ******************************/
#define TAHDT_AHBADDR         (0x50426000UL)
#define TAHDT_BB_BASE_ADDR    (TAHDT_AHBADDR + 0x000UL)
#define TAHDT_LL_BASE_ADDR    (TAHDT_AHBADDR + 0x100UL)
#define TAHDT_DMA_BASE_ADDR   (TAHDT_AHBADDR + 0x200UL)

///*******************************      tahdt baseband registers      ******************************/
#define reg_tahdt_bb_tx_buffer        REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x00)
#define REG_TAHDT_BB_TX_BUFFER_ADDR   (TAHDT_BB_BASE_ADDR + 0x00)

#define reg_tahdt_bb_rx_buffer        REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x04)
#define REG_TAHDT_BB_RX_BUFFER_ADDR   (TAHDT_BB_BASE_ADDR + 0x04)   

#define reg_tahdt_bb_soft_reset       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x08)
enum {
    FLD_TAHDT_BB_SOFT_RST_P       = BIT(0),
    FLD_TAHDT_BB_CRYPT_SOFT_RST_P = BIT(1),
    FLD_TAHDT_BB_POLAR_SOFT_RST_P = BIT(2),
    FLD_TAHDT_BB_TXFIFO_CLR_P     = BIT(3),
    FLD_TAHDT_BB_RXFIFO_CLR_P     = BIT(4),
    FLD_TAHDT_BB_LLRFIFO_CLR_P    = BIT(5),
};

#define reg_tahdt_bb_frame_indicator  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x09)
enum {
    FLD_TAHDT_BB_FRAME1 = BIT(0),
    FLD_TAHDT_BB_FRAME2 = BIT(1),
    FLD_TAHDT_BB_FRAME3 = BIT(2),
    FLD_TAHDT_BB_FRAME4 = BIT(3),
    FLD_TAHDT_BB_FRAME_ALL = BIT_RNG(0, 3),
    FLD_TAHDT_BB_MCS    = BIT_RNG(4, 7),
};

#define reg_tahdt_bb_frame_ctrl0      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x0a)
enum {
    FLD_TAHDT_BB_CTRL_TYPE = BIT_RNG(0, 4),
};

#define reg_tahdt_bb_frame_ctrl1      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x0b)
enum {
    FLD_TAHDT_BB_SYMB_RATE      = BIT_RNG(0, 1),
    FLD_TAHDT_BB_PILOT_INTERVAL = BIT_RNG(2, 3),
    FLD_TAHDT_BB_TX_SERPAR_IF   = BIT(4),
    FLD_TAHDT_BB_TX_SWAP        = BIT(5),
    FLD_TAHDT_BB_RX_FOOTER_EN   = BIT(6),
};

#define reg_tahdt_bb_trx_pldlen       REG_ADDR16(TAHDT_BB_BASE_ADDR + 0x0c)

#define reg_tahdt_bb_whiten_ctrl      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x0e)
enum {
    FLD_TAHDT_BB_WHITEN_INIT = BIT_RNG(0, 6),
    FLD_TAHDT_BB_WHITEN_EN   = BIT(7),
};

#define reg_tahdt_bb_dp_ctrl          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x0f)
enum {
    FLD_TAHDT_BB_CRC_EN                = BIT(0),
    FLD_TAHDT_BB_CRC_TYPE              = BIT(1),
    FLD_TAHDT_BB_HEC_INIT_MAN          = BIT(2),
    FLD_TAHDT_BB_POLAR_EN_MAN          = BIT(3),
    FLD_TAHDT_BB_POLAR_EN              = BIT(4),
    FLD_TAHDT_BB_DP_BYPASS_EN          = BIT(5),
    FLD_TAHDT_BB_POLAR_BYPASS_EN       = BIT(6),
    FLD_TAHDT_BB_POLAR_AFTER_WHITEN_EN = BIT(7),
};

#define reg_tahdt_bb_crc_init         REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x10)

#define reg_tahdt_bb_datseg_crc_init0 REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x14)
#define reg_tahdt_bb_datseg_crc_init1 REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x15)
#define reg_tahdt_bb_datseg_crc_init2 REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x16)

#define reg_tahdt_bb_hec_init0        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x17)
#define reg_tahdt_bb_hec_init1        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x18)
#define reg_tahdt_bb_hec_init2        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x19)

#define reg_tahdt_bb_llid0            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1a)
#define reg_tahdt_bb_llid1            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1b)
#define reg_tahdt_bb_llid2            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1c)

#define reg_tahdt_bb_bch_init0        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1d)
#define reg_tahdt_bb_bch_init1        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1e)
#define reg_tahdt_bb_bch_init2        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x1f)
#define reg_tahdt_bb_bch_init3        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x20)
#define reg_tahdt_bb_bch_init4        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x21)

#define reg_tahdt_bb_m_init           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x22)
enum {
    FLD_TAHDT_BB_M_INIT    = BIT_RNG(0, 5),
    FLD_TAHDT_BB_M_INIT_EN = BIT(7),
};

#define reg_tahdt_bb_m_seqn           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x23)
enum {
    FLD_TAHDT_BB_M_SEQN          = BIT_RNG(0, 2),
    FLD_TAHDT_BB_BCH_IN_ORD      = BIT(3),
    FLD_TAHDT_BB_BCH_OUT_ORD     = BIT(4),
    FLD_TAHDT_BB_SYNCWORD_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_syncword_man_w0  REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x24)
#define reg_tahdt_bb_syncword_man_w1  REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x28)

#define reg_tahdt_bb_datseg_man0      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x2c)
enum {
    FLD_TAHDT_BB_N1024_MAN     = BIT_RNG(0, 6),
    FLD_TAHDT_BB_DATSEG_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_datseg_man1      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x2d)
enum {
    FLD_TAHDT_BB_N512_MAN = BIT_RNG(0, 1),
    FLD_TAHDT_BB_N256_MAN = BIT_RNG(2, 3),
    FLD_TAHDT_BB_N128_MAN = BIT_RNG(4, 5),
    FLD_TAHDT_BB_N64_MAN  = BIT_RNG(6, 7),
};

#define reg_tahdt_bb_datseg_man2      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x2e)
enum {
    FLD_TAHDT_BB_K64_FINAL_MAN = BIT_RNG(0, 6),
};

#define reg_tahdt_bb_datseg_man3      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x2f)
enum {
    FLD_TAHDT_BB_KR_MAN_L = BIT_RNG(0, 7),
};

#define reg_tahdt_bb_datseg_man4      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x30)
enum {
    FLD_TAHDT_BB_KR_MAN_H = BIT_RNG(0, 2),
};

#define reg_tahdt_bb_datseg_man5      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x31)
enum {
    FLD_TAHDT_BB_PAD_NUM_MAN = BIT_RNG(0, 5),
};

#define reg_tahdt_bb_clk_select       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x32)

#define reg_tahdt_bb_rxdma_burst      REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x33)
enum {
    FLD_TAHDT_BB_RXDMA_BURST_SIZE = BIT_RNG(0, 1),
};

#define reg_tahdt_bb_debug_ctrl0       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x34)
enum {
    FLD_TAHDT_BB_DBG0_SEL = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DBG0_EN  = BIT(7),
};
#define reg_tahdt_bb_debug_ctrl1       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x35)
enum {
    FLD_TAHDT_BB_DBG1_SEL = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DBG1_EN  = BIT(7),
};
#define reg_tahdt_bb_debug_ctrl2       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x36)
enum {
    FLD_TAHDT_BB_DBG2_SEL = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DBG2_EN  = BIT(7),
};
#define reg_tahdt_bb_debug_ctrl3       REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x37)
enum {
    FLD_TAHDT_BB_DBG3_SEL = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DBG3_EN  = BIT(7),
};
#define reg_tahdt_bb_debug_port0       REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x38)
#define reg_tahdt_bb_debug_port1       REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x39)
#define reg_tahdt_bb_debug_port2       REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x3a)
#define reg_tahdt_bb_debug_port3       REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x3b)

#define reg_tahdt_bb_fifo_indicator   REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x3c)
enum {
    FLD_TAHDT_BB_TXFIFO_FULL   = BIT(0),
    FLD_TAHDT_BB_TXFIFO_EMPTY  = BIT(1),
    FLD_TAHDT_BB_RXFIFO_FULL   = BIT(2),
    FLD_TAHDT_BB_RXFIFO_EMPTY  = BIT(3),
    FLD_TAHDT_BB_LLRFIFO_FULL  = BIT(4),
    FLD_TAHDT_BB_LLRFIFO_EMPYT = BIT(5),
};

#define reg_tahdt_bb_error_indicator  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x3d)
enum {
    FLD_TAHDT_BB_DP_CRC_ERR        = BIT(0),
    FLD_TAHDT_BB_DP_HEC_ERR        = BIT(1),
    FLD_TAHDT_BB_DP_MIC_ERR        = BIT(2),
    FLD_TAHDT_BB_DP_DATSEG_CRC_ERR = BIT(3),
    FLD_TAHDT_BB_TXCRYPT_ERR       = BIT(4),
    FLD_TAHDT_BB_RXCRYPT_ERR       = BIT(5),
    FLD_TAHDT_BB_DP_PLDLEN_ERR     = BIT(6),
    FLD_TAHDT_BB_DP_MCS_ERR        = BIT(7),
};

#define reg_tahdt_bb_fsm_indicator   REG_ADDR16(TAHDT_BB_BASE_ADDR + 0x3e)
enum {
    FLD_TAHDT_BB_PKTCTRL_CS = BIT_RNG(0, 3),
    FLD_TAHDT_BB_SEGCRC_CS = BIT_RNG(4, 5),
    FLD_TAHDT_BB_DP_CS = BIT_RNG(8, 10),
    FLD_TAHDT_BB_POLAR_CS = BIT_RNG(11, 15),
};

#define reg_tahdt_bb_syncword0            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x40)
enum {
    FLD_TAHDT_BB_SYNCGEN_START_P    = BIT(0),
    FLD_TAHDT_BB_SYNCGEN_DONE_CLR_P = BIT(1),
    FLD_TAHDT_BB_SYNCGEN_VALID      = BIT(2),  
};

#define reg_tahdt_bb_syncword1            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x41)
#define reg_tahdt_bb_syncword2            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x42)
#define reg_tahdt_bb_syncword3            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x43)
#define reg_tahdt_bb_syncword4            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x44)
#define reg_tahdt_bb_syncword5            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x45)
#define reg_tahdt_bb_syncword6            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x46)
#define reg_tahdt_bb_syncword7            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x47)
#define reg_tahdt_bb_syncword8            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x48)

#define reg_tahdt_bb_polar_datseg0        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x49)
enum {
    FLD_TAHDT_BB_N1024       = BIT_RNG(0, 6),
    FLD_TAHDT_BB_DATSEG_DONE = BIT(7),
};

#define reg_tahdt_bb_polar_datseg1        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4a)
enum {
    FLD_TAHDT_BB_N512 = BIT_RNG(0, 1),
    FLD_TAHDT_BB_N256 = BIT_RNG(2, 3),
    FLD_TAHDT_BB_N128 = BIT_RNG(4, 5),
    FLD_TAHDT_BB_N64  = BIT_RNG(6, 7),
};

#define reg_tahdt_bb_polar_datseg2        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4b)
enum {
    FLD_TAHDT_BB_K64_FINAL = BIT_RNG(0, 6),
};

#define reg_tahdt_bb_polar_datseg3        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4c)
enum {
    FLD_TAHDT_BB_KR_L = BIT_RNG(0, 7),
};

#define reg_tahdt_bb_polar_datseg4        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4d)
enum {
    FLD_TAHDT_BB_KR_H = BIT_RNG(0, 2),
};

#define reg_tahdt_bb_polar_datseg5        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4e)
enum {
    FLD_TAHDT_BB_PAD_NUM           = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DATSEG_DONE_CLR_P = BIT(6),
    FLD_TAHDT_BB_DATSEG_START_P    = BIT(7),
};

#define reg_tahdt_bb_tx_chn               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x4f)
enum {
    FLD_TAHDT_BB_TX_CHN = BIT_RNG(0, 2),
};

#define reg_tahdt_bb_preamble_ctrl0          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x50)
enum {
    FLD_TAHDT_BB_PREAMBLE_LEN_MAN    = BIT_RNG(0, 6),
    FLD_TAHDT_BB_PREAMBLE_LEN_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_preamble_ctrl1          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x51)
enum {
    FLD_TAHDT_BB_PREAMBLE_MAN    = BIT_RNG(0, 7),
};

#define reg_tahdt_bb_preamble_ctrl2          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x52)
enum {
    FLD_TAHDT_BB_PREAMBLE_MAN_EN = BIT(0),
};

#define reg_tahdt_bb_synclen_ctrl             REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x53)
enum {
    FLD_TAHDT_BB_SYNCWORD_LEN_MAN    = BIT_RNG(0, 6),
    FLD_TAHDT_BB_SYNCWORD_LEN_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_ctrllen_ctrl             REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x54)
enum {
    FLD_TAHDT_BB_CTRLFIELD_LEN_MAN    = BIT_RNG(0, 5),
    FLD_TAHDT_BB_CTRLFIELD_LEN_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_datalen_ctrl0            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x55)
enum {
    FLD_TAHDT_BB_DATAFIELD_LEN_MAN_L = BIT_RNG(0, 7),
};

#define reg_tahdt_bb_datalen_ctrl1            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x56)
enum {
    FLD_TAHDT_BB_DATAFIELD_LEN_MAN_H  = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DATAFIELD_LEN_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_trailer_ctrl             REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x57)
enum {
    FLD_TAHDT_BB_TRAILER_LEN  = BIT_RNG(0, 3),
    FLD_TAHDT_BB_TRAILER_EN   = BIT(7),
};

#define reg_tahdt_bb_fh_ctrl                  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x58)
enum {
    FLD_TAHDT_BB_FH_START_P   = BIT(0),
    FLD_TAHDT_BB_FH_EN        = BIT(1),
    FLD_TAHDT_BB_FH_REMAP_EN  = BIT(2),
    FLD_TAHDT_BB_FH_PARA2_SEL = BIT(3),
    FLD_TAHDT_BB_FH_SEL       = BIT_RNG(4, 5),
};

#define reg_tahdt_bb_fh_status                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x59)
enum {
    FLD_TAHDT_BB_FH_STATUS       = BIT_RNG(0, 1),
    FLD_TAHDT_BB_FH_STATUS_CLR_P = BIT(7),
};

#define reg_tahdt_bb_fh_ch_idx                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x5a)
#define reg_tahdt_bb_fh_map_idx               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x5b)

#define reg_tahdt_bb_fh_prn                   REG_ADDR16(TAHDT_BB_BASE_ADDR + 0x5c)
#define reg_tahdt_bb_fh_slot_cnt              REG_ADDR16(TAHDT_BB_BASE_ADDR + 0x5e)

#define reg_tahdt_bb_fh_chmap_w0              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x60)
#define reg_tahdt_bb_fh_chmap_w1              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x64)
#define reg_tahdt_bb_fh_chmap_w2              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x68)
#define reg_tahdt_bb_fh_chmap_w3              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x6c)
#define reg_tahdt_bb_fh_chmap_w4              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x70)
#define reg_tahdt_bb_fh_chmap_w5              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x74)
#define reg_tahdt_bb_fh_chmap_b6              REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x78)

#define reg_tahdt_bb_fh_chmap_hw2             REG_ADDR16(TAHDT_BB_BASE_ADDR + 0x68)

#define reg_tahdt_bb_fh_chmap0                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x60)
#define reg_tahdt_bb_fh_chmap1                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x61)
#define reg_tahdt_bb_fh_chmap2                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x62)
#define reg_tahdt_bb_fh_chmap3                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x63)
#define reg_tahdt_bb_fh_chmap4                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x64)
#define reg_tahdt_bb_fh_chmap5                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x65)
#define reg_tahdt_bb_fh_chmap6                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x66)
#define reg_tahdt_bb_fh_chmap7                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x67)
#define reg_tahdt_bb_fh_chmap8                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x68)
#define reg_tahdt_bb_fh_chmap9                REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x69)
#define reg_tahdt_bb_fh_chmap10               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6a)
#define reg_tahdt_bb_fh_chmap11               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6b)
#define reg_tahdt_bb_fh_chmap12               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6c)
#define reg_tahdt_bb_fh_chmap13               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6d)
#define reg_tahdt_bb_fh_chmap14               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6e)
#define reg_tahdt_bb_fh_chmap15               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x6f)
#define reg_tahdt_bb_fh_chmap16               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x70)
#define reg_tahdt_bb_fh_chmap17               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x71)
#define reg_tahdt_bb_fh_chmap18               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x72)
#define reg_tahdt_bb_fh_chmap19               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x73)
#define reg_tahdt_bb_fh_chmap20               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x74)
#define reg_tahdt_bb_fh_chmap21               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x75)
#define reg_tahdt_bb_fh_chmap22               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x76)
#define reg_tahdt_bb_fh_chmap23               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x77)
#define reg_tahdt_bb_fh_chmap24               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x78)

#define reg_tahdt_bb_ctrlfield_info0          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x79)
#define reg_tahdt_bb_ctrlfield_info1          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7a)
#define reg_tahdt_bb_ctrlfield_info2          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7b)
#define reg_tahdt_bb_ctrlfield_info3          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7c)
#define reg_tahdt_bb_ctrlfield_info4          REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7d)

#define reg_tahdt_bb_crypt_ctrl               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7e)
enum {
    FLD_TAHDT_BB_CRYPT_ENABLE = BIT(0),
    FLD_TAHDT_BB_CRYPT_ALGO   = BIT(1),
    FLD_TAHDT_BB_CRYPT_MODE   = BIT(2),
    FLD_TAHDT_BB_CRYPT_DSB    = BIT(3),
    FLD_TAHDT_BB_MIC_DSB      = BIT(4),
    FLD_TAHDT_BB_MST_SLV      = BIT(5),
};

#define reg_tahdt_bb_crypt_clkslot0           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x7f)
#define reg_tahdt_bb_crypt_clkslot1           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x80)
#define reg_tahdt_bb_crypt_clkslot2           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x81)
#define reg_tahdt_bb_crypt_clkslot3           REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x82)
enum {
    FLD_TAHDT_BB_CLK_SLOT_24_29 = BIT_RNG(0, 5),
    FLD_TAHDT_BB_DAYCOUNTER_8_9 = BIT_RNG(6, 7),
};

#define reg_tahdt_bb_crypt_daycnt             REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x83)

#define reg_tahdt_bb_crypt_txccmcnt_w0        REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x84)
#define reg_tahdt_bb_crypt_txccmcnt_b1        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x88) 
enum {
    FLD_TAHDT_BB_TXCCMPKTCNT_32_38 = BIT_RNG(0, 6),
    FLD_TAHDT_BB_TXCCMPKTCNT_AUTOINC_DSB = BIT(7),
};

#define reg_tahdt_bb_crypt_rxccmcnt_w0        REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x8c)
#define reg_tahdt_bb_crypt_rxccmcnt_b1        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0x90) 
enum {
    FLD_TAHDT_BB_RXCCMPKTCNT_32_38 = BIT_RNG(0, 6),
    FLD_TAHDT_BB_RXCCMPKTCNT_AUTOINC_DSB = BIT(7),
};

#define reg_tahdt_bb_crypt_iv_w0              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x94)
#define reg_tahdt_bb_crypt_iv_w1              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x98)

#define reg_tahdt_bb_crypt_sk_w0              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0x9c)
#define reg_tahdt_bb_crypt_sk_w1              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xa0)
#define reg_tahdt_bb_crypt_sk_w2              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xa4)
#define reg_tahdt_bb_crypt_sk_w3              REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xa8)

#define reg_tahdt_bb_crypt_receive_rxmic      REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xac)
#define reg_tahdt_bb_crypt_calculate_rxmic     REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xb0)
#define reg_tahdt_bb_crypt_calculate_txmic     REG_ADDR32(TAHDT_BB_BASE_ADDR + 0xb4)

#define reg_tahdt_bb_datseg_crc_error_table0  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xb8)
#define reg_tahdt_bb_datseg_crc_error_table1  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xb9)
#define reg_tahdt_bb_datseg_crc_error_table2  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xba)
#define reg_tahdt_bb_datseg_crc_error_table3  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xbb)
#define reg_tahdt_bb_datseg_crc_error_table4  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xbc)
#define reg_tahdt_bb_datseg_crc_error_table5  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xbd)
#define reg_tahdt_bb_datseg_crc_error_table6  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xbe)
#define reg_tahdt_bb_datseg_crc_error_table7  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xbf)
#define reg_tahdt_bb_datseg_crc_error_table8  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xc0)

#define reg_tahdt_bb_version                  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xc4)
enum {
    FLD_TAHDT_BB_VERSION = BIT(0),
};

#define reg_tahdt_bb_test_ctrl0               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xc5)
enum {
    FLD_TAHDT_BB_TXDMA_EN         = BIT(0),
    FLD_TAHDT_BB_TX_TEST_MODE_EN  = BIT(1),
    FLD_TAHDT_BB_TX_TEST_INFINITE = BIT(2),
    FLD_TAHDT_BB_TX_TEST_DATA_SRC = BIT_RNG(3, 4),
};

#define reg_tahdt_bb_test_ctrl1               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xc6)

#define reg_tahdt_bb_test_ctrl2               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xc7)
enum {
    FLD_TAHDT_BB_TX_TEST_START_P = BIT(0),
    FLD_TAHDT_BB_TX_TEST_STOP_P  = BIT(1),
};

#define reg_tahdt_bb_maxlen                   REG_ADDR16(TAHDT_BB_BASE_ADDR + 0xc8)
enum {
    FLD_TAHDT_BB_MAXLEN = BIT_RNG(0, 10),
};

#define reg_tahdt_bb_rx_gain                  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xca)
#define reg_tahdt_bb_rx_rssi                  REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xcb)

#define reg_tahdt_bb_polar_pktlen             REG_ADDR16(TAHDT_BB_BASE_ADDR + 0xcc)
enum {
    FLD_TAHDT_BB_POLAR_PKTLEN = BIT_RNG(0, 13),
};

#define reg_tahdt_bb_empty_pkt_ind            REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xce)
enum {
    FLD_TAHDT_BB_EMPTY_PKT_FLAG = BIT(0),
};

#if defined(MCU_CORE_TL753X)
#define reg_tahdt_bb_tx_mcs_man               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xd0)
enum {
    FLD_TAHDT_BB_TX_MCS_MAN    = BIT_RNG(0, 3),
    FLD_TAHDT_BB_TX_MCS_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_rx_mcs_man               REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xd1)
enum {
    FLD_TAHDT_BB_RX_MCS_MAN    = BIT_RNG(0, 3),
    FLD_TAHDT_BB_RX_MCS_MAN_EN = BIT(7),
};

#define reg_tahdt_bb_trx_pldlen_man_en        REG_ADDR8(TAHDT_BB_BASE_ADDR + 0xd2)
enum {
    FLD_TAHDT_BB_TX_PLDLEN_MAN_EN = BIT(0),
    FLD_TAHDT_BB_RX_PLDLEN_MAN_EN = BIT(1),
};

#define reg_tahdt_bb_tx_pldlen_man            REG_ADDR16(TAHDT_BB_BASE_ADDR + 0xd4)
enum {
    FLD_TAHDT_BB_TX_PLDLEN_MAN = BIT_RNG(0, 10),
};
#define reg_tahdt_bb_rx_pldlen_man            REG_ADDR16(TAHDT_BB_BASE_ADDR + 0xd6)
enum {
    FLD_TAHDT_BB_RX_PLDLEN_MAN = BIT_RNG(0, 10),
};
#endif


///*******************************      tahdt logic link registers      ******************************/
#define reg_tahdt_ll_cmd      REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x00)
enum{
    FLD_TAHDT_LL_CMD         = BIT_RNG(0, 2),
    FLD_TAHDT_LL_CMD_TRIGGER = BIT(7),
};

#define reg_tahdt_ll_timeout_enable   REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x01)
enum {
    FLD_TAHDT_LL_TX_TIMEOUT_EN     = BIT(0),
    FLD_TAHDT_LL_RX_TIMEOUT_EN     = BIT(1),
    FLD_TAHDT_LL_RX_1ST_TIMEOUT_EN = BIT(2),
    FLD_TAHDT_LL_FSM_TIMEOUT_EN    = BIT(3),
};

#define reg_tahdt_ll_tx_settle        REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x02)
#define reg_tahdt_ll_tx_wait          REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x04)
#define reg_tahdt_ll_rx_settle        REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x06)
#define reg_tahdt_ll_rx_wait          REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x08)
#define reg_tahdt_ll_rx_timeout       REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x0a)
#define reg_tahdt_ll_t1_coex          REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x0c)
#define reg_tahdt_ll_t2_coex          REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x0d)
#define reg_tahdt_ll_rx_1st_timeout0  REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x0e)
#define reg_tahdt_ll_rx_1st_timeout1  REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x0f)
#define reg_tahdt_ll_rx_1st_timeout2  REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x10)
#define reg_tahdt_ll_fsm_timeout0     REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x11)
#define reg_tahdt_ll_fsm_timeout1     REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x12)
#define reg_tahdt_ll_fsm_timeout2     REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x13)
#define reg_tahdt_ll_cmd_schedule     REG_ADDR32(TAHDT_LL_BASE_ADDR + 0x14)

#define reg_tahdt_ll_func_enable      REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x18)
enum {
    FLD_TAHDT_LL_FUNC_MD_EN               = BIT(0),
    FLD_TAHDT_LL_FUNC_SN_EN               = BIT(1),
    FLD_TAHDT_LL_FUNC_NESN_EN             = BIT(2),
    FLD_TAHDT_LL_FUNC_CRC2_ERROR_EN       = BIT(3),
    FLD_TAHDT_LL_FUNC_TXDMA_TRIG_AUTO_EN  = BIT(4),
    FLD_TAHDT_LL_FUNC_CMD_SCHEDULE_EN     = BIT(5),
    FLD_TAHDT_LL_FUNC_RXIRQ_REPORT_ALL    = BIT(6),
};

#define reg_tahdt_ll_sn_nesn          REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x19)
enum {
    FLD_TAHDT_LL_INIT_GTX_SN   = BIT(0),
    FLD_TAHDT_LL_INIT_GTX_NESN = BIT(1),
    FLD_TAHDT_LL_INIT_GRX_SN   = BIT(2),
    FLD_TAHDT_LL_INIT_GRX_NESN = BIT(3),
    FLD_TAHDT_LL_INIT_SN_EN    = BIT(4),
    FLD_TAHDT_LL_INIT_NESN_EN  = BIT(5),
};

#define reg_tahdt_ll_trx_en_man       REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1a)
enum {
    FLD_TAHDT_LL_TX_EN_MAN    = BIT(0),
    FLD_TAHDT_LL_RX_EN_MAN    = BIT(1),
    FLD_TAHDT_LL_RF_ON_MAN_EN = BIT(2),
    FLD_TAHDT_LL_RF_ON_MAN    = BIT(3),
    FLD_TAHDT_LL_RX_ON_MAN    = BIT(4),
};

#define reg_tahdt_ll_tx_en_delay      REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1b)
enum {
    FLD_TAHDT_LL_TXEN_DELAY    = BIT_RNG(0, 6),
    FLD_TAHDT_LL_TXEN_DELAY_EN = BIT(7),
};

#define reg_tahdt_ll_rx_en_delay      REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1c)
enum {
    FLD_TAHDT_LL_RXEN_DELAY    = BIT_RNG(0, 6),
    FLD_TAHDT_LL_RXEN_DELAY_EN = BIT(7),
};

#define reg_tahdt_ll_wlan_coex        REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1d)
enum {
    FLD_TAHDT_LL_COEX_EN       = BIT(0),
    FLD_TAHDT_LL_COEX_WLAN_POL = BIT(1),
    FLD_TAHDT_LL_COEX_STATUS   = BIT(2),
    FLD_TAHDT_LL_COEX_TRX_POL  = BIT(3),
    FLD_TAHDT_LL_COEX_TRX_PRIO = BIT(4),
    FLD_TAHDT_LL_COEX_TX_PRIO  = BIT(5),
    FLD_TAHDT_LL_COEX_RX_PRIO  = BIT(6),
};

#define reg_tahdt_ll_tx_dp_trig_time  REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1e)
#define reg_tahdt_ll_tx_dp_trig_en    REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x1f)
enum {
    FLD_TAHDT_LL_TX_DP_TRIG_EN       = BIT(0),
};

#define reg_tahdt_ll_irq_status       REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x20)
typedef enum {
    FLD_TAHDT_LL_TX_IRQ             = BIT(0),
    FLD_TAHDT_LL_RX_IRQ             = BIT(1),
    FLD_TAHDT_LL_TX_TIMEOUT_IRQ     = BIT(2),
    FLD_TAHDT_LL_RX_TIMEOUT_IRQ     = BIT(3),
    FLD_TAHDT_LL_RX_1ST_TIMEOUT_IRQ = BIT(4),
    FLD_TAHDT_LL_FSM_TIMEOUT_IRQ    = BIT(5),
    FLD_TAHDT_LL_RX_CRC2_ERROR_IRQ  = BIT(6),
    FLD_TAHDT_LL_CMD_DONE_IRQ       = BIT(7),
    FLD_TAHDT_LL_WLAN_DENY_IRQ      = BIT(8),
    FLD_TAHDT_LL_RX_SYNC_IRQ        = BIT(9),
    FLD_TAHDT_LL_RXCTRL_DONE_IRQ    = BIT(10),
    FLD_TAHDT_LL_RXFIFO_FULL_IRQ    = BIT(11),
    FLD_TAHDT_LL_IRQ_ALL            = BIT_RNG(0, 11),
}rf_tahdt_irq_e;

#define reg_tahdt_ll_irq_mask         REG_ADDR16(TAHDT_LL_BASE_ADDR + 0x24)
enum {
    FLD_TAHDT_LL_TX_IRQ_MASK             = BIT(0),
    FLD_TAHDT_LL_RX_IRQ_MASK             = BIT(1),
    FLD_TAHDT_LL_TX_TIMEOUT_IRQ_MASK     = BIT(2),
    FLD_TAHDT_LL_RX_TIMEOUT_IRQ_MASK     = BIT(3),
    FLD_TAHDT_LL_1ST_RX_TIMEOUT_IRQ_MASK = BIT(4),
    FLD_TAHDT_LL_FSM_TIMEOUT_IRQ_MASK    = BIT(5),
    FLD_TAHDT_LL_RX_CRC2_ERROR_IRQ_MASK  = BIT(6),
    FLD_TAHDT_LL_CMD_DONE_IRQ_MASK       = BIT(7),
    FLD_TAHDT_LL_WLAN_DENY_IRQ_MASK      = BIT(8),
    FLD_TAHDT_LL_RX_SYNC_IRQ_MASK        = BIT(9),
    FLD_TAHDT_LL_RXCTRL_DONE_IRQ_MASK    = BIT(10),
    FLD_TAHDT_LL_RXFIFO_FULL_IRQ_MASK    = BIT(11),
};

#define reg_tahdt_ll_fsm_evtctrl     REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x28)
enum {
    FLD_TAHDT_LL_EVENTCTRL_CS = BIT_RNG(0, 3),
};

#define reg_tahdt_ll_counter0         REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x29)
enum {
    FLD_TAHDT_LL_NAK_CNT = BIT_RNG(0, 3),
    FLD_TAHDT_LL_OLD_CNT = BIT_RNG(4, 7),
};

#define reg_tahdt_ll_counter1         REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x2a)
enum {
    FLD_TAHDT_LL_CRC_CNT = BIT_RNG(0, 3),
};

#define reg_tahdt_ll_trx_field         REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x2b)
enum {
    FLD_TAHDT_LL_TX_MD   = BIT(0),
    FLD_TAHDT_LL_TX_SN   = BIT(1),
    FLD_TAHDT_LL_TX_NESN = BIT(2),
    FLD_TAHDT_LL_RX_MD   = BIT(3),
    FLD_TAHDT_LL_RX_SN   = BIT(4),
    FLD_TAHDT_LL_RX_NESN = BIT(5),
};

#define reg_tahdt_ll_ts_ctrl          REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x2c)
enum {
    FLD_TAHDT_LL_TXON_TS_EN = BIT(0),
    FLD_TAHDT_LL_TXEN_TS_EN = BIT(1),
    FLD_TAHDT_LL_TXDONE_TS_EN = BIT(2),
    FLD_TAHDT_LL_RXSYNC_TS_EN = BIT(3),
    FLD_TAHDT_LL_RXDONE_TS_EN = BIT(4),
};

#define reg_tahdt_ll_txstart_timestamp    REG_ADDR32(TAHDT_LL_BASE_ADDR + 0x30)
#define reg_tahdt_ll_txdone_timestamp     REG_ADDR32(TAHDT_LL_BASE_ADDR + 0x34)
#define reg_tahdt_ll_rxsync_timestamp     REG_ADDR32(TAHDT_LL_BASE_ADDR + 0x38)
#define reg_tahdt_ll_rxdone_timestamp     REG_ADDR32(TAHDT_LL_BASE_ADDR + 0x3c)

#define reg_tahdt_ll_trx_commit_ctrl  REG_ADDR8(TAHDT_LL_BASE_ADDR + 0x40)
enum {
    FLD_TAHDT_LL_TX_COMMIT_CTRL = BIT(0),
    FLD_TAHDT_LL_RX_COMMIT_CTRL = BIT(1),
};


///*******************************      tahdt dma registers      ******************************/
#define reg_tahdt_dma_ctrl(i)  REG_ADDR32(TAHDT_DMA_BASE_ADDR + 0x44 + (i) * 0x14)
enum {
    FLD_TAHDT_DMA_CHANNEL_ENABLE        = BIT(0),
    FLD_TAHDT_DMA_CHANNEL_TC_MASK       = BIT(1),
    FLD_TAHDT_DMA_CHANNEL_ERR_MASK      = BIT(2),
    FLD_TAHDT_DMA_CHANNEL_ABT_MASK      = BIT(3),
    FLD_TAHDT_DMA_CHANNEL_DST_REQ_SEL   = BIT_RNG(4, 8),
    FLD_TAHDT_DMA_CHANNEL_SRC_REQ_SEL   = BIT_RNG(9, 13),
    FLD_TAHDT_DMA_CHANNEL_DST_ADDR_CTRL = BIT_RNG(14, 15),
    FLD_TAHDT_DMA_CHANNEL_SRC_ADDR_CTRL = BIT_RNG(16, 17),
    FLD_TAHDT_DMA_CHANNEL_DST_MODE      = BIT(18),
    FLD_TAHDT_DMA_CHANNEL_SRC_MODE      = BIT(19),
    FLD_TAHDT_DMA_CHANNEL_DST_WIDTH     = BIT_RNG(20, 21),
    FLD_TAHDT_DMA_CHANNEL_SRC_WIDTH     = BIT_RNG(22, 23),
    FLD_TAHDT_DMA_CHANNEL_SRC_BURST_SIZE= BIT_RNG(24, 26),
    FLD_TAHDT_DMA_CHANNEL_READ_NUM_EN   = BIT(28),
    FLD_TAHDT_DMA_CHANNEL_PRIORITY      = BIT(29),
    FLD_TAHDT_DMA_CHANNEL_WRITE_NUM_EN  = BIT(30),
    FLD_TAHDT_DMA_CHANNEL_AUTO_ENABLE_EN= BIT(31),
};

#define reg_tahdt_dma_ctrl0(i)    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x44 + (i) * 0x14)
#define reg_tahdt_dma_ctrl3(i)    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x47 + (i) * 0x14)
enum {
    FLD_TAHDT_DMA_SRC_BURST_SIZE = BIT_RNG(0, 2),
    FLD_TAHDT_DMA_R_NUM_EN       = BIT(4),
    FLD_TAHDT_DMA_PRIORITY       = BIT(5),
    FLD_TAHDT_DMA_W_NUM_EN       = BIT(6),
    FLD_TAHDT_DMA_AUTO_ENABLE_EN = BIT(7),
};

#define reg_tahdt_dma_src_addr(i) REG_ADDR32(TAHDT_DMA_BASE_ADDR + 0x48 + (i) * 0x14)
#define reg_tahdt_dma_dst_addr(i) REG_ADDR32(TAHDT_DMA_BASE_ADDR + 0x4c + (i) * 0x14)

#define reg_tahdt_dma_trans_size(i)   REG_ADDR32(TAHDT_DMA_BASE_ADDR + 0x50 + (i) * 0x14)
enum {
    FLD_TAHDT_DMA_TX_SIZE     = BIT_RNG(0, 21),
    FLD_TAHDT_DMA_TX_SIZE_IDX = BIT_RNG(22, 23),
};

#define reg_tahdt_dma_tx_size     REG_ADDR16(TAHDT_DMA_BASE_ADDR + 0xf0)
#define reg_tahdt_dma_tx_chn_dep  REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0xf3)

#define reg_tahdt_dma_rx_size     REG_ADDR16(TAHDT_DMA_BASE_ADDR + 0xf6)
#define reg_tahdt_dma_rx_wptr_mask REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x10d)

#define reg_tahdt_dma_rx_wptr     REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0xf4)
enum {
    FLD_TAHDT_DMA_WPTR_MASK = BIT_RNG(0, 4),
};
#define reg_tahdt_dma_rx_rptr     REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0xf5)
enum {
    FLD_TAHDT_DMA_RPTR_MASK = BIT_RNG(0, 4),
    FLD_TAHDT_DMA_RPTR_SET  = BIT(5),
    FLD_TAHDT_DMA_RPTR_NEXT = BIT(6),
    FLD_TAHDT_DMA_RPTR_CLR  = BIT(7),
};
#define reg_tahdt_dma_tx_wptr(i)  REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x100 + (i << 1))
#define reg_tahdt_dma_tx_rptr(i)  REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x101 + (i << 1))
#define reg_tahdt_dma_tx_wptr6    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x118)
#define reg_tahdt_dma_tx_rptr6    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x119)
#define reg_tahdt_dma_tx_wptr7    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x11a)
#define reg_tahdt_dma_tx_rptr7    REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x11b)


#define reg_tahdt_dma_auto_ctrl   REG_ADDR8(TAHDT_DMA_BASE_ADDR + 0x10c)
enum {
    FLD_TAHDT_DMA_TX_MULTI_EN     = BIT(0),
    FLD_TAHDT_DMA_RX_MULTI_EN     = BIT(1),
    FLD_TAHDT_DMA_CH_0_RNUM_EN_BK = BIT(2),
    FLD_TAHDT_DMA_CH_1_RNUM_EN_BK = BIT(3),
    FLD_TAHDT_DMA_CH1_RX_ERR_EN   = BIT(4),
    FLD_TAHDT_DMA_DMA_REQ_D1_EN   = BIT(5),
};

#endif /*HAL_TAHDT_REG_H*/

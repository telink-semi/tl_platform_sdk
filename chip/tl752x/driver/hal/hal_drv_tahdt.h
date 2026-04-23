/********************************************************************************************************
 * @file    hal_drv_tahdt.h
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


#ifndef __HAL_DRV_TAHDT_H__
#define __HAL_DRV_TAHDT_H__

#include "hal/hal_tahdt_reg.h"
#include "hal/hal_rf_common.h"


/**
 *@brief    This interface configures physical layer parameters for TAHDT Wireless Frame Type 1.
 *@return   none.
 */
static inline void tahdt_mdm_frame1_setup(void)
{
    // reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x61) | 0x2;
    /*don't modify pilot interval*/
    reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x67) | 0x0;
    reg_tahdt_mdm_cfg1 = 64;
    reg_tahdt_mdm_rx_cfg0 = (reg_tahdt_mdm_rx_cfg0 & 0x80) | 0x41;
    reg_tahdt_mdm_rx_cfg1 = 0x40;
    reg_tahdt_mdm_rx_cfg2 = 0xdc;
    reg_tahdt_mdm_rx_cfg3 = 0x95;
    reg_tahdt_mdm_rx_cfg4 = (reg_tahdt_mdm_rx_cfg4 & 0x80) | 30;
    reg_tahdt_mdm_rx_cfg5 = (reg_tahdt_mdm_rx_cfg5 & 0xC0) | 30;
    reg_tahdt_mdm_rx_cfg6 = 0x2A;
    reg_tahdt_mdm_rx_cfg7 = (reg_tahdt_mdm_rx_cfg7 & 0xF0) | 7;
    reg_tahdt_mdm_rx_cfg8 = 252;
    reg_tahdt_mdm_rx_cfg9 = reg_tahdt_mdm_rx_cfg9 & 0xFE;
}

/**
 *@brief    This interface configures physical layer parameters for TAHDT Wireless Frame Type 2.
 *@return   none.
 */
static inline void tahdt_mdm_frame2_setup(void)
{
    // reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x61) | 0xA;
    /*don't modify pilot interval*/
    reg_tahdt_mdm_cfg0 = ((reg_tahdt_mdm_cfg0 & 0x67) | 0x8);
    reg_tahdt_mdm_cfg1 = 128;//TODO:The configuration related to Demod is not related to the clock and may need to be adjusted during distance testing
    reg_tahdt_mdm_rx_cfg0 = (reg_tahdt_mdm_rx_cfg0 & 0x80) | 0x5E;
    reg_tahdt_mdm_rx_cfg1 = 0x00;
    reg_tahdt_mdm_rx_cfg2 = 0x84;
    reg_tahdt_mdm_rx_cfg3 = 0x93;
    reg_tahdt_mdm_rx_cfg4 = (reg_tahdt_mdm_rx_cfg4 & 0x80) | 61;// sync threshold
    reg_tahdt_mdm_rx_cfg5 = (reg_tahdt_mdm_rx_cfg5 & 0xC0) | 30;
    reg_tahdt_mdm_rx_cfg6 = 0x2A;
    reg_tahdt_mdm_rx_cfg7 = (reg_tahdt_mdm_rx_cfg7 & 0xF0) | 5;
    reg_tahdt_mdm_rx_cfg8 = 252;
    reg_tahdt_mdm_rx_cfg9 = reg_tahdt_mdm_rx_cfg9 & 0xFE;
}

/**
 *@brief    This interface configures physical layer parameters for TAHDT Wireless Frame Type 3.
 *@return   none.
 */
static inline void tahdt_mdm_frame3_setup(void)
{
    // reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x61) | 0x12;
    /*don't modify pilot interval*/
    reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x67) | 0x10;
    reg_tahdt_mdm_cfg1 = 128;
    reg_tahdt_mdm_rx_cfg0 = (reg_tahdt_mdm_rx_cfg0 & 0x80) | 0x5E;
    reg_tahdt_mdm_rx_cfg1 = 0x05;
    reg_tahdt_mdm_rx_cfg2 = 0x84;
    reg_tahdt_mdm_rx_cfg3 = 0x93;
    reg_tahdt_mdm_rx_cfg4 = (reg_tahdt_mdm_rx_cfg4 & 0x80) | 60;
    reg_tahdt_mdm_rx_cfg5 = (reg_tahdt_mdm_rx_cfg5 & 0xC0) | 30;
    reg_tahdt_mdm_rx_cfg6 = 0x2A;
    reg_tahdt_mdm_rx_cfg7 = (reg_tahdt_mdm_rx_cfg7 & 0xF0) | 5;
    reg_tahdt_mdm_rx_cfg8 = 252;
    reg_tahdt_mdm_rx_cfg9 = reg_tahdt_mdm_rx_cfg9 & 0xFE;
}

/**
 *@brief    This interface configures physical layer parameters for TAHDT Wireless Frame Type 4.
 *@return   none.
 */
static inline void tahdt_mdm_frame4_setup(void)
{
    // reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x61) | 0x1A;
    /*don't modify pilot interval*/
    reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & 0x67) | 0x18;
    reg_tahdt_mdm_cfg1 = 128;
    reg_tahdt_mdm_rx_cfg0 = (reg_tahdt_mdm_rx_cfg0 & 0x80) | 0x5E;
    reg_tahdt_mdm_rx_cfg1 = 0x05;
    reg_tahdt_mdm_rx_cfg2 = 0x84;
    reg_tahdt_mdm_rx_cfg3 = 0x93;
    reg_tahdt_mdm_rx_cfg4 = (reg_tahdt_mdm_rx_cfg4 & 0x80) | 60;
    reg_tahdt_mdm_rx_cfg5 = (reg_tahdt_mdm_rx_cfg5 & 0xC0) | 30;
    reg_tahdt_mdm_rx_cfg6 = 0x2A;
    reg_tahdt_mdm_rx_cfg7 = (reg_tahdt_mdm_rx_cfg7 & 0xF0) | 5;
    reg_tahdt_mdm_rx_cfg8 = 252;
    reg_tahdt_mdm_rx_cfg9 = reg_tahdt_mdm_rx_cfg9 & 0xFE;
}

/**
 *@brief This function initializes PHY layer configuration for TAHDT 1M rate mode
 *@return   none.
 */
static inline void tahdt_radio_1m_setup(void)
{
    //TODO:To fix intermediate frequency is not accuracy
    //In order to switch modes and make modifications, further confirmation and verification are required
    REG_ADDR32(0x50421024) = (REG_ADDR32(0x50421024) & 0xFFCFFFFF);
    REG_ADDR32(0x50421074) = (REG_ADDR32(0x50421074) & 0xFF800000) | 0x200001;
    REG_ADDR32(0x50421064) = (REG_ADDR32(0x50421064) & 0xFFBFFFFF);
    REG_ADDR32(0x50421108) = (REG_ADDR32(0x50421108) & 0xFFFFFCFF) | 0x0200;// txlpf bw trim for tahdt 4M mode add by shilei 20251203

    reg_tahdt_radio_mode_cfg_rx1_1 = reg_tahdt_radio_mode_cfg_rx1_1 & (~FLD_TAHDT_RADIO_RX_MODE);
    reg_tahdt_mdm_mode_ctrl_tx1_0 = reg_tahdt_mdm_mode_ctrl_tx1_0 & (~FLD_TAHDT_MDM_BLE_MODE_TX);
    reg_tahdt_radio_mode_cfg_tx1_0 = reg_tahdt_radio_mode_cfg_tx1_0 & (~FLD_TAHDT_RADIO_BLE_MODE_TX);

    reg_tahdt_radio_hsspl_ctrl0 = (reg_tahdt_radio_hsspl_ctrl0 & 0xF0) | 0x03;
    reg_tahdt_radio_hsspl_ctrl1 = (reg_tahdt_radio_hsspl_ctrl1 & 0xF0) | 0x03;
    reg_tahdt_radio_hsspl_ctrl2 = reg_tahdt_radio_hsspl_ctrl2 & (~FLD_TAHDT_RADIO_RXC_MODE_OW);

    reg_tahdt_radio_mode_cfg_tx3_0 = reg_tahdt_radio_mode_cfg_tx3_0 | FLD_TAHDT_RADIO_TX_IQ_MODE_EN_BLE;

    reg_tahdt_bb_frame_ctrl1 = reg_tahdt_bb_frame_ctrl1 & (~FLD_TAHDT_BB_SYMB_RATE);

    reg_tahdt_bb_trailer_ctrl = 0x82;
    /**
     * This register must be configured for hardware RSSI calculation.
     * By default, the RSSI value needs to be offset by subtracting 110 after reading. Based on current test results,
     * it is found that an additional fixed value must be subtracted according to different modes to obtain the accurate RSSI.
     */
    reg_rf_gaim_comp0= 0x50; //grx_comp for RSSI:-60(0x44),-40(0x56), -30(0x62) -20(0x6c)
//    REG_ADDR8(RADIOADDR+0x21) = (REG_ADDR8(RADIOADDR+0x21) & 0xDF); //rxc_norrow_chf_sel
//    REG_ADDR8(MODEMADDR+0x13a) = (REG_ADDR8(MODEMADDR+0x13a) & 0xFB); //rxc_norrow_chf_sel
}

/**
 *@brief This function initializes PHY layer configuration for TAHDT 2M rate mode
 *@return   none.
 */
static inline void tahdt_radio_2m_setup(void)
{
    //TODO:To fix intermediate frequency is not accuracy
    //In order to switch modes and make modifications, further confirmation and verification are required
    REG_ADDR32(0x50421024) = (REG_ADDR32(0x50421024) & 0xFFCFFFFF);
    REG_ADDR32(0x50421074) = (REG_ADDR32(0x50421074) & 0xFF800000) | 0x200001;
    REG_ADDR32(0x50421064) = (REG_ADDR32(0x50421064) & 0xFFBFFFFF);
    REG_ADDR32(0x50421108) = (REG_ADDR32(0x50421108) & 0xFFFFFCFF) | 0x0200;// txlpf bw trim for tahdt 4M mode add by shilei 20251203

    reg_tahdt_radio_mode_cfg_rx1_1 = reg_tahdt_radio_mode_cfg_rx1_1 | FLD_TAHDT_RADIO_RX_MODE;
    reg_tahdt_mdm_mode_ctrl_tx1_0 = reg_tahdt_mdm_mode_ctrl_tx1_0 | FLD_TAHDT_MDM_BLE_MODE_TX;
    reg_tahdt_radio_mode_cfg_tx1_0 = reg_tahdt_radio_mode_cfg_tx1_0 | FLD_TAHDT_RADIO_BLE_MODE_TX;

    reg_tahdt_radio_hsspl_ctrl0 = (reg_tahdt_radio_hsspl_ctrl0 & 0xF0) | 0x07;
    reg_tahdt_radio_hsspl_ctrl1 = (reg_tahdt_radio_hsspl_ctrl1 & 0xF0) | 0x07;
    reg_tahdt_radio_hsspl_ctrl2 = reg_tahdt_radio_hsspl_ctrl2 | FLD_TAHDT_RADIO_RXC_MODE_OW;

    reg_tahdt_radio_mode_cfg_tx3_0 = reg_tahdt_radio_mode_cfg_tx3_0 | FLD_TAHDT_RADIO_TX_IQ_MODE_EN_BLE;
    reg_tahdt_bb_frame_ctrl1 = (reg_tahdt_bb_frame_ctrl1 & (~FLD_TAHDT_BB_SYMB_RATE)) | 0x1;

    reg_tahdt_bb_trailer_ctrl = 0x83;
    /**
     * This register must be configured for hardware RSSI calculation.
     * By default, the RSSI value needs to be offset by subtracting 110 after reading. Based on current test results,
     * it is found that an additional fixed value must be subtracted according to different modes to obtain the accurate RSSI.
     */
    reg_rf_gaim_comp0= 0x48; //grx_comp for RSSI:-60(0x44),-40(0x56), -30(0x62) -20(0x6c)
//    REG_ADDR8(RADIOADDR+0x21) = (REG_ADDR8(RADIOADDR+0x21) & 0xDF) | 0x20; //rxc_norrow_chf_sel
//    REG_ADDR8(MODEMADDR+0x13a) = (REG_ADDR8(MODEMADDR+0x13a) & 0xFB); //rxc_norrow_chf_sel
}

/**
 *@brief This function initializes PHY layer configuration for TAHDT 4M rate mode
 *@return   none.
 */
static inline void tahdt_radio_4m_setup(void)
{
    //TODO:To fix intermediate frequency is not accuracy
    //In order to switch modes and make modifications, further confirmation and verification are required
    REG_ADDR32(0x50421024) = (REG_ADDR32(0x50421024) & 0xFFCFFFFF) | 0x300000;
    REG_ADDR32(0x50421074) = (REG_ADDR32(0x50421074) & 0xFF800000) | 0x400002;
    REG_ADDR32(0x50421064) = (REG_ADDR32(0x50421064) & 0xFFBFFFFF) | 0x400000;
    REG_ADDR32(0x50421108) = (REG_ADDR32(0x50421108) & 0xFFFFFCFF);// txlpf bw trim for tahdt 4M mode add by shilei 20251203

    reg_tahdt_radio_mode_cfg_rx1_1 = reg_tahdt_radio_mode_cfg_rx1_1 | FLD_TAHDT_RADIO_RX_MODE;
    reg_tahdt_mdm_mode_ctrl_tx1_0 = reg_tahdt_mdm_mode_ctrl_tx1_0 | FLD_TAHDT_MDM_BLE_MODE_TX;
    reg_tahdt_radio_mode_cfg_tx1_0 = reg_tahdt_radio_mode_cfg_tx1_0 | FLD_TAHDT_RADIO_BLE_MODE_TX;

    reg_tahdt_radio_hsspl_ctrl0 = (reg_tahdt_radio_hsspl_ctrl0 & 0xF0) | 0x0B;
    reg_tahdt_radio_hsspl_ctrl1 = (reg_tahdt_radio_hsspl_ctrl1 & 0xF0) | 0x0B;
    reg_tahdt_radio_hsspl_ctrl2 = reg_tahdt_radio_hsspl_ctrl2 | FLD_TAHDT_RADIO_RXC_MODE_OW;

    reg_tahdt_radio_mode_cfg_tx3_0 = reg_tahdt_radio_mode_cfg_tx3_0 | FLD_TAHDT_RADIO_TX_IQ_MODE_EN_BLE;
    reg_tahdt_bb_frame_ctrl1 = (reg_tahdt_bb_frame_ctrl1 & (~FLD_TAHDT_BB_SYMB_RATE)) | 0x2;

    reg_tahdt_bb_trailer_ctrl = 0x89;
    /**
     * This register must be configured for hardware RSSI calculation.
     * By default, the RSSI value needs to be offset by subtracting 110 after reading. Based on current test results,
     * it is found that an additional fixed value must be subtracted according to different modes to obtain the accurate RSSI.
     */
    //0x65 -27,0x67 -25,0x61 -31
    reg_rf_gaim_comp0= 0x4a; //grx_comp for RSSI:-60(0x44),-40(0x56), -30(0x62) -20(0x6c)
//    REG_ADDR8(RADIOADDR+0x21) = (REG_ADDR8(RADIOADDR+0x21) & 0xDF) | 0x20; //rxc_norrow_chf_sel
//    REG_ADDR8(MODEMADDR+0x13a) = (REG_ADDR8(MODEMADDR+0x13a) & 0xFB) | 0x4; //rxc_norrow_chf_sel
}

static inline void tahdt_bb_soft_reset(unsigned char reset)
{
    reg_tahdt_bb_soft_reset = reset;
}

static inline void tahdt_bb_soft_reset_all(void)
{
    reg_tahdt_bb_soft_reset = reg_tahdt_bb_soft_reset | 
        (FLD_TAHDT_BB_SOFT_RST_P | FLD_TAHDT_BB_CRYPT_SOFT_RST_P | FLD_TAHDT_BB_POLAR_SOFT_RST_P);
}

/**
 * @brief    This function is used to set the TAHDT Wireless Frame Type
 * @param[in]   frame_type    - The TAHDT Wireless Frame Type
 * @return   none.
 */
static inline void tahdt_bb_set_frame_type(unsigned char frame_type)
{
    reg_tahdt_bb_frame_indicator = (reg_tahdt_bb_frame_indicator & (~FLD_TAHDT_BB_FRAME_ALL)) | (1 << (frame_type & 0x03));

    if(frame_type == 0) tahdt_mdm_frame1_setup();
    else if(frame_type == 1) tahdt_mdm_frame2_setup();
    else if(frame_type == 2) tahdt_mdm_frame3_setup();
    else if(frame_type == 3) tahdt_mdm_frame4_setup();
}

static inline void tahdt_bb_set_mcs_type(unsigned char mcs_type)
{
    reg_tahdt_bb_frame_indicator = (reg_tahdt_bb_frame_indicator & (~FLD_TAHDT_BB_MCS)) | ((mcs_type & 0x0F) << 4);
}

static inline void tahdt_bb_set_ctrl_type(unsigned char ctrl_type)
{
    reg_tahdt_bb_frame_ctrl0 = (reg_tahdt_bb_frame_ctrl0 & (~FLD_TAHDT_BB_CTRL_TYPE)) | (ctrl_type & 0x1F);
}

static inline void tahdt_bb_set_phy_type(unsigned char phy_type)
{
    reg_tahdt_bb_frame_ctrl1 = (reg_tahdt_bb_frame_ctrl1 & (~FLD_TAHDT_BB_SYMB_RATE)) | (phy_type & 0x03);

    if(phy_type == 0) tahdt_radio_1m_setup();
    else if(phy_type == 1) tahdt_radio_2m_setup();
    else if(phy_type == 2) tahdt_radio_4m_setup();
}

static inline void tahdt_bb_set_pilot_type(unsigned char pilot_type)
{
    reg_tahdt_mdm_cfg0 = (reg_tahdt_mdm_cfg0 & (~FLD_TAHDT_MDM_PILOT_INTERVAL)) | ((pilot_type & 0x03) << 1);
    reg_tahdt_bb_frame_ctrl1 = (reg_tahdt_bb_frame_ctrl1 & (~FLD_TAHDT_BB_PILOT_INTERVAL)) | ((pilot_type & 0x03) << 2);
}

static inline void tahdt_bb_set_pdu_size(unsigned short pdu_size) 
{
    reg_tahdt_bb_trx_pldlen = pdu_size;
}

static inline void tahdt_bb_set_whiten(unsigned char seed)
{
    reg_tahdt_bb_whiten_ctrl = (seed & FLD_TAHDT_BB_WHITEN_INIT) | FLD_TAHDT_BB_WHITEN_EN;
}

static inline void tahdt_bb_close_whiten(void)
{
    reg_tahdt_bb_whiten_ctrl = reg_tahdt_bb_whiten_ctrl & (~FLD_TAHDT_BB_WHITEN_EN);
}

static inline void tahdt_bb_enable_crc(void)
{
    reg_tahdt_bb_dp_ctrl = reg_tahdt_bb_dp_ctrl | FLD_TAHDT_BB_CRC_EN;
}

static inline void tahdt_bb_disable_crc(void)
{
    reg_tahdt_bb_dp_ctrl = reg_tahdt_bb_dp_ctrl & (~reg_tahdt_bb_dp_ctrl);
}

static inline void tahdt_bb_set_crc_type(unsigned char crc_type) 
{
    reg_tahdt_bb_dp_ctrl = (reg_tahdt_bb_dp_ctrl & (~FLD_TAHDT_BB_CRC_TYPE)) | 
                         ((crc_type << 1) & FLD_TAHDT_BB_CRC_TYPE) | FLD_TAHDT_BB_CRC_EN;
}

static inline void tahdt_bb_set_dat_Crc(unsigned int seed)
{
    reg_tahdt_bb_crc_init = seed;
}

static inline void tahdt_bb_set_seg_crc(unsigned int seed)
{
    reg_tahdt_bb_datseg_crc_init0 = seed & 0xFF;
    reg_tahdt_bb_datseg_crc_init1 = (seed >> 8) & 0xFF;
    reg_tahdt_bb_datseg_crc_init1 = (seed >> 16) & 0xFF;
}

static inline void tahdt_bb_set_hec_crc(unsigned int seed)
{
    reg_tahdt_bb_hec_init0 = seed & 0xFF;
    reg_tahdt_bb_hec_init1 = (seed >> 8) & 0xFF;
    reg_tahdt_bb_hec_init2 = (seed >> 16) & 0xFF;
}

static inline void tahdt_bb_set_logic_id(unsigned int logic_id) 
{
    reg_tahdt_bb_llid0 = logic_id & 0xFF;
    reg_tahdt_bb_llid1 = (logic_id >> 8) & 0xFF;
    reg_tahdt_bb_llid2 = (logic_id >> 16) & 0xFF;
}

static inline void tahdt_bb_set_m_init(unsigned char seed)
{
    reg_tahdt_bb_m_init = FLD_TAHDT_BB_M_INIT_EN | (seed & FLD_TAHDT_BB_M_INIT);
}

/**
 * @brief This function is used to choose an M-sequence (Maximal-length sequence)
 *       which serves as a pseudo-random code for generating synchronization signals.
 *       The selected sequence ensures robust synchronization and scrambling in physical layer communication
 * @param[in] seq_type  -SparkLink m sequence number, (range:0~5）
 * @return   none.
 */
static inline void tahdt_bb_set_seq_type(unsigned char seq_type)
{
    //SparkLink m sequence number, 0~5
    reg_tahdt_bb_m_seqn = (reg_tahdt_bb_m_seqn & (~FLD_TAHDT_BB_M_SEQN)) | (seq_type & 0x7);
}

static inline void tahdt_bb_start_man_sync(void)
{
    reg_tahdt_bb_m_seqn = reg_tahdt_bb_m_seqn | FLD_TAHDT_BB_SYNCWORD_MAN_EN;
}

static inline void tahdt_bb_close_man_sync(void)
{
    reg_tahdt_bb_m_seqn = reg_tahdt_bb_m_seqn & (~FLD_TAHDT_BB_SYNCWORD_MAN_EN);
}

static inline void tahdt_bb_set_syncword(unsigned int syncword)
{
    reg_tahdt_bb_syncword_man_w0 = syncword;
}

static inline void tahdt_bb_set_dual_syncword(unsigned int syncword0, unsigned int syncword1)
{
    reg_tahdt_bb_syncword_man_w0 = syncword0;
    reg_tahdt_bb_syncword_man_w1 = syncword1;
}

static inline void tahdt_bb_set_rf_clock(unsigned char clock_mhz)
{
    reg_tahdt_bb_clk_select = clock_mhz;
}

static inline unsigned char tahdt_bb_read_fifo_ind(void)
{
    return reg_tahdt_bb_fifo_indicator;
}

static inline unsigned char tahdt_bb_read_error_ind(void)
{
    return reg_tahdt_bb_error_indicator;
}

static inline void tahdt_bb_gen_syncword(void)
{
    reg_tahdt_bb_syncword0 = FLD_TAHDT_BB_SYNCGEN_START_P; //SparkLink syncword generation start pulse
    while((reg_tahdt_bb_syncword0 & FLD_TAHDT_BB_SYNCGEN_VALID) == 0){} //SparkLink syncword valid level signal
    reg_tahdt_bb_syncword0 = FLD_TAHDT_BB_SYNCGEN_DONE_CLR_P; //SparkLink syncword generation done clear pulse
}

static inline unsigned int tahdt_bb_get_syncword(void)
{
    return ((unsigned int)(reg_tahdt_bb_syncword1)) | 
           ((unsigned int)(reg_tahdt_bb_syncword2 << 8)) | 
           ((unsigned int)(reg_tahdt_bb_syncword3 << 16)) | 
           ((unsigned int)(reg_tahdt_bb_syncword4 << 24));
}

static inline unsigned int tahdt_bb_get_syncword_h(void)
{
    return ((unsigned int)(reg_tahdt_bb_syncword5)) | 
           ((unsigned int)(reg_tahdt_bb_syncword6 << 8)) | 
           ((unsigned int)(reg_tahdt_bb_syncword7 << 16)) | 
           ((unsigned int)(reg_tahdt_bb_syncword8 << 24));
}

static inline void tahdt_bb_gen_rf_channel(unsigned char is_llid) //LLID or Syncword
{
    reg_tahdt_bb_fh_ctrl = (reg_tahdt_bb_fh_ctrl & (~FLD_TAHDT_BB_FH_PARA2_SEL)) | ((is_llid << 3) & FLD_TAHDT_BB_FH_PARA2_SEL);
    reg_tahdt_bb_fh_ctrl = reg_tahdt_bb_fh_ctrl | FLD_TAHDT_BB_FH_START_P;
    __asm__("fence iorw, iorw");
    while((reg_tahdt_bb_fh_status & FLD_TAHDT_BB_FH_STATUS) == 1){}
    reg_tahdt_bb_fh_status = FLD_TAHDT_BB_FH_STATUS_CLR_P | 0x80;
}

static inline void tahdt_bb_set_freq_slot(unsigned short slot_cnt) 
{
    reg_tahdt_bb_fh_slot_cnt = slot_cnt;
}

static inline void tahdt_bb_set_2g4_chnmap(unsigned char *chnmap) 
{
    reg_tahdt_bb_fh_chmap_w0 = ((unsigned int *)chnmap)[0];
    reg_tahdt_bb_fh_chmap_w1 = ((unsigned int *)chnmap)[1];
    reg_tahdt_bb_fh_chmap_hw2 = ((unsigned short *)chnmap)[4];
}

static inline void tahdt_bb_set_2g4_chnmap_byte(unsigned char *chnmap) 
{
    reg_tahdt_bb_fh_chmap0 = chnmap[0];
    reg_tahdt_bb_fh_chmap1 = chnmap[1];
    reg_tahdt_bb_fh_chmap2 = chnmap[2];
    reg_tahdt_bb_fh_chmap3 = chnmap[3];
    reg_tahdt_bb_fh_chmap4 = chnmap[4];
    reg_tahdt_bb_fh_chmap5 = chnmap[5];
    reg_tahdt_bb_fh_chmap6 = chnmap[6];
    reg_tahdt_bb_fh_chmap7 = chnmap[7];
    reg_tahdt_bb_fh_chmap8 = chnmap[8];
    reg_tahdt_bb_fh_chmap9 = chnmap[9];
}

static inline void tahdt_bb_clear_all_chnmap(void)
{
    reg_tahdt_bb_fh_chmap_w0 = 0;
    reg_tahdt_bb_fh_chmap_w1 = 0;
    reg_tahdt_bb_fh_chmap_w2 = 0;
    reg_tahdt_bb_fh_chmap_w3 = 0;
    reg_tahdt_bb_fh_chmap_w4 = 0;
    reg_tahdt_bb_fh_chmap_w5 = 0;
    reg_tahdt_bb_fh_chmap_b6 = 0;
}

static inline void tahdt_bb_set_crypt_ctrl(unsigned char ctrl) 
{
    reg_tahdt_bb_crypt_ctrl = ctrl;
}

static inline void tahdt_bb_close_crypt(void)
{
    reg_tahdt_bb_crypt_ctrl = 0x00;
}

static inline void tahdt_bb_set_crypt_slot(unsigned int slot, unsigned short day_cnt) 
{
    reg_tahdt_bb_crypt_clkslot0 = slot & 0xFF;
    reg_tahdt_bb_crypt_clkslot1 = (slot>>8) & 0xFF;
    reg_tahdt_bb_crypt_clkslot2 = (slot>>16) & 0xFF;
    reg_tahdt_bb_crypt_clkslot3 = ((slot >> 24) & FLD_TAHDT_BB_CLK_SLOT_24_29) |
                                (((day_cnt >> 8) << 6) & FLD_TAHDT_BB_DAYCOUNTER_8_9);
    reg_tahdt_bb_crypt_daycnt = day_cnt & 0xFF;
}

static inline void tahdt_bb_set_crypt_tx_cnt(unsigned long long count, unsigned char no_inc) 
{
    reg_tahdt_bb_crypt_txccmcnt_w0 = count & 0xFFFFFFFF;
    reg_tahdt_bb_crypt_txccmcnt_b1 = ((count >> 32) & FLD_TAHDT_BB_TXCCMPKTCNT_32_38) | 
                                  ((no_inc << 7) & FLD_TAHDT_BB_TXCCMPKTCNT_AUTOINC_DSB);
}
static inline void tahdt_bb_set_crypt_rx_cnt(unsigned long long count, unsigned char no_inc) 
{
    reg_tahdt_bb_crypt_rxccmcnt_w0 = count & 0xFFFFFFFF;
    reg_tahdt_bb_crypt_rxccmcnt_b1 = ((count >> 32) & FLD_TAHDT_BB_RXCCMPKTCNT_32_38) | 
                                  ((no_inc << 7) & FLD_TAHDT_BB_RXCCMPKTCNT_AUTOINC_DSB);
}

static inline void tahdt_bb_set_crypt_iv_tab(unsigned int *iv_tab) 
{
    reg_tahdt_bb_crypt_iv_w0 = iv_tab[0];
    reg_tahdt_bb_crypt_iv_w1 = iv_tab[1];
}

static inline void tahdt_bb_set_linkkey(unsigned int *linkkey) 
{
    reg_tahdt_bb_crypt_sk_w0 = linkkey[0];
    reg_tahdt_bb_crypt_sk_w1 = linkkey[1];
    reg_tahdt_bb_crypt_sk_w2 = linkkey[2];
    reg_tahdt_bb_crypt_sk_w3 = linkkey[3];
}

typedef enum {
    TAHDT_VERSION_1P0 = 0,
    TAHDT_VERSION_2P0 = 1,
} tahdt_version_e;

static inline void tahdt_bb_set_version(tahdt_version_e version)
{
    reg_tahdt_bb_version = version;
}

static inline void tahdt_bb_set_rx_maxlen(unsigned short maxlen)
{
    reg_tahdt_bb_maxlen = maxlen;
}

static inline unsigned char tahdt_bb_get_rx_gain(void)
{
    return reg_tahdt_bb_rx_gain;
}
static inline unsigned char tahdt_bb_get_rx_rssi(void)
{
    return reg_tahdt_bb_rx_rssi;
}
static inline unsigned short tahdt_bb_get_polar_pktlen(void)
{
    return reg_tahdt_bb_polar_pktlen & FLD_TAHDT_BB_POLAR_PKTLEN;
}

static inline void rf_tahdt_set_channel(unsigned char chn)
{
    unsigned char ctrim;
    unsigned int freq;

    freq = 2402+chn;

    if(freq >= 2460) ctrim = 2;
    else if(freq >= 2440) ctrim = 3;
    else if(freq >= 2416) ctrim = 4;
    else if(freq >= 2380) ctrim = 5;
    else ctrim = 7;

    if((reg_tahdt_bb_frame_ctrl1 & FLD_TAHDT_BB_SYMB_RATE) == 2)
    {
        REG_ADDR16(0x5042106c) = (freq - 3) & 0xFFFF;
    }
    else{
        REG_ADDR16(0x5042106c) = 0;
    }

    /*turn off CHNL_FREQ_DIRECT*/
    reg_tahdt_radio_txrx_dbg3_0 =  ((0x62 << 1) & FLD_TAHDT_RADIO_CHNL_FREQ_L);
    reg_tahdt_radio_txrx_dbg3_1 = (reg_tahdt_radio_txrx_dbg3_1 & (~FLD_TAHDT_RADIO_CHNL_FREQ_H)) | 
                                ((0x12) & FLD_TAHDT_RADIO_CHNL_FREQ_H);
    /*select old_ll*/
    reg_tahdt_radio_burst_cfg_txrx_1 = reg_tahdt_radio_burst_cfg_txrx_1 | FLD_TAHDT_RADIO_CH_NUM_LL_SEL;
    /*CHNL_NUM*/
    reg_tahdt_radio_burst_cfg_txrx_0 = chn;

    reg_tahdt_radio_burst_cfg_txrx_1 = (reg_tahdt_radio_burst_cfg_txrx_1 & (~FLD_TAHDT_RADIO_HOLD1)) |
                                    ((ctrim << 5) & FLD_TAHDT_RADIO_HOLD1);
}

static inline void rf_tahdt_set_txrx_off(void)
{
    
}

static inline void tahdt_ll_set_tx_settle(unsigned short time_us)
{
    reg_tahdt_ll_tx_settle = time_us;
}
static inline void tahdt_ll_set_tx_wait(unsigned short time_us)
{
    reg_tahdt_ll_tx_wait = time_us;
}
static inline void tahdt_ll_set_rx_settle(unsigned short time_us)
{
    reg_tahdt_ll_rx_settle = time_us;
}
static inline void tahdt_ll_set_rx_wait(unsigned short time_us)
{
    reg_tahdt_ll_rx_wait = time_us;
}
static inline void tahdt_ll_set_rx_timeout(unsigned short time_us)
{
    reg_tahdt_ll_timeout_enable = reg_tahdt_ll_timeout_enable | FLD_TAHDT_LL_RX_TIMEOUT_EN;
    reg_tahdt_ll_rx_timeout = time_us;
}
static inline void tahdt_ll_set_fst_timeout(unsigned int time_us)
{
    reg_tahdt_ll_timeout_enable = reg_tahdt_ll_timeout_enable | FLD_TAHDT_LL_RX_1ST_TIMEOUT_EN;
    reg_tahdt_ll_rx_1st_timeout0 = time_us & 0xFF;
    reg_tahdt_ll_rx_1st_timeout1 = (time_us >> 8) & 0xFF;
    reg_tahdt_ll_rx_1st_timeout2 = (time_us >> 16) & 0xFF;
}
static inline void tahdt_ll_set_fsm_timeout(unsigned int time_us)
{
    reg_tahdt_ll_timeout_enable = reg_tahdt_ll_timeout_enable | FLD_TAHDT_LL_FSM_TIMEOUT_EN;
    reg_tahdt_ll_fsm_timeout0 = time_us & 0xFF;
    reg_tahdt_ll_fsm_timeout1 = (time_us >> 8) & 0xFF;
    reg_tahdt_ll_fsm_timeout2 = (time_us >> 16) & 0xFF;
}
static inline void tahdt_ll_set_schedule_time(unsigned int time_tick)
{
    reg_tahdt_ll_func_enable = reg_tahdt_ll_func_enable & (~FLD_TAHDT_LL_FUNC_CMD_SCHEDULE_EN);
    reg_tahdt_ll_cmd_schedule = time_tick;
    reg_tahdt_ll_func_enable = reg_tahdt_ll_func_enable | FLD_TAHDT_LL_FUNC_CMD_SCHEDULE_EN;
}

static inline void tahdt_ll_start_auto_sn(void)
{
    reg_tahdt_ll_func_enable = reg_tahdt_ll_func_enable | (FLD_TAHDT_LL_FUNC_MD_EN | FLD_TAHDT_LL_FUNC_SN_EN | FLD_TAHDT_LL_FUNC_NESN_EN);
}
static inline void tahdt_ll_close_auto_sn(void)
{
    reg_tahdt_ll_func_enable = reg_tahdt_ll_func_enable & (~(FLD_TAHDT_LL_FUNC_MD_EN | FLD_TAHDT_LL_FUNC_SN_EN | FLD_TAHDT_LL_FUNC_NESN_EN));
}
static inline void tahdt_ll_setSnNesn(unsigned char txSn, unsigned char txNesn, unsigned char rxSn, unsigned char rxNesn)
{
    ((void)(txSn));
    ((void)(txNesn));
    ((void)(rxSn));
    ((void)(rxNesn));
}

#define tahdt_tx_packet_dma_len(rf_data_len)         (((rf_data_len)+3)/4)|(((rf_data_len) % 4)<<22)

//TODO adjust D25F and N22
#if defined(MCU_CORE_TL752X_N22)
#define convert_ram_addr_cpu2bus(addr)              (((unsigned int)addr) | 0x50000000)
#else
#define convert_ram_addr_cpu2bus(addr)              ((unsigned int)addr)
#endif

typedef enum {
    TAHDT_DMA_TX = 0,
    TAHDT_DMA_RX = 1,
} tahdt_dma_ch_e;

static inline void tahdt_dma_ch_en(tahdt_dma_ch_e ch)
{
    reg_tahdt_dma_ctrl(ch) = reg_tahdt_dma_ctrl(ch) | (FLD_TAHDT_DMA_CHANNEL_ENABLE);
}

static inline void tahdt_dma_ch_dis(tahdt_dma_ch_e ch)
{
    reg_tahdt_dma_ctrl(ch) = reg_tahdt_dma_ctrl(ch) & (~(FLD_TAHDT_DMA_CHANNEL_ENABLE));
}

static inline void tahdt_dma_set_src_addr(tahdt_dma_ch_e ch, unsigned char *src_addr)
{
    reg_tahdt_dma_src_addr(ch) = (unsigned int)convert_ram_addr_cpu2bus(src_addr);
}

static inline void tahdt_dma_set_dst_addr(tahdt_dma_ch_e ch, unsigned char *dst_addr)
{
    reg_tahdt_dma_dst_addr(ch) = (unsigned int)convert_ram_addr_cpu2bus(dst_addr);
}

typedef enum {
    TAHDT_DMA_TX_CHN0 = 0,
    TAHDT_DMA_TX_CHN1,
    TAHDT_DMA_TX_CHN2,
    TAHDT_DMA_TX_CHN3,
    TAHDT_DMA_TX_CHN4,
    TAHDT_DMA_TX_CHN5,
} tahdt_dma_tx_ch_e;

static inline void tahdt_dma_set_tx_wptr_with_ch(tahdt_dma_tx_ch_e ch, unsigned char flag)
{
    reg_tahdt_dma_tx_wptr(ch) = flag;
}

static inline unsigned char tahdt_dma_get_tx_wptr_with_ch(tahdt_dma_tx_ch_e ch)
{
    return reg_tahdt_dma_tx_wptr(ch);
}

static inline void tahdt_dma_set_tx_rptr_with_ch(tahdt_dma_tx_ch_e ch, unsigned char flag)
{
    reg_tahdt_dma_tx_rptr(ch) = flag;
}

static inline unsigned char tahdt_dma_get_tx_rptr_with_ch(tahdt_dma_tx_ch_e ch)
{
    return reg_tahdt_dma_tx_rptr(ch);
}

static inline void tahdt_dma_reset_tx_ptr_with_ch(tahdt_dma_tx_ch_e ch)
{
    reg_tahdt_dma_tx_wptr(ch) = 0;
    reg_tahdt_dma_tx_rptr(ch) = reg_tahdt_dma_tx_rptr(ch) | FLD_TAHDT_DMA_RPTR_CLR;
}

static inline void tahdt_dma_set_tx_wptr(unsigned char flag)
{
    reg_tahdt_dma_tx_wptr(TAHDT_DMA_TX_CHN0) = flag;
}

static inline unsigned char tahdt_dma_get_tx_wptr(void)
{
    return reg_tahdt_dma_tx_wptr(TAHDT_DMA_TX_CHN0);
}

static inline void tahdt_dma_set_tx_rptr(unsigned char flag)
{
    reg_tahdt_dma_tx_rptr(TAHDT_DMA_TX_CHN0) = flag;
}

static inline unsigned char tahdt_dma_get_tx_rptr(void)
{
    return reg_tahdt_dma_tx_rptr(TAHDT_DMA_TX_CHN0);
}

static inline void tahdt_dma_reset_tx_ptr(void)
{
    reg_tahdt_dma_tx_wptr(TAHDT_DMA_TX_CHN0) = 0;
    reg_tahdt_dma_tx_rptr(TAHDT_DMA_TX_CHN0) = reg_tahdt_dma_tx_rptr(TAHDT_DMA_TX_CHN0) | FLD_TAHDT_DMA_RPTR_CLR;
}

typedef enum{
    TAHDT_LL_CMD_STOP    = 0x80, //RW
    TAHDT_LL_CMD_GTX     = 0x81, //RW
    TAHDT_LL_CMD_GRX     = 0x82, //RW
    TAHDT_LL_CMD_STX     = 0x83, //RW
    TAHDT_LL_CMD_SRX     = 0x84, //RW
    TAHDT_LL_CMD_STX2RX  = 0x85, //RW
    TAHDT_LL_CMD_SRX2TX  = 0x86, //RW
    TAHDT_LL_CMD_TRIGGER = 0x80, //W1C
} tahdt_ll_cmd_e;

static inline void tahdt_set_cmd(tahdt_ll_cmd_e cmd)
{
    reg_tahdt_ll_cmd = cmd;
}

void rf_tahdt_cfg_rx_dma(void);
void rf_tahdt_cfg_tx_dma(void);

void rf_tahdt_set_rx_dma(unsigned char *pRxBuff, unsigned short rxSize);
void rf_tahdt_set_tx_dma(unsigned char *pTxBuff, unsigned short tx_size, unsigned char tx_depth);
void rf_tahdt_set_tx_dma_without_buff(unsigned short tx_size, unsigned char tx_depth);
void rf_tahdt_set_tx_dma_buff(unsigned char *pTxBuff);

void rf_tahdt_start_fsm(tahdt_ll_cmd_e mode, void *pTxAddr, unsigned int tick);
void rf_tahdt_close_fsm(void);
void rf_tahdt_waitIdle(void);

void tahdt_dbgport_init(void);
void rf_tahdt_init(void);
#endif /*HAL_DRV_TAHDT_H_*/

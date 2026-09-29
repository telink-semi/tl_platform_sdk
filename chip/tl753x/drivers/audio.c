/********************************************************************************************************
 * @file    audio.c
 *
 * @brief   This is the source file for tl753x
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
#include "audio.h"

/**
 * @brief Audio rx fifo channel.
 * 
 */
static unsigned char audio_rx_fifo_chn;

/**
 * @brief Audio rx dma channel.
 * 
 */
static unsigned char audio_rx_dma_chn;

/**
 * @brief Audio tx fifo channel.
 * 
 */
static unsigned char audio_tx_fifo_chn;

/**
 * @brief Audio tx dma channel.
 * 
 */
static unsigned char audio_tx_dma_chn;

/**
 * @brief Audio tx dma list config table.
 * 
 */
static dma_chain_config_t g_audio_tx_dma_list_cfg[4];

/**
 * @brief Audio rx dma list config table.
 * 
 */
static dma_chain_config_t g_audio_rx_dma_list_cfg[4];

/**
 * @brief       This function servers to powen down bbpll to audio clock lock.
 * @return      none.
 */
extern _attribute_ram_code_sec_optimize_o2_noinline_ void pm_audio_pll_power_down(void);

/**
 * @brief Audio i2s data/lr_clk invert config table.
 * 
 */
static i2s_invert_config_t audio_i2s_invert_config[3] = {
    {

     .i2s_lr_clk_invert_select = I2S_LR_CLK_INVERT_DIS,
     .i2s_data_invert_select   = I2S_DATA_INVERT_DIS,
///to debug DSP B
//       .i2s_lr_clk_invert_select = I2S_LR_CLK_INVERT_EN,
//     .i2s_data_invert_select   = I2S_DATA_INVERT_EN,
     },
    {
     .i2s_lr_clk_invert_select = I2S_LR_CLK_INVERT_DIS,
     .i2s_data_invert_select   = I2S_DATA_INVERT_DIS,
     },
    {
     .i2s_lr_clk_invert_select = I2S_LR_CLK_INVERT_DIS,
     .i2s_data_invert_select   = I2S_DATA_INVERT_DIS,
     },
};

/**
 * @brief Audio rx dma config table.
 * 
 */
dma_config_t audio_dma_rx_config[4] = {
    {
     .dst_req_sel    = 0,
     .src_req_sel    = DMA_REQ_AUDIO0_RX,
     .dst_addr_ctrl  = DMA_ADDR_INCREMENT,
     .src_addr_ctrl  = DMA_ADDR_FIX,
     .dstmode        = DMA_NORMAL_MODE,
     .srcmode        = DMA_HANDSHAKE_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = 0,
     .src_req_sel    = DMA_REQ_AUDIO1_RX,
     .dst_addr_ctrl  = DMA_ADDR_INCREMENT,
     .src_addr_ctrl  = DMA_ADDR_FIX,
     .dstmode        = DMA_NORMAL_MODE,
     .srcmode        = DMA_HANDSHAKE_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = 0,
     .src_req_sel    = DMA_REQ_AUDIO2_RX,
     .dst_addr_ctrl  = DMA_ADDR_INCREMENT,
     .src_addr_ctrl  = DMA_ADDR_FIX,
     .dstmode        = DMA_NORMAL_MODE,
     .srcmode        = DMA_HANDSHAKE_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = 0,
     .src_req_sel    = DMA_REQ_AUDIO3_RX,
     .dst_addr_ctrl  = DMA_ADDR_INCREMENT,
     .src_addr_ctrl  = DMA_ADDR_FIX,
     .dstmode        = DMA_NORMAL_MODE,
     .srcmode        = DMA_HANDSHAKE_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
};

/**
 * @brief Audio tx dma config table.
 * 
 */
dma_config_t audio_dma_tx_config[4] = {
    {
     .dst_req_sel    = DMA_REQ_AUDIO0_TX,
     .src_req_sel    = 0,
     .dst_addr_ctrl  = DMA_ADDR_FIX,
     .src_addr_ctrl  = DMA_ADDR_INCREMENT,
     .dstmode        = DMA_HANDSHAKE_MODE,
     .srcmode        = DMA_NORMAL_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = DMA_REQ_AUDIO1_TX,
     .src_req_sel    = 0,
     .dst_addr_ctrl  = DMA_ADDR_FIX,
     .src_addr_ctrl  = DMA_ADDR_INCREMENT,
     .dstmode        = DMA_HANDSHAKE_MODE,
     .srcmode        = DMA_NORMAL_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = DMA_REQ_AUDIO2_TX,
     .src_req_sel    = 0,
     .dst_addr_ctrl  = DMA_ADDR_FIX,
     .src_addr_ctrl  = DMA_ADDR_INCREMENT,
     .dstmode        = DMA_HANDSHAKE_MODE,
     .srcmode        = DMA_NORMAL_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
    {
     .dst_req_sel    = DMA_REQ_AUDIO3_TX,
     .src_req_sel    = 0,
     .dst_addr_ctrl  = DMA_ADDR_FIX,
     .src_addr_ctrl  = DMA_ADDR_INCREMENT,
     .dstmode        = DMA_HANDSHAKE_MODE,
     .srcmode        = DMA_NORMAL_MODE,
     .dstwidth       = DMA_CTR_WORD_WIDTH,
     .srcwidth       = DMA_CTR_WORD_WIDTH,
     .src_burst_size = DMA_BURST_1_WORD,
     .read_num_en    = 0,
     .priority       = 0,
     .write_num_en   = 0,
     .auto_en        = 0,
     },
};

/**********************************************************************************************************************
 *                                                Audio power/clock interface                                               *
 *********************************************************************************************************************/

/**
 * @brief      This function serves to enable or disable codec ldo_ana and ldo_cdc voltage by manual.
 * @param[in]  en  - 0:enable; 1:disable.
 * @return     none
 * @note
 */
void audio_codec_ldo_ana_cdc_enable(unsigned char en)
{
    analog_write_reg8(areg_aon_0x7b, analog_read_reg8(areg_aon_0x7b) & ~(FLD_AUTO_PD_LDO_CDC | FLD_AUTO_PD_LDO_ANA));
    if (en)
    {
        analog_write_reg8(areg_aon_0x7c, analog_read_reg8(areg_aon_0x7c) & ~(FLD_AUTO_PD_LDO_CDC | FLD_AUTO_PD_LDO_ANA));
    }
    else
    {
        analog_write_reg8(areg_aon_0x7c, analog_read_reg8(areg_aon_0x7c) | (FLD_AUTO_PD_LDO_CDC | FLD_AUTO_PD_LDO_ANA));
    }
}

/**
 * @brief       This function temporarily turns off AVDD2 or BK1 with a 50us interval and reopen.
 * @param[in]   none.
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void pm_close_avdd2_50us_restore(void)
{
    unsigned char flag = 0;

    if(g_areg_aon_07&0x2) { //bk1 cntr enable
        //just need close one bit here to disable dcdc bk1, the delay between configure two bit is also not needed here, confirmed by ze.wang, add by nanshun.ouyang 20260724
        g_areg_aon_07 &= ~0x2;
        analog_write_reg8(0x07, g_areg_aon_07);
        flag = 1;
    } else if((g_areg_aon_08&0x2) == 0) { //avdd2 enable
        g_areg_aon_08 |= 0x2;
        analog_write_reg8(0x08, g_areg_aon_08);
        flag = 2;
    } else { //error
        while(1) {};
    }

    core_cclk_delay_tick((unsigned long long)((int)sys_clk.cclk_d25f_dsp * 50000)); //50ms

    if(flag == 1) { //restore bk1
        g_areg_aon_07 |= 0x2;
        analog_write_reg8(0x07, g_areg_aon_07);
        core_cclk_delay_tick((unsigned long long)((int)sys_clk.cclk_d25f_dsp * 500));
    } else if (flag == 2) { //restore avdd2
        g_areg_aon_08 &= ~0x2;
        analog_write_reg8(0x08, g_areg_aon_08);
    }
}

/**
 * @brief       This function used to close and reopen LDO:AVDD2 or DCDC:BK1 and configure FLD_CODEC_BGR_ENP and FLD_CODEC_PGOOD_CDC.
 * @param[in]   none.
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void audio_codec_pre_init(void)
{
    clock_pll_audio_init(PLL1_AUDIO_CLK_172P032M);
    pm_set_dig_module_power_switch(FLD_PD_AUDIO_EN, PM_POWER_DOWN);

    audio_init(PLL1_AUDIO_CLK_172P032M);
    audio_codec_adc_clk_en(AUDIO_LINEIN_ADC0);
    reg_audio_codec_dac_cfg4 = (reg_audio_codec_dac_cfg4 & ~(FLD_CODEC_PGOOD_CDC)) | MASK_VAL(FLD_CODEC_PGOOD_CDC, 7);
    reg_audio_codec_dac_cfg3 |= FLD_CODEC_BGR_ENP;
    //BGR should be enabled before 2.0V Power(LDO:AVDD2 or DCDC:BK1), so close and reopen 2.0V here.
    //add by jiawei.shi 20260724
    pm_close_avdd2_50us_restore();

    BM_CLR(reg_clk_en2, FLD_CLK2_AUDIO_EN);
    BM_CLR(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
    pm_audio_pll_power_down();

}

/*!
 * @name Audio clock interface.
 * @{
 */

/**
 * @brief      This function serves to initialize audio.
 * @param[in]  audio_pll - audio pll clock select.
 * @return     none
 * @note       - When using the audio module, this interface must be configured first, otherwise the following interfaces will not take effect.
 *             - When the sampling rate is 44.1KHz, audio_pll needs to be set to PLL1_AUDIO_CLK_158P0544M.
 */
extern volatile unsigned char g_audio_clk_index;
_attribute_ram_code_sec_noinline_ void audio_init(pll_audio_clk_e  clk)
{
    unsigned char aclk_div = 0;

    #if (PM_7D_POWER_DEBUG == 0)
    //pm_set_dig_module_power_switch(FLD_PD_AUDIO_EN, PM_POWER_DOWN);
    #endif
    //BM_CLR(reg_rst2, FLD_RST2_AUDIO);
    //BM_CLR(reg_clk_en2, FLD_CLK2_AUDIO_EN);
    //BM_CLR(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
    //audio_delay_ms(5);
    #if (PM_7D_POWER_DEBUG == 0)
      //audio_codec_ldo_ana_cdc_enable(0);

        pm_set_dig_module_power_switch(FLD_PD_AUDIO_EN, PM_POWER_UP);

    #endif
    BM_SET(reg_rst2, FLD_RST2_AUDIO);
    BM_SET(reg_clk_en2, FLD_CLK2_AUDIO_EN);

    switch (clk) {
    case PLL1_AUDIO_CLK_172P032M:   /*audio clck = 172.032Hz/4 = 43.008MHz*/
        aclk_div = 4;
        break;
    case PLL1_AUDIO_CLK_158P0544M:  /*audio clck = 158.0544Hz/4 = 39.5136MHz*/
        aclk_div = 4;
        break;
    case PLL1_AUDIO_CLK_86P016M:    /*audio clck = 86.016Hz/2 = 43.008MHz*/
        aclk_div = 2;
        break;
    case PLL1_AUDIO_CLK_43P008M:    /*audio clck = 43.008Hz/1 = 43.008MHz*/
        aclk_div = 1;
        break;
    case PLL0_AUDIO_CLK_96M:       /*audio clck = 96MHz/2 = 48MHz*/
        aclk_div = 2;
        break;
    case PLL0_AUDIO_CLK_192M:       /*audio clck = 192MHz/4 = 48MHz*/
        aclk_div = 4;
        break;
    case PLL0_AUDIO_CLK_240M:       /*audio clck = 240MHz/5 = 48MHz*/
        aclk_div = 5;
        break;
    case PLL0_AUDIO_CLK_288M:       /*audio clck = 288MHz/6 = 48MHz*/
        aclk_div = 6;
        break;
    default:
        aclk_div = 1;
        break;
    }
    g_audio_clk_index = clk;
    if(PLL1_AUDIO_CLK_MAX > clk) /* clk source : PLL1 */
    {
        reg_audio_pll_set &= 0x00;
    }
    else                         /* clk source : PLL0 */
    {
        reg_audio_pll_set |= 0xff;
    }

    reg_audio_clk_aclk_set = (reg_audio_clk_aclk_set & (~FLD_CLK_ACLK_SET)) | (aclk_div & FLD_CLK_ACLK_SET);
    BM_SET(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
}

/**
 * @}
 */
/**********************************************************************************************************************
 *                                                Audio anc interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio anc interface
 * @{
 */

/**
 * @brief      This function serves to set dac control resample fs.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  in_fs   - resample input fs.
 * @param[in]  out_fs  - resample output fs.
 * @note
 *             - when resample fs rely on dac, this function must be called
 */
void audio_anc_set_dac_cnt_mode(audio_anc_chn_e anc_chn, audio_anc_resample_in_fs_e in_fs, audio_anc_resample_out_fs_e out_fs)
{
    char reg_data = 0;
    /* 0: 48k->768k; 1: 96k->768k or 48k->384k; 2: 96k->384k or 48k->192k, 3: 96k -> 192k */
    if ((ANC_RESAMPLE_IN_FS_48K == in_fs) && (ANC_RESAMPLE_OUT_FS_768K == out_fs))
    {
        reg_data = 0;
    }
    else if (((ANC_RESAMPLE_IN_FS_48K == in_fs) && (ANC_RESAMPLE_OUT_FS_384K == out_fs)) || ((ANC_RESAMPLE_IN_FS_96K == in_fs) && (ANC_RESAMPLE_OUT_FS_768K == out_fs)))
    {
        reg_data = 1;
    }
    else if (((ANC_RESAMPLE_IN_FS_48K == in_fs) && (ANC_RESAMPLE_OUT_FS_192K == out_fs)) || ((ANC_RESAMPLE_IN_FS_96K == in_fs) && (ANC_RESAMPLE_OUT_FS_384K == out_fs)))
    {
        reg_data = 2;
    }
    else //96k -> 192k
    {
        reg_data = 3;
    }

    reg_audio_anc_config2(anc_chn) = (reg_audio_anc_config2(anc_chn) & (~FLD_ANC_DAC_CNT_MODE)) |
                                     MASK_VAL(FLD_ANC_DAC_CNT_MODE, reg_data); /* set dac cnt mode to control audio pcm rate. */
}

/**
 * @brief      This function serves to set the resample frequency of anc.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  fs_decision - who decides the resample frequency of anc.
 * @param[in]  in_fs       - resample input fs.
 * @param[in]  out_fs      - resample output fs.
 */
void audio_anc_set_resample_in_out_fs(audio_anc_chn_e anc_chn, audio_anc_resample_fs_decision_e fs_decision, audio_anc_resample_in_fs_e in_fs, audio_anc_resample_out_fs_e out_fs)
{
    if (fs_decision == ANC_RESAMPLE_DAC_DECISION_FS) {
        BM_SET(reg_audio_anc_config(anc_chn), FLD_ANC_SRC_EN);
        BM_SET(reg_audio_anc_config(anc_chn), FLD_ANC_SRC_RATE_SEL);
        audio_anc_set_dac_cnt_mode(anc_chn, in_fs, out_fs);
    } else {
        BM_CLR(reg_audio_anc_config(anc_chn), FLD_ANC_SRC_RATE_SEL);
    }
    if ((in_fs == ANC_RESAMPLE_IN_FS_48K) && (out_fs == ANC_RESAMPLE_OUT_FS_768K))
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_48K_IN_768K_OUT);
    }
    else if ((in_fs == ANC_RESAMPLE_IN_FS_48K) && (out_fs == ANC_RESAMPLE_OUT_FS_384K))
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_48K_IN_384K_OUT);
    }
    else if ((in_fs == ANC_RESAMPLE_IN_FS_48K) && (out_fs == ANC_RESAMPLE_OUT_FS_192K))
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_48K_IN_192K_OUT);
    }
    else if ((in_fs == ANC_RESAMPLE_IN_FS_96K) && (out_fs == ANC_RESAMPLE_OUT_FS_768K))
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_96K_IN_768K_OUT);
    }
    else if ((in_fs == ANC_RESAMPLE_IN_FS_96K) && (out_fs == ANC_RESAMPLE_OUT_FS_384K))
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_96K_IN_384K_OUT);
    }
    else
    {
        reg_audio_anc_only_ref0(anc_chn) = MASK_VAL(FLD_ANC_RESAMPLE_MODE_SEL, ANC_RESAMPLE_96K_IN_192K_OUT);
    }
}

/**
 * @brief      This function servers to update anc wz or cz biquad iir filter coefficients.
 * 
 * @param[in]  anc_chn - anc channel.
 * @param[in]  wcz_chn - wcz_chn channel.
 * @param[in]  data    - wcz biquad iir filter data.
 * @return     none
 */
void audio_anc_update_wcz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed int data[12][5])
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_start(anc_chn) = BIT(wcz_chn);

    for (unsigned char i = 0; i < 12; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wcz_iir_b0(anc_chn, wcz_chn, i) = data[i][0];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wcz_iir_b1(anc_chn, wcz_chn, i) = data[i][1];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wcz_iir_b2(anc_chn, wcz_chn, i) = data[i][2];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wcz_iir_a1(anc_chn, wcz_chn, i) = data[i][3];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wcz_iir_a2(anc_chn, wcz_chn, i) = data[i][4];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_done(anc_chn) = BIT(wcz_chn);
}

/**
 * @brief      This function servers to set anc wz or cz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  wcz_chn  - wcz_chn channel.
 * @param[in]  data     - wcz fir filter data address.
 * @note
 *             - bypass coefficients: wz[0] = 0x4000, the rest of the parameters are all set to 0
 * @return     none
 */
void audio_anc_update_wcz_fir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed short *data)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_start(anc_chn) = BIT(wcz_chn);
    for (unsigned char i = 0; i < 16; i++)
    {
        for(unsigned char j = 0; j < 4; j++)
        {
            while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
            REG_ADDR32(REG_AUDIO_ANC_COEF(anc_chn) + 0xa80 + (wcz_chn) * 0x200 + i * 0x20 + j * 4) = ((data[i + j * 32 + 16] << 16) & 0xFFFF0000) | (data[i + j * 32] & 0xFFFF);
        }
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_done(anc_chn) = BIT(wcz_chn);
}

/**
 * @brief      This function servers to update anc cz3 biquad iir filter coefficients.
 * 
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - cz3 biquad iir filter data.
 * @return     none
 */
void audio_anc_update_cz3_iir_coef(audio_anc_chn_e anc_chn, signed int data[12][5])
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_start(anc_chn) = FLD_ANC_CZ3_IIR_START;
    for (unsigned char i = 0; i < 12; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_iir_b0(anc_chn, i) = data[i][0];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_iir_b1(anc_chn, i) = data[i][1];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_iir_b2(anc_chn, i) = data[i][2];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_iir_a1(anc_chn, i) = data[i][3];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_iir_a2(anc_chn, i) = data[i][4];
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_done(anc_chn) = FLD_ANC_CZ3_IIR_DONE;
}

/**
 * @brief      This function servers to update anc cz3 fir filter coefficients.
 * 
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  data     - cz fir filter data.
 * @return     none
 */
void audio_anc_update_cz3_fir_coef(audio_anc_chn_e anc_chn, signed short *data)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_start(anc_chn) = FLD_ANC_CZ3_FIR_START;
    for (unsigned char i = 0; i < 16; i++)
    {
        for(unsigned char j = 0; j < 4; j++)
        {
            while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
            REG_ADDR32(REG_AUDIO_ANC_COEF(anc_chn) + 0x1280 + i * 0x20 + j * 4) = ((data[i + j * 32 + 16] << 16) & 0xFFFF0000) | (data[i + j * 32] & 0xFFFF);
        }
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_done(anc_chn) = FLD_ANC_CZ3_FIR_DONE;
}

/**
 * @brief      This function servers to update anc rz biquad iir filter coefficients.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  rz_chn  - rz channel.
 * @param[in]  data    - rz fir filter data.
 * @return     none
 */
void audio_anc_update_rz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn, signed int data[12][5])
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_start(anc_chn) = BIT(5 + rz_chn);
    for (unsigned char i = 0; i < 12; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_rz_iir_b0(anc_chn, rz_chn, i) = data[i][0];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_rz_iir_b1(anc_chn, rz_chn, i) = data[i][1];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_rz_iir_b2(anc_chn, rz_chn, i) = data[i][2];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_rz_iir_a1(anc_chn, rz_chn, i) = data[i][3];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_rz_iir_a2(anc_chn, rz_chn, i) = data[i][4];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_iir_done(anc_chn) = BIT(5 + rz_chn);
}

/**
 * @brief      This function servers to update anc rz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  rz_chn   - rz channel.
 * @param[in]  data     - rz fir filter data.
 * @return     none
 */
void audio_anc_update_rz_fir_coef(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn, signed short *data)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_start(anc_chn) = BIT(5 + rz_chn);
    for (unsigned char i = 0; i < 16; i++)
    {
        for(unsigned char j = 0; j < 4; j++)
        {
            while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
            REG_ADDR32(REG_AUDIO_ANC_COEF(anc_chn) + 0x1480 + 0x200 * rz_chn + i * 0x20 + j * 4) = ((data[i + j * 32 + 16] << 16) & 0xFFFF0000) | (data[i + j * 32] & 0xFFFF);
        }
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_done(anc_chn) = BIT(5 + rz_chn);
}

/**
 * @brief      This function servers to update anc bz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  bz_chn   - bz channel.
 * @param[in]  data     - bz fir filter data.
 * @return     none
 */
void audio_anc_update_bz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_bz_chn_e bz_chn, signed int data[6][5])
{
    (void)anc_chn;
    for (unsigned char i = 0; i < 6; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_bz_iir_b0(bz_chn, i) = data[i][0];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_bz_iir_b1(bz_chn, i) = data[i][1];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_bz_iir_b2(bz_chn, i) = data[i][2];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_bz_iir_a1(bz_chn, i) = data[i][3];
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_bz_iir_a2(bz_chn, i) = data[i][4];
    }
}

/**
 * @brief      This function servers to update anc hb1 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb1 coefficient length is 21 word, bit[0-25] valid.
 */
void audio_anc_update_hb1_coef(audio_anc_chn_e anc_chn, signed int *data)
{
    for (unsigned char i = 0; i < 21; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_hb1_coef(anc_chn, i) = data[i] & FLD_ANC_HB1_COEF;
    }
}

/**
 * @brief      This function servers to update anc hb2 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb2 coefficient length is 8 word, bit[0-25] valid.
 */
void audio_anc_update_hb2_coef(audio_anc_chn_e anc_chn, signed int *data)
{
    for (unsigned char i = 0; i < 7; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_hb2_coef(anc_chn, i) = data[i] & FLD_ANC_HB2_COEF;
    }
}

/**
 * @brief      This function servers to update anc hb3 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb3 coefficient length is 8 word, bit[0-25] valid.
 */
void audio_anc_update_hb3_coef(audio_anc_chn_e anc_chn, signed int *data)
{
    for (unsigned char i = 0; i < 7; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_hb3_coef(anc_chn, i) = data[i] & FLD_ANC_HB3_COEF;
    }
}

/**
 * @brief      This function servers to update anc droop coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc droop coefficient length is 6 word, bit[0-13] valid.
 */
void audio_anc_update_droop_coef(audio_anc_chn_e anc_chn, signed short *data)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_droop_coef(anc_chn, i) = data[i] & FLD_ANC_DROOP_COEF;
    }
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio asrc interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio asrc interface
 * @{
 */

/**
 * @brief      This function serves to update asrc droop coefficients.
 * 
 * @param[in]  asrc_chn  - asrc channel select.
 * @param[in]  d_coef    - asrc droop coefficients data address.
 * @param[in]  data_len  - asrc droop coefficients data length.
 * @return     none
 * @note
 *             - droop coef max length is 9.
 */
void audio_asrc_update_droop_coef(audio_hac_asrc_chn_e asrc_chn, signed short *d_coef, unsigned char data_len)
{
    for (unsigned char i = 0; i < data_len; i++) {
        reg_audio_asrc_drop_coef(asrc_chn, i) = d_coef[i] & FLD_ASRC_DROP_COEF;
    }
}

/**
 * @brief      This function serves to update asrc half_band1 coefficients.
 * 
 * @param[in]  asrc_chn - asrc channel.
 * @param[in]  hb1_coef - asrc half_band1 coefficients data address.
 * @return     none
 * @note
 *             - asrc half_band1 coefficient length is 32 word, bit[0-25] valid.
 */
void audio_asrc_update_hb1_coef(audio_hac_asrc_chn_e asrc_chn, signed int *hb1_coef)
{
    for (unsigned char i = 0; i < 32; i++) {
        reg_audio_asrc_hb1_coef(asrc_chn, i) = hb1_coef[i] & FLD_ASRC_HB1_COEF;
    }
}

/**
 * @brief      This function serves to update asrc half_band2 coefficients.
 * 
 * @param[in]  asrc_chn - asrc channel.
 * @param[in]  hb2_coef - asrc half_band2 coefficients data address. 
 * @return     none
 * @note
 *             - asrc half_band2 coefficient length is 7 word, bit[0-25] valid.
 */
void audio_asrc_update_hb2_coef(audio_hac_asrc_chn_e asrc_chn, signed int *hb2_coef)
{
    for (unsigned char i = 0; i < 7; i++) {
        reg_audio_asrc_hb2_coef(asrc_chn, i) = hb2_coef[i] & FLD_ASRC_HB1_COEF;
    }
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio codec interface                                               *
 *********************************************************************************************************************/
/**
 * @brief     Weak delay interface for audio module in millisecond
 * @param[in] millisec - delay duration in millisecond
 * @return    none
 */
__attribute__((weak)) void audio_delay_ms(unsigned int millisec)
{
    delay_ms(millisec);
}

/*!
 * @name Audio codec interface
 * @{
 */

/**
 * @brief      This function serves to enable codec adc analog part.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_ana_en(audio_codec_input_select_e input)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned int val       = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        val |= (FLD_CODEC_ADC0_ANA_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        val |= (FLD_CODEC_ADC1_ANA_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        val |= (FLD_CODEC_ADC2_ANA_ENABLE);
    }
    reg_audio_codec_cfg_0 |= (val);
}

/**
 * @brief      This function serves to disable codec adc analog part.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_ana_dis(audio_codec_input_select_e input)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned int val       = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        val |= (FLD_CODEC_ADC0_ANA_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        val |= (FLD_CODEC_ADC1_ANA_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        val |= (FLD_CODEC_ADC2_ANA_ENABLE);
    }
    reg_audio_codec_cfg_0 &= ~(val);
}

/**
 * @brief      This function serves to enable codec adc reset.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_rst_en(audio_codec_input_select_e input)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned int val       = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        val |= (FLD_CODEC_ADC0_RSTN);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        val |= (FLD_CODEC_ADC1_RSTN);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        val |= (FLD_CODEC_ADC2_RSTN);
    }
    reg_audio_codec_cfg_0 |= (val);
}

/**
 * @brief      This function serves to disable codec adc reset.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_rst_dis(audio_codec_input_select_e input)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned int val       = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        val |= (FLD_CODEC_ADC0_RSTN);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        val |= (FLD_CODEC_ADC1_RSTN);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        val |= (FLD_CODEC_ADC2_RSTN);
    }
    reg_audio_codec_cfg_0 &= ~(val);
}

/**
 * @brief      This function serves to enable codec adc.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_en(audio_codec_input_select_e input)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned int val       = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        val |= (FLD_CODEC_ADC0_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        val |= (FLD_CODEC_ADC1_ENABLE);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        val |= (FLD_CODEC_ADC2_ENABLE);
    }
    reg_audio_codec_cfg_0 |= (val);
}

/**
 * @brief      This function serves to disable codec adc.
 * @param[in]  input - adc channel.
 * @return     none
 */
void audio_codec_adc_dis(audio_codec_input_select_e input)
{
   unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
   unsigned int val       = 0;

   if (channel & AUDIO_LINEIN_ADC0)
   {
       val |= (FLD_CODEC_ADC0_ENABLE);
   }

   if (channel & AUDIO_LINEIN_ADC1)
   {
       val |= (FLD_CODEC_ADC1_ENABLE);
   }

   if (channel & AUDIO_LINEIN_ADC2)
   {
       val |= (FLD_CODEC_ADC2_ENABLE);
   }

   reg_audio_codec_adc_dac_en &= ~(val);
}

/**
 * @brief      This function serves to enable codec dac reset.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_rst_en(audio_codec_output_select_e output)
{
    unsigned int val       = 0;
    if (output & AUDIO_DAC_A0)
    {
        val |= (FLD_CODEC_DAC0_RSTN);
    }

    if (output & AUDIO_DAC_A1)
    {
        val |= (FLD_CODEC_DAC1_RSTN);
    }
    reg_audio_codec_cfg_5 |= (val);
}

/**
 * @brief      This function serves to disable codec dac reset.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_rst_dis(audio_codec_output_select_e output)
{
    unsigned int val       = 0;
    if (output & AUDIO_DAC_A0)
    {
        val |= (FLD_CODEC_DAC0_RSTN);
    }

    if (output & AUDIO_DAC_A1)
    {
        val |= (FLD_CODEC_DAC1_RSTN);
    }
    reg_audio_codec_cfg_5 &= ~(val);
}

/**
 * @brief      This function serves to enable codec dac.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_en(audio_codec_output_select_e output)
{
    unsigned int val       = 0;
    if (output & AUDIO_DAC_A0)
    {
        val |= (FLD_CODEC_DAC0_ENABLE);
    }

    if (output & AUDIO_DAC_A1)
    {
        val |= (FLD_CODEC_DAC1_ENABLE);
    }
    reg_audio_codec_cfg_5 |= val;
}

/**
 * @brief      This function serves to disable codec dac.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_dis(audio_codec_output_select_e output)
{
    unsigned int val       = 0;
    if (output & AUDIO_DAC_A0)
    {
        val |= (FLD_CODEC_DAC0_ENABLE);
    }

    if (output & AUDIO_DAC_A1)
    {
        val |= (FLD_CODEC_DAC1_ENABLE);
    }
    reg_audio_codec_cfg_5 &= ~(val);
}

/**
 * @brief      This function serves to enable codec adc clock.
 * @param[in]  input  - input channel.
 * @return     none
 */
void audio_codec_adc_clk_en(audio_codec_input_select_e input)
{
    unsigned char channel = input & BIT_RNG(0, 2);
    unsigned char en      = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        en |= FLD_CODEC_ADC0_EN;
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        en |= FLD_CODEC_ADC1_EN;
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        en |= FLD_CODEC_ADC2_EN;
    }

    reg_audio_codec_adc_dac_en |= (en);
}

/**
 * @brief      This function serves to disable codec adc clock.
 * @param[in]  input  - input channel.
 * @return     none
 */
void audio_codec_adc_clk_dis(audio_codec_input_select_e input)
{
    unsigned char channel = input & BIT_RNG(0, 2);
    unsigned char en      = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        en |= FLD_CODEC_ADC0_EN;
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        en |= FLD_CODEC_ADC1_EN;
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        en |= FLD_CODEC_ADC2_EN;
    }

    reg_audio_codec_adc_dac_en &= ~(en);
}

/**
 * @brief      This function serves to enable codec dac clock.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_dac_clk_en(audio_codec_output_select_e output)
{
    unsigned char en      = 0;

    if (output & AUDIO_DAC_A0)
    {
        en |= FLD_CODEC_DAC0_EN;
    }

    if (output & AUDIO_DAC_A1)
    {
        en |= FLD_CODEC_DAC1_EN;
    }

    reg_audio_codec_adc_dac_en |= (en);
}

/**
 * @brief      This function serves to disable codec dac clock.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_dac_clk_dis(audio_codec_output_select_e output)
{
    unsigned char en      = 0;

    if (output & AUDIO_DAC_A0)
    {
        en |= FLD_CODEC_DAC0_EN;
    }

    if (output & AUDIO_DAC_A1)
    {
        en |= FLD_CODEC_DAC1_EN;
    }

    reg_audio_codec_adc_dac_en &= ~(en);
}

/**
 * @brief      This function serves to enable codec adc and dac clock.
 * @param[in]  input  - input channel.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_adc_dac_clk_en(audio_codec_input_select_e input, audio_codec_output_select_e output)
{
    unsigned char channel = input & BIT_RNG(0, 2);
    unsigned char en      = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        en |= FLD_CODEC_ADC0_EN;
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        en |= FLD_CODEC_ADC1_EN;
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        en |= FLD_CODEC_ADC2_EN;
    }

    if (output & AUDIO_DAC_A0)
    {
        en |= FLD_CODEC_DAC0_EN;
    }

    if (output & AUDIO_DAC_A1)
    {
        en |= FLD_CODEC_DAC1_EN;
    }

    reg_audio_codec_adc_dac_en |= (en);
}

/**
 * @brief      This function serves to disable codec adc and dac clock.
 * @param[in]  input  - input channel.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_adc_dac_clk_dis(audio_codec_input_select_e input, audio_codec_output_select_e output)
{
    unsigned char channel = input & BIT_RNG(0, 2);
    unsigned char en      = 0;

    if (channel & AUDIO_LINEIN_ADC0)
    {
        en |= FLD_CODEC_ADC0_EN;
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        en |= FLD_CODEC_ADC1_EN;
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        en |= FLD_CODEC_ADC2_EN;
    }

    if (output & AUDIO_DAC_A0)
    {
        en |= FLD_CODEC_DAC0_EN;
    }

    if (output & AUDIO_DAC_A1)
    {
        en |= FLD_CODEC_DAC1_EN;
    }

    reg_audio_codec_adc_dac_en &= ~(en);
}

/**
 * @brief      This function serves to power down codec adc.
 * @param[in]  input - adc channel.
 * @return     none
 */
void audio_codec_adc_power_down(audio_codec_input_select_e input)
{
    audio_codec_adc_ana_dis(input);
    audio_codec_adc_rst_dis(input);
    audio_codec_adc_dis(input);
    audio_codec_adc_clk_dis(input);
    if (input & BIT(3)) //amic
    {
        audio_codec_set_micbias(0);
    }
}

/**
 * @brief      This function serves to enable/disable codec micbias output.
 * @param[in]  enable - 1: enable micbias, 0: disable micbias.
 * @return     none
 * @note
 *             - bias only for amic.
 */
void audio_codec_set_micbias(unsigned char enable)
{
    if (enable)
    {
        reg_audio_codec_dac_cfg3 = (reg_audio_codec_dac_cfg3 & ~(FLD_CODEC_MIC_BIAS_SEL | FLD_CODEC_VREF_MICBIAS_TRIM))
                                    | MASK_VAL(FLD_CODEC_MIC_BIAS_SEL, 4) | MASK_VAL(FLD_CODEC_VREF_MICBIAS_TRIM, 8) | FLD_CODEC_MIC_BIAS_EN;
    }
    else
    {
        reg_audio_codec_dac_cfg3 &= ~FLD_CODEC_MIC_BIAS_EN;
    }
}

/**
 * @brief      This function serves to mute/unmute dac dem output.
 * @param[in]  set - 1: mute, 0: not mute.
 * @return     none
 * @note
 */
void audio_codec_dac_dem_mute_set(unsigned char set)
{
    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_DEM_MUTE)) | MASK_VAL(FLD_CODEC_I_CFG_DEM_MUTE, set);
}

/**
 * @brief      This function serves to enable/disable dac autx output.
 * @param[in]  output - output channel.
 * @param[in]  en     - 1: mute, 0: not mute.
 * @return     none
 * @note
 */
void audio_codec_dac_autx_mute_enable(audio_codec_output_select_e output, unsigned char en)
{
    if (output & AUDIO_DAC_A0) {
        reg_audio_codec_dac_cfg4 = (reg_audio_codec_dac_cfg4 & ~FLD_CODEC_TX_MUTE_L_CORE) | MASK_VAL(FLD_CODEC_TX_MUTE_L_CORE, en);
    }
    if (output & AUDIO_DAC_A1) {
        reg_audio_codec_dac_cfg4 = (reg_audio_codec_dac_cfg4 & ~FLD_CODEC_TX_MUTE_R_CORE) | MASK_VAL(FLD_CODEC_TX_MUTE_R_CORE, en);
    }
}

/**
 * @brief      This function serves to power down codec dac.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_output_power_down(audio_codec_output_select_e output)
{
    audio_codec_dac_dem_mute_set(1);
    audio_codec_dac_autx_mute_enable(output, 1);
    audio_codec_dac_rst_dis(output);
    audio_codec_dac_dis(output);
    audio_codec_dac_clk_dis(output);
}

/**
 * @brief      This function serves to set codec output mute.
 * @param[in]  output - output channel.
 * @param[in]  cmd    - mute type.
 * @return     none
 */
void audio_codec_set_output_mute(audio_codec_output_select_e output, audio_dac_mute_cmd_t cmd)
{
    if (AUDIO_DAC_MUTE_DSM == cmd) {
        /* Dsm out mute will mute all channel*/
        audio_codec_dac_dem_mute_set(1);
    } else {
        /* Analog mute specified channel*/
        audio_codec_dac_autx_mute_enable(output, 1);
    }
}

/**
 * @brief      This function serves to get audio codec clock from audio_codec_clk_config_table.
 * @param[in]  fs - sample_rate.
 * @return     none
 * @note       adc and dac use the same codec clock table
 */
unsigned int audio_codec_clk_get(audio_sample_rate_e fs)
{
    unsigned int index = AUDIO_CLK_TABLE_PLL1_START;

    if(g_audio_clk_index == PLL0_AUDIO_CLK_96M){
        index = AUDIO_CLK_TABLE_PLL0_96_START;
    }
    else if(g_audio_clk_index == PLL0_AUDIO_CLK_192M) {
        index = AUDIO_CLK_TABLE_PLL0_192_START;
    }
    else if(g_audio_clk_index == PLL0_AUDIO_CLK_240M) {
        index = AUDIO_CLK_TABLE_PLL0_240_START;
    }
    else if(g_audio_clk_index == PLL0_AUDIO_CLK_288M) {
        index = AUDIO_CLK_TABLE_PLL0_288_START;
    }

    for (index++ ; index < sizeof(audio_codec_clk_config_table) / sizeof(codec_clk_config_t); index++)
    {
        if (fs == audio_codec_clk_config_table[index].rate)
            return audio_codec_clk_config_table[index].clk;
    }
    return 6144000;
}

/**
 * @brief      This function serves to set audio codec adc clock.
 * @param[in]  clk - codec adc clock.
 * @return     none
 */
void audio_codec_adc_clk_set(unsigned int clk)
{
    unsigned char div = 1;
    switch (g_audio_clk_index) {
    case PLL1_AUDIO_CLK_172P032M:
        div = 172032000 / clk;
        break;
    case PLL1_AUDIO_CLK_169P344M:
        div = 169344000 / clk;
        break;
    case PLL1_AUDIO_CLK_158P0544M:
        div = 158054400 / clk;
        break;
    case PLL1_AUDIO_CLK_86P016M:
        div = 86016000 / clk;
        break;
    case PLL1_AUDIO_CLK_43P008M:
        div = 43008000 / clk;
        break;
    case PLL0_AUDIO_CLK_96M:
        div = 96000000 / clk;
        break;
    case PLL0_AUDIO_CLK_192M:
        div = 192000000 / clk;
        break;
    case PLL0_AUDIO_CLK_240M:
        div = 240000000 / clk;
        break;
    case PLL0_AUDIO_CLK_288M:
        div = 288000000 / clk;
        break;
    default:
        break;
    }
    reg_audio_codec_adc_clk_set = div;
}

/**
 * @brief      This function serves to set audio codec dac clock.
 * @param[in]  clk - codec dac clock.
 * @return     none
 */
void audio_codec_dac_clk_set(unsigned int clk)
{
    unsigned char div = 1;
    switch (g_audio_clk_index) {
    case PLL1_AUDIO_CLK_172P032M:
        div = 172032000 / clk;
        break;
    case PLL1_AUDIO_CLK_169P344M:
        div = 169344000 / clk;
        break;
    case PLL1_AUDIO_CLK_158P0544M:
        div = 158054400 / clk;
        break;
    case PLL1_AUDIO_CLK_86P016M:
        div = 86016000 / clk;
        break;
    case PLL1_AUDIO_CLK_43P008M:
        div = 43008000 / clk;
        break;
    case PLL0_AUDIO_CLK_96M:
        div = 96000000 / clk;
        break;
    case PLL0_AUDIO_CLK_192M:
        div = 192000000 / clk;
        break;
    case PLL0_AUDIO_CLK_240M:
        div = 240000000 / clk;
        break;
    case PLL0_AUDIO_CLK_288M:
        div = 288000000 / clk;
        break;
    default:
        break;
    }
    reg_audio_codec_dac01_clk_set = div;
    reg_audio_codec_dac_clk_set = div * 2;
}

/**
 * @brief      This function serves to set codec input sample rate.
 * @param[in]  input - input channel.
 * @param[in]  fs    - input sample rate.
 * @return     none
 * @note
 */
void audio_codec_set_input_fs(audio_codec_input_select_e input, audio_sample_rate_e fs)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.
    unsigned char pwr_mode = ((fs & BIT(4))>>4);
    unsigned char rate     = fs & BIT_RNG(0, 2);
    unsigned int adc_clk = audio_codec_clk_get(fs);

    audio_codec_adc_clk_set(adc_clk);

    if (fs == AUDIO_768K)
    {
        reg_audio_codec_adc768k_out_fmt |= channel;
    }

    if (channel & AUDIO_LINEIN_ADC0)
    {
        reg_audio_codec_cfg_0 = (reg_audio_codec_cfg_0 & ~(FLD_CODEC_ADC0_RATE_SEL | FLD_CODEC_ADC0_PWR_MODE)) | MASK_VAL(FLD_CODEC_ADC0_RATE_SEL, rate)
         | MASK_VAL(FLD_CODEC_ADC0_PWR_MODE, pwr_mode);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        reg_audio_codec_cfg_1 = (reg_audio_codec_cfg_1 & ~(FLD_CODEC_ADC1_RATE_SEL | FLD_CODEC_ADC1_PWR_MODE)) | MASK_VAL(FLD_CODEC_ADC1_RATE_SEL, rate)
         | MASK_VAL(FLD_CODEC_ADC1_PWR_MODE, pwr_mode);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        reg_audio_codec_cfg_2 = (reg_audio_codec_cfg_2 & ~(FLD_CODEC_ADC2_RATE_SEL | FLD_CODEC_ADC2_PWR_MODE)) | MASK_VAL(FLD_CODEC_ADC2_RATE_SEL, rate)
         | MASK_VAL(FLD_CODEC_ADC2_PWR_MODE, pwr_mode);

    }
}

/**
 * @brief      This function serves to set codec output sample rate.
 * @param[in]  fs - output sample rate.
 * @return     none
 * @note
 */
void audio_codec_set_output_fs(audio_codec_output_select_e output, audio_sample_rate_e fs)
{
    unsigned char pwr_mode = ((fs & BIT(4))>>4);
    unsigned char rate     = fs & BIT_RNG(0, 2);
    unsigned int dac_clk = audio_codec_clk_get(fs);
    audio_codec_dac_clk_set(dac_clk);

    if (output & AUDIO_DAC_A0)
    {
        reg_audio_codec_cfg_5 = (reg_audio_codec_cfg_5 & ~(FLD_CODEC_DAC0_RATE_SEL | FLD_CODEC_DAC0_PWR_MODE))
                                  | MASK_VAL(FLD_CODEC_DAC0_RATE_SEL, rate) | MASK_VAL(FLD_CODEC_DAC0_PWR_MODE, pwr_mode);
    }

    if (output & AUDIO_DAC_A1)
    {
        reg_audio_codec_cfg_7 = (reg_audio_codec_cfg_7 & ~(FLD_CODEC_DAC1_RATE_SEL | FLD_CODEC_DAC1_PWR_MODE))
                                  | MASK_VAL(FLD_CODEC_DAC1_RATE_SEL, rate) | MASK_VAL(FLD_CODEC_DAC1_PWR_MODE, pwr_mode);
    }

}

/**
 * @brief      This function serves to set codec input data bit width.
 * @param[in]  input - input channel.
 * @param[in]  wl    - bit width.
 * @return     none
 * @note
 */
void audio_codec_set_input_wl(audio_codec_input_select_e input, audio_codec_data_select_e wl)
{
    unsigned char channel = input & BIT_RNG(0, 2); //bit[0-2] adc channel.

    if (channel & AUDIO_LINEIN_ADC0)
    {
        if (wl == AUDIO_CODEC_BIT_16_DATA)
        {
            reg_audio_codec_adc_fmt_l |= (FLD_CODEC_ADC0_768_SEL | FLD_CODEC_ADC0_384_SEL | FLD_CODEC_ADC0_192_SEL | FLD_CODEC_ADC0_96_SEL | FLD_CODEC_ADC0_48_SEL);
        }
        else
        {
            reg_audio_codec_adc_fmt_l &= ~(FLD_CODEC_ADC0_768_SEL | FLD_CODEC_ADC0_384_SEL | FLD_CODEC_ADC0_192_SEL | FLD_CODEC_ADC0_96_SEL | FLD_CODEC_ADC0_48_SEL);
        }
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        if (wl == AUDIO_CODEC_BIT_16_DATA)
        {
            reg_audio_codec_adc_fmt_l |= (FLD_CODEC_ADC1_768_SEL | FLD_CODEC_ADC1_384_SEL | FLD_CODEC_ADC1_192_SEL);
            reg_audio_codec_adc_fmt_2 |= (FLD_CODEC_ADC1_96_SEL | FLD_CODEC_ADC1_48_SEL);
        }
        else
        {
            reg_audio_codec_adc_fmt_l &= ~(FLD_CODEC_ADC1_768_SEL | FLD_CODEC_ADC1_384_SEL | FLD_CODEC_ADC1_192_SEL);
            reg_audio_codec_adc_fmt_2 &= ~(FLD_CODEC_ADC1_96_SEL | FLD_CODEC_ADC1_48_SEL);
        }
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        if (wl == AUDIO_CODEC_BIT_16_DATA)
        {
            reg_audio_codec_adc_fmt_2 |= (FLD_CODEC_ADC2_768_SEL | FLD_CODEC_ADC2_384_SEL | FLD_CODEC_ADC2_192_SEL | FLD_CODEC_ADC2_96_SEL | FLD_CODEC_ADC2_48_SEL);
        }
        else
        {
            reg_audio_codec_adc_fmt_2 &= ~(FLD_CODEC_ADC2_768_SEL | FLD_CODEC_ADC2_384_SEL | FLD_CODEC_ADC2_192_SEL | FLD_CODEC_ADC2_96_SEL | FLD_CODEC_ADC2_48_SEL);
        }
    }
}

/**
 * @brief      This function serves to set codec output data bit width.
 * @param[in]  output - output channel.
 * @param[in]  wl     - bit width.
 * @return     none
 */
void audio_codec_set_output_wl(audio_codec_output_select_e output, audio_codec_data_select_e wl)
{
    if (output & AUDIO_DAC_A0)
    {
        reg_audio_codec_dac_fmt = (reg_audio_codec_dac_fmt & ~FLD_CODEC_DAC0_SEL) | MASK_VAL(FLD_CODEC_DAC0_SEL, wl);
    }

    if (output & AUDIO_DAC_A1)
    {
        reg_audio_codec_dac_fmt = (reg_audio_codec_dac_fmt & ~FLD_CODEC_DAC1_SEL) | MASK_VAL(FLD_CODEC_DAC1_SEL, wl);
    }
}

/**
 * @brief      This function serves to set codec input analog gain.
 * @param[in]  input - input channel.
 * @param[in]  gain  - input analog gain.
 * @return     none
 * @note
 *             - input analog gain only for line_in or amic.
 */
void audio_codec_set_input_again(audio_codec_input_select_e input, audio_codec_input_again_e gain)
{
    unsigned char channel = input & BIT_RNG(0, 2); //bit[0-2] adc channel.

    if (channel & AUDIO_LINEIN_ADC0)
    {
        reg_audio_codec_cfg_8 = (reg_audio_codec_cfg_8 & ~FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1) | MASK_VAL(FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1, gain);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        reg_audio_codec_cfg_9 = (reg_audio_codec_cfg_9 & ~FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2) | MASK_VAL(FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2, gain);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        reg_audio_codec_cfg_10 = (reg_audio_codec_cfg_10 & ~FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3) | MASK_VAL(FLD_CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3, gain);
    }
}

/**
 * @brief      This function serves to set codec input digital gain.
 * @param[in]  input - input channel.
 * @param[in]  gain  - input digital gain.
 * @return     none
 */
void audio_codec_set_input_dgain(audio_codec_input_select_e input, audio_codec_input_dgain_e gain)
{
    unsigned char channel = input & BIT_RNG(0, 2); //bit[0-2] adc channel.

    if (channel & AUDIO_LINEIN_ADC0)
    {
        reg_audio_codec_adc0_dig_gain = (reg_audio_codec_adc0_dig_gain & ~(FLD_CODEC_ADC_GAIN_SMOOTH_SEL | FLD_CODEC_ADC_GAIN_ENABLE | FLD_CODEC_ADC_DST_GAIN_INDEX)) |
                 MASK_VAL(FLD_CODEC_ADC_DST_GAIN_INDEX, gain) | MASK_VAL(FLD_CODEC_ADC_GAIN_SMOOTH_SEL, 7) | FLD_CODEC_ADC_GAIN_ENABLE;
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        reg_audio_codec_adc1_dig_gain = (reg_audio_codec_adc1_dig_gain & ~(FLD_CODEC_ADC_GAIN_SMOOTH_SEL | FLD_CODEC_ADC_GAIN_ENABLE | FLD_CODEC_ADC_DST_GAIN_INDEX)) |
                 MASK_VAL(FLD_CODEC_ADC_DST_GAIN_INDEX, gain) | MASK_VAL(FLD_CODEC_ADC_GAIN_SMOOTH_SEL, 7) | FLD_CODEC_ADC_GAIN_ENABLE;
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        reg_audio_codec_adc2_dig_gain = (reg_audio_codec_adc2_dig_gain & ~(FLD_CODEC_ADC_GAIN_SMOOTH_SEL | FLD_CODEC_ADC_GAIN_ENABLE | FLD_CODEC_ADC_DST_GAIN_INDEX)) |
                 MASK_VAL(FLD_CODEC_ADC_DST_GAIN_INDEX, gain) | MASK_VAL(FLD_CODEC_ADC_GAIN_SMOOTH_SEL, 7) | FLD_CODEC_ADC_GAIN_ENABLE;
    }
}

/**
 * @brief      This function serves to set codec output analog gain.
 * @param[in]  output - output channel.
 * @param[in]  gain   - output analog gain.
 * @return     none
 */
void audio_codec_set_output_again(audio_codec_output_select_e output, audio_codec_output_again_e gain)
{
    if (output & AUDIO_DAC_A0)
    {
        reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~FLD_CODEC_I_CFG_AUTX_GAIN_USER_L) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_GAIN_USER_L, gain);
    }

    if (output & AUDIO_DAC_A1)
    {
        reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~FLD_CODEC_I_CFG_AUTX_GAIN_USER_R) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_GAIN_USER_R, gain);
    }
}

/**
 * @brief      This function serves to set codec output digital gain.
 * @param[in]  output - output channel.
 * @param[in]  gain   - output digital gain.
 * @return     none
 */
void audio_codec_set_output_dgain(audio_codec_output_select_e output, audio_codec_output_dgain_e gain)
{
    if (output & AUDIO_DAC_A0)
    {
        reg_audio_codec_dac0_dig_gain = (reg_audio_codec_dac0_dig_gain & ~(FLD_CODEC_DAC_DST_GAIN_INDEX | FLD_CODEC_DAC_GAIN_SMOOTH_SEL | FLD_CODEC_DAC_GAIN_ENABLE)) |
                MASK_VAL(FLD_CODEC_DAC_DST_GAIN_INDEX, gain) | MASK_VAL(FLD_CODEC_DAC_GAIN_SMOOTH_SEL, 7) | FLD_CODEC_DAC_GAIN_ENABLE;
    }

    if (output & AUDIO_DAC_A1)
    {
        reg_audio_codec_dac1_dig_gain = (reg_audio_codec_dac1_dig_gain & ~(FLD_CODEC_DAC_DST_GAIN_INDEX | FLD_CODEC_DAC_GAIN_SMOOTH_SEL | FLD_CODEC_DAC_GAIN_ENABLE)) |
                MASK_VAL(FLD_CODEC_DAC_DST_GAIN_INDEX, gain) | MASK_VAL(FLD_CODEC_DAC_GAIN_SMOOTH_SEL, 7) | FLD_CODEC_DAC_GAIN_ENABLE;
    }

}

/**
 * @brief      This function serves to enable/disable codec input HPF(High Pass Filter).
 * @param[in]  input  - input channel.
 * @param[in]  enable - 1: adc High Pass Filter active, 0:adc High Pass Filter inactive.
 * @return     none
 * @note
 */
void audio_codec_input_hpf_en(audio_codec_input_select_e input, unsigned char enable)
{
    unsigned char channel  = input & BIT_RNG(0, 2); //bit[0-2] adc channel.

    if (channel & AUDIO_LINEIN_ADC0)
    {
        reg_audio_codec_cfg_0 = (reg_audio_codec_cfg_0 & ~FLD_CODEC_ADC0_HPF_EN) | MASK_VAL(FLD_CODEC_ADC0_HPF_EN, enable);
    }

    if (channel & AUDIO_LINEIN_ADC1)
    {
        reg_audio_codec_cfg_1 = (reg_audio_codec_cfg_1 & ~FLD_CODEC_ADC1_HPF_EN) | MASK_VAL(FLD_CODEC_ADC1_HPF_EN, enable);
    }

    if (channel & AUDIO_LINEIN_ADC2)
    {
        reg_audio_codec_cfg_2 = (reg_audio_codec_cfg_2 & ~FLD_CODEC_ADC2_HPF_EN) | MASK_VAL(FLD_CODEC_ADC2_HPF_EN, enable);
    }
}

/**
 * @brief      This function serves to set codec ldo ana voltage.
 * @param[in]  vol  - audio_codec_ldo_ana_cdc_e.
 * @return     none
 * @note
 */
void audio_codec_ldo_ana_set(audio_codec_ldo_ana_cdc_e vol)
{
    analog_write_reg8(areg_aon_0x7e, (analog_read_reg8(areg_aon_0x7e) & ~FLD_LDO_VOL_SEL_ANA) | MASK_VAL(FLD_LDO_VOL_SEL_ANA, vol));
}

/**
 * @brief      This function serves to set codec ldo cdc voltage.
 * @param[in]  vol  - audio_codec_ldo_ana_cdc_e.
 * @return     none
 * @note
 */
void audio_codec_ldo_cdc_set(audio_codec_ldo_ana_cdc_e vol)
{
    analog_write_reg8(areg_aon_0x7e, (analog_read_reg8(areg_aon_0x7e) & ~FLD_LDO_VOL_SEL_CDC) | MASK_VAL(FLD_LDO_VOL_SEL_CDC, vol));
}

/**
 * @brief      This function serves to init codec input.
 * @param[in]  input_config - codec input config.
 * @return     none
 */
void audio_codec_input_init(audio_codec_input_config_t *input_config)
{
    //vol ana and cdc sel
    audio_codec_ldo_ana_set(AUDIO_CODEC_LDO_ANA_CDC_1P85V);
    audio_codec_ldo_cdc_set(AUDIO_CODEC_LDO_ANA_CDC_1P85V);

    //codec config
    audio_codec_set_input_wl(input_config->input_src, input_config->data_format);
    audio_codec_set_input_fs(input_config->input_src, input_config->sample_rate);

    reg_audio_codec_dac_cfg4 = (reg_audio_codec_dac_cfg4 & ~(FLD_CODEC_PGOOD_CDC)) | MASK_VAL(FLD_CODEC_PGOOD_CDC, 7);

    reg_audio_codec_dac_cfg3 = (reg_audio_codec_dac_cfg3 & ~(FLD_CODEC_VREF_ADC_TRIM)) | MASK_VAL(FLD_CODEC_VREF_ADC_TRIM, 8)| FLD_CODEC_BGR_ENP;

    audio_delay_ms(5);
    reg_audio_codec_cfg_13 |=  (FLD_CODEC_AUDIO_CODEC_REC_VREFP18_ENP | FLD_CODEC_AUDIO_CODEC_REC_VCOM_ENP) |
            FLD_CODEC_CDC_VREF_FAST_STARTUP_0P8 |
            FLD_CODEC_CDC_ENP_VREF_0P8;

    audio_codec_adc_rst_en(input_config->input_src);
    audio_codec_adc_ana_en(input_config->input_src);
    audio_delay_ms(40);

    reg_audio_codec_cfg_13 &= ~FLD_CODEC_CDC_VREF_FAST_STARTUP_0P8;
    audio_delay_ms(3);

    reg_audio_codec_cfg_8 &= ~(FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1 | FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1);
    reg_audio_codec_cfg_9 &= ~(FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2 | FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2);
    reg_audio_codec_cfg_10&= ~(FLD_CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3 | FLD_CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3);

    audio_codec_set_input_again(input_config->input_src, AUDIO_ADC_PGA_GAIN_0DB);
    audio_codec_set_input_dgain(input_config->input_src, AUDIO_ADC_DIG_GAIN_0DB);

    if (input_config->input_src & BIT(3))
    {
        audio_codec_set_micbias(1);
    }
}

/**
 * @brief      This function serves to get dac autx iref status.
 * @return     status
 */
unsigned char audio_codec_dac_get_autx_iref_ok_status(void)
{
    return (reg_audio_codec_intr_status & FLD_CODEC_O_AUTX_IREF_OK);
}

/**
 * @brief      This function serves to set dac autx power.
 * @param[in]  set  - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_autx_powerup_set(unsigned char set)
{
    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_AUTX_PDB)) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_PDB, set);
}

/**
 * @brief      This function serves to set dac L/R channel disable or enable.
 * @param[in]  output  - output channel.
 * @param[in]  flag    - 1:disable, 0:enable.
 * @return     none
 */
void audio_codec_dac_autx_ch_disable(audio_codec_output_select_e output, unsigned char flag)
{
    if (output & AUDIO_DAC_A0) {
        reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_AUTX_LCH_DISABLE)) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_LCH_DISABLE, flag);
    }
    if (output & AUDIO_DAC_A1) {
        reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_AUTX_RCH_DISABLE)) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_RCH_DISABLE, flag);
    }
}

/**
 * @brief      This function serves to set dac hpamp ofce enable or disable.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_hpamp_ofc_enable(unsigned char flag)
{
    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~(FLD_CODEC_I_CFG_HPAMP_OFC_ENA)) | MASK_VAL(FLD_CODEC_I_CFG_HPAMP_OFC_ENA, flag);
}

/**
 * @brief      This function serves to get dac hpamp ofce status.
 * @param[in]  output - output channel.
 * @return     none
 */
unsigned char audio_codec_dac_get_hpamp_ofc_status(audio_codec_output_select_e output)
{
    int val0 = 1, val1 = 1;
    if (output & AUDIO_DAC_A0) {
        val0 = reg_audio_codec_dac_status & FLD_CODEC_SYNC_O_HPAMP_OFC_DONE_L;
    }
    if (output & AUDIO_DAC_A1) {
        val1 = reg_audio_codec_dac_status & FLD_CODEC_SYNC_O_HPAMP_OFC_DONE_R;
    }
    return ((val0) && (val1));
}

/**
 * @brief      This function serves to set dac ed dss forcelow.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_ed_dss_forcelow(unsigned char flag)
{
    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~(FLD_CODEC_I_CFG_ED_DSS_FORCELOW)) | MASK_VAL(FLD_CODEC_I_CFG_ED_DSS_FORCELOW, flag);
}

/**
 * @brief      This function serves to set dac autx ofc neg18db.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_autx_ofc_neg18db_enable(unsigned char flag)
{
    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~(FLD_CODEC_I_CFG_AUTX_OFC_ENA1)) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_OFC_ENA1, flag);
}

/**
 * @brief      This function serves to get dac autx ofc status.
 * @param[in]  output - output channel.
 * @return     none
 */
unsigned char audio_codec_dac_get_autx_ofc_status(audio_codec_output_select_e output)
{
    int val0 = 1, val1 = 1;
    if (output & AUDIO_DAC_A0) {
        val0 = reg_audio_codec_dac_status & FLD_CODEC_SYNC_O_AUTX_OFC_DONE_L;
    }
    if (output & AUDIO_DAC_A0) {
        val0 = reg_audio_codec_dac_status & FLD_CODEC_SYNC_O_AUTX_OFC_DONE_R;
    }
    return ((val0) && (val1));
}

/**
 * @brief      This function serves to set dac ed dss forcehigh.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_ed_dss_forcehigh(unsigned char flag)
{
    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~(FLD_CODEC_I_CFG_ED_DSS_FORCEHIGH)) | MASK_VAL(FLD_CODEC_I_CFG_ED_DSS_FORCEHIGH, flag);
}

/**
 * @brief      This function serves to set dac autx ofc 0db.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_autx_ofc_0db_enable(unsigned char flag)
{
    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2 & ~(FLD_CODEC_I_CFG_AUTX_OFC_ENA2)) | MASK_VAL(FLD_CODEC_I_CFG_AUTX_OFC_ENA2, flag);
}

/**
 * @brief      This function serves to enable or disable dac dem.
 * @param[in]  flag    - 1:enable, 0:disable.
 * @return     none
 */
void audio_codec_dac_dem_enable(unsigned char flag)
{
    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_DEM_ENA)) | MASK_VAL(FLD_CODEC_I_CFG_DEM_ENA, flag);
}

/**
 * @brief      This function serves to init codec output config.
 * @param[in]  output_config - codec output config.
 * @return     none
 */
void audio_codec_output_init(audio_codec_output_config_t *output_config)
{
    //vol ana and cdc sel
    audio_codec_ldo_ana_set(AUDIO_CODEC_LDO_ANA_CDC_1P85V);
    audio_codec_ldo_cdc_set(AUDIO_CODEC_LDO_ANA_CDC_1P85V);

    audio_codec_set_output_fs(output_config->output_dst, output_config->sample_rate);
    audio_codec_set_output_wl(output_config->output_dst, output_config->data_format);

    reg_audio_codec_dac_cfg4 = (reg_audio_codec_dac_cfg4 & ~(FLD_CODEC_PGOOD_CDC)) | MASK_VAL(FLD_CODEC_PGOOD_CDC, 7);
    reg_audio_codec_dac_cfg3 = (reg_audio_codec_dac_cfg3 & ~(FLD_CODEC_VREF_DAC_TRIM)) | MASK_VAL(FLD_CODEC_VREF_DAC_TRIM, 8) | FLD_CODEC_BGR_ENP;

    audio_delay_ms(5);

    audio_codec_dac_rst_en(output_config->output_dst);

    audio_codec_set_output_mute(output_config->output_dst, AUDIO_DAC_MUTE_DSM);
    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~(FLD_CODEC_I_CFG_DEM_ED_ENA | FLD_CODEC_I_CFG_DEM_ED_THRESH_LOW | FLD_CODEC_I_CFG_DEM_ED_THRESH_HIGH))
                                 | FLD_CODEC_I_CFG_DEM_ED_ENA | MASK_VAL(FLD_CODEC_I_CFG_DEM_ED_THRESH_LOW, 6) | MASK_VAL(FLD_CODEC_I_CFG_DEM_ED_THRESH_HIGH, 6) | FLD_CODEC_I_CFG_DEM_ENA;


    audio_codec_set_output_mute(output_config->output_dst, AUDIO_DAC_MUTE_ANA);
    audio_codec_dac_autx_mute_enable(AUDIO_DAC_A0_A1,1);

    reg_audio_codec_dac_cfg1 = reg_audio_codec_dac_cfg1 & ~(FLD_CODEC_I_CFG_ED_NG_ENA);

    reg_audio_codec_dac_cfg1 |= FLD_CODEC_I_CFG_DSM_ENA;
    reg_audio_codec_dac_cfg4 |= FLD_CODEC_TX_IREF_PDB_CORE;

    audio_delay_ms(2);

    reg_audio_codec_dac_cfg4 &= ~FLD_CODEC_TX_IREF_PDB_CORE;
    audio_delay_ms(2);
    reg_audio_codec_dac_cfg4 |= FLD_CODEC_TX_IREF_PDB_CORE;

    // This while loop takes approximately 310ns.
    while(audio_codec_dac_get_autx_iref_ok_status() == 0){};

    audio_codec_dac_autx_powerup_set(1);

    audio_codec_dac_autx_ch_disable(output_config->output_dst, 0);

    audio_delay_ms(40);
    audio_codec_dac_hpamp_ofc_enable(1);

    // This while loop takes approximately 3.07ms.
    while (audio_codec_dac_get_hpamp_ofc_status(output_config->output_dst) == 0){audio_delay_ms(1);};

    audio_codec_dac_hpamp_ofc_enable(0);
    audio_delay_ms(2);

    audio_codec_dac_ed_dss_forcelow(1);

    audio_codec_dac_autx_ofc_neg18db_enable(1);

    // This while loop takes approximately 3.27ms.
    while (audio_codec_dac_get_autx_ofc_status(output_config->output_dst) == 0){audio_delay_ms(1);};

    audio_codec_dac_ed_dss_forcelow(0);


    audio_codec_dac_autx_ofc_neg18db_enable(0);
    audio_delay_ms(2);

    audio_codec_dac_ed_dss_forcehigh(1);

    audio_codec_dac_autx_ofc_0db_enable(1);

    // This while loop takes approximately 3.27ms.
    while (audio_codec_dac_get_autx_ofc_status(output_config->output_dst) == 0){audio_delay_ms(1);};

    audio_codec_dac_ed_dss_forcehigh(0);
    audio_codec_dac_autx_ofc_0db_enable(0);
    audio_delay_ms(2);

    audio_codec_dac_dem_enable(1);

    audio_codec_set_output_again(output_config->output_dst, AUDIO_DAC_AUTX_GAIN_0DB);
    audio_codec_set_output_dgain(output_config->output_dst, AUDIO_DAC_DIG_GAIN_0DB);

    audio_codec_dac_dem_mute_set(0);
    audio_codec_dac_autx_mute_enable(output_config->output_dst, 0);

#if (CODEC_DAC_MODE == DRV_CODEC_DAC_DSS_ENABLE)

    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~FLD_CODEC_I_CFG_ED_DSS_THRESH)
        | MASK_VAL(FLD_CODEC_I_CFG_ED_DSS_THRESH, 56);

    reg_audio_codec_dac_cfg1 = (reg_audio_codec_dac_cfg1 & ~(FLD_CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA | FLD_CODEC_I_CFG_ED_DSS_ZCD_ENA))
        | (FLD_CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA | FLD_CODEC_I_CFG_ED_DSS_ZCD_ENA);

    reg_audio_codec_dac_cfg2 = (reg_audio_codec_dac_cfg2
        & ~(FLD_CODEC_I_CFG_DSS_MULTIPLY_L | FLD_CODEC_I_CFG_DSS_MULTIPLY_R
            | FLD_CODEC_I_CFG_DSS_DIVIDE_L | FLD_CODEC_I_CFG_DSS_DIVIDE_R
            | FLD_CODEC_I_CFG_DSS_DIGGAIN_ENA))
        | MASK_VAL(FLD_CODEC_I_CFG_DSS_MULTIPLY_L, 8)
        | MASK_VAL(FLD_CODEC_I_CFG_DSS_MULTIPLY_R, 8)
        | MASK_VAL(FLD_CODEC_I_CFG_DSS_DIVIDE_L, 0)
        | MASK_VAL(FLD_CODEC_I_CFG_DSS_DIVIDE_R, 0)
        | FLD_CODEC_I_CFG_DSS_DIGGAIN_ENA;

    reg_audio_codec_dac_cfg0 = (reg_audio_codec_dac_cfg0 & ~FLD_CODEC_I_CFG_ED_DSS_ENA)
        | FLD_CODEC_I_CFG_ED_DSS_ENA;

#elif (CODEC_DAC_MODE == DRV_CODEC_DAC_NG_ENABLE)
    reg_audio_codec_dac_cfg1 = (reg_audio_codec_dac_cfg1 &~(FLD_CODEC_I_CFG_ED_NG_THRESH | FLD_CODEC_I_CFG_ED_NG_RLS_TIME | FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA | FLD_CODEC_I_CFG_ED_NG_ZCD_ENA | FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL | FLD_CODEC_I_CFG_ED_NG_ENA))
        | MASK_VAL(FLD_CODEC_I_CFG_ED_NG_THRESH, 113)
        | MASK_VAL(FLD_CODEC_I_CFG_ED_NG_RLS_TIME, 1)
        | MASK_VAL(FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL, 0)
        | FLD_CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA
        | FLD_CODEC_I_CFG_ED_NG_ZCD_ENA
        | FLD_CODEC_I_CFG_ED_NG_ENA;

#endif
}

/**
 * @brief      This function serves to power down codec, include codec adc and dac, close codec ldo_ana and ldo_cdc.
 * @return     none
 */
void audio_codec_power_down(void)
{
    audio_codec_adc_power_down(AUDIO_AMIC_ADC0_ADC1_ADC2);
    audio_codec_output_power_down(AUDIO_DAC_A0_A1);
}
/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio dmic interface                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio dmic interface
 * @{
 */

/**
 * @brief      This function serves to enable/disable dmic clock.
 * @param[in]  dmic_ch  - dmic channel.
 * @param[in]  enable - 1:enable dmic clock, 0:disable dmic clock.
 */
void audio_dmic_clk_en(audio_dmic_channel_e dmic_ch, unsigned char enable)
{
    if (enable)
    {
        reg_audio_clk_en_0 = reg_audio_clk_en_0 | BIT(dmic_ch + 5); //enable dmic clock
    }
    else
    {
        reg_audio_clk_en_0 = reg_audio_clk_en_0 & ~BIT(dmic_ch + 5); //disable dmic clock
    }
}
/**
 * @brief      This function serves to init dmic data pos/neg and dmic clk.
 * @param[in]  dmic_ch - dmic channel.
 * @return     none
 */
void audio_dmic_init(audio_dmic_channel_e dmic_ch)
{
    if (dmic_ch == AUDIO_DMIC0)
    {
        reg_audio_dmic_lr_data_ctrl_1 = 0x10;
        reg_audio_dmic_lr_data_ctrl_2 = 0xf0;
    }
    else
    {
        reg_audio_dmic_single_data_ctrl_1 = 0x10;
        reg_audio_dmic_single_data_ctrl_2 = 0xf0;
    }
    if ((PLL1_AUDIO_CLK_43P008M == g_audio_clk_index) || (PLL1_AUDIO_CLK_86P016M == g_audio_clk_index))
    {
        reg_audio_dmic_set = MASK_VAL(FLD_CLK_DMIC_SET, 1);
    }
    else
    {
        reg_audio_dmic_set = MASK_VAL(FLD_CLK_DMIC_SET, 2);
    }
}

/**
 * @brief      This function serves to init dmic data bit width.
 * @param[in]  dmic_ch - dmic channel.
 * @param[in]  wl      - data bit width.
 * @return     none
 */
void audio_dmic_set_input_wl(audio_dmic_channel_e dmic_ch, audio_dmic_data_select_e wl)
{
    if(AUDIO_DMIC0 == dmic_ch)
    {
        if(AUDIO_DMIC_BIT_16_DATA == wl)
        {
            reg_audio_dmic_codec_lr_gain_shift_ctrl = (reg_audio_dmic_codec_lr_gain_shift_ctrl & ~FLD_CODEC_GAIN_SHIFT_LR) |
                                                        MASK_VAL(FLD_CODEC_GAIN_SHIFT_LR, 0x16);
            reg_audio_dmic_codec_lr_low_latency_gain_ctrl = (reg_audio_dmic_codec_lr_low_latency_gain_ctrl & ~FLD_CODEC_GAIN_SHIFT_LOW_LATENCY) |
                                                                MASK_VAL(FLD_CODEC_GAIN_SHIFT_LOW_LATENCY, 0x16);
        }
        else
        {
            reg_audio_dmic_codec_lr_gain_shift_ctrl = (reg_audio_dmic_codec_lr_gain_shift_ctrl & ~FLD_CODEC_GAIN_SHIFT_LR) |
                                                        MASK_VAL(FLD_CODEC_GAIN_SHIFT_LR, 0xe);
            reg_audio_dmic_codec_lr_low_latency_gain_ctrl = (reg_audio_dmic_codec_lr_low_latency_gain_ctrl & ~FLD_CODEC_GAIN_SHIFT_LOW_LATENCY) |
                                                                MASK_VAL(FLD_CODEC_GAIN_SHIFT_LOW_LATENCY, 0xe);
        }
    }
    else
    {
        if(AUDIO_DMIC_BIT_16_DATA == wl)
        {
            reg_audio_dmic_codec_single_gain_shift_ctrl = (reg_audio_dmic_codec_single_gain_shift_ctrl & ~FLD_CODEC_GAIN_SHIFT_SINGLE) |
                                                        MASK_VAL(FLD_CODEC_GAIN_SHIFT_SINGLE, 0x16);
            reg_audio_dmic_codec_single_low_latency_gain_ctrl = (reg_audio_dmic_codec_single_low_latency_gain_ctrl & ~FLD_CODEC_GAIN_SHIFT_LOW) |
                                                                MASK_VAL(FLD_CODEC_GAIN_SHIFT_LOW, 0x16);
        }
        else
        {
            reg_audio_dmic_codec_single_gain_shift_ctrl = (reg_audio_dmic_codec_single_gain_shift_ctrl & ~FLD_CODEC_GAIN_SHIFT_SINGLE) |
                                                        MASK_VAL(FLD_CODEC_GAIN_SHIFT_SINGLE, 0xe);
            reg_audio_dmic_codec_single_low_latency_gain_ctrl = (reg_audio_dmic_codec_single_low_latency_gain_ctrl & ~FLD_CODEC_GAIN_SHIFT_LOW) |
                                                                MASK_VAL(FLD_CODEC_GAIN_SHIFT_LOW, 0xe);
        }
    }
    reg_audio_dmic_codec_lr_ctrl(dmic_ch) = (reg_audio_dmic_codec_lr_ctrl(dmic_ch) & (~FLD_CODEC_OUTPUT_BIT_SEL_LR)) |
                                            MASK_VAL(FLD_CODEC_OUTPUT_BIT_SEL_LR, !wl);
}

/**
 * @brief      This function serves to init dmic input simple rate.
 * @param[in]  dmic_ch - dmic channel.
 * @param[in]  fs      - dmic simple rate.
 * @return     none
 * @note       768k always enable
 */
void audio_dmic_set_input_fs(audio_dmic_channel_e dmic_ch, audio_sample_rate_e fs)
{
    if (PLL1_AUDIO_CLK_43P008M == g_audio_clk_index)
    {
        switch (fs)
        {
        case AUDIO_48K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(5);
            break;
        case AUDIO_16K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(4) | BIT(0);
            break;
        case AUDIO_96K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(6);
            break;
        case AUDIO_192K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(7);
            break;
        default:
            break;
        }
    }
    else /* reference root_clk = 86.016MHz (172.032M/2 or 86.016M/1) */
    {
        switch (fs)
        {
        case AUDIO_16K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(0);
            break;
        case AUDIO_44P1K:
        case AUDIO_48K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) & (~BIT(0));
            break;
        case AUDIO_32K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(4) | BIT(0);
            break;
        case AUDIO_96K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(5);
            break;
        case AUDIO_192K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(6);
            break;
        case AUDIO_384K:
            reg_audio_dmic_codec_lr_ctrl(dmic_ch) = reg_audio_dmic_codec_lr_ctrl(dmic_ch) | BIT(7);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief      This function serves to set dmic0 channel.
 * @param[in]  ch - dmic0 input channel.
 * @return     none
 */
void audio_dmic0_set_stereo(audio_dmic_input_select_e ch)
{
    reg_audio_dmic_codec_lr_ctrl(0) = (reg_audio_dmic_codec_lr_ctrl(0) & ~FLD_CODEC_CH_SEL_LR) |
                                      MASK_VAL(FLD_CODEC_CH_SEL_LR, (ch & 3) == 3);
}

/**
 * @brief      This function serves to set dmic digital gain.
 * @param[in]  dmic_ch - dmic channel.
 * @param[in]  gain    - dmic gain.
 * @return     none
 */
void audio_dmic_set_dgain(audio_dmic_channel_e dmic_ch, audio_dmic_dgain_e gain)
{
    if (dmic_ch == AUDIO_DMIC0)
    {
        reg_audio_dmic_codec_lr_gain_ctrl = (reg_audio_dmic_codec_lr_gain_ctrl & ~FLD_CODEC_GAIN_LR) |
                                            MASK_VAL(FLD_CODEC_GAIN_LR, gain);
    }
    else
    {
        reg_audio_dmic_codec_single_gain_ctrl = (reg_audio_dmic_codec_single_gain_ctrl & ~FLD_CODEC_GAIN_SINGLE) |
                                                MASK_VAL(FLD_CODEC_GAIN_SINGLE, gain);
    }
}

/**
 * @brief      This function serves to enable dmic channel.
 * @param[in]  dmic_ch - dmic channel.
 * @param[in]  en      - 1:enable, 0:disable.
 * @return     none
 */
void audio_dmic_en(audio_dmic_channel_e dmic_ch, unsigned char en)
{
    if (dmic_ch == AUDIO_DMIC0)
    {
        reg_audio_dmic_codec_lr_gain_shift_ctrl = (reg_audio_dmic_codec_lr_gain_shift_ctrl & ~FLD_CODEC_CODEC_EN_LR) |
                                            MASK_VAL(FLD_CODEC_CODEC_EN_LR, en);
    }
    else
    {
        reg_audio_dmic_codec_lr_gain_shift_ctrl = (reg_audio_dmic_codec_lr_gain_shift_ctrl & ~FLD_CODEC_CODEC_EN_SINGLE) |
                                                MASK_VAL(FLD_CODEC_CODEC_EN_SINGLE, en);
    }
}

/**
 * @brief      This function serves to init dmic input.
 * @param[in]  input_config - dmic input config.
 * @return     none
 */
void audio_dmic_input_init(audio_dmic_input_config_t *input_config)
{
    audio_dmic_channel_e dmic_channel = (input_config->input_src & BIT(2)) ? 1 : 0;
    audio_dmic_clk_en(dmic_channel, 1);
    audio_dmic_init(dmic_channel);
    audio_dmic_set_input_wl(dmic_channel, input_config->data_format);
    audio_dmic_set_input_fs(dmic_channel, input_config->sample_rate);

    audio_dmic_set_dgain(dmic_channel, input_config->d_gain);
    if (dmic_channel == AUDIO_DMIC0)
    {
        audio_dmic0_set_stereo(input_config->input_src);
    }

    audio_dmic_en(dmic_channel, 1);
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio dma/fifo interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio dma/fifo interface
 * @{
 */

/**
 * @brief      This function serves to config  rx_dma channel.
 * @param[in]  chn          - dma channel
 * @param[in]  dst_addr     - Pointer to data buffer, it must be 4-bytes aligned address.
 *                            and the actual buffer size defined by the user needs to be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  data_len     - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @param[in]  head_of_list - the head address of dma llp.
 * @return     none
 */
void audio_rx_dma_config(dma_chn_e chn, unsigned short *dst_addr, unsigned int data_len, dma_chain_config_t *head_of_list)
{
    audio_rx_dma_chn = chn;
    audio_set_rx_buff_len(audio_rx_fifo_chn, data_len);
    dma_config(chn, &audio_dma_rx_config[audio_rx_fifo_chn]);
    dma_set_address(chn, REG_AUDIO_FIFO_ADDR(audio_rx_fifo_chn), (unsigned int)(dst_addr));
    dma_set_size(chn, data_len, DMA_WORD_WIDTH);
    reg_dma_llp(chn) = (unsigned int)(head_of_list);
}

/**
 * @brief      This function serves to set rx dma chain transfer.
 * @param[in]  config_addr - the head of list of llp_pointer.
 * @param[in]  llpointer   - the next element of llp_pointer.
 * @param[in]  dst_addr    - Pointer to data buffer, it must be 4-bytes aligned address and the actual buffer size defined by the user needs to
 *                           be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  data_len    - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @return     none
 */
void audio_rx_dma_add_list_element(dma_chain_config_t *config_addr, dma_chain_config_t *llpointer, unsigned short *dst_addr, unsigned int data_len)
{
    config_addr->dma_chain_ctl      = reg_dma_ctrl(audio_rx_dma_chn) | FLD_DMA_CHANNEL_ENABLE;
    config_addr->dma_chain_src_addr = REG_AUDIO_FIFO_ADDR(audio_rx_fifo_chn);
    config_addr->dma_chain_dst_addr = (unsigned int)(dst_addr);
    config_addr->dma_chain_data_len = dma_cal_size(data_len, 4);
    config_addr->dma_chain_llp_ptr  = (unsigned int)(llpointer);
}

/**
 * @brief      This function serves to set audio rx dma chain transfer.
 * @param[in]  rx_fifo_chn - rx fifo select.
 * @param[in]  chn         - dma channel.
 * @param[in]  in_buff     - Pointer to data buffer, it must be 4-bytes aligned address and the actual buffer size defined by the user needs to
 *                           be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  buff_size   - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @return     none
 */
void audio_rx_dma_chain_init(audio_fifo_chn_e rx_fifo_chn, dma_chn_e chn, unsigned short *in_buff, unsigned int buff_size)
{
    audio_rx_fifo_chn = rx_fifo_chn;
    audio_rx_dma_config(chn, (unsigned short *)in_buff, buff_size, &g_audio_rx_dma_list_cfg[rx_fifo_chn]);
    audio_rx_dma_add_list_element(&g_audio_rx_dma_list_cfg[rx_fifo_chn], &g_audio_rx_dma_list_cfg[rx_fifo_chn], (unsigned short *)in_buff, buff_size);
}

/**
 * @brief      This function serves to config  tx_dma channel.
 * @param[in]  chn          - dma channel.
 * @param[in]  src_addr     - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  data_len     - Length of DMA in bytes, range from 1 to 0x10000.
 * @param[in]  head_of_list - the head address of dma llp.
 * @return     none
 */
void audio_tx_dma_config(dma_chn_e chn, unsigned short *src_addr, unsigned int data_len, dma_chain_config_t *head_of_list)
{

    audio_tx_dma_chn = chn;
    audio_set_tx_buff_len(audio_tx_fifo_chn, data_len);
    dma_config(chn, &audio_dma_tx_config[audio_tx_fifo_chn]);
    dma_set_address(chn, (unsigned int)(src_addr), REG_AUDIO_FIFO_ADDR(audio_tx_fifo_chn));
    dma_set_size(chn, data_len, DMA_WORD_WIDTH);
    reg_dma_llp(chn) = (unsigned int)head_of_list;
}

/**
 * @brief      This function serves to set tx dma chain transfer.
 * @param[in]  config_addr - the head of list of llp_pointer.
 * @param[in]  llpointer   - the next element of llp_pointer.
 * @param[in]  src_addr    - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  data_len    - Length of DMA in bytes, range from 1 to 0x10000.
 * @return     none
 */
void audio_tx_dma_add_list_element(dma_chain_config_t *config_addr, dma_chain_config_t *llpointer, unsigned short *src_addr, unsigned int data_len)
{
    config_addr->dma_chain_ctl      = reg_dma_ctrl(audio_tx_dma_chn) | FLD_DMA_CHANNEL_ENABLE;
    config_addr->dma_chain_src_addr = (unsigned int)src_addr;
    config_addr->dma_chain_dst_addr = REG_AUDIO_FIFO_ADDR(audio_tx_fifo_chn);
    config_addr->dma_chain_data_len = dma_cal_size(data_len, 4);
    config_addr->dma_chain_llp_ptr  = (unsigned int)llpointer;
}

/**
 * @brief      This function serves to initialize audio tx dma chain transfer.
 * @param[in]  tx_fifo_chn - tx fifo select.
 * @param[in]  chn         - dma channel.
 * @param[in]  out_buff    - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  buff_size   - Length of DMA in bytes, range from 1 to 0x10000.
 * @return     none
 */
void audio_tx_dma_chain_init(audio_fifo_chn_e tx_fifo_chn, dma_chn_e chn, unsigned short *out_buff, unsigned int buff_size)
{
    audio_tx_fifo_chn = tx_fifo_chn;
    audio_tx_dma_config(chn, (unsigned short *)out_buff, buff_size, &g_audio_tx_dma_list_cfg[tx_fifo_chn]);
    audio_tx_dma_add_list_element(&g_audio_tx_dma_list_cfg[tx_fifo_chn], &g_audio_tx_dma_list_cfg[tx_fifo_chn], (unsigned short *)out_buff, buff_size);
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio hac interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio hac interface
 * @{
 */

/**
 * @brief      This function servers to update hac biquad filter coefficients.
 * 
 * @param[in]  hac_chn - hac channel.
 * @param[in]  biquad  - biquad step audio_hac_biquad_e.
 * @param[in]  data    - biquad filter data address, [b0, b1, b2, a1, a2].
 * @return     none
 */
void audio_hac_update_biquad_coef(audio_hac_eq_chn_e eq_chn, audio_hac_biquad_e biquad, signed int *data)
{
    reg_audio_hac_eq_bq_b0(eq_chn, biquad) = data[0];
    reg_audio_hac_eq_bq_b1(eq_chn, biquad) = data[1];
    reg_audio_hac_eq_bq_b2(eq_chn, biquad) = data[2];
    reg_audio_hac_eq_bq_a1(eq_chn, biquad) = data[3];
    reg_audio_hac_eq_bq_a2(eq_chn, biquad) = data[4];
}

void audio_hac_set_input_num(audio_hac_chn_e hac_chn,unsigned short num)
{
    if(hac_chn <= HAC_CH3_ASRC1) {
        reg_audio_hac_eq_asrc_input_num(hac_chn) = num;
    } else {
        reg_audio_hac_eq2_input_num = num;
    }
}

void audio_hac_set_asrc_tdm_num(audio_hac_asrc_chn_e asrc_ch,unsigned char num)
{
    if(asrc_ch) {
        reg_audio_hac_asrc_tdm_num = (reg_audio_hac_asrc_tdm_num & (~FLD_HAC_ASRC1_TDM_NUM))|MASK_VAL(FLD_HAC_ASRC1_TDM_NUM, num);
    } else {
        reg_audio_hac_asrc_tdm_num = (reg_audio_hac_asrc_tdm_num & (~FLD_HAC_ASRC0_TDM_NUM))|MASK_VAL(FLD_HAC_ASRC0_TDM_NUM, num);
    }
}

/**
 * @brief      This function servers to select hac's asrc input and output fs.
 *
 * @param[in]  hac_chn   - hac channel.
 * @param[in]  fs_in     - input fs.
 * @param[in]  fs_out    - output fs.
 * @param[in]  ppm       - ppm value.
 * @param[in]  tdm_cn    - tdm channel count.
 * @return     none
 * @note       support fs in and out:
 *              - IN_16K_OUT_16K
 *              - IN_32K_OUT_16K
 *              - IN_44P1K_OUT_16K
 *              - IN_48K_OUT_16K
 *              - IN_96K_OUT_16K
 *              - IN_16K_OUT_32K
 *              - IN_32K_OUT_32K
 *              - IN_44P1K_OUT_32K
 *              - IN_48K_OUT_32K
 *              - IN_96K_OUT_32K
 *              - IN_16K_OUT_44P1K
 *              - IN_32K_OUT_44P1K
 *              - IN_44P1K_OUT_44P1
 *              - IN_48K_OUT_44P1K
 *              - IN_96K_OUT_44P1K
 *              - IN_16K_OUT_48K
 *              - IN_32K_OUT_48K
 *              - IN_44P1K_OUT_48K
 *              - IN_48K_OUT_48K
 *              - IN_96K_OUT_48K
 *              - IN_16K_OUT_96K
 *              - IN_32K_OUT_96K
 *              - IN_44P1K_OUT_96K
 *              - IN_48K_OUT_96K
 *              - IN_96K_OUT_96K
 *              - IN_768K_OUT_96K
 *              - IN_192K_OUT_192K
 *              - IN_384K_OUT_384K
 *              - IN_768K_OUT_768K
 *
 */
void audio_hac_asrc_fs_in_out(audio_hac_asrc_chn_e asrc_ch, int fs_in, int fs_out, int ppm, int tdm_chn)
{
    int  frac_advance = 0;
    int  den_rate     = 0;
    char int_advance  = 0;

    if (fs_in == fs_out) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 16;
            int_advance  = 15;
        } else {
            frac_advance = ppm * 16;
            int_advance  = 16;
        }
    } else if ((fs_in == 32000 && fs_out == 16000) || (fs_in == 96000 && fs_out == 48000)) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 32;
            int_advance  = 31;
        } else {
            frac_advance = ppm * 32;
            int_advance  = 32;
        }
    }

    else if ((fs_in == 48000 && fs_out == 16000) || (fs_in == 96000 && fs_out == 32000)) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 48;
            int_advance  = 47;
        } else {
            frac_advance = ppm * 48;
            int_advance  = 48;
        }
    }

    else if (fs_in == 96000 && fs_out == 16000) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 96;
            int_advance  = 95;
        } else {
            frac_advance = ppm * 96;
            int_advance  = 96;
        }
    }

    else if ((fs_in == 16000 && fs_out == 32000) || (fs_in == 48000 && fs_out == 96000)) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 8;
            int_advance  = 7;
        } else {
            frac_advance = ppm * 8;
            int_advance  = 8;
        }
    }

    else if (fs_in == 48000 && fs_out == 32000) {
        den_rate = 1000000;
        if (ppm <= 0) {
            frac_advance = 1000000 + ppm * 24;
            int_advance  = 23;
        } else {
            frac_advance = ppm * 24;
            int_advance  = 24;
        }
    }

    else if ((fs_in == 16000 && fs_out == 48000) || (fs_in == 32000 && fs_out == 96000)) {
        den_rate     = 3000000;
        frac_advance = 1000000 + ppm * 16;
        int_advance  = 5;
    }

    else if (fs_in == 32000 && fs_out == 48000) {
        den_rate     = 3000000;
        frac_advance = 2000000 + ppm * 32;
        int_advance  = 10;
    }

    else if (fs_in == 16000 && fs_out == 96000) {
        den_rate     = 3000000;
        frac_advance = 2000000 + ppm * 8;
        int_advance  = 2;
    }

    else if (fs_in == 44100 && fs_out == 16000) {
        den_rate     = 10000000;
        frac_advance = 1000000 + ppm * 441;
        int_advance  = 44;
    }

    else if (fs_in == 44100 && fs_out == 32000) {
        den_rate     = 20000000;
        frac_advance = 1000000 + ppm * 441;
        int_advance  = 22;
    }

    else if (fs_in == 44100 && fs_out == 48000) {
        den_rate     = 10000000;
        frac_advance = 7000000 + ppm * 147;
        int_advance  = 14;
    }

    else if (fs_in == 44100 && fs_out == 96000) {
        den_rate     = 20000000;
        frac_advance = 7000000 + ppm * 147;
        int_advance  = 7;
    }

    else if (fs_in == 16000 && fs_out == 44100) {
        den_rate     = 1378125; /* 459375 * 3 */
        frac_advance = 1109375 + ppm * 8;
        int_advance  = 5;
    }

    else if (fs_in == 32000 && fs_out == 44100) {
        den_rate     = 1378125; /* 459375 * 3 */
        frac_advance = 840625 + ppm * 16;
        int_advance  = 11;
    }

    else if (fs_in == 48000 && fs_out == 44100) {
        den_rate     = 459375;
        frac_advance = 190625 + ppm * 8;
        int_advance  = 17;
    }

    else if (fs_in == 96000 && fs_out == 44100) {
        den_rate     = 459375;
        frac_advance = 381250 + ppm * 16;
        int_advance  = 34;
    } else if (fs_in == 768000 && fs_out == 96000) {
        den_rate     = 1000000;
        frac_advance = 1000000;
        int_advance  = 127;
    }

    audio_hac_set_interval(asrc_ch, fs_in, tdm_chn);
    audio_hac_set_frac_adv(asrc_ch, frac_advance);
    audio_hac_set_den_rate(asrc_ch, den_rate);
    audio_hac_set_int_adv(asrc_ch, int_advance);
    audio_hac_lag_int_config_done(asrc_ch);
}

/**
 * @brief      This function servers to set hac interval.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  in_fs   - sample rate.
 * @param[in]  tdm_chn - tdm channel.
 * @return     none
 */
void audio_hac_set_interval(audio_hac_asrc_chn_e asrc_chn, int in_fs, int tdm_chn)
{
    if (tdm_chn == 4) {
        if (in_fs > 48000) {
            reg_audio_hac_asrc_interval = (reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2))));
        } else if (in_fs < 44100) {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x03 << ((asrc_chn) * 2)));
        } else {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x02 << ((asrc_chn) * 2)));
        }
    } else if (tdm_chn == 2) {
        if (in_fs > 96000) {
            reg_audio_hac_asrc_interval = (reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2))));
        } else if (in_fs < 96000) {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x03 << ((asrc_chn) * 2)));
        } else {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x02 << ((asrc_chn) * 2)));
        }
    } else {
        if (in_fs > 192000) {
            reg_audio_hac_asrc_interval = (reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2))));
        } else if (in_fs < 192000) {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x03 << ((asrc_chn) * 2)));
        } else {
            reg_audio_hac_asrc_interval = ((reg_audio_hac_asrc_interval & (~(0x03 << ((asrc_chn) * 2)))) | (0x02 << ((asrc_chn) * 2)));
        }
    }
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio I2S interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio I2S interface
 * @{
 */

/**
 * @brief      This function serves to config i2s line mode.
 * 
 * @param[in]  i2s_sel   - i2s select.
 * @param[in]  io_mode - line mode.
 * @return     none
 */
void audio_i2s_set_io_mode(i2s_select_e i2s_sel, i2s_io_mode_e io_mode)
{

    switch (io_mode) {
    case I2S_5_LINE_MODE:
        reg_audio_i2s_route(i2s_sel) = (reg_audio_i2s_route(i2s_sel) & (~FLD_I2S_MODE)) | I2S_5_LINE_MODE;
        break;
    case I2S_4_LINE_DAC_MODE:
        reg_audio_i2s_route(i2s_sel) = (reg_audio_i2s_route(i2s_sel) & (~FLD_I2S_MODE)) | I2S_4_LINE_DAC_MODE;
        break;
    case I2S_4_LINE_ADC_MODE:
        reg_audio_i2s_route(i2s_sel) = (reg_audio_i2s_route(i2s_sel) & (~FLD_I2S_MODE)) | I2S_4_LINE_ADC_MODE;
        break;
    case I2S_2_LANE_TX_MODE:
        BM_SET(reg_audio_i2s_cfg3(i2s_sel), FLD_I2S_TX_2LINE_EN);
        break;
    case I2S_2_LANE_RX_MODE:
        BM_SET(reg_audio_i2s_cfg3(i2s_sel), FLD_I2S_RX_2LINE_EN);
        break;
    default:
        break;
    }
}

/**
 * @brief      This function serves to config i2s0 interface, word length, and m/s.
 * @param[in]  i2s_sel      - i2s channel select
 * @param[in]  i2s_format   - interface protocol
 * @param[in]  wl           - audio data word length
 * @param[in]  m_s          - select i2s as master or slave
 * @param[in]  i2s_config_t - the ptr of i2s_config_t that configure i2s lr_clk phase and lr_clk swap.
 *  i2s_config_t->i2s_lr_clk_invert_select-lr_clk phase control(in RJ,LJ or i2s modes),in i2s mode(opposite phasing in  RJ,LJ mode), 0=right channel data when lr_clk high ,1=right channel data when lr_clk low.
 *                                                                                     in DSP mode(in DSP mode only), DSP mode A/B select,0=DSP mode A ,1=DSP mode B.
 *            i2s_config_t->i2s_data_invert_select - 0=left channel data left,1=right channel data left.
 * but data output channel will be inverted,you can also set i2s_config_t->i2s_data_invert_select=1 to recovery it.
 * @return    none
 */
void audio_i2s_config(i2s_select_e i2s_sel, i2s_mode_select_e i2s_format, i2s_wl_mode_e wl, i2s_m_s_mode_e m_s, i2s_invert_config_t *i2s_config_t)
{
    reg_audio_i2s_cfg1(i2s_sel) = (reg_audio_i2s_cfg1(i2s_sel) & (~(FLD_I2S_ADC_DCI_MS | FLD_I2S_DAC_DCI_MS))) |
                                  MASK_VAL(FLD_I2S_ADC_DCI_MS, m_s, FLD_I2S_DAC_DCI_MS, m_s);

    reg_audio_i2s_cfg2(i2s_sel) = (reg_audio_i2s_cfg2(i2s_sel) & (~(FLD_I2S_Wl | FLD_I2S_FORMAT))) |
                                  MASK_VAL(FLD_I2S_Wl, wl, FLD_I2S_FORMAT, i2s_format);


    reg_audio_i2s_cfg3(i2s_sel) =
        (reg_audio_i2s_cfg3(i2s_sel) & (~(FLD_I2S_LR_SWAP | FLD_I2S_LRP))) |
        MASK_VAL(FLD_I2S_LR_SWAP, i2s_config_t->i2s_data_invert_select, FLD_I2S_LRP, i2s_config_t->i2s_lr_clk_invert_select);
}

/**
 * @brief      This function serves to config tdm mode, word length, slot width, and master/slave.
 * 
 * @param[in]  tdm_mode       - tdm mode.
 * @param[in]  tdm_slot_width - tdm slow width.
 * @param[in]  rx_ch_num      - tdm rx channel num.
 * @param[in]  tx_ch_num      - tdm tx channel num.
 * @return     none
 */
void audio_i2s_tdm_config(i2s_tdm_mode_select_e tdm_mode, i2s_tdm_slot_width_e tdm_slot_width, unsigned char rx_ch_num, unsigned char tx_ch_num)
{
    reg_audio_i2s0_tdm_cfg = MASK_VAL(FLD_I2S_TDM_RX_CH_NUM, ((rx_ch_num - 1) >> 1), FLD_I2S_TDM_TX_CH_NUM, ((tx_ch_num - 1) >> 1), FLD_I2S_TDM_MODE, tdm_mode, FLD_I2S_TDM_SLOT, tdm_slot_width);
}

/**
 * @brief      This function serves to set sampling rate when i2s as master.
 * @param[in]  i2s_select - i2s channel select
 * @param[in]  i2s_clk_config                         i2s_clk_config[2]                   i2s_clk_config[3]-->lrclk_adc(sampling rate)
                                                             ||                                 ||
 *  audio_clk(36.864M default)------->div---->i2s_clk--->2 * div(div = 0, bypass)--->blck----->div
 *                                    ||                                                        ||
 *                     i2s_clk_config[0]/i2s_clk_config[1]                               i2s_clk_config[4]-->lrclk_dac (sampling rate)
 *
 *  For example: sampling rate = 16K, i2s_clk_config[5] = { 1, 3, 6, 64, 64 }, sampling rate = 36.864MHz * (1 / 3) / (2 * 6) / (64)  = 16KHz.
 * @return    none
 * @attention The default is from audio_clk 36.864M(default). If the pll is changed, the clk will be changed accordingly.
 */
void audio_i2s_set_clock(i2s_select_e i2s_select, unsigned short *i2s_clk_config)
{
    audio_i2s_set_clk(i2s_select, i2s_clk_config[0], i2s_clk_config[1]);
    audio_i2s_set_bclk(i2s_select, i2s_clk_config[2]);
    audio_i2s_set_lrclk(i2s_select, i2s_clk_config[3], i2s_clk_config[4]);
}

/**
 * @brief      This function serves to initialize configuration i2s.
 * @param[in]  i2s_config - the relevant configuration struct pointer @see audio_i2s_config_t.
 * @return     none
 */
void audio_i2s_config_init(audio_i2s_config_t *i2s_config)
{
    audio_i2s_set_pin(i2s_config->i2s_select, i2s_config->pin_config);
    if (i2s_config->master_slave_mode == I2S_AS_MASTER_EN) {
        audio_i2s_set_clock(i2s_config->i2s_select, i2s_config->sample_rate);
    }
    audio_i2s_set_io_mode(i2s_config->i2s_select, i2s_config->io_mode);
    audio_i2s_config(i2s_config->i2s_select, i2s_config->i2s_mode, i2s_config->data_width, i2s_config->master_slave_mode, &audio_i2s_invert_config[i2s_config->i2s_select]);
    if (i2s_config->i2s_mode == I2S_TDM_MODE && i2s_config->i2s_select == I2S0) {
        audio_i2s_tdm_config(i2s_config->tdm_mode, i2s_config->tdm_slot_width, (i2s_config->sample_rate[3] / (16 + i2s_config->tdm_slot_width * 8)), i2s_config->sample_rate[4] / (16 + i2s_config->tdm_slot_width * 8));
    }
    reg_audio_clk_en_0 |= BIT(1 + i2s_config->i2s_select);
//    audio_i2s_clk_en(i2s_config->i2s_select);

}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio matrix interface                                              *
 *********************************************************************************************************************/
/*!
 * @name Audio matrix interface
 * @{
 */

/**
 * @brief      This function serves to select fifo rx route source and data format.
 *
 * @param[in]  fifo_num    - fifo channel.
 * @param[in]  route_from  - fifo rx route from.
 * @param[in]  data_format - fifo rx data format(route from i2s/anc/adc/hac valid), others select FIFO_RX_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_rx_fifo_route(audio_fifo_chn_e fifo_num, audio_matrix_fifo_rx_route_e route_from, audio_matrix_fifo_rx_format_e data_format)
{
    reg_audio_matrix_fifo_wr_sel(fifo_num) = (reg_audio_matrix_fifo_wr_sel(fifo_num) & (~FLD_MATRIX_FIFO_WR_SEL)) | route_from;

    switch (route_from) {
    case FIFO_RX_ROUTE_I2S0_RX:
        reg_audio_matrix_i2s0_rx_sel = (reg_audio_matrix_i2s0_rx_sel & (~FLD_MATRIX_I2S0_RX_SEL)) | MASK_VAL(FLD_MATRIX_I2S0_RX_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_I2S1_RX:
        reg_audio_matrix_i2s1_tx_dma_sel = (reg_audio_matrix_i2s1_tx_dma_sel & (~FLD_MATRIX_I2S1_RX_SEL)) | MASK_VAL(FLD_MATRIX_I2S1_RX_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_I2S2_RX:
        reg_audio_matrix_i2s2_rx_sel = (reg_audio_matrix_i2s2_rx_sel & (~FLD_MATRIX_I2S2_RX_SEL)) | MASK_VAL(FLD_MATRIX_I2S2_RX_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_ANC0:
        if (fifo_num < FIFO2) {
            reg_audio_matrix_anc0_rx_sel = (reg_audio_matrix_anc0_rx_sel & (~FLD_MATRIX_ANC0_RX_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_RX_SEL, data_format);
        } else {
            reg_audio_matrix_anc0_rx_sel = (reg_audio_matrix_anc0_rx_sel & (~FLD_MATRIX_ANC0_RX_V2_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_RX_V2_SEL, data_format);
        }
        break;
    case FIFO_RX_ROUTE_CODEC_768K:
        reg_audio_matrix_adc768_384_sel = (reg_audio_matrix_adc768_384_sel & (~FLD_MATRIX_ADC768_SEL)) | MASK_VAL(FLD_MATRIX_ADC768_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_CODEC_384K:
        reg_audio_matrix_adc768_384_sel = (reg_audio_matrix_adc768_384_sel & (~FLD_MATRIX_ADC384_SEL)) | MASK_VAL(FLD_MATRIX_ADC384_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_CODEC_192K:
        reg_audio_matrix_adc192_96_sel = (reg_audio_matrix_adc192_96_sel & (~FLD_MATRIX_ADC192_SEL)) | MASK_VAL(FLD_MATRIX_ADC192_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_CODEC_96K:
        reg_audio_matrix_adc192_96_sel = ((reg_audio_matrix_adc192_96_sel & (~FLD_MATRIX_ADC96_SEL)) | MASK_VAL(FLD_MATRIX_ADC96_SEL, data_format));
        break;
    case FIFO_RX_ROUTE_CODEC_48K:
        reg_audio_matrix_adc48_dmic768_sel = ((reg_audio_matrix_adc48_dmic768_sel & (~FLD_MATRIX_ADC48_SEL)) | MASK_VAL(FLD_MATRIX_ADC48_SEL, data_format));
        break;
    case FIFO_RX_ROUTE_DMIC_768K:
        reg_audio_matrix_adc48_dmic768_sel = (reg_audio_matrix_adc48_dmic768_sel & (~FLD_MATRIX_DMIC768_SEL)) | MASK_VAL(FLD_MATRIX_DMIC768_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_384K_LL:
        reg_audio_matrix_dmic384ll_192ll_sel = (reg_audio_matrix_dmic384ll_192ll_sel & (~FLD_MATRIX_DMIC384LL_SEL)) | MASK_VAL(FLD_MATRIX_DMIC384LL_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_192K_LL:
        reg_audio_matrix_dmic384ll_192ll_sel = (reg_audio_matrix_dmic384ll_192ll_sel & (~FLD_MATRIX_DMIC192LL_SEL)) | MASK_VAL(FLD_MATRIX_DMIC192LL_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_384K:
        reg_audio_matrix_dmic384_192_sel = (reg_audio_matrix_dmic384_192_sel & (~FLD_MATRIX_DMIC384_SEL)) | MASK_VAL(FLD_MATRIX_DMIC384_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_192K:
        reg_audio_matrix_dmic384_192_sel = (reg_audio_matrix_dmic384_192_sel & (~FLD_MATRIX_DMIC192_SEL)) | MASK_VAL(FLD_MATRIX_DMIC192_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_96K:
        reg_audio_matrix_dmic96_32_sel = (reg_audio_matrix_dmic96_32_sel & (~FLD_MATRIX_DMIC96_SEL)) | MASK_VAL(FLD_MATRIX_DMIC96_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_32K:
        reg_audio_matrix_dmic96_32_sel = (reg_audio_matrix_dmic96_32_sel & (~FLD_MATRIX_DMIC32_SEL)) | MASK_VAL(FLD_MATRIX_DMIC32_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_DMIC_16K_OR_48K:
        reg_audio_matrix_dmic16k48k_sel = (reg_audio_matrix_dmic16k48k_sel & (~FLD_MATRIX_DMIC16K48K_SEL)) | MASK_VAL(FLD_MATRIX_DMIC16K48K_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_SPDIF_RX:
        break;
    case FIFO_RX_ROUTE_USB_ISO_RX:
        break;
    case FIFO_RX_ROUTE_EQ0:
        reg_audio_matrix_fifo_rx_hac01_sel = (reg_audio_matrix_fifo_rx_hac01_sel & (~FLD_MATRIX_FIFO_RX_HAC0_SEL)) | MASK_VAL(FLD_MATRIX_FIFO_RX_HAC0_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_EQ1:
        reg_audio_matrix_fifo_rx_hac01_sel = (reg_audio_matrix_fifo_rx_hac01_sel & (~FLD_MATRIX_FIFO_RX_HAC1_SEL)) | MASK_VAL(FLD_MATRIX_FIFO_RX_HAC1_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_EQ2:
        reg_audio_matrix_hac4_rx_dma_sel = (reg_audio_matrix_hac4_rx_dma_sel & (~FLD_MATRIX_HAC4_RX_DMA)) | MASK_VAL(FLD_MATRIX_HAC4_RX_DMA, data_format);
        break;
    case FIFO_RX_ROUTE_ASRC0_TDM0_DATA:
        reg_audio_matrix_fifo_rx_hac23_sel = (reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC2_SEL)) | MASK_VAL(FLD_MATRIX_FIFO_RX_HAC2_SEL, data_format);
        break;
    case FIFO_RX_ROUTE_ASRC1_TDM1_DATA:
        reg_audio_matrix_fifo_rx_hac23_sel = (reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC3_SEL)) | MASK_VAL(FLD_MATRIX_FIFO_RX_HAC3_SEL, data_format);
        break;
    default:
        break;
    }
}

/**
 * @brief   This function serves to select i2s tx route source and data format.
 *
 * @param[in]  i2s_tx_chn  - i2s tx channel.
 * @param[in]  route_from  - i2s tx route from.
 * @param[in]  data_format - i2s tx data format(route from fifo/hac2/hac3 valid), others select I2S_TX_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_i2s_tx_route(audio_i2s_tx_chn_e i2s_tx_chn, audio_matrix_i2s_tx_route_e route_from, audio_matrix_i2s_tx_format_e data_format)
{
    /* matrix route select. */
    switch (i2s_tx_chn) {
    case I2S0_CHN0:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN0) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN0) & (~FLD_MATRIX_I2S0_EVEN_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_EVEN_TX_SEL, route_from);
        break;
    case I2S0_CHN1:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN1) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN1) & (~FLD_MATRIX_I2S0_ODD_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_ODD_TX_SEL, route_from);
        break;
    case I2S0_CHN2:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN2) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN2) & (~FLD_MATRIX_I2S0_EVEN_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_EVEN_TX_SEL, route_from);
        break;
    case I2S0_CHN3:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN3) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN3) & (~FLD_MATRIX_I2S0_ODD_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_ODD_TX_SEL, route_from);
        break;
    case I2S0_CHN4:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN4) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN4) & (~FLD_MATRIX_I2S0_EVEN_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_EVEN_TX_SEL, route_from);
        break;
    case I2S0_CHN5:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN5) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN5) & (~FLD_MATRIX_I2S0_ODD_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_ODD_TX_SEL, route_from);
        break;
    case I2S0_CHN6:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN6) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN6) & (~FLD_MATRIX_I2S0_EVEN_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_EVEN_TX_SEL, route_from);
        break;
    case I2S0_CHN7:
        reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN7) = (reg_audio_matrix_i2s0_ch_tx_sel(I2S0_CHN7) & (~FLD_MATRIX_I2S0_ODD_TX_SEL)) |
                                                     MASK_VAL(FLD_MATRIX_I2S0_ODD_TX_SEL, route_from);
        break;
    case I2S1_CHN0:
        reg_audio_matrix_i2s1_ch01_tx_sel = (reg_audio_matrix_i2s1_ch01_tx_sel & (~FLD_MATRIX_I2S1_CH0_TX_SEL)) |
                                            MASK_VAL(FLD_MATRIX_I2S1_CH0_TX_SEL, route_from);
        break;
    case I2S1_CHN1:
        reg_audio_matrix_i2s1_ch01_tx_sel = (reg_audio_matrix_i2s1_ch01_tx_sel & (~FLD_MATRIX_I2S1_CH1_TX_SEL)) |
                                            MASK_VAL(FLD_MATRIX_I2S1_CH1_TX_SEL, route_from);
        break;
    case I2S2_CHN0:
        reg_audio_matrix_i2s2_ch01_tx_sel = (reg_audio_matrix_i2s2_ch01_tx_sel & (~FLD_MATRIX_I2S2_CH0_TX_SEL)) |
                                            MASK_VAL(FLD_MATRIX_I2S2_CH0_TX_SEL, route_from);
        break;
    case I2S2_CHN1:
        reg_audio_matrix_i2s2_ch01_tx_sel = (reg_audio_matrix_i2s2_ch01_tx_sel & (~FLD_MATRIX_I2S2_CH1_TX_SEL)) |
                                            MASK_VAL(FLD_MATRIX_I2S2_CH1_TX_SEL, route_from);
        break;
    default:
        break;
    }

    /* find i2s num. */
    unsigned char i2s_select = 0;
    if (i2s_tx_chn <= I2S0_CHN7) {
        i2s_select = I2S0;
    } else if ((i2s_tx_chn > I2S0_CHN7) && (i2s_tx_chn <= I2S1_CHN1)) {
        i2s_select = I2S1;
    } else {
        i2s_select = I2S2;
    }

    if (route_from == I2S_TX_ROUTE_FIFO) /* set i2s data format. */
    {
        switch (i2s_select) {
        case I2S0:
            reg_audio_matrix_i2s0_tx_dma_sel = (reg_audio_matrix_i2s0_tx_dma_sel & (~FLD_MATRIX_I2S0_TX_DMA_SEL)) | data_format;
            break;
        case I2S1:
            reg_audio_matrix_i2s1_tx_dma_sel = (reg_audio_matrix_i2s1_tx_dma_sel & (~FLD_MATRIX_I2S1_TX_DMA_SEL)) | data_format;
            break;
        case I2S2:
            reg_audio_matrix_i2s2_tx_dma_sel = (reg_audio_matrix_i2s2_tx_dma_sel & (~FLD_MATRIX_I2S2_TX_DMA_SEL)) | data_format;
            break;
        default:
            break;
        }
    }
}

/**
 * @brief      This function serves to select anc_src route source and format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_src route from.
 * @param[in]  data_format - anc src data format(route from fifo/i2s/adc valid), others select ANC_SRC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_src_route(audio_anc_chn_e anc_chn, audio_anc_src_chn_e src_chn, audio_matrix_anc_src_route_e route_from, audio_matrix_anc_src_format_e data_format)
{
    if ((anc_chn == ANC0) && (src_chn == ANC0_SRC0))
    {
        reg_audio_matrix_anc0_src0_sel = (reg_audio_matrix_anc0_src0_sel & (~FLD_MATRIX_ANC0_SRC0_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_SRC0_SEL, route_from);
        if (anc_chn == ANC0) {
            switch (route_from) {
            case ANC_SRC_ROUTE_FIFO:
                reg_audio_matrix_anc0_src_dma_sel = (reg_audio_matrix_anc0_src_dma_sel & (~FLD_MATRIX_ANC0_SRC_DMA_SEL)) |
                                                         MASK_VAL(FLD_MATRIX_ANC0_SRC_DMA_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(0) = (reg_audio_matrix_i2s_rx_anc_sel_0(0) & (~FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(1) = (reg_audio_matrix_i2s_rx_anc_sel_0(1) & (~FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(2) = (reg_audio_matrix_i2s_rx_anc_sel_0(2) & (~FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_CODEC_96K:
                reg_audio_matrix_adc_rx_anc_sel_0 = (reg_audio_matrix_adc_rx_anc_sel_0 & (~FLD_MATRIX_ADC96_RX_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC96_RX_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_CODEC_48K:
                reg_audio_matrix_adc_rx_anc_sel_2 = (reg_audio_matrix_adc_rx_anc_sel_2 & (~FLD_MATRIX_ADC48_RX_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC48_RX_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic768_anc0_sel1 = (reg_audio_matrix_dmic768_anc0_sel1 & (~FLD_MATRIX_DMIC96_ANC0_SRC0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC96_ANC0_SRC0_SEL, data_format);
                break;
            case ANC_SRC_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic384ll_anc_sell = (reg_audio_matrix_dmic384ll_anc_sell & (~FLD_MATRIX_DMIC16K48K_ANC0_SRC_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_SRC_SEL, data_format);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief      This function serves to select anc_src route source and format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_ref route from.
 * @param[in]  data_format - anc ref data format(route from i2s/adc valid), others select ANC_REF_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_ref_route(audio_anc_chn_e anc_chn, audio_anc_ref_chn_e ref_chn, audio_matrix_anc_ref_route_e route_from, audio_matrix_anc_ref_format_e data_format)
{
    if (anc_chn == ANC0)
    {
        if (ref_chn == ANC0_REF0)
        {
            reg_audio_matrix_anc0_ref0_sel = (reg_audio_matrix_anc0_ref0_sel & (~FLD_MATRIX_ANC0_REF0_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_REF0_SEL, route_from);
            switch (route_from) {
            case ANC_REF_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(0) = (reg_audio_matrix_i2s_rx_anc_sel_0(0) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(1) = (reg_audio_matrix_i2s_rx_anc_sel_0(1) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(2) = (reg_audio_matrix_i2s_rx_anc_sel_0(2) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_768K:
                reg_audio_matrix_adc_rx_anc_sel_0 = (reg_audio_matrix_adc_rx_anc_sel_0 & (~FLD_MATRIX_ADC768_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC768_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_384K:
                reg_audio_matrix_adc_rx_anc_sel_2 = (reg_audio_matrix_adc_rx_anc_sel_2 & (~FLD_MATRIX_ADC384_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC384_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_192K:
                reg_audio_matrix_adc_rx_anc_sel_4 = (reg_audio_matrix_adc_rx_anc_sel_4 & (~FLD_MATRIX_ADC192_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC192_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_sel1 = (reg_audio_matrix_dmic768_anc0_sel1 & (~FLD_MATRIX_DMIC768_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC768_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc_sell = (reg_audio_matrix_dmic384ll_anc_sell & (~FLD_MATRIX_DMIC384LL_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_REF0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_rx_anc_sel_0 = (reg_audio_matrix_dmic192ll_rx_anc_sel_0 & (~FLD_MATRIX_DMIC192LL_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_REF0_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else if (ref_chn == ANC0_REF1)
        {
            reg_audio_matrix_anc0_ref1_sel = (reg_audio_matrix_anc0_ref1_sel & (~FLD_MATRIX_ANC0_REF1_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_REF1_SEL, route_from);
            switch (route_from) {
            case ANC_REF_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(0) = (reg_audio_matrix_i2s_anc0_ref_sel(0) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(1) = (reg_audio_matrix_i2s_anc0_ref_sel(1) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(2) = (reg_audio_matrix_i2s_anc0_ref_sel(2) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_768K:
                reg_audio_matrix_adc_anc0_ref_sel(0) = (reg_audio_matrix_adc_anc0_ref_sel(0) & (~FLD_MATRIX_ADC_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_384K:
                reg_audio_matrix_adc_anc0_ref_sel(1) = (reg_audio_matrix_adc_anc0_ref_sel(1) & (~FLD_MATRIX_ADC_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_192K:
                reg_audio_matrix_adc_anc0_ref_sel(2) = (reg_audio_matrix_adc_anc0_ref_sel(2) & (~FLD_MATRIX_ADC_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic_anc0_ref_sel = (reg_audio_matrix_dmic_anc0_ref_sel & (~FLD_MATRIX_DMIC768_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC768_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_ref_sel = (reg_audio_matrix_dmic384ll_anc0_ref_sel & (~FLD_MATRIX_DMIC384LL_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_REF1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_ref_sel = (reg_audio_matrix_dmic192ll_anc0_ref_sel & (~FLD_MATRIX_DMIC192LL_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_REF1_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else
        {
            reg_audio_matrix_anc0_ref2_sel = (reg_audio_matrix_anc0_ref2_sel & (~FLD_MATRIX_ANC0_REF2_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_REF2_SEL, route_from);
            switch (route_from) {
            case ANC_REF_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(0) = (reg_audio_matrix_i2s_anc0_ref_sel(0) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(1) = (reg_audio_matrix_i2s_anc0_ref_sel(1) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(2) = (reg_audio_matrix_i2s_anc0_ref_sel(2) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_768K:
                reg_audio_matrix_adc_anc0_ref_sel(0) = (reg_audio_matrix_adc_anc0_ref_sel(0) & (~FLD_MATRIX_ADC_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_384K:
                reg_audio_matrix_adc_anc0_ref_sel(1) = (reg_audio_matrix_adc_anc0_ref_sel(1) & (~FLD_MATRIX_ADC_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_192K:
                reg_audio_matrix_adc_anc0_ref_sel(2) = (reg_audio_matrix_adc_anc0_ref_sel(2) & (~FLD_MATRIX_ADC_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic_anc0_ref_sel = (reg_audio_matrix_dmic_anc0_ref_sel & (~FLD_MATRIX_DMIC768_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC768_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_ref_sel = (reg_audio_matrix_dmic384ll_anc0_ref_sel & (~FLD_MATRIX_DMIC384LL_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_REF2_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_ref_sel = (reg_audio_matrix_dmic192ll_anc0_ref_sel & (~FLD_MATRIX_DMIC192LL_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_REF2_SEL, data_format);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief      This function serves to select anc_err route source and data format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_err route from.
 * @param[in]  data_format - anc err data format(route from i2s/adc valid), others select ANC_ERR_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_err_route(audio_anc_chn_e anc_chn, audio_anc_err_chn_e err_chn, audio_matrix_anc_err_route_e route_from, audio_matrix_anc_err_format_e data_format)
{
    if (anc_chn == ANC0)
    {
        if (err_chn == ANC0_ERR0)
        {
            reg_audio_matrix_anc0_err0_sel = (reg_audio_matrix_anc0_err0_sel & (~FLD_MATRIX_ANC0_ERR0_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_ERR0_SEL, route_from);
            switch (route_from) {
            case ANC_REF_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(0) = (reg_audio_matrix_i2s_rx_anc_sel_1(0) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(1) = (reg_audio_matrix_i2s_rx_anc_sel_1(1) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(2) = (reg_audio_matrix_i2s_rx_anc_sel_1(2) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_768K:
                reg_audio_matrix_adc_rx_anc_sel_1 = (reg_audio_matrix_adc_rx_anc_sel_1 & (~FLD_MATRIX_ADC768_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC768_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_384K:
                reg_audio_matrix_adc_rx_anc_sel_3 = (reg_audio_matrix_adc_rx_anc_sel_3 & (~FLD_MATRIX_ADC384_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC384_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_192K:
                reg_audio_matrix_adc_rx_anc_sel_5 = (reg_audio_matrix_adc_rx_anc_sel_5 & (~FLD_MATRIX_ADC192_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC192_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_sel2 = (reg_audio_matrix_dmic768_anc0_sel2 & (~FLD_MATRIX_DMIC768_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC768_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc_sel2 = (reg_audio_matrix_dmic384ll_anc_sel2 & (~FLD_MATRIX_DMIC384LL_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_rx_anc_sel_1 = (reg_audio_matrix_dmic192ll_rx_anc_sel_1 & (~FLD_MATRIX_DMIC192LL_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_ERR0_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else
        {
            reg_audio_matrix_anc0_err1_sel = (reg_audio_matrix_anc0_err1_sel & (~FLD_MATRIX_ANC0_ERR1_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_ERR1_SEL, route_from);
            switch (route_from) {
            case ANC_REF_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_err_sel(0) = (reg_audio_matrix_i2s_anc0_err_sel(0) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_err_sel(1) = (reg_audio_matrix_i2s_anc0_err_sel(1) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_err_sel(2) = (reg_audio_matrix_i2s_anc0_err_sel(2) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_768K:
                reg_audio_matrix_adc_anc0_err_sel(0) = (reg_audio_matrix_adc_anc0_err_sel(0) & (~FLD_MATRIX_ADC_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_384K:
                reg_audio_matrix_adc_anc0_err_sel(1) = (reg_audio_matrix_adc_anc0_err_sel(1) & (~FLD_MATRIX_ADC_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_CODEC_192K:
                reg_audio_matrix_adc_anc0_err_sel(2) = (reg_audio_matrix_adc_anc0_err_sel(2) & (~FLD_MATRIX_ADC_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_ADC_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic_anc0_err_sel = (reg_audio_matrix_dmic_anc0_err_sel & (~FLD_MATRIX_DMIC768_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC768_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_err_sel = (reg_audio_matrix_dmic384ll_anc0_err_sel & (~FLD_MATRIX_DMIC384LL_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_REF_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_err_sel = (reg_audio_matrix_dmic192ll_anc0_err_sel & (~FLD_MATRIX_DMIC192LL_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_ERR1_SEL, data_format);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief      This function serves to select anc_err route source and data format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_err route from.
 * @param[in]  data_format - anc err data format(route from i2s/adc valid), others select ANC_ERR_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_bz_route(audio_anc_chn_e anc_chn, audio_anc_bz_chn_e bz_chn, audio_matrix_anc_bz_route_e route_from, audio_matrix_anc_bz_format_e data_format)
{
    if (anc_chn == ANC0)
    {
        if ((bz_chn == ANC0_BZ0) || (bz_chn == ANC0_BZ1) || (bz_chn == ANC0_BZ2))
        {
            reg_audio_matrix_anc0_bz_ref_sel(bz_chn) = (reg_audio_matrix_anc0_bz_ref_sel(bz_chn) & (~FLD_MATRIX_ANC0_BZ_REF_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_BZ_REF_SEL, route_from);
        }
        else //ANC0_BZ3,ANC0_BZ4
        {
            reg_audio_matrix_anc0_bz_err_sel(bz_chn) = (reg_audio_matrix_anc0_bz_err_sel(bz_chn) & (~FLD_MATRIX_ANC0_BZ_ERR_SEL)) | MASK_VAL(FLD_MATRIX_ANC0_BZ_ERR_SEL, route_from);
        }

        if (bz_chn == ANC0_BZ0)
        {
            switch (route_from) {
            case ANC_BZ_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(0) = (reg_audio_matrix_i2s_rx_anc_sel_0(0) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(1) = (reg_audio_matrix_i2s_rx_anc_sel_0(1) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_rx_anc_sel_0(2) = (reg_audio_matrix_i2s_rx_anc_sel_0(2) & (~FLD_MATRIX_I2S_RX_ANC0_REF0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_768K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel1 = (reg_audio_matrix_adc768_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC768_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC768_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_384K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel3 = (reg_audio_matrix_adc768_anc0_bz_ref_sel3 & (~FLD_MATRIX_ADC384_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC384_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_192K:
                reg_audio_matrix_adc192_anc0_bz_ref_sel1 = (reg_audio_matrix_adc192_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC192_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC192_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_96K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel1 = (reg_audio_matrix_adc96_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC96_ANC0_BZ_REF0_SEL)) |
                                                          MASK_VAL(FLD_MATRIX_ADC96_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_48K:
                reg_audio_matrix_adc48_anc0_bz_ref_sel1 = (reg_audio_matrix_adc48_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC48_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC48_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic768_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC768_ANC0_BZ_REF0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC768_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic384ll_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC384LL_ANC0_BZ_REF0_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC192LL_ANC0_BZ_REF0_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC384_ANC0_BZ_REF0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC384_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC192_ANC0_BZ_REF0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC192_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic96_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic96_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC96_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC96_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_32K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC32_ANC0_BZ_REF0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC32_ANC0_BZ_REF0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF0_SEL)) |
                                                               MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF0_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else if (bz_chn == ANC0_BZ1)
        {
            switch (route_from) {
            case ANC_BZ_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(0) = (reg_audio_matrix_i2s_anc0_ref_sel(0) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(1) = (reg_audio_matrix_i2s_anc0_ref_sel(1) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(2) = (reg_audio_matrix_i2s_anc0_ref_sel(2) & (~FLD_MATRIX_I2S_ANC0_REF1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_768K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel1 = (reg_audio_matrix_adc768_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC768_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC768_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_384K:
                reg_audio_matrix_adc384_anc0_bz_ref_sel1 = (reg_audio_matrix_adc384_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC384_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC384_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_192K:
                reg_audio_matrix_adc192_anc0_bz_ref_sel1 = (reg_audio_matrix_adc192_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC192_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC192_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_96K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel2 = (reg_audio_matrix_adc96_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC96_ANC0_BZ_REF1_SEL)) |
                                                          MASK_VAL(FLD_MATRIX_ADC96_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_48K:
                reg_audio_matrix_adc48_anc0_bz_ref_sel1 = (reg_audio_matrix_adc48_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC48_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC48_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic768_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC768_ANC0_BZ_REF1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC768_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic384ll_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC384LL_ANC0_BZ_REF1_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC192LL_ANC0_BZ_REF1_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC384_ANC0_BZ_REF1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC384_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K:
                reg_audio_matrix_dmic192_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic192_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC192_ANC0_BZ_REF1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC192_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic96_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic96_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC96_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC96_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_32K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC32_ANC0_BZ_REF1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC32_ANC0_BZ_REF1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF1_SEL)) |
                                                               MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF1_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else if (bz_chn == ANC0_BZ2)
        {
            switch (route_from) {
            case ANC_BZ_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(0) = (reg_audio_matrix_i2s_anc0_ref_sel(0) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(1) = (reg_audio_matrix_i2s_anc0_ref_sel(1) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_ref_sel(2) = (reg_audio_matrix_i2s_anc0_ref_sel(2) & (~FLD_MATRIX_I2S_ANC0_REF2_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_768K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel2 = (reg_audio_matrix_adc768_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC768_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC768_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_384K:
                reg_audio_matrix_adc384_anc0_bz_ref_sel1 = (reg_audio_matrix_adc384_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC384_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC384_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_192K:
                reg_audio_matrix_adc192_anc0_bz_ref_sel2 = (reg_audio_matrix_adc192_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC192_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC192_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_96K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel2 = (reg_audio_matrix_adc96_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC96_ANC0_BZ_REF2_SEL)) |
                                                          MASK_VAL(FLD_MATRIX_ADC96_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_48K:
                reg_audio_matrix_adc48_anc0_bz_ref_sel2 = (reg_audio_matrix_adc48_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC48_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC48_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic768_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC768_ANC0_BZ_REF2_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC768_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic384ll_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC384LL_ANC0_BZ_REF2_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC192LL_ANC0_BZ_REF2_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC384_ANC0_BZ_REF2_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC384_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K:
                reg_audio_matrix_dmic192_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic192_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC192_ANC0_BZ_REF2_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC192_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic96_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic96_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC96_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC96_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_32K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC32_ANC0_BZ_REF2_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC32_ANC0_BZ_REF2_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF2_SEL)) |
                                                               MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_BZ_REF2_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else if (bz_chn == ANC0_BZ3)
        {
            switch (route_from) {
            case ANC_BZ_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(0) = (reg_audio_matrix_i2s_rx_anc_sel_1(0) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(1) = (reg_audio_matrix_i2s_rx_anc_sel_1(1) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_rx_anc_sel_1(2) = (reg_audio_matrix_i2s_rx_anc_sel_1(2) & (~FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_RX_ANC0_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_768K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel2 = (reg_audio_matrix_adc768_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC768_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC768_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_384K:
                reg_audio_matrix_adc384_anc0_bz_ref_sel2 = (reg_audio_matrix_adc384_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC384_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC384_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_192K:
                reg_audio_matrix_adc192_anc0_bz_ref_sel2 = (reg_audio_matrix_adc192_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC192_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC192_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_96K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel3 = (reg_audio_matrix_adc96_anc0_bz_ref_sel3 & (~FLD_MATRIX_ADC96_ANC0_BZ_ERR0_SEL)) |
                                                          MASK_VAL(FLD_MATRIX_ADC96_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_48K:
                reg_audio_matrix_adc48_anc0_bz_ref_sel2 = (reg_audio_matrix_adc48_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC48_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC48_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_bz_err_sel = (reg_audio_matrix_dmic768_anc0_bz_err_sel & (~FLD_MATRIX_DMIC768_ANC0_BZ_ERR0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC768_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic384ll_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic384ll_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR0_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR0_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC384_ANC0_BZ_ERR0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC384_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K:
                reg_audio_matrix_dmic192_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic192_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC192_ANC0_BZ_ERR0_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC192_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic96_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic96_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC96_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC96_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_32K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC32_ANC0_BZ_ERR0_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC32_ANC0_BZ_ERR0_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR0_SEL)) |
                                                               MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR0_SEL, data_format);
                break;
            default:
                break;
            }
        }
        else //bz_chn == ANC0_BZ4
        {
            switch (route_from) {
            case ANC_BZ_ROUTE_I2S0_RX:
                reg_audio_matrix_i2s_anc0_err_sel(0) = (reg_audio_matrix_i2s_anc0_err_sel(0) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S1_RX:
                reg_audio_matrix_i2s_anc0_err_sel(1) = (reg_audio_matrix_i2s_anc0_err_sel(1) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_I2S2_RX:
                reg_audio_matrix_i2s_anc0_err_sel(2) = (reg_audio_matrix_i2s_anc0_err_sel(2) & (~FLD_MATRIX_I2S_ANC0_ERR1_SEL)) |
                                                       MASK_VAL(FLD_MATRIX_I2S_ANC0_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_768K:
                reg_audio_matrix_adc768_anc0_bz_ref_sel3 = (reg_audio_matrix_adc768_anc0_bz_ref_sel3 & (~FLD_MATRIX_ADC768_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC768_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_384K:
                reg_audio_matrix_adc384_anc0_bz_ref_sel2 = (reg_audio_matrix_adc384_anc0_bz_ref_sel2 & (~FLD_MATRIX_ADC384_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC384_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_192K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel1 = (reg_audio_matrix_adc96_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC192_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC192_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_96K:
                reg_audio_matrix_adc96_anc0_bz_ref_sel3 = (reg_audio_matrix_adc96_anc0_bz_ref_sel3 & (~FLD_MATRIX_ADC96_ANC0_BZ_ERR1_SEL)) |
                                                          MASK_VAL(FLD_MATRIX_ADC96_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_CODEC_48K:
                reg_audio_matrix_dmic768_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic768_anc0_bz_ref_sel1 & (~FLD_MATRIX_ADC48_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_ADC48_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_768K:
                reg_audio_matrix_dmic768_anc0_bz_err_sel = (reg_audio_matrix_dmic768_anc0_bz_err_sel & (~FLD_MATRIX_DMIC768_ANC0_BZ_ERR1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC768_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR1_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC384LL_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K_LL:
                reg_audio_matrix_dmic192ll_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic192ll_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR1_SEL)) |
                                                              MASK_VAL(FLD_MATRIX_DMIC192LL_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_384K:
                reg_audio_matrix_dmic384_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic384_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC384_ANC0_BZ_ERR1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC384_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_192K:
                reg_audio_matrix_dmic192_anc0_bz_ref_sel2 = (reg_audio_matrix_dmic192_anc0_bz_ref_sel2 & (~FLD_MATRIX_DMIC192_ANC0_BZ_ERR1_SEL)) |
                                                            MASK_VAL(FLD_MATRIX_DMIC192_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_96K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel1 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel1 & (~FLD_MATRIX_DMIC96_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC96_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_32K:
                reg_audio_matrix_dmic32_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic32_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC32_ANC0_BZ_ERR1_SEL)) |
                                                           MASK_VAL(FLD_MATRIX_DMIC32_ANC0_BZ_ERR1_SEL, data_format);
                break;
            case ANC_BZ_ROUTE_DMIC_16K_OR_48K:
                reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel3 = (reg_audio_matrix_dmic16k48k_anc0_bz_ref_sel3 & (~FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR1_SEL)) |
                                                               MASK_VAL(FLD_MATRIX_DMIC16K48K_ANC0_BZ_ERR1_SEL, data_format);
                break;
            default:
                break;
            }
        }
    }
}
/**
 * @brief      This function serves to select dac route source and data format.
 *
 * @param[in]  dac_chn     - dac channel.
 * @param[in]  route_from  - dac route from.
 * @param[in]  data_format - dac data format(route from fifo valid), others select DAC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_dac_route(audio_codec_output_select_e dac_chn, audio_matrix_dac_route_e route_from, audio_matrix_dac_format_e data_format)
{

    switch (dac_chn) {
    case AUDIO_DAC_A0:
        reg_audio_matrix_dac_sel = (reg_audio_matrix_dac_sel & (~FLD_MATRIX_DAC_L_SEL)) | route_from;
        break;
    case AUDIO_DAC_A1:
        /* AUDIO_DAC_A0 should also be set and set the same value with AUDIO_DAC_A1 even only using DAC_A2 */
    case AUDIO_DAC_A0_A1:
        reg_audio_matrix_dac_sel = MASK_VAL(FLD_MATRIX_DAC_L_SEL, route_from, FLD_MATRIX_DAC_R_SEL, route_from);
        break;
    default:
        break;
    }

    if (route_from == DAC_ROUTE_FIFO) {
        reg_audio_matrix_anc1_src_dma_sel = (reg_audio_matrix_anc1_src_dma_sel & (~FLD_MATRIX_DAC_DMA_SEL)) | MASK_VAL(FLD_MATRIX_DAC_DMA_SEL, data_format);
    }
}

/**
 * @brief      This function serves to select hac route source and data format.
 *
 * @param[in]  hac_chn     - hac channel.
 * @param[in]  route_from  - hac route from.
 * @param[in]  data_format - hac data format(route from i2s/adc valid), others select HAC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_hac_route(audio_hac_chn_e hac_chn, audio_matrix_hac_route_e route_from, audio_matrix_hac_format_e data_format)
{
    reg_audio_matrix_hac_tx_sel(hac_chn) = (reg_audio_matrix_hac_tx_sel(hac_chn) & (~FLD_MATRIX_HAC_TX_SEL)) | MASK_VAL(FLD_MATRIX_HAC_TX_SEL, route_from);
    unsigned char mask = FLD_MATRIX_I2S_RX_HAC_ODD_SEL;
    if ((hac_chn == HAC_CH0_EQ0) || (hac_chn == HAC_CH2_ASRC0))
    {
        mask = FLD_MATRIX_I2S_RX_HAC_EVEN_SEL;
    }
    if ((hac_chn == HAC_CH0_EQ0) || (hac_chn == HAC_CH1_EQ1) || (hac_chn == HAC_CH2_ASRC0) || (hac_chn == HAC_CH3_ASRC1))
    {
        switch (route_from) {
        case HAC_DATA_ROUTE_FIFO0:
        case HAC_DATA_ROUTE_FIFO1:
        case HAC_DATA_ROUTE_FIFO2:
        case HAC_DATA_ROUTE_FIFO3:
            if ((hac_chn == HAC_CH0_EQ0) || (hac_chn == HAC_CH1_EQ1))
            {
                if (hac_chn == HAC_CH0_EQ0)
                {
                    mask = FLD_MATRIX_HAC0_TX_DMA_SEL;
                }
                else
                {
                    mask = FLD_MATRIX_HAC1_TX_DMA_SEL;
                }
                reg_audio_matrix_hac01_tx_dma_sel(route_from) = ((reg_audio_matrix_hac01_tx_dma_sel(route_from) & (~mask)) |
                                                                               MASK_VAL(mask, data_format));
            }
            else
            {
                if (hac_chn == HAC_CH2_ASRC0)
                {
                    mask = FLD_MATRIX_HAC2_TX_DMA_SEL;
                }
                else
                {
                    mask = FLD_MATRIX_HAC3_TX_DMA_SEL;
                }
                reg_audio_matrix_hac23_tx_dma_sel(route_from) = ((reg_audio_matrix_hac23_tx_dma_sel(route_from) & (~mask)) |
                                                                               MASK_VAL(mask, data_format));
             }
            break;
        case HAC_DATA_ROUTE_I2S0_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S0, hac_chn) = (reg_audio_matrix_i2s_rx_hac_sel(I2S0, hac_chn) & (~mask)) |
                                                             MASK_VAL(mask, data_format);
            break;
        case HAC_DATA_ROUTE_I2S1_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S1, hac_chn) = (reg_audio_matrix_i2s_rx_hac_sel(I2S1, hac_chn) & (~mask)) |
                                                             MASK_VAL(mask, data_format);
            break;
        case HAC_DATA_ROUTE_I2S2_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S2, hac_chn) = (reg_audio_matrix_i2s_rx_hac_sel(I2S2, hac_chn) & (~mask)) |
                                                             MASK_VAL(mask, data_format);
            break;
        default:
            break;
        }
    }
    else //HAC_CH4_EQ2
    {
        switch (route_from) {
        case HAC_DATA_ROUTE_FIFO0:
            reg_audio_matrix_hac4_tx_dma0_sel = ((reg_audio_matrix_hac4_tx_dma0_sel & (~FLD_MATRIX_HAC4_TX_DMA0_SEL)) |
                                                MASK_VAL(FLD_MATRIX_HAC4_TX_DMA0_SEL, data_format));
            break;
        case HAC_DATA_ROUTE_FIFO1:
            reg_audio_matrix_hac4_tx_dma0_sel = ((reg_audio_matrix_hac4_tx_dma0_sel & (~FLD_MATRIX_HAC4_TX_DMA1_SEL)) |
                                                MASK_VAL(FLD_MATRIX_HAC4_TX_DMA1_SEL, data_format));
            break;
        case HAC_DATA_ROUTE_FIFO2:
            reg_audio_matrix_hac4_tx_dma23_sel = ((reg_audio_matrix_hac4_tx_dma23_sel & (~FLD_MATRIX_HAC4_TX_DMA2_SEL)) |
                                                 MASK_VAL(FLD_MATRIX_HAC4_TX_DMA2_SEL, data_format));
            break;
        case HAC_DATA_ROUTE_FIFO3:
            reg_audio_matrix_hac4_tx_dma23_sel = ((reg_audio_matrix_hac4_tx_dma23_sel & (~FLD_MATRIX_HAC4_TX_DMA3_SEL)) |
                                                 MASK_VAL(FLD_MATRIX_HAC4_TX_DMA3_SEL, data_format));
            break;
        case HAC_DATA_ROUTE_I2S0_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S0, HAC_CH1_EQ1) = (reg_audio_matrix_i2s_rx_hac_sel(I2S0, HAC_CH1_EQ1) & (~FLD_MATRIX_I2S_RX_HAC_ODD_SEL)) |
                                                             MASK_VAL(FLD_MATRIX_I2S_RX_HAC_ODD_SEL, data_format);
            break;
        case HAC_DATA_ROUTE_I2S1_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S1, HAC_CH1_EQ1) = (reg_audio_matrix_i2s_rx_hac_sel(I2S1, HAC_CH1_EQ1) & (~FLD_MATRIX_I2S_RX_HAC_ODD_SEL)) |
                                                             MASK_VAL(FLD_MATRIX_I2S_RX_HAC_ODD_SEL, data_format);
            break;
        case HAC_DATA_ROUTE_I2S2_RX:
            reg_audio_matrix_i2s_rx_hac_sel(I2S2, HAC_CH1_EQ1) = (reg_audio_matrix_i2s_rx_hac_sel(I2S2, HAC_CH1_EQ1) & (~mask)) |
                                                             MASK_VAL(mask, data_format);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief      This function serves to select side_tone route source and data format.
 *
 * @param[in]  sd_chn      - side_tone channel.
 * @param[in]  route_from  - side_tone route from.
 * @param[in]  data_format - side tone data format(route from fifo/i2s/adc valid), others select SIDE_TONE_DATA_FORMAT_INVALID.
 * @return     none
 */

void audio_matrix_set_side_tone_route(audio_side_tone_chn_e sd_chn, audio_matrix_side_tone_route_e route_from,
                                  audio_matrix_side_tone_format_e data_format)
{
    reg_audio_matrix_sdtn_sel(sd_chn) = (reg_audio_matrix_sdtn_sel(sd_chn) & (~FLD_MATRIX_SDTN_SEL)) | route_from;

    switch (route_from) {
    case SIDE_TONE_ROUTE_FIFO:
        reg_audio_matrix_sdtn_dma_sel(sd_chn) = (reg_audio_matrix_sdtn_dma_sel(sd_chn) & (~FLD_MATRIX_SDTN_DMA_SEL)) |
                                                MASK_VAL(FLD_MATRIX_SDTN_DMA_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_I2S0_RX:
        reg_audio_matrix_i2s_sdtn_sel(sd_chn) = (reg_audio_matrix_i2s_sdtn_sel(sd_chn) & (~FLD_MATRIX_I2S0_SDTN_SEL)) |
                                                MASK_VAL(FLD_MATRIX_I2S0_SDTN_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_I2S1_RX:
        reg_audio_matrix_i2s_sdtn_sel(sd_chn) = (reg_audio_matrix_i2s_sdtn_sel(sd_chn) & (~FLD_MATRIX_I2S1_SDTN_SEL)) |
                                                MASK_VAL(FLD_MATRIX_I2S1_SDTN_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_I2S2_RX:
        reg_audio_matrix_i2s_adc_sdtn_sel(sd_chn) = (reg_audio_matrix_i2s_adc_sdtn_sel(sd_chn) & (~FLD_MATRIX_I2S2_SDTN_SEL)) |
                                                    MASK_VAL(FLD_MATRIX_I2S2_SDTN_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_ADC0:
        reg_audio_matrix_i2s_adc_sdtn_sel(sd_chn) = (reg_audio_matrix_i2s_adc_sdtn_sel(sd_chn) & (~FLD_MATRIX_ADC0_SDTN_SEL)) |
                                                    MASK_VAL(FLD_MATRIX_ADC0_SDTN_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_ADC1:
        reg_audio_matrix_adc_sdtn_sel(sd_chn) = (reg_audio_matrix_adc_sdtn_sel(sd_chn) & (~FLD_MATRIX_ADC1_SDTN_SEL)) |
                                                MASK_VAL(FLD_MATRIX_ADC1_SDTN_SEL, data_format);
        break;
    case SIDE_TONE_ROUTE_ADC2:
        reg_audio_matrix_adc_sdtn_sel(sd_chn) = (reg_audio_matrix_adc_sdtn_sel(sd_chn) & (~FLD_MATRIX_ADC2_SDTN_SEL)) |
                                                MASK_VAL(FLD_MATRIX_ADC2_SDTN_SEL, data_format);
        break;
    default:
        break;
    }
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio pin interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio pin interface
 * @{
 */

/**
 * @brief      This function configures codec0 stream0 dmic pin.
 * @param[in]  dmic0_data - the data of dmic pin
 * @param[in]  dmic0_clk1 - the clk1 of dmic pin
 * @param[in]  dmic0_clk2 - the clk2 of dmic pin,if need not set clk2, please set GPIO_NONE_PIN.
 * @return     none
 */
void audio_dmic0_set_pin(gpio_func_pin_e dmic0_data, gpio_func_pin_e dmic0_clk1, gpio_func_pin_e dmic0_clk2)
{
    /* codec0 dmic0 data. */
    gpio_input_en((gpio_pin_e)dmic0_data);
    gpio_set_mux_function(dmic0_data, DMIC0_DAT_I);
    gpio_function_dis((gpio_pin_e)dmic0_data);
    /* codec0 dmic0 clock1. */
    gpio_set_mux_function(dmic0_clk1, DMIC0_CLK0);
    gpio_function_dis((gpio_pin_e)dmic0_clk1);
    /* codec0 dmic1 clock2. */
    if (dmic0_clk2 != GPIO_NONE_PIN) {
        gpio_set_mux_function(dmic0_clk2, DMIC0_CLK0);
        gpio_function_dis((gpio_pin_e)dmic0_clk2);
    }
}

/**
 * @brief      This function configures codec0 stream1 dmic pin.
 * @param[in]  dmic1_data - the data of dmic pin.
 * @param[in]  dmic1_clk1 - the clk1 of dmic pin.
 * @param[in]  dmic1_clk2 - the clk2 of dmic pin, if need not set clk2,please set GPIO_NONE_PIN.
 * @return     none
 */
void audio_dmic1_set_pin(gpio_func_pin_e dmic1_data, gpio_func_pin_e dmic1_clk1, gpio_func_pin_e dmic1_clk2)
{
    /* codec0 dmic1 data. */
    gpio_input_en((gpio_pin_e)dmic1_data);
    gpio_set_mux_function(dmic1_data, DMIC1_DAT_I);
    gpio_function_dis((gpio_pin_e)dmic1_data);
    /* codec0 dmic1 clock1. */
    gpio_set_mux_function(dmic1_clk1, DMIC1_CLK0);
    gpio_function_dis((gpio_pin_e)dmic1_clk1);
    /* codec0 dmic1 clock2. */
    if (dmic1_clk2 != GPIO_NONE_PIN) {
        gpio_set_mux_function(dmic1_clk2, DMIC1_CLK0);
        gpio_function_dis((gpio_pin_e)dmic1_clk2);
    }
}

/**
 * @brief      This function serves to configure i2s pin.
 * @param[in]  i2s_select - channel select.
 * @param[in]  config     - i2s config pin struct.
 * @return     none
 */
void audio_i2s_set_pin(i2s_select_e i2s_select, i2s_pin_config_t *config)
{
    gpio_input_en((gpio_pin_e)config->bclk_pin);
    gpio_set_mux_function((gpio_func_pin_e)config->bclk_pin, I2S0_BCK_IO + i2s_select * 6);
    gpio_function_dis((gpio_pin_e)config->bclk_pin);

    if (config->adc_lr_clk_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->adc_lr_clk_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->adc_lr_clk_pin, I2S0_LR0_IO + i2s_select * 6);
        gpio_function_dis((gpio_pin_e)config->adc_lr_clk_pin);
    }

    if (config->adc_dat_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->adc_dat_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->adc_dat_pin, I2S0_DAT0_IO + i2s_select * 6);
        gpio_function_dis((gpio_pin_e)config->adc_dat_pin);
    }

    if (config->dac_lr_clk_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->dac_lr_clk_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->dac_lr_clk_pin, I2S0_LR1_IO + i2s_select * 6);
        gpio_function_dis((gpio_pin_e)config->dac_lr_clk_pin);
    }

    if (config->dac_dat_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->dac_dat_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->dac_dat_pin, I2S0_DAT1_IO + i2s_select * 6);
        gpio_function_dis((gpio_pin_e)config->dac_dat_pin);
    }
}

/**
 * @brief      This function serves to configure spdif pin.
 * @param[in]  config     - spdif config pin struct.
 * @return     none
 */
void audio_spdif_set_pin(spdif_pin_config_t *config)
{
    if (config->spdif_rx_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->spdif_rx_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->spdif_rx_pin, SPDIF_RX);
        gpio_function_dis((gpio_pin_e)config->spdif_rx_pin);
    }

    if (config->spdif_tx_pin != GPIO_NONE_PIN) {
        gpio_input_en((gpio_pin_e)config->spdif_tx_pin);
        gpio_set_mux_function((gpio_func_pin_e)config->spdif_tx_pin, SPDIF_TX);
        gpio_function_dis((gpio_pin_e)config->spdif_tx_pin);
    }
}

/**********************************************************************************************************************
 *                                                Audio spdif interface                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio spdif interface
 * @{
 */
/**
 * @brief      This function serves to set spdif rx fs.
 * @param[in]  clk - audio pll clock
 * @return     none
 * @note       only support PLL1_AUDIO_CLK_169P344M and PLL1_AUDIO_CLK_158P0544M
 */
void audio_spdif_set_rx_fs(pll_audio_clk_e clk)
{
    (void)clk;
}
/**
 * @}
 */

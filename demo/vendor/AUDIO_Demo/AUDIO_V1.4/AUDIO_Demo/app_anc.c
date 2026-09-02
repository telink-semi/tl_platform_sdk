/********************************************************************************************************
 * @file    app_anc.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#if (AUDIO_MODE == ANC_DEMO)
#include "app_filter_data.h"
#include "app_sin_data.h"
#define ANC_HB_REF012ERR01_MODE                      (1)
#define ANC_HB_REF012ERR0_MODE                       (2)
#define ANC_HB_REF01ERR01_MODE                       (3)
#define ANC_HB_REF01ERR0_MODE                        (4)
#define ANC_HB_REF0ERR0_MODE                         (5)
#define ANC_HB_REF0ERR01_MODE                        (6)
#define ANC_FF_REF0_MODE                             (7)
#define ANC_FF_REF0WZ384_MODE                        (8)
#define ANC_HB_REF0WZ384ERR0CZ256_MODE               (9)
#define ANC_HB_REF012ERR01_MODE_PLUS_GAIN            (10)
#define ANC_HB_REF0WZ384ERR0CZ256_MODE_PLUS_GAIN     (11)
#define ANC_HB_REF012ERR01_MODE_PLUS_RESAMPLE        (12)
#define ANC_BZ_TEST                                  (13)
#define ANC_HB_REF0ERR0_MODE_PLUS_RESAMPLE           (14)
#define ANC_HB_REF012ERR01_MODE_PLUS_REFDC           (15)
#define ANC_FF_REF0_MODE_I2S                         (16)
#define ANC_FB_MODE                                  (17)
#define ANC_HB_REF0WZ384ERR0CZ256_MODE_PLUS_RESAMPLE (18)
#define ANC_FB_MODE_PLUS_RESAMPLE                    (19)
#define ANC_FF_REF0WZ384_MODE_PLUS_RESAMPLE          (20)
#define ANC_HB_REF012ERR0_MODE_PLUS_RESAMPLE         (21)
#define ANC_COFF_UPDATE                              (22)

#define ANC_MODE                                ANC_HB_REF012ERR01_MODE_PLUS_RESAMPLE

#define ANC_CHANNEL_SELECT                      ANC0

#define ANC_FS                                  384000

#define HAC_CHANNEL_SELECT       HAC_CH0_EQ0
#define HAC_EQ_CHANNEL_SELECT    HAC_EQ0
#define EQ_ASRC_FS               ANC_FS
#define USE_I2S                  0

int AUDIO_BUFFER_IN[2048];
int AUDIO_BUFFER_POST_PRE[4096];
int AUDIO_BUFFER_OUT0[2048];
int AUDIO_BUFFER_OUT1[2048];
int AUDIO_BUFFER_OUT2[2048];
int AUDIO_BUFFER_ZERO[2048];
int AUDIO_BUFFER_ONE[2048];
int AUDIO_BUFFER_BZ_OUT[2048*5];
int AUDIO_BUFFER_PRE[2048];
int AUDIO_BUFFER_POST[2048];

unsigned short audio_i2s_48k_config[5]      = {1, 14, 2, 64, 64}; // sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 2) / (64)  = 48KHz
unsigned short audio_i2s_48k_config_fpga[5] = {1, 7, 2, 64, 64};  // sampling rate = pll1_clk(default 86.016MHz) * (1 / 7) / (2 * 2) / (64)  = 48KHz

unsigned short audio_i2s_96k_config[5]      = {2, 14, 2, 64, 64}; // sampling rate = pll1_clk(default 172.032MHz) * (2 / 14) / (2 * 2) / (64)  = 96KHz
unsigned short audio_i2s_96k_config_fpga[5] = {2, 7, 2, 64, 64};  // sampling rate = pll1_clk(default 86.016MHz) * (2 / 7) / (2 * 2) / (64)  = 96KHz

unsigned short audio_i2s_192k_config[5]      = {2, 14, 1, 64, 64}; // sampling rate = pll1_clk(default 172.032MHz) * (2 / 14) / (2 * 1) / (64)  = 192KHz
unsigned short audio_i2s_192k_config_fpga[5] = {2, 7, 1, 64, 64};  // sampling rate = pll1_clk(default 86.016MHz) * (2 / 7) / (2 * 1) / (64)  = 192KHz

unsigned short audio_i2s_384k_config[5]      = {4, 14, 1, 64, 64}; // sampling rate = pll1_clk(default 172.032MHz) * (4 / 14) / (2 * 1) / (64)  = 192KHz
unsigned short audio_i2s_384k_config_fpga[5] = {2, 7, 0, 64, 64};  // sampling rate = pll1_clk(default 86.016MHz) * (2 / 7) / (1 * 1) / (64)  = 192KHz

volatile unsigned long gap0 = 0;
volatile unsigned long gap1 = 0;

volatile int ANC_PASS = 0;
volatile int offset = 0;


#define I2S_SEL                                 1//I2S0
#if (I2S_SEL == 0)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG2,
        .adc_lr_clk_pin = GPIO_FC_PG3,
        .adc_dat_pin    = GPIO_FC_PG4,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
    };
#elif  (I2S_SEL == 1)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PH4,
        .adc_lr_clk_pin = GPIO_FC_PH5,
        .adc_dat_pin    = GPIO_FC_PF3,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
    };
#else
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG7,
        .adc_lr_clk_pin = GPIO_FC_PH0,
        .adc_dat_pin    = GPIO_FC_PH1,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
#endif

unsigned short audio_i2s_192k_config_24slot[5] = {12, 112, 0, 48, 48};
unsigned short audio_i2s_384k_config_24slot[5] = {24, 112, 0, 48, 48};
unsigned short audio_i2s_768k_config_24slot[5] = {48, 112, 0, 48, 48};

int SaturateSigned(int iDataIn, int iBW)
{
    int iDataOut;

    int iUpper = (1 << (iBW - 1)) - 1;
    int iLower = -(1 << (iBW - 1));

    iDataOut = (iDataIn > iUpper) ? iUpper : ((iDataIn < iLower) ? iLower : iDataIn);

    return iDataOut;
}

void user_init(void)
{
    clock_pll_audio_init(PLL1_AUDIO_CLK_172P032M);
    audio_init(PLL1_AUDIO_CLK_172P032M);  //must configured first.

#if (ANC_MODE == ANC_FF_REF0_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref0[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_FF_REF0_MODE_I2S)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S_SEL,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_192k_config_fpga,
        .io_mode           = I2S_5_LINE_MODE,
    };

    // i2s config
    audio_i2s_config_init(&audio_i2s_config);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S0_RX + I2S_SEL, FIFO_RX_I2S_RX_CHN0_20_OR_24);  //rx fifo source select I2S_SEL
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA0); /* dis llp */


    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);

    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    //anc bz config
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ0, bz0_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ0, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_BZ_OUT);
    audio_rx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_OUT1, sizeof(AUDIO_BUFFER_OUT1));
    dma_llp_dis(DMA2); /* dis llp */

    audio_rx_dma_en(DMA1);
    audio_rx_dma_en(DMA2);

    audio_rx_dma_en(DMA0);

    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif (ANC_MODE == ANC_FF_REF0WZ384_MODE)
#if (USE_I2S)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S_SEL,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_192k_config_fpga,
        .io_mode           = I2S_5_LINE_MODE,
    };

    // i2s config
    audio_i2s_config_init(&audio_i2s_config);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S0_RX + I2S_SEL, FIFO_RX_I2S_RX_CHN0_20_OR_24);  //rx fifo source select I2S_SEL
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA0); /* dis llp */
#else
    unsigned short in_data_rate = 0;

    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
#endif
    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0WZ384);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wz2
#if (USE_I2S)
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
#else
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
#endif

    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    //anc bz config
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ0, bz0_iir);
#if (USE_I2S)
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ0, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_BZ_OUT);
    audio_rx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_OUT1, sizeof(AUDIO_BUFFER_OUT1));
    dma_llp_dis(DMA2); /* dis llp */
#endif

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
#if (USE_I2S)
    audio_rx_dma_en(DMA2);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#else
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (ff_ref0wz384[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#endif
#elif (ANC_MODE == ANC_HB_REF0ERR0_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref0err0[i] != AUDIO_BUFFER_OUT0[i])
        {
             ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF0ERR01_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);     //wcz0->wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wcz0->wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wcz0->wz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref0err01[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF0WZ384ERR0CZ256_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0WZ384ERR0CZ256);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref0wz384err0cz256[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF01ERR0_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF01ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref01err0[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF01ERR01_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF01ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref01err01[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR0_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref012err0[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR01_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref012err01[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR01_MODE_PLUS_GAIN)
#define DATA_LEFTSHIFT_FIRST                1
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, BIT(14)<<1, 0x0e - 1);//data<<2
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, BIT(14)>>1, 0x0e + 1);      //data>>2
#else
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, BIT(14)>>3, 0x0e + 3);//data>>2
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, BIT(14)<<3, 0x0e - 3);      //data<<2
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, BIT(14)<<1, 0x0e - 1);//data<<3
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, BIT(14)>>2, 0x0e + 1);     //wz1 data>>3
#else
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, BIT(14)>>3, 0x0e + 4);//data>>3
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, BIT(14)<<4, 0x0e - 3);       //wz1 data<<3
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, BIT(14)<<2, 0x0e - 2); //data<<4
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, BIT(14)>>2, 0x0e + 2);        //wz2 data>>4
#else
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, BIT(14)>>4, 0x0e + 4);//data>>4
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, BIT(14)<<4, 0x0e - 4);     //wz2 data<<4
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, BIT(14)<<2, 0x0e - 3);     //cz0 data<<5
#else
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, BIT(14)>>4, 0x0e + 5);     //cz0 data>>5
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, BIT(14)>>3, 0x0e + 3);     //cz3->cz1 data<<6
#else
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, BIT(14)<<5, 0x0e - 5);     //cz3->cz1 data>>6
#endif

    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (DATA_LEFTSHIFT_FIRST == 1)
        if (hb_ref012err01_gain_leftfirst[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (hb_ref012err01_gain_rightfirst[i] != AUDIO_BUFFER_OUT0[i])
#endif
        {
             ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF0WZ384ERR0CZ256_MODE_PLUS_GAIN)
#define DATA_LEFTSHIFT_FIRST                  1
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0WZ384ERR0CZ256);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, BIT(14)<<1, 0x0e - 1);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, BIT(14)>>1, 0x0e + 1);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, BIT(14)<<2, 0x0e - 1);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, BIT(14)>>1, 0x0e + 2);
#else
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, BIT(14)>>2, 0x0e + 3);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, BIT(14)<<3, 0x0e - 2);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, BIT(14)>>3, 0x0e + 3);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, BIT(14)<<3, 0x0e - 3);
#endif

    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wz2

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, BIT(14)<<2, 0x0e - 2);     //cz0
#else
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, BIT(14)>>3, 0x0e + 4);     //cz0
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

#if (DATA_LEFTSHIFT_FIRST == 1)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, BIT(14)>>2, 0x0e + 2);     //cz3->cz1
#else
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, BIT(14)<<4, 0x0e - 4);     //cz3->cz1
#endif
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (DATA_LEFTSHIFT_FIRST == 1)
        if (hb_ref0wz384err0cz256_gain_leftfirst[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (0 != AUDIO_BUFFER_OUT0[i]) // all 0 output
#endif
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR01_MODE_PLUS_RESAMPLE)
#define RZ_DATA_SHIFT               0 //test rz gain and gain_shift, 0:gain-0x4000,gain_shift-0xe; 1:gain-0x8000,gain_shift-0xd; 2:gain-0x2000,gain_shift-0xf;
#define Limiter_Test                1 // 0:wz_sum right shift 0, cz_sum right shift 0; 1:wz_sum right shift 1, cz_sum right shift 2; 2:wz_sum right shift 2, cz_sum right shift 3;2:wz_sum right shift 3, cz_sum right shift 1;
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    delay_us(1);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1
    delay_us(1);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2
    delay_us(1);

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0
    delay_us(1);

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    delay_us(1);
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1
    delay_us(1);


    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    delay_us(1);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    delay_us(1);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    delay_us(1);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    delay_us(1);
    audio_resample_rst_dis(ANC_CHANNEL_SELECT);
    audio_resample_rst_en(ANC_CHANNEL_SELECT);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);
#if (RZ_DATA_SHIFT == 0)
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x4000, 0x0e);     //rz0
    delay_us(1);
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ1, 0x4000, 0x0e);     //rz1
    delay_us(1);
    #if (Limiter_Test == 0)
        audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 0);
        audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 0);
    #elif (Limiter_Test == 1)
        audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 1);
        audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 2);
    #elif (Limiter_Test == 2)
        audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 2);
        audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 3);
    #else
        audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 3);
        audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 1);
    #endif
#elif (RZ_DATA_SHIFT == 1)
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x8000, 0x0d);     //rz0
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ1, 0x8000, 0x0d);     //rz1
#else
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x2000, 0x0f);     //rz0
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ1, 0x2000, 0x0f);     //rz1
#endif
    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz_iir);    //rz0
    delay_us(1);
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz0_fir);   //rz0
    delay_us(1);

    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ1, rz_iir);    //rz1
    delay_us(1);
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ1, rz1_fir);   //rz1
    delay_us(1);

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (RZ_DATA_SHIFT == 0)
    #if (Limiter_Test == 0)
        if (hb_ref012err01_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
    #elif (Limiter_Test == 1)
        if (hb_ref012err01_plus_resample_limiter_test1[i] != AUDIO_BUFFER_OUT0[i])
    #elif (Limiter_Test == 2)
        if (hb_ref012err01_plus_resample_limiter_test2[i] != AUDIO_BUFFER_OUT0[i])
    #else
        if (hb_ref012err01_plus_resample_limiter_test3[i] != AUDIO_BUFFER_OUT0[i])
    #endif
#elif (RZ_DATA_SHIFT == 1)
        if (hb_ref012err01_plus_resample_rz_gain1[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (hb_ref012err01_plus_resample_rz_gain2[i] != AUDIO_BUFFER_OUT0[i])
#endif
        {
            ANC_PASS = BIT(31)|i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_BZ_TEST)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S_SEL,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_192k_config_24slot,
        .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_I2S0_RX + I2S_SEL, ANC_ERR_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_ERR_ROUTE_I2S0_RX + I2S_SEL, ANC_ERR_I2S_CH0_20_OR_24_BIT);
    //anc bz config
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ0, bz0_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ0, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ1, bz1_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ1, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ2, bz2_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ2, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ3, bz3_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ3, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ4, bz4_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ4, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);

    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_BZ_OUT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_BZ_OUT, sizeof(AUDIO_BUFFER_BZ_OUT));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_I2S0_RX + I2S_SEL, FIFO_RX_I2S_RX_CHN0_20_OR_24);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif (ANC_MODE == ANC_HB_REF0ERR0_MODE_PLUS_RESAMPLE)
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_384K);

    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x4000, 0x0e);     //rz0
    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz_iir);    //rz0
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz0_fir);   //rz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_EQ0, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_ref0err0_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR01_MODE_PLUS_REFDC)
    unsigned short in_data_rate = 0;
#define REF_DC     0xffa5a5
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_dc(ANC_CHANNEL_SELECT, ANC0_REF0, REF_DC);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_dc(ANC_CHANNEL_SELECT, ANC0_REF1, REF_DC);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_dc(ANC_CHANNEL_SELECT, ANC0_REF2, REF_DC);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(2000);
    for (int i = 0; i < 2048; i++)
    {
#if (REF_DC == 0x5a5a)
        if (hb_ref012err01_dc5a5a[i] != AUDIO_BUFFER_OUT0[i])
#else //0xa5a5
        if (hb_ref012err01_dcffa5a5[i] != AUDIO_BUFFER_OUT0[i])
#endif
        {
             ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_FB_MODE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FB);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    reg_audio_anc_config(ANC_CHANNEL_SELECT) |= FLD_FB_MODE_INPUT_SEL;

    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz_iir);  //WCZ1->WZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz0_fir); //WCZ1->WZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz_iir);  //WCZ2->CZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz0_fir); //WCZ2->CZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x4000, 0x0e);     //cz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz_iir);  //WCZ0->CZ2,
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz0_fir); //WCZ0->CZ2,

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz_iir);  //WCZ3->CZ3
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz0_fir); //WCZ3->CZ3

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_POST_PRE_32BIT);
    audio_rx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_POST_PRE, sizeof(AUDIO_BUFFER_POST_PRE));
    dma_llp_dis(DMA2); /* dis llp */

    //hac config
    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);


    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_rx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (fb_mode[i] != AUDIO_BUFFER_OUT0[i])
            break;
        if(i == 2047)
            ANC_PASS = 3;
    }
    for (int i = 0; i < 2048; i++)
    {
        if (AUDIO_BUFFER_IN[i] != AUDIO_BUFFER_POST_PRE[2 * i + 1])
            break;
        if(i == 2047)
            ANC_PASS = 2;
    }
    for (int i = 0; i < 2048; i++)
    {
        if (fb_mode_cz0_out[i] != AUDIO_BUFFER_POST_PRE[2 * i])
            break;
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF0WZ384ERR0CZ256_MODE_PLUS_RESAMPLE)
#define  Limiter_Test                     3 // 0:wz_sum right shift 0, cz_sum right shift 0; 1:wz_sum right shift 1, cz_sum right shift 2; 2:wz_sum right shift 2, cz_sum right shift 3;2:wz_sum right shift 3, cz_sum right shift 1;
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

 //   int count = 1000;
    //anc config
    audio_anc_rst_dis(ANC_CHANNEL_SELECT);
    audio_resample_rst_dis(ANC_CHANNEL_SELECT);
    audio_anc_rst_en(ANC_CHANNEL_SELECT);
    audio_resample_rst_en(ANC_CHANNEL_SELECT);
    audio_anc_clk_dis(ANC_CHANNEL_SELECT);
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0WZ384ERR0CZ256);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);

    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    AAAAA_DEBUG1 = 1;
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    AAAAA_DEBUG1 = 2;
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    AAAAA_DEBUG1 = 3;
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    AAAAA_DEBUG1 = 4;
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    //anc resample config

    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);

    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x4000, 0x0e);     //rz0
    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz_iir);    //rz0
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz0_fir);   //rz0

#if (Limiter_Test == 0)
    audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 0);
    audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 0);
#elif (Limiter_Test == 1)
    audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 1);
    audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 2);
#elif (Limiter_Test == 2)
    audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 2);
    audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 3);
#else
    audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 3);
    audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 1);
#endif

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (Limiter_Test == 0)
        if (hb_ref0wz384err0cz256_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
#elif (Limiter_Test == 1)
        if (hb_ref0wz384err0cz256_plus_resample_limiter_test1[i] != AUDIO_BUFFER_OUT0[i])
#elif (Limiter_Test == 2)
        if (hb_ref0wz384err0cz256_plus_resample_limiter_test2[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (hb_ref0wz384err0cz256_plus_resample_limiter_test3[i] != AUDIO_BUFFER_OUT0[i])
#endif
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_FB_MODE_PLUS_RESAMPLE)//pass
#define CZ1_DATA_SHIFT                  0//test cz1 gain and gain_shift, 0:gain-0x4000,gain_shift-0xe; 1:gain-0x8000,gain_shift-0xd; 2:gain-0x2000,gain_shift-0xf;
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO0, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FB);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder2_mode(ANC_CHANNEL_SELECT, ANC_FB_ERR_MIC_IN_PLUS_RESAMPLE);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);
    audio_anc_set_hb_input_priority(ANC_CHANNEL_SELECT, ANC_HB_RESAMPLE_FIRST);

    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz_iir);  //WCZ1->WZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz0_fir); //WCZ1->WZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //CZ0_gain -> CZ0_gain
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz_iir);  //WCZ2->CZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz0_fir); //WCZ2->CZ0

#if (CZ1_DATA_SHIFT == 0)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x4000, 0x0e);     //CZ2_gain -> CZ1_gain
#elif (CZ1_DATA_SHIFT == 1)
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x8000, 0x0d);     //CZ2_gain -> CZ1_gain
#else
    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x2000, 0x0f);     //CZ2_gain -> CZ1_gain
#endif
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz_iir);  //WCZ0->CZ2,
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz0_fir); //WCZ0->CZ2,


    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //CZ3_gain -> CZ3_gain
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz_iir);  //WCZ3->CZ3
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz0_fir); //WCZ3->CZ3

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_EQ0, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO3, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_POST_PRE_32BIT);
    //audio_matrix_set_rx_fifo_route(FIFO3, FIFO_RX_ROUTE_EQ1, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_POST_PRE, sizeof(AUDIO_BUFFER_POST_PRE));
    dma_llp_dis(DMA3); /* dis llp */


    audio_rx_dma_en(DMA1);
    audio_rx_dma_en(DMA3);
    audio_tx_dma_en(DMA0);
    audio_tx_dma_en(DMA2);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (CZ1_DATA_SHIFT == 0)
        if (hb_mode_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
#elif (CZ1_DATA_SHIFT == 1)
        if (hb_mode_plus_resample_cz1_gain1[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (hb_mode_plus_resample_cz1_gain2[i] != AUDIO_BUFFER_OUT0[i])
#endif
            while(1);
        if(i == 2047)
            ANC_PASS = 3;
    }
    for(int i = 0; i < 2048; i++)
    {
        AUDIO_BUFFER_POST[i] = AUDIO_BUFFER_POST_PRE[2 * i];
        AUDIO_BUFFER_PRE[i] =  AUDIO_BUFFER_POST_PRE[2 * i + 1];
    }
    for (int i = 0; i < 2048; i++)
    {
#if (CZ1_DATA_SHIFT == 0)
        if (hb_mode_plus_resample_add2_in[i] != AUDIO_BUFFER_PRE[i])
#elif (CZ1_DATA_SHIFT == 1)
        if (hb_mode_plus_resample_add2_in_cz1_gain1[i] != AUDIO_BUFFER_PRE[i])
#else
        if (hb_mode_plus_resample_add2_in_cz1_gain2[i] != AUDIO_BUFFER_PRE[i])
#endif
            while(1);
        if(i == 2047)
            ANC_PASS = 2;
    }
    for (int i = 0; i < 2048; i++)
    {
#if (CZ1_DATA_SHIFT == 0)
        if (hb_mode_plus_resample_cz0_out[i] != AUDIO_BUFFER_POST[i])
#elif (CZ1_DATA_SHIFT == 1)
        if (hb_mode_plus_resample_cz0_out_cz1_gain1[i] != AUDIO_BUFFER_POST[i])
#else
        if (hb_mode_plus_resample_cz0_out_cz1_gain2[i] != AUDIO_BUFFER_POST[i])
#endif
            while(1);
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_FF_REF0WZ384_MODE_PLUS_RESAMPLE)
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0WZ384);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);   //wz0

    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    delay_us(1);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1
    delay_us(1);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    delay_us(1);
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2
    delay_us(1);

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (ff_ref0wz384_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = BIT(31) | i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_HB_REF012ERR0_MODE_PLUS_RESAMPLE)
#define Resample_Mode     3 //0:48k->192k; 1:48k->384k; 2:96k->192k; 3:96k->384k
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_eq0 = 0;
    unsigned short in_data_rate_eq1 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
#if (Resample_Mode == 0)
    in_data_rate_eq0 = (43008000 / 192000) - 1;
    in_data_rate_eq1 = (43008000 / 48000) - 1;
#elif (Resample_Mode == 1)
    in_data_rate_eq0 = (43008000 / 384000) - 1;
    in_data_rate_eq1 = (43008000 / 48000) - 1;
#elif (Resample_Mode == 2)
    in_data_rate_eq0 = (43008000 / 192000) - 1;
    in_data_rate_eq1 = (43008000 / 96000) - 1;
#else
    in_data_rate_eq0 = (43008000 / 384000) - 1;
    in_data_rate_eq1 = (43008000 / 96000) - 1;
#endif
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_eq0);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_eq1);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
#if (Resample_Mode == 0)
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);
#elif (Resample_Mode == 1)
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_384K);
#elif (Resample_Mode == 2)
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_96K, ANC_RESAMPLE_OUT_FS_192K);
#else
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_96K, ANC_RESAMPLE_OUT_FS_384K);
#endif

    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x4000, 0x0e);     //rz0
    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz_iir);    //rz0
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz0_fir);   //rz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
#if (Resample_Mode == 0)
        if (hb_ref012err0_plus_resample[i] != AUDIO_BUFFER_OUT0[i])
#elif (Resample_Mode == 1)
        if (hb_ref012err0_plus_resample_test1[i] != AUDIO_BUFFER_OUT0[i])
#elif (Resample_Mode == 2)
        if (hb_ref012err0_plus_resample_test2[i] != AUDIO_BUFFER_OUT0[i])
#else
        if (hb_ref012err0_plus_resample_test3[i] != AUDIO_BUFFER_OUT0[i])
#endif
            break;
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_MODE == ANC_COFF_UPDATE)
#define ANC_MODE_HB_REF012ERR01_COFF_UPDATE               1
#define ANC_MODE_HB_REF012ERR0_COFF_UPDATE                2
#define ANC_MODE_HB_REF01ERR01_COFF_UPDATE                3
#define ANC_MODE_HB_REF01ERR0_COFF_UPDATE                 4
#define ANC_MODE_HB_REF0ERR0_COFF_UPDATE                  5
#define ANC_MODE_HB_REF0ERR01_COFF_UPDATE                 6
#define ANC_MODE_FF_REF0_COFF_UPDATE                      7
#define ANC_MODE_FF_REF0WZ384_COFF_UPDATE                 8
#define ANC_MODE_HB_REF0WZ384ERR0CZ256_COFF_UPDATE        9
#define ANC_MODE_FB_COFF_UPDATE                           10
#define ANC_MODE_RZ_UPDATE                                11
#define ANC_MODE_FB_RESAMPLE_UPDATE                       12
#define ANC_MODE_BZ_UPDATE                                13

#define ANC_COFF_UPDATE_MODE                              ANC_MODE_FB_RESAMPLE_UPDATE

#if (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF012ERR01_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(2);
    unsigned long t1 = stimer_get_tick();
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_IIR_START;
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b0(ANC_CHANNEL_SELECT, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][4];
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_FIR_START;
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1280 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8) |
                                                                BIT(4) | BIT(4 + 8);
    unsigned long t2 = stimer_get_tick();
    gap0 = t2 - t1;
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref012err01[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(SaturateSigned(AUDIO_BUFFER_IN[i]*3,24) + SaturateSigned(AUDIO_BUFFER_IN[i]*2,24),24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }


    t1 = stimer_get_tick();
    delay_us(100);
    t2 = stimer_get_tick();
    gap1 = t2 - t1;
    printf("%d,%lu,%lu\n",offset,gap0,gap1);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF012ERR0_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(2);
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref012err0[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(SaturateSigned(AUDIO_BUFFER_IN[i]*3,24) + AUDIO_BUFFER_IN[i],24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF01ERR01_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF01ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);

    delay_ms(2);
   // while(1){};
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_IIR_START;
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b0(ANC_CHANNEL_SELECT, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][4];
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_FIR_START;
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1280 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | FLD_ANC_CZ3_IIR_DONE | BIT(4 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref01err01[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(SaturateSigned(AUDIO_BUFFER_IN[i]*2,24)*2,24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF01ERR0_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF01ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);

    delay_ms(2);
   // while(1){};
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        //reg_audio_anc_iir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref01err0[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(SaturateSigned(AUDIO_BUFFER_IN[i]*2,24)+AUDIO_BUFFER_IN[i],24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF0ERR0_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0ERR0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);

    delay_ms(2);
   // while(1){};
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        //reg_audio_anc_iir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref0err0[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if ((SaturateSigned(AUDIO_BUFFER_IN[i]*2,24)) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF0ERR01_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);     //wcz0->wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wcz0->wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wcz0->wz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);

    delay_ms(2);
   // while(1){};
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_IIR_START;
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b0(ANC_CHANNEL_SELECT, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][4];
        }
        //reg_audio_anc_iir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_FIR_START;
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1280 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(4) | BIT(4 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref0err01[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(AUDIO_BUFFER_IN[i]+SaturateSigned(AUDIO_BUFFER_IN[i]*2,24),24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_FF_REF0_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);

    delay_ms(2);
    //while(1){};
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //void audio_anc_update_wcz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed int data[12][5])
    unsigned long t1 = stimer_get_tick();
    {
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        //reg_audio_anc_iir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //void audio_anc_update_wcz_fir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed short *data)
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = (BIT(ANC0_WCZ0)) | BIT(ANC0_WCZ0 + 8);
    unsigned long t2 = stimer_get_tick();
    unsigned long t3 = stimer_get_tick();
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    //audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x8000, 0x0e);
    unsigned long t4 = stimer_get_tick();
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref0[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }

        if (offset != 0)
        {
            if (AUDIO_BUFFER_IN[i] != AUDIO_BUFFER_OUT0[i])
            {
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
gap0 = t2 - t1;
    printf("%d\n",offset);

    gap1 = t4 - t3;
    printf("%lu %lu\n",gap0,gap1);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_FF_REF0WZ384_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0WZ384);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wz2

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);

    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(2);
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (ff_ref0wz384[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (AUDIO_BUFFER_IN[i] != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_HB_REF0WZ384ERR0CZ256_COFF_UPDATE)
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0WZ384ERR0CZ256);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA3);
    delay_ms(2);
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_IIR_START;
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b0(ANC_CHANNEL_SELECT, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_b2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_cz3_iir_a2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][4];
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_FIR_START;
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1280 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8) |
                                                                BIT(4) | BIT(4 + 8);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (offset == 0)
        {
            if (hb_ref0wz384err0cz256[i] != AUDIO_BUFFER_OUT0[i])
            {
                offset = i;
            }
        }
        if (offset != 0)
        {
            if (SaturateSigned(AUDIO_BUFFER_IN[i]*2,24) != AUDIO_BUFFER_OUT0[i])
            {
                AAAAA_DEBUG = i;
                break;
            }
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
    printf("%d\n",offset);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_FB_COFF_UPDATE)
#define FB_UPDATE_MODE            1  //1:update cz3 iir to 0
    unsigned short in_data_rate = 0;
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ0, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA3); /* dis llp */
    // hac config
    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FB);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    reg_audio_anc_config(ANC_CHANNEL_SELECT) |= FLD_FB_MODE_INPUT_SEL;

    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz_iir);  //WCZ1->WZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz0_fir); //WCZ1->WZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz_iir);  //WCZ2->CZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz0_fir); //WCZ2->CZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x4000, 0x0e);     //cz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz_iir);  //WCZ0->CZ2,
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz0_fir); //WCZ0->CZ2,

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz_iir);  //WCZ3->CZ3
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz0_fir); //WCZ3->CZ3

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_POST_PRE_32BIT);
    audio_rx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_POST_PRE, sizeof(AUDIO_BUFFER_POST_PRE));
    dma_llp_dis(DMA2); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_rx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);
    delay_ms(2);
#if 1
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 12; i++)
        {
#if (FB_UPDATE_MODE == 0)
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
#else
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = 0;
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = 0;
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = 0;
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = 0;
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = 0;
#endif
        }
    }
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
    //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
    {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
        for (unsigned char i = 0; i < 16; i++)
        {
            for(unsigned char j = 0; j < 4; j++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
            }
        }
        //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8)
                                                                ;
#endif
    delay_ms(1000);
    for (int k = 0; k < 2048; k++)
    {
        AUDIO_BUFFER_POST[k] = AUDIO_BUFFER_POST_PRE[2 * k];
    }

    int i = 0;
    for (; i < 2048; i++)
    {
        if (fb_mode[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS |= 0x40;
            break;
        }
    }
    for (int j = 0; j < i; j++)
    {
        if (AUDIO_BUFFER_IN[j] != AUDIO_BUFFER_POST_PRE[2 * j + 1])
        {
            ANC_PASS |= 0x20;
            while(1);
        }
    }
    for (int j = 0; j < i; j++)
    {
        if (fb_mode_cz0_out[j] != AUDIO_BUFFER_POST_PRE[2 * j])
        {
            ANC_PASS |= 0x10;
            break;
        }
    }
    i++;
    offset = i;
    for (int j = i; j < 2048; j++)
    {
        if (fb_mode_bypass_mode1[j] != AUDIO_BUFFER_OUT0[j])
            break;
        if (j == 2047)
            ANC_PASS |= 4;
    }
    for (int j = i; j < 2048; j++)
    {
        if (AUDIO_BUFFER_IN[j] != AUDIO_BUFFER_POST_PRE[2 * j + 1])
            break;
        if (j == 2047)
            ANC_PASS |= 2;
    }
    for (int j = i; j < 2048; j++)
    {
        if (fb_mode_cz0_out_bypass_mode1[i] != AUDIO_BUFFER_POST[i])
            break;
        if (j == 2047)
            ANC_PASS |= 1;
    }
    printf ("%d %d\n",offset,ANC_PASS);
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_RZ_UPDATE)
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_EQ1, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT2, sizeof(AUDIO_BUFFER_OUT2));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO3, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_ZERO, sizeof(AUDIO_BUFFER_ZERO));
    dma_llp_dis(DMA3); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
        AUDIO_BUFFER_OUT0[i] = 0;
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);
    audio_resample_rst_dis(ANC_CHANNEL_SELECT);
    reg_audio_anc_config1(ANC_CHANNEL_SELECT) |= FLD_ANC_SOFT_RST_EN;


    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ0, 0x4000, 0x0e);     //rz0
    audio_anc_set_rz_gain(ANC_CHANNEL_SELECT, ANC0_RZ1, 0x4000, 0x0e);     //rz1
    audio_anc_set_wz_sum_right_shift(ANC_CHANNEL_SELECT, 0);
    audio_anc_set_cz_sum_right_shift(ANC_CHANNEL_SELECT, 0);

    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz_iir);    //rz0
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ0, rz0_fir);   //rz0

    audio_anc_update_rz_iir_coef(ANC_CHANNEL_SELECT, ANC0_RZ1, rz_iir);    //rz1
    audio_anc_update_rz_fir_coef(ANC_CHANNEL_SELECT, ANC0_RZ1, rz1_fir);   //rz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_REF_ROUTE_EQ0 + HAC_CHANNEL_SELECT, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_resample_rst_en(ANC_CHANNEL_SELECT);
    reg_audio_anc_config1(ANC_CHANNEL_SELECT) &= ~FLD_ANC_SOFT_RST_EN;
    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);
    audio_tx_dma_en(DMA3);


    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);

    delay_ms(5);
 #if 1
    {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
            for (unsigned char i = 0; i < 12; i++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
            for (unsigned char i = 0; i < 12; i++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][0];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][1];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][2];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][3];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ2, i) = iir_bypass[i][4];
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
            for (unsigned char i = 0; i < 12; i++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][0];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][1];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][2];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][3];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ1, i) = iir_bypass[i][4];
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
            for (unsigned char i = 0; i < 12; i++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][0];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][1];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][2];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][3];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ3, i) = iir_bypass[i][4];
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_IIR_START;
            for (unsigned char i = 0; i < 12; i++)
            {
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_cz3_iir_b0(ANC_CHANNEL_SELECT, i) = iir_bypass[i][0];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_cz3_iir_b1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][1];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_cz3_iir_b2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][2];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_cz3_iir_a1(ANC_CHANNEL_SELECT, i) = iir_bypass[i][3];
                while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                reg_audio_anc_cz3_iir_a2(ANC_CHANNEL_SELECT, i) = iir_bypass[i][4];
            }
        }
        //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0
        //audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //cz0
        {
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
            for (unsigned char i = 0; i < 16; i++)
            {
                for(unsigned char j = 0; j < 4; j++)
                {
                    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                    REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
                }
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ2);
            for (unsigned char i = 0; i < 16; i++)
            {
                for(unsigned char j = 0; j < 4; j++)
                {
                    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                    REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ2) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
                }
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ1);
            for (unsigned char i = 0; i < 16; i++)
            {
                for(unsigned char j = 0; j < 4; j++)
                {
                    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                    REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ1) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
                }
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ3);
            for (unsigned char i = 0; i < 16; i++)
            {
                for(unsigned char j = 0; j < 4; j++)
                {
                    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                    REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ3) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
                }
            }
            delay_us(1);
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = FLD_ANC_CZ3_FIR_START;
            for (unsigned char i = 0; i < 16; i++)
            {
                for(unsigned char j = 0; j < 4; j++)
                {
                    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
                    REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1280 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
                }
            }
            //reg_audio_anc_fir_done(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        }

     //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
     //audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //cz0
     {
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_RZ0_IIR_START;
         for (unsigned char i = 0; i < 12; i++)
         {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b0(ANC_CHANNEL_SELECT, ANC0_RZ0, i) = iir_bypass[i][0];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b1(ANC_CHANNEL_SELECT, ANC0_RZ0, i) = iir_bypass[i][1];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b2(ANC_CHANNEL_SELECT, ANC0_RZ0, i) = iir_bypass[i][2];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_a1(ANC_CHANNEL_SELECT, ANC0_RZ0, i) = iir_bypass[i][3];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_a2(ANC_CHANNEL_SELECT, ANC0_RZ0, i) = iir_bypass[i][4];
         }
         delay_us(1);
         while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
         reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = FLD_ANC_RZ1_IIR_START;
         for (unsigned char i = 0; i < 12; i++)
         {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b0(ANC_CHANNEL_SELECT, ANC0_RZ1, i) = iir_bypass[i][0];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b1(ANC_CHANNEL_SELECT, ANC0_RZ1, i) = iir_bypass[i][1];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_b2(ANC_CHANNEL_SELECT, ANC0_RZ1, i) = iir_bypass[i][2];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_a1(ANC_CHANNEL_SELECT, ANC0_RZ1, i) = iir_bypass[i][3];
             while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             reg_audio_anc_rz_iir_a2(ANC_CHANNEL_SELECT, ANC0_RZ1, i) = iir_bypass[i][4];
         }
     }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(5 + ANC0_RZ0);
        for (unsigned char i = 0; i < 16; i++)
        {
         for(unsigned char j = 0; j < 4; j++)
         {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
             REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1480 + 0x200 * ANC0_RZ0 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
         }
        }
        delay_us(1);
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(5 + ANC0_RZ1);
        for (unsigned char i = 0; i < 16; i++)
        {
          for(unsigned char j = 0; j < 4; j++)
          {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
              REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0x1480 + 0x200 * ANC0_RZ1 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
          }
        }
     while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(ANC0_WCZ1) | BIT(ANC0_WCZ2) | BIT(ANC0_WCZ3) | BIT(ANC0_WCZ0 + 8) | BIT(ANC0_WCZ1 + 8) | BIT(ANC0_WCZ2 + 8) | BIT(ANC0_WCZ3 + 8) |
                                                                        BIT(4) | BIT(4 + 8) | BIT(5 + ANC0_RZ0) | BIT(5 + ANC0_RZ1) | BIT(13 + ANC0_RZ0) | BIT(13 + ANC0_RZ1);
#endif
    delay_ms(1000);
    for (int i = 0; i < 2048; i++)
    {
        if (hb_rz_update_before[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = i;
            offset = i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }

    for (int i = offset + 1; i < 2048; i++)
    {
        if (hb_rz_update_after[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS = i;
            offset = i;
            break;
        }
        if(i == 2047)
            ANC_PASS = 1;
    }
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_FB_RESAMPLE_UPDATE)
    int resample_hb1_coff[21] = {-463,1168,-2563,4960,-8808,14673,-23252,35383,-52075,74549,-104325,143386,-194500,261864,-352495,479510,-671043,1000613,-1738887,5326482,8388608};//default
    int resample_hb2_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    int resample_hb3_coff[7] = {-3579,31041,-142644,469196,-1333012,5173296,8388608};//default
    short resample_droop_coff[5] = {1,-4,12,-58,2100};
    unsigned short in_data_rate_192 = 0;
    unsigned short in_data_rate_48 = 0;
    //comment this code in audio_init BM_SET(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
    audio_matrix_set_hac_route(HAC_CH0_EQ0, HAC_DATA_ROUTE_FIFO0, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_ZERO, sizeof(AUDIO_BUFFER_ZERO));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_hac_route(HAC_CH1_EQ1, HAC_DATA_ROUTE_FIFO2, HAC_EQ_20_OR_24_BIT);
    audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA2); /* dis llp */

    // hac config
    in_data_rate_192 = (43008000 / 192000 )-1;
    in_data_rate_48  = (43008000 / 48000 )-1;
    audio_hac_set_in_data_rate(HAC_CH0_EQ0, in_data_rate_192);
    audio_hac_set_in_data_rate(HAC_CH1_EQ1, in_data_rate_48);

    for(int i=0;i<2048;i++) {
        AUDIO_BUFFER_IN[i] = sin_48k_stereo_24bit[i%96];
    }

    audio_hac_bypass_eq_asrc(HAC_CH0_EQ0,1);
    audio_hac_eq_config_en(HAC_EQ0);
    audio_hac_asrc_ch_en(HAC_CH0_EQ0,1);

    audio_hac_bypass_eq_asrc(HAC_CH1_EQ1,1);
    audio_hac_eq_config_en(HAC_EQ1);
    audio_hac_asrc_ch_en(HAC_CH1_EQ1,1);

    audio_hac_set_data_dst(HAC_CH0_EQ0, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH0_EQ0, HAC_INPUT_DATA_MCU);
    audio_hac_set_data_dst(HAC_CH1_EQ1, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CH1_EQ1, HAC_INPUT_DATA_MCU);

    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FB);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder2_mode(ANC_CHANNEL_SELECT, ANC_FB_ERR_MIC_IN_PLUS_RESAMPLE);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_RESAMPLE_FIRST);
    audio_anc_set_hb_input_priority(ANC_CHANNEL_SELECT, ANC_HB_RESAMPLE_FIRST);

    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz_iir);  //WCZ1->WZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, wz0_fir); //WCZ1->WZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //CZ0_gain -> CZ0_gain
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz_iir);  //WCZ2->CZ0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, cz0_fir); //WCZ2->CZ0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ1, 0x4000, 0x0e);     //CZ2_gain -> CZ1_gain
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz_iir);  //WCZ0->CZ2,
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, cz0_fir); //WCZ0->CZ2,

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //CZ3_gain -> CZ3_gain
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz_iir);  //WCZ3->CZ3
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, cz0_fir); //WCZ3->CZ3

    //anc resample config
    audio_anc_update_hb1_coef(ANC0, resample_hb1_coff);
    audio_anc_update_hb2_coef(ANC0, resample_hb2_coff);
    audio_anc_update_hb3_coef(ANC0, resample_hb3_coff);
    audio_anc_update_droop_coef(ANC0, resample_droop_coff);
    audio_anc_set_resample_in_out_fs(ANC0, ANC_RESAMPLE_OTHERS_DECISION_FS, ANC_RESAMPLE_IN_FS_48K, ANC_RESAMPLE_OUT_FS_192K);
    audio_resample_rst_dis(ANC_CHANNEL_SELECT);
    reg_audio_anc_config1(ANC_CHANNEL_SELECT) |= FLD_ANC_SOFT_RST_EN;

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_EQ0, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_src_route(ANC_CHANNEL_SELECT, ANC0_SRC0, ANC_SRC_ROUTE_EQ1, ANC_SRC_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_SPEAKER_OUT);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_OUT0, sizeof(AUDIO_BUFFER_OUT0));
    dma_llp_dis(DMA1); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO3, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_POST_PRE_32BIT);
    //audio_matrix_set_rx_fifo_route(FIFO3, FIFO_RX_ROUTE_EQ1, FIFO_RX_HAC_EQ_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(FIFO3, DMA3, (unsigned short *)AUDIO_BUFFER_POST_PRE, sizeof(AUDIO_BUFFER_POST_PRE));
    dma_llp_dis(DMA3); /* dis llp */
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    audio_resample_rst_en(ANC_CHANNEL_SELECT);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_config1(ANC_CHANNEL_SELECT) &= ~FLD_ANC_SOFT_RST_EN;
    BM_SET(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
    audio_rx_dma_en(DMA1);
    audio_rx_dma_en(DMA3);
    audio_tx_dma_en(DMA0);
    audio_tx_dma_en(DMA2);

    reg_audio_clk_en_1 |= (FLD_CLK_EQ0_EN | FLD_CLK_EQ1_EN);
    reg_audio_hac_mux_sel &= ~(FLD_HAC_EQ0_INPUT_ROUTE | FLD_HAC_EQ1_INPUT_ROUTE);

    delay_ms(5);
 #if 1
    {
        while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_iir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
        for (unsigned char i = 0; i < 12; i++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b0(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][0];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][1];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_b2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][2];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a1(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][3];
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            reg_audio_anc_wcz_iir_a2(ANC_CHANNEL_SELECT, ANC0_WCZ0, i) = iir_bypass[i][4];
        }
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_fir_start(ANC_CHANNEL_SELECT) = BIT(ANC0_WCZ0);
    for (unsigned char i = 0; i < 16; i++)
    {
        for(unsigned char j = 0; j < 4; j++)
        {
            while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
            REG_ADDR32(REG_AUDIO_ANC_COEF(ANC_CHANNEL_SELECT) + 0xa80 + (ANC0_WCZ0) * 0x200 + i * 0x20 + j * 4) = ((fir_bypass[i + j * 32 + 16] << 16) & 0xFFFF0000) | (fir_bypass[i + j * 32] & 0xFFFF);
        }
    }
    delay_us(1);
    while(reg_audio_anc_config1(ANC_CHANNEL_SELECT) & FLD_ANC_FSM_STATUS){};
    REG_ADDR16(REG_AUDIO_ANC_BASE(ANC_CHANNEL_SELECT) + 0x9e) = BIT(ANC0_WCZ0) | BIT(8 + ANC0_WCZ0);

#endif
    delay_ms(1000);
    for(int i = 0; i < 2048; i++)
    {
        AUDIO_BUFFER_POST[i] = AUDIO_BUFFER_POST_PRE[2 * i];
        AUDIO_BUFFER_PRE[i] =  AUDIO_BUFFER_POST_PRE[2 * i + 1];
    }
    for (int i = 0; i < 2048; i++)
    {

        if (hb_mode_plus_resample_add2_in_updatecz2_before[i] != AUDIO_BUFFER_PRE[i])
        {
            offset = i;
            break;
        }
        if(i == 2047)
            ANC_PASS |= 8;
    }
    for (int i = 0; i < offset; i++)
    {
        if (hb_mode_plus_resample_updatecz2_before[i] != AUDIO_BUFFER_OUT0[i])
        {
            ANC_PASS |= BIT(31);
            break;
        }
        if(i == 2047)
            ANC_PASS |= 4;
    }
    for (int i = 0; i < offset; i++)
    {
        if (hb_mode_plus_resample_cz0_out_updatecz2_before[i] != AUDIO_BUFFER_POST[i])
        {
            ANC_PASS |= BIT(30);
            break;
        }
        if(i == 2047)
            ANC_PASS |= 2;
    }

    for (int i = offset; i < 2048; i++)
    {
        if (hb_mode_plus_resample_add2_in_updatecz2_after[i] != AUDIO_BUFFER_PRE[i])
        {
            break;
        }
        if(i == 2047)
            ANC_PASS |= 1;
    }
#elif (ANC_COFF_UPDATE_MODE == ANC_MODE_BZ_UPDATE)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S_SEL,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_192k_config_24slot,
        .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF012ERR01);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz0_fir); //wz0

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);     //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz_iir);  //wcz2->wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, wz1_fir); //wcz2->wz1

    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF2, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);     //wz2
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz_iir);  //wcz3->wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, wz2_fir); //wcz3->wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz_iir);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, cz0_fir); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, cz_iir);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, cz1_fir);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF1, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF2, ANC_REF_ROUTE_I2S0_RX + I2S_SEL, ANC_REF_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_I2S0_RX + I2S_SEL, ANC_ERR_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR1, ANC_ERR_ROUTE_I2S0_RX + I2S_SEL, ANC_ERR_I2S_CH0_20_OR_24_BIT);
    //anc bz config
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ0, bz0_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ0, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ1, bz1_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ1, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ2, bz2_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ2, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ3, bz3_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ3, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ4, bz4_iir);
    audio_matrix_set_anc_bz_route(ANC_CHANNEL_SELECT, ANC0_BZ4, ANC_BZ_ROUTE_I2S0_RX + I2S_SEL, ANC_BZ_I2S_CH0_20_OR_24_BIT);

    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_ANC0, FIFO_RX_ANC_BZ_OUT);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_BZ_OUT, sizeof(AUDIO_BUFFER_BZ_OUT));
    dma_llp_dis(DMA0); /* dis llp */
    audio_matrix_set_rx_fifo_route(FIFO1, FIFO_RX_ROUTE_I2S0_RX + I2S_SEL, FIFO_RX_I2S_RX_CHN0_20_OR_24);
    audio_rx_dma_chain_init(FIFO1, DMA1, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    dma_llp_dis(DMA1); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_rx_dma_en(DMA1);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
    delay_ms(5);

    //anc bz update config
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ0, iir_bypass);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ1, iir_bypass);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ2, iir_bypass);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ3, iir_bypass);
    audio_anc_update_bz_iir_coef(ANC_CHANNEL_SELECT, ANC0_BZ4, iir_bypass);



#endif

#endif
}
void main_loop(void)
{

}
#endif
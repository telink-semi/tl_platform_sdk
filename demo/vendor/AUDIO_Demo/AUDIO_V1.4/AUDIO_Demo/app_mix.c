/********************************************************************************************************
 * @file    app_mix.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#if (AUDIO_MODE == AUDIO_MIX_DEMO)
#include "app_filter_data.h"
#define DMIC0_INPUT_TO_BUF_TO_I2S     (1)  /* data route: codec0 dmic -> i2s */
#define DMIC1_INPUT_TO_BUF_TO_I2S     (2)  /* data route: codec0 dmic -> i2s */

#define LINE_INPUT_TO_BUF_TO_I2S      (3)  /* data route: codec0 line-in -> i2s */

#define I2S_INPUT_TO_BUF_TO_DAC       (6)  /* data route: i2s -> codec0 line-out */
#define LINE0_INPUT_TO_HAC_BUF_TO_I2S (7)  /* data route: codec0 line-in -> hac -> i2s */
#define LINE1_INPUT_TO_HAC_BUF_TO_I2S (8)  /* data route: codec0 line-in -> hac -> i2s */

#define LINE_INPUT_TO_ANC_TO_DAC      (9)  /* data route: codec0 line-in -> anc -> dac */

#define AUDIO_MODE_SELECT             LINE_INPUT_TO_ANC_TO_DAC
#define FIFO_SELECT                   FIFO0

unsigned short audio_i2s_192k_config[5] ={2, 14, 1, 64, 64}; /* sampling rate = pll1_clk(default 172.032MHz) * (2 / 14) / (2 * 1) / (64)  = 96KHz */
unsigned short audio_i2s_96k_config[5] = {1, 14, 1, 64, 64}; /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 1) / (64)  = 96KHz */
unsigned short audio_i2s_48k_config[5] = {1, 14, 2, 64, 64}; /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_44p1k_config[5]={1, 14, 2, 64, 64}; /* sampling rate = pll1_clk(PLL1    158.0544MHz)* (1 / 14) / (2 * 2) / (64)  = 44.1KHz */
unsigned short audio_i2s_16k_config[5] = {1, 14, 6, 64, 64}; /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 6) / (64)  = 16KHz */

signed short drop_coef[9] = {0, 0, 0, 0, 1, -4, 12, -58, 2100};

int AUDIO_BUFF[4096];

void user_init(void)
{
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    clock_pll_audio_init(PLL_AUDIO_CLK_172P032M);
    audio_init(PLL_AUDIO_CLK_172P032M); /* must configured first. */

#if (AUDIO_MODE_SELECT == DMIC0_INPUT_TO_BUF_TO_I2S)
    i2s_pin_config_t i2s_pin_config = {

        .bclk_pin       = GPIO_FC_PA2,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PC0,
        .dac_dat_pin    = GPIO_FC_PC1,

    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48k_config,
    };

    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_DMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_DIGITAL_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_set_dmic_a_pin(GPIO_FC_PG0, GPIO_FC_PF6, GPIO_FC_PF7);
    audio_codec0_input_init(&codec0_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_A2_32BIT); /* fifo0 source select i2s0 */


    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */
    #elif (AUDIO_MODE_SELECT == DMIC1_INPUT_TO_BUF_TO_I2S)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PA2,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PC0,
        .dac_dat_pin    = GPIO_FC_PC1,
        #endif
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48k_config,
    };

    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_DMIC_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_DIGITAL_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_set_dmic_b_pin(GPIO_FC_PG3, GPIO_FC_PG1, GPIO_FC_PG2);
    audio_codec0_input_init(&codec0_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCB, FIFO_RX_CODEC0_ADCB_B1_B2_32BIT); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */

    #elif (AUDIO_MODE_SELECT == LINE_INPUT_TO_BUF_TO_I2S)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PA4,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PA5,
        .dac_dat_pin    = GPIO_FC_PA6,
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48k_config,
    };

    audio_codec_input_config_t codec_input_config = {
        .input_src   = AUDIO_LINEIN_ADC0_ADC1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec_input_init(&codec_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC_48K, FIFO_RX_CODEC_OR_DMIC_A1_A2_32BIT);

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */
    audio_i2s_clk_en(audio_i2s_config.i2s_select);

    #elif (AUDIO_MODE_SELECT == I2S_INPUT_TO_BUF_TO_DAC)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PA4,
        .adc_lr_clk_pin = GPIO_FC_PA5,
        .adc_dat_pin    = GPIO_FC_PA6,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48k_config,
    };
    audio_i2s_config_init(&audio_i2s_config);

    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */

    /* dac config */
    audio_codec_output_config_t codec_output_config = {
        .output_dst  = AUDIO_DAC_A0_A1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    audio_codec_output_init(&codec_output_config);
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0 + FIFO_SELECT);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif (AUDIO_MODE_SELECT == LINE_INPUT_TO_ANC_TO_DAC)
#define ANC_CHANNEL_SELECT   ANC0
    //anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB_REF0WZ384ERR0CZ256);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);

    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ1, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ2, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, iir_bypass);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, fir_bypass); //wz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, iir_bypass);  //wz1
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ2, fir_bypass); //wz1
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, iir_bypass);  //wz2
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ3, fir_bypass); //wz2

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ0, 0x4000, 0x0e);     //cz0
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, iir_bypass);  //wcz1->cz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ1, fir_bypass); //wcz1->cz0

    audio_anc_set_cz_gain(ANC_CHANNEL_SELECT, ANC0_CZ3, 0x4000, 0x0e);     //cz3->cz1
    audio_anc_update_cz3_iir_coef(ANC_CHANNEL_SELECT, iir_bypass);             //cz3->cz1
    audio_anc_update_cz3_fir_coef(ANC_CHANNEL_SELECT, fir_bypass);            //cz3->cz1

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_CODEC_384K, ANC_REF_CODEC_OR_DMIC_A1_32_BIT);
    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC0_ERR0, ANC_ERR_ROUTE_CODEC_384K, ANC_ERR_CODEC_OR_DMIC_A2_32_BIT);

    /*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
        .output_dst  = AUDIO_DAC_A0,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_384K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec_output_init(&codec_output_config);

    /*********************** input config ****************************/
    audio_codec_input_config_t codec_input_config = {
        .input_src   = AUDIO_LINEIN_ADC0_ADC1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_384K,
    };

    if (codec_output_config.sample_rate == AUDIO_768K)
    {
        reg_audio_codec_cfg_0 = (reg_audio_codec_cfg_0 & ~(FLD_CODEC_ADC0_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC0_COEF_SEL, 0);
        reg_audio_codec_cfg_1 = (reg_audio_codec_cfg_1 & ~(FLD_CODEC_ADC1_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC1_COEF_SEL, 0);
        reg_audio_codec_cfg_2 = (reg_audio_codec_cfg_2 & ~(FLD_CODEC_ADC2_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC2_COEF_SEL, 0);

        reg_audio_codec_cfg_5 = (reg_audio_codec_cfg_5 & ~(FLD_CODEC_DAC0_COEF_SEL)) | MASK_VAL(FLD_CODEC_DAC0_COEF_SEL, 0);
        reg_audio_codec_cfg_7 = (reg_audio_codec_cfg_7 & ~(FLD_CODEC_DAC1_COEF_SEL)) | MASK_VAL(FLD_CODEC_DAC1_COEF_SEL, 0);
    }
    else if ((codec_output_config.sample_rate == AUDIO_384K) || (codec_output_config.sample_rate == AUDIO_192K))
    {
        reg_audio_codec_cfg_0 = (reg_audio_codec_cfg_0 & ~(FLD_CODEC_ADC0_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC0_COEF_SEL, 3);
        reg_audio_codec_cfg_1 = (reg_audio_codec_cfg_1 & ~(FLD_CODEC_ADC1_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC1_COEF_SEL, 3);
        reg_audio_codec_cfg_2 = (reg_audio_codec_cfg_2 & ~(FLD_CODEC_ADC2_COEF_SEL)) | MASK_VAL(FLD_CODEC_ADC2_COEF_SEL, 3);
        reg_audio_codec_cfg_5 = (reg_audio_codec_cfg_5 & ~(FLD_CODEC_DAC0_COEF_SEL)) | MASK_VAL(FLD_CODEC_DAC0_COEF_SEL, 3);
        reg_audio_codec_cfg_7 = (reg_audio_codec_cfg_7 & ~(FLD_CODEC_DAC1_COEF_SEL)) | MASK_VAL(FLD_CODEC_DAC1_COEF_SEL, 3);
    }
    audio_codec_input_init(&codec_input_config);
#endif

#if (AUDIO_MODE_SELECT < LINE_INPUT_TO_ANC_TO_DAC)
    audio_fifo_ptr_en(AUDIO_RX_FIFO0 << FIFO_SELECT); /* Enable rx fifo ptr */
    /* dma config */
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);
    /* Note: The audio's rx fifo pointer needs to be shifted some bytes (for example 8 bytes) before enabling tx dma,
     * otherwise data phasing will occur between multiple channels. */
    while (audio_get_rx_wptr(FIFO_SELECT) < 16) {
    };
    audio_tx_dma_en(DMA1);
#endif
}

void main_loop(void)
{
    gpio_toggle(LED2);
    delay_ms(500);
}
#endif

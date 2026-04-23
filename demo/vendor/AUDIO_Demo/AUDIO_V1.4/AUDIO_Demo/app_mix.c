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
#define DMIC2_INPUT_TO_BUF_TO_I2S     (3)  /* data route: codec1 dmic -> i2s */
#define LINE0_INPUT_TO_BUF_TO_I2S     (4)  /* data route: codec0 line-in -> i2s */
#define LINE1_INPUT_TO_BUF_TO_I2S     (5)  /* data route: codec0 line-in -> i2s */
#define I2S_INPUT_TO_BUF_TO_DAC       (6)  /* data route: i2s -> codec0 line-out */
#define LINE0_INPUT_TO_HAC_BUF_TO_I2S (7)  /* data route: codec0 line-in -> hac -> i2s */
#define LINE1_INPUT_TO_HAC_BUF_TO_I2S (8)  /* data route: codec0 line-in -> hac -> i2s */
#define ADC0_DAC_LATENCY              (9)  /* data route: codec0 line-in -> siedetone -> DAC */
#define ADC1_DAC_LATENCY              (10) /* data route: codec1 line-in -> siedetone -> DAC */
#define ANC_FF_SIDETONE_PATH0         (11) /* data route: codec0 ADC_A1 -> ref_mic -> DACA1, codec0 ADC_A2 -> sidetone -> DACA2 */
#define ANC_FF_SIDETONE_PATH1         (12) /* data route: codec0 ADC_B1 -> ref_mic -> DACA1, codec0 ADC_B2 -> sidetone -> DACA2 */
#define ANC_FB_SIDETONE_PATH0         (13) /* data route: codec0 ADC_A1 -> err_mic -> DACA1, codec0 ADC_A2 -> sidetone -> DACA2 */
#define ANC_FB_SIDETONE_PATH1         (14) /* data route: codec0 ADC_B1 -> err_mic -> DACA1, codec0 ADC_B2 -> sidetone -> DACA2 */
#define ANC_HB_PATH0                  (15) /* data route: (codec0 ADC_A1 -> ref_mic, codec0 ADC_A2 -> err_mic) -> DACA1 */
#define ANC_HB_PATH1                  (16) /* data route: (codec0 ADC_B1 -> ref_mic, codec0 ADC_B2 -> err_mic) -> DACA1 */

#define AUDIO_MODE_SELECT             DMIC0_INPUT_TO_BUF_TO_I2S
#define FIFO_SELECT                   FIFO0

#define HAC_ASRC_CHANNEL_SELECT       HAC_CHN0

unsigned short audio_i2s_96k_config[5] = {1, 3, 1, 64, 64}; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 1) / (64)  = 96KHz */
unsigned short audio_i2s_48k_config[5] = {1, 3, 2, 64, 64}; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_16k_config[5] = {1, 3, 6, 64, 64}; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 6) / (64)  = 16KHz */

signed short drop_coef[9] = {0, 0, 0, 0, 1, -4, 12, -58, 2100};

int AUDIO_BUFF[4096];

void user_init(void)
{
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
#if(AUDIO_MODE_SELECT < ANC_FF_SIDETONE_PATH0)
    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M); /* must configured first. */
#endif
    #if (AUDIO_MODE_SELECT == DMIC0_INPUT_TO_BUF_TO_I2S)
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
    #elif (AUDIO_MODE_SELECT == DMIC2_INPUT_TO_BUF_TO_I2S)
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

    audio_codec1_input_config_t codec1_input_config = {
        .input_src   = AUDIO_CODEC1_DMIC_A1_A2,
        .data_format = AUDIO_CODEC1_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec1_power_on(AUDIO_CODEC1_DIGITAL_ONLY);
    audio_codec1_set_dmic_a_pin(GPIO_FC_PG6, GPIO_FC_PG4, GPIO_FC_PG5);
    audio_codec1_input_init(&codec1_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC1_ADCA, FIFO_RX_CODEC1_ADCA_A1_A2_32BIT); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */
    #elif (AUDIO_MODE_SELECT == LINE0_INPUT_TO_BUF_TO_I2S)
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
        .input_src   = AUDIO_LINEIN_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_input_init(&codec0_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_A2_32BIT); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */
    #elif (AUDIO_MODE_SELECT == LINE1_INPUT_TO_BUF_TO_I2S)
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
        .input_src   = AUDIO_LINEIN_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_input_init(&codec0_input_config);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCB, FIFO_RX_CODEC0_ADCB_B1_B2_32BIT); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo0 */
    #elif (AUDIO_MODE_SELECT == I2S_INPUT_TO_BUF_TO_DAC)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PA2,
        .adc_lr_clk_pin = GPIO_FC_PC0,
        .adc_dat_pin    = GPIO_FC_PC1,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
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
    audio_i2s_config_init(&audio_i2s_config);
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */

    /* dac config */
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    audio_codec0_power_on(AUDIO_CODEC0_DAC_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_output_init(&codec0_output_config);
    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0 + FIFO_SELECT);

    #elif (AUDIO_MODE_SELECT == LINE0_INPUT_TO_HAC_BUF_TO_I2S)
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
        .sample_rate       = audio_i2s_96k_config,
    };

    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_input_init(&codec0_input_config);
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_32BIT); /* fifo0 source select codec */

    audio_hac_clk_en(HAC_ASRC_CHANNEL_SELECT);
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / 768000 / 1); /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / 96000 / 1); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, 768000, 96000, 1, 1);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    signed int biq0[5] = {2736183, 5472365, 2736183, -474667053, 217176327};
    signed int biq1[5] = {25893499, 25893499, 0, -216648459, 0};
    audio_hac_update_biquad_coef(HAC_ASRC_CHANNEL_SELECT, 0, biq0);
    audio_hac_update_biquad_coef(HAC_ASRC_CHANNEL_SELECT, 1, biq1);
    audio_hac_eq_config_en(HAC_ASRC_CHANNEL_SELECT);
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_ADC0, HAC_ADC_LEFT_32_BIT);
    //audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);
    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);
    audio_i2s_config_init(&audio_i2s_config);
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_1CH); /* i2s0_ch0 sel hac */
    #elif (AUDIO_MODE_SELECT == LINE1_INPUT_TO_HAC_BUF_TO_I2S)

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
        .sample_rate       = audio_i2s_96k_config,
    };

    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_B1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* codec adc config */
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V);
    audio_codec0_input_init(&codec0_input_config);
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_CODEC0_ADCB, FIFO_RX_CODEC0_ADCB_B1_32BIT); /* fifo0 source select codec */

    audio_hac_clk_en(HAC_ASRC_CHANNEL_SELECT);
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / 768000 / 1); /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / 96000 / 1); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, 768000, 96000, 0, 1);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    signed int biq0[5] = {2736183, 5472365, 2736183, -474667053, 217176327};
    signed int biq1[5] = {25893499, 25893499, 0, -216648459, 0};
    audio_hac_update_biquad_coef(HAC_ASRC_CHANNEL_SELECT, 0, biq0);
    audio_hac_update_biquad_coef(HAC_ASRC_CHANNEL_SELECT, 1, biq1);
    audio_hac_eq_config_en(HAC_ASRC_CHANNEL_SELECT);
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_ADC1, HAC_ADC_LEFT_32_BIT);
    //audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);
    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    audio_i2s_config_init(&audio_i2s_config);
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_1CH); /* i2s0_ch0 sel hac */
#elif (AUDIO_MODE_SELECT == ADC0_DAC_LATENCY)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */
    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_LINEIN_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix input config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);

    audio_matrix_set_side_tone_route(SIDE_TONE_CHN6,SIDE_TONE_ROUTE_ADC0,SIDE_TONE_ADC_LEFT_32_BIT);
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC0,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN6);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN6, SIDETONE_0DB);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN6, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 2);

    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
    audio_codec0_input_init(&codec0_input_config);
    audio_codec0_set_output_again(codec0_output_config.output_dst,AUDIO_OUT_A_GAIN_0_DB);
    audio_codec0_output_init(&codec0_output_config);
    audio_tx_dma_en(DMA1);
#elif (AUDIO_MODE_SELECT == ADC1_DAC_LATENCY)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_LINEIN_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix input config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);

    audio_matrix_set_side_tone_route(SIDE_TONE_CHN6,SIDE_TONE_ROUTE_ADC1,SIDE_TONE_ADC_LEFT_32_BIT);
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC1,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN6);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN6, SIDETONE_0DB);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN6, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 2);

    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
    audio_codec0_input_init(&codec0_input_config);
    audio_codec0_set_output_again(codec0_output_config.output_dst,AUDIO_OUT_A_GAIN_0_DB);
    audio_codec0_output_init(&codec0_output_config);
    audio_tx_dma_en(DMA1);
#elif (AUDIO_MODE_SELECT == ANC_FF_SIDETONE_PATH0)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_FF);//0-FF   1-FB    2-HB
    audio_anc_set_wz_iir_taps(ANC0, 5);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 5);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, (short *)wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_latch_ref_mic_gain(ANC0);
    audio_anc_latch_wz_fir_gain(ANC0);
    audio_matrix_set_anc_ref_route(ANC0, ANC_REF_ROUTE_CODEC0_ADCA, ANC_REF_ADC_LEFT_32_BIT);//adc_L -> ref_mic

    //sidetone config
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC0,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 1);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#elif (AUDIO_MODE_SELECT == ANC_FF_SIDETONE_PATH1)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_FF);//0-FF   1-FB    2-HB
    audio_anc_set_wz_iir_taps(ANC0, 5);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 5);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, (short *)wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_latch_ref_mic_gain(ANC0);
    audio_anc_latch_wz_fir_gain(ANC0);
    audio_matrix_set_anc_ref_route(ANC0, ANC_REF_ROUTE_CODEC0_ADCB, ANC_REF_ADC_LEFT_32_BIT);//adc_L -> ref_mic

    //sidetone config
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC1,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 1);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#elif (AUDIO_MODE_SELECT == ANC_FB_SIDETONE_PATH0)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_FB);
    audio_anc_set_adder2_mode(ANC0, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC0, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC0, ANC_WZ_FIRST);
    audio_anc_set_wz_fir_gain(ANC0, 0x4000, 15);
    audio_anc_set_wz_iir_taps(ANC0, 5);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 5);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_set_cz_iir_taps(ANC0, 0, 5);
    audio_anc_update_cz_iir_coef(ANC0, 0, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC0, 0, wz_fir390_bypass, 0x96);
    audio_anc_set_cz_iir_taps(ANC0, 2, 5);
    audio_anc_update_cz_iir_coef(ANC0, 2, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 2, 0x96);
    audio_anc_update_cz_fir_coef(ANC0, 2, wz_fir390_bypass, 0x96);// fir_taps=150

    audio_matrix_set_anc_err_route(ANC0, ANC_ERR_ROUTE_CODEC0_ADCA, ANC_ERR_ADC_LEFT_32_BIT);

    //sidetone config
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC0,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 1);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#elif (AUDIO_MODE_SELECT == ANC_FB_SIDETONE_PATH1)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_FB);
    audio_anc_set_adder2_mode(ANC0, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC0, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC0, ANC_WZ_FIRST);
    audio_anc_set_wz_fir_gain(ANC0, 0x4000, 15);
    audio_anc_set_wz_iir_taps(ANC0, 5);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 5);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_set_cz_iir_taps(ANC0, 0, 5);
    audio_anc_update_cz_iir_coef(ANC0, 0, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC0, 0, wz_fir390_bypass, 0x96);
    audio_anc_set_cz_iir_taps(ANC0, 2, 5);
    audio_anc_update_cz_iir_coef(ANC0, 2, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 2, 0x96);
    audio_anc_update_cz_fir_coef(ANC0, 2, wz_fir390_bypass, 0x96);// fir_taps=150

    audio_matrix_set_anc_err_route(ANC0, ANC_ERR_ROUTE_CODEC0_ADCB, ANC_ERR_ADC_LEFT_32_BIT);

    //sidetone config
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN7,SIDE_TONE_ROUTE_ADC1,SIDE_TONE_ADC_RIGHT_32_BIT);
    audio_side_tone_dma_en(SIDE_TONE_CHN67);
    audio_side_tone_ch_en(SIDE_TONE_CHN7);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN7, SIDETONE_0DB);
    audio_side_tone_set_req_count(SIDE_TONE_CHN67, 36864000, 768000, 1);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#elif (AUDIO_MODE_SELECT == ANC_HB_PATH0)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_HB);
    audio_anc_set_adder2_mode(ANC0, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC0, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC0, ANC_WZ_FIRST);

    audio_anc_latch_wz_fir_gain(ANC0);
    audio_anc_latch_ref_mic_gain(ANC0);
    audio_anc_set_wz_iir_taps(ANC0, 24);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 24);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_set_cz_iir_taps(ANC0, 0, 5);
    audio_anc_update_cz_iir_coef(ANC0, 0, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC0, 0, wz_fir390_bypass, 0x96);

    audio_matrix_set_anc_err_route(ANC0, ANC_ERR_ROUTE_CODEC0_ADCA, ANC_ERR_ADC_LEFT_32_BIT);
    audio_matrix_set_anc_ref_route(ANC0, ANC_REF_ROUTE_CODEC0_ADCA, ANC_REF_ADC_RIGHT_32_BIT);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#elif (AUDIO_MODE_SELECT == ANC_HB_PATH1)
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M); /* must configured first. */
    audio_anc_clk_en(ANC0);
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    audio_codec0_input_init(&codec0_input_config);
    //anc config
    audio_anc_set_mode(ANC0, ANC_MODE_HB);
    audio_anc_set_adder2_mode(ANC0, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC0, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC0, ANC_WZ_FIRST);

    audio_anc_latch_wz_fir_gain(ANC0);
    audio_anc_latch_ref_mic_gain(ANC0);
    audio_anc_set_wz_iir_taps(ANC0, 24);
    audio_anc_update_wz_iir_coef(ANC0, wz_iir_bypass, 24);
    audio_anc_set_wz_fir_taps(ANC0, 390);
    audio_anc_update_wz_fir_coef(ANC0, wz_fir390_bypass, sizeof(wz_fir390_bypass) / sizeof(wz_fir390_bypass[0]));
    audio_anc_set_cz_iir_taps(ANC0, 0, 5);
    audio_anc_update_cz_iir_coef(ANC0, 0, wz_iir_bypass, 5);
    audio_anc_set_cz_fir_taps(ANC0, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC0, 0, wz_fir390_bypass, 0x96);

    audio_matrix_set_anc_err_route(ANC0, ANC_ERR_ROUTE_CODEC0_ADCB, ANC_ERR_ADC_LEFT_32_BIT);
    audio_matrix_set_anc_ref_route(ANC0, ANC_REF_ROUTE_CODEC0_ADCB, ANC_REF_ADC_RIGHT_32_BIT);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_768K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(AUDIO_DAC_A1, DAC_ROUTE_ANC0_SPEAKER, DAC_DATA_FORMAT_INVALID);
    audio_codec0_output_init(&codec0_output_config);

    audio_codec0_set_input_filter_mode(codec0_input_config.input_src, LOW_LATENCY_FILTER_MODE);
    audio_codec0_set_output_filter_mode(LOW_LATENCY_FILTER_MODE);
#endif
#if(AUDIO_MODE_SELECT < ADC0_DAC_LATENCY)
    audio_fifo_ptr_en(AUDIO_RX_FIFO0 << FIFO_SELECT); /* Enable rx fifo ptr */
    /* dma config */
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);
    /* Note: The audio's rx fifo pointer needs to be shifted some bytes (for example 8 bytes) before enabling tx dma,
     * otherwise data phasing will occur between multiple channels. */
    while (audio_get_rx_wptr(FIFO_SELECT) < 8) {
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

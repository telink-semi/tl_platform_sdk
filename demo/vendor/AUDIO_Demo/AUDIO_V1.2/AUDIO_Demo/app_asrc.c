/********************************************************************************************************
 * @file    app_asrc.c
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
#if (AUDIO_MODE == ASRC_DEMO)
    #include "app_sin_data.h"
    #include "app_filter_data.h"
    #define RAM_TO_HAC_TO_RAM_MONO   (1)      /* data route: ram -> hac -> ram mono. */
    #define ADC_TO_HAC_TO_RAM_TO_DAC (2)      /* data route: adc -> hac -> ram -> dac. */
    #define RAM_TO_HAC_TO_DAC        (3)      /* data route: ram -> hac -> dac. */
    #if defined(MCU_CORE_TL751X)
        #define RAM_TO_HAC_TO_RAM_STEREO (4)  /* data route: ram -> hac -> ram. stereo*/
        #define RAM_TO_HAC_TO_RAM_4CH    (5)  /* data route: ram -> hac -> ram. 4ch*/
        #define RAM_TO_HAC_TO_RAM_6CH    (6)  /* data route: ram -> hac -> ram. 6ch*/
        #define RAM_TO_HAC_TO_RAM_8CH    (7)  /* data route: ram -> hac -> ram. 8ch*/
        #define RAM_TO_HAC_TO_I2S_MONO   (8)  /* data route: ram -> hac -> i2s mono. */
        #define RAM_TO_HAC_TO_I2S_STEREO (9)  /* data route: ram -> hac -> i2s stereo. */
        #define I2S_TO_HAC_TO_I2S_MONO   (10) /* data route: i2s -> hac -> i2s mono. */
        #define I2S_TO_HAC_TO_I2S_STEREO (11) /* data route: i2s -> hac -> i2s stereo. */
    #endif

    #define AUDIO_HAC_MODE_SEL      RAM_TO_HAC_TO_RAM_MONO

    #define HAC_FIRST_HAC2_EN       1
    #define HAC_ASRC_CHANNEL_SELECT HAC_CHN0       /* hac channel 0-3. If use more than 1 data path; hac2 or hac3 should be selected. */
    #define HAC_DATA_PATH           HAC_CHN0_DATA0 /* Only used in RAM_TO_HAC_TO_DAC demo */

    #define AUDIO_DMA_CHANNEL_TX    DMA0
    #define AUDIO_DMA_CHANNEL_RX    DMA1
    #define AUDIO_FIFO_CHANNEL      FIFO0
    #define ASRC_FS_IN              48000
    #define ASRC_FS_OUT             48000
    #define PPM                     0
signed short drop_coef[9] = {0, 0, 0, 0, 1, -4, 12, -58, 2100};

    #if defined(MCU_CORE_TL751X)
unsigned short audio_i2s_48kin_96kout_config[5] = {1, 3, 1, 128, 64}; /* For asrc 48k in 96k out */
    #endif

int AUDIO_BUFFER[480*48];

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    #if defined(MCU_CORE_TL7518)
    audio_init(AUDIO_PLL_CLK_36P864M); /* must configured first. */
    #elif defined(MCU_CORE_TL751X)
    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M); /* must configured first. */
    audio_hac_clk_en(HAC_ASRC_CHANNEL_SELECT);
    #endif

    #if (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_MONO)
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 1);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 1); /* 36.864MHz/FS_OUT/CH_NUM. */

        #if defined(MCU_CORE_TL7518)
    audio_asrc_fs_select(HAC_ASRC_CHANNEL_SELECT, AUDIO_ASRC_FS_IN_48K_OUT_48K, PPM);
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_DATA_FORMAT_INVALID);            /* hac route from fifo. */
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_DATA_FORMAT_INVALID); /* rx fifo route from hac. */
        #elif defined(MCU_CORE_TL751X)
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);
    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);
    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);
        #endif

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_mono_24bit, sizeof(sin_48k_mono_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == ADC_TO_HAC_TO_RAM_TO_DAC)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_LINEIN_ADC_A1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    audio_codec0_input_init(&codec0_input_config);

    /*********************** hac config ****************************/
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    /* If the HAC data is output via AHB_MST, then there is no need to match this register, when txfifo will read away the output as soon as the AHB_MST is not empty. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 384);                                                                              /* 36.864MHz/384 = 96KHz. */

        #if defined(MCU_CORE_TL7518)
    audio_asrc_fs_select(HAC_ASRC_CHANNEL_SELECT, AUDIO_ASRC_FS_IN_48K_OUT_96K, PPM);                                                   /* asrc in 48K, out 96K. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_CODEC0_ADCA, HAC_ADC_LEFT_32_BIT);                               /* hac route from adc. */
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_DATA_FORMAT_INVALID); /* rx fifo route from hac. */
        #elif defined(MCU_CORE_TL751X)
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);
    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT);                                                   /* Bypass the EQ function by configuring the specified parameters. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_ADC0, HAC_ADC_LEFT_32_BIT);  /* A1/B1:LIGHT; A2/B2:RIGHT */
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);
    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);
        #endif


    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_96K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_MONO_24BIT_FIFO0 + AUDIO_FIFO_CHANNEL); /* dac route from fifo. */
    audio_codec0_output_init(&codec0_output_config);

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);

    /* tx dma config. */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_DAC)
    audio_codec0_power_on(AUDIO_CODEC0_DAC_ONLY, AUDIO_CODEC0_1P8V); /* power on dac. */

    /*********************** hac config ****************************/
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 768); /* 36.864MHz/768 = 48KHz. */
    /* If the HAC data is output via AHB_MST, then there is no need to match this register, when txfifo will read away the output as soon as the AHB_MST is not empty. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 384);                                                                   /* 36.864MHz/384 = 96KHz. */
        #if defined(MCU_CORE_TL7518)
    audio_asrc_fs_select(HAC_ASRC_CHANNEL_SELECT, AUDIO_ASRC_FS_IN_48K_OUT_96K, PPM);                                        /* asrc in 48K, out 96K. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_DATA_FORMAT_INVALID); /* hac route from ram. */
        #elif defined(MCU_CORE_TL751X)
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);
    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);
        #endif

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_96K,
    };

    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_HAC_DATA0 + HAC_DATA_PATH, DAC_DATA_FORMAT_INVALID); /* dac route from hac. */
    audio_codec0_output_init(&codec0_output_config);

    /* tx dma config. */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_mono_24bit, sizeof(sin_48k_mono_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_STEREO)
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 2);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 2); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 2);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC23_STEREO_20_OR_24BIT);

    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_2CH);
    audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 2);
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);

    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_4CH)
    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 4);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 4); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 4);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC23_4_CHN_20_OR_24BIT);

    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_4CH);
    audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 4);
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);

    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_4ch_24bit, sizeof(sin_48k_4ch_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_6CH)
    audio_hac_clk_en(HAC_CHN2);
    audio_hac_clk_en(HAC_CHN3);

    audio_hac_set_data_src(HAC_CHN2, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN2, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHN3, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN3, HAC_OUTPUT_DATA_MATRIX);

        #if HAC_FIRST_HAC2_EN
    unsigned char hac2_ch_num = 4;
    unsigned char hac3_ch_num = 2;
        #else
    unsigned char hac2_ch_num = 2;
    unsigned char hac3_ch_num = 4;
        #endif

    audio_hac_set_in_data_rate(HAC_CHN2, 36864000 / ASRC_FS_IN / 4);                   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_in_data_rate(HAC_CHN3, 36864000 / ASRC_FS_IN / 4);                   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN2, 36864000 / ASRC_FS_OUT / (hac2_ch_num * 2)); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN3, 36864000 / ASRC_FS_OUT / (hac3_ch_num * 2)); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_CHN2, ASRC_FS_IN, ASRC_FS_OUT, PPM, 4);
    audio_hac_asrc_fs_in_out(HAC_CHN3, ASRC_FS_IN, ASRC_FS_OUT, PPM, 4);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_CHN2, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_CHN2, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_CHN3, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_CHN3, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_CHN2); /* Bypass the EQ function by configuring the specified parameters. */
    audio_hac_bypass_eq(HAC_CHN3); /* Bypass the EQ function by configuring the specified parameters. */

        #if HAC_FIRST_HAC2_EN
    audio_hac_set_in_data_rate_6ch(HAC_CHN3, 36864000 / ASRC_FS_IN / 4 * 3);
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_6_CHN_20_OR_24BIT);
    audio_hac_asrc_6ch_first_en(HAC_CHN2);
        #else
    audio_hac_set_in_data_rate_6ch(HAC_CHN2, 36864000 / ASRC_FS_IN / 4 * 3);
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_6_CHN_20_OR_24BIT);
    audio_hac_asrc_6ch_first_en(HAC_CHN3);
        #endif
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_6CH);
    audio_hac_set_tdm_num(HAC_CHN2, hac2_ch_num);
    audio_hac_set_tdm_num(HAC_CHN3, hac3_ch_num);
    audio_hac_asrc_ch_en(HAC_CHN2, 1);
    audio_hac_asrc_ch_en(HAC_CHN3, 1);
    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);

    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_6ch_24bit, sizeof(sin_48k_6ch_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_8CH)
    audio_hac_clk_en(HAC_CHN2);
    audio_hac_clk_en(HAC_CHN3);

    audio_hac_set_data_src(HAC_CHN2, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN2, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHN3, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN3, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_CHN2, 36864000 / ASRC_FS_IN / 4);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN2, 36864000 / ASRC_FS_OUT / 4); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_set_in_data_rate(HAC_CHN3, 36864000 / ASRC_FS_IN / 4);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN3, 36864000 / ASRC_FS_OUT / 4); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_CHN2, ASRC_FS_IN, ASRC_FS_OUT, PPM, 4);
    audio_hac_asrc_fs_in_out(HAC_CHN3, ASRC_FS_IN, ASRC_FS_OUT, PPM, 4);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_CHN2, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_CHN3, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_CHN2, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_CHN3, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_CHN2); /* Bypass the EQ function by configuring the specified parameters. */
    audio_hac_bypass_eq(HAC_CHN3); /* Bypass the EQ function by configuring the specified parameters. */

        #if HAC_FIRST_HAC2_EN
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_8_CHN_20_OR_24BIT);
    audio_hac_asrc_8ch_first_en(HAC_CHN2);
        #else
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_8_CHN_20_OR_24BIT);
    audio_hac_asrc_8ch_first_en(HAC_CHN3);
        #endif
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_8CH);
    audio_hac_set_tdm_num(HAC_CHN2, 4);
    audio_hac_set_tdm_num(HAC_CHN3, 4);
    audio_hac_asrc_ch_en(HAC_CHN2, 1);
    audio_hac_asrc_ch_en(HAC_CHN3, 1);

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);

    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_8ch_24bit, sizeof(sin_48k_8ch_24bit));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_I2S_MONO)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
        #endif
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48kin_96kout_config,
    };

    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 1);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 1); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */

    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    audio_i2s_config_init(&audio_i2s_config);

    /* matrix input config */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_1CH); /* i2s0_ch0 sel hac */

    /* dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_mono_24bit, sizeof(sin_48k_mono_24bit));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_I2S_STEREO)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
        #endif
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48kin_96kout_config,
    };

    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 2);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 2); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 2);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */

    audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 2);
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_2CH);
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    audio_i2s_config_init(&audio_i2s_config);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);

    /* matrix input config */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC23_STEREO_20_OR_24BIT);

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_2CH); /* i2s0_ch0 sel hac */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_2CH); /* i2s0_ch1 sel hac */

    /* dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    #elif (AUDIO_HAC_MODE_SEL == I2S_TO_HAC_TO_I2S_MONO)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
        #endif
    };

    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48kin_96kout_config,
    };

    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 1);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 1); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */

    if ((HAC_ASRC_CHANNEL_SELECT == HAC_CHN2) || (HAC_ASRC_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 1);
    }
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    audio_i2s_config_init(&audio_i2s_config);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);

    /* matrix input config */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_I2S0_RX, HAC23_I2S_CH0_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_1CH); /* i2s0_ch0 sel hac */

    /* dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    #elif (AUDIO_HAC_MODE_SEL == I2S_TO_HAC_TO_I2S_STEREO)
    i2s_pin_config_t i2s_pin_config = {
        #if defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
        #endif
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        .sample_rate       = audio_i2s_48kin_96kout_config,
    };

    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 2);   /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 2); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 2);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT);
    audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 2);
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_2CH);
    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);

    audio_i2s_config_init(&audio_i2s_config);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);

    /* matrix input config */
    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_I2S0_RX, HAC23_I2S_CH01_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC23_STEREO_20_OR_24BIT);

    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_2CH); /* i2s0_ch0 sel hac */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, I2S_TX_HAC_2CH); /* i2s0_ch1 sel hac */

    /* dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    #endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}
#endif

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
    #define RAM_TO_HAC_TO_RAM_MONO   (1)      /* data route: ram -> hac -> ram mono. */
    #define RAM_TO_HAC_TO_RAM_STEREO (2)  /* data route: ram -> hac -> ram. stereo*/

    #define AUDIO_HAC_MODE_SEL      RAM_TO_HAC_TO_RAM_MONO

    #define HAC_CHANNEL_SELECT      HAC_CH2_ASRC0
    #define HAC_ASRC_CHANNEL_SELECT HAC_ASRC0
    #define ASRC_FS_IN              48000
    #define ASRC_FS_OUT             16000
    #define PPM                     0
    #define TDM_CH                  AUDIO_HAC_MODE_SEL

    #define HAC_FIFO_CHANNEL        FIFO0
    #define DAC_FIFO_CHANNEL        FIFO1
    #define DAC_DMA_CHANNEL         DMA2
    #define HAC_RX_DMA_CHANNEL      DMA0
    #define HAC_TX_DMA_CHANNEL      DMA1

//volatile command_buff[16] = {0};
signed short drop_coef[9] = {0, 0, 0, 0, 1, -4, 12, -58, 2100};
int AUDIO_BUFFER[48*TDM_CH];

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    clock_pll_audio_init(PLL1_AUDIO_CLK_172P032M);
    audio_init(PLL1_AUDIO_CLK_172P032M); /* must configured first. */

    audio_hac_clk_en(HAC_CHANNEL_SELECT);

    audio_asrc_set_droop_step((audio_hac_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_hac_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));

#if (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_MONO)

    audio_hac_set_asrc_tdm_num(HAC_ASRC_CHANNEL_SELECT,1);

    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_input_num(HAC_CHANNEL_SELECT,48);
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, (43008000 / ASRC_FS_IN /AUDIO_HAC_MODE_SEL )-1);   /* 43.008MHz/FS_IN/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, TDM_CH);

    audio_matrix_set_hac_route(HAC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + HAC_FIFO_CHANNEL, HAC_ASRC_20_OR_24_BIT);
    audio_tx_dma_chain_init(HAC_FIFO_CHANNEL, HAC_TX_DMA_CHANNEL, (unsigned short *)sin_48k_mono_24bit, sizeof(sin_48k_mono_24bit));

    audio_matrix_set_rx_fifo_route(HAC_FIFO_CHANNEL, FIFO_RX_ROUTE_ASRC0_TDM0_DATA + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_ASRC_MONO_20_OR_24BIT);
    audio_rx_dma_chain_init(HAC_FIFO_CHANNEL, HAC_RX_DMA_CHANNEL, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));

    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT, 1);

/*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
       .output_dst  = AUDIO_DAC_A0,
       .data_format = AUDIO_CODEC_BIT_24_DATA,
       .sample_rate = AUDIO_16K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_MONO_24BIT_FIFO0 + DAC_FIFO_CHANNEL);
    audio_tx_dma_chain_init(DAC_FIFO_CHANNEL, DAC_DMA_CHANNEL, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));

    audio_codec_dac_clck_en(codec_output_config.output_dst);
    audio_codec_output_init(&codec_output_config);
    audio_codec_dac_en(codec_output_config.output_dst);

    audio_rx_dma_en(HAC_RX_DMA_CHANNEL);
    audio_tx_dma_en(HAC_TX_DMA_CHANNEL);
    audio_tx_dma_en(DAC_DMA_CHANNEL);

#elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_STEREO)

    audio_hac_set_asrc_tdm_num(HAC_ASRC_CHANNEL_SELECT, 2);

    audio_hac_set_input_num(HAC_CHANNEL_SELECT,96);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, (43008000 / ASRC_FS_IN/AUDIO_HAC_MODE_SEL)-1);   /* 43.008MHz/FS_IN/CH_NUM. */
    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, TDM_CH);

    audio_matrix_set_hac_route(HAC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + HAC_FIFO_CHANNEL, HAC_ASRC_20_OR_24_BIT);
    audio_tx_dma_chain_init(HAC_FIFO_CHANNEL, HAC_TX_DMA_CHANNEL, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));

    audio_matrix_set_rx_fifo_route(HAC_FIFO_CHANNEL, FIFO_RX_ROUTE_ASRC0_TDM0_DATA + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC_ASRC_STEREO_20_OR_24BIT);
    audio_rx_dma_chain_init(HAC_FIFO_CHANNEL, HAC_RX_DMA_CHANNEL, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));

    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT, 1);

    /*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
       .output_dst  = AUDIO_DAC_A0_A1,
       .data_format = AUDIO_CODEC_BIT_24_DATA,
       .sample_rate = AUDIO_16K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0 + DAC_FIFO_CHANNEL);
    audio_tx_dma_chain_init(DAC_FIFO_CHANNEL, DAC_DMA_CHANNEL, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));


    audio_codec_dac_clck_en(codec_output_config.output_dst);
    audio_codec_output_init(&codec_output_config);
    audio_codec_dac_en(codec_output_config.output_dst);

    audio_rx_dma_en(HAC_RX_DMA_CHANNEL);
    audio_tx_dma_en(HAC_TX_DMA_CHANNEL);
    audio_tx_dma_en(DAC_DMA_CHANNEL);

#endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}
#endif

/********************************************************************************************************
 * @file    app_codec.c
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
#if (AUDIO_MODE == CODEC_DEMO)

#include "app_sin_data.h"

#define LINE_INPUT_TO_BUF_TO_LINEOUT  (1)
#define AMIC_INPUT_TO_BUF_TO_LINEOUT  (2)
#define AMIC_INPUT_TO_BUF             (3)
#define BUFFER_TO_LINEOUT             (4)

#define CODEC_MODE_SELECT            BUFFER_TO_LINEOUT

#define PLL0_AUDIO_CLK (0)
#define PLL1_AUDIO_CLK (1)

#define AUDIO_CLK_SOURCE_SEL PLL0_AUDIO_CLK

#define AUDIO_BUFF_SIZE    4096
unsigned char AUDIO_BUFF[AUDIO_BUFF_SIZE];

void user_init(void)
{
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    clock_pll_audio_init(PLL1_AUDIO_CLK_172P032M);
#if (AUDIO_CLK_SOURCE_SEL == PLL1_AUDIO_CLK)
    audio_init(PLL1_AUDIO_CLK_172P032M); /* must configured first. */
#else
    audio_init(PLL0_AUDIO_CLK_192M); /* must configured first. */
    pm_audio_pll_power_down();
#endif
#if (CODEC_MODE_SELECT == LINE_INPUT_TO_BUF_TO_LINEOUT)

    /*********************** input config ****************************/
    audio_codec_input_config_t codec_input_config = {
        .input_src   = AUDIO_LINEIN_ADC0_ADC1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC_48K, FIFO_RX_CODEC_OR_DMIC_A0_A1_32BIT);

    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA1); /* the rx dma enable must precede the adc enable. */

    audio_codec_adc_clck_en(codec_input_config.input_src);
    audio_codec_input_init(&codec_input_config);
    audio_codec_adc_en(codec_input_config.input_src);

    /*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
        .output_dst  = AUDIO_DAC_A0_A1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);

    audio_codec_dac_clck_en(codec_output_config.output_dst);
    audio_codec_output_init(&codec_output_config);
    audio_codec_dac_en(codec_output_config.output_dst);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA0);

#elif (CODEC_MODE_SELECT == AMIC_INPUT_TO_BUF_TO_LINEOUT)

    /*********************** input config ****************************/
    audio_codec_input_config_t codec_input_config = {
        .input_src   = AUDIO_AMIC_ADC0_ADC1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC_48K, FIFO_RX_CODEC_OR_DMIC_A0_A1_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec_adc_clck_en(codec_input_config.input_src);
    audio_codec_input_init(&codec_input_config);
    audio_codec_adc_en(codec_input_config.input_src);

    /*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
        .output_dst  = AUDIO_DAC_A0_A1,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);

    audio_codec_dac_clck_en(codec_output_config.output_dst);
    audio_codec_output_init(&codec_output_config);
    audio_codec_dac_en(codec_output_config.output_dst);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);

#elif (CODEC_MODE_SELECT == AMIC_INPUT_TO_BUF)

    /*********************** input config ****************************/
    audio_codec_input_config_t codec_input_config = {
        .input_src   = AUDIO_AMIC_ADC0,
        .data_format = AUDIO_CODEC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC_48K, FIFO_RX_CODEC_OR_DMIC_A0_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec_adc_clck_en(codec_input_config.input_src);
    audio_codec_input_init(&codec_input_config);
    audio_codec_adc_en(codec_input_config.input_src);

#elif (CODEC_MODE_SELECT == BUFFER_TO_LINEOUT)

    /*********************** output config ****************************/
    audio_codec_output_config_t codec_output_config = {
        .output_dst  = AUDIO_DAC_A0,
        .data_format = AUDIO_CODEC_BIT_16_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_MONO_16BIT_FIFO0);

    audio_codec_dac_clck_en(codec_output_config.output_dst);
    audio_codec_output_init(&codec_output_config);
    audio_codec_dac_en(codec_output_config.output_dst);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)sin_48k_mono_d1, sizeof(sin_48k_mono_d1));
    audio_tx_dma_en(DMA1);

#endif
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED2);
}

#endif

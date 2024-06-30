/********************************************************************************************************
 * @file    app_codec0.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "app_config.h"
#if (AUDIO_MODE == CODEC0_DEMO)
#include "app_sin_data.h"

#define LINE_INPUT_TO_BUF_TO_LINEOUT (1)
#define AMIC_INPUT_TO_BUF_TO_LINEOUT (2)
#define AMIC_INPUT_TO_BUF            (3)
#define BUFFER_TO_LINEOUT            (4)

#define CODEC0_MODE_SELECT BUFFER_TO_LINEOUT

#define AUDIO_BUFF_SIZE 4096
int AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    audio_init(AUDIO_PLL_CLK_36P864M); /* must configured first. */

#if (CODEC0_MODE_SELECT == LINE_INPUT_TO_BUF_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_3P3V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_LINEIN_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec0_input_init(&codec0_input_config);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);
    audio_codec0_output_init(&codec0_output_config);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);
#elif (CODEC0_MODE_SELECT == AMIC_INPUT_TO_BUF_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_3P3V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };

    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec0_input_init(&codec0_input_config);
    audio_codec0_set_input_again(codec0_input_config.input_src, AUDIO_IN_A_GAIN_8_DB);

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_STEREO_24BIT_FIFO0);
    audio_codec0_output_init(&codec0_output_config);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);
#elif (CODEC0_MODE_SELECT == AMIC_INPUT_TO_BUF)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_3P3V); /* only power on adc. */
    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_B1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCB, FIFO_RX_CODEC0_ADCB_B1_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec0_input_init(&codec0_input_config);
    audio_codec0_set_input_again(codec0_input_config.input_src, AUDIO_IN_A_GAIN_8_DB);
#elif (CODEC0_MODE_SELECT == BUFFER_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_DAC_ONLY, AUDIO_CODEC0_3P3V); /* only power on dac. */

    /*********************** output config ****************************/
    audio_codec0_output_config_t codec0_output_config = {
        .output_dst  = AUDIO_DAC_A1,
        .data_format = AUDIO_CODEC0_BIT_16_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix output config. */
    audio_matrix_set_dac_route(codec0_output_config.output_dst, DAC_ROUTE_FIFO, DAC_FIFO_MONO_16BIT_FIFO0);
    audio_codec0_output_init(&codec0_output_config);

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)sin_48k_mono_d1, sizeof(sin_48k_mono_d1));
    audio_tx_dma_en(DMA1);
#endif
}

void main_loop(void)
{
    delay_ms(200);
    gpio_toggle(LED1);
}

#endif

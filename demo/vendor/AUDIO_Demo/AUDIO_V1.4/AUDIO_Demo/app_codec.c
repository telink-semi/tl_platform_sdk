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
    #define DMIC0_INPUT_TO_BUF_TO_LINEOUT (5)
    #define DMIC1_INPUT_TO_BUF_TO_LINEOUT (6)

    #if defined(MCU_CORE_TL751X)
        #define DMIC2_INPUT_TO_BUF_TO_LINEOUT (7) //codec1
    #endif

    #define CODEC0_MODE_SELECT AMIC_INPUT_TO_BUF_TO_LINEOUT

    #define AUDIO_BUFF_SIZE    4096
int AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

void user_init(void)
{
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    #if defined(MCU_CORE_TL7518)
    audio_init(AUDIO_PLL_CLK_36P864M); /* must configured first. */
    #elif defined(MCU_CORE_TL751X)
    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M); /* must configured first. */
    #endif

    #if (CODEC0_MODE_SELECT == LINE_INPUT_TO_BUF_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

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
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

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
    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V); /* only power on adc. */
    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_AMIC_ADC_A1,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec0_input_init(&codec0_input_config);

    #elif (CODEC0_MODE_SELECT == BUFFER_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_DAC_ONLY, AUDIO_CODEC0_1P8V); /* only power on dac. */

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
    #elif (CODEC0_MODE_SELECT == DMIC0_INPUT_TO_BUF_TO_LINEOUT)
        #if defined(MCU_CORE_TL7518)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_3P3V); /* power on adc and dac. */
        #elif defined(MCU_CORE_TL751X)
    audio_codec0_power_on(AUDIO_CODEC0_DIGITAL_AND_DAC, AUDIO_CODEC0_1P8V); /* power on codec digital and dac. */
        #endif
    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_DMIC_ADC_A1_A2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };

    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

        #if defined(MCU_CORE_TL7518)
    audio_codec0_set_dmic_a_pin(AUDIO_DMIC0_DATA_PF7, AUDIO_DMIC_CLK1_PF6, AUDIO_DMIC_CLK0_PF5);
        #elif defined(MCU_CORE_TL751X)
    audio_codec0_set_dmic_a_pin(GPIO_FC_PG0, GPIO_FC_PF6, GPIO_FC_PF7);
        #endif
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
    #elif (CODEC0_MODE_SELECT == DMIC1_INPUT_TO_BUF_TO_LINEOUT)
        #if defined(MCU_CORE_TL7518)
    audio_codec0_power_on(AUDIO_CODEC0_ADC_AND_DAC, AUDIO_CODEC0_3P3V); /* power on adc and dac. */
        #elif defined(MCU_CORE_TL751X)
    audio_codec0_power_on(AUDIO_CODEC0_DIGITAL_AND_DAC, AUDIO_CODEC0_1P8V); /* power on codec digital and dac. */
        #endif

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_DMIC_ADC_B1_B2,
        .data_format = AUDIO_CODEC0_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCB, FIFO_RX_CODEC0_ADCB_B1_B2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

        #if defined(MCU_CORE_TL7518)
    audio_codec0_set_dmic_b_pin(AUDIO_DMIC0_DATA_PF7, AUDIO_DMIC_CLK1_PF6, AUDIO_DMIC_CLK0_PF5);
        #elif defined(MCU_CORE_TL751X)
    audio_codec0_set_dmic_b_pin(GPIO_FC_PG3, GPIO_FC_PG1, GPIO_FC_PG2);
        #endif
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
    #elif (CODEC0_MODE_SELECT == DMIC2_INPUT_TO_BUF_TO_LINEOUT)
    audio_codec0_power_on(AUDIO_CODEC0_DAC_ONLY, AUDIO_CODEC0_1P8V); /* only power on dac. */
    audio_codec1_power_on(AUDIO_CODEC1_DIGITAL_ONLY);                /* power on codec1 digital part. */

    /*********************** input config ****************************/
    audio_codec1_input_config_t codec1_input_config = {
        .input_src   = AUDIO_CODEC1_DMIC_A1_A2,
        .data_format = AUDIO_CODEC1_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC1_ADCA, FIFO_RX_CODEC1_ADCA_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_codec1_set_dmic_a_pin(GPIO_FC_PG6, GPIO_FC_PG4, GPIO_FC_PG5);
    audio_codec1_input_init(&codec1_input_config);
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
    #endif
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED2);
}

#endif

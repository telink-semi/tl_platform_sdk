/********************************************************************************************************
 * @file    app_sidetone.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#if (AUDIO_MODE == SIDETONE_DEMO)
#include "app_filter_data.h"

/* data route : ram -> i2sTx -> i2sRx -> sidetone. Connect i2s adc_dat_pin and dac_dat_pin with a wire. */
#define SIDETONE_CH01_TEST          1
#define SIDETONE_CH23_TEST          2
#define SIDETONE_CH45_TEST          3
#define SIDETONE_CH_SEL             SIDETONE_CH01_TEST

#define SIDETONE_AUDIO_CLK          36864000
#define SIDETONE_I2S_SAMPLE         48000
#define SIDETONE_CH_NUM             2

#define I2S_RX_BUFF_OFFSET_LEN      8

#define CHUNK_SIZE                  (2048)
unsigned short audio_i2s_48k_config[5] = { 1, 3, 2, 64, 64 };

int AUDIO_BUFFER_OUT[CHUNK_SIZE + I2S_RX_BUFF_OFFSET_LEN] = { 0 };
int offset = 0;
void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M);
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
    };
#if (SIDETONE_CH_SEL == SIDETONE_CH01_TEST)
    audio_i2s_config_t audio_i2s_config = {
       .i2s_select        = I2S0,
       .i2s_mode          = I2S_I2S_MODE,
       .pin_config        = &i2s_pin_config,
       .data_width        = I2S_BIT_24_DATA,
       .master_slave_mode = I2S_AS_MASTER_EN,
       .sample_rate       = audio_i2s_48k_config,
       .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
     /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN0,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN1,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */

    audio_side_tone_dma_en(SIDE_TONE_CHN01);
    audio_side_tone_ch_en(SIDE_TONE_CHN0);
    audio_side_tone_ch_en(SIDE_TONE_CHN1);
    audio_side_tone_set_req_count(SIDE_TONE_CHN01, 36864000, 48000, 2);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN0, SIDETONE_m30_DB);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN1, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN0, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN1, SIDETONE_m30_DB);
#elif (SIDETONE_CH_SEL == SIDETONE_CH23_TEST)
    audio_i2s_config_t audio_i2s_config = {
       .i2s_select        = I2S1,
       .i2s_mode          = I2S_I2S_MODE,
       .pin_config        = &i2s_pin_config,
       .data_width        = I2S_BIT_24_DATA,
       .master_slave_mode = I2S_AS_MASTER_EN,
       .sample_rate       = audio_i2s_48k_config,
       .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
     /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S1_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN2,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN3,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S1_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */

    audio_side_tone_dma_en(SIDE_TONE_CHN23);
    audio_side_tone_ch_en(SIDE_TONE_CHN2);
    audio_side_tone_ch_en(SIDE_TONE_CHN3);
    audio_side_tone_set_req_count(SIDE_TONE_CHN23, 36864000, 48000, 2);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN2, SIDETONE_m30_DB);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN3, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN2, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN3, SIDETONE_m30_DB);
#elif (SIDETONE_CH_SEL == SIDETONE_CH45_TEST)
    audio_i2s_config_t audio_i2s_config = {
       .i2s_select        = I2S2,
       .i2s_mode          = I2S_I2S_MODE,
       .pin_config        = &i2s_pin_config,
       .data_width        = I2S_BIT_24_DATA,
       .master_slave_mode = I2S_AS_MASTER_EN,
       .sample_rate       = audio_i2s_48k_config,
       .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
     /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S2_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */

    /* matrix output config */
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN4,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_side_tone_route(SIDE_TONE_CHN5,SIDE_TONE_ROUTE_FIFO,SIDE_TONE_FIFO1_20_OR_24_STEREO);
    audio_matrix_set_i2s_tx_route(I2S2_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S2_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 sel fifo0 */

    audio_side_tone_dma_en(SIDE_TONE_CHN45);
    audio_side_tone_ch_en(SIDE_TONE_CHN4);
    audio_side_tone_ch_en(SIDE_TONE_CHN5);
    audio_side_tone_set_req_count(SIDE_TONE_CHN45, 36864000, 48000, 2);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN4, SIDETONE_m30_DB);
    audio_side_tone_set_dac_gain(SIDE_TONE_CHN5, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN4, SIDETONE_m30_DB);
    audio_side_tone_set_adc_gain(SIDE_TONE_CHN5, SIDETONE_m30_DB);
#endif
    /* rx dma config */
    audio_clear_fifo(AUDIO_RX_FIFO0, 1);
    audio_fifo_ptr_en(AUDIO_RX_FIFO0);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT, (CHUNK_SIZE + I2S_RX_BUFF_OFFSET_LEN * 2) * 4);
    dma_llp_dis(DMA0); /* dis llp */
    /* tx dma config */
    //FIFO0 used DAC data ,FIFO1 used ADC data
    audio_clear_fifo(AUDIO_TX_FIFO0, 1);
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)sidetone_data_in, (CHUNK_SIZE + I2S_RX_BUFF_OFFSET_LEN) * 4);
    audio_set_fifo_tx_trig_num(FIFO0,SIDETONE_CH_NUM);
    dma_llp_dis(DMA1); /* dis llp */

    audio_clear_fifo(AUDIO_TX_FIFO1, 1);
    audio_tx_dma_chain_init(FIFO1, DMA2, (unsigned short *)&sidetone_data_in[CHUNK_SIZE], (CHUNK_SIZE + I2S_RX_BUFF_OFFSET_LEN) * 4);;
    audio_set_fifo_tx_trig_num(FIFO1,SIDETONE_CH_NUM);
    dma_llp_dis(DMA2); /* dis llp */

    audio_rx_dma_en(DMA0);
    audio_tx_dma_en(DMA1);
    audio_tx_dma_en(DMA2);

    delay_ms(CHUNK_SIZE*1000/SIDETONE_I2S_SAMPLE/SIDETONE_CH_NUM+1); /* waiting for dma rx complete. */

    while (AUDIO_BUFFER_OUT[offset] == 0)
        offset++;
    for(unsigned int i = 0; i < 2048; i++)
    {
        if (sidetone_data_out[i] != AUDIO_BUFFER_OUT[i + offset])
        {
            AUDIO_BUFFER_OUT[0] = i;
            AUDIO_BUFFER_OUT[1] = sidetone_data_out[i];
            AUDIO_BUFFER_OUT[2] = AUDIO_BUFFER_OUT[i + offset];
            while(1);
        }
    }
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}
#endif

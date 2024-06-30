/********************************************************************************************************
 * @file    app_i2s.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
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
#if (AUDIO_MODE == I2S_DEMO)

#define I2S_5LINE_MODE (1)

#define I2S_LINE_MODE   I2S_5LINE_MODE
#define AUDIO_BUFF_SIZE 4096
int AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

unsigned short audio_i2s_48k_config[5] = { 1, 3, 2, 64, 64 }; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_44p1k_config[5] = { 1, 3, 2, 64, 64 }; /* sampling rate = pll1_clk(pll1_clk needs to be configured 33.8688MHz/169.344MHz by audio_init()) * (1 / 3) / (2 * 2) / (64)  = 44.1KHz */
unsigned short audio_i2s_24k_config[5] = { 1, 3, 4, 64, 64 }; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 4) / (64)  = 24KHz */
unsigned short audio_i2s_16k_config[5] = { 1, 3, 6, 64, 64 }; /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 6) / (64)  = 16KHz */

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    audio_init(AUDIO_PLL_CLK_36P864M); /* must configured first. */

#if (I2S_LINE_MODE == I2S_5LINE_MODE)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = I2S_BCLK_PB3,
        .adc_lr_clk_pin = I2S_ADC_LR_CLK_PB4,
        .adc_dat_pin    = I2S_ADC_DAT_PB0,
        .dac_lr_clk_pin = I2S_DAC_LR_CLK_PB1,
        .dac_dat_pin    = I2S_DAC_DAT_PB2,
    };

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

    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo0 source select i2s0 */
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);

    /* matrix output config. */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 tx sel fifo0 */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch1 tx sel fifo0 */

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);
#endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}

#endif

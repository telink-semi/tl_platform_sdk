/********************************************************************************************************
 * @file    app_spdif.c
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
#if (AUDIO_MODE == SPDIF_DEMO)
#define SPDIF_RX_SAMPLE_44100   0

#define SPDIF_RX_TO_TX_LOOP     1

int spdif_tx_data[] = {
    0,        0,        1094932,  1094932,  2171131,  2171131,  3210180,  3210180,  4194303,  4194303,  5106660,  5106660,  5931640,  5931640,
    6655129,  6655129,  7264746,  7264746,  7750062,  7750062,  8102772,  8102772,  8316841,  8316841,  8388607,  8388607,  8316841,  8316841,
    8102772,  8102772,  7750062,  7750062,  7264746,  7264746,  6655129,  6655129,  5931640,  5931640,  5106660,  5106660,  4194303,  4194303,
    3210180,  3210180,  2171131,  2171131,  1094932,  1094932,  0,        0,        -1094932, -1094932, -2171131, -2171131, -3210180, -3210180,
    -4194303, -4194303, -5106660, -5106660, -5931640, -5931640, -6655129, -6655129, -7264746, -7264746, -7750062, -7750062, -8102772, -8102772,
    -8316841, -8316841, -8388607, -8388607, -8316841, -8316841, -8102772, -8102772, -7750062, -7750062, -7264746, -7264746, -6655129, -6655129,
    -5931640, -5931640, -5106660, -5106660, -4194303, -4194303, -3210180, -3210180, -2171131, -2171131, -1094932, -1094932,
};

#if SPDIF_RX_SAMPLE_44100
unsigned int spdif_rx_data[441*10] = { 0 };
#else
unsigned int spdif_rx_data[384*20] = { 0 };
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
#if SPDIF_RX_SAMPLE_44100
    {
        clock_pll_audio_init(PLL1_AUDIO_CLK_169P344M);
        audio_init(PLL1_AUDIO_CLK_169P344M); /* must configured first. */
        audio_spdif_set_rx_fs(PLL1_AUDIO_CLK_169P344M);
        audio_spdif_set_tx_clk(SPDIF_TX_CLK_44P1K);
    }
#else
    clock_pll_audio_init(PLL1_AUDIO_CLK_172P032M);
    audio_init(PLL1_AUDIO_CLK_172P032M); /* must configured first. */

    audio_spdif_set_rx_fs(PLL1_AUDIO_CLK_172P032M);
    audio_spdif_set_tx_clk(SPDIF_TX_CLK_48K);
#endif

    audio_spdif_set_auto_preamble(1);
    audio_spdif_set_rx_parity(0);
    audio_spdif_set_tx_fmt(0);
    audio_spdif_set_rx_fmt(0);

    spdif_pin_config_t spdif_pin = {
        .spdif_tx_pin = GPIO_FC_PB5,
        .spdif_rx_pin = GPIO_FC_PE0,
    };
    audio_spdif_set_pin(&spdif_pin);

    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_SPDIF_RX, FIFO_RX_DATA_FORMAT_INVALID);

    audio_spdif_rx_decode_en();
    audio_spdif_tx_encode_en();
    /* dma config */
#if (SPDIF_RX_TO_TX_LOOP)
    audio_fifo_ptr_en(AUDIO_RX_FIFO0); /* Enable rx fifo ptr */
    audio_matrix_set_spdif_tx_route(SPDIF_TX_ROUTE_FIFO0);

    /* dma config */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)spdif_rx_data, sizeof(spdif_rx_data));
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)spdif_rx_data, sizeof(spdif_rx_data));
    audio_rx_dma_en(DMA0);
    /* Note: The audio's rx fifo pointer needs to be shifted some bytes (for example 8 bytes) before enabling tx dma,
     * otherwise data phasing will occur between multiple channels. */
    while (audio_get_rx_wptr(FIFO0) < 8) {};
    audio_tx_dma_en(DMA1);
#else
    audio_matrix_set_spdif_tx_route(SPDIF_TX_ROUTE_FIFO1);
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)spdif_rx_data, sizeof(spdif_rx_data));
    audio_tx_dma_chain_init(FIFO1, DMA1, (unsigned short *)spdif_tx_data, sizeof(spdif_tx_data));
    audio_rx_dma_en(DMA0);
    audio_tx_dma_en(DMA1);
#endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}

#endif

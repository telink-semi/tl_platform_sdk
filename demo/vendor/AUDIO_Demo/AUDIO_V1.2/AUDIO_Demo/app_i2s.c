/********************************************************************************************************
 * @file    app_i2s.c
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
#if (AUDIO_MODE == I2S_DEMO)

    #define I2S_5LINE_MODE     (1)

    #define I2S_TDM_2_CHN_MODE (2)
    #define I2S_TDM_4_CHN_MODE (3)
    #define I2S_TDM_6_CHN_MODE (4)
    #define I2S_TDM_8_CHN_MODE (5)

    #if defined(MCU_CORE_TL751X)
        #define I2S_FIFO_RX_IRQ (6)
        #define I2S_FIFO_TX_IRQ (7)
    #endif

    #define I2S_DEMO_MODE   I2S_5LINE_MODE
    #define FIFO_SELECT     FIFO0

    #define AUDIO_BUFF_SIZE 4096
short AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

unsigned short audio_i2s_48k_config[5]     = {1, 3, 2, 64, 64};            /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_48k_config_dsp[5] = {1, 4, 2, 48, 48};            /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 4) / (2 * 2) / (48)  = 48KHz */
unsigned short audio_i2s_44p1k_config[5]   = {1, 3, 2, 64, 64};            /* sampling rate = pll1_clk(pll1_clk needs to be configured 33.8688MHz/169.344MHz by audio_init()) * (1 / 3) / (2 * 2) / (64)  = 44.1KHz */
unsigned short audio_i2s_32k_config[5]     = {1, 3, 3, 64, 64};            /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 3) / (64)  = 32KHz */
unsigned short audio_i2s_24k_config[5]     = {1, 3, 4, 64, 64};            /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 4) / (64)  = 24KHz */
unsigned short audio_i2s_16k_config[5]     = {1, 3, 6, 64, 64};            /* sampling rate = pll1_clk(default 36.864MHz) * (1 / 3) / (2 * 6) / (64)  = 16KHz */

unsigned short audio_tdm_2_chn_48k_config[5]        = {1, 3, 2, 64, 64};   /*sloat32, sampling rate = 36.864MHz * (1 / 3) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_tdm_4_chn_48k_config[5]        = {1, 3, 1, 128, 128}; /*sloat32, sampling rate = 36.864MHz * (1 / 3) / (2 * 1) / (128) = 48KHz */
unsigned short audio_tdm_6_chn_48k_config[5]        = {1, 2, 1, 192, 192}; /*sloat32, sampling rate = 36.864MHz * (1 / 2) / (2 * 1) / (192) = 48KHz */
unsigned short audio_tdm_8_chn_48k_config_slot24[5] = {3, 6, 1, 192, 192}; /*sloat24, sampling rate = 36.864MHz * (3 / 6) / (2 * 1) / (192) = 48KHz */

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
    #endif

    i2s_pin_config_t i2s_pin_config = {
    #if defined(MCU_CORE_TL7518)
        .bclk_pin       = I2S_BCLK_PB3,
        .adc_lr_clk_pin = I2S_ADC_LR_CLK_PB4,
        .adc_dat_pin    = I2S_ADC_DAT_PB0,
        .dac_lr_clk_pin = I2S_DAC_LR_CLK_PB1,
        .dac_dat_pin    = I2S_DAC_DAT_PB2,
    #elif defined(MCU_CORE_TL751X)
        .bclk_pin       = GPIO_FC_PC2,
        .adc_lr_clk_pin = GPIO_FC_PC3,
        .adc_dat_pin    = GPIO_FC_PC4,
        .dac_lr_clk_pin = GPIO_FC_PC5,
        .dac_dat_pin    = GPIO_FC_PC6,
    #endif
    };
    #if (I2S_DEMO_MODE == I2S_5LINE_MODE)
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
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo source select i2s0 */
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);

    /* matrix output config. */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 tx sel fifo */

    /* tx dma init. */
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);
    #elif ((I2S_DEMO_MODE == I2S_TDM_2_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_4_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_6_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_8_CHN_MODE))

    audio_i2s_config_t audio_i2s_config = {
        .i2s_select = I2S0,
        .i2s_mode   = I2S_TDM_MODE,
        .tdm_mode   = I2S_TDM_MODE_A,
        #if (I2S_DEMO_MODE == I2S_TDM_8_CHN_MODE)
        .tdm_slot_width = I2S_TDM_SLOT_WIDTH_24,
        #else
        .tdm_slot_width = I2S_TDM_SLOT_WIDTH_32,
        #endif
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .io_mode           = I2S_5_LINE_MODE,
        #if (I2S_DEMO_MODE == I2S_TDM_2_CHN_MODE)
        .sample_rate = audio_tdm_2_chn_48k_config,
        #elif (I2S_DEMO_MODE == I2S_TDM_4_CHN_MODE)
        .sample_rate = audio_tdm_4_chn_48k_config,
        #elif (I2S_DEMO_MODE == I2S_TDM_6_CHN_MODE)
        .sample_rate = audio_tdm_6_chn_48k_config,
        #elif (I2S_DEMO_MODE == I2S_TDM_8_CHN_MODE)
        .sample_rate = audio_tdm_8_chn_48k_config_slot24,
        #endif
    };
    audio_i2s_config_init(&audio_i2s_config);

        #if (I2S_DEMO_MODE == I2S_TDM_2_CHN_MODE)
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch1 sel fifo */
        #elif (I2S_DEMO_MODE == I2S_TDM_4_CHN_MODE)
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S0_TDM_20_OR_24); /* fifo0 source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch1 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN2, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch2 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN3, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch3 sel fifo */
        #elif (I2S_DEMO_MODE == I2S_TDM_6_CHN_MODE)
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S0_TDM_20_OR_24); /* fifo0 source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch1 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN2, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch2 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN3, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch3 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN4, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch4 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN5, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch5 sel fifo */
        #elif (I2S_DEMO_MODE == I2S_TDM_8_CHN_MODE)
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S0_TDM_20_OR_24); /* fifo0 source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch1 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN2, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch2 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN3, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch3 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN4, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch4 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN5, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch5 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN6, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch6 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN7, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch7 sel fifo */
        #endif
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
    #elif (I2S_DEMO_MODE == I2S_FIFO_RX_IRQ)
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
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo */

    /* enable irq. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_DFIFO);

    audio_set_rx_buff_thres(FIFO_SELECT, sizeof(AUDIO_BUFF) / 2);
    audio_fifo_irq_en(AUDIO_RX_FIFO0 << FIFO_SELECT); //rx fifo irq_en
    audio_fifo_ptr_en(AUDIO_RX_FIFO0 << FIFO_SELECT); //rx ptr_en

    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);
    audio_tx_dma_en(DMA1);
    #elif (I2S_DEMO_MODE == I2S_FIFO_TX_IRQ)
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
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo source select i2s0 */
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 sel fifo */


    /* enable irq. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_DFIFO);

    audio_set_tx_buff_thres(FIFO_SELECT, sizeof(AUDIO_BUFF) / 2);
    audio_fifo_irq_en(AUDIO_TX_FIFO0 << FIFO_SELECT); //tx fifo irq_en
    audio_fifo_ptr_en(AUDIO_TX_FIFO0 << FIFO_SELECT); //tx ptr_en

    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);
    audio_tx_dma_en(DMA1);
    #endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}

    #if ((I2S_DEMO_MODE == I2S_FIFO_RX_IRQ) || (I2S_DEMO_MODE == I2S_FIFO_TX_IRQ))

volatile unsigned int audio_rx_fifo_irq_cnt = 0;
volatile unsigned int audio_tx_fifo_irq_cnt = 0;

volatile unsigned int audio_rx_fifo_wptr = 0;
volatile unsigned int audio_tx_fifo_rptr = 0;

_attribute_ram_code_sec_ void audio_irq_handler(void)
{
        #if (I2S_DEMO_MODE == I2S_FIFO_RX_IRQ)
    if (audio_get_fifo_irq_status(AUDIO_RX_FIFO0 << FIFO_SELECT)) {
        audio_rx_fifo_wptr = audio_get_rx_wptr(FIFO_SELECT);
        audio_clr_fifo_irq_status(AUDIO_RX_FIFO0 << FIFO_SELECT);
        audio_rx_fifo_irq_cnt++;
    }
        #elif (I2S_DEMO_MODE == I2S_FIFO_TX_IRQ)
    if (audio_get_fifo_irq_status(AUDIO_TX_FIFO0 << FIFO_SELECT)) {
        audio_tx_fifo_rptr = audio_get_tx_rptr(FIFO_SELECT);
        audio_clr_fifo_irq_status(AUDIO_TX_FIFO0 << FIFO_SELECT);
        audio_tx_fifo_irq_cnt++;
    }
        #endif
}
PLIC_ISR_REGISTER(audio_irq_handler, IRQ_DFIFO)
    #endif
#endif

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

    #if defined(MCU_CORE_TL753X)
        #define I2S_FIFO_RX_IRQ (6)
        #define I2S_FIFO_TX_IRQ (7)
    #endif

    #define I2S_4LINE_DAC_MODE 8
    #define I2S_4LINE_ADC_MODE 9
    #define I2S_2LINE_TX_MODE  10
    #define I2S_2LINE_RX_MODE  11
    #define I2S_SCHEDULE_MODE  12
    #define I2S_ALIGN_MODE     13


    #define I2S_DEMO_MODE   I2S_5LINE_MODE
    #define FIFO_SELECT     FIFO0

    #define AUDIO_BUFF_SIZE 9600*4

#include "app_sin_data.h"

#define I2S_BUFF_TO_TX_TEST_EN      0

short AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

unsigned short audio_i2s_192k_config[5]     = {1, 14, 0, 64, 64};
unsigned short audio_i2s_96k_config[5]     = {1, 14, 1, 64, 64};
unsigned short audio_i2s_48k_config[5]     = {1, 14, 2, 64, 64};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_48k_config_dsp[5] = {3, 56, 2, 48, 48};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 4) / (2 * 2) / (48)  = 48KHz */
unsigned short audio_i2s_44p1k_config[5]   = {1, 14, 2, 64, 64};            /* sampling rate = pll1_clk(pll1_clk needs to be configured 33.8688MHz/169.344MHz by audio_init()) * (1 / 3) / (2 * 2) / (64)  = 44.1KHz */
unsigned short audio_i2s_32k_config[5]     = {1, 14, 3, 64, 64};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 3) / (2 * 3) / (64)  = 32KHz */
unsigned short audio_i2s_24k_config[5]     = {1, 14, 4, 64, 64};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 3) / (2 * 4) / (64)  = 24KHz */
unsigned short audio_i2s_16k_config[5]     = {1, 14, 6, 64, 64};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 3) / (2 * 6) / (64)  = 16KHz */

unsigned short audio_tdm_2_chn_48k_config[5]        = {1, 14, 2, 64, 64};   /*sloat32, sampling rate = 36.864MHz * (1 / 3) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_tdm_4_chn_48k_config[5]        = {1, 14, 1, 128, 128}; /*sloat32, sampling rate = 36.864MHz * (1 / 3) / (2 * 1) / (128) = 48KHz */
//unsigned short audio_tdm_4_chn_48k_config[5]        = {1, 14, 0, 128, 128};
unsigned short audio_tdm_6_chn_48k_config[5]        = {3, 56, 0, 192, 192}; /*sloat32, sampling rate = 36.864MHz * (1 / 2) / (2 * 1) / (192) = 48KHz */
//unsigned short audio_tdm_8_chn_48k_config_slot24[5] = {1, 14, 1, 256, 256}; /*sloat24, sampling rate = 36.864MHz * (3 / 6) / (2 * 1) / (192) = 48KHz */
unsigned short audio_tdm_8_chn_48k_config_slot24[5] = {1, 14, 0, 256, 256};
volatile int AAAAA_DEBUG = 0;
void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(GPIO_PF6);
    gpio_output_en(GPIO_PF6);
    gpio_input_dis(GPIO_PF6);

    #if defined(MCU_CORE_TL7518)
    audio_init(AUDIO_PLL_CLK_36P864M); /* must configured first. */
    #elif defined(MCU_CORE_TL751X)
    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M); /* must configured first. */
    #elif defined(MCU_CORE_TL753X)
    AAAAA_DEBUG |= 0x01;
//    clock_pll_audio_init(PLL_AUDIO_CLK_172P032M);
    audio_init(PLL_AUDIO_CLK_172P032M); /* must configured first. */
    AAAAA_DEBUG |= 0x02;
    #endif

#if (I2S_DEMO_MODE != I2S_ALIGN_MODE)&(I2S_DEMO_MODE != I2S_SCHEDULE_MODE)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PA0,
        .adc_lr_clk_pin = GPIO_FC_PA1,
        .adc_dat_pin    = GPIO_FC_PA2,
        .dac_lr_clk_pin = GPIO_FC_PB0,
        .dac_dat_pin    = GPIO_FC_PF7,
    };
#endif

#if (I2S_DEMO_MODE == I2S_5LINE_MODE)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
//      .master_slave_mode = I2S_AS_SLAVE_EN,
        .sample_rate       = audio_i2s_48k_config,
//      .sample_rate       = audio_i2s_96k_config,
//      .sample_rate       = audio_i2s_192k_config,
        //////to debug DSP mode
        //.sample_rate       = audio_i2s_48k_config_dsp,
        .io_mode           = I2S_5_LINE_MODE,
    };
    AAAAA_DEBUG |= 0x04;
    audio_i2s_config_init(&audio_i2s_config);
#if (!I2S_BUFF_TO_TX_TEST_EN)
    /* matrix input config. */
    AAAAA_DEBUG |= 0x08;
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo source select i2s0 */
    /* rx dma init. */
    AAAAA_DEBUG |= 0x100;
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);
#endif
    /* matrix output config. */
    AAAAA_DEBUG |= 0x200;
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 tx sel fifo */

    /* tx dma init. */
#if I2S_BUFF_TO_TX_TEST_EN
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
#else
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
#endif

    audio_tx_dma_en(DMA1);
#elif (I2S_DEMO_MODE == I2S_4LINE_DAC_MODE)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_48k_config,
        .io_mode           = I2S_4_LINE_DAC_MODE,
    };
    AAAAA_DEBUG |= 0x04;
    audio_i2s_config_init(&audio_i2s_config);

    /* matrix input config. */
    AAAAA_DEBUG |= 0x08;
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo source select i2s0 */
    /* rx dma init. */
    AAAAA_DEBUG |= 0x100;
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);

    /* matrix output config. */
    AAAAA_DEBUG |= 0x200;
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 tx sel fifo */

    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

    audio_tx_dma_en(DMA1);
#elif (I2S_DEMO_MODE == I2S_4LINE_ADC_MODE)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_48k_config,
        //////to debug DSP mode
        //.sample_rate       = audio_i2s_48k_config_dsp,
        .io_mode           = I2S_4_LINE_ADC_MODE,
    };
    AAAAA_DEBUG |= 0x04;
    audio_i2s_config_init(&audio_i2s_config);

    /* matrix input config. */
    AAAAA_DEBUG |= 0x08;
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo source select i2s0 */
    /* rx dma init. */
    AAAAA_DEBUG |= 0x100;
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0);

    /* matrix output config. */
    AAAAA_DEBUG |= 0x200;
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 tx sel fifo */

    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

    audio_tx_dma_en(DMA1);
#elif ((I2S_DEMO_MODE == I2S_TDM_2_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_4_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_6_CHN_MODE) || (I2S_DEMO_MODE == I2S_TDM_8_CHN_MODE))

    audio_i2s_config_t audio_i2s_config = {
        .i2s_select = I2S0,
        .i2s_mode   = I2S_TDM_MODE,
        .tdm_mode   = I2S_TDM_MODE_C,
        .tdm_slot_width = I2S_TDM_SLOT_WIDTH_32,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
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
//    audio_i2s_config_init(&audio_i2s_config);
    AAAAA_DEBUG |= 0x04;
    #if (I2S_DEMO_MODE == I2S_TDM_2_CHN_MODE)
    /* matrix input config */
    audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* fifo0 source select i2s0 */
    AAAAA_DEBUG |= 0x08;
    /* matrix output config */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch0 sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S0_TX_FIFO0_20_OR_24_TDM_I2S0 + FIFO_SELECT); /* i2s0_ch1 sel fifo */
    AAAAA_DEBUG |= 0x100;
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
    /* dma config */
    AAAAA_DEBUG |= 0x200;
    audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

    reg_audio_dma_rx_max(FIFO_SELECT) = 0xffff;
    reg_audio_dma_rx_wptr(FIFO_SELECT) = 0x0000;
    audio_clear_fifo(AUDIO_RX_FIFO0 << FIFO_SELECT, 0);
    audio_fifo_ptr_en(AUDIO_RX_FIFO0 << FIFO_SELECT);

    audio_rx_dma_en(DMA0);

    audio_i2s_config_init(&audio_i2s_config);
    AAAAA_DEBUG |= 0x400;
    /* Note: The audio's rx fifo pointer needs to be shifted some bytes (for example 8 bytes) before enabling tx dma,
     * otherwise data phasing will occur between multiple channels. */
    while (audio_get_rx_wptr(FIFO_SELECT) < 16) {
    };

    AAAAA_DEBUG |= 0x800;
    audio_tx_dma_en(DMA1);
#elif (I2S_DEMO_MODE == I2S_FIFO_RX_IRQ)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
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
        .data_width        = I2S_BIT_32_DATA,
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
#elif (I2S_DEMO_MODE == I2S_2LINE_TX_MODE)
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_48k_config,
        .io_mode           = I2S_2_LANE_TX_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);

    /* matrix output config. */
    audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO + FIFO_SELECT); /* i2s0_ch1 tx sel fifo */

    extern void sina_waveform_generation(int freq,int ch,int bits,int samp_cn,int *addr);
    sina_waveform_generation(48000,4,24,sizeof(AUDIO_BUFF)/sizeof(AUDIO_BUFF[0])/4,(int *)AUDIO_BUFF);
    audio_tx_dma_chain_init(FIFO_SELECT, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

    audio_tx_dma_en(DMA1);
#elif (I2S_DEMO_MODE == I2S_2LINE_RX_MODE)
    audio_i2s_config_t audio_i2s_config = {
            .i2s_select        = I2S0,
            .i2s_mode          = I2S_I2S_MODE,
            .pin_config        = &i2s_pin_config,
            .data_width        = I2S_BIT_32_DATA,
            .master_slave_mode = I2S_AS_MASTER_EN,
            .sample_rate       = audio_i2s_48k_config,
            .io_mode           = I2S_2_LANE_RX_MODE,
        };
        audio_i2s_config_init(&audio_i2s_config);

        /* matrix input config. */
        audio_matrix_set_rx_fifo_route(FIFO_SELECT, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24); /* rx fifo source select i2s0 */

        /* rx dma init. */
        audio_rx_dma_chain_init(FIFO_SELECT, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
        audio_rx_dma_en(DMA0);
#elif (I2S_DEMO_MODE == I2S_SCHEDULE_MODE)
        i2s_pin_config_t i2s_pin_config[] = {
            {
                .bclk_pin       = GPIO_FC_PA0,
                .adc_lr_clk_pin = GPIO_FC_PA1,
                .adc_dat_pin    = GPIO_FC_PA2,
                .dac_lr_clk_pin = GPIO_FC_PB0,
                .dac_dat_pin    = GPIO_FC_PF7,
            },
            {
                .bclk_pin       = GPIO_FC_PG1,
                .adc_lr_clk_pin = GPIO_FC_PG2,
                .adc_dat_pin    = GPIO_FC_PG3,
                .dac_lr_clk_pin = GPIO_FC_PG4,
                .dac_dat_pin    = GPIO_FC_PG5,
            },
            {
                .bclk_pin       = GPIO_FC_PC3,
                .adc_lr_clk_pin = GPIO_FC_PC4,
                .adc_dat_pin    = GPIO_FC_PC5,
                .dac_lr_clk_pin = GPIO_FC_PC6,
                .dac_dat_pin    = GPIO_FC_PC7,
            },
        };

        audio_i2s_config_t audio_i2s_config[] = {
            {
             .i2s_select = I2S0,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[0],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
            {
             .i2s_select = I2S1,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[1],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
            {
             .i2s_select = I2S2,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[2],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
        };

        /* schecule time config. */
        unsigned int t0 = stimer_get_tick();
        audio_i2s_set_target_value(I2S0, t0 + 1 * SYSTEM_TIMER_TICK_1S);
        audio_i2s_schedule_en(I2S0);

        audio_i2s_set_target_value(I2S1, t0 + 2 * SYSTEM_TIMER_TICK_1S);
        audio_i2s_schedule_en(I2S1);

        audio_i2s_set_target_value(I2S2, t0 + 3 * SYSTEM_TIMER_TICK_1S);
        audio_i2s_schedule_en(I2S2);

        /* i2s clk and pin config. */
        audio_i2s_config_init(&audio_i2s_config[0]);
        audio_i2s_config_init(&audio_i2s_config[1]);
        audio_i2s_config_init(&audio_i2s_config[2]);

        /* matrix config. */
        audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO);

        audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO1_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S1_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO1_20_OR_24_STEREO);

        audio_matrix_set_i2s_tx_route(I2S2_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO2_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S2_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO2_20_OR_24_STEREO);

        /* dma init. */
        audio_tx_dma_chain_init(FIFO0, DMA0, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
        audio_tx_dma_chain_init(FIFO1, DMA1, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
        audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));



        /* DMA enable. */
        audio_tx_dma_en(DMA0);
        audio_tx_dma_en(DMA1);
        audio_tx_dma_en(DMA2);

#elif (I2S_DEMO_MODE == I2S_ALIGN_MODE)
        i2s_pin_config_t i2s_pin_config[] = {
            {
                .bclk_pin       = GPIO_FC_PA0,
                .adc_lr_clk_pin = GPIO_FC_PA1,
                .adc_dat_pin    = GPIO_FC_PA2,
                .dac_lr_clk_pin = GPIO_FC_PB0,
                .dac_dat_pin    = GPIO_FC_PF7,
            },
            {
                .bclk_pin       = GPIO_FC_PG1,
                .adc_lr_clk_pin = GPIO_FC_PG2,
                .adc_dat_pin    = GPIO_FC_PG3,
                .dac_lr_clk_pin = GPIO_FC_PG4,
                .dac_dat_pin    = GPIO_FC_PG5,
            },
            {
                .bclk_pin       = GPIO_FC_PC3,
                .adc_lr_clk_pin = GPIO_FC_PC4,
                .adc_dat_pin    = GPIO_FC_PC5,
                .dac_lr_clk_pin = GPIO_FC_PC6,
                .dac_dat_pin    = GPIO_FC_PC7,
            },
        };

        audio_i2s_config_t audio_i2s_config[] = {
            {
             .i2s_select = I2S0,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[0],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
            {
             .i2s_select = I2S1,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[1],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
            {
             .i2s_select = I2S2,
             .i2s_mode = I2S_I2S_MODE,
             .pin_config = &i2s_pin_config[2],
             .data_width = I2S_BIT_32_DATA,
             .master_slave_mode = I2S_AS_MASTER_EN,
             .io_mode = I2S_5_LINE_MODE,
             .sample_rate = audio_i2s_48k_config,
             },
        };

        /* i2s align config. */
        unsigned int t0 = stimer_get_tick();
        i2s_align_config_t i2s_align_config = {
            .align_th = t0 + 1 * SYSTEM_TIMER_TICK_1S,
            .align_mode = I2S0_I2S1_ALIGN,
            .align_clk = I2S_ALIGN_CLK,
        };
        audio_i2s_align_config(&i2s_align_config);
        audio_i2s_align_en();

        /* i2s clk and pin config. */
        audio_i2s_config_init(&audio_i2s_config[0]);
        audio_i2s_config_init(&audio_i2s_config[1]);
        audio_i2s_config_init(&audio_i2s_config[2]);

        /* matrix config. */
        audio_matrix_set_i2s_tx_route(I2S0_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S0_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO);

        audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO1_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S1_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO1_20_OR_24_STEREO);

        audio_matrix_set_i2s_tx_route(I2S2_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO2_20_OR_24_STEREO);
        audio_matrix_set_i2s_tx_route(I2S2_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO2_20_OR_24_STEREO);

        /* dma init. */
        audio_tx_dma_chain_init(FIFO0, DMA0, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
        audio_tx_dma_chain_init(FIFO1, DMA1, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
        audio_tx_dma_chain_init(FIFO2, DMA2, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));

        /* DMA enable. */
        audio_tx_dma_en(DMA0);
        audio_tx_dma_en(DMA1);
        audio_tx_dma_en(DMA2);

    #endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    gpio_toggle(GPIO_PF6);
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

/********************************************************************************************************
 * @file    app_dmic.c
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
#if (AUDIO_MODE == DMIC_DEMO)
#include "app_sin_data.h"
#include "app_filter_data.h"
#define DMIC0_INPUT_TO_BUF_TO_LINEOUT (1) //DMIC0 support STEREO
#define DMIC1_INPUT_TO_BUF_TO_LINEOUT (2) //DMIC1 only support MONO

#define DMIC_MODE_SEL                 DMIC0_INPUT_TO_BUF_TO_LINEOUT

#define BIT24_USED                                 1//I2S0

int AUDIO_BUFF[9600];

unsigned short audio_i2s_16k_config[5]     = {2, 14, 6, 64, 64};
unsigned short audio_i2s_32k_config[5]     = {4, 14, 6, 64, 64};
unsigned short audio_i2s_48k_config[5]     = {2, 14, 2, 64, 64};            /* sampling rate = pll1_clk(default 172.032MHz) * (1 / 14) / (2 * 2) / (64)  = 48KHz */
unsigned short audio_i2s_48k_config_24slot[5]     = {6, 14, 8, 48, 48};
unsigned short audio_i2s_48k_config_PDM[5]  = {1, 28, 0, 64, 64};//172.032/2
unsigned short audio_i2s_96k_config[5]     = {2, 14, 1, 64, 64};

unsigned short audio_i2s_192k_config[5]     = {4, 14, 1, 64, 64};
unsigned short audio_i2s_192k_config_24slot[5] = {12, 112, 0, 48, 48};

unsigned short audio_i2s_384k_config_24slot[5] = {24, 112, 0, 48, 48};
unsigned short audio_i2s_768k_config_24slot[5] = {48, 112, 0, 48, 48};

unsigned short audio_i2s_384k_config[5]     = {4, 14, 0, 64, 64};

volatile int AAAAA_DEBUG;
void user_init(void)
{
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

#if (DMIC_MODE_SEL == DMIC0_INPUT_TO_BUF_TO_LINEOUT)
#if (0)
    audio_init(PLL_AUDIO_CLK_86P016M);  //must configured first.

    /*********************** input config ****************************/
    audio_dmic_input_config_t dmic_input_config = {
        .input_src   = AUDIO_DMIC0_STEREO,
        .data_format = AUDIO_DMIC_BIT_24_DATA,
        .sample_rate = AUDIO_192K,
        .d_gain = AUDIO_DMIC_D_GAIN_0DB,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_DMIC_192K, FIFO_RX_CODEC_OR_DMIC_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

    audio_dmic0_set_pin(GPIO_FC_PE4, GPIO_FC_PE1, GPIO_NONE_PIN);
    audio_dmic_input_init(&dmic_input_config);
    reg_audio_dmic_lr_data_ctrl_1 = 0x10;
    reg_audio_dmic_lr_data_ctrl_2 = 0xf0;
   // reg_audio_dmic_single_data_ctrl_1 = 0x10;
   // reg_audio_dmic_single_data_ctrl_2 = 0xf0;
    audio_rx_dma_en(DMA0);

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG2,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PG5,
        .dac_dat_pin    = GPIO_FC_PG6,
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S1,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_192k_config,
        .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
    audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch0 tx sel fifo */
    audio_matrix_set_i2s_tx_route(I2S1_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch1 tx sel fifo */
    audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_tx_dma_en(DMA1);
    delay_ms(5000);
    audio_rx_dma_dis(DMA0);
#else
#define FIFO_USED                    0
    audio_init(PLL_AUDIO_CLK_86P016M);  //must configured first.

        /*********************** input config ****************************/
        audio_dmic_input_config_t dmic_input_config = {
            .input_src   = AUDIO_DMIC0_L,
#if (BIT24_USED == 1)
            .data_format = AUDIO_DMIC_BIT_24_DATA,
#else
            .data_format = AUDIO_DMIC_BIT_16_DATA,
#endif
            .sample_rate = AUDIO_384K,
            .d_gain = AUDIO_DMIC_D_GAIN_0DB,
        };
        /* matrix input config. */

#if (FIFO_USED)
#if (BIT24_USED == 1)
        audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_DMIC_384K, FIFO_RX_CODEC_OR_DMIC_A1_32BIT);
#else
        audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_DMIC_384K, FIFO_RX_CODEC_OR_DMIC_A1_16BIT);
#endif
#else
#define ANC_CHANNEL_SELECT                      ANC0
    //anc config
    audio_anc_clk_en(ANC_CHANNEL_SELECT);
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF_REF0);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_CZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_CZ_FIRST);
    audio_anc_set_ref_mic_gain(ANC_CHANNEL_SELECT, ANC0_REF0, 0x4000, 0x0e);
    audio_anc_set_wz_gain(ANC_CHANNEL_SELECT, ANC0_WZ0, 0x4000, 0x0e);
    audio_anc_update_wcz_iir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_iir_bypass);  //wz0
    audio_anc_update_wcz_fir_coef(ANC_CHANNEL_SELECT, ANC0_WCZ0, wz_fir_bypass); //wz0

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC0_REF0, ANC_REF_ROUTE_DMIC_384K_LL, ANC_REF_CODEC_OR_DMIC_A1_32_BIT);

#endif
        /* rx dma init. */
        audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));

        audio_dmic0_set_pin(GPIO_FC_PE4, GPIO_FC_PE1, GPIO_NONE_PIN);
       // audio_dmic_input_init(&dmic_input_config);
#if (BIT24_USED == 1)
#else
        reg_audio_dmic_codec_lr_gain_ctrl = (reg_audio_dmic_codec_lr_gain_ctrl & ~FLD_CODEC_GAIN_LR) |
                                                    MASK_VAL(FLD_CODEC_GAIN_LR, 0xe);

        reg_audio_dmic_codec_lr_gain_shift_ctrl = (reg_audio_dmic_codec_lr_gain_shift_ctrl & ~FLD_CODEC_GAIN_SHIFT_LR) |
                                                    MASK_VAL(FLD_CODEC_GAIN_SHIFT_LR, 0x16);
        reg_audio_dmic_codec_lr_low_latency_gain_ctrl = (reg_audio_dmic_codec_lr_low_latency_gain_ctrl & ~FLD_CODEC_GAIN_SHIFT_LOW_LATENCY) |
                                                            MASK_VAL(FLD_CODEC_GAIN_SHIFT_LOW_LATENCY, 0x16);
#endif
        reg_audio_dmic_lr_data_ctrl_1 = 0x10;
        reg_audio_dmic_lr_data_ctrl_2 = 0xf0;
       // reg_audio_dmic_single_data_ctrl_1 = 0x10;
       // reg_audio_dmic_single_data_ctrl_2 = 0xf0;
        audio_rx_dma_en(DMA0);

#define I2S_SEL                                 1//I2S0
#if (I2S_SEL == 0)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG2,
        .adc_lr_clk_pin = GPIO_FC_PG3,
        .adc_dat_pin    = GPIO_FC_PG4,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
    };
#elif  (I2S_SEL == 1)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PH4,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PH5,
        .dac_dat_pin    = GPIO_FC_PF3,
    };
#else
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG7,
        .adc_lr_clk_pin = GPIO_FC_PH0,
        .adc_dat_pin    = GPIO_FC_PH1,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
#endif

        audio_i2s_config_t audio_i2s_config = {
            .i2s_select        = I2S1,
            .i2s_mode          = I2S_I2S_MODE,
            .pin_config        = &i2s_pin_config,
#if (BIT24_USED == 1)
            .data_width        = I2S_BIT_24_DATA,
#else
            .data_width        = I2S_BIT_16_DATA,
#endif
            .master_slave_mode = I2S_AS_MASTER_EN,
            .sample_rate       = audio_i2s_384k_config_24slot,
            .io_mode           = I2S_5_LINE_MODE,
        };
        audio_i2s_config_init(&audio_i2s_config);
        audio_i2s_clk_en(audio_i2s_config.i2s_select);
#if (FIFO_USED)
#if (BIT24_USED == 1)
        audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_MONO); /* i2s0_ch0 tx sel fifo */
#else
        audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_16_MONO); /* i2s0_ch0 tx sel fifo */
#endif
      //  audio_matrix_set_i2s_tx_route(I2S1_CHN1, I2S_TX_ROUTE_FIFO, I2S_TX_FIFO0_20_OR_24_STEREO); /* i2s0_ch1 tx sel fifo */
        audio_tx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
        audio_tx_dma_en(DMA1);
#else
        audio_matrix_set_i2s_tx_route(I2S1_CHN0, I2S_TX_ROUTE_ANC0_SPEAKER, I2S_RX_DATA_FORMAT_INVALID);
#endif
       // delay_ms(5000);
       // audio_rx_dma_dis(DMA0);
        audio_dmic_input_init(&dmic_input_config);
       // audio_i2s_clk_en(audio_i2s_config.i2s_select);

#endif

#elif (DMIC_MODE_SEL == DMIC1_INPUT_TO_BUF_TO_LINEOUT)
    audio_init(PLL_AUDIO_CLK_86P016M);  //must configured first.

    /*********************** input config ****************************/
    audio_dmic_input_config_t dmic_input_config = {
        .input_src   = AUDIO_DMIC0_STEREO,
        .data_format = AUDIO_DMIC_BIT_24_DATA,
        .sample_rate = AUDIO_48K,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC_48K, FIFO_RX_CODEC_OR_DMIC_A1_A2_32BIT);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA0); /* the rx dma enable must precede the adc enable. */

    audio_dmic_input_init(&dmic_input_config);
#else
    audio_init(PLL_AUDIO_CLK_86P016M);  //must configured first.

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PG2,
        .adc_lr_clk_pin = GPIO_FC_PG5,
        .adc_dat_pin    = GPIO_FC_PG6,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_NONE_PIN,
    };
    audio_i2s_config_t audio_i2s_config = {
        .i2s_select        = I2S0,
        .i2s_mode          = I2S_I2S_MODE,
        .pin_config        = &i2s_pin_config,
        .data_width        = I2S_BIT_32_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate       = audio_i2s_48k_config_PDM,
        .io_mode           = I2S_5_LINE_MODE,
    };
    audio_i2s_config_init(&audio_i2s_config);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_I2S0_RX, FIFO_RX_I2S_RX_CHN01_20_OR_24);
    audio_rx_dma_chain_init(FIFO0, DMA1, (unsigned short *)AUDIO_BUFF, sizeof(AUDIO_BUFF));
    audio_rx_dma_en(DMA1);
    delay_ms(5000);
    audio_rx_dma_dis(DMA1);
#endif
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED2);
}

#endif

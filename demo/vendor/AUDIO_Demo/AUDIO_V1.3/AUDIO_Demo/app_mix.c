/********************************************************************************************************
 * @file    app_mix.c
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
#if (AUDIO_MODE >= DMIC_INPUT_TO_BUF_TO_I2S)
    #include "audio_common.h"
    #define AUDIO_BUFF_SIZE 4096
signed short AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));


    #define SAMPLE_RATE AUDIO_48K
    #define DATA_WIDTH  CODEC_BIT_16_DATA
    #define RX_FIFO_NUM FIFO0
    #define TX_FIFO_NUM FIFO0 // TX Hardware is fixed to FIFO and cannot be modified.
    #define RX_DMA_CHN  DMA0
    #define TX_DMA_CHN  DMA1

#if (AUDIO_MODE == LINE_INPUT_TO_BUF_TO_I2S)
    #define INPUT_SRC   LINE_STREAM0_MONO_L
#elif (AUDIO_MODE == DMIC_INPUT_TO_BUF_TO_I2S)
    #define INPUT_SRC   DMIC_STREAM0_STEREO
#endif

    #if defined(MCU_CORE_TL721X)
unsigned short audio_i2s_48k_config[5] = {8,  625,  0, 64, 64}; //240M * 8  / 625  / 64 = 48K
unsigned short audio_i2s_32k_config[5] = {16, 1875, 0, 64, 64}; //240M * 16 / 1875 / 64 = 32K
unsigned short audio_i2s_24k_config[5] = {4,  625,  0, 64, 64}; //240M * 4  / 625  / 64 = 24K
unsigned short audio_i2s_16k_config[5] = {8,  1875, 0, 64, 64}; //240M * 8  / 1875 / 64 = 16K
unsigned short audio_i2s_12k_config[5] = {2,  625,  0, 64, 64}; //240M * 2  / 625  / 64 = 12K
    #elif defined(MCU_CORE_TL321X)
unsigned short audio_i2s_48k_config[5] = {2,  125, 0, 64, 64}; //192M * 2  / 125 / 64 = 48K
unsigned short audio_i2s_32k_config[5] = {16, 125, 6, 64, 64}; //192M * 16 / 125 / (2*6) / 64 = 32K
unsigned short audio_i2s_24k_config[5] = {1,  125, 0, 64, 64}; //192M * 1  / 125 / 64 = 24K
unsigned short audio_i2s_16k_config[5] = {8,  125, 6, 64, 64}; //192M * 8  / 125 / (2*6) / 64 = 16K
unsigned short audio_i2s_12k_config[5] = {1,  125, 1, 64, 64}; //192M * 1  / 125 / (2*1) /64 = 12K
    #elif defined(MCU_CORE_TL322X)
unsigned short audio_i2s_48k_config[5] = {16, 125, 3, 64, 64}; //144M * 16 / 125 / (2*3) / 64 = 48K
unsigned short audio_i2s_32k_config[5] = {32, 125, 9, 64, 64}; //144M * 32 / 125 / (2*9) / 64 = 32K
unsigned short audio_i2s_24k_config[5] = {8,  125, 3, 64, 64}; //144M * 8  / 125 / (2*3) / 64 = 24K
unsigned short audio_i2s_16k_config[5] = {16, 125, 9, 64, 64}; //144M * 16 / 125 / (2*9) / 64 = 16K
unsigned short audio_i2s_12k_config[5] = {4,  125, 3, 64, 64}; //144M * 4  / 125 / (2*3) / 64 = 12K
    #endif

audio_codec_stream0_input_t audio_codec_stream0_input =
    {
        .input_src     = INPUT_SRC,
        .sample_rate   = SAMPLE_RATE,
        .data_width    = DATA_WIDTH,
        .fifo_chn      = RX_FIFO_NUM,
        .dma_num       = RX_DMA_CHN,
        .data_buf      = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
};

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);

    audio_init();
    #if ((AUDIO_MODE == DMIC_INPUT_TO_BUF_TO_I2S) || (AUDIO_MODE == LINE_INPUT_TO_BUF_TO_I2S))
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_NONE_PIN,
        .dac_dat_pin    = GPIO_FC_PB6,
    };
    audio_i2s_config_t audio_i2s_config =
        {
            .i2s_select        = I2S2,
            .i2s_mode          = I2S_I2S_MODE,
            .pin_config        = &i2s_pin_config,
            .data_width        = I2S_BIT_16_DATA,
            .master_slave_mode = I2S_AS_MASTER_EN,
            .sample_rate       = (unsigned short *)&audio_i2s_48k_config,
        };
    audio_i2s_input_output_t audio_i2s_output =
        {
            .i2s_select    = audio_i2s_config.i2s_select,
            .data_width    = audio_i2s_config.data_width,
#if (AUDIO_MODE == LINE_INPUT_TO_BUF_TO_I2S)
            .i2s_ch_sel    = I2S_CHANNEL_LEFT,
#elif (AUDIO_MODE == DMIC_INPUT_TO_BUF_TO_I2S)
            .i2s_ch_sel    = I2S_CHANNEL_STEREO,
#endif
#if defined(MCU_CORE_TL322X)
            .fifo_chn      = FIFO1,
#else
            .fifo_chn      = FIFO2,
#endif
            .dma_num       = DMA1,
            .data_buf      = AUDIO_BUFF,
            .data_buf_size = sizeof(AUDIO_BUFF),
        };
#if (AUDIO_MODE == DMIC_INPUT_TO_BUF_TO_I2S)
    /****setting up the dmic's multiplexed pins****/
    audio_set_stream0_dmic_pin(GPIO_FC_PA2, GPIO_FC_PA3, GPIO_FC_PA4);
#endif

    /****stream0 line in/amic/dmic init****/
    audio_codec_stream0_input_init(&audio_codec_stream0_input);
        #if defined(MCU_CORE_TL721X)
            //audio_reset_audio_clk(64, 625, CLK_USB_MODE_OFF, SAMPLE_RATE);//Used for internal THD+N Ratio performance test.
        #elif defined(MCU_CORE_TL321X)
            //audio_reset_audio_clk(16, 125, CLK_USB_MODE_OFF, SAMPLE_RATE);//Used for internal THD+N Ratio performance test.
        #endif
    audio_set_stream0_dig_gain(CODEC_IN_D_GAIN_0_DB);
    audio_rx_dma_chain_init(audio_codec_stream0_input.fifo_chn, audio_codec_stream0_input.dma_num, (unsigned short *)audio_codec_stream0_input.data_buf, audio_codec_stream0_input.data_buf_size);
    audio_codec_stream0_input_en(audio_codec_stream0_input.dma_num);
    audio_codec_input_path_en(audio_codec_stream0_input.fifo_chn);
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num, (unsigned short *)audio_i2s_output.data_buf, audio_i2s_output.data_buf_size);
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
    #endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(200);
}

#endif

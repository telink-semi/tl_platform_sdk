/********************************************************************************************************
 * @file    hal_i2s.c
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
#include "../i2c/hal_i2c.h"
#include "../i2c/hal_es8389.h"
#include "../i2c/hal_nau8821.h"
#include "hal_i2s.h"

#if defined(MCU_CORE_TL321X)
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
#define MCLK_PIN_NUM GPIO_FC_PA0
#endif
unsigned short audio_i2s_48k_config[5] = {2, 125, 0, 64, 64};
#else
#define I2S_PIN_BCLK                PIN22//GPIO_FC_PA3, //J5
#define I2S_PIN_ADC_LR_CLK          PIN32//GPIO_FC_PB4, 
#define I2S_PIN_DAC_LR_CLK          PIN32//GPIO_FC_PB4, 
#define I2S_PIN_ADC_DAT             PIN24//GPIO_FC_PA4, 
#define I2S_PIN_DAC_DAT             PIN21//GPIO_FC_PA2,
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
#define MCLK_PIN_NUM                PIN11//GPIO_FC_PE7
#endif
#if defined(MCU_CORE_TL721X)
unsigned short audio_i2s_48k_config[5] = {8, 625, 0, 64, 64};
#else
unsigned short audio_i2s_48k_config[5] = {12, 750, 0, 64, 64};
#endif
#endif

i2s_pin_config_t i2s_pin_config = {
#if defined(MCU_CORE_TL321X)
    .bclk_pin       = GPIO_FC_PA1, //J5
    .adc_lr_clk_pin = GPIO_FC_PD1,
    .dac_lr_clk_pin = GPIO_FC_PD1,
    .adc_dat_pin    = GPIO_FC_PD4,
    .dac_dat_pin    = GPIO_FC_PB0,
#else
    // .bclk_pin       = GPIO_FC_PC1, //J6
    // .adc_lr_clk_pin = GPIO_FC_PA1,
    // .dac_lr_clk_pin = GPIO_FC_PA1,
    // .adc_dat_pin    = GPIO_FC_PB3,
    // .dac_dat_pin    = GPIO_FC_PA0,

    .bclk_pin       = (gpio_func_pin_e)I2S_PIN_BCLK, //J5
    .adc_lr_clk_pin = (gpio_func_pin_e)I2S_PIN_ADC_LR_CLK, 
    .dac_lr_clk_pin = (gpio_func_pin_e)I2S_PIN_DAC_LR_CLK, 
    .adc_dat_pin =    (gpio_func_pin_e)I2S_PIN_ADC_DAT, 
    .dac_dat_pin =    (gpio_func_pin_e)I2S_PIN_DAC_DAT,
#endif
};

audio_i2s_config_t hal_i2s_config = {
    .i2s_select        = I2S2,
    .i2s_mode          = I2S_I2S_MODE,
    .pin_config        = &i2s_pin_config,
    .data_width        = I2S_BIT_16_DATA,
    .master_slave_mode = I2S_AS_MASTER_EN,
    .sample_rate       = audio_i2s_48k_config,
};

audio_i2s_input_output_t hal_i2s_input = {
    .i2s_select    = I2S2,
    .data_width    = I2S_BIT_16_DATA,
    .i2s_ch_sel    = I2S_CHANNEL_STEREO,
#if defined(MCU_CORE_TL322X)
    .fifo_chn      = FIFO1,
#else
    .fifo_chn      = FIFO2,
#endif
    .dma_num       = I2S_MIC_DMA,
    .data_buf      = NULL,
    .data_buf_size = 0,
};

audio_i2s_input_output_t hal_i2s_output = {
    .i2s_select    = I2S2,
    .data_width    = I2S_BIT_16_DATA,
    .i2s_ch_sel    = I2S_CHANNEL_STEREO,
#if defined(MCU_CORE_TL322X)
    .fifo_chn      = FIFO1,
#else
    .fifo_chn      = FIFO2,
#endif
    .dma_num       = I2S_SPK_DMA,
    .data_buf      = NULL,
    .data_buf_size = 0,
};

void hal_i2s_init(unsigned int *mic_buff, unsigned int *spk_buff, unsigned int mic_buff_size, unsigned int spk_buff_size)
{
    hal_i2s_input.data_buf       = mic_buff;
    hal_i2s_input.data_buf_size  = mic_buff_size;
    hal_i2s_output.data_buf      = spk_buff;
    hal_i2s_output.data_buf_size = spk_buff_size;

    /***initialize the audio module***/
    audio_init();
    hal_i2c_init();
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_es8389)
    hal_es8389_init();
#endif
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
    nau8821_i2c_probe();
#endif
    /***Initialize i2s configuration***/
    audio_i2s_config_init(&hal_i2s_config);
    /***initialize the configuration of the input path of the i2s***/
    audio_i2s_input_init(&hal_i2s_input);
    /***initialize the configuration of the output path of the i2s***/
    audio_i2s_output_init(&hal_i2s_output);

#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
    delay_ms(1);

#if defined(MCU_CORE_TL321X)
    audio_set_sdm_clk_as_mclk(MCLK_PIN_NUM, 8, 125);
#elif defined(MCU_CORE_TL721X)
    audio_set_i2s_clk_as_mclk(I2S0, (gpio_func_pin_e)MCLK_PIN_NUM, 32, 640);
#elif defined(MCU_CORE_TL322X)
    // audio_set_i2s_clk_as_mclk((gpio_func_pin_e)MCLK_PIN_NUM, 1, 12);
    audio_set_codec_clk_as_mclk((gpio_func_pin_e)MCLK_PIN_NUM);
#endif
#endif
    /***configuring external codec-related registers via i2c***/
    /***initialize audio's rx dma channel***/
    audio_rx_dma_chain_init(hal_i2s_input.fifo_chn, hal_i2s_input.dma_num, (unsigned short *)hal_i2s_input.data_buf, hal_i2s_input.data_buf_size);
    /***initialize audio's tx dma channel***/
    audio_tx_dma_chain_init(hal_i2s_output.fifo_chn, hal_i2s_output.dma_num, (unsigned short *)hal_i2s_output.data_buf, hal_i2s_output.data_buf_size);
    /***enable rx channel for i2s***/
    audio_rx_dma_en(hal_i2s_input.dma_num);
    /***enable tx channel for i2s***/
    audio_tx_dma_en(hal_i2s_output.dma_num);
    /***enable clocking of i2s***/
    audio_i2s_clk_en(hal_i2s_config.i2s_select);
}

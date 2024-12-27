/********************************************************************************************************
 * @file    app_i2s.c
 *
 * @brief   This is the source file for TL721X/TL321X
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#if((AUDIO_MODE >= I2S_TO_EXT_CODEC_WM)&&(AUDIO_MODE <DMIC_INPUT_TO_BUF_TO_I2S))
#include "audio_common.h"
#include "ext_codec_wm/ext_codec_wm.h"

#define    AUDIO_BUFF_SIZE  4096
//When the i2s data bit width is selected as 16bit, the following buf is used,
//when the data bit width is selected as 20/24bit,
//you can define a buf with the same size of the signed int type for use.
signed short AUDIO_BUFF[AUDIO_BUFF_SIZE>>1] __attribute__((aligned(4)));

#if defined(MCU_CORE_TL721X)
/*Note:
 * 1.I2S input has no requirement for rx FIFO.
 * 2.The tx FIFO corresponding to the I2S output is fixed as shown in the table below (not modifiable):
 * | I2S output  |      tx FIFO    | Requirement |
 * |-------------|-----------------|-------------|
 * |    i2s0     |      fifo0      | must        |
 * |    i2s1     |      fifo1      | must        |
 * |    i2s2     |      fifo2      | must        |
 */

/**
 *                                          i2s_clk_config[2]   i2s_clk_config[3]-->lrclk_adc(sampling rate)
 *                                                  ||                  ||
 *  pll(240M default)------->div---->i2s_clk--->2 * div(div=0,bypass)--->blck----->div
 *                           ||                                         ||
 *           i2s_clk_config[0]/i2s_clk_config[1]                 i2s_clk_config[4]-->lrclk_dac(sampling rate)
 * For example:sampling rate=16K,i2s_clk_config[5]={ 4,1875,0,32,32},sampling rate=240M*(4/1875)/32=16K
 *
 */

unsigned short audio_i2s_8k_config[4][5] =
{
    {4, 1875,    0,     64,     64},
    {4, 625,    3,      32,     32},
    {1, 750,    0,      40,     40},
    {1, 625,    0,      48,     48},
};


unsigned short audio_i2s_16k_config[4][5] =
{
    {8,     1875,    0,     64,     64},
    {4,     1875,   0,      32,     32},
    {1,     375,    0,      40,     40},
    {2,     625,    0,      48,     48},
};

unsigned short audio_i2s_24k_config[4][5] =
{
    {4,     625,    0,      64,     64},
    {2,     625,    0,      32,     32},
    {1,     250,    0,      40,     40},
    {3,     625,    0,      48,     48},
};

unsigned short audio_i2s_32k_config[4][5] =
{
    {16,    1875,   0,      64,     64},
    {256,   625,    48,     32,     32},
    {2,     375,    0,      40,     40},
    {4,     625,    0,      48,     48},
};

unsigned short  audio_i2s_44k1_config[4][5] =
{
    {147,   12500,  0,      64,     64},
    {147,   25000,  0,      32,     32},
    {147,   20000,  0,      40,     40},
    {441,   50000,  0,      48,     48},
};

unsigned short  audio_i2s_48k_config[4][5] =
{
    {8,     625,    0,      64,     64},
    {4,     625,    0,      32,     32},
    {1,     125,    0,      40,     40},
    {6,     625,    0,      48,     48},
};

unsigned short  audio_i2s_96k_config[4][5] =
{
    {16,    625,    0,      64,     64},
    {8,     625,    0,      32,     32},
    {2,     125,    0,      40,     40},
    {12,    625,    0,      48,     48},
};

unsigned short  audio_i2s_192k_config[4][5] =
{
    {32,    625,    0,      64,     64},
    {16,    625,    0,      32,     32},
    {4,     125,    0,      40,     40},
    {6,     125,    0,      48,     48},
};

unsigned short audio_i2s_tdm_8k_config[6][5] =
{
    {8,     1875,   0,      128,    128},                   //TDM MODE 16bit 8Channel
    {2,     625,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {4,     1875,   0,      64,     64},                    //TDM MODE 16bit 4Channel

    {4,     625,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {3,     625,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {2,     625,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_16k_config[6][5] =
{
    {16,    1875,    0,     128,    128},                   //TDM MODE 16bit 8Channel
    {4,     625,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {8,    1875,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {8,     625,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {6,     625,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {4,     625,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_24k_config[6][5] =
{
    {8,     625,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {6,     625,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {4,     625,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {12,    625,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {9,     625,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {6,     625,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_32k_config[6][5] =
{
    {32,    1875,   0,      128,    128},                   //TDM MODE 16bit 8Channel
    {8,     625,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {16,    1875,   0,      64,     64},                    //TDM MODE 16bit 4Channel

    {16,    625,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {12,    625,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {8,     625,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_44k1_config[6][5] =
{
    {147,   6250,   0,      128,    128},                   //TDM MODE 16bit 8Channel
    {441,   25000,  0,      96,     96},                    //TDM MODE 16bit 6Channel
    {147,   12500,  0,      64,     64},                    //TDM MODE 16bit 4Channel

    {441,   12500,  0,      192,    192},                   //TDM MODE 24bit 8Channel
    {1323,  50000,  0,      144,    144},                   //TDM MODE 24bit 6Channel
    {441,   25000,  0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_48k_config[7][5] =
{
    {16,    625,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {12,    625,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {8,     625,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {24,    625,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {18,    625,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {12,    625,    0,      96,     96},                    //TDM MODE 24bit 4Channel
    {32,    625,    0,      256,    256},                   //TDM MODE 24bit/slot:32bit 8Channel
};
#elif defined(MCU_CORE_TL321X)
/*Note:
 * 1.I2S input has no requirement for rx FIFO.
 * 2.The tx FIFO corresponding to the I2S output is fixed as shown in the table below (not modifiable):
 * | I2S output  |      tx FIFO    | Requirement |
 * |-------------|-----------------|-------------|
 * |    i2s2     |      fifo2      | must        |
 */

/**
 *                                          i2s_clk_config[2]   i2s_clk_config[3]-->lrclk_adc(sampling rate)
 *                                                  ||                  ||
 *  pll(192M default)------->div---->i2s_clk--->2 * div(div=0,bypass)--->blck----->div
 *                           ||                                         ||
 *           i2s_clk_config[0]/i2s_clk_config[1]                 i2s_clk_config[4]-->lrclk_dac(sampling rate)
 * For example:sampling rate=16K, i2s_clk_config[5]={ 8,125,6,64,64}, sampling rate=192M*(8/125)/(2*6)/64=16K
 *
 */
unsigned short audio_i2s_8k_config[5]   = {8,125,12,64,64};//AUDIO_RATE_EQUAL   8000
unsigned short audio_i2s_16k_config[5][5] =
{
    { 8,    125,    6,  64, 64},        //AUDIO_RATE_EQUAL  16000  i2s_clk=12.288M
    {23,    154,    14, 64, 64},        //AUDIO_RATE_GT_L0  16001.86
    {21,    164,    12, 64, 64},        //AUDIO_RATE_GT_L1  16006.1
    {33,    221,    14, 64, 64},        //AUDIO_RATE_LT_L0  15998.71
    {27,    211,    12, 64, 64},        //AUDIO_RATE_LT_L0  15995.26
};

unsigned short audio_i2s_32k_config[5]  =    {8, 125,3,  64, 64};//32000

unsigned short  audio_i2s_48k_config[5][5] =
{
    {2,     125,    0,  64, 64},        //AUDIO_RATE_EQUAL  48000   192M*(1)/(2*6)/64=48K
    {69,    154,    14, 64, 64},        //AUDIO_RATE_GT_L0  48005
    {70,    243,    9,  64, 64},        //AUDIO_RATE_GT_L1  48010
    {91,    237,    12, 64, 64},        //AUDIO_RATE_LT_L0  47995
    {82,    233,    11, 64, 64},        //AUDIO_RATE_LT_L1  47990
};

unsigned short  audio_i2s_44k1_config[5][5] =
{
    {76,    235,    11, 64, 64},        //AUDIO_RATE_EQUAL  44100
    {101,   229,    15, 64, 64},        //AUDIO_RATE_GT_L0  44105
    {1,     17,     2,  64, 64},        //AUDIO_RATE_GT_L1  44117
    {60,    157,    13, 64, 64},        //AUDIO_RATE_LT_L0  44096
    {81,    212,    13, 64, 64},        //AUDIO_RATE_LT_L1  44085
};

unsigned short  audio_i2s_96k_config[0x04][0x05] =
{
    {4,     125,    0,      64,     64},
    {2,     125,    0,      32,     32},
    {2,     100,    0,      40,     40},
    {6,     250,    0,      48,     48},
};

unsigned short  audio_i2s_192k_config[0x04][0x05] =
{
    {8,     125,    0,      64,     64},
    {4,     125,    0,      32,     32},
    {1,     25,     0,      40,     40},
    {6,     125,    0,      48,     48},
};

unsigned short audio_i2s_tdm_8k_config[0x06][0x05] =
{
    {2,     375,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {1,     250,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {1,     375,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {1,     125,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {3,     500,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {1,     250,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_16k_config[0x06][0x05] =
{
    {4,     375,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {1,     125,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {2,     375,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {2,     125,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {3,     250,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {1,     125,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_24k_config[0x06][0x05] =
{
    {2,     125,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {3,     250,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {1,     125,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {3,     125,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {9,     500,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {3,     250,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_32k_config[0x06][0x05] =
{
    {8,     375,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {2,     125,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {4,     375,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {4,     125,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {3,     125,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {2,     125,    0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_44k1_config[0x06][0x05] =
{
    {147,   5000,   0,      128,    128},                   //TDM MODE 16bit 8Channel
    {441,   20000,  0,      96,     96},                    //TDM MODE 16bit 6Channel
    {147,   10000,  0,      64,     64},                    //TDM MODE 16bit 4Channel

    {441,   10000,  0,      192,    192},                   //TDM MODE 24bit 8Channel
    {1323,  40000,  0,      144,    144},                   //TDM MODE 24bit 6Channel
    {441,   20000,  0,      96,     96},                    //TDM MODE 24bit 4Channel
};

unsigned short audio_i2s_tdm_48k_config[0x07][0x05] =
{
    {4,     125,    0,      128,    128},                   //TDM MODE 16bit 8Channel
    {3,     125,    0,      96,     96},                    //TDM MODE 16bit 6Channel
    {2,     125,    0,      64,     64},                    //TDM MODE 16bit 4Channel

    {5,     104,    0,      192,    192},                   //TDM MODE 24bit 8Channel
    {9,     250,    0,      144,    144},                   //TDM MODE 24bit 6Channel
    {3,     125,    0,      96,     96},                    //TDM MODE 24bit 4Channel
    {16,    250,    0,      256,    256},                   //TDM MODE 24bit/slot:32bit 8Channel
};

#endif


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

    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);

#if (AUDIO_MODE== I2S_TO_EXT_CODEC_WM)
    i2s_pin_config_t i2s_pin_config = {
    .bclk_pin       = GPIO_FC_PD5,
    .adc_lr_clk_pin = GPIO_FC_PB3,
    .dac_lr_clk_pin = GPIO_FC_PB4,
    .adc_dat_pin    = GPIO_FC_PB5,
    .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_24_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_48k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_input =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA0,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };
    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA1,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s input init ****/
    audio_i2s_input_init(&audio_i2s_input);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** setting the codec clock of audio as the current mclk clock****/
    audio_set_codec_clk_as_mclk(GPIO_FC_PC6);//only set i2s as master mclk=24*/2=12M
    /**** configuring external codec-related registers via i2c***/
    audio_i2c_init_wm(GPIO_FC_PF7,GPIO_FC_PF6,(unsigned char)(sys_clk.pclk*1000*1000/(4*100000)));//set i2c frequency 100K
    /**** tx rx dma init ****/
    audio_rx_dma_chain_init(audio_i2s_input.fifo_chn, audio_i2s_input.dma_num,(unsigned short *)audio_i2s_input.data_buf,audio_i2s_input.data_buf_size);
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num,(unsigned short *)audio_i2s_output.data_buf,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_rx_dma_en(audio_i2s_input.dma_num);
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S_OUTPUT_DOUBLE_BUFF)
    /*Note:
     * The tx and rx FIFO corresponding to the I2S output is fixed as shown in the table below (not modifiable):

        | I2S 2FIFO Mode|             FIFO Usage              |
        |---------------|-------------------------------------|
        | I2S0_2FIFO    | I2S0_L->tx_FIFO0, I2S0_R->tx_FIFO1  |
        | I2S1_2FIFO    | I2S1_L->tx_FIFO1, I2S1_R->tx_FIFO2  |
        | I2S2_2FIFO    | I2S2_L->tx_FIFO1, I2S2_R->tx_FIFO2  |
     */

    __attribute__((aligned(4))) signed short buff_L[0x10] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

    __attribute__((aligned(4))) signed short buff_R[0x10] = {0xFF,0xEE,0xDD,0xCC,0xBB,0xAA,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00};

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_32k_config[0],
    };

    audio_i2s_input_output_t audio_i2s_output0 =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO1,
        .dma_num = DMA2,
        .data_buf = buff_L,
        .data_buf_size = sizeof(buff_L),
    };
    audio_i2s_input_output_t audio_i2s_output1 =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA3,
        .data_buf = buff_R,
        .data_buf_size = sizeof(buff_R),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output0);
    audio_i2s_output_init(&audio_i2s_output1);
    /**** enable the left and right channels to be configured with one fifo channel each ****/
    audio_i2s_2fifo_en(audio_i2s_config.i2s_select);
    /**** tx dma init ****/
    audio_tx_dma_chain_init(audio_i2s_output0.fifo_chn, audio_i2s_output0.dma_num,(unsigned short *)audio_i2s_output0.data_buf,audio_i2s_output0.data_buf_size);
    audio_tx_dma_chain_init(audio_i2s_output1.fifo_chn, audio_i2s_output1.dma_num,(unsigned short *)audio_i2s_output1.data_buf,audio_i2s_output1.data_buf_size);
    /**** i2s starts run ****/
    audio_tx_dma_en(audio_i2s_output0.dma_num);
    audio_tx_dma_en(audio_i2s_output1.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S2_TDM_MODE_TEST)

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,//Only i2s2 supports TDM mode
        .i2s_mode = I2S2_TDM_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_tdm_48k_config[2],
    };
    audio_i2s2_tdm_config_t audio_i2s2_tdm_config =
    {
        .tdm_mode = TDM_MODE_A,
        .slot_num = BIT16_SLOT_WIDTH,
    };

    audio_i2s_input_output_t audio_i2s_input =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,//i2s2 input tdm mode only support FIFO2.
        .dma_num = DMA0,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_i2s2_tdm_input_output_t audio_i2s2_tdm_input =
    {
        .tdm_chn = TDM_4CHANNEL,
        .data_width = I2S_BIT_16_DATA,
        .burst_size = DMA_BURST_2_WORD,
        .fifo_chn   = audio_i2s_input.fifo_chn,
        .dma_num    = audio_i2s_input.dma_num,
    };

    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA1,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_i2s2_tdm_input_output_t audio_i2s2_tdm_output =
    {
        .tdm_chn = TDM_4CHANNEL,
        .data_width = I2S_BIT_16_DATA,
        .burst_size = DMA_BURST_2_WORD,
        .fifo_chn   = audio_i2s_output.fifo_chn,
        .dma_num    = audio_i2s_output.dma_num,
    };


    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s tdm mode config init****/
    audio_i2s2_tdm_config_init(&audio_i2s2_tdm_config);
    /**** i2s input init ****/
    audio_i2s_input_init(&audio_i2s_input);
    /**** i2s tdm mode input init ****/
    audio_i2s2_tdm_input_init(&audio_i2s2_tdm_input);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** i2s tdm mode output init ****/
    audio_i2s2_tdm_output_init(&audio_i2s2_tdm_output);
    /**** rx tx dma init ****/
    audio_rx_dma_chain_init(audio_i2s_input.fifo_chn, audio_i2s_input.dma_num,(unsigned short *)audio_i2s_input.data_buf,audio_i2s_input.data_buf_size);
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num,(unsigned short *)audio_i2s_output.data_buf,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_rx_dma_en(audio_i2s_input.dma_num);
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S_TO_2LANE_RX)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_NONE_PIN,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_48k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_input =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA0,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s input init ****/
    audio_i2s_input_init(&audio_i2s_input);
    /**** enable 2lane rx mode for i2s ****/
    audio_i2s_2lane_rx_en(audio_i2s_config.i2s_select);
    /**** set rx dma channel burst size ****/
    audio_set_dma_rx_burst(audio_i2s_input.fifo_chn,audio_i2s_input.dma_num,DMA_BURST_2_WORD);
    /**** rx dma init ****/
    audio_rx_dma_chain_init(audio_i2s_input.fifo_chn,audio_i2s_input.dma_num,(unsigned short *)audio_i2s_input.data_buf,audio_i2s_input.data_buf_size);
    /**** i2s starts run ****/
    audio_rx_dma_en(audio_i2s_input.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S_TO_2LANE_TX)
    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_NONE_PIN,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_48k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA1,
        .data_buf = SinData_16bit_ap,
        .data_buf_size = sizeof(SinData_16bit_ap),
    };


    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** enable 2lane tx mode for i2s***/
    audio_i2s_2lane_tx_en(audio_i2s_config.i2s_select);
    /**** set tx dma channel burst size ****/
    audio_set_dma_tx_burst(audio_i2s_output.fifo_chn,audio_i2s_output.dma_num,DMA_BURST_2_WORD);
    /**** tx dma init ****/
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num,(unsigned short *)audio_i2s_output.data_buf,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S_TO_TARGET)

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_192k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_input =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO1,
        .dma_num = DMA0,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };
    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA1,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s input init ****/
    audio_i2s_input_init(&audio_i2s_input);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** sets the threshold time at which the i2s is triggered(the i2s is only triggered to work if the threshold is reached.)****/
    audio_set_i2s_target_value(audio_i2s_config.i2s_select,stimer_get_tick()+1000);
    /**** enable threshold trigger***/
    audio_i2s_schedule_en(audio_i2s_config.i2s_select);
    /**** rx tx dma init ****/
    audio_rx_dma_chain_init(audio_i2s_input.fifo_chn, audio_i2s_input.dma_num,(unsigned short *)audio_i2s_input.data_buf,audio_i2s_input.data_buf_size);
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num,(unsigned short *)audio_i2s_output.data_buf,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_rx_dma_en(audio_i2s_input.dma_num);
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == I2S_ASCl_TEST)
    /*Note:
     * 1. Only supports 16bits
     * 2. ASCL only supports up-sampling conversion.
     * 3. The ASCL corresponding to the I2S output is fixed as shown in the table below (not modifiable):

        | I2S   |  ASCL     |
        |-------|-----------|
        | I2S0  |  ASCL0    |
        | I2S1  |  ASCL1    |
        | I2S2  |  ASCL2    |
     */

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_96k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2,
        .dma_num = DMA1,
        .data_buf = sin_48k_d2,
        .data_buf_size = sizeof(sin_48k_d2),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** i2s ascl config ****/
    audio_set_i2s_ascl_en(audio_i2s_config.i2s_select);
    audio_set_ascl_gain(ASCL2,ASCL_OUT_D_GAIN_0_DB);
    audio_ascl_set_conversion_sample_rate(ASCL2,AUDIO_ASCL_48K,AUDIO_ASCL_96K,AUDIO_STEREO);
    /**** tx dma init ****/
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn, audio_i2s_output.dma_num,(unsigned short *)audio_i2s_output.data_buf,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);
#elif(AUDIO_MODE == AUDIO_FIFO_IRQ_TEST)
#define FIFO0_NUM            FIFO0
#define FIFO2_NUM            FIFO2

#define RX_DMA_CHN           DMA0
#define TX_DMA_CHN           DMA1

    i2s_pin_config_t i2s_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };

    audio_i2s_config_t audio_i2s_config =
    {
        .i2s_select = I2S2,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s_pin_config,
        .data_width = I2S_BIT_16_DATA,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)&audio_i2s_48k_config[0],
    };
    audio_i2s_input_output_t audio_i2s_input =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO0_NUM,
        .dma_num = DMA0,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };
    audio_i2s_input_output_t audio_i2s_output =
    {
        .i2s_select = audio_i2s_config.i2s_select,
        .data_width = audio_i2s_config.data_width,
        .i2s_ch_sel = I2S_CHANNEL_STEREO,
        .fifo_chn = FIFO2_NUM,
        .dma_num = TX_DMA_CHN,
        .data_buf = AUDIO_BUFF,
        .data_buf_size = sizeof(AUDIO_BUFF),
    };

    audio_init();
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s_config);
    /**** i2s input init ****/
    audio_i2s_input_init(&audio_i2s_input);
    /**** i2s output init ****/
    audio_i2s_output_init(&audio_i2s_output);
    /**** enable audio fifo interrupt****/
    plic_interrupt_enable(IRQ_DFIFO);
    core_interrupt_enable();
    /**** setting i2s audio rx fifo thresholds ****/
    audio_set_rx_fifo_threshold(audio_i2s_input.fifo_chn,AUDIO_BUFF_SIZE/2);
    /**** setting i2s audio tx fifo thresholds ***/
    audio_set_tx_fifo_threshold(audio_i2s_output.fifo_chn,AUDIO_BUFF_SIZE/2);
    /**** enable rx fifo interrupt for i2s ****/
    audio_rxfifo_irq_en(audio_i2s_input.fifo_chn);
    /**** enable tx fifo interrupt for i2s ****/
    audio_txfifo_irq_en(audio_i2s_output.fifo_chn);
    /**** rx tx dma init ****/
    audio_rx_dma_chain_init(audio_i2s_input.fifo_chn, audio_i2s_input.dma_num,(unsigned short *)AUDIO_BUFF,audio_i2s_input.data_buf_size);
    audio_tx_dma_chain_init(audio_i2s_output.fifo_chn,audio_i2s_output.dma_num,(unsigned short *)AUDIO_BUFF,audio_i2s_output.data_buf_size);
    /**** i2s starts run****/
    audio_rx_dma_en(audio_i2s_input.dma_num);
    audio_tx_dma_en(audio_i2s_output.dma_num);
    audio_i2s_clk_en(audio_i2s_config.i2s_select);

#elif(AUDIO_MODE == I2S_ALIGN)



#define I2S1_I2S2_ALIGN_MODE          0
#define I2S0_I2S1_ALIGN_MODE          1
#define I2S0_I2S1_I2S2_ALIGN_MODE     2
#define I2S_ALIGN_MODE  I2S0_I2S1_ALIGN_MODE

#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE)
#define I2S_ALIGN_INPUT_PATH I2S0_IN_FIFO
#define RX_FIFO_NUM FIFO0
#define TX_FIFO_NUM FIFO0
#elif(I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE)
#define I2S_ALIGN_INPUT_PATH I2S1_IN_FIFO
#define RX_FIFO_NUM FIFO1
#define TX_FIFO_NUM FIFO1
#elif(I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
#define I2S_ALIGN_INPUT_PATH I2S0_IN_FIFO
#define RX_FIFO_NUM FIFO0
#define TX_FIFO_NUM FIFO0
#endif

#define SAMPLE_RATE &audio_i2s_48k_config[0]
#define DATA_WIDTH I2S_BIT_24_DATA
#define CHANNEL_SELECT AUDIO_STEREO
#define RX_DMA_CHN DMA0
#define TX_DMA_CHN DMA1

#if defined(MCU_CORE_TL721X)

    /*Note:
          1. I2S align mode function description:
             supports 3 alignment modes (I2S0_I2S1_ALIGN/I2S1_I2S2_ALIGN/I2S0_I2S1_I2S2_ALIGN)
             When the sys_timer count to the set threshold ticks, I2S generate the same phase clock(LR_CLK) so as to achieve phase alignment .
          2. Initialization order requirements for align mode:must call the audio_set_i2s_align_en() to enable align mode function first, and then initialize the relevant configuration of I2S,
             step(1) Must call the audio_set_i2s_align_en() first ,and set data format for align mode .
             step(2) Configure the initialization of I2S
             step(3) Call the audio_set_i2s_align_mask_dis() to disable the align mask
             step(4) Set sys_timer threshold ticks
             step(5) Call the audio_set_i2s_align_mask_en() to enable the align mask.
        *3:The I2S Alignment Mode usage restrictions are listed in the table below
           | I2S Channel Align         | FIFO Usage          | Input Path Setting| channel_select& data_width                 |
           |---------------------------|---------------------|-------------------|-----------------                           |
           | I2S0_I2S1_ALIGN           | RX_FIFO0,TX_FIFO0   | I2S0_IN_FIFO      | All support                                |
           | I2S1_I2S2_ALIGN           | RX_FIFO1,TX_FIFO1   | I2S1_IN_FIFO      | All support                                |
           | I2S0_I2S1_I2S2_ALIGN      | RX_FIFO0,TX_FIFO0   | I2S0_IN_FIFO      | AUDIO_MONO&I2S_BIT_16_DATA is not supported|
        */

#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    i2s_pin_config_t i2s0_pin_config = {
        .bclk_pin       = GPIO_FC_PD5,
        .adc_lr_clk_pin = GPIO_FC_PB3,
        .dac_lr_clk_pin = GPIO_FC_PB4,
        .adc_dat_pin    = GPIO_FC_PB5,
        .dac_dat_pin    = GPIO_FC_PB6,
    };
    audio_i2s_config_t audio_i2s0_config =
   {
       .i2s_select = I2S0,
       .i2s_mode = I2S_I2S_MODE,
       .pin_config = &i2s0_pin_config,
       .data_width = DATA_WIDTH,
       .master_slave_mode = I2S_AS_MASTER_EN,
       .sample_rate = (unsigned short *)SAMPLE_RATE,
   };
#endif

#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    i2s_pin_config_t i2s1_pin_config = {
        .bclk_pin       = GPIO_FC_PB7,
        .adc_lr_clk_pin = GPIO_FC_PC5,
        .dac_lr_clk_pin = GPIO_FC_PC6,
        .adc_dat_pin    = GPIO_FC_PC7,
        .dac_dat_pin    = GPIO_FC_PB0,
    };
    audio_i2s_config_t audio_i2s1_config =
    {
        .i2s_select = I2S1,
        .i2s_mode = I2S_I2S_MODE,
        .pin_config = &i2s1_pin_config,
        .data_width = DATA_WIDTH,
        .master_slave_mode = I2S_AS_MASTER_EN,
        .sample_rate = (unsigned short *)SAMPLE_RATE,
    };
#endif
#if(I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE ||I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    i2s_pin_config_t i2s2_pin_config = {
        .bclk_pin       = GPIO_FC_PF0,
        .adc_lr_clk_pin = GPIO_FC_PF1,
        .dac_lr_clk_pin = GPIO_FC_PF2,
        .adc_dat_pin    = GPIO_FC_PF3,
        .dac_dat_pin    = GPIO_FC_PB1,
    };
    audio_i2s_config_t audio_i2s2_config =
   {
       .i2s_select = I2S2,
       .i2s_mode = I2S_I2S_MODE,
       .pin_config = &i2s2_pin_config,
       .data_width = DATA_WIDTH,
       .master_slave_mode = I2S_AS_MASTER_EN,
       .sample_rate = (unsigned short *)SAMPLE_RATE,
   };
#endif

    audio_init();
    //step(1)
    /**** align mode initialization ****/
    audio_i2s_align_en();
    audio_set_dma_rx_burst(RX_FIFO_NUM,RX_DMA_CHN,DMA_BURST_2_WORD);
    audio_set_i2s_align_mode(I2S_ALIGN_MODE);
    audio_set_i2s_align_data_width(I2S_ALIGN_MODE,CHANNEL_SELECT,DATA_WIDTH);
    //step(2)
    /**** setting the clock of i2s1 as the current i2s clock****/
    audio_i2s_set_mclk(GPIO_FC_PC4);//only set i2s as master mclk=24*/2=12M
    /**** configuring external codec-related registers via i2c***/
    audio_i2c_init_wm(GPIO_FC_PF7,GPIO_FC_PF6,(unsigned char)(sys_clk.pclk*1000*1000/(4*100000)));//set i2c frequency 100K
#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s0_config);
    /**** i2s txfifo enable ****/
    audio_txfifo_en((audio_fifo_chn_e)audio_i2s0_config.i2s_select);
#endif
#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s1_config);
    /**** i2s txfifo enable ****/
    audio_txfifo_en((audio_fifo_chn_e)audio_i2s1_config.i2s_select);
#endif
#if(I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE ||I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    /**** i2s config init ****/
    audio_i2s_config_init(&audio_i2s2_config);
    /**** i2s txfifo enable ****/
    audio_txfifo_en((audio_fifo_chn_e)audio_i2s2_config.i2s_select);
#endif
    /**** i2s rxfifo enable ****/
    audio_rxfifo_en(RX_FIFO_NUM);
    /**** i2s fifo set input path ****/
    audio_data_fifo_input_path_sel(RX_FIFO_NUM,I2S_ALIGN_INPUT_PATH);
    /**** rx tx dma init ****/
    audio_rx_dma_chain_init(RX_FIFO_NUM, RX_DMA_CHN,(unsigned short *)AUDIO_BUFF,AUDIO_BUFF_SIZE);
    audio_tx_dma_chain_init(TX_FIFO_NUM, TX_DMA_CHN,(unsigned short *)AUDIO_BUFF,AUDIO_BUFF_SIZE);
    /**** i2s starts run ****/
    audio_rx_dma_en(RX_DMA_CHN);
    audio_tx_dma_en(TX_DMA_CHN);
#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    audio_i2s_clk_en(audio_i2s0_config.i2s_select);
#endif
#if(I2S_ALIGN_MODE == I2S0_I2S1_ALIGN_MODE || I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE || I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    audio_i2s_clk_en(audio_i2s1_config.i2s_select);
#endif
#if(I2S_ALIGN_MODE == I2S1_I2S2_ALIGN_MODE ||I2S_ALIGN_MODE == I2S0_I2S1_I2S2_ALIGN_MODE)
    audio_i2s_clk_en(audio_i2s2_config.i2s_select);
#endif
    //step(3)
    audio_i2s_align_mask_dis();
    //step(4)
    audio_set_i2s_align_th_tick(stimer_get_tick()+64);
    //step(5)
    audio_i2s_align_mask_en();
#endif
#endif
}

#if(AUDIO_MODE==AUDIO_FIFO_IRQ_TEST)
volatile unsigned int irq_cnt[2];
volatile unsigned int  fifo_dma_ptr_test[4];

_attribute_ram_code_sec_ void audio_irq_handler(void)
{
    if(audio_get_irq_status(AUDIO_RX_FIFO0_IRQ))//rx0
    {
        audio_clr_irq_status(AUDIO_RX_FIFO0_IRQ);
        fifo_dma_ptr_test[0]=audio_get_rx_dma_wptr(RX_DMA_CHN)-(unsigned int )AUDIO_BUFF;
        fifo_dma_ptr_test[1]=audio_get_rx_wptr(FIFO0_NUM);
        fifo_dma_ptr_test[1] = fifo_dma_ptr_test[1]<<2;// =fifo_dma_ptr_test[0]=fifo_dma_ptr_test[1]=(AUDIO_BUFF_SIZE/2)+4
        gpio_toggle(LED2);
        irq_cnt[0]++;

    }
    if(audio_get_irq_status(AUDIO_TX_FIFO2_IRQ))//tx0
    {
        audio_clr_irq_status(AUDIO_TX_FIFO2_IRQ);
        fifo_dma_ptr_test[2]=audio_get_tx_dma_rptr(TX_DMA_CHN)-(unsigned int )AUDIO_BUFF;
        fifo_dma_ptr_test[3]=audio_get_tx_rptr(FIFO2_NUM);
        fifo_dma_ptr_test[3] = fifo_dma_ptr_test[3]<<2;// =(AUDIO_BUFF_SIZE/2)+4
        gpio_toggle(LED3);
        irq_cnt[1]++;
    }
}
PLIC_ISR_REGISTER(audio_irq_handler, IRQ_DFIFO)
#endif


void main_loop (void)
{
    gpio_toggle(LED1);
    delay_ms(200);
}

#endif







/********************************************************************************************************
 * @file    app_eq.c
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
#if (AUDIO_MODE == EQ_DEMO)
    #include "app_filter_data.h"
    #define RAM_TO_HAC_TO_RAM_MONO   (1) /* data route: ram -> hac -> ram. mono*/
    #define RAM_TO_HAC_TO_RAM_STEREO (2) /* data route: ram -> hac -> ram. stereo*/
    #define RAM_TO_HAC_TO_RAM_4CH    (4) /* data route: ram -> hac -> ram. 4ch*/
    #define RAM_TO_HAC_TO_RAM_6CH    (6) /* data route: ram -> hac -> ram. 6ch*/
    #define RAM_TO_HAC_TO_RAM_8CH    (8) /* data route: ram -> hac -> ram. 8ch*/

    #define EQ_MODE                  RAM_TO_HAC_TO_RAM_MONO


    #define HAC_FIRST_HAC2_EN        0
    #define HAC_EQ_CHANNEL_SELECT    HAC_CHN0 /* hac channel 0-3. If use more than 1 data path; hac2 or hac3 should be selected. */

    #define AUDIO_DMA_CHANNEL_TX     DMA0
    #define AUDIO_DMA_CHANNEL_RX     DMA1
    #define AUDIO_FIFO_CHANNEL       FIFO0
    #define ASRC_FS                  48000
    #define PPM                      0

    #define EQ_TDM_CH_NUM            EQ_MODE
    #define EQ_SINGLE_CH_LENGTH      1024
    #define EQ_TDM_DATA_LENGTH       (EQ_TDM_CH_NUM * EQ_SINGLE_CH_LENGTH)

    #define DMA_EN                   1

signed int biq[HAC_BIQUAD_CNT][5] =
    {
        {84990913, -168967346, 83977982, -534321664, 265891104},
        {82787407, -163199524, 80478398, -516082208, 247856352},
        {84392858, -160103618, 76297548, -506292096, 239712224},
        {85537374, -157496920, 73571731, -498048992, 234711696},
        {80532961, -115971489, 46903317, -366734048, 134553440},
        {56232092, -61261818,  24715454, -193726880, -12456842},
        {64360760, -52568576,  23113383, -166236432, 8182074  },
        {60685287, -37330116,  28670378, -118048192, 14131978 },
        {84990913, -168967346, 83977982, -534321664, 265891104},
        {82787407, -163199524, 80478398, -516082208, 247856352},
};

int AUDIO_BUFFER_IN[EQ_TDM_DATA_LENGTH];
int AUDIO_BUFFER_OUT[EQ_TDM_DATA_LENGTH];

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M);
    audio_hac_clk_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_set_data_src(HAC_EQ_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_EQ_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

    #if (EQ_MODE == RAM_TO_HAC_TO_RAM_MONO)

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_EQ_CHANNEL_SELECT, i, biq[i]);
    };
    //eq_config_en
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_bypass_asrc(HAC_EQ_CHANNEL_SELECT, 1);

    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM);  /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_ch_en(HAC_EQ_CHANNEL_SELECT, 1);
    if ((HAC_EQ_CHANNEL_SELECT == HAC_CHN2) || (HAC_EQ_CHANNEL_SELECT == HAC_CHN3)) {
        audio_hac_set_tdm_num(HAC_EQ_CHANNEL_SELECT, EQ_TDM_CH_NUM);
    }

    audio_matrix_set_hac_route(HAC_EQ_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_EQ_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);

    #elif (EQ_MODE == RAM_TO_HAC_TO_RAM_STEREO)

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_EQ_CHANNEL_SELECT, i, biq[i]);
    };
    //eq_config_en
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_bypass_asrc(HAC_EQ_CHANNEL_SELECT, 1);

    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM);  /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_ch_en(HAC_EQ_CHANNEL_SELECT, 1);
    audio_hac_set_tdm_num(HAC_EQ_CHANNEL_SELECT, EQ_TDM_CH_NUM);
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_2CH);

    audio_matrix_set_hac_route(HAC_EQ_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_EQ_CHANNEL_SELECT, FIFO_RX_HAC23_STEREO_20_OR_24BIT);

    #elif (EQ_MODE == RAM_TO_HAC_TO_RAM_4CH)

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_EQ_CHANNEL_SELECT, i, biq[i]);
    };
    //eq_config_en
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);
    audio_hac_bypass_asrc(HAC_EQ_CHANNEL_SELECT, 1);

    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM);  /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_EQ_CHANNEL_SELECT, 36864000 / ASRC_FS / EQ_TDM_CH_NUM); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_ch_en(HAC_EQ_CHANNEL_SELECT, 1);
    audio_hac_set_tdm_num(HAC_EQ_CHANNEL_SELECT, EQ_TDM_CH_NUM);
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_4CH);

    audio_matrix_set_hac_route(HAC_EQ_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_EQ_CHANNEL_SELECT, FIFO_RX_HAC23_4_CHN_20_OR_24BIT);

    #elif (EQ_MODE == RAM_TO_HAC_TO_RAM_6CH)
    audio_hac_clk_en(HAC_CHN2);
    audio_hac_clk_en(HAC_CHN3);

    audio_hac_set_data_src(HAC_CHN2, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN2, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHN3, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN3, HAC_OUTPUT_DATA_MATRIX);

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_CHN2, i, biq[i]);
        audio_hac_update_biquad_coef(HAC_CHN3, i, biq[i]);
    };
    //eq_config_en
    audio_hac_eq_config_en(HAC_CHN2);
    audio_hac_eq_config_en(HAC_CHN3);
    audio_hac_bypass_asrc(HAC_CHN2, 1);
    audio_hac_bypass_asrc(HAC_CHN3, 1);

    audio_hac_asrc_ch_en(HAC_CHN2, 1);
    audio_hac_asrc_ch_en(HAC_CHN3, 1);

    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_6CH);
        #if HAC_FIRST_HAC2_EN
    unsigned char hac2_ch_num = 4;
    unsigned char hac3_ch_num = 2;
        #else
    unsigned char hac2_ch_num = 2;
    unsigned char hac3_ch_num = 4;
        #endif
    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_CHN2, 36864000 / ASRC_FS / 4);            /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_in_data_rate(HAC_CHN3, 36864000 / ASRC_FS / 4);            /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN2, 36864000 / ASRC_FS / hac2_ch_num); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN3, 36864000 / ASRC_FS / hac3_ch_num); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_set_tdm_num(HAC_CHN2, hac2_ch_num);
    audio_hac_set_tdm_num(HAC_CHN3, hac3_ch_num);

        #if HAC_FIRST_HAC2_EN
    audio_hac_set_in_data_rate_6ch(HAC_CHN3, 36864000 / ASRC_FS / 4 * 3);
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_6_CHN_20_OR_24BIT);
    audio_hac_asrc_6ch_first_en(HAC_CHN2);
        #else
    audio_hac_set_in_data_rate_6ch(HAC_CHN2, 36864000 / ASRC_FS / 4 * 3);
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_6_CHN_20_OR_24BIT);
    audio_hac_asrc_6ch_first_en(HAC_CHN3);
        #endif
    #elif (EQ_MODE == RAM_TO_HAC_TO_RAM_8CH)
    audio_hac_clk_en(HAC_CHN2);
    audio_hac_clk_en(HAC_CHN3);

    audio_hac_set_data_src(HAC_CHN2, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN2, HAC_OUTPUT_DATA_MATRIX);
    audio_hac_set_data_src(HAC_CHN3, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHN3, HAC_OUTPUT_DATA_MATRIX);

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_CHN2, i, biq[i]);
        audio_hac_update_biquad_coef(HAC_CHN3, i, biq[i]);
    };
    //eq_config_en
    audio_hac_eq_config_en(HAC_CHN2);
    audio_hac_eq_config_en(HAC_CHN3);
    audio_hac_bypass_asrc(HAC_CHN2, 1);
    audio_hac_bypass_asrc(HAC_CHN3, 1);

    /* If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate. */
    audio_hac_set_in_data_rate(HAC_CHN2, 36864000 / ASRC_FS / 4);  /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN2, 36864000 / ASRC_FS / 4); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_set_in_data_rate(HAC_CHN3, 36864000 / ASRC_FS / 4);  /* 36.864MHz/FS_IN/CH_NUM. */
    audio_hac_set_out_data_rate(HAC_CHN3, 36864000 / ASRC_FS / 4); /* 36.864MHz/FS_OUT/CH_NUM. */
    audio_hac_asrc_ch_en(HAC_CHN2, 1);
    audio_hac_set_tdm_num(HAC_CHN2, 4);
    audio_hac_asrc_ch_en(HAC_CHN3, 1);
    audio_hac_set_tdm_num(HAC_CHN3, 4);
    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_8CH);
        #if HAC_FIRST_HAC2_EN
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC2_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_8_CHN_20_OR_24BIT);
    audio_hac_asrc_8ch_first_en(HAC_CHN2);
        #else
    audio_matrix_set_hac_route(HAC_CHN2, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC2_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_hac_route(HAC_CHN3, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC3_TDM_20_OR_24_BIT_HAC3_FIRST);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_TDM01_DATA23, FIFO_RX_HAC23_8_CHN_20_OR_24BIT);
    audio_hac_asrc_8ch_first_en(HAC_CHN3);
        #endif

    #endif

    for (int i = 0; i < EQ_SINGLE_CH_LENGTH; i++) {
        for (int j = 0; j < EQ_TDM_CH_NUM; j++) {
            AUDIO_BUFFER_IN[i * EQ_TDM_CH_NUM + j] = eq_data_in[i];
        }
    }
    #if (DMA_EN == 1)
    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER_OUT, sizeof(AUDIO_BUFFER_OUT));
    dma_llp_dis(AUDIO_DMA_CHANNEL_RX); /* dis llp */
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)AUDIO_BUFFER_IN, sizeof(AUDIO_BUFFER_IN));
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    dma_llp_dis(AUDIO_DMA_CHANNEL_TX); /* dis llp */
    /* At ASRC_FS sample rate, it takes at least (EQ_TDM_DATA_LENGTH / (ASRC_FS/1000))ms for the DMA to finish transferring the audio data.
     * Wait twice as long to ensure transmission is completed.*/
    delay_ms(EQ_TDM_DATA_LENGTH / (ASRC_FS / 1000) * 2);
    #else
    for (int i = 0; i < EQ_SINGLE_CH_LENGTH; i++) {
        for (int j = 0; j < EQ_TDM_CH_NUM; j++) {
            write_reg32(REG_AUDIO_FIFO_ADDR(AUDIO_FIFO_CHANNEL), AUDIO_BUFFER_IN[i * EQ_TDM_CH_NUM + j]);
        }
        delay_us(100);
        for (int j = 0; j < EQ_TDM_CH_NUM; j++) {
            AUDIO_BUFFER_OUT[i * EQ_TDM_CH_NUM + j] = read_reg32(REG_AUDIO_FIFO_ADDR(AUDIO_FIFO_CHANNEL));
        }
    }

    #endif
    for (int i = 0; i < EQ_SINGLE_CH_LENGTH; i++) {
        for (int j = 0; j < EQ_TDM_CH_NUM; j++) {
            if (AUDIO_BUFFER_OUT[i * EQ_TDM_CH_NUM + j] != eq_data_out[i]) {
                AUDIO_BUFFER_IN[0] = i;                                       //for debug
                AUDIO_BUFFER_IN[1] = j;                                       //for debug
                AUDIO_BUFFER_IN[2] = AUDIO_BUFFER_OUT[i * EQ_TDM_CH_NUM + j]; //for debug
                AUDIO_BUFFER_IN[3] = eq_data_out[i];                          //for debug
                while (1)
                    ;
            }
        }
    }
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(200);
}
#endif

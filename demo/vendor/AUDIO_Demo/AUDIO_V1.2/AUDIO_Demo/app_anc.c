/********************************************************************************************************
 * @file    app_anc.c
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
#if (AUDIO_MODE == ANC_DEMO)
#include "app_filter_data.h"
#define RAM_TO_HAC_TO_ANC_TO_RAM_FF   (1) /* data route: ram -> hac -> ANC -> ram. Feed-Forward */
#define RAM_TO_HAC_TO_ANC_TO_RAM_FB   (2) /* data route: ram -> hac -> ANC -> ram. Feed-Back */
#define RAM_TO_HAC_TO_ANC_TO_RAM_HB   (3) /* data route: ram -> hac -> ANC -> ram. Hybrid */
#define ANC_FILTER_MODE RAM_TO_HAC_TO_ANC_TO_RAM_FF

#define ANC_CHANNEL_SELECT ANC0

#define HAC_CHANNEL_SELECT HAC_CHN0
#define AUDIO_ANC_HAC_DATA_PATH HAC_CHN0_DATA0

#define ANC_FS       384000

#define AUDIO_DMA_CHANNEL_TX    DMA0
#define AUDIO_DMA_CHANNEL_RX    DMA1
#define AUDIO_FIFO_CHANNEL      FIFO0

int AUDIO_BUFFER_IN[2048];
int AUDIO_BUFFER_OUT[4096];
int AUDIO_BUFFER_OUT1[2048];

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    clock_pll_audio_init(PLL_AUDIO_CLK_184P32M);
    audio_init(PLL_AUDIO_CLK_184P32M);
    audio_hac_clk_en(HAC_CHANNEL_SELECT);
    audio_anc_clk_en(ANC_CHANNEL_SELECT);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);

#if (ANC_FILTER_MODE == RAM_TO_HAC_TO_ANC_TO_RAM_FF)
    // hac config
    audio_hac_bypass_eq(HAC_CHANNEL_SELECT);
    audio_hac_bypass_asrc(HAC_CHANNEL_SELECT, 1);

    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_IN/CH_NUM.
    audio_hac_set_out_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_OUT/CH_NUM.
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT, 1);
    if((HAC_CHANNEL_SELECT == HAC_CHN2) || (HAC_CHANNEL_SELECT == HAC_CHN3))
        audio_hac_set_tdm_num(HAC_CHANNEL_SELECT, 1);

    audio_matrix_set_hac_route(HAC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
    //audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);

    // anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FF);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_FIRST);
    audio_anc_latch_ref_mic_gain(ANC_CHANNEL_SELECT);
    audio_anc_latch_wz_fir_gain(ANC_CHANNEL_SELECT);
    audio_anc_set_wz_iir_taps(ANC_CHANNEL_SELECT, 5);
    audio_anc_update_wz_iir_coef(ANC_CHANNEL_SELECT, wzbiq, 5);
    audio_anc_set_wz_fir_taps(ANC_CHANNEL_SELECT, 390);

    audio_anc_update_wz_fir_coef(ANC_CHANNEL_SELECT, fir390_ff, sizeof(fir390_ff) / sizeof(fir390_ff[0]));

    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC_REF_ROUTE_HAC_DATA0 + AUDIO_ANC_HAC_DATA_PATH, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_ANC0 + ANC_CHANNEL_SELECT, FIFO_RX_ANC_SPEAKER_OUT);

    audio_anc_set_resample_in_out_fs(ANC_CHANNEL_SELECT, ANC_RESAMPLE_OTHERS_DECISION_FS,
            ANC_RESAMPLE_IN_FS_48K, ANC_FS==384000?ANC_RESAMPLE_OUT_FS_384K:ANC_RESAMPLE_OUT_FS_768K);

    /* rx dma config */
    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER_OUT, 2048 * 4);
    dma_llp_dis(AUDIO_DMA_CHANNEL_RX); /* dis llp */
    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
    /* tx dma config */
    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)anc_data_in_ff, 2048 * 4);
    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
    dma_llp_dis(AUDIO_DMA_CHANNEL_TX); /* dis llp */
    /* At ASRC_FS sample rate, it takes at least (EQ_TDM_DATA_LENGTH / (ASRC_FS/1000))ms for the DMA to finish transferring the audio data.
     * Wait twice as long to ensure transmission is completed.*/
    delay_ms(1000);
    for(unsigned int i = 0; i < 2048; i++)
    {
        if (anc_data_out_ff[i] != AUDIO_BUFFER_OUT[i])
        {
            AUDIO_BUFFER_OUT[0] = i;
            AUDIO_BUFFER_OUT[1] = anc_data_out_ff[i];
            AUDIO_BUFFER_OUT[2] = AUDIO_BUFFER_OUT[i];
            while(1);
        }
    }
#elif (ANC_FILTER_MODE == RAM_TO_HAC_TO_ANC_TO_RAM_FB)
    // hac config
    audio_hac_bypass_eq(HAC_CHANNEL_SELECT);
    audio_hac_bypass_asrc(HAC_CHANNEL_SELECT, 1);

    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_IN/CH_NUM.
    audio_hac_set_out_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_OUT/CH_NUM.
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT, 1);
    if((HAC_CHANNEL_SELECT == HAC_CHN2) || (HAC_CHANNEL_SELECT == HAC_CHN3))
        audio_hac_set_tdm_num(HAC_CHANNEL_SELECT, 1);

    audio_matrix_set_hac_route(HAC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + FIFO0, HAC_20_OR_24_BIT);
    //audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_CHANNEL_SELECT, FIFO_RX_HAC_MONO_20_OR_24BIT);

    // anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_FB);
    audio_anc_set_adder2_mode(ANC_CHANNEL_SELECT, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_FIRST);
    audio_anc_latch_wz_fir_gain(ANC_CHANNEL_SELECT);
    audio_anc_set_wz_iir_taps(ANC_CHANNEL_SELECT, 5);
    audio_anc_update_wz_iir_coef(ANC_CHANNEL_SELECT, wzbiq, 5);
    audio_anc_set_wz_fir_taps(ANC_CHANNEL_SELECT, 390);
    audio_anc_update_wz_fir_coef(ANC_CHANNEL_SELECT, fir390_fb_hb, sizeof(fir390_fb_hb) / sizeof(fir390_fb_hb[0]));
    audio_anc_set_cz_iir_taps(ANC_CHANNEL_SELECT, 0, 5);
    audio_anc_update_cz_iir_coef(ANC_CHANNEL_SELECT, 0, wzbiq, 5);
    audio_anc_set_cz_fir_taps(ANC_CHANNEL_SELECT, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC_CHANNEL_SELECT, 0, fir390_fb_hb, 0x96);
    audio_anc_set_cz_iir_taps(ANC_CHANNEL_SELECT, 2, 5);
    audio_anc_update_cz_iir_coef(ANC_CHANNEL_SELECT, 2, wzbiq, 5);
    audio_anc_set_cz_fir_taps(ANC_CHANNEL_SELECT, 2, 0x96);
    audio_anc_update_cz_fir_coef(ANC_CHANNEL_SELECT, 2, fir390_fb_hb, 0x96);// fir_taps=150

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC_ERR_ROUTE_HAC_DATA0 + AUDIO_ANC_HAC_DATA_PATH, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_ANC0 + ANC_CHANNEL_SELECT, FIFO_RX_ANC_POST_PRE_32BIT);
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0 + ANC_CHANNEL_SELECT, FIFO_RX_ANC_SPEAKER_OUT);

    audio_anc_set_resample_in_out_fs(ANC_CHANNEL_SELECT, ANC_RESAMPLE_OTHERS_DECISION_FS,
            ANC_RESAMPLE_IN_FS_48K, ANC_FS==384000?ANC_RESAMPLE_OUT_FS_384K:ANC_RESAMPLE_OUT_FS_768K);

    /* rx dma config */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT, 4096 * 4);
    dma_llp_dis(DMA0); /* dis llp */
    audio_rx_dma_en(DMA0);
    audio_rx_dma_chain_init(FIFO2, DMA1, (unsigned short *)AUDIO_BUFFER_OUT1, 2048 * 4);
    dma_llp_dis(DMA1); /* dis llp */
    audio_rx_dma_en(DMA1);
    /* tx dma config */
    audio_tx_dma_chain_init(FIFO0, DMA2, (unsigned short *)anc_data_in_fb, 2048 * 4);
    dma_llp_dis(DMA2); /* dis llp */
    audio_tx_dma_en(DMA2);
    /* At ASRC_FS sample rate, it takes at least (DATA_LENGTH / (ASRC_FS/1000))ms for the DMA to finish transferring the audio data.
     * Wait twice as long to ensure transmission is completed.*/
    delay_ms(1000);

    for(unsigned int i = 0; i < 2048; i++)
    {
        if (cz0_data_out[i] != AUDIO_BUFFER_OUT[2*i])//cz0 post
        {
            AUDIO_BUFFER_OUT[0] = 0;
            AUDIO_BUFFER_OUT[1] = i;
            AUDIO_BUFFER_OUT[2] = cz0_data_out[i];
            AUDIO_BUFFER_OUT[3] = AUDIO_BUFFER_OUT[2*i];
            while(1);
        }
    }
    for(unsigned int i = 0; i < 2048; i++)
    {
        if (anc_data_in_fb[i] != AUDIO_BUFFER_OUT[2*i+1])//pre
        {
            AUDIO_BUFFER_OUT[0] = 1;
            AUDIO_BUFFER_OUT[1] = i;
            AUDIO_BUFFER_OUT[2] = anc_data_in_fb[i];
            AUDIO_BUFFER_OUT[3] = AUDIO_BUFFER_OUT[2*i+1];
            while(1);
        }
    }
    for(unsigned int i = 0; i < 2048; i++)
    {
        if (anc_data_out_fb[i] != AUDIO_BUFFER_OUT1[i])//spk
        {
            AUDIO_BUFFER_OUT1[0] = 1;
            AUDIO_BUFFER_OUT1[1] = i;
            AUDIO_BUFFER_OUT1[2] = anc_data_out_fb[i];
            AUDIO_BUFFER_OUT1[3] = AUDIO_BUFFER_OUT1[i];
            while(1);
        }
    }
#elif (ANC_FILTER_MODE == RAM_TO_HAC_TO_ANC_TO_RAM_HB)
    // hac config
    audio_hac_bypass_asrc(HAC_CHANNEL_SELECT, 1);
    audio_hac_bypass_eq(HAC_CHANNEL_SELECT);
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_IN/CH_NUM.
    audio_hac_set_out_data_rate(HAC_CHANNEL_SELECT, 36864000/ANC_FS/1);//  36.864MHz/FS_OUT/CH_NUM.
    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT, 1);
    if((HAC_CHANNEL_SELECT == HAC_CHN2) || (HAC_CHANNEL_SELECT == HAC_CHN3))
        audio_hac_set_tdm_num(HAC_CHANNEL_SELECT, 1);

    audio_matrix_set_hac_route(HAC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);

    // anc config
    audio_anc_set_mode(ANC_CHANNEL_SELECT, ANC_MODE_HB);
    audio_anc_set_adder2_mode(ANC_CHANNEL_SELECT, ANC_ERR_MIC_TO_ADDR2);
    audio_anc_set_adder3_mode(ANC_CHANNEL_SELECT, ANC_WZ_TO_HEADPHONE);
    audio_anc_set_adder3_priority(ANC_CHANNEL_SELECT, ANC_WZ_FIRST);
    audio_anc_set_resample_in_out_fs(ANC_CHANNEL_SELECT, ANC_RESAMPLE_OTHERS_DECISION_FS,
            ANC_RESAMPLE_IN_FS_48K, ANC_FS==384000?ANC_RESAMPLE_OUT_FS_384K:ANC_RESAMPLE_OUT_FS_768K);

    audio_anc_latch_wz_fir_gain(ANC_CHANNEL_SELECT);
    audio_anc_latch_ref_mic_gain(ANC_CHANNEL_SELECT);
    audio_anc_set_wz_iir_taps(ANC_CHANNEL_SELECT, 24);
    audio_anc_update_wz_iir_coef(ANC_CHANNEL_SELECT, wzbiq, 24);
    audio_anc_set_wz_fir_taps(ANC_CHANNEL_SELECT, 390);
    audio_anc_update_wz_fir_coef(ANC_CHANNEL_SELECT, fir390_fb_hb, sizeof(fir390_fb_hb) / sizeof(fir390_fb_hb[0]));
    audio_anc_set_cz_iir_taps(ANC_CHANNEL_SELECT, 0, 5);
    audio_anc_update_cz_iir_coef(ANC_CHANNEL_SELECT, 0, cz2biq, 5);
    audio_anc_set_cz_fir_taps(ANC_CHANNEL_SELECT, 0, 0x96);// fir_taps=150
    audio_anc_update_cz_fir_coef(ANC_CHANNEL_SELECT, 0, fir390_fb_hb, 0x96);

    audio_matrix_set_anc_err_route(ANC_CHANNEL_SELECT, ANC_ERR_ROUTE_HAC_DATA0 + AUDIO_ANC_HAC_DATA_PATH, ANC_ERR_DATA_FORMAT_INVALID);
    audio_matrix_set_anc_ref_route(ANC_CHANNEL_SELECT, ANC_REF_ROUTE_HAC_DATA0 + AUDIO_ANC_HAC_DATA_PATH, ANC_REF_DATA_FORMAT_INVALID);
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_ANC0 + ANC_CHANNEL_SELECT, FIFO_RX_ANC_POST_PRE_32BIT);
    audio_matrix_set_rx_fifo_route(FIFO2, FIFO_RX_ROUTE_ANC0 + ANC_CHANNEL_SELECT, FIFO_RX_ANC_SPEAKER_OUT);

    /* rx dma config */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)AUDIO_BUFFER_OUT, 4096 * 4);
    dma_llp_dis(DMA0); /* dis llp */
    audio_rx_dma_en(DMA0);
    audio_rx_dma_chain_init(FIFO2, DMA1, (unsigned short *)AUDIO_BUFFER_OUT1, 2048 * 4);
    dma_llp_dis(DMA1); /* dis llp */
    audio_rx_dma_en(DMA1);
    /* tx dma config */
    audio_tx_dma_chain_init(FIFO0, DMA2, (unsigned short *)anc_data_in_hb, 2048 * 4);
    audio_tx_dma_en(DMA2);
    dma_llp_dis(DMA2); /* dis llp */

    dma_chn_en(DMA0);
    dma_chn_en(DMA1);
    dma_chn_en(DMA2);

    delay_ms(1000);
    for (unsigned int i=0;i<2048;i++)
    {
        if (cz0_data_out_hb[i] != AUDIO_BUFFER_OUT[2*i])//cz0 out
        {
            AUDIO_BUFFER_OUT[0] = 0;
            AUDIO_BUFFER_OUT[1] = i;
            AUDIO_BUFFER_OUT[2] = cz0_data_out_hb[i];
            AUDIO_BUFFER_OUT[3] = AUDIO_BUFFER_OUT[2*i];
            while(1);
        }
        if (wz_data_out[i] != AUDIO_BUFFER_OUT1[i])//wz out
        {
            AUDIO_BUFFER_OUT1[0] = 1;
            AUDIO_BUFFER_OUT1[1] = i;
            AUDIO_BUFFER_OUT1[2] = wz_data_out[i];
            AUDIO_BUFFER_OUT1[3] = AUDIO_BUFFER_OUT1[i];
            while(1);
        }
        if (anc_data_in_hb[i] != AUDIO_BUFFER_OUT[2*i+1]) //err mic
        {
            AUDIO_BUFFER_OUT[0] = 2;
            AUDIO_BUFFER_OUT[1] = i;
            AUDIO_BUFFER_OUT[2] = anc_data_in_hb[i];
            AUDIO_BUFFER_OUT[3] = AUDIO_BUFFER_OUT[2*i+1];
            while(1);
        }
    }
#endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(200);
}
#endif

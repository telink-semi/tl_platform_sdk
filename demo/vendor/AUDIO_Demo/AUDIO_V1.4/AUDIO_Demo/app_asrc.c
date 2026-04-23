/********************************************************************************************************
 * @file    app_asrc.c
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
#if (AUDIO_MODE == ASRC_DEMO)
    #define RAM_TO_HAC_TO_RAM_MONO   (1)      /* data route: ram -> hac -> ram mono. */
    #define RAM_TO_HAC_TO_RAM_STEREO (2)  /* data route: ram -> hac -> ram. stereo*/

    #define AUDIO_HAC_MODE_SEL      RAM_TO_HAC_TO_RAM_MONO

    #define HAC_CHANNEL_SELECT      HAC_CH2_ASRC0
    #define HAC_ASRC_CHANNEL_SELECT HAC_ASRC0
    #define ASRC_SINGLE_CH_LENGTH   1024
    #define ASRC_FS_IN              48000
    #define ASRC_FS_OUT             48000
    #define PPM                     0

//volatile command_buff[16] = {0};
signed short drop_coef[9] = {0, 0, 0, 0, 1, -4, 12, -58, 2100};

int audio_buff_input[ASRC_SINGLE_CH_LENGTH] =
{
    0xff803e3a, 0xff94146c, 0x000464eb, 0xffaf33c3, 0x0018066c, 0x004b031a, 0x002cbf72, 0xffcb9eca,
    0xffb92b58, 0x00637eaa, 0xff93477b, 0xffe23b0a, 0xffae1da7, 0x0028de8d, 0x00772fa9, 0xffb2b731,
    0x0030c31b, 0xffb0ade1, 0xff8dc6c6, 0x000754ad, 0xffaaad3e, 0x005cf651, 0x002c3cfa, 0x00550c60,
    0x0079ebf3, 0x0021b466, 0xffdd08fb, 0xffc1c665, 0x0070872a, 0x005b5e6d, 0x0026f092, 0xffaebd44,
    0x006493b1, 0xffe4986a, 0x002bad11, 0x0004f898, 0x0046e85a, 0xfff8fdb3, 0xffe4309f, 0x0021ebf2,
    0x00167476, 0x0053122c, 0xffe08d63, 0x00223589, 0x002635e3, 0x00534dd1, 0xff917b7f, 0x00287b83,
    0x000bd027, 0xffde4bec, 0x00017d65, 0xff9e6a58, 0x006cc0cb, 0x000018b4, 0x0043a8f2, 0xffcdd1b5,
    0x00003583, 0xffc2a0b7, 0xffbe0a5d, 0x000fe4ca, 0xfffb8354, 0xffc53c39, 0x0055ac63, 0x007095e5,
    0x007f3ab5, 0x00435f81, 0xffa23cbb, 0x00041568, 0xfffae0e6, 0x0058672d, 0x002f52c2, 0x004c70d0,
    0x005d4183, 0x002e878d, 0x007155ee, 0x006d4ef2, 0x0047687f, 0x0066da20, 0xffb40267, 0xff8bceab,
    0xff98348d, 0x00688b29, 0x0068915f, 0xff988595, 0x000691b7, 0x00252806, 0x00197b8e, 0xffa19c88,
    0xffa04a12, 0x00400e33, 0x0069e466, 0x002b0ffc, 0x00237f55, 0xffe6f628, 0xffe69a5a, 0xffab0a0c,
    0xffc8bfd0, 0x0049a678, 0x000ebfe0, 0x0068662e, 0xffb3bcf2, 0x003ebb68, 0xffda11f2, 0xffd94971,
    0xffa09fef, 0x00039b5b, 0x0062cc4d, 0xffbfe33b, 0x0004012b, 0x0025804e, 0xffb93123, 0x00634c64,
    0xffb37d7a, 0x0041a7ca, 0xff86ae7e, 0xffe282b7, 0x000cebe5, 0x002aa06f, 0x0046a199, 0x003f891f,
    0x0032356e, 0xffe0b712, 0xffbac2d7, 0xffe0a40d, 0x000fc7a2, 0xffeb8818, 0x002125ab, 0xffa5b7e9,
    0xff83aed4, 0xffc2a86e, 0x0051e21c, 0x000fc716, 0x005b4863, 0x00137657, 0x000a59ac, 0x005890d4,
    0xfffd9aea, 0xffd209f6, 0x004c1dd3, 0x00784e0c, 0xffb84b9e, 0xffa33cc5, 0xffd57457, 0xfff79057,
    0xffc53562, 0xffcdddd8, 0x005980b0, 0x004b3e45, 0x003e9b3c, 0x0040fd2d, 0x003e06c3, 0x0018b332,
    0x005802ad, 0x005d5960, 0x0004d198, 0x005ffd3f, 0xff91a7b2, 0x004fedfc, 0xffa6bb6d, 0x002a39a3,
    0xfffc92d5, 0xffeba152, 0x00464fb0, 0x003a1400, 0x00054e23, 0x00101400, 0x000016d1, 0xffdc646b,
    0xffdb3e6a, 0xff8b8d96, 0xfffe757a, 0x0016ecc5, 0xffea9492, 0xffc60a7f, 0xffd7370d, 0xffd33727,
    0xffbee8fb, 0xffa3692c, 0x0018b487, 0x000393f9, 0x00446ba7, 0xffeaba91, 0xff8c969c, 0xffe03770,
    0xffbdbf25, 0xffe0af7b, 0xffd63d35, 0xffba778a, 0xffe46c02, 0xffa322d9, 0xfff2c69c, 0x00042c55,
    0xff89f8ad, 0x0033cde9, 0x0000b500, 0x00492882, 0x006f9b9e, 0xff801080, 0x00553425, 0xffb8df1f,
    0xffea96a9, 0x0013e4c2, 0x0044ff60, 0xffbe1a76, 0xff8b2846, 0xff85e60d, 0x0026e634, 0x0042dc67,
    0xff9c2440, 0x000a85f4, 0x0075f639, 0x005e5f43, 0xffb12916, 0xffbc5500, 0x00593d1c, 0xffcb3079,
    0xffd97673, 0x00477519, 0xfff730db, 0xffe36f1b, 0xffad6112, 0xff8623c9, 0x005ab396, 0xff812b0d,
    0xff8c6c78, 0x003c694c, 0xff8fbd93, 0x0000e1e5, 0x0041fcc6, 0x0000e805, 0x003d9ed0, 0x00441dcb,
    0xffa6af25, 0xffc0c95a, 0x0064e744, 0x00323266, 0x0034517b, 0x002ccb93, 0x0046ed1b, 0xff951b9f,
    0x002272f1, 0xfffd6fb4, 0xff9cf120, 0xffd07cc5, 0x00419ffc, 0xff9c48f4, 0xffa4e69e, 0xffd0bb63,
    0xffeb33f6, 0xffa0683f, 0x0029d8df, 0x00303f51, 0x003bd267, 0x002becfb, 0xff8def20, 0xfff0d2cd,
};
int audio_buff_output[ASRC_SINGLE_CH_LENGTH*6];

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    audio_init(PLL_AUDIO_CLK_86P016M); /* must configured first. */
    audio_hac_clk_en(HAC_CHANNEL_SELECT);


    audio_hac_set_input_num(HAC_CHANNEL_SELECT,256);
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, (43008000 / ASRC_FS_IN )-1);  /* 36.864MHz/FS_IN/CH_NUM. */

    audio_hac_set_asrc_tdm_num(HAC_ASRC_CHANNEL_SELECT,1);

    audio_hac_set_out_data_addr(HAC_CHANNEL_SELECT,(unsigned int)audio_buff_output);
    audio_hac_set_in_data_addr(HAC_CHANNEL_SELECT,(unsigned int)audio_buff_input);

//  audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);

    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));

    #if (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_MONO)

    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 1);

    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_AHB_MST);
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MCU);
    reg_audio_hac_ahb_master_read_en = 1;

    #elif (AUDIO_HAC_MODE_SEL == RAM_TO_HAC_TO_RAM_STEREO)
//    audio_hac_set_data_src(HAC_ASRC_CHANNEL_SELECT, HAC_INPUT_DATA_MATRIX);
//    audio_hac_set_data_dst(HAC_ASRC_CHANNEL_SELECT, HAC_OUTPUT_DATA_MATRIX);
//
//    audio_hac_set_in_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_IN / 2);   /* 36.864MHz/FS_IN/CH_NUM. */
//    audio_hac_set_out_data_rate(HAC_ASRC_CHANNEL_SELECT, 36864000 / ASRC_FS_OUT / 2); /* 36.864MHz/FS_OUT/CH_NUM. */
//    audio_hac_asrc_fs_in_out(HAC_ASRC_CHANNEL_SELECT, ASRC_FS_IN, ASRC_FS_OUT, PPM, 2);
//
//    audio_asrc_set_droop_step((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, ASRC_DROOP_STEP_17TAPS);
//    audio_asrc_update_droop_coef((audio_asrc_chn_e)HAC_ASRC_CHANNEL_SELECT, drop_coef, sizeof(drop_coef) / sizeof(drop_coef[0]));
//    audio_hac_bypass_eq(HAC_ASRC_CHANNEL_SELECT); /* Bypass the EQ function by configuring the specified parameters. */
//    audio_matrix_set_hac_route(HAC_ASRC_CHANNEL_SELECT, HAC_DATA_ROUTE_FIFO0 + AUDIO_FIFO_CHANNEL, HAC_20_OR_24_BIT);
//    audio_matrix_set_rx_fifo_route(AUDIO_FIFO_CHANNEL, FIFO_RX_ROUTE_HAC_DATA0 + HAC_ASRC_CHANNEL_SELECT, FIFO_RX_HAC23_STEREO_20_OR_24BIT);
//
//    audio_hac_set_tdm_tx_dma_ch(AUDIO_FIFO_CHANNEL, HAC_TDM_TX_DMA_2CH);
//    audio_hac_set_tdm_num(HAC_ASRC_CHANNEL_SELECT, 2);
//    audio_hac_asrc_ch_en(HAC_ASRC_CHANNEL_SELECT, 1);
//
//    /* rx dma config */
//    audio_rx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_RX, (unsigned short *)AUDIO_BUFFER, sizeof(AUDIO_BUFFER));
//    audio_rx_dma_en(AUDIO_DMA_CHANNEL_RX);
//
//    /* tx dma config */
//    audio_tx_dma_chain_init(AUDIO_FIFO_CHANNEL, AUDIO_DMA_CHANNEL_TX, (unsigned short *)sin_48k_stereo_24bit, sizeof(sin_48k_stereo_24bit));
//    audio_tx_dma_en(AUDIO_DMA_CHANNEL_TX);
//
    #endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);
}
#endif

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
#include "app_sin_data.h"
    #define RAM_TO_HAC_TO_RAM_MONO   (1) /* data route: ram -> hac -> ram. mono*/

    #define EQ_MODE                  RAM_TO_HAC_TO_RAM_MONO

    #define HAC_CHANNEL_SELECT    HAC_CH0_EQ0
    #define HAC_EQ_CHANNEL_SELECT    HAC_EQ0

    #define AUDIO_DMA_CHANNEL_TX     DMA0
    #define AUDIO_DMA_CHANNEL_RX     DMA1
    #define AUDIO_FIFO_CHANNEL       FIFO0
    #define EQ_ASRC_FS               48000
    #define PPM                      0

    #define EQ_SINGLE_CH_LENGTH      1024

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
//
//signed int biq[HAC_BIQUAD_CNT][5] =
//{
//  { 0x100506c0,0xe026e600,0xfd42660,0xe026e600,0xfd92d20},
//  { 0xf9ab3a0,0xe13d35e0,0xf2b4940,0xe13d35e0,0xec5fce0},
//  { 0xfe82b30,0xe1d29880,0xe618cb0,0xe1d29880,0xe49b7e0},
//  { 0x101f6500,0xe2506020,0xdde05a0,0xe2506020,0xdfd6a90},
//  { 0xf2deb40,0xea241520,0x8d73420,0xea241520,0x8051f60},
//  { 0xa995730,0xf473f660,0x4a89548,0xf473f660,0xff41ec76},
//  { 0xc2191c0,0xf6176ef0,0x45b4778,0xf6176ef0,0x7cd93a},
//  { 0xb7037f0,0xf8f6ba40,0x5676b10,0xf8f6ba40,0xd7a30a},
//  { 0xd7a30a,0x100506c0,0xe026e600,0xfd42660,0xe026e600},
//  { 0xfd92d20,0xf9ab3a0,0xe13d35e0,0xf2b4940,0xe13d35e0},
//};

int audio_buff_input[EQ_SINGLE_CH_LENGTH] =
{
    0xffb08d2c, 0xffc2b77f, 0x007c7f55, 0x005314c4, 0x00570df4, 0xffb30ab9, 0xffc3dec1, 0x005b7902,
    0xff8c0765, 0xffc66d95, 0x00211682, 0x002b0c74, 0xffeab9ab, 0xff81cf2c, 0xffd13aa4, 0x0033192b,
    0x003f5082, 0xffd6b6e0, 0xff98c610, 0x005689a0, 0x0049a28b, 0x00013ada, 0x0022a943, 0xff8b6d92,
    0xfffc0d4d, 0x004e9590, 0x00567735, 0x002c20d7, 0x00347549, 0xffc25d18, 0xffb3b4a8, 0x007e0fdc,
    0x004d6207, 0x007057b9, 0x006045c2, 0x00141f0c, 0xffc53f96, 0x0000f108, 0xfff7fa9e, 0xff92b1e7,
    0xff99b75d, 0xfff653ef, 0x000b3fc2, 0xffbb4ce9, 0x00553236, 0xffe81a80, 0xffdae9af, 0x0005e026,
    0xffac752e, 0x000bab6f, 0xffff255e, 0xffedaaab, 0xffea5ff0, 0x003f287f, 0xff878378, 0xffb7c185,
    0xff87c821, 0xffad095f, 0x00022817, 0x00593513, 0x006d7c4b, 0xffbe512d, 0xfff819cc, 0x0002d7e4,
    0x007e5d09, 0xfff16298, 0x004cacd3, 0xfff8a266, 0x00279e9c, 0x004b786f, 0x004e1221, 0xfffabc19,
    0x0055239c, 0x007ab77f, 0x00650833, 0x002620fe, 0x0007fee3, 0x005ee98e, 0x0031a3d5, 0xffd2e38f,
    0x006d0d77, 0x004ed072, 0x000342bf, 0xff961a65, 0x0071b7fa, 0xffd01b67, 0xffb99740, 0xffad5de4,
    0xfff4cdf6, 0x00580045, 0xffbcd6dd, 0x0079f308, 0x0011850e, 0x004a6dae, 0x005b0792, 0x0051922c,
    0xffa299d8, 0x000de4cb, 0x00386f9d, 0xffcac976, 0x007b86f4, 0x0029eb45, 0xffa12188, 0x000b042e,
    0xffb5e8b2, 0x000624f6, 0x0069abd1, 0x003c33af, 0x0010fbbf, 0x0000079c, 0x006ce4eb, 0x003010c1,
    0x0041353a, 0x006d31fa, 0x0054daf6, 0xff970403, 0xffae06b2, 0x00006128, 0xffbce163, 0xff90adb4,
    0xffbbb958, 0xffa70693, 0x005abeef, 0x003c0684, 0xffdf6cfb, 0x00557fe3, 0xfffcfa19, 0xffcd2c42,
};
int audio_buff_output[EQ_SINGLE_CH_LENGTH];
int audio_buff_output_check[EQ_SINGLE_CH_LENGTH] =
{
    0xffffffef, 0x00000002, 0x00000016, 0xffffffef, 0x0000001b, 0xffffffe9, 0x00000014, 0x00000012,
    0xffffffd2, 0x00000021, 0xfffffff8, 0xfffffffd, 0xfffffffa, 0xffffffee, 0x00000008, 0xfffffffc,
    0xfffffffe, 0xfffffff4, 0xfffffffc, 0x0000001f, 0xfffffff1, 0x0000000c, 0x00000018, 0xffffffe8,
    0x0000002a, 0x00000007, 0x00000016, 0x00000017, 0x00000023, 0x00000005, 0x0000001e, 0x00000035,
    0x00000004, 0x0000003b, 0x0000001e, 0x0000001d, 0x00000018, 0x00000026, 0x0000000a, 0x00000001,
    0x0000000d, 0x00000008, 0xfffffffc, 0xfffffff4, 0x00000022, 0xffffffdc, 0x00000011, 0x00000001,
    0xffffffea, 0x00000018, 0xffffffef, 0x00000005, 0x00000001, 0x00000012, 0xffffffdb, 0x0000001a,
    0xffffffdf, 0x00000002, 0xfffffffe, 0x00000008, 0x0000000a, 0xfffffff0, 0x00000023, 0xfffffffb,
    0x00000028, 0xfffffff0, 0x00000038, 0xfffffff5, 0x0000002a, 0x00000014, 0x0000001b, 0x0000000d,
    0x00000030, 0x00000016, 0x0000001f, 0x00000018, 0x00000019, 0x00000027, 0x00000008, 0x0000000d,
    0x00000032, 0xfffffffc, 0x00000012, 0xfffffffb, 0x00000032, 0xffffffd1, 0x00000019, 0xffffffef,
    0x00000004, 0x00000007, 0xffffffdf, 0x00000036, 0xffffffda, 0x00000029, 0x00000006, 0x00000015,
    0xfffffff5, 0x0000002f, 0x00000003, 0x00000000, 0x0000003d, 0xfffffff3, 0x0000000f, 0x00000029,
    0xffffffed, 0x00000029, 0x00000017, 0x0000000e, 0x0000001f, 0x0000001a, 0x00000032, 0x00000010,
    0x00000037, 0x0000002e, 0x00000029, 0x0000000e, 0x00000032, 0x0000001b, 0x00000007, 0x00000015,
    0x00000013, 0xffffffff, 0x00000031, 0xffffffff, 0x00000016, 0x00000036, 0x00000001, 0x00000027,
};

volatile unsigned short in_data_rate = 0;
void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    audio_init(PLL_AUDIO_CLK_86P016M); /* must configured first. */
    audio_hac_clk_en(HAC_CHANNEL_SELECT);

    audio_hac_set_input_num(HAC_CHANNEL_SELECT,128);

    in_data_rate = (43008000 / EQ_ASRC_FS )-1;
    audio_hac_set_in_data_rate(HAC_CHANNEL_SELECT, in_data_rate);  /* 36.864MHz/FS_IN/CH_NUM. */

    ///FOR TEST
//    for(int i=0;i<96;i++) {
//      audio_buff_input[i] = sin_48k_stereo_24bit[i];
//    }
    audio_hac_set_out_data_addr(HAC_CHANNEL_SELECT,(unsigned int)audio_buff_output);
    audio_hac_set_in_data_addr(HAC_CHANNEL_SELECT,(unsigned int)audio_buff_input);

//    audio_hac_bypass_eq_asrc(HAC_CHANNEL_SELECT,1);

    for (int i = 0; i < HAC_BIQUAD_CNT; i++) {
        audio_hac_update_biquad_coef(HAC_EQ_CHANNEL_SELECT, i, biq[i]);
    };
    audio_hac_eq_config_en(HAC_EQ_CHANNEL_SELECT);

    audio_hac_asrc_ch_en(HAC_CHANNEL_SELECT,1);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_AHB_MST);
    reg_audio_hac_ahb_master_read_en = 1;
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MCU);

    delay_ms(10);

    audio_hac_set_out_data_addr(HAC_CHANNEL_SELECT,(unsigned int)(&audio_buff_output[128]));
    audio_hac_set_in_data_addr(HAC_CHANNEL_SELECT,(unsigned int)(&audio_buff_input[128]));

    audio_hac_input_afifo_clr(HAC_CHANNEL_SELECT);

    audio_hac_set_data_dst(HAC_CHANNEL_SELECT, HAC_OUTPUT_DATA_AHB_MST);
    reg_audio_hac_ahb_master_read_en = 1;
    audio_hac_set_data_src(HAC_CHANNEL_SELECT, HAC_INPUT_DATA_MCU);

//  delay_ms(200);
//    for(int i=0;i<128;i++) {
//      if(audio_buff_output[i] != audio_buff_output_check[i])
//      {
//          while(1) {
//              gpio_toggle(LED2);
//              delay_ms(200);
//          }
//      }
//    }

}


void main_loop(void)
{

    gpio_toggle(LED1);
    delay_ms(200);

}
#endif

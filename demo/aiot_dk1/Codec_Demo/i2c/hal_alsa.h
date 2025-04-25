/********************************************************************************************************
 * @file    hal_alsa.h
 *
 * @brief   This is the source file for TL7518/TL721X/TL321X
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
#ifndef _ALSA_HAL_H_
#define _ALSA_HAL_H_
#include "../dk1_codec_app_config.h"

typedef struct _ALSA_DEVICE
{
    unsigned char regmap;

} Alsa_Device;

#define Everest_Revision 2.0.1.0.0511
/*******************
    2.1.0.0.0511
*******************/
/************************* General PARAMETER ******************************/
#define Everest_MasterMode 1
#define Everest_SlaveMode  0
#define Everest_Invert     1
#define Everest_NoInvert   0
#define Everest_On         1
#define Everest_OFF        0
#define Everest_Mute       1
#define Everest_Unmute     0
#define Everest_TRI        1
#define Everest_NoTRI      0
#define Everest_SCLK_PIN   1
#define Everest_MCLK_PIN   0

/***** General REGISTER MAP *****/
#define Everest_Reg0x00 0x00
#define Everest_Reg0x01 0x01
#define Everest_Reg0x02 0x02
#define Everest_Reg0x03 0x03
#define Everest_Reg0x04 0x04
#define Everest_Reg0x05 0x05
#define Everest_Reg0x06 0x06
#define Everest_Reg0x07 0x07
#define Everest_Reg0x08 0x08
#define Everest_Reg0x09 0x09
#define Everest_Reg0x0A 0x0A
#define Everest_Reg0x0B 0x0B
#define Everest_Reg0x0C 0x0C
#define Everest_Reg0x0D 0x0D
#define Everest_Reg0x0E 0x0E
#define Everest_Reg0x0F 0x0F
#define Everest_Reg0x10 0x10
#define Everest_Reg0x11 0x11
#define Everest_Reg0x12 0x12
#define Everest_Reg0x13 0x13
#define Everest_Reg0x14 0x14
#define Everest_Reg0x15 0x15
#define Everest_Reg0x16 0x16
#define Everest_Reg0x17 0x17
#define Everest_Reg0x18 0x18
#define Everest_Reg0x19 0x19
#define Everest_Reg0x1A 0x1A
#define Everest_Reg0x1B 0x1B
#define Everest_Reg0x1C 0x1C
#define Everest_Reg0x1D 0x1D
#define Everest_Reg0x1E 0x1E
#define Everest_Reg0x1F 0x1F
#define Everest_Reg0x20 0x20
#define Everest_Reg0x21 0x21
#define Everest_Reg0x22 0x22
#define Everest_Reg0x23 0x23
#define Everest_Reg0x24 0x24
#define Everest_Reg0x25 0x25
#define Everest_Reg0x26 0x26
#define Everest_Reg0x27 0x27
#define Everest_Reg0x28 0x28
#define Everest_Reg0x29 0x29
#define Everest_Reg0x2A 0x2A
#define Everest_Reg0x2B 0x2B
#define Everest_Reg0x2C 0x2C
#define Everest_Reg0x2D 0x2D
#define Everest_Reg0x2E 0x2E
#define Everest_Reg0x2F 0x2F
#define Everest_Reg0x30 0x30
#define Everest_Reg0x31 0x31
#define Everest_Reg0x32 0x32
#define Everest_Reg0x33 0x33
#define Everest_Reg0x34 0x34
#define Everest_Reg0x35 0x35
#define Everest_Reg0x36 0x36
#define Everest_Reg0x37 0x37
#define Everest_Reg0x38 0x38
#define Everest_Reg0x39 0x39
#define Everest_Reg0x3A 0x3A
#define Everest_Reg0x3B 0x3B
#define Everest_Reg0x3C 0x3C
#define Everest_Reg0x3D 0x3D
#define Everest_Reg0x3E 0x3E
#define Everest_Reg0x3F 0x3F
#define Everest_Reg0x40 0x40
#define Everest_Reg0x41 0x41
#define Everest_Reg0x42 0x42
#define Everest_Reg0x43 0x43
#define Everest_Reg0x44 0x44
#define Everest_Reg0x45 0x45
#define Everest_Reg0x46 0x46
#define Everest_Reg0x47 0x47
#define Everest_Reg0x48 0x48
#define Everest_Reg0x49 0x49
#define Everest_Reg0x4A 0x4A
#define Everest_Reg0x4B 0x4B
#define Everest_Reg0x4C 0x4C
#define Everest_Reg0x4D 0x4D
#define Everest_Reg0x4E 0x4E
#define Everest_Reg0x4F 0x4F
#define Everest_Reg0x50 0x50
#define Everest_Reg0x51 0x51
#define Everest_Reg0x52 0x52
#define Everest_Reg0x53 0x53
#define Everest_Reg0x54 0x54
#define Everest_Reg0x55 0x55
#define Everest_Reg0x56 0x56
#define Everest_Reg0x57 0x57
#define Everest_Reg0x58 0x58
#define Everest_Reg0x59 0x59
#define Everest_Reg0x5A 0x5A
#define Everest_Reg0x5B 0x5B
#define Everest_Reg0x5C 0x5C
#define Everest_Reg0x5D 0x5D
#define Everest_Reg0x5E 0x5E
#define Everest_Reg0x5F 0x5F
#define Everest_Reg0x60 0x60
#define Everest_Reg0x61 0x61
#define Everest_Reg0x62 0x62
#define Everest_Reg0x63 0x63
#define Everest_Reg0x64 0x64
#define Everest_Reg0x65 0x65
#define Everest_Reg0x66 0x66
#define Everest_Reg0x67 0x67
#define Everest_Reg0x68 0x68
#define Everest_Reg0x69 0x69
#define Everest_Reg0x6A 0x6A
#define Everest_Reg0x6B 0x6B
#define Everest_Reg0x6C 0x6C
#define Everest_Reg0x6D 0x6D
#define Everest_Reg0x6E 0x6E
#define Everest_Reg0x6F 0x6F
#define Everest_Reg0x70 0x70
#define Everest_Reg0x71 0x71
#define Everest_Reg0x72 0x72
#define Everest_Reg0x73 0x73
#define Everest_Reg0x74 0x74
#define Everest_Reg0x75 0x75
#define Everest_Reg0x76 0x76
#define Everest_Reg0x77 0x77
#define Everest_Reg0x78 0x78
#define Everest_Reg0x79 0x79
#define Everest_Reg0x7A 0x7A
#define Everest_Reg0x7B 0x7B
#define Everest_Reg0x7C 0x7C
#define Everest_Reg0x7D 0x7D
#define Everest_Reg0x7E 0x7E
#define Everest_Reg0x7F 0x7F
#define Everest_Reg0x80 0x80
#define Everest_Reg0x81 0x81
#define Everest_Reg0x82 0x82
#define Everest_Reg0x83 0x83
#define Everest_Reg0x84 0x84
#define Everest_Reg0x85 0x85
#define Everest_Reg0x86 0x86
#define Everest_Reg0x87 0x87
#define Everest_Reg0x88 0x88
#define Everest_Reg0x89 0x89
#define Everest_Reg0x8A 0x8A
#define Everest_Reg0x8B 0x8B
#define Everest_Reg0x8C 0x8C
#define Everest_Reg0x8D 0x8D
#define Everest_Reg0x8E 0x8E
#define Everest_Reg0x8F 0x8F
#define Everest_Reg0x90 0x90
#define Everest_Reg0x91 0x91
#define Everest_Reg0x92 0x92
#define Everest_Reg0x93 0x93
#define Everest_Reg0x94 0x94
#define Everest_Reg0x95 0x95
#define Everest_Reg0x96 0x96
#define Everest_Reg0x97 0x97
#define Everest_Reg0x98 0x98
#define Everest_Reg0x99 0x99
#define Everest_Reg0x9A 0x9A
#define Everest_Reg0x9B 0x9B
#define Everest_Reg0x9C 0x9C
#define Everest_Reg0x9D 0x9D
#define Everest_Reg0x9E 0x9E
#define Everest_Reg0x9F 0x9F
#define Everest_Reg0xA0 0xA0
#define Everest_Reg0xA1 0xA1
#define Everest_Reg0xA2 0xA2
#define Everest_Reg0xA3 0xA3
#define Everest_Reg0xA4 0xA4
#define Everest_Reg0xA5 0xA5
#define Everest_Reg0xA6 0xA6
#define Everest_Reg0xA7 0xA7
#define Everest_Reg0xA8 0xA8
#define Everest_Reg0xA9 0xA9
#define Everest_Reg0xAA 0xAA
#define Everest_Reg0xAB 0xAB
#define Everest_Reg0xAC 0xAC
#define Everest_Reg0xAD 0xAD
#define Everest_Reg0xAE 0xAE
#define Everest_Reg0xAF 0xAF
#define Everest_Reg0xB0 0xB0
#define Everest_Reg0xB1 0xB1
#define Everest_Reg0xB2 0xB2
#define Everest_Reg0xB3 0xB3
#define Everest_Reg0xB4 0xB4
#define Everest_Reg0xB5 0xB5
#define Everest_Reg0xB6 0xB6
#define Everest_Reg0xB7 0xB7
#define Everest_Reg0xB8 0xB8
#define Everest_Reg0xB9 0xB9
#define Everest_Reg0xBA 0xBA
#define Everest_Reg0xBB 0xBB
#define Everest_Reg0xBC 0xBC
#define Everest_Reg0xBD 0xBD
#define Everest_Reg0xBE 0xBE
#define Everest_Reg0xBF 0xBF
#define Everest_Reg0xC0 0xC0
#define Everest_Reg0xC1 0xC1
#define Everest_Reg0xC2 0xC2
#define Everest_Reg0xC3 0xC3
#define Everest_Reg0xC4 0xC4
#define Everest_Reg0xC5 0xC5
#define Everest_Reg0xC6 0xC6
#define Everest_Reg0xC7 0xC7
#define Everest_Reg0xC8 0xC8
#define Everest_Reg0xC9 0xC9
#define Everest_Reg0xCA 0xCA
#define Everest_Reg0xCB 0xCB
#define Everest_Reg0xCC 0xCC
#define Everest_Reg0xCD 0xCD
#define Everest_Reg0xCE 0xCE
#define Everest_Reg0xCF 0xCF
#define Everest_Reg0xD0 0xD0
#define Everest_Reg0xD1 0xD1
#define Everest_Reg0xD2 0xD2
#define Everest_Reg0xD3 0xD3
#define Everest_Reg0xD4 0xD4
#define Everest_Reg0xD5 0xD5
#define Everest_Reg0xD6 0xD6
#define Everest_Reg0xD7 0xD7
#define Everest_Reg0xD8 0xD8
#define Everest_Reg0xD9 0xD9
#define Everest_Reg0xDA 0xDA
#define Everest_Reg0xDB 0xDB
#define Everest_Reg0xDC 0xDC
#define Everest_Reg0xDD 0xDD
#define Everest_Reg0xDE 0xDE
#define Everest_Reg0xDF 0xDF
#define Everest_Reg0xE0 0xE0
#define Everest_Reg0xE1 0xE1
#define Everest_Reg0xE2 0xE2
#define Everest_Reg0xE3 0xE3
#define Everest_Reg0xE4 0xE4
#define Everest_Reg0xE5 0xE5
#define Everest_Reg0xE6 0xE6
#define Everest_Reg0xE7 0xE7
#define Everest_Reg0xE8 0xE8
#define Everest_Reg0xE9 0xE9
#define Everest_Reg0xEA 0xEA
#define Everest_Reg0xEB 0xEB
#define Everest_Reg0xEC 0xEC
#define Everest_Reg0xED 0xED
#define Everest_Reg0xEE 0xEE
#define Everest_Reg0xEF 0xEF
#define Everest_Reg0xF0 0xF0
#define Everest_Reg0xF1 0xF1
#define Everest_Reg0xF2 0xF2
#define Everest_Reg0xF3 0xF3
#define Everest_Reg0xF4 0xF4
#define Everest_Reg0xF5 0xF5
#define Everest_Reg0xF6 0xF6
#define Everest_Reg0xF7 0xF7
#define Everest_Reg0xF8 0xF8
#define Everest_Reg0xF9 0xF9
#define Everest_Reg0xFA 0xFA
#define Everest_Reg0xFB 0xFB
#define Everest_Reg0xFC 0xFC
#define Everest_Reg0xFD 0xFD
#define Everest_Reg0xFE 0xFE
#define Everest_Reg0xFF 0xFF

/***** RATIO_MCLK_LRCK *****/
#define RATIO_MCLK_LRCK_16         16
#define RATIO_MCLK_LRCK_32         32
#define RATIO_MCLK_LRCK_48         48
#define RATIO_MCLK_LRCK_64         64
#define RATIO_MCLK_LRCK_100        100
#define RATIO_MCLK_LRCK_128        128
#define RATIO_MCLK_LRCK_192        192
#define RATIO_MCLK_LRCK_250        250
#define RATIO_MCLK_LRCK_256        256
#define RATIO_MCLK_LRCK_384        384
#define RATIO_MCLK_LRCK_500        500
#define RATIO_MCLK_LRCK_512        512
#define RATIO_MCLK_LRCK_768        768
#define RATIO_MCLK_LRCK_896        896
#define RATIO_MCLK_LRCK_1024       1024
#define RATIO_MCLK_LRCK_1152       1152
#define RATIO_MCLK_LRCK_1280       1280
#define RATIO_MCLK_LRCK_1408       1408
#define RAITO_MCLK_LRCK_1536       1536
#define RATIO_MCLK_LRCK_1664       1664
#define RATIO_MCLK_LRCK_1792       1792
#define RATIO_MCLK_LRCK_1920       1920
#define RATIO_MCLK_LRCK_2048       2048
#define RATIO_MCLK_LRCK_3072       3072
#define RATIO_MCLK_LRCK_4096       4096

#define SND_SOC_DAIFMT_MASTER_MASK 0x80
#define SND_SOC_DAIFMT_CBS_CFS     0 << 7
#define SND_SOC_DAIFMT_CBM_CFM     1 << 7

#define SND_SOC_DAIFMT_FORMAT_MASK 0x70
#define SND_SOC_DAIFMT_I2S         0 << 4
#define SND_SOC_DAIFMT_RIGHT_J     1 << 4
#define SND_SOC_DAIFMT_LEFT_J      2 << 4
#define SND_SOC_DAIFMT_DSP_A       3 << 4
#define SND_SOC_DAIFMT_DSP_B       4 << 4

#define SND_SOC_DAIFMT_INV_MASK    0x0F
#define SND_SOC_DAIFMT_NB_NF       0
#define SND_SOC_DAIFMT_IB_IF       1
#define SND_SOC_DAIFMT_IB_NF       2
#define SND_SOC_DAIFMT_NB_IF       3

#define SNDRV_PCM_FORMAT_S16_LE    0
#define SNDRV_PCM_FORMAT_S20_LE    1
#define SNDRV_PCM_FORMAT_S24_LE    2
#define SNDRV_PCM_FORMAT_S32_LE    3


#define regmap_write               hal_i2c_write
#define regmap_read                hal_i2c_read
#define regmap_update_bits         hal_i2c_update_bits
#define ussleep(ms)                delay_ms(ms)


#endif

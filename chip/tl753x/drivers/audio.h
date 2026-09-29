/********************************************************************************************************
 * @file    audio.h
 *
 * @brief   This is the header file for tl753x
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
/** @page AUDIO
 *
 *  API Reference
 *  ===============
 *  Header File: audio.h
 */

#ifndef __AUDIO_H_
#define __AUDIO_H_

#include "driver.h"
#include "reg_include/register.h"

#define DRV_CODEC_DAC_NONE            (0)
#define DRV_CODEC_DAC_DSS_ENABLE      (1)
#define DRV_CODEC_DAC_NG_ENABLE       (2)

#define CODEC_DAC_MODE                DRV_CODEC_DAC_NONE

/**********************************************************************************************************************
 *                                                Audio anc enum/struct                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio anc enum/struct.
 * @{
 */

/**
 * @brief ANC channel.
 * 
 */
typedef enum
{
    ANC0 = 0x00,
} audio_anc_chn_e;

/**
 * @brief ANC src channel.
 *
 */
typedef enum
{
    ANC0_SRC0,
} audio_anc_src_chn_e;

/**
 * @brief ANC ref channel.
 *
 */
typedef enum
{
    ANC0_REF0,
    ANC0_REF1,
    ANC0_REF2,
} audio_anc_ref_chn_e;

/**
 * @brief ANC err channel.
 *
 */
typedef enum
{
    ANC0_ERR0,
    ANC0_ERR1,
    ANC0_ERR2,
} audio_anc_err_chn_e;

/**
 * @brief ANC wz channel.
 *
 */
typedef enum
{
    ANC0_WZ0,
    ANC0_WZ1,
    ANC0_WZ2,
} audio_anc_wz_chn_e;

/**
 * @brief ANC cz channel.
 *
 */
typedef enum
{
    ANC0_CZ0,
    ANC0_CZ1,
    ANC0_CZ2,
    ANC0_CZ3,
} audio_anc_cz_chn_e;

/**
 * @brief ANC wcz channel.
 *
 */
typedef enum
{
    ANC0_WCZ0,
    ANC0_WCZ1,
    ANC0_WCZ2,
    ANC0_WCZ3,
} audio_anc_wcz_chn_e;

/**
 * @brief ANC rz channel.
 *
 */
typedef enum
{
    ANC0_RZ0,
    ANC0_RZ1,
} audio_anc_rz_chn_e;

/**
 * @brief ANC bz channel.
 *
 */
typedef enum
{
    ANC0_BZ0,//anc_bz_ref0
    ANC0_BZ1,//anc_bz_ref1
    ANC0_BZ2,//anc_bz_ref2
    ANC0_BZ3,//anc_bz_err0
    ANC0_BZ4,//anc_bz_err1
} audio_anc_bz_chn_e;

/**
 * @brief ANC mode.
 * 0: ref012err01;        (192/384k)
 * 1: ref012err0;         (192/384/768k)
 * 2: ref01err01;         (192/384k)
 * 3: ref01err0;          (192/384/768k)
 * 4: ref0err0;           (192/384/768k)
 * 5: ref0err01;          (192/384/768k)
 * 6: ref0;               (192/384/768k)
 * 7: ref0wz384;          (192/384/768k)
 * 8: ref0wz384err0cz256; (192/384k)
 * 9: feed_back mode
 */
typedef enum
{
    ANC_MODE_HB_REF012ERR01,
    ANC_MODE_HB_REF012ERR0,
    ANC_MODE_HB_REF01ERR01,
    ANC_MODE_HB_REF01ERR0,
    ANC_MODE_HB_REF0ERR0,
    ANC_MODE_HB_REF0ERR01,
    ANC_MODE_FF_REF0,
    ANC_MODE_FF_REF0WZ384,
    ANC_MODE_HB_REF0WZ384ERR0CZ256,
    ANC_MODE_FB,
} audio_anc_mode_e;

/**
 * @brief ANC resample mode sel.
 * 0:48k->768k; 1:96k->768k or 48k->384k; 2: 96k->384k
 */
typedef enum
{
    ANC_48K_IN_768K_OUT = 0x00,
    ANC_96K_IN_768K_OUT = 0x01,
    ANC_48K_IN_384K_OUT = 0x01,
    ANC_96K_IN_384K_OUT = 0x02,
} audio_anc_dac_cnt_mode_e;

/**
 * @brief ANC resample mode sel.
 * 0:48k->768k;1:48k->384k;2:96k->768k;3:96k->384k;4:48k->192k;others 96k->192k
 */
typedef enum
{
    ANC_RESAMPLE_48K_IN_768K_OUT,
    ANC_RESAMPLE_48K_IN_384K_OUT,
    ANC_RESAMPLE_96K_IN_768K_OUT,
    ANC_RESAMPLE_96K_IN_384K_OUT,
    ANC_RESAMPLE_48K_IN_192K_OUT,
    ANC_RESAMPLE_96K_IN_192K_OUT,
} audio_anc_resample_mode_e;

/**
 * @brief ANC resample input fs.
 *
 */
typedef enum
{
    ANC_RESAMPLE_IN_FS_48K,
    ANC_RESAMPLE_IN_FS_96K,
} audio_anc_resample_in_fs_e;

/**
 * @brief ANC resample output fs.
 *
 */
typedef enum
{
    ANC_RESAMPLE_OUT_FS_768K,
    ANC_RESAMPLE_OUT_FS_384K,
    ANC_RESAMPLE_OUT_FS_192K
} audio_anc_resample_out_fs_e;

/**
 * @brief ANC adder2 input mode select.
 *
 */
typedef enum
{
    ANC_FB_ERR_MIC_IN,               /**< err mic. */
    ANC_FB_ERR_MIC_IN_PLUS_RESAMPLE, /**< err mic + resample. */
} audio_anc_set_adder2_mode_e;

/**
 * @brief ANC adder3 output mode select.
 *
 */
typedef enum
{
    ANC_WZ_CZ_PLUS_RESAMPLE_TO_HEADPHONE, /**< wz + cz + resample. */
    ANC_WZ_CZ_TO_HEADPHONE,               /**< wz + cz. */
} audio_anc_set_adder3_mode_e;

/**
 * @brief ANC adder3 output data priority.
 *
 */
typedef enum
{
    ANC_WZ_CZ_FIRST,
    ANC_RESAMPLE_FIRST,
} audio_anc_adder3_out_pri_e;

/**
 * @brief ANC fb mode input data priority.
 *
 */
typedef enum
{
    ANC_HB_RESAMPLE_FIRST,
    ANC_HB_ERR0_FIRST,
} audio_anc_hb_input_pri_e;

/**
 * @brief ANC resample output fs decision.
 *
 */
typedef enum
{
    ANC_RESAMPLE_DAC_DECISION_FS,
    ANC_RESAMPLE_OTHERS_DECISION_FS, /**< i2s_rx, dac and hac, etc.*/
} audio_anc_resample_fs_decision_e;



/**********************************************************************************************************************
 *                                                Audio codec enum/struct                                             *
 *********************************************************************************************************************/
/*!
 * @name Audio codec enum/struct.
 * @{
 */

/**
 * @brief codec LDO ANA/CDC voltage selection.
 *
 */
typedef enum
{
    AUDIO_CODEC_LDO_ANA_CDC_1P5V,
    AUDIO_CODEC_LDO_ANA_CDC_1P55V,
    AUDIO_CODEC_LDO_ANA_CDC_1P6V,
    AUDIO_CODEC_LDO_ANA_CDC_1P65V,
    AUDIO_CODEC_LDO_ANA_CDC_1P7V,
    AUDIO_CODEC_LDO_ANA_CDC_1P75V,
    AUDIO_CODEC_LDO_ANA_CDC_1P8V,
    AUDIO_CODEC_LDO_ANA_CDC_1P85V,
} audio_codec_ldo_ana_cdc_e;

/**
 * @brief codec input select.
 *
 */
typedef enum
{
    AUDIO_LINEIN_ADC0           = BIT(0),
    AUDIO_LINEIN_ADC1           = BIT(1),
    AUDIO_LINEIN_ADC2           = BIT(2),
    AUDIO_LINEIN_ADC0_ADC1      = BIT(0) | BIT(1),
    AUDIO_LINEIN_ADC0_ADC2      = BIT(0) | BIT(2),
    AUDIO_LINEIN_ADC1_ADC2      = BIT(1) | BIT(2),
    AUDIO_LINEIN_ADC0_ADC1_ADC2 = BIT(0) | BIT(1) | BIT(2),

    AUDIO_AMIC_ADC0             = BIT(0) | BIT(3), /**< bit3: amic. */
    AUDIO_AMIC_ADC1             = BIT(1) | BIT(3),
    AUDIO_AMIC_ADC2             = BIT(2) | BIT(3),
    AUDIO_AMIC_ADC0_ADC1        = BIT(0) | BIT(1) | BIT(3),
    AUDIO_AMIC_ADC0_ADC2        = BIT(0) | BIT(2) | BIT(3),
    AUDIO_AMIC_ADC1_ADC2        = BIT(1) | BIT(2) | BIT(3),
    AUDIO_AMIC_ADC0_ADC1_ADC2   = BIT(0) | BIT(1) | BIT(2) | BIT(3),
} audio_codec_input_select_e;

/**@brief audio dac channel mute command*/
typedef enum {
    AUDIO_DAC_MUTE_DSM,
    AUDIO_DAC_MUTE_ANA,
} audio_dac_mute_cmd_t;

/**
 * @brief codec output channel.
 *
 */
typedef enum
{
    AUDIO_DAC_A0    = BIT(0),
    AUDIO_DAC_A1    = BIT(1),
    AUDIO_DAC_A0_A1 = BIT(0) | BIT(1),
} audio_codec_output_select_e;

/**
 * @brief codec input channel analog gain, [-6dB, 39dB], 3dB steps.
 */
typedef enum
{
    AUDIO_ADC_PGA_GAIN_N_6DB,
    AUDIO_ADC_PGA_GAIN_N_3DB,
    AUDIO_ADC_PGA_GAIN_0DB,
    AUDIO_ADC_PGA_GAIN_P_3DB,
    AUDIO_ADC_PGA_GAIN_P_6DB,
    AUDIO_ADC_PGA_GAIN_P_9DB,
    AUDIO_ADC_PGA_GAIN_P_12DB,
    AUDIO_ADC_PGA_GAIN_P_15DB,
    AUDIO_ADC_PGA_GAIN_P_18DB,
    AUDIO_ADC_PGA_GAIN_P_21DB,
    AUDIO_ADC_PGA_GAIN_P_24DB,
    AUDIO_ADC_PGA_GAIN_P_27DB,
    AUDIO_ADC_PGA_GAIN_P_30DB,
    AUDIO_ADC_PGA_GAIN_P_33DB,
    AUDIO_ADC_PGA_GAIN_P_36DB,
    AUDIO_ADC_PGA_GAIN_P_39DB,
} audio_codec_input_again_e;

/**
 * @brief codec input channel digital gain, [-69dB, 24dB], 3dB steps.
 * @note
 */
typedef enum
{
    AUDIO_ADC_DIG_GAIN_N_69DB = 0x03,
    AUDIO_ADC_DIG_GAIN_N_66DB = 0x0B,
    AUDIO_ADC_DIG_GAIN_N_63DB = 0x13,
    AUDIO_ADC_DIG_GAIN_N_60DB = 0x1B,
    AUDIO_ADC_DIG_GAIN_N_57DB = 0x23,
    AUDIO_ADC_DIG_GAIN_N_54DB = 0x2B,
    AUDIO_ADC_DIG_GAIN_N_51DB = 0x33,
    AUDIO_ADC_DIG_GAIN_N_48DB = 0x3B,
    AUDIO_ADC_DIG_GAIN_N_45DB = 0x43,
    AUDIO_ADC_DIG_GAIN_N_42DB = 0x4B,
    AUDIO_ADC_DIG_GAIN_N_39DB = 0x53,
    AUDIO_ADC_DIG_GAIN_N_36DB = 0x5B,
    AUDIO_ADC_DIG_GAIN_N_33DB = 0x63,
    AUDIO_ADC_DIG_GAIN_N_30DB = 0x6B,
    AUDIO_ADC_DIG_GAIN_N_27DB = 0x73,
    AUDIO_ADC_DIG_GAIN_N_24DB = 0x7B,
    AUDIO_ADC_DIG_GAIN_N_21DB = 0x83,
    AUDIO_ADC_DIG_GAIN_N_18DB = 0x8B,
    AUDIO_ADC_DIG_GAIN_N_15DB = 0x93,
    AUDIO_ADC_DIG_GAIN_N_12DB = 0x9B,
    AUDIO_ADC_DIG_GAIN_N_9DB  = 0xA3,
    AUDIO_ADC_DIG_GAIN_N_6DB  = 0xAB,
    AUDIO_ADC_DIG_GAIN_N_3DB  = 0xB3,
    AUDIO_ADC_DIG_GAIN_0DB    = 0xBB,
    AUDIO_ADC_DIG_GAIN_P_3DB  = 0xC3,
    AUDIO_ADC_DIG_GAIN_P_6DB  = 0xCB,
    AUDIO_ADC_DIG_GAIN_P_9DB  = 0xD3,
    AUDIO_ADC_DIG_GAIN_P_12DB = 0xDB,
    AUDIO_ADC_DIG_GAIN_P_15DB = 0xE3,
    AUDIO_ADC_DIG_GAIN_P_18DB = 0xEB,
    AUDIO_ADC_DIG_GAIN_P_21DB = 0xF3,
    AUDIO_ADC_DIG_GAIN_P_24DB = 0xFB,
} audio_codec_input_dgain_e;

/**
 * @brief codec output channel analog gain, [0dB, -18dB].
 */
typedef enum
{
    AUDIO_DAC_AUTX_GAIN_0DB,       /*   0db    */
    AUDIO_DAC_AUTX_GAIN_N_1_15DB,  /* -1.15db  */
    AUDIO_DAC_AUTX_GAIN_N_2_49DB,  /* -2.49db  */
    AUDIO_DAC_AUTX_GAIN_N_4_08DB,  /* -4.08db  */
    AUDIO_DAC_AUTX_GAIN_N_6_02DB,  /* -6.02db  */
    AUDIO_DAC_AUTX_GAIN_N_8_51DB,  /* -8.52db  */
    AUDIO_DAC_AUTX_GAIN_N_12_04DB, /* -12.04db */
    AUDIO_DAC_AUTX_GAIN_N_18_06DB, /* -18.06db */
} audio_codec_output_again_e;

/**
 * @brief codec output channel digital gain, [-69dB, 24dB], 3dB steps.
 * @note
 */
typedef enum
{
    AUDIO_DAC_DIG_GAIN_N_69DB = 0x03,
    AUDIO_DAC_DIG_GAIN_N_66DB = 0x0B,
    AUDIO_DAC_DIG_GAIN_N_63DB = 0x13,
    AUDIO_DAC_DIG_GAIN_N_60DB = 0x1B,
    AUDIO_DAC_DIG_GAIN_N_57DB = 0x23,
    AUDIO_DAC_DIG_GAIN_N_54DB = 0x2B,
    AUDIO_DAC_DIG_GAIN_N_51DB = 0x33,
    AUDIO_DAC_DIG_GAIN_N_48DB = 0x3B,
    AUDIO_DAC_DIG_GAIN_N_45DB = 0x43,
    AUDIO_DAC_DIG_GAIN_N_42DB = 0x4B,
    AUDIO_DAC_DIG_GAIN_N_39DB = 0x53,
    AUDIO_DAC_DIG_GAIN_N_36DB = 0x5B,
    AUDIO_DAC_DIG_GAIN_N_33DB = 0x63,
    AUDIO_DAC_DIG_GAIN_N_30DB = 0x6B,
    AUDIO_DAC_DIG_GAIN_N_27DB = 0x73,
    AUDIO_DAC_DIG_GAIN_N_24DB = 0x7B,
    AUDIO_DAC_DIG_GAIN_N_21DB = 0x83,
    AUDIO_DAC_DIG_GAIN_N_18DB = 0x8B,
    AUDIO_DAC_DIG_GAIN_N_15DB = 0x93,
    AUDIO_DAC_DIG_GAIN_N_12DB = 0x9B,
    AUDIO_DAC_DIG_GAIN_N_9DB  = 0xA3,
    AUDIO_DAC_DIG_GAIN_N_6DB  = 0xAB,
    AUDIO_DAC_DIG_GAIN_N_3DB  = 0xB3,
    AUDIO_DAC_DIG_GAIN_0DB    = 0xBB,
    AUDIO_DAC_DIG_GAIN_P_3DB  = 0xC3,
    AUDIO_DAC_DIG_GAIN_P_6DB  = 0xCB,
    AUDIO_DAC_DIG_GAIN_P_9DB  = 0xD3,
    AUDIO_DAC_DIG_GAIN_P_12DB = 0xDB,
    AUDIO_DAC_DIG_GAIN_P_15DB = 0xE3,
    AUDIO_DAC_DIG_GAIN_P_18DB = 0xEB,
    AUDIO_DAC_DIG_GAIN_P_21DB = 0xF3,
    AUDIO_DAC_DIG_GAIN_P_24DB = 0xFB,
} audio_codec_output_dgain_e;

/**
 * @brief Audio sample rate value.
 * |                                    |                            |
 * | :---------------------------------- | :------------------------- |
 * |            <31:8>                   |         <7:0>              |
 * |         audio_control_div           |       codec_fs             |
 * | fs = MCLK / (audio_control_div + 1) |   codec_freq_sel reg value |
 *
 * @note MCLK = 11.2896MHz(for 44.1kHz) or 12.288MHz (for others).
 */

/*******************************************************************
|codec_adc_clk  |pwr_mode |rate_sel  | codec_out_rate| oversample |
|6.144 MHz       | 0       | 0        |    48 kHz     |   128      |
|5.6448MHz       | 0       | 1        |    44.1 kHz   |   128      |
|6.144 MHz       | 0       | 2        |    96 kHz     |   64       |
|6.144 MHz       | 0       | 3        |    192 kHz    |   32       |
|6.144 MHz       | 0       | 4        |    384 kHz    |   16       |
|6.144 MHz       | 0       | 5        |    768 kHz    |   8        |
|6.144 MHz       | 0       | other    |    48 kHz     |   128      |
--------------------------------------------------------------------
|3.072 MHz       | 1       | 0        |    48 kHz     |   64       |
|2.048 MHz       | 1       | 1        |    32 kHz     |   64       |
|1.024 MHz       | 1       | 2        |    16 kHz     |   64       |
|0.512 MHz       | 1       | 3        |    8 kHz      |   64       |
|3.072 MHz       | 1       | other    |    48 kHz     |   64       |
********************************************************************/
typedef enum
{
    /* normal power mode */
    AUDIO_48K   = 0x00,
    AUDIO_44P1K = 0x01,
    AUDIO_96K   = 0x02,
    AUDIO_192K  = 0x03,
    AUDIO_384K  = 0x04,
    AUDIO_768K  = 0x05,
    /* low power mode */
    AUDIO_48K_L = 0x00 | BIT(4),
    AUDIO_32K   = 0x01 | BIT(4),
    AUDIO_16K   = 0x02 | BIT(4),
    AUDIO_8K    = 0x03 | BIT(4),
} audio_sample_rate_e;

typedef struct {
    audio_sample_rate_e rate;
    unsigned int clk;
} codec_clk_config_t;

#define AUDIO_CLK_TABLE_PLL1_START  0
#define AUDIO_CLK_TABLE_PLL0_96_START   11
#define AUDIO_CLK_TABLE_PLL0_192_START  22
#define AUDIO_CLK_TABLE_PLL0_240_START  33
#define AUDIO_CLK_TABLE_PLL0_288_START  44

static const codec_clk_config_t audio_codec_clk_config_table[] = {
    /* AUDIO SOURCE SELECT PLL1 */
    { AUDIO_CLK_TABLE_PLL1_START, 0 },
    /* normal power mode */
    { AUDIO_48K,   6144000 },
    { AUDIO_44P1K, 5644800 },
    { AUDIO_96K,   6144000 },
    { AUDIO_192K,  6144000 },
    { AUDIO_384K,  6144000 },
    { AUDIO_768K,  6144000 },
    /* low power mode */
    { AUDIO_48K_L, 3072000 },
    { AUDIO_32K,   2048000 },
    { AUDIO_16K,   1024000 },
    { AUDIO_8K,    512000  },

    /* AUDIO SOURCE SELECT PLL0 */
    { AUDIO_CLK_TABLE_PLL0_96_START, 0 },
    /* normal power mode */
    { AUDIO_48K,   6000000 },
    { AUDIO_44P1K, 6000000 },
    { AUDIO_96K,   6000000 },
    { AUDIO_192K,  6000000 },
    { AUDIO_384K,  6000000 },
    { AUDIO_768K,  6000000 },
    /* low power mode */
    { AUDIO_48K_L, 3000000 },
    { AUDIO_32K,   2000000 },
    { AUDIO_16K,   1000000 },
    { AUDIO_8K,     500000 },

    /* AUDIO SOURCE SELECT PLL0 */
    { AUDIO_CLK_TABLE_PLL0_192_START, 0 },
    /* normal power mode */
    { AUDIO_48K,   6193548 },
    { AUDIO_44P1K, 5647058 },
    { AUDIO_96K,   6193548 },
    { AUDIO_192K,  6193548 },
    { AUDIO_384K,  6193548 },
    { AUDIO_768K,  6193548 },
    /* low power mode */
    { AUDIO_48K_L, 3096770 },
    { AUDIO_32K,   2064516 },
    { AUDIO_16K,   1021276 },
    { AUDIO_8K,     510638 },

    /* AUDIO SOURCE SELECT PLL0 */
    { AUDIO_CLK_TABLE_PLL0_240_START, 0 },
    /* normal power mode */
    { AUDIO_48K,   6000000 },
    { AUDIO_44P1K, 6000000 },
    { AUDIO_96K,   6000000 },
    { AUDIO_192K,  6000000 },
    { AUDIO_384K,  6000000 },
    { AUDIO_768K,  6000000 },
    /* low power mode */
    { AUDIO_48K_L, 3000000 },
    { AUDIO_32K,   2000000 },
    { AUDIO_16K,   1000000 },
    { AUDIO_8K,     500000 },

      /* AUDIO SOURCE SELECT PLL0 */
    { AUDIO_CLK_TABLE_PLL0_288_START, 0 },
    /* normal power mode */
    { AUDIO_48K,   6127659 },
    { AUDIO_44P1K, 5647058 },
    { AUDIO_96K,   6127659 },
    { AUDIO_192K,  6127659 },
    { AUDIO_384K,  6127659 },
    { AUDIO_768K,  6127659 },
    /* low power mode */
    { AUDIO_48K_L, 3063829 },
    { AUDIO_32K,   2042553 },
    { AUDIO_16K,   1021276 },
    { AUDIO_8K,     510638 },
};

/**
 * @brief Audio codec data format.
 *
 */
typedef enum
{
    AUDIO_CODEC_BIT_16_DATA = 1,
    AUDIO_CODEC_BIT_24_DATA = 0,
} audio_codec_data_select_e;

/**
 * @brief Audio dmic data format.
 *
 */
typedef enum
{
    AUDIO_DMIC_BIT_16_DATA = 1,
    AUDIO_DMIC_BIT_24_DATA = 0,
} audio_dmic_data_select_e;

/**
 * @brief codec input config.
 *
 */
typedef struct
{
    audio_codec_input_select_e input_src;
    audio_sample_rate_e         sample_rate;
    audio_codec_data_select_e  data_format;
} audio_codec_input_config_t;


/**
 * @brief codec output config.
 *
 */
typedef struct
{
    audio_codec_output_select_e output_dst;
    audio_sample_rate_e          sample_rate;
    audio_codec_data_select_e   data_format;
} audio_codec_output_config_t;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio dmic enum/struct                                             *
 *********************************************************************************************************************/
/*!
 * @name Audio codec enum/struct.
 * @{
 */

/**
 * @brief dmic select.
 *
 */
typedef enum
{
    AUDIO_DMIC0,
    AUDIO_DMIC1,
} audio_dmic_channel_e;

/**
 * @brief dmic select.
 *
 */
typedef enum
{
    AUDIO_DMIC0_L         = BIT(0),
    AUDIO_DMIC0_R         = BIT(1),
    AUDIO_DMIC0_STEREO    = BIT(0) | BIT(1),
    AUDIO_DMIC1_L         = BIT(0) | BIT(2),
    AUDIO_DMIC1_R         = BIT(1) | BIT(2),
} audio_dmic_input_select_e;

/**
 * @brief codec output channel digital gain, [-64dB, 63dB], 1dB steps.
 */
typedef enum
{
    AUDIO_DMIC_D_GAIN_0DB = 0x0e, //default
} audio_dmic_dgain_e;


/**
 * @brief dmic input config.
 *
 */
typedef struct
{
    audio_dmic_input_select_e input_src;
    audio_sample_rate_e         sample_rate;
    audio_dmic_data_select_e  data_format;
    audio_dmic_dgain_e      d_gain;
} audio_dmic_input_config_t;


/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio dma/fifo enum/struct                                          *
 *********************************************************************************************************************/
/*!
 * @name Audio dma/fifo enum/struct.
 * @{
 */

/**
 * @brief FIFO channel.
 * 
 */
typedef enum
{
    FIFO0 = 0x00,
    FIFO1,
    FIFO2,
    FIFO3,
} audio_fifo_chn_e;

/**
 * @brief FIFO TX/RX IRQ type.
 * 
 */
typedef enum
{
    AUDIO_TX_FIFO0 = BIT(0),
    AUDIO_TX_FIFO1 = BIT(1),
    AUDIO_TX_FIFO2 = BIT(2),
    AUDIO_TX_FIFO3 = BIT(3),
    AUDIO_RX_FIFO0 = BIT(4),
    AUDIO_RX_FIFO1 = BIT(5),
    AUDIO_RX_FIFO2 = BIT(6),
    AUDIO_RX_FIFO3 = BIT(7),
} audio_fifo_type_e;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio hac enum/struct                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio hac enum/struct.
 * @{
 */

/**
 * @brief HAC channel.
 * 
 */
typedef enum
{
    HAC_CH0_EQ0 = 0x00,
    HAC_CH1_EQ1,
    HAC_CH2_ASRC0,
    HAC_CH3_ASRC1,
    HAC_CH4_EQ2,
} audio_hac_chn_e;

typedef enum
{
    HAC_EQ0 = 0x00,
    HAC_EQ1,
    HAC_EQ3,
} audio_hac_eq_chn_e;

typedef enum
{
    HAC_ASRC0 = 0x00,
    HAC_ASRC1,
} audio_hac_asrc_chn_e;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio asrc enum/struct                                              *
 *********************************************************************************************************************/

/**
 * @brief ASRC droop step.
 *
 */
typedef enum
{
    ASRC_DROOP_STEP_9TAPS,
    ASRC_DROOP_STEP_13TAPS,
    ASRC_DROOP_STEP_17TAPS,
} audio_asrc_droop_step_e;

/**
 * @}
 */

/**
 * @brief HAC biquad coefficient select.
 * 
 */
typedef enum
{
    HAC_BIQUAD0,
    HAC_BIQUAD1,
    HAC_BIQUAD2,
    HAC_BIQUAD3,
    HAC_BIQUAD4,
    HAC_BIQUAD5,
    HAC_BIQUAD6,
    HAC_BIQUAD7,
    HAC_BIQUAD8,
    HAC_BIQUAD9,
    HAC_BIQUAD_CNT,
} audio_hac_biquad_e;

/**
 * @brief HAC data input data select.
 *
 */
typedef enum
{
    HAC_INPUT_DATA_MATRIX,
    HAC_INPUT_DATA_MCU,
} audio_hac_input_data_e;

/**
 * @brief HAC data output select.
 *
 */
typedef enum
{
    HAC_OUTPUT_DATA_MATRIX,
    HAC_OUTPUT_DATA_AHB_MST,
} audio_hac_output_data_e;

/**
 * @brief hac tdm_tx_dma_ch num
 *
 */
typedef enum
{
    HAC_TDM_TX_DMA_2CH = 0x00,
    HAC_TDM_TX_DMA_4CH = 0x01,
    HAC_TDM_TX_DMA_6CH = 0x02,
    HAC_TDM_TX_DMA_8CH = 0x03,
} audio_hac_tdm_tx_dma_ch_e;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio i2s enum/struct                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio i2s enum struct.
 * @{
 */

/**
 * @brief I2S select.
 * 
 */
typedef enum
{
    I2S0,
    I2S1,
    I2S2,
} i2s_select_e;

/**
 * @brief I2S mode.
 * 
 */
typedef enum
{
    I2S_RJ_MODE,
    I2S_LJ_MODE,
    I2S_I2S_MODE,
    I2S_DSP_MODE,
    I2S_TDM_MODE, /**< only for i2s0. */
} i2s_mode_select_e;

/**
 * @brief TDM mode.
 * @note  Only for i2s0.
 */
typedef enum
{
    I2S_TDM_MODE_A,
    I2S_TDM_MODE_B,
    I2S_TDM_MODE_C,
} i2s_tdm_mode_select_e;

/**
 * @brief TDM channel.
 * @note  Only for i2s0.
 */
typedef enum
{
    I2S_TDM_2_CHN,
    I2S_TDM_4_CHN,
    I2S_TDM_6_CHN,
    I2S_TDM_8_CHN,
} i2s_tdm_chn_e;

/**
 * @brief TDM slot width.
 * @note  Only for i2s0.
 * 
 */
typedef enum
{
    I2S_TDM_SLOT_WIDTH_16,
    I2S_TDM_SLOT_WIDTH_24,
    I2S_TDM_SLOT_WIDTH_32,
} i2s_tdm_slot_width_e;

/**
 * @brief I2S line mode.
 * 
 */
typedef enum
{
    I2S_5_LINE_MODE,     /**< BCLK, ADC_LR_CLK, DAC_LR_CLK, ADC_DATA, DAC_DATA. */
    I2S_4_LINE_DAC_MODE, /**< BCLK, DAC_LR_CLK, ADC_DATA, DAC_DATA. */
    I2S_4_LINE_ADC_MODE, /**< BCLK, ADC_LR_CLK, ADC_DATA, DAC_DATA. */
    I2S_2_LANE_TX_MODE,  /**< ADC_DATA and DAC_DATA as TX at the same time. */
    I2S_2_LANE_RX_MODE,  /**< ADC_DATA and DAC_DATA as RX at the same time. */
} i2s_io_mode_e;

/**
 * @brief I2S word length.
 * 
 */
typedef enum
{
    I2S_BIT_16_DATA,
    I2S_BIT_20_DATA,
    I2S_BIT_24_DATA,
    I2S_BIT_32_DATA,
} i2s_wl_mode_e;

/**
 * @brief I2S master/slave select.
 * 
 */
typedef enum
{
    I2S_AS_SLAVE_EN,
    I2S_AS_MASTER_EN,
} i2s_m_s_mode_e;

/**
 * @brief I2S align mode.
 * 
 */
typedef enum
{
    I2S0_I2S1_ALIGN      = BIT(0) | BIT(1),
    I2S1_I2S2_ALIGN      = BIT(1) | BIT(2),
    I2S0_I2S1_I2S2_ALIGN = BIT(0) | BIT(1) | BIT(2),
} i2s_align_mode_e;

/**
 * @brief I2S align clk.
 * 
 */
typedef enum
{
    I2S_ALIGN_SELF_CLK, /**< use self i2s clk as align clk.*/
    I2S_ALIGN_CLK,      /**< use i2s1 clk as align clk.*/
} i2s_align_clk_e;

/**
 * @brief I2S data invert select.
 * 
 */
typedef enum
{
    I2S_DATA_INVERT_DIS,
    I2S_DATA_INVERT_EN,
} i2s_data_invert_e;

/**
 * @brief I2S CLK invert select.
 * 
 */
typedef enum
{
    I2S_LR_CLK_INVERT_DIS, /**< dsp mode: dsp mode a */
    I2S_LR_CLK_INVERT_EN,  /**< dsp mode: dsp mode b */
} i2s_lr_clk_invert_e;

/**
 * @brief I2S TX channel.
 * 
 */
typedef enum
{
    I2S0_CHN0,
    I2S0_CHN1,
    I2S0_CHN2,
    I2S0_CHN3,
    I2S0_CHN4,
    I2S0_CHN5,
    I2S0_CHN6,
    I2S0_CHN7,

    I2S1_CHN0,
    I2S1_CHN1,

    I2S2_CHN0,
    I2S2_CHN1,
} audio_i2s_tx_chn_e;

/**
 * @brief I2S invert config.
 * 
 */
typedef struct
{
    unsigned char i2s_lr_clk_invert_select;
    unsigned char i2s_data_invert_select;
} i2s_invert_config_t;

/**
 * @brief I2S pin config.
 * 
 */
typedef struct
{
    gpio_func_pin_e bclk_pin;
    gpio_func_pin_e adc_lr_clk_pin;
    gpio_func_pin_e adc_dat_pin;
    gpio_func_pin_e dac_lr_clk_pin;
    gpio_func_pin_e dac_dat_pin;
} i2s_pin_config_t;

/**
 * @brief I2S align config.
 * 
 */
typedef struct
{
    unsigned int     align_th; /**< align threshold*/
    i2s_align_mode_e align_mode;
    i2s_align_clk_e  align_clk;
} i2s_align_config_t;

/**
 * @brief I2S config.
 * 
 */
typedef struct
{
    unsigned short       *sample_rate;
    i2s_pin_config_t     *pin_config;
    i2s_select_e          i2s_select;
    i2s_wl_mode_e         data_width;
    i2s_mode_select_e     i2s_mode;
    i2s_tdm_mode_select_e tdm_mode;
    i2s_tdm_slot_width_e  tdm_slot_width;
    i2s_m_s_mode_e        master_slave_mode;
    i2s_io_mode_e         io_mode;
} audio_i2s_config_t;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio matrix enum/struct                                            *
 *********************************************************************************************************************/
/*!
 * @name Audio matrix enum/struct.
 * @{
 */

/**
 * @brief fifo rx route source select.
 * 
 */
typedef enum
{
    FIFO_RX_ROUTE_I2S0_RX = 0x01,
    FIFO_RX_ROUTE_I2S1_RX,
    FIFO_RX_ROUTE_I2S2_RX,
    FIFO_RX_ROUTE_ANC0,
    FIFO_RX_ROUTE_CODEC_768K = 0x06,
    FIFO_RX_ROUTE_CODEC_384K,
    FIFO_RX_ROUTE_CODEC_192K,
    FIFO_RX_ROUTE_CODEC_96K,
    // all codec sample rate could use this FIFO_RX_ROUTE_CODEC_48K(include 768K,384K,192K,96K,48K,44.1K,32K,16K,8K)
    FIFO_RX_ROUTE_CODEC_48K,
    FIFO_RX_ROUTE_DMIC_768K,
    FIFO_RX_ROUTE_DMIC_384K_LL,//DMIC_384k_low latency
    FIFO_RX_ROUTE_DMIC_192K_LL,//DMIC_192k_low latency
    FIFO_RX_ROUTE_DMIC_384K,
    FIFO_RX_ROUTE_DMIC_192K,
    FIFO_RX_ROUTE_DMIC_96K,
    FIFO_RX_ROUTE_DMIC_32K,
    FIFO_RX_ROUTE_DMIC_16K_OR_48K,
    FIFO_RX_ROUTE_SPDIF_RX,
    FIFO_RX_ROUTE_USB_ISO_RX,
    FIFO_RX_ROUTE_EQ0,
    FIFO_RX_ROUTE_EQ1,
    FIFO_RX_ROUTE_EQ2,
    FIFO_RX_ROUTE_ASRC0_TDM0_DATA,
    FIFO_RX_ROUTE_ASRC1_TDM1_DATA,
} audio_matrix_fifo_rx_route_e;

/**
 * @brief fifo rx route data format select.
 * 
 */
typedef enum
{
    /* fifo rx route i2s data format */
    FIFO_RX_I2S_RX_CHN01_20_OR_24 = 0x00, /**< fifo rx route from i2s data format. */
    FIFO_RX_I2S_RX_CHN01_16,
    FIFO_RX_I2S_RX_CHN0_20_OR_24,
    FIFO_RX_I2S_RX_CHN0_16,
    FIFO_RX_I2S_RX_CHN1_20_OR_24,
    FIFO_RX_I2S_RX_CHN1_16,

    FIFO_RX_I2S1_I2S0_CHN01_20_OR_24 = 0x06,  /**< i2s1_ch0 + i2s1_ch1 + i2s0_ch0 + i2s0_ch1 20/24bit */
    FIFO_RX_I2S1_I2S0_CHN01_16,               /**< i2s1_ch1+i2s1_ch0+i2s0_ch1+i2s0_ch0 16bit */

    /* fifo rx route anc data format */
    FIFO_RX_ANC_POST_PRE_32BIT = 0x00, /**< fifo rx route from anc0 data common format. */
    FIFO_RX_ANC_POST_PRE_16BIT,
    FIFO_RX_ANC_SPEAKER_OUT,
    FIFO_RX_ANC_BZ_OUT,

    /* fifo rx route from codec adc or dmic data format */
    FIFO_RX_CODEC_OR_DMIC_A0_A1_32BIT = 0x00, /**< fifo rx route from codec adc or dmic data format. */
    FIFO_RX_CODEC_OR_DMIC_A0_A1_16BIT,
    FIFO_RX_CODEC_OR_DMIC_A0_A1_A2_32BIT,
    FIFO_RX_CODEC_OR_DMIC_A0_32BIT,
    FIFO_RX_CODEC_OR_DMIC_A0_16BIT,
    FIFO_RX_CODEC_OR_DMIC_A1_32BIT,
    FIFO_RX_CODEC_OR_DMIC_A1_16BIT,
    FIFO_RX_CODEC_OR_DMIC_A2_32BIT,
    FIFO_RX_CODEC_OR_DMIC_A2_16BIT,

    FIFO_RX_HAC_EQ_MONO_16BIT = 0x01, /**< fifo rx route from hac0(eq0)/hac1(eq1)/hac4(eq2) common data format. */
    FIFO_RX_HAC_EQ_MONO_20_OR_24BIT,

    FIFO_RX_HAC_ASRC_MONO_16BIT = 0x01,    /**< fifo rx route from hac2(asrc_tdm0)/hac3(asrc_tdm1) data format. */
    FIFO_RX_HAC_ASRC_MONO_20_OR_24BIT,
    FIFO_RX_HAC_ASRC_STEREO_16BIT,
    FIFO_RX_HAC_ASRC_STEREO_20_OR_24BIT,

    FIFO_RX_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_fifo_rx_format_e;

/**
 * @brief i2s tx route source select.
 * 
 */
typedef enum
{
    I2S_TX_ROUTE_FIFO = 0x01, /**< I2S channel 0/1 route. */
    I2S_TX_ROUTE_ANC0_SPEAKER,
    I2S_TX_ROUTE_HAC_DATA0,
    I2S_TX_ROUTE_HAC_DATA1,
    I2S_TX_ROUTE_HAC_TDM0_DATA0123,
    I2S_TX_ROUTE_HAC_TDM1_DATA0123,
    I2S_TX_ROUTE_HAC_TDM01_DATA0123,

    TDM0_TX_ROUTE_HAC_TDM0_DATA0123 = 0x02, /**< tdm channel 2-7 route. */
    TDM1_TX_ROUTE_HAC_TDM1_DATA0123,
} audio_matrix_i2s_tx_route_e;

/**
 * @brief i2s tx route data format select.
 * 
 */
typedef enum
{
    I2S_TX_FIFO0_20_OR_24_MONO = 0x00, /**< i2s common config */
    I2S_TX_FIFO1_20_OR_24_MONO,
    I2S_TX_FIFO2_20_OR_24_MONO,
    I2S_TX_FIFO3_20_OR_24_MONO,
    I2S_TX_FIFO01_20_OR_24_STEREO,
    I2S_TX_FIFO23_20_OR_24_STEREO,
    I2S_TX_FIFO0_20_OR_24_STEREO,
    I2S_TX_FIFO1_20_OR_24_STEREO,
    I2S_TX_FIFO2_20_OR_24_STEREO,
    I2S_TX_FIFO3_20_OR_24_STEREO,
    I2S_TX_FIFO0_16_MONO,
    I2S_TX_FIFO1_16_MONO,
    I2S_TX_FIFO2_16_MONO,
    I2S_TX_FIFO3_16_MONO,
    I2S_TX_FIFO01_16_STEREO,
    I2S_TX_FIFO23_16_STEREO,
    I2S_TX_FIFO0_16_STEREO,
    I2S_TX_FIFO1_16_STEREO,
    I2S_TX_FIFO2_16_STEREO,
    I2S_TX_FIFO3_16_STEREO,

    I2S0_TX_FIFO0_16_STEREO_I2S01 = 0x14, /**< for i2s0 config */
    I2S0_TX_FIFO1_16_STEREO_I2S01,
    I2S0_TX_FIFO2_16_STEREO_I2S01,
    I2S0_TX_FIFO3_16_STEREO_I2S01,
    I2S0_TX_FIFO0_20_OR_24_STEREO_I2S01,
    I2S0_TX_FIFO1_20_OR_24_STEREO_I2S01,
    I2S0_TX_FIFO2_20_OR_24_STEREO_I2S01,
    I2S0_TX_FIFO3_20_OR_24_STEREO_I2S01,
    I2S0_TX_FIFO0_20_OR_24_TDM_I2S0,
    I2S0_TX_FIFO1_20_OR_24_TDM_I2S0,
    I2S0_TX_FIFO2_20_OR_24_TDM_I2S0,
    I2S0_TX_FIFO3_20_OR_24_TDM_I2S0,
    I2S_TX_FIFO0_16_TDM_I2S0,
    I2S_TX_FIFO1_16_TDM_I2S0,
    I2S_TX_FIFO2_16_TDM_I2S0,
    I2S_TX_FIFO3_16_TDM_I2S0,
    I2S_TX_FIFO0_16_STEREO_I2S012,
    I2S_TX_FIFO0_20_OR_24_STEREO_I2S012,

    I2S1_TX_FIFO0_16_STEREO_I2S01 = 0x14, /**< for i2s1 config */
    I2S1_TX_FIFO1_16_STEREO_I2S01,
    I2S1_TX_FIFO2_16_STEREO_I2S01,
    I2S1_TX_FIFO3_16_STEREO_I2S01,
    I2S1_TX_FIFO0_20_OR_24_STEREO_I2S01,
    I2S1_TX_FIFO1_20_OR_24_STEREO_I2S01,
    I2S1_TX_FIFO2_20_OR_24_STEREO_I2S01,
    I2S1_TX_FIFO3_20_OR_24_STEREO_I2S01,
    I2S1_TX_FIFO0_16_STEREO_I2S012,
    I2S1_TX_FIFO0_20_OR_24_STEREO_I2S012,
    I2S1_TX_FIFO0_16_STEREO_I2S12,
    I2S1_TX_FIFO0_20_OR_24_STEREO_I2S12,

    I2S2_TX_FIFO0_16_STEREO_I2S012 = 0x14, /**< for i2s2 config */
    I2S2_TX_FIFO0_20_OR_24_STEREO_I2S012,
    I2S2_TX_FIFO0_16_STEREO_I2S12,
    I2S2_TX_FIFO0_20_OR_24_STEREO_I2S12,

    I2S_TX_HAC_1CH = 1, /**< for i2s tx hac common config */
    I2S_TX_HAC_2CH = 2,
    I2S_TX_HAC_TDM = 3,

    I2S0_TX_HAC_2LINE          = 4, /**< for i2s0 tx hac config */
    I2S0_TX_HAC_I2S01_SYNC     = 5,
    I2S0_TX_HAC_I2S012_SYNC    = 6,
    I2S0_TX_HAC_TDM_HAC3_FIRST = 7,

    I2S1_TX_HAC_2LINE       = 4, /**< for i2s1 tx hac config */
    I2S1_TX_HAC_I2S01_SYNC  = 5,
    I2S1_TX_HAC_I2S12_SYNC  = 6,
    I2S1_TX_HAC_I2S012_SYNC = 7,

    I2S2_TX_HAC_I2S12_SYNC  = 4,  /**< for i2s1 tx hac config */
    I2S2_TX_HAC_I2S012_SYNC = 5,

    I2S_TX_HAC_CH01_20_OR_24 = 0, /**< for i2s rx hac common config */
    I2S_TX_HAC_CH0_20_OR_24  = 2,
    I2S_TX_HAC_CH1_20_OR_24  = 4,
    I2S_TX_HAC_TDM2_FIRST    = 6,
    I2S_TX_HAC_TDM3_FIRST    = 7,

    I2S_RX_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_i2s_tx_format_e;

/**
 * @brief anc_src route source select.
 * 
 */
typedef enum
{
    ANC_SRC_ROUTE_FIFO = 0x01,
    ANC_SRC_ROUTE_I2S0_RX,
    ANC_SRC_ROUTE_I2S1_RX,
    ANC_SRC_ROUTE_I2S2_RX,
    ANC_SRC_ROUTE_CODEC_96K,
    ANC_SRC_ROUTE_CODEC_48K,
    ANC_SRC_ROUTE_DMIC_96K,
    ANC_SRC_ROUTE_DMIC_16K_OR_48K,
    ANC_SRC_ROUTE_EQ0,
    ANC_SRC_ROUTE_EQ1,
    ANC_SRC_ROUTE_EQ2,
    ANC_SRC_ROUTE_ASRC0_TDM0_DATA0,
    ANC_SRC_ROUTE_ASRC0_TDM0_DATA1,
    ANC_SRC_ROUTE_ASRC1_TDM1_DATA0,
    ANC_SRC_ROUTE_ASRC1_TDM1_DATA1,
} audio_matrix_anc_src_route_e;

/**
 * @brief anc_src route data format select.
 * 
 */
typedef enum
{
    ANC_SRC_DATA_FIFO0, /**< anc src route from fifo data format select. */
    ANC_SRC_DATA_FIFO1,
    ANC_SRC_DATA_FIFO2,
    ANC_SRC_DATA_FIFO3,

    ANC_SRC_I2S_CH0_20_OR_24_BIT = 0x02, /**< anc src route from i2s data format select. */
    ANC_SRC_I2S_CH1_20_OR_24_BIT = 0x04,

    ANC_SRC_CODEC_ADCA0_32_BIT = 0x00,     /**< anc src route from codec 96k or 48k data format select. */
    ANC_SRC_CODEC_ADCA1_32_BIT = 0x01,
    ANC_SRC_CODEC_ADCA2_32_BIT = 0x02,

    ANC_SRC_DMIC_A0_32_BIT = 0x00,     /**< anc src route from dmic 96k or 48k data format select. */
    ANC_SRC_DMIC_A1_32_BIT = 0x01,
    ANC_SRC_DMIC_A2_32_BIT = 0x02,

    ANC_SRC_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_anc_src_format_e;

/**
 * @brief anc_ref route source select.
 * 
 */
typedef enum
{
    ANC_REF_ROUTE_I2S0_RX = 0x01,
    ANC_REF_ROUTE_I2S1_RX,
    ANC_REF_ROUTE_I2S2_RX,
    ANC_REF_ROUTE_CODEC_768K,
    ANC_REF_ROUTE_CODEC_384K,
    ANC_REF_ROUTE_CODEC_192K,
    ANC_REF_ROUTE_DMIC_768K,
    ANC_REF_ROUTE_DMIC_384K_LL,//DMIC_384k_low latency
    ANC_REF_ROUTE_DMIC_192K_LL,//DMIC_192k_low latency
    ANC_REF_ROUTE_EQ0,
    ANC_REF_ROUTE_EQ1,
    ANC_REF_ROUTE_EQ2,
    ANC_REF_ROUTE_ASRC0_TDM0_DATA0,
    ANC_REF_ROUTE_ASRC0_TDM0_DATA1,
    ANC_REF_ROUTE_ASRC1_TDM1_DATA0,
    ANC_REF_ROUTE_ASRC1_TDM1_DATA1,
} audio_matrix_anc_ref_route_e;

/**
 * @brief anc_ref route data format select.
 * 
 */
typedef enum
{
    ANC_REF_I2S_CH0_20_OR_24_BIT = 0x02, /**< anc ref route from i2s data format select. */
    ANC_REF_I2S_CH1_20_OR_24_BIT = 0x04,

    ANC_REF_CODEC_OR_DMIC_A0_32_BIT = 0x00,     /**< anc ref route from codec adc or dmic data format select. */
    ANC_REF_CODEC_OR_DMIC_A1_32_BIT = 0x01,
    ANC_REF_CODEC_OR_DMIC_A2_32_BIT = 0x02,

    ANC_REF_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_anc_ref_format_e;

/**
 * @brief anc_err route source select.
 * 
 */
typedef enum
{
    ANC_ERR_ROUTE_I2S0_RX = 0x01,
    ANC_ERR_ROUTE_I2S1_RX,
    ANC_ERR_ROUTE_I2S2_RX,
    ANC_ERR_ROUTE_CODEC_768K,
    ANC_ERR_ROUTE_CODEC_384K,
    ANC_ERR_ROUTE_CODEC_192K,
    ANC_ERR_ROUTE_DMIC_768K,
    ANC_ERR_ROUTE_DMIC_384K_LL,//DMIC_384k_low latency
    ANC_ERR_ROUTE_DMIC_192K_LL,//DMIC_192k_low latency
    ANC_ERR_ROUTE_EQ0,
    ANC_ERR_ROUTE_EQ1,
    ANC_ERR_ROUTE_EQ2,
    ANC_ERR_ROUTE_ASRC0_TDM0_DATA0,
    ANC_ERR_ROUTE_ASRC0_TDM0_DATA1,
    ANC_ERR_ROUTE_ASRC1_TDM1_DATA0,
    ANC_ERR_ROUTE_ASRC1_TDM1_DATA1,
} audio_matrix_anc_err_route_e;

/**
 * @brief anc_err route data format select.
 *
 */
typedef enum
{
    ANC_ERR_I2S_CH0_20_OR_24_BIT = 0x02, /**< anc err route from i2s data format select. */
    ANC_ERR_I2S_CH1_20_OR_24_BIT = 0x04,

    ANC_ERR_CODEC_OR_DMIC_A0_32_BIT = 0x00,     /**< anc ref route from codec adc or dmic data format select. */
    ANC_ERR_CODEC_OR_DMIC_A1_32_BIT = 0x01,
    ANC_ERR_CODEC_OR_DMIC_A2_32_BIT = 0x02,

    ANC_ERR_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_anc_err_format_e;

/**
 * @brief anc bz route source select.
 *
 */
typedef enum
{
    ANC_BZ_ROUTE_I2S0_RX = 0x0e,
    ANC_BZ_ROUTE_I2S1_RX,
    ANC_BZ_ROUTE_I2S2_RX,
    ANC_BZ_ROUTE_CODEC_768K = 0x01,
    ANC_BZ_ROUTE_CODEC_384K,
    ANC_BZ_ROUTE_CODEC_192K,
    ANC_BZ_ROUTE_CODEC_96K,
    ANC_BZ_ROUTE_CODEC_48K,
    ANC_BZ_ROUTE_DMIC_768K,
    ANC_BZ_ROUTE_DMIC_384K_LL,//DMIC_384k_low latency
    ANC_BZ_ROUTE_DMIC_192K_LL,//DMIC_192k_low latency
    ANC_BZ_ROUTE_DMIC_384K,
    ANC_BZ_ROUTE_DMIC_192K,
    ANC_BZ_ROUTE_DMIC_96K,
    ANC_BZ_ROUTE_DMIC_32K,
    ANC_BZ_ROUTE_DMIC_16K_OR_48K,
} audio_matrix_anc_bz_route_e;

/**
 * @brief anc_err route data format select.
 * 
 */
typedef enum
{
    ANC_BZ_I2S_CH0_20_OR_24_BIT = 0x02, /**< anc bz route from i2s data format select. */
    ANC_BZ_I2S_CH1_20_OR_24_BIT = 0x04,

    ANC_BZ_CODEC_OR_DMIC_A0_32_BIT = 0x00,     /**< anc bz route from codec adc or dmic data format select. */
    ANC_BZ_CODEC_OR_DMIC_A1_32_BIT = 0x01,
    ANC_BZ_CODEC_OR_DMIC_A2_32_BIT = 0x02,

    ANC_BZ_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_anc_bz_format_e;

/**
 * @brief dac route source select.
 * 
 */
typedef enum
{
    DAC_ROUTE_FIFO = 0x01,
    DAC_ROUTE_ANC0_SPEAKER,
    DAC_ROUTE_ANC1_SPEAKER,
    DAC_ROUTE_HAC_DATA0,
    DAC_ROUTE_HAC_DATA1,
    DAC_ROUTE_HAC_TDM0_DATA0,
    DAC_ROUTE_HAC_TDM0_DATA1,
    DAC_ROUTE_HAC_TDM0_DATA2,
    DAC_ROUTE_HAC_TDM0_DATA3,
    DAC_ROUTE_HAC_TDM1_DATA0,
    DAC_ROUTE_HAC_TDM1_DATA1,
    DAC_ROUTE_HAC_TDM1_DATA2,
    DAC_ROUTE_HAC_TDM1_DATA3,
} audio_matrix_dac_route_e;

/**
 * @brief dac route data format select.
 * 
 */
typedef enum
{
    DAC_FIFO_MONO_24BIT_FIFO0, /**< dac route from fifo data format select. */
    DAC_FIFO_MONO_24BIT_FIFO1,
    DAC_FIFO_MONO_24BIT_FIFO2,
    DAC_FIFO_MONO_24BIT_FIFO3,
    DAC_FIFO_STEREO_24BIT_FIFO0,
    DAC_FIFO_STEREO_24BIT_FIFO1,
    DAC_FIFO_STEREO_24BIT_FIFO2,
    DAC_FIFO_STEREO_24BIT_FIFO3,
    DAC_FIFO_STEREO_24BIT_2FIFO0,
    DAC_FIFO_STEREO_24BIT_2FIFO2,
    DAC_FIFO_MONO_16BIT_FIFO0,
    DAC_FIFO_MONO_16BIT_FIFO1,
    DAC_FIFO_MONO_16BIT_FIFO2,
    DAC_FIFO_MONO_16BIT_FIFO3,
    DAC_FIFO_STEREO_16BIT_FIFO0,
    DAC_FIFO_STEREO_16BIT_FIFO1,
    DAC_FIFO_STEREO_16BIT_FIFO2,
    DAC_FIFO_STEREO_16BIT_FIFO3,
    DAC_FIFO_STEREO_16BIT_2FIFO0,
    DAC_FIFO_STEREO_16BIT_2FIFO2,

    DAC_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_dac_format_e;

/**
 * @brief spdif tx route source select.
 * 
 */
typedef enum
{
    SPDIF_TX_ROUTE_FIFO0 = 0x01,
    SPDIF_TX_ROUTE_FIFO1,
    SPDIF_TX_ROUTE_FIFO2,
    SPDIF_TX_ROUTE_FIFO3,
    SPDIF_TX_ROUTE_HAC_DATA0,
    SPDIF_TX_ROUTE_HAC_DATA1,
    SPDIF_TX_ROUTE_HAC_TDM0_DATA0,
    SPDIF_TX_ROUTE_HAC_TDM0_DATA1,
    SPDIF_TX_ROUTE_HAC_TDM0_DATA2,
    SPDIF_TX_ROUTE_HAC_TDM0_DATA3,
    SPDIF_TX_ROUTE_HAC_TDM1_DATA0,
    SPDIF_TX_ROUTE_HAC_TDM1_DATA1,
    SPDIF_TX_ROUTE_HAC_TDM1_DATA2,
    SPDIF_TX_ROUTE_HAC_TDM1_DATA3,
} audio_matrix_spdif_tx_route_e;

/**
 * @brief hac route source select.
 * 
 */
typedef enum
{
    HAC_DATA_ROUTE_FIFO0 = 0x01,
    HAC_DATA_ROUTE_FIFO1,
    HAC_DATA_ROUTE_FIFO2,
    HAC_DATA_ROUTE_FIFO3,
    HAC_DATA_ROUTE_I2S0_RX,
    HAC_DATA_ROUTE_I2S1_RX,
    HAC_DATA_ROUTE_I2S2_RX,
    HAC_DATA_ROUTE_ANC0_PRE,
    HAC_DATA_ROUTE_ANC0_POST,
    HAC_DATA_ROUTE_ANC0_SPEAKER,

    HAC_DATA_ROUTE_SPDIF_RX,
    HAC_DATA_ROUTE_USB_ISO_RX,
} audio_matrix_hac_route_e;

/**
 * @brief hac route data format select.
 * 
 */
typedef enum
{
    HAC_EQ_16_BIT       = 0x01,
    HAC_EQ_20_OR_24_BIT = 0x02,                          /**< hac0(eq0)/hac1(eq1)/hac4(eq2) route from DMA common data format select. */

    HAC_ASRC_TDM_20_OR_24_BIT_HAC2_FIRST         = 0x00, /**< hac2(asrc0)/hac3(asrc1) route from DMA common data format select. */
    HAC_ASRC_16_BIT                              = 0x01,
    HAC_ASRC_20_OR_24_BIT                        = 0x02,
    HAC_ASRC_I2S012_SYNC_16_BIT_HAC2_FIRST       = 0x03,
    HAC_ASRC_I2S012_SYNC_20_OR_24_BIT_HAC2_FIRST = 0x04,
    HAC_ASRC_TDM_16_BIT_HAC3_FIRST               = 0x05,
    HAC_ASRC_TDM_20_OR_24_BIT_HAC3_FIRST         = 0x06,
    HAC_ASRC_TDM_16_BIT_HAC2_FIRST               = 0x07,

    HAC_EQ_I2S_CH0_20_OR_24_BIT = 0x02,  /**< hac0(eq0)/hac1(eq1)/hac4(eq2) route from i2s common data format select. */
    HAC_EQ_I2S_CH1_20_OR_24_BIT = 0x04,

    HAC_ASRC_I2S_CH01_20_OR_24_BIT = 0x00, /**< hac2(asrc0)/hac3(asrc1) route from i2s common data format select. */
    HAC_ASRC_I2S_CH0_20_OR_24_BIT  = 0x02,
    HAC_ASRC_I2S_CH1_20_OR_24_BIT  = 0x04,
    HAC_ASRC_I2S_TDM_HAC2_FIRST    = 0x06,
    HAC_ASRC_I2S_TDM_HAC3_FIRST    = 0x07,

    HAC_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_hac_format_e;

/**
 * @brief side_tone route source select.
 * 
 */
typedef enum
{
    SIDE_TONE_ROUTE_FIFO = 0x01,
    SIDE_TONE_ROUTE_I2S0_RX,
    SIDE_TONE_ROUTE_I2S1_RX,
    SIDE_TONE_ROUTE_I2S2_RX,
    SIDE_TONE_ROUTE_ADC0,
    SIDE_TONE_ROUTE_ADC1,
    SIDE_TONE_ROUTE_ADC2,
    SIDE_TONE_ROUTE_SPDIF_RX,
    SIDE_TONE_ROUTE_HAC_DATA0,
    SIDE_TONE_ROUTE_HAC_DATA1,
    SIDE_TONE_TX_ROUTE_HAC_TDM0_DATA0,
    SIDE_TONE_TX_ROUTE_HAC_TDM0_DATA1,
    SIDE_TONE_TX_ROUTE_HAC_TDM0_DATA2,
    SIDE_TONE_TX_ROUTE_HAC_TDM0_DATA3,
    SIDE_TONE_TX_ROUTE_HAC_TDM1_DATA0,
    SIDE_TONE_TX_ROUTE_HAC_TDM1_DATA1,
    SIDE_TONE_TX_ROUTE_HAC_TDM1_DATA2,
    SIDE_TONE_TX_ROUTE_HAC_TDM1_DATA3,
} audio_matrix_side_tone_route_e;

/**
 * @brief side_tone route data format select.
 * 
 */
typedef enum
{
    SIDE_TONE_FIFO0_20_OR_24_MONO = 0x00, /**< side_tone route from fifo data format select. */
    SIDE_TONE_FIFO1_20_OR_24_MONO,
    SIDE_TONE_FIFO2_20_OR_24_MONO,
    SIDE_TONE_FIFO3_20_OR_24_MONO,
    SIDE_TONE_FIFO01_20_OR_24_STEREO,
    SIDE_TONE_FIFO23_20_OR_24_STEREO,
    SIDE_TONE_FIFO0_20_OR_24_STEREO,
    SIDE_TONE_FIFO1_20_OR_24_STEREO,
    SIDE_TONE_FIFO2_20_OR_24_STEREO,
    SIDE_TONE_FIFO3_20_OR_24_STEREO,
    SIDE_TONE_FIFO0_16_MONO,
    SIDE_TONE_FIFO1_16_MONO,
    SIDE_TONE_FIFO2_16_MONO,
    SIDE_TONE_FIFO3_16_MONO,
    SIDE_TONE_FIFO01_16_STEREO,
    SIDE_TONE_FIFO23_16_STEREO,
    SIDE_TONE_FIFO0_16_STEREO,
    SIDE_TONE_FIFO1_16_STEREO,
    SIDE_TONE_FIFO2_16_STEREO,
    SIDE_TONE_FIFO3_16_STEREO,

    SIDE_TONE_I2S_CH0_20_OR_24_BIT = 0x02, /**< side_tone route from i2s data format select. */
    SIDE_TONE_I2S_CH1_20_OR_24_BIT = 0x04,

    SIDE_TONE_ADC_LEFT_32_BIT  = 0x02,     /**< side_tone route from adc data format select. */
    SIDE_TONE_ADC_RIGHT_32_BIT = 0x04,

    SIDE_TONE_DATA_FORMAT_INVALID = 0xff,
} audio_matrix_side_tone_format_e;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio side_tone enum/struct                                         *
 *********************************************************************************************************************/
/*!
 * @name Audio side_tone enum/struct.
 * @{
 */

/**
 * @brief side_tone channel.
 * 
 */
typedef enum
{
    SIDE_TONE_CHN0 = 0x00,
    SIDE_TONE_CHN1,
    SIDE_TONE_CHN2,
    SIDE_TONE_CHN3,
    SIDE_TONE_CHN4,
    SIDE_TONE_CHN5,
    SIDE_TONE_CHN6,
    SIDE_TONE_CHN7,
} audio_side_tone_chn_e;

/**
 * @brief side_tone channels.
 *
 */
typedef enum
{
    SIDE_TONE_CHN01 = 0x00,
    SIDE_TONE_CHN23,
    SIDE_TONE_CHN45,
    SIDE_TONE_CHN67,
} audio_side_tone_chns_e;

/**
 * @brief side_tone gain.
 */
typedef enum
{
    SIDETONE_m30_DB = 0,
    SIDETONE_m27_DB,
    SIDETONE_m24_DB,
    SIDETONE_m21_DB,
    SIDETONE_m18_DB,
    SIDETONE_m15_DB,
    SIDETONE_m12_DB,
    SIDETONE_m9_DB,
    SIDETONE_m6_DB,
    SIDETONE_m3_DB,
    SIDETONE_0DB,
    SIDETONE_3DB,
    SIDETONE_6DB,
    SIDETONE_9DB,
    SIDETONE_12DB,
    SIDETONE_15DB,
} audio_side_tone_gain_e;

/**********************************************************************************************************************
 *                                                Audio spdif enum/struct                                             *
 *********************************************************************************************************************/
/*!
 * @name Audio spdif enum/struct
 * @{
 */

/**
 * @brief spdif tx clk config.
 * 
 */
typedef enum
{
    SPDIF_TX_CLK_32K   = 18,
    SPDIF_TX_CLK_44P1K = 15,
    SPDIF_TX_CLK_48K   = 12,
    SPDIF_TX_CLK_96K   = 6,
    SPDIF_TX_CLK_192K  = 3,
} spdif_tx_clk_e;

typedef enum
{
    SPDIF_PREAMBLE_B = 0x01,
    SPDIF_PREAMBLE_M,
    SPDIF_PREAMBLE_W,
} spdif_preamble_e;

/**
 * @brief spdif pin config.
 * 
 */
typedef struct
{
    gpio_func_pin_e spdif_rx_pin;
    gpio_func_pin_e spdif_tx_pin;
} spdif_pin_config_t;

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio anc interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio anc interface.
 * @{
 */

/**
 * @brief      This function serves to enable anc clock.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_anc_clk_en(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_en_1 |= FLD_CLK_ANC0_EN;
}

/**
 * @brief      This function serves to disable anc clock.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_anc_clk_dis(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_en_1 &= ~FLD_CLK_ANC0_EN;
}

/**
 * @brief      This function serves to enable anc reset.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_anc_rst_en(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_rst_en_2 |= FLD_CLK_RST_ANC0_FCLK_EN;
}

/**
 * @brief      This function serves to disable anc reset.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_anc_rst_dis(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_rst_en_2 &= ~FLD_CLK_RST_ANC0_FCLK_EN;
}

/**
 * @brief      This function serves to enable anc resample reset.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_resample_rst_en(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_rst_en_2 |= FLD_CLK_RST_ANC0_RSMP_N_EN;
}

/**
 * @brief      This function serves to disable anc resample reset.
 * @param[in]  anc_chn  - anc channel.
 * @return     none
 */
static inline void audio_resample_rst_dis(audio_anc_chn_e anc_chn)
{
    (void)anc_chn;
    reg_audio_clk_rst_en_2 &= ~FLD_CLK_RST_ANC0_RSMP_N_EN;
}

/**
 * @brief      This function serves to set anc mode.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  anc_mode - anc mode.
 * @return     none
 */
static inline void audio_anc_set_mode(audio_anc_chn_e anc_chn, audio_anc_mode_e anc_mode)
{
    reg_audio_anc_config2(anc_chn) = (reg_audio_anc_config2(anc_chn) & (~FLD_ANC_MODE_SEL)) | MASK_VAL(FLD_ANC_MODE_SEL, anc_mode);
}

/**
 * @brief      This function serves to select anc adder2 input mode.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  input_mode - adder2 input mode select.
 * @note
 */

static inline void audio_anc_set_adder2_mode(audio_anc_chn_e anc_chn, audio_anc_set_adder2_mode_e input_mode)
{
    reg_audio_anc_config2(anc_chn) = (reg_audio_anc_config2(anc_chn) & (~FLD_ANC_ADD_CZ1_SEL)) | MASK_VAL(FLD_ANC_ADD_CZ1_SEL, input_mode);
}

/**
 * @brief      This function serves to select anc adder3 output mode.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  output_mode - adder3 output mode select.
 * @note
 */

static inline void audio_anc_set_adder3_mode(audio_anc_chn_e anc_chn, audio_anc_set_adder3_mode_e output_mode)
{
    reg_audio_anc_config2(anc_chn) = (reg_audio_anc_config2(anc_chn) & (~FLD_ANC_ADD_SRC_SEL)) | MASK_VAL(FLD_ANC_ADD_SRC_SEL, output_mode);
}

/**
 * @brief      This function serves to select anc adder3 output data priority.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  mode_sel - adder3 output data priority.
 * @note
 *        - The adder3 output is the sum of wz and resample, but the two are not consistent in terms of time, this register is used to select which timing is first.
 */
static inline void audio_anc_set_adder3_priority(audio_anc_chn_e anc_chn, audio_anc_adder3_out_pri_e mode_sel)
{
    reg_audio_anc_config(anc_chn) = (reg_audio_anc_config(anc_chn) & (~FLD_ANC_SPK_SEL)) | MASK_VAL(FLD_ANC_SPK_SEL, mode_sel);
}

/**
 * @brief      This function serves to select anc fb mode input priority.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  mode_sel - anc hb mode input priority.
 * @note
 *        - The hb input is the sum of err0 mic and resample, but the two are not consistent in terms of time, this register is used to select which timing is first.
 */
static inline void audio_anc_set_hb_input_priority(audio_anc_chn_e anc_chn, audio_anc_hb_input_pri_e mode_sel)
{
    reg_audio_anc_config(anc_chn) = (reg_audio_anc_config(anc_chn) & (~FLD_FB_MODE_INPUT_SEL)) | MASK_VAL(FLD_FB_MODE_INPUT_SEL, mode_sel);
}

/**
 * @brief      This function serves to set dac control resample fs.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  in_fs   - resample input fs.
 * @param[in]  out_fs  - resample output fs.
 * @note
 *             - when resample fs rely on dac, this function must be called
 */
void audio_anc_set_dac_cnt_mode(audio_anc_chn_e anc_chn, audio_anc_resample_in_fs_e in_fs, audio_anc_resample_out_fs_e out_fs);

/**
 * @brief      This function serves to set the resample frequency of anc.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  fs_decision - who decides the resample frequency of anc.
 * @param[in]  in_fs       - resample input fs.
 * @param[in]  out_fs      - resample output fs.
 */
void audio_anc_set_resample_in_out_fs(audio_anc_chn_e anc_chn, audio_anc_resample_fs_decision_e fs_decision, audio_anc_resample_in_fs_e in_fs,
                                      audio_anc_resample_out_fs_e out_fs);

/**
 * @brief      This function serves to set ref mic dc value.
 * @param[in]  anc_chn        - anc channel.
 * @param[in]  ref_chn        - ref channel.
 * @param[in]  dc             - dc value.
 * @return     none
 */
static inline void audio_anc_set_ref_dc(audio_anc_chn_e anc_chn, audio_anc_ref_chn_e ref_chn, unsigned int dc)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_ref_dc(anc_chn, ref_chn) = dc & FLD_ANC_REF_DC;
}

/**
 * @brief      This function serves to latch ref mic gain.
 * @param[in]  anc_chn        - anc channel.
 * @param[in]  ref_chn        - ref channel.
 * @return     none
 */
static inline void audio_anc_latch_ref_mic_gain(audio_anc_chn_e anc_chn, audio_anc_ref_chn_e ref_chn)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    BM_SET(reg_audio_anc_gain_shift_latch(anc_chn), BIT(ref_chn));
}

/**
 * @brief      This function serves to set anc ref mic gain ref_mic_gain = ref_gain >> ref_gain_shift.
 * @param[in]  anc_chn        - anc channel.
 * @param[in]  ref_chn        - ref channel.
 * @param[in]  ref_gain       - ref_gain value bit[0-27] valid.
 * @param[in]  ref_gain_shift - ref_gain shift bit[0-5] valid.
 * @return     none
 */
static inline void audio_anc_set_ref_mic_gain(audio_anc_chn_e anc_chn, audio_anc_ref_chn_e ref_chn, unsigned int ref_gain, unsigned char ref_gain_shift)
{
    if (ref_chn == 0)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_ref0_gain(anc_chn) = ref_gain & FLD_ANC_REF0_GAIN;
    }
    else if (ref_chn == 1)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_ref1_gain(anc_chn) = ref_gain & FLD_ANC_REF1_GAIN;
    }
    else
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_ref2_gain(anc_chn) = ref_gain & FLD_ANC_REF2_GAIN;
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_ref_gain_shift(anc_chn, ref_chn) = ref_gain_shift & FLD_ANC_REF_GAIN_SHIFT;
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    audio_anc_latch_ref_mic_gain(anc_chn, ref_chn);
}

/**
 * @brief      This function serves to latch wz gain.
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  wz_chn        - wz channel.
 * @return     none
 */
static inline void audio_anc_latch_wz_gain(audio_anc_chn_e anc_chn, audio_anc_wz_chn_e wz_chn)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    BM_SET(reg_audio_anc_gain_shift_latch(anc_chn), BIT(wz_chn + 4));
}

/**
 * @brief      This function serves to set anc wz fir gain wz_fir_gain = wz_gain >> wz_gain_shift.
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  wz_chn        - wz channel.
 * @param[in]  wz_gain       - wz_gain value bit[0-27] valid.
 * @param[in]  wz_gain_shift - wz_gain_shift bit[0-5] valid.
 * @return     none
 */
static inline void audio_anc_set_wz_gain(audio_anc_chn_e anc_chn, audio_anc_wz_chn_e wz_chn, unsigned int wz_gain, unsigned char wz_gain_shift)
{
    if (wz_chn == 0)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wz0_gain(anc_chn) = wz_gain & FLD_ANC_WZ0_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_gain0_mul_shift(anc_chn) = wz_gain_shift & FLD_ANC_GAIN0_MUL_SHIFT;
    }
    else if  (wz_chn == 1)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wz1_gain(anc_chn) = wz_gain & FLD_ANC_WZ1_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_gain1_mul_shift(anc_chn) = wz_gain_shift & FLD_ANC_GAIN1_MUL_SHIFT;
    }
    else
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_wz2_gain(anc_chn) = wz_gain & FLD_ANC_WZ2_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_gain2_mul_shift(anc_chn) = wz_gain_shift & FLD_ANC_GAIN2_MUL_SHIFT;
    }
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    audio_anc_latch_wz_gain(anc_chn, wz_chn);
}

/**
 * @brief      This function serves to latch cz gain.
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  cz_chn        - cz channel.
 * @return     none
 */
static inline void audio_anc_latch_cz_gain(audio_anc_chn_e anc_chn, audio_anc_cz_chn_e cz_chn)
{
    if (cz_chn == ANC0_CZ0)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        BM_SET(reg_audio_anc_cz_rz_gain_shift_latch(anc_chn), BIT(0));
    }
    else if (cz_chn == ANC0_CZ1)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        BM_SET(reg_audio_anc_cz_rz_gain_shift_latch(anc_chn), BIT(4));
    }
    else
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        BM_SET(reg_audio_anc_cz_rz_gain_shift_latch(anc_chn), BIT(1));
    }
}

/**
 * @brief      This function serves to set anc cz fir gain cz_fir_gain = cz_gain >> cz_gain_shift.
 *
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  cz_chn        - cz channel.
 * @param[in]  cz_gain       - cz_gain value bit[0-27] valid.
 * @param[in]  cz_gain_shift - cz_gain_shift bit[0-5] valid.
 * @return     none
 */
static inline void audio_anc_set_cz_gain(audio_anc_chn_e anc_chn, audio_anc_cz_chn_e cz_chn, unsigned int cz_gain, unsigned char cz_gain_shift)
{
    if (cz_chn == ANC0_CZ0)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz0_gain(anc_chn) = cz_gain & FLD_ANC_CZ0_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz0_gain_shift(anc_chn) = cz_gain_shift & FLD_ANC_CZ0_GAIN_SHIFT;
    }
    else if (cz_chn == ANC0_CZ1)
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz1_gain(anc_chn) = cz_gain & FLD_ANC_CZ1_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz1_gain_shift(anc_chn) = cz_gain_shift & FLD_ANC_CZ1_GAIN_SHIFT;
    }
    else
    {
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_gain(anc_chn) = cz_gain & FLD_ANC_CZ3_GAIN;
        while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
        reg_audio_anc_cz3_gain_shift(anc_chn) = cz_gain_shift & FLD_ANC_CZ3_GAIN_SHIFT;
    }

    audio_anc_latch_cz_gain(anc_chn, cz_chn);
}

/**
 * @brief      This function servers to update anc wz or cz biquad iir filter coefficients.
 * 
 * @param[in]  anc_chn - anc channel.
 * @param[in]  wcz_chn - wcz_chn channel.
 * @param[in]  data    - wcz biquad iir filter data.
 * @return     none
 */
void audio_anc_update_wcz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed int data[12][5]);

/**
 * @brief      This function servers to set anc wz or cz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  wcz_chn  - wcz_chn channel.
 * @param[in]  data     - wcz fir filter data address.
 * @note
 *             - bypass coefficients: wz[0] = 0x4000, the rest of the parameters are all set to 0
 * @return     none
 */
void audio_anc_update_wcz_fir_coef(audio_anc_chn_e anc_chn, audio_anc_wcz_chn_e wcz_chn, signed short *data);

/**
 * @brief      This function servers to update anc cz3 biquad iir filter coefficients.
 * 
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - cz3 biquad iir filter data.
 * @return     none
 */
void audio_anc_update_cz3_iir_coef(audio_anc_chn_e anc_chn, signed int data[12][5]);

/**
 * @brief      This function servers to update anc cz3 fir filter coefficients.
 * 
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  data     - cz fir filter data.
 * @return     none
 */
void audio_anc_update_cz3_fir_coef(audio_anc_chn_e anc_chn, signed short *data);

/**
 * @brief      This function serves to latch rz gain.
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  rz_chn        - rz channel.
 * @return     none
 */
static inline void audio_anc_latch_rz_gain(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    BM_SET(reg_audio_anc_cz_rz_gain_shift_latch(anc_chn), BIT(rz_chn + 2));
}

/**
 * @brief      This function serves to set anc rz fir gain rz_fir_gain = rz_gain >> rz_gain_shift.
 *
 * @param[in]  anc_chn       - anc channel.
 * @param[in]  rz_chn        - rz channel.
 * @param[in]  rz_gain       - rz_gain value bit[0-27] valid.
 * @param[in]  rz_gain_shift - wz_gain_shift bit[0-5] valid.
 * @return     none
 */
static inline void audio_anc_set_rz_gain(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn, unsigned int rz_gain, unsigned char rz_gain_shift)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_rz_gain(anc_chn, rz_chn) = rz_gain & FLD_ANC_RZ_GAIN;
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_rz_gain_shift(anc_chn, rz_chn) = rz_gain_shift & FLD_ANC_RZ_GAIN_SHIFT;
    audio_anc_latch_rz_gain(anc_chn, rz_chn);
}

/**
 * @brief      This function servers to update anc rz biquad iir filter coefficients.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  rz_chn  - rz channel.
 * @param[in]  data    - rz fir filter data.
 * @return     none
 */
void audio_anc_update_rz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn, signed int data[12][5]);

/**
 * @brief      This function servers to update anc rz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  rz_chn   - rz channel.
 * @param[in]  data     - rz fir filter data.
 * @return     none
 */
void audio_anc_update_rz_fir_coef(audio_anc_chn_e anc_chn, audio_anc_rz_chn_e rz_chn, signed short *data);

/**
 * @brief      This function servers to update anc bz fir filter coefficients.
 *
 * @param[in]  anc_chn  - anc channel.
 * @param[in]  bz_chn   - bz channel.
 * @param[in]  data     - bz fir filter data.
 * @return     none
 */
void audio_anc_update_bz_iir_coef(audio_anc_chn_e anc_chn, audio_anc_bz_chn_e bz_chn, signed int data[6][5]);

/**
 * @brief      This function servers to update anc hb1 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb1 coefficient length is 21 word, bit[0-25] valid.
 */
void audio_anc_update_hb1_coef(audio_anc_chn_e anc_chn, signed int *data);

/**
 * @brief      This function servers to update anc hb2 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb2 coefficient length is 8 word, bit[0-25] valid.
 */
void audio_anc_update_hb2_coef(audio_anc_chn_e anc_chn, signed int *data);

/**
 * @brief      This function servers to update anc hb3 coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc hb3 coefficient length is 8 word, bit[0-25] valid.
 */
void audio_anc_update_hb3_coef(audio_anc_chn_e anc_chn, signed int *data);

/**
 * @brief      This function servers to update anc droop coefficients.
 * @param[in]  anc_chn - anc channel.
 * @param[in]  data    - coefficient data address.
 * @note
 *             - anc droop coefficient length is 6 word, bit[0-13] valid.
 */
void audio_anc_update_droop_coef(audio_anc_chn_e anc_chn, signed short *data);

/**
 * @brief      This function serves to set anc wz sum right shift.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  val     - 0:right shift 0; 1: right shift 1; 2 right shift 2; 3 right shift 3
 * @return     none
 */
static inline void audio_anc_set_wz_sum_right_shift(audio_anc_chn_e anc_chn, unsigned char val)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_limiter_shift(anc_chn) = (reg_audio_anc_limiter_shift(anc_chn) & ~FLD_ANC_WZ_SUM_LIMITER_SHIFT) | MASK_VAL(FLD_ANC_WZ_SUM_LIMITER_SHIFT, val);
}

/**
 * @brief      This function serves to set anc cz sum right shift.
 *
 * @param[in]  anc_chn - anc channel.
 * @param[in]  val     - 0:right shift 0; 1: right shift 1; 2 right shift 2; 3 right shift 3
 * @return     none
 */
static inline void audio_anc_set_cz_sum_right_shift(audio_anc_chn_e anc_chn, unsigned char val)
{
    while(reg_audio_anc_config1(anc_chn) & FLD_ANC_FSM_STATUS){};
    reg_audio_anc_limiter_shift(anc_chn) = (reg_audio_anc_limiter_shift(anc_chn) & ~FLD_ANC_CZ_SUM_LIMITER_SHIFT) | MASK_VAL(FLD_ANC_CZ_SUM_LIMITER_SHIFT, val);
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio asrc interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio asrc interface.
 * @{
 */

/**
 * @brief      This function serves to update asrc half_band1 coefficients.
 * 
 * @param[in]  asrc_chn - asrc channel.
 * @param[in]  hb1_coef - asrc half_band1 coefficients data address.
 * @return     none
 * @note
 *             - asrc half_band1 coefficient length is 32 word, bit[0-25] valid.
 */
void audio_asrc_update_hb1_coef(audio_hac_asrc_chn_e asrc_chn, signed int *hb1_coef);

/**
 * @brief      This function serves to update asrc half_band2 coefficients.
 * 
 * @param[in]  asrc_chn - asrc channel.
 * @param[in]  hb2_coef - asrc half_band2 coefficients data address. 
 * @return     none
 * @note
 *             - asrc half_band2 coefficient length is 7 word, bit[0-25] valid.
 */
void audio_asrc_update_hb2_coef(audio_hac_asrc_chn_e asrc_chn, signed int *hb2_coef);

/**
 * @brief      This function serves to set asrc droop step.
 *
 * @param[in]  asrc_chn - asrc channel select.
 * @param[in]  step     - asrc droop step audio_asrc_droop_step_e.
 * @return     none
 */
static inline void audio_asrc_set_droop_step(audio_hac_asrc_chn_e asrc_chn, audio_asrc_droop_step_e step)
{
    reg_audio_asrc_drop_len_mod(asrc_chn) = (reg_audio_asrc_drop_len_mod(asrc_chn) & (~FLD_ASRC_DROP_LEN_MOD)) | step;
}

/**
 * @brief      This function serves to update asrc droop coefficients.
 *
 * @param[in]  asrc_chn  - asrc channel select.
 * @param[in]  d_coef    - asrc droop coefficients data address.
 * @param[in]  data_len  - asrc droop coefficients data length.
 * @return     none
 * @note
 *             - droop coef max length is 9.
 */
void audio_asrc_update_droop_coef(audio_hac_asrc_chn_e asrc_chn, signed short *d_coef, unsigned char data_len);

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio clock interface                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio clock interface.
 * @{
 */

/**
 * @brief       This function used to close and reopen LDO:AVDD2 or DCDC:BK1 and configure FLD_CODEC_BGR_ENP and FLD_CODEC_PGOOD_CDC.
 * @param[in]   none.
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void audio_codec_pre_init(void);

/**
 * @brief      This function serves to initialize audio.
 * @param[in]  audio_pll - audio pll clock select.
 * @return     none
 * @note       - When using the audio module, this interface must be configured first, otherwise the following interfaces will not take effect.
 *             - When the sampling rate is 44.1KHz, audio_pll needs to be set to PLL1_AUDIO_CLK_158P0544M.
 */
_attribute_ram_code_sec_noinline_ void audio_init(pll_audio_clk_e clk);

/**
 * @brief      This function serves set audio clk.The audio clk is divided by pll1_clk. When the internal codec operates at a sampling rate of 44.1KHz, \n
 *             audio_clk needs to be set to 33.8688MHz, and the remaining sampling rate audio_clk needs to be set to 36.864MHz.
 * @param[in]  clk_div - pll1_clk div.
 * @return     none
 */
static inline void audio_clk_set(unsigned int clk_div)
{
    reg_audio_clk_aclk_set = (reg_audio_clk_aclk_set & (~FLD_CLK_ACLK_SET)) | (clk_div & FLD_CLK_ACLK_SET);
    BM_SET(reg_audio_clk_en_0, FLD_CLK_ACLK_EN);
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio codec interface                                               *
 *********************************************************************************************************************/
/**
 * @brief     Weak delay interface for audio module in millisecond
 * @param[in] millisec - delay duration in millisecond
 * @return    none
 */
void audio_delay_ms(unsigned int millisec);

 /*!
 * @name Audio codec0 interface.
 * @{
 */

/**
 * @brief      This function serves to enable codec adc analog part.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_ana_en(audio_codec_input_select_e input);

/**
 * @brief      This function serves to disable codec adc analog part.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_ana_dis(audio_codec_input_select_e input);

/**
 * @brief      This function serves to enable codec adc reset.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_rst_en(audio_codec_input_select_e input);

/**
 * @brief      This function serves to disable codec adc reset.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_rst_dis(audio_codec_input_select_e input);

/**
 * @brief      This function serves to enable codec adc.
 * @param[in]  input - input channel.
 * @return     none
 */
void audio_codec_adc_en(audio_codec_input_select_e input);

/**
 * @brief      This function serves to disable codec adc.
 * @param[in]  input - adc channel.
 * @return     none
 */
void audio_codec_adc_dis(audio_codec_input_select_e input);

/**
 * @brief      This function serves to enable codec dac reset.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_rst_en(audio_codec_output_select_e output);

/**
 * @brief      This function serves to disable codec dac reset.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_rst_dis(audio_codec_output_select_e output);

/**
 * @brief      This function serves to enable codec dac.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_en(audio_codec_output_select_e output);

/**
 * @brief      This function serves to disable codec dac.
 * @param[in]  output - dac channel.
 * @return     none
 */
void audio_codec_dac_dis(audio_codec_output_select_e output);

/**
 * @brief      This function serves to enable codec adc clock.
 * @param[in]  input  - input channel.
 * @return     none
 */
void audio_codec_adc_clk_en(audio_codec_input_select_e input);

/**
 * @brief      This function serves to disable codec adc clock.
 * @param[in]  input  - input channel.
 * @return     none
 */
void audio_codec_adc_clk_dis(audio_codec_input_select_e input);

/**
 * @brief      This function serves to enable codec dac clock.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_dac_clk_en(audio_codec_output_select_e output);

/**
 * @brief      This function serves to disable codec dac clock.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_dac_clk_dis(audio_codec_output_select_e output);

/**
 * @brief      This function serves to enable codec adc and dac clock.
 * @param[in]  input  - input channel.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_adc_dac_clk_en(audio_codec_input_select_e input, audio_codec_output_select_e output);

/**
 * @brief      This function serves to disable codec adc and dac clock.
 * @param[in]  input  - input channel.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_adc_dac_clk_dis(audio_codec_input_select_e input, audio_codec_output_select_e output);

/**
 * @brief      This function serves to power down codec adc.
 * @param[in]  input - adc channel.
 * @return     none
 */
void audio_codec_adc_power_down(audio_codec_input_select_e input);

/**
 * @brief      This function serves to power down codec dac.
 * @param[in]  output - output channel.
 * @return     none
 */
void audio_codec_output_power_down(audio_codec_output_select_e output);

/**
 * @brief      This function serves to enable/disable codec micbias output.
 * @param[in]  enable - 1: enable micbias, 0: disable micbias.
 * @return     none
 * @note
 *             - bias only for amic.
 */
void audio_codec_set_micbias(unsigned char enable);

/**
 * @brief      This function serves to set codec output mute.
 * @param[in]  output - output channel.
 * @param[in]  cmd    - mute type.
 * @return     none
 */
void audio_codec_set_output_mute(audio_codec_output_select_e output, audio_dac_mute_cmd_t cmd);

/**
 * @brief      This function serves to set codec input sample rate.
 * @param[in]  input - input channel.
 * @param[in]  fs    - input sample rate.
 * @return     none
 * @note
 */
void audio_codec_set_input_fs(audio_codec_input_select_e input, audio_sample_rate_e fs);

/**
 * @brief      This function serves to set codec output sample rate.
 * @param[in]  fs - output sample rate.
 * @return     none
 * @note
 */
void audio_codec_set_output_fs(audio_codec_output_select_e output, audio_sample_rate_e fs);

/**
 * @brief      This function serves to set codec input data bit width.
 * @param[in]  input - input channel.
 * @param[in]  wl    - bit width.
 * @return     none
 * @note
 */
void audio_codec_set_input_wl(audio_codec_input_select_e input, audio_codec_data_select_e wl);

/**
 * @brief      This function serves to set codec output data bit width.
 * @param[in]  output - output channel.
 * @param[in]  wl     - bit width.
 * @return     none
 */
void audio_codec_set_output_wl(audio_codec_output_select_e output, audio_codec_data_select_e wl);

/**
 * @brief      This function serves to set codec input analog gain.
 * @param[in]  input - input channel.
 * @param[in]  gain  - input analog gain.
 * @return     none
 * @note
 *             - input analog gain only for line_in or amic.
 */
void audio_codec_set_input_again(audio_codec_input_select_e input, audio_codec_input_again_e gain);

/**
 * @brief      This function serves to set codec input digital gain.
 * @param[in]  input - input channel.
 * @param[in]  gain  - input digital gain.
 * @return     none
 */
void audio_codec_set_input_dgain(audio_codec_input_select_e input, audio_codec_input_dgain_e gain);


/**
 * @brief      This function serves to set codec output analog gain.
 * @param[in]  output - output channel.
 * @param[in]  gain   - output analog gain.
 * @return     none
 */
void audio_codec_set_output_again(audio_codec_output_select_e output, audio_codec_output_again_e gain);

/**
 * @brief      This function serves to set codec output digital gain.
 * @param[in]  output - output channel.
 * @param[in]  gain   - output digital gain.
 * @return     none
 */
void audio_codec_set_output_dgain(audio_codec_output_select_e output, audio_codec_output_dgain_e gain);

/**
 * @brief      This function serves to enable/disable codec input HPF(High Pass Filter).
 * @param[in]  input  - input channel.
 * @param[in]  enable - 1: adc High Pass Filter active, 0:adc High Pass Filter inactive.
 * @return     none
 * @note
 */
void audio_codec_input_hpf_en(audio_codec_input_select_e input, unsigned char enable);

/**
 * @brief      This function serves to init codec input.
 * @param[in]  input_config - codec input config.
 * @return     none
 */
void audio_codec_input_init(audio_codec_input_config_t *input_config);

/**
 * @brief      This function serves to init codec output config.
 * @param[in]  output_config - codec output config.
 * @return     none
 */
void audio_codec_output_init(audio_codec_output_config_t *output_config);

/**
 * @brief      This function serves to power down codec, include codec adc and dac, close codec ldo_ana and ldo_cdc.
 * @return     none
 */
void audio_codec_power_down(void);


/**********************************************************************************************************************
 *                                                Audio dmic interface                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio dmic interface
 * @{
 */

/**
 * @brief      This function serves to enable/disable dmic clock.
 * @param[in]  dmic_ch  - dmic channel.
 * @param[in]  enable - 1:enable dmic clock, 0:disable dmic clock.
 */
void audio_dmic_clk_en(audio_dmic_channel_e dmic_ch, unsigned char enable);

/**
 * @brief      This function serves to init dmic input.
 * @param[in]  input_config - dmic input config.
 * @return     none
 */
void audio_dmic_input_init(audio_dmic_input_config_t *input_config);

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio dma/fifo interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio ama/fifo interface.
 * @{
 */

/**
 * @brief      This function serves to tx fifo dma trigger number.
 * @param[in]  tx_fifo_chn - the fifo channel.
 * @param[in]  number      - the number of dma trigger, the unit is word.
 * @return     none
 */
static inline void audio_set_fifo_tx_trig_num(audio_fifo_chn_e tx_fifo_chn, unsigned char number)
{
    reg_audio_dma_tx_fifo_trig_num(tx_fifo_chn) = (reg_audio_dma_tx_fifo_trig_num(tx_fifo_chn) & (~FLD_TX_FIFO_TRIG_NUM)) |
                                                  (number & FLD_TX_FIFO_TRIG_NUM);
}

/**
 * @brief      This function serves to rx fifo dma trigger number.
 * @param[in]  rx_fifo_chn - the fifo channel.
 * @param[in]  number      - the number of dma trigger, the unit is word.
 * @return     none
 */
static inline void audio_set_fifo_rx_trig_num(audio_fifo_chn_e rx_fifo_chn, unsigned char number)
{
    reg_audio_dma_rx_fifo_trig_num(rx_fifo_chn) = (reg_audio_dma_rx_fifo_trig_num(rx_fifo_chn) & (~FLD_RX_FIFO_TRIG_NUM)) |
                                                  (number & FLD_RX_FIFO_TRIG_NUM);
}

/**
 * @brief      This function serves to clear fifo data.
 * @param[in]  fifo_chn   - fifo channel
 * @param[in]  clear_flag
 *                        - 1: audio fifo cnt clear
 *                        - 0: audio fifo cnt clear release.
 * @return     none.
 */
static inline void audio_clear_fifo(audio_fifo_type_e fifo_chn, char clear_flag)
{
    reg_audio_dma_fifo_clr = reg_audio_dma_fifo_clr | MASK_VAL(fifo_chn, clear_flag);
}

/**
 * @brief      This function serves to enable read fifo ptr.
 * @param[in]  fifo_chn - fifo channel
 * @return     none
 */
static inline void audio_fifo_ptr_en(audio_fifo_type_e fifo_chn)
{
    BM_SET(reg_audio_dma_ptr_en, fifo_chn);
}

/**
 * @brief      This function serves to disable read fifo ptr.
 * @param[in]  fifo_chn - fifo channel
 * @return     none
 */
static inline void audio_fifo_ptr_dis(audio_fifo_type_e fifo_chn)
{
    BM_CLR(reg_audio_dma_ptr_en, fifo_chn);
}

/**
 * @brief      This function servers to get audio fifo irq status.
 * @param[in]  fifo_type - the audio fifo type.
 * @return     irq status of audio fifo.
 */
static inline unsigned char audio_get_fifo_irq_status(audio_fifo_type_e fifo_type)
{
    return reg_audio_dma_irq_st & fifo_type;
}

/**
 * @brief      This function servers to clear audio fifo irq status.
 * @param[in]  fifo_type - the audio fifo type.
 * @return     none
 */
static inline void audio_clr_fifo_irq_status(audio_fifo_type_e fifo_type)
{
    reg_audio_dma_irq_st = fifo_type;
}

/**
 * @brief      This function serves to enable audio fifo irq.
 * @param[in]  fifo_chn - audio fifo channel.
 * @return     none
 */
static inline void audio_fifo_irq_en(audio_fifo_type_e fifo_chn)
{
    BM_SET(reg_audio_dma_irq_en, fifo_chn);
}

/**
 * @brief      This function serves to disable audio fifo irq.
 * @param[in]  fifo_chn - audio fifo channel.
 * @return     none
 */
static inline void audio_fifo_irq_dis(audio_fifo_type_e fifo_chn)
{
    BM_CLR(reg_audio_dma_irq_en, fifo_chn);
}

/**
 * @brief      This function serves to get tx read pointer.
 * @param[in]  tx_fifo_chn - select fifo channel
 * @return     the result of tx read pointer.
 */
static inline unsigned short audio_get_tx_rptr(audio_fifo_chn_e tx_fifo_chn)
{
    return reg_audio_dma_tx_rptr(tx_fifo_chn);
}

/**
 * @brief      This function serves to set tx read pointer.
 * @param[in]  tx_fifo_chn - select fifo channel
 * @return     the result of tx read pointer.
 */
static inline void audio_set_tx_rptr(audio_fifo_chn_e tx_fifo_chn, unsigned short value)
{
    reg_audio_dma_tx_rptr(tx_fifo_chn) = value;
}

/**
 * @brief      This function serves to get rx write pointer.
 * @param[in]  rx_fifo_chn - select fifo channel
 * @return     the result of rx write pointer.
 */
static inline unsigned short audio_get_rx_wptr(audio_fifo_chn_e rx_fifo_chn)
{
    return reg_audio_dma_rx_wptr(rx_fifo_chn);
}

/**
 * @brief      This function serves to set rx write pointer.
 * @param[in]  rx_fifo_chn - select fifo channel
 * @return     the result of rx write pointer.
 */
static inline void audio_set_rx_wptr(audio_fifo_chn_e rx_fifo_chn, unsigned short value)
{
    reg_audio_dma_rx_wptr(rx_fifo_chn) = value;
}

/**
 * @brief      This function serves to set tx buff length.
 * @param[in]  tx_fifo_chn - the fifo channel.
 * @param[in]  len         - the length of tx buff, the unit is byte.
 * @return     none
 */
static inline void audio_set_tx_buff_len(audio_fifo_chn_e tx_fifo_chn, unsigned short len)
{
    reg_audio_dma_tx_max(tx_fifo_chn) = (((len) >> 2) - 1);
}

/**
 * @brief      This function serves to set rx buff length.
 * @param[in]  rx_fifo_chn - the fifo channel.
 * @param[in]  len         - the length of rx buff, the unit is byte.
 * @return     none
 */
static inline void audio_set_rx_buff_len(audio_fifo_chn_e rx_fifo_chn, unsigned short len)
{
    reg_audio_dma_rx_max(rx_fifo_chn) = ((len) >> 2) - 1;
}

/**
 * @brief      This function serves to set tx buff threshold.
 * @param[in]  tx_fifo_chn - the fifo channel.
 * @param[in]  threshold   - the threshold of tx buff, the unit is byte.
 * @return     none
 */
static inline void audio_set_tx_buff_thres(audio_fifo_chn_e tx_fifo_chn, unsigned short threshold)
{
    reg_audio_dma_tx_th(tx_fifo_chn) = ((threshold) >> 2) - 1;
}

/**
 * @brief      This function serves to set rx buff threshold.
 * @param[in]  rx_fifo_chn - the fifo channel.
 * @param[in]  threshold   - the threshold of rx buff, the unit is byte.
 * @return     none
 */
static inline void audio_set_rx_buff_thres(audio_fifo_chn_e rx_fifo_chn, unsigned short threshold)
{
    reg_audio_dma_rx_th(rx_fifo_chn) = ((threshold) >> 2) - 1;
}

/**
 *  @brief      This function serves to get dma tx buff pointer.
 *  @param[in]  chn - dma channel
 *  @return     the result of tx read pointer.
 */
static inline unsigned int audio_get_tx_dma_rptr(dma_chn_e chn)
{
    return reg_dma_src_addr(chn);
}

/**
 *  @brief      This function serves to get dma rx buff pointer.
 *  @param[in]  chn - dma channel
 *  @return     the result of rx write pointer.
 */
static inline unsigned int audio_get_rx_dma_wptr(dma_chn_e chn)
{
    return reg_dma_dst_addr(chn);
}

/**
 * @brief      This function serves to enable rx_dma channel.
 * @param[in]  chn   - dma channel.
 * @return     none
 */
static inline void audio_rx_dma_en(dma_chn_e chn)
{
    dma_chn_en(chn);
}

/**
  * @brief      This function serves to disable rx_dma channel.
  * @param[in]  chn   - dma channel.
  * @return     none
  */
static inline void audio_rx_dma_dis(dma_chn_e chn)
{
    dma_chn_dis(chn);
}

/**
 * @brief      This function serves to enable tx_dma channel.
 * @param[in]  chn   - dma channel.
 * @return     none
 */
static inline void audio_tx_dma_en(dma_chn_e chn)
{
    dma_chn_en(chn);
}

/**
 * @brief      This function serves to disable dis_dma channel.
 * @param[in]  chn   - dma channel.
 * @return     none
 */
static inline void audio_tx_dma_dis(dma_chn_e chn)
{
    dma_chn_dis(chn);
}

/**
 * @brief      This function serves to config rx_dma channel.
 * @param[in]  chn          - dma channel.
 * @param[in]  dst_addr     - Pointer to data buffer, it must be 4-bytes aligned address.
 *                           and the actual buffer size defined by the user needs to be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  data_len     - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @param[in]  head_of_list - the head address of dma llp.
 * @return     none
 */
void audio_rx_dma_config(dma_chn_e chn, unsigned short *dst_addr, unsigned int data_len, dma_chain_config_t *head_of_list);

/**
 * @brief      This function serves to set rx dma chain transfer.
 * @param[in]  config_addr - the head of list of llp_pointer.
 * @param[in]  llpointer   - the next element of llp_pointer.
 * @param[in]  dst_addr    - Pointer to data buffer, it must be 4-bytes aligned address and the actual buffer size defined by the user needs to \n
 *                           be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  data_len    - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @return     none
 */
void audio_rx_dma_add_list_element(dma_chain_config_t *config_addr, dma_chain_config_t *llpointer, unsigned short *dst_addr, unsigned int data_len);

/**
 * @brief      This function serves to set audio rx dma chain transfer.
 * @param[in]  rx_fifo_chn - rx fifo select.
 * @param[in]  chn         - dma channel.
 * @param[in]  in_buff     - Pointer to data buffer, it must be 4-bytes aligned address and the actual buffer size defined by the user needs to \n
 *                           be not smaller than the data_len, otherwise there may be an out-of-bounds problem.
 * @param[in]  buff_size   - Length of DMA in bytes, it must be set to a multiple of 4. The maximum value that can be set is 0x10000.
 * @return     none
 */
void audio_rx_dma_chain_init(audio_fifo_chn_e rx_fifo_chn, dma_chn_e chn, unsigned short *in_buff, unsigned int buff_size);

/**
 * @brief      This function serves to config  tx_dma channel.
 * @param[in]  chn          - dma channel.
 * @param[in]  src_addr     - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  data_len     - Length of DMA in bytes, range from 1 to 0x10000.
 * @param[in]  head_of_list - the head address of dma llp.
 * @return     none
 */
void audio_tx_dma_config(dma_chn_e chn, unsigned short *src_addr, unsigned int data_len, dma_chain_config_t *head_of_list);

/**
 * @brief      This function serves to set tx dma chain transfer.
 * @param[in]  config_addr - the head of list of llp_pointer.
 * @param[in]  llpointer   - the next element of llp_pointer.
 * @param[in]  src_addr    - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  data_len    - Length of DMA in bytes, range from 1 to 0x10000.
 * @return     none
 */
void audio_tx_dma_add_list_element(dma_chain_config_t *config_addr, dma_chain_config_t *llpointer, unsigned short *src_addr, unsigned int data_len);

/**
 * @brief      This function serves to initialize audio tx dma chain transfer.
 * @param[in]  tx_fifo_chn - tx fifo select.
 * @param[in]  chn         - dma channel.
 * @param[in]  out_buff    - Pointer to data buffer, it must be 4-bytes aligned address.
 * @param[in]  buff_size   - Length of DMA in bytes, range from 1 to 0x10000.
 * @return     none
 */
void audio_tx_dma_chain_init(audio_fifo_chn_e tx_fifo_chn, dma_chn_e chn, unsigned short *out_buff, unsigned int buff_size);

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio hac interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio hac interface.
 * @{
 */
/**
 * @brief      This function servers to enable/disable hac clock.
 *
 * @param[in]  hac_chn    - hac channel.
 * @return     none
 */
static inline void audio_hac_clk_en(audio_hac_chn_e hac_chn)
{
    reg_audio_clk_en_1 |= BIT(hac_chn);
}

/**
 * @brief      This function servers to enable/disable hac reset.
 *
 * @param[in]  hac_chn    - hac channel.
 * @param[in]  reset_flag
 *                        - 1: hac en
 *                        - 0: hac dis
 * @return     none
 */
static inline void audio_hac_asrc_ch_en(audio_hac_chn_e hac_chn, char reset_flag)
{
    reg_audio_hac_eq_asrc_en = (reg_audio_hac_eq_asrc_en & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), reset_flag);
}


static inline void audio_hac_input_afifo_clr(audio_hac_chn_e hac_chn)
{
    reg_audio_hac_input_afifo_clr |= BIT(hac_chn);
}

/**
 * @brief      This function servers to select hac data src.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  src     - hac data source.
 * @return     none
 */
static inline void audio_hac_set_data_src(audio_hac_chn_e hac_chn, audio_hac_input_data_e src)
{
    reg_audio_hac_mux_sel = (reg_audio_hac_mux_sel & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), src);
}

/**
 * @brief      This function servers to select hac data dst.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  dst     - hac data dst.
 * @return     none
 */
static inline void audio_hac_set_data_dst(audio_hac_chn_e hac_chn, audio_hac_output_data_e dst)
{
    reg_audio_hac_hmst_sel = (reg_audio_hac_hmst_sel & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), dst);
}

/**
 * @brief      This function servers to set hac out data address when out type is HAC_OUTPUT_DATA_AHB_MST.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  address - out data address.
 * @return     none
 */
static inline void audio_hac_set_out_data_addr(audio_hac_chn_e hac_chn, unsigned int address)
{
     if(hac_chn<HAC_CH4_EQ2) {
        reg_audio_hac_eq_asrc_output_addr(hac_chn) = address;
    } else {
        reg_audio_hac_eq2_haddr = address;
    }
    reg_audio_hac_haddr_set      = (reg_audio_hac_haddr_set & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), 1);

}

static inline void audio_hac_set_in_data_addr(audio_hac_chn_e hac_chn, unsigned int address)
{
    reg_audio_hac_ahb_wr_addr(hac_chn) = address;
    reg_audio_hac_asrc_eq_ahb_wr_set      = (reg_audio_hac_asrc_eq_ahb_wr_set & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), 1);

}

/**
 * @brief      This function servers to set MCU write fifo rate, when the input source is from AHB_SLV.
 *
 * @param[in]  hac_chn  - hac channel.
 * @param[in]  rate_div - MCU write fifo rate, rate = audio_clk / rate_div. for example, audio_clk = 36.864MHz, HAC sample = 48KHz, rate_div = 36.864MHz / 48KHz = 768.
 * @return     none
 * @note
 *             - If the data coming from matrix itself has a fixed sample rate, then there is no need for the HAC to control the input sample rate, then you need to write 0 to the above registers.
 */
static inline void audio_hac_set_in_data_rate(audio_hac_chn_e hac_chn, unsigned short rate_div)
{
    if(hac_chn <= HAC_CH3_ASRC1) {
        reg_audio_hac_eq_asrc_rd_num(hac_chn) = rate_div;
    } else {
        reg_audio_hac_eq2_rd_num = rate_div;
    }
}

///**
// * @brief      This function servers to set hac tdm num.
// *
// * @param[in]  hac_chn  - hac channel (only hac2 and hac3 need to set this register).
// * @param[in]  num - tdm number.
// * @return     none
// * @note
// */
//static inline void audio_hac_set_tdm_num(audio_hac_chn_e hac_chn, unsigned char num)
//{
//    unsigned char mask    = FLD_HAC_TDM0_NUM << (4 * (hac_chn - 2));
//    reg_audio_hac_tdm_num = (reg_audio_hac_tdm_num & ~mask) | MASK_VAL(mask, num);
//}
//
///**
// * @brief      This function servers to set hac 8 channel fist.
// *
// * @param[in]  hac_chn_first  - hac channel.
// * @return     none
// * @note
// */
////static inline void audio_hac_asrc_8ch_first_en(audio_hac_chn_e hac_chn_first)
////{
////    if (hac_chn_first == HAC_CHN2) {
////        reg_audio_matrix_fifo_rx_hac23_sel = reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC3_SEL);
////    } else if (hac_chn_first == HAC_CHN3) {
////        reg_audio_matrix_fifo_rx_hac23_sel = reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC2_SEL);
////    }
////}
//
///**
// * @brief      This function servers to set hac 6 channel fist.
// *
// * @param[in]  hac_chn_first  - hac channel.
// * @return     none
// * @note
// */
////static inline void audio_hac_asrc_6ch_first_en(audio_hac_chn_e hac_chn_first)
////{
////    if (hac_chn_first == HAC_CHN2) {
////        reg_audio_hac_asrc_6ch_en          = FLD_HAC_ASRC_6CH_HAC2_FIRST_EN;
////        reg_audio_matrix_fifo_rx_hac23_sel = reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC3_SEL);
////    } else if (hac_chn_first == HAC_CHN3) {
////        reg_audio_hac_asrc_6ch_en          = FLD_HAC_ASRC_6CH_HAC3_FIRST_EN;
////        reg_audio_matrix_fifo_rx_hac23_sel = reg_audio_matrix_fifo_rx_hac23_sel & (~FLD_MATRIX_FIFO_RX_HAC2_SEL);
////    }
////}

/**
 * @brief      This function servers to set hac out data rate, when the output is matrix.
 *
 * @param[in]  hac_chn  - hac channel.
 * @param[in]  rate_div - hac out data rate, rate = audio_clk / rate_div. for example, audio_clk = 36.864MHz, HAC sample = 384KHz, rate_div = 36.864MHz / 384KHz = 96.
 * @return     none
 * @note
 *             - If the HAC data is output via AHB_MST, then there is no need to match this register, when txfifo will read away the output as soon as the AHB_MST is not empty.
 */
//static inline void audio_hac_set_out_data_rate(audio_hac_chn_e hac_chn, unsigned int rate_div)
//{
//    reg_audio_hac_txfifo_rd_num(hac_chn) = (rate_div - 1) & FLD_HAC_TXFIFO_RD_NUM;
//}

/**
 * @brief      This function servers to clear hac fifo cnt.
 *
 * @param[in]  hac_chn    - hac channel.
 * @param[in]  reset_flag
 *                        - 1: hac fifo cnt clear.
 *                        - 0: hac fifo cnt clear release.
 * @return     none
 */
static inline void audio_hac_clear_fifo_cnt(audio_hac_chn_e hac_chn, char reset_flag)
{
    reg_audio_hac_fifo_cnt_clr = (reg_audio_hac_fifo_cnt_clr & (~BIT(hac_chn))) | MASK_VAL(BIT(hac_chn), reset_flag);
}

/**
 * @brief      This function servers to enable eq config.
 *
 * @param[in]  hac_chn - hac channel.
 * @return     none
 */
static inline void audio_hac_eq_config_en(audio_hac_eq_chn_e eq_chn)
{
    BM_SET(reg_audio_hac_eq_config_en, BIT(eq_chn));
}

/**
 * @brief      This function servers to enable/disable asrc bypass.
 *
 * @param[in]  asrc_chn - asrc channel select.
 * @param[in]  enable   - 1: asrc by pass, 0: asrc no bypass.
 * @return     none
 */
static inline void audio_hac_bypass_eq_asrc(audio_hac_chn_e hac_chn, unsigned char enable)
{
    unsigned char bypass_chg_table[5] = {0x00,0x01,0x03,0x04,0x02};
    enable ? BM_SET(reg_audio_hac_bypass_eq_asrc, BIT(bypass_chg_table[hac_chn])) : BM_CLR(reg_audio_hac_bypass_eq_asrc, BIT(bypass_chg_table[hac_chn]));
}

///**
// * @brief      This function serves to select hac tdm tx fifo channal numbers.
// *
// * @param[in]  fifo ch - tdm used fifo.
// * @param[in]  chn   - tdm channal numbers
// * @return     none
// */
//static inline void audio_hac_set_tdm_tx_dma_ch(audio_fifo_chn_e fifo_ch, audio_hac_tdm_tx_dma_ch_e chn)
//{
//    reg_audio_hac_tdm_tx_dma_ch_num = ((reg_audio_hac_tdm_tx_dma_ch_num & (~(0x03 << ((fifo_ch) * 2)))) | ((chn) << ((fifo_ch) * 2)));
//}
//
/**
 * @brief      This function servers to update hac biquad filter coefficients.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  biquad  - biquad step audio_hac_biquad_e.
 * @param[in]  data    - biquad filter data address, [b0, b1, b2, a1, a2].
 * @return     none
 */
void audio_hac_update_biquad_coef(audio_hac_eq_chn_e eq_chn, audio_hac_biquad_e biquad, signed int *data);

void audio_hac_set_input_num(audio_hac_chn_e hac_chn,unsigned short num);
void audio_hac_set_asrc_tdm_num(audio_hac_asrc_chn_e asrc_ch,unsigned char num);
///**
// * @brief      This function serves to get hac tx fifo cnt.
// *
// * @param[in]  fifo_chn - hac channel.
// * @return     hac tx fifo cnt.
// */
//unsigned int audio_hac_get_txfifo_cnt(audio_fifo_chn_e hac_chn);

/**
 * @brief      This function servers to select hac's asrc input and output fs.
 *
 * @param[in]  hac_chn   - hac channel.
 * @param[in]  fs_in     - input fs.
 * @param[in]  fs_out    - output fs.
 * @param[in]  ppm       - ppm value.
 * @return     none
 * @note       support fs in and out:
 *              - IN_16K_OUT_16K
 *              - IN_32K_OUT_16K
 *              - IN_44P1K_OUT_16K
 *              - IN_48K_OUT_16K
 *              - IN_96K_OUT_16K
 *              - IN_16K_OUT_32K
 *              - IN_32K_OUT_32K
 *              - IN_44P1K_OUT_32K
 *              - IN_48K_OUT_32K
 *              - IN_96K_OUT_32K
 *              - IN_16K_OUT_44P1K
 *              - IN_32K_OUT_44P1K
 *              - IN_44P1K_OUT_44P1
 *              - IN_48K_OUT_44P1K
 *              - IN_96K_OUT_44P1K
 *              - IN_16K_OUT_48K
 *              - IN_32K_OUT_48K
 *              - IN_44P1K_OUT_48K
 *              - IN_48K_OUT_48K
 *              - IN_96K_OUT_48K
 *              - IN_16K_OUT_96K
 *              - IN_32K_OUT_96K
 *              - IN_44P1K_OUT_96K
 *              - IN_48K_OUT_96K
 *              - IN_96K_OUT_96K
 *              - IN_768K_OUT_96K
 *              - IN_192K_OUT_192K
 *              - IN_384K_OUT_384K
 *              - IN_768K_OUT_768K
 *
 */
void audio_hac_asrc_fs_in_out(audio_hac_asrc_chn_e asrc_ch, int fs_in, int fs_out, int ppm, int tdm_chn);

/**
 * @brief      This function servers to set frac adc data.
 *
 * @param[in]  hac_chn  - hac channel.
 * @param[in]  frac_adc - frac adc value.
 * @return     none
 */
static inline void audio_hac_set_frac_adv(audio_hac_asrc_chn_e asrc_chn, int frac_adc)
{
    reg_audio_hac_asrc_frac_adv(asrc_chn) = frac_adc&FLD_HAC_ASRC_FRAC_ADV;
}

/**
 * @brief      This function servers to set den rate data.
 *
 * @param[in]  hac_chn  - hac channel.
 * @param[in]  den_rate - den rate value.
 * @return     none
 */
static inline void audio_hac_set_den_rate(audio_hac_asrc_chn_e hac_chn, int den_rate)
{
    reg_audio_hac_asrc_den_rate(hac_chn) = den_rate & FLD_HAC_ASRC_DEN_RATE;
}

/**
 * @brief      This function servers to set int adv data.
 *
 * @param[in]  hac_chn  - hac channel.
 * @param[in]  int_adv  - int adv value.
 * @return     none
 */
static inline void audio_hac_set_int_adv(audio_hac_asrc_chn_e hac_chn, char int_adv)
{
    reg_audio_hac_asrc_int_adv(hac_chn) = int_adv & FLD_HAC_ASRC_INT_ADV;
}

/**
 * @brief      This function servers to set lag_int config done.
 *
 * @param[in]  hac_chn  - hac channel.
 * @return     none
 * @note
 *             - After configuring the correlation coefficients, set the bit of the corresponding channel to 1, so that the coefficients will be uniformly latched into lag_int.
 */
static inline void audio_hac_lag_int_config_done(audio_hac_asrc_chn_e hac_chn)
{
    BM_SET(reg_audio_hac_asrc_lag_update, BIT(hac_chn));
}

/**
 * @brief      This function servers to set hac interval.
 *
 * @param[in]  hac_chn - hac channel.
 * @param[in]  in_fs   - sample rate.
 * @param[in]  tdm_chn - tdm channel.
 * @return     none
 */
void audio_hac_set_interval(audio_hac_asrc_chn_e asrc_chn, int in_fs, int tdm_chn);

///**
// * @}
// */

/**********************************************************************************************************************
 *                                                Audio I2S interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio I2S interface.
 * @{
 */

/**
 * @brief      This function serves to set i2s clock.
 * @param[in]  i2s_select      - i2s channel select.
 * @param[in]  div_numerator   - the dividing factor of div_numerator bit[0-14] valid.
 * @param[in]  div_denominator - the dividing factor of div_denominator bit[0-15] valid.
 * @return     none
 */
static inline void audio_i2s_set_clk(i2s_select_e i2s_select, unsigned short div_numerator, unsigned short div_denominator)
{
    reg_audio_clk_i2s_step(i2s_select) = div_numerator & FLD_CLK_I2S_STEP;
    reg_audio_clk_i2s_mod(i2s_select)  = div_denominator;
}

/**
 * @brief      This function serves to set the bclk divider.
 * @param[in]  i2s_select - i2s channel select.
 * @param[in]  div        - bclk = i2s_clk / (div * 2), if div = 0, i2s_clk = bclk.
 * @return     none
 */
static inline void audio_i2s_set_bclk(i2s_select_e i2s_select, unsigned char div)
{
    reg_audio_i2s_pcm_clk_num(i2s_select) = div;
}

/**
 * @brief      This function serves to set the i2s lrclk divider.
 * @param[in]  i2s_select - i2s channel select.
 * @param[in]  adc_div    - adc_lrclk = bclk / (adc_div).
 * @param[in]  dac_div    - dac_lrclk = bclk / (dac_div).
 * @return     none
 */
static inline void audio_i2s_set_lrclk(i2s_select_e i2s_select, unsigned short adc_div, unsigned short dac_div)
{
    reg_audio_i2s_int_pcm_num(i2s_select) = (adc_div - 1) & FLD_I2S_INT_PCM_NUM;
    reg_audio_i2s_dec_pcm_num(i2s_select) = (dac_div - 1) & FLD_I2S_DEC_PCM_NUM;
}

/**
 * @brief      This function serves to enable bclk and lr_clk.
 * @param[in]  i2s_select - i2s channel select
 * @return     none
 */
static inline void audio_i2s_clk_en(i2s_select_e i2s_select)
{
    BM_SET(reg_audio_i2s_cfg1(i2s_select), FLD_I2S_CLK_EN);
}

/**
 * @brief      This function serves to disable bclk and lr_clk
 * @param[in]  i2s_select - i2s channel select
 * @return     none
 */
static inline void audio_i2s_clk_dis(i2s_select_e i2s_select)
{
    BM_CLR(reg_audio_i2s_cfg1(i2s_select), FLD_I2S_CLK_EN);
}

/**
 * @brief      This function serves to set i2s schedule target value.
 * 
 * @param[in]  i2s_select   - i2s channel.
 * @param[in]  target_value - target value.
 * @return none
 */
static inline void audio_i2s_set_target_value(i2s_select_e i2s_select, unsigned int target_value)
{
    reg_audio_i2s_stimer_target(i2s_select) = target_value;
}

/**
 * @brief      This function serves to enable the i2s schedule.

 * @return    none
 */
static inline void audio_i2s_schedule_en(i2s_select_e i2s_select)
{
    BM_SET(reg_audio_i2s_route(i2s_select), FLD_I2S_SCHEDULE_EN);
}

/**
 * @brief      This function serves to disable the i2s schedule.
 * @return    none
 */
static inline void audio_i2s_schedule_dis(i2s_select_e i2s_select)
{
    BM_CLR(reg_audio_i2s_route(i2s_select), FLD_I2S_SCHEDULE_EN);
}

/**
 * @brief      This function serves to enable the i2s align function.
 * @return    none
 */
static inline void audio_i2s_align_en(void)
{
    BM_SET(reg_audio_i2s0_align_cfg, FLD_I2S_ALIGN_EN);
}

/**
 * @brief      This function serves to disable the i2s align function.
 * @return    none
 */
static inline void audio_i2s_align_dis(void)
{
    BM_CLR(reg_audio_i2s0_align_cfg, FLD_I2S_ALIGN_EN);
}

/**
 * @brief      This function serves to config i2s align mode.
 * 
 * @param[in]  align_config - i2s align config.
 * @return     none
 */
static inline void audio_i2s_align_config(i2s_align_config_t *align_config)
{
    reg_audio_i2s0_timer_th  = align_config->align_th;
    reg_audio_i2s0_align_cfg = MASK_VAL(FLD_I2S_ALIGN_EN, 1, FLD_I2S_ALIGN_CTRL, align_config->align_mode, FLD_I2S_ALIGN_MASK, 0, FLD_I2S_CLK_SEL, align_config->align_clk);
}

/**
 * @brief      This function serves to initialize configuration i2s.
 * @param[in]  i2s_config - the relevant configuration struct pointer @see audio_i2s_config_t.
 * @return     none
 */
void audio_i2s_config_init(audio_i2s_config_t *i2s_config);

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio matrix interface                                              *
 *********************************************************************************************************************/
/*!
 * @name Audio matrix interface.
 * @{
 */

/**
 * @brief      This function serves to select fifo rx route source and data format.
 *
 * @param[in]  fifo_num    - fifo channel.
 * @param[in]  route_from  - fifo rx route from.
 * @param[in]  data_format - fifo rx data format (route from i2s/anc/adc/hac valid), others select FIFO_RX_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_rx_fifo_route(audio_fifo_chn_e fifo_num, audio_matrix_fifo_rx_route_e route_from, audio_matrix_fifo_rx_format_e data_format);

/**
 * @brief   This function serves to select i2s tx route source and data format.
 *
 * @param[in]  i2s_tx_chn  - i2s tx channel.
 * @param[in]  route_from  - i2s tx route from.
 * @param[in]  data_format - i2s tx data format(route from fifo/hac2/hac3 valid), others select I2S_TX_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_i2s_tx_route(audio_i2s_tx_chn_e i2s_tx_chn, audio_matrix_i2s_tx_route_e route_from, audio_matrix_i2s_tx_format_e data_format);

/**
 * @brief      This function serves to select anc_src route source and format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_src route from.
 * @param[in]  data_format - anc src data format(route from fifo/i2s/adc valid), others select ANC_SRC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_src_route(audio_anc_chn_e anc_chn, audio_anc_src_chn_e src_chn, audio_matrix_anc_src_route_e route_from, audio_matrix_anc_src_format_e data_format);

/**
 * @brief      This function serves to select anc_src route source and format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_ref route from.
 * @param[in]  data_format - anc ref data format(route from i2s/adc valid), others select ANC_REF_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_ref_route(audio_anc_chn_e anc_chn, audio_anc_ref_chn_e ref_chn, audio_matrix_anc_ref_route_e route_from, audio_matrix_anc_ref_format_e data_format);

/**
 * @brief      This function serves to select anc_err route source and data format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_err route from.
 * @param[in]  data_format - anc err data format(route from i2s/adc valid), others select ANC_ERR_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_err_route(audio_anc_chn_e anc_chn, audio_anc_err_chn_e err_chn, audio_matrix_anc_err_route_e route_from, audio_matrix_anc_err_format_e data_format);

/**
 * @brief      This function serves to select anc_err route source and data format.
 *
 * @param[in]  anc_chn     - anc channel.
 * @param[in]  route_from  - anc_err route from.
 * @param[in]  data_format - anc err data format(route from i2s/adc valid), others select ANC_ERR_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_anc_bz_route(audio_anc_chn_e anc_chn, audio_anc_bz_chn_e bz_chn, audio_matrix_anc_bz_route_e route_from, audio_matrix_anc_bz_format_e data_format);

/**
 * @brief      This function serves to select dac route source and data format.
 *
 * @param[in]  dac_chn     - dac channel.
 * @param[in]  route_from  - dac route from.
 * @param[in]  data_format - dac data format(route from fifo valid), others select DAC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_dac_route(audio_codec_output_select_e dac_chn, audio_matrix_dac_route_e route_from, audio_matrix_dac_format_e data_format);

/**
 * @brief      This function serves to select spdif tx route source.
 *
 * @param[in]  route_from - spdif tx route from.
 * @return     none
 */
static inline void audio_matrix_set_spdif_tx_route(audio_matrix_spdif_tx_route_e route_from)
{
    reg_audio_matrix_tx_sel = (reg_audio_matrix_tx_sel & (~FLD_MATRIX_SPDIF_TX_SEL)) | route_from;
}

/**
 * @brief      This function serves to select hac route source and data format.
 *
 * @param[in]  hac_chn     - hac channel.
 * @param[in]  route_from  - hac route from.
 * @param[in]  data_format - hac data format(route from i2s/adc valid), others select HAC_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_hac_route(audio_hac_chn_e hac_chn, audio_matrix_hac_route_e route_from, audio_matrix_hac_format_e data_format);

/**
 * @brief      This function serves to select side_tone route source and data format.
 *
 * @param[in]  sd_chn      - side_tone channel.
 * @param[in]  route_from  - side_tone route from.
 * @param[in]  data_format - side tone data format(route from fifo/i2s/adc valid), others select SIDE_TONE_DATA_FORMAT_INVALID.
 * @return     none
 */
void audio_matrix_set_side_tone_route(audio_side_tone_chn_e sd_chn, audio_matrix_side_tone_route_e route_from,
                                   audio_matrix_side_tone_format_e data_format);
/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio pin interface                                                 *
 *********************************************************************************************************************/
/*!
 * @name Audio pin interface.
 * @{
 */

/**
 * @brief      This function configures codec0 stream0 dmic pin.
 * @param[in]  dmic0_data - the data of dmic pin
 * @param[in]  dmic0_clk1 - the clk1 of dmic pin
 * @param[in]  dmic0_clk2 - the clk2 of dmic pin,if need not set clk2, please set GPIO_NONE_PIN.
 * @return     none
 */
void audio_dmic0_set_pin(gpio_func_pin_e dmic0_data, gpio_func_pin_e dmic0_clk1, gpio_func_pin_e dmic0_clk2);

/**
 * @brief      This function configures codec0 stream1 dmic pin.
 * @param[in]  dmic1_data - the data of dmic pin.
 * @param[in]  dmic1_clk1 - the clk1 of dmic pin.
 * @param[in]  dmic1_clk2 - the clk2 of dmic pin, if need not set clk2,please set GPIO_NONE_PIN.
 * @return     none
 */
void audio_dmic1_set_pin(gpio_func_pin_e dmic1_data, gpio_func_pin_e dmic1_clk1, gpio_func_pin_e dmic1_clk2);

/**
 * @brief      This function serves to configure i2s pin.
 * @param[in]  i2s_select - channel select.
 * @param[in]  config     - i2s config pin struct.
 * @return     none
 */
void audio_i2s_set_pin(i2s_select_e i2s_select, i2s_pin_config_t *config);

/**
 * @brief      This function serves to configure spdif pin.
 * @param[in]  config     - spdif config pin struct.
 * @return     none
 */
void audio_spdif_set_pin(spdif_pin_config_t *config);

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio side_tone interface                                           *
 *********************************************************************************************************************/
/*!
 * @name Audio side_tone interface.
 * @{
 */

/**
 * @brief      This function servers to enable side tone.
 *
 * @param[in]  sdtn_chn    - side tone channel.
 * @return     none
 */
static inline void audio_side_tone_ch_en(audio_side_tone_chn_e sdtn_chn)
{
    reg_audio_matrix_sdtn_en |= BIT(sdtn_chn);
}

static inline void audio_side_tone_set_simple_mode(audio_side_tone_chn_e sdtn_chn)
{
    switch(sdtn_chn)
    {
        case SIDE_TONE_CHN0:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (FLD_MATRIX_SDTN01_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN0_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN1:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (FLD_MATRIX_SDTN01_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN1_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN2:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (FLD_MATRIX_SDTN23_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN2_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN3:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (FLD_MATRIX_SDTN23_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN3_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN4:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (FLD_MATRIX_SDTN45_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN4_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN5:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (FLD_MATRIX_SDTN45_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN5_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN6:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (FLD_MATRIX_SDTN67_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN6_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN7:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (FLD_MATRIX_SDTN45_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN7_EN_SIMPLE );
            break;
        default:
            break;
    }

}

static inline void audio_side_tones_set_simple_mode(audio_side_tone_chns_e sdtn_chn)
{
    switch(sdtn_chn)
    {
        case SIDE_TONE_CHN01:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (
//                                                  FLD_MATRIX_SDTN01_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN0_EN_SIMPLE |
                                                    FLD_MATRIX_SDTN1_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN23:
            reg_audio_matrix_sdtn0123_simple_ctrl |= (
//                                                  FLD_MATRIX_SDTN23_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN2_EN_SIMPLE |
                                                    FLD_MATRIX_SDTN3_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN45:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (
//                                                  FLD_MATRIX_SDTN45_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN4_EN_SIMPLE |
                                                    FLD_MATRIX_SDTN5_EN_SIMPLE );
            break;
        case SIDE_TONE_CHN67:
            reg_audio_matrix_sdtn4567_simple_ctrl |= (
//                                                  FLD_MATRIX_SDTN45_BY_ADC_VLD |
                                                    FLD_MATRIX_SDTN6_EN_SIMPLE |
                                                    FLD_MATRIX_SDTN7_EN_SIMPLE );
            break;
        default:
            break;
    }

}

/**
 * @brief      This function servers to enable side tone dma mode.
 *
 * @param[in]  sdtn_chns    - side tone channels.
 * @return     none
 */
static inline void audio_side_tone_dma_en(audio_side_tone_chns_e sdtn_chns)
{
    reg_audio_matrix_sdtn_dma_mode |= BIT(sdtn_chns);
}

/**
 * @brief      This function servers to enable side tone dma mode.
 *
 * @param[in]  sdtn_chns    - side tone channels.
 * @param[in]  audio_clk    - audio clk, eg.
 * @param[in]  fs           - sample rate.
 * @param[in]  val          - stereo 2; mono 1.
 * @return     none
 */
static inline void audio_side_tone_set_req_count(audio_side_tone_chns_e sdtn_chns, unsigned int audio_clk, unsigned fs, unsigned char val)
{
    reg_audio_matrix_sdtn_req_count(sdtn_chns) = audio_clk / fs - val;
}

/**
 * @brief      This function serves to enable anc.
 *
 * @param[in]  sdtn_ch - sidetone channel.
 * @param[in]  gain    - adc gain.
 * @return     none
 */
static inline void audio_side_tone_set_adc_gain(audio_side_tone_chn_e sdtn_ch, audio_side_tone_gain_e gain)
{
    unsigned char chn_mask = (sdtn_ch % 2) ? FLD_MATRIX_SDTN_ODD_ADC : FLD_MATRIX_SDTN_EVEN_ADC;

    reg_audio_matrix_sdtn_gain_adc(sdtn_ch) = (reg_audio_matrix_sdtn_gain_adc(sdtn_ch) & (~chn_mask)) | MASK_VAL(chn_mask, gain);
}

/**
 * @brief      This function serves to enable anc.
 *
 * @param[in]  sdtn_ch - anc channel.
 * @param[in]  gain    - dac gain.
 * @return     none
 */
static inline void audio_side_tone_set_dac_gain(audio_side_tone_chn_e sdtn_ch, audio_side_tone_gain_e gain)
{
    unsigned char chn_mask = (sdtn_ch % 2) ? FLD_MATRIX_SDTN_ODD_DAC : FLD_MATRIX_SDTN_EVEN_DAC;

    reg_audio_matrix_sdtn_gain_dac(sdtn_ch) = (reg_audio_matrix_sdtn_gain_dac(sdtn_ch) & (~chn_mask)) | MASK_VAL(chn_mask, gain);
}

/**
 * @}
 */

/**********************************************************************************************************************
 *                                                Audio spdif interface                                               *
 *********************************************************************************************************************/
/*!
 * @name Audio spdif interface.
 * @{
 */

/*!
 * @name Audio spdif interface
 * @{
 */
/**
 * @brief      This function serves to set spdif rx fs.
 * @param[in]  clk - audio pll clock
 * @return     none
 * @note       only support PLL1_AUDIO_CLK_169P344M and PLL1_AUDIO_CLK_158P0544M
 */
void audio_spdif_set_rx_fs(pll_audio_clk_e clk);

/**
 * @brief      This function serves to enable spdif tx encode.
 * @param      none
 * @return     none
 */
static inline void audio_spdif_tx_encode_en(void)
{
    BM_SET(reg_audio_spdif_config, FLD_SPDIF_ENCODER_EN);
}

/**
 * @brief      This function serves to enable spdif rx decode.
 * @param      none
 * @return     none
 */
static inline void audio_spdif_rx_decode_en(void)
{
    BM_SET(reg_audio_spdif_config, FLD_SPDIF_DECODER_EN);
}

/**
 * @brief      This function serves to set spdif rx parity.
 * @param[in]  val - 0:parity by hardware; 1:parity by software
 * @return     none
 */
static inline void audio_spdif_set_rx_parity(unsigned char val)
{
    if (val) {
        BM_SET(reg_audio_spdif_config, FLD_SPDIF_PARITY_SELECT);
    } else {
        BM_CLR(reg_audio_spdif_config, FLD_SPDIF_PARITY_SELECT);
    }
}

/**
 * @brief      This function serves to enable spdif debug clk.
 * @param      none
 * @return     none
 */
static inline void audio_spdif_dbg_clk_en(void)
{
    BM_SET(reg_audio_spdif_config, FLD_SPDIF_DBG_CLK_EN);
}

/**
 * @brief      This function serves to set spdif RX format.
 * @param[in]  val - 0:low 28 bits for data, high 4bits for Pre_code. 1:high 28 bits for data, low 4bits for Pre_code.
 * @return     none
 */
static inline void audio_spdif_set_rx_fmt(unsigned char val)
{
    if (val) {
        BM_SET(reg_audio_spdif_config, FLD_SPDIF_RX_FMT);
    } else {
        BM_CLR(reg_audio_spdif_config, FLD_SPDIF_RX_FMT);
    }
}

/**
 * @brief      This function serves to set spdif tx format.
 * @param[in]  val - 0:low 28 bits for data, high 4bits for Pre_code. 1 :high 28 bits for data, low 4bits for Pre_code.
 * @return     none
 */
static inline void audio_spdif_set_tx_fmt(unsigned char val)
{
    if (val) {
        BM_SET(reg_audio_spdif_config, FLD_SPDIF_TX_FMT);
    } else {
        BM_CLR(reg_audio_spdif_config, FLD_SPDIF_TX_FMT);
    }
}

/**
 * @brief      This function serves to set hardware auto generates the preamble
 * @param[in]  val - 1'b0:preamble by software;1'b1:preamble by hardware
 * @return     none
 */
static inline void audio_spdif_set_auto_preamble(unsigned char val)
{
    if (val) {
        BM_SET(reg_audio_spdif_config, FLD_SPDIF_PREAMBLE_SELECT);
    } else {
        BM_CLR(reg_audio_spdif_config, FLD_SPDIF_PREAMBLE_SELECT);
    }
}

/**
 * @brief      This function serves to The hardware auto generates the preamble
 * @param      none
 * @return     none
 */
static inline void audio_spdif_soft_preamble(void)
{
    BM_CLR(reg_audio_spdif_config, FLD_SPDIF_PREAMBLE_SELECT);
}

/**
 * @brief      This function serves to set spdif tx clock.
 * @param[in]  tx_clk - spdif_tx_clk_e
 * @return     none
 */
static inline void audio_spdif_set_tx_clk(spdif_tx_clk_e tx_clk)
{
    BM_SET(reg_audio_clk_en_0, FLD_CLK_SPDIF_EN);
    reg_audio_spdif_tx_div = tx_clk;
}

/**
 * @}
 */

 #endif /* _AUDIO_H_ */

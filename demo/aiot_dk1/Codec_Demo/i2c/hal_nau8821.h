/********************************************************************************************************
 * @file    hal_nau8821.h
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

#ifndef __NAU8821_H__
#define __NAU8821_H__

#include <stdbool.h>
#include <stdint.h>
#include "hal_i2c.h"

#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)

#define I2C_NAU8821_ADD                    0x36

#define NAU8821_R00_RESET                  0x00
#define NAU8821_R01_ENA_CTRL               0x01
#define NAU8821_R03_CLK_DIVIDER            0x03
#define NAU8821_R04_FLL1                   0x04
#define NAU8821_R05_FLL2                   0x05
#define NAU8821_R06_FLL3                   0x06
#define NAU8821_R07_FLL4                   0x07
#define NAU8821_R08_FLL5                   0x08
#define NAU8821_R09_FLL6                   0x09
#define NAU8821_R0A_FLL7                   0x0a
#define NAU8821_R0B_FLL8                   0x0b
#define NAU8821_R0D_JACK_DET_CTRL          0x0d
#define NAU8821_R0F_INTERRUPT_MASK         0x0f
#define NAU8821_R10_IRQ_STATUS             0x10
#define NAU8821_R11_INT_CLR_KEY_STATUS     0x11
#define NAU8821_R12_INTERRUPT_DIS_CTRL     0x12
#define NAU8821_R13_DMIC_CTRL              0x13
#define NAU8821_R1A_GPIO12_CTRL            0x1a
#define NAU8821_R1B_TDM_CTRL               0x1b
#define NAU8821_R1C_I2S_PCM_CTRL1          0x1c
#define NAU8821_R1D_I2S_PCM_CTRL2          0x1d
#define NAU8821_R1E_LEFT_TIME_SLOT         0x1e
#define NAU8821_R1F_RIGHT_TIME_SLOT        0x1f
#define NAU8821_R21_BIQ0_COF1              0x21
#define NAU8821_R22_BIQ0_COF2              0x22
#define NAU8821_R23_BIQ0_COF3              0x23
#define NAU8821_R24_BIQ0_COF4              0x24
#define NAU8821_R25_BIQ0_COF5              0x25
#define NAU8821_R26_BIQ0_COF6              0x26
#define NAU8821_R27_BIQ0_COF7              0x27
#define NAU8821_R28_BIQ0_COF8              0x28
#define NAU8821_R29_BIQ0_COF9              0x29
#define NAU8821_R2A_BIQ0_COF10             0x2a
#define NAU8821_R2B_ADC_RATE               0x2b
#define NAU8821_R2C_DAC_CTRL1              0x2c
#define NAU8821_R2D_DAC_CTRL2              0x2d
#define NAU8821_R2F_DAC_DGAIN_CTRL         0x2f
#define NAU8821_R30_ADC_DGAIN_CTRL         0x30
#define NAU8821_R31_MUTE_CTRL              0x31
#define NAU8821_R32_HSVOL_CTRL             0x32
#define NAU8821_R34_DACR_CTRL              0x34
#define NAU8821_R35_ADC_DGAIN_CTRL1        0x35
#define NAU8821_R36_ADC_DRC_KNEE_IP12      0x36
#define NAU8821_R37_ADC_DRC_KNEE_IP34      0x37
#define NAU8821_R38_ADC_DRC_SLOPES         0x38
#define NAU8821_R39_ADC_DRC_ATKDCY         0x39
#define NAU8821_R3A_DAC_DRC_KNEE_IP12      0x3a
#define NAU8821_R3B_DAC_DRC_KNEE_IP34      0x3b
#define NAU8821_R3C_DAC_DRC_SLOPES         0x3c
#define NAU8821_R3D_DAC_DRC_ATKDCY         0x3d
#define NAU8821_R41_BIQ1_COF1              0x41
#define NAU8821_R42_BIQ1_COF2              0x42
#define NAU8821_R43_BIQ1_COF3              0x43
#define NAU8821_R44_BIQ1_COF4              0x44
#define NAU8821_R45_BIQ1_COF5              0x45
#define NAU8821_R46_BIQ1_COF6              0x46
#define NAU8821_R47_BIQ1_COF7              0x47
#define NAU8821_R48_BIQ1_COF8              0x48
#define NAU8821_R49_BIQ1_COF9              0x49
#define NAU8821_R4A_BIQ1_COF10             0x4a
#define NAU8821_R4B_CLASSG_CTRL            0x4b
#define NAU8821_R4C_IMM_MODE_CTRL          0x4c
#define NAU8821_R4D_IMM_RMS_L              0x4d
#define NAU8821_R4E_FUSE_CTRL2             0x4e
#define NAU8821_R4F_FUSE_CTRL3             0x4f
#define NAU8821_R51_FUSE_CTRL1             0x51
#define NAU8821_R53_OTPDOUT_1              0x53
#define NAU8821_R54_OTPDOUT_2              0x54
#define NAU8821_R55_MISC_CTRL              0x55
#define NAU8821_R58_I2C_DEVICE_ID          0x58
#define NAU8821_R59_SARDOUT_RAM_STATUS     0x59
#define NAU8821_R5A_SOFTWARE_RST           0x5a
#define NAU8821_R66_BIAS_ADJ               0x66
#define NAU8821_R68_TRIM_SETTINGS          0x68
#define NAU8821_R69_ANALOG_CONTROL_1       0x69
#define NAU8821_R6A_ANALOG_CONTROL_2       0x6a
#define NAU8821_R6B_PGA_MUTE               0x6b
#define NAU8821_R71_ANALOG_ADC_1           0x71
#define NAU8821_R72_ANALOG_ADC_2           0x72
#define NAU8821_R73_RDAC                   0x73
#define NAU8821_R74_MIC_BIAS               0x74
#define NAU8821_R76_BOOST                  0x76
#define NAU8821_R77_FEPGA                  0x77
#define NAU8821_R7E_PGA_GAIN               0x7e
#define NAU8821_R7F_POWER_UP_CONTROL       0x7f
#define NAU8821_R80_CHARGE_PUMP            0x80
#define NAU8821_R81_CHARGE_PUMP_INPUT_READ 0x81
#define NAU8821_R82_GENERAL_STATUS         0x82
#define NAU8821_REG_MAX                    NAU8821_R82_GENERAL_STATUS
///* 16-bit control register address, and 16-bits control register data */
#define NAU8821_REG_ADDR_LEN 16
#define NAU8821_REG_DATA_LEN 16

/* ENA_CTRL (0x01) */
#define NAU8821_CMLCK_ENB_SFT   15
#define NAU8821_CMLCK_ENB       (0x1 << NAU8821_CMLCK_ENB_SFT)
#define NAU8821_CLK_DAC_INV_SFT 14
#define NAU8821_CLK_DAC_INV     (0x1 << NAU8821_CLK_DAC_INV)
#define NAU8821_EN_DACR_SFT     11
#define NAU8821_EN_DACR         (0x1 << NAU8821_EN_DACR_SFT)
#define NAU8821_EN_DACL_SFT     10
#define NAU8821_EN_DACL         (0x1 << NAU8821_EN_DACL_SFT)
#define NAU8821_EN_ADCR_SFT     9
#define NAU8821_EN_ADCR         (0x1 << NAU8821_EN_ADCR_SFT)
#define NAU8821_EN_ADCL_SFT     8
#define NAU8821_EN_ADCL         (0x1 << NAU8821_EN_ADCL_SFT)
#define NAU8821_EN_ADC_CLK_SFT  7
#define NAU8821_EN_ADC_CLK      (0x1 << NAU8821_EN_ADC_CLK_SFT)
#define NAU8821_EN_DAC_CLK_SFT  6
#define NAU8821_EN_DAC_CLK      (0x1 << NAU8821_EN_DAC_CLK_SFT)
#define NAU8821_EN_I2S_CLK_SFT  4
#define NAU8821_EN_I2S_CLK      (0x1 << NAU8821_EN_I2S_CLK_SFT)
#define NAU8821_EN_DRC_CLK_SFT  0
#define NAU8821_EN_DRC_CLK      (0x1 << NAU8821_EN_DRC_CLK_SFT)

/* CLK_DIVIDER (0x03) */
#define NAU8821_CLK_SRC_SFT        15
#define NAU8821_CLK_SRC_MASK       (0x1 << NAU8821_CLK_SRC_SFT)
#define NAU8821_CLK_SRC_VCO        (0x1 << NAU8821_CLK_SRC_SFT)
#define NAU8821_CLK_SRC_MCLK       (0x0 << NAU8821_CLK_SRC_SFT)
#define NAU8821_CLK_CODEC_SRC_SFT  13
#define NAU8821_CLK_CODEC_SRC_MASK (0x1 << NAU8821_CLK_CODEC_SRC_SFT)
#define NAU8821_CLK_CODEC_SRC_VCO  (0x1 << NAU8821_CLK_CODEC_SRC_SFT)
#define NAU8821_CLK_CODEC_SRC_MCLK (0x0 << NAU8821_CLK_CODEC_SRC_SFT)
#define NAU8821_CLK_ADC_SRC_SFT    6
#define NAU8821_CLK_ADC_SRC_MASK   (0x3 << NAU8821_CLK_ADC_SRC_SFT)
#define NAU8821_CLK_DAC_SRC_SFT    4
#define NAU8821_CLK_DAC_SRC_MASK   (0x3 << NAU8821_CLK_DAC_SRC_SFT)
#define NAU8821_CLK_MCLK_SRC_MASK  0xf

/* FLL1 (0x04) */
#define NAU8821_ICTRL_LATCH_SFT  10
#define NAU8821_ICTRL_LATCH_MASK (0x7 << NAU8821_ICTRL_LATCH_SFT)
#define NAU8821_FLL_RATIO_MASK   0x7f

/* FLL3 (0x06) */
#define NAU8821_GAIN_ERR_SFT     12
#define NAU8821_GAIN_ERR_MASK    (0xf << NAU8821_GAIN_ERR_SFT)
#define NAU8821_FLL_CLK_SRC_SFT  10
#define NAU8821_FLL_CLK_SRC_MASK (0x3 << NAU8821_FLL_CLK_SRC_SFT)
#define NAU8821_FLL_CLK_SRC_FS   (0x3 << NAU8821_FLL_CLK_SRC_SFT)
#define NAU8821_FLL_CLK_SRC_BLK  (0x2 << NAU8821_FLL_CLK_SRC_SFT)
#define NAU8821_FLL_CLK_SRC_MCLK (0x0 << NAU8821_FLL_CLK_SRC_SFT)
#define NAU8821_FLL_INTEGER_MASK 0x3ff

/* FLL4 (0x07) */
#define NAU8821_HIGHBW_EN_SFT    15
#define NAU8821_HIGHBW_EN        (0x1 << NAU8821_HIGHBW_EN_SFT)
#define NAU8821_FLL_REF_DIV_SFT  10
#define NAU8821_FLL_REF_DIV_MASK (0x3 << NAU8821_FLL_REF_DIV_SFT)

/* FLL5 (0x08) */
#define NAU8821_FLL_PDB_DAC_EN    (0x1 << 15)
#define NAU8821_FLL_LOOP_FTR_EN   (0x1 << 14)
#define NAU8821_FLL_CLK_SW_SFT    13
#define NAU8821_FLL_CLK_SW_MASK   (0x1 << NAU8821_FLL_CLK_SW_SFT)
#define NAU8821_FLL_CLK_SW_N2     (0x1 << NAU8821_FLL_CLK_SW_SFT)
#define NAU8821_FLL_CLK_SW_REF    (0x0 << NAU8821_FLL_CLK_SW_SFT)
#define NAU8821_FLL_FTR_SW_SFT    12
#define NAU8821_FLL_FTR_SW_MASK   (0x1 << NAU8821_FLL_FTR_SW_SFT)
#define NAU8821_FLL_FTR_SW_ACCU   (0x1 << NAU8821_FLL_FTR_SW_SFT)
#define NAU8821_FLL_FTR_SW_FILTER (0x0 << NAU8821_FLL_FTR_SW_SFT)

/* FLL6 (0x09) */
#define NAU8821_DCO_EN    (0x1 << 15)
#define NAU8821_SDM_EN    (0x1 << 14)
#define NAU8821_CUTOFF500 (0x1 << 13)

/* FLL7 (0x0a) */
#define NAU8821_FLL_FRACH_MASK 0xff

/* FLL8 (0x0b) */
#define NAU8821_FLL_FRACL_MASK 0xffff

/* JACK_DET_CTRL (0x0d) */
/* 0 - open, 1 - short to GND */
#define NAU8821_SPKR_DWN1R_SFT            15
#define NAU8821_SPKR_DWN1R                (0x1 << NAU8821_SPKR_DWN1R_SFT)
#define NAU8821_SPKR_DWN1L_SFT            14
#define NAU8821_SPKR_DWN1L                (0x1 << NAU8821_SPKR_DWN1L_SFT)
#define NAU8821_JACK_DET_RESTART          (0x1 << 9)
#define NAU8821_JACK_DET_DB_BYPASS        (0x1 << 8)
#define NAU8821_JACK_INSERT_DEBOUNCE_SFT  5
#define NAU8821_JACK_INSERT_DEBOUNCE_MASK (0x7 << NAU8821_JACK_INSERT_DEBOUNCE_SFT)
#define NAU8821_JACK_EJECT_DEBOUNCE_SFT   2
#define NAU8821_JACK_EJECT_DEBOUNCE_MASK  (0x7 << NAU8821_JACK_EJECT_DEBOUNCE_SFT)
#define NAU8821_JACK_POLARITY             (0x1 << 1) /* 0 - active low, 1 - active high */

/* INTERRUPT_MASK (0x0f) */
#define NAU8821_IRQ_PIN_PULL_UP    (0x1 << 14)
#define NAU8821_IRQ_PIN_PULL_EN    (0x1 << 13)
#define NAU8821_IRQ_OUTPUT_EN      (0x1 << 11)
#define NAU8821_IRQ_RMS_EN         (0x1 << 8)
#define NAU8821_IRQ_KEY_RELEASE_EN (0x1 << 7)
#define NAU8821_IRQ_KEY_PRESS_EN   (0x1 << 6)
#define NAU8821_IRQ_MIC_DET_EN     (0x1 << 4)
#define NAU8821_IRQ_EJECT_EN       (0x1 << 2)
#define NAU8821_IRQ_INSERT_EN      0x1

/* IRQ_STATUS (0x10) */
#define NAU8821_SHORT_CIRCUIT_IRQ    (0x1 << 9)
#define NAU8821_IMPEDANCE_MEAS_IRQ   (0x1 << 8)
#define NAU8821_KEY_IRQ_SFT          6
#define NAU8821_KEY_IRQ_MASK         (0x3 << NAU8821_KEY_IRQ_SFT)
#define NAU8821_KEY_RELEASE_IRQ      (0x2 << NAU8821_KEY_IRQ_SFT)
#define NAU8821_KEY_SHORT_PRESS_IRQ  (0x1 << NAU8821_KEY_IRQ_SFT)
#define NAU8821_MIC_DETECT_IRQ       (0x1 << 4)
#define NAU8821_JACK_EJECT_IRQ_MASK  (0x3 << 2)
#define NAU8821_JACK_EJECT_DETECTED  (0x1 << 2)
#define NAU8821_JACK_INSERT_IRQ_MASK 0x3
#define NAU8821_JACK_INSERT_DETECTED 0x1

/* INTERRUPT_DIS_CTRL (0x12) */
#define NAU8821_IRQ_KEY_RELEASE_DIS (0x1 << 7)
#define NAU8821_IRQ_KEY_PRESS_DIS   (0x1 << 6)
#define NAU8821_IRQ_MIC_DIS         (0x1 << 4)
#define NAU8821_IRQ_EJECT_DIS       (0x1 << 2)
#define NAU8821_IRQ_INSERT_DIS      0x1

/* DMIC_CTRL (0x13) */
#define NAU8821_DMIC_DS_SFT   7
#define NAU8821_DMIC_DS_MASK  (0x1 << NAU8821_DMIC_DS_SFT)
#define NAU8821_DMIC_DS_HIGH  (0x1 << NAU8821_DMIC_DS_SFT)
#define NAU8821_DMIC_DS_LOW   (0x0 << NAU8821_DMIC_DS_SFT)
#define NAU8821_DMIC_SRC_SFT  1
#define NAU8821_DMIC_SRC_MASK (0x3 << NAU8821_DMIC_SRC_SFT)
#define NAU8821_CLK_DMIC_SRC  (0x2 << NAU8821_DMIC_SRC_SFT)
#define NAU8821_DMIC_EN_SFT   0

/* GPIO12_CTRL (0x1a) */
#define NAU8821_JKDET_PULL_UP   (0x1 << 11) /* 0 - pull down, 1 - pull up */
#define NAU8821_JKDET_PULL_EN   (0x1 << 9)  /* 0 - enable pull, 1 - disable */
#define NAU8821_JKDET_OUTPUT_EN (0x1 << 8)  /* 0 - enable input, 1 - enable output */

/* TDM_CTRL (0x1b) */
#define NAU8821_TDM_EN_SFT   15
#define NAU8821_TDM_EN       (0x1 << NAU8821_TDM_EN_SFT)
#define NAU8821_ADCPHS_SFT   13
#define NAU8821_DACL_CH_SFT  7
#define NAU8821_DACL_CH_MASK (0x7 << NAU8821_DACL_CH_SFT)
#define NAU8821_DACR_CH_SFT  4
#define NAU8821_DACR_CH_MASK (0x7 << NAU8821_DACR_CH_SFT)
#define NAU8821_ADCL_CH_SFT  2
#define NAU8821_ADCL_CH_MASK (0x3 << NAU8821_ADCL_CH_SFT)
#define NAU8821_ADCR_CH_SFT  0
#define NAU8821_ADCR_CH_MASK 0x3

/* I2S_PCM_CTRL1 (0x1c) */
#define NAU8821_I2S_BP_SFT    7
#define NAU8821_I2S_BP_MASK   (0x1 << NAU8821_I2S_BP_SFT)
#define NAU8821_I2S_BP_INV    (0x1 << NAU8821_I2S_BP_SFT)
#define NAU8821_I2S_PCMB_SFT  6
#define NAU8821_I2S_PCMB_MASK (0x1 << NAU8821_I2S_PCMB_SFT)
#define NAU8821_I2S_PCMB_EN   (0x1 << NAU8821_I2S_PCMB_SFT)
#define NAU8821_I2S_DL_SFT    2
#define NAU8821_I2S_DL_MASK   (0x3 << NAU8821_I2S_DL_SFT)
#define NAU8821_I2S_DL_32     (0x3 << NAU8821_I2S_DL_SFT)
#define NAU8821_I2S_DL_24     (0x2 << NAU8821_I2S_DL_SFT)
#define NAU8821_I2S_DL_20     (0x1 << NAU8821_I2S_DL_SFT)
#define NAU8821_I2S_DL_16     (0x0 << NAU8821_I2S_DL_SFT)
#define NAU8821_I2S_DF_MASK   0x3
#define NAU8821_I2S_DF_PCM_AB 0x3
#define NAU8821_I2S_DF_I2S    0x2
#define NAU8821_I2S_DF_LEFT   0x1
#define NAU8821_I2S_DF_RIGHT  0x0

/* I2S_PCM_CTRL2 (0x1d) */
#define NAU8821_I2S_TRISTATE_SFT 15
#define NAU8821_I2S_TRISTATE     (0x1 << NAU8821_I2S_TRISTATE_SFT)
#define NAU8821_I2S_LRC_DIV_SFT  12
#define NAU8821_I2S_LRC_DIV_MASK (0x3 << NAU8821_I2S_LRC_DIV_SFT)
#define NAU8821_I2S_MS_SFT       3
#define NAU8821_I2S_MS_MASK      (0x1 << NAU8821_I2S_MS_SFT)
#define NAU8821_I2S_MS_MASTER    (0x1 << NAU8821_I2S_MS_SFT)
#define NAU8821_I2S_MS_SLAVE     (0x0 << NAU8821_I2S_MS_SFT)
#define NAU8821_I2S_BLK_DIV_MASK 0x7

/* LEFT_TIME_SLOT (0x1e) */
#define NAU8821_TSLOT_L_OFFSET_MASK 0x3ff
#define NAU8821_DIS_FS_SHORT_DET    (0x1 << 13)

/* RIGHT_TIME_SLOT (0x1f) */
#define NAU8821_TSLOT_R_OFFSET_MASK 0x3ff

/* BIQ0_COF10 (0x2a) */
#define NAU8821_BIQ0_ADC_EN_SFT 3
#define NAU8821_BIQ0_ADC_EN_EN  (0x1 << NAU8821_BIQ0_ADC_EN_SFT)

/* ADC_RATE (0x2b) */
#define NAU8821_ADC_SYNC_DOWN_SFT  0
#define NAU8821_ADC_SYNC_DOWN_MASK 0x3
#define NAU8821_ADC_SYNC_DOWN_256  0x3
#define NAU8821_ADC_SYNC_DOWN_128  0x2
#define NAU8821_ADC_SYNC_DOWN_64   0x1
#define NAU8821_ADC_SYNC_DOWN_32   0x0
#define NAU8821_ADC_L_SRC_SFT      15
#define NAU8821_ADC_L_SRC_EN       (0x1 << NAU8821_ADC_L_SRC_SFT)
#define NAU8821_ADC_R_SRC_SFT      14
#define NAU8821_ADC_R_SRC_EN       (0x1 << NAU8821_ADC_R_SRC_SFT)

/* DAC_CTRL1 (0x2c) */
#define NAU8821_DAC_OVERSAMPLE_SFT  0
#define NAU8821_DAC_OVERSAMPLE_MASK 0x7
#define NAU8821_DAC_OVERSAMPLE_32   0x4
#define NAU8821_DAC_OVERSAMPLE_128  0x2
#define NAU8821_DAC_OVERSAMPLE_256  0x1
#define NAU8821_DAC_OVERSAMPLE_64   0x0

/* DAC_DGAIN_CTRL (0x2f) */
#define NAU8821_DAC1_TO_DAC0_ST_SFT  8
#define NAU8821_DAC1_TO_DAC0_ST_MASK (0xff << NAU8821_DAC1_TO_DAC0_ST_SFT)
#define NAU8821_DAC0_TO_DAC1_ST_SFT  0
#define NAU8821_DAC0_TO_DAC1_ST_MASK 0xff

/* MUTE_CTRL (0x31) */
#define NAU8821_DAC_ZC_EN     (0x1 << 12)
#define NAU8821_DAC_SOFT_MUTE (0x1 << 9)
#define NAU8821_ADC_ZC_EN     (0x1 << 2)
#define NAU8821_ADC_SOFT_MUTE (0x1 << 1)

/* HSVOL_CTRL (0x32) */
#define NAU8821_HP_MUTE      (0x1 << 15)
#define NAU8821_HP_MUTE_AUTO (0x1 << 14)
#define NAU8821_HPL_MUTE     (0x1 << 13)
#define NAU8821_HPR_MUTE     (0x1 << 12)
#define NAU8821_HPL_VOL_SFT  4
#define NAU8821_HPL_VOL_MASK (0x3 << NAU8821_HPL_VOL_SFT)
#define NAU8821_HPR_VOL_SFT  0
#define NAU8821_HPR_VOL_MASK (0x3 << NAU8821_HPR_VOL_SFT)

/* DACR_CTRL (0x34) */
#define NAU8821_DACR_CH_VOL_SFT  8
#define NAU8821_DACR_CH_VOL_MASK (0xff << NAU8821_DACR_CH_VOL_SFT)
#define NAU8821_DACL_CH_VOL_SFT  0
#define NAU8821_DACL_CH_VOL_MASK 0xff

/* ADC_DGAIN_CTRL1 (0x35) */
#define NAU8821_ADCR_CH_VOL_SFT  8
#define NAU8821_ADCR_CH_VOL_MASK (0xff << NAU8821_ADCR_CH_VOL_SFT)
#define NAU8821_ADCL_CH_VOL_SFT  0
#define NAU8821_ADCL_CH_VOL_MASK 0xff

/* BIQ1_COF10 (0x4a) */
#define NAU8821_BIQ1_DAC_EN_SFT 3
#define NAU8821_BIQ1_DAC_EN_EN  (0x1 << NAU8821_BIQ1_DAC_EN_SFT)

/* CLASSG_CTRL (0x4b) */
#define NAU8821_CLASSG_TIMER_SFT   8
#define NAU8821_CLASSG_TIMER_MASK  (0x3f << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_64MS  (0x20 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_32MS  (0x10 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_16MS  (0x8 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_8MS   (0x4 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_2MS   (0x2 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_TIMER_1MS   (0x1 << NAU8821_CLASSG_TIMER_SFT)
#define NAU8821_CLASSG_RDAC_EN_SFT 2
#define NAU8821_CLASSG_RDAC_EN     (0x1 << NAU8821_CLASSG_RDAC_EN_SFT)
#define NAU8821_CLASSG_LDAC_EN_SFT 1
#define NAU8821_CLASSG_LDAC_EN     (0x1 << NAU8821_CLASSG_LDAC_EN_SFT)
#define NAU8821_CLASSG_EN_SFT      0
#define NAU8821_CLASSG_EN          0x1

/* IMM_MODE_CTRL (0x4c) */
#define NAU8821_IMM_THD_SFT      8
#define NAU8821_IMM_THD_MASK     (0x3f << NAU8821_IMM_THD_SFT)
#define NAU8821_IMM_GEN_VOL_SFT  6
#define NAU8821_IMM_GEN_VOL_MASK (0x3 << NAU8821_IMM_GEN_VOL_SFT)
#define NAU8821_IMM_CYC_SFT      4
#define NAU8821_IMM_CYC_MASK     (0x3 << NAU8821_IMM_CYC_SFT)
#define NAU8821_IMM_EN           (0x1 << 3)
#define NAU8821_IMM_DAC_SRC_MASK 0x3

/* I2C_DEVICE_ID (0x58) */
#define NAU8821_KEYDET           (0x1 << 7)
#define NAU8821_MICDET           (0x1 << 6)
#define NAU8821_SOFTWARE_ID_MASK 0x3

/* BIAS_ADJ (0x66) */
#define NAU8821_BIAS_HP_IMP        (0x1 << 15)
#define NAU8821_BIAS_TESTDAC_SFT   8
#define NAU8821_BIAS_TESTDAC_EN    (0x3 << NAU8821_BIAS_TESTDAC_SFT)
#define NAU8821_BIAS_TESTDACR_EN   (0x2 << NAU8821_BIAS_TESTDAC_SFT)
#define NAU8821_BIAS_TESTDACL_EN   (0x1 << NAU8821_BIAS_TESTDAC_SFT)
#define NAU8821_BIAS_VMID          (0x1 << 6)
#define NAU8821_BIAS_VMID_SEL_SFT  4
#define NAU8821_BIAS_VMID_SEL_MASK (0x3 << NAU8821_BIAS_VMID_SEL_SFT)

/* ANALOG_CONTROL_1 (0x69) */
#define NAU8821_JD_POL_SFT      2
#define NAU8821_JD_POL_MASK     (0x1 << NAU8821_JD_POL_SFT)
#define NAU8821_JD_POL_INV      (0x1 << NAU8821_JD_POL_SFT)
#define NAU8821_JD_OUT_POL_SFT  1
#define NAU8821_JD_OUT_POL_MASK (0x1 << NAU8821_JD_OUT_POL_SFT)
#define NAU8821_JD_OUT_POL_INV  (0x1 << NAU8821_JD_OUT_POL_SFT)
#define NAU8821_JD_EN_SFT       0
#define NAU8821_JD_EN           0x1

/* ANALOG_CONTROL_2 (0x6a) */
#define NAU8821_HP_NON_CLASSG_CURRENT_2xADJ (0x1 << 12)
#define NAU8821_DAC_CAPACITOR_MSB           (0x1 << 1)
#define NAU8821_DAC_CAPACITOR_LSB           0x1

/* ANALOG_ADC_1 (0x71) */
#define NAU8821_MICDET_EN_SFT 0
#define NAU8821_MICDET_MASK   0x1
#define NAU8821_MICDET_DIS    0x1
#define NAU8821_MICDET_EN     0x0

/* ANALOG_ADC_2 (0x72) */
#define NAU8821_ADC_VREFSEL_SFT  8
#define NAU8821_ADC_VREFSEL_MASK (0x3 << NAU8821_ADC_VREFSEL_SFT)
#define NAU8821_POWERUP_ADCL_SFT 6
#define NAU8821_POWERUP_ADCL     (0x1 << NAU8821_POWERUP_ADCL_SFT)
#define NAU8821_POWERUP_ADCR_SFT 4
#define NAU8821_POWERUP_ADCR     (0x1 << NAU8821_POWERUP_ADCR_SFT)

/* RDAC (0x73) */
#define NAU8821_DACR_EN_SFT        13
#define NAU8821_DACR_EN            (0x3 << NAU8821_DACR_EN_SFT)
#define NAU8821_DACL_EN_SFT        12
#define NAU8821_DACL_EN            (0x3 << NAU8821_DACL_EN_SFT)
#define NAU8821_DACR_CLK_EN_SFT    9
#define NAU8821_DACR_CLK_EN        (0x3 << NAU8821_DACR_CLK_EN_SFT)
#define NAU8821_DACL_CLK_EN_SFT    8
#define NAU8821_DACL_CLK_EN        (0x3 << NAU8821_DACL_CLK_EN_SFT)
#define NAU8821_DAC_CLK_DELAY_SFT  4
#define NAU8821_DAC_CLK_DELAY_MASK (0x7 << NAU8821_DAC_CLK_DELAY_SFT)
#define NAU8821_DAC_VREF_SFT       2
#define NAU8821_DAC_VREF_MASK      (0x3 << NAU8821_DAC_VREF_SFT)

/* MIC_BIAS (0x74) */
#define NAU8821_MICBIAS_JKR2         (0x1 << 12)
#define NAU8821_MICBIAS_POWERUP_SFT  8
#define NAU8821_MICBIAS_POWERUP      (0x1 << NAU8821_MICBIAS_POWERUP_SFT)
#define NAU8821_MICBIAS_VOLTAGE_SFT  0
#define NAU8821_MICBIAS_VOLTAGE_MASK 0x7

/* BOOST (0x76) */
#define NAU8821_PRECHARGE_DIS     (0x1 << 13)
#define NAU8821_GLOBAL_BIAS_EN    (0x1 << 12)
#define NAU8821_HP_BOOST_DIS_SFT  9
#define NAU8821_HP_BOOST_DIS      (0x1 << NAU8821_HP_BOOST_DIS_SFT)
#define NAU8821_HP_BOOST_G_DIS    (0x1 << 8)
#define NAU8821_SHORT_SHUTDOWN_EN (0x1 << 6)

/* FEPGA (0x77) */
#define NAU8821_FEPGA_MODEL_SFT  4
#define NAU8821_FEPGA_MODEL_MASK (0xf << NAU8821_FEPGA_MODEL_SFT)
#define NAU8821_FEPGA_MODER_SFT  0
#define NAU8821_FEPGA_MODER_MASK 0xf

/* PGA_GAIN (0x7e) */
#define NAU8821_PGA_GAIN_L_SFT  8
#define NAU8821_PGA_GAIN_L_MASK (0x3f << NAU8821_PGA_GAIN_L_SFT)
#define NAU8821_PGA_GAIN_R_SFT  0
#define NAU8821_PGA_GAIN_R_MASK 0x3f

/* POWER_UP_CONTROL (0x7f) */
#define NAU8821_PUP_PGA_L_SFT       15
#define NAU8821_PUP_PGA_L           (0x1 << NAU8821_PUP_PGA_L_SFT)
#define NAU8821_PUP_PGA_R_SFT       14
#define NAU8821_PUP_PGA_R           (0x1 << NAU8821_PUP_PGA_R_SFT)
#define NAU8821_PUP_INTEG_R_SFT     5
#define NAU8821_PUP_INTEG_R         (0x1 << NAU8821_PUP_INTEG_R_SFT)
#define NAU8821_PUP_INTEG_L_SFT     4
#define NAU8821_PUP_INTEG_L         (0x1 << NAU8821_PUP_INTEG_L_SFT)
#define NAU8821_PUP_DRV_INSTG_R_SFT 3
#define NAU8821_PUP_DRV_INSTG_R     (0x1 << NAU8821_PUP_DRV_INSTG_R_SFT)
#define NAU8821_PUP_DRV_INSTG_L_SFT 2
#define NAU8821_PUP_DRV_INSTG_L     (0x1 << NAU8821_PUP_DRV_INSTG_L_SFT)
#define NAU8821_PUP_MAIN_DRV_R_SFT  1
#define NAU8821_PUP_MAIN_DRV_R      (0x1 << NAU8821_PUP_MAIN_DRV_R_SFT)
#define NAU8821_PUP_MAIN_DRV_L_SFT  0
#define NAU8821_PUP_MAIN_DRV_L      0x1

/* CHARGE_PUMP (0x80) */
#define NAU8821_JAMNODCLOW          (0x1 << 10)
#define NAU8821_POWER_DOWN_DACR_SFT 9
#define NAU8821_POWER_DOWN_DACR     (0x1 << NAU8821_POWER_DOWN_DACR_SFT)
#define NAU8821_POWER_DOWN_DACL_SFT 8
#define NAU8821_POWER_DOWN_DACL     (0x1 << NAU8821_POWER_DOWN_DACL_SFT)
#define NAU8821_CHANRGE_PUMP_EN_SFT 5
#define NAU8821_CHANRGE_PUMP_EN     (0x1 << NAU8821_CHANRGE_PUMP_EN_SFT)

/* GENERAL_STATUS (0x82) */
#define NAU8821_GPIO2_IN_SFT 1
#define NAU8821_GPIO2_IN     (0x1 << NAU8821_GPIO2_IN_SFT)

#define NUVOTON_CODEC_DAI    "nau8821-hifi"

/* System Clock Source */
enum
{
    NAU8821_CLK_DIS,
    NAU8821_CLK_MCLK,
    NAU8821_CLK_INTERNAL,
    NAU8821_CLK_FLL_MCLK,
    NAU8821_CLK_FLL_BLK,
    NAU8821_CLK_FLL_FS,
};

struct nau8821
{
    struct device               *dev;
    struct regmap               *regmap;
    struct snd_soc_dapm_context *dapm;
    struct snd_soc_jack         *jack;
    //    struct work_struct jdet_work;
    int  irq;
    int  clk_id;
    int  micbias_voltage;
    int  vref_impedance;
    bool jkdet_enable;
    bool jkdet_pull_enable;
    bool jkdet_pull_up;
    int  jkdet_polarity;
    int  jack_insert_debounce;
    int  jack_eject_debounce;
    int  fs;
    int  dmic_clk_threshold;
};

typedef struct
{
    uint8_t vref_impedance;
    uint8_t micbias_voltage;
} tlkdrv_nau8821_config_t;

extern int nau8821_digital_mute(int mute, int direction);
int        nau8821_i2c_probe(void);
int        nau8821_read_status(void);

#endif
#endif /* __NAU8821_H__ */

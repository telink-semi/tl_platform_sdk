/*******************************************************************************************************
 *
 * @file    codec.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __CODEC_H__
#define __CODEC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//TSING_CODEC_CFG_0 offsetaddress : 0x0000
//TSING_CODEC_CFG_0 RegResetValue : 0x00000000
#define CODEC_ANA_ADC3_ENABLE_POS  (2U)
#define CODEC_ANA_ADC3_ENABLE_MSK  (0x1UL << CODEC_ANA_ADC3_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_ANA_ADC3_ENABLE      CODEC_ANA_ADC3_ENABLE_MSK
#define CODEC_ANA_ADC3_ENABLE_W(X) ((X) << CODEC_ANA_ADC3_ENABLE_POS)
#define CODEC_ANA_ADC2_ENABLE_POS  (3U)
#define CODEC_ANA_ADC2_ENABLE_MSK  (0x1UL << CODEC_ANA_ADC2_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_ANA_ADC2_ENABLE      CODEC_ANA_ADC2_ENABLE_MSK
#define CODEC_ANA_ADC2_ENABLE_W(X) ((X) << CODEC_ANA_ADC2_ENABLE_POS)
#define CODEC_ANA_ADC1_ENABLE_POS  (4U)
#define CODEC_ANA_ADC1_ENABLE_MSK  (0x1UL << CODEC_ANA_ADC1_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_ANA_ADC1_ENABLE      CODEC_ANA_ADC1_ENABLE_MSK
#define CODEC_ANA_ADC1_ENABLE_W(X) ((X) << CODEC_ANA_ADC1_ENABLE_POS)
#define CODEC_ANA_ADC0_ENABLE_POS  (5U)
#define CODEC_ANA_ADC0_ENABLE_MSK  (0x1UL << CODEC_ANA_ADC0_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_ANA_ADC0_ENABLE      CODEC_ANA_ADC0_ENABLE_MSK
#define CODEC_ANA_ADC0_ENABLE_W(X) ((X) << CODEC_ANA_ADC0_ENABLE_POS)
#define CODEC_DIG_DA1_ENABLE_POS   (6U)
#define CODEC_DIG_DA1_ENABLE_MSK   (0x1UL << CODEC_DIG_DA1_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_DA1_ENABLE       CODEC_DIG_DA1_ENABLE_MSK
#define CODEC_DIG_DA1_ENABLE_W(X)  ((X) << CODEC_DIG_DA1_ENABLE_POS)
#define CODEC_DIG_DA0_ENABLE_POS   (7U)
#define CODEC_DIG_DA0_ENABLE_MSK   (0x1UL << CODEC_DIG_DA0_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_DA0_ENABLE       CODEC_DIG_DA0_ENABLE_MSK
#define CODEC_DIG_DA0_ENABLE_W(X)  ((X) << CODEC_DIG_DA0_ENABLE_POS)
#define CODEC_DIG_ADC3_ENABLE_POS  (8U)
#define CODEC_DIG_ADC3_ENABLE_MSK  (0x1UL << CODEC_DIG_ADC3_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_ADC3_ENABLE      CODEC_DIG_ADC3_ENABLE_MSK
#define CODEC_DIG_ADC3_ENABLE_W(X) ((X) << CODEC_DIG_ADC3_ENABLE_POS)
#define CODEC_DIG_ADC2_ENABLE_POS  (9U)
#define CODEC_DIG_ADC2_ENABLE_MSK  (0x1UL << CODEC_DIG_ADC2_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_ADC2_ENABLE      CODEC_DIG_ADC2_ENABLE_MSK
#define CODEC_DIG_ADC2_ENABLE_W(X) ((X) << CODEC_DIG_ADC2_ENABLE_POS)
#define CODEC_DIG_ADC1_ENABLE_POS  (10U)
#define CODEC_DIG_ADC1_ENABLE_MSK  (0x1UL << CODEC_DIG_ADC1_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_ADC1_ENABLE      CODEC_DIG_ADC1_ENABLE_MSK
#define CODEC_DIG_ADC1_ENABLE_W(X) ((X) << CODEC_DIG_ADC1_ENABLE_POS)
#define CODEC_DIG_ADC0_ENABLE_POS  (11U)
#define CODEC_DIG_ADC0_ENABLE_MSK  (0x1UL << CODEC_DIG_ADC0_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_ADC0_ENABLE      CODEC_DIG_ADC0_ENABLE_MSK
#define CODEC_DIG_ADC0_ENABLE_W(X) ((X) << CODEC_DIG_ADC0_ENABLE_POS)
#define CODEC_ANA_ADC4_ENABLE_POS  (14U)
#define CODEC_ANA_ADC4_ENABLE_MSK  (0x1UL << CODEC_ANA_ADC4_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_ANA_ADC4_ENABLE      CODEC_ANA_ADC4_ENABLE_MSK
#define CODEC_ANA_ADC4_ENABLE_W(X) ((X) << CODEC_ANA_ADC4_ENABLE_POS)
#define CODEC_DIG_ADC4_ENABLE_POS  (15U)
#define CODEC_DIG_ADC4_ENABLE_MSK  (0x1UL << CODEC_DIG_ADC4_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_DIG_ADC4_ENABLE      CODEC_DIG_ADC4_ENABLE_MSK
#define CODEC_DIG_ADC4_ENABLE_W(X) ((X) << CODEC_DIG_ADC4_ENABLE_POS)
#define CODEC_ADC_DATA_SW_POS      (16U)
#define CODEC_ADC_DATA_SW_MSK      (0x1fUL << CODEC_ADC_DATA_SW_POS) /*!< Enable 1: Adc data is from DMA corresponding to 5 ADCs*/
#define CODEC_ADC_DATA_SW          CODEC_ADC_DATA_SW_MSK
#define CODEC_ADC_DATA_SW_W(X)     ((X) << CODEC_ADC_DATA_SW_POS)

//TSING_CODEC_CFG_1 offsetaddress : 0x0004
//TSING_CODEC_CFG_1 RegResetValue : 0x00004F00
#define CODEC_CG_DA1_ENABLE_POS   (0U)
#define CODEC_CG_DA1_ENABLE_MSK   (0x1UL << CODEC_CG_DA1_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_DA1_ENABLE       CODEC_CG_DA1_ENABLE_MSK
#define CODEC_CG_DA1_ENABLE_W(X)  ((X) << CODEC_CG_DA1_ENABLE_POS)
#define CODEC_CG_DA0_ENABLE_POS   (1U)
#define CODEC_CG_DA0_ENABLE_MSK   (0x1UL << CODEC_CG_DA0_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_DA0_ENABLE       CODEC_CG_DA0_ENABLE_MSK
#define CODEC_CG_DA0_ENABLE_W(X)  ((X) << CODEC_CG_DA0_ENABLE_POS)
#define CODEC_CG_ADC3_ENABLE_POS  (2U)
#define CODEC_CG_ADC3_ENABLE_MSK  (0x1UL << CODEC_CG_ADC3_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_ADC3_ENABLE      CODEC_CG_ADC3_ENABLE_MSK
#define CODEC_CG_ADC3_ENABLE_W(X) ((X) << CODEC_CG_ADC3_ENABLE_POS)
#define CODEC_CG_ADC2_ENABLE_POS  (3U)
#define CODEC_CG_ADC2_ENABLE_MSK  (0x1UL << CODEC_CG_ADC2_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_ADC2_ENABLE      CODEC_CG_ADC2_ENABLE_MSK
#define CODEC_CG_ADC2_ENABLE_W(X) ((X) << CODEC_CG_ADC2_ENABLE_POS)
#define CODEC_CG_ADC1_ENABLE_POS  (4U)
#define CODEC_CG_ADC1_ENABLE_MSK  (0x1UL << CODEC_CG_ADC1_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_ADC1_ENABLE      CODEC_CG_ADC1_ENABLE_MSK
#define CODEC_CG_ADC1_ENABLE_W(X) ((X) << CODEC_CG_ADC1_ENABLE_POS)
#define CODEC_CG_ADC0_ENABLE_POS  (5U)
#define CODEC_CG_ADC0_ENABLE_MSK  (0x1UL << CODEC_CG_ADC0_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_ADC0_ENABLE      CODEC_CG_ADC0_ENABLE_MSK
#define CODEC_CG_ADC0_ENABLE_W(X) ((X) << CODEC_CG_ADC0_ENABLE_POS)
#define CODEC_DA0_CLKINV_EN_POS   (7U)
#define CODEC_DA0_CLKINV_EN_MSK   (0x1UL << CODEC_DA0_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_DA0_CLKINV_EN       CODEC_DA0_CLKINV_EN_MSK
#define CODEC_DA0_CLKINV_EN_W(X)  ((X) << CODEC_DA0_CLKINV_EN_POS)
#define CODEC_ADC3_CLKINV_EN_POS  (8U)
#define CODEC_ADC3_CLKINV_EN_MSK  (0x1UL << CODEC_ADC3_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_ADC3_CLKINV_EN      CODEC_ADC3_CLKINV_EN_MSK
#define CODEC_ADC3_CLKINV_EN_W(X) ((X) << CODEC_ADC3_CLKINV_EN_POS)
#define CODEC_ADC2_CLKINV_EN_POS  (9U)
#define CODEC_ADC2_CLKINV_EN_MSK  (0x1UL << CODEC_ADC2_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_ADC2_CLKINV_EN      CODEC_ADC2_CLKINV_EN_MSK
#define CODEC_ADC2_CLKINV_EN_W(X) ((X) << CODEC_ADC2_CLKINV_EN_POS)
#define CODEC_ADC1_CLKINV_EN_POS  (10U)
#define CODEC_ADC1_CLKINV_EN_MSK  (0x1UL << CODEC_ADC1_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_ADC1_CLKINV_EN      CODEC_ADC1_CLKINV_EN_MSK
#define CODEC_ADC1_CLKINV_EN_W(X) ((X) << CODEC_ADC1_CLKINV_EN_POS)
#define CODEC_ADC0_CLKINV_EN_POS  (11U)
#define CODEC_ADC0_CLKINV_EN_MSK  (0x1UL << CODEC_ADC0_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_ADC0_CLKINV_EN      CODEC_ADC0_CLKINV_EN_MSK
#define CODEC_ADC0_CLKINV_EN_W(X) ((X) << CODEC_ADC0_CLKINV_EN_POS)
#define CODEC_CG_ADC4_ENABLE_POS  (13U)
#define CODEC_CG_ADC4_ENABLE_MSK  (0x1UL << CODEC_CG_ADC4_ENABLE_POS) /*!< 0 disable 1 enable*/
#define CODEC_CG_ADC4_ENABLE      CODEC_CG_ADC4_ENABLE_MSK
#define CODEC_CG_ADC4_ENABLE_W(X) ((X) << CODEC_CG_ADC4_ENABLE_POS)
#define CODEC_ADC4_CLKINV_EN_POS  (14U)
#define CODEC_ADC4_CLKINV_EN_MSK  (0x1UL << CODEC_ADC4_CLKINV_EN_POS) /*!< 0 disable 1 enable*/
#define CODEC_ADC4_CLKINV_EN      CODEC_ADC4_CLKINV_EN_MSK
#define CODEC_ADC4_CLKINV_EN_W(X) ((X) << CODEC_ADC4_CLKINV_EN_POS)

//TSING_CODEC_CFG_2 offsetaddress : 0x0008
//TSING_CODEC_CFG_2 RegResetValue : 0x000005BB
#define CODEC_ADC0_DIG_GAIN_SEL_POS  (0U)
#define CODEC_ADC0_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_ADC0_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the ADC output is amplified; <8’d187: the ADC output is narrowed;*/
#define CODEC_ADC0_DIG_GAIN_SEL      CODEC_ADC0_DIG_GAIN_SEL_MSK
#define CODEC_ADC0_DIG_GAIN_SEL_W(X) ((X) << CODEC_ADC0_DIG_GAIN_SEL_POS)
#define CODEC_ADC0_HPF_FC_POS        (8U)
#define CODEC_ADC0_HPF_FC_MSK        (0x7UL << CODEC_ADC0_HPF_FC_POS) /*!< select the cutoff frequency of the HPF;*/
#define CODEC_ADC0_HPF_FC            CODEC_ADC0_HPF_FC_MSK
#define CODEC_ADC0_HPF_FC_W(X)       ((X) << CODEC_ADC0_HPF_FC_POS)
#define CODEC_ADC0_HPF_EN_POS        (11U)
#define CODEC_ADC0_HPF_EN_MSK        (0x1UL << CODEC_ADC0_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;*/
#define CODEC_ADC0_HPF_EN            CODEC_ADC0_HPF_EN_MSK
#define CODEC_ADC0_HPF_EN_W(X)       ((X) << CODEC_ADC0_HPF_EN_POS)
#define CODEC_ADC0_COEF_SEL_POS      (12U)
#define CODEC_ADC0_COEF_SEL_MSK      (0x3UL << CODEC_ADC0_COEF_SEL_POS) /*!< select which decimating filter coefficients to be used;*/
#define CODEC_ADC0_COEF_SEL          CODEC_ADC0_COEF_SEL_MSK
#define CODEC_ADC0_COEF_SEL_W(X)     ((X) << CODEC_ADC0_COEF_SEL_POS)
#define CODEC_ADC0_RATE_SEL_POS      (14U)
#define CODEC_ADC0_RATE_SEL_MSK      (0x7UL << CODEC_ADC0_RATE_SEL_POS) /*!< select ADC output rate: pwr_mode=0, 0: 48kHz, 1: 44.1kHz, 2: 96kHz, 3: 192kHz,              4: 384kHz, 5: 768kHz, other: 48kHz pwr_mode=1, 0: 48kHz, 1: 32kHz, 2: 16kHz, 3: 8kHz,  other: 48kHz*/
#define CODEC_ADC0_RATE_SEL          CODEC_ADC0_RATE_SEL_MSK
#define CODEC_ADC0_RATE_SEL_W(X)     ((X) << CODEC_ADC0_RATE_SEL_POS)
#define CODEC_ADC0_PWR_MODE_POS      (17U)
#define CODEC_ADC0_PWR_MODE_MSK \
    (0x1UL << CODEC_ADC0_PWR_MODE_POS) /*!< 0: normal power mode, the ΣΔ modulator output rate  is fixedto 6.144MHz (5.6448MHz for 44.1kHz ADC),  the over sample rate is varying; 1: low power mode, the over sample rate is fixed to 64,  the modulator output rate is varying;*/
#define CODEC_ADC0_PWR_MODE       CODEC_ADC0_PWR_MODE_MSK
#define CODEC_ADC0_PWR_MODE_W(X)  ((X) << CODEC_ADC0_PWR_MODE_POS)
#define CODEC_ADC0_TEST_MOD_POS   (18U)
#define CODEC_ADC0_TEST_MOD_MSK   (0x1UL << CODEC_ADC0_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: adc_out={sdm_in(n), sdm_in(n-1), sdm_in(n-2), sdm_in(n-3), sdm_in(n-4), sdm_in(n-5)}, where n increases with time; 0: normal, 1: bypass CODEC ADC filters;*/
#define CODEC_ADC0_TEST_MOD       CODEC_ADC0_TEST_MOD_MSK
#define CODEC_ADC0_TEST_MOD_W(X)  ((X) << CODEC_ADC0_TEST_MOD_POS)
#define CODEC_ADC0_HPF_FC_EXT_POS (19U)
#define CODEC_ADC0_HPF_FC_EXT_MSK \
    (0x1UL                        \
     << CODEC_ADC0_HPF_FC_EXT_POS) /*!< |{adc0_hpf_fc_ext, adc0_hpf_fc[2:0]}  |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_ADC0_HPF_FC_EXT      CODEC_ADC0_HPF_FC_EXT_MSK
#define CODEC_ADC0_HPF_FC_EXT_W(X) ((X) << CODEC_ADC0_HPF_FC_EXT_POS)

//TSING_CODEC_CFG_3 offsetaddress : 0x000C
//TSING_CODEC_CFG_3 RegResetValue : 0x000005BB
#define CODEC_ADC1_DIG_GAIN_SEL_POS  (0U)
#define CODEC_ADC1_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_ADC1_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the ADC output is amplified; <8’d187: the ADC output is narrowed;*/
#define CODEC_ADC1_DIG_GAIN_SEL      CODEC_ADC1_DIG_GAIN_SEL_MSK
#define CODEC_ADC1_DIG_GAIN_SEL_W(X) ((X) << CODEC_ADC1_DIG_GAIN_SEL_POS)
#define CODEC_ADC1_HPF_FC_POS        (8U)
#define CODEC_ADC1_HPF_FC_MSK        (0x7UL << CODEC_ADC1_HPF_FC_POS) /*!< select the cutoff frequency of the HPF;*/
#define CODEC_ADC1_HPF_FC            CODEC_ADC1_HPF_FC_MSK
#define CODEC_ADC1_HPF_FC_W(X)       ((X) << CODEC_ADC1_HPF_FC_POS)
#define CODEC_ADC1_HPF_EN_POS        (11U)
#define CODEC_ADC1_HPF_EN_MSK        (0x1UL << CODEC_ADC1_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;*/
#define CODEC_ADC1_HPF_EN            CODEC_ADC1_HPF_EN_MSK
#define CODEC_ADC1_HPF_EN_W(X)       ((X) << CODEC_ADC1_HPF_EN_POS)
#define CODEC_ADC1_COEF_SEL_POS      (12U)
#define CODEC_ADC1_COEF_SEL_MSK      (0x3UL << CODEC_ADC1_COEF_SEL_POS) /*!< select which decimating filter coefficients to be used;*/
#define CODEC_ADC1_COEF_SEL          CODEC_ADC1_COEF_SEL_MSK
#define CODEC_ADC1_COEF_SEL_W(X)     ((X) << CODEC_ADC1_COEF_SEL_POS)
#define CODEC_ADC1_RATE_SEL_POS      (14U)
#define CODEC_ADC1_RATE_SEL_MSK      (0x7UL << CODEC_ADC1_RATE_SEL_POS) /*!< select ADC output rate: pwr_mode=0, 0: 48kHz, 1: 44.1kHz, 2: 96kHz, 3: 192kHz,              4: 384kHz, 5: 768kHz, other: 48kHz pwr_mode=1, 0: 48kHz, 1: 32kHz, 2: 16kHz, 3: 8kHz,  other: 48kHz*/
#define CODEC_ADC1_RATE_SEL          CODEC_ADC1_RATE_SEL_MSK
#define CODEC_ADC1_RATE_SEL_W(X)     ((X) << CODEC_ADC1_RATE_SEL_POS)
#define CODEC_ADC1_PWR_MODE_POS      (17U)
#define CODEC_ADC1_PWR_MODE_MSK \
    (0x1UL << CODEC_ADC1_PWR_MODE_POS) /*!< 0: normal power mode, the ΣΔ modulator output rate  is fixedto 6.144MHz (5.6448MHz for 44.1kHz ADC),  the over sample rate is varying; 1: low power mode, the over sample rate is fixed to 64,  the modulator output rate is varying;*/
#define CODEC_ADC1_PWR_MODE       CODEC_ADC1_PWR_MODE_MSK
#define CODEC_ADC1_PWR_MODE_W(X)  ((X) << CODEC_ADC1_PWR_MODE_POS)
#define CODEC_ADC1_TEST_MOD_POS   (18U)
#define CODEC_ADC1_TEST_MOD_MSK   (0x1UL << CODEC_ADC1_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: adc_out={sdm_in(n), sdm_in(n-1), sdm_in(n-2), sdm_in(n-3), sdm_in(n-4), sdm_in(n-5)}, where n increases with time; 0: normal, 1: bypass CODEC ADC filters;*/
#define CODEC_ADC1_TEST_MOD       CODEC_ADC1_TEST_MOD_MSK
#define CODEC_ADC1_TEST_MOD_W(X)  ((X) << CODEC_ADC1_TEST_MOD_POS)
#define CODEC_ADC1_HPF_FC_EXT_POS (19U)
#define CODEC_ADC1_HPF_FC_EXT_MSK \
    (0x1UL                        \
     << CODEC_ADC1_HPF_FC_EXT_POS) /*!< |{adc1_hpf_fc_ext, adc1_hpf_fc[2:0]}  |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_ADC1_HPF_FC_EXT      CODEC_ADC1_HPF_FC_EXT_MSK
#define CODEC_ADC1_HPF_FC_EXT_W(X) ((X) << CODEC_ADC1_HPF_FC_EXT_POS)

//TSING_CODEC_CFG_4 offsetaddress : 0x0010
//TSING_CODEC_CFG_4 RegResetValue : 0x000005BB
#define CODEC_ADC2_DIG_GAIN_SEL_POS  (0U)
#define CODEC_ADC2_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_ADC2_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the ADC output is amplified; <8’d187: the ADC output is narrowed;*/
#define CODEC_ADC2_DIG_GAIN_SEL      CODEC_ADC2_DIG_GAIN_SEL_MSK
#define CODEC_ADC2_DIG_GAIN_SEL_W(X) ((X) << CODEC_ADC2_DIG_GAIN_SEL_POS)
#define CODEC_ADC2_HPF_FC_POS        (8U)
#define CODEC_ADC2_HPF_FC_MSK        (0x7UL << CODEC_ADC2_HPF_FC_POS) /*!< select the cutoff frequency of the HPF;*/
#define CODEC_ADC2_HPF_FC            CODEC_ADC2_HPF_FC_MSK
#define CODEC_ADC2_HPF_FC_W(X)       ((X) << CODEC_ADC2_HPF_FC_POS)
#define CODEC_ADC2_HPF_EN_POS        (11U)
#define CODEC_ADC2_HPF_EN_MSK        (0x1UL << CODEC_ADC2_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;*/
#define CODEC_ADC2_HPF_EN            CODEC_ADC2_HPF_EN_MSK
#define CODEC_ADC2_HPF_EN_W(X)       ((X) << CODEC_ADC2_HPF_EN_POS)
#define CODEC_ADC2_COEF_SEL_POS      (12U)
#define CODEC_ADC2_COEF_SEL_MSK      (0x3UL << CODEC_ADC2_COEF_SEL_POS) /*!< select which decimating filter coefficients to be used;*/
#define CODEC_ADC2_COEF_SEL          CODEC_ADC2_COEF_SEL_MSK
#define CODEC_ADC2_COEF_SEL_W(X)     ((X) << CODEC_ADC2_COEF_SEL_POS)
#define CODEC_ADC2_RATE_SEL_POS      (14U)
#define CODEC_ADC2_RATE_SEL_MSK      (0x7UL << CODEC_ADC2_RATE_SEL_POS) /*!< select ADC output rate: pwr_mode=0, 0: 48kHz, 1: 44.1kHz, 2: 96kHz, 3: 192kHz,              4: 384kHz, 5: 768kHz, other: 48kHz pwr_mode=1, 0: 48kHz, 1: 32kHz, 2: 16kHz, 3: 8kHz,  other: 48kHz*/
#define CODEC_ADC2_RATE_SEL          CODEC_ADC2_RATE_SEL_MSK
#define CODEC_ADC2_RATE_SEL_W(X)     ((X) << CODEC_ADC2_RATE_SEL_POS)
#define CODEC_ADC2_PWR_MODE_POS      (17U)
#define CODEC_ADC2_PWR_MODE_MSK \
    (0x1UL << CODEC_ADC2_PWR_MODE_POS) /*!< 0: normal power mode, the ΣΔ modulator output rate  is fixedto 6.144MHz (5.6448MHz for 44.1kHz ADC),  the over sample rate is varying; 1: low power mode, the over sample rate is fixed to 64,  the modulator output rate is varying;*/
#define CODEC_ADC2_PWR_MODE       CODEC_ADC2_PWR_MODE_MSK
#define CODEC_ADC2_PWR_MODE_W(X)  ((X) << CODEC_ADC2_PWR_MODE_POS)
#define CODEC_ADC2_TEST_MOD_POS   (18U)
#define CODEC_ADC2_TEST_MOD_MSK   (0x1UL << CODEC_ADC2_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: adc_out={sdm_in(n), sdm_in(n-1), sdm_in(n-2), sdm_in(n-3), sdm_in(n-4), sdm_in(n-5)}, where n increases with time; 0: normal, 1: bypass CODEC ADC filters;*/
#define CODEC_ADC2_TEST_MOD       CODEC_ADC2_TEST_MOD_MSK
#define CODEC_ADC2_TEST_MOD_W(X)  ((X) << CODEC_ADC2_TEST_MOD_POS)
#define CODEC_ADC2_HPF_FC_EXT_POS (19U)
#define CODEC_ADC2_HPF_FC_EXT_MSK \
    (0x1UL                        \
     << CODEC_ADC2_HPF_FC_EXT_POS) /*!< |{adc2_hpf_fc_ext, adc2_hpf_fc[2:0]}  |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_ADC2_HPF_FC_EXT      CODEC_ADC2_HPF_FC_EXT_MSK
#define CODEC_ADC2_HPF_FC_EXT_W(X) ((X) << CODEC_ADC2_HPF_FC_EXT_POS)

//TSING_CODEC_CFG_5 offsetaddress : 0x0014
//TSING_CODEC_CFG_5 RegResetValue : 0x000005BB
#define CODEC_ADC3_DIG_GAIN_SEL_POS  (0U)
#define CODEC_ADC3_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_ADC3_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the ADC output is amplified; <8’d187: the ADC output is narrowed;*/
#define CODEC_ADC3_DIG_GAIN_SEL      CODEC_ADC3_DIG_GAIN_SEL_MSK
#define CODEC_ADC3_DIG_GAIN_SEL_W(X) ((X) << CODEC_ADC3_DIG_GAIN_SEL_POS)
#define CODEC_ADC3_HPF_FC_POS        (8U)
#define CODEC_ADC3_HPF_FC_MSK        (0x7UL << CODEC_ADC3_HPF_FC_POS) /*!< select the cutoff frequency of the HPF;*/
#define CODEC_ADC3_HPF_FC            CODEC_ADC3_HPF_FC_MSK
#define CODEC_ADC3_HPF_FC_W(X)       ((X) << CODEC_ADC3_HPF_FC_POS)
#define CODEC_ADC3_HPF_EN_POS        (11U)
#define CODEC_ADC3_HPF_EN_MSK        (0x1UL << CODEC_ADC3_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;*/
#define CODEC_ADC3_HPF_EN            CODEC_ADC3_HPF_EN_MSK
#define CODEC_ADC3_HPF_EN_W(X)       ((X) << CODEC_ADC3_HPF_EN_POS)
#define CODEC_ADC3_COEF_SEL_POS      (12U)
#define CODEC_ADC3_COEF_SEL_MSK      (0x3UL << CODEC_ADC3_COEF_SEL_POS) /*!< select which decimating filter coefficients to be used;*/
#define CODEC_ADC3_COEF_SEL          CODEC_ADC3_COEF_SEL_MSK
#define CODEC_ADC3_COEF_SEL_W(X)     ((X) << CODEC_ADC3_COEF_SEL_POS)
#define CODEC_ADC3_RATE_SEL_POS      (14U)
#define CODEC_ADC3_RATE_SEL_MSK      (0x7UL << CODEC_ADC3_RATE_SEL_POS) /*!< select ADC output rate: pwr_mode=0, 0: 48kHz, 1: 44.1kHz, 2: 96kHz, 3: 192kHz,              4: 384kHz, 5: 768kHz, other: 48kHz pwr_mode=1, 0: 48kHz, 1: 32kHz, 2: 16kHz, 3: 8kHz,  other: 48kHz*/
#define CODEC_ADC3_RATE_SEL          CODEC_ADC3_RATE_SEL_MSK
#define CODEC_ADC3_RATE_SEL_W(X)     ((X) << CODEC_ADC3_RATE_SEL_POS)
#define CODEC_ADC3_PWR_MODE_POS      (17U)
#define CODEC_ADC3_PWR_MODE_MSK \
    (0x1UL << CODEC_ADC3_PWR_MODE_POS) /*!< 0: normal power mode, the ΣΔ modulator output rate  is fixedto 6.144MHz (5.6448MHz for 44.1kHz ADC),  the over sample rate is varying; 1: low power mode, the over sample rate is fixed to 64,  the modulator output rate is varying;*/
#define CODEC_ADC3_PWR_MODE       CODEC_ADC3_PWR_MODE_MSK
#define CODEC_ADC3_PWR_MODE_W(X)  ((X) << CODEC_ADC3_PWR_MODE_POS)
#define CODEC_ADC3_TEST_MOD_POS   (18U)
#define CODEC_ADC3_TEST_MOD_MSK   (0x1UL << CODEC_ADC3_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: adc_out={sdm_in(n), sdm_in(n-1), sdm_in(n-2), sdm_in(n-3), sdm_in(n-4), sdm_in(n-5)}, where n increases with time; 0: normal, 1: bypass CODEC ADC filters;*/
#define CODEC_ADC3_TEST_MOD       CODEC_ADC3_TEST_MOD_MSK
#define CODEC_ADC3_TEST_MOD_W(X)  ((X) << CODEC_ADC3_TEST_MOD_POS)
#define CODEC_ADC3_HPF_FC_EXT_POS (19U)
#define CODEC_ADC3_HPF_FC_EXT_MSK \
    (0x1UL                        \
     << CODEC_ADC3_HPF_FC_EXT_POS) /*!< |{adc3_hpf_fc_ext, adc3_hpf_fc[2:0]}  |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_ADC3_HPF_FC_EXT      CODEC_ADC3_HPF_FC_EXT_MSK
#define CODEC_ADC3_HPF_FC_EXT_W(X) ((X) << CODEC_ADC3_HPF_FC_EXT_POS)

//TSING_CODEC_CFG_6 offsetaddress : 0x0018
//TSING_CODEC_CFG_6 RegResetValue : 0x000EBB02
#define CODEC_DA0_MUTE_WIN_POS  (0U)
#define CODEC_DA0_MUTE_WIN_MSK  (0xfUL << CODEC_DA0_MUTE_WIN_POS) /*!< |   mute_win      |    number of PCM samples | |     4’d0       |          2048            | |4’d1 ~ 4’d15   |    mute_win × 4096       |*/
#define CODEC_DA0_MUTE_WIN      CODEC_DA0_MUTE_WIN_MSK
#define CODEC_DA0_MUTE_WIN_W(X) ((X) << CODEC_DA0_MUTE_WIN_POS)
#define CODEC_DA0_MUTE_THRE_POS (4U)
#define CODEC_DA0_MUTE_THRE_MSK \
    (0xfUL                      \
     << CODEC_DA0_MUTE_THRE_POS) /*!< |mute_thre  |  DAC code              |  DAC code (dB) | |  4’d0     |      1                 |      0         | |  4’d1     |      4                 |      12        | |  4’d2     |      8                 |      18        | |  4’d3     |      12                |      21.625    | |  4’d4     |      16                |      24.125    | |  4’d5     |      20                |      26        | |  4’d6     |      24                |      27.625    | |  4’d7     |      28                |      29        | |  4’d8     |      32                |      30.125    | |  4’d9     |      36                |      31.125    | |  4’d10    |      40                |      32        | |  4’d11    |      44                |      32.875    | |  4’d12    |      48                |      33.625    | |  4’d13    |      52                |      34.375    | |  4’d14    |      56                |      35        | |  4’d15    |      -1(disable mute)  |       /        |*/
#define CODEC_DA0_MUTE_THRE         CODEC_DA0_MUTE_THRE_MSK
#define CODEC_DA0_MUTE_THRE_W(X)    ((X) << CODEC_DA0_MUTE_THRE_POS)
#define CODEC_DA0_DIG_GAIN_SEL_POS  (8U)
#define CODEC_DA0_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_DA0_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the DAC output is amplified; <8’d187: the DAC output is narrowed;*/
#define CODEC_DA0_DIG_GAIN_SEL      CODEC_DA0_DIG_GAIN_SEL_MSK
#define CODEC_DA0_DIG_GAIN_SEL_W(X) ((X) << CODEC_DA0_DIG_GAIN_SEL_POS)
#define CODEC_DA0_DEM_SEL_POS       (16U)
#define CODEC_DA0_DEM_SEL_MSK       (0x1UL << CODEC_DA0_DEM_SEL_POS) /*!< select order of vector-based mismatch-shaping; 0: 1s order DEM, 1: 2s order DEM;*/
#define CODEC_DA0_DEM_SEL           CODEC_DA0_DEM_SEL_MSK
#define CODEC_DA0_DEM_SEL_W(X)      ((X) << CODEC_DA0_DEM_SEL_POS)
#define CODEC_DA0_MAX_DBFS_SEL_POS  (17U)
#define CODEC_DA0_MAX_DBFS_SEL_MSK  (0x7UL << CODEC_DA0_MAX_DBFS_SEL_POS) /*!< maximum DAC output amplitude related to full scale in dB; 0 ~ 7 → -1dBFS ~ -8dBFS;*/
#define CODEC_DA0_MAX_DBFS_SEL      CODEC_DA0_MAX_DBFS_SEL_MSK
#define CODEC_DA0_MAX_DBFS_SEL_W(X) ((X) << CODEC_DA0_MAX_DBFS_SEL_POS)
#define CODEC_DA0_COEF_SEL_POS      (20U)
#define CODEC_DA0_COEF_SEL_MSK      (0x3UL << CODEC_DA0_COEF_SEL_POS) /*!< select which interpolating filter coefficients to be used;*/
#define CODEC_DA0_COEF_SEL          CODEC_DA0_COEF_SEL_MSK
#define CODEC_DA0_COEF_SEL_W(X)     ((X) << CODEC_DA0_COEF_SEL_POS)
#define CODEC_DA0_RATE_SEL_POS      (22U)
#define CODEC_DA0_RATE_SEL_MSK      (0x7UL << CODEC_DA0_RATE_SEL_POS) /*!< */
#define CODEC_DA0_RATE_SEL          CODEC_DA0_RATE_SEL_MSK
#define CODEC_DA0_RATE_SEL_W(X)     ((X) << CODEC_DA0_RATE_SEL_POS)
#define CODEC_DA0_PWR_MODE_POS      (25U)
#define CODEC_DA0_PWR_MODE_MSK \
    (0x1UL                     \
     << CODEC_DA0_PWR_MODE_POS) /*!< |codec_6p144_clk |pwr_mode |rate_sel | ADC Output Rate | Oversampling Ratio | |6.144 MHz | 0 | 0 | 48 kHz | 128 | |5.6448MHz | 0 | 1 | 44.1 kHz | 128 | |6.144 MHz | 0 | 2 | 96 kHz | 64 | |6.144 MHz | 0 | 3 | 192 kHz | 32 | |6.144 MHz | 0 | 4 | 384 kHz | 16 | |6.144 MHz | 0 | 5 | 768 kHz | 8 | |6.144 MHz | 0 | Others | 48 kHz | 128 | |3.072 MHz | 1 | 0 | 48 kHz | 64 | |2.048 MHz | 1 | 1 | 32 kHz | 64 | |1.024 MHz | 1 | 2 | 16 kHz | 64 | |0.512 MHz | 1 | 3 | 8 kHz | 64 | |3.072 MHz | 1 | Others | 48 kHz | 64 |*/
#define CODEC_DA0_PWR_MODE      CODEC_DA0_PWR_MODE_MSK
#define CODEC_DA0_PWR_MODE_W(X) ((X) << CODEC_DA0_PWR_MODE_POS)
#define CODEC_DA0_TEST_MOD_POS  (26U)
#define CODEC_DA0_TEST_MOD_MSK  (0x1UL << CODEC_DA0_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: dem_pa=anc_pa[15:0], dem_pb=anc_pb[17:8], dem_pc=anc_pb[7:0]; Note: The anc_ra and anc_rb port signals in the test mode have become high level*/
#define CODEC_DA0_TEST_MOD      CODEC_DA0_TEST_MOD_MSK
#define CODEC_DA0_TEST_MOD_W(X) ((X) << CODEC_DA0_TEST_MOD_POS)

//TSING_CODEC_CFG_7 offsetaddress : 0x001C
//TSING_CODEC_CFG_7 RegResetValue : 0x00000000
#define CODEC_DA0_PCM_OFFSET_POS  (0U)
#define CODEC_DA0_PCM_OFFSET_MSK  (0xffffffffUL << CODEC_DA0_PCM_OFFSET_POS) /*!< */
#define CODEC_DA0_PCM_OFFSET      CODEC_DA0_PCM_OFFSET_MSK
#define CODEC_DA0_PCM_OFFSET_W(X) ((X) << CODEC_DA0_PCM_OFFSET_POS)

//TSING_CODEC_CFG_8 offsetaddress : 0x0020
//TSING_CODEC_CFG_8 RegResetValue : 0x0000BB02
#define CODEC_DA1_MUTE_WIN_POS  (0U)
#define CODEC_DA1_MUTE_WIN_MSK  (0xfUL << CODEC_DA1_MUTE_WIN_POS) /*!< |   mute_win      |    number of PCM samples | |     4’d0       |          2048            | |4’d1 ~ 4’d15   |    mute_win × 4096       |*/
#define CODEC_DA1_MUTE_WIN      CODEC_DA1_MUTE_WIN_MSK
#define CODEC_DA1_MUTE_WIN_W(X) ((X) << CODEC_DA1_MUTE_WIN_POS)
#define CODEC_DA1_MUTE_THRE_POS (4U)
#define CODEC_DA1_MUTE_THRE_MSK \
    (0xfUL                      \
     << CODEC_DA1_MUTE_THRE_POS) /*!< |mute_thre  |  DAC code              |  DAC code (dB) | |  4’d0     |      1                 |      0         | |  4’d1     |      4                 |      12        | |  4’d2     |      8                 |      18        | |  4’d3     |      12                |      21.625    | |  4’d4     |      16                |      24.125    | |  4’d5     |      20                |      26        | |  4’d6     |      24                |      27.625    | |  4’d7     |      28                |      29        | |  4’d8     |      32                |      30.125    | |  4’d9     |      36                |      31.125    | |  4’d10    |      40                |      32        | |  4’d11    |      44                |      32.875    | |  4’d12    |      48                |      33.625    | |  4’d13    |      52                |      34.375    | |  4’d14    |      56                |      35        | |  4’d15    |      -1(disable mute)  |       /        |*/
#define CODEC_DA1_MUTE_THRE         CODEC_DA1_MUTE_THRE_MSK
#define CODEC_DA1_MUTE_THRE_W(X)    ((X) << CODEC_DA1_MUTE_THRE_POS)
#define CODEC_DA1_DIG_GAIN_SEL_POS  (8U)
#define CODEC_DA1_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_DA1_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the DAC output is amplified; <8’d187: the DAC output is narrowed;*/
#define CODEC_DA1_DIG_GAIN_SEL      CODEC_DA1_DIG_GAIN_SEL_MSK
#define CODEC_DA1_DIG_GAIN_SEL_W(X) ((X) << CODEC_DA1_DIG_GAIN_SEL_POS)
#define CODEC_DA1_DEM_SEL_POS       (16U)
#define CODEC_DA1_DEM_SEL_MSK       (0x1UL << CODEC_DA1_DEM_SEL_POS) /*!< select order of vector-based mismatch-shaping; 0: 1s order DEM, 1: 2s order DEM;*/
#define CODEC_DA1_DEM_SEL           CODEC_DA1_DEM_SEL_MSK
#define CODEC_DA1_DEM_SEL_W(X)      ((X) << CODEC_DA1_DEM_SEL_POS)
#define CODEC_DA1_MAX_DBFS_SEL_POS  (17U)
#define CODEC_DA1_MAX_DBFS_SEL_MSK  (0x7UL << CODEC_DA1_MAX_DBFS_SEL_POS) /*!< maximum DAC output amplitude related to full scale in dB; 0 ~ 7 → -1dBFS ~ -8dBFS;*/
#define CODEC_DA1_MAX_DBFS_SEL      CODEC_DA1_MAX_DBFS_SEL_MSK
#define CODEC_DA1_MAX_DBFS_SEL_W(X) ((X) << CODEC_DA1_MAX_DBFS_SEL_POS)
#define CODEC_DA1_COEF_SEL_POS      (20U)
#define CODEC_DA1_COEF_SEL_MSK      (0x3UL << CODEC_DA1_COEF_SEL_POS) /*!< select which interpolating filter coefficients to be used;*/
#define CODEC_DA1_COEF_SEL          CODEC_DA1_COEF_SEL_MSK
#define CODEC_DA1_COEF_SEL_W(X)     ((X) << CODEC_DA1_COEF_SEL_POS)
#define CODEC_DA1_RATE_SEL_POS      (22U)
#define CODEC_DA1_RATE_SEL_MSK      (0x7UL << CODEC_DA1_RATE_SEL_POS) /*!< */
#define CODEC_DA1_RATE_SEL          CODEC_DA1_RATE_SEL_MSK
#define CODEC_DA1_RATE_SEL_W(X)     ((X) << CODEC_DA1_RATE_SEL_POS)
#define CODEC_DA1_PWR_MODE_POS      (25U)
#define CODEC_DA1_PWR_MODE_MSK \
    (0x1UL                     \
     << CODEC_DA1_PWR_MODE_POS) /*!< |Main Clock clk |pwr_mode |rate_sel | ADC Output Rate | Oversampling Ratio | |6.144 MHz | 0 | 0 | 48 kHz | 128 | |5.6448MHz | 0 | 1 | 44.1 kHz | 128 | |6.144 MHz | 0 | 2 | 96 kHz | 64 | |6.144 MHz | 0 | 3 | 192 kHz | 32 | |6.144 MHz | 0 | 4 | 384 kHz | 16 | |6.144 MHz | 0 | 5 | 768 kHz | 8 | |6.144 MHz | 0 | Others | 48 kHz | 128 | |3.072 MHz | 1 | 0 | 48 kHz | 64 | |2.048 MHz | 1 | 1 | 32 kHz | 64 | |1.024 MHz | 1 | 2 | 16 kHz | 64 | |0.512 MHz | 1 | 3 | 8 kHz | 64 | |3.072 MHz | 1 | Others | 48 kHz | 64 |*/
#define CODEC_DA1_PWR_MODE      CODEC_DA1_PWR_MODE_MSK
#define CODEC_DA1_PWR_MODE_W(X) ((X) << CODEC_DA1_PWR_MODE_POS)
#define CODEC_DA1_TEST_MOD_POS  (26U)
#define CODEC_DA1_TEST_MOD_MSK  (0x1UL << CODEC_DA1_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: dem_pa=anc_pa[15:0], dem_pb=anc_pb[17:8], dem_pc=anc_pb[7:0]; Note: The anc_ra and anc_rb port signals in the test mode have become high level*/
#define CODEC_DA1_TEST_MOD      CODEC_DA1_TEST_MOD_MSK
#define CODEC_DA1_TEST_MOD_W(X) ((X) << CODEC_DA1_TEST_MOD_POS)

//TSING_CODEC_CFG_9 offsetaddress : 0x0024
//TSING_CODEC_CFG_9 RegResetValue : 0x00000000
#define CODEC_DA1_PCM_OFFSET_POS  (0U)
#define CODEC_DA1_PCM_OFFSET_MSK  (0xffffffffUL << CODEC_DA1_PCM_OFFSET_POS) /*!< */
#define CODEC_DA1_PCM_OFFSET      CODEC_DA1_PCM_OFFSET_MSK
#define CODEC_DA1_PCM_OFFSET_W(X) ((X) << CODEC_DA1_PCM_OFFSET_POS)

//TSING_CODEC_CFG_10 offsetaddress : 0x0028
//TSING_CODEC_CFG_10 RegResetValue : 0x000005BB
#define CODEC_ADC4_DIG_GAIN_SEL_POS  (0U)
#define CODEC_ADC4_DIG_GAIN_SEL_MSK  (0xffUL << CODEC_ADC4_DIG_GAIN_SEL_POS) /*!< select digital gain, 8’d187: the gain is 1; >8’d187: the ADC output is amplified; <8’d187: the ADC output is narrowed;*/
#define CODEC_ADC4_DIG_GAIN_SEL      CODEC_ADC4_DIG_GAIN_SEL_MSK
#define CODEC_ADC4_DIG_GAIN_SEL_W(X) ((X) << CODEC_ADC4_DIG_GAIN_SEL_POS)
#define CODEC_ADC4_HPF_FC_POS        (8U)
#define CODEC_ADC4_HPF_FC_MSK        (0x7UL << CODEC_ADC4_HPF_FC_POS) /*!< select the cutoff frequency of the HPF;*/
#define CODEC_ADC4_HPF_FC            CODEC_ADC4_HPF_FC_MSK
#define CODEC_ADC4_HPF_FC_W(X)       ((X) << CODEC_ADC4_HPF_FC_POS)
#define CODEC_ADC4_HPF_EN_POS        (11U)
#define CODEC_ADC4_HPF_EN_MSK        (0x1UL << CODEC_ADC4_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;*/
#define CODEC_ADC4_HPF_EN            CODEC_ADC4_HPF_EN_MSK
#define CODEC_ADC4_HPF_EN_W(X)       ((X) << CODEC_ADC4_HPF_EN_POS)
#define CODEC_ADC4_COEF_SEL_POS      (12U)
#define CODEC_ADC4_COEF_SEL_MSK      (0x3UL << CODEC_ADC4_COEF_SEL_POS) /*!< select which decimating filter coefficients to be used;*/
#define CODEC_ADC4_COEF_SEL          CODEC_ADC4_COEF_SEL_MSK
#define CODEC_ADC4_COEF_SEL_W(X)     ((X) << CODEC_ADC4_COEF_SEL_POS)
#define CODEC_ADC4_RATE_SEL_POS      (14U)
#define CODEC_ADC4_RATE_SEL_MSK      (0x7UL << CODEC_ADC4_RATE_SEL_POS) /*!< select ADC output rate: pwr_mode=0, 0: 48kHz, 1: 44.1kHz, 2: 96kHz, 3: 192kHz,              4: 384kHz, 5: 768kHz, other: 48kHz pwr_mode=1, 0: 48kHz, 1: 32kHz, 2: 16kHz, 3: 8kHz,  other: 48kHz*/
#define CODEC_ADC4_RATE_SEL          CODEC_ADC4_RATE_SEL_MSK
#define CODEC_ADC4_RATE_SEL_W(X)     ((X) << CODEC_ADC4_RATE_SEL_POS)
#define CODEC_ADC4_PWR_MODE_POS      (17U)
#define CODEC_ADC4_PWR_MODE_MSK \
    (0x1UL << CODEC_ADC4_PWR_MODE_POS) /*!< 0: normal power mode, the ΣΔ modulator output rate  is fixedto 6.144MHz (5.6448MHz for 44.1kHz ADC),  the over sample rate is varying; 1: low power mode, the over sample rate is fixed to 64,  the modulator output rate is varying;*/
#define CODEC_ADC4_PWR_MODE       CODEC_ADC4_PWR_MODE_MSK
#define CODEC_ADC4_PWR_MODE_W(X)  ((X) << CODEC_ADC4_PWR_MODE_POS)
#define CODEC_ADC4_TEST_MOD_POS   (18U)
#define CODEC_ADC4_TEST_MOD_MSK   (0x1UL << CODEC_ADC4_TEST_MOD_POS) /*!< When the test mode is enabled, when it is 1, the input of the module is directly used as the output; Corresponding relationship: adc_out={sdm_in(n), sdm_in(n-1), sdm_in(n-2), sdm_in(n-3), sdm_in(n-4), sdm_in(n-5)}, where n increases with time; 0: normal, 1: bypass CODEC ADC filters;*/
#define CODEC_ADC4_TEST_MOD       CODEC_ADC4_TEST_MOD_MSK
#define CODEC_ADC4_TEST_MOD_W(X)  ((X) << CODEC_ADC4_TEST_MOD_POS)
#define CODEC_ADC4_HPF_FC_EXT_POS (19U)
#define CODEC_ADC4_HPF_FC_EXT_MSK \
    (0x1UL                        \
     << CODEC_ADC4_HPF_FC_EXT_POS) /*!< |{adc4_hpf_fc_ext, adc4_hpf_fc[2:0]}  |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_ADC4_HPF_FC_EXT      CODEC_ADC4_HPF_FC_EXT_MSK
#define CODEC_ADC4_HPF_FC_EXT_W(X) ((X) << CODEC_ADC4_HPF_FC_EXT_POS)

//TSING_CODEC_CFG_11 offsetaddress : 0x002C
//TSING_CODEC_CFG_11 RegResetValue : 0x000CBC72
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_POS   (0U)
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_MSK   (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_POS) /*!< AUDIO CODEC Recording Channel 1 PGA gain control, see gain map for details*/
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1       CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_W(X)  ((X) << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_POS     (4U)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_POS) /*!< AUDIO CODEC PGA current selection control terminal of recording channel 1 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1         CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_POS  (8U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_POS) /*!< AUDIO CODEC Recording Channel 1 single-ended signal input is enabled. 1: Enable, the signal enters from INN, and the INP is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_POS  (9U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_POS) /*!< AUDIO CODEC Recording Channel 1 single-ended signal input is enabled. 1: Enable, the signal enters from INP, and the INN is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_POS  (10U)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_POS) /*!< AUDIO CODEC Recording Channel 1 differential signal input is enabled. 1: Enable; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1      CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_POS     (11U)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_POS) /*!< AUDIO CODEC ADC current selection control terminal of recording channel 1 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1         CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_POS        (15U)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_POS) /*!< AUDIO CODEC DEM function enable control of recording channel 1 1: DEM function enable; 0: DEM function disabled*/
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1            CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_POS       (16U)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_MSK       (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_POS) /*!< AUDIO CODEC ADC quantizer DLY time selection terminal of recording channel 1 0,48ns; 1,30n*/
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1           CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_W(X)      ((X) << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_POS        (17U)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_POS) /*!< AUDIO CODEC ADC quantizer 1bit or 4bit selector of recording channel 1 0,4bit; 1,1bit*/
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1            CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_POS    (18U)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_POS) /*!< AUDIO CODEC INT_RST control terminal of ADC of recording channel 1 (note the timing)*/
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1        CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH1_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_POS    (19U)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_POS) /*!< AUDIO CODEC CH1&#39;s quantizer output sampling clock forward and inverse phase control. 1: CLK_ADC inverse; 0: CLK_ADC.*/
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1        CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH1_POS)
#define CODEC_AUDIO_CODEC_REGBAK_CH1_POS             (20U)
#define CODEC_AUDIO_CODEC_REGBAK_CH1_MSK             (0x1UL << CODEC_AUDIO_CODEC_REGBAK_CH1_POS) /*!< */
#define CODEC_AUDIO_CODEC_REGBAK_CH1                 CODEC_AUDIO_CODEC_REGBAK_CH1_MSK
#define CODEC_AUDIO_CODEC_REGBAK_CH1_W(X)            ((X) << CODEC_AUDIO_CODEC_REGBAK_CH1_POS)

//TSING_CODEC_CFG_12 offsetaddress : 0x0030
//TSING_CODEC_CFG_12 RegResetValue : 0x000CBC72
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_POS   (0U)
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_MSK   (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_POS) /*!< AUDIO CODEC Recording Channel 2 PGA gain control, see gain map for details*/
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2       CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_W(X)  ((X) << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_POS     (4U)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_POS) /*!< AUDIO CODEC PGA current selection control terminal of recording channel 2 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2         CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_POS  (8U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_POS) /*!< AUDIO CODEC Recording Channel 2 single-ended signal input enable. 1: Enable, the signal enters from INN, and the INP is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_POS  (9U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_POS) /*!< AUDIO CODEC Recording Channel 2 single-ended signal input enable. 1: Enable, the signal enters from INP, and the INN is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_POS  (10U)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_POS) /*!< AUDIO CODEC Recording Channel 2 differential signal input is enabled. 1: Enable; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2      CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_POS     (11U)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_POS) /*!< AUDIO CODEC ADC current selection control terminal of recording channel 2 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2         CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_POS        (15U)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_POS) /*!< AUDIO CODEC DEM function enable control of recording channel 2 1: DEM function enable; 0: DEM function disabled*/
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2            CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_POS       (16U)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_MSK       (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_POS) /*!< AUDIO CODEC ADC quantizer DLY time selection terminal of AUDIO CODEC recording channel 2 0,48ns; 1,30n*/
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2           CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_W(X)      ((X) << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_POS        (17U)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_POS) /*!< AUDIO CODEC ADC quantizer 1bit or 4bit selector of recording channel 2 0,4bit; 1,1bit*/
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2            CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_POS    (18U)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_POS) /*!< AUDIO CODEC INT_RST control terminal of ADC of recording channel 2 (note the timing)*/
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2        CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH2_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_POS    (19U)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_POS) /*!< AUDIO CODEC CH2&#39;s quantizer output sampling clock forward and inverse phase control. 1: CLK_ADC inverse; 0: CLK_ADC.*/
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2        CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH2_POS)
#define CODEC_AUDIO_CODEC_REGBAK_CH2_POS             (20U)
#define CODEC_AUDIO_CODEC_REGBAK_CH2_MSK             (0x1UL << CODEC_AUDIO_CODEC_REGBAK_CH2_POS) /*!< */
#define CODEC_AUDIO_CODEC_REGBAK_CH2                 CODEC_AUDIO_CODEC_REGBAK_CH2_MSK
#define CODEC_AUDIO_CODEC_REGBAK_CH2_W(X)            ((X) << CODEC_AUDIO_CODEC_REGBAK_CH2_POS)

//TSING_CODEC_CFG_13 offsetaddress : 0x0034
//TSING_CODEC_CFG_13 RegResetValue : 0x000CBC72
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_POS   (0U)
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_MSK   (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_POS) /*!< AUDIO CODEC Recording Channel 3 PGA gain control, see gain map for details*/
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3       CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_W(X)  ((X) << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_POS     (4U)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_POS) /*!< AUDIO CODEC PGA current selection control terminal of recording channel 3 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3         CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_POS  (8U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_POS) /*!< AUDIO CODEC Recording Channel 3 single-ended signal input is enabled. 1: Enable, the signal enters from INN, and the INP is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_POS  (9U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_POS) /*!< AUDIO CODEC Recording Channel 3 single-ended signal input is enabled. 1: Enable, the signal enters from INP, and the INN is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3      CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_POS  (10U)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_POS) /*!< AUDIO CODEC Recording Channel 3 differential signal input is enabled. 1: Enable; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3      CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_W(X) ((X) << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_POS     (11U)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_MSK     (0xfUL << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_POS) /*!< AUDIO CODEC ADC current selection control terminal of recording channel 3 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3         CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_POS        (15U)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_POS) /*!< AUDIO CODEC DEM function enable control of recording channel 3 1: DEM function enable; 0: DEM function disabled*/
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3            CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_POS       (16U)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_MSK       (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_POS) /*!< AUDIO CODEC ADC quantizer DLY time selection terminal of AUDIO CODEC recording channel 3 0,48ns; 1,30n*/
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3           CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_W(X)      ((X) << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_POS        (17U)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_POS) /*!< AUDIO CODEC ADC quantizer 1bit or 4bit selector of recording channel 3 0,4bit; 1,1bit*/
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3            CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_POS    (18U)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_POS) /*!< AUDIO CODEC INT_RST control terminal of ADC of recording channel 3 (note the timing)*/
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3        CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH3_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_POS    (19U)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_MSK    (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_POS) /*!< AUDIO CODEC CH3&#39;s quantizer output sampling clock forward and inverse phase control. 1: CLK_ADC inverse; 0: CLK_ADC.*/
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3        CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH3_POS)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_POS             (20U)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_MSK             (0x1UL << CODEC_AUDIO_CODEC_REGBAK_CH3_POS) /*!< */
#define CODEC_AUDIO_CODEC_REGBAK_CH3                 CODEC_AUDIO_CODEC_REGBAK_CH3_MSK
#define CODEC_AUDIO_CODEC_REGBAK_CH3_W(X)            ((X) << CODEC_AUDIO_CODEC_REGBAK_CH3_POS)

//TSING_CODEC_CFG_14 offsetaddress : 0x0038
//TSING_CODEC_CFG_14 RegResetValue : 0x000CBC72
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_POS           (0U)
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_MSK           (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_POS) /*!< AUDIO CODEC Recording Channel 4 PGA gain control, see gain map for details*/
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4               CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_W(X)          ((X) << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_POS             (4U)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_MSK             (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_POS) /*!< AUDIO CODEC PGA current selection control terminal of recording channel 4 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4                 CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_W(X)            ((X) << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_POS          (8U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_POS) /*!< AUDIO CODEC Recording Channel 4 single-ended signal input is enabled. 1: Enable, the signal enters from INN, and the INP is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4              CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_POS          (9U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_POS) /*!< AUDIO CODEC Recording Channel 4 single-ended signal input is enabled. 1: Enable, the signal enters from INP, and the INN is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4              CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_POS          (10U)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_POS) /*!< AUDIO CODEC Recording Channel 4 differential signal input is enabled. 1: Enable; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4              CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_POS             (11U)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_MSK             (0xfUL << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_POS) /*!< AUDIO CODEC ADC current selection control terminal of recording channel 4 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4                 CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_W(X)            ((X) << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_POS                (15U)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_MSK                (0x1UL << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_POS) /*!< AUDIO CODEC DEM function enable control of recording channel 4 1: DEM function enable; 0: DEM function disabled*/
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4                    CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_W(X)               ((X) << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_POS               (16U)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_MSK               (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_POS) /*!< AUDIO CODEC ADC quantizer DLY time selection terminal of AUDIO CODEC recording channel 4 0,48ns; 1,30n*/
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4                   CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_W(X)              ((X) << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_POS                (17U)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_MSK                (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_POS) /*!< AUDIO CODEC ADC quantizer 1bit or 4bit selector of recording channel 4 0,4bit; 1,1bit*/
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4                    CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_W(X)               ((X) << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_POS            (18U)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_MSK            (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_POS) /*!< AUDIO CODEC INT_RST control terminal of ADC of recording channel 4 (note the timing)*/
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4                CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_W(X)           ((X) << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH4_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_POS            (19U)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_MSK            (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_POS) /*!< AUDIO CODEC CH4&#39;s quantizer output sampling clock forward and inverse phase control. 1: CLK_ADC inverse; 0: CLK_ADC.*/
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4                CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_W(X)           ((X) << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH4_POS)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_POS  (20U)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_MSK  (0x1UL << CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_POS) /*!< */
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14      CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_MSK
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_W(X) ((X) << CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_14_POS)

//TSING_CODEC_CFG_15 offsetaddress : 0x003C
//TSING_CODEC_CFG_15 RegResetValue : 0x000CBC72
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_POS           (0U)
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_MSK           (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_POS) /*!< AUDIO CODEC Recording Channel 5 PGA gain control, see gain map for details*/
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5               CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_W(X)          ((X) << CODEC_AUDIO_CODEC_REC_PGA_GAIN_ST1_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_POS             (4U)
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_MSK             (0xfUL << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_POS) /*!< AUDIO CODEC PGA current selection control terminal of recording channel 5 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5                 CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_W(X)            ((X) << CODEC_AUDIO_CODEC_REC_PGA_IB_SEL_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_POS          (8U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_POS) /*!< AUDIO CODEC Recording Channel 5 single-ended signal input is enabled. 1: Enable, the signal enters from INN, and the INP is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5              CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_N_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_POS          (9U)
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_POS) /*!< AUDIO CODEC Recording Channel 5 single-ended signal input is enabled. 1: Enable, the signal enters from INP, and the INN is grounded internally; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5              CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_SE_MODE_P_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_POS          (10U)
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_MSK          (0x1UL << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_POS) /*!< AUDIO CODEC Recording Channel 5 differential signal input is enabled. 1: Enable; 0: Turn off.*/
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5              CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_PGA_DIFF_MODE_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_POS             (11U)
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_MSK             (0xfUL << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_POS) /*!< AUDIO CODEC ADC current selection control terminal of recording channel 5 0000 0.125uA 0111 2uA 1111 4uA*/
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5                 CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_W(X)            ((X) << CODEC_AUDIO_CODEC_REC_ADC_IB_SEL_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_POS                (15U)
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_MSK                (0x1UL << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_POS) /*!< AUDIO CODEC DEM function enable control of recording channel 5 1: DEM function enable; 0: DEM function disabled*/
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5                    CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_W(X)               ((X) << CODEC_AUDIO_CODEC_REC_ENP_DEM_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_POS               (16U)
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_MSK               (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_POS) /*!< AUDIO CODEC ADC quantizer DLY time selection terminal of AUDIO CODEC recording channel 5 0,48ns; 1,30n*/
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5                   CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_W(X)              ((X) << CODEC_AUDIO_CODEC_REC_ADC_QDLY_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_POS                (17U)
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_MSK                (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_POS) /*!< AUDIO CODEC ADC quantizer 1bit or 4bit selector of AUDIO CODEC recording channel 5 0,4bit; 1,1bit*/
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5                    CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_W(X)               ((X) << CODEC_AUDIO_CODEC_REC_ADC_Q1B_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_POS            (18U)
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_MSK            (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_POS) /*!< AUDIO CODEC INT_RST control terminal of ADC of recording channel 5 (note the timing)*/
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5                CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_W(X)           ((X) << CODEC_AUDIO_CODEC_REC_ADC_INT_RST_CH5_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_POS            (19U)
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_MSK            (0x1UL << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_POS) /*!< AUDIO CODEC CH5&#39;s quantizer output sampling clock forward and inverse phase control. 1: CLK_ADC inverse; 0: CLK_ADC.*/
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5                CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_W(X)           ((X) << CODEC_AUDIO_CODEC_REC_ADC_CLK_INV_CH5_POS)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_POS  (20U)
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_MSK  (0x1UL << CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_POS) /*!< */
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15      CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_MSK
#define CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_W(X) ((X) << CODEC_AUDIO_CODEC_REGBAK_CH3_TSING_CODEC_CFG_15_POS)

//TSING_CODEC_CFG_16 offsetaddress : 0x0040
//TSING_CODEC_CFG_16 RegResetValue : 0x005B7024
#define CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_POS    (0U)
#define CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_MSK    (0x7UL << CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM        CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_MSK
#define CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_LDO_VOL_TRIM_POS)
#define CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_POS    (3U)
#define CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_MSK    (0x7UL << CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM        CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_MSK
#define CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_ADC_LDO_TRIM_POS)
#define CODEC_AUDIO_CODEC_REC_LOWP_MODE_POS       (6U)
#define CODEC_AUDIO_CODEC_REC_LOWP_MODE_MSK       (0x1UL << CODEC_AUDIO_CODEC_REC_LOWP_MODE_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_LOWP_MODE           CODEC_AUDIO_CODEC_REC_LOWP_MODE_MSK
#define CODEC_AUDIO_CODEC_REC_LOWP_MODE_W(X)      ((X) << CODEC_AUDIO_CODEC_REC_LOWP_MODE_POS)
#define CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_POS  (7U)
#define CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_MSK  (0x1UL << CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE      CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_MSK
#define CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_W(X) ((X) << CODEC_AUDIO_CODEC_REC_VREF_LOWP_MODE_POS)
#define CODEC_AUDIO_CODEC_REC_VREFP18_ENP_POS     (8U)
#define CODEC_AUDIO_CODEC_REC_VREFP18_ENP_MSK     (0x1UL << CODEC_AUDIO_CODEC_REC_VREFP18_ENP_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_VREFP18_ENP         CODEC_AUDIO_CODEC_REC_VREFP18_ENP_MSK
#define CODEC_AUDIO_CODEC_REC_VREFP18_ENP_W(X)    ((X) << CODEC_AUDIO_CODEC_REC_VREFP18_ENP_POS)
#define CODEC_AUDIO_CODEC_REC_VCOM_ENP_POS        (9U)
#define CODEC_AUDIO_CODEC_REC_VCOM_ENP_MSK        (0x1UL << CODEC_AUDIO_CODEC_REC_VCOM_ENP_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_VCOM_ENP            CODEC_AUDIO_CODEC_REC_VCOM_ENP_MSK
#define CODEC_AUDIO_CODEC_REC_VCOM_ENP_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_VCOM_ENP_POS)
#define CODEC_AUDIO_CODEC_REC_TEST_SEL_POS        (10U)
#define CODEC_AUDIO_CODEC_REC_TEST_SEL_MSK        (0x3UL << CODEC_AUDIO_CODEC_REC_TEST_SEL_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_TEST_SEL            CODEC_AUDIO_CODEC_REC_TEST_SEL_MSK
#define CODEC_AUDIO_CODEC_REC_TEST_SEL_W(X)       ((X) << CODEC_AUDIO_CODEC_REC_TEST_SEL_POS)
#define CODEC_AUDIO_CODEC_REC_IB_SEL_POS          (12U)
#define CODEC_AUDIO_CODEC_REC_IB_SEL_MSK          (0xfUL << CODEC_AUDIO_CODEC_REC_IB_SEL_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_IB_SEL              CODEC_AUDIO_CODEC_REC_IB_SEL_MSK
#define CODEC_AUDIO_CODEC_REC_IB_SEL_W(X)         ((X) << CODEC_AUDIO_CODEC_REC_IB_SEL_POS)
#define CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_POS    (16U)
#define CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_MSK    (0x7UL << CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_SELI_VREF1P8        CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_MSK
#define CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_W(X)   ((X) << CODEC_AUDIO_CODEC_REC_SELI_VREF1P8_POS)
#define CODEC_AUDIO_CODEC_REC_SELI_VCOM_POS       (19U)
#define CODEC_AUDIO_CODEC_REC_SELI_VCOM_MSK       (0x7UL << CODEC_AUDIO_CODEC_REC_SELI_VCOM_POS) /*!< */
#define CODEC_AUDIO_CODEC_REC_SELI_VCOM           CODEC_AUDIO_CODEC_REC_SELI_VCOM_MSK
#define CODEC_AUDIO_CODEC_REC_SELI_VCOM_W(X)      ((X) << CODEC_AUDIO_CODEC_REC_SELI_VCOM_POS)
#define CODEC_CDC_VREF_MODE_0P8_POS               (22U)
#define CODEC_CDC_VREF_MODE_0P8_MSK               (0x1UL << CODEC_CDC_VREF_MODE_0P8_POS) /*!< */
#define CODEC_CDC_VREF_MODE_0P8                   CODEC_CDC_VREF_MODE_0P8_MSK
#define CODEC_CDC_VREF_MODE_0P8_W(X)              ((X) << CODEC_CDC_VREF_MODE_0P8_POS)
#define CODEC_CDC_VREF_FAST_STARTUP_0P8_POS       (23U)
#define CODEC_CDC_VREF_FAST_STARTUP_0P8_MSK       (0x1UL << CODEC_CDC_VREF_FAST_STARTUP_0P8_POS) /*!< */
#define CODEC_CDC_VREF_FAST_STARTUP_0P8           CODEC_CDC_VREF_FAST_STARTUP_0P8_MSK
#define CODEC_CDC_VREF_FAST_STARTUP_0P8_W(X)      ((X) << CODEC_CDC_VREF_FAST_STARTUP_0P8_POS)
#define CODEC_CDC_ENP_VREF_0P8_POS                (24U)
#define CODEC_CDC_ENP_VREF_0P8_MSK                (0x1UL << CODEC_CDC_ENP_VREF_0P8_POS) /*!< */
#define CODEC_CDC_ENP_VREF_0P8                    CODEC_CDC_ENP_VREF_0P8_MSK
#define CODEC_CDC_ENP_VREF_0P8_W(X)               ((X) << CODEC_CDC_ENP_VREF_0P8_POS)
#define CODEC_CTL_R_0P8_POS                       (25U)
#define CODEC_CTL_R_0P8_MSK                       (0x3UL << CODEC_CTL_R_0P8_POS) /*!< Power-on time control for slow start of VREF 00: 1.2s 01: 0.6s 10: 0.3s 11: 0.15s*/
#define CODEC_CTL_R_0P8                           CODEC_CTL_R_0P8_MSK
#define CODEC_CTL_R_0P8_W(X)                      ((X) << CODEC_CTL_R_0P8_POS)

//TSING_CODEC_CFG_17 offsetaddress : 0x0044
//TSING_CODEC_CFG_17 RegResetValue : 0x0000000F
#define CODEC_IDLE_LIMIT_POS  (0U)
#define CODEC_IDLE_LIMIT_MSK  (0xfUL << CODEC_IDLE_LIMIT_POS) /*!< After the AHB Slave interface IDLE duration reaches idle_limit * 16, if ahb_lp_en = 1, the AHB Slave interface clock is gated*/
#define CODEC_IDLE_LIMIT      CODEC_IDLE_LIMIT_MSK
#define CODEC_IDLE_LIMIT_W(X) ((X) << CODEC_IDLE_LIMIT_POS)
#define CODEC_AHB_LP_EN_POS   (4U)
#define CODEC_AHB_LP_EN_MSK   (0x1UL << CODEC_AHB_LP_EN_POS) /*!< 0:disable 1:enable*/
#define CODEC_AHB_LP_EN       CODEC_AHB_LP_EN_MSK
#define CODEC_AHB_LP_EN_W(X)  ((X) << CODEC_AHB_LP_EN_POS)

//TSING_CODEC_CFG_18 offsetaddress : 0x0048
//TSING_CODEC_CFG_18 RegResetValue : 0x00000000
#define CODEC_DA1_SOFT_RESET_POS    (0U)
#define CODEC_DA1_SOFT_RESET_MSK    (0x1UL << CODEC_DA1_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DA1_SOFT_RESET        CODEC_DA1_SOFT_RESET_MSK
#define CODEC_DA1_SOFT_RESET_W(X)   ((X) << CODEC_DA1_SOFT_RESET_POS)
#define CODEC_DA0_SOFT_RESET_POS    (1U)
#define CODEC_DA0_SOFT_RESET_MSK    (0x1UL << CODEC_DA0_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DA0_SOFT_RESET        CODEC_DA0_SOFT_RESET_MSK
#define CODEC_DA0_SOFT_RESET_W(X)   ((X) << CODEC_DA0_SOFT_RESET_POS)
#define CODEC_ADC3_SOFT_RESET_POS   (2U)
#define CODEC_ADC3_SOFT_RESET_MSK   (0x1UL << CODEC_ADC3_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADC3_SOFT_RESET       CODEC_ADC3_SOFT_RESET_MSK
#define CODEC_ADC3_SOFT_RESET_W(X)  ((X) << CODEC_ADC3_SOFT_RESET_POS)
#define CODEC_ADC2_SOFT_RESET_POS   (3U)
#define CODEC_ADC2_SOFT_RESET_MSK   (0x1UL << CODEC_ADC2_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADC2_SOFT_RESET       CODEC_ADC2_SOFT_RESET_MSK
#define CODEC_ADC2_SOFT_RESET_W(X)  ((X) << CODEC_ADC2_SOFT_RESET_POS)
#define CODEC_ADC1_SOFT_RESET_POS   (4U)
#define CODEC_ADC1_SOFT_RESET_MSK   (0x1UL << CODEC_ADC1_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADC1_SOFT_RESET       CODEC_ADC1_SOFT_RESET_MSK
#define CODEC_ADC1_SOFT_RESET_W(X)  ((X) << CODEC_ADC1_SOFT_RESET_POS)
#define CODEC_ADC0_SOFT_RESET_POS   (5U)
#define CODEC_ADC0_SOFT_RESET_MSK   (0x1UL << CODEC_ADC0_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADC0_SOFT_RESET       CODEC_ADC0_SOFT_RESET_MSK
#define CODEC_ADC0_SOFT_RESET_W(X)  ((X) << CODEC_ADC0_SOFT_RESET_POS)
#define CODEC_DMIC_SOFT_RESET_POS   (6U)
#define CODEC_DMIC_SOFT_RESET_MSK   (0x1UL << CODEC_DMIC_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DMIC_SOFT_RESET       CODEC_DMIC_SOFT_RESET_MSK
#define CODEC_DMIC_SOFT_RESET_W(X)  ((X) << CODEC_DMIC_SOFT_RESET_POS)
#define CODEC_DAC_SOFT_RESET_POS    (7U)
#define CODEC_DAC_SOFT_RESET_MSK    (0x1UL << CODEC_DAC_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DAC_SOFT_RESET        CODEC_DAC_SOFT_RESET_MSK
#define CODEC_DAC_SOFT_RESET_W(X)   ((X) << CODEC_DAC_SOFT_RESET_POS)
#define CODEC_ADPL_SOFT_RESET_POS   (8U)
#define CODEC_ADPL_SOFT_RESET_MSK   (0x1UL << CODEC_ADPL_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADPL_SOFT_RESET       CODEC_ADPL_SOFT_RESET_MSK
#define CODEC_ADPL_SOFT_RESET_W(X)  ((X) << CODEC_ADPL_SOFT_RESET_POS)
#define CODEC_6P144_SOFT_RESET_POS  (9U)
#define CODEC_6P144_SOFT_RESET_MSK  (0x1UL << CODEC_6P144_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_6P144_SOFT_RESET      CODEC_6P144_SOFT_RESET_MSK
#define CODEC_6P144_SOFT_RESET_W(X) ((X) << CODEC_6P144_SOFT_RESET_POS)
#define CODEC_ADC4_SOFT_RESET_POS   (10U)
#define CODEC_ADC4_SOFT_RESET_MSK   (0x1UL << CODEC_ADC4_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_ADC4_SOFT_RESET       CODEC_ADC4_SOFT_RESET_MSK
#define CODEC_ADC4_SOFT_RESET_W(X)  ((X) << CODEC_ADC4_SOFT_RESET_POS)
#define CODEC_DMIC1_SOFT_RESET_POS  (11U)
#define CODEC_DMIC1_SOFT_RESET_MSK  (0x1UL << CODEC_DMIC1_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DMIC1_SOFT_RESET      CODEC_DMIC1_SOFT_RESET_MSK
#define CODEC_DMIC1_SOFT_RESET_W(X) ((X) << CODEC_DMIC1_SOFT_RESET_POS)
#define CODEC_DMIC0_SOFT_RESET_POS  (12U)
#define CODEC_DMIC0_SOFT_RESET_MSK  (0x1UL << CODEC_DMIC0_SOFT_RESET_POS) /*!< 0: No reset; 1: Reset*/
#define CODEC_DMIC0_SOFT_RESET      CODEC_DMIC0_SOFT_RESET_MSK
#define CODEC_DMIC0_SOFT_RESET_W(X) ((X) << CODEC_DMIC0_SOFT_RESET_POS)

//TSING_CODEC_CFG_19 offsetaddress : 0x004C
//TSING_CODEC_CFG_19 RegResetValue : 0x00000000
#define CODEC_ADC_DMA_CH1_ENABLE_POS      (0U)
#define CODEC_ADC_DMA_CH1_ENABLE_MSK      (0x3UL << CODEC_ADC_DMA_CH1_ENABLE_POS) /*!< &quot;[1]-dma_ch1 read DMIC1 FIFO enabled, 0: not enabled; 1: enable [0]-dma_ch1 read DMIC0 FIFO enabled, 0: not enabled; 1: enable Only configurations as 2&#39;h00, 2&#39;h01 and 2&#39;b11&quot;*/
#define CODEC_ADC_DMA_CH1_ENABLE          CODEC_ADC_DMA_CH1_ENABLE_MSK
#define CODEC_ADC_DMA_CH1_ENABLE_W(X)     ((X) << CODEC_ADC_DMA_CH1_ENABLE_POS)
#define CODEC_ADC_DMA_CH0_ENABLE_3_0_POS  (2U)
#define CODEC_ADC_DMA_CH0_ENABLE_3_0_MSK  (0xfUL << CODEC_ADC_DMA_CH0_ENABLE_3_0_POS) /*!< &quot;[5]-dma_ch0 read ADC3 FIFO enabled, 0: not enabled; 1: Enable [4]-dma_ch0 read ADC2 FIFO enabled, 0: not enabled; 1: Enable [3]-dma_ch0 read ADC1 FIFO enabled, 0: not enabled; 1: Enable [2]-dma_ch0 read ADC0 FIFO enabled, 0: not enabled; 1: Enable&quot;*/
#define CODEC_ADC_DMA_CH0_ENABLE_3_0      CODEC_ADC_DMA_CH0_ENABLE_3_0_MSK
#define CODEC_ADC_DMA_CH0_ENABLE_3_0_W(X) ((X) << CODEC_ADC_DMA_CH0_ENABLE_3_0_POS)
#define CODEC_DAC_DMA_CH_ENABLE_POS       (6U)
#define CODEC_DAC_DMA_CH_ENABLE_MSK       (0x3UL << CODEC_DAC_DMA_CH_ENABLE_POS) /*!< &quot;[1]-dma_ch Write DAC1 FIFO enabled, 0: Not enabled; 1: Enable [0]-dma_ch Write DAC0 FIFO enabled, 0: Not enabled; 1: Enable&quot;*/
#define CODEC_DAC_DMA_CH_ENABLE           CODEC_DAC_DMA_CH_ENABLE_MSK
#define CODEC_DAC_DMA_CH_ENABLE_W(X)      ((X) << CODEC_DAC_DMA_CH_ENABLE_POS)
#define CODEC_ADC_DMA_CH0_ENABLE_4_POS    (8U)
#define CODEC_ADC_DMA_CH0_ENABLE_4_MSK    (0x1UL << CODEC_ADC_DMA_CH0_ENABLE_4_POS) /*!< &quot;[8]-dma_ch0 reads ADC4 FIFO enabled, 0: not enabled; 1: enabled&quot;*/
#define CODEC_ADC_DMA_CH0_ENABLE_4        CODEC_ADC_DMA_CH0_ENABLE_4_MSK
#define CODEC_ADC_DMA_CH0_ENABLE_4_W(X)   ((X) << CODEC_ADC_DMA_CH0_ENABLE_4_POS)
#define CODEC_DAC0_PC_DMA_ENABLE_POS      (9U)
#define CODEC_DAC0_PC_DMA_ENABLE_MSK      (0x7UL << CODEC_DAC0_PC_DMA_ENABLE_POS) /*!< 1:dac0_pc_fifo 2:fb_fade_out_fifo 3:ff_fade_out 4:fb_fade_out,ff_fadeout 5:fb_fade_out,ff_fadeout,dac0_pc_fifo,0*/
#define CODEC_DAC0_PC_DMA_ENABLE          CODEC_DAC0_PC_DMA_ENABLE_MSK
#define CODEC_DAC0_PC_DMA_ENABLE_W(X)     ((X) << CODEC_DAC0_PC_DMA_ENABLE_POS)
#define CODEC_FADE_OUT_SEL_POS            (12U)
#define CODEC_FADE_OUT_SEL_MSK            (0x1UL << CODEC_FADE_OUT_SEL_POS) /*!< 0:ar_fade_out_data 1:al_fade_out_data*/
#define CODEC_FADE_OUT_SEL                CODEC_FADE_OUT_SEL_MSK
#define CODEC_FADE_OUT_SEL_W(X)           ((X) << CODEC_FADE_OUT_SEL_POS)

//TSING_CODEC_ADC_DMA0_DATA offsetaddress : 0x0050
//TSING_CODEC_ADC_DMA0_DATA RegResetValue : 0x00000000
#define CODEC_ADC_DMA_CH0_RDATA_POS  (0U)
#define CODEC_ADC_DMA_CH0_RDATA_MSK  (0xffffffffUL << CODEC_ADC_DMA_CH0_RDATA_POS) /*!< ADC DMA CH0 data*/
#define CODEC_ADC_DMA_CH0_RDATA      CODEC_ADC_DMA_CH0_RDATA_MSK
#define CODEC_ADC_DMA_CH0_RDATA_W(X) ((X) << CODEC_ADC_DMA_CH0_RDATA_POS)

//TSING_CODEC_ADC_DMA1_DATA offsetaddress : 0x0054
//TSING_CODEC_ADC_DMA1_DATA RegResetValue : 0x00000000
#define CODEC_ADC_DMA_CH1_RDATA_POS  (0U)
#define CODEC_ADC_DMA_CH1_RDATA_MSK  (0xffffffffUL << CODEC_ADC_DMA_CH1_RDATA_POS) /*!< ADC DMA CH1 data*/
#define CODEC_ADC_DMA_CH1_RDATA      CODEC_ADC_DMA_CH1_RDATA_MSK
#define CODEC_ADC_DMA_CH1_RDATA_W(X) ((X) << CODEC_ADC_DMA_CH1_RDATA_POS)

//TSING_CODEC_DAC0_DMA_DATA offsetaddress : 0x0058
//TSING_CODEC_DAC0_DMA_DATA RegResetValue : 0x00000000
#define CODEC_DAC0_DMA_CH_WDATA_POS  (0U)
#define CODEC_DAC0_DMA_CH_WDATA_MSK  (0xffffffffUL << CODEC_DAC0_DMA_CH_WDATA_POS) /*!< DAC DMA CH0 data*/
#define CODEC_DAC0_DMA_CH_WDATA      CODEC_DAC0_DMA_CH_WDATA_MSK
#define CODEC_DAC0_DMA_CH_WDATA_W(X) ((X) << CODEC_DAC0_DMA_CH_WDATA_POS)

//TSING_CODEC_DAC1_DMA_DATA offsetaddress : 0x005C
//TSING_CODEC_DAC1_DMA_DATA RegResetValue : 0x00000000
#define CODEC_DAC1_DMA_CH_WDATA_POS  (0U)
#define CODEC_DAC1_DMA_CH_WDATA_MSK  (0xffffffffUL << CODEC_DAC1_DMA_CH_WDATA_POS) /*!< DAC DMA CH1 data*/
#define CODEC_DAC1_DMA_CH_WDATA      CODEC_DAC1_DMA_CH_WDATA_MSK
#define CODEC_DAC1_DMA_CH_WDATA_W(X) ((X) << CODEC_DAC1_DMA_CH_WDATA_POS)

//TSING_CODEC_DAC0_PA_DATA offsetaddress : 0x0060
//TSING_CODEC_DAC0_PA_DATA RegResetValue : 0x00000000
#define CODEC_DAC0_PA_WDATA_POS  (0U)
#define CODEC_DAC0_PA_WDATA_MSK  (0xffffffffUL << CODEC_DAC0_PA_WDATA_POS) /*!< DAC0 PA data*/
#define CODEC_DAC0_PA_WDATA      CODEC_DAC0_PA_WDATA_MSK
#define CODEC_DAC0_PA_WDATA_W(X) ((X) << CODEC_DAC0_PA_WDATA_POS)

//TSING_CODEC_DAC0_PB_DATA offsetaddress : 0x0064
//TSING_CODEC_DAC0_PB_DATA RegResetValue : 0x00000000
#define CODEC_DAC0_PB_WDATA_POS  (0U)
#define CODEC_DAC0_PB_WDATA_MSK  (0xffffffffUL << CODEC_DAC0_PB_WDATA_POS) /*!< DAC0 PB data*/
#define CODEC_DAC0_PB_WDATA      CODEC_DAC0_PB_WDATA_MSK
#define CODEC_DAC0_PB_WDATA_W(X) ((X) << CODEC_DAC0_PB_WDATA_POS)

//TSING_CODEC_DAC0_PC_DATA offsetaddress : 0x0068
//TSING_CODEC_DAC0_PC_DATA RegResetValue : 0x00000000
#define CODEC_DAC0_PC_RDATA_POS  (0U)
#define CODEC_DAC0_PC_RDATA_MSK  (0xffffffffUL << CODEC_DAC0_PC_RDATA_POS) /*!< DAC0 PC data*/
#define CODEC_DAC0_PC_RDATA      CODEC_DAC0_PC_RDATA_MSK
#define CODEC_DAC0_PC_RDATA_W(X) ((X) << CODEC_DAC0_PC_RDATA_POS)

//TSING_CODEC_DAC1_PA_DATA offsetaddress : 0x006C
//TSING_CODEC_DAC1_PA_DATA RegResetValue : 0x00000000
#define CODEC_DAC1_PA_WDATA_POS  (0U)
#define CODEC_DAC1_PA_WDATA_MSK  (0xffffffffUL << CODEC_DAC1_PA_WDATA_POS) /*!< DAC1 PA data*/
#define CODEC_DAC1_PA_WDATA      CODEC_DAC1_PA_WDATA_MSK
#define CODEC_DAC1_PA_WDATA_W(X) ((X) << CODEC_DAC1_PA_WDATA_POS)

//TSING_CODEC_DAC1_PB_DATA offsetaddress : 0x0070
//TSING_CODEC_DAC1_PB_DATA RegResetValue : 0x00000000
#define CODEC_DAC1_PB_WDATA_POS  (0U)
#define CODEC_DAC1_PB_WDATA_MSK  (0xffffffffUL << CODEC_DAC1_PB_WDATA_POS) /*!< DAC1 PB data*/
#define CODEC_DAC1_PB_WDATA      CODEC_DAC1_PB_WDATA_MSK
#define CODEC_DAC1_PB_WDATA_W(X) ((X) << CODEC_DAC1_PB_WDATA_POS)

//TSING_CODEC_DAC1_PC_DATA offsetaddress : 0x0074
//TSING_CODEC_DAC1_PC_DATA RegResetValue : 0x00000000
#define CODEC_DAC1_PC_RDATA_POS  (0U)
#define CODEC_DAC1_PC_RDATA_MSK  (0xffffffffUL << CODEC_DAC1_PC_RDATA_POS) /*!< DAC1 PC data*/
#define CODEC_DAC1_PC_RDATA      CODEC_DAC1_PC_RDATA_MSK
#define CODEC_DAC1_PC_RDATA_W(X) ((X) << CODEC_DAC1_PC_RDATA_POS)

//TSING_CODEC_FIFO_STATUS0 offsetaddress : 0x0078
//TSING_CODEC_FIFO_STATUS0 RegResetValue : 0x00000303
#define CODEC_ADC1_CH0_FIFO_EMPTY_POS     (0U)
#define CODEC_ADC1_CH0_FIFO_EMPTY_MSK     (0x1UL << CODEC_ADC1_CH0_FIFO_EMPTY_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_EMPTY         CODEC_ADC1_CH0_FIFO_EMPTY_MSK
#define CODEC_ADC1_CH0_FIFO_EMPTY_W(X)    ((X) << CODEC_ADC1_CH0_FIFO_EMPTY_POS)
#define CODEC_ADC1_CH0_FIFO_AE_POS        (1U)
#define CODEC_ADC1_CH0_FIFO_AE_MSK        (0x1UL << CODEC_ADC1_CH0_FIFO_AE_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_AE            CODEC_ADC1_CH0_FIFO_AE_MSK
#define CODEC_ADC1_CH0_FIFO_AE_W(X)       ((X) << CODEC_ADC1_CH0_FIFO_AE_POS)
#define CODEC_ADC1_CH0_FIFO_HF_POS        (2U)
#define CODEC_ADC1_CH0_FIFO_HF_MSK        (0x1UL << CODEC_ADC1_CH0_FIFO_HF_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_HF            CODEC_ADC1_CH0_FIFO_HF_MSK
#define CODEC_ADC1_CH0_FIFO_HF_W(X)       ((X) << CODEC_ADC1_CH0_FIFO_HF_POS)
#define CODEC_ADC1_CH0_FIFO_AF_POS        (3U)
#define CODEC_ADC1_CH0_FIFO_AF_MSK        (0x1UL << CODEC_ADC1_CH0_FIFO_AF_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_AF            CODEC_ADC1_CH0_FIFO_AF_MSK
#define CODEC_ADC1_CH0_FIFO_AF_W(X)       ((X) << CODEC_ADC1_CH0_FIFO_AF_POS)
#define CODEC_ADC1_CH0_FIFO_FULL_POS      (4U)
#define CODEC_ADC1_CH0_FIFO_FULL_MSK      (0x1UL << CODEC_ADC1_CH0_FIFO_FULL_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_FULL          CODEC_ADC1_CH0_FIFO_FULL_MSK
#define CODEC_ADC1_CH0_FIFO_FULL_W(X)     ((X) << CODEC_ADC1_CH0_FIFO_FULL_POS)
#define CODEC_ADC1_CH0_FIFO_RD_ERROR_POS  (5U)
#define CODEC_ADC1_CH0_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_ADC1_CH0_FIFO_RD_ERROR_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_RD_ERROR      CODEC_ADC1_CH0_FIFO_RD_ERROR_MSK
#define CODEC_ADC1_CH0_FIFO_RD_ERROR_W(X) ((X) << CODEC_ADC1_CH0_FIFO_RD_ERROR_POS)
#define CODEC_ADC1_CH0_FIFO_WR_ERROR_POS  (6U)
#define CODEC_ADC1_CH0_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_ADC1_CH0_FIFO_WR_ERROR_POS) /*!< ch0(adc123) adc1  fifo status*/
#define CODEC_ADC1_CH0_FIFO_WR_ERROR      CODEC_ADC1_CH0_FIFO_WR_ERROR_MSK
#define CODEC_ADC1_CH0_FIFO_WR_ERROR_W(X) ((X) << CODEC_ADC1_CH0_FIFO_WR_ERROR_POS)
#define CODEC_ADC4_CH1_FIFO_EMPTY_POS     (8U)
#define CODEC_ADC4_CH1_FIFO_EMPTY_MSK     (0x1UL << CODEC_ADC4_CH1_FIFO_EMPTY_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_EMPTY         CODEC_ADC4_CH1_FIFO_EMPTY_MSK
#define CODEC_ADC4_CH1_FIFO_EMPTY_W(X)    ((X) << CODEC_ADC4_CH1_FIFO_EMPTY_POS)
#define CODEC_ADC4_CH1_FIFO_AE_POS        (9U)
#define CODEC_ADC4_CH1_FIFO_AE_MSK        (0x1UL << CODEC_ADC4_CH1_FIFO_AE_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_AE            CODEC_ADC4_CH1_FIFO_AE_MSK
#define CODEC_ADC4_CH1_FIFO_AE_W(X)       ((X) << CODEC_ADC4_CH1_FIFO_AE_POS)
#define CODEC_ADC4_CH1_FIFO_HF_POS        (10U)
#define CODEC_ADC4_CH1_FIFO_HF_MSK        (0x1UL << CODEC_ADC4_CH1_FIFO_HF_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_HF            CODEC_ADC4_CH1_FIFO_HF_MSK
#define CODEC_ADC4_CH1_FIFO_HF_W(X)       ((X) << CODEC_ADC4_CH1_FIFO_HF_POS)
#define CODEC_ADC4_CH1_FIFO_AF_POS        (11U)
#define CODEC_ADC4_CH1_FIFO_AF_MSK        (0x1UL << CODEC_ADC4_CH1_FIFO_AF_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_AF            CODEC_ADC4_CH1_FIFO_AF_MSK
#define CODEC_ADC4_CH1_FIFO_AF_W(X)       ((X) << CODEC_ADC4_CH1_FIFO_AF_POS)
#define CODEC_ADC4_CH1_FIFO_FULL_POS      (12U)
#define CODEC_ADC4_CH1_FIFO_FULL_MSK      (0x1UL << CODEC_ADC4_CH1_FIFO_FULL_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_FULL          CODEC_ADC4_CH1_FIFO_FULL_MSK
#define CODEC_ADC4_CH1_FIFO_FULL_W(X)     ((X) << CODEC_ADC4_CH1_FIFO_FULL_POS)
#define CODEC_ADC4_CH1_FIFO_RD_ERROR_POS  (13U)
#define CODEC_ADC4_CH1_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_ADC4_CH1_FIFO_RD_ERROR_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_RD_ERROR      CODEC_ADC4_CH1_FIFO_RD_ERROR_MSK
#define CODEC_ADC4_CH1_FIFO_RD_ERROR_W(X) ((X) << CODEC_ADC4_CH1_FIFO_RD_ERROR_POS)
#define CODEC_ADC4_CH1_FIFO_WR_ERROR_POS  (14U)
#define CODEC_ADC4_CH1_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_ADC4_CH1_FIFO_WR_ERROR_POS) /*!< ch1(adc4)adc4 fifo status*/
#define CODEC_ADC4_CH1_FIFO_WR_ERROR      CODEC_ADC4_CH1_FIFO_WR_ERROR_MSK
#define CODEC_ADC4_CH1_FIFO_WR_ERROR_W(X) ((X) << CODEC_ADC4_CH1_FIFO_WR_ERROR_POS)
#define CODEC_DAC_FIFO_EMPTY_POS          (16U)
#define CODEC_DAC_FIFO_EMPTY_MSK          (0x1UL << CODEC_DAC_FIFO_EMPTY_POS) /*!< */
#define CODEC_DAC_FIFO_EMPTY              CODEC_DAC_FIFO_EMPTY_MSK
#define CODEC_DAC_FIFO_EMPTY_W(X)         ((X) << CODEC_DAC_FIFO_EMPTY_POS)
#define CODEC_DAC_FIFO_AE_POS             (17U)
#define CODEC_DAC_FIFO_AE_MSK             (0x1UL << CODEC_DAC_FIFO_AE_POS) /*!< */
#define CODEC_DAC_FIFO_AE                 CODEC_DAC_FIFO_AE_MSK
#define CODEC_DAC_FIFO_AE_W(X)            ((X) << CODEC_DAC_FIFO_AE_POS)
#define CODEC_DAC_FIFO_HF_POS             (18U)
#define CODEC_DAC_FIFO_HF_MSK             (0x1UL << CODEC_DAC_FIFO_HF_POS) /*!< */
#define CODEC_DAC_FIFO_HF                 CODEC_DAC_FIFO_HF_MSK
#define CODEC_DAC_FIFO_HF_W(X)            ((X) << CODEC_DAC_FIFO_HF_POS)
#define CODEC_DAC_FIFO_AF_POS             (19U)
#define CODEC_DAC_FIFO_AF_MSK             (0x1UL << CODEC_DAC_FIFO_AF_POS) /*!< */
#define CODEC_DAC_FIFO_AF                 CODEC_DAC_FIFO_AF_MSK
#define CODEC_DAC_FIFO_AF_W(X)            ((X) << CODEC_DAC_FIFO_AF_POS)
#define CODEC_DAC_FIFO_FULL_POS           (20U)
#define CODEC_DAC_FIFO_FULL_MSK           (0x1UL << CODEC_DAC_FIFO_FULL_POS) /*!< */
#define CODEC_DAC_FIFO_FULL               CODEC_DAC_FIFO_FULL_MSK
#define CODEC_DAC_FIFO_FULL_W(X)          ((X) << CODEC_DAC_FIFO_FULL_POS)
#define CODEC_DAC_FIFO_RD_ERROR_POS       (21U)
#define CODEC_DAC_FIFO_RD_ERROR_MSK       (0x1UL << CODEC_DAC_FIFO_RD_ERROR_POS) /*!< */
#define CODEC_DAC_FIFO_RD_ERROR           CODEC_DAC_FIFO_RD_ERROR_MSK
#define CODEC_DAC_FIFO_RD_ERROR_W(X)      ((X) << CODEC_DAC_FIFO_RD_ERROR_POS)
#define CODEC_DAC_FIFO_WR_ERROR_POS       (22U)
#define CODEC_DAC_FIFO_WR_ERROR_MSK       (0x1UL << CODEC_DAC_FIFO_WR_ERROR_POS) /*!< */
#define CODEC_DAC_FIFO_WR_ERROR           CODEC_DAC_FIFO_WR_ERROR_MSK
#define CODEC_DAC_FIFO_WR_ERROR_W(X)      ((X) << CODEC_DAC_FIFO_WR_ERROR_POS)
#define CODEC_ADC2_CH0_FIFO_RD_ERROR_POS  (24U)
#define CODEC_ADC2_CH0_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_ADC2_CH0_FIFO_RD_ERROR_POS) /*!< ch0(adc123) adc2  fifo status*/
#define CODEC_ADC2_CH0_FIFO_RD_ERROR      CODEC_ADC2_CH0_FIFO_RD_ERROR_MSK
#define CODEC_ADC2_CH0_FIFO_RD_ERROR_W(X) ((X) << CODEC_ADC2_CH0_FIFO_RD_ERROR_POS)
#define CODEC_ADC2_CH0_FIFO_WR_ERROR_POS  (25U)
#define CODEC_ADC2_CH0_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_ADC2_CH0_FIFO_WR_ERROR_POS) /*!< ch0(adc123) adc2  fifo status*/
#define CODEC_ADC2_CH0_FIFO_WR_ERROR      CODEC_ADC2_CH0_FIFO_WR_ERROR_MSK
#define CODEC_ADC2_CH0_FIFO_WR_ERROR_W(X) ((X) << CODEC_ADC2_CH0_FIFO_WR_ERROR_POS)
#define CODEC_ADC3_CH0_FIFO_RD_ERROR_POS  (26U)
#define CODEC_ADC3_CH0_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_ADC3_CH0_FIFO_RD_ERROR_POS) /*!< ch0(adc123) adc3  fifo status*/
#define CODEC_ADC3_CH0_FIFO_RD_ERROR      CODEC_ADC3_CH0_FIFO_RD_ERROR_MSK
#define CODEC_ADC3_CH0_FIFO_RD_ERROR_W(X) ((X) << CODEC_ADC3_CH0_FIFO_RD_ERROR_POS)
#define CODEC_ADC3_CH0_FIFO_WR_ERROR_POS  (27U)
#define CODEC_ADC3_CH0_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_ADC3_CH0_FIFO_WR_ERROR_POS) /*!< ch0(adc123) adc3  fifo status*/
#define CODEC_ADC3_CH0_FIFO_WR_ERROR      CODEC_ADC3_CH0_FIFO_WR_ERROR_MSK
#define CODEC_ADC3_CH0_FIFO_WR_ERROR_W(X) ((X) << CODEC_ADC3_CH0_FIFO_WR_ERROR_POS)
#define CODEC_ADC5_CH1_FIFO_RD_ERROR_POS  (28U)
#define CODEC_ADC5_CH1_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_ADC5_CH1_FIFO_RD_ERROR_POS) /*!< ch1(adc5)adc5 fifo status*/
#define CODEC_ADC5_CH1_FIFO_RD_ERROR      CODEC_ADC5_CH1_FIFO_RD_ERROR_MSK
#define CODEC_ADC5_CH1_FIFO_RD_ERROR_W(X) ((X) << CODEC_ADC5_CH1_FIFO_RD_ERROR_POS)
#define CODEC_ADC5_CH1_FIFO_WR_ERROR_POS  (29U)
#define CODEC_ADC5_CH1_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_ADC5_CH1_FIFO_WR_ERROR_POS) /*!< ch1(adc5)adc5 fifo status*/
#define CODEC_ADC5_CH1_FIFO_WR_ERROR      CODEC_ADC5_CH1_FIFO_WR_ERROR_MSK
#define CODEC_ADC5_CH1_FIFO_WR_ERROR_W(X) ((X) << CODEC_ADC5_CH1_FIFO_WR_ERROR_POS)

//TSING_CODEC_FIFO_STATUS1 offsetaddress : 0x007C
//TSING_CODEC_FIFO_STATUS1 RegResetValue : 0x00030000
#define CODEC_DAC0_PC_FIFO_EMPTY_POS     (16U)
#define CODEC_DAC0_PC_FIFO_EMPTY_MSK     (0x1UL << CODEC_DAC0_PC_FIFO_EMPTY_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_EMPTY         CODEC_DAC0_PC_FIFO_EMPTY_MSK
#define CODEC_DAC0_PC_FIFO_EMPTY_W(X)    ((X) << CODEC_DAC0_PC_FIFO_EMPTY_POS)
#define CODEC_DAC0_PC_FIFO_AE_POS        (17U)
#define CODEC_DAC0_PC_FIFO_AE_MSK        (0x1UL << CODEC_DAC0_PC_FIFO_AE_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_AE            CODEC_DAC0_PC_FIFO_AE_MSK
#define CODEC_DAC0_PC_FIFO_AE_W(X)       ((X) << CODEC_DAC0_PC_FIFO_AE_POS)
#define CODEC_DAC0_PC_FIFO_HF_POS        (18U)
#define CODEC_DAC0_PC_FIFO_HF_MSK        (0x1UL << CODEC_DAC0_PC_FIFO_HF_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_HF            CODEC_DAC0_PC_FIFO_HF_MSK
#define CODEC_DAC0_PC_FIFO_HF_W(X)       ((X) << CODEC_DAC0_PC_FIFO_HF_POS)
#define CODEC_DAC0_PC_FIFO_AF_POS        (19U)
#define CODEC_DAC0_PC_FIFO_AF_MSK        (0x1UL << CODEC_DAC0_PC_FIFO_AF_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_AF            CODEC_DAC0_PC_FIFO_AF_MSK
#define CODEC_DAC0_PC_FIFO_AF_W(X)       ((X) << CODEC_DAC0_PC_FIFO_AF_POS)
#define CODEC_DAC0_PC_FIFO_FULL_POS      (20U)
#define CODEC_DAC0_PC_FIFO_FULL_MSK      (0x1UL << CODEC_DAC0_PC_FIFO_FULL_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_FULL          CODEC_DAC0_PC_FIFO_FULL_MSK
#define CODEC_DAC0_PC_FIFO_FULL_W(X)     ((X) << CODEC_DAC0_PC_FIFO_FULL_POS)
#define CODEC_DAC0_PC_FIFO_RD_ERROR_POS  (21U)
#define CODEC_DAC0_PC_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_DAC0_PC_FIFO_RD_ERROR_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_RD_ERROR      CODEC_DAC0_PC_FIFO_RD_ERROR_MSK
#define CODEC_DAC0_PC_FIFO_RD_ERROR_W(X) ((X) << CODEC_DAC0_PC_FIFO_RD_ERROR_POS)
#define CODEC_DAC0_PC_FIFO_WR_ERROR_POS  (22U)
#define CODEC_DAC0_PC_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_DAC0_PC_FIFO_WR_ERROR_POS) /*!< */
#define CODEC_DAC0_PC_FIFO_WR_ERROR      CODEC_DAC0_PC_FIFO_WR_ERROR_MSK
#define CODEC_DAC0_PC_FIFO_WR_ERROR_W(X) ((X) << CODEC_DAC0_PC_FIFO_WR_ERROR_POS)

//TSING_CODEC_FIFO_STATUS2 offsetaddress : 0x0080
//TSING_CODEC_FIFO_STATUS2 RegResetValue : 0x00030000
#define CODEC_DAC1_PC_FIFO_EMPTY_POS     (16U)
#define CODEC_DAC1_PC_FIFO_EMPTY_MSK     (0x1UL << CODEC_DAC1_PC_FIFO_EMPTY_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_EMPTY         CODEC_DAC1_PC_FIFO_EMPTY_MSK
#define CODEC_DAC1_PC_FIFO_EMPTY_W(X)    ((X) << CODEC_DAC1_PC_FIFO_EMPTY_POS)
#define CODEC_DAC1_PC_FIFO_AE_POS        (17U)
#define CODEC_DAC1_PC_FIFO_AE_MSK        (0x1UL << CODEC_DAC1_PC_FIFO_AE_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_AE            CODEC_DAC1_PC_FIFO_AE_MSK
#define CODEC_DAC1_PC_FIFO_AE_W(X)       ((X) << CODEC_DAC1_PC_FIFO_AE_POS)
#define CODEC_DAC1_PC_FIFO_HF_POS        (18U)
#define CODEC_DAC1_PC_FIFO_HF_MSK        (0x1UL << CODEC_DAC1_PC_FIFO_HF_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_HF            CODEC_DAC1_PC_FIFO_HF_MSK
#define CODEC_DAC1_PC_FIFO_HF_W(X)       ((X) << CODEC_DAC1_PC_FIFO_HF_POS)
#define CODEC_DAC1_PC_FIFO_AF_POS        (19U)
#define CODEC_DAC1_PC_FIFO_AF_MSK        (0x1UL << CODEC_DAC1_PC_FIFO_AF_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_AF            CODEC_DAC1_PC_FIFO_AF_MSK
#define CODEC_DAC1_PC_FIFO_AF_W(X)       ((X) << CODEC_DAC1_PC_FIFO_AF_POS)
#define CODEC_DAC1_PC_FIFO_FULL_POS      (20U)
#define CODEC_DAC1_PC_FIFO_FULL_MSK      (0x1UL << CODEC_DAC1_PC_FIFO_FULL_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_FULL          CODEC_DAC1_PC_FIFO_FULL_MSK
#define CODEC_DAC1_PC_FIFO_FULL_W(X)     ((X) << CODEC_DAC1_PC_FIFO_FULL_POS)
#define CODEC_DAC1_PC_FIFO_RD_ERROR_POS  (21U)
#define CODEC_DAC1_PC_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_DAC1_PC_FIFO_RD_ERROR_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_RD_ERROR      CODEC_DAC1_PC_FIFO_RD_ERROR_MSK
#define CODEC_DAC1_PC_FIFO_RD_ERROR_W(X) ((X) << CODEC_DAC1_PC_FIFO_RD_ERROR_POS)
#define CODEC_DAC1_PC_FIFO_WR_ERROR_POS  (22U)
#define CODEC_DAC1_PC_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_DAC1_PC_FIFO_WR_ERROR_POS) /*!< */
#define CODEC_DAC1_PC_FIFO_WR_ERROR      CODEC_DAC1_PC_FIFO_WR_ERROR_MSK
#define CODEC_DAC1_PC_FIFO_WR_ERROR_W(X) ((X) << CODEC_DAC1_PC_FIFO_WR_ERROR_POS)

//TSING_CODEC_FIFO_STATUS3 offsetaddress : 0x0084
//TSING_CODEC_FIFO_STATUS3 RegResetValue : 0x000303
#define CODEC_DAC0_FIFO_EMPTY_POS     (0U)
#define CODEC_DAC0_FIFO_EMPTY_MSK     (0x1UL << CODEC_DAC0_FIFO_EMPTY_POS) /*!< */
#define CODEC_DAC0_FIFO_EMPTY         CODEC_DAC0_FIFO_EMPTY_MSK
#define CODEC_DAC0_FIFO_EMPTY_W(X)    ((X) << CODEC_DAC0_FIFO_EMPTY_POS)
#define CODEC_DAC0_FIFO_AE_POS        (1U)
#define CODEC_DAC0_FIFO_AE_MSK        (0x1UL << CODEC_DAC0_FIFO_AE_POS) /*!< */
#define CODEC_DAC0_FIFO_AE            CODEC_DAC0_FIFO_AE_MSK
#define CODEC_DAC0_FIFO_AE_W(X)       ((X) << CODEC_DAC0_FIFO_AE_POS)
#define CODEC_DAC0_FIFO_HF_POS        (2U)
#define CODEC_DAC0_FIFO_HF_MSK        (0x1UL << CODEC_DAC0_FIFO_HF_POS) /*!< */
#define CODEC_DAC0_FIFO_HF            CODEC_DAC0_FIFO_HF_MSK
#define CODEC_DAC0_FIFO_HF_W(X)       ((X) << CODEC_DAC0_FIFO_HF_POS)
#define CODEC_DAC0_FIFO_AF_POS        (3U)
#define CODEC_DAC0_FIFO_AF_MSK        (0x1UL << CODEC_DAC0_FIFO_AF_POS) /*!< */
#define CODEC_DAC0_FIFO_AF            CODEC_DAC0_FIFO_AF_MSK
#define CODEC_DAC0_FIFO_AF_W(X)       ((X) << CODEC_DAC0_FIFO_AF_POS)
#define CODEC_DAC0_FIFO_FULL_POS      (4U)
#define CODEC_DAC0_FIFO_FULL_MSK      (0x1UL << CODEC_DAC0_FIFO_FULL_POS) /*!< */
#define CODEC_DAC0_FIFO_FULL          CODEC_DAC0_FIFO_FULL_MSK
#define CODEC_DAC0_FIFO_FULL_W(X)     ((X) << CODEC_DAC0_FIFO_FULL_POS)
#define CODEC_DAC0_FIFO_WR_ERROR_POS  (5U)
#define CODEC_DAC0_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_DAC0_FIFO_WR_ERROR_POS) /*!< */
#define CODEC_DAC0_FIFO_WR_ERROR      CODEC_DAC0_FIFO_WR_ERROR_MSK
#define CODEC_DAC0_FIFO_WR_ERROR_W(X) ((X) << CODEC_DAC0_FIFO_WR_ERROR_POS)
#define CODEC_DAC0_FIFO_RD_ERROR_POS  (6U)
#define CODEC_DAC0_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_DAC0_FIFO_RD_ERROR_POS) /*!< */
#define CODEC_DAC0_FIFO_RD_ERROR      CODEC_DAC0_FIFO_RD_ERROR_MSK
#define CODEC_DAC0_FIFO_RD_ERROR_W(X) ((X) << CODEC_DAC0_FIFO_RD_ERROR_POS)
#define CODEC_DAC1_FIFO_EMPTY_POS     (8U)
#define CODEC_DAC1_FIFO_EMPTY_MSK     (0x1UL << CODEC_DAC1_FIFO_EMPTY_POS) /*!< */
#define CODEC_DAC1_FIFO_EMPTY         CODEC_DAC1_FIFO_EMPTY_MSK
#define CODEC_DAC1_FIFO_EMPTY_W(X)    ((X) << CODEC_DAC1_FIFO_EMPTY_POS)
#define CODEC_DAC1_FIFO_AE_POS        (9U)
#define CODEC_DAC1_FIFO_AE_MSK        (0x1UL << CODEC_DAC1_FIFO_AE_POS) /*!< */
#define CODEC_DAC1_FIFO_AE            CODEC_DAC1_FIFO_AE_MSK
#define CODEC_DAC1_FIFO_AE_W(X)       ((X) << CODEC_DAC1_FIFO_AE_POS)
#define CODEC_DAC1_FIFO_HF_POS        (10U)
#define CODEC_DAC1_FIFO_HF_MSK        (0x1UL << CODEC_DAC1_FIFO_HF_POS) /*!< */
#define CODEC_DAC1_FIFO_HF            CODEC_DAC1_FIFO_HF_MSK
#define CODEC_DAC1_FIFO_HF_W(X)       ((X) << CODEC_DAC1_FIFO_HF_POS)
#define CODEC_DAC1_FIFO_AF_POS        (11U)
#define CODEC_DAC1_FIFO_AF_MSK        (0x1UL << CODEC_DAC1_FIFO_AF_POS) /*!< */
#define CODEC_DAC1_FIFO_AF            CODEC_DAC1_FIFO_AF_MSK
#define CODEC_DAC1_FIFO_AF_W(X)       ((X) << CODEC_DAC1_FIFO_AF_POS)
#define CODEC_DAC1_FIFO_FULL_POS      (12U)
#define CODEC_DAC1_FIFO_FULL_MSK      (0x1UL << CODEC_DAC1_FIFO_FULL_POS) /*!< */
#define CODEC_DAC1_FIFO_FULL          CODEC_DAC1_FIFO_FULL_MSK
#define CODEC_DAC1_FIFO_FULL_W(X)     ((X) << CODEC_DAC1_FIFO_FULL_POS)
#define CODEC_DAC1_FIFO_WR_ERROR_POS  (13U)
#define CODEC_DAC1_FIFO_WR_ERROR_MSK  (0x1UL << CODEC_DAC1_FIFO_WR_ERROR_POS) /*!< */
#define CODEC_DAC1_FIFO_WR_ERROR      CODEC_DAC1_FIFO_WR_ERROR_MSK
#define CODEC_DAC1_FIFO_WR_ERROR_W(X) ((X) << CODEC_DAC1_FIFO_WR_ERROR_POS)
#define CODEC_DAC1_FIFO_RD_ERROR_POS  (14U)
#define CODEC_DAC1_FIFO_RD_ERROR_MSK  (0x1UL << CODEC_DAC1_FIFO_RD_ERROR_POS) /*!< */
#define CODEC_DAC1_FIFO_RD_ERROR      CODEC_DAC1_FIFO_RD_ERROR_MSK
#define CODEC_DAC1_FIFO_RD_ERROR_W(X) ((X) << CODEC_DAC1_FIFO_RD_ERROR_POS)

//CODEC_INTR_CTRL offsetaddress : 0x00C0
//CODEC_INTR_CTRL RegResetValue : 0x3aff0f01
#define CODEC_AUDIO_CODEC_INTR_EN_POS  (0U)
#define CODEC_AUDIO_CODEC_INTR_EN_MSK  (0x1UL << CODEC_AUDIO_CODEC_INTR_EN_POS) /*!< audio interrupt enable*/
#define CODEC_AUDIO_CODEC_INTR_EN      CODEC_AUDIO_CODEC_INTR_EN_MSK
#define CODEC_AUDIO_CODEC_INTR_EN_W(X) ((X) << CODEC_AUDIO_CODEC_INTR_EN_POS)
#define CODEC_WR_SEL_HF_POS            (1U)
#define CODEC_WR_SEL_HF_MSK            (0x1UL << CODEC_WR_SEL_HF_POS) /*!< fifo write data ready select pop half full or almost empty*/
#define CODEC_WR_SEL_HF                CODEC_WR_SEL_HF_MSK
#define CODEC_WR_SEL_HF_W(X)           ((X) << CODEC_WR_SEL_HF_POS)
#define CODEC_RD_SEL_HF_POS            (2U)
#define CODEC_RD_SEL_HF_MSK            (0x1UL << CODEC_RD_SEL_HF_POS) /*!< fifo read data ready select push half full or almost full*/
#define CODEC_RD_SEL_HF                CODEC_RD_SEL_HF_MSK
#define CODEC_RD_SEL_HF_W(X)           ((X) << CODEC_RD_SEL_HF_POS)
#define CODEC_ADJ_ERR_FLG_CLR_POS      (3U)
#define CODEC_ADJ_ERR_FLG_CLR_MSK      (0x1UL << CODEC_ADJ_ERR_FLG_CLR_POS) /*!< adj_err_flag intr clear*/
#define CODEC_ADJ_ERR_FLG_CLR          CODEC_ADJ_ERR_FLG_CLR_MSK
#define CODEC_ADJ_ERR_FLG_CLR_W(X)     ((X) << CODEC_ADJ_ERR_FLG_CLR_POS)
#define CODEC_DATAL_WR_RDY_CLR_POS     (4U)
#define CODEC_DATAL_WR_RDY_CLR_MSK     (0x1UL << CODEC_DATAL_WR_RDY_CLR_POS) /*!< fifo l write data ready intr clear*/
#define CODEC_DATAL_WR_RDY_CLR         CODEC_DATAL_WR_RDY_CLR_MSK
#define CODEC_DATAL_WR_RDY_CLR_W(X)    ((X) << CODEC_DATAL_WR_RDY_CLR_POS)
#define CODEC_DATAL_RD_RDY_CLR_POS     (5U)
#define CODEC_DATAL_RD_RDY_CLR_MSK     (0x1UL << CODEC_DATAL_RD_RDY_CLR_POS) /*!< fifo l read data ready intr clear*/
#define CODEC_DATAL_RD_RDY_CLR         CODEC_DATAL_RD_RDY_CLR_MSK
#define CODEC_DATAL_RD_RDY_CLR_W(X)    ((X) << CODEC_DATAL_RD_RDY_CLR_POS)
#define CODEC_FIFOL_OF_CLR_POS         (6U)
#define CODEC_FIFOL_OF_CLR_MSK         (0x1UL << CODEC_FIFOL_OF_CLR_POS) /*!< fifo l overflow intr clear*/
#define CODEC_FIFOL_OF_CLR             CODEC_FIFOL_OF_CLR_MSK
#define CODEC_FIFOL_OF_CLR_W(X)        ((X) << CODEC_FIFOL_OF_CLR_POS)
#define CODEC_FIFOL_UF_CLR_POS         (7U)
#define CODEC_FIFOL_UF_CLR_MSK         (0x1UL << CODEC_FIFOL_UF_CLR_POS) /*!< fifo l underflow intr clear*/
#define CODEC_FIFOL_UF_CLR             CODEC_FIFOL_UF_CLR_MSK
#define CODEC_FIFOL_UF_CLR_W(X)        ((X) << CODEC_FIFOL_UF_CLR_POS)
#define CODEC_INL_FB_RD_EN_POS         (8U)
#define CODEC_INL_FB_RD_EN_MSK         (0x1UL << CODEC_INL_FB_RD_EN_POS) /*!< fifo inl_fb  intr enable*/
#define CODEC_INL_FB_RD_EN             CODEC_INL_FB_RD_EN_MSK
#define CODEC_INL_FB_RD_EN_W(X)        ((X) << CODEC_INL_FB_RD_EN_POS)
#define CODEC_OUTL_FB_RD_EN_POS        (9U)
#define CODEC_OUTL_FB_RD_EN_MSK        (0x1UL << CODEC_OUTL_FB_RD_EN_POS) /*!< fifo outl_fb  intr enable*/
#define CODEC_OUTL_FB_RD_EN            CODEC_OUTL_FB_RD_EN_MSK
#define CODEC_OUTL_FB_RD_EN_W(X)       ((X) << CODEC_OUTL_FB_RD_EN_POS)
#define CODEC_INL_FF_RD_EN_POS         (10U)
#define CODEC_INL_FF_RD_EN_MSK         (0x1UL << CODEC_INL_FF_RD_EN_POS) /*!< fifo inl_ff  intr enable*/
#define CODEC_INL_FF_RD_EN             CODEC_INL_FF_RD_EN_MSK
#define CODEC_INL_FF_RD_EN_W(X)        ((X) << CODEC_INL_FF_RD_EN_POS)
#define CODEC_OUTL_FF_RD_EN_POS        (11U)
#define CODEC_OUTL_FF_RD_EN_MSK        (0x1UL << CODEC_OUTL_FF_RD_EN_POS) /*!< fifo outl_ff  intr enable*/
#define CODEC_OUTL_FF_RD_EN            CODEC_OUTL_FF_RD_EN_MSK
#define CODEC_OUTL_FF_RD_EN_W(X)       ((X) << CODEC_OUTL_FF_RD_EN_POS)
#define CODEC_DATAR_WR_RDY_CLR_POS     (12U)
#define CODEC_DATAR_WR_RDY_CLR_MSK     (0x1UL << CODEC_DATAR_WR_RDY_CLR_POS) /*!< fifo r write data ready intr clear*/
#define CODEC_DATAR_WR_RDY_CLR         CODEC_DATAR_WR_RDY_CLR_MSK
#define CODEC_DATAR_WR_RDY_CLR_W(X)    ((X) << CODEC_DATAR_WR_RDY_CLR_POS)
#define CODEC_DATAR_RD_RDY_CLR_POS     (13U)
#define CODEC_DATAR_RD_RDY_CLR_MSK     (0x1UL << CODEC_DATAR_RD_RDY_CLR_POS) /*!< fifo r read data ready intr clear*/
#define CODEC_DATAR_RD_RDY_CLR         CODEC_DATAR_RD_RDY_CLR_MSK
#define CODEC_DATAR_RD_RDY_CLR_W(X)    ((X) << CODEC_DATAR_RD_RDY_CLR_POS)
#define CODEC_FIFOR_OF_CLR_POS         (14U)
#define CODEC_FIFOR_OF_CLR_MSK         (0x1UL << CODEC_FIFOR_OF_CLR_POS) /*!< fifo r overflow intr clear*/
#define CODEC_FIFOR_OF_CLR             CODEC_FIFOR_OF_CLR_MSK
#define CODEC_FIFOR_OF_CLR_W(X)        ((X) << CODEC_FIFOR_OF_CLR_POS)
#define CODEC_FIFOR_UF_CLR_POS         (15U)
#define CODEC_FIFOR_UF_CLR_MSK         (0x1UL << CODEC_FIFOR_UF_CLR_POS) /*!< fifo r underflow intr clear*/
#define CODEC_FIFOR_UF_CLR             CODEC_FIFOR_UF_CLR_MSK
#define CODEC_FIFOR_UF_CLR_W(X)        ((X) << CODEC_FIFOR_UF_CLR_POS)
#define CODEC_INR_FB_RD_EN_POS         (16U)
#define CODEC_INR_FB_RD_EN_MSK         (0x1UL << CODEC_INR_FB_RD_EN_POS) /*!< fifo inr_fb  intr enable*/
#define CODEC_INR_FB_RD_EN             CODEC_INR_FB_RD_EN_MSK
#define CODEC_INR_FB_RD_EN_W(X)        ((X) << CODEC_INR_FB_RD_EN_POS)
#define CODEC_OUTR_FB_RD_EN_POS        (17U)
#define CODEC_OUTR_FB_RD_EN_MSK        (0x1UL << CODEC_OUTR_FB_RD_EN_POS) /*!< fifo outr_fb  intr enable*/
#define CODEC_OUTR_FB_RD_EN            CODEC_OUTR_FB_RD_EN_MSK
#define CODEC_OUTR_FB_RD_EN_W(X)       ((X) << CODEC_OUTR_FB_RD_EN_POS)
#define CODEC_INR_FF_RD_EN_POS         (18U)
#define CODEC_INR_FF_RD_EN_MSK         (0x1UL << CODEC_INR_FF_RD_EN_POS) /*!< fifo inr_ff  intr enable*/
#define CODEC_INR_FF_RD_EN             CODEC_INR_FF_RD_EN_MSK
#define CODEC_INR_FF_RD_EN_W(X)        ((X) << CODEC_INR_FF_RD_EN_POS)
#define CODEC_OUTR_FF_RD_EN_POS        (19U)
#define CODEC_OUTR_FF_RD_EN_MSK        (0x1UL << CODEC_OUTR_FF_RD_EN_POS) /*!< fifo outr_ff  intr enable*/
#define CODEC_OUTR_FF_RD_EN            CODEC_OUTR_FF_RD_EN_MSK
#define CODEC_OUTR_FF_RD_EN_W(X)       ((X) << CODEC_OUTR_FF_RD_EN_POS)
#define CODEC_ADJ_ERR_FLG_EN_POS       (20U)
#define CODEC_ADJ_ERR_FLG_EN_MSK       (0x1UL << CODEC_ADJ_ERR_FLG_EN_POS) /*!< adj_err_flag intr enable*/
#define CODEC_ADJ_ERR_FLG_EN           CODEC_ADJ_ERR_FLG_EN_MSK
#define CODEC_ADJ_ERR_FLG_EN_W(X)      ((X) << CODEC_ADJ_ERR_FLG_EN_POS)
#define CODEC_DATAL_WR_RDY_EN_POS      (21U)
#define CODEC_DATAL_WR_RDY_EN_MSK      (0x1UL << CODEC_DATAL_WR_RDY_EN_POS) /*!< fifo l write data ready intr enable*/
#define CODEC_DATAL_WR_RDY_EN          CODEC_DATAL_WR_RDY_EN_MSK
#define CODEC_DATAL_WR_RDY_EN_W(X)     ((X) << CODEC_DATAL_WR_RDY_EN_POS)
#define CODEC_DATAL_RD_RDY_EN_POS      (22U)
#define CODEC_DATAL_RD_RDY_EN_MSK      (0x1UL << CODEC_DATAL_RD_RDY_EN_POS) /*!< fifo l read data ready intr enable*/
#define CODEC_DATAL_RD_RDY_EN          CODEC_DATAL_RD_RDY_EN_MSK
#define CODEC_DATAL_RD_RDY_EN_W(X)     ((X) << CODEC_DATAL_RD_RDY_EN_POS)
#define CODEC_FIFOL_OF_EN_POS          (23U)
#define CODEC_FIFOL_OF_EN_MSK          (0x1UL << CODEC_FIFOL_OF_EN_POS) /*!< fifo l overflow intr enable*/
#define CODEC_FIFOL_OF_EN              CODEC_FIFOL_OF_EN_MSK
#define CODEC_FIFOL_OF_EN_W(X)         ((X) << CODEC_FIFOL_OF_EN_POS)
#define CODEC_FIFOL_UF_EN_POS          (24U)
#define CODEC_FIFOL_UF_EN_MSK          (0x1UL << CODEC_FIFOL_UF_EN_POS) /*!< fifo l underflow intr enable*/
#define CODEC_FIFOL_UF_EN              CODEC_FIFOL_UF_EN_MSK
#define CODEC_FIFOL_UF_EN_W(X)         ((X) << CODEC_FIFOL_UF_EN_POS)
#define CODEC_AUTX_ILIM_DET_EN_POS     (25U)
#define CODEC_AUTX_ILIM_DET_EN_MSK     (0x1UL << CODEC_AUTX_ILIM_DET_EN_POS) /*!< */
#define CODEC_AUTX_ILIM_DET_EN         CODEC_AUTX_ILIM_DET_EN_MSK
#define CODEC_AUTX_ILIM_DET_EN_W(X)    ((X) << CODEC_AUTX_ILIM_DET_EN_POS)
#define CODEC_O_AUTX_ILIM_DET_CLR_POS  (26U)
#define CODEC_O_AUTX_ILIM_DET_CLR_MSK  (0x1UL << CODEC_O_AUTX_ILIM_DET_CLR_POS) /*!< */
#define CODEC_O_AUTX_ILIM_DET_CLR      CODEC_O_AUTX_ILIM_DET_CLR_MSK
#define CODEC_O_AUTX_ILIM_DET_CLR_W(X) ((X) << CODEC_O_AUTX_ILIM_DET_CLR_POS)
#define CODEC_DATAR_WR_RDY_EN_POS      (27U)
#define CODEC_DATAR_WR_RDY_EN_MSK      (0x1UL << CODEC_DATAR_WR_RDY_EN_POS) /*!< fifo r write data ready intr enable*/
#define CODEC_DATAR_WR_RDY_EN          CODEC_DATAR_WR_RDY_EN_MSK
#define CODEC_DATAR_WR_RDY_EN_W(X)     ((X) << CODEC_DATAR_WR_RDY_EN_POS)
#define CODEC_DATAR_RD_RDY_EN_POS      (28U)
#define CODEC_DATAR_RD_RDY_EN_MSK      (0x1UL << CODEC_DATAR_RD_RDY_EN_POS) /*!< fifo r read data ready intr enable*/
#define CODEC_DATAR_RD_RDY_EN          CODEC_DATAR_RD_RDY_EN_MSK
#define CODEC_DATAR_RD_RDY_EN_W(X)     ((X) << CODEC_DATAR_RD_RDY_EN_POS)
#define CODEC_FIFOR_OF_EN_POS          (29U)
#define CODEC_FIFOR_OF_EN_MSK          (0x1UL << CODEC_FIFOR_OF_EN_POS) /*!< fifo r overflow intr enable*/
#define CODEC_FIFOR_OF_EN              CODEC_FIFOR_OF_EN_MSK
#define CODEC_FIFOR_OF_EN_W(X)         ((X) << CODEC_FIFOR_OF_EN_POS)
#define CODEC_FIFOR_UF_EN_POS          (30U)
#define CODEC_FIFOR_UF_EN_MSK          (0x1UL << CODEC_FIFOR_UF_EN_POS) /*!< fifo r underflow intr enable*/
#define CODEC_FIFOR_UF_EN              CODEC_FIFOR_UF_EN_MSK
#define CODEC_FIFOR_UF_EN_W(X)         ((X) << CODEC_FIFOR_UF_EN_POS)

//CODEC_INTR_STATUS offsetaddress : 0x00C4
//CODEC_INTR_STATUS RegResetValue : 0x00000000
#define CODEC_OFFSET_ADJ_POS       (0U)
#define CODEC_OFFSET_ADJ_MSK       (0xffffffUL << CODEC_OFFSET_ADJ_POS) /*!< */
#define CODEC_OFFSET_ADJ           CODEC_OFFSET_ADJ_MSK
#define CODEC_OFFSET_ADJ_W(X)      ((X) << CODEC_OFFSET_ADJ_POS)
#define CODEC_ERR_TYPE_POS         (24U)
#define CODEC_ERR_TYPE_MSK         (0x3UL << CODEC_ERR_TYPE_POS) /*!< */
#define CODEC_ERR_TYPE             CODEC_ERR_TYPE_MSK
#define CODEC_ERR_TYPE_W(X)        ((X) << CODEC_ERR_TYPE_POS)
#define CODEC_PPM_ADJ_STATE_POS    (26U)
#define CODEC_PPM_ADJ_STATE_MSK    (0x7UL << CODEC_PPM_ADJ_STATE_POS) /*!< */
#define CODEC_PPM_ADJ_STATE        CODEC_PPM_ADJ_STATE_MSK
#define CODEC_PPM_ADJ_STATE_W(X)   ((X) << CODEC_PPM_ADJ_STATE_POS)
#define CODEC_O_AUTX_IREF_OK_POS   (29U)
#define CODEC_O_AUTX_IREF_OK_MSK   (0x1UL << CODEC_O_AUTX_IREF_OK_POS) /*!< */
#define CODEC_O_AUTX_IREF_OK       CODEC_O_AUTX_IREF_OK_MSK
#define CODEC_O_AUTX_IREF_OK_W(X)  ((X) << CODEC_O_AUTX_IREF_OK_POS)
#define CODEC_O_AUTX_ILIM_DET_POS  (30U)
#define CODEC_O_AUTX_ILIM_DET_MSK  (0x1UL << CODEC_O_AUTX_ILIM_DET_POS) /*!< */
#define CODEC_O_AUTX_ILIM_DET      CODEC_O_AUTX_ILIM_DET_MSK
#define CODEC_O_AUTX_ILIM_DET_W(X) ((X) << CODEC_O_AUTX_ILIM_DET_POS)
#define CODEC_ADJ_ERR_FLG_POS      (31U)
#define CODEC_ADJ_ERR_FLG_MSK      (0x1UL << CODEC_ADJ_ERR_FLG_POS) /*!< */
#define CODEC_ADJ_ERR_FLG          CODEC_ADJ_ERR_FLG_MSK
#define CODEC_ADJ_ERR_FLG_W(X)     ((X) << CODEC_ADJ_ERR_FLG_POS)

//CODEC_INTR_STATUS1 offsetaddress : 0x00C8
//CODEC_INTR_STATUS1 RegResetValue : 0x10000000
#define CODEC_AR_IFFT_DONE_O_RAW_POS   (18U)
#define CODEC_AR_IFFT_DONE_O_RAW_MSK   (0x1UL << CODEC_AR_IFFT_DONE_O_RAW_POS) /*!< ar_ifft_done_o intr*/
#define CODEC_AR_IFFT_DONE_O_RAW       CODEC_AR_IFFT_DONE_O_RAW_MSK
#define CODEC_AR_IFFT_DONE_O_RAW_W(X)  ((X) << CODEC_AR_IFFT_DONE_O_RAW_POS)
#define CODEC_AR_FFT_DONE_O_RAW_POS    (19U)
#define CODEC_AR_FFT_DONE_O_RAW_MSK    (0x1UL << CODEC_AR_FFT_DONE_O_RAW_POS) /*!< ar_fft_done_o intr*/
#define CODEC_AR_FFT_DONE_O_RAW        CODEC_AR_FFT_DONE_O_RAW_MSK
#define CODEC_AR_FFT_DONE_O_RAW_W(X)   ((X) << CODEC_AR_FFT_DONE_O_RAW_POS)
#define CODEC_AL_IFFT_DONE_O_RAW_POS   (20U)
#define CODEC_AL_IFFT_DONE_O_RAW_MSK   (0x1UL << CODEC_AL_IFFT_DONE_O_RAW_POS) /*!< al_ifft_done_o intr*/
#define CODEC_AL_IFFT_DONE_O_RAW       CODEC_AL_IFFT_DONE_O_RAW_MSK
#define CODEC_AL_IFFT_DONE_O_RAW_W(X)  ((X) << CODEC_AL_IFFT_DONE_O_RAW_POS)
#define CODEC_AL_FFT_DONE_O_RAW_POS    (21U)
#define CODEC_AL_FFT_DONE_O_RAW_MSK    (0x1UL << CODEC_AL_FFT_DONE_O_RAW_POS) /*!< al_fft_done_o intr*/
#define CODEC_AL_FFT_DONE_O_RAW        CODEC_AL_FFT_DONE_O_RAW_MSK
#define CODEC_AL_FFT_DONE_O_RAW_W(X)   ((X) << CODEC_AL_FFT_DONE_O_RAW_POS)
#define CODEC_O_AUTX_ILIM_DET_RAW_POS  (22U)
#define CODEC_O_AUTX_ILIM_DET_RAW_MSK  (0x1UL << CODEC_O_AUTX_ILIM_DET_RAW_POS) /*!< o_autx_ilim_det intr*/
#define CODEC_O_AUTX_ILIM_DET_RAW      CODEC_O_AUTX_ILIM_DET_RAW_MSK
#define CODEC_O_AUTX_ILIM_DET_RAW_W(X) ((X) << CODEC_O_AUTX_ILIM_DET_RAW_POS)
#define CODEC_ADJ_ERR_FLG_RAW_POS      (23U)
#define CODEC_ADJ_ERR_FLG_RAW_MSK      (0x1UL << CODEC_ADJ_ERR_FLG_RAW_POS) /*!< adj_err_flag intr*/
#define CODEC_ADJ_ERR_FLG_RAW          CODEC_ADJ_ERR_FLG_RAW_MSK
#define CODEC_ADJ_ERR_FLG_RAW_W(X)     ((X) << CODEC_ADJ_ERR_FLG_RAW_POS)
#define CODEC_DATAR_WR_RDY_RAW_POS     (24U)
#define CODEC_DATAR_WR_RDY_RAW_MSK     (0x1UL << CODEC_DATAR_WR_RDY_RAW_POS) /*!< fifo r write data ready intr*/
#define CODEC_DATAR_WR_RDY_RAW         CODEC_DATAR_WR_RDY_RAW_MSK
#define CODEC_DATAR_WR_RDY_RAW_W(X)    ((X) << CODEC_DATAR_WR_RDY_RAW_POS)
#define CODEC_DATAR_RD_RDY_RAW_POS     (25U)
#define CODEC_DATAR_RD_RDY_RAW_MSK     (0x1UL << CODEC_DATAR_RD_RDY_RAW_POS) /*!< fifo r read data ready intr*/
#define CODEC_DATAR_RD_RDY_RAW         CODEC_DATAR_RD_RDY_RAW_MSK
#define CODEC_DATAR_RD_RDY_RAW_W(X)    ((X) << CODEC_DATAR_RD_RDY_RAW_POS)
#define CODEC_FIFOR_OF_RAW_POS         (26U)
#define CODEC_FIFOR_OF_RAW_MSK         (0x1UL << CODEC_FIFOR_OF_RAW_POS) /*!< fifo r overflow intr*/
#define CODEC_FIFOR_OF_RAW             CODEC_FIFOR_OF_RAW_MSK
#define CODEC_FIFOR_OF_RAW_W(X)        ((X) << CODEC_FIFOR_OF_RAW_POS)
#define CODEC_FIFOR_UF_RAW_POS         (27U)
#define CODEC_FIFOR_UF_RAW_MSK         (0x1UL << CODEC_FIFOR_UF_RAW_POS) /*!< fifo r underflow intr*/
#define CODEC_FIFOR_UF_RAW             CODEC_FIFOR_UF_RAW_MSK
#define CODEC_FIFOR_UF_RAW_W(X)        ((X) << CODEC_FIFOR_UF_RAW_POS)
#define CODEC_DATAL_WR_RDY_RAW_POS     (28U)
#define CODEC_DATAL_WR_RDY_RAW_MSK     (0x1UL << CODEC_DATAL_WR_RDY_RAW_POS) /*!< fifo l write data ready intr*/
#define CODEC_DATAL_WR_RDY_RAW         CODEC_DATAL_WR_RDY_RAW_MSK
#define CODEC_DATAL_WR_RDY_RAW_W(X)    ((X) << CODEC_DATAL_WR_RDY_RAW_POS)
#define CODEC_DATAL_RD_RDY_RAW_POS     (29U)
#define CODEC_DATAL_RD_RDY_RAW_MSK     (0x1UL << CODEC_DATAL_RD_RDY_RAW_POS) /*!< fifo l read data ready intr*/
#define CODEC_DATAL_RD_RDY_RAW         CODEC_DATAL_RD_RDY_RAW_MSK
#define CODEC_DATAL_RD_RDY_RAW_W(X)    ((X) << CODEC_DATAL_RD_RDY_RAW_POS)
#define CODEC_FIFOL_OF_RAW_POS         (30U)
#define CODEC_FIFOL_OF_RAW_MSK         (0x1UL << CODEC_FIFOL_OF_RAW_POS) /*!< fifo l overflow intr*/
#define CODEC_FIFOL_OF_RAW             CODEC_FIFOL_OF_RAW_MSK
#define CODEC_FIFOL_OF_RAW_W(X)        ((X) << CODEC_FIFOL_OF_RAW_POS)
#define CODEC_FIFOL_UF_RAW_POS         (31U)
#define CODEC_FIFOL_UF_RAW_MSK         (0x1UL << CODEC_FIFOL_UF_RAW_POS) /*!< fifo l underflow intr*/
#define CODEC_FIFOL_UF_RAW             CODEC_FIFOL_UF_RAW_MSK
#define CODEC_FIFOL_UF_RAW_W(X)        ((X) << CODEC_FIFOL_UF_RAW_POS)

//CODEC_INTR_CTRL1 offsetaddress : 0x00CC
//CODEC_INTR_CTRL1 RegResetValue : 0x00000000
#define CODEC_AR_IFFT_DONE_O_CLR_POS  (0U)
#define CODEC_AR_IFFT_DONE_O_CLR_MSK  (0x1UL << CODEC_AR_IFFT_DONE_O_CLR_POS) /*!< ar_ifft_done_o interrupt clear*/
#define CODEC_AR_IFFT_DONE_O_CLR      CODEC_AR_IFFT_DONE_O_CLR_MSK
#define CODEC_AR_IFFT_DONE_O_CLR_W(X) ((X) << CODEC_AR_IFFT_DONE_O_CLR_POS)
#define CODEC_AR_FFT_DONE_O_CLR_POS   (1U)
#define CODEC_AR_FFT_DONE_O_CLR_MSK   (0x1UL << CODEC_AR_FFT_DONE_O_CLR_POS) /*!< ar_fft_done_o interrupt clear*/
#define CODEC_AR_FFT_DONE_O_CLR       CODEC_AR_FFT_DONE_O_CLR_MSK
#define CODEC_AR_FFT_DONE_O_CLR_W(X)  ((X) << CODEC_AR_FFT_DONE_O_CLR_POS)
#define CODEC_AL_IFFT_DONE_O_CLR_POS  (2U)
#define CODEC_AL_IFFT_DONE_O_CLR_MSK  (0x1UL << CODEC_AL_IFFT_DONE_O_CLR_POS) /*!< al_ifft_done_o interrupt clear*/
#define CODEC_AL_IFFT_DONE_O_CLR      CODEC_AL_IFFT_DONE_O_CLR_MSK
#define CODEC_AL_IFFT_DONE_O_CLR_W(X) ((X) << CODEC_AL_IFFT_DONE_O_CLR_POS)
#define CODEC_AL_FFT_DONE_O_CLR_POS   (3U)
#define CODEC_AL_FFT_DONE_O_CLR_MSK   (0x1UL << CODEC_AL_FFT_DONE_O_CLR_POS) /*!< al_fft_done_o interrupt clear*/
#define CODEC_AL_FFT_DONE_O_CLR       CODEC_AL_FFT_DONE_O_CLR_MSK
#define CODEC_AL_FFT_DONE_O_CLR_W(X)  ((X) << CODEC_AL_FFT_DONE_O_CLR_POS)
#define CODEC_AR_IFFT_DONE_O_EN_POS   (4U)
#define CODEC_AR_IFFT_DONE_O_EN_MSK   (0x1UL << CODEC_AR_IFFT_DONE_O_EN_POS) /*!< ar_ifft_done_o interrupt enable*/
#define CODEC_AR_IFFT_DONE_O_EN       CODEC_AR_IFFT_DONE_O_EN_MSK
#define CODEC_AR_IFFT_DONE_O_EN_W(X)  ((X) << CODEC_AR_IFFT_DONE_O_EN_POS)
#define CODEC_AR_FFT_DONE_O_EN_POS    (5U)
#define CODEC_AR_FFT_DONE_O_EN_MSK    (0x1UL << CODEC_AR_FFT_DONE_O_EN_POS) /*!< ar_fft_done_o interrupt enable*/
#define CODEC_AR_FFT_DONE_O_EN        CODEC_AR_FFT_DONE_O_EN_MSK
#define CODEC_AR_FFT_DONE_O_EN_W(X)   ((X) << CODEC_AR_FFT_DONE_O_EN_POS)
#define CODEC_AL_IFFT_DONE_O_EN_POS   (6U)
#define CODEC_AL_IFFT_DONE_O_EN_MSK   (0x1UL << CODEC_AL_IFFT_DONE_O_EN_POS) /*!< al_ifft_done_o interrupt enable*/
#define CODEC_AL_IFFT_DONE_O_EN       CODEC_AL_IFFT_DONE_O_EN_MSK
#define CODEC_AL_IFFT_DONE_O_EN_W(X)  ((X) << CODEC_AL_IFFT_DONE_O_EN_POS)
#define CODEC_AL_FFT_DONE_O_EN_POS    (7U)
#define CODEC_AL_FFT_DONE_O_EN_MSK    (0x1UL << CODEC_AL_FFT_DONE_O_EN_POS) /*!< al_fft_done_o interrupt enable*/
#define CODEC_AL_FFT_DONE_O_EN        CODEC_AL_FFT_DONE_O_EN_MSK
#define CODEC_AL_FFT_DONE_O_EN_W(X)   ((X) << CODEC_AL_FFT_DONE_O_EN_POS)

//CODEC_DAC_CFG0 offsetaddress : 0x00D0
//CODEC_DAC_CFG0 RegResetValue : 0x00000000
#define CODEC_I_CFG_DEM_ED_ENA_POS          (0U)
#define CODEC_I_CFG_DEM_ED_ENA_MSK          (0x1UL << CODEC_I_CFG_DEM_ED_ENA_POS) /*!< */
#define CODEC_I_CFG_DEM_ED_ENA              CODEC_I_CFG_DEM_ED_ENA_MSK
#define CODEC_I_CFG_DEM_ED_ENA_W(X)         ((X) << CODEC_I_CFG_DEM_ED_ENA_POS)
#define CODEC_I_CFG_DEM_ED_THRESH_LOW_POS   (1U)
#define CODEC_I_CFG_DEM_ED_THRESH_LOW_MSK   (0x7UL << CODEC_I_CFG_DEM_ED_THRESH_LOW_POS) /*!< */
#define CODEC_I_CFG_DEM_ED_THRESH_LOW       CODEC_I_CFG_DEM_ED_THRESH_LOW_MSK
#define CODEC_I_CFG_DEM_ED_THRESH_LOW_W(X)  ((X) << CODEC_I_CFG_DEM_ED_THRESH_LOW_POS)
#define CODEC_I_CFG_DEM_ED_THRESH_HIGH_POS  (4U)
#define CODEC_I_CFG_DEM_ED_THRESH_HIGH_MSK  (0x7UL << CODEC_I_CFG_DEM_ED_THRESH_HIGH_POS) /*!< */
#define CODEC_I_CFG_DEM_ED_THRESH_HIGH      CODEC_I_CFG_DEM_ED_THRESH_HIGH_MSK
#define CODEC_I_CFG_DEM_ED_THRESH_HIGH_W(X) ((X) << CODEC_I_CFG_DEM_ED_THRESH_HIGH_POS)
#define CODEC_I_CFG_DEM_ED_RLS_TIME_POS     (7U)
#define CODEC_I_CFG_DEM_ED_RLS_TIME_MSK     (0x3UL << CODEC_I_CFG_DEM_ED_RLS_TIME_POS) /*!< */
#define CODEC_I_CFG_DEM_ED_RLS_TIME         CODEC_I_CFG_DEM_ED_RLS_TIME_MSK
#define CODEC_I_CFG_DEM_ED_RLS_TIME_W(X)    ((X) << CODEC_I_CFG_DEM_ED_RLS_TIME_POS)
#define CODEC_I_CFG_DEM_ENA_POS             (9U)
#define CODEC_I_CFG_DEM_ENA_MSK             (0x1UL << CODEC_I_CFG_DEM_ENA_POS) /*!< */
#define CODEC_I_CFG_DEM_ENA                 CODEC_I_CFG_DEM_ENA_MSK
#define CODEC_I_CFG_DEM_ENA_W(X)            ((X) << CODEC_I_CFG_DEM_ENA_POS)
#define CODEC_I_CFG_DEM_DYNAMIC_PD_POS      (10U)
#define CODEC_I_CFG_DEM_DYNAMIC_PD_MSK      (0x1UL << CODEC_I_CFG_DEM_DYNAMIC_PD_POS) /*!< */
#define CODEC_I_CFG_DEM_DYNAMIC_PD          CODEC_I_CFG_DEM_DYNAMIC_PD_MSK
#define CODEC_I_CFG_DEM_DYNAMIC_PD_W(X)     ((X) << CODEC_I_CFG_DEM_DYNAMIC_PD_POS)
#define CODEC_I_CFG_DEM_MUTE_POS            (11U)
#define CODEC_I_CFG_DEM_MUTE_MSK            (0x1UL << CODEC_I_CFG_DEM_MUTE_POS) /*!< */
#define CODEC_I_CFG_DEM_MUTE                CODEC_I_CFG_DEM_MUTE_MSK
#define CODEC_I_CFG_DEM_MUTE_W(X)           ((X) << CODEC_I_CFG_DEM_MUTE_POS)
#define CODEC_I_CFG_AUTX_PDB_POS            (12U)
#define CODEC_I_CFG_AUTX_PDB_MSK            (0x1UL << CODEC_I_CFG_AUTX_PDB_POS) /*!< */
#define CODEC_I_CFG_AUTX_PDB                CODEC_I_CFG_AUTX_PDB_MSK
#define CODEC_I_CFG_AUTX_PDB_W(X)           ((X) << CODEC_I_CFG_AUTX_PDB_POS)
#define CODEC_I_CFG_AUTX_LCH_DISABLE_POS    (13U)
#define CODEC_I_CFG_AUTX_LCH_DISABLE_MSK    (0x1UL << CODEC_I_CFG_AUTX_LCH_DISABLE_POS) /*!< */
#define CODEC_I_CFG_AUTX_LCH_DISABLE        CODEC_I_CFG_AUTX_LCH_DISABLE_MSK
#define CODEC_I_CFG_AUTX_LCH_DISABLE_W(X)   ((X) << CODEC_I_CFG_AUTX_LCH_DISABLE_POS)
#define CODEC_I_CFG_AUTX_RCH_DISABLE_POS    (14U)
#define CODEC_I_CFG_AUTX_RCH_DISABLE_MSK    (0x1UL << CODEC_I_CFG_AUTX_RCH_DISABLE_POS) /*!< */
#define CODEC_I_CFG_AUTX_RCH_DISABLE        CODEC_I_CFG_AUTX_RCH_DISABLE_MSK
#define CODEC_I_CFG_AUTX_RCH_DISABLE_W(X)   ((X) << CODEC_I_CFG_AUTX_RCH_DISABLE_POS)
#define CODEC_I_CFG_ED_DSS_ENA_POS          (15U)
#define CODEC_I_CFG_ED_DSS_ENA_MSK          (0x1UL << CODEC_I_CFG_ED_DSS_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_ENA              CODEC_I_CFG_ED_DSS_ENA_MSK
#define CODEC_I_CFG_ED_DSS_ENA_W(X)         ((X) << CODEC_I_CFG_ED_DSS_ENA_POS)
#define CODEC_I_CFG_ED_DSS_THRESH_POS       (16U)
#define CODEC_I_CFG_ED_DSS_THRESH_MSK       (0xffUL << CODEC_I_CFG_ED_DSS_THRESH_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_THRESH           CODEC_I_CFG_ED_DSS_THRESH_MSK
#define CODEC_I_CFG_ED_DSS_THRESH_W(X)      ((X) << CODEC_I_CFG_ED_DSS_THRESH_POS)
#define CODEC_I_CFG_ED_DSS_RLS_TIME_POS     (24U)
#define CODEC_I_CFG_ED_DSS_RLS_TIME_MSK     (0x3fUL << CODEC_I_CFG_ED_DSS_RLS_TIME_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_RLS_TIME         CODEC_I_CFG_ED_DSS_RLS_TIME_MSK
#define CODEC_I_CFG_ED_DSS_RLS_TIME_W(X)    ((X) << CODEC_I_CFG_ED_DSS_RLS_TIME_POS)

//CODEC_DAC_CFG1 offsetaddress : 0x00D4
//CODEC_DAC_CFG1 RegResetValue : 0x00000000
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_POS  (0U)
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_MSK  (0x3UL << CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL      CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_MSK
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_W(X) ((X) << CODEC_I_CFG_ED_DSS_ZCD_TIMER_SEL_POS)
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_POS  (2U)
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_MSK  (0x1UL << CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA      CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_MSK
#define CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_W(X) ((X) << CODEC_I_CFG_ED_DSS_ZCD_TIMER_ENA_POS)
#define CODEC_I_CFG_ED_DSS_ZCD_ENA_POS        (3U)
#define CODEC_I_CFG_ED_DSS_ZCD_ENA_MSK        (0x1UL << CODEC_I_CFG_ED_DSS_ZCD_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_ZCD_ENA            CODEC_I_CFG_ED_DSS_ZCD_ENA_MSK
#define CODEC_I_CFG_ED_DSS_ZCD_ENA_W(X)       ((X) << CODEC_I_CFG_ED_DSS_ZCD_ENA_POS)
#define CODEC_I_CFG_ED_NG_ENA_POS             (4U)
#define CODEC_I_CFG_ED_NG_ENA_MSK             (0x1UL << CODEC_I_CFG_ED_NG_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_NG_ENA                 CODEC_I_CFG_ED_NG_ENA_MSK
#define CODEC_I_CFG_ED_NG_ENA_W(X)            ((X) << CODEC_I_CFG_ED_NG_ENA_POS)
#define CODEC_I_CFG_ED_NG_THRESH_POS          (5U)
#define CODEC_I_CFG_ED_NG_THRESH_MSK          (0xffUL << CODEC_I_CFG_ED_NG_THRESH_POS) /*!< */
#define CODEC_I_CFG_ED_NG_THRESH              CODEC_I_CFG_ED_NG_THRESH_MSK
#define CODEC_I_CFG_ED_NG_THRESH_W(X)         ((X) << CODEC_I_CFG_ED_NG_THRESH_POS)
#define CODEC_I_CFG_ED_NG_RLS_TIME_POS        (13U)
#define CODEC_I_CFG_ED_NG_RLS_TIME_MSK        (0x3fUL << CODEC_I_CFG_ED_NG_RLS_TIME_POS) /*!< */
#define CODEC_I_CFG_ED_NG_RLS_TIME            CODEC_I_CFG_ED_NG_RLS_TIME_MSK
#define CODEC_I_CFG_ED_NG_RLS_TIME_W(X)       ((X) << CODEC_I_CFG_ED_NG_RLS_TIME_POS)
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_POS   (19U)
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_MSK   (0x3UL << CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_POS) /*!< */
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL       CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_MSK
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_W(X)  ((X) << CODEC_I_CFG_ED_NG_ZCD_TIMER_SEL_POS)
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_POS   (21U)
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_MSK   (0x1UL << CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA       CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_MSK
#define CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_W(X)  ((X) << CODEC_I_CFG_ED_NG_ZCD_TIMER_ENA_POS)
#define CODEC_I_CFG_ED_NG_ZCD_ENA_POS         (22U)
#define CODEC_I_CFG_ED_NG_ZCD_ENA_MSK         (0x1UL << CODEC_I_CFG_ED_NG_ZCD_ENA_POS) /*!< */
#define CODEC_I_CFG_ED_NG_ZCD_ENA             CODEC_I_CFG_ED_NG_ZCD_ENA_MSK
#define CODEC_I_CFG_ED_NG_ZCD_ENA_W(X)        ((X) << CODEC_I_CFG_ED_NG_ZCD_ENA_POS)
#define CODEC_I_CFG_ED_NG_FORCELOW_POS        (23U)
#define CODEC_I_CFG_ED_NG_FORCELOW_MSK        (0x1UL << CODEC_I_CFG_ED_NG_FORCELOW_POS) /*!< */
#define CODEC_I_CFG_ED_NG_FORCELOW            CODEC_I_CFG_ED_NG_FORCELOW_MSK
#define CODEC_I_CFG_ED_NG_FORCELOW_W(X)       ((X) << CODEC_I_CFG_ED_NG_FORCELOW_POS)
#define CODEC_I_CFG_ED_NG_FORCEHIGH_POS       (24U)
#define CODEC_I_CFG_ED_NG_FORCEHIGH_MSK       (0x1UL << CODEC_I_CFG_ED_NG_FORCEHIGH_POS) /*!< */
#define CODEC_I_CFG_ED_NG_FORCEHIGH           CODEC_I_CFG_ED_NG_FORCEHIGH_MSK
#define CODEC_I_CFG_ED_NG_FORCEHIGH_W(X)      ((X) << CODEC_I_CFG_ED_NG_FORCEHIGH_POS)
#define CODEC_I_CFG_INVERT_DSM_IN_POS         (25U)
#define CODEC_I_CFG_INVERT_DSM_IN_MSK         (0x1UL << CODEC_I_CFG_INVERT_DSM_IN_POS) /*!< */
#define CODEC_I_CFG_INVERT_DSM_IN             CODEC_I_CFG_INVERT_DSM_IN_MSK
#define CODEC_I_CFG_INVERT_DSM_IN_W(X)        ((X) << CODEC_I_CFG_INVERT_DSM_IN_POS)
#define CODEC_I_CFG_DSM_ENA_POS               (26U)
#define CODEC_I_CFG_DSM_ENA_MSK               (0x1UL << CODEC_I_CFG_DSM_ENA_POS) /*!< */
#define CODEC_I_CFG_DSM_ENA                   CODEC_I_CFG_DSM_ENA_MSK
#define CODEC_I_CFG_DSM_ENA_W(X)              ((X) << CODEC_I_CFG_DSM_ENA_POS)
#define CODEC_I_CFG_DSM_INJ_ENA_L_POS         (27U)
#define CODEC_I_CFG_DSM_INJ_ENA_L_MSK         (0x1UL << CODEC_I_CFG_DSM_INJ_ENA_L_POS) /*!< */
#define CODEC_I_CFG_DSM_INJ_ENA_L             CODEC_I_CFG_DSM_INJ_ENA_L_MSK
#define CODEC_I_CFG_DSM_INJ_ENA_L_W(X)        ((X) << CODEC_I_CFG_DSM_INJ_ENA_L_POS)
#define CODEC_I_CFG_DSM_INJ_ENA_R_POS         (28U)
#define CODEC_I_CFG_DSM_INJ_ENA_R_MSK         (0x1UL << CODEC_I_CFG_DSM_INJ_ENA_R_POS) /*!< */
#define CODEC_I_CFG_DSM_INJ_ENA_R             CODEC_I_CFG_DSM_INJ_ENA_R_MSK
#define CODEC_I_CFG_DSM_INJ_ENA_R_W(X)        ((X) << CODEC_I_CFG_DSM_INJ_ENA_R_POS)
#define CODEC_I_CFG_DSM_OBS_ENA_L_POS         (29U)
#define CODEC_I_CFG_DSM_OBS_ENA_L_MSK         (0x1UL << CODEC_I_CFG_DSM_OBS_ENA_L_POS) /*!< */
#define CODEC_I_CFG_DSM_OBS_ENA_L             CODEC_I_CFG_DSM_OBS_ENA_L_MSK
#define CODEC_I_CFG_DSM_OBS_ENA_L_W(X)        ((X) << CODEC_I_CFG_DSM_OBS_ENA_L_POS)
#define CODEC_I_CFG_DSM_OBS_ENA_R_POS         (30U)
#define CODEC_I_CFG_DSM_OBS_ENA_R_MSK         (0x1UL << CODEC_I_CFG_DSM_OBS_ENA_R_POS) /*!< */
#define CODEC_I_CFG_DSM_OBS_ENA_R             CODEC_I_CFG_DSM_OBS_ENA_R_MSK
#define CODEC_I_CFG_DSM_OBS_ENA_R_W(X)        ((X) << CODEC_I_CFG_DSM_OBS_ENA_R_POS)

//CODEC_DAC_CFG2 offsetaddress : 0x00D8
//CODEC_DAC_CFG2 RegResetValue : 0x00000000
#define CODEC_I_CFG_DSS_DIGGAIN_ENA_POS     (0U)
#define CODEC_I_CFG_DSS_DIGGAIN_ENA_MSK     (0x1UL << CODEC_I_CFG_DSS_DIGGAIN_ENA_POS) /*!< */
#define CODEC_I_CFG_DSS_DIGGAIN_ENA         CODEC_I_CFG_DSS_DIGGAIN_ENA_MSK
#define CODEC_I_CFG_DSS_DIGGAIN_ENA_W(X)    ((X) << CODEC_I_CFG_DSS_DIGGAIN_ENA_POS)
#define CODEC_I_CFG_DSS_MULTIPLY_L_POS      (1U)
#define CODEC_I_CFG_DSS_MULTIPLY_L_MSK      (0xfUL << CODEC_I_CFG_DSS_MULTIPLY_L_POS) /*!< */
#define CODEC_I_CFG_DSS_MULTIPLY_L          CODEC_I_CFG_DSS_MULTIPLY_L_MSK
#define CODEC_I_CFG_DSS_MULTIPLY_L_W(X)     ((X) << CODEC_I_CFG_DSS_MULTIPLY_L_POS)
#define CODEC_I_CFG_DSS_DIVIDE_L_POS        (5U)
#define CODEC_I_CFG_DSS_DIVIDE_L_MSK        (0x3UL << CODEC_I_CFG_DSS_DIVIDE_L_POS) /*!< */
#define CODEC_I_CFG_DSS_DIVIDE_L            CODEC_I_CFG_DSS_DIVIDE_L_MSK
#define CODEC_I_CFG_DSS_DIVIDE_L_W(X)       ((X) << CODEC_I_CFG_DSS_DIVIDE_L_POS)
#define CODEC_I_CFG_DSS_MULTIPLY_R_POS      (7U)
#define CODEC_I_CFG_DSS_MULTIPLY_R_MSK      (0xfUL << CODEC_I_CFG_DSS_MULTIPLY_R_POS) /*!< */
#define CODEC_I_CFG_DSS_MULTIPLY_R          CODEC_I_CFG_DSS_MULTIPLY_R_MSK
#define CODEC_I_CFG_DSS_MULTIPLY_R_W(X)     ((X) << CODEC_I_CFG_DSS_MULTIPLY_R_POS)
#define CODEC_I_CFG_DSS_DIVIDE_R_POS        (11U)
#define CODEC_I_CFG_DSS_DIVIDE_R_MSK        (0x3UL << CODEC_I_CFG_DSS_DIVIDE_R_POS) /*!< */
#define CODEC_I_CFG_DSS_DIVIDE_R            CODEC_I_CFG_DSS_DIVIDE_R_MSK
#define CODEC_I_CFG_DSS_DIVIDE_R_W(X)       ((X) << CODEC_I_CFG_DSS_DIVIDE_R_POS)
#define CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_POS  (13U)
#define CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_MSK  (0x1UL << CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_POS) /*!< */
#define CODEC_I_CFG_DSS_DOUT_DLY1CYCLE      CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_MSK
#define CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_W(X) ((X) << CODEC_I_CFG_DSS_DOUT_DLY1CYCLE_POS)
#define CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_POS  (14U)
#define CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_MSK  (0x7UL << CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_LVL_DLY2AFE      CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_MSK
#define CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_W(X) ((X) << CODEC_I_CFG_ED_DSS_LVL_DLY2AFE_POS)
#define CODEC_I_CFG_ED_DSS_FORCELOW_POS     (17U)
#define CODEC_I_CFG_ED_DSS_FORCELOW_MSK     (0x1UL << CODEC_I_CFG_ED_DSS_FORCELOW_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_FORCELOW         CODEC_I_CFG_ED_DSS_FORCELOW_MSK
#define CODEC_I_CFG_ED_DSS_FORCELOW_W(X)    ((X) << CODEC_I_CFG_ED_DSS_FORCELOW_POS)
#define CODEC_I_CFG_ED_DSS_FORCEHIGH_POS    (18U)
#define CODEC_I_CFG_ED_DSS_FORCEHIGH_MSK    (0x1UL << CODEC_I_CFG_ED_DSS_FORCEHIGH_POS) /*!< */
#define CODEC_I_CFG_ED_DSS_FORCEHIGH        CODEC_I_CFG_ED_DSS_FORCEHIGH_MSK
#define CODEC_I_CFG_ED_DSS_FORCEHIGH_W(X)   ((X) << CODEC_I_CFG_ED_DSS_FORCEHIGH_POS)
#define CODEC_I_CFG_AUTX_GAIN_USER_L_POS    (19U)
#define CODEC_I_CFG_AUTX_GAIN_USER_L_MSK    (0x7UL << CODEC_I_CFG_AUTX_GAIN_USER_L_POS) /*!< */
#define CODEC_I_CFG_AUTX_GAIN_USER_L        CODEC_I_CFG_AUTX_GAIN_USER_L_MSK
#define CODEC_I_CFG_AUTX_GAIN_USER_L_W(X)   ((X) << CODEC_I_CFG_AUTX_GAIN_USER_L_POS)
#define CODEC_I_CFG_AUTX_GAIN_USER_R_POS    (22U)
#define CODEC_I_CFG_AUTX_GAIN_USER_R_MSK    (0x7UL << CODEC_I_CFG_AUTX_GAIN_USER_R_POS) /*!< */
#define CODEC_I_CFG_AUTX_GAIN_USER_R        CODEC_I_CFG_AUTX_GAIN_USER_R_MSK
#define CODEC_I_CFG_AUTX_GAIN_USER_R_W(X)   ((X) << CODEC_I_CFG_AUTX_GAIN_USER_R_POS)
#define CODEC_I_CFG_HPAMP_OFC_ENA_POS       (25U)
#define CODEC_I_CFG_HPAMP_OFC_ENA_MSK       (0x1UL << CODEC_I_CFG_HPAMP_OFC_ENA_POS) /*!< */
#define CODEC_I_CFG_HPAMP_OFC_ENA           CODEC_I_CFG_HPAMP_OFC_ENA_MSK
#define CODEC_I_CFG_HPAMP_OFC_ENA_W(X)      ((X) << CODEC_I_CFG_HPAMP_OFC_ENA_POS)
#define CODEC_I_CFG_AUTX_OFC_ENA1_POS       (26U)
#define CODEC_I_CFG_AUTX_OFC_ENA1_MSK       (0x1UL << CODEC_I_CFG_AUTX_OFC_ENA1_POS) /*!< */
#define CODEC_I_CFG_AUTX_OFC_ENA1           CODEC_I_CFG_AUTX_OFC_ENA1_MSK
#define CODEC_I_CFG_AUTX_OFC_ENA1_W(X)      ((X) << CODEC_I_CFG_AUTX_OFC_ENA1_POS)
#define CODEC_I_CFG_AUTX_OFC_ENA2_POS       (27U)
#define CODEC_I_CFG_AUTX_OFC_ENA2_MSK       (0x1UL << CODEC_I_CFG_AUTX_OFC_ENA2_POS) /*!< */
#define CODEC_I_CFG_AUTX_OFC_ENA2           CODEC_I_CFG_AUTX_OFC_ENA2_MSK
#define CODEC_I_CFG_AUTX_OFC_ENA2_W(X)      ((X) << CODEC_I_CFG_AUTX_OFC_ENA2_POS)
#define CODEC_I_CFG_OFC_INIT_CNT_POS        (28U)
#define CODEC_I_CFG_OFC_INIT_CNT_MSK        (0xfUL << CODEC_I_CFG_OFC_INIT_CNT_POS) /*!< */
#define CODEC_I_CFG_OFC_INIT_CNT            CODEC_I_CFG_OFC_INIT_CNT_MSK
#define CODEC_I_CFG_OFC_INIT_CNT_W(X)       ((X) << CODEC_I_CFG_OFC_INIT_CNT_POS)

//CODEC_DAC_CFG3 offsetaddress : 0x00DC
//CODEC_DAC_CFG3 RegResetValue : 0x00000000
#define CODEC_PGOOD_CDC_POS            (0U)
#define CODEC_PGOOD_CDC_MSK            (0x7UL << CODEC_PGOOD_CDC_POS) /*!< PGOOD signal of DAC PGOOD_CDC*/
#define CODEC_PGOOD_CDC                CODEC_PGOOD_CDC_MSK
#define CODEC_PGOOD_CDC_W(X)           ((X) << CODEC_PGOOD_CDC_POS)
#define CODEC_I_CFG_AUTX_MUTE_L_POS    (3U)
#define CODEC_I_CFG_AUTX_MUTE_L_MSK    (0x1UL << CODEC_I_CFG_AUTX_MUTE_L_POS) /*!< Mute autx Lch: 0 = unmute. 1 = mute.*/
#define CODEC_I_CFG_AUTX_MUTE_L        CODEC_I_CFG_AUTX_MUTE_L_MSK
#define CODEC_I_CFG_AUTX_MUTE_L_W(X)   ((X) << CODEC_I_CFG_AUTX_MUTE_L_POS)
#define CODEC_I_CFG_AUTX_MUTE_R_POS    (4U)
#define CODEC_I_CFG_AUTX_MUTE_R_MSK    (0x1UL << CODEC_I_CFG_AUTX_MUTE_R_POS) /*!< Mute autx Rch: 0 = unmute. 1 = mute.*/
#define CODEC_I_CFG_AUTX_MUTE_R        CODEC_I_CFG_AUTX_MUTE_R_MSK
#define CODEC_I_CFG_AUTX_MUTE_R_W(X)   ((X) << CODEC_I_CFG_AUTX_MUTE_R_POS)
#define CODEC_I_CFG_AUTX_IREF_PDB_POS  (5U)
#define CODEC_I_CFG_AUTX_IREF_PDB_MSK  (0x1UL << CODEC_I_CFG_AUTX_IREF_PDB_POS) /*!< Power up autx reference generation blocks: 0 = power down. 1 = power up.*/
#define CODEC_I_CFG_AUTX_IREF_PDB      CODEC_I_CFG_AUTX_IREF_PDB_MSK
#define CODEC_I_CFG_AUTX_IREF_PDB_W(X) ((X) << CODEC_I_CFG_AUTX_IREF_PDB_POS)
#define CODEC_O_AUTX_OFC_DONE_L_POS    (6U)
#define CODEC_O_AUTX_OFC_DONE_L_MSK    (0x1UL << CODEC_O_AUTX_OFC_DONE_L_POS) /*!< "Output signal indicating that the OFC of autx Lch path is done: 0 = Either not in OFC mode or OFC is not done. 1 = In OFC mode and OFC is done."*/
#define CODEC_O_AUTX_OFC_DONE_L        CODEC_O_AUTX_OFC_DONE_L_MSK
#define CODEC_O_AUTX_OFC_DONE_L_W(X)   ((X) << CODEC_O_AUTX_OFC_DONE_L_POS)
#define CODEC_O_AUTX_OFC_DONE_R_POS    (7U)
#define CODEC_O_AUTX_OFC_DONE_R_MSK    (0x1UL << CODEC_O_AUTX_OFC_DONE_R_POS) /*!< "Output signal indicating that the OFC of autx Rch path is done: 0 = Either not in OFC mode or OFC is not done. 1 = In OFC mode and OFC is done."*/
#define CODEC_O_AUTX_OFC_DONE_R        CODEC_O_AUTX_OFC_DONE_R_MSK
#define CODEC_O_AUTX_OFC_DONE_R_W(X)   ((X) << CODEC_O_AUTX_OFC_DONE_R_POS)
#define CODEC_HPAMP_OFC_CODE_L_POS     (16U)
#define CODEC_HPAMP_OFC_CODE_L_MSK     (0x7fUL << CODEC_HPAMP_OFC_CODE_L_POS) /*!< OFC code result of autx Lch HPAMP*/
#define CODEC_HPAMP_OFC_CODE_L         CODEC_HPAMP_OFC_CODE_L_MSK
#define CODEC_HPAMP_OFC_CODE_L_W(X)    ((X) << CODEC_HPAMP_OFC_CODE_L_POS)
#define CODEC_HPAMP_OFC_DONE_L_POS     (23U)
#define CODEC_HPAMP_OFC_DONE_L_MSK     (0x1UL << CODEC_HPAMP_OFC_DONE_L_POS) /*!< "Output signal indicating that the OFC of autx Lch HPAMP is done: 0 = Either not in OFC mode or OFC is not done. 1 = In OFC mode and OFC is done."*/
#define CODEC_HPAMP_OFC_DONE_L         CODEC_HPAMP_OFC_DONE_L_MSK
#define CODEC_HPAMP_OFC_DONE_L_W(X)    ((X) << CODEC_HPAMP_OFC_DONE_L_POS)
#define CODEC_HPAMP_OFC_CODE_R_POS     (24U)
#define CODEC_HPAMP_OFC_CODE_R_MSK     (0x7fUL << CODEC_HPAMP_OFC_CODE_R_POS) /*!< OFC code result of autx Rch HPAMP*/
#define CODEC_HPAMP_OFC_CODE_R         CODEC_HPAMP_OFC_CODE_R_MSK
#define CODEC_HPAMP_OFC_CODE_R_W(X)    ((X) << CODEC_HPAMP_OFC_CODE_R_POS)
#define CODEC_HPAMP_OFC_DONE_R_POS     (31U)
#define CODEC_HPAMP_OFC_DONE_R_MSK     (0x1UL << CODEC_HPAMP_OFC_DONE_R_POS) /*!< "Output signal indicating that the OFC of autx Rch HPAMP is done: 0 = Either not in OFC mode or OFC is not done. 1 = In OFC mode and OFC is done."*/
#define CODEC_HPAMP_OFC_DONE_R         CODEC_HPAMP_OFC_DONE_R_MSK
#define CODEC_HPAMP_OFC_DONE_R_W(X)    ((X) << CODEC_HPAMP_OFC_DONE_R_POS)

//CODEC_DAC_CFG4 offsetaddress : 0x00E0
//CODEC_DAC_CFG4 RegResetValue : 0x00b00000
#define CODEC_OFCCODE_AUTXGAIN_M18DB_L_POS  (0U)
#define CODEC_OFCCODE_AUTXGAIN_M18DB_L_MSK  (0xffUL << CODEC_OFCCODE_AUTXGAIN_M18DB_L_POS) /*!< */
#define CODEC_OFCCODE_AUTXGAIN_M18DB_L      CODEC_OFCCODE_AUTXGAIN_M18DB_L_MSK
#define CODEC_OFCCODE_AUTXGAIN_M18DB_L_W(X) ((X) << CODEC_OFCCODE_AUTXGAIN_M18DB_L_POS)
#define CODEC_OFCCODE_AUTXGAIN_M18DB_R_POS  (8U)
#define CODEC_OFCCODE_AUTXGAIN_M18DB_R_MSK  (0xffUL << CODEC_OFCCODE_AUTXGAIN_M18DB_R_POS) /*!< */
#define CODEC_OFCCODE_AUTXGAIN_M18DB_R      CODEC_OFCCODE_AUTXGAIN_M18DB_R_MSK
#define CODEC_OFCCODE_AUTXGAIN_M18DB_R_W(X) ((X) << CODEC_OFCCODE_AUTXGAIN_M18DB_R_POS)
#define CODEC_OFCCODE_AUTXGAIN_USER_L_POS   (16U)
#define CODEC_OFCCODE_AUTXGAIN_USER_L_MSK   (0xffUL << CODEC_OFCCODE_AUTXGAIN_USER_L_POS) /*!< */
#define CODEC_OFCCODE_AUTXGAIN_USER_L       CODEC_OFCCODE_AUTXGAIN_USER_L_MSK
#define CODEC_OFCCODE_AUTXGAIN_USER_L_W(X)  ((X) << CODEC_OFCCODE_AUTXGAIN_USER_L_POS)
#define CODEC_OFCCODE_AUTXGAIN_USER_R_POS   (24U)
#define CODEC_OFCCODE_AUTXGAIN_USER_R_MSK   (0xffUL << CODEC_OFCCODE_AUTXGAIN_USER_R_POS) /*!< */
#define CODEC_OFCCODE_AUTXGAIN_USER_R       CODEC_OFCCODE_AUTXGAIN_USER_R_MSK
#define CODEC_OFCCODE_AUTXGAIN_USER_R_W(X)  ((X) << CODEC_OFCCODE_AUTXGAIN_USER_R_POS)

//CODEC_DAC_TEST1 offsetaddress : 0x00E8
//CODEC_DAC_TEST1 RegResetValue : 0x00000000
#define CODEC_I_CFG_AUTX_TSTCTRL_1_POS  (0U)
#define CODEC_I_CFG_AUTX_TSTCTRL_1_MSK  (0xffffffffUL << CODEC_I_CFG_AUTX_TSTCTRL_1_POS) /*!< autx analog test control register 1.*/
#define CODEC_I_CFG_AUTX_TSTCTRL_1      CODEC_I_CFG_AUTX_TSTCTRL_1_MSK
#define CODEC_I_CFG_AUTX_TSTCTRL_1_W(X) ((X) << CODEC_I_CFG_AUTX_TSTCTRL_1_POS)

//CODEC_DAC_TEST2 offsetaddress : 0x00EC
//CODEC_DAC_TEST2 RegResetValue : 0x00000000
#define CODEC_I_CFG_AUTX_TSTCTRL_2_POS  (0U)
#define CODEC_I_CFG_AUTX_TSTCTRL_2_MSK  (0xffffffffUL << CODEC_I_CFG_AUTX_TSTCTRL_2_POS) /*!< autx analog test control register 2.*/
#define CODEC_I_CFG_AUTX_TSTCTRL_2      CODEC_I_CFG_AUTX_TSTCTRL_2_MSK
#define CODEC_I_CFG_AUTX_TSTCTRL_2_W(X) ((X) << CODEC_I_CFG_AUTX_TSTCTRL_2_POS)

//CODEC_DEBUG_CTRL offsetaddress : 0x00F0
//CODEC_DEBUG_CTRL RegResetValue : 0x00000000
#define CODEC_DBG_BUS_SEL_POS    (0U)
#define CODEC_DBG_BUS_SEL_MSK    (0x7UL << CODEC_DBG_BUS_SEL_POS) /*!< */
#define CODEC_DBG_BUS_SEL        CODEC_DBG_BUS_SEL_MSK
#define CODEC_DBG_BUS_SEL_W(X)   ((X) << CODEC_DBG_BUS_SEL_POS)
#define CODEC_CODEC_DBG_BUS_POS  (4U)
#define CODEC_CODEC_DBG_BUS_MSK  (0xffffUL << CODEC_CODEC_DBG_BUS_POS) /*!< */
#define CODEC_CODEC_DBG_BUS      CODEC_CODEC_DBG_BUS_MSK
#define CODEC_CODEC_DBG_BUS_W(X) ((X) << CODEC_CODEC_DBG_BUS_POS)

//CODEC_DAC_BSEL offsetaddress : 0x00F4
//CODEC_DAC_BSEL RegResetValue : 0x00000000
#define CODEC_DAC_DMA_LEFT_16BIT_SEL_POS   (0U)
#define CODEC_DAC_DMA_LEFT_16BIT_SEL_MSK   (0x1UL << CODEC_DAC_DMA_LEFT_16BIT_SEL_POS) /*!< music sel  0=24bit  1=16bit dac_pcm0*/
#define CODEC_DAC_DMA_LEFT_16BIT_SEL       CODEC_DAC_DMA_LEFT_16BIT_SEL_MSK
#define CODEC_DAC_DMA_LEFT_16BIT_SEL_W(X)  ((X) << CODEC_DAC_DMA_LEFT_16BIT_SEL_POS)
#define CODEC_DAC_DMA_RIGHT_16BIT_SEL_POS  (1U)
#define CODEC_DAC_DMA_RIGHT_16BIT_SEL_MSK  (0x1UL << CODEC_DAC_DMA_RIGHT_16BIT_SEL_POS) /*!< music sel  0=24bit  1=16bit dac_pcm1*/
#define CODEC_DAC_DMA_RIGHT_16BIT_SEL      CODEC_DAC_DMA_RIGHT_16BIT_SEL_MSK
#define CODEC_DAC_DMA_RIGHT_16BIT_SEL_W(X) ((X) << CODEC_DAC_DMA_RIGHT_16BIT_SEL_POS)
#define CODEC_STERO_16BIT_MODE_POS         (2U)
#define CODEC_STERO_16BIT_MODE_MSK         (0x1UL << CODEC_STERO_16BIT_MODE_POS) /*!< stero_16bit_mode, 1:music pcm1/music pcm0 share one fifo; 0:separated fifo.*/
#define CODEC_STERO_16BIT_MODE             CODEC_STERO_16BIT_MODE_MSK
#define CODEC_STERO_16BIT_MODE_W(X)        ((X) << CODEC_STERO_16BIT_MODE_POS)
#define CODEC_H2L_ORDER_POS                (3U)
#define CODEC_H2L_ORDER_MSK                (0x1UL << CODEC_H2L_ORDER_POS) /*!< 16bit mode data order for dac/adc fifo dma trans. 1: {high,low} like {adc1_data,adc0_date};0 {low,high}*/
#define CODEC_H2L_ORDER                    CODEC_H2L_ORDER_MSK
#define CODEC_H2L_ORDER_W(X)               ((X) << CODEC_H2L_ORDER_POS)

//CODEC_ADC_BSEL offsetaddress : 0x00F8
//CODEC_ADC_BSEL RegResetValue : 0x00000000
#define CODEC_ADC_DMA_CH0_16BIT_SEL_POS  (0U)
#define CODEC_ADC_DMA_CH0_16BIT_SEL_MSK  (0x1UL << CODEC_ADC_DMA_CH0_16BIT_SEL_POS) /*!< 0=24bit  1=16bit dma ch0 adc 0 1 2 3 4*/
#define CODEC_ADC_DMA_CH0_16BIT_SEL      CODEC_ADC_DMA_CH0_16BIT_SEL_MSK
#define CODEC_ADC_DMA_CH0_16BIT_SEL_W(X) ((X) << CODEC_ADC_DMA_CH0_16BIT_SEL_POS)
#define CODEC_ADC_DMA_CH1_16BIT_SEL_POS  (1U)
#define CODEC_ADC_DMA_CH1_16BIT_SEL_MSK  (0x1UL << CODEC_ADC_DMA_CH1_16BIT_SEL_POS) /*!< 0=24bit  1=16bit dma ch1 adc 3 4*/
#define CODEC_ADC_DMA_CH1_16BIT_SEL      CODEC_ADC_DMA_CH1_16BIT_SEL_MSK
#define CODEC_ADC_DMA_CH1_16BIT_SEL_W(X) ((X) << CODEC_ADC_DMA_CH1_16BIT_SEL_POS)

//CODEC_MUSIC_LVL offsetaddress : 0x00FC
//CODEC_MUSIC_LVL RegResetValue : 0x00000000
#define CODEC_DAC_DMA_FIFO_WORD_CNT_POS   (0U)
#define CODEC_DAC_DMA_FIFO_WORD_CNT_MSK   (0xfUL << CODEC_DAC_DMA_FIFO_WORD_CNT_POS) /*!< music  left fifo water level*/
#define CODEC_DAC_DMA_FIFO_WORD_CNT       CODEC_DAC_DMA_FIFO_WORD_CNT_MSK
#define CODEC_DAC_DMA_FIFO_WORD_CNT_W(X)  ((X) << CODEC_DAC_DMA_FIFO_WORD_CNT_POS)
#define CODEC_DAC1_DMA_FIFO_WORD_CNT_POS  (4U)
#define CODEC_DAC1_DMA_FIFO_WORD_CNT_MSK  (0xfUL << CODEC_DAC1_DMA_FIFO_WORD_CNT_POS) /*!< music  right fifo water level*/
#define CODEC_DAC1_DMA_FIFO_WORD_CNT      CODEC_DAC1_DMA_FIFO_WORD_CNT_MSK
#define CODEC_DAC1_DMA_FIFO_WORD_CNT_W(X) ((X) << CODEC_DAC1_DMA_FIFO_WORD_CNT_POS)

//ASRC_SAVE_CLKNCNT offsetaddress : 0x100
//ASRC_SAVE_CLKNCNT RegResetValue : 0x00000000
#define CODEC_CLKNCNT_SAVE_POS  (0U)
#define CODEC_CLKNCNT_SAVE_MSK  (0xfffffffUL << CODEC_CLKNCNT_SAVE_POS) /*!< value of clkncnt at music data path req or fifo intr*/
#define CODEC_CLKNCNT_SAVE      CODEC_CLKNCNT_SAVE_MSK
#define CODEC_CLKNCNT_SAVE_W(X) ((X) << CODEC_CLKNCNT_SAVE_POS)

//ASRC_SAVE_FINECNT offsetaddress : 0x104
//ASRC_SAVE_FINECNT RegResetValue : 0x00000000
#define CODEC_FINECNT_SAVE_POS        (0U)
#define CODEC_FINECNT_SAVE_MSK        (0x3ffUL << CODEC_FINECNT_SAVE_POS) /*!< value of finecnt_save at music data path req or fifo intr*/
#define CODEC_FINECNT_SAVE            CODEC_FINECNT_SAVE_MSK
#define CODEC_FINECNT_SAVE_W(X)       ((X) << CODEC_FINECNT_SAVE_POS)
#define CODEC_MUSIC_FIFO_POP_NUM_POS  (12U)
#define CODEC_MUSIC_FIFO_POP_NUM_MSK  (0x1fUL << CODEC_MUSIC_FIFO_POP_NUM_POS) /*!< value of music_fifo_pop_num at music data path req or fifo intr*/
#define CODEC_MUSIC_FIFO_POP_NUM      CODEC_MUSIC_FIFO_POP_NUM_MSK
#define CODEC_MUSIC_FIFO_POP_NUM_W(X) ((X) << CODEC_MUSIC_FIFO_POP_NUM_POS)

//ASRC_SAVE_CNTL offsetaddress : 0x108
//ASRC_SAVE_CNTL RegResetValue : 0x00000111
#define CODEC_ASRC_TIME_FIFO_POPNUM_SEL_POS  (0U)
#define CODEC_ASRC_TIME_FIFO_POPNUM_SEL_MSK  (0x1UL << CODEC_ASRC_TIME_FIFO_POPNUM_SEL_POS) /*!< trigger point select. 1:select music data path req. 0:select fifo statue.*/
#define CODEC_ASRC_TIME_FIFO_POPNUM_SEL      CODEC_ASRC_TIME_FIFO_POPNUM_SEL_MSK
#define CODEC_ASRC_TIME_FIFO_POPNUM_SEL_W(X) ((X) << CODEC_ASRC_TIME_FIFO_POPNUM_SEL_POS)
#define CODEC_FIFO_POP_CON_SEL_POS           (4U)
#define CODEC_FIFO_POP_CON_SEL_MSK           (0x3UL << CODEC_FIFO_POP_CON_SEL_POS) /*!< trigger point of fifo status 2'b11:dac_dma_fifo_pop_af 2'b10:dac_dma_fifo_pop_hf 2'h01:dac_dma_fifo_pop_ae 2'h00:dac_dma_fifo_pop_empty*/
#define CODEC_FIFO_POP_CON_SEL               CODEC_FIFO_POP_CON_SEL_MSK
#define CODEC_FIFO_POP_CON_SEL_W(X)          ((X) << CODEC_FIFO_POP_CON_SEL_POS)
#define CODEC_SAVE_EDGE_SEL_POS              (8U)
#define CODEC_SAVE_EDGE_SEL_MSK              (0x1UL << CODEC_SAVE_EDGE_SEL_POS) /*!< cdc control. 1:select the 2th cdc sync pulse. 0:select the 4th cdc sync pulse.*/
#define CODEC_SAVE_EDGE_SEL                  CODEC_SAVE_EDGE_SEL_MSK
#define CODEC_SAVE_EDGE_SEL_W(X)             ((X) << CODEC_SAVE_EDGE_SEL_POS)

//DAC_DCRM_CNTL offsetaddress : 0x110
//DAC_DCRM_CNTL RegResetValue : 0x00000000
#define CODEC_DAC0_HPF_FC_POS (0U)
#define CODEC_DAC0_HPF_FC_MSK \
    (0xfUL                    \
     << CODEC_DAC0_HPF_FC_POS) /*!< |      {dac0_hpf_fc[3:0]}           |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_DAC0_HPF_FC      CODEC_DAC0_HPF_FC_MSK
#define CODEC_DAC0_HPF_FC_W(X) ((X) << CODEC_DAC0_HPF_FC_POS)
#define CODEC_DAC0_HPF_EN_POS  (4U)
#define CODEC_DAC0_HPF_EN_MSK  (0x1UL << CODEC_DAC0_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF;(dc removal func.)*/
#define CODEC_DAC0_HPF_EN      CODEC_DAC0_HPF_EN_MSK
#define CODEC_DAC0_HPF_EN_W(X) ((X) << CODEC_DAC0_HPF_EN_POS)
#define CODEC_DAC1_HPF_FC_POS  (8U)
#define CODEC_DAC1_HPF_FC_MSK \
    (0xfUL                    \
     << CODEC_DAC1_HPF_FC_POS) /*!< |      {dac1_hpf_fc[3:0]}           |   rb   |fcutoff (Hz) fs is sample rate in Hz  | |            0000                   |   3    |      24.58·fs / 1000                 | |            0001                   |   4    |      10.985·fs / 1000                | |            0010                   |   5    |      5.22·fs / 1000                  | |            0011                   |   6    |      2.5466·fs / 1000                | |            0100                   |   7    |      1.258·fs / 1000                 | |            0101                   |   8    |      0.6254·fs / 1000                | |            0110                   |   9    |      0.3118·fs / 1000                | |            0111                   |   10   |     0.15565·fs / 1000                | |            1000                   |   11   |     0.07777·fs / 1000                | |            1001                   |   12   |     0.03887·fs / 1000                | |            1010                   |   13   |     0.01943·fs / 1000                | |            1011                   |   14   |     0.0097·fs / 1000                 | |            1100                   |   15   |     0.004857·fs / 1000               | |            1101                   |   16   |     0.00243·fs / 1000                | |            1110                   |   17   |     0.0012143·fs / 1000              | |            1111                   |   18   |     0.00060713·fs / 1000             |*/
#define CODEC_DAC1_HPF_FC      CODEC_DAC1_HPF_FC_MSK
#define CODEC_DAC1_HPF_FC_W(X) ((X) << CODEC_DAC1_HPF_FC_POS)
#define CODEC_DAC1_HPF_EN_POS  (12U)
#define CODEC_DAC1_HPF_EN_MSK  (0x1UL << CODEC_DAC1_HPF_EN_POS) /*!< 0: bypass HPF, 1: enable HPF; (dc removal func.)*/
#define CODEC_DAC1_HPF_EN      CODEC_DAC1_HPF_EN_MSK
#define CODEC_DAC1_HPF_EN_W(X) ((X) << CODEC_DAC1_HPF_EN_POS)

//DAC0_NG_CTRL_REG0 offsetaddress : 0x0114
//DAC0_NG_CTRL_REG0 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_PRE_GAIN_POS  (0U)
#define CODEC_DAC0_NG_PRE_GAIN_MSK  (0x7fffUL << CODEC_DAC0_NG_PRE_GAIN_POS) /*!< pre_gain*/
#define CODEC_DAC0_NG_PRE_GAIN      CODEC_DAC0_NG_PRE_GAIN_MSK
#define CODEC_DAC0_NG_PRE_GAIN_W(X) ((X) << CODEC_DAC0_NG_PRE_GAIN_POS)
#define CODEC_DAC0_NG_DOUT_SEL_POS  (15U)
#define CODEC_DAC0_NG_DOUT_SEL_MSK  (0x1UL << CODEC_DAC0_NG_DOUT_SEL_POS) /*!< noise gate module output select; 0: select dc_removal data, 1: select noise_gate data*/
#define CODEC_DAC0_NG_DOUT_SEL      CODEC_DAC0_NG_DOUT_SEL_MSK
#define CODEC_DAC0_NG_DOUT_SEL_W(X) ((X) << CODEC_DAC0_NG_DOUT_SEL_POS)
#define CODEC_DAC0_NG_ENABLE_POS    (16U)
#define CODEC_DAC0_NG_ENABLE_MSK    (0x1UL << CODEC_DAC0_NG_ENABLE_POS) /*!< noise gate module enable; 0: bypass, 1: enable noise gate*/
#define CODEC_DAC0_NG_ENABLE        CODEC_DAC0_NG_ENABLE_MSK
#define CODEC_DAC0_NG_ENABLE_W(X)   ((X) << CODEC_DAC0_NG_ENABLE_POS)

//DAC0_NG_CTRL_REG1 offsetaddress : 0x0118
//DAC0_NG_CTRL_REG1 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_T_LIN_POS  (0U)
#define CODEC_DAC0_NG_T_LIN_MSK  (0xffffffffUL << CODEC_DAC0_NG_T_LIN_POS) /*!< t_lin*/
#define CODEC_DAC0_NG_T_LIN      CODEC_DAC0_NG_T_LIN_MSK
#define CODEC_DAC0_NG_T_LIN_W(X) ((X) << CODEC_DAC0_NG_T_LIN_POS)

//DAC0_NG_CTRL_REG2 offsetaddress : 0x011c
//DAC0_NG_CTRL_REG2 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_ALPHA_A_POS  (0U)
#define CODEC_DAC0_NG_ALPHA_A_MSK  (0x1ffffUL << CODEC_DAC0_NG_ALPHA_A_POS) /*!< alpha_A*/
#define CODEC_DAC0_NG_ALPHA_A      CODEC_DAC0_NG_ALPHA_A_MSK
#define CODEC_DAC0_NG_ALPHA_A_W(X) ((X) << CODEC_DAC0_NG_ALPHA_A_POS)

//DAC0_NG_CTRL_REG3 offsetaddress : 0x0120
//DAC0_NG_CTRL_REG3 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_ALPHA_R_POS  (0U)
#define CODEC_DAC0_NG_ALPHA_R_MSK  (0x1ffffUL << CODEC_DAC0_NG_ALPHA_R_POS) /*!< alpha_R*/
#define CODEC_DAC0_NG_ALPHA_R      CODEC_DAC0_NG_ALPHA_R_MSK
#define CODEC_DAC0_NG_ALPHA_R_W(X) ((X) << CODEC_DAC0_NG_ALPHA_R_POS)

//DAC0_NG_CTRL_REG4 offsetaddress : 0x0124
//DAC0_NG_CTRL_REG4 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_ALPHA_A_INV_POS  (0U)
#define CODEC_DAC0_NG_ALPHA_A_INV_MSK  (0x3ffffUL << CODEC_DAC0_NG_ALPHA_A_INV_POS) /*!< alpha_A_inv*/
#define CODEC_DAC0_NG_ALPHA_A_INV      CODEC_DAC0_NG_ALPHA_A_INV_MSK
#define CODEC_DAC0_NG_ALPHA_A_INV_W(X) ((X) << CODEC_DAC0_NG_ALPHA_A_INV_POS)

//DAC0_NG_CTRL_REG5 offsetaddress : 0x0128
//DAC0_NG_CTRL_REG5 RegResetValue : 0x00000000
#define CODEC_DAC0_NG_ALPHA_R_INV_POS  (0U)
#define CODEC_DAC0_NG_ALPHA_R_INV_MSK  (0x3ffffUL << CODEC_DAC0_NG_ALPHA_R_INV_POS) /*!< alpha_R_inv*/
#define CODEC_DAC0_NG_ALPHA_R_INV      CODEC_DAC0_NG_ALPHA_R_INV_MSK
#define CODEC_DAC0_NG_ALPHA_R_INV_W(X) ((X) << CODEC_DAC0_NG_ALPHA_R_INV_POS)

//DAC1_NG_CTRL_REG0 offsetaddress : 0x0130
//DAC1_NG_CTRL_REG0 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_PRE_GAIN_POS  (0U)
#define CODEC_DAC1_NG_PRE_GAIN_MSK  (0x7fffUL << CODEC_DAC1_NG_PRE_GAIN_POS) /*!< pre_gain*/
#define CODEC_DAC1_NG_PRE_GAIN      CODEC_DAC1_NG_PRE_GAIN_MSK
#define CODEC_DAC1_NG_PRE_GAIN_W(X) ((X) << CODEC_DAC1_NG_PRE_GAIN_POS)
#define CODEC_DAC1_NG_DOUT_SEL_POS  (15U)
#define CODEC_DAC1_NG_DOUT_SEL_MSK  (0x1UL << CODEC_DAC1_NG_DOUT_SEL_POS) /*!< noise gate module output select; 0: select dc_removal data, 1: select noise_gate data*/
#define CODEC_DAC1_NG_DOUT_SEL      CODEC_DAC1_NG_DOUT_SEL_MSK
#define CODEC_DAC1_NG_DOUT_SEL_W(X) ((X) << CODEC_DAC1_NG_DOUT_SEL_POS)
#define CODEC_DAC1_NG_ENABLE_POS    (16U)
#define CODEC_DAC1_NG_ENABLE_MSK    (0x1UL << CODEC_DAC1_NG_ENABLE_POS) /*!< noise gate module enable; 0: bypass, 1: enable noise gate*/
#define CODEC_DAC1_NG_ENABLE        CODEC_DAC1_NG_ENABLE_MSK
#define CODEC_DAC1_NG_ENABLE_W(X)   ((X) << CODEC_DAC1_NG_ENABLE_POS)

//DAC1_NG_CTRL_REG1 offsetaddress : 0x0134
//DAC1_NG_CTRL_REG1 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_T_LIN_POS  (0U)
#define CODEC_DAC1_NG_T_LIN_MSK  (0xffffffffUL << CODEC_DAC1_NG_T_LIN_POS) /*!< t_lin*/
#define CODEC_DAC1_NG_T_LIN      CODEC_DAC1_NG_T_LIN_MSK
#define CODEC_DAC1_NG_T_LIN_W(X) ((X) << CODEC_DAC1_NG_T_LIN_POS)

//DAC1_NG_CTRL_REG2 offsetaddress : 0x0138
//DAC1_NG_CTRL_REG2 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_ALPHA_A_POS  (0U)
#define CODEC_DAC1_NG_ALPHA_A_MSK  (0x1ffffUL << CODEC_DAC1_NG_ALPHA_A_POS) /*!< alpha_A*/
#define CODEC_DAC1_NG_ALPHA_A      CODEC_DAC1_NG_ALPHA_A_MSK
#define CODEC_DAC1_NG_ALPHA_A_W(X) ((X) << CODEC_DAC1_NG_ALPHA_A_POS)

//DAC1_NG_CTRL_REG3 offsetaddress : 0x013c
//DAC1_NG_CTRL_REG3 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_ALPHA_R_POS  (0U)
#define CODEC_DAC1_NG_ALPHA_R_MSK  (0x1ffffUL << CODEC_DAC1_NG_ALPHA_R_POS) /*!< alpha_R*/
#define CODEC_DAC1_NG_ALPHA_R      CODEC_DAC1_NG_ALPHA_R_MSK
#define CODEC_DAC1_NG_ALPHA_R_W(X) ((X) << CODEC_DAC1_NG_ALPHA_R_POS)

//DAC1_NG_CTRL_REG4 offsetaddress : 0x0140
//DAC1_NG_CTRL_REG4 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_ALPHA_A_INV_POS  (0U)
#define CODEC_DAC1_NG_ALPHA_A_INV_MSK  (0x3ffffUL << CODEC_DAC1_NG_ALPHA_A_INV_POS) /*!< alpha_A_inv*/
#define CODEC_DAC1_NG_ALPHA_A_INV      CODEC_DAC1_NG_ALPHA_A_INV_MSK
#define CODEC_DAC1_NG_ALPHA_A_INV_W(X) ((X) << CODEC_DAC1_NG_ALPHA_A_INV_POS)

//DAC1_NG_CTRL_REG5 offsetaddress : 0x0144
//DAC1_NG_CTRL_REG5 RegResetValue : 0x00000000
#define CODEC_DAC1_NG_ALPHA_R_INV_POS  (0U)
#define CODEC_DAC1_NG_ALPHA_R_INV_MSK  (0x3ffffUL << CODEC_DAC1_NG_ALPHA_R_INV_POS) /*!< alpha_R_inv*/
#define CODEC_DAC1_NG_ALPHA_R_INV      CODEC_DAC1_NG_ALPHA_R_INV_MSK
#define CODEC_DAC1_NG_ALPHA_R_INV_W(X) ((X) << CODEC_DAC1_NG_ALPHA_R_INV_POS)

//DAC_DMA_CTRL offsetaddress : 0x014c
//DAC_DMA_CTRL RegResetValue : 0x00000000
#define CODEC_DAC_PCM_LR_CO_POS  (0U)
#define CODEC_DAC_PCM_LR_CO_MSK  (0x1UL << CODEC_DAC_PCM_LR_CO_POS) /*!< 0: disable 1: dac0*/
#define CODEC_DAC_PCM_LR_CO      CODEC_DAC_PCM_LR_CO_MSK
#define CODEC_DAC_PCM_LR_CO_W(X) ((X) << CODEC_DAC_PCM_LR_CO_POS)

//CODEC_DAC_CFG5 offsetaddress : 0x0150
//CODEC_DAC_CFG5 RegResetValue : 0x00600000
#define CODEC_DSM_DATA_L_M2P5DB_TH_POS  (0U)
#define CODEC_DSM_DATA_L_M2P5DB_TH_MSK  (0xffffffffUL << CODEC_DSM_DATA_L_M2P5DB_TH_POS) /*!< Left (l) dsm -2.5dB saturation processing threshold. Formula 2^(bit width-1) = dsm_data_l_m2p5dB_th * 10^ (2.5/20)*/
#define CODEC_DSM_DATA_L_M2P5DB_TH      CODEC_DSM_DATA_L_M2P5DB_TH_MSK
#define CODEC_DSM_DATA_L_M2P5DB_TH_W(X) ((X) << CODEC_DSM_DATA_L_M2P5DB_TH_POS)

//CODEC_DAC_CFG6 offsetaddress : 0x0154
//CODEC_DAC_CFG6 RegResetValue : 0x00600000
#define CODEC_DSM_DATA_R_M2P5DB_TH_POS  (0U)
#define CODEC_DSM_DATA_R_M2P5DB_TH_MSK  (0xffffffffUL << CODEC_DSM_DATA_R_M2P5DB_TH_POS) /*!< Right (r) dsm -2.5dB saturation processing threshold. Formula 2^(bit width-1) = dsm_data_r_m2p5dB_th * 10^ (2.5/20)*/
#define CODEC_DSM_DATA_R_M2P5DB_TH      CODEC_DSM_DATA_R_M2P5DB_TH_MSK
#define CODEC_DSM_DATA_R_M2P5DB_TH_W(X) ((X) << CODEC_DSM_DATA_R_M2P5DB_TH_POS)

//BP_384FLT_FR_DLY offsetaddress : 0x0158
//BP_384FLT_FR_DLY RegResetValue : 0x00000000
#define CODEC_BP_384FLT_FOR_DLY_POS  (0U)
#define CODEC_BP_384FLT_FOR_DLY_MSK  (0x1UL << CODEC_BP_384FLT_FOR_DLY_POS) /*!< 1: The downsampling/up sampling filter at the 384k sampling rate is used to achieve consistency with the digital path of 768.*/
#define CODEC_BP_384FLT_FOR_DLY      CODEC_BP_384FLT_FOR_DLY_MSK
#define CODEC_BP_384FLT_FOR_DLY_W(X) ((X) << CODEC_BP_384FLT_FOR_DLY_POS)

//FPGA_AD_CFG offsetaddress : 0x0160
//FPGA_AD_CFG RegResetValue : 0x0000016b
#define CODEC_ADC2_PD_POS     (0U)
#define CODEC_ADC2_PD_MSK     (0x1UL << CODEC_ADC2_PD_POS) /*!< Power down all circuitry. active low*/
#define CODEC_ADC2_PD         CODEC_ADC2_PD_MSK
#define CODEC_ADC2_PD_W(X)    ((X) << CODEC_ADC2_PD_POS)
#define CODEC_ADC2_RESET_POS  (1U)
#define CODEC_ADC2_RESET_MSK  (0x1UL << CODEC_ADC2_RESET_POS) /*!< Reset digital filter. active low*/
#define CODEC_ADC2_RESET      CODEC_ADC2_RESET_MSK
#define CODEC_ADC2_RESET_W(X) ((X) << CODEC_ADC2_RESET_POS)
#define CODEC_ADC2_CS_POS     (2U)
#define CODEC_ADC2_CS_MSK     (0x1UL << CODEC_ADC2_CS_POS) /*!< Chip select. active low*/
#define CODEC_ADC2_CS         CODEC_ADC2_CS_MSK
#define CODEC_ADC2_CS_W(X)    ((X) << CODEC_ADC2_CS_POS)
#define CODEC_ADC2_RD_POS     (3U)
#define CODEC_ADC2_RD_MSK     (0x1UL << CODEC_ADC2_RD_POS) /*!< Read enable.Digital input: active low*/
#define CODEC_ADC2_RD         CODEC_ADC2_RD_MSK
#define CODEC_ADC2_RD_W(X)    ((X) << CODEC_ADC2_RD_POS)
#define CODEC_ADC2_OTR_POS    (4U)
#define CODEC_ADC2_OTR_MSK    (0x1UL << CODEC_ADC2_OTR_POS) /*!< Active when analog inputs are out of range*/
#define CODEC_ADC2_OTR        CODEC_ADC2_OTR_MSK
#define CODEC_ADC2_OTR_W(X)   ((X) << CODEC_ADC2_OTR_POS)
#define CODEC_ADC1_PD_POS     (5U)
#define CODEC_ADC1_PD_MSK     (0x1UL << CODEC_ADC1_PD_POS) /*!< Power down all circuitry. active low*/
#define CODEC_ADC1_PD         CODEC_ADC1_PD_MSK
#define CODEC_ADC1_PD_W(X)    ((X) << CODEC_ADC1_PD_POS)
#define CODEC_ADC1_RESET_POS  (6U)
#define CODEC_ADC1_RESET_MSK  (0x1UL << CODEC_ADC1_RESET_POS) /*!< Reset digital filter. active low*/
#define CODEC_ADC1_RESET      CODEC_ADC1_RESET_MSK
#define CODEC_ADC1_RESET_W(X) ((X) << CODEC_ADC1_RESET_POS)
#define CODEC_ADC1_CS_POS     (7U)
#define CODEC_ADC1_CS_MSK     (0x1UL << CODEC_ADC1_CS_POS) /*!< Chip select. active low*/
#define CODEC_ADC1_CS         CODEC_ADC1_CS_MSK
#define CODEC_ADC1_CS_W(X)    ((X) << CODEC_ADC1_CS_POS)
#define CODEC_ADC1_RD_POS     (8U)
#define CODEC_ADC1_RD_MSK     (0x1UL << CODEC_ADC1_RD_POS) /*!< Read enable.Digital input: active low*/
#define CODEC_ADC1_RD         CODEC_ADC1_RD_MSK
#define CODEC_ADC1_RD_W(X)    ((X) << CODEC_ADC1_RD_POS)
#define CODEC_ADC1_OTR_POS    (9U)
#define CODEC_ADC1_OTR_MSK    (0x1UL << CODEC_ADC1_OTR_POS) /*!< Active when analog inputs are out of range*/
#define CODEC_ADC1_OTR        CODEC_ADC1_OTR_MSK
#define CODEC_ADC1_OTR_W(X)   ((X) << CODEC_ADC1_OTR_POS)

//FPGA_PGA_CFG0 offsetaddress : 0x0164
//FPGA_PGA_CFG0 RegResetValue : 0x2a000000
#define CODEC_PGA2_OL_POS     (0U)
#define CODEC_PGA2_OL_MSK     (0x1UL << CODEC_PGA2_OL_POS) /*!< Overload Indicator Bit. SDI*/
#define CODEC_PGA2_OL         CODEC_PGA2_OL_MSK
#define CODEC_PGA2_OL_W(X)    ((X) << CODEC_PGA2_OL_POS)
#define CODEC_PGA2_START_POS  (1U)
#define CODEC_PGA2_START_MSK  (0x1UL << CODEC_PGA2_START_POS) /*!< PGA2500 SERIAL PORT trans start, when pga done is 1, write this bit to 0.*/
#define CODEC_PGA2_START      CODEC_PGA2_START_MSK
#define CODEC_PGA2_START_W(X) ((X) << CODEC_PGA2_START_POS)
#define CODEC_PGA2_CM_POS     (2U)
#define CODEC_PGA2_CM_MSK     (0x1UL << CODEC_PGA2_CM_POS) /*!< CM Servo Enable(Active High) SDI*/
#define CODEC_PGA2_CM         CODEC_PGA2_CM_MSK
#define CODEC_PGA2_CM_W(X)    ((X) << CODEC_PGA2_CM_POS)
#define CODEC_PGA2_DC_N_POS   (3U)
#define CODEC_PGA2_DC_N_MSK   (0x1UL << CODEC_PGA2_DC_N_POS) /*!< DC Servo Enable (Active Low) SDI*/
#define CODEC_PGA2_DC_N       CODEC_PGA2_DC_N_MSK
#define CODEC_PGA2_DC_N_W(X)  ((X) << CODEC_PGA2_DC_N_POS)
#define CODEC_PGA2_PGA_G_POS  (4U)
#define CODEC_PGA2_PGA_G_MSK  (0x3fUL << CODEC_PGA2_PGA_G_POS) /*!< Preamplifier Gain.   where N = G[5:0]DEC,For N = 0, Gain = 0dB;For N = 1 to 56, Gain (dB) = 9 + N*/
#define CODEC_PGA2_PGA_G      CODEC_PGA2_PGA_G_MSK
#define CODEC_PGA2_PGA_G_W(X) ((X) << CODEC_PGA2_PGA_G_POS)
#define CODEC_PGA1_DONE_POS   (10U)
#define CODEC_PGA1_DONE_MSK   (0x1UL << CODEC_PGA1_DONE_POS) /*!< PGA2500 SERIAL PORT trans done, after pga done is 1, if pga_start is write to 0, pga done will be 0.*/
#define CODEC_PGA1_DONE       CODEC_PGA1_DONE_MSK
#define CODEC_PGA1_DONE_W(X)  ((X) << CODEC_PGA1_DONE_POS)
#define CODEC_PGA1_GPO_D_POS  (11U)
#define CODEC_PGA1_GPO_D_MSK  (0xfUL << CODEC_PGA1_GPO_D_POS) /*!< Data for GPO.SDI*/
#define CODEC_PGA1_GPO_D      CODEC_PGA1_GPO_D_MSK
#define CODEC_PGA1_GPO_D_W(X) ((X) << CODEC_PGA1_GPO_D_POS)
#define CODEC_PGA1_OL_POS     (15U)
#define CODEC_PGA1_OL_MSK     (0x1UL << CODEC_PGA1_OL_POS) /*!< Overload Indicator Bit. SDI*/
#define CODEC_PGA1_OL         CODEC_PGA1_OL_MSK
#define CODEC_PGA1_OL_W(X)    ((X) << CODEC_PGA1_OL_POS)
#define CODEC_PGA1_START_POS  (16U)
#define CODEC_PGA1_START_MSK  (0x1UL << CODEC_PGA1_START_POS) /*!< PGA2500 SERIAL PORT trans start, when pga done is 1, write this bit to 0.*/
#define CODEC_PGA1_START      CODEC_PGA1_START_MSK
#define CODEC_PGA1_START_W(X) ((X) << CODEC_PGA1_START_POS)
#define CODEC_PGA1_CM_POS     (17U)
#define CODEC_PGA1_CM_MSK     (0x1UL << CODEC_PGA1_CM_POS) /*!< CM Servo Enable(Active High) SDI*/
#define CODEC_PGA1_CM         CODEC_PGA1_CM_MSK
#define CODEC_PGA1_CM_W(X)    ((X) << CODEC_PGA1_CM_POS)
#define CODEC_PGA1_DC_N_POS   (18U)
#define CODEC_PGA1_DC_N_MSK   (0x1UL << CODEC_PGA1_DC_N_POS) /*!< DC Servo Enable (Active Low) SDI*/
#define CODEC_PGA1_DC_N       CODEC_PGA1_DC_N_MSK
#define CODEC_PGA1_DC_N_W(X)  ((X) << CODEC_PGA1_DC_N_POS)
#define CODEC_PGA1_PGA_G_POS  (19U)
#define CODEC_PGA1_PGA_G_MSK  (0x3fUL << CODEC_PGA1_PGA_G_POS) /*!< Preamplifier Gain.   where N = G[5:0]DEC,For N = 0, Gain = 0dB;For N = 1 to 56, Gain (dB) = 9 + N*/
#define CODEC_PGA1_PGA_G      CODEC_PGA1_PGA_G_MSK
#define CODEC_PGA1_PGA_G_W(X) ((X) << CODEC_PGA1_PGA_G_POS)
#define CODEC_HPA_SD_POS      (25U)
#define CODEC_HPA_SD_MSK      (0x1UL << CODEC_HPA_SD_POS) /*!< Shutdown. Active low logic.TPA6133A2*/
#define CODEC_HPA_SD          CODEC_HPA_SD_MSK
#define CODEC_HPA_SD_W(X)     ((X) << CODEC_HPA_SD_POS)
#define CODEC_PGA2_DCEN_POS   (26U)
#define CODEC_PGA2_DCEN_MSK   (0x1UL << CODEC_PGA2_DCEN_POS) /*!< DC Servo Enable (Active Low)*/
#define CODEC_PGA2_DCEN       CODEC_PGA2_DCEN_MSK
#define CODEC_PGA2_DCEN_W(X)  ((X) << CODEC_PGA2_DCEN_POS)
#define CODEC_PGA2_ZCEN_POS   (27U)
#define CODEC_PGA2_ZCEN_MSK   (0x1UL << CODEC_PGA2_ZCEN_POS) /*!< Zero Crossing Detector Enable (Active High)*/
#define CODEC_PGA2_ZCEN       CODEC_PGA2_ZCEN_MSK
#define CODEC_PGA2_ZCEN_W(X)  ((X) << CODEC_PGA2_ZCEN_POS)
#define CODEC_PGA1_DCEN_POS   (28U)
#define CODEC_PGA1_DCEN_MSK   (0x1UL << CODEC_PGA1_DCEN_POS) /*!< DC Servo Enable (Active Low)*/
#define CODEC_PGA1_DCEN       CODEC_PGA1_DCEN_MSK
#define CODEC_PGA1_DCEN_W(X)  ((X) << CODEC_PGA1_DCEN_POS)
#define CODEC_PGA1_ZCEN_POS   (29U)
#define CODEC_PGA1_ZCEN_MSK   (0x1UL << CODEC_PGA1_ZCEN_POS) /*!< Zero Crossing Detector Enable (Active High)*/
#define CODEC_PGA1_ZCEN       CODEC_PGA1_ZCEN_MSK
#define CODEC_PGA1_ZCEN_W(X)  ((X) << CODEC_PGA1_ZCEN_POS)

//FPGA_PGA_CFG1 offsetaddress : 0x0168
//FPGA_PGA_CFG1 RegResetValue : 0x00000001
#define CODEC_PGA_SDI_SEL1_POS  (0U)
#define CODEC_PGA_SDI_SEL1_MSK  (0x1UL << CODEC_PGA_SDI_SEL1_POS) /*!< pga sdi source select ,when 1, only pga1* active; when 0, only pga2* active*/
#define CODEC_PGA_SDI_SEL1      CODEC_PGA_SDI_SEL1_MSK
#define CODEC_PGA_SDI_SEL1_W(X) ((X) << CODEC_PGA_SDI_SEL1_POS)
#define CODEC_PGA2_DONE_POS     (1U)
#define CODEC_PGA2_DONE_MSK     (0x1UL << CODEC_PGA2_DONE_POS) /*!< PGA2500 SERIAL PORT trans done, after pga done is 1, if pga_start is write to 0, pga done will be 0.*/
#define CODEC_PGA2_DONE         CODEC_PGA2_DONE_MSK
#define CODEC_PGA2_DONE_W(X)    ((X) << CODEC_PGA2_DONE_POS)
#define CODEC_PGA2_GPO_D_POS    (2U)
#define CODEC_PGA2_GPO_D_MSK    (0xfUL << CODEC_PGA2_GPO_D_POS) /*!< Data for GPO.SDI*/
#define CODEC_PGA2_GPO_D        CODEC_PGA2_GPO_D_MSK
#define CODEC_PGA2_GPO_D_W(X)   ((X) << CODEC_PGA2_GPO_D_POS)

//FPGA_PGA_CFG2 offsetaddress : 0x016C
//FPGA_PGA_CFG2 RegResetValue : 0xFFFFFFFE
#define CODEC_FPGA_ADC0_SEL_POS  (0U)
#define CODEC_FPGA_ADC0_SEL_MSK  (0x1UL << CODEC_FPGA_ADC0_SEL_POS) /*!< Select data from AD0 or AD1 on FPGA default adc0*/
#define CODEC_FPGA_ADC0_SEL      CODEC_FPGA_ADC0_SEL_MSK
#define CODEC_FPGA_ADC0_SEL_W(X) ((X) << CODEC_FPGA_ADC0_SEL_POS)
#define CODEC_FPGA_ADC0_EN_POS   (1U)
#define CODEC_FPGA_ADC0_EN_MSK   (0x1UL << CODEC_FPGA_ADC0_EN_POS) /*!< ADC data is poured from FPGA or SDM, by default, from FPGA*/
#define CODEC_FPGA_ADC0_EN       CODEC_FPGA_ADC0_EN_MSK
#define CODEC_FPGA_ADC0_EN_W(X)  ((X) << CODEC_FPGA_ADC0_EN_POS)
#define CODEC_FPGA_ADC1_SEL_POS  (2U)
#define CODEC_FPGA_ADC1_SEL_MSK  (0x1UL << CODEC_FPGA_ADC1_SEL_POS) /*!< Select data from AD0 or AD1 on FPGA Default adc1*/
#define CODEC_FPGA_ADC1_SEL      CODEC_FPGA_ADC1_SEL_MSK
#define CODEC_FPGA_ADC1_SEL_W(X) ((X) << CODEC_FPGA_ADC1_SEL_POS)
#define CODEC_FPGA_ADC1_EN_POS   (3U)
#define CODEC_FPGA_ADC1_EN_MSK   (0x1UL << CODEC_FPGA_ADC1_EN_POS) /*!< ADC data is poured from FPGA or SDM, by default, from FPGA*/
#define CODEC_FPGA_ADC1_EN       CODEC_FPGA_ADC1_EN_MSK
#define CODEC_FPGA_ADC1_EN_W(X)  ((X) << CODEC_FPGA_ADC1_EN_POS)
#define CODEC_FPGA_ADC2_SEL_POS  (4U)
#define CODEC_FPGA_ADC2_SEL_MSK  (0x1UL << CODEC_FPGA_ADC2_SEL_POS) /*!< Select data from AD0 or AD1 on FPGA Default adc1*/
#define CODEC_FPGA_ADC2_SEL      CODEC_FPGA_ADC2_SEL_MSK
#define CODEC_FPGA_ADC2_SEL_W(X) ((X) << CODEC_FPGA_ADC2_SEL_POS)
#define CODEC_FPGA_ADC2_EN_POS   (5U)
#define CODEC_FPGA_ADC2_EN_MSK   (0x1UL << CODEC_FPGA_ADC2_EN_POS) /*!< ADC data is poured from FPGA or SDM, by default, from FPGA*/
#define CODEC_FPGA_ADC2_EN       CODEC_FPGA_ADC2_EN_MSK
#define CODEC_FPGA_ADC2_EN_W(X)  ((X) << CODEC_FPGA_ADC2_EN_POS)
#define CODEC_FPGA_ADC3_SEL_POS  (6U)
#define CODEC_FPGA_ADC3_SEL_MSK  (0x1UL << CODEC_FPGA_ADC3_SEL_POS) /*!< Select data from AD0 or AD1 on FPGA Default adc1*/
#define CODEC_FPGA_ADC3_SEL      CODEC_FPGA_ADC3_SEL_MSK
#define CODEC_FPGA_ADC3_SEL_W(X) ((X) << CODEC_FPGA_ADC3_SEL_POS)
#define CODEC_FPGA_ADC3_EN_POS   (7U)
#define CODEC_FPGA_ADC3_EN_MSK   (0x1UL << CODEC_FPGA_ADC3_EN_POS) /*!< ADC data is poured from FPGA or SDM, by default, from FPGA*/
#define CODEC_FPGA_ADC3_EN       CODEC_FPGA_ADC3_EN_MSK
#define CODEC_FPGA_ADC3_EN_W(X)  ((X) << CODEC_FPGA_ADC3_EN_POS)
#define CODEC_FPGA_ADC4_SEL_POS  (8U)
#define CODEC_FPGA_ADC4_SEL_MSK  (0x1UL << CODEC_FPGA_ADC4_SEL_POS) /*!< Select data from AD0 or AD1 on FPGA Default adc1*/
#define CODEC_FPGA_ADC4_SEL      CODEC_FPGA_ADC4_SEL_MSK
#define CODEC_FPGA_ADC4_SEL_W(X) ((X) << CODEC_FPGA_ADC4_SEL_POS)
#define CODEC_FPGA_ADC4_EN_POS   (9U)
#define CODEC_FPGA_ADC4_EN_MSK   (0x1UL << CODEC_FPGA_ADC4_EN_POS) /*!< ADC data is poured from FPGA or SDM, by default, from FPGA*/
#define CODEC_FPGA_ADC4_EN       CODEC_FPGA_ADC4_EN_MSK
#define CODEC_FPGA_ADC4_EN_W(X)  ((X) << CODEC_FPGA_ADC4_EN_POS)
#define CODEC_FPGA_DAC_SEL_POS   (10U)
#define CODEC_FPGA_DAC_SEL_MSK   (0x1UL << CODEC_FPGA_DAC_SEL_POS) /*!< DAC for left or right default left*/
#define CODEC_FPGA_DAC_SEL       CODEC_FPGA_DAC_SEL_MSK
#define CODEC_FPGA_DAC_SEL_W(X)  ((X) << CODEC_FPGA_DAC_SEL_POS)

//CODEC_DAC0_LIMTER offsetaddress : 0x0200
//CODEC_DAC0_LIMTER RegResetValue : 0x00000000
#define CODEC_DA0_COMPRESS_RATIO_POS (0U)
#define CODEC_DA0_COMPRESS_RATIO_MSK \
    (0x7fUL                          \
     << CODEC_DA0_COMPRESS_RATIO_POS) /*!< % 2. [compress_ratio] % Compression ratio, that is, after exceeding the limiter starting threshold, increase the compression according to the N:1 ratio. It is recommended that 2,4,8,16,32,64 % compress ratio, if input bigger than limiter threshold, start to compress the %delta data as N:1, 2,4,8,16,32,64 suggested parameter.compress_ratio = 16;*/
#define CODEC_DA0_COMPRESS_RATIO      CODEC_DA0_COMPRESS_RATIO_MSK
#define CODEC_DA0_COMPRESS_RATIO_W(X) ((X) << CODEC_DA0_COMPRESS_RATIO_POS)
#define CODEC_DA0_LIMITER_THR_POS     (7U)
#define CODEC_DA0_LIMITER_THR_MSK     (0xffffffUL << CODEC_DA0_LIMITER_THR_POS) /*!< % 1. [limiter_thr] % limiter start threshold, if this threshold is exceeded, the amplitude data will start compressing 1/2, 1/4, 1/8, 1/16, 1/32 % threshold to start limiter, limiter_thr_ratio = 1/4; parameter.limiter_thr = 2^23 * limiter_thr_ratio;*/
#define CODEC_DA0_LIMITER_THR         CODEC_DA0_LIMITER_THR_MSK
#define CODEC_DA0_LIMITER_THR_W(X)    ((X) << CODEC_DA0_LIMITER_THR_POS)
#define CODEC_DA0_LIMIT_EN_POS        (31U)
#define CODEC_DA0_LIMIT_EN_MSK        (0x1UL << CODEC_DA0_LIMIT_EN_POS) /*!< Limiter enable*/
#define CODEC_DA0_LIMIT_EN            CODEC_DA0_LIMIT_EN_MSK
#define CODEC_DA0_LIMIT_EN_W(X)       ((X) << CODEC_DA0_LIMIT_EN_POS)

//CODEC_DAC1_LIMTER offsetaddress : 0x0204
//CODEC_DAC1_LIMTER RegResetValue : 0x00000000
#define CODEC_DA1_COMPRESS_RATIO_POS (0U)
#define CODEC_DA1_COMPRESS_RATIO_MSK \
    (0x7fUL                          \
     << CODEC_DA1_COMPRESS_RATIO_POS) /*!< % 2. [compress_ratio] % Compression ratio, that is, after exceeding the limiter starting threshold, increase the compression according to the N:1 ratio. It is recommended that 2,4,8,16,32,64 % compress ratio, if input bigger than limiter threshold, start to compress the %delta data as N:1, 2,4,8,16,32,64 suggested parameter.compress_ratio = 16;*/
#define CODEC_DA1_COMPRESS_RATIO      CODEC_DA1_COMPRESS_RATIO_MSK
#define CODEC_DA1_COMPRESS_RATIO_W(X) ((X) << CODEC_DA1_COMPRESS_RATIO_POS)
#define CODEC_DA1_LIMITER_THR_POS     (7U)
#define CODEC_DA1_LIMITER_THR_MSK     (0xffffffUL << CODEC_DA1_LIMITER_THR_POS) /*!< % 1. [limiter_thr] % limiter start threshold, if this threshold is exceeded, the amplitude data will start compressing 1/2, 1/4, 1/8, 1/16, 1/32 % threshold to start limiter, limiter_thr_ratio = 1/4; parameter.limiter_thr = 2^23 * limiter_thr_ratio;*/
#define CODEC_DA1_LIMITER_THR         CODEC_DA1_LIMITER_THR_MSK
#define CODEC_DA1_LIMITER_THR_W(X)    ((X) << CODEC_DA1_LIMITER_THR_POS)
#define CODEC_DA1_LIMIT_EN_POS        (31U)
#define CODEC_DA1_LIMIT_EN_MSK        (0x1UL << CODEC_DA1_LIMIT_EN_POS) /*!< Limiter enable*/
#define CODEC_DA1_LIMIT_EN            CODEC_DA1_LIMIT_EN_MSK
#define CODEC_DA1_LIMIT_EN_W(X)       ((X) << CODEC_DA1_LIMIT_EN_POS)

//CODEC_ADC0_DIG_GAIN offsetaddress : 0x0208
//CODEC_ADC0_DIG_GAIN RegResetValue : 0x0
#define CODEC_ADC0_DST_GAIN_INDEX_POS   (0U)
#define CODEC_ADC0_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_ADC0_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_ADC0_DST_GAIN_INDEX       CODEC_ADC0_DST_GAIN_INDEX_MSK
#define CODEC_ADC0_DST_GAIN_INDEX_W(X)  ((X) << CODEC_ADC0_DST_GAIN_INDEX_POS)
#define CODEC_ADC0_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_ADC0_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_ADC0_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_ADC0_GAIN_SMOOTH_SEL      CODEC_ADC0_GAIN_SMOOTH_SEL_MSK
#define CODEC_ADC0_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_ADC0_GAIN_SMOOTH_SEL_POS)
#define CODEC_ADC0_GAIN_ENABLE_POS      (11U)
#define CODEC_ADC0_GAIN_ENABLE_MSK      (0x1UL << CODEC_ADC0_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_ADC0_GAIN_ENABLE          CODEC_ADC0_GAIN_ENABLE_MSK
#define CODEC_ADC0_GAIN_ENABLE_W(X)     ((X) << CODEC_ADC0_GAIN_ENABLE_POS)

//CODEC_ADC1_DIG_GAIN offsetaddress : 0x020C
//CODEC_ADC1_DIG_GAIN RegResetValue : 0x0
#define CODEC_ADC1_DST_GAIN_INDEX_POS   (0U)
#define CODEC_ADC1_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_ADC1_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_ADC1_DST_GAIN_INDEX       CODEC_ADC1_DST_GAIN_INDEX_MSK
#define CODEC_ADC1_DST_GAIN_INDEX_W(X)  ((X) << CODEC_ADC1_DST_GAIN_INDEX_POS)
#define CODEC_ADC1_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_ADC1_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_ADC1_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_ADC1_GAIN_SMOOTH_SEL      CODEC_ADC1_GAIN_SMOOTH_SEL_MSK
#define CODEC_ADC1_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_ADC1_GAIN_SMOOTH_SEL_POS)
#define CODEC_ADC1_GAIN_ENABLE_POS      (11U)
#define CODEC_ADC1_GAIN_ENABLE_MSK      (0x1UL << CODEC_ADC1_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_ADC1_GAIN_ENABLE          CODEC_ADC1_GAIN_ENABLE_MSK
#define CODEC_ADC1_GAIN_ENABLE_W(X)     ((X) << CODEC_ADC1_GAIN_ENABLE_POS)

//CODEC_ADC2_DIG_GAIN offsetaddress : 0x0210
//CODEC_ADC2_DIG_GAIN RegResetValue : 0x0
#define CODEC_ADC2_DST_GAIN_INDEX_POS   (0U)
#define CODEC_ADC2_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_ADC2_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_ADC2_DST_GAIN_INDEX       CODEC_ADC2_DST_GAIN_INDEX_MSK
#define CODEC_ADC2_DST_GAIN_INDEX_W(X)  ((X) << CODEC_ADC2_DST_GAIN_INDEX_POS)
#define CODEC_ADC2_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_ADC2_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_ADC2_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_ADC2_GAIN_SMOOTH_SEL      CODEC_ADC2_GAIN_SMOOTH_SEL_MSK
#define CODEC_ADC2_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_ADC2_GAIN_SMOOTH_SEL_POS)
#define CODEC_ADC2_GAIN_ENABLE_POS      (11U)
#define CODEC_ADC2_GAIN_ENABLE_MSK      (0x1UL << CODEC_ADC2_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_ADC2_GAIN_ENABLE          CODEC_ADC2_GAIN_ENABLE_MSK
#define CODEC_ADC2_GAIN_ENABLE_W(X)     ((X) << CODEC_ADC2_GAIN_ENABLE_POS)

//CODEC_ADC3_DIG_GAIN offsetaddress : 0x0214
//CODEC_ADC3_DIG_GAIN RegResetValue : 0x0
#define CODEC_ADC3_DST_GAIN_INDEX_POS   (0U)
#define CODEC_ADC3_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_ADC3_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_ADC3_DST_GAIN_INDEX       CODEC_ADC3_DST_GAIN_INDEX_MSK
#define CODEC_ADC3_DST_GAIN_INDEX_W(X)  ((X) << CODEC_ADC3_DST_GAIN_INDEX_POS)
#define CODEC_ADC3_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_ADC3_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_ADC3_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_ADC3_GAIN_SMOOTH_SEL      CODEC_ADC3_GAIN_SMOOTH_SEL_MSK
#define CODEC_ADC3_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_ADC3_GAIN_SMOOTH_SEL_POS)
#define CODEC_ADC3_GAIN_ENABLE_POS      (11U)
#define CODEC_ADC3_GAIN_ENABLE_MSK      (0x1UL << CODEC_ADC3_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_ADC3_GAIN_ENABLE          CODEC_ADC3_GAIN_ENABLE_MSK
#define CODEC_ADC3_GAIN_ENABLE_W(X)     ((X) << CODEC_ADC3_GAIN_ENABLE_POS)

//CODEC_ADC4_DIG_GAIN offsetaddress : 0x0218
//CODEC_ADC4_DIG_GAIN RegResetValue : 0x0
#define CODEC_ADC4_DST_GAIN_INDEX_POS   (0U)
#define CODEC_ADC4_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_ADC4_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_ADC4_DST_GAIN_INDEX       CODEC_ADC4_DST_GAIN_INDEX_MSK
#define CODEC_ADC4_DST_GAIN_INDEX_W(X)  ((X) << CODEC_ADC4_DST_GAIN_INDEX_POS)
#define CODEC_ADC4_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_ADC4_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_ADC4_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_ADC4_GAIN_SMOOTH_SEL      CODEC_ADC4_GAIN_SMOOTH_SEL_MSK
#define CODEC_ADC4_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_ADC4_GAIN_SMOOTH_SEL_POS)
#define CODEC_ADC4_GAIN_ENABLE_POS      (11U)
#define CODEC_ADC4_GAIN_ENABLE_MSK      (0x1UL << CODEC_ADC4_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_ADC4_GAIN_ENABLE          CODEC_ADC4_GAIN_ENABLE_MSK
#define CODEC_ADC4_GAIN_ENABLE_W(X)     ((X) << CODEC_ADC4_GAIN_ENABLE_POS)

//CODEC_DAC0_DIG_GAIN offsetaddress : 0x021C
//CODEC_DAC0_DIG_GAIN RegResetValue : 0x0
#define CODEC_DA0_DST_GAIN_INDEX_POS   (0U)
#define CODEC_DA0_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_DA0_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_DA0_DST_GAIN_INDEX       CODEC_DA0_DST_GAIN_INDEX_MSK
#define CODEC_DA0_DST_GAIN_INDEX_W(X)  ((X) << CODEC_DA0_DST_GAIN_INDEX_POS)
#define CODEC_DA0_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_DA0_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_DA0_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_DA0_GAIN_SMOOTH_SEL      CODEC_DA0_GAIN_SMOOTH_SEL_MSK
#define CODEC_DA0_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_DA0_GAIN_SMOOTH_SEL_POS)
#define CODEC_DA0_GAIN_ENABLE_POS      (11U)
#define CODEC_DA0_GAIN_ENABLE_MSK      (0x1UL << CODEC_DA0_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_DA0_GAIN_ENABLE          CODEC_DA0_GAIN_ENABLE_MSK
#define CODEC_DA0_GAIN_ENABLE_W(X)     ((X) << CODEC_DA0_GAIN_ENABLE_POS)

//CODEC_DAC1_DIG_GAIN offsetaddress : 0x0220
//CODEC_DAC1_DIG_GAIN RegResetValue : 0x0
#define CODEC_DA1_DST_GAIN_INDEX_POS   (0U)
#define CODEC_DA1_DST_GAIN_INDEX_MSK   (0xffUL << CODEC_DA1_DST_GAIN_INDEX_POS) /*!< [dst_gain_index]  the gain to update, this is index  [0,1,2,3,.....255] ->[-70dB,...,0dB,...+25dB], index 187 -> 0dB*/
#define CODEC_DA1_DST_GAIN_INDEX       CODEC_DA1_DST_GAIN_INDEX_MSK
#define CODEC_DA1_DST_GAIN_INDEX_W(X)  ((X) << CODEC_DA1_DST_GAIN_INDEX_POS)
#define CODEC_DA1_GAIN_SMOOTH_SEL_POS  (8U)
#define CODEC_DA1_GAIN_SMOOTH_SEL_MSK  (0x7UL << CODEC_DA1_GAIN_SMOOTH_SEL_POS) /*!< [gain_smooth] smooth factor while gain update, [1,2,4,8,16,32, 64,128] 0~7 corresponds from left to right in sequence*/
#define CODEC_DA1_GAIN_SMOOTH_SEL      CODEC_DA1_GAIN_SMOOTH_SEL_MSK
#define CODEC_DA1_GAIN_SMOOTH_SEL_W(X) ((X) << CODEC_DA1_GAIN_SMOOTH_SEL_POS)
#define CODEC_DA1_GAIN_ENABLE_POS      (11U)
#define CODEC_DA1_GAIN_ENABLE_MSK      (0x1UL << CODEC_DA1_GAIN_ENABLE_POS) /*!< The default is the new version, the old version has been deleted rev*/
#define CODEC_DA1_GAIN_ENABLE          CODEC_DA1_GAIN_ENABLE_MSK
#define CODEC_DA1_GAIN_ENABLE_W(X)     ((X) << CODEC_DA1_GAIN_ENABLE_POS)

typedef struct {
    volatile uint32_t TSING_CODEC_CFG_0;         //offsetaddress : 0x0000
    volatile uint32_t TSING_CODEC_CFG_1;         //offsetaddress : 0x0004
    volatile uint32_t TSING_CODEC_CFG_2;         //offsetaddress : 0x0008
    volatile uint32_t TSING_CODEC_CFG_3;         //offsetaddress : 0x000C
    volatile uint32_t TSING_CODEC_CFG_4;         //offsetaddress : 0x0010
    volatile uint32_t TSING_CODEC_CFG_5;         //offsetaddress : 0x0014
    volatile uint32_t TSING_CODEC_CFG_6;         //offsetaddress : 0x0018
    volatile uint32_t TSING_CODEC_CFG_7;         //offsetaddress : 0x001C
    volatile uint32_t TSING_CODEC_CFG_8;         //offsetaddress : 0x0020
    volatile uint32_t TSING_CODEC_CFG_9;         //offsetaddress : 0x0024
    volatile uint32_t TSING_CODEC_CFG_10;        //offsetaddress : 0x0028
    volatile uint32_t TSING_CODEC_CFG_11;        //offsetaddress : 0x002C
    volatile uint32_t TSING_CODEC_CFG_12;        //offsetaddress : 0x0030
    volatile uint32_t TSING_CODEC_CFG_13;        //offsetaddress : 0x0034
    volatile uint32_t TSING_CODEC_CFG_14;        //offsetaddress : 0x0038
    volatile uint32_t TSING_CODEC_CFG_15;        //offsetaddress : 0x003C
    volatile uint32_t TSING_CODEC_CFG_16;        //offsetaddress : 0x0040
    volatile uint32_t TSING_CODEC_CFG_17;        //offsetaddress : 0x0044
    volatile uint32_t TSING_CODEC_CFG_18;        //offsetaddress : 0x0048
    volatile uint32_t TSING_CODEC_CFG_19;        //offsetaddress : 0x004C
    volatile uint32_t TSING_CODEC_ADC_DMA0_DATA; //offsetaddress : 0x0050
    volatile uint32_t TSING_CODEC_ADC_DMA1_DATA; //offsetaddress : 0x0054
    volatile uint32_t TSING_CODEC_DAC0_DMA_DATA; //offsetaddress : 0x0058
    volatile uint32_t TSING_CODEC_DAC1_DMA_DATA; //offsetaddress : 0x005C
    volatile uint32_t TSING_CODEC_DAC0_PA_DATA;  //offsetaddress : 0x0060
    volatile uint32_t TSING_CODEC_DAC0_PB_DATA;  //offsetaddress : 0x0064
    volatile uint32_t TSING_CODEC_DAC0_PC_DATA;  //offsetaddress : 0x0068
    volatile uint32_t TSING_CODEC_DAC1_PA_DATA;  //offsetaddress : 0x006C
    volatile uint32_t TSING_CODEC_DAC1_PB_DATA;  //offsetaddress : 0x0070
    volatile uint32_t TSING_CODEC_DAC1_PC_DATA;  //offsetaddress : 0x0074
    volatile uint32_t TSING_CODEC_FIFO_STATUS0;  //offsetaddress : 0x0078
    volatile uint32_t TSING_CODEC_FIFO_STATUS1;  //offsetaddress : 0x007C
    volatile uint32_t TSING_CODEC_FIFO_STATUS2;  //offsetaddress : 0x0080
    volatile uint32_t TSING_CODEC_FIFO_STATUS3;  //offsetaddress : 0x0084
    volatile uint32_t rev_0[(0x00C0 - 0x0084) / 4 - 1];
    volatile uint32_t CODEC_INTR_CTRL;    //offsetaddress : 0x00C0
    volatile uint32_t CODEC_INTR_STATUS;  //offsetaddress : 0x00C4
    volatile uint32_t CODEC_INTR_STATUS1; //offsetaddress : 0x00C8
    volatile uint32_t CODEC_INTR_CTRL1;   //offsetaddress : 0x00CC
    volatile uint32_t CODEC_DAC_CFG0;     //offsetaddress : 0x00D0
    volatile uint32_t CODEC_DAC_CFG1;     //offsetaddress : 0x00D4
    volatile uint32_t CODEC_DAC_CFG2;     //offsetaddress : 0x00D8
    volatile uint32_t CODEC_DAC_CFG3;     //offsetaddress : 0x00DC
    volatile uint32_t CODEC_DAC_CFG4;     //offsetaddress : 0x00E0
    volatile uint32_t rev_1[(0x00E8 - 0x00E0) / 4 - 1];
    volatile uint32_t CODEC_DAC_TEST1;   //offsetaddress : 0x00E8
    volatile uint32_t CODEC_DAC_TEST2;   //offsetaddress : 0x00EC
    volatile uint32_t CODEC_DEBUG_CTRL;  //offsetaddress : 0x00F0
    volatile uint32_t CODEC_DAC_BSEL;    //offsetaddress : 0x00F4
    volatile uint32_t CODEC_ADC_BSEL;    //offsetaddress : 0x00F8
    volatile uint32_t CODEC_MUSIC_LVL;   //offsetaddress : 0x00FC
    volatile uint32_t ASRC_SAVE_CLKNCNT; //offsetaddress : 0x100
    volatile uint32_t ASRC_SAVE_FINECNT; //offsetaddress : 0x104
    volatile uint32_t ASRC_SAVE_CNTL;    //offsetaddress : 0x108
    volatile uint32_t rev_2[(0x110 - 0x108) / 4 - 1];
    volatile uint32_t DAC_DCRM_CNTL;     //offsetaddress : 0x110
    volatile uint32_t DAC0_NG_CTRL_REG0; //offsetaddress : 0x0114
    volatile uint32_t DAC0_NG_CTRL_REG1; //offsetaddress : 0x0118
    volatile uint32_t DAC0_NG_CTRL_REG2; //offsetaddress : 0x011c
    volatile uint32_t DAC0_NG_CTRL_REG3; //offsetaddress : 0x0120
    volatile uint32_t DAC0_NG_CTRL_REG4; //offsetaddress : 0x0124
    volatile uint32_t DAC0_NG_CTRL_REG5; //offsetaddress : 0x0128
    volatile uint32_t rev_3[(0x0130 - 0x0128) / 4 - 1];
    volatile uint32_t DAC1_NG_CTRL_REG0; //offsetaddress : 0x0130
    volatile uint32_t DAC1_NG_CTRL_REG1; //offsetaddress : 0x0134
    volatile uint32_t DAC1_NG_CTRL_REG2; //offsetaddress : 0x0138
    volatile uint32_t DAC1_NG_CTRL_REG3; //offsetaddress : 0x013c
    volatile uint32_t DAC1_NG_CTRL_REG4; //offsetaddress : 0x0140
    volatile uint32_t DAC1_NG_CTRL_REG5; //offsetaddress : 0x0144
    volatile uint32_t rev_4[(0x014c - 0x0144) / 4 - 1];
    volatile uint32_t DAC_DMA_CTRL;     //offsetaddress : 0x014c
    volatile uint32_t CODEC_DAC_CFG5;   //offsetaddress : 0x0150
    volatile uint32_t CODEC_DAC_CFG6;   //offsetaddress : 0x0154
    volatile uint32_t BP_384FLT_FR_DLY; //offsetaddress : 0x0158
    volatile uint32_t rev_5[(0x0160 - 0x0158) / 4 - 1];
    volatile uint32_t FPGA_AD_CFG;   //offsetaddress : 0x0160
    volatile uint32_t FPGA_PGA_CFG0; //offsetaddress : 0x0164
    volatile uint32_t FPGA_PGA_CFG1; //offsetaddress : 0x0168
    volatile uint32_t FPGA_PGA_CFG2; //offsetaddress : 0x016C
    volatile uint32_t rev_6[(0x0200 - 0x016C) / 4 - 1];
    volatile uint32_t CODEC_DAC0_LIMTER;   //offsetaddress : 0x0200
    volatile uint32_t CODEC_DAC1_LIMTER;   //offsetaddress : 0x0204
    volatile uint32_t CODEC_ADC0_DIG_GAIN; //offsetaddress : 0x0208
    volatile uint32_t CODEC_ADC1_DIG_GAIN; //offsetaddress : 0x020C
    volatile uint32_t CODEC_ADC2_DIG_GAIN; //offsetaddress : 0x0210
    volatile uint32_t CODEC_ADC3_DIG_GAIN; //offsetaddress : 0x0214
    volatile uint32_t CODEC_ADC4_DIG_GAIN; //offsetaddress : 0x0218
    volatile uint32_t CODEC_DAC0_DIG_GAIN; //offsetaddress : 0x021C
    volatile uint32_t CODEC_DAC1_DIG_GAIN; //offsetaddress : 0x0220
} codec_reg_t;
#ifdef __cplusplus
}
#endif
#endif
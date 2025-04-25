/********************************************************************************************************
 * @file    hal_es8389_everest.h
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
#ifndef Everest_H
#define Everest_H

#include "hal_alsa.h" //LINUS-ALSA

extern const Alsa_Device *EVEREST;
/***** VERSION *****/
#define Everest_Revision 2.0.0.0.0418

/************************* Everest PARAMETER ******************************/

/***** Everest_MainCLK_Source *****/
#define Everest_MCLK_PIN       0
#define Everest_SCLK_PIN       1
#define Everest_MainCLK_Source Everest_SCLK_PIN

/***** Everest_ADCL_InputSel *****/
#define Everest_InputSelL_MIC1P1N    1
#define Everest_InputSelL_MIC1P_LIN1 5
#define Everest_InputSelL_MIC2P_LIN2 6
#define Everest_ADCL_InputSel        Everest_InputSelL_MIC1P1N

/***** Everest_ADCR_InputSel *****/
#define Everest_InputSelR_MIC2P2N    1
#define Everest_InputSelR_MIC2N_RIN2 5
#define Everest_InputSelR_MIC1N_RIN1 6
#define Everest_ADCR_InputSel        Everest_InputSelR_MIC2P2N

/***** Everest_ADCL_PGAGain *****/
#define Everest_ADCL_PGAGain    0 //0~15
#define Everest_ADCL_PGAGainSel Everest_ADCL_PGAGain

/***** Everest_ADCR_PGAGain *****/
#define Everest_ADCR_PGAGain    0 //0~15
#define Everest_ADCR_PGAGainSel Everest_ADCR_PGAGain

/***** Everest_ADCL_PGAGain *****/
#define Everest_ADCL_PGAGain    0 //0~15
#define Everest_ADCL_PGAGainSel Everest_ADCL_PGAGain

/***** Everest_ADCR_PGAGain *****/
#define Everest_ADCR_PGAGain    0 //0~15
#define Everest_ADCR_PGAGainSel Everest_ADCR_PGAGain

#define Everest_RATIO_MCLK_LRCK RATIO_MCLK_LRCK_256

/************************* Everest REGISTER MAP ******************************/
#define Everest_Reg0x27_ADC1_Volume        0x27
#define Everest_Reg0x28_ADC2_Volume        0x28
#define Everest_Reg0x46_DAC1_Volume        0x46
#define Everest_Reg0x47_DAC2_Volume        0x47
#define Everest_Reg0x72_ADCL_Input_PGAGain 0x72
#define Everest_Reg0x73_ADCR_Input_PGAGain 0x73


#endif

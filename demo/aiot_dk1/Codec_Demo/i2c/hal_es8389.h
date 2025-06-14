/********************************************************************************************************
 * @file    hal_es8389.h
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
#ifndef ES8389_H
#define ES8389_H
#include "hal_i2c.h"
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_es8389)

#include "hal_alsa.h" //LINUS-ALSA

extern const Alsa_Device *ES8389;
/***** VERSION *****/
#define ES8389_Revision 2.1.0.0.0511

/************************* ES8389 PARAMETER ******************************/
#define I2C_ES8389_ADD 0x20
//Probe->set_dai_sysclk
#define ES8389_RATIO_MCLK_LRCK RATIO_MCLK_LRCK_32 //Everest_set_dai_sysclk
#define ES8389_FreqMCLK        512000             //Everest_set_dai_sysclk
#define ES8389_DAIFMT_FORMAT   0                  //0:IIS;    1:LJ;    2:DSPA;    7:DSPB
#define ES8389_DAIFMT_LE       3                  //0:24B;    1:20B;    2:18B;    3:16B;    4:32B
/***** ES8389 General PARAMETER *****/
#define ES8389_MainCLK_Source        Everest_SCLK_PIN //MCLK_PIN=0;SCLK_PIN=1

#define ES8389_MS_ModeSel            Everest_SlaveMode //Everest_SlaveMode=0;Everest_MasterMode=1

#define ES8389_MCLK_Invert           Everest_Invert   //Invert=1;NoInvert=0
#define ES8389_BCLK_Invert           Everest_NoInvert //Invert=1;NoInvert=0
#define ES8389_LRCK_Invert           Everest_NoInvert //Invert=1;NoInvert=0
#define ES8389_DMIC_Invert           Everest_NoInvert //INVET=1;NoInvert=0
#define ES8389_ADC1_Invert           Everest_NoInvert //Invert=1;NoInvert=0
#define ES8389_ADC2_Invert           Everest_NoInvert //Invert=1;NoInvert=0
#define ES8389_DAC1_Invert           Everest_NoInvert //Invert=1;NoInvert=0
#define ES8389_DAC2_Invert           Everest_NoInvert //Invert=1;NoInvert=0

#define ES8389_ADC1_MUTE             Everest_Unmute //Unmute=0;Mute=1
#define ES8389_ADC2_MUTE             Everest_Unmute //Unmute=0;Mute=1
#define ES8389_DAC1_MUTE             Everest_Unmute //Unmute=0;Mute=1
#define ES8389_DAC2_MUTE             Everest_Unmute //Unmute=0;Mute=1

#define ES8389_BCLK_TRI              Everest_NoTRI //NoTRI=0;TRI=1
#define ES8389_LRCK_TRI              Everest_NoTRI //NoTRI=0;TRI=1
#define ES8389_ASDOUT_TRI            Everest_NoTRI //NoTRI=0;TRI=1

#define ES8389_DMICSel               Everest_OFF //ON=1;OFF=0
#define ES8389_MIX_DAC1AndADC1ToADC1 Everest_OFF //ON=1;OFF=0
#define ES8389_MIX_DAC2AndADC2ToADC2 Everest_OFF //ON=1;OFF=0

#define ES8389_MIX_DAC1AndDAC2ToDAC1 Everest_OFF //ON=1;OFF=0
#define ES8389_MIX_DAC1AndDAC2ToDAC2 Everest_OFF //ON=1;OFF=0
#define ES8389_MIX_ADC1AndDAC1ToDAC1 Everest_OFF //ON=1;OFF=0
#define ES8389_MIX_ADC2AndDAC2ToDAC2 Everest_OFF //ON=1;OFF=0
#define ES8389_LOOP_ADCToDAC         Everest_OFF //ON=1;OFF=0
#define ES8389_LOOP_DACToADC         Everest_OFF //ON=1;OFF=0

#define ES8389_SCLK_Divide           4   //1~127    .MasterMode
#define ES8389_LRCK_Divide           256 //1~4096.MasterMode

#define ES8389_ADCPTDM_SLOTSel       0  //0~7
#define ES8389_DACSTDM_SLOTSel       0  //0~7
#define ES8389_ADCL_PGAGainSel       11 //0~15
#define ES8389_ADCR_PGAGainSel       11 //0~15
#define ES8389_ADC_DMICGainSel       0  //0~15

/***** ES8389_TDMSel *****/
#define ES8389_TDM_OFF     0
#define ES8389_TDM_ON_PTDM 1
#define ES8389_TDM_ON_STDM 2
#define ES8389_TDMSel      ES8389_TDM_OFF

/***** ES8389_ADCL_InputSel *****/
#define ES8389_InputSelL_MIC1P1N    1
#define ES8389_InputSelL_MIC1P_LIN1 5
#define ES8389_InputSelL_MIC2P_LIN2 6
#define ES8389_ADCL_InputSel        ES8389_InputSelL_MIC1P1N

/***** ES8389_ADCR_InputSel *****/
#define ES8389_InputSelR_MIC2P2N    1
#define ES8389_InputSelR_MIC2N_RIN2 5
#define ES8389_InputSelR_MIC1N_RIN1 6
#define ES8389_ADCR_InputSel        ES8389_InputSelR_MIC2P2N

/************************* ES8389 REGISTER MAP ******************************/
#define ES8389_Reg0x01_CLKTRI_MSMode      0x01
#define ES8389_Reg0x02_CLKInvert          0x02
#define ES8389_Reg0x0B_SCLKDivide         0x0B
#define ES8389_Reg0x0C_MSTFMT_LRCKDivideH 0x0C
#define ES8389_Reg0x0D_LRCKDivideL        0x0D
#define ES8389_Reg0x20_ADCFMT_ADCMUTE     0x20
#define ES8389_Reg0x23_DMICSel_TDMSel     0x23
#define ES8389_Reg0x24_ADCInvert          0x25
#define ES8389_Reg0x25_ADCInvert          0x25
#define ES8389_Reg0x26_DMIC_Volume        0x26
#define ES8389_Reg0x27_ADC1_Volume        0x27
#define ES8389_Reg0x28_ADC2_Volume        0x28
#define ES8389_Reg0x2A_ADCPTDM_SLOTSel    0x2A
#define ES8389_Reg0x31_ADCMix             0x31
#define ES8389_Reg0x40_DACFMT_DACMUTE     0x40
#define ES8389_Reg0x44_DACMix             0x44
#define ES8389_Reg0x45_DACInvert          0x45
#define ES8389_Reg0x46_DAC1_Volume        0x46
#define ES8389_Reg0x47_DAC2_Volume        0x47
#define ES8389_Reg0x48_ADC2DAC_Volume     0x48
#define ES8389_Reg0x49_DACSTDM_SLOTSel    0x49
#define ES8389_Reg0x6D_DMICSel            0x6D
#define ES8389_Reg0x72_ADCL_Input_PGAGain 0x72
#define ES8389_Reg0x73_ADCR_Input_PGAGain 0x73
#define ES8389_Reg0xF0_LOOP               0xF0

void hal_es8389_init(void);
void Everest_mute(uint8_t mute);

#endif
#endif

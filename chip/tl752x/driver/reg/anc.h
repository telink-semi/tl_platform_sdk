/*******************************************************************************************************
 *
 * @file    anc.h
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
#ifndef __ANC_H__
#define __ANC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//ANC_L_CTL offsetaddress : 0x0000
//ANC_L_CTL RegResetValue : 0x0000000
#define ANC_AL_ADC_MAP_POS            (0U)
#define ANC_AL_ADC_MAP_MSK            (0x7UL << ANC_AL_ADC_MAP_POS) /*!< 3-channel ADC input mapping relationship control:*/
#define ANC_AL_ADC_MAP                ANC_AL_ADC_MAP_MSK
#define ANC_AL_ADC_MAP_W(X)           ((X) << ANC_AL_ADC_MAP_POS)
#define ANC_AL_MUSIC_RATE_POS         (4U)
#define ANC_AL_MUSIC_RATE_MSK         (0x3UL << ANC_AL_MUSIC_RATE_POS) /*!< ANC audio input signal rate control:*/
#define ANC_AL_MUSIC_RATE             ANC_AL_MUSIC_RATE_MSK
#define ANC_AL_MUSIC_RATE_W(X)        ((X) << ANC_AL_MUSIC_RATE_POS)
#define ANC_AL_ANC_RATE_POS           (6U)
#define ANC_AL_ANC_RATE_MSK           (0x3UL << ANC_AL_ANC_RATE_POS) /*!< ANC operating rate control:*/
#define ANC_AL_ANC_RATE               ANC_AL_ANC_RATE_MSK
#define ANC_AL_ANC_RATE_W(X)          ((X) << ANC_AL_ANC_RATE_POS)
#define ANC_AL_PHN_RATE_POS           (8U)
#define ANC_AL_PHN_RATE_MSK           (0x1UL << ANC_AL_PHN_RATE_POS) /*!< Dual-machine noise reduction output rate control:*/
#define ANC_AL_PHN_RATE               ANC_AL_PHN_RATE_MSK
#define ANC_AL_PHN_RATE_W(X)          ((X) << ANC_AL_PHN_RATE_POS)
#define ANC_AL_DIG_EQ_EN_POS          (9U)
#define ANC_AL_DIG_EQ_EN_MSK          (0x1UL << ANC_AL_DIG_EQ_EN_POS) /*!< Digital Equalization IIR Filter Enable, Highly Effective*/
#define ANC_AL_DIG_EQ_EN              ANC_AL_DIG_EQ_EN_MSK
#define ANC_AL_DIG_EQ_EN_W(X)         ((X) << ANC_AL_DIG_EQ_EN_POS)
#define ANC_AL_ANC_FB_EN_POS          (10U)
#define ANC_AL_ANC_FB_EN_MSK          (0x1UL << ANC_AL_ANC_FB_EN_POS) /*!< Feedback ANC IIR filter enables high efficiency*/
#define ANC_AL_ANC_FB_EN              ANC_AL_ANC_FB_EN_MSK
#define ANC_AL_ANC_FB_EN_W(X)         ((X) << ANC_AL_ANC_FB_EN_POS)
#define ANC_AL_ANC_FF_EN_POS          (11U)
#define ANC_AL_ANC_FF_EN_MSK          (0x1UL << ANC_AL_ANC_FF_EN_POS) /*!< Feedforward ANC IIR filter enabled, highly effective*/
#define ANC_AL_ANC_FF_EN              ANC_AL_ANC_FF_EN_MSK
#define ANC_AL_ANC_FF_EN_W(X)         ((X) << ANC_AL_ANC_FF_EN_POS)
#define ANC_AL_PHN_SC_EN_POS          (12U)
#define ANC_AL_PHN_SC_EN_MSK          (0x1UL << ANC_AL_PHN_SC_EN_POS) /*!< Sanmai noise reduction (left ear) sc path extraction enables, highly effective*/
#define ANC_AL_PHN_SC_EN              ANC_AL_PHN_SC_EN_MSK
#define ANC_AL_PHN_SC_EN_W(X)         ((X) << ANC_AL_PHN_SC_EN_POS)
#define ANC_AL_PHN_MN_EN_POS          (13U)
#define ANC_AL_PHN_MN_EN_MSK          (0x1UL << ANC_AL_PHN_MN_EN_POS) /*!< Sanmai noise reduction (left ear) mn path extraction enables, highly effective*/
#define ANC_AL_PHN_MN_EN              ANC_AL_PHN_MN_EN_MSK
#define ANC_AL_PHN_MN_EN_W(X)         ((X) << ANC_AL_PHN_MN_EN_POS)
#define ANC_AL_MUSIC_96K_EN_POS       (14U)
#define ANC_AL_MUSIC_96K_EN_MSK       (0x1UL << ANC_AL_MUSIC_96K_EN_POS) /*!< 96k music playback rate enable:*/
#define ANC_AL_MUSIC_96K_EN           ANC_AL_MUSIC_96K_EN_MSK
#define ANC_AL_MUSIC_96K_EN_W(X)      ((X) << ANC_AL_MUSIC_96K_EN_POS)
#define ANC_AL_SB_EN_POS              (15U)
#define ANC_AL_SB_EN_MSK              (0x1UL << ANC_AL_SB_EN_POS) /*!< Feedback secondary channel cascade IIR filter bank enable:*/
#define ANC_AL_SB_EN                  ANC_AL_SB_EN_MSK
#define ANC_AL_SB_EN_W(X)             ((X) << ANC_AL_SB_EN_POS)
#define ANC_AL_ENABLE_POS             (16U)
#define ANC_AL_ENABLE_MSK             (0x1UL << ANC_AL_ENABLE_POS) /*!< Total enable, high valid, low reset internal signal*/
#define ANC_AL_ENABLE                 ANC_AL_ENABLE_MSK
#define ANC_AL_ENABLE_W(X)            ((X) << ANC_AL_ENABLE_POS)
#define ANC_AL_SB_FB_EN_POS           (18U)
#define ANC_AL_SB_FB_EN_MSK           (0x1UL << ANC_AL_SB_FB_EN_POS) /*!< Enable the output of the feedback secondary channel to cancel the input of the feedback ANC:*/
#define ANC_AL_SB_FB_EN               ANC_AL_SB_FB_EN_MSK
#define ANC_AL_SB_FB_EN_W(X)          ((X) << ANC_AL_SB_FB_EN_POS)
#define ANC_AL_MUSIC_SB_EN_POS        (19U)
#define ANC_AL_MUSIC_SB_EN_MSK        (0x1UL << ANC_AL_MUSIC_SB_EN_POS) /*!< Enable feedback secondary channel IIR filter bank to compensate for music signals:*/
#define ANC_AL_MUSIC_SB_EN            ANC_AL_MUSIC_SB_EN_MSK
#define ANC_AL_MUSIC_SB_EN_W(X)       ((X) << ANC_AL_MUSIC_SB_EN_POS)
#define ANC_AL_DWN_FB_SR_POS          (20U)
#define ANC_AL_DWN_FB_SR_MSK          (0x1UL << ANC_AL_DWN_FB_SR_POS) /*!< Adaptive ANC&#39;s feedback path downsampling and decimation filter input control:*/
#define ANC_AL_DWN_FB_SR              ANC_AL_DWN_FB_SR_MSK
#define ANC_AL_DWN_FB_SR_W(X)         ((X) << ANC_AL_DWN_FB_SR_POS)
#define ANC_AL_PHN_RATE2_POS          (21U)
#define ANC_AL_PHN_RATE2_MSK          (0x1UL << ANC_AL_PHN_RATE2_POS) /*!< Dual-machine noise reduction output rate control:*/
#define ANC_AL_PHN_RATE2              ANC_AL_PHN_RATE2_MSK
#define ANC_AL_PHN_RATE2_W(X)         ((X) << ANC_AL_PHN_RATE2_POS)
#define ANC_AL_PORT0_SR_POS           (22U)
#define ANC_AL_PORT0_SR_MSK           (0x7UL << ANC_AL_PORT0_SR_POS) /*!< ADC0 port multiplexing control*/
#define ANC_AL_PORT0_SR               ANC_AL_PORT0_SR_MSK
#define ANC_AL_PORT0_SR_W(X)          ((X) << ANC_AL_PORT0_SR_POS)
#define ANC_AL_PORT1_SR_POS           (25U)
#define ANC_AL_PORT1_SR_MSK           (0x3UL << ANC_AL_PORT1_SR_POS) /*!< ADC1 port multiplexing control*/
#define ANC_AL_PORT1_SR               ANC_AL_PORT1_SR_MSK
#define ANC_AL_PORT1_SR_W(X)          ((X) << ANC_AL_PORT1_SR_POS)
#define ANC_AL_BYPASS_WF_POS          (27U)
#define ANC_AL_BYPASS_WF_MSK          (0x1UL << ANC_AL_BYPASS_WF_POS) /*!< IIR filter bank input and output short-circuit control of feedforward ANC path*/
#define ANC_AL_BYPASS_WF              ANC_AL_BYPASS_WF_MSK
#define ANC_AL_BYPASS_WF_W(X)         ((X) << ANC_AL_BYPASS_WF_POS)
#define ANC_AL_BYPASS_HF_POS          (28U)
#define ANC_AL_BYPASS_HF_MSK          (0x1UL << ANC_AL_BYPASS_HF_POS) /*!< FIR filter input and output short-circuit control of feedforward ANC path*/
#define ANC_AL_BYPASS_HF              ANC_AL_BYPASS_HF_MSK
#define ANC_AL_BYPASS_HF_W(X)         ((X) << ANC_AL_BYPASS_HF_POS)
#define ANC_AL_PHN_MN_ADP_BYPASS_POS  (29U)
#define ANC_AL_PHN_MN_ADP_BYPASS_MSK  (0x1UL << ANC_AL_PHN_MN_ADP_BYPASS_POS) /*!< Sanmai noise reduction (left ear) mn path downsampling bypass enable, highly effective*/
#define ANC_AL_PHN_MN_ADP_BYPASS      ANC_AL_PHN_MN_ADP_BYPASS_MSK
#define ANC_AL_PHN_MN_ADP_BYPASS_W(X) ((X) << ANC_AL_PHN_MN_ADP_BYPASS_POS)
#define ANC_AL_PHN_SC_ADP_BYPASS_POS  (30U)
#define ANC_AL_PHN_SC_ADP_BYPASS_MSK  (0x1UL << ANC_AL_PHN_SC_ADP_BYPASS_POS) /*!< Sanmai noise reduction (left ear) Sc path downsampling bypass enable, highly effective*/
#define ANC_AL_PHN_SC_ADP_BYPASS      ANC_AL_PHN_SC_ADP_BYPASS_MSK
#define ANC_AL_PHN_SC_ADP_BYPASS_W(X) ((X) << ANC_AL_PHN_SC_ADP_BYPASS_POS)

//ANC_L_RSSI_SIZE0 offsetaddress : 0x0004
//ANC_L_RSSI_SIZE0 RegResetValue : 0x0000000
#define ANC_AL_RSSI3_SIZE_POS  (0U)
#define ANC_AL_RSSI3_SIZE_MSK  (0xffUL << ANC_AL_RSSI3_SIZE_POS) /*!< Observation length win3_size when calculating RSSI;*/
#define ANC_AL_RSSI3_SIZE      ANC_AL_RSSI3_SIZE_MSK
#define ANC_AL_RSSI3_SIZE_W(X) ((X) << ANC_AL_RSSI3_SIZE_POS)
#define ANC_AL_RSSI2_SIZE_POS  (8U)
#define ANC_AL_RSSI2_SIZE_MSK  (0xffUL << ANC_AL_RSSI2_SIZE_POS) /*!< Observation length win2_size when calculating RSSI;*/
#define ANC_AL_RSSI2_SIZE      ANC_AL_RSSI2_SIZE_MSK
#define ANC_AL_RSSI2_SIZE_W(X) ((X) << ANC_AL_RSSI2_SIZE_POS)
#define ANC_AL_RSSI1_SIZE_POS  (16U)
#define ANC_AL_RSSI1_SIZE_MSK  (0xffUL << ANC_AL_RSSI1_SIZE_POS) /*!< Observation length win1_size when calculating RSSI;*/
#define ANC_AL_RSSI1_SIZE      ANC_AL_RSSI1_SIZE_MSK
#define ANC_AL_RSSI1_SIZE_W(X) ((X) << ANC_AL_RSSI1_SIZE_POS)
#define ANC_AL_RSSI0_SIZE_POS  (24U)
#define ANC_AL_RSSI0_SIZE_MSK  (0xffUL << ANC_AL_RSSI0_SIZE_POS) /*!< Observation length win0_size when calculating RSSI;*/
#define ANC_AL_RSSI0_SIZE      ANC_AL_RSSI0_SIZE_MSK
#define ANC_AL_RSSI0_SIZE_W(X) ((X) << ANC_AL_RSSI0_SIZE_POS)

//ANC_L_RSSI_SIZE1 offsetaddress : 0x0008
//ANC_L_RSSI_SIZE1 RegResetValue : 0x0000000
#define ANC_AL_RSSI4_SIZE_POS  (0U)
#define ANC_AL_RSSI4_SIZE_MSK  (0xffUL << ANC_AL_RSSI4_SIZE_POS) /*!< Set the observation length win4_size when calculating RSSI for feedback ANC input noise;*/
#define ANC_AL_RSSI4_SIZE      ANC_AL_RSSI4_SIZE_MSK
#define ANC_AL_RSSI4_SIZE_W(X) ((X) << ANC_AL_RSSI4_SIZE_POS)
#define ANC_AL_RSSI_SEL_POS    (8U)
#define ANC_AL_RSSI_SEL_MSK    (0xffUL << ANC_AL_RSSI_SEL_POS) /*!< rssi input selection*/
#define ANC_AL_RSSI_SEL        ANC_AL_RSSI_SEL_MSK
#define ANC_AL_RSSI_SEL_W(X)   ((X) << ANC_AL_RSSI_SEL_POS)

//ANC_L_DATAPATH_SEL offsetaddress : 0x000C
//ANC_L_DATAPATH_SEL RegResetValue : 0x0000000
#define ANC_AL_ANC_DATAPATH_EN0_POS  (0U)
#define ANC_AL_ANC_DATAPATH_EN0_MSK  (0x1UL << ANC_AL_ANC_DATAPATH_EN0_POS) /*!< ADC0 FIFO input selection*/
#define ANC_AL_ANC_DATAPATH_EN0      ANC_AL_ANC_DATAPATH_EN0_MSK
#define ANC_AL_ANC_DATAPATH_EN0_W(X) ((X) << ANC_AL_ANC_DATAPATH_EN0_POS)
#define ANC_AL_ANC_DATAPATH_EN1_POS  (1U)
#define ANC_AL_ANC_DATAPATH_EN1_MSK  (0x1UL << ANC_AL_ANC_DATAPATH_EN1_POS) /*!< Input selection for ADC1 FIFO*/
#define ANC_AL_ANC_DATAPATH_EN1      ANC_AL_ANC_DATAPATH_EN1_MSK
#define ANC_AL_ANC_DATAPATH_EN1_W(X) ((X) << ANC_AL_ANC_DATAPATH_EN1_POS)
#define ANC_AL_ANC_DATAPATH_EN2_POS  (2U)
#define ANC_AL_ANC_DATAPATH_EN2_MSK  (0x1UL << ANC_AL_ANC_DATAPATH_EN2_POS) /*!< Input selection of DAC path*/
#define ANC_AL_ANC_DATAPATH_EN2      ANC_AL_ANC_DATAPATH_EN2_MSK
#define ANC_AL_ANC_DATAPATH_EN2_W(X) ((X) << ANC_AL_ANC_DATAPATH_EN2_POS)
#define ANC_AL_ANC_ADC0_DELAY_POS    (3U)
#define ANC_AL_ANC_ADC0_DELAY_MSK    (0x1UL << ANC_AL_ANC_ADC0_DELAY_POS) /*!< ADC0 input delay (4 codec cock cycles) enabled*/
#define ANC_AL_ANC_ADC0_DELAY        ANC_AL_ANC_ADC0_DELAY_MSK
#define ANC_AL_ANC_ADC0_DELAY_W(X)   ((X) << ANC_AL_ANC_ADC0_DELAY_POS)
#define ANC_AL_ANC_ADC1_DELAY_POS    (4U)
#define ANC_AL_ANC_ADC1_DELAY_MSK    (0x1UL << ANC_AL_ANC_ADC1_DELAY_POS) /*!< ADC1 input delay (3 codec cock cycles) enabled*/
#define ANC_AL_ANC_ADC1_DELAY        ANC_AL_ANC_ADC1_DELAY_MSK
#define ANC_AL_ANC_ADC1_DELAY_W(X)   ((X) << ANC_AL_ANC_ADC1_DELAY_POS)
#define ANC_AL_ANC_ADC2_DELAY_POS    (5U)
#define ANC_AL_ANC_ADC2_DELAY_MSK    (0x1UL << ANC_AL_ANC_ADC2_DELAY_POS) /*!< ADC2 input delay (2 codec cock cycles) enabled*/
#define ANC_AL_ANC_ADC2_DELAY        ANC_AL_ANC_ADC2_DELAY_MSK
#define ANC_AL_ANC_ADC2_DELAY_W(X)   ((X) << ANC_AL_ANC_ADC2_DELAY_POS)
#define ANC_AL_ANC_DATAPATH_EN3_POS  (7U)
#define ANC_AL_ANC_DATAPATH_EN3_MSK  (0x1UL << ANC_AL_ANC_DATAPATH_EN3_POS) /*!< Input selection of ADC2 path*/
#define ANC_AL_ANC_DATAPATH_EN3      ANC_AL_ANC_DATAPATH_EN3_MSK
#define ANC_AL_ANC_DATAPATH_EN3_W(X) ((X) << ANC_AL_ANC_DATAPATH_EN3_POS)
#define ANC_AL_ANC_ADC3_DELAY_POS    (8U)
#define ANC_AL_ANC_ADC3_DELAY_MSK    (0x1UL << ANC_AL_ANC_ADC3_DELAY_POS) /*!< ADC3 input delay (2 codec cock cycles) enabled*/
#define ANC_AL_ANC_ADC3_DELAY        ANC_AL_ANC_ADC3_DELAY_MSK
#define ANC_AL_ANC_ADC3_DELAY_W(X)   ((X) << ANC_AL_ANC_ADC3_DELAY_POS)
#define ANC_AL_ANC_ADC4_DELAY_POS    (9U)
#define ANC_AL_ANC_ADC4_DELAY_MSK    (0x1UL << ANC_AL_ANC_ADC4_DELAY_POS) /*!< ADC4 input delay (2 codec cock cycles) enabled*/
#define ANC_AL_ANC_ADC4_DELAY        ANC_AL_ANC_ADC4_DELAY_MSK
#define ANC_AL_ANC_ADC4_DELAY_W(X)   ((X) << ANC_AL_ANC_ADC4_DELAY_POS)

//ANC_L_CTL2 offsetaddress : 0x0010
//ANC_L_CTL2 RegResetValue : 0x0000000
#define ANC_AL_ADC_MN_MAP_POS  (0U)
#define ANC_AL_ADC_MN_MAP_MSK  (0x7UL << ANC_AL_ADC_MN_MAP_POS) /*!< MN path selection ADC source*/
#define ANC_AL_ADC_MN_MAP      ANC_AL_ADC_MN_MAP_MSK
#define ANC_AL_ADC_MN_MAP_W(X) ((X) << ANC_AL_ADC_MN_MAP_POS)
#define ANC_AL_ADC_SC_MAP_POS  (3U)
#define ANC_AL_ADC_SC_MAP_MSK  (0x7UL << ANC_AL_ADC_SC_MAP_POS) /*!< Sc path selection ADC source*/
#define ANC_AL_ADC_SC_MAP      ANC_AL_ADC_SC_MAP_MSK
#define ANC_AL_ADC_SC_MAP_W(X) ((X) << ANC_AL_ADC_SC_MAP_POS)
#define ANC_AL_ADC_FF_MAP_POS  (6U)
#define ANC_AL_ADC_FF_MAP_MSK  (0x7UL << ANC_AL_ADC_FF_MAP_POS) /*!< ff path selection ADC source*/
#define ANC_AL_ADC_FF_MAP      ANC_AL_ADC_FF_MAP_MSK
#define ANC_AL_ADC_FF_MAP_W(X) ((X) << ANC_AL_ADC_FF_MAP_POS)
#define ANC_AL_ADC_FB_MAP_POS  (9U)
#define ANC_AL_ADC_FB_MAP_MSK  (0x7UL << ANC_AL_ADC_FB_MAP_POS) /*!< FB path selection ADC source*/
#define ANC_AL_ADC_FB_MAP      ANC_AL_ADC_FB_MAP_MSK
#define ANC_AL_ADC_FB_MAP_W(X) ((X) << ANC_AL_ADC_FB_MAP_POS)
#define ANC_AL_ADC_CLK_EN_POS  (12U)
#define ANC_AL_ADC_CLK_EN_MSK  (0x1UL << ANC_AL_ADC_CLK_EN_POS) /*!< al_adc_clk_en clock enable*/
#define ANC_AL_ADC_CLK_EN      ANC_AL_ADC_CLK_EN_MSK
#define ANC_AL_ADC_CLK_EN_W(X) ((X) << ANC_AL_ADC_CLK_EN_POS)

//ANC_L_RSSI_RSLT0 offsetaddress : 0x0400
//ANC_L_RSSI_RSLT0 RegResetValue : 0x0000000
#define ANC_AL_RSSI3_DB_RAW_POS  (0U)
#define ANC_AL_RSSI3_DB_RAW_MSK  (0xffUL << ANC_AL_RSSI3_DB_RAW_POS) /*!< Feedforward ANC input noise intensity, unit is dB*/
#define ANC_AL_RSSI3_DB_RAW      ANC_AL_RSSI3_DB_RAW_MSK
#define ANC_AL_RSSI3_DB_RAW_W(X) ((X) << ANC_AL_RSSI3_DB_RAW_POS)
#define ANC_AL_RSSI2_DB_RAW_POS  (8U)
#define ANC_AL_RSSI2_DB_RAW_MSK  (0xffUL << ANC_AL_RSSI2_DB_RAW_POS) /*!< ANC output signal strength, unit is dB*/
#define ANC_AL_RSSI2_DB_RAW      ANC_AL_RSSI2_DB_RAW_MSK
#define ANC_AL_RSSI2_DB_RAW_W(X) ((X) << ANC_AL_RSSI2_DB_RAW_POS)
#define ANC_AL_RSSI1_DB_RAW_POS  (16U)
#define ANC_AL_RSSI1_DB_RAW_MSK  (0xffUL << ANC_AL_RSSI1_DB_RAW_POS) /*!< Feedback ANC output signal strength, unit is dB*/
#define ANC_AL_RSSI1_DB_RAW      ANC_AL_RSSI1_DB_RAW_MSK
#define ANC_AL_RSSI1_DB_RAW_W(X) ((X) << ANC_AL_RSSI1_DB_RAW_POS)
#define ANC_AL_RSSI0_DB_RAW_POS  (24U)
#define ANC_AL_RSSI0_DB_RAW_MSK  (0xffUL << ANC_AL_RSSI0_DB_RAW_POS) /*!< Audio input path signal strength, unit is dB*/
#define ANC_AL_RSSI0_DB_RAW      ANC_AL_RSSI0_DB_RAW_MSK
#define ANC_AL_RSSI0_DB_RAW_W(X) ((X) << ANC_AL_RSSI0_DB_RAW_POS)

//ANC_L_RSSI_RSLT1 offsetaddress : 0x0404
//ANC_L_RSSI_RSLT1 RegResetValue : 0x0000000
#define ANC_AL_RSSI4_DB_RAW_POS    (0U)
#define ANC_AL_RSSI4_DB_RAW_MSK    (0xffUL << ANC_AL_RSSI4_DB_RAW_POS) /*!< Feedforward ANC input noise intensity, unit is dB*/
#define ANC_AL_RSSI4_DB_RAW        ANC_AL_RSSI4_DB_RAW_MSK
#define ANC_AL_RSSI4_DB_RAW_W(X)   ((X) << ANC_AL_RSSI4_DB_RAW_POS)
#define ANC_AL_RSSI4_VALID_RC_POS  (8U)
#define ANC_AL_RSSI4_VALID_RC_MSK  (0x1UL << ANC_AL_RSSI4_VALID_RC_POS) /*!< al_rssi4_valid Output enable Read clear*/
#define ANC_AL_RSSI4_VALID_RC      ANC_AL_RSSI4_VALID_RC_MSK
#define ANC_AL_RSSI4_VALID_RC_W(X) ((X) << ANC_AL_RSSI4_VALID_RC_POS)
#define ANC_AL_RSSI3_VALID_RC_POS  (9U)
#define ANC_AL_RSSI3_VALID_RC_MSK  (0x1UL << ANC_AL_RSSI3_VALID_RC_POS) /*!< al_rssi3_valid Output enable Read clear*/
#define ANC_AL_RSSI3_VALID_RC      ANC_AL_RSSI3_VALID_RC_MSK
#define ANC_AL_RSSI3_VALID_RC_W(X) ((X) << ANC_AL_RSSI3_VALID_RC_POS)
#define ANC_AL_RSSI2_VALID_RC_POS  (10U)
#define ANC_AL_RSSI2_VALID_RC_MSK  (0x1UL << ANC_AL_RSSI2_VALID_RC_POS) /*!< al_rssi2_valid Output enable Read clear*/
#define ANC_AL_RSSI2_VALID_RC      ANC_AL_RSSI2_VALID_RC_MSK
#define ANC_AL_RSSI2_VALID_RC_W(X) ((X) << ANC_AL_RSSI2_VALID_RC_POS)
#define ANC_AL_RSSI1_VALID_RC_POS  (11U)
#define ANC_AL_RSSI1_VALID_RC_MSK  (0x1UL << ANC_AL_RSSI1_VALID_RC_POS) /*!< al_rssi1_valid Output enable Read clear*/
#define ANC_AL_RSSI1_VALID_RC      ANC_AL_RSSI1_VALID_RC_MSK
#define ANC_AL_RSSI1_VALID_RC_W(X) ((X) << ANC_AL_RSSI1_VALID_RC_POS)
#define ANC_AL_RSSI0_VALID_RC_POS  (12U)
#define ANC_AL_RSSI0_VALID_RC_MSK  (0x1UL << ANC_AL_RSSI0_VALID_RC_POS) /*!< al_rssi0_valid Output enable Read clear*/
#define ANC_AL_RSSI0_VALID_RC      ANC_AL_RSSI0_VALID_RC_MSK
#define ANC_AL_RSSI0_VALID_RC_W(X) ((X) << ANC_AL_RSSI0_VALID_RC_POS)
#define ANC_AL_RSSI4_DB_SW_POS     (13U)
#define ANC_AL_RSSI4_DB_SW_MSK     (0x1UL << ANC_AL_RSSI4_DB_SW_POS) /*!< al_rssi4_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AL_RSSI4_DB_SW         ANC_AL_RSSI4_DB_SW_MSK
#define ANC_AL_RSSI4_DB_SW_W(X)    ((X) << ANC_AL_RSSI4_DB_SW_POS)
#define ANC_AL_RSSI3_DB_SW_POS     (14U)
#define ANC_AL_RSSI3_DB_SW_MSK     (0x1UL << ANC_AL_RSSI3_DB_SW_POS) /*!< al_rssi3_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AL_RSSI3_DB_SW         ANC_AL_RSSI3_DB_SW_MSK
#define ANC_AL_RSSI3_DB_SW_W(X)    ((X) << ANC_AL_RSSI3_DB_SW_POS)
#define ANC_AL_RSSI2_DB_SW_POS     (15U)
#define ANC_AL_RSSI2_DB_SW_MSK     (0x1UL << ANC_AL_RSSI2_DB_SW_POS) /*!< al_rssi2_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AL_RSSI2_DB_SW         ANC_AL_RSSI2_DB_SW_MSK
#define ANC_AL_RSSI2_DB_SW_W(X)    ((X) << ANC_AL_RSSI2_DB_SW_POS)
#define ANC_AL_RSSI1_DB_SW_POS     (16U)
#define ANC_AL_RSSI1_DB_SW_MSK     (0x1UL << ANC_AL_RSSI1_DB_SW_POS) /*!< al_rssi1_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AL_RSSI1_DB_SW         ANC_AL_RSSI1_DB_SW_MSK
#define ANC_AL_RSSI1_DB_SW_W(X)    ((X) << ANC_AL_RSSI1_DB_SW_POS)
#define ANC_AL_RSSI0_DB_SW_POS     (17U)
#define ANC_AL_RSSI0_DB_SW_MSK     (0x1UL << ANC_AL_RSSI0_DB_SW_POS) /*!< al_rssi0_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AL_RSSI0_DB_SW         ANC_AL_RSSI0_DB_SW_MSK
#define ANC_AL_RSSI0_DB_SW_W(X)    ((X) << ANC_AL_RSSI0_DB_SW_POS)

//ANC_L_RSSI_DEBUG1 offsetaddress : 0x0408
//ANC_L_RSSI_DEBUG1 RegResetValue : 0x0000000
#define ANC_AL_RSSI0_DB_MAX_POS  (0U)
#define ANC_AL_RSSI0_DB_MAX_MSK  (0xffUL << ANC_AL_RSSI0_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AL_RSSI0_DB_MAX      ANC_AL_RSSI0_DB_MAX_MSK
#define ANC_AL_RSSI0_DB_MAX_W(X) ((X) << ANC_AL_RSSI0_DB_MAX_POS)
#define ANC_AL_RSSI0_DB_MIN_POS  (8U)
#define ANC_AL_RSSI0_DB_MIN_MSK  (0xffUL << ANC_AL_RSSI0_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AL_RSSI0_DB_MIN      ANC_AL_RSSI0_DB_MIN_MSK
#define ANC_AL_RSSI0_DB_MIN_W(X) ((X) << ANC_AL_RSSI0_DB_MIN_POS)
#define ANC_AL_RSSI1_DB_MAX_POS  (16U)
#define ANC_AL_RSSI1_DB_MAX_MSK  (0xffUL << ANC_AL_RSSI1_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AL_RSSI1_DB_MAX      ANC_AL_RSSI1_DB_MAX_MSK
#define ANC_AL_RSSI1_DB_MAX_W(X) ((X) << ANC_AL_RSSI1_DB_MAX_POS)
#define ANC_AL_RSSI1_DB_MIN_POS  (24U)
#define ANC_AL_RSSI1_DB_MIN_MSK  (0xffUL << ANC_AL_RSSI1_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AL_RSSI1_DB_MIN      ANC_AL_RSSI1_DB_MIN_MSK
#define ANC_AL_RSSI1_DB_MIN_W(X) ((X) << ANC_AL_RSSI1_DB_MIN_POS)

//ANC_L_RSSI_DEBUG2 offsetaddress : 0x040C
//ANC_L_RSSI_DEBUG2 RegResetValue : 0x0000000
#define ANC_AL_RSSI2_DB_MAX_POS  (0U)
#define ANC_AL_RSSI2_DB_MAX_MSK  (0xffUL << ANC_AL_RSSI2_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AL_RSSI2_DB_MAX      ANC_AL_RSSI2_DB_MAX_MSK
#define ANC_AL_RSSI2_DB_MAX_W(X) ((X) << ANC_AL_RSSI2_DB_MAX_POS)
#define ANC_AL_RSSI2_DB_MIN_POS  (8U)
#define ANC_AL_RSSI2_DB_MIN_MSK  (0xffUL << ANC_AL_RSSI2_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AL_RSSI2_DB_MIN      ANC_AL_RSSI2_DB_MIN_MSK
#define ANC_AL_RSSI2_DB_MIN_W(X) ((X) << ANC_AL_RSSI2_DB_MIN_POS)
#define ANC_AL_RSSI3_DB_MAX_POS  (16U)
#define ANC_AL_RSSI3_DB_MAX_MSK  (0xffUL << ANC_AL_RSSI3_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AL_RSSI3_DB_MAX      ANC_AL_RSSI3_DB_MAX_MSK
#define ANC_AL_RSSI3_DB_MAX_W(X) ((X) << ANC_AL_RSSI3_DB_MAX_POS)
#define ANC_AL_RSSI3_DB_MIN_POS  (24U)
#define ANC_AL_RSSI3_DB_MIN_MSK  (0xffUL << ANC_AL_RSSI3_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AL_RSSI3_DB_MIN      ANC_AL_RSSI3_DB_MIN_MSK
#define ANC_AL_RSSI3_DB_MIN_W(X) ((X) << ANC_AL_RSSI3_DB_MIN_POS)

//ANC_L_RSSI_DEBUG3 offsetaddress : 0x0410
//ANC_L_RSSI_DEBUG3 RegResetValue : 0x0000000
#define ANC_AL_RSSI4_DB_MAX_POS   (0U)
#define ANC_AL_RSSI4_DB_MAX_MSK   (0xffUL << ANC_AL_RSSI4_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AL_RSSI4_DB_MAX       ANC_AL_RSSI4_DB_MAX_MSK
#define ANC_AL_RSSI4_DB_MAX_W(X)  ((X) << ANC_AL_RSSI4_DB_MAX_POS)
#define ANC_AL_RSSI4_DB_MIN_POS   (8U)
#define ANC_AL_RSSI4_DB_MIN_MSK   (0xffUL << ANC_AL_RSSI4_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AL_RSSI4_DB_MIN       ANC_AL_RSSI4_DB_MIN_MSK
#define ANC_AL_RSSI4_DB_MIN_W(X)  ((X) << ANC_AL_RSSI4_DB_MIN_POS)
#define ANC_AL_RSSI0_DB_MASK_POS  (16U)
#define ANC_AL_RSSI0_DB_MASK_MSK  (0x1UL << ANC_AL_RSSI0_DB_MASK_POS) /*!< Use max min threshold method to compare 1: No comparison 0: Compare*/
#define ANC_AL_RSSI0_DB_MASK      ANC_AL_RSSI0_DB_MASK_MSK
#define ANC_AL_RSSI0_DB_MASK_W(X) ((X) << ANC_AL_RSSI0_DB_MASK_POS)
#define ANC_AL_RSSI1_DB_MASK_POS  (17U)
#define ANC_AL_RSSI1_DB_MASK_MSK  (0x1UL << ANC_AL_RSSI1_DB_MASK_POS) /*!< Use max min threshold method to compare 1: No comparison 0: Compare*/
#define ANC_AL_RSSI1_DB_MASK      ANC_AL_RSSI1_DB_MASK_MSK
#define ANC_AL_RSSI1_DB_MASK_W(X) ((X) << ANC_AL_RSSI1_DB_MASK_POS)
#define ANC_AL_RSSI2_DB_MASK_POS  (18U)
#define ANC_AL_RSSI2_DB_MASK_MSK  (0x1UL << ANC_AL_RSSI2_DB_MASK_POS) /*!< Use max min threshold method to compare 1: No comparison 0: Compare*/
#define ANC_AL_RSSI2_DB_MASK      ANC_AL_RSSI2_DB_MASK_MSK
#define ANC_AL_RSSI2_DB_MASK_W(X) ((X) << ANC_AL_RSSI2_DB_MASK_POS)
#define ANC_AL_RSSI3_DB_MASK_POS  (19U)
#define ANC_AL_RSSI3_DB_MASK_MSK  (0x1UL << ANC_AL_RSSI3_DB_MASK_POS) /*!< Use max min threshold method to compare 1: No comparison 0: Compare*/
#define ANC_AL_RSSI3_DB_MASK      ANC_AL_RSSI3_DB_MASK_MSK
#define ANC_AL_RSSI3_DB_MASK_W(X) ((X) << ANC_AL_RSSI3_DB_MASK_POS)
#define ANC_AL_RSSI4_DB_MASK_POS  (20U)
#define ANC_AL_RSSI4_DB_MASK_MSK  (0x1UL << ANC_AL_RSSI4_DB_MASK_POS) /*!< Use max min threshold method to compare 1: No comparison 0: Compare*/
#define ANC_AL_RSSI4_DB_MASK      ANC_AL_RSSI4_DB_MASK_MSK
#define ANC_AL_RSSI4_DB_MASK_W(X) ((X) << ANC_AL_RSSI4_DB_MASK_POS)

//ANC_L_MN_IIR offsetaddress : 0x0500
//ANC_L_MN_IIR RegResetValue : 0x0000000
#define ANC_AL_IIR_FB_MN_POS      (0U)
#define ANC_AL_IIR_FB_MN_MSK      (0x7UL << ANC_AL_IIR_FB_MN_POS) /*!< The left MN_IIR filter coefficient decimal bit width selection: 0:23 bits, 1:24 bits,..., 7:30 bits*/
#define ANC_AL_IIR_FB_MN          ANC_AL_IIR_FB_MN_MSK
#define ANC_AL_IIR_FB_MN_W(X)     ((X) << ANC_AL_IIR_FB_MN_POS)
#define ANC_AL_MN_IIR_EN_POS      (3U)
#define ANC_AL_MN_IIR_EN_MSK      (0x1UL << ANC_AL_MN_IIR_EN_POS) /*!< The left MN_IIR filter module enables Write 1 enables*/
#define ANC_AL_MN_IIR_EN          ANC_AL_MN_IIR_EN_MSK
#define ANC_AL_MN_IIR_EN_W(X)     ((X) << ANC_AL_MN_IIR_EN_POS)
#define ANC_AL_BYPASS_MN_IIR_POS  (4U)
#define ANC_AL_BYPASS_MN_IIR_MSK  (0x1UL << ANC_AL_BYPASS_MN_IIR_POS) /*!< Left MN_IIR filter bypass enable Write 1 enable*/
#define ANC_AL_BYPASS_MN_IIR      ANC_AL_BYPASS_MN_IIR_MSK
#define ANC_AL_BYPASS_MN_IIR_W(X) ((X) << ANC_AL_BYPASS_MN_IIR_POS)
#define ANC_AL_IIR_SEL_MN_POS     (5U)
#define ANC_AL_IIR_SEL_MN_MSK     (0x7UL << ANC_AL_IIR_SEL_MN_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_AL_IIR_SEL_MN         ANC_AL_IIR_SEL_MN_MSK
#define ANC_AL_IIR_SEL_MN_W(X)    ((X) << ANC_AL_IIR_SEL_MN_POS)

//ANC_L_SC_IIR offsetaddress : 0x0504
//ANC_L_SC_IIR RegResetValue : 0x0000000
#define ANC_AL_IIR_FB_SC_POS      (0U)
#define ANC_AL_IIR_FB_SC_MSK      (0x7UL << ANC_AL_IIR_FB_SC_POS) /*!< The left MN_IIR filter coefficient decimal bit width selection: 0:23 bits, 1:24 bits,..., 7:30 bits*/
#define ANC_AL_IIR_FB_SC          ANC_AL_IIR_FB_SC_MSK
#define ANC_AL_IIR_FB_SC_W(X)     ((X) << ANC_AL_IIR_FB_SC_POS)
#define ANC_AL_SC_IIR_EN_POS      (3U)
#define ANC_AL_SC_IIR_EN_MSK      (0x1UL << ANC_AL_SC_IIR_EN_POS) /*!< The left MN_IIR filter module enables Write 1 enables*/
#define ANC_AL_SC_IIR_EN          ANC_AL_SC_IIR_EN_MSK
#define ANC_AL_SC_IIR_EN_W(X)     ((X) << ANC_AL_SC_IIR_EN_POS)
#define ANC_AL_BYPASS_SC_IIR_POS  (4U)
#define ANC_AL_BYPASS_SC_IIR_MSK  (0x1UL << ANC_AL_BYPASS_SC_IIR_POS) /*!< Left MN_IIR filter bypass enable Write 1 enable*/
#define ANC_AL_BYPASS_SC_IIR      ANC_AL_BYPASS_SC_IIR_MSK
#define ANC_AL_BYPASS_SC_IIR_W(X) ((X) << ANC_AL_BYPASS_SC_IIR_POS)
#define ANC_AL_IIR_SEL_SC_POS     (5U)
#define ANC_AL_IIR_SEL_SC_MSK     (0x7UL << ANC_AL_IIR_SEL_SC_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_AL_IIR_SEL_SC         ANC_AL_IIR_SEL_SC_MSK
#define ANC_AL_IIR_SEL_SC_W(X)    ((X) << ANC_AL_IIR_SEL_SC_POS)

//ANC_R_CTL offsetaddress : 0x0800
//ANC_R_CTL RegResetValue : 0x0000000
#define ANC_AR_ADC_MAP_POS            (0U)
#define ANC_AR_ADC_MAP_MSK            (0x7UL << ANC_AR_ADC_MAP_POS) /*!< 3-channel ADC input mapping relationship control:*/
#define ANC_AR_ADC_MAP                ANC_AR_ADC_MAP_MSK
#define ANC_AR_ADC_MAP_W(X)           ((X) << ANC_AR_ADC_MAP_POS)
#define ANC_AR_MUSIC_RATE_POS         (4U)
#define ANC_AR_MUSIC_RATE_MSK         (0x3UL << ANC_AR_MUSIC_RATE_POS) /*!< ANC audio input signal rate control:*/
#define ANC_AR_MUSIC_RATE             ANC_AR_MUSIC_RATE_MSK
#define ANC_AR_MUSIC_RATE_W(X)        ((X) << ANC_AR_MUSIC_RATE_POS)
#define ANC_AR_ANC_RATE_POS           (6U)
#define ANC_AR_ANC_RATE_MSK           (0x3UL << ANC_AR_ANC_RATE_POS) /*!< ANC operating rate control:*/
#define ANC_AR_ANC_RATE               ANC_AR_ANC_RATE_MSK
#define ANC_AR_ANC_RATE_W(X)          ((X) << ANC_AR_ANC_RATE_POS)
#define ANC_AR_PHN_RATE_POS           (8U)
#define ANC_AR_PHN_RATE_MSK           (0x1UL << ANC_AR_PHN_RATE_POS) /*!< Dual-machine noise reduction output rate control:*/
#define ANC_AR_PHN_RATE               ANC_AR_PHN_RATE_MSK
#define ANC_AR_PHN_RATE_W(X)          ((X) << ANC_AR_PHN_RATE_POS)
#define ANC_AR_DIG_EQ_EN_POS          (9U)
#define ANC_AR_DIG_EQ_EN_MSK          (0x1UL << ANC_AR_DIG_EQ_EN_POS) /*!< Digital Equalization IIR Filter Enable, Highly Effective*/
#define ANC_AR_DIG_EQ_EN              ANC_AR_DIG_EQ_EN_MSK
#define ANC_AR_DIG_EQ_EN_W(X)         ((X) << ANC_AR_DIG_EQ_EN_POS)
#define ANC_AR_ANC_FB_EN_POS          (10U)
#define ANC_AR_ANC_FB_EN_MSK          (0x1UL << ANC_AR_ANC_FB_EN_POS) /*!< Feedback ANC IIR filter enables high efficiency*/
#define ANC_AR_ANC_FB_EN              ANC_AR_ANC_FB_EN_MSK
#define ANC_AR_ANC_FB_EN_W(X)         ((X) << ANC_AR_ANC_FB_EN_POS)
#define ANC_AR_ANC_FF_EN_POS          (11U)
#define ANC_AR_ANC_FF_EN_MSK          (0x1UL << ANC_AR_ANC_FF_EN_POS) /*!< Feedforward ANC IIR filter enabled, highly effective*/
#define ANC_AR_ANC_FF_EN              ANC_AR_ANC_FF_EN_MSK
#define ANC_AR_ANC_FF_EN_W(X)         ((X) << ANC_AR_ANC_FF_EN_POS)
#define ANC_AR_PHN_RATE2_POS          (12U)
#define ANC_AR_PHN_RATE2_MSK          (0x1UL << ANC_AR_PHN_RATE2_POS) /*!< Dual-machine noise reduction output rate control:*/
#define ANC_AR_PHN_RATE2              ANC_AR_PHN_RATE2_MSK
#define ANC_AR_PHN_RATE2_W(X)         ((X) << ANC_AR_PHN_RATE2_POS)
#define ANC_AR_MUSIC_96K_EN_POS       (14U)
#define ANC_AR_MUSIC_96K_EN_MSK       (0x1UL << ANC_AR_MUSIC_96K_EN_POS) /*!< 96k music playback rate enable:*/
#define ANC_AR_MUSIC_96K_EN           ANC_AR_MUSIC_96K_EN_MSK
#define ANC_AR_MUSIC_96K_EN_W(X)      ((X) << ANC_AR_MUSIC_96K_EN_POS)
#define ANC_AR_SB_EN_POS              (15U)
#define ANC_AR_SB_EN_MSK              (0x1UL << ANC_AR_SB_EN_POS) /*!< Feedback secondary channel cascade IIR filter bank enable:*/
#define ANC_AR_SB_EN                  ANC_AR_SB_EN_MSK
#define ANC_AR_SB_EN_W(X)             ((X) << ANC_AR_SB_EN_POS)
#define ANC_AR_ENABLE_POS             (16U)
#define ANC_AR_ENABLE_MSK             (0x1UL << ANC_AR_ENABLE_POS) /*!< Total enable, high valid, low reset internal signal*/
#define ANC_AR_ENABLE                 ANC_AR_ENABLE_MSK
#define ANC_AR_ENABLE_W(X)            ((X) << ANC_AR_ENABLE_POS)
#define ANC_AR_SB_FB_EN_POS           (18U)
#define ANC_AR_SB_FB_EN_MSK           (0x1UL << ANC_AR_SB_FB_EN_POS) /*!< Enable the output of the feedback secondary channel to cancel the input of the feedback ANC:*/
#define ANC_AR_SB_FB_EN               ANC_AR_SB_FB_EN_MSK
#define ANC_AR_SB_FB_EN_W(X)          ((X) << ANC_AR_SB_FB_EN_POS)
#define ANC_AR_MUSIC_SB_EN_POS        (19U)
#define ANC_AR_MUSIC_SB_EN_MSK        (0x1UL << ANC_AR_MUSIC_SB_EN_POS) /*!< Enable feedback secondary channel IIR filter bank to compensate for music signals:*/
#define ANC_AR_MUSIC_SB_EN            ANC_AR_MUSIC_SB_EN_MSK
#define ANC_AR_MUSIC_SB_EN_W(X)       ((X) << ANC_AR_MUSIC_SB_EN_POS)
#define ANC_AR_DWN_FB_SR_POS          (20U)
#define ANC_AR_DWN_FB_SR_MSK          (0x1UL << ANC_AR_DWN_FB_SR_POS) /*!< Adaptive ANC&#39;s feedback path downsampling and decimation filter input control:*/
#define ANC_AR_DWN_FB_SR              ANC_AR_DWN_FB_SR_MSK
#define ANC_AR_DWN_FB_SR_W(X)         ((X) << ANC_AR_DWN_FB_SR_POS)
#define ANC_AR_PHN_TR_ADP_BYPASS_POS  (21U)
#define ANC_AR_PHN_TR_ADP_BYPASS_MSK  (0x1UL << ANC_AR_PHN_TR_ADP_BYPASS_POS) /*!< Sanmai noise reduction (right ear) tr channel downsampling bypass enable, highly effective*/
#define ANC_AR_PHN_TR_ADP_BYPASS      ANC_AR_PHN_TR_ADP_BYPASS_MSK
#define ANC_AR_PHN_TR_ADP_BYPASS_W(X) ((X) << ANC_AR_PHN_TR_ADP_BYPASS_POS)
#define ANC_AR_PHN_TR_EN_POS          (22U)
#define ANC_AR_PHN_TR_EN_MSK          (0x1UL << ANC_AR_PHN_TR_EN_POS) /*!< Sanmai noise reduction (right ear) tr channel extraction enables, highly effective*/
#define ANC_AR_PHN_TR_EN              ANC_AR_PHN_TR_EN_MSK
#define ANC_AR_PHN_TR_EN_W(X)         ((X) << ANC_AR_PHN_TR_EN_POS)
#define ANC_AR_PORT0_SR_POS           (23U)
#define ANC_AR_PORT0_SR_MSK           (0x3UL << ANC_AR_PORT0_SR_POS) /*!< ADC0 port multiplexing control*/
#define ANC_AR_PORT0_SR               ANC_AR_PORT0_SR_MSK
#define ANC_AR_PORT0_SR_W(X)          ((X) << ANC_AR_PORT0_SR_POS)
#define ANC_AR_PORT1_SR_POS           (25U)
#define ANC_AR_PORT1_SR_MSK           (0x3UL << ANC_AR_PORT1_SR_POS) /*!< ADC1 port multiplexing control*/
#define ANC_AR_PORT1_SR               ANC_AR_PORT1_SR_MSK
#define ANC_AR_PORT1_SR_W(X)          ((X) << ANC_AR_PORT1_SR_POS)
#define ANC_AR_BYPASS_WF_POS          (27U)
#define ANC_AR_BYPASS_WF_MSK          (0x1UL << ANC_AR_BYPASS_WF_POS) /*!< IIR filter bank input and output short-circuit control of feedforward ANC path*/
#define ANC_AR_BYPASS_WF              ANC_AR_BYPASS_WF_MSK
#define ANC_AR_BYPASS_WF_W(X)         ((X) << ANC_AR_BYPASS_WF_POS)
#define ANC_AR_BYPASS_HF_POS          (28U)
#define ANC_AR_BYPASS_HF_MSK          (0x1UL << ANC_AR_BYPASS_HF_POS) /*!< FIR filter input and output short-circuit control of feedforward ANC path*/
#define ANC_AR_BYPASS_HF              ANC_AR_BYPASS_HF_MSK
#define ANC_AR_BYPASS_HF_W(X)         ((X) << ANC_AR_BYPASS_HF_POS)

//ANC_R_RSSI_SIZE0 offsetaddress : 0x0804
//ANC_R_RSSI_SIZE0 RegResetValue : 0x0000000
#define ANC_AR_RSSI3_SIZE_POS  (0U)
#define ANC_AR_RSSI3_SIZE_MSK  (0xffUL << ANC_AR_RSSI3_SIZE_POS) /*!< Observation length win3_size when calculating RSSI;*/
#define ANC_AR_RSSI3_SIZE      ANC_AR_RSSI3_SIZE_MSK
#define ANC_AR_RSSI3_SIZE_W(X) ((X) << ANC_AR_RSSI3_SIZE_POS)
#define ANC_AR_RSSI2_SIZE_POS  (8U)
#define ANC_AR_RSSI2_SIZE_MSK  (0xffUL << ANC_AR_RSSI2_SIZE_POS) /*!< Observation length win2_size when calculating RSSI;*/
#define ANC_AR_RSSI2_SIZE      ANC_AR_RSSI2_SIZE_MSK
#define ANC_AR_RSSI2_SIZE_W(X) ((X) << ANC_AR_RSSI2_SIZE_POS)
#define ANC_AR_RSSI1_SIZE_POS  (16U)
#define ANC_AR_RSSI1_SIZE_MSK  (0xffUL << ANC_AR_RSSI1_SIZE_POS) /*!< Observation length win1_size when calculating RSSI;*/
#define ANC_AR_RSSI1_SIZE      ANC_AR_RSSI1_SIZE_MSK
#define ANC_AR_RSSI1_SIZE_W(X) ((X) << ANC_AR_RSSI1_SIZE_POS)
#define ANC_AR_RSSI0_SIZE_POS  (24U)
#define ANC_AR_RSSI0_SIZE_MSK  (0xffUL << ANC_AR_RSSI0_SIZE_POS) /*!< Observation length win0_size when calculating RSSI;*/
#define ANC_AR_RSSI0_SIZE      ANC_AR_RSSI0_SIZE_MSK
#define ANC_AR_RSSI0_SIZE_W(X) ((X) << ANC_AR_RSSI0_SIZE_POS)

//ANC_R_RSSI_SIZE1 offsetaddress : 0x0808
//ANC_R_RSSI_SIZE1 RegResetValue : 0x0000000
#define ANC_AR_RSSI4_SIZE_POS  (0U)
#define ANC_AR_RSSI4_SIZE_MSK  (0xffUL << ANC_AR_RSSI4_SIZE_POS) /*!< Observation length win4_size when calculating RSSI;*/
#define ANC_AR_RSSI4_SIZE      ANC_AR_RSSI4_SIZE_MSK
#define ANC_AR_RSSI4_SIZE_W(X) ((X) << ANC_AR_RSSI4_SIZE_POS)
#define ANC_AR_RSSI_SEL_POS    (8U)
#define ANC_AR_RSSI_SEL_MSK    (0xffUL << ANC_AR_RSSI_SEL_POS) /*!< rssi input selection*/
#define ANC_AR_RSSI_SEL        ANC_AR_RSSI_SEL_MSK
#define ANC_AR_RSSI_SEL_W(X)   ((X) << ANC_AR_RSSI_SEL_POS)

//ANC_R_DATAPATH_SEL offsetaddress : 0x080C
//ANC_R_DATAPATH_SEL RegResetValue : 0x0000000
#define ANC_AR_ANC_DATAPATH_EN0_POS  (0U)
#define ANC_AR_ANC_DATAPATH_EN0_MSK  (0x1UL << ANC_AR_ANC_DATAPATH_EN0_POS) /*!< ADC0 FIFO input selection*/
#define ANC_AR_ANC_DATAPATH_EN0      ANC_AR_ANC_DATAPATH_EN0_MSK
#define ANC_AR_ANC_DATAPATH_EN0_W(X) ((X) << ANC_AR_ANC_DATAPATH_EN0_POS)
#define ANC_AR_ANC_DATAPATH_EN1_POS  (1U)
#define ANC_AR_ANC_DATAPATH_EN1_MSK  (0x1UL << ANC_AR_ANC_DATAPATH_EN1_POS) /*!< Input selection for ADC1 FIFO*/
#define ANC_AR_ANC_DATAPATH_EN1      ANC_AR_ANC_DATAPATH_EN1_MSK
#define ANC_AR_ANC_DATAPATH_EN1_W(X) ((X) << ANC_AR_ANC_DATAPATH_EN1_POS)
#define ANC_AR_ANC_DATAPATH_EN2_POS  (2U)
#define ANC_AR_ANC_DATAPATH_EN2_MSK  (0x1UL << ANC_AR_ANC_DATAPATH_EN2_POS) /*!< Input selection of DAC path*/
#define ANC_AR_ANC_DATAPATH_EN2      ANC_AR_ANC_DATAPATH_EN2_MSK
#define ANC_AR_ANC_DATAPATH_EN2_W(X) ((X) << ANC_AR_ANC_DATAPATH_EN2_POS)
#define ANC_AR_ANC_ADC0_DELAY_POS    (3U)
#define ANC_AR_ANC_ADC0_DELAY_MSK    (0x1UL << ANC_AR_ANC_ADC0_DELAY_POS) /*!< ADC0 input delay (4 codec cock cycles) enabled*/
#define ANC_AR_ANC_ADC0_DELAY        ANC_AR_ANC_ADC0_DELAY_MSK
#define ANC_AR_ANC_ADC0_DELAY_W(X)   ((X) << ANC_AR_ANC_ADC0_DELAY_POS)
#define ANC_AR_ANC_ADC1_DELAY_POS    (4U)
#define ANC_AR_ANC_ADC1_DELAY_MSK    (0x1UL << ANC_AR_ANC_ADC1_DELAY_POS) /*!< ADC1 input delay (3 codec cock cycles) enabled*/
#define ANC_AR_ANC_ADC1_DELAY        ANC_AR_ANC_ADC1_DELAY_MSK
#define ANC_AR_ANC_ADC1_DELAY_W(X)   ((X) << ANC_AR_ANC_ADC1_DELAY_POS)
#define ANC_AR_ANC_ADC2_DELAY_POS    (5U)
#define ANC_AR_ANC_ADC2_DELAY_MSK    (0x1UL << ANC_AR_ANC_ADC2_DELAY_POS) /*!< ADC2 input delay (2 codec cock cycles) enabled*/
#define ANC_AR_ANC_ADC2_DELAY        ANC_AR_ANC_ADC2_DELAY_MSK
#define ANC_AR_ANC_ADC2_DELAY_W(X)   ((X) << ANC_AR_ANC_ADC2_DELAY_POS)
#define ANC_AR_ANC_DATAPATH_EN3_POS  (7U)
#define ANC_AR_ANC_DATAPATH_EN3_MSK  (0x1UL << ANC_AR_ANC_DATAPATH_EN3_POS) /*!< Input selection of ADC2 path*/
#define ANC_AR_ANC_DATAPATH_EN3      ANC_AR_ANC_DATAPATH_EN3_MSK
#define ANC_AR_ANC_DATAPATH_EN3_W(X) ((X) << ANC_AR_ANC_DATAPATH_EN3_POS)
#define ANC_AR_ANC_ADC3_DELAY_POS    (8U)
#define ANC_AR_ANC_ADC3_DELAY_MSK    (0x1UL << ANC_AR_ANC_ADC3_DELAY_POS) /*!< ADC3 input delay (2 codec cock cycles) enabled*/
#define ANC_AR_ANC_ADC3_DELAY        ANC_AR_ANC_ADC3_DELAY_MSK
#define ANC_AR_ANC_ADC3_DELAY_W(X)   ((X) << ANC_AR_ANC_ADC3_DELAY_POS)
#define ANC_AR_ANC_ADC4_DELAY_POS    (9U)
#define ANC_AR_ANC_ADC4_DELAY_MSK    (0x1UL << ANC_AR_ANC_ADC4_DELAY_POS) /*!< ADC4 input delay (2 codec cock cycles) enabled*/
#define ANC_AR_ANC_ADC4_DELAY        ANC_AR_ANC_ADC4_DELAY_MSK
#define ANC_AR_ANC_ADC4_DELAY_W(X)   ((X) << ANC_AR_ANC_ADC4_DELAY_POS)

//ANC_R_CTL2 offsetaddress : 0x0810
//ANC_R_CTL2 RegResetValue : 0x0000000
#define ANC_AR_ADC_TR_MAP_POS  (3U)
#define ANC_AR_ADC_TR_MAP_MSK  (0x7UL << ANC_AR_ADC_TR_MAP_POS) /*!< Tr path selection ADC source*/
#define ANC_AR_ADC_TR_MAP      ANC_AR_ADC_TR_MAP_MSK
#define ANC_AR_ADC_TR_MAP_W(X) ((X) << ANC_AR_ADC_TR_MAP_POS)
#define ANC_AR_ADC_FF_MAP_POS  (6U)
#define ANC_AR_ADC_FF_MAP_MSK  (0x7UL << ANC_AR_ADC_FF_MAP_POS) /*!< ff path selection ADC source*/
#define ANC_AR_ADC_FF_MAP      ANC_AR_ADC_FF_MAP_MSK
#define ANC_AR_ADC_FF_MAP_W(X) ((X) << ANC_AR_ADC_FF_MAP_POS)
#define ANC_AR_ADC_FB_MAP_POS  (9U)
#define ANC_AR_ADC_FB_MAP_MSK  (0x7UL << ANC_AR_ADC_FB_MAP_POS) /*!< FB path selection ADC source*/
#define ANC_AR_ADC_FB_MAP      ANC_AR_ADC_FB_MAP_MSK
#define ANC_AR_ADC_FB_MAP_W(X) ((X) << ANC_AR_ADC_FB_MAP_POS)
#define ANC_AR_ADC_CLK_EN_POS  (12U)
#define ANC_AR_ADC_CLK_EN_MSK  (0x1UL << ANC_AR_ADC_CLK_EN_POS) /*!< ar_adc_clk_en clock enable*/
#define ANC_AR_ADC_CLK_EN      ANC_AR_ADC_CLK_EN_MSK
#define ANC_AR_ADC_CLK_EN_W(X) ((X) << ANC_AR_ADC_CLK_EN_POS)

//ANC_R_RSSI_RSLT0 offsetaddress : 0x0C00
//ANC_R_RSSI_RSLT0 RegResetValue : 0x0000000
#define ANC_AR_RSSI3_DB_RAW_POS  (0U)
#define ANC_AR_RSSI3_DB_RAW_MSK  (0xffUL << ANC_AR_RSSI3_DB_RAW_POS) /*!< Feedforward ANC input noise intensity, unit is dB*/
#define ANC_AR_RSSI3_DB_RAW      ANC_AR_RSSI3_DB_RAW_MSK
#define ANC_AR_RSSI3_DB_RAW_W(X) ((X) << ANC_AR_RSSI3_DB_RAW_POS)
#define ANC_AR_RSSI2_DB_RAW_POS  (8U)
#define ANC_AR_RSSI2_DB_RAW_MSK  (0xffUL << ANC_AR_RSSI2_DB_RAW_POS) /*!< ANC output signal strength, unit is dB*/
#define ANC_AR_RSSI2_DB_RAW      ANC_AR_RSSI2_DB_RAW_MSK
#define ANC_AR_RSSI2_DB_RAW_W(X) ((X) << ANC_AR_RSSI2_DB_RAW_POS)
#define ANC_AR_RSSI1_DB_RAW_POS  (16U)
#define ANC_AR_RSSI1_DB_RAW_MSK  (0xffUL << ANC_AR_RSSI1_DB_RAW_POS) /*!< Feedback ANC output signal strength, unit is dB*/
#define ANC_AR_RSSI1_DB_RAW      ANC_AR_RSSI1_DB_RAW_MSK
#define ANC_AR_RSSI1_DB_RAW_W(X) ((X) << ANC_AR_RSSI1_DB_RAW_POS)
#define ANC_AR_RSSI0_DB_RAW_POS  (24U)
#define ANC_AR_RSSI0_DB_RAW_MSK  (0xffUL << ANC_AR_RSSI0_DB_RAW_POS) /*!< Audio input path signal strength, unit is dB*/
#define ANC_AR_RSSI0_DB_RAW      ANC_AR_RSSI0_DB_RAW_MSK
#define ANC_AR_RSSI0_DB_RAW_W(X) ((X) << ANC_AR_RSSI0_DB_RAW_POS)

//ANC_R_RSSI_RSLT1 offsetaddress : 0x0C04
//ANC_R_RSSI_RSLT1 RegResetValue : 0x0000000
#define ANC_AR_RSSI4_DB_RAW_POS    (0U)
#define ANC_AR_RSSI4_DB_RAW_MSK    (0xffUL << ANC_AR_RSSI4_DB_RAW_POS) /*!< Feedforward ANC input noise intensity, unit is dB*/
#define ANC_AR_RSSI4_DB_RAW        ANC_AR_RSSI4_DB_RAW_MSK
#define ANC_AR_RSSI4_DB_RAW_W(X)   ((X) << ANC_AR_RSSI4_DB_RAW_POS)
#define ANC_AR_RSSI4_VALID_RC_POS  (8U)
#define ANC_AR_RSSI4_VALID_RC_MSK  (0x1UL << ANC_AR_RSSI4_VALID_RC_POS) /*!< ar_rssi4_valid Output enable Read clear*/
#define ANC_AR_RSSI4_VALID_RC      ANC_AR_RSSI4_VALID_RC_MSK
#define ANC_AR_RSSI4_VALID_RC_W(X) ((X) << ANC_AR_RSSI4_VALID_RC_POS)
#define ANC_AR_RSSI3_VALID_RC_POS  (9U)
#define ANC_AR_RSSI3_VALID_RC_MSK  (0x1UL << ANC_AR_RSSI3_VALID_RC_POS) /*!< ar_rssi3_valid Output enable Read clear*/
#define ANC_AR_RSSI3_VALID_RC      ANC_AR_RSSI3_VALID_RC_MSK
#define ANC_AR_RSSI3_VALID_RC_W(X) ((X) << ANC_AR_RSSI3_VALID_RC_POS)
#define ANC_AR_RSSI2_VALID_RC_POS  (10U)
#define ANC_AR_RSSI2_VALID_RC_MSK  (0x1UL << ANC_AR_RSSI2_VALID_RC_POS) /*!< ar_rssi2_valid Output enable Read clear*/
#define ANC_AR_RSSI2_VALID_RC      ANC_AR_RSSI2_VALID_RC_MSK
#define ANC_AR_RSSI2_VALID_RC_W(X) ((X) << ANC_AR_RSSI2_VALID_RC_POS)
#define ANC_AR_RSSI1_VALID_RC_POS  (11U)
#define ANC_AR_RSSI1_VALID_RC_MSK  (0x1UL << ANC_AR_RSSI1_VALID_RC_POS) /*!< ar_rssi1_valid Output enable Read clear*/
#define ANC_AR_RSSI1_VALID_RC      ANC_AR_RSSI1_VALID_RC_MSK
#define ANC_AR_RSSI1_VALID_RC_W(X) ((X) << ANC_AR_RSSI1_VALID_RC_POS)
#define ANC_AR_RSSI0_VALID_RC_POS  (12U)
#define ANC_AR_RSSI0_VALID_RC_MSK  (0x1UL << ANC_AR_RSSI0_VALID_RC_POS) /*!< ar_rssi0_valid Output enable Read clear*/
#define ANC_AR_RSSI0_VALID_RC      ANC_AR_RSSI0_VALID_RC_MSK
#define ANC_AR_RSSI0_VALID_RC_W(X) ((X) << ANC_AR_RSSI0_VALID_RC_POS)
#define ANC_AR_RSSI4_DB_SW_POS     (13U)
#define ANC_AR_RSSI4_DB_SW_MSK     (0x1UL << ANC_AR_RSSI4_DB_SW_POS) /*!< ar_rssi4_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AR_RSSI4_DB_SW         ANC_AR_RSSI4_DB_SW_MSK
#define ANC_AR_RSSI4_DB_SW_W(X)    ((X) << ANC_AR_RSSI4_DB_SW_POS)
#define ANC_AR_RSSI3_DB_SW_POS     (14U)
#define ANC_AR_RSSI3_DB_SW_MSK     (0x1UL << ANC_AR_RSSI3_DB_SW_POS) /*!< ar_rssi3_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AR_RSSI3_DB_SW         ANC_AR_RSSI3_DB_SW_MSK
#define ANC_AR_RSSI3_DB_SW_W(X)    ((X) << ANC_AR_RSSI3_DB_SW_POS)
#define ANC_AR_RSSI2_DB_SW_POS     (15U)
#define ANC_AR_RSSI2_DB_SW_MSK     (0x1UL << ANC_AR_RSSI2_DB_SW_POS) /*!< ar_rssi2_db_sw 1: Real-time value 0: Report interrupted latch value*/
#define ANC_AR_RSSI2_DB_SW         ANC_AR_RSSI2_DB_SW_MSK
#define ANC_AR_RSSI2_DB_SW_W(X)    ((X) << ANC_AR_RSSI2_DB_SW_POS)
#define ANC_AR_RSSI1_DB_SW_POS     (16U)
#define ANC_AR_RSSI1_DB_SW_MSK     (0x1UL << ANC_AR_RSSI1_DB_SW_POS) /*!< ar_rssi1_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AR_RSSI1_DB_SW         ANC_AR_RSSI1_DB_SW_MSK
#define ANC_AR_RSSI1_DB_SW_W(X)    ((X) << ANC_AR_RSSI1_DB_SW_POS)
#define ANC_AR_RSSI0_DB_SW_POS     (17U)
#define ANC_AR_RSSI0_DB_SW_MSK     (0x1UL << ANC_AR_RSSI0_DB_SW_POS) /*!< ar_rssi0_db_sw 1: Real-time value 0: Report the latch value of interruption*/
#define ANC_AR_RSSI0_DB_SW         ANC_AR_RSSI0_DB_SW_MSK
#define ANC_AR_RSSI0_DB_SW_W(X)    ((X) << ANC_AR_RSSI0_DB_SW_POS)

//ANC_R_RSSI_DEBUG1 offsetaddress : 0x0C08
//ANC_R_RSSI_DEBUG1 RegResetValue : 0x0000000
#define ANC_AR_RSSI0_DB_MAX_POS  (0U)
#define ANC_AR_RSSI0_DB_MAX_MSK  (0xffUL << ANC_AR_RSSI0_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AR_RSSI0_DB_MAX      ANC_AR_RSSI0_DB_MAX_MSK
#define ANC_AR_RSSI0_DB_MAX_W(X) ((X) << ANC_AR_RSSI0_DB_MAX_POS)
#define ANC_AR_RSSI0_DB_MIN_POS  (8U)
#define ANC_AR_RSSI0_DB_MIN_MSK  (0xffUL << ANC_AR_RSSI0_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AR_RSSI0_DB_MIN      ANC_AR_RSSI0_DB_MIN_MSK
#define ANC_AR_RSSI0_DB_MIN_W(X) ((X) << ANC_AR_RSSI0_DB_MIN_POS)
#define ANC_AR_RSSI1_DB_MAX_POS  (16U)
#define ANC_AR_RSSI1_DB_MAX_MSK  (0xffUL << ANC_AR_RSSI1_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AR_RSSI1_DB_MAX      ANC_AR_RSSI1_DB_MAX_MSK
#define ANC_AR_RSSI1_DB_MAX_W(X) ((X) << ANC_AR_RSSI1_DB_MAX_POS)
#define ANC_AR_RSSI1_DB_MIN_POS  (24U)
#define ANC_AR_RSSI1_DB_MIN_MSK  (0xffUL << ANC_AR_RSSI1_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AR_RSSI1_DB_MIN      ANC_AR_RSSI1_DB_MIN_MSK
#define ANC_AR_RSSI1_DB_MIN_W(X) ((X) << ANC_AR_RSSI1_DB_MIN_POS)

//ANC_R_RSSI_DEBUG2 offsetaddress : 0x0C0C
//ANC_R_RSSI_DEBUG2 RegResetValue : 0x0000000
#define ANC_AR_RSSI2_DB_MAX_POS  (0U)
#define ANC_AR_RSSI2_DB_MAX_MSK  (0xffUL << ANC_AR_RSSI2_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AR_RSSI2_DB_MAX      ANC_AR_RSSI2_DB_MAX_MSK
#define ANC_AR_RSSI2_DB_MAX_W(X) ((X) << ANC_AR_RSSI2_DB_MAX_POS)
#define ANC_AR_RSSI2_DB_MIN_POS  (8U)
#define ANC_AR_RSSI2_DB_MIN_MSK  (0xffUL << ANC_AR_RSSI2_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AR_RSSI2_DB_MIN      ANC_AR_RSSI2_DB_MIN_MSK
#define ANC_AR_RSSI2_DB_MIN_W(X) ((X) << ANC_AR_RSSI2_DB_MIN_POS)
#define ANC_AR_RSSI3_DB_MAX_POS  (16U)
#define ANC_AR_RSSI3_DB_MAX_MSK  (0xffUL << ANC_AR_RSSI3_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AR_RSSI3_DB_MAX      ANC_AR_RSSI3_DB_MAX_MSK
#define ANC_AR_RSSI3_DB_MAX_W(X) ((X) << ANC_AR_RSSI3_DB_MAX_POS)
#define ANC_AR_RSSI3_DB_MIN_POS  (24U)
#define ANC_AR_RSSI3_DB_MIN_MSK  (0xffUL << ANC_AR_RSSI3_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AR_RSSI3_DB_MIN      ANC_AR_RSSI3_DB_MIN_MSK
#define ANC_AR_RSSI3_DB_MIN_W(X) ((X) << ANC_AR_RSSI3_DB_MIN_POS)

//AL_ASRC offsetaddress : 0x0C10
//AL_ASRC RegResetValue : 0x0000000
#define ANC_ASRC_ENABLE_POS         (0U)
#define ANC_ASRC_ENABLE_MSK         (0x1UL << ANC_ASRC_ENABLE_POS) /*!< ASRC enable*/
#define ANC_ASRC_ENABLE             ANC_ASRC_ENABLE_MSK
#define ANC_ASRC_ENABLE_W(X)        ((X) << ANC_ASRC_ENABLE_POS)
#define ANC_ASRC_BYPASS_POS         (1U)
#define ANC_ASRC_BYPASS_MSK         (0x1UL << ANC_ASRC_BYPASS_POS) /*!< ASRC bypass control*/
#define ANC_ASRC_BYPASS             ANC_ASRC_BYPASS_MSK
#define ANC_ASRC_BYPASS_W(X)        ((X) << ANC_ASRC_BYPASS_POS)
#define ANC_ASRC_WAIT_CNT_POS       (4U)
#define ANC_ASRC_WAIT_CNT_MSK       (0x3fUL << ANC_ASRC_WAIT_CNT_POS) /*!< Number of sample cycle waited between sample adjustment and fifo request adjustment for ASRC*/
#define ANC_ASRC_WAIT_CNT           ANC_ASRC_WAIT_CNT_MSK
#define ANC_ASRC_WAIT_CNT_W(X)      ((X) << ANC_ASRC_WAIT_CNT_POS)
#define ANC_ASRC_FERR_POS           (12U)
#define ANC_ASRC_FERR_MSK           (0x7fUL << ANC_ASRC_FERR_POS) /*!< ASRC frequency error (7-bit signed)*/
#define ANC_ASRC_FERR               ANC_ASRC_FERR_MSK
#define ANC_ASRC_FERR_W(X)          ((X) << ANC_ASRC_FERR_POS)
#define ANC_ASRC_L_FIFO_STATUS_POS  (20U)
#define ANC_ASRC_L_FIFO_STATUS_MSK  (0xffUL << ANC_ASRC_L_FIFO_STATUS_POS) /*!< Bit7: push_empty*/
#define ANC_ASRC_L_FIFO_STATUS      ANC_ASRC_L_FIFO_STATUS_MSK
#define ANC_ASRC_L_FIFO_STATUS_W(X) ((X) << ANC_ASRC_L_FIFO_STATUS_POS)

//AR_ASRC offsetaddress : 0x0C14
//AR_ASRC RegResetValue : 0x0000000
#define ANC_FREQ_ERR_PPM_POS        (0U)
#define ANC_FREQ_ERR_PPM_MSK        (0x7fUL << ANC_FREQ_ERR_PPM_POS) /*!< ASRC frequency error (7-bit signed)*/
#define ANC_FREQ_ERR_PPM            ANC_FREQ_ERR_PPM_MSK
#define ANC_FREQ_ERR_PPM_W(X)       ((X) << ANC_FREQ_ERR_PPM_POS)
#define ANC_ASRC_R_FIFO_STATUS_POS  (20U)
#define ANC_ASRC_R_FIFO_STATUS_MSK  (0xffUL << ANC_ASRC_R_FIFO_STATUS_POS) /*!< Bit7: push_empty*/
#define ANC_ASRC_R_FIFO_STATUS      ANC_ASRC_R_FIFO_STATUS_MSK
#define ANC_ASRC_R_FIFO_STATUS_W(X) ((X) << ANC_ASRC_R_FIFO_STATUS_POS)

//ANC_R_RSSI_DEBUG3 offsetaddress : 0x0C18
//ANC_R_RSSI_DEBUG3 RegResetValue : 0x0000000
#define ANC_AR_RSSI4_DB_MAX_POS   (0U)
#define ANC_AR_RSSI4_DB_MAX_MSK   (0xffUL << ANC_AR_RSSI4_DB_MAX_POS) /*!< The maximum input noise intensity value is dB*/
#define ANC_AR_RSSI4_DB_MAX       ANC_AR_RSSI4_DB_MAX_MSK
#define ANC_AR_RSSI4_DB_MAX_W(X)  ((X) << ANC_AR_RSSI4_DB_MAX_POS)
#define ANC_AR_RSSI4_DB_MIN_POS   (8U)
#define ANC_AR_RSSI4_DB_MIN_MSK   (0xffUL << ANC_AR_RSSI4_DB_MIN_POS) /*!< The minimum input noise intensity value is dB*/
#define ANC_AR_RSSI4_DB_MIN       ANC_AR_RSSI4_DB_MIN_MSK
#define ANC_AR_RSSI4_DB_MIN_W(X)  ((X) << ANC_AR_RSSI4_DB_MIN_POS)
#define ANC_AR_RSSI0_DB_MASK_POS  (16U)
#define ANC_AR_RSSI0_DB_MASK_MSK  (0x1UL << ANC_AR_RSSI0_DB_MASK_POS) /*!< 1: No comparison 0: Compare*/
#define ANC_AR_RSSI0_DB_MASK      ANC_AR_RSSI0_DB_MASK_MSK
#define ANC_AR_RSSI0_DB_MASK_W(X) ((X) << ANC_AR_RSSI0_DB_MASK_POS)
#define ANC_AR_RSSI1_DB_MASK_POS  (17U)
#define ANC_AR_RSSI1_DB_MASK_MSK  (0x1UL << ANC_AR_RSSI1_DB_MASK_POS) /*!< 1: No comparison 0: Compare*/
#define ANC_AR_RSSI1_DB_MASK      ANC_AR_RSSI1_DB_MASK_MSK
#define ANC_AR_RSSI1_DB_MASK_W(X) ((X) << ANC_AR_RSSI1_DB_MASK_POS)
#define ANC_AR_RSSI2_DB_MASK_POS  (18U)
#define ANC_AR_RSSI2_DB_MASK_MSK  (0x1UL << ANC_AR_RSSI2_DB_MASK_POS) /*!< 1: No comparison 0: Compare*/
#define ANC_AR_RSSI2_DB_MASK      ANC_AR_RSSI2_DB_MASK_MSK
#define ANC_AR_RSSI2_DB_MASK_W(X) ((X) << ANC_AR_RSSI2_DB_MASK_POS)
#define ANC_AR_RSSI3_DB_MASK_POS  (19U)
#define ANC_AR_RSSI3_DB_MASK_MSK  (0x1UL << ANC_AR_RSSI3_DB_MASK_POS) /*!< 1: No comparison 0: Compare*/
#define ANC_AR_RSSI3_DB_MASK      ANC_AR_RSSI3_DB_MASK_MSK
#define ANC_AR_RSSI3_DB_MASK_W(X) ((X) << ANC_AR_RSSI3_DB_MASK_POS)
#define ANC_AR_RSSI4_DB_MASK_POS  (20U)
#define ANC_AR_RSSI4_DB_MASK_MSK  (0x1UL << ANC_AR_RSSI4_DB_MASK_POS) /*!< 1: No comparison 0: Compare*/
#define ANC_AR_RSSI4_DB_MASK      ANC_AR_RSSI4_DB_MASK_MSK
#define ANC_AR_RSSI4_DB_MASK_W(X) ((X) << ANC_AR_RSSI4_DB_MASK_POS)

//AR_ANC_IIR_FB offsetaddress : 0x0C20
//AR_ANC_IIR_FB RegResetValue : 0x0000000
#define ANC_IIR_FB_WF_R_POS   (0U)
#define ANC_IIR_FB_WF_R_MSK   (0x7UL << ANC_IIR_FB_WF_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_WF_R       ANC_IIR_FB_WF_R_MSK
#define ANC_IIR_FB_WF_R_W(X)  ((X) << ANC_IIR_FB_WF_R_POS)
#define ANC_IIR_FB_EQ_R_POS   (4U)
#define ANC_IIR_FB_EQ_R_MSK   (0x7UL << ANC_IIR_FB_EQ_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_EQ_R       ANC_IIR_FB_EQ_R_MSK
#define ANC_IIR_FB_EQ_R_W(X)  ((X) << ANC_IIR_FB_EQ_R_POS)
#define ANC_IIR_FB_WB_R_POS   (8U)
#define ANC_IIR_FB_WB_R_MSK   (0x7UL << ANC_IIR_FB_WB_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_WB_R       ANC_IIR_FB_WB_R_MSK
#define ANC_IIR_FB_WB_R_W(X)  ((X) << ANC_IIR_FB_WB_R_POS)
#define ANC_IIR_FB_SB_R_POS   (12U)
#define ANC_IIR_FB_SB_R_MSK   (0x7UL << ANC_IIR_FB_SB_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_SB_R       ANC_IIR_FB_SB_R_MSK
#define ANC_IIR_FB_SB_R_W(X)  ((X) << ANC_IIR_FB_SB_R_POS)
#define ANC_IIR_SEL_WF_R_POS  (16U)
#define ANC_IIR_SEL_WF_R_MSK  (0x7UL << ANC_IIR_SEL_WF_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_WF_R      ANC_IIR_SEL_WF_R_MSK
#define ANC_IIR_SEL_WF_R_W(X) ((X) << ANC_IIR_SEL_WF_R_POS)
#define ANC_IIR_SEL_EQ_R_POS  (20U)
#define ANC_IIR_SEL_EQ_R_MSK  (0x7UL << ANC_IIR_SEL_EQ_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_EQ_R      ANC_IIR_SEL_EQ_R_MSK
#define ANC_IIR_SEL_EQ_R_W(X) ((X) << ANC_IIR_SEL_EQ_R_POS)
#define ANC_IIR_SEL_WB_R_POS  (24U)
#define ANC_IIR_SEL_WB_R_MSK  (0x7UL << ANC_IIR_SEL_WB_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_WB_R      ANC_IIR_SEL_WB_R_MSK
#define ANC_IIR_SEL_WB_R_W(X) ((X) << ANC_IIR_SEL_WB_R_POS)
#define ANC_IIR_SEL_SB_R_POS  (28U)
#define ANC_IIR_SEL_SB_R_MSK  (0x7UL << ANC_IIR_SEL_SB_R_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_SB_R      ANC_IIR_SEL_SB_R_MSK
#define ANC_IIR_SEL_SB_R_W(X) ((X) << ANC_IIR_SEL_SB_R_POS)

//AL_ANC_IIR_FB offsetaddress : 0x0C24
//AL_ANC_IIR_FB RegResetValue : 0x0000000
#define ANC_IIR_FB_WF_L_POS   (0U)
#define ANC_IIR_FB_WF_L_MSK   (0x7UL << ANC_IIR_FB_WF_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_WF_L       ANC_IIR_FB_WF_L_MSK
#define ANC_IIR_FB_WF_L_W(X)  ((X) << ANC_IIR_FB_WF_L_POS)
#define ANC_IIR_FB_EQ_L_POS   (4U)
#define ANC_IIR_FB_EQ_L_MSK   (0x7UL << ANC_IIR_FB_EQ_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_EQ_L       ANC_IIR_FB_EQ_L_MSK
#define ANC_IIR_FB_EQ_L_W(X)  ((X) << ANC_IIR_FB_EQ_L_POS)
#define ANC_IIR_FB_WB_L_POS   (8U)
#define ANC_IIR_FB_WB_L_MSK   (0x7UL << ANC_IIR_FB_WB_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_WB_L       ANC_IIR_FB_WB_L_MSK
#define ANC_IIR_FB_WB_L_W(X)  ((X) << ANC_IIR_FB_WB_L_POS)
#define ANC_IIR_FB_SB_L_POS   (12U)
#define ANC_IIR_FB_SB_L_MSK   (0x7UL << ANC_IIR_FB_SB_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_FB_SB_L       ANC_IIR_FB_SB_L_MSK
#define ANC_IIR_FB_SB_L_W(X)  ((X) << ANC_IIR_FB_SB_L_POS)
#define ANC_IIR_SEL_WF_L_POS  (16U)
#define ANC_IIR_SEL_WF_L_MSK  (0x7UL << ANC_IIR_SEL_WF_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_WF_L      ANC_IIR_SEL_WF_L_MSK
#define ANC_IIR_SEL_WF_L_W(X) ((X) << ANC_IIR_SEL_WF_L_POS)
#define ANC_IIR_SEL_EQ_L_POS  (20U)
#define ANC_IIR_SEL_EQ_L_MSK  (0x7UL << ANC_IIR_SEL_EQ_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_EQ_L      ANC_IIR_SEL_EQ_L_MSK
#define ANC_IIR_SEL_EQ_L_W(X) ((X) << ANC_IIR_SEL_EQ_L_POS)
#define ANC_IIR_SEL_WB_L_POS  (24U)
#define ANC_IIR_SEL_WB_L_MSK  (0x7UL << ANC_IIR_SEL_WB_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_WB_L      ANC_IIR_SEL_WB_L_MSK
#define ANC_IIR_SEL_WB_L_W(X) ((X) << ANC_IIR_SEL_WB_L_POS)
#define ANC_IIR_SEL_SB_L_POS  (28U)
#define ANC_IIR_SEL_SB_L_MSK  (0x7UL << ANC_IIR_SEL_SB_L_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_IIR_SEL_SB_L      ANC_IIR_SEL_SB_L_MSK
#define ANC_IIR_SEL_SB_L_W(X) ((X) << ANC_IIR_SEL_SB_L_POS)

//ANC_EN_48M_96M offsetaddress : 0x0C28
//ANC_EN_48M_96M RegResetValue : 0x0000000
#define ANC_EN_48M_POS  (0U)
#define ANC_EN_48M_MSK  (0x1UL << ANC_EN_48M_POS) /*!< ANC processing clock selection: 0:24MHZ, 1:48MHz*/
#define ANC_EN_48M      ANC_EN_48M_MSK
#define ANC_EN_48M_W(X) ((X) << ANC_EN_48M_POS)
#define ANC_EN_96M_POS  (1U)
#define ANC_EN_96M_MSK  (0x1UL << ANC_EN_96M_POS) /*!< ANC processing clock selection: 0:24/48MHZ, 1:96MHz*/
#define ANC_EN_96M      ANC_EN_96M_MSK
#define ANC_EN_96M_W(X) ((X) << ANC_EN_96M_POS)

//PPM_ADJ_CRTL0 offsetaddress : 0x0C2C
//PPM_ADJ_CRTL0 RegResetValue : 0x0000000
#define ANC_CNT_COM_EN_POS    (0U)
#define ANC_CNT_COM_EN_MSK    (0x1UL << ANC_CNT_COM_EN_POS) /*!< Enable compensation of local count value, 0: The local count value does not compensate, keep cnt_com=0, 1: Enable compensation of local count value*/
#define ANC_CNT_COM_EN        ANC_CNT_COM_EN_MSK
#define ANC_CNT_COM_EN_W(X)   ((X) << ANC_CNT_COM_EN_POS)
#define ANC_CNT_DIF_MAX_POS   (4U)
#define ANC_CNT_DIF_MAX_MSK   (0xfffUL << ANC_CNT_DIF_MAX_POS) /*!< When the absolute value of the counter count deviation exceeds this threshold, set error err_type=1, and an interrupt is generated.*/
#define ANC_CNT_DIF_MAX       ANC_CNT_DIF_MAX_MSK
#define ANC_CNT_DIF_MAX_W(X)  ((X) << ANC_CNT_DIF_MAX_POS)
#define ANC_CNT_DIF_MIN_POS   (16U)
#define ANC_CNT_DIF_MIN_MSK   (0xffUL << ANC_CNT_DIF_MIN_POS) /*!< The absolute value of the minimum counter deviation that needs to be met for the start frequency deviation control word adjustment*/
#define ANC_CNT_DIF_MIN       ANC_CNT_DIF_MIN_MSK
#define ANC_CNT_DIF_MIN_W(X)  ((X) << ANC_CNT_DIF_MIN_POS)
#define ANC_MAX_ADJ_STEP_POS  (24U)
#define ANC_MAX_ADJ_STEP_MSK  (0x7fUL << ANC_MAX_ADJ_STEP_POS) /*!< The maximum step size for adjusting the frequency deviation control word according to the counter deviation is ppm*/
#define ANC_MAX_ADJ_STEP      ANC_MAX_ADJ_STEP_MSK
#define ANC_MAX_ADJ_STEP_W(X) ((X) << ANC_MAX_ADJ_STEP_POS)
#define ANC_ID_MASK_EN_POS    (31U)
#define ANC_ID_MASK_EN_MSK    (0x1UL << ANC_ID_MASK_EN_POS) /*!< Block Bluetooth ID packets enable, 1 enable blocking*/
#define ANC_ID_MASK_EN        ANC_ID_MASK_EN_MSK
#define ANC_ID_MASK_EN_W(X)   ((X) << ANC_ID_MASK_EN_POS)

//PPM_ADJ_CRTL1 offsetaddress : 0x0C30
//PPM_ADJ_CRTL1 RegResetValue : 0x0000000
#define ANC_OS_ADJ_STEP_POS  (0U)
#define ANC_OS_ADJ_STEP_MSK  (0x7fUL << ANC_OS_ADJ_STEP_POS) /*!< To compensate for the accumulated offset, the step size of the frequency deviation control word is fine-tuned, the unit is ppm*/
#define ANC_OS_ADJ_STEP      ANC_OS_ADJ_STEP_MSK
#define ANC_OS_ADJ_STEP_W(X) ((X) << ANC_OS_ADJ_STEP_POS)
#define ANC_PKT_MASK_EN_POS  (7U)
#define ANC_PKT_MASK_EN_MSK  (0x1UL << ANC_PKT_MASK_EN_POS) /*!< Block all Bluetooth packets enabled, 1 enable blocking*/
#define ANC_PKT_MASK_EN      ANC_PKT_MASK_EN_MSK
#define ANC_PKT_MASK_EN_W(X) ((X) << ANC_PKT_MASK_EN_POS)
#define ANC_OS_FB_MAX_POS    (8U)
#define ANC_OS_FB_MAX_MSK    (0xffffUL << ANC_OS_FB_MAX_POS) /*!< When the absolute value of the accumulated offset exceeds this threshold, set error err_type=2, and an interrupt is generated.*/
#define ANC_OS_FB_MAX        ANC_OS_FB_MAX_MSK
#define ANC_OS_FB_MAX_W(X)   ((X) << ANC_OS_FB_MAX_POS)
#define ANC_OS_FB_MIN_POS    (24U)
#define ANC_OS_FB_MIN_MSK    (0xffUL << ANC_OS_FB_MIN_POS) /*!< When the accumulated offset is greater than this threshold, fine-tune the frequency deviation control word*/
#define ANC_OS_FB_MIN        ANC_OS_FB_MIN_MSK
#define ANC_OS_FB_MIN_W(X)   ((X) << ANC_OS_FB_MIN_POS)

//PPM_ADJ_CRTL2 offsetaddress : 0x0C34
//PPM_ADJ_CRTL2 RegResetValue : 0x0000000
#define ANC_OS_MIN_CNT_POS   (0U)
#define ANC_OS_MIN_CNT_MSK   (0x1ffffffUL << ANC_OS_MIN_CNT_POS) /*!< When the accumulated offset is greater than this threshold, fine-tune the frequency deviation control word*/
#define ANC_OS_MIN_CNT       ANC_OS_MIN_CNT_MSK
#define ANC_OS_MIN_CNT_W(X)  ((X) << ANC_OS_MIN_CNT_POS)
#define ANC_MAX_ERR_PPM_POS  (26U)
#define ANC_MAX_ERR_PPM_MSK  (0x3fUL << ANC_MAX_ERR_PPM_POS) /*!< When the absolute value of the frequency deviation control word exceeds this threshold, set error err_type=3, and an interrupt is generated.*/
#define ANC_MAX_ERR_PPM      ANC_MAX_ERR_PPM_MSK
#define ANC_MAX_ERR_PPM_W(X) ((X) << ANC_MAX_ERR_PPM_POS)

//PPM_ADJ_CRTL3 offsetaddress : 0x0C38
//PPM_ADJ_CRTL3 RegResetValue : 0x0000000
#define ANC_OS_REF_POS  (0U)
#define ANC_OS_REF_MSK  (0xffffffUL << ANC_OS_REF_POS) /*!< The software-defined cumulative offset adjusted reference value, which the hardware approximates the reference value by adjusting the frequency deviation.*/
#define ANC_OS_REF      ANC_OS_REF_MSK
#define ANC_OS_REF_W(X) ((X) << ANC_OS_REF_POS)
#define ANC_OS_SR_POS   (24U)
#define ANC_OS_SR_MSK   (0x1UL << ANC_OS_SR_POS) /*!< Select the input source of the accumulated offset, 0: Calculate based on the local counter (open loop), 1: Calculate based on the number of valid pulses input from ASRC (closed loop)*/
#define ANC_OS_SR       ANC_OS_SR_MSK
#define ANC_OS_SR_W(X)  ((X) << ANC_OS_SR_POS)

//PPM_ADJ_CRTL4 offsetaddress : 0x0C3C
//PPM_ADJ_CRTL4 RegResetValue : 0x0000000
#define ANC_JUDGE_SEL_POS     (0U)
#define ANC_JUDGE_SEL_MSK     (0x1UL << ANC_JUDGE_SEL_POS) /*!< Select the source of the reference time pulse, 1: the locally restored Bluetooth slot start pulse, 0: the locally received the synchronization pulse of the mobile phone Bluetooth data packet.*/
#define ANC_JUDGE_SEL         ANC_JUDGE_SEL_MSK
#define ANC_JUDGE_SEL_W(X)    ((X) << ANC_JUDGE_SEL_POS)
#define ANC_PPM_USR_EN_POS    (1U)
#define ANC_PPM_USR_EN_MSK    (0x1UL << ANC_PPM_USR_EN_POS) /*!< Enable frequency deviation control word software configuration, 0: Not enabled, 1: Software configuration enable, freq_err_ppm = freq_ppm_usr*/
#define ANC_PPM_USR_EN        ANC_PPM_USR_EN_MSK
#define ANC_PPM_USR_EN_W(X)   ((X) << ANC_PPM_USR_EN_POS)
#define ANC_PPM_NEG_EN_POS    (2U)
#define ANC_PPM_NEG_EN_MSK    (0x1UL << ANC_PPM_NEG_EN_POS) /*!< Enable the output of the frequency deviation control word after being negative, 0: Not enabled, output directly, 1: output after taking negative value*/
#define ANC_PPM_NEG_EN        ANC_PPM_NEG_EN_MSK
#define ANC_PPM_NEG_EN_W(X)   ((X) << ANC_PPM_NEG_EN_POS)
#define ANC_PPM_RSTR_EN_POS   (3U)
#define ANC_PPM_RSTR_EN_MSK   (0x1UL << ANC_PPM_RSTR_EN_POS) /*!< eRestores the stored frequency deviation control word at the end of the cumulative offset adjustment, 0: Not enabled, the control word remains unchanged, 1: Enable recovery*/
#define ANC_PPM_RSTR_EN       ANC_PPM_RSTR_EN_MSK
#define ANC_PPM_RSTR_EN_W(X)  ((X) << ANC_PPM_RSTR_EN_POS)
#define ANC_FREQ_PPM_USR_POS  (4U)
#define ANC_FREQ_PPM_USR_MSK  (0x7fUL << ANC_FREQ_PPM_USR_POS) /*!< The frequency deviation control word manually configured by the software is ppm, that is, 1/1048576*/
#define ANC_FREQ_PPM_USR      ANC_FREQ_PPM_USR_MSK
#define ANC_FREQ_PPM_USR_W(X) ((X) << ANC_FREQ_PPM_USR_POS)
#define ANC_DEL_OS_THRE_POS   (12U)
#define ANC_DEL_OS_THRE_MSK   (0xffUL << ANC_DEL_OS_THRE_POS) /*!< When fine-tuning the frequency deviation, the absolute value of the cumulative offset change must be greater than this threshold to maintain the frequency control word unchanged.*/
#define ANC_DEL_OS_THRE       ANC_DEL_OS_THRE_MSK
#define ANC_DEL_OS_THRE_W(X)  ((X) << ANC_DEL_OS_THRE_POS)
#define ANC_ID_MASK_THRE_POS  (24U)
#define ANC_ID_MASK_THRE_MSK  (0xffUL << ANC_ID_MASK_THRE_POS) /*!< Masked Bluetooth packet delay control threshold (delay 8* id_mask_thre 6.144MHz clock cycles)*/
#define ANC_ID_MASK_THRE      ANC_ID_MASK_THRE_MSK
#define ANC_ID_MASK_THRE_W(X) ((X) << ANC_ID_MASK_THRE_POS)

//AR_FIR_FB_HF offsetaddress : 0x0C40
//AR_FIR_FB_HF RegResetValue : 0x0000000
#define ANC_AR_FIR_FB_HF_POS  (0U)
#define ANC_AR_FIR_FB_HF_MSK  (0x7UL << ANC_AR_FIR_FB_HF_POS) /*!< FIR intercept bit width control register 0~7 corresponds to decimal bits 20~27bit*/
#define ANC_AR_FIR_FB_HF      ANC_AR_FIR_FB_HF_MSK
#define ANC_AR_FIR_FB_HF_W(X) ((X) << ANC_AR_FIR_FB_HF_POS)

//AR_FIR_COE_A offsetaddress : 0x0C44
//AR_FIR_COE_A RegResetValue : 0x0000000
#define ANC_AR_FIR_COE_A_POS  (0U)
#define ANC_AR_FIR_COE_A_MSK  (0xffffffffUL << ANC_AR_FIR_COE_A_POS) /*!< FIR coefficient address extension register*/
#define ANC_AR_FIR_COE_A      ANC_AR_FIR_COE_A_MSK
#define ANC_AR_FIR_COE_A_W(X) ((X) << ANC_AR_FIR_COE_A_POS)

//AR_FIR_COE_D offsetaddress : 0x0C48
//AR_FIR_COE_D RegResetValue : 0x0000000
#define ANC_AR_FIR_COE_D_POS  (0U)
#define ANC_AR_FIR_COE_D_MSK  (0xffffffffUL << ANC_AR_FIR_COE_D_POS) /*!< FIR coefficient data extension register*/
#define ANC_AR_FIR_COE_D      ANC_AR_FIR_COE_D_MSK
#define ANC_AR_FIR_COE_D_W(X) ((X) << ANC_AR_FIR_COE_D_POS)

//AR_FIR_INIT_DONE offsetaddress : 0x0C4C
//AR_FIR_INIT_DONE RegResetValue : 0x0000000
#define ANC_AR_FIR_INIT_DONE_POS  (0U)
#define ANC_AR_FIR_INIT_DONE_MSK  (0x1UL << ANC_AR_FIR_INIT_DONE_POS) /*!< The state signal of the FIR memory coefficient initialization completed, 1 indicates completion*/
#define ANC_AR_FIR_INIT_DONE      ANC_AR_FIR_INIT_DONE_MSK
#define ANC_AR_FIR_INIT_DONE_W(X) ((X) << ANC_AR_FIR_INIT_DONE_POS)

//AR_FIR_ENABLE offsetaddress : 0x0C50
//AR_FIR_ENABLE RegResetValue : 0x0000000
#define ANC_AR_FIR_ENABLE_POS  (0U)
#define ANC_AR_FIR_ENABLE_MSK  (0x1UL << ANC_AR_FIR_ENABLE_POS) /*!< Set 0 when configuring the FIR filter coefficient register, set 1 when configuring the configuration*/
#define ANC_AR_FIR_ENABLE      ANC_AR_FIR_ENABLE_MSK
#define ANC_AR_FIR_ENABLE_W(X) ((X) << ANC_AR_FIR_ENABLE_POS)

//AL_FIR_FB_HF offsetaddress : 0x0C54
//AL_FIR_FB_HF RegResetValue : 0x0000000
#define ANC_AL_FIR_FB_HF_POS  (0U)
#define ANC_AL_FIR_FB_HF_MSK  (0x7UL << ANC_AL_FIR_FB_HF_POS) /*!< FIR intercept bit width control register 0~7 corresponds to decimal bits 20~27bit*/
#define ANC_AL_FIR_FB_HF      ANC_AL_FIR_FB_HF_MSK
#define ANC_AL_FIR_FB_HF_W(X) ((X) << ANC_AL_FIR_FB_HF_POS)

//AL_FIR_COE_A offsetaddress : 0x0C58
//AL_FIR_COE_A RegResetValue : 0x0000000
#define ANC_AL_FIR_COE_A_POS  (0U)
#define ANC_AL_FIR_COE_A_MSK  (0xffffffffUL << ANC_AL_FIR_COE_A_POS) /*!< FIR coefficient address extension register*/
#define ANC_AL_FIR_COE_A      ANC_AL_FIR_COE_A_MSK
#define ANC_AL_FIR_COE_A_W(X) ((X) << ANC_AL_FIR_COE_A_POS)

//AL_FIR_COE_D offsetaddress : 0x0C5C
//AL_FIR_COE_D RegResetValue : 0x0000000
#define ANC_AL_FIR_COE_D_POS  (0U)
#define ANC_AL_FIR_COE_D_MSK  (0xffffffffUL << ANC_AL_FIR_COE_D_POS) /*!< FIR coefficient data extension register*/
#define ANC_AL_FIR_COE_D      ANC_AL_FIR_COE_D_MSK
#define ANC_AL_FIR_COE_D_W(X) ((X) << ANC_AL_FIR_COE_D_POS)

//AL_FIR_INIT_DONE offsetaddress : 0x0C60
//AL_FIR_INIT_DONE RegResetValue : 0x0000000
#define ANC_AL_FIR_INIT_DONE_POS  (0U)
#define ANC_AL_FIR_INIT_DONE_MSK  (0x1UL << ANC_AL_FIR_INIT_DONE_POS) /*!< The state signal of the FIR memory coefficient initialization completed, 1 indicates completion*/
#define ANC_AL_FIR_INIT_DONE      ANC_AL_FIR_INIT_DONE_MSK
#define ANC_AL_FIR_INIT_DONE_W(X) ((X) << ANC_AL_FIR_INIT_DONE_POS)

//AL_FIR_ENABLE offsetaddress : 0x0C64
//AL_FIR_ENABLE RegResetValue : 0x0000000
#define ANC_AL_FIR_ENABLE_POS  (0U)
#define ANC_AL_FIR_ENABLE_MSK  (0x1UL << ANC_AL_FIR_ENABLE_POS) /*!< Set 0 when configuring the FIR filter coefficient register, set 1 when configuring the configuration*/
#define ANC_AL_FIR_ENABLE      ANC_AL_FIR_ENABLE_MSK
#define ANC_AL_FIR_ENABLE_W(X) ((X) << ANC_AL_FIR_ENABLE_POS)

//AR_FIR_COE_Q offsetaddress : 0x0C68
//AR_FIR_COE_Q RegResetValue : 0x0000000
#define ANC_AR_FIR_COE_Q_POS  (0U)
#define ANC_AR_FIR_COE_Q_MSK  (0xffffffffUL << ANC_AR_FIR_COE_Q_POS) /*!< FIR coefficient readback data extension register*/
#define ANC_AR_FIR_COE_Q      ANC_AR_FIR_COE_Q_MSK
#define ANC_AR_FIR_COE_Q_W(X) ((X) << ANC_AR_FIR_COE_Q_POS)

//AL_FIR_COE_Q offsetaddress : 0x0C6C
//AL_FIR_COE_Q RegResetValue : 0x0000000
#define ANC_AL_FIR_COE_Q_POS  (0U)
#define ANC_AL_FIR_COE_Q_MSK  (0xffffffffUL << ANC_AL_FIR_COE_Q_POS) /*!< FIR coefficient readback data extension register*/
#define ANC_AL_FIR_COE_Q      ANC_AL_FIR_COE_Q_MSK
#define ANC_AL_FIR_COE_Q_W(X) ((X) << ANC_AL_FIR_COE_Q_POS)

//AL_ASRC2 offsetaddress : 0x0CF0
//AL_ASRC2 RegResetValue : 0x0000000
#define ANC_AL_FERR_SEL_I_POS     (0U)
#define ANC_AL_FERR_SEL_I_MSK     (0x1UL << ANC_AL_FERR_SEL_I_POS) /*!< ASRC ferr_sel_i*/
#define ANC_AL_FERR_SEL_I         ANC_AL_FERR_SEL_I_MSK
#define ANC_AL_FERR_SEL_I_W(X)    ((X) << ANC_AL_FERR_SEL_I_POS)
#define ANC_AL_FERR_EXPAND_I_POS  (1U)
#define ANC_AL_FERR_EXPAND_I_MSK  (0x7ffUL << ANC_AL_FERR_EXPAND_I_POS) /*!< ASRC ferr_expand_i*/
#define ANC_AL_FERR_EXPAND_I      ANC_AL_FERR_EXPAND_I_MSK
#define ANC_AL_FERR_EXPAND_I_W(X) ((X) << ANC_AL_FERR_EXPAND_I_POS)

//AR_ASRC2 offsetaddress : 0x0CF4
//AR_ASRC2 RegResetValue : 0x0000000
#define ANC_AR_FERR_SEL_I_POS     (0U)
#define ANC_AR_FERR_SEL_I_MSK     (0x1UL << ANC_AR_FERR_SEL_I_POS) /*!< ASRC ferr_sel_i*/
#define ANC_AR_FERR_SEL_I         ANC_AR_FERR_SEL_I_MSK
#define ANC_AR_FERR_SEL_I_W(X)    ((X) << ANC_AR_FERR_SEL_I_POS)
#define ANC_AR_FERR_EXPAND_I_POS  (1U)
#define ANC_AR_FERR_EXPAND_I_MSK  (0x7ffUL << ANC_AR_FERR_EXPAND_I_POS) /*!< ASRC ferr_expand_i*/
#define ANC_AR_FERR_EXPAND_I      ANC_AR_FERR_EXPAND_I_MSK
#define ANC_AR_FERR_EXPAND_I_W(X) ((X) << ANC_AR_FERR_EXPAND_I_POS)

//ANC_R_TR_IIR offsetaddress : 0x0D00
//ANC_R_TR_IIR RegResetValue : 0x0000000
#define ANC_AR_IIR_FB_TR_POS      (0U)
#define ANC_AR_IIR_FB_TR_MSK      (0x7UL << ANC_AR_IIR_FB_TR_POS) /*!< The right MN_IIR filter coefficient decimal bit width selection: 0:23 bits, 1:24 bits,..., 7:30 bits*/
#define ANC_AR_IIR_FB_TR          ANC_AR_IIR_FB_TR_MSK
#define ANC_AR_IIR_FB_TR_W(X)     ((X) << ANC_AR_IIR_FB_TR_POS)
#define ANC_AR_TR_IIR_EN_POS      (3U)
#define ANC_AR_TR_IIR_EN_MSK      (0x1UL << ANC_AR_TR_IIR_EN_POS) /*!< The right MN_IIR filter module enables Write 1 enables*/
#define ANC_AR_TR_IIR_EN          ANC_AR_TR_IIR_EN_MSK
#define ANC_AR_TR_IIR_EN_W(X)     ((X) << ANC_AR_TR_IIR_EN_POS)
#define ANC_AR_BYPASS_TR_IIR_POS  (4U)
#define ANC_AR_BYPASS_TR_IIR_MSK  (0x1UL << ANC_AR_BYPASS_TR_IIR_POS) /*!< The right MN_IIR filter bypass enable Write 1 enable*/
#define ANC_AR_BYPASS_TR_IIR      ANC_AR_BYPASS_TR_IIR_MSK
#define ANC_AR_BYPASS_TR_IIR_W(X) ((X) << ANC_AR_BYPASS_TR_IIR_POS)
#define ANC_AR_IIR_SEL_TR_POS     (5U)
#define ANC_AR_IIR_SEL_TR_MSK     (0x7UL << ANC_AR_IIR_SEL_TR_POS) /*!< The low input of the iir filter is 0: 4 bits, 1: 5 bits, 2: 6, 3: 7 bits, others: 8 bits*/
#define ANC_AR_IIR_SEL_TR         ANC_AR_IIR_SEL_TR_MSK
#define ANC_AR_IIR_SEL_TR_W(X)    ((X) << ANC_AR_IIR_SEL_TR_POS)

//ANC_L_IIR_ORDER_SEL offsetaddress : 0x0D04
//ANC_L_IIR_ORDER_SEL RegResetValue : 0x0000000
#define ANC_AL_IIR_ORDER_SEL_SB_POS  (0U)
#define ANC_AL_IIR_ORDER_SEL_SB_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_SB_POS) /*!< al_iir_order_sel_sb 20th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_SB      ANC_AL_IIR_ORDER_SEL_SB_MSK
#define ANC_AL_IIR_ORDER_SEL_SB_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_SB_POS)
#define ANC_AL_IIR_ORDER_SEL_FB_POS  (5U)
#define ANC_AL_IIR_ORDER_SEL_FB_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_FB_POS) /*!< al_iir_order_sel_fb 20th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_FB      ANC_AL_IIR_ORDER_SEL_FB_MSK
#define ANC_AL_IIR_ORDER_SEL_FB_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_FB_POS)
#define ANC_AL_IIR_ORDER_SEL_WF_POS  (10U)
#define ANC_AL_IIR_ORDER_SEL_WF_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_WF_POS) /*!< al_iir_order_sel_wf 20th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_WF      ANC_AL_IIR_ORDER_SEL_WF_MSK
#define ANC_AL_IIR_ORDER_SEL_WF_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_WF_POS)
#define ANC_AL_IIR_ORDER_SEL_MN_POS  (15U)
#define ANC_AL_IIR_ORDER_SEL_MN_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_MN_POS) /*!< al_iir_order_sel_mn 10th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_MN      ANC_AL_IIR_ORDER_SEL_MN_MSK
#define ANC_AL_IIR_ORDER_SEL_MN_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_MN_POS)
#define ANC_AL_IIR_ORDER_SEL_SC_POS  (20U)
#define ANC_AL_IIR_ORDER_SEL_SC_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_SC_POS) /*!< al_iir_order_sel_sc 10th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_SC      ANC_AL_IIR_ORDER_SEL_SC_MSK
#define ANC_AL_IIR_ORDER_SEL_SC_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_SC_POS)
#define ANC_AL_IIR_ORDER_SEL_EQ_POS  (25U)
#define ANC_AL_IIR_ORDER_SEL_EQ_MSK  (0x1fUL << ANC_AL_IIR_ORDER_SEL_EQ_POS) /*!< al_iir_order_sel_eq 10th order filter, the current configuration order = value 1*/
#define ANC_AL_IIR_ORDER_SEL_EQ      ANC_AL_IIR_ORDER_SEL_EQ_MSK
#define ANC_AL_IIR_ORDER_SEL_EQ_W(X) ((X) << ANC_AL_IIR_ORDER_SEL_EQ_POS)

//ANC_R_IIR_ORDER_SEL offsetaddress : 0x0D08
//ANC_R_IIR_ORDER_SEL RegResetValue : 0x0000000
#define ANC_AR_IIR_ORDER_SEL_SB_POS  (0U)
#define ANC_AR_IIR_ORDER_SEL_SB_MSK  (0x1fUL << ANC_AR_IIR_ORDER_SEL_SB_POS) /*!< ar_iir_order_sel_sb 20th order filter, the current configuration order = value 1*/
#define ANC_AR_IIR_ORDER_SEL_SB      ANC_AR_IIR_ORDER_SEL_SB_MSK
#define ANC_AR_IIR_ORDER_SEL_SB_W(X) ((X) << ANC_AR_IIR_ORDER_SEL_SB_POS)
#define ANC_AR_IIR_ORDER_SEL_FB_POS  (5U)
#define ANC_AR_IIR_ORDER_SEL_FB_MSK  (0x1fUL << ANC_AR_IIR_ORDER_SEL_FB_POS) /*!< ar_iir_order_sel_fb 20th order filter, the current configuration order = value 1*/
#define ANC_AR_IIR_ORDER_SEL_FB      ANC_AR_IIR_ORDER_SEL_FB_MSK
#define ANC_AR_IIR_ORDER_SEL_FB_W(X) ((X) << ANC_AR_IIR_ORDER_SEL_FB_POS)
#define ANC_AR_IIR_ORDER_SEL_WF_POS  (10U)
#define ANC_AR_IIR_ORDER_SEL_WF_MSK  (0x1fUL << ANC_AR_IIR_ORDER_SEL_WF_POS) /*!< ar_iir_order_sel_wf 20th order filter, the current configuration order = value 1*/
#define ANC_AR_IIR_ORDER_SEL_WF      ANC_AR_IIR_ORDER_SEL_WF_MSK
#define ANC_AR_IIR_ORDER_SEL_WF_W(X) ((X) << ANC_AR_IIR_ORDER_SEL_WF_POS)
#define ANC_AR_IIR_ORDER_SEL_TR_POS  (15U)
#define ANC_AR_IIR_ORDER_SEL_TR_MSK  (0x1fUL << ANC_AR_IIR_ORDER_SEL_TR_POS) /*!< ar_iir_order_sel_tr 10th order filter, the current configuration order = value 1*/
#define ANC_AR_IIR_ORDER_SEL_TR      ANC_AR_IIR_ORDER_SEL_TR_MSK
#define ANC_AR_IIR_ORDER_SEL_TR_W(X) ((X) << ANC_AR_IIR_ORDER_SEL_TR_POS)
#define ANC_AR_IIR_ORDER_SEL_EQ_POS  (20U)
#define ANC_AR_IIR_ORDER_SEL_EQ_MSK  (0x1fUL << ANC_AR_IIR_ORDER_SEL_EQ_POS) /*!< ar_iir_order_sel_eq 10th order filter, the current configuration order = value 1*/
#define ANC_AR_IIR_ORDER_SEL_EQ      ANC_AR_IIR_ORDER_SEL_EQ_MSK
#define ANC_AR_IIR_ORDER_SEL_EQ_W(X) ((X) << ANC_AR_IIR_ORDER_SEL_EQ_POS)

//ANC_LR_SYNC_START offsetaddress : 0x0DE0
//ANC_LR_SYNC_START RegResetValue : 0x0000000
#define ANC_ANC_LR_SYNC_START_POS  (0U)
#define ANC_ANC_LR_SYNC_START_MSK  (0x1UL << ANC_ANC_LR_SYNC_START_POS) /*!< 0:anc right-way enable comes from ar_enable;*/
#define ANC_ANC_LR_SYNC_START      ANC_ANC_LR_SYNC_START_MSK
#define ANC_ANC_LR_SYNC_START_W(X) ((X) << ANC_ANC_LR_SYNC_START_POS)

//ANC_L_MN_GC_REG0 offsetaddress : 0x0E00
//ANC_L_MN_GC_REG0 RegResetValue : 0x0000000
#define ANC_AL_MN_GC_ENABLE_POS       (0U)
#define ANC_AL_MN_GC_ENABLE_MSK       (0x1UL << ANC_AL_MN_GC_ENABLE_POS) /*!< al_mn_gc_enable*/
#define ANC_AL_MN_GC_ENABLE           ANC_AL_MN_GC_ENABLE_MSK
#define ANC_AL_MN_GC_ENABLE_W(X)      ((X) << ANC_AL_MN_GC_ENABLE_POS)
#define ANC_AL_MN_GC_BYPASS_POS       (1U)
#define ANC_AL_MN_GC_BYPASS_MSK       (0x1UL << ANC_AL_MN_GC_BYPASS_POS) /*!< al_mn_gc_bypass*/
#define ANC_AL_MN_GC_BYPASS           ANC_AL_MN_GC_BYPASS_MSK
#define ANC_AL_MN_GC_BYPASS_W(X)      ((X) << ANC_AL_MN_GC_BYPASS_POS)
#define ANC_AL_MN_GC_DELAY_POINT_POS  (2U)
#define ANC_AL_MN_GC_DELAY_POINT_MSK  (0x1ffUL << ANC_AL_MN_GC_DELAY_POINT_POS) /*!< al_mn_gc_delay_point*/
#define ANC_AL_MN_GC_DELAY_POINT      ANC_AL_MN_GC_DELAY_POINT_MSK
#define ANC_AL_MN_GC_DELAY_POINT_W(X) ((X) << ANC_AL_MN_GC_DELAY_POINT_POS)

//ANC_L_MN_GC_REG1 offsetaddress : 0x0E04
//ANC_L_MN_GC_REG1 RegResetValue : 0x0000000
#define ANC_AL_MN_GC_ENV_SMOOTH_FIX_POS       (0U)
#define ANC_AL_MN_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << ANC_AL_MN_GC_ENV_SMOOTH_FIX_POS) /*!< al_mn_gc_env_smooth_fix*/
#define ANC_AL_MN_GC_ENV_SMOOTH_FIX           ANC_AL_MN_GC_ENV_SMOOTH_FIX_MSK
#define ANC_AL_MN_GC_ENV_SMOOTH_FIX_W(X)      ((X) << ANC_AL_MN_GC_ENV_SMOOTH_FIX_POS)
#define ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< al_mn_gc_env_smooth_cmop_fix*/
#define ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX      ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << ANC_AL_MN_GC_ENV_SMOOTH_CMOP_FIX_POS)

//ANC_L_MN_GC_REG2 offsetaddress : 0x0E08
//ANC_L_MN_GC_REG2 RegResetValue : 0x0000000
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< al_mn_gc_out_gain_smooth_1_fix*/
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX           ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< al_mn_gc_out_gain_smooth_1_comp_fix*/
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//ANC_L_MN_GC_REG3 offsetaddress : 0x0E0C
//ANC_L_MN_GC_REG3 RegResetValue : 0x0000000
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< al_mn_gc_out_gain_smooth_2_fix*/
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX           ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< al_mn_gc_out_gain_smooth_2_comp_fix*/
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << ANC_AL_MN_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//ANC_L_SC_GC_REG0 offsetaddress : 0x0E10
//ANC_L_SC_GC_REG0 RegResetValue : 0x0000000
#define ANC_AL_SC_GC_ENABLE_POS       (0U)
#define ANC_AL_SC_GC_ENABLE_MSK       (0x1UL << ANC_AL_SC_GC_ENABLE_POS) /*!< al_sc_gc_enable*/
#define ANC_AL_SC_GC_ENABLE           ANC_AL_SC_GC_ENABLE_MSK
#define ANC_AL_SC_GC_ENABLE_W(X)      ((X) << ANC_AL_SC_GC_ENABLE_POS)
#define ANC_AL_SC_GC_BYPASS_POS       (1U)
#define ANC_AL_SC_GC_BYPASS_MSK       (0x1UL << ANC_AL_SC_GC_BYPASS_POS) /*!< al_sc_gc_bypass*/
#define ANC_AL_SC_GC_BYPASS           ANC_AL_SC_GC_BYPASS_MSK
#define ANC_AL_SC_GC_BYPASS_W(X)      ((X) << ANC_AL_SC_GC_BYPASS_POS)
#define ANC_AL_SC_GC_DELAY_POINT_POS  (2U)
#define ANC_AL_SC_GC_DELAY_POINT_MSK  (0x1ffUL << ANC_AL_SC_GC_DELAY_POINT_POS) /*!< al_sc_gc_delay_point*/
#define ANC_AL_SC_GC_DELAY_POINT      ANC_AL_SC_GC_DELAY_POINT_MSK
#define ANC_AL_SC_GC_DELAY_POINT_W(X) ((X) << ANC_AL_SC_GC_DELAY_POINT_POS)

//ANC_L_SC_GC_REG1 offsetaddress : 0x0E14
//ANC_L_SC_GC_REG1 RegResetValue : 0x0000000
#define ANC_AL_SC_GC_ENV_SMOOTH_FIX_POS       (0U)
#define ANC_AL_SC_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << ANC_AL_SC_GC_ENV_SMOOTH_FIX_POS) /*!< al_sc_gc_env_smooth_fix*/
#define ANC_AL_SC_GC_ENV_SMOOTH_FIX           ANC_AL_SC_GC_ENV_SMOOTH_FIX_MSK
#define ANC_AL_SC_GC_ENV_SMOOTH_FIX_W(X)      ((X) << ANC_AL_SC_GC_ENV_SMOOTH_FIX_POS)
#define ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< al_sc_gc_env_smooth_cmop_fix*/
#define ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX      ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << ANC_AL_SC_GC_ENV_SMOOTH_CMOP_FIX_POS)

//ANC_L_SC_GC_REG2 offsetaddress : 0x0E18
//ANC_L_SC_GC_REG2 RegResetValue : 0x0000000
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< al_sc_gc_out_gain_smooth_1_fix*/
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX           ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< al_sc_gc_out_gain_smooth_1_comp_fix*/
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//ANC_L_SC_GC_REG3 offsetaddress : 0x0E1C
//ANC_L_SC_GC_REG3 RegResetValue : 0x0000000
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< al_sc_gc_out_gain_smooth_2_fix*/
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX           ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< al_sc_gc_out_gain_smooth_2_comp_fix*/
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << ANC_AL_SC_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//ANC_L_EQ_GC_REG0 offsetaddress : 0x0E20
//ANC_L_EQ_GC_REG0 RegResetValue : 0x0000000
#define ANC_AL_EQ_GC_ENABLE_POS       (0U)
#define ANC_AL_EQ_GC_ENABLE_MSK       (0x1UL << ANC_AL_EQ_GC_ENABLE_POS) /*!< al_eq_gc_enable*/
#define ANC_AL_EQ_GC_ENABLE           ANC_AL_EQ_GC_ENABLE_MSK
#define ANC_AL_EQ_GC_ENABLE_W(X)      ((X) << ANC_AL_EQ_GC_ENABLE_POS)
#define ANC_AL_EQ_GC_BYPASS_POS       (1U)
#define ANC_AL_EQ_GC_BYPASS_MSK       (0x1UL << ANC_AL_EQ_GC_BYPASS_POS) /*!< al_eq_gc_bypass*/
#define ANC_AL_EQ_GC_BYPASS           ANC_AL_EQ_GC_BYPASS_MSK
#define ANC_AL_EQ_GC_BYPASS_W(X)      ((X) << ANC_AL_EQ_GC_BYPASS_POS)
#define ANC_AL_EQ_GC_DELAY_POINT_POS  (2U)
#define ANC_AL_EQ_GC_DELAY_POINT_MSK  (0x1ffUL << ANC_AL_EQ_GC_DELAY_POINT_POS) /*!< al_eq_gc_delay_point*/
#define ANC_AL_EQ_GC_DELAY_POINT      ANC_AL_EQ_GC_DELAY_POINT_MSK
#define ANC_AL_EQ_GC_DELAY_POINT_W(X) ((X) << ANC_AL_EQ_GC_DELAY_POINT_POS)

//ANC_L_EQ_GC_REG1 offsetaddress : 0x0E24
//ANC_L_EQ_GC_REG1 RegResetValue : 0x0000000
#define ANC_AL_EQ_GC_ENV_SMOOTH_FIX_POS       (0U)
#define ANC_AL_EQ_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << ANC_AL_EQ_GC_ENV_SMOOTH_FIX_POS) /*!< al_eq_gc_env_smooth_fix*/
#define ANC_AL_EQ_GC_ENV_SMOOTH_FIX           ANC_AL_EQ_GC_ENV_SMOOTH_FIX_MSK
#define ANC_AL_EQ_GC_ENV_SMOOTH_FIX_W(X)      ((X) << ANC_AL_EQ_GC_ENV_SMOOTH_FIX_POS)
#define ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< al_eq_gc_env_smooth_cmop_fix*/
#define ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX      ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << ANC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS)

//ANC_L_EQ_GC_REG2 offsetaddress : 0x0E28
//ANC_L_EQ_GC_REG2 RegResetValue : 0x0000000
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< al_eq_gc_out_gain_smooth_1_fix*/
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX           ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< al_eq_gc_out_gain_smooth_1_comp_fix*/
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//ANC_L_EQ_GC_REG3 offsetaddress : 0x0E2C
//ANC_L_EQ_GC_REG3 RegResetValue : 0x0000000
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< al_eq_gc_out_gain_smooth_2_fix*/
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX           ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< al_eq_gc_out_gain_smooth_2_comp_fix*/
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << ANC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//ANC_R_TR_GC_REG0 offsetaddress : 0x0E30
//ANC_R_TR_GC_REG0 RegResetValue : 0x0000000
#define ANC_AR_TR_GC_ENABLE_POS       (0U)
#define ANC_AR_TR_GC_ENABLE_MSK       (0x1UL << ANC_AR_TR_GC_ENABLE_POS) /*!< ar_tr_gc_enable*/
#define ANC_AR_TR_GC_ENABLE           ANC_AR_TR_GC_ENABLE_MSK
#define ANC_AR_TR_GC_ENABLE_W(X)      ((X) << ANC_AR_TR_GC_ENABLE_POS)
#define ANC_AR_TR_GC_BYPASS_POS       (1U)
#define ANC_AR_TR_GC_BYPASS_MSK       (0x1UL << ANC_AR_TR_GC_BYPASS_POS) /*!< ar_tr_gc_bypass*/
#define ANC_AR_TR_GC_BYPASS           ANC_AR_TR_GC_BYPASS_MSK
#define ANC_AR_TR_GC_BYPASS_W(X)      ((X) << ANC_AR_TR_GC_BYPASS_POS)
#define ANC_AR_TR_GC_DELAY_POINT_POS  (2U)
#define ANC_AR_TR_GC_DELAY_POINT_MSK  (0x1ffUL << ANC_AR_TR_GC_DELAY_POINT_POS) /*!< ar_tr_gc_delay_point*/
#define ANC_AR_TR_GC_DELAY_POINT      ANC_AR_TR_GC_DELAY_POINT_MSK
#define ANC_AR_TR_GC_DELAY_POINT_W(X) ((X) << ANC_AR_TR_GC_DELAY_POINT_POS)

//ANC_R_TR_GC_REG1 offsetaddress : 0x0E34
//ANC_R_TR_GC_REG1 RegResetValue : 0x0000000
#define ANC_AR_TR_GC_ENV_SMOOTH_FIX_POS       (0U)
#define ANC_AR_TR_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << ANC_AR_TR_GC_ENV_SMOOTH_FIX_POS) /*!< ar_tr_gc_env_smooth_fix*/
#define ANC_AR_TR_GC_ENV_SMOOTH_FIX           ANC_AR_TR_GC_ENV_SMOOTH_FIX_MSK
#define ANC_AR_TR_GC_ENV_SMOOTH_FIX_W(X)      ((X) << ANC_AR_TR_GC_ENV_SMOOTH_FIX_POS)
#define ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< ar_tr_gc_env_smooth_cmop_fix*/
#define ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX      ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << ANC_AR_TR_GC_ENV_SMOOTH_CMOP_FIX_POS)

//ANC_R_TR_GC_REG2 offsetaddress : 0x0E38
//ANC_R_TR_GC_REG2 RegResetValue : 0x0000000
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< al_tr_gc_out_gain_smooth_1_fix*/
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX           ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< al_tr_gc_out_gain_smooth_1_comp_fix*/
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//ANC_R_TR_GC_REG3 offsetaddress : 0x0E3C
//ANC_R_TR_GC_REG3 RegResetValue : 0x0000000
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< ar_tr_gc_out_gain_smooth_2_fix*/
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX           ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< ar_tr_gc_out_gain_smooth_2_comp_fix*/
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << ANC_AR_TR_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//ANC_R_EQ_GC_REG0 offsetaddress : 0x0E40
//ANC_R_EQ_GC_REG0 RegResetValue : 0x0000000
#define ANC_AR_EQ_GC_ENABLE_POS       (0U)
#define ANC_AR_EQ_GC_ENABLE_MSK       (0x1UL << ANC_AR_EQ_GC_ENABLE_POS) /*!< ar_eq_gc_enable*/
#define ANC_AR_EQ_GC_ENABLE           ANC_AR_EQ_GC_ENABLE_MSK
#define ANC_AR_EQ_GC_ENABLE_W(X)      ((X) << ANC_AR_EQ_GC_ENABLE_POS)
#define ANC_AR_EQ_GC_BYPASS_POS       (1U)
#define ANC_AR_EQ_GC_BYPASS_MSK       (0x1UL << ANC_AR_EQ_GC_BYPASS_POS) /*!< ar_eq_gc_bypass*/
#define ANC_AR_EQ_GC_BYPASS           ANC_AR_EQ_GC_BYPASS_MSK
#define ANC_AR_EQ_GC_BYPASS_W(X)      ((X) << ANC_AR_EQ_GC_BYPASS_POS)
#define ANC_AR_EQ_GC_DELAY_POINT_POS  (2U)
#define ANC_AR_EQ_GC_DELAY_POINT_MSK  (0x1ffUL << ANC_AR_EQ_GC_DELAY_POINT_POS) /*!< ar_eq_gc_delay_point delayed audio point, corresponding to delay_time in matlab algorithm*/
#define ANC_AR_EQ_GC_DELAY_POINT      ANC_AR_EQ_GC_DELAY_POINT_MSK
#define ANC_AR_EQ_GC_DELAY_POINT_W(X) ((X) << ANC_AR_EQ_GC_DELAY_POINT_POS)

//ANC_R_EQ_GC_REG1 offsetaddress : 0x0E44
//ANC_R_EQ_GC_REG1 RegResetValue : 0x0000000
#define ANC_AR_EQ_GC_ENV_SMOOTH_FIX_POS       (0U)
#define ANC_AR_EQ_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << ANC_AR_EQ_GC_ENV_SMOOTH_FIX_POS) /*!< ar_eq_gc_env_smooth_fix corresponds to env_smooth_fix in the matlab algorithm, and fix( env_smooth * smooth_bit_scale);*/
#define ANC_AR_EQ_GC_ENV_SMOOTH_FIX           ANC_AR_EQ_GC_ENV_SMOOTH_FIX_MSK
#define ANC_AR_EQ_GC_ENV_SMOOTH_FIX_W(X)      ((X) << ANC_AR_EQ_GC_ENV_SMOOTH_FIX_POS)
#define ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< ar_eq_gc_env_smooth_cmop_fix corresponding to env_smooth_cmop_fix = smooth_bit_scale - env_smooth_fix*/
#define ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX      ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << ANC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS)

//ANC_R_EQ_GC_REG2 offsetaddress : 0x0E48
//ANC_R_EQ_GC_REG2 RegResetValue : 0x0000000
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< al_eq_gc_out_gain_smooth_1_fix corresponding to out_gain_smooth_1_fix in the matlab algorithm = fix( env_smooth * smooth_bit_scale )*/
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX           ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< al_eq_gc_out_gain_smooth_1_comp_fix corresponding to out_gain_smooth_1_comp_fix = smooth_bit_scale - out_gain_smooth_1_fix*/
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//ANC_R_EQ_GC_REG3 offsetaddress : 0x0E4C
//ANC_R_EQ_GC_REG3 RegResetValue : 0x0000000
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< ar_eq_gc_out_gain_smooth_2_fix corresponding to out_gain_smooth_2_fix in the matlab algorithm = fix( out_gain_smooth_2 * smooth_bit_scale )*/
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX           ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< ar_eq_gc_out_gain_smooth_2_comp_fix corresponding to out_gain_smooth_2_comp_fix = smooth_bit_scale - out_gain_smooth_2_fix*/
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << ANC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//ANC_REGIF_INTERRUPT_INT_RAW offsetaddress : 0xF000
//ANC_REGIF_INTERRUPT_INT_RAW RegResetValue : 0x0000000
#define ANC_AL_RSSI4_VALID_INTR_RAW_POS  (0U)
#define ANC_AL_RSSI4_VALID_INTR_RAW_MSK  (0x1UL << ANC_AL_RSSI4_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_RSSI4_VALID_INTR_RAW      ANC_AL_RSSI4_VALID_INTR_RAW_MSK
#define ANC_AL_RSSI4_VALID_INTR_RAW_W(X) ((X) << ANC_AL_RSSI4_VALID_INTR_RAW_POS)
#define ANC_AL_RSSI3_VALID_INTR_RAW_POS  (1U)
#define ANC_AL_RSSI3_VALID_INTR_RAW_MSK  (0x1UL << ANC_AL_RSSI3_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_RSSI3_VALID_INTR_RAW      ANC_AL_RSSI3_VALID_INTR_RAW_MSK
#define ANC_AL_RSSI3_VALID_INTR_RAW_W(X) ((X) << ANC_AL_RSSI3_VALID_INTR_RAW_POS)
#define ANC_AL_RSSI2_VALID_INTR_RAW_POS  (2U)
#define ANC_AL_RSSI2_VALID_INTR_RAW_MSK  (0x1UL << ANC_AL_RSSI2_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_RSSI2_VALID_INTR_RAW      ANC_AL_RSSI2_VALID_INTR_RAW_MSK
#define ANC_AL_RSSI2_VALID_INTR_RAW_W(X) ((X) << ANC_AL_RSSI2_VALID_INTR_RAW_POS)
#define ANC_AL_RSSI1_VALID_INTR_RAW_POS  (3U)
#define ANC_AL_RSSI1_VALID_INTR_RAW_MSK  (0x1UL << ANC_AL_RSSI1_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_RSSI1_VALID_INTR_RAW      ANC_AL_RSSI1_VALID_INTR_RAW_MSK
#define ANC_AL_RSSI1_VALID_INTR_RAW_W(X) ((X) << ANC_AL_RSSI1_VALID_INTR_RAW_POS)
#define ANC_AL_RSSI0_VALID_INTR_RAW_POS  (4U)
#define ANC_AL_RSSI0_VALID_INTR_RAW_MSK  (0x1UL << ANC_AL_RSSI0_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_RSSI0_VALID_INTR_RAW      ANC_AL_RSSI0_VALID_INTR_RAW_MSK
#define ANC_AL_RSSI0_VALID_INTR_RAW_W(X) ((X) << ANC_AL_RSSI0_VALID_INTR_RAW_POS)
#define ANC_AR_RSSI4_VALID_INTR_RAW_POS  (5U)
#define ANC_AR_RSSI4_VALID_INTR_RAW_MSK  (0x1UL << ANC_AR_RSSI4_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_RSSI4_VALID_INTR_RAW      ANC_AR_RSSI4_VALID_INTR_RAW_MSK
#define ANC_AR_RSSI4_VALID_INTR_RAW_W(X) ((X) << ANC_AR_RSSI4_VALID_INTR_RAW_POS)
#define ANC_AR_RSSI3_VALID_INTR_RAW_POS  (6U)
#define ANC_AR_RSSI3_VALID_INTR_RAW_MSK  (0x1UL << ANC_AR_RSSI3_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_RSSI3_VALID_INTR_RAW      ANC_AR_RSSI3_VALID_INTR_RAW_MSK
#define ANC_AR_RSSI3_VALID_INTR_RAW_W(X) ((X) << ANC_AR_RSSI3_VALID_INTR_RAW_POS)
#define ANC_AR_RSSI2_VALID_INTR_RAW_POS  (7U)
#define ANC_AR_RSSI2_VALID_INTR_RAW_MSK  (0x1UL << ANC_AR_RSSI2_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_RSSI2_VALID_INTR_RAW      ANC_AR_RSSI2_VALID_INTR_RAW_MSK
#define ANC_AR_RSSI2_VALID_INTR_RAW_W(X) ((X) << ANC_AR_RSSI2_VALID_INTR_RAW_POS)
#define ANC_AR_RSSI1_VALID_INTR_RAW_POS  (8U)
#define ANC_AR_RSSI1_VALID_INTR_RAW_MSK  (0x1UL << ANC_AR_RSSI1_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_RSSI1_VALID_INTR_RAW      ANC_AR_RSSI1_VALID_INTR_RAW_MSK
#define ANC_AR_RSSI1_VALID_INTR_RAW_W(X) ((X) << ANC_AR_RSSI1_VALID_INTR_RAW_POS)
#define ANC_AR_RSSI0_VALID_INTR_RAW_POS  (9U)
#define ANC_AR_RSSI0_VALID_INTR_RAW_MSK  (0x1UL << ANC_AR_RSSI0_VALID_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_RSSI0_VALID_INTR_RAW      ANC_AR_RSSI0_VALID_INTR_RAW_MSK
#define ANC_AR_RSSI0_VALID_INTR_RAW_W(X) ((X) << ANC_AR_RSSI0_VALID_INTR_RAW_POS)

//ANC_REGIF_INTERRUPT_INT_FORCE offsetaddress : 0xF004
//ANC_REGIF_INTERRUPT_INT_FORCE RegResetValue : 0x0000000
#define ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (0U)
#define ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (1U)
#define ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (2U)
#define ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (3U)
#define ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (4U)
#define ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (5U)
#define ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_RSSI4_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (6U)
#define ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_RSSI3_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (7U)
#define ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_RSSI2_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (8U)
#define ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_RSSI1_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS  (9U)
#define ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE      ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_RSSI0_VALID_INTR_RAW_ANC_REGIF_INTERRUPT_INT_FORCE_POS)

//ANC_REGIF_INTERRUPT_INT_MASK offsetaddress : 0xF008
//ANC_REGIF_INTERRUPT_INT_MASK RegResetValue : 0x0000000
#define ANC_AL_RSSI4_VALID_INTR_MASK_POS  (0U)
#define ANC_AL_RSSI4_VALID_INTR_MASK_MSK  (0x1UL << ANC_AL_RSSI4_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_RSSI4_VALID_INTR_MASK      ANC_AL_RSSI4_VALID_INTR_MASK_MSK
#define ANC_AL_RSSI4_VALID_INTR_MASK_W(X) ((X) << ANC_AL_RSSI4_VALID_INTR_MASK_POS)
#define ANC_AL_RSSI3_VALID_INTR_MASK_POS  (1U)
#define ANC_AL_RSSI3_VALID_INTR_MASK_MSK  (0x1UL << ANC_AL_RSSI3_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_RSSI3_VALID_INTR_MASK      ANC_AL_RSSI3_VALID_INTR_MASK_MSK
#define ANC_AL_RSSI3_VALID_INTR_MASK_W(X) ((X) << ANC_AL_RSSI3_VALID_INTR_MASK_POS)
#define ANC_AL_RSSI2_VALID_INTR_MASK_POS  (2U)
#define ANC_AL_RSSI2_VALID_INTR_MASK_MSK  (0x1UL << ANC_AL_RSSI2_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_RSSI2_VALID_INTR_MASK      ANC_AL_RSSI2_VALID_INTR_MASK_MSK
#define ANC_AL_RSSI2_VALID_INTR_MASK_W(X) ((X) << ANC_AL_RSSI2_VALID_INTR_MASK_POS)
#define ANC_AL_RSSI1_VALID_INTR_MASK_POS  (3U)
#define ANC_AL_RSSI1_VALID_INTR_MASK_MSK  (0x1UL << ANC_AL_RSSI1_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_RSSI1_VALID_INTR_MASK      ANC_AL_RSSI1_VALID_INTR_MASK_MSK
#define ANC_AL_RSSI1_VALID_INTR_MASK_W(X) ((X) << ANC_AL_RSSI1_VALID_INTR_MASK_POS)
#define ANC_AL_RSSI0_VALID_INTR_MASK_POS  (4U)
#define ANC_AL_RSSI0_VALID_INTR_MASK_MSK  (0x1UL << ANC_AL_RSSI0_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_RSSI0_VALID_INTR_MASK      ANC_AL_RSSI0_VALID_INTR_MASK_MSK
#define ANC_AL_RSSI0_VALID_INTR_MASK_W(X) ((X) << ANC_AL_RSSI0_VALID_INTR_MASK_POS)
#define ANC_AR_RSSI4_VALID_INTR_MASK_POS  (5U)
#define ANC_AR_RSSI4_VALID_INTR_MASK_MSK  (0x1UL << ANC_AR_RSSI4_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_RSSI4_VALID_INTR_MASK      ANC_AR_RSSI4_VALID_INTR_MASK_MSK
#define ANC_AR_RSSI4_VALID_INTR_MASK_W(X) ((X) << ANC_AR_RSSI4_VALID_INTR_MASK_POS)
#define ANC_AR_RSSI3_VALID_INTR_MASK_POS  (6U)
#define ANC_AR_RSSI3_VALID_INTR_MASK_MSK  (0x1UL << ANC_AR_RSSI3_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_RSSI3_VALID_INTR_MASK      ANC_AR_RSSI3_VALID_INTR_MASK_MSK
#define ANC_AR_RSSI3_VALID_INTR_MASK_W(X) ((X) << ANC_AR_RSSI3_VALID_INTR_MASK_POS)
#define ANC_AR_RSSI2_VALID_INTR_MASK_POS  (7U)
#define ANC_AR_RSSI2_VALID_INTR_MASK_MSK  (0x1UL << ANC_AR_RSSI2_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_RSSI2_VALID_INTR_MASK      ANC_AR_RSSI2_VALID_INTR_MASK_MSK
#define ANC_AR_RSSI2_VALID_INTR_MASK_W(X) ((X) << ANC_AR_RSSI2_VALID_INTR_MASK_POS)
#define ANC_AR_RSSI1_VALID_INTR_MASK_POS  (8U)
#define ANC_AR_RSSI1_VALID_INTR_MASK_MSK  (0x1UL << ANC_AR_RSSI1_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_RSSI1_VALID_INTR_MASK      ANC_AR_RSSI1_VALID_INTR_MASK_MSK
#define ANC_AR_RSSI1_VALID_INTR_MASK_W(X) ((X) << ANC_AR_RSSI1_VALID_INTR_MASK_POS)
#define ANC_AR_RSSI0_VALID_INTR_MASK_POS  (9U)
#define ANC_AR_RSSI0_VALID_INTR_MASK_MSK  (0x1UL << ANC_AR_RSSI0_VALID_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_RSSI0_VALID_INTR_MASK      ANC_AR_RSSI0_VALID_INTR_MASK_MSK
#define ANC_AR_RSSI0_VALID_INTR_MASK_W(X) ((X) << ANC_AR_RSSI0_VALID_INTR_MASK_POS)

//ANC_REGIF_INTERRUPT_INT_STATUS offsetaddress : 0xF00C
//ANC_REGIF_INTERRUPT_INT_STATUS RegResetValue : 0x0000000
#define ANC_AL_RSSI4_VALID_INTR_STATUS_POS  (0U)
#define ANC_AL_RSSI4_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AL_RSSI4_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_RSSI4_VALID_INTR_STATUS      ANC_AL_RSSI4_VALID_INTR_STATUS_MSK
#define ANC_AL_RSSI4_VALID_INTR_STATUS_W(X) ((X) << ANC_AL_RSSI4_VALID_INTR_STATUS_POS)
#define ANC_AL_RSSI3_VALID_INTR_STATUS_POS  (1U)
#define ANC_AL_RSSI3_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AL_RSSI3_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_RSSI3_VALID_INTR_STATUS      ANC_AL_RSSI3_VALID_INTR_STATUS_MSK
#define ANC_AL_RSSI3_VALID_INTR_STATUS_W(X) ((X) << ANC_AL_RSSI3_VALID_INTR_STATUS_POS)
#define ANC_AL_RSSI2_VALID_INTR_STATUS_POS  (2U)
#define ANC_AL_RSSI2_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AL_RSSI2_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_RSSI2_VALID_INTR_STATUS      ANC_AL_RSSI2_VALID_INTR_STATUS_MSK
#define ANC_AL_RSSI2_VALID_INTR_STATUS_W(X) ((X) << ANC_AL_RSSI2_VALID_INTR_STATUS_POS)
#define ANC_AL_RSSI1_VALID_INTR_STATUS_POS  (3U)
#define ANC_AL_RSSI1_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AL_RSSI1_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_RSSI1_VALID_INTR_STATUS      ANC_AL_RSSI1_VALID_INTR_STATUS_MSK
#define ANC_AL_RSSI1_VALID_INTR_STATUS_W(X) ((X) << ANC_AL_RSSI1_VALID_INTR_STATUS_POS)
#define ANC_AL_RSSI0_VALID_INTR_STATUS_POS  (4U)
#define ANC_AL_RSSI0_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AL_RSSI0_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_RSSI0_VALID_INTR_STATUS      ANC_AL_RSSI0_VALID_INTR_STATUS_MSK
#define ANC_AL_RSSI0_VALID_INTR_STATUS_W(X) ((X) << ANC_AL_RSSI0_VALID_INTR_STATUS_POS)
#define ANC_AR_RSSI4_VALID_INTR_STATUS_POS  (5U)
#define ANC_AR_RSSI4_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AR_RSSI4_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_RSSI4_VALID_INTR_STATUS      ANC_AR_RSSI4_VALID_INTR_STATUS_MSK
#define ANC_AR_RSSI4_VALID_INTR_STATUS_W(X) ((X) << ANC_AR_RSSI4_VALID_INTR_STATUS_POS)
#define ANC_AR_RSSI3_VALID_INTR_STATUS_POS  (6U)
#define ANC_AR_RSSI3_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AR_RSSI3_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_RSSI3_VALID_INTR_STATUS      ANC_AR_RSSI3_VALID_INTR_STATUS_MSK
#define ANC_AR_RSSI3_VALID_INTR_STATUS_W(X) ((X) << ANC_AR_RSSI3_VALID_INTR_STATUS_POS)
#define ANC_AR_RSSI2_VALID_INTR_STATUS_POS  (7U)
#define ANC_AR_RSSI2_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AR_RSSI2_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_RSSI2_VALID_INTR_STATUS      ANC_AR_RSSI2_VALID_INTR_STATUS_MSK
#define ANC_AR_RSSI2_VALID_INTR_STATUS_W(X) ((X) << ANC_AR_RSSI2_VALID_INTR_STATUS_POS)
#define ANC_AR_RSSI1_VALID_INTR_STATUS_POS  (8U)
#define ANC_AR_RSSI1_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AR_RSSI1_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_RSSI1_VALID_INTR_STATUS      ANC_AR_RSSI1_VALID_INTR_STATUS_MSK
#define ANC_AR_RSSI1_VALID_INTR_STATUS_W(X) ((X) << ANC_AR_RSSI1_VALID_INTR_STATUS_POS)
#define ANC_AR_RSSI0_VALID_INTR_STATUS_POS  (9U)
#define ANC_AR_RSSI0_VALID_INTR_STATUS_MSK  (0x1UL << ANC_AR_RSSI0_VALID_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_RSSI0_VALID_INTR_STATUS      ANC_AR_RSSI0_VALID_INTR_STATUS_MSK
#define ANC_AR_RSSI0_VALID_INTR_STATUS_W(X) ((X) << ANC_AR_RSSI0_VALID_INTR_STATUS_POS)

//S0_B0 offsetaddress : 0x10000
//S0_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S0_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S0_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S0_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S0_B0_REG      ANC_IIR_COEFF_S0_B0_REG_MSK
#define ANC_IIR_COEFF_S0_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S0_B0_REG_POS)

//S0_B1 offsetaddress : 0x10004
//S0_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S0_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S0_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S0_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S0_B1_REG      ANC_IIR_COEFF_S0_B1_REG_MSK
#define ANC_IIR_COEFF_S0_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S0_B1_REG_POS)

//S0_B2 offsetaddress : 0x10008
//S0_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S0_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S0_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S0_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S0_B2_REG      ANC_IIR_COEFF_S0_B2_REG_MSK
#define ANC_IIR_COEFF_S0_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S0_B2_REG_POS)

//S0_A1 offsetaddress : 0x1000C
//S0_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S0_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S0_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S0_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S0_A1_REG      ANC_IIR_COEFF_S0_A1_REG_MSK
#define ANC_IIR_COEFF_S0_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S0_A1_REG_POS)

//S0_A2 offsetaddress : 0x10010
//S0_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S0_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S0_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S0_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S0_A2_REG      ANC_IIR_COEFF_S0_A2_REG_MSK
#define ANC_IIR_COEFF_S0_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S0_A2_REG_POS)

//S1_B0 offsetaddress : 0x10014
//S1_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S1_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S1_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S1_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S1_B0_REG      ANC_IIR_COEFF_S1_B0_REG_MSK
#define ANC_IIR_COEFF_S1_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S1_B0_REG_POS)

//S1_B1 offsetaddress : 0x10018
//S1_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S1_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S1_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S1_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S1_B1_REG      ANC_IIR_COEFF_S1_B1_REG_MSK
#define ANC_IIR_COEFF_S1_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S1_B1_REG_POS)

//S1_B2 offsetaddress : 0x1001C
//S1_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S1_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S1_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S1_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S1_B2_REG      ANC_IIR_COEFF_S1_B2_REG_MSK
#define ANC_IIR_COEFF_S1_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S1_B2_REG_POS)

//S1_A1 offsetaddress : 0x10020
//S1_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S1_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S1_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S1_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S1_A1_REG      ANC_IIR_COEFF_S1_A1_REG_MSK
#define ANC_IIR_COEFF_S1_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S1_A1_REG_POS)

//S1_A2 offsetaddress : 0x10024
//S1_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S1_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S1_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S1_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S1_A2_REG      ANC_IIR_COEFF_S1_A2_REG_MSK
#define ANC_IIR_COEFF_S1_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S1_A2_REG_POS)

//S2_B0 offsetaddress : 0x10028
//S2_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S2_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S2_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S2_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S2_B0_REG      ANC_IIR_COEFF_S2_B0_REG_MSK
#define ANC_IIR_COEFF_S2_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S2_B0_REG_POS)

//S2_B1 offsetaddress : 0x1002C
//S2_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S2_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S2_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S2_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S2_B1_REG      ANC_IIR_COEFF_S2_B1_REG_MSK
#define ANC_IIR_COEFF_S2_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S2_B1_REG_POS)

//S2_B2 offsetaddress : 0x10030
//S2_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S2_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S2_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S2_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S2_B2_REG      ANC_IIR_COEFF_S2_B2_REG_MSK
#define ANC_IIR_COEFF_S2_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S2_B2_REG_POS)

//S2_A1 offsetaddress : 0x10034
//S2_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S2_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S2_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S2_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S2_A1_REG      ANC_IIR_COEFF_S2_A1_REG_MSK
#define ANC_IIR_COEFF_S2_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S2_A1_REG_POS)

//S2_A2 offsetaddress : 0x10038
//S2_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S2_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S2_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S2_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S2_A2_REG      ANC_IIR_COEFF_S2_A2_REG_MSK
#define ANC_IIR_COEFF_S2_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S2_A2_REG_POS)

//S3_B0 offsetaddress : 0x1003C
//S3_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S3_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S3_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S3_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S3_B0_REG      ANC_IIR_COEFF_S3_B0_REG_MSK
#define ANC_IIR_COEFF_S3_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S3_B0_REG_POS)

//S3_B1 offsetaddress : 0x10040
//S3_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S3_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S3_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S3_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S3_B1_REG      ANC_IIR_COEFF_S3_B1_REG_MSK
#define ANC_IIR_COEFF_S3_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S3_B1_REG_POS)

//S3_B2 offsetaddress : 0x10044
//S3_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S3_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S3_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S3_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S3_B2_REG      ANC_IIR_COEFF_S3_B2_REG_MSK
#define ANC_IIR_COEFF_S3_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S3_B2_REG_POS)

//S3_A1 offsetaddress : 0x10048
//S3_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S3_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S3_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S3_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S3_A1_REG      ANC_IIR_COEFF_S3_A1_REG_MSK
#define ANC_IIR_COEFF_S3_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S3_A1_REG_POS)

//S3_A2 offsetaddress : 0x1004C
//S3_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S3_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S3_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S3_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S3_A2_REG      ANC_IIR_COEFF_S3_A2_REG_MSK
#define ANC_IIR_COEFF_S3_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S3_A2_REG_POS)

//S4_B0 offsetaddress : 0x10050
//S4_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S4_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S4_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S4_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S4_B0_REG      ANC_IIR_COEFF_S4_B0_REG_MSK
#define ANC_IIR_COEFF_S4_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S4_B0_REG_POS)

//S4_B1 offsetaddress : 0x10054
//S4_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S4_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S4_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S4_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S4_B1_REG      ANC_IIR_COEFF_S4_B1_REG_MSK
#define ANC_IIR_COEFF_S4_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S4_B1_REG_POS)

//S4_B2 offsetaddress : 0x10058
//S4_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S4_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S4_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S4_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S4_B2_REG      ANC_IIR_COEFF_S4_B2_REG_MSK
#define ANC_IIR_COEFF_S4_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S4_B2_REG_POS)

//S4_A1 offsetaddress : 0x1005C
//S4_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S4_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S4_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S4_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S4_A1_REG      ANC_IIR_COEFF_S4_A1_REG_MSK
#define ANC_IIR_COEFF_S4_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S4_A1_REG_POS)

//S4_A2 offsetaddress : 0x10060
//S4_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S4_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S4_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S4_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S4_A2_REG      ANC_IIR_COEFF_S4_A2_REG_MSK
#define ANC_IIR_COEFF_S4_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S4_A2_REG_POS)

//S5_B0 offsetaddress : 0x10064
//S5_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S5_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S5_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S5_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S5_B0_REG      ANC_IIR_COEFF_S5_B0_REG_MSK
#define ANC_IIR_COEFF_S5_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S5_B0_REG_POS)

//S5_B1 offsetaddress : 0x10068
//S5_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S5_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S5_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S5_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S5_B1_REG      ANC_IIR_COEFF_S5_B1_REG_MSK
#define ANC_IIR_COEFF_S5_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S5_B1_REG_POS)

//S5_B2 offsetaddress : 0x1006C
//S5_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S5_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S5_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S5_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S5_B2_REG      ANC_IIR_COEFF_S5_B2_REG_MSK
#define ANC_IIR_COEFF_S5_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S5_B2_REG_POS)

//S5_A1 offsetaddress : 0x10070
//S5_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S5_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S5_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S5_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S5_A1_REG      ANC_IIR_COEFF_S5_A1_REG_MSK
#define ANC_IIR_COEFF_S5_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S5_A1_REG_POS)

//S5_A2 offsetaddress : 0x10074
//S5_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S5_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S5_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S5_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S5_A2_REG      ANC_IIR_COEFF_S5_A2_REG_MSK
#define ANC_IIR_COEFF_S5_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S5_A2_REG_POS)

//S6_B0 offsetaddress : 0x10078
//S6_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S6_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S6_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S6_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S6_B0_REG      ANC_IIR_COEFF_S6_B0_REG_MSK
#define ANC_IIR_COEFF_S6_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S6_B0_REG_POS)

//S6_B1 offsetaddress : 0x1007C
//S6_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S6_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S6_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S6_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S6_B1_REG      ANC_IIR_COEFF_S6_B1_REG_MSK
#define ANC_IIR_COEFF_S6_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S6_B1_REG_POS)

//S6_B2 offsetaddress : 0x10080
//S6_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S6_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S6_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S6_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S6_B2_REG      ANC_IIR_COEFF_S6_B2_REG_MSK
#define ANC_IIR_COEFF_S6_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S6_B2_REG_POS)

//S6_A1 offsetaddress : 0x10084
//S6_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S6_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S6_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S6_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S6_A1_REG      ANC_IIR_COEFF_S6_A1_REG_MSK
#define ANC_IIR_COEFF_S6_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S6_A1_REG_POS)

//S6_A2 offsetaddress : 0x10088
//S6_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S6_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S6_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S6_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S6_A2_REG      ANC_IIR_COEFF_S6_A2_REG_MSK
#define ANC_IIR_COEFF_S6_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S6_A2_REG_POS)

//S7_B0 offsetaddress : 0x1008C
//S7_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S7_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S7_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S7_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S7_B0_REG      ANC_IIR_COEFF_S7_B0_REG_MSK
#define ANC_IIR_COEFF_S7_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S7_B0_REG_POS)

//S7_B1 offsetaddress : 0x10090
//S7_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S7_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S7_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S7_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S7_B1_REG      ANC_IIR_COEFF_S7_B1_REG_MSK
#define ANC_IIR_COEFF_S7_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S7_B1_REG_POS)

//S7_B2 offsetaddress : 0x10094
//S7_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S7_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S7_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S7_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S7_B2_REG      ANC_IIR_COEFF_S7_B2_REG_MSK
#define ANC_IIR_COEFF_S7_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S7_B2_REG_POS)

//S7_A1 offsetaddress : 0x10098
//S7_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S7_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S7_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S7_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S7_A1_REG      ANC_IIR_COEFF_S7_A1_REG_MSK
#define ANC_IIR_COEFF_S7_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S7_A1_REG_POS)

//S7_A2 offsetaddress : 0x1009C
//S7_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S7_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S7_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S7_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S7_A2_REG      ANC_IIR_COEFF_S7_A2_REG_MSK
#define ANC_IIR_COEFF_S7_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S7_A2_REG_POS)

//S8_B0 offsetaddress : 0x100A0
//S8_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S8_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S8_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S8_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S8_B0_REG      ANC_IIR_COEFF_S8_B0_REG_MSK
#define ANC_IIR_COEFF_S8_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S8_B0_REG_POS)

//S8_B1 offsetaddress : 0x100A4
//S8_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S8_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S8_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S8_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S8_B1_REG      ANC_IIR_COEFF_S8_B1_REG_MSK
#define ANC_IIR_COEFF_S8_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S8_B1_REG_POS)

//S8_B2 offsetaddress : 0x100A8
//S8_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S8_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S8_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S8_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S8_B2_REG      ANC_IIR_COEFF_S8_B2_REG_MSK
#define ANC_IIR_COEFF_S8_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S8_B2_REG_POS)

//S8_A1 offsetaddress : 0x100AC
//S8_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S8_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S8_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S8_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S8_A1_REG      ANC_IIR_COEFF_S8_A1_REG_MSK
#define ANC_IIR_COEFF_S8_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S8_A1_REG_POS)

//S8_A2 offsetaddress : 0x100B0
//S8_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S8_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S8_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S8_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S8_A2_REG      ANC_IIR_COEFF_S8_A2_REG_MSK
#define ANC_IIR_COEFF_S8_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S8_A2_REG_POS)

//S9_B0 offsetaddress : 0x100B4
//S9_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S9_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S9_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S9_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S9_B0_REG      ANC_IIR_COEFF_S9_B0_REG_MSK
#define ANC_IIR_COEFF_S9_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S9_B0_REG_POS)

//S9_B1 offsetaddress : 0x100B8
//S9_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S9_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S9_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S9_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S9_B1_REG      ANC_IIR_COEFF_S9_B1_REG_MSK
#define ANC_IIR_COEFF_S9_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S9_B1_REG_POS)

//S9_B2 offsetaddress : 0x100BC
//S9_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S9_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S9_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S9_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S9_B2_REG      ANC_IIR_COEFF_S9_B2_REG_MSK
#define ANC_IIR_COEFF_S9_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S9_B2_REG_POS)

//S9_A1 offsetaddress : 0x100C0
//S9_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S9_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S9_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S9_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S9_A1_REG      ANC_IIR_COEFF_S9_A1_REG_MSK
#define ANC_IIR_COEFF_S9_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S9_A1_REG_POS)

//S9_A2 offsetaddress : 0x100C4
//S9_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S9_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S9_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S9_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S9_A2_REG      ANC_IIR_COEFF_S9_A2_REG_MSK
#define ANC_IIR_COEFF_S9_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S9_A2_REG_POS)

//S10_B0 offsetaddress : 0x100C8
//S10_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S10_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S10_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S10_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S10_B0_REG      ANC_IIR_COEFF_S10_B0_REG_MSK
#define ANC_IIR_COEFF_S10_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S10_B0_REG_POS)

//S10_B1 offsetaddress : 0x100CC
//S10_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S10_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S10_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S10_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S10_B1_REG      ANC_IIR_COEFF_S10_B1_REG_MSK
#define ANC_IIR_COEFF_S10_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S10_B1_REG_POS)

//S10_B2 offsetaddress : 0x100D0
//S10_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S10_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S10_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S10_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S10_B2_REG      ANC_IIR_COEFF_S10_B2_REG_MSK
#define ANC_IIR_COEFF_S10_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S10_B2_REG_POS)

//S10_A1 offsetaddress : 0x100D4
//S10_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S10_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S10_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S10_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S10_A1_REG      ANC_IIR_COEFF_S10_A1_REG_MSK
#define ANC_IIR_COEFF_S10_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S10_A1_REG_POS)

//S10_A2 offsetaddress : 0x100D8
//S10_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S10_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S10_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S10_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S10_A2_REG      ANC_IIR_COEFF_S10_A2_REG_MSK
#define ANC_IIR_COEFF_S10_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S10_A2_REG_POS)

//S11_B0 offsetaddress : 0x100DC
//S11_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S11_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S11_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S11_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S11_B0_REG      ANC_IIR_COEFF_S11_B0_REG_MSK
#define ANC_IIR_COEFF_S11_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S11_B0_REG_POS)

//S11_B1 offsetaddress : 0x100E0
//S11_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S11_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S11_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S11_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S11_B1_REG      ANC_IIR_COEFF_S11_B1_REG_MSK
#define ANC_IIR_COEFF_S11_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S11_B1_REG_POS)

//S11_B2 offsetaddress : 0x100E4
//S11_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S11_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S11_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S11_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S11_B2_REG      ANC_IIR_COEFF_S11_B2_REG_MSK
#define ANC_IIR_COEFF_S11_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S11_B2_REG_POS)

//S11_A1 offsetaddress : 0x100E8
//S11_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S11_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S11_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S11_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S11_A1_REG      ANC_IIR_COEFF_S11_A1_REG_MSK
#define ANC_IIR_COEFF_S11_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S11_A1_REG_POS)

//S11_A2 offsetaddress : 0x100EC
//S11_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S11_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S11_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S11_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S11_A2_REG      ANC_IIR_COEFF_S11_A2_REG_MSK
#define ANC_IIR_COEFF_S11_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S11_A2_REG_POS)

//S12_B0 offsetaddress : 0x100F0
//S12_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S12_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S12_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S12_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S12_B0_REG      ANC_IIR_COEFF_S12_B0_REG_MSK
#define ANC_IIR_COEFF_S12_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S12_B0_REG_POS)

//S12_B1 offsetaddress : 0x100F4
//S12_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S12_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S12_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S12_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S12_B1_REG      ANC_IIR_COEFF_S12_B1_REG_MSK
#define ANC_IIR_COEFF_S12_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S12_B1_REG_POS)

//S12_B2 offsetaddress : 0x100F8
//S12_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S12_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S12_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S12_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S12_B2_REG      ANC_IIR_COEFF_S12_B2_REG_MSK
#define ANC_IIR_COEFF_S12_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S12_B2_REG_POS)

//S12_A1 offsetaddress : 0x100FC
//S12_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S12_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S12_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S12_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S12_A1_REG      ANC_IIR_COEFF_S12_A1_REG_MSK
#define ANC_IIR_COEFF_S12_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S12_A1_REG_POS)

//S12_A2 offsetaddress : 0x10100
//S12_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S12_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S12_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S12_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S12_A2_REG      ANC_IIR_COEFF_S12_A2_REG_MSK
#define ANC_IIR_COEFF_S12_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S12_A2_REG_POS)

//S13_B0 offsetaddress : 0x10104
//S13_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S13_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S13_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S13_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S13_B0_REG      ANC_IIR_COEFF_S13_B0_REG_MSK
#define ANC_IIR_COEFF_S13_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S13_B0_REG_POS)

//S13_B1 offsetaddress : 0x10108
//S13_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S13_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S13_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S13_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S13_B1_REG      ANC_IIR_COEFF_S13_B1_REG_MSK
#define ANC_IIR_COEFF_S13_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S13_B1_REG_POS)

//S13_B2 offsetaddress : 0x1010C
//S13_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S13_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S13_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S13_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S13_B2_REG      ANC_IIR_COEFF_S13_B2_REG_MSK
#define ANC_IIR_COEFF_S13_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S13_B2_REG_POS)

//S13_A1 offsetaddress : 0x10110
//S13_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S13_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S13_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S13_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S13_A1_REG      ANC_IIR_COEFF_S13_A1_REG_MSK
#define ANC_IIR_COEFF_S13_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S13_A1_REG_POS)

//S13_A2 offsetaddress : 0x10114
//S13_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S13_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S13_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S13_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S13_A2_REG      ANC_IIR_COEFF_S13_A2_REG_MSK
#define ANC_IIR_COEFF_S13_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S13_A2_REG_POS)

//S14_B0 offsetaddress : 0x10118
//S14_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S14_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S14_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S14_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S14_B0_REG      ANC_IIR_COEFF_S14_B0_REG_MSK
#define ANC_IIR_COEFF_S14_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S14_B0_REG_POS)

//S14_B1 offsetaddress : 0x1011C
//S14_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S14_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S14_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S14_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S14_B1_REG      ANC_IIR_COEFF_S14_B1_REG_MSK
#define ANC_IIR_COEFF_S14_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S14_B1_REG_POS)

//S14_B2 offsetaddress : 0x10120
//S14_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S14_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S14_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S14_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S14_B2_REG      ANC_IIR_COEFF_S14_B2_REG_MSK
#define ANC_IIR_COEFF_S14_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S14_B2_REG_POS)

//S14_A1 offsetaddress : 0x10124
//S14_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S14_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S14_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S14_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S14_A1_REG      ANC_IIR_COEFF_S14_A1_REG_MSK
#define ANC_IIR_COEFF_S14_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S14_A1_REG_POS)

//S14_A2 offsetaddress : 0x10128
//S14_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S14_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S14_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S14_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S14_A2_REG      ANC_IIR_COEFF_S14_A2_REG_MSK
#define ANC_IIR_COEFF_S14_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S14_A2_REG_POS)

//S15_B0 offsetaddress : 0x1012C
//S15_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S15_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S15_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S15_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S15_B0_REG      ANC_IIR_COEFF_S15_B0_REG_MSK
#define ANC_IIR_COEFF_S15_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S15_B0_REG_POS)

//S15_B1 offsetaddress : 0x10130
//S15_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S15_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S15_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S15_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S15_B1_REG      ANC_IIR_COEFF_S15_B1_REG_MSK
#define ANC_IIR_COEFF_S15_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S15_B1_REG_POS)

//S15_B2 offsetaddress : 0x10134
//S15_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S15_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S15_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S15_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S15_B2_REG      ANC_IIR_COEFF_S15_B2_REG_MSK
#define ANC_IIR_COEFF_S15_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S15_B2_REG_POS)

//S15_A1 offsetaddress : 0x10138
//S15_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S15_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S15_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S15_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S15_A1_REG      ANC_IIR_COEFF_S15_A1_REG_MSK
#define ANC_IIR_COEFF_S15_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S15_A1_REG_POS)

//S15_A2 offsetaddress : 0x1013C
//S15_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S15_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S15_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S15_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S15_A2_REG      ANC_IIR_COEFF_S15_A2_REG_MSK
#define ANC_IIR_COEFF_S15_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S15_A2_REG_POS)

//S16_B0 offsetaddress : 0x10140
//S16_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S16_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S16_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S16_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S16_B0_REG      ANC_IIR_COEFF_S16_B0_REG_MSK
#define ANC_IIR_COEFF_S16_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S16_B0_REG_POS)

//S16_B1 offsetaddress : 0x10144
//S16_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S16_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S16_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S16_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S16_B1_REG      ANC_IIR_COEFF_S16_B1_REG_MSK
#define ANC_IIR_COEFF_S16_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S16_B1_REG_POS)

//S16_B2 offsetaddress : 0x10148
//S16_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S16_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S16_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S16_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S16_B2_REG      ANC_IIR_COEFF_S16_B2_REG_MSK
#define ANC_IIR_COEFF_S16_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S16_B2_REG_POS)

//S16_A1 offsetaddress : 0x1014C
//S16_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S16_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S16_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S16_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S16_A1_REG      ANC_IIR_COEFF_S16_A1_REG_MSK
#define ANC_IIR_COEFF_S16_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S16_A1_REG_POS)

//S16_A2 offsetaddress : 0x10150
//S16_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S16_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S16_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S16_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S16_A2_REG      ANC_IIR_COEFF_S16_A2_REG_MSK
#define ANC_IIR_COEFF_S16_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S16_A2_REG_POS)

//S17_B0 offsetaddress : 0x10154
//S17_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S17_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S17_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S17_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S17_B0_REG      ANC_IIR_COEFF_S17_B0_REG_MSK
#define ANC_IIR_COEFF_S17_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S17_B0_REG_POS)

//S17_B1 offsetaddress : 0x10158
//S17_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S17_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S17_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S17_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S17_B1_REG      ANC_IIR_COEFF_S17_B1_REG_MSK
#define ANC_IIR_COEFF_S17_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S17_B1_REG_POS)

//S17_B2 offsetaddress : 0x1015C
//S17_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S17_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S17_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S17_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S17_B2_REG      ANC_IIR_COEFF_S17_B2_REG_MSK
#define ANC_IIR_COEFF_S17_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S17_B2_REG_POS)

//S17_A1 offsetaddress : 0x10160
//S17_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S17_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S17_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S17_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S17_A1_REG      ANC_IIR_COEFF_S17_A1_REG_MSK
#define ANC_IIR_COEFF_S17_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S17_A1_REG_POS)

//S17_A2 offsetaddress : 0x10164
//S17_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S17_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S17_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S17_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S17_A2_REG      ANC_IIR_COEFF_S17_A2_REG_MSK
#define ANC_IIR_COEFF_S17_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S17_A2_REG_POS)

//S18_B0 offsetaddress : 0x10168
//S18_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S18_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S18_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S18_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S18_B0_REG      ANC_IIR_COEFF_S18_B0_REG_MSK
#define ANC_IIR_COEFF_S18_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S18_B0_REG_POS)

//S18_B1 offsetaddress : 0x1016C
//S18_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S18_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S18_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S18_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S18_B1_REG      ANC_IIR_COEFF_S18_B1_REG_MSK
#define ANC_IIR_COEFF_S18_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S18_B1_REG_POS)

//S18_B2 offsetaddress : 0x10170
//S18_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S18_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S18_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S18_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S18_B2_REG      ANC_IIR_COEFF_S18_B2_REG_MSK
#define ANC_IIR_COEFF_S18_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S18_B2_REG_POS)

//S18_A1 offsetaddress : 0x10174
//S18_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S18_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S18_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S18_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S18_A1_REG      ANC_IIR_COEFF_S18_A1_REG_MSK
#define ANC_IIR_COEFF_S18_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S18_A1_REG_POS)

//S18_A2 offsetaddress : 0x10178
//S18_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S18_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S18_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S18_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S18_A2_REG      ANC_IIR_COEFF_S18_A2_REG_MSK
#define ANC_IIR_COEFF_S18_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S18_A2_REG_POS)

//S19_B0 offsetaddress : 0x1017C
//S19_B0 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S19_B0_REG_POS  (0U)
#define ANC_IIR_COEFF_S19_B0_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S19_B0_REG_POS) /*!< */
#define ANC_IIR_COEFF_S19_B0_REG      ANC_IIR_COEFF_S19_B0_REG_MSK
#define ANC_IIR_COEFF_S19_B0_REG_W(X) ((X) << ANC_IIR_COEFF_S19_B0_REG_POS)

//S19_B1 offsetaddress : 0x10180
//S19_B1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S19_B1_REG_POS  (0U)
#define ANC_IIR_COEFF_S19_B1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S19_B1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S19_B1_REG      ANC_IIR_COEFF_S19_B1_REG_MSK
#define ANC_IIR_COEFF_S19_B1_REG_W(X) ((X) << ANC_IIR_COEFF_S19_B1_REG_POS)

//S19_B2 offsetaddress : 0x10184
//S19_B2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S19_B2_REG_POS  (0U)
#define ANC_IIR_COEFF_S19_B2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S19_B2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S19_B2_REG      ANC_IIR_COEFF_S19_B2_REG_MSK
#define ANC_IIR_COEFF_S19_B2_REG_W(X) ((X) << ANC_IIR_COEFF_S19_B2_REG_POS)

//S19_A1 offsetaddress : 0x10188
//S19_A1 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S19_A1_REG_POS  (0U)
#define ANC_IIR_COEFF_S19_A1_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S19_A1_REG_POS) /*!< */
#define ANC_IIR_COEFF_S19_A1_REG      ANC_IIR_COEFF_S19_A1_REG_MSK
#define ANC_IIR_COEFF_S19_A1_REG_W(X) ((X) << ANC_IIR_COEFF_S19_A1_REG_POS)

//S19_A2 offsetaddress : 0x1018C
//S19_A2 RegResetValue : 0x0000000
#define ANC_IIR_COEFF_S19_A2_REG_POS  (0U)
#define ANC_IIR_COEFF_S19_A2_REG_MSK  (0xffffffffUL << ANC_IIR_COEFF_S19_A2_REG_POS) /*!< */
#define ANC_IIR_COEFF_S19_A2_REG      ANC_IIR_COEFF_S19_A2_REG_MSK
#define ANC_IIR_COEFF_S19_A2_REG_W(X) ((X) << ANC_IIR_COEFF_S19_A2_REG_POS)

//IIR_COEFF_CTL_REG offsetaddress : 0x10190
//IIR_COEFF_CTL_REG RegResetValue : 0x0000000
#define ANC_IIR_COEFF_EN_POS   (0U)
#define ANC_IIR_COEFF_EN_MSK   (0x1UL << ANC_IIR_COEFF_EN_POS) /*!< The synchronization coefficient is enabled. After enabling, the synchronization starts. The synchronization is automatically pulled down, and the maximum time is consumed to be a sample point.*/
#define ANC_IIR_COEFF_EN       ANC_IIR_COEFF_EN_MSK
#define ANC_IIR_COEFF_EN_W(X)  ((X) << ANC_IIR_COEFF_EN_POS)
#define ANC_IIR_COEFF_SEL_POS  (1U)
#define ANC_IIR_COEFF_SEL_MSK  (0xfUL << ANC_IIR_COEFF_SEL_POS) /*!< Coefficient selection:*/
#define ANC_IIR_COEFF_SEL      ANC_IIR_COEFF_SEL_MSK
#define ANC_IIR_COEFF_SEL_W(X) ((X) << ANC_IIR_COEFF_SEL_POS)

//AL_FB_FADE_REG_DONE offsetaddress : 0x10194
//AL_FB_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_DONE_POS  (0U)
#define ANC_TMP_AL_FB_FADE_DONE_MSK  (0x1UL << ANC_TMP_AL_FB_FADE_DONE_POS) /*!< */
#define ANC_TMP_AL_FB_FADE_DONE      ANC_TMP_AL_FB_FADE_DONE_MSK
#define ANC_TMP_AL_FB_FADE_DONE_W(X) ((X) << ANC_TMP_AL_FB_FADE_DONE_POS)

//AL_FB_FADE_REG_ENABLE offsetaddress : 0x10198
//AL_FB_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AL_FB_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AL_FB_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AL_FB_FADE_ENABLE      ANC_TMP_AL_FB_FADE_ENABLE_MSK
#define ANC_TMP_AL_FB_FADE_ENABLE_W(X) ((X) << ANC_TMP_AL_FB_FADE_ENABLE_POS)

//AL_FB_FADE_REG_COEFF offsetaddress : 0x1019C
//AL_FB_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_COEFF_POS  (0U)
#define ANC_TMP_AL_FB_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AL_FB_FADE_COEFF_POS) /*!< The initial value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AL_FB_FADE_COEFF      ANC_TMP_AL_FB_FADE_COEFF_MSK
#define ANC_TMP_AL_FB_FADE_COEFF_W(X) ((X) << ANC_TMP_AL_FB_FADE_COEFF_POS)

//AL_FB_FADE_REG_STEP offsetaddress : 0x101A0
//AL_FB_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_STEP_POS  (0U)
#define ANC_TMP_AL_FB_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AL_FB_FADE_STEP_POS) /*!< */
#define ANC_TMP_AL_FB_FADE_STEP      ANC_TMP_AL_FB_FADE_STEP_MSK
#define ANC_TMP_AL_FB_FADE_STEP_W(X) ((X) << ANC_TMP_AL_FB_FADE_STEP_POS)

//AL_FB_FADE_REG_INTERVAL offsetaddress : 0x101A4
//AL_FB_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AL_FB_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AL_FB_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AL_FB_FADE_INTERVAL      ANC_TMP_AL_FB_FADE_INTERVAL_MSK
#define ANC_TMP_AL_FB_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AL_FB_FADE_INTERVAL_POS)

//AL_FB_FADE_REG_DATA_END_MAX offsetaddress : 0x101A8
//AL_FB_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AL_FB_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AL_FB_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AL_FB_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AL_FB_FADE_DATA_END_MAX      ANC_TMP_AL_FB_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AL_FB_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AL_FB_FADE_DATA_END_MAX_POS)

//AL_SB_FADE_REG_DONE offsetaddress : 0x101B0
//AL_SB_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_DONE_POS  (0U)
#define ANC_TMP_AL_SB_FADE_DONE_MSK  (0x1UL << ANC_TMP_AL_SB_FADE_DONE_POS) /*!< */
#define ANC_TMP_AL_SB_FADE_DONE      ANC_TMP_AL_SB_FADE_DONE_MSK
#define ANC_TMP_AL_SB_FADE_DONE_W(X) ((X) << ANC_TMP_AL_SB_FADE_DONE_POS)

//AL_SB_FADE_REG_ENABLE offsetaddress : 0x101B4
//AL_SB_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AL_SB_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AL_SB_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AL_SB_FADE_ENABLE      ANC_TMP_AL_SB_FADE_ENABLE_MSK
#define ANC_TMP_AL_SB_FADE_ENABLE_W(X) ((X) << ANC_TMP_AL_SB_FADE_ENABLE_POS)

//AL_SB_FADE_REG_COEFF offsetaddress : 0x101B8
//AL_SB_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_COEFF_POS  (0U)
#define ANC_TMP_AL_SB_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AL_SB_FADE_COEFF_POS) /*!< The initial value of fade, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AL_SB_FADE_COEFF      ANC_TMP_AL_SB_FADE_COEFF_MSK
#define ANC_TMP_AL_SB_FADE_COEFF_W(X) ((X) << ANC_TMP_AL_SB_FADE_COEFF_POS)

//AL_SB_FADE_REG_STEP offsetaddress : 0x101BC
//AL_SB_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_STEP_POS  (0U)
#define ANC_TMP_AL_SB_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AL_SB_FADE_STEP_POS) /*!< */
#define ANC_TMP_AL_SB_FADE_STEP      ANC_TMP_AL_SB_FADE_STEP_MSK
#define ANC_TMP_AL_SB_FADE_STEP_W(X) ((X) << ANC_TMP_AL_SB_FADE_STEP_POS)

//AL_SB_FADE_REG_INTERVAL offsetaddress : 0x101C0
//AL_SB_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AL_SB_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AL_SB_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AL_SB_FADE_INTERVAL      ANC_TMP_AL_SB_FADE_INTERVAL_MSK
#define ANC_TMP_AL_SB_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AL_SB_FADE_INTERVAL_POS)

//AL_SB_FADE_REG_DATA_END_MAX offsetaddress : 0x101C4
//AL_SB_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AL_SB_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AL_SB_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AL_SB_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AL_SB_FADE_DATA_END_MAX      ANC_TMP_AL_SB_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AL_SB_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AL_SB_FADE_DATA_END_MAX_POS)

//AL_FF_FADE_REG_DONE offsetaddress : 0x101CC
//AL_FF_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_DONE_POS  (0U)
#define ANC_TMP_AL_FF_FADE_DONE_MSK  (0x1UL << ANC_TMP_AL_FF_FADE_DONE_POS) /*!< */
#define ANC_TMP_AL_FF_FADE_DONE      ANC_TMP_AL_FF_FADE_DONE_MSK
#define ANC_TMP_AL_FF_FADE_DONE_W(X) ((X) << ANC_TMP_AL_FF_FADE_DONE_POS)

//AL_FF_FADE_REG_ENABLE offsetaddress : 0x101D0
//AL_FF_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AL_FF_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AL_FF_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AL_FF_FADE_ENABLE      ANC_TMP_AL_FF_FADE_ENABLE_MSK
#define ANC_TMP_AL_FF_FADE_ENABLE_W(X) ((X) << ANC_TMP_AL_FF_FADE_ENABLE_POS)

//AL_FF_FADE_REG_COEFF offsetaddress : 0x101D4
//AL_FF_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_COEFF_POS  (0U)
#define ANC_TMP_AL_FF_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AL_FF_FADE_COEFF_POS) /*!< The initial value of fade, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AL_FF_FADE_COEFF      ANC_TMP_AL_FF_FADE_COEFF_MSK
#define ANC_TMP_AL_FF_FADE_COEFF_W(X) ((X) << ANC_TMP_AL_FF_FADE_COEFF_POS)

//AL_FF_FADE_REG_STEP offsetaddress : 0x101D8
//AL_FF_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_STEP_POS  (0U)
#define ANC_TMP_AL_FF_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AL_FF_FADE_STEP_POS) /*!< */
#define ANC_TMP_AL_FF_FADE_STEP      ANC_TMP_AL_FF_FADE_STEP_MSK
#define ANC_TMP_AL_FF_FADE_STEP_W(X) ((X) << ANC_TMP_AL_FF_FADE_STEP_POS)

//AL_FF_FADE_REG_INTERVAL offsetaddress : 0x101DC
//AL_FF_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AL_FF_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AL_FF_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AL_FF_FADE_INTERVAL      ANC_TMP_AL_FF_FADE_INTERVAL_MSK
#define ANC_TMP_AL_FF_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AL_FF_FADE_INTERVAL_POS)

//AL_FF_FADE_REG_DATA_END_MAX offsetaddress : 0x101E0
//AL_FF_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AL_FF_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AL_FF_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AL_FF_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AL_FF_FADE_DATA_END_MAX      ANC_TMP_AL_FF_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AL_FF_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AL_FF_FADE_DATA_END_MAX_POS)

//AR_FB_FADE_REG_DONE offsetaddress : 0x101E8
//AR_FB_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_DONE_POS  (0U)
#define ANC_TMP_AR_FB_FADE_DONE_MSK  (0x1UL << ANC_TMP_AR_FB_FADE_DONE_POS) /*!< */
#define ANC_TMP_AR_FB_FADE_DONE      ANC_TMP_AR_FB_FADE_DONE_MSK
#define ANC_TMP_AR_FB_FADE_DONE_W(X) ((X) << ANC_TMP_AR_FB_FADE_DONE_POS)

//AR_FB_FADE_REG_ENABLE offsetaddress : 0x101EC
//AR_FB_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AR_FB_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AR_FB_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AR_FB_FADE_ENABLE      ANC_TMP_AR_FB_FADE_ENABLE_MSK
#define ANC_TMP_AR_FB_FADE_ENABLE_W(X) ((X) << ANC_TMP_AR_FB_FADE_ENABLE_POS)

//AR_FB_FADE_REG_COEFF offsetaddress : 0x101F0
//AR_FB_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_COEFF_POS  (0U)
#define ANC_TMP_AR_FB_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AR_FB_FADE_COEFF_POS) /*!< The initial value of fade, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AR_FB_FADE_COEFF      ANC_TMP_AR_FB_FADE_COEFF_MSK
#define ANC_TMP_AR_FB_FADE_COEFF_W(X) ((X) << ANC_TMP_AR_FB_FADE_COEFF_POS)

//AR_FB_FADE_REG_STEP offsetaddress : 0x101F4
//AR_FB_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_STEP_POS  (0U)
#define ANC_TMP_AR_FB_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AR_FB_FADE_STEP_POS) /*!< */
#define ANC_TMP_AR_FB_FADE_STEP      ANC_TMP_AR_FB_FADE_STEP_MSK
#define ANC_TMP_AR_FB_FADE_STEP_W(X) ((X) << ANC_TMP_AR_FB_FADE_STEP_POS)

//AR_FB_FADE_REG_INTERVAL offsetaddress : 0x101F8
//AR_FB_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AR_FB_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AR_FB_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AR_FB_FADE_INTERVAL      ANC_TMP_AR_FB_FADE_INTERVAL_MSK
#define ANC_TMP_AR_FB_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AR_FB_FADE_INTERVAL_POS)

//AR_FB_FADE_REG_DATA_END_MAX offsetaddress : 0x101FC
//AR_FB_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AR_FB_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AR_FB_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AR_FB_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AR_FB_FADE_DATA_END_MAX      ANC_TMP_AR_FB_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AR_FB_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AR_FB_FADE_DATA_END_MAX_POS)

//AR_SB_FADE_REG_DONE offsetaddress : 0x10204
//AR_SB_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_DONE_POS  (0U)
#define ANC_TMP_AR_SB_FADE_DONE_MSK  (0x1UL << ANC_TMP_AR_SB_FADE_DONE_POS) /*!< */
#define ANC_TMP_AR_SB_FADE_DONE      ANC_TMP_AR_SB_FADE_DONE_MSK
#define ANC_TMP_AR_SB_FADE_DONE_W(X) ((X) << ANC_TMP_AR_SB_FADE_DONE_POS)

//AR_SB_FADE_REG_ENABLE offsetaddress : 0x10208
//AR_SB_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AR_SB_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AR_SB_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AR_SB_FADE_ENABLE      ANC_TMP_AR_SB_FADE_ENABLE_MSK
#define ANC_TMP_AR_SB_FADE_ENABLE_W(X) ((X) << ANC_TMP_AR_SB_FADE_ENABLE_POS)

//AR_SB_FADE_REG_COEFF offsetaddress : 0x1020C
//AR_SB_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_COEFF_POS  (0U)
#define ANC_TMP_AR_SB_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AR_SB_FADE_COEFF_POS) /*!< The initial value of fade, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AR_SB_FADE_COEFF      ANC_TMP_AR_SB_FADE_COEFF_MSK
#define ANC_TMP_AR_SB_FADE_COEFF_W(X) ((X) << ANC_TMP_AR_SB_FADE_COEFF_POS)

//AR_SB_FADE_REG_STEP offsetaddress : 0x10210
//AR_SB_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_STEP_POS  (0U)
#define ANC_TMP_AR_SB_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AR_SB_FADE_STEP_POS) /*!< */
#define ANC_TMP_AR_SB_FADE_STEP      ANC_TMP_AR_SB_FADE_STEP_MSK
#define ANC_TMP_AR_SB_FADE_STEP_W(X) ((X) << ANC_TMP_AR_SB_FADE_STEP_POS)

//AR_SB_FADE_REG_INTERVAL offsetaddress : 0x10214
//AR_SB_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AR_SB_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AR_SB_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AR_SB_FADE_INTERVAL      ANC_TMP_AR_SB_FADE_INTERVAL_MSK
#define ANC_TMP_AR_SB_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AR_SB_FADE_INTERVAL_POS)

//AR_SB_FADE_REG_DATA_END_MAX offsetaddress : 0x10218
//AR_SB_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AR_SB_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AR_SB_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AR_SB_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AR_SB_FADE_DATA_END_MAX      ANC_TMP_AR_SB_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AR_SB_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AR_SB_FADE_DATA_END_MAX_POS)

//AR_FF_FADE_REG_DONE offsetaddress : 0x10220
//AR_FF_FADE_REG_DONE RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_DONE_POS  (0U)
#define ANC_TMP_AR_FF_FADE_DONE_MSK  (0x1UL << ANC_TMP_AR_FF_FADE_DONE_POS) /*!< */
#define ANC_TMP_AR_FF_FADE_DONE      ANC_TMP_AR_FF_FADE_DONE_MSK
#define ANC_TMP_AR_FF_FADE_DONE_W(X) ((X) << ANC_TMP_AR_FF_FADE_DONE_POS)

//AR_FF_FADE_REG_ENABLE offsetaddress : 0x10224
//AR_FF_FADE_REG_ENABLE RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_ENABLE_POS  (0U)
#define ANC_TMP_AR_FF_FADE_ENABLE_MSK  (0x1UL << ANC_TMP_AR_FF_FADE_ENABLE_POS) /*!< */
#define ANC_TMP_AR_FF_FADE_ENABLE      ANC_TMP_AR_FF_FADE_ENABLE_MSK
#define ANC_TMP_AR_FF_FADE_ENABLE_W(X) ((X) << ANC_TMP_AR_FF_FADE_ENABLE_POS)

//AR_FF_FADE_REG_COEFF offsetaddress : 0x10228
//AR_FF_FADE_REG_COEFF RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_COEFF_POS  (0U)
#define ANC_TMP_AR_FF_FADE_COEFF_MSK  (0xffffffffUL << ANC_TMP_AR_FF_FADE_COEFF_POS) /*!< The initial value of fade, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed point number 1*/
#define ANC_TMP_AR_FF_FADE_COEFF      ANC_TMP_AR_FF_FADE_COEFF_MSK
#define ANC_TMP_AR_FF_FADE_COEFF_W(X) ((X) << ANC_TMP_AR_FF_FADE_COEFF_POS)

//AR_FF_FADE_REG_STEP offsetaddress : 0x1022C
//AR_FF_FADE_REG_STEP RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_STEP_POS  (0U)
#define ANC_TMP_AR_FF_FADE_STEP_MSK  (0xffffffffUL << ANC_TMP_AR_FF_FADE_STEP_POS) /*!< */
#define ANC_TMP_AR_FF_FADE_STEP      ANC_TMP_AR_FF_FADE_STEP_MSK
#define ANC_TMP_AR_FF_FADE_STEP_W(X) ((X) << ANC_TMP_AR_FF_FADE_STEP_POS)

//AR_FF_FADE_REG_INTERVAL offsetaddress : 0x10230
//AR_FF_FADE_REG_INTERVAL RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_INTERVAL_POS  (0U)
#define ANC_TMP_AR_FF_FADE_INTERVAL_MSK  (0xffffffffUL << ANC_TMP_AR_FF_FADE_INTERVAL_POS) /*!< */
#define ANC_TMP_AR_FF_FADE_INTERVAL      ANC_TMP_AR_FF_FADE_INTERVAL_MSK
#define ANC_TMP_AR_FF_FADE_INTERVAL_W(X) ((X) << ANC_TMP_AR_FF_FADE_INTERVAL_POS)

//AR_FF_FADE_REG_DATA_END_MAX offsetaddress : 0x10234
//AR_FF_FADE_REG_DATA_END_MAX RegResetValue : 0x0000000
#define ANC_TMP_AR_FF_FADE_DATA_END_MAX_POS  (0U)
#define ANC_TMP_AR_FF_FADE_DATA_END_MAX_MSK  (0xffffffffUL << ANC_TMP_AR_FF_FADE_DATA_END_MAX_POS) /*!< The final value of the fade coefficient, (1bit sign bit, 4bit integer bit, 27bit decimal bit), default to fixed-point number 0*/
#define ANC_TMP_AR_FF_FADE_DATA_END_MAX      ANC_TMP_AR_FF_FADE_DATA_END_MAX_MSK
#define ANC_TMP_AR_FF_FADE_DATA_END_MAX_W(X) ((X) << ANC_TMP_AR_FF_FADE_DATA_END_MAX_POS)

//ANC_COEFF_INTERRUPT_INT_RAW offsetaddress : 0x1F000
//ANC_COEFF_INTERRUPT_INT_RAW RegResetValue : 0x0000000
#define ANC_AL_FF_FADE_DONE_INTR_RAW_POS  (0U)
#define ANC_AL_FF_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AL_FF_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_FF_FADE_DONE_INTR_RAW      ANC_AL_FF_FADE_DONE_INTR_RAW_MSK
#define ANC_AL_FF_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AL_FF_FADE_DONE_INTR_RAW_POS)
#define ANC_AL_FB_FADE_DONE_INTR_RAW_POS  (1U)
#define ANC_AL_FB_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AL_FB_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_FB_FADE_DONE_INTR_RAW      ANC_AL_FB_FADE_DONE_INTR_RAW_MSK
#define ANC_AL_FB_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AL_FB_FADE_DONE_INTR_RAW_POS)
#define ANC_AL_SB_FADE_DONE_INTR_RAW_POS  (2U)
#define ANC_AL_SB_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AL_SB_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AL_SB_FADE_DONE_INTR_RAW      ANC_AL_SB_FADE_DONE_INTR_RAW_MSK
#define ANC_AL_SB_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AL_SB_FADE_DONE_INTR_RAW_POS)
#define ANC_AR_FF_FADE_DONE_INTR_RAW_POS  (3U)
#define ANC_AR_FF_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AR_FF_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_FF_FADE_DONE_INTR_RAW      ANC_AR_FF_FADE_DONE_INTR_RAW_MSK
#define ANC_AR_FF_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AR_FF_FADE_DONE_INTR_RAW_POS)
#define ANC_AR_FB_FADE_DONE_INTR_RAW_POS  (4U)
#define ANC_AR_FB_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AR_FB_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_FB_FADE_DONE_INTR_RAW      ANC_AR_FB_FADE_DONE_INTR_RAW_MSK
#define ANC_AR_FB_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AR_FB_FADE_DONE_INTR_RAW_POS)
#define ANC_AR_SB_FADE_DONE_INTR_RAW_POS  (5U)
#define ANC_AR_SB_FADE_DONE_INTR_RAW_MSK  (0x1UL << ANC_AR_SB_FADE_DONE_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_AR_SB_FADE_DONE_INTR_RAW      ANC_AR_SB_FADE_DONE_INTR_RAW_MSK
#define ANC_AR_SB_FADE_DONE_INTR_RAW_W(X) ((X) << ANC_AR_SB_FADE_DONE_INTR_RAW_POS)
#define ANC_IIR_COEFF_EN_INTR_RAW_POS     (6U)
#define ANC_IIR_COEFF_EN_INTR_RAW_MSK     (0x1UL << ANC_IIR_COEFF_EN_INTR_RAW_POS) /*!< raw, default 0*/
#define ANC_IIR_COEFF_EN_INTR_RAW         ANC_IIR_COEFF_EN_INTR_RAW_MSK
#define ANC_IIR_COEFF_EN_INTR_RAW_W(X)    ((X) << ANC_IIR_COEFF_EN_INTR_RAW_POS)

//ANC_COEFF_INTERRUPT_INT_FORCE offsetaddress : 0x1F004
//ANC_COEFF_INTERRUPT_INT_FORCE RegResetValue : 0x0000000
#define ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (0U)
#define ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (1U)
#define ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (2U)
#define ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AL_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (3U)
#define ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_FF_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (4U)
#define ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_FB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS  (5U)
#define ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK  (0x1UL << ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE      ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X) ((X) << ANC_AR_SB_FADE_DONE_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)
#define ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS     (6U)
#define ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK     (0x1UL << ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS) /*!< force, write 1 set, debug use*/
#define ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE         ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_MSK
#define ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_W(X)    ((X) << ANC_IIR_COEFF_EN_INTR_RAW_ANC_COEFF_INTERRUPT_INT_FORCE_POS)

//ANC_COEFF_INTERRUPT_INT_MASK offsetaddress : 0x1F008
//ANC_COEFF_INTERRUPT_INT_MASK RegResetValue : 0x0000000
#define ANC_AL_FF_FADE_DONE_INTR_MASK_POS  (0U)
#define ANC_AL_FF_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AL_FF_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_FF_FADE_DONE_INTR_MASK      ANC_AL_FF_FADE_DONE_INTR_MASK_MSK
#define ANC_AL_FF_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AL_FF_FADE_DONE_INTR_MASK_POS)
#define ANC_AL_FB_FADE_DONE_INTR_MASK_POS  (1U)
#define ANC_AL_FB_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AL_FB_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_FB_FADE_DONE_INTR_MASK      ANC_AL_FB_FADE_DONE_INTR_MASK_MSK
#define ANC_AL_FB_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AL_FB_FADE_DONE_INTR_MASK_POS)
#define ANC_AL_SB_FADE_DONE_INTR_MASK_POS  (2U)
#define ANC_AL_SB_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AL_SB_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AL_SB_FADE_DONE_INTR_MASK      ANC_AL_SB_FADE_DONE_INTR_MASK_MSK
#define ANC_AL_SB_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AL_SB_FADE_DONE_INTR_MASK_POS)
#define ANC_AR_FF_FADE_DONE_INTR_MASK_POS  (3U)
#define ANC_AR_FF_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AR_FF_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_FF_FADE_DONE_INTR_MASK      ANC_AR_FF_FADE_DONE_INTR_MASK_MSK
#define ANC_AR_FF_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AR_FF_FADE_DONE_INTR_MASK_POS)
#define ANC_AR_FB_FADE_DONE_INTR_MASK_POS  (4U)
#define ANC_AR_FB_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AR_FB_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_FB_FADE_DONE_INTR_MASK      ANC_AR_FB_FADE_DONE_INTR_MASK_MSK
#define ANC_AR_FB_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AR_FB_FADE_DONE_INTR_MASK_POS)
#define ANC_AR_SB_FADE_DONE_INTR_MASK_POS  (5U)
#define ANC_AR_SB_FADE_DONE_INTR_MASK_MSK  (0x1UL << ANC_AR_SB_FADE_DONE_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_AR_SB_FADE_DONE_INTR_MASK      ANC_AR_SB_FADE_DONE_INTR_MASK_MSK
#define ANC_AR_SB_FADE_DONE_INTR_MASK_W(X) ((X) << ANC_AR_SB_FADE_DONE_INTR_MASK_POS)
#define ANC_IIR_COEFF_EN_INTR_MASK_POS     (6U)
#define ANC_IIR_COEFF_EN_INTR_MASK_MSK     (0x1UL << ANC_IIR_COEFF_EN_INTR_MASK_POS) /*!< mask, default 1, int off*/
#define ANC_IIR_COEFF_EN_INTR_MASK         ANC_IIR_COEFF_EN_INTR_MASK_MSK
#define ANC_IIR_COEFF_EN_INTR_MASK_W(X)    ((X) << ANC_IIR_COEFF_EN_INTR_MASK_POS)

//ANC_COEFF_INTERRUPT_INT_STATUS offsetaddress : 0x1F00C
//ANC_COEFF_INTERRUPT_INT_STATUS RegResetValue : 0x0000000
#define ANC_AL_FF_FADE_DONE_INTR_STATUS_POS  (0U)
#define ANC_AL_FF_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AL_FF_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_FF_FADE_DONE_INTR_STATUS      ANC_AL_FF_FADE_DONE_INTR_STATUS_MSK
#define ANC_AL_FF_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AL_FF_FADE_DONE_INTR_STATUS_POS)
#define ANC_AL_FB_FADE_DONE_INTR_STATUS_POS  (1U)
#define ANC_AL_FB_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AL_FB_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_FB_FADE_DONE_INTR_STATUS      ANC_AL_FB_FADE_DONE_INTR_STATUS_MSK
#define ANC_AL_FB_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AL_FB_FADE_DONE_INTR_STATUS_POS)
#define ANC_AL_SB_FADE_DONE_INTR_STATUS_POS  (2U)
#define ANC_AL_SB_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AL_SB_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AL_SB_FADE_DONE_INTR_STATUS      ANC_AL_SB_FADE_DONE_INTR_STATUS_MSK
#define ANC_AL_SB_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AL_SB_FADE_DONE_INTR_STATUS_POS)
#define ANC_AR_FF_FADE_DONE_INTR_STATUS_POS  (3U)
#define ANC_AR_FF_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AR_FF_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_FF_FADE_DONE_INTR_STATUS      ANC_AR_FF_FADE_DONE_INTR_STATUS_MSK
#define ANC_AR_FF_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AR_FF_FADE_DONE_INTR_STATUS_POS)
#define ANC_AR_FB_FADE_DONE_INTR_STATUS_POS  (4U)
#define ANC_AR_FB_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AR_FB_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_FB_FADE_DONE_INTR_STATUS      ANC_AR_FB_FADE_DONE_INTR_STATUS_MSK
#define ANC_AR_FB_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AR_FB_FADE_DONE_INTR_STATUS_POS)
#define ANC_AR_SB_FADE_DONE_INTR_STATUS_POS  (5U)
#define ANC_AR_SB_FADE_DONE_INTR_STATUS_MSK  (0x1UL << ANC_AR_SB_FADE_DONE_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_AR_SB_FADE_DONE_INTR_STATUS      ANC_AR_SB_FADE_DONE_INTR_STATUS_MSK
#define ANC_AR_SB_FADE_DONE_INTR_STATUS_W(X) ((X) << ANC_AR_SB_FADE_DONE_INTR_STATUS_POS)
#define ANC_IIR_COEFF_EN_INTR_STATUS_POS     (6U)
#define ANC_IIR_COEFF_EN_INTR_STATUS_MSK     (0x1UL << ANC_IIR_COEFF_EN_INTR_STATUS_POS) /*!< stauts default 0*/
#define ANC_IIR_COEFF_EN_INTR_STATUS         ANC_IIR_COEFF_EN_INTR_STATUS_MSK
#define ANC_IIR_COEFF_EN_INTR_STATUS_W(X)    ((X) << ANC_IIR_COEFF_EN_INTR_STATUS_POS)

typedef struct {
    volatile uint32_t ANC_L_CTL;          //offsetaddress : 0x0000
    volatile uint32_t ANC_L_RSSI_SIZE0;   //offsetaddress : 0x0004
    volatile uint32_t ANC_L_RSSI_SIZE1;   //offsetaddress : 0x0008
    volatile uint32_t ANC_L_DATAPATH_SEL; //offsetaddress : 0x000C
    volatile uint32_t ANC_L_CTL2;         //offsetaddress : 0x0010
    volatile uint32_t rev_0[(0x0400 - 0x0010) / 4 - 1];
    volatile uint32_t ANC_L_RSSI_RSLT0;  //offsetaddress : 0x0400
    volatile uint32_t ANC_L_RSSI_RSLT1;  //offsetaddress : 0x0404
    volatile uint32_t ANC_L_RSSI_DEBUG1; //offsetaddress : 0x0408
    volatile uint32_t ANC_L_RSSI_DEBUG2; //offsetaddress : 0x040C
    volatile uint32_t ANC_L_RSSI_DEBUG3; //offsetaddress : 0x0410
    volatile uint32_t rev_1[(0x0500 - 0x0410) / 4 - 1];
    volatile uint32_t ANC_L_MN_IIR; //offsetaddress : 0x0500
    volatile uint32_t ANC_L_SC_IIR; //offsetaddress : 0x0504
    volatile uint32_t rev_2[(0x0800 - 0x0504) / 4 - 1];
    volatile uint32_t ANC_R_CTL;          //offsetaddress : 0x0800
    volatile uint32_t ANC_R_RSSI_SIZE0;   //offsetaddress : 0x0804
    volatile uint32_t ANC_R_RSSI_SIZE1;   //offsetaddress : 0x0808
    volatile uint32_t ANC_R_DATAPATH_SEL; //offsetaddress : 0x080C
    volatile uint32_t ANC_R_CTL2;         //offsetaddress : 0x0810
    volatile uint32_t rev_3[(0x0C00 - 0x0810) / 4 - 1];
    volatile uint32_t ANC_R_RSSI_RSLT0;  //offsetaddress : 0x0C00
    volatile uint32_t ANC_R_RSSI_RSLT1;  //offsetaddress : 0x0C04
    volatile uint32_t ANC_R_RSSI_DEBUG1; //offsetaddress : 0x0C08
    volatile uint32_t ANC_R_RSSI_DEBUG2; //offsetaddress : 0x0C0C
    volatile uint32_t AL_ASRC;           //offsetaddress : 0x0C10
    volatile uint32_t AR_ASRC;           //offsetaddress : 0x0C14
    volatile uint32_t ANC_R_RSSI_DEBUG3; //offsetaddress : 0x0C18
    volatile uint32_t rev_4[(0x0C20 - 0x0C18) / 4 - 1];
    volatile uint32_t AR_ANC_IIR_FB;    //offsetaddress : 0x0C20
    volatile uint32_t AL_ANC_IIR_FB;    //offsetaddress : 0x0C24
    volatile uint32_t ANC_EN_48M_96M;   //offsetaddress : 0x0C28
    volatile uint32_t PPM_ADJ_CRTL0;    //offsetaddress : 0x0C2C
    volatile uint32_t PPM_ADJ_CRTL1;    //offsetaddress : 0x0C30
    volatile uint32_t PPM_ADJ_CRTL2;    //offsetaddress : 0x0C34
    volatile uint32_t PPM_ADJ_CRTL3;    //offsetaddress : 0x0C38
    volatile uint32_t PPM_ADJ_CRTL4;    //offsetaddress : 0x0C3C
    volatile uint32_t AR_FIR_FB_HF;     //offsetaddress : 0x0C40
    volatile uint32_t AR_FIR_COE_A;     //offsetaddress : 0x0C44
    volatile uint32_t AR_FIR_COE_D;     //offsetaddress : 0x0C48
    volatile uint32_t AR_FIR_INIT_DONE; //offsetaddress : 0x0C4C
    volatile uint32_t AR_FIR_ENABLE;    //offsetaddress : 0x0C50
    volatile uint32_t AL_FIR_FB_HF;     //offsetaddress : 0x0C54
    volatile uint32_t AL_FIR_COE_A;     //offsetaddress : 0x0C58
    volatile uint32_t AL_FIR_COE_D;     //offsetaddress : 0x0C5C
    volatile uint32_t AL_FIR_INIT_DONE; //offsetaddress : 0x0C60
    volatile uint32_t AL_FIR_ENABLE;    //offsetaddress : 0x0C64
    volatile uint32_t AR_FIR_COE_Q;     //offsetaddress : 0x0C68
    volatile uint32_t AL_FIR_COE_Q;     //offsetaddress : 0x0C6C
    volatile uint32_t rev_5[(0x0CF0 - 0x0C6C) / 4 - 1];
    volatile uint32_t AL_ASRC2; //offsetaddress : 0x0CF0
    volatile uint32_t AR_ASRC2; //offsetaddress : 0x0CF4
    volatile uint32_t rev_6[(0x0D00 - 0x0CF4) / 4 - 1];
    volatile uint32_t ANC_R_TR_IIR;        //offsetaddress : 0x0D00
    volatile uint32_t ANC_L_IIR_ORDER_SEL; //offsetaddress : 0x0D04
    volatile uint32_t ANC_R_IIR_ORDER_SEL; //offsetaddress : 0x0D08
    volatile uint32_t rev_7[(0x0DE0 - 0x0D08) / 4 - 1];
    volatile uint32_t ANC_LR_SYNC_START; //offsetaddress : 0x0DE0
    volatile uint32_t rev_8[(0x0E00 - 0x0DE0) / 4 - 1];
    volatile uint32_t ANC_L_MN_GC_REG0; //offsetaddress : 0x0E00
    volatile uint32_t ANC_L_MN_GC_REG1; //offsetaddress : 0x0E04
    volatile uint32_t ANC_L_MN_GC_REG2; //offsetaddress : 0x0E08
    volatile uint32_t ANC_L_MN_GC_REG3; //offsetaddress : 0x0E0C
    volatile uint32_t ANC_L_SC_GC_REG0; //offsetaddress : 0x0E10
    volatile uint32_t ANC_L_SC_GC_REG1; //offsetaddress : 0x0E14
    volatile uint32_t ANC_L_SC_GC_REG2; //offsetaddress : 0x0E18
    volatile uint32_t ANC_L_SC_GC_REG3; //offsetaddress : 0x0E1C
    volatile uint32_t ANC_L_EQ_GC_REG0; //offsetaddress : 0x0E20
    volatile uint32_t ANC_L_EQ_GC_REG1; //offsetaddress : 0x0E24
    volatile uint32_t ANC_L_EQ_GC_REG2; //offsetaddress : 0x0E28
    volatile uint32_t ANC_L_EQ_GC_REG3; //offsetaddress : 0x0E2C
    volatile uint32_t ANC_R_TR_GC_REG0; //offsetaddress : 0x0E30
    volatile uint32_t ANC_R_TR_GC_REG1; //offsetaddress : 0x0E34
    volatile uint32_t ANC_R_TR_GC_REG2; //offsetaddress : 0x0E38
    volatile uint32_t ANC_R_TR_GC_REG3; //offsetaddress : 0x0E3C
    volatile uint32_t ANC_R_EQ_GC_REG0; //offsetaddress : 0x0E40
    volatile uint32_t ANC_R_EQ_GC_REG1; //offsetaddress : 0x0E44
    volatile uint32_t ANC_R_EQ_GC_REG2; //offsetaddress : 0x0E48
    volatile uint32_t ANC_R_EQ_GC_REG3; //offsetaddress : 0x0E4C
    volatile uint32_t rev_9[(0xF000 - 0x0E4C) / 4 - 1];
    volatile uint32_t ANC_REGIF_INTERRUPT_INT_RAW;    //offsetaddress : 0xF000
    volatile uint32_t ANC_REGIF_INTERRUPT_INT_FORCE;  //offsetaddress : 0xF004
    volatile uint32_t ANC_REGIF_INTERRUPT_INT_MASK;   //offsetaddress : 0xF008
    volatile uint32_t ANC_REGIF_INTERRUPT_INT_STATUS; //offsetaddress : 0xF00C
    volatile uint32_t rev_10[(0x10000 - 0xF00C) / 4 - 1];
    volatile uint32_t S0_B0;                       //offsetaddress : 0x10000
    volatile uint32_t S0_B1;                       //offsetaddress : 0x10004
    volatile uint32_t S0_B2;                       //offsetaddress : 0x10008
    volatile uint32_t S0_A1;                       //offsetaddress : 0x1000C
    volatile uint32_t S0_A2;                       //offsetaddress : 0x10010
    volatile uint32_t S1_B0;                       //offsetaddress : 0x10014
    volatile uint32_t S1_B1;                       //offsetaddress : 0x10018
    volatile uint32_t S1_B2;                       //offsetaddress : 0x1001C
    volatile uint32_t S1_A1;                       //offsetaddress : 0x10020
    volatile uint32_t S1_A2;                       //offsetaddress : 0x10024
    volatile uint32_t S2_B0;                       //offsetaddress : 0x10028
    volatile uint32_t S2_B1;                       //offsetaddress : 0x1002C
    volatile uint32_t S2_B2;                       //offsetaddress : 0x10030
    volatile uint32_t S2_A1;                       //offsetaddress : 0x10034
    volatile uint32_t S2_A2;                       //offsetaddress : 0x10038
    volatile uint32_t S3_B0;                       //offsetaddress : 0x1003C
    volatile uint32_t S3_B1;                       //offsetaddress : 0x10040
    volatile uint32_t S3_B2;                       //offsetaddress : 0x10044
    volatile uint32_t S3_A1;                       //offsetaddress : 0x10048
    volatile uint32_t S3_A2;                       //offsetaddress : 0x1004C
    volatile uint32_t S4_B0;                       //offsetaddress : 0x10050
    volatile uint32_t S4_B1;                       //offsetaddress : 0x10054
    volatile uint32_t S4_B2;                       //offsetaddress : 0x10058
    volatile uint32_t S4_A1;                       //offsetaddress : 0x1005C
    volatile uint32_t S4_A2;                       //offsetaddress : 0x10060
    volatile uint32_t S5_B0;                       //offsetaddress : 0x10064
    volatile uint32_t S5_B1;                       //offsetaddress : 0x10068
    volatile uint32_t S5_B2;                       //offsetaddress : 0x1006C
    volatile uint32_t S5_A1;                       //offsetaddress : 0x10070
    volatile uint32_t S5_A2;                       //offsetaddress : 0x10074
    volatile uint32_t S6_B0;                       //offsetaddress : 0x10078
    volatile uint32_t S6_B1;                       //offsetaddress : 0x1007C
    volatile uint32_t S6_B2;                       //offsetaddress : 0x10080
    volatile uint32_t S6_A1;                       //offsetaddress : 0x10084
    volatile uint32_t S6_A2;                       //offsetaddress : 0x10088
    volatile uint32_t S7_B0;                       //offsetaddress : 0x1008C
    volatile uint32_t S7_B1;                       //offsetaddress : 0x10090
    volatile uint32_t S7_B2;                       //offsetaddress : 0x10094
    volatile uint32_t S7_A1;                       //offsetaddress : 0x10098
    volatile uint32_t S7_A2;                       //offsetaddress : 0x1009C
    volatile uint32_t S8_B0;                       //offsetaddress : 0x100A0
    volatile uint32_t S8_B1;                       //offsetaddress : 0x100A4
    volatile uint32_t S8_B2;                       //offsetaddress : 0x100A8
    volatile uint32_t S8_A1;                       //offsetaddress : 0x100AC
    volatile uint32_t S8_A2;                       //offsetaddress : 0x100B0
    volatile uint32_t S9_B0;                       //offsetaddress : 0x100B4
    volatile uint32_t S9_B1;                       //offsetaddress : 0x100B8
    volatile uint32_t S9_B2;                       //offsetaddress : 0x100BC
    volatile uint32_t S9_A1;                       //offsetaddress : 0x100C0
    volatile uint32_t S9_A2;                       //offsetaddress : 0x100C4
    volatile uint32_t S10_B0;                      //offsetaddress : 0x100C8
    volatile uint32_t S10_B1;                      //offsetaddress : 0x100CC
    volatile uint32_t S10_B2;                      //offsetaddress : 0x100D0
    volatile uint32_t S10_A1;                      //offsetaddress : 0x100D4
    volatile uint32_t S10_A2;                      //offsetaddress : 0x100D8
    volatile uint32_t S11_B0;                      //offsetaddress : 0x100DC
    volatile uint32_t S11_B1;                      //offsetaddress : 0x100E0
    volatile uint32_t S11_B2;                      //offsetaddress : 0x100E4
    volatile uint32_t S11_A1;                      //offsetaddress : 0x100E8
    volatile uint32_t S11_A2;                      //offsetaddress : 0x100EC
    volatile uint32_t S12_B0;                      //offsetaddress : 0x100F0
    volatile uint32_t S12_B1;                      //offsetaddress : 0x100F4
    volatile uint32_t S12_B2;                      //offsetaddress : 0x100F8
    volatile uint32_t S12_A1;                      //offsetaddress : 0x100FC
    volatile uint32_t S12_A2;                      //offsetaddress : 0x10100
    volatile uint32_t S13_B0;                      //offsetaddress : 0x10104
    volatile uint32_t S13_B1;                      //offsetaddress : 0x10108
    volatile uint32_t S13_B2;                      //offsetaddress : 0x1010C
    volatile uint32_t S13_A1;                      //offsetaddress : 0x10110
    volatile uint32_t S13_A2;                      //offsetaddress : 0x10114
    volatile uint32_t S14_B0;                      //offsetaddress : 0x10118
    volatile uint32_t S14_B1;                      //offsetaddress : 0x1011C
    volatile uint32_t S14_B2;                      //offsetaddress : 0x10120
    volatile uint32_t S14_A1;                      //offsetaddress : 0x10124
    volatile uint32_t S14_A2;                      //offsetaddress : 0x10128
    volatile uint32_t S15_B0;                      //offsetaddress : 0x1012C
    volatile uint32_t S15_B1;                      //offsetaddress : 0x10130
    volatile uint32_t S15_B2;                      //offsetaddress : 0x10134
    volatile uint32_t S15_A1;                      //offsetaddress : 0x10138
    volatile uint32_t S15_A2;                      //offsetaddress : 0x1013C
    volatile uint32_t S16_B0;                      //offsetaddress : 0x10140
    volatile uint32_t S16_B1;                      //offsetaddress : 0x10144
    volatile uint32_t S16_B2;                      //offsetaddress : 0x10148
    volatile uint32_t S16_A1;                      //offsetaddress : 0x1014C
    volatile uint32_t S16_A2;                      //offsetaddress : 0x10150
    volatile uint32_t S17_B0;                      //offsetaddress : 0x10154
    volatile uint32_t S17_B1;                      //offsetaddress : 0x10158
    volatile uint32_t S17_B2;                      //offsetaddress : 0x1015C
    volatile uint32_t S17_A1;                      //offsetaddress : 0x10160
    volatile uint32_t S17_A2;                      //offsetaddress : 0x10164
    volatile uint32_t S18_B0;                      //offsetaddress : 0x10168
    volatile uint32_t S18_B1;                      //offsetaddress : 0x1016C
    volatile uint32_t S18_B2;                      //offsetaddress : 0x10170
    volatile uint32_t S18_A1;                      //offsetaddress : 0x10174
    volatile uint32_t S18_A2;                      //offsetaddress : 0x10178
    volatile uint32_t S19_B0;                      //offsetaddress : 0x1017C
    volatile uint32_t S19_B1;                      //offsetaddress : 0x10180
    volatile uint32_t S19_B2;                      //offsetaddress : 0x10184
    volatile uint32_t S19_A1;                      //offsetaddress : 0x10188
    volatile uint32_t S19_A2;                      //offsetaddress : 0x1018C
    volatile uint32_t IIR_COEFF_CTL_REG;           //offsetaddress : 0x10190
    volatile uint32_t AL_FB_FADE_REG_DONE;         //offsetaddress : 0x10194
    volatile uint32_t AL_FB_FADE_REG_ENABLE;       //offsetaddress : 0x10198
    volatile uint32_t AL_FB_FADE_REG_COEFF;        //offsetaddress : 0x1019C
    volatile uint32_t AL_FB_FADE_REG_STEP;         //offsetaddress : 0x101A0
    volatile uint32_t AL_FB_FADE_REG_INTERVAL;     //offsetaddress : 0x101A4
    volatile uint32_t AL_FB_FADE_REG_DATA_END_MAX; //offsetaddress : 0x101A8
    volatile uint32_t rev_11[(0x101B0 - 0x101A8) / 4 - 1];
    volatile uint32_t AL_SB_FADE_REG_DONE;         //offsetaddress : 0x101B0
    volatile uint32_t AL_SB_FADE_REG_ENABLE;       //offsetaddress : 0x101B4
    volatile uint32_t AL_SB_FADE_REG_COEFF;        //offsetaddress : 0x101B8
    volatile uint32_t AL_SB_FADE_REG_STEP;         //offsetaddress : 0x101BC
    volatile uint32_t AL_SB_FADE_REG_INTERVAL;     //offsetaddress : 0x101C0
    volatile uint32_t AL_SB_FADE_REG_DATA_END_MAX; //offsetaddress : 0x101C4
    volatile uint32_t rev_12[(0x101CC - 0x101C4) / 4 - 1];
    volatile uint32_t AL_FF_FADE_REG_DONE;         //offsetaddress : 0x101CC
    volatile uint32_t AL_FF_FADE_REG_ENABLE;       //offsetaddress : 0x101D0
    volatile uint32_t AL_FF_FADE_REG_COEFF;        //offsetaddress : 0x101D4
    volatile uint32_t AL_FF_FADE_REG_STEP;         //offsetaddress : 0x101D8
    volatile uint32_t AL_FF_FADE_REG_INTERVAL;     //offsetaddress : 0x101DC
    volatile uint32_t AL_FF_FADE_REG_DATA_END_MAX; //offsetaddress : 0x101E0
    volatile uint32_t rev_13[(0x101E8 - 0x101E0) / 4 - 1];
    volatile uint32_t AR_FB_FADE_REG_DONE;         //offsetaddress : 0x101E8
    volatile uint32_t AR_FB_FADE_REG_ENABLE;       //offsetaddress : 0x101EC
    volatile uint32_t AR_FB_FADE_REG_COEFF;        //offsetaddress : 0x101F0
    volatile uint32_t AR_FB_FADE_REG_STEP;         //offsetaddress : 0x101F4
    volatile uint32_t AR_FB_FADE_REG_INTERVAL;     //offsetaddress : 0x101F8
    volatile uint32_t AR_FB_FADE_REG_DATA_END_MAX; //offsetaddress : 0x101FC
    volatile uint32_t rev_14[(0x10204 - 0x101FC) / 4 - 1];
    volatile uint32_t AR_SB_FADE_REG_DONE;         //offsetaddress : 0x10204
    volatile uint32_t AR_SB_FADE_REG_ENABLE;       //offsetaddress : 0x10208
    volatile uint32_t AR_SB_FADE_REG_COEFF;        //offsetaddress : 0x1020C
    volatile uint32_t AR_SB_FADE_REG_STEP;         //offsetaddress : 0x10210
    volatile uint32_t AR_SB_FADE_REG_INTERVAL;     //offsetaddress : 0x10214
    volatile uint32_t AR_SB_FADE_REG_DATA_END_MAX; //offsetaddress : 0x10218
    volatile uint32_t rev_15[(0x10220 - 0x10218) / 4 - 1];
    volatile uint32_t AR_FF_FADE_REG_DONE;         //offsetaddress : 0x10220
    volatile uint32_t AR_FF_FADE_REG_ENABLE;       //offsetaddress : 0x10224
    volatile uint32_t AR_FF_FADE_REG_COEFF;        //offsetaddress : 0x10228
    volatile uint32_t AR_FF_FADE_REG_STEP;         //offsetaddress : 0x1022C
    volatile uint32_t AR_FF_FADE_REG_INTERVAL;     //offsetaddress : 0x10230
    volatile uint32_t AR_FF_FADE_REG_DATA_END_MAX; //offsetaddress : 0x10234
    volatile uint32_t rev_16[(0x1F000 - 0x10234) / 4 - 1];
    volatile uint32_t ANC_COEFF_INTERRUPT_INT_RAW;    //offsetaddress : 0x1F000
    volatile uint32_t ANC_COEFF_INTERRUPT_INT_FORCE;  //offsetaddress : 0x1F004
    volatile uint32_t ANC_COEFF_INTERRUPT_INT_MASK;   //offsetaddress : 0x1F008
    volatile uint32_t ANC_COEFF_INTERRUPT_INT_STATUS; //offsetaddress : 0x1F00C
} anc_reg_t;
#ifdef __cplusplus
}
#endif
#endif
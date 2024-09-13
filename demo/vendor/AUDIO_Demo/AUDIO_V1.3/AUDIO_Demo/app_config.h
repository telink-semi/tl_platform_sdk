/********************************************************************************************************
 * @file    app_config.h
 *
 * @brief   This is the header file for B91m
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#pragma once
#include "driver.h"
#include "common.h"
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

/**
 *  TL721X
 *  codec support   input: line_in(mono only)/amic_in(mono only) /dmic_in
 *                  output: support SDM out
 *   I2S support 3 I2S (I2S0/I2S1/I2S2), only I2S2 supports TDM mode.
 */
#define    LINE_INPUT_TO_BUF_TO_LINEOUT        1  //line_in->buff->SDM out
#define    AMIC_INPUT_TO_BUF_TO_LINEOUT        2  //amic_in->buff->SDM out
#define    DMIC_INPUT_TO_BUF_TO_LINEOUT        3  //dmic_in->buff->SDM out
#define    BUFFER_TO_LINEOUT                   4  //buff to line_out
#define    DMA_IRQ_TEST                        5  //DMA llp_irq
#define    I2S_TO_EXT_CODEC_WM                 6  //I2S input->buff->I2S out for WM8731 external codec
#define    I2S_OUTPUT_DOUBLE_BUFF              7  //I2S(I2S0/I2S1/I2S2) outputs double buff data with double tx FIFO.
#define    I2S2_TDM_MODE_TEST                  8  //I2S2 TDM mode
#define    I2S_TO_2LANE_RX                     9  //2lane data rx
#define    I2S_TO_2LANE_TX                     10 //2lane data tx
#define    I2S_TO_TARGET                       11 //Reach target tick value to enable i2s
#define    I2S_ASCl_TEST                       12 //I2S Sample rate conversion ( up-sampling only)
#define    AUDIO_FIFO_IRQ_TEST                 13//FIFO threshold irq
#if defined(MCU_CORE_TL721X)
#define    I2S_ALIGN                           14//I2S supports 3 alignment modes (I2S0_I2S1_ALIGN/I2S1_I2S2_ALIGN/I2S0_I2S1_I2S2_ALIGN), and aligned I2S share a fifo and buffer.
#endif


#define    AUDIO_MODE                    AMIC_INPUT_TO_BUF_TO_LINEOUT

/* There are 4 steps in order to clear codec pop:
 * Step1 - mute audio;
 * Step2 - enable audio codec;
 * Step3 - Clear codec input pop and dis mute audio;
 * Step4 - enable codec input path, codec data come in.
 */
#define    AUDIO_CLR_CODEC_POP           1

/* Collect enough codec data and make it fade in. */
#define    AUDIO_CODEC_FADE_IN           1

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

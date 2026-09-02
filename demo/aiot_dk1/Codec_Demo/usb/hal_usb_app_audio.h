/********************************************************************************************************
 * @file    hal_usb_app_audio.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#include <inttypes.h>
#include <stddef.h>

typedef struct {
    sa_dac_t *codec_buf_spk;
    sa_adc_t *codec_buf_mic;
    sa_dac_t *codec_play_buf_spk;
    int spk_buffer_size;
    int mic_buffer_size; 
    int play_buf_spk_size;
    volatile unsigned int paly_out_w;
    volatile unsigned int paly_in_w;
    volatile unsigned int iso_out_w;
    volatile unsigned int iso_out_r;
    volatile unsigned int iso_in_w;
    volatile unsigned int iso_in_r;
    volatile unsigned int num_iso_out; 
    unsigned int usb_iso_cfg_tick_out;
    int usb_iso_out_en:1;
    int usb_iso_in_en:1;
    int first_play:1;
} hal_usb_app_audio_ctx_t;

void hal_usb_app_audio_init(hal_usb_app_audio_ctx_t *ctx);
void hal_usb_app_audio_handle_loop(void);
int16_t hal_usb_app_audio_get_curvol(void);
uint8_t hal_usb_app_audio_get_speaker_vol(void);
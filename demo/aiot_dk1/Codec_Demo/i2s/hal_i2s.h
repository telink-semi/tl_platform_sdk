/********************************************************************************************************
 * @file    hal_i2s.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#ifndef HAL_I2S_H
#define HAL_I2S_H


#ifdef __cplusplus
extern "C"
{
#endif


#define I2S_MIC_DMA DMA6
#define I2S_SPK_DMA DMA5

    void hal_i2s_init(unsigned int *mic_buff, unsigned int *spk_buff, unsigned int mic_buff_size, unsigned int spk_buff_size);


#ifdef __cplusplus
}
#endif

#endif

/********************************************************************************************************
 * @file    hal_i2c.h
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
#ifndef HAL_I2C_H
#define HAL_I2C_H

#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define I2C_CLK_SPEED 400000 //i2c clock 400K.
#if defined(MCU_CORE_TL721X)
#define I2C_GPIO_SDA_PIN GPIO_FC_PB7
#define I2C_GPIO_SCL_PIN GPIO_FC_PC0
#elif defined(MCU_CORE_TL321X)
#define I2C_GPIO_SDA_PIN GPIO_FC_PB7
#define I2C_GPIO_SCL_PIN GPIO_FC_PA4
#endif

#define I2C_TX_DMA_CHN DMA2
#define I2C_RX_DMA_CHN DMA3

    void hal_i2c_init(void);
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_es8389)
    __attribute__((section(".ram_code"))) void hal_i2c_write(uint8_t addr, uint8_t reg, uint8_t value);
    __attribute__((section(".ram_code"))) void hal_i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);
    void                                       hal_i2c_update_bits(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value);
#endif
#if (AUDIO_I2S_TO_EXT_MODE == I2S_TO_EXT_nau8821)
    __attribute__((section(".ram_code"))) void    hal_i2c_nau8821_write(uint8_t addr, uint16_t reg, uint16_t value);
    __attribute__((section(".ram_code"))) uint8_t hal_i2c_nau8821_read(uint8_t addr, uint16_t reg, uint16_t *data);
    uint8_t                                       hal_i2c_nau8821_update_bits(uint8_t addr, uint16_t reg, uint16_t mask, uint16_t value);
#endif

#ifdef __cplusplus
}
#endif

#endif

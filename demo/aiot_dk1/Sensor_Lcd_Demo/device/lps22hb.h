/********************************************************************************************************
 * @file    lps22hb.h
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
#ifndef LPS22HB_H
#define LPS22HB_H
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C"
{
#endif

#include "common.h"

#define LPS22HB_I2C_ADDR     0xB8
#define LPS22HB_WHO_AM_I     0x0F

#define LPS22HB_CTRL_REG1    0x10
#define LPS22HB_CTRL_REG2    0x11
#define LPS22HB_CTRL_REG3    0x12
#define LPS22HB_FIFO_CTRL    0x14
#define LPS22HB_RES_CONF     0x1A

#define LPS22HB_STATUS       0x27
#define LPS22HB_PRESS_OUT_XL 0x28
#define LPS22HB_PRESS_OUT_L  0x29
#define LPS22HB_PRESS_OUT_H  0x2A

#define LPS22HB_TEMP_OUT_L   0x2B
#define LPS22HB_TEMP_OUT_H   0x2C

    typedef struct
    {
        uint8_t  statue;
        uint32_t press;
        int16_t  temperature;
    } lps22hb_data_st;

    uint8_t         lps22hb_iic_init(void);
    lps22hb_data_st lps22hb_iic_get_data(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
#endif

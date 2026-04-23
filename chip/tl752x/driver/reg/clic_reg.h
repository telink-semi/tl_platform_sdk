/*******************************************************************************************************
 *
 * @file    clic_reg.h
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
#ifndef __CLIC_REG_H__
#define __CLIC_REG_H__

#include "bit.h"

/******************************* interrupt registers: n22 clic base 0xe4000000 ******************************/
#define CLIC_BASE_ADDR 0xe4000000

#define reg_clic_cfg   (*(volatile unsigned char *)(CLIC_BASE_ADDR))

enum
{
    FLD_CLIC_NLBITS = BIT_RNG(1, 4),
};

#define reg_clic_pending(i)   (*(volatile unsigned char *)(CLIC_BASE_ADDR + 0x1000 + ((i) << 2)))
#define reg_clic_src(i)       (*(volatile unsigned char *)(CLIC_BASE_ADDR + 0x1001 + ((i) << 2)))

#define reg_clic_attribute(i) (*(volatile unsigned char *)(CLIC_BASE_ADDR + 0x1002 + ((i) << 2)))

enum
{
    FLD_CLIC_SHV  = BIT(0), /**< 0 non-vectored, 1: vectored. */
    FLD_CLIC_TRIG = BIT_RNG(1, 2),
    FLD_CLIC_MODE = BIT_RNG(6, 7),
};

#define reg_clic_input_ctl(i) (*(volatile unsigned char *)(CLIC_BASE_ADDR + 0x1003 + ((i) << 2)))

enum
{
    FLD_CLIC_LEVEL = BIT_RNG(6, 7),
};

#define reg_clic_mth (*(volatile unsigned char *)(CLIC_BASE_ADDR + 0x0b))

enum
{
    FLD_CLIC_MTH = BIT_RNG(6, 7),
};

#endif /* __CLIC_REG_H__ */

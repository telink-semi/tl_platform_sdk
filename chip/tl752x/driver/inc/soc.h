/*******************************************************************************************************
 *
 * @file    soc.h
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
#pragma once

#include "bit.h"

/*Attention: for all the 2-byte address operation (like REG_ADDR16,write_reg16,read_reg16) ,
 *           the address parameter should  be multiple of 2. For example:REG_ADDR16(0x2),REG_ADDR16(0x4).
 *
 *           for all the 4-byte address operation (like REG_ADDR32,write_reg32,read_reg32) ,
 *           the address parameter should  be multiple of 4. For example:write_reg32(0x4),write_reg32(0x8).
*/
#define FLASH_R_BASE_ADDR     0x10000000
#define REG_RW_BASE_ADDR      0x00000000
#define REG_ADDR8(a)          (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (a)))
#define REG_ADDR16(a)         (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (a)))
#define REG_ADDR32(a)         (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (a)))

#define write_reg8(addr, v)   (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (addr)) = (unsigned char)(v))
#define write_reg16(addr, v)  (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (addr)) = (unsigned short)(v))
#define write_reg32(addr, v)  (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (addr)) = (unsigned long)(v))

#define read_reg8(addr)       (*(volatile unsigned char *)(REG_RW_BASE_ADDR | (addr)))
#define read_reg16(addr)      (*(volatile unsigned short *)(REG_RW_BASE_ADDR | (addr)))
#define read_reg32(addr)      (*(volatile unsigned long *)(REG_RW_BASE_ADDR | (addr)))

#define write_sram8(addr, v)  (*(volatile unsigned char *)((addr)) = (unsigned char)(v))
#define write_sram16(addr, v) (*(volatile unsigned short *)((addr)) = (unsigned short)(v))
#define write_sram32(addr, v) (*(volatile unsigned long *)((addr)) = (unsigned long)(v))

#define read_sram8(addr)      (*(volatile unsigned char *)((addr)))
#define read_sram16(addr)     (*(volatile unsigned short *)((addr)))
#define read_sram32(addr)     (*(volatile unsigned long *)((addr)))
#define TCMD_UNDER_BOTH       0xc0
#define TCMD_UNDER_RD         0x80
#define TCMD_UNDER_WR         0x40

#define TCMD_MASK             0x3f

#define TCMD_WRITE            0x3
#define TCMD_WAIT             0x7
#define TCMD_WAREG            0x8

#define D25_ILM_BASE          (0x20000)
#define D25_DLM_BASE          (0x80000)

/*******************************************************************************************************
 *
 * @file    sdmmc.h
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
#ifndef __SDMMC_H__
#define __SDMMC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sdmmc_reg {
    volatile uint32_t CTRL;       /* 0x00 < Control register, offset: 0x0 */
    volatile uint32_t PWREN;      /* 0x04 < Power Enable register, offset: 0x4 */
    volatile uint32_t CLKDIV;     /* 0x08 < Clock Divider register, offset: 0x8 */
    volatile uint32_t RESERVED_0; /* 0x0c */
    volatile uint32_t CLKENA;     /* 0x10 < Clock Enable register, offset: 0x10 */
    volatile uint32_t TMOUT;      /* 0x14 < Time-out register, offset: 0x14 */
    volatile uint32_t CTYPE;      /* 0x18 < Card Type register, offset: 0x18 */
    volatile uint32_t BLKSIZ;     /* 0x1c < Block Size register, offset: 0x1C */
    volatile uint32_t BYTCNT;     /* 0x20 < Byte Count register, offset: 0x20 */
    volatile uint32_t INTMASK;    /* 0x24 < Interrupt Mask register, offset: 0x24 */
    volatile uint32_t CMDARG;     /* 0x28 < Command Argument register, offset: 0x28 */
    volatile uint32_t CMD;        /* 0x2c < Command register, offset: 0x2C */
    volatile uint32_t RESP[4];    /* 0x30 - 0x3c < Response register, array offset: 0x30, array step: 0x4 */
    volatile uint32_t MINTSTS;    /* 0x40 < Masked Interrupt Status register, offset: 0x40 */
    volatile uint32_t RINTSTS;    /* 0x44 < Raw Interrupt Status register, offset: 0x44 */
    volatile uint32_t STATUS;     /* 0x48 < Status register, offset: 0x48 */
    volatile uint32_t FIFOTH;     /* 0x4c < FIFO Threshold Watermark register, offset: 0x4C */
    volatile uint32_t CDETECT;    /* 0x50 < Card Detect register, offset: 0x50 */
    volatile uint32_t WRTPRT;     /* 0x54 < Write Protect register, offset: 0x54 */
    volatile uint32_t SDIO_GPIO;  /* 0x58 */
    volatile uint32_t TCBCNT;     /* 0x5c < Transferred CIU Card Byte Count register, offset: 0x5C */
    volatile uint32_t TBBCNT;     /* 0x60 < Transferred Host to BIU-FIFO Byte Count register, offset: 0x60 */
    volatile uint32_t DEBNCE;     /* 0x64 < Debounce Count register, offset: 0x64 */
    volatile uint32_t USRID;      /* 0x68 */
    volatile uint32_t VERID;      /* 0x6C */
    volatile uint32_t HCON;       /* 0x70 */
    volatile uint32_t UHS_REG;    /* 0x74 */
    volatile uint32_t RST_N;      /* 0x78 < Hardware Reset, offset: 0x78 */
    volatile uint32_t RESERVED_1; /* 0x7c */
    volatile uint32_t BMOD;       /* 0x80 < Bus Mode register, offset: 0x80 */
    volatile uint32_t PLDMND;     /* 0x84 < Poll Demand register, offset: 0x84 */
    volatile uint32_t DBADDR;     /* 0x88 < Descriptor List Base Address register, offset: 0x88 */
    volatile uint32_t IDSTS;      /* 0x8c < Internal DMAC Status register, offset: 0x8C */
    volatile uint32_t IDINTEN;    /* 0x90 < Internal DMAC Interrupt Enable register, offset: 0x90 */
    volatile uint32_t DSCADDR;    /* 0x94 < Current Host Descriptor Address register, offset: 0x94 */
    volatile uint32_t BUFADDR;    /* 0x98 < Current Buffer Descriptor Address register, offset: 0x98 */
    volatile uint32_t RESERVED_2[(0x100 - 0x98) / 4 - 1];
    volatile uint32_t CARDTHRCTL;     /* Offset: 0x100 UHS Register */
    volatile uint32_t BACK_END_POWER; /* Offset: 0x104 UHS Register */
    volatile uint32_t UHS_REG_EXT;    /* Offset: 0x108 UHS Register */
    volatile uint32_t EMMC_DDR_REG;   /* Offset: 0x10C UHS Register */
    volatile uint32_t ENABLE_SHIFT;   /* Offset: 0x110 UHS Register */
    volatile uint32_t RESERVED_3[(0x200 - 0x110) / 4 - 1];
    volatile uint32_t FIFO[32]; /* SDIF FIFO, array offset: 0x200, array step: 0x4 */
} sdmmc_reg_t;

#ifdef __cplusplus
}
#endif

#endif

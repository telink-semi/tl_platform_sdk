/*******************************************************************************************************
 *
 * @file    efuse.h
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
#ifndef __EFUSE_H__
#define __EFUSE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BIT_PER_WORD          (32)
#define INIT_TIMES            (0xffffffff)
#define PRG_RETRY_TIMES       (0xffffffff)
#define EFUSE_BUSY_TIMES      (0xffffffff)
#define EFUSE_RD(num)         (num << 0)
#define EFUSE_PRG(num)        (num << 16)
#define EFUSE_PRG_BIT(num)    (num << 21)
#define EFUSE_RD_STAT_FINISH  (0 << 16)
#define EFUSE_PRG_STAT_FINISH (0 << 24)
#define EFUSE_BUSY            (0x1)

#define EFUSE_CTRL_RD_START_APB_MASK  (0x1UL << 0)
#define EFUSE_CTRL_UPDATE_SR_MASK     (0x1UL << 1)
#define EFUSE_CTRL_PRG_START_APB_MASK (0x1UL << 16)
#define EFUSE_CTRL_PRG_SEL_APB_MASK   (0x1UL << 24)

/* STATUS0 BIT MASK */
#define EFUSE_STATUS0_BUSY_MASK       (0x1UL << 0)
#define EFUSE_STATUS0_INIT_DONE_MASK  (0x1UL << 16)
#define EFUSE_STATUS0_PRG_FINISH_MASK (0x1UL << 16)

/* STATUS1 BIT MASK */
#define EFUSE_STATUS1_I_JTAG_DISABLE_MASK (0x1UL << 0)
#define EFUSE_STATUS1_I_RD_STATE_MASK     (0x7UL << 16)
#define EFUSE_STATUS1_I_PRG_STATE_MASK    (0xFUL << 24)

typedef struct efuse_ctrl_reg {
    volatile uint32_t EFUSE_CTRL;         /* Offset: 0x000 EFUSE CTRL Register */
    volatile uint32_t EFUSE_STATUS0;      /* Offset: 0x004 EFUSE STATUS0 Register */
    volatile uint32_t EFUSE_STATUS1;      /* Offset: 0x008 EFUSE STATUS1 Register */
    volatile uint32_t EFUSE_MARGIN_ADDR;  /* Offset: 0x00c EFUSE MARGIN Register */
    volatile uint32_t EFUSE_DATA;         /* Offset: 0x010 EFUSE DATA Register */
    volatile uint32_t EFUSE_O_SP_PD_PS;   /* Offset: 0x014 EFUSE O_SP_PD_PS Register */
    volatile uint32_t EFUSE_O_SP_PS_CSB;  /* Offset: 0x018 EFUSE O_SP_PS_CSB Register */
    volatile uint32_t EFUSE_O_SP_CSB_SB;  /* Offset: 0x01c EFUSE O_SP_CSB_SB Register */
    volatile uint32_t EFUSE_O_TPP;        /* Offset: 0x020 EFUSE O_TPP Register */
    volatile uint32_t EFUSE_O_TPI;        /* Offset: 0x024 EFUSE O_TPI Register */
    volatile uint32_t EFUSE_O_HP_CSB_SB;  /* Offset: 0x028 EFUSE O_HP_CSB_SB Register */
    volatile uint32_t EFUSE_O_HP_PS_CSB;  /* Offset: 0x02c EFUSE O_HP_PS_CSB Register */
    volatile uint32_t EFUSE_O_HP_PD_PS;   /* Offset: 0x030 EFUSE O_HP_PD_PS Register */
    volatile uint32_t EFUSE_O_HP_A;       /* Offset: 0x034 EFUSE O_HP_A Register */
    volatile uint32_t EFUSE_O_SR_PD_CSB;  /* Offset: 0x038 EFUSE O_SR_PD_CSB Register */
    volatile uint32_t EFUSE_O_SR_CSB_SB;  /* Offset: 0x03c EFUSE O_SR_CSB_SB Register */
    volatile uint32_t EFUSE_O_RD;         /* Offset: 0x040 EFUSE O_RD Register */
    volatile uint32_t EFUSE_O_HR_A_SB;    /* Offset: 0x044 EFUSE O_HR_A_SB Register */
    volatile uint32_t EFUSE_O_HR_CSB_SB;  /* Offset: 0x048 EFUSE O_HR_CSB_SB Register */
    volatile uint32_t EFUSE_O_HR_PD_CSB;  /* Offset: 0x04c EFUSE O_HR_PD_CSB Register */
    volatile uint32_t EFUSE_O_SR_A_SB_HR; /* Offset: 0x050 EFUSE O_SR_A_SB_HR Register */
    volatile uint32_t EFUSE_INT;          /* Offset: 0x054 (R)    EFUSE INTERRUPT Register */
    volatile uint32_t EFUSE_SKE_CTL;      /* Offset: 0x058 (R)    EFUSE SKE CONTROL Register */
} efuse_reg_t;

#ifdef __cplusplus
}
#endif
#endif

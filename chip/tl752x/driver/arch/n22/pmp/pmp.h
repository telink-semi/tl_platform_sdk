/*******************************************************************************************************
 *
 * @file    pmp.h
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
#if defined(MCU_CORE_TL752X_N22)

#ifndef __PMP_H__
#define __PMP_H__

#define PMP_CFG_R_ACCESS_ALLOWED     1
#define PMP_CFG_R_ACCESS_NOT_ALLOWED 0
#define PMP_CFG_W_ACCESS_ALLOWED     1
#define PMP_CFG_W_ACCESS_NOT_ALLOWED 0
#define PMP_CFG_X_ACCESS_ALLOWED     1
#define PMP_CFG_X_ACCESS_NOT_ALLOWED 0
#define PMP_CFG_A_OFF                0
#define PMP_CFG_A_NAT4BYTE           2
#define PMP_CFG_A_NAPOT              3
#define PMP_CFG_L_MODE0              0
#define PMP_CFG_L_MODE1              1

#define PMP_CFG_R_SET(val)         ((val & 0x01) << 0)
#define PMP_CFG_W_SET(val)         ((val & 0x01) << 1)
#define PMP_CFG_X_SET(val)         ((val & 0x01) << 2)
#define PMP_CFG_A_SET(val)         ((val & 0x03) << 3)
#define PMP_CFG_L_SET(val)         ((val & 0x01) << 7)
#define PMP_CFG_VAL(R, W, X, A, L) (PMP_CFG_R_SET(R) | PMP_CFG_W_SET(W) | PMP_CFG_X_SET(X) | PMP_CFG_A_SET(A) | PMP_CFG_L_SET(L))

#define PMP_NAT4BYTE(addr)               (addr >> 2)

//size = 2 << (bit_len + 2)
#define PMP_NAPOT(addr, size)  ((((addr) >> 2) & (~((size)-1))) | ((((size) - 1) >> 1)))

typedef enum {
    PMP_NOP_8BYTE = (2UL << 0),
    PMP_NOP_16BYTE = (2UL << 1),
    PMP_NOP_32BYTE = (2UL << 2),
    PMP_NOP_64BYTE = (2UL << 3),
    PMP_NOP_128BYTE = (2UL << 4),
    PMP_NOP_256BYTE = (2UL << 5),
    PMP_NOP_512BYTE = (2UL << 6),
    PMP_NOP_1KBYTE = (2UL << 7),
    PMP_NOP_2KBYTE = (2UL << 8),
    PMP_NOP_4KBYTE = (2UL << 9),
    PMP_NOP_8KBYTE = (2UL << 10),
    PMP_NOP_16KBYTE = (2UL << 11),
    PMP_NOP_32KBYTE = (2UL << 12),
    PMP_NOP_64KBYTE = (2UL << 13),
    PMP_NOP_128KBYTE = (2UL << 14),
    PMP_NOP_256KBYTE = (2UL << 15),
    PMP_NOP_512KBYTE = (2UL << 16),
    PMP_NOP_1MBYTE = (2UL << 17),
    PMP_NOP_2MBYTE = (2UL << 18),
    PMP_NOP_4MBYTE = (2UL << 19),
    PMP_NOP_8MBYTE = (2UL << 20),
    PMP_NOP_16MBYTE = (2UL << 21),
    PMP_NOP_32MBYTE = (2UL << 22),
    PMP_NOP_64MBYTE = (2UL << 23),
    PMP_NOP_128MBYTE = (2UL << 24),
    PMP_NOP_256MBYTE = (2UL << 25),
    PMP_NOP_512MBYTE = (2UL << 26),
    PMP_NOP_1GBYTE = (2UL << 27),
    PMP_NOP_2GMBYTE = (2UL << 28),
    PMP_NOP_4GMBYTE = (2UL << 29),
} pmp_nop_size_t;

typedef enum {
    PMP_ENTYR0 = 0,
    PMP_ENTYR1,
    PMP_ENTYR2,
    PMP_ENTYR3,
    PMP_ENTYR4,
    PMP_ENTYR5,
    PMP_ENTYR6,
    PMP_ENTYR7,
    PMP_ENTYR8,
    PMP_ENTYR9,
    PMP_ENTYR10,
    PMP_ENTYR11,
    PMP_ENTYR12,
    PMP_ENTYR13,
    PMP_ENTYR14,
    PMP_ENTYR15,
} pmp_entry_t;

/**
 * @description: pmp config entry
 * @param {pmp_entry_t} entry
 * @param {unsigned int} val
 * @param {unsigned int} addr
 * @return {int} -1 is invalid, 0 is valid
 */
extern int pmp_config_entry(pmp_entry_t entry, unsigned int val, unsigned int addr);

/**
 * @description: reset all entry
 * @param {none}
 * @return {int} -1 is invalid, 0 is valid
 */
extern int pmp_config_entry_reset_all(void);

/**
 * @description: reset one entry
 * @param {none}
 * @return {int} -1 is invalid, 0 is valid
 */
int pmp_config_entry_reset(pmp_entry_t entry);

#endif
#endif

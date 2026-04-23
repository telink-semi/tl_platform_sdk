/*******************************************************************************************************
 *
 * @file    tl_chip.h
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
#ifndef __TL_CHIP_H__
#define __TL_CHIP_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

/* register operation interfaces*/
#define SET_PROTECT_BIT(REG, BIT)           ((REG) = (BIT) | ((BIT) << 16))
#define CLEAR_PROTECT_BIT(REG, BIT)         ((REG) = ((BIT) << 16))
#define SET_BIT(REG, BIT)                   ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)                 ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)                  ((REG) & (BIT))
#define CLEAR_REG(REG)                      ((REG) = (0x0))
#define WRITE_REG(REG, VAL)                 ((REG) = (VAL))
#define READ_REG(REG)                       ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define DRV_MAX_DELAY 0xFFFFFFFFU
#define DRV_IM        volatile const
#define DRV_IOM       volatile
#define DRV_INLNE     inline
#define __NOP()       __asm__("nop")

#ifndef DRV_BIT
//lint -emacro(835, BIT) '<<0'
#define DRV_BIT(x) (1u << (x))
#endif

#define __DRV_LOCK(__HANDLE__)                  \
    do {                                        \
        if ((__HANDLE__)->lock == DRV_LOCKED) { \
            return DRV_BUSY;                    \
        } else {                                \
            (__HANDLE__)->lock = DRV_LOCKED;    \
        }                                       \
    } while (0U)

#define __DRV_UNLOCK(__HANDLE__)           \
    do {                                   \
        (__HANDLE__)->lock = DRV_UNLOCKED; \
    } while (0U)

typedef enum {
    DRV_OK = 0x00U,
    DRV_ERROR = 0x01U,
    DRV_BUSY = 0x02U,
    DRV_TIMEOUT = 0x03U
} drv_status_t;

typedef enum {
    DRV_UNLOCKED = 0x00U,
    DRV_LOCKED = 0x01U
} drv_lock_t;

typedef enum {
    DRV_RESET = 0U,
    DRV_SET = !DRV_RESET
} drv_flag_status_t;

/* calculate the greatest dicisior */
static DRV_INLNE int drv_gcd(int a, int b)
{
    int r;
    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

#include "tl752x.h"

#ifdef __cplusplus
}
#endif

#endif

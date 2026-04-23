/*******************************************************************************************************
 *
 * @file    trng.h
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
#ifndef __TRNG_H__
#define __TRNG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"

//TRNG_CR offsetaddress : 0x0
#define TRNG_RNG_EN_POS                   (0U)
#define TRNG_RNG_EN_MSK                   (0x1UL << TRNG_RNG_EN_POS)
#define TRNG_RNG_EN                       TRNG_RNG_EN_MSK
#define TRNG_RNG_EN_W(val)                (val << TRNG_RNG_EN_POS)

#define TRNG_ROS_EN_POS                   (4U)
#define TRNG_ROS_EN_MSK                   (0xfUL << TRNG_ROS_EN_POS)
#define TRNG_ROS_EN                       TRNG_ROS_EN_MSK
#define TRNG_ROS_EN_W(val)                (val << TRNG_ROS_EN_POS)

#define TRNG_DI_EN_POS                   (16U)
#define TRNG_DI_EN_MSK                   (0x1UL << TRNG_DI_EN_POS)
#define TRNG_DI_EN                       TRNG_DI_EN_MSK
#define TRNG_DI_EN_W(val)                (val << TRNG_DI_EN_POS)

#define TRNG_ERI_EN_POS                  (17U)
#define TRNG_ERI_EN_MSK                  (0x1UL << TRNG_ERI_EN_POS)
#define TRNG_ERI_EN                      TRNG_ERI_EN_MSK
#define TRNG_ERI_EN_W(val)               (val << TRNG_ERI_EN_POS)

#define TRNG_IRQ_EN_POS                  (24U)
#define TRNG_IRQ_EN_MSK                  (0x1UL << TRNG_IRQ_EN_POS)
#define TRNG_IRQ_EN                      TRNG_IRQ_EN_MSK
#define TRNG_IRQ_EN_W(val)               (val << TRNG_IRQ_EN_POS)

//TRNG_MSEL offsetaddress : 0x04
#define TRNG_MSEL_DEF_POS                (0U)
#define TRNG_MSEL_DEF_MSK                (0x1UL << TRNG_MSEL_DEF_POS)
#define TRNG_MSEL_DEF                    TRNG_MSEL_DEF_MSK
#define TRNG_MSEL_DEF_W(val)             (val << TRNG_MSEL_DEF_POS)

//TRNG_SR offsetaddress : 0x08
#define TRNG_ERERR_POS                   (2U)
#define TRNG_ERERR_MSK                   (0x1UL << TRNG_ERERR_POS)
#define TRNG_ERERR                       TRNG_ERERR_MSK
#define TRNG_ERERR_W(val)                (val << TRNG_ERERR_POS)

#define TRNG_DRDY_POS                    (1U)
#define TRNG_DRDY_MSK                    (0x1UL << TRNG_DRDY_POS)
#define TRNG_DRDY                        TRNG_DRDY_MSK
#define TRNG_DRDY_W(val)                 (val << TRNG_DRDY_POS)

#define TRNG_HTF_POS                     (0U)
#define TRNG_HTF_MSK                     (0x1UL << TRNG_HTF_POS)
#define TRNG_HTF                         TRNG_HTF_MSK
#define TRNG_HTF_W(val)                  (val << TRNG_HTF_POS)

//SCLK_FREQ offsetaddress : 0x88
#define TRNG_FSEL_POS                    (0U)
#define TRNG_FSEL_MSK                    (0x3UL << TRNG_FSEL_POS)
#define TRNG_FSEL                        TRNG_FSEL_MSK
#define TRNG_FSEL_W(val)                 (val << TRNG_FSEL_POS)


//TERO_CR offsetaddress : 0xB0
#define TRNG_TERO_EN_POS                 (0U)
#define TRNG_TERO_EN_MSK                 (0x1UL << TRNG_TERO_EN_POS)
#define TRNG_TERO_EN                     TRNG_TERO_EN_MSK
#define TRNG_TERO_EN_W(val)              (val << TRNG_TERO_EN_POS)

//TERO_SR offsetaddress : 0xD0
#define TRNG_TERO_DR_POS                 (0U)
#define TRNG_TERO_DR_MSK                 (0x1UL << TRNG_TERO_DR_POS)
#define TRNG_TERO_DR                     TRNG_TERO_DR_MSK
#define TRNG_TERO_DR_W(val)              (val << TRNG_TERO_DR_POS)

typedef struct {
    DRV_IOM uint32_t TRNG_CR;                        /* offset 0x000 */
    DRV_IOM uint32_t TRNG_MSEL;                      /* offset 0x004 */
    DRV_IOM uint32_t TRNG_SR;                        /* offset 0x008 */
    DRV_IOM uint32_t TRNG_DR;                        /* offset 0x00c */
    DRV_IOM uint32_t TRNG_VERSION;                   /* offset 0x010 */
    DRV_IOM uint32_t rev_0[(0x040 - 0x010) / 4 - 1]; /* offset 0x040-0x010 */
    DRV_IOM uint32_t TRNG_RESEED;                    /* offset 0x040 */
    DRV_IOM uint32_t rev_1[(0x060 - 0x040) / 4 - 1];
    DRV_IOM uint32_t TRNG_HT_CR; /* offset 0x060 */
    DRV_IOM uint32_t rev_2[(0x070 - 0x060) / 4 - 1];
    DRV_IOM uint32_t TRNG_HT_SR; /* offset 0x070 */
    DRV_IOM uint32_t rev_3[(0x080 - 0x070) / 4 - 1];
    DRV_IOM uint32_t RO_SRC_EN1; /* offset 0x080 */
    DRV_IOM uint32_t RO_SRC_EN2; /* offset 0x084 */
    DRV_IOM uint32_t SCLK_FREQ;  /* offset 0x088 */
    DRV_IOM uint32_t rev_4[(0x0B0 - 0x088) / 4 - 1];
    DRV_IOM uint32_t TERO_CR;    /* offset 0x0B0 */
    DRV_IOM uint32_t TERO_THOLD; /* offset 0x0B4 */
    DRV_IOM uint32_t rev_5[(0x0C0 - 0x0B4) / 4 - 1];
    DRV_IOM uint32_t TERO_CNT; /* offset 0x0C0 */
    DRV_IOM uint32_t rev_6[(0x0D0 - 0x0C0) / 4 - 1];
    DRV_IOM uint32_t TERO_SR; /* offset 0x0D0 */
    DRV_IOM uint32_t TERO_DR; /* offset 0x0D4 */
    DRV_IOM uint32_t rev_7[(0x0E0 - 0x0D4) / 4 - 1];
    DRV_IOM uint32_t TERO_RCR; /* offset 0x0E0 */
    DRV_IOM uint32_t rev_8[(0x0FC - 0x0E0) / 4 - 1];
} trng_reg_t;

#ifdef __cplusplus
}
#endif

#endif
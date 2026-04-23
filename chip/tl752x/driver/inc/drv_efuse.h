/*******************************************************************************************************
 *
 * @file    drv_efuse.h
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
#ifndef __DRV_EFUSE_H__
#define __DRV_EFUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "reg/efuse.h"
#include "tl_chip.h"

typedef enum {
    EFUSE_USER_REGION0 = 0,
    EFUSE_USER_REGION1 = 1,
    EFUSE_USER_REGION2 = 2,
    EFUSE_USER_REGION3 = 3,
    EFUSE_USER_REGION4 = 4,
    EFUSE_USER_REGION5 = 5,
    EFUSE_USER_REGION6 = 6,
    EFUSE_USER_REGION7 = 7,
    EFUSE_USER_REGION8 = 8,
    EFUSE_USER_REGION9 = 9,
    EFUSE_USER_REGION10 = 10,
    EFUSE_USER_REGION11 = 11,
    EFUSE_USER_REGION12 = 12,
    EFUSE_USER_REGION13 = 13,
    EFUSE_USER_REGION14 = 14,
    EFUSE_USER_REGION15 = 15,
    EFUSE_USER_REGION16 = 16,
    EFUSE_USER_REGION17 = 17,
    EFUSE_USER_REGION18 = 18,
    EFUSE_USER_REGION19 = 19,
    EFUSE_TRIM0 = 20,
    EFUSE_TRIM1 = 21,
    EFUSE_TRIM2 = 22,
    EFUSE_TRIM3 = 23,
    EFUSE_KR0 = 24,
    EFUSE_KR1 = 25,
    EFUSE_KR2 = 26,
    EFUSE_KR3 = 27,
    EFUSE_CHIP_ID = 28,
    EFUSE_TEST_KEY = 29,
    EFUSE_FUNC_INFO = 30,
    EFUSE_PROTECTION = 31,
    EFUSE_REGION_MAX,
} efuse_region_t;

/**
 * @brief  efuse read
 * @param  hipcm: Pointer to a efuse_reg_t structure
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_efuse_read(efuse_reg_t *efuse_ptr, efuse_region_t mem_addr, uint32_t *val);

/**
 * @brief  efuse set bit
 * @param  hipcm: Pointer to a efuse_reg_t structure
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_efuse_set_bit(efuse_reg_t *efuse_ptr, efuse_region_t mem_addr, uint32_t bit);

/**
 * @brief  efuse set region
 * @param  hipcm: Pointer to a efuse_reg_t structure
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_efuse_set_region(efuse_reg_t *efuse_ptr, efuse_region_t mem_addr, uint32_t val);

/**
 * @brief  efuse init
 * @param  efuse_ptr: Pointer to a efuse_reg_t structure
 * @param  apb2_fraq: apb2 bus freq
 * @return drv_status_t
 * @note   none
 */
extern void drv_efuse_init(efuse_reg_t *efuse_ptr, uint32_t apb2_fraq);

#ifdef __cplusplus
}
#endif

#endif
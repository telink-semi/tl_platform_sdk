/*******************************************************************************************************
 *
 * @file    drv_nor_flash.h
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
/*
 * @FilePath: \tx232_driver_src\driver\inc\drf_nor_flash.h
 * @Version: V1.0.1
 * @Date: 2025-07-04 12:08:57
 * @Author: driver group
 * @Description: nor flash driver
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __DRV_NOR_FLASH_H__
#define __DRV_NOR_FLASH_H__
#include <stdbool.h>
#include <stdint.h>
#include "tl_chip.h"
#include "inc/drv_dwc_ssi.h"
#ifdef __cplusplus
extern "C" {
#endif

#define FLASH_OTP_DEBUG 0

/**
 * @brief     flash status type definition
 */
typedef enum
{
    FLASH_TYPE_8BIT_STATUS          = 0,
    FLASH_TYPE_16BIT_STATUS_ONE_CMD = 1,
    FLASH_TYPE_16BIT_STATUS_TWO_CMD = 2,
} flash_status_typedef_e;

enum {
    NOR_WRAP_AROUND_NONE,
    NOR_WARP_LENGTH_8BIT,
    NOR_WARP_LENGTH_16BIT,
    NOR_WARP_LENGTH_32BIT,
    NOR_WARP_LENGTH_64BIT,
};

#define ID5(_jedec_id, _ext_id)     \
    .id = {                         \
        ((_jedec_id) >> 16) & 0xff, \
        ((_jedec_id) >> 8) & 0xff,  \
        ((_jedec_id) >> 0) & 0xff,  \
        ((_ext_id) >> 8) & 0xff,    \
        ((_ext_id) >> 0) & 0xff,    \
    },                              \
    .id_len = ((_ext_id) ? 5 : 3)

#define __FLASH(_name, _jedec_id, _block_size, _n_blocks, _status_type) .name = _name, ID5(_jedec_id, 0), .block_size = _block_size, .n_blocks = (_n_blocks), .page_size = 256, .status_type = _status_type

typedef struct {
    char name[12];
    uint8_t id[5];
    uint8_t id_len;
    uint32_t block_size;
    uint16_t n_blocks;
    uint16_t page_size;
    flash_status_typedef_e status_type;
} spi_nor_info_t;

typedef struct {
    uint32_t wrap_param;
} nor_flash_dev_init_t;

typedef struct __nor_flash_dev_t {
    nor_flash_dev_init_t init;
    const spi_nor_info_t *info;
    dwc_ssi_handle_t *dwc_ssi;
    drv_status_t (*read_jedec_id)(struct __nor_flash_dev_t *, uint8_t *);
    drv_status_t (*read_data)(struct __nor_flash_dev_t *, uint32_t, uint8_t *, uint32_t);
    drv_status_t (*fast_read_data)(struct __nor_flash_dev_t *, uint32_t, uint8_t *, uint32_t);
    drv_status_t (*page_pragram)(struct __nor_flash_dev_t *, uint32_t, uint8_t *, uint32_t);
    drv_status_t (*chip_erase)(struct __nor_flash_dev_t *);
    drv_status_t (*block_erase)(struct __nor_flash_dev_t *, uint32_t);
    drv_status_t (*sector_erase)(struct __nor_flash_dev_t *, uint32_t);
} nor_flash_dev_t;

extern void drv_nor_init(nor_flash_dev_t *flash);
extern void drv_nor_deinit(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_read_jedec_id(nor_flash_dev_t *flash, uint8_t *id);
extern drv_status_t drv_nor_read_uid(nor_flash_dev_t *flash, uint8_t *uid);
extern drv_status_t drv_nor_read_sr0(nor_flash_dev_t *flash, uint8_t *sr);
extern drv_status_t drv_nor_read_sr1(nor_flash_dev_t *flash, uint8_t *sr);
extern drv_status_t drv_nor_read_data(nor_flash_dev_t *flash, uint32_t addr, uint8_t *ptr, uint32_t size);
extern drv_status_t drv_nor_fast_read_quad_output(nor_flash_dev_t *flash, uint32_t addr, uint8_t *ptr, uint32_t size);
extern drv_status_t drv_nor_page_program(nor_flash_dev_t *flash, uint32_t addr, uint8_t *ptr, uint32_t page_size);
extern drv_status_t drv_nor_chip_erase(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_block_erase(nor_flash_dev_t *flash, uint32_t addr);
extern drv_status_t drv_nor_sector_erase(nor_flash_dev_t *flash, uint32_t addr);
extern drv_status_t drv_nor_block64_erase(nor_flash_dev_t *flash, uint32_t addr);
extern drv_status_t drv_nor_deep_power_down(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_release_deep_power_down(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_set_wrap(nor_flash_dev_t *flash, uint8_t wrap);
extern drv_status_t drv_nor_enable_quad(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_disable_quad(nor_flash_dev_t *flash);
extern bool drv_nor_checkout_quad(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_reset_sr0(nor_flash_dev_t *flash);
extern drv_status_t drv_nor_write_sr0(nor_flash_dev_t *flash, uint8_t* data_ptr);
extern drv_status_t drv_nor_write_sr1(nor_flash_dev_t *flash, uint8_t* data_ptr);
extern drv_status_t drv_nor_write_sr(nor_flash_dev_t *flash, uint8_t* data_ptr);
#if FLASH_OTP_DEBUG
extern drv_status_t drv_nor_read_otp(nor_flash_dev_t *flash, uint32_t addr, uint8_t *ptr, uint32_t size);
extern drv_status_t drv_nor_write_otp(nor_flash_dev_t *flash, uint32_t addr, uint8_t *ptr, uint32_t page_size);
extern drv_status_t drv_nor_erase_otp(nor_flash_dev_t *flash, uint32_t addr);
#endif
extern drv_status_t drv_nor_read_configure(nor_flash_dev_t *flash, uint8_t *sr);
extern drv_status_t drv_nor_write_configure(nor_flash_dev_t *flash, uint8_t* data_ptr);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_NOR_FLASH_H__ */

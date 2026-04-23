/********************************************************************************************************
 * @file    flash_common.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef __FLASH_COMMON_H__
#define __FLASH_COMMON_H__
#include "flash_type.h"
typedef unsigned char (*flash_write_status_fp)(unsigned short, unsigned int);
typedef unsigned char (*flash_lock_fp)(unsigned int);
typedef unsigned char (*flash_unlock_fp)(void);
typedef unsigned int (*flash_get_lock_block_fp)(void);

typedef struct
{
    unsigned int mid;
    //flash_protect
    flash_get_lock_block_fp get_lock;
    flash_unlock_fp         unlock;
    flash_lock_fp           lock_func;
    unsigned int            lock_size;
    //flash qe enable(4line)
    flash_write_status_fp flash_write_status;
    unsigned int          flash_qe_mask;
    unsigned short        qe_en;
    unsigned short        qe_dis;
} flash_hal_handler_t;

typedef struct
{
    unsigned int mid;
    unsigned int block_size;
} flash_user_defined_list_t;

typedef struct
{
    flash_user_defined_list_t *list;
    unsigned int               flash_cnt;
} flash_hal_user_handler_t;

#endif

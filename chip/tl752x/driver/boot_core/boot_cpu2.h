/*******************************************************************************************************
 *
 * @file    boot_cpu2.h
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
#ifndef __BOOT_CPU2_H__
#define __BOOT_CPU2_H__

typedef struct {
    unsigned int base_addr;
    unsigned int offset;
    const unsigned int *data;
    unsigned int len;
} cpu2_section_t;

/**
 * @description: boot CPU2
 * @param {unsigned int} iram_start_addr
 * @param {unsigned int} iram_len, for CPU2
 * @param {unsigned int} dram_start_addr
 * @param {unsigned int} dram_len, for CPU2
 * @return {none}
 */
void boot_cpu2_with_image(unsigned char *iram_addr, unsigned int iram_len, unsigned char *dram_addr, unsigned int dram_len);

/**
 * @description: boot CPU2
 * @param {unsigned int} iram_src_addr
 * @param {unsigned int} dram_src_addr
 * @return {none}
 */
void boot_cpu2(unsigned int iram_src_addr, unsigned int dram_src_addr);

/**
 * @description: poweroff CPU2
 * @return {none}
 */
void boot_cpu2_power_off(void);

#endif

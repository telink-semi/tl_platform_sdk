/*******************************************************************************************************
 *
 * @file    boot_cpu1.h
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
#ifndef __BOOT_CPU1_H__
#define __BOOT_CPU1_H__

/**
 * @description: md_boot_CPU1_with_image
 * @param {unsigned char*} src_ptr
 * @param {unsigned int} len
 * @return {none}
 */
void boot_cpu1_with_image(unsigned char *src_ptr, unsigned int len);

/**
 * @description: md_boot_CPU1
 * @param {unsigned int} start_addr, in flash
 * @param {unsigned int} len, for CPU1
 * @return {none}
 */
void boot_cpu1(unsigned int start_addr, unsigned int len);

#endif

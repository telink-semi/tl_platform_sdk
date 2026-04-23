/********************************************************************************************************
 * @file    flash_work_voltage_test.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "common.h"

#if DEMO_MODE == FLASH_WORK_VOLTAGE_TEST

unsigned char test_buf[4096] = {0};
void user_init(void)
{
    delay_ms(1);
    for (unsigned char i = 0; i < 3; i++) {
        flash_erase_sector(0x0000 + 4096 * i);
        delay_ms(1);
        flash_write_page(0x0000 + 4096 * i, 4095, (unsigned char *)test_buf);
        delay_ms(1);
        flash_read_page(0x0000 + 4096 * i, 4095, (unsigned char *)test_buf);
        delay_ms(1);
    }
}

void main_loop(void)
{
    delay_ms(500);
}

#endif


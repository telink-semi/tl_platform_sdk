/********************************************************************************************************
 * @file    app_hts221.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "../device/hts221.h"
#include "common.h"

#if (EXAMPLE_SELECT == EXAMPLE_HTS221)

volatile uint8_t i2c_rx_buff[32] __attribute__((aligned(4)));

void user_init(void)
{
    board_gpio_init();
    board_iic_init();
    WAIT_OK(hts221_iic_init());
}

volatile uint32_t AAAAA1 = 0;
volatile uint32_t AAAAA2 = 0;

_attribute_ram_code_sec_noinline_ void main_loop(void)
{
    if (0 == gpio_get_level(SW4)) {
        delay_ms(20);
        if (0 == gpio_get_level(SW4)) {
            gpio_toggle(D1);
            while (0 == gpio_get_level(SW4));
        }
    }
    delay_ms(1);
    if (AAAAA1++ == 500) {
        AAAAA1 = 0;
        AAAAA2++;
        hts221_iic_get_data();
    }
}

#endif

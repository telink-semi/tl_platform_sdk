/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
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

_attribute_nvm_rodata_sec_ unsigned int g_nvm_rodata = 0x11223344;
_attribute_nvm_rwdata_nocopy_sec_ unsigned int g_nvm_nocopy_data = 0x55667788;
_attribute_nvm_rwdata_copy_sec_ unsigned int g_nvm_copy_data = 0x99aabbcc;
_attribute_nvm_rwdata_copy_sec_ unsigned int g_nvm_copy_data_cnt = 0;

_attribute_nvm_code_sec_ void nvm_inline_function(void)
{
    printf("nvm inline function\r\n");
}

_attribute_nvm_code_sec_noinline_ void nvm_noinline_function(void)
{
    printf("nvm no inline function\r\n");
}

void nvm_test(void)
{
    if (g_nvm_rodata == 0x11223344)
    {
        printf("g_nvm_rodata is correct\r\n");
    }
    else
    {
        printf("g_nvm_rodata is error\r\n");
    }

    if (g_nvm_nocopy_data == 0x55667788)
    {
        printf("g_nvm_nocopy_data is correct\r\n");
    }
    else
    {
        printf("g_nvm_nocopy_data is error\r\n");
    }

    if (g_nvm_copy_data == 0x99aabbcc)
    {
        printf("g_nvm_copy_data is correct\r\n");
    }
    else
    {
        printf("g_nvm_copy_data is error expect 0x99aabbcc, actual 0x%x, data address 0x%p\r\n", g_nvm_copy_data, &g_nvm_copy_data);
    }

    printf("nvm function test\r\n");
    nvm_inline_function();
    nvm_noinline_function();
    printf("nvm function test end\r\n");
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    nvm_test();
}

void main_loop(void)
{
    delay_ms(500);
    printf(" Hello world! \n");
    g_nvm_copy_data_cnt++;
}

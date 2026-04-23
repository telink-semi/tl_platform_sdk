/********************************************************************************************************
 * @file    tl_log_transport_uart.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#if defined(MCU_CORE_TL752X)

#include "modules/drv_arbiter.h"

//usr_puts is mostly provided by main.c for now.
extern void usr_puts(char *ptr, int len);

__attribute__((weak)) void _epm_log_transport_uart_write(void *data, uint32_t data_length)
{
    if (data == NULL || data_length == 0) {
        return;
    }

    while (!__DRV_ARBITER5_ID_LOG())
    ;

    usr_puts((char *)data, data_length);

    __DRV_CLEAR_ARBITER5_ID_LOG();


    return;
}


#endif

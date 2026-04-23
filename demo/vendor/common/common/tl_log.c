/********************************************************************************************************
 * @file    tl_log.c
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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "tl_chip.h"
#include "common.h"
#include "common.h"
#include "tl_log_transport.h"


void async_log_data_dump(const uint8_t *data, uint32_t bytes_num, const char *format)
{
    char buffer[512];
    int len = 0;
    
    // Format the message
    len = soc_sprintf(buffer, "%s", format);
    len += soc_sprintf(buffer + len, "\r\n");
    
    // Check if the data buffer is valid and has content
    if (data != NULL && bytes_num > 0) {
        for (uint32_t i = 0; i < bytes_num; i++) {
            len += soc_sprintf(buffer + len, "%02X", data[i]);
            if ((i + 1) % 8 == 0) {
                len += soc_sprintf(buffer + len, "\r\n");
            } else if (i < bytes_num - 1) {
                len += soc_sprintf(buffer + len, " ");
            }
        }
        if (bytes_num % 8 != 0) {
            len += soc_sprintf(buffer + len, "\r\n");
        }
    }
    
    _epm_log_transport_uart_write(buffer, len);
}

void async_log_dump(const char *format, int args_size, ...)
{
    int len;
    char buffer[256];
    va_list ap;
    va_start(ap, args_size);

    len = soc_vsprintf(buffer, format, ap);
    _epm_log_transport_uart_write (buffer, len);
    va_end(ap);

    return;
}

#endif

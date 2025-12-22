/********************************************************************************************************
 * @file    log.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#ifndef LOG_H
#define LOG_H

#include "common.h"
/*
 * Assert parameter validation
 */
#define ASSERT_EN 0
/*
 * Serial debug use PE0 Baudrate is 1Mbps 8/N/1
 * NOTE: serial debug will DISABLE INTERRUPT !!
 */
#define SERIAL_DBG_EN 0

#define UART0_TX_PIN  GPIO_FC_PD1
#define UART0_RX_PIN  GPIO_FC_PC4

int trace(const char *format, ...);

enum
{
    IO_PUT_CHAR_UART = 0,
    IO_PUT_CHAR_USB,
    IO_PUT_CHAR_RAM,
};

/* TRACE */
#if SERIAL_DBG_EN


#define PRINTK(...) trace(__VA_ARGS__)
#define LOG(...)                     \
    do {                             \
        PRINT("[INF]: "__VA_ARGS__); \
    } while (0)
#define LOG_ERR(...)                 \
    do {                             \
        PRINT("[ERR]: "__VA_ARGS__); \
    } while (0)
#define LOG_WAR(...)                 \
    do {                             \
        PRINT("[WAR]: "__VA_ARGS__); \
    } while (0)
#define DUMP_HEX(a, b) dump_hex_with_format(a, b, 16);

#else
#define PRINTK(...)
#define LOG(...)
#define LOG_ERR(...)
#define LOG_WAR(...)
#define DUMP_HEX(a, b)
#endif

#if ASSERT_EN
#define ASSERT(a)                                                    \
    do {                                                             \
        if (!a) {                                                    \
            LOG_ERR("ASSERT ERR %s, line %d\n", __FILE__, __LINE__); \
            while (1);                                               \
        }                                                            \
    } while (0);
#if SERIAL_DBG_EN
#define ASSERT_INFO(expression, para1, para2)                           \
    do {                                                                \
        if (!(expression))                                              \
            __assert_info(expression, para1, para2, __FILE__, __LINE__) \
    } while (0)

#define __assert_info(expression, para1, para2, file, lineno)                                     \
    {                                                                                             \
        trace(" para1:%d, para2: %d,%s:%u: assert_info failed!\r\n", para1, para2, file, lineno); \
    }

#define ASSERT_WARN(expression)                           \
    do {                                                  \
        if (!(expression))                                \
            __assert_warn(expression, __FILE__, __LINE__) \
    } while (0)

#define __assert_warn(expression, file, lineno)         \
    {                                                   \
        trace("%s:%u: assert warn!\r\n", file, lineno); \
    }
#else
#define ASSERT_INFO(expression, para1, para2)                           \
    do {                                                                \
        if (!(expression))                                              \
            __assert_info(expression, para1, para2, __FILE__, __LINE__) \
    } while (0)

#define __assert_info(expression, para1, para2, file, lineno)                                      \
    {                                                                                              \
        printf(" para1:%d, para2: %d,%s:%u: assert_info failed!\r\n", para1, para2, file, lineno); \
    }

#define ASSERT_WARN(expression)                           \
    do {                                                  \
        if (!(expression))                                \
            __assert_warn(expression, __FILE__, __LINE__) \
    } while (0)

#define __assert_warn(expression, file, lineno)          \
    {                                                    \
        printf("%s:%u: assert warn!\r\n", file, lineno); \
    }

#endif
#else
#define ASSERT(a)
#define ASSERT_INFO(ignore, para1, para2) ((void)0)
#define ASSERT_WARN(expression)           ((void)0)
#endif
void uart0_init(void);
void printk_write_callback(int io, void (*put)(int));
void trace_write(int c);
#endif

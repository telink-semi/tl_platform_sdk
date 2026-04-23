/********************************************************************************************************
 * @file    soc_printf.c
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
/*
 * @FilePath: \tx232_driver_src\components\soc_printf\soc_printf.c
 * @Version: V1.0.1
 * @Date: 2025-07-07 09:59:44
 * @Author: driver group
 * @Description:soc_printf
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "soc_printf.h"

const char std_str[] = "0123456789abcdef";
#define MAX_NUM 256

void change_num_uint(unsigned int val, char *out_str, unsigned int *p_count,
    unsigned int base, unsigned char width)
{
    unsigned int change_count = 0;
    char change_str[21] = "";
    char *p = &change_str[20];

    do {
        *p = std_str[val%base];
        p--;
        val /= base;
        change_count++;
    } while (val);

    if (width > change_count) {
        memset(&out_str[*p_count], '0', width - change_count);
        *p_count += width - change_count;
    }

    memcpy(&out_str[*p_count], &change_str[20-change_count + 1],
                    change_count);
    *p_count += change_count;
}

void change_num_int(int val, char *out_str, unsigned int *p_count,
    unsigned int base)
{
    if (val < 0) {
        /* avoid UB when val == INT_MIN */
        unsigned int u = (unsigned int)(-(long long)val);
        out_str[*p_count] = '-';
        (*p_count)++;
        change_num_uint(u, out_str, p_count, base, 0);
        return;
    }
    change_num_uint((unsigned int)val, out_str, p_count, base, 0);
}

void change_num_uint_ll(unsigned long long int val, char *out_str, unsigned int *p_count,
    unsigned int base)
{
    unsigned int change_count = 0;
    char change_str[21] = "";
    char *p = &change_str[20];

    do {
        *p = std_str[val%base];
        p--;
        val /= base;
        change_count++;
    }while (val);

    memcpy(&out_str[*p_count], &change_str[20-change_count + 1],
                    change_count);
    *p_count += change_count;
}

void change_num_int_ll(long long int val, char *out_str, unsigned int *p_count,
    unsigned int base)
{
    if (val < 0) {
        /* avoid UB when val == LLONG_MIN */
        unsigned long long u = (unsigned long long)(-(long long)val);
        out_str[*p_count] = '-';
        (*p_count)++;
        change_num_uint_ll(u, out_str, p_count, base);
        return;
    }
    change_num_uint_ll((unsigned long long)val, out_str, p_count, base);
}

void change_num_float(double val, char *out_str, unsigned int *p_count, unsigned int precision)
{
    if (val < 0) {
        out_str[*p_count] = '-';
        (*p_count)++;
        val = -val;
    }
    
    // Extract integer part
    unsigned int integer_part = (unsigned int)val;
    change_num_uint(integer_part, out_str, p_count, 10, 0);
    
    if (precision > 0) {
        out_str[*p_count] = '.';
        (*p_count)++;
        
        // Extract fractional part
        double fractional = val - integer_part;
        unsigned int multiplier = 1;
        for (unsigned int i = 0; i < precision; i++) {
            multiplier *= 10;
        }
        
        unsigned int frac_digits = (unsigned int)(fractional * multiplier + 0.5); // Round
        change_num_uint(frac_digits, out_str, p_count, 10, precision);
    }
}
extern void usr_puts(char *ptr, int len);
int soc_vsprintf(char *buffer, const char *str, va_list ap)
{
    char local_buf[MAX_NUM];
    /* use provided buffer if non-NULL, else local buffer */
    char *out_str = buffer ? buffer : local_buf;
    unsigned int count = 0;
    char *s = NULL;
    unsigned int s_len;
    unsigned char width = 0;

     while ('\0' != *str) {
        if (count >= (MAX_NUM - 25))
        {
            if (count < MAX_NUM - 1)
            {
                out_str[count++] = '\n';
            }
            break;
        }
        switch (*str) {
        case '%':
            str ++;
            switch (*str) {
            case 'o':
                change_num_int(va_arg(ap, int), out_str, &count, 8);
                break;
            case 'u':
                change_num_uint(va_arg(ap, unsigned int), out_str, &count, 10, 0);
                break;
            case 'd':
                change_num_int(va_arg(ap, int), out_str, &count, 10);
                break;
            case 'p':
                out_str[count++] = '0';
                out_str[count++] = 'x';
                change_num_uint(va_arg(ap, unsigned int), out_str, &count, 16, 0);
                break;
            case 'x':
                change_num_uint(va_arg(ap, unsigned int), out_str, &count, 16, 0);
                break;
            case 's':
                s = va_arg(ap, char*);
                if (!s) s = "(null)";
                s_len = strlen(s);
                if (count + s_len > MAX_NUM - 2)
                {
                    s_len = MAX_NUM - count - 2;
                }
                memcpy(&out_str[count], s, s_len);
                count += s_len;
                break;
            case '0':
                str ++;
                if ((*str >= '0') && *str <= '9') {
                    width = *str - '0';
                    str ++;
                    switch (*str) {
                    case 'u':
                        change_num_uint(va_arg(ap, unsigned int), out_str, &count, 10, width);
                        break;
                    case 'x':
                    case 'X':  // Add this line
                        change_num_uint(va_arg(ap, unsigned int), out_str, &count, 16, width);
                        break;
                    default :
                        if ((*str >= '0') && *str <= '9') {
                            width *= 10;
                            width += *str - '0';
                            str ++;
                            switch (*str) {
                            case 'u':
                                change_num_uint(va_arg(ap, unsigned int), out_str, &count, 10, width);
                                break;
                            case 'x':
                            case 'X':  // Add this line
                                change_num_uint(va_arg(ap, unsigned int), out_str, &count, 16, width);
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            case 'l':
                str++;
                if (*str == 'l') {
                    str++;
                    switch (*str) {
                    case 'x':
                        change_num_uint_ll(va_arg(ap, unsigned long long int), out_str, &count, 16);
                        break;
                    case 'd':
                        change_num_int_ll(va_arg(ap, long long int), out_str, &count, 10);
                        break;
                    case 'o':
                        change_num_int_ll(va_arg(ap, long long int), out_str, &count, 8);
                        break;
                    default:
                        break;
                    }
                }
                break;
            case '.':
                str++;
                if ((*str >= '0') && (*str <= '9')) {
                    unsigned int precision = *str - '0';
                    str++;
                    if (*str == 'f') {
                        change_num_float(va_arg(ap, double), out_str, &count, precision);
                    }
                }
                break;
            case 'f':
                change_num_float(va_arg(ap, double), out_str, &count, 6); // Default 6 decimal places
                break;
            case '%':
                out_str[count] = '%';
                count ++;
                break;
            default:
                break;
            }
            break;
        default:
            out_str[count] = *str;
            count++;
            break;
        }
        str ++;
    }
    if (count >= MAX_NUM) {
        count = MAX_NUM;
    }
    /* do not call usr_puts here: just return length and let caller decide */
    return (int)count;
}

int soc_vprintf(const char *str, va_list ap)
{
    char out_str[MAX_NUM];
    int count = soc_vsprintf(out_str, str, ap);
    if (count > 0)
        usr_puts(out_str, count);
    return count;
}

int soc_sprintf(char *buffer, const char *str, ...)
{
    va_list ap;
    int result;

    va_start(ap, str);
    result = soc_vsprintf(buffer, str, ap);
    va_end(ap);
    
    // Add null termination for sprintf compatibility
    if (buffer && result < MAX_NUM) {
        buffer[result] = '\0';
    }
    
    return result;
}

int soc_printf(const char *str, ...)
{
    va_list ap;
    int count;

    va_start(ap, str);
    count = soc_vprintf(str, ap);
    va_end(ap);
    return count;
}
#endif

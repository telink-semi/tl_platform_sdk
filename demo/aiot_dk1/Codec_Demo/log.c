/********************************************************************************************************
 * @file    log.c
 *
 * @brief   This is the source file for TL7518/TL721X/TL321X
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

#include "log.h"

#if SERIAL_DBG_EN

void uart0_init(void)
{
    unsigned short div  = 0;
    unsigned char  bwpc = 0;

    uart_set_pin(0, UART0_TX_PIN, UART0_RX_PIN);
    uart_cal_div_and_bwpc(1000000, sys_clk.pclk * 1000 * 1000, &div, &bwpc);
    uart_init(0, div, bwpc, UART_PARITY_NONE, UART_STOP_BIT_ONE);
    uart_tx_irq_trig_level(0, 0);
    uart_rx_irq_trig_level(0, 1);
    uart_set_irq_mask(0, UART_RX_IRQ_MASK | UART_ERR_IRQ_MASK);
    uart_set_rx_timeout_with_exp(0, bwpc, 12, UART_BW_MUL2, 0);
    uart_set_irq_mask(0, UART_RXDONE_MASK);
    plic_interrupt_enable(IRQ_UART0);
}

void trace_write(int c)
{
    uart_send_byte(0, (const char)c);
}

void (*putchar_callback[IO_PUT_CHAR_RAM])(int) = {NULL, NULL};

void printk_write_callback(int io, void (*put)(int))
{
    if (io > IO_PUT_CHAR_RAM) {
        return;
    }

    putchar_callback[io] = put;
}

static void printchar(int io, char **str, int c)
{
    if (str) {
        **str = c;
        ++(*str);
    } else {
        if (putchar_callback[io]) {
            putchar_callback[io](c);
        }
    }
}

#define PAD_RIGHT 1
#define PAD_ZERO  2

static int prints(int io, char **out, const char *string, int width, int pad)
{
    register int pc = 0, padchar = ' ';

    if (width > 0) {
        register int         len = 0;
        register const char *ptr;

        for (ptr = string; *ptr; ++ptr) {
            ++len;
        }

        if (len >= width) {
            width = 0;
        } else {
            width -= len;
        }

        if (pad & PAD_ZERO) {
            padchar = '0';
        }
    }

    if (!(pad & PAD_RIGHT)) {
        for (; width > 0; --width) {
            printchar(io, out, padchar);
            ++pc;
        }
    }

    for (; *string; ++string) {
        printchar(io, out, *string);
        ++pc;
    }

    for (; width > 0; --width) {
        printchar(io, out, padchar);
        ++pc;
    }

    return pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12

static int printi(int io, char **out, int i, int b, int sg, int width, int pad, int letbase)
{
    char                  print_buf[PRINT_BUF_LEN];
    register char        *s;
    register int          t, neg = 0, pc = 0;
    register unsigned int u = i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints(io, out, print_buf, width, pad);
    }

    if (sg && b == 10 && i < 0) {
        neg = 1;
        u   = -i;
    }

    s  = print_buf + PRINT_BUF_LEN - 1;
    *s = '\0';

    while (u) {
        t = u % b;

        if (t >= 10) {
            t += letbase - '0' - 10;
        }

        *--s = t + '0';
        u /= b;
    }

    if (neg) {
        if (width && (pad & PAD_ZERO)) {
            printchar(io, out, '-');
            ++pc;
            --width;
        } else {
            *--s = '-';
        }
    }

    return pc + prints(io, out, s, width, pad);
}

int print(int io, char **out, const char *format, va_list args)
{
    register int width, pad;
    register int pc = 0;
    char         scr[2];

    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            width = pad = 0;

            if (*format == '\0') {
                break;
            }

            if (*format == '%') {
                goto out;
            }

            if (*format == '-') {
                ++format;
                pad = PAD_RIGHT;
            }

            while (*format == '0') {
                ++format;
                pad |= PAD_ZERO;
            }

            for (; *format >= '0' && *format <= '9'; ++format) {
                width *= 10;
                width += *format - '0';
            }

            if (*format == 's') {
                register char *s = (char *)va_arg(args, int);
                pc += prints(io, out, s ? s : "(null)", width, pad);
                continue;
            }

            if (*format == 'd') {
                pc += printi(io, out, va_arg(args, int), 10, 1, width, pad, 'a');
                continue;
            }

            if (*format == 'x') {
                pc += printi(io, out, va_arg(args, int), 16, 0, width, pad, 'a');
                continue;
            }

            if (*format == 'X') {
                pc += printi(io, out, va_arg(args, int), 16, 0, width, pad, 'A');
                continue;
            }

            if (*format == 'u') {
                pc += printi(io, out, va_arg(args, int), 10, 0, width, pad, 'a');
                continue;
            }

            if (*format == 'c') {
                /* char are converted to int then pushed on the stack */
                scr[0] = (char)va_arg(args, int);
                scr[1] = '\0';
                pc += prints(io, out, scr, width, pad);
                continue;
            }
        } else {
out:
            printchar(io, out, *format);
            ++pc;
        }
    }

    if (out) {
        **out = '\0';
    }

    va_end(args);
    return pc;
}

int trace(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    return print(IO_PUT_CHAR_UART, 0, format, args);
}

void dump_hex_with_format(uint8_t *p_dat, int len, int number)
{
    int i, j;

    for (i = 0; i < len;) {
        trace("[%08x]: ", i);
        for (j = 0; j < number && i < len; j++, i++) {
            trace("%02x ", p_dat[i]);
        }
        trace("\r\n");
    }
    trace("\r\n");
}


#endif

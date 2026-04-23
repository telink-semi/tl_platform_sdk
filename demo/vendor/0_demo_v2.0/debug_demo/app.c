/********************************************************************************************************
 * @file    app.c
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
#include "common.h"
// log init
uart_handle_t uart_huart;

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_huart, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    uart_huart.instance = UART1;
    uart_huart.init.baudrate = 500000;
    uart_huart.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_huart.init.parity = UART_PARITY_NONE;
    uart_huart.init.stopbits = UART_STOPBITS_1;
    uart_huart.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_huart);
}
volatile unsigned char debug=0;

void user_init(void)
{
    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1
    LOG_INF("Debug Demo!\n");
}
void main_loop(void)
{
    debug++;
}


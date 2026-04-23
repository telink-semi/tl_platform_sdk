/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
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

/**************************** include header *********************************/
#include "common.h"
#include "inc/drv_cpr.h"
#include "inc/drv_uart.h"
#include "inc/drv_wdt.h"
#include "modules/drv_gpio.h"
#include "soc_printf.h"
#include "hal/hal_wdt.h"
#include "inc/drv_delay.h"
#include "hal/hal_systimer.h"

// log init
uart_handle_t uart_handle;

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
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

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}

void user_init(void)
{
    log_init();
    soc_printf("WDT SAMPLE!\r\n");

    wd_32k_init();
    wd_32k_set_interval_ms(2048);//Note: timeout_ms is a power of 2, and the exponent must be >= 11,such as 2048, 4096, 8192, etc.The actual reset time =2*timeout
    wd_32k_start();
    delay_ms(2000);
    wd_32k_clear();
    delay_ms(1000);
    soc_printf("32k wd cleared! \r\n");
    wd_32k_stop();
    soc_printf("32k wd stopped! \r\n");
}
void main_loop(void){

    soc_printf("%d ms \r\n", wd_32k_get_tick()/32);
    delay_ms(1000);
}

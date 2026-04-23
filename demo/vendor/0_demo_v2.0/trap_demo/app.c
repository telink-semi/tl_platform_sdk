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

#if (TRAP_DEMO == INTERRUPT_MTIME_DEMO)
void user_init(void)
{
    gpio_init_t gpio_init;

    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_2;
    gpio_init.mode = MODE_OUTPUT;
    gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&gpio_init);

    log_init();
    soc_printf("this is mtime demo\r\n");

    unsigned char trim;
    trim = drv_cal_32KRC();
    drv_cal_set_32KRC_trim(trim);
    mtime_clk_init();

    core_interrupt_enable();
    core_mie_enable(FLD_MIE_MTIE);
    mtime_set_interval_ms(500);
}

_attribute_ram_code_sec_ void mtime_irq_handler(void)
{
    mtime_set_interval_ms(1000);
    static gpio_pinstate_t pin_state = GPIO_PIN_SET;
    pin_state = !pin_state;
    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_2, pin_state);
}

void main_loop(void)
{

}
#else
void user_init(void)
{

}
void main_loop(void)
{

}
#endif

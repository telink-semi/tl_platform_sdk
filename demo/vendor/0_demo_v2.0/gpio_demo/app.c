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
#include <stdio.h>
#include <string.h>

#include "inc/drv_uart.h"
#include "hal/hal_gpio.h"
#include "common.h"

#include "tl_chip.h"

volatile int gpio_irq_flag = 0;
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
void GPIO_IRQHandler(void)
{
    if (gpio_get_irq_status(GPIO_PA2)) {
        gpio_set_low_level(GPIO_PA9);
        gpio_set_high_level(GPIO_PA9);
        gpio_clr_irq_status(GPIO_PA2);
    }
    if (gpio_get_irq_status(GPIO_PA3)) {
        gpio_set_low_level(GPIO_PA8);
        gpio_set_high_level(GPIO_PA8);
        gpio_clr_irq_status(GPIO_PA3);
    }

    if (gpio_get_irq_status(GPIO_PB5)) {
        gpio_set_low_level(GPIO_PA5);
        gpio_set_high_level(GPIO_PA5);
        gpio_clr_irq_status(GPIO_PB5);
    }
    if (gpio_get_irq_status(GPIO_PB6)) {
        gpio_set_low_level(GPIO_PA11);
        gpio_set_high_level(GPIO_PA11);
        gpio_clr_irq_status(GPIO_PB6);
    }
}

PLIC_ISR_REGISTER(GPIO_IRQHandler, GPIO_IRQn);

void user_init(void)
{
    log_init();
    gpio_function_en(GPIO_PA2);
    gpio_function_en(GPIO_PA3);
    gpio_function_en(GPIO_PA4);
    gpio_function_en(GPIO_PA5);
    gpio_function_en(GPIO_PA7);
    gpio_function_en(GPIO_PA6);
    gpio_function_en(GPIO_PA8);
    gpio_function_en(GPIO_PA9);
    gpio_function_en(GPIO_PA11);
    gpio_function_en(GPIO_PB5);
    gpio_function_en(GPIO_PB6);

    gpio_output_en(GPIO_PA8);
    gpio_output_en(GPIO_PA9);
    gpio_output_en(GPIO_PA4);
    gpio_output_en(GPIO_PA5);
    gpio_output_en(GPIO_PA11);
    gpio_input_en(GPIO_PA2);
    gpio_input_en(GPIO_PA3);
    gpio_input_en(GPIO_PB5);
    gpio_input_en(GPIO_PB6);
    gpio_input_en(GPIO_PA6);
    gpio_input_en(GPIO_PA7);

    gpio_set_up_down_res(GPIO_PA2,GPIO_PIN_PULLDOWN);
    gpio_set_up_down_res(GPIO_PA3,GPIO_PIN_PULLUP);
    gpio_set_up_down_res(GPIO_PA6,GPIO_PIN_PULLUP);
    gpio_set_up_down_res(GPIO_PA7,GPIO_PIN_PULLUP);
    gpio_set_up_down_res(GPIO_PB5,GPIO_PIN_PULLDOWN);
    gpio_set_up_down_res(GPIO_PB6,GPIO_PIN_PULLUP);


    gpio_set_irq(GPIO_PA2, GPIO_INTR_POSEDGE);
    gpio_set_irq(GPIO_PA3, GPIO_INTR_NEGEDGE);
    gpio_set_irq(GPIO_PB5, GPIO_INTR_POSEDGE);
    gpio_set_irq(GPIO_PB6, GPIO_INTR_NEGEDGE);
    gpio_irq_en();
}

void main_loop(void)
{
    gpio_toggle(GPIO_PA4);

   if(gpio_get_level(GPIO_PA6)){
       soc_printf("GPIO_PA6 toggle: %d\n", gpio_get_level(GPIO_PA6));
   }
   else{
       soc_printf("GPIO_PA6 toggle: %d\n", gpio_get_level(GPIO_PA6));
   }
   if(gpio_get_level(GPIO_PA7)){
       soc_printf("GPIO_PA7 toggle: %d\n", gpio_get_level(GPIO_PA7));
   }
   else{
       soc_printf("GPIO_PA7 toggle: %d\n", gpio_get_level(GPIO_PA7));
   }
}


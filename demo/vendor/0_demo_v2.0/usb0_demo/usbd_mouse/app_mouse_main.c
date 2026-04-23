/********************************************************************************************************
 * @file    app_mouse_main.c
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
/*
 * @FilePath: \epm_driver\demo\usb2.0\usbd_mouse\main.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb test code
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */
#include "common.h"
#if (USB_DEMO_TYPE == USB_MOUSE)
#include "usbd_mouse.h"

//log init
uart_handle_t log_uart;

uint32_t bsp_key_scan(void)
{
    static uint8_t key_release = 1;
    if (drv_gpio_readpin(GPIO_PORT_B, GPIO_PIN_3) == GPIO_PIN_RESET) {
        drv_delay_ms(10);
        if (drv_gpio_readpin(GPIO_PORT_B, GPIO_PIN_3) == GPIO_PIN_RESET) {
            if (key_release == 1) {
                key_release = 0;
                return USB_OK;
            } else {
                return USB_ERROR;
            }
        }
    } else {
        key_release = 1;
    }
    return USB_ERROR;
}

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&log_uart, (uint8_t *)ptr, len, DRV_MAX_DELAY);
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

    log_uart.instance = UART1;
    log_uart.init.baudrate = 500000;
    log_uart.init.hwflowctl = UART_HWCONTROL_NONE;
    log_uart.init.parity = UART_PARITY_NONE;
    log_uart.init.stopbits = UART_STOPBITS_1;
    log_uart.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&log_uart);
}

void user_init(void)
{
    /* init uart */
    log_init(); //uart1 used pa0 pa1

    core_interrupt_enable();

    soc_printf("usb device mouse sample start!\n");

    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_3;
    gpio_init.mode = MODE_INPUT;
    gpio_init.pull = GPIO_NOPULL;
    gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
    drv_gpio_init(&gpio_init);

    drv_delay_ms(100);
    usbd_mouse_init();
    while (usb_device_is_init() != 1) {
    }

    while (1) {
        if (bsp_key_scan() == USB_OK) {
            soc_printf("wake up test.\r\n");
            usbd_wakeup_host();
            extern uint8_t usb_test_flag;
            usb_test_flag = 1;
        }
        usbd_mouse_test();
    }
}

void main_loop(void)
{

}
#endif

/********************************************************************************************************
 * @file    app_audio_main.c
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
 * @FilePath: \epm_driver\demo\usb2.0\usbd_audio_hs_v2\main.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb test code
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header ********************************/
#include "common.h"
#if (USB_DEMO_TYPE == USB_MIC_SPK)
#include "app_audio.h"

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/************************* variable definition *******************************/
//log init
uart_handle_t log_uart;
uint8_t usb_test_flag;

/**************************** function declear *******************************/
extern void codec_dac_adc_init(void);
extern uint32_t audio_codec_adc_test(void);
extern uint32_t system_audio_play_test(void);

/********************** function implementation ******************************/
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
    cpr_mclk0_init_t mclk0_init;

    /* pll0 out  */
    drv_cpr_enable_bbpll();

    mclk0_init.source = DRV_CPR_MCLK0_SOURCE_DIVIDED_PLL;
    mclk0_init.freq = 192000000;
    mclk0_init.pll_sel = DRV_CPR_MCLK0_PLL_SEL_BBPLL;
    drv_cpr_config_mclk0(&mclk0_init);

    core_interrupt_enable();

    /* init uart */
    log_init(); //uart1 used pa0 pa1

    soc_printf("\r\n usbd_audio sample!\r\n");

    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.mode = MODE_OUTPUT;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
    drv_gpio_init(&gpio_init);

    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_0, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_0, GPIO_PIN_RESET);

    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_1, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_1, GPIO_PIN_RESET);

    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_2, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_2, GPIO_PIN_RESET);

    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_3, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_3, GPIO_PIN_RESET);

    codec_dac_adc_init();

    usbd_audio_init();
    while (usb_device_is_init() != 1)
        ;

    while (1) {
        //if (usb_test_flag)
        //{
        //    usb_test_flag = 0;
        //    uint8_t consumer[3];
        //    consumer[0] = 0x02; // consumer report id
        //    consumer[1] = 0x00;
        //    consumer[2] = 0x00;
        //    usbd_ep_tx(HID_IN_EP, consumer, 3);
        //}

        audio_codec_adc_test();
        system_audio_play_test();
    }
}

void main_loop(void)
{

}

#endif

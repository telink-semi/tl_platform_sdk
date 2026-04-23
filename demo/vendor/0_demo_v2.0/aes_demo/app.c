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
/*
 ============================================================================
 Name        : app.c
 Author      : knw
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, ANSI-style
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "common.h"

// log init
uart_handle_t uart_handle;

bt_aes_handle_t aes_handle;

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
    uint8_t in[16] = { 0xcc, 0xdd, 0xee, 0xff, 0x88, 0x99, 0xaa, 0xbb, 0x44, 0x55, 0x66, 0x77, 0x00, 0x11, 0x22, 0x33 };
    uint8_t out[16];
    SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_CFG_AHB_BUS_CLK_EN_MSK);

    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1

    soc_printf("bt aes demo\r\n");

    __DRV_PMU_CLK_EN_M_AO_SET(PMU_CPU1_SYSTEM_CLK_EN_MSK);

    SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_HCLK_EN | CPR_BT_SYS_CLK_EN);
    SET_BIT(CPR->BT_CFG, CPR_BT_SYS_CPU_DM_GCLKEN | CPR_BT_SYS_CPU_EM_GCLKEN);
    aes_handle.key[0] = 0x23456789;
    aes_handle.key[1] = 0x76543210;
    aes_handle.key[2] = 0x12345678;
    aes_handle.key[3] = 0x98765432;

    drv_bt_aes_init(&aes_handle);
    drv_bt_aes_cipher(&aes_handle, in, out);
    for (uint32_t index = 0; index < sizeof(out); index++) {
        soc_printf("%x ", out[index]);
    }
    soc_printf("\n");

    memset(in, 0, sizeof(in));
    drv_bt_aes_decipher(&aes_handle, out, in);
    for (uint32_t index = 0; index < sizeof(in); index++) {
        soc_printf("%x ", in[index]);
    }
    while (1) {
    }
}

void main_loop(void)
{
}

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
#include <string.h>
#include "inc/drv_trng.h"
#include "inc/drv_cpr.h"
#include "modules/drv_gpio.h"
#include "inc/drv_uart.h"
#include "inc/drv_sys_ctl.h"
#include "common.h"
#include "inc/drv_delay.h"

#define DATA_LEN 1024

uint32_t data_arr[DATA_LEN];
uint32_t data;
trng_handle_t htrng;
uart_handle_t uart_handle;

// log init
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

void trng_ro_test(void)
{
    drv_status_t status;

    soc_printf("tero test\n");

    __DRV_CPR_TRNG_CLK_ENABLE();

    htrng.instance = TRNG;
    htrng.init.ro_entropy_src_sel = TRNG_ENTROPY_SRC_0_EN | TRNG_ENTROPY_SRC_1_EN | TRNG_ENTROPY_SRC_2_EN | TRNG_ENTROPY_SRC_3_EN;
    htrng.init.trng_mode = TRNG_MODE_TRUE_RANDOM;
    htrng.init.sample_clock = TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_4;
    htrng.init.clock_src = TRNG_CLOCK_SRC_RO;
    htrng.init.trng_ctrl_port_read = drv_sys_ctr_osr_port_read;
    htrng.init.trng_ctrl_port_write = drv_sys_ctr_osr_port_write;
    drv_trng_init(&htrng);

    status = drv_trng_get_ro_random(&htrng, data_arr, DATA_LEN, DRV_MAX_DELAY);

    if (status == DRV_OK) {
        for (int i = 0; i < DATA_LEN; i++) {
            soc_printf("0x%02x, ", data_arr[i] & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 8 & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 16 & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 24 & 0xff);
            soc_printf("\n");
        }
    } else {
        soc_printf("get ro random error\n");
    }

    soc_printf("test again\n");
    drv_delay_ms(2000);
    memset(data_arr, 0, sizeof(data_arr));
    status = drv_trng_get_ro_random(&htrng, data_arr, DATA_LEN, DRV_MAX_DELAY);

    if (status == DRV_OK) {
        for (int i = 0; i < DATA_LEN; i++) {
            soc_printf("0x%02x, ", data_arr[i] & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 8 & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 16 & 0xff);
            soc_printf("0x%02x, ", data_arr[i] >> 24 & 0xff);
            soc_printf("\n");
        }
    } else {
        soc_printf("get ro random error\n");
    }

    soc_printf("test finish\n");
}

volatile uint32_t flag = 0;
void trng_ro_isr_cbk(trng_handle_t *trng)
{
    (void) trng;
    flag = 1;
}

void trng_ro_it_test(void)
{
    soc_printf("tero it test\n");

    __DRV_CPR_TRNG_CLK_ENABLE();

    htrng.instance = TRNG;
    htrng.init.ro_entropy_src_sel = TRNG_ENTROPY_SRC_0_EN | TRNG_ENTROPY_SRC_1_EN | TRNG_ENTROPY_SRC_2_EN | TRNG_ENTROPY_SRC_3_EN;
    htrng.init.trng_mode = TRNG_MODE_TRUE_RANDOM;
    htrng.init.sample_clock = TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_4;
    htrng.init.clock_src = TRNG_CLOCK_SRC_RO;
    htrng.init.trng_ctrl_port_read = drv_sys_ctr_osr_port_read;
    htrng.init.trng_ctrl_port_write = drv_sys_ctr_osr_port_write;
    drv_trng_init(&htrng);
    drv_trng_register_callback(&htrng, trng_ro_isr_cbk);
    flag = 0;
    drv_hw_int_enable(OSR_TRNG_IRQn);

    drv_trng_get_ro_random_it(&htrng, data_arr, DATA_LEN);

    while (flag == 0);

    for (int i = 0; i < DATA_LEN; i++) {
        soc_printf("0x%02x, ", data_arr[i] & 0xff);
        soc_printf("0x%02x, ", data_arr[i] >> 8 & 0xff);
        soc_printf("0x%02x, ", data_arr[i] >> 16 & 0xff);
        soc_printf("0x%02x, ", data_arr[i] >> 24 & 0xff);
        soc_printf("\n");
    }
    soc_printf("test finish\n");
    while(1) {

    }
}

void OSR_TRNG_IRQHandler(void)
{
    drv_trng_irq_handler(&htrng);
}
ISR_REGISTER(OSR_TRNG_IRQHandler, OSR_TRNG_IRQn)

void user_init(void)
{
    core_interrupt_enable();

    log_init();

    //trng_ro_test();
    //trng_ro_it_test();
    trng_init();
    data = trng_rand();
    soc_printf("trng data %x\n",data);
}
void main_loop(void)
{

}

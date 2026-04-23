/********************************************************************************************************
 * @file    master_interrupt.c
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
#include "common.h"
#if (I2C_MODE    ==  I2C_MASTER_INTERRUPT)
unsigned char i2c_master_it_rx_buf[1024];
unsigned int i2c_master_it_rx_len = 1024;
unsigned char i2c_master_it_tx_buf[1024] = { 1, 2, 3, 4 };
unsigned int i2c_master_it_tx_len = 1024;

i2c_handle_t i2c1_handle;

/**
 * @description: I2C1_IRQHandler
 * @param {none}
 * @return {none}
 */
void I2C1_IRQHandler(void)
{
    drv_i2c_irq_public_handle(&i2c1_handle);
}
void i2c_master_it_rx_test_cbk(i2c_handle_t *hi2c)
{
    LOG_INF("master end_len:%d\n", hi2c->rx_idx);
    for (unsigned int i = 0; i < hi2c->rx_idx; i++) {
        LOG_INF("master rx_buff[%d] %d, \n", i, hi2c->rx_buff[i]);
    }
}

void i2c_master_it_tx_test_cbk(i2c_handle_t *hi2c)
{
    LOG_INF("master send %d\n", hi2c->tx_idx);
}

void i2c_master_init(i2c_handle_t *hi2c)
{
    hi2c->init.i2c_mode = MASTER_MODE;
    hi2c->init.speed_mode = I2C_STD_MODE;
    hi2c->init.master_addr_width = I2C_7BITADDR;
    hi2c->init.slave_addr_width = I2C_7BITADDR;
    hi2c->init.device_addr = 0x28;
    hi2c->rx_buff = i2c_master_it_rx_buf;
    hi2c->tx_cnt = 0;
    hi2c->tx_buff = i2c_master_it_tx_buf;
    hi2c->rx_cnt = 0;
    hi2c->tx_cplt_cb = i2c_master_it_tx_test_cbk;
    hi2c->rx_cplt_cb = i2c_master_it_rx_test_cbk;
    hi2c->init.int_mask = 0;

    drv_i2c_init(hi2c);
    LOG_INF("can start i2c master test\n");
}
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
void i2c_pin_mux(void)
{
    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.mode = MODE_AF;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_3;
    drv_gpio_init(&gpio_init);
}
void user_init(void)
{
//    cpr_mclk0_init_t mclk0_init;
//    cpr_cpu_freq_init_t cpu_freq;
//    drv_status_t status;
//
//    __DRV_PMU_CLK_DBLR_ENABLE();
//    mclk0_init.source = DRV_CPR_MCLK0_SOURCE_DOUBLE;
//    mclk0_init.freq = 48000000;
//    mclk0_init.double_clock_sel = DRV_CPR_MCLK0_DBLR_SET_ORIGINAL; //DRV_CPR_MCLK0_DBLR_SET_ORIGINAL:48M, DRV_CPR_MCLK0_DBLR_SET_DIVIDED:32M
//    drv_cpr_config_mclk0(&mclk0_init);
//    cpu_freq.cpu0_freq = 48000000;
//    cpu_freq.cpu1_freq = 48000000;
//    cpu_freq.cpu2_freq = 48000000;
//    status = drv_cpr_set_cpu_freq(&cpu_freq);
//    if (status != DRV_OK) {
//        soc_printf("set cpu freq fail\n");
//    } else {
//        soc_printf("get cpu0 freq:%d\n", drv_cpr_get_cpu0_freq());
//        soc_printf("get cpu1 freq:%d\n", drv_cpr_get_cpu1_freq());
//        soc_printf("get cpu2 freq:%d\n", drv_cpr_get_cpu2_freq());
//    }

    core_interrupt_enable();
    log_init();
    __DRV_CPR_I2C1_CLK_ENABLE();
    drv_i2c_set_mclk(0);
    i2c_pin_mux();
//    soc_printf("i2c_test start init\n");

    drv_hw_int_enable(I2C1_IRQn);
   // i2c_master_init(&i2c1_handle);
    i2c1_handle.instance = I2C1;
    i2c1_handle.init.i2c_mode = MASTER_MODE;
    i2c1_handle.init.restart_en = DRV_SET;
    i2c1_handle.init.master_addr_width = I2C_7BITADDR;
    i2c1_handle.init.slave_addr_width = I2C_7BITADDR;
    i2c1_handle.init.speed_mode = I2C_STD_MODE;
    i2c1_handle.init.device_addr = 0x30;
    i2c1_handle.init.device_speed = 100000; //100kHz
    i2c1_handle.rx_buff = i2c_master_it_rx_buf;
    i2c1_handle.tx_cnt = 0;
    i2c1_handle.tx_buff = i2c_master_it_tx_buf;
    i2c1_handle.rx_cnt = 0;
    i2c1_handle.tx_cplt_cb = i2c_master_it_tx_test_cbk;
    i2c1_handle.rx_cplt_cb = i2c_master_it_rx_test_cbk;
    i2c1_handle.init.int_mask = 0;

    drv_i2c_init(&i2c1_handle);
    for (int i = 0; i < 64; i++) {
        i2c_master_it_tx_buf[i] = i;
    }

    while (1) {
        drv_i2c_master_interrupt_write(&i2c1_handle, 0x28, 0, i2c_master_it_tx_buf, 16);
        drv_delay_ms(1000);

        drv_i2c_master_interrupt_read(&i2c1_handle, 0x28, 0, i2c_master_it_rx_buf, 16);
        drv_delay_ms(1000);

    }
}


void main_loop(void){

}

ISR_REGISTER(I2C1_IRQHandler, I2C1_IRQn)
#endif

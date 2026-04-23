/********************************************************************************************************
 * @file    slave_polling.c
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
#if (I2C_MODE    ==  I2C_SLAVE_POLLING)
uint8_t gI2cRxBuf[4100];
uint8_t gI2cTxBuf[4100];

i2c_handle_t i2c1_handle;
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
void drv_i2c_slave_tx_test(i2c_handle_t *hi2c)
{
    uint32_t i = 0;
    for (i = 0; i < 16; i++) {
        gI2cTxBuf[i] = i + 48;
    }
    drv_i2c_slave_sync_send(hi2c, gI2cTxBuf, 16);
    soc_printf("\r\n slave send end");
}

void drv_i2c_slave_rx_test(i2c_handle_t *hi2c)
{
    uint32_t i = 0;
    soc_printf("\r\n slave normal start to recive\r\n");

    drv_i2c_slave_sync_receive(hi2c, gI2cRxBuf, 16);

    for (i = 0; i < 15; i++) {
        soc_printf("gI2cRxBuf[%d]:0x%x\r\n", i, gI2cRxBuf[i]);
    }

    soc_printf("\r\n slave normal end to recive\r\n");
}

void user_init(void)
{
    log_init();

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
    __DRV_CPR_I2C1_CLK_ENABLE();
    drv_i2c_set_mclk(0);
    i2c_pin_mux();
    LOG_INF("i2c_test start init\n");
    i2c1_handle.instance = I2C1;
    i2c1_handle.init.i2c_mode = SLAVE_MODE;
    i2c1_handle.init.restart_en = DRV_SET;
    i2c1_handle.init.master_addr_width = I2C_7BITADDR;
    i2c1_handle.init.slave_addr_width = I2C_7BITADDR;
    i2c1_handle.init.speed_mode = I2C_STD_MODE;
    i2c1_handle.init.device_addr = 0x28;
    i2c1_handle.init.int_mask = 0;
    drv_i2c_init(&i2c1_handle);

    memset(gI2cRxBuf, 0, sizeof(gI2cRxBuf));
    while (1) {
        // drv_i2c_slave_tx_test(&i2c1_handle);
        drv_i2c_slave_rx_test(&i2c1_handle);
        drv_i2c_slave_tx_test(&i2c1_handle);
//        drv_delay_ms(1000);
    }
}

void main_loop(void){

}
#endif

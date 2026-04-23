/********************************************************************************************************
 * @file    spis_it.c
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
#if(SPI_MODE   ==    SPI_SLAVE_INTERRUPT_MODE)
/**************************** include header *********************************/
#include <stdio.h>
#include <string.h>
#include "inc/drv_cpr.h"
#include "inc/drv_pmu.h"
#include "modules/drv_gpio.h"
#include "inc/drv_uart.h"
#include "inc/drv_spi.h"
#include "inc/drv_delay.h"
#include "soc_printf.h"

/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define MAX_SPI_RX_BUF (2000)
#define MAX_SPI_TX_BUF (2000)

/**************************** type definition ********************************/

/**************************** function declear *******************************/
void drv_spis_txcplt_callback(void *h_spis);
void drv_spis_rxcplt_callback(void *h_spis);
void drv_spis_error_callback(void *val);

/************************* variable definition *******************************/
//log init
uart_handle_t log_uart;
volatile uint32_t g_spi_tx_send_len = 40;
char spi_tx_buf[MAX_SPI_TX_BUF] = { 'S', 'P', 'I', 'S', '-', 'T', 'X' };
char spi_rx_buf[MAX_SPI_RX_BUF] = { 0 };
volatile uint8_t spi_rx_flag = 0;
volatile uint8_t spi_tx_flag = 0;
spi_handle_t hspis;
spi_cb_t spis_cd = {
    .rx_cplt_cb = drv_spis_rxcplt_callback,
    .tx_cplt_cb = drv_spis_txcplt_callback,
    .rx_error_cb = drv_spis_error_callback,
    .tx_error_cb = drv_spis_error_callback,
};

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

void DW_APB_SSI0_S_IRQHandler(void)
{
    drv_spis_irqhandler(&hspis);
}

ISR_REGISTER(DW_APB_SSI0_S_IRQHandler, DW_APB_SSI0_S_IRQn)

void drv_spis_txcplt_callback(void *h_spis)
{
    (void)h_spis;
    spi_tx_flag = 1;
    soc_printf("tx cplt\r\n");
}

void drv_spis_rxcplt_callback(void *h_spis)
{
    (void)h_spis;
    spi_rx_flag = 1;
    soc_printf("rx cplt\r\n");
}

void drv_spis_error_callback(void *val)
{
    soc_printf("spis error = %x\r\n", (int)val);
}

void spi_slave_init(void)
{
    for (uint16_t i = 7; i < MAX_SPI_TX_BUF - 1; i++) {
        spi_tx_buf[i] = (uint8_t)i;
    }

    hspis.instance = SPIS;
    hspis.init.mode = SPI_MODE_SLAVE;
    hspis.init.data_width = SPI_DATASIZE_8BITS;
    hspis.init.scph = SPI_CLOCK_PHASE_1EDGE;
    hspis.init.scpol = SPI_CLOCK_POLARITY_LOW;
    drv_spi_deinit(&hspis);
    drv_spi_init(&hspis);

    drv_spi_register_cb(&hspis, &spis_cd);
}

void drv_spi_msp_init(spi_handle_t *hspi)
{
    (void)hspi;
    __DRV_CPR_SPIS_CLK_ENABLE();
    drv_cpr_spis_mclk_set(0);

    /** GPIO Configuration */
    gpio_init_t gpio_init;
#if 0
    /**
    PA2 ------> SPI_CLK
    PA3 ------> SPI_SSN
    PA4 ------> SPI_RX
    PA5 ------> SPI_TX
    */
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init( &gpio_init);

    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; //gpio
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
    drv_gpio_init( &gpio_init);
#else
    /**
    PB2 ------> SPI_CLK
    PB3 ------> SPI_SSN
    PB4 ------> SPI_RX
    PB5 ------> SPI_TX
    */
    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_3;
    drv_gpio_init(&gpio_init);
#endif

    drv_hw_int_enable(DW_APB_SSI0_S_IRQn); /*!< enable hw int */
}

void drv_spi_msp_deinit(spi_handle_t *hspi)

{
    (void)hspi;
    drv_hw_int_disable(DW_APB_SSI0_S_IRQn); /*!< disable hw int */

    __DRV_CPR_SPIS_DEINIT();

    __DRV_CPR_SPIS_CLK_DISABLE();
}

//int main(void)
void user_init(void)
{
    core_interrupt_enable();

    /* init uart */
    log_init(); //uart1 used pa0 pa1

    soc_printf("\r\nspi slave test\r\n");
    spi_slave_init();
}

void main_loop(void)
{
    g_spi_tx_send_len = 40;
#if 0
    spi_rx_flag = 0;
    soc_printf("spi_it_tx\r\n");
    drv_spi_tx_it(&hspis, (uint8_t *)spi_tx_buf, g_spi_tx_send_len);
    while (spi_tx_flag == 0)
        ;
    soc_printf("send ok\r\n");
#endif
#if 0
    soc_printf("spi_it_rx\r\n");
    spi_rx_flag = 0;
    drv_spi_rx_it(&hspis, (uint8_t *)spi_rx_buf, g_spi_tx_send_len);
    while (spi_rx_flag == 0)
        ;
    soc_printf("\r\n rx data:");
    for (uint32_t i = 0; i < g_spi_tx_send_len; i++ ) {
        soc_printf("0x%02x ",spi_rx_buf[i]);
    }
#endif
#if 1
    spi_tx_flag = 0;
    spi_rx_flag = 0;

    soc_printf("\r\nspi_it_txrx\r\n");
    drv_spi_txrx_it(&hspis, (uint8_t *)spi_tx_buf, (uint8_t *)spi_rx_buf, g_spi_tx_send_len);
    while (spi_rx_flag == 0 || spi_tx_flag == 0)
        ;
    soc_printf("\r\n tx rx data:");
    for (uint32_t i = 0; i < g_spi_tx_send_len; i++ ) {
        soc_printf("0x%02x ",spi_rx_buf[i]);
    }
#endif
    
}
#endif

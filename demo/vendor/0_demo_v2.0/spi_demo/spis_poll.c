/********************************************************************************************************
 * @file    spis_poll.c
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
#if(SPI_MODE   ==    SPI_SLAVE_POLL_MODE)
/**************************** include header *********************************/
#include "soc_printf.h"

/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define MAX_SPI_RX_BUF (40)
#define MAX_SPI_TX_BUF (40)

/**************************** type definition ********************************/

/************************* variable definition *******************************/
//log init
uart_handle_t log_uart;
volatile uint32_t g_spi_tx_send_len = MAX_SPI_RX_BUF;
char spi_tx_buf[MAX_SPI_TX_BUF] = {'S', 'P', 'I', 'S', '-', 'T', 'X'};
char spi_rx_buf[MAX_SPI_RX_BUF] = {0};
spi_handle_t hspis;

/**************************** function declear *******************************/

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

void spi_slave_init(void)
{

    hspis.instance = SPIS;
    hspis.init.mode = SPI_MODE_SLAVE;
    hspis.init.data_width = SPI_DATASIZE_8BITS;
    hspis.init.scph = SPI_CLOCK_PHASE_1EDGE;
    hspis.init.scpol = SPI_CLOCK_POLARITY_LOW;
    drv_spi_deinit(&hspis);
    drv_spi_init(&hspis);
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

    drv_hw_int_disable(DW_APB_SSI0_S_IRQn); /*!< disable hw int */
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
    cpr_mclk0_init_t mclk0_init;

    __DRV_PMU_CLK_DBLR_ENABLE();

    mclk0_init.source = DRV_CPR_MCLK0_SOURCE_DOUBLE;
    mclk0_init.freq = 48000000;
    mclk0_init.double_clock_sel = DRV_CPR_MCLK0_DBLR_SET_ORIGINAL;
    drv_cpr_config_mclk0(&mclk0_init);

    /* init uart */
    log_init(); //uart1 used pa0 pa1

    soc_printf("\r\nspi slave test\r\n");
    spi_slave_init();

    for (uint16_t i = 7; i < MAX_SPI_TX_BUF; i++) {
        spi_tx_buf[i] = (uint8_t)i;
    }

   
}

void main_loop(void)
{
#if 0
    soc_printf("\r\nslave rx start\r\n");
    memset(spi_rx_buf, 0, sizeof(spi_rx_buf));
    drv_spi_rx(&hspis, (uint8_t *)spi_rx_buf, MAX_SPI_RX_BUF, 0xffffffff);
    for (uint16_t i = 0; i < MAX_SPI_RX_BUF; i++) {
        soc_printf("0x%02x ", spi_rx_buf[i]);
    }
    soc_printf("\r\nrx end\r\n");
#endif
#if 0
    soc_printf("\r\nslave tx start\r\n");
    drv_spi_tx(&hspis, (uint8_t *)spi_tx_buf, MAX_SPI_TX_BUF, 0xffffffff);
    soc_printf("tx end\r\n");

#endif
#if 1
    soc_printf("\r\nspi_txrx start\r\n");
    memset(spi_rx_buf, 0, sizeof(spi_rx_buf));
    drv_spi_txrx(&hspis, (uint8_t *)spi_tx_buf, (uint8_t *)spi_rx_buf, MAX_SPI_TX_BUF, 0xffffffff);
    for (uint16_t i = 0; i < MAX_SPI_RX_BUF; i++) {
        soc_printf("0x%02x ", spi_rx_buf[i]);
    }
    soc_printf("\r\ntxrx end\r\n");
#endif
}
#endif

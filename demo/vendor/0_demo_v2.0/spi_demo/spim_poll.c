/********************************************************************************************************
 * @file    spim_poll.c
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
#if(SPI_MODE   ==    SPI_MASTER_POLL_MODE)
/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define MAX_SPI_RX_BUF (40)
#define MAX_SPI_TX_BUF (40)

/**************************** type definition ********************************/

/************************** variable definition ******************************/

uint32_t g_spi_tx_send_len = MAX_SPI_RX_BUF;
char spi_tx_buf[MAX_SPI_TX_BUF] = { 0 };
char spi_rx_buf[MAX_SPI_RX_BUF] = { 0 };
volatile uint8_t spi_rx_flag = 0;
volatile uint8_t spi_tx_flag = 0;
spi_handle_t hspim;


/************************* function implementation ***************************/
uart_handle_t log_uart;
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

void spi_master_init(void)
{
    hspim.instance = SPIM;
    hspim.init.mode = SPI_MODE_MASTER;
    hspim.init.data_width = SPI_DATASIZE_8BITS;
    hspim.init.scph = SPI_CLOCK_PHASE_1EDGE;
    hspim.init.scpol = SPI_CLOCK_POLARITY_LOW;
    //hspim.init.scpol = SPI_CLOCK_POLARITY_HIGH;
    hspim.init.mclk = 48000000; //spim_mclk = mclk0 = 48m
    hspim.init.spi_clock = 3000000;
    hspim.init.rsd = 0;
    drv_spi_deinit(&hspim);
    drv_spi_init(&hspim);

    drv_spim_cs_select(&hspim, SPI_SSN0);
    //drv_spim_cs_select(&hspim, SPI_SSN1);
    //drv_spim_cs_select(&hspim, SPI_SSN2);
    //drv_spim_cs_select(&hspim, SPI_SSN3);
}

void drv_spi_msp_init(spi_handle_t *hspi)
{
     (void)hspi;
    __DRV_CPR_SPIM_CLK_ENABLE();
    drv_cpr_spim_mclk_set(0); //spim_mclk = mclk0 = 48m

    /** GPIO Configuration */
    gpio_init_t gpio_init;
    /**  master                slave
      PB2 ------> SPI_CLK <---> SPI_CLK <------ PB2
      PB3 ------> SPI_SSN <---> SPI_SSN <------ PB3
      PB4 ------> SPI_RX  <---> SPI_TX  <------ PB5
      PB5 ------> SPI_TX  <---> SPI_RX  <------ PB4
      */
    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_8;
    drv_gpio_init(&gpio_init);


    drv_hw_int_disable(DW_APB_SSI0_M_IRQn); /*!< disable hw int */
}

void drv_spi_msp_deinit(spi_handle_t *hspi)
{
    (void)hspi;
    drv_hw_int_disable(DW_APB_SSI0_M_IRQn); /*!< disable hw int */

    __DRV_CPR_SPIM_DEINIT();
    __DRV_CPR_SPIM_CLK_DISABLE();
}

void user_init(void)
{
    log_init();

    /** only for test */
   gpio_function_en(GPIO_PB7);
   gpio_function_en(GPIO_PB8);

   gpio_output_en(GPIO_PB7);
   gpio_output_en(GPIO_PB8);
   
   for (uint16_t i = 0; i < MAX_SPI_TX_BUF; i++)
   {
       spi_tx_buf[i] = i;
   }
   spi_master_init();
   //core_interrupt_enable();
   soc_printf("\r\nspi master test\r\n");
}

void main_loop(void)
{
    uint32_t res = 0;
#if 0
    soc_printf("master tx start\r\n");
    res = drv_spi_tx(&hspim, (uint8_t *)spi_tx_buf, MAX_SPI_TX_BUF, 1000);
    if (res == DRV_OK) {
        soc_printf("master tx OK\r\n");
    }
#endif
        
#if 1
    soc_printf("master txrx\r\n");
    res = drv_spi_txrx(&hspim, (uint8_t *)spi_tx_buf, (uint8_t *)spi_rx_buf, MAX_SPI_TX_BUF, 0xffffffff);
    if (res == DRV_OK) {
        soc_printf("send&receive OK\n");
    }
    for (int i = 0; i < MAX_SPI_RX_BUF; i++ ) {
        soc_printf("0x%02x ",spi_rx_buf[i]);
    }
    soc_printf("\r\nmaster rx end\r\n");
    spi_tx_buf[0] ++;
    spi_tx_buf[g_spi_tx_send_len-1] ++;
#endif
    drv_delay_ms(1000);
}
#endif

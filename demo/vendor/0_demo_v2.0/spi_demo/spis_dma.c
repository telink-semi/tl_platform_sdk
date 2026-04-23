/********************************************************************************************************
 * @file    spis_dma.c
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
#if(SPI_MODE   ==    SPI_SLAVE_DMA_MODE)
/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define MAX_SPI_RX_BUF (2000)
#define MAX_SPI_TX_BUF (2000)

/**************************** type definition ********************************/

/**************************** function declear *******************************/

/************************* variable definition *******************************/
//log init
uart_handle_t log_uart;
volatile uint32_t g_spi_tx_send_len = 40;
char spi_tx_buf[MAX_SPI_TX_BUF] = { 'S', 'P', 'I', 'S', '-', 'T', 'X' };
char spi_rx_buf[MAX_SPI_RX_BUF] = { 0 };
volatile uint8_t spi_rx_flag = 0;
volatile uint8_t spi_tx_flag = 0;
spi_handle_t hspis;
dmac_handle_t spis_rx_dmac_handle;
dmac_handle_t spis_tx_dmac_handle;

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

void CPU_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(hspis.hdmatx);
    drv_dmac_irq_handle(hspis.hdmarx);
}
ISR_REGISTER(CPU_DMA_IRQHandler, CPU_DMA_IRQn)

void drv_spis_txcplt_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    spi_tx_flag = 1;
    gpio_toggle(GPIO_PB6);
   // soc_printf("tx cplt\r\n");
}

void drv_spis_rxcplt_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    spi_rx_flag = 1;
    gpio_toggle(GPIO_PB1);
    //soc_printf("rx cplt\r\n");
}

void drv_spis_error_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    soc_printf("spis error\r\n");
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

    drv_dmac_register_cb(&spis_tx_dmac_handle, DRV_DMA_XFER_CPLT_CB_ID, drv_spis_txcplt_callback);
    drv_dmac_register_cb(&spis_rx_dmac_handle, DRV_DMA_XFER_CPLT_CB_ID, drv_spis_rxcplt_callback);
    drv_dmac_register_cb(&spis_tx_dmac_handle, DRV_DMA_XFER_ERROR_CB_ID, drv_spis_error_callback);
    drv_dmac_register_cb(&spis_rx_dmac_handle, DRV_DMA_XFER_ERROR_CB_ID, drv_spis_error_callback);
}

void drv_spi_msp_init(spi_handle_t *hspi)
{
    /** CLK Configuration */
    __DRV_CPR_SPIS_CLK_ENABLE();
    drv_cpr_spis_mclk_set(0);

    __DRV_CPR_SYSTEM_CLK_ENABLE();
    __DRV_CPR_CPU_DMA_CLK_ENABLE();

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
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_3;
    drv_gpio_init(&gpio_init);


    /** tx dma Configuration */
    spis_tx_dmac_handle.instance = CPU_DMAC;
    spis_tx_dmac_handle.init.channel = CPU_DMAC_CH0;
    spis_tx_dmac_handle.init.src_hs_num = 0;
    spis_tx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    spis_tx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    spis_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    spis_tx_dmac_handle.init.src_burst_size = DMAC_MSIZE_1;

    spis_tx_dmac_handle.init.dst_hs_num = CPU_DMAC_HS_DW_APB_SSI_S_TX;
    spis_tx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_HARD;
    spis_tx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_CONSTANT;
    spis_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    spis_tx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_1;

    spis_tx_dmac_handle.init.trans_mode = DMAC_CTL_TT_MEM2PER;
    spis_tx_dmac_handle.init.fifo_mode = 1;
    drv_dmac_init(&spis_tx_dmac_handle);
    __DRV_LINKDMA(hspi, hdmatx, spis_tx_dmac_handle);

    /** rx dma Configuration */
    spis_rx_dmac_handle.instance = CPU_DMAC;
    spis_rx_dmac_handle.init.channel = CPU_DMAC_CH1;
    spis_rx_dmac_handle.init.src_hs_num = CPU_DMAC_HS_DW_APB_SSI_S_RX;
    spis_rx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_HARD;
    spis_rx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    spis_rx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    spis_rx_dmac_handle.init.src_burst_size = DMAC_MSIZE_1;

    spis_rx_dmac_handle.init.dst_hs_num = 0;
    spis_rx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    spis_rx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    spis_rx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    spis_rx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_1;

    spis_rx_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    spis_rx_dmac_handle.init.fifo_mode = 1;
    drv_dmac_init(&spis_rx_dmac_handle);
    __DRV_LINKDMA(hspi, hdmarx, spis_rx_dmac_handle);

    drv_hw_int_enable(CPU_DMA_IRQn); /*!< enable hw int */
}

void drv_spi_msp_deinit(spi_handle_t *hspi)
{
    (void)hspi;
    drv_hw_int_disable(CPU_DMA_IRQn); /*!< disable hw int */

    __DRV_CPR_SPIS_DEINIT();
    __DRV_CPR_SPIS_CLK_DISABLE();
    __DRV_CPR_CPU_DMA_CLK_DISABLE();
}

void user_init(void)
{
    log_init();
    gpio_function_en(GPIO_PB6);
    gpio_function_en(GPIO_PB1);

    gpio_output_en(GPIO_PB6);
    gpio_output_en(GPIO_PB1);
    spi_slave_init();
    core_interrupt_enable();
    soc_printf("\r\nspi slave test\r\n");

}
void main_loop(void)
{
    g_spi_tx_send_len = 40;
#if 0       
    soc_printf("spi_dma_tx\r\n");
    drv_spi_tx_dma(&hspis, (uint8_t *)spi_tx_buf, RAM_ADDR_OFFSET, g_spi_tx_send_len);
    while (spi_tx_flag == 0)
        ;
    soc_printf("send ok\r\n");
    spi_tx_flag = 0;
    spi_rx_flag = 0;
#endif
#if 0
    soc_printf("spi_dma_rx\r\n");
    drv_spi_rx_dma(&hspis, (uint8_t *)spi_rx_buf, RAM_ADDR_OFFSET, g_spi_tx_send_len);
    while (spi_rx_flag == 0)
        ;
    soc_printf("\r\n rx data:");
    for (int i = 0; i < MAX_SPI_RX_BUF; i++ ) {
        soc_printf("0x%02x ",spi_rx_buf[i]);
    }
    spi_tx_flag = 0;
    spi_rx_flag = 0;
#endif
#if 1
    soc_printf("spi_dma_txrx\r\n");
    drv_spi_txrx_dma(&hspis, (uint8_t *)spi_tx_buf, (uint8_t *)spi_rx_buf, RAM_ADDR_OFFSET, g_spi_tx_send_len);
    while (spi_rx_flag == 0 || spi_tx_flag == 0)
        ;
    soc_printf("\r\n tx rx data:");
    for (uint32_t i = 0; i < g_spi_tx_send_len; i++ ) {
        soc_printf("0x%02x ",spi_rx_buf[i]);
    }
    spi_tx_flag = 0;
    spi_rx_flag = 0;
    //drv_delay_ms(1000);
    spi_tx_buf[7] ++;
    spi_tx_buf[g_spi_tx_send_len-1] ++;
#endif
}
#endif

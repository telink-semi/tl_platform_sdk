/********************************************************************************************************
 * @file    spim_dma.c
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
#if(SPI_MODE   ==    SPI_MASTER_DMA_MODE)
#include "hal/hal_clock.h"
/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define MAX_SPI_RX_BUF (40)
#define MAX_SPI_TX_BUF (40)

/************************** variable definition ******************************/
uint32_t g_spi_tx_send_len = 40;
char spi_tx_buf[MAX_SPI_TX_BUF] = { 0 };
char spi_rx_buf[MAX_SPI_RX_BUF] = { 0 };
volatile uint8_t spi_rx_flag = 0;
volatile uint8_t spi_tx_flag = 0;
spi_handle_t hspim;
dmac_handle_t spim_rx_dmac_handle;
dmac_handle_t spim_tx_dmac_handle;

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

void CPU_DMA_IRQHandler(void)
{

    drv_dmac_irq_handle(hspim.hdmatx);
    drv_dmac_irq_handle(hspim.hdmarx);
}

ISR_REGISTER(CPU_DMA_IRQHandler, CPU_DMA_IRQn)

void drv_spim_txcplt_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    spi_tx_flag = 1;
    gpio_toggle(GPIO_PB6);
    soc_printf("tx cplt\r\n");
}

void drv_spim_rxcplt_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    spi_rx_flag = 1;
    gpio_toggle(GPIO_PB1);
    soc_printf("rx cplt\r\n");
}

void drv_spim_error_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    soc_printf("spim error\r\n");
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

    drv_dmac_register_cb(&spim_tx_dmac_handle, DRV_DMA_XFER_CPLT_CB_ID, drv_spim_txcplt_callback);
    drv_dmac_register_cb(&spim_rx_dmac_handle, DRV_DMA_XFER_CPLT_CB_ID, drv_spim_rxcplt_callback);
    drv_dmac_register_cb(&spim_tx_dmac_handle, DRV_DMA_XFER_ERROR_CB_ID, drv_spim_error_callback);
    drv_dmac_register_cb(&spim_rx_dmac_handle, DRV_DMA_XFER_ERROR_CB_ID, drv_spim_error_callback);

    drv_spim_cs_select(&hspim, SPI_SSN0);
    // drv_spim_cs_select(&hspim, SPI_SSN1);
    // drv_spim_cs_select(&hspim, SPI_SSN2);
    // drv_spim_cs_select(&hspim, SPI_SSN3);
}

void drv_spi_msp_init(spi_handle_t *hspi)
{
    /** CLK Configuration */
    __DRV_CPR_SPIM_CLK_ENABLE();
    drv_cpr_spim_mclk_set(0); //spim_mclk = mclk0 = 48m

    __DRV_CPR_SYSTEM_CLK_ENABLE();
    SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_CFG_AHB_BUS_CLK_EN_MSK); /* enable ahb bus */
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
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_8;
    drv_gpio_init(&gpio_init);


    /** tx dma Configuration */
    spim_tx_dmac_handle.instance = CPU_DMAC;
    spim_tx_dmac_handle.init.channel = CPU_DMAC_CH0;
    spim_tx_dmac_handle.init.src_hs_num = 0;
    spim_tx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    spim_tx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    spim_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    spim_tx_dmac_handle.init.src_burst_size = DMAC_MSIZE_1;

    spim_tx_dmac_handle.init.dst_hs_num = CPU_DMAC_HS_DW_APB_SSI_M_TX;
    spim_tx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_HARD;
    spim_tx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_CONSTANT;
    spim_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    spim_tx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_1;

    spim_tx_dmac_handle.init.trans_mode = DMAC_CTL_TT_MEM2PER;
    spim_tx_dmac_handle.init.fifo_mode = 1;
    drv_dmac_init(&spim_tx_dmac_handle);
    __DRV_LINKDMA(hspi, hdmatx, spim_tx_dmac_handle);

    /** rx dma Configuration */
    spim_rx_dmac_handle.instance = CPU_DMAC;
    spim_rx_dmac_handle.init.channel = CPU_DMAC_CH1;
    spim_rx_dmac_handle.init.src_hs_num = CPU_DMAC_HS_DW_APB_SSI_M_RX;
    spim_rx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_HARD;
    spim_rx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    spim_rx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    spim_rx_dmac_handle.init.src_burst_size = DMAC_MSIZE_1;

    spim_rx_dmac_handle.init.dst_hs_num = 0;
    spim_rx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    spim_rx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    spim_rx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    spim_rx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_1;

    spim_rx_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    spim_rx_dmac_handle.init.fifo_mode = 1;
    drv_dmac_init(&spim_rx_dmac_handle);
    __DRV_LINKDMA(hspi, hdmarx, spim_rx_dmac_handle);

    /** int Configuration */
    drv_hw_int_enable(CPU_DMA_IRQn);        /*!< enable hw int */
    drv_hw_int_disable(DW_APB_SSI0_M_IRQn); /*!< disable hw int */
}

void drv_spi_msp_deinit(spi_handle_t *hspi)
{
    (void)hspi;
    drv_hw_int_disable(CPU_DMA_IRQn);       /*!< disable hw int */
    drv_hw_int_disable(DW_APB_SSI0_M_IRQn); /*!< disable hw int */

    __DRV_CPR_SPIM_DEINIT();
    __DRV_CPR_SPIM_CLK_DISABLE();
    __DRV_CPR_CPU_DMA_CLK_DISABLE();
}

void user_init(void)
{
    log_init();
     /** only for test */
    gpio_function_en(GPIO_PB6);
    gpio_function_en(GPIO_PB1);

    gpio_output_en(GPIO_PB6);
    gpio_output_en(GPIO_PB1);
    for (uint16_t i = 0; i < MAX_SPI_TX_BUF - 1; i++)
    {
        spi_tx_buf[i] = i;
    }

    spi_master_init();
    core_interrupt_enable();
    soc_printf("\r\nspi master test\r\n");
}
void main_loop(void)
{
    soc_printf("spi_dma_tx\r\n");
    drv_spi_tx_dma(&hspim, (uint8_t *)spi_tx_buf, RAM_ADDR_OFFSET, g_spi_tx_send_len);
    while (spi_tx_flag == 0)
        ;
    spi_tx_flag = 0;
    drv_delay_ms(5);

    soc_printf("spi_dma_txrx\r\n");
    drv_spi_txrx_dma(&hspim, (uint8_t *)spi_tx_buf, (uint8_t *)spi_rx_buf, RAM_ADDR_OFFSET, g_spi_tx_send_len);
    while (spi_rx_flag == 0 || spi_tx_flag == 0)
        ;
    spi_rx_flag = 0;
    spi_tx_buf[0] ++;
    spi_tx_buf[g_spi_tx_send_len-1] ++;

    drv_delay_ms(2000);
}
#endif

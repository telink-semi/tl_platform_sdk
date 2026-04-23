/********************************************************************************************************
 * @file    app_dma.c
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
#if(UART_MODE   ==    UART_DMA)
/**************************** include header *********************************/
#include "inc/drv_cpr.h"
#include "modules/drv_gpio.h"
#include "inc/drv_uart.h"
#include <stdio.h>
#include <string.h>
#include "modules/drv_pmu_ex.h"
#include "hal/hal_uart.h"

/*************************** macro definition ********************************/
#define MAX_UART_RX_BUF (100)
#define MAX_UART_TX_BUF (100)

 uint8_t uart_tx_buf[MAX_UART_TX_BUF]={0};
 uint8_t uart_rx_buf[MAX_UART_RX_BUF]={0};

uart_handle_t uart_handle;
dmac_handle_t uart_dmac_tx;
dmac_handle_t uart_dmac_rx;

volatile int uart_dma_tx_finish_flag = 0;
volatile int uart_dma_rx_finish_flag = 0;

void CPU_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&uart_dmac_tx);
    drv_dmac_irq_handle(&uart_dmac_rx);
}
#if defined(MCU_CORE_TL752X)
PLIC_ISR_REGISTER(CPU_DMA_IRQHandler, IRQ_CPU_DMA)
#else
PLIC_ISR_REGISTER(CPU_DMA_IRQHandler, CPU_DMA_IRQn)
#endif


#if defined(MCU_CORE_TL651X)
void UART1_IRQHandler(void)
{
    drv_uart_irq_handler(&uart_handle);
}
ISR_REGISTER(UART1_IRQHandler, UART1_IRQn)
#endif

void uart_dma_tx_cb(uart_handle_t *huart)
{
    (void)huart;
     uart_dma_tx_finish_flag = 1;
}

void uart_dma_rx_cb(uart_handle_t *huart)
{
    (void)huart;
      uart_dma_rx_finish_flag = 1;
}

void uart_init(void)
{
    uart_set_pin(GPIO_PORT_A,GPIO_PIN_0,GPIO_PIN_1,GPIO_ALTERNATE_FUNC_2);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    hal_uart_init(DRV_CPR_UART_MCLK_SRC_DBLR,&uart_handle);

    drv_uart_register_callback(&uart_handle, DRV_UART_DMA_RX_CB_ID, uart_dma_rx_cb);
    drv_uart_register_callback(&uart_handle, DRV_UART_DMA_TX_CB_ID, uart_dma_tx_cb);

    memset(&uart_dmac_tx, 0, sizeof(uart_dmac_tx));
    uart_dmac_tx.init.channel = CPU_DMAC_CH1;
    uart_set_tx_dma_config(&uart_dmac_tx,&uart_handle);

    memset(&uart_dmac_rx, 0, sizeof(uart_dmac_rx));
    uart_dmac_rx.init.channel = CPU_DMAC_CH0;
    uart_set_rx_dma_config(&uart_dmac_rx,&uart_handle);

    drv_hw_int_enable(CPU_DMA_IRQn);
#if defined(MCU_CORE_TL651X)
    drv_hw_int_enable(UART1_IRQn);
#endif
    core_interrupt_enable();
}

void uart_tx_test(void)
{
    uint32_t val = 0;
    for (volatile int i = 0; i < MAX_UART_TX_BUF; i++) {
        val = i % 10;
        if (val == 0) {
            uart_tx_buf[i] = '\n';
        } else {
            uart_tx_buf[i] = '0' + val;
        }
    }
    uart_dma_tx_finish_flag = 0;
    uart_send_dma(&uart_handle, (uint8_t *)((uint32_t)&uart_tx_buf + CPU_SYS_BUS), MAX_UART_TX_BUF);
//    while (uart_handle.gstate != DRV_UART_STATE_READY) {
//        __NOP();
//    }
    while (uart_dma_tx_finish_flag == 0) {
       __NOP();
    }
}

drv_status_t uart_rx_test(void)
{
//  drv_status_t status;

    memset(uart_rx_buf, 0, MAX_UART_RX_BUF);

    uart_dma_rx_finish_flag = 0;

//  status = drv_uart_rx_fifo_config(&uart_handle, UART_RXFIFO_CHAR_1, 500000);
//  if (status != DRV_OK) {
//      return status;
//  }

    drv_uart_transmit(&uart_handle, (uint8_t *)"please start tx data\r\n", strlen("please start tx data\r\n"), DRV_MAX_DELAY);
    uart_receive_dma(&uart_handle, (uint8_t *)((uint32_t)uart_rx_buf + CPU_SYS_BUS), MAX_UART_RX_BUF);

    // while (uart_handle.rxstate != DRV_UART_STATE_READY) {
    //     __NOP();
    // }
    while (uart_dma_rx_finish_flag == 0) {
        __NOP();
    }
    uart_dma_rx_finish_flag = 0;
    drv_uart_transmit(&uart_handle, uart_rx_buf, uart_handle.rx_xfercount, DRV_MAX_DELAY);
    //this func is used to waiting for Transmitter Shift Register and the FIFO are both empty
    drv_uart_transmitter_empty_waiting(&uart_handle, DRV_MAX_DELAY);

    return DRV_OK;
}

void user_init(void)
{
    uart_init();
    uart_tx_test();
//    drv_delay_ms(1);
    uart_rx_test();
}
void main_loop(void){
    while(1){
        uart_tx_test();
         // drv_delay_ms(1);
        uart_rx_test();
    }
}
#endif


/********************************************************************************************************
 * @file    app_nodma.c
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
#if(UART_MODE   ==    UART_NDMA)
/**************************** include header *********************************/
/*************************** macro definition ********************************/
#define MAX_UART_RX_BUF (100)
#define MAX_UART_TX_BUF (100)

uint8_t uart_tx_buf[MAX_UART_TX_BUF];
uint8_t uart_rx_buf[MAX_UART_RX_BUF];

uart_handle_t uart_handle;
volatile int uart_it_tx_finish_flag = 0;
volatile int uart_it_rx_finish_flag = 0;

volatile unsigned int g_uart_rec_len=0;
char uart_tx_start_buf[MAX_UART_TX_BUF] = "uart tx test\n";

void UART1_IRQHandler(void)
{
    drv_uart_irq_handler(&uart_handle);
}
#if defined(MCU_CORE_TL752X)
PLIC_ISR_REGISTER(UART1_IRQHandler, UART1_IRQn)
#else
PLIC_ISR_REGISTER(UART1_IRQHandler, UART1_IRQn)
#endif

void uart_it_tx_cb(uart_handle_t *huart)
{
    (void)huart;
    static unsigned int tx_again_flag = 1;

    if (tx_again_flag != 0) {
        tx_again_flag--;
        drv_uart_transmit_it(&uart_handle, uart_tx_buf, MAX_UART_TX_BUF);
    }else{
         uart_it_tx_finish_flag = 1;
    }
}
#if defined(MCU_CORE_TL752X)
void uart_it_rx_cb(uart_handle_t *huart)
{
    if (huart->rx_callback_arg->type == UART_RX_CALLBACK_COMPLETE)
    {
        uart_it_rx_finish_flag=1;
        g_uart_rec_len = huart->rx_callback_arg->rx_data_len;
    }
    huart->rx_callback_arg->type=0;
}
#else
void uart_it_rx_cb(uart_handle_t *huart)
{
    if (huart->rx_callback_arg->type == UART_RX_CALLBACK_COMPLETE) {
        uart_it_rx_finish_flag = 1;
    } else {
        drv_uart_receive_it_continue(huart);
    }
}
#endif

void uart_init(void)
{
    uart_set_pin(GPIO_PORT_A,GPIO_PIN_0,GPIO_PIN_1,GPIO_ALTERNATE_FUNC_2);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;

    hal_uart_init(DRV_CPR_UART_MCLK_SRC_DBLR,&uart_handle);

    drv_uart_register_callback(&uart_handle, DRV_UART_IT_TX_CB_ID, uart_it_tx_cb);
    drv_uart_register_callback(&uart_handle, DRV_UART_IT_RX_CB_ID, uart_it_rx_cb);

    drv_hw_int_enable(UART1_IRQn);
    core_interrupt_enable();

    drv_uart_transmit(&uart_handle, (unsigned char*)uart_tx_start_buf, strlen(uart_tx_start_buf), DRV_MAX_DELAY);
}

void uart_tx_test(void)
{
    uint32_t val = 0;
    for (int i = 0; i < MAX_UART_TX_BUF; i++) {
        val = i % 10;
        if (val == 0) {
            uart_tx_buf[i] = '\n';
        } else {
            uart_tx_buf[i] = '0' + val;
        }
    }
    drv_uart_transmit_it(&uart_handle, uart_tx_buf, MAX_UART_TX_BUF);
//    while (uart_handle.gstate != DRV_UART_STATE_READY) {
//        __NOP();
//    }
    while (uart_it_tx_finish_flag == 0) {
        __NOP();
    }
}

drv_status_t uart_rx_test(void)
{
//    drv_status_t status;

    memset(uart_rx_buf, 0, MAX_UART_RX_BUF);

//    status = drv_uart_rx_fifo_config(&uart_handle, UART_RXFIFO_QUARTER_FULL, 500000);
//    if (status != DRV_OK) {
//        return status;
//    }
    uart_it_rx_finish_flag =0;
   // drv_uart_transmit(&uart_handle, (uint8_t *)"please start tx data\r\n", strlen("please start tx data\r\n"), DRV_MAX_DELAY);
    drv_uart_receive_it(&uart_handle, uart_rx_buf, MAX_UART_RX_BUF);

    // while (uart_handle.rxstate != DRV_UART_STATE_READY) {
    //     __NOP();
    // }
    while (uart_it_rx_finish_flag == 0) {
        __NOP();
    }

    drv_uart_transmit(&uart_handle, uart_rx_buf, uart_handle.rx_xfercount, DRV_MAX_DELAY);
    //this func is used to waiting for Transmitter Shift Register and the FIFO are both empty
    drv_uart_transmitter_empty_waiting(&uart_handle, DRV_MAX_DELAY);

    return DRV_OK;
}

void user_init(void)
{
    uart_init();
    // uart_tx_test();
    uart_rx_test();
}

void main_loop(void){
    while(1){
        uart_rx_test();
    }
}
#endif

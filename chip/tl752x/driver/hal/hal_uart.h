/********************************************************************************************************
 * @file    hal_uart.h
 *
 * @brief   This is the header file for tl752x
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



#ifndef HAL_UART_H_
#define HAL_UART_H_
#include "inc/drv_uart.h"

#define uart_send_dma(uart_handle,uart_tx_buf,data_size)                  drv_uart_transmit_dma(uart_handle,uart_tx_buf,data_size)
#define uart_receive_dma(uart_handle,uart_rx_buf,data_size)               drv_uart_receive_dma(uart_handle,uart_rx_buf,data_size)

void uart_set_pin(unsigned int gpio_port,unsigned int tx_pin,unsigned int rx_pin,unsigned int gpio_func);

void hal_uart_init(unsigned char clk_src, uart_handle_t *huart);

void uart_set_tx_dma_config(dmac_handle_t *uart_dmac_tx, uart_handle_t *huart);

void uart_set_rx_dma_config(dmac_handle_t *uart_dmac_rx, uart_handle_t *huart);

#endif

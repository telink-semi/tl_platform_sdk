/*******************************************************************************************************
 *
 * @file    drv_uart.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "reg/uart.h"
#include "inc/drv_dmac.h"

#if defined(UART_VER_V2)
#define UART_POP_NUM_POS                      (0U)
#define UART_POP_NUM_MSK                      (0xFFFFUL << UART_POP_NUM_POS)
#define UART_POP_NUM                          UART_POP_NUM_MSK
#define UART_POP_NUM_CLEAR_POS                (16U)
#define UART_POP_NUM_CLEAR_MSK                (0x1UL << UART_POP_NUM_CLEAR_POS)
#define UART_POP_NUM_CLEAR                    UART_POP_NUM_CLEAR_MSK
#define UART_TIMEOUT_EN_POS                   (17U)
#define UART_TIMEOUT_EN_MSK                   (0x1UL << UART_TIMEOUT_EN_POS)
#define UART_TIMEOUT_EN                       UART_TIMEOUT_EN_MSK
#define UART_DMA_RX_OPTION_POS                (31U)
#define UART_DMA_RX_OPTION_MSK                (0x01UL << UART_DMA_RX_OPTION_POS)
#define UART_DMA_RX_OPTION                    UART_DMA_RX_OPTION_MSK
#endif

/** @defgroup UART_Word_Length UART Word Length
 * @{
 */
#define UART_WORDLENGTH_5B 0UL
#define UART_WORDLENGTH_6B 1UL
#define UART_WORDLENGTH_7B 2UL
#define UART_WORDLENGTH_8B 3UL

/** @defgroup UART_Stop_Bits UART Number of Stop Bits
 * @{
 */
#define UART_STOPBITS_1        0
#define UART_STOPBITS_1_5_OR_2 1 // stopbits is 1.5 when wordlength is 5bit

/** @defgroup UART_Parity UART Parity
 * @{
 */
#define UART_PARITY_NONE 0
#define UART_PARITY_EVEN 1
#define UART_PARITY_ODD  2

/** @defgroup UART_Hardware_Flow_Control UART Hardware Flow Control
 * @{
 */
#define UART_HWCONTROL_NONE    0
#define UART_HWCONTROL_CTS     1
#define UART_HWCONTROL_RTS_CTS 2

typedef enum {
    UART_RXFIFO_CHAR_1 = 0,   /* 1 character in the FIFO */
    UART_RXFIFO_QUARTER_FULL, /* FIFO 1/4 full */
    UART_RXFIFO_HALF_FULL,    /* FIFO 1/2 full */
    UART_RXFIFO_FULL_2,       /* FIFO 2 less than full */
} uart_rx_fifo_th_t;

typedef enum {
    UART_RX_CALLBACK_STOP,
    UART_RX_CALLBACK_COMPLETE
} uart_rx_callback_type_t;

typedef struct {
    uint32_t baudrate;
    uint32_t wordlength; //@ref UART_Word_Length
    uint32_t stopbits;   //@ref UART_Stop_Bits
    uint32_t parity;     //@ref UART_Parity
    uint32_t hwflowctl;  //@ref UART_Hardware_Flow_Control
} uart_init_t;

typedef enum {
    DRV_UART_STATE_RESET = 0x00U,      /*!< Peripheral is not yet Initialized                                                   Value is allowed for gState and RxState */
    DRV_UART_STATE_READY = 0x20U,      /*!< Peripheral Initialized and ready for use                                                  Value is allowed for gState and RxState */
    DRV_UART_STATE_BUSY = 0x24U,       /*!< an internal process is ongoing                                                  Value is allowed for gState only */
    DRV_UART_STATE_BUSY_TX = 0x21U,    /*!< Data Transmission process is ongoing                                                   Value is allowed for gState only */
    DRV_UART_STATE_BUSY_RX = 0x22U,    /*!< Data Reception process is ongoing                                                   Value is allowed for RxState only */
    DRV_UART_STATE_BUSY_TX_RX = 0x23U, /*!< Data Transmission and Reception process is ongoing
                                           Not to be used for neither gState nor RxState.
                                           Value is result of combination (Or) between gState and RxState values */
    DRV_UART_STATE_TIMEOUT = 0xA0U,    /*!< Timeout state Value is allowed for gState only */
    DRV_UART_STATE_ERROR = 0xE0U       /*!< Error Value is allowed for gState only */
} drv_uart_state_t;

typedef struct {
    volatile uint32_t rx_data_len;
    uart_rx_callback_type_t type;
} uart_rx_callback_arg_t;

typedef enum {
    DRV_UART_IT_TX_CB_ID = 0x00U,
    DRV_UART_IT_RX_CB_ID = 0x01U,
    DRV_UART_DMA_TX_CB_ID = 0x02U,
    DRV_UART_DMA_RX_CB_ID = 0x03U,
} drv_uart_callback_id_t;

typedef struct __uart_handle_t {
    uart_reg_t *instance; /*!< UART registers base address        */
    uart_init_t init;     /*!< UART communication parameters      */
    uint32_t (*uart_get_freq)(void);
    const uint8_t *ptxbuffptr;       /*!< Pointer to UART Tx transfer Buffer */
    uint32_t tx_xfersize;            /*!< UART Tx Transfer size              */
    DRV_IOM uint32_t tx_xfercount;   /*!< UART Tx Transfer Counter           */
    uint8_t *prxbuffptr;             /*!< Pointer to UART Rx transfer Buffer */
    uint32_t rx_xfersize;            /*!< UART Rx Transfer size              */
    DRV_IOM uint32_t rx_xfercount;   /*!< UART Rx Transfer Counter           */
    drv_lock_t lock;                 /*!< Locking object                     */
    DRV_IOM drv_uart_state_t gstate; /*!< UART state information related to global Handle management
                                             and also related to Tx operations.
                                             This parameter can be a value of @ref drv_uart_state_t */
    DRV_IOM drv_uart_state_t rxstate;
    uart_rx_callback_arg_t *rx_callback_arg;
    void (*it_tx_callback)(struct __uart_handle_t *huart);
    void (*it_rx_callback)(struct __uart_handle_t *huart);
    void (*dma_tx_callback)(struct __uart_handle_t *huart);
    void (*dma_rx_callback)(struct __uart_handle_t *huart);
#if defined(UART_VER_V2)
    volatile uint32_t dma_rx_handle_state;
#endif
    dmac_handle_t *hdmatx; /*!< UART Tx DMA Handle parameters      */
    dmac_handle_t *hdmarx; /*!< UART Rx DMA Handle parameters      */
} uart_handle_t;

typedef void (*puart_callback_t)(struct __uart_handle_t *huart); /*!< pointer to an UART callback function */

/**
 * @brief  Initializes the UART mode according to the specified parameters in
 *          the uart_handle_t and create the associated handle.
 * @param  {uart_handle_t} *huart, Pointer to a uart_handle_t structure that
 *          contains the configuration information for the specified UART module.
 * @retval drv_status_t
 */
extern drv_status_t drv_uart_init(uart_handle_t *huart);

/**
 * @brief  DeInitializes the UART peripheral.
 * @param  {uart_handle_t} *huart, Pointer to a uart_handle_t structure that contains
 *          the configuration information for the specified UART module.
 * @retval drv_status_t
 */
extern drv_status_t drv_uart_deinit(uart_handle_t *huart);

/**
 * @brief Sends an amount of data in blocking mode.
 * @param {uart_handle_t} *huart,Pointer to a uart_handle_t structure that contains
 *         the configuration information for the specified UART module.
 * @param {uint8_t} *pdata, Pointer to data buffer
 * @param {uint32_t} size, Amount of data elements
 * @param {uint32_t} timeout, Timeout duration
 * @retval drv_status_t
 */
extern drv_status_t drv_uart_transmit(uart_handle_t *huart, const uint8_t *pdata, uint32_t size, uint32_t timeout);

/**
 * @brief  Sends an amount of data in blocking mode.
 * @param  huart, Pointer to a uart_handle_t structure that contains
 *         the configuration information for the specified UART module.
 * @param  pdata, Pointer to data buffer (u8 data elements).
 * @param  size,  Amount of data elements (u8) to be sent
 * @param  timeout, Timeout duration
 * @retval drv_status_t
 */
extern drv_status_t drv_uart_receive(uart_handle_t *huart, uint8_t *pdata, uint32_t size, uint32_t timeout);

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  huart, Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  pdata, Pointer to data buffer (u8 data elements).
  * @param  size,  Amount of data elements (u8) to be sent
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_transmit_it(uart_handle_t *huart, const uint8_t *pdata, uint32_t size);

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  huart Pointer to a uart_handle_t structure that contains
  *               the configuration information for the specified UART module.
  * @param  pdata Pointer to data buffer (u8 data elements).
  * @param  size  Amount of data elements (u8 ) to be received.
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_receive_it(uart_handle_t *huart, uint8_t *pdata, uint32_t size);

/**
 * @brief: uart irq handler
 * @param  huart Pointer to a uart_handle_t structure that contains
 *               the configuration information for the specified UART module.
 * @retval {none}
 */
extern void drv_uart_irq_handler(uart_handle_t *huart);

/**
 * @brief: waiting for Transmitter Shift Register and the FIFO are both empty
 * @param  huart Pointer to a uart_handle_t structure that contains
 *               the configuration information for the specified UART module.
 * @param  timeout, Timeout duration
 * @retval {none}
 */
extern drv_status_t drv_uart_transmitter_empty_waiting(uart_handle_t *huart, uint32_t timeout);

/**
 * @brief  get rx FIFO data num
 * @retval {uint32_t} data num
 */
extern uint32_t drv_uart_get_rxfifo_data_num(uart_handle_t *huart);

/**
 * @brief  Used to continue transmission after a stop interruption
 * @param  huart Pointer to a uart_handle_t structure that contains
 *               the configuration information for the specified UART module.
 * @param  timeout, Timeout duration
 * @retval {none}
 */
extern drv_status_t drv_uart_receive_it_continue(uart_handle_t *huart);

/**
  * @brief  Register a User UART Callback
  * @param  huart uart handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *           @ref DRV_UART_TX_CB_ID
  *           @ref DRV_UART_RX_CB_ID
  * @param  pCallback pointer to the Callback function
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_register_callback(uart_handle_t *huart, drv_uart_callback_id_t callback_id, puart_callback_t pcallback);
/**
  * @brief  unRegister a User UART Callback
  * @param  huart uart handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *           @ref DRV_UART_TX_CB_ID
  *           @ref DRV_UART_RX_CB_ID
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_unregister_callback(uart_handle_t *huart, drv_uart_callback_id_t callback_id);

/**
  * @brief  Sends an amount of data in DMA mode.
  * @param  huart  Pointer to a uart_handle_t structure that contains
  *                the configuration information for the specified UART module.
  * @param  pdata Pointer to data buffer.
  * @param  size  Amount of data elements.
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_transmit_dma(uart_handle_t *huart, const uint8_t *pdata, uint32_t size);

/**
  * @brief  Receives an amount of data in DMA mode.
  * @param  huart Pointer to a uart_handle_t structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer .
  * @param  Size  Amount of data elements to be received.
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_receive_dma(uart_handle_t *huart, uint8_t *pdata, uint32_t size);

/**
  * @brief  Receives fifo config.
  * @param  huart Pointer to a uart_handle_t structure that contains
  *               the configuration information for the specified UART module.
  * @param  fifo_th @ref uart_rx_fifo_th_t.
  * @param  timeout  timeout val.
  * @retval drv_status_t
  */
extern drv_status_t drv_uart_rx_fifo_config(uart_handle_t *huart, uart_rx_fifo_th_t fifo_th, uint32_t timeout);

#ifdef __cplusplus
}
#endif
#endif

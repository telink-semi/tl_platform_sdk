/*******************************************************************************************************
 *
 * @file    drv_spi.h
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
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "inc/drv_dmac.h"
#include "reg/spi.h"

/*************************** macro definition ********************************/

/**************************** type definition ********************************/
//SPI operating mode
typedef enum {
    SPI_MODE_SLAVE = 0,
    SPI_MODE_MASTER = 1,
} spi_mode_t;

typedef enum {
    SPI_NO_ERROR = 0,
    SPI_TX_FIFO_OVERFLOW = 1,
    SPI_RX_FIFO_UNDERFLOW = 2,
    SPI_RX_FIFO_OVERFLOW = 3,
} spi_error_t;

typedef enum {
    SPI_SSN0 = 0,
    SPI_SSN1 = 1,
    SPI_SSN2 = 2,
    SPI_SSN3 = 3,
} spi_ssnsel_t;

typedef enum {
    SPI_FRAMEFORMAT_SPI = 0,
    SPI_FRAMEFORMAT_SSP = 1,
} spi_frameformat_t;

typedef enum {
    SPI_CLOCK_POLARITY_LOW = 0,
    SPI_CLOCK_POLARITY_HIGH = 1,
} spi_scpol_t;

typedef enum {
    SPI_CLOCK_PHASE_1EDGE = 0,
    SPI_CLOCK_PHASE_2EDGE = 1,
} spi_scph_t;

typedef enum {
    SPI_TXRX = 0,
    SPI_TX = 1,
    SPI_RX = 2,
} spi_tmod_t;

typedef enum {
    SPI_NORMAL_MODE = 0,
    SPI_TEST_MODE = 1,
} spi_srl_mode_t;

typedef enum {
    SPI_TX_FIFO_NOT_EMPTY = 0,
    SPI_TX_FIFO_EMPTY = 1,
} spi_tx_fifo_stat_t;

typedef enum {
    SPI_RX_FIFO_EMPTY = 0,
    SPI_RX_FIFO_NOT_EMPTY = 1,
} spi_rx_fifo_stat_t;

typedef enum {
    SPI_DATASIZE_4BITS = 3,
    SPI_DATASIZE_5BITS = 4,
    SPI_DATASIZE_6BITS = 5,
    SPI_DATASIZE_7BITS = 6,
    SPI_DATASIZE_8BITS = 7,
    SPI_DATASIZE_9BITS = 8,
    SPI_DATASIZE_10BITS = 9,
    SPI_DATASIZE_11BITS = 10,
    SPI_DATASIZE_12BITS = 11,
    SPI_DATASIZE_13BITS = 12,
    SPI_DATASIZE_14BITS = 13,
    SPI_DATASIZE_15BITS = 14,
    SPI_DATASIZE_16BITS = 15,
    SPI_DATASIZE_17BITS = 16,
    SPI_DATASIZE_18BITS = 17,
    SPI_DATASIZE_19BITS = 18,
    SPI_DATASIZE_20BITS = 19,
    SPI_DATASIZE_21BITS = 20,
    SPI_DATASIZE_22BITS = 21,
    SPI_DATASIZE_23BITS = 22,
    SPI_DATASIZE_24BITS = 23,
    SPI_DATASIZE_25BITS = 34,
    SPI_DATASIZE_26BITS = 25,
    SPI_DATASIZE_27BITS = 26,
    SPI_DATASIZE_28BITS = 27,
    SPI_DATASIZE_29BITS = 28,
    SPI_DATASIZE_30BITS = 29,
    SPI_DATASIZE_31BITS = 30,
    SPI_DATASIZE_32BITS = 31,
} spi_datawidth_t;

typedef enum {
    SPI_FRAME_8BITS = 0,
    SPI_FRAME_16BITS = 1,
    SPI_FRAME_32BITS = 2,
} spi_frame_mode_t;

typedef struct {
    uint32_t mclk;   /*!< The frequency of mclk0 after spi frequency division. master use only */
    spi_mode_t mode; /*!< Specifies the SPI operating mode.
  This parameter can be a value of @ref SPI_Mode */
    /*!< A summary of the frequency ratio restrictions between the bit-rate
     clock (sclk_out/sclk_in) and the spi clock (ssi_clk) are as follows:
    Master
        Fssi_clk >= 2x (maximum Fsclk_out)
    Slave SSI_ENH_CLK_RATIO=0
        Receive only: Fssi_clk >= 6× (maximum Fsclk_in)
        Transmit and Receive: Fssi_clk >= 12× (maximum Fsclk_in)
    Slave SSI_ENH_CLK_RATIO=1
        Fssi_clk >= 4x (maximum Fsclk_in) */
    uint32_t spi_clock; /*!< master use only */
    uint8_t rsd;        /*!< RX Sample Delay. master use only */
    spi_datawidth_t data_width;
    spi_scph_t scph;
    spi_scpol_t scpol;
} spi_init_t;

/**
 * @brief  spi Callback Structure definition
 */
typedef struct {
    void (*tx_cplt_cb)(void *hspi); /*!< spi Callback */
    void (*rx_cplt_cb)(void *hspi); /*!< spi Callback */
    void (*tx_error_cb)(void *val); /*!< spi Callback */
    void (*rx_error_cb)(void *val); /*!< spi Callback */
} spi_cb_t;

/**
 * @brief  SPI handle Structure definition
 */
typedef struct {
    spi_reg_t *instance; /*!< SPI registers base address */
    spi_init_t init;
    dmac_handle_t *hdmatx;    /*!< spi Tx DMA Handle parameters */
    dmac_handle_t *hdmarx;    /*!< spi Rx DMA Handle parameters */
    uint8_t *tx_buff;         /*!< Pointer to SPI Tx transfer Buffer */
    volatile uint32_t tx_cnt; /*!< SPI Tx Transfer Counter */
    uint8_t *rx_buff;         /*!< Pointer to SPI Rx transfer Buffer */
    volatile uint32_t rx_cnt; /*!< SPI Rx Transfer Counter */
    drv_lock_t lock;          /*!< Locking object */
    spi_frame_mode_t frame_width;
    const spi_cb_t *cb; /*!< spi Callback */
} spi_handle_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  spi deinit
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_deinit(spi_handle_t *hspi);
/**
 * @brief  spi init
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_init(spi_handle_t *hspi);

/**
 * @brief  check whether the SPI rx fifo is empty
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  data_width: Data width.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_set_datawidth(spi_handle_t *hspi, spi_datawidth_t data_width);
/**
 * @brief  check whether the SPI rx fifo is empty
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return rx fifo status
 * @note   none
 */
extern uint32_t drv_spi_rx_fifo_check(spi_handle_t *hspi);

/**
 * @brief  check whether the SPI is actively transferring data
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_busy_status_check(spi_handle_t *hspi);

/**
 * @brief  SPI Master baud Rate Select 
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  baudrate: Baud Rate
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spim_set_baudrate(spi_handle_t *hspi, uint16_t baudrate);

/**
 * @brief  SPI Master cs select
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ssn_sel: SPI_SSN0, SPI_SSN1, SPI_SSN2, SPI_SSN3
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spim_cs_select(spi_handle_t *hspi, spi_ssnsel_t ssnSel);

/**
 * @brief  Register a User SPI Callback
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  cb: pCallback pointer to the Callback function
 * @retval status
 */
extern drv_status_t drv_spi_register_cb(spi_handle_t *hspi, spi_cb_t *cb);
/**
 * @brief  Unregister an SPI Callback
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @retval status
 */
extern drv_status_t drv_spi_unregister_cb(spi_handle_t *hspi);

/**
 * @brief  spi master Transmit an amount of data in blocking mode.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @param  timeout: time-out period
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_tx(spi_handle_t *hspi, uint8_t *ptxbuf, uint32_t len, uint32_t timeout);
/**
 * @brief  spi receive an amount of data in blocking mode.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  prxbuf: Receive data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @param  timeout: time-out period
 * @return drv_status_t
 * @note   continuous data transfers is not supported
 */
extern drv_status_t drv_spi_rx(spi_handle_t *hspi, uint8_t *prxbuf, uint32_t len, uint32_t timeout);
/**
 * @brief  spi master Transmit an amount of data in blocking mode.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  prxbuf: receive data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @param  timeout: time-out period
 * @return drv_status_t
 * @note   continuous data transfers is not supported
 */
extern drv_status_t drv_spi_txrx(spi_handle_t *hspi, uint8_t *ptxbuf, uint8_t *prxbuf, uint32_t len, uint32_t timeout);

/**
 * @brief  spi Transmit an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_tx_it(spi_handle_t *hspi, uint8_t *ptxbuf, uint32_t len);
/**
 * @brief  spi receive an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  prxbuf: Receive data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_rx_it(spi_handle_t *hspi, uint8_t *prxbuf, uint32_t len);
/**
 * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  prxbuf: Receive data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spi_txrx_it(spi_handle_t *hspi, uint8_t *ptxbuf, uint8_t *prxbuf, uint32_t len);

/**
 * @brief  spi Transmit an amount of data in non-blocking mode with DMA.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  offset: dma access ram offset address
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   Only SPI_TX mode is supported
 */
extern drv_status_t drv_spi_tx_dma(spi_handle_t *hspi, uint8_t *ptxbuf, uint32_t offset, uint32_t len);
/**
 * @brief  spi receive an amount of data in non-blocking mode with DMA.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  prxbuf: Receive data buffer
 * @param  offset: dma access ram offset address
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   Only SPI_RX mode is supported
 */
extern drv_status_t drv_spi_rx_dma(spi_handle_t *hspi, uint8_t *prxbuf, uint32_t offset, uint32_t len);
/**
 * @brief  Transmit and Receive an amount of data in non-blocking mode with dma.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @param  ptxbuf: Send data buffer
 * @param  prxbuf: Receive data buffer addr
 * @param  offset: dma access ram offset address
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   Only SPI_TXRX mode is supported
 */
extern drv_status_t drv_spi_txrx_dma(spi_handle_t *hspi, uint8_t *ptxbuf, uint8_t *prxbuf, uint32_t offset, uint32_t len);

/**
 * @brief  spim interrupt handler.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return none
 * @note   none
 */
extern void drv_spim_irqhandler(spi_handle_t *hspi);
/**
 * @brief  spis interrupt handler.
 *
 * @param  hspi: hspi pointer to a spi_handle_t structure that contains the configuration information for SPI module.
 * @return none
 * @note   none
 */
extern void drv_spis_irqhandler(spi_handle_t *hspi);

/**
 * @brief  Initialize the spi MSP.
 * @param  hrsm: Pointer to a spi_handle_t structure that contains
 *         the configuration information for the specified spi.
 * @retval None
 */
extern void drv_spi_msp_init(spi_handle_t *hspi);

/**
 * @brief  DeInitialize the spi MSP.
 * @param  hrsm: Pointer to a spi_handle_t structure that contains
 *         the configuration information for the specified spi.
 * @retval None
 */
extern void drv_spi_msp_deinit(spi_handle_t *hspi);

// PJB_TEST
extern void drv_spi_tx_test(spi_handle_t *hspi, uint8_t *ptxbuf, uint32_t len);
extern void drv_spi_rx_test(spi_handle_t *hspi, uint8_t *prxbuf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif

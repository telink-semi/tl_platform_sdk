/*******************************************************************************************************
 *
 * @file    drv_gpadc.h
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
#ifndef __DRV_GPADC_H__
#define __DRV_GPADC_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "tl_chip.h"
#include "reg/gpadc.h"
#include "inc/drv_dmac.h"

/**************************** macro definition *******************************/

/**************************** type definition ********************************/
typedef enum {
    RISING_CLK_EDGE = 0,
    FALLING_CLK_EDGE = 1,
} clk_edge_sel_t;

typedef enum {
    DATA_READY = 0,
    FIFO_OVERFLOW = 1,
    FIFO_UNDERFLOW = 2,
} int_sel_t;

typedef enum {
    GP_ADC_EXIN = 0,
    AD0,
    AD1,
    AD2,
    AD3,
    AD4,
    AD5,
    AD6,
    AD7,
    AD8,
    AD9,
    AD10,
    AD11,
    TSN,
    CHARGER,
    VBATTERY,
} gpadc_channel_t;

/**
 * @brief  gpadc Callback Structure definition
 */
typedef struct {
    void (*cplt_cb)(void *hgpadc);  /*!< gpadc Callback */
    void (*error_cb)(void *hgpadc); /*!< gpadc Callback */
} gpadc_cb_t;

/**
 * @brief  gpadc init handle Structure definition
 */
typedef struct {
    uint32_t channel;
    uint16_t resdiv;
    uint8_t ipclk_div;
    uint8_t mclk_div;
    uint8_t thresh;
    clk_edge_sel_t edge;
    drv_flag_status_t auto_sw;
} gpadc_init_t;

/**
 * @brief  gpadc handle Structure definition
 */
typedef struct {
    gpadc_t *instance;     /*!< Register base address */
    gpadc_init_t init;     /*!< ADC required parameters */
    dmac_handle_t *hdma;   /*!< DMA Handle parameters */
    uint32_t *buff;        /*!< Pointer to gpadc Rx Buffer */
    volatile uint32_t cnt; /*!< gpadc Rx Counter */
    drv_lock_t lock;       /*!< Locking object */
    const gpadc_cb_t *cb;  /*!< gpadc Callback */
} gpadc_handle_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  gpadc deinit
 *
 * @param  hgpadc: ADC handle
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_deinit(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc init
 *
 * @param  hgpadc: ADC handle
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_init(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc CLK enable
 *
 * @param  hgpadc: ADC handle
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_clk_enable(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc CLK disable
 *
 * @param  hgpadc: ADC handle
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_clk_disable(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc fifo flush
 *
 * @param  hgpadc: ADC handle
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_fifo_flush(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc receive or Transmit an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @param  pbuf: data buffer
 * @param  len: data length
 * @param  timeout: time-out period
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_start(gpadc_handle_t *hgpadc, uint32_t *buf, uint32_t len, uint32_t timeout);

/**
 * @brief  gpadc stop
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_stop(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc receive or Transmit an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @param  pbuf: data buffer
 * @param  len: data length
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_start_it(gpadc_handle_t *hgpadc, uint32_t *buf, uint32_t len);

/**
 * @brief  gpadc stop
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_stop_it(gpadc_handle_t *hgpadc);

/**
 * @brief  gpadc receive or Transmit an amount of data in non-blocking mode with DMA.
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @param  buf: Receive data buffer
 * @param  len: data length
 * @return drv_status_t
 * @note   Only RX mode is supported
 */
extern drv_status_t drv_gpadc_start_dma(gpadc_handle_t *hgpadc, uint32_t *buf, uint32_t len);

/**
 * @brief  gpadc stop
 *
 * @param  hgpadc: gpadc pointer to a gpadc_handle_t structure that contains the configuration information for gpadc module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_gpadc_stop_dma(gpadc_handle_t *hgpadc);

/**
 * @brief  get int status
 *
 * @param  hgpadc: ADC handle
 * @return int status
 * @note   none
 */
extern uint32_t drv_gpadc_int_status_get(gpadc_handle_t *hgpadc);

/**
 * @brief  Register a user gpadc callback
 * @param  hgpadc: ADC handle
 * @param  cb: \ref gpadc_cb_t
 * @retval drv_status_t
 */
extern drv_status_t drv_gpadc_register_cb(gpadc_handle_t *hgpadc, gpadc_cb_t *cb);

/**
 * @brief  Unregister an gpadc callback
 * @param  hgpadc: ADC handle
 * @param  cb: \ref gpadc_cb_t
 * @retval drv_status_t
 */
extern drv_status_t drv_gpadc_unregister_cb(gpadc_handle_t *hgpadc, gpadc_cb_t *cb);

/**
 * @brief  gpadc interrupt handler.
 *
 * @param  hgpadc: ADC handle
 * @return none
 * @note   none
 */
extern void drv_gpadc_irqhandler(gpadc_handle_t *hgpadc);

/**
 * @brief  Initialize the gpadc MSP.
 * @param  hgpadc: Pointer to a gpadc_handle_t structure that contains
 *         the configuration information for the specified gpadc.
 * @retval None
 */
extern void drv_gpadc_msp_init(gpadc_handle_t *hgpadc);

/**
 * @brief  DeInitialize the gpadc MSP.
 * @param  hgpadc: Pointer to a gpadc_handle_t structure that contains
 *         the configuration information for the specified gpadc.
 * @retval None
 */
extern void drv_gpadc_msp_deinit(gpadc_handle_t *hgpadc);

#ifdef __cplusplus
}
#endif

#endif

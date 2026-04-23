/*******************************************************************************************************
 *
 * @file    drv_spdif.h
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
#ifndef __DRV_SPDIF_H__
#define __DRV_SPDIF_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "tl_chip.h"
#include "inc/drv_dmac.h"
#include "reg/spdif.h"
#include <string.h>

/*************************** macro definition ********************************/
#define FIFO_ALMOST_FULL_THRESHOLD  23 /* 24 * 8 = 192 */
#define FIFO_ALMOST_EMPTY_THRESHOLD 7  /* 1 * 192 = 192 */
#define PREAMBLEDEL_NUM             3

/**************************** type definition ********************************/
typedef enum {
    SPDIF_STEREO,
    SPDIF_MONO,
} spdif_channel_mode;

typedef enum {
    SPDIF_WD_16BIT,
    SPDIF_WD_20BIT,
} spdif_wd;

typedef struct {
    uint32_t sample_fre;
    spdif_wd pcmwidth;
    spdif_channel_mode chl;
    uint8_t duplicate;
    uint8_t tx_mode;
} spdif_init_t;

/**
 * @brief  spi Callback Structure definition
 */
typedef struct {
    void (*cplt_cb)(void *hspdif);  /*!< spdif transfer complete Callback */
    void (*error_cb)(void *hspdif); /*!< spdif Callback */
    void (*event_cb)(void *hspdif); /*!< spdif Callback */
} spdif_cb_t;

typedef struct {
    spdif_reg_t *instance; /*!< spdif registers base address */
    spdif_init_t init;
    dmac_handle_t *hdma;   /*!< DMA Handle parameters */
    uint32_t *buff;        /*!< Pointer to spdif transfer Buffer */
    volatile uint16_t cnt; /*!< spdif Transfer Counter */
    const spdif_cb_t *cb;  /*!< spdif Callback */
} spdif_handle_t;

/************************* variable definition *******************************/

/*************************** function declear ********************************/

/************************ function implementation ****************************/
/**
 * @brief  spdif interrupt handler.
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @return none
 * @note   none
 */
extern void drv_spdif_irqhandler(spdif_handle_t *hspdif);

/**
 * @brief  spdif init
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_init(spdif_handle_t *hspdif);

/**
 * @brief  spdif deinit
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_deinit(spdif_handle_t *hspdif);

/**
 * @brief  spdif receive or Transmit an amount of data in non-blocking mode with Interrupt.
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @param  buf: data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_transfer_it(spdif_handle_t *hspdif, uint32_t *buf, uint32_t len);

/**
 * @brief  spdif receive or Transmit an amount of data in non-blocking mode with DMA.
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @param  buf: Receive data buffer
 * @param  len: data length. Bytes = ceil(data_width / 8) * len
 * @return drv_status_t
 * @note   Only RX mode is supported
 */
extern drv_status_t drv_spdif_transfer_dma(spdif_handle_t *hspdif, uint32_t *buf, uint32_t len);

/**
 * @brief  spdif enable
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_enable(spdif_handle_t *hspdif);

/**
 * @brief  spdif stop
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_disable(spdif_handle_t *hspdif);

/**
 * @brief  Register a User spdif Callback
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @param  cb: \ref spdif_cb_t. pCallback pointer to the Callback function
 * @retval status
 */
extern drv_status_t drv_spdif_register_cb(spdif_handle_t *hspdif, spdif_cb_t *cb);

/**
 * @brief  Unregister an spdif Callback
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @retval status
 */
extern drv_status_t drv_spdif_unregister_cb(spdif_handle_t *hspdif);

/**
 * @brief  spdif Read user information and channel status
 *
 * @param  hspdif: spdif pointer to a spdif_handle_t structure that contains the configuration information for spdif module.
 * @param  buf: data buffer
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_spdif_read_metadata(spdif_handle_t *hspdif, uint32_t *buf);

/**
 * @brief  Initialize the spdif MSP.
 * @param  hspdif: Pointer to a spdif_handle_t structure that contains
 *         the configuration information for the specified spdif.
 * @retval None
 */
extern void drv_spdif_msp_init(spdif_handle_t *hspdif);

/**
 * @brief  DeInitialize the spdif MSP.
 * @param  hspdif: Pointer to a spdif_handle_t structure that contains
 *         the configuration information for the specified spdif.
 * @retval None
 */
extern void drv_spdif_msp_deinit(spdif_handle_t *hspdif);

#endif

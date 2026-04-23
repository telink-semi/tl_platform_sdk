/*******************************************************************************************************
 *
 * @file    drv_pdm.h
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
#ifndef __DRV_PDM_H__
#define __DRV_PDM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "inc/drv_dmac.h"
#include "reg/pdm.h"

#define PDM_USER_FIFO_TRIG_LVL 0x7
#define PDM_USER_HPF_EN        0x1
#define PDM_USER_HPF_FC        0x5

#define DRV_PDM_ERROR_NONE      0x00000000U /*!< No error              */
#define DRV_PDM_ERROR_DMA       0x00000001U /*!< DMA transfer error    */
#define DRV_PDM_ERROR_TIMEOUT   0x00000002U /*!< Timeout Error         */
#define DRV_PDM_ERROR_SIZE      0x00000004U /*!< Size Management error */
#define DRV_PDM_ERROR_DMA_PARAM 0x00000008U /*!< DMA Parameter Error   */

/** @brief PDM wide. */
typedef enum {
    PDM_WD_16BIT,
    PDM_WD_20BIT,
} pdm_wd_t;

/** @brief PDM stereo mode. */
typedef enum {
    PDM_MODE_MONO,
    PDM_MODE_STEREO,
} pdm_mode_t;

typedef enum {
    PDM_SAMPLEDGE_FALL = 0,
    PDM_SAMPLEDGE_RISE,
} pdm_sampledge_t;

typedef enum {
    PDM_FIFO_STORE_NOINTERTWINE = 0,
    PDM_FIFO_STORE_INTERTWINE,
} pdm_fifo_storemode_t;

typedef void (*drv_pdm_rx_cb_t)(void *);

typedef struct {
    uint32_t audio_fre;
    pdm_wd_t pcmwidth;
    pdm_sampledge_t sampledge;
    pdm_mode_t chl;
    pdm_fifo_storemode_t store_mode; // only 16bit wide can set PDM_FIFO_STORE_INTERTWINE
} pdm_init_t;

typedef enum {
    DRV_PDM_RX_COMPLETE_CB_ID = 0,
    DRV_PDM_RX_ERROR_CB_ID = 1,
    DRV_PDM_RX_CB_ID_ALL = 2,
} drv_pdm_cb_id_type_t;

/**
 * @brief  pdm State structures definition
 */
typedef enum {
    DRV_PDM_STATE_RESET = 0x00U, /*!< PDM not yet initialized or disabled    */
    DRV_PDM_STATE_READY = 0x01U, /*!< PDM initialized and ready for use      */
    DRV_PDM_STATE_BUSY = 0x02U,  /*!< PDM process is ongoing                 */
    DRV_PDM_STATE_ERROR = 0x03U  /*!< PDM ERROR state                      */
} drv_pdm_state_t;

typedef struct {
    void (*rx_cplt_callback)(void *hpdm);    /*!< pdm receive complete callback      */
    void (*rx_error_callback)(void *hpdm);   /*!< pdm receive error callback         */
    void (*msp_init_callback)(void *hpdm);   /*!< pdm Msp Init callback              */
    void (*msp_deinit_callback)(void *hpdm); /*!< pdm Msp deinit callback            */
} pdm_handle_cb_t;

typedef struct _pdm_handle_t {
    pdm_reg_t *instance;           /*!< Pdm registers base address                               */
    pdm_init_t init;               /*!< Pdm communication parameters                             */
    uint32_t mclk;                 /*!< Pdm mclk                                                 */
    uint32_t *prxbuffptr;          /*!< Pointer to Pdm Rx transfer Buffer                        */
    uint32_t rx_xfersize;          /*!< Pdm Rx Transfer size                                     */
    DRV_IOM uint32_t rx_xfercount; /*!< Pdm Rx Transfer Counter                                  */
    dmac_handle_t *hdma_rx;        /*!< Pdm Rx DMA handle parameters                             */
    drv_lock_t lock;               /*!< Locking object                                           */
    DRV_IOM drv_pdm_state_t state; /*!< Pdm state information related to global Handle management
                    This parameter can be a value of @ref drv_pdm_state_t        */
    pdm_handle_cb_t *cb;           /*!< DMA transfer callback                                    */
    DRV_IOM uint32_t error_code;   /*!< pdm Error code                                           */
} pdm_handle_t;

/**
 * @brief  Enable pdm.
 * @param  hdma: pointer to a pdm_handle_t structure that contains
 *               the configuration information for the specified pdm.
 * @retval None
 */
extern void drv_pdm_start(pdm_handle_t *hpdm);

/**
 * @brief  Disable pdm.
 * @param  hdma: pointer to a pdm_handle_t structure that contains
 *               the configuration information for the specified pdm.
 * @retval None
 */
extern void drv_pdm_stop(pdm_handle_t *hpdm);

/**
 * @brief  Initializes the pdm according to the specified parameters
 *         in the pdm_handle_t and initialize the associated handle.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_init(pdm_handle_t *hpdm);

/**
 * @brief  DeInitialize the pdm peripheral.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *         the configuration information for the specified pdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_deinit(pdm_handle_t *hpdm);

/**
 * @brief Register callbacks
 * @param hpdm: pointer to a pdm_handle_t structure that contains
 *              the configuration information for the specified pdm handle.
 * @param cb: pointer to private callback function structure which has pointer to
 *                   a pdm_handle_cb_t structure as parameter.
 * @retval drv_status_t
 */

extern drv_status_t drv_pdm_register_cb(pdm_handle_t *hpdm, pdm_handle_cb_t *cb);

/**
 * @brief UnRegister callbacks
 * @param hpdm: pointer to a pdm_handle_t structure that contains
 *              the configuration information for the specified pdm handle.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_unregister_cb(pdm_handle_t *hpdm);

/**
 * @brief  Receive an amount of data in non-blocking mode with Interrupt
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be received
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_it_rx(pdm_handle_t *hpdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Receive pdm an amount of data in non-blocking mode with DMA
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be sent
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_recevie_dma(pdm_handle_t *hpdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Set the DMA llp head node according to the specified
 *         parameters in the node.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_recevie_dma_llp_head_set(pdm_handle_t *hpdm, dmac_llp_node_t *node);

/**
 * @brief  Add the DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_list: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_recevie_dma_llp_node_add(pdm_handle_t *hpdm, dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t *buffer, uint32_t len);

/**
 * @brief  Start the DMA llp Transfer.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *                the configuration information for the specified pdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_pdm_recevie_dma_llp_start(pdm_handle_t *hpdm, drv_flag_status_t int_en);

/**
 * @brief  Initialize the pdm MSP.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *         the configuration information for the specified pdm.
 * @retval None
 */
extern void drv_pdm_msp_init(pdm_handle_t *hpdm);

/**
 * @brief  DeInitialize the pdm MSP.
 * @param  hpdm Pointer to a pdm_handle_t structure that contains
 *         the configuration information for the specified pdm.
 * @retval None
 */
extern void drv_pdm_msp_deinit(pdm_handle_t *hpdm);

/**
 * @brief  Handles pdm interrupt request.
 * @param  hdma: pointer to a pdm_handle_t structure that contains
 *               the configuration information for the specified pdm.
 * @retval None
 */
extern void drv_pdm_irqhandle(pdm_handle_t *hpdm);

#ifdef __cplusplus
}
#endif

#endif

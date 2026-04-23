/*******************************************************************************************************
 *
 * @file    drv_tdm.h
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
#ifndef __DRV_TDM_H__
#define __DRV_TDM_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "reg/tdm.h"
#include "inc/drv_dmac.h"

/*************************** macro definition ********************************/
#define TDM_LINE0_TX (0x0 << 0)
#define TDM_LINE0_RX (0x1 << 0)
#define TDM_LINE1_TX (0x0 << 1)
#define TDM_LINE1_RX (0x1 << 1)
#define TDM_LINE2_TX (0x0 << 2)
#define TDM_LINE2_RX (0x1 << 2)
#define TDM_LINE3_TX (0x0 << 3)
#define TDM_LINE3_RX (0x1 << 3)

#define TDM_LINE0_EN (0x1 << 0)
#define TDM_LINE1_EN (0x1 << 1)
#define TDM_LINE2_EN (0x1 << 2)
#define TDM_LINE3_EN (0x1 << 3)

/* define INT */
#define TDM_TX_FIFO_LVL (16)
#define TDM_RX_FIFO_LVL (16)

#define TDM_FIFO_STA_TXFIFO_EMPTY  (0x01 << 9)
#define TDM_FIFO_STA_TXFIFO_AEMPTY (0x01 << 8)

#define DRV_TDM_STATE_RESET   0x0000U /*!< TDM not yet initialized or disabled                */
#define DRV_TDM_STATE_READY   0x0001U /*!< TDM initialized and ready for use                  */
#define DRV_TDM_STATE_BUSY    0x0002U /*!< TDM initialized and ready for use                  */
#define DRV_TDM_STATE_BUSY_TX 0x0004U /*!< Data Transmission process is ongoing               */
#define DRV_TDM_STATE_BUSY_RX 0x0008U /*!< Data Reception process is ongoing                  */
#define DRV_TDM_STATE_TIMEOUT 0x0010U /*!< TDM timeout state                                  */
#define DRV_TDM_STATE_ERROR   0x0020U /*!< TDM error state                                    */

#define DRV_TDM_ERROR_NONE      (0x00000000U) /*!< No error                    */
#define DRV_TDM_ERROR_TIMEOUT   (0x00000001U) /*!< Timeout error               */
#define DRV_TDM_ERROR_OVR       (0x00000002U) /*!< OVR error                   */
#define DRV_TDM_ERROR_UDR       (0x00000004U) /*!< UDR error                   */
#define DRV_TDM_ERROR_DMA       (0x00000008U) /*!< DMA transfer error          */
#define DRV_TDM_ERROR_DMA_PARAM (0x00000010U) /*!< Busy Rx Line error          */
/**************************** type definition ********************************/

typedef enum {
    TDM_TRANS_DRIVE_DATA_AT_SAME_EDGE,
    TDM_TRANS_DRIVE_DATA_NOT_AT_SAME_EDGE,
} tdm_edgetransfer_t;

typedef enum {
    TDM_PADDING_0_AT_LSB,
    TDM_SIGN_EXTENSION_AT_MSB,
} tdm_dataextention_t;

typedef enum {
    TDM_SLOT_RESOLUTION_NA,
    TDM_SLOT_RESOLUTION_8_BITS,
    TDM_SLOT_RESOLUTION_12_BITS,
    TDM_SLOT_RESOLUTION_16_BITS,
    TDM_SLOT_RESOLUTION_20_BITS,
    TDM_SLOT_RESOLUTION_24_BITS,
    TDM_SLOT_RESOLUTION_28_BITS,
    TDM_SLOT_RESOLUTION_32_BITS,
} tdm_slotresolution_t;

typedef enum {
    TDM_1_SLOT_USED,
    TDM_2_SLOT_USED,
    TDM_3_SLOT_USED,
    TDM_4_SLOT_USED,
    TDM_5_SLOT_USED,
    TDM_6_SLOT_USED,
    TDM_7_SLOT_USED,
    TDM_8_SLOT_USED,
} tdm_slotnum_t;

typedef enum {
    TDM_SLOT_W_NA,
    TDM_SLOT_W_8_BITS,
    TDM_SLOT_W_12_BITS,
    TDM_SLOT_W_16_BITS,
    TDM_SLOT_W_20_BITS,
    TDM_SLOT_W_24_BITS,
    TDM_SLOT_W_28_BITS,
    TDM_SLOT_W_32_BITS,
} tdm_slotwidth_t;

typedef enum {
    TDM_MODE,
    I2S_MODE,
} tdm_modeselect_t;

typedef enum {
    TDM_WS_SIGNAL_1_SCLK_CYCLE,
    TDM_WS_SIGNAL_2_SCLK_CYCLE,
} tdm_wssignalwidth_t;

typedef enum {
    TDM_WS_0_LEFT_CH_WS_1_RIGHT_CH,
    TDM_WS_1_LEFT_CH_WS_0_RIGHT_CH,
} tdm_wspolarityi2s_t;

typedef enum {
    TDM_WS_ALIG_TO_SCLK_N_EDGE,
    TDM_WS_ALIG_TO_SCLK_P_EDGE,
} tdm_wspolaritytdm_t;

typedef enum {
    TDM_WS_FORMAT_I2S_STANDARD,
    TDM_WS_FORMAT_I2S_LEFT_JUSTIFIED,
    TDM_WS_FORMAT_I2S_RIGHT_JUSTIFIED,
    TDM_WS_FORMAT_NA,
} tdm_wsformati2s_t;

typedef enum {
    TDM_WS_FORMAT_STANDARD_DSP,
    TDM_WS_FORMAT_LEFT_JUSTIFIED,
} tdm_wsformattdm_t;

typedef enum {
    TDM_SCLK_DRV_DATA_AT_P_EDGE,
    TDM_SCLK_DRV_DATA_AT_N_EDGE,
} tdm_sclkpolarity_t;

typedef enum {
    TDM_SLAVE_MODE,
    TDM_MASTER_MODE,
} tdm_masteren_t;

typedef enum {
    TDM_INT_RXFIFO_DATA_READY,
    TDM_INT_RXFIFO_OVERFLOW,
    TDM_INT_RXFIFO_UNDERFLOW,
    TDM_INT_TXFIFO_DATA_READY,
    TDM_INT_TXFIFO_OVERFLOW,
    TDM_INT_TXFIFO_UNDERFLOW,
} tdm_int_id_t;

/* config type define */
typedef struct tdm_ch_cfg {
    uint8_t ch_trx : 4; /* each bit for one channel,[ch3,ch2,ch1,ch0],0 for tx,1 for rx */
    uint8_t ch_en  : 4; /* each bit for one channel,[ch3,ch2,ch1,ch0],0 for disable,1 for enable */
} tdm_ch_cfg_t;

typedef struct {
    tdm_ch_cfg_t ch_cfg;
    tdm_wspolarityi2s_t ws_polarity;
    tdm_wsformati2s_t ws_format;
} tdm_i2s_mode_cfg_t;

typedef struct {
    tdm_slotnum_t slot_num;
    tdm_wssignalwidth_t ws_width;
    tdm_wspolaritytdm_t ws_polarity;
    tdm_wsformattdm_t ws_format;
    uint8_t tx_en : 1;
    uint8_t rx_en : 1;
} tdm_tdm_mode_cfg_t;

typedef struct {
    tdm_modeselect_t mode;
    tdm_slotresolution_t slot_resolution;
    tdm_slotwidth_t slot_width;
    tdm_sclkpolarity_t sclk_polarity;
    tdm_masteren_t master_mode;
    uint32_t audio_fre;
    union {
        tdm_i2s_mode_cfg_t i2s_cfg;
        tdm_tdm_mode_cfg_t tdm_cfg;
    } mode_cfg;

} tdm_init_t;

typedef struct {
    void (*tx_cplt_callback)(void *htdm);    /*!< tdm transfer complete callback     */
    void (*tx_error_callback)(void *htdm);   /*!< tdm transfer error callback        */
    void (*rx_cplt_callback)(void *htdm);    /*!< tdm receive complete callback      */
    void (*rx_error_callback)(void *htdm);   /*!< tdm receive error callback         */
    void (*msp_init_callback)(void *htdm);   /*!< tdm Msp Init callback              */
    void (*msp_deinit_callback)(void *htdm); /*!< tdm Msp deinit callback            */
} tdm_handle_cb_t;

typedef struct _tdm_handle_t {
    tdm_reg_t *instance;           /*!< Tdm registers base address                               */
    tdm_init_t init;               /*!< Tdm communication parameters                             */
    uint32_t *ptxbuffptr;          /*!< Pointer to Tdm Tx transfer Buffer                        */
    uint32_t tx_xfersize;          /*!< Tdm Tx Transfer size                                     */
    DRV_IOM uint32_t tx_xfercount; /*!< Tdm Tx Transfer Counter                                  */
    uint32_t *prxbuffptr;          /*!< Pointer to Tdm Rx transfer Buffer                        */
    uint32_t rx_xfersize;          /*!< Tdm Rx Transfer size                                     */
    DRV_IOM uint32_t rx_xfercount; /*!< Tdm Rx Transfer Counter                                  */
    dmac_handle_t *hdma_tx;        /*!< Tdm Rx DMA handle parameters                             */
    dmac_handle_t *hdma_rx;        /*!< Tdm Rx DMA handle parameters                             */
    drv_lock_t lock;               /*!< Locking object                                           */
    DRV_IOM uint32_t state;        /*!< Tdm state information related to global Handle management*/
    tdm_handle_cb_t *cb;           /*!< DMA transfer callback                                    */
    DRV_IOM uint32_t error_code;   /*!< Tdm Error code                                           */
} tdm_handle_t;
/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  Enable tdm.
 * @param  htdm: pointer to a tdm_handle_t structure that contains
 *               the configuration information for the specified tdm.
 * @retval None
 */
extern void drv_tdm_start(tdm_handle_t *htdm);

/**
 * @brief  Disable tdm.
 * @param  htdm: pointer to a tdm_handle_t structure that contains
 *               the configuration information for the specified tdm.
 * @retval None
 */
extern void drv_tdm_stop(tdm_handle_t *htdm);

/**
 * @brief  Initializes the tdm according to the specified parameters
 *         in the tdm_handle_t and initialize the associated handle.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *                the configuration information for the specified tdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_init(tdm_handle_t *htdm);

/**
 * @brief  DeInitialize the tdm peripheral.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_deinit(tdm_handle_t *htdm);

/**
 * @brief Register callbacks
 * @param htdm: pointer to a tdm_handle_t structure that contains
 *              the configuration information for the specified tdm handle.
 * @param cb: pointer to private callback function structure which has pointer to
 *                   a tdm_handle_cb_t structure as parameter.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_register_cb(tdm_handle_t *htdm, tdm_handle_cb_t *cb);

/**
 * @brief UnRegister callbacks
 * @param htdm: pointer to a tdm_handle_t structure that contains
 *              the configuration information for the specified tdm handle.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_unregister_cb(tdm_handle_t *htdm);

/**
 * @brief  Transfer an amount of data in non-blocking mode with Interrupt
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *                the configuration information for the specified tdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be sent
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_it_tx(tdm_handle_t *htdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Receive an amount of data in non-blocking mode with Interrupt
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *                the configuration information for the specified tdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be received
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_it_rx(tdm_handle_t *htdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Receive tdm an amount of data in non-blocking mode with DMA
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *                the configuration information for the specified tdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be sent
 * @retval drv_status_t
 */
drv_status_t drv_tdm_recevie_dma(tdm_handle_t *htdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Transfer an amount of data in non-blocking mode with DMA
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *                the configuration information for the specified tdm.
 * @param  p_data Pointer to data buffer
 * @param  size Amount of data to be sent
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_transfer_dma(tdm_handle_t *htdm, uint32_t *p_data, uint32_t size);

/**
 * @brief  Set the DMA llp head node according to the specified
 *         parameters in the node.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_transfer_dma_llp_head_set(tdm_handle_t *htdm, dmac_llp_node_t *node);

/**
 * @brief  Set the DMA llp head node according to the specified
 *         parameters in the node.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_recevie_dma_llp_head_set(tdm_handle_t *htdm, dmac_llp_node_t *node);

/**
 * @brief  Add the DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_list: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_transfer_dma_llp_node_add(tdm_handle_t *htdm, dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t *buffer, uint32_t len);

/**
 * @brief  Add the DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_list: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_recevie_dma_llp_node_add(tdm_handle_t *htdm, dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t *buffer, uint32_t len);

/**
 * @brief  Start the DMA llp Transfer.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_transfer_dma_llp_start(tdm_handle_t *htdm, drv_flag_status_t int_en);

/**
 * @brief  Start the DMA llp Transfer.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @retval drv_status_t
 */
extern drv_status_t drv_tdm_recevie_dma_llp_start(tdm_handle_t *htdm, drv_flag_status_t int_en);

/**
 * @brief  Initialize the tdm MSP.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @retval None
 */
extern void drv_tdm_msp_init(tdm_handle_t *htdm);

/**
 * @brief  DeInitialize the tdm MSP.
 * @param  htdm Pointer to a tdm_handle_t structure that contains
 *         the configuration information for the specified tdm.
 * @retval None
 */
extern void drv_tdm_msp_deinit(tdm_handle_t *htdm);

/**
 * @brief  Handles tdm interrupt request.
 * @param  hdma: pointer to a tdm_handle_t structure that contains
 *               the configuration information for the specified tdm.
 * @retval None
 */
extern void drv_tdm_irqhandle(tdm_handle_t *htdm);
#ifdef __cplusplus
}
#endif

#endif

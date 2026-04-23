/*******************************************************************************************************
 *
 * @file    drv_dmac.h
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
#ifndef __DRV_DMAC_H__
#define __DRV_DMAC_H__

/**************************** include header *********************************/

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "reg/dma.h"
#include "tl_chip.h"
#define DMA_TRX_MAX_LEN 4095

/** @defgroup DMA_Error_Code DMA Error Code
 * @{
 */
#define DRV_DMA_ERROR_NONE          0x00000000U /*!< No error             */
#define DRV_DMA_ERROR_TE            0x00000001U /*!< Transfer error       */
#define DRV_DMA_ERROR_NO_XFER       0x00000004U /*!< no ongoing transfer  */
#define DRV_DMA_ERROR_TIMEOUT       0x00000020U /*!< Timeout error        */
#define DRV_DMA_ERROR_NOT_SUPPORTED 0x00000100U /*!< Not supported mode   */

#define __DRV_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__) \
    do {                                                             \
        (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__);         \
        (__DMA_HANDLE__).parent = (__HANDLE__);                      \
    } while (0U)

typedef uint64_t dmac_io_t;

#define __DRV_DMAC_CHANNEL_ENABLE(__HANDLE__)                                                                                                                  \
    do {                                                                                                                                                       \
        (__HANDLE__)->instance->DMAC_CHENREG = (dmac_io_t)1UL << (__HANDLE__->init.channel + DMA_CHANNEL_OFFSET) | (dmac_io_t)1UL << __HANDLE__->init.channel; \
    } while (0)

#define __DRV_DMAC_CHANNEL_DISABLE(__HANDLE__)                                                                    \
    do {                                                                                                          \
        (__HANDLE__)->instance->DMAC_CHENREG = (dmac_io_t)1UL << (__HANDLE__->init.channel + DMA_CHANNEL_OFFSET); \
    } while (0)

/**************************** type definition ********************************/
typedef void (*dmac_ch_irq_hook_t)(void *arg);

typedef enum {
    DMAC_CTL_TT_MEM2MEM = 0,
    DMAC_CTL_TT_MEM2PER,
    DMAC_CTL_TT_PER2MEM,
    DMAC_CTL_TT_PER2PER,
} dmac_trans_mode_t;

typedef enum {
    DMAC_MSIZE_1 = 0,
    DMAC_MSIZE_4,
    DMAC_MSIZE_8,
    DMAC_MSIZE_16,
    DMAC_MSIZE_32,
    DMAC_MSIZE_64,
    DMAC_MSIZE_128,
    DMAC_MSIZE_256,
} dmac_msize_t;

typedef enum {
    DMAC_ADDR_INCREASE = 0,
    DMAC_ADDR_DECREASE,
    DMAC_ADDR_CONSTANT,
} dmac_inc_t;

typedef enum {
    DMAC_TR_WIDTH_8BITS = 0,
    DMAC_TR_WIDTH_16BITS,
    DMAC_TR_WIDTH_32BITS,
    DMAC_TR_WIDTH_64BITS,
    DMAC_TR_WIDTH_128BITS,
    DMAC_TR_WIDTH_256BITS,
} dmac_tr_width_t;

typedef enum {
    DMAC_CFG_HS_SEL_HARD = 0,
    DMAC_CFG_HS_SEL_SOFT,
} dmac_hs_mode_t;

typedef enum {
    DMAC_CH_PRIOR_0 = 0,
    DMAC_CH_PRIOR_1,
    DMAC_CH_PRIOR_2,
    DMAC_CH_PRIOR_3,
    DMAC_CH_PRIOR_4,
    DMAC_CH_PRIOR_5,
    DMAC_CH_PRIOR_6,
    DMAC_CH_PRIOR_7,
} dmac_ch_prior_t;

typedef enum {
    DMAC_TFR_INTR = 0,
    DMAC_BLOCK_INTR,
    DMAC_SRCT_INTR,
    DMAC_DSTT_INTR,
    DMAC_ERR_INTR,
    DMAC_MAX_INTR,
} dmac_intr_type_t;

typedef enum {
    DMAC_CH_FREE = 0,
    DMAC_CH_RUNNING,
} dmac_ch_status_t;

/**
 * @brief  HAL DMA State structures definition
 */
typedef enum {
    DRV_DMA_STATE_RESET = 0x00U,  /*!< DMA not yet initialized or disabled    */
    DRV_DMA_STATE_READY = 0x01U,  /*!< DMA initialized and ready for use      */
    DRV_DMA_STATE_BUSY = 0x02U,   /*!< DMA process is ongoing                 */
    DRV_DMA_STATE_TIMEOUT = 0x03U /*!< DMA timeout state                      */
} drv_dmac_state_t;

/**
 * @brief  HAL DMA Callback ID structure definition
 */
typedef enum {
    DRV_DMA_SRC_XFER_CPLT_CB_ID       = 0x00U,    /*!< SRC transfer     */
    DRV_DMA_DST_XFER_CPLT_CB_ID       = 0x01U,    /*!< DST transfer     */
    DRV_DMA_BLOCK_XFER_CPLT_CB_ID     = 0x02U,    /*!< BLOCK transfer    */
    DRV_DMA_XFER_CPLT_CB_ID           = 0x03U,    /*!< Full transfer     */
    DRV_DMA_XFER_ERROR_CB_ID          = 0x04U,    /*!< Error             */
    DRV_DMA_XFER_SUSPEND_CB_ID        = 0x05U,    /*!< Suspend           */
    DRV_DMA_XFER_ALL_CB_ID            = 0x06U     /*!< All               */
} drv_dmac_cb_id_type_t;

typedef struct {
    uint32_t srcx;
    uint32_t darx;
    uint32_t llpx;
    uint32_t ctlx_l;
    uint32_t ctlx_h;
    uint32_t sstat;
    uint32_t dstat;
}dmac_llp_node_t;

/**
 * @brief  DMA init Structure definition
 */
typedef struct {
    uint32_t channel;                /*!< Specifies the channel used for the specified stream.
                                          This parameter can be a value of dma channel selection                                     */
    dmac_tr_width_t src_bus_width;   /*!< Specifies Source Transfer Width.Mapped to AHB bus hsize For a non-memory peripheral,
                                          typically the peripheral (source)FIFO width.                                               */
    dmac_tr_width_t dst_bus_width;   /*!< Specifies Destination Transfer Width.Mapped to AHB bus hsize For a non-memory peripheral,
                                          typically the peripheral (source)FIFO width.                                               */
    dmac_msize_t src_burst_size;     /*!< Specifies the Source Burst transfer configuration for the peripheral transfers.
                                          It specifies the amount of data to be transferred in a single non interruptible
                                          transaction.This parameter can be a value of @ref dmac_msize_t                             */
    dmac_msize_t dst_burst_size;     /*!< Specifies the Destination Burst transfer configuration for the peripheral transfers.
                                          It specifies the amount of data to be transferred in a single non interruptible
                                          transaction.This parameter can be a value of @ref dmac_msize_t                             */
    dmac_inc_t src_addr_change_mode; /*!< Specifies whether the Source Peripheral address register should be incremented or not.
                                          This parameter can be a value of @ref dmac_inc_t                                           */
    dmac_inc_t dst_addr_change_mode; /*!< Specifies whether the Destination Peripheral address register should be incremented or not.
                                          This parameter can be a value of @ref dmac_inc_t                                           */
    dmac_hs_mode_t src_hs_mode;      /*!< Specifies Source Software or Hardware Handshaking Select.Thisregister selects 
                                          which of the handshaking interfaceshardware or software-is active for source requestson
                                          this channel.lf the source peripheral is memory, then this bit is ignored.                 */
    dmac_hs_mode_t dst_hs_mode;      /*!< Specifies Destination Software or Hardware Handshaking Select.Thisregister selects 
                                          which of the handshaking interfaceshardware or software-is active for source requestson
                                          this channel.lf the source peripheral is memory, then this bit is ignored.                 */
    uint32_t src_hs_num;             /*!< Specifies Source Hardware interface.Assigns a hardware handshaking interface to the      
                                          source of channel if the src_hs_mode field is DMAC_CFG_HS_SEL_HARD; otherwise, this field 
                                          isignored. The channel can then communicate with the source peripheral connected to that 
                                          interface through theassigned hardware handshaking interface.
                                          NOTE: For correct DW ahb dmac operation, only one peripheral (source or destination) 
                                          should be assigned to the same handshaking interface.                                      */
    uint32_t dst_hs_num;             /*!< Specifies Destination Hardware interface.Assigns a hardware handshaking interface to the      
                                          destination of channel if the dst_hs_mode field is DMAC_CFG_HS_SEL_HARD; otherwise, this field 
                                          isignored. The channel can then communicate with the destination peripheral connected to that 
                                          interface through theassigned hardware handshaking interface.
                                          NOTE: For correct DW ahb dmac operation, only one peripheral (source or destination) 
                                          should be assigned to the same handshaking interface.                                      */
    dmac_trans_mode_t trans_mode;    /*!< Specifies Transfer Type and Flow Control. Flow control can beassigned to the DW ahb dmac,
                                          the source peripheral, or the destination peripheral.                                      */
    uint32_t fifo_mode;              /*!< Specifies FlFO Mode Select.Determines how much space data needs to be available in the 
                                          FlFO before a burst transaction request is serviced.                                       */
    uint32_t src_llp_en;              /*!< Specifies src llp Select.                                                                 */
    uint32_t dst_llp_en;              /*!< Specifies dst llp Select.                                                                 */
} dmac_init_t;

/**
 * @brief  DMA handle Structure definition
 */
typedef struct _dma_handle_t {
    dmac_reg_t *instance;                                          /*!< Register base address                  */
    dmac_init_t init;                                              /*!< DMA communication parameters           */
    drv_lock_t lock;                                               /*!< DMA locking object                     */
    DRV_IOM drv_dmac_state_t state;                                /*!< DMA transfer state                     */
    void *parent;                                                  /*!< Parent object state                    */
    void (*src_xfer_cplt_callback)(struct _dma_handle_t *hdma);    /*!< DMA transfer complete callback         */
    void (*dst_xfer_cplt_callback)(struct _dma_handle_t *hdma);    /*!< DMA transfer complete callback         */
    void (*block_xfer_cplt_callback)(struct _dma_handle_t *hdma);  /*!< DMA transfer complete callback         */
    void (*xfer_cplt_callback)(struct _dma_handle_t *hdma);        /*!< DMA transfer complete callback         */
    void (*xfer_suspend_callback)(struct _dma_handle_t *hdma);     /*!< DMA transfer complete callback         */
    void (*xfer_error_callback)(struct _dma_handle_t *hdma);       /*!< DMA transfer error callback            */
    DRV_IOM uint32_t error_code;                                   /*!< DMA Error code                         */
    dmac_channel_reg_t *channel_address;                           /*!< DMA channel Base Address               */
} dmac_handle_t;

/**
 * @brief  Initialize the DMA according to the specified
 *         parameters in the dmac_init_t and initialize the associated handle.
 * @param  hdma: Pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_init(dmac_handle_t *hdma);

/**
 * @brief  Set the DMA llp head node according to the specified
 *         parameters in the node.
 * @param  hdma: Pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_llp_head_set(dmac_handle_t *hdma, dmac_llp_node_t *node);

/**
 * @brief  Add the DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  hdma: Pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_list: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_llp_node_add(dmac_handle_t *hdma, dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t src_address, uint32_t dst_address, uint32_t len);

/**
 * @brief  DeInitialize the DMA peripheral.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_deinit(dmac_handle_t *hdma);

/**
 * @brief  Start the DMA Transfer.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  src_address: The source memory Buffer address
 * @param  dst_address: The destination memory Buffer address
 * @param  data_length: The length of data to be transferred from source to destination
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_start(dmac_handle_t *hdma, uint32_t src_address, uint32_t dst_address, uint32_t data_length);

/**
 * @brief  Start the DMA Transfer with interrupt enabled.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  src_address: The source memory Buffer address
 * @param  dst_address: The destination memory Buffer address
 * @param  data_length: The length of data to be transferred from source to destination
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_start_it(dmac_handle_t *hdma, uint32_t src_address, uint32_t dst_address, uint32_t data_length);

/**
 * @brief  Start the DMA llp Transfer.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  int_en: block transfer complete int en
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_llp_start(dmac_handle_t *hdma, uint32_t block_int_en, uint32_t tfr_int_en);

/**
 * @brief  Get llp item transfer state.
 * @param  item: pointer to a dmac_lli_node_t structure
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_llp_item_transfer_cplt(dmac_llp_node_t *node);

/**
 * @brief  Clear llp item transfer state.
 * @param  item: pointer to a dmac_lli_node_t structure
 * @retval drv_status_t
 */
drv_status_t drv_dmac_llp_item_transfer_cplt_clr(dmac_llp_node_t *node);

/**
 * @brief  Suspend the DMA Transfer in Interrupt mode.
 * @param  hdma  : pointer to a dmac_handle_t structure that contains
 *                 the configuration information for the specified DMA Channel.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_suspend(dmac_handle_t *hdma);

/**
 * @brief  Polling for transfer complete.
 * @param  hdma:    pointer to a dmac_handle_t structure that contains
 *                  the configuration information for the specified DMA Channel.
 * @param  timeout:       Timeout duration.
 * @retval drv_status_t
*/
drv_status_t drv_dmac_poll_for_transfer(dmac_handle_t *hdma, uint32_t timeout);

/**
 * @brief Register callbacks
 * @param hdma: pointer to a dmac_handle_t structure that contains
 *              the configuration information for the specified DMA Channel.
 * @param cb_id: User Callback identifier
 *                    a drv_dmac_cb_id_type_t ENUM as parameter.
 * @param cb: pointer to private callback function which has pointer to
 *                   a dmac_handle_t structure as parameter.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_register_cb(dmac_handle_t *hdma, drv_dmac_cb_id_type_t cb_id, void (*cb)(dmac_handle_t *_hdma));

/**
 * @brief UnRegister callbacks
 * @param hdma: pointer to a dmac_handle_t structure that contains
 *              the configuration information for the specified DMA Channel.
 * @param cb_id: User Callback identifier
 *                    a drv_dmac_cb_id_type_t ENUM as parameter.
 * @retval drv_status_t
 */
extern drv_status_t drv_dmac_unregister_cb(dmac_handle_t *hdma, drv_dmac_cb_id_type_t cb_id);

/**
 * @brief  Handles DMA interrupt request.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @retval None
 */
extern void drv_dmac_irq_handle(dmac_handle_t *hdma);

/**
 * @brief  Return the DMA source memory address.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @retval uint32_t:The dma source memory address
 */
uint32_t drv_dmac_get_src_address(dmac_handle_t *hdma);

/**
 * @brief  Return the DMA destination memory address.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @retval uint32_t:The dma destination memory address
 */
uint32_t drv_dmac_get_dst_address(dmac_handle_t *hdma);

/**
 * @brief  Return the DMA source memory address.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  src_address: The source memory Buffer address
 * @retval None
 */
void drv_dmac_set_src_address(dmac_handle_t *hdma, uint32_t src_address);

/**
 * @brief  Return the DMA destination memory address.
 * @param  hdma: pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  dst_address: The destination memory Buffer address
 * @retval None
 */
void drv_dmac_set_dst_address(dmac_handle_t *hdma, uint32_t dst_address);

#ifdef __cplusplus
}
#endif

#endif

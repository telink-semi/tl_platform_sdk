/*******************************************************************************************************
 *
 * @file    drv_ipcm.h
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
#ifndef __DRV_IPCM_H__
#define __DRV_IPCM_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "tl_chip.h"
#include "reg/ipcm.h"

/**************************** macro definition *******************************/

/**************************** type definition ********************************/
typedef enum {
    IPCM_CPU_0,
    IPCM_CPU_1,
    IPCM_CPU_2,
    IPCM_CPU_MAX,
} ipcm_cpu_id_t;

typedef struct {
    ipcm_cpu_id_t cpux;
    uint32_t msg_addr;
} ipcm_msg_t;

typedef void (*ipcm_cb)(ipcm_cpu_id_t cpux, uint32_t msg_addr);
typedef void (*ipcm_ack_cb)(ipcm_cpu_id_t cpux);
typedef struct {
    uint32_t resv; /* reserved for future use */
} ipcm_init_t;

/**
 * @brief  resample handle Structure definition
 */
typedef struct {
    ipcm_reg_t *instance; /*!< ipcm base address */
    ipcm_init_t init;     /*!< ipcm required parameters */
    drv_lock_t lock;      /*!< Locking object */
    ipcm_cb cb;           /*!< ipcm Callback */
    ipcm_ack_cb ack_cb;
} ipcm_handle_t;

/************************** variable declear ******************************/

/**************************** function declear *******************************/

/************************ function implementation ****************************/
/**
 * @brief  ipcm deinit
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_deinit(ipcm_handle_t *hipcm);
/**
 * @brief  ipcm init
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_init(ipcm_handle_t *hipcm);
/**
 * @brief  ipcm send a message
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @param  cpux: Message target CPU
 * @param  msg_addr: Message address
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_send_msg(ipcm_handle_t *hipcm, ipcm_cpu_id_t cpux, uint32_t msg_addr);
/**
 * @brief  ipcm send a message without blocking
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @param  cpux: Message target CPU
 * @param  msg_addr: Message address
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_async_send_msg(ipcm_handle_t *hipcm, ipcm_cpu_id_t target_cpu, uint32_t msg_addr);
/**
 * @brief  ipcm send an acknowledge signal
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @param  cpux: Message target CPU
 * @return drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_send_ack(ipcm_handle_t *hipcm, ipcm_cpu_id_t target_cpu);
/**
 * @brief  Register a User ipcm Callback
 *         To be used instead of the weak predefined callback
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @param  cb: pCallback pointer to the Callback function
 * @retval drv_status_t
 * @note   none
 */
extern drv_status_t drv_ipcm_register_cb(ipcm_handle_t *hipcm, ipcm_cb cb);
/**
 * @brief  Register a User ipcm Acknowledge Callback
 *         To be used instead of the weak predefined callback
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *        the configuration information for the specified ipcm.
 *  @param  cb: pCallback pointer to the Callback function
 * @retval drv_status_t
 */
extern drv_status_t drv_ipcm_register_ack_cb(ipcm_handle_t *hipcm, ipcm_ack_cb cb);
/**
 * @brief  Unregister an ipcm Callback
 *         ipcm callaback is redirected to the weak predefined callback
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 * @retval status
 * @note   none
 */
extern drv_status_t drv_ipcm_unregister_cb(ipcm_handle_t *hipcm);
/**
 * @brief  ipcm interrupt handler.
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @return none
 * @note   none
 */
extern void drv_ipcm_irqhandler(ipcm_handle_t *hipcm);
/**
 * @brief  ipcm get vector
 *
 * @param  hipcm: Pointer to a ipcm_handle_t structure that contains
 *         the configuration information for the specified ipcm.
 * @param  cpux: Message target CPU
 * @param  msg_addr: Message address
 * @return uint32_t
 * @note   none
 */
extern uint32_t drv_ipcm_get_vector(ipcm_handle_t *hipcm, ipcm_cpu_id_t target_cpu);

#ifdef __cplusplus
}
#endif

#endif

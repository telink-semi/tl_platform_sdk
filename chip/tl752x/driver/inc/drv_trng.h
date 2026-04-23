/*******************************************************************************************************
 *
 * @file    drv_trng.h
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
#ifndef __DRV_TRNG_H__
#define __DRV_TRNG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "reg/trng.h"
#include "tl_chip.h"

//ENTROPY_SRC_NUM_EN
#define TRNG_ENTROPY_SRC_0_EN                (8UL)
#define TRNG_ENTROPY_SRC_1_EN                (4U)
#define TRNG_ENTROPY_SRC_2_EN                (2UL)
#define TRNG_ENTROPY_SRC_3_EN                (1UL)

//TRNG_MODE
#define TRNG_MODE_TRUE_RANDOM                0U
#define TRNG_MODE_FALSE_RANDOM               1U

//SAMPLE_CLOCK
#define TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_4     0U
#define TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_8     1U
#define TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_16    2U
#define TRNG_SAMPLE_CLOCK_IS_INPUT_DIV_32    3U

//CLOCK_SRC
#define TRNG_CLOCK_SRC_RO                    0U
#define TRNG_CLOCK_SRC_SYSTEM                1U

typedef struct {
    uint32_t ro_entropy_src_sel;//@ref ENTROPY_SRC_NUM_EN
    uint32_t trng_mode;//@ref TRNG_MODE
    uint32_t sample_clock; //@ref SAMPLE_CLOCK
    uint32_t clock_src; //@ref CLOCK_SRC
    uint32_t (*trng_ctrl_port_read)(void);
    void (*trng_ctrl_port_write)(uint32_t val);
} trng_init_t;

typedef struct __trng_handle_t {
    trng_reg_t *instance;
    trng_init_t init;
    uint32_t *pbuffptr;
    uint32_t xfersize;
    DRV_IOM uint32_t xfercount;
    drv_lock_t lock;
    void (*it_complate_callback)(struct __trng_handle_t *htrng);
} trng_handle_t;

typedef void (*ptrng_callback_t)(trng_handle_t *htrng); /*!< pointer to an TRNG callback function */

/**
 * @brief  Initializes the trng mode according to the specified parameters in
 *          the trng_handle_t and create the associated handle.
 * @param  {trng_handle_t} *htrng, Pointer to a trng_handle_t structure that
 *          contains the configuration information for the specified TRNG module.
 * @retval drv_status_t
 */
extern drv_status_t drv_trng_init(trng_handle_t *htrng);

/**
 * @brief get an amount of ramdom data in blocking mode.
 * @param {trng_handle_t} *htrng,Pointer to a trng_handle_t structure that contains
 *         the configuration information for the specified TRNG module.
 * @param {uint32_t} *pdata, Pointer to data buffer
 * @param {uint32_t} size, Amount of data elements
 * @param {uint32_t} timeout, Timeout duration
 * @retval drv_status_t
 */
extern drv_status_t drv_trng_get_ro_random(trng_handle_t *htrng, uint32_t *pdata, uint32_t size, uint32_t timeout);

/**
 * @brief get an amount of ramdom data in non blocking mode.
 * @param {trng_handle_t} *htrng,Pointer to a trng_handle_t structure that contains
 *         the configuration information for the specified TRNG module.
 * @param {uint32_t} *pdata, Pointer to data buffer
 * @param {uint32_t} size, Amount of data elements
 * @retval drv_status_t
 */
extern drv_status_t drv_trng_get_ro_random_it(trng_handle_t *htrng, uint32_t *pdata, uint32_t size);

/**
 * @brief: htrng irq handler
 * @param  htrng Pointer to a trng_handle_t structure that contains
 *               the configuration information for the specified TRNG module.
 * @retval {none}
 */
extern void drv_trng_irq_handler(trng_handle_t *htrng);

/**
  * @brief  Register a User TRNG Callback
  * @param  htrng trng handle
  * @param  pCallback pointer to the Callback function
  * @retval none
  */
extern void drv_trng_register_callback(trng_handle_t *htrng,  ptrng_callback_t pcallback);
/**
  * @brief  unRegister a User trng Callback
  * @param  htrng trng handle
  * @retval none
  */
extern void drv_trng_unregister_callback(trng_handle_t *htrng);

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************************************
 *
 * @file    drv_wdt.h
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
#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "reg/wdt.h"
typedef enum {
    RESET = 0x00U,     /*!< Generate a system reset */
    INTERRUPT = 0x01U, /*!< First generate an interrupt and even if it is cleared by the time a second timeout occurs then generate a system reset   */
} wdt_mode_type;
typedef struct {
    uint32_t topval;
    _Bool mode;
    _Bool wdt_enable;
} wdt_init_t;

typedef struct __wdt_handle_t {
    wdt_reg_t *instance; /*!< SYSTIMER registers base address        */
    wdt_init_t init;     /*!< SYSTIMER communication parameters      */
    void (*wdt_callback)(void);
} wdt_handle_t;

/**
 * @description: wdt init
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @param {uint32_t} topVal time-out period
 * @param {uint32_t} pulseLen The reset signal maintains the number of pclk clock cycles
 * @param {uint32_t} mode Working mode
 * @return {*}
 */
extern void drv_wdt_init(wdt_handle_t *hwdt);

/**
 * @description: wdt deinit
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @return {*}
 */
extern void drv_wdt_deinit(wdt_handle_t *hwdt);
/**
 * @description: Restart counter
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @return {*}
 */
extern void drv_wdt_restart_counter(wdt_handle_t *hwdt);
/**
 * @description: Setting the timeout period
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @param {uint32_t} val
 * @return {*}
 */
extern void drv_wdt_set_timeout_val(wdt_handle_t *hwdt, uint32_t val);
/**
 * @description: Read the current count value
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @return {*} current counter value register
 */
extern int drv_wdt_get_val(wdt_handle_t *hwdt);
/**
 * @description: clear intr
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @return {*} interrupt clear register
 */
extern int drv_wdt_clear_intr(wdt_handle_t *hwdt);
/**
 * @description: Get interrupt status
 * @param {wdt_reg_t} *addr Pointer to a wdt_reg_t structure that contains
 *               the configuration information for the specified wdt module.
 * @return {*}
 */
extern int drv_wdt_get_intr_status(wdt_handle_t *hwdt);
/**
 * @brief: rtc irq handler
 * @param  huart Pointer to a uart_handle_t structure that contains
 *               the configuration information for the specified rtc module.
 * @retval {none}
 */
extern void drv_wdt_irq_handler(wdt_handle_t *hwdt);
#ifdef __cplusplus
}
#endif
#endif

/*******************************************************************************************************
 *
 * @file    drv_systimer.h
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
#ifndef __DRV_SYS_TIMER_H__
#define __DRV_SYS_TIMER_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "reg/systimer.h"

typedef enum {
    SYSTIMER_INTR_DISABLE = 0,
    SYSTIMER_INTR_ENABLE = 1,
    SYSTIMER_WAIT_INTR_ENABLE = 2,
    SYSTIMER_PAST_INTR_ENABLE = 3,
} systimer_intr_type_t;
typedef struct {
    uint32_t tick;
    uint32_t interrupt_tick;
    uint32_t calibration_cycle;
    systimer_intr_type_t intr_enable;
    _Bool calibration_32k_enable;
    _Bool timer_auto_enable;
} systimer_init_t;

typedef struct {
    uint32_t raw;
    uint32_t ms;
    uint32_t us;
} systimer_time_t;

/**
 * @description: systimer init
 * @param {systimer_init_t} init
 * @return {*}
 */
extern void drv_systimer_init(systimer_init_t *init);
/**
 * @description: systimer deinit
 * @param {uint32_t} tick_h
 * @return {*}
 */
extern void drv_systimer_deinit(void);
/**
 * @description: systimer tick set
 * @param {uint32_t} tick_l
 * @return {*}
 */
extern void drv_systimer_set_tick(uint32_t tick_l);
/**
 * @description: systiemr tick get
 * @return {*}
 */
extern uint32_t drv_systimer_get_tick(void);
/**
 * @description: systimer int levl set tick
 * @param {uint32_t} tick
 * @return {*}
 */
extern void drv_systimer_set_intr_level(uint32_t tick);
/**
 * @description: systimer int levl get tick
 * @return {uint32_t} tick_l
 */
extern uint32_t drv_systimer_get_intr_level(void);
/**
 * @description: systimer auto enable
 * @return {*}
 */
extern void drv_systimer_enable_auto(void);
/**
 * @description: systimer auto disable
 * @return {*}
 */
extern void drv_systimer_disable_auto(void);
/**
 * @description: systimer interrupt enable
 * @return {*}
 */
extern void drv_systimer_enable_intr(void);
/**
 * @description: systimer past interrupt enable
 * @return {*}
 */
extern void drv_systimer_past_enable_intr(void);
/**
 * @description: systimer wait interrupt enable
 * @return {*}
 */
extern void drv_systimer_wait_enable_intr(void);
/**
 * @description: systimer interrupt disable
 * @return {*}
 */
extern void drv_systimer_disable_intr(void);
/**
 * @description: systimer interrupt clear
 * @return {*}
 */
extern void drv_systimer_clear_intr(void);
/**
 * @description: systimer calibration 32k enable

 * @param {uint32_t} calibration_cycle
 * @return {*}
 */
extern void drv_systimer_enable_calibration_32k(uint32_t calibration_cycle);
/**
 * @description: systimer get 32k
 * @param {uint32_t} *freq
 * @return {*}
 */
extern _Bool drv_systimer_get_32k_freq(uint32_t *freq);
/**
 * @description: systimer get 32k cycle
 * @return {*}
 */
extern uint32_t drv_systimer_get_cnt_per_32k_cycle(void);
/**
 * @description: systimer get 32k cycle
 * @return {systimer_time_t} systimer_time
 */
extern systimer_time_t drv_systimer_get_time(void);
/**
 * @description: systimer check running
 * @return {*}
 */
extern _Bool drv_systimer_check_running(void);
#if defined(MCU_CORE_TL752X_N22)
extern uint32_t drv_systimer_get_cpu0_isr_level(void);
extern uint32_t drv_systimer_get_cpu1_isr_level(void);
extern _Bool drv_systimer_cpu0_isr_enable(void);
#endif

#ifdef __cplusplus
}
#endif

#endif

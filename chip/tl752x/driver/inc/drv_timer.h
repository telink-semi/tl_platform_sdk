/*******************************************************************************************************
 *
 * @file    drv_timer.h
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
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "tl_chip.h"
#include "reg/timer.h"

typedef enum {
    TIMER_AUTO_RUN = 0, /* one time shot */
    TIMER_USER_DEF,     /* period running */
} timer_workmode_t;

typedef enum {
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,
    TIMER6,
    TIMER7,
} timer_num_t;

typedef enum {
    TIMER_START = 0,
    TIMER_STOP,
    TIMER_INT_CLEAR,
    TIMER_INT_ENABLE,
    TIMER_INT_DISABLE,
} timer_event_t;

typedef enum {
    TIMER = 0,
    TIMER_PWM,
} timer_function_t;
//Timer clock source selection: 0:clk32 1:clk_hfxo 2:mclk3_cpr
typedef enum {
    TIMER_CLK32 = 0, // 32Khz clock source
    TIMER_CLK_HFXO,  // 24Mhz clock source
    TIMER_CLK_CPR    // source
} timer_clk_source_t;
typedef struct {
    timer_num_t timer_num;
    uint32_t period;
    uint8_t duty_cycle; /* 0~100% */
    timer_function_t function;
    timer_workmode_t mode;
    _Bool intr_enable;
} timer_init_t;

typedef struct __timer_handle_t {
    timer_reg_t *instance;
    timer_init_t init;
    void (*timer_callback)(struct __timer_handle_t *htimer);
} timer_handle_t;

/**
 * @brief: timer deinit
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @return {*}
 */
extern void drv_timer_deinit(timer_handle_t *htimer);
/**
 * @brief: timer init
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @param {timer_handle_t} *htim
 * @return {*}
 */
extern void drv_timer_init(timer_handle_t *htimer);
/**
 * @brief: timer control
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @param {e_timer_event_t} event
 * @return {*}
 */
extern int drv_timer_control(timer_handle_t *htimer, timer_event_t event);
/**
 * @brief: timer read current value
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @return {*}
 */
extern int drv_timer_read(timer_handle_t *htimer);
/**
 * @brief:    set timer period
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @return {*}
 */
extern void drv_timer_set_period(timer_handle_t *htimer);
/**
 * @brief: set timer pwm duty cycle
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @return {*}
 */
extern void drv_timer_set_duty_cycle(timer_handle_t *htimer);
/**
 * @brief: timer irq handler
 * @param {timer_handle_t} timer     TIMER0,    TIMER1,    TIMER2,    TIMER3,    TIMER4,    TIMER5,    TIMER6,    TIMER7,
 * @return {*}
 */
extern void drv_timer_irq_handler(timer_handle_t *htimer);
/**
* @brief  Set the mclk divider
* @param  div: mclk divider
* @return none
*/
extern void drv_timer_mclk_div(uint8_t div);
#ifdef __cplusplus
}
#endif

#endif
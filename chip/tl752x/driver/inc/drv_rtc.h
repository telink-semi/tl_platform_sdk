/*******************************************************************************************************
 *
 * @file    drv_rtc.h
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
#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "reg/rtc.h"

#define RTC_FREQUENCY 32

typedef enum {
    RTC_STATE_RESET = 0x00U,   /*!< RTC not yet initialized or disabled */
    RTC_STATE_READY = 0x01U,   /*!< RTC initialized and ready for use   */
    RTC_STATE_BUSY = 0x02U,    /*!< RTC process is ongoing              */
    RTC_STATE_TIMEOUT = 0x03U, /*!< RTC timeout state                   */
    RTC_STATE_ERROR = 0x04U    /*!< RTC error state                     */
} rtc_state_type;

typedef struct {
    uint32_t loadCount;  // load value
    uint32_t matchCount; // match value
    uint32_t wrap;       // Optional. Allows the user to force the counter to wrap when a match occurs instead of waiting until the maximum count is reached. 0 = Wrap disabled, 1 = Wrap enabled, This bit is writable only when RTC_WRAP_MODE = 1
    _Bool enable;
} rtc_init_t;

typedef struct {
    rtc_init_t init;      /*!< RTC required parameters */
    rtc_state_type state; /*!< Time communication state */
    uint32_t rtc_tick;    // rtc tick count
    void (*rtc_callback)(void);
} rtc_handle_t;

typedef struct {
    uint32_t tick;
    uint32_t ms;
} rtc_time_t;

/**
 * @description: rtc init
 * @param {rtc_handle_t} *rtccfg configuration information
 * @return {*}
 */
extern uint32_t drv_rtc_init(rtc_handle_t *hrtc);
/**
 * @description: De-initialize the RTC driver
 * @param {rtc_handle_t} *rtccfg configuration information
 * @return {*}
 */
extern uint32_t drv_rtc_deinit(rtc_handle_t *hrtc);
/**
 * @description: rtc enable
 * @param {rtc_handle_t} *rtccfg configuration information
 * @return {*}
 */
extern uint32_t drv_rtc_enable(rtc_handle_t *hrtc);
/**
 * @description: Read the current count value
 * @return {*}
 */
extern uint32_t drv_rtc_get_val(void);
/**
 * @description: set the match count value
 * @param {rtc_handle_t} *rtccfg configuration information
 * @param {uint32_t} val
 * @return {*}
 */
extern void drv_rtc_set_matchCount(rtc_handle_t *hrtc, uint32_t val);
/**
 * @description: get the match count value
 * @return {*}
 */
extern uint32_t drv_rtc_get_matchCount(void);
/**
 * @description: get the tick value
 * @return {*}
 */
extern rtc_time_t drv_rtc_get_tick_val(void);
/**
 * @description: rtc config refresh
 * @param {rtc_handle_t} *rtccfg configuration information
 * @return {*}
 */
extern void drv_rtc_refresh(rtc_handle_t *hrtc);
/**
 * @brief: rtc irq handler
 * @param  hrtc rtc handle
 * @retval {none}
 */
extern void drv_rtc_irq_handler(rtc_handle_t *hrtc);
extern void drv_rtc_presclr_config(uint32_t pre_val);
#ifdef __cplusplus
}
#endif

#endif

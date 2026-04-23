/********************************************************************************************************
 * @file    hal_timer.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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



#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "tl_chip.h"
#include "reg/timer.h"

typedef struct
{
    unsigned char  pclk;
} sys_clk_t;
extern sys_clk_t sys_clk;

typedef enum
{
    FLD_TMR0_MODE_IRQ = 0,
    FLD_TMR1_MODE_IRQ,
    FLD_TMR2_MODE_IRQ,
    FLD_TMR3_MODE_IRQ,
    FLD_TMR4_MODE_IRQ,
    FLD_TMR5_MODE_IRQ,
    FLD_TMR6_MODE_IRQ,
    FLD_TMR7_MODE_IRQ,
} timer_irq_e;
/**
 * @brief   Mode of Timer
 */
typedef enum
{
    TIMER_MODE_SYSCLK       = 0,
} timer_mode_e;

enum
{
    TIMER_TICK_CLOCK_1S  = 1000000,
    TIMER_TICK_CLOCK_1MS = (TIMER_TICK_CLOCK_1S / 1000),
    TIMER_TICK_CLOCK_1US = (TIMER_TICK_CLOCK_1S / 1000000),
};

/**
 * @brief     This function set to capture tick for timer0-7.
 * @param[in] type - timer0-7.
 * @param[in] cap_tick - set capture tick value.
 * @return    none
 */
void timer_set_cap_tick(timer_num_t type, unsigned int cap_tick);

/**
 * @brief     the specified timer start working.
 * @param[in] type - select the timer to start.
 * @return    none
 */
void timer_start(timer_num_t type);

/**
 * @brief     the specified timer stop working.
 * @param[in] type - select the timer to stop.
 * @return    none
 */
void timer_stop(timer_num_t type);

/**
 * @brief     This function set timer irq mask.
 * @param[in] mask - variable of enumeration to select the timer interrupt mask.
 * @return    none.
 */
void timer_set_irq_mask(timer_irq_e mask);

/**
 * @brief     This function clear timer irq mask.
 * @param[in] mask - variable of enumeration to select the timer interrupt mask.
 * @return    none.
 */
void timer_clr_irq_mask(timer_irq_e mask);

/**
 * @brief     set mode of timer.
 * @param[in] type - select the timer to start.
 * @param[in] mode - select mode for timer.
 * @return    none
 */
void timer_set_mode(timer_num_t type, timer_mode_e mode);

/**
 * @brief     This function refer to clear timer irq status.
 * @param[in] status - variable of enumeration to select the timer interrupt source.
 * @return    none
 */
void timer_clr_irq_status(timer_irq_e status);

void timer_init(timer_num_t type);

/**
 * @brief     This function is used to configure the timer clock frequency to 16MHz.
 * @param[in] none
 * @return    none
 * @attention This function MUST be called after timer_init(), otherwise it won't work.
 */
void timer_set_clk(void);

static inline unsigned char timer_get_irq_status(timer_irq_e status)
{
    (void)status;
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif

/********************************************************************************************************
 * @file    hal_systimer.h
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

#ifndef __HAL_SYS_TIMER_H__
#define __HAL_SYS_TIMER_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */
#include "inc/drv_systimer.h"
#include "modules/drv_systimer_ex.h"
#include "compiler.h"
#include "tl_chip.h"

/**
 * @brief define system clock tick per us/ms/s.
 */
enum
{
    SYSTEM_TIMER_TICK_1US = 16,
    SYSTEM_TIMER_TICK_1MS = 16000,
    SYSTEM_TIMER_TICK_1S  = 16000000,

    SYSTEM_TIMER_TICK_625US  = 10000, //625*16
    SYSTEM_TIMER_TICK_1250US = 20000, //1250*16
};

typedef enum
{
    FLD_SYSTEM_IRQ_D25F = (1<<0), /**<
                                            When the current tick value of the system timer reaches the preset tick value,the IRQ_SYSTIMER interrupt is generated,
                                            This mask must be turned on if you want to trigger an interrupt.
                                            If you do not trigger an interrupt and only polling can detect the state, this mask also needs to be turned on.
                                            Get interrupt status:stimer_get_irq_status(),clear interrupt status:stimer_clr_irq_status().
                                            The interrupt flag bit needs to be manually cleared.
                                          */
    FLD_SYSTEM_IRQ_N22  = (1<<1), /**<
                                            When the current tick value of the system timer reaches the preset tick value,the IRQ_SYSTIMER interrupt is generated,
                                            This mask must be turned on if you want to trigger an interrupt.
                                            If you do not trigger an interrupt and only polling can detect the state, this mask also needs to be turned on.
                                            Get interrupt status:stimer_get_irq_status(),clear interrupt status:stimer_clr_irq_status().
                                            The interrupt flag bit needs to be manually cleared.
                                          */
    FLD_SYSTEM_IRQ_DSP  = (1<<2), /**<
                                            When the current tick value of the system timer reaches the preset tick value,the IRQ_SYSTIMER interrupt is generated,
                                            This mask must be turned on if you want to trigger an interrupt.
                                            If you do not trigger an interrupt and only polling can detect the state, this mask also needs to be turned on.
                                            Get interrupt status:stimer_get_irq_status(),clear interrupt status:stimer_clr_irq_status().
                                            The interrupt flag bit needs to be manually cleared.
                                          */
    FLD_SYSTEM_32K_IRQ  = (1<<3), /**<
                                            When the system timer completes the calibration of 32k timer,the IRQ_SYSTIMER interrupt is generated,
                                            This mask must be turned on if you want to trigger an interrupt.
                                            If you do not trigger an interrupt and only polling can detect the state, this mask also needs to be turned on.
                                            Get interrupt status:stimer_get_irq_status(),clear interrupt status:stimer_clr_irq_status().
                                            The interrupt flag bit needs to be manually cleared.
                                         <p>
                                            In Non-dma mode,the received data is read by stimer_get_tracking_32k_value().
                                          */
} stimer_irq_e;

typedef enum
{
    STIMER_MANUAL_MODE                   = 0x00, /**< Write a register to start the system timer. */
    STIMER_AUTO_MODE_W_TRIG              = 0x01, /**< When you write the tick value of the system timer,
                                                the system timer starts automatically. */
    STIMER_AUTO_MODE_W_AND_NXT_32K_START = 0x02, /**< Configure this mode:
                                                When the first 32k scale rises, the system timer starts automatically.*/
    STIMER_AUTO_MODE_W_AND_NXT_32K_DONE  = 0x03, /**< After the tick value is written to the system timer,
                                                the system timer automatically starts when the first 32k tick rises. */
} stimer_enable_mode_e;


extern unsigned int g_track_32kcnt;

/**
 * @brief       This function servers to set tick of d25f irq capture.
 * @param[in]   tick - the value of irq tick.
 * @return      none.
 */
static _always_inline void stimer_set_irq_capture_d25f(unsigned int tick)
{
    WRITE_REG(SYS_TIMER->LVL1, (tick));
}

/**
 * @brief       This function servers to set tick of n22 irq capture.
 * @param[in]   tick - the value of irq tick.
 * @return      none.
 */
static _always_inline void stimer_set_irq_capture_n22(unsigned int tick)
{
    WRITE_REG(SYS_TIMER->LVL0, (tick));
}

/**
 * @brief       This function servers to set tick of dsp irq capture.
 * @param[in]   tick - the value of irq tick.
 * @return      none.
 */
static _always_inline void stimer_set_irq_capture_dsp(unsigned int tick)
{
    WRITE_REG(SYS_TIMER->LVL2, (tick));
}

/**
 * @brief     This function performs to get system timer tick.
 * @return    system timer tick value.
 */
static _always_inline unsigned int stimer_get_tick(void)
{
    return READ_REG(SYS_TIMER->TICK_L);
}

/**
 * @brief       This function is used to set the tick value of the system timer.
 * @param[in]   tick - the value of system timer tick.
 * @return      none.
 */
static _always_inline void stimer_set_tick(unsigned int tick)
{
    WRITE_REG(SYS_TIMER->TICK_L, tick);
}

static _always_inline void stimer_disable(void)
{
    CLEAR_REG(SYS_TIMER->CFG);
}

static _always_inline void stimer_32k_tracking_enable(void)
{
    SET_BIT(SYS_TIMER->CFG, SYSTIMER_32K_CALIBRATION_ENABLE);
}

static _always_inline void stimer_32k_tracking_disable(void)
{
    CLEAR_BIT(SYS_TIMER->CFG, SYSTIMER_32K_CALIBRATION_ENABLE);
}

/**
 * @brief   This function is used to disable automatic mode for system timer.
 * @return  none.
 */
static _always_inline void stimer_set_manual_enable_mode(void)
{
    CLEAR_BIT(SYS_TIMER->CFG, SYSTIMER_AUTO_ENABLE);
    SET_BIT(SYS_TIMER->CFG, SYSTIMER_MANUAL_ENABLE);
}

/**
 * @brief   This function is used to enable automatic mode for system timer.
 * @return  none.
 */
static _always_inline void stimer_set_auto_enable_mode(void)
{
    CLEAR_BIT(SYS_TIMER->CFG, SYSTIMER_MANUAL_ENABLE);
    SET_BIT(SYS_TIMER->CFG, SYSTIMER_AUTO_ENABLE);
}

/**
 * @brief   This function is used to enable the function to update the tick value of system timer at the next 32k rise edge.
 * @return  none.
 */
static _always_inline void stimer_set_update_upon_nxt_32k_enable(void)
{
    SET_BIT(SYS_TIMER->CFG, SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE);
}

/**
 * @brief   This function is used to disable the function to update the tick value of system timer at the next 32k rise edge.
 * @return  none.
 */
static _always_inline void stimer_set_update_upon_nxt_32k_disable(void)
{
    CLEAR_BIT(SYS_TIMER->CFG, SYSTIMER_VALUE_UPDATE_32K_EDGE_ENABLE);
}

/**
 * @brief   This function is used to enable the function to trigger the operation at the next 32k rise edge.
 * @return  none.
 */
static _always_inline void stimer_set_run_upon_nxt_32k_enable(void)
{
    SET_BIT(SYS_TIMER->CFG, SYSTIMER_START_32K_EDGE_ENABLE);
}

/**
 * @brief   This function is used to disable the function to trigger the operation at the next 32k rise edge.
 * @return  none.
 */
static _always_inline void stimer_set_run_upon_nxt_32k_disable(void)
{
    CLEAR_BIT(SYS_TIMER->CFG, SYSTIMER_START_32K_EDGE_ENABLE);
}

/**
 * @brief       This function is used to start the system timer.
 * @param[in]   mode    - starting mode.
 * @param[in]   tick    - The initial value of the tick at startup.
 * @return      none.
 */
_attribute_ram_code_sec_optimize_o2_noinline_ void stimer_enable(stimer_enable_mode_e mode, unsigned int tick);

/**
 * @brief       This function servers to set system timer irq mask.
 * @param[in]   mask - the irq mask.
 * @return      none.
 * @note        When three cores write to the interrupt mask register or other shared registers simultaneously, there is a risk of errors, 
 *              so only one core should operate on these registers at a time, or a mutex variable should be set for exclusivity.
 */
extern void stimer_set_irq_mask(stimer_irq_e mask);

/**
 * @brief       This function servers to get system timer irq status.
 * @param[in]   status - the irq status.
 * @retval      non-zero -  the interrupt occurred.
 * @retval      zero  -  the interrupt did not occur.
 */
extern unsigned char stimer_get_irq_status(stimer_irq_e status);

/**
 * @brief       This function servers to clear system timer irq status.
 * @param[in]   status - the irq status.
 * @return      none.
 */
extern void stimer_clr_irq_status(stimer_irq_e status);

/**
 * @brief     This function serves to set timeout by us.
 * @param[in] ref  - reference tick of system timer .
 * @param[in] us   - count by us.
 * @return    true - timeout, false - not timeout
 */
extern _attribute_ram_code_sec_noinline_ _Bool clock_time_exceed(unsigned int ref, unsigned int us);

/**
 * @brief     This function performs to set delay time by us.
 * @param[in] microsec - need to delay.
 * @return    none
 */
extern _attribute_ram_code_sec_noinline_ void delay_us(unsigned int microsec);

/**
 * @brief     This function performs to set delay time by ms.
 * @param[in] millisec - need to delay.
 * @return    none
 */
extern _attribute_ram_code_sec_noinline_ void delay_ms(unsigned int millisec);

#ifdef __cplusplus
}
#endif

#endif

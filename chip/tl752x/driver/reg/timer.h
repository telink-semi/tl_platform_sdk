/*******************************************************************************************************
 *
 * @file    timer.h
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
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//TimerNControlReg offsetaddress : 0x08 + (N-1)*0x14
#define TIMER_TIMER_ENABLE_POS (0U)
#define TIMER_TIMER_ENABLE_MSK (0x1UL << TIMER_TIMER_ENABLE_POS) /*!< Timer enable bit for Timer N. Values: ■ 0x1 (ENABLED): Timer N is enabled ■ 0x0 (DISABLE): Timer N is disabled Exists: Always*/
#define TIMER_TIMER_ENABLE     TIMER_TIMER_ENABLE_MSK
#define TIMER_TIMER_MODE_POS   (1U)
#define TIMER_TIMER_MODE_MSK \
    (0x1UL                   \
     << TIMER_TIMER_MODE_POS) /*!< Timer mode for Timer N. Note: You must set the Timer1LoadCount register to all 1s before enabling the timer in free-running mode. Values: ■ 0x1 (USER_DEFINED): User-Defined mode of operation ■ 0x0 (FREE_RUNNING): Free Running mode of operation Exists: Always*/
#define TIMER_TIMER_MODE               TIMER_TIMER_MODE_MSK
#define TIMER_TIMER_INTERRUPT_MASK_POS (2U)
#define TIMER_TIMER_INTERRUPT_MASK_MSK (0x1UL << TIMER_TIMER_INTERRUPT_MASK_POS) /*!< Timer interrupt mask for Timer N. Values: ■ 0x1 (MASKED): Timer N interrupt is masked ■ 0x0 (UNMASKED): Timer N interrupt is unmasked Exists: Always*/
#define TIMER_TIMER_INTERRUPT_MASK     TIMER_TIMER_INTERRUPT_MASK_MSK
#define TIMER_TIMER_PWM_POS            (3U)
#define TIMER_TIMER_PWM_MSK \
    (0x1UL << TIMER_TIMER_PWM_POS) /*!< Pulse Width Modulation of timer_N_toggle output. This field is only present when TIM_NEWMODE is enabled Values: ■ 0x1 (ENABLED): PWM for timer_N_toggle o/p is enabled ■ 0x0 (DISABLE): PWM for timer_N_toggle o/p is disabled Exists: TIM_NEWMODE==1*/
#define TIMER_TIMER_PWM             TIMER_TIMER_PWM_MSK
#define TIMER_TIMER_0N100PWM_EN_POS (4U)
#define TIMER_TIMER_0N100PWM_EN_MSK \
    (0x1UL                          \
     << TIMER_TIMER_0N100PWM_EN_POS) /*!< Optional. Allows user to enable or disable the usage of Timer 0% and 100% mode feature. This bit is present only when (TIM_0N100_PWM_MODE=1 and TIMER_HAS_TOGGLE_N=1). Otherwise reserved. Values: ■ 0x1 (ENABLED): Timer 0% and 100% PWM duty cycle mode is enabled ■ 0x0 (DISABLE): Timer 0% and 100% PWM duty cycle mode is disabled Exists: TIM_0N100_PWM_MODE && TIMER_HAS_TOGGLE_1*/
#define TIMER_TIMER_0N100PWM_EN         TIMER_TIMER_0N100PWM_EN_MSK
#define TIMER_RSVD_TIMERNCONTROLREG_POS (5U)
#define TIMER_RSVD_TIMERNCONTROLREG_MSK (0x1UL << TIMER_RSVD_TIMERNCONTROLREG_POS) /*!< TimerNControlReg 31to5 Reserved field Exists: Always*/
#define TIMER_RSVD_TIMERNCONTROLREG     TIMER_RSVD_TIMERNCONTROLREG_MSK

typedef struct {
    volatile uint32_t TIMER0_LOAD_COUNTER;  /* offset 0x0000 */
    volatile uint32_t TIMER0_CURRENT_VALUE; /* offset 0x0004 */
    volatile uint32_t TIMER0_CONTROL_REG;   /* offset 0x0008 */
    volatile uint32_t TIMER0_EOI;           /* offset 0x000c */
    volatile uint32_t TIMER0_INT_STATUS;    /* offset 0x0010 */
    volatile uint32_t TIMER1_LOAD_COUNTER;  /* offset 0x0014 */
    volatile uint32_t TIMER1_CURRENT_VALUE; /* offset 0x0018 */
    volatile uint32_t TIMER1_CONTROL_REG;   /* offset 0x001c */
    volatile uint32_t TIMER1_EOI;           /* offset 0x0020 */
    volatile uint32_t TIMER1_INT_STATUS;    /* offset 0x0024 */
    volatile uint32_t TIMER2_LOAD_COUNTER;  /* offset 0x0028 */
    volatile uint32_t TIMER2_CURRENT_VALUE; /* offset 0x002c */
    volatile uint32_t TIMER2_CONTROL_REG;   /* offset 0x0030 */
    volatile uint32_t TIMER2_EOI;           /* offset 0x0034 */
    volatile uint32_t TIMER2_INT_STATUS;    /* offset 0x0038 */
    volatile uint32_t TIMER3_LOAD_COUNTER;  /* offset 0x003c */
    volatile uint32_t TIMER3_CURRENT_VALUE; /* offset 0x0040 */
    volatile uint32_t TIMER3_CONTROL_REG;   /* offset 0x0044 */
    volatile uint32_t TIMER3_EOI;           /* offset 0x0048 */
    volatile uint32_t TIMER3_INT_STATUS;    /* offset 0x004c */
    volatile uint32_t rev_0[(0x00a0 - 0x004c) / 4 - 1];
    volatile uint32_t TIMER_INT_STATUS;     /* offset 0x00a0 */
    volatile uint32_t TIMER_EOI;            /* offset 0x00a4 */
    volatile uint32_t TIMER_RAW_INT_STATUS; /* offset 0x00a8 */
    volatile uint32_t TIMER_COMP_VERSION;   /* offset 0x00ac */
    volatile uint32_t TIMER0_LOAD_COUNTER2; /* offset 0x00b0 */
    volatile uint32_t TIMER1_LOAD_COUNTER2; /* offset 0x00b4 */
    volatile uint32_t TIMER2_LOAD_COUNTER2; /* offset 0x00b8 */
    volatile uint32_t TIMER3_LOAD_COUNTER2; /* offset 0x00bc */
    volatile uint32_t rev_1[(0x00d0 - 0x00bc) / 4 - 1];
    volatile uint32_t TIMER0_N_PROT_LEVEL; /* offset 0x00d0 */
    volatile uint32_t TIMER1_N_PROT_LEVEL; /* offset 0x00d4 */
    volatile uint32_t TIMER2_N_PROT_LEVEL; /* offset 0x00d8 */
    volatile uint32_t TIMER3_N_PROT_LEVEL; /* offset 0x00dc */
} timer_reg_t;
#ifdef __cplusplus
}
#endif
#endif
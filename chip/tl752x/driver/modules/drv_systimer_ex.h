/*******************************************************************************************************
 *
 * @file    drv_systimer_ex.h
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
#ifndef __DRV_SYSTIMER_EX_H__
#define __DRV_SYSTIMER_EX_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MCU_CORE_TL752X_D25F)
#define SYSTIMER_INTR_INTERRUPT SYSTIMER_LEVEL_1_INTRRUPT
#define SYSTIMER_INTERRUPT_MASK SYSTIMER_INTERRUPT_MASK_LEVEL1
#define SYSTIMER_PAST_INTERRUPT_MASK SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL1
#define SYSTIMER_WAIT_INTERRUPT_MASK SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL1
#define SYSTIMER_LEVEL_ID       LVL1
#elif defined(MCU_CORE_TL752X_N22)
#define SYSTIMER_INTR_INTERRUPT SYSTIMER_LEVEL_0_INTRRUPT
#define SYSTIMER_INTERRUPT_MASK      SYSTIMER_INTERRUPT_MASK_LEVEL0
#define SYSTIMER_PAST_INTERRUPT_MASK SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL0
#define SYSTIMER_WAIT_INTERRUPT_MASK SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL0
#define SYSTIMER_LEVEL_ID       LVL0
#elif defined(MCU_CORE_TL752X_DSP)
#define SYSTIMER_INTR_INTERRUPT SYSTIMER_LEVEL_2_INTRRUPT
#define SYSTIMER_INTERRUPT_MASK      SYSTIMER_INTERRUPT_MASK_LEVEL2
#define SYSTIMER_PAST_INTERRUPT_MASK SYSTIMER_ENABLE_PAST_INTERRUPT_LEVEL2
#define SYSTIMER_WAIT_INTERRUPT_MASK SYSTIMER_ENABLE_INTERRUPT_WAIT_LEVEL2
#define SYSTIMER_LEVEL_ID       LVL2
#endif
#ifdef __cplusplus
}
#endif

#endif

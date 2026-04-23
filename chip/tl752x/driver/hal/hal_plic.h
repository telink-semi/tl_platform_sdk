/********************************************************************************************************
 * @file    hal_plic.h
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



#ifndef __HAL_PLIC_H__
#define __HAL_PLIC_H__
#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include "hal/plic.h"
#define IRQ_GPIO_IRQ0 IRQ_GPIO

#define IRQ_TIMER0    IRQ_TIMER0_0   /* TIMER0_0_IRQHandler */
#define IRQ_TIMER1    IRQ_TIMER0_1   /* TIMER0_1_IRQHandler */
#define IRQ_TIMER2    IRQ_TIMER0_2   /* TIMER0_2_IRQHandler */
#define IRQ_TIMER3    IRQ_TIMER0_3   /* TIMER0_3_IRQHandler */
#define IRQ_TIMER4    IRQ_TIMER1_0   /* TIMER1_0_IRQHandler */
#define IRQ_TIMER5    IRQ_TIMER1_1   /* TIMER1_1_IRQHandler */
#define IRQ_TIMER6    IRQ_TIMER1_2   /* TIMER1_2_IRQHandler */
#define IRQ_TIMER7    IRQ_TIMER1_3   /* TIMER1_3_IRQHandler */

#define IRQ_TRNG      IRQ_OSR_TRNG   /* OSR_TRNG_IRQHandler */
#ifdef __cplusplus
}
#endif

#endif

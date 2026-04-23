/*******************************************************************************************************
 *
 * @file    plic_reg.h
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
#ifndef INTERRUPT_REG_H
#define INTERRUPT_REG_H

/*******************************     interrupt registers:  plic base 0xe4000000   ******************************/
#define reg_irq_feature         (*(volatile unsigned long *)(0 + (0xe4000000)))

#define reg_irq_pending(i)      (*(volatile unsigned long *)(0 + (0xe4001000 + ((i > 31) ? 4 : 0))))

#define reg_irq_src0            (*(volatile unsigned long *)(0 + (0xe4002000)))
#define reg_irq_src1            (*(volatile unsigned long *)(0 + (0xe4002004)))

#define reg_irq_src(i)          (*(volatile unsigned long *)(0 + (0xe4002000 + ((i > 31) ? 4 : 0))))

#define reg_irq_threshold       (*(volatile unsigned long *)(0 + (0xe4200000)))
#define reg_irq_done            (*(volatile unsigned long *)(0 + (0xe4200004)))

#define reg_irq_src_priority(i) (*(volatile unsigned long *)(0 + 0xe4000000 + ((i) << 2)))

#endif

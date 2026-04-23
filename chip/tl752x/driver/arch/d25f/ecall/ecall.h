/*******************************************************************************************************
 *
 * @file    ecall.h
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
#if defined(MCU_CORE_TL752X_D25F)

#ifndef __ECALL_H__
#define __ECALL_H__

#define ECALL_ASSERT_ERROR_ID           1
#define ECALL_CHANGE_TO_USER_MODE_ID    2
#define ECALL_CHANGE_TO_MACHINE_MODE_ID 3
#define ECALL_OS_CALL_ID                7

#define RISCV_ECALL(which, arg0, arg1, arg2)       __nds__ecall3(which,arg0, arg1, arg2)

#define RISCV_ECALL_OS()               RISCV_ECALL(ECALL_OS_CALL_ID,0,0,0)
#define RISCV_ECALL_0(which) RISCV_ECALL(which, 0, 0, 0)

#endif
#endif

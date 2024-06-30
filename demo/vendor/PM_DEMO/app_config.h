/********************************************************************************************************
 * @file    app_config.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif
#include "driver.h"
#include "common.h"


#define WAKEUP_PAD              GPIO_PA0
#define CURRENT_TEST            1
#define CRC_OK                  1
#define MDEC_MATCH_VALUE        0x02

#if defined(MCU_CORE_B91)
#define PM_TICK_STIMER          PM_TICK_STIMER_16M
#endif


/**
 * @note To enter sleep using COMPARATOR Wake mode, the voltage difference between the input level and the configured wake level
 *       needs to be greater than 100mV. If the input level is particularly close to the wake level, the chip will not sleep properly
 *       due to the unstable state of the LPC, resulting in a crash.
 */

/* SUSPEND MODE */
//[eagle]The A0 version of the suspend execution process is abnormal and the program restarts.
#define SUSPEND_PAD_WAKEUP              10
#define SUSPEND_32K_RC_WAKEUP           11
#if (defined(MCU_CORE_B91)||defined(MCU_CORE_B92))
#define SUSPEND_32K_XTAL_WAKEUP         12
#define SUSPEND_COMPARATOR_WAKEUP       13
#define SUSPEND_CORE_USB_WAKEUP         14
#endif
#if defined(MCU_CORE_B91)
#define SUSPEND_MDEC_WAKEUP             15
#endif
#if defined(MCU_CORE_B92)
// CTB mode : For internal testing only, this function is not available externally
#define SUSPEND_CTB_WAKEUP              16
//#define SUSPEND_CORE_GPIO_WAKEUP        17
#endif

/* DEEP SLEEP MODE */
#define DEEP_PAD_WAKEUP                 20
#define DEEP_32K_RC_WAKEUP              21
#if (defined(MCU_CORE_B91)||defined(MCU_CORE_B92))
#define DEEP_32K_XTAL_WAKEUP            22
#define DEEP_COMPARATOR_WAKEUP          23
#endif
#if defined(MCU_CORE_B91)
#define DEEP_MDEC_WAKEUP                24
#endif
#if defined(MCU_CORE_B92)
// CTB mode : For internal testing only, this function is not available externally
#define DEEP_CTB_WAKEUP                 25
#endif

/* DEEP SLEEP WITH RETENTION MODE */
#if defined(MCU_CORE_B91)|| defined(MCU_CORE_B92)|| defined(MCU_CORE_TL721X)
#define DEEP_RET32K_PAD_WAKEUP          30
#define DEEP_RET32K_32K_RC_WAKEUP       31
#if (defined(MCU_CORE_B91)||defined(MCU_CORE_B92))
#define DEEP_RET32K_32K_XTAL_WAKEUP     32
#define DEEP_RET32K_COMPARATOR_WAKEUP   33
#endif
#if defined(MCU_CORE_B91)
#define DEEP_RET32K_MDEC_WAKEUP         34
#endif
#if defined(MCU_CORE_B92)
// CTB mode : For internal testing only, this function is not available externally
#define DEEP_RET32K_CTB_WAKEUP          35
#endif
#endif

#if defined(MCU_CORE_B91)|| defined(MCU_CORE_B92)|| defined(MCU_CORE_TL721X)
#define DEEP_RET64K_PAD_WAKEUP          40
#define DEEP_RET64K_32K_RC_WAKEUP       41
#if (defined(MCU_CORE_B91)||defined(MCU_CORE_B92))
#define DEEP_RET64K_32K_XTAL_WAKEUP     42
#define DEEP_RET64K_COMPARATOR_WAKEUP   43
#endif
#if defined(MCU_CORE_B91)
#define DEEP_RET64K_MDEC_WAKEUP         44
#endif
#if defined(MCU_CORE_B92)
// CTB mode : For internal testing only, this function is not available externally
#define DEEP_RET64K_CTB_WAKEUP          45
#endif
#endif

#if defined(MCU_CORE_B92)
#define DEEP_RET96K_PAD_WAKEUP          50
#define DEEP_RET96K_32K_RC_WAKEUP       51
#define DEEP_RET96K_32K_XTAL_WAKEUP     52
#define DEEP_RET96K_COMPARATOR_WAKEUP   53
// CTB mode : For internal testing only, this function is not available externally
#define DEEP_RET96K_CTB_WAKEUP          54
#endif

#if defined(MCU_CORE_TL721X)
#define DEEP_RET128K_PAD_WAKEUP         60
#define DEEP_RET128K_32K_RC_WAKEUP      61
#endif

#if defined(MCU_CORE_TL721X)
#define DEEP_RET256K_PAD_WAKEUP         70
#define DEEP_RET256K_32K_RC_WAKEUP      71
#endif

#define PM_MODE                         SUSPEND_32K_RC_WAKEUP


/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif


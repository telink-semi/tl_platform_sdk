/*******************************************************************************************************
 *
 * @file    drv_arbiter.h
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
#ifndef __DRV_ARBITER_H__
#define __DRV_ARBITER_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "modules/cpr.h"
#include "tl_chip.h"

/********************************** LOCK **********************************/
#if defined(MCU_CORE_TL752X_D25F)
#define __DRV_ARBITER0()                              \
    ({                                                \
        WRITE_REG(CPR->ARBITER0, CPR_CPU0_LOCK_W(1)); \
        READ_BIT(CPR->ARBITER0, CPR_CPU0_LOCK);       \
    })
#define __DRV_ARBITER1()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER1, CPR_CPU0_LOCK_ARBITER1_W(1)); \
        READ_BIT(CPR->ARBITER1, CPR_CPU0_LOCK_ARBITER1);       \
    })
#define __DRV_ARBITER2()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER2, CPR_CPU0_LOCK_ARBITER2_W(1)); \
        READ_BIT(CPR->ARBITER2, CPR_CPU0_LOCK_ARBITER2);       \
    })
#define __DRV_ARBITER3()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER3, CPR_CPU0_LOCK_ARBITER3_W(1)); \
        READ_BIT(CPR->ARBITER3, CPR_CPU0_LOCK_ARBITER3);       \
    })
#define __DRV_ARBITER4()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER4, CPR_CPU0_LOCK_ARBITER4_W(1)); \
        READ_BIT(CPR->ARBITER4, CPR_CPU0_LOCK_ARBITER4);       \
    })
#define __DRV_ARBITER5_ID_LOG()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER5, CPR_CPU0_LOCK_ARBITER5_W(1)); \
        READ_BIT(CPR->ARBITER5, CPR_CPU0_LOCK_ARBITER5);       \
    })
#define __DRV_BT_DRV_ARBITER6()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER6, CPR_CPU0_LOCK_ARBITER6_W(1)); \
        READ_BIT(CPR->ARBITER6, CPR_CPU0_LOCK_ARBITER6);       \
    })
#define __GPIO_ARBITER()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER7, CPR_CPU0_LOCK_ARBITER7_W(1)); \
        READ_BIT(CPR->ARBITER7, CPR_CPU0_LOCK_ARBITER7);       \
    })
#elif defined(MCU_CORE_TL752X_N22)
#define __DRV_ARBITER0()                              \
    ({                                                \
        WRITE_REG(CPR->ARBITER0, CPR_CPU1_LOCK_W(1)); \
        READ_BIT(CPR->ARBITER0, CPR_CPU1_LOCK);       \
    })
#define __DRV_ARBITER1()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER1, CPR_CPU1_LOCK_ARBITER1_W(1)); \
        READ_BIT(CPR->ARBITER1, CPR_CPU1_LOCK_ARBITER1);       \
    })
#define __DRV_ARBITER2()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER2, CPR_CPU1_LOCK_ARBITER2_W(1)); \
        READ_BIT(CPR->ARBITER2, CPR_CPU1_LOCK_ARBITER2);       \
    })
#define __DRV_ARBITER3()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER3, CPR_CPU1_LOCK_ARBITER3_W(1)); \
        READ_BIT(CPR->ARBITER3, CPR_CPU1_LOCK_ARBITER3);       \
    })
#define __DRV_ARBITER4()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER4, CPR_CPU1_LOCK_ARBITER4_W(1)); \
        READ_BIT(CPR->ARBITER4, CPR_CPU1_LOCK_ARBITER4);       \
    })
#define __DRV_ARBITER5_ID_LOG()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER5, CPR_CPU1_LOCK_ARBITER5_W(1)); \
        READ_BIT(CPR->ARBITER5, CPR_CPU1_LOCK_ARBITER5);       \
    })
#define __DRV_BT_DRV_ARBITER6()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER6, CPR_CPU1_LOCK_ARBITER6_W(1)); \
        READ_BIT(CPR->ARBITER6, CPR_CPU1_LOCK_ARBITER6);       \
    })
#define __GPIO_ARBITER()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER7, CPR_CPU1_LOCK_ARBITER7_W(1)); \
        READ_BIT(CPR->ARBITER7, CPR_CPU1_LOCK_ARBITER7);       \
    })

#elif defined(MCU_CORE_TL752X_DSP)
#define __DRV_ARBITER0()                              \
    ({                                                \
        WRITE_REG(CPR->ARBITER0, CPR_CPU2_LOCK_W(1)); \
        READ_BIT(CPR->ARBITER0, CPR_CPU2_LOCK);       \
    })
#define __DRV_ARBITER1()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER1, CPR_CPU2_LOCK_ARBITER1_W(1)); \
        READ_BIT(CPR->ARBITER1, CPR_CPU2_LOCK_ARBITER1);       \
    })
#define __DRV_ARBITER2()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER2, CPR_CPU2_LOCK_ARBITER2_W(1)); \
        READ_BIT(CPR->ARBITER2, CPR_CPU2_LOCK_ARBITER2);       \
    })
#define __DRV_ARBITER3()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER3, CPR_CPU2_LOCK_ARBITER3_W(1)); \
        READ_BIT(CPR->ARBITER3, CPR_CPU2_LOCK_ARBITER3);       \
    })
#define __DRV_ARBITER4()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER4, CPR_CPU2_LOCK_ARBITER4_W(1)); \
        READ_BIT(CPR->ARBITER4, CPR_CPU2_LOCK_ARBITER4);       \
    })
#define __DRV_ARBITER5_ID_LOG()                                \
    ({                                                         \
        WRITE_REG(CPR->ARBITER5, CPR_CPU2_LOCK_ARBITER5_W(1)); \
        READ_BIT(CPR->ARBITER5, CPR_CPU2_LOCK_ARBITER5);       \
    })
#define __DRV_BT_DRV_ARBITER6()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER6, CPR_CPU2_LOCK_ARBITER6_W(1)); \
        READ_BIT(CPR->ARBITER6, CPR_CPU2_LOCK_ARBITER6);       \
    })
#define __GPIO_ARBITER()                                       \
    ({                                                         \
        WRITE_REG(CPR->ARBITER7, CPR_CPU2_LOCK_ARBITER7_W(1)); \
        READ_BIT(CPR->ARBITER7, CPR_CPU2_LOCK_ARBITER7);       \
    })
#endif

#define __DRV_CLEAR_ARBITER0()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER0, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_CLEAR_ARBITER1()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER1, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_CLEAR_ARBITER2()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER2, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_CLEAR_ARBITER3()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER3, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_CLEAR_ARBITER4()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER4, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_CLEAR_ARBITER5_ID_LOG()         \
    do {                                      \
        WRITE_REG(CPR->ARBITER5, 0xFFFFFFFF); \
    } while (0U)
#define __DRV_BT_DRV_CLEAR_ARBITER6()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER6, 0xFFFFFFFF); \
    } while (0U)
#define __GPIO_CLEAR_ARBITER()                \
    do {                                      \
        WRITE_REG(CPR->ARBITER7, 0xFFFFFFFF); \
    } while (0U)
#ifdef __cplusplus
}
#endif

#endif

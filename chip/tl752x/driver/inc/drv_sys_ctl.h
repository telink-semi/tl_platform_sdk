/*******************************************************************************************************
 *
 * @file    drv_sys_ctl.h
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
#ifndef __DRV_SYS_CTL_H__
#define __DRV_SYS_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/sys_ctl.h"
#include "modules/drv_sysctl_ex.h"

/********************************** SDIO **********************************/
#define __DRV_SYS_CTL_SDIO_CARD_DETECT_ON()                       \
    do {                                                          \
        CLEAR_BIT(SYS_CTL->SDIO_CFG, SYS_CTL_SDIO_CARD_DETECT_N); \
    } while (0)

#define __DRV_SYS_CTL_SDIO_CARD_DETECT_OFF()                    \
    do {                                                        \
        SET_BIT(SYS_CTL->SDIO_CFG, SYS_CTL_SDIO_CARD_DETECT_N); \
    } while (0)

#define __DRV_SYS_CTL_SDIO_CARD_PRT_ON()                        \
    do {                                                        \
        SET_BIT(SYS_CTL->SDIO_CFG, SYS_CTL_SDIO_CARD_DETECT_N); \
    } while (0)

#define __DRV_SYS_CTL_SDIO_CARD_PRT_OFF()                         \
    do {                                                          \
        CLEAR_BIT(SYS_CTL->SDIO_CFG, SYS_CTL_SDIO_CARD_DETECT_N); \
    } while (0)

/********************************** TEST CFG **********************************/

#define __DRV_SYS_CTL_GET_TEST_CFG()    READ_REG(SYS_CTL->TEST_CFG)
#define __DRV_SYS_CTL_SET_TEST_CFG(val) WRITE_REG(SYS_CTL->TEST_CFG, val)

/********************************** OSR **********************************/
/**
 * @brief: osr port val read
 * @retval: port val
 */
extern uint32_t drv_sys_ctr_osr_port_read(void);

/**
 * @brief: osr port val write
 * @param {uint32_t} val
 * @retval: none
 */
extern void drv_sys_ctr_osr_port_write(uint32_t val);

#ifdef __cplusplus
}
#endif

#endif

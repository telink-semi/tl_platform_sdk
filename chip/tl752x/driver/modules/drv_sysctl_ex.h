/*******************************************************************************************************
 *
 * @file    drv_sysctl_ex.h
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
#ifndef __DRV_SYSCTL_EX_H__
#define __DRV_SYSCTL_EX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"

/** @defgroup audio dma handshake select
 * @{
 */
#define DRV_SYSCTL_HS_FROM_AUDIO_DMA (0x0)
#define DRV_SYSCTL_HS_FROM_CPU2_DMA  (0x1)

/** @defgroup audio dma handshake select
 * @{
 */
#define DRV_SYSCTL_IIS0_DMA_TX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_0_POS)
#define DRV_SYSCTL_IIS1_DMA_TX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_1_POS)
#define DRV_SYSCTL_IIS2_DMA_TX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_2_POS)
#define DRV_SYSCTL_IIS3_DMA_TX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_3_POS)
#define DRV_SYSCTL_IIS0_DMA_RX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_4_POS)
#define DRV_SYSCTL_IIS1_DMA_RX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_5_POS)
#define DRV_SYSCTL_IIS2_DMA_RX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_6_POS)
#define DRV_SYSCTL_IIS3_DMA_RX_HS     (SYS_CTL_AUDIO_FUNC_DMA_SEL_7_POS)
#define DRV_SYSCTL_RESAMPLE_DMA_TX_HS (SYS_CTL_AUDIO_FUNC_DMA_SEL_8_POS)
#define DRV_SYSCTL_RESAMPLE_DMA_RX_HS (SYS_CTL_AUDIO_FUNC_DMA_SEL_9_POS)
#define DRV_SYSCTL_PMD0_DMA_HS        (SYS_CTL_AUDIO_FUNC_DMA_SEL_10_POS)
#define DRV_SYSCTL_PMDS_DMA_HS        (SYS_CTL_AUDIO_FUNC_DMA_SEL_11_POS)
#define DRV_SYSCTL_SPDIF_DMA_HS       (SYS_CTL_AUDIO_FUNC_DMA_SEL_12_POS)
#define DRV_SYSCTL_PMDC_DMA_HS        (SYS_CTL_AUDIO_FUNC_DMA_SEL_13_POS)

#define __DRV_SYSCTL_SET_AUDIO_FUNC_DMA_SEL(__DMA_HS_SEL__, __DMA_SEL__) MODIFY_REG(SYS_CTL->AUDIO_FUNC_DMA_SEL, (0x1UL << __DMA_HS_SEL__), (__DMA_SEL__ << __DMA_HS_SEL__))

/**
 * @brief  set usb configuration information
 *
 * @param  none
 * @return none
 * @note   none
 */
extern void drv_sysctl_usb_cfg_set(void);

extern void drv_sysctl_usb_idpad_set(void);

#ifdef __cplusplus
}
#endif

#endif

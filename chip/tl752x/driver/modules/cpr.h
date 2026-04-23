/*******************************************************************************************************
 *
 * @file    cpr.h
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
#ifndef __CPR_H__
#define __CPR_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

//RST_SET_CPU_SYSTEM offsetaddress : 0x0000
//RST_SET_CPU_SYSTEM RegResetValue : 0x000007ef
#define CPR_RSTN_CPU0_CORE_POS          (0U)
#define CPR_RSTN_CPU0_CORE_MSK          (0x1UL << CPR_RSTN_CPU0_CORE_POS) /*!< */
#define CPR_RSTN_CPU0_CORE              CPR_RSTN_CPU0_CORE_MSK
#define CPR_RSTN_CPU0_CORE_PULSE_POS    (1U)
#define CPR_RSTN_CPU0_CORE_PULSE_MSK    (0x1UL << CPR_RSTN_CPU0_CORE_PULSE_POS) /*!< */
#define CPR_RSTN_CPU0_CORE_PULSE        CPR_RSTN_CPU0_CORE_PULSE_MSK
#define CPR_RSTN_CPU0_SLV_POS           (2U)
#define CPR_RSTN_CPU0_SLV_MSK           (0x1UL << CPR_RSTN_CPU0_SLV_POS) /*!< */
#define CPR_RSTN_CPU0_SLV               CPR_RSTN_CPU0_SLV_MSK
#define CPR_RSTN_CPU0_BUS_POS           (3U)
#define CPR_RSTN_CPU0_BUS_MSK           (0x1UL << CPR_RSTN_CPU0_BUS_POS) /*!< */
#define CPR_RSTN_CPU0_BUS               CPR_RSTN_CPU0_BUS_MSK
#define CPR_RSTN_CPU1_CORE_POS          (5U)
#define CPR_RSTN_CPU1_CORE_MSK          (0x1UL << CPR_RSTN_CPU1_CORE_POS) /*!< */
#define CPR_RSTN_CPU1_CORE              CPR_RSTN_CPU1_CORE_MSK
#define CPR_RSTN_CPU1_CORE_PULSE_POS    (6U)
#define CPR_RSTN_CPU1_CORE_PULSE_MSK    (0x1UL << CPR_RSTN_CPU1_CORE_PULSE_POS) /*!< */
#define CPR_RSTN_CPU1_CORE_PULSE        CPR_RSTN_CPU1_CORE_PULSE_MSK
#define CPR_RSTN_CPU1_BUS_POS           (7U)
#define CPR_RSTN_CPU1_BUS_MSK           (0x1UL << CPR_RSTN_CPU1_BUS_POS) /*!< */
#define CPR_RSTN_CPU1_BUS               CPR_RSTN_CPU1_BUS_MSK
#define CPR_RSTN_CPU1_ILM_POS           (8U)
#define CPR_RSTN_CPU1_ILM_MSK           (0x1UL << CPR_RSTN_CPU1_ILM_POS) /*!< */
#define CPR_RSTN_CPU1_ILM               CPR_RSTN_CPU1_ILM_MSK
#define CPR_RSTN_CPU1_DLM_POS           (9U)
#define CPR_RSTN_CPU1_DLM_MSK           (0x1UL << CPR_RSTN_CPU1_DLM_POS) /*!< */
#define CPR_RSTN_CPU1_DLM               CPR_RSTN_CPU1_DLM_MSK
#define CPR_RSTN_SHRAM1_POS             (10U)
#define CPR_RSTN_SHRAM1_MSK             (0x1UL << CPR_RSTN_SHRAM1_POS) /*!< Shram1 reset, write 0 reset*/
#define CPR_RSTN_SHRAM1                 CPR_RSTN_SHRAM1_MSK
#define CPR_CPU0_SLV_PULSE_RST_MASK_POS (11U)
#define CPR_CPU0_SLV_PULSE_RST_MASK_MSK (0x1UL << CPR_CPU0_SLV_PULSE_RST_MASK_POS) /*!< */
#define CPR_CPU0_SLV_PULSE_RST_MASK     CPR_CPU0_SLV_PULSE_RST_MASK_MSK
#define CPR_CPU0_BUS_PULSE_RST_MASK_POS (12U)
#define CPR_CPU0_BUS_PULSE_RST_MASK_MSK (0x1UL << CPR_CPU0_BUS_PULSE_RST_MASK_POS) /*!< */
#define CPR_CPU0_BUS_PULSE_RST_MASK     CPR_CPU0_BUS_PULSE_RST_MASK_MSK

//RST_SET_MAIN_AHB_BUS0 offsetaddress : 0x0004
//RST_SET_MAIN_AHB_BUS0 RegResetValue : 0x00009BFF
#define CPR_RSTN_BT_SYS_POS       (0U)
#define CPR_RSTN_BT_SYS_MSK       (0x1UL << CPR_RSTN_BT_SYS_POS) /*!< bt_sys reset, write 0 reset*/
#define CPR_RSTN_BT_SYS           CPR_RSTN_BT_SYS_MSK
#define CPR_RSTN_SYS_CTL_POS      (1U)
#define CPR_RSTN_SYS_CTL_MSK      (0x1UL << CPR_RSTN_SYS_CTL_POS) /*!< sys_ctl reset, write 0 reset*/
#define CPR_RSTN_SYS_CTL          CPR_RSTN_SYS_CTL_MSK
#define CPR_RSTN_CFG_AHB_BUS_POS  (2U)
#define CPR_RSTN_CFG_AHB_BUS_MSK  (0x1UL << CPR_RSTN_CFG_AHB_BUS_POS) /*!< cfg_ahb_bus reset, write 0 reset*/
#define CPR_RSTN_CFG_AHB_BUS      CPR_RSTN_CFG_AHB_BUS_MSK
#define CPR_RSTN_USB1_H_POS       (3U)
#define CPR_RSTN_USB1_H_MSK       (0x1UL << CPR_RSTN_USB1_H_POS) /*!< usb1 bus reset, write 0 reset*/
#define CPR_RSTN_USB1_H           CPR_RSTN_USB1_H_MSK
#define CPR_RSTN_USB1_PHY_POS     (4U)
#define CPR_RSTN_USB1_PHY_MSK     (0x1UL << CPR_RSTN_USB1_PHY_POS) /*!< usb1 phy reset, write 0 reset*/
#define CPR_RSTN_USB1_PHY         CPR_RSTN_USB1_PHY_MSK
#define CPR_RSTN_SWIRE_POS        (5U)
#define CPR_RSTN_SWIRE_MSK        (0x1UL << CPR_RSTN_SWIRE_POS) /*!< Swire reset, write 0 reset*/
#define CPR_RSTN_SWIRE            CPR_RSTN_SWIRE_MSK
#define CPR_RSTN_TAHDT_H_POS        (6U)
#define CPR_RSTN_TAHDT_H_MSK        (0x1UL << CPR_RSTN_TAHDT_H_POS) /*!< TAHDT bus reset, write 0 reset*/
#define CPR_RSTN_TAHDT_H            CPR_RSTN_TAHDT_H_MSK
#define CPR_RSTN_CPU1_DMA_POS     (7U)
#define CPR_RSTN_CPU1_DMA_MSK     (0x1UL << CPR_RSTN_CPU1_DMA_POS) /*!< CPU1_dma reset, write 0 reset*/
#define CPR_RSTN_CPU1_DMA         CPR_RSTN_CPU1_DMA_MSK
#define CPR_RSTN_DWC_SSI_1_H_POS  (8U)
#define CPR_RSTN_DWC_SSI_1_H_MSK  (0x1UL << CPR_RSTN_DWC_SSI_1_H_POS) /*!< dwc_ssi_0_p reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI_1_H      CPR_RSTN_DWC_SSI_1_H_MSK
#define CPR_RSTN_DWC_SSI_0_H_POS  (9U)
#define CPR_RSTN_DWC_SSI_0_H_MSK  (0x1UL << CPR_RSTN_DWC_SSI_0_H_POS) /*!< dwc_ssi_0_p reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI_0_H      CPR_RSTN_DWC_SSI_0_H_MSK
#define CPR_RSTN_CPU_DMA_POS      (11U)
#define CPR_RSTN_CPU_DMA_MSK      (0x1UL << CPR_RSTN_CPU_DMA_POS) /*!< cpu_dma reset, write 0 reset*/
#define CPR_RSTN_CPU_DMA          CPR_RSTN_CPU_DMA_MSK
#define CPR_RSTN_HWA_AHB_BUS_POS  (12U)
#define CPR_RSTN_HWA_AHB_BUS_MSK  (0x1UL << CPR_RSTN_HWA_AHB_BUS_POS) /*!< hwa_ahb_bus reset, write 0 reset*/
#define CPR_RSTN_HWA_AHB_BUS      CPR_RSTN_HWA_AHB_BUS_MSK
#define CPR_RSTN_CPU2_APBBRG_POS  (13U)
#define CPR_RSTN_CPU2_APBBRG_MSK  (0x1UL << CPR_RSTN_CPU2_APBBRG_POS) /*!< CPU2 apb bridge reset, write 0 reset*/
#define CPR_RSTN_CPU2_APBBRG      CPR_RSTN_CPU2_APBBRG_MSK
#define CPR_RSTN_CPU2_H_POS       (14U)
#define CPR_RSTN_CPU2_H_MSK       (0x1UL << CPR_RSTN_CPU2_H_POS) /*!< CPU2_h reset, write 0 reset*/
#define CPR_RSTN_CPU2_H           CPR_RSTN_CPU2_H_MSK
#define CPR_RSTN_HWA2_AHB_BUS_POS (15U)
#define CPR_RSTN_HWA2_AHB_BUS_MSK (0x1UL << CPR_RSTN_HWA2_AHB_BUS_POS) /*!< hwa2_ahb_bus reset, write 0 reset*/
#define CPR_RSTN_HWA2_AHB_BUS     CPR_RSTN_HWA2_AHB_BUS_MSK

//RST_SET_MAIN_AHB_BUS1 offsetaddress : 0x0008
//RST_SET_MAIN_AHB_BUS1 RegResetValue : 0x00000778
#define CPR_RSTN_OSR_TRNG_POS     (3U)
#define CPR_RSTN_OSR_TRNG_MSK     (0x1UL << CPR_RSTN_OSR_TRNG_POS) /*!< osr_trng reset, write 0 reset*/
#define CPR_RSTN_OSR_TRNG         CPR_RSTN_OSR_TRNG_MSK
#define CPR_RSTN_DWC_SSI1_PHY_POS (4U)
#define CPR_RSTN_DWC_SSI1_PHY_MSK (0x1UL << CPR_RSTN_DWC_SSI1_PHY_POS) /*!< dwc_ssi1_phy reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI1_PHY     CPR_RSTN_DWC_SSI1_PHY_MSK
#define CPR_RSTN_DWC_SSI0_PHY_POS (5U)
#define CPR_RSTN_DWC_SSI0_PHY_MSK (0x1UL << CPR_RSTN_DWC_SSI0_PHY_POS) /*!< dwc_ssi0_phy reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI0_PHY     CPR_RSTN_DWC_SSI0_PHY_MSK
#define CPR_RSTN_BT_SYS_RF_POS    (6U)
#define CPR_RSTN_BT_SYS_RF_MSK    (0x1UL << CPR_RSTN_BT_SYS_RF_POS) /*!< rstn_bt_sys_rf reset, write 0 reset*/
#define CPR_RSTN_BT_SYS_RF        CPR_RSTN_BT_SYS_RF_MSK
#define CPR_RSTN_BT_SYS_32K_POS   (8U)
#define CPR_RSTN_BT_SYS_32K_MSK   (0x1UL << CPR_RSTN_BT_SYS_32K_POS) /*!< bt 32k system soft reset, write 0 reset*/
#define CPR_RSTN_BT_SYS_32K       CPR_RSTN_BT_SYS_32K_MSK
#define CPR_RSTN_AON_BUS_POS      (9U)
#define CPR_RSTN_AON_BUS_MSK      (0x1UL << CPR_RSTN_AON_BUS_POS) /*!< aon apb bridge reset, write 0 reset*/
#define CPR_RSTN_AON_BUS          CPR_RSTN_AON_BUS_MSK
#define CPR_RSTN_BT_SYS_BB_POS    (10U)
#define CPR_RSTN_BT_SYS_BB_MSK    (0x1UL << CPR_RSTN_BT_SYS_BB_POS) /*!< 2.4G BB soft reset, write 0 reset*/
#define CPR_RSTN_BT_SYS_BB        CPR_RSTN_BT_SYS_BB_MSK

//RST_SET_AUDIO_BUS offsetaddress : 0x000c
//RST_SET_AUDIO_BUS RegResetValue : 0x0
#define CPR_RSTN_PDMC_P_POS     (0U)
#define CPR_RSTN_PDMC_P_MSK     (0x1UL << CPR_RSTN_PDMC_P_POS) /*!< pdmc reset, write 0 reset*/
#define CPR_RSTN_PDMC_P         CPR_RSTN_PDMC_P_MSK
#define CPR_RSTN_PDM1_P_POS     (1U)
#define CPR_RSTN_PDM1_P_MSK     (0x1UL << CPR_RSTN_PDM1_P_POS) /*!< pdm1 reset, write 0 reset*/
#define CPR_RSTN_PDM1_P         CPR_RSTN_PDM1_P_MSK
#define CPR_RSTN_PDM0_P_POS     (2U)
#define CPR_RSTN_PDM0_P_MSK     (0x1UL << CPR_RSTN_PDM0_P_POS) /*!< pdm0 reset, write 0 reset*/
#define CPR_RSTN_PDM0_P         CPR_RSTN_PDM0_P_MSK
#define CPR_RSTN_I2S2_P_POS     (3U)
#define CPR_RSTN_I2S2_P_MSK     (0x1UL << CPR_RSTN_I2S2_P_POS) /*!< i2s2 pclk reset, write 0 reset*/
#define CPR_RSTN_I2S2_P         CPR_RSTN_I2S2_P_MSK
#define CPR_RSTN_I2S1_P_POS     (4U)
#define CPR_RSTN_I2S1_P_MSK     (0x1UL << CPR_RSTN_I2S1_P_POS) /*!< i2s1 pclk reset, write 0 reset*/
#define CPR_RSTN_I2S1_P         CPR_RSTN_I2S1_P_MSK
#define CPR_RSTN_I2S0_P_POS     (5U)
#define CPR_RSTN_I2S0_P_MSK     (0x1UL << CPR_RSTN_I2S0_P_POS) /*!< i2s0 pclk reset, write 0 reset*/
#define CPR_RSTN_I2S0_P         CPR_RSTN_I2S0_P_MSK
#define CPR_RSTN_AUDIO_DMA_POS  (6U)
#define CPR_RSTN_AUDIO_DMA_MSK  (0x1UL << CPR_RSTN_AUDIO_DMA_POS) /*!< audio_dma reset, write 0 reset*/
#define CPR_RSTN_AUDIO_DMA      CPR_RSTN_AUDIO_DMA_MSK
#define CPR_RSTN_AUDIO_BUS_POS  (7U)
#define CPR_RSTN_AUDIO_BUS_MSK  (0x1UL << CPR_RSTN_AUDIO_BUS_POS) /*!< audio_bus reset, write 0 reset*/
#define CPR_RSTN_AUDIO_BUS      CPR_RSTN_AUDIO_BUS_MSK
#define CPR_RSTN_CPU2_DMA_POS   (8U)
#define CPR_RSTN_CPU2_DMA_MSK   (0x1UL << CPR_RSTN_CPU2_DMA_POS) /*!< CPU2_dma reset, write 0 reset*/
#define CPR_RSTN_CPU2_DMA       CPR_RSTN_CPU2_DMA_MSK
#define CPR_RSTN_SPDIF_P_POS    (9U)
#define CPR_RSTN_SPDIF_P_MSK    (0x1UL << CPR_RSTN_SPDIF_P_POS) /*!< spdif reset, write 0 reset*/
#define CPR_RSTN_SPDIF_P        CPR_RSTN_SPDIF_P_MSK
#define CPR_RSTN_RESAMPLE_P_POS (10U)
#define CPR_RSTN_RESAMPLE_P_MSK (0x1UL << CPR_RSTN_RESAMPLE_P_POS) /*!< Universal resample bus reset, write 0 reset*/
#define CPR_RSTN_RESAMPLE_P     CPR_RSTN_RESAMPLE_P_MSK
#define CPR_RSTN_I2S3_P_POS     (13U)
#define CPR_RSTN_I2S3_P_MSK     (0x1UL << CPR_RSTN_I2S3_P_POS) /*!< i2s3 pclk reset, write 0 reset*/
#define CPR_RSTN_I2S3_P         CPR_RSTN_I2S3_P_MSK

//RST_SET_MAIN_APB offsetaddress : 0x0010
//RST_SET_MAIN_APB RegResetValue : 0x0000ffff
#define CPR_RSTN_TIMER_P_POS        (0U)
#define CPR_RSTN_TIMER_P_MSK        (0x1UL << CPR_RSTN_TIMER_P_POS) /*!< timer_p reset, write 0 reset*/
#define CPR_RSTN_TIMER_P            CPR_RSTN_TIMER_P_MSK
#define CPR_RSTN_SYSTIMER_P_POS     (1U)
#define CPR_RSTN_SYSTIMER_P_MSK     (0x1UL << CPR_RSTN_SYSTIMER_P_POS) /*!< systimer_p reset, write 0 reset*/
#define CPR_RSTN_SYSTIMER_P         CPR_RSTN_SYSTIMER_P_MSK
#define CPR_RSTN_DW_APB_SSI_S_P_POS (2U)
#define CPR_RSTN_DW_APB_SSI_S_P_MSK (0x1UL << CPR_RSTN_DW_APB_SSI_S_P_POS) /*!< dw_apb_ssi_s_p reset, write 0 reset*/
#define CPR_RSTN_DW_APB_SSI_S_P     CPR_RSTN_DW_APB_SSI_S_P_MSK
#define CPR_RSTN_DW_APB_SSI_M_P_POS (3U)
#define CPR_RSTN_DW_APB_SSI_M_P_MSK (0x1UL << CPR_RSTN_DW_APB_SSI_M_P_POS) /*!< dw_apb_ssi_m_p reset, write 0 reset*/
#define CPR_RSTN_DW_APB_SSI_M_P     CPR_RSTN_DW_APB_SSI_M_P_MSK
#define CPR_RSTN_UART1_P_POS        (4U)
#define CPR_RSTN_UART1_P_MSK        (0x1UL << CPR_RSTN_UART1_P_POS) /*!< uart1 reset, write 0 reset*/
#define CPR_RSTN_UART1_P            CPR_RSTN_UART1_P_MSK
#define CPR_RSTN_UART_P_POS         (5U)
#define CPR_RSTN_UART_P_MSK         (0x1UL << CPR_RSTN_UART_P_POS) /*!< uart reset, write 0 reset*/
#define CPR_RSTN_UART_P             CPR_RSTN_UART_P_MSK
#define CPR_RSTN_I2C1_P_POS         (6U)
#define CPR_RSTN_I2C1_P_MSK         (0x1UL << CPR_RSTN_I2C1_P_POS) /*!< i2c1 reset, write 0 reset*/
#define CPR_RSTN_I2C1_P             CPR_RSTN_I2C1_P_MSK
#define CPR_RSTN_I2C_P_POS          (7U)
#define CPR_RSTN_I2C_P_MSK          (0x1UL << CPR_RSTN_I2C_P_POS) /*!< i2c reset, write 0 reset*/
#define CPR_RSTN_I2C_P              CPR_RSTN_I2C_P_MSK
#define CPR_RSTN_CPU2_WDT_P_POS     (8U)
#define CPR_RSTN_CPU2_WDT_P_MSK     (0x1UL << CPR_RSTN_CPU2_WDT_P_POS) /*!< CPU2_wdt_p reset, write 0 reset*/
#define CPR_RSTN_CPU2_WDT_P         CPR_RSTN_CPU2_WDT_P_MSK
#define CPR_RSTN_CPU_WDT_P_POS      (9U)
#define CPR_RSTN_CPU_WDT_P_MSK      (0x1UL << CPR_RSTN_CPU_WDT_P_POS) /*!< cpu_wdt_p reset, write 0 reset*/
#define CPR_RSTN_CPU_WDT_P          CPR_RSTN_CPU_WDT_P_MSK
#define CPR_RSTN_CPU_CPU1_WDT_P_POS (10U)
#define CPR_RSTN_CPU_CPU1_WDT_P_MSK (0x1UL << CPR_RSTN_CPU_CPU1_WDT_P_POS) /*!< cpu_CPU1_wdt_p reset, write 0 reset*/
#define CPR_RSTN_CPU_CPU1_WDT_P     CPR_RSTN_CPU_CPU1_WDT_P_MSK
#define CPR_RSTN_TIMER1_P_POS       (11U)
#define CPR_RSTN_TIMER1_P_MSK       (0x1UL << CPR_RSTN_TIMER1_P_POS) /*!< timer1_p reset, write 0 reset*/
#define CPR_RSTN_TIMER1_P           CPR_RSTN_TIMER1_P_MSK
#define CPR_RSTN_GPIO_POS           (12U)
#define CPR_RSTN_GPIO_MSK           (0x1UL << CPR_RSTN_GPIO_POS) /*!< gpio reset, write 0 reset*/
#define CPR_RSTN_GPIO               CPR_RSTN_GPIO_MSK
#define CPR_RSTN_GP_ADC_POS         (13U)
#define CPR_RSTN_GP_ADC_MSK         (0x1UL << CPR_RSTN_GP_ADC_POS) /*!< gp adc reset, write 0 reset*/
#define CPR_RSTN_GP_ADC             CPR_RSTN_GP_ADC_MSK
#define CPR_RSTN_EFUSE_POS          (14U)
#define CPR_RSTN_EFUSE_MSK          (0x1UL << CPR_RSTN_EFUSE_POS) /*!< efuse reset, write 0 reset*/
#define CPR_RSTN_EFUSE              CPR_RSTN_EFUSE_MSK
#define CPR_RSTN_I2C2_P_POS         (15U)
#define CPR_RSTN_I2C2_P_MSK         (0x1UL << CPR_RSTN_I2C2_P_POS) /*!< i2c2 reset, write 0 reset*/
#define CPR_RSTN_I2C2_P             CPR_RSTN_I2C2_P_MSK

//RST_SET_FUNC0 offsetaddress : 0x0014
//RST_SET_FUNC0 RegResetValue : 0xffff
#define CPR_RSTN_UART_DIV_POS     (0U)
#define CPR_RSTN_UART_DIV_MSK     (0x1UL << CPR_RSTN_UART_DIV_POS) /*!< uart clock divider reset*/
#define CPR_RSTN_UART_DIV         CPR_RSTN_UART_DIV_MSK
#define CPR_RSTN_DW_APB_SSI_S_POS (1U)
#define CPR_RSTN_DW_APB_SSI_S_MSK (0x1UL << CPR_RSTN_DW_APB_SSI_S_POS) /*!< dw_apb_ssi_s reset, write 0 reset*/
#define CPR_RSTN_DW_APB_SSI_S     CPR_RSTN_DW_APB_SSI_S_MSK
#define CPR_RSTN_DW_APB_SSI_M_POS (2U)
#define CPR_RSTN_DW_APB_SSI_M_MSK (0x1UL << CPR_RSTN_DW_APB_SSI_M_POS) /*!< dw_apb_ssi_m reset, write 0 reset*/
#define CPR_RSTN_DW_APB_SSI_M     CPR_RSTN_DW_APB_SSI_M_MSK
#define CPR_RSTN_UART1_POS        (3U)
#define CPR_RSTN_UART1_MSK        (0x1UL << CPR_RSTN_UART1_POS) /*!< uart1 reset, write 0 reset*/
#define CPR_RSTN_UART1            CPR_RSTN_UART1_MSK
#define CPR_RSTN_UART_POS         (4U)
#define CPR_RSTN_UART_MSK         (0x1UL << CPR_RSTN_UART_POS) /*!< uart reset, write 0 reset*/
#define CPR_RSTN_UART             CPR_RSTN_UART_MSK
#define CPR_RSTN_I2C1_POS         (5U)
#define CPR_RSTN_I2C1_MSK         (0x1UL << CPR_RSTN_I2C1_POS) /*!< i2c1 reset, write 0 reset*/
#define CPR_RSTN_I2C1             CPR_RSTN_I2C1_MSK
#define CPR_RSTN_I2C_POS          (6U)
#define CPR_RSTN_I2C_MSK          (0x1UL << CPR_RSTN_I2C_POS) /*!< i2c reset, write 0 reset*/
#define CPR_RSTN_I2C              CPR_RSTN_I2C_MSK
#define CPR_RSTN_DWC_SSI_1_POS    (7U)
#define CPR_RSTN_DWC_SSI_1_MSK    (0x1UL << CPR_RSTN_DWC_SSI_1_POS) /*!< dwc_ssi_1 reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI_1        CPR_RSTN_DWC_SSI_1_MSK
#define CPR_RSTN_DWC_SSI_0_POS    (8U)
#define CPR_RSTN_DWC_SSI_0_MSK    (0x1UL << CPR_RSTN_DWC_SSI_0_POS) /*!< dwc_ssi_0 reset, write 0 reset*/
#define CPR_RSTN_DWC_SSI_0        CPR_RSTN_DWC_SSI_0_MSK
#define CPR_RSTN_CPU2_WDT_POS     (9U)
#define CPR_RSTN_CPU2_WDT_MSK     (0x1UL << CPR_RSTN_CPU2_WDT_POS) /*!< CPU2_wdt reset, write 0 reset*/
#define CPR_RSTN_CPU2_WDT         CPR_RSTN_CPU2_WDT_MSK
#define CPR_RSTN_CPU_WDT_POS      (10U)
#define CPR_RSTN_CPU_WDT_MSK      (0x1UL << CPR_RSTN_CPU_WDT_POS) /*!< cpu_wdt reset, write 0 reset*/
#define CPR_RSTN_CPU_WDT          CPR_RSTN_CPU_WDT_MSK
#define CPR_RSTN_TIMER1_POS       (11U)
#define CPR_RSTN_TIMER1_MSK       (0x1UL << CPR_RSTN_TIMER1_POS) /*!< timer reset, write 0 reset*/
#define CPR_RSTN_TIMER1           CPR_RSTN_TIMER1_MSK
#define CPR_RSTN_TIMER2_POS       (12U)
#define CPR_RSTN_TIMER2_MSK       (0x1UL << CPR_RSTN_TIMER2_POS) /*!< timer reset, write 0 reset*/
#define CPR_RSTN_TIMER2           CPR_RSTN_TIMER2_MSK
#define CPR_RSTN_TIMER3_POS       (13U)
#define CPR_RSTN_TIMER3_MSK       (0x1UL << CPR_RSTN_TIMER3_POS) /*!< timer reset, write 0 reset*/
#define CPR_RSTN_TIMER3           CPR_RSTN_TIMER3_MSK
#define CPR_RSTN_TIMER4_POS       (14U)
#define CPR_RSTN_TIMER4_MSK       (0x1UL << CPR_RSTN_TIMER4_POS) /*!< timer reset, write 0 reset*/
#define CPR_RSTN_TIMER4           CPR_RSTN_TIMER4_MSK
#define CPR_RSTN_I2C2_POS         (15U)
#define CPR_RSTN_I2C2_MSK         (0x1UL << CPR_RSTN_I2C2_POS) /*!< i2c2 reset, write 0 reset*/
#define CPR_RSTN_I2C2             CPR_RSTN_I2C2_MSK

//RST_SET_FUNC1 offsetaddress : 0x0018
//RST_SET_FUNC1 RegResetValue : 0x0000ffff
#define CPR_RSTN_UTMI_P_POS     (0U)
#define CPR_RSTN_UTMI_P_MSK     (0x1UL << CPR_RSTN_UTMI_P_POS) /*!< USB module reset, write 0 reset*/
#define CPR_RSTN_UTMI_P         CPR_RSTN_UTMI_P_MSK
#define CPR_RSTN_USB_H_POS      (1U)
#define CPR_RSTN_USB_H_MSK      (0x1UL << CPR_RSTN_USB_H_POS) /*!< USB module reset, write 0 reset*/
#define CPR_RSTN_USB_H          CPR_RSTN_USB_H_MSK
#define CPR_RSTN_PHY_POS        (2U)
#define CPR_RSTN_PHY_MSK        (0x1UL << CPR_RSTN_PHY_POS) /*!< USB module reset, write 0 reset*/
#define CPR_RSTN_PHY            CPR_RSTN_PHY_MSK
#define CPR_RSTN_ANC_POS        (3U)
#define CPR_RSTN_ANC_MSK        (0x1UL << CPR_RSTN_ANC_POS) /*!< Anc module reset, write 0 reset*/
#define CPR_RSTN_ANC            CPR_RSTN_ANC_MSK
#define CPR_RSTN_UART2_P_POS    (4U)
#define CPR_RSTN_UART2_P_MSK    (0x1UL << CPR_RSTN_UART2_P_POS) /*!< */
#define CPR_RSTN_UART2_P        CPR_RSTN_UART2_P_MSK
#define CPR_RSTN_UART2_POS      (5U)
#define CPR_RSTN_UART2_MSK      (0x1UL << CPR_RSTN_UART2_POS) /*!< */
#define CPR_RSTN_UART2          CPR_RSTN_UART2_MSK
#define CPR_RSTN_UART3_P_POS    (6U)
#define CPR_RSTN_UART3_P_MSK    (0x1UL << CPR_RSTN_UART3_P_POS) /*!< */
#define CPR_RSTN_UART3_P        CPR_RSTN_UART3_P_MSK
#define CPR_RSTN_UART3_POS      (7U)
#define CPR_RSTN_UART3_MSK      (0x1UL << CPR_RSTN_UART3_POS) /*!< */
#define CPR_RSTN_UART3          CPR_RSTN_UART3_MSK
#define CPR_RSTN_UART4_P_POS    (8U)
#define CPR_RSTN_UART4_P_MSK    (0x1UL << CPR_RSTN_UART4_P_POS) /*!< */
#define CPR_RSTN_UART4_P        CPR_RSTN_UART4_P_MSK
#define CPR_RSTN_UART4_POS      (9U)
#define CPR_RSTN_UART4_MSK      (0x1UL << CPR_RSTN_UART4_POS) /*!< */
#define CPR_RSTN_UART4          CPR_RSTN_UART4_MSK
#define CPR_RSTN_CPU_RF_WDT_POS (10U)
#define CPR_RSTN_CPU_RF_WDT_MSK (0x1UL << CPR_RSTN_CPU_RF_WDT_POS) /*!< cpu_rf_wdt reset, write 0 reset*/
#define CPR_RSTN_CPU_RF_WDT     CPR_RSTN_CPU_RF_WDT_MSK
#define CPR_RSTN_SYSTIMER_POS   (11U)
#define CPR_RSTN_SYSTIMER_MSK   (0x1UL << CPR_RSTN_SYSTIMER_POS) /*!< systimer reset, write 0 reset*/
#define CPR_RSTN_SYSTIMER       CPR_RSTN_SYSTIMER_MSK
#define CPR_RSTN_TIMER1_1_POS   (12U)
#define CPR_RSTN_TIMER1_1_MSK   (0x1UL << CPR_RSTN_TIMER1_1_POS) /*!< timer1 reset, write 0 reset*/
#define CPR_RSTN_TIMER1_1       CPR_RSTN_TIMER1_1_MSK
#define CPR_RSTN_TIMER1_2_POS   (13U)
#define CPR_RSTN_TIMER1_2_MSK   (0x1UL << CPR_RSTN_TIMER1_2_POS) /*!< timer1 reset, write 0 reset*/
#define CPR_RSTN_TIMER1_2       CPR_RSTN_TIMER1_2_MSK
#define CPR_RSTN_TIMER1_3_POS   (14U)
#define CPR_RSTN_TIMER1_3_MSK   (0x1UL << CPR_RSTN_TIMER1_3_POS) /*!< timer1 reset, write 0 reset*/
#define CPR_RSTN_TIMER1_3       CPR_RSTN_TIMER1_3_MSK
#define CPR_RSTN_TIMER1_4_POS   (15U)
#define CPR_RSTN_TIMER1_4_MSK   (0x1UL << CPR_RSTN_TIMER1_4_POS) /*!< timer1 reset, write 0 reset*/
#define CPR_RSTN_TIMER1_4       CPR_RSTN_TIMER1_4_MSK

//RST_SET_AUDIO_FUNC offsetaddress : 0x001c
//RST_SET_AUDIO_FUNC RegResetValue : 0x0
#define CPR_RSTN_PDMC_POS        (0U)
#define CPR_RSTN_PDMC_MSK        (0x1UL << CPR_RSTN_PDMC_POS) /*!< pdm0 reset, write 0 reset*/
#define CPR_RSTN_PDMC            CPR_RSTN_PDMC_MSK
#define CPR_RSTN_PDM1_POS        (1U)
#define CPR_RSTN_PDM1_MSK        (0x1UL << CPR_RSTN_PDM1_POS) /*!< pdm1 reset, write 0 reset*/
#define CPR_RSTN_PDM1            CPR_RSTN_PDM1_MSK
#define CPR_RSTN_PDM0_POS        (2U)
#define CPR_RSTN_PDM0_MSK        (0x1UL << CPR_RSTN_PDM0_POS) /*!< pdmc reset, write 0 reset*/
#define CPR_RSTN_PDM0            CPR_RSTN_PDM0_MSK
#define CPR_RSTN_I2S2_POS        (3U)
#define CPR_RSTN_I2S2_MSK        (0x1UL << CPR_RSTN_I2S2_POS) /*!< i2s2 reset, write 0 reset*/
#define CPR_RSTN_I2S2            CPR_RSTN_I2S2_MSK
#define CPR_RSTN_I2S1_POS        (4U)
#define CPR_RSTN_I2S1_MSK        (0x1UL << CPR_RSTN_I2S1_POS) /*!< i2s1 reset, write 0 reset*/
#define CPR_RSTN_I2S1            CPR_RSTN_I2S1_MSK
#define CPR_RSTN_I2S0_POS        (5U)
#define CPR_RSTN_I2S0_MSK        (0x1UL << CPR_RSTN_I2S0_POS) /*!< i2s0 reset, write 0 reset*/
#define CPR_RSTN_I2S0            CPR_RSTN_I2S0_MSK
#define CPR_RSTN_CODEC_POS       (6U)
#define CPR_RSTN_CODEC_MSK       (0x1UL << CPR_RSTN_CODEC_POS) /*!< codec reset, write 0 reset*/
#define CPR_RSTN_CODEC           CPR_RSTN_CODEC_MSK
#define CPR_RSTN_CPU2_M_POS      (7U)
#define CPR_RSTN_CPU2_M_MSK      (0x1UL << CPR_RSTN_CPU2_M_POS) /*!< CPU2_m reset, write 0 reset*/
#define CPR_RSTN_CPU2_M          CPR_RSTN_CPU2_M_MSK
#define CPR_RSTN_CODEC_ADC_POS   (9U)
#define CPR_RSTN_CODEC_ADC_MSK   (0x1UL << CPR_RSTN_CODEC_ADC_POS) /*!< codec_adc reset, write 0 reset*/
#define CPR_RSTN_CODEC_ADC       CPR_RSTN_CODEC_ADC_MSK
#define CPR_RSTN_CODEC_6P144_POS (10U)
#define CPR_RSTN_CODEC_6P144_MSK (0x1UL << CPR_RSTN_CODEC_6P144_POS) /*!< codec_adc_6p144 reset, write 0 reset*/
#define CPR_RSTN_CODEC_6P144     CPR_RSTN_CODEC_6P144_MSK
#define CPR_RSTN_I2S3_POS        (11U)
#define CPR_RSTN_I2S3_MSK        (0x1UL << CPR_RSTN_I2S3_POS) /*!< i2s3 reset, write 0 reset*/
#define CPR_RSTN_I2S3            CPR_RSTN_I2S3_MSK
#define CPR_RSTN_RESAMPLE_POS    (12U)
#define CPR_RSTN_RESAMPLE_MSK    (0x1UL << CPR_RSTN_RESAMPLE_POS) /*!< General resample module reset, write 0 reset*/
#define CPR_RSTN_RESAMPLE        CPR_RSTN_RESAMPLE_MSK

//CLK_EN_MCU_SYSTEM offsetaddress : 0x0020
//CLK_EN_MCU_SYSTEM RegResetValue : 0xf
#define CPR_CPU0_CORE_CLK_EN_POS (0U)
#define CPR_CPU0_CORE_CLK_EN_MSK (0x1UL << CPR_CPU0_CORE_CLK_EN_POS) /*!< CPU0 CPU core clock enable*/
#define CPR_CPU0_CORE_CLK_EN     CPR_CPU0_CORE_CLK_EN_MSK
#define CPR_CPU0_DC_CLK_EN_POS   (1U)
#define CPR_CPU0_DC_CLK_EN_MSK   (0x1UL << CPR_CPU0_DC_CLK_EN_POS) /*!< CPU0 cpu dcache clock enable*/
#define CPR_CPU0_DC_CLK_EN       CPR_CPU0_DC_CLK_EN_MSK
#define CPR_CPU0_LM_CLK_EN_POS   (2U)
#define CPR_CPU0_LM_CLK_EN_MSK   (0x1UL << CPR_CPU0_LM_CLK_EN_POS) /*!< CPU0 cpu lm clock enable*/
#define CPR_CPU0_LM_CLK_EN       CPR_CPU0_LM_CLK_EN_MSK
#define CPR_CPU0_ROM_CLK_EN_POS  (3U)
#define CPR_CPU0_ROM_CLK_EN_MSK  (0x1UL << CPR_CPU0_ROM_CLK_EN_POS) /*!< CPU0 cpu rom clock enable*/
#define CPR_CPU0_ROM_CLK_EN      CPR_CPU0_ROM_CLK_EN_MSK
#define CPR_OSR_TRNG_CLK_EN_POS  (4U)
#define CPR_OSR_TRNG_CLK_EN_MSK  (0x1UL << CPR_OSR_TRNG_CLK_EN_POS) /*!< osr_trng_clk clock enable*/
#define CPR_OSR_TRNG_CLK_EN      CPR_OSR_TRNG_CLK_EN_MSK
#define CPR_CPU0_SUSP_CLK_BK_POS (5U)
#define CPR_CPU0_SUSP_CLK_BK_MSK (0x1UL << CPR_CPU0_SUSP_CLK_BK_POS) /*!< CPU0 cpu clock enable back up for debug during suspend*/
#define CPR_CPU0_SUSP_CLK_BK     CPR_CPU0_SUSP_CLK_BK_MSK

//CLK_EN_AUDIO_SYSTEM offsetaddress : 0x0024
//CLK_EN_AUDIO_SYSTEM RegResetValue : 0x0
#define CPR_AUDIO_BUS_CLK_EN_POS   (0U)
#define CPR_AUDIO_BUS_CLK_EN_MSK   (0x1UL << CPR_AUDIO_BUS_CLK_EN_POS) /*!< audio system bus clock enable*/
#define CPR_AUDIO_BUS_CLK_EN       CPR_AUDIO_BUS_CLK_EN_MSK
#define CPR_CPU2_CLK_EN_POS        (1U)
#define CPR_CPU2_CLK_EN_MSK        (0x1UL << CPR_CPU2_CLK_EN_POS) /*!< hifi5 CPU2 clock enable*/
#define CPR_CPU2_CLK_EN            CPR_CPU2_CLK_EN_MSK
#define CPR_CPU2_DMA_HCLK_EN_POS   (2U)
#define CPR_CPU2_DMA_HCLK_EN_MSK   (0x1UL << CPR_CPU2_DMA_HCLK_EN_POS) /*!< CPU2_dma_clk clock enable*/
#define CPR_CPU2_DMA_HCLK_EN       CPR_CPU2_DMA_HCLK_EN_MSK
#define CPR_CPU2_WDT_PCLK_EN_POS   (3U)
#define CPR_CPU2_WDT_PCLK_EN_MSK   (0x1UL << CPR_CPU2_WDT_PCLK_EN_POS) /*!< CPU2_wdt_pclk clock enable*/
#define CPR_CPU2_WDT_PCLK_EN       CPR_CPU2_WDT_PCLK_EN_MSK
#define CPR_CPU2_WDT_TCLK_EN_POS   (4U)
#define CPR_CPU2_WDT_TCLK_EN_MSK   (0x1UL << CPR_CPU2_WDT_TCLK_EN_POS) /*!< CPU2_wdt_tclk clock enable*/
#define CPR_CPU2_WDT_TCLK_EN       CPR_CPU2_WDT_TCLK_EN_MSK
#define CPR_CPU2_APB_HCLK_EN_POS   (5U)
#define CPR_CPU2_APB_HCLK_EN_MSK   (0x1UL << CPR_CPU2_APB_HCLK_EN_POS) /*!< CPU2_apb_hclk clock enable*/
#define CPR_CPU2_APB_HCLK_EN       CPR_CPU2_APB_HCLK_EN_MSK
#define CPR_CODEC_PCLK_EN_POS      (6U)
#define CPR_CODEC_PCLK_EN_MSK      (0x1UL << CPR_CODEC_PCLK_EN_POS) /*!< codec_pclk clock enable*/
#define CPR_CODEC_PCLK_EN          CPR_CODEC_PCLK_EN_MSK
#define CPR_CODEC_DAC_CLK_EN_POS   (7U)
#define CPR_CODEC_DAC_CLK_EN_MSK   (0x1UL << CPR_CODEC_DAC_CLK_EN_POS) /*!< codec_dac clock enable*/
#define CPR_CODEC_DAC_CLK_EN       CPR_CODEC_DAC_CLK_EN_MSK
#define CPR_CODEC_ADC_CLK_EN_POS   (8U)
#define CPR_CODEC_ADC_CLK_EN_MSK   (0x1UL << CPR_CODEC_ADC_CLK_EN_POS) /*!< codec_adc clock always enabled*/
#define CPR_CODEC_ADC_CLK_EN       CPR_CODEC_ADC_CLK_EN_MSK
#define CPR_CODEC_6P144_CLK_EN_POS (11U)
#define CPR_CODEC_6P144_CLK_EN_MSK (0x1UL << CPR_CODEC_6P144_CLK_EN_POS) /*!< codec_6p144 clock enable*/
#define CPR_CODEC_6P144_CLK_EN     CPR_CODEC_6P144_CLK_EN_MSK
#define CPR_ANC_CLK_EN_POS         (12U)
#define CPR_ANC_CLK_EN_MSK         (0x1UL << CPR_ANC_CLK_EN_POS) /*!< anc clock enable*/
#define CPR_ANC_CLK_EN             CPR_ANC_CLK_EN_MSK
#define CPR_MCLK1_EN_POS           (13U)
#define CPR_MCLK1_EN_MSK           (0x1UL << CPR_MCLK1_EN_POS) /*!< mclk1 clock enable*/
#define CPR_MCLK1_EN               CPR_MCLK1_EN_MSK

//CLK_EN_RF_SYSTEM offsetaddress : 0x0028
//CLK_EN_RF_SYSTEM RegResetValue : 0x8000
#define CPR_BT_SYS_HCLK_EN_POS       (0U)
#define CPR_BT_SYS_HCLK_EN_MSK       (0x1UL << CPR_BT_SYS_HCLK_EN_POS) /*!< bt_sys_hclk clock enable*/
#define CPR_BT_SYS_HCLK_EN           CPR_BT_SYS_HCLK_EN_MSK
#define CPR_BT_SYS_CLK_EN_POS        (1U)
#define CPR_BT_SYS_CLK_EN_MSK        (0x1UL << CPR_BT_SYS_CLK_EN_POS) /*!< bt_sys_clk clock enable*/
#define CPR_BT_SYS_CLK_EN            CPR_BT_SYS_CLK_EN_MSK
#define CPR_BT_RFDIG_CLK_EN_POS      (2U)
#define CPR_BT_RFDIG_CLK_EN_MSK      (0x1UL << CPR_BT_RFDIG_CLK_EN_POS) /*!< rf dfe clock enable*/
#define CPR_BT_RFDIG_CLK_EN          CPR_BT_RFDIG_CLK_EN_MSK
#define CPR_SYSTIMER_PCLK_EN_POS     (3U)
#define CPR_SYSTIMER_PCLK_EN_MSK     (0x1UL << CPR_SYSTIMER_PCLK_EN_POS) /*!< systimer_pclk clock enable*/
#define CPR_SYSTIMER_PCLK_EN         CPR_SYSTIMER_PCLK_EN_MSK
#define CPR_SYSTIMER_CLK_EN_POS      (4U)
#define CPR_SYSTIMER_CLK_EN_MSK      (0x1UL << CPR_SYSTIMER_CLK_EN_POS) /*!< systimer_clk clock enable*/
#define CPR_SYSTIMER_CLK_EN          CPR_SYSTIMER_CLK_EN_MSK
#define CPR_TAHDT_HCLK_EN_POS          (5U)
#define CPR_TAHDT_HCLK_EN_MSK          (0x1UL << CPR_TAHDT_HCLK_EN_POS) /*!< sle_hclk clock enable*/
#define CPR_TAHDT_HCLK_EN              CPR_TAHDT_HCLK_EN_MSK
#define CPR_CPU1_DMA_HCLK_EN_POS     (6U)
#define CPR_CPU1_DMA_HCLK_EN_MSK     (0x1UL << CPR_CPU1_DMA_HCLK_EN_POS) /*!< CPU1_dma_hclk_en clock enable*/
#define CPR_CPU1_DMA_HCLK_EN         CPR_CPU1_DMA_HCLK_EN_MSK
#define CPR_RCCAL_CLK_EN_POS         (12U)
#define CPR_RCCAL_CLK_EN_MSK         (0x1UL << CPR_RCCAL_CLK_EN_POS) /*!< 32k/48m rc calibration clock enable*/
#define CPR_RCCAL_CLK_EN             CPR_RCCAL_CLK_EN_MSK
#define CPR_GPIO_PCLK_EN_POS         (13U)
#define CPR_GPIO_PCLK_EN_MSK         (0x1UL << CPR_GPIO_PCLK_EN_POS) /*!< gpio_pclk clock enable*/
#define CPR_GPIO_PCLK_EN             CPR_GPIO_PCLK_EN_MSK
#define CPR_GPIO_DEBOUNCE_CLK_EN_POS (14U)
#define CPR_GPIO_DEBOUNCE_CLK_EN_MSK (0x1UL << CPR_GPIO_DEBOUNCE_CLK_EN_POS) /*!< gpio_debounce_clk clock enable*/
#define CPR_GPIO_DEBOUNCE_CLK_EN     CPR_GPIO_DEBOUNCE_CLK_EN_MSK
#define CPR_EFUSE_PCLK_EN_POS        (15U)
#define CPR_EFUSE_PCLK_EN_MSK        (0x1UL << CPR_EFUSE_PCLK_EN_POS) /*!< efuse_pclk clock enable*/
#define CPR_EFUSE_PCLK_EN            CPR_EFUSE_PCLK_EN_MSK

//CLK_EN_AHB offsetaddress : 0x002c
//CLK_EN_AHB RegResetValue : 0xe000
#define CPR_CFG_AHB_BUS_CLK_EN_POS  (0U)
#define CPR_CFG_AHB_BUS_CLK_EN_MSK  (0x1UL << CPR_CFG_AHB_BUS_CLK_EN_POS) /*!< cfg_ahb_bus_clk clock enable*/
#define CPR_CFG_AHB_BUS_CLK_EN      CPR_CFG_AHB_BUS_CLK_EN_MSK
#define CPR_SYS_CTL_CLK_EN_POS      (1U)
#define CPR_SYS_CTL_CLK_EN_MSK      (0x1UL << CPR_SYS_CTL_CLK_EN_POS) /*!< sys_ctl_clk clock enable*/
#define CPR_SYS_CTL_CLK_EN          CPR_SYS_CTL_CLK_EN_MSK
#define CPR_HWA_AHB_BUS_CLK_EN_POS  (2U)
#define CPR_HWA_AHB_BUS_CLK_EN_MSK  (0x1UL << CPR_HWA_AHB_BUS_CLK_EN_POS) /*!< hwa_ahb_bus_clk clock enable*/
#define CPR_HWA_AHB_BUS_CLK_EN      CPR_HWA_AHB_BUS_CLK_EN_MSK
#define CPR_HWA2_AHB_BUS_CLK_EN_POS (3U)
#define CPR_HWA2_AHB_BUS_CLK_EN_MSK (0x1UL << CPR_HWA2_AHB_BUS_CLK_EN_POS) /*!< hwa2_ahb_bus_clk clock enable*/
#define CPR_HWA2_AHB_BUS_CLK_EN     CPR_HWA2_AHB_BUS_CLK_EN_MSK
#define CPR_CPU_DMA_HCLK_EN_POS     (4U)
#define CPR_CPU_DMA_HCLK_EN_MSK     (0x1UL << CPR_CPU_DMA_HCLK_EN_POS) /*!< cpu_dma_hclk clock enable*/
#define CPR_CPU_DMA_HCLK_EN         CPR_CPU_DMA_HCLK_EN_MSK
#define CPR_AUDIO_DMA_HCLK_EN_POS   (5U)
#define CPR_AUDIO_DMA_HCLK_EN_MSK   (0x1UL << CPR_AUDIO_DMA_HCLK_EN_POS) /*!< audio_dma_hclk clock enable*/
#define CPR_AUDIO_DMA_HCLK_EN       CPR_AUDIO_DMA_HCLK_EN_MSK
#define CPR_USB_HCLK_EN_POS         (6U)
#define CPR_USB_HCLK_EN_MSK         (0x1UL << CPR_USB_HCLK_EN_POS) /*!< usb_hclk clock enable*/
#define CPR_USB_HCLK_EN             CPR_USB_HCLK_EN_MSK
#define CPR_USB_PHY_CLK_EN_POS      (7U)
#define CPR_USB_PHY_CLK_EN_MSK      (0x1UL << CPR_USB_PHY_CLK_EN_POS) /*!< usb_phy_clk clock enable*/
#define CPR_USB_PHY_CLK_EN          CPR_USB_PHY_CLK_EN_MSK
#define CPR_UTMIFS_CLK48_EN_POS     (8U)
#define CPR_UTMIFS_CLK48_EN_MSK     (0x1UL << CPR_UTMIFS_CLK48_EN_POS) /*!< utmifs_clk48m clock enable*/
#define CPR_UTMIFS_CLK48_EN         CPR_UTMIFS_CLK48_EN_MSK
#define CPR_DWC_SSI0_HCLK_EN_POS    (9U)
#define CPR_DWC_SSI0_HCLK_EN_MSK    (0x1UL << CPR_DWC_SSI0_HCLK_EN_POS) /*!< dwc_ssi0_mclk clock enable*/
#define CPR_DWC_SSI0_HCLK_EN        CPR_DWC_SSI0_HCLK_EN_MSK
#define CPR_DWC_SSI0_MCLK_EN_POS    (10U)
#define CPR_DWC_SSI0_MCLK_EN_MSK    (0x1UL << CPR_DWC_SSI0_MCLK_EN_POS) /*!< dwc_ssi0_hclk clock enable*/
#define CPR_DWC_SSI0_MCLK_EN        CPR_DWC_SSI0_MCLK_EN_MSK
#define CPR_DWC_SSI1_HCLK_EN_POS    (11U)
#define CPR_DWC_SSI1_HCLK_EN_MSK    (0x1UL << CPR_DWC_SSI1_HCLK_EN_POS) /*!< dwc_ssi1_mclk clock enable*/
#define CPR_DWC_SSI1_HCLK_EN        CPR_DWC_SSI1_HCLK_EN_MSK
#define CPR_DWC_SSI1_MCLK_EN_POS    (12U)
#define CPR_DWC_SSI1_MCLK_EN_MSK    (0x1UL << CPR_DWC_SSI1_MCLK_EN_POS) /*!< dwc_ssi1_hclk clock enable*/
#define CPR_DWC_SSI1_MCLK_EN        CPR_DWC_SSI1_MCLK_EN_MSK
#define CPR_SWIRE_HCLK_EN_POS       (13U)
#define CPR_SWIRE_HCLK_EN_MSK       (0x1UL << CPR_SWIRE_HCLK_EN_POS) /*!< swire_hclk clock enable*/
#define CPR_SWIRE_HCLK_EN           CPR_SWIRE_HCLK_EN_MSK
#define CPR_USB1_HCLK_EN_POS        (14U)
#define CPR_USB1_HCLK_EN_MSK        (0x1UL << CPR_USB1_HCLK_EN_POS) /*!< usb1_hclk clock enable*/
#define CPR_USB1_HCLK_EN            CPR_USB1_HCLK_EN_MSK
#define CPR_USB1_CLK48M_EN_POS      (15U)
#define CPR_USB1_CLK48M_EN_MSK      (0x1UL << CPR_USB1_CLK48M_EN_POS) /*!< usb1 48m clock enable*/
#define CPR_USB1_CLK48M_EN          CPR_USB1_CLK48M_EN_MSK

//CLK_EN_APB0 offsetaddress : 0x0030
//CLK_EN_APB0 RegResetValue : 0x0
#define CPR_UART1_PCLK_EN_POS        (0U)
#define CPR_UART1_PCLK_EN_MSK        (0x1UL << CPR_UART1_PCLK_EN_POS) /*!< uart1_pclk clock enable*/
#define CPR_UART1_PCLK_EN            CPR_UART1_PCLK_EN_MSK
#define CPR_UART1_MCLK_EN_POS        (1U)
#define CPR_UART1_MCLK_EN_MSK        (0x1UL << CPR_UART1_MCLK_EN_POS) /*!< uart1_mclk clock enable*/
#define CPR_UART1_MCLK_EN            CPR_UART1_MCLK_EN_MSK
#define CPR_DW_APB_SSI_S_PCLK_EN_POS (2U)
#define CPR_DW_APB_SSI_S_PCLK_EN_MSK (0x1UL << CPR_DW_APB_SSI_S_PCLK_EN_POS) /*!< dw_apb_ssi_s_pclk clock enable*/
#define CPR_DW_APB_SSI_S_PCLK_EN     CPR_DW_APB_SSI_S_PCLK_EN_MSK
#define CPR_DW_APB_SSI_S_CLK_EN_POS  (3U)
#define CPR_DW_APB_SSI_S_CLK_EN_MSK  (0x1UL << CPR_DW_APB_SSI_S_CLK_EN_POS) /*!< dw_apb_ssi_s_clk clock enable*/
#define CPR_DW_APB_SSI_S_CLK_EN      CPR_DW_APB_SSI_S_CLK_EN_MSK
#define CPR_DW_APB_SSI_M_PCLK_EN_POS (4U)
#define CPR_DW_APB_SSI_M_PCLK_EN_MSK (0x1UL << CPR_DW_APB_SSI_M_PCLK_EN_POS) /*!< dw_apb_ssi_m_pclk clock enable*/
#define CPR_DW_APB_SSI_M_PCLK_EN     CPR_DW_APB_SSI_M_PCLK_EN_MSK
#define CPR_DW_APB_SSI_MCLK_EN_POS   (5U)
#define CPR_DW_APB_SSI_MCLK_EN_MSK   (0x1UL << CPR_DW_APB_SSI_MCLK_EN_POS) /*!< dw_apb_ssi_mclk clock enable*/
#define CPR_DW_APB_SSI_MCLK_EN       CPR_DW_APB_SSI_MCLK_EN_MSK
#define CPR_I2C_PCLK_EN_POS          (6U)
#define CPR_I2C_PCLK_EN_MSK          (0x1UL << CPR_I2C_PCLK_EN_POS) /*!< i2c_pclk clock enable*/
#define CPR_I2C_PCLK_EN              CPR_I2C_PCLK_EN_MSK
#define CPR_I2C_MCLK_EN_POS          (7U)
#define CPR_I2C_MCLK_EN_MSK          (0x1UL << CPR_I2C_MCLK_EN_POS) /*!< i2c_mclk clock enable*/
#define CPR_I2C_MCLK_EN              CPR_I2C_MCLK_EN_MSK
#define CPR_I2C1_PCLK_EN_POS         (8U)
#define CPR_I2C1_PCLK_EN_MSK         (0x1UL << CPR_I2C1_PCLK_EN_POS) /*!< i2c1_pclk clock enable*/
#define CPR_I2C1_PCLK_EN             CPR_I2C1_PCLK_EN_MSK
#define CPR_I2C1_MCLK_EN_POS         (9U)
#define CPR_I2C1_MCLK_EN_MSK         (0x1UL << CPR_I2C1_MCLK_EN_POS) /*!< i2c1_mclk clock enable*/
#define CPR_I2C1_MCLK_EN             CPR_I2C1_MCLK_EN_MSK
#define CPR_CPU0_WDT_PCLK_EN_POS     (10U)
#define CPR_CPU0_WDT_PCLK_EN_MSK     (0x1UL << CPR_CPU0_WDT_PCLK_EN_POS) /*!< CPU0_wdt_pclk clock enable*/
#define CPR_CPU0_WDT_PCLK_EN         CPR_CPU0_WDT_PCLK_EN_MSK
#define CPR_CPU0_WDT_TCLK_EN_POS     (11U)
#define CPR_CPU0_WDT_TCLK_EN_MSK     (0x1UL << CPR_CPU0_WDT_TCLK_EN_POS) /*!< CPU0_wdt_tclk clock enable*/
#define CPR_CPU0_WDT_TCLK_EN         CPR_CPU0_WDT_TCLK_EN_MSK
#define CPR_UART2_PCLK_EN_POS        (12U)
#define CPR_UART2_PCLK_EN_MSK        (0x1UL << CPR_UART2_PCLK_EN_POS) /*!< uart2_pclk clock enable*/
#define CPR_UART2_PCLK_EN            CPR_UART2_PCLK_EN_MSK
#define CPR_UART2_MCLK_EN_POS        (13U)
#define CPR_UART2_MCLK_EN_MSK        (0x1UL << CPR_UART2_MCLK_EN_POS) /*!< uart2_mclk clock enable*/
#define CPR_UART2_MCLK_EN            CPR_UART2_MCLK_EN_MSK
#define CPR_UART3_PCLK_EN_POS        (14U)
#define CPR_UART3_PCLK_EN_MSK        (0x1UL << CPR_UART3_PCLK_EN_POS) /*!< uart3_pclk clock enable*/
#define CPR_UART3_PCLK_EN            CPR_UART3_PCLK_EN_MSK
#define CPR_UART3_MCLK_EN_POS        (15U)
#define CPR_UART3_MCLK_EN_MSK        (0x1UL << CPR_UART3_MCLK_EN_POS) /*!< uart3_mclk clock enable*/
#define CPR_UART3_MCLK_EN            CPR_UART3_MCLK_EN_MSK

//CLK_EN_APB1 offsetaddress : 0x0034
//CLK_EN_APB1 RegResetValue : 0x4000
#define CPR_TIMER_PCLK_EN_POS     (0U)
#define CPR_TIMER_PCLK_EN_MSK     (0x1UL << CPR_TIMER_PCLK_EN_POS) /*!< timer_pclk clock enable*/
#define CPR_TIMER_PCLK_EN         CPR_TIMER_PCLK_EN_MSK
#define CPR_TIMER_1_MCLK_EN_POS   (1U)
#define CPR_TIMER_1_MCLK_EN_MSK   (0x1UL << CPR_TIMER_1_MCLK_EN_POS) /*!< timer_1_mclk clock enable*/
#define CPR_TIMER_1_MCLK_EN       CPR_TIMER_1_MCLK_EN_MSK
#define CPR_TIMER_2_MCLK_EN_POS   (2U)
#define CPR_TIMER_2_MCLK_EN_MSK   (0x1UL << CPR_TIMER_2_MCLK_EN_POS) /*!< timer_2_mclk clock enable*/
#define CPR_TIMER_2_MCLK_EN       CPR_TIMER_2_MCLK_EN_MSK
#define CPR_TIMER_3_MCLK_EN_POS   (3U)
#define CPR_TIMER_3_MCLK_EN_MSK   (0x1UL << CPR_TIMER_3_MCLK_EN_POS) /*!< timer_3_mclk clock enable*/
#define CPR_TIMER_3_MCLK_EN       CPR_TIMER_3_MCLK_EN_MSK
#define CPR_TIMER_4_MCLK_EN_POS   (4U)
#define CPR_TIMER_4_MCLK_EN_MSK   (0x1UL << CPR_TIMER_4_MCLK_EN_POS) /*!< timer_4_mclk clock enable*/
#define CPR_TIMER_4_MCLK_EN       CPR_TIMER_4_MCLK_EN_MSK
#define CPR_TIMER1_PCLK_EN_POS    (5U)
#define CPR_TIMER1_PCLK_EN_MSK    (0x1UL << CPR_TIMER1_PCLK_EN_POS) /*!< timer1_pclk clock enable*/
#define CPR_TIMER1_PCLK_EN        CPR_TIMER1_PCLK_EN_MSK
#define CPR_TIMER1_1_MCLK_EN_POS  (6U)
#define CPR_TIMER1_1_MCLK_EN_MSK  (0x1UL << CPR_TIMER1_1_MCLK_EN_POS) /*!< timer1_1_mclk clock enable*/
#define CPR_TIMER1_1_MCLK_EN      CPR_TIMER1_1_MCLK_EN_MSK
#define CPR_TIMER1_2_MCLK_EN_POS  (7U)
#define CPR_TIMER1_2_MCLK_EN_MSK  (0x1UL << CPR_TIMER1_2_MCLK_EN_POS) /*!< timer1_2_mclk clock enable*/
#define CPR_TIMER1_2_MCLK_EN      CPR_TIMER1_2_MCLK_EN_MSK
#define CPR_TIMER1_3_MCLK_EN_POS  (8U)
#define CPR_TIMER1_3_MCLK_EN_MSK  (0x1UL << CPR_TIMER1_3_MCLK_EN_POS) /*!< timer1_3_mclk clock enable*/
#define CPR_TIMER1_3_MCLK_EN      CPR_TIMER1_3_MCLK_EN_MSK
#define CPR_TIMER1_4_MCLK_EN_POS  (9U)
#define CPR_TIMER1_4_MCLK_EN_MSK  (0x1UL << CPR_TIMER1_4_MCLK_EN_POS) /*!< timer1_4_mclk clock enable*/
#define CPR_TIMER1_4_MCLK_EN      CPR_TIMER1_4_MCLK_EN_MSK
#define CPR_RESAMPLE_PCLK_EN_POS  (11U)
#define CPR_RESAMPLE_PCLK_EN_MSK  (0x1UL << CPR_RESAMPLE_PCLK_EN_POS) /*!< resample_pclk clock enable*/
#define CPR_RESAMPLE_PCLK_EN      CPR_RESAMPLE_PCLK_EN_MSK
#define CPR_RESAMPLE_MCLK_EN_POS  (12U)
#define CPR_RESAMPLE_MCLK_EN_MSK  (0x1UL << CPR_RESAMPLE_MCLK_EN_POS) /*!< resample_mclk clock enable*/
#define CPR_RESAMPLE_MCLK_EN      CPR_RESAMPLE_MCLK_EN_MSK
#define CPR_CLKOUT0_EN_POS        (13U)
#define CPR_CLKOUT0_EN_MSK        (0x1UL << CPR_CLKOUT0_EN_POS) /*!< clkout0 clock enable*/
#define CPR_CLKOUT0_EN            CPR_CLKOUT0_EN_MSK
#define CPR_CLKOUT0_DIR_POS       (14U)
#define CPR_CLKOUT0_DIR_MSK       (0x1UL << CPR_CLKOUT0_DIR_POS) /*!< clkout0_dir output 1 input 0*/
#define CPR_CLKOUT0_DIR           CPR_CLKOUT0_DIR_MSK
#define CPR_AUDIO_APB_HCLK_EN_POS (15U)
#define CPR_AUDIO_APB_HCLK_EN_MSK (0x1UL << CPR_AUDIO_APB_HCLK_EN_POS) /*!< audio_apb_hclk clock enable*/
#define CPR_AUDIO_APB_HCLK_EN     CPR_AUDIO_APB_HCLK_EN_MSK

//CLK_EN_APB2 offsetaddress : 0x0038
//CLK_EN_APB2 RegResetValue : 0x0
#define CPR_I2S0_PCLK_EN_POS  (0U)
#define CPR_I2S0_PCLK_EN_MSK  (0x1UL << CPR_I2S0_PCLK_EN_POS) /*!< i2s0_pclk clock enable*/
#define CPR_I2S0_PCLK_EN      CPR_I2S0_PCLK_EN_MSK
#define CPR_I2S0_MCLK_EN_POS  (1U)
#define CPR_I2S0_MCLK_EN_MSK  (0x1UL << CPR_I2S0_MCLK_EN_POS) /*!< i2s0_mclk clock enable*/
#define CPR_I2S0_MCLK_EN      CPR_I2S0_MCLK_EN_MSK
#define CPR_I2S1_PCLK_EN_POS  (2U)
#define CPR_I2S1_PCLK_EN_MSK  (0x1UL << CPR_I2S1_PCLK_EN_POS) /*!< i2s1_pclk clock enable*/
#define CPR_I2S1_PCLK_EN      CPR_I2S1_PCLK_EN_MSK
#define CPR_I2S1_MCLK_EN_POS  (3U)
#define CPR_I2S1_MCLK_EN_MSK  (0x1UL << CPR_I2S1_MCLK_EN_POS) /*!< i2s1_mclk clock enable*/
#define CPR_I2S1_MCLK_EN      CPR_I2S1_MCLK_EN_MSK
#define CPR_I2S2_PCLK_EN_POS  (4U)
#define CPR_I2S2_PCLK_EN_MSK  (0x1UL << CPR_I2S2_PCLK_EN_POS) /*!< i2s2_pclk clock enable*/
#define CPR_I2S2_PCLK_EN      CPR_I2S2_PCLK_EN_MSK
#define CPR_I2S2_MCLK_EN_POS  (5U)
#define CPR_I2S2_MCLK_EN_MSK  (0x1UL << CPR_I2S2_MCLK_EN_POS) /*!< i2s2_mclk clock enable*/
#define CPR_I2S2_MCLK_EN      CPR_I2S2_MCLK_EN_MSK
#define CPR_I2S3_PCLK_EN_POS  (6U)
#define CPR_I2S3_PCLK_EN_MSK  (0x1UL << CPR_I2S3_PCLK_EN_POS) /*!< i2s3_pclk clock enable*/
#define CPR_I2S3_PCLK_EN      CPR_I2S3_PCLK_EN_MSK
#define CPR_I2S3_MCLK_EN_POS  (7U)
#define CPR_I2S3_MCLK_EN_MSK  (0x1UL << CPR_I2S3_MCLK_EN_POS) /*!< i2s3_mclk clock enable*/
#define CPR_I2S3_MCLK_EN      CPR_I2S3_MCLK_EN_MSK
#define CPR_PDM0_PCLK_EN_POS  (8U)
#define CPR_PDM0_PCLK_EN_MSK  (0x1UL << CPR_PDM0_PCLK_EN_POS) /*!< pdm0_pclk clock enable*/
#define CPR_PDM0_PCLK_EN      CPR_PDM0_PCLK_EN_MSK
#define CPR_PDM0_MCLK_EN_POS  (9U)
#define CPR_PDM0_MCLK_EN_MSK  (0x1UL << CPR_PDM0_MCLK_EN_POS) /*!< pdm0_mclk clock enable*/
#define CPR_PDM0_MCLK_EN      CPR_PDM0_MCLK_EN_MSK
#define CPR_PDM1_PCLK_EN_POS  (10U)
#define CPR_PDM1_PCLK_EN_MSK  (0x1UL << CPR_PDM1_PCLK_EN_POS) /*!< pdm1_pclk clock enable*/
#define CPR_PDM1_PCLK_EN      CPR_PDM1_PCLK_EN_MSK
#define CPR_PDM1_MCLK_EN_POS  (11U)
#define CPR_PDM1_MCLK_EN_MSK  (0x1UL << CPR_PDM1_MCLK_EN_POS) /*!< pdm1_mclk clock enable*/
#define CPR_PDM1_MCLK_EN      CPR_PDM1_MCLK_EN_MSK
#define CPR_PDMC_PCLK_EN_POS  (12U)
#define CPR_PDMC_PCLK_EN_MSK  (0x1UL << CPR_PDMC_PCLK_EN_POS) /*!< pdmc_pclk clock enable*/
#define CPR_PDMC_PCLK_EN      CPR_PDMC_PCLK_EN_MSK
#define CPR_PDMC_MCLK_EN_POS  (13U)
#define CPR_PDMC_MCLK_EN_MSK  (0x1UL << CPR_PDMC_MCLK_EN_POS) /*!< pdmc_mclk clock enable*/
#define CPR_PDMC_MCLK_EN      CPR_PDMC_MCLK_EN_MSK
#define CPR_SPDIF_PCLK_EN_POS (14U)
#define CPR_SPDIF_PCLK_EN_MSK (0x1UL << CPR_SPDIF_PCLK_EN_POS) /*!< spdif pclk clock enable*/
#define CPR_SPDIF_PCLK_EN     CPR_SPDIF_PCLK_EN_MSK
#define CPR_SPDIF_MCLK_EN_POS (15U)
#define CPR_SPDIF_MCLK_EN_MSK (0x1UL << CPR_SPDIF_MCLK_EN_POS) /*!< spdif mclk clock enable*/
#define CPR_SPDIF_MCLK_EN     CPR_SPDIF_MCLK_EN_MSK

//CLK_EN_APB3 offsetaddress : 0x003c
//CLK_EN_APB3 RegResetValue : 0x0
#define CPR_CPU1_WDT_PCLK_EN_POS (0U)
#define CPR_CPU1_WDT_PCLK_EN_MSK (0x1UL << CPR_CPU1_WDT_PCLK_EN_POS) /*!< CPU1_wdt_pclk enable*/
#define CPR_CPU1_WDT_PCLK_EN     CPR_CPU1_WDT_PCLK_EN_MSK
#define CPR_CPU1_WDT_TCLK_EN_POS (1U)
#define CPR_CPU1_WDT_TCLK_EN_MSK (0x1UL << CPR_CPU1_WDT_TCLK_EN_POS) /*!< CPU1_wdt_tclk enable*/
#define CPR_CPU1_WDT_TCLK_EN     CPR_CPU1_WDT_TCLK_EN_MSK
#define CPR_GP_ADC_PCLK_EN_POS   (2U)
#define CPR_GP_ADC_PCLK_EN_MSK   (0x1UL << CPR_GP_ADC_PCLK_EN_POS) /*!< gp_adc_pclk clock enable*/
#define CPR_GP_ADC_PCLK_EN       CPR_GP_ADC_PCLK_EN_MSK
#define CPR_I2C2_PCLK_EN_POS     (3U)
#define CPR_I2C2_PCLK_EN_MSK     (0x1UL << CPR_I2C2_PCLK_EN_POS) /*!< i2c2_pclk clock enable*/
#define CPR_I2C2_PCLK_EN         CPR_I2C2_PCLK_EN_MSK
#define CPR_I2C2_MCLK_EN_POS     (4U)
#define CPR_I2C2_MCLK_EN_MSK     (0x1UL << CPR_I2C2_MCLK_EN_POS) /*!< i2c2_mclk clock enable*/
#define CPR_I2C2_MCLK_EN         CPR_I2C2_MCLK_EN_MSK
#define CPR_UART_PCLK_EN_POS     (5U)
#define CPR_UART_PCLK_EN_MSK     (0x1UL << CPR_UART_PCLK_EN_POS) /*!< uart_pclk clock enable*/
#define CPR_UART_PCLK_EN         CPR_UART_PCLK_EN_MSK
#define CPR_UART_MCLK_EN_POS     (6U)
#define CPR_UART_MCLK_EN_MSK     (0x1UL << CPR_UART_MCLK_EN_POS) /*!< uart_mclk clock enable*/
#define CPR_UART_MCLK_EN         CPR_UART_MCLK_EN_MSK
#define CPR_UART4_PCLK_EN_POS    (7U)
#define CPR_UART4_PCLK_EN_MSK    (0x1UL << CPR_UART4_PCLK_EN_POS) /*!< uart4_pclk clock enable*/
#define CPR_UART4_PCLK_EN        CPR_UART4_PCLK_EN_MSK
#define CPR_UART4_MCLK_EN_POS    (8U)
#define CPR_UART4_MCLK_EN_MSK    (0x1UL << CPR_UART4_MCLK_EN_POS) /*!< uart4_mclk clock enable*/
#define CPR_UART4_MCLK_EN        CPR_UART4_MCLK_EN_MSK
#define CPR_CPU1_APB_HCLK_EN_POS (9U)
#define CPR_CPU1_APB_HCLK_EN_MSK (0x1UL << CPR_CPU1_APB_HCLK_EN_POS) /*!< CPU1_apb_hclk enable*/
#define CPR_CPU1_APB_HCLK_EN     CPR_CPU1_APB_HCLK_EN_MSK
#define CPR_PMU_PCLK_EN_POS      (13U)
#define CPR_PMU_PCLK_EN_MSK      (0x1UL << CPR_PMU_PCLK_EN_POS) /*!< pmu_pclk clock enable*/
#define CPR_PMU_PCLK_EN          CPR_PMU_PCLK_EN_MSK
#define CPR_RTC_PCLK_EN_POS      (14U)
#define CPR_RTC_PCLK_EN_MSK      (0x1UL << CPR_RTC_PCLK_EN_POS) /*!< rtc_pclk clock enable*/
#define CPR_RTC_PCLK_EN          CPR_RTC_PCLK_EN_MSK
#define CPR_AON_APB_HCLK_EN_POS  (15U)
#define CPR_AON_APB_HCLK_EN_MSK  (0x1UL << CPR_AON_APB_HCLK_EN_POS) /*!< aon_apb_hclk clock enable*/
#define CPR_AON_APB_HCLK_EN      CPR_AON_APB_HCLK_EN_MSK

//CLK_MUX offsetaddress : 0x0050
//CLK_MUX RegResetValue : 0x0
#define CPR_MCLK1_SEL_POS           (0U)
#define CPR_MCLK1_SEL_MSK           (0x3UL << CPR_MCLK1_SEL_POS) /*!< mclk1 selection 0/1:clkin0 2:clk_pll0_out 3:clk_pll1_out*/
#define CPR_MCLK1_SEL               CPR_MCLK1_SEL_MSK
#define CPR_MCLK1_SEL_W(X)          ((X) << CPR_MCLK1_SEL_POS)
#define CPR_UART_MCLK_SRC_SEL_POS   (2U)
#define CPR_UART_MCLK_SRC_SEL_MSK   (0x3UL << CPR_UART_MCLK_SRC_SEL_POS) /*!< uart0_mclk selection 0: clk_hfxo 1: clk_dblr 2: divided from uart_mul/uart_div*/
#define CPR_UART_MCLK_SRC_SEL       CPR_UART_MCLK_SRC_SEL_MSK
#define CPR_UART_MCLK_SRC_SEL_W(X)  ((X) << CPR_UART_MCLK_SRC_SEL_POS)
#define CPR_UART1_MCLK_SRC_SEL_POS  (4U)
#define CPR_UART1_MCLK_SRC_SEL_MSK  (0x3UL << CPR_UART1_MCLK_SRC_SEL_POS) /*!< uart1_mclk selection 0: clk_hfxo 1: clk_dblr 2: divided from uart_mul/uart_div*/
#define CPR_UART1_MCLK_SRC_SEL      CPR_UART1_MCLK_SRC_SEL_MSK
#define CPR_UART1_MCLK_SRC_SEL_W(X) ((X) << CPR_UART1_MCLK_SRC_SEL_POS)
#define CPR_UART2_MCLK_SRC_SEL_POS  (6U)
#define CPR_UART2_MCLK_SRC_SEL_MSK  (0x3UL << CPR_UART2_MCLK_SRC_SEL_POS) /*!< uart2_mclk selection 0: clk_hfxo 1: clk_dblr 2: divided from uart_mul/uart_div*/
#define CPR_UART2_MCLK_SRC_SEL      CPR_UART2_MCLK_SRC_SEL_MSK
#define CPR_UART2_MCLK_SRC_SEL_W(X) ((X) << CPR_UART2_MCLK_SRC_SEL_POS)
#define CPR_UART3_MCLK_SRC_SEL_POS  (8U)
#define CPR_UART3_MCLK_SRC_SEL_MSK  (0x3UL << CPR_UART3_MCLK_SRC_SEL_POS) /*!< uart3_mclk selection 0: clk_hfxo 1: clk_dblr 2: divided from uart_mul/uart_div*/
#define CPR_UART3_MCLK_SRC_SEL      CPR_UART3_MCLK_SRC_SEL_MSK
#define CPR_UART3_MCLK_SRC_SEL_W(X) ((X) << CPR_UART3_MCLK_SRC_SEL_POS)
#define CPR_UART4_MCLK_SRC_SEL_POS  (10U)
#define CPR_UART4_MCLK_SRC_SEL_MSK  (0x3UL << CPR_UART4_MCLK_SRC_SEL_POS) /*!< uart4_mclk selection 0: clk_hfxo 1: clk_dblr 2: divided from uart_mul/uart_div*/
#define CPR_UART4_MCLK_SRC_SEL      CPR_UART4_MCLK_SRC_SEL_MSK
#define CPR_UART4_MCLK_SRC_SEL_W(X) ((X) << CPR_UART4_MCLK_SRC_SEL_POS)
#define CPR_ANC_CLK_SRC_SEL_POS     (14U)
#define CPR_ANC_CLK_SRC_SEL_MSK     (0x3UL << CPR_ANC_CLK_SRC_SEL_POS) /*!< ANC clock source selection 0: anc_clk48m from doubler clock 48MHz 1: anc_clk48m from hfxo 24MHz 2: anc_clk48m from mclk0 frequency division 3: anc_clk96m from mclk0 frequency division; anc_clk48m from anc_clk96m binary frequency division*/
#define CPR_ANC_CLK_SRC_SEL         CPR_ANC_CLK_SRC_SEL_MSK
#define CPR_ANC_CLK_SRC_SEL_W(X)    ((X) << CPR_ANC_CLK_SRC_SEL_POS)
#define CPR_CPU0_MTIME_CLK_SEL_POS  (16U)
#define CPR_CPU0_MTIME_CLK_SEL_MSK  (0x1UL << CPR_CPU0_MTIME_CLK_SEL_POS) /*!< CPU0 cpu mtime clock select 0: 32k rc osc 1: divided from clk_hfxo*/
#define CPR_CPU0_MTIME_CLK_SEL      CPR_CPU0_MTIME_CLK_SEL_MSK
#define CPR_CPU0_MTIME_CLK_SEL_W(X) ((X) << CPR_CPU0_MTIME_CLK_SEL_POS)
#define CPR_CPU1_MTIME_CLK_SEL_POS  (17U)
#define CPR_CPU1_MTIME_CLK_SEL_MSK  (0x1UL << CPR_CPU1_MTIME_CLK_SEL_POS) /*!< CPU1 cpu mtime clock select 0: 32k rc osc 1: divided from clk_hfxo*/
#define CPR_CPU1_MTIME_CLK_SEL      CPR_CPU1_MTIME_CLK_SEL_MSK
#define CPR_CPU1_MTIME_CLK_SEL_W(X) ((X) << CPR_CPU1_MTIME_CLK_SEL_POS)
#define CPR_CPU2_CLK_SEL_POS        (21U)
#define CPR_CPU2_CLK_SEL_MSK        (0x3UL << CPR_CPU2_CLK_SEL_POS) /*!< CPU2_hclk Selection: 00: mclk0_g_div; 01: CPU0_system_clk 10: CPU1_system_clk 11: ahb_clk*/
#define CPR_CPU2_CLK_SEL            CPR_CPU2_CLK_SEL_MSK
#define CPR_CPU2_CLK_SEL_W(X)       ((X) << CPR_CPU2_CLK_SEL_POS)
#define CPR_I2S1_MCLK_SEL_POS       (26U)
#define CPR_I2S1_MCLK_SEL_MSK       (0x1UL << CPR_I2S1_MCLK_SEL_POS) /*!< 0: i2s1_mclk_pre 1: i2s0_mclk_pre*/
#define CPR_I2S1_MCLK_SEL           CPR_I2S1_MCLK_SEL_MSK
#define CPR_I2S1_MCLK_SEL_W(X)      ((X) << CPR_I2S1_MCLK_SEL_POS)
#define CPR_I2S2_MCLK_SEL_POS       (27U)
#define CPR_I2S2_MCLK_SEL_MSK       (0x1UL << CPR_I2S2_MCLK_SEL_POS) /*!< 0: i2s2_mclk_pre 1: i2s0_mclk_pre*/
#define CPR_I2S2_MCLK_SEL           CPR_I2S2_MCLK_SEL_MSK
#define CPR_I2S2_MCLK_SEL_W(X)      ((X) << CPR_I2S2_MCLK_SEL_POS)
#define CPR_I2S3_MCLK_SEL_POS       (28U)
#define CPR_I2S3_MCLK_SEL_MSK       (0x1UL << CPR_I2S3_MCLK_SEL_POS) /*!< 0: i2s3_mclk_pre 1: i2s0_mclk_pre*/
#define CPR_I2S3_MCLK_SEL           CPR_I2S3_MCLK_SEL_MSK
#define CPR_I2S3_MCLK_SEL_W(X)      ((X) << CPR_I2S3_MCLK_SEL_POS)

//CLK_DIV_BUS offsetaddress : 0x0054
//CLK_DIV_BUS RegResetValue : 0x0100
#define CPR_CPU1_APB_DIV_VAL_POS  (8U)
#define CPR_CPU1_APB_DIV_VAL_MSK  (0xffUL << CPR_CPU1_APB_DIV_VAL_POS) /*!< CPU1 apb frequency division factor*/
#define CPR_CPU1_APB_DIV_VAL      CPR_CPU1_APB_DIV_VAL_MSK
#define CPR_CPU1_APB_DIV_VAL_W(X) ((X) << CPR_CPU1_APB_DIV_VAL_POS)
#define CPR_AHB_DIV_VAL_POS       (16U)
#define CPR_AHB_DIV_VAL_MSK       (0xffUL << CPR_AHB_DIV_VAL_POS) /*!< ahb_div divider factor*/
#define CPR_AHB_DIV_VAL           CPR_AHB_DIV_VAL_MSK
#define CPR_AHB_DIV_VAL_W(X)      ((X) << CPR_AHB_DIV_VAL_POS)
#define CPR_MCLK0_G_DIV_VAL_POS   (24U)
#define CPR_MCLK0_G_DIV_VAL_MSK   (0xffUL << CPR_MCLK0_G_DIV_VAL_POS) /*!< mclk0_g_div divider factor*/
#define CPR_MCLK0_G_DIV_VAL       CPR_MCLK0_G_DIV_VAL_MSK
#define CPR_MCLK0_G_DIV_VAL_W(X)  ((X) << CPR_MCLK0_G_DIV_VAL_POS)

//CLK_DIV_CPU offsetaddress : 0x0058
//CLK_DIV_CPU RegResetValue : 0x17170000
#define CPR_CPU0_SYSTEM_CLK_DIV_VAL_POS  (0U)
#define CPR_CPU0_SYSTEM_CLK_DIV_VAL_MSK  (0xffUL << CPR_CPU0_SYSTEM_CLK_DIV_VAL_POS) /*!< CPU0 cpu clk frequency division factor*/
#define CPR_CPU0_SYSTEM_CLK_DIV_VAL      CPR_CPU0_SYSTEM_CLK_DIV_VAL_MSK
#define CPR_CPU0_SYSTEM_CLK_DIV_VAL_W(X) ((X) << CPR_CPU0_SYSTEM_CLK_DIV_VAL_POS)
#define CPR_CPU1_SYSTEM_CLK_DIV_VAL_POS  (8U)
#define CPR_CPU1_SYSTEM_CLK_DIV_VAL_MSK  (0xffUL << CPR_CPU1_SYSTEM_CLK_DIV_VAL_POS) /*!< CPU1 cpu/bus clk frequency division factor*/
#define CPR_CPU1_SYSTEM_CLK_DIV_VAL      CPR_CPU1_SYSTEM_CLK_DIV_VAL_MSK
#define CPR_CPU1_SYSTEM_CLK_DIV_VAL_W(X) ((X) << CPR_CPU1_SYSTEM_CLK_DIV_VAL_POS)
#define CPR_CPU0_MTIME_DIV_VAL_POS       (16U)
#define CPR_CPU0_MTIME_DIV_VAL_MSK       (0xffUL << CPR_CPU0_MTIME_DIV_VAL_POS) /*!< CPU0_mtime_clk div value when using clk_hfxo as source*/
#define CPR_CPU0_MTIME_DIV_VAL           CPR_CPU0_MTIME_DIV_VAL_MSK
#define CPR_CPU0_MTIME_DIV_VAL_W(X)      ((X) << CPR_CPU0_MTIME_DIV_VAL_POS)
#define CPR_CPU1_MTIME_DIV_VAL_POS       (24U)
#define CPR_CPU1_MTIME_DIV_VAL_MSK       (0xffUL << CPR_CPU1_MTIME_DIV_VAL_POS) /*!< CPU1_mtime_clk div value when using clk_hfxo as source*/
#define CPR_CPU1_MTIME_DIV_VAL           CPR_CPU1_MTIME_DIV_VAL_MSK
#define CPR_CPU1_MTIME_DIV_VAL_W(X)      ((X) << CPR_CPU1_MTIME_DIV_VAL_POS)

//CLK_DIV_FUNC0 offsetaddress : 0x005c
//CLK_DIV_FUNC0 RegResetValue : 0x1000000
#define CPR_DWC_SSI1_M_DIV_VAL_POS  (0U)
#define CPR_DWC_SSI1_M_DIV_VAL_MSK  (0xffUL << CPR_DWC_SSI1_M_DIV_VAL_POS) /*!< dwc_ssi1_m frequency division factor*/
#define CPR_DWC_SSI1_M_DIV_VAL      CPR_DWC_SSI1_M_DIV_VAL_MSK
#define CPR_DWC_SSI1_M_DIV_VAL_W(X) ((X) << CPR_DWC_SSI1_M_DIV_VAL_POS)
#define CPR_DWC_SSI0_M_DIV_VAL_POS  (8U)
#define CPR_DWC_SSI0_M_DIV_VAL_MSK  (0xffUL << CPR_DWC_SSI0_M_DIV_VAL_POS) /*!< dwc_ssi0_m frequency division factor*/
#define CPR_DWC_SSI0_M_DIV_VAL      CPR_DWC_SSI0_M_DIV_VAL_MSK
#define CPR_DWC_SSI0_M_DIV_VAL_W(X) ((X) << CPR_DWC_SSI0_M_DIV_VAL_POS)
#define CPR_MCLK3_CPR_DIV_VAL_POS   (16U)
#define CPR_MCLK3_CPR_DIV_VAL_MSK   (0xffUL << CPR_MCLK3_CPR_DIV_VAL_POS) /*!< mclk3_cpr_div divider factor*/
#define CPR_MCLK3_CPR_DIV_VAL       CPR_MCLK3_CPR_DIV_VAL_MSK
#define CPR_MCLK3_CPR_DIV_VAL_W(X)  ((X) << CPR_MCLK3_CPR_DIV_VAL_POS)
#define CPR_BT_SYS_CLK_DIV_VAL_POS  (24U)
#define CPR_BT_SYS_CLK_DIV_VAL_MSK  (0xffUL << CPR_BT_SYS_CLK_DIV_VAL_POS) /*!< bt_sys_clk frequency division factor*/
#define CPR_BT_SYS_CLK_DIV_VAL      CPR_BT_SYS_CLK_DIV_VAL_MSK
#define CPR_BT_SYS_CLK_DIV_VAL_W(X) ((X) << CPR_BT_SYS_CLK_DIV_VAL_POS)

//CLK_DIV_FUNC1 offsetaddress : 0x0060
//CLK_DIV_FUNC1 RegResetValue : 0x107
#define CPR_UART_DIV_POS              (0U)
#define CPR_UART_DIV_MSK              (0xffUL << CPR_UART_DIV_POS) /*!< a two-third_division&gt;0*/
#define CPR_UART_DIV                  CPR_UART_DIV_MSK
#define CPR_UART_DIV_W(X)             ((X) << CPR_UART_DIV_POS)
#define CPR_UART_MUL_POS              (8U)
#define CPR_UART_MUL_MSK              (0xffUL << CPR_UART_MUL_POS) /*!< uart mul value, uart_mul &gt;0*/
#define CPR_UART_MUL                  CPR_UART_MUL_MSK
#define CPR_UART_MUL_W(X)             ((X) << CPR_UART_MUL_POS)
#define CPR_DW_APB_SSI_S_DIV_VAL_POS  (16U)
#define CPR_DW_APB_SSI_S_DIV_VAL_MSK  (0xffUL << CPR_DW_APB_SSI_S_DIV_VAL_POS) /*!< dw_apb_ssi_s frequency division factor*/
#define CPR_DW_APB_SSI_S_DIV_VAL      CPR_DW_APB_SSI_S_DIV_VAL_MSK
#define CPR_DW_APB_SSI_S_DIV_VAL_W(X) ((X) << CPR_DW_APB_SSI_S_DIV_VAL_POS)
#define CPR_DW_APB_SSI_M_DIV_VAL_POS  (24U)
#define CPR_DW_APB_SSI_M_DIV_VAL_MSK  (0xffUL << CPR_DW_APB_SSI_M_DIV_VAL_POS) /*!< dw_apb_ssi_m frequency division factor*/
#define CPR_DW_APB_SSI_M_DIV_VAL      CPR_DW_APB_SSI_M_DIV_VAL_MSK
#define CPR_DW_APB_SSI_M_DIV_VAL_W(X) ((X) << CPR_DW_APB_SSI_M_DIV_VAL_POS)

//CLK_DIV_FUNC4 offsetaddress : 0x006c
//CLK_DIV_FUNC4 RegResetValue : 0x4
#define CPR_I2C_M_DIV_VAL_POS  (0U)
#define CPR_I2C_M_DIV_VAL_MSK  (0xffUL << CPR_I2C_M_DIV_VAL_POS) /*!< i2c_m divider factor*/
#define CPR_I2C_M_DIV_VAL      CPR_I2C_M_DIV_VAL_MSK
#define CPR_I2C_M_DIV_VAL_W(X) ((X) << CPR_I2C_M_DIV_VAL_POS)

//CLK_DIV_FUNC5 offsetaddress : 0x0070
//CLK_DIV_FUNC5 RegResetValue : 0x1
#define CPR_UTMIFS_CLK48_DIV_POS      (0U)
#define CPR_UTMIFS_CLK48_DIV_MSK      (0xffUL << CPR_UTMIFS_CLK48_DIV_POS) /*!< utmifs_clk48_div_out divide factor*/
#define CPR_UTMIFS_CLK48_DIV          CPR_UTMIFS_CLK48_DIV_MSK
#define CPR_UTMIFS_CLK48_DIV_W(X)     ((X) << CPR_UTMIFS_CLK48_DIV_POS)
#define CPR_UTMIFS_CLK48_SRC_SEL_POS  (25U)
#define CPR_UTMIFS_CLK48_SRC_SEL_MSK  (0x1UL << CPR_UTMIFS_CLK48_SRC_SEL_POS) /*!< USB FS 48M clock source selection 0: from doubler clock 48MHz (clk_dblr) 1: from mclk0 frequency division (utmifs_clk48_div_out)*/
#define CPR_UTMIFS_CLK48_SRC_SEL      CPR_UTMIFS_CLK48_SRC_SEL_MSK
#define CPR_UTMIFS_CLK48_SRC_SEL_W(X) ((X) << CPR_UTMIFS_CLK48_SRC_SEL_POS)

//CLK_DIV_FUNC6 offsetaddress : 0x0074
//CLK_DIV_FUNC6 RegResetValue : 0x50100
#define CPR_DBG_CLK_SEL_POS                 (0U)
#define CPR_DBG_CLK_SEL_MSK                 (0x3UL << CPR_DBG_CLK_SEL_POS) /*!< dbg div clock source select 0: mclk0 1: rc 32k 2: codec 6.144MHz clock 3: usb pll 120m*/
#define CPR_DBG_CLK_SEL                     CPR_DBG_CLK_SEL_MSK
#define CPR_DBG_CLK_SEL_W(X)                ((X) << CPR_DBG_CLK_SEL_POS)
#define CPR_DBG_CLK_EN_POS                  (2U)
#define CPR_DBG_CLK_EN_MSK                  (0x1UL << CPR_DBG_CLK_EN_POS) /*!< dbg clock div enable*/
#define CPR_DBG_CLK_EN                      CPR_DBG_CLK_EN_MSK
#define CPR_DBG_CLK_EN_W(X)                 ((X) << CPR_DBG_CLK_EN_POS)
#define CPR_ANC_CLK_DIV_POS                 (8U)
#define CPR_ANC_CLK_DIV_MSK                 (0xffUL << CPR_ANC_CLK_DIV_POS) /*!< CLK_MUX[15:14] is 2, anc_clk48m divider factor CLK_MUX[15:14] is 3, anc_clk96m divider factor*/
#define CPR_ANC_CLK_DIV                     CPR_ANC_CLK_DIV_MSK
#define CPR_ANC_CLK_DIV_W(X)                ((X) << CPR_ANC_CLK_DIV_POS)
#define CPR_DBG_DIV_POS                     (16U)
#define CPR_DBG_DIV_MSK                     (0xffUL << CPR_DBG_DIV_POS) /*!< dbg_div_clk divider factor*/
#define CPR_DBG_DIV                         CPR_DBG_DIV_MSK
#define CPR_DBG_DIV_W(X)                    ((X) << CPR_DBG_DIV_POS)
#define CPR_DBLR_DIV_SEL_POS                (25U)
#define CPR_DBLR_DIV_SEL_MSK                (0x1UL << CPR_DBLR_DIV_SEL_POS) /*!< Doubler clock 1.5 frequency division output duty cycle selection 0: 2/3 1: 1/3*/
#define CPR_DBLR_DIV_SEL                    CPR_DBLR_DIV_SEL_MSK
#define CPR_DBLR_DIV_SEL_W(X)               ((X) << CPR_DBLR_DIV_SEL_POS)
#define CPR_SYSTIMER_DIV_SEL_POS            (26U)
#define CPR_SYSTIMER_DIV_SEL_MSK            (0x1UL << CPR_SYSTIMER_DIV_SEL_POS) /*!< systimer clock 1.5 frequency division output duty cycle selection 0: 2/3 1: 1/3*/
#define CPR_SYSTIMER_DIV_SEL                CPR_SYSTIMER_DIV_SEL_MSK
#define CPR_SYSTIMER_DIV_SEL_W(X)           ((X) << CPR_SYSTIMER_DIV_SEL_POS)
#define CPR_USB_PHY_PLL_120M_CLKDIV_EN_POS  (27U)
#define CPR_USB_PHY_PLL_120M_CLKDIV_EN_MSK  (0x1UL << CPR_USB_PHY_PLL_120M_CLKDIV_EN_POS) /*!< usb_phy_pll_120m clock divider enable 0: disable 1: enable*/
#define CPR_USB_PHY_PLL_120M_CLKDIV_EN      CPR_USB_PHY_PLL_120M_CLKDIV_EN_MSK
#define CPR_USB_PHY_PLL_120M_CLKDIV_EN_W(X) ((X) << CPR_USB_PHY_PLL_120M_CLKDIV_EN_POS)

//CLK_DIV_AUDIO0 offsetaddress : 0x0078
//CLK_DIV_AUDIO0 RegResetValue : 0x50007c
#define CPR_I2S0_MCLK_DIV_VAL_POS      (0U)
#define CPR_I2S0_MCLK_DIV_VAL_MSK      (0xfffffUL << CPR_I2S0_MCLK_DIV_VAL_POS) /*!< i2s0_mclk divider factor*/
#define CPR_I2S0_MCLK_DIV_VAL          CPR_I2S0_MCLK_DIV_VAL_MSK
#define CPR_I2S0_MCLK_DIV_VAL_W(X)     ((X) << CPR_I2S0_MCLK_DIV_VAL_POS)
#define CPR_RESAMPLE_MCLK_DIV_VAL_POS  (20U)
#define CPR_RESAMPLE_MCLK_DIV_VAL_MSK  (0x1ffUL << CPR_RESAMPLE_MCLK_DIV_VAL_POS) /*!< resample_mclk frequency division factor*/
#define CPR_RESAMPLE_MCLK_DIV_VAL      CPR_RESAMPLE_MCLK_DIV_VAL_MSK
#define CPR_RESAMPLE_MCLK_DIV_VAL_W(X) ((X) << CPR_RESAMPLE_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO1 offsetaddress : 0x007c
//CLK_DIV_AUDIO1 RegResetValue : 0x50007c
#define CPR_I2S1_MCLK_DIV_VAL_POS   (0U)
#define CPR_I2S1_MCLK_DIV_VAL_MSK   (0xfffffUL << CPR_I2S1_MCLK_DIV_VAL_POS) /*!< i2s1_mclk divider factor*/
#define CPR_I2S1_MCLK_DIV_VAL       CPR_I2S1_MCLK_DIV_VAL_MSK
#define CPR_I2S1_MCLK_DIV_VAL_W(X)  ((X) << CPR_I2S1_MCLK_DIV_VAL_POS)
#define CPR_SPDIF_MCLK_DIV_VAL_POS  (20U)
#define CPR_SPDIF_MCLK_DIV_VAL_MSK  (0x1ffUL << CPR_SPDIF_MCLK_DIV_VAL_POS) /*!< spdif_mclk frequency division factor*/
#define CPR_SPDIF_MCLK_DIV_VAL      CPR_SPDIF_MCLK_DIV_VAL_MSK
#define CPR_SPDIF_MCLK_DIV_VAL_W(X) ((X) << CPR_SPDIF_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO2 offsetaddress : 0x0080
//CLK_DIV_AUDIO2 RegResetValue : 0x7c0007c
#define CPR_I2S2_MCLK_DIV_VAL_POS      (0U)
#define CPR_I2S2_MCLK_DIV_VAL_MSK      (0xfffffUL << CPR_I2S2_MCLK_DIV_VAL_POS) /*!< i2s2_mclk divider factor*/
#define CPR_I2S2_MCLK_DIV_VAL          CPR_I2S2_MCLK_DIV_VAL_MSK
#define CPR_I2S2_MCLK_DIV_VAL_W(X)     ((X) << CPR_I2S2_MCLK_DIV_VAL_POS)
#define CPR_CODEC_ADC_CLK_DIV_VAL_POS  (20U)
#define CPR_CODEC_ADC_CLK_DIV_VAL_MSK  (0x3ffUL << CPR_CODEC_ADC_CLK_DIV_VAL_POS) /*!< codec_adc_clk divider factor*/
#define CPR_CODEC_ADC_CLK_DIV_VAL      CPR_CODEC_ADC_CLK_DIV_VAL_MSK
#define CPR_CODEC_ADC_CLK_DIV_VAL_W(X) ((X) << CPR_CODEC_ADC_CLK_DIV_VAL_POS)

//CLK_DIV_AUDIO3 offsetaddress : 0x0084
//CLK_DIV_AUDIO3 RegResetValue : 0x7c
#define CPR_I2S3_MCLK_DIV_VAL_POS  (0U)
#define CPR_I2S3_MCLK_DIV_VAL_MSK  (0xfffffUL << CPR_I2S3_MCLK_DIV_VAL_POS) /*!< i2s3_mclk divider factor*/
#define CPR_I2S3_MCLK_DIV_VAL      CPR_I2S3_MCLK_DIV_VAL_MSK
#define CPR_I2S3_MCLK_DIV_VAL_W(X) ((X) << CPR_I2S3_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO4 offsetaddress : 0x0088
//CLK_DIV_AUDIO4 RegResetValue : 0x7c
#define CPR_PDM0_MCLK_DIV_VAL_POS  (0U)
#define CPR_PDM0_MCLK_DIV_VAL_MSK  (0xfffffUL << CPR_PDM0_MCLK_DIV_VAL_POS) /*!< pdm0_mclk divider factor*/
#define CPR_PDM0_MCLK_DIV_VAL      CPR_PDM0_MCLK_DIV_VAL_MSK
#define CPR_PDM0_MCLK_DIV_VAL_W(X) ((X) << CPR_PDM0_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO5 offsetaddress : 0x008c
//CLK_DIV_AUDIO5 RegResetValue : 0x7c
#define CPR_PDM1_MCLK_DIV_VAL_POS  (0U)
#define CPR_PDM1_MCLK_DIV_VAL_MSK  (0xfffffUL << CPR_PDM1_MCLK_DIV_VAL_POS) /*!< pdm1_mclk divider factor*/
#define CPR_PDM1_MCLK_DIV_VAL      CPR_PDM1_MCLK_DIV_VAL_MSK
#define CPR_PDM1_MCLK_DIV_VAL_W(X) ((X) << CPR_PDM1_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO6 offsetaddress : 0x0090
//CLK_DIV_AUDIO6 RegResetValue : 0x7c
#define CPR_PDMC_MCLK_DIV_VAL_POS  (0U)
#define CPR_PDMC_MCLK_DIV_VAL_MSK  (0xfffffUL << CPR_PDMC_MCLK_DIV_VAL_POS) /*!< pdmc_mclk divider factor*/
#define CPR_PDMC_MCLK_DIV_VAL      CPR_PDMC_MCLK_DIV_VAL_MSK
#define CPR_PDMC_MCLK_DIV_VAL_W(X) ((X) << CPR_PDMC_MCLK_DIV_VAL_POS)

//CLK_DIV_AUDIO7 offsetaddress : 0x0094
//CLK_DIV_AUDIO7 RegResetValue : 0x7c
#define CPR_CLKOUT0_DIV_VAL_POS  (0U)
#define CPR_CLKOUT0_DIV_VAL_MSK  (0xfffffUL << CPR_CLKOUT0_DIV_VAL_POS) /*!< clkout0 frequency division factor*/
#define CPR_CLKOUT0_DIV_VAL      CPR_CLKOUT0_DIV_VAL_MSK
#define CPR_CLKOUT0_DIV_VAL_W(X) ((X) << CPR_CLKOUT0_DIV_VAL_POS)

//CLK_DIV_AUDIO8 offsetaddress : 0x0098
//CLK_DIV_AUDIO8 RegResetValue : 0x7c00007c
#define CPR_CLKOUT1_DIV_VAL_POS          (0U)
#define CPR_CLKOUT1_DIV_VAL_MSK          (0xfffffUL << CPR_CLKOUT1_DIV_VAL_POS) /*!< clkout1 frequency division factor*/
#define CPR_CLKOUT1_DIV_VAL              CPR_CLKOUT1_DIV_VAL_MSK
#define CPR_CLKOUT1_DIV_VAL_W(X)         ((X) << CPR_CLKOUT1_DIV_VAL_POS)
#define CPR_CODEC_6P144_CLK_SEL_POS      (21U)
#define CPR_CODEC_6P144_CLK_SEL_MSK      (0x1UL << CPR_CODEC_6P144_CLK_SEL_POS) /*!< code_6p144_clk selection signal 0 – mclk1 divide-out output 1 – PLL0 low frequency clock*/
#define CPR_CODEC_6P144_CLK_SEL          CPR_CODEC_6P144_CLK_SEL_MSK
#define CPR_CODEC_6P144_CLK_SEL_W(X)     ((X) << CPR_CODEC_6P144_CLK_SEL_POS)
#define CPR_CODEC_6P144_CLK_DIV_VAL_POS  (24U)
#define CPR_CODEC_6P144_CLK_DIV_VAL_MSK  (0xffUL << CPR_CODEC_6P144_CLK_DIV_VAL_POS) /*!< code_6p144_clk frequency division factor*/
#define CPR_CODEC_6P144_CLK_DIV_VAL      CPR_CODEC_6P144_CLK_DIV_VAL_MSK
#define CPR_CODEC_6P144_CLK_DIV_VAL_W(X) ((X) << CPR_CODEC_6P144_CLK_DIV_VAL_POS)

//CLK_DIV_AUDIO9 offsetaddress : 0x009c
//CLK_DIV_AUDIO9 RegResetValue : 0x41000001
#define CPR_CODEC_DAC_CLK_DIV_VAL_POS   (0U)
#define CPR_CODEC_DAC_CLK_DIV_VAL_MSK   (0x3ffUL << CPR_CODEC_DAC_CLK_DIV_VAL_POS) /*!< codec_dac_clk frequency division factor (if there is no special requirement, frequency division remains 1)*/
#define CPR_CODEC_DAC_CLK_DIV_VAL       CPR_CODEC_DAC_CLK_DIV_VAL_MSK
#define CPR_CODEC_DAC_CLK_DIV_VAL_W(X)  ((X) << CPR_CODEC_DAC_CLK_DIV_VAL_POS)
#define CPR_PDM1_CLK_MUX_DMIC_POS       (20U)
#define CPR_PDM1_CLK_MUX_DMIC_MSK       (0x1UL << CPR_PDM1_CLK_MUX_DMIC_POS) /*!< pinmux PA16. if pdm1_clk_mux_dmic is "1" dmic1_clk connect to PA16  else pdm1_clk*/
#define CPR_PDM1_CLK_MUX_DMIC           CPR_PDM1_CLK_MUX_DMIC_MSK
#define CPR_PDM1_CLK_MUX_DMIC_W(X)      ((X) << CPR_PDM1_CLK_MUX_DMIC_POS)
#define CPR_CODEC_DMIC_CLK_DIV_VAL_POS  (24U)
#define CPR_CODEC_DMIC_CLK_DIV_VAL_MSK  (0x3UL << CPR_CODEC_DMIC_CLK_DIV_VAL_POS) /*!< code_dmic_clk divider factor*/
#define CPR_CODEC_DMIC_CLK_DIV_VAL      CPR_CODEC_DMIC_CLK_DIV_VAL_MSK
#define CPR_CODEC_DMIC_CLK_DIV_VAL_W(X) ((X) << CPR_CODEC_DMIC_CLK_DIV_VAL_POS)
#define CPR_CODEC_DMIC_CLK_EN_POS       (26U)
#define CPR_CODEC_DMIC_CLK_EN_MSK       (0x1UL << CPR_CODEC_DMIC_CLK_EN_POS) /*!< code_dmic_clk clock enable*/
#define CPR_CODEC_DMIC_CLK_EN           CPR_CODEC_DMIC_CLK_EN_MSK
#define CPR_CODEC_DMIC_CLK_EN_W(X)      ((X) << CPR_CODEC_DMIC_CLK_EN_POS)
#define CPR_CODEC_DAC_CLK_SEL_POS       (27U)
#define CPR_CODEC_DAC_CLK_SEL_MSK       (0x1UL << CPR_CODEC_DAC_CLK_SEL_POS) /*!< codec_dac_clk selection 0 – mclk1 divide-out output 1 – PLL0 low frequency clock*/
#define CPR_CODEC_DAC_CLK_SEL           CPR_CODEC_DAC_CLK_SEL_MSK
#define CPR_CODEC_DAC_CLK_SEL_W(X)      ((X) << CPR_CODEC_DAC_CLK_SEL_POS)
#define CPR_CODEC_ADC_CLK_SEL_POS       (29U)
#define CPR_CODEC_ADC_CLK_SEL_MSK       (0x1UL << CPR_CODEC_ADC_CLK_SEL_POS) /*!< codec_adc_clk selection 0 – mclk1 divide-out output 1 – PLL0 low frequency clock*/
#define CPR_CODEC_ADC_CLK_SEL           CPR_CODEC_ADC_CLK_SEL_MSK
#define CPR_CODEC_ADC_CLK_SEL_W(X)      ((X) << CPR_CODEC_ADC_CLK_SEL_POS)
#define CPR_CODEC_DAC_CLK_INV_EN_POS    (30U)
#define CPR_CODEC_DAC_CLK_INV_EN_MSK    (0x1UL << CPR_CODEC_DAC_CLK_INV_EN_POS) /*!< Codec_dac_clk reverse enable 0 – No reverse 1 – Negative*/
#define CPR_CODEC_DAC_CLK_INV_EN        CPR_CODEC_DAC_CLK_INV_EN_MSK
#define CPR_CODEC_DAC_CLK_INV_EN_W(X)   ((X) << CPR_CODEC_DAC_CLK_INV_EN_POS)
#define CPR_CODEC_DMIC_CLK_POS          (31U)
#define CPR_CODEC_DMIC_CLK_MSK          (0x1UL << CPR_CODEC_DMIC_CLK_POS) /*!< code_dmic1_clk clock enable*/
#define CPR_CODEC_DMIC_CLK              CPR_CODEC_DMIC_CLK_MSK
#define CPR_CODEC_DMIC_CLK_W(X)         ((X) << CPR_CODEC_DMIC_CLK_POS)

//CLK_DIV_APB offsetaddress : 0x00a0
//CLK_DIV_APB RegResetValue : 0x07010101
#define CPR_APB0_DIV_VAL_POS  (0U)
#define CPR_APB0_DIV_VAL_MSK  (0xffUL << CPR_APB0_DIV_VAL_POS) /*!< main_apb frequency division factor*/
#define CPR_APB0_DIV_VAL      CPR_APB0_DIV_VAL_MSK
#define CPR_APB0_DIV_VAL_W(X) ((X) << CPR_APB0_DIV_VAL_POS)
#define CPR_APB1_DIV_VAL_POS  (8U)
#define CPR_APB1_DIV_VAL_MSK  (0xffUL << CPR_APB1_DIV_VAL_POS) /*!< CPU2_apb frequency division factor*/
#define CPR_APB1_DIV_VAL      CPR_APB1_DIV_VAL_MSK
#define CPR_APB1_DIV_VAL_W(X) ((X) << CPR_APB1_DIV_VAL_POS)
#define CPR_APB2_DIV_VAL_POS  (16U)
#define CPR_APB2_DIV_VAL_MSK  (0xffUL << CPR_APB2_DIV_VAL_POS) /*!< audio_apb frequency division factor*/
#define CPR_APB2_DIV_VAL      CPR_APB2_DIV_VAL_MSK
#define CPR_APB2_DIV_VAL_W(X) ((X) << CPR_APB2_DIV_VAL_POS)
#define CPR_APB3_DIV_VAL_POS  (24U)
#define CPR_APB3_DIV_VAL_MSK  (0xffUL << CPR_APB3_DIV_VAL_POS) /*!< aon_apb frequency division factor*/
#define CPR_APB3_DIV_VAL      CPR_APB3_DIV_VAL_MSK
#define CPR_APB3_DIV_VAL_W(X) ((X) << CPR_APB3_DIV_VAL_POS)

//CLK_DIV_PLL offsetaddress : 0x00a4
//CLK_DIV_PLL RegResetValue : 0x7070000
#define CPR_PLL_AUDIO_DIV_VAL_POS  (16U)
#define CPR_PLL_AUDIO_DIV_VAL_MSK  (0xffUL << CPR_PLL_AUDIO_DIV_VAL_POS) /*!< PLL output to mclk1 frequency division factor*/
#define CPR_PLL_AUDIO_DIV_VAL      CPR_PLL_AUDIO_DIV_VAL_MSK
#define CPR_PLL_AUDIO_DIV_VAL_W(X) ((X) << CPR_PLL_AUDIO_DIV_VAL_POS)
#define CPR_PLL_SYS_DIV_VAL_POS    (24U)
#define CPR_PLL_SYS_DIV_VAL_MSK    (0xffUL << CPR_PLL_SYS_DIV_VAL_POS) /*!< PLL output to mclk0 frequency division factor*/
#define CPR_PLL_SYS_DIV_VAL        CPR_PLL_SYS_DIV_VAL_MSK
#define CPR_PLL_SYS_DIV_VAL_W(X)   ((X) << CPR_PLL_SYS_DIV_VAL_POS)

//CLK_SET offsetaddress : 0x00a8
//CLK_SET RegResetValue : 0x1
#define CPR_MCLK0_SEL_POS       (0U)
#define CPR_MCLK0_SEL_MSK       (0x3UL << CPR_MCLK0_SEL_POS) /*!< mclk0 selection 0: divided pll clock 1: clk_hfrco (48MHz) 2: clk_hfxo (24MHz) 3: doubler clock (original 48MHz or divided to 32MHz)*/
#define CPR_MCLK0_SEL           CPR_MCLK0_SEL_MSK
#define CPR_MCLK0_SEL_W(X)      ((X) << CPR_MCLK0_SEL_POS)
#define CPR_MCLK0_DBLR_SEL_POS  (2U)
#define CPR_MCLK0_DBLR_SEL_MSK  (0x1UL << CPR_MCLK0_DBLR_SEL_POS) /*!< mclk0 doubler input selection 0: 48MHz (clk_dblr) 1: 32MHz (from clk_dblr)*/
#define CPR_MCLK0_DBLR_SEL      CPR_MCLK0_DBLR_SEL_MSK
#define CPR_MCLK0_DBLR_SEL_W(X) ((X) << CPR_MCLK0_DBLR_SEL_POS)
#define CPR_MCLK0_PLL_SEL_POS   (3U)
#define CPR_MCLK0_PLL_SEL_MSK   (0x1UL << CPR_MCLK0_PLL_SEL_POS) /*!< mclk0 pll input selection 0: pll0 (bbpll) 1: pll1 (frac pll)*/
#define CPR_MCLK0_PLL_SEL       CPR_MCLK0_PLL_SEL_MSK
#define CPR_MCLK0_PLL_SEL_W(X)  ((X) << CPR_MCLK0_PLL_SEL_POS)

//RST_CTRL offsetaddress : 0x00ac
//RST_CTRL RegResetValue : 0x0
#define CPR_RESET_SRC_POS  (0U)
#define CPR_RESET_SRC_MSK  (0x7UL << CPR_RESET_SRC_POS) /*!< 0: bor reset 1: rpd reset 2: CPU0 wdt reset 3: CPU1 wdt reset 4: CPU2 wdt reset 5: soft reset*/
#define CPR_RESET_SRC      CPR_RESET_SRC_MSK
#define CPR_RESET_SRC_W(X) ((X) << CPR_RESET_SRC_POS)
#define CPR_RSTN_SOFT_POS  (3U)
#define CPR_RSTN_SOFT_MSK  (0x1UL << CPR_RSTN_SOFT_POS) /*!< Soft reset, write 1 reset, automatic clear reset*/
#define CPR_RSTN_SOFT      CPR_RSTN_SOFT_MSK
#define CPR_RSTN_SOFT_W(X) ((X) << CPR_RSTN_SOFT_POS)

//ROM_CFG offsetaddress : 0x00b0
//ROM_CFG RegResetValue : 0x8016
#define CPR_ROM_CFG_POS         (0U)
#define CPR_ROM_CFG_MSK         (0x3fUL << CPR_ROM_CFG_POS) /*!< Rom low power consumption control, multi-bit control, please refer to the Rom manual for details*/
#define CPR_ROM_CFG             CPR_ROM_CFG_MSK
#define CPR_ROM_CFG_W(X)        ((X) << CPR_ROM_CFG_POS)
#define CPR_ROM_SLP_POS         (6U)
#define CPR_ROM_SLP_MSK         (0x1UL << CPR_ROM_SLP_POS) /*!< rom sleep control*/
#define CPR_ROM_SLP             CPR_ROM_SLP_MSK
#define CPR_ROM_SLP_W(X)        ((X) << CPR_ROM_SLP_POS)
#define CPR_ROM_IDLE_LIMIT_POS  (12U)
#define CPR_ROM_IDLE_LIMIT_MSK  (0xfUL << CPR_ROM_IDLE_LIMIT_POS) /*!< rom low power consumption control, after idle_limit clk cycle,go into low power mode.*/
#define CPR_ROM_IDLE_LIMIT      CPR_ROM_IDLE_LIMIT_MSK
#define CPR_ROM_IDLE_LIMIT_W(X) ((X) << CPR_ROM_IDLE_LIMIT_POS)
#define CPR_ROM_AHB_LP_POS      (16U)
#define CPR_ROM_AHB_LP_MSK      (0x1UL << CPR_ROM_AHB_LP_POS) /*!< rom low power control, low power consumption enable: 1: enable low power consumption 0: not enable low power consumption*/
#define CPR_ROM_AHB_LP          CPR_ROM_AHB_LP_MSK
#define CPR_ROM_AHB_LP_W(X)     ((X) << CPR_ROM_AHB_LP_POS)

//SHRAM_CFG offsetaddress : 0x00b4
//SHRAM_CFG RegResetValue : 0x55812108
#define CPR_CPU1_ILM_IDLE_LIMIT_POS  (0U)
#define CPR_CPU1_ILM_IDLE_LIMIT_MSK  (0xfUL << CPR_CPU1_ILM_IDLE_LIMIT_POS) /*!< CPU1 ilm low power consumption control, after idle_limit clk cycle,go into low power mode.*/
#define CPR_CPU1_ILM_IDLE_LIMIT      CPR_CPU1_ILM_IDLE_LIMIT_MSK
#define CPR_CPU1_ILM_IDLE_LIMIT_W(X) ((X) << CPR_CPU1_ILM_IDLE_LIMIT_POS)
#define CPR_CPU1_ILM_LP_EN_POS       (4U)
#define CPR_CPU1_ILM_LP_EN_MSK       (0x1UL << CPR_CPU1_ILM_LP_EN_POS) /*!< CPU1 ilm low power control, low power consumption enable: 1: enable low power consumption 0: not enable low power consumption*/
#define CPR_CPU1_ILM_LP_EN           CPR_CPU1_ILM_LP_EN_MSK
#define CPR_CPU1_ILM_LP_EN_W(X)      ((X) << CPR_CPU1_ILM_LP_EN_POS)
#define CPR_CPU1_DLM_IDLE_LIMIT_POS  (5U)
#define CPR_CPU1_DLM_IDLE_LIMIT_MSK  (0xfUL << CPR_CPU1_DLM_IDLE_LIMIT_POS) /*!< CPU1 dlm low power consumption control, after idle_limit clk cycle,go into low power mode.*/
#define CPR_CPU1_DLM_IDLE_LIMIT      CPR_CPU1_DLM_IDLE_LIMIT_MSK
#define CPR_CPU1_DLM_IDLE_LIMIT_W(X) ((X) << CPR_CPU1_DLM_IDLE_LIMIT_POS)
#define CPR_CPU1_DLM_LP_EN_POS       (9U)
#define CPR_CPU1_DLM_LP_EN_MSK       (0x1UL << CPR_CPU1_DLM_LP_EN_POS) /*!< CPU1 dlm low power consumption control, low power consumption enable: 1: enable low power consumption 0: not enable low power consumption*/
#define CPR_CPU1_DLM_LP_EN           CPR_CPU1_DLM_LP_EN_MSK
#define CPR_CPU1_DLM_LP_EN_W(X)      ((X) << CPR_CPU1_DLM_LP_EN_POS)
#define CPR_SHRAM1_IDLE_LIMIT_POS    (10U)
#define CPR_SHRAM1_IDLE_LIMIT_MSK    (0xfUL << CPR_SHRAM1_IDLE_LIMIT_POS) /*!< Shram1 low power consumption control, after idle_limit clk cycle,go into low power mode.*/
#define CPR_SHRAM1_IDLE_LIMIT        CPR_SHRAM1_IDLE_LIMIT_MSK
#define CPR_SHRAM1_IDLE_LIMIT_W(X)   ((X) << CPR_SHRAM1_IDLE_LIMIT_POS)
#define CPR_SHRAM1_LP_EN_POS         (14U)
#define CPR_SHRAM1_LP_EN_MSK         (0x1UL << CPR_SHRAM1_LP_EN_POS) /*!< Shram1 low power consumption control, low power consumption enable: 1: enable low power consumption 0: not enable low power consumption*/
#define CPR_SHRAM1_LP_EN             CPR_SHRAM1_LP_EN_MSK
#define CPR_SHRAM1_LP_EN_W(X)        ((X) << CPR_SHRAM1_LP_EN_POS)
#define CPR_T_RAM_CEN_SET_POS        (16U)
#define CPR_T_RAM_CEN_SET_MSK        (0x1fUL << CPR_T_RAM_CEN_SET_POS) /*!< */
#define CPR_T_RAM_CEN_SET            CPR_T_RAM_CEN_SET_MSK
#define CPR_T_RAM_CEN_SET_W(X)       ((X) << CPR_T_RAM_CEN_SET_POS)
#define CPR_T_RAM_RETN_SET_POS       (21U)
#define CPR_T_RAM_RETN_SET_MSK       (0x1fUL << CPR_T_RAM_RETN_SET_POS) /*!< */
#define CPR_T_RAM_RETN_SET           CPR_T_RAM_RETN_SET_MSK
#define CPR_T_RAM_RETN_SET_W(X)      ((X) << CPR_T_RAM_RETN_SET_POS)
#define CPR_T_RAM_PGEN_SET_POS       (26U)
#define CPR_T_RAM_PGEN_SET_MSK       (0x1fUL << CPR_T_RAM_PGEN_SET_POS) /*!< */
#define CPR_T_RAM_PGEN_SET           CPR_T_RAM_PGEN_SET_MSK
#define CPR_T_RAM_PGEN_SET_W(X)      ((X) << CPR_T_RAM_PGEN_SET_POS)

//RAM_CFG offsetaddress : 0x00b8
//RAM_CFG RegResetValue : 0xc480828
#define CPR_RFSP_RAWLM_POS  (0U)
#define CPR_RFSP_RAWLM_MSK  (0x3UL << CPR_RFSP_RAWLM_POS) /*!< */
#define CPR_RFSP_RAWLM      CPR_RFSP_RAWLM_MSK
#define CPR_RFSP_RAWLM_W(X) ((X) << CPR_RFSP_RAWLM_POS)
#define CPR_RFSP_RAWL_POS   (2U)
#define CPR_RFSP_RAWL_MSK   (0x1UL << CPR_RFSP_RAWL_POS) /*!< */
#define CPR_RFSP_RAWL       CPR_RFSP_RAWL_MSK
#define CPR_RFSP_RAWL_W(X)  ((X) << CPR_RFSP_RAWL_POS)
#define CPR_RFSP_WABLM_POS  (3U)
#define CPR_RFSP_WABLM_MSK  (0x3UL << CPR_RFSP_WABLM_POS) /*!< */
#define CPR_RFSP_WABLM      CPR_RFSP_WABLM_MSK
#define CPR_RFSP_WABLM_W(X) ((X) << CPR_RFSP_WABLM_POS)
#define CPR_RFSP_WABL_POS   (5U)
#define CPR_RFSP_WABL_MSK   (0x1UL << CPR_RFSP_WABL_POS) /*!< */
#define CPR_RFSP_WABL       CPR_RFSP_WABL_MSK
#define CPR_RFSP_WABL_W(X)  ((X) << CPR_RFSP_WABL_POS)
#define CPR_RFSP_EMAS_POS   (6U)
#define CPR_RFSP_EMAS_MSK   (0x1UL << CPR_RFSP_EMAS_POS) /*!< */
#define CPR_RFSP_EMAS       CPR_RFSP_EMAS_MSK
#define CPR_RFSP_EMAS_W(X)  ((X) << CPR_RFSP_EMAS_POS)
#define CPR_RFSP_EMAW_POS   (7U)
#define CPR_RFSP_EMAW_MSK   (0x3UL << CPR_RFSP_EMAW_POS) /*!< */
#define CPR_RFSP_EMAW       CPR_RFSP_EMAW_MSK
#define CPR_RFSP_EMAW_W(X)  ((X) << CPR_RFSP_EMAW_POS)
#define CPR_RFSP_EMA_POS    (9U)
#define CPR_RFSP_EMA_MSK    (0x7UL << CPR_RFSP_EMA_POS) /*!< */
#define CPR_RFSP_EMA        CPR_RFSP_EMA_MSK
#define CPR_RFSP_EMA_W(X)   ((X) << CPR_RFSP_EMA_POS)
#define CPR_RESV_POS        (12U)
#define CPR_RESV_MSK        (0xfUL << CPR_RESV_POS) /*!< */
#define CPR_RESV            CPR_RESV_MSK
#define CPR_RESV_W(X)       ((X) << CPR_RESV_POS)
#define CPR_SRSP_RAWLM_POS  (16U)
#define CPR_SRSP_RAWLM_MSK  (0x3UL << CPR_SRSP_RAWLM_POS) /*!< */
#define CPR_SRSP_RAWLM      CPR_SRSP_RAWLM_MSK
#define CPR_SRSP_RAWLM_W(X) ((X) << CPR_SRSP_RAWLM_POS)
#define CPR_SRSP_RAWL_POS   (18U)
#define CPR_SRSP_RAWL_MSK   (0x1UL << CPR_SRSP_RAWL_POS) /*!< */
#define CPR_SRSP_RAWL       CPR_SRSP_RAWL_MSK
#define CPR_SRSP_RAWL_W(X)  ((X) << CPR_SRSP_RAWL_POS)
#define CPR_SRSP_WABLM_POS  (19U)
#define CPR_SRSP_WABLM_MSK  (0x7UL << CPR_SRSP_WABLM_POS) /*!< */
#define CPR_SRSP_WABLM      CPR_SRSP_WABLM_MSK
#define CPR_SRSP_WABLM_W(X) ((X) << CPR_SRSP_WABLM_POS)
#define CPR_SRSP_WABL_POS   (22U)
#define CPR_SRSP_WABL_MSK   (0x1UL << CPR_SRSP_WABL_POS) /*!< */
#define CPR_SRSP_WABL       CPR_SRSP_WABL_MSK
#define CPR_SRSP_WABL_W(X)  ((X) << CPR_SRSP_WABL_POS)
#define CPR_SRSP_EMAS_POS   (23U)
#define CPR_SRSP_EMAS_MSK   (0x1UL << CPR_SRSP_EMAS_POS) /*!< */
#define CPR_SRSP_EMAS       CPR_SRSP_EMAS_MSK
#define CPR_SRSP_EMAS_W(X)  ((X) << CPR_SRSP_EMAS_POS)
#define CPR_SRSP_EMAW_POS   (24U)
#define CPR_SRSP_EMAW_MSK   (0x3UL << CPR_SRSP_EMAW_POS) /*!< */
#define CPR_SRSP_EMAW       CPR_SRSP_EMAW_MSK
#define CPR_SRSP_EMAW_W(X)  ((X) << CPR_SRSP_EMAW_POS)
#define CPR_SRSP_EMA_POS    (26U)
#define CPR_SRSP_EMA_MSK    (0x7UL << CPR_SRSP_EMA_POS) /*!< */
#define CPR_SRSP_EMA        CPR_SRSP_EMA_MSK
#define CPR_SRSP_EMA_W(X)   ((X) << CPR_SRSP_EMA_POS)

//CPU1_SLP_KICK offsetaddress : 0x00c0
//CPU1_SLP_KICK RegResetValue : 0xe
#define CPR_SLEEP_KICK_POS             (0U)
#define CPR_SLEEP_KICK_MSK             (0x1UL << CPR_SLEEP_KICK_POS) /*!< rf system sleep kick*/
#define CPR_SLEEP_KICK                 CPR_SLEEP_KICK_MSK
#define CPR_CPU1_WAIT_NEG32K_ACK_POS   (1U)
#define CPR_CPU1_WAIT_NEG32K_ACK_MSK   (0x1UL << CPR_CPU1_WAIT_NEG32K_ACK_POS) /*!< clk32k negative edge acknowledge enable for CPU1 triggered sleep 0: disable 1: wait for 32k clock negedge before entering sleep*/
#define CPR_CPU1_WAIT_NEG32K_ACK       CPR_CPU1_WAIT_NEG32K_ACK_MSK
#define CPR_CPU1_WAIT_CPU1_WFI_ACK_POS (2U)
#define CPR_CPU1_WAIT_CPU1_WFI_ACK_MSK (0x1UL << CPR_CPU1_WAIT_CPU1_WFI_ACK_POS) /*!< CPU1 wfi acknowledge enable for CPU1 triggered sleep 0: disable 1: wait for CPU1 wfi ack before entering sleep*/
#define CPR_CPU1_WAIT_CPU1_WFI_ACK     CPR_CPU1_WAIT_CPU1_WFI_ACK_MSK
#define CPR_CPU1_WAIT_CPU0_WFI_ACK_POS (3U)
#define CPR_CPU1_WAIT_CPU0_WFI_ACK_MSK (0x1UL << CPR_CPU1_WAIT_CPU0_WFI_ACK_POS) /*!< CPU0 wfi acknowledge enable for CPU1 triggered sleep 0: disable 1: wait for CPU0 wfi ack before entering sleep*/
#define CPR_CPU1_WAIT_CPU0_WFI_ACK     CPR_CPU1_WAIT_CPU0_WFI_ACK_MSK

//CPU0_SLP_KICK offsetaddress : 0x00c4
//CPU0_SLP_KICK RegResetValue : 0x6
#define CPR_CPU0_SLEEP_KICK_POS        (0U)
#define CPR_CPU0_SLEEP_KICK_MSK        (0x1UL << CPR_CPU0_SLEEP_KICK_POS) /*!< mcu system sleep kick*/
#define CPR_CPU0_SLEEP_KICK            CPR_CPU0_SLEEP_KICK_MSK
#define CPR_CPU0_WAIT_NEG32K_ACK_POS   (1U)
#define CPR_CPU0_WAIT_NEG32K_ACK_MSK   (0x1UL << CPR_CPU0_WAIT_NEG32K_ACK_POS) /*!< clk32k negative edge acknowledge enable for CPU0 triggered sleep 0: disable 1: wait for 32k clock negedge before entering sleep*/
#define CPR_CPU0_WAIT_NEG32K_ACK       CPR_CPU0_WAIT_NEG32K_ACK_MSK
#define CPR_CPU0_WAIT_CPU0_WFI_ACK_POS (2U)
#define CPR_CPU0_WAIT_CPU0_WFI_ACK_MSK (0x1UL << CPR_CPU0_WAIT_CPU0_WFI_ACK_POS) /*!< CPU0 wfi acknowledge enable for CPU0 triggered sleep 0: disable 1: wait for CPU0 wfi ack before entering sleep*/
#define CPR_CPU0_WAIT_CPU0_WFI_ACK     CPR_CPU0_WAIT_CPU0_WFI_ACK_MSK
#define CPR_CPU0_WAIT_CPU1_WFI_ACK_POS (3U)
#define CPR_CPU0_WAIT_CPU1_WFI_ACK_MSK (0x1UL << CPR_CPU0_WAIT_CPU1_WFI_ACK_POS) /*!< CPU1 wfi acknowledge enable for CPU0 triggered sleep 0: disable 1: wait for CPU1 wfi ack before entering sleep*/
#define CPR_CPU0_WAIT_CPU1_WFI_ACK     CPR_CPU0_WAIT_CPU1_WFI_ACK_MSK

//CPU1_SLP_CTRL offsetaddress : 0x00c8
//CPU1_SLP_CTRL RegResetValue : 0x0
#define CPR_PA_GPIO_WAK_EN_POS  (0U)
#define CPR_PA_GPIO_WAK_EN_MSK  (0x1UL << CPR_PA_GPIO_WAK_EN_POS) /*!< PA I/O wake-up enable*/
#define CPR_PA_GPIO_WAK_EN      CPR_PA_GPIO_WAK_EN_MSK
#define CPR_IPCM_WAK_EN_POS     (1U)
#define CPR_IPCM_WAK_EN_MSK     (0x1UL << CPR_IPCM_WAK_EN_POS) /*!< ipcm wake-up enable*/
#define CPR_IPCM_WAK_EN         CPR_IPCM_WAK_EN_MSK
#define CPR_TIMER_WAK_EN_0_POS  (2U)
#define CPR_TIMER_WAK_EN_0_MSK  (0x1UL << CPR_TIMER_WAK_EN_0_POS) /*!< timer[0] wake up enable*/
#define CPR_TIMER_WAK_EN_0      CPR_TIMER_WAK_EN_0_MSK
#define CPR_TIMER_WAK_EN_1_POS  (3U)
#define CPR_TIMER_WAK_EN_1_MSK  (0x1UL << CPR_TIMER_WAK_EN_1_POS) /*!< timer[1] wake up enable*/
#define CPR_TIMER_WAK_EN_1      CPR_TIMER_WAK_EN_1_MSK
#define CPR_TIMER_WAK_EN_2_POS  (4U)
#define CPR_TIMER_WAK_EN_2_MSK  (0x1UL << CPR_TIMER_WAK_EN_2_POS) /*!< timer[2] wake up enable*/
#define CPR_TIMER_WAK_EN_2      CPR_TIMER_WAK_EN_2_MSK
#define CPR_TIMER_WAK_EN_3_POS  (5U)
#define CPR_TIMER_WAK_EN_3_MSK  (0x1UL << CPR_TIMER_WAK_EN_3_POS) /*!< timer[3] wake up enable*/
#define CPR_TIMER_WAK_EN_3      CPR_TIMER_WAK_EN_3_MSK
#define CPR_TIMER1_WAK_EN_0_POS (6U)
#define CPR_TIMER1_WAK_EN_0_MSK (0x1UL << CPR_TIMER1_WAK_EN_0_POS) /*!< timer1[0] wake up enable*/
#define CPR_TIMER1_WAK_EN_0     CPR_TIMER1_WAK_EN_0_MSK
#define CPR_TIMER1_WAK_EN_1_POS (7U)
#define CPR_TIMER1_WAK_EN_1_MSK (0x1UL << CPR_TIMER1_WAK_EN_1_POS) /*!< timer1[1] wake up enable*/
#define CPR_TIMER1_WAK_EN_1     CPR_TIMER1_WAK_EN_1_MSK
#define CPR_TIMER1_WAK_EN_2_POS (8U)
#define CPR_TIMER1_WAK_EN_2_MSK (0x1UL << CPR_TIMER1_WAK_EN_2_POS) /*!< timer1[2] wake-up enable*/
#define CPR_TIMER1_WAK_EN_2     CPR_TIMER1_WAK_EN_2_MSK
#define CPR_TIMER1_WAK_EN_3_POS (9U)
#define CPR_TIMER1_WAK_EN_3_MSK (0x1UL << CPR_TIMER1_WAK_EN_3_POS) /*!< timer1[3] wake-up enable*/
#define CPR_TIMER1_WAK_EN_3     CPR_TIMER1_WAK_EN_3_MSK
#define CPR_WDT_WAK_EN_POS      (10U)
#define CPR_WDT_WAK_EN_MSK      (0x1UL << CPR_WDT_WAK_EN_POS) /*!< watchdog wake-up enable*/
#define CPR_WDT_WAK_EN          CPR_WDT_WAK_EN_MSK
#define CPR_BT_WAK_EN_POS       (11U)
#define CPR_BT_WAK_EN_MSK       (0x1UL << CPR_BT_WAK_EN_POS) /*!< rw bt/ble/dm and dbm wake-up enable*/
#define CPR_BT_WAK_EN           CPR_BT_WAK_EN_MSK
#define CPR_BB_WAK_EN_POS       (12U)
#define CPR_BB_WAK_EN_MSK       (0x1UL << CPR_BB_WAK_EN_POS) /*!< 2.4g bb wake-up enable*/
#define CPR_BB_WAK_EN           CPR_BB_WAK_EN_MSK
#define CPR_TAHDT_WAK_EN_POS      (13U)
#define CPR_TAHDT_WAK_EN_MSK      (0x1UL << CPR_TAHDT_WAK_EN_POS) /*!< sle wake-up enable*/
#define CPR_TAHDT_WAK_EN          CPR_TAHDT_WAK_EN_MSK
#define CPR_SYSTIMER_WAK_EN_POS (14U)
#define CPR_SYSTIMER_WAK_EN_MSK (0x1UL << CPR_SYSTIMER_WAK_EN_POS) /*!< system timer wake-up enable*/
#define CPR_SYSTIMER_WAK_EN     CPR_SYSTIMER_WAK_EN_MSK
#define CPR_USB1_WAK_EN_POS     (15U)
#define CPR_USB1_WAK_EN_MSK     (0x1UL << CPR_USB1_WAK_EN_POS) /*!< usb1 wake-up enable*/
#define CPR_USB1_WAK_EN         CPR_USB1_WAK_EN_MSK

//CPU0_SLP_CTRL offsetaddress : 0x00cc
//CPU0_SLP_CTRL RegResetValue : 0x0
#define CPR_PDMCU_PA_GPIO_WAK_EN_POS  (0U)
#define CPR_PDMCU_PA_GPIO_WAK_EN_MSK  (0x1UL << CPR_PDMCU_PA_GPIO_WAK_EN_POS) /*!< PA I/O wake-up enable (mcu system)*/
#define CPR_PDMCU_PA_GPIO_WAK_EN      CPR_PDMCU_PA_GPIO_WAK_EN_MSK
#define CPR_PDMCU_IPCM_WAK_EN_POS     (1U)
#define CPR_PDMCU_IPCM_WAK_EN_MSK     (0x1UL << CPR_PDMCU_IPCM_WAK_EN_POS) /*!< ipcm wake-up enable (mcu system)*/
#define CPR_PDMCU_IPCM_WAK_EN         CPR_PDMCU_IPCM_WAK_EN_MSK
#define CPR_PDMCU_TIMER_WAK_EN_0_POS  (2U)
#define CPR_PDMCU_TIMER_WAK_EN_0_MSK  (0x1UL << CPR_PDMCU_TIMER_WAK_EN_0_POS) /*!< timer[0] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER_WAK_EN_0      CPR_PDMCU_TIMER_WAK_EN_0_MSK
#define CPR_PDMCU_TIMER_WAK_EN_1_POS  (3U)
#define CPR_PDMCU_TIMER_WAK_EN_1_MSK  (0x1UL << CPR_PDMCU_TIMER_WAK_EN_1_POS) /*!< timer[1] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER_WAK_EN_1      CPR_PDMCU_TIMER_WAK_EN_1_MSK
#define CPR_PDMCU_TIMER_WAK_EN_2_POS  (4U)
#define CPR_PDMCU_TIMER_WAK_EN_2_MSK  (0x1UL << CPR_PDMCU_TIMER_WAK_EN_2_POS) /*!< timer[2] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER_WAK_EN_2      CPR_PDMCU_TIMER_WAK_EN_2_MSK
#define CPR_PDMCU_TIMER_WAK_EN_3_POS  (5U)
#define CPR_PDMCU_TIMER_WAK_EN_3_MSK  (0x1UL << CPR_PDMCU_TIMER_WAK_EN_3_POS) /*!< timer[3] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER_WAK_EN_3      CPR_PDMCU_TIMER_WAK_EN_3_MSK
#define CPR_PDMCU_TIMER1_WAK_EN_0_POS (6U)
#define CPR_PDMCU_TIMER1_WAK_EN_0_MSK (0x1UL << CPR_PDMCU_TIMER1_WAK_EN_0_POS) /*!< timer1[0] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER1_WAK_EN_0     CPR_PDMCU_TIMER1_WAK_EN_0_MSK
#define CPR_PDMCU_TIMER1_WAK_EN_1_POS (7U)
#define CPR_PDMCU_TIMER1_WAK_EN_1_MSK (0x1UL << CPR_PDMCU_TIMER1_WAK_EN_1_POS) /*!< timer1[1] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER1_WAK_EN_1     CPR_PDMCU_TIMER1_WAK_EN_1_MSK
#define CPR_PDMCU_TIMER1_WAK_EN_2_POS (8U)
#define CPR_PDMCU_TIMER1_WAK_EN_2_MSK (0x1UL << CPR_PDMCU_TIMER1_WAK_EN_2_POS) /*!< timer1[2] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER1_WAK_EN_2     CPR_PDMCU_TIMER1_WAK_EN_2_MSK
#define CPR_PDMCU_TIMER1_WAK_EN_3_POS (9U)
#define CPR_PDMCU_TIMER1_WAK_EN_3_MSK (0x1UL << CPR_PDMCU_TIMER1_WAK_EN_3_POS) /*!< timer1[3] wake-up enable (mcu system)*/
#define CPR_PDMCU_TIMER1_WAK_EN_3     CPR_PDMCU_TIMER1_WAK_EN_3_MSK
#define CPR_PDMCU_WDT_WAK_EN_POS      (10U)
#define CPR_PDMCU_WDT_WAK_EN_MSK      (0x1UL << CPR_PDMCU_WDT_WAK_EN_POS) /*!< watchdog wake-up enable (mcu system)*/
#define CPR_PDMCU_WDT_WAK_EN          CPR_PDMCU_WDT_WAK_EN_MSK
#define CPR_PDMCU_BT_WAK_EN_POS       (11U)
#define CPR_PDMCU_BT_WAK_EN_MSK       (0x1UL << CPR_PDMCU_BT_WAK_EN_POS) /*!< rw bt/ble/dm and dbm wake-up enable (mcu system)*/
#define CPR_PDMCU_BT_WAK_EN           CPR_PDMCU_BT_WAK_EN_MSK
#define CPR_PDMCU_BB_WAK_EN_POS       (12U)
#define CPR_PDMCU_BB_WAK_EN_MSK       (0x1UL << CPR_PDMCU_BB_WAK_EN_POS) /*!< 2.4g bb wake-up enable (mcu system)*/
#define CPR_PDMCU_BB_WAK_EN           CPR_PDMCU_BB_WAK_EN_MSK
#define CPR_PDMCU_TAHDT_WAK_EN_POS      (13U)
#define CPR_PDMCU_TAHDT_WAK_EN_MSK      (0x1UL << CPR_PDMCU_TAHDT_WAK_EN_POS) /*!< Sle wake-up enable (mcu system)*/
#define CPR_PDMCU_TAHDT_WAK_EN          CPR_PDMCU_TAHDT_WAK_EN_MSK
#define CPR_PDMCU_SYSTIMER_WAK_EN_POS (14U)
#define CPR_PDMCU_SYSTIMER_WAK_EN_MSK (0x1UL << CPR_PDMCU_SYSTIMER_WAK_EN_POS) /*!< System timer wake-up enable (mcu system)*/
#define CPR_PDMCU_SYSTIMER_WAK_EN     CPR_PDMCU_SYSTIMER_WAK_EN_MSK
#define CPR_PDMCU_USB1_WAK_EN_POS     (15U)
#define CPR_PDMCU_USB1_WAK_EN_MSK     (0x1UL << CPR_PDMCU_USB1_WAK_EN_POS) /*!< usb1 wake-up enable (mcu system)*/
#define CPR_PDMCU_USB1_WAK_EN         CPR_PDMCU_USB1_WAK_EN_MSK

//CPU2_REMAP_VEC offsetaddress : 0x00d0
//CPU2_REMAP_VEC RegResetValue : 0x0
#define CPR_CPU2_REMAP_VEC_POS  (0U)
#define CPR_CPU2_REMAP_VEC_MSK  (0xffffffffUL << CPR_CPU2_REMAP_VEC_POS) /*!< CPU2 remap startup address, valid when CPU2_CFG[2]==1*/
#define CPR_CPU2_REMAP_VEC      CPR_CPU2_REMAP_VEC_MSK
#define CPR_CPU2_REMAP_VEC_W(X) ((X) << CPR_CPU2_REMAP_VEC_POS)

//RC_CALIB offsetaddress : 0x00dc
//RC_CALIB RegResetValue : 0x4030
#define CPR_RCCAL_EN_POS        (0U)
#define CPR_RCCAL_EN_MSK        (0x1UL << CPR_RCCAL_EN_POS) /*!< RC OSC calibration enable*/
#define CPR_RCCAL_EN            CPR_RCCAL_EN_MSK
#define CPR_RCCAL_EN_W(X)       ((X) << CPR_RCCAL_EN_POS)
#define CPR_RCCAL_LEN_POS       (1U)
#define CPR_RCCAL_LEN_MSK       (0x1UL << CPR_RCCAL_LEN_POS) /*!< RC OSC calibration length for 32K RC calibration mode: 0: 1 cycle of 32K RC 1: 2 cycle of 32K RC for 48M RC calibration mode: 0: 1000 cycle of 48M RC 1: 2000 cycle of 48M RC*/
#define CPR_RCCAL_LEN           CPR_RCCAL_LEN_MSK
#define CPR_RCCAL_LEN_W(X)      ((X) << CPR_RCCAL_LEN_POS)
#define CPR_RCCAL_MODE_POS      (2U)
#define CPR_RCCAL_MODE_MSK      (0x1UL << CPR_RCCAL_MODE_POS) /*!< RC OSC calibration mode 0: 48M RC calibration 1: 32K RC calibration*/
#define CPR_RCCAL_MODE          CPR_RCCAL_MODE_MSK
#define CPR_RCCAL_MODE_W(X)     ((X) << CPR_RCCAL_MODE_POS)
#define CPR_RCCAL_WAIT_LEN_POS  (4U)
#define CPR_RCCAL_WAIT_LEN_MSK  (0x7UL << CPR_RCCAL_WAIT_LEN_POS) /*!< RC OSC calibation wait settle length (only for 48M) rccal_wait_len * 32 / 24 (us)*/
#define CPR_RCCAL_WAIT_LEN      CPR_RCCAL_WAIT_LEN_MSK
#define CPR_RCCAL_WAIT_LEN_W(X) ((X) << CPR_RCCAL_WAIT_LEN_POS)
#define CPR_RCCAL_DONE_POS      (7U)
#define CPR_RCCAL_DONE_MSK      (0x1UL << CPR_RCCAL_DONE_POS) /*!< RC OSC calibration done indicator, cleared upon reset or when rccal_en == 0*/
#define CPR_RCCAL_DONE          CPR_RCCAL_DONE_MSK
#define CPR_RCCAL_DONE_W(X)     ((X) << CPR_RCCAL_DONE_POS)
#define CPR_RCCAL_TRIM_POS      (8U)
#define CPR_RCCAL_TRIM_MSK      (0x7fUL << CPR_RCCAL_TRIM_POS) /*!< RC OSC calibration trim result*/
#define CPR_RCCAL_TRIM          CPR_RCCAL_TRIM_MSK
#define CPR_RCCAL_TRIM_W(X)     ((X) << CPR_RCCAL_TRIM_POS)
#define CPR_RCCAL_CNT_POS       (16U)
#define CPR_RCCAL_CNT_MSK       (0x7ffUL << CPR_RCCAL_CNT_POS) /*!< RC OSC calibration count result*/
#define CPR_RCCAL_CNT           CPR_RCCAL_CNT_MSK
#define CPR_RCCAL_CNT_W(X)      ((X) << CPR_RCCAL_CNT_POS)

//BT_CFG offsetaddress : 0x00e0
//BT_CFG RegResetValue : 0x180
#define CPR_BT_SYS_CPU_BT_GCLKEN_POS   (0U)
#define CPR_BT_SYS_CPU_BT_GCLKEN_MSK   (0x1UL << CPR_BT_SYS_CPU_BT_GCLKEN_POS) /*!< bt_sys_cpu_bt_gclken*/
#define CPR_BT_SYS_CPU_BT_GCLKEN       CPR_BT_SYS_CPU_BT_GCLKEN_MSK
#define CPR_BT_SYS_CPU_BT_GCLKEN_W(X)  ((X) << CPR_BT_SYS_CPU_BT_GCLKEN_POS)
#define CPR_BT_SYS_CPU_BLE_GCLKEN_POS  (1U)
#define CPR_BT_SYS_CPU_BLE_GCLKEN_MSK  (0x1UL << CPR_BT_SYS_CPU_BLE_GCLKEN_POS) /*!< bt_sys_cpu_ble_gclken*/
#define CPR_BT_SYS_CPU_BLE_GCLKEN      CPR_BT_SYS_CPU_BLE_GCLKEN_MSK
#define CPR_BT_SYS_CPU_BLE_GCLKEN_W(X) ((X) << CPR_BT_SYS_CPU_BLE_GCLKEN_POS)
#define CPR_BT_SYS_CPU_DM_GCLKEN_POS   (2U)
#define CPR_BT_SYS_CPU_DM_GCLKEN_MSK   (0x1UL << CPR_BT_SYS_CPU_DM_GCLKEN_POS) /*!< bt_sys_cpu_dm_gclken*/
#define CPR_BT_SYS_CPU_DM_GCLKEN       CPR_BT_SYS_CPU_DM_GCLKEN_MSK
#define CPR_BT_SYS_CPU_DM_GCLKEN_W(X)  ((X) << CPR_BT_SYS_CPU_DM_GCLKEN_POS)
#define CPR_BT_SYS_CPU_EM_GCLKEN_POS   (3U)
#define CPR_BT_SYS_CPU_EM_GCLKEN_MSK   (0x1UL << CPR_BT_SYS_CPU_EM_GCLKEN_POS) /*!< bt_sys_cpu_em_gclken*/
#define CPR_BT_SYS_CPU_EM_GCLKEN       CPR_BT_SYS_CPU_EM_GCLKEN_MSK
#define CPR_BT_SYS_CPU_EM_GCLKEN_W(X)  ((X) << CPR_BT_SYS_CPU_EM_GCLKEN_POS)
#define CPR_BT_SYS_CLKSEL_POS          (4U)
#define CPR_BT_SYS_CLKSEL_MSK          (0x3fUL << CPR_BT_SYS_CLKSEL_POS) /*!< bt_sys_clksel*/
#define CPR_BT_SYS_CLKSEL              CPR_BT_SYS_CLKSEL_MSK
#define CPR_BT_SYS_CLKSEL_W(X)         ((X) << CPR_BT_SYS_CLKSEL_POS)
#define CPR_BT_SYS_TAHDT_MODE_POS        (10U)
#define CPR_BT_SYS_TAHDT_MODE_MSK        (0x1UL << CPR_BT_SYS_TAHDT_MODE_POS) /*!< 0: rw br/edr/le; 2.4g bb 1: sparklink/private ble*/
#define CPR_BT_SYS_TAHDT_MODE            CPR_BT_SYS_TAHDT_MODE_MSK
#define CPR_BT_SYS_TAHDT_MODE_W(X)       ((X) << CPR_BT_SYS_TAHDT_MODE_POS)

//DMA_CTRL offsetaddress : 0x00e4
//DMA_CTRL RegResetValue : 0x0
#define CPR_CPU_DMA_CH_CLK_EN_5_0_POS    (0U)
#define CPR_CPU_DMA_CH_CLK_EN_5_0_MSK    (0x3fUL << CPR_CPU_DMA_CH_CLK_EN_5_0_POS) /*!< cpu dma channel clock enable*/
#define CPR_CPU_DMA_CH_CLK_EN_5_0        CPR_CPU_DMA_CH_CLK_EN_5_0_MSK
#define CPR_CPU_DMA_CH_CLK_EN_5_0_W(X)   ((X) << CPR_CPU_DMA_CH_CLK_EN_5_0_POS)
#define CPR_CPU2_DMA_CH_CLK_EN_3_0_POS   (6U)
#define CPR_CPU2_DMA_CH_CLK_EN_3_0_MSK   (0xfUL << CPR_CPU2_DMA_CH_CLK_EN_3_0_POS) /*!< CPU2 dma channel clock enable*/
#define CPR_CPU2_DMA_CH_CLK_EN_3_0       CPR_CPU2_DMA_CH_CLK_EN_3_0_MSK
#define CPR_CPU2_DMA_CH_CLK_EN_3_0_W(X)  ((X) << CPR_CPU2_DMA_CH_CLK_EN_3_0_POS)
#define CPR_AUDIO_DMA_CH_CLK_EN_3_0_POS  (10U)
#define CPR_AUDIO_DMA_CH_CLK_EN_3_0_MSK  (0xfUL << CPR_AUDIO_DMA_CH_CLK_EN_3_0_POS) /*!< audio dma channel clock enable*/
#define CPR_AUDIO_DMA_CH_CLK_EN_3_0      CPR_AUDIO_DMA_CH_CLK_EN_3_0_MSK
#define CPR_AUDIO_DMA_CH_CLK_EN_3_0_W(X) ((X) << CPR_AUDIO_DMA_CH_CLK_EN_3_0_POS)
#define CPR_CPU2_DMA_SEL_0_POS           (16U)
#define CPR_CPU2_DMA_SEL_0_MSK           (0x1UL << CPR_CPU2_DMA_SEL_0_POS) /*!< CPU2 dma handshake[0] select: 0: dump_anc_req[0] 1: tsing_codec_dma_tx_req[0]*/
#define CPR_CPU2_DMA_SEL_0               CPR_CPU2_DMA_SEL_0_MSK
#define CPR_CPU2_DMA_SEL_0_W(X)          ((X) << CPR_CPU2_DMA_SEL_0_POS)
#define CPR_CPU2_DMA_SEL_1_POS           (17U)
#define CPR_CPU2_DMA_SEL_1_MSK           (0x1UL << CPR_CPU2_DMA_SEL_1_POS) /*!< CPU2 dma handshake[1] select: 0: dump_anc_req[1] 1: tsing_codec_dma_tx_req[1]*/
#define CPR_CPU2_DMA_SEL_1               CPR_CPU2_DMA_SEL_1_MSK
#define CPR_CPU2_DMA_SEL_1_W(X)          ((X) << CPR_CPU2_DMA_SEL_1_POS)
#define CPR_CPU2_DMA_SEL_2_POS           (18U)
#define CPR_CPU2_DMA_SEL_2_MSK           (0x1UL << CPR_CPU2_DMA_SEL_2_POS) /*!< CPU2 dma handshake[2] select: 0: dump_anc_req[2] 1: tsing_codec_dma_rx_req[0]*/
#define CPR_CPU2_DMA_SEL_2               CPR_CPU2_DMA_SEL_2_MSK
#define CPR_CPU2_DMA_SEL_2_W(X)          ((X) << CPR_CPU2_DMA_SEL_2_POS)
#define CPR_CPU2_DMA_SEL_3_POS           (19U)
#define CPR_CPU2_DMA_SEL_3_MSK           (0x1UL << CPR_CPU2_DMA_SEL_3_POS) /*!< CPU2 dma handshake[3] select: 0: dump_anc_req[3] 1: tsing_codec_dma_rx_req[1]*/
#define CPR_CPU2_DMA_SEL_3               CPR_CPU2_DMA_SEL_3_MSK
#define CPR_CPU2_DMA_SEL_3_W(X)          ((X) << CPR_CPU2_DMA_SEL_3_POS)
#define CPR_CPU2_DMA_SEL_4_POS           (20U)
#define CPR_CPU2_DMA_SEL_4_MSK           (0x1UL << CPR_CPU2_DMA_SEL_4_POS) /*!< CPU2 dma handshake[4] select: 0: i2s0_dma_tx_req 1: i2s0_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_4               CPR_CPU2_DMA_SEL_4_MSK
#define CPR_CPU2_DMA_SEL_4_W(X)          ((X) << CPR_CPU2_DMA_SEL_4_POS)
#define CPR_CPU2_DMA_SEL_5_POS           (21U)
#define CPR_CPU2_DMA_SEL_5_MSK           (0x1UL << CPR_CPU2_DMA_SEL_5_POS) /*!< CPU2 dma handshake[5] select: 0: i2s1_dma_tx_req 1: i2s1_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_5               CPR_CPU2_DMA_SEL_5_MSK
#define CPR_CPU2_DMA_SEL_5_W(X)          ((X) << CPR_CPU2_DMA_SEL_5_POS)
#define CPR_CPU2_DMA_SEL_6_POS           (22U)
#define CPR_CPU2_DMA_SEL_6_MSK           (0x1UL << CPR_CPU2_DMA_SEL_6_POS) /*!< CPU2 dma handshake[6] select: 0: i2s2_dma_tx_req 1: i2s2_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_6               CPR_CPU2_DMA_SEL_6_MSK
#define CPR_CPU2_DMA_SEL_6_W(X)          ((X) << CPR_CPU2_DMA_SEL_6_POS)
#define CPR_CPU2_DMA_SEL_7_POS           (23U)
#define CPR_CPU2_DMA_SEL_7_MSK           (0x1UL << CPR_CPU2_DMA_SEL_7_POS) /*!< CPU2 dma handshake[7] select: 0: i2s3_dma_tx_req 1: i2s3_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_7               CPR_CPU2_DMA_SEL_7_MSK
#define CPR_CPU2_DMA_SEL_7_W(X)          ((X) << CPR_CPU2_DMA_SEL_7_POS)
#define CPR_CPU2_DMA_SEL_8_POS           (24U)
#define CPR_CPU2_DMA_SEL_8_MSK           (0x1UL << CPR_CPU2_DMA_SEL_8_POS) /*!< CPU2 dma handshake[8] select: 0: spdif_dma_req 1: i2s0_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_8               CPR_CPU2_DMA_SEL_8_MSK
#define CPR_CPU2_DMA_SEL_8_W(X)          ((X) << CPR_CPU2_DMA_SEL_8_POS)
#define CPR_CPU2_DMA_SEL_9_POS           (25U)
#define CPR_CPU2_DMA_SEL_9_MSK           (0x1UL << CPR_CPU2_DMA_SEL_9_POS) /*!< CPU2 dma handshake[9] select: 0: pdmc_dma_tx_req 1: i2s1_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_9               CPR_CPU2_DMA_SEL_9_MSK
#define CPR_CPU2_DMA_SEL_9_W(X)          ((X) << CPR_CPU2_DMA_SEL_9_POS)
#define CPR_CPU2_DMA_SEL_10_POS          (26U)
#define CPR_CPU2_DMA_SEL_10_MSK          (0x1UL << CPR_CPU2_DMA_SEL_10_POS) /*!< CPU2 dma handshake[10] select: 0: resample_dma_tx_req 1: i2s2_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_10              CPR_CPU2_DMA_SEL_10_MSK
#define CPR_CPU2_DMA_SEL_10_W(X)         ((X) << CPR_CPU2_DMA_SEL_10_POS)
#define CPR_CPU2_DMA_SEL_11_POS          (27U)
#define CPR_CPU2_DMA_SEL_11_MSK          (0x1UL << CPR_CPU2_DMA_SEL_11_POS) /*!< CPU2 dma handshake[11] select: 0: resample_dma_rx_req 1: i2s3_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_11              CPR_CPU2_DMA_SEL_11_MSK
#define CPR_CPU2_DMA_SEL_11_W(X)         ((X) << CPR_CPU2_DMA_SEL_11_POS)
#define CPR_CPU2_DMA_SEL_12_POS          (28U)
#define CPR_CPU2_DMA_SEL_12_MSK          (0x1UL << CPR_CPU2_DMA_SEL_12_POS) /*!< CPU2 dma handshake[12] select: 0: pdm0_dma_req 1: resample_dma_tx_req*/
#define CPR_CPU2_DMA_SEL_12              CPR_CPU2_DMA_SEL_12_MSK
#define CPR_CPU2_DMA_SEL_12_W(X)         ((X) << CPR_CPU2_DMA_SEL_12_POS)
#define CPR_CPU2_DMA_SEL_13_POS          (29U)
#define CPR_CPU2_DMA_SEL_13_MSK          (0x1UL << CPR_CPU2_DMA_SEL_13_POS) /*!< CPU2 dma handshake[13] select: 0: pdm1_dma_req 1: resample_dma_rx_req*/
#define CPR_CPU2_DMA_SEL_13              CPR_CPU2_DMA_SEL_13_MSK
#define CPR_CPU2_DMA_SEL_13_W(X)         ((X) << CPR_CPU2_DMA_SEL_13_POS)
#define CPR_CPU2_DMA_SEL_14_POS          (30U)
#define CPR_CPU2_DMA_SEL_14_MSK          (0x1UL << CPR_CPU2_DMA_SEL_14_POS) /*!< CPU2 dma handshake[14] select: 0: spdif_dma_req 1: pdm0_dma_req*/
#define CPR_CPU2_DMA_SEL_14              CPR_CPU2_DMA_SEL_14_MSK
#define CPR_CPU2_DMA_SEL_14_W(X)         ((X) << CPR_CPU2_DMA_SEL_14_POS)
#define CPR_CPU2_DMA_SEL_15_POS          (31U)
#define CPR_CPU2_DMA_SEL_15_MSK          (0x1UL << CPR_CPU2_DMA_SEL_15_POS) /*!< CPU2 dma handshake[15] select: 0: pdmc_dma_tx_req 1: pdm1_dma_req*/
#define CPR_CPU2_DMA_SEL_15              CPR_CPU2_DMA_SEL_15_MSK
#define CPR_CPU2_DMA_SEL_15_W(X)         ((X) << CPR_CPU2_DMA_SEL_15_POS)

//PD_CTRL offsetaddress : 0x00e8
//PD_CTRL RegResetValue : 0x1b3
#define CPR_AUDIO_SYS_PD_POS       (0U)
#define CPR_AUDIO_SYS_PD_MSK       (0x1UL << CPR_AUDIO_SYS_PD_POS) /*!< audio system power control 0: power on 1: power off*/
#define CPR_AUDIO_SYS_PD           CPR_AUDIO_SYS_PD_MSK
#define CPR_AUDIO_SYS_ISO_POS      (1U)
#define CPR_AUDIO_SYS_ISO_MSK      (0x1UL << CPR_AUDIO_SYS_ISO_POS) /*!< audio system isolation control 0: isolation off 1: isolation on*/
#define CPR_AUDIO_SYS_ISO          CPR_AUDIO_SYS_ISO_MSK
#define CPR_CPU0_LP_EN_POS         (2U)
#define CPR_CPU0_LP_EN_MSK         (0x1UL << CPR_CPU0_LP_EN_POS) /*!< */
#define CPR_CPU0_LP_EN             CPR_CPU0_LP_EN_MSK
#define CPR_CPU1_LP_EN_POS         (3U)
#define CPR_CPU1_LP_EN_MSK         (0x1UL << CPR_CPU1_LP_EN_POS) /*!< */
#define CPR_CPU1_LP_EN             CPR_CPU1_LP_EN_MSK
#define CPR_CPU2_LP_EN_POS         (4U)
#define CPR_CPU2_LP_EN_MSK         (0x1UL << CPR_CPU2_LP_EN_POS) /*!< */
#define CPR_CPU2_LP_EN             CPR_CPU2_LP_EN_MSK
#define CPR_MAIN_APB_LP_EN_POS     (5U)
#define CPR_MAIN_APB_LP_EN_MSK     (0x1UL << CPR_MAIN_APB_LP_EN_POS) /*!< */
#define CPR_MAIN_APB_LP_EN         CPR_MAIN_APB_LP_EN_MSK
#define CPR_CPU0F_SLEEP_ACK_EN_POS (6U)
#define CPR_CPU0F_SLEEP_ACK_EN_MSK (0x1UL << CPR_CPU0F_SLEEP_ACK_EN_POS) /*!< mcu system low power mode enable 0: mcu system does not enter low power mode 1: mcu system enters low power mode upon sleep kick(w/o wfi) or wfi after sleep kick*/
#define CPR_CPU0F_SLEEP_ACK_EN     CPR_CPU0F_SLEEP_ACK_EN_MSK
#define CPR_CPU2_APB_LP_EN_POS     (7U)
#define CPR_CPU2_APB_LP_EN_MSK     (0x1UL << CPR_CPU2_APB_LP_EN_POS) /*!< */
#define CPR_CPU2_APB_LP_EN         CPR_CPU2_APB_LP_EN_MSK
#define CPR_AON_APB_LP_EN_POS      (8U)
#define CPR_AON_APB_LP_EN_MSK      (0x1UL << CPR_AON_APB_LP_EN_POS) /*!< */
#define CPR_AON_APB_LP_EN          CPR_AON_APB_LP_EN_MSK
#define CPR_CPU1_APB_LP_EN_POS     (9U)
#define CPR_CPU1_APB_LP_EN_MSK     (0x1UL << CPR_CPU1_APB_LP_EN_POS) /*!< */
#define CPR_CPU1_APB_LP_EN         CPR_CPU1_APB_LP_EN_MSK
#define CPR_TIMER_LP_EN_POS        (10U)
#define CPR_TIMER_LP_EN_MSK        (0x1UL << CPR_TIMER_LP_EN_POS) /*!< */
#define CPR_TIMER_LP_EN            CPR_TIMER_LP_EN_MSK
#define CPR_DWC_SSI_LP_EN_POS      (11U)
#define CPR_DWC_SSI_LP_EN_MSK      (0x1UL << CPR_DWC_SSI_LP_EN_POS) /*!< */
#define CPR_DWC_SSI_LP_EN          CPR_DWC_SSI_LP_EN_MSK
#define CPR_UART_LP_EN_POS         (12U)
#define CPR_UART_LP_EN_MSK         (0x1UL << CPR_UART_LP_EN_POS) /*!< */
#define CPR_UART_LP_EN             CPR_UART_LP_EN_MSK
#define CPR_I2C_LP_EN_POS          (13U)
#define CPR_I2C_LP_EN_MSK          (0x1UL << CPR_I2C_LP_EN_POS) /*!< */
#define CPR_I2C_LP_EN              CPR_I2C_LP_EN_MSK
#define CPR_SPI_LP_EN_POS          (14U)
#define CPR_SPI_LP_EN_MSK          (0x1UL << CPR_SPI_LP_EN_POS) /*!< */
#define CPR_SPI_LP_EN              CPR_SPI_LP_EN_MSK
#define CPR_CPU1_SLEEP_ACK_EN_POS  (15U)
#define CPR_CPU1_SLEEP_ACK_EN_MSK  (0x1UL << CPR_CPU1_SLEEP_ACK_EN_POS) /*!< rf system low power mode enable 0: rf system does not enter low power mode 1: rf system enters low power mode upon sleep kick(w/o wfi) or wfi after sleep kick*/
#define CPR_CPU1_SLEEP_ACK_EN      CPR_CPU1_SLEEP_ACK_EN_MSK

//PERI_CTRL offsetaddress : 0x00ec
//PERI_CTRL RegResetValue : 0x0
#define CPR_CPU_WDT_PAUSE_POS       (0U)
#define CPR_CPU_WDT_PAUSE_MSK       (0x1UL << CPR_CPU_WDT_PAUSE_POS) /*!< CPU0 watchdog timer pause*/
#define CPR_CPU_WDT_PAUSE           CPR_CPU_WDT_PAUSE_MSK
#define CPR_CPU_RF_WDT_PAUSE_POS    (1U)
#define CPR_CPU_RF_WDT_PAUSE_MSK    (0x1UL << CPR_CPU_RF_WDT_PAUSE_POS) /*!< CPU1 watchdog timer pause*/
#define CPR_CPU_RF_WDT_PAUSE        CPR_CPU_RF_WDT_PAUSE_MSK
#define CPR_CPU2_WDT_PAUSE_POS      (2U)
#define CPR_CPU2_WDT_PAUSE_MSK      (0x1UL << CPR_CPU2_WDT_PAUSE_POS) /*!< CPU2 watchdog timer pause*/
#define CPR_CPU2_WDT_PAUSE          CPR_CPU2_WDT_PAUSE_MSK
#define CPR_PORT_UART_IRDA_SEL_POS  (3U)
#define CPR_PORT_UART_IRDA_SEL_MSK  (0x1UL << CPR_PORT_UART_IRDA_SEL_POS) /*!< */
#define CPR_PORT_UART_IRDA_SEL      CPR_PORT_UART_IRDA_SEL_MSK
#define CPR_PORT_UART4_IRDA_SEL_POS (4U)
#define CPR_PORT_UART4_IRDA_SEL_MSK (0x1UL << CPR_PORT_UART4_IRDA_SEL_POS) /*!< */
#define CPR_PORT_UART4_IRDA_SEL     CPR_PORT_UART4_IRDA_SEL_MSK
#define CPR_BT_PCM_USE_I2S2_POS     (5U)
#define CPR_BT_PCM_USE_I2S2_MSK     (0x1UL << CPR_BT_PCM_USE_I2S2_POS) /*!< */
#define CPR_BT_PCM_USE_I2S2         CPR_BT_PCM_USE_I2S2_MSK
#define CPR_USB1_RESUME_POS         (6U)
#define CPR_USB1_RESUME_MSK         (0x1UL << CPR_USB1_RESUME_POS) /*!< usb1 resume*/
#define CPR_USB1_RESUME             CPR_USB1_RESUME_MSK

//CPU2_CFG offsetaddress : 0x00f0
//CPU2_CFG RegResetValue : 0x0
#define CPR_CPU2_TCM_MEM_SEL_POS   (0U)
#define CPR_CPU2_TCM_MEM_SEL_MSK   (0x1UL << CPR_CPU2_TCM_MEM_SEL_POS) /*!< CPU2 ICACHE and DTCM multiplexing enable; 0 - ICACHE (128KB) DTCM (384KB) 1 - DTCM (512KB)*/
#define CPR_CPU2_TCM_MEM_SEL       CPR_CPU2_TCM_MEM_SEL_MSK
#define CPR_CPU2_TCM_MEM_SEL_W(X)  ((X) << CPR_CPU2_TCM_MEM_SEL_POS)
#define CPR_CPU2_STALL_POS         (1U)
#define CPR_CPU2_STALL_MSK         (0x1UL << CPR_CPU2_STALL_POS) /*!< CPU2 stall. When set to 1, CPU2 will enter low power mode immediately.*/
#define CPR_CPU2_STALL             CPR_CPU2_STALL_MSK
#define CPR_CPU2_STALL_W(X)        ((X) << CPR_CPU2_STALL_POS)
#define CPR_CPU2_REMAP_POS         (2U)
#define CPR_CPU2_REMAP_MSK         (0x1UL << CPR_CPU2_REMAP_POS) /*!< CPU2 remap. 1 = CPU2 run from CPU2_REMAP_VEC register 0 = CPU2 run from CPU2 TCM (internal)*/
#define CPR_CPU2_REMAP             CPR_CPU2_REMAP_MSK
#define CPR_CPU2_REMAP_W(X)        ((X) << CPR_CPU2_REMAP_POS)
#define CPR_CPU2_OCDHALTONRST_POS  (3U)
#define CPR_CPU2_OCDHALTONRST_MSK  (0x1UL << CPR_CPU2_OCDHALTONRST_POS) /*!< Enters OCDHaltMode if this signal is sampled asserted on reset*/
#define CPR_CPU2_OCDHALTONRST      CPR_CPU2_OCDHALTONRST_MSK
#define CPR_CPU2_OCDHALTONRST_W(X) ((X) << CPR_CPU2_OCDHALTONRST_POS)
#define CPR_CPU2_PDEBUGENABLE_POS  (4U)
#define CPR_CPU2_PDEBUGENABLE_MSK  (0x1UL << CPR_CPU2_PDEBUGENABLE_POS) /*!< Traceport enable*/
#define CPR_CPU2_PDEBUGENABLE      CPR_CPU2_PDEBUGENABLE_MSK
#define CPR_CPU2_PDEBUGENABLE_W(X) ((X) << CPR_CPU2_PDEBUGENABLE_POS)

//DAC_CLK_CFG offsetaddress : 0x00f4
//DAC_CLK_CFG RegResetValue : 0x7017f
#define CPR_CODEC_DAC_TIMER_STROBE_DIV_POS  (0U)
#define CPR_CODEC_DAC_TIMER_STROBE_DIV_MSK  (0xffffUL << CPR_CODEC_DAC_TIMER_STROBE_DIV_POS) /*!< DAC timer strobe divider factor, the source clock is codec_dac_clk.*/
#define CPR_CODEC_DAC_TIMER_STROBE_DIV      CPR_CODEC_DAC_TIMER_STROBE_DIV_MSK
#define CPR_CODEC_DAC_TIMER_STROBE_DIV_W(X) ((X) << CPR_CODEC_DAC_TIMER_STROBE_DIV_POS)
#define CPR_CODEC_DAC_OFC_CLK_DIV_POS       (16U)
#define CPR_CODEC_DAC_OFC_CLK_DIV_MSK       (0xffUL << CPR_CODEC_DAC_OFC_CLK_DIV_POS) /*!< DAC ofc clock divider factor, the source clock is 32k clock.*/
#define CPR_CODEC_DAC_OFC_CLK_DIV           CPR_CODEC_DAC_OFC_CLK_DIV_MSK
#define CPR_CODEC_DAC_OFC_CLK_DIV_W(X)      ((X) << CPR_CODEC_DAC_OFC_CLK_DIV_POS)
#define CPR_CODEC_DAC_OFC_CLK_EN_POS        (24U)
#define CPR_CODEC_DAC_OFC_CLK_EN_MSK        (0x1UL << CPR_CODEC_DAC_OFC_CLK_EN_POS) /*!< DAC ofc clock enables.*/
#define CPR_CODEC_DAC_OFC_CLK_EN            CPR_CODEC_DAC_OFC_CLK_EN_MSK
#define CPR_CODEC_DAC_OFC_CLK_EN_W(X)       ((X) << CPR_CODEC_DAC_OFC_CLK_EN_POS)

//CLK_MUX1 offsetaddress : 0x00f8
//CLK_MUX1 RegResetValue : 0x0
#define CPR_TIMER_1_SEL_POS   (0U)
#define CPR_TIMER_1_SEL_MSK   (0x3UL << CPR_TIMER_1_SEL_POS) /*!< timer_1 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER_1_SEL       CPR_TIMER_1_SEL_MSK
#define CPR_TIMER_1_SEL_W(X)  ((X) << CPR_TIMER_1_SEL_POS)
#define CPR_TIMER_2_SEL_POS   (2U)
#define CPR_TIMER_2_SEL_MSK   (0x3UL << CPR_TIMER_2_SEL_POS) /*!< timer_2 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER_2_SEL       CPR_TIMER_2_SEL_MSK
#define CPR_TIMER_2_SEL_W(X)  ((X) << CPR_TIMER_2_SEL_POS)
#define CPR_TIMER_3_SEL_POS   (4U)
#define CPR_TIMER_3_SEL_MSK   (0x3UL << CPR_TIMER_3_SEL_POS) /*!< timer_3 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER_3_SEL       CPR_TIMER_3_SEL_MSK
#define CPR_TIMER_3_SEL_W(X)  ((X) << CPR_TIMER_3_SEL_POS)
#define CPR_TIMER_4_SEL_POS   (6U)
#define CPR_TIMER_4_SEL_MSK   (0x3UL << CPR_TIMER_4_SEL_POS) /*!< timer_4 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER_4_SEL       CPR_TIMER_4_SEL_MSK
#define CPR_TIMER_4_SEL_W(X)  ((X) << CPR_TIMER_4_SEL_POS)
#define CPR_TIMER1_1_SEL_POS  (8U)
#define CPR_TIMER1_1_SEL_MSK  (0x3UL << CPR_TIMER1_1_SEL_POS) /*!< timer1_1 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER1_1_SEL      CPR_TIMER1_1_SEL_MSK
#define CPR_TIMER1_1_SEL_W(X) ((X) << CPR_TIMER1_1_SEL_POS)
#define CPR_TIMER1_2_SEL_POS  (10U)
#define CPR_TIMER1_2_SEL_MSK  (0x3UL << CPR_TIMER1_2_SEL_POS) /*!< timer1_2 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER1_2_SEL      CPR_TIMER1_2_SEL_MSK
#define CPR_TIMER1_2_SEL_W(X) ((X) << CPR_TIMER1_2_SEL_POS)
#define CPR_TIMER1_3_SEL_POS  (12U)
#define CPR_TIMER1_3_SEL_MSK  (0x3UL << CPR_TIMER1_3_SEL_POS) /*!< timer1_3 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER1_3_SEL      CPR_TIMER1_3_SEL_MSK
#define CPR_TIMER1_3_SEL_W(X) ((X) << CPR_TIMER1_3_SEL_POS)
#define CPR_TIMER1_4_SEL_POS  (14U)
#define CPR_TIMER1_4_SEL_MSK  (0x3UL << CPR_TIMER1_4_SEL_POS) /*!< timer1_4 clock source selection: 0:clk32 1:clk_hfxo 2/3:mclk3_cpr*/
#define CPR_TIMER1_4_SEL      CPR_TIMER1_4_SEL_MSK
#define CPR_TIMER1_4_SEL_W(X) ((X) << CPR_TIMER1_4_SEL_POS)

//SDMMC_CLK_CFG offsetaddress : 0x00fc
//SDMMC_CLK_CFG RegResetValue : 0x3f023
#define CPR_SDMMC_MCLK_DIV_POS     (0U)
#define CPR_SDMMC_MCLK_DIV_MSK     (0xfUL << CPR_SDMMC_MCLK_DIV_POS) /*!< SDMMC_MCLK frequency division factor*/
#define CPR_SDMMC_MCLK_DIV         CPR_SDMMC_MCLK_DIV_MSK
#define CPR_SDMMC_MCLK_DIV_W(X)    ((X) << CPR_SDMMC_MCLK_DIV_POS)
#define CPR_SDMMC_RX_DELAY_POS     (4U)
#define CPR_SDMMC_RX_DELAY_MSK     (0x3UL << CPR_SDMMC_RX_DELAY_POS) /*!< The delay beat number of SDMMC_RXCLK relative to SDMMC_MCLK is the register value plus 1. The number of beats is the source clock of SDMMC_MCLK.*/
#define CPR_SDMMC_RX_DELAY         CPR_SDMMC_RX_DELAY_MSK
#define CPR_SDMMC_RX_DELAY_W(X)    ((X) << CPR_SDMMC_RX_DELAY_POS)
#define CPR_SDMMC_TX_DELAY_POS     (8U)
#define CPR_SDMMC_TX_DELAY_MSK     (0x3UL << CPR_SDMMC_TX_DELAY_POS) /*!< The delay beat number of SDMMC_TXCLK relative to SDMMC_MCLK is the register value plus 1. The beat number unit is the source clock of SDMMC_MCLK.*/
#define CPR_SDMMC_TX_DELAY         CPR_SDMMC_TX_DELAY_MSK
#define CPR_SDMMC_TX_DELAY_W(X)    ((X) << CPR_SDMMC_TX_DELAY_POS)
#define CPR_SDMMC_RXCLK_EN_POS     (12U)
#define CPR_SDMMC_RXCLK_EN_MSK     (0x1UL << CPR_SDMMC_RXCLK_EN_POS) /*!< SDMMC_RXCLK enabled*/
#define CPR_SDMMC_RXCLK_EN         CPR_SDMMC_RXCLK_EN_MSK
#define CPR_SDMMC_RXCLK_EN_W(X)    ((X) << CPR_SDMMC_RXCLK_EN_POS)
#define CPR_SDMMC_TXCLK_EN_POS     (13U)
#define CPR_SDMMC_TXCLK_EN_MSK     (0x1UL << CPR_SDMMC_TXCLK_EN_POS) /*!< SDMMC_TXCLK enabled*/
#define CPR_SDMMC_TXCLK_EN         CPR_SDMMC_TXCLK_EN_MSK
#define CPR_SDMMC_TXCLK_EN_W(X)    ((X) << CPR_SDMMC_TXCLK_EN_POS)
#define CPR_SDMMC_MCLK_EN_POS      (14U)
#define CPR_SDMMC_MCLK_EN_MSK      (0x1UL << CPR_SDMMC_MCLK_EN_POS) /*!< SDMMC_MCLK enabled*/
#define CPR_SDMMC_MCLK_EN          CPR_SDMMC_MCLK_EN_MSK
#define CPR_SDMMC_MCLK_EN_W(X)     ((X) << CPR_SDMMC_MCLK_EN_POS)
#define CPR_SDMMC_HCLK_EN_POS      (15U)
#define CPR_SDMMC_HCLK_EN_MSK      (0x1UL << CPR_SDMMC_HCLK_EN_POS) /*!< SDMMC_HCLK enable*/
#define CPR_SDMMC_HCLK_EN          CPR_SDMMC_HCLK_EN_MSK
#define CPR_SDMMC_HCLK_EN_W(X)     ((X) << CPR_SDMMC_HCLK_EN_POS)
#define CPR_RSTN_SOFT_SDMMC_POS    (16U)
#define CPR_RSTN_SOFT_SDMMC_MSK    (0x1UL << CPR_RSTN_SOFT_SDMMC_POS) /*!< SDMMC module function soft reset 0: Reset 1: No reset*/
#define CPR_RSTN_SOFT_SDMMC        CPR_RSTN_SOFT_SDMMC_MSK
#define CPR_RSTN_SOFT_SDMMC_W(X)   ((X) << CPR_RSTN_SOFT_SDMMC_POS)
#define CPR_RSTN_SOFT_SDMMC_H_POS  (17U)
#define CPR_RSTN_SOFT_SDMMC_H_MSK  (0x1UL << CPR_RSTN_SOFT_SDMMC_H_POS) /*!< SDMMC module bus soft reset 0: Reset 1: No reset*/
#define CPR_RSTN_SOFT_SDMMC_H      CPR_RSTN_SOFT_SDMMC_H_MSK
#define CPR_RSTN_SOFT_SDMMC_H_W(X) ((X) << CPR_RSTN_SOFT_SDMMC_H_POS)

//PD_RAM_CTRL_0 offsetaddress : 0x100
//PD_RAM_CTRL_0 RegResetValue : 0x0
#define CPR_CPU0_ILM_LP_MAN_EN_POS      (0U)
#define CPR_CPU0_ILM_LP_MAN_EN_MSK      (0x7UL << CPR_CPU0_ILM_LP_MAN_EN_POS) /*!< */
#define CPR_CPU0_ILM_LP_MAN_EN          CPR_CPU0_ILM_LP_MAN_EN_MSK
#define CPR_CPU0_ILM_LP_MAN_EN_W(X)     ((X) << CPR_CPU0_ILM_LP_MAN_EN_POS)
#define CPR_CPU0_ICACHE_LP_MAN_EN_POS   (3U)
#define CPR_CPU0_ICACHE_LP_MAN_EN_MSK   (0x3UL << CPR_CPU0_ICACHE_LP_MAN_EN_POS) /*!< */
#define CPR_CPU0_ICACHE_LP_MAN_EN       CPR_CPU0_ICACHE_LP_MAN_EN_MSK
#define CPR_CPU0_ICACHE_LP_MAN_EN_W(X)  ((X) << CPR_CPU0_ICACHE_LP_MAN_EN_POS)
#define CPR_CPU0_DCACHE_LP_MAN_EN_POS   (5U)
#define CPR_CPU0_DCACHE_LP_MAN_EN_MSK   (0x1UL << CPR_CPU0_DCACHE_LP_MAN_EN_POS) /*!< */
#define CPR_CPU0_DCACHE_LP_MAN_EN       CPR_CPU0_DCACHE_LP_MAN_EN_MSK
#define CPR_CPU0_DCACHE_LP_MAN_EN_W(X)  ((X) << CPR_CPU0_DCACHE_LP_MAN_EN_POS)
#define CPR_CPU0_BTB_LP_MAN_EN_POS      (6U)
#define CPR_CPU0_BTB_LP_MAN_EN_MSK      (0x1UL << CPR_CPU0_BTB_LP_MAN_EN_POS) /*!< */
#define CPR_CPU0_BTB_LP_MAN_EN          CPR_CPU0_BTB_LP_MAN_EN_MSK
#define CPR_CPU0_BTB_LP_MAN_EN_W(X)     ((X) << CPR_CPU0_BTB_LP_MAN_EN_POS)
#define CPR_UART_RAM_LP_MAN_EN_POS      (7U)
#define CPR_UART_RAM_LP_MAN_EN_MSK      (0x1UL << CPR_UART_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_UART_RAM_LP_MAN_EN          CPR_UART_RAM_LP_MAN_EN_MSK
#define CPR_UART_RAM_LP_MAN_EN_W(X)     ((X) << CPR_UART_RAM_LP_MAN_EN_POS)
#define CPR_BTMDM_RAM_LP_MAN_EN_POS     (8U)
#define CPR_BTMDM_RAM_LP_MAN_EN_MSK     (0x1UL << CPR_BTMDM_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_BTMDM_RAM_LP_MAN_EN         CPR_BTMDM_RAM_LP_MAN_EN_MSK
#define CPR_BTMDM_RAM_LP_MAN_EN_W(X)    ((X) << CPR_BTMDM_RAM_LP_MAN_EN_POS)
#define CPR_USB_RAM_LP_MAN_EN_POS       (9U)
#define CPR_USB_RAM_LP_MAN_EN_MSK       (0x1UL << CPR_USB_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_USB_RAM_LP_MAN_EN           CPR_USB_RAM_LP_MAN_EN_MSK
#define CPR_USB_RAM_LP_MAN_EN_W(X)      ((X) << CPR_USB_RAM_LP_MAN_EN_POS)
#define CPR_USB1_RAM_LP_MAN_EN_POS      (10U)
#define CPR_USB1_RAM_LP_MAN_EN_MSK      (0x1UL << CPR_USB1_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_USB1_RAM_LP_MAN_EN          CPR_USB1_RAM_LP_MAN_EN_MSK
#define CPR_USB1_RAM_LP_MAN_EN_W(X)     ((X) << CPR_USB1_RAM_LP_MAN_EN_POS)
#define CPR_RESAMPLE_RAM_LP_MAN_EN_POS  (11U)
#define CPR_RESAMPLE_RAM_LP_MAN_EN_MSK  (0x3UL << CPR_RESAMPLE_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_RESAMPLE_RAM_LP_MAN_EN      CPR_RESAMPLE_RAM_LP_MAN_EN_MSK
#define CPR_RESAMPLE_RAM_LP_MAN_EN_W(X) ((X) << CPR_RESAMPLE_RAM_LP_MAN_EN_POS)
#define CPR_CPU1_ILM_LP_MAN_EN_POS      (13U)
#define CPR_CPU1_ILM_LP_MAN_EN_MSK      (0x1ffUL << CPR_CPU1_ILM_LP_MAN_EN_POS) /*!< */
#define CPR_CPU1_ILM_LP_MAN_EN          CPR_CPU1_ILM_LP_MAN_EN_MSK
#define CPR_CPU1_ILM_LP_MAN_EN_W(X)     ((X) << CPR_CPU1_ILM_LP_MAN_EN_POS)
#define CPR_CPU1_DLM_LP_MAN_EN_POS      (22U)
#define CPR_CPU1_DLM_LP_MAN_EN_MSK      (0x3UL << CPR_CPU1_DLM_LP_MAN_EN_POS) /*!< */
#define CPR_CPU1_DLM_LP_MAN_EN          CPR_CPU1_DLM_LP_MAN_EN_MSK
#define CPR_CPU1_DLM_LP_MAN_EN_W(X)     ((X) << CPR_CPU1_DLM_LP_MAN_EN_POS)
#define CPR_SHRAM1_LP_MAN_EN_POS        (24U)
#define CPR_SHRAM1_LP_MAN_EN_MSK        (0x3UL << CPR_SHRAM1_LP_MAN_EN_POS) /*!< */
#define CPR_SHRAM1_LP_MAN_EN            CPR_SHRAM1_LP_MAN_EN_MSK
#define CPR_SHRAM1_LP_MAN_EN_W(X)       ((X) << CPR_SHRAM1_LP_MAN_EN_POS)

//PD_RAM_CTRL_1 offsetaddress : 0x104
//PD_RAM_CTRL_1 RegResetValue : 0x3ffffff
#define CPR_CPU0_ILM_RET1N_MAN_VAL_POS     (0U)
#define CPR_CPU0_ILM_RET1N_MAN_VAL_MSK     (0x7UL << CPR_CPU0_ILM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ILM_RET1N_MAN_VAL         CPR_CPU0_ILM_RET1N_MAN_VAL_MSK
#define CPR_CPU0_ILM_RET1N_MAN_VAL_W(X)    ((X) << CPR_CPU0_ILM_RET1N_MAN_VAL_POS)
#define CPR_CPU0_ICACHE_RET1N_MAN_VAL_POS  (3U)
#define CPR_CPU0_ICACHE_RET1N_MAN_VAL_MSK  (0x3UL << CPR_CPU0_ICACHE_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ICACHE_RET1N_MAN_VAL      CPR_CPU0_ICACHE_RET1N_MAN_VAL_MSK
#define CPR_CPU0_ICACHE_RET1N_MAN_VAL_W(X) ((X) << CPR_CPU0_ICACHE_RET1N_MAN_VAL_POS)
#define CPR_CPU0_DCACHE_RET1N_MAN_VAL_POS  (5U)
#define CPR_CPU0_DCACHE_RET1N_MAN_VAL_MSK  (0x1UL << CPR_CPU0_DCACHE_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_DCACHE_RET1N_MAN_VAL      CPR_CPU0_DCACHE_RET1N_MAN_VAL_MSK
#define CPR_CPU0_DCACHE_RET1N_MAN_VAL_W(X) ((X) << CPR_CPU0_DCACHE_RET1N_MAN_VAL_POS)
#define CPR_CPU0_BTB_RET1N_MAN_VAL_POS     (6U)
#define CPR_CPU0_BTB_RET1N_MAN_VAL_MSK     (0x1UL << CPR_CPU0_BTB_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_BTB_RET1N_MAN_VAL         CPR_CPU0_BTB_RET1N_MAN_VAL_MSK
#define CPR_CPU0_BTB_RET1N_MAN_VAL_W(X)    ((X) << CPR_CPU0_BTB_RET1N_MAN_VAL_POS)
#define CPR_UART_RAM_RET1N_MAN_VAL_POS     (7U)
#define CPR_UART_RAM_RET1N_MAN_VAL_MSK     (0x1UL << CPR_UART_RAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_UART_RAM_RET1N_MAN_VAL         CPR_UART_RAM_RET1N_MAN_VAL_MSK
#define CPR_UART_RAM_RET1N_MAN_VAL_W(X)    ((X) << CPR_UART_RAM_RET1N_MAN_VAL_POS)
#define CPR_BTMDM_RAM_RET1N_MAN_VAL_POS    (8U)
#define CPR_BTMDM_RAM_RET1N_MAN_VAL_MSK    (0x1UL << CPR_BTMDM_RAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_BTMDM_RAM_RET1N_MAN_VAL        CPR_BTMDM_RAM_RET1N_MAN_VAL_MSK
#define CPR_BTMDM_RAM_RET1N_MAN_VAL_W(X)   ((X) << CPR_BTMDM_RAM_RET1N_MAN_VAL_POS)
#define CPR_USB_RAM_RET1N_MAN_VAL_POS      (9U)
#define CPR_USB_RAM_RET1N_MAN_VAL_MSK      (0x1UL << CPR_USB_RAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_USB_RAM_RET1N_MAN_VAL          CPR_USB_RAM_RET1N_MAN_VAL_MSK
#define CPR_USB_RAM_RET1N_MAN_VAL_W(X)     ((X) << CPR_USB_RAM_RET1N_MAN_VAL_POS)
#define CPR_USB1_RAM_RET1N_MAN_VAL_POS     (10U)
#define CPR_USB1_RAM_RET1N_MAN_VAL_MSK     (0x1UL << CPR_USB1_RAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_USB1_RAM_RET1N_MAN_VAL         CPR_USB1_RAM_RET1N_MAN_VAL_MSK
#define CPR_USB1_RAM_RET1N_MAN_VAL_W(X)    ((X) << CPR_USB1_RAM_RET1N_MAN_VAL_POS)
#define CPR_RESAMPLE_RET1N_MAN_VAL_POS     (11U)
#define CPR_RESAMPLE_RET1N_MAN_VAL_MSK     (0x3UL << CPR_RESAMPLE_RET1N_MAN_VAL_POS) /*!< */
#define CPR_RESAMPLE_RET1N_MAN_VAL         CPR_RESAMPLE_RET1N_MAN_VAL_MSK
#define CPR_RESAMPLE_RET1N_MAN_VAL_W(X)    ((X) << CPR_RESAMPLE_RET1N_MAN_VAL_POS)
#define CPR_CPU1_ILM_RET1N_MAN_VAL_POS     (13U)
#define CPR_CPU1_ILM_RET1N_MAN_VAL_MSK     (0x1ffUL << CPR_CPU1_ILM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU1_ILM_RET1N_MAN_VAL         CPR_CPU1_ILM_RET1N_MAN_VAL_MSK
#define CPR_CPU1_ILM_RET1N_MAN_VAL_W(X)    ((X) << CPR_CPU1_ILM_RET1N_MAN_VAL_POS)
#define CPR_CPU1_DLM_RET1N_MAN_VAL_POS     (22U)
#define CPR_CPU1_DLM_RET1N_MAN_VAL_MSK     (0x3UL << CPR_CPU1_DLM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU1_DLM_RET1N_MAN_VAL         CPR_CPU1_DLM_RET1N_MAN_VAL_MSK
#define CPR_CPU1_DLM_RET1N_MAN_VAL_W(X)    ((X) << CPR_CPU1_DLM_RET1N_MAN_VAL_POS)
#define CPR_SHRAM1_RET1N_MAN_VAL_POS       (24U)
#define CPR_SHRAM1_RET1N_MAN_VAL_MSK       (0x3UL << CPR_SHRAM1_RET1N_MAN_VAL_POS) /*!< */
#define CPR_SHRAM1_RET1N_MAN_VAL           CPR_SHRAM1_RET1N_MAN_VAL_MSK
#define CPR_SHRAM1_RET1N_MAN_VAL_W(X)      ((X) << CPR_SHRAM1_RET1N_MAN_VAL_POS)

//PD_RAM_CTRL_2 offsetaddress : 0x108
//PD_RAM_CTRL_2 RegResetValue : 0x3ffffff
#define CPR_CPU0_ILM_RET2N_MAN_VAL_POS     (0U)
#define CPR_CPU0_ILM_RET2N_MAN_VAL_MSK     (0x7UL << CPR_CPU0_ILM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ILM_RET2N_MAN_VAL         CPR_CPU0_ILM_RET2N_MAN_VAL_MSK
#define CPR_CPU0_ILM_RET2N_MAN_VAL_W(X)    ((X) << CPR_CPU0_ILM_RET2N_MAN_VAL_POS)
#define CPR_CPU0_ICACHE_RET2N_MAN_VAL_POS  (3U)
#define CPR_CPU0_ICACHE_RET2N_MAN_VAL_MSK  (0x3UL << CPR_CPU0_ICACHE_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ICACHE_RET2N_MAN_VAL      CPR_CPU0_ICACHE_RET2N_MAN_VAL_MSK
#define CPR_CPU0_ICACHE_RET2N_MAN_VAL_W(X) ((X) << CPR_CPU0_ICACHE_RET2N_MAN_VAL_POS)
#define CPR_CPU0_DCACHE_RET2N_MAN_VAL_POS  (5U)
#define CPR_CPU0_DCACHE_RET2N_MAN_VAL_MSK  (0x1UL << CPR_CPU0_DCACHE_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_DCACHE_RET2N_MAN_VAL      CPR_CPU0_DCACHE_RET2N_MAN_VAL_MSK
#define CPR_CPU0_DCACHE_RET2N_MAN_VAL_W(X) ((X) << CPR_CPU0_DCACHE_RET2N_MAN_VAL_POS)
#define CPR_CPU0_BTB_RET2N_MAN_VAL_POS     (6U)
#define CPR_CPU0_BTB_RET2N_MAN_VAL_MSK     (0x1UL << CPR_CPU0_BTB_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU0_BTB_RET2N_MAN_VAL         CPR_CPU0_BTB_RET2N_MAN_VAL_MSK
#define CPR_CPU0_BTB_RET2N_MAN_VAL_W(X)    ((X) << CPR_CPU0_BTB_RET2N_MAN_VAL_POS)
#define CPR_UART_RAM_RET2N_MAN_VAL_POS     (7U)
#define CPR_UART_RAM_RET2N_MAN_VAL_MSK     (0x1UL << CPR_UART_RAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_UART_RAM_RET2N_MAN_VAL         CPR_UART_RAM_RET2N_MAN_VAL_MSK
#define CPR_UART_RAM_RET2N_MAN_VAL_W(X)    ((X) << CPR_UART_RAM_RET2N_MAN_VAL_POS)
#define CPR_BTMDM_RAM_RET2N_MAN_VAL_POS    (8U)
#define CPR_BTMDM_RAM_RET2N_MAN_VAL_MSK    (0x1UL << CPR_BTMDM_RAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_BTMDM_RAM_RET2N_MAN_VAL        CPR_BTMDM_RAM_RET2N_MAN_VAL_MSK
#define CPR_BTMDM_RAM_RET2N_MAN_VAL_W(X)   ((X) << CPR_BTMDM_RAM_RET2N_MAN_VAL_POS)
#define CPR_USB_RAM_RET2N_MAN_VAL_POS      (9U)
#define CPR_USB_RAM_RET2N_MAN_VAL_MSK      (0x1UL << CPR_USB_RAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_USB_RAM_RET2N_MAN_VAL          CPR_USB_RAM_RET2N_MAN_VAL_MSK
#define CPR_USB_RAM_RET2N_MAN_VAL_W(X)     ((X) << CPR_USB_RAM_RET2N_MAN_VAL_POS)
#define CPR_USB1_RAM_RET2N_MAN_VAL_POS     (10U)
#define CPR_USB1_RAM_RET2N_MAN_VAL_MSK     (0x1UL << CPR_USB1_RAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_USB1_RAM_RET2N_MAN_VAL         CPR_USB1_RAM_RET2N_MAN_VAL_MSK
#define CPR_USB1_RAM_RET2N_MAN_VAL_W(X)    ((X) << CPR_USB1_RAM_RET2N_MAN_VAL_POS)
#define CPR_RESAMPLE_RET2N_MAN_VAL_POS     (11U)
#define CPR_RESAMPLE_RET2N_MAN_VAL_MSK     (0x3UL << CPR_RESAMPLE_RET2N_MAN_VAL_POS) /*!< */
#define CPR_RESAMPLE_RET2N_MAN_VAL         CPR_RESAMPLE_RET2N_MAN_VAL_MSK
#define CPR_RESAMPLE_RET2N_MAN_VAL_W(X)    ((X) << CPR_RESAMPLE_RET2N_MAN_VAL_POS)
#define CPR_CPU1_ILM_RET2N_MAN_VAL_POS     (13U)
#define CPR_CPU1_ILM_RET2N_MAN_VAL_MSK     (0x1ffUL << CPR_CPU1_ILM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU1_ILM_RET2N_MAN_VAL         CPR_CPU1_ILM_RET2N_MAN_VAL_MSK
#define CPR_CPU1_ILM_RET2N_MAN_VAL_W(X)    ((X) << CPR_CPU1_ILM_RET2N_MAN_VAL_POS)
#define CPR_CPU1_DLM_RET2N_MAN_VAL_POS     (22U)
#define CPR_CPU1_DLM_RET2N_MAN_VAL_MSK     (0x3UL << CPR_CPU1_DLM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU1_DLM_RET2N_MAN_VAL         CPR_CPU1_DLM_RET2N_MAN_VAL_MSK
#define CPR_CPU1_DLM_RET2N_MAN_VAL_W(X)    ((X) << CPR_CPU1_DLM_RET2N_MAN_VAL_POS)
#define CPR_SHRAM1_RET2N_MAN_VAL_POS       (24U)
#define CPR_SHRAM1_RET2N_MAN_VAL_MSK       (0x3UL << CPR_SHRAM1_RET2N_MAN_VAL_POS) /*!< */
#define CPR_SHRAM1_RET2N_MAN_VAL           CPR_SHRAM1_RET2N_MAN_VAL_MSK
#define CPR_SHRAM1_RET2N_MAN_VAL_W(X)      ((X) << CPR_SHRAM1_RET2N_MAN_VAL_POS)

//PD_RAM_CTRL_3 offsetaddress : 0x10c
//PD_RAM_CTRL_3 RegResetValue : 0x0
#define CPR_CPU0_ILM_PGEN_MAN_VAL_POS     (0U)
#define CPR_CPU0_ILM_PGEN_MAN_VAL_MSK     (0x7UL << CPR_CPU0_ILM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ILM_PGEN_MAN_VAL         CPR_CPU0_ILM_PGEN_MAN_VAL_MSK
#define CPR_CPU0_ILM_PGEN_MAN_VAL_W(X)    ((X) << CPR_CPU0_ILM_PGEN_MAN_VAL_POS)
#define CPR_CPU0_ICACHE_PGEN_MAN_VAL_POS  (3U)
#define CPR_CPU0_ICACHE_PGEN_MAN_VAL_MSK  (0x3UL << CPR_CPU0_ICACHE_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU0_ICACHE_PGEN_MAN_VAL      CPR_CPU0_ICACHE_PGEN_MAN_VAL_MSK
#define CPR_CPU0_ICACHE_PGEN_MAN_VAL_W(X) ((X) << CPR_CPU0_ICACHE_PGEN_MAN_VAL_POS)
#define CPR_CPU0_DCACHE_PGEN_MAN_VAL_POS  (5U)
#define CPR_CPU0_DCACHE_PGEN_MAN_VAL_MSK  (0x1UL << CPR_CPU0_DCACHE_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU0_DCACHE_PGEN_MAN_VAL      CPR_CPU0_DCACHE_PGEN_MAN_VAL_MSK
#define CPR_CPU0_DCACHE_PGEN_MAN_VAL_W(X) ((X) << CPR_CPU0_DCACHE_PGEN_MAN_VAL_POS)
#define CPR_CPU0_BTB_PGEN_MAN_VAL_POS     (6U)
#define CPR_CPU0_BTB_PGEN_MAN_VAL_MSK     (0x1UL << CPR_CPU0_BTB_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU0_BTB_PGEN_MAN_VAL         CPR_CPU0_BTB_PGEN_MAN_VAL_MSK
#define CPR_CPU0_BTB_PGEN_MAN_VAL_W(X)    ((X) << CPR_CPU0_BTB_PGEN_MAN_VAL_POS)
#define CPR_UART_RAM_PGEN_MAN_VAL_POS     (7U)
#define CPR_UART_RAM_PGEN_MAN_VAL_MSK     (0x1UL << CPR_UART_RAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_UART_RAM_PGEN_MAN_VAL         CPR_UART_RAM_PGEN_MAN_VAL_MSK
#define CPR_UART_RAM_PGEN_MAN_VAL_W(X)    ((X) << CPR_UART_RAM_PGEN_MAN_VAL_POS)
#define CPR_BTMDM_RAM_PGEN_MAN_VAL_POS    (8U)
#define CPR_BTMDM_RAM_PGEN_MAN_VAL_MSK    (0x1UL << CPR_BTMDM_RAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_BTMDM_RAM_PGEN_MAN_VAL        CPR_BTMDM_RAM_PGEN_MAN_VAL_MSK
#define CPR_BTMDM_RAM_PGEN_MAN_VAL_W(X)   ((X) << CPR_BTMDM_RAM_PGEN_MAN_VAL_POS)
#define CPR_USB_RAM_PGEN_MAN_VAL_POS      (9U)
#define CPR_USB_RAM_PGEN_MAN_VAL_MSK      (0x1UL << CPR_USB_RAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_USB_RAM_PGEN_MAN_VAL          CPR_USB_RAM_PGEN_MAN_VAL_MSK
#define CPR_USB_RAM_PGEN_MAN_VAL_W(X)     ((X) << CPR_USB_RAM_PGEN_MAN_VAL_POS)
#define CPR_USB1_RAM_PGEN_MAN_VAL_POS     (10U)
#define CPR_USB1_RAM_PGEN_MAN_VAL_MSK     (0x1UL << CPR_USB1_RAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_USB1_RAM_PGEN_MAN_VAL         CPR_USB1_RAM_PGEN_MAN_VAL_MSK
#define CPR_USB1_RAM_PGEN_MAN_VAL_W(X)    ((X) << CPR_USB1_RAM_PGEN_MAN_VAL_POS)
#define CPR_RESAMPLE_PGEN_MAN_VAL_POS     (11U)
#define CPR_RESAMPLE_PGEN_MAN_VAL_MSK     (0x3UL << CPR_RESAMPLE_PGEN_MAN_VAL_POS) /*!< */
#define CPR_RESAMPLE_PGEN_MAN_VAL         CPR_RESAMPLE_PGEN_MAN_VAL_MSK
#define CPR_RESAMPLE_PGEN_MAN_VAL_W(X)    ((X) << CPR_RESAMPLE_PGEN_MAN_VAL_POS)
#define CPR_CPU1_ILM_PGEN_MAN_VAL_POS     (13U)
#define CPR_CPU1_ILM_PGEN_MAN_VAL_MSK     (0x1ffUL << CPR_CPU1_ILM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU1_ILM_PGEN_MAN_VAL         CPR_CPU1_ILM_PGEN_MAN_VAL_MSK
#define CPR_CPU1_ILM_PGEN_MAN_VAL_W(X)    ((X) << CPR_CPU1_ILM_PGEN_MAN_VAL_POS)
#define CPR_CPU1_DLM_PGEN_MAN_VAL_POS     (22U)
#define CPR_CPU1_DLM_PGEN_MAN_VAL_MSK     (0x3UL << CPR_CPU1_DLM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU1_DLM_PGEN_MAN_VAL         CPR_CPU1_DLM_PGEN_MAN_VAL_MSK
#define CPR_CPU1_DLM_PGEN_MAN_VAL_W(X)    ((X) << CPR_CPU1_DLM_PGEN_MAN_VAL_POS)
#define CPR_SHRAM1_PGEN_MAN_VAL_POS       (24U)
#define CPR_SHRAM1_PGEN_MAN_VAL_MSK       (0x3UL << CPR_SHRAM1_PGEN_MAN_VAL_POS) /*!< */
#define CPR_SHRAM1_PGEN_MAN_VAL           CPR_SHRAM1_PGEN_MAN_VAL_MSK
#define CPR_SHRAM1_PGEN_MAN_VAL_W(X)      ((X) << CPR_SHRAM1_PGEN_MAN_VAL_POS)

//PD_RAM_CTRL_4 offsetaddress : 0x110
//PD_RAM_CTRL_4 RegResetValue : 0x0
#define CPR_CPU2_IRAM_LP_MAN_EN_POS      (0U)
#define CPR_CPU2_IRAM_LP_MAN_EN_MSK      (0xffUL << CPR_CPU2_IRAM_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_IRAM_LP_MAN_EN          CPR_CPU2_IRAM_LP_MAN_EN_MSK
#define CPR_CPU2_IRAM_LP_MAN_EN_W(X)     ((X) << CPR_CPU2_IRAM_LP_MAN_EN_POS)
#define CPR_CPU2_DRAM_LP_MAN_EN_POS      (8U)
#define CPR_CPU2_DRAM_LP_MAN_EN_MSK      (0xfffUL << CPR_CPU2_DRAM_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_DRAM_LP_MAN_EN          CPR_CPU2_DRAM_LP_MAN_EN_MSK
#define CPR_CPU2_DRAM_LP_MAN_EN_W(X)     ((X) << CPR_CPU2_DRAM_LP_MAN_EN_POS)
#define CPR_CPU2_ICACHE_LP_MAN_EN_POS    (20U)
#define CPR_CPU2_ICACHE_LP_MAN_EN_MSK    (0xfUL << CPR_CPU2_ICACHE_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_ICACHE_LP_MAN_EN        CPR_CPU2_ICACHE_LP_MAN_EN_MSK
#define CPR_CPU2_ICACHE_LP_MAN_EN_W(X)   ((X) << CPR_CPU2_ICACHE_LP_MAN_EN_POS)
#define CPR_CPU2_ITAG_LP_MAN_EN_POS      (24U)
#define CPR_CPU2_ITAG_LP_MAN_EN_MSK      (0x1UL << CPR_CPU2_ITAG_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_ITAG_LP_MAN_EN          CPR_CPU2_ITAG_LP_MAN_EN_MSK
#define CPR_CPU2_ITAG_LP_MAN_EN_W(X)     ((X) << CPR_CPU2_ITAG_LP_MAN_EN_POS)
#define CPR_CPU2_DCACHE_LP_MAN_EN_POS    (25U)
#define CPR_CPU2_DCACHE_LP_MAN_EN_MSK    (0xfUL << CPR_CPU2_DCACHE_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_DCACHE_LP_MAN_EN        CPR_CPU2_DCACHE_LP_MAN_EN_MSK
#define CPR_CPU2_DCACHE_LP_MAN_EN_W(X)   ((X) << CPR_CPU2_DCACHE_LP_MAN_EN_POS)
#define CPR_CPU2_DTAG_LP_MAN_EN_POS      (29U)
#define CPR_CPU2_DTAG_LP_MAN_EN_MSK      (0x1UL << CPR_CPU2_DTAG_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_DTAG_LP_MAN_EN          CPR_CPU2_DTAG_LP_MAN_EN_MSK
#define CPR_CPU2_DTAG_LP_MAN_EN_W(X)     ((X) << CPR_CPU2_DTAG_LP_MAN_EN_POS)
#define CPR_CPU2_PREFETCH_LP_MAN_EN_POS  (30U)
#define CPR_CPU2_PREFETCH_LP_MAN_EN_MSK  (0x1UL << CPR_CPU2_PREFETCH_LP_MAN_EN_POS) /*!< */
#define CPR_CPU2_PREFETCH_LP_MAN_EN      CPR_CPU2_PREFETCH_LP_MAN_EN_MSK
#define CPR_CPU2_PREFETCH_LP_MAN_EN_W(X) ((X) << CPR_CPU2_PREFETCH_LP_MAN_EN_POS)

//PD_RAM_CTRL_5 offsetaddress : 0x114
//PD_RAM_CTRL_5 RegResetValue : 0x7fffffff
#define CPR_CPU2_IRAM_RET1N_MAN_VAL_POS      (0U)
#define CPR_CPU2_IRAM_RET1N_MAN_VAL_MSK      (0xffUL << CPR_CPU2_IRAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_IRAM_RET1N_MAN_VAL          CPR_CPU2_IRAM_RET1N_MAN_VAL_MSK
#define CPR_CPU2_IRAM_RET1N_MAN_VAL_W(X)     ((X) << CPR_CPU2_IRAM_RET1N_MAN_VAL_POS)
#define CPR_CPU2_DRAM_RET1N_MAN_VAL_POS      (8U)
#define CPR_CPU2_DRAM_RET1N_MAN_VAL_MSK      (0xfffUL << CPR_CPU2_DRAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DRAM_RET1N_MAN_VAL          CPR_CPU2_DRAM_RET1N_MAN_VAL_MSK
#define CPR_CPU2_DRAM_RET1N_MAN_VAL_W(X)     ((X) << CPR_CPU2_DRAM_RET1N_MAN_VAL_POS)
#define CPR_CPU2_ICACHE_RET1N_MAN_VAL_POS    (20U)
#define CPR_CPU2_ICACHE_RET1N_MAN_VAL_MSK    (0xfUL << CPR_CPU2_ICACHE_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ICACHE_RET1N_MAN_VAL        CPR_CPU2_ICACHE_RET1N_MAN_VAL_MSK
#define CPR_CPU2_ICACHE_RET1N_MAN_VAL_W(X)   ((X) << CPR_CPU2_ICACHE_RET1N_MAN_VAL_POS)
#define CPR_CPU2_ITAG_RET1N_MAN_VAL_POS      (24U)
#define CPR_CPU2_ITAG_RET1N_MAN_VAL_MSK      (0x1UL << CPR_CPU2_ITAG_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ITAG_RET1N_MAN_VAL          CPR_CPU2_ITAG_RET1N_MAN_VAL_MSK
#define CPR_CPU2_ITAG_RET1N_MAN_VAL_W(X)     ((X) << CPR_CPU2_ITAG_RET1N_MAN_VAL_POS)
#define CPR_CPU2_DCACHE_RET1N_MAN_VAL_POS    (25U)
#define CPR_CPU2_DCACHE_RET1N_MAN_VAL_MSK    (0xfUL << CPR_CPU2_DCACHE_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DCACHE_RET1N_MAN_VAL        CPR_CPU2_DCACHE_RET1N_MAN_VAL_MSK
#define CPR_CPU2_DCACHE_RET1N_MAN_VAL_W(X)   ((X) << CPR_CPU2_DCACHE_RET1N_MAN_VAL_POS)
#define CPR_CPU2_DTAG_RET1N_MAN_VAL_POS      (29U)
#define CPR_CPU2_DTAG_RET1N_MAN_VAL_MSK      (0x1UL << CPR_CPU2_DTAG_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DTAG_RET1N_MAN_VAL          CPR_CPU2_DTAG_RET1N_MAN_VAL_MSK
#define CPR_CPU2_DTAG_RET1N_MAN_VAL_W(X)     ((X) << CPR_CPU2_DTAG_RET1N_MAN_VAL_POS)
#define CPR_CPU2_PREFETCH_RET1N_MAN_VAL_POS  (30U)
#define CPR_CPU2_PREFETCH_RET1N_MAN_VAL_MSK  (0x1UL << CPR_CPU2_PREFETCH_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_PREFETCH_RET1N_MAN_VAL      CPR_CPU2_PREFETCH_RET1N_MAN_VAL_MSK
#define CPR_CPU2_PREFETCH_RET1N_MAN_VAL_W(X) ((X) << CPR_CPU2_PREFETCH_RET1N_MAN_VAL_POS)

//PD_RAM_CTRL_6 offsetaddress : 0x118
//PD_RAM_CTRL_6 RegResetValue : 0x7fffffff
#define CPR_CPU2_IRAM_RET2N_MAN_VAL_POS      (0U)
#define CPR_CPU2_IRAM_RET2N_MAN_VAL_MSK      (0xffUL << CPR_CPU2_IRAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_IRAM_RET2N_MAN_VAL          CPR_CPU2_IRAM_RET2N_MAN_VAL_MSK
#define CPR_CPU2_IRAM_RET2N_MAN_VAL_W(X)     ((X) << CPR_CPU2_IRAM_RET2N_MAN_VAL_POS)
#define CPR_CPU2_DRAM_RET2N_MAN_VAL_POS      (8U)
#define CPR_CPU2_DRAM_RET2N_MAN_VAL_MSK      (0xfffUL << CPR_CPU2_DRAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DRAM_RET2N_MAN_VAL          CPR_CPU2_DRAM_RET2N_MAN_VAL_MSK
#define CPR_CPU2_DRAM_RET2N_MAN_VAL_W(X)     ((X) << CPR_CPU2_DRAM_RET2N_MAN_VAL_POS)
#define CPR_CPU2_ICACHE_RET2N_MAN_VAL_POS    (20U)
#define CPR_CPU2_ICACHE_RET2N_MAN_VAL_MSK    (0xfUL << CPR_CPU2_ICACHE_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ICACHE_RET2N_MAN_VAL        CPR_CPU2_ICACHE_RET2N_MAN_VAL_MSK
#define CPR_CPU2_ICACHE_RET2N_MAN_VAL_W(X)   ((X) << CPR_CPU2_ICACHE_RET2N_MAN_VAL_POS)
#define CPR_CPU2_ITAG_RET2N_MAN_VAL_POS      (24U)
#define CPR_CPU2_ITAG_RET2N_MAN_VAL_MSK      (0x1UL << CPR_CPU2_ITAG_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ITAG_RET2N_MAN_VAL          CPR_CPU2_ITAG_RET2N_MAN_VAL_MSK
#define CPR_CPU2_ITAG_RET2N_MAN_VAL_W(X)     ((X) << CPR_CPU2_ITAG_RET2N_MAN_VAL_POS)
#define CPR_CPU2_DCACHE_RET2N_MAN_VAL_POS    (25U)
#define CPR_CPU2_DCACHE_RET2N_MAN_VAL_MSK    (0xfUL << CPR_CPU2_DCACHE_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DCACHE_RET2N_MAN_VAL        CPR_CPU2_DCACHE_RET2N_MAN_VAL_MSK
#define CPR_CPU2_DCACHE_RET2N_MAN_VAL_W(X)   ((X) << CPR_CPU2_DCACHE_RET2N_MAN_VAL_POS)
#define CPR_CPU2_DTAG_RET2N_MAN_VAL_POS      (29U)
#define CPR_CPU2_DTAG_RET2N_MAN_VAL_MSK      (0x1UL << CPR_CPU2_DTAG_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DTAG_RET2N_MAN_VAL          CPR_CPU2_DTAG_RET2N_MAN_VAL_MSK
#define CPR_CPU2_DTAG_RET2N_MAN_VAL_W(X)     ((X) << CPR_CPU2_DTAG_RET2N_MAN_VAL_POS)
#define CPR_CPU2_PREFETCH_RET2N_MAN_VAL_POS  (30U)
#define CPR_CPU2_PREFETCH_RET2N_MAN_VAL_MSK  (0x1UL << CPR_CPU2_PREFETCH_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CPU2_PREFETCH_RET2N_MAN_VAL      CPR_CPU2_PREFETCH_RET2N_MAN_VAL_MSK
#define CPR_CPU2_PREFETCH_RET2N_MAN_VAL_W(X) ((X) << CPR_CPU2_PREFETCH_RET2N_MAN_VAL_POS)

//PD_RAM_CTRL_7 offsetaddress : 0x11c
//PD_RAM_CTRL_7 RegResetValue : 0x7fffffff
#define CPR_CPU2_IRAM_PGEN_MAN_VAL_POS      (0U)
#define CPR_CPU2_IRAM_PGEN_MAN_VAL_MSK      (0xffUL << CPR_CPU2_IRAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_IRAM_PGEN_MAN_VAL          CPR_CPU2_IRAM_PGEN_MAN_VAL_MSK
#define CPR_CPU2_IRAM_PGEN_MAN_VAL_W(X)     ((X) << CPR_CPU2_IRAM_PGEN_MAN_VAL_POS)
#define CPR_CPU2_DRAM_PGEN_MAN_VAL_POS      (8U)
#define CPR_CPU2_DRAM_PGEN_MAN_VAL_MSK      (0xfffUL << CPR_CPU2_DRAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DRAM_PGEN_MAN_VAL          CPR_CPU2_DRAM_PGEN_MAN_VAL_MSK
#define CPR_CPU2_DRAM_PGEN_MAN_VAL_W(X)     ((X) << CPR_CPU2_DRAM_PGEN_MAN_VAL_POS)
#define CPR_CPU2_ICACHE_PGEN_MAN_VAL_POS    (20U)
#define CPR_CPU2_ICACHE_PGEN_MAN_VAL_MSK    (0xfUL << CPR_CPU2_ICACHE_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ICACHE_PGEN_MAN_VAL        CPR_CPU2_ICACHE_PGEN_MAN_VAL_MSK
#define CPR_CPU2_ICACHE_PGEN_MAN_VAL_W(X)   ((X) << CPR_CPU2_ICACHE_PGEN_MAN_VAL_POS)
#define CPR_CPU2_ITAG_PGEN_MAN_VAL_POS      (24U)
#define CPR_CPU2_ITAG_PGEN_MAN_VAL_MSK      (0x1UL << CPR_CPU2_ITAG_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_ITAG_PGEN_MAN_VAL          CPR_CPU2_ITAG_PGEN_MAN_VAL_MSK
#define CPR_CPU2_ITAG_PGEN_MAN_VAL_W(X)     ((X) << CPR_CPU2_ITAG_PGEN_MAN_VAL_POS)
#define CPR_CPU2_DCACHE_PGEN_MAN_VAL_POS    (25U)
#define CPR_CPU2_DCACHE_PGEN_MAN_VAL_MSK    (0xfUL << CPR_CPU2_DCACHE_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DCACHE_PGEN_MAN_VAL        CPR_CPU2_DCACHE_PGEN_MAN_VAL_MSK
#define CPR_CPU2_DCACHE_PGEN_MAN_VAL_W(X)   ((X) << CPR_CPU2_DCACHE_PGEN_MAN_VAL_POS)
#define CPR_CPU2_DTAG_PGEN_MAN_VAL_POS      (29U)
#define CPR_CPU2_DTAG_PGEN_MAN_VAL_MSK      (0x1UL << CPR_CPU2_DTAG_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_DTAG_PGEN_MAN_VAL          CPR_CPU2_DTAG_PGEN_MAN_VAL_MSK
#define CPR_CPU2_DTAG_PGEN_MAN_VAL_W(X)     ((X) << CPR_CPU2_DTAG_PGEN_MAN_VAL_POS)
#define CPR_CPU2_PREFETCH_PGEN_MAN_VAL_POS  (30U)
#define CPR_CPU2_PREFETCH_PGEN_MAN_VAL_MSK  (0x1UL << CPR_CPU2_PREFETCH_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_PREFETCH_PGEN_MAN_VAL      CPR_CPU2_PREFETCH_PGEN_MAN_VAL_MSK
#define CPR_CPU2_PREFETCH_PGEN_MAN_VAL_W(X) ((X) << CPR_CPU2_PREFETCH_PGEN_MAN_VAL_POS)

//PD_RAM_CTRL_8 offsetaddress : 0x120
//PD_RAM_CTRL_8 RegResetValue : 0x3f3f3f
#define CPR_CODEC_RAM_PGEN_MAN_VAL_POS   (0U)
#define CPR_CODEC_RAM_PGEN_MAN_VAL_MSK   (0x3fUL << CPR_CODEC_RAM_PGEN_MAN_VAL_POS) /*!< */
#define CPR_CODEC_RAM_PGEN_MAN_VAL       CPR_CODEC_RAM_PGEN_MAN_VAL_MSK
#define CPR_CODEC_RAM_PGEN_MAN_VAL_W(X)  ((X) << CPR_CODEC_RAM_PGEN_MAN_VAL_POS)
#define CPR_CODEC_RAM_RET2N_MAN_VAL_POS  (8U)
#define CPR_CODEC_RAM_RET2N_MAN_VAL_MSK  (0x3fUL << CPR_CODEC_RAM_RET2N_MAN_VAL_POS) /*!< */
#define CPR_CODEC_RAM_RET2N_MAN_VAL      CPR_CODEC_RAM_RET2N_MAN_VAL_MSK
#define CPR_CODEC_RAM_RET2N_MAN_VAL_W(X) ((X) << CPR_CODEC_RAM_RET2N_MAN_VAL_POS)
#define CPR_CODEC_RAM_RET1N_MAN_VAL_POS  (16U)
#define CPR_CODEC_RAM_RET1N_MAN_VAL_MSK  (0x3fUL << CPR_CODEC_RAM_RET1N_MAN_VAL_POS) /*!< */
#define CPR_CODEC_RAM_RET1N_MAN_VAL      CPR_CODEC_RAM_RET1N_MAN_VAL_MSK
#define CPR_CODEC_RAM_RET1N_MAN_VAL_W(X) ((X) << CPR_CODEC_RAM_RET1N_MAN_VAL_POS)
#define CPR_CODEC_RAM_LP_MAN_EN_POS      (24U)
#define CPR_CODEC_RAM_LP_MAN_EN_MSK      (0x3fUL << CPR_CODEC_RAM_LP_MAN_EN_POS) /*!< */
#define CPR_CODEC_RAM_LP_MAN_EN          CPR_CODEC_RAM_LP_MAN_EN_MSK
#define CPR_CODEC_RAM_LP_MAN_EN_W(X)     ((X) << CPR_CODEC_RAM_LP_MAN_EN_POS)

//PD_RAM_CTRL_9 offsetaddress : 0x124
//PD_RAM_CTRL_9 RegResetValue : 0x0
#define CPR_CPU0_RAM_LP_MODE_POS       (0U)
#define CPR_CPU0_RAM_LP_MODE_MSK       (0x1UL << CPR_CPU0_RAM_LP_MODE_POS) /*!< */
#define CPR_CPU0_RAM_LP_MODE           CPR_CPU0_RAM_LP_MODE_MSK
#define CPR_CPU0_RAM_LP_MODE_W(X)      ((X) << CPR_CPU0_RAM_LP_MODE_POS)
#define CPR_CPU0_RAM_RET_MODE_POS      (1U)
#define CPR_CPU0_RAM_RET_MODE_MSK      (0x1UL << CPR_CPU0_RAM_RET_MODE_POS) /*!< */
#define CPR_CPU0_RAM_RET_MODE          CPR_CPU0_RAM_RET_MODE_MSK
#define CPR_CPU0_RAM_RET_MODE_W(X)     ((X) << CPR_CPU0_RAM_RET_MODE_POS)
#define CPR_UART_RAM_LP_MODE_POS       (2U)
#define CPR_UART_RAM_LP_MODE_MSK       (0x1UL << CPR_UART_RAM_LP_MODE_POS) /*!< */
#define CPR_UART_RAM_LP_MODE           CPR_UART_RAM_LP_MODE_MSK
#define CPR_UART_RAM_LP_MODE_W(X)      ((X) << CPR_UART_RAM_LP_MODE_POS)
#define CPR_UART_RAM_RET_MODE_POS      (3U)
#define CPR_UART_RAM_RET_MODE_MSK      (0x1UL << CPR_UART_RAM_RET_MODE_POS) /*!< */
#define CPR_UART_RAM_RET_MODE          CPR_UART_RAM_RET_MODE_MSK
#define CPR_UART_RAM_RET_MODE_W(X)     ((X) << CPR_UART_RAM_RET_MODE_POS)
#define CPR_USB_RAM_LP_MODE_POS        (4U)
#define CPR_USB_RAM_LP_MODE_MSK        (0x1UL << CPR_USB_RAM_LP_MODE_POS) /*!< */
#define CPR_USB_RAM_LP_MODE            CPR_USB_RAM_LP_MODE_MSK
#define CPR_USB_RAM_LP_MODE_W(X)       ((X) << CPR_USB_RAM_LP_MODE_POS)
#define CPR_USB_RAM_RET_MODE_POS       (5U)
#define CPR_USB_RAM_RET_MODE_MSK       (0x1UL << CPR_USB_RAM_RET_MODE_POS) /*!< */
#define CPR_USB_RAM_RET_MODE           CPR_USB_RAM_RET_MODE_MSK
#define CPR_USB_RAM_RET_MODE_W(X)      ((X) << CPR_USB_RAM_RET_MODE_POS)
#define CPR_RESAMPLE_RAM_LP_MODE_POS   (6U)
#define CPR_RESAMPLE_RAM_LP_MODE_MSK   (0x1UL << CPR_RESAMPLE_RAM_LP_MODE_POS) /*!< */
#define CPR_RESAMPLE_RAM_LP_MODE       CPR_RESAMPLE_RAM_LP_MODE_MSK
#define CPR_RESAMPLE_RAM_LP_MODE_W(X)  ((X) << CPR_RESAMPLE_RAM_LP_MODE_POS)
#define CPR_RESAMPLE_RAM_RET_MODE_POS  (7U)
#define CPR_RESAMPLE_RAM_RET_MODE_MSK  (0x1UL << CPR_RESAMPLE_RAM_RET_MODE_POS) /*!< */
#define CPR_RESAMPLE_RAM_RET_MODE      CPR_RESAMPLE_RAM_RET_MODE_MSK
#define CPR_RESAMPLE_RAM_RET_MODE_W(X) ((X) << CPR_RESAMPLE_RAM_RET_MODE_POS)
#define CPR_CPU1_ILM_LP_MODE_POS       (8U)
#define CPR_CPU1_ILM_LP_MODE_MSK       (0x1UL << CPR_CPU1_ILM_LP_MODE_POS) /*!< */
#define CPR_CPU1_ILM_LP_MODE           CPR_CPU1_ILM_LP_MODE_MSK
#define CPR_CPU1_ILM_LP_MODE_W(X)      ((X) << CPR_CPU1_ILM_LP_MODE_POS)
#define CPR_CPU1_ILM_RET_MODE_POS      (9U)
#define CPR_CPU1_ILM_RET_MODE_MSK      (0x1UL << CPR_CPU1_ILM_RET_MODE_POS) /*!< */
#define CPR_CPU1_ILM_RET_MODE          CPR_CPU1_ILM_RET_MODE_MSK
#define CPR_CPU1_ILM_RET_MODE_W(X)     ((X) << CPR_CPU1_ILM_RET_MODE_POS)
#define CPR_CPU1_DLM_LP_MODE_POS       (10U)
#define CPR_CPU1_DLM_LP_MODE_MSK       (0x1UL << CPR_CPU1_DLM_LP_MODE_POS) /*!< */
#define CPR_CPU1_DLM_LP_MODE           CPR_CPU1_DLM_LP_MODE_MSK
#define CPR_CPU1_DLM_LP_MODE_W(X)      ((X) << CPR_CPU1_DLM_LP_MODE_POS)
#define CPR_CPU1_DLM_RET_MODE_POS      (11U)
#define CPR_CPU1_DLM_RET_MODE_MSK      (0x1UL << CPR_CPU1_DLM_RET_MODE_POS) /*!< */
#define CPR_CPU1_DLM_RET_MODE          CPR_CPU1_DLM_RET_MODE_MSK
#define CPR_CPU1_DLM_RET_MODE_W(X)     ((X) << CPR_CPU1_DLM_RET_MODE_POS)
#define CPR_SHRAM1_LP_MODE_POS         (12U)
#define CPR_SHRAM1_LP_MODE_MSK         (0x1UL << CPR_SHRAM1_LP_MODE_POS) /*!< */
#define CPR_SHRAM1_LP_MODE             CPR_SHRAM1_LP_MODE_MSK
#define CPR_SHRAM1_LP_MODE_W(X)        ((X) << CPR_SHRAM1_LP_MODE_POS)
#define CPR_SHRAM1_RET_MODE_POS        (13U)
#define CPR_SHRAM1_RET_MODE_MSK        (0x1UL << CPR_SHRAM1_RET_MODE_POS) /*!< */
#define CPR_SHRAM1_RET_MODE            CPR_SHRAM1_RET_MODE_MSK
#define CPR_SHRAM1_RET_MODE_W(X)       ((X) << CPR_SHRAM1_RET_MODE_POS)
#define CPR_CPU2_RAM_LP_MODE_POS       (14U)
#define CPR_CPU2_RAM_LP_MODE_MSK       (0x1UL << CPR_CPU2_RAM_LP_MODE_POS) /*!< */
#define CPR_CPU2_RAM_LP_MODE           CPR_CPU2_RAM_LP_MODE_MSK
#define CPR_CPU2_RAM_LP_MODE_W(X)      ((X) << CPR_CPU2_RAM_LP_MODE_POS)
#define CPR_CPU2_RAM_RET_MODE_POS      (15U)
#define CPR_CPU2_RAM_RET_MODE_MSK      (0x1UL << CPR_CPU2_RAM_RET_MODE_POS) /*!< */
#define CPR_CPU2_RAM_RET_MODE          CPR_CPU2_RAM_RET_MODE_MSK
#define CPR_CPU2_RAM_RET_MODE_W(X)     ((X) << CPR_CPU2_RAM_RET_MODE_POS)
#define CPR_CODEC_RAM_LP_MODE_POS      (16U)
#define CPR_CODEC_RAM_LP_MODE_MSK      (0x1UL << CPR_CODEC_RAM_LP_MODE_POS) /*!< */
#define CPR_CODEC_RAM_LP_MODE          CPR_CODEC_RAM_LP_MODE_MSK
#define CPR_CODEC_RAM_LP_MODE_W(X)     ((X) << CPR_CODEC_RAM_LP_MODE_POS)
#define CPR_CODEC_RAM_RET_MODE_POS     (17U)
#define CPR_CODEC_RAM_RET_MODE_MSK     (0x1UL << CPR_CODEC_RAM_RET_MODE_POS) /*!< */
#define CPR_CODEC_RAM_RET_MODE         CPR_CODEC_RAM_RET_MODE_MSK
#define CPR_CODEC_RAM_RET_MODE_W(X)    ((X) << CPR_CODEC_RAM_RET_MODE_POS)

//PD_RAM_CTRL_10 offsetaddress : 0x128
//PD_RAM_CTRL_10 RegResetValue : 0x0
#define CPR_CPU0_RAM_CEN_MAN_EN_POS       (0U)
#define CPR_CPU0_RAM_CEN_MAN_EN_MSK       (0x1UL << CPR_CPU0_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_CPU0_RAM_CEN_MAN_EN           CPR_CPU0_RAM_CEN_MAN_EN_MSK
#define CPR_CPU0_RAM_CEN_MAN_EN_W(X)      ((X) << CPR_CPU0_RAM_CEN_MAN_EN_POS)
#define CPR_UART_RAM_CEN_MAN_EN_POS       (1U)
#define CPR_UART_RAM_CEN_MAN_EN_MSK       (0x1UL << CPR_UART_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_UART_RAM_CEN_MAN_EN           CPR_UART_RAM_CEN_MAN_EN_MSK
#define CPR_UART_RAM_CEN_MAN_EN_W(X)      ((X) << CPR_UART_RAM_CEN_MAN_EN_POS)
#define CPR_USB_RAM_CEN_MAN_EN_POS        (2U)
#define CPR_USB_RAM_CEN_MAN_EN_MSK        (0x1UL << CPR_USB_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_USB_RAM_CEN_MAN_EN            CPR_USB_RAM_CEN_MAN_EN_MSK
#define CPR_USB_RAM_CEN_MAN_EN_W(X)       ((X) << CPR_USB_RAM_CEN_MAN_EN_POS)
#define CPR_USB1_RAM_CEN_MAN_EN_POS       (3U)
#define CPR_USB1_RAM_CEN_MAN_EN_MSK       (0x1UL << CPR_USB1_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_USB1_RAM_CEN_MAN_EN           CPR_USB1_RAM_CEN_MAN_EN_MSK
#define CPR_USB1_RAM_CEN_MAN_EN_W(X)      ((X) << CPR_USB1_RAM_CEN_MAN_EN_POS)
#define CPR_RESAMPLE_RAM_CEN_MAN_EN_POS   (4U)
#define CPR_RESAMPLE_RAM_CEN_MAN_EN_MSK   (0x1UL << CPR_RESAMPLE_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_RESAMPLE_RAM_CEN_MAN_EN       CPR_RESAMPLE_RAM_CEN_MAN_EN_MSK
#define CPR_RESAMPLE_RAM_CEN_MAN_EN_W(X)  ((X) << CPR_RESAMPLE_RAM_CEN_MAN_EN_POS)
#define CPR_CPU1_RAM_CEN_MAN_EN_POS       (5U)
#define CPR_CPU1_RAM_CEN_MAN_EN_MSK       (0x1UL << CPR_CPU1_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_CPU1_RAM_CEN_MAN_EN           CPR_CPU1_RAM_CEN_MAN_EN_MSK
#define CPR_CPU1_RAM_CEN_MAN_EN_W(X)      ((X) << CPR_CPU1_RAM_CEN_MAN_EN_POS)
#define CPR_SHRAM1_CEN_MAN_EN_POS         (6U)
#define CPR_SHRAM1_CEN_MAN_EN_MSK         (0x1UL << CPR_SHRAM1_CEN_MAN_EN_POS) /*!< */
#define CPR_SHRAM1_CEN_MAN_EN             CPR_SHRAM1_CEN_MAN_EN_MSK
#define CPR_SHRAM1_CEN_MAN_EN_W(X)        ((X) << CPR_SHRAM1_CEN_MAN_EN_POS)
#define CPR_BTEM_CEN_MAN_EN_POS           (7U)
#define CPR_BTEM_CEN_MAN_EN_MSK           (0x1UL << CPR_BTEM_CEN_MAN_EN_POS) /*!< */
#define CPR_BTEM_CEN_MAN_EN               CPR_BTEM_CEN_MAN_EN_MSK
#define CPR_BTEM_CEN_MAN_EN_W(X)          ((X) << CPR_BTEM_CEN_MAN_EN_POS)
#define CPR_BTMDM_RAM_CEN_MAN_EN_POS      (8U)
#define CPR_BTMDM_RAM_CEN_MAN_EN_MSK      (0x1UL << CPR_BTMDM_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_BTMDM_RAM_CEN_MAN_EN          CPR_BTMDM_RAM_CEN_MAN_EN_MSK
#define CPR_BTMDM_RAM_CEN_MAN_EN_W(X)     ((X) << CPR_BTMDM_RAM_CEN_MAN_EN_POS)
#define CPR_CPU2_RAM_CEN_MAN_EN_POS       (9U)
#define CPR_CPU2_RAM_CEN_MAN_EN_MSK       (0x1UL << CPR_CPU2_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_CPU2_RAM_CEN_MAN_EN           CPR_CPU2_RAM_CEN_MAN_EN_MSK
#define CPR_CPU2_RAM_CEN_MAN_EN_W(X)      ((X) << CPR_CPU2_RAM_CEN_MAN_EN_POS)
#define CPR_CODEC_RAM_CEN_MAN_EN_POS      (10U)
#define CPR_CODEC_RAM_CEN_MAN_EN_MSK      (0x1UL << CPR_CODEC_RAM_CEN_MAN_EN_POS) /*!< */
#define CPR_CODEC_RAM_CEN_MAN_EN          CPR_CODEC_RAM_CEN_MAN_EN_MSK
#define CPR_CODEC_RAM_CEN_MAN_EN_W(X)     ((X) << CPR_CODEC_RAM_CEN_MAN_EN_POS)
#define CPR_CPU0_RAM_CEN_MAN_VAL_POS      (16U)
#define CPR_CPU0_RAM_CEN_MAN_VAL_MSK      (0x1UL << CPR_CPU0_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_CPU0_RAM_CEN_MAN_VAL          CPR_CPU0_RAM_CEN_MAN_VAL_MSK
#define CPR_CPU0_RAM_CEN_MAN_VAL_W(X)     ((X) << CPR_CPU0_RAM_CEN_MAN_VAL_POS)
#define CPR_UART_RAM_CEN_MAN_VAL_POS      (17U)
#define CPR_UART_RAM_CEN_MAN_VAL_MSK      (0x1UL << CPR_UART_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_UART_RAM_CEN_MAN_VAL          CPR_UART_RAM_CEN_MAN_VAL_MSK
#define CPR_UART_RAM_CEN_MAN_VAL_W(X)     ((X) << CPR_UART_RAM_CEN_MAN_VAL_POS)
#define CPR_USB_RAM_CEN_MAN_VAL_POS       (18U)
#define CPR_USB_RAM_CEN_MAN_VAL_MSK       (0x1UL << CPR_USB_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_USB_RAM_CEN_MAN_VAL           CPR_USB_RAM_CEN_MAN_VAL_MSK
#define CPR_USB_RAM_CEN_MAN_VAL_W(X)      ((X) << CPR_USB_RAM_CEN_MAN_VAL_POS)
#define CPR_USB1_RAM_CEN_MAN_VAL_POS      (19U)
#define CPR_USB1_RAM_CEN_MAN_VAL_MSK      (0x1UL << CPR_USB1_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_USB1_RAM_CEN_MAN_VAL          CPR_USB1_RAM_CEN_MAN_VAL_MSK
#define CPR_USB1_RAM_CEN_MAN_VAL_W(X)     ((X) << CPR_USB1_RAM_CEN_MAN_VAL_POS)
#define CPR_RESAMPLE_RAM_CEN_MAN_VAL_POS  (20U)
#define CPR_RESAMPLE_RAM_CEN_MAN_VAL_MSK  (0x1UL << CPR_RESAMPLE_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_RESAMPLE_RAM_CEN_MAN_VAL      CPR_RESAMPLE_RAM_CEN_MAN_VAL_MSK
#define CPR_RESAMPLE_RAM_CEN_MAN_VAL_W(X) ((X) << CPR_RESAMPLE_RAM_CEN_MAN_VAL_POS)
#define CPR_CPU1_RAM_CEN_MAN_VAL_POS      (21U)
#define CPR_CPU1_RAM_CEN_MAN_VAL_MSK      (0x1UL << CPR_CPU1_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_CPU1_RAM_CEN_MAN_VAL          CPR_CPU1_RAM_CEN_MAN_VAL_MSK
#define CPR_CPU1_RAM_CEN_MAN_VAL_W(X)     ((X) << CPR_CPU1_RAM_CEN_MAN_VAL_POS)
#define CPR_SHRAM1_CEN_MAN_VAL_POS        (22U)
#define CPR_SHRAM1_CEN_MAN_VAL_MSK        (0x1UL << CPR_SHRAM1_CEN_MAN_VAL_POS) /*!< */
#define CPR_SHRAM1_CEN_MAN_VAL            CPR_SHRAM1_CEN_MAN_VAL_MSK
#define CPR_SHRAM1_CEN_MAN_VAL_W(X)       ((X) << CPR_SHRAM1_CEN_MAN_VAL_POS)
#define CPR_BTEM_CEN_MAN_VAL_POS          (23U)
#define CPR_BTEM_CEN_MAN_VAL_MSK          (0x1UL << CPR_BTEM_CEN_MAN_VAL_POS) /*!< */
#define CPR_BTEM_CEN_MAN_VAL              CPR_BTEM_CEN_MAN_VAL_MSK
#define CPR_BTEM_CEN_MAN_VAL_W(X)         ((X) << CPR_BTEM_CEN_MAN_VAL_POS)
#define CPR_BTMDM_RAM_CEN_MAN_VAL_POS     (24U)
#define CPR_BTMDM_RAM_CEN_MAN_VAL_MSK     (0x1UL << CPR_BTMDM_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_BTMDM_RAM_CEN_MAN_VAL         CPR_BTMDM_RAM_CEN_MAN_VAL_MSK
#define CPR_BTMDM_RAM_CEN_MAN_VAL_W(X)    ((X) << CPR_BTMDM_RAM_CEN_MAN_VAL_POS)
#define CPR_CPU2_RAM_CEN_MAN_VAL_POS      (25U)
#define CPR_CPU2_RAM_CEN_MAN_VAL_MSK      (0x1UL << CPR_CPU2_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_CPU2_RAM_CEN_MAN_VAL          CPR_CPU2_RAM_CEN_MAN_VAL_MSK
#define CPR_CPU2_RAM_CEN_MAN_VAL_W(X)     ((X) << CPR_CPU2_RAM_CEN_MAN_VAL_POS)
#define CPR_CODEC_RAM_CEN_MAN_VAL_POS     (26U)
#define CPR_CODEC_RAM_CEN_MAN_VAL_MSK     (0x1UL << CPR_CODEC_RAM_CEN_MAN_VAL_POS) /*!< */
#define CPR_CODEC_RAM_CEN_MAN_VAL         CPR_CODEC_RAM_CEN_MAN_VAL_MSK
#define CPR_CODEC_RAM_CEN_MAN_VAL_W(X)    ((X) << CPR_CODEC_RAM_CEN_MAN_VAL_POS)

//TEMP_CTRL offsetaddress : 0x130
//TEMP_CTRL RegResetValue : 0x0
#define CPR_TEMP_MON_EN_POS              (0U)
#define CPR_TEMP_MON_EN_MSK              (0x1UL << CPR_TEMP_MON_EN_POS) /*!< Charging temperature protection enables, 0: Turn off the temperature protection; 1: Turn on the temperature protection*/
#define CPR_TEMP_MON_EN                  CPR_TEMP_MON_EN_MSK
#define CPR_TEMP_MON_EN_W(X)             ((X) << CPR_TEMP_MON_EN_POS)
#define CPR_TEMP_HC_CTRL_EN_POS          (1U)
#define CPR_TEMP_HC_CTRL_EN_MSK          (0x1UL << CPR_TEMP_HC_CTRL_EN_POS) /*!< Hardware control charging amplitude enable*/
#define CPR_TEMP_HC_CTRL_EN              CPR_TEMP_HC_CTRL_EN_MSK
#define CPR_TEMP_HC_CTRL_EN_W(X)         ((X) << CPR_TEMP_HC_CTRL_EN_POS)
#define CPR_HC_CHG_CV_SEL_HIGH_PROP_POS  (2U)
#define CPR_HC_CHG_CV_SEL_HIGH_PROP_MSK  (0x7UL << CPR_HC_CHG_CV_SEL_HIGH_PROP_POS) /*!< When the temperature is too high, the charging current needs to be reduced.*/
#define CPR_HC_CHG_CV_SEL_HIGH_PROP      CPR_HC_CHG_CV_SEL_HIGH_PROP_MSK
#define CPR_HC_CHG_CV_SEL_HIGH_PROP_W(X) ((X) << CPR_HC_CHG_CV_SEL_HIGH_PROP_POS)
#define CPR_HC_CHG_CC_SEL_HIGH_PROP_POS  (5U)
#define CPR_HC_CHG_CC_SEL_HIGH_PROP_MSK  (0x3fUL << CPR_HC_CHG_CC_SEL_HIGH_PROP_POS) /*!< When the temperature is too high, the charging current needs to be reduced.*/
#define CPR_HC_CHG_CC_SEL_HIGH_PROP      CPR_HC_CHG_CC_SEL_HIGH_PROP_MSK
#define CPR_HC_CHG_CC_SEL_HIGH_PROP_W(X) ((X) << CPR_HC_CHG_CC_SEL_HIGH_PROP_POS)
#define CPR_HC_CHG_CV_SEL_NORM_POS       (11U)
#define CPR_HC_CHG_CV_SEL_NORM_MSK       (0x7UL << CPR_HC_CHG_CV_SEL_NORM_POS) /*!< When the temperature is normal, the output value of chg_cv_sel*/
#define CPR_HC_CHG_CV_SEL_NORM           CPR_HC_CHG_CV_SEL_NORM_MSK
#define CPR_HC_CHG_CV_SEL_NORM_W(X)      ((X) << CPR_HC_CHG_CV_SEL_NORM_POS)
#define CPR_HC_CHG_CC_SEL_NORM_POS       (14U)
#define CPR_HC_CHG_CC_SEL_NORM_MSK       (0x3fUL << CPR_HC_CHG_CC_SEL_NORM_POS) /*!< When the temperature is normal, the output value of chg_cc_sel*/
#define CPR_HC_CHG_CC_SEL_NORM           CPR_HC_CHG_CC_SEL_NORM_MSK
#define CPR_HC_CHG_CC_SEL_NORM_W(X)      ((X) << CPR_HC_CHG_CC_SEL_NORM_POS)
#define CPR_HC_CHG_CV_SEL_LOW_PROP_POS   (20U)
#define CPR_HC_CHG_CV_SEL_LOW_PROP_MSK   (0x7UL << CPR_HC_CHG_CV_SEL_LOW_PROP_POS) /*!< When the temperature is too low, the output value of chg_cv_sel needs to be reduced.*/
#define CPR_HC_CHG_CV_SEL_LOW_PROP       CPR_HC_CHG_CV_SEL_LOW_PROP_MSK
#define CPR_HC_CHG_CV_SEL_LOW_PROP_W(X)  ((X) << CPR_HC_CHG_CV_SEL_LOW_PROP_POS)
#define CPR_HC_CHG_CC_SEL_LOW_PROP_POS   (23U)
#define CPR_HC_CHG_CC_SEL_LOW_PROP_MSK   (0x3fUL << CPR_HC_CHG_CC_SEL_LOW_PROP_POS) /*!< When the temperature is too low, the output value of chg_cc_sel needs to be reduced.*/
#define CPR_HC_CHG_CC_SEL_LOW_PROP       CPR_HC_CHG_CC_SEL_LOW_PROP_MSK
#define CPR_HC_CHG_CC_SEL_LOW_PROP_W(X)  ((X) << CPR_HC_CHG_CC_SEL_LOW_PROP_POS)

//TEMP_TH_0 offsetaddress : 0x134
//TEMP_TH_0 RegResetValue : 0x53
#define CPR_TEMP_TRIG_NUM_POS        (0U)
#define CPR_TEMP_TRIG_NUM_MSK        (0xfUL << CPR_TEMP_TRIG_NUM_POS) /*!< Number of judgments*/
#define CPR_TEMP_TRIG_NUM            CPR_TEMP_TRIG_NUM_MSK
#define CPR_TEMP_TRIG_NUM_W(X)       ((X) << CPR_TEMP_TRIG_NUM_POS)
#define CPR_TEMP_TOTAL_SAMP_NUM_POS  (4U)
#define CPR_TEMP_TOTAL_SAMP_NUM_MSK  (0xfUL << CPR_TEMP_TOTAL_SAMP_NUM_POS) /*!< The sampling length is used in conjunction with temp_trig_num to improve sampling accuracy. For example, if 3 samples in 5 samples are higher than a certain threshold, it is determined that the current temperature is higher than this threshold. Then temp_total_samp_num is configured as 5, and temp_trig_num is configured as 3.*/
#define CPR_TEMP_TOTAL_SAMP_NUM      CPR_TEMP_TOTAL_SAMP_NUM_MSK
#define CPR_TEMP_TOTAL_SAMP_NUM_W(X) ((X) << CPR_TEMP_TOTAL_SAMP_NUM_POS)
#define CPR_TEMP_NORMAL_TH_POS       (8U)
#define CPR_TEMP_NORMAL_TH_MSK       (0x3ffUL << CPR_TEMP_NORMAL_TH_POS) /*!< The temperature is normal threshold. When the temperature is less than or equal to the threshold is greater than temp_low_prop_th, the charging current is normal.*/
#define CPR_TEMP_NORMAL_TH           CPR_TEMP_NORMAL_TH_MSK
#define CPR_TEMP_NORMAL_TH_W(X)      ((X) << CPR_TEMP_NORMAL_TH_POS)

//TEMP_TH_1 offsetaddress : 0x138
//TEMP_TH_1 RegResetValue : 0x0
#define CPR_TEMP_HIGH_PROP_TH_POS  (0U)
#define CPR_TEMP_HIGH_PROP_TH_MSK  (0x3ffUL << CPR_TEMP_HIGH_PROP_TH_POS) /*!< The high temperature reduces the charging current threshold. When the temperature is less than or equal to the threshold, the charging current is reduced; when the temperature is higher than this threshold, the charging current is stopped.*/
#define CPR_TEMP_HIGH_PROP_TH      CPR_TEMP_HIGH_PROP_TH_MSK
#define CPR_TEMP_HIGH_PROP_TH_W(X) ((X) << CPR_TEMP_HIGH_PROP_TH_POS)
#define CPR_TEMP_LOW_PROP_TH_POS   (10U)
#define CPR_TEMP_LOW_PROP_TH_MSK   (0x3ffUL << CPR_TEMP_LOW_PROP_TH_POS) /*!< Low temperature reduces the charging current threshold. When the temperature is less than or equal to the threshold, it reduces the charging current.*/
#define CPR_TEMP_LOW_PROP_TH       CPR_TEMP_LOW_PROP_TH_MSK
#define CPR_TEMP_LOW_PROP_TH_W(X)  ((X) << CPR_TEMP_LOW_PROP_TH_POS)
#define CPR_TEMP_LOW_STOP_TH_POS   (20U)
#define CPR_TEMP_LOW_STOP_TH_MSK   (0x3ffUL << CPR_TEMP_LOW_STOP_TH_POS) /*!< The charging threshold is stopped when the measured sensor value is less than or equal to the threshold.*/
#define CPR_TEMP_LOW_STOP_TH       CPR_TEMP_LOW_STOP_TH_MSK
#define CPR_TEMP_LOW_STOP_TH_W(X)  ((X) << CPR_TEMP_LOW_STOP_TH_POS)

//BBPLL_CFG0 offsetaddress : 0x0140
//BBPLL_CFG0 RegResetValue : 0x4cd0_8888
#define CPR_BBPLL_LPF_R3_POS    (0U)
#define CPR_BBPLL_LPF_R3_MSK    (0xfUL << CPR_BBPLL_LPF_R3_POS) /*!< bbpll lpf R3 control bits*/
#define CPR_BBPLL_LPF_R3        CPR_BBPLL_LPF_R3_MSK
#define CPR_BBPLL_LPF_R3_W(X)   ((X) << CPR_BBPLL_LPF_R3_POS)
#define CPR_BBPLL_LPF_R2_POS    (4U)
#define CPR_BBPLL_LPF_R2_MSK    (0xfUL << CPR_BBPLL_LPF_R2_POS) /*!< bbpll lpf R2 control bits*/
#define CPR_BBPLL_LPF_R2        CPR_BBPLL_LPF_R2_MSK
#define CPR_BBPLL_LPF_R2_W(X)   ((X) << CPR_BBPLL_LPF_R2_POS)
#define CPR_BBPLL_LPF_C3_POS    (8U)
#define CPR_BBPLL_LPF_C3_MSK    (0xfUL << CPR_BBPLL_LPF_C3_POS) /*!< bbpll lpf C3 control bits*/
#define CPR_BBPLL_LPF_C3        CPR_BBPLL_LPF_C3_MSK
#define CPR_BBPLL_LPF_C3_W(X)   ((X) << CPR_BBPLL_LPF_C3_POS)
#define CPR_BBPLL_LPF_C2_POS    (12U)
#define CPR_BBPLL_LPF_C2_MSK    (0xfUL << CPR_BBPLL_LPF_C2_POS) /*!< bbpll lpf C2 control bits*/
#define CPR_BBPLL_LPF_C2        CPR_BBPLL_LPF_C2_MSK
#define CPR_BBPLL_LPF_C2_W(X)   ((X) << CPR_BBPLL_LPF_C2_POS)
#define CPR_BBPLL_IOS_POS       (16U)
#define CPR_BBPLL_IOS_MSK       (0x3UL << CPR_BBPLL_IOS_POS) /*!< bbpll charge pump up/down offset current input control bits,*/
#define CPR_BBPLL_IOS           CPR_BBPLL_IOS_MSK
#define CPR_BBPLL_IOS_W(X)      ((X) << CPR_BBPLL_IOS_POS)
#define CPR_BBPLL_ICP_POS       (18U)
#define CPR_BBPLL_ICP_MSK       (0x7UL << CPR_BBPLL_ICP_POS) /*!< bbpll charge pump current control bits*/
#define CPR_BBPLL_ICP           CPR_BBPLL_ICP_MSK
#define CPR_BBPLL_ICP_W(X)      ((X) << CPR_BBPLL_ICP_POS)
#define CPR_BBPLL_VCO_RES_POS   (21U)
#define CPR_BBPLL_VCO_RES_MSK   (0x3UL << CPR_BBPLL_VCO_RES_POS) /*!< bbpll vco rc filter resistance control bits*/
#define CPR_BBPLL_VCO_RES       CPR_BBPLL_VCO_RES_MSK
#define CPR_BBPLL_VCO_RES_W(X)  ((X) << CPR_BBPLL_VCO_RES_POS)
#define CPR_BBPLL_VCO_IB_POS    (23U)
#define CPR_BBPLL_VCO_IB_MSK    (0x7UL << CPR_BBPLL_VCO_IB_POS) /*!< bbpll vco bias current input control bits*/
#define CPR_BBPLL_VCO_IB        CPR_BBPLL_VCO_IB_MSK
#define CPR_BBPLL_VCO_IB_W(X)   ((X) << CPR_BBPLL_VCO_IB_POS)
#define CPR_BBPLL_VCO_BAND_POS  (26U)
#define CPR_BBPLL_VCO_BAND_MSK  (0x7UL << CPR_BBPLL_VCO_BAND_POS) /*!< bbpll vco freq band control bits*/
#define CPR_BBPLL_VCO_BAND      CPR_BBPLL_VCO_BAND_MSK
#define CPR_BBPLL_VCO_BAND_W(X) ((X) << CPR_BBPLL_VCO_BAND_POS)
#define CPR_BBPLL_VCO_KV_POS    (29U)
#define CPR_BBPLL_VCO_KV_MSK    (0x3UL << CPR_BBPLL_VCO_KV_POS) /*!< bbpll vco gain control bits*/
#define CPR_BBPLL_VCO_KV        CPR_BBPLL_VCO_KV_MSK
#define CPR_BBPLL_VCO_KV_W(X)   ((X) << CPR_BBPLL_VCO_KV_POS)

//BBPLL_CFG1 offsetaddress : 0x0144
//BBPLL_CFG1 RegResetValue : 0x20_11d6
#define CPR_BBPLL_LD_VL_POS            (0U)
#define CPR_BBPLL_LD_VL_MSK            (0x7UL << CPR_BBPLL_LD_VL_POS) /*!< bbpll locked control voltage low limit control bits*/
#define CPR_BBPLL_LD_VL                CPR_BBPLL_LD_VL_MSK
#define CPR_BBPLL_LD_VL_W(X)           ((X) << CPR_BBPLL_LD_VL_POS)
#define CPR_BBPLL_LD_VH_POS            (3U)
#define CPR_BBPLL_LD_VH_MSK            (0x7UL << CPR_BBPLL_LD_VH_POS) /*!< bbpll locked control voltage high limit control bits*/
#define CPR_BBPLL_LD_VH                CPR_BBPLL_LD_VH_MSK
#define CPR_BBPLL_LD_VH_W(X)           ((X) << CPR_BBPLL_LD_VH_POS)
#define CPR_BBPLL_BG_CP_EN_POS         (6U)
#define CPR_BBPLL_BG_CP_EN_MSK         (0x1UL << CPR_BBPLL_BG_CP_EN_POS) /*!< bbpll bandgap 10uA to cp enable control signal, 1: enable, 0: disable*/
#define CPR_BBPLL_BG_CP_EN             CPR_BBPLL_BG_CP_EN_MSK
#define CPR_BBPLL_BG_CP_EN_W(X)        ((X) << CPR_BBPLL_BG_CP_EN_POS)
#define CPR_BBPLL_BG_VCO_EN_POS        (7U)
#define CPR_BBPLL_BG_VCO_EN_MSK        (0x1UL << CPR_BBPLL_BG_VCO_EN_POS) /*!< bbpll bandgap 10uA to vco enable control signal, 1: enable, 0: disable*/
#define CPR_BBPLL_BG_VCO_EN            CPR_BBPLL_BG_VCO_EN_MSK
#define CPR_BBPLL_BG_VCO_EN_W(X)       ((X) << CPR_BBPLL_BG_VCO_EN_POS)
#define CPR_BBPLL_BG_LDO_EN_POS        (8U)
#define CPR_BBPLL_BG_LDO_EN_MSK        (0x1UL << CPR_BBPLL_BG_LDO_EN_POS) /*!< bbpll bandgap 10uA to ldo enable control signal, 1: enable, 0: disable*/
#define CPR_BBPLL_BG_LDO_EN            CPR_BBPLL_BG_LDO_EN_MSK
#define CPR_BBPLL_BG_LDO_EN_W(X)       ((X) << CPR_BBPLL_BG_LDO_EN_POS)
#define CPR_BBPLL_LDO_TRIM_POS         (12U)
#define CPR_BBPLL_LDO_TRIM_MSK         (0x7UL << CPR_BBPLL_LDO_TRIM_POS) /*!< bbpll ldo trim control signal*/
#define CPR_BBPLL_LDO_TRIM             CPR_BBPLL_LDO_TRIM_MSK
#define CPR_BBPLL_LDO_TRIM_W(X)        ((X) << CPR_BBPLL_LDO_TRIM_POS)
#define CPR_BBPLL_CK_CODEC_EN_POS      (15U)
#define CPR_BBPLL_CK_CODEC_EN_MSK      (0x1UL << CPR_BBPLL_CK_CODEC_EN_POS) /*!< bbpll output 6.144M clock to codec enable signal, 1: enable, 0: disable*/
#define CPR_BBPLL_CK_CODEC_EN          CPR_BBPLL_CK_CODEC_EN_MSK
#define CPR_BBPLL_CK_CODEC_EN_W(X)     ((X) << CPR_BBPLL_CK_CODEC_EN_POS)
#define CPR_BBPLL_CK_DIG_EN_POS        (16U)
#define CPR_BBPLL_CK_DIG_EN_MSK        (0x1UL << CPR_BBPLL_CK_DIG_EN_POS) /*!< bbpll output 768M clock to digital enable signal, 1: enable, 0: disable*/
#define CPR_BBPLL_CK_DIG_EN            CPR_BBPLL_CK_DIG_EN_MSK
#define CPR_BBPLL_CK_DIG_EN_W(X)       ((X) << CPR_BBPLL_CK_DIG_EN_POS)
#define CPR_BBPLL_VCO_FAST_EN_POS      (17U)
#define CPR_BBPLL_VCO_FAST_EN_MSK      (0x1UL << CPR_BBPLL_VCO_FAST_EN_POS) /*!< bbpll vco fast startup control signal, 1: fast startup, 0: normal slow startup*/
#define CPR_BBPLL_VCO_FAST_EN          CPR_BBPLL_VCO_FAST_EN_MSK
#define CPR_BBPLL_VCO_FAST_EN_W(X)     ((X) << CPR_BBPLL_VCO_FAST_EN_POS)
#define CPR_BBPLL_LDO_FC_POS           (18U)
#define CPR_BBPLL_LDO_FC_MSK           (0x1UL << CPR_BBPLL_LDO_FC_POS) /*!< bbpll ldo fast charge control signal*/
#define CPR_BBPLL_LDO_FC               CPR_BBPLL_LDO_FC_MSK
#define CPR_BBPLL_LDO_FC_W(X)          ((X) << CPR_BBPLL_LDO_FC_POS)
#define CPR_BBPLL_LD_PD_POS            (21U)
#define CPR_BBPLL_LD_PD_MSK            (0x1UL << CPR_BBPLL_LD_PD_POS) /*!< bbpll lock detector power down control signal, 1: power down, 0: work*/
#define CPR_BBPLL_LD_PD                CPR_BBPLL_LD_PD_MSK
#define CPR_BBPLL_LD_PD_W(X)           ((X) << CPR_BBPLL_LD_PD_POS)
#define CPR_BBPLL_PUP_POS              (22U)
#define CPR_BBPLL_PUP_MSK              (0x1UL << CPR_BBPLL_PUP_POS) /*!< bbpll power up control signal, 1: power up, 0: power down*/
#define CPR_BBPLL_PUP                  CPR_BBPLL_PUP_MSK
#define CPR_BBPLL_PUP_W(X)             ((X) << CPR_BBPLL_PUP_POS)
#define CPR_BBPLL_LDO_PUP_POS          (23U)
#define CPR_BBPLL_LDO_PUP_MSK          (0x1UL << CPR_BBPLL_LDO_PUP_POS) /*!< bbpll ldo power up control signal, 1: power up, 0: power down*/
#define CPR_BBPLL_LDO_PUP              CPR_BBPLL_LDO_PUP_MSK
#define CPR_BBPLL_LDO_PUP_W(X)         ((X) << CPR_BBPLL_LDO_PUP_POS)
#define CPR_BBPLL_BG_PUP_IBG_POS       (25U)
#define CPR_BBPLL_BG_PUP_IBG_MSK       (0x1UL << CPR_BBPLL_BG_PUP_IBG_POS) /*!< bbpll bandgap ibg bias to bbpll enable control signal, 1: enable, 0: disable*/
#define CPR_BBPLL_BG_PUP_IBG           CPR_BBPLL_BG_PUP_IBG_MSK
#define CPR_BBPLL_BG_PUP_IBG_W(X)      ((X) << CPR_BBPLL_BG_PUP_IBG_POS)
#define CPR_BBPLL_BG_PUP_IBG_TBUF_POS  (29U)
#define CPR_BBPLL_BG_PUP_IBG_TBUF_MSK  (0x1UL << CPR_BBPLL_BG_PUP_IBG_TBUF_POS) /*!< bbpll bandgap ibg bias to txbuf enable control signal, 1: enable, 0: disable*/
#define CPR_BBPLL_BG_PUP_IBG_TBUF      CPR_BBPLL_BG_PUP_IBG_TBUF_MSK
#define CPR_BBPLL_BG_PUP_IBG_TBUF_W(X) ((X) << CPR_BBPLL_BG_PUP_IBG_TBUF_POS)

//BBPLL_TEST offsetaddress : 0x0148
//BBPLL_TEST RegResetValue : 0x0
#define CPR_BBPLL_CK6P144M_TEST_EN_POS  (0U)
#define CPR_BBPLL_CK6P144M_TEST_EN_MSK  (0x1UL << CPR_BBPLL_CK6P144M_TEST_EN_POS) /*!< bbpll output 24M test control signal, 1:test enable, 0: test disable*/
#define CPR_BBPLL_CK6P144M_TEST_EN      CPR_BBPLL_CK6P144M_TEST_EN_MSK
#define CPR_BBPLL_CK6P144M_TEST_EN_W(X) ((X) << CPR_BBPLL_CK6P144M_TEST_EN_POS)
#define CPR_BBPLL_VCTL_TEST_EN_POS      (1U)
#define CPR_BBPLL_VCTL_TEST_EN_MSK      (0x1UL << CPR_BBPLL_VCTL_TEST_EN_POS) /*!< bbpll locked voltage test control signal, 1:test enable, 0: test disable*/
#define CPR_BBPLL_VCTL_TEST_EN          CPR_BBPLL_VCTL_TEST_EN_MSK
#define CPR_BBPLL_VCTL_TEST_EN_W(X)     ((X) << CPR_BBPLL_VCTL_TEST_EN_POS)
#define CPR_BBPLL_DC_TEST_EN_POS        (2U)
#define CPR_BBPLL_DC_TEST_EN_MSK        (0x1UL << CPR_BBPLL_DC_TEST_EN_POS) /*!< bbpll dc test control signal, 1:dc signal is connected to testpin, 0: disconnected*/
#define CPR_BBPLL_DC_TEST_EN            CPR_BBPLL_DC_TEST_EN_MSK
#define CPR_BBPLL_DC_TEST_EN_W(X)       ((X) << CPR_BBPLL_DC_TEST_EN_POS)
#define CPR_BBPLL_CK_TEST_EN_POS        (3U)
#define CPR_BBPLL_CK_TEST_EN_MSK        (0x1UL << CPR_BBPLL_CK_TEST_EN_POS) /*!< bbpll ck test control signal, 1:ck signal is connected to testpin, 0: disconnected*/
#define CPR_BBPLL_CK_TEST_EN            CPR_BBPLL_CK_TEST_EN_MSK
#define CPR_BBPLL_CK_TEST_EN_W(X)       ((X) << CPR_BBPLL_CK_TEST_EN_POS)
#define CPR_BBPLL_LDO_DIAG_CODE_POS     (4U)
#define CPR_BBPLL_LDO_DIAG_CODE_MSK     (0x7UL << CPR_BBPLL_LDO_DIAG_CODE_POS) /*!< bbpll ldo test signal mux choice*/
#define CPR_BBPLL_LDO_DIAG_CODE         CPR_BBPLL_LDO_DIAG_CODE_MSK
#define CPR_BBPLL_LDO_DIAG_CODE_W(X)    ((X) << CPR_BBPLL_LDO_DIAG_CODE_POS)
#define CPR_BBPLL_LDO_DIAG_SEL_POS      (7U)
#define CPR_BBPLL_LDO_DIAG_SEL_MSK      (0x1UL << CPR_BBPLL_LDO_DIAG_SEL_POS) /*!< bbpll ldo test control signal, 1: test enable, 0: test disable*/
#define CPR_BBPLL_LDO_DIAG_SEL          CPR_BBPLL_LDO_DIAG_SEL_MSK
#define CPR_BBPLL_LDO_DIAG_SEL_W(X)     ((X) << CPR_BBPLL_LDO_DIAG_SEL_POS)

//FRAC_PLL offsetaddress : 0x014c
//FRAC_PLL RegResetValue : 0x0
#define CPR_FRAC_PLL_EN_POS         (0U)
#define CPR_FRAC_PLL_EN_MSK         (0x1UL << CPR_FRAC_PLL_EN_POS) /*!< pll enable signal, high active*/
#define CPR_FRAC_PLL_EN             CPR_FRAC_PLL_EN_MSK
#define CPR_FRAC_PLL_EN_W(X)        ((X) << CPR_FRAC_PLL_EN_POS)
#define CPR_FRAC_PLL_RESETN_POS     (1U)
#define CPR_FRAC_PLL_RESETN_MSK     (0x1UL << CPR_FRAC_PLL_RESETN_POS) /*!< reset signal, low active*/
#define CPR_FRAC_PLL_RESETN         CPR_FRAC_PLL_RESETN_MSK
#define CPR_FRAC_PLL_RESETN_W(X)    ((X) << CPR_FRAC_PLL_RESETN_POS)
#define CPR_FRAC_PLL_EN_FRAC_POS    (2U)
#define CPR_FRAC_PLL_EN_FRAC_MSK    (0x1UL << CPR_FRAC_PLL_EN_FRAC_POS) /*!< fractional divider enable, high active*/
#define CPR_FRAC_PLL_EN_FRAC        CPR_FRAC_PLL_EN_FRAC_MSK
#define CPR_FRAC_PLL_EN_FRAC_W(X)   ((X) << CPR_FRAC_PLL_EN_FRAC_POS)
#define CPR_FRAC_PLL_DIVF_INTG_POS  (3U)
#define CPR_FRAC_PLL_DIVF_INTG_MSK  (0x1fUL << CPR_FRAC_PLL_DIVF_INTG_POS) /*!< integral divider ratio (FN) selection*/
#define CPR_FRAC_PLL_DIVF_INTG      CPR_FRAC_PLL_DIVF_INTG_MSK
#define CPR_FRAC_PLL_DIVF_INTG_W(X) ((X) << CPR_FRAC_PLL_DIVF_INTG_POS)
#define CPR_FRAC_PLL_ADJ_POS        (8U)
#define CPR_FRAC_PLL_ADJ_MSK \
    (0xffUL                  \
     << CPR_FRAC_PLL_ADJ_POS) /*!< pll parameter adjustment signal [15:14]: working frequency adjustment signal          00: low          01: normal (default)          10: high          11: higher [13:12]: VCO gain adjustment signal          00: lower          01: low          10: normal (default)          11: high [11:10]: loop filter resistance adjustment signal          00: lower          01: low          10: normal (default)          11: high [9:8]:   charge pump current adjustment signal          00: 0.5          01: 1.0 (default)          10: 1.5          11: 2.0*/
#define CPR_FRAC_PLL_ADJ            CPR_FRAC_PLL_ADJ_MSK
#define CPR_FRAC_PLL_ADJ_W(X)       ((X) << CPR_FRAC_PLL_ADJ_POS)
#define CPR_FRAC_PLL_DIVF_FRAC_POS  (16U)
#define CPR_FRAC_PLL_DIVF_FRAC_MSK  (0xffffUL << CPR_FRAC_PLL_DIVF_FRAC_POS) /*!< fractional divier ratio (FD) FD = FRAC/2^16*/
#define CPR_FRAC_PLL_DIVF_FRAC      CPR_FRAC_PLL_DIVF_FRAC_MSK
#define CPR_FRAC_PLL_DIVF_FRAC_W(X) ((X) << CPR_FRAC_PLL_DIVF_FRAC_POS)

//PLL_STAT offsetaddress : 0x0150
//PLL_STAT RegResetValue : 0x0
#define CPR_BBPLL_LOW_FLAG_POS   (0U)
#define CPR_BBPLL_LOW_FLAG_MSK   (0x1UL << CPR_BBPLL_LOW_FLAG_POS) /*!< */
#define CPR_BBPLL_LOW_FLAG       CPR_BBPLL_LOW_FLAG_MSK
#define CPR_BBPLL_LOW_FLAG_W(X)  ((X) << CPR_BBPLL_LOW_FLAG_POS)
#define CPR_BBPLL_HIGH_FLAG_POS  (1U)
#define CPR_BBPLL_HIGH_FLAG_MSK  (0x1UL << CPR_BBPLL_HIGH_FLAG_POS) /*!< */
#define CPR_BBPLL_HIGH_FLAG      CPR_BBPLL_HIGH_FLAG_MSK
#define CPR_BBPLL_HIGH_FLAG_W(X) ((X) << CPR_BBPLL_HIGH_FLAG_POS)
#define CPR_BBPLL_LOCK_FLAG_POS  (2U)
#define CPR_BBPLL_LOCK_FLAG_MSK  (0x1UL << CPR_BBPLL_LOCK_FLAG_POS) /*!< */
#define CPR_BBPLL_LOCK_FLAG      CPR_BBPLL_LOCK_FLAG_MSK
#define CPR_BBPLL_LOCK_FLAG_W(X) ((X) << CPR_BBPLL_LOCK_FLAG_POS)
#define CPR_FRAC_PLL_LD_POS      (3U)
#define CPR_FRAC_PLL_LD_MSK      (0x1UL << CPR_FRAC_PLL_LD_POS) /*!< frac pll lock indication, high indicates pll locked*/
#define CPR_FRAC_PLL_LD          CPR_FRAC_PLL_LD_MSK
#define CPR_FRAC_PLL_LD_W(X)     ((X) << CPR_FRAC_PLL_LD_POS)

//PGA_SCLK_DIV offsetaddress : 0x0160
//PGA_SCLK_DIV RegResetValue : 0x9
#define CPR_PGA_SCLK_DIV_VAL_POS  (0U)
#define CPR_PGA_SCLK_DIV_VAL_MSK  (0xffUL << CPR_PGA_SCLK_DIV_VAL_POS) /*!< pga_sclk divider. only exists in FPGA*/
#define CPR_PGA_SCLK_DIV_VAL      CPR_PGA_SCLK_DIV_VAL_MSK
#define CPR_PGA_SCLK_DIV_VAL_W(X) ((X) << CPR_PGA_SCLK_DIV_VAL_POS)
#define CPR_XIP_DECRYPT_EN_POS    (8U)
#define CPR_XIP_DECRYPT_EN_MSK    (0x1UL << CPR_XIP_DECRYPT_EN_POS) /*!< xip decryption enable, only exists in FPGA*/
#define CPR_XIP_DECRYPT_EN        CPR_XIP_DECRYPT_EN_MSK
#define CPR_XIP_DECRYPT_EN_W(X)   ((X) << CPR_XIP_DECRYPT_EN_POS)

//XIP_SW_KEYA offsetaddress : 0x0164
//XIP_SW_KEYA RegResetValue : 0x0
#define CPR_XIP_DECRYPT_KEYA_FPGA_POS  (0U)
#define CPR_XIP_DECRYPT_KEYA_FPGA_MSK  (0xffffffffUL << CPR_XIP_DECRYPT_KEYA_FPGA_POS) /*!< xip decryption key A, only exists in FPGA*/
#define CPR_XIP_DECRYPT_KEYA_FPGA      CPR_XIP_DECRYPT_KEYA_FPGA_MSK
#define CPR_XIP_DECRYPT_KEYA_FPGA_W(X) ((X) << CPR_XIP_DECRYPT_KEYA_FPGA_POS)

//XIP_SW_KEYB offsetaddress : 0x0168
//XIP_SW_KEYB RegResetValue : 0x0
#define CPR_XIP_DECRYPT_KEYB_FPGA_POS  (0U)
#define CPR_XIP_DECRYPT_KEYB_FPGA_MSK  (0xffffffffUL << CPR_XIP_DECRYPT_KEYB_FPGA_POS) /*!< xip decryption key B, only exists in FPGA*/
#define CPR_XIP_DECRYPT_KEYB_FPGA      CPR_XIP_DECRYPT_KEYB_FPGA_MSK
#define CPR_XIP_DECRYPT_KEYB_FPGA_W(X) ((X) << CPR_XIP_DECRYPT_KEYB_FPGA_POS)

//ARBITER0 offsetaddress : 0x0170
//ARBITER0 RegResetValue : 0x0
#define CPR_CPU0_LOCK_POS    (0U)
#define CPR_CPU0_LOCK_MSK    (0x1UL << CPR_CPU0_LOCK_POS) /*!< 0:ram0 unlocked by cpu0 ,1:ram0 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK        CPR_CPU0_LOCK_MSK
#define CPR_CPU0_LOCK_W(X)   ((X) << CPR_CPU0_LOCK_POS)
#define CPR_CPU1_LOCK_POS    (1U)
#define CPR_CPU1_LOCK_MSK    (0x1UL << CPR_CPU1_LOCK_POS) /*!< */
#define CPR_CPU1_LOCK        CPR_CPU1_LOCK_MSK
#define CPR_CPU1_LOCK_W(X)   ((X) << CPR_CPU1_LOCK_POS)
#define CPR_CPU2_LOCK_POS    (2U)
#define CPR_CPU2_LOCK_MSK    (0x1UL << CPR_CPU2_LOCK_POS) /*!< */
#define CPR_CPU2_LOCK        CPR_CPU2_LOCK_MSK
#define CPR_CPU2_LOCK_W(X)   ((X) << CPR_CPU2_LOCK_POS)
#define CPR_USER_DIFINE_POS  (3U)
#define CPR_USER_DIFINE_MSK  (0x1UL << CPR_USER_DIFINE_POS) /*!< */
#define CPR_USER_DIFINE      CPR_USER_DIFINE_MSK
#define CPR_USER_DIFINE_W(X) ((X) << CPR_USER_DIFINE_POS)

//ARBITER1 offsetaddress : 0x0174
//ARBITER1 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER1_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER1_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER1_POS) /*!< 0:ram1 unlocked by cpu0 ,1:ram1 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER1        CPR_CPU0_LOCK_ARBITER1_MSK
#define CPR_CPU0_LOCK_ARBITER1_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER1_POS)
#define CPR_CPU1_LOCK_ARBITER1_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER1_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER1_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER1        CPR_CPU1_LOCK_ARBITER1_MSK
#define CPR_CPU1_LOCK_ARBITER1_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER1_POS)
#define CPR_CPU2_LOCK_ARBITER1_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER1_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER1_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER1        CPR_CPU2_LOCK_ARBITER1_MSK
#define CPR_CPU2_LOCK_ARBITER1_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER1_POS)
#define CPR_USER_DIFINE_ARBITER1_POS  (3U)
#define CPR_USER_DIFINE_ARBITER1_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER1_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER1      CPR_USER_DIFINE_ARBITER1_MSK
#define CPR_USER_DIFINE_ARBITER1_W(X) ((X) << CPR_USER_DIFINE_ARBITER1_POS)

//ARBITER2 offsetaddress : 0x0178
//ARBITER2 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER2_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER2_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER2_POS) /*!< 0:ram2 unlocked by cpu0 ,1:ram2 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER2        CPR_CPU0_LOCK_ARBITER2_MSK
#define CPR_CPU0_LOCK_ARBITER2_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER2_POS)
#define CPR_CPU1_LOCK_ARBITER2_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER2_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER2_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER2        CPR_CPU1_LOCK_ARBITER2_MSK
#define CPR_CPU1_LOCK_ARBITER2_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER2_POS)
#define CPR_CPU2_LOCK_ARBITER2_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER2_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER2_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER2        CPR_CPU2_LOCK_ARBITER2_MSK
#define CPR_CPU2_LOCK_ARBITER2_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER2_POS)
#define CPR_USER_DIFINE_ARBITER2_POS  (3U)
#define CPR_USER_DIFINE_ARBITER2_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER2_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER2      CPR_USER_DIFINE_ARBITER2_MSK
#define CPR_USER_DIFINE_ARBITER2_W(X) ((X) << CPR_USER_DIFINE_ARBITER2_POS)

//ARBITER3 offsetaddress : 0x017c
//ARBITER3 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER3_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER3_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER3_POS) /*!< 0:ram3 unlocked by cpu0 ,1:ram3 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER3        CPR_CPU0_LOCK_ARBITER3_MSK
#define CPR_CPU0_LOCK_ARBITER3_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER3_POS)
#define CPR_CPU1_LOCK_ARBITER3_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER3_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER3_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER3        CPR_CPU1_LOCK_ARBITER3_MSK
#define CPR_CPU1_LOCK_ARBITER3_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER3_POS)
#define CPR_CPU2_LOCK_ARBITER3_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER3_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER3_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER3        CPR_CPU2_LOCK_ARBITER3_MSK
#define CPR_CPU2_LOCK_ARBITER3_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER3_POS)
#define CPR_USER_DIFINE_ARBITER3_POS  (3U)
#define CPR_USER_DIFINE_ARBITER3_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER3_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER3      CPR_USER_DIFINE_ARBITER3_MSK
#define CPR_USER_DIFINE_ARBITER3_W(X) ((X) << CPR_USER_DIFINE_ARBITER3_POS)

//ARBITER4 offsetaddress : 0x0180
//ARBITER4 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER4_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER4_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER4_POS) /*!< 0:ram4 unlocked by cpu0 ,1:ram4 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER4        CPR_CPU0_LOCK_ARBITER4_MSK
#define CPR_CPU0_LOCK_ARBITER4_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER4_POS)
#define CPR_CPU1_LOCK_ARBITER4_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER4_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER4_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER4        CPR_CPU1_LOCK_ARBITER4_MSK
#define CPR_CPU1_LOCK_ARBITER4_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER4_POS)
#define CPR_CPU2_LOCK_ARBITER4_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER4_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER4_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER4        CPR_CPU2_LOCK_ARBITER4_MSK
#define CPR_CPU2_LOCK_ARBITER4_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER4_POS)
#define CPR_USER_DIFINE_ARBITER4_POS  (3U)
#define CPR_USER_DIFINE_ARBITER4_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER4_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER4      CPR_USER_DIFINE_ARBITER4_MSK
#define CPR_USER_DIFINE_ARBITER4_W(X) ((X) << CPR_USER_DIFINE_ARBITER4_POS)

//ARBITER5 offsetaddress : 0x0184
//ARBITER5 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER5_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER5_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER5_POS) /*!< 0:ram5 unlocked by cpu0 ,1:ram5 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER5        CPR_CPU0_LOCK_ARBITER5_MSK
#define CPR_CPU0_LOCK_ARBITER5_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER5_POS)
#define CPR_CPU1_LOCK_ARBITER5_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER5_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER5_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER5        CPR_CPU1_LOCK_ARBITER5_MSK
#define CPR_CPU1_LOCK_ARBITER5_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER5_POS)
#define CPR_CPU2_LOCK_ARBITER5_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER5_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER5_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER5        CPR_CPU2_LOCK_ARBITER5_MSK
#define CPR_CPU2_LOCK_ARBITER5_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER5_POS)
#define CPR_USER_DIFINE_ARBITER5_POS  (3U)
#define CPR_USER_DIFINE_ARBITER5_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER5_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER5      CPR_USER_DIFINE_ARBITER5_MSK
#define CPR_USER_DIFINE_ARBITER5_W(X) ((X) << CPR_USER_DIFINE_ARBITER5_POS)

//ARBITER6 offsetaddress : 0x0188
//ARBITER6 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER6_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER6_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER6_POS) /*!< 0:ram6 unlocked by cpu0 ,1:ram6 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER6        CPR_CPU0_LOCK_ARBITER6_MSK
#define CPR_CPU0_LOCK_ARBITER6_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER6_POS)
#define CPR_CPU1_LOCK_ARBITER6_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER6_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER6_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER6        CPR_CPU1_LOCK_ARBITER6_MSK
#define CPR_CPU1_LOCK_ARBITER6_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER6_POS)
#define CPR_CPU2_LOCK_ARBITER6_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER6_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER6_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER6        CPR_CPU2_LOCK_ARBITER6_MSK
#define CPR_CPU2_LOCK_ARBITER6_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER6_POS)
#define CPR_USER_DIFINE_ARBITER6_POS  (3U)
#define CPR_USER_DIFINE_ARBITER6_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER6_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER6      CPR_USER_DIFINE_ARBITER6_MSK
#define CPR_USER_DIFINE_ARBITER6_W(X) ((X) << CPR_USER_DIFINE_ARBITER6_POS)

//ARBITER7 offsetaddress : 0x018c
//ARBITER7 RegResetValue : 0x0
#define CPR_CPU0_LOCK_ARBITER7_POS    (0U)
#define CPR_CPU0_LOCK_ARBITER7_MSK    (0x1UL << CPR_CPU0_LOCK_ARBITER7_POS) /*!< 0:ram7 unlocked by cpu0 ,1:ram7 locked by cpu0; write 32'hffff ffff to clear*/
#define CPR_CPU0_LOCK_ARBITER7        CPR_CPU0_LOCK_ARBITER7_MSK
#define CPR_CPU0_LOCK_ARBITER7_W(X)   ((X) << CPR_CPU0_LOCK_ARBITER7_POS)
#define CPR_CPU1_LOCK_ARBITER7_POS    (1U)
#define CPR_CPU1_LOCK_ARBITER7_MSK    (0x1UL << CPR_CPU1_LOCK_ARBITER7_POS) /*!< */
#define CPR_CPU1_LOCK_ARBITER7        CPR_CPU1_LOCK_ARBITER7_MSK
#define CPR_CPU1_LOCK_ARBITER7_W(X)   ((X) << CPR_CPU1_LOCK_ARBITER7_POS)
#define CPR_CPU2_LOCK_ARBITER7_POS    (2U)
#define CPR_CPU2_LOCK_ARBITER7_MSK    (0x1UL << CPR_CPU2_LOCK_ARBITER7_POS) /*!< */
#define CPR_CPU2_LOCK_ARBITER7        CPR_CPU2_LOCK_ARBITER7_MSK
#define CPR_CPU2_LOCK_ARBITER7_W(X)   ((X) << CPR_CPU2_LOCK_ARBITER7_POS)
#define CPR_USER_DIFINE_ARBITER7_POS  (3U)
#define CPR_USER_DIFINE_ARBITER7_MSK  (0x1UL << CPR_USER_DIFINE_ARBITER7_POS) /*!< */
#define CPR_USER_DIFINE_ARBITER7      CPR_USER_DIFINE_ARBITER7_MSK
#define CPR_USER_DIFINE_ARBITER7_W(X) ((X) << CPR_USER_DIFINE_ARBITER7_POS)

//PA_MUX_CTL_0 offsetaddress : 0x1e0
//PA_MUX_CTL_0 RegResetValue : 0x0
#define CPR_PA_MUX_CTL_31_0_POS  (0U)
#define CPR_PA_MUX_CTL_31_0_MSK  (0xffffffffUL << CPR_PA_MUX_CTL_31_0_POS) /*!< 0000~1010 corresponds to func0~func10: PA00:pa_mux_ctl[3:0] PA01:pa_mux_ctl[7:4] PA02:pa_mux_ctl[11:8] PA03:pa_mux_ctl[15:12] PA04:pa_mux_ctl[19:16] PA05:pa_mux_ctl[23:20] PA06:pa_mux_ctl[27:24] PA07:pa_mux_ctl[31:28]*/
#define CPR_PA_MUX_CTL_31_0      CPR_PA_MUX_CTL_31_0_MSK
#define CPR_PA_MUX_CTL_31_0_W(X) ((X) << CPR_PA_MUX_CTL_31_0_POS)

//PA_MUX_CTL_1 offsetaddress : 0x1e4
//PA_MUX_CTL_1 RegResetValue : 0x0
#define CPR_PA_MUX_CTL_63_32_POS  (0U)
#define CPR_PA_MUX_CTL_63_32_MSK  (0xffffffffUL << CPR_PA_MUX_CTL_63_32_POS) /*!< 0000~ Pa13:pa_mux_ttl[55:52] 14:pa_mux_ttl[59:56] at 15:pa_mux_ctl[63:6*/
#define CPR_PA_MUX_CTL_63_32      CPR_PA_MUX_CTL_63_32_MSK
#define CPR_PA_MUX_CTL_63_32_W(X) ((X) << CPR_PA_MUX_CTL_63_32_POS)

//PA_MUX_CTL_2 offsetaddress : 0x1e8
//PA_MUX_CTL_2 RegResetValue : 0x0
#define CPR_PA_MUX_CTL_95_64_POS  (0U)
#define CPR_PA_MUX_CTL_95_64_MSK  (0xffffffffUL << CPR_PA_MUX_CTL_95_64_POS) /*!< 0000~ Pa21:Pa_mux_ttl[87:84] pa22:pa_mux_ttl[91:88] pa23:pa_mux_ctl[95:92]*/
#define CPR_PA_MUX_CTL_95_64      CPR_PA_MUX_CTL_95_64_MSK
#define CPR_PA_MUX_CTL_95_64_W(X) ((X) << CPR_PA_MUX_CTL_95_64_POS)

//PA_MUX_CTL_3 offsetaddress : 0x1ec
//PA_MUX_CTL_3 RegResetValue : 0x0
#define CPR_PA_MUX_CTL_127_96_POS (0U)
#define CPR_PA_MUX_CTL_127_96_MSK \
    (0xffffffffUL << CPR_PA_MUX_CTL_127_96_POS) /*!< 0000010 corresponds to func0~func10: pa_mux_ttl[99:96] pa25: pa_mux_ctl[103:100] 26: pa_mux_ttl[107:1 pa_mux_ttl[115:112] pa29: pa_mux_ttl[119:116] Pa30: Pa_mux_ttl[123:120] Pa31: pa_mux_ctl[127:124]*/
#define CPR_PA_MUX_CTL_127_96      CPR_PA_MUX_CTL_127_96_MSK
#define CPR_PA_MUX_CTL_127_96_W(X) ((X) << CPR_PA_MUX_CTL_127_96_POS)

//PB_MUX_CTL_0 offsetaddress : 0x1f0
//PB_MUX_CTL_0 RegResetValue : 0x0
#define CPR_PB_MUX_CTL_31_0_POS  (0U)
#define CPR_PB_MUX_CTL_31_0_MSK  (0xffffffffUL << CPR_PB_MUX_CTL_31_0_POS) /*!< 0000~1010 corresponds to func0~func10: PB00:pb_mux_ctl[3:0] PB01:pb_mux_ctl[7:4] PB02:pb_mux_ctl[11:8] PB03:pb_mux_ctl[15:12] PB04:pb_mux_ctl[19:16] PB05:pb_mux_ctl[23:20] PB06:pb_mux_ctl[27:24] PB07:pb_mux_ctl[31:28]*/
#define CPR_PB_MUX_CTL_31_0      CPR_PB_MUX_CTL_31_0_MSK
#define CPR_PB_MUX_CTL_31_0_W(X) ((X) << CPR_PB_MUX_CTL_31_0_POS)

//PB_MUX_CTL_1 offsetaddress : 0x1f4
//PB_MUX_CTL_1 RegResetValue : 0x0
#define CPR_PB_MUX_CTL_55_32_POS  (0U)
#define CPR_PB_MUX_CTL_55_32_MSK  (0xfffffffUL << CPR_PB_MUX_CTL_55_32_POS) /*!< 0000~1010 corresponds to func0~func10: PB08:pb_mux_ctl[35:32] PB09:pb_mux_ctl[39:36] PB10:pb_mux_ctl[43:40] PB11:pb_mux_ctl[47:44] PB12:pb_mux_ctl[51:48] PB13:pb_mux_ctl[55:52] PB_SWIRE:pb_mux_ctl[59:56]*/
#define CPR_PB_MUX_CTL_55_32      CPR_PB_MUX_CTL_55_32_MSK
#define CPR_PB_MUX_CTL_55_32_W(X) ((X) << CPR_PB_MUX_CTL_55_32_POS)

//PC_MUX_CTL offsetaddress : 0x1f8
//PC_MUX_CTL RegResetValue : 0x0
#define CPR_PC_MUX_CTL_19_0_POS  (0U)
#define CPR_PC_MUX_CTL_19_0_MSK  (0xfffffUL << CPR_PC_MUX_CTL_19_0_POS) /*!< */
#define CPR_PC_MUX_CTL_19_0      CPR_PC_MUX_CTL_19_0_MSK
#define CPR_PC_MUX_CTL_19_0_W(X) ((X) << CPR_PC_MUX_CTL_19_0_POS)

//JTAG_MUX_CTL offsetaddress : 0x1fc
//JTAG_MUX_CTL RegResetValue : 0x0
#define CPR_JTAG_CPU_SWITCH_POS  (0U)
#define CPR_JTAG_CPU_SWITCH_MSK  (0x1UL << CPR_JTAG_CPU_SWITCH_POS) /*!< PA06~PA09 function switch to cpu jtag*/
#define CPR_JTAG_CPU_SWITCH      CPR_JTAG_CPU_SWITCH_MSK
#define CPR_JTAG_CPU2_SWITCH_POS (1U)
#define CPR_JTAG_CPU2_SWITCH_MSK (0x1UL << CPR_JTAG_CPU2_SWITCH_POS) /*!< PA06~PA09 function switch to CPU2 jtag*/
#define CPR_JTAG_CPU2_SWITCH     CPR_JTAG_CPU2_SWITCH_MSK

//PA_IE_CFG offsetaddress : 0x0200
//PA_IE_CFG RegResetValue : 0xffffffff
#define CPR_PA_IE_POS  (0U)
#define CPR_PA_IE_MSK  (0xffffffffUL << CPR_PA_IE_POS) /*!< PA I/O input enable*/
#define CPR_PA_IE      CPR_PA_IE_MSK
#define CPR_PA_IE_W(X) ((X) << CPR_PA_IE_POS)

//PC_IE_CFG offsetaddress : 0x0204
//PC_IE_CFG RegResetValue : 0x3ff
#define CPR_PC_IE_POS  (0U)
#define CPR_PC_IE_MSK  (0x3ffUL << CPR_PC_IE_POS) /*!< PC I/O input enable*/
#define CPR_PC_IE      CPR_PC_IE_MSK
#define CPR_PC_IE_W(X) ((X) << CPR_PC_IE_POS)

//PA_CTRL_0 offsetaddress : 0x0208
//PA_CTRL_0 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_31_0_POS  (0U)
#define CPR_PA_CTRL_31_0_MSK  (0xffffffffUL << CPR_PA_CTRL_31_0_POS) /*!< pa control*/
#define CPR_PA_CTRL_31_0      CPR_PA_CTRL_31_0_MSK
#define CPR_PA_CTRL_31_0_W(X) ((X) << CPR_PA_CTRL_31_0_POS)

//PA_CTRL_1 offsetaddress : 0x020c
//PA_CTRL_1 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_63_32_POS  (0U)
#define CPR_PA_CTRL_63_32_MSK  (0xffffffffUL << CPR_PA_CTRL_63_32_POS) /*!< pa control*/
#define CPR_PA_CTRL_63_32      CPR_PA_CTRL_63_32_MSK
#define CPR_PA_CTRL_63_32_W(X) ((X) << CPR_PA_CTRL_63_32_POS)

//PA_CTRL_2 offsetaddress : 0x0210
//PA_CTRL_2 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_95_64_POS  (0U)
#define CPR_PA_CTRL_95_64_MSK  (0xffffffffUL << CPR_PA_CTRL_95_64_POS) /*!< pa control*/
#define CPR_PA_CTRL_95_64      CPR_PA_CTRL_95_64_MSK
#define CPR_PA_CTRL_95_64_W(X) ((X) << CPR_PA_CTRL_95_64_POS)

//PA_CTRL_3 offsetaddress : 0x0214
//PA_CTRL_3 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_127_96_POS  (0U)
#define CPR_PA_CTRL_127_96_MSK  (0xffffffffUL << CPR_PA_CTRL_127_96_POS) /*!< pa control*/
#define CPR_PA_CTRL_127_96      CPR_PA_CTRL_127_96_MSK
#define CPR_PA_CTRL_127_96_W(X) ((X) << CPR_PA_CTRL_127_96_POS)

//PA_CTRL_4 offsetaddress : 0x0218
//PA_CTRL_4 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_159_128_POS  (0U)
#define CPR_PA_CTRL_159_128_MSK  (0xffffffffUL << CPR_PA_CTRL_159_128_POS) /*!< pa control*/
#define CPR_PA_CTRL_159_128      CPR_PA_CTRL_159_128_MSK
#define CPR_PA_CTRL_159_128_W(X) ((X) << CPR_PA_CTRL_159_128_POS)

//PA_CTRL_5 offsetaddress : 0x021c
//PA_CTRL_5 RegResetValue : 0xaaaa_aaaa
#define CPR_PA_CTRL_191_160_POS  (0U)
#define CPR_PA_CTRL_191_160_MSK  (0xffffffffUL << CPR_PA_CTRL_191_160_POS) /*!< pa control*/
#define CPR_PA_CTRL_191_160      CPR_PA_CTRL_191_160_MSK
#define CPR_PA_CTRL_191_160_W(X) ((X) << CPR_PA_CTRL_191_160_POS)

//PC_CTRL_0 offsetaddress : 0x0220
//PC_CTRL_0 RegResetValue : 0xaaaa_6aaa
#define CPR_PC_CTRL_31_0_POS  (0U)
#define CPR_PC_CTRL_31_0_MSK  (0xffffffffUL << CPR_PC_CTRL_31_0_POS) /*!< PC control*/
#define CPR_PC_CTRL_31_0      CPR_PC_CTRL_31_0_MSK
#define CPR_PC_CTRL_31_0_W(X) ((X) << CPR_PC_CTRL_31_0_POS)

//PC_CTRL_1 offsetaddress : 0x0224
//PC_CTRL_1 RegResetValue : 0x08eb_aaaa
#define CPR_PC_CTRL_59_32_POS  (0U)
#define CPR_PC_CTRL_59_32_MSK  (0xfffffffUL << CPR_PC_CTRL_59_32_POS) /*!< PC control*/
#define CPR_PC_CTRL_59_32      CPR_PC_CTRL_59_32_MSK
#define CPR_PC_CTRL_59_32_W(X) ((X) << CPR_PC_CTRL_59_32_POS)

//PA_WKUP_CTRL offsetaddress : 0x022c
//PA_WKUP_CTRL RegResetValue : 0x3
#define CPR_PA_PAD_DEB_TH_POS  (0U)
#define CPR_PA_PAD_DEB_TH_MSK  (0x7UL << CPR_PA_PAD_DEB_TH_POS) /*!< PA31~PA00 debounce threshold*/
#define CPR_PA_PAD_DEB_TH      CPR_PA_PAD_DEB_TH_MSK
#define CPR_PA_PAD_DEB_TH_W(X) ((X) << CPR_PA_PAD_DEB_TH_POS)
#define CPR_PA_IRQ_SEL_POS     (3U)
#define CPR_PA_IRQ_SEL_MSK     (0x1UL << CPR_PA_IRQ_SEL_POS) /*!< PA GPIO irq source select 0: from new gpio irq 1: from old gpio irq*/
#define CPR_PA_IRQ_SEL         CPR_PA_IRQ_SEL_MSK
#define CPR_PA_IRQ_SEL_W(X)    ((X) << CPR_PA_IRQ_SEL_POS)

//PA_WKUP_IRQ offsetaddress : 0x0230
//PA_WKUP_IRQ RegResetValue : 0x0
#define CPR_PA_PAD_WKUP_IRQ_POS  (0U)
#define CPR_PA_PAD_WKUP_IRQ_MSK  (0xffffffffUL << CPR_PA_PAD_WKUP_IRQ_POS) /*!< PA31~PA00 irq status, write 1 to clear*/
#define CPR_PA_PAD_WKUP_IRQ      CPR_PA_PAD_WKUP_IRQ_MSK
#define CPR_PA_PAD_WKUP_IRQ_W(X) ((X) << CPR_PA_PAD_WKUP_IRQ_POS)

//PA_WKUP_CFG0 offsetaddress : 0x0234
//PA_WKUP_CFG0 RegResetValue : 0x0
#define CPR_PA_PAD_WKUP_EN_POS  (0U)
#define CPR_PA_PAD_WKUP_EN_MSK  (0xffffffffUL << CPR_PA_PAD_WKUP_EN_POS) /*!< PA31~PA00 wake up enable 0: disable 1: enable*/
#define CPR_PA_PAD_WKUP_EN      CPR_PA_PAD_WKUP_EN_MSK
#define CPR_PA_PAD_WKUP_EN_W(X) ((X) << CPR_PA_PAD_WKUP_EN_POS)

//PA_WKUP_CFG1 offsetaddress : 0x0238
//PA_WKUP_CFG1 RegResetValue : 0x0
#define CPR_PA_PAD_WKUP_POL_POS  (0U)
#define CPR_PA_PAD_WKUP_POL_MSK  (0xffffffffUL << CPR_PA_PAD_WKUP_POL_POS) /*!< PA31~PA00 wake up polarity 0: logic high level 1: logic low level*/
#define CPR_PA_PAD_WKUP_POL      CPR_PA_PAD_WKUP_POL_MSK
#define CPR_PA_PAD_WKUP_POL_W(X) ((X) << CPR_PA_PAD_WKUP_POL_POS)

//PA_WKUP_CFG2 offsetaddress : 0x023c
//PA_WKUP_CFG2 RegResetValue : 0x0
#define CPR_PA_PAD_WKUP_SEL_POS  (0U)
#define CPR_PA_PAD_WKUP_SEL_MSK  (0xffffffffUL << CPR_PA_PAD_WKUP_SEL_POS) /*!< PA31~PA00 wake up debounce select 0: w/i debounce 1: w/o debounce*/
#define CPR_PA_PAD_WKUP_SEL      CPR_PA_PAD_WKUP_SEL_MSK
#define CPR_PA_PAD_WKUP_SEL_W(X) ((X) << CPR_PA_PAD_WKUP_SEL_POS)

//SYS_CTL_CPU_INTR_SET0 offsetaddress : 0x240
//SYS_CTL_CPU_INTR_SET0 RegResetValue : 0x0
#define CPR_CPU0_INTR_SET0_POS  (0U)
#define CPR_CPU0_INTR_SET0_MSK  (0x1UL << CPR_CPU0_INTR_SET0_POS) /*!< */
#define CPR_CPU0_INTR_SET0      CPR_CPU0_INTR_SET0_MSK
#define CPR_CPU0_INTR_SET1_POS  (1U)
#define CPR_CPU0_INTR_SET1_MSK  (0x1UL << CPR_CPU0_INTR_SET1_POS) /*!< */
#define CPR_CPU0_INTR_SET1      CPR_CPU0_INTR_SET1_MSK
#define CPR_CPU0_INTR_SET2_POS  (2U)
#define CPR_CPU0_INTR_SET2_MSK  (0x1UL << CPR_CPU0_INTR_SET2_POS) /*!< */
#define CPR_CPU0_INTR_SET2      CPR_CPU0_INTR_SET2_MSK
#define CPR_CPU0_INTR_SET3_POS  (3U)
#define CPR_CPU0_INTR_SET3_MSK  (0x1UL << CPR_CPU0_INTR_SET3_POS) /*!< */
#define CPR_CPU0_INTR_SET3      CPR_CPU0_INTR_SET3_MSK
#define CPR_CPU0_INTR_SET4_POS  (4U)
#define CPR_CPU0_INTR_SET4_MSK  (0x1UL << CPR_CPU0_INTR_SET4_POS) /*!< */
#define CPR_CPU0_INTR_SET4      CPR_CPU0_INTR_SET4_MSK
#define CPR_CPU0_INTR_SET5_POS  (5U)
#define CPR_CPU0_INTR_SET5_MSK  (0x1UL << CPR_CPU0_INTR_SET5_POS) /*!< */
#define CPR_CPU0_INTR_SET5      CPR_CPU0_INTR_SET5_MSK
#define CPR_CPU0_INTR_SET6_POS  (6U)
#define CPR_CPU0_INTR_SET6_MSK  (0x1UL << CPR_CPU0_INTR_SET6_POS) /*!< */
#define CPR_CPU0_INTR_SET6      CPR_CPU0_INTR_SET6_MSK
#define CPR_CPU0_INTR_SET7_POS  (7U)
#define CPR_CPU0_INTR_SET7_MSK  (0x1UL << CPR_CPU0_INTR_SET7_POS) /*!< */
#define CPR_CPU0_INTR_SET7      CPR_CPU0_INTR_SET7_MSK
#define CPR_CPU0_INTR_SET8_POS  (8U)
#define CPR_CPU0_INTR_SET8_MSK  (0x1UL << CPR_CPU0_INTR_SET8_POS) /*!< */
#define CPR_CPU0_INTR_SET8      CPR_CPU0_INTR_SET8_MSK
#define CPR_CPU0_INTR_SET9_POS  (9U)
#define CPR_CPU0_INTR_SET9_MSK  (0x1UL << CPR_CPU0_INTR_SET9_POS) /*!< */
#define CPR_CPU0_INTR_SET9      CPR_CPU0_INTR_SET9_MSK
#define CPR_CPU0_INTR_SET10_POS (10U)
#define CPR_CPU0_INTR_SET10_MSK (0x1UL << CPR_CPU0_INTR_SET10_POS) /*!< */
#define CPR_CPU0_INTR_SET10     CPR_CPU0_INTR_SET10_MSK
#define CPR_CPU0_INTR_SET11_POS (11U)
#define CPR_CPU0_INTR_SET11_MSK (0x1UL << CPR_CPU0_INTR_SET11_POS) /*!< */
#define CPR_CPU0_INTR_SET11     CPR_CPU0_INTR_SET11_MSK
#define CPR_CPU0_INTR_SET12_POS (12U)
#define CPR_CPU0_INTR_SET12_MSK (0x1UL << CPR_CPU0_INTR_SET12_POS) /*!< */
#define CPR_CPU0_INTR_SET12     CPR_CPU0_INTR_SET12_MSK
#define CPR_CPU0_INTR_SET13_POS (13U)
#define CPR_CPU0_INTR_SET13_MSK (0x1UL << CPR_CPU0_INTR_SET13_POS) /*!< */
#define CPR_CPU0_INTR_SET13     CPR_CPU0_INTR_SET13_MSK
#define CPR_CPU0_INTR_SET14_POS (14U)
#define CPR_CPU0_INTR_SET14_MSK (0x1UL << CPR_CPU0_INTR_SET14_POS) /*!< */
#define CPR_CPU0_INTR_SET14     CPR_CPU0_INTR_SET14_MSK
#define CPR_CPU0_INTR_SET15_POS (15U)
#define CPR_CPU0_INTR_SET15_MSK \
    (0x1UL                      \
     << CPR_CPU0_INTR_SET15_POS) /*!< Interrupt generation bit sent to the CPU When the CPU writes the interrupt number n, the counter of the corresponding interrupt source n is added &quot;1&quot;. When the count value of the interrupt source n is not equal to zero, if the interrupt source n is enabled, the interrupt source n sent to the CPU by SYS_CTRL will send an interrupt, adding the write mask function [0]: interrupt source 0, write 0 bits to 16 bits at the same time [1]: interrupt source 1, write 1 bits to 17 bits at the same time... [15]: interrupt source 15, write 15 bits to 31 bits at the same time*/
#define CPR_CPU0_INTR_SET15 CPR_CPU0_INTR_SET15_MSK

//SYS_CTL_CPU_INTR_CLR offsetaddress : 0x248
//SYS_CTL_CPU_INTR_CLR RegResetValue : 0x0
#define CPR_CPU_INTR_CLEAR_POS  (0U)
#define CPR_CPU_INTR_CLEAR_MSK  (0xffffUL << CPR_CPU_INTR_CLEAR_POS) /*!< Interrupt clearance sent to the CPU [0]: Interrupt source 0 [1]: Interrupt source 1 … [15]: Interrupt source 15*/
#define CPR_CPU_INTR_CLEAR      CPR_CPU_INTR_CLEAR_MSK
#define CPR_CPU_INTR_CLEAR_W(X) ((X) << CPR_CPU_INTR_CLEAR_POS)

//SYS_CTL_CPU_INTR_EN offsetaddress : 0x24c
//SYS_CTL_CPU_INTR_EN RegResetValue : 0x0
#define CPR_CPU0_INTR_ALL_EN_POS  (0U)
#define CPR_CPU0_INTR_ALL_EN_MSK  (0x1UL << CPR_CPU0_INTR_ALL_EN_POS) /*!< */
#define CPR_CPU0_INTR_ALL_EN      CPR_CPU0_INTR_ALL_EN_MSK
#define CPR_CPU0_INTR_ALL_EN_W(X) ((X) << CPR_CPU0_INTR_ALL_EN_POS)

//SYS_CTL_CPU_INTR_EN0 offsetaddress : 0x250
//SYS_CTL_CPU_INTR_EN0 RegResetValue : 0x0
#define CPR_CPU_INTR_SRC0_EN_POS   (0U)
#define CPR_CPU_INTR_SRC0_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC0_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC0_EN       CPR_CPU_INTR_SRC0_EN_MSK
#define CPR_CPU_INTR_SRC0_EN_W(X)  ((X) << CPR_CPU_INTR_SRC0_EN_POS)
#define CPR_CPU_INTR_SRC1_EN_POS   (1U)
#define CPR_CPU_INTR_SRC1_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC1_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC1_EN       CPR_CPU_INTR_SRC1_EN_MSK
#define CPR_CPU_INTR_SRC1_EN_W(X)  ((X) << CPR_CPU_INTR_SRC1_EN_POS)
#define CPR_CPU_INTR_SRC2_EN_POS   (2U)
#define CPR_CPU_INTR_SRC2_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC2_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC2_EN       CPR_CPU_INTR_SRC2_EN_MSK
#define CPR_CPU_INTR_SRC2_EN_W(X)  ((X) << CPR_CPU_INTR_SRC2_EN_POS)
#define CPR_CPU_INTR_SRC3_EN_POS   (3U)
#define CPR_CPU_INTR_SRC3_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC3_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC3_EN       CPR_CPU_INTR_SRC3_EN_MSK
#define CPR_CPU_INTR_SRC3_EN_W(X)  ((X) << CPR_CPU_INTR_SRC3_EN_POS)
#define CPR_CPU_INTR_SRC4_EN_POS   (4U)
#define CPR_CPU_INTR_SRC4_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC4_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC4_EN       CPR_CPU_INTR_SRC4_EN_MSK
#define CPR_CPU_INTR_SRC4_EN_W(X)  ((X) << CPR_CPU_INTR_SRC4_EN_POS)
#define CPR_CPU_INTR_SRC5_EN_POS   (5U)
#define CPR_CPU_INTR_SRC5_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC5_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC5_EN       CPR_CPU_INTR_SRC5_EN_MSK
#define CPR_CPU_INTR_SRC5_EN_W(X)  ((X) << CPR_CPU_INTR_SRC5_EN_POS)
#define CPR_CPU_INTR_SRC6_EN_POS   (6U)
#define CPR_CPU_INTR_SRC6_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC6_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC6_EN       CPR_CPU_INTR_SRC6_EN_MSK
#define CPR_CPU_INTR_SRC6_EN_W(X)  ((X) << CPR_CPU_INTR_SRC6_EN_POS)
#define CPR_CPU_INTR_SRC7_EN_POS   (7U)
#define CPR_CPU_INTR_SRC7_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC7_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC7_EN       CPR_CPU_INTR_SRC7_EN_MSK
#define CPR_CPU_INTR_SRC7_EN_W(X)  ((X) << CPR_CPU_INTR_SRC7_EN_POS)
#define CPR_CPU_INTR_SRC8_EN_POS   (8U)
#define CPR_CPU_INTR_SRC8_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC8_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC8_EN       CPR_CPU_INTR_SRC8_EN_MSK
#define CPR_CPU_INTR_SRC8_EN_W(X)  ((X) << CPR_CPU_INTR_SRC8_EN_POS)
#define CPR_CPU_INTR_SRC9_EN_POS   (9U)
#define CPR_CPU_INTR_SRC9_EN_MSK   (0x1UL << CPR_CPU_INTR_SRC9_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC9_EN       CPR_CPU_INTR_SRC9_EN_MSK
#define CPR_CPU_INTR_SRC9_EN_W(X)  ((X) << CPR_CPU_INTR_SRC9_EN_POS)
#define CPR_CPU_INTR_SRC10_EN_POS  (10U)
#define CPR_CPU_INTR_SRC10_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC10_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC10_EN      CPR_CPU_INTR_SRC10_EN_MSK
#define CPR_CPU_INTR_SRC10_EN_W(X) ((X) << CPR_CPU_INTR_SRC10_EN_POS)
#define CPR_CPU_INTR_SRC11_EN_POS  (11U)
#define CPR_CPU_INTR_SRC11_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC11_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC11_EN      CPR_CPU_INTR_SRC11_EN_MSK
#define CPR_CPU_INTR_SRC11_EN_W(X) ((X) << CPR_CPU_INTR_SRC11_EN_POS)
#define CPR_CPU_INTR_SRC12_EN_POS  (12U)
#define CPR_CPU_INTR_SRC12_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC12_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC12_EN      CPR_CPU_INTR_SRC12_EN_MSK
#define CPR_CPU_INTR_SRC12_EN_W(X) ((X) << CPR_CPU_INTR_SRC12_EN_POS)
#define CPR_CPU_INTR_SRC13_EN_POS  (13U)
#define CPR_CPU_INTR_SRC13_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC13_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC13_EN      CPR_CPU_INTR_SRC13_EN_MSK
#define CPR_CPU_INTR_SRC13_EN_W(X) ((X) << CPR_CPU_INTR_SRC13_EN_POS)
#define CPR_CPU_INTR_SRC14_EN_POS  (14U)
#define CPR_CPU_INTR_SRC14_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC14_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC14_EN      CPR_CPU_INTR_SRC14_EN_MSK
#define CPR_CPU_INTR_SRC14_EN_W(X) ((X) << CPR_CPU_INTR_SRC14_EN_POS)
#define CPR_CPU_INTR_SRC15_EN_POS  (15U)
#define CPR_CPU_INTR_SRC15_EN_MSK  (0x1UL << CPR_CPU_INTR_SRC15_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_INTR_SRC15_EN      CPR_CPU_INTR_SRC15_EN_MSK
#define CPR_CPU_INTR_SRC15_EN_W(X) ((X) << CPR_CPU_INTR_SRC15_EN_POS)

//SYS_CTL_CPU_INTR_STATUS0 offsetaddress : 0x258
//SYS_CTL_CPU_INTR_STATUS0 RegResetValue : 0x0
#define CPR_CPU_INTR_SRC0_STA_POS   (0U)
#define CPR_CPU_INTR_SRC0_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC0_STA_POS) /*!< When the interrupt counter of the interrupt source is not 0 and intr_srcx_en and intr_en are both 1, the interrupt status is 1. Writing 1 to this register will cause the interrupt counter to be reduced by 1*/
#define CPR_CPU_INTR_SRC0_STA       CPR_CPU_INTR_SRC0_STA_MSK
#define CPR_CPU_INTR_SRC0_STA_W(X)  ((X) << CPR_CPU_INTR_SRC0_STA_POS)
#define CPR_CPU_INTR_SRC1_STA_POS   (1U)
#define CPR_CPU_INTR_SRC1_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC1_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC1_STA       CPR_CPU_INTR_SRC1_STA_MSK
#define CPR_CPU_INTR_SRC1_STA_W(X)  ((X) << CPR_CPU_INTR_SRC1_STA_POS)
#define CPR_CPU_INTR_SRC2_STA_POS   (2U)
#define CPR_CPU_INTR_SRC2_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC2_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC2_STA       CPR_CPU_INTR_SRC2_STA_MSK
#define CPR_CPU_INTR_SRC2_STA_W(X)  ((X) << CPR_CPU_INTR_SRC2_STA_POS)
#define CPR_CPU_INTR_SRC3_STA_POS   (3U)
#define CPR_CPU_INTR_SRC3_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC3_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC3_STA       CPR_CPU_INTR_SRC3_STA_MSK
#define CPR_CPU_INTR_SRC3_STA_W(X)  ((X) << CPR_CPU_INTR_SRC3_STA_POS)
#define CPR_CPU_INTR_SRC4_STA_POS   (4U)
#define CPR_CPU_INTR_SRC4_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC4_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC4_STA       CPR_CPU_INTR_SRC4_STA_MSK
#define CPR_CPU_INTR_SRC4_STA_W(X)  ((X) << CPR_CPU_INTR_SRC4_STA_POS)
#define CPR_CPU_INTR_SRC5_STA_POS   (5U)
#define CPR_CPU_INTR_SRC5_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC5_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC5_STA       CPR_CPU_INTR_SRC5_STA_MSK
#define CPR_CPU_INTR_SRC5_STA_W(X)  ((X) << CPR_CPU_INTR_SRC5_STA_POS)
#define CPR_CPU_INTR_SRC6_STA_POS   (6U)
#define CPR_CPU_INTR_SRC6_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC6_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC6_STA       CPR_CPU_INTR_SRC6_STA_MSK
#define CPR_CPU_INTR_SRC6_STA_W(X)  ((X) << CPR_CPU_INTR_SRC6_STA_POS)
#define CPR_CPU_INTR_SRC7_STA_POS   (7U)
#define CPR_CPU_INTR_SRC7_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC7_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC7_STA       CPR_CPU_INTR_SRC7_STA_MSK
#define CPR_CPU_INTR_SRC7_STA_W(X)  ((X) << CPR_CPU_INTR_SRC7_STA_POS)
#define CPR_CPU_INTR_SRC8_STA_POS   (8U)
#define CPR_CPU_INTR_SRC8_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC8_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC8_STA       CPR_CPU_INTR_SRC8_STA_MSK
#define CPR_CPU_INTR_SRC8_STA_W(X)  ((X) << CPR_CPU_INTR_SRC8_STA_POS)
#define CPR_CPU_INTR_SRC9_STA_POS   (9U)
#define CPR_CPU_INTR_SRC9_STA_MSK   (0x1UL << CPR_CPU_INTR_SRC9_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC9_STA       CPR_CPU_INTR_SRC9_STA_MSK
#define CPR_CPU_INTR_SRC9_STA_W(X)  ((X) << CPR_CPU_INTR_SRC9_STA_POS)
#define CPR_CPU_INTR_SRC10_STA_POS  (10U)
#define CPR_CPU_INTR_SRC10_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC10_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC10_STA      CPR_CPU_INTR_SRC10_STA_MSK
#define CPR_CPU_INTR_SRC10_STA_W(X) ((X) << CPR_CPU_INTR_SRC10_STA_POS)
#define CPR_CPU_INTR_SRC11_STA_POS  (11U)
#define CPR_CPU_INTR_SRC11_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC11_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC11_STA      CPR_CPU_INTR_SRC11_STA_MSK
#define CPR_CPU_INTR_SRC11_STA_W(X) ((X) << CPR_CPU_INTR_SRC11_STA_POS)
#define CPR_CPU_INTR_SRC12_STA_POS  (12U)
#define CPR_CPU_INTR_SRC12_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC12_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC12_STA      CPR_CPU_INTR_SRC12_STA_MSK
#define CPR_CPU_INTR_SRC12_STA_W(X) ((X) << CPR_CPU_INTR_SRC12_STA_POS)
#define CPR_CPU_INTR_SRC13_STA_POS  (13U)
#define CPR_CPU_INTR_SRC13_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC13_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC13_STA      CPR_CPU_INTR_SRC13_STA_MSK
#define CPR_CPU_INTR_SRC13_STA_W(X) ((X) << CPR_CPU_INTR_SRC13_STA_POS)
#define CPR_CPU_INTR_SRC14_STA_POS  (14U)
#define CPR_CPU_INTR_SRC14_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC14_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC14_STA      CPR_CPU_INTR_SRC14_STA_MSK
#define CPR_CPU_INTR_SRC14_STA_W(X) ((X) << CPR_CPU_INTR_SRC14_STA_POS)
#define CPR_CPU_INTR_SRC15_STA_POS  (15U)
#define CPR_CPU_INTR_SRC15_STA_MSK  (0x1UL << CPR_CPU_INTR_SRC15_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_INTR_SRC15_STA      CPR_CPU_INTR_SRC15_STA_MSK
#define CPR_CPU_INTR_SRC15_STA_W(X) ((X) << CPR_CPU_INTR_SRC15_STA_POS)

//SYS_CTL_CPU_INTR_RAW offsetaddress : 0x260
//SYS_CTL_CPU_INTR_RAW RegResetValue : 0x0
#define CPR_CPU_INTR_SRC0_RAW_POS   (0U)
#define CPR_CPU_INTR_SRC0_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC0_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC0_RAW       CPR_CPU_INTR_SRC0_RAW_MSK
#define CPR_CPU_INTR_SRC0_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC0_RAW_POS)
#define CPR_CPU_INTR_SRC1_RAW_POS   (2U)
#define CPR_CPU_INTR_SRC1_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC1_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC1_RAW       CPR_CPU_INTR_SRC1_RAW_MSK
#define CPR_CPU_INTR_SRC1_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC1_RAW_POS)
#define CPR_CPU_INTR_SRC2_RAW_POS   (4U)
#define CPR_CPU_INTR_SRC2_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC2_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC2_RAW       CPR_CPU_INTR_SRC2_RAW_MSK
#define CPR_CPU_INTR_SRC2_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC2_RAW_POS)
#define CPR_CPU_INTR_SRC3_RAW_POS   (6U)
#define CPR_CPU_INTR_SRC3_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC3_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC3_RAW       CPR_CPU_INTR_SRC3_RAW_MSK
#define CPR_CPU_INTR_SRC3_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC3_RAW_POS)
#define CPR_CPU_INTR_SRC4_RAW_POS   (8U)
#define CPR_CPU_INTR_SRC4_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC4_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC4_RAW       CPR_CPU_INTR_SRC4_RAW_MSK
#define CPR_CPU_INTR_SRC4_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC4_RAW_POS)
#define CPR_CPU_INTR_SRC5_RAW_POS   (10U)
#define CPR_CPU_INTR_SRC5_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC5_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC5_RAW       CPR_CPU_INTR_SRC5_RAW_MSK
#define CPR_CPU_INTR_SRC5_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC5_RAW_POS)
#define CPR_CPU_INTR_SRC6_RAW_POS   (12U)
#define CPR_CPU_INTR_SRC6_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC6_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC6_RAW       CPR_CPU_INTR_SRC6_RAW_MSK
#define CPR_CPU_INTR_SRC6_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC6_RAW_POS)
#define CPR_CPU_INTR_SRC7_RAW_POS   (14U)
#define CPR_CPU_INTR_SRC7_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC7_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC7_RAW       CPR_CPU_INTR_SRC7_RAW_MSK
#define CPR_CPU_INTR_SRC7_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC7_RAW_POS)
#define CPR_CPU_INTR_SRC8_RAW_POS   (16U)
#define CPR_CPU_INTR_SRC8_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC8_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC8_RAW       CPR_CPU_INTR_SRC8_RAW_MSK
#define CPR_CPU_INTR_SRC8_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC8_RAW_POS)
#define CPR_CPU_INTR_SRC9_RAW_POS   (18U)
#define CPR_CPU_INTR_SRC9_RAW_MSK   (0x3UL << CPR_CPU_INTR_SRC9_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC9_RAW       CPR_CPU_INTR_SRC9_RAW_MSK
#define CPR_CPU_INTR_SRC9_RAW_W(X)  ((X) << CPR_CPU_INTR_SRC9_RAW_POS)
#define CPR_CPU_INTR_SRC10_RAW_POS  (20U)
#define CPR_CPU_INTR_SRC10_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC10_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC10_RAW      CPR_CPU_INTR_SRC10_RAW_MSK
#define CPR_CPU_INTR_SRC10_RAW_W(X) ((X) << CPR_CPU_INTR_SRC10_RAW_POS)
#define CPR_CPU_INTR_SRC11_RAW_POS  (22U)
#define CPR_CPU_INTR_SRC11_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC11_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC11_RAW      CPR_CPU_INTR_SRC11_RAW_MSK
#define CPR_CPU_INTR_SRC11_RAW_W(X) ((X) << CPR_CPU_INTR_SRC11_RAW_POS)
#define CPR_CPU_INTR_SRC12_RAW_POS  (24U)
#define CPR_CPU_INTR_SRC12_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC12_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC12_RAW      CPR_CPU_INTR_SRC12_RAW_MSK
#define CPR_CPU_INTR_SRC12_RAW_W(X) ((X) << CPR_CPU_INTR_SRC12_RAW_POS)
#define CPR_CPU_INTR_SRC13_RAW_POS  (26U)
#define CPR_CPU_INTR_SRC13_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC13_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC13_RAW      CPR_CPU_INTR_SRC13_RAW_MSK
#define CPR_CPU_INTR_SRC13_RAW_W(X) ((X) << CPR_CPU_INTR_SRC13_RAW_POS)
#define CPR_CPU_INTR_SRC14_RAW_POS  (28U)
#define CPR_CPU_INTR_SRC14_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC14_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC14_RAW      CPR_CPU_INTR_SRC14_RAW_MSK
#define CPR_CPU_INTR_SRC14_RAW_W(X) ((X) << CPR_CPU_INTR_SRC14_RAW_POS)
#define CPR_CPU_INTR_SRC15_RAW_POS  (30U)
#define CPR_CPU_INTR_SRC15_RAW_MSK  (0x3UL << CPR_CPU_INTR_SRC15_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_INTR_SRC15_RAW      CPR_CPU_INTR_SRC15_RAW_MSK
#define CPR_CPU_INTR_SRC15_RAW_W(X) ((X) << CPR_CPU_INTR_SRC15_RAW_POS)

//SYS_CTL_CPU2_INTR_SET0 offsetaddress : 0x280
//SYS_CTL_CPU2_INTR_SET0 RegResetValue : 0x0
#define CPR_CPU2_INTR_SET0_POS  (0U)
#define CPR_CPU2_INTR_SET0_MSK  (0x1UL << CPR_CPU2_INTR_SET0_POS) /*!< */
#define CPR_CPU2_INTR_SET0      CPR_CPU2_INTR_SET0_MSK
#define CPR_CPU2_INTR_SET1_POS  (1U)
#define CPR_CPU2_INTR_SET1_MSK  (0x1UL << CPR_CPU2_INTR_SET1_POS) /*!< */
#define CPR_CPU2_INTR_SET1      CPR_CPU2_INTR_SET1_MSK
#define CPR_CPU2_INTR_SET2_POS  (2U)
#define CPR_CPU2_INTR_SET2_MSK  (0x1UL << CPR_CPU2_INTR_SET2_POS) /*!< */
#define CPR_CPU2_INTR_SET2      CPR_CPU2_INTR_SET2_MSK
#define CPR_CPU2_INTR_SET3_POS  (3U)
#define CPR_CPU2_INTR_SET3_MSK  (0x1UL << CPR_CPU2_INTR_SET3_POS) /*!< */
#define CPR_CPU2_INTR_SET3      CPR_CPU2_INTR_SET3_MSK
#define CPR_CPU2_INTR_SET4_POS  (4U)
#define CPR_CPU2_INTR_SET4_MSK  (0x1UL << CPR_CPU2_INTR_SET4_POS) /*!< */
#define CPR_CPU2_INTR_SET4      CPR_CPU2_INTR_SET4_MSK
#define CPR_CPU2_INTR_SET5_POS  (5U)
#define CPR_CPU2_INTR_SET5_MSK  (0x1UL << CPR_CPU2_INTR_SET5_POS) /*!< */
#define CPR_CPU2_INTR_SET5      CPR_CPU2_INTR_SET5_MSK
#define CPR_CPU2_INTR_SET6_POS  (6U)
#define CPR_CPU2_INTR_SET6_MSK  (0x1UL << CPR_CPU2_INTR_SET6_POS) /*!< */
#define CPR_CPU2_INTR_SET6      CPR_CPU2_INTR_SET6_MSK
#define CPR_CPU2_INTR_SET7_POS  (7U)
#define CPR_CPU2_INTR_SET7_MSK  (0x1UL << CPR_CPU2_INTR_SET7_POS) /*!< */
#define CPR_CPU2_INTR_SET7      CPR_CPU2_INTR_SET7_MSK
#define CPR_CPU2_INTR_SET8_POS  (8U)
#define CPR_CPU2_INTR_SET8_MSK  (0x1UL << CPR_CPU2_INTR_SET8_POS) /*!< */
#define CPR_CPU2_INTR_SET8      CPR_CPU2_INTR_SET8_MSK
#define CPR_CPU2_INTR_SET9_POS  (9U)
#define CPR_CPU2_INTR_SET9_MSK  (0x1UL << CPR_CPU2_INTR_SET9_POS) /*!< */
#define CPR_CPU2_INTR_SET9      CPR_CPU2_INTR_SET9_MSK
#define CPR_CPU2_INTR_SET10_POS (10U)
#define CPR_CPU2_INTR_SET10_MSK (0x1UL << CPR_CPU2_INTR_SET10_POS) /*!< */
#define CPR_CPU2_INTR_SET10     CPR_CPU2_INTR_SET10_MSK
#define CPR_CPU2_INTR_SET11_POS (11U)
#define CPR_CPU2_INTR_SET11_MSK (0x1UL << CPR_CPU2_INTR_SET11_POS) /*!< */
#define CPR_CPU2_INTR_SET11     CPR_CPU2_INTR_SET11_MSK
#define CPR_CPU2_INTR_SET12_POS (12U)
#define CPR_CPU2_INTR_SET12_MSK (0x1UL << CPR_CPU2_INTR_SET12_POS) /*!< */
#define CPR_CPU2_INTR_SET12     CPR_CPU2_INTR_SET12_MSK
#define CPR_CPU2_INTR_SET13_POS (13U)
#define CPR_CPU2_INTR_SET13_MSK (0x1UL << CPR_CPU2_INTR_SET13_POS) /*!< */
#define CPR_CPU2_INTR_SET13     CPR_CPU2_INTR_SET13_MSK
#define CPR_CPU2_INTR_SET14_POS (14U)
#define CPR_CPU2_INTR_SET14_MSK (0x1UL << CPR_CPU2_INTR_SET14_POS) /*!< */
#define CPR_CPU2_INTR_SET14     CPR_CPU2_INTR_SET14_MSK
#define CPR_CPU2_INTR_SET15_POS (15U)
#define CPR_CPU2_INTR_SET15_MSK \
    (0x1UL                      \
     << CPR_CPU2_INTR_SET15_POS) /*!< Interrupt generation bit sent to CPU2 CPU2 writes interrupt number n, and the counter of the corresponding interrupt source n is added &quot;1&quot;. When the count value of interrupt source n is not equal to zero, if interrupt source n is enabled, SYS_CTRL sends interrupt to interrupt source n of CPU2, adding the write mask function [0]: interrupt source 0, write 0 bits to 16 bits at the same time [1]: interrupt source 1, write 1 bits to 17 bits at the same time... [15]: interrupt source 15, write 15 bits to 31 bits at the same time*/
#define CPR_CPU2_INTR_SET15 CPR_CPU2_INTR_SET15_MSK

//SYS_CTL_CPU2_INTR_CLR offsetaddress : 0x288
//SYS_CTL_CPU2_INTR_CLR RegResetValue : 0x0
#define CPR_CPU2_INTR_CLEAR_POS  (0U)
#define CPR_CPU2_INTR_CLEAR_MSK  (0xffffUL << CPR_CPU2_INTR_CLEAR_POS) /*!< Interrupt clearance sent to CPU2 [0]: Interrupt source 0 [1]: Interrupt source 1 … [15]: Interrupt source 15*/
#define CPR_CPU2_INTR_CLEAR      CPR_CPU2_INTR_CLEAR_MSK
#define CPR_CPU2_INTR_CLEAR_W(X) ((X) << CPR_CPU2_INTR_CLEAR_POS)

//SYS_CTL_CPU2_INTR_EN offsetaddress : 0x28c
//SYS_CTL_CPU2_INTR_EN RegResetValue : 0x0
#define CPR_CPU2_INTR_EN__ALL_POS  (0U)
#define CPR_CPU2_INTR_EN__ALL_MSK  (0x1UL << CPR_CPU2_INTR_EN__ALL_POS) /*!< */
#define CPR_CPU2_INTR_EN__ALL      CPR_CPU2_INTR_EN__ALL_MSK
#define CPR_CPU2_INTR_EN__ALL_W(X) ((X) << CPR_CPU2_INTR_EN__ALL_POS)

//SYS_CTL_CPU2_INTR_EN0 offsetaddress : 0x290
//SYS_CTL_CPU2_INTR_EN0 RegResetValue : 0x0
#define CPR_CPU2_INTR_SRC0_EN_POS   (0U)
#define CPR_CPU2_INTR_SRC0_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC0_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC0_EN       CPR_CPU2_INTR_SRC0_EN_MSK
#define CPR_CPU2_INTR_SRC0_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC0_EN_POS)
#define CPR_CPU2_INTR_SRC1_EN_POS   (1U)
#define CPR_CPU2_INTR_SRC1_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC1_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC1_EN       CPR_CPU2_INTR_SRC1_EN_MSK
#define CPR_CPU2_INTR_SRC1_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC1_EN_POS)
#define CPR_CPU2_INTR_SRC2_EN_POS   (2U)
#define CPR_CPU2_INTR_SRC2_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC2_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC2_EN       CPR_CPU2_INTR_SRC2_EN_MSK
#define CPR_CPU2_INTR_SRC2_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC2_EN_POS)
#define CPR_CPU2_INTR_SRC3_EN_POS   (3U)
#define CPR_CPU2_INTR_SRC3_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC3_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC3_EN       CPR_CPU2_INTR_SRC3_EN_MSK
#define CPR_CPU2_INTR_SRC3_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC3_EN_POS)
#define CPR_CPU2_INTR_SRC4_EN_POS   (4U)
#define CPR_CPU2_INTR_SRC4_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC4_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC4_EN       CPR_CPU2_INTR_SRC4_EN_MSK
#define CPR_CPU2_INTR_SRC4_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC4_EN_POS)
#define CPR_CPU2_INTR_SRC5_EN_POS   (5U)
#define CPR_CPU2_INTR_SRC5_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC5_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC5_EN       CPR_CPU2_INTR_SRC5_EN_MSK
#define CPR_CPU2_INTR_SRC5_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC5_EN_POS)
#define CPR_CPU2_INTR_SRC6_EN_POS   (6U)
#define CPR_CPU2_INTR_SRC6_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC6_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC6_EN       CPR_CPU2_INTR_SRC6_EN_MSK
#define CPR_CPU2_INTR_SRC6_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC6_EN_POS)
#define CPR_CPU2_INTR_SRC7_EN_POS   (7U)
#define CPR_CPU2_INTR_SRC7_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC7_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC7_EN       CPR_CPU2_INTR_SRC7_EN_MSK
#define CPR_CPU2_INTR_SRC7_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC7_EN_POS)
#define CPR_CPU2_INTR_SRC8_EN_POS   (8U)
#define CPR_CPU2_INTR_SRC8_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC8_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC8_EN       CPR_CPU2_INTR_SRC8_EN_MSK
#define CPR_CPU2_INTR_SRC8_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC8_EN_POS)
#define CPR_CPU2_INTR_SRC9_EN_POS   (9U)
#define CPR_CPU2_INTR_SRC9_EN_MSK   (0x1UL << CPR_CPU2_INTR_SRC9_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC9_EN       CPR_CPU2_INTR_SRC9_EN_MSK
#define CPR_CPU2_INTR_SRC9_EN_W(X)  ((X) << CPR_CPU2_INTR_SRC9_EN_POS)
#define CPR_CPU2_INTR_SRC10_EN_POS  (10U)
#define CPR_CPU2_INTR_SRC10_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC10_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC10_EN      CPR_CPU2_INTR_SRC10_EN_MSK
#define CPR_CPU2_INTR_SRC10_EN_W(X) ((X) << CPR_CPU2_INTR_SRC10_EN_POS)
#define CPR_CPU2_INTR_SRC11_EN_POS  (11U)
#define CPR_CPU2_INTR_SRC11_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC11_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC11_EN      CPR_CPU2_INTR_SRC11_EN_MSK
#define CPR_CPU2_INTR_SRC11_EN_W(X) ((X) << CPR_CPU2_INTR_SRC11_EN_POS)
#define CPR_CPU2_INTR_SRC12_EN_POS  (12U)
#define CPR_CPU2_INTR_SRC12_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC12_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC12_EN      CPR_CPU2_INTR_SRC12_EN_MSK
#define CPR_CPU2_INTR_SRC12_EN_W(X) ((X) << CPR_CPU2_INTR_SRC12_EN_POS)
#define CPR_CPU2_INTR_SRC13_EN_POS  (13U)
#define CPR_CPU2_INTR_SRC13_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC13_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC13_EN      CPR_CPU2_INTR_SRC13_EN_MSK
#define CPR_CPU2_INTR_SRC13_EN_W(X) ((X) << CPR_CPU2_INTR_SRC13_EN_POS)
#define CPR_CPU2_INTR_SRC14_EN_POS  (14U)
#define CPR_CPU2_INTR_SRC14_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC14_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC14_EN      CPR_CPU2_INTR_SRC14_EN_MSK
#define CPR_CPU2_INTR_SRC14_EN_W(X) ((X) << CPR_CPU2_INTR_SRC14_EN_POS)
#define CPR_CPU2_INTR_SRC15_EN_POS  (15U)
#define CPR_CPU2_INTR_SRC15_EN_MSK  (0x1UL << CPR_CPU2_INTR_SRC15_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU2_INTR_SRC15_EN      CPR_CPU2_INTR_SRC15_EN_MSK
#define CPR_CPU2_INTR_SRC15_EN_W(X) ((X) << CPR_CPU2_INTR_SRC15_EN_POS)

//SYS_CTL_CPU2_INTR_STATUS0 offsetaddress : 0x298
//SYS_CTL_CPU2_INTR_STATUS0 RegResetValue : 0x0
#define CPR_CPU2_INTR_SRC0_STA_POS   (0U)
#define CPR_CPU2_INTR_SRC0_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC0_STA_POS) /*!< When the interrupt counter of the interrupt source is not 0 and intr_srcx_en and intr_en are both 1, the interrupt status is 1. Writing 1 to this register will cause the interrupt counter to be reduced by 1*/
#define CPR_CPU2_INTR_SRC0_STA       CPR_CPU2_INTR_SRC0_STA_MSK
#define CPR_CPU2_INTR_SRC0_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC0_STA_POS)
#define CPR_CPU2_INTR_SRC1_STA_POS   (1U)
#define CPR_CPU2_INTR_SRC1_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC1_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC1_STA       CPR_CPU2_INTR_SRC1_STA_MSK
#define CPR_CPU2_INTR_SRC1_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC1_STA_POS)
#define CPR_CPU2_INTR_SRC2_STA_POS   (2U)
#define CPR_CPU2_INTR_SRC2_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC2_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC2_STA       CPR_CPU2_INTR_SRC2_STA_MSK
#define CPR_CPU2_INTR_SRC2_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC2_STA_POS)
#define CPR_CPU2_INTR_SRC3_STA_POS   (3U)
#define CPR_CPU2_INTR_SRC3_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC3_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC3_STA       CPR_CPU2_INTR_SRC3_STA_MSK
#define CPR_CPU2_INTR_SRC3_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC3_STA_POS)
#define CPR_CPU2_INTR_SRC4_STA_POS   (4U)
#define CPR_CPU2_INTR_SRC4_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC4_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC4_STA       CPR_CPU2_INTR_SRC4_STA_MSK
#define CPR_CPU2_INTR_SRC4_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC4_STA_POS)
#define CPR_CPU2_INTR_SRC5_STA_POS   (5U)
#define CPR_CPU2_INTR_SRC5_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC5_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC5_STA       CPR_CPU2_INTR_SRC5_STA_MSK
#define CPR_CPU2_INTR_SRC5_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC5_STA_POS)
#define CPR_CPU2_INTR_SRC6_STA_POS   (6U)
#define CPR_CPU2_INTR_SRC6_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC6_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC6_STA       CPR_CPU2_INTR_SRC6_STA_MSK
#define CPR_CPU2_INTR_SRC6_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC6_STA_POS)
#define CPR_CPU2_INTR_SRC7_STA_POS   (7U)
#define CPR_CPU2_INTR_SRC7_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC7_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC7_STA       CPR_CPU2_INTR_SRC7_STA_MSK
#define CPR_CPU2_INTR_SRC7_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC7_STA_POS)
#define CPR_CPU2_INTR_SRC8_STA_POS   (8U)
#define CPR_CPU2_INTR_SRC8_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC8_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC8_STA       CPR_CPU2_INTR_SRC8_STA_MSK
#define CPR_CPU2_INTR_SRC8_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC8_STA_POS)
#define CPR_CPU2_INTR_SRC9_STA_POS   (9U)
#define CPR_CPU2_INTR_SRC9_STA_MSK   (0x1UL << CPR_CPU2_INTR_SRC9_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC9_STA       CPR_CPU2_INTR_SRC9_STA_MSK
#define CPR_CPU2_INTR_SRC9_STA_W(X)  ((X) << CPR_CPU2_INTR_SRC9_STA_POS)
#define CPR_CPU2_INTR_SRC10_STA_POS  (10U)
#define CPR_CPU2_INTR_SRC10_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC10_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC10_STA      CPR_CPU2_INTR_SRC10_STA_MSK
#define CPR_CPU2_INTR_SRC10_STA_W(X) ((X) << CPR_CPU2_INTR_SRC10_STA_POS)
#define CPR_CPU2_INTR_SRC11_STA_POS  (11U)
#define CPR_CPU2_INTR_SRC11_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC11_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC11_STA      CPR_CPU2_INTR_SRC11_STA_MSK
#define CPR_CPU2_INTR_SRC11_STA_W(X) ((X) << CPR_CPU2_INTR_SRC11_STA_POS)
#define CPR_CPU2_INTR_SRC12_STA_POS  (12U)
#define CPR_CPU2_INTR_SRC12_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC12_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC12_STA      CPR_CPU2_INTR_SRC12_STA_MSK
#define CPR_CPU2_INTR_SRC12_STA_W(X) ((X) << CPR_CPU2_INTR_SRC12_STA_POS)
#define CPR_CPU2_INTR_SRC13_STA_POS  (13U)
#define CPR_CPU2_INTR_SRC13_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC13_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC13_STA      CPR_CPU2_INTR_SRC13_STA_MSK
#define CPR_CPU2_INTR_SRC13_STA_W(X) ((X) << CPR_CPU2_INTR_SRC13_STA_POS)
#define CPR_CPU2_INTR_SRC14_STA_POS  (14U)
#define CPR_CPU2_INTR_SRC14_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC14_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC14_STA      CPR_CPU2_INTR_SRC14_STA_MSK
#define CPR_CPU2_INTR_SRC14_STA_W(X) ((X) << CPR_CPU2_INTR_SRC14_STA_POS)
#define CPR_CPU2_INTR_SRC15_STA_POS  (15U)
#define CPR_CPU2_INTR_SRC15_STA_MSK  (0x1UL << CPR_CPU2_INTR_SRC15_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU2_INTR_SRC15_STA      CPR_CPU2_INTR_SRC15_STA_MSK
#define CPR_CPU2_INTR_SRC15_STA_W(X) ((X) << CPR_CPU2_INTR_SRC15_STA_POS)

//SYS_CTL_CPU2_INTR_RAW0 offsetaddress : 0x2a0
//SYS_CTL_CPU2_INTR_RAW0 RegResetValue : 0x0
#define CPR_CPU2_INTR_SRC0_RAW_POS   (0U)
#define CPR_CPU2_INTR_SRC0_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC0_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC0_RAW       CPR_CPU2_INTR_SRC0_RAW_MSK
#define CPR_CPU2_INTR_SRC0_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC0_RAW_POS)
#define CPR_CPU2_INTR_SRC1_RAW_POS   (2U)
#define CPR_CPU2_INTR_SRC1_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC1_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC1_RAW       CPR_CPU2_INTR_SRC1_RAW_MSK
#define CPR_CPU2_INTR_SRC1_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC1_RAW_POS)
#define CPR_CPU2_INTR_SRC2_RAW_POS   (4U)
#define CPR_CPU2_INTR_SRC2_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC2_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC2_RAW       CPR_CPU2_INTR_SRC2_RAW_MSK
#define CPR_CPU2_INTR_SRC2_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC2_RAW_POS)
#define CPR_CPU2_INTR_SRC3_RAW_POS   (6U)
#define CPR_CPU2_INTR_SRC3_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC3_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC3_RAW       CPR_CPU2_INTR_SRC3_RAW_MSK
#define CPR_CPU2_INTR_SRC3_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC3_RAW_POS)
#define CPR_CPU2_INTR_SRC4_RAW_POS   (8U)
#define CPR_CPU2_INTR_SRC4_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC4_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC4_RAW       CPR_CPU2_INTR_SRC4_RAW_MSK
#define CPR_CPU2_INTR_SRC4_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC4_RAW_POS)
#define CPR_CPU2_INTR_SRC5_RAW_POS   (10U)
#define CPR_CPU2_INTR_SRC5_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC5_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC5_RAW       CPR_CPU2_INTR_SRC5_RAW_MSK
#define CPR_CPU2_INTR_SRC5_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC5_RAW_POS)
#define CPR_CPU2_INTR_SRC6_RAW_POS   (12U)
#define CPR_CPU2_INTR_SRC6_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC6_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC6_RAW       CPR_CPU2_INTR_SRC6_RAW_MSK
#define CPR_CPU2_INTR_SRC6_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC6_RAW_POS)
#define CPR_CPU2_INTR_SRC7_RAW_POS   (14U)
#define CPR_CPU2_INTR_SRC7_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC7_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC7_RAW       CPR_CPU2_INTR_SRC7_RAW_MSK
#define CPR_CPU2_INTR_SRC7_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC7_RAW_POS)
#define CPR_CPU2_INTR_SRC8_RAW_POS   (16U)
#define CPR_CPU2_INTR_SRC8_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC8_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC8_RAW       CPR_CPU2_INTR_SRC8_RAW_MSK
#define CPR_CPU2_INTR_SRC8_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC8_RAW_POS)
#define CPR_CPU2_INTR_SRC9_RAW_POS   (18U)
#define CPR_CPU2_INTR_SRC9_RAW_MSK   (0x3UL << CPR_CPU2_INTR_SRC9_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC9_RAW       CPR_CPU2_INTR_SRC9_RAW_MSK
#define CPR_CPU2_INTR_SRC9_RAW_W(X)  ((X) << CPR_CPU2_INTR_SRC9_RAW_POS)
#define CPR_CPU2_INTR_SRC10_RAW_POS  (20U)
#define CPR_CPU2_INTR_SRC10_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC10_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC10_RAW      CPR_CPU2_INTR_SRC10_RAW_MSK
#define CPR_CPU2_INTR_SRC10_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC10_RAW_POS)
#define CPR_CPU2_INTR_SRC11_RAW_POS  (22U)
#define CPR_CPU2_INTR_SRC11_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC11_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC11_RAW      CPR_CPU2_INTR_SRC11_RAW_MSK
#define CPR_CPU2_INTR_SRC11_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC11_RAW_POS)
#define CPR_CPU2_INTR_SRC12_RAW_POS  (24U)
#define CPR_CPU2_INTR_SRC12_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC12_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC12_RAW      CPR_CPU2_INTR_SRC12_RAW_MSK
#define CPR_CPU2_INTR_SRC12_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC12_RAW_POS)
#define CPR_CPU2_INTR_SRC13_RAW_POS  (26U)
#define CPR_CPU2_INTR_SRC13_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC13_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC13_RAW      CPR_CPU2_INTR_SRC13_RAW_MSK
#define CPR_CPU2_INTR_SRC13_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC13_RAW_POS)
#define CPR_CPU2_INTR_SRC14_RAW_POS  (28U)
#define CPR_CPU2_INTR_SRC14_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC14_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC14_RAW      CPR_CPU2_INTR_SRC14_RAW_MSK
#define CPR_CPU2_INTR_SRC14_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC14_RAW_POS)
#define CPR_CPU2_INTR_SRC15_RAW_POS  (30U)
#define CPR_CPU2_INTR_SRC15_RAW_MSK  (0x3UL << CPR_CPU2_INTR_SRC15_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU2_INTR_SRC15_RAW      CPR_CPU2_INTR_SRC15_RAW_MSK
#define CPR_CPU2_INTR_SRC15_RAW_W(X) ((X) << CPR_CPU2_INTR_SRC15_RAW_POS)

//SYS_CTL_CPU_AP_INTR_SET0 offsetaddress : 0x2c0
//SYS_CTL_CPU_AP_INTR_SET0 RegResetValue : 0x0
#define CPR_CPU_AP_INTR_SET0_POS  (0U)
#define CPR_CPU_AP_INTR_SET0_MSK  (0x1UL << CPR_CPU_AP_INTR_SET0_POS) /*!< */
#define CPR_CPU_AP_INTR_SET0      CPR_CPU_AP_INTR_SET0_MSK
#define CPR_CPU_AP_INTR_SET1_POS  (1U)
#define CPR_CPU_AP_INTR_SET1_MSK  (0x1UL << CPR_CPU_AP_INTR_SET1_POS) /*!< */
#define CPR_CPU_AP_INTR_SET1      CPR_CPU_AP_INTR_SET1_MSK
#define CPR_CPU_AP_INTR_SET2_POS  (2U)
#define CPR_CPU_AP_INTR_SET2_MSK  (0x1UL << CPR_CPU_AP_INTR_SET2_POS) /*!< */
#define CPR_CPU_AP_INTR_SET2      CPR_CPU_AP_INTR_SET2_MSK
#define CPR_CPU_AP_INTR_SET3_POS  (3U)
#define CPR_CPU_AP_INTR_SET3_MSK  (0x1UL << CPR_CPU_AP_INTR_SET3_POS) /*!< */
#define CPR_CPU_AP_INTR_SET3      CPR_CPU_AP_INTR_SET3_MSK
#define CPR_CPU_AP_INTR_SET4_POS  (4U)
#define CPR_CPU_AP_INTR_SET4_MSK  (0x1UL << CPR_CPU_AP_INTR_SET4_POS) /*!< */
#define CPR_CPU_AP_INTR_SET4      CPR_CPU_AP_INTR_SET4_MSK
#define CPR_CPU_AP_INTR_SET5_POS  (5U)
#define CPR_CPU_AP_INTR_SET5_MSK  (0x1UL << CPR_CPU_AP_INTR_SET5_POS) /*!< */
#define CPR_CPU_AP_INTR_SET5      CPR_CPU_AP_INTR_SET5_MSK
#define CPR_CPU_AP_INTR_SET6_POS  (6U)
#define CPR_CPU_AP_INTR_SET6_MSK  (0x1UL << CPR_CPU_AP_INTR_SET6_POS) /*!< */
#define CPR_CPU_AP_INTR_SET6      CPR_CPU_AP_INTR_SET6_MSK
#define CPR_CPU_AP_INTR_SET7_POS  (7U)
#define CPR_CPU_AP_INTR_SET7_MSK  (0x1UL << CPR_CPU_AP_INTR_SET7_POS) /*!< */
#define CPR_CPU_AP_INTR_SET7      CPR_CPU_AP_INTR_SET7_MSK
#define CPR_CPU_AP_INTR_SET8_POS  (8U)
#define CPR_CPU_AP_INTR_SET8_MSK  (0x1UL << CPR_CPU_AP_INTR_SET8_POS) /*!< */
#define CPR_CPU_AP_INTR_SET8      CPR_CPU_AP_INTR_SET8_MSK
#define CPR_CPU_AP_INTR_SET9_POS  (9U)
#define CPR_CPU_AP_INTR_SET9_MSK  (0x1UL << CPR_CPU_AP_INTR_SET9_POS) /*!< */
#define CPR_CPU_AP_INTR_SET9      CPR_CPU_AP_INTR_SET9_MSK
#define CPR_CPU_AP_INTR_SET10_POS (10U)
#define CPR_CPU_AP_INTR_SET10_MSK (0x1UL << CPR_CPU_AP_INTR_SET10_POS) /*!< */
#define CPR_CPU_AP_INTR_SET10     CPR_CPU_AP_INTR_SET10_MSK
#define CPR_CPU_AP_INTR_SET11_POS (11U)
#define CPR_CPU_AP_INTR_SET11_MSK (0x1UL << CPR_CPU_AP_INTR_SET11_POS) /*!< */
#define CPR_CPU_AP_INTR_SET11     CPR_CPU_AP_INTR_SET11_MSK
#define CPR_CPU_AP_INTR_SET12_POS (12U)
#define CPR_CPU_AP_INTR_SET12_MSK (0x1UL << CPR_CPU_AP_INTR_SET12_POS) /*!< */
#define CPR_CPU_AP_INTR_SET12     CPR_CPU_AP_INTR_SET12_MSK
#define CPR_CPU_AP_INTR_SET13_POS (13U)
#define CPR_CPU_AP_INTR_SET13_MSK (0x1UL << CPR_CPU_AP_INTR_SET13_POS) /*!< */
#define CPR_CPU_AP_INTR_SET13     CPR_CPU_AP_INTR_SET13_MSK
#define CPR_CPU_AP_INTR_SET14_POS (14U)
#define CPR_CPU_AP_INTR_SET14_MSK (0x1UL << CPR_CPU_AP_INTR_SET14_POS) /*!< */
#define CPR_CPU_AP_INTR_SET14     CPR_CPU_AP_INTR_SET14_MSK
#define CPR_CPU_AP_INTR_SET15_POS (15U)
#define CPR_CPU_AP_INTR_SET15_MSK \
    (0x1UL                        \
     << CPR_CPU_AP_INTR_SET15_POS) /*!< The interrupt generation bit sent to the AP When the AP writes the interrupt number n, the counter of the corresponding interrupt source n is added &quot;1&quot;. When the count value of the interrupt source n is not equal to zero, if the interrupt source n is enabled, SYS_CTRL sends an interrupt to the interrupt source n of the AP, adding the write mask function [0]: interrupt source 0, write 0 bits to 16 bits at the same time [1]: interrupt source 1, write 1 bits to 17 bits at the same time... [15]: interrupt source 15, write 15 bits to 31 bits at the same time*/
#define CPR_CPU_AP_INTR_SET15 CPR_CPU_AP_INTR_SET15_MSK

//SYS_CTL_CPU_AP_INTR_CLR offsetaddress : 0x2c8
//SYS_CTL_CPU_AP_INTR_CLR RegResetValue : 0x0
#define CPR_CPU_AP_INTR_CLR_POS  (0U)
#define CPR_CPU_AP_INTR_CLR_MSK  (0xffffUL << CPR_CPU_AP_INTR_CLR_POS) /*!< Interrupt clearance sent to the CPU [0]: Interrupt source 0 [1]: Interrupt source 1 … [15]: Interrupt source 15*/
#define CPR_CPU_AP_INTR_CLR      CPR_CPU_AP_INTR_CLR_MSK
#define CPR_CPU_AP_INTR_CLR_W(X) ((X) << CPR_CPU_AP_INTR_CLR_POS)

//SYS_CTL_CPU_AP_INTR_EN offsetaddress : 0x2cc
//SYS_CTL_CPU_AP_INTR_EN RegResetValue : 0x0
#define CPR_CPU_AP_INTR_ALL_EN_POS  (0U)
#define CPR_CPU_AP_INTR_ALL_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_ALL_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_ALL_EN      CPR_CPU_AP_INTR_ALL_EN_MSK
#define CPR_CPU_AP_INTR_ALL_EN_W(X) ((X) << CPR_CPU_AP_INTR_ALL_EN_POS)
#define CPR_RESERVED_POS            (1U)
#define CPR_RESERVED_MSK            (0x7fffffffUL << CPR_RESERVED_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_RESERVED                CPR_RESERVED_MSK
#define CPR_RESERVED_W(X)           ((X) << CPR_RESERVED_POS)

//SYS_CTL_CPU_AP_INTR_EN0 offsetaddress : 0x2d0
//SYS_CTL_CPU_AP_INTR_EN0 RegResetValue : 0x0
#define CPR_CPU_AP_INTR_SRC0_EN_POS   (0U)
#define CPR_CPU_AP_INTR_SRC0_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC0_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC0_EN       CPR_CPU_AP_INTR_SRC0_EN_MSK
#define CPR_CPU_AP_INTR_SRC0_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC0_EN_POS)
#define CPR_CPU_AP_INTR_SRC1_EN_POS   (1U)
#define CPR_CPU_AP_INTR_SRC1_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC1_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC1_EN       CPR_CPU_AP_INTR_SRC1_EN_MSK
#define CPR_CPU_AP_INTR_SRC1_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC1_EN_POS)
#define CPR_CPU_AP_INTR_SRC2_EN_POS   (2U)
#define CPR_CPU_AP_INTR_SRC2_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC2_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC2_EN       CPR_CPU_AP_INTR_SRC2_EN_MSK
#define CPR_CPU_AP_INTR_SRC2_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC2_EN_POS)
#define CPR_CPU_AP_INTR_SRC3_EN_POS   (3U)
#define CPR_CPU_AP_INTR_SRC3_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC3_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC3_EN       CPR_CPU_AP_INTR_SRC3_EN_MSK
#define CPR_CPU_AP_INTR_SRC3_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC3_EN_POS)
#define CPR_CPU_AP_INTR_SRC4_EN_POS   (4U)
#define CPR_CPU_AP_INTR_SRC4_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC4_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC4_EN       CPR_CPU_AP_INTR_SRC4_EN_MSK
#define CPR_CPU_AP_INTR_SRC4_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC4_EN_POS)
#define CPR_CPU_AP_INTR_SRC5_EN_POS   (5U)
#define CPR_CPU_AP_INTR_SRC5_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC5_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC5_EN       CPR_CPU_AP_INTR_SRC5_EN_MSK
#define CPR_CPU_AP_INTR_SRC5_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC5_EN_POS)
#define CPR_CPU_AP_INTR_SRC6_EN_POS   (6U)
#define CPR_CPU_AP_INTR_SRC6_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC6_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC6_EN       CPR_CPU_AP_INTR_SRC6_EN_MSK
#define CPR_CPU_AP_INTR_SRC6_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC6_EN_POS)
#define CPR_CPU_AP_INTR_SRC7_EN_POS   (7U)
#define CPR_CPU_AP_INTR_SRC7_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC7_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC7_EN       CPR_CPU_AP_INTR_SRC7_EN_MSK
#define CPR_CPU_AP_INTR_SRC7_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC7_EN_POS)
#define CPR_CPU_AP_INTR_SRC8_EN_POS   (8U)
#define CPR_CPU_AP_INTR_SRC8_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC8_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC8_EN       CPR_CPU_AP_INTR_SRC8_EN_MSK
#define CPR_CPU_AP_INTR_SRC8_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC8_EN_POS)
#define CPR_CPU_AP_INTR_SRC9_EN_POS   (9U)
#define CPR_CPU_AP_INTR_SRC9_EN_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC9_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC9_EN       CPR_CPU_AP_INTR_SRC9_EN_MSK
#define CPR_CPU_AP_INTR_SRC9_EN_W(X)  ((X) << CPR_CPU_AP_INTR_SRC9_EN_POS)
#define CPR_CPU_AP_INTR_SRC10_EN_POS  (10U)
#define CPR_CPU_AP_INTR_SRC10_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC10_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC10_EN      CPR_CPU_AP_INTR_SRC10_EN_MSK
#define CPR_CPU_AP_INTR_SRC10_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC10_EN_POS)
#define CPR_CPU_AP_INTR_SRC11_EN_POS  (11U)
#define CPR_CPU_AP_INTR_SRC11_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC11_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC11_EN      CPR_CPU_AP_INTR_SRC11_EN_MSK
#define CPR_CPU_AP_INTR_SRC11_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC11_EN_POS)
#define CPR_CPU_AP_INTR_SRC12_EN_POS  (12U)
#define CPR_CPU_AP_INTR_SRC12_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC12_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC12_EN      CPR_CPU_AP_INTR_SRC12_EN_MSK
#define CPR_CPU_AP_INTR_SRC12_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC12_EN_POS)
#define CPR_CPU_AP_INTR_SRC13_EN_POS  (13U)
#define CPR_CPU_AP_INTR_SRC13_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC13_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC13_EN      CPR_CPU_AP_INTR_SRC13_EN_MSK
#define CPR_CPU_AP_INTR_SRC13_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC13_EN_POS)
#define CPR_CPU_AP_INTR_SRC14_EN_POS  (14U)
#define CPR_CPU_AP_INTR_SRC14_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC14_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC14_EN      CPR_CPU_AP_INTR_SRC14_EN_MSK
#define CPR_CPU_AP_INTR_SRC14_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC14_EN_POS)
#define CPR_CPU_AP_INTR_SRC15_EN_POS  (15U)
#define CPR_CPU_AP_INTR_SRC15_EN_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC15_EN_POS) /*!< 0: Not enabled; 1: Enable*/
#define CPR_CPU_AP_INTR_SRC15_EN      CPR_CPU_AP_INTR_SRC15_EN_MSK
#define CPR_CPU_AP_INTR_SRC15_EN_W(X) ((X) << CPR_CPU_AP_INTR_SRC15_EN_POS)

//SYS_CTL_CPU_AP_INTR_STATUS0 offsetaddress : 0x2d8
//SYS_CTL_CPU_AP_INTR_STATUS0 RegResetValue : 0x0
#define CPR_CPU_AP_INTR_SRC0_STA_POS   (0U)
#define CPR_CPU_AP_INTR_SRC0_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC0_STA_POS) /*!< When the interrupt counter of the interrupt source is not 0, and intr_srcx_en and intr_en are both 1, the interrupt status is 1*/
#define CPR_CPU_AP_INTR_SRC0_STA       CPR_CPU_AP_INTR_SRC0_STA_MSK
#define CPR_CPU_AP_INTR_SRC0_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC0_STA_POS)
#define CPR_CPU_AP_INTR_SRC1_STA_POS   (1U)
#define CPR_CPU_AP_INTR_SRC1_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC1_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC1_STA       CPR_CPU_AP_INTR_SRC1_STA_MSK
#define CPR_CPU_AP_INTR_SRC1_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC1_STA_POS)
#define CPR_CPU_AP_INTR_SRC2_STA_POS   (2U)
#define CPR_CPU_AP_INTR_SRC2_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC2_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC2_STA       CPR_CPU_AP_INTR_SRC2_STA_MSK
#define CPR_CPU_AP_INTR_SRC2_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC2_STA_POS)
#define CPR_CPU_AP_INTR_SRC3_STA_POS   (3U)
#define CPR_CPU_AP_INTR_SRC3_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC3_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC3_STA       CPR_CPU_AP_INTR_SRC3_STA_MSK
#define CPR_CPU_AP_INTR_SRC3_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC3_STA_POS)
#define CPR_CPU_AP_INTR_SRC4_STA_POS   (4U)
#define CPR_CPU_AP_INTR_SRC4_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC4_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC4_STA       CPR_CPU_AP_INTR_SRC4_STA_MSK
#define CPR_CPU_AP_INTR_SRC4_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC4_STA_POS)
#define CPR_CPU_AP_INTR_SRC5_STA_POS   (5U)
#define CPR_CPU_AP_INTR_SRC5_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC5_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC5_STA       CPR_CPU_AP_INTR_SRC5_STA_MSK
#define CPR_CPU_AP_INTR_SRC5_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC5_STA_POS)
#define CPR_CPU_AP_INTR_SRC6_STA_POS   (6U)
#define CPR_CPU_AP_INTR_SRC6_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC6_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC6_STA       CPR_CPU_AP_INTR_SRC6_STA_MSK
#define CPR_CPU_AP_INTR_SRC6_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC6_STA_POS)
#define CPR_CPU_AP_INTR_SRC7_STA_POS   (7U)
#define CPR_CPU_AP_INTR_SRC7_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC7_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC7_STA       CPR_CPU_AP_INTR_SRC7_STA_MSK
#define CPR_CPU_AP_INTR_SRC7_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC7_STA_POS)
#define CPR_CPU_AP_INTR_SRC8_STA_POS   (8U)
#define CPR_CPU_AP_INTR_SRC8_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC8_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC8_STA       CPR_CPU_AP_INTR_SRC8_STA_MSK
#define CPR_CPU_AP_INTR_SRC8_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC8_STA_POS)
#define CPR_CPU_AP_INTR_SRC9_STA_POS   (9U)
#define CPR_CPU_AP_INTR_SRC9_STA_MSK   (0x1UL << CPR_CPU_AP_INTR_SRC9_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC9_STA       CPR_CPU_AP_INTR_SRC9_STA_MSK
#define CPR_CPU_AP_INTR_SRC9_STA_W(X)  ((X) << CPR_CPU_AP_INTR_SRC9_STA_POS)
#define CPR_CPU_AP_INTR_SRC10_STA_POS  (10U)
#define CPR_CPU_AP_INTR_SRC10_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC10_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC10_STA      CPR_CPU_AP_INTR_SRC10_STA_MSK
#define CPR_CPU_AP_INTR_SRC10_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC10_STA_POS)
#define CPR_CPU_AP_INTR_SRC11_STA_POS  (11U)
#define CPR_CPU_AP_INTR_SRC11_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC11_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC11_STA      CPR_CPU_AP_INTR_SRC11_STA_MSK
#define CPR_CPU_AP_INTR_SRC11_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC11_STA_POS)
#define CPR_CPU_AP_INTR_SRC12_STA_POS  (12U)
#define CPR_CPU_AP_INTR_SRC12_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC12_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC12_STA      CPR_CPU_AP_INTR_SRC12_STA_MSK
#define CPR_CPU_AP_INTR_SRC12_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC12_STA_POS)
#define CPR_CPU_AP_INTR_SRC13_STA_POS  (13U)
#define CPR_CPU_AP_INTR_SRC13_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC13_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC13_STA      CPR_CPU_AP_INTR_SRC13_STA_MSK
#define CPR_CPU_AP_INTR_SRC13_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC13_STA_POS)
#define CPR_CPU_AP_INTR_SRC14_STA_POS  (14U)
#define CPR_CPU_AP_INTR_SRC14_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC14_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC14_STA      CPR_CPU_AP_INTR_SRC14_STA_MSK
#define CPR_CPU_AP_INTR_SRC14_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC14_STA_POS)
#define CPR_CPU_AP_INTR_SRC15_STA_POS  (15U)
#define CPR_CPU_AP_INTR_SRC15_STA_MSK  (0x1UL << CPR_CPU_AP_INTR_SRC15_STA_POS) /*!< Description same as bit 0*/
#define CPR_CPU_AP_INTR_SRC15_STA      CPR_CPU_AP_INTR_SRC15_STA_MSK
#define CPR_CPU_AP_INTR_SRC15_STA_W(X) ((X) << CPR_CPU_AP_INTR_SRC15_STA_POS)

//SYS_CTL_CPU_AP_INTR_RAW offsetaddress : 0x2e0
//SYS_CTL_CPU_AP_INTR_RAW RegResetValue : 0x0
#define CPR_CPU_AP_INTR_SRC0_RAW_POS   (0U)
#define CPR_CPU_AP_INTR_SRC0_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC0_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC0_RAW       CPR_CPU_AP_INTR_SRC0_RAW_MSK
#define CPR_CPU_AP_INTR_SRC0_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC0_RAW_POS)
#define CPR_CPU_AP_INTR_SRC1_RAW_POS   (2U)
#define CPR_CPU_AP_INTR_SRC1_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC1_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC1_RAW       CPR_CPU_AP_INTR_SRC1_RAW_MSK
#define CPR_CPU_AP_INTR_SRC1_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC1_RAW_POS)
#define CPR_CPU_AP_INTR_SRC2_RAW_POS   (4U)
#define CPR_CPU_AP_INTR_SRC2_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC2_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC2_RAW       CPR_CPU_AP_INTR_SRC2_RAW_MSK
#define CPR_CPU_AP_INTR_SRC2_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC2_RAW_POS)
#define CPR_CPU_AP_INTR_SRC3_RAW_POS   (6U)
#define CPR_CPU_AP_INTR_SRC3_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC3_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC3_RAW       CPR_CPU_AP_INTR_SRC3_RAW_MSK
#define CPR_CPU_AP_INTR_SRC3_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC3_RAW_POS)
#define CPR_CPU_AP_INTR_SRC4_RAW_POS   (8U)
#define CPR_CPU_AP_INTR_SRC4_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC4_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC4_RAW       CPR_CPU_AP_INTR_SRC4_RAW_MSK
#define CPR_CPU_AP_INTR_SRC4_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC4_RAW_POS)
#define CPR_CPU_AP_INTR_SRC5_RAW_POS   (10U)
#define CPR_CPU_AP_INTR_SRC5_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC5_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC5_RAW       CPR_CPU_AP_INTR_SRC5_RAW_MSK
#define CPR_CPU_AP_INTR_SRC5_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC5_RAW_POS)
#define CPR_CPU_AP_INTR_SRC6_RAW_POS   (12U)
#define CPR_CPU_AP_INTR_SRC6_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC6_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC6_RAW       CPR_CPU_AP_INTR_SRC6_RAW_MSK
#define CPR_CPU_AP_INTR_SRC6_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC6_RAW_POS)
#define CPR_CPU_AP_INTR_SRC7_RAW_POS   (14U)
#define CPR_CPU_AP_INTR_SRC7_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC7_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC7_RAW       CPR_CPU_AP_INTR_SRC7_RAW_MSK
#define CPR_CPU_AP_INTR_SRC7_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC7_RAW_POS)
#define CPR_CPU_AP_INTR_SRC8_RAW_POS   (16U)
#define CPR_CPU_AP_INTR_SRC8_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC8_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC8_RAW       CPR_CPU_AP_INTR_SRC8_RAW_MSK
#define CPR_CPU_AP_INTR_SRC8_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC8_RAW_POS)
#define CPR_CPU_AP_INTR_SRC9_RAW_POS   (18U)
#define CPR_CPU_AP_INTR_SRC9_RAW_MSK   (0x3UL << CPR_CPU_AP_INTR_SRC9_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC9_RAW       CPR_CPU_AP_INTR_SRC9_RAW_MSK
#define CPR_CPU_AP_INTR_SRC9_RAW_W(X)  ((X) << CPR_CPU_AP_INTR_SRC9_RAW_POS)
#define CPR_CPU_AP_INTR_SRC10_RAW_POS  (20U)
#define CPR_CPU_AP_INTR_SRC10_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC10_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC10_RAW      CPR_CPU_AP_INTR_SRC10_RAW_MSK
#define CPR_CPU_AP_INTR_SRC10_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC10_RAW_POS)
#define CPR_CPU_AP_INTR_SRC11_RAW_POS  (22U)
#define CPR_CPU_AP_INTR_SRC11_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC11_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC11_RAW      CPR_CPU_AP_INTR_SRC11_RAW_MSK
#define CPR_CPU_AP_INTR_SRC11_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC11_RAW_POS)
#define CPR_CPU_AP_INTR_SRC12_RAW_POS  (24U)
#define CPR_CPU_AP_INTR_SRC12_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC12_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC12_RAW      CPR_CPU_AP_INTR_SRC12_RAW_MSK
#define CPR_CPU_AP_INTR_SRC12_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC12_RAW_POS)
#define CPR_CPU_AP_INTR_SRC13_RAW_POS  (26U)
#define CPR_CPU_AP_INTR_SRC13_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC13_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC13_RAW      CPR_CPU_AP_INTR_SRC13_RAW_MSK
#define CPR_CPU_AP_INTR_SRC13_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC13_RAW_POS)
#define CPR_CPU_AP_INTR_SRC14_RAW_POS  (28U)
#define CPR_CPU_AP_INTR_SRC14_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC14_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC14_RAW      CPR_CPU_AP_INTR_SRC14_RAW_MSK
#define CPR_CPU_AP_INTR_SRC14_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC14_RAW_POS)
#define CPR_CPU_AP_INTR_SRC15_RAW_POS  (30U)
#define CPR_CPU_AP_INTR_SRC15_RAW_MSK  (0x3UL << CPR_CPU_AP_INTR_SRC15_RAW_POS) /*!< When the interrupt counter of the interrupt source is not 0, the interrupt original state is 1*/
#define CPR_CPU_AP_INTR_SRC15_RAW      CPR_CPU_AP_INTR_SRC15_RAW_MSK
#define CPR_CPU_AP_INTR_SRC15_RAW_W(X) ((X) << CPR_CPU_AP_INTR_SRC15_RAW_POS)

//CPU0_IPCM_VECTOR_0 offsetaddress : 0x300
//CPU0_IPCM_VECTOR_0 RegResetValue : 0x0
#define CPR_CPU0_IPCM_VEC0_POS  (0U)
#define CPR_CPU0_IPCM_VEC0_MSK  (0xffffffffUL << CPR_CPU0_IPCM_VEC0_POS) /*!< CPU0 cpu ipcm vector 0*/
#define CPR_CPU0_IPCM_VEC0      CPR_CPU0_IPCM_VEC0_MSK
#define CPR_CPU0_IPCM_VEC0_W(X) ((X) << CPR_CPU0_IPCM_VEC0_POS)

//CPU0_IPCM_VECTOR_1 offsetaddress : 0x304
//CPU0_IPCM_VECTOR_1 RegResetValue : 0x0
#define CPR_CPU0_IPCM_VEC1_POS  (0U)
#define CPR_CPU0_IPCM_VEC1_MSK  (0xffffffffUL << CPR_CPU0_IPCM_VEC1_POS) /*!< CPU0 cpu ipcm vector 1*/
#define CPR_CPU0_IPCM_VEC1      CPR_CPU0_IPCM_VEC1_MSK
#define CPR_CPU0_IPCM_VEC1_W(X) ((X) << CPR_CPU0_IPCM_VEC1_POS)

//CPU1_IPCM_VECTOR_0 offsetaddress : 0x308
//CPU1_IPCM_VECTOR_0 RegResetValue : 0x0
#define CPR_CPU1_IPCM_VEC0_POS  (0U)
#define CPR_CPU1_IPCM_VEC0_MSK  (0xffffffffUL << CPR_CPU1_IPCM_VEC0_POS) /*!< CPU1 cpu ipcm vector 0*/
#define CPR_CPU1_IPCM_VEC0      CPR_CPU1_IPCM_VEC0_MSK
#define CPR_CPU1_IPCM_VEC0_W(X) ((X) << CPR_CPU1_IPCM_VEC0_POS)

//CPU1_IPCM_VECTOR_1 offsetaddress : 0x30c
//CPU1_IPCM_VECTOR_1 RegResetValue : 0x0
#define CPR_CPU1_IPCM_VEC1_POS  (0U)
#define CPR_CPU1_IPCM_VEC1_MSK  (0xffffffffUL << CPR_CPU1_IPCM_VEC1_POS) /*!< CPU1 cpu ipcm vector 1*/
#define CPR_CPU1_IPCM_VEC1      CPR_CPU1_IPCM_VEC1_MSK
#define CPR_CPU1_IPCM_VEC1_W(X) ((X) << CPR_CPU1_IPCM_VEC1_POS)

//CPU2_IPCM_VECTOR_0 offsetaddress : 0x310
//CPU2_IPCM_VECTOR_0 RegResetValue : 0x0
#define CPR_CPU2_IPCM_VEC0_POS  (0U)
#define CPR_CPU2_IPCM_VEC0_MSK  (0xffffffffUL << CPR_CPU2_IPCM_VEC0_POS) /*!< hifi5 CPU2 ipcm vector 0*/
#define CPR_CPU2_IPCM_VEC0      CPR_CPU2_IPCM_VEC0_MSK
#define CPR_CPU2_IPCM_VEC0_W(X) ((X) << CPR_CPU2_IPCM_VEC0_POS)

//CPU2_IPCM_VECTOR_1 offsetaddress : 0x314
//CPU2_IPCM_VECTOR_1 RegResetValue : 0x0
#define CPR_CPU2_IPCM_VEC1_POS  (0U)
#define CPR_CPU2_IPCM_VEC1_MSK  (0xffffffffUL << CPR_CPU2_IPCM_VEC1_POS) /*!< hifi5 CPU2 ipcm vector 1*/
#define CPR_CPU2_IPCM_VEC1      CPR_CPU2_IPCM_VEC1_MSK
#define CPR_CPU2_IPCM_VEC1_W(X) ((X) << CPR_CPU2_IPCM_VEC1_POS)

//CHIP_VERSION offsetaddress : 0x320
//CHIP_VERSION RegResetValue : 0x90620000
#define CPR_CHIP_VERSION_POS  (0U)
#define CPR_CHIP_VERSION_MSK  (0xffffUL << CPR_CHIP_VERSION_POS) /*!< chip version*/
#define CPR_CHIP_VERSION      CPR_CHIP_VERSION_MSK
#define CPR_CHIP_VERSION_W(X) ((X) << CPR_CHIP_VERSION_POS)
#define CPR_CHIP_CODE_POS     (16U)
#define CPR_CHIP_CODE_MSK     (0xffffUL << CPR_CHIP_CODE_POS) /*!< chip code*/
#define CPR_CHIP_CODE         CPR_CHIP_CODE_MSK
#define CPR_CHIP_CODE_W(X)    ((X) << CPR_CHIP_CODE_POS)

typedef struct {
    volatile uint32_t RST_SET_CPU_SYSTEM;    //offsetaddress : 0x0000
    volatile uint32_t RST_SET_MAIN_AHB_BUS0; //offsetaddress : 0x0004
    volatile uint32_t RST_SET_MAIN_AHB_BUS1; //offsetaddress : 0x0008
    volatile uint32_t RST_SET_AUDIO_BUS;     //offsetaddress : 0x000c
    volatile uint32_t RST_SET_MAIN_APB;      //offsetaddress : 0x0010
    volatile uint32_t RST_SET_FUNC0;         //offsetaddress : 0x0014
    volatile uint32_t RST_SET_FUNC1;         //offsetaddress : 0x0018
    volatile uint32_t RST_SET_AUDIO_FUNC;    //offsetaddress : 0x001c
    volatile uint32_t CLK_EN_MCU_SYSTEM;     //offsetaddress : 0x0020
    volatile uint32_t CLK_EN_AUDIO_SYSTEM;   //offsetaddress : 0x0024
    volatile uint32_t CLK_EN_RF_SYSTEM;      //offsetaddress : 0x0028
    volatile uint32_t CLK_EN_AHB;            //offsetaddress : 0x002c
    volatile uint32_t CLK_EN_APB0;           //offsetaddress : 0x0030
    volatile uint32_t CLK_EN_APB1;           //offsetaddress : 0x0034
    volatile uint32_t CLK_EN_APB2;           //offsetaddress : 0x0038
    volatile uint32_t CLK_EN_APB3;           //offsetaddress : 0x003c
    volatile uint32_t rev_0[(0x0050 - 0x003c) / 4 - 1];
    volatile uint32_t CLK_MUX;       //offsetaddress : 0x0050
    volatile uint32_t CLK_DIV_BUS;   //offsetaddress : 0x0054
    volatile uint32_t CLK_DIV_CPU;   //offsetaddress : 0x0058
    volatile uint32_t CLK_DIV_FUNC0; //offsetaddress : 0x005c
    volatile uint32_t CLK_DIV_FUNC1; //offsetaddress : 0x0060
    volatile uint32_t rev_1[(0x006c - 0x0060) / 4 - 1];
    volatile uint32_t CLK_DIV_FUNC4;  //offsetaddress : 0x006c
    volatile uint32_t CLK_DIV_FUNC5;  //offsetaddress : 0x0070
    volatile uint32_t CLK_DIV_FUNC6;  //offsetaddress : 0x0074
    volatile uint32_t CLK_DIV_AUDIO0; //offsetaddress : 0x0078
    volatile uint32_t CLK_DIV_AUDIO1; //offsetaddress : 0x007c
    volatile uint32_t CLK_DIV_AUDIO2; //offsetaddress : 0x0080
    volatile uint32_t CLK_DIV_AUDIO3; //offsetaddress : 0x0084
    volatile uint32_t CLK_DIV_AUDIO4; //offsetaddress : 0x0088
    volatile uint32_t CLK_DIV_AUDIO5; //offsetaddress : 0x008c
    volatile uint32_t CLK_DIV_AUDIO6; //offsetaddress : 0x0090
    volatile uint32_t CLK_DIV_AUDIO7; //offsetaddress : 0x0094
    volatile uint32_t CLK_DIV_AUDIO8; //offsetaddress : 0x0098
    volatile uint32_t CLK_DIV_AUDIO9; //offsetaddress : 0x009c
    volatile uint32_t CLK_DIV_APB;    //offsetaddress : 0x00a0
    volatile uint32_t CLK_DIV_PLL;    //offsetaddress : 0x00a4
    volatile uint32_t CLK_SET;        //offsetaddress : 0x00a8
    volatile uint32_t RST_CTRL;       //offsetaddress : 0x00ac
    volatile uint32_t ROM_CFG;        //offsetaddress : 0x00b0
    volatile uint32_t SHRAM_CFG;      //offsetaddress : 0x00b4
    volatile uint32_t RAM_CFG;        //offsetaddress : 0x00b8
    volatile uint32_t rev_2[(0x00c0 - 0x00b8) / 4 - 1];
    volatile uint32_t CPU1_SLP_KICK;  //offsetaddress : 0x00c0
    volatile uint32_t CPU0_SLP_KICK;  //offsetaddress : 0x00c4
    volatile uint32_t CPU1_SLP_CTRL;  //offsetaddress : 0x00c8
    volatile uint32_t CPU0_SLP_CTRL;  //offsetaddress : 0x00cc
    volatile uint32_t CPU2_REMAP_VEC; //offsetaddress : 0x00d0
    volatile uint32_t rev_3[(0x00dc - 0x00d0) / 4 - 1];
    volatile uint32_t RC_CALIB;       //offsetaddress : 0x00dc
    volatile uint32_t BT_CFG;         //offsetaddress : 0x00e0
    volatile uint32_t DMA_CTRL;       //offsetaddress : 0x00e4
    volatile uint32_t PD_CTRL;        //offsetaddress : 0x00e8
    volatile uint32_t PERI_CTRL;      //offsetaddress : 0x00ec
    volatile uint32_t CPU2_CFG;       //offsetaddress : 0x00f0
    volatile uint32_t DAC_CLK_CFG;    //offsetaddress : 0x00f4
    volatile uint32_t CLK_MUX1;       //offsetaddress : 0x00f8
    volatile uint32_t SDMMC_CLK_CFG;  //offsetaddress : 0x00fc
    volatile uint32_t PD_RAM_CTRL_0;  //offsetaddress : 0x100
    volatile uint32_t PD_RAM_CTRL_1;  //offsetaddress : 0x104
    volatile uint32_t PD_RAM_CTRL_2;  //offsetaddress : 0x108
    volatile uint32_t PD_RAM_CTRL_3;  //offsetaddress : 0x10c
    volatile uint32_t PD_RAM_CTRL_4;  //offsetaddress : 0x110
    volatile uint32_t PD_RAM_CTRL_5;  //offsetaddress : 0x114
    volatile uint32_t PD_RAM_CTRL_6;  //offsetaddress : 0x118
    volatile uint32_t PD_RAM_CTRL_7;  //offsetaddress : 0x11c
    volatile uint32_t PD_RAM_CTRL_8;  //offsetaddress : 0x120
    volatile uint32_t PD_RAM_CTRL_9;  //offsetaddress : 0x124
    volatile uint32_t PD_RAM_CTRL_10; //offsetaddress : 0x128
    volatile uint32_t rev_4[(0x130 - 0x128) / 4 - 1];
    volatile uint32_t TEMP_CTRL; //offsetaddress : 0x130
    volatile uint32_t TEMP_TH_0; //offsetaddress : 0x134
    volatile uint32_t TEMP_TH_1; //offsetaddress : 0x138
    volatile uint32_t rev_5[(0x0140 - 0x138) / 4 - 1];
    volatile uint32_t BBPLL_CFG0; //offsetaddress : 0x0140
    volatile uint32_t BBPLL_CFG1; //offsetaddress : 0x0144
    volatile uint32_t BBPLL_TEST; //offsetaddress : 0x0148
    volatile uint32_t FRAC_PLL;   //offsetaddress : 0x014c
    volatile uint32_t PLL_STAT;   //offsetaddress : 0x0150
    volatile uint32_t rev_6[(0x0160 - 0x0150) / 4 - 1];
    volatile uint32_t PGA_SCLK_DIV; //offsetaddress : 0x0160
    volatile uint32_t XIP_SW_KEYA;  //offsetaddress : 0x0164
    volatile uint32_t XIP_SW_KEYB;  //offsetaddress : 0x0168
    volatile uint32_t rev_7[(0x0170 - 0x0168) / 4 - 1];
    volatile uint32_t ARBITER0; //offsetaddress : 0x0170
    volatile uint32_t ARBITER1; //offsetaddress : 0x0174
    volatile uint32_t ARBITER2; //offsetaddress : 0x0178
    volatile uint32_t ARBITER3; //offsetaddress : 0x017c
    volatile uint32_t ARBITER4; //offsetaddress : 0x0180
    volatile uint32_t ARBITER5; //offsetaddress : 0x0184
    volatile uint32_t ARBITER6; //offsetaddress : 0x0188
    volatile uint32_t ARBITER7; //offsetaddress : 0x018c
    volatile uint32_t rev_8[(0x1e0 - 0x018c) / 4 - 1];
    volatile uint32_t PA_MUX_CTL_0; //offsetaddress : 0x1e0
    volatile uint32_t PA_MUX_CTL_1; //offsetaddress : 0x1e4
    volatile uint32_t PA_MUX_CTL_2; //offsetaddress : 0x1e8
    volatile uint32_t PA_MUX_CTL_3; //offsetaddress : 0x1ec
    volatile uint32_t PB_MUX_CTL_0; //offsetaddress : 0x1f0
    volatile uint32_t PB_MUX_CTL_1; //offsetaddress : 0x1f4
    volatile uint32_t PC_MUX_CTL;   //offsetaddress : 0x1f8
    volatile uint32_t JTAG_MUX_CTL; //offsetaddress : 0x1fc
    volatile uint32_t PA_IE_CFG;    //offsetaddress : 0x0200
    volatile uint32_t PC_IE_CFG;    //offsetaddress : 0x0204
    volatile uint32_t PA_CTRL_0;    //offsetaddress : 0x0208
    volatile uint32_t PA_CTRL_1;    //offsetaddress : 0x020c
    volatile uint32_t PA_CTRL_2;    //offsetaddress : 0x0210
    volatile uint32_t PA_CTRL_3;    //offsetaddress : 0x0214
    volatile uint32_t PA_CTRL_4;    //offsetaddress : 0x0218
    volatile uint32_t PA_CTRL_5;    //offsetaddress : 0x021c
    volatile uint32_t PC_CTRL_0;    //offsetaddress : 0x0220
    volatile uint32_t PC_CTRL_1;    //offsetaddress : 0x0224
    volatile uint32_t rev_9[(0x022c - 0x0224) / 4 - 1];
    volatile uint32_t PA_WKUP_CTRL;          //offsetaddress : 0x022c
    volatile uint32_t PA_WKUP_IRQ;           //offsetaddress : 0x0230
    volatile uint32_t PA_WKUP_CFG0;          //offsetaddress : 0x0234
    volatile uint32_t PA_WKUP_CFG1;          //offsetaddress : 0x0238
    volatile uint32_t PA_WKUP_CFG2;          //offsetaddress : 0x023c
    volatile uint32_t SYS_CTL_CPU_INTR_SET0; //offsetaddress : 0x240
    volatile uint32_t rev_10[(0x248 - 0x240) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_INTR_CLR; //offsetaddress : 0x248
    volatile uint32_t SYS_CTL_CPU_INTR_EN;  //offsetaddress : 0x24c
    volatile uint32_t SYS_CTL_CPU_INTR_EN0; //offsetaddress : 0x250
    volatile uint32_t rev_11[(0x258 - 0x250) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_INTR_STATUS0; //offsetaddress : 0x258
    volatile uint32_t rev_12[(0x260 - 0x258) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_INTR_RAW; //offsetaddress : 0x260
    volatile uint32_t rev_13[(0x280 - 0x260) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU2_INTR_SET0; //offsetaddress : 0x280
    volatile uint32_t rev_14[(0x288 - 0x280) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU2_INTR_CLR; //offsetaddress : 0x288
    volatile uint32_t SYS_CTL_CPU2_INTR_EN;  //offsetaddress : 0x28c
    volatile uint32_t SYS_CTL_CPU2_INTR_EN0; //offsetaddress : 0x290
    volatile uint32_t rev_15[(0x298 - 0x290) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU2_INTR_STATUS0; //offsetaddress : 0x298
    volatile uint32_t rev_16[(0x2a0 - 0x298) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU2_INTR_RAW0; //offsetaddress : 0x2a0
    volatile uint32_t rev_17[(0x2c0 - 0x2a0) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_AP_INTR_SET0; //offsetaddress : 0x2c0
    volatile uint32_t rev_18[(0x2c8 - 0x2c0) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_AP_INTR_CLR; //offsetaddress : 0x2c8
    volatile uint32_t SYS_CTL_CPU_AP_INTR_EN;  //offsetaddress : 0x2cc
    volatile uint32_t SYS_CTL_CPU_AP_INTR_EN0; //offsetaddress : 0x2d0
    volatile uint32_t rev_19[(0x2d8 - 0x2d0) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_AP_INTR_STATUS0; //offsetaddress : 0x2d8
    volatile uint32_t rev_20[(0x2e0 - 0x2d8) / 4 - 1];
    volatile uint32_t SYS_CTL_CPU_AP_INTR_RAW; //offsetaddress : 0x2e0
    volatile uint32_t rev_21[(0x300 - 0x2e0) / 4 - 1];
    volatile uint32_t CPU0_IPCM_VECTOR_0; //offsetaddress : 0x300
    volatile uint32_t CPU0_IPCM_VECTOR_1; //offsetaddress : 0x304
    volatile uint32_t CPU1_IPCM_VECTOR_0; //offsetaddress : 0x308
    volatile uint32_t CPU1_IPCM_VECTOR_1; //offsetaddress : 0x30c
    volatile uint32_t CPU2_IPCM_VECTOR_0; //offsetaddress : 0x310
    volatile uint32_t CPU2_IPCM_VECTOR_1; //offsetaddress : 0x314
    volatile uint32_t rev_22[(0x320 - 0x314) / 4 - 1];
    volatile uint32_t CHIP_VERSION; //offsetaddress : 0x320
} cpr_reg_t;
#ifdef __cplusplus
}
#endif
#endif
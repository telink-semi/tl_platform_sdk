/*******************************************************************************************************
 *
 * @file    pmu.h
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
#ifndef __PMU_H__
#define __PMU_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

//RST_SET_AO offsetaddress : 0x00
//RST_SET_AO RegResetValue : 0x3f
#define PMU_RSTN_RTC_P_SET_POS     (0U)
#define PMU_RSTN_RTC_P_SET_MSK     (0x1UL << PMU_RSTN_RTC_P_SET_POS) /*!< rtc_p soft reset*/
#define PMU_RSTN_RTC_P_SET         PMU_RSTN_RTC_P_SET_MSK
#define PMU_RSTN_SOFT_RTC_SET_POS  (1U)
#define PMU_RSTN_SOFT_RTC_SET_MSK  (0x1UL << PMU_RSTN_SOFT_RTC_SET_POS) /*!< rtc soft reset*/
#define PMU_RSTN_SOFT_RTC_SET      PMU_RSTN_SOFT_RTC_SET_MSK
#define PMU_RSTN_SOFT_CHG_DEB_POS  (2U)
#define PMU_RSTN_SOFT_CHG_DEB_MSK  (0x1UL << PMU_RSTN_SOFT_CHG_DEB_POS) /*!< chg_deb soft reset*/
#define PMU_RSTN_SOFT_CHG_DEB      PMU_RSTN_SOFT_CHG_DEB_MSK
#define PMU_RSTN_SOFT_GPIO_SET_POS (3U)
#define PMU_RSTN_SOFT_GPIO_SET_MSK (0x1UL << PMU_RSTN_SOFT_GPIO_SET_POS) /*!< gpio soft reset*/
#define PMU_RSTN_SOFT_GPIO_SET     PMU_RSTN_SOFT_GPIO_SET_MSK
#define PMU_RSTN_SOFT_RPD_POS      (4U)
#define PMU_RSTN_SOFT_RPD_MSK      (0x1UL << PMU_RSTN_SOFT_RPD_POS) /*!< rpd soft reset*/
#define PMU_RSTN_SOFT_RPD          PMU_RSTN_SOFT_RPD_MSK
#define PMU_RSTN_SOFT_RW_LP_POS    (5U)
#define PMU_RSTN_SOFT_RW_LP_MSK    (0x1UL << PMU_RSTN_SOFT_RW_LP_POS) /*!< rw lp soft reset*/
#define PMU_RSTN_SOFT_RW_LP        PMU_RSTN_SOFT_RW_LP_MSK
#define PMU_RW_LP_ISO_POS          (6U)
#define PMU_RW_LP_ISO_MSK          (0x1UL << PMU_RW_LP_ISO_POS) /*!< rw timing gen lp isolation*/
#define PMU_RW_LP_ISO              PMU_RW_LP_ISO_MSK

//CLK_EN_M_AO offsetaddress : 0x08
//CLK_EN_M_AO RegResetValue : 0x0
#define PMU_CPU1_SYSTEM_CLK_EN_POS   (0U)
#define PMU_CPU1_SYSTEM_CLK_EN_MSK   (0x1UL << PMU_CPU1_SYSTEM_CLK_EN_POS) /*!< CPU1 system bus clock enable*/
#define PMU_CPU1_SYSTEM_CLK_EN       PMU_CPU1_SYSTEM_CLK_EN_MSK
#define PMU_CPU1_CORE_CLK_EN_POS     (1U)
#define PMU_CPU1_CORE_CLK_EN_MSK     (0x1UL << PMU_CPU1_CORE_CLK_EN_POS) /*!< CPU1 CPU core clock enable*/
#define PMU_CPU1_CORE_CLK_EN         PMU_CPU1_CORE_CLK_EN_MSK
#define PMU_CPU1_CORE_AON_CLK_EN_POS (2U)
#define PMU_CPU1_CORE_AON_CLK_EN_MSK (0x1UL << PMU_CPU1_CORE_AON_CLK_EN_POS) /*!< CPU1 cpu core aon clock enable*/
#define PMU_CPU1_CORE_AON_CLK_EN     PMU_CPU1_CORE_AON_CLK_EN_MSK
#define PMU_CPU1_ILM_CLK_EN_POS      (3U)
#define PMU_CPU1_ILM_CLK_EN_MSK      (0x1UL << PMU_CPU1_ILM_CLK_EN_POS) /*!< CPU1 ilm clock enable*/
#define PMU_CPU1_ILM_CLK_EN          PMU_CPU1_ILM_CLK_EN_MSK
#define PMU_CPU1_DLM_CLK_EN_POS      (4U)
#define PMU_CPU1_DLM_CLK_EN_MSK      (0x1UL << PMU_CPU1_DLM_CLK_EN_POS) /*!< CPU1 dlm clock enable*/
#define PMU_CPU1_DLM_CLK_EN          PMU_CPU1_DLM_CLK_EN_MSK
#define PMU_SHRAM1_CLK_EN_POS        (5U)
#define PMU_SHRAM1_CLK_EN_MSK        (0x1UL << PMU_SHRAM1_CLK_EN_POS) /*!< Shram1 clock enable*/
#define PMU_SHRAM1_CLK_EN            PMU_SHRAM1_CLK_EN_MSK
#define PMU_RTC_CLK_EN_POS           (6U)
#define PMU_RTC_CLK_EN_MSK           (0x1UL << PMU_RTC_CLK_EN_POS) /*!< rtc clock enable*/
#define PMU_RTC_CLK_EN               PMU_RTC_CLK_EN_MSK
#define PMU_CHG_DEB_CLK_EN_POS       (7U)
#define PMU_CHG_DEB_CLK_EN_MSK       (0x1UL << PMU_CHG_DEB_CLK_EN_POS) /*!< charger debounce clock enable*/
#define PMU_CHG_DEB_CLK_EN           PMU_CHG_DEB_CLK_EN_MSK
#define PMU_GPIO_DEB_CLK_EN_POS      (8U)
#define PMU_GPIO_DEB_CLK_EN_MSK      (0x1UL << PMU_GPIO_DEB_CLK_EN_POS) /*!< gpio debounce clock enable*/
#define PMU_GPIO_DEB_CLK_EN          PMU_GPIO_DEB_CLK_EN_MSK
#define PMU_BT_SYS_CLK32K_EN_POS     (9U)
#define PMU_BT_SYS_CLK32K_EN_MSK     (0x1UL << PMU_BT_SYS_CLK32K_EN_POS) /*!< bt_sys_clk32k clock enable*/
#define PMU_BT_SYS_CLK32K_EN         PMU_BT_SYS_CLK32K_EN_MSK

//CPU0_RESET_VECTOR offsetaddress : 0x10
//CPU0_RESET_VECTOR RegResetValue : 0x2000_0000
#define PMU_CPU0_RESET_VECTOR_POS  (0U)
#define PMU_CPU0_RESET_VECTOR_MSK  (0xffffffffUL << PMU_CPU0_RESET_VECTOR_POS) /*!< CPU0 cpu reset vector*/
#define PMU_CPU0_RESET_VECTOR      PMU_CPU0_RESET_VECTOR_MSK
#define PMU_CPU0_RESET_VECTOR_W(X) ((X) << PMU_CPU0_RESET_VECTOR_POS)

//CPU1_RESET_VECTOR offsetaddress : 0x14
//CPU1_RESET_VECTOR RegResetValue : 0x0
#define PMU_CPU1_RESET_VECTOR_POS  (0U)
#define PMU_CPU1_RESET_VECTOR_MSK  (0xffffffffUL << PMU_CPU1_RESET_VECTOR_POS) /*!< CPU1 cpu reset vector*/
#define PMU_CPU1_RESET_VECTOR      PMU_CPU1_RESET_VECTOR_MSK
#define PMU_CPU1_RESET_VECTOR_W(X) ((X) << PMU_CPU1_RESET_VECTOR_POS)

//CPU0_SP offsetaddress : 0x18
//CPU0_SP RegResetValue : 0x0
#define PMU_CPU0_SP_POS  (0U)
#define PMU_CPU0_SP_MSK  (0xffffffffUL << PMU_CPU0_SP_POS) /*!< CPU0 cpu stack pointer*/
#define PMU_CPU0_SP      PMU_CPU0_SP_MSK
#define PMU_CPU0_SP_W(X) ((X) << PMU_CPU0_SP_POS)

//CPU1_SP offsetaddress : 0x1c
//CPU1_SP RegResetValue : 0x0
#define PMU_CPU1_SP_POS  (0U)
#define PMU_CPU1_SP_MSK  (0xffffffffUL << PMU_CPU1_SP_POS) /*!< CPU1 cpu stack pointer*/
#define PMU_CPU1_SP      PMU_CPU1_SP_MSK
#define PMU_CPU1_SP_W(X) ((X) << PMU_CPU1_SP_POS)

//AUTO_PWDN_CTRL offsetaddress : 0x20
//AUTO_PWDN_CTRL RegResetValue : 0x3ff
#define PMU_AUTO_PD_HP_BGR_POS      (0U)
#define PMU_AUTO_PD_HP_BGR_MSK      (0x1UL << PMU_AUTO_PD_HP_BGR_POS) /*!< high power bgr auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_HP_BGR          PMU_AUTO_PD_HP_BGR_MSK
#define PMU_AUTO_PD_BUCK_ANA_POS    (1U)
#define PMU_AUTO_PD_BUCK_ANA_MSK    (0x1UL << PMU_AUTO_PD_BUCK_ANA_POS) /*!< buck_ana auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_BUCK_ANA        PMU_AUTO_PD_BUCK_ANA_MSK
#define PMU_AUTO_PD_BUCK_DIG_POS    (2U)
#define PMU_AUTO_PD_BUCK_DIG_MSK    (0x1UL << PMU_AUTO_PD_BUCK_DIG_POS) /*!< buck_dig auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_BUCK_DIG        PMU_AUTO_PD_BUCK_DIG_MSK
#define PMU_AUTO_PD_LDO_DIG_POS     (3U)
#define PMU_AUTO_PD_LDO_DIG_MSK     (0x1UL << PMU_AUTO_PD_LDO_DIG_POS) /*!< ldo_dig auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_LDO_DIG         PMU_AUTO_PD_LDO_DIG_MSK
#define PMU_AUTO_PD_VDDMEMCE_POS    (4U)
#define PMU_AUTO_PD_VDDMEMCE_MSK    (0x1UL << PMU_AUTO_PD_VDDMEMCE_POS) /*!< vdd_mem_ce auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_VDDMEMCE        PMU_AUTO_PD_VDDMEMCE_MSK
#define PMU_AUTO_PD_VDDCPU1_POS     (5U)
#define PMU_AUTO_PD_VDDCPU1_MSK     (0x1UL << PMU_AUTO_PD_VDDCPU1_POS) /*!< vddCPU1 auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_VDDCPU1         PMU_AUTO_PD_VDDCPU1_MSK
#define PMU_AUTO_PD_VDDMCU_POS      (6U)
#define PMU_AUTO_PD_VDDMCU_MSK      (0x1UL << PMU_AUTO_PD_VDDMCU_POS) /*!< vddmcu auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_VDDMCU          PMU_AUTO_PD_VDDMCU_MSK
#define PMU_AUTO_PD_HFRCO_POS       (7U)
#define PMU_AUTO_PD_HFRCO_MSK       (0x1UL << PMU_AUTO_PD_HFRCO_POS) /*!< hfrco auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_HFRCO           PMU_AUTO_PD_HFRCO_MSK
#define PMU_AUTO_PD_HFXO_POS        (8U)
#define PMU_AUTO_PD_HFXO_MSK        (0x1UL << PMU_AUTO_PD_HFXO_POS) /*!< hfxo auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_HFXO            PMU_AUTO_PD_HFXO_MSK
#define PMU_AUTO_PD_IO_POS          (9U)
#define PMU_AUTO_PD_IO_MSK          (0x1UL << PMU_AUTO_PD_IO_POS) /*!< pd domain I/O auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_IO              PMU_AUTO_PD_IO_MSK
#define PMU_AUTO_RET_PDCPU1_RAM_POS (10U)
#define PMU_AUTO_RET_PDCPU1_RAM_MSK (0x1UL << PMU_AUTO_RET_PDCPU1_RAM_POS) /*!< CPU1 sram auto retention enable upon entering/exiting sleep 0: disable 1: enable*/
#define PMU_AUTO_RET_PDCPU1_RAM     PMU_AUTO_RET_PDCPU1_RAM_MSK
#define PMU_AUTO_RET_PDMCU_RAM_POS  (11U)
#define PMU_AUTO_RET_PDMCU_RAM_MSK  (0x1UL << PMU_AUTO_RET_PDMCU_RAM_POS) /*!< CPU0 sram auto retention enable upon entering/exiting sleep 0: disable 1: enable*/
#define PMU_AUTO_RET_PDMCU_RAM      PMU_AUTO_RET_PDMCU_RAM_MSK
#define PMU_AUTO_PD_RC32K_POS       (12U)
#define PMU_AUTO_PD_RC32K_MSK       (0x1UL << PMU_AUTO_PD_RC32K_POS) /*!< rc 32k auto power down enable upon entering sleep 0: disable 1: enable*/
#define PMU_AUTO_PD_RC32K           PMU_AUTO_PD_RC32K_MSK

//POWER_CFG0 offsetaddress : 0x24
//POWER_CFG0 RegResetValue : 0x4f2f_2f6f
#define PMU_TPUP_ALL_POS       (0U)
#define PMU_TPUP_ALL_MSK       (0xffUL << PMU_TPUP_ALL_POS) /*!< */
#define PMU_TPUP_ALL           PMU_TPUP_ALL_MSK
#define PMU_TPUP_ALL_W(X)      ((X) << PMU_TPUP_ALL_POS)
#define PMU_TPUP_BUCK_ANA_POS  (8U)
#define PMU_TPUP_BUCK_ANA_MSK  (0xffUL << PMU_TPUP_BUCK_ANA_POS) /*!< */
#define PMU_TPUP_BUCK_ANA      PMU_TPUP_BUCK_ANA_MSK
#define PMU_TPUP_BUCK_ANA_W(X) ((X) << PMU_TPUP_BUCK_ANA_POS)
#define PMU_TPUP_BUCK_DIG_POS  (16U)
#define PMU_TPUP_BUCK_DIG_MSK  (0xffUL << PMU_TPUP_BUCK_DIG_POS) /*!< */
#define PMU_TPUP_BUCK_DIG      PMU_TPUP_BUCK_DIG_MSK
#define PMU_TPUP_BUCK_DIG_W(X) ((X) << PMU_TPUP_BUCK_DIG_POS)
#define PMU_TPUP_LDO_DIG_POS   (24U)
#define PMU_TPUP_LDO_DIG_MSK   (0xffUL << PMU_TPUP_LDO_DIG_POS) /*!< */
#define PMU_TPUP_LDO_DIG       PMU_TPUP_LDO_DIG_MSK
#define PMU_TPUP_LDO_DIG_W(X)  ((X) << PMU_TPUP_LDO_DIG_POS)

//POWER_CFG1 offsetaddress : 0x28
//POWER_CFG1 RegResetValue : 0x4f4f_2f4f
#define PMU_TPUP_SW_DIG_POS  (0U)
#define PMU_TPUP_SW_DIG_MSK  (0xffUL << PMU_TPUP_SW_DIG_POS) /*!< */
#define PMU_TPUP_SW_DIG      PMU_TPUP_SW_DIG_MSK
#define PMU_TPUP_SW_DIG_W(X) ((X) << PMU_TPUP_SW_DIG_POS)
#define PMU_TPUP_SW_IO_POS   (8U)
#define PMU_TPUP_SW_IO_MSK   (0xffUL << PMU_TPUP_SW_IO_POS) /*!< */
#define PMU_TPUP_SW_IO       PMU_TPUP_SW_IO_MSK
#define PMU_TPUP_SW_IO_W(X)  ((X) << PMU_TPUP_SW_IO_POS)
#define PMU_TPUP_HFRCO_POS   (16U)
#define PMU_TPUP_HFRCO_MSK   (0xffUL << PMU_TPUP_HFRCO_POS) /*!< */
#define PMU_TPUP_HFRCO       PMU_TPUP_HFRCO_MSK
#define PMU_TPUP_HFRCO_W(X)  ((X) << PMU_TPUP_HFRCO_POS)
#define PMU_TPUP_HFXO_POS    (24U)
#define PMU_TPUP_HFXO_MSK    (0xffUL << PMU_TPUP_HFXO_POS) /*!< */
#define PMU_TPUP_HFXO        PMU_TPUP_HFXO_MSK
#define PMU_TPUP_HFXO_W(X)   ((X) << PMU_TPUP_HFXO_POS)

//POWER_CFG2 offsetaddress : 0x2c
//POWER_CFG2 RegResetValue : 0x13
#define PMU_TPUP_PDMCU_ALL_POS  (0U)
#define PMU_TPUP_PDMCU_ALL_MSK  (0xfUL << PMU_TPUP_PDMCU_ALL_POS) /*!< */
#define PMU_TPUP_PDMCU_ALL      PMU_TPUP_PDMCU_ALL_MSK
#define PMU_TPUP_PDMCU_ALL_W(X) ((X) << PMU_TPUP_PDMCU_ALL_POS)
#define PMU_TPUP_SW_PDMCU_POS   (4U)
#define PMU_TPUP_SW_PDMCU_MSK   (0xfUL << PMU_TPUP_SW_PDMCU_POS) /*!< */
#define PMU_TPUP_SW_PDMCU       PMU_TPUP_SW_PDMCU_MSK
#define PMU_TPUP_SW_PDMCU_W(X)  ((X) << PMU_TPUP_SW_PDMCU_POS)

//SLP_CTRL offsetaddress : 0x30
//SLP_CTRL RegResetValue : 0x0
#define PMU_CPR_WAK_EN_POS            (0U)
#define PMU_CPR_WAK_EN_MSK            (0x1UL << PMU_CPR_WAK_EN_POS) /*!< Wake up from cpr source enable (rf system)*/
#define PMU_CPR_WAK_EN                PMU_CPR_WAK_EN_MSK
#define PMU_RTC_WAK_EN_POS            (1U)
#define PMU_RTC_WAK_EN_MSK            (0x1UL << PMU_RTC_WAK_EN_POS) /*!< rtc wake-up enable (rf system)*/
#define PMU_RTC_WAK_EN                PMU_RTC_WAK_EN_MSK
#define PMU_AON_GPIO_WAK_EN_POS       (2U)
#define PMU_AON_GPIO_WAK_EN_MSK       (0x1UL << PMU_AON_GPIO_WAK_EN_POS) /*!< aon gpio wake-up enable (rf system)*/
#define PMU_AON_GPIO_WAK_EN           PMU_AON_GPIO_WAK_EN_MSK
#define PMU_CHG_STAT_WAK_EN_POS       (3U)
#define PMU_CHG_STAT_WAK_EN_MSK       (0x1UL << PMU_CHG_STAT_WAK_EN_POS) /*!< Charging starts wake-up enable (rf system)*/
#define PMU_CHG_STAT_WAK_EN           PMU_CHG_STAT_WAK_EN_MSK
#define PMU_CHG_DET_WAK_EN_POS        (4U)
#define PMU_CHG_DET_WAK_EN_MSK        (0x1UL << PMU_CHG_DET_WAK_EN_POS) /*!< Entry wake-up enable (rf system)*/
#define PMU_CHG_DET_WAK_EN            PMU_CHG_DET_WAK_EN_MSK
#define PMU_RW_LP_WAK_EN_POS          (5U)
#define PMU_RW_LP_WAK_EN_MSK          (0x1UL << PMU_RW_LP_WAK_EN_POS) /*!< RW LP wake-up source wake-up enable (rf system)*/
#define PMU_RW_LP_WAK_EN              PMU_RW_LP_WAK_EN_MSK
#define PMU_PDMCU_CPR_WAK_EN_POS      (6U)
#define PMU_PDMCU_CPR_WAK_EN_MSK      (0x1UL << PMU_PDMCU_CPR_WAK_EN_POS) /*!< Wake up enable from cpr wake source (mcu system)*/
#define PMU_PDMCU_CPR_WAK_EN          PMU_PDMCU_CPR_WAK_EN_MSK
#define PMU_PDMCU_RTC_WAK_EN_POS      (7U)
#define PMU_PDMCU_RTC_WAK_EN_MSK      (0x1UL << PMU_PDMCU_RTC_WAK_EN_POS) /*!< rtc wake-up enable (mcu system)*/
#define PMU_PDMCU_RTC_WAK_EN          PMU_PDMCU_RTC_WAK_EN_MSK
#define PMU_PDMCU_GPIO_WAK_EN_POS     (8U)
#define PMU_PDMCU_GPIO_WAK_EN_MSK     (0x1UL << PMU_PDMCU_GPIO_WAK_EN_POS) /*!< aon gpio wake-up enable (mcu system)*/
#define PMU_PDMCU_GPIO_WAK_EN         PMU_PDMCU_GPIO_WAK_EN_MSK
#define PMU_PDMCU_CHG_STAT_WAK_EN_POS (9U)
#define PMU_PDMCU_CHG_STAT_WAK_EN_MSK (0x1UL << PMU_PDMCU_CHG_STAT_WAK_EN_POS) /*!< Charging starts wake-up enable (mcu system)*/
#define PMU_PDMCU_CHG_STAT_WAK_EN     PMU_PDMCU_CHG_STAT_WAK_EN_MSK
#define PMU_PDMCU_CHG_DET_WAK_EN_POS  (10U)
#define PMU_PDMCU_CHG_DET_WAK_EN_MSK  (0x1UL << PMU_PDMCU_CHG_DET_WAK_EN_POS) /*!< Entry wake-up enable (mcu system)*/
#define PMU_PDMCU_CHG_DET_WAK_EN      PMU_PDMCU_CHG_DET_WAK_EN_MSK
#define PMU_PDMCU_RW_LP_WAK_EN_POS    (11U)
#define PMU_PDMCU_RW_LP_WAK_EN_MSK    (0x1UL << PMU_PDMCU_RW_LP_WAK_EN_POS) /*!< RW LP wake-up source wake-up enable (mcu system)*/
#define PMU_PDMCU_RW_LP_WAK_EN        PMU_PDMCU_RW_LP_WAK_EN_MSK

//RET_RAM_CTRL_0 offsetaddress : 0x34
//RET_RAM_CTRL_0 RegResetValue : 0x0
#define PMU_CPU0_ILM_LP_MAN_EN_0_POS     (0U)
#define PMU_CPU0_ILM_LP_MAN_EN_0_MSK     (0x1UL << PMU_CPU0_ILM_LP_MAN_EN_0_POS) /*!< CPU0 ilm 0~32KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU0_ILM_LP_MAN_EN_0         PMU_CPU0_ILM_LP_MAN_EN_0_MSK
#define PMU_CPU0_ILM_LP_MAN_EN_0_W(X)    ((X) << PMU_CPU0_ILM_LP_MAN_EN_0_POS)
#define PMU_CPU0_ILM_LP_MAN_EN_1_POS     (1U)
#define PMU_CPU0_ILM_LP_MAN_EN_1_MSK     (0x1UL << PMU_CPU0_ILM_LP_MAN_EN_1_POS) /*!< CPU0 ilm 32KB~64KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU0_ILM_LP_MAN_EN_1         PMU_CPU0_ILM_LP_MAN_EN_1_MSK
#define PMU_CPU0_ILM_LP_MAN_EN_1_W(X)    ((X) << PMU_CPU0_ILM_LP_MAN_EN_1_POS)
#define PMU_CPU0_ILM_LP_MAN_EN_2_POS     (2U)
#define PMU_CPU0_ILM_LP_MAN_EN_2_MSK     (0x1UL << PMU_CPU0_ILM_LP_MAN_EN_2_POS) /*!< CPU0 ilm 64KB~96KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU0_ILM_LP_MAN_EN_2         PMU_CPU0_ILM_LP_MAN_EN_2_MSK
#define PMU_CPU0_ILM_LP_MAN_EN_2_W(X)    ((X) << PMU_CPU0_ILM_LP_MAN_EN_2_POS)
#define PMU_CPU0_DLM_LP_MAN_EN_0_POS     (3U)
#define PMU_CPU0_DLM_LP_MAN_EN_0_MSK     (0x1UL << PMU_CPU0_DLM_LP_MAN_EN_0_POS) /*!< CPU0 dlm 0~32KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU0_DLM_LP_MAN_EN_0         PMU_CPU0_DLM_LP_MAN_EN_0_MSK
#define PMU_CPU0_DLM_LP_MAN_EN_0_W(X)    ((X) << PMU_CPU0_DLM_LP_MAN_EN_0_POS)
#define PMU_CPU0_DLM_LP_MAN_EN_1_POS     (4U)
#define PMU_CPU0_DLM_LP_MAN_EN_1_MSK     (0x1UL << PMU_CPU0_DLM_LP_MAN_EN_1_POS) /*!< CPU0 dlm 32KB~64KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU0_DLM_LP_MAN_EN_1         PMU_CPU0_DLM_LP_MAN_EN_1_MSK
#define PMU_CPU0_DLM_LP_MAN_EN_1_W(X)    ((X) << PMU_CPU0_DLM_LP_MAN_EN_1_POS)
#define PMU_CPU1_ILM_LP_MAN_EN_0_POS     (5U)
#define PMU_CPU1_ILM_LP_MAN_EN_0_MSK     (0x1UL << PMU_CPU1_ILM_LP_MAN_EN_0_POS) /*!< CPU1 ilm 0~32KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_ILM_LP_MAN_EN_0         PMU_CPU1_ILM_LP_MAN_EN_0_MSK
#define PMU_CPU1_ILM_LP_MAN_EN_0_W(X)    ((X) << PMU_CPU1_ILM_LP_MAN_EN_0_POS)
#define PMU_CPU1_ILM_LP_MAN_EN_1_POS     (6U)
#define PMU_CPU1_ILM_LP_MAN_EN_1_MSK     (0x1UL << PMU_CPU1_ILM_LP_MAN_EN_1_POS) /*!< CPU1 ilm 32KB~64KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_ILM_LP_MAN_EN_1         PMU_CPU1_ILM_LP_MAN_EN_1_MSK
#define PMU_CPU1_ILM_LP_MAN_EN_1_W(X)    ((X) << PMU_CPU1_ILM_LP_MAN_EN_1_POS)
#define PMU_CPU1_ILM_LP_MAN_EN_2_POS     (7U)
#define PMU_CPU1_ILM_LP_MAN_EN_2_MSK     (0x1UL << PMU_CPU1_ILM_LP_MAN_EN_2_POS) /*!< CPU1 ilm 64KB~96KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_ILM_LP_MAN_EN_2         PMU_CPU1_ILM_LP_MAN_EN_2_MSK
#define PMU_CPU1_ILM_LP_MAN_EN_2_W(X)    ((X) << PMU_CPU1_ILM_LP_MAN_EN_2_POS)
#define PMU_CPU1_DLM_LP_MAN_EN_0_POS     (8U)
#define PMU_CPU1_DLM_LP_MAN_EN_0_MSK     (0x1UL << PMU_CPU1_DLM_LP_MAN_EN_0_POS) /*!< CPU1 dlm 0~32KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_DLM_LP_MAN_EN_0         PMU_CPU1_DLM_LP_MAN_EN_0_MSK
#define PMU_CPU1_DLM_LP_MAN_EN_0_W(X)    ((X) << PMU_CPU1_DLM_LP_MAN_EN_0_POS)
#define PMU_CPU1_DLM_LP_MAN_EN_1_POS     (9U)
#define PMU_CPU1_DLM_LP_MAN_EN_1_MSK     (0x1UL << PMU_CPU1_DLM_LP_MAN_EN_1_POS) /*!< CPU1 dlm 32KB~64KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_DLM_LP_MAN_EN_1         PMU_CPU1_DLM_LP_MAN_EN_1_MSK
#define PMU_CPU1_DLM_LP_MAN_EN_1_W(X)    ((X) << PMU_CPU1_DLM_LP_MAN_EN_1_POS)
#define PMU_CPU1_SHRAM1_LP_MAN_EN_0_POS  (10U)
#define PMU_CPU1_SHRAM1_LP_MAN_EN_0_MSK  (0x1UL << PMU_CPU1_SHRAM1_LP_MAN_EN_0_POS) /*!< CPU1 shram1 0~32KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_SHRAM1_LP_MAN_EN_0      PMU_CPU1_SHRAM1_LP_MAN_EN_0_MSK
#define PMU_CPU1_SHRAM1_LP_MAN_EN_0_W(X) ((X) << PMU_CPU1_SHRAM1_LP_MAN_EN_0_POS)
#define PMU_CPU1_SHRAM1_LP_MAN_EN_1_POS  (11U)
#define PMU_CPU1_SHRAM1_LP_MAN_EN_1_MSK  (0x1UL << PMU_CPU1_SHRAM1_LP_MAN_EN_1_POS) /*!< CPU1 shram1 32KB~64KB low power control select 0: auto control 1: manual control*/
#define PMU_CPU1_SHRAM1_LP_MAN_EN_1      PMU_CPU1_SHRAM1_LP_MAN_EN_1_MSK
#define PMU_CPU1_SHRAM1_LP_MAN_EN_1_W(X) ((X) << PMU_CPU1_SHRAM1_LP_MAN_EN_1_POS)
#define PMU_BTEM_LP_MAN_EN_POS           (12U)
#define PMU_BTEM_LP_MAN_EN_MSK           (0x1UL << PMU_BTEM_LP_MAN_EN_POS) /*!< bt exchange memory low power control select 0: auto control 1: manual control*/
#define PMU_BTEM_LP_MAN_EN               PMU_BTEM_LP_MAN_EN_MSK
#define PMU_BTEM_LP_MAN_EN_W(X)          ((X) << PMU_BTEM_LP_MAN_EN_POS)

//RET_RAM_CTRL_1 offsetaddress : 0x38
//RET_RAM_CTRL_1 RegResetValue : 0x66_6666
#define PMU_CPU0_ILM_PGEN_MAN_VAL_POS      (0U)
#define PMU_CPU0_ILM_PGEN_MAN_VAL_MSK      (0x1UL << PMU_CPU0_ILM_PGEN_MAN_VAL_POS) /*!< CPU0 ilm (vddmemce) pgen manual value*/
#define PMU_CPU0_ILM_PGEN_MAN_VAL          PMU_CPU0_ILM_PGEN_MAN_VAL_MSK
#define PMU_CPU0_ILM_PGEN_MAN_VAL_W(X)     ((X) << PMU_CPU0_ILM_PGEN_MAN_VAL_POS)
#define PMU_CPU0_ILM_RET2N_MAN_VAL_POS     (1U)
#define PMU_CPU0_ILM_RET2N_MAN_VAL_MSK     (0x1UL << PMU_CPU0_ILM_RET2N_MAN_VAL_POS) /*!< CPU0 ilm (vddmemce) ret2n manual value*/
#define PMU_CPU0_ILM_RET2N_MAN_VAL         PMU_CPU0_ILM_RET2N_MAN_VAL_MSK
#define PMU_CPU0_ILM_RET2N_MAN_VAL_W(X)    ((X) << PMU_CPU0_ILM_RET2N_MAN_VAL_POS)
#define PMU_CPU0_ILM_RET1N_MAN_VAL_POS     (2U)
#define PMU_CPU0_ILM_RET1N_MAN_VAL_MSK     (0x1UL << PMU_CPU0_ILM_RET1N_MAN_VAL_POS) /*!< CPU0 ilm (vddmemce) ret1n manual value*/
#define PMU_CPU0_ILM_RET1N_MAN_VAL         PMU_CPU0_ILM_RET1N_MAN_VAL_MSK
#define PMU_CPU0_ILM_RET1N_MAN_VAL_W(X)    ((X) << PMU_CPU0_ILM_RET1N_MAN_VAL_POS)
#define PMU_CPU0_DLM_PGEN_MAN_VAL_POS      (4U)
#define PMU_CPU0_DLM_PGEN_MAN_VAL_MSK      (0x1UL << PMU_CPU0_DLM_PGEN_MAN_VAL_POS) /*!< CPU0 dlm (vddmemce) pgen manual value*/
#define PMU_CPU0_DLM_PGEN_MAN_VAL          PMU_CPU0_DLM_PGEN_MAN_VAL_MSK
#define PMU_CPU0_DLM_PGEN_MAN_VAL_W(X)     ((X) << PMU_CPU0_DLM_PGEN_MAN_VAL_POS)
#define PMU_CPU0_DLM_RET2N_MAN_VAL_POS     (5U)
#define PMU_CPU0_DLM_RET2N_MAN_VAL_MSK     (0x1UL << PMU_CPU0_DLM_RET2N_MAN_VAL_POS) /*!< CPU0 dlm (vddmemce) ret2n manual value*/
#define PMU_CPU0_DLM_RET2N_MAN_VAL         PMU_CPU0_DLM_RET2N_MAN_VAL_MSK
#define PMU_CPU0_DLM_RET2N_MAN_VAL_W(X)    ((X) << PMU_CPU0_DLM_RET2N_MAN_VAL_POS)
#define PMU_CPU0_DLM_RET1N_MAN_VAL_POS     (6U)
#define PMU_CPU0_DLM_RET1N_MAN_VAL_MSK     (0x1UL << PMU_CPU0_DLM_RET1N_MAN_VAL_POS) /*!< CPU0 dlm (vddmemce) ret1n manual value*/
#define PMU_CPU0_DLM_RET1N_MAN_VAL         PMU_CPU0_DLM_RET1N_MAN_VAL_MSK
#define PMU_CPU0_DLM_RET1N_MAN_VAL_W(X)    ((X) << PMU_CPU0_DLM_RET1N_MAN_VAL_POS)
#define PMU_CPU1_ILM_PGEN_MAN_VAL_POS      (8U)
#define PMU_CPU1_ILM_PGEN_MAN_VAL_MSK      (0x1UL << PMU_CPU1_ILM_PGEN_MAN_VAL_POS) /*!< CPU1 ilm (vddmemce) pgen manual value*/
#define PMU_CPU1_ILM_PGEN_MAN_VAL          PMU_CPU1_ILM_PGEN_MAN_VAL_MSK
#define PMU_CPU1_ILM_PGEN_MAN_VAL_W(X)     ((X) << PMU_CPU1_ILM_PGEN_MAN_VAL_POS)
#define PMU_CPU1_ILM_RET2N_MAN_VAL_POS     (9U)
#define PMU_CPU1_ILM_RET2N_MAN_VAL_MSK     (0x1UL << PMU_CPU1_ILM_RET2N_MAN_VAL_POS) /*!< CPU1 ilm (vddmemce) ret2n manual value*/
#define PMU_CPU1_ILM_RET2N_MAN_VAL         PMU_CPU1_ILM_RET2N_MAN_VAL_MSK
#define PMU_CPU1_ILM_RET2N_MAN_VAL_W(X)    ((X) << PMU_CPU1_ILM_RET2N_MAN_VAL_POS)
#define PMU_CPU1_ILM_RET1N_MAN_VAL_POS     (10U)
#define PMU_CPU1_ILM_RET1N_MAN_VAL_MSK     (0x1UL << PMU_CPU1_ILM_RET1N_MAN_VAL_POS) /*!< CPU1 ilm (vddmemce) ret1n manual value*/
#define PMU_CPU1_ILM_RET1N_MAN_VAL         PMU_CPU1_ILM_RET1N_MAN_VAL_MSK
#define PMU_CPU1_ILM_RET1N_MAN_VAL_W(X)    ((X) << PMU_CPU1_ILM_RET1N_MAN_VAL_POS)
#define PMU_CPU1_DLM_PGEN_MAN_VAL_POS      (12U)
#define PMU_CPU1_DLM_PGEN_MAN_VAL_MSK      (0x1UL << PMU_CPU1_DLM_PGEN_MAN_VAL_POS) /*!< CPU1 dlm (vddmemce) pgen manual value*/
#define PMU_CPU1_DLM_PGEN_MAN_VAL          PMU_CPU1_DLM_PGEN_MAN_VAL_MSK
#define PMU_CPU1_DLM_PGEN_MAN_VAL_W(X)     ((X) << PMU_CPU1_DLM_PGEN_MAN_VAL_POS)
#define PMU_CPU1_DLM_RET2N_MAN_VAL_POS     (13U)
#define PMU_CPU1_DLM_RET2N_MAN_VAL_MSK     (0x1UL << PMU_CPU1_DLM_RET2N_MAN_VAL_POS) /*!< CPU1 dlm (vddmemce) ret2n manual value*/
#define PMU_CPU1_DLM_RET2N_MAN_VAL         PMU_CPU1_DLM_RET2N_MAN_VAL_MSK
#define PMU_CPU1_DLM_RET2N_MAN_VAL_W(X)    ((X) << PMU_CPU1_DLM_RET2N_MAN_VAL_POS)
#define PMU_CPU1_DLM_RET1N_MAN_VAL_POS     (14U)
#define PMU_CPU1_DLM_RET1N_MAN_VAL_MSK     (0x1UL << PMU_CPU1_DLM_RET1N_MAN_VAL_POS) /*!< CPU1 dlm (vddmemce) ret1n manual value*/
#define PMU_CPU1_DLM_RET1N_MAN_VAL         PMU_CPU1_DLM_RET1N_MAN_VAL_MSK
#define PMU_CPU1_DLM_RET1N_MAN_VAL_W(X)    ((X) << PMU_CPU1_DLM_RET1N_MAN_VAL_POS)
#define PMU_CPU1_SHRAM1_PGEN_MAN_VAL_POS   (16U)
#define PMU_CPU1_SHRAM1_PGEN_MAN_VAL_MSK   (0x1UL << PMU_CPU1_SHRAM1_PGEN_MAN_VAL_POS) /*!< CPU1 shram1 (vddmemce) pgen manual value*/
#define PMU_CPU1_SHRAM1_PGEN_MAN_VAL       PMU_CPU1_SHRAM1_PGEN_MAN_VAL_MSK
#define PMU_CPU1_SHRAM1_PGEN_MAN_VAL_W(X)  ((X) << PMU_CPU1_SHRAM1_PGEN_MAN_VAL_POS)
#define PMU_CPU1_SHRAM1_RET2N_MAN_VAL_POS  (17U)
#define PMU_CPU1_SHRAM1_RET2N_MAN_VAL_MSK  (0x1UL << PMU_CPU1_SHRAM1_RET2N_MAN_VAL_POS) /*!< CPU1 shram1 (vddmemce) ret2n manual value*/
#define PMU_CPU1_SHRAM1_RET2N_MAN_VAL      PMU_CPU1_SHRAM1_RET2N_MAN_VAL_MSK
#define PMU_CPU1_SHRAM1_RET2N_MAN_VAL_W(X) ((X) << PMU_CPU1_SHRAM1_RET2N_MAN_VAL_POS)
#define PMU_CPU1_SHRAM1_RET1N_MAN_VAL_POS  (18U)
#define PMU_CPU1_SHRAM1_RET1N_MAN_VAL_MSK  (0x1UL << PMU_CPU1_SHRAM1_RET1N_MAN_VAL_POS) /*!< CPU1 shram1 (vddmemce) ret1n manual value*/
#define PMU_CPU1_SHRAM1_RET1N_MAN_VAL      PMU_CPU1_SHRAM1_RET1N_MAN_VAL_MSK
#define PMU_CPU1_SHRAM1_RET1N_MAN_VAL_W(X) ((X) << PMU_CPU1_SHRAM1_RET1N_MAN_VAL_POS)
#define PMU_BTEM_PGEN_MAN_VAL_POS          (20U)
#define PMU_BTEM_PGEN_MAN_VAL_MSK          (0x1UL << PMU_BTEM_PGEN_MAN_VAL_POS) /*!< bt exchange memory (vddmemce) pgen manual value*/
#define PMU_BTEM_PGEN_MAN_VAL              PMU_BTEM_PGEN_MAN_VAL_MSK
#define PMU_BTEM_PGEN_MAN_VAL_W(X)         ((X) << PMU_BTEM_PGEN_MAN_VAL_POS)
#define PMU_BTEM_RET2N_MAN_VAL_POS         (21U)
#define PMU_BTEM_RET2N_MAN_VAL_MSK         (0x1UL << PMU_BTEM_RET2N_MAN_VAL_POS) /*!< bt exchange memory (vddmemce) ret2n manual value*/
#define PMU_BTEM_RET2N_MAN_VAL             PMU_BTEM_RET2N_MAN_VAL_MSK
#define PMU_BTEM_RET2N_MAN_VAL_W(X)        ((X) << PMU_BTEM_RET2N_MAN_VAL_POS)
#define PMU_BTEM_RET1N_MAN_VAL_POS         (22U)
#define PMU_BTEM_RET1N_MAN_VAL_MSK         (0x1UL << PMU_BTEM_RET1N_MAN_VAL_POS) /*!< bt exchange memory (vddmemce) ret1n manual value*/
#define PMU_BTEM_RET1N_MAN_VAL             PMU_BTEM_RET1N_MAN_VAL_MSK
#define PMU_BTEM_RET1N_MAN_VAL_W(X)        ((X) << PMU_BTEM_RET1N_MAN_VAL_POS)

//RET_RAM_CTRL_2 offsetaddress : 0x3c
//RET_RAM_CTRL_2 RegResetValue : 0x0
#define PMU_CPU0_ILM_LP_MODE_POS      (0U)
#define PMU_CPU0_ILM_LP_MODE_MSK      (0x1UL << PMU_CPU0_ILM_LP_MODE_POS) /*!< CPU0 ilm (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_CPU0_ILM_LP_MODE          PMU_CPU0_ILM_LP_MODE_MSK
#define PMU_CPU0_ILM_LP_MODE_W(X)     ((X) << PMU_CPU0_ILM_LP_MODE_POS)
#define PMU_CPU0_ILM_RET_MODE_POS     (1U)
#define PMU_CPU0_ILM_RET_MODE_MSK     (0x1UL << PMU_CPU0_ILM_RET_MODE_POS) /*!< CPU0 ilm (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_CPU0_ILM_RET_MODE         PMU_CPU0_ILM_RET_MODE_MSK
#define PMU_CPU0_ILM_RET_MODE_W(X)    ((X) << PMU_CPU0_ILM_RET_MODE_POS)
#define PMU_CPU0_DLM_LP_MODE_POS      (2U)
#define PMU_CPU0_DLM_LP_MODE_MSK      (0x1UL << PMU_CPU0_DLM_LP_MODE_POS) /*!< CPU0 dlm (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_CPU0_DLM_LP_MODE          PMU_CPU0_DLM_LP_MODE_MSK
#define PMU_CPU0_DLM_LP_MODE_W(X)     ((X) << PMU_CPU0_DLM_LP_MODE_POS)
#define PMU_CPU0_DLM_RET_MODE_POS     (3U)
#define PMU_CPU0_DLM_RET_MODE_MSK     (0x1UL << PMU_CPU0_DLM_RET_MODE_POS) /*!< CPU0 dlm (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_CPU0_DLM_RET_MODE         PMU_CPU0_DLM_RET_MODE_MSK
#define PMU_CPU0_DLM_RET_MODE_W(X)    ((X) << PMU_CPU0_DLM_RET_MODE_POS)
#define PMU_CPU1_ILM_LP_MODE_POS      (4U)
#define PMU_CPU1_ILM_LP_MODE_MSK      (0x1UL << PMU_CPU1_ILM_LP_MODE_POS) /*!< CPU1 ilm (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_CPU1_ILM_LP_MODE          PMU_CPU1_ILM_LP_MODE_MSK
#define PMU_CPU1_ILM_LP_MODE_W(X)     ((X) << PMU_CPU1_ILM_LP_MODE_POS)
#define PMU_CPU1_ILM_RET_MODE_POS     (5U)
#define PMU_CPU1_ILM_RET_MODE_MSK     (0x1UL << PMU_CPU1_ILM_RET_MODE_POS) /*!< CPU1 ilm (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_CPU1_ILM_RET_MODE         PMU_CPU1_ILM_RET_MODE_MSK
#define PMU_CPU1_ILM_RET_MODE_W(X)    ((X) << PMU_CPU1_ILM_RET_MODE_POS)
#define PMU_CPU1_DLM_LP_MODE_POS      (6U)
#define PMU_CPU1_DLM_LP_MODE_MSK      (0x1UL << PMU_CPU1_DLM_LP_MODE_POS) /*!< CPU1 dlm (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_CPU1_DLM_LP_MODE          PMU_CPU1_DLM_LP_MODE_MSK
#define PMU_CPU1_DLM_LP_MODE_W(X)     ((X) << PMU_CPU1_DLM_LP_MODE_POS)
#define PMU_CPU1_DLM_RET_MODE_POS     (7U)
#define PMU_CPU1_DLM_RET_MODE_MSK     (0x1UL << PMU_CPU1_DLM_RET_MODE_POS) /*!< CPU1 dlm (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_CPU1_DLM_RET_MODE         PMU_CPU1_DLM_RET_MODE_MSK
#define PMU_CPU1_DLM_RET_MODE_W(X)    ((X) << PMU_CPU1_DLM_RET_MODE_POS)
#define PMU_CPU1_SHRAM1_LP_MODE_POS   (8U)
#define PMU_CPU1_SHRAM1_LP_MODE_MSK   (0x1UL << PMU_CPU1_SHRAM1_LP_MODE_POS) /*!< CPU1 shram1 (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_CPU1_SHRAM1_LP_MODE       PMU_CPU1_SHRAM1_LP_MODE_MSK
#define PMU_CPU1_SHRAM1_LP_MODE_W(X)  ((X) << PMU_CPU1_SHRAM1_LP_MODE_POS)
#define PMU_CPU1_SHRAM1_RET_MODE_POS  (9U)
#define PMU_CPU1_SHRAM1_RET_MODE_MSK  (0x1UL << PMU_CPU1_SHRAM1_RET_MODE_POS) /*!< CPU1 shram1 (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_CPU1_SHRAM1_RET_MODE      PMU_CPU1_SHRAM1_RET_MODE_MSK
#define PMU_CPU1_SHRAM1_RET_MODE_W(X) ((X) << PMU_CPU1_SHRAM1_RET_MODE_POS)
#define PMU_BTEM_LP_MODE_POS          (10U)
#define PMU_BTEM_LP_MODE_MSK          (0x1UL << PMU_BTEM_LP_MODE_POS) /*!< bt exchange memory (vddmemce) low power mode 0: retention 1: power down*/
#define PMU_BTEM_LP_MODE              PMU_BTEM_LP_MODE_MSK
#define PMU_BTEM_LP_MODE_W(X)         ((X) << PMU_BTEM_LP_MODE_POS)
#define PMU_BTEM_RET_MODE_POS         (11U)
#define PMU_BTEM_RET_MODE_MSK         (0x1UL << PMU_BTEM_RET_MODE_POS) /*!< bt exchange memory (vddmemce) retention mode 0: retention mode 2 1: retention mode 1*/
#define PMU_BTEM_RET_MODE             PMU_BTEM_RET_MODE_MSK
#define PMU_BTEM_RET_MODE_W(X)        ((X) << PMU_BTEM_RET_MODE_POS)

//SOFT_PWDN_CTRL offsetaddress : 0x40
//SOFT_PWDN_CTRL RegResetValue : 0x7f
#define PMU_SOFT_EN_HP_BGR_POS    (0U)
#define PMU_SOFT_EN_HP_BGR_MSK    (0x1UL << PMU_SOFT_EN_HP_BGR_POS) /*!< high power bgr manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_HP_BGR        PMU_SOFT_EN_HP_BGR_MSK
#define PMU_SOFT_EN_HP_BGR_W(X)   ((X) << PMU_SOFT_EN_HP_BGR_POS)
#define PMU_SOFT_EN_BUCK_ANA_POS  (1U)
#define PMU_SOFT_EN_BUCK_ANA_MSK  (0x1UL << PMU_SOFT_EN_BUCK_ANA_POS) /*!< buck_ana manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_BUCK_ANA      PMU_SOFT_EN_BUCK_ANA_MSK
#define PMU_SOFT_EN_BUCK_ANA_W(X) ((X) << PMU_SOFT_EN_BUCK_ANA_POS)
#define PMU_SOFT_EN_BUCK_DIG_POS  (2U)
#define PMU_SOFT_EN_BUCK_DIG_MSK  (0x1UL << PMU_SOFT_EN_BUCK_DIG_POS) /*!< buck_dig manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_BUCK_DIG      PMU_SOFT_EN_BUCK_DIG_MSK
#define PMU_SOFT_EN_BUCK_DIG_W(X) ((X) << PMU_SOFT_EN_BUCK_DIG_POS)
#define PMU_SOFT_EN_LDO_DIG_POS   (3U)
#define PMU_SOFT_EN_LDO_DIG_MSK   (0x1UL << PMU_SOFT_EN_LDO_DIG_POS) /*!< ldo_dig manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_LDO_DIG       PMU_SOFT_EN_LDO_DIG_MSK
#define PMU_SOFT_EN_LDO_DIG_W(X)  ((X) << PMU_SOFT_EN_LDO_DIG_POS)
#define PMU_SOFT_EN_IO_SW_POS     (4U)
#define PMU_SOFT_EN_IO_SW_MSK     (0x1UL << PMU_SOFT_EN_IO_SW_POS) /*!< I/O power switch manual on/off control 0: off 1: on*/
#define PMU_SOFT_EN_IO_SW         PMU_SOFT_EN_IO_SW_MSK
#define PMU_SOFT_EN_IO_SW_W(X)    ((X) << PMU_SOFT_EN_IO_SW_POS)
#define PMU_SOFT_EN_HFRCO_POS     (5U)
#define PMU_SOFT_EN_HFRCO_MSK     (0x1UL << PMU_SOFT_EN_HFRCO_POS) /*!< hfrco manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_HFRCO         PMU_SOFT_EN_HFRCO_MSK
#define PMU_SOFT_EN_HFRCO_W(X)    ((X) << PMU_SOFT_EN_HFRCO_POS)
#define PMU_SOFT_EN_RC32K_POS     (6U)
#define PMU_SOFT_EN_RC32K_MSK     (0x1UL << PMU_SOFT_EN_RC32K_POS) /*!< rc 32k manual power up/down control 0: power down 1: power up*/
#define PMU_SOFT_EN_RC32K         PMU_SOFT_EN_RC32K_MSK
#define PMU_SOFT_EN_RC32K_W(X)    ((X) << PMU_SOFT_EN_RC32K_POS)

//PB_IE_CFG offsetaddress : 0x50
//PB_IE_CFG RegResetValue : 0x3fff
#define PMU_PB_IE_POS  (0U)
#define PMU_PB_IE_MSK  (0x3fffUL << PMU_PB_IE_POS) /*!< PB INPUT ENABLE*/
#define PMU_PB_IE      PMU_PB_IE_MSK
#define PMU_PB_IE_W(X) ((X) << PMU_PB_IE_POS)

//PB_CTRL_0 offsetaddress : 0x54
//PB_CTRL_0 RegResetValue : 0xaaaa_aaaa
#define PMU_PB_CTRL_31_0_POS  (0U)
#define PMU_PB_CTRL_31_0_MSK  (0xffffffffUL << PMU_PB_CTRL_31_0_POS) /*!< pb control*/
#define PMU_PB_CTRL_31_0      PMU_PB_CTRL_31_0_MSK
#define PMU_PB_CTRL_31_0_W(X) ((X) << PMU_PB_CTRL_31_0_POS)

//PB_CTRL_1 offsetaddress : 0x58
//PB_CTRL_1 RegResetValue : 0xaaaa_aaaa
#define PMU_PB_CTRL_63_32_POS  (0U)
#define PMU_PB_CTRL_63_32_MSK  (0xffffffffUL << PMU_PB_CTRL_63_32_POS) /*!< pb control*/
#define PMU_PB_CTRL_63_32      PMU_PB_CTRL_63_32_MSK
#define PMU_PB_CTRL_63_32_W(X) ((X) << PMU_PB_CTRL_63_32_POS)

//PB_CTRL_2 offsetaddress : 0x5c
//PB_CTRL_2 RegResetValue : 0xa_aaaa
#define PMU_PB_CTRL_83_64_POS  (0U)
#define PMU_PB_CTRL_83_64_MSK  (0xfffffUL << PMU_PB_CTRL_83_64_POS) /*!< pb control*/
#define PMU_PB_CTRL_83_64      PMU_PB_CTRL_83_64_MSK
#define PMU_PB_CTRL_83_64_W(X) ((X) << PMU_PB_CTRL_83_64_POS)

//PB_WKUP_IRQ offsetaddress : 0x60
//PB_WKUP_IRQ RegResetValue : 0x0
#define PMU_PB00_PAD_WKUP_IRQ_POS  (0U)
#define PMU_PB00_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB00_PAD_WKUP_IRQ_POS) /*!< PB00 irq status, write 1 to clear*/
#define PMU_PB00_PAD_WKUP_IRQ      PMU_PB00_PAD_WKUP_IRQ_MSK
#define PMU_PB00_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB00_PAD_WKUP_IRQ_POS)
#define PMU_PB01_PAD_WKUP_IRQ_POS  (1U)
#define PMU_PB01_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB01_PAD_WKUP_IRQ_POS) /*!< PB01 irq status, write 1 to clear*/
#define PMU_PB01_PAD_WKUP_IRQ      PMU_PB01_PAD_WKUP_IRQ_MSK
#define PMU_PB01_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB01_PAD_WKUP_IRQ_POS)
#define PMU_PB02_PAD_WKUP_IRQ_POS  (2U)
#define PMU_PB02_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB02_PAD_WKUP_IRQ_POS) /*!< PB02 irq status, write 1 to clear*/
#define PMU_PB02_PAD_WKUP_IRQ      PMU_PB02_PAD_WKUP_IRQ_MSK
#define PMU_PB02_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB02_PAD_WKUP_IRQ_POS)
#define PMU_PB03_PAD_WKUP_IRQ_POS  (3U)
#define PMU_PB03_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB03_PAD_WKUP_IRQ_POS) /*!< PB03 irq status, write 1 to clear*/
#define PMU_PB03_PAD_WKUP_IRQ      PMU_PB03_PAD_WKUP_IRQ_MSK
#define PMU_PB03_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB03_PAD_WKUP_IRQ_POS)
#define PMU_PB04_PAD_WKUP_IRQ_POS  (4U)
#define PMU_PB04_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB04_PAD_WKUP_IRQ_POS) /*!< PB04 irq status, write 1 to clear*/
#define PMU_PB04_PAD_WKUP_IRQ      PMU_PB04_PAD_WKUP_IRQ_MSK
#define PMU_PB04_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB04_PAD_WKUP_IRQ_POS)
#define PMU_PB05_PAD_WKUP_IRQ_POS  (5U)
#define PMU_PB05_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB05_PAD_WKUP_IRQ_POS) /*!< PB05 irq status, write 1 to clear*/
#define PMU_PB05_PAD_WKUP_IRQ      PMU_PB05_PAD_WKUP_IRQ_MSK
#define PMU_PB05_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB05_PAD_WKUP_IRQ_POS)
#define PMU_PB06_PAD_WKUP_IRQ_POS  (6U)
#define PMU_PB06_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB06_PAD_WKUP_IRQ_POS) /*!< PB06 irq status, write 1 to clear*/
#define PMU_PB06_PAD_WKUP_IRQ      PMU_PB06_PAD_WKUP_IRQ_MSK
#define PMU_PB06_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB06_PAD_WKUP_IRQ_POS)
#define PMU_PB07_PAD_WKUP_IRQ_POS  (7U)
#define PMU_PB07_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB07_PAD_WKUP_IRQ_POS) /*!< PB07 irq status, write 1 to clear*/
#define PMU_PB07_PAD_WKUP_IRQ      PMU_PB07_PAD_WKUP_IRQ_MSK
#define PMU_PB07_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB07_PAD_WKUP_IRQ_POS)
#define PMU_PB08_PAD_WKUP_IRQ_POS  (8U)
#define PMU_PB08_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB08_PAD_WKUP_IRQ_POS) /*!< PB08 irq status, write 1 to clear*/
#define PMU_PB08_PAD_WKUP_IRQ      PMU_PB08_PAD_WKUP_IRQ_MSK
#define PMU_PB08_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB08_PAD_WKUP_IRQ_POS)
#define PMU_PB09_PAD_WKUP_IRQ_POS  (9U)
#define PMU_PB09_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB09_PAD_WKUP_IRQ_POS) /*!< PB09 irq status, write 1 to clear*/
#define PMU_PB09_PAD_WKUP_IRQ      PMU_PB09_PAD_WKUP_IRQ_MSK
#define PMU_PB09_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB09_PAD_WKUP_IRQ_POS)
#define PMU_PB10_PAD_WKUP_IRQ_POS  (10U)
#define PMU_PB10_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB10_PAD_WKUP_IRQ_POS) /*!< PB10 irq status, write 1 to clear*/
#define PMU_PB10_PAD_WKUP_IRQ      PMU_PB10_PAD_WKUP_IRQ_MSK
#define PMU_PB10_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB10_PAD_WKUP_IRQ_POS)
#define PMU_PB11_PAD_WKUP_IRQ_POS  (11U)
#define PMU_PB11_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB11_PAD_WKUP_IRQ_POS) /*!< PB11 irq status, write 1 to clear*/
#define PMU_PB11_PAD_WKUP_IRQ      PMU_PB11_PAD_WKUP_IRQ_MSK
#define PMU_PB11_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB11_PAD_WKUP_IRQ_POS)
#define PMU_PB12_PAD_WKUP_IRQ_POS  (12U)
#define PMU_PB12_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB12_PAD_WKUP_IRQ_POS) /*!< PB12 irq status, write 1 to clear*/
#define PMU_PB12_PAD_WKUP_IRQ      PMU_PB12_PAD_WKUP_IRQ_MSK
#define PMU_PB12_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB12_PAD_WKUP_IRQ_POS)
#define PMU_PB13_PAD_WKUP_IRQ_POS  (13U)
#define PMU_PB13_PAD_WKUP_IRQ_MSK  (0x1UL << PMU_PB13_PAD_WKUP_IRQ_POS) /*!< PB13 irq status, write 1 to clear*/
#define PMU_PB13_PAD_WKUP_IRQ      PMU_PB13_PAD_WKUP_IRQ_MSK
#define PMU_PB13_PAD_WKUP_IRQ_W(X) ((X) << PMU_PB13_PAD_WKUP_IRQ_POS)
#define PMU_CHG_STAT_WKUP_IRQ_POS  (14U)
#define PMU_CHG_STAT_WKUP_IRQ_MSK  (0x1UL << PMU_CHG_STAT_WKUP_IRQ_POS) /*!< chg stat irq status, write 1 to clear*/
#define PMU_CHG_STAT_WKUP_IRQ      PMU_CHG_STAT_WKUP_IRQ_MSK
#define PMU_CHG_STAT_WKUP_IRQ_W(X) ((X) << PMU_CHG_STAT_WKUP_IRQ_POS)
#define PMU_CHG_DET_WKUP_IRQ_POS   (15U)
#define PMU_CHG_DET_WKUP_IRQ_MSK   (0x1UL << PMU_CHG_DET_WKUP_IRQ_POS) /*!< chg det irq status, write 1 to clear*/
#define PMU_CHG_DET_WKUP_IRQ       PMU_CHG_DET_WKUP_IRQ_MSK
#define PMU_CHG_DET_WKUP_IRQ_W(X)  ((X) << PMU_CHG_DET_WKUP_IRQ_POS)
#define PMU_RW_LP_WKUP_IRQ_POS     (16U)
#define PMU_RW_LP_WKUP_IRQ_MSK     (0x1UL << PMU_RW_LP_WKUP_IRQ_POS) /*!< rw lp osc_en irq status, write 1 to clear*/
#define PMU_RW_LP_WKUP_IRQ         PMU_RW_LP_WKUP_IRQ_MSK
#define PMU_RW_LP_WKUP_IRQ_W(X)    ((X) << PMU_RW_LP_WKUP_IRQ_POS)

//PB_WKUP_CFG0 offsetaddress : 0x64
//PB_WKUP_CFG0 RegResetValue : 0x6_0000
#define PMU_PB00_PAD_WKUP_EN_POS  (0U)
#define PMU_PB00_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB00_PAD_WKUP_EN_POS) /*!< PB00 wake up irq enable 0: disable 7: enable*/
#define PMU_PB00_PAD_WKUP_EN      PMU_PB00_PAD_WKUP_EN_MSK
#define PMU_PB00_PAD_WKUP_EN_W(X) ((X) << PMU_PB00_PAD_WKUP_EN_POS)
#define PMU_PB01_PAD_WKUP_EN_POS  (1U)
#define PMU_PB01_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB01_PAD_WKUP_EN_POS) /*!< PB01 wake up irq enable 0: disable 7: enable*/
#define PMU_PB01_PAD_WKUP_EN      PMU_PB01_PAD_WKUP_EN_MSK
#define PMU_PB01_PAD_WKUP_EN_W(X) ((X) << PMU_PB01_PAD_WKUP_EN_POS)
#define PMU_PB02_PAD_WKUP_EN_POS  (2U)
#define PMU_PB02_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB02_PAD_WKUP_EN_POS) /*!< PB02 wake up irq enable 0: disable 6: enable*/
#define PMU_PB02_PAD_WKUP_EN      PMU_PB02_PAD_WKUP_EN_MSK
#define PMU_PB02_PAD_WKUP_EN_W(X) ((X) << PMU_PB02_PAD_WKUP_EN_POS)
#define PMU_PB03_PAD_WKUP_EN_POS  (3U)
#define PMU_PB03_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB03_PAD_WKUP_EN_POS) /*!< PB03 wake up irq enable 0: disable 6: enable*/
#define PMU_PB03_PAD_WKUP_EN      PMU_PB03_PAD_WKUP_EN_MSK
#define PMU_PB03_PAD_WKUP_EN_W(X) ((X) << PMU_PB03_PAD_WKUP_EN_POS)
#define PMU_PB04_PAD_WKUP_EN_POS  (4U)
#define PMU_PB04_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB04_PAD_WKUP_EN_POS) /*!< PB04 wake up irq enable 0: disable 5: enable*/
#define PMU_PB04_PAD_WKUP_EN      PMU_PB04_PAD_WKUP_EN_MSK
#define PMU_PB04_PAD_WKUP_EN_W(X) ((X) << PMU_PB04_PAD_WKUP_EN_POS)
#define PMU_PB05_PAD_WKUP_EN_POS  (5U)
#define PMU_PB05_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB05_PAD_WKUP_EN_POS) /*!< PB05 wake up irq enable 0: disable 5: enable*/
#define PMU_PB05_PAD_WKUP_EN      PMU_PB05_PAD_WKUP_EN_MSK
#define PMU_PB05_PAD_WKUP_EN_W(X) ((X) << PMU_PB05_PAD_WKUP_EN_POS)
#define PMU_PB06_PAD_WKUP_EN_POS  (6U)
#define PMU_PB06_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB06_PAD_WKUP_EN_POS) /*!< PB06 wake up irq enable 0: disable 4: enable*/
#define PMU_PB06_PAD_WKUP_EN      PMU_PB06_PAD_WKUP_EN_MSK
#define PMU_PB06_PAD_WKUP_EN_W(X) ((X) << PMU_PB06_PAD_WKUP_EN_POS)
#define PMU_PB07_PAD_WKUP_EN_POS  (7U)
#define PMU_PB07_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB07_PAD_WKUP_EN_POS) /*!< PB07 wake up irq enable 0: disable 4: enable*/
#define PMU_PB07_PAD_WKUP_EN      PMU_PB07_PAD_WKUP_EN_MSK
#define PMU_PB07_PAD_WKUP_EN_W(X) ((X) << PMU_PB07_PAD_WKUP_EN_POS)
#define PMU_PB08_PAD_WKUP_EN_POS  (8U)
#define PMU_PB08_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB08_PAD_WKUP_EN_POS) /*!< PB08 wake up irq enable 0: disable 3: enable*/
#define PMU_PB08_PAD_WKUP_EN      PMU_PB08_PAD_WKUP_EN_MSK
#define PMU_PB08_PAD_WKUP_EN_W(X) ((X) << PMU_PB08_PAD_WKUP_EN_POS)
#define PMU_PB09_PAD_WKUP_EN_POS  (9U)
#define PMU_PB09_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB09_PAD_WKUP_EN_POS) /*!< PB09 wake up irq enable 0: disable 3: enable*/
#define PMU_PB09_PAD_WKUP_EN      PMU_PB09_PAD_WKUP_EN_MSK
#define PMU_PB09_PAD_WKUP_EN_W(X) ((X) << PMU_PB09_PAD_WKUP_EN_POS)
#define PMU_PB10_PAD_WKUP_EN_POS  (10U)
#define PMU_PB10_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB10_PAD_WKUP_EN_POS) /*!< PB10 wake up irq enable 0: disable 2: enable*/
#define PMU_PB10_PAD_WKUP_EN      PMU_PB10_PAD_WKUP_EN_MSK
#define PMU_PB10_PAD_WKUP_EN_W(X) ((X) << PMU_PB10_PAD_WKUP_EN_POS)
#define PMU_PB11_PAD_WKUP_EN_POS  (11U)
#define PMU_PB11_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB11_PAD_WKUP_EN_POS) /*!< PB11 wake up irq enable 0: disable 2: enable*/
#define PMU_PB11_PAD_WKUP_EN      PMU_PB11_PAD_WKUP_EN_MSK
#define PMU_PB11_PAD_WKUP_EN_W(X) ((X) << PMU_PB11_PAD_WKUP_EN_POS)
#define PMU_PB12_PAD_WKUP_EN_POS  (12U)
#define PMU_PB12_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB12_PAD_WKUP_EN_POS) /*!< PB12 wake up irq enable 0: disable 1: enable*/
#define PMU_PB12_PAD_WKUP_EN      PMU_PB12_PAD_WKUP_EN_MSK
#define PMU_PB12_PAD_WKUP_EN_W(X) ((X) << PMU_PB12_PAD_WKUP_EN_POS)
#define PMU_PB13_PAD_WKUP_EN_POS  (13U)
#define PMU_PB13_PAD_WKUP_EN_MSK  (0x1UL << PMU_PB13_PAD_WKUP_EN_POS) /*!< PB13 wake up irq enable 0: disable 1: enable*/
#define PMU_PB13_PAD_WKUP_EN      PMU_PB13_PAD_WKUP_EN_MSK
#define PMU_PB13_PAD_WKUP_EN_W(X) ((X) << PMU_PB13_PAD_WKUP_EN_POS)
#define PMU_CHG_STAT_WKUP_EN_POS  (14U)
#define PMU_CHG_STAT_WKUP_EN_MSK  (0x1UL << PMU_CHG_STAT_WKUP_EN_POS) /*!< charging status detect irq enable 0: disable 1: enable*/
#define PMU_CHG_STAT_WKUP_EN      PMU_CHG_STAT_WKUP_EN_MSK
#define PMU_CHG_STAT_WKUP_EN_W(X) ((X) << PMU_CHG_STAT_WKUP_EN_POS)
#define PMU_CHG_DET_WKUP_EN_POS   (15U)
#define PMU_CHG_DET_WKUP_EN_MSK   (0x1UL << PMU_CHG_DET_WKUP_EN_POS) /*!< charging box detect irq enable 0: disable 1: enable*/
#define PMU_CHG_DET_WKUP_EN       PMU_CHG_DET_WKUP_EN_MSK
#define PMU_CHG_DET_WKUP_EN_W(X)  ((X) << PMU_CHG_DET_WKUP_EN_POS)
#define PMU_RW_LP_WKUP_EN_POS     (16U)
#define PMU_RW_LP_WKUP_EN_MSK     (0x1UL << PMU_RW_LP_WKUP_EN_POS) /*!< rw lp osc_en irq enable 0: disable 1: enable*/
#define PMU_RW_LP_WKUP_EN         PMU_RW_LP_WKUP_EN_MSK
#define PMU_RW_LP_WKUP_EN_W(X)    ((X) << PMU_RW_LP_WKUP_EN_POS)
#define PMU_PB_PAD_DEB_TH_POS     (17U)
#define PMU_PB_PAD_DEB_TH_MSK     (0x7UL << PMU_PB_PAD_DEB_TH_POS) /*!< PB I/O debounce threshold*/
#define PMU_PB_PAD_DEB_TH         PMU_PB_PAD_DEB_TH_MSK
#define PMU_PB_PAD_DEB_TH_W(X)    ((X) << PMU_PB_PAD_DEB_TH_POS)

//PB_WKUP_CFG1 offsetaddress : 0x68
//PB_WKUP_CFG1 RegResetValue : 0xc0000000
#define PMU_PB00_PAD_WKUP_POL_POS  (0U)
#define PMU_PB00_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB00_PAD_WKUP_POL_POS) /*!< pb00 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB00_PAD_WKUP_POL      PMU_PB00_PAD_WKUP_POL_MSK
#define PMU_PB00_PAD_WKUP_POL_W(X) ((X) << PMU_PB00_PAD_WKUP_POL_POS)
#define PMU_PB01_PAD_WKUP_POL_POS  (1U)
#define PMU_PB01_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB01_PAD_WKUP_POL_POS) /*!< pb01 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB01_PAD_WKUP_POL      PMU_PB01_PAD_WKUP_POL_MSK
#define PMU_PB01_PAD_WKUP_POL_W(X) ((X) << PMU_PB01_PAD_WKUP_POL_POS)
#define PMU_PB02_PAD_WKUP_POL_POS  (2U)
#define PMU_PB02_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB02_PAD_WKUP_POL_POS) /*!< pb02 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB02_PAD_WKUP_POL      PMU_PB02_PAD_WKUP_POL_MSK
#define PMU_PB02_PAD_WKUP_POL_W(X) ((X) << PMU_PB02_PAD_WKUP_POL_POS)
#define PMU_PB03_PAD_WKUP_POL_POS  (3U)
#define PMU_PB03_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB03_PAD_WKUP_POL_POS) /*!< pb03 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB03_PAD_WKUP_POL      PMU_PB03_PAD_WKUP_POL_MSK
#define PMU_PB03_PAD_WKUP_POL_W(X) ((X) << PMU_PB03_PAD_WKUP_POL_POS)
#define PMU_PB04_PAD_WKUP_POL_POS  (4U)
#define PMU_PB04_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB04_PAD_WKUP_POL_POS) /*!< pb04 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB04_PAD_WKUP_POL      PMU_PB04_PAD_WKUP_POL_MSK
#define PMU_PB04_PAD_WKUP_POL_W(X) ((X) << PMU_PB04_PAD_WKUP_POL_POS)
#define PMU_PB05_PAD_WKUP_POL_POS  (5U)
#define PMU_PB05_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB05_PAD_WKUP_POL_POS) /*!< pb05 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB05_PAD_WKUP_POL      PMU_PB05_PAD_WKUP_POL_MSK
#define PMU_PB05_PAD_WKUP_POL_W(X) ((X) << PMU_PB05_PAD_WKUP_POL_POS)
#define PMU_PB06_PAD_WKUP_POL_POS  (6U)
#define PMU_PB06_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB06_PAD_WKUP_POL_POS) /*!< pb06 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB06_PAD_WKUP_POL      PMU_PB06_PAD_WKUP_POL_MSK
#define PMU_PB06_PAD_WKUP_POL_W(X) ((X) << PMU_PB06_PAD_WKUP_POL_POS)
#define PMU_PB07_PAD_WKUP_POL_POS  (7U)
#define PMU_PB07_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB07_PAD_WKUP_POL_POS) /*!< pb07 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB07_PAD_WKUP_POL      PMU_PB07_PAD_WKUP_POL_MSK
#define PMU_PB07_PAD_WKUP_POL_W(X) ((X) << PMU_PB07_PAD_WKUP_POL_POS)
#define PMU_PB08_PAD_WKUP_POL_POS  (8U)
#define PMU_PB08_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB08_PAD_WKUP_POL_POS) /*!< pb08 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB08_PAD_WKUP_POL      PMU_PB08_PAD_WKUP_POL_MSK
#define PMU_PB08_PAD_WKUP_POL_W(X) ((X) << PMU_PB08_PAD_WKUP_POL_POS)
#define PMU_PB09_PAD_WKUP_POL_POS  (9U)
#define PMU_PB09_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB09_PAD_WKUP_POL_POS) /*!< pb09 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB09_PAD_WKUP_POL      PMU_PB09_PAD_WKUP_POL_MSK
#define PMU_PB09_PAD_WKUP_POL_W(X) ((X) << PMU_PB09_PAD_WKUP_POL_POS)
#define PMU_PB10_PAD_WKUP_POL_POS  (10U)
#define PMU_PB10_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB10_PAD_WKUP_POL_POS) /*!< pb10 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB10_PAD_WKUP_POL      PMU_PB10_PAD_WKUP_POL_MSK
#define PMU_PB10_PAD_WKUP_POL_W(X) ((X) << PMU_PB10_PAD_WKUP_POL_POS)
#define PMU_PB11_PAD_WKUP_POL_POS  (11U)
#define PMU_PB11_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB11_PAD_WKUP_POL_POS) /*!< pb11 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB11_PAD_WKUP_POL      PMU_PB11_PAD_WKUP_POL_MSK
#define PMU_PB11_PAD_WKUP_POL_W(X) ((X) << PMU_PB11_PAD_WKUP_POL_POS)
#define PMU_PB12_PAD_WKUP_POL_POS  (12U)
#define PMU_PB12_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB12_PAD_WKUP_POL_POS) /*!< pb12 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB12_PAD_WKUP_POL      PMU_PB12_PAD_WKUP_POL_MSK
#define PMU_PB12_PAD_WKUP_POL_W(X) ((X) << PMU_PB12_PAD_WKUP_POL_POS)
#define PMU_PB13_PAD_WKUP_POL_POS  (13U)
#define PMU_PB13_PAD_WKUP_POL_MSK  (0x1UL << PMU_PB13_PAD_WKUP_POL_POS) /*!< pb13 wake up polarity select 0: logic high 1: logic low*/
#define PMU_PB13_PAD_WKUP_POL      PMU_PB13_PAD_WKUP_POL_MSK
#define PMU_PB13_PAD_WKUP_POL_W(X) ((X) << PMU_PB13_PAD_WKUP_POL_POS)
#define PMU_PB00_PAD_WKUP_SEL_POS  (16U)
#define PMU_PB00_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB00_PAD_WKUP_SEL_POS) /*!< pb00 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB00_PAD_WKUP_SEL      PMU_PB00_PAD_WKUP_SEL_MSK
#define PMU_PB00_PAD_WKUP_SEL_W(X) ((X) << PMU_PB00_PAD_WKUP_SEL_POS)
#define PMU_PB01_PAD_WKUP_SEL_POS  (17U)
#define PMU_PB01_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB01_PAD_WKUP_SEL_POS) /*!< pb01 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB01_PAD_WKUP_SEL      PMU_PB01_PAD_WKUP_SEL_MSK
#define PMU_PB01_PAD_WKUP_SEL_W(X) ((X) << PMU_PB01_PAD_WKUP_SEL_POS)
#define PMU_PB02_PAD_WKUP_SEL_POS  (18U)
#define PMU_PB02_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB02_PAD_WKUP_SEL_POS) /*!< pb02 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB02_PAD_WKUP_SEL      PMU_PB02_PAD_WKUP_SEL_MSK
#define PMU_PB02_PAD_WKUP_SEL_W(X) ((X) << PMU_PB02_PAD_WKUP_SEL_POS)
#define PMU_PB03_PAD_WKUP_SEL_POS  (19U)
#define PMU_PB03_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB03_PAD_WKUP_SEL_POS) /*!< pb03 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB03_PAD_WKUP_SEL      PMU_PB03_PAD_WKUP_SEL_MSK
#define PMU_PB03_PAD_WKUP_SEL_W(X) ((X) << PMU_PB03_PAD_WKUP_SEL_POS)
#define PMU_PB04_PAD_WKUP_SEL_POS  (20U)
#define PMU_PB04_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB04_PAD_WKUP_SEL_POS) /*!< pb04 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB04_PAD_WKUP_SEL      PMU_PB04_PAD_WKUP_SEL_MSK
#define PMU_PB04_PAD_WKUP_SEL_W(X) ((X) << PMU_PB04_PAD_WKUP_SEL_POS)
#define PMU_PB05_PAD_WKUP_SEL_POS  (21U)
#define PMU_PB05_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB05_PAD_WKUP_SEL_POS) /*!< pb05 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB05_PAD_WKUP_SEL      PMU_PB05_PAD_WKUP_SEL_MSK
#define PMU_PB05_PAD_WKUP_SEL_W(X) ((X) << PMU_PB05_PAD_WKUP_SEL_POS)
#define PMU_PB06_PAD_WKUP_SEL_POS  (22U)
#define PMU_PB06_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB06_PAD_WKUP_SEL_POS) /*!< pb06 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB06_PAD_WKUP_SEL      PMU_PB06_PAD_WKUP_SEL_MSK
#define PMU_PB06_PAD_WKUP_SEL_W(X) ((X) << PMU_PB06_PAD_WKUP_SEL_POS)
#define PMU_PB07_PAD_WKUP_SEL_POS  (23U)
#define PMU_PB07_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB07_PAD_WKUP_SEL_POS) /*!< pb07 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB07_PAD_WKUP_SEL      PMU_PB07_PAD_WKUP_SEL_MSK
#define PMU_PB07_PAD_WKUP_SEL_W(X) ((X) << PMU_PB07_PAD_WKUP_SEL_POS)
#define PMU_PB08_PAD_WKUP_SEL_POS  (24U)
#define PMU_PB08_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB08_PAD_WKUP_SEL_POS) /*!< pb08 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB08_PAD_WKUP_SEL      PMU_PB08_PAD_WKUP_SEL_MSK
#define PMU_PB08_PAD_WKUP_SEL_W(X) ((X) << PMU_PB08_PAD_WKUP_SEL_POS)
#define PMU_PB09_PAD_WKUP_SEL_POS  (25U)
#define PMU_PB09_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB09_PAD_WKUP_SEL_POS) /*!< pb09 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB09_PAD_WKUP_SEL      PMU_PB09_PAD_WKUP_SEL_MSK
#define PMU_PB09_PAD_WKUP_SEL_W(X) ((X) << PMU_PB09_PAD_WKUP_SEL_POS)
#define PMU_PB10_PAD_WKUP_SEL_POS  (26U)
#define PMU_PB10_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB10_PAD_WKUP_SEL_POS) /*!< pb10 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB10_PAD_WKUP_SEL      PMU_PB10_PAD_WKUP_SEL_MSK
#define PMU_PB10_PAD_WKUP_SEL_W(X) ((X) << PMU_PB10_PAD_WKUP_SEL_POS)
#define PMU_PB11_PAD_WKUP_SEL_POS  (27U)
#define PMU_PB11_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB11_PAD_WKUP_SEL_POS) /*!< pb11 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB11_PAD_WKUP_SEL      PMU_PB11_PAD_WKUP_SEL_MSK
#define PMU_PB11_PAD_WKUP_SEL_W(X) ((X) << PMU_PB11_PAD_WKUP_SEL_POS)
#define PMU_PB12_PAD_WKUP_SEL_POS  (28U)
#define PMU_PB12_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB12_PAD_WKUP_SEL_POS) /*!< pb12 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB12_PAD_WKUP_SEL      PMU_PB12_PAD_WKUP_SEL_MSK
#define PMU_PB12_PAD_WKUP_SEL_W(X) ((X) << PMU_PB12_PAD_WKUP_SEL_POS)
#define PMU_PB13_PAD_WKUP_SEL_POS  (29U)
#define PMU_PB13_PAD_WKUP_SEL_MSK  (0x1UL << PMU_PB13_PAD_WKUP_SEL_POS) /*!< pb13 wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_PB13_PAD_WKUP_SEL      PMU_PB13_PAD_WKUP_SEL_MSK
#define PMU_PB13_PAD_WKUP_SEL_W(X) ((X) << PMU_PB13_PAD_WKUP_SEL_POS)
#define PMU_CHG_STAT_WKUP_SEL_POS  (30U)
#define PMU_CHG_STAT_WKUP_SEL_MSK  (0x1UL << PMU_CHG_STAT_WKUP_SEL_POS) /*!< charging status detect wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_CHG_STAT_WKUP_SEL      PMU_CHG_STAT_WKUP_SEL_MSK
#define PMU_CHG_STAT_WKUP_SEL_W(X) ((X) << PMU_CHG_STAT_WKUP_SEL_POS)
#define PMU_CHG_DET_WKUP_SEL_POS   (31U)
#define PMU_CHG_DET_WKUP_SEL_MSK   (0x1UL << PMU_CHG_DET_WKUP_SEL_POS) /*!< charging box detect wake up source select 0: w/i debounce 1: w/o debounce*/
#define PMU_CHG_DET_WKUP_SEL       PMU_CHG_DET_WKUP_SEL_MSK
#define PMU_CHG_DET_WKUP_SEL_W(X)  ((X) << PMU_CHG_DET_WKUP_SEL_POS)

//PB_OE_MAN offsetaddress : 0x6c
//PB_OE_MAN RegResetValue : 0x0
#define PMU_PB_OUT_MAN_POS   (0U)
#define PMU_PB_OUT_MAN_MSK   (0x3fffUL << PMU_PB_OUT_MAN_POS) /*!< PB00~PB13 manual output value*/
#define PMU_PB_OUT_MAN       PMU_PB_OUT_MAN_MSK
#define PMU_PB_OUT_MAN_W(X)  ((X) << PMU_PB_OUT_MAN_POS)
#define PMU_PB_OE_MAN_POS    (16U)
#define PMU_PB_OE_MAN_MSK    (0x3fffUL << PMU_PB_OE_MAN_POS) /*!< PB00~PB13 manual output enable*/
#define PMU_PB_OE_MAN        PMU_PB_OE_MAN_MSK
#define PMU_PB_OE_MAN_W(X)   ((X) << PMU_PB_OE_MAN_POS)
#define PMU_PB_DBG_EN_0_POS  (30U)
#define PMU_PB_DBG_EN_0_MSK  (0x1UL << PMU_PB_DBG_EN_0_POS) /*!< PB04 manual output select 0: PB_OE_MAN[4] 1: pdCPU1 low power debug signal*/
#define PMU_PB_DBG_EN_0      PMU_PB_DBG_EN_0_MSK
#define PMU_PB_DBG_EN_0_W(X) ((X) << PMU_PB_DBG_EN_0_POS)
#define PMU_PB_DBG_EN_1_POS  (31U)
#define PMU_PB_DBG_EN_1_MSK  (0x1UL << PMU_PB_DBG_EN_1_POS) /*!< PB05 manual output select 0: PB_OE_MAN[5] 1: pdmcu low power debug signal*/
#define PMU_PB_DBG_EN_1      PMU_PB_DBG_EN_1_MSK
#define PMU_PB_DBG_EN_1_W(X) ((X) << PMU_PB_DBG_EN_1_POS)

//VREF offsetaddress : 0x70
//VREF RegResetValue : 0x4240
#define PMU_ENP_PTAT_50N_POS    (0U)
#define PMU_ENP_PTAT_50N_MSK    (0x1UL << PMU_ENP_PTAT_50N_POS) /*!< 50nA current source (for audio codec) enable 0: disable 1: enable*/
#define PMU_ENP_PTAT_50N        PMU_ENP_PTAT_50N_MSK
#define PMU_ENP_PTAT_50N_W(X)   ((X) << PMU_ENP_PTAT_50N_POS)
#define PMU_VREF_UVLO_TRIM_POS  (4U)
#define PMU_VREF_UVLO_TRIM_MSK  (0x7UL << PMU_VREF_UVLO_TRIM_POS) /*!< UVLO 0.9V reference calibration Step:10mV 100: 0.9V*/
#define PMU_VREF_UVLO_TRIM      PMU_VREF_UVLO_TRIM_MSK
#define PMU_VREF_UVLO_TRIM_W(X) ((X) << PMU_VREF_UVLO_TRIM_POS)
#define PMU_VREF_DAC_TRIM_POS   (7U)
#define PMU_VREF_DAC_TRIM_MSK   (0x7UL << PMU_VREF_DAC_TRIM_POS) /*!< DAC 0.9V Reference Calibration Step:10mV 100: 0.9V*/
#define PMU_VREF_DAC_TRIM       PMU_VREF_DAC_TRIM_MSK
#define PMU_VREF_DAC_TRIM_W(X)  ((X) << PMU_VREF_DAC_TRIM_POS)
#define PMU_VREF_ADC_TRIM_POS   (12U)
#define PMU_VREF_ADC_TRIM_MSK   (0x7UL << PMU_VREF_ADC_TRIM_POS) /*!< ADC 0.9V reference calibration Step:10mV 100: 0.9V*/
#define PMU_VREF_ADC_TRIM       PMU_VREF_ADC_TRIM_MSK
#define PMU_VREF_ADC_TRIM_W(X)  ((X) << PMU_VREF_ADC_TRIM_POS)

//MIC_BIAS offsetaddress : 0x74
//MIC_BIAS RegResetValue : 0x42
#define PMU_MIC_BIAS_SEL_POS   (0U)
#define PMU_MIC_BIAS_SEL_MSK   (0x7UL << PMU_MIC_BIAS_SEL_POS) /*!< VMIC_BIAS Output Voltage Selection 000:1.7 001:1.75 010:1.8 (default) 011:1.85 100:1.9 101:1.95 110:2.0 111:2.05*/
#define PMU_MIC_BIAS_SEL       PMU_MIC_BIAS_SEL_MSK
#define PMU_MIC_BIAS_SEL_W(X)  ((X) << PMU_MIC_BIAS_SEL_POS)
#define PMU_MIC_BIAS_TRIM_POS  (4U)
#define PMU_MIC_BIAS_TRIM_MSK  (0x7UL << PMU_MIC_BIAS_TRIM_POS) /*!< VMIC_BIAS Output Voltage Calibration Step:10mV 100: 0.9V(default)*/
#define PMU_MIC_BIAS_TRIM      PMU_MIC_BIAS_TRIM_MSK
#define PMU_MIC_BIAS_TRIM_W(X) ((X) << PMU_MIC_BIAS_TRIM_POS)
#define PMU_ENP_MIC_BIAS_POS   (9U)
#define PMU_ENP_MIC_BIAS_MSK   (0x1UL << PMU_ENP_MIC_BIAS_POS) /*!< VMIC_BIAS Enable 0: disable 1: enable*/
#define PMU_ENP_MIC_BIAS       PMU_ENP_MIC_BIAS_MSK
#define PMU_ENP_MIC_BIAS_W(X)  ((X) << PMU_ENP_MIC_BIAS_POS)

//RC_OSC offsetaddress : 0x78
//RC_OSC RegResetValue : 0x124_4020
#define PMU_OSC_CLK_48M_TRIM_POS          (0U)
#define PMU_OSC_CLK_48M_TRIM_MSK          (0x3fUL << PMU_OSC_CLK_48M_TRIM_POS) /*!< 48MHz RC OSC Calibration Control Word Manual Register*/
#define PMU_OSC_CLK_48M_TRIM              PMU_OSC_CLK_48M_TRIM_MSK
#define PMU_OSC_CLK_48M_TRIM_W(X)         ((X) << PMU_OSC_CLK_48M_TRIM_POS)
#define PMU_OSC_CLK_48M_TRIM_REG_SEL_POS  (6U)
#define PMU_OSC_CLK_48M_TRIM_REG_SEL_MSK  (0x1UL << PMU_OSC_CLK_48M_TRIM_REG_SEL_POS) /*!< 48MHz RCO calibration control word selection 0: from manual register 1: from calibration module*/
#define PMU_OSC_CLK_48M_TRIM_REG_SEL      PMU_OSC_CLK_48M_TRIM_REG_SEL_MSK
#define PMU_OSC_CLK_48M_TRIM_REG_SEL_W(X) ((X) << PMU_OSC_CLK_48M_TRIM_REG_SEL_POS)
#define PMU_OSC_CLK_32K_TRIM_POS          (8U)
#define PMU_OSC_CLK_32K_TRIM_MSK          (0x7fUL << PMU_OSC_CLK_32K_TRIM_POS) /*!< 32KHz RC OSC calibration control word manual register, default 32KHz*/
#define PMU_OSC_CLK_32K_TRIM              PMU_OSC_CLK_32K_TRIM_MSK
#define PMU_OSC_CLK_32K_TRIM_W(X)         ((X) << PMU_OSC_CLK_32K_TRIM_POS)
#define PMU_OSC_CLK_32K_TRIM_REG_SEL_POS  (15U)
#define PMU_OSC_CLK_32K_TRIM_REG_SEL_MSK  (0x1UL << PMU_OSC_CLK_32K_TRIM_REG_SEL_POS) /*!< 32KHz RCO calibration control word selection 0: from manual register 1: from calibration module*/
#define PMU_OSC_CLK_32K_TRIM_REG_SEL      PMU_OSC_CLK_32K_TRIM_REG_SEL_MSK
#define PMU_OSC_CLK_32K_TRIM_REG_SEL_W(X) ((X) << PMU_OSC_CLK_32K_TRIM_REG_SEL_POS)
#define PMU_VOL_48M_TRIM_POS              (16U)
#define PMU_VOL_48M_TRIM_MSK              (0x7UL << PMU_VOL_48M_TRIM_POS) /*!< 48MHz RCO LDO calibration*/
#define PMU_VOL_48M_TRIM                  PMU_VOL_48M_TRIM_MSK
#define PMU_VOL_48M_TRIM_W(X)             ((X) << PMU_VOL_48M_TRIM_POS)
#define PMU_VOL_32K_TRIM_POS              (19U)
#define PMU_VOL_32K_TRIM_MSK              (0x7UL << PMU_VOL_32K_TRIM_POS) /*!< 32KHz RCO LDO calibration*/
#define PMU_VOL_32K_TRIM                  PMU_VOL_32K_TRIM_MSK
#define PMU_VOL_32K_TRIM_W(X)             ((X) << PMU_VOL_32K_TRIM_POS)
#define PMU_LDO_OSC_TRIM_POS              (22U)
#define PMU_LDO_OSC_TRIM_MSK              (0x7UL << PMU_LDO_OSC_TRIM_POS) /*!< LDO_OSC output voltage calibration Step:10mV 100:0.9V*/
#define PMU_LDO_OSC_TRIM                  PMU_LDO_OSC_TRIM_MSK
#define PMU_LDO_OSC_TRIM_W(X)             ((X) << PMU_LDO_OSC_TRIM_POS)

//CHARGER offsetaddress : 0x7c
//CHARGER RegResetValue : 0x2aa2_b090
#define PMU_CHG_DET_POS        (0U)
#define PMU_CHG_DET_MSK        (0x1UL << PMU_CHG_DET_POS) /*!< Input Test 0: Not in the warehouse 1: Input*/
#define PMU_CHG_DET            PMU_CHG_DET_MSK
#define PMU_CHG_DET_W(X)       ((X) << PMU_CHG_DET_POS)
#define PMU_CHG_RS_TRIM_POS    (1U)
#define PMU_CHG_RS_TRIM_MSK    (0xfUL << PMU_CHG_RS_TRIM_POS) /*!< RS value configure  uRSET=80K Step:1K*/
#define PMU_CHG_RS_TRIM        PMU_CHG_RS_TRIM_MSK
#define PMU_CHG_RS_TRIM_W(X)   ((X) << PMU_CHG_RS_TRIM_POS)
#define PMU_CHG_STAT_POS       (5U)
#define PMU_CHG_STAT_MSK       (0x1UL << PMU_CHG_STAT_POS) /*!< Charger status 0: not charging 1: charging*/
#define PMU_CHG_STAT           PMU_CHG_STAT_MSK
#define PMU_CHG_STAT_W(X)      ((X) << PMU_CHG_STAT_POS)
#define PMU_CHG_PLUG_FLAG_POS  (6U)
#define PMU_CHG_PLUG_FLAG_MSK  (0x1UL << PMU_CHG_PLUG_FLAG_POS) /*!< Adaptor plug/pull flag 1:  plug or voltage is above 4.2V 0:  pull or voltage is below 4.2V*/
#define PMU_CHG_PLUG_FLAG      PMU_CHG_PLUG_FLAG_MSK
#define PMU_CHG_PLUG_FLAG_W(X) ((X) << PMU_CHG_PLUG_FLAG_POS)
#define PMU_CHG_CTM_SEL_POS    (7U)
#define PMU_CHG_CTM_SEL_MSK    (0x3UL << PMU_CHG_CTM_SEL_POS) /*!< Charging Terminate Ratio 00: 10% 01: 5%(default) 10:2.5% 11:0%*/
#define PMU_CHG_CTM_SEL        PMU_CHG_CTM_SEL_MSK
#define PMU_CHG_CTM_SEL_W(X)   ((X) << PMU_CHG_CTM_SEL_POS)
#define PMU_CHG_CV_SEL_POS     (9U)
#define PMU_CHG_CV_SEL_MSK     (0x7UL << PMU_CHG_CV_SEL_POS) /*!< Regulation Voltage set 000: 4.2V(default) 001: 4.3V 010: 4.4V 011: 4.5V 100: 3.8V 101: 3.9V 110: 4.0V 111: 4.1V*/
#define PMU_CHG_CV_SEL         PMU_CHG_CV_SEL_MSK
#define PMU_CHG_CV_SEL_W(X)    ((X) << PMU_CHG_CV_SEL_POS)
#define PMU_CHG_CC_SEL_POS     (12U)
#define PMU_CHG_CC_SEL_MSK \
    (0x3fUL                \
     << PMU_CHG_CC_SEL_POS) /*!< Constant charging current set (mA) 00_0000 to 01_1000: 5 01_1001: 10 01_1010: 15 01_1011: 20 01_1100: 25 01_1101: 30 01_1110: 35 01_1111: 40 10_0000: 45 10_0001: 50 10_0010: 55 10_0011: 60 10_0100: 65 10_0101: 70 10_0110: 75 10_0111: 80 10_1000: 85 10_1001: 90 10_1010: 95 10_1011: 100 (default) 10_1100: 105 10_1101: 110 10_1110: 115 10_1111: 120 11_0000: 125 11_0001: 130 … 11_1110: 195 11_1111: 200*/
#define PMU_CHG_CC_SEL          PMU_CHG_CC_SEL_MSK
#define PMU_CHG_CC_SEL_W(X)     ((X) << PMU_CHG_CC_SEL_POS)
#define PMU_CHG_VREF_TRIM_POS   (18U)
#define PMU_CHG_VREF_TRIM_MSK   (0xfUL << PMU_CHG_VREF_TRIM_POS) /*!< VREF Calibration Control Step: 30mV 1000*/
#define PMU_CHG_VREF_TRIM       PMU_CHG_VREF_TRIM_MSK
#define PMU_CHG_VREF_TRIM_W(X)  ((X) << PMU_CHG_VREF_TRIM_POS)
#define PMU_CHG_PG_TRIM_POS     (23U)
#define PMU_CHG_PG_TRIM_MSK     (0x3UL << PMU_CHG_PG_TRIM_POS) /*!< Power Good Trimming 00:1.025 01:1.05 (default) 10:1.075 11:1.1*/
#define PMU_CHG_PG_TRIM         PMU_CHG_PG_TRIM_MSK
#define PMU_CHG_PG_TRIM_W(X)    ((X) << PMU_CHG_PG_TRIM_POS)
#define PMU_CHG_TRK_SEL_POS     (25U)
#define PMU_CHG_TRK_SEL_MSK     (0x1UL << PMU_CHG_TRK_SEL_POS) /*!< Trickle and pre-charge ratio 0:10% (trickle), 20% (pre-chg) 1:5% (trickle), 10% (pre-chg)*/
#define PMU_CHG_TRK_SEL         PMU_CHG_TRK_SEL_MSK
#define PMU_CHG_TRK_SEL_W(X)    ((X) << PMU_CHG_TRK_SEL_POS)
#define PMU_CHG_STOP_POS        (26U)
#define PMU_CHG_STOP_MSK        (0x1UL << PMU_CHG_STOP_POS) /*!< Charging prohibit 0: enable charging 1: disable charging*/
#define PMU_CHG_STOP            PMU_CHG_STOP_MSK
#define PMU_CHG_STOP_W(X)       ((X) << PMU_CHG_STOP_POS)
#define PMU_CHG_DEB_CNT_TH_POS  (27U)
#define PMU_CHG_DEB_CNT_TH_MSK  (0x7UL << PMU_CHG_DEB_CNT_TH_POS) /*!< Charge status signal (analog chg plug*/
#define PMU_CHG_DEB_CNT_TH      PMU_CHG_DEB_CNT_TH_MSK
#define PMU_CHG_DEB_CNT_TH_W(X) ((X) << PMU_CHG_DEB_CNT_TH_POS)
#define PMU_CHG_SEL_HW_POS      (30U)
#define PMU_CHG_SEL_HW_MSK      (0x1UL << PMU_CHG_SEL_HW_POS) /*!< chg_cc_sel/chg_cv_sel/chg_stop control select 0: from pmu register 1: from hw temp detect*/
#define PMU_CHG_SEL_HW          PMU_CHG_SEL_HW_MSK
#define PMU_CHG_SEL_HW_W(X)     ((X) << PMU_CHG_SEL_HW_POS)

//LDO_DIG offsetaddress : 0x80
//LDO_DIG RegResetValue : 0x7746
#define PMU_LDO_DIG_SEL_POS   (0U)
#define PMU_LDO_DIG_SEL_MSK   (0xfUL << PMU_LDO_DIG_SEL_POS) /*!< LDO_DIG Output voltage selection 0000: 0.65V 0001: 0.675V 0010: 0.7V 0011: 0.725V 0100: 0.75V 0101: 0.775V 0110: 0.8V(default) 0111: 0.825V 1000: 0.85V 1001: 0.875V 1010: 0.9V 1011: 0.925V 1100: 0.95V 1101: 0.975V 1110: 1.0V 1111: 1.025V*/
#define PMU_LDO_DIG_SEL       PMU_LDO_DIG_SEL_MSK
#define PMU_LDO_DIG_SEL_W(X)  ((X) << PMU_LDO_DIG_SEL_POS)
#define PMU_LDO_DIG_TRIM_POS  (4U)
#define PMU_LDO_DIG_TRIM_MSK  (0x7UL << PMU_LDO_DIG_TRIM_POS) /*!< Output calibration Step:10mV 100: 0.4V(default)*/
#define PMU_LDO_DIG_TRIM      PMU_LDO_DIG_TRIM_MSK
#define PMU_LDO_DIG_TRIM_W(X) ((X) << PMU_LDO_DIG_TRIM_POS)
#define PMU_ENP_LDO_RET_POS   (7U)
#define PMU_ENP_LDO_RET_MSK   (0x1UL << PMU_ENP_LDO_RET_POS) /*!< LDO_RET enable 0: disable 1: enable*/
#define PMU_ENP_LDO_RET       PMU_ENP_LDO_RET_MSK
#define PMU_ENP_LDO_RET_W(X)  ((X) << PMU_ENP_LDO_RET_POS)
#define PMU_LDO_RET_SEL_POS   (8U)
#define PMU_LDO_RET_SEL_MSK \
    (0xfUL << PMU_LDO_RET_SEL_POS) /*!< LDO_RET Output voltage selection (manual or auto work mode) 0000: 0.65V 0001: 0.675V 0010: 0.7V 0011: 0.725V 0100: 0.75V 0101: 0.775V 0110: 0.825V(default) 1000: 0.85V 1001: 0.875V 1010: 0.9V 1011: 0.925V 1100: 0.95V 1101: 0.975V 1110: 1.0V 1111: 1.025V*/
#define PMU_LDO_RET_SEL      PMU_LDO_RET_SEL_MSK
#define PMU_LDO_RET_SEL_W(X) ((X) << PMU_LDO_RET_SEL_POS)
#define PMU_LDO_AON_SEL_POS  (12U)
#define PMU_LDO_AON_SEL_MSK \
    (0xfUL << PMU_LDO_AON_SEL_POS) /*!< LDO_AON Output voltage selection (manual or auto work mode) 0000: 0.65V 0001: 0.675V 0010: 0.7V 0011: 0.725V 0100: 0.75V 0101: 0.775V 0110: 0.825V (default) 1000: 0.85V 1001: 0.875V 1010: 0.9V 1011: 0.925V 1100: 0.95V 1101: 0.975V 1110: 1.0V 1111: 1.025V*/
#define PMU_LDO_AON_SEL      PMU_LDO_AON_SEL_MSK
#define PMU_LDO_AON_SEL_W(X) ((X) << PMU_LDO_AON_SEL_POS)

//LDO_ANA offsetaddress : 0x84
//LDO_ANA RegResetValue : 0x9b30_98cc
#define PMU_ENP_IDLE_RFPA_POS  (0U)
#define PMU_ENP_IDLE_RFPA_MSK  (0x1UL << PMU_ENP_IDLE_RFPA_POS) /*!< LDO_RFPA Low Power Mode Enable 0: shutdown 1: low power*/
#define PMU_ENP_IDLE_RFPA      PMU_ENP_IDLE_RFPA_MSK
#define PMU_ENP_IDLE_RFPA_W(X) ((X) << PMU_ENP_IDLE_RFPA_POS)
#define PMU_LDO_CDC_SEL_POS    (1U)
#define PMU_LDO_CDC_SEL_MSK    (0x7UL << PMU_LDO_CDC_SEL_POS) /*!< LDO_CDC output voltage selection 000: 1.5V 001: 1.55V 010: 1.6V 011: 1.65V 100: 1.7V 101: 1.75V 110: 1.8V (default) 111: 1.85V*/
#define PMU_LDO_CDC_SEL        PMU_LDO_CDC_SEL_MSK
#define PMU_LDO_CDC_SEL_W(X)   ((X) << PMU_LDO_CDC_SEL_POS)
#define PMU_LDO_CDC_TRIM_POS   (4U)
#define PMU_LDO_CDC_TRIM_MSK   (0x7UL << PMU_LDO_CDC_TRIM_POS) /*!< LDO_CDC Output Voltage Calibration Step:20mV 100: 1.8V*/
#define PMU_LDO_CDC_TRIM       PMU_LDO_CDC_TRIM_MSK
#define PMU_LDO_CDC_TRIM_W(X)  ((X) << PMU_LDO_CDC_TRIM_POS)
#define PMU_CDC_ANA_ISOX_POS   (7U)
#define PMU_CDC_ANA_ISOX_MSK   (0x1UL << PMU_CDC_ANA_ISOX_POS) /*!< Codec Analog Side Signal Isolation 0: normal 1: isolation*/
#define PMU_CDC_ANA_ISOX       PMU_CDC_ANA_ISOX_MSK
#define PMU_CDC_ANA_ISOX_W(X)  ((X) << PMU_CDC_ANA_ISOX_POS)
#define PMU_ENP_LDO_CDC_POS    (8U)
#define PMU_ENP_LDO_CDC_MSK    (0x1UL << PMU_ENP_LDO_CDC_POS) /*!< LDO_CDC Enable 0: disable 1: enable*/
#define PMU_ENP_LDO_CDC        PMU_ENP_LDO_CDC_MSK
#define PMU_ENP_LDO_CDC_W(X)   ((X) << PMU_ENP_LDO_CDC_POS)
#define PMU_ENP_LDO_RFPA_POS   (9U)
#define PMU_ENP_LDO_RFPA_MSK   (0x1UL << PMU_ENP_LDO_RFPA_POS) /*!< LDO_RFPA output enable (manual mode) 0: disable 1: enable*/
#define PMU_ENP_LDO_RFPA       PMU_ENP_LDO_RFPA_MSK
#define PMU_ENP_LDO_RFPA_W(X)  ((X) << PMU_ENP_LDO_RFPA_POS)
#define PMU_LDO_ANA_SEL_POS    (10U)
#define PMU_LDO_ANA_SEL_MSK    (0x7UL << PMU_LDO_ANA_SEL_POS) /*!< LDO_ANA output voltage selection 000: 1.5V 001: 1.55V 010: 1.6V 011: 1.65V 100: 1.7V 101: 1.75V 110: 1.8V (default) 111: 1.85V*/
#define PMU_LDO_ANA_SEL        PMU_LDO_ANA_SEL_MSK
#define PMU_LDO_ANA_SEL_W(X)   ((X) << PMU_LDO_ANA_SEL_POS)
#define PMU_LDO_ANA_TRIM_POS   (13U)
#define PMU_LDO_ANA_TRIM_MSK   (0x7UL << PMU_LDO_ANA_TRIM_POS) /*!< LDO_ANA Output Voltage Calibration Step:10mV 100: 0.9V(default)*/
#define PMU_LDO_ANA_TRIM       PMU_LDO_ANA_TRIM_MSK
#define PMU_LDO_ANA_TRIM_W(X)  ((X) << PMU_LDO_ANA_TRIM_POS)
#define PMU_ENP_LDO_ANA_POS    (17U)
#define PMU_ENP_LDO_ANA_MSK    (0x1UL << PMU_ENP_LDO_ANA_POS) /*!< LDO_ANA Enable 0: disable 1: enable*/
#define PMU_ENP_LDO_ANA        PMU_ENP_LDO_ANA_MSK
#define PMU_ENP_LDO_ANA_W(X)   ((X) << PMU_ENP_LDO_ANA_POS)
#define PMU_LDO_IO_TRIM_POS    (18U)
#define PMU_LDO_IO_TRIM_MSK    (0x7UL << PMU_LDO_IO_TRIM_POS) /*!< LDO_IO Output Voltage Calibration Step:10mV 100: 0.9(default)*/
#define PMU_LDO_IO_TRIM        PMU_LDO_IO_TRIM_MSK
#define PMU_LDO_IO_TRIM_W(X)   ((X) << PMU_LDO_IO_TRIM_POS)
#define PMU_LDO_IO_SEL_POS     (21U)
#define PMU_LDO_IO_SEL_MSK \
    (0xfUL                 \
     << PMU_LDO_IO_SEL_POS) /*!< LDO_IO Output voltage selection (manual or auto work mode) 0000: 2.55V 0001: 2.6V 0010: 2.65V 0011: 2.7V 0100: 2.75V 0101: 2.80V 0110: 2.85V 0111: 2.9V 1000: 2.95V 1001: 3.0V(default) 1010: 3.05V 1011: 3.1V 1100: 3.15V 1101: 3.2V 1110: 3.25V 1111: 3.3V*/
#define PMU_LDO_IO_SEL       PMU_LDO_IO_SEL_MSK
#define PMU_LDO_IO_SEL_W(X)  ((X) << PMU_LDO_IO_SEL_POS)
#define PMU_LDO_RFPA_SEL_POS (25U)
#define PMU_LDO_RFPA_SEL_MSK \
    (0xfUL                   \
     << PMU_LDO_RFPA_SEL_POS) /*!< LDO_RFPA Output voltage selection (manual or auto work mode) 0000: 2.0V 0001: 2.1V 0010: 2.2V 0011: 2.3V 0100: 2.4V 0101: 2.5V 0110: 2.6V 0111: 2.7V 1000: 2.8V 1001: 2.9V 1010: 3.0V 1011: 3.1V 1100: 3.2V 1101: 3.3V(default) 1110: 3.4V 1111: 3.5V*/
#define PMU_LDO_RFPA_SEL       PMU_LDO_RFPA_SEL_MSK
#define PMU_LDO_RFPA_SEL_W(X)  ((X) << PMU_LDO_RFPA_SEL_POS)
#define PMU_LDO_RFPA_TRIM_POS  (29U)
#define PMU_LDO_RFPA_TRIM_MSK  (0x7UL << PMU_LDO_RFPA_TRIM_POS) /*!< LDO_RFPA Output Voltage Calibration Step:10mV 100: 0.9(default)*/
#define PMU_LDO_RFPA_TRIM      PMU_LDO_RFPA_TRIM_MSK
#define PMU_LDO_RFPA_TRIM_W(X) ((X) << PMU_LDO_RFPA_TRIM_POS)

//BUCK_DIG offsetaddress : 0x88
//BUCK_DIG RegResetValue : 0x1902_451c
#define PMU_BUCK_DIG_TRIM_POS       (0U)
#define PMU_BUCK_DIG_TRIM_MSK       (0x7UL << PMU_BUCK_DIG_TRIM_POS) /*!< VREF step=10mV 100: 0.6V*/
#define PMU_BUCK_DIG_TRIM           PMU_BUCK_DIG_TRIM_MSK
#define PMU_BUCK_DIG_TRIM_W(X)      ((X) << PMU_BUCK_DIG_TRIM_POS)
#define PMU_BUCK_DIG_SEL_POS        (3U)
#define PMU_BUCK_DIG_SEL_MSK        (0x7UL << PMU_BUCK_DIG_SEL_POS) /*!< BUCK_DIG output voltage selection 000: 1.05V 001: 1.1V 010: 1.15V 011: 1.2V (default) 100: 1.25V 101: 1.3V 110: 1.35V 111: 1.4V*/
#define PMU_BUCK_DIG_SEL            PMU_BUCK_DIG_SEL_MSK
#define PMU_BUCK_DIG_SEL_W(X)       ((X) << PMU_BUCK_DIG_SEL_POS)
#define PMU_BUCK_DIG_ZCD_SEL_POS    (6U)
#define PMU_BUCK_DIG_ZCD_SEL_MSK    (0x7UL << PMU_BUCK_DIG_ZCD_SEL_POS) /*!< BUCK_DIG reverse current threshold 100: 0*/
#define PMU_BUCK_DIG_ZCD_SEL        PMU_BUCK_DIG_ZCD_SEL_MSK
#define PMU_BUCK_DIG_ZCD_SEL_W(X)   ((X) << PMU_BUCK_DIG_ZCD_SEL_POS)
#define PMU_BUCK_DIG_OCP_SEL_POS    (9U)
#define PMU_BUCK_DIG_OCP_SEL_MSK    (0x3UL << PMU_BUCK_DIG_OCP_SEL_POS) /*!< Peak inductor current 00: 100mA 01: 200mA 10: 300mA 11: 400mA*/
#define PMU_BUCK_DIG_OCP_SEL        PMU_BUCK_DIG_OCP_SEL_MSK
#define PMU_BUCK_DIG_OCP_SEL_W(X)   ((X) << PMU_BUCK_DIG_OCP_SEL_POS)
#define PMU_BUCK_DIG_PSK_SEL_POS    (11U)
#define PMU_BUCK_DIG_PSK_SEL_MSK    (0xfUL << PMU_BUCK_DIG_PSK_SEL_POS) /*!< 0000: 0 0001: 25mV 0010: 50mV 0011: 75mV 0100: 100mV 0101: 125mV 0110: 150mV 0111: 175mV 1000: 200mV 1001: 225mV 1010: 250mV 1011: 275mV 1100: 300mV 1101: 325mV 1110: 350mV 1111: 375m*/
#define PMU_BUCK_DIG_PSK_SEL        PMU_BUCK_DIG_PSK_SEL_MSK
#define PMU_BUCK_DIG_PSK_SEL_W(X)   ((X) << PMU_BUCK_DIG_PSK_SEL_POS)
#define PMU_BUCK_DIG_SLP_SEL_POS    (15U)
#define PMU_BUCK_DIG_SLP_SEL_MSK    (0x7UL << PMU_BUCK_DIG_SLP_SEL_POS) /*!< Slope compensation selection*/
#define PMU_BUCK_DIG_SLP_SEL        PMU_BUCK_DIG_SLP_SEL_MSK
#define PMU_BUCK_DIG_SLP_SEL_W(X)   ((X) << PMU_BUCK_DIG_SLP_SEL_POS)
#define PMU_BUCK_DIG_EAO_CLAMP_POS  (18U)
#define PMU_BUCK_DIG_EAO_CLAMP_MSK  (0x3UL << PMU_BUCK_DIG_EAO_CLAMP_POS) /*!< [19]: clamp eao low level [18]: clamp eao high level*/
#define PMU_BUCK_DIG_EAO_CLAMP      PMU_BUCK_DIG_EAO_CLAMP_MSK
#define PMU_BUCK_DIG_EAO_CLAMP_W(X) ((X) << PMU_BUCK_DIG_EAO_CLAMP_POS)
#define PMU_BUCK_OSC_TRIM_POS       (20U)
#define PMU_BUCK_OSC_TRIM_MSK       (0x1fUL << PMU_BUCK_OSC_TRIM_POS) /*!< Oscillator frequency calibration 00000: 1.6M (can be large) ... 10000: 2M (guaranteed) ... 11101: 2.4M (can be small)*/
#define PMU_BUCK_OSC_TRIM           PMU_BUCK_OSC_TRIM_MSK
#define PMU_BUCK_OSC_TRIM_W(X)      ((X) << PMU_BUCK_OSC_TRIM_POS)
#define PMU_VOL_BUCK_OSC_TRIM_POS   (25U)
#define PMU_VOL_BUCK_OSC_TRIM_MSK   (0x7UL << PMU_VOL_BUCK_OSC_TRIM_POS) /*!< Buck osc power-supply voltage trim*/
#define PMU_VOL_BUCK_OSC_TRIM       PMU_VOL_BUCK_OSC_TRIM_MSK
#define PMU_VOL_BUCK_OSC_TRIM_W(X)  ((X) << PMU_VOL_BUCK_OSC_TRIM_POS)
#define PMU_ENP_DIG_PSK_HYS_POS     (28U)
#define PMU_ENP_DIG_PSK_HYS_MSK     (0x1UL << PMU_ENP_DIG_PSK_HYS_POS) /*!< 0: disable hys control 1: enable hys control*/
#define PMU_ENP_DIG_PSK_HYS         PMU_ENP_DIG_PSK_HYS_MSK
#define PMU_ENP_DIG_PSK_HYS_W(X)    ((X) << PMU_ENP_DIG_PSK_HYS_POS)
#define PMU_ENP_BUCK_DIG_LP_POS     (29U)
#define PMU_ENP_BUCK_DIG_LP_MSK     (0x1UL << PMU_ENP_BUCK_DIG_LP_POS) /*!< Low power control (at PSK mode) 0: disable LP 1: enable LP*/
#define PMU_ENP_BUCK_DIG_LP         PMU_ENP_BUCK_DIG_LP_MSK
#define PMU_ENP_BUCK_DIG_LP_W(X)    ((X) << PMU_ENP_BUCK_DIG_LP_POS)

//BUCK_ANA offsetaddress : 0x8c
//BUCK_ANA RegResetValue : 0x12_451c
#define PMU_BUCK_ANA_TRIM_POS       (0U)
#define PMU_BUCK_ANA_TRIM_MSK       (0x7UL << PMU_BUCK_ANA_TRIM_POS) /*!< VREF step=10mV 100: 0.6V*/
#define PMU_BUCK_ANA_TRIM           PMU_BUCK_ANA_TRIM_MSK
#define PMU_BUCK_ANA_TRIM_W(X)      ((X) << PMU_BUCK_ANA_TRIM_POS)
#define PMU_BUCK_ANA_SEL_POS        (3U)
#define PMU_BUCK_ANA_SEL_MSK        (0x7UL << PMU_BUCK_ANA_SEL_POS) /*!< BUCK_ANA output voltage selection 000: 1.85V 001: 1.9V 010: 1.95V 011: 2.0V (default) 100: 2.05V 101: 2.1V 110: 2.15V 111: 2.2V*/
#define PMU_BUCK_ANA_SEL            PMU_BUCK_ANA_SEL_MSK
#define PMU_BUCK_ANA_SEL_W(X)       ((X) << PMU_BUCK_ANA_SEL_POS)
#define PMU_BUCK_ANA_ZCD_SEL_POS    (6U)
#define PMU_BUCK_ANA_ZCD_SEL_MSK    (0x7UL << PMU_BUCK_ANA_ZCD_SEL_POS) /*!< BUCK_ANA reverse current threshold 100: 0*/
#define PMU_BUCK_ANA_ZCD_SEL        PMU_BUCK_ANA_ZCD_SEL_MSK
#define PMU_BUCK_ANA_ZCD_SEL_W(X)   ((X) << PMU_BUCK_ANA_ZCD_SEL_POS)
#define PMU_BUCK_ANA_OCP_SEL_POS    (9U)
#define PMU_BUCK_ANA_OCP_SEL_MSK    (0x3UL << PMU_BUCK_ANA_OCP_SEL_POS) /*!< Peak inductor current 00: 100mA 01: 200mA 10: 300mA 11: 400mA*/
#define PMU_BUCK_ANA_OCP_SEL        PMU_BUCK_ANA_OCP_SEL_MSK
#define PMU_BUCK_ANA_OCP_SEL_W(X)   ((X) << PMU_BUCK_ANA_OCP_SEL_POS)
#define PMU_BUCK_ANA_PSK_SEL_POS    (11U)
#define PMU_BUCK_ANA_PSK_SEL_MSK    (0xfUL << PMU_BUCK_ANA_PSK_SEL_POS) /*!< 0000: 0 0001: 25mV 0010: 50mV 0011: 75mV 0100: 100mV 0101: 125mV 0110: 150mV 0111: 175mV 1000: 200mV 1001: 225mV 1010: 250mV 1011: 275mV 1100: 300mV 1101: 325mV 1110: 350mV 1111: 375m*/
#define PMU_BUCK_ANA_PSK_SEL        PMU_BUCK_ANA_PSK_SEL_MSK
#define PMU_BUCK_ANA_PSK_SEL_W(X)   ((X) << PMU_BUCK_ANA_PSK_SEL_POS)
#define PMU_BUCK_ANA_SLP_SEL_POS    (15U)
#define PMU_BUCK_ANA_SLP_SEL_MSK    (0x7UL << PMU_BUCK_ANA_SLP_SEL_POS) /*!< BUCK_ANA slope selection*/
#define PMU_BUCK_ANA_SLP_SEL        PMU_BUCK_ANA_SLP_SEL_MSK
#define PMU_BUCK_ANA_SLP_SEL_W(X)   ((X) << PMU_BUCK_ANA_SLP_SEL_POS)
#define PMU_BUCK_ANA_EAO_CLAMP_POS  (18U)
#define PMU_BUCK_ANA_EAO_CLAMP_MSK  (0x3UL << PMU_BUCK_ANA_EAO_CLAMP_POS) /*!< [19]: clamp eao low level [18]: clamp eao high level*/
#define PMU_BUCK_ANA_EAO_CLAMP      PMU_BUCK_ANA_EAO_CLAMP_MSK
#define PMU_BUCK_ANA_EAO_CLAMP_W(X) ((X) << PMU_BUCK_ANA_EAO_CLAMP_POS)
#define PMU_ENP_ANA_PSK_HYS_POS     (20U)
#define PMU_ENP_ANA_PSK_HYS_MSK     (0x1UL << PMU_ENP_ANA_PSK_HYS_POS) /*!< 0: disable hys control 1: enable hys control*/
#define PMU_ENP_ANA_PSK_HYS         PMU_ENP_ANA_PSK_HYS_MSK
#define PMU_ENP_ANA_PSK_HYS_W(X)    ((X) << PMU_ENP_ANA_PSK_HYS_POS)
#define PMU_ENP_BUCK_ANA_LP_POS     (21U)
#define PMU_ENP_BUCK_ANA_LP_MSK     (0x1UL << PMU_ENP_BUCK_ANA_LP_POS) /*!< Low power control (at PSK mode) 0: disable LP 1: enable LP*/
#define PMU_ENP_BUCK_ANA_LP         PMU_ENP_BUCK_ANA_LP_MSK
#define PMU_ENP_BUCK_ANA_LP_W(X)    ((X) << PMU_ENP_BUCK_ANA_LP_POS)

//CODEC_CFG0 offsetaddress : 0x90
//CODEC_CFG0 RegResetValue : 0x0
#define PMU_HPAMP_OFC_FORCE_CODE_L_POS  (0U)
#define PMU_HPAMP_OFC_FORCE_CODE_L_MSK  (0x7fUL << PMU_HPAMP_OFC_FORCE_CODE_L_POS) /*!< OFC code to be forced to autx Lch HPAMP.*/
#define PMU_HPAMP_OFC_FORCE_CODE_L      PMU_HPAMP_OFC_FORCE_CODE_L_MSK
#define PMU_HPAMP_OFC_FORCE_CODE_L_W(X) ((X) << PMU_HPAMP_OFC_FORCE_CODE_L_POS)
#define PMU_HPAMP_OFC_FORCE_L_POS       (7U)
#define PMU_HPAMP_OFC_FORCE_L_MSK       (0x1UL << PMU_HPAMP_OFC_FORCE_L_POS) /*!< Force OFC code i_cfg_hpamp_ofc_force_code_l[6:0] to autx Lch HPAMP: 0 = Don`t force. 1 = Force.*/
#define PMU_HPAMP_OFC_FORCE_L           PMU_HPAMP_OFC_FORCE_L_MSK
#define PMU_HPAMP_OFC_FORCE_L_W(X)      ((X) << PMU_HPAMP_OFC_FORCE_L_POS)
#define PMU_HPAMP_OFC_FORCE_CODE_R_POS  (8U)
#define PMU_HPAMP_OFC_FORCE_CODE_R_MSK  (0x7fUL << PMU_HPAMP_OFC_FORCE_CODE_R_POS) /*!< OFC code to be forced to autx Rch HPAMP.*/
#define PMU_HPAMP_OFC_FORCE_CODE_R      PMU_HPAMP_OFC_FORCE_CODE_R_MSK
#define PMU_HPAMP_OFC_FORCE_CODE_R_W(X) ((X) << PMU_HPAMP_OFC_FORCE_CODE_R_POS)
#define PMU_HPAMP_OFC_FORCE_R_POS       (15U)
#define PMU_HPAMP_OFC_FORCE_R_MSK       (0x1UL << PMU_HPAMP_OFC_FORCE_R_POS) /*!< Force OFC code i_cfg_hpamp_ofc_force_code_r[6:0] to autx Rch HPAMP:0 = Don`t force.1 = Force.*/
#define PMU_HPAMP_OFC_FORCE_R           PMU_HPAMP_OFC_FORCE_R_MSK
#define PMU_HPAMP_OFC_FORCE_R_W(X)      ((X) << PMU_HPAMP_OFC_FORCE_R_POS)
#define PMU_AUTX_OFC_FORCE_L_POS        (16U)
#define PMU_AUTX_OFC_FORCE_L_MSK        (0x1UL << PMU_AUTX_OFC_FORCE_L_POS) /*!< Force OFC code i_cfg_autx_ofc_force_code1_l[7:0] and i_cfg_autx_ofc_force_code2_l[7:0] to autx Lch path:0 = Don`t force. 1 = Force.*/
#define PMU_AUTX_OFC_FORCE_L            PMU_AUTX_OFC_FORCE_L_MSK
#define PMU_AUTX_OFC_FORCE_L_W(X)       ((X) << PMU_AUTX_OFC_FORCE_L_POS)
#define PMU_AUTX_OFC_FORCE_R_POS        (17U)
#define PMU_AUTX_OFC_FORCE_R_MSK        (0x1UL << PMU_AUTX_OFC_FORCE_R_POS) /*!< Force OFC code i_cfg_autx_ofc_force_code1_r[7:0] and i_cfg_autx_ofc_force_code2_r[7:0] to autx Rch path:0 = Don`t force. 1 = Force.*/
#define PMU_AUTX_OFC_FORCE_R            PMU_AUTX_OFC_FORCE_R_MSK
#define PMU_AUTX_OFC_FORCE_R_W(X)       ((X) << PMU_AUTX_OFC_FORCE_R_POS)

//CODEC_CFG1 offsetaddress : 0x94
//CODEC_CFG1 RegResetValue : 0x0
#define PMU_AUTX_OFC_FORCE_CODE1_L_POS  (0U)
#define PMU_AUTX_OFC_FORCE_CODE1_L_MSK  (0xffUL << PMU_AUTX_OFC_FORCE_CODE1_L_POS) /*!< The 1st OFC code to be forced to autx Lch path.*/
#define PMU_AUTX_OFC_FORCE_CODE1_L      PMU_AUTX_OFC_FORCE_CODE1_L_MSK
#define PMU_AUTX_OFC_FORCE_CODE1_L_W(X) ((X) << PMU_AUTX_OFC_FORCE_CODE1_L_POS)
#define PMU_AUTX_OFC_FORCE_CODE1_R_POS  (8U)
#define PMU_AUTX_OFC_FORCE_CODE1_R_MSK  (0xffUL << PMU_AUTX_OFC_FORCE_CODE1_R_POS) /*!< The 1st OFC code to be forced to autx Rch path.*/
#define PMU_AUTX_OFC_FORCE_CODE1_R      PMU_AUTX_OFC_FORCE_CODE1_R_MSK
#define PMU_AUTX_OFC_FORCE_CODE1_R_W(X) ((X) << PMU_AUTX_OFC_FORCE_CODE1_R_POS)
#define PMU_AUTX_OFC_FORCE_CODE2_L_POS  (16U)
#define PMU_AUTX_OFC_FORCE_CODE2_L_MSK  (0xffUL << PMU_AUTX_OFC_FORCE_CODE2_L_POS) /*!< The 2nd OFC code to be forced to autx Lch path.*/
#define PMU_AUTX_OFC_FORCE_CODE2_L      PMU_AUTX_OFC_FORCE_CODE2_L_MSK
#define PMU_AUTX_OFC_FORCE_CODE2_L_W(X) ((X) << PMU_AUTX_OFC_FORCE_CODE2_L_POS)
#define PMU_AUTX_OFC_FORCE_CODE2_R_POS  (24U)
#define PMU_AUTX_OFC_FORCE_CODE2_R_MSK  (0xffUL << PMU_AUTX_OFC_FORCE_CODE2_R_POS) /*!< The 2nd OFC code to be forced to autx Rch path.*/
#define PMU_AUTX_OFC_FORCE_CODE2_R      PMU_AUTX_OFC_FORCE_CODE2_R_MSK
#define PMU_AUTX_OFC_FORCE_CODE2_R_W(X) ((X) << PMU_AUTX_OFC_FORCE_CODE2_R_POS)

//RF_CFG0 offsetaddress : 0x98
//RF_CFG0 RegResetValue : 0x82
#define PMU_AON_TSTBUF_VCM_POS         (0U)
#define PMU_AON_TSTBUF_VCM_MSK         (0x3UL << PMU_AON_TSTBUF_VCM_POS) /*!< */
#define PMU_AON_TSTBUF_VCM             PMU_AON_TSTBUF_VCM_MSK
#define PMU_AON_TSTBUF_VCM_W(X)        ((X) << PMU_AON_TSTBUF_VCM_POS)
#define PMU_AON_TSTBUF_RXEN_POS        (2U)
#define PMU_AON_TSTBUF_RXEN_MSK        (0x1UL << PMU_AON_TSTBUF_RXEN_POS) /*!< */
#define PMU_AON_TSTBUF_RXEN            PMU_AON_TSTBUF_RXEN_MSK
#define PMU_AON_TSTBUF_RXEN_W(X)       ((X) << PMU_AON_TSTBUF_RXEN_POS)
#define PMU_AON_TSTBUF_TXEN_POS        (3U)
#define PMU_AON_TSTBUF_TXEN_MSK        (0x1UL << PMU_AON_TSTBUF_TXEN_POS) /*!< */
#define PMU_AON_TSTBUF_TXEN            PMU_AON_TSTBUF_TXEN_MSK
#define PMU_AON_TSTBUF_TXEN_W(X)       ((X) << PMU_AON_TSTBUF_TXEN_POS)
#define PMU_AON_TSTBUF_EN_POS          (4U)
#define PMU_AON_TSTBUF_EN_MSK          (0x1UL << PMU_AON_TSTBUF_EN_POS) /*!< */
#define PMU_AON_TSTBUF_EN              PMU_AON_TSTBUF_EN_MSK
#define PMU_AON_TSTBUF_EN_W(X)         ((X) << PMU_AON_TSTBUF_EN_POS)
#define PMU_BBPLL_BG_TRIM_POS          (5U)
#define PMU_BBPLL_BG_TRIM_MSK          (0x7UL << PMU_BBPLL_BG_TRIM_POS) /*!< bbpll bandgap trim control signal*/
#define PMU_BBPLL_BG_TRIM              PMU_BBPLL_BG_TRIM_MSK
#define PMU_BBPLL_BG_TRIM_W(X)         ((X) << PMU_BBPLL_BG_TRIM_POS)
#define PMU_XO_CLKSEL_DIG_POS          (10U)
#define PMU_XO_CLKSEL_DIG_MSK          (0x1UL << PMU_XO_CLKSEL_DIG_POS) /*!< clock frequency select for clk_mdm: 0: 24MHz 1: 48MHz*/
#define PMU_XO_CLKSEL_DIG              PMU_XO_CLKSEL_DIG_MSK
#define PMU_XO_CLKSEL_DIG_W(X)         ((X) << PMU_XO_CLKSEL_DIG_POS)
#define PMU_XO_DUTYC_POS               (11U)
#define PMU_XO_DUTYC_MSK               (0x3UL << PMU_XO_DUTYC_POS) /*!< */
#define PMU_XO_DUTYC                   PMU_XO_DUTYC_MSK
#define PMU_XO_DUTYC_W(X)              ((X) << PMU_XO_DUTYC_POS)
#define PMU_XO_CLKTAHDT_EN_POS           (13U)
#define PMU_XO_CLKTAHDT_EN_MSK           (0x1UL << PMU_XO_CLKTAHDT_EN_POS) /*!< */
#define PMU_XO_CLKTAHDT_EN               PMU_XO_CLKTAHDT_EN_MSK
#define PMU_XO_CLKTAHDT_EN_W(X)          ((X) << PMU_XO_CLKTAHDT_EN_POS)
#define PMU_BT_SYS_RF_REG_SRC_SEL_POS  (21U)
#define PMU_BT_SYS_RF_REG_SRC_SEL_MSK  (0x1UL << PMU_BT_SYS_RF_REG_SRC_SEL_POS) /*!< */
#define PMU_BT_SYS_RF_REG_SRC_SEL      PMU_BT_SYS_RF_REG_SRC_SEL_MSK
#define PMU_BT_SYS_RF_REG_SRC_SEL_W(X) ((X) << PMU_BT_SYS_RF_REG_SRC_SEL_POS)

//RF_CFG1 offsetaddress : 0x9c
//RF_CFG1 RegResetValue : 0x827_ba90
#define PMU_CLK_STATUS_POS           (0U)
#define PMU_CLK_STATUS_MSK           (0x1UL << PMU_CLK_STATUS_POS) /*!< */
#define PMU_CLK_STATUS               PMU_CLK_STATUS_MSK
#define PMU_CLK_STATUS_W(X)          ((X) << PMU_CLK_STATUS_POS)
#define PMU_WAKEUP_REG_POS           (1U)
#define PMU_WAKEUP_REG_MSK           (0x1UL << PMU_WAKEUP_REG_POS) /*!< */
#define PMU_WAKEUP_REG               PMU_WAKEUP_REG_MSK
#define PMU_WAKEUP_REG_W(X)          ((X) << PMU_WAKEUP_REG_POS)
#define PMU_XO_DIAGSEL_POS           (2U)
#define PMU_XO_DIAGSEL_MSK           (0x1UL << PMU_XO_DIAGSEL_POS) /*!< */
#define PMU_XO_DIAGSEL               PMU_XO_DIAGSEL_MSK
#define PMU_XO_DIAGSEL_W(X)          ((X) << PMU_XO_DIAGSEL_POS)
#define PMU_XO_LDO_DIAGSEL_POS       (3U)
#define PMU_XO_LDO_DIAGSEL_MSK       (0x1UL << PMU_XO_LDO_DIAGSEL_POS) /*!< */
#define PMU_XO_LDO_DIAGSEL           PMU_XO_LDO_DIAGSEL_MSK
#define PMU_XO_LDO_DIAGSEL_W(X)      ((X) << PMU_XO_LDO_DIAGSEL_POS)
#define PMU_XO_LDO_TRIM_POS          (4U)
#define PMU_XO_LDO_TRIM_MSK          (0x3UL << PMU_XO_LDO_TRIM_POS) /*!< */
#define PMU_XO_LDO_TRIM              PMU_XO_LDO_TRIM_MSK
#define PMU_XO_LDO_TRIM_W(X)         ((X) << PMU_XO_LDO_TRIM_POS)
#define PMU_XO_FSTART_POS            (6U)
#define PMU_XO_FSTART_MSK            (0x1UL << PMU_XO_FSTART_POS) /*!< */
#define PMU_XO_FSTART                PMU_XO_FSTART_MSK
#define PMU_XO_FSTART_W(X)           ((X) << PMU_XO_FSTART_POS)
#define PMU_XO_IBIT_POS              (7U)
#define PMU_XO_IBIT_MSK              (0xfUL << PMU_XO_IBIT_POS) /*!< */
#define PMU_XO_IBIT                  PMU_XO_IBIT_MSK
#define PMU_XO_IBIT_W(X)             ((X) << PMU_XO_IBIT_POS)
#define PMU_XO_CFIX_POS              (11U)
#define PMU_XO_CFIX_MSK              (0x7UL << PMU_XO_CFIX_POS) /*!< */
#define PMU_XO_CFIX                  PMU_XO_CFIX_MSK
#define PMU_XO_CFIX_W(X)             ((X) << PMU_XO_CFIX_POS)
#define PMU_XO_CTUNE_POS             (14U)
#define PMU_XO_CTUNE_MSK             (0x3fUL << PMU_XO_CTUNE_POS) /*!< */
#define PMU_XO_CTUNE                 PMU_XO_CTUNE_MSK
#define PMU_XO_CTUNE_W(X)            ((X) << PMU_XO_CTUNE_POS)
#define PMU_XO_EN_CLKRF_EN_POS       (20U)
#define PMU_XO_EN_CLKRF_EN_MSK       (0x1UL << PMU_XO_EN_CLKRF_EN_POS) /*!< */
#define PMU_XO_EN_CLKRF_EN           PMU_XO_EN_CLKRF_EN_MSK
#define PMU_XO_EN_CLKRF_EN_W(X)      ((X) << PMU_XO_EN_CLKRF_EN_POS)
#define PMU_XO_EN_CLKDIG_EN_POS      (21U)
#define PMU_XO_EN_CLKDIG_EN_MSK      (0x1UL << PMU_XO_EN_CLKDIG_EN_POS) /*!< */
#define PMU_XO_EN_CLKDIG_EN          PMU_XO_EN_CLKDIG_EN_MSK
#define PMU_XO_EN_CLKDIG_EN_W(X)     ((X) << PMU_XO_EN_CLKDIG_EN_POS)
#define PMU_XO_EN_CLKBBPLL_EN_POS    (22U)
#define PMU_XO_EN_CLKBBPLL_EN_MSK    (0x1UL << PMU_XO_EN_CLKBBPLL_EN_POS) /*!< */
#define PMU_XO_EN_CLKBBPLL_EN        PMU_XO_EN_CLKBBPLL_EN_MSK
#define PMU_XO_EN_CLKBBPLL_EN_W(X)   ((X) << PMU_XO_EN_CLKBBPLL_EN_POS)
#define PMU_XO_EN_CLKBB_EN_POS       (23U)
#define PMU_XO_EN_CLKBB_EN_MSK       (0x1UL << PMU_XO_EN_CLKBB_EN_POS) /*!< */
#define PMU_XO_EN_CLKBB_EN           PMU_XO_EN_CLKBB_EN_MSK
#define PMU_XO_EN_CLKBB_EN_W(X)      ((X) << PMU_XO_EN_CLKBB_EN_POS)
#define PMU_XO_LDO_FCHG_POS          (24U)
#define PMU_XO_LDO_FCHG_MSK          (0x1UL << PMU_XO_LDO_FCHG_POS) /*!< xo ldo fast charge manual value if xo_auto is 0*/
#define PMU_XO_LDO_FCHG              PMU_XO_LDO_FCHG_MSK
#define PMU_XO_LDO_FCHG_W(X)         ((X) << PMU_XO_LDO_FCHG_POS)
#define PMU_XO_LDO_PUP_POS           (25U)
#define PMU_XO_LDO_PUP_MSK           (0x1UL << PMU_XO_LDO_PUP_POS) /*!< xo ldo power up manual value if xo_auto is 0*/
#define PMU_XO_LDO_PUP               PMU_XO_LDO_PUP_MSK
#define PMU_XO_LDO_PUP_W(X)          ((X) << PMU_XO_LDO_PUP_POS)
#define PMU_XO_PUP_POS               (26U)
#define PMU_XO_PUP_MSK               (0x1UL << PMU_XO_PUP_POS) /*!< xo power up manual value if xo_auto is 0*/
#define PMU_XO_PUP                   PMU_XO_PUP_MSK
#define PMU_XO_PUP_W(X)              ((X) << PMU_XO_PUP_POS)
#define PMU_XO_AUTO_POS              (27U)
#define PMU_XO_AUTO_MSK              (0x1UL << PMU_XO_AUTO_POS) /*!< */
#define PMU_XO_AUTO                  PMU_XO_AUTO_MSK
#define PMU_XO_AUTO_W(X)             ((X) << PMU_XO_AUTO_POS)
#define PMU_BBPLL_BG_FORCE_POS       (28U)
#define PMU_BBPLL_BG_FORCE_MSK       (0x1UL << PMU_BBPLL_BG_FORCE_POS) /*!< bbpll bandgap force startup control signal, 1: force startup, 0: normal startup*/
#define PMU_BBPLL_BG_FORCE           PMU_BBPLL_BG_FORCE_MSK
#define PMU_BBPLL_BG_FORCE_W(X)      ((X) << PMU_BBPLL_BG_FORCE_POS)
#define PMU_BBPLL_BG_PUP_POS         (29U)
#define PMU_BBPLL_BG_PUP_MSK         (0x1UL << PMU_BBPLL_BG_PUP_POS) /*!< bbpll bandgap power up control signal, 1: power up, 0: power down*/
#define PMU_BBPLL_BG_PUP             PMU_BBPLL_BG_PUP_MSK
#define PMU_BBPLL_BG_PUP_W(X)        ((X) << PMU_BBPLL_BG_PUP_POS)
#define PMU_BBPLL_BG_PUP_IBG_XO_POS  (30U)
#define PMU_BBPLL_BG_PUP_IBG_XO_MSK  (0x1UL << PMU_BBPLL_BG_PUP_IBG_XO_POS) /*!< bbpll bandgap ibg bias to xo enable control signal, 1: enable, 0: disable*/
#define PMU_BBPLL_BG_PUP_IBG_XO      PMU_BBPLL_BG_PUP_IBG_XO_MSK
#define PMU_BBPLL_BG_PUP_IBG_XO_W(X) ((X) << PMU_BBPLL_BG_PUP_IBG_XO_POS)
#define PMU_XO_CLKX2_EN_POS          (31U)
#define PMU_XO_CLKX2_EN_MSK          (0x1UL << PMU_XO_CLKX2_EN_POS) /*!< 48MHz doubler clock enable*/
#define PMU_XO_CLKX2_EN              PMU_XO_CLKX2_EN_MSK
#define PMU_XO_CLKX2_EN_W(X)         ((X) << PMU_XO_CLKX2_EN_POS)

//SW_USB offsetaddress : 0xa0
//SW_USB RegResetValue : 0x0
#define PMU_ENP_SW_USB_POS  (0U)
#define PMU_ENP_SW_USB_MSK  (0x1UL << PMU_ENP_SW_USB_POS) /*!< SW_USB Enable 0: disable 1: enable*/
#define PMU_ENP_SW_USB      PMU_ENP_SW_USB_MSK
#define PMU_ENP_SW_USB_W(X) ((X) << PMU_ENP_SW_USB_POS)
#define PMU_ENP_SW_EFU_POS  (1U)
#define PMU_ENP_SW_EFU_MSK  (0x1UL << PMU_ENP_SW_EFU_POS) /*!< SW_EFU Enable 0: disable 1: enable*/
#define PMU_ENP_SW_EFU      PMU_ENP_SW_EFU_MSK
#define PMU_ENP_SW_EFU_W(X) ((X) << PMU_ENP_SW_EFU_POS)

//TEMP_SENSOR offsetaddress : 0xa4
//TEMP_SENSOR RegResetValue : 0x88
#define PMU_TS_SLOPE_SEL_POS  (0U)
#define PMU_TS_SLOPE_SEL_MSK  (0xfUL << PMU_TS_SLOPE_SEL_POS) /*!< TS Slope Calibration (mV/℃) 0000: 2.91 0001: 3.045 0010: 3.18 0011: 3.31 0100: 3.46 0101: 3.56 0110: 3.73 0111: 3.86 1000: 4.01 1001: 4.14 1010: 4.28 1011: 4.41 1100: 4.55 1101: 4.69 1110: 4.83 1111: 4.96*/
#define PMU_TS_SLOPE_SEL      PMU_TS_SLOPE_SEL_MSK
#define PMU_TS_SLOPE_SEL_W(X) ((X) << PMU_TS_SLOPE_SEL_POS)
#define PMU_TS_AM_TRIM_POS    (4U)
#define PMU_TS_AM_TRIM_MSK    (0xfUL << PMU_TS_AM_TRIM_POS) /*!< TS room temperature calibration*/
#define PMU_TS_AM_TRIM        PMU_TS_AM_TRIM_MSK
#define PMU_TS_AM_TRIM_W(X)   ((X) << PMU_TS_AM_TRIM_POS)
#define PMU_ENP_TSN_POS       (8U)
#define PMU_ENP_TSN_MSK       (0x1UL << PMU_ENP_TSN_POS) /*!< Temperature sensor enable 0: disable 1: enable*/
#define PMU_ENP_TSN           PMU_ENP_TSN_MSK
#define PMU_ENP_TSN_W(X)      ((X) << PMU_ENP_TSN_POS)

//GP_REG0 offsetaddress : 0xb0
//GP_REG0 RegResetValue : 0x0
#define PMU_GP_REG0_POS  (0U)
#define PMU_GP_REG0_MSK  (0xffffffffUL << PMU_GP_REG0_POS) /*!< general purpose retention register 0*/
#define PMU_GP_REG0      PMU_GP_REG0_MSK
#define PMU_GP_REG0_W(X) ((X) << PMU_GP_REG0_POS)

//GP_REG1 offsetaddress : 0xb4
//GP_REG1 RegResetValue : 0x0
#define PMU_GP_REG1_POS  (0U)
#define PMU_GP_REG1_MSK  (0xffffffffUL << PMU_GP_REG1_POS) /*!< general purpose retention register 1*/
#define PMU_GP_REG1      PMU_GP_REG1_MSK
#define PMU_GP_REG1_W(X) ((X) << PMU_GP_REG1_POS)

//GP_REG2 offsetaddress : 0xb8
//GP_REG2 RegResetValue : 0x0
#define PMU_GP_REG2_POS  (0U)
#define PMU_GP_REG2_MSK  (0xffffffffUL << PMU_GP_REG2_POS) /*!< general purpose retention register 2*/
#define PMU_GP_REG2      PMU_GP_REG2_MSK
#define PMU_GP_REG2_W(X) ((X) << PMU_GP_REG2_POS)

//GP_REG3 offsetaddress : 0xbc
//GP_REG3 RegResetValue : 0x0
#define PMU_GP_REG3_POS  (0U)
#define PMU_GP_REG3_MSK  (0xffffffffUL << PMU_GP_REG3_POS) /*!< general purpose retention register 3*/
#define PMU_GP_REG3      PMU_GP_REG3_MSK
#define PMU_GP_REG3_W(X) ((X) << PMU_GP_REG3_POS)

//GP_REG4 offsetaddress : 0xc0
//GP_REG4 RegResetValue : 0x0
#define PMU_GP_REG4_POS  (0U)
#define PMU_GP_REG4_MSK  (0xffffffffUL << PMU_GP_REG4_POS) /*!< general purpose retention register 4*/
#define PMU_GP_REG4      PMU_GP_REG4_MSK
#define PMU_GP_REG4_W(X) ((X) << PMU_GP_REG4_POS)

//GP_REG5 offsetaddress : 0xc4
//GP_REG5 RegResetValue : 0x0
#define PMU_GP_REG5_POS  (0U)
#define PMU_GP_REG5_MSK  (0xffffffffUL << PMU_GP_REG5_POS) /*!< general purpose retention register 5*/
#define PMU_GP_REG5      PMU_GP_REG5_MSK
#define PMU_GP_REG5_W(X) ((X) << PMU_GP_REG5_POS)

//GP_REG6 offsetaddress : 0xc8
//GP_REG6 RegResetValue : 0x0
#define PMU_GP_REG6_POS  (0U)
#define PMU_GP_REG6_MSK  (0xffffffffUL << PMU_GP_REG6_POS) /*!< general purpose retention register 6*/
#define PMU_GP_REG6      PMU_GP_REG6_MSK
#define PMU_GP_REG6_W(X) ((X) << PMU_GP_REG6_POS)

//GP_REG7 offsetaddress : 0xcc
//GP_REG7 RegResetValue : 0x0
#define PMU_GP_REG7_POS  (0U)
#define PMU_GP_REG7_MSK  (0xffffffffUL << PMU_GP_REG7_POS) /*!< general purpose retention register 7*/
#define PMU_GP_REG7      PMU_GP_REG7_MSK
#define PMU_GP_REG7_W(X) ((X) << PMU_GP_REG7_POS)

//RPD_CFG offsetaddress : 0xd0
//RPD_CFG RegResetValue : 0x2
#define PMU_RPD_FREQ_DIFF_THD_POS  (0U)
#define PMU_RPD_FREQ_DIFF_THD_MSK  (0x3fUL << PMU_RPD_FREQ_DIFF_THD_POS) /*!< Reset pattern detection module frequency estimation threshold. If the frequency estimation phase fluctuates more than the set threshold value during the frequency estimation phase, the frequency estimation fails.*/
#define PMU_RPD_FREQ_DIFF_THD      PMU_RPD_FREQ_DIFF_THD_MSK
#define PMU_RPD_FREQ_DIFF_THD_W(X) ((X) << PMU_RPD_FREQ_DIFF_THD_POS)
#define PMU_RPD_MASK_POS           (6U)
#define PMU_RPD_MASK_MSK           (0x1UL << PMU_RPD_MASK_POS) /*!< Reset pattern detection module blocks signals; 0 – not blocked; 1 – blocked;*/
#define PMU_RPD_MASK               PMU_RPD_MASK_MSK
#define PMU_RPD_MASK_W(X)          ((X) << PMU_RPD_MASK_POS)

//PAD_SINGLE_WIRE offsetaddress : 0xd4
//PAD_SINGLE_WIRE RegResetValue : 0x26
#define PMU_PB_SWIRE_CTRL_POS  (0U)
#define PMU_PB_SWIRE_CTRL_MSK  (0x3fUL << PMU_PB_SWIRE_CTRL_POS) /*!< PAD single wire ctrl register*/
#define PMU_PB_SWIRE_CTRL      PMU_PB_SWIRE_CTRL_MSK
#define PMU_PB_SWIRE_CTRL_W(X) ((X) << PMU_PB_SWIRE_CTRL_POS)
#define PMU_PB_SWIRE_MODE_POS  (6U)
#define PMU_PB_SWIRE_MODE_MSK  (0x1UL << PMU_PB_SWIRE_MODE_POS) /*!< PAD single wire output mode 0: normal cmos drive 1: pullup/pulldown drive*/
#define PMU_PB_SWIRE_MODE      PMU_PB_SWIRE_MODE_MSK
#define PMU_PB_SWIRE_MODE_W(X) ((X) << PMU_PB_SWIRE_MODE_POS)
#define PMU_PD_VBUS_POS        (7U)
#define PMU_PD_VBUS_MSK        (0x1UL << PMU_PD_VBUS_POS) /*!< Force VBUS low level when VBUS is not powered 0 – normal 1 – force VBUS to low level if there's no driving source*/
#define PMU_PD_VBUS            PMU_PD_VBUS_MSK
#define PMU_PD_VBUS_W(X)       ((X) << PMU_PD_VBUS_POS)

typedef struct {
    volatile uint32_t RST_SET_AO; //offsetaddress : 0x00
    volatile uint32_t rev_0[(0x08 - 0x00) / 4 - 1];
    volatile uint32_t CLK_EN_M_AO; //offsetaddress : 0x08
    volatile uint32_t rev_1[(0x10 - 0x08) / 4 - 1];
    volatile uint32_t CPU0_RESET_VECTOR; //offsetaddress : 0x10
    volatile uint32_t CPU1_RESET_VECTOR; //offsetaddress : 0x14
    volatile uint32_t CPU0_SP;           //offsetaddress : 0x18
    volatile uint32_t CPU1_SP;           //offsetaddress : 0x1c
    volatile uint32_t AUTO_PWDN_CTRL;    //offsetaddress : 0x20
    volatile uint32_t POWER_CFG0;        //offsetaddress : 0x24
    volatile uint32_t POWER_CFG1;        //offsetaddress : 0x28
    volatile uint32_t POWER_CFG2;        //offsetaddress : 0x2c
    volatile uint32_t SLP_CTRL;          //offsetaddress : 0x30
    volatile uint32_t RET_RAM_CTRL_0;    //offsetaddress : 0x34
    volatile uint32_t RET_RAM_CTRL_1;    //offsetaddress : 0x38
    volatile uint32_t RET_RAM_CTRL_2;    //offsetaddress : 0x3c
    volatile uint32_t SOFT_PWDN_CTRL;    //offsetaddress : 0x40
    volatile uint32_t rev_2[(0x50 - 0x40) / 4 - 1];
    volatile uint32_t PB_IE_CFG;    //offsetaddress : 0x50
    volatile uint32_t PB_CTRL_0;    //offsetaddress : 0x54
    volatile uint32_t PB_CTRL_1;    //offsetaddress : 0x58
    volatile uint32_t PB_CTRL_2;    //offsetaddress : 0x5c
    volatile uint32_t PB_WKUP_IRQ;  //offsetaddress : 0x60
    volatile uint32_t PB_WKUP_CFG0; //offsetaddress : 0x64
    volatile uint32_t PB_WKUP_CFG1; //offsetaddress : 0x68
    volatile uint32_t PB_OE_MAN;    //offsetaddress : 0x6c
    volatile uint32_t VREF;         //offsetaddress : 0x70
    volatile uint32_t MIC_BIAS;     //offsetaddress : 0x74
    volatile uint32_t RC_OSC;       //offsetaddress : 0x78
    volatile uint32_t CHARGER;      //offsetaddress : 0x7c
    volatile uint32_t LDO_DIG;      //offsetaddress : 0x80
    volatile uint32_t LDO_ANA;      //offsetaddress : 0x84
    volatile uint32_t BUCK_DIG;     //offsetaddress : 0x88
    volatile uint32_t BUCK_ANA;     //offsetaddress : 0x8c
    volatile uint32_t CODEC_CFG0;   //offsetaddress : 0x90
    volatile uint32_t CODEC_CFG1;   //offsetaddress : 0x94
    volatile uint32_t RF_CFG0;      //offsetaddress : 0x98
    volatile uint32_t RF_CFG1;      //offsetaddress : 0x9c
    volatile uint32_t SW_USB;       //offsetaddress : 0xa0
    volatile uint32_t TEMP_SENSOR;  //offsetaddress : 0xa4
    volatile uint32_t rev_3[(0xb0 - 0xa4) / 4 - 1];
    volatile uint32_t GP_REG0;         //offsetaddress : 0xb0
    volatile uint32_t GP_REG1;         //offsetaddress : 0xb4
    volatile uint32_t GP_REG2;         //offsetaddress : 0xb8
    volatile uint32_t GP_REG3;         //offsetaddress : 0xbc
    volatile uint32_t GP_REG4;         //offsetaddress : 0xc0
    volatile uint32_t GP_REG5;         //offsetaddress : 0xc4
    volatile uint32_t GP_REG6;         //offsetaddress : 0xc8
    volatile uint32_t GP_REG7;         //offsetaddress : 0xcc
    volatile uint32_t RPD_CFG;         //offsetaddress : 0xd0
    volatile uint32_t PAD_SINGLE_WIRE; //offsetaddress : 0xd4
} pmu_reg_t;
#ifdef __cplusplus
}
#endif
#endif
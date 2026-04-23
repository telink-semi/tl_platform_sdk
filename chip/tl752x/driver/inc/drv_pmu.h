/*******************************************************************************************************
 *
 * @file    drv_pmu.h
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
#ifndef __DRV_PMU_H__
#define __DRV_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "modules/pmu.h"
#include "tl_chip.h"
#include "modules/drv_pmu_ex.h"

/********************************** MIC BIAS **********************************/
#define __DRV_PMU_SET_MIC_BIAS_SEL(__MIC_BIAS_SEL__)   MODIFY_REG(PMU->MIC_BIAS, PMU_MIC_BIAS_SEL_MSK, __MIC_BIAS_SEL__ << PMU_MIC_BIAS_SEL_POS)
#define __DRV_PMU_SET_MIC_BIAS_TRIM(__MIC_BIAS_TRIM__) MODIFY_REG(PMU->MIC_BIAS, PMU_MIC_BIAS_TRIM_MSK, __MIC_BIAS_TRIM__ << PMU_MIC_BIAS_TRIM_POS)

/********************************** LDO_DIG **********************************/
#define __DRV_PMU_SET_LDO_DIG_SEL(__LDO_DIG_SEL__)   MODIFY_REG(PMU->LDO_DIG, PMU_LDO_DIG_SEL_MSK, __LDO_DIG_SEL__ << PMU_LDO_DIG_SEL_POS)
#define __DRV_PMU_SET_LDO_DIG_TRIM(__LDO_DIG_TRIM__) MODIFY_REG(PMU->LDO_DIG, PMU_LDO_DIG_TRIM_MSK, __LDO_DIG_TRIM__ << PMU_LDO_DIG_TRIM_POS)

#define __DRV_PMU_SET_LDO_AON_SEL(__LDO_AON_SEL__) MODIFY_REG(PMU->LDO_DIG, PMU_LDO_AON_SEL_MSK, __LDO_AON_SEL__ << PMU_LDO_AON_SEL_POS)
#define __DRV_PMU_SET_LDO_RET_SEL(__LDO_RET_SEL__) MODIFY_REG(PMU->LDO_DIG, PMU_LDO_RET_SEL_MSK, __LDO_RET_SEL__ << PMU_LDO_RET_SEL_POS)
#define __DRV_PMU_LDO_RET_ENABLE()                 SET_BIT(PMU->LDO_DIG, PMU_ENP_LDO_RET_MSK)
#define __DRV_PMU_LDO_RET_DISABLE()                CLEAR_BIT(PMU->LDO_DIG, PMU_ENP_LDO_RET_MSK)
/********************************** LDO_ANA **********************************/
#define __DRV_PMU_LDO_RFPA_ENABLE()                    SET_BIT(PMU->LDO_ANA, PMU_ENP_IDLE_RFPA_MSK | PMU_ENP_LDO_RFPA_MSK)
#define __DRV_PMU_LDO_RFPA_DISABLE()                   CLEAR_BIT(PMU->LDO_ANA, PMU_ENP_IDLE_RFPA_MSK | PMU_ENP_LDO_RFPA_MSK)
#define __DRV_PMU_SET_LDO_RFPA_SEL(__LDO_RFPA_SEL__)   MODIFY_REG(PMU->LDO_ANA, PMU_LDO_RFPA_SEL_MSK, __LDO_RFPA_SEL__ << PMU_LDO_RFPA_SEL_POS)
#define __DRV_PMU_SET_LDO_RFPA_TRIM(__LDO_RFPA_TRIM__) MODIFY_REG(PMU->LDO_ANA, PMU_LDO_RFPA_TRIM_MSK, __LDO_RFPA_TRIM__ << PMU_LDO_RFPA_TRIM_POS)

#define __DRV_PMU_SET_LDO_IO_SEL(__LDO_IO_SEL__)   MODIFY_REG(PMU->LDO_ANA, PMU_LDO_IO_SEL_MSK, __LDO_IO_SEL__ << PMU_LDO_IO_SEL_POS)
#define __DRV_PMU_SET_LDO_IO_TRIM(__LDO_IO_TRIM__) MODIFY_REG(PMU->LDO_ANA, PMU_LDO_IO_TRIM_MSK, __LDO_IO_TRIM__ << PMU_LDO_IO_TRIM_POS)

#define __DRV_PMU_SET_LDO_ANA_SEL(__LDO_ANA_SEL__)   MODIFY_REG(PMU->LDO_ANA, PMU_LDO_ANA_SEL_MSK, __LDO_ANA_SEL__ << PMU_LDO_ANA_SEL_POS)
#define __DRV_PMU_SET_LDO_ANA_TRIM(__LDO_ANA_TRIM__) MODIFY_REG(PMU->LDO_ANA, PMU_LDO_ANA_TRIM_MSK, __LDO_ANA_TRIM__ << PMU_LDO_ANA_TRIM_POS)

#define __DRV_PMU_SET_LDO_CDC_SEL(__LDO_CDC_SEL__)   MODIFY_REG(PMU->LDO_ANA, PMU_LDO_CDC_SEL_MSK, __LDO_CDC_SEL__ << PMU_LDO_CDC_SEL_POS)
#define __DRV_PMU_SET_LDO_CDC_TRIM(__LDO_CDC_TRIM__) MODIFY_REG(PMU->LDO_ANA, PMU_LDO_CDC_TRIM_MSK, __LDO_CDC_TRIM__ << PMU_LDO_CDC_TRIM_POS)

/********************************** BUCK DIG **********************************/
#define __DRV_PMU_SET_BUCK_DIG_SEL(__BUCK_DIG_SEL__)   MODIFY_REG(PMU->BUCK_DIG, PMU_BUCK_DIG_SEL_MSK, __BUCK_DIG_SEL__ << PMU_BUCK_DIG_SEL_POS)
#define __DRV_PMU_SET_BUCK_DIG_TRIM(__BUCK_DIG_TRIM__) MODIFY_REG(PMU->BUCK_DIG, PMU_BUCK_DIG_TRIM_MSK, __BUCK_DIG_TRIM__ << PMU_BUCK_DIG_TRIM_POS)

#define __DRV_PMU_SET_BUCK_ANA_SEL(__BUCK_ANA_SEL__)  MODIFY_REG(PMU->BUCK_ANA, PMU_BUCK_ANA_SEL_MSK, __BUCK_ANA_SEL__ << PMU_BUCK_ANA_SEL_POS)
#define __DRV_PM_SET_BUCK_ANA_TRIM(__BUCK_ANA_TRIM__) MODIFY_REG(PMU->BUCK_ANA, PMU_BUCK_ANA_TRIM_MSK, __BUCK_ANA_TRIM__ << PMU_BUCK_ANA_TRIM_POS)

/************************************POWER_CFG0***************************************/
#define __DRV_PMU_POWER_CFG0_SET_LDO_DIG(__LDO_DIG__) MODIFY_REG(PMU->POWER_CFG0, PMU_TPUP_LDO_DIG_MSK, __LDO_DIG__ << PMU_TPUP_LDO_DIG_POS)
#ifdef __cplusplus
}
#endif

#endif

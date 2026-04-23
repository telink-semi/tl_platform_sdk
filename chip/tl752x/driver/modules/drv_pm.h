/*******************************************************************************************************
 *
 * @file    drv_pm.h
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
#ifndef __DRV_PM_H__
#define __DRV_PM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"
#include "modules/pmu.h"
#include "modules/cpr.h"
typedef enum {
    SLEEP_MODE_DEEP,
    SLEEP_MODE_LDO_RETENTION,
    SLEEP_MODE_RETENTION,
    SLEEP_MODE_SUSPEND,
    SLEEP_MODE_WFI,

} sleep_mode_t;

enum {
    SLEEP_WAKEUP_SRC_RTC,
    SLEEP_WAKEUP_SRC_GPIO,
    SLEEP_WAKEUP_SRC_SYSTIMER,
    SLEEP_WAKEUP_SRC_IPCM,
    SLEEP_WAKEUP_SRC_BT,
};

typedef struct {
    sleep_mode_t mode;

} drv_pm_cpu0_handle_t;

typedef struct {
    sleep_mode_t mode;

} drv_pm_cpu1_handle_t;

typedef struct __pm_handle {
    sleep_mode_t mode;
    uint8_t ret_ldo_val;
    void (*suspend_cb)(struct __pm_handle *hpm);
    void (*resume_cb)(struct __pm_handle *hpm);
} pm_handle_t;

// SLP WAKEUP source
#define PM_CPU1_WKUP_CPR             PMU_CPR_WAK_EN_MSK
#define PM_CPU1_WKUP_RTC             PMU_RTC_WAK_EN_MSK
#define PM_CPU1_WKUP_AON_GPIO        PMU_AON_GPIO_WAK_EN_MSK
#define PM_CPU1_WKUP_CHARGE_STAT     PMU_CHG_STAT_WAK_EN_MSK
#define PM_CPU1_WKUP_CHARGE_DET      PMU_CHG_DET_WAK_EN_MSK
#define PM_CPU1_WKUP_RW_LP           PMU_RW_LP_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_CPR         PMU_PDMCU_CPR_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_RTC         PMU_PDMCU_RTC_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_GPIO        PMU_PDMCU_GPIO_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_CHARGE_STAT PMU_PDMCU_CHG_STAT_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_CHARGE_DET  PMU_PDMCU_CHG_DET_WAK_EN_MSK
#define PM_CPU0_WKUP_SRC_RW_LP       PMU_PDMCU_RW_LP_WAK_EN_MSK

#define __DRV_PM_GET_WKUP_GPIOB_STATUS() READ_REG(PMU->PB_WKUP_IRQ)

#define __DRV_PM_SET_WKUP_SRC(__WKUP_SRC__) SET_PROTECT_BIT(PMU->SLP_CTRL, __WKUP_SRC__)
#define __DRV_PM_CLR_WKUP_SRC(__WKUP_SRC__) CLEAR_PROTECT_BIT(PMU->SLP_CTRL, __WKUP_SRC__)

#define __DRV_PM_SET_WKUP_GPIOB(__GPIO_PIN__) SET_BIT(PMU->PB_WKUP_CFG0, __GPIO_PIN__)

#define __DRV_PM_SET_WKUP_GPIOB_FALLING(__GPIO_PIN__)                    \
    do {                                                                 \
        SET_BIT(PMU->PB_WKUP_CFG1, __GPIO_PIN__ | (__GPIO_PIN__ << 16)); \
    } while (0)

#define __DRV_PM_SET_WKUP_GPIOB_RISING(__GPIO_PIN__)    \
    do {                                                \
        CLEAR_BIT(PMU->PB_WKUP_CFG1, __GPIO_PIN__);     \
        SET_BIT(PMU->PB_WKUP_CFG1, __GPIO_PIN__ << 16); \
    } while (0)

#define __DRV_PM_CLR_WKUP_GPIOB_STATUS(__GPIO_PIN__) SET_BIT(PMU->PB_WKUP_IRQ, __GPIO_PIN__)

/*************************************************************************/

#define __DRV_PM_SET_WKUP_GPIOA(__GPIO_PIN__) SET_BIT(CPR->PA_WKUP_CFG0, __GPIO_PIN__)

#define __DRV_PM_SET_WKUP_GPIOA_FALLING(__GPIO_PIN__)                    \
    do {                                                                 \
        SET_BIT(CPR->PA_WKUP_CFG1, __GPIO_PIN__);  \
        SET_BIT(CPR->PA_WKUP_CFG2, __GPIO_PIN__);    \
    } while (0)

#define __DRV_PM_SET_WKUP_GPIOA_RISING(__GPIO_PIN__) \
    do {                                             \
        CLEAR_BIT(CPR->PA_WKUP_CFG1, __GPIO_PIN__);  \
        SET_BIT(CPR->PA_WKUP_CFG2, __GPIO_PIN__);    \
    } while (0)

#define __DRV_PM_GET_WKUP_GPIOA_STATUS() READ_REG(CPR->PA_WKUP_IRQ)

#define __DRV_PM_CLR_WKUP_GPIOA_STATUS(__GPIO_PIN__) SET_BIT(CPR->PA_WKUP_IRQ, __GPIO_PIN__)

/*CPU0 cpr wakeup src*/
/*The wake-up source under the CPR wake-up function*/
#define PM_CPU0_CPR_WKUP_SRC_GPIOA    CPR_PDMCU_PA_GPIO_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_IPCM     CPR_PDMCU_IPCM_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER0_0 CPR_PDMCU_TIMER_WAK_EN_0_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER0_1 CPR_PDMCU_TIMER_WAK_EN_1_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER0_2 CPR_PDMCU_TIMER_WAK_EN_2_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER0_3 CPR_PDMCU_TIMER_WAK_EN_3_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER1_0 CPR_PDMCU_TIMER1_WAK_EN_0_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER1_1 CPR_PDMCU_TIMER1_WAK_EN_1_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER1_2 CPR_PDMCU_TIMER1_WAK_EN_2_MSK
#define PM_CPU0_CPR_WKUP_SRC_TIMER1_3 CPR_PDMCU_TIMER1_WAK_EN_3_MSK
#define PM_CPU0_CPR_WKUP_SRC_WDT      CPR_PDMCU_WDT_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_BT       CPR_PDMCU_BT_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_BB       CPR_PDMCU_BB_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_SLE      CPR_PDMCU_SLE_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_SYSTIMER CPR_PDMCU_SYSTIMER_WAK_EN_MSK
#define PM_CPU0_CPR_WKUP_SRC_USB1     CPR_PDMCU_USB1_WAK_EN_MSK

#define PM_CPU0_CPR_WKUP_SRC_SET(__CPR_WKUP_SRC__) SET_PROTECT_BIT(CPR->CPU0_SLP_CTRL, __CPR_WKUP_SRC__)
#define PM_CPU0_CPR_WKUP_SRC_CLR(__CPR_WKUP_SRC__) CLEAR_PROTECT_BIT(CPR->CPU0_SLP_CTRL, __CPR_WKUP_SRC__)

/*CPU1 cpr wakeup src*/
/*The wake-up source under the CPR wake-up function*/
#define PM_CPU1_CPR_WKUP_SRC_GPIOA    CPR_PA_GPIO_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_IPCM     CPR_IPCM_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER0_0 CPR_TIMER_WAK_EN_0_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER0_1 CPR_TIMER_WAK_EN_1_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER0_2 CPR_TIMER_WAK_EN_2_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER0_3 CPR_TIMER_WAK_EN_3_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER1_0 CPR_TIMER1_WAK_EN_0_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER1_1 CPR_TIMER1_WAK_EN_1_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER1_2 CPR_TIMER1_WAK_EN_2_MSK
#define PM_CPU1_CPR_WKUP_SRC_TIMER1_3 CPR_TIMER1_WAK_EN_3_MSK
#define PM_CPU1_CPR_WKUP_SRC_WDT      CPR_WDT_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_BT       CPR_BT_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_BB       CPR_BB_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_TAHDT      CPR_TAHDT_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_SYSTIMER CPR_SYSTIMER_WAK_EN_MSK
#define PM_CPU1_CPR_WKUP_SRC_USB1     CPR_USB1_WAK_EN_MSK

#define PM_CPU1_CPR_WKUP_SRC_SET(__CPR_WKUP_SRC__) SET_PROTECT_BIT(CPR->CPU1_SLP_CTRL, __CPR_WKUP_SRC__)
#define PM_CPU1_CPR_WKUP_SRC_CLR(__CPR_WKUP_SRC__) CLEAR_PROTECT_BIT(CPR->CPU1_SLP_CTRL, __CPR_WKUP_SRC__)

_attribute_retention_ram_code_sec_noinline_ void drv_pm_cpu0_enter_wfi_mode(void);

#if defined(MCU_CORE_TL752X_D25F)
extern void drv_pm_cpu0_init(void);
extern uint32_t drv_pm_cpu0_enter(pm_handle_t *handle);

#endif
#if defined(MCU_CORE_TL752X_N22)
extern uint32_t drv_pm_cpu1_enter(pm_handle_t *handle);
#endif

#ifdef __cplusplus
}
#endif

#endif

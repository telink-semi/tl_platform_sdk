/********************************************************************************************************
 * @file    hal_pm.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#ifndef _HAL_PM_H_
#define _HAL_PM_H_

#include "bit.h"
#include "compiler.h"

#include "hal/hal_flash.h"
#include "hal/hal_gpio.h"
#include "hal/hal_sys.h"
#include "hal/hal_systimer.h"
#include "hal/hal_rtc.h"

#include "modules/drv_pm.h"
#include "modules/drv_gpio.h"

#include "inc/drv_pmu.h"
#include "inc/drv_cpr.h"
#include "inc/drv_efuse.h"
#include "inc/drv_systimer.h"
#include "inc/drv_rtc.h"

/**
 * @brief   deep sleep wake up status
 */
typedef struct
{
    unsigned char   is_pad_wakeup;
    unsigned char   mcu_status;
    unsigned short  wakeup_src;
} pm_status_info_s;

/**
 * @brief   mcu status
 */
typedef enum
{
    MCU_POWER_ON                = SYS_RESET_SRC_BOR,
    MCU_RPD_RESET_BACK          = SYS_RESET_SRC_RPD,
    MCU_D25F_WDT_RESET_BACK     = SYS_RESET_SRC_D25_WDT,
    MCU_N22_WDT_RESET_BACK      = SYS_RESET_SRC_N22_WDT,
    MCU_SW_RESET_BACK           = SYS_RESET_SRC_SOFT,

    MCU_DEEP_BACK               = BIT(4),
} pm_mcu_status;


typedef enum
{
    SUSPEND_MODE        = 0x2,
    DEEPSLEEP_MODE      = 0x0,
    N22_CWFI_MODE       = 0x20,

/* don't release at 20260415 */
#if 0
    RET_MODE            = 0x1,
    D25F_SWFI_MODE      = 0x10,
#endif
} pm_sleep_mode_e;

typedef enum
{
    PM_N22_WAKEUP_CPR            = BIT(0),
    PM_N22_WAKEUP_RTC            = BIT(1),
    PM_N22_WAKEUP_PAD            = BIT(2),

    PM_D25F_WAKEUP_CPR           = BIT(6 + 0),
    PM_D25F_WAKEUP_RTC           = BIT(6 + 1),
    PM_D25F_WAKEUP_PAD           = BIT(6 + 2),

/* don't release at 20260415 */
#if 0
    PM_N22_WAKEUP_CHARGE_START   = BIT(3),
    PM_N22_WAKEUP_CHARGE_DET     = BIT(4),
    PM_N22_WAKEUP_RW_LP          = BIT(5),

    PM_D25F_WAKEUP_CHARGE_START  = BIT(6 + 3),
    PM_D25F_WAKEUP_CHARGE_DET    = BIT(6 + 4),
    PM_D25F_WAKEUP_RW_LP         = BIT(6 + 5),
#endif
} pm_sleep_wakeup_src_e;

typedef enum
{
    WAKEUP_STATUS_PAD        = PM_N22_WAKEUP_PAD,
    WAKEUP_STATUS_CORE       = PM_N22_WAKEUP_CPR,
    WAKEUP_STATUS_TIMER      = PM_N22_WAKEUP_RTC,

/* don't release at 20260415 */
#if 0
    WAKEUP_STATUS_CHARGE_START = PM_N22_WAKEUP_CHARGE_START,
    WAKEUP_STATUS_CHARGE_DET = PM_N22_WAKEUP_CHARGE_DET,
#endif

    STATUS_GPIO_ERR_NO_ENTER_PM = BIT(16), /**<Bit8 is used to determine whether the wake source is normal.*/
    STATUS_EXCEED_MAX           = BIT(27),
    STATUS_EXCEED_MIN           = BIT(28),
    STATUS_CLEAR_FAIL           = BIT(29),
    STATUS_ENTER_SUSPEND        = BIT(30),
} pm_wakeup_status_e;

typedef enum
{
/* don't release at 20260415 */
#if 0
    PM_TICK_STIMER = 0,     //16M
#endif
    PM_TICK_32K    = 1,
} pm_wakeup_tick_type_e;

typedef enum
{
    PM_EMA_CFG_LOW_FREQ   = 0x0,
    PM_EMA_CFG_HIGH_FREQ  = 0x1,
}pm_ema_cfg_e;

typedef struct
{
    unsigned short suspend;  /**< suspend_early_wakeup_time_us = deep_ret_r_delay_us + xtal_stable_time + early_time*/
    unsigned short deep_ret; /**< deep_ret_early_wakeup_time_us = deep_ret_r_delay_us + early_time*/
    unsigned short deep;     /**< deep_early_wakeup_time_us = suspend_ret_r_delay_us*/
    unsigned short sleep_min_time;             /**< sleep_min_time_us = suspend_early_wakeup_time_us + 200*/
} pm_early_wakeup_time_us_s;

typedef struct
{
    unsigned char       sleep_mode;
    unsigned char       resv0[3];
    unsigned int        wakeup_tick;        /* stimer tick */
} pm_sync_msg_t;

#if defined(MCU_CORE_TL752X_D25F)
extern _attribute_data_retention_sec_ unsigned char g_pm_long_suspend;
extern _attribute_data_retention_sec_ unsigned int  g_pm_tick_32k_calib;
extern _attribute_data_retention_sec_ unsigned int  g_pm_tick_cur;
extern _attribute_data_retention_sec_ unsigned int  g_pm_tick_32k_cur;

extern pm_status_info_s g_pm_status_info;
#endif

#if defined(MCU_CORE_TL752X_N22)

#endif


static _always_inline void pm_set_wakeup_src_n22_cpr(unsigned int src_msk)
{
    PM_CPU1_CPR_WKUP_SRC_SET(src_msk);
}

static _always_inline void pm_set_wakeup_src_d25f_cpr(unsigned int src_msk)
{
    PM_CPU0_CPR_WKUP_SRC_SET(src_msk);
}

static _always_inline void pm_set_wakeup_src(unsigned int src_msk)
{
    __DRV_PM_SET_WKUP_SRC(src_msk);
}

static _always_inline pm_sleep_wakeup_src_e pm_get_wakeup_src(void)
{
    return ((pm_sleep_wakeup_src_e)READ_REG(PMU->SLP_CTRL));
}

/********************************************************************/
void pm_update_status_info(unsigned char clr_en);

void pm_wakeup_gpio_init(gpio_init_t *cfg);

/**
 * @brief       this function serves to config SRAM ema.
 * @param[in]   ema_cfg - ema config type select.
 * @return      none.
 * @note        user should set it to PM_EMA_CFG_HIGH_FREQ before switch to high_freq,
 *                       or set it to PM_EMA_CFG_LOW_FREQ after switch to low_freq;
 *              SRAM access was prohibited during the execution of this interface.
 */
_attribute_text_sec_ void pm_set_ema(pm_ema_cfg_e ema_cfg);

#if defined(MCU_CORE_TL752X_D25F)
_attribute_text_sec_optimize_o2_ int pm_sleep_wakeup(pm_sleep_mode_e sleep_mode, pm_sleep_wakeup_src_e wakeup_src, pm_wakeup_tick_type_e wakeup_tick_type, unsigned int wakeup_tick);
#endif

#if defined(MCU_CORE_TL752X_N22)
int pm_sleep_wakeup_n22(pm_sleep_mode_e sleep_mode);
#endif

#endif

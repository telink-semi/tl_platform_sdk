/********************************************************************************************************
 * @file    hal_sys.h
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


/** @page SYS
 *
 *  Introduction
 *  ===============
 *  Clock init and system timer delay.
 *
 *  API Reference
 *  ===============
 *  Header File: hal_sys.h
 */

#ifndef HAL_SYS_H_
#define HAL_SYS_H_

#include "inc/drv_cpr.h"
#include "inc/drv_pmu.h"
#include "compiler.h"

typedef enum
{
    SYS_RESET_SRC_BOR        =   0,
    SYS_RESET_SRC_RPD        =   1,
    SYS_RESET_SRC_D25_WDT    =   2,
    SYS_RESET_SRC_N22_WDT    =   3,
    SYS_RESET_SRC_SOFT       =   4,   // not 5, confirmed by kang@weina
}sys_reset_src_e;

typedef enum
{
    EPM9062_A0        =   0,
    EPM9062_A1        =   1,
}chip_version_e;

static _always_inline sys_reset_src_e sys_roftrst_src_get(void)
{
    return (CPR->RST_CTRL & CPR_RESET_SRC);
}
static _always_inline void sys_roftrst(void)
{
    SET_BIT(CPR->RST_CTRL, CPR_RSTN_SOFT);
}

/**
 * @brief       This function serves to initialize dsp core system.
 * @return      none
 * @note        1.Only after calling this function can other DSP related functions be called.
 *              Otherwise, other DSP function settings will not take effect.
 *              2.dsp and cclk is a binding relationship, cclk is how much, dsp is how much,
 *              dsp does not have a corresponding clk configuration interface.
 */
void sys_dsp_init(unsigned int addr);

/**
 * @brief       This function serves to start dsp core system.
 * @return      none
 */
void sys_dsp_start(void);

/**
* @brief       This function serves to stall dsp by dis dsp clock.
* @return      none
*/
void sys_dsp_clk_dis(void);

/**
* @brief       This function serves to start dsp.
* @return      none
*/
void sys_dsp_clk_en(void);


/**
 * @brief      This function serves to initialize n22 core system.
 * @param[in]  addr - start up address
 * @return     none
 * @note        Only after calling this function can other N22 related functions be called. 
 *              Otherwise, other N22 function settings will not take effect.
 */
void sys_n22_init(unsigned int addr);

/**
 * @brief       This function serves to start n22 core system.
 * @return      none
 */
void sys_n22_start(void);

/**
 * @brief      This function reboot mcu.
 * @return     none
 */
_attribute_ram_code_sec_ void sys_reboot(void);

chip_version_e sys_get_chip_ver(void);

void sys_init(void);
#endif

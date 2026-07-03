/********************************************************************************************************
 * @file    hal_charger.h
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
#ifndef _HAL_CHARGER_H_
#define _HAL_CHARGER_H_
#include "inc/drv_pmu.h"

typedef enum
{
    CC_5mA  = 0,
    CC_10mA  = 0x19,
    CC_15mA,
    CC_20mA,
    CC_25mA,
    CC_30mA,
    CC_35mA,
    CC_40mA,
    CC_45mA,
    CC_50mA,
    CC_55mA,
    CC_60mA,
    CC_65mA,
    CC_70mA,
    CC_75mA,
    CC_80mA,
    CC_85mA,
    CC_90mA,
    CC_95mA,
    CC_100mA,//default
    CC_105mA,
    CC_110mA,
    CC_115mA,
    CC_120mA,
    CC_125mA,
    CC_130mA,
    CC_135mA,
    CC_140mA,
    CC_145mA,
    CC_150mA,
    CC_155mA,
    CC_160mA,
    CC_165mA,
    CC_170mA,
    CC_175mA,
    CC_180mA,
    CC_185mA,
    CC_190mA,
    CC_195mA,
    CC_200mA,
    CC_MIN = CC_5mA,
    CC_MAX = CC_200mA,
} charger_cc_cur_e;

typedef enum
{
    CV_4P2V  = 0,//default
    CV_4P3V,
    CV_4P4V,
    CV_4P5V,
    CV_3P8V,
    CV_3P9V,
    CV_4P0V,
    CV_4P1V,

} charger_cv_vol_e;

/**
 * @brief       Set the charger constant current (CC) level with offset compensation.
 *
 * @param[in]   cc_cur  - target constant current level, see @ref charger_cc_cur_e.
 * @return      none
 * @note        The actual register value is computed as: target value + offset from the
 *              pre-configured lookup table (based on RS trim). The result is clamped to
 *              the valid range [CC_MIN, CC_MAX].
 */
void charger_set_cc(charger_cc_cur_e cc_cur);

/**
 * @brief       Set the charger voltage (CV) level.
 *
 * @param[in]   cv_vol  - target voltage level, see @ref charger_cv_vol_e.
 * @return      none
 */
void charger_set_cv(charger_cv_vol_e cv_vol);

/**
 * @brief       Enable the charger.
 *
 * @param[in]   none
 * @return      none
 */
void charger_enable(void);

/**
 * @brief       Disable the charger.
 *
 * @param[in]   none
 * @return      none
 */
void charger_disable(void);

/**
 * @brief       Trim the charger VREF value.
 *
 * @param[in]   trim_val  - trim value for the VREF control bits.
 * @return      none
 */
void charger_vref_trim(unsigned short trim_val);

/**
 * @brief       Trim the charger RS (current-sense resistor) value.
 *
 * @param[in]   trim_val  - trim value for the RS control bits.
 * @return      none
 */
void charger_rs_trim(unsigned short trim_val);

/**
 * @brief       Write both VREF and RS trim values and update the CC level offset index.
 *
 * @param[in]   vref  - 4-bit trim value for VREF.
 *              rs    - 8-bit value where bits [6:4] encode the 3-bit CC offset index,
 *                      and bits [3:0] are the 4-bit RS trim value.
 * @return      none
 * @note        The upper nibble of `rs` (bits [6:4]) selects the CC level offset from the
 *              lookup table. The selected offset will be applied in subsequent calls to
 *              charger_set_cc().
 */
void charger_vref_rs_trim(unsigned char vref, unsigned char rs);
#endif

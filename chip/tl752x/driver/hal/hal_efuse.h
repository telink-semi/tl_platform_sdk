/********************************************************************************************************
 * @file    hal_efuse.h
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


#ifndef DRIVER_HAL_HAL_EFUSE_H_
#define DRIVER_HAL_HAL_EFUSE_H_
#ifdef __cplusplus
extern "C" {
#endif
typedef enum
{
    DRV_API_SUCCESS       = 0x00,
    DRV_API_FAILURE       = 0x01,
    DRV_API_TIMEOUT       = 0x02,
    DRV_API_INVALID_PARAM = 0x03
} drv_api_status_e;


typedef struct
{
    signed short  cp_gpio_offset;
    unsigned short cp_gpio_gain;
    signed short  cp_vbat_offset;
    unsigned short cp_vbat_gain;
    signed short  ft_gpio_offset;
    unsigned short ft_gpio_gain;
    signed short  ft_vbat_offset;
    unsigned short ft_vbat_gain;
} adc_ft_cp_calib_t;

/**
 * @note This rs variable (cp_rs or ft_rs) has bit 0-3 representing the rs trim value, 
 *       and bits 4-6 representing the offset value of chg_cc_sel.
 */
typedef struct
{
    unsigned char cp_vref;
    unsigned char cp_rs;
    unsigned char ft_vref;
    unsigned char ft_rs;
} charger_trim_t;

/**
 * @brief       This function is used to get ieee addr.
 *
 * @param[in]   buf - ieee addr data buffer.
 * @return      DRV_API_SUCCESS: get success;
 *              others: get fail.
 */
drv_api_status_e efuse_get_ieee_addr(unsigned char *buf);

/**
 * @brief       This function is used to Tighten the judgment of illegal values for gpio calibration and vbat calibration in the efuse.
 *
 * @param[in]   gain - the value of gpio_calib_vref_gain or vbat_calib_vref_gain
 *              offset - the value of gpio_calib_vref_offset or vbat_calib_vref_offset
 *              calib_func - Function pointer to gpio_calibration or vbat_calibration.
 * @return      DRV_API_FAILURE:the calibration function is invalid;
 *              DRV_API_SUCCESS:the calibration function is valid.
 */
drv_api_status_e efuse_set_adc_calib_value(unsigned short gain, signed short offset, int (*calib_func)(unsigned short, signed short));
/**
 * @brief      This function servers to get calibration value from EFUSE.
 * @param[in]  none
 * @return     1 - the calibration value update, 0 - the calibration value is not update.
 */
drv_api_status_e efuse_calib_adc_vref(void);

/**
 * @brief      This function servers to config the charger trim value from EFUSE.
 * @param[in]  none
 * @return     DRV_API_SUCCESS - the calibration value config success,
 *             DRV_API_FAILURE - the calibration value config fail.
 */
drv_api_status_e efuse_calib_charger_vref_rs(void);

#ifdef __cplusplus
}
#endif
#endif /* DRIVER_HAL_HAL_EFUSE_H_ */

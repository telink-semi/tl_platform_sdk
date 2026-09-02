/********************************************************************************************************
 * @file    calibration.c
 *
 * @brief   This is the source file for tl521x
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "calibration.h"

extern drv_api_status_e efuse_calib_sd_adc_vref(unsigned char calib_single_gpio_flag, unsigned char calib_vbat_flag, unsigned char calib_diff_gpio_flag);

/**
 * @brief      This function serves to set the calibration value of the the adc vref with valid range.
 * @param[in]  gain       - the gain value (valid range: [8000, 12000]).
 * @param[in]  offset     - the offset value (valid range: [-1000, 1000]).
 * @param[in]  calib_func - the calibration function to be called if values are valid.
 * @return     0 - calibration value set successfully, -1 - calibration value is invalid.
 */
int user_set_sd_adc_calib_value(unsigned short gain, signed short offset, void (*calib_func)(unsigned short, signed short))
{
    /**
     * The legal range of gain for both gpio and vbat in efuse is [8000,12000],
     * and the legal range of offset for both gpio and vbat is [-1000,1000].
     */
    if ((gain >= 8000) && (gain <= 12000) && (offset >= -1000) && (offset <= 1000)) {
        (*calib_func)(gain, offset);
        return 0;
    }
    return -1;
}

/**
 * @brief      This function serves to calibrate the sd adc vref from flash or efuse.
 *             If flash address is 0, calibrate all groups from efuse directly.
 *             Otherwise, read calibration values from flash first; for any group
 *             whose flash values are invalid, fall back to efuse values.
 * @param[in]  flash_addr - flash address of calibration values, or 0 to use efuse only.
 * @return     none.
 */
void user_calib_adc_vref(unsigned int flash_addr)
{
    /* 3 groups to calibrate: single-gpio / vbat / diff-gpio. */
    unsigned char need_efuse_single_gpio = 0;
    unsigned char need_efuse_vbat        = 0;
    unsigned char need_efuse_diff_gpio   = 0;

    if (flash_addr == 0) {
        /* No valid flash address: calibrate all 3 groups from efuse. */
        efuse_calib_sd_adc_vref(1, 1, 1);
        return;
    }

    /*
     * Flash layout (12 bytes = 3 groups x 4 bytes), each group stores:
     *   [gain: unsigned short][offset: signed short]
     *   [0..3]  single-gpio group
     *   [4..7]  vbat group
     *   [8..11] diff-gpio group
     */
    unsigned char flash_calib[12] = {0};
    flash_read_page(flash_addr, sizeof(flash_calib), flash_calib);

    /*
     * Apply each group's flash value only when it is within the legal range
     * (user_set_sd_adc_calib_value returns 0). Otherwise mark that group so
     * it can be recovered from efuse later.
     */
    if (user_set_sd_adc_calib_value(*(unsigned short *)(flash_calib + 0), *(signed short *)(flash_calib + 2), sd_adc_set_single_gpio_calib_vref) != 0) {
        need_efuse_single_gpio = 1;
    }
    if (user_set_sd_adc_calib_value(*(unsigned short *)(flash_calib + 4), *(signed short *)(flash_calib + 6), sd_adc_set_vbat_calib_vref) != 0) {
        need_efuse_vbat = 1;
    }
    if (user_set_sd_adc_calib_value(*(unsigned short *)(flash_calib + 8), *(signed short *)(flash_calib + 10), sd_adc_set_diff_gpio_calib_vref) != 0) {
        need_efuse_diff_gpio = 1;
    }

    /* Only fall back to efuse for the groups whose flash values were invalid. */
    if (need_efuse_single_gpio || need_efuse_vbat || need_efuse_diff_gpio) {
        efuse_calib_sd_adc_vref(need_efuse_single_gpio, need_efuse_vbat, need_efuse_diff_gpio);
    }
}

/**
 * @brief      This function serves to update rf frequency offset.
 * @param[in]  addr - the frequency offset value address of flash.
 * @return     1 - the frequency offset update, 0 - the frequency offset is not update.
 */
unsigned char user_calib_freq_offset(unsigned int addr)
{
    unsigned char frequency_offset_value = 0xff;

    flash_read_page(addr, 1, &frequency_offset_value);

    if (0xff != frequency_offset_value) {
        rf_update_internal_cap(frequency_offset_value);
        return 1;
    }

    return 0;
}

/**
 * @brief       This function is used to calibrate the user's parameters.
 *              This function is to read the calibration value stored in otp and flash,
 *              and use the calibration value to configure the chip to improve chip performance.
 *              (reduce adc measurement error, reduce frequency offset, etc.)
 * @return      none.
 */
void calibration_func(void)
{
    unsigned char flash_mid[4];
    unsigned char flash_uid[16];
    unsigned char flash_mid_sure = 0;
    unsigned int  ieee_flash_pos = 0, cap_value_addr = 0;
    unsigned char ieee_addr[8];
    unsigned int adc_value_addr = 0;
    /******check for flash mid********/
    flash_mid_sure = flash_read_mid_uid_with_check((unsigned int *)flash_mid, flash_uid);


    if (1 == flash_mid_sure) {
        switch (flash_mid[2]) {
        case FLASH_SIZE_64K:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_64K;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_64K;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_64K;
            break;
        case FLASH_SIZE_128K:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_128K;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_128K;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_128K;
            break;
        case FLASH_SIZE_512K:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_512K;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_512K;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_512K;
            break;
        case FLASH_SIZE_1M:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_1M;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_1M;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_1M;
            break;
        case FLASH_SIZE_2M:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_2M;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_2M;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_2M;
            break;
        case FLASH_SIZE_4M:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_4M;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_4M;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_4M;
            break;
        case FLASH_SIZE_16M:
            cap_value_addr = FLASH_CAP_VALUE_ADDR_16M;
            ieee_flash_pos = FLASH_IEEE_ADDR_LOCATION_16M;
            adc_value_addr = FLASH_ADC_CALI_VALUE_ADDR_16M;
            break;
        default:
            break;
        }
        if (cap_value_addr) {
            user_calib_freq_offset(cap_value_addr);
        }
        if (ieee_flash_pos) {
            user_get_ieee_addr(ieee_flash_pos, ieee_addr);
        }
    } else {
        user_get_ieee_addr(0, ieee_addr);
    }
    /*adc calibration*/
    user_calib_adc_vref(adc_value_addr);
}

/**
 * @brief      This function serves to check if IEEE address is legal.
 * @param[in]  value  - Pointer to value address buffer
 * @return     0: value address is illegal, 1:value address is legal
 */
unsigned char user_check_ieee_addr(unsigned char *value)
{
    //IEEE address is legal if it is not all 0x00 or all 0xFF.
    for (int i = 1; i < 8; i++) {
        if (value[i] != value[0]) {
            return 1;
        }
    }
    //If all elements are the same, check if it is all 0x00 or all 0xFF
    return (value[0] == 0x00 || value[0] == 0xFF) ? 0 : 1;
}

/**
 * @brief      This function serves to read IEEE address from OTP.
 * @param[out] buf  - Pointer to IEEE address buffer(IEEE address is 8bytes)
 * @return     ieee_addr_source_e
 */
ieee_addr_source_e user_get_otp_ieee_addr(unsigned char *buf)
{
    //Read IEEE address priority: FLASH > OTP
    //otp_get_ieee_addr(buf);
    if (user_check_ieee_addr(buf)) {
        return IEEE_ADDR_FROM_OTP;
    } else {
        return IEEE_ADDR_NOT_EXIST;
    }
}

/**
 * @brief      This function serves to read IEEE address from FLASH or OTP.
 * @param[in]  addr - the IEEE address of flash
 *                    0:     Read the IEEE address from OTP.
 *                    other: first read the IEEE address from the flash memory.
 *                           If it is not a valid value, then read it from OTP.
 * @param[out] buf  - Pointer to IEEE address buffer(IEEE address is 8bytes)
 * @return     ieee_addr_source_e
 */
ieee_addr_source_e user_get_ieee_addr(unsigned int addr, unsigned char *buf)
{
    if (addr == 0) {
        return user_get_otp_ieee_addr(buf);
    } else {
        //Read IEEE address priority: FLASH > OTP
        flash_read_page(addr, 8, buf);
        if (user_check_ieee_addr(buf)) {
            return IEEE_ADDR_FROM_FLASH;
        } else {
            return user_get_otp_ieee_addr(buf);
        }
    }
}

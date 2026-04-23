/********************************************************************************************************
 * @file    hal_adc.h
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

#ifndef DRIVER_HAL_HAL_ADC_H_
#define DRIVER_HAL_HAL_ADC_H_
#include <stdint.h>
#include "driver.h"

#define ADC_GPIO_GAIN_MIN_LIMIT   2000
#define ADC_GPIO_GAIN_MAX_LIMIT   5000
#define ADC_GPIO_OFFSET_MIN_LIMIT 100
#define ADC_GPIO_OFFSET_MAX_LIMIT 1500

#define ADC_VBAT_GAIN_MIN_LIMIT   8000
#define ADC_VBAT_GAIN_MAX_LIMIT   18000
#define ADC_VBAT_OFFSET_MIN_LIMIT 2000
#define ADC_VBAT_OFFSET_MAX_LIMIT 4000

typedef struct
{
    uint8_t ipclk_div;
    uint8_t mclk_div;
    gpadc_channel_t chn;    /* GPIO pin */
    //uint8_t resdiv;         /* half of the voltage divider enable flag 1: enable 0 : disable */
} adc_cfg_t;

/**
 * @brief This function is used to init adc module.
 * @param[in] cfg - the adc cfg.
 * @return none
 */
int adc_init(adc_cfg_t cfg);

/**
 * @brief ADC module deinit, clear the global s_adc_cfg variable.
 * @param[in] cfg - adc configure .
 * @return none
 */
void adc_deinit(adc_cfg_t cfg);

/**
 * @brief      This function enable ADC source clock
 * @return     none
 */
void adc_clk_en(void);

/**
 * @brief      This function disable ADC clock.
 * @return     none
 */
void adc_clk_dis(void);

/**
 * @brief  ADC fifo flush
 * @note   none
 */
void adc_fifo_flush(void);

/**
 * @brief  ADC receive or Transmit an amount of data with poll mode.
 *
 * @param  buf: data buffer
 * @param  len: data length
 * @param  timeout: time-out period
 * @return none
 * @note   none
 */
void adc_sample_start(uint32_t *buf, uint32_t len, uint32_t timeout);

/**
 * @brief  gpadc stop
 * @note   none
 */
void adc_sample_stop(void);

/**
 * @brief This function is used to calib ADC 1.8V vref for GPIO.
 * @param[in] vref - GPIO sampling calibration value.
 * @param[in] offset - GPIO sampling two-point calibration value offset.
 * @return none
 */
int adc_set_gpio_calib_vref(unsigned short vref, signed short offset);

/**
 * @brief This function is used to calib ADC 1.8V vref for Vbat.
 * @param[in] vref - Vbat channel sampling calibration value.
 * @param[in] offset - Vbat channel sampling two-point calibration value offset.
 * @return none
 */
int adc_set_vbat_calib_vref(unsigned short vref, signed short offset);

/**
 * @brief This function serves to calculate voltage from adc sample code.
 * @param[in]   adc_code    - the adc sample code(should be positive value.)
 * @return      adc_voltage  - the average value of adc voltage value(adc voltage value >= 0).
 */
unsigned short adc_calculate_voltage(uint32_t adc_code);
#endif /* DRIVER_HAL_HAL_ADC_H_ */

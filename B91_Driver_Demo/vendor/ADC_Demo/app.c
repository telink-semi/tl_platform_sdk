/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91
 *
 * @author	Driver Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#include "app_config.h"

#define  ADC_DMA_CHN		DMA7
#define  ADC_SAMPLE_PIN		ADC_GPIO_PD1
#define  ADC_SAMPLE_NUM		8

volatile unsigned short adc_temp_val;
volatile unsigned short adc_vol_mv_val;
volatile unsigned short adc_code_val;
volatile unsigned short adc_sample_buffer[ADC_SAMPLE_NUM] __attribute__((aligned(4))) = {0};


unsigned short adc_sort_and_get_average_code(void);
unsigned short adc_get_voltage_dma(void);
unsigned short adc_get_temperature_dma(void);
unsigned short adc_get_voltage(void);
unsigned short adc_get_temperature(void);

void user_init()
{
	gpio_function_en(LED1);
	gpio_output_en(LED1);
#if (ADC_MODE == ADC_DMA_MODE)
	adc_set_dma_config(ADC_DMA_CHN);
#endif

#if (ADC_SAMPLE_MODE == ADC_GPIO_SAMPLE)
	adc_gpio_sample_init(ADC_SAMPLE_PIN, ADC_VREF_1P2V, ADC_PRESCALE_1F8, ADC_SAMPLE_FREQ_96K);
#elif(ADC_SAMPLE_MODE == ADC_VBAT_SAMPLE)
	/**		The battery voltage sample range is 1.8~3.5V,
	 * 		and must set sys_init() function  with the mode for battery voltage less than 3.6V.
	 * 		For battery voltage > 3.6V, should take some external voltage divider.
	 **/
	adc_battery_voltage_sample_init();
#elif(ADC_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
	adc_temperature_sample_init();
#endif
	adc_power_on();
}

void main_loop (void)
{
#if (ADC_MODE == ADC_DMA_MODE)
#if (ADC_SAMPLE_MODE != ADC_TEMP_SENSOR_SAMPLE)
	adc_vol_mv_val = adc_get_voltage_dma();
#else
	adc_temp_val = adc_get_temperature_dma();
#endif
#elif(ADC_MODE == ADC_NDMA_MODE)
#if (ADC_SAMPLE_MODE != ADC_TEMP_SENSOR_SAMPLE)
	adc_vol_mv_val = adc_get_voltage();
#else
	adc_temp_val = adc_get_temperature();
#endif
#endif
	delay_ms(1000);
	gpio_toggle(LED1);
}
/**
 * @brief This function serves to sort adc sample code and get average value.
 * @return 		adc_code_average 	- the average value of adc sample code.
 */
unsigned short adc_sort_and_get_average_code(void)
{

	unsigned short adc_code_average = 0;
	unsigned int i, j;
	unsigned short temp;
	/**** insert Sort and get average value ******/
	for(i = 1 ;i < ADC_SAMPLE_NUM; i++)
	{
		if(adc_sample_buffer[i] < adc_sample_buffer[i-1])
		{
			temp = adc_sample_buffer[i];
			adc_sample_buffer[i] = adc_sample_buffer[i-1];
			for(j=i-1; adc_sample_buffer[j] > temp;j--)
			{
				adc_sample_buffer[j+1] = adc_sample_buffer[j];
			}
			adc_sample_buffer[j+1] = temp;
		}
	}

	//get average value from raw data(abandon 1/4 small and 1/4 big data)
	for (i = ADC_SAMPLE_NUM>>2; i < (ADC_SAMPLE_NUM - (ADC_SAMPLE_NUM>>2)); i++)
	{
		adc_code_average += adc_sample_buffer[i]/(ADC_SAMPLE_NUM>>1);
	}
	return adc_code_average;
}
/**
 * @brief This function serves to get adc sample code by dma and convert to voltage value.
 * @return 		adc_vol_mv_average 	- the average value of adc voltage value.
 */
unsigned short adc_get_voltage_dma(void)
{
	unsigned short adc_vol_mv_average = 0;
	unsigned short adc_code_average = 0;

	adc_get_code_dma((unsigned short *)adc_sample_buffer, ADC_SAMPLE_NUM);
	adc_code_average = adc_sort_and_get_average_code();
	adc_vol_mv_average = adc_calculate_voltage(adc_code_average);
	return adc_vol_mv_average;
}

/**
 * @brief This function serves to get adc sample code by manual and convert to voltage value.
 * @return 		adc_vol_mv_average 	- the average value of adc voltage value.
 */
unsigned short adc_get_voltage(void)
{
	unsigned short adc_vol_mv_average = 0;
	unsigned short adc_code_average = 0;
	for (int i = 0; i < ADC_SAMPLE_NUM; i++)
	{
		adc_sample_buffer[i] = adc_get_code();
		//wait at least 2 sample cycle(f = 96K, T = 10.4us)
		delay_us(21);
	}
	adc_code_average = adc_sort_and_get_average_code();
	adc_vol_mv_average = adc_calculate_voltage(adc_code_average);
	return adc_vol_mv_average;
}
/**
 * @brief This function serves to get temperature sensor adc sample code by dma and temperature value.
 * @return 		adc_temp_average 	- the average value of temperature value.
 */
unsigned short adc_get_temperature_dma(void)
{
	unsigned short adc_temp_average = 0;
	unsigned short adc_code_average = 0;

	adc_get_code_dma((unsigned short *)adc_sample_buffer, ADC_SAMPLE_NUM);
	adc_code_average = adc_sort_and_get_average_code();
	adc_temp_average = adc_calculate_temperature(adc_code_average);
	return adc_temp_average;
}

/**
 * @brief This function serves to get adc sample code by manual and convert to temperature value.
 * @return 		adc_temp_average 	- the average value of temperature value.
 */
unsigned short adc_get_temperature(void)
{
	unsigned short adc_temp_average = 0;
	unsigned short adc_code_average = 0;

	for (int i = 0; i < ADC_SAMPLE_NUM; i++)
	{
		adc_sample_buffer[i] = adc_get_code();
		//wait at least 2 sample cycle(f = 96K, T = 10.4us)
		delay_us(21);
	}
	adc_code_average = adc_sort_and_get_average_code();
	adc_temp_average = adc_calculate_temperature(adc_code_average);
	return adc_temp_average;
}





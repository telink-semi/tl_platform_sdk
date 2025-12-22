/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "common.h"

sd_adc_gpio_cfg_t sd_adc_gpio_cfg =
{
    .clk_freq           = SD_ADC_SAPMPLE_CLK_2M,
    .downsample_rate    = SD_ADC_DOWNSAMPLE_RATE_128,
    .gpio_div           = SD_ADC_GPIO_CHN_DIV_1F4,
    .input_p            = SD_ADC_GPIO_PB6P,
    .input_n            = SD_ADC_GNDN,
};

volatile unsigned int sd_adc_irq_cnt=0;
signed int sd_adc_vol_10x = 0;
volatile signed int sd_adc_vol = 0;
volatile signed int temp_value = 0;
volatile unsigned int sd_adc_rx_done_flag=0;
volatile unsigned char vbat_low_vol_detect = 0;


/*
 *  The length of sd_adc_sample_buffer must be >= SD_ADC_FIFO_DEPTH, otherwise there is a risk of array overflow.
 */
signed int sd_adc_sample_buffer[SD_ADC_SAMPLE_CNT] __attribute__((aligned(4))) = {0};
signed int sd_adc_sort_and_get_average_code(signed int *sample_buffer);
signed int sd_adc_get_result(sd_adc_result_type_e result_type);
void user_init(void)
{

    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);

    sd_adc_init(SD_ADC_SINGLE_DC_MODE);

#if(SD_ADC_MODE==SD_ADC_GPIO_MODE )
    sd_adc_gpio_sample_init(&sd_adc_gpio_cfg);
#elif(SD_ADC_MODE==SD_ADC_VBAT_MODE )
    sd_adc_vbat_sample_init(SD_ADC_SAPMPLE_CLK_2M, SD_ADC_VBAT_DIV_1F4, SD_ADC_DOWNSAMPLE_RATE_128);
#elif(SD_ADC_MODE==SD_ADC_TEMP_MODE)
    sd_adc_temp_init(SD_ADC_SAPMPLE_CLK_2M, SD_ADC_DOWNSAMPLE_RATE_128);
#endif


#if(SAMPLE_MODE == DMA_INTERRUPT_MODE)
    sd_adc_set_dma_config(SD_ADC_DMA_CHN);
    dma_set_irq_mask(SD_ADC_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    sd_adc_start_sample_dma((signed int *)sd_adc_sample_buffer, SD_ADC_SAMPLE_CNT<<2);
#endif

    sd_adc_power_on(SD_ADC_SAMPLE_MODE);
#if defined(MCU_CORE_TL323X)
    delay_us(200);//must delay 200us for the ADC to stabilize
#endif
    sd_adc_sample_start();
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop(void)
{
#if(SAMPLE_MODE == NDMA_POLLING_MODE)
#if(SD_ADC_MODE==SD_ADC_GPIO_MODE || SD_ADC_MODE==SD_ADC_VBAT_MODE)
    sd_adc_vol_10x = sd_adc_get_result(SD_ADC_VOLTAGE_10X_MV);
    sd_adc_vol = sd_adc_vol_10x / 10;
    printf("vol = %d.%d mv \n",(sd_adc_vol_10x / 10),((unsigned int)sd_adc_vol_10x % 10));
#elif(SD_ADC_MODE==SD_ADC_TEMP_MODE )
        temp_value = sd_adc_get_result(TEMP_VALUE);
        printf("temp = %d \n",temp_value);
#endif
#elif(SAMPLE_MODE == DMA_INTERRUPT_MODE)

    if(sd_adc_rx_done_flag == 1)
    {
#if(SD_ADC_MODE==SD_ADC_GPIO_MODE || SD_ADC_MODE==SD_ADC_VBAT_MODE)
        sd_adc_vol_10x = sd_adc_get_result(SD_ADC_VOLTAGE_10X_MV);
        sd_adc_vol = sd_adc_vol_10x / 10;
        printf("vol = %d.%d mv\n",(sd_adc_vol_10x / 10),((unsigned int)sd_adc_vol_10x % 10));
#elif(SD_ADC_MODE==SD_ADC_TEMP_MODE)
        temp_value = sd_adc_get_result(TEMP_VALUE);
        printf("temp = %d \n",temp_value);
#endif
        sd_adc_rx_done_flag = 0;
#if(SAMPLE_MODE == DMA_INTERRUPT_MODE)
        sd_adc_start_sample_dma((signed int *)sd_adc_sample_buffer, SD_ADC_SAMPLE_CNT<<2);
#endif
        sd_adc_sample_start();
    }
#endif
}

#if(SAMPLE_MODE == DMA_INTERRUPT_MODE)
_attribute_ram_code_sec_ void dma_irq_handler(void)
{
    if (dma_get_tc_irq_status(BIT(SD_ADC_DMA_CHN))) {
        sd_adc_sample_stop();
        sd_adc_irq_cnt++;
        sd_adc_rx_done_flag = 1;
        sd_adc_clr_irq_status_dma();
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
#endif
/**
 * @brief       This function serves to sort and get average code.
 * @param[in]   sd_adc_data_buf -Pointer to sd_adc_data_buf
 * @return      average code
 * @note        If sd_adc_sort_and_get_average_code() interface is called, SD_ADC_SAMPLE_CNT must be a multiple of 4.
 */
signed int sd_adc_sort_and_get_average_code(signed int *sample_buffer)
{
    int i, j;
    signed int sd_adc_code_average = 0;
    signed int temp;

    /**** insert Sort and get average value ******/
    for(i = 1 ;i < SD_ADC_SAMPLE_CNT; i++)
    {
        if(sample_buffer[i] < sample_buffer[i-1])
        {
            temp = sample_buffer[i];
            sample_buffer[i] = sample_buffer[i-1];
            for(j=i-1; j>=0 && sample_buffer[j] > temp;j--)
            {
                sample_buffer[j+1] = sample_buffer[j];
            }
            sample_buffer[j+1] = temp;
        }
    }
    //get average value from raw data(abandon 1/4 small and 1/4 big data)
    for (i = SD_ADC_SAMPLE_CNT>>2; i < (SD_ADC_SAMPLE_CNT - (SD_ADC_SAMPLE_CNT>>2)); i++)
    {
        sd_adc_code_average += sample_buffer[i]/(SD_ADC_SAMPLE_CNT>>1);
    }
    return sd_adc_code_average;
}

/**
 * @brief       This function serves to get voltage or temperature value.
 * @param[in]   result_type -sd_adc_result_type_e
 * @return      voltage or temperature value
 */
signed int sd_adc_get_result(sd_adc_result_type_e result_type)
{
    signed int code_average;
    signed int sd_adc_result;

#if(SAMPLE_MODE == NDMA_POLLING_MODE)
    int cnt = 0;
    while (cnt < SD_ADC_SAMPLE_CNT) {
        int sample_cnt = sd_adc_get_rxfifo_cnt();
        if (sample_cnt > 0) {
            sd_adc_sample_buffer[cnt] = sd_adc_get_raw_code();
            cnt++;
        }
    }
#endif

    code_average = sd_adc_sort_and_get_average_code(sd_adc_sample_buffer);

    if(result_type == SD_ADC_VOLTAGE_10X_MV)
    {
        return sd_adc_result = sd_adc_calculate_voltage(code_average,result_type);
    }
    else if(result_type == SD_ADC_VOLTAGE_MV)
    {
        return sd_adc_result = sd_adc_calculate_voltage(code_average,result_type);

    }
    else if((result_type == TEMP_VALUE))
    {
        return sd_adc_result = sd_adc_calculate_temperature(code_average);
    }
    else
    {
        return 0;
    }
}

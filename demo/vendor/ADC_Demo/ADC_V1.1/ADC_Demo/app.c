/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for TL751X/TL721X/TL321X
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
#include "app_config.h"

adc_gpio_cfg_t adc_gpio_cfg_m =
{
        .v_ref = ADC_VREF_1P2V,
        .pre_scale = ADC_PRESCALE_1F8,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .pin = GPIO_M_CHN_SAMPLE_PIN,
};
adc_gpio_cfg_t adc_gpio_cfg_l =
{
        .v_ref = ADC_VREF_1P2V,
        .pre_scale = ADC_PRESCALE_1F8,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .pin = GPIO_L_CHN_SAMPLE_PIN,
};
adc_gpio_cfg_t adc_gpio_cfg_r =
{
        .v_ref = ADC_VREF_1P2V,
        .pre_scale = ADC_PRESCALE_1F8,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .pin = GPIO_R_CHN_SAMPLE_PIN,
};

typedef enum{
    ADC_VOLTAGE,
    TEMP_VALUE,
}adc_result_type_e;

volatile unsigned short adc_m_chn_val;
volatile unsigned short adc_l_chn_val;
volatile unsigned short adc_r_chn_val;
volatile unsigned short adc_temp_val;

unsigned short adc_sample_buffer[ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};
unsigned short channel_buffers[3][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};

unsigned short adc_sort_and_get_average_code(unsigned short *channel_sample_buffer);
void adc_code_split_dma(unsigned short *sample_buffer, unsigned int sample_num,unsigned char chn_cnt,unsigned short buffers[chn_cnt][sample_num]);
unsigned short adc_get_result(adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_result_type_e result_type);
void adc_start_dma(void);

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);

#if (ADC_MODE == ADC_DMA_MODE)
    adc_set_dma_config(ADC_DMA_CHN);

#if(ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN)
    adc_init(DMA_M_CHN);
#elif(ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN)
    adc_init(DMA_M_L_CHN);
#elif(ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
    adc_init(DMA_M_L_R_CHN);
#endif

#if((ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))

#if (ADC_M_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);
#elif(ADC_M_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_vbat_sample_init(ADC_M_CHANNEL);
#elif(ADC_M_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_init(ADC_M_CHANNEL);
#endif

#endif

#if((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))

#if (ADC_L_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_gpio_sample_init(ADC_L_CHANNEL,adc_gpio_cfg_l);
#elif(ADC_L_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_vbat_sample_init(ADC_L_CHANNEL);
#elif(ADC_L_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_init(ADC_L_CHANNEL);
#endif

#endif

#if(ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)

#if (ADC_R_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_gpio_sample_init(ADC_R_CHANNEL,adc_gpio_cfg_r);
#elif(ADC_R_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_vbat_sample_init(ADC_R_CHANNEL);
#elif(ADC_R_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_init(ADC_R_CHANNEL);
#endif

#endif


#elif (ADC_MODE == ADC_NDMA_MODE)

     adc_init(NDMA_M_CHN);

#if (ADC_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);
#elif(ADC_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_vbat_sample_init(ADC_M_CHANNEL);
#elif(ADC_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_init(ADC_M_CHANNEL);
#endif

#endif
    adc_power_on();
}

void main_loop (void)
{

#if(ADC_MODE == ADC_DMA_MODE)
    adc_start_dma();

#if((ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))

#if ((ADC_M_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE) || (ADC_M_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE))
    adc_m_chn_val = adc_get_result(DMA,ADC_M_CHANNEL,ADC_VOLTAGE);
#elif(ADC_M_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_val = adc_get_result(DMA,ADC_M_CHANNEL,TEMP_VALUE);
#endif

#endif

#if((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
#if ((ADC_L_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE) || (ADC_L_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE))
    adc_l_chn_val = adc_get_result(DMA,ADC_L_CHANNEL, ADC_VOLTAGE);
#elif(ADC_L_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_val = adc_get_result(DMA,ADC_L_CHANNEL,TEMP_VALUE);
#endif

#endif

#if(ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)

#if ((ADC_R_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE) || (ADC_R_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE))
    adc_r_chn_val = adc_get_result(DMA,ADC_R_CHANNEL, ADC_VOLTAGE);
#elif(ADC_R_CHN_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_val = adc_get_result(DMA,ADC_R_CHANNEL,TEMP_VALUE);
#endif

#endif

#elif(ADC_MODE == ADC_NDMA_MODE)

#if(ADC_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE)
    adc_temp_val = adc_get_result(NDMA,ADC_M_CHANNEL,TEMP_VALUE);
#else
    adc_m_chn_val = adc_get_result(NDMA,ADC_M_CHANNEL,ADC_VOLTAGE);
#endif

#endif

    delay_ms(500);
    gpio_toggle(LED1);
}

/**
 * @brief This function serves to sort adc sample code and get average value.
 * @param[in]   channel_sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @return      adc_code_average    - the average value of adc sample code.
 */
unsigned short adc_sort_and_get_average_code(unsigned short *channel_sample_buffer)
{
    int i, j;
    unsigned short adc_code_average = 0;
    unsigned short temp;

        /**** insert Sort and get average value ******/
        for(i = 1 ;i < ADC_SAMPLE_GROUP_CNT; i++)
        {
            if(channel_sample_buffer[i] < channel_sample_buffer[i-1])
            {
                temp = channel_sample_buffer[i];
                channel_sample_buffer[i] = channel_sample_buffer[i-1];
                for(j=i-1; j>=0 && channel_sample_buffer[j] > temp;j--)
                {
                    channel_sample_buffer[j+1] = channel_sample_buffer[j];
                }
                channel_sample_buffer[j+1] = temp;
            }
        }
        //get average value from raw data(abandon 1/4 small and 1/4 big data)
        for (i = ADC_SAMPLE_GROUP_CNT>>2; i < (ADC_SAMPLE_GROUP_CNT - (ADC_SAMPLE_GROUP_CNT>>2)); i++)
        {
            adc_code_average += channel_sample_buffer[i]/(ADC_SAMPLE_GROUP_CNT>>1);
        }
        return adc_code_average;
}

/**
 * @brief       This function serves to split the data from all channels in the sample buffer into different channels.
 * @param[in]   sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *                              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @param[in]   sample_num    - This parameter is used to set the size of the received dma and must be set to a multiple of 4. The maximum value that can be set is 0xFFFFFC.
 * @param[in]   chn_cnt -number of channels used.
 * @param[in]   buffers -This parameter is the first address of ADC sample channel buffers, which must be 4 bytes aligned, otherwise the program will enter an exception.
 * @return      none
 */
void adc_code_split_dma(unsigned short *sample_buffer, unsigned int sample_num,unsigned char chn_cnt,unsigned short buffers[chn_cnt][sample_num])
{
    unsigned int i,j;
    for (i = 0; i < chn_cnt; i++) {
        for (j = 0; j < sample_num; j++) {
            buffers[i][j] = sample_buffer[j*chn_cnt + i];
        }
    }
}
/**
 * @brief      This function is used to start the dma to get the adc sample code into adc_sample_buffer and split it into different channels of data.
 * @return     none.
 * @attention  When using multi-channel sampling in DMA mode, you need to make sure that the dma handling data process is not interrupted, otherwise it will result in the sampling data of the multi-channels being misordered when you come back;
 *             if there is a possibility of interruption in the process of data handling by the dma, you have to reconfigure and initialize the ADC and the DMA after coming back in order to continue to work normally.
 */
void adc_start_dma(void)
{
    adc_get_code_dma((unsigned short *)adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT));
    adc_code_split_dma((unsigned short *)adc_sample_buffer, ADC_SAMPLE_GROUP_CNT,ADC_SAMPLE_CHN_CNT ,channel_buffers);
}
/**
 * @brief      This function serves to convert to voltage value and temperature value.
 * @param[in]  transfer_mode -enum variable of adc code transfer mode.
 * @param[in]  chn - enum variable of ADC sample channel.
 * @param[in]  result_type - enum variable of result value
 * @return     adc_result   - adc voltage value or temperature value.
 */
unsigned short adc_get_result(adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_result_type_e result_type)
{
    unsigned short code_average;
    unsigned short adc_result;

    if(transfer_mode==NDMA)
    {
        for (int i = 0; i < ADC_SAMPLE_GROUP_CNT; i++)
        {
            channel_buffers[chn][i]= adc_get_code();
            if(channel_buffers[chn][i] & BIT(11)){ //12 bit resolution, BIT(11) is sign bit, 1 means negative voltage in differential_mode
                channel_buffers[chn][i]=0;
            }
            else{
                channel_buffers[chn][i] &= 0x7FF;  //BIT(10..0) is valid adc code
            }
        }
    }

    code_average = adc_sort_and_get_average_code(channel_buffers[chn]);

    if(result_type == ADC_VOLTAGE)
    {
        return adc_result = adc_calculate_voltage(chn, code_average);
    }else if((result_type == TEMP_VALUE))
    {
        return adc_result = adc_calculate_temperature(code_average);
    }else
    {
        return 0;
    }
}

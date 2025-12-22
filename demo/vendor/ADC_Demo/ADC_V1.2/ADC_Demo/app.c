/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"

#if (DEMO_MODE == NORMAL_MODE)
adc_chn_cfg_t adc_cfg_m =
{
        .pre_scale = ADC_PRESCALE_1F4,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .input_p = GPIO_M_CHNP_SAMPLE_SIGNAL,
        .input_n = GPIO_M_CHNN_SAMPLE_SIGNAL,
};
adc_chn_cfg_t adc_cfg_l =
{
        .pre_scale = ADC_PRESCALE_1F4,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .input_p = GPIO_L_CHNP_SAMPLE_SIGNAL,
        .input_n = GPIO_L_CHNN_SAMPLE_SIGNAL,
};
adc_chn_cfg_t adc_cfg_r =
{
        .pre_scale = ADC_PRESCALE_1F4,
        .sample_freq = ADC_SAMPLE_FREQ_96K,
        .input_p = GPIO_R_CHNP_SAMPLE_SIGNAL,
        .input_n = GPIO_R_CHNN_SAMPLE_SIGNAL,
};

volatile short adc_m_chn_val;
volatile short adc_l_chn_val;
volatile short adc_r_chn_val;
volatile short adc_temp_val;
volatile unsigned int  adc_dma_rx_done_flag = 0;

short adc_sample_buffer[ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};
short channel_buffers[3][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};

short adc_sort_and_get_average_code(short *channel_sample_buffer);
short adc_get_result(adc_num_e sar_adc_num,adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_input_pch_e input_p);
#if (ADC_MODE == ADC_DMA_MODE)
void adc_code_split_dma(short *sample_buffer, unsigned int sample_num,unsigned char chn_cnt,short buffers[chn_cnt][sample_num]);
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_set_low_level(LED1);
    gpio_set_high_level(LED1);

#if (ADC_MODE == ADC_DMA_MODE)
    adc_set_dma_config(ADC_MODULE_SEL,ADC_DMA_CHN);
    dma_set_irq_mask(ADC_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();

#if(ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN)
    adc_init(ADC_MODULE_SEL,DMA_M_CHN);


#elif(ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN)
    adc_init(ADC_MODULE_SEL,DMA_M_L_CHN);
#elif(ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
    adc_init(ADC_MODULE_SEL,DMA_M_L_R_CHN);
#endif

#if((ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))

#if (ADC_M_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);
#elif(ADC_M_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0_MODULE,ADC_VBAT_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);
#endif

#endif

#if(INTERNAL_TEST_FUNC_EN && ((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)))

#if (ADC_L_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_L_CHANNEL,&adc_cfg_l);
#elif(ADC_L_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0_MODULE,ADC_VBAT_SAMPLE,ADC_L_CHANNEL,&adc_cfg_l);
#endif

#endif

#if(INTERNAL_TEST_FUNC_EN && ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)

#if (ADC_R_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_R_CHANNEL,&adc_cfg_r);
#elif(ADC_R_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0_MODULE,ADC_VBAT_SAMPLE,ADC_R_CHANNEL,&adc_cfg_r);
#endif

#endif


#elif (ADC_MODE == ADC_NDMA_MODE)
    adc_init(ADC_MODULE_SEL,NDMA_M_CHN);
#if (ADC_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);

#elif(ADC_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0_MODULE,ADC_VBAT_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);

#elif( INTERNAL_TEST_FUNC_EN && (ADC_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE))
    adc_channel_sample_init(ADC0_MODULE,ADC_TEMP_SENSOR_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);
#endif
#endif
#if INTERNAL_TEST_FUNC_EN
#if (ADC_FEATURE_MODE == ADC_PEM_FEATURE)
    pem_init();
#if(PEM_EVENT_MODE == PEM_GPIO)
    gpio_set_pem_event(ADC_MODULE_SEL,0,GPIO_PA1);
#elif(PEM_EVENT_MODE == PEM_SAR_ADC)
    adc_set_pem_event(ADC_MODULE_SEL,0,ADC_PEM_EVENT_RX_THRESHOLD)
#endif

#if(PEM_TASK_MODE == PEM_GPIO)
    gpio_set_pem_task(ADC_MODULE_SEL,0,GPIO_PA0);
#elif(PEM_TASK_MODE == PEM_SAR_ADC)
    adc_trigger_en(sar_adc_num);
    adc_set_trigger_cnt(ADC_MODULE_SEL,TRIGGER_CNT);
    adc_set_pem_task(ADC_MODULE_SEL,0);
#endif
    pem_chn_en(0);
#elif(ADC_FEATURE_MODE == ADC_TRIGGER_FEATURE)
    adc_trigger_en(sar_adc_num);
    adc_set_trigger_cnt(TRIGGER_CNT);
#elif(ADC_FEATURE_MODE == ADC_OVERSAMPLE_FEATURE)
    adc_oversample_en(sar_adc_num);
    adc_set_oversample_cnt(OVERSAMPLE_AVERAGE_CNT);
#elif(ADC_FEATURE_MODE == ADC_TRIGGER_AND_OVERSAMPLE_FEATURE)
    adc_oversample_en(sar_adc_num);
    adc_trigger_en(sar_adc_num);
    adc_set_oversample_cnt(OVERSAMPLE_AVERAGE_CNT);
    adc_set_trigger_cnt(TRIGGER_CNT);
#endif
#endif
}

void main_loop (void)
{
    adc_power_on(ADC_MODULE_SEL);

#if(ADC_MODE == ADC_DMA_MODE)

    adc_start_sample_dma(ADC_MODULE_SEL,(short *)adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT)<<1);
#if (INTERNAL_TEST_FUNC_EN && (ADC_FEATURE_MODE == ADC_TRIGGER_FEATURE || ADC_FEATURE_MODE == ADC_TRIGGER_AND_OVERSAMPLE_FEATURE))
    adc_trigger_start();
#endif
    adc_dma_rx_done_flag = 0;
    while(!adc_dma_rx_done_flag);
    adc_code_split_dma((short *)adc_sample_buffer , ADC_SAMPLE_GROUP_CNT,ADC_SAMPLE_CHN_CNT,channel_buffers);

#if((ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
    adc_m_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_M_CHANNEL,adc_cfg_m.input_p);
#endif
#if(INTERNAL_TEST_FUNC_EN && ((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)))
    adc_l_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_L_CHANNEL, adc_cfg_l.input_p);
#endif
#if(INTERNAL_TEST_FUNC_EN && (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
    adc_r_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_R_CHANNEL, adc_cfg_r.input_p);
#endif


#elif(ADC_MODE == ADC_NDMA_MODE)

#if(INTERNAL_TEST_FUNC_EN && (ADC_SAMPLE_MODE == ADC_TEMP_SENSOR_SAMPLE))
    adc_temp_val = adc_get_result(NDMA,ADC_M_CHANNEL,TEMP_VALUE);
#else

    adc_m_chn_val = adc_get_result(ADC_MODULE_SEL,NDMA,ADC_M_CHANNEL,adc_cfg_m.input_p);
#endif

#endif

    adc_power_off(ADC_MODULE_SEL);
    delay_ms(500);
    gpio_toggle(LED1);
}

#if(ADC_MODE == ADC_DMA_MODE)
_attribute_ram_code_sec_ void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(BIT(ADC_DMA_CHN)))
    {
        adc_dma_rx_done_flag = 1;
        /******clear adc sample finished status********/
        adc_clr_irq_status_dma(ADC_MODULE_SEL);
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
#endif

/**
 * @brief This function serves to sort adc sample code and get average value.
 * @param[in]   channel_sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @return      adc_code_average    - the average value of adc sample code.
 */
short adc_sort_and_get_average_code(short *channel_sample_buffer)
{
    int i, j;
    int adc_code_average = 0;
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
            adc_code_average += channel_sample_buffer[i];//If the filtered data exceeds 10,000 entries, there is a risk of overflow.
        }
        return (short)(adc_code_average/(ADC_SAMPLE_GROUP_CNT>>1));
}
/**
 * @brief      This function serves to convert to voltage value and temperature value.
 * @param[in]  transfer_mode -enum variable of adc code transfer mode.
 * @param[in]  chn - enum variable of ADC sample channel.
 * @param[in]  result_type - enum variable of result value
 * @return     adc_result   - adc voltage value or temperature value.
 */
short adc_get_result(adc_num_e sar_adc_num,adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_input_pch_e input_p)
{
    short code_average;
    short adc_result;
    unsigned int cnt = 0;
    if(transfer_mode==NDMA)
    {
        adc_start_sample_nodma(sar_adc_num);
#if INTERNAL_TEST_FUNC_EN && ((ADC_FEATURE_MODE == ADC_TRIGGER_FEATURE) || (ADC_FEATURE_MODE == ADC_TRIGGER_AND_OVERSAMPLE_FEATURE))
        adc_trigger_start();
#endif
        while (cnt < ADC_SAMPLE_GROUP_CNT)
        {

            int sample_cnt = adc_get_rxfifo_cnt(sar_adc_num);
            if (sample_cnt > 0)
            {
                channel_buffers[chn][cnt]= adc_get_raw_code(sar_adc_num);

                if(channel_buffers[chn][cnt] & BIT(11)){ //12 bit resolution, BIT(11) is sign bit, 1 means negative voltage in differential_mode
                    channel_buffers[chn][cnt]=0;
                }
                else{
                channel_buffers[chn][cnt] &= 0x7FF;  //BIT(10..0) is valid adc code
                }
                cnt++;
            }
        }
    }
    code_average = adc_sort_and_get_average_code(channel_buffers[chn]);


   if(input_p == ADC_VBAT_P){
        return adc_result = adc_calculate_voltage(ADC_VBAT_SAMPLE,chn,code_average);
    }
#if INTERNAL_TEST_FUNC_EN
    else if(input_p == ADC_TEMPSENSORN_P){
        return input_p =  adc_calculate_voltage(ADC_TEMP_SENSOR_MODE,chn,code_average);
    }
#endif
    else{
        return adc_result = adc_calculate_voltage(ADC_GPIO_SAMPLE,chn,code_average);
    }
}

#if (ADC_MODE == ADC_DMA_MODE)
/**
 * @brief       This function serves to split the data from all channels in the sample buffer into different channels.
 * @param[in]   sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *                              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @param[in]   sample_num    - This parameter is used to set the size of the received dma and must be set to a multiple of 4. The maximum value that can be set is 0xFFFFFC.
 * @param[in]   chn_cnt -number of channels used.
 * @param[in]   buffers -This parameter is the first address of ADC sample channel buffers, which must be 4 bytes aligned, otherwise the program will enter an exception.
 * @return      none
 */
void adc_code_split_dma(short *sample_buffer, unsigned int sample_num,unsigned char chn_cnt,short buffers[chn_cnt][sample_num])
{
    unsigned int i,j;
    for (i = 0; i < chn_cnt; i++) {
        for (j = 0; j < sample_num; j++) {
            buffers[i][j] = sample_buffer[j*chn_cnt + i];
        }
    }
}
#endif
#endif


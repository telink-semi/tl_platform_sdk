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

    #if (ADC_MODE == ADC_SIGNAL_ADC_RUNNING_MODE)
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
        #if ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE
dma_chain_config_t rx_dma_list;
        #endif
volatile short adc_m_chn_val;
volatile short adc_l_chn_val;
volatile short adc_r_chn_val;
volatile short adc_temp_val;
volatile unsigned int  adc_dma_rx_done_flag = 0;

short adc_sample_buffer[ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};

short adc_sort_and_get_average_code(short *channel_sample_buffer);
    #elif (ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)
adc_chn_cfg_t sar0_adc_cfg_m = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC0_GPIO_PC0P,
    .input_n     = ADC_GND_N,
};

adc_chn_cfg_t sar0_adc_cfg_l = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC0_GPIO_PC1P,
    .input_n     = ADC_GND_N,
};

adc_chn_cfg_t sar0_adc_cfg_r = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC0_GPIO_PC2P,
    .input_n     = ADC_GND_N,
};

adc_chn_cfg_t sar1_adc_cfg_m = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC1_GPIO_PB0P,
    .input_n     = ADC_GND_N,
};

adc_chn_cfg_t sar1_adc_cfg_l = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC1_GPIO_PB1P,
    .input_n     = ADC_GND_N,
};

adc_chn_cfg_t sar1_adc_cfg_r = {
    .pre_scale   = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_2M,
    .input_p     = ADC1_GPIO_PB2P,
    .input_n     = ADC_GND_N,
};

volatile short sar0_adc_m_chn_val;
volatile short sar1_adc_m_chn_val;

        #if (ADC_SLE_DMA_MODE != ADC_NDMA_MODE )
            #if (ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN || ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
volatile short sar0_adc_l_chn_val;
                #if ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
volatile short sar0_adc_r_chn_val;
                #endif
            #endif


            #if (ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN || ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
volatile short sar1_adc_l_chn_val;

                #if ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
volatile short sar1_adc_r_chn_val;
                #endif
            #endif

            #if ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE
volatile unsigned int sar0_dma_rx_done_flag = 0;
volatile unsigned int sar1_dma_rx_done_flag = 0;
            #elif ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE
dma_chain_config_t rx_dma_list[2];
            #endif
short sar0_adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAR0_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};
short sar1_adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAR1_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};

short sar0_channel_buffers[ADC_SAR0_SAMPLE_CHN_CNT][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
short sar1_channel_buffers[ADC_SAR1_SAMPLE_CHN_CNT][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
        #else
short sar0_adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};
short sar1_adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAMPLE_CHN_CNT] __attribute__((aligned(4))) = {0};

short sar0_channel_buffers[ADC_SAMPLE_CHN_CNT][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
short sar1_channel_buffers[ADC_SAMPLE_CHN_CNT][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
        #endif
short adc_sort_and_get_average_code(short *channel_sample_buffer);
    #endif
short adc_get_result_dma_dual_sar(adc_num_e sar_adc_num, adc_sample_chn_e chn, adc_input_pch_e input_p);

volatile unsigned int  adc_power_flag = 1;
short channel_buffers[3][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
short adc_get_result(adc_num_e sar_adc_num,adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_input_pch_e input_p);

    #if (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE || ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE)
void adc_code_split_dma(short *sample_buffer, unsigned int sample_num,unsigned char chn_cnt,short buffers[chn_cnt][sample_num]);
    #endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_toggle(LED1);

    #if (ADC_MODE == ADC_SIGNAL_ADC_RUNNING_MODE)
        #if (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE || ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE)

            #if (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
    adc_set_dma_config(ADC_MODULE_SEL,ADC_DMA_CHN);
    dma_set_irq_mask(ADC_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    adc_dma_rx_done_flag = 0;
            #endif
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
    adc_channel_sample_init(ADC0,ADC_VBAT_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);
                #endif

            #endif

            #if(((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)))

                #if (ADC_L_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_L_CHANNEL,&adc_cfg_l);
                #elif(ADC_L_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0,ADC_VBAT_SAMPLE,ADC_L_CHANNEL,&adc_cfg_l);
                #endif

            #endif

            #if(ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)

                #if (ADC_R_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_R_CHANNEL,&adc_cfg_r);
                #elif(ADC_R_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0,ADC_VBAT_SAMPLE,ADC_R_CHANNEL,&adc_cfg_r);
                #endif
            #endif
            #if ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE

    adc_power_on(ADC_MODULE_SEL);
    adc_dma_chain_transmission_start(ADC_MODULE_SEL, ADC_DMA_CHN,(unsigned short *)(adc_sample_buffer), ADC_SAMPLE_GROUP_CNT*2*ADC_SAMPLE_CHN_CNT, &rx_dma_list);
            #endif

        #elif (ADC_SLE_DMA_MODE == ADC_NDMA_MODE)
    adc_init(ADC_MODULE_SEL,NDMA_M_CHN);
            #if (ADC_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC_MODULE_SEL,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);

            #elif(ADC_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0,ADC_VBAT_SAMPLE,ADC_M_CHANNEL,&adc_cfg_m);

            #endif
        #endif
        #if (ADC_SLE_DMA_MODE != ADC_NDMA_MODE)
            #if ADC_TRIGGER_FEATURE
    adc_trigger_en(ADC0);
    adc_set_trigger_cnt(ADC0,TRIGGER_CNT);
            #endif
        #endif
    #elif (ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)
        #if (ADC_SLE_DMA_MODE == ADC_NDMA_MODE)
    adc_init(ADC0,NDMA_M_CHN);
    adc_init(ADC1,NDMA_M_CHN);
            #if (ADC_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC0,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&sar0_adc_cfg_m);
    adc_channel_sample_init(ADC1,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&sar1_adc_cfg_m);
            #elif(ADC_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0,ADC_VBAT_SAMPLE,ADC_M_CHANNEL,&sar0_adc_cfg_m);
    adc_channel_sample_init(ADC1,ADC_GPIO_SAMPLE,ADC_M_CHANNEL,&sar1_adc_cfg_m);//SAR1 does not support vbat sampling. You can connect the gpio sampling pin to the battery externally.
            #endif

        #elif (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE || ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE)
            #if ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE
    adc_set_dma_config(ADC0, SAR0_DMA_CHN);
    dma_set_irq_mask(SAR1_DMA_CHN, TC_MASK);
    adc_set_dma_config(ADC1, SAR1_DMA_CHN);
    dma_set_irq_mask(SAR0_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    sar0_dma_rx_done_flag = 0;
    sar1_dma_rx_done_flag = 0;
            #endif
            #if(ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN)
    adc_init(ADC0, DMA_M_CHN);
            #elif(ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN)
    adc_init(ADC0,DMA_M_L_CHN);
            #elif(ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
    adc_init(ADC0,DMA_M_L_R_CHN);
            #endif
            #if(ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN)
    adc_init(ADC1, DMA_M_CHN);
            #elif(ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN)
    adc_init(ADC1,DMA_M_L_CHN);
            #elif(ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
    adc_init(ADC1,DMA_M_L_R_CHN);
            #endif
            #if((ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
                #if (ADC_SAR0_M_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_GPIO_SAMPLE, ADC_M_CHANNEL, &sar0_adc_cfg_m);
                #elif(ADC_SAR0_M_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_VBAT_SAMPLE, ADC_M_CHANNEL, &sar0_adc_cfg_m);
                #endif
                #if((ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
                    #if (ADC_SAR0_L_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_GPIO_SAMPLE, ADC_L_CHANNEL, &sar0_adc_cfg_l);
                    #elif(ADC_SAR0_L_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_VBAT_SAMPLE, ADC_L_CHANNEL, &sar0_adc_cfg_l);
                    #endif
                    #if ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
                        #if (ADC_SAR0_R_CHN_SAMPLE_MODE == ADC_GPIO_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_GPIO_SAMPLE, ADC_R_CHANNEL, &sar0_adc_cfg_r);
                        #elif(ADC_SAR0_R_CHN_SAMPLE_MODE == ADC_VBAT_SAMPLE)
    adc_channel_sample_init(ADC0, ADC_VBAT_SAMPLE, ADC_R_CHANNEL, &sar0_adc_cfg_r);
                        #endif
                    #endif
                #endif
            #endif
        #if((ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
    adc_channel_sample_init(ADC1, ADC_GPIO_SAMPLE, ADC_M_CHANNEL, &sar1_adc_cfg_m);
                #if (ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN || ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
    adc_channel_sample_init(ADC1, ADC_GPIO_SAMPLE, ADC_L_CHANNEL, &sar1_adc_cfg_l);
                    #if ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
    adc_channel_sample_init(ADC1, ADC_GPIO_SAMPLE, ADC_R_CHANNEL, &sar1_adc_cfg_r);
                    #endif
                #endif
            #endif
            #if ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE
    adc_power_on(ADC0);
    adc_power_on(ADC1);
    adc_dma_chain_transmission_start(ADC0, SAR0_DMA_CHN,(unsigned short *)(sar0_adc_sample_buffer), ADC_SAMPLE_GROUP_CNT*2*ADC_SAR0_SAMPLE_CHN_CNT, &rx_dma_list[0]);
    adc_dma_chain_transmission_start(ADC1, SAR1_DMA_CHN,(unsigned short *)(sar1_adc_sample_buffer), ADC_SAMPLE_GROUP_CNT*2*ADC_SAR1_SAMPLE_CHN_CNT, &rx_dma_list[1]);
            #endif
        #endif
    #endif
    #if (ADC_SLE_DMA_MODE != ADC_NDMA_MODE)
        #if ADC_TRIGGER_FEATURE
    adc_trigger_en(ADC0);
    adc_set_trigger_cnt(ADC0,TRIGGER_CNT);
    adc_trigger_en(ADC1);
    adc_set_trigger_cnt(ADC1,TRIGGER_CNT);
        #endif
    #endif
}
void main_loop (void)
{
    #if(ADC_SLE_DMA_MODE != ADC_NDMA_MODE)
    static int loop_cnt = 0;
    if(!(loop_cnt % 50))
    {
        #if ADC_TRIGGER_FEATURE
            #if(ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)
        adc_trigger_start(ADC0);
        adc_trigger_start(ADC1);
            #elif(ADC_MODE == ADC_SIGNAL_ADC_RUNNING_MODE)
        adc_trigger_start(ADC_MODULE_SEL);
            #endif
        #endif
    }
    loop_cnt ++;
        #endif

    #if(ADC_MODE == ADC_SIGNAL_ADC_RUNNING_MODE)
        #if(ADC_SLE_DMA_MODE == ADC_NDMA_MODE)
    adc_power_on(ADC_MODULE_SEL);

    adc_m_chn_val = adc_get_result(ADC_MODULE_SEL,NDMA,ADC_M_CHANNEL,adc_cfg_m.input_p);
    printf("adc_m_chn_val = %d \n", adc_m_chn_val);
    adc_power_off(ADC_MODULE_SEL);
    delay_ms(500);
    gpio_toggle(LED1);
        #elif(ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE || ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE)
            #if(ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
    if(adc_power_flag)
    {
        adc_power_flag = 0;
        adc_power_on(ADC_MODULE_SEL);
        adc_start_sample_dma(ADC_MODULE_SEL,(short *)adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT*ADC_SAMPLE_CHN_CNT)<<1);
    }
    if(adc_dma_rx_done_flag)

            #endif
    {
        adc_code_split_dma((short *)adc_sample_buffer , ADC_SAMPLE_GROUP_CNT,ADC_SAMPLE_CHN_CNT,channel_buffers);

            #if((ADC_SAMPLE_CHN_CNT == DMA_M_1_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
        adc_m_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_M_CHANNEL,adc_cfg_m.input_p);
        printf("adc_m_chn_val = %d \n", adc_m_chn_val);
            #endif
            #if(((ADC_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN) || (ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)))
        adc_l_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_L_CHANNEL, adc_cfg_l.input_p);
        printf("adc_l_chn_val = %d \n", adc_l_chn_val);
            #endif
            #if((ADC_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN))
        adc_r_chn_val = adc_get_result(ADC_MODULE_SEL,DMA,ADC_R_CHANNEL, adc_cfg_r.input_p);
        printf("adc_r_chn_val = %d \n", adc_r_chn_val);
            #endif
            #if(ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
        adc_power_off(ADC_MODULE_SEL);
        adc_power_flag = 1 ;
        adc_dma_rx_done_flag = 0;
        /*
         *   It is necessary to wait for a period of time. Otherwise, in the case of high sampling rate, there will be many interrupt triggers,
         *   and the program is likely to get stuck in the interrupt continuously.
         */
        delay_ms(100);
        gpio_toggle(LED1);
            #endif

    }

        #endif
    #elif (ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)
        #if ADC_SLE_DMA_MODE == ADC_NDMA_MODE
    adc_power_on(ADC0);
    adc_power_on(ADC1);

    sar0_adc_m_chn_val = adc_get_result(ADC0,NDMA,ADC_M_CHANNEL,sar0_adc_cfg_m.input_p);
    sar1_adc_m_chn_val = adc_get_result(ADC1,NDMA,ADC_M_CHANNEL,sar1_adc_cfg_m.input_p);
    printf("sar0_adc_m_chn_val = %d \n", sar0_adc_m_chn_val);
    printf("sar1_adc_m_chn_val = %d \n", sar1_adc_m_chn_val);
    adc_power_off(ADC0);
    adc_power_off(ADC1);
    delay_ms(500);
    gpio_toggle(LED1);
        #elif(ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE || ADC_SLE_DMA_MODE == ADC_DMA_CHAIN_MODE)
            #if (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
    if(adc_power_flag)
    {
        adc_power_flag = 0;
        adc_power_on(ADC0);
        adc_power_on(ADC1);
        adc_start_sample_dma(ADC0, (short *)sar0_adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT * ADC_SAR0_SAMPLE_CHN_CNT) << 1);
        adc_start_sample_dma(ADC1, (short *)sar1_adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT * ADC_SAR1_SAMPLE_CHN_CNT) << 1);
    }


    if(sar0_dma_rx_done_flag && sar1_dma_rx_done_flag)
    {

        sar0_dma_rx_done_flag = 0;
        sar1_dma_rx_done_flag = 0;
            #endif

        adc_code_split_dma((short *)sar0_adc_sample_buffer, ADC_SAMPLE_GROUP_CNT, ADC_SAR0_SAMPLE_CHN_CNT, sar0_channel_buffers);
        adc_code_split_dma((short *)sar1_adc_sample_buffer, ADC_SAMPLE_GROUP_CNT, ADC_SAR1_SAMPLE_CHN_CNT, sar1_channel_buffers);

        sar0_adc_m_chn_val = adc_get_result_dma_dual_sar(ADC0, ADC_M_CHANNEL, sar0_adc_cfg_m.input_p);
        sar1_adc_m_chn_val = adc_get_result_dma_dual_sar(ADC1, ADC_M_CHANNEL, sar1_adc_cfg_m.input_p);
        printf("sar0_adc_m_chn_val = %d \n", sar0_adc_m_chn_val);
        printf("sar1_adc_m_chn_val = %d \n", sar1_adc_m_chn_val);
            #if (ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN || ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
        sar0_adc_l_chn_val = adc_get_result_dma_dual_sar(ADC0, ADC_L_CHANNEL, sar0_adc_cfg_l.input_p);
        printf("sar0_adc_l_chn_val = %d \n", sar0_adc_l_chn_val);
                #if ADC_SAR0_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
        sar0_adc_r_chn_val = adc_get_result_dma_dual_sar(ADC0, ADC_R_CHANNEL, sar0_adc_cfg_r.input_p);
        printf("sar0_adc_r_chn_val = %d \n", sar0_adc_r_chn_val);
                #endif
            #endif

            #if (ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_2_CHN_EN || ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN)
        sar1_adc_l_chn_val = adc_get_result_dma_dual_sar(ADC1, ADC_L_CHANNEL, sar1_adc_cfg_l.input_p);
        printf("sar1_adc_l_chn_val = %d \n", sar1_adc_l_chn_val);
                #if ADC_SAR1_SAMPLE_CHN_CNT == DMA_M_L_R_3_CHN_EN
        sar1_adc_r_chn_val = adc_get_result_dma_dual_sar(ADC1, ADC_R_CHANNEL, sar1_adc_cfg_r.input_p);
        printf("sar1_adc_r_chn_val = %d \n", sar1_adc_r_chn_val);   
                #endif
            #endif

            #if (ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
        adc_power_flag = 1;
        adc_power_off(ADC0);
        adc_power_off(ADC1);
        /*
         *   It is necessary to wait for a period of time. Otherwise, in the case of high sampling rate, there will be many interrupt triggers,
         *   and the program is likely to get stuck in the interrupt continuously.
         */
        delay_ms(100);
        gpio_toggle(LED1);
    }
            #endif
        #endif
    #endif
}

    #if(ADC_SLE_DMA_MODE == ADC_DMA_INTERRUPT_MODE)
        #if(ADC_MODE == ADC_SIGNAL_ADC_RUNNING_MODE)
_attribute_ram_code_sec_ void dma_irq_handler(void)
{

    if(dma_get_tc_irq_status(BIT(ADC_DMA_CHN)))
    {
        adc_dma_rx_done_flag = 1;
        /******clear adc sample finished status********/
        adc_clr_irq_status_dma(ADC_MODULE_SEL);
    }
}
        #elif(ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)

_attribute_ram_code_sec_ void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(BIT(SAR0_DMA_CHN)))
    {
        sar0_dma_rx_done_flag = 1;
        adc_clr_irq_status_dma(ADC0);
    }
    if(dma_get_tc_irq_status(BIT(SAR1_DMA_CHN)))
    {
        sar1_dma_rx_done_flag = 1;
        adc_clr_irq_status_dma(ADC1);
    }
}
        #endif
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


    #if (ADC_MODE == ADC_DOUBLE_ADC_RUNNING_MODE)
/**
 * @brief      This function serves to convert to two sar voltage value.
 * @param[in]  transfer_mode -enum variable of adc code transfer mode.
 * @param[in]  chn - enum variable of ADC sample channel.
 * @param[in]  result_type - enum variable of result value
 * @return     adc_result   - adc voltage value or temperature value.
 */
short adc_get_result_dma_dual_sar(adc_num_e sar_adc_num, adc_sample_chn_e chn, adc_input_pch_e input_p)
{
    short code_average;
    short adc_result;

    if (sar_adc_num == ADC0) {
        code_average = adc_sort_and_get_average_code(sar0_channel_buffers[chn]);
    } else {
        code_average = adc_sort_and_get_average_code(sar1_channel_buffers[chn]);
    }

    if (input_p == ADC_VBAT_P) {
        adc_result = adc_calculate_voltage(sar_adc_num, ADC_VBAT_SAMPLE, chn, code_average);
    } else {
        adc_result = adc_calculate_voltage(sar_adc_num, ADC_GPIO_SAMPLE, chn, code_average);
    }

    return adc_result;
}
    #endif
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
        while (cnt < ADC_SAMPLE_GROUP_CNT)
        {
            int sample_cnt = adc_get_rxfifo_cnt(sar_adc_num);
            if (sample_cnt > 0)
            {
                channel_buffers[chn][cnt]= adc_get_raw_code(sar_adc_num);
                cnt++;
            }
        }
    }
    code_average = adc_sort_and_get_average_code(channel_buffers[chn]);


   if(input_p == ADC_VBAT_P){
        return adc_result = adc_calculate_voltage(sar_adc_num,ADC_VBAT_SAMPLE,chn,code_average);
    }

    else{
        return adc_result = adc_calculate_voltage(sar_adc_num,ADC_GPIO_SAMPLE,chn,code_average);
    }
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

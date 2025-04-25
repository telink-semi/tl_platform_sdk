/********************************************************************************************************
 * @file    app_autotest.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2023, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#if (DEMO_MODE == TEST_MODE)
// set parament cmd
#define CMD_PRE_SCALER 0x01
#define CMD_VREF_VOL 0x02
#define CMD_DMA 0x03
#define CMD_CLOCK 0x04
#define CMD_CORE_REG 0x06
#define CMD_VBAT_MODE 0x07
#define CMD_SET_COLLECT_MODE 0x08
#define CMD_DIVIDER      0x09
#define CMD_POWER_AFTER_DELAY      0x0a
#define CMD_DWA_SELECT     0x0b
#define CMD_WRITE_CORE_REG 0x10 // This function is not implemented in the next machine and is used as a placeholder
#define CMD_WRITE_ANALOG_REG 0x20
#define CMD_WRITE_ANALOG_HIGH_REG 0x21
#define ADC_DMA_CHN DMA7

typedef enum
{
    ADC_VOLTAGE,
    TEMP_VALUE,
} adc_result_type_e;

adc_chn_cnt_e DMA_chanal = NDMA_M_CHN;
adc_transfer_mode_e DMA_type = NDMA;

volatile int collect_times = 100;
char collect_adc_val[1000];
volatile char collect_adc_val1[1000];
volatile unsigned int correct_cmd_count = 0;
volatile unsigned int cmd_count = 0;
volatile unsigned int cmd_display = 0;
volatile unsigned char adc_start_flag = 1;

volatile unsigned short adc_temp_val;
volatile unsigned short adc_m_chn_val;
volatile int poweron_after_delay = 90;
volatile char cmd_dwa_select = 0;
unsigned short channel_buffers[3][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
unsigned short adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAMPLE_CHN_CNT];
volatile unsigned char adc_high_addr = 0;
volatile unsigned char adc_init_flg = 1;
#if defined(MCU_CORE_TL751X)
adc_gpio_cfg_t adc_gpio_cfg_m =
{
    .v_ref = ADC_VREF_GPIO_1P2V,
    .pre_scale = ADC_PRESCALE_1F8,
    .sample_freq = ADC_SAMPLE_FREQ_96K,
    .pin = ADC_GPIO_PG0,
};
adc_chn_cfg_t chn_cfg =
{
    .divider = ADC_VBAT_DIV_1F4,
    .v_ref = ADC_VREF_VBAT_1P2V,
    .pre_scale = ADC_PRESCALE_1,
    .sample_freq = ADC_SAMPLE_FREQ_96K,
    .input_p = ADC_VBAT,
    .input_n = GND,

};
#elif defined(MCU_CORE_TL721X)
adc_gpio_cfg_t adc_gpio_cfg_m =
{
        .v_ref = ADC_VREF_GPIO_1P2V,
        .pre_scale = ADC_PRESCALE_1F4,
        .sample_freq = ADC_SAMPLE_FREQ_23K,
        .pin = GPIO_M_CHN_SAMPLE_PIN,
};

adc_chn_cfg_t chn_cfg =
{
    .divider = ADC_VBAT_DIV_1F4,
    .v_ref = ADC_VREF_GPIO_1P2V,
    .pre_scale = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_23K,
    .input_p = ADC_VBAT,
    .input_n = GND,

};
#elif defined(MCU_CORE_TL321X)
adc_gpio_cfg_t adc_gpio_cfg_m =
{
        .v_ref = ADC_VREF_1P2V,
        .pre_scale = ADC_PRESCALE_1F4,
        .sample_freq = ADC_SAMPLE_FREQ_23K,
        .pin = GPIO_M_CHN_SAMPLE_PIN,
};

adc_chn_cfg_t chn_cfg =
{
    .divider = ADC_VBAT_DIV_1F4,
    .v_ref = ADC_VREF_1P2V,
    .pre_scale = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_23K,
    .input_p = ADC_VBAT,
    .input_n = GND,

};
#endif
void adc_temperature_test(void);
void adc_set_parameter_start_sample_test(void);
void adc_set_parameter_start_vbat_test(void);
void adc_set_parameter_collect_sample_test(void);
void adc_sample_test(void);
void adc_vbat_test(void);
void adc_set_parameter(void);
void adc_multiple_vbat_test(void);
void adc_multiple_sample_test(void);
void adc_get_data_collect_test(void);
void adc_set_parameter_collect_vbat_test(void);
void adc_multiple_filter_partial_pressure_sample_test(void);
extern void adc_chn_config(adc_sample_chn_e chn , adc_chn_cfg_t adc_cfg);
//unsigned short adc_get_result(adc_transfer_mode_e transfer_mode, adc_sample_chn_e chn);
unsigned short adc_get_result(adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_result_type_e result_type);
struct PC_CMD_FUNC
{
    unsigned short cmd_name;
    void (*func)(void);
};
#if defined(MCU_CORE_TL751X)
volatile unsigned int adc_data = 0;
void adc_collection_data(void)
{

    memset(collect_adc_val, 0, sizeof(collect_adc_val));
    int i = 0;
    while (i < collect_times*2)
    {
        int sample_cnt = adc_get_rxfifo_cnt();
        if (sample_cnt > 0)
        {
            gpio_toggle(GPIO_PE0);
            adc_data =  adc_get_raw_code();
            adc_m_chn_val= adc_data & 0xffff;


            collect_adc_val[i] = adc_m_chn_val & 0xff;
            collect_adc_val[i+1] = (adc_m_chn_val >> 8) & 0xff;

            adc_m_chn_val= (adc_data & 0xffff0000 >> 16);
            collect_adc_val[i+2] = adc_m_chn_val & 0xff;
            collect_adc_val[i+3] = (adc_m_chn_val >> 8) & 0xff;
            i+=4 ;
        }
    }
}
#elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
void adc_collection_data(void)
{
    memset(collect_adc_val, 0, sizeof(collect_adc_val));
    int i = 0;
    while (i < collect_times*2)
    {
        int sample_cnt = adc_get_rxfifo_cnt();
        if (sample_cnt > 0)
        {
            gpio_toggle(GPIO_PE0);
            adc_m_chn_val= adc_get_raw_code();
            collect_adc_val[i] = adc_m_chn_val & 0xff;
            collect_adc_val[i+1] = (adc_m_chn_val >> 8) & 0xff;
            i+=2 ;
        }
    }
}
#endif
/**
 * @brief       This function serves to split the data from all channels in the sample buffer into different channels.
 * @param[in]   sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *                              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @param[in]   sample_num       - This parameter is used to set the size of the received dma and must be set to a multiple of 4. The maximum value that can be set is 0xFFFFFC.
 * @param[in]   chn_cnt -number of channels used.
 * @param[in]   buffers -This parameter is the first address of ADC sample channel buffers, which must be 4 bytes aligned, otherwise the program will enter an exception.
 * @return         none
 */
void adc_code_split_dma(unsigned short *sample_buffer, unsigned int sample_num, unsigned char chn_cnt, unsigned short buffers[chn_cnt][sample_num])
{
    unsigned int i, j;
    for (i = 0; i < chn_cnt; i++)
    {
        for (j = 0; j < sample_num; j++)
        {
            buffers[i][j] = sample_buffer[j * chn_cnt + i];
        }
    }
}
/**
 * @brief      This function is used to start the dma to get the adc sample code into adc_sample_buffer and split it into different channels of data.
 * @return        none.
 * @attention  When using multi-channel sampling in DMA mode, you need to make sure that the dma handling data process is not interrupted, otherwise it will result in the sampling data of the multi-channels being misordered when you come back;
 *                if there is a possibility of interruption in the process of data handling by the dma, you have to reconfigure and initialize the ADC and the DMA after coming back in order to continue to work normally.
 */
void adc_start_dma(void)
{
//    adc_get_raw_code_dma((unsigned short *)adc_sample_buffer, (ADC_SAMPLE_GROUP_CNT * ADC_SAMPLE_CHN_CNT));
//    adc_code_split_dma((unsigned short *)adc_sample_buffer, ADC_SAMPLE_GROUP_CNT, ADC_SAMPLE_CHN_CNT, channel_buffers);
}

struct PC_CMD_FUNC pc_cmd_func[] = {
    {DUTCMD_ADC_BASE_SAMPLE, adc_sample_test},
    {DUTCMD_ADC_BASE_SAMPLE_SET_PARAMETER_STAR, adc_set_parameter_start_sample_test},
    {DUTCMD_ADC_BASE_VBAT_SET_PARAMETER_STAR,adc_set_parameter_start_vbat_test},
    {DUTCMD_ADC_BASE_SAMPLE_SET_PARAMETER_COLLECT, adc_set_parameter_collect_sample_test},
    {DUTCMD_ADC_BASE_VBAT_SET_PARAMETER_COLLECT, adc_set_parameter_collect_vbat_test},
    {DUTCMD_ADC_BASE_VBAT, adc_vbat_test},
    {DUTCMD_ADC_BASE_TEMPERATURE, adc_temperature_test},
    {DUTCMD_ADC_BASE_SET_PARAMETER, adc_set_parameter},
    {DUTCMD_ADC_BASE_GET_DATA,adc_get_data_collect_test},
    {DUTCMD_ADC_BASE_MULTIPLE_VBAT,adc_multiple_vbat_test},
    {DUTCMD_ADC_BASE_MULTIPLE_SAMPLE,adc_multiple_sample_test},
    {DUTCMD_ADC_BASE_MULTIPLE_SAMPLE_PARTIAL_PRESSURE,adc_multiple_filter_partial_pressure_sample_test}
};

/**
 * @brief This function serves to sort adc sample code and get average value.
 * @param[in]   channel_sample_buffer - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @return         adc_code_average     - the average value of adc sample code.
 */
unsigned short adc_sort_and_get_average_code(unsigned short *channel_sample_buffer)
{
    int i, j;
    unsigned short adc_code_average = 0;
    unsigned short temp;

    /**** insert Sort and get average value ******/
    for (i = 1; i < ADC_SAMPLE_GROUP_CNT; i++)
    {
        if (channel_sample_buffer[i] < channel_sample_buffer[i - 1])
        {
            temp = channel_sample_buffer[i];
            channel_sample_buffer[i] = channel_sample_buffer[i - 1];
            for (j = i - 1; j >= 0 && channel_sample_buffer[j] > temp; j--)
            {
                channel_sample_buffer[j + 1] = channel_sample_buffer[j];
            }
            channel_sample_buffer[j + 1] = temp;
        }
    }
    // get average value from raw data(abandon 1/4 small and 1/4 big data)
    for (i = ADC_SAMPLE_GROUP_CNT >> 2; i < (ADC_SAMPLE_GROUP_CNT - (ADC_SAMPLE_GROUP_CNT >> 2)); i++)
    {
        adc_code_average += channel_sample_buffer[i] / (ADC_SAMPLE_GROUP_CNT >> 1);
    }
    return adc_code_average;
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
    unsigned int cnt = 0;

    if(transfer_mode==NDMA)
    {
        adc_start_sample_nodma();

        while (cnt < ADC_SAMPLE_GROUP_CNT)
        {
            int sample_cnt = adc_get_rxfifo_cnt();
            if (sample_cnt > 0)
            {
                channel_buffers[chn][cnt]= adc_get_raw_code();
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
    return code_average;
    if(result_type == ADC_VOLTAGE)
    {
        return adc_result = adc_calculate_voltage(chn, code_average);
    }
#if INTERNAL_TEST_FUNC_EN
    else if((result_type == TEMP_VALUE))
    {
        return adc_result = adc_calculate_temperature(code_average);
    }
#endif
    else
    {
        return 0;
    }
}

void adc_set_parameter(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    unsigned char cmd = para->payload[2];
    unsigned char value = para->payload[3];
    unsigned char send_data[4];
    char execute_flag = 0x66;
    adc_init_flg = 1;
    if (CMD_PRE_SCALER == cmd)
    {
        adc_gpio_cfg_m.pre_scale = value;
        chn_cfg.pre_scale  = value;
    }
    else if (CMD_VREF_VOL == cmd)
    {
        adc_gpio_cfg_m.v_ref = value;
        chn_cfg.v_ref  = value;
    }
    else if (CMD_DMA == cmd)
    {
        if (value == 1)
        {
            DMA_type = DMA;
            DMA_chanal = DMA_M_CHN;
        }
        else
        {
            DMA_type = NDMA;
            DMA_chanal = NDMA_M_CHN;
        }
    }
    else if (CMD_CLOCK == cmd)
    {
        if (23 == value)
        {
            adc_gpio_cfg_m.sample_freq = ADC_SAMPLE_FREQ_23K;
            chn_cfg.sample_freq = ADC_SAMPLE_FREQ_23K;
        }
        else if (48 == value)
        {
            adc_gpio_cfg_m.sample_freq = ADC_SAMPLE_FREQ_48K;
            chn_cfg.sample_freq = ADC_SAMPLE_FREQ_48K;
        }
        else if (96 == value)
        {
            adc_gpio_cfg_m.sample_freq = ADC_SAMPLE_FREQ_96K;
            chn_cfg.sample_freq = ADC_SAMPLE_FREQ_96K;
        }
        else if (192 == value)
        {
            adc_gpio_cfg_m.sample_freq = ADC_SAMPLE_FREQ_192K;
            chn_cfg.sample_freq = ADC_SAMPLE_FREQ_192K;
        }
    }
    else if (CMD_DIVIDER == cmd)
    {
        chn_cfg.divider = value;
    }
    else if (CMD_WRITE_ANALOG_REG == cmd)
    {
        unsigned int addr = (adc_high_addr<<8) | para->payload[4];

        analog_write_reg8(addr, value);
    }
    else if (CMD_WRITE_ANALOG_HIGH_REG == cmd)
    {
        adc_high_addr = para->payload[4];

    }
    else if (CMD_VBAT_MODE == cmd)
    {
        if (1 == value)
        {
           // platform_init(DCDC_1P4_DCDC_2P0, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M,1);
        }
        else
        {

           // platform_init(DCDC_1P4_DCDC_2P0, VBAT_MAX_VALUE_LESS_THAN_3V6, INTERNAL_CAP_XTAL24M,1);
        }
    }
    else if (CMD_SET_COLLECT_MODE == cmd)
    {
        collect_times = value;
    }
    else if (CMD_POWER_AFTER_DELAY == cmd)
    {
        poweron_after_delay = value * 10;
    }
    else if(CMD_DWA_SELECT == cmd)
    {
        cmd_dwa_select = 1;
    }
    else
    {
        execute_flag = 0xFF;
    }
    send_data[0] = para->payload[2] + 0xa5;
    send_data[1] = para->payload[3] + 0xa5;
    send_data[2] = 4;
    send_data[3] = execute_flag;
    result_buff_write(send_data, send_data[2]);
}

void adc_temperature_test(void)
{
    unsigned char send_data[4];

    if (DMA == DMA_type)
    {
        adc_set_dma_config(ADC_DMA_CHN);
    }
    adc_temp_val = adc_get_result(DMA_type, ADC_M_CHANNEL,TEMP_VALUE);

    send_data[0] = adc_temp_val & 0xff;
    send_data[1] = (adc_temp_val >> 8) & 0xff;
    send_data[2] = 4;
    send_data[3] = 0x66;
    result_buff_write(send_data, send_data[2]);
}

void adc_set_parameter_collect_sample_test(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    gpio_pin_e pin = (para->payload[2] << 8 | para->payload[3]) & 0xffff;
    adc_gpio_cfg_m.pin = pin | (para->payload[4] << 12);
    memset(collect_adc_val,0,1000);

    if (DMA == DMA_type)
    {

        adc_set_dma_config(ADC_DMA_CHN);
    }

        adc_init(DMA_chanal);
        if(cmd_dwa_select == 1)
        {
            analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
        }
        adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);



}
void adc_set_parameter_start_sample_test(void)
{

    adc_power_on();
    //        adc_get_raw_code();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.
    adc_start_sample_nodma();
    if (DMA == DMA_type)
    {
        adc_start_dma();
    }
    adc_collection_data();

    adc_power_off();
}

void adc_multiple_vbat_test(void)
{
    if(adc_init_flg)
    {
        if (DMA == DMA_type)
        {
            adc_set_dma_config(ADC_DMA_CHN);
        }

        adc_init(DMA_chanal);
        adc_chn_config(ADC_M_CHANNEL, chn_cfg);
        if(cmd_dwa_select == 1)
        {
            analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
        }
        adc_init_flg = 0;
    }
    adc_power_on();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.

    adc_start_sample_nodma();
    if (DMA == DMA_type)
    {
        adc_start_dma();
    }

    adc_collection_data();

    adc_power_off();


}

void adc_set_parameter_collect_vbat_test(void)
{

    if (DMA == DMA_type)
    {
        adc_set_dma_config(ADC_DMA_CHN);
    }

    adc_init(DMA_chanal);
    if(cmd_dwa_select == 1)
    {
        analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
    }

    adc_chn_config(ADC_M_CHANNEL, chn_cfg);


}

void adc_set_parameter_start_vbat_test(void)
{

    adc_power_on();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.
    adc_start_sample_nodma();

    if (DMA == DMA_type)
    {
        adc_start_dma();
    }

    adc_collection_data();
    adc_power_off();

}
volatile unsigned char ii = 0 ;
void adc_multiple_filter_partial_pressure_sample_test(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    gpio_pin_e pin = (para->payload[2] << 8 | para->payload[3]) & 0xffff;
    adc_gpio_cfg_m.pin = pin | (para->payload[4] << 12);


    memset(collect_adc_val,0,1000);
    gpio_function_en(GPIO_PA0);
    gpio_output_en(GPIO_PA0);
    if(adc_init_flg)
    {
        adc_init(DMA_chanal);

        adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);

        if(cmd_dwa_select == 1)
        {
            analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
        }
        adc_init_flg = 0;
    }
    else
    {
       adc_pin_config(ADC_GPIO_MODE, adc_gpio_cfg_m.pin );
       adc_set_diff_input(0, para->payload[4], GND);
    }

    adc_power_on();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.
    adc_start_sample_nodma();

#if defined(MCU_CORE_TL751X)
    int i = 0 , j = 0;
    unsigned short code_array[8] ={0};

    char flag = 1;
    while (i < collect_times*2)
    {
        int sample_cnt = adc_get_rxfifo_cnt();
        if (sample_cnt > 0)
        {

            gpio_toggle(GPIO_PE0);
           
            if( j < 8)
            {
                adc_data =  adc_get_raw_code();
                code_array[j] = adc_data & 0xffff;
                code_array[j+1] = (adc_data >> 16);
                j+=2;
            }
            if(j == 8)
            {
                adc_m_chn_val = adc_sort_and_get_average_code(code_array);
                collect_adc_val[i] = adc_m_chn_val & 0xff;
                collect_adc_val[i+1] = (adc_m_chn_val >> 8) & 0xff;
                memset(code_array,0,16);
                i+=2;
                j = 0;
            }
            if(flag)
            {
                flag--;
                j-=2;
            }

        }
    }
#elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    int i = 0 , j = 0;
    unsigned short code_array[8] ={0};
    while (i < collect_times*2)
    {
        int sample_cnt = adc_get_rxfifo_cnt();
        if (sample_cnt > 0)
        {
            ii = 9;
            gpio_toggle(GPIO_PE0);

            if( j < 8)
            {
                code_array[j] = adc_get_raw_code();
                j++;
            }
            if(j == 8)
            {
                adc_m_chn_val = adc_sort_and_get_average_code(code_array);
                collect_adc_val[i] = adc_m_chn_val & 0xff;
                collect_adc_val[i+1] = (adc_m_chn_val >> 8) & 0xff;
                i+=2;
                j = 0;
            }

        }
    }
#endif
    ii++;
    adc_power_off();

}
volatile char aaa = 0 ;
void adc_multiple_sample_test(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    gpio_pin_e pin = (para->payload[2] << 8 | para->payload[3]) & 0xffff;
    adc_gpio_cfg_m.pin = pin | (para->payload[4] << 12);;
    memset(collect_adc_val,0,1000);
    gpio_function_en(GPIO_PA0);
    gpio_output_en(GPIO_PA0);
    if(adc_init_flg)
    {
        if (DMA == DMA_type){
            adc_set_dma_config(ADC_DMA_CHN);
        }
        adc_init(DMA_chanal);
        adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);
        if(cmd_dwa_select == 1)
        {
            analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
        }
        adc_init_flg = 0;
    }
    else
    {
       adc_pin_config(ADC_GPIO_MODE, adc_gpio_cfg_m.pin );
       adc_set_diff_input(0, para->payload[4], GND);
    }

    adc_power_on();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.

    adc_start_sample_nodma();
    if (DMA == DMA_type){
        adc_start_dma();
    }
    adc_collection_data();
    adc_power_off();

}

// A maximum of 30 data can be obtained at a time
void adc_get_data_collect_test(void)
{
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    char num = para->payload[2];
    char start = para->payload[3];
    unsigned char send_data[64];
    send_data[1] = (num+1) * 2;
    memcpy(send_data+2,collect_adc_val+start,num*2);
    result_buff_write(send_data, send_data[1]);

}
//This interface is deprecated
void adc_vbat_test(void)
{

    if(adc_start_flag)
    {
        if (DMA == DMA_type)
        {
            adc_set_dma_config(ADC_DMA_CHN);
        }

        adc_init(DMA_chanal);
        adc_chn_config(ADC_M_CHANNEL, chn_cfg);
        if(cmd_dwa_select == 1)
        {
            analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
        }

        adc_power_on();
        delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.

        adc_start_sample_nodma();
        adc_start_flag = 0;
    }

    adc_collection_data();

}
//This interface is deprecated
void adc_sample_test(void)
{
    unsigned char send_data[4];
    autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
    gpio_pin_e pin = (para->payload[2] << 8 | para->payload[3]) & 0xffff;
    adc_gpio_cfg_m.pin = pin | (para->payload[4] << 12);

    if (DMA == DMA_type)
    {
        adc_set_dma_config(ADC_DMA_CHN);
    }
    adc_init(DMA_chanal);
    
    adc_gpio_sample_init(ADC_M_CHANNEL,adc_gpio_cfg_m);
    if(cmd_dwa_select == 1)
    {
        analog_write_reg8(areg_adc_data_sample_control, (analog_read_reg8(areg_adc_data_sample_control)&(~FLD_DWA_EN_O)));
    }
    adc_power_on();
    delay_us(poweron_after_delay);//Wait >30us after adc_power_on() for ADC to be stable.
    adc_start_sample_nodma();
    if (DMA == DMA_type)
    {
        adc_start_dma();
    }
    while (1)
    {
        int sample_cnt = adc_get_rxfifo_cnt();
        if (sample_cnt > 0)
        {
            gpio_toggle(GPIO_PE0);
            adc_m_chn_val= adc_get_raw_code();
            break;
        }
    }
    send_data[0] = adc_m_chn_val & 0xff;
    send_data[1] = (adc_m_chn_val >> 8) & 0xff;
    send_data[2] = 4;
    send_data[3] = 0x66;
    result_buff_write(send_data, send_data[2]);
}

void user_init(void)
{
    gpio_function_en(GPIO_PE0);
    gpio_output_en(GPIO_PE0);

    // intiate parameter buffer to receive CMD and parameter
    para_buff_init();
    // initiate result buffer to send the result
    result_buff_init();
//    analog_write_reg8(0x15, 0xf4);
//    analog_write_reg8(0x0f, 0xf4);
}


void pc_data_handle(void)
{
    unsigned char i;
    int crc_flag;
    if (para_buff_have_data() != 0)
    {
        cmd_count++;
        crc_flag = para_buff_read(para_buff, COMMAND_BUFF_SIZE); // 1:CRC correct  -1:CRC error  0:buffer size overflow
        autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
        unsigned int test_cmd = (para->payload[1] << 8 | para->payload[0]);
        cmd_display = test_cmd;
        if (crc_flag == 1)
        {
            for (i = 0; i < sizeof(pc_cmd_func) / sizeof(struct PC_CMD_FUNC); i++)
            {
                if (pc_cmd_func[i].cmd_name == test_cmd)
                {
                    correct_cmd_count++;
                    pc_cmd_func[i].func();
                    break;
                }
            }
        }
    }
}

/*********************************************************************************************************
 *                                                main loop
 *********************************************************************************************************/
void main_loop(void)
{
    while(1)
    {
        pc_data_handle();
    }
}

#endif

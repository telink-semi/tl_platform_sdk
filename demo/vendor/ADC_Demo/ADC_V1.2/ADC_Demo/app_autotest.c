/********************************************************************************************************
 * @file    app_autotest.c
 *
 * @brief   This is the source file for B91m
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
#include "driver.h"
#include "dma.h"
#if INTERNAL_TEST_FUNC_EN && (DEMO_MODE == TEST_MODE)


// set parament cmd
#define CMD_PRE_SET_NUM 0x00
#define CMD_PRE_SCALER 0x01
#define CMD_VREF_VOL 0x02
#define CMD_DMA 0x03
#define CMD_CLOCK 0x04
#define CMD_CORE_REG 0x06
#define CMD_VBAT_MODE 0x07 // modify
#define CMD_SET_COLLECT_MODE 0x08
#define CMD_DIVIDER      0x09


#define CMD_POWER_ON_AFTER_DELAY      0x0a
//#define CMD_MULTIPLE_CHNA_NUM 0x0c
#define SUB_CMD_MULTIPLE_GPIO_MODE 0x01
#define SUB_CMD_MULTIPLE_VBAT_MODE 0x02
#define CMD_ADC_NUM 0x0d

#define CMD_DWA_SELECT     0x0b
#define CMD_WRITE_CORE_REG 0x10 // This function is not implemented in the next machine and is used as a placeholder
#define CMD_MULTIPLEADC_NUM 0x11
#define CMD_WRITE_ANALOG_REG 0x20
#define CMD_WRITE_ANALOG_HIGH_REG 0x21
#define CMD_GET_DATA_ADDR  0x22

#define BUF_SIZE    2 * COMMAND_BUFF_SIZE
#define  ADC_DMA_CHN                DMA6
adc_chn_cnt_e g_adc_chanal = NDMA_M_CHN;
adc_transfer_mode_e DMA_type = NDMA;

volatile int collect_times = 100;
volatile int  adc_irq_temp_cnt = 0;
char collect_adc_val[1000];
volatile char collect_adc_val1[1000];
volatile unsigned int correct_cmd_count = 0;
volatile unsigned int cmd_count = 0;
volatile unsigned int cmd_display = 0;
volatile unsigned char adc_start_flag = 1;
volatile int adc_irq_cnt = 0;
volatile unsigned short adc_temp_val;
volatile unsigned short adc_m_chn_val;
volatile int poweron_after_delay = 90;
volatile char cmd_dwa_select = 0;
unsigned short channel_buffers[3][ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = {0};
unsigned short adc_sample_buffer[ADC_SAMPLE_GROUP_CNT * ADC_SAMPLE_CHN_CNT];
volatile unsigned char adc_high_addr = 0;
static unsigned char g_adc_vref =0;
static unsigned char g_adc_divider=0;
volatile unsigned char irq_flag = 0 ;
int multiple_chan_num =0;

char multiple_adc_chn;

adc_chn_cfg_t * adc_chn_cfg[3];

autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;

adc_chn_cfg_t adc_chn_cfg_m =
{

    .pre_scale = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_23K,
    .input_p = ADC0_GPIO_PC0P,
    .input_n = ADC_GND_N,
};


adc_chn_cfg_t adc_chn_cfg_l =
{
    .pre_scale = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_96K,
    .input_p = ADC0_GPIO_PC0P,
    .input_n = ADC_GND_N,
};
adc_chn_cfg_t adc_chn_cfg_r =
{
    .pre_scale = ADC_PRESCALE_1F4,
    .sample_freq = ADC_SAMPLE_FREQ_96K,
    .input_p = ADC0_GPIO_PC0P,
    .input_n = ADC_GND_N,
};

adc_chn_cfg_t* adc_gpio_multiple_config[2] ={&adc_chn_cfg_l,&adc_chn_cfg_r};

void adc_start_vbat_test(void);
void adc_sample_init_test(void);
void adc_set_parameter_collect_sample_test(void);
void adc_start_sample_test(void);
void adc_vbat_test(void);
void adc_set_parameter(void);
void adc_sample_test(void);
void adc_get_data_collect_test(void);

void adc_dma_complete_inquiry(void);
void adc_multiple_init_test(void);
void adc_multiple_start_test(void);


#if !defined(MCU_CORE_TL322X)
void adc_chn_config(adc_num_e adc_num,adc_sample_chn_e chn , adc_chn_cfg_t adc_cfg);
//unsigned short adc_get_result(adc_transfer_mode_e transfer_mode, adc_sample_chn_e chn);
short adc_get_result(adc_num_e sar_adc_num,adc_transfer_mode_e transfer_mode,adc_sample_chn_e chn,adc_input_pch_e input_p);
#else
adc_num_e adc_num = ADC0;


#endif

struct PC_CMD_FUNC
{
    unsigned short cmd_name;
    void (*func)(void);
};

void adc_collection_data(void)
{
    memset(collect_adc_val, 0, sizeof(collect_adc_val));
    int i = 0;
    while (i < collect_times*2)
    {
        int sample_cnt = adc_get_rxfifo_cnt(adc_num);
        if (sample_cnt > 0)
        {
            gpio_toggle(GPIO_PE0);
            adc_m_chn_val= adc_get_raw_code(adc_num);
            collect_adc_val[i] = adc_m_chn_val & 0xff;
            collect_adc_val[i+1] = (adc_m_chn_val >> 8) & 0xff;
            i+=2 ;
        }
    }
}

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
    {DUTCMD_ADC_BASE_SAMPLE_STAR, adc_start_sample_test},
    {DUTCMD_ADC_BASE_SAMPLE_INIT_TEST,adc_sample_init_test},
    {DUTCMD_ADC_BASE_SET_PARAMETER, adc_set_parameter},
    {DUTCMD_ADC_BASE_GET_DATA,adc_get_data_collect_test},
    {DUTCMD_ADC_BASE_SAMPLE,adc_sample_test},
    {DUTCMD_ADC_BASE_VBAT, adc_vbat_test},
    {DUTCMD_ADC_BASE_MULTIPLE_START, adc_multiple_start_test},
    {DUTCMD_ADC_BASE_MULTIPLE_INIT, adc_multiple_init_test},
    
    {DUTCMD_ADC_BASE_DMA_COMPLETE_INQUIRY, adc_dma_complete_inquiry},
};

uint16_t crc16(unsigned char *data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ 0x8408;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void package(unsigned char *data, unsigned char length) {
    if (length > BUF_SIZE-5) {
        printf("The data length exceeds the maximum limit (59 bytes)\n");
        return;
    }

    command_buff[BUF_SIZE] = 0xAA;
    command_buff[BUF_SIZE + 1] = length;
    memcpy(&command_buff[BUF_SIZE + 2], data, length);  

    uint16_t crc = crc16(data, length);
    command_buff[BUF_SIZE*2-3] = (unsigned char)(crc >> 8);  
    command_buff[BUF_SIZE*2-2] = (unsigned char)(crc & 0xFF); 

    command_buff[BUF_SIZE*2-1] = 0x55;
}
int send_data(unsigned char * data,unsigned char length)
{
    for(int i = 0 ; i < 48000000 ; i++)
    {
        if (command_buff[BUF_SIZE*2-1] == 0x00)
        {
            package(data, length);
            return  1;
        }

    }
    return -1;
}


int unpack(void) {

    if (command_buff[0] != 0xAA || command_buff[BUF_SIZE-1] != 0x55) {

        return -1; 

    }
    unsigned char length = command_buff[1];
    if (length > BUF_SIZE-5) {
        return -2;
    }
    uint16_t received_crc = (command_buff[BUF_SIZE-3] << 8) | command_buff[BUF_SIZE-2];
    uint16_t computed_crc = crc16(&command_buff[2], length);
    if (received_crc != computed_crc) {
        return -3; 
    }
    para = (autotest_package_t_ptr)&command_buff[2];
    unsigned int test_cmd = (para->payload[1] << 8 | para->payload[0]);

    for (unsigned char i = 0; i < sizeof(pc_cmd_func) / sizeof(struct PC_CMD_FUNC); i++)
    {
        if (pc_cmd_func[i].cmd_name == test_cmd)
        {
            correct_cmd_count++;
            pc_cmd_func[i].func();
            break;
        }
    }
    command_buff[BUF_SIZE-1] = 0x00;

    printf("%02x",command_buff[BUF_SIZE-1]);

    return length; 
}

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


void adc_send_data_addr(void)
{
    unsigned int addr =  (unsigned int)collect_adc_val;
    unsigned char data[5];
    data[0] = CMD_GET_DATA_ADDR;
    data[1] = (unsigned char)(addr & 0xFF);      
    data[2] = (unsigned char)((addr >> 8) & 0xFF);  
    data[3] = (unsigned char)((addr >> 16) & 0xFF);
    data[4] = (unsigned char)((addr >> 24) & 0xFF);
    send_data(data, 5);
}
void adc_set_parameter(void)
{

    unsigned char cmd = para->payload[2];
    unsigned char value = para->payload[3];
    unsigned char send_data[4];
    char execute_flag = 0x66;
    char circul_num = 1 ;
    if (CMD_PRE_SET_NUM == cmd)
    {
        circul_num = value;
    }

    for(char index = 0; index < circul_num; index++ )
    {
        if(circul_num != 1)
        {
            cmd = para->payload[4 + index*2];
            value = para->payload[5 + index*2];
        }

        switch (cmd)
        {
            case CMD_PRE_SCALER:
                adc_chn_cfg[multiple_chan_num]->pre_scale = value;
                break;

            case CMD_VREF_VOL:
                g_adc_vref = value;
                break;

            case CMD_MULTIPLEADC_NUM:
                multiple_chan_num = value;
                break;

            case CMD_DMA:
                if (value == 1)
                {
                    DMA_type = DMA;
                    g_adc_chanal = DMA_M_CHN;
                }
                else
                {
                    DMA_type = NDMA;
                    g_adc_chanal = NDMA_M_CHN;
                }
                break;

            case CMD_CLOCK:
                switch (value)
                {
                    case 23:
                        adc_chn_cfg[multiple_chan_num]->sample_freq = ADC_SAMPLE_FREQ_23K;
                        break;
                    case 48:
                        adc_chn_cfg[multiple_chan_num]->sample_freq = ADC_SAMPLE_FREQ_48K;
                        break;
                    case 96:
                        adc_chn_cfg[multiple_chan_num]->sample_freq = ADC_SAMPLE_FREQ_96K;
                        break;
                    case 192:
                        adc_chn_cfg[multiple_chan_num]->sample_freq = ADC_SAMPLE_FREQ_192K;
                        break;
                    case 2:
                        adc_chn_cfg[multiple_chan_num]->sample_freq  = ADC_SAMPLE_FREQ_2M;

                        break;
                    case 1:
                        adc_chn_cfg[multiple_chan_num]->sample_freq  = ADC_SAMPLE_FREQ_1M;
                        break;
                    default:
                        break;
                }
                break;

            case CMD_DIVIDER:
                g_adc_divider = value;
                break;

            case CMD_WRITE_ANALOG_REG:
                {
                    unsigned int addr = (adc_high_addr << 8) | para->payload[4];
                    analog_write_reg8(addr, value);
                }
                break;

            case CMD_WRITE_ANALOG_HIGH_REG:
                adc_high_addr = para->payload[4];
                break;


            case CMD_SET_COLLECT_MODE:
                collect_times = value * 10;
                break;

            case CMD_POWER_ON_AFTER_DELAY:
                poweron_after_delay = value * 10;
                break;

            case CMD_DWA_SELECT:
                cmd_dwa_select = 1;
                break;

            case CMD_GET_DATA_ADDR:
                adc_send_data_addr();
                break;

            case CMD_ADC_NUM:
                adc_num = value;
                break;
            default:
                execute_flag = 0xFF;
                break;
        }

    }
    send_data[0] = para->payload[2] + 0xa5;
    send_data[1] = para->payload[3] + 0xa5;
    send_data[2] = 4;
    send_data[3] = execute_flag;
    result_buff_write(send_data, send_data[2]);
}


void adc_set_parameter_collect_sample_test(void)
{
    gpio_shutdown(GPIO_ALL);
    adc_chn_cfg[multiple_chan_num]->input_p = para->payload[2] | (para->payload[3] << 8);
    adc_chn_cfg[multiple_chan_num]->input_n = para->payload[4] | (para->payload[5] << 8);

    memset(collect_adc_val,0,1000);

    if (DMA == DMA_type)
    {
        adc_set_dma_config(adc_num,ADC_DMA_CHN);
    }

    adc_init(adc_num, g_adc_chanal);

    adc_channel_sample_init(adc_num,ADC_GPIO_MODE, ADC_M_CHANNEL,&adc_chn_cfg_m);
    unsigned char offset = (ADC_M_CHANNEL == 0) ? 0 : (1 << ADC_M_CHANNEL);
    reg_adc_channel_set_state(adc_num,ADC_M_CHANNEL) = (reg_adc_channel_set_state(adc_num,ADC_M_CHANNEL)&(~FLD_SEL_VREF)) | (g_adc_vref<<6);
    reg_adc_vabt_div(adc_num) = (reg_adc_vabt_div(adc_num) & (~BIT_RNG(offset,offset+1)))| ((g_adc_divider) << offset);

}
void adc_start_vbat_test(void)
{

    adc_power_on(adc_num);
    //        adc_get_raw_code(adc_num);

    adc_start_sample_nodma(adc_num);
    if (DMA == DMA_type)
    {
        adc_start_dma();
    }
    adc_collection_data();

    adc_power_off(adc_num);
}

void adc_vbat_test(void)
{
    gpio_shutdown(GPIO_ALL);

    adc_chn_cfg[multiple_chan_num]->input_n = para->payload[3]>>4;
    adc_chn_cfg[multiple_chan_num]->input_p = ADC_VBAT_P;

    switch (adc_chn_cfg[multiple_chan_num]->input_n)
    {
        case ADC1_GPIO_PB0N:
            adc_pin_config(GPIO_PB0);
            break;
        case ADC1_GPIO_PB1N:
            adc_pin_config(GPIO_PB1);
            break;
        case ADC1_GPIO_PB2N:
            adc_pin_config(GPIO_PB2);
            break;
        case ADC1_GPIO_PB3N:
            adc_pin_config(GPIO_PB3);
            break;
        case ADC1_GPIO_PB4N:
            adc_pin_config(GPIO_PB4);
            break;
        case ADC1_GPIO_PB5N:
            adc_pin_config(GPIO_PB5);
            break;
        case ADC1_GPIO_PB6N:
            adc_pin_config(GPIO_PB6);
            break;
        case ADC1_GPIO_PB7N:
            adc_pin_config(GPIO_PB7);
            break;
        case ADC0_GPIO_PC0N:
             adc_pin_config(GPIO_PC0);
            break;
        case ADC0_GPIO_PC1N:
            adc_pin_config(GPIO_PC1);
            break;
        case ADC0_GPIO_PC2N:
            adc_pin_config(GPIO_PC2);
            break;
        case ADC0_GPIO_PC3N:
            adc_pin_config(GPIO_PC3);
            break;
        case ADC0_GPIO_PC4N:
            adc_pin_config(GPIO_PC4);
            break;
        case ADC0_GPIO_PC5N:
            adc_pin_config(GPIO_PC5);
            break;
        case ADC0_GPIO_PC6N:
            adc_pin_config(GPIO_PC6);
            break;
        case ADC0_GPIO_PC7N:
            adc_pin_config(GPIO_PC7);
            break;
        default:
            break;

    }
    if (DMA == DMA_type)
    {
        adc_set_dma_config(adc_num,ADC_DMA_CHN);
    }

    adc_init(adc_num, g_adc_chanal);


    adc_channel_sample_init(adc_num,ADC_VBAT_MODE, ADC_M_CHANNEL,&adc_chn_cfg_m);
    adc_power_on(adc_num);


    adc_start_sample_nodma(adc_num);
    if (DMA == DMA_type)
    {
        adc_start_dma();
    }

    adc_collection_data();

    adc_power_off(adc_num);


}

_attribute_ram_code_sec_ void dma_irq_handler(void)
{
    if (dma_get_tc_irq_status(BIT(ADC_DMA_CHN))) {

        irq_flag = 1;
        /******clear adc sample finished status********/
        adc_clr_irq_status_dma(adc_num);
        /******get adc sample data and sort these data ********/

    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
void adc_multiple_start_test(void)
{
    adc_power_on(adc_num);
    irq_flag = 0;
    adc_start_sample_dma(adc_num,(short *)collect_adc_val, collect_times*2*(multiple_adc_chn+1));
}

void adc_multiple_init_test(void)
{
    multiple_adc_chn =  para->payload[2];

    adc_set_dma_config(adc_num,ADC_DMA_CHN);
    dma_set_irq_mask(ADC_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    if(multiple_adc_chn == 1){
        adc_init(adc_num, DMA_M_CHN);
    }
    else if (multiple_adc_chn == 2){
        adc_init(adc_num, DMA_M_L_CHN);
    }
    else if(multiple_adc_chn == 3){
        adc_init(adc_num, DMA_M_L_R_CHN);
    }

//    adc_chn_config(adc_num, ADC_M_CHANNEL, adc_chn_cfg_m);
//
//    if (multiple_adc_chn > 1){
//        adc_chn_config(adc_num, ADC_M_CHANNEL, adc_chn_cfg_l);
//    }
//    if(multiple_adc_chn > 2){
//        adc_chn_config(adc_num, ADC_M_CHANNEL, adc_chn_cfg_r);
//    }
}
void adc_dma_complete_inquiry(void)
{
    unsigned char data[3];

    data[0] = (unsigned char)(DUTCMD_ADC_BASE_DMA_COMPLETE_INQUIRY & 0xFF);
    data[1] = (unsigned char)((DUTCMD_ADC_BASE_DMA_COMPLETE_INQUIRY >> 8) & 0xFF);
    data[2] = irq_flag;
    send_data(data, 3);
    adc_power_off(adc_num);
}
void adc_start_sample_test(void)
{
    adc_power_on(adc_num);
    adc_start_sample_nodma(adc_num);

    adc_collection_data();
    adc_power_off(adc_num);


}
void adc_sample_init_test(void)
{

        gpio_shutdown(GPIO_ALL);
        adc_chn_cfg[multiple_chan_num]->input_p = para->payload[2] | (para->payload[3] << 8);
        adc_chn_cfg[multiple_chan_num]->input_n = para->payload[4] | (para->payload[5] << 8);

        memset(collect_adc_val,0,1000);


        if (DMA == DMA_type){
            adc_set_dma_config(adc_num,ADC_DMA_CHN);
        }
        adc_init(adc_num, g_adc_chanal);
        adc_channel_sample_init(adc_num,ADC_GPIO_MODE, ADC_M_CHANNEL,&adc_chn_cfg_m);
        unsigned char offset = (ADC_M_CHANNEL == 0) ? 0 : (1 << ADC_M_CHANNEL);
        reg_adc_channel_set_state(adc_num,ADC_M_CHANNEL) = (reg_adc_channel_set_state(adc_num,ADC_M_CHANNEL)&(~FLD_SEL_VREF)) | (g_adc_vref<<6);
        reg_adc_vabt_div(adc_num) = (reg_adc_vabt_div(adc_num) & (~BIT_RNG(offset,offset+1)))| ((g_adc_divider) << offset);

}
volatile unsigned char ii = 0 ;
void adc_sample_test(void)
{
    gpio_shutdown(GPIO_ALL);
    adc_chn_cfg[multiple_chan_num]->input_p = para->payload[2] | (para->payload[3] << 8);
    adc_chn_cfg[multiple_chan_num]->input_n = para->payload[4] | (para->payload[5] << 8);

    memset(collect_adc_val,0,1000);

    adc_init( adc_num, g_adc_chanal);
    adc_channel_sample_init(adc_num,ADC_GPIO_MODE, ADC_M_CHANNEL,&adc_chn_cfg_m);
    unsigned char offset = (ADC_M_CHANNEL == 0) ? 0 : (1 << ADC_M_CHANNEL);
    reg_adc_channel_set_state(adc_num,g_adc_chanal) = (reg_adc_channel_set_state(adc_num,g_adc_chanal)&(~FLD_SEL_VREF)) | (g_adc_vref<<6);
    reg_adc_vabt_div(adc_num) = (reg_adc_vabt_div(adc_num) & (~BIT_RNG(offset,offset+1)))| ((g_adc_divider) << offset);

    adc_power_on(adc_num);


    adc_start_sample_nodma(adc_num);
    if (DMA == DMA_type){
        adc_start_dma();
    }
    adc_collection_data();
    adc_power_off(adc_num);

}

// A maximum of 30 data can be obtained at a time
void adc_get_data_collect_test(void)
{

    char num = para->payload[2];
    char start = para->payload[3];
    unsigned char send_data[64];
    send_data[1] = (num+1) * 2;
    memcpy(send_data+2,collect_adc_val+start,num*2);
    result_buff_write(send_data, send_data[1]);

}


void user_init(void)
{
    gpio_function_en(GPIO_PE0);
    gpio_output_en(GPIO_PE0);

    // intiate parameter buffer to receive CMD and parameter
    para_buff_init();
    // initiate result buffer to send the result
    result_buff_init();

    write_sram8(PARA_BUF_WPTR, 0xff);
    adc_chn_cfg[multiple_chan_num] = &adc_chn_cfg_m;
    adc_chn_cfg[1] = &adc_chn_cfg_l;
    adc_chn_cfg[2] = &adc_chn_cfg_r;

}



void pc_data_handle(void)
{
    unsigned char i;
    int crc_flag;
    if (para_buff_have_data() != 0)
    {
        cmd_count++;
        crc_flag = para_buff_read(para_buff, COMMAND_BUFF_SIZE); // 1:CRC correct  -1:CRC error  0:buffer size overflow
        para = (autotest_package_t_ptr)para_buff;
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
volatile unsigned int return_v;


void main_loop(void)
{

    unsigned char data[BUF_SIZE-5] = {97, 13, 0, 95, 0, 16, 96, 43, 86, 15, 93, 13, 0, 76, 70, 96, 40, 57, 54, 97, 70, 5, 58, 41, 75, 30, 73, 54, 64, 38, 70, 71, 4, 63, 44, 27, 94, 1, 22, 90, 4, 49, 5, 90, 14, 100, 24, 39, 25, 28, 100, 36, 56, 60, 0, 49, 32, 61, 98, 26, 14, 19, 15, 56, 93, 28, 49, 8, 22, 82, 61, 82, 77, 69, 91, 10, 45, 1, 86, 70, 18, 71, 29, 23, 93, 29, 6, 58, 73, 50, 38, 32, 10, 42, 6, 91, 70, 71, 39, 50, 79, 2, 86, 60, 63, 78, 100, 37, 82, 16, 3, 68, 75, 45, 35, 44, 20, 65, 17, 5, 0, 54, 70};
    send_data(data, BUF_SIZE-5);

#if COMMUNICATION_PROTOCOL == TEST_COMMUNICATION_PROTOCOL
    while(1)
    {
        return_v = unpack();
    }

#else
    {
        while(1)
        {
            pc_data_handle();
        }
    }
#endif

}

#endif

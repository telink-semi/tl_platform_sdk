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
#include "app_config.h"
/*
 *                            User configuration
 * AUTO_TEST_EN define as 0: Demo mode,  define as 1: internal auto test mode.
 * AUTO_TEST_EN can be enabled only during local debugging, not during upload.
 * test_cmd use to select the sub-test mode, the value select from dut_cmd_func[].cmd_name
 */
#define  AUTO_TEST_EN   0


volatile unsigned int test_cmd = 0;

unsigned char analog_write_byte_test(void);
unsigned char analog_write_halfword_test(void);
unsigned char analog_write_word_test(void);
unsigned char analog_write_buff_test(void);
#if defined(MCU_CORE_B91)||defined(MCU_CORE_B92)
#if (ANALOG_DMA == 1)
unsigned char analog_write_word_dma_test(void);
unsigned char analog_write_buff_dma_test(void);
unsigned char analog_write_addr_data_dma_test(void);
#endif
#endif

struct DUT_CMD_FUNC {
    unsigned int    cmd_name;
    unsigned char   (*func)(void);
};

struct DUT_CMD_FUNC dut_cmd_func[] = {
        {DUTCMD_ANALOG_BYTE_WRITE,   analog_write_byte_test},
        {DUTCMD_ANALOG_HALFWORD_WRITE,  analog_write_halfword_test},
        {DUTCMD_ANALOG_WORD_WRITE,  analog_write_word_test},
        {DUTCMD_ANALOG_BUFF_WRITE,  analog_write_buff_test},
#if defined(MCU_CORE_B91)||defined(MCU_CORE_B92)
#if (ANALOG_DMA == 1)
        {DUTCMD_ANALOG_WORD_DMA_WRITE,  analog_write_word_dma_test},
        {DUTCMD_ANALOG_BUFF_DMA_WRITE,  analog_write_buff_dma_test},
        {DUTCMD_ANALOG_ADDR_DATA_WRITE, analog_write_addr_data_dma_test},
#endif
#endif
};

unsigned char normal_tx_buffer[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
unsigned char normal_rx_buffer[8] = {0x00};
unsigned char normal_rx_buffer1[8] = {0x00};
unsigned short normal_rx_hword[2] = {0x0000};
unsigned int normal_rx_word  __attribute__((aligned(4)))= 0x00000000;

unsigned int var_dma_tx_word[1] = {0xaabbccdd};
unsigned int var_dma_rx_word[1] = {0x0};

unsigned char var_dma_write_addr_data[8] __attribute__((aligned(4))) = {0x39, 0xbb, 0x3a, 0xcc, 0x3b, 0xdd, 0x3c, 0xee};

volatile unsigned short NN;

unsigned char test_result = 0;

unsigned char analog_write_byte_test(void)
{
    unsigned char write_data[4] = {0x11, 0x22, 0x33, 0x44};
    analog_write_reg8(PM_ANA_REG_WD_CLR_BUF0, write_data[0]);
    analog_write_reg8(PM_ANA_REG_WD_CLR_BUF0+1, write_data[1]);
    analog_write_reg8(PM_ANA_REG_WD_CLR_BUF0+2, write_data[2]);
    analog_write_reg8(PM_ANA_REG_WD_CLR_BUF0+3, write_data[3]);

    normal_rx_buffer[0] = analog_read_reg8(PM_ANA_REG_WD_CLR_BUF0);
    normal_rx_buffer[1] = analog_read_reg8(PM_ANA_REG_WD_CLR_BUF0+1);
    normal_rx_buffer[2] = analog_read_reg8(PM_ANA_REG_WD_CLR_BUF0+2);
    normal_rx_buffer[3] = analog_read_reg8(PM_ANA_REG_WD_CLR_BUF0+3);

    if(memcmp((const void *)write_data, (const void *)normal_rx_buffer, 4))
    {
        return 0;
    }
    return 1;
}

unsigned char analog_write_halfword_test(void)
{
    unsigned short write_data[2] = {0xccdd, 0xeeff};
    analog_write_reg16(PM_ANA_REG_WD_CLR_BUF0, write_data[0]);
    analog_write_reg16(PM_ANA_REG_WD_CLR_BUF0+2, write_data[1]);

    normal_rx_hword[0] = analog_read_reg16(PM_ANA_REG_WD_CLR_BUF0);
    normal_rx_hword[1] = analog_read_reg16(PM_ANA_REG_WD_CLR_BUF0+2);

    if(memcmp((unsigned char *)write_data, (unsigned char *)&normal_rx_hword, 4))
    {
        return 0;
    }
    return 1;
}

unsigned char analog_write_word_test(void)
{
    unsigned int write_data = 0xaabbccdd;
    analog_write_reg32(PM_ANA_REG_WD_CLR_BUF0, write_data);

    normal_rx_word=analog_read_reg32(PM_ANA_REG_WD_CLR_BUF0);

    if(memcmp((unsigned char *)&write_data, (unsigned char *)&normal_rx_word, 4))
    {
        return 0;
    }
    return 1;
}

unsigned char analog_write_buff_test(void)
{
    analog_write_buff(PM_ANA_REG_WD_CLR_BUF0, (unsigned char *)normal_tx_buffer, 8);
    analog_read_buff(PM_ANA_REG_WD_CLR_BUF0, (unsigned char *)normal_rx_buffer1, 8);

    if(memcmp((unsigned char *)normal_tx_buffer, (unsigned char *)normal_rx_buffer1, 8))
    {
        return 0;
    }
    return 1;
}

#if defined(MCU_CORE_B91)||defined(MCU_CORE_B92)
#if (ANALOG_DMA == 1)
unsigned char analog_write_word_dma_test(void)
{
    analog_write_reg32_dma(DMA0, 0x38, (unsigned int *)var_dma_tx_word);
    analog_read_reg32_dma(DMA0, 0x38, (unsigned int *)var_dma_rx_word);

    if(memcmp((unsigned int *)var_dma_tx_word, (unsigned int *)var_dma_rx_word, 1))
    {
        return 0;
    }
    return 1;
}

unsigned char analog_write_buff_dma_test(void)
{
    analog_write_buff_dma(DMA0, 0x39, (unsigned char*)normal_tx_buffer, 4);
    analog_read_buff_dma(DMA0, 0x39, (unsigned char*)normal_rx_buffer, 4);
    if(memcmp((unsigned char *)normal_tx_buffer, (unsigned char *)normal_rx_buffer, 4))
    {
        return 0;
    }
    return 1;
}

unsigned char analog_write_addr_data_dma_test(void)
{
    unsigned int write_data = 0xeeddccbb;
    analog_write_addr_data_dma(DMA0, (unsigned char*)var_dma_write_addr_data, 8);
    normal_rx_word=analog_read_reg32(0x39);

    if(memcmp((unsigned char *)&write_data, (unsigned char *)&normal_rx_word, 4))
    {
        return 0;
    }
    return 1;
}
#endif
#endif

void user_init(void)
{
#if(AUTO_TEST_EN)
    //1.initiate parameter buffer to receive CMD and parameter
    para_buff_init();
    //2.initiate result buffer to send the result
    result_buff_init();
#else
    gpio_function_en(LED1 | LED2);
    gpio_output_en(LED1 | LED2);
    gpio_set_low_level(LED1 | LED2);

    test_result = analog_write_byte_test();
    if(test_result == 0)
    {
        while(1){}
    }
    test_result = analog_write_halfword_test();
    if(test_result == 0)
    {
        while(1){}
    }
    test_result = analog_write_word_test();
    if(test_result == 0)
    {
        while(1){}
    }
    test_result = analog_write_buff_test();
    if(test_result == 0)
    {
        while(1){}
    }
#endif
}

void main_loop(void)
{
    while(1)
    {
#if(AUTO_TEST_EN)
        int crc_flag;
        if(para_buff_have_data() != 0)
        {
            crc_flag = para_buff_read(para_buff,COMMAND_BUFF_SIZE); // 1:CRC correct  -1:CRC error  0:buffer size overflow
            autotest_package_t_ptr para = (autotest_package_t_ptr)para_buff;
            test_cmd = (para->payload[1]<<8 | para->payload[0]);
            if(crc_flag == 1){
                for (unsigned int i=0; i<sizeof (dut_cmd_func)/sizeof (struct DUT_CMD_FUNC); i++)
                {
                    if (dut_cmd_func[i].cmd_name == test_cmd)
                    {
                        test_result = dut_cmd_func[i].func();
                        result_buff_write(&test_result, 1);
                        break;
                    }
                }
            }
        }
#else
        gpio_toggle(LED1 | LED2);
        delay_ms(500);
#endif
    }
}

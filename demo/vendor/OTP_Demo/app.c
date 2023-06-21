/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for B91m
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
#include "otp.h"

unsigned char write_buff[16] = {0x11, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
unsigned char read_buff[16] = {0};
unsigned char read_init_margin_buff[16] = {0};
unsigned char read_pgm_margin_buff[16] = {0};

void user_init()
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);

    otp_set_active_mode();

#if (OTP_TEST_MODE == OTP_TEST_BASE_READ_WRITE)
    /* this test will write full otp space 256 * 32 = 8K Bit except for 0 word(for die function definition) */
    unsigned int write_data = 0x5a5a5a5a;
    unsigned int read_data = 0xa5a5a5a5;
    for (unsigned int j = 1; j < 256; j++)
    {
        /* 1、write */
        otp_write(j * 4, 1, (unsigned int *)&write_data);
        /* 2、read */
        read_data = 0xa5a5a5a5;
        otp_read(j * 4, 1, (unsigned int *)&read_data);
        /* 3、check */
        if (write_data != read_data)
        {
            gpio_toggle(LED2);
            return;
        }
    }
#elif (OTP_TEST_MODE == OTP_TEST_8K_SIZE)
    unsigned int write_data = 0x5a5a5a5a;
    unsigned int read_data = 0xa5a5a5a5;
    /* 1、write */
    otp_write(1024 + 32, 1, (unsigned int *)&write_data);
    /* 2、read */
    otp_read(32, 1, (unsigned int *)&read_data);
    /* 3、check */
    if (write_data != read_data)
    {
        gpio_toggle(LED2);
    }
#elif (OTP_TEST_MODE == OTP_TEST_AUTO_LOAD)
    /* first power up/hardware reset/deep/deep retention can trigger autoload */
    int auto_load_data = 0;

    /* 1、write data for test */
    unsigned int write_data = ~(BIT(10)); /* bit10 is reserved */
    otp_write(0, 1, (unsigned int *)&write_data);

    /* hardware reset and wait auto load done */
    while (reg_otp_status & FLD_OTP_AUTO_EN_BUSY);

    /* 2、read auto load register data */
    auto_load_data = reg_otp_auto_load_dat;

    /* 3、check */
    if (auto_load_data & BIT(10))
    {
        gpio_toggle(LED2);
    }
#elif (OTP_TEST_MODE == OTP_TEST_MANUAL_MODE)
    /* 1、write data */
    otp_write(32, 4, (unsigned int *)write_buff);
    /* 2、set manual mode */
    otp_manual_mode();
    /* 3、read data */
    otp_read(32, 4, (unsigned int *)read_buff);
    /* 4、check */
    for (unsigned int i = 0; i < sizeof(read_buff); i++)
    {
        if (write_buff[i] != read_buff[i])
        {
            gpio_toggle(LED2);
            break;
        }
    }
#elif (OTP_TEST_MODE == OTP_TEST_KEY_LOCK)
    /* when key lock OTP 1-8 word can't be read and it's data is 0 word data */

    /* 1、enable die key lock */
    unsigned int write_data = ~(1 << 18);
    otp_write(0, 1, (unsigned int *)&write_data);

    /* hardware reset to trigger auto load */

    /* 2、key lock */
    otp_key_lock();

    /* 3、read otp word 0 data to check */
    unsigned int read_data;
    otp_read(0, 1, (unsigned int *)&read_data);

    /* 4、read otp word 1-4 data and check */
    memset(read_buff, 0x5a, sizeof(read_buff));
    otp_read(4, 4, (unsigned int *)read_buff);
    for (char i = 0; i < sizeof(read_buff); i += 4)
    {
        /* word 1-4 can't be read */
        if (*(unsigned int *)&read_buff[0] != read_data)
        {
            gpio_toggle(LED2);
            break;
        }
    }

    /* 5、read otp word 5-8 and check */
    memset(read_buff, 0x5a, sizeof(read_buff));
    otp_read(20, 4, (unsigned int *)read_buff);
    for (char i = 0; i < sizeof(read_buff); i += 4)
    {
        /* word 5-8 can't be read */
        if (*(unsigned int *)&read_buff[0] != read_data)
        {
            gpio_toggle(LED3);
            break;
        }
    }

    /* 6、read otp word 9-12 and check to ensure key lock size */
    memset(read_buff, 0x5a, sizeof(read_buff));
    otp_read(36, 4, (unsigned int *)read_buff);
    for (char i = 0; i < sizeof(read_buff); i += 4)
    {
        /* word 9-12 can be read */
        if (*(unsigned int *)&read_buff[0] == read_data)
        {
            gpio_toggle(LED4);
            break;
        }
    }
#elif (OTP_TEST_MODE == OTP_TEST_MARGIN_READ)
    /* 1、write data */
    otp_write(32, 4, (unsigned int *)write_buff);
    /* 2、init margin read and check */
    otp_initial_margin_read(32, 4, (unsigned int *)read_init_margin_buff);
    for (unsigned int i = 0; i < sizeof(read_buff); i++)
    {
        if (write_buff[i] != read_init_margin_buff[i])
        {
            gpio_toggle(LED2);
            break;
        }
    }
    /* 3、pgm margin read and check */
    otp_pgm_margin_read(32, 4, (unsigned int *)read_pgm_margin_buff);
    for (unsigned int i = 0; i < sizeof(read_buff); i++)
    {
        if (write_buff[i] != read_pgm_margin_buff[i])
        {
            gpio_toggle(LED3);
            break;
        }
    }
#elif (OTP_TEST_MODE == OTP_TEST_SHUTDOWN)
    /* TODO FPGA can't test */
#elif (OTP_TEST_MODE == OTP_TEST_ROW)
    /* TODO FPGA can't test */
#elif (OTP_TEST_MODE == OTP_TEST_COLUMN)
    /* TODO FPGA can't test */
#endif
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(50);
}

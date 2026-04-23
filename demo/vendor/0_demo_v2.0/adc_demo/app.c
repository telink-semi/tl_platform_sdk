/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
/**************************** include header *********************************/
#include <stdio.h>
#include <string.h>
#include "inc/drv_cpr.h"
#include "inc/drv_pmu.h"
#include "modules/drv_gpio.h"
#include "inc/drv_uart.h"
#include "hal/hal_adc.h"
#include "inc/drv_delay.h"
#include "common.h"
#include "hal/hal_clock.h"

#define ADC_SAMPLE_GROUP_CNT 8

uart_handle_t log_uart;
uint32_t adc_raw_data[ADC_SAMPLE_GROUP_CNT] __attribute__((aligned(4))) = { 0 };

/**
 *   sample_freq             = apb_clk / ipclk_div /mclk_div
 *   example: 24K            = 24M     /    10     / 100
 *   the api clock_get_apb_freq() can get the apb_clk
 *   It is recommended to set the sampling rate below 48K by using the ipclk_div and mclk_div parameters.
 */
adc_cfg_t adc_cfg = {
    .ipclk_div = 10,
    .mclk_div = 100,
    .chn = AD6, /* AD0 ~AD11 for GPIO mode, VBATTERY for VBAT mode */
};

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&log_uart, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
{
    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    log_uart.instance = UART1;
    log_uart.init.baudrate = 500000;
    log_uart.init.hwflowctl = UART_HWCONTROL_NONE;
    log_uart.init.parity = UART_PARITY_NONE;
    log_uart.init.stopbits = UART_STOPBITS_1;
    log_uart.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&log_uart);
}

/**
 * @brief This function serves to sort adc sample code and get average value.
 * @param[in]   adc_raw_data_buf - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 *              and the actual buffer size defined by the user needs to be not smaller than the sample_num, otherwise there may be an out-of-bounds problem.
 * @return      adc_code_average    - the average value of adc sample code.
 */
uint32_t adc_sort_and_get_average_code(uint32_t *adc_raw_data_buf)
{
    int            i, j;
    uint32_t adc_code_average = 0;
    uint32_t temp;
    adc_raw_data_buf[0] = adc_raw_data_buf[0] & 0x3ff;   // low 10 bit is the valid code
    /**** insert Sort and get average value ******/
    for (i = 1; i < ADC_SAMPLE_GROUP_CNT; i++) {
        adc_raw_data_buf[i] = adc_raw_data_buf[i] & 0x3ff;   // low 10 bit is the valid code
        if (adc_raw_data_buf[i] < adc_raw_data_buf[i - 1]) {
            temp                     = adc_raw_data_buf[i];
            adc_raw_data_buf[i] = adc_raw_data_buf[i - 1];
            for (j = i - 1; j >= 0 && adc_raw_data_buf[j] > temp; j--) {
                adc_raw_data_buf[j + 1] = adc_raw_data_buf[j];
            }
            adc_raw_data_buf[j + 1] = temp;
        }
    }
    // Calculate the average value of the middle 50% of the data (excluding the first and last 25% respectively)
    const int drop_cnt = ADC_SAMPLE_GROUP_CNT >> 2;      // drop num（25%）
    const int use_cnt  = ADC_SAMPLE_GROUP_CNT - 2 * drop_cnt; // use num（50%）
    uint32_t total = 0;
    for (i = drop_cnt; i < drop_cnt + use_cnt; i++) {
        total += adc_raw_data_buf[i];
    }
    //Round to the nearest whole number (optional)
    adc_code_average = (total + use_cnt / 2) / use_cnt;
    return adc_code_average;
}
void adc_get_result(void)
{
    uint32_t code_average;
    unsigned short adc_result;
    adc_clk_en();
    adc_sample_start(adc_raw_data, ADC_SAMPLE_GROUP_CNT, 1000);
    adc_sample_stop();
    adc_clk_dis();
    code_average = adc_sort_and_get_average_code(adc_raw_data);
    adc_result = adc_calculate_voltage(code_average);
    soc_printf("adc_result %d\r\n", adc_result);
    drv_delay_ms(1000);
}

void user_init(void)
{
    /* init uart */
    log_init(); //uart1 used pa0 pa1
    adc_init(adc_cfg);
    drv_delay_ms(100);
}

void main_loop(void)
{
    adc_get_result();
}

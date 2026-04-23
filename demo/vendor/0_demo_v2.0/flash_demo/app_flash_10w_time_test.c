/********************************************************************************************************
 * @file    app_flash_10w_time_test.c
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
#include "common.h"

#if(DEMO_MODE == FLASH_10W_TIME_TEST)

unsigned char test_buf[256]={0};

unsigned int test_area_addr=0x10000;

unsigned int sys_tick = 0;
unsigned int f_sector_erase_us = 0;
unsigned int f_page_write_us = 0;

unsigned char                    board_config[10]  = {0};
volatile unsigned short          run_led_config = 0;//program running led
volatile unsigned short          uart_tx_pin_config=0;


#define CLOCK_SYS_CLOCK_HZ      16000000//lynx systimer clk fixed at 16MHz，confirmed by nanshun.ouyang
enum{
    CLOCK_SYS_TIMER_CLK_1S = CLOCK_SYS_CLOCK_HZ,
    CLOCK_SYS_TIMER_CLK_1MS = (CLOCK_SYS_CLOCK_HZ / 1000),
    CLOCK_SYS_TIMER_CLK_1US = (CLOCK_SYS_CLOCK_HZ / 1000000),
};
/********************************************************/
//  log init
uart_handle_t uart_handle;
void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}
void user_init(void)
{

    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1
    /**
     * @brief board config start addr: 0x9C00
     * run led     = byte0<<8+byte1
     * err led     = byte2<<8+byte3
     * uart tx pin = byte8<<8+byte9
     */
    flash_read_page(0x9C00, 10, board_config);
    run_led_config = (board_config[0]<<8) + board_config[1];
    uart_tx_pin_config = (board_config[8]<<8) + board_config[9];

    gpio_function_en(run_led_config);
    gpio_output_en(run_led_config);


    for(int k=0; k<3; k++)
    {
        soc_printf("************************ Start check Area%d ************************\n",k);
        for(int j=0; j<10; j++)
        {
            for(int i=0; i<10000; i++)
            {
                /******sector(4k byte) erase*******/
                sys_tick = stimer_get_tick();
                flash_erase_sector(test_area_addr+k*0x1000);
                f_sector_erase_us = (stimer_get_tick() - sys_tick)/CLOCK_SYS_TIMER_CLK_1US;
                /******page(256 byte) write*******/
                sys_tick = stimer_get_tick();
                flash_write_page(test_area_addr+k*0x1000,256,(unsigned char *)test_buf);
                f_page_write_us = (stimer_get_tick() - sys_tick)/CLOCK_SYS_TIMER_CLK_1US;
                if(i==9999)
                {
                    soc_printf("flash 0x1%d000 No.%d0000 sector erase time: %d us\n",k,j+1,f_sector_erase_us);
                    soc_printf("flash 0x1%d000 No.%d0000 page write time: %d us\n",k,j+1,f_page_write_us);
                }
            }
        }
    }
    soc_printf("************************ Finish ************************\n");

}


void main_loop(void)
{
    delay_ms(500);
    gpio_set_high_level(run_led_config);

}

#endif

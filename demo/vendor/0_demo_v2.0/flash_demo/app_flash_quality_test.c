/********************************************************************************************************
 * @file    app_flash_quality_test.c
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
/*
 ============================================================================
 Name        : main.c
 Author      : knw
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, ANSI-style
 ============================================================================
 */

#include "common.h"

#if DEMO_MODE == FLASH_QUALITY_TEST

#define FLASH_VOLTAGE_TEST      0
#define FLASH_MID_TEST          1
#define FLASH_LIFE_TEST         2        //should be ram code
#define FLASH_TEST_MODE         FLASH_VOLTAGE_TEST


//Note that the LED1/LED2 and printf.h GPIO(serial port), and LED3/LED4,which needs to be changed according to the pin of the board.
unsigned char                    board_config[13]  = {0};
volatile unsigned short          run_led_config = 0;//program running led
volatile unsigned short          err_led_config = 0;//program error led
volatile unsigned short          min_time_config = 0;//VOLTAGE_TEST1/FLASH_VOLTAGE_TEST2,determine the minimum power-on time
volatile unsigned short          max_time_config = 0;//VOLTAGE_TEST1/FLASH_VOLTAGE_TEST2,determine the maximum power-on time
volatile unsigned short          uart_tx_pin_config=0;
volatile unsigned int            flash_mid_def=0;
gpio_init_t run_gpio_init;
gpio_init_t err_gpio_init;
gpio_init_t max_gpio_init;
gpio_init_t min_gpio_init;

char pin_state = 0;
unsigned char            jedec_id[3]               = {0};
/********************************************************/
//  log init
uart_handle_t uart_handle;
static dmac_handle_t flash_dmac_handle;
dwc_ssi_handle_t dwc_ssi_handle;

void CPU_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&flash_dmac_handle);
}

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
/********************************************************/


#if (FLASH_TEST_MODE == FLASH_VOLTAGE_TEST)
volatile unsigned char  flash_size              = 0;
volatile unsigned int   flash_sector            = 0;
unsigned char           test_buf[6]             = {0};
unsigned char           error_buf[2]            = {0};
unsigned char           read_buf[5000] __attribute__((aligned(4)))         = {0};
volatile unsigned char  ran_a                   = 0;
unsigned int            flash_mid               = 0;
unsigned int            test_area_addr1         = 0;
unsigned int            test_area_addr2         = 0;
unsigned char           test_area_data          = 0;
unsigned int            error_flag_addr         = 0;
unsigned int            error_data_addr         = 0;
unsigned int            error_mid_addr          = 0;
unsigned int            error_flag_loop_addr    = 0;
unsigned int            error_data_loop_addr    = 0;
unsigned int            error_flag              = 0;
unsigned int            error_data              = 0;
unsigned int            error_mid               = 0;
unsigned int            error_data_loop         = 0;
unsigned int            error_flag_loop         = 0;
unsigned int            error_no_test_addr      = 0;
unsigned int            error_no_test_data      = 0;
unsigned int            no_test_error_flag_addr = 0;
unsigned int            no_test_error_data_addr = 0;
volatile unsigned short adc_vbat                = 0;
volatile unsigned char  debug                   = 0;
volatile unsigned char  debug1                  = 0;
volatile unsigned char  debug2                  = 0;
volatile unsigned int addr_debug                = 0;
unsigned char uid_buf[16]         = {0};
void user_init(void)
{

/********************************************************/
    flash_init(CPU_DMAC_CH5);
    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1
/********************************************************/

/**
   * @brief board config start addr: 0x9C00
   * run led      = byte0<<8+byte1
   * err led      = byte2<<8+byte3
   * min time pin = byte4<<8+byte5
   * max time pin = byte6<<8+byte7
   * uart tx pin  = byte8<<8+byte9
*/
    flash_read_page(0x9C00, sizeof(board_config), board_config);
    run_led_config = (board_config[0]<<8) + board_config[1];
    err_led_config = (board_config[2]<<8) + board_config[3];
    min_time_config = (board_config[4]<<8) + board_config[5];
    max_time_config = (board_config[6]<<8) + board_config[7];
    uart_tx_pin_config = (board_config[8]<<8) + board_config[9];
    flash_mid_def = (board_config[10]<<16) + (board_config[11]<<8) + board_config[12];

    run_gpio_init.port = (run_led_config & 0xff00);
    run_gpio_init.pin  = (run_led_config & 0x00ff);
    run_gpio_init.mode = MODE_OUTPUT;
    run_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&run_gpio_init);


    err_gpio_init.port = (err_led_config & 0xff00);
    err_gpio_init.pin  = (err_led_config & 0x00ff);
    err_gpio_init.mode = MODE_OUTPUT;
    err_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&err_gpio_init);


    max_gpio_init.port = (max_time_config & 0xff00);
    max_gpio_init.pin  = (max_time_config & 0x00ff);
    max_gpio_init.mode = MODE_OUTPUT;
    max_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&max_gpio_init);


    min_gpio_init.port = (min_time_config & 0xff00);
    min_gpio_init.pin  = (min_time_config & 0x00ff);
    min_gpio_init.mode = MODE_OUTPUT;
    min_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&min_gpio_init);

    drv_gpio_writepin(run_gpio_init.port, run_gpio_init.pin, 0);//run led
    drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 0);//err led
    drv_gpio_writepin(max_gpio_init.port, max_gpio_init.pin, 0);//max led
    drv_gpio_writepin(min_gpio_init.port, min_gpio_init.pin, 0);//min led


/********************************************************/
    flash_mid = flash_read_mid();
    flash_size = (flash_mid & 0xff0000) >> 16;

    flash_sector = 16;
    for (int i = 0; i < (flash_size - 0x10); i++) {
     flash_sector = flash_sector * 2;
    }
    if((flash_mid_def & 0xff0000) == 0x110000 )  //128k Byte
    {
     test_area_addr1         = 0x6000;
     test_area_addr2         = 0x16000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x10000;
     error_data_addr         = 0x10004;
     error_mid_addr          = 0x10008;
     error_flag_loop_addr    = 0x1000c;
     error_data_loop_addr    = 0x10010;
     no_test_error_flag_addr = 0x10014;
     no_test_error_data_addr = 0x10018;
    }
    else if((flash_mid_def & 0xff0000) == 0x120000 ) //256k Byte
    {
     test_area_addr1         = 0x16000;
     test_area_addr2         = 0x36000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x130000 )//512k Byte
    {
     test_area_addr1         = 0x36000;
     test_area_addr2         = 0x76000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x140000 )//1M Byte
    {
     test_area_addr1         = 0x76000;
     test_area_addr2         = 0xf6000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x150000 )//2M Byte
    {
     test_area_addr1         = 0xf6000;
     test_area_addr2         = 0x1f6000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x160000 )//4M Byte
    {
     test_area_addr1         = 0x1f6000;
     test_area_addr2         = 0x3f6000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x170000 )//8M Byte
    {
     test_area_addr1         = 0x3f6000;
     test_area_addr2         = 0x7f6000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    else if((flash_mid_def & 0xff0000) == 0x180000 )//16M Byte
    {
     test_area_addr1         = 0x7f6000;
     test_area_addr2         = 0xff6000;
     test_area_data          = 0x01;
     error_flag_addr         = 0x20000;
     error_data_addr         = 0x20004;
     error_mid_addr          = 0x20008;
     error_flag_loop_addr    = 0x2000c;
     error_data_loop_addr    = 0x20010;
     no_test_error_flag_addr = 0x20014;
     no_test_error_data_addr = 0x20018;
    }
    soc_printf("\n");
    soc_printf("start");
    soc_printf(",");

    flash_read_page(error_mid_addr,sizeof(error_mid) , (unsigned char*)&error_mid);
    flash_read_page(no_test_error_flag_addr, sizeof(error_no_test_addr), (unsigned char*)&error_no_test_addr);
    flash_read_page(no_test_error_data_addr, sizeof(error_no_test_data), (unsigned char*)&error_no_test_data);


    if ((error_mid != 0xffffffff) || (error_no_test_addr != 0xffffffff) || (error_no_test_data != 0xffffffff)) {
        drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);
        debug1++;
        while (1)
            ;
    }

    if (flash_mid != flash_mid_def) {
        soc_printf("flash_mid: %d", flash_mid);
        soc_printf(",");
        flash_page_program(error_mid_addr, 4, (unsigned char*)&flash_mid);

        drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);
        debug2++;
        while (1)
            ;
    }

    for (unsigned int i = 0; i < (flash_sector - 10); i++) {
        unsigned int addr = 0xa000 + i * (0x1000);
        addr_debug        = addr;
        if ((((addr >= 0xa000) && (addr < test_area_addr1)) || ((addr >= (test_area_addr1 + 0xa000)) && (addr < test_area_addr2))) && (addr != error_flag_addr)) {
            flash_read_page(addr,4095 , (unsigned char*)read_buf);

            for (unsigned int j = 0; j < 4095; j++) {
                if ((read_buf[j] != 0xff)) {
                    debug++;
                    soc_printf("error_data: %d", read_buf[j]);
                    soc_printf(",");
                    soc_printf("error_data_index_j:%d", j);
                    soc_printf(",");
                    flash_page_program(no_test_error_flag_addr, 4, (unsigned char*)&addr);
                    flash_page_program(no_test_error_data_addr, 4, (read_buf + j));

                    drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);
                    while (1)
                        ;
                }
            }
        }
    }
        ran_a = drv_systimer_get_tick()&0xf;//generate ran

        soc_printf("ran_a:%d", ran_a);
        soc_printf(",");
        soc_printf("action:");

}
void main_loop(void){
    drv_delay_ms(5);
    drv_gpio_writepin(min_gpio_init.port, min_gpio_init.pin, 1);
    pin_state = !pin_state;
    drv_gpio_writepin(run_gpio_init.port, run_gpio_init.pin, pin_state);

    for (unsigned char i = 0; i < 6; i++) {
          test_buf[i] = test_area_data * ran_a;
      }
      if (ran_a <= 9) {
          flash_erase_sector(test_area_addr1 + ran_a * (0x1000));
          soc_printf("e");
          for (unsigned int i = 0; i < 4095; i = i + 4) {
            flash_page_program(test_area_addr1 + ran_a * (0x1000) + i , 4, (unsigned char *)test_buf);

          }
          soc_printf("w");
          flash_read_page(test_area_addr1 + ran_a * (0x1000),4095 , (unsigned char*)read_buf);
          for (int i = 0; i < 4095; i++) {
              if (((read_buf[i] != 0xff) && (read_buf[i] != test_buf[0]))) {
                  flash_page_program(error_flag_loop_addr, 1, (unsigned char *)test_buf);
                  flash_page_program(error_data_loop_addr, 1, (unsigned char *)(read_buf + i));
                  soc_printf("r:1oop_error_read_data:%d", read_buf[i]);
                  soc_printf("_");
                  soc_printf("r:loop_error_read_data_index_i: %d", i);
                  drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);
                  while (1)
                      ;
              }
          }
          soc_printf("r");
          soc_printf(";");
          drv_gpio_writepin(max_gpio_init.port, max_gpio_init.pin, 1);
      } else if (ran_a > 9) {
          flash_erase_sector(test_area_addr2 + (ran_a - 10) * (0x1000));
          soc_printf("e");
          for (unsigned int i = 0; i < 4095; i = i + 4) {
              flash_page_program(test_area_addr2 + (ran_a - 10) * (0x1000) + i , 4, (unsigned char *)test_buf);
          }
          soc_printf("w");
          flash_read_page(test_area_addr2 + (ran_a - 10) * (0x1000),4095 , (unsigned char*)read_buf);
          for (int i = 0; i < 4095; i++) {
              if (((read_buf[i] != 0xff) && (read_buf[i] != test_buf[0]))) {
                  flash_page_program(error_flag_loop_addr, 1, (unsigned char *)test_buf);
                  flash_page_program(error_data_loop_addr, 1, (unsigned char *)(read_buf + i));
                  soc_printf("r:1oop_error_read_data:%d", read_buf[i]);
                  drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);
                  while (1)
                      ;
              }
          }
          soc_printf("r");
          soc_printf(";");
          drv_gpio_writepin(max_gpio_init.port, max_gpio_init.pin, 1);
      }
}
#elif (FLASH_TEST_MODE == FLASH_MID_TEST)

unsigned int            flash_mid               = 0;
void user_init(void)
{
/********************************************************/
    flash_init(CPU_DMAC_CH5);
    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1

/********************************************************/



/**
   * @brief board config start addr: 0x9C00
   * run led      = byte0<<8+byte1
   * err led      = byte2<<8+byte3
   * min time pin = byte4<<8+byte5
   * max time pin = byte6<<8+byte7
   * uart tx pin  = byte8<<8+byte9
*/
    flash_read_page(0x9C00, sizeof(board_config), board_config);
    run_led_config = (board_config[0]<<8) + board_config[1];
    err_led_config = (board_config[2]<<8) + board_config[3];
    min_time_config = (board_config[4]<<8) + board_config[5];
    max_time_config = (board_config[6]<<8) + board_config[7];
    uart_tx_pin_config = (board_config[8]<<8) + board_config[9];
    flash_mid_def = (board_config[10]<<16) + (board_config[11]<<8) + board_config[12];

    run_gpio_init.port = (run_led_config & 0xff00);
    run_gpio_init.pin  = (run_led_config & 0x00ff);
    run_gpio_init.mode = MODE_OUTPUT;
    run_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&run_gpio_init);


    err_gpio_init.port = (err_led_config & 0xff00);
    err_gpio_init.pin  = (err_led_config & 0x00ff);
    err_gpio_init.mode = MODE_OUTPUT;
    err_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&err_gpio_init);


    max_gpio_init.port = (max_time_config & 0xff00);
    max_gpio_init.pin  = (max_time_config & 0x00ff);
    max_gpio_init.mode = MODE_OUTPUT;
    max_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&max_gpio_init);


    min_gpio_init.port = (min_time_config & 0xff00);
    min_gpio_init.pin  = (min_time_config & 0x00ff);
    min_gpio_init.mode = MODE_OUTPUT;
    min_gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&min_gpio_init);

    drv_gpio_writepin(run_gpio_init.port, run_gpio_init.pin, 0);//run led
    drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 0);//err led
    drv_gpio_writepin(max_gpio_init.port, max_gpio_init.pin, 0);//max led
    drv_gpio_writepin(min_gpio_init.port, min_gpio_init.pin, 0);//min led


/********************************************************/

    flash_mid = flash_read_mid();
    if (flash_mid != flash_mid_def) {
        soc_printf("error\n");
        drv_gpio_writepin(err_gpio_init.port, err_gpio_init.pin, 1);//err led
    }else {
        soc_printf("11");
        drv_delay_ms(50);
        drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_2, 1);//run led
        drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_5, 1);//min led

    }
}

void main_loop(void)
{

}
#elif (FLASH_TEST_MODE == FLASH_LIFE_TEST)


#define CLOCK_SYS_CLOCK_HZ 16000000 //lynx systimer clk fixed at 16MHz，confirmed by nanshun.ouyang
enum
{
CLOCK_SYS_TIMER_CLK_1S  = CLOCK_SYS_CLOCK_HZ,
CLOCK_SYS_TIMER_CLK_1MS = (CLOCK_SYS_CLOCK_HZ / 1000),
CLOCK_SYS_TIMER_CLK_1US = (CLOCK_SYS_CLOCK_HZ / 1000000),
};

volatile unsigned int loop_cnt  = 0;
volatile unsigned int flash_mid = 0;

volatile unsigned int f_16byte_write_us         = 0;
volatile unsigned int f_16byte_write_max_us     = 0;
volatile unsigned int f_16byte_write_min_us     = 0xffff;
volatile unsigned int f_16byte_write_average_us = 0;
volatile unsigned int f_16byte_read_us          = 0;
volatile unsigned int f_16byte_read_max_us      = 0;
volatile unsigned int f_16byte_read_min_us      = 0xffff;
volatile unsigned int f_16byte_read_average_us  = 0;
volatile unsigned int f_16byte_read_error_cnt   = 0;


volatile unsigned int f_page_write_us         = 0;
volatile unsigned int f_page_write_max_us     = 0;
volatile unsigned int f_page_write_min_us     = 0xffff;
volatile unsigned int f_page_write_average_us = 0;
volatile unsigned int f_page_read_us          = 0;
volatile unsigned int f_page_read_max_us      = 0;
volatile unsigned int f_page_read_min_us      = 0xffff;
volatile unsigned int f_page_read_average_us  = 0;
volatile unsigned int f_page_read_error_cnt   = 0;


volatile unsigned int f_sector_erase_us         = 0;
volatile unsigned int f_sector_erase_max_us     = 0;
volatile unsigned int f_sector_erase_min_us     = 0xffff;
volatile unsigned int f_sector_erase_average_us = 0;


volatile unsigned char flash_size    = 0;
volatile unsigned int  flash_page    = 0;
volatile unsigned int  flash_sector  = 0;
unsigned char          test_buf[256] = {0};
unsigned char          read_buf[256] = {0};


void user_init(void)
{

///********************************************************/
    flash_init(CPU_DMAC_CH5);
    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1

/********************************************************/

/**
   * @brief board config start addr: 0x9C00
   * run led      = byte0<<8+byte1
   * err led      = byte2<<8+byte3
   * min time pin = byte4<<8+byte5
   * max time pin = byte6<<8+byte7
   * uart tx pin  = byte8<<8+byte9
*/
    flash_read_page(0x9C00, sizeof(board_config), board_config);
    run_led_config = (board_config[0]<<8) + board_config[1];
    err_led_config = (board_config[2]<<8) + board_config[3];
    min_time_config = (board_config[4]<<8) + board_config[5];
    max_time_config = (board_config[6]<<8) + board_config[7];
    uart_tx_pin_config = (board_config[8]<<8) + board_config[9];
    flash_mid_def = (board_config[10]<<16) + (board_config[11]<<8) + board_config[12];

    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.mode = MODE_OUTPUT;
    gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&gpio_init);

    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_2, 0);//run led
    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_3, 0);//err led

        /******get the size of the flash*******/
    flash_mid = flash_read_mid();
    flash_size = (flash_mid & 0xff0000) >> 16;

    flash_sector = 16;
    for (int i = 0; i < (flash_size - 0x10); i++) {
        flash_sector = flash_sector * 2;
    }
    flash_page = flash_sector * 16;

    for (int i = 0; i < 256; i++) {
        test_buf[i] = 0x00;
    }

    soc_printf("mid: 0x%x", flash_mid);

    soc_printf(",");
    soc_printf("\n");
    /******tabulation*******************/
    soc_printf("loop_cnt ");
    soc_printf(",");

    soc_printf("one_loop_erase_cnt");
    soc_printf(",");

    soc_printf("sector_erase_average_us");
    soc_printf(",");

    soc_printf("sector_erase_max_us");
    soc_printf(",");

    soc_printf("sector_erase_min_us");
    soc_printf(",");

    soc_printf("page_write_average_us");
    soc_printf(",");

    soc_printf("page_write_max_us");
    soc_printf(",");

    soc_printf("page_write_min_us");
    soc_printf(",");

    soc_printf("page_read_average_us");
    soc_printf(",");

    soc_printf("page_read_max_us");
    soc_printf(",");

    soc_printf("page_read_min_us");
    soc_printf(",");

    soc_printf("page_read_error_cnt");
    soc_printf(",");


    soc_printf("16byte_write_average_us");
    soc_printf(",");

    soc_printf("16byte_write_max_us");
    soc_printf(",");

    soc_printf("16byte_write_min_us");
    soc_printf(",");

    soc_printf("16byte_read_average_us");
    soc_printf(",");

    soc_printf("16byte_read_max_us");
    soc_printf(",");

    soc_printf("16byte_read_min_us");
    soc_printf(",");

    soc_printf("16byte_read_error_cnt");
    soc_printf(",");

    soc_printf("\n");
}

void main_loop(void)
{
    pin_state = !pin_state;
    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_1, pin_state);

    unsigned int sys_tick = drv_systimer_get_tick(); //current time tick
    /******loop cnt*******/
    loop_cnt++;
    soc_printf("%d", loop_cnt);
    soc_printf(",");

    soc_printf("%d", loop_cnt * 2);
    soc_printf(",");

    /*********page check**************/
    for (unsigned int i = 0; i < flash_sector; i++) {
        for (int j = 0; j < 16; j++) {
            /******page write*******/
            sys_tick = drv_systimer_get_tick();
//            flash_write_page(i * 4096 + j * 256, 256, (unsigned char *)test_buf);
//            drv_nor_page_program(NOR_FLASH_PORT_0, i * 4096 + j * 256, (uint8_t *)((uint32_t)test_buf + MCUA_SYS_BUS_BASE), 256);
            flash_page_program(i * 4096 + j * 256, 256, (unsigned char *)test_buf);

            f_page_write_us = (drv_systimer_get_tick() - sys_tick) / CLOCK_SYS_TIMER_CLK_1US;
            f_page_write_average_us += f_page_write_us;
            if (f_page_write_us > f_page_write_max_us) {
                f_page_write_max_us = f_page_write_us;
            }
            if (f_page_write_us < f_page_write_min_us) {
                f_page_write_min_us = f_page_write_us;
            }

            /******page read*******/
            sys_tick = drv_systimer_get_tick();
//            flash_read_page(i * 4096 + j * 256, 256, (unsigned char *)read_buf);
//            drv_nor_read_data(NOR_FLASH_PORT_0, i * 4096 + j * 256, (uint8_t *)((uint32_t)read_buf + MCUA_SYS_BUS_BASE), 256);
            flash_read_page(i * 4096 + j * 256,256, (unsigned char *)read_buf);
            f_page_read_us = (drv_systimer_get_tick() - sys_tick) / CLOCK_SYS_TIMER_CLK_1US;
            for (int cnt = 0; cnt < 256; cnt++) {
                if (read_buf[cnt] != 0x00) {
                    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_2, 1);
                    f_page_read_error_cnt++;
                }
            }
            f_page_read_average_us += f_page_read_us;
            if (f_page_read_us > f_page_read_max_us) {
                f_page_read_max_us = f_page_read_us;
            }
            if (f_page_read_us < f_page_read_min_us) {
                f_page_read_min_us = f_page_read_us;
            }
        }
        sys_tick = drv_systimer_get_tick();
//        flash_erase_sector(i * 4096);
//        drv_nor_sector_erase(NOR_FLASH_PORT_0, i * 4096);
        flash_erase_sector(i * 4096);
        f_sector_erase_us = (drv_systimer_get_tick() - sys_tick) / CLOCK_SYS_TIMER_CLK_1US;
        if (f_sector_erase_us > f_sector_erase_max_us) {
            f_sector_erase_max_us = f_sector_erase_us;
        }
        if (f_sector_erase_us < f_sector_erase_min_us) {
            f_sector_erase_min_us = f_sector_erase_us;
        }
        f_sector_erase_average_us += f_sector_erase_us;
    }
    f_sector_erase_average_us = f_sector_erase_average_us / flash_sector;
    f_page_write_average_us   = f_page_write_average_us / (flash_sector * 16);
    f_page_read_average_us    = f_page_read_average_us / (flash_sector * 16);

    //sector print
    soc_printf("%d", f_sector_erase_average_us);
    soc_printf(",");

    soc_printf("%d", f_sector_erase_max_us);
    soc_printf(",");

    soc_printf("%d", f_sector_erase_min_us);
    soc_printf(",");


    //write print
    soc_printf("%d", f_page_write_average_us);
    soc_printf(",");

    soc_printf("%d", f_page_write_max_us);
    soc_printf(",");

    soc_printf("%d", f_page_write_min_us);
    soc_printf(",");

    //read print
    soc_printf("%d", f_page_read_average_us);
    soc_printf(",");

    soc_printf("%d", f_page_read_max_us);
    soc_printf(",");

    soc_printf("%d", f_page_read_min_us);
    soc_printf(",");

    soc_printf("%d", f_page_read_error_cnt);
    soc_printf(",");


    /***********16 byte check*************/
    for (unsigned int i = 0; i < flash_sector; i++) {
        for (unsigned int j = 0; j < 256; j++) {
            /******16 byte write*******/
            sys_tick = drv_systimer_get_tick();
//            flash_write_page(i * 4096 + j * 16, 16, (unsigned char *)test_buf);
//            drv_nor_page_program(NOR_FLASH_PORT_0, i * 4096 + j * 16, (uint8_t *)((uint32_t)test_buf + MCUA_SYS_BUS_BASE), 16);
            flash_page_program(i * 4096 + j * 16,16, (unsigned char *)test_buf);
            f_16byte_write_us = (drv_systimer_get_tick() - sys_tick) / CLOCK_SYS_TIMER_CLK_1US;
            f_16byte_write_average_us += f_16byte_write_us;
            if (f_16byte_write_us > f_16byte_write_max_us) {
                f_16byte_write_max_us = f_16byte_write_us;
            }
            if (f_16byte_write_us < f_16byte_write_min_us) {
                f_16byte_write_min_us = f_16byte_write_us;
            }
            /******16 byte read*******/
            sys_tick = drv_systimer_get_tick();
//            flash_read_page(i * 4096 + j * 16, 16, (unsigned char *)read_buf);
//            drv_nor_read_data(NOR_FLASH_PORT_0, i * 4096 + j * 16, (uint8_t *)((uint32_t)read_buf + MCUA_SYS_BUS_BASE), 16);
            flash_read_page(i * 4096 + j * 16, 16, (unsigned char *)read_buf);
            f_16byte_read_us = (drv_systimer_get_tick() - sys_tick) / CLOCK_SYS_TIMER_CLK_1US;
            for (int cnt = 0; cnt < 16; cnt++) {
                if (read_buf[cnt] != 0x00) {
                    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_2, 1);
                    f_16byte_read_error_cnt++;
                }
            }
            f_16byte_read_average_us += f_16byte_read_us;
            if (f_16byte_read_us > f_16byte_read_max_us) {
                f_16byte_read_max_us = f_16byte_read_us;
            }
            if (f_16byte_read_us < f_16byte_read_min_us) {
                f_16byte_read_min_us = f_16byte_read_us;
            }
        }
//        flash_erase_sector(i * 4096);
//        drv_nor_sector_erase(NOR_FLASH_PORT_0, i * 4096);
        flash_erase_sector(i * 4096);
    }
    f_16byte_write_average_us = f_16byte_write_average_us / (flash_sector * 256);
    f_16byte_read_average_us  = f_16byte_read_average_us / (flash_sector * 256);

    //write print
    soc_printf("%d", f_16byte_write_average_us);
    soc_printf(",");

    soc_printf("%d", f_16byte_write_max_us);
    soc_printf(",");

    soc_printf("%d", f_16byte_write_min_us);
    soc_printf(",");

    //read print
    soc_printf("%d", f_16byte_read_average_us);
    soc_printf(",");

    soc_printf("%d", f_16byte_read_max_us);
    soc_printf(",");

    soc_printf("%d", f_16byte_read_min_us);
    soc_printf(",");

    soc_printf("%d", f_16byte_read_error_cnt);
    soc_printf(",");
    soc_printf("\n");
}




#endif

#endif

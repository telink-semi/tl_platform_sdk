/********************************************************************************************************
 * @file    app_hspi_xip.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#if defined(MCU_CORE_TL753X)
    #if (SPI_MODE == SPI_XIP_MODE)
/**********************************************************************************************************************
 *                                         SPI module selection                                                       *
 *********************************************************************************************************************/

    #define HSPI_MODULE    3
    #define SPI_MODULE_SEL HSPI_MODULE

    /**********************************************************************************************************************
*                                         SPI clock set
*********************************************************************************************************************/
    #define SPI_CLK 48000000 //48M

    #define SPI_XIP_SERIAL_CMD_READ       1
    #define SPI_XIP_SYNC_READ             2
    #define SPI_XIP_LOAD_PROGRAM_TO_PSRAM 3

    #define SPI_XIP_TEST_MODE             SPI_XIP_LOAD_PROGRAM_TO_PSRAM

hspi_pin_config_t spi_pin_config =
    {
        .spi_csn_pin      = GPIO_FC_PA0,
        .spi_clk_pin      = GPIO_FC_PA1,
        .spi_mosi_io0_pin = GPIO_FC_PJ2,
        .spi_miso_io1_pin = GPIO_FC_PJ4,
        .spi_io2_pin      = GPIO_FC_PA3,
        .spi_io3_pin      = GPIO_FC_PA5,
        .spi_io4_pin      = GPIO_FC_PA4,
        .spi_io5_pin      = GPIO_FC_PA6,
        .spi_io6_pin      = GPIO_FC_PJ3,
        .spi_io7_pin      = GPIO_FC_PJ5,
        .spi_dm_pin       = GPIO_FC_PA2,

};

/**
 * @brief  psram read data lane
 */
typedef enum
{
    OPI_DDR_PSRAM_SYNC_READ      = 0x0000,
    OPI_DDR_PSRAM_SYNC_WRITE     = 0x8080,
    OPI_DDR_PSRAM_READ_LINEAR    = 0x2020,
    OPI_DDR_PSRAM_WRITE_LINEAR   = 0xA0A0,
    OPI_DDR_PSRAM_MODE_READ_REG  = 0x4040,
    OPI_DDR_PSRAM_MODE_WRITE_REG = 0xc0c0,
    OPI_DDR_PSRAM_RESET          = 0xffff,
} opi_ddr_psram_lane_e;

    #if (SPI_XIP_TEST_MODE == SPI_XIP_SERIAL_CMD_READ)

spi_wr_xip_config_t spi_wr_xip_reg_config =
    {
        .spi_xip_wr_io_mode     = SPI_OCTAL_MODE,
        .spi_xip_wr_addr_len    = 3,
        .spi_xip_wr_addr_fmt_en = 1,
        .spi_xip_wr_addr_en     = 1,
        .spi_xip_wr_cmd_fmt_en  = 1,
        .spi_xip_wr_cmd_en      = 1,
        .spi_xip_wr_dummy_cnt   = 0,
        .spi_xip_wr_transmode   = SPI_MODE_WR_WRITE_ONLY,
        .spi_xip_wr_cmd1_en     = 1,

};

spi_wr_xip_config_t spi_wr_xip_config =
    {
        .spi_xip_wr_io_mode     = SPI_OCTAL_MODE,
        .spi_xip_wr_addr_len    = 3,
        .spi_xip_wr_addr_fmt_en = 1,
        .spi_xip_wr_addr_en     = 1,
        .spi_xip_wr_cmd_fmt_en  = 1,
        .spi_xip_wr_cmd_en      = 1,
        .spi_xip_wr_dummy_cnt   = 0,
        .spi_xip_wr_transmode   = SPI_MODE_WR_WRITE_ONLY,
        .spi_xip_wr_cmd1_en     = 1,
};
        #define XIP_DUMMY_CNT 8
spi_rd_xip_config_t spi_rd_xip_config =
    {
        .spi_xip_rd_io_mode       = SPI_OCTAL_MODE,
        .spi_xip_rd_addr_len      = 3,
        .spi_xip_rd_addr_fmt_en   = 1,
        .spi_xip_rd_addr_en       = 1,
        .spi_xip_rd_cmd_fmt_en    = 1,
        .spi_xip_rd_cmd_en        = 1,
        .spi_xip_rd_dummy_cnt     = XIP_DUMMY_CNT & 0x0f,
        .spi_xip_rd_dummy_cnt_add = XIP_DUMMY_CNT >> 4,
        .spi_xip_rd_transmode     = SPI_MODE_RD_DUMMY_READ,
        .spi_xip_rd_cmd1_en       = 1,
        .spi_xip_page_mode_en     = 0,
        .spi_xip_timeout_mode_en  = 0,
        .spi_xip_tcem_mode_en     = 1,
};

unsigned char       read_data[2]  = {0};
unsigned char       read_data1[2] = {0};

_attribute_ram_code_sec_noinline_ void user_init(void)
{
    gpio_output_en(LED1);     //enable output
    gpio_input_dis(LED1);     //disable input
    gpio_set_low_level(LED1); //LED Off
    gpio_function_en(LED1);   //enable gpio

    gpio_output_en(LED2);     //enable output
    gpio_input_dis(LED2);     //disable input
    gpio_set_low_level(LED2); //LED Off
    gpio_function_en(LED2);   //enable gpio

    spi_master_init(SPI_MODULE_SEL, SRC_CLK_BASEBAND_PLL_192M, SRC_CLK_BASEBAND_PLL_192M / SPI_CLK, SPI_MODE0);

    hspi_set_pin(&spi_pin_config);

    spi_set_wr_tcem_us(SPI_MODULE_SEL, 7);
    spi_set_rd_tcem_us(SPI_MODULE_SEL, 7);

    //set DQS DLL
    unsigned char ddr_mode = 1, dqs_mode = 0, dqs_edge = 0, dll_mode = 1;
    reg_spi_xip_ddr_ctrl0(SPI_MODULE_SEL) = (dqs_edge << 4) | (dqs_mode << 3) | (ddr_mode << 2) | (ddr_mode << 1) | ddr_mode; // xip_dqs_edge|xip_dqs_mode|cmd_ddr|addr_ddr|data_ddr
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) &= ~(dll_mode << 7);
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) |= (dll_mode << 6);
    volatile unsigned char dly_sel      = 0x0a;
    reg_spi_rxdll_ctrl1(SPI_MODULE_SEL) = (dll_mode << 4) | dly_sel;

    //printf("\n reg_xip_wr_tcem_set: %d \n", reg_xip_wr_tcem_set(SPI_MODULE_SEL) );
    //default page boundary size is 32byte, 2^page_size.
    //Use this combined with xip_mode being xip sequential mode
    spi_xip_page_size(SPI_MODULE_SEL, 4);
    spi_xip_en(SPI_MODULE_SEL);
    
    spi_set_wr_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_wr_xip_config);
    spi_set_rd_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_rd_xip_config);

    spi_master_read_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_MODE_READ_REG, 0x00, (unsigned char *)read_data, 2, SPI_MODE_RD_DUMMY_READ);
    printf("\n MR0= %x,MR1= %x \n", read_data[0], read_data[1]);

    unsigned char data = 0x29;
    spi_master_write_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_MODE_WRITE_REG, 0x00, &data, 1, SPI_MODE_WR_WRITE_ONLY);
    delay_us(100);
    spi_master_read_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_MODE_READ_REG, 0x00, (unsigned char *)read_data1, 2, SPI_MODE_RD_DUMMY_READ);
    printf("\n MR0= %x,MR1= %x \n", read_data1[0], read_data1[1]);
}

    #elif (SPI_XIP_TEST_MODE == SPI_XIP_SYNC_READ)

        #define XIP_DUMMY_CNT 8

spi_wr_xip_config_t spi_wr_xip_config =
    {
        .spi_xip_wr_io_mode     = SPI_OCTAL_MODE,
        .spi_xip_wr_addr_len    = 3, //4 bytes
        .spi_xip_wr_addr_fmt_en = 1,
        .spi_xip_wr_addr_en     = 1,
        .spi_xip_wr_cmd_fmt_en  = 1,
        .spi_xip_wr_cmd_en      = 1,
        .spi_xip_wr_dummy_cnt   = 7,
        .spi_xip_wr_transmode   = SPI_MODE_WR_DUMMY_WRITE,
        .spi_xip_wr_cmd1_en     = 1,

};

spi_rd_xip_config_t spi_rd_xip_config =
    {
        .spi_xip_rd_io_mode       = SPI_OCTAL_MODE,
        .spi_xip_rd_addr_len      = 3, //4 bytes
        .spi_xip_rd_addr_fmt_en   = 1,
        .spi_xip_rd_addr_en       = 1,
        .spi_xip_rd_cmd_fmt_en    = 1,
        .spi_xip_rd_cmd_en        = 1,
        .spi_xip_rd_dummy_cnt     = XIP_DUMMY_CNT & 0x0f,
        .spi_xip_rd_transmode     = SPI_MODE_RD_DUMMY_READ,
        .spi_xip_rd_cmd1_en       = 1,
        .spi_xip_rd_dummy_cnt_add = XIP_DUMMY_CNT >> 4,
        .spi_xip_page_mode_en     = 0,
        .spi_xip_timeout_mode_en  = 0,
        .spi_xip_tcem_mode_en     = 1,
};
        #define DATA_BUFF_BYTE_LEN 16
unsigned char read_data[DATA_BUFF_BYTE_LEN]  = {0};
unsigned char write_data[DATA_BUFF_BYTE_LEN] = {0xAA, 0x10, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xBB};

_attribute_ram_code_sec_noinline_ void user_init(void)
{
    gpio_output_en(LED1);     //enable output
    gpio_input_dis(LED1);     //disable input
    gpio_set_low_level(LED1); //LED Off
    gpio_function_en(LED1);   //enable gpio

    gpio_output_en(LED2);     //enable output
    gpio_input_dis(LED2);     //disable input
    gpio_set_low_level(LED2); //LED Off
    gpio_function_en(LED2);   //enable gpio

    spi_master_init(SPI_MODULE_SEL, SRC_CLK_BASEBAND_PLL_192M, SRC_CLK_BASEBAND_PLL_192M / SPI_CLK, SPI_MODE0);

    hspi_set_pin(&spi_pin_config);

    spi_set_wr_tcem_us(SPI_MODULE_SEL, 7);
    spi_set_rd_tcem_us(SPI_MODULE_SEL, 7);

    //set DQS DLL
    unsigned char ddr_mode = 1, dqs_mode = 0, dqs_edge = 0, dll_mode = 1;
    reg_spi_xip_ddr_ctrl0(SPI_MODULE_SEL) = (dqs_edge << 4) | (dqs_mode << 3) | (ddr_mode << 2) | (ddr_mode << 1) | ddr_mode; // xip_dqs_edge|xip_dqs_mode|cmd_ddr|addr_ddr|data_ddr
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) &= ~(dll_mode << 7);
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) |= (dll_mode << 6);
    volatile unsigned char dly_sel      = 0x0a;
    reg_spi_rxdll_ctrl1(SPI_MODULE_SEL) = (dll_mode << 4) | dly_sel;

    spi_xip_page_size(SPI_MODULE_SEL, 4);
    spi_xip_en(SPI_MODULE_SEL);

    spi_set_wr_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_wr_xip_config);
    spi_set_rd_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_rd_xip_config);

    unsigned char data = 0x09;
    spi_master_write_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_MODE_WRITE_REG, 0x00, &data, 1, SPI_MODE_WR_WRITE_ONLY);
    delay_us(100);

    volatile unsigned int cnt = 0;
    while (cnt < 1000) {
        write_data[0]++;
        write_data[DATA_BUFF_BYTE_LEN - 1]++;
        spi_master_write_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_SYNC_WRITE, 0x00, (unsigned char *)write_data, DATA_BUFF_BYTE_LEN, SPI_MODE_WR_DUMMY_WRITE);
        delay_us(100);
        spi_master_read_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_SYNC_READ, 0x00, (unsigned char *)read_data, DATA_BUFF_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
        delay_us(1000);
        cnt++;
        volatile unsigned test_result = 0xff;
        for (unsigned char i = 0; i < DATA_BUFF_BYTE_LEN; i++) {
            if (read_data[i] != (write_data[i])) {
                test_result = 0;
                gpio_set_high_level(LED2); //LED on indicate data error
                break;
            }
        }
        if (test_result == 0) {

            printf("cnt=%d,reg_spi_rxdll_ctrl1=%x\n", cnt, reg_spi_rxdll_ctrl1(SPI_MODULE_SEL));
            printf("Psram _write_read_data_fail, \n");
        } else {

            printf("cnt=%d,reg_spi_rxdll_ctrl1=%x\n", cnt, reg_spi_rxdll_ctrl1(SPI_MODULE_SEL));
            printf("Psram _write_read_data_success, \n");

        }
        printf("read_data ");
        for (unsigned char i = 0; i < DATA_BUFF_BYTE_LEN; i++) {
            printf(" %2x", read_data[i]);
        }
        printf("\n");
        printf("write_data");
        for (unsigned char i = 0; i < DATA_BUFF_BYTE_LEN; i++) {
            printf(" %2x", write_data[i]);
        }
        printf("\n");
        dly_sel++;
        if (dly_sel <= 0x0f) {
            reg_spi_rxdll_ctrl1(SPI_MODULE_SEL) = (reg_spi_rxdll_ctrl1(SPI_MODULE_SEL) & (~FLD_SPI_DLL_DLY_SEL)) | dly_sel;
        }
    }
    printf("Psram _write_read_data_pass, \n");
}
    #elif (SPI_XIP_TEST_MODE == SPI_XIP_LOAD_PROGRAM_TO_PSRAM)
        #define XIP_DUMMY_CNT 8
        #define DATA_BUFF_BYTE_LEN 16
        #define LED_PROGRAM_BYTE_LEN 0x40 // determined by program size,
unsigned char led_program_in_sram[LED_PROGRAM_BYTE_LEN] = {
    0x37, 0x17, 0x14, 0x80, 0x81, 0x56, 0x23, 0x03, 0xd7, 0xc6, 0xb7, 0x16, 0x14, 0x80, 0xb7, 0x17,
    0x14, 0x80, 0x7d, 0x46, 0x93, 0x86, 0xe6, 0xc6, 0x13, 0x07, 0x00, 0xf8, 0x23, 0x81, 0xc7, 0xc6,
    0xb7, 0x07, 0x10, 0x00, 0x93, 0x87, 0x17, 0x00, 0xfd, 0x17, 0xfd, 0xff, 0x23, 0x80, 0xe6, 0x00,
    0xc5, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
unsigned char led_program_in_psram[LED_PROGRAM_BYTE_LEN] = {0};

spi_wr_xip_config_t spi_wr_xip_reg_config =
    {
        .spi_xip_wr_io_mode     = SPI_OCTAL_MODE,
        .spi_xip_wr_addr_len    = 3,
        .spi_xip_wr_addr_fmt_en = 1,
        .spi_xip_wr_addr_en     = 1,
        .spi_xip_wr_cmd_fmt_en  = 1,
        .spi_xip_wr_cmd_en      = 1,
        .spi_xip_wr_dummy_cnt   = 0,
        .spi_xip_wr_transmode   = SPI_MODE_WR_WRITE_ONLY,
        .spi_xip_wr_cmd1_en     = 1,

};

spi_wr_xip_config_t spi_wr_xip_config =
    {
        .spi_xip_wr_io_mode     = SPI_OCTAL_MODE,
        .spi_xip_wr_addr_len    = 3, //4 bytes
        .spi_xip_wr_addr_fmt_en = 1,
        .spi_xip_wr_addr_en     = 1,
        .spi_xip_wr_cmd_fmt_en  = 1,
        .spi_xip_wr_cmd_en      = 1,
        .spi_xip_wr_dummy_cnt   = 7,
        .spi_xip_wr_transmode   = SPI_MODE_WR_DUMMY_WRITE,
        .spi_xip_wr_cmd1_en     = 1,

};

spi_rd_xip_config_t spi_rd_xip_config =
    {
        .spi_xip_rd_io_mode       = SPI_OCTAL_MODE,
        .spi_xip_rd_addr_len      = 3, //4 bytes
        .spi_xip_rd_addr_fmt_en   = 1,
        .spi_xip_rd_addr_en       = 1,
        .spi_xip_rd_cmd_fmt_en    = 1,
        .spi_xip_rd_cmd_en        = 1,
        .spi_xip_rd_dummy_cnt     = XIP_DUMMY_CNT & 0x0f,
        .spi_xip_rd_transmode     = SPI_MODE_RD_DUMMY_READ,
        .spi_xip_rd_cmd1_en       = 1,
        .spi_xip_rd_dummy_cnt_add = XIP_DUMMY_CNT >> 4,
        .spi_xip_page_mode_en     = 0,
        .spi_xip_timeout_mode_en  = 0,
        .spi_xip_tcem_mode_en     = 1,
};

_attribute_ram_code_sec_noinline_ void user_init(void)
{
    gpio_output_en(LED1);     //enable output
    gpio_input_dis(LED1);     //disable input
    gpio_set_low_level(LED1); //LED Off
    gpio_function_en(LED1);   //enable gpio
    gpio_output_en(LED2);     //enable output
    gpio_input_dis(LED2);     //disable input
    gpio_set_low_level(LED2); //LED Off
    gpio_function_en(LED2);   //enable gpio

    /**** 1. initialize spi ******/
    spi_master_init(SPI_MODULE_SEL, SRC_CLK_BASEBAND_PLL_192M, SRC_CLK_BASEBAND_PLL_192M / SPI_CLK, SPI_MODE0);

    hspi_set_pin(&spi_pin_config);

    spi_set_wr_tcem_us(SPI_MODULE_SEL, 7);
    spi_set_rd_tcem_us(SPI_MODULE_SEL, 7);

    unsigned char ddr_mode = 1, dqs_mode = 0, dqs_edge = 0, dll_mode = 1;       //ddr_mode=1,dqs_mode=0,dqs_edge=0,dll_mode=1,dummy_sub1=1
    reg_spi_xip_ddr_ctrl0(SPI_MODULE_SEL) = (dqs_edge << 4) | (dqs_mode << 3) | (ddr_mode << 2) | (ddr_mode << 1) | ddr_mode; // xip_dqs_edge|xip_dqs_mode|cmd_ddr|addr_ddr|data_ddr
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) &= ~(dll_mode << 7);
    reg_spi_rxdll_ctrl0(SPI_MODULE_SEL) |= (dll_mode << 6);
    volatile unsigned char dly_sel      = 0x0a;
    reg_spi_rxdll_ctrl1(SPI_MODULE_SEL) = (dll_mode << 4) | dly_sel;

    spi_xip_page_size(SPI_MODULE_SEL, 7);
    spi_xip_en(SPI_MODULE_SEL);

    /**** 2. initialize psram ******/
    spi_set_wr_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_wr_xip_config);

    spi_set_rd_xip_config(SPI_MODULE_SEL, SPI_XIP0, &spi_rd_xip_config);

    unsigned char data = 0x09;
    spi_master_write_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_MODE_WRITE_REG, 0x00, &data, 1, SPI_MODE_WR_WRITE_ONLY);
    delay_us(100);

    /**** 3. write led program to psram ******/
    spi_master_write_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_SYNC_WRITE, 0x00, (unsigned char *)led_program_in_sram, LED_PROGRAM_BYTE_LEN, SPI_MODE_WR_DUMMY_WRITE); //write bin data to psram
    /**** 4. read back led program from psram ******/
    spi_master_read_xip(SPI_MODULE_SEL, SPI_XIP0, OPI_DDR_PSRAM_SYNC_READ, 0x00, (unsigned char *)led_program_in_psram, LED_PROGRAM_BYTE_LEN, SPI_MODE_RD_DUMMY_READ); //read bin data from psram
    printf("\r\n");
    printf("Psram data");
    for (unsigned char i = 0; i < LED_PROGRAM_BYTE_LEN; i++) {
        printf(" %2x", led_program_in_psram[i]);
    }
    printf("\r\n");
    printf("Sram  data");
    for (unsigned char i = 0; i < LED_PROGRAM_BYTE_LEN; i++) {
        printf(" %2x", led_program_in_sram[i]);
    }
    printf("\r\n");
    for (unsigned int i = 0; i < LED_PROGRAM_BYTE_LEN; i++) {
        if (led_program_in_sram[i] != led_program_in_psram[i]) {
            gpio_set_high_level(LED2);
            break;
        }
    }
    
    /**** 5. run led program in psram ******/
    __asm__("li t0,0x9C000000");
    __asm__("jalr t0");
}
    #endif

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}

    #endif
#endif

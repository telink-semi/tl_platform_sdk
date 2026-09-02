/********************************************************************************************************
 * @file    FlashDevice_Interface.c
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
#include "FlashDevice_Interface.h"
#include "FlashDevice_Driver.h"
#include "common.h"


void FlashDevice_Interface_Init(uint8_t mode, uint32_t speed)
{
    (void)mode;
    (void)speed;
#if defined(MCU_CORE_TL322X)
    gspi_pin_config_t gspi_pin_config = {
        .spi_csn_pin      = (gpio_func_pin_e)FLASH_SPI_PIN_CSN,
        .spi_clk_pin      = (gpio_func_pin_e)FLASH_SPI_PIN_CLK,
        .spi_mosi_io0_pin = (gpio_func_pin_e)FLASH_SPI_PIN_MOSI,
        .spi_miso_io1_pin = (gpio_func_pin_e)FLASH_SPI_PIN_MISO,
    #if 1
        .spi_io2_pin      = (gpio_func_pin_e)GPIO_NONE_PIN, //quad  mode is required, otherwise it is NONE_PIN.
        .spi_io3_pin      = (gpio_func_pin_e)GPIO_NONE_PIN, //quad  mode is required, otherwise it is NONE_PIN.
    #else
        .spi_io2_pin      = (gpio_func_pin_e)FLASH_SPI_PIN_IO2, //quad  mode is required, otherwise it is NONE_PIN.
        .spi_io3_pin      = (gpio_func_pin_e)FLASH_SPI_PIN_IO3, //quad  mode is required, otherwise it is NONE_PIN.
    #endif
    };
    spi_wr_rd_config_t spi_wr_rd_config = {
        .spi_io_mode   = SPI_SINGLE_MODE, /*IO mode set to SPI_3_LINE_MODE when SPI_3LINE_SLAVE.*/
        .spi_dummy_cnt = 0,              //B92 supports up to 32 clk cycle dummy, and TL751X,TL7518,TL721X,TL321X,tl322x supports up to 256 clk cycle dummy.
        .spi_dummy_hold = 0,
        .spi_cmd_en      = 0,
        .spi_addr_en     = 0,
        .spi_addr_len    = 0, //when spi_addr_en = 0,invalid set.
        .spi_cmd_fmt_en  = 0, //when spi_cmd_en = 0,invalid set.
        .spi_addr_fmt_en = 0, //when spi_addr_en = 0,invalid set.
    };


    spi_master_init(FLASH_SPI_MODULE_SEL, sys_clk.pll_clk * 1000000 / speed, SPI_MODE0);

    if(FLASH_SPI_MODULE_SEL == GSPI_MODULE) {
        gspi_set_pin(&gspi_pin_config);
    } else if(FLASH_SPI_MODULE_SEL == GSPI1_MODULE) {
        gspi1_set_pin(&gspi_pin_config);
    } else if(FLASH_SPI_MODULE_SEL == GSPI2_MODULE) {
        gspi2_set_pin(&gspi_pin_config);
    } else if(FLASH_SPI_MODULE_SEL == GSPI3_MODULE) {
        gspi3_set_pin(&gspi_pin_config);
    }

    gpio_function_en(FLASH_PIN_WP);
    gpio_function_en(FLASH_PIN_HOLD);
    gpio_output_en(FLASH_PIN_WP);
    gpio_output_en(FLASH_PIN_HOLD);
    gpio_set_high_level(FLASH_PIN_WP);
    gpio_set_high_level(FLASH_PIN_HOLD);

    
    spi_master_config_plus(FLASH_SPI_MODULE_SEL, &spi_wr_rd_config);
#endif
}

void FlashDevice_Interface_Write(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length)
{
    uint32_t address = 0;
    for(uint32_t i = 0; i < cmd_length; i++){
        address <<= 8;
        address |= cmd_data[i];
    }
    spi_set_addr_len(FLASH_SPI_MODULE_SEL, cmd_length);
    spi_set_address(FLASH_SPI_MODULE_SEL, address);
    spi_addr_en(FLASH_SPI_MODULE_SEL);
    spi_master_write_plus(FLASH_SPI_MODULE_SEL, 0, address, pdata, length, SPI_MODE_WR_WRITE_ONLY);
    spi_addr_dis(FLASH_SPI_MODULE_SEL);
    
}

void FlashDevice_Interface_Read(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length)
{
    spi_master_write_read(FLASH_SPI_MODULE_SEL, cmd_data, cmd_length, pdata, length);
}
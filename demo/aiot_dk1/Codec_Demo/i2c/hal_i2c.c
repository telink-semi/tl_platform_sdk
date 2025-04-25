/********************************************************************************************************
 * @file    hal_i2c.c
 *
 * @brief   This is the source file for TL7518/TL721X/TL321X
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
#include "../dk1_codec_app_config.h"

void hal_i2c_init(void)
{
    i2c_set_pin(I2C_GPIO_SDA_PIN, I2C_GPIO_SCL_PIN);
    i2c_set_tx_dma_config(I2C_TX_DMA_CHN);
    i2c_set_rx_dma_config(I2C_RX_DMA_CHN);
    i2c_master_init();
    i2c_set_master_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / (4 * I2C_CLK_SPEED)));
}

__attribute__((section(".ram_code"))) void hal_i2c_write(uint8_t addr, uint8_t reg, uint8_t value)
{
    uint8_t write_buf[4];
    int     ref = 0;

    write_buf[0] = reg;
    write_buf[1] = value;

    i2c_master_write_dma(addr, (unsigned char *)write_buf, 2);
    ref = (clock_time() - 2) | 1;
    while (i2c_master_busy() && !clock_time_exceed(ref, 50 * 1000));
}

__attribute__((section(".ram_code"))) void hal_i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    uint8_t write_buf[4];
    int     ref = 0;

    write_buf[0] = reg;

    i2c_master_write_dma(addr, (unsigned char *)write_buf, 1);
    ref = (clock_time() - 2) | 1;
    while (i2c_master_busy() && !clock_time_exceed(ref, 50 * 1000));


    i2c_master_read_dma(addr, (unsigned char *)data, len);
    ref = (clock_time() - 2) | 1;
    while (i2c_master_busy() && !clock_time_exceed(ref, 50 * 1000));
}

void hal_i2c_update_bits(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value)
{
    int     ref = 0;
    uint8_t read_buf[4];
    uint8_t write_buf[4];
    hal_i2c_read(addr, reg, read_buf, 1);

    write_buf[0] = reg;
    write_buf[1] = (read_buf[0] & (~mask)) | (mask & value);

    i2c_master_write_dma(addr, (unsigned char *)write_buf, 2);
    ref = (clock_time() - 2) | 1;
    while (i2c_master_busy() && !clock_time_exceed(ref, 50 * 1000));
}

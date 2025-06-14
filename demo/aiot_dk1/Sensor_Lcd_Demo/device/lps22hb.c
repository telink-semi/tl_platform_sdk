/********************************************************************************************************
 * @file    lps22hb.c
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
#include "lps22hb.h"
#include "common.h"

__attribute__((unused)) static uint8_t lps22hb_iic_read(uint8_t reg_addr, uint8_t *pData, uint32_t Size)
{
    i2c_master_write(LPS22HB_I2C_ADDR, &reg_addr, 1);
    return i2c_master_read(LPS22HB_I2C_ADDR, pData, Size) ? 0 : ENXIO;
}

__attribute__((unused)) static uint8_t lps22hb_iic_write(uint8_t reg_addr, uint8_t pData)
{
    uint8_t write_buff[2] = {reg_addr, pData};
    return i2c_master_write(LPS22HB_I2C_ADDR, write_buff, 2) ? 0 : ENXIO;
}

uint8_t lps22hb_iic_init(void)
{
    uint8_t id   = 0;
    uint8_t data = 0;
    uint8_t ret  = lps22hb_iic_read(LPS22HB_WHO_AM_I, &id, 1);
    if (!(0xb1 == id && 0 == ret)) {
        return ENXIO;
    }

    data = BIT(2); // SWRESET
    lps22hb_iic_write(LPS22HB_CTRL_REG2, data);
    do {
        delay_ms(2);
        lps22hb_iic_read(LPS22HB_CTRL_REG2, &data, 1);
    } while (data & BIT(2));

    data = 0x20;
    lps22hb_iic_write(LPS22HB_CTRL_REG1, data);
    return 0;
}

lps22hb_data_st lps22hb_iic_get_data(void)
{
    uint8_t         data_buff[5];
    lps22hb_data_st lps22hb_data;
#if 0
    do{
        lps22hb_iic_read(LPS22HB_STATUS, data_buff, 1);
        lps22hb_data.statue = data_buff[0];
        delay_ms(2);
    } while ((lps22hb_data.statue & 0x03) != 0x03);
#endif
    lps22hb_iic_read(LPS22HB_PRESS_OUT_XL, data_buff, 3);
    lps22hb_data.press = ((data_buff[2] << 16) | (data_buff[1] << 8) | data_buff[0]);

    lps22hb_iic_read(LPS22HB_TEMP_OUT_L, data_buff, 2);
    lps22hb_data.temperature = ((data_buff[1] << 8) | data_buff[0]);

    //    printf("out : %.2f\r\n", lps22hb_data.press/4096.0);
    //    printf("Temperature:%03d.%02dC\r\n\r\n\r\n",(int)lps22hb_data.temperature /100,(int)lps22hb_data.temperature %100);
    lps22hb_data.press       = lps22hb_data.press / 4096.0;
    lps22hb_data.temperature = lps22hb_data.temperature / 100;
    return lps22hb_data;
}

/********************************************************************************************************
 * @file    app_all.c
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
#include "stdio.h"
#include "./device/st7789.h"
#include "./device/hts221.h"
#include "./device/lps22hb.h"
#include "./device/lsm9ds1.h"
#include "common.h"

#if (EXAMPLE_SELECT == EXAMPLE_ALL)
uint32_t        g_time0;
uint8_t         g_flag_hts221_is_exit  = 1;
uint8_t         g_flag_lsm9ds1_is_exit = 1;
uint8_t         g_flag_lps22hb_is_exit = 1;
static uint32_t tick_change_page       = 0;
static uint8_t  page                   = 0;

void user_init(void)
{
    board_iic_init();
    LCD_Init();

    if (lsm9ds1_iic_init()) {
        g_flag_lsm9ds1_is_exit = 0;
        LCD_ShowString(20, 34, 240 - 20, 24, 24, (uint8_t *)"lsm9ds1 is not exit");
    }

    if (lps22hb_iic_init()) {
        g_flag_lps22hb_is_exit = 0;
        LCD_ShowString(20, 154, 240 - 20, 24, 24, (uint8_t *)"lps22hb is not exit");
    }

    if (hts221_iic_init()) {
        g_flag_hts221_is_exit = 0;
        LCD_ShowString(20, 262, 240 - 20, 24, 24, (uint8_t *)"hts221 is not exit");
    }
    g_time0          = stimer_get_tick();
    tick_change_page = stimer_get_tick();
}

lsm9ds1_data_st g_lsm9ds1_data;
lps22hb_data_st g_lps22hb_data;
hts221_data_st  g_hts221_data;

_attribute_ram_code_sec_noinline_ void main_loop(void)
{
    while (1) {
        uint8_t str[40];

        if (clock_time_exceed(tick_change_page, 5 * 1000 * 1000)) {
            tick_change_page = stimer_get_tick();
            page++;
            page %= 2;
            LCD_Fill(BACK_COLOR);
        }

        if (page == 0) {
            if (g_flag_lsm9ds1_is_exit) {
                g_lsm9ds1_data = lsm9ds1_iic_get_data();
                if (g_lsm9ds1_data.pitch_x > 0) {
                    sprintf((char *)str, "pitch_x: %6d", (int)g_lsm9ds1_data.pitch_x);
                } else {
                    g_lsm9ds1_data.pitch_x = -g_lsm9ds1_data.pitch_x;
                    sprintf((char *)str, "pitch_x:-%6d", (int)g_lsm9ds1_data.pitch_x);
                }
                LCD_ShowString(20, 10, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.pitch_y > 0) {
                    sprintf((char *)str, "pitch_y: %6d", (int)g_lsm9ds1_data.pitch_y);
                } else {
                    g_lsm9ds1_data.pitch_y = -g_lsm9ds1_data.pitch_y;
                    sprintf((char *)str, "pitch_y:-%6d", (int)g_lsm9ds1_data.pitch_y);
                }
                LCD_ShowString(20, 34, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.pitch_z > 0) {
                    sprintf((char *)str, "pitch_z: %6d", (int)g_lsm9ds1_data.pitch_z);
                } else {
                    g_lsm9ds1_data.pitch_z = -g_lsm9ds1_data.pitch_z;
                    sprintf((char *)str, "pitch_z:-%6d", (int)g_lsm9ds1_data.pitch_z);
                }
                LCD_ShowString(20, 58, 240 - 20, 24, 24, str);
                //////////////////////////////////////////////////////////////////////////////////////
                if (g_lsm9ds1_data.acc_x > 0) {
                    sprintf((char *)str, "acc_x  : %6d", (int)g_lsm9ds1_data.acc_x);
                } else {
                    g_lsm9ds1_data.acc_x = -g_lsm9ds1_data.acc_x;
                    sprintf((char *)str, "acc_x  :-%6d", (int)g_lsm9ds1_data.acc_x);
                }
                LCD_ShowString(20, 82, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.acc_y > 0) {
                    sprintf((char *)str, "acc_y  : %6d", (int)g_lsm9ds1_data.acc_y);
                } else {
                    g_lsm9ds1_data.acc_y = -g_lsm9ds1_data.acc_y;
                    sprintf((char *)str, "acc_y  :-%6d", (int)g_lsm9ds1_data.acc_y);
                }
                LCD_ShowString(20, 106, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.acc_z > 0) {
                    sprintf((char *)str, "acc_z  : %6d", (int)g_lsm9ds1_data.acc_z);
                } else {
                    g_lsm9ds1_data.acc_z = -g_lsm9ds1_data.acc_z;
                    sprintf((char *)str, "acc_z  :-%6d", (int)g_lsm9ds1_data.acc_z);
                }
                LCD_ShowString(20, 130, 240 - 20, 24, 24, str);
                ////////////////////////////////////////////////
                if (g_lsm9ds1_data.mag_x > 0) {
                    sprintf((char *)str, "mag_x  : %6d", (int)g_lsm9ds1_data.mag_x);
                } else {
                    g_lsm9ds1_data.mag_x = -g_lsm9ds1_data.mag_x;
                    sprintf((char *)str, "mag_x  :-%6d", (int)g_lsm9ds1_data.mag_x);
                }
                LCD_ShowString(20, 154, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.mag_y > 0) {
                    sprintf((char *)str, "mag_y  : %6d", (int)g_lsm9ds1_data.mag_y);
                } else {
                    g_lsm9ds1_data.mag_y = -g_lsm9ds1_data.mag_y;
                    sprintf((char *)str, "mag_y  :-%6d", (int)g_lsm9ds1_data.mag_y);
                }
                LCD_ShowString(20, 178, 240 - 20, 24, 24, str);

                if (g_lsm9ds1_data.mag_z > 0) {
                    sprintf((char *)str, "mag_z  : %6d", (int)g_lsm9ds1_data.mag_z);
                } else {
                    g_lsm9ds1_data.mag_z = -g_lsm9ds1_data.mag_z;
                    sprintf((char *)str, "mag_z  :-%6d", (int)g_lsm9ds1_data.mag_z);
                }
                LCD_ShowString(20, 202, 240 - 20, 24, 24, str);
            }
        } else if (page == 1) {
            if (g_flag_lps22hb_is_exit) {
                g_lps22hb_data = lps22hb_iic_get_data();
                sprintf((char *)str, "press  :%6d", (int)g_lps22hb_data.press);
                LCD_ShowString(20, 10, 240 - 20, 24, 24, str);
            }
            if (g_flag_hts221_is_exit) {
                g_hts221_data = hts221_iic_get_data();
                if (g_hts221_data.temperature > 0) {
                    sprintf((char *)str, "temp   :%3d", (int)g_hts221_data.temperature);
                } else {
                    g_hts221_data.temperature = -g_hts221_data.temperature;
                    sprintf((char *)str, "temp   :-%3d", (int)g_hts221_data.temperature);
                }
                LCD_ShowString(20, 34, 240 - 20, 24, 24, str);
                sprintf((char *)str, "humi   :%3d", (int)g_hts221_data.humidity);
                LCD_ShowString(20, 58, 240 - 20, 24, 24, str);
            }
        }
    }
}

#endif

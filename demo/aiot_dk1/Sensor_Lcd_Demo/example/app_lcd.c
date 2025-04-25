/********************************************************************************************************
 * @file    app_lcd.c
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
#include "../device/st7789.h"
#include "../dk1_sensor_lcd_app_config.h"

#if (EXAMPLE_SELECT == EXAMPLE_LCD)

volatile uint32_t g_time0;
volatile uint32_t g_index   = 0;
volatile uint16_t g_color[] = {BLACK, BLUE, BRED, WHITE, GRED};
volatile uint32_t g_time1;
volatile uint32_t g_index2 = 0;
volatile uint32_t g_index3 = 0;

void user_init(void)
{
    gpio_function_en(GPIO_PA4);
    gpio_output_en(GPIO_PA4);
    gpio_set_high_level(GPIO_PA4);
    LCD_Test();
    g_time0 = stimer_get_tick();
    // g_time1 = stimer_get_tick();
}

_attribute_ram_code_sec_noinline_ void main_loop(void)
{
    //if(clock_time_exceed(g_time0,100*1000)){
    LCD_Fill(g_color[g_index++ % 5]);
    g_time0 = stimer_get_tick();
    g_index2++;
    //}
    if (clock_time_exceed(g_time1, 1000 * 1000)) {
        g_time1  = stimer_get_tick();
        g_index3 = g_index2;
        g_index2 = 0;
    }
}

#endif

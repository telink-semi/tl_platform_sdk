/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "lib/include/dpr.h"

#define LOOP_CNT    16
#define LOOP_SHIFT  4

volatile unsigned short g_dpr_cnt[LOOP_CNT][8] = {0};
unsigned short g_dpr_cnt_avg[8] = {0};

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    dpr_init();
    dpr_chn_enable(DPR_CHN_DEFAULT);
    delay_ms(10);   /* wait for dpr ready */
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop(void)
{
    gpio_toggle(LED1);

    int j = 0;
    while(j < LOOP_CNT)
    {
        dpr_trigger();

        /* delay for diverse sampling data, not necessary */
        delay_ms(10);   

        for(int i=0; i<8; i++)
        {
            g_dpr_cnt[j][i] = dpr_r_chn_cnt_get(i);
            g_dpr_cnt_avg[i] += g_dpr_cnt[j][i];
        }

        j++;
    }

    for(int i=0; i<8; i++)
    {
        g_dpr_cnt_avg[i] =  (g_dpr_cnt_avg[i] >> LOOP_SHIFT);
    }

    printf(" dpr cnt: %d %d %d %d %d %d %d %d \r\n", g_dpr_cnt_avg[0], g_dpr_cnt_avg[1], g_dpr_cnt_avg[2], g_dpr_cnt_avg[3], g_dpr_cnt_avg[4], g_dpr_cnt_avg[5], g_dpr_cnt_avg[6], g_dpr_cnt_avg[7]);
    memset(g_dpr_cnt_avg, 0, sizeof(g_dpr_cnt_avg));
    delay_ms(500);
}


/********************************************************************************************************
 * @file    app_manual_debounce.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
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

#if(KEYCAN_MODE_TEST   ==     KEYSCAN_MANUAL_MODE)
#if (KEYSCAN_ROW_COL_MODE == KEYSCAN_ROW_COL_3X3)
#define ROW_CNT 3
#define COL_CNT 3

unsigned char g_ks_row[ROW_CNT] = {KS_PC0, KS_PC1, KS_PC2};
unsigned char g_ks_col[COL_CNT] = {KS_PE0, KS_PE1, KS_PE2};
#elif (KEYSCAN_ROW_COL_MODE == KEYSCAN_ROW_COL_6X15)
#define ROW_CNT 6
#define COL_CNT 15

unsigned char g_ks_row[ROW_CNT] = {KS_PC0, KS_PC1, KS_PC2, KS_PC3, KS_PC4};
unsigned char g_ks_col[COL_CNT] = {KS_PE0, KS_PE1, KS_PE2, KS_PD0, KS_PD1, KS_PD2, KS_PD3, KS_PB0, KS_PB1, KS_PB2, KS_PB3, KS_PB4, KS_PB5, KS_PB6, KS_PB7};
#elif (KEYSCAN_ROW_COL_MODE == KEYSCAN_ROW_COL_6X21)
#define ROW_CNT 6
#define COL_CNT 21

unsigned char g_ks_row[ROW_CNT] = {KS_PC0, KS_PC1, KS_PC2, KS_PC3, KS_PC4};
unsigned char g_ks_col[COL_CNT] = {KS_PE0, KS_PE1, KS_PE2, KS_PC5, KS_PC6, KS_PC7, KS_PD0, KS_PD1, KS_PD2, KS_PD3, KS_PD4, KS_PD5, KS_PD6, KS_PD7, KS_PB0, KS_PB1, KS_PB2, KS_PB3, KS_PB4, KS_PB5, KS_PB6};
#elif (KEYSCAN_ROW_COL_MODE == KEYSCAN_ROW_COL_8X16)
#define ROW_CNT 8
#define COL_CNT 16

unsigned char g_ks_row[ROW_CNT] = {KS_PC0, KS_PC1, KS_PC2, KS_PC3, KS_PC4, KS_PC5, KS_PC6, KS_PC7};
unsigned char g_ks_col[COL_CNT] = {KS_PD0, KS_PD1, KS_PD2, KS_PD3, KS_PD4, KS_PD5, KS_PD6, KS_PD7, KS_PB0, KS_PB1, KS_PB2, KS_PB3, KS_PB4, KS_PB5, KS_PB6, KS_PB7};
#elif(KEYSCAN_ROW_COL_MODE == KEYSCAN_ROW_COL_6X20)
#define ROW_CNT 6
#define COL_CNT 20

unsigned char g_ks_row[ROW_CNT] = {KS_PC1, KS_PC0, KS_PB7, KS_PC7, KS_PC6, KS_PC5};
unsigned char g_ks_col[COL_CNT] = {KS_PC2, KS_PC3, KS_PC4, KS_PB1, KS_PB3,KS_PD0, KS_PD1, KS_PD2, KS_PF0, KS_PF4, KS_PF5, KS_PE2,KS_PE1, KS_PE0,KS_PF6,KS_PE3,KS_PE4,KS_PE5,KS_PE6,KS_PE7};
#endif

#define DMA_SIZE (8 * 4)

unsigned int now_ks_scanning_buff[8] ={0};
unsigned int last_ks_scanning_buff[8] ={0};
unsigned int dma_ks_scanning_buff[8] ={0};

void user_init(void)
{
    keyscan_set_martix(g_ks_row, ROW_CNT, g_ks_col, COL_CNT, KS_INT_PIN_PULLUP);
    keyscan_init_clk_24m(KEYSCAN_8K,KS_24MXTAL,1);
    keyscan_dma_enable();

    dma_set_llp_sof_mode(DMA0, 1);
    keyscan_dma_config_llp(DMA0, dma_ks_scanning_buff, DMA_SIZE);

    keyscan_enable();
    printf("\n Keyscan Test Start! Please press button. \n");
}

_attribute_ram_code_sec_noinline_ void main_loop(void)
{
#if 1
    if (keyscan_get_rxdone_irq_status())
        {
            keyscan_clr_rxdone_irq_status();
            for(int i=0;i<8;i++)
            {
                now_ks_scanning_buff[i]=dma_ks_scanning_buff[i];
            }
        }
    else
    {
        return;
    }
#endif

    for(int i=0;i<ROW_CNT;i++)
    {
        if(last_ks_scanning_buff[i]!=now_ks_scanning_buff[i])
        {
              for(int k=0;k<31;k++)
              {
                  unsigned int now_bit=now_ks_scanning_buff[i]&(1<<k);
                    if((last_ks_scanning_buff[i]&(1<<k))!=now_bit)
                    {
                        if(now_bit)
                        {
                            printf("row=%d ,col=%d, is press\r\n", i, k);
                        }
                        else
                        {
                            printf("row=%d ,col=%d is release \r\n", i, k);
                        }
                    }
              }
            last_ks_scanning_buff[i]=now_ks_scanning_buff[i];
        }
    }
}

#endif

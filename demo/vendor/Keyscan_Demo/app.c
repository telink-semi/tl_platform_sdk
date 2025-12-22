/********************************************************************************************************
 * @file    app.c
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
#if(KEYCAN_MODE_TEST   ==     KEYSCAN_AUTO_MODE)
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

volatile int row = -1, col = -1;

volatile unsigned char g_key_value[256] = {0};
volatile unsigned char g_key_value_rptr = 0;
volatile unsigned char g_key_value_wptr = 0;

volatile unsigned char g_keyscan_error_flag = 0; //1 indicates that the data stored in the interrupt is abnormal.

#if (KEYSCAN_MODE != KEYSCAN_NDMA)
    #define DMA_SIZE (ROW_CNT * 4)

unsigned int ks_buffer[DMA_SIZE / 4] = {0};
#endif
void user_init(void)
{
    keyscan_set_martix(g_ks_row, ROW_CNT, g_ks_col, COL_CNT, KS_INT_PIN_PULLDOWN);
    keyscan_init(DEBOUNCE_PERIOD_8MS, 1, TRIPLE_SCAN_TIMES);

    keyscan_enable();

    plic_interrupt_enable(IRQ_KEY_SCAN);
    core_interrupt_enable();

    printf("\n Keyscan Test Start! Please press button. \n");
}

void main_loop(void)
{

    while (1) {
        if (g_key_value_rptr == g_key_value_wptr) {
            break;
        }
        if (g_key_value[g_key_value_rptr] != KESYCAN_END_FLAG) {
            row = g_key_value[g_key_value_rptr] >> 5;
            col = g_key_value[g_key_value_rptr] & 0x1f;

            printf("%d row %d column\n", row, col);
        }
        g_key_value_rptr = (g_key_value_rptr + 1) & 0xff;
    }

#if (KEYSCAN_TEST_SUSPEND)
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_KEY_SCAN, 0);
#endif
}

/**
 * @brief        This function serves to handle the interrupt of MCU.
 * @return       none
 */
_attribute_ram_code_sec_noinline_ void keyscan_irq_handler(void)
{
    if (keyscan_get_irq_status()) {
        keyscan_clr_irq_status();

        unsigned char rptr    = 0;
        unsigned char wptr    = 0;
        unsigned char key_val = 0;

        while (1) {
            rptr    = keyscan_get_rptr();
            wptr    = keyscan_get_wptr();
            key_val = keyscan_get_ks_value();

            g_key_value[g_key_value_wptr] = key_val;
            g_key_value_wptr              = (g_key_value_wptr + 1) & 0xff;

            if (key_val == KESYCAN_END_FLAG) { //scan done
                break;
            } else if (rptr == wptr) {
                g_keyscan_error_flag = 1;
                break;
            }
        }
    }
}
PLIC_ISR_REGISTER(keyscan_irq_handler, IRQ_KEY_SCAN)
#endif

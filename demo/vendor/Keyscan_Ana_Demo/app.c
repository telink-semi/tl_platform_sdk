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

#define BUFFER_SIZE (256)

#if (KS_TEST_MODE == KEYSCAN_TEST_1XADC_8K_ONCE)

#define KEYSCAN_ADC_BUFFER_SIZE (BUFFER_SIZE / 2)
short adc_buffer[KEYSCAN_ADC_BUFFER_SIZE] = {0};

#elif (KS_TEST_MODE == KEYSCAN_TEST_2XADC_8K_ONCE)

#define KEYSCAN_ADC_BUFFER_SIZE (BUFFER_SIZE / 2)
short adc_buffer[KEYSCAN_ADC_BUFFER_SIZE] = {0};

#elif (KS_TEST_MODE == KEYSCAN_TEST_2XADC_8K_TWICE_M1)

#define KEYSCAN_ADC_BUFFER_SIZE (BUFFER_SIZE)
short adc_buffer[KEYSCAN_ADC_BUFFER_SIZE] = {0};

#elif (KS_TEST_MODE == KEYSCAN_TEST_2XADC_8K_TWICE_M2)
#define KEYSCAN_ADC_BUFFER_SIZE (BUFFER_SIZE)
short adc_buffer[KEYSCAN_ADC_BUFFER_SIZE] = {0};

#if (!KS_DMA_LLP_ENABLE)
volatile unsigned char irq_cnt = 0;
#endif

#endif

/* update threshold according to the real hall value */
ks_ana_threshold_t ks_ana_threshold = {
    .release_threshold = 768,
    .press_threshold = 864
};

/* update gpio pin according to the hardware design */
ks_ana_gpio_pin_t ks_ana_gpio_pin = {
    .pin_group_id = KS_PIN_GROUP_ID_0,
    .ana_switch_enable_pin = GPIO_PH2,
    .ana_switch_channel_pin = {GPIO_PE3, GPIO_PE4, GPIO_PE5, GPIO_PE6},
    .hall_rows_power_pin = {GPIO_PH3, GPIO_PH4, GPIO_PH5, GPIO_PH6, GPIO_PH7, GPIO_PE0, GPIO_PE1, GPIO_PE2}
};

/* update this map according to the hardware design */
const ks_ana_data_t ks_ana_data_map[KS_FIXED_SCAN_TOTAL_KEYS] = {
    {0, "M"},       {1, "?"},      {2, "+"},      {3, "."},      {4, "N"},       {5, "Ctrl"},  {6, "9"},           {7, "0"},
    {8, "B"},       {9, "Fn"},     {10, "8"},     {11, "Enter"}, {12, "V"},      {13, "Alt"},  {14, "7"},          {15, "3"},
    {16, "C"},      {17, "Space"}, {18, "-"},     {19, "2"},     {20, "X"},      {21, "Alt"},  {22, "*"},          {23, "1"},
    {24, "Z"},      {25, "Win"},   {26, "/"},     {27, "6"},     {28, "Shift"},  {29, "Ctrl"}, {30, "Num"},        {31, "5"},
    {32, ","},      {33, "?"},     {34, "4"},     {35, ""},      {36, "."},      {37, "?"},    {38, ""},           {39, ""},
    {40, "/"},      {41, ""},      {42, ""},      {43, ""},      {44, "Shift"},  {45, ""},     {46, ""},           {47, ""},
    {48, "?"},      {49, ""},      {50, ""},      {51, ""},      {52, ""},       {53, ""},     {54, ""},           {55, ""},
    {56, ""},       {57, ""},      {58, ""},      {59, ""},      {60, ""},       {61, ""},     {62, ""},           {63, ""},
    {64, "J"},      {65, "U"},     {66, "7"},     {67, "F7"},    {68, "H"},      {69, "Y"},    {70, "6"},          {71, "F6"},
    {72, "G"},      {73, "T"},     {74, "5"},     {75, "F5"},    {76, "F"},      {77, "R"},    {78, "4"},          {79, "F4"},
    {80, "D"},      {81, "E"},     {82, "3"},     {83, "F3"},    {84, "S"},      {85, "W"},    {86, "2"},          {87, "F2"},
    {88, "A"},      {89, "Q"},     {90, "1"},     {91, "F1"},    {92, "CapsLk"}, {93, "Tab"},  {94, "~"},          {95, "Esc"},
    {96, "K"},      {97, "I"},     {98, "8"},     {99, "F8"},    {100, "L"},     {101, "O"},   {102, "9"},         {103, "F9"},
    {104, ";"},     {105, "P"},    {106, "0"},    {107, "F10"},  {108, "'"},     {109, "["},   {110, "-"},         {111, "F11"},
    {112, "Enter"}, {113, "]"},    {114, "="},    {115, "F12"},  {116, ""},      {117, "\\"},  {118, "Backspace"}, {119, "Home"},
    {120, ""},      {121, ""},     {122, "PgDn"}, {123, "Del"},  {124, ""},      {125, ""},    {126, "PgUp"},      {127, "Ins"}
};
static ks_ana_value_t ks_ana_value;
volatile unsigned char cols = 0, rows = 0;
extern ks_ana_threshold_t ks_ana_threshold_g;

int ks_get_value_and_debounce(ks_ana_mode_e ks_ana_mode, short *data, unsigned int index, unsigned int size, unsigned int len, unsigned char col, unsigned char row);
int ks_ana_get_keyvalue_from_meta_data(ks_ana_mode_e ks_ana_mode, short *data);
void ks_ana_get_hall_max_min_value(short *data, unsigned int times);

void user_init(void)
{

#if (KS_TEST_MODE == KEYSCAN_TEST_1XADC_8K_ONCE)
    #if (!KS_DMA_LLP_ENABLE)
    ks_ana_set_rx_dma_config(ADC0,KS_ANA_ADC0_DMA_CHN);
    ks_ana_receive_dma(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);

    #else
    ks_ana_rx_dma_chain_init(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);
    #endif
#else
    #if (!KS_DMA_LLP_ENABLE)
    ks_ana_set_rx_dma_config(ADC0,KS_ANA_ADC0_DMA_CHN);
    ks_ana_receive_dma(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);

    ks_ana_set_rx_dma_config(ADC1,KS_ANA_ADC1_DMA_CHN);
    ks_ana_receive_dma(ADC1, KS_ANA_ADC1_DMA_CHN, (unsigned short*)(adc_buffer + KEYSCAN_ADC_BUFFER_SIZE / 2), KEYSCAN_ADC_BUFFER_SIZE);

    #else
    ks_ana_rx_dma_chain_init(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);
    ks_ana_rx_dma_chain_init(ADC1, KS_ANA_ADC1_DMA_CHN, (unsigned short*)(adc_buffer + KEYSCAN_ADC_BUFFER_SIZE / 2), KEYSCAN_ADC_BUFFER_SIZE);
    #endif
#endif
    ks_ana_init(ks_ana_gpio_pin, KS_TEST_MODE, HALL_INIT_TIME, ks_ana_threshold);

#if (!KS_DMA_LLP_ENABLE)
    plic_interrupt_enable(IRQ_KEY_SCAN);
    core_interrupt_enable();
#endif

    printf("Keyscan-A done.\n");
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop(void)
{
    ks_ana_get_keyvalue_from_meta_data(KS_TEST_MODE, adc_buffer);

#if KS_TEST_THRESHOLD
    ks_ana_get_hall_max_min_value(adc_buffer, 500);
#endif
}

#if (!KS_DMA_LLP_ENABLE)
_attribute_ram_code_sec_ void keyscan_ana_irq_handler(void)
{
    unsigned char irq_status = ks_ana_get_irq_status();
    if (irq_status & (FLD_KS_FRM_END_STA | FLD_KS_FRM_END1_STA)) {
        ks_ana_clr_irq_status(irq_status);

    #if (KS_TEST_MODE == KEYSCAN_TEST_1XADC_8K_ONCE)
        ks_ana_set_rx_dma_config(ADC0,KS_ANA_ADC0_DMA_CHN);
        ks_ana_receive_dma(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);
    #elif (KS_TEST_MODE == KEYSCAN_TEST_2XADC_8K_TWICE_M2)//this mode will trigger twice interrupt
        irq_cnt++;
        if (irq_cnt % 2 == 0) {
            irq_cnt = 0;

            ks_ana_set_rx_dma_config(ADC0,KS_ANA_ADC0_DMA_CHN);
            ks_ana_receive_dma(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);

            ks_ana_set_rx_dma_config(ADC1,KS_ANA_ADC1_DMA_CHN);
            ks_ana_receive_dma(ADC1, KS_ANA_ADC1_DMA_CHN, (unsigned short*)(adc_buffer + KEYSCAN_ADC_BUFFER_SIZE / 2), KEYSCAN_ADC_BUFFER_SIZE);
        }
    #else
        ks_ana_set_rx_dma_config(ADC0,KS_ANA_ADC0_DMA_CHN);
        ks_ana_receive_dma(ADC0, KS_ANA_ADC0_DMA_CHN, (unsigned short*)adc_buffer, KEYSCAN_ADC_BUFFER_SIZE);

        ks_ana_set_rx_dma_config(ADC1,KS_ANA_ADC1_DMA_CHN);
        ks_ana_receive_dma(ADC1, KS_ANA_ADC1_DMA_CHN, (unsigned short*)(adc_buffer + KEYSCAN_ADC_BUFFER_SIZE / 2), KEYSCAN_ADC_BUFFER_SIZE);
    #endif
    }
}
PLIC_ISR_REGISTER(keyscan_ana_irq_handler, IRQ_KEY_SCAN)
#endif


/**
 * @brief      This function serves to debounce.
 * @param[in]  ks_ana_mode          - the Analog Keyscan mode
 * @param[in]  data                 - the meta data
 * @param[in]  index                - the key index in data
 * @param[in]  size                 - the meta data size
 * @param[in]  len                  - the meta data len
 * @param[out] col                  - the key col
 * @param[out] row                  - the key row
 * @return     none
 */
int ks_get_value_and_debounce(ks_ana_mode_e ks_ana_mode, short *data, unsigned int index, unsigned int size, unsigned int len, unsigned char col, unsigned char row)
{
    memset(&ks_ana_value.now_key_bits[0], 0, KS_FIXED_ROWS);
    unsigned char press_flag = 1;
    unsigned char unused_flag = 0;
    int key = -1;

    if (unused_flag != 1) {
        if ((ks_ana_mode == KEYSCAN_2XADC_8K_ONCE_MODE)||   (ks_ana_mode == KEYSCAN_1XADC_8K_ONCE_MODE)) {
            if (data[index] > ks_ana_threshold_g.release_threshold && data[index] < ks_ana_threshold_g.press_threshold) {
                press_flag = 1;
            } else if (data[index] < ks_ana_threshold_g.release_threshold) {
                press_flag = 0;
            } else if (data[index] > ks_ana_threshold_g.press_threshold) {
                press_flag = 2;
            }
        } else if (ks_ana_mode == KEYSCAN_2XADC_8K_TWICE_M1_MODE || ks_ana_mode == KEYSCAN_2XADC_8K_TWICE_M2_MODE) {
            if (((data[index] < ks_ana_threshold_g.press_threshold) && (data[index] > ks_ana_threshold_g.release_threshold)) &&
                ((data[index + 4] < ks_ana_threshold_g.press_threshold)&&((data[index+4] > ks_ana_threshold_g.release_threshold)))) {
                press_flag = 1;
            } else if ((data[index] < ks_ana_threshold_g.release_threshold) && (data[index + 4] < ks_ana_threshold_g.release_threshold)) {
                press_flag = 0;
            } else {
                press_flag = 2;
            }
            if(press_flag == 1  || press_flag == 0){
                if(col>=8){
                    col= col-8+4;
                }
                    index = ((index/8)/2)*8+col;
            }
        }
        if (press_flag == 1) {
            ks_ana_value.now_key_bits[row] |= (1 << col);
        } else if (press_flag == 0) {
            ks_ana_value.now_key_bits[row] &= (~(1 << col));
        }
        if ((ks_ana_value.last_key_bits[row] & (1 << col)) != (ks_ana_value.now_key_bits[row] & (1 << col))) {
            key = index % size / len;
            printf("ADC0 get key, number = %d\n", key);
        }
    }
    unused_flag = 0;
    return key;
}

/**
 * @brief      This function serves to get key value from meta data.
 * @param[in]  ks_ana_mode  - the keyscan mode
 * @param[in]  data     - the meta data
 * @return     key
 */
int ks_ana_get_keyvalue_from_meta_data(ks_ana_mode_e ks_ana_mode, short *data)
{
   volatile unsigned int size = 0, len = 0;


    if (ks_ana_mode == KEYSCAN_1XADC_8K_ONCE_MODE) {
        size = KS_ADC0_SCAN_ONCE_DATA_SIZE;
        len = KS_ADC0_SCAN_ONCE_DATA_LEN;

        cols = KS_FIXED_COLS;
        rows = KS_FIXED_ROWS;
    } else if (ks_ana_mode == KEYSCAN_2XADC_8K_ONCE_MODE) {
        size = KS_ADC0_1_SCAN_ONCE_DATA_SIZE;
        len = KS_ADC0_1_SCAN_ONCE_DATA_LEN;

        cols = KS_FIXED_COLS;
        rows = KS_FIXED_ROWS;
    } else {
        size = KS_ADC0_1_SCAN_TWICE_DATA_SIZE;
        len = KS_ADC0_1_SCAN_TWICE_DATA_LEN;

        cols = KS_FIXED_COLS * 2;
        rows = KS_FIXED_ROWS;
    }

    int key = -1;

    for (volatile unsigned char row = 0; row < rows; row++) {
      volatile unsigned char col = 0;
       volatile unsigned int index = 0;

        if ((ks_ana_mode == KEYSCAN_2XADC_8K_ONCE_MODE)  || (ks_ana_mode == KEYSCAN_1XADC_8K_ONCE_MODE)) {
            for (col = 0; col < cols; col++) {
                index = row * cols + col;
                key = ks_get_value_and_debounce(ks_ana_mode, data, index, size, len, col, row);
            }
        } else if ((ks_ana_mode == KEYSCAN_2XADC_8K_TWICE_M1_MODE) || (ks_ana_mode == KEYSCAN_2XADC_8K_TWICE_M2_MODE)) {
            volatile unsigned char t = 0;
            while(col < cols) {
                index = row * cols + t * 8;  //0/8   16/24  32/40  48/56  64/72
                t++;

                for (volatile unsigned char k = 0; k < 4; k++) {
                    if (index + 1 < rows * cols) {

                        key = ks_get_value_and_debounce(ks_ana_mode, data, index, size, len, col+k, row);
                        index++;

                    }
                }

                col += 8;

            }
        }

        if (ks_ana_value.last_key_bits[row] != ks_ana_value.now_key_bits[row]) {
            ks_ana_value.last_key_bits[row] = ks_ana_value.now_key_bits[row];
        }
    }

    return key;
}

/**
 * @brief      This function serves to get halls release state max and min value on keyboard.
 * @param[in]  data     - the meta data
 * @param[in]  times    - times
 * @return     none
 */
void ks_ana_get_hall_max_min_value(short *data, unsigned int times)
{
    unsigned char unused_flag = 0;
    unsigned int cnt = 0;
    int max = 0, min = 65535, sum_max = 0, sum_min = 0;

    for (int row = 0; row < KS_FIXED_ROWS; row++) {
        for (int col = 0; col < KS_FIXED_COLS; col++) {
            unsigned char index = row * 8 + col;

            if (unused_flag != 1) {
                max = max > data[index] ? max : data[index];
                min = min < data[index] ? min : data[index];

                unused_flag = 0;
            }
        }
    }

    if (cnt < times) {
        cnt++;
        sum_max += max;
        sum_min += min;
    }
}
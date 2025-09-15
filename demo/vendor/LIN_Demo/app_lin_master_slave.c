/********************************************************************************************************
 * @file    app_lin_master_slave.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#if (LIN_TEST_MODE == LIN_TEST_MASTER_SLAVE)

#define DMA_ENABLE        0
#define USE_HW_FILTER_PID 0

lin_hw_init_para_t lin_module0 = {
    .lin_num  = LIN0,
    .role     = LIN_MASTER_NODE,
    .en_pin   = LIN0_TEST_EN_PIN,
    .tx_pin   = LIN0_TEST_TX_PIN,
    .rx_pin   = LIN0_TEST_RX_PIN,
    .baudrate = LIN_TEST_BAUDRATE,
    .hw_cfg   =
    {
        .break_len           = LIN_TEST_BREAK_LEN,
        .break1_len          = LIN_TEST_BREAK1_LEN,
        .time_base           = LIN_TEST_TIMEBASE,
        .jitter_us           = 30,   //max 30us
        .inactive_timeout_ms = 4000, //max 10000ms
        .rx_smp_pos          = LIN_RX_SMP_POS_CENTER,
    },
    .dma_cfg =
    {
        .dma_mode_enable = DMA_ENABLE,
        .tx_dma_chn      = DMA0,
        .rx_dma_chn      = DMA1,
    },
    .checksum_cfg =
    {
        .checksum_sw_enable = false,
        .sum_func           = 0,
    },
};

lin_hw_init_para_t lin_module1 =
{
    .lin_num  = LIN1,
    .role     = LIN_SLAVE_NODE,
    .en_pin   = LIN1_TEST_EN_PIN,
    .tx_pin   = LIN1_TEST_TX_PIN,
    .rx_pin   = LIN1_TEST_RX_PIN,
    .baudrate = LIN_TEST_BAUDRATE,
    .pclk     = 36 * 1000 * 1000,
    .hw_cfg   =
    {
        .break_len           = LIN_TEST_BREAK_LEN,
        .break1_len          = LIN_TEST_BREAK1_LEN,
        .time_base           = LIN_TEST_TIMEBASE,
        .jitter_us           = 30,   //max 30us
        .inactive_timeout_ms = 4000, //max 10000ms
        .rx_smp_pos          = LIN_RX_SMP_POS_CENTER,
    },
    .dma_cfg =
    {
        .dma_mode_enable = DMA_ENABLE,
        .tx_dma_chn      = DMA2,
        .rx_dma_chn      = DMA3,
    },
    .checksum_cfg =
    {
        .checksum_sw_enable = false,
        .sum_func           = 0,
    },
};

static lin_handle_t_ptr s_handle0 = 0;
static lin_handle_t_ptr s_handle1 = 0;

lin_frame_item_t s_frame_list0[] = {
    /* If LIN_TEST_BAUDRATE is 20K, (slot_cnt 3) * (LIN_TEST_TIMEBASE 5ms) = 15ms is enough to send a frame,
     * if using lower BAUDRATE, higher slot_cnt or higher LIN_TEST_TIMEBASE should be selected.
     */
    {LIN_ACTION_TX, 0x01, 1, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_TX, 0x02, 2, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_TX, 0x03, 3, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_TX, 0x04, 4, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_TX, 0x05, 5, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x06, 6, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x07, 7, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x08, 8, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},

    {LIN_ACTION_RX, 0x11, 1, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_RX, 0x12, 2, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_RX, 0x13, 3, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_RX, 0x14, 4, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
    {LIN_ACTION_RX, 0x15, 5, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x16, 6, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x17, 7, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x18, 8, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
};

lin_schedule_t     proc_table0    = {0, s_frame_list0, sizeof(s_frame_list0) / sizeof(s_frame_list0[0]), 0};
lin_schedule_t_ptr cur_proc_table = &proc_table0;

#if (USE_HW_FILTER_PID)
static unsigned char s_frame_index_hit = 0xff;
#else
static int s_frame_index_hit = -1;
#endif

static lin_frame_item_t_ptr s_frame_hit = 0;

lin_frame_item_t s_frame_list1[] = {
    {LIN_ACTION_RX, 0x01, 1, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_RX, 0x02, 2, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_RX, 0x03, 3, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_RX, 0x04, 4, {0x00},                                           LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_RX, 0x05, 5, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_RX, 0x06, 6, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_RX, 0x07, 7, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_RX, 0x08, 8, {0x00},                                           LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},

    {LIN_ACTION_TX, 0x11, 1, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_TX, 0x12, 2, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_TX, 0x13, 3, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_TX, 0x14, 4, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
    {LIN_ACTION_TX, 0x15, 5, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_TX, 0x16, 6, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_TX, 0x17, 7, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
    {LIN_ACTION_TX, 0x18, 8, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 0, 0, 0},
};

int get_frame_index(unsigned char id, lin_frame_item_t_ptr frame_list, int frame_list_size)
{
    int ret = -1;
    for (int i = 0; i < frame_list_size; i++) {
        if (frame_list[i].id == id) {
            ret = i;
            break;
        }
    }

    return ret;
}

bool init_filter_pid_table(void)
{
#if (USE_HW_FILTER_PID)
    bool ret = false;
    lin_slave_clr_pid_filter_table(s_handle1);
    unsigned char frame_list_len = sizeof(s_frame_list1) / sizeof(s_frame_list1[0]);

    if (frame_list_len <= 16) {
        for (unsigned char i = 0; i < frame_list_len; i++) {
            bool tx_en = (s_frame_list1[i].action == LIN_ACTION_TX);
            lin_slave_add_2_pid_filter_table(s_handle1, s_frame_list1[i].id, s_frame_list1[i].len, tx_en);
        }
        lin_slave_enable_pid_filter_table(s_handle1);
        ret = true;
    }

    return ret;
#else
    return true;
#endif
}

#define DEBUG_PIN LED2

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1); //enable output
    gpio_input_dis(LED1); //disable input

    gpio_function_en(DEBUG_PIN);
    gpio_output_en(DEBUG_PIN); //enable output
    gpio_input_dis(DEBUG_PIN); //disable input

    s_handle0 = lin_hw_init(&lin_module0);
    s_handle1 = lin_hw_init(&lin_module1);
    if (!s_handle0 || !s_handle1 || !init_filter_pid_table()) {
        while (1);
    }

    lin_set_irq_mask(s_handle0, FLD_LIN_MASK_RESP_TX_DONE_RW | FLD_LIN_MASK_RESP_RX_DONE_RW | FLD_LIN_MASK_RESP_TIMEOUT_RW | FLD_LIN_MASK_RESP_CHECKSUM_ERR_RW | FLD_LIN_MASK_REC_HEADER_RW | FLD_LIN_MASK_COMM_FRAME_SLOT_DONE_RW);
    lin_set_irq_mask(s_handle1, FLD_LIN_MASK_RESP_TX_DONE_RW | FLD_LIN_MASK_RESP_RX_DONE_RW | FLD_LIN_MASK_RESP_TIMEOUT_RW | FLD_LIN_MASK_HEADER_TIMEOUT_RW | FLD_LIN_MASK_RESP_CHECKSUM_ERR_RW | FLD_LIN_MASK_REC_HEADER_RW | FLD_LIN_MASK_REC_HEADER_ERR_RW);
    plic_interrupt_enable(IRQ_LIN0);
    plic_interrupt_enable(IRQ_LIN1);
    core_interrupt_enable();
    lin_set_slot(s_handle0, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
    lin_master_send_header(s_handle0, cur_proc_table->frame_list[cur_proc_table->item_index].id);
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}

volatile unsigned int irq0_cnt                = 0,
                      irq0_cnt_header_done    = 0,
                      irq0_cnt_checksum_error = 0,
                      irq0_cnt_resp_tx_done   = 0,
                      irq0_cnt_resp_rx_done   = 0,
                      irq0_cnt_resp_timeout   = 0,
                      irq0_cnt_slot_done      = 0;

/**
 * @brief       This function serves to handle the interrupt of MCU
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void lin0_irq_handler(void)
{
    irq0_cnt++;
    if (lin_get_irq_status(s_handle0)) {
        if (lin_get_irq_status(s_handle0) & FLD_LIN_REC_HIT_PID_W1C) {
            irq0_cnt_header_done++;
            lin_clr_irq_status(s_handle0, FLD_LIN_REC_HIT_PID_W1C);
            if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_TX) {
                lin_send_response(s_handle0,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].data,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].len,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type);
                lin_set_response_discard(s_handle0->lin_num);
            } else if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_RX) {
                lin_start_recv_response(s_handle0,
                                        cur_proc_table->frame_list[cur_proc_table->item_index].len,
                                        cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type);
            }
        }

        if (lin_get_irq_status(s_handle0) & FLD_LIN_RESP_CHECKSUM_ERR_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq0_cnt_checksum_error++;
            lin_clr_irq_status(s_handle0, FLD_LIN_RESP_CHECKSUM_ERR_W1C);
            if (cur_proc_table->frame_list[cur_proc_table->item_index].conflict_proc_schedule) {
                cur_proc_table             = cur_proc_table->frame_list[cur_proc_table->item_index].conflict_proc_schedule;
                cur_proc_table->item_index = 0;
            }
        }

        if (lin_get_irq_status(s_handle0) & (FLD_LIN_RESP_TX_DONE_W1C | FLD_LIN_RESP_RX_DONE_W1C | FLD_LIN_RESP_TIMEOUT_W1C)) {
            if (lin_get_irq_status(s_handle0) & FLD_LIN_RESP_TX_DONE_W1C) {
                irq0_cnt_resp_tx_done++;
                lin_clr_irq_status(s_handle0, FLD_LIN_RESP_TX_DONE_W1C);
            }

            if (lin_get_irq_status(s_handle0) & FLD_LIN_RESP_RX_DONE_W1C) {
                irq0_cnt_resp_rx_done++;
                lin_clr_irq_status(s_handle0, FLD_LIN_RESP_RX_DONE_W1C);

                if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_RX) {
                    lin_get_response_data(s_handle0, cur_proc_table->frame_list[cur_proc_table->item_index].data, cur_proc_table->frame_list[cur_proc_table->item_index].len, cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type, 0);
                }
            }

            if (lin_get_irq_status(s_handle0) & FLD_LIN_RESP_TIMEOUT_W1C) {
                gpio_toggle(DEBUG_PIN);
                irq0_cnt_resp_timeout++;
                lin_clr_irq_status(s_handle0, FLD_LIN_RESP_TIMEOUT_W1C);
                lin_set_response_discard(s_handle0->lin_num);
            }

            cur_proc_table->item_index++;
            if (cur_proc_table->item_index >= cur_proc_table->item_cnt) {
                if (cur_proc_table->next_proc_schedule) {
                    cur_proc_table = cur_proc_table->next_proc_schedule;
                    cur_proc_table->item_index++;
                }
                cur_proc_table->item_index %= cur_proc_table->item_cnt;
            }
        }

        if (lin_get_irq_status(s_handle0) & FLD_LIN_COMM_FRAME_SLOT_DONE_W1C) {
            irq0_cnt_slot_done++;
            lin_clr_irq_status(s_handle0, FLD_LIN_COMM_FRAME_SLOT_DONE_W1C);
            lin_set_slot(s_handle0, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
            lin_master_send_header(s_handle0, cur_proc_table->frame_list[cur_proc_table->item_index].id);
        }
    }
}

PLIC_ISR_REGISTER(lin0_irq_handler, IRQ_LIN0)

volatile unsigned int irq1_cnt                = 0,
                      irq1_cnt_header_done    = 0,
                      irq1_cnt_checksum_error = 0,
                      irq1_cnt_resp_tx_done   = 0,
                      irq1_cnt_resp_rx_done   = 0,
                      irq1_cnt_resp_timeout   = 0,
                      irq1_cnt_header_timeout = 0,
                      irq1_cnt_pid_error      = 0;

/**
 * @brief       This function serves to handle the interrupt of MCU
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void lin_irq_handler(void)
{
    irq1_cnt++;
    if (lin_get_irq_status(s_handle1)) {
        if (lin_get_irq_status(s_handle1) & FLD_LIN_REC_HIT_PID_W1C) {
            irq1_cnt_header_done++;
            lin_clr_irq_status(s_handle1, FLD_LIN_REC_HIT_PID_W1C);
    #if (USE_HW_FILTER_PID)
            s_frame_index_hit = lin_slave_get_filter_table_match_idx(s_handle1);
            if (s_frame_index_hit < (sizeof(s_frame_list1) / sizeof(s_frame_list1[0])))
    #else
            s_frame_index_hit = get_frame_index(lin_get_id(s_handle1), s_frame_list1, sizeof(s_frame_list1) / sizeof(s_frame_list1[0]));
            if (s_frame_index_hit != -1)
    #endif
            {
                s_frame_hit = &(s_frame_list1[s_frame_index_hit]);

                if (s_frame_hit->action == LIN_ACTION_TX) {
                    lin_send_response(s_handle1, s_frame_hit->data, s_frame_hit->len, s_frame_hit->checksum_type);
                } else if (s_frame_hit->action == LIN_ACTION_RX) {
                    lin_start_recv_response(s_handle1, s_frame_hit->len, s_frame_hit->checksum_type);
                } else {
                    lin_discard_response(s_handle1);
                }
            } else {
                s_frame_hit = 0;
                lin_discard_response(s_handle1);
            }
        }

        if (lin_get_irq_status(s_handle1) & FLD_LIN_HEADER_TIMEOUT_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq1_cnt_header_timeout++;
            lin_clr_irq_status(s_handle1, FLD_LIN_HEADER_TIMEOUT_W1C);
        }

        if (lin_get_irq_status(s_handle1) & FLD_LIN_RESP_CHECKSUM_ERR_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq1_cnt_checksum_error++;
            lin_clr_irq_status(s_handle1, FLD_LIN_RESP_CHECKSUM_ERR_W1C);
        }

        if (lin_get_irq_status(s_handle1) & FLD_LIN_RESP_TIMEOUT_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq1_cnt_resp_timeout++;
            lin_clr_irq_status(s_handle1, FLD_LIN_RESP_TIMEOUT_W1C);
        }

        if (lin_get_irq_status(s_handle1) & (FLD_LIN_RESP_TX_DONE_W1C | FLD_LIN_RESP_RX_DONE_W1C)) {
            if (lin_get_irq_status(s_handle1) & FLD_LIN_RESP_TX_DONE_W1C) {
                irq1_cnt_resp_tx_done++;
                lin_clr_irq_status(s_handle1, FLD_LIN_RESP_TX_DONE_W1C);
            }

            if (lin_get_irq_status(s_handle1) & FLD_LIN_RESP_RX_DONE_W1C) {
                irq1_cnt_resp_rx_done++;
                lin_clr_irq_status(s_handle1, FLD_LIN_RESP_RX_DONE_W1C);
                if (s_frame_hit) {
                    lin_get_response_data(s_handle1, s_frame_hit->data, s_frame_hit->len, s_frame_hit->checksum_type, 0);
                }
            }
        }

        if (lin_get_irq_status(s_handle1) & FLD_LIN_REC_HIT_PID_ERR_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq1_cnt_pid_error++;
            lin_clr_irq_status(s_handle1, FLD_LIN_REC_HIT_PID_ERR_W1C);
        }
    }
}

PLIC_ISR_REGISTER(lin_irq_handler, IRQ_LIN1)

#endif

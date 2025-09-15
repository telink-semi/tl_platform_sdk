/********************************************************************************************************
 * @file    app_lin_master_schedule.c
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

#if (LIN_TEST_MODE == LIN_TEST_MASTER_SCHEDULE)

#define LIN_NUM0       0 //LIN0
#define LIN_NUM1       1 //LIN1

#define LIN_NUM_SELECT LIN_NUM0

#if(LIN_NUM_SELECT == LIN_NUM0)
    #define IRQ_SELECT     IRQ_LIN0
#else
    #define IRQ_SELECT     IRQ_LIN1
#endif

lin_hw_init_para_t lin_module0 =
{
    .lin_num  = LIN_NUM_SELECT,
    .role     = LIN_MASTER_NODE,
#if(LIN_NUM_SELECT == LIN_NUM0)
    .en_pin   = LIN0_TEST_EN_PIN,
    .tx_pin   = LIN0_TEST_TX_PIN,
    .rx_pin   = LIN0_TEST_RX_PIN,
#else
    .en_pin   = LIN1_TEST_EN_PIN,
    .tx_pin   = LIN1_TEST_TX_PIN,
    .rx_pin   = LIN1_TEST_RX_PIN,
#endif
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
        .dma_mode_enable = false,
        .tx_dma_chn      = DMA0,
        .rx_dma_chn      = DMA1,
    },
    .checksum_cfg =
    {
        .checksum_sw_enable = true,
        .sum_func           = &lin_software_checksum,
    },
};

static lin_handle_t_ptr s_handle = 0;

lin_frame_item_t frame_list[] = {
    /* If LIN_TEST_BAUDRATE is 20K, (slot_cnt 3) * (LIN_TEST_TIMEBASE 5ms) = 15ms is enough to send a frame,
     * if using lower BAUDRATE, higher slot_cnt or higher LIN_TEST_TIMEBASE should be selected.
     */
    {LIN_ACTION_TX, 0x01, 1, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x02, 2, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x03, 3, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x04, 4, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x05, 5, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x06, 6, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x07, 7, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_TX, 0x08, 8, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},

    {LIN_ACTION_RX, 0x11, 1, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x12, 2, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x13, 3, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x14, 4, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x15, 5, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x16, 6, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x17, 7, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
    {LIN_ACTION_RX, 0x18, 8, {0x00}, LIN_CHECKSUM_TYPE_CLASSIC, 3, 0, 0},
};

lin_schedule_t     proc_table0    = {0, frame_list, sizeof(frame_list) / sizeof(frame_list[0]), 0};
lin_schedule_t_ptr cur_proc_table = &proc_table0;

void update_schedule_table(void)
{
    unsigned char index;

    cur_proc_table->item_index += s_handle->table_size;
    index = cur_proc_table->item_index + s_handle->table_size - 1;
    cur_proc_table->item_index %= cur_proc_table->item_cnt;

    if (index >= cur_proc_table->item_cnt) {
        if (cur_proc_table->next_proc_schedule) {
            cur_proc_table = cur_proc_table->next_proc_schedule;
        }
    }

    lin_master_clr_schedule_table(s_handle);
    unsigned char remain_cnt = cur_proc_table->item_cnt - cur_proc_table->item_index;
    unsigned char cnt        = ((remain_cnt > 16) ? 16 : remain_cnt);

    for (unsigned char i = 0; i < cnt; i++) {
        index = i + cur_proc_table->item_index;
        lin_master_add_2_schedule_table(s_handle, cur_proc_table->frame_list[index].id, cur_proc_table->frame_list[index].slot_cnt);
    }

    lin_master_refresh_schedule_table(s_handle);
    lin_master_enable_schedule_table(s_handle);
}

#define DEBUG_PIN      LED2

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1); //enable output
    gpio_input_dis(LED1); //disable input

    gpio_function_en(DEBUG_PIN);
    gpio_output_en(DEBUG_PIN); //enable output
    gpio_input_dis(DEBUG_PIN); //disable input

    s_handle = lin_hw_init(&lin_module0);
    if (!s_handle) {
        while (1);
    }

    lin_set_irq_mask(s_handle, FLD_LIN_MASK_RESP_TX_DONE_RW | FLD_LIN_MASK_RESP_RX_DONE_RW | FLD_LIN_MASK_RESP_TIMEOUT_RW | FLD_LIN_MASK_RESP_CHECKSUM_ERR_RW | FLD_LIN_MASK_REC_HEADER_RW | FLD_LIN_MASK_COMM_FRAME_SLOT_DONE_RW | FLD_LIN_MASK_COMM_SCHEDULE_END_RW);
    plic_interrupt_enable(IRQ_SELECT);
    core_interrupt_enable();

    lin_rst_timebase(s_handle);
    lin_master_init_schedule_table(s_handle);
    update_schedule_table();
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}

volatile unsigned int irq_cnt                = 0,
                      irq_cnt_header_done    = 0,
                      irq_cnt_checksum_error = 0,
                      irq_cnt_resp_tx_done   = 0,
                      irq_cnt_resp_rx_done   = 0,
                      irq_cnt_resp_timeout   = 0,
                      irq_cnt_slot_done      = 0,
                      irq_cnt_schedule_end   = 0;

/**
 * @brief       This function serves to handle the interrupt of MCU
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void lin_irq_handler(void)
{
    irq_cnt++;
    if (lin_get_irq_status(s_handle)) {
        unsigned char index = lin_master_get_schedule_table_cur_idx(s_handle) + cur_proc_table->item_index;
        if (lin_get_irq_status(s_handle) & FLD_LIN_REC_HIT_PID_W1C) {
            irq_cnt_header_done++;
            lin_clr_irq_status(s_handle, FLD_LIN_REC_HIT_PID_W1C);

            if (cur_proc_table->frame_list[index].action == LIN_ACTION_TX) {
                lin_send_response(s_handle,
                                  cur_proc_table->frame_list[index].data,
                                  cur_proc_table->frame_list[index].len,
                                  cur_proc_table->frame_list[index].checksum_type);
            } else if (cur_proc_table->frame_list[index].action == LIN_ACTION_RX) {
                lin_start_recv_response(s_handle,
                                        cur_proc_table->frame_list[index].len,
                                        cur_proc_table->frame_list[index].checksum_type);
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_CHECKSUM_ERR_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq_cnt_checksum_error++;
            lin_clr_irq_status(s_handle, FLD_LIN_RESP_CHECKSUM_ERR_W1C);
            if (cur_proc_table->frame_list[index].conflict_proc_schedule) {
                lin_master_stop_schedule_table(s_handle);
                cur_proc_table             = cur_proc_table->frame_list[index].conflict_proc_schedule;
                cur_proc_table->item_index = 0;
                s_handle->table_size       = 0;
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TIMEOUT_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq_cnt_resp_timeout++;
            lin_clr_irq_status(s_handle, FLD_LIN_RESP_TIMEOUT_W1C);
        }

        if (lin_get_irq_status(s_handle) & (FLD_LIN_RESP_TX_DONE_W1C | FLD_LIN_RESP_RX_DONE_W1C)) {
            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TX_DONE_W1C) {
                irq_cnt_resp_tx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_TX_DONE_W1C);
            }

            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_RX_DONE_W1C) {
                irq_cnt_resp_rx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_RX_DONE_W1C);

                if (cur_proc_table->frame_list[index].action == LIN_ACTION_RX) {
                    lin_get_response_data(s_handle, cur_proc_table->frame_list[index].data, cur_proc_table->frame_list[index].len, cur_proc_table->frame_list[index].checksum_type, 0);
                }
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_COMM_FRAME_SLOT_DONE_W1C) {
            irq_cnt_slot_done++;
            lin_clr_irq_status(s_handle, FLD_LIN_COMM_FRAME_SLOT_DONE_W1C);
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_COMM_HIT_SCHEDULE_END_W1C) {
            irq_cnt_schedule_end++;
            lin_clr_irq_status(s_handle, FLD_LIN_COMM_HIT_SCHEDULE_END_W1C);
            update_schedule_table();
        }
    }
}

PLIC_ISR_REGISTER(lin_irq_handler, IRQ_SELECT)

#endif

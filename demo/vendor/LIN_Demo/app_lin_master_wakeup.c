/********************************************************************************************************
 * @file    app_lin_master_wakeup.c
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

#if (LIN_TEST_MODE == LIN_TEST_MASTER_WEAKUP)

#define LIN_NUM0       0 //LIN0
#define LIN_NUM1       1 //LIN1

#define LIN_NUM_SELECT LIN_NUM0

#if(LIN_NUM_SELECT == LIN_NUM0)
    #define IRQ_SELECT     IRQ_LIN0
#else
    #define IRQ_SELECT     IRQ_LIN1
#endif

/* Determined by whether the bus is idle or not, if it exceeds the inactive_timeout_ms time,
 * an inactive interrupt will be generated, and the PHY will be set in the interrupt to enter sleep.
 */
#define LIN_SLEEP_MODE_IRQ           0
#define LIN_SLEEP_MODE_FORCE         1 // Force LIN bus to sleep and wake up, loop test.
#define LIN_SLEEP_MODE_SEND_WAKEUP   2 // Send a wake up signal.

#define LIN_SLEEP_MODE               LIN_SLEEP_MODE_IRQ

lin_hw_init_para_t lin_module0 = {
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
        .checksum_sw_enable = false,
        .sum_func           = 0,
    },
};

static lin_handle_t_ptr s_handle = 0;

lin_frame_item_t frame_list[] = {
    {LIN_ACTION_TX, 0x01, 1, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, LIN_CHECKSUM_TYPE_ENHANCED, 3, 0, 0},
};

lin_schedule_t     proc_table0    = {0, frame_list, sizeof(frame_list) / sizeof(frame_list[0]), 0};
lin_schedule_t_ptr cur_proc_table = &proc_table0;

#define DEBUG_PIN LED2

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

    lin_set_irq_mask(s_handle, FLD_LIN_MASK_RESP_TX_DONE_RW | FLD_LIN_MASK_RESP_RX_DONE_RW | FLD_LIN_MASK_RESP_TIMEOUT_RW | FLD_LIN_MASK_RESP_CHECKSUM_ERR_RW |
                     FLD_LIN_MASK_REC_HEADER_RW | FLD_LIN_MASK_COMM_FRAME_SLOT_DONE_RW | FLD_LIN_MASK_REC_HEADER_ERR_RW);
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
    lin_set_irq_mask(s_handle, FLD_LIN_MASK_BUS_INACTIVE_RW);
#endif
    plic_interrupt_enable(IRQ_SELECT);
    core_interrupt_enable();

    lin_rst_timebase(s_handle);
    lin_set_slot(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
    lin_master_send_header(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].id);
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
volatile unsigned int irq_cnt_inactive_cnt  = 0;
volatile unsigned int lin_sleep_status      = 0; //0:wake up;1:sleep
#endif
void main_loop(void)
{
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
    while (lin_sleep_status) {
        delay_us(50);
        //Apply an external pull down signal at LIN BUS last at least 150us, giving MCU enough time to detect low level.
        if (gpio_get_level((gpio_pin_e)s_handle->rx_pin) == 0)
        {
            lin_set_hw_en(s_handle->lin_num, true); //weak up LIN bus
            lin_set_state(s_handle->lin_num, LIN_STATE_INIT);
            lin_set_state(s_handle->lin_num, LIN_STATE_RUN);
            lin_sleep_status = 0;
            lin_set_irq_mask(s_handle, FLD_LIN_MASK_BUS_INACTIVE_RW);
            delay_ms(150);;// To avoid the pull down signal on LIN BUS.
            lin_set_slot(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
            lin_master_send_header(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].id);
        }
    }
#elif (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_FORCE)
    while (1) {
        lin_set_hw_en(s_handle->lin_num, false); //LIN bus go to sleep
        lin_set_state(s_handle->lin_num, LIN_STATE_SLEEP);
        delay_us(50000);
        lin_set_hw_en(s_handle->lin_num, true); //weak up LIN bus
        lin_set_state(s_handle->lin_num, LIN_STATE_INIT);
        lin_set_state(s_handle->lin_num, LIN_STATE_RUN);
        lin_set_slot(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
        lin_master_send_header(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].id);
        delay_us(50000);
    }
#elif (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_SEND_WAKEUP)
    while (1) {
        delay_us(50000);
        lin_send_wakeup_signal(s_handle, 150);
    }
#endif
}

volatile unsigned int irq_cnt                = 0,
                      irq_cnt_header_done    = 0,
                      irq_cnt_pid_err        = 0,
                      irq_cnt_checksum_error = 0,
                      irq_cnt_resp_tx_done   = 0,
                      irq_cnt_resp_rx_done   = 0,
                      irq_cnt_resp_timeout   = 0,
                      irq_cnt_slot_done      = 0;


/**
 * @brief       This function serves to handle the interrupt of MCU
 * @param[in]   none
 * @return      none
 */

_attribute_ram_code_sec_ void lin_irq_handler(void)
{
    irq_cnt++;
    if (lin_get_irq_status(s_handle)) {
        if (lin_get_irq_status(s_handle) & FLD_LIN_REC_HIT_PID_W1C) {
            irq_cnt_header_done++;
            lin_clr_irq_status(s_handle, FLD_LIN_REC_HIT_PID_W1C);
            if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_TX) {
                lin_send_response(s_handle,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].data,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].len,
                                  cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type);
                lin_set_response_discard(s_handle->lin_num);
            } else if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_RX) {
                lin_start_recv_response(s_handle,
                                        cur_proc_table->frame_list[cur_proc_table->item_index].len,
                                        cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type);
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_REC_HIT_PID_ERR_W1C) {
            gpio_toggle(DEBUG_PIN);
            irq_cnt_pid_err++;
            lin_clr_irq_status(s_handle, FLD_LIN_REC_HIT_PID_ERR_W1C);
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_CHECKSUM_ERR_W1C) {
            irq_cnt_checksum_error++;
            lin_clr_irq_status(s_handle, FLD_LIN_RESP_CHECKSUM_ERR_W1C);
            if (cur_proc_table->frame_list[cur_proc_table->item_index].conflict_proc_schedule) {
                cur_proc_table             = cur_proc_table->frame_list[cur_proc_table->item_index].conflict_proc_schedule;
                cur_proc_table->item_index = 0;
            }
        }

        if (lin_get_irq_status(s_handle) & (FLD_LIN_RESP_TX_DONE_W1C | FLD_LIN_RESP_RX_DONE_W1C | FLD_LIN_RESP_TIMEOUT_W1C)) {
            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TX_DONE_W1C) {
                irq_cnt_resp_tx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_TX_DONE_W1C);
            }

            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_RX_DONE_W1C) {
                irq_cnt_resp_rx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_RX_DONE_W1C);
                if (cur_proc_table->frame_list[cur_proc_table->item_index].action == LIN_ACTION_RX) {
                    lin_get_response_data(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].data, cur_proc_table->frame_list[cur_proc_table->item_index].len, cur_proc_table->frame_list[cur_proc_table->item_index].checksum_type, 0);
                }
            }

            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TIMEOUT_W1C) {
                gpio_toggle(DEBUG_PIN);
                irq_cnt_resp_timeout++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_TIMEOUT_W1C);
                lin_set_response_discard(s_handle->lin_num);
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

        if (lin_get_irq_status(s_handle) & FLD_LIN_COMM_FRAME_SLOT_DONE_W1C) {
            irq_cnt_slot_done++;
            lin_clr_irq_status(s_handle, FLD_LIN_COMM_FRAME_SLOT_DONE_W1C);
            //lin_set_slot(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].slot_cnt);
            //lin_master_send_header(s_handle, cur_proc_table->frame_list[cur_proc_table->item_index].id);
        }
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
        if (lin_get_irq_status(s_handle) & FLD_LIN_BUS_INACTIVE_W1C) {
            lin_sleep_status = 1;
            irq_cnt_inactive_cnt++;
            lin_clr_irq_status(s_handle, FLD_LIN_BUS_INACTIVE_W1C);
            lin_clr_irq_mask(s_handle, FLD_LIN_BUS_INACTIVE_W1C);
            lin_set_hw_en(s_handle->lin_num, false); //go to sleep
            lin_set_state(s_handle->lin_num, LIN_STATE_SLEEP);
        }
#endif
    }
}

PLIC_ISR_REGISTER(lin_irq_handler, IRQ_SELECT)

#endif

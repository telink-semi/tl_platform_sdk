/********************************************************************************************************
 * @file    app_lin_slave_wakeup.c
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

#if (LIN_TEST_MODE == LIN_TEST_SLAVE_WEAKUP)

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
    .role     = LIN_SLAVE_NODE,
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
        .dma_mode_enable = true,
        .tx_dma_chn      = DMA0,
        .rx_dma_chn      = DMA1,
    },
    .checksum_cfg =
    {
        .checksum_sw_enable = false,
        .sum_func           = 0,
    },
};

static lin_handle_t_ptr          s_handle          = 0;
static int                       s_frame_index_hit = -1;
static lin_frame_item_t_ptr s_frame_hit       = 0;

lin_frame_item_t s_frame_list[] = {
    {LIN_ACTION_RX, 0x11, 1, {0x00}, LIN_CHECKSUM_TYPE_ENHANCED, 0, 0, 0},
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

#define DEBUG_PIN  LED2

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1); //enable output
    gpio_input_dis(LED1); //disable input

    gpio_function_en(DEBUG_PIN);
    gpio_output_en(DEBUG_PIN);  //enable output
    gpio_input_dis(DEBUG_PIN);  //disable input

    s_handle = lin_hw_init(&lin_module0);
    if (!s_handle) {
        while (1);
    }

    lin_set_irq_mask(s_handle, FLD_LIN_MASK_RESP_TX_DONE_RW | FLD_LIN_MASK_RESP_RX_DONE_RW | FLD_LIN_MASK_RESP_TIMEOUT_RW |FLD_LIN_MASK_HEADER_TIMEOUT_RW |
                     FLD_LIN_MASK_RESP_CHECKSUM_ERR_RW | FLD_LIN_MASK_REC_HEADER_RW | FLD_LIN_MASK_REC_HEADER_ERR_RW | FLD_LIN_MASK_REC_NEW_BREAK_RW);
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
    lin_set_irq_mask(s_handle, FLD_LIN_MASK_BUS_INACTIVE_RW);
#endif
    plic_interrupt_enable(IRQ_SELECT);
    core_interrupt_enable();
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
lin_get_response_result_t data;

#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
volatile unsigned int irq_cnt_inactive_cnt  = 0;
volatile unsigned int lin_sleep_status      = 0; //0:wake up;1:sleep
#endif

void main_loop(void)
{
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
    while (lin_sleep_status) {
        delay_us(50);
        if ((gpio_get_level((gpio_pin_e)s_handle->rx_pin) == 0))
        {
            lin_sleep_status = 0;
            lin_set_hw_en(s_handle->lin_num, true); //weak up LIN bus
            lin_set_state(s_handle->lin_num, LIN_STATE_INIT);
            lin_set_state(s_handle->lin_num, LIN_STATE_RUN);
            lin_set_irq_mask(s_handle, FLD_LIN_MASK_BUS_INACTIVE_RW);
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
                      irq_cnt_checksum_error = 0,
                      irq_cnt_resp_tx_done   = 0,
                      irq_cnt_resp_rx_done   = 0,
                      irq_cnt_resp_timeout   = 0,
                      irq_cnt_header_timeout = 0,
                      irq_cnt_new_break      = 0,
                      irq_cnt_pid_error      = 0,
                      irq_cnt_discard        = 0;

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
            lin_clr_irq_status(s_handle, FLD_LIN_REC_HIT_PID_W1C);
            irq_cnt_header_done++;
            s_frame_index_hit = get_frame_index(lin_get_id(s_handle), s_frame_list, sizeof(s_frame_list) / sizeof(s_frame_list[0]));
            if (s_frame_index_hit != -1) {
                s_frame_hit = &(s_frame_list[s_frame_index_hit]);
                if (s_frame_hit->action == LIN_ACTION_TX) {
                    lin_send_response(s_handle, s_frame_hit->data, s_frame_hit->len, s_frame_hit->checksum_type);
                } else if (s_frame_hit->action == LIN_ACTION_RX) {
                    lin_start_recv_response(s_handle, s_frame_hit->len, s_frame_hit->checksum_type);
                } else {
                    lin_discard_response(s_handle);
                    irq_cnt_discard++;
                }
            } else {
                s_frame_hit = 0;
                lin_discard_response(s_handle);
                irq_cnt_discard++;
                gpio_toggle(DEBUG_PIN);
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_HEADER_TIMEOUT_W1C) {
            irq_cnt_header_timeout++;
            gpio_toggle(DEBUG_PIN);
            lin_clr_irq_status(s_handle, FLD_LIN_HEADER_TIMEOUT_W1C);
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_REC_NEW_BREAK_W1C) {
            irq_cnt_new_break++;
            gpio_toggle(DEBUG_PIN);
            lin_clr_irq_status(s_handle, FLD_LIN_REC_NEW_BREAK_W1C);
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_CHECKSUM_ERR_W1C) {
            irq_cnt_checksum_error++;
            gpio_toggle(DEBUG_PIN);
            lin_clr_irq_status(s_handle, FLD_LIN_RESP_CHECKSUM_ERR_W1C);
        }

        if (lin_get_irq_status(s_handle) & (FLD_LIN_RESP_TX_DONE_W1C | FLD_LIN_RESP_RX_DONE_W1C | FLD_LIN_RESP_TIMEOUT_W1C)) {
            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TX_DONE_W1C) {
                irq_cnt_resp_tx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_TX_DONE_W1C);
            }

            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_RX_DONE_W1C) {
                irq_cnt_resp_rx_done++;
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_RX_DONE_W1C);
                if (s_frame_hit) {
                    lin_get_response_data(s_handle, s_frame_hit->data, s_frame_hit->len, s_frame_hit->checksum_type, &data);
                }
            }

            if (lin_get_irq_status(s_handle) & FLD_LIN_RESP_TIMEOUT_W1C) {
                irq_cnt_resp_timeout++;
                gpio_toggle(DEBUG_PIN);
                lin_clr_irq_status(s_handle, FLD_LIN_RESP_TIMEOUT_W1C);
            }
        }

        if (lin_get_irq_status(s_handle) & FLD_LIN_REC_HIT_PID_ERR_W1C) {
            irq_cnt_pid_error++;
            gpio_toggle(DEBUG_PIN);
            irq_cnt_discard++;
            lin_clr_irq_status(s_handle, FLD_LIN_REC_HIT_PID_ERR_W1C);
            lin_discard_response(s_handle);
            s_frame_hit = 0;
        }
#if (LIN_SLEEP_MODE ==  LIN_SLEEP_MODE_IRQ)
        if (lin_get_irq_status(s_handle) & FLD_LIN_BUS_INACTIVE_W1C) {
            irq_cnt_inactive_cnt++;
            lin_sleep_status = 1;
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

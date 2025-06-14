/********************************************************************************************************
 * @file    tx_ping_pong.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#include "driver.h"
typedef struct {
   can_frame_t  *items ;
   volatile char front;      
   volatile char rear;           
   volatile unsigned char queue_len_flag;
   volatile unsigned char queue_len;
}tx_queue_t;

typedef struct {
    volatile unsigned char tx_mailbox_num_from;
    volatile unsigned char tx_mailbox_num_to;
    volatile unsigned char tx_mailbox_cnt;
    volatile unsigned char tx_prio_num_from;
    volatile unsigned char tx_prio_num_to;    
    volatile unsigned char tx_mailbox_cur_prio;
    volatile tx_queue_t    queue;
    volatile unsigned char queue_is_empty_flag;
    volatile unsigned char tx_mailbox_w_index;
    volatile unsigned char tx_mailbox_r_index;
    volatile unsigned char prio_loop_flag;
}can_tx_task_t;

typedef struct {

   can_fd_frame_t  *items ;
   volatile char front;     
   volatile char rear;          
   volatile unsigned char queue_len_flag;
   volatile unsigned char queue_len;
}tx_fd_queue_t;

typedef struct {
    volatile unsigned char tx_mailbox_num_from;
    volatile unsigned char tx_mailbox_num_to;
    volatile unsigned char tx_mailbox_cnt;
    volatile unsigned char tx_prio_num_from;
    volatile unsigned char tx_prio_num_to;    
    volatile unsigned char tx_mailbox_cur_prio;
    volatile tx_fd_queue_t queue;
    volatile unsigned char queue_is_empty_flag;
    volatile unsigned char tx_mailbox_w_index;
    volatile unsigned char tx_mailbox_r_index;
    volatile unsigned char prio_loop_flag;
}can_fd_tx_task_t;


_Bool is_empty(tx_queue_t *queue);


_Bool is_full(tx_queue_t *queue);


_Bool enqueue(can_tx_task_t *task, can_frame_t*tx_data);


can_frame_t* dequeue(can_tx_task_t *task);


unsigned char can_tx_buff_enqueue(can_chn_e chn,can_tx_task_t *task, can_frame_t* tx_data);


void can_send_mailbox_request(can_chn_e chn,can_tx_task_t *task);




_Bool fd_enqueue(can_fd_tx_task_t *task, can_fd_frame_t*tx_data);


can_fd_frame_t* fd_dequeue(can_fd_tx_task_t *task);



unsigned char can_fd_tx_buff_enqueue(can_chn_e chn,can_fd_tx_task_t *task, can_fd_frame_t* tx_data);


void can_fd_send_mailbox_request(can_chn_e chn,can_fd_tx_task_t *task);




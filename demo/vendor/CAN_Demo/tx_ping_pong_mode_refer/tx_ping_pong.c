/********************************************************************************************************
 * @file    tx_ping_pong.c
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
#include "tx_ping_pong.h"
#include "string.h"
_attribute_data_retention_sec_ preempt_config_t s_can_preempt_config =
{
    .preempt_en =0,
    .threshold  =1,
};
volatile unsigned char g_can_r;
volatile unsigned char empty_enqueue_flag;

_Bool is_empty(tx_queue_t *queue){
    return queue->queue_len_flag == 0;
}


_Bool is_full(tx_queue_t *queue){
     return queue->queue_len_flag == queue->queue_len;

}


_Bool enqueue(can_tx_task_t *task, can_frame_t*tx_data){
     if (task->queue.queue_len_flag == task->queue.queue_len)
     {
         return 0;
     }
     memcpy(task->queue.items+task->queue.rear, tx_data, (DLC_LENGTH_DECODE(tx_data->length)+8));
     task->queue.rear = (task->queue.rear + 1) % (task->queue.queue_len);
     g_can_r = plic_enter_critical_sec(s_can_preempt_config.preempt_en,s_can_preempt_config.threshold);
     task->queue.queue_len_flag++;
     plic_exit_critical_sec(s_can_preempt_config.preempt_en,g_can_r);
     return 1;
}


can_frame_t* dequeue(can_tx_task_t *task){
    if (task->queue.queue_len_flag == 0) {
        return NULL;
     }
    unsigned char value = task->queue.front;
    task->queue.front = (task->queue.front + 1) % (task->queue.queue_len);
     g_can_r = plic_enter_critical_sec(s_can_preempt_config.preempt_en,s_can_preempt_config.threshold);
     task->queue.queue_len_flag--;
    plic_exit_critical_sec(s_can_preempt_config.preempt_en,g_can_r);
    return task->queue.items + value;
}



unsigned char can_tx_buff_enqueue(can_chn_e chn,can_tx_task_t *task, can_frame_t* tx_data){
unsigned char return_data=1;
    if(task->queue_is_empty_flag ==1){
        tx_data->prio = task->tx_mailbox_cur_prio;
        can_write_tx_mb(chn,task->tx_mailbox_num_from+ task->tx_mailbox_w_index,tx_data,0);
        task->queue_is_empty_flag=0;
        task->tx_mailbox_w_index++;
        task->tx_mailbox_w_index&=(task->tx_mailbox_cnt-1);
    }else{
        return_data=enqueue(task,tx_data);
    }
    return return_data;
}


void can_send_mailbox_request(can_chn_e chn,can_tx_task_t *task){
    unsigned char int_flag=0;
    unsigned char inactive_cnt=0;
    can_frame_t* data;
    for(unsigned char i=0;i< task->tx_mailbox_cnt;i++){
        unsigned char num = i+ task->tx_mailbox_num_from;
        if(can_get_mb_irq_status(chn,num)){
             gpio_toggle(GPIO_PA0);
            task->tx_mailbox_r_index++;
            task->tx_mailbox_r_index&=(task->tx_mailbox_cnt-1);
            can_clr_mb_irq_status(chn,num);
            int_flag=1;
        }
    }
    if(int_flag==1){
        inactive_cnt = (task->tx_mailbox_w_index +(task->tx_mailbox_cnt-1))-task->tx_mailbox_r_index;
        if(task->prio_loop_flag ==1){
             if(task->tx_mailbox_r_index== task->tx_mailbox_w_index){
                 task->prio_loop_flag=0;
                 inactive_cnt=(task->tx_mailbox_cnt-1);
             }
        }
        if( empty_enqueue_flag==1){
             if(task->tx_mailbox_r_index == task->tx_mailbox_w_index){
                    task->queue_is_empty_flag =1;
                    empty_enqueue_flag=0;
             }
        }
        if((task->queue_is_empty_flag==0)&&(task->prio_loop_flag==0)){
            if(inactive_cnt>0){
                if(inactive_cnt>task->tx_mailbox_cnt){
                    inactive_cnt = inactive_cnt-task->tx_mailbox_cnt;
                }
                for(unsigned char i=0;i<inactive_cnt;i++){
                    data =dequeue(task);
                    if(data==NULL){
                        empty_enqueue_flag=1;
                    if(task->tx_mailbox_r_index == task->tx_mailbox_w_index){
                        task->queue_is_empty_flag =1;
                        empty_enqueue_flag=0;
                    }
                        break;
                    }else{
                        gpio_toggle(GPIO_PA1);
                        data->prio =  task->tx_mailbox_cur_prio;

                        can_write_tx_mb(chn,task->tx_mailbox_num_from+ task->tx_mailbox_w_index,data,0);
                        task->tx_mailbox_w_index++;
                        task->tx_mailbox_w_index&=(task->tx_mailbox_cnt-1);
                        if(task->tx_mailbox_w_index ==0){
                            task->tx_mailbox_cur_prio++; 
                            if(!(task->tx_mailbox_cur_prio &task->tx_prio_num_to)){
                                task->tx_mailbox_cur_prio = task->tx_prio_num_from;
                                task->prio_loop_flag=1;
                            }
                        }
                    }

                }

            }

        }
    }
}


_Bool fd_enqueue(can_fd_tx_task_t *task, can_fd_frame_t*tx_data){
     if (task->queue.queue_len_flag == task->queue.queue_len)
     {
         return 0;
     }
     memcpy(task->queue.items+task->queue.rear, tx_data, (DLC_LENGTH_DECODE(tx_data->length)+8));
     task->queue.rear = (task->queue.rear + 1) % (task->queue.queue_len);
     g_can_r = plic_enter_critical_sec(s_can_preempt_config.preempt_en,s_can_preempt_config.threshold);
     task->queue.queue_len_flag++;
     plic_exit_critical_sec(s_can_preempt_config.preempt_en,g_can_r);
     return 1;
}


can_fd_frame_t* fd_dequeue(can_fd_tx_task_t *task){
    if (task->queue.queue_len_flag == 0) {
        return NULL;
     }
    unsigned char value = task->queue.front;
    task->queue.front = (task->queue.front + 1) % 8;
     g_can_r = plic_enter_critical_sec(s_can_preempt_config.preempt_en,s_can_preempt_config.threshold);
     task->queue.queue_len_flag--;
    plic_exit_critical_sec(s_can_preempt_config.preempt_en,g_can_r);
    return task->queue.items + value;
}



unsigned char can_fd_tx_buff_enqueue(can_chn_e chn,can_fd_tx_task_t *task, can_fd_frame_t* tx_data){
unsigned char return_data=1;
    if(task->queue_is_empty_flag ==1){
        canfd_write_tx_mb(chn,task->tx_mailbox_num_from+ task->tx_mailbox_w_index,tx_data);
        task->queue_is_empty_flag=0;
        task->tx_mailbox_w_index++;
        task->tx_mailbox_w_index&=(task->tx_mailbox_cnt-1);
    }else{
        return_data=fd_enqueue(task,tx_data);
    }
    return return_data;
}


void can_fd_send_mailbox_request(can_chn_e chn,can_fd_tx_task_t *task){
    unsigned char int_flag=0;
    unsigned char inactive_cnt=0;
    can_fd_frame_t* data;
    for(unsigned char i=0;i< task->tx_mailbox_cnt;i++){
        unsigned char num = i+ task->tx_mailbox_num_from;
        if(can_get_mb_irq_status(chn,num)){
            task->tx_mailbox_r_index++;
            task->tx_mailbox_r_index&=(task->tx_mailbox_cnt-1);
            can_clr_mb_irq_status(chn,num);
            int_flag=1;
        }
    }
    if(int_flag==1){
        inactive_cnt = (task->tx_mailbox_w_index +(task->tx_mailbox_cnt-1))-task->tx_mailbox_r_index;
        if(task->prio_loop_flag ==1){
             if(task->tx_mailbox_r_index== task->tx_mailbox_w_index){
                 task->prio_loop_flag=0;
                 inactive_cnt=(task->tx_mailbox_cnt-1);
             }
        }
        if( empty_enqueue_flag==1){
             if(task->tx_mailbox_r_index == task->tx_mailbox_w_index){
                    task->queue_is_empty_flag =1;
                    empty_enqueue_flag=0;
             }
        }
        if((task->queue_is_empty_flag==0)&&(task->prio_loop_flag==0)){
            if(inactive_cnt>0){
                if(inactive_cnt>task->tx_mailbox_cnt){
                    inactive_cnt = inactive_cnt-task->tx_mailbox_cnt;
                }
                for(unsigned char i=0;i<inactive_cnt;i++){
                    data =fd_dequeue(task);
                    if(data==NULL){
                        empty_enqueue_flag=1;
                    if(task->tx_mailbox_r_index == task->tx_mailbox_w_index){
                        task->queue_is_empty_flag =1;
                        empty_enqueue_flag=0;
                    }
                        break;
                    }else{
                        canfd_write_tx_mb(chn,task->tx_mailbox_num_from+ task->tx_mailbox_w_index,data);
                        task->tx_mailbox_w_index++;
                        task->tx_mailbox_w_index&=(task->tx_mailbox_cnt-1);
                        if(task->tx_mailbox_w_index ==0){
                            task->tx_mailbox_cur_prio++; 
                            if(!(task->tx_mailbox_cur_prio &task->tx_prio_num_to)){
                                task->tx_mailbox_cur_prio = task->tx_prio_num_from;
                                task->prio_loop_flag=1;
                            }
                        }
                    }

                }
            }

        }
    }
}

/*!
 * @brief This interface is used for data conversion in word
 * @param[in] data    - the convert buff
 * @param[in] len - data length.
 * @return  none
 */
void data_convert_by_word(unsigned char *data,unsigned char len){
    unsigned int wordCount = len>>2;
    volatile unsigned int rem = len & 3;
    unsigned int *wd = (unsigned int *)data;
    volatile unsigned char i = 0;
    unsigned char word[4];
    volatile unsigned char j=0;
    for (j=0; j<wordCount; j++) {
        word[0] = wd[j]>>24;
        word[1] = wd[j]>>16;
        word[2] = wd[j]>>8;
        word[3] = wd[j];
        *(((unsigned int *)data)+j) = *(unsigned int*)word;
        i=4*(j+1);
    }

    unsigned char *ofp = (unsigned char *)&wd[j];
    unsigned char rem_data[4];
    for(j=0;j<rem;j++){
        rem_data[j] = ofp[rem-j-1];
    }
    for(j=0;j<rem;j++){
        data[i+j]=rem_data[j];
    }

}

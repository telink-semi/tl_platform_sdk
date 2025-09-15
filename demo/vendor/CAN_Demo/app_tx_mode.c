/********************************************************************************************************
 * @file    app_tx_mode.c
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
#include "tx_ping_pong_mode_refer/tx_ping_pong.h"

#if(CAN_TEST   ==    CAN_TX_MODE)
#define IS_LITTLE_END_CONVERT  0

#define TX_ONE_MB     0
#define TX_PING_PONG  1
#define TX_MODE       TX_PING_PONG

#define  IS_TX_RX     1
#define  QUEUE_LEN    8
can_frame_t tx_queue_items_low[QUEUE_LEN];

can_tx_task_t  tx_task_low={
        .tx_mailbox_num_from = 4,
        .tx_mailbox_num_to   = 7,
        .tx_mailbox_cnt      = 4,
        .tx_prio_num_from    = 0,
        .tx_prio_num_to      = 1,
        .tx_mailbox_cur_prio = 0,
        .queue               ={
            .items = tx_queue_items_low,
            .front = 0,
            .rear  = 0,
            .queue_len_flag = 0,
            .queue_len = QUEUE_LEN,
        },
        .queue_is_empty_flag = 1,
        .tx_mailbox_w_index  =0,
        .tx_mailbox_r_index  =0,
        .prio_loop_flag      =0,
};


can_timing_config_t timing_cfg;
can_timing_config_t can1_timing_cfg;

can_mb_cfg_t mb_cfg;

can_rx_mb_config_t rxmb_cfg[4]={
        {CAN_ID_STD(0x00),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x02),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x04),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x06),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
};
unsigned int rxmb_individual_mask[4]={
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
};

can_frame_t tx_frame;
can_frame_t rx_frame[4];
can_frame_t can1_rx_frame[4];


#define RXMB_START_INDEX         0
#define MB_RX_NUM                4
#define TXMB_START_INDEX         4

#define CAN_BIT_RATE     1000000
unsigned char g_tx_buff[8]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
void user_init(void)
{
    //io
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);
    can_set_pin(CAN1,GPIO_FC_PB5,GPIO_FC_PB4);
/**************************************************************can0********************************************************/
    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);

    //init
    can_cal_timing_config(CAN0,CAN_BIT_RATE,sys_clk.pclk * 1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
#if(TX_MODE    ==   TX_ONE_MB)
    can_init(CAN0,&timing_cfg,&mb_cfg,1,0);
#elif(TX_MODE    ==   TX_PING_PONG)
    can_init(CAN0,&timing_cfg,&mb_cfg,1,1);
#endif

    //rxmb id/active
    for(volatile unsigned char i=0;i< sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_rx_mailbox_cfg(CAN0,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN0,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    //txmb
#if(TX_MODE    ==  TX_ONE_MB)
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);
#elif(TX_MODE   ==    TX_PING_PONG)
    for(unsigned char i=0; i<tx_task_low.tx_mailbox_cnt;i++){
        can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX+i,1);
    }
#endif


    //irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN0,i+RXMB_START_INDEX);
    }
#if(TX_MODE    ==  TX_ONE_MB)
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
#elif(TX_MODE   ==    TX_PING_PONG)
    for(unsigned char i=0; i<tx_task_low.tx_mailbox_cnt;i++){
        can_set_mb_irq_mask(CAN0,i+tx_task_low.tx_mailbox_num_from);
    }
#endif

    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();

/**************************************************************can1********************************************************/
    can_module_en(CAN1);
    can_enter_freeze_mode(CAN1);

    //init
    can_cal_timing_config(CAN1,CAN_BIT_RATE,sys_clk.pclk * 1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN1,&timing_cfg,&mb_cfg,1,0);

    //rxmb id/active
    for(volatile unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){

        can_set_rx_mailbox_cfg(CAN1,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN1,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    //txmb
    can_set_tx_mailbox_cfg(CAN1,TXMB_START_INDEX,1);

    //irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN1,i+RXMB_START_INDEX);
    }
    can_set_mb_irq_mask(CAN1,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN1,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN1);
    core_interrupt_enable();
    can_exit_freeze_mode(CAN1);

}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done=0;
volatile unsigned char can1_rx_done=0;
volatile unsigned char can1_tx_done=1;
void main_loop (void)
{

#if(TX_MODE == TX_PING_PONG)
  for(volatile unsigned char j=0;j<1;j++){
          for(volatile unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
                tx_frame.id     = rxmb_cfg[i].id;
                tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
                tx_frame.type   = CAN_FRAME_TYPE_DATA;
                tx_frame.length = CAN_8B_PER_FRAME;
                for(volatile unsigned char m=0;m<DLC_LENGTH_DECODE(CAN_8B_PER_FRAME);m++){
                      *(((unsigned char *)&tx_frame.data_word0)+m) = *(g_tx_buff+m);
                }
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)&tx_frame.data_word0,DLC_LENGTH_DECODE(CAN_8B_PER_FRAME));
#endif
                tx_frame.data_byte0++;
                while(!can_tx_buff_enqueue(CAN0,&tx_task_low,&tx_frame)){};
                can_exit_freeze_mode(CAN0);
            }
    }

#elif(TX_MODE == TX_ONE_MB)
    for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        while(!tx_done);
        tx_frame.id     = rxmb_cfg[i].id;
        tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
        tx_frame.type   = CAN_FRAME_TYPE_DATA;
        tx_frame.length = CAN_8B_PER_FRAME;
        for(volatile unsigned char j=0;j<DLC_LENGTH_DECODE(CAN_8B_PER_FRAME);j++){
              *(((unsigned char *)&tx_frame.data_word0)+j) = *(g_tx_buff+j);
        }
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)&tx_frame.data_word0,DLC_LENGTH_DECODE(CAN_8B_PER_FRAME));
#endif
        can_write_tx_mb(CAN0,TXMB_START_INDEX,&tx_frame,0);
        can_exit_freeze_mode(CAN0);

        tx_done=0;


    }
#endif

#if(IS_TX_RX)
     while(!(can1_rx_done==4));
     can1_rx_done=0;
     for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        while(!can1_tx_done){};
            can_write_tx_mb(CAN1,TXMB_START_INDEX,&can1_rx_frame[i],0);
            can1_tx_done=0;

    }
     while(!(rx_done ==4));
     rx_done=0;
    for(volatile unsigned int i=0;i< 4;i++){
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)&can1_rx_frame[i].data_word0,DLC_LENGTH_DECODE(can1_rx_frame[i].length));
#endif
        for(volatile unsigned char j=0;j<can1_rx_frame[i].length;j++){
               if(*((&(rx_frame[i].data_byte0))+j) !=*((&(can1_rx_frame[i].data_byte0))+j)){
                   gpio_set_high_level(LED1);
                   while(1);
               }
        }
    }
#endif
//    while(1);
    can1_tx_done=1;
    tx_done=1;
}


volatile unsigned char tx_done_cnt=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){
    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN0,i)){
            can_read_rx_mb(CAN0,i,&rx_frame[i]);
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)&rx_frame[i].data_word0,DLC_LENGTH_DECODE(rx_frame[i].length));
#endif
            can_clr_mb_irq_status(CAN0,i);
            rx_done++;
            break;
        }
    }
#if(TX_MODE == TX_PING_PONG)
        can_send_mailbox_request(CAN0,&tx_task_low);
#elif(TX_MODE == TX_ONE_MB)
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done_cnt++;
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }
#endif
}

_attribute_ram_code_sec_ void can1_irq_handler(void){

    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN1,i)){
            can_read_rx_mb(CAN1,i,&can1_rx_frame[i]);
            can_clr_mb_irq_status(CAN1,i);
            can1_rx_done++;
            break;
        }
    }
    if(can_get_mb_irq_status(CAN1,TXMB_START_INDEX)){
        can1_tx_done=1;
        can_clr_mb_irq_status(CAN1,TXMB_START_INDEX);
    }

}

PLIC_ISR_REGISTER(can1_irq_handler, IRQ_CAN1)
PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











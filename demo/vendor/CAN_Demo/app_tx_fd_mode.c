/********************************************************************************************************
 * @file    app_tx_fd_mode.c
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

#if(CAN_TEST   ==    CAN_TX_FD_MODE)

#define  IS_TX_RX    1
#define  IS_LITTLE_END_CONVERT    0

can_timing_config_t timing_cfg;
can_timing_config_t can1_timing_cfg;

can_mb_cfg_t mb_cfg;

can_fd_rx_mb_config_t rxmb_cfg[4]={
        {CAN_ID_STD(0x00),CAN_FRAME_FORMAT_STANDARD},
        {CAN_ID_STD(0x02),CAN_FRAME_FORMAT_STANDARD},
        {CAN_ID_STD(0x04),CAN_FRAME_FORMAT_STANDARD},
        {CAN_ID_STD(0x06),CAN_FRAME_FORMAT_STANDARD},
};
unsigned int rxmb_individual_mask[4]={
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
};


can_fd_frame_t tx_fd_frame;
can_fd_frame_t rx_fd_frame[4];
can_fd_frame_t can1_rx_frame[4];
can_fd_frame_t can1_fd_rx_frame[4];
can_fd_baud_rate_t  rate_cfg={
    .canfd_timing_mode = CANFD_FDCBT,
    .bit_rate = 1000000,
    .bit_rate_fd = 1000000,
};

unsigned char g_tx_buff[16]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

#define RXMB_START_INDEX         0
#define MB_RX_NUM                4
#define TXMB_START_INDEX         4

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);
    can_set_pin(CAN1,GPIO_FC_PB5,GPIO_FC_PB4);
/**************************************************************can0********************************************************/

    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);

    //init
    canfd_cal_timing_config(CAN0,&rate_cfg,sys_clk.pclk*1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_64BYTE_PERMB;
    canfd_init(CAN0,&timing_cfg,&mb_cfg, 1,1,0);

    //rxmb id/active
    for(volatile unsigned char i=0;i< sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){
        canfd_set_rx_mailbox_cfg(CAN0,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN0,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    //txmb
    canfd_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);


    //irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN0,i+RXMB_START_INDEX);
    }

    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);

    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();

/**************************************************************can1********************************************************/
    can_module_en(CAN1);
    can_enter_freeze_mode(CAN1);

    //init
    canfd_cal_timing_config(CAN1,&rate_cfg,sys_clk.pclk*1000000,&can1_timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_64BYTE_PERMB;
    canfd_init(CAN1,&timing_cfg,&mb_cfg, 1,1,0);


    //rxmb id/active
    for(volatile unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){

        canfd_set_rx_mailbox_cfg(CAN1,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN1,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    //txmb
    canfd_set_tx_mailbox_cfg(CAN1,TXMB_START_INDEX,1);


    //irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){
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
volatile unsigned char heihei_debug=0;
void main_loop (void)
{
    for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){
        while(!tx_done);
        tx_fd_frame.id     = rxmb_cfg[i].id;
        tx_fd_frame.format = CAN_FRAME_FORMAT_STANDARD;
        tx_fd_frame.type   = CAN_FRAME_TYPE_DATA;
        tx_fd_frame.length = CAN_16B_PER_FRAME;
        tx_fd_frame.edl    = 1;
        tx_fd_frame.brs    = 1;
        for(volatile unsigned char j=0;j<DLC_LENGTH_DECODE(CAN_16B_PER_FRAME);j++){
              *(((unsigned char *)tx_fd_frame.data_word)+j) = *(g_tx_buff+j);
        }
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)tx_fd_frame.data_word,DLC_LENGTH_DECODE(CAN_16B_PER_FRAME));
#endif
        canfd_write_tx_mb(CAN0,TXMB_START_INDEX,&tx_fd_frame);
        can_exit_freeze_mode(CAN0);
        tx_fd_frame.data_byte0++;
        tx_done=0;

    }
//    while(1);
#if(IS_TX_RX)
     while(!(can1_rx_done==4));
     can1_rx_done=0;
     for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_fd_rx_mb_config_t);i++){
        while(!can1_tx_done){};
        canfd_write_tx_mb(CAN1,TXMB_START_INDEX,&can1_rx_frame[i]);
            can1_tx_done=0;

    }
     while(!(rx_done ==4));
     rx_done=0;
    for(volatile unsigned int i=0;i< 4;i++){
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)can1_rx_frame[i].data_word,DLC_LENGTH_DECODE(can1_rx_frame[i].length));
#endif
        for(volatile unsigned char j=0;j<can1_rx_frame[i].length;j++){
               if(*((&(rx_fd_frame[i].data_byte0))+j) !=*((&(can1_rx_frame[i].data_byte0))+j)){
                   gpio_set_high_level(LED1);
                   heihei_debug++;
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
volatile unsigned char can0_irq_debug=0;
volatile unsigned char can1_irq_debug=0;
volatile unsigned char can0_err_type=0;
volatile unsigned char can0_fast_err_type=0;
volatile unsigned char can1_err_type=0;
volatile unsigned char can1_fast_err_type=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){

    if(can_get_err_irq_status(CAN0,CAN_ERR_STATUS)){
        gpio_toggle(LED1);
        can0_irq_debug++;
        can0_err_type=can_get_err_type(CAN0);
        can0_fast_err_type = canfd_get_err_fast_type(CAN0);
        can_clr_err_irq_status(CAN0,CAN_ERR_STATUS);
        while(1);
    }
     for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN0,i)){
            canfd_read_rx_mb(CAN0,i,&rx_fd_frame[i]);
#if IS_LITTLE_END_CONVERT
        data_convert_by_word((unsigned char*)rx_fd_frame[i].data_word,DLC_LENGTH_DECODE(rx_fd_frame[i].length));
#endif
            can_clr_mb_irq_status(CAN0,i);
            rx_done++;
            break;
        }
    }
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done_cnt++;
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }

}

_attribute_ram_code_sec_ void can1_irq_handler(void){

    if(can_get_err_irq_status(CAN1,CAN_ERR_STATUS)){
        gpio_toggle(LED1);
        can1_irq_debug++;
        can1_err_type=can_get_err_type(CAN1);
        can1_fast_err_type = canfd_get_err_fast_type(CAN1);
        if(can1_irq_debug==1){
            while(1);
        }
        can_clr_err_irq_status(CAN1,CAN_ERR_STATUS);
    }
    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN1,i)){
            canfd_read_rx_mb(CAN1,i,&can1_rx_frame[i]);
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











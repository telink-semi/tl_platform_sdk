/********************************************************************************************************
 * @file    app_rtr.c
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

#if(CAN_TEST   ==    REMOTE_FRAME_MODE)

#define AUTO_RESPONSE    0
#define MANUAL_RESPONSE  1
#define RTR_MODE         AUTO_RESPONSE


can_timing_config_t rx_timing_cfg;
can_mb_cfg_t rx_mb_cfg;

can_rx_mb_config_t rxmb_cfg[1]={
#if(RTR_MODE     ==    MANUAL_RESPONSE)
        {CAN_ID_STD(0x00),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_REMOTE,REMOTE_REQUEST_STORING},
#elif( RTR_MODE      ==   AUTO_RESPONSE)
        {CAN_ID_STD(0x00),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_REMOTE,REMOTE_REQUSET_NO_STORING},
#endif
};
unsigned int rxmb_individual_mask[1]={
         CAN_RX_MB_STD_MASK(0xff, 1, 1),
};

can_timing_config_t tx_timing_cfg;
can_mb_cfg_t tx_mb_cfg;
can_frame_t tx_frame;
can_frame_t tx_reviced_frame;
#define RXMB_START_INDEX         0
#define MB_RX_NUM                1
#define TXMB_START_INDEX         4

unsigned int remote_frame_payload[2]={0x22223344,0x55667788};

#define CAN_BIT_RATE      1000000
void user_init(void)
{
    //io
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);
    can_set_pin(CAN1,GPIO_FC_PB5,GPIO_FC_PB4);

//can1 rx
    can_module_en(CAN1);
    can_enter_freeze_mode(CAN1);

//init
    can_cal_timing_config(CAN1,CAN_BIT_RATE,sys_clk.pclk*1000000,&rx_timing_cfg,0.75);
    rx_mb_cfg.mb_max         =  16;
    rx_mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN1,&rx_timing_cfg,&rx_mb_cfg,1,0);
    reg_can_ctrl2_2(CAN1) &= ~FLD_CAN_EACEN;
//rxmb id filter/active
    for(unsigned char i=0;i< sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_rx_mailbox_cfg(CAN1,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN1,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
#if(RTR_MODE      ==   AUTO_RESPONSE)

    can_set_mb_remote_frame_payload(CAN1,RXMB_START_INDEX,(unsigned int*)remote_frame_payload,CAN_8B_PER_FRAME);
#endif

//irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN1,i+RXMB_START_INDEX);
    }
    can_set_err_irq_mask(CAN1,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN1);
    core_interrupt_enable();
    can_exit_freeze_mode(CAN1);



//can0 tx
    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);

//init
    can_cal_timing_config(CAN0,CAN_BIT_RATE,sys_clk.pclk*1000000,&tx_timing_cfg,0.75);
    tx_mb_cfg.mb_max         =  16;
    tx_mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN0,&tx_timing_cfg,&tx_mb_cfg,1,0);
    reg_can_ctrl2_2(CAN0) &= ~FLD_CAN_EACEN;
//txmb
    can_set_tx_mailbox_cfg(CAN0,0,0);
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);

//irq
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();

}


void main_loop (void)
{
    tx_frame.id     = rxmb_cfg[0].id;
    tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
    tx_frame.type   = CAN_FRAME_TYPE_REMOTE;
    tx_frame.length = 0x08;
    tx_frame.data_word0 = 0x44332211;
    tx_frame.data_word1 = 0x88776655;
    can_write_tx_mb(CAN0,TXMB_START_INDEX,&tx_frame,0);
    can_exit_freeze_mode(CAN0);
    while(1);
}

volatile unsigned char can0_done=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        can0_done++;
        if(can0_done==2){
            can_read_rx_mb(CAN0,TXMB_START_INDEX,&tx_reviced_frame);
        }
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }
}

volatile unsigned char can1_done=0;
volatile unsigned char rx_index=0;
_attribute_ram_code_sec_ void can1_irq_handler(void){
#if(RTR_MODE      ==   AUTO_RESPONSE)
    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN1,i)){
            can_clr_mb_irq_status(CAN1,i);
            can1_done++;
            break;
        }
    }
#elif(RTR_MODE     ==    MANUAL_RESPONSE)
    can1_done++;

    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN1,i)){
            rx_index =i;
            can_clr_mb_irq_status(CAN1,i);
            break;
        }
    }
    if(can1_done==1){
            tx_frame.id     = rxmb_cfg[0].id;
            tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
            tx_frame.type   = CAN_FRAME_TYPE_DATA;
            tx_frame.length = 0x08;
            tx_frame.data_word0 = 0x44332299;
            tx_frame.data_word1 = 0x88776655;
            can_write_tx_mb(CAN1,rx_index,&tx_frame,1);
    }



#endif
}
PLIC_ISR_REGISTER(can1_irq_handler, IRQ_CAN1)
PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











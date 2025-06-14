/********************************************************************************************************
 * @file    app_pn_mode.c
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

#if(CAN_TEST   ==    CAN_PN_MODE)
#define RXMB_START_INDEX         0
#define MB_RX_NUM                4

#define TXMB_START_INDEX 0

can_rx_mb_config_t rxmb_cfg[4]={
        {CAN_ID_STD(0x00),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x01),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x02),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
        {CAN_ID_STD(0x03),CAN_FRAME_FORMAT_STANDARD,CAN_FRAME_TYPE_DATA,NONE},
};
unsigned int rxmb_individual_mask[4]={
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
         CAN_RX_MB_STD_MASK(0xff, 0, 0),
};
can_timing_config_t can1_timing_cfg;
can_mb_cfg_t can1_mb_cfg;

can_timing_config_t can0_timing_cfg;
can_mb_cfg_t can0_mb_cfg;
can_frame_t rx_frame[4];
can_frame_t tx_frame;

#define   DOZE_MODE     0
#define   STOP_MODE     1
#define   DOZE_PN_MODE  2
#define   STOP_PN_MODE  3
#define   SLEEP_MODE    STOP_PN_MODE

#define MATCH_NUM       4
can_pn_config_t pn_cfg={
    .timeout_is_en  =1,
    .timeout_value  =(MATCH_NUM+2)*16*8/64,
    .match_is_en    =1,
    .match_src      =CAN_PN_MATSRC_ID_Data,
    .match_num      = MATCH_NUM,
    .id_match_mode  =CAN_PN_MATCH_EQUAL,
    .id_lower       =CAN_ID_STD(0x01),
    .id_upper       =CAN_PN_STD_MASK(0x7ff,1,1),
    .length_lower   = 0x01,
    .length_upper   = 0x08,
    .lower_word0    = 0x00112233,
    .lower_word1    = 0x44556677,
    .upper_word0    = 0xffffffff,
    .upper_word1    = 0xffffffff,
};

#define CAN_BIT_RATE            1000000
void user_init(void)
{
    //io
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);
    can_set_pin(CAN1,GPIO_FC_PB5,GPIO_FC_PB4);

    can_module_en(CAN1);
    can_enter_freeze_mode(CAN1);

    //init
    can_cal_timing_config(CAN1,CAN_BIT_RATE,sys_clk.pclk *1000000,&can1_timing_cfg,0.75);
    can1_mb_cfg.mb_max         =  16;
    can1_mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN1,&can1_timing_cfg,&can1_mb_cfg,1,0);

    //rxmb id filter/active
    for(unsigned char i=0;i< sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_rx_mailbox_cfg(CAN1,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN1,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN1,i+RXMB_START_INDEX);
    }
#if( SLEEP_MODE  ==  DOZE_MODE)
    can_set_self_wakeup_irq_mask(CAN1,CAN_WAKEUP_MASK);
#elif(SLEEP_MODE  ==  STOP_MODE)
    can_set_self_wakeup_irq_mask(CAN1,CAN_WAKEUP_MASK);
#elif(SLEEP_MODE  ==  DOZE_PN_MODE)
    can_set_pn_config(CAN1,&pn_cfg);
    can_set_pn_irq_mask(CAN1,CAN_PN_MATCH_IRQ|CAN_PN_TIMEOUT_IRQ);
#elif(SLEEP_MODE  ==  STOP_PN_MODE)
    can_set_pn_config(CAN1,&pn_cfg);
    can_set_pn_irq_mask(CAN1,CAN_PN_MATCH_IRQ|CAN_PN_TIMEOUT_IRQ);
#endif
     plic_interrupt_enable(IRQ_CAN1);
     core_interrupt_enable();
     can_exit_freeze_mode(CAN1);


 /*********************************************************can0**************************************************/
    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);

    //init
    can_cal_timing_config(CAN0,CAN_BIT_RATE,sys_clk.pclk *1000000,&can0_timing_cfg,0.75);
    can0_mb_cfg.mb_max         =  16;
    can0_mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN0,&can0_timing_cfg,&can0_mb_cfg,1,0);

    //txmb
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);

    //irq
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();

}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done;
void main_loop (void)
{
//can1
#if( SLEEP_MODE   ==  DOZE_MODE)
    can_enter_doze_mode(CAN1);
#elif(SLEEP_MODE   ==  STOP_MODE)
    can_enter_stop_mode(CAN1);
#elif(SLEEP_MODE   ==  DOZE_PN_MODE)
    can_enter_pn_doze_mode(CAN1);
#elif(SLEEP_MODE   ==  STOP_PN_MODE)
    can_enter_pn_stop_mode(CAN1);
#endif

 //CAN0
    for(unsigned char i=0;i<MATCH_NUM;i++){
        while(!tx_done){};
        tx_frame.id     = CAN_ID_STD(0x01);
        tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
        tx_frame.type   = CAN_FRAME_TYPE_DATA;
        tx_frame.length = 0x08;
        tx_frame.data_word0 = 0x00112233;
        tx_frame.data_word1 = 0x44556677;
        can_write_tx_mb(CAN0,TXMB_START_INDEX,&tx_frame,0);
        can_exit_freeze_mode(CAN0);
        tx_done=0;

    }
    while(1);

}
volatile unsigned char debug_can0_irq=0;
volatile unsigned char debug_can1_irq=0;
volatile unsigned char debug_can1_wakeup_irq=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){
    debug_can0_irq++;
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }
}

_attribute_ram_code_sec_ void can1_irq_handler(void){
    debug_can1_irq++;
    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN1,i)){
            can_read_rx_mb(CAN1,i,&rx_frame[i]);
            can_clr_mb_irq_status(CAN1,i);
            rx_done++;
            break;
        }
    }


    if(can_get_self_wakeup_irq_status(CAN1,CAN_WAKEUP_STATUS)){
        debug_can1_wakeup_irq++;
#if(SLEEP_MODE   ==  DOZE_MODE)
        can_exit_doze_mode(CAN1);
#elif(SLEEP_MODE   ==  STOP_MODE)
        can_exit_stop_mode(CAN1);
#endif
        can_clr_self_wakeup_irq_status(CAN1,CAN_WAKEUP_STATUS);
     }

    if(can_get_pn_irq_status(CAN1,CAN_PN_MATCH_IRQ)){
        debug_can1_wakeup_irq++;
#if(SLEEP_MODE   ==  DOZE_PN_MODE)
        can_exit_doze_mode(CAN1);
#elif(SLEEP_MODE   ==  STOP_PN_MODE)
        can_exit_stop_mode(CAN1);
#endif
        can_clr_self_wakeup_irq_status(CAN1,CAN_WAKEUP_STATUS);
        can_clr_pn_irq_status(CAN1,CAN_PN_MATCH_IRQ);

     }
    if(can_get_pn_irq_status(CAN1,CAN_PN_TIMEOUT_IRQ)){
#if(SLEEP_MODE   ==  DOZE_PN_MODE)
        reg_can_mcr0(CAN1) &= ~FLD_CAN_DOZE_REQ;
        reg_can_mcr2(CAN1) &= ~FLD_CAN_DOZE;
        reg_can_esr1_0(CAN1) = FLD_CAN_WAK_INT_STATUS;
#elif(SLEEP_MODE   ==  STOP_PN_MODE)
        reg_can_mcr1(CAN1) &=~FLD_CAN_STOP_REQ;
        reg_can_esr1_0(CAN1) = FLD_CAN_WAK_INT_STATUS;
#endif
        can_clr_self_wakeup_irq_status(CAN1,CAN_WAKEUP_STATUS);
        can_clr_pn_irq_status(CAN1,CAN_PN_TIMEOUT_IRQ);
     }
}

PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
PLIC_ISR_REGISTER(can1_irq_handler, IRQ_CAN1)
#endif











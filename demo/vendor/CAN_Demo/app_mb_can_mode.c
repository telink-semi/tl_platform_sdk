/********************************************************************************************************
 * @file    app_mb_can_mode.c
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

#if(CAN_TEST   ==    MB_CAN_MODE)

can_timing_config_t timing_cfg;
can_mb_cfg_t mb_cfg;

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

can_frame_t tx_frame;

can_frame_t rx_frame[4];

#define RXMB_START_INDEX         0
#define MB_RX_NUM                4
#define TXMB_START_INDEX         4

#define  CAN_BIT_RATE    1000000
void user_init(void)
{
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);

    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);
    //init
    can_cal_timing_config(CAN0,CAN_BIT_RATE,sys_clk.pclk * 1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN0,&timing_cfg,&mb_cfg,1,0);

    //rxmb id filter/active
    for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_rx_mailbox_cfg(CAN0,i+RXMB_START_INDEX,&rxmb_cfg[i],1);
        can_set_rx_individual_mask(CAN0,i+RXMB_START_INDEX,&rxmb_individual_mask[i]);
    }
    //txmb
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);

    //irq
    for(unsigned char i=0; i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
        can_set_mb_irq_mask(CAN0,i+RXMB_START_INDEX);
    }
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();
    can_exit_freeze_mode(CAN0);
}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done=0;
void main_loop (void)
{
    if(rx_done ==MB_RX_NUM){
        rx_done =0;
        for(unsigned char i=0;i<sizeof(rxmb_cfg)/sizeof(can_rx_mb_config_t);i++){
                while(!tx_done){};
                can_write_tx_mb(CAN0,TXMB_START_INDEX,&rx_frame[i],0);
                tx_done=0;
        }
    }
}


_attribute_ram_code_sec_ void can0_irq_handler(void){
    for(unsigned char i=RXMB_START_INDEX;i<RXMB_START_INDEX+MB_RX_NUM;i++){
        if(can_get_mb_irq_status(CAN0,i)){
            can_read_rx_mb(CAN0,i,&rx_frame[i]);
            can_clr_mb_irq_status(CAN0,i);
            rx_done++;
            break;
        }
    }
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }

}


PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











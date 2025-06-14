/********************************************************************************************************
 * @file    app_legacy_rxfifo_mode.c
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

#if(CAN_TEST   ==    LEGACY_RXFIFO_MODE)

#define CAN_RX_NODMA      0
#define CAN_RX_DMA        1
#define CAN_RX_DMA_CHAIN  2
#define CAN_RX_MODE   CAN_RX_DMA_CHAIN

#define CAN_DMA_CHA_RX       DMA0
#define DMA_REV_LEN           0xFFFFFC    //0xFFFFFC

#define FILTER_CNT     4
can_timing_config_t timing_cfg;
can_mb_cfg_t mb_cfg;

can_rx_fifo_config_t rxfifo_config;
unsigned int rxfifo_id_filter[FILTER_CNT] = {
    CAN_RX_FIFO_STD_FILTER_TYPE_A(0x00, 0, 0), CAN_RX_FIFO_STD_FILTER_TYPE_A(0x01, 0, 0),
    CAN_RX_FIFO_STD_FILTER_TYPE_A(0x02, 0, 0), CAN_RX_FIFO_STD_FILTER_TYPE_A(0x03, 0, 0)
/*
 *  CAN_RX_FIFO_STD_FILTER_TYPE_B_HIGH(0x321, 0, 0)|CAN_RX_FIFO_STD_FILTER_TYPE_B_LOW(0x321, 0, 0),
 *  CAN_RX_FIFO_STD_FILTER_TYPE_C_HIGH(0x321)|CAN_RX_FIFO_STD_FILTER_TYPE_C_MID_HIGH(0x321)|CAN_RX_FIFO_STD_FILTER_TYPE_C_MID_LOW(0x321)|CAN_RX_FIFO_STD_FILTER_TYPE_C_LOW(0x321),
 */
};

unsigned int rxfifo_individual_mask[FILTER_CNT]={
        CAN_RX_FIFO_STD_MASK_TYPE_A(0x7ff, 0, 0),
        CAN_RX_FIFO_STD_MASK_TYPE_A(0x7ff, 0, 0),
        CAN_RX_FIFO_STD_MASK_TYPE_A(0x7ff, 0, 0),
        CAN_RX_FIFO_STD_MASK_TYPE_A(0x7ff, 0, 0),
/*
*  CAN_RX_FIFO_STD_MASK_TYPE_B_HIGH(0x7ff, 0, 0)|CAN_RX_FIFO_STD_MASK_TYPE_B_LOW(0x7ff, 0, 0),
*  CAN_RX_FIFO_STD_MASK_TYPE_C_HIGH(0x7ff)|CAN_RX_FIFO_STD_MASK_TYPE_C_MID_HIGH(0x7ff)|CAN_RX_FIFO_STD_MASK_TYPE_C_MID_LOW(0x7ff)|CAN_RX_FIFO_STD_MASK_TYPE_C_LOW(0x7ff),
*/
};

#define RX_BUFF_LEN     4
can_frame_t  rx_frame[RX_BUFF_LEN];
can_frame_dma_t  rx_dma_frame[RX_BUFF_LEN];
dma_chain_config_t rx_dma_list[4];

#define TXMB_START_INDEX         8

#define CAN_BIT_RATE        1000000
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

    //legacy rxfifo
    rxfifo_config.id_filter_table = rxfifo_id_filter;
    rxfifo_config.id_filter_type  = CAN_RXFIFO_FILTER_TYPE_A;
    rxfifo_config.id_filter_num   = sizeof(rxfifo_id_filter) / sizeof(rxfifo_id_filter[0]);
    rxfifo_config.priority        = CAN_RXFIFO_PRIO_HIGH;
    can_set_legacy_rxfifo_cfg(CAN0, &rxfifo_config, 1);

    //individual mask
    for(unsigned char i=0;i< FILTER_CNT;i++){
        can_set_rx_individual_mask(CAN0,i,&rxfifo_individual_mask[i]);
    }
    //txmb
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);

    //irq
#if(CAN_RX_MODE  == CAN_RX_NODMA)
    can_set_legacy_rxfifo_irq_mask(CAN0,CAN_LEGACY_RXFIFO_AVAILD_IRQ);
#elif(CAN_RX_MODE  == CAN_RX_DMA)
    can_set_rx_dma_config(CAN0, CAN_DMA_CHA_RX);
    can_receive_dma(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,((unsigned char*)(&(rx_dma_frame->frame))), DMA_REV_LEN);
    dma_set_irq_mask(CAN_DMA_CHA_RX, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
#elif(CAN_RX_MODE ==  CAN_RX_DMA_CHAIN)
    dma_set_llp_irq_mode(CAN_DMA_CHA_RX,DMA_INTERRUPT_MODE);
    dma_set_irq_mask(CAN_DMA_CHA_RX, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    can_set_dma_chain_llp(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,((unsigned char*)(&(rx_dma_frame->frame))),DMA_REV_LEN,&rx_dma_list[0]);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,&rx_dma_list[0],&rx_dma_list[1],(unsigned char*)(&(rx_dma_frame+1)->frame),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,&rx_dma_list[1],&rx_dma_list[2],(unsigned char*)(&(rx_dma_frame+2)->frame),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,&rx_dma_list[2],&rx_dma_list[3],(unsigned char*)(&(rx_dma_frame+3)->frame),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,&rx_dma_list[3],&rx_dma_list[0],(unsigned char*)(&(rx_dma_frame+0)->frame),DMA_REV_LEN);
    dma_chn_en(CAN_DMA_CHA_RX);
#endif
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK|FLD_CAN_BUS_OFF_MASK);
    can_set_err_irq_mask(CAN0,CAN_BUS_OFF_DONE_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();
    can_exit_freeze_mode(CAN0);
}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done=0;
void main_loop (void)
{

    if(rx_done ==RX_BUFF_LEN){
        rx_done =0;
        for(unsigned char i=0;i<RX_BUFF_LEN;i++){
            while(!tx_done){};
#if(CAN_RX_MODE  == CAN_RX_NODMA)
            can_write_tx_mb(CAN0,TXMB_START_INDEX,&rx_frame[i],0);
#elif(CAN_RX_MODE  == CAN_RX_DMA || CAN_RX_MODE  == CAN_RX_DMA_CHAIN )
             can_write_tx_mb(CAN0,TXMB_START_INDEX,&(rx_dma_frame[i].frame),0);
#endif
                tx_done=0;

        }
    }

}

void dma_irq_handler(void){
#if(CAN_RX_MODE  == CAN_RX_DMA)
    if(dma_get_tc_irq_status( BIT(CAN_DMA_CHA_RX))){
        dma_clr_tc_irq_status( BIT(CAN_DMA_CHA_RX));
        rx_done++;
        can_receive_dma(CAN0,CAN_DMA_CHA_RX,CAN_LEGACY_RXFIFO,(unsigned char*)(&(rx_dma_frame+rx_done)->frame), DMA_REV_LEN);
    }
#elif(CAN_RX_MODE  == CAN_RX_DMA_CHAIN)
    if(dma_get_tc_irq_status( BIT(CAN_DMA_CHA_RX))){
        dma_clr_tc_irq_status( BIT(CAN_DMA_CHA_RX));
        rx_done++;
    }
#endif
}


_attribute_ram_code_sec_ void can0_irq_handler(void){
#if(CAN_RX_MODE  == CAN_RX_NODMA)
    if(can_get_legacy_rxfifo_irq_status(CAN0,CAN_LEGACY_RXFIFO_AVAILD_IRQ)){
        can_read_legacy_rxfifo(CAN0,&rx_frame[rx_done]);
        can_clr_legacy_rxfifo_irq_status(CAN0,CAN_LEGACY_RXFIFO_AVAILD_IRQ);
        rx_done++;
    }
#endif
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }

}

PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











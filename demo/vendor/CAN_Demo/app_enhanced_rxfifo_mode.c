/********************************************************************************************************
 * @file    app_enhanced_rxfifo_mode.c
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

#if(CAN_TEST   ==    ENHANCED_RXFIFO_MODE)

#define CAN_RX_NODMA      0
#define CAN_RX_DMA        1
#define CAN_RX_DMA_CHAIN  2
#define CAN_RX_MODE       CAN_RX_DMA_CHAIN

#define CAN_DMA_CHA_RX       DMA0
#define DMA_REV_LEN          0xFFFFFC    //0xFFFFFC


can_fd_baud_rate_t  rate_cfg={
    .canfd_timing_mode = CANFD_FDCBT,
    .bit_rate = 1000000,
    .bit_rate_fd = 1000000,
};

can_timing_config_t timing_cfg;

can_mb_cfg_t mb_cfg;

unsigned int id_filter_table[]={
        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_LOW(0x01,0),
        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_HIGH(0x01,0),

        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_LOW(0x02,0),
        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_HIGH(0x02,0),

        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_LOW(0x03,0),
        CAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_HIGH(0x03,0),

        CAN_ENHANCED_RX_FIFO_STD_TWO_FILTERS(0x01,0,0x03,0),
        CAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(0x00,0,0x3ff,1),
};

can_enhanced_rx_fifo_config_t rxfifo_cfg;

can_fd_frame_t rx_frame[4];


dma_chain_config_t rx_dma_list[4];
#define ENHANCED_RXFIFO_TRIGGER_CNT 4

#if((CAN_RX_MODE     ==  CAN_RX_DMA_CHAIN))
typedef struct{
    unsigned int length;
    can_fd_frame_t frame;
}canfd_frame_dma_t;
canfd_frame_dma_t rx_dma_frame[ENHANCED_RXFIFO_TRIGGER_CNT];
#endif

#if((CAN_RX_MODE     ==  CAN_RX_DMA))
typedef struct{
    unsigned int length;
    can_fd_frame_t frame[ENHANCED_RXFIFO_TRIGGER_CNT];
}can_fd_frame_dma_t;
can_fd_frame_dma_t rx_dma_frame;


#endif
#define TXMB_START_INDEX         0

void user_init(void)
{

    gpio_function_en(GPIO_PA0);
    gpio_output_en(GPIO_PA0);
    can_set_pin(CAN0,GPIO_FC_PB3,GPIO_FC_PB2);
    can_set_pin(CAN1,GPIO_FC_PB5,GPIO_FC_PB4);

    can_module_en(CAN0);
    can_enter_freeze_mode(CAN0);

    //init
    canfd_cal_timing_config(CAN0,&rate_cfg,sys_clk.pclk*1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_64BYTE_PERMB;
    canfd_init(CAN0,&timing_cfg,&mb_cfg, 1,1,0);

    //id filter
    rxfifo_cfg.id_filter_table = id_filter_table;
    rxfifo_cfg.id_filter_pairnum = 4;
    rxfifo_cfg.extendid_filternum =3;
    rxfifo_cfg.priority = CAN_RXFIFO_PRIO_HIGH;
    can_set_enhanced_rxfifo_cfg(CAN0,&rxfifo_cfg,1);

    //txmb
    canfd_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);

    //rx
#if(CAN_RX_MODE       ==  CAN_RX_NODMA)
    can_set_enhanced_rxfifo_watermark(CAN0,ENHANCED_RXFIFO_TRIGGER_CNT);
    can_set_enhanced_rxfifo_irq_mask(CAN0,CAN_ENHANCED_RXFIFO_WATERMARK_IRQ);
#elif(CAN_RX_MODE     ==  CAN_RX_DMA)
    can_set_enhanced_rxfifo_watermark(CAN0,ENHANCED_RXFIFO_TRIGGER_CNT);
    can_set_rx_dma_config(CAN0, CAN_DMA_CHA_RX);
    can_receive_dma(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,((unsigned char*)((rx_dma_frame.frame))), DMA_REV_LEN);
    dma_set_irq_mask(CAN_DMA_CHA_RX, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
#elif(CAN_RX_MODE     ==  CAN_RX_DMA_CHAIN)
    dma_set_llp_irq_mode(CAN_DMA_CHA_RX,DMA_INTERRUPT_MODE);
    dma_set_irq_mask(CAN_DMA_CHA_RX, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    can_set_dma_chain_llp(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,((unsigned char*)(&(rx_dma_frame[0].frame))),DMA_REV_LEN,&rx_dma_list[0]);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,&rx_dma_list[0],&rx_dma_list[1],((unsigned char*)(&(rx_dma_frame[1].frame))),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,&rx_dma_list[1],&rx_dma_list[2],((unsigned char*)(&(rx_dma_frame[2].frame))),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,&rx_dma_list[2],&rx_dma_list[3],((unsigned char*)(&(rx_dma_frame[3].frame))),DMA_REV_LEN);
    can_rx_dma_add_list_element(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,&rx_dma_list[3],&rx_dma_list[0],((unsigned char*)(&(rx_dma_frame[0].frame))),DMA_REV_LEN);
    dma_chn_en(CAN_DMA_CHA_RX);
#endif
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK|FLD_CAN_BUS_OFF_MASK);
    can_set_err_irq_mask(CAN0,CAN_BUS_OFF_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();
    can_exit_freeze_mode(CAN0);

}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done=0;
can_fd_frame_t tx_fd_frame;
void main_loop (void)
{
    if(rx_done ==ENHANCED_RXFIFO_TRIGGER_CNT){
        rx_done =0;
        for(unsigned char i=0;i<ENHANCED_RXFIFO_TRIGGER_CNT;i++){
            while(!tx_done){};
#if(CAN_RX_MODE  == CAN_RX_NODMA)
                canfd_write_tx_mb(CAN0,TXMB_START_INDEX,&rx_frame[i]);
#elif(CAN_RX_MODE  == CAN_RX_DMA)
                canfd_write_tx_mb(CAN0,TXMB_START_INDEX,&(rx_dma_frame.frame[i]));
#elif(CAN_RX_MODE  == CAN_RX_DMA_CHAIN )
                canfd_write_tx_mb(CAN0,TXMB_START_INDEX,&(rx_dma_frame[i].frame));
#endif
                tx_done=0;

        }
    }
}

void dma_irq_handler(void){
#if(CAN_RX_MODE  == CAN_RX_DMA)
    if(dma_get_tc_irq_status( BIT(CAN_DMA_CHA_RX))){
        dma_clr_tc_irq_status( BIT(CAN_DMA_CHA_RX));
        rx_done=ENHANCED_RXFIFO_TRIGGER_CNT;
        can_receive_dma(CAN0,CAN_DMA_CHA_RX,CAN_ENHANCED_RXFIFO,(unsigned char*)((rx_dma_frame.frame)), DMA_REV_LEN);
        for(unsigned char i=0;i<ENHANCED_RXFIFO_TRIGGER_CNT;i++){
            can_enhanced_rxfifo_dma_reset_idhit(CAN0,rx_dma_frame.frame+i);
        }
    }
#elif(CAN_RX_MODE  == CAN_RX_DMA_CHAIN)
    if(dma_get_tc_irq_status( BIT(CAN_DMA_CHA_RX))){
        dma_clr_tc_irq_status( BIT(CAN_DMA_CHA_RX));
        can_enhanced_rxfifo_dma_reset_idhit(CAN0,(&(rx_dma_frame+rx_done)->frame));
        rx_done++;
    }
#endif
}

_attribute_ram_code_sec_ void can0_irq_handler(void){
    if(can_get_enhanced_rxfifo_irq_status(CAN0,CAN_ENHANCED_RXFIFO_WATERMARK_IRQ)){
        for(unsigned char i=0;i<ENHANCED_RXFIFO_TRIGGER_CNT;i++){
            can_read_enhanced_rxfifo(CAN0,&rx_frame[i]);
            can_clr_enhanced_rxfifo_irq_status(CAN0,CAN_ENHANCED_RXFIFO_WATERMARK_IRQ|CAN_ENHANCED_RXFIFO_AVAILD_IRQ);
            rx_done++;
        }
    }

    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        tx_done=1;
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
    }

}

PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











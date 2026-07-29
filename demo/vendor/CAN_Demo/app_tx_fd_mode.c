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

#define CAN_MODULE_SEL CAN0

#define  IS_LITTLE_END_CONVERT    1

can_timing_config_t timing_cfg;

can_mb_cfg_t mb_cfg;

can_fd_frame_t tx_fd_frame;
can_fd_baud_rate_t  rate_cfg={
    .canfd_timing_mode = CANFD_FDCBT,
    .bit_rate = 1000000,
    .bit_rate_fd = 4000000,
};

unsigned char g_tx_buff[16]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

#define TXMB_START_INDEX         0

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1); //enable output
    gpio_input_dis(LED1); //disable input
    gpio_function_en(LED2);
    gpio_output_en(LED2); //enable output
    gpio_input_dis(LED2); //disable input

    /* PCLK needs to be a multiple of the communication baud rate */
#if defined(MCU_CORE_TL322X)
    PLL_192M_D25F_96M_HCLK_N22_48M_PCLK_48M_MSPI_48M;
#elif defined(MCU_CORE_TL521X)
    PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
#endif

    can_set_pin(CAN_MODULE_SEL,CAN0_GPIO_TX_PIN,CAN0_GPIO_RX_PIN);
/**************************************************************can0********************************************************/
    can_module_en(CAN_MODULE_SEL);
    can_enter_freeze_mode(CAN_MODULE_SEL);

    //init
    canfd_cal_timing_config(CAN_MODULE_SEL,&rate_cfg,sys_clk.pclk*1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_64BYTE_PERMB;
    canfd_init(CAN_MODULE_SEL,&timing_cfg,&mb_cfg, 1,1,0);

    //txmb
    canfd_set_tx_mailbox_cfg(CAN_MODULE_SEL,TXMB_START_INDEX,1);

    //irq
    can_set_mb_irq_mask(CAN_MODULE_SEL,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN_MODULE_SEL,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();
}

volatile unsigned char tx_done=1;
volatile unsigned char rx_done=0;
void main_loop (void)
{
    delay_ms(1000);
    while(!tx_done);
    gpio_toggle(LED1);
    tx_fd_frame.id     = CAN_ID_STD(0x00);
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
    canfd_write_tx_mb(CAN_MODULE_SEL,TXMB_START_INDEX,&tx_fd_frame);
    can_exit_freeze_mode(CAN_MODULE_SEL);
    g_tx_buff[0]++;
    tx_done=0;
}

volatile unsigned char tx_done_cnt=0;
volatile unsigned char can0_irq_debug=0;
volatile unsigned char can0_err_type=0;
volatile unsigned char can0_fast_err_type=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){

    if(can_get_err_irq_status(CAN_MODULE_SEL,CAN_ERR_STATUS)){
        gpio_toggle(LED1);
        can0_irq_debug++;
        can0_err_type=can_get_err_type(CAN_MODULE_SEL);
        can0_fast_err_type = canfd_get_err_fast_type(CAN_MODULE_SEL);
        can_clr_err_irq_status(CAN_MODULE_SEL,CAN_ERR_STATUS);
        gpio_set_high_level(LED2);
        while(1);
    }
    if(can_get_mb_irq_status(CAN_MODULE_SEL,TXMB_START_INDEX)){
        tx_done_cnt++;
        tx_done=1;
        can_clr_mb_irq_status(CAN_MODULE_SEL,TXMB_START_INDEX);
    }

}

PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











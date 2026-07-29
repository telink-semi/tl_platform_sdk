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

#define CAN_MODULE_SEL CAN0

#define IS_LITTLE_END_CONVERT  0

can_timing_config_t timing_cfg;

can_mb_cfg_t mb_cfg;

can_frame_t tx_frame;
#define TXMB_START_INDEX         0

#define CAN_BIT_RATE     1000000
unsigned char g_tx_buff[8]= {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
void user_init(void)
{
    //io
    gpio_function_en(LED1);
    gpio_output_en(LED1); //enable output
    gpio_input_dis(LED1); //disable input

    /* PCLK needs to be a multiple of the communication baud rate */
#if defined(MCU_CORE_TL322X)
    PLL_192M_D25F_96M_HCLK_N22_48M_PCLK_48M_MSPI_48M;
#elif defined(MCU_CORE_TL521X)
    PLL_144M_CCLK_48M_HCLK_48M_PCLK_48M_MSPI_48M;
#endif

    can_set_pin(CAN_MODULE_SEL,CAN0_GPIO_TX_PIN,CAN0_GPIO_RX_PIN);
/**************************************************************CAN_MODULE_SEL********************************************************/
    can_module_en(CAN_MODULE_SEL);
    can_enter_freeze_mode(CAN_MODULE_SEL);

    //init
    can_cal_timing_config(CAN_MODULE_SEL,CAN_BIT_RATE,sys_clk.pclk * 1000000,&timing_cfg,0.75);
    mb_cfg.mb_max         =  16;
    mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN_MODULE_SEL,&timing_cfg,&mb_cfg,1,0);
    can_set_tx_mailbox_cfg(CAN_MODULE_SEL,TXMB_START_INDEX,1);
    can_set_mb_irq_mask(CAN_MODULE_SEL,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN_MODULE_SEL,CAN_ERR_MASK);
    plic_interrupt_enable(IRQ_CAN0);
    core_interrupt_enable();
}

volatile unsigned char tx_done=1;

void main_loop (void)
{
    delay_ms(1000);
    while(!tx_done);
    gpio_toggle(LED1);
    tx_frame.id     = CAN_ID_STD(0x00);
    tx_frame.format = CAN_FRAME_FORMAT_STANDARD;
    tx_frame.type   = CAN_FRAME_TYPE_DATA;
    tx_frame.length = CAN_8B_PER_FRAME;
    for(volatile unsigned char j=0;j<DLC_LENGTH_DECODE(CAN_8B_PER_FRAME);j++){
            *(((unsigned char *)&tx_frame.data_word0)+j) = *(g_tx_buff+j);
    }
#if IS_LITTLE_END_CONVERT
    data_convert_by_word((unsigned char*)&tx_frame.data_word0,DLC_LENGTH_DECODE(CAN_8B_PER_FRAME));
#endif
    can_write_tx_mb(CAN_MODULE_SEL,TXMB_START_INDEX,&tx_frame,0);
    can_exit_freeze_mode(CAN_MODULE_SEL);
    g_tx_buff[0]++;
    tx_done=0;
}


volatile unsigned char tx_done_cnt=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){
    if(can_get_mb_irq_status(CAN_MODULE_SEL,TXMB_START_INDEX)){
        can_clr_mb_irq_status(CAN_MODULE_SEL,TXMB_START_INDEX);
        tx_done_cnt++;
        tx_done=1;
    }
}

PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif

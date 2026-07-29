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

#define CAN_MODULE_SEL CAN0

can_timing_config_t tx_timing_cfg;
can_mb_cfg_t tx_mb_cfg;
can_frame_t tx_frame;
can_frame_t tx_reviced_frame;
#define TXMB_START_INDEX         4

#define CAN_BIT_RATE      1000000
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

    can_set_pin(CAN_MODULE_SEL, CAN0_GPIO_TX_PIN, CAN0_GPIO_RX_PIN);
/**************************************************************CAN_MODULE_SEL********************************************************/
    can_module_en(CAN_MODULE_SEL);
    can_enter_freeze_mode(CAN_MODULE_SEL);

    //init
    can_cal_timing_config(CAN_MODULE_SEL,CAN_BIT_RATE,sys_clk.pclk*1000000,&tx_timing_cfg,0.75);
    tx_mb_cfg.mb_max         =  16;
    tx_mb_cfg.mb_data_size   =  CAN_8BYTE_PERMB;
    can_init(CAN0,&tx_timing_cfg,&tx_mb_cfg,1,0);
    reg_can_ctrl2_2(CAN0) &= ~FLD_CAN_EACEN;
    can_set_tx_mailbox_cfg(CAN0,TXMB_START_INDEX,1);
    can_set_mb_irq_mask(CAN0,TXMB_START_INDEX);
    can_set_err_irq_mask(CAN0,CAN_ERR_MASK);
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
    tx_frame.type   = CAN_FRAME_TYPE_REMOTE;
    tx_frame.length = 0x08;
    can_write_tx_mb(CAN0,TXMB_START_INDEX,&tx_frame,0);
    can_exit_freeze_mode(CAN0);
    tx_done=0;
}

volatile unsigned char tx_done_cnt=0;
_attribute_ram_code_sec_ void can0_irq_handler(void){
    if(can_get_mb_irq_status(CAN0,TXMB_START_INDEX)){
        can_clr_mb_irq_status(CAN0,TXMB_START_INDEX);
        tx_done = 1;
        tx_done_cnt++;
    }
}

PLIC_ISR_REGISTER(can0_irq_handler, IRQ_CAN0)
#endif











/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for B91
 *
 * @author	D.M.H
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#include "../PLIC_Demo/app_config.h"
/**************************notices******************************************
 * ********timer clock use APB clock ******************/
#define TIMER_MODE_GPIO_TRIGGER_TICK    0xf
volatile unsigned int t0;
unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) ={3,0,0,0,0,10,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xc,0xf};
#define TX_PKT_PAYLOAD		15
#define RF_FREQ				17
#define RF_POWER			RF_POWER_P4p35dBm
#define ACCESS_CODE        0x29417671//0xd6be898e// 0x898e898e//
void user_init(void)
{
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
	gpio_set_low_level(LED1|LED2|LED3|LED4);
	plic_preempt_feature_en();
	core_interrupt_enable();
	plic_set_priority(IRQ1_SYSTIMER,IRQ_PRI_LEV3);
	plic_set_priority(IRQ4_TIMER0, IRQ_PRI_LEV2);
	plic_set_priority(IRQ15_ZB_RT, IRQ_PRI_LEV1);


	/******** rf init********/
	plic_interrupt_enable(IRQ15_ZB_RT);

	rf_set_power_level(RF_POWER);
	rf_set_ble_chn(RF_FREQ);
	rf_access_code_comm(ACCESS_CODE);
	rf_set_tx_dma(2,128);


	u8 rf_data_len = TX_PKT_PAYLOAD+2;
	ble_tx_packet[4]=0;
	ble_tx_packet[5]=TX_PKT_PAYLOAD;
	u32 rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
	ble_tx_packet[3] = (rf_tx_dma_len >> 24)&0xff;
	ble_tx_packet[2] = (rf_tx_dma_len >> 16)&0xff;
	ble_tx_packet[1] = (rf_tx_dma_len >> 8)&0xff;
	ble_tx_packet[0] = rf_tx_dma_len&0xff;

	rf_set_txmode();
	delay_us(85);//Wait for calibration to stabilize


	  /******** stimer init********/
	plic_interrupt_enable(IRQ1_SYSTIMER);
	stimer_set_irq_capture(sys_get_stimer_tick() + CLOCK_16M_SYS_TIMER_CLK_1MS); //1ms

  /******** timer0 init********/
	plic_interrupt_enable(IRQ4_TIMER0);
	timer_set_mode(TIMER0, TIMER_MODE_SYSCLK, 0, sys_clk.pclk*1000);//1ms
	rf_set_irq_mask(FLD_RF_IRQ_TX);
	timer_start(TIMER0);
	stimer_set_irq_mask(FLD_SYSTEM_IRQ);		//irq enable

}

void main_loop(void)
{
	rf_tx_pkt ((void *)&ble_tx_packet);
	delay_us(1000);//1ms
	gpio_toggle(LED1);

}


void stimer_irq_handler()
{
	if(stimer_get_irq_status(FLD_SYSTEM_IRQ))
	{
		gpio_set_high_level(LED2);
		stimer_clr_irq_status(FLD_SYSTEM_IRQ);  //clr irq
		stimer_set_irq_capture(sys_get_stimer_tick() + 16*1000);
		delay_us(250);
		gpio_set_low_level(LED2);
	}
}

void timer0_irq_handler(void)
{

	if(timer_get_irq_status(TMR_STA_TMR0))
	{
		gpio_set_high_level(LED3);
		timer_clr_irq_status(TMR_STA_TMR0);
		delay_us(600);
		gpio_set_low_level(LED3);
	}
}

void rf_irq_handler(void)
{
	if(rf_get_irq_status(FLD_RF_IRQ_TX)){
		gpio_set_high_level(LED4);
		rf_clr_irq_status(FLD_RF_IRQ_TX);
		delay_us(800);
		gpio_set_low_level(LED4);
	}
	else
	{
		rf_clr_irq_status(FLD_RF_IRQ_ALL);
	}
}


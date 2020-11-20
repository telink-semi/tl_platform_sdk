/********************************************************************************************************
 * @file	app_lr_s8_125k.c
 *
 * @brief	This is the source file for B91
 *
 * @author	Driver Group
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
#include "app_config.h"

#if RF_MODE == RF_LR_S8_125K


unsigned char  rx_packet[128*4]  __attribute__ ((aligned (4)));
unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) ={3,0,0,0,0,10,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xc,0xf};


#define TX					1
#define RX					2
#define RF_TRX_MODE			TX

#define AUTO  				1
#define MANUAL				2
#define RF_AUTO_MODE 		MANUAL

#define RF_RX_IRQ_EN				0

#define TX_PKT_PAYLOAD		15

#define RX_FIFO_NUM			4
#define RX_FIFO_DEP			128

#define RF_FREQ				17
#define RF_POWER			RF_POWER_P9p11dBm
#define ACCESS_CODE        0x29417671// 0xd6be898e//
volatile unsigned int rx_cnt=0;
volatile unsigned int tx_cnt=0;

#if(RF_RX_IRQ_EN)
_attribute_ram_code_sec_ void rf_irq_handler(void)
{


	if(rf_get_irq_status(FLD_RF_IRQ_RX))
	{
#if(RF_AUTO_MODE == AUTO)
		unsigned char* raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM,RX_FIFO_DEP,rx_packet);
		if(rf_ble_packet_crc_ok(raw_pkt))
		{
					rx_cnt++;
					gpio_toggle(LED5);
		}
		rf_start_srx(stimer_get_tick());
#else
		if(rf_ble_packet_crc_ok(rx_packet))
		{
			rx_cnt++;
			gpio_toggle(LED5);
		}
#endif
			rf_clr_irq_status(FLD_RF_IRQ_RX);



	}
	else
	{
		rf_clr_irq_status(0xffff);
	}


}
#endif

#if(RF_AUTO_MODE == AUTO)
void user_init(void)
{
	rf_set_power_level(RF_POWER);
	rf_set_ble_chn(RF_FREQ);
	rf_access_code_comm(ACCESS_CODE);


#if(RF_TRX_MODE==TX)
	rf_set_tx_dma(2,128);
#elif(RF_TRX_MODE==RX)
	rf_set_rx_dma(rx_packet,RX_FIFO_NUM-1,RX_FIFO_DEP);
#if(RF_RX_IRQ_EN)

	core_interrupt_enable();
	plic_interrupt_enable(IRQ15_ZB_RT);
	rf_set_irq_mask(FLD_RF_IRQ_RX );
	rf_start_srx(0, 0);
#endif
#endif

	gpio_function_en(LED1|LED2|LED3|LED4|LED5|LED6);
	gpio_output_en(LED1|LED2|LED3|LED4|LED5|LED6);

}


void main_loop(void)
{


#if(RF_TRX_MODE==TX)
	unsigned char rf_data_len = TX_PKT_PAYLOAD+2;
	ble_tx_packet[4]=0;
	ble_tx_packet[5]=TX_PKT_PAYLOAD;
	unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
	ble_tx_packet[3] = (rf_tx_dma_len >> 24)&0xff;
	ble_tx_packet[2] = (rf_tx_dma_len >> 16)&0xff;
	ble_tx_packet[1] = (rf_tx_dma_len >> 8)&0xff;
	ble_tx_packet[0] = rf_tx_dma_len&0xff;
	rf_start_stx(ble_tx_packet, stimer_get_tick());

	while(1)
	{

		delay_ms(1);
		while(!(rf_get_irq_status(FLD_RF_IRQ_TX)));
		rf_clr_irq_status(FLD_RF_IRQ_TX);
		rf_start_stx(ble_tx_packet,stimer_get_tick());
		gpio_toggle(LED4);
		//delay_ms(100);
		tx_cnt++;
	}


#elif(RF_TRX_MODE==RX)
#if(!RF_RX_IRQ_EN)
	rf_start_srx(stimer_get_tick());
	while(1)
	{
		if(rf_get_irq_status(FLD_RF_IRQ_RX ))
		{
			unsigned char* raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM,RX_FIFO_DEP,rx_packet);
			if(rf_ble_packet_crc_ok(raw_pkt))
			{
				gpio_toggle(LED4);
				rx_cnt++;
				//delay_ms(100);

			}
				rf_clr_irq_status(FLD_RF_IRQ_RX );
				rf_start_srx(stimer_get_tick());


		}

	}
#endif
#endif
	gpio_toggle(LED6);
	delay_ms(100);
}

#elif(RF_AUTO_MODE == MANUAL)

void user_init(void)
{
	rf_set_power_level(RF_POWER);
	rf_set_ble_chn(RF_FREQ);
	rf_access_code_comm(ACCESS_CODE);

#if(RF_TRX_MODE==TX)
	rf_set_tx_dma(2,128);
#elif(RF_TRX_MODE==RX)
	rf_set_rx_dma(rx_packet,RX_FIFO_NUM-1,RX_FIFO_DEP);

#if(RF_RX_IRQ_EN)

	core_interrupt_enable();
	plic_interrupt_enable(IRQ15_ZB_RT);
	rf_set_irq_mask(FLD_RF_IRQ_RX );
	rf_set_rxmode();
	delay_us(85);//Wait for calibration to stabilize
#endif
#endif
	gpio_function_en(LED1|LED2|LED3|LED4|LED5|LED6);
	gpio_output_en(LED1|LED2|LED3|LED4|LED5|LED6);

}

void main_loop(void)
{
#if(RF_TRX_MODE==TX)

	unsigned char rf_data_len = TX_PKT_PAYLOAD+2;
	ble_tx_packet[4]=0;
	ble_tx_packet[5]=TX_PKT_PAYLOAD;
	unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
	ble_tx_packet[3] = (rf_tx_dma_len >> 24)&0xff;
	ble_tx_packet[2] = (rf_tx_dma_len >> 16)&0xff;
	ble_tx_packet[1] = (rf_tx_dma_len >> 8)&0xff;
	ble_tx_packet[0] = rf_tx_dma_len&0xff;

	rf_set_txmode();
	delay_us(113);//Wait for calibration to stabilize

	while(1)
	{
		delay_ms(1);
		rf_tx_pkt(ble_tx_packet);
		while(!(rf_get_irq_status(FLD_RF_IRQ_TX)));
		rf_clr_irq_status(FLD_RF_IRQ_TX);
		gpio_toggle(LED4);
		//delay_ms(100);
		tx_cnt++;
	}


#elif(RF_TRX_MODE==RX)
#if(!RF_RX_IRQ_EN)


	rf_set_rxmode();
	delay_us(85);//Wait for calibration to stabilize
	while(1)
	{
		if(rf_get_irq_status(FLD_RF_IRQ_RX ))
		{
			if(rf_ble_packet_crc_ok(rx_packet))
			{
				gpio_toggle(LED4);
				rx_cnt++;
//				delay_ms(100);
			}
			rf_clr_irq_status(FLD_RF_IRQ_RX );

		}

	}
#endif
#endif

	gpio_toggle(LED6);
	delay_ms(100);
}

#endif

#endif




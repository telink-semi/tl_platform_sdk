/********************************************************************************************************
 * @file	app_dma.c
 *
 * @brief	This is the source file for B91
 *
 * @author	D.M.H / J.C.F
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

#if(SPI_MODE == SPI_DMA_MODE)
/**********************************************************************************************************************
 *                                         SPI device  selection                                                	 *
 *********************************************************************************************************************/
#define SPI_MASTER_DEVICE		       		  1
#define SPI_SLAVE_DEVICE		      		  2

#define SPI_DEVICE				   	         SPI_MASTER_DEVICE

/**********************************************************************************************************************
 *                                         SPI protocol demo selection                                                *
 *********************************************************************************************************************/
#define SPI_KITE_VULTURE_SLAVE_PROTOCOL		        1
#define SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL		    2
#define SPI_EAGLE_SPI_SLAVE_PROTOCOL		        3

#define SPI_TRANS_MODE			       		SPI_KITE_VULTURE_SLAVE_PROTOCOL

/**********************************************************************************************************************
 *                                         SPI module selection                                               	 	  *
 *********************************************************************************************************************/
#define PSPI_MODULE		       					   0
#define HSPI_MODULE		   						   1

#define SPI_MODULE_SEL	    					 PSPI_MODULE

/**********************************************************************************************************************
*                                         SPI clock set
* * When cclk pclk and hclk are set to 24MHz, the SPI_CLK[use DMA] range are as follows
* SPI_KITE_VULTURE_SLAVE_PROTOCOL    PSPI_MODULE 			max:depend on spi slave  min:48000
* 									 HSPI_MODULE 			max:depend on spi slave  min:48000
* SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL PSPI_MODULE single io	max:1000000   min:48000
* 												 dual io	max:1000000   min:48000
* 									 HSPI_MODULE single io	max:1000000   min:48000
* 												 dual io	max:1000000   min:48000
* 												 quad io	max:1000000   min:48000
* SPI_EAGLE_SPI_SLAVE_PROTOCOL 		 PSPI_MODULE single io	max:12000000  min:48000
* 												 dual io	max:4000000   min:48000
* 									 HSPI_MODULE single io	max:12000000  min:48000
* 												 dual io	max:6000000   min:48000                                            	 	  *
*********************************************************************************************************************/
#define SPI_CLK	    					  	 1000000
/**********************************************************************************************************************
 *                                         SPI pin selection                                               	 	  *
 *********************************************************************************************************************/
volatile  u8 end_irq_flag = 0;
#if (SPI_MODULE_SEL == PSPI_MODULE)
pspi_pin_config_t pspi_pin_config = {
	.pspi_clk_pin 		= PSPI_CLK_PC5,
	.pspi_csn_pin   	= PSPI_CSN_PC4,
	.pspi_mosi_io0_pin  = PSPI_MOSI_IO0_PC7,
	.pspi_miso_io1_pin  = PSPI_MISO_IO1_PC6,
};

#elif (SPI_MODULE_SEL == HSPI_MODULE)
hspi_pin_config_t hspi_pin_config = {
	.hspi_clk_pin		= HSPI_CLK_PB4,
	.hspi_csn_pin 		= HSPI_CSN_PB6,
	.hspi_mosi_io0_pin  = HSPI_MOSI_IO0_PB3,
	.hspi_miso_io1_pin  = HSPI_MISO_IO1_PB2,//3line mode set none
	.hspi_wp_io2_pin    = HSPI_WP_IO2_PB1,//set quad mode otherwise set none
	.hspi_hold_io3_pin  = HSPI_HOLD_IO3_PB0,//set quad mode otherwise set none
};
#endif

/**********************************************************************************************************************
 *                                          dma  channel                                               	 	  *
 *********************************************************************************************************************/
#if(SPI_MODULE_SEL == PSPI_MODULE)
#define  PSPI_TX_DMA_CHN  DMA2
#define  PSPI_RX_DMA_CHN  DMA3
#elif(SPI_MODULE_SEL == HSPI_MODULE)
#define  HSPI_TX_DMA_CHN  DMA4
#define  HSPI_RX_DMA_CHN  DMA5
#endif



#if(SPI_DEVICE == SPI_MASTER_DEVICE)
/**********************************************************************************************************************
 *                          SPI pin selection  just set for  hspi/pspi  master/slave mode  			                                	 	  *
 *********************************************************************************************************************/

#if(SPI_TRANS_MODE == SPI_KITE_VULTURE_SLAVE_PROTOCOL)
	#define SPI_KITE_VULTURE_READ_CMD			0x80
	#define SPI_KITE_VULTURE_WRITE_CMD			0x00
	typedef struct {
	u8 address[3];
	u8 cmd;
	u8 data[16];
	} __attribute__((aligned(4))) spi_tx_kite_vulture_slave_protocol_t;

	spi_tx_kite_vulture_slave_protocol_t spi_tx_kite_vulture_slave_protocol_process = {
	.address = {0x04, 0x40, 0x00},
	.cmd = SPI_KITE_VULTURE_WRITE_CMD,
	.data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};
	u8 spi_rx_dma_eagle_kite_vulture_slave_protocol_buff[16] __attribute__((aligned(4))) = {0x00};

#elif(SPI_TRANS_MODE == SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL)

#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_config_t pspi_eagle_pspi_slave_protocol_config = {
	.pspi_io_mode   = PSPI_SINGLE,
	.pspi_dummy_cnt = 8,
	.pspi_cmd_en 	= true,
	};
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_config_t hspi_eagle_hspi_slave_protocol_config = {
	.hspi_io_mode	  = HSPI_SINGLE,
	.hspi_dummy_cnt   = 8,
	.hspi_cmd_en 	  = true,
	.hspi_addr_en 	  = false,
	.hspi_addr_len 	  = 4,//when hspi_addr_en = false,invalid set.
	.hspi_cmd_fmt_en  = false,//when hspi_cmd_en = false,invalid set.
	.hspi_addr_fmt_en = false,//when hspi_addr_en = false,invalid set.
	};
#endif

	#define SPI_RX_DMA_EAGLE_HSPI_PSPI_MASTER_BUFF_LEN     16
	u8 spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff[SPI_RX_DMA_EAGLE_HSPI_PSPI_MASTER_BUFF_LEN] __attribute__((aligned(4))) = {0x00};
	typedef struct
	{
		u8 address[4];
		u8 data_len;
		u8 data[0x13];
	}  __attribute__((aligned(4))) spi_tx_eagle_hspi_pspi_slave_protocol_t;

	spi_tx_eagle_hspi_pspi_slave_protocol_t eagle_hspi_pspi_slave_protocol_process =
	{
		.address = {0xc0, 0x00, 0x00, 0x00},
		.data_len = 0x13,
		.data = {0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};
#elif(SPI_TRANS_MODE == SPI_EAGLE_SPI_SLAVE_PROTOCOL)
	u8 spi_rx_dma_eagle_spi_slave_protocol_buff[16] __attribute__((aligned(4))) = {0x00};
	typedef struct
	{
#if(SPI_MODULE_SEL == PSPI_MODULE)
		u8 address[4];
#endif
		u8 data[16];
	} __attribute__((aligned(4))) spi_tx_eagle_spi_slave_protocol_t;
	spi_tx_eagle_spi_slave_protocol_t spi_tx_eagle_spi_slave_protocol_t_process = {
#if(SPI_MODULE_SEL == PSPI_MODULE)
		.address = {0xc0, 0x00, 0x02, 0x00},
#endif
		.data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};

#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_config_t pspi_eagle_spi_slave_protocol_config = {
		.pspi_io_mode 	= PSPI_SINGLE,
		.pspi_dummy_cnt = 8,
		.pspi_cmd_en 	= true,
	};
#elif(SPI_MODULE_SEL == HSPI_MODULE)
#define spi_eagle_slve_address	0xc0000200
	hspi_config_t hspi_eagle_spi_slave_protocol_config = {
		.hspi_io_mode 		= HSPI_SINGLE,
		.hspi_dummy_cnt 	= 8,
		.hspi_cmd_en 		= true,
		.hspi_addr_en 		= true,
		.hspi_addr_len 		= 4,//when hspi_addr_en = false,invalid set.
		.hspi_cmd_fmt_en 	= false,//when hspi_cmd_en = false,invalid set.
		.hspi_addr_fmt_en 	= false,//when hspi_addr_en=false,invalid set.
	};
	#endif
#endif


void user_init()
{
	delay_ms(2000);
	gpio_function_en(LED4);
	gpio_output_en(LED4); 		//enable output
	gpio_input_dis(LED4);			//disable input
	gpio_set_high_level(LED4);             	        //LED On
	core_interrupt_enable();
	spi_set_irq_mask(SPI_MODULE_SEL, SPI_END_INT_EN);//endint_en
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_set_pin(&pspi_pin_config);
	spi_master_init(SPI_MODULE_SEL, sys_clk.pclk * 1000000 / (2 * SPI_CLK) - 1, SPI_MODE0);
	plic_interrupt_enable(IRQ23_SPI_APB);
	pspi_set_tx_dma_config(PSPI_TX_DMA_CHN);
	pspi_set_rx_dma_config(PSPI_RX_DMA_CHN);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_set_pin(&hspi_pin_config);
	spi_master_init(SPI_MODULE_SEL, sys_clk.hclk * 1000000 / (2 * SPI_CLK) - 1, SPI_MODE0);
	plic_interrupt_enable(IRQ22_SPI_AHB);
	hspi_set_tx_dma_config(HSPI_TX_DMA_CHN);
	hspi_set_rx_dma_config(HSPI_RX_DMA_CHN);
#endif

#if (SPI_TRANS_MODE == SPI_KITE_VULTURE_SLAVE_PROTOCOL)
	spi_master_config(SPI_MODULE_SEL, SPI_NOMAL);
#elif(SPI_TRANS_MODE == SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_master_config_plus(&pspi_eagle_pspi_slave_protocol_config);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_master_config_plus(&hspi_eagle_hspi_slave_protocol_config);
#endif
#elif(SPI_TRANS_MODE == SPI_EAGLE_SPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_master_config_plus(&pspi_eagle_spi_slave_protocol_config);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_master_config_plus(&hspi_eagle_spi_slave_protocol_config);
#endif
#endif

}

void main_loop (void)
{
	delay_ms(500);
	gpio_toggle(LED4);
#if (SPI_TRANS_MODE == SPI_KITE_VULTURE_SLAVE_PROTOCOL)
	spi_tx_kite_vulture_slave_protocol_process.cmd = SPI_KITE_VULTURE_WRITE_CMD;
	spi_master_write_dma(SPI_MODULE_SEL, (u8*)&spi_tx_kite_vulture_slave_protocol_process, sizeof(spi_tx_kite_vulture_slave_protocol_process));
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	spi_tx_kite_vulture_slave_protocol_process.cmd = SPI_KITE_VULTURE_READ_CMD;
	spi_master_write_read_dma(SPI_MODULE_SEL, (u8*)&spi_tx_kite_vulture_slave_protocol_process, 4, (u8*)spi_rx_dma_eagle_kite_vulture_slave_protocol_buff , 16);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	for(u8 i = 0; i < 16; i++)
	{
		if(spi_tx_kite_vulture_slave_protocol_process.data[i] != spi_rx_dma_eagle_kite_vulture_slave_protocol_buff[i])
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	spi_tx_kite_vulture_slave_protocol_process.data[0]++;
#elif(SPI_TRANS_MODE == SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL)
	spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, 0x00, (u8*)&eagle_hspi_pspi_slave_protocol_process, sizeof(eagle_hspi_pspi_slave_protocol_process), SPI_MODE_WR_DUMMY_WRITE);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, 0x00, (u8*)spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff, 16, SPI_MODE_RD_DUMMY_READ);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	for(u8 i = 0; i < 16; i++)
	{
		if(eagle_hspi_pspi_slave_protocol_process.data[3 + i] != (spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff[i]))
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	eagle_hspi_pspi_slave_protocol_process.data[3]++;
#elif(SPI_TRANS_MODE == SPI_EAGLE_SPI_SLAVE_PROTOCOL)
	#if(SPI_MODULE_SEL == HSPI_MODULE)
	spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_CMD, spi_eagle_slve_address, (u8*)&spi_tx_eagle_spi_slave_protocol_t_process, sizeof(spi_tx_eagle_spi_slave_protocol_st_process), SPI_MODE_WR_WRITE_ONLY);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	spi_master_read_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_CMD, spi_eagle_slve_address, (u8*)spi_rx_dma_eagle_spi_slave_protocol_buff, 16, SPI_MODE_RD_DUMMY_READ);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.
	#endif

	#if(SPI_MODULE_SEL == PSPI_MODULE)
	spi_master_write_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_CMD, 0x00, (u8*)&spi_tx_eagle_spi_slave_protocol_t_process, sizeof(spi_tx_eagle_spi_slave_protocol_t_process), SPI_MODE_WR_WRITE_ONLY);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.

	spi_master_write_read_dma_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_CMD, (u8*)&spi_tx_eagle_spi_slave_protocol_t_process, 4, (u8*)spi_rx_dma_eagle_spi_slave_protocol_buff, 16, SPI_MODE_WR_DUMMY_RD);
	while(!end_irq_flag);//Wait for spi transmission end interrupt.
	end_irq_flag = 0;
	while (spi_is_busy(SPI_MODULE_SEL));//Spi transmission end interrupt doesn't mean spi is free. Better to check spi busy state again.
	for (u8 i = 0; i < 16; i++)
	{
		if(spi_tx_eagle_spi_slave_protocol_t_process.data[i] != (spi_rx_dma_eagle_spi_slave_protocol_buff[i]))
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	spi_tx_eagle_spi_slave_protocol_t_process.data[0]++;
#endif
#endif
}

#if(SPI_MODULE_SEL == PSPI_MODULE)
_attribute_ram_code_sec_noinline_ void pspi_irq_handler(void)
#elif(SPI_MODULE_SEL == HSPI_MODULE)
_attribute_ram_code_sec_noinline_ void hspi_irq_handler(void)
#endif
{
	if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
	{
		spi_clr_irq_status(SPI_MODULE_SEL, FLD_SPI_END_INT);//clr
		end_irq_flag = 1;
	}
}
#elif(SPI_DEVICE == SPI_SLAVE_DEVICE)

void user_init()
{
	delay_ms(2000);
	gpio_function_en(LED4 | LED2);
	gpio_output_en(LED4 | LED2); 		//enable output
	gpio_input_dis(LED4 | LED2);			//disable input
	gpio_set_high_level(LED4 | LED2);              	//LED On
#if(SPI_TRANS_MODE!= SPI_EAGLE_SPI_SLAVE_PROTOCOL)
	spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);
	spi_rx_dma_en(SPI_MODULE_SEL);
	spi_tx_dma_en(SPI_MODULE_SEL);
	core_interrupt_enable();
	spi_set_irq_mask(SPI_MODULE_SEL,SPI_SLV_CMD_EN |SPI_END_INT_EN);//endint_en txfifoint_en rxfifoint_en
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_set_pin(&pspi_pin_config);
	plic_interrupt_enable(IRQ23_SPI_APB);
	pspi_set_tx_dma_config(PSPI_TX_DMA_CHN);
	pspi_set_rx_dma_config(PSPI_RX_DMA_CHN);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_set_pin(&hspi_pin_config);
	plic_interrupt_enable(IRQ22_SPI_AHB);
	hspi_set_tx_dma_config(HSPI_TX_DMA_CHN);
	hspi_set_rx_dma_config(HSPI_RX_DMA_CHN);
#endif
#elif(SPI_TRANS_MODE == SPI_EAGLE_SPI_SLAVE_PROTOCOL)
	spi_slave_set_pin();//EAGLE_SPI_SLAVE only need set pin.
#endif
}

void main_loop (void)
{
	delay_ms(500);
	gpio_toggle(LED4);
}
#if(SPI_TRANS_MODE == SPI_EAGLE_HSPI_PSPI_SLAVE_PROTOCOL)
#define SPI_RX_DMA_EAGLE_HSPI_PSPI_SLAVE_BUFF_LEN     24
#define EAGLE_HSPI_PSPI_SLAVE_TX_DMA_BUFF_OFFSET       8 //must be a multiple 4
__attribute__((aligned(4))) u8 spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff[SPI_RX_DMA_EAGLE_HSPI_PSPI_SLAVE_BUFF_LEN] = {0x00};

#if(SPI_MODULE_SEL == PSPI_MODULE)
_attribute_ram_code_sec_noinline_ void pspi_irq_handler(void)
{
	u8 slave_cmd ;
	if (spi_get_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT))
	{
		slave_cmd = spi_slave_get_cmd(SPI_MODULE_SEL);
		switch (slave_cmd)
		{
			case SPI_WRITE_DATA_SINGLE_CMD:
			case SPI_WRITE_DATA_DUAL_CMD:
				spi_rx_tx_irq_trig_cnt(SPI_MODULE_SEL, 5);
				spi_set_rx_dma(SPI_MODULE_SEL,(u8*)spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff,SPI_RX_DMA_EAGLE_HSPI_PSPI_SLAVE_BUFF_LEN);
				gpio_toggle(LED2);
			break;

			case SPI_READ_DATA_SINGLE_CMD:
			case SPI_READ_DATA_DUAL_CMD:
				spi_rx_tx_irq_trig_cnt(SPI_MODULE_SEL, 4);
				spi_set_tx_dma(SPI_MODULE_SEL,(u8*)spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff+EAGLE_HSPI_PSPI_SLAVE_TX_DMA_BUFF_OFFSET,16);
				gpio_toggle(LED2);
			break;
		}
		spi_clr_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT);//clr
	}
	if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
	{
		spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
		spi_rx_fifo_clr(SPI_MODULE_SEL);
		gpio_toggle(LED2);
	}
}

#elif(SPI_MODULE_SEL == HSPI_MODULE)

_attribute_ram_code_sec_noinline_ void hspi_irq_handler(void)
{
	u8 slave_cmd ;
	
	if (spi_get_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT))
	{
		slave_cmd = spi_slave_get_cmd(SPI_MODULE_SEL);
		switch (slave_cmd)
		{
			case SPI_WRITE_DATA_SINGLE_CMD:
			case SPI_WRITE_DATA_DUAL_CMD:
			case HSPI_WRITE_DATA_QUAD_CMD:
				spi_rx_tx_irq_trig_cnt(SPI_MODULE_SEL, 5);//setting only for fixing the bug that slave receive number of bytes in multiples of 4 will fail.
				spi_set_rx_dma(SPI_MODULE_SEL,(u8*)spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff,SPI_RX_DMA_EAGLE_HSPI_PSPI_SLAVE_BUFF_LEN);
			break;

			case SPI_READ_DATA_SINGLE_CMD:
			case SPI_READ_DATA_DUAL_CMD:
			case HSPI_READ_DATA_QUAD_CMD:
				spi_rx_tx_irq_trig_cnt(SPI_MODULE_SEL, 4);//recover trigger level to 4.
				spi_tx_cnt(SPI_MODULE_SEL,16);
				spi_set_tx_dma(SPI_MODULE_SEL,(u8*)spi_rx_dma_eagle_hspi_pspi_slave_protocol_buff+EAGLE_HSPI_PSPI_SLAVE_TX_DMA_BUFF_OFFSET,16);
				gpio_toggle(LED4);
			break;
		}
		spi_clr_irq_status(SPI_MODULE_SEL, SPI_SLV_CMD_INT);//clr
		gpio_toggle(LED4);
	}

	if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
	{
		spi_clr_irq_status(SPI_MODULE_SEL, SPI_END_INT);//clr
		spi_rx_fifo_clr(SPI_MODULE_SEL);
		gpio_toggle(LED4);
	}

}
#endif
#endif
#endif
#endif

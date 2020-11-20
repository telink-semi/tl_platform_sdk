/********************************************************************************************************
 * @file	app.c
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

#if (SPI_MODE == SPI_NDMA_MODE)
/**********************************************************************************************************************
*                                         SPI device  selection                                                	 *
*********************************************************************************************************************/
#define SPI_MASTER_DEVICE		       		  1
#define SPI_SLAVE_DEVICE		      		  2

#define SPI_DEVICE				   		    SPI_MASTER_DEVICE

/**********************************************************************************************************************
*                                         SPI protocol demo selection                                                *
*********************************************************************************************************************/
#define KITE_VULTURE_SLAVE_PROTOCOL		    1 // kite or vulture as slave
#define HSPI_PSPI_SLAVE_PROTOCOL		    2  // eagle hspi/pspi slave mode as slave
#define SPI_SLAVE_PROTOCOL		       		3  // eagle spi slave as slave

#define SPI_TRANS_MODE			       		 KITE_VULTURE_SLAVE_PROTOCOL

/**********************************************************************************************************************
*                                         SPI module selection                                               	 	  *
*********************************************************************************************************************/
#define PSPI_MODULE		       					 0
#define HSPI_MODULE		   						 1

#define SPI_MODULE_SEL	    					PSPI_MODULE

/**********************************************************************************************************************
 *                                         SPI multiple slave                                               	 	  *
 *********************************************************************************************************************/
#define ONE_SLAVE	       						 0
#define MULTI_SLAVE		   						 1

#define SPI_SLAVE_NUM	    				 ONE_SLAVE

/**********************************************************************************************************************
 *                                         3line SPI slave enable                                              	 	  *
 *********************************************************************************************************************/
#define SPI_NORMAL_SLAVE	       					0
#define SPI_3LINE_SLAVE		   						1

#define SPI_SLAVE_MODE	    				   SPI_NORMAL_SLAVE

/**********************************************************************************************************************
*                                         SPI clock set
* * When cclk pclk and hclk are set to 24MHz, the SPI_CLK[no use DMA] range are as follows
* KITE_VULTURE_SLAVE_PROTOCOL    	PSPI_MODULE 			max:depend on spi slave  min:48000
* 									HSPI_MODULE 			max:depend on spi slave  min:48000
* HSPI_PSPI_SLAVE_PROTOCOL 			PSPI_MODULE single io	max:500000    min:48000
* 												dual io		max:500000    min:48000
* 									HSPI_MODULE single io	max:500000    min:48000
* 												dual io		max:500000    min:48000
* 												quad io		max:400000    min:48000
* SPI_SLAVE_PROTOCOL 		 		PSPI_MODULE single io	max:12000000  min:48000
* 												dual io		max:4000000   min:48000
* 									HSPI_MODULE single io	max:12000000  min:48000
* 												dual io		max:6000000   min:48000
*
*********************************************************************************************************************/
#define SPI_CLK	    					  	400000
/**********************************************************************************************************************
*                                         SPI pin set
*                          lection  just set for  hspi/pspi  master/slave mode  not include eagle spi slave                                            	 	  *
*********************************************************************************************************************/
#if (SPI_MODULE_SEL == PSPI_MODULE)
pspi_pin_config_t pspi_pin_config = {
	.pspi_clk_pin 		= PSPI_CLK_PC5,
	.pspi_csn_pin   	= PSPI_CSN_PC4,
	.pspi_mosi_io0_pin  = PSPI_MOSI_IO0_PC7,
	.pspi_miso_io1_pin  = PSPI_MISO_IO1_PC6,
};
#if (SPI_SLAVE_NUM == MULTI_SLAVE)
#define SLAVE0_CSN_PIN PSPI_CSN_PC4
#define SLAVE1_CSN_PIN PSPI_CSN_PC0
#define SLAVE2_CSN_PIN PSPI_CSN_PD0
#endif
#elif (SPI_MODULE_SEL == HSPI_MODULE)
hspi_pin_config_t hspi_pin_config = {
	.hspi_clk_pin		= HSPI_CLK_PB4,
	.hspi_csn_pin 		= HSPI_CSN_PB6,
	.hspi_mosi_io0_pin  = HSPI_MOSI_IO0_PB3,
	.hspi_miso_io1_pin  = HSPI_MISO_IO1_PB2,//3line mode set none
	.hspi_wp_io2_pin    = HSPI_WP_IO2_PB1,//set quad mode otherwise set none
	.hspi_hold_io3_pin  = HSPI_HOLD_IO3_PB0,//set quad mode otherwise set none
};
#if (SPI_SLAVE_NUM == MULTI_SLAVE)
#define SLAVE0_CSN_PIN HSPI_CSN_PB6
#define SLAVE1_CSN_PIN HSPI_CSN_PA1
#endif
#endif

#if (SPI_DEVICE == SPI_MASTER_DEVICE)
	/**********************************************************************************************************************
	*                                         SPI master setting 				                                	 	  *
	*********************************************************************************************************************/
#define 	DATA_BYTE_LEN     16
unsigned char spi_rx_buff[DATA_BYTE_LEN] __attribute__((aligned(4))) = {0x00};
#if (SPI_TRANS_MODE == KITE_VULTURE_SLAVE_PROTOCOL)
	#define SPI_KITE_VULTURE_READ_CMD			0x80
	#define SPI_KITE_VULTURE_WRITE_CMD			0x00
	typedef struct {
		unsigned char address[3];
		unsigned char cmd;
		unsigned char data[DATA_BYTE_LEN];
	} __attribute__((aligned(4))) spi_tx_kite_vulture_slave_protocol_t;

	spi_tx_kite_vulture_slave_protocol_t  spi_tx_buff = {
		.address = {0x04, 0x40, 0x00},
		.cmd = SPI_KITE_VULTURE_WRITE_CMD,
		.data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};
#elif (SPI_TRANS_MODE == HSPI_PSPI_SLAVE_PROTOCOL)

#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_config_t pspi_slave_protocol_config = {
		.pspi_io_mode 	= PSPI_SINGLE,
		.pspi_dummy_cnt = 8,
		.pspi_cmd_en 	= 1,
	};
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_config_t hspi_slave_protocol_config = {
		.hspi_io_mode 		= HSPI_SINGLE,
		.hspi_dummy_cnt 	= 8,
		.hspi_cmd_en 		= 1,
		.hspi_addr_en 		= 0,//must
		.hspi_addr_len 		= 4,//when hspi_addr_en = false, invalid set.
		.hspi_cmd_fmt_en 	= 0,//when hspi_cmd_en = false, invalid set.
		.hspi_addr_fmt_en 	= 0,//when hspi_addr_en = false, invalid set.
	};
#endif
	typedef struct
	{
		unsigned char address[4];
		unsigned char data_len;
		unsigned char data[DATA_BYTE_LEN + 3];
	} spi_tx_eagle_hspi_pspi_slave_protocol_t;

	spi_tx_eagle_hspi_pspi_slave_protocol_t  spi_tx_buff =
	{
		.address = {0xc0, 0x00, 0x00, 0x00},
		.data_len = DATA_BYTE_LEN + 3,
		.data = {0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};
#elif(SPI_TRANS_MODE == SPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_config_t spi_slave_protocol_config = {
		.pspi_io_mode 	= PSPI_SINGLE,
		.pspi_dummy_cnt = 8,
		.pspi_cmd_en 	= 1,
	};

#elif(SPI_MODULE_SEL == HSPI_MODULE)
#define spi_slave_address	0xc0000200
	hspi_config_t spi_slave_protocol_config = {
		.hspi_io_mode 		= HSPI_SINGLE,
		.hspi_dummy_cnt 	= 8,
		.hspi_cmd_en 		= 1,
		.hspi_addr_en 		= 1,
		.hspi_addr_len 		= 4,//when hspi_addr_en = false, invalid set.
		.hspi_cmd_fmt_en 	= 0,//when hspi_cmd_en = false, invalid set.
		.hspi_addr_fmt_en 	= 1,//when hspi_addr_en = false, invalid set.
	};
#endif
	typedef struct
	{
#if(SPI_MODULE_SEL == PSPI_MODULE)
		unsigned char address[4];
#endif
		unsigned char data[DATA_BYTE_LEN];
	}  __attribute__((aligned(4)))  spi_tx_eagle_spi_slave_protocol_t;
	spi_tx_eagle_spi_slave_protocol_t spi_tx_buff =
	{
#if(SPI_MODULE_SEL == PSPI_MODULE)
		.address = {0xc0, 0x00, 0x02, 0x00},
#endif
		.data = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	};


#endif

void user_init()
{
	delay_ms(2000);
	gpio_function_en(LED4);
	gpio_output_en(LED4); 		//enable output
	gpio_input_dis(LED4);			//disable input
	gpio_set_high_level(LED4);              	//LED On
#if(SPI_MODULE_SEL == PSPI_MODULE)
	spi_master_init(SPI_MODULE_SEL, sys_clk.pclk * 1000000 / (2 * SPI_CLK) - 1, SPI_MODE0);
	pspi_set_pin(&pspi_pin_config);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_set_pin(&hspi_pin_config);
	spi_master_init(SPI_MODULE_SEL, sys_clk.hclk * 1000000 / (2 * SPI_CLK) - 1, SPI_MODE0);
#endif

#if (SPI_TRANS_MODE == KITE_VULTURE_SLAVE_PROTOCOL)
	spi_master_config(SPI_MODULE_SEL, SPI_NOMAL);
#elif(SPI_TRANS_MODE == HSPI_PSPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_master_config_plus(&pspi_slave_protocol_config);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_master_config_plus(&hspi_slave_protocol_config);
#endif
#elif(SPI_TRANS_MODE == SPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_master_config_plus(&spi_slave_protocol_config);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_master_config_plus(&spi_slave_protocol_config);
#endif
#endif
}

void main_loop (void)
{
	delay_ms(500);
	gpio_toggle(LED4);
#if (SPI_TRANS_MODE == KITE_VULTURE_SLAVE_PROTOCOL)
	spi_tx_buff.cmd = SPI_KITE_VULTURE_WRITE_CMD;
	spi_master_write(SPI_MODULE_SEL, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff));
	spi_tx_buff.cmd = SPI_KITE_VULTURE_READ_CMD;
	spi_master_write_read(SPI_MODULE_SEL, (unsigned char*)&spi_tx_buff, 4, (unsigned char*)spi_rx_buff, DATA_BYTE_LEN);
	for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
	{
		if(spi_tx_buff.data[i] != (spi_rx_buff[i]))
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	spi_tx_buff.data[0]++;
#elif(SPI_TRANS_MODE == HSPI_PSPI_SLAVE_PROTOCOL)
	spi_master_write_plus(SPI_MODULE_SEL, SPI_WRITE_DATA_SINGLE_CMD, 0x00, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_DUMMY_WRITE);
	spi_master_read_plus(SPI_MODULE_SEL, SPI_READ_DATA_SINGLE_CMD, 0x00, (unsigned char*)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
	for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
	{
		if(spi_tx_buff.data[3 + i] != (spi_rx_buff[i]))
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	spi_tx_buff.data[3]++;
#elif(SPI_TRANS_MODE == SPI_SLAVE_PROTOCOL)
#if(SPI_MODULE_SEL == HSPI_MODULE)
	spi_master_write_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_CMD, spi_slave_address, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
	spi_master_read_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_CMD, spi_slave_address, (unsigned char*)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_RD_DUMMY_READ);
#endif
#if(SPI_MODULE_SEL == PSPI_MODULE)
	spi_master_write_plus(SPI_MODULE_SEL, SPI_SLAVE_WRITE_DATA_CMD, 0x00, (unsigned char*)&spi_tx_buff, sizeof(spi_tx_buff), SPI_MODE_WR_WRITE_ONLY);
	spi_master_write_read_plus(SPI_MODULE_SEL, SPI_SLAVE_READ_DATA_CMD, (unsigned char*)&spi_tx_buff, 4, (unsigned char*)spi_rx_buff, DATA_BYTE_LEN, SPI_MODE_WR_DUMMY_RD);
#endif
	for (unsigned char i = 0; i < DATA_BYTE_LEN; i++)
	{
		if(spi_tx_buff.data[i] != (spi_rx_buff[i]))
		{
			gpio_set_high_level(LED2);//LED on indicate data error
		}
	}
	spi_tx_buff.data[0]++;
#endif
#if (SPI_SLAVE_NUM == MULTI_SLAVE)
#if (SPI_MODULE_SEL == HSPI_MODULE)
	if (hspi_pin_config.hspi_csn_pin == SLAVE0_CSN_PIN)
	{
		hspi_pin_config.hspi_csn_pin = hspi_change_csn_pin(SLAVE1_CSN_PIN);
	}
	else if (hspi_pin_config.hspi_csn_pin == SLAVE1_CSN_PIN)
	{
		hspi_pin_config.hspi_csn_pin = hspi_change_csn_pin(SLAVE0_CSN_PIN);
	}
#elif (SPI_MODULE_SEL == PSPI_MODULE)
	if (pspi_pin_config.pspi_csn_pin == SLAVE0_CSN_PIN)
	{
		pspi_pin_config.pspi_csn_pin = pspi_change_csn_pin(SLAVE1_CSN_PIN);
	}
	else if (pspi_pin_config.pspi_csn_pin == SLAVE1_CSN_PIN)
	{
		pspi_pin_config.pspi_csn_pin = pspi_change_csn_pin(SLAVE0_CSN_PIN);
	}
#endif
#endif
}

#elif(SPI_DEVICE == SPI_SLAVE_DEVICE)
	/**********************************************************************************************************************
	*                                         SPI slave setting 				                                	 	  *
	*********************************************************************************************************************/
void user_init()
{
	delay_ms(2000);
	gpio_function_en(LED4 | LED2);
	gpio_output_en(LED4 | LED2); 		//enable output
	gpio_input_dis(LED4 | LED2);			//disable input
	gpio_set_high_level(LED4 | LED2);              	//LED On
#if(SPI_TRANS_MODE!= SPI_SLAVE_PROTOCOL)
	spi_slave_init(SPI_MODULE_SEL, SPI_MODE0);
	core_interrupt_enable();
	spi_set_irq_mask(SPI_MODULE_SEL, SPI_SLV_CMD_EN |SPI_RXFIFO_INT_EN |SPI_END_INT_EN );//endint_en txfifoint_en rxfifoint_en
#if(SPI_MODULE_SEL == PSPI_MODULE)
	pspi_set_pin(&pspi_pin_config);
	plic_interrupt_enable(IRQ23_SPI_APB);
#elif(SPI_MODULE_SEL == HSPI_MODULE)
	hspi_set_pin(&hspi_pin_config);
	plic_interrupt_enable(IRQ22_SPI_AHB);
#endif
#if(SPI_SLAVE_MODE == SPI_3LINE_SLAVE)
	spi_set_3line_mode(SPI_MODULE_SEL);
#endif
#elif(SPI_TRANS_MODE == SPI_SLAVE_PROTOCOL)
	spi_slave_set_pin();//EAGLE_SPI_SLAVE only need set pin.
#endif
}

void main_loop(void)
{
	delay_ms(500);
	gpio_toggle(LED4);
}


#if(SPI_TRANS_MODE == HSPI_PSPI_SLAVE_PROTOCOL)
#define SPI_RX_BUFF_LEN     24
#define DATA_BYTE_LEN    	16
#define DATA_BYTE_OFFSET    8 //must be a multiple 4
unsigned char spi_rx_buff[SPI_RX_BUFF_LEN] __attribute__((aligned(4))) = {0x00};
volatile  unsigned int hspi_irq_rx_cnt = 0;
volatile  unsigned char  slave_cmd;
volatile  unsigned int hspi_tx_cnt = 0;
volatile  unsigned int hspi_tx_num = 0;
/*  handle cmd  interrupt when received read cmd enable txfifo interrupt */
_attribute_ram_code_sec_ void spi_irq_slv_cmd_process(void)
{
	slave_cmd = spi_slave_get_cmd(SPI_MODULE_SEL);
	switch (slave_cmd)
	{
	case SPI_READ_DATA_SINGLE_CMD:
		spi_set_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN);//enable txfifo_int
	break;
	case SPI_READ_DATA_DUAL_CMD:
		spi_set_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN);//enable txfifo_int
	break;
	case HSPI_READ_DATA_QUAD_CMD:
		spi_set_irq_mask(SPI_MODULE_SEL, SPI_TXFIFO_INT_EN);//enable txfifo_int
	break;
	}
}
 /*  handle txfifo  interrupt to return data that received from data master */
_attribute_ram_code_sec_ void spi_irq_tx_fifo_process(void)
{
	hspi_tx_num = spi_rx_buff[4] - 3;// return data number to master.
	if ((hspi_tx_num - hspi_tx_cnt) < 4)
	{
		spi_write(SPI_MODULE_SEL, spi_rx_buff + DATA_BYTE_OFFSET + hspi_tx_cnt, hspi_tx_num - hspi_tx_cnt);
		spi_clr_irq_mask(SPI_MODULE_SEL,SPI_TXFIFO_INT_EN);//disable txfifo_int
		hspi_tx_cnt = 0;//reset
		hspi_tx_num = 0;
	}

	else
	{
		spi_write(SPI_MODULE_SEL, spi_rx_buff + DATA_BYTE_OFFSET + hspi_tx_cnt, 4);
		spi_clr_irq_status(SPI_MODULE_SEL, SPI_TXF_INT);//clr
		hspi_tx_cnt += 4;
	}

}
 /*  handle rxfifo  interrupt to  received data from  master */
_attribute_ram_code_sec_ void spi_irq_rx_fifo_process(void)
{
	if(hspi_irq_rx_cnt < (SPI_RX_BUFF_LEN-(SPI_RX_BUFF_LEN % 4)))
	{
		spi_read(SPI_MODULE_SEL, spi_rx_buff + hspi_irq_rx_cnt, 4);
		hspi_irq_rx_cnt += 4;
		}
	else
	{
		spi_read(SPI_MODULE_SEL, spi_rx_buff + hspi_irq_rx_cnt, SPI_RX_BUFF_LEN % 4);
		hspi_irq_rx_cnt += SPI_RX_BUFF_LEN % 4;
		spi_rx_fifo_clr(SPI_MODULE_SEL);
	}
}

 /*  handle end  interrupt to  received remains data  from master */
_attribute_ram_code_sec_ void spi_irq_end_process(void)
{

	if(((spi_get_rxfifo_num(SPI_MODULE_SEL)) != 0) && (hspi_irq_rx_cnt < SPI_RX_BUFF_LEN))
	{
		spi_read(SPI_MODULE_SEL, spi_rx_buff + hspi_irq_rx_cnt,  spi_get_rxfifo_num(SPI_MODULE_SEL));
	}
	spi_tx_fifo_clr(SPI_MODULE_SEL);
	spi_rx_fifo_clr(SPI_MODULE_SEL);
	hspi_irq_rx_cnt = 0;
}

#if(SPI_MODULE_SEL == PSPI_MODULE)
_attribute_ram_code_sec_ void pspi_irq_handler(void)
#elif(SPI_MODULE_SEL == HSPI_MODULE)
_attribute_ram_code_sec_ void hspi_irq_handler(void)
#endif
{
	gpio_toggle(LED2);
	if (spi_get_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT))
	{
		spi_irq_slv_cmd_process();
		spi_clr_irq_status(SPI_MODULE_SEL,SPI_SLV_CMD_INT);//clr
		gpio_toggle(LED2);
	}

	if (spi_get_irq_status(SPI_MODULE_SEL,SPI_RXF_INT))
	{
		spi_irq_rx_fifo_process();
		spi_clr_irq_status(SPI_MODULE_SEL,SPI_RXF_INT);//clr
		gpio_toggle(LED2);
	}

	if(spi_get_irq_status(SPI_MODULE_SEL,SPI_END_INT))
	{
		spi_irq_end_process();
		spi_clr_irq_status(SPI_MODULE_SEL,SPI_END_INT);//clr
		gpio_toggle(LED2);
	}

	if (spi_get_irq_status(SPI_MODULE_SEL,SPI_TXF_INT))
	{
		spi_irq_tx_fifo_process();
		spi_clr_irq_status(SPI_MODULE_SEL,SPI_TXF_INT);//clr
		gpio_toggle(LED2);
	}

}
#endif
#endif
#endif



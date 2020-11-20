/********************************************************************************************************
 * @file	app_dma.c
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


#if(I2C_MASTER_WRITE_READ_MODE == I2C_MASTER_WRITE_READ_DMA)

/************************************************  i2c_mode  **********************************/
#define  	I2C_MASTER_DEVICE        	1   //i2c master demo
#define     I2C_SLAVE_DEVICE			2   //i2c slave demo

#define     I2C_DEVICE					I2C_MASTER_DEVICE


#define     I2C_CLK_SPEED				200000 //i2c clock 200K.

#define  I2C_TX_DMA_CHN  DMA1
#define  I2C_RX_DMA_CHN  DMA0
#define  I2C_RX_DMA_STATUS  BIT(I2C_RX_DMA_CHN)

#define LED1            GPIO_PB4//blue
#define LED2            GPIO_PB5//green
#define LED3            GPIO_PB6//white
#define LED4            GPIO_PB7//red


//This length is the total length, including both the length of the slave RAM address(First three bytes) and the length of the data to be sent.
#define     BUFF_DATA_LEN_DMA	 	     	     16
volatile unsigned char i2c_tx_buff[BUFF_DATA_LEN_DMA] __attribute__((aligned(4))) = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};


#define     RX_BUFF_DATA_LEN_DMA	 	     	 16

volatile unsigned char i2c_rx_buff[RX_BUFF_DATA_LEN_DMA] __attribute__((aligned(4)));


void user_init(void)
{
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);

	i2c_set_pin(I2C_GPIO_SDA_B3,I2C_GPIO_SCL_B2);
	i2c_set_rx_dma_config(I2C_RX_DMA_CHN);
	i2c_set_tx_dma_config(I2C_TX_DMA_CHN);

#if(I2C_DEVICE == I2C_MASTER_DEVICE)
	//For eagle the slave ID is 0x5a, for kite the slave ID is 0x5c.
	i2c_master_init();
	i2c_set_master_clk((unsigned char)(sys_clk.pclk*1000*1000/(4*I2C_CLK_SPEED)));//set i2c frequency 200K.
#elif(I2C_DEVICE == I2C_SLAVE_DEVICE)

	i2c_slave_init(0x5a);
	core_interrupt_enable();
	plic_interrupt_enable(IRQ5_DMA);

	dma_clr_irq_mask(I2C_TX_DMA_CHN,TC_MASK|ERR_MASK|ABT_MASK);
	dma_clr_irq_mask(I2C_RX_DMA_CHN,TC_MASK|ERR_MASK|ABT_MASK);

	dma_set_irq_mask(I2C_RX_DMA_CHN, TC_MASK);

	i2c_clr_irq_status(I2C_TX_DONE_CLR);
	i2c_set_irq_mask(I2C_TX_DONE_MASK);
	core_interrupt_enable();
	plic_interrupt_enable(IRQ21_I2C);

	i2c_slave_set_rx_dma((unsigned char*)i2c_rx_buff,RX_BUFF_DATA_LEN_DMA);





#endif
}

void main_loop(void)
{
#if(I2C_DEVICE == I2C_MASTER_DEVICE)


	i2c_tx_buff[4]++;

	i2c_master_write_dma(0x5a,(unsigned char *)i2c_tx_buff,BUFF_DATA_LEN_DMA);
	while(i2c_master_busy());
	delay_ms(10);
    i2c_master_read_dma(0x5a,(unsigned char *)i2c_rx_buff,RX_BUFF_DATA_LEN_DMA);
	while(i2c_master_busy());

	for(volatile unsigned int i=0;i<RX_BUFF_DATA_LEN_DMA;i++)
	{
		if( i2c_rx_buff[i] != i2c_tx_buff[i] )
		{
			gpio_toggle(LED2);
			delay_ms(50);
		}
	}
	gpio_toggle(LED1);
#endif
}

/**
 * @brief		This function serves to handle the interrupt of i2c
 * @param[in] 	none
 * @return 		none
 */
void dma_irq_handler(void)
{
#if(I2C_DEVICE == I2C_SLAVE_DEVICE)

    if(dma_get_tc_irq_status(I2C_RX_DMA_STATUS))
    {
    	i2c_slave_set_tx_dma((unsigned char*)i2c_rx_buff,RX_BUFF_DATA_LEN_DMA);
        gpio_toggle(LED1);
        dma_clr_tc_irq_status(I2C_RX_DMA_STATUS);
	}

	gpio_toggle(LED3);


#endif

}


 void i2c_irq_handler(void)
{

#if(I2C_DEVICE == I2C_SLAVE_DEVICE)
	if(i2c_get_irq_status(I2C_TXDONE_STATUS))
	{

		i2c_slave_set_rx_dma((unsigned char*)i2c_rx_buff,RX_BUFF_DATA_LEN_DMA);
		i2c_clr_irq_status(I2C_TX_DONE_CLR);
        gpio_toggle(LED2);
	}

#endif
}




#endif















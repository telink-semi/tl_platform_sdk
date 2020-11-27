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
#include "app_sin_data.h"
#include <string.h>
unsigned int  dma_rx_irq_cnt=0;
#if ((AUDIO_MODE==LINEIN_TO_LINEOUT)||(AUDIO_MODE==AMIC_TO_LINEOUT)||(AUDIO_MODE==DMIC_TO_LINEOUT)||(AUDIO_MODE==EXT_CODEC_LINEIN_LINEOUT))
#define    AUDIO_BUFF_SIZE    4096
volatile signed short AUDIO_BUFF[AUDIO_BUFF_SIZE>>1] __attribute__((aligned(4)));
#elif(AUDIO_MODE==BUFFER_TO_LINEOUT)
dma_chain_config_t tx_dma_list_config[2];
#define    MIC_BUFFER_SIZE    (441*4)

#elif(AUDIO_MODE==FLASH_TO_LINEOUT)
#define FLASH_16k_SIZE    0x3400
#define FLASH_BUFF_ZERO    1024

#define FLASH_48k_SIZE    0xF000
#define AUIDO_BUFF_SIZE   4096
#define AUIDO_THD_SIZE    1024
 unsigned char flash_read_16K_buff[FLASH_16k_SIZE]__attribute__((aligned(4)));
 unsigned char flash_read_48K_buff[FLASH_48k_SIZE]__attribute__((aligned(4)));
 unsigned char aduio_buff [AUIDO_BUFF_SIZE] __attribute__((aligned(4)));

volatile unsigned int tx_rptr_out=0;
volatile unsigned int tx_wptr_out=0;
volatile unsigned int flash_rptr=0;
volatile unsigned short remaining;
volatile unsigned char ex_cnt;
volatile unsigned char swith;
unsigned long t;
#endif


void user_init()
{
#if(CHIP_VER_A0==CHIP_VER)
	audio_set_codec_supply(CODEC_2P8V);
#endif
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
#if (AUDIO_MODE==LINEIN_TO_LINEOUT)
	audio_init(LINE_IN_TO_BUF_TO_LINE_OUT,AUDIO_16K,MONO_BIT_16);
	audio_rx_dma_chain_init(DMA2,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);
	audio_tx_dma_chain_init (DMA3,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);

#elif(AUDIO_MODE==AMIC_TO_LINEOUT)
	audio_init(AMIC_IN_TO_BUF_TO_LINE_OUT ,AUDIO_16K,MONO_BIT_16);
	audio_rx_dma_chain_init(DMA2,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);
	audio_tx_dma_chain_init (DMA3,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);
#elif(AUDIO_MODE==DMIC_TO_LINEOUT)
	audio_set_dmic_pin(DMIC_GROUPB_B2_DAT_B3_B4_CLK);
	audio_init(DMIC_IN_TO_BUF_TO_LINE_OUT ,AUDIO_16K,MONO_BIT_16);
	audio_rx_dma_chain_init(DMA2,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);
	audio_tx_dma_chain_init (DMA3,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);

#elif(AUDIO_MODE==BUFFER_TO_LINEOUT)
	audio_init(BUF_TO_LINE_OUT,AUDIO_44EP1K,MONO_BIT_16);
	/*ping-pong buff*/
	audio_tx_dma_config(DMA3,(unsigned short*)(&sin_44K1_d1[0]),MIC_BUFFER_SIZE,&tx_dma_list_config[0]);
	audio_tx_dma_add_list_element(&tx_dma_list_config[0],&tx_dma_list_config[1],(unsigned short*)(&sin_44K1_d2[0]),MIC_BUFFER_SIZE);
	audio_tx_dma_add_list_element(&tx_dma_list_config[1],&tx_dma_list_config[0],(unsigned short*)(&sin_44K1_d1[0]),MIC_BUFFER_SIZE);
	audio_tx_dma_en();

#elif(AUDIO_MODE==FLASH_TO_LINEOUT)
	flash_read_page(0x8000,FLASH_16k_SIZE,(unsigned char *)flash_read_16K_buff);
	flash_read_page(0xe000,FLASH_48k_SIZE,(unsigned char *)flash_read_48K_buff);
	audio_init(BUF_TO_LINE_OUT,AUDIO_48K,MONO_BIT_16);
	audio_tx_dma_chain_init (DMA3,(unsigned short*)aduio_buff,AUIDO_BUFF_SIZE);
#elif(AUDIO_MODE==EXT_CODEC_LINEIN_LINEOUT)
	/* WM8731 for demo*/
	audio_i2s_init(PWM_PWM0_PB4,I2C_GPIO_SDA_B3,I2C_GPIO_SCL_B2);
	audio_rx_dma_chain_init(DMA0,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);
	audio_tx_dma_chain_init (DMA1,(unsigned short*)AUDIO_BUFF,AUDIO_BUFF_SIZE);

#endif
}


#if(AUDIO_MODE==FLASH_TO_LINEOUT)
_attribute_ram_code_sec_ void audio_data_fifo(unsigned char *pdata, unsigned int buff_len)
{
	unsigned short unused_buff;
	tx_rptr_out = ((audio_get_tx_dma_rptr (DMA3)-(unsigned int)aduio_buff));
	if((tx_wptr_out&(AUIDO_BUFF_SIZE - 1))>tx_rptr_out)
	{
		unused_buff=AUIDO_BUFF_SIZE-(tx_wptr_out&(AUIDO_BUFF_SIZE-1))+tx_rptr_out;
	}
	else
	{
		unused_buff=tx_rptr_out-tx_wptr_out;
	}

	if(unused_buff>AUIDO_THD_SIZE)
	{
		gpio_toggle(LED3);
		memcpy(aduio_buff+tx_wptr_out,pdata+flash_rptr,AUIDO_THD_SIZE);
		tx_wptr_out=(tx_wptr_out+AUIDO_THD_SIZE)&(AUIDO_BUFF_SIZE-1);
		flash_rptr=(flash_rptr+AUIDO_THD_SIZE);
		if(flash_rptr>=(buff_len))
		{
		   flash_rptr=0;
		}
	}

}
#endif


/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
#if(AUDIO_MODE==FLASH_TO_LINEOUT)
#if 1
	audio_data_fifo(flash_read_48K_buff,FLASH_48k_SIZE);
#endif
	/////////////////////adc  power on/down test /////////////////////////////////////////
#if 0
	audio_data_fifo(flash_read_48K_buff,FLASH_48k_SIZE);
	if(clock_time_exceed(t,4000000))
	{
		  t = stimer_get_tick()|1;
		 gpio_toggle(LED4);
		 ex_cnt++;
		 if(ex_cnt&1)
		  {
			     audio_codec_dac_power_down();

		  }
		  else
		  {
			    audio_codec_dac_power_on();

		  }

	  }
#endif
	/////////////////////exchange dac sample rate  test /////////////////////////////////////////
#if 0
	if(swith==0)
	{
		audio_data_fifo(flash_read_48K_buff,FLASH_48k_SIZE);
	}
	else

	{
		audio_data_fifo(flash_read_16K_buff,FLASH_16k_SIZE);
	}

	 if(clock_time_exceed(t,3000000))
{
	t = stimer_get_tick()|1;
	gpio_toggle(LED4);
	ex_cnt++;
	if(ex_cnt&1)
	{
		audio_pause_out_path();
		audio_change_sample_rate(AUDIO_16K);
		memset(aduio_buff,0,AUIDO_BUFF_SIZE);//Clear data that does not match the dac sampling rate
		audio_resume_out_path();
		swith=1;
		flash_rptr=0;
	}
	else
	{
		audio_pause_out_path();
		audio_change_sample_rate(AUDIO_48K);
		memset(aduio_buff,0,AUIDO_BUFF_SIZE);//Clear data that does not match the dac sampling rate
		audio_resume_out_path();
		swith=0;
		flash_rptr=0;
	}

}
#endif
#endif

}





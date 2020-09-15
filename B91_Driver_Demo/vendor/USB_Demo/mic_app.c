/********************************************************************************************************
 * @file	mic_app.c
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
#include "app_config.h"
#if(USB_DEMO_TYPE==USB_MICROPHONE)
#include "usb_default.h"
#include "application/usbstd/usb.h"
#define AUDIO_LINE_IN            0
#define AUDIO_AMIC_IN            1
#define AUDIO_DMIC_IN            2

#define  AUDIO_IN_MODE          AUDIO_AMIC_IN

#define MIC_SAMPLING_RATE   (MIC_SAMPLE_RATE== 8000) ?  AUDIO_8K :((MIC_SAMPLE_RATE== 16000) ?  AUDIO_16K :(  (MIC_SAMPLE_RATE== 32000) ?  AUDIO_32K :( (MIC_SAMPLE_RATE== 48000) ? AUDIO_48K : AUDIO_16K) ) )
#define MIC_MONO_STEREO       ((MIC_CHANNLE_COUNT==1) ?  MONO_BIT_16 :STEREO_BIT_16 )

#define	MIC_BUFFER_SIZE			2048
#define MIC_DMA_CHN             DMA2


u16		iso_in_buff[MIC_BUFFER_SIZE];

volatile u32		iso_in_w = 0;
volatile u32  	     iso_in_r = 0;
u32		num_iso_in = 0;
/**
 * @brief     This function serves to send data to USB. only adaptive mono 16bit
 * @param[in] audio_rate - audio rate. This value is matched with usb_default.h :MIC_SAMPLE_RATE.
 * @return    none.
 */

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
	unsigned char length = 0;
	iso_in_w = ((audio_get_rx_dma_wptr (MIC_DMA_CHN) - (u32)iso_in_buff) >> 1);
	 usbhw_reset_ep_ptr(USB_EDP_MIC);//reset pointer of Endpoint7's buf
	switch(audio_rate)
	{
		case 	AUDIO_8K:	length = 8* MIC_CHANNLE_COUNT;break;
		case	AUDIO_16K:	length = 16*MIC_CHANNLE_COUNT;break;
		case	AUDIO_32K:	length = 32*MIC_CHANNLE_COUNT;break;
		case	AUDIO_48K:	length = 48*MIC_CHANNLE_COUNT;break;
		default:			length = 16*MIC_CHANNLE_COUNT;break;
	}

	if (0 &&(iso_in_w - (iso_in_r&(MIC_BUFFER_SIZE-1)))< length)
	{
		for (u8 i=0; i<length*2; i++)
		{
			reg_usb_ep7_dat = 0;
		}
	}

	else
	{
		for (u8 i=0; i<length&& iso_in_r != iso_in_w ; i++)
		{
			short md = iso_in_buff[iso_in_r++ &(MIC_BUFFER_SIZE-1)];
			reg_usb_ep7_dat = md;
			reg_usb_ep7_dat = md >>8;
		}

	}
	 usbhw_data_ep_ack(USB_EDP_MIC);;
}
/**
 * @brief		This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in] 	none
 * @return 		none
 */
void  usb_endpoint_irq_handler (void)
{
	if (usbhw_get_eps_irq() & FLD_USB_EDP7_IRQ)
	{

		usbhw_clr_eps_irq(FLD_USB_EDP7_IRQ);;	//clear interrupt flag of endpoint 7
		/////// get MIC input data ///////////////////////////////
		audio_tx_data_to_usb(MIC_SAMPLING_RATE);
		num_iso_in++;
		if ((num_iso_in & 0x7f) == 0)		gpio_toggle(LED1);
	}

}

void user_init(void)
{
	audio_set_codec_supply();
	gpio_function_en(LED1|LED2|LED3|LED4);
    gpio_output_en(LED1|LED2|LED3|LED4);
	reg_usb_ep6_buf_addr = 0x40;		// 192 max
	reg_usb_ep7_buf_addr = 0x20;		// 32
	reg_usb_ep8_buf_addr = 0x00;
	reg_usb_ep_max_size = (192 >> 3);
	//1.enable USB DP pull up 1.5k
	usb_set_pin_en();
	//2.enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
	usb_init_interrupt();
	//3.enable global interrupt
	core_interrupt_enable();
	plic_interrupt_enable(IRQ11_USB_ENDPOINT);		// enable usb endpoint interrupt
	usbhw_set_eps_irq_mask(FLD_USB_EDP7_IRQ);
	usbhw_set_irq_mask(USB_IRQ_RESET_MASK|USB_IRQ_SUSPEND_MASK);
#if(AUDIO_IN_MODE==AUDIO_LINE_IN)
	audio_init(LINE_IN_ONLY ,MIC_SAMPLING_RATE,MIC_MONO_STEREO);
	audio_rx_dma_chain_init(DMA2,(u16*)&iso_in_buff,MIC_BUFFER_SIZE*2);
#elif(AUDIO_IN_MODE==AUDIO_DMIC_IN)
	audio_set_dmic_pin(DMIC_GROUPB_B2_DAT_B3_B4_CLK);
	audio_init(DMIC_IN_ONLY ,MIC_SAMPLING_RATE,MIC_MONO_STEREO);
	audio_rx_dma_chain_init(DMA2,(u16*)&iso_in_buff,MIC_BUFFER_SIZE*2);
#elif(AUDIO_IN_MODE==AUDIO_AMIC_IN)
	audio_init(AMIC_IN_ONLY ,MIC_SAMPLING_RATE,MIC_MONO_STEREO);
	audio_rx_dma_chain_init(DMA2,(u16*)&iso_in_buff,MIC_BUFFER_SIZE*2);
#endif

}

void main_loop (void)
{
	usb_handle_irq();
}

#endif



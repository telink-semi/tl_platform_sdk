/********************************************************************************************************
 * @file	mic_spk_app.c
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
#if(USB_DEMO_TYPE==USB_MIC_SPEAKER)
#include "usb_default.h"
#include "application/usbstd/usb.h"
#define AUDIO_SAMPLING_RATE  AUDIO_48K
#define LED1            GPIO_PB4
#define LED2            GPIO_PB5
#define LED3            GPIO_PB6
#define LED4            GPIO_PB7
#define MIC_DMA_CHN             DMA2
#define SPK_DMA_CHN             DMA3
#define	MIC_BUFFER_SIZE			4096
#define	SPK_BUFFER_SIZE			4096

unsigned short		iso_in_buff[MIC_BUFFER_SIZE];
unsigned short		iso_out_buff[SPK_BUFFER_SIZE];

int		iso_in_w = 0;
int		iso_in_r = 0;

int		iso_out_w = 0;
int		iso_out_r = 0;

/**
 * @brief     This function serves to send data to USB. only adaptive mono 16bit
 * @param[in] audio_rate - audio rate. This value is matched with usb_default.h :MIC_SAMPLE_RATE.
 * @return    none.
*/

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
	unsigned char length = 0;
	iso_in_w = ((audio_get_rx_dma_wptr(MIC_DMA_CHN) - (unsigned int)iso_in_buff) >> 1);
	 usbhw_reset_ep_ptr(USB_EDP_MIC);//reset pointer of Endpoint7's buf

	switch(audio_rate)
	{
		case 	AUDIO_8K:	length = 8* MIC_CHANNLE_COUNT;break;
		case	AUDIO_16K:	length = 16*MIC_CHANNLE_COUNT;break;
		case	AUDIO_32K:	length = 32*MIC_CHANNLE_COUNT;break;
		case	AUDIO_48K:	length = 48*MIC_CHANNLE_COUNT;break;
		default:			length = 16*MIC_CHANNLE_COUNT;break;
	}

		for (unsigned char i=0; i<length&& iso_in_r != iso_in_w ; i++)
		{
			short md = iso_in_buff[iso_in_r++ &(MIC_BUFFER_SIZE-1)];
			reg_usb_ep7_dat = md;
			reg_usb_ep7_dat = md >>8;
		}
   usbhw_data_ep_ack(USB_EDP_MIC);

}




/**
 * @brief     This function servers to set USB Input.
 * @param[in] none
 * @return    none.
 */
void  audio_rx_data_from_usb ()
{
	unsigned char len = reg_usb_ep_ptr(USB_EDP_SPEAKER);
	usbhw_reset_ep_ptr(USB_EDP_SPEAKER);
	for (unsigned int i=0; i<len; i+=4)
	{
		signed short d0 = reg_usb_ep6_dat;
		d0 |= reg_usb_ep6_dat << 8;
	    signed short d1 = reg_usb_ep6_dat;
		d1 |= reg_usb_ep6_dat << 8;
#if 0
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d0;
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d1;
#else
		unsigned int d = (d0 + d1) >> 1;
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d;
#endif
	}
	usbhw_data_ep_ack(USB_EDP_SPEAKER);
}



int		num_iso_in = 0;
int 	num_iso_out = 0;

_attribute_ram_code_sec_ void  usb_endpoint_irq_handler (void)
{
	/////////////////////////////////////
	// ISO IN
	/////////////////////////////////////
	if (usbhw_get_eps_irq()& FLD_USB_EDP7_IRQ)
	{
		usbhw_clr_eps_irq(FLD_USB_EDP7_IRQ);	//clear interrupt flag of endpoint 7
		/////// get MIC input data ///////////////////////////////
		audio_tx_data_to_usb(AUDIO_16K);
		num_iso_in++;
		if ((num_iso_in & 0x7f) == 0) gpio_toggle(LED2);
	}

	/////////////////////////////////////
	// ISO OUT
	/////////////////////////////////////
	if (usbhw_get_eps_irq()&FLD_USB_EDP6_IRQ)
	{
		usbhw_clr_eps_irq(FLD_USB_EDP6_IRQ);
		///////////// output to audio fifo out ////////////////
		audio_rx_data_from_usb();
		num_iso_out++;
		if ((num_iso_out & 0x7f) == 0) gpio_toggle(LED3);
	}

}


void user_init(void)
{
#if(CHIP_VER_A0==CHIP_VER)
	audio_set_codec_supply(CODEC_2P8V);
#endif
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);

	reg_usb_ep6_buf_addr = 0x40;		// 192 max
	reg_usb_ep7_buf_addr = 0x20;		// 32
	reg_usb_ep8_buf_addr = 0x00;
	reg_usb_ep_max_size = (192 >> 3);
	plic_interrupt_enable(IRQ11_USB_ENDPOINT);		// enable usb endpoint interrupt

	//1.enable USB DP pull up 1.5k
	usb_set_pin_en();
	//2.enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
	usb_init_interrupt();
	//3.enable global interrupt
	core_interrupt_enable();
	usbhw_set_eps_irq_mask(FLD_USB_EDP7_IRQ|FLD_USB_EDP6_IRQ);
	usbhw_set_irq_mask(USB_IRQ_RESET_MASK|USB_IRQ_SUSPEND_MASK);
	audio_init(LINE_IN_TO_BUF_TO_LINE_OUT,AUDIO_ADC_16K_DAC_48K,MONO_BIT_16);//mic sampling=16K,spk sampling=48K,should match the setting in usb_default.h.
	audio_rx_dma_chain_init(MIC_DMA_CHN,iso_in_buff,MIC_BUFFER_SIZE * 2);
	audio_tx_dma_chain_init (SPK_DMA_CHN,iso_out_buff, SPK_BUFFER_SIZE * 2);
}

void main_loop (void)
{

	usb_handle_irq();
}


#endif

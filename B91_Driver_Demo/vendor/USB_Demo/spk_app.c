/********************************************************************************************************
 * @file	spk_app.c
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
#include "application/usbstd/usb.h"
#if(USB_DEMO_TYPE==USB_SPEAKER)
#define SPK_SAMPLING_RATE   (SPEAKER_SAMPLE_RATE== 8000) ?  AUDIO_8K :((SPEAKER_SAMPLE_RATE== 16000) ?  AUDIO_16K :(  (SPEAKER_SAMPLE_RATE== 32000) ?  AUDIO_32K :( (SPEAKER_SAMPLE_RATE== 48000) ? AUDIO_48K : AUDIO_16K) ) )
#define SPK_DMA_CHN    DMA3
#define	SPK_BUFFER_SIZE			2048
u16		iso_out_buff[SPK_BUFFER_SIZE];

volatile u32		iso_out_w = 0;
volatile u32  	     iso_out_r = 0;
volatile u32  	     iso_out_w_r = 0;

u32		            num_iso_out = 0;

u8 more_rate;
u8 less_rate;
u8 equal_rate;
void user_init(void)
{
	audio_set_codec_supply();
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);

	reg_usb_ep6_buf_addr = 0x40;		// 192 max
	reg_usb_ep7_buf_addr = 0x20;		// 32
	reg_usb_ep8_buf_addr = 0x00;
	reg_usb_ep_max_size = (192 >> 3);
	//reg_usb_mask = BIT(6) | BIT(7);			//audio out interrupt enable

	usbhw_data_ep_ack(6);
	//1.enable USB DP pull up 1.5k
	usb_set_pin_en();
	//2.enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
	usb_init_interrupt();
	//3.enable global interrupt
	core_interrupt_enable();
	plic_interrupt_enable(IRQ11_USB_ENDPOINT);		// enable usb endpoint interrupt
	usbhw_set_eps_irq_mask(FLD_USB_EDP6_IRQ);
	usbhw_set_irq_mask(USB_IRQ_RESET_MASK|USB_IRQ_SUSPEND_MASK);
	audio_init(OUT_ONLY ,SPK_SAMPLING_RATE,MONO_BIT_16);
	audio_tx_dma_chain_init(SPK_DMA_CHN,(u16*)&iso_out_buff,SPK_BUFFER_SIZE*2);
}

/**
 * @brief     This function servers to set USB Input.
 * @param[in] none
 * @return    none.
 */
void  audio_rx_data_from_usb ()
{
	u8 len = reg_usb_ep6_ptr;
	usbhw_reset_ep_ptr(USB_EDP_SPEAKER);
	for (u32 i=0; i<len; i+=4)
	{
		s16 d0 = reg_usb_ep6_dat;
		d0 |= reg_usb_ep6_dat << 8;
	    s16 d1 = reg_usb_ep6_dat;
		d1 |= reg_usb_ep6_dat << 8;
#if 0
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d0;
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d1;
#else
		u32 d = (d0 + d1) >> 1;
		iso_out_buff[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = d;

#endif
		iso_out_w_r=((iso_out_w&(SPK_BUFFER_SIZE - 1))- iso_out_r)&(SPK_BUFFER_SIZE - 1);

	}
	usbhw_data_ep_ack(USB_EDP_SPEAKER);
}


void  usb_endpoint_irq_handler (void)
{
	/////////////////////////////////////
             	// ISO OUT
	/////////////////////////////////////
	if (usbhw_get_eps_irq()&FLD_USB_EDP6_IRQ)
	{
		usbhw_clr_eps_irq(FLD_USB_EDP6_IRQ);
		///////////// output to audio fifo out ////////////////
		audio_rx_data_from_usb();
		num_iso_out++;
		if ((num_iso_out & 0x7f) == 0)		gpio_toggle(LED2);
	}

}
#if 0
/**
 * @brief     This function servers to adjust sampling rate .
 * @param[in] none
 * @return    none.
 */
_attribute_ram_code_sec_noinline_  void change_rate(void)
	{
		iso_out_r = ((audio_get_tx_dma_rptr (SPK_DMA_CHN) - (u32)iso_out_buff) >> 1);


		if((((iso_out_w&(SPK_BUFFER_SIZE - 1))- iso_out_r)&(SPK_BUFFER_SIZE - 1))<1000)

		{
			audio_set_i2s_clock(AUDIO_48K,AUDIO_RATE_LT_L1,1);
			less_rate++;
			gpio_toggle(LED3);
		}

		else  if((((iso_out_w&(SPK_BUFFER_SIZE - 1))- iso_out_r)&(SPK_BUFFER_SIZE - 1))>2000)

		{

			 audio_set_i2s_clock(SPK_SAMPLING_RATE,AUDIO_RATE_GT_L1,1);
			 gpio_toggle(LED4);
			 more_rate++;

		}

		else
		{

			audio_set_i2s_clock(SPK_SAMPLING_RATE,AUDIO_RATE_LT_L0,1);
			equal_rate++;

	    }



	}
#endif

void main_loop (void)
{
	usb_handle_irq();
}
#endif



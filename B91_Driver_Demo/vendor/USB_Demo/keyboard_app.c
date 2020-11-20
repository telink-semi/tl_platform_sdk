/********************************************************************************************************
 * @file	keyboard_app.c
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
#if(USB_DEMO_TYPE==USB_KEYBOARD)
#include "application/usb_app/usbkb.h"
#include "application/usbstd/usb.h"
unsigned char  kb_data[6];

// BYTE0: special key(Ctrl/shift ...);
// BYTE1: reserved;
// BYTE2~BYTE7: normal key

void user_init()
{
	//1.enable USB DP pull up 1.5k
	usb_set_pin_en();
	//2.enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
	usb_init_interrupt();
	//3.enable global interrupt
	core_interrupt_enable();

	usbhw_set_irq_mask(USB_IRQ_RESET_MASK|USB_IRQ_SUSPEND_MASK);

	//initiate LED for indication
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_input_dis(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
	gpio_set_high_level(LED1|LED2|LED3|LED4);
	gpio_function_en(GPIO_PC1);
	gpio_input_en(GPIO_PC1);
	gpio_output_dis(GPIO_PC1);
	gpio_set_up_down_res(GPIO_PC1, GPIO_PIN_PULLUP_10K);

	gpio_function_en(GPIO_PC2);
	gpio_input_en(GPIO_PC2);
	gpio_output_dis(GPIO_PC2);
	gpio_set_up_down_res(GPIO_PC2, GPIO_PIN_PULLUP_10K);
}


void main_loop (void)
{
	usb_handle_irq();

		if(gpio_get_level(GPIO_PC1)==0)
		{
			delay_us(10000);
			if(gpio_get_level(GPIO_PC1)==0)
			{
				while(gpio_get_level(GPIO_PC1)==0);
				gpio_set_high_level(LED1);
				// normal key: data[0]~data[5]
			    kb_data[0] = 0;
				kb_data[1] = 0;
				kb_data[2] = 0x59;	// number key: 1
				kb_data[3] = 0;  // number key: 2
				kb_data[4] = 0;
				kb_data[5] = 0;

				usbkb_hid_report_normal(0x00,kb_data);

			}
		}

		if(gpio_get_level(GPIO_PC2)==0)
		{
			delay_us(10000);
			if(gpio_get_level(GPIO_PC2)==0)
			{
				while(gpio_get_level(GPIO_PC2)==0);
			{
					for(int i=0;i<6;i++)
					{
						kb_data[i]=0;
					}
				}

				usbkb_hid_report_normal(0x00,kb_data);
			}
		}
	}

#endif

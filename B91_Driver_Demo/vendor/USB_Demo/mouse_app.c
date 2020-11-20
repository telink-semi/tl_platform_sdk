/********************************************************************************************************
 * @file	mouse_app.c
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
#if(USB_DEMO_TYPE==USB_MOUSE)
#include "application/usbstd/usb.h"
#include "application/usb_app/usbmouse.h"

char  mouse[4];

void user_init(void)
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
	delay_us(100000);
	gpio_set_low_level(LED1|LED2|LED3|LED4);

	//initiate Button for Mouse input
	gpio_function_en(GPIO_PC1);
	gpio_input_en(GPIO_PC1);
	gpio_output_dis(GPIO_PC1);
	gpio_set_up_down_res(GPIO_PC1, GPIO_PIN_PULLUP_10K);

	gpio_function_en(GPIO_PC2);
	gpio_input_en(GPIO_PC2);
	gpio_output_dis(GPIO_PC2);
	gpio_set_up_down_res(GPIO_PC2, GPIO_PIN_PULLUP_10K);
}

/* enum to USB input device and simulate the left click and right click of mouse */
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
			//printf("Key:Mouse  Click ! \r\n");
			mouse[0] = BIT(1);// BIT(0) - left key; BIT(1) - right key; BIT(2) - middle key; BIT(3) - side key; BIT(4) - external key
			mouse[1] = -2;	  // Displacement relative to x coordinate
			mouse[2] = 2;	  // Displacement relative to y coordinate
			mouse[3] = 0;     // Displacement relative to the roller
			usbmouse_hid_report(USB_HID_MOUSE,(unsigned char*)mouse,4);
		}
	}

	if(gpio_get_level(GPIO_PC2)==0)
	{
		delay_us(10000);
		if(gpio_get_level(GPIO_PC2)==0)
		{
			while(gpio_get_level(GPIO_PC2)==0);
			gpio_set_low_level(LED1);
			//printf("Key:release \r\n");
			mouse[0] = 0;
			mouse[1] = 0;
			mouse[2] = 0;
			mouse[3] = 0;
			usbmouse_hid_report(USB_HID_MOUSE,(unsigned char*)mouse,4);
		}
	}
}

#endif

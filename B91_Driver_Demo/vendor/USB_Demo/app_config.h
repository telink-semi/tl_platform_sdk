/********************************************************************************************************
 * @file	app_config.h
 *
 * @brief	This is the header file for B91
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
#pragma once
#include "../../drivers.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define LED1            GPIO_PB4
#define LED2            GPIO_PB5
#define LED3            GPIO_PB6
#define LED4            GPIO_PB7

#define	 USB_MOUSE          1
#define	 USB_KEYBOARD		2
#define	 USB_MICROPHONE		3
#define	 USB_SPEAKER		4
#define	 USB_CDC	        5
#define	 USB_MIC_SPEAKER    6

#define	 USB_DEMO_TYPE		USB_MOUSE



#if	(USB_DEMO_TYPE == USB_MOUSE)
	#define	USB_MOUSE_ENABLE 		1
#elif (USB_DEMO_TYPE == USB_KEYBOARD)
	#define	USB_KEYBOARD_ENABLE 	1
#elif (USB_DEMO_TYPE == USB_MICROPHONE)
	#define	  USB_MIC_ENABLE 		1
#elif (USB_DEMO_TYPE == USB_SPEAKER)
	#define	USB_SPEAKER_ENABLE 		1
#elif (USB_DEMO_TYPE == USB_CDC)
	#define USB_CDC_ENABLE          1
#elif (USB_DEMO_TYPE == USB_MIC_SPEAKER)
	#define	USB_MIC_ENABLE 			1
	#define	USB_SPEAKER_ENABLE 		1
#endif


#define CHIP_VER_A0              0
#define CHIP_VER_A1              1
#define CHIP_VER             CHIP_VER_A1










/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

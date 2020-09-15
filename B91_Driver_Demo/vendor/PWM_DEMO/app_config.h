/********************************************************************************************************
 * @file	app_config.h
 *
 * @brief	This is the header file for B91
 *
 * @author	D.M.H / Z.S.X
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
#include "../../drivers.h"
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define	 PWM_CONTINUE		    1
#define	 PWM_COUNT			    2
#define	 PWM_IR			        3
#define	 PWM_IR_FIFO		    4
#define	 PWM_IR_DMA		        5

#define	 SET_PWM_MODE		   PWM_IR_DMA
  /*
   * PWM0:GPIO_PB4  GPIO_PC0  GPIO_PE3
   * PWM1:GPIO_PB5  GPIO_PE1
   * PWM2:GPIO_PB7  GPIO_PE2
   * PWM3:GPIO_PB1  GPIO_PE0
   * PWM4:GPIO_PD7  GPIO_PE4
   * PWM5:GPIO_PB0  GPIO_PE5
   *
   * PWM0_N:GPIO_PD0
   * PWM1_N:GPIO_PD1
   * PWM2_N:GPIO_PD2  GPIO_PE6
   * PWM3_N:GPIO_PD3  GPIO_PE7
   * PWM4_N:GPIO_PD4
   * PWM5_N:GPIO_PD5
   *
   * */

#define LED1            GPIO_PB4
#define LED2            GPIO_PB5
#define LED3            GPIO_PB6
#define LED4            GPIO_PB7


#define     PWM_PCLK_SPEED				12000000 //pwm clock 12M.
#define     PWM_32K_SPEED               32000    //pwm 32K


/**
 * This configure is for PWM Ticks.
 */
enum{
	CLOCK_PWM_CLOCK_1S = PWM_PCLK_SPEED,
	CLOCK_PWM_CLOCK_1MS = (CLOCK_PWM_CLOCK_1S / 1000),
	CLOCK_PWM_CLOCK_1US = (CLOCK_PWM_CLOCK_1S / 1000000),
};

enum{
	CLOCK_PWM_32K_1S = PWM_32K_SPEED,
	CLOCK_PWM_32K_1MS = (CLOCK_PWM_32K_1S  / 1000),
};











/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

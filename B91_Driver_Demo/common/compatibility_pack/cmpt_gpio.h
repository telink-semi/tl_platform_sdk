/********************************************************************************************************
 * @file	cmpt_gpio.h
 *
 * @brief	This is the header file for B91
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
/**	@page GPIO
 *
 *	Introduction
 *	===============
 *	TLSR9518 contain two six group gpio(A~F), total 44 gpio pin.
 *
 *	API Reference
 *	===============
 *	Header File: gpio.h
 */
#ifndef DRIVERS_CMPT_GPIO_H_
#define DRIVERS_CMPT_GPIO_H_

#include "../../drivers/B91/gpio.h"
/**********************************************************************************************************************
 *                                         global constants                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           global macro                                                             *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                         global data type                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                     global variable declaration                                                    *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                      global function prototype                                                     *
 *********************************************************************************************************************/
#define gpio_setup_up_down_resistor  gpio_set_up_down_res

#define  gpio_read                    gpio_get_level


/**
 * @brief     This function set the pin's output level.
 * @param[in] pin - the pin needs to set its output level
 * @param[in] value - value of the output level(1: high 0: low)
 * @return    none
 */
static inline void gpio_write(gpio_pin_e pin, unsigned char value)
{
	if(value)
	{
		gpio_set_high_level(pin);
	}
	else
	{
		gpio_set_low_level(pin);
	}
}





/**
 * @brief      This function enable set output function of a pin.
 * @param[in]  pin - the pin needs to set the output function (1: enable,0: disable)
 * @return     none
 */
static inline void gpio_set_output_en(gpio_pin_e pin, unsigned char value)
{
	if(value)
	{
		gpio_output_en(pin);
	}
	else
	{
		gpio_output_dis(pin);
	}


}

/**
 * @brief      This function servers to set gpio function.
 * @param[in]  pin - the selected pin.
 * @param[in]  value - enable or disable the pin's gpio  function(1: enable,0: disable )
 * @return    none
 */
 void gpio_set_gpio_en(gpio_pin_e pin, unsigned char value);



/**
 * @brief      This function set the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function
 * @param[in]  value - enable or disable the pin's input function(1: enable,0: disable )
 * @return     none
 */
void gpio_set_input_en(gpio_pin_e pin, unsigned char value);


#endif

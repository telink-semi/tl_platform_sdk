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

/**********************************************************************************************************************
*                                         swire device selection                                                	 *
*********************************************************************************************************************/
#define SWIRE_MASTER_DEVICE		       		  1
#define SWIRE_SLAVE_DEVICE		      		  2
#define SWIRE_DEVICE				   		  SWIRE_MASTER_DEVICE


#define DATA_LEN			6
#define ADDRESS_LEN			4			//B91s is four bytes, B85s is three bytes.
#define ADDRESS_VALUE		0xc0000000
#define SLAVE_ID			0           //The default id of an empty chip is 0
#define SWIRE_SPEED			1000000


unsigned char wbuf[DATA_LEN] = {};
unsigned char rbuf[DATA_LEN] = {};
void user_init()
{
	gpio_function_en(LED1|LED2|LED3|LED4);
	gpio_output_en(LED1|LED2|LED3|LED4);
	gpio_input_dis(LED1|LED2|LED3|LED4);
	delay_ms(3000);
#if (SWIRE_DEVICE == SWIRE_MASTER_DEVICE)
	unsigned int i;
	for( i = 0; i < DATA_LEN; i++){
		wbuf[i]= i;
	}
	swire_set_swm_en();
	//Swire communication needs to be connected to a pull-up resistor
	//if there is no external pull-up, the software configuration of the pull-up resistor is required
	gpio_set_up_down_res(GPIO_SWM, GPIO_PIN_PULLUP_10K);
	swire_set_clk(SWIRE_SPEED);
#else
	swire_set_sws_en();
	swire_set_slave_id(SLAVE_ID);
#endif

}


void main_loop (void)
{
#if (SWIRE_DEVICE == SWIRE_MASTER_DEVICE)
	unsigned char i;
	unsigned int addr = ADDRESS_VALUE;
	swire_master_write(SLAVE_ID,(unsigned char*)(&addr),ADDRESS_LEN,wbuf,DATA_LEN);
	unsigned int read_result = swire_master_read(SLAVE_ID,(unsigned char*)(&addr),ADDRESS_LEN,rbuf,DATA_LEN);
	if(read_result == 0){
		//read timeout
		gpio_set_high_level(LED4);
	}else{
		for( i = 0; i < DATA_LEN; i++){
			if(wbuf[i] != rbuf[i]){
				break;
			}
		}
		if(i<DATA_LEN){
			//read error
			gpio_set_high_level(LED4);
		}else{
			//read ok
			gpio_set_high_level(LED1);
		}
	}
	//If you keep reading and writing in the mainloop and use the BDT to access the chip through sws at the same time,
	//sometimes there will be BDT access errors (the reason is: there is a problem with the BMC of the B91 chip, so there will be such a phenomenon)
	//In case there is a bus conflict, after the test, the program stops here
	gpio_input_dis(GPIO_SWM);
	gpio_output_dis(GPIO_SWM);
	gpio_function_en(GPIO_SWM);
	gpio_set_low_level(LED2);
	while(1);
#else
	gpio_toggle(LED1|LED2|LED3|LED4);
	delay_ms(1000);
#endif
}












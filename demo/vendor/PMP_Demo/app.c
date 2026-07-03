/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#include "common.h"
#include "pmp_config.h"

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);

    //PMP hardware init
    init_pmp_config();

#if(MCU_MODE==U_MODE)
    /**
       Switch to user mode and jump to the user_app function to start the user program.
       Note:
              1.If the user_app address is configured as non-executable, it will trigger an exception when started,
              which can also serve as a check for executability.
              2.The hardware initialization should be completed as much as possible before switching to User mode.
              Otherwise, in User mode, there may be insufficient permissions to access certain registers, leading to exceptions.
       Modify by kun.he, confirmed by minghai.duan at 20230928
     */
    switch_to_user_mode(user_app);
#else
    /**
       Switch to machine mode and jump to the user_app function to start the user program.
       Note:
              1. On MCU power-up, the default privilege level is Machine Mode.
              Using this function in Machine Mode is similar to function jumps.
              2. In PMP configuration, the lock bit must be set to 1 for PMP configurations to take effect.
       Modify by kun.he, confirmed by minghai.duan at 20230928
     */
    switch_to_machine_mode(user_app);
#endif
    /**
     * Note: After switching modes, the function will not return.
     * If it returns, the program logic will be incorrect
     */
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop(void)
{
    //Never execute
    gpio_toggle(LED1);
    gpio_toggle(LED2);
    gpio_toggle(LED3);
    gpio_toggle(LED4);
    delay_ms(500);
}

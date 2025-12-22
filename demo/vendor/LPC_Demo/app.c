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
#include "lpc.h"


#define LPC_GPIO_DETECTION   0
#if defined(MCU_CORE_TL323X)
#define LPC_VBAT_DETECTION   1
#endif
#define LPC_DETECTION_MODE   LPC_GPIO_DETECTION

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

#if LPC_DETECTION_MODE == LPC_GPIO_DETECTION
#if defined(MCU_CORE_TL751X)
    lpc_gpio_vol_detect_init(LPC_NORMAL,LPC_INPUT_PG5,LPC_REF_872MV,LPC_SCALING_PER50);
#else
    //When the chip works in low power mode, the reference voltage can only be provided by UVLO or from PB0 and PB3.
    lpc_gpio_vol_detect_init(LPC_NORMAL,LPC_INPUT_PB5,LPC_REF_872MV,LPC_SCALING_PER50);
#endif
#elif LPC_DETECTION_MODE == LPC_VBAT_DETECTION
    lpc_vbat_vol_detect_init(LPC_VBAT_FALLING_2P20V_RISING_2P30V);

#endif
    //LPC POWER must be turned on last.
    lpc_power_on();
    //The LPC sampling clock source is RC 32K. After turning on the LPC POWER, you must wait for two sampling periods to obtain the sampling value.
    delay_us(64);
}

void main_loop(void)
{
    printf("result = %d\r\n", lpc_get_result());
    gpio_toggle(LED1);
    delay_ms(200);
}

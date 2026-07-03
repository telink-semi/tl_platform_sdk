/********************************************************************************************************
 * @file    app_pwm.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
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

/**************************** include header *********************************/
#include "common.h"

#if (TIMER_MODE == TIMER_PWM_MODE)

#include "inc/drv_cpr.h"
#include "modules/drv_gpio.h"
#include "inc/drv_timer.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include "inc/drv_delay.h"
#include "hal/hal_timer.h"

/**
 * Note:pwm_pin_mux() only initialize PB1/6/7/8/9 for PWM function, to use other gpio,
 *      please modify the gpio configuration in pwm_pin_mux().
 */
/********************************************************************************
    Timer1 - PWM1   :  PA10_FUNC_2.   PB0_FUNC_9.     PB9_FUNC_9.
    Timer2 - PWM2   :  PA0_FUNC_9.    PA23_FUNC_4.    PB6_FUNC_9.    PB10_FUNC_1.
    Timer3 - PWM3   :  PB1_FUNC_9.
    Timer4 - PWM4   :  PA11_FUNC_2.   PA24_FUNC_4.    PB7_FUNC_9.
    Timer5 - PWM5   :  PA0_FUNC_7.    PB3_FUNC_6.     PB8_FUNC_9.
********************************************************************************/

#define TIMER1_EN      1
#define TIMER2_EN      2
#define TIMER3_EN      3
#define TIMER4_EN      4
#define TIMER5_EN      5
#define TIMER_ENABLE   TIMER1_EN

timer_handle_t timer0_1;
timer_handle_t timer0_2;
timer_handle_t timer0_3;
timer_handle_t timer1_0;
timer_handle_t timer1_1;

// log init
uart_handle_t uart_handle;

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_UART1_CLK_ENABLE();
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}
void pwm_pin_mux(void)
{
    gpio_init_t gpio_init;
    __DRV_CPR_UART1_CLK_ENABLE();
    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_9 | GPIO_PIN_6 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_9;
    drv_gpio_init(&gpio_init);
}

void user_init(void)
{
    log_init();
    pwm_pin_mux();

    soc_printf(" timer pwm mode sample\r\n");
    soc_printf("NOTE:only TIMER1~TIMER5 has pwm mode,Timer0/6/7 does not have a PWM mode\r\n");

#if TIMER_ENABLE == TIMER1_EN//PWM1->PB9
    timer_init(TIMER1);
    timer0_1.instance = TIMER0_3;
    timer0_1.init.timer_num = TIMER1;//timer0_1
    timer0_1.init.period = 500 * sys_clk.pclk * TIMER_TICK_CLOCK_1MS;
    timer0_1.init.duty_cycle = 10;//duty_clycle = 500ms*10%
    timer0_1.init.function = TIMER_PWM;
    timer0_1.init.mode = TIMER_USER_DEF;
    drv_timer_set_duty_cycle(&timer0_1);
    drv_timer_init(&timer0_1);
    drv_timer_control(&timer0_1, TIMER_START);

#elif TIMER_ENABLE == TIMER2_EN//PWM2->PB6
    timer_init(TIMER2);
    timer0_2.instance = TIMER0_3;
    timer0_2.init.timer_num = TIMER2;//timer0_2
    timer0_2.init.period = 500 * sys_clk.pclk * TIMER_TICK_CLOCK_1MS;
    timer0_2.init.duty_cycle = 20;//duty_clycle = 500ms*20%
    timer0_2.init.function = TIMER_PWM;
    timer0_2.init.mode = TIMER_USER_DEF;
    drv_timer_set_duty_cycle(&timer0_2);
    drv_timer_init(&timer0_2);
    drv_timer_control(&timer0_2, TIMER_START);

#elif TIMER_ENABLE == TIMER3_EN//PWM3->PB1
    timer_init(TIMER3);
    timer0_3.instance = TIMER0_3;
    timer0_3.init.timer_num = TIMER3;//Timer0_3
    timer0_3.init.period = 500 * sys_clk.pclk * TIMER_TICK_CLOCK_1MS;
    timer0_3.init.duty_cycle = 30;//duty_clycle = 500ms*30%
    timer0_3.init.function = TIMER_PWM;
    timer0_3.init.mode = TIMER_USER_DEF;
    drv_timer_set_duty_cycle(&timer0_3);
    drv_timer_init(&timer0_3);
    drv_timer_control(&timer0_3, TIMER_START);

#elif TIMER_ENABLE == TIMER4_EN//PWM4->PB7
    timer_init(TIMER4);
    timer1_0.instance = TIMER4_7;
    timer1_0.init.timer_num = TIMER0;//Timer1_0
    timer1_0.init.period = 500 * sys_clk.pclk * TIMER_TICK_CLOCK_1MS;
    timer1_0.init.duty_cycle = 40;//duty_clycle = 500ms*40%
    timer1_0.init.function = TIMER_PWM;
    timer1_0.init.mode = TIMER_USER_DEF;
    drv_timer_set_duty_cycle(&timer1_0);
    drv_timer_init(&timer1_0);
    drv_timer_control(&timer1_0, TIMER_START);
#elif TIMER_ENABLE == TIMER5_EN//PWM5->PB3
    timer_init(TIMER5);
    timer1_1.instance = TIMER4_7;
    timer1_1.init.timer_num = TIMER1;//Timer1_1
    timer1_1.init.period = 500 * sys_clk.pclk * TIMER_TICK_CLOCK_1MS;
    timer1_1.init.duty_cycle = 50;//duty_clycle = 500ms*50%
    timer1_1.init.function = TIMER_PWM;
    timer1_1.init.mode = TIMER_USER_DEF;
    drv_timer_set_duty_cycle(&timer1_1);
    drv_timer_init(&timer1_1);
    drv_timer_control(&timer1_1, TIMER_START);
#endif
    soc_printf("please test pwm waveform using a oscilloscopes\r\n");
}
void main_loop(void){

}
#endif

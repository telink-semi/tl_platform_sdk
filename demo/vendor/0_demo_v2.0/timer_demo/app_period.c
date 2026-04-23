/********************************************************************************************************
 * @file    app_period.c
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

#if (TIMER_MODE == TIMER_PERIOD_MODE)

#include "inc/drv_cpr.h"
#include "modules/drv_gpio.h"
#include "inc/drv_timer.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include "inc/drv_uart.h"
#include "hal/hal_timer.h"

#define TIMER0_EN      0
#define TIMER1_EN      1
#define TIMER4_EN      4
#define TIMER_ENABLE   TIMER0_EN

#define TIMER_PERIOD_TIME (10)

timer_handle_t timer0_0;
timer_handle_t timer0_1;
timer_handle_t timer0_2;
timer_handle_t timer0_3;
timer_handle_t timer1_0;
timer_handle_t timer1_1;
timer_handle_t timer1_2;
timer_handle_t timer1_3;

volatile char toggle_flag=0;
volatile int  timer_counter=0;
#if TIMER_ENABLE == TIMER0_EN

_attribute_ram_code_sec_ void timer0_irq_handler(void)
{
     if(toggle_flag == 0)
     {
        drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 0);
        toggle_flag = 1;
     }else
     {
         drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 1);
         toggle_flag = 0;
     }
     soc_printf("timer0 period timeout\r\n");
     timer_counter++;
     timer_clr_irq_status(FLD_TMR0_MODE_IRQ);
     if (TIMER_PERIOD_TIME == timer_counter)
     {
        plic_interrupt_disable(IRQ_TIMER0_0);
        timer_clr_irq_mask(FLD_TMR0_MODE_IRQ);
        timer_stop(TIMER0);
     }
}
PLIC_ISR_REGISTER(timer0_irq_handler, IRQ_TIMER0_0)
#elif TIMER_ENABLE == TIMER1_EN
_attribute_ram_code_sec_ void timer1_irq_handler(void)
{
     if(toggle_flag == 0)
     {
        drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 0);
        toggle_flag = 1;
     }else
     {
         drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 1);
         toggle_flag = 0;
     }
     soc_printf("timer1 period timeout\r\n");
     timer_counter++;
     timer_clr_irq_status(FLD_TMR1_MODE_IRQ);
     if (TIMER_PERIOD_TIME == timer_counter)
     {
        plic_interrupt_disable(IRQ_TIMER0_1);
        timer_clr_irq_mask(FLD_TMR1_MODE_IRQ);
        timer_stop(TIMER1);
     }
}
PLIC_ISR_REGISTER(timer1_irq_handler, IRQ_TIMER0_1)

#elif (TIMER_ENABLE == TIMER4_EN)
_attribute_ram_code_sec_ void timer4_irq_handler(void)
{
     if(toggle_flag == 0)
     {
        drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 0);
        toggle_flag = 1;
     }else
     {
         drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 1);
         toggle_flag = 0;
     }
     soc_printf("timer4 period timeout\r\n");
     timer_counter++;
     timer_clr_irq_status(FLD_TMR4_MODE_IRQ);
     if (TIMER_PERIOD_TIME == timer_counter)
     {
        plic_interrupt_disable(IRQ_TIMER1_0);
        timer_clr_irq_mask(FLD_TMR4_MODE_IRQ);
        timer_stop(TIMER4);
     }
}
PLIC_ISR_REGISTER(timer4_irq_handler, IRQ_TIMER1_0)
#endif

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


void user_init(void)
{
    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_7| GPIO_PIN_14;
    gpio_init.mode = MODE_OUTPUT;
    gpio_init.electric = GPIO_ELECTRIC_2MA;
    drv_gpio_init(&gpio_init);
    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 0);

    log_init();

#if TIMER_ENABLE == TIMER0_EN
    plic_interrupt_enable(IRQ_TIMER0_0);
    core_interrupt_enable();
    timer_init(TIMER0);
    timer_set_cap_tick(TIMER0,500 * sys_clk.pclk);//If the system clock is 48 MHz RC, the actual frequency is only 32 MHz
    timer_set_mode(TIMER0, TIMER_MODE_SYSCLK);
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    timer_start(TIMER0);

#elif TIMER_ENABLE == TIMER1_EN
    plic_interrupt_enable(IRQ_TIMER0_1);
    core_interrupt_enable();
    timer_init(TIMER1);
    timer_set_cap_tick(TIMER1,500 * sys_clk.pclk);//If the system clock is 48 MHz RC, the actual frequency is only 32 MHz
    timer_set_mode(TIMER1, TIMER_MODE_SYSCLK);
    timer_set_irq_mask(FLD_TMR1_MODE_IRQ);
    timer_start(TIMER1);
#elif TIMER_ENABLE == TIMER4_EN
    plic_interrupt_enable(IRQ_TIMER1_0);
    core_interrupt_enable();
    timer_init(TIMER4);
    timer_set_cap_tick(TIMER4,500 * sys_clk.pclk);//If the system clock is 48 MHz RC, the actual frequency is only 32 MHz
    timer_set_mode(TIMER4, TIMER_MODE_SYSCLK);
    timer_set_irq_mask(FLD_TMR4_MODE_IRQ);
    timer_start(TIMER4);
#endif

    drv_gpio_writepin(GPIO_PORT_A, GPIO_PIN_7, 1);
    soc_printf("timer period \n");
}
void main_loop(void){

}

#endif

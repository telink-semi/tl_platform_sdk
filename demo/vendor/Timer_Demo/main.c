/********************************************************************************************************
 * @file    main.c
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
#include "app_config.h"

extern void user_init(void);
extern void main_loop (void);
volatile int timer0_irq_cnt = 0;
volatile int timer1_irq_cnt = 0;
volatile unsigned int timer0_gpio_width =0;
volatile unsigned int timer1_gpio_width =0;

_attribute_ram_code_sec_ void timer0_irq_handler(void)
{
#if( TIMER_MODE == TIMER_SYS_CLOCK_MODE )
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR0_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR0))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR0);//clear irq status
#endif
        gpio_toggle(LED2);
        timer0_irq_cnt ++;
    }
#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR0_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR0))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR0);//clear irq status
#endif
        gpio_toggle(LED2);
        timer0_irq_cnt ++;
    }
#elif(TIMER_MODE == TIMER_GPIO_WIDTH_MODE)
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR0_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR0))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR0);//clear irq status
#endif
        timer0_gpio_width = timer0_get_gpio_width();
        timer0_set_tick(0);
        gpio_toggle(LED2);
    }
#endif
}
PLIC_ISR_REGISTER(timer0_irq_handler, IRQ_TIMER0)

_attribute_ram_code_sec_ void timer1_irq_handler(void)
{
#if( TIMER_MODE == TIMER_SYS_CLOCK_MODE )
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR1_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR1))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR1);//clear irq status
#endif
        gpio_toggle(LED3);
        timer1_irq_cnt ++;
    }
#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR1_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR1))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR1);//clear irq status
#endif
        gpio_toggle(LED3);
        timer1_irq_cnt ++;
    }
#elif(TIMER_MODE == TIMER_GPIO_WIDTH_MODE)
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    if(timer_get_irq_status(FLD_TMR1_MODE_IRQ))
#else
    if(timer_get_irq_status(TMR_STA_TMR1))
#endif
    {
#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ);//clear irq status
#else
        timer_clr_irq_status(TMR_STA_TMR1);//clear irq status
#endif
        timer1_gpio_width = timer1_get_gpio_width();
        timer1_set_tick(0);
        gpio_toggle(LED3);
    }

#endif
}
PLIC_ISR_REGISTER(timer1_irq_handler, IRQ_TIMER1)

/**
 * @brief       This is main function
 * @param[in]   none
 * @return      none
 */
int main(void)
{
    PLATFORM_INIT;
    CLOCK_INIT;
    user_init();

    while(1)
    {
        main_loop();
    }

    return 0;
}

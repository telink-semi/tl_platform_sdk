/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "lib/include/pm/pm.h"

/* Initialize CTB in single-channel or multi-channel mode based on compile-time macro */
#if (CTB_MODE == ONE_CHN_MODE)
    /* Set of touch channels enabled in single-channel mode: channel 0 */
    #define CTB_OPEN_CHANNELS CTB_CHANNEL_0
#else
    /* Set of touch channels enabled in multi-channel mode: channels 0~3 */
    #define CTB_OPEN_CHANNELS (CTB_CHANNEL_0 | CTB_CHANNEL_1 | CTB_CHANNEL_2 | CTB_CHANNEL_3)
#endif

volatile unsigned char ctb_flag = 0;
volatile unsigned int ctb_irq_cnt = 0;
volatile unsigned int pm_irq_cnt = 0;
volatile unsigned short touch_chn = 0;

/**
 * @brief User initialization, configures LED and CTB module and enables interrupts
 */
void user_init(void)
{
    /* Configure LED1 and LED2 pins as GPIO function */
    gpio_function_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED1);
    gpio_output_en(LED2);
    gpio_input_dis(LED1);
    gpio_input_dis(LED2);
    gpio_set_low_level(LED1);
    gpio_set_low_level(LED2);

#if (CTB_SENSITIVITY_MANUAL == CTB_SENSITIVITY_MANUAL_ON)
    ctb_sensitivity_manual_config(CTB_OPEN_CHANNELS, 100);
#endif
    ctb_init(CTB_OPEN_CHANNELS);

    plic_interrupt_enable(IRQ_PM_LVL);
    core_interrupt_enable();
}

void main_loop(void)
{
    if(ctb_flag == 1)
    {
        delay_ms(500);
        gpio_set_low_level(LED1);
        ctb_flag = 0;
    }
    gpio_toggle(LED2);
    delay_ms(500);
}

/**
 * @brief       This function serves to handle the interrupt of CTB.
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void pm_level_irq_handler(void)
{
    if (ctb_get_irq_status() & CTB_IRQ) {
        touch_chn = ctb_get_chn();
        ctb_clr_irq(touch_chn);
        printf("CHN %d TOUCH!\r\n",BIT_LOW_BIT(touch_chn));
        gpio_set_high_level(LED1);
        ctb_flag =1;
        ctb_irq_cnt++;
    }
    ctb_clear_irq_status();
    pm_irq_cnt++;
}
PLIC_ISR_REGISTER(pm_level_irq_handler, IRQ_PM_LVL)
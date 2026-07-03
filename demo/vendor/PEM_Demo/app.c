/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#if (DEMO_MODE == NORMAL_MODE)

#define PEM_PWM_EVENT_MODE      PWM_EVENT_PWM1_START
#define PEM_STIMER_EVENT_MODE   STIMER_EVENT_TRIG_POS
#define PEM_GPIO_EVENT_MODE     PA1_INPUT
#define PEM_STIMER_TASK_MODE    STIMER_TASK_EN
#define PEM_ADC_TASK_MODE       ADC_TASK_SINGLE_ADC_TRIG
#define PEM_GPIO_TASK_MODE      LED3_TOGGLE
#define PEM_PWM_TASK_MODE       PWM_TASK_PWM1_EN



void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);

    pem_init();

    #if (PEM_EVENT_MODE == PEM_STIMER)
    pem_event_stimer_init(PEM_ID, PEM_STIMER_EVENT_MODE);
    #elif (PEM_EVENT_MODE == PEM_PWM)
    pem_event_pwm_init(PEM_ID, PEM_PWM_EVENT_MODE);
    #elif (PEM_EVENT_MODE == PEM_SAR_ADC)
    pem_event_adc_init(PEM_ID, ADC_EVENT_RX_THRESHOLD);
    #elif (PEM_EVENT_MODE == PEM_GPIO)
    pem_event_gpio_init(PEM_ID, PEM_GPIO_EVENT_MODE, PEM_EVENT_RISING);
    #elif (PEM_EVENT_MODE == PEM_MISC)
    pem_event_misc_init(PEM_ID, MISC_EVENT_LPC);
    #endif

    #if (PEM_TASK_MODE == PEM_STIMER)
    pem_task_stimer_init(PEM_ID, PEM_STIMER_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_PWM)
    pem_task_pwm_init(PEM_ID, PEM_PWM_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_SAR_ADC)
    pem_task_adc_init(PEM_ID, PEM_ADC_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_GPIO)
    pem_task_gpio_init(PEM_ID, PEM_GPIO_TASK_MODE);
    #endif

    //start
    pem_chn_en(PEM_ID);

    #if (PEM_EVENT_MODE == PEM_STIMER)
    pem_event_stimer_start(PEM_STIMER_EVENT_MODE);
    #elif (PEM_EVENT_MODE == PEM_PWM)
    pem_event_pwm_start(PEM_PWM_EVENT_MODE);
    #elif (PEM_EVENT_MODE == PEM_SAR_ADC)
    pem_event_adc_start(ADC_EVENT_RX_THRESHOLD);
    #elif (PEM_EVENT_MODE == PEM_GPIO)
    pem_event_gpio_start(PEM_GPIO_EVENT_MODE);
    #elif (PEM_EVENT_MODE == PEM_MISC)
    pem_event_misc_start(MISC_EVENT_LPC);
    #endif
}

void main_loop(void)
{
    #if (PEM_TASK_MODE == PEM_STIMER)
    pem_task_stimer_mainloop(PEM_STIMER_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_PWM)
    pem_task_pwm_mainloop(PEM_PWM_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_SAR_ADC)
    pem_task_adc_mainloop(PEM_ADC_TASK_MODE);
    #elif (PEM_TASK_MODE == PEM_GPIO)
    pem_task_gpio_mainloop(PEM_GPIO_TASK_MODE);
    #endif
}

#endif

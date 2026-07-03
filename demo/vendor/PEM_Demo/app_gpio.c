/********************************************************************************************************
 * @file    app_gpio.c
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
#include "pem.h"

#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)
#define PEM_GPIO_GROUP         0x0700
#elif defined(MCU_CORE_TL521X)||defined(MCU_CORE_TL323X)
#define PEM_GPIO_GROUP         0x0600
#endif


void gpio_init_input(unsigned int gpio_sel)
{
    unsigned int gpio_pin = (gpio_sel&0xff00)|(1<<(gpio_sel&0x00ff));

    gpio_function_en(gpio_pin);
    gpio_output_dis(gpio_pin);
    gpio_input_en(gpio_pin);
}

void gpio_init_output(unsigned int gpio_sel)
{
    unsigned int gpio_pin = (gpio_sel&0xff00)|(1<<(gpio_sel&0x00ff));

    gpio_function_en(gpio_pin);
    gpio_output_en(gpio_pin);
}

void pem_event_gpio_init(unsigned char pem_id, unsigned int gpio_sel, pem_event_pol_e gpio_pol)
{
#if 1
    if(gpio_sel < PEM_GPIO_GROUP)
    {
        gpio_init_input(gpio_sel);
    }
#else
    switch (gpio_sel)
    {
    case PA0_INPUT:
        gpio_function_en(GPIO_PA0);
        gpio_output_dis(GPIO_PA0);
        gpio_input_en(GPIO_PA0);
        break;

    case PA1_INPUT:
        gpio_function_en(GPIO_PA1);
        gpio_output_dis(GPIO_PA1);
        gpio_input_en(GPIO_PA1);
        break;

    default:
        break;
    }
#endif

    gpio_set_pem_event(pem_id, gpio_sel, gpio_pol);
}

int pem_event_gpio_start(unsigned int gpio_sel)
{
    switch (gpio_sel)
    {
    case PA0_INPUT:
        break;

    default:
        break;
    }
    return 1;
}

void pem_task_gpio_init(unsigned char pem_id, unsigned int gpio_sel)
{
#if 1
    gpio_init_output(gpio_sel);

#else
    switch (gpio_sel)
    {
    case PA0_TOGGLE:
        gpio_function_en(GPIO_PA0);
        gpio_output_en(GPIO_PA0);
        break;

    case PA1_TOGGLE:
        gpio_function_en(GPIO_PA1);
        gpio_output_en(GPIO_PA1);
        break;

    case PC7_TOGGLE:
        gpio_function_en(GPIO_PC7);
        gpio_output_en(GPIO_PC7);
        break;

    default:
        break;
    }
#endif

    gpio_set_pem_task(pem_id, gpio_sel);
}

int pem_task_gpio_mainloop(unsigned int gpio_sel)
{
    switch (gpio_sel)
    {
    case PA0_TOGGLE:
        break;

    default:
        break;
    }
    return 1;
}

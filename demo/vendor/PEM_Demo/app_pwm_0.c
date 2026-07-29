/********************************************************************************************************
 * @file    app_pwm_0.c
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

void pwm0_init(gpio_func_pin_e pin)
{
    pwm_set_pin(pin, PWM0);
    pwm_set_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / PWM_PCLK_SPEED - 1));
    pwm_set_pwm0_mode(PWM_NORMAL_MODE);
    pwm_set_tcmp(PWM0_ID, 100 * CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM0_ID, 600 * CLOCK_PWM_CLOCK_1US);
}

void pwm1_init(gpio_func_pin_e pin)
{
    pwm_set_pin(pin, PWM1);
    pwm_set_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / PWM_PCLK_SPEED - 1));
    pwm_set_tcmp(PWM1_ID, 400 * CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM1_ID, 900 * CLOCK_PWM_CLOCK_1US);
}

void pwm2_init(gpio_func_pin_e pin)
{
    pwm_set_pin(pin, PWM2);
    pwm_set_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / PWM_PCLK_SPEED - 1));
    pwm_set_tcmp(PWM2_ID, 500 * CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM2_ID, 100 * CLOCK_PWM_CLOCK_1US);
}

void pem_event_pwm_init(unsigned char pem_id, unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_EVENT_PWM0_START:
        pwm0_init(PWM0_PIN);
        break;

    case PWM_EVENT_PWM1_START:
        pwm1_init(PWM1_PIN);
        break;

    case PWM_EVENT_PWM2_START:
        pwm2_init(PWM2_PIN);
        break;

    default:
        break;
    }

    pwm_set_pem_event(pem_id, pwm_sel);
}

int pem_event_pwm_start(unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_EVENT_PWM0_START:
        pwm_start(FLD_PWM0_EN);
        break;

    case PWM_EVENT_PWM1_START:
        pwm_start(FLD_PWM1_EN);
        break;

    case PWM_EVENT_PWM2_START:
        pwm_start(FLD_PWM2_EN);
        break;

    default:
        break;
    }

    return 1;
}

void pem_task_pwm_init(unsigned char pem_id, unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_TASK_PWM0_EN:
        pwm0_init(PWM0_PIN);
        break;

    case PWM_TASK_PWM1_EN:
        pwm1_init(PWM1_PIN);
        break;

    case PWM_TASK_PWM2_EN:
        pwm2_init(PWM2_PIN);
        break;

    default:
        break;
    }

    pwm_set_pem_task(pem_id, pwm_sel);
}

int pem_task_pwm_mainloop(unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_TASK_PWM0_EN:
        break;

    case PWM_TASK_PWM1_EN:
        break;

    case PWM_TASK_PWM2_EN:
        break;

    default:
        break;
    }
    return 1;
}


#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
void pem_event_pwm_1_init(unsigned char pem_id, unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_EVENT_PWM0_CYCDONE:
        pwm0_init(PWM0_PIN);
        break;

    case PWM_EVENT_PWM1_CYCDONE:
        pwm1_init(PWM1_PIN);
        break;

    case PWM_EVENT_PWM2_CYCDONE:
        pwm2_init(PWM2_PIN);
        break;

    default:
        break;
    }

    pwm_set_pem_event(pem_id, pwm_sel);
}

int pem_event_pwm_1_start(unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_EVENT_PWM0_CYCDONE:
        break;

    case PWM_EVENT_PWM1_CYCDONE:
        break;

    case PWM_EVENT_PWM2_CYCDONE:
        break;

    default:
        break;
    }

    return 1;
}

void pem_task_pwm_1_init(unsigned char pem_id, unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_TASK_PWM0_DISABLE:
        pwm0_init(PWM0_PIN);
        pwm_start(FLD_PWM0_EN);
        break;

    case PWM_TASK_PWM1_DISABLE:
        pwm1_init(PWM1_PIN);
        pwm_start(FLD_PWM1_EN);
        break;

    case PWM_TASK_PWM2_DISABLE:
        pwm2_init(PWM2_PIN);
        pwm_start(FLD_PWM2_EN);
        break;

    default:
        break;
    }

    pwm_set_pem_task(pem_id, pwm_sel);
}

int pem_task_pwm_1_mainloop(unsigned char pwm_sel)
{
    switch (pwm_sel)
    {
    case PWM_TASK_PWM0_DISABLE:
        break;

    case PWM_TASK_PWM1_DISABLE:
        break;

    case PWM_TASK_PWM2_DISABLE:
        break;

    default:
        break;
    }
    return 1;
}
#endif

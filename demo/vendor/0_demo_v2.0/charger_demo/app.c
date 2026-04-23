/********************************************************************************************************
 * @file    app.c
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
#include "inc/drv_uart.h"
#include "modules/drv_gpio.h"
#include "inc/drv_pmu.h"
#include "inc/drv_cpr.h"
#include "common.h"
#include "hal/hal_systimer.h"
#include "hal/hal_charger.h"

#define CHARGE_STATE_TEST_EN                       1

#define CHARGE_STATE_USE_ISR                       1


#ifndef CHARGE_STATE_TEST_EN
#define CHARGE_STATE_TEST_EN                         0
#endif

volatile int detect_loop=0;
unsigned int debounce_flag = 0;
unsigned int debounce_timer_start = 0;

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


/**
 * Note: There are two conditions for triggering Charger interrupt: Vbus insertion and Charging enabled.
 * (Removing the Vbus does NOT trigger an interrupt.)
 */
void CHG_START_IRQHandler(void)
{
    uint32_t reg_charger = READ_REG(PMU->CHARGER);

    debounce_flag++;
    if(debounce_flag == 1)
    {
        debounce_timer_start = stimer_get_tick();
    }

    if (!clock_time_exceed(debounce_timer_start, 200000)) {//debounce time: 200ms
        return;
    }
    debounce_timer_start = stimer_get_tick();
    debounce_flag = 0;
    if (reg_charger & PMU_CHG_DET) {
            soc_printf("\n################detect_loop = %d #######################\n",detect_loop++);
            soc_printf("charger in box\n");
        }
    WRITE_REG(PMU->PB_WKUP_IRQ, PMU_CHG_DET_WKUP_IRQ);

    if (reg_charger & PMU_CHG_STAT) {
        soc_printf("charging\n");
    }
     WRITE_REG(PMU->PB_WKUP_IRQ, PMU_CHG_STAT_WKUP_IRQ);

    if (reg_charger & PMU_CHG_PLUG_FLAG) {
        soc_printf("plug or V > 4.2V\n");
    }

}
PLIC_ISR_REGISTER(CHG_START_IRQHandler, CHG_START_IRQn)

void charge_isr_test(void)
{
#if CHARGE_STATE_USE_ISR
    SET_BIT(PMU->PB_WKUP_CFG0, PMU_CHG_DET_WKUP_EN);
    SET_BIT(PMU->PB_WKUP_CFG0, PMU_CHG_STAT_WKUP_EN);
    drv_hw_int_enable(CHG_START_IRQn);
#else
    uint32_t val = 0;
    uint32_t lst_val = 0;

    CLEAR_BIT(PMU->PB_WKUP_CFG0, PMU_CHG_DET_WKUP_EN);
    CLEAR_BIT(PMU->PB_WKUP_CFG0, PMU_CHG_STAT_WKUP_EN);
    drv_hw_int_disable(CHG_START_IRQn);
#endif

    SET_PROTECT_BIT(PMU->CLK_EN_M_AO, PMU_CHG_DEB_CLK_EN);

    soc_printf("charge state test\n");

    while (1) {
        delay_ms(100);
#if !CHARGE_STATE_USE_ISR

        val = READ_REG(PMU->CHARGER) & (PMU_CHG_DET | PMU_CHG_STAT | PMU_CHG_PLUG_FLAG);
        if (lst_val != val) {

            if ((val & PMU_CHG_DET) != (lst_val & PMU_CHG_DET)) {
                if (val & PMU_CHG_DET) {
                    soc_printf("charger in box\n");
                } else {
                    soc_printf("charger out box\n");
                }
            }

            if ((val & PMU_CHG_STAT) != (lst_val & PMU_CHG_STAT)) {
                if (val & PMU_CHG_STAT) {
                    soc_printf("charging\n");
                } else {
                    soc_printf("not charging\n");
                }
            }

            if ((val & PMU_CHG_PLUG_FLAG) != (lst_val & PMU_CHG_PLUG_FLAG)) {
                if (val & PMU_CHG_PLUG_FLAG) {
                    soc_printf("plug or V > 4.2V\n");
                } else {
                    soc_printf("pull or V < 4.2V\n");
                }
            }

            lst_val = val;
        }
#endif
    }
}


void user_init(void)
{
#if CHARGE_STATE_USE_ISR
    core_interrupt_enable();
#endif

    log_init();
    soc_printf("charger demo\r\n");

    #if CHARGE_STATE_TEST_EN
    charge_isr_test();
    #endif

}
void main_loop(void){

}

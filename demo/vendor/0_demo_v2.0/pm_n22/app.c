/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "driver.h"

#define PM_PAD_WAKEUP                       0
#define PM_RTC_WAKEUP                       1
#define PM_IPCM_WAKEUP                      0

#if (PM_PAD_WAKEUP)
#define PM_PAD_WAKEUP_MODE_POS_EDGE         0
#define PM_PAD_WAKEUP_MODE_NEG_EDGE         1
#define PM_PAD_WAKEUP_MODE      PM_PAD_WAKEUP_MODE_POS_EDGE

gpio_init_t wakeup_gpio_init =
{
    .port = GPIO_PORT_B,
    .pin  = GPIO_PIN_(4),
    .mode = MODE_INPUT,
#if (PM_PAD_WAKEUP_MODE == PM_PAD_WAKEUP_MODE_POS_EDGE)
    .pull = GPIO_PULLDOWN,
    .intr_type = GPIO_INTR_POSEDGE,
#elif (PM_PAD_WAKEUP_MODE == PM_PAD_WAKEUP_MODE_NEG_EDGE)
    .pull = GPIO_PULLUP,
    .intr_type = GPIO_INTR_NEGEDGE,
#endif

    .alternate = GPIO_ALTERNATE_DEFAULT,
};
#endif

#if (PM_RTC_WAKEUP)
#define PM_RTC_WAKEUP_TIME_MS               (2000)
#define PM_RTC_WAKEUP_TICK                  (32 * PM_RTC_WAKEUP_TIME_MS)
#endif

void ipcm_callback(ipcm_cpu_id_t cpux, uint32_t msg_addr);
ipcm_handle_t hipcm =
{
    .instance = IPCM,
    .cb       = ipcm_callback,
};

uart_handle_t uart_handle;
volatile uint32_t d25_enter_sleep;
volatile uint32_t g_d25_wakeup_tick;
volatile pm_sleep_mode_e g_sleep_mode;

/***********************************IPCM config**********************************/
void ipcm_callback(ipcm_cpu_id_t cpux, uint32_t msg_addr)
{
    if(cpux != IPCM_CPU_0) return;

    pm_sync_msg_t *p_msg = (pm_sync_msg_t *)msg_addr;
    d25_enter_sleep   = 1;
    g_sleep_mode      = (pm_sleep_mode_e)p_msg->sleep_mode;
    g_d25_wakeup_tick = p_msg->wakeup_tick;
}

void IPCM_IRQHandler(void)
{
    drv_ipcm_irqhandler(&hipcm);
}

ISR_REGISTER(IPCM_IRQHandler, IPCM_IRQn)


#if (PM_RTC_WAKEUP)
/***********************************RTC config**********************************/
void RTC_IRQHandler(void)
{
    READ_REG(RTC->EOI);
}

ISR_REGISTER(RTC_IRQHandler, RTC_IRQn)
#endif

#if (PM_PAD_WAKEUP)
/***********************************GPIO config**********************************/
void GPIO_IRQHandler(void)
{
    uint32_t irq_pin;

    irq_pin = drv_gpio_irq_read(GPIO_PORT_B);
    if (irq_pin) {
        drv_gpio_irq_clear(GPIO_PORT_B, irq_pin);
    }

    irq_pin = drv_gpio_irq_read(GPIO_PORT_A);
    if (irq_pin) {
        drv_gpio_irq_clear(GPIO_PORT_A, irq_pin);
    }
}

ISR_REGISTER(GPIO_IRQHandler, GPIO_IRQn)
#endif

/***********************************UART log config**********************************/
void log_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_GPIO_CLK_ENABLE();
    SET_PROTECT_BIT(PMU->CLK_EN_M_AO, PMU_GPIO_DEB_CLK_EN_MSK);

    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    __DRV_CPR_UART0_CLK_ENABLE();
    uart_handle.instance = UART0;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}
void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
    drv_uart_transmitter_empty_waiting(&uart_handle, 0xffff);
}

void app_ipcm_init(void)
{
    drv_ipcm_deinit(&hipcm);
    drv_ipcm_init(&hipcm);
    drv_hw_int_enable(IPCM_IRQn);
}

void user_init(void)
{
    log_init();

    app_ipcm_init();

     soc_printf("pm n22 demo\r\n");

    DEBUG_DOT();

    clic_init();

    DEBUG_DOT();

    core_interrupt_enable();

    DEBUG_DOT();
}

void main_loop(void)
{

#if (PM_PAD_WAKEUP)
    DEBUG_DOT();

    drv_hw_int_enable(GPIO_IRQn);
#endif

#if (PM_RTC_WAKEUP)
    DEBUG_DOT();

    drv_hw_int_enable(RTC_IRQn);
#endif

    DEBUG_DOT();

    while(d25_enter_sleep == 0);
    d25_enter_sleep = 0;

    soc_printf("N22 sleep, mode %d\r\n", g_sleep_mode);

    DEBUG_DOT();

    /* sleep times cnt */
    PMU->GP_REG2 = PMU->GP_REG2 + 1;

    pm_sleep_wakeup_n22(g_sleep_mode);

    DEBUG_DOT();

/* don't release at 20260415 */
#if 0
    if(g_sleep_mode == RET_MODE)
    {
        app_ipcm_init();
        log_init();
    }
#endif

    DEBUG_DOT();

    soc_printf("N22 wakeup\r\n");

    DEBUG_DOT();
}



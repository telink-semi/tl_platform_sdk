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

#define PM_TICK_TYPE_STIMER                 0
#define PM_TICK_TYPE_RTC                    1
#define PM_TICK_TYPE                        PM_TICK_TYPE_RTC

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
#if (PM_IPCM_WAKEUP)
    .cb       = ipcm_callback,
#endif
};


uart_handle_t uart_handle;

pm_sync_msg_t pm_msg;

volatile uint32_t n22_sleep_time;
volatile uint32_t g_wakeup_src;
volatile uint32_t g_n22_wakeup_tick;
volatile pm_sleep_mode_e g_sleep_mode = DEEPSLEEP_MODE;

extern volatile unsigned int g_version;

#if (PM_IPCM_WAKEUP)
/***********************************IPCM config**********************************/
void ipcm_callback(ipcm_cpu_id_t cpux, uint32_t msg_addr)
{
    if(cpux != IPCM_CPU_1) return;

    pm_sync_msg_t *p_msg = (pm_sync_msg_t *)msg_addr;
    g_n22_wakeup_tick = p_msg->wakeup_tick;
}

void IPCM_IRQHandler(void)
{
    drv_ipcm_irqhandler(&hipcm);
}

ISR_REGISTER(IPCM_IRQHandler, IPCM_IRQn)
#endif

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

    DEBUG_DOT();

    __DRV_CPR_GPIO_CLK_ENABLE();
    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    DEBUG_DOT();

    memset(&uart_handle, 0, sizeof(uart_handle_t));

    DEBUG_DOT();

    __DRV_CPR_UART1_CLK_ENABLE();
    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;

    DEBUG_DOT();

    drv_uart_init(&uart_handle);

    DEBUG_DOT();
}

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
    drv_uart_transmitter_empty_waiting(&uart_handle, 0xffff);
}


void app_gpio_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_GPIO_CLK_ENABLE();

    gpio_init.port = GPIO_PORT_B;
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.mode = MODE_INPUT;
    gpio_init.pull = GPIO_PULLDOWN;
    gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
    gpio_init.intr_type = GPIO_INTR_DISABLE;
    drv_gpio_init(&gpio_init);
}

void user_init(void)
{
    log_init();

    boot_cpu1(0x100000, 512 * 1024);

    delay_ms(100);

    soc_printf("pm d25f demo, chip_version: 0x%x\r\n", g_version);
    soc_printf("g_pm_status_info.mcu_status: %d\r\n", g_pm_status_info.mcu_status);

    core_interrupt_enable();

//    app_gpio_init();

    DEBUG_DOT();
}

void main_loop(void)
{
    DEBUG_DOT();

#if (PM_PAD_WAKEUP)
    g_wakeup_src |= (PM_CPU0_WKUP_SRC_GPIO | PM_CPU1_WKUP_AON_GPIO);
    pm_wakeup_gpio_init(&wakeup_gpio_init);
    drv_hw_int_enable(GPIO_IRQn);

    DEBUG_DOT();
#endif

#if (PM_RTC_WAKEUP)
    /* RTC was configured in N22 */
    g_wakeup_src |= (PM_CPU0_WKUP_SRC_RTC | PM_CPU1_WKUP_RTC);
    drv_hw_int_enable(RTC_IRQn);

    DEBUG_DOT();
#endif

#if (PM_IPCM_WAKEUP)
    pm_set_wakeup_src_d25f_cpr(PM_CPU0_CPR_WKUP_SRC_IPCM);
    g_wakeup_src |= PM_CPU0_WKUP_SRC_CPR;

    /* add ipcm init here */

    drv_hw_int_enable(IPCM_IRQn);

    DEBUG_DOT();
#endif

    soc_printf("D25F sleep, mode %d\r\n", g_sleep_mode);
    pm_msg.sleep_mode  = (unsigned char)g_sleep_mode;
    pm_msg.wakeup_tick = 0;
    /* notify N22 start sleep */
    if(g_sleep_mode <= SUSPEND_MODE)
    {
        soc_printf("ipcm send to N22\r\n");
        drv_ipcm_send_msg(&hipcm, IPCM_CPU_1, (MCUA_SYS_BUS_BASE + (uint32_t)&pm_msg));
    }

    DEBUG_DOT();

#if (PM_RTC_WAKEUP)
    #if (PM_TICK_TYPE == PM_TICK_TYPE_STIMER)
        pm_sleep_wakeup(g_sleep_mode, g_wakeup_src, PM_TICK_STIMER, stimer_get_tick() + 2000 * SYSTEM_TIMER_TICK_1MS);
    #elif (PM_TICK_TYPE == PM_TICK_TYPE_RTC)
        pm_sleep_wakeup(g_sleep_mode, g_wakeup_src, PM_TICK_32K, 2 * CLOCK_32K_TIMER_TICK_1S);
    #endif
#else
    pm_sleep_wakeup(g_sleep_mode, g_wakeup_src, PM_TICK_32K, 0);
#endif

    DEBUG_DOT();

/* don't release at 20260415 */
#if 0
    if(g_sleep_mode == RET_MODE)
    {
        log_init();
    }
#endif

    DEBUG_DOT();

    soc_printf("D25F wakeup\r\n");

    DEBUG_DOT();

//    g_sleep_mode--;

    DEBUG_DOT();

    delay_ms(1000);

    DEBUG_DOT();
}


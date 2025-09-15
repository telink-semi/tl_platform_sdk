/********************************************************************************************************
 * @file    app.c
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
#include "common.h"
#include "compiler.h"

#if ((!PM_SET_DVDD_MODE) && (CORE_MODE == CORE_SINGLE))

unsigned char dat[5] = {0};
unsigned char result = 0;

_attribute_data_retention_sec_ volatile unsigned int retention_data_test  = 0;
volatile unsigned long                               pm_cal_24mrc_counter = 0;

#if (defined(MCU_CORE_B92))&&(PM_MODE & CTB_WAKEUP)
// For internal testing only, this function is not available externally
void ctb_lpc_init(void)
{
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_PB0); //Select the reference voltage of CTB as the reference voltage of LPC.
    lpc_set_input_chn(LPC_INPUT_PB7);             //Select the output voltage of CTB as the input of LPC.
    lpc_set_scaling_coeff(LPC_SCALING_PER100);
    lpc_power_on();
    delay_us(100);
    lpc_set_diff_mode();
}
#endif

/**
 * @brief      This function servers to enable gpio function.
 * @param[in]  pin - the selected pin.
 * @param[in]  io_high_low_level - set the pin's output high/low level. (1: high,0: low)
 * @return     none
 */
void led_init(gpio_pin_e pin, bool io_high_low_level)
{
    gpio_function_en(pin);
    gpio_output_en(pin);
    gpio_input_dis(pin);

    if (io_high_low_level)
    {
        gpio_set_high_level(pin);
    }
    else
    {
        gpio_set_low_level(pin);
    }
}

void user_init(void)
{
    delay_ms(2000);

    #if CURRENT_TEST
    gpio_shutdown(GPIO_ALL);

    #else
    // init the LED pin, for indication
    led_init(LED1, 1);
    led_init(LED2, 1);
    delay_ms(1000);

    #if (defined(MCU_CORE_B91))&&(PM_MODE & MDEC_WAKEUP)
    led_init(LED3, 0);
    if (((pm_get_wakeup_src()) & PM_WAKEUP_MDEC) && (CRC_OK == mdec_read_dat(dat)))
    {
        gpio_set_high_level(LED3);
    }
    delay_ms(2000);
    #endif

    #if (PM_MODE & COMPARATOR_WAKEUP)
    led_init(LED4, 0);
    result = lpc_get_result();
    if (result)
    {
        gpio_set_high_level(LED4);
    }
    else
    {
        gpio_set_low_level(LED4);
    }
    delay_ms(2000);
    #endif

    #endif

    //24M RC is inaccurate, and it is greatly affected by temperature, so real-time calibration is required
    //The 24M RC needs to be calibrated before the pm_sleep_wakeup function,
    //because this clock will be used to kick 24m xtal start after wake up,
    //The more accurate this time, the faster the crystal will start.Calibration cycle depends on usage
    if (g_pm_status_info.mcu_status == MCU_DEEPRET_BACK)
    {
        if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000))
        {
            clock_cal_24m_rc();
            pm_cal_24mrc_counter = stimer_get_tick();
        }
    }
    else
    {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();
    
        if (PM_CLOCK_SELECT == PM_CLK_32K_RC)
        {
            clock_32k_init(CLK_32K_RC);
            clock_cal_32k_rc(); //6.68ms
        }
        else if (PM_CLOCK_SELECT == PM_CLK_32K_XTAL)
        {
            clock_32k_init(CLK_32K_XTAL);
            clock_kick_32k_xtal(10);
        }
    }

    #if (PM_MODE & PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    #endif

    #if (defined(MCU_CORE_B91))&&(PM_MODE & MDEC_WAKEUP)
    mdec_init(FLD_SELE_PE0);
    mdec_reset();
    pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
    #endif

    #if (PM_MODE & COMPARATOR_WAKEUP)
    lpc_set_input_chn(LPC_WAKEUP_PAD);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    #endif

    #if (PM_MODE & CORE_USB_WAKEUP)
    #if (defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X))
    usbhw_init();
    #endif
    usb_set_pin(1);
    reg_wakeup_en |= 0x01;
    gpio_set_up_down_res(GPIO_PA5, GPIO_PIN_PULLDOWN_100K);
    gpio_set_up_down_res(GPIO_PA6, GPIO_PIN_PULLUP_10K);
    pm_set_suspend_power_cfg(FLD_PD_USB_EN, 1);
    #endif

    #if (PM_MODE & CORE_GPIO_WAKEUP)
    gpio_input_en(WAKEUP_CORE_PAD);
    gpio_irq_en(WAKEUP_CORE_PAD, GPIO_IRQ0);
    reg_gpio_irq_ctrl |= FLD_GPIO_CORE_WAKEUP_EN;
    reg_wakeup_en |= 0x02;
    pm_set_gpio_wakeup(WAKEUP_CORE_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_CORE_PAD, GPIO_PIN_PULLDOWN_100K);
    #endif

    // CTB mode : For internal testing only, this function is not available externally
    #if (defined(MCU_CORE_B92)&&(PM_MODE & CTB_WAKEUP))
    ctb_init();
    ctb_lpc_init();
    #endif
}

void main_loop(void)
{
    if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000))
    {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();
    }

    delay_ms(500);

    #if !CURRENT_TEST
    gpio_set_low_level(LED2);
    #endif

    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    // CTB mode : For internal testing only, this function is not available externally
    retention_data_test ++;
    #if (PM_WAKEUP_TICK_TYPE == PM_WAKEUP_SLEEP_TYPE)
        pm_sleep_wakeup(PM_SLEEP_MODE, PM_SLEEP_WAKEUP_SRC, PM_TICK_STIMER, stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS);
    #elif (PM_WAKEUP_TICK_TYPE == PM_WAKEUP_LONG_SLEEP_TYPE)
    #if (PM_CLOCK_SELECT == PM_CLK_32K_RC)
        pm_sleep_wakeup(PM_SLEEP_MODE, PM_SLEEP_WAKEUP_SRC, PM_TICK_32K, 2 * CLOCK_32K_TIMER_TICK_1S);
    #else
        pm_sleep_wakeup(PM_SLEEP_MODE, PM_SLEEP_WAKEUP_SRC, PM_TICK_32K, 2 * CLOCK_32K_XTAL_TIMER_TICK_1S);
    #endif
    #endif

    #if (defined(MCU_CORE_B91))&&(PM_MODE & MDEC_WAKEUP)
    if ((CRC_OK == mdec_read_dat(dat)))
    {
        gpio_toggle(LED3);
    }
    mdec_reset();
    #endif

    #if (PM_MODE & COMPARATOR_WAKEUP)
    if (1 == lpc_get_result())
    {
        gpio_toggle(LED4);
    }
    #endif

    #if !CURRENT_TEST
    gpio_set_high_level(LED2);
    #endif
}
#endif

/********************************************************************************************************
 * @file    app_multi_core.c
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
#include "compiler.h"

#if ((!PM_SET_DVDD_MODE) && (CORE_MODE == CORE_MULTI))

unsigned char dat[5] = {0};
unsigned char result = 0;

_attribute_data_retention_sec_ volatile unsigned int retention_data_test  = 0;
volatile unsigned long                               pm_cal_24mrc_counter = 0;

#if (DSP_TEST)
unsigned int           val_d25f_to_dsp_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_dsp_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_dsp_to_d25_irq_flag = 0;
volatile unsigned char mailbox_dsp_to_d25_cnt      = 0;
#endif

#if (N22_TEST)
unsigned int           val_d25f_to_n22_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_n22_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_n22_to_d25_irq_flag = 0;
volatile unsigned char mailbox_n22_to_d25_cnt      = 0;
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

    #if (!CURRENT_TEST)
    // init the LED pin, for indication
    led_init(LED1, 1);
    delay_ms(1000);

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

    #if (DSP_TEST)
    sys_dsp_init(DSP_FW_DOWNLOAD_FLASH_ADDR);
    sys_dsp_start();
    mailbox_set_irq_mask(FLD_MAILBOX_DSP_TO_D25F_IRQ);
    plic_interrupt_enable(IRQ_MAILBOX_DSP_TO_D25);
    core_interrupt_enable();
    #endif

    #if (N22_TEST)
    sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
    sys_n22_start();
    #if defined(MCU_CORE_TL751X)
    mailbox_set_irq_mask(FLD_MAILBOX_N22_TO_D25F_IRQ);
    #else
    mailbox_set_irq_mask_d25f();
    #endif
    plic_interrupt_enable(IRQ_MAILBOX_N22_TO_D25);
    core_interrupt_enable();
    #endif

    #else
    #if (DSP_TEST)
    pm_set_dig_module_power_switch(FLD_PD_DSP_EN, PM_POWER_UP);
    #endif

    #if (N22_TEST)
    pm_set_dig_module_power_switch(FLD_PD_ZB_EN, PM_POWER_UP);
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
        #if !defined(MCU_CORE_TL322X)
        else if (PM_CLOCK_SELECT == PM_CLK_32K_XTAL)
        {
            clock_32k_init(CLK_32K_XTAL);
            clock_kick_32k_xtal(10);
        } //32k xtal not support now
        #endif
    }

    #if (PM_MODE & PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    #endif

    #if (PM_MODE & COMPARATOR_WAKEUP)
    lpc_set_input_chn(LPC_WAKEUP_PAD);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    #endif

    #if (PM_MODE & CORE_USB_WAKEUP)
    #if defined(MCU_CORE_TL322X)
    usb1hw_init();
    usb1_set_pin();
    pm_set_usb_wakeup();
    gpio_set_up_down_res(GPIO_PA5, GPIO_PIN_PULLDOWN_100K);//DM
    gpio_set_up_down_res(GPIO_PA6, GPIO_PIN_PULLUP_10K);//DP
    pm_set_suspend_power_cfg(FLD_PD_USB_EN, 1);
    #elif defined(MCU_CORE_TL751X)
    usbhw_init();
    usb_set_pin(1);
    pm_set_usb_wakeup();
    gpio_set_up_down_res(GPIO_PF2, GPIO_PIN_PULLDOWN_100K);//DM
    gpio_set_up_down_res(GPIO_PF3, GPIO_PIN_PULLUP_10K);//DP
    pm_set_suspend_power_cfg(FLD_PD_USB_EN, 1);
    #endif
    #endif

    #if (PM_MODE & CORE_GPIO_WAKEUP)
    gpio_input_en(WAKEUP_CORE_PAD);
    gpio_irq_en(WAKEUP_CORE_PAD, GPIO_IRQ0);
    reg_gpio_irq_ctrl |= FLD_GPIO_CORE_WAKEUP_EN;
    reg_wakeup_en |= 0x02;
    pm_set_gpio_wakeup(WAKEUP_CORE_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_CORE_PAD, GPIO_PIN_PULLDOWN_100K);
    #endif

    #if (defined(MCU_CORE_TL751X) && (PM_MODE & WT_WAKEUP))
    wt_init();
    pm_set_suspend_power_cfg(FLD_PD_WT_EN, 1);
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
    gpio_set_low_level(LED1);
    #endif

    #if (DSP_TEST)
    val_d25f_to_dsp_word[0] = 0x01234567;
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    while (mailbox_dsp_to_d25_irq_flag == 0)
    {
        delay_us(1);
    }
    mailbox_dsp_to_d25_irq_flag = 0;
    #endif

    #if (N22_TEST)
    val_d25f_to_n22_word[0] = 0x01234567;
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    while (mailbox_n22_to_d25_irq_flag == 0)
    {
        delay_us(1);
    }
    mailbox_n22_to_d25_irq_flag = 0;
    #endif

    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
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

    #if (PM_MODE & COMPARATOR_WAKEUP)
    if (1 == lpc_get_result())
    {
        gpio_toggle(LED4);
    }
    #endif

    #if (DSP_TEST)
    if (pm_get_suspend_power_cfg() & FLD_PD_DSP_EN)
    {
        sys_dsp_init(DSP_FW_DOWNLOAD_FLASH_ADDR);
        sys_dsp_start();
    }
    else
    {
        val_d25f_to_dsp_word[0] = 0x11111111;
        mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    }
    #endif

    #if (N22_TEST)
    if (pm_get_suspend_power_cfg() & FLD_PD_ZB_EN)
    {
        sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
        sys_n22_start();
    }
    else
    {
        val_d25f_to_n22_word[0] = 0x11111111;
        mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    }
    #endif

    #if !CURRENT_TEST
    gpio_set_high_level(LED1);
    #endif
}

#if (DSP_TEST)
_attribute_ram_code_sec_noinline_ void mailbox_dsp_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_DSP_TO_D25F_IRQ)
    {
        mailbox_clr_irq_status(FLD_MAILBOX_DSP_TO_D25F_IRQ);
        mailbox_d25f_get_dsp_msg(val_dsp_to_d25f_word);
        mailbox_dsp_to_d25_irq_flag = 1;
        mailbox_dsp_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_dsp_to_d25_irq_handler, IRQ_MAILBOX_DSP_TO_D25)
#endif

#if defined(MCU_CORE_TL751X)
#if (N22_TEST)
_attribute_ram_code_sec_noinline_ void mailbox_n22_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_N22_TO_D25F_IRQ)
    {
        mailbox_clr_irq_status(FLD_MAILBOX_N22_TO_D25F_IRQ);
        mailbox_d25f_get_n22_msg(val_n22_to_d25f_word);
        mailbox_n22_to_d25_irq_flag = 1;
        mailbox_n22_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_n22_to_d25_irq_handler, IRQ_MAILBOX_N22_TO_D25)
#endif


#else
#if (N22_TEST)
_attribute_ram_code_sec_noinline_ void mailbox_n22_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status_d25f())
    {
        mailbox_clr_irq_status_d25f();
        mailbox_d25f_get_n22_msg(val_n22_to_d25f_word);
        mailbox_n22_to_d25_irq_flag = 1;
        mailbox_n22_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_n22_to_d25_irq_handler, IRQ_MAILBOX_N22_TO_D25)
#endif
#endif

#endif

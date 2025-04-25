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

#if (CORE_MODE == CORE_MULTI)

unsigned char dat[5] = {0};
unsigned char result = 0;

_attribute_data_retention_sec_ volatile unsigned int retention_data_test  = 0;
volatile unsigned long                               pm_cal_24mrc_counter = 0;

unsigned int           val_d25f_to_dsp_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_dsp_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_dsp_to_d25_irq_flag = 0;
volatile unsigned char mailbox_dsp_to_d25_cnt      = 0;

unsigned int           val_d25f_to_n22_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_n22_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_n22_to_d25_irq_flag = 0;
volatile unsigned char mailbox_n22_to_d25_cnt      = 0;

void user_init(void)
{
    delay_ms(1000);


    #if (defined(MCU_CORE_TL751X) && (PM_MODE == PM_SET_DVDD_MODE))
    //Upward Voltage
    pm_set_dvdd(LDO_DVDD1_DVDD2_VOL_0P9V, DMA8, D25F, 1000);
    PLL_300M_D25F_DSP_300M_HCLK_150M_PCLK_150M_MSPI_60M_WT_10M;

    //Downward Voltage
    PLL_264M_D25F_DSP_132M_HCLK_66M_PCLK_66M_MSPI_44M_WT_11M;
    pm_set_dvdd(LDO_DVDD1_DVDD2_VOL_0P8V, DMA8, D25F, 1000);

    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
#endif

    //24M RC is inaccurate, and it is greatly affected by temperature, so real-time calibration is required
    //The 24M RC needs to be calibrated before the pm_sleep_wakeup function,
    //because this clock will be used to kick 24m xtal start after wake up,
    //The more accurate this time, the faster the crystal will start.Calibration cycle depends on usage
    if (g_pm_status_info.mcu_status == MCU_STATUS_DEEPRET_BACK) {
        if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000)) {
            clock_cal_24m_rc();
            pm_cal_24mrc_counter = stimer_get_tick();
        }
    } else {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();

        //If it is timer or mdec wake up, you need to initialize 32K
    #if defined(MCU_CORE_TL751X)
        if (PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET128K_32K_RC_WAKEUP || PM_MODE == DEEP_RET256K_32K_RC_WAKEUP || PM_MODE == DEEP_RET384K_32K_RC_WAKEUP) {
            clock_32k_init(CLK_32K_RC);
            clock_cal_32k_rc(); //6.68ms
        }
    #endif
    }

    //32k xtal not support now
//    #if defined(MCU_CORE_TL751X)
//    if (PM_MODE == SUSPEND_32K_XTAL_WAKEUP || PM_MODE == DEEP_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET128K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET256K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET384K_32K_XTAL_WAKEUP) {
//        clock_32k_init(CLK_32K_XTAL);
//        clock_kick_32k_xtal(10);
//    }
//    #endif

    #if !CURRENT_TEST
    // init the LED pin, for indication
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_set_high_level(LED1);
    delay_ms(1000);

    #if (defined(MCU_CORE_TL751X) && ((PM_MODE == SUSPEND_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET128K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET256K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET384K_COMPARATOR_WAKEUP)))
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);
    result = lpc_get_result();
    if (result) {
        gpio_set_high_level(LED3);
    } else {
        gpio_set_low_level(LED3);
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
    mailbox_set_irq_mask(FLD_MAILBOX_N22_TO_D25F_IRQ);
    plic_interrupt_enable(IRQ_MAILBOX_N22_TO_D25);
    core_interrupt_enable();
    #endif

    delay_ms(1000);

    #if (DSP_TEST)
    val_d25f_to_dsp_word[0] = 0x01234567;
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    while (mailbox_dsp_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_dsp_to_d25_irq_flag = 0;
    #endif

    #if (N22_TEST)
    val_d25f_to_n22_word[0] = 0x01234567;
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    while (mailbox_n22_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_n22_to_d25_irq_flag = 0;
    #endif

    #else

    #if (DSP_TEST)
    pm_set_dig_module_power_switch(FLD_PD_DSP_EN, PM_POWER_UP);
    #endif

    #if (N22_TEST)
    pm_set_dig_module_power_switch(FLD_PD_ZB_EN, PM_POWER_UP);
    #endif

    #endif

    #if (PM_MODE == SUSPEND_PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    g_pm_sleep_mode.sleep_mode = SUSPEND_SLEEP_MODE;

    #elif (PM_MODE == DEEP_PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    g_pm_sleep_mode.sleep_mode = DEEP_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET128K_PAD_WAKEUP)
    retention_data_test++;
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW128K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET256K_PAD_WAKEUP)
    retention_data_test++;
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW256K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET384K_PAD_WAKEUP)
    retention_data_test++;
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW384K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (PM_MODE == DEEP_32K_RC_WAKEUP)
    g_pm_sleep_mode.sleep_mode = DEEP_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET128K_32K_RC_WAKEUP)
    retention_data_test++;
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW128K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET256K_32K_RC_WAKEUP)
    retention_data_test++;
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW256K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET384K_32K_RC_WAKEUP)
    retention_data_test++;
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW384K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == SUSPEND_COMPARATOR_WAKEUP)
    lpc_set_input_chn(LPC_INPUT_PG1);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_COMPARATOR_WAKEUP)
    lpc_set_input_chn(LPC_INPUT_PG1);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    g_pm_sleep_mode.sleep_mode = DEEP_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET128K_COMPARATOR_WAKEUP)
    retention_data_test++;
    lpc_set_input_chn(LPC_INPUT_PG1);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW128K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET256K_COMPARATOR_WAKEUP)
    retention_data_test++;
    lpc_set_input_chn(LPC_INPUT_PG1);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW256K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X)) && (PM_MODE == DEEP_RET384K_COMPARATOR_WAKEUP)
    retention_data_test++;
    lpc_set_input_chn(LPC_INPUT_PG1);
    lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
    lpc_set_scaling_coeff(LPC_SCALING_PER75);
    lpc_power_on();
    delay_us(64);
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    g_pm_sleep_mode.sleep_mode    = RET_SLEEP_MODE;
    g_pm_sleep_mode.d25f_ret_mode = D25F_RET_MODE_SRAM_LOW384K;
    g_pm_sleep_mode.n22_ret_mode  = N22_RET_MODE_SRAM_NONE;
    g_pm_sleep_mode.dsp_ret_mode  = DSP_RET_MODE_SRAM_NONE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL751X) && (PM_MODE == SUSPEND_CORE_USB_WAKEUP))
    usbhw_init();
    usb_set_pin(1);
    pm_set_usb_wakeup();
    gpio_set_up_down_res(GPIO_PF2, GPIO_PIN_PULLDOWN_100K);//DM
    gpio_set_up_down_res(GPIO_PF3, GPIO_PIN_PULLUP_10K);//DP
    pm_set_suspend_power_cfg(FLD_PD_USB_EN, 1);

    #endif
}

void main_loop(void)
{
    if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000)) {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();
    }

    #if !CURRENT_TEST
    gpio_set_low_level(LED1);
    delay_ms(500);
    #endif

    #if (PM_MODE == SUSPEND_PAD_WAKEUP)
    pm_set_dig_module_power_switch(FLD_PD_ZB_EN | FLD_PD_USB_EN | FLD_PD_AUDIO_EN | FLD_PD_DSP_EN | FLD_PD_WT_EN, PM_POWER_UP);
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (PM_MODE == SUSPEND_32K_RC_WAKEUP)
    g_pm_sleep_mode.sleep_mode = SUSPEND_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_TIMER, PM_TICK_STIMER, stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS);

    #elif (defined(MCU_CORE_TL751X) && (PM_MODE == SUSPEND_COMPARATOR_WAKEUP))
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    g_pm_sleep_mode.sleep_mode = SUSPEND_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);
    if (1 == lpc_get_result()) {
        gpio_toggle(LED3);
    }

    //#elif(PM_MODE == SUSPEND_CORE_USB_WAKEUP || PM_MODE == SUSPEND_CORE_GPIO_WAKEUP)
    #elif (defined(MCU_CORE_TL751X) && (PM_MODE == SUSPEND_CORE_USB_WAKEUP))
    g_pm_sleep_mode.sleep_mode = SUSPEND_SLEEP_MODE;
    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_CORE, PM_TICK_STIMER, 0);

    // CTB mode : For internal testing only, this function is not available externally
//    #elif (defined(MCU_CORE_TL751X) && (PM_MODE == SUSPEND_CTB_WAKEUP))
//    g_pm_sleep_mode.sleep_mode = SUSPEND_SLEEP_MODE;
//    pm_sleep_wakeup(g_pm_sleep_mode, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #endif

    #if (DSP_TEST)
    if (pm_get_suspend_power_cfg() & FLD_PD_DSP_EN) {
        sys_dsp_init(DSP_FW_DOWNLOAD_FLASH_ADDR);
        sys_dsp_start();
    } else {
        val_d25f_to_dsp_word[0] = 0x11111111;
        mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    }
    #endif

    #if (N22_TEST)
    if (pm_get_suspend_power_cfg() & FLD_PD_ZB_EN) {
        sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
        sys_n22_start();
    } else {
        val_d25f_to_n22_word[0] = 0x11111111;
        mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    }
    #endif

    #if !CURRENT_TEST
    gpio_set_high_level(LED1);
    #endif

    delay_ms(500);

    #if (PM_MODE == PM_SET_DVDD_MODE)
    gpio_toggle(LED1);
    #endif

    #if (DSP_TEST)
    val_d25f_to_dsp_word[0] = 0x01234567;
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    while (mailbox_dsp_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_dsp_to_d25_irq_flag = 0;
    #endif

    #if (N22_TEST)
    val_d25f_to_n22_word[0] = 0x01234567;
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    while (mailbox_n22_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_n22_to_d25_irq_flag = 0;
    #endif
}

_attribute_ram_code_sec_noinline_ void mailbox_dsp_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_DSP_TO_D25F_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_DSP_TO_D25F_IRQ);
        mailbox_d25f_get_dsp_msg(val_dsp_to_d25f_word);
        mailbox_dsp_to_d25_irq_flag = 1;
        mailbox_dsp_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_dsp_to_d25_irq_handler, IRQ_MAILBOX_DSP_TO_D25)

_attribute_ram_code_sec_noinline_ void mailbox_n22_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_N22_TO_D25F_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_N22_TO_D25F_IRQ);
        mailbox_d25f_get_n22_msg(val_n22_to_d25f_word);
        mailbox_n22_to_d25_irq_flag = 1;
        mailbox_n22_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_n22_to_d25_irq_handler, IRQ_MAILBOX_N22_TO_D25)

#endif

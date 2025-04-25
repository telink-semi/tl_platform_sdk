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
#include "app_config.h"
#include "compiler.h"

#if (CORE_MODE == CORE_SINGLE)

unsigned char dat[5] = {0};
unsigned char result = 0;

_attribute_data_retention_sec_ volatile unsigned int retention_data_test  = 0;
volatile unsigned long                               pm_cal_24mrc_counter = 0;

    #if defined(MCU_CORE_B92)
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

void user_init(void)
{
    delay_ms(2000);

    #if (defined(MCU_CORE_TL7518) && (PM_MODE == PM_SET_DVDD_MODE))
    //Upward Voltage
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P9_CONFG, DMA8, D25F, 1000);
    CCLK_192M_HCLK_192M_PCLK_48M_MSPI_48M;

    //Downward Voltage
    CCLK_96M_HCLK_96M_PCLK_24M_MSPI_48M;
    pm_set_dvdd(DVDD1_DVDD2_VOL_0P8_CONFG, DMA8, D25F, 1000);
    #elif (defined(MCU_CORE_TL721X) && (PM_MODE == PM_SET_DVDD_MODE))
    pm_set_probe_vol_to_pd3(VDD_RAM);

    //Upward Voltage
    pm_set_dvdd(CORE_0P9V_SRAM_0P9V_BB_0P9V, DMA1, 1000);
    PLL_240M_CCLK_240M_HCLK_120M_PCLK_120M_MSPI_48M;

    //Downward Voltage
    PLL_240M_CCLK_120M_HCLK_60M_PCLK_60M_MSPI_48M;
    pm_set_dvdd(CORE_0P8V_SRAM_0P8V_BB_0P8V, DMA1, 1000);
    #endif
    #if CURRENT_TEST
    gpio_shutdown(GPIO_ALL);

    #else
    // init the LED pin, for indication
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_set_high_level(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_set_low_level(LED2);
    delay_ms(1000);
        #if defined(MCU_CORE_B91)
            #if ((PM_MODE == SUSPEND_MDEC_WAKEUP) || (PM_MODE == DEEP_MDEC_WAKEUP) || (PM_MODE == DEEP_RET32K_MDEC_WAKEUP) || (PM_MODE == DEEP_RET64K_MDEC_WAKEUP))
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);
    if (((pm_get_wakeup_src()) & PM_WAKEUP_MDEC) && (CRC_OK == mdec_read_dat(dat))) {
        gpio_set_high_level(LED3);
        delay_ms(2000);
    }
            #endif
        #endif
        #if (defined(MCU_CORE_B91) && ((PM_MODE == SUSPEND_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP)))
    || (defined(MCU_CORE_B92) && ((PM_MODE == SUSPEND_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET96K_COMPARATOR_WAKEUP))) || (defined(MCU_CORE_TL721X) && ((PM_MODE == SUSPEND_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET128K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET256K_COMPARATOR_WAKEUP))) || (defined(MCU_CORE_TL321X) && ((PM_MODE == SUSPEND_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP) || (PM_MODE == DEEP_RET96K_COMPARATOR_WAKEUP))) gpio_function_en(LED3);
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

    #endif

    //24M RC is inaccurate, and it is greatly affected by temperature, so real-time calibration is required
    //The 24M RC needs to be calibrated before the pm_sleep_wakeup function,
    //because this clock will be used to kick 24m xtal start after wake up,
    //The more accurate this time, the faster the crystal will start.Calibration cycle depends on usage
    #if defined(MCU_CORE_B91)
    if (g_pm_status_info.mcu_status == MCU_STATUS_DEEPRET_BACK) {
    #else
    if (g_pm_status_info.mcu_status == MCU_DEEPRET_BACK) {
    #endif
        if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000)) {
            clock_cal_24m_rc();
            pm_cal_24mrc_counter = stimer_get_tick();
        }
    }


    else {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();

        //If it is timer or mdec wake up, you need to initialize 32K
    #if defined(MCU_CORE_B91)
        if (PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_RC_WAKEUP || PM_MODE == SUSPEND_MDEC_WAKEUP || PM_MODE == DEEP_MDEC_WAKEUP || PM_MODE == DEEP_RET32K_MDEC_WAKEUP || PM_MODE == DEEP_RET64K_MDEC_WAKEUP || PM_MODE == SUSPEND_COMPARATOR_WAKEUP || PM_MODE == DEEP_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP) {
            clock_32k_init(CLK_32K_RC);
            clock_cal_32k_rc(); //6.68ms
        } else if (PM_MODE == SUSPEND_32K_XTAL_WAKEUP || PM_MODE == DEEP_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET32K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET64K_32K_XTAL_WAKEUP) {
            clock_32k_init(CLK_32K_XTAL);
            clock_kick_32k_xtal(10);
        }
    #elif defined(MCU_CORE_B92)
        if (PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_RC_WAKEUP || PM_MODE == DEEP_RET96K_32K_RC_WAKEUP || PM_MODE == SUSPEND_COMPARATOR_WAKEUP || PM_MODE == DEEP_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET96K_COMPARATOR_WAKEUP) {
            clock_32k_init(CLK_32K_RC);
            clock_cal_32k_rc(); //6.68ms
        } else if (PM_MODE == SUSPEND_32K_XTAL_WAKEUP || PM_MODE == DEEP_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET32K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET64K_32K_XTAL_WAKEUP || PM_MODE == DEEP_RET96K_32K_XTAL_WAKEUP) {
            clock_32k_init(CLK_32K_XTAL);
            clock_kick_32k_xtal(10);
        }
    #elif defined(MCU_CORE_TL721X)
    if (PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_RC_WAKEUP || PM_MODE == DEEP_RET128K_32K_RC_WAKEUP || PM_MODE == DEEP_RET256K_32K_RC_WAKEUP || PM_MODE == SUSPEND_COMPARATOR_WAKEUP || PM_MODE == DEEP_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET128K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET256K_COMPARATOR_WAKEUP) {
        clock_32k_init(CLK_32K_RC);
        clock_cal_32k_rc(); //6.68ms
    }
    #elif defined(MCU_CORE_TL321X)
    if (PM_MODE == SUSPEND_32K_RC_WAKEUP || PM_MODE == DEEP_32K_RC_WAKEUP || PM_MODE == DEEP_RET32K_32K_RC_WAKEUP || PM_MODE == DEEP_RET64K_32K_RC_WAKEUP || PM_MODE == DEEP_RET96K_32K_RC_WAKEUP || PM_MODE == SUSPEND_COMPARATOR_WAKEUP || PM_MODE == DEEP_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP || PM_MODE == DEEP_RET96K_COMPARATOR_WAKEUP) {
        clock_32k_init(CLK_32K_RC);
        clock_cal_32k_rc(); //6.68ms
    }
    #endif
    }

    #if (PM_MODE == SUSPEND_PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);

    #elif (PM_MODE == DEEP_PAD_WAKEUP) //Caution: if wake-up source is only pad, 32K clock source MUST be 32K RC.
    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
    pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET32K_PAD_WAKEUP)
retention_data_test++;
pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET64K_PAD_WAKEUP)
retention_data_test++;
pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif ((defined(MCU_CORE_B92) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET96K_PAD_WAKEUP))
retention_data_test++;
pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW96K, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET128K_PAD_WAKEUP)
retention_data_test++;
pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW128K, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET256K_PAD_WAKEUP)
retention_data_test++;
pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW256K, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (PM_MODE == DEEP_32K_RC_WAKEUP || ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && PM_MODE == DEEP_32K_XTAL_WAKEUP))
pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && PM_MODE == DEEP_RET32K_32K_RC_WAKEUP) || ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && PM_MODE == DEEP_RET32K_32K_XTAL_WAKEUP)
retention_data_test++;
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && PM_MODE == DEEP_RET64K_32K_RC_WAKEUP) || ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && PM_MODE == DEEP_RET64K_32K_XTAL_WAKEUP)
retention_data_test++;
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif ((defined(MCU_CORE_B92) || defined(MCU_CORE_TL321X)) && PM_MODE == DEEP_RET96K_32K_RC_WAKEUP) || (defined(MCU_CORE_B92) && PM_MODE == DEEP_RET96K_32K_XTAL_WAKEUP)
retention_data_test++;
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW96K, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET128K_32K_RC_WAKEUP)
retention_data_test++;
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW128K, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET256K_32K_RC_WAKEUP)
retention_data_test++;
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW256K, PM_WAKEUP_TIMER, PM_TICK_STIMER, (stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS));

    #elif (defined(MCU_CORE_B91) && (PM_MODE == SUSPEND_MDEC_WAKEUP))
mdec_init(FLD_SELE_PE0);
mdec_reset();
pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);

    #elif (defined(MCU_CORE_B91) && (PM_MODE == DEEP_MDEC_WAKEUP))
mdec_init(FLD_SELE_PE0);
mdec_reset();
pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_MDEC, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) && (PM_MODE == DEEP_RET32K_MDEC_WAKEUP))
retention_data_test++;
mdec_init(FLD_SELE_PE0);
mdec_reset();
pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_MDEC, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) && (PM_MODE == DEEP_RET64K_MDEC_WAKEUP))
retention_data_test++;
mdec_init(FLD_SELE_PE0);
mdec_reset();
pm_set_mdec_value_wakeup(MDEC_MATCH_VALUE);
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_MDEC, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == SUSPEND_COMPARATOR_WAKEUP)
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_COMPARATOR_WAKEUP)
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET32K_COMPARATOR_WAKEUP)
retention_data_test++;
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET64K_COMPARATOR_WAKEUP)
retention_data_test++;
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif ((defined(MCU_CORE_B92) || defined(MCU_CORE_TL321X)) && (PM_MODE == DEEP_RET96K_COMPARATOR_WAKEUP))
retention_data_test++;
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW96K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif ((defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET128K_COMPARATOR_WAKEUP))
retention_data_test++;
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW128K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif ((defined(MCU_CORE_TL721X)) && (PM_MODE == DEEP_RET256K_COMPARATOR_WAKEUP))
retention_data_test++;
lpc_set_input_chn(LPC_INPUT_PB1);
lpc_set_input_ref(LPC_LOWPOWER, LPC_REF_820MV);
lpc_set_scaling_coeff(LPC_SCALING_PER75);
lpc_power_on();
delay_us(64);
//When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
//otherwise can not enter sleep normally, crash occurs.
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW256K, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && (PM_MODE == SUSPEND_CORE_USB_WAKEUP)
usb_set_pin(1);
reg_wakeup_en |= 0x01;
gpio_set_up_down_res(GPIO_PA5, GPIO_PIN_PULLDOWN_100K);
gpio_set_up_down_res(GPIO_PA6, GPIO_PIN_PULLUP_10K);
pm_set_suspend_power_cfg(FLD_PD_USB_EN, 1);

    //#elif(PM_MODE == SUSPEND_CORE_GPIO_WAKEUP)
    //    gpio_input_en(WAKEUP_PAD);
    //    gpio_irq_en(WAKEUP_PAD);
    //    reg_gpio_irq_ctrl |= FLD_GPIO_CORE_WAKEUP_EN;
    //    reg_wakeup_en |= 0x02;
    //    pm_set_gpio_wakeup(WAKEUP_PAD, WAKEUP_LEVEL_HIGH, 1);
    //    gpio_set_up_down_res(WAKEUP_PAD, GPIO_PIN_PULLDOWN_100K);

    // CTB mode : For internal testing only, this function is not available externally
    #elif (defined(MCU_CORE_B92) && (PM_MODE == SUSPEND_CTB_WAKEUP))
ctb_init();
ctb_lpc_init();

    #elif (defined(MCU_CORE_B92) && (PM_MODE == DEEP_CTB_WAKEUP))
ctb_init();
ctb_lpc_init();
pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B92) && (PM_MODE == DEEP_RET32K_CTB_WAKEUP))
retention_data_test++;
ctb_init();
ctb_lpc_init();
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW32K, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B92) && (PM_MODE == DEEP_RET64K_CTB_WAKEUP))
retention_data_test++;
ctb_init();
ctb_lpc_init();
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW64K, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #elif (defined(MCU_CORE_B92) && (PM_MODE == DEEP_RET96K_CTB_WAKEUP))
retention_data_test++;
ctb_init();
ctb_lpc_init();
pm_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW96K, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #endif
}

void main_loop(void)
{
    if (clock_time_exceed(pm_cal_24mrc_counter, 10 * 1000 * 1000)) {
        clock_cal_24m_rc();
        pm_cal_24mrc_counter = stimer_get_tick();
    }

    #if !CURRENT_TEST
    gpio_set_low_level(LED2);
    delay_ms(500);
    #endif

    #if (PM_MODE == SUSPEND_PAD_WAKEUP)
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_PAD, PM_TICK_STIMER, 0);

    #elif (PM_MODE == SUSPEND_32K_RC_WAKEUP) || ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && (PM_MODE == SUSPEND_32K_XTAL_WAKEUP))
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER, stimer_get_tick() + 4000 * SYSTEM_TIMER_TICK_1MS);

    #elif ((defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (PM_MODE == SUSPEND_COMPARATOR_WAKEUP))
    //When entering sleep, keep the input voltage and reference voltage difference must be greater than 30mV,
    //otherwise can not enter sleep normally, crash occurs.
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_COMPARATOR, PM_TICK_STIMER, 0);
    if (1 == lpc_get_result()) {
        gpio_toggle(LED3);
    }

    #elif (defined(MCU_CORE_B91) && (PM_MODE == SUSPEND_MDEC_WAKEUP))
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_MDEC, PM_TICK_STIMER, 0);
    if ((CRC_OK == mdec_read_dat(dat))) {
        gpio_toggle(LED3);
    }
    mdec_reset();

    //#elif(PM_MODE == SUSPEND_CORE_USB_WAKEUP || PM_MODE == SUSPEND_CORE_GPIO_WAKEUP)
    #elif (defined(MCU_CORE_B91) || defined(MCU_CORE_B92)) && (PM_MODE == SUSPEND_CORE_USB_WAKEUP)
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_CORE, PM_TICK_STIMER, 0);

    // CTB mode : For internal testing only, this function is not available externally
    #elif (defined(MCU_CORE_B92) && (PM_MODE == SUSPEND_CTB_WAKEUP))
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_CTB, PM_TICK_STIMER, 0);

    #else
    gpio_set_high_level(LED2);
    #endif

    #if !CURRENT_TEST
    gpio_set_high_level(LED2);
    #endif

    delay_ms(2000);
}
#endif

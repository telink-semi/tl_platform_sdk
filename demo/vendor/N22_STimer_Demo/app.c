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

volatile unsigned int cur_32k_tick[200];
volatile unsigned int cur_32k_tick_step[200];
volatile unsigned int cur_32k_tick_step_err;
volatile unsigned int stimer_track_32k_value;
volatile unsigned int stimer_tick_low3bit;
volatile unsigned int cur_32k_track[200];
volatile unsigned int cur_32k_tick_track_err;


#if defined(MCU_CORE_TL322X)
    #define CAPT_DMA_CNT 200
unsigned int       stimer_capt_dma_buff[CAPT_DMA_CNT] __attribute__((aligned(4)))  = {0};
unsigned int       stimer_capt_dma0_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
unsigned int       stimer_capt_dma1_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
dma_chain_config_t stimer_dma_chain_cfg[2];

    #define PWM_PCLK_SPEED 24000000

enum
{
    CLOCK_PWM_CLOCK_1S  = PWM_PCLK_SPEED,
    CLOCK_PWM_CLOCK_1MS = (CLOCK_PWM_CLOCK_1S / 1000),
    CLOCK_PWM_CLOCK_1US = (CLOCK_PWM_CLOCK_1S / 1000000),
};

void stimer_set_pwm0(void)
{
    //PB0 A20---PWM1
    write_reg8(GPIO_BASE_ADDR + 0x16, 0xfe);
    write_reg8(GPIO_BASE_ADDR + 0xb8, 0x01);

    write_reg8(REG_PWM_BASE + 0x10, 0x10);
    write_reg8(REG_PWM_BASE + 0x11, 0x00);
    write_reg8(REG_PWM_BASE + 0x12, 0x00);

    write_reg16(REG_PWM_BASE + 0x30, 0x0099); //TCMP
    write_reg16(REG_PWM_BASE + 0x32, 0x00ff); //TMAX
    write_reg8(REG_PWM_BASE + 0x34, 0x20);    //PHASE

    write_reg8(REG_PWM_BASE + 0x1c, 0xff);
}
#endif

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

#if defined(MCU_CORE_TL322X)
    gpio_function_en(INPUT_CAPT_PIN);
    gpio_input_en(INPUT_CAPT_PIN);
    gpio_output_dis(INPUT_CAPT_PIN);
#endif

#if (STIMER_MODE == STIMER_IRQ_N22)
    stimer_set_irq_capture_n22(stimer_get_tick() + (500 * SYSTEM_TIMER_TICK_1MS)); //set capture tick
    #if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_n22(FLD_SYSTEM_IRQ_MASK_N22);                              //irq enable
    #else
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_N22); //irq enable
    #endif
    clic_interrupt_vector_en(IRQ_SYSTIMER);
    clic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_IRQ_D25_N22_DSP)
    stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
    stimer_set_irq_capture_n22(stimer_get_tick() + (500 * SYSTEM_TIMER_TICK_1MS));
    #if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_MASK_D25F);                    //irq enable
    stimer_set_irq_mask_n22(FLD_SYSTEM_IRQ_MASK_N22);                      //irq enable
    #else
    stimer_set_irq_capture_dsp(stimer_get_tick() + (200 * SYSTEM_TIMER_TICK_1MS));
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_D25F | FLD_SYSTEM_IRQ_N22 | FLD_SYSTEM_IRQ_DSP); //irq enable
    #endif
    clic_interrupt_vector_en(IRQ_SYSTIMER);
    clic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_GET_32K_TICK)
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc();
#elif (STIMER_MODE == STIMER_SET_32K_TICK)
    clock_set_32k_tick(clock_get_32k_tick() + 32000); //1s
    analog_write_reg8(0x64, 0xff);
    analog_write_reg8(0x4b, 0x04);
    clic_interrupt_vector_en(IRQ_PM_LVL);
    clic_interrupt_enable(IRQ_PM_LVL);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_SET_32K_TICK_LVL)
    clock_set_32k_tick(clock_get_32k_tick() + 32000); //1s
    pm_set_wakeup_src(PM_WAKEUP_TIMER);
    pm_clr_irq_status(WAKEUP_STATUS_ALL);
    clic_interrupt_vector_en(IRQ_PM_LVL);
    clic_interrupt_enable(IRQ_PM_LVL);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_TRACK_32K_TICK)
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc();
    stimer_set_32k_track_cnt(STIMER_TRACK_32KCNT_16);
    stimer_track_32k_value = SYSTEM_TIMER_TICK_1MS / 32 * g_track_32kcnt;
    delay_ms(1000);

#elif (defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE)

    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
    stimer_set_irq_mask_d25f(FLD_SYSTEM_CAPT_IRQ_MASK | FLD_SYSTEM_OVERFLOW_IRQ_MASK);
    clic_interrupt_vector_en(IRQ_SYSTIMER);
    clic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the stimer input capture function.
     * The pwm output waveform passes through gpio, generating the gpio trigger signal, triggering the stimer input capture function.
     */
    stimer_set_pwm0();

#elif (defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA)
    /**
     * It is recommended to enable DMA before enabling capture.
     * Otherwise, the signal may be captured but not read by DMA, which could result in a data overflow.
     */
    stimer_set_input_capt_dma_config(CAPT_DMA_CHN);
    stimer_set_input_capt_value_dma(CAPT_DMA_CHN, stimer_capt_dma_buff, CAPT_DMA_CNT * 4);
    dma_set_irq_mask(CAPT_DMA_CHN, TC_MASK);
    clic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the system timer input capture function.
     */
    stimer_set_pwm0();

#elif (defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA_LLP_MODE)
    /**
     * It is recommended to enable DMA before enabling capture.
     * Otherwise, the signal may be captured but not read by DMA, which could result in a data overflow.
     * Configure interrupt first, then configure DMA, otherwise DMA cannot enter interrupt.
     */
    dma_set_irq_mask(CAPT_DMA_CHN, TC_MASK);
    dma_set_llp_irq_mode(CAPT_DMA_CHN, DMA_INTERRUPT_MODE);
    clic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    stimer_set_input_capt_dma_chain_llp(CAPT_DMA_CHN, stimer_capt_dma0_buff, CAPT_DMA_CNT * 4, &stimer_dma_chain_cfg[0]);
    stimer_input_capt_dma_add_list_element(CAPT_DMA_CHN, stimer_capt_dma1_buff, CAPT_DMA_CNT * 4, &stimer_dma_chain_cfg[0], &stimer_dma_chain_cfg[1]);
    stimer_input_capt_dma_add_list_element(CAPT_DMA_CHN, stimer_capt_dma0_buff, CAPT_DMA_CNT * 4, &stimer_dma_chain_cfg[1], &stimer_dma_chain_cfg[0]);
    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the system timer input capture function.
     */
    stimer_set_pwm0();

#endif
}

void main_loop(void)
{
#if (STIMER_MODE == STIMER_DELAY)
    delay_ms(500);
    gpio_toggle(LED2);

#elif (STIMER_MODE == STIMER_IRQ_D25_N22_DSP)
    delay_ms(20);
    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_D25F))
    #else
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_D25F))
    #endif
    {
        gpio_toggle(LED3);
    #if defined(MCU_CORE_TL322X)
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_D25F);
    #else
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_D25F);
    #endif
        stimer_set_irq_capture_d25f(stimer_get_tick() + (500 * SYSTEM_TIMER_TICK_1MS));
    }
    #if !defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_DSP)) {
        gpio_toggle(LED4);
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_DSP);
        stimer_set_irq_capture_dsp(stimer_get_tick() + (200 * SYSTEM_TIMER_TICK_1MS));
    }
    #endif

#elif (STIMER_MODE == STIMER_GET_32K_TICK)
    cur_32k_tick[0] = clock_get_32k_tick();
    for (int i = 1; i < 200; i++) {
        delay_ms(100);
        cur_32k_tick[i]      = clock_get_32k_tick();
        cur_32k_tick_step[i] = cur_32k_tick[i] - cur_32k_tick[i - 1];
        if ((cur_32k_tick_step[i] < 0xc7f) || (cur_32k_tick_step[i] > 0xc83)) //0xc81,500ppm
        {
            cur_32k_tick_step_err = i;
            gpio_set_high_level(LED2);
            while (1)
                ;
        }
    }

#elif (STIMER_MODE == STIMER_GET_TICK)
    if ((stimer_get_tick() & (0x07)) != 0x00) {
        stimer_tick_low3bit = 1;
        gpio_set_high_level(LED1);
        while (1)
            ;
    }
#elif (STIMER_MODE == STIMER_TRACK_32K_TICK)
    for (int i = 0; i < 200; i++) {
        delay_ms(500);
        cur_32k_track[i] = stimer_get_tracking_32k_value();
        if ((cur_32k_track[i] < (stimer_track_32k_value - 0x06)) || (cur_32k_track[i] > (stimer_track_32k_value + 0x06))) //500ppm
        {
            cur_32k_tick_track_err = i;
            gpio_set_high_level(LED2);
            while (1)
                ;
        }
    }

#endif
}

/**
 *      ===============  handler  =================
 */
#if ((STIMER_MODE == STIMER_IRQ_N22) || (STIMER_MODE == STIMER_IRQ_D25_N22_DSP))
_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    #if defined(MCU_CORE_TL322X)
    if (stimer_get_irq_status_n22())
    #else
    if (stimer_get_irq_status(FLD_SYSTEM_IRQ_N22))
    #endif
    {
        gpio_toggle(LED2);
    #if defined(MCU_CORE_TL322X)
        stimer_clr_irq_status_n22(); //clr irq
    #else
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_N22); //clr irq
    #endif
        stimer_set_irq_capture_n22(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
    }
}
CLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

#elif (STIMER_MODE == STIMER_SET_32K_TICK)
_attribute_ram_code_sec_ void pm_irq_handler(void)
{
    if (analog_read_reg8(0x64) & (BIT(2))) {
        gpio_toggle(LED1);
        clock_set_32k_tick(clock_get_32k_tick() + 32000); //1s
    }
    analog_write_reg8(0x64, 0xff);
}
CLIC_ISR_REGISTER(pm_irq_handler, IRQ_PM_IRQ)

#elif (STIMER_MODE == STIMER_SET_32K_TICK_LVL)
_attribute_ram_code_sec_ void pm_level_irq_handler(void)
{
    if (analog_read_reg8(0x64) & (BIT(2))) {
        gpio_toggle(LED2);
        clock_set_32k_tick(clock_get_32k_tick() + 32000); //1s
    }
    analog_write_reg8(0x64, 0xff);
}
CLIC_ISR_REGISTER(pm_level_irq_handler, IRQ_PM_LVL)


#endif

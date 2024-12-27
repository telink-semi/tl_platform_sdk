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

#define DSP_FW_DOWNLOAD_FLASH_ADDR      0x20040000
#define N22_FW_DOWNLOAD_FLASH_ADDR      0x20080000

volatile unsigned int cur_32k_tick[200];
volatile unsigned int cur_32k_tick_step[200];
volatile unsigned int cur_32k_tick_step_err;
volatile unsigned int stimer_track_32k_value;
volatile unsigned int stimer_tick_low3bit;
volatile unsigned int cur_32k_track[200];
volatile unsigned int cur_32k_tick_track_err;
volatile unsigned int stimer_cnt =0;


#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)
#define CAPT_DMA_CNT        200
volatile unsigned int curr_capt_val =0;
volatile unsigned int last_capt_val =0;
volatile unsigned int diff_capt_val[CAPT_DMA_CNT] ={0};
unsigned int stimer_capt_dma_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
unsigned int stimer_capt_dma0_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
unsigned int stimer_capt_dma1_buff[CAPT_DMA_CNT] __attribute__((aligned(4))) = {0};
volatile unsigned int stimer_capt_step_val[CAPT_DMA_CNT];

dma_chain_config_t stimer_dma_chain_cfg[2];

#define     PWM_PCLK_SPEED              24000000
enum{
    CLOCK_PWM_CLOCK_1S = PWM_PCLK_SPEED,
    CLOCK_PWM_CLOCK_1MS = (CLOCK_PWM_CLOCK_1S / 1000),
    CLOCK_PWM_CLOCK_1US = (CLOCK_PWM_CLOCK_1S / 1000000),
};

#if defined(MCU_CORE_TL322X)
void stimer_set_pwm0(void)
{
    //PB0 A20---PWM1
    write_reg8(GPIO_BASE_ADDR+0x16, 0xfe);
    write_reg8(GPIO_BASE_ADDR+0xb8, 0x01);

    write_reg8(REG_PWM_BASE+0x10, 0x10);
    write_reg8(REG_PWM_BASE+0x11, 0x00);
    write_reg8(REG_PWM_BASE+0x12, 0x00);

    write_reg16(REG_PWM_BASE+0x30, 0x0099); //TCMP
    write_reg16(REG_PWM_BASE+0x32, 0x00ff);        //TMAX
    write_reg8(REG_PWM_BASE+0x34, 0x20);        //PHASE

    write_reg8(REG_PWM_BASE+0x1c, 0xff);
}
#else
void stimer_set_pwm0(gpio_func_pin_e pin)
{
    pwm_set_pin(pin,PWM0);
    pwm_set_clk((unsigned char) (sys_clk.pclk*1000*1000/PWM_PCLK_SPEED-1));
    pwm_set_pwm0_mode(PWM_NORMAL_MODE);
    pwm_set_tcmp(PWM0_ID,100* CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM0_ID,800* CLOCK_PWM_CLOCK_1US);
    pwm_start(FLD_PWM0_EN);
}
#endif

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

#if N22_TEST
    sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
    sys_n22_start();
#endif
#if DSP_TEST
    sys_dsp_init(DSP_FW_DOWNLOAD_FLASH_ADDR);
    sys_dsp_start();
#endif

#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)
    gpio_function_en(INPUT_CAPT_PIN);
    gpio_input_en(INPUT_CAPT_PIN);
    gpio_output_dis(INPUT_CAPT_PIN);
#endif

#if (!(defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X))) && (STIMER_MODE == STIMER_IRQ)
    stimer_set_irq_capture(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick

#if defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_MASK);   //irq enable
#else
    stimer_set_irq_mask(FLD_SYSTEM_IRQ);
#endif
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();

#elif ((defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_IRQ_D25))
    stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
#if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_MASK_D25F);
#else
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_D25F);   //irq enable
#endif
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();

#elif  ((defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_IRQ_D25_N22_DSP))
    stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S); //set capture tick
    stimer_set_irq_capture_n22(stimer_get_tick() + (500*SYSTEM_TIMER_TICK_1MS));
#if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_MASK_D25F ); //irq enable
    stimer_set_irq_mask_n22(FLD_SYSTEM_IRQ_MASK_N22);
#else
    stimer_set_irq_capture_dsp(stimer_get_tick() + (200*SYSTEM_TIMER_TICK_1MS));
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_D25F | FLD_SYSTEM_IRQ_N22 | FLD_SYSTEM_IRQ_DSP); //irq enable
#endif
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_GET_32K_TICK)
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc();

#elif (STIMER_MODE == STIMER_SET_32K_TICK)
    clock_set_32k_tick(clock_get_32k_tick() + 32000);   //1s
#if defined(MCU_CORE_TL721X)
    pm_clr_irq_status(FLD_WAKEUP_STATUS_ALL);
#else
    pm_clr_irq_status(WAKEUP_STATUS_ALL);
#endif
#if defined(MCU_CORE_B91)
    plic_interrupt_enable(IRQ_PM_TM);
#elif defined(MCU_CORE_B92)||defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X)
    plic_interrupt_enable(IRQ_PM_IRQ);
#endif
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_SET_32K_TICK_LVL)
    clock_set_32k_tick(clock_get_32k_tick() + 32000);   //1s
    pm_set_wakeup_src(PM_WAKEUP_TIMER);
#if defined(MCU_CORE_TL721X)
    pm_clr_irq_status(FLD_WAKEUP_STATUS_ALL);
#else
    pm_clr_irq_status(WAKEUP_STATUS_ALL);
#endif
    plic_interrupt_enable(IRQ_PM_LVL);
    core_interrupt_enable();

#elif (STIMER_MODE == STIMER_TRACK_32K_TICK)
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc();
    stimer_set_32k_track_cnt(STIMER_TRACK_32KCNT_16);
    stimer_track_32k_value = SYSTEM_TIMER_TICK_1MS/32 * g_track_32kcnt;
    delay_ms(1000);
#if defined(MCU_CORE_TL721X)
    stimer_set_irq_mask(FLD_SYSTEM_IRQ_32K_CAL_MASK);
#elif defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_d25f(FLD_SYSTEM_IRQ_32K_CAL_MASK);
#else
    stimer_set_irq_mask(FLD_SYSTEM_32K_IRQ);
#endif
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();


#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE)
    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
#if defined(MCU_CORE_TL322X)
    stimer_set_irq_mask_d25f(FLD_SYSTEM_CAPT_IRQ_MASK|FLD_SYSTEM_OVERFLOW_IRQ_MASK);
#else
    stimer_set_irq_mask(FLD_SYSTEM_CAPT_IRQ_MASK|FLD_SYSTEM_OVERFLOW_IRQ_MASK);
#endif
    plic_interrupt_enable(IRQ_SYSTIMER);
    core_interrupt_enable();
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the stimer input capture function.
     * The pwm output waveform passes through gpio, generating the gpio trigger signal, triggering the stimer input capture function.
     */
#if defined(MCU_CORE_TL322X)
    stimer_set_pwm0();
#else
    stimer_set_pwm0(PWM0_PIN);
#endif

#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA)
    /**
     * It is recommended to enable DMA before enabling capture.
     * Otherwise, the signal may be captured but not read by DMA, which could result in a data overflow.
     */
    stimer_set_input_capt_dma_config(CAPT_DMA_CHN);
    stimer_set_input_capt_value_dma(CAPT_DMA_CHN, stimer_capt_dma_buff, CAPT_DMA_CNT*4);
    dma_set_irq_mask(CAPT_DMA_CHN, TC_MASK);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the system timer input capture function.
     */
#if defined(MCU_CORE_TL322X)
    stimer_set_pwm0();
#else
    stimer_set_pwm0(PWM0_PIN);
#endif


#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA_LLP_MODE)
    /**
     * It is recommended to enable DMA before enabling capture.
     * Otherwise, the signal may be captured but not read by DMA, which could result in a data overflow.
     * Configure interrupt first, then configure DMA, otherwise DMA cannot enter interrupt.
     */
    dma_set_irq_mask(CAPT_DMA_CHN, TC_MASK);
    dma_set_llp_irq_mode(CAPT_DMA_CHN, DMA_INTERRUPT_MODE);
    plic_interrupt_enable(IRQ_DMA);
    core_interrupt_enable();
    stimer_set_input_capt_dma_chain_llp(CAPT_DMA_CHN, stimer_capt_dma0_buff, CAPT_DMA_CNT*4, &stimer_dma_chain_cfg[0]);
    stimer_input_capt_dma_add_list_element(CAPT_DMA_CHN, stimer_capt_dma1_buff, CAPT_DMA_CNT*4, &stimer_dma_chain_cfg[0], &stimer_dma_chain_cfg[1]);
    stimer_input_capt_dma_add_list_element(CAPT_DMA_CHN, stimer_capt_dma0_buff, CAPT_DMA_CNT*4, &stimer_dma_chain_cfg[1], &stimer_dma_chain_cfg[0]);
    stimer_set_input_capt_pin(INPUT_CAPT_PIN, CAPT_RISING_EDGE);
    stimer_set_input_capt_enable();
    /**
     * Select pwm0 as the trigger signal for the system timer input capture function.
     */
#if defined(MCU_CORE_TL322X)
    stimer_set_pwm0();
#else
    stimer_set_pwm0(PWM0_PIN);
#endif

#endif
}

void main_loop(void)
{
#if (STIMER_MODE == STIMER_DELAY)
    delay_ms(500);
    gpio_toggle(LED1);

#elif ((defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_IRQ_D25_N22_DSP))
    delay_ms(20);
#if defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status_n22(FLD_SYSTEM_IRQ_N22))
#else
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ_N22))
#endif
    {
        gpio_toggle(LED3);
#if defined(MCU_CORE_TL322X)
        stimer_clr_irq_status_n22();
#else
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_N22);
#endif
        stimer_set_irq_capture_n22(stimer_get_tick() + (500*SYSTEM_TIMER_TICK_1MS));
    }
#if !defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ_DSP))
    {
        gpio_toggle(LED4);
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_DSP);
        stimer_set_irq_capture_dsp(stimer_get_tick() + (200*SYSTEM_TIMER_TICK_1MS));
    }
#endif

#elif (STIMER_MODE == STIMER_GET_32K_TICK)
    cur_32k_tick[0] = clock_get_32k_tick();
    for(int i=1; i<200; i++)
    {
        delay_ms(100);
        cur_32k_tick[i] = clock_get_32k_tick();
        cur_32k_tick_step[i] = cur_32k_tick[i] - cur_32k_tick[i-1];
        if((cur_32k_tick_step[i] < 0xc7f) || (cur_32k_tick_step[i] > 0xc83))    //0xc81,500ppm
        {
            cur_32k_tick_step_err = i;
            gpio_set_high_level(LED1);
            while(1);
        }
    }

#elif (STIMER_MODE == STIMER_GET_TICK)
    if((stimer_get_tick()&(0x07)) != 0x00)
    {
        stimer_tick_low3bit = 1;
        gpio_set_high_level(LED1);
        while(1);
    }

#endif
}

#if (!(defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X))) && (STIMER_MODE == STIMER_IRQ)
_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ))
    {
        gpio_toggle(LED2);
        stimer_clr_irq_status(FLD_SYSTEM_IRQ);            //clr irq
        stimer_set_irq_capture(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

#elif  (defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL322X)) && ((STIMER_MODE == STIMER_IRQ_D25) || (STIMER_MODE == STIMER_IRQ_D25_N22_DSP))
_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
#if defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_D25F))
#else
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ_D25F))
#endif
    {
        gpio_toggle(LED2);
#if defined(MCU_CORE_TL322X)
        stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_D25F);
#else
        stimer_clr_irq_status(FLD_SYSTEM_IRQ_D25F);
#endif
        stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

#elif (STIMER_MODE == STIMER_SET_32K_TICK)
_attribute_ram_code_sec_ void pm_irq_handler(void)
{
    if(analog_read_reg8(0x64)&(BIT(2)))
    {
        gpio_toggle(LED2);
        clock_set_32k_tick(clock_get_32k_tick() + 32000);   //1s
    }
    analog_write_reg8(0x64, 0xff);
}
#if defined(MCU_CORE_B91)
PLIC_ISR_REGISTER(pm_irq_handler, IRQ_PM_TM)

#elif  defined(MCU_CORE_B92)||defined(MCU_CORE_TL751X)||defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)
PLIC_ISR_REGISTER(pm_irq_handler, IRQ_PM_IRQ)
#endif

#elif (STIMER_MODE == STIMER_SET_32K_TICK_LVL)
_attribute_ram_code_sec_ void pm_level_irq_handler(void)
{
    if(analog_read_reg8(0x64)&(BIT(2)))
    {
        gpio_toggle(LED2);
        clock_set_32k_tick(clock_get_32k_tick() + 32000);   //1s
    }
    analog_write_reg8(0x64, 0xff);
}
PLIC_ISR_REGISTER(pm_level_irq_handler, IRQ_PM_LVL)

#elif (STIMER_MODE == STIMER_TRACK_32K_TICK)
_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
#if defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status_d25f(FLD_SYSTEM_32K_IRQ))
#else
    if(stimer_get_irq_status(FLD_SYSTEM_32K_IRQ))
#endif
    {
        gpio_toggle(LED1);
#if defined(MCU_CORE_TL322X)
        stimer_clr_irq_status_d25f(FLD_SYSTEM_32K_IRQ);
#else
        stimer_clr_irq_status(FLD_SYSTEM_32K_IRQ);
#endif
        if(stimer_cnt < 200)
        {
            cur_32k_track[stimer_cnt] = stimer_get_tracking_32k_value();
            if((cur_32k_track[stimer_cnt] < (stimer_track_32k_value-0x06)) || (cur_32k_track[stimer_cnt] > (stimer_track_32k_value+0x06)))  //500ppm
            {
                cur_32k_tick_track_err = stimer_cnt;
                gpio_set_high_level(LED1);
            }
        }
        stimer_cnt++;
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)


#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE)
_attribute_ram_code_sec_ void stimer_irq_handler(void)
{
    gpio_toggle(LED1);
#if defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT))
#else
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ_CAPT))
#endif
    {
        if(stimer_cnt == 0)
        {
#if defined(MCU_CORE_TL322X)
            stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT);
#else
            stimer_clr_irq_status(FLD_SYSTEM_IRQ_CAPT);
#endif
#if defined(MCU_CORE_TL721X)
            gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
#else
            gpio_clr_irq_status(GPIO_IRQ_IRQ1);
#endif
            last_capt_val = stimer_get_input_capt_value();
            stimer_cnt++;
        }
        else if((stimer_cnt > 0)&&(stimer_cnt <= (CAPT_DMA_CNT/2)))
        {
#if defined(MCU_CORE_TL322X)
            stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT);
#else
            stimer_clr_irq_status(FLD_SYSTEM_IRQ_CAPT);
#endif
#if defined(MCU_CORE_TL721X)
            gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
#else
            gpio_clr_irq_status(GPIO_IRQ_IRQ1);
#endif
            curr_capt_val = stimer_get_input_capt_value();
            diff_capt_val[stimer_cnt-1] = curr_capt_val - last_capt_val;
            last_capt_val = curr_capt_val;
            stimer_cnt++;
        }
    }
#if defined(MCU_CORE_TL322X)
    if(stimer_get_irq_status_d25f(FLD_SYSTEM_IRQ_OVERFLOW))
#else
    if(stimer_get_irq_status(FLD_SYSTEM_IRQ_OVERFLOW))
#endif
    {
        if((stimer_cnt > (CAPT_DMA_CNT/2))&&(stimer_cnt <= CAPT_DMA_CNT))
        {
#if defined(MCU_CORE_TL322X)
            stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_CAPT);
            stimer_clr_irq_status_d25f(FLD_SYSTEM_IRQ_OVERFLOW);
#else
            stimer_clr_irq_status(FLD_SYSTEM_IRQ_CAPT);
            stimer_clr_irq_status(FLD_SYSTEM_IRQ_OVERFLOW);
#endif
#if defined(MCU_CORE_TL721X)
            gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
#else
            gpio_clr_irq_status(GPIO_IRQ_IRQ1);
#endif
            curr_capt_val = stimer_get_input_capt_value();
            diff_capt_val[stimer_cnt-1] = curr_capt_val - last_capt_val;
            last_capt_val = curr_capt_val;
        }
        stimer_cnt++;
    }
}
PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)

#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X))&& (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA)
void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(CAPT_DMA_STATUS))
    {
        gpio_toggle(LED1);
        dma_clr_tc_irq_status(CAPT_DMA_STATUS);
        for(int i=0; i<(CAPT_DMA_CNT-1); i++)
        {
            stimer_capt_step_val[i] = stimer_capt_dma_buff[i+1] - stimer_capt_dma_buff[i];
        }
        stimer_set_input_capt_value_dma(CAPT_DMA_CHN, stimer_capt_dma_buff, CAPT_DMA_CNT*4);
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)

#elif  (defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)) && (STIMER_MODE == STIMER_INPUT_CAPTURE_DMA_LLP_MODE)
void dma_irq_handler(void)
{
    if(dma_get_tc_irq_status(CAPT_DMA_STATUS))
    {
        gpio_toggle(LED1);
        dma_clr_tc_irq_status(CAPT_DMA_STATUS);
        for(int i=0; i<(CAPT_DMA_CNT-1); i++)
        {
            stimer_capt_step_val[i] = stimer_capt_dma0_buff[i+1] - stimer_capt_dma0_buff[i];
        }
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
#endif


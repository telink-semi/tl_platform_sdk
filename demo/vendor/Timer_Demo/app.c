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


/**
    ===============================================================================
                         ##### timer clock use APB clock  #####
    ===============================================================================
*/

#define TIMER_MODE_GPIO_TRIGGER_TICK 0x01
volatile int          timer0_irq_cnt    = 0;
volatile int          timer1_irq_cnt    = 0;
volatile unsigned int timer0_gpio_width = 0;
volatile unsigned int timer1_gpio_width = 0;

#if defined(MCU_CORE_TL721X)
#if((TIMER_MODE == TIMER_INPUT_CAPTURE_MODE) || (TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA) || (TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA_LLP))
#define     PWM_PCLK_SPEED              12000000 //pwm clock 12M.
/**
 * This configure is for PWM Ticks.
 */
enum
{
    CLOCK_PWM_CLOCK_1S  = PWM_PCLK_SPEED,
    CLOCK_PWM_CLOCK_1MS = (CLOCK_PWM_CLOCK_1S / 1000),
    CLOCK_PWM_CLOCK_1US = (CLOCK_PWM_CLOCK_1S / 1000000),
};

/**
 * @brief     This function servers to set the pwm0 output waveform .
 * @return    none.
 */
void pwm0_set_output(gpio_func_pin_e pin)
{
    pwm_set_pin(pin,PWM0);
    pwm_set_clk((unsigned char) (sys_clk.pclk*1000*1000/PWM_PCLK_SPEED-1));
    pwm_set_pwm0_mode(PWM_NORMAL_MODE);
    pwm_set_tcmp(PWM0_ID,50 * CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM0_ID,100 * CLOCK_PWM_CLOCK_1US);
    pwm_start(FLD_PWM0_EN);
}
#endif

#if(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE)
volatile unsigned char tmr0_capt_cnt  = 0;
volatile unsigned char tmr1_capt_cnt  = 0;
volatile unsigned long g_tick_cycle_tmr0[200];
volatile unsigned long timer0_curr_capt_val;
volatile unsigned long timer0_last_capt_val;
volatile unsigned long g_tick_cycle_tmr1[200];
volatile unsigned long timer1_curr_capt_val;
volatile unsigned long timer1_last_capt_val;

#elif(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA)
unsigned char rev_buff1[256] __attribute__((aligned(4)))= {0};
unsigned char rev_buff2[256] __attribute__((aligned(4)))= {0};

#elif(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA_LLP)
#define DMA_REV_LEN          256
dma_chain_config_t rx_dma_list1[2];
dma_chain_config_t rx_dma_list2[2];
unsigned char rev_buff3[256] __attribute__((aligned(4)))= {0};
unsigned char rev_buff4[256] __attribute__((aligned(4)))= {0};
#endif
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_function_en(LED2);
    gpio_function_en(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED1);
    gpio_output_en(LED2);
    gpio_output_en(LED3);
    gpio_output_en(LED4);

    clock_cal_24m_rc();
#if (TIMER_MODE == TIMER_SYS_CLOCK_MODE)
    plic_interrupt_enable(IRQ_TIMER0);
    plic_interrupt_enable(IRQ_TIMER1);
    core_interrupt_enable();
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, 500 * sys_clk.pclk * 1000); //500ms
    timer_set_init_tick(TIMER1, 0);
    timer_set_cap_tick(TIMER1, 500 * sys_clk.pclk * 1000); //500ms
    timer_set_mode(TIMER0, TIMER_MODE_SYSCLK);
    timer_set_mode(TIMER1, TIMER_MODE_SYSCLK);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    timer_set_irq_mask(FLD_TMR1_MODE_IRQ);
    #endif
    timer_start(TIMER1);
    timer_start(TIMER0);

#elif (TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_TIMER0);
    plic_interrupt_enable(IRQ_TIMER1);

    gpio_function_en(TIMER0_TRIG_PIN | TIMER1_TRIG_PIN);
    gpio_output_en(TIMER0_TRIG_PIN | TIMER1_TRIG_PIN);
    gpio_set_low_level(TIMER0_TRIG_PIN | TIMER1_TRIG_PIN);

    /****  timer0 POL_RISING  TIMER0_GPIO link TIMER0_TRIG_PIN  **/
    timer_gpio_init(TIMER0, TIMER0_GPIO, POL_RISING);
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, TIMER_MODE_GPIO_TRIGGER_TICK);
    timer_set_mode(TIMER0, TIMER_MODE_GPIO_TRIGGER);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    #endif
    timer_start(TIMER0);

    /****  timer1  POL_RISING  TIMER1_GPIO link TIMER1_TRIG_PIN  **/
    timer_gpio_init(TIMER1, TIMER1_GPIO, POL_RISING);
    timer_set_init_tick(TIMER1, 0);
    timer_set_cap_tick(TIMER1, TIMER_MODE_GPIO_TRIGGER_TICK);
    timer_set_mode(TIMER1, TIMER_MODE_GPIO_TRIGGER);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    timer_set_irq_mask(FLD_TMR1_MODE_IRQ);
    #endif
    timer_start(TIMER1);

#elif (TIMER_MODE == TIMER_GPIO_WIDTH_MODE)

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_TIMER0);
    plic_interrupt_enable(IRQ_TIMER1);

    gpio_function_en(TIMER0_TRIG_PIN | TIMER1_TRIG_PIN);
    gpio_output_en(TIMER0_TRIG_PIN | TIMER1_TRIG_PIN);

    /****  timer0 POL_RISING  TIMER0_GPIO link TIMER0_TRIG_PIN  **/
    gpio_set_high_level(TIMER0_TRIG_PIN);
    delay_ms(50);
    timer_gpio_init(TIMER0, TIMER0_GPIO, POL_FALLING);
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, 0);
    timer_set_mode(TIMER0, TIMER_MODE_GPIO_WIDTH);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    #endif
    timer_start(TIMER0);
    gpio_set_low_level(TIMER0_TRIG_PIN);
    delay_ms(250);
    gpio_set_high_level(TIMER0_TRIG_PIN);

    /****  timer1  POL_RISING  TIMER1_GPIO link TIMER1_TRIG_PIN  **/
    gpio_set_low_level(TIMER1_TRIG_PIN);
    delay_ms(50);
    timer_gpio_init(TIMER1, TIMER1_GPIO, POL_RISING);
    timer_set_init_tick(TIMER1, 0);
    timer_set_cap_tick(TIMER1, 0);
    timer_set_mode(TIMER1, TIMER_MODE_GPIO_WIDTH);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    timer_set_irq_mask(FLD_TMR1_MODE_IRQ);
    #endif
    timer_start(TIMER1);
    gpio_set_high_level(TIMER1_TRIG_PIN);
    delay_ms(250);
    gpio_set_low_level(TIMER1_TRIG_PIN);

#elif (TIMER_MODE == TIMER_TICK_MODE)
    /** Timer0*/
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, 0);
    timer_set_mode(TIMER0, TIMER_MODE_TICK); //cpu clock tick.
    timer_start(TIMER0);
    /** Timer1*/
    timer_set_init_tick(TIMER1, 0);
    timer_set_cap_tick(TIMER1, 0);
    timer_set_mode(TIMER1, TIMER_MODE_TICK); //cpu clock tick.
    timer_start(TIMER1);

#elif (TIMER_MODE == TIMER_WATCHDOG_MODE)
    delay_ms(500);
    //eagle will enter deep once after reboot, so the watchdog status cannot be read.
    if (wd_get_status()) {
        gpio_set_high_level(LED1);
        wd_clear_status();
    }
    wd_set_interval_ms(1000);
    /**
     * Wd_clear() must be executed before each call to wd_start() to avoid abnormal watchdog reset time because the initial count value is not 0.
     * For example, the watchdog is reset soon or a few minutes later.
     */
    wd_clear();
    wd_start();

#elif (!defined(MCU_CORE_B91)&&(TIMER_MODE == TIMER_32K_WATCHDOG_MODE))
    delay_ms(500);
    //Remove the stop 32k watchdog operation in main, otherwise this state cannot be read.
    if (wd_32k_get_status()) {
        gpio_set_high_level(LED1);
        wd_32k_clear_status();
    }

    #if (WATCHDOG_MODE == WATCHDOG_32K_RC_MODE)
    clock_32k_init(CLK_32K_RC);
    clock_cal_32k_rc(); //6.68ms
    #elif (WATCHDOG_MODE == WATCHDOG_32K_XTAL_MODE) //The TL7518 A0 version not support 32k xtal.
    clock_32k_init(CLK_32K_XTAL);
    clock_kick_32k_xtal(10);
    #endif

    #if defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL323X)
    wd_32k_set_interval_ms(1000);
    #else
    wd_32k_stop();
    wd_32k_set_interval_ms(1000);
    wd_32k_start();
    #endif

#elif(defined(MCU_CORE_TL721X)&&(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE))

//PWM_OUTPUT_PIN link to TIMER0_CAPT_PIN and TIMER1_CAPT_PIN, output waveform to timer for trigger capture.
    pwm0_set_output(PWM_OUTPUT_PIN);

/*Timer0*/
    timer_set_input_capture_mode(TIMER0,TMR_CAPT_FALLING_EDGE,TIMER0_CAPT_PIN);
    timer_set_irq_mask(FLD_TMR0_CAPT_IRQ);
    timer_start(TIMER0);

/*Timer1*/
    timer_set_input_capture_mode(TIMER1,TMR_CAPT_RISING_EDGE,TIMER1_CAPT_PIN);
    timer_set_irq_mask(FLD_TMR1_CAPT_IRQ);
    timer_start(TIMER1);

    plic_interrupt_enable(IRQ_TIMER0);
    plic_interrupt_enable(IRQ_TIMER1);
    core_interrupt_enable();

#elif(defined(MCU_CORE_TL721X)&&(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA))

//PWM_OUTPUT_PIN link to TIMER0_CAPT_PIN and TIMER1_CAPT_PIN, output waveform to timer for trigger capture.
    pwm0_set_output(PWM_OUTPUT_PIN);
/*Timer0*/
    //timer0 DMA set
    timer_set_rx_dma_config(TIMER0,DMA0);
    timer_receive_dma(TIMER0,(unsigned char*)rev_buff1,256);
    //timer0 input capture set
    timer_set_input_capture_mode(TIMER0,TMR_CAPT_FALLING_EDGE,TIMER0_CAPT_PIN);
    timer_start(TIMER0);
/*Timer1*/
    //timer1 DMA set
    timer_set_rx_dma_config(TIMER1,DMA1);
    timer_receive_dma(TIMER1,(unsigned char*)rev_buff2,256);
    //timer1 input capture set
    timer_set_input_capture_mode(TIMER1,TMR_CAPT_RISING_EDGE,TIMER1_CAPT_PIN);
    timer_start(TIMER1);

#elif(defined(MCU_CORE_TL721X)&&(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE_WITH_DMA_LLP))
//PWM_OUTPUT_PIN link to TIMER0_CAPT_PIN and TIMER1_CAPT_PIN, output waveform to timer for trigger capture.
    pwm0_set_output(PWM_OUTPUT_PIN);
/*Timer0*/
    //timer0 DMA LLP set
    timer_set_dma_chain_llp(TIMER0,DMA0,(unsigned char*)(rev_buff3),DMA_REV_LEN,&rx_dma_list1[0]);
    timer_set_rx_dma_add_list_element(TIMER0,DMA0,&rx_dma_list1[0],&rx_dma_list1[1],(unsigned short*)(rev_buff3),DMA_REV_LEN);
    timer_set_rx_dma_add_list_element(TIMER0,DMA0,&rx_dma_list1[1],&rx_dma_list1[0],(unsigned short*)(rev_buff3),DMA_REV_LEN);
    dma_chn_en(DMA0);
    //timer0 input capture set
    timer_set_input_capture_mode(TIMER0,TMR_CAPT_FALLING_EDGE,TIMER0_CAPT_PIN);
    timer_set_irq_mask(FLD_TMR0_CAPT_IRQ);
    timer_start(TIMER0);

/*Timer1*/
    //timer1 DMA LLP set
    timer_set_dma_chain_llp(TIMER1,DMA1,(unsigned char*)(rev_buff4),DMA_REV_LEN,&rx_dma_list2[0]);
    timer_set_rx_dma_add_list_element(TIMER1,DMA1,&rx_dma_list2[0],&rx_dma_list2[1],(unsigned short*)(rev_buff4),DMA_REV_LEN);
    timer_set_rx_dma_add_list_element(TIMER1,DMA1,&rx_dma_list2[1],&rx_dma_list2[0],(unsigned short*)(rev_buff4),DMA_REV_LEN);
    dma_chn_en(DMA1);
    //timer1 input capture set
    timer_set_input_capture_mode(TIMER1,TMR_CAPT_RISING_EDGE,TIMER1_CAPT_PIN);
    timer_set_irq_mask(FLD_TMR1_CAPT_IRQ);
    timer_start(TIMER1);
#endif
}

void main_loop(void)
{
#if (TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)

    gpio_toggle(TIMER0_TRIG_PIN);
    gpio_toggle(TIMER1_TRIG_PIN);

#elif (TIMER_MODE == TIMER_TICK_MODE)

    if (timer0_get_tick() > 500 * sys_clk.pclk * 1000) {
        timer0_set_tick(0);
        gpio_toggle(LED2);
        gpio_toggle(LED3);
    }
    if (timer1_get_tick() > 500 * sys_clk.pclk * 1000) {
        timer1_set_tick(0);
        gpio_toggle(LED4);
    }
#endif

#if (TIMER_MODE == TIMER_WATCHDOG_MODE)
    //900ms<1000ms, watchdog does not overflow and the program continues to run.
    delay_ms(900);
    wd_clear();
    gpio_set_high_level(LED2);
    //1100ms>1000ms, watchdog overflows, program restarts.
    delay_ms(1100);
    gpio_set_high_level(LED3);

#elif (!defined(MCU_CORE_B91)&&(TIMER_MODE == TIMER_32K_WATCHDOG_MODE))
    //900ms<1000ms, watchdog does not overflow and the program continues to run.
    delay_ms(900);

    #if defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL323X)
    wd_32k_feed();
    #else
    wd_32k_stop();
    wd_32k_set_interval_ms(1000);
    wd_32k_start();
    #endif

    gpio_set_high_level(LED2);
    //1100ms>1000ms, watchdog overflows, program restarts.
    delay_ms(1100);
    gpio_set_high_level(LED3);
#else

    delay_ms(500);
    gpio_toggle(LED1);

#endif
}

_attribute_ram_code_sec_ void timer0_irq_handler(void)
{
#if (TIMER_MODE == TIMER_SYS_CLOCK_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR0_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR0))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR0); //clear irq status
    #endif
        gpio_toggle(LED2);
        timer0_irq_cnt++;
    }
#elif (TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR0_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR0))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR0); //clear irq status
    #endif
        gpio_toggle(LED2);
        timer0_irq_cnt++;
    }
#elif (TIMER_MODE == TIMER_GPIO_WIDTH_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR0_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR0))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR0); //clear irq status
    #endif
        timer0_gpio_width = timer0_get_gpio_width();
        timer0_set_tick(0);
        gpio_toggle(LED2);
    }
#if defined(MCU_CORE_TL721X)
#elif(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE)
    if(timer_get_irq_status(FLD_TMR0_CAPT_IRQ))//tmr0_capt_irq
    {
         timer_clr_irq_status(FLD_TMR0_CAPT_IRQ);
         if(tmr0_capt_cnt >= 200)
         {
             tmr0_capt_cnt = 0;
         }
         timer0_curr_capt_val = timer_get_capture_value(TIMER0);
         g_tick_cycle_tmr0[tmr0_capt_cnt] = (timer0_curr_capt_val - timer0_last_capt_val);
         timer0_last_capt_val = timer0_curr_capt_val;
         tmr0_capt_cnt++;
    }
#endif
#endif
}
PLIC_ISR_REGISTER(timer0_irq_handler, IRQ_TIMER0)

_attribute_ram_code_sec_ void timer1_irq_handler(void)
{
#if (TIMER_MODE == TIMER_SYS_CLOCK_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR1_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR1))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR1); //clear irq status
    #endif
        gpio_toggle(LED3);
        timer1_irq_cnt++;
    }
#elif (TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR1_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR1))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR1); //clear irq status
    #endif
        gpio_toggle(LED3);
        timer1_irq_cnt++;
    }
#elif (TIMER_MODE == TIMER_GPIO_WIDTH_MODE)
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    if (timer_get_irq_status(FLD_TMR1_MODE_IRQ))
    #else
    if (timer_get_irq_status(TMR_STA_TMR1))
    #endif
    {
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
        timer_clr_irq_status(FLD_TMR1_MODE_IRQ); //clear irq status
    #else
        timer_clr_irq_status(TMR_STA_TMR1); //clear irq status
    #endif
        timer1_gpio_width = timer1_get_gpio_width();
        timer1_set_tick(0);
        gpio_toggle(LED3);
    }
#if defined(MCU_CORE_TL721X)
#elif(TIMER_MODE == TIMER_INPUT_CAPTURE_MODE)
    if(timer_get_irq_status(FLD_TMR1_CAPT_IRQ))
    {
         timer_clr_irq_status(FLD_TMR1_CAPT_IRQ);
         if(tmr1_capt_cnt >= 200)
         {
             tmr1_capt_cnt = 0;
         }
         timer1_curr_capt_val = timer_get_capture_value(TIMER1);
         g_tick_cycle_tmr1[tmr1_capt_cnt] = (timer1_curr_capt_val - timer1_last_capt_val);
         timer1_last_capt_val = timer1_curr_capt_val;
         tmr1_capt_cnt++;
    }
#endif
#endif
}
PLIC_ISR_REGISTER(timer1_irq_handler, IRQ_TIMER1)

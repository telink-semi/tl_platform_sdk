/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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

#define BUFF_DATA_LEN 12
#if ((IR_LEARN_MODE == IR_DIGITAL_RX_MODE) || (IR_LEARN_MODE == IR_ANALOG_RX_MODE))
    #if (DMA_EN)
        #define IR_LEARN_DMA_CHANNEL DMA1
dma_chain_config_t    rx_dma_list[2];
volatile unsigned int g_dma_chain_cnt = 0;
        #if (IR_LEARN_RX_DATA_WIDTH == 16)
unsigned short g_ir_dma_rx_buff[BUFF_DATA_LEN] __attribute__((aligned(4))) = {0};
unsigned short g_rec_buff0[BUFF_DATA_LEN] __attribute__((aligned(4)))      = {0};
unsigned short g_rec_buff1[BUFF_DATA_LEN] __attribute__((aligned(4)))      = {0};
        #elif (IR_LEARN_RX_DATA_WIDTH == 24)
unsigned int g_ir_dma_rx_buff[BUFF_DATA_LEN] __attribute__((aligned(4))) = {0};
unsigned int g_rec_buff0[BUFF_DATA_LEN] __attribute__((aligned(4)))      = {0};
unsigned int g_rec_buff1[BUFF_DATA_LEN] __attribute__((aligned(4)))      = {0};
        #endif /* IR_LEARN_RX_DATA_WIDTH */
    #endif          /* DMA_EN */

volatile unsigned int g_ir_timeout_irq_cnt = 0;
volatile unsigned int g_ir_rx_buf_irq_cnt  = 0;
volatile unsigned int g_il_index           = 0;
    #if (IR_LEARN_RX_DATA_WIDTH == 16)
volatile unsigned short g_il_wave_receive_buff[BUFF_DATA_LEN] = {0};
    #elif (IR_LEARN_RX_DATA_WIDTH == 24)
volatile unsigned int g_il_wave_receive_buff[BUFF_DATA_LEN] = {0};
    #endif /* IR_LEARN_RX_DATA_WIDTH */
#endif

#if (IR_LEARN_MODE == IR_DIGITAL_TX_MODE) || (IR_LEARN_MODE == IR_ANALOG_TX_MODE)
volatile unsigned short g_il_wave_send_buff[BUFF_DATA_LEN] = {0}; /* For comparison with data received by ir. */
unsigned short          g_ir_dma_send_buff[BUFF_DATA_LEN]  = {0};

    #define PWM_PCLK_SPEED 24000000

enum
{
    CLOCK_PWM_CLOCK_1S  = PWM_PCLK_SPEED,
    CLOCK_PWM_CLOCK_1MS = (CLOCK_PWM_CLOCK_1S / 1000),
    CLOCK_PWM_CLOCK_1US = (CLOCK_PWM_CLOCK_1S / 1000000),
};

void pwm_send_init(void)
{
    pwm_set_clk((unsigned char)(sys_clk.pclk * 1000 * 1000 / PWM_PCLK_SPEED - 1));
    pwm_set_tcmp(PWM0_ID, 50 * CLOCK_PWM_CLOCK_1US);
    pwm_set_tmax(PWM0_ID, 100 * CLOCK_PWM_CLOCK_1US);
    pwm_set_pwm0_tcmp_and_tmax_shadow(200 * CLOCK_PWM_CLOCK_1US, 100 * CLOCK_PWM_CLOCK_1US);
    pwm_set_pwm0_mode(PWM_IR_DMA_FIFO_MODE);

    /* prepare pwm send data. */
    unsigned char index = 0;
    /* normal. */
    for (unsigned char i = 0; i < 6; i++) {
        unsigned char carrier       = (i % 2 == 0) ? 1 : 0;
        g_ir_dma_send_buff[index++] = pwm_cal_pwm0_ir_fifo_cfg_data(0x0001, 0, carrier);
    }

    /* shadow. */
    for (unsigned char i = 0; i < 6; i++) {
        unsigned char carrier       = (i % 2 == 0) ? 1 : 0;
        g_ir_dma_send_buff[index++] = pwm_cal_pwm0_ir_fifo_cfg_data(0x0001, 1, carrier);
    }

    /**
     * buffer[0] is cmp time, buffer[1] is cycle time, and so on.
     * Fill the actual data sent by PWM into the array g_ir_dma_send_buff.
     * The purpose of this is to facilitate comparison with the data received in the array g_il_wave_receive_buff.
     */
    g_il_wave_send_buff[0] = 50 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[1] = 100 * CLOCK_PWM_CLOCK_1US * 2;
    g_il_wave_send_buff[2] = 50 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[3] = 100 * CLOCK_PWM_CLOCK_1US * 2;
    g_il_wave_send_buff[4] = 50 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[5] = 100 * CLOCK_PWM_CLOCK_1US * 2;

    g_il_wave_send_buff[6]  = 100 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[7]  = 200 * CLOCK_PWM_CLOCK_1US * 2;
    g_il_wave_send_buff[8]  = 100 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[9]  = 200 * CLOCK_PWM_CLOCK_1US * 2;
    g_il_wave_send_buff[10] = 100 * CLOCK_PWM_CLOCK_1US;
    g_il_wave_send_buff[11] = 200 * CLOCK_PWM_CLOCK_1US * 2;
}

#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);

#if (IR_LEARN_MODE == IR_DIGITAL_TX_MODE)

    /* pwm config. */
    pwm_send_init();
    pwm_set_pin(GPIO_FC_PB0, PWM0);

    /* interrupt config. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_PWM);
    pwm_set_irq_mask(FLD_PWM0_IR_DMA_FIFO_IRQ);

    /* dam config. */
    pwm_set_dma_config(DMA0);
    pwm_set_dma_buf(DMA0, (unsigned int)g_ir_dma_send_buff, sizeof(g_ir_dma_send_buff));
    pwm_ir_dma_mode_start(DMA0);
#elif (IR_LEARN_MODE == IR_DIGITAL_RX_MODE)
    ir_learn_rx_t ir_learn_rx = {
        .high_data_en  = 1,
        .cycle_data_en = 1,
        .timeout_en    = 1,
        .rx_invert_en  = 0,
        .cnt_mode      = RISING_EDGE_START_CNT,
    #if (IR_LEARN_RX_DATA_WIDTH == 16)
        .data_format = IR_LEARN_BIT_16_DATA,
    #elif (IR_LEARN_RX_DATA_WIDTH == 24)
        .data_format = IR_LEARN_BIT_24_DATA,
    #endif
        .rx_mode = DIGITAL_RX_MODE,
    };

    ir_learn_rx_init(&ir_learn_rx);
    ir_learn_set_dig_rx_pin(GPIO_PA0, GPIO_PIN_PULLDOWN_100K);
    #if (DMA_EN)
        #if (DMA_MODE == DMA_MODE_NO_CHAIN)
    /**
     * API ir_learn_receive_dma is responsible for moving the data received by the ir-learn module from the ir-learn fifo to the sram.
     */
    ir_learn_receive_dma(IR_LEARN_DMA_CHANNEL, (unsigned int *)(g_ir_dma_rx_buff), sizeof(g_ir_dma_rx_buff));
        #elif (DMA_MODE == DMA_LLP_PINGPONG)
    /* DMA irq init. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_DMA);
    dma_set_llp_irq_mode(IR_LEARN_DMA_CHANNEL, DMA_INTERRUPT_MODE);
    dma_set_irq_mask(IR_LEARN_DMA_CHANNEL, TC_MASK);
    /* RX DMA init. */
    ir_learn_set_dma_chain_llp(IR_LEARN_DMA_CHANNEL, (unsigned char *)(g_rec_buff0), sizeof(g_rec_buff0), &rx_dma_list[0]);
    ir_learn_rx_dma_add_list_element(IR_LEARN_DMA_CHANNEL, &rx_dma_list[0], &rx_dma_list[1], (unsigned char *)(g_rec_buff1), sizeof(g_rec_buff1));
    ir_learn_rx_dma_add_list_element(IR_LEARN_DMA_CHANNEL, &rx_dma_list[1], &rx_dma_list[0], (unsigned char *)(g_rec_buff0), sizeof(g_rec_buff0));
    dma_chn_en(IR_LEARN_DMA_CHANNEL);
        #endif
    #else
    ir_learn_rx_irq_trig_cnt(0x03);
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_IR_LEARN);
    ir_learn_set_irq_mask(FLD_IR_LEARN_TIMEOUT_IRQ | FLD_IR_LEARN_RXFIFO_IRQ);
    #endif
    ir_learn_en();
#elif (IR_LEARN_MODE == IR_ANALOG_TX_MODE)
    /* pwm config. */
    pwm_send_init();

    /* ir_learn tx config. */
    ir_learn_tx_t ir_learn_tx = {
        .tx_mode = ANALOG_TX_MODE,
    };
    ir_learn_tx_init(&ir_learn_tx);

    /* interrupt config. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_PWM);
    pwm_set_irq_mask(FLD_PWM0_IR_DMA_FIFO_IRQ);

    /* dam config. */
    pwm_set_dma_config(DMA0);
    pwm_set_dma_buf(DMA0, (unsigned int)g_ir_dma_send_buff, sizeof(g_ir_dma_send_buff));
    pwm_ir_dma_mode_start(DMA0);
#elif (IR_LEARN_MODE == IR_ANALOG_RX_MODE)
    ir_learn_rx_t ir_learn_rx = {
        .high_data_en  = 1,
        .cycle_data_en = 1,
        .timeout_en    = 1,
        .rx_invert_en  = 1,
        .cnt_mode      = RISING_EDGE_START_CNT,
    #if (IR_LEARN_RX_DATA_WIDTH == 16)
        .data_format = IR_LEARN_BIT_16_DATA,
    #elif (IR_LEARN_RX_DATA_WIDTH == 24)
        .data_format = IR_LEARN_BIT_24_DATA,
    #endif
        .rx_mode = ANALOG_RX_MODE,
    };
    ir_learn_rx_init(&ir_learn_rx);

    #if (DMA_EN)
        #if (DMA_MODE == DMA_MODE_NO_CHAIN)
    /**
     * API ir_learn_receive_dma is responsible for moving the data received by the ir-learn module from the ir-learn fifo to the sram.
     */
    ir_learn_receive_dma(IR_LEARN_DMA_CHANNEL, (unsigned int *)(g_ir_dma_rx_buff), sizeof(g_ir_dma_rx_buff));
        #elif (DMA_MODE == DMA_LLP_PINGPONG)
    /* DMA irq init. */
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_DMA);
    dma_set_llp_irq_mode(IR_LEARN_DMA_CHANNEL, DMA_INTERRUPT_MODE);
    dma_set_irq_mask(IR_LEARN_DMA_CHANNEL, TC_MASK);
    /* RX DMA init. */
    ir_learn_set_dma_chain_llp(IR_LEARN_DMA_CHANNEL, (unsigned char *)(g_rec_buff0), sizeof(g_rec_buff0), &rx_dma_list[0]);
    ir_learn_rx_dma_add_list_element(IR_LEARN_DMA_CHANNEL, &rx_dma_list[0], &rx_dma_list[1], (unsigned char *)(g_rec_buff1), sizeof(g_rec_buff1));
    ir_learn_rx_dma_add_list_element(IR_LEARN_DMA_CHANNEL, &rx_dma_list[1], &rx_dma_list[0], (unsigned char *)(g_rec_buff0), sizeof(g_rec_buff0));
    dma_chn_en(IR_LEARN_DMA_CHANNEL);
        #endif
    #else
    ir_learn_rx_irq_trig_cnt(0x03);

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_IR_LEARN);
    ir_learn_set_irq_mask(FLD_IR_LEARN_TIMEOUT_IRQ | FLD_IR_LEARN_RXFIFO_IRQ);
    #endif
    ir_learn_en();
    #if (IR_LEARN_PM_FUNCTION_EN)
    ir_learn_ana_rx_dis();
    pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, PM_TICK_STIMER, 500);
    ir_learn_ana_rx_en();
    #endif /* IR_LEARN_PM_FUNCTION_EN */

#endif
}

/**
 * @brief       This function serves to handle the interrupt of MCU
 * @return      none
 */
#if ((IR_LEARN_MODE == IR_DIGITAL_RX_MODE) || (IR_LEARN_MODE == IR_ANALOG_RX_MODE)) && (!DMA_EN)
_attribute_ram_code_sec_noinline_ void ir_learn_irq_handler(void)
{
    if (ir_learn_get_irq_status(FLD_IR_LEARN_RXFIFO_IRQ)) {
        gpio_toggle(LED4);
        g_ir_rx_buf_irq_cnt++;
        unsigned char fifo_cnt = ir_learn_get_rx_fifo_status(FLD_IR_LEARN_FIFO_RX_CNT);
    #if (IR_LEARN_RX_DATA_WIDTH == 16)
        for (unsigned char i = 0; i < fifo_cnt / 2; i++) {
            g_il_wave_receive_buff[g_il_index++] = ir_learn_get_data_by_hword();
            g_il_index %= BUFF_DATA_LEN;
        }
    #elif (IR_LEARN_RX_DATA_WIDTH == 24)
        for (unsigned char i = 0; i < fifo_cnt / 4; i++) {
            g_il_wave_receive_buff[g_il_index++] = ir_learn_get_data_by_word();
            g_il_index %= BUFF_DATA_LEN;
        }
    #endif
        ir_learn_clr_irq_status(FLD_IR_LEARN_RXFIFO_IRQ);
    }

    if (ir_learn_get_irq_status(FLD_IR_LEARN_TIMEOUT_IRQ)) {
        gpio_toggle(LED3);
        g_ir_timeout_irq_cnt++;
        unsigned char fifo_cnt = ir_learn_get_rx_fifo_status(FLD_IR_LEARN_FIFO_RX_CNT);
    #if (IR_LEARN_RX_DATA_WIDTH == 16)
        for (unsigned char i = 0; i < fifo_cnt / 2; i++) {
            g_il_wave_receive_buff[g_il_index++] = ir_learn_get_data_by_hword();
            g_il_index %= BUFF_DATA_LEN;
        }
    #elif (IR_LEARN_RX_DATA_WIDTH == 24)
        for (unsigned char i = 0; i < fifo_cnt / 4; i++) {
            g_il_wave_receive_buff[g_il_index++] = ir_learn_get_data_by_word();
            g_il_index %= BUFF_DATA_LEN;
        }
    #endif
        ir_learn_clr_irq_status(FLD_IR_LEARN_TIMEOUT_IRQ);
    }
}
PLIC_ISR_REGISTER(ir_learn_irq_handler, IRQ_IR_LEARN)
#endif

#if (IR_LEARN_MODE == IR_DIGITAL_TX_MODE) || (IR_LEARN_MODE == IR_ANALOG_TX_MODE)
_attribute_ram_code_sec_ void pwm_irq_handler(void)
{
    if (pwm_get_irq_status(FLD_PWM0_IR_DMA_FIFO_IRQ)) {
        pwm_clr_irq_status(FLD_PWM0_IR_DMA_FIFO_IRQ);
        gpio_toggle(LED2);
    }
}
PLIC_ISR_REGISTER(pwm_irq_handler, IRQ_PWM)
#endif

#if ((IR_LEARN_MODE == IR_DIGITAL_RX_MODE) || (IR_LEARN_MODE == IR_ANALOG_RX_MODE))
    #if ((DMA_EN) && (DMA_MODE == DMA_LLP_PINGPONG))
void dma_irq_handler(void)
{
    if (dma_get_tc_irq_status(BIT(IR_LEARN_DMA_CHANNEL))) {
        dma_clr_tc_irq_status(BIT(IR_LEARN_DMA_CHANNEL));
        g_dma_chain_cnt++;
        gpio_toggle(LED3);
    }
}
PLIC_ISR_REGISTER(dma_irq_handler, IRQ_DMA)
    #endif
#endif

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}

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

/****  This demo is for N22 only and needs to be used with the main core D25f
 *
 * Notices: 1.N22 and D25 cannot write the same register at the same time
 *          2.N22 and D25 can read the same register at the same time
 *  ***/

#if (TEST_MAILBOX)
    #if (MAILBOX_N22_D25F)
unsigned int           val_n22_to_d25f_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_d25f_to_n22_word[2]     = {0};
volatile unsigned char mailbox_d25_to_n22_irq_flag = 0;
    #endif

    #if !defined(MCU_CORE_TL322X) && (MAILBOX_N22_DSP)
unsigned int           val_n22_to_dsp_word[2]      = {0x01234567, 0x89abcdef};
unsigned int           val_dsp_to_n22_word[2]      = {0};
volatile unsigned char mailbox_dsp_to_n22_irq_flag = 0;
    #endif
#endif

void user_init(void)
{
    gpio_function_en(LED2);
    gpio_input_dis(LED2);
    gpio_output_en(LED2);

#if (TEST_MAILBOX)
    #if (MAILBOX_N22_D25F)
    #if defined(MCU_CORE_TL322X)
    mailbox_set_irq_mask_n22();
    #else
    mailbox_set_irq_mask(FLD_MAILBOX_D25F_TO_N22_IRQ);
    #endif
    clic_init();
    clic_interrupt_enable(IRQ_IRQ_MAILBOX_D25_TO_N22);
    core_interrupt_enable();
    #endif

    #if !defined(MCU_CORE_TL322X) && (MAILBOX_N22_DSP)
    mailbox_set_irq_mask(FLD_MAILBOX_DSP_TO_N22_IRQ);
    clic_init();
    clic_interrupt_enable(IRQ_IRQ_MAILBOX_DSP_TO_N22);
    core_interrupt_enable();

    mailbox_n22_set_dsp_msg(val_n22_to_dsp_word);
    #endif
#endif
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop(void)
{
#if (TEST_MAILBOX)
    #if (MAILBOX_N22_D25F)
    if (mailbox_d25_to_n22_irq_flag == 1) {
        mailbox_d25_to_n22_irq_flag = 0;
        if ((val_d25f_to_n22_word[0] == val_n22_to_d25f_word[0]) && (val_d25f_to_n22_word[1] == val_n22_to_d25f_word[1])) {
            mailbox_n22_set_d25f_msg(val_n22_to_d25f_word);
        #if (TEST_STALL)
            gpio_set_low_level(LED2);
            core_entry_wfi_mode();
        #else
            gpio_toggle(LED2);
        #endif
        }
    }
        #if (TEST_STALL)
    gpio_toggle(LED2);
    delay_ms(100);
        #endif
    #endif

    #if !defined(MCU_CORE_TL322X) && (MAILBOX_N22_DSP)
    if (mailbox_dsp_to_n22_irq_flag == 1) {
        mailbox_dsp_to_n22_irq_flag = 0;

        if ((val_dsp_to_n22_word[0] == val_n22_to_dsp_word[0]) && (val_dsp_to_n22_word[1] == val_n22_to_dsp_word[1])) {
            gpio_toggle(LED2);
        }
    }
    delay_ms(300);
    mailbox_n22_set_dsp_msg(val_n22_to_dsp_word);
    #endif
#else
    gpio_toggle(LED2); //D2F cannot go to toggle at the same time
    delay_ms(1000);    //can read with D25F at the same time
#endif
}

#if (TEST_MAILBOX)
    #if defined(MCU_CORE_TL322X) && (MAILBOX_N22_D25F)
_attribute_ram_code_sec_noinline_ void mailbox_d25_to_n22_irq_handler(void)
{
    if (mailbox_get_irq_status_n22()) {
        mailbox_clr_irq_status_n22();
        mailbox_n22_get_d25f_msg(val_d25f_to_n22_word);
        mailbox_d25_to_n22_irq_flag = 1;
    }
}
CLIC_ISR_REGISTER(mailbox_d25_to_n22_irq_handler, IRQ_IRQ_MAILBOX_D25_TO_N22)
    #endif

    #if !defined(MCU_CORE_TL322X) && (MAILBOX_N22_D25F)
_attribute_ram_code_sec_noinline_ void mailbox_d25_to_n22_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_D25F_TO_N22_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_D25F_TO_N22_IRQ);
        mailbox_n22_get_d25f_msg(val_d25f_to_n22_word);
        mailbox_d25_to_n22_irq_flag = 1;
    }
}
CLIC_ISR_REGISTER(mailbox_d25_to_n22_irq_handler, IRQ_IRQ_MAILBOX_D25_TO_N22)
    #endif

    #if !defined(MCU_CORE_TL322X) && (MAILBOX_N22_DSP)
_attribute_ram_code_sec_noinline_ void mailbox_dsp_to_n22_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_DSP_TO_N22_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_DSP_TO_N22_IRQ);
        mailbox_n22_get_dsp_msg(val_dsp_to_n22_word);
        mailbox_dsp_to_n22_irq_flag = 1;
    }
}
CLIC_ISR_REGISTER(mailbox_dsp_to_n22_irq_handler, IRQ_IRQ_MAILBOX_DSP_TO_N22)
    #endif
#endif

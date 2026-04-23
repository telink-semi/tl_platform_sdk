/********************************************************************************************************
 * @file    hal_mailbox.h
 *
 * @brief   This is the header file for tl752x
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



#ifndef __HAL_MAILBOX_H__
#define __HAL_MAILBOX_H__
#include "inc/drv_ipcm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    FLD_MAILBOX_D25F_TO_DSP_IRQ = BIT(0),
    FLD_MAILBOX_DSP_TO_D25F_IRQ = BIT(1),
    FLD_MAILBOX_D25F_TO_N22_IRQ = BIT(2),
    FLD_MAILBOX_N22_TO_D25F_IRQ = BIT(3),
    FLD_MAILBOX_N22_TO_DSP_IRQ  = BIT(4),
    FLD_MAILBOX_DSP_TO_N22_IRQ  = BIT(5),
} mailbox_irq_status_e;

void mailbox_d25f_set_n22_msg(unsigned int *msg_words);
void mailbox_d25f_get_n22_msg(unsigned int *msg_words);

void mailbox_d25f_set_dsp_msg(unsigned int *msg_words);
void mailbox_d25f_get_dsp_msg(unsigned int *msg_words);

void mailbox_n22_set_d25f_msg(unsigned int *msg_words);
void mailbox_n22_get_d25f_msg(unsigned int *msg_words);

void mailbox_n22_set_dsp_msg(unsigned int *msg_words);
void mailbox_n22_get_dsp_msg(unsigned int *msg_words);

void mailbox_dsp_set_d25f_msg(unsigned int * msg_words);
void mailbox_dsp_get_d25f_msg(unsigned int *msg_words);

void mailbox_dsp_set_n22_msg(unsigned int * msg_words);
void mailbox_dsp_get_n22_msg(unsigned int *msg_words);

unsigned int mailbox_get_irq_status(void);
void mailbox_clr_irq_status(unsigned int status);

void mailbox_set_irq_mask(mailbox_irq_status_e mask);
void mailbox_clr_irq_mask(mailbox_irq_status_e mask);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_MAILBOX_H__ */

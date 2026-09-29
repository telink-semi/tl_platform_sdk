/********************************************************************************************************
 * @file    mailbox.c
 *
 * @brief   This is the source file for tl753x
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "mailbox.h"

/**
 * @brief     This function servers to set mailbox irq mask.
 * @param[in] mask - mailbox irq mask.
 * @return    none
 */
void mailbox_set_irq_mask(mailbox_irq_status_e mask)
{
    switch (mask)
    {
    case FLD_MAILBOX_N22_TO_D25F_IRQ:
        BM_SET(reg_mailbox_irq_mask0, BIT(0));
        break;
    case FLD_MAILBOX_DSP_TO_D25F_IRQ:
        BM_SET(reg_mailbox_irq_mask0, BIT(1));
        break;
    case FLD_MAILBOX_D25F_TO_N22_IRQ:
        BM_SET(reg_mailbox_irq_mask1, BIT(0));
        break;
    case FLD_MAILBOX_DSP_TO_N22_IRQ:
        BM_SET(reg_mailbox_irq_mask1, BIT(1));
        break;
    case FLD_MAILBOX_D25F_TO_DSP_IRQ:
        BM_SET(reg_mailbox_irq_mask2, BIT(0));
        break;
    case FLD_MAILBOX_N22_TO_DSP_IRQ:
        BM_SET(reg_mailbox_irq_mask2, BIT(1));
        break;
    default:
        break;
    }
}

/**
 * @brief     This function servers to clr mailbox irq mask.
 * @param[in] mask - mailbox irq mask.
 * @return    none
 */
void mailbox_clr_irq_mask(mailbox_irq_status_e mask)
{
    switch (mask)
    {
    case FLD_MAILBOX_N22_TO_D25F_IRQ:
        BM_CLR(reg_mailbox_irq_mask0, BIT(0));
        break;
    case FLD_MAILBOX_DSP_TO_D25F_IRQ:
        BM_CLR(reg_mailbox_irq_mask0, BIT(1));
        break;
    case FLD_MAILBOX_D25F_TO_N22_IRQ:
        BM_CLR(reg_mailbox_irq_mask1, BIT(0));
        break;
    case FLD_MAILBOX_DSP_TO_N22_IRQ:
        BM_CLR(reg_mailbox_irq_mask1, BIT(1));
        break;
    case FLD_MAILBOX_D25F_TO_DSP_IRQ:
        BM_CLR(reg_mailbox_irq_mask2, BIT(0));
        break;
    case FLD_MAILBOX_N22_TO_DSP_IRQ:
        BM_CLR(reg_mailbox_irq_mask2, BIT(1));
        break;
    default:
        break;
    }
}

/**
 * @brief     This function servers to get the mailbox interrupt status.
 * @param[in] status    - variable of enum to select the mailbox interrupt source.
 * @retval    non-zero      - the interrupt occurred.
 * @retval    zero  - the interrupt did not occur.
 */
unsigned char mailbox_get_irq_status(void)
{
    unsigned int intr_status = 0;
    unsigned int ret = 0;

    intr_status = reg_mailbox_irq_status0;
    if (intr_status & (BIT(0)))
    {
        ret |= FLD_MAILBOX_N22_TO_D25F_IRQ;
    }

    if (intr_status & (BIT(1)))
    {
        ret |= FLD_MAILBOX_DSP_TO_D25F_IRQ;
    }

    intr_status = reg_mailbox_irq_status1;
    if (intr_status & (BIT(0)))
    {
        ret |= FLD_MAILBOX_D25F_TO_N22_IRQ;
    }

    if (intr_status & (BIT(1)))
    {
        ret |= FLD_MAILBOX_DSP_TO_N22_IRQ;
    }

    intr_status = reg_mailbox_irq_status2;
    if (intr_status & (BIT(0)))
    {
        ret |= FLD_MAILBOX_D25F_TO_DSP_IRQ;
    }

    if (intr_status & (BIT(1)))
    {
        ret |= FLD_MAILBOX_N22_TO_DSP_IRQ;
    }

    return ret;
}

/**
 * @brief     This function servers to clear the mailbox interrupt.
 * @param[in] status  - variable of enum to select the mailbox interrupt source.
 * @return    none.
 */
void mailbox_clr_irq_status(mailbox_irq_status_e status)
{
    switch (status)
    {
    case FLD_MAILBOX_N22_TO_D25F_IRQ:
        reg_mailbox_irq_status0 = BIT(0);
        break;
    case FLD_MAILBOX_DSP_TO_D25F_IRQ:
        reg_mailbox_irq_status0 = BIT(1);
        break;
    case FLD_MAILBOX_D25F_TO_N22_IRQ:
        reg_mailbox_irq_status1 = BIT(0);
        break;
    case FLD_MAILBOX_DSP_TO_N22_IRQ:
        reg_mailbox_irq_status1 = BIT(1);
        break;
    case FLD_MAILBOX_D25F_TO_DSP_IRQ:
        reg_mailbox_irq_status2 = BIT(0);
        break;
    case FLD_MAILBOX_N22_TO_DSP_IRQ:
        reg_mailbox_irq_status2 = BIT(1);
        break;
    default:
        break;
    }
}

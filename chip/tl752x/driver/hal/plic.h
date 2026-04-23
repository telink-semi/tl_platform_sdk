/********************************************************************************************************
 * @file    plic.h
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


/** @page PLIC
 *
 *  Introduction
 *  ===============
 *  Platform-Level Interrupt Controller (PLIC)
 *
 *  API Reference
 *  ===============
 *  Header File: plic.h
 *
 *  PLIC features
 *  ===============
 *    - Compatible with RISC-V PLIC
 *    - For preemptive priority interrupt extension, when preempt is enabled, high priority interrupt can disturb low priority interrupt.
 *    - There are two modes of interrupt, vector and regular mode, and the driver defaults to vector mode(each external interrupt has its own entry address, which can speed up the response to interrupts).
 *
 *  How to use this driver
 *  ===============
 *    - Use the feature of preemptive priority interrupt:
 *        -# Enable preempt using the function plic_preempt_feature_en().
 *        -# Set interrupt priority and threshold using the function plic_set_priority() and plic_set_threshold(), interrupt occurs only when priority is greater than threshold.
 *            - default priority is 1.
 *            - default threshold is 0.
 *        -# Enable global interrupt using the function core_interrupt_enable().
 *        -# Enable plic interrupt source, for example stimer module plic_interrupt_enable(IRQ_SYSTIMER).
 *        -# Enable the mask of the corresponding module, for example stimer_set_irq_mask().
 *    - Do not use the feature of preemptive priority interrupt:
 *        -# Enable global interrupt using the function core_interrupt_enable().
 *        -# Enable plic interrupt source, for example stimer module plic_interrupt_enable(IRQ_SYSTIMER).
 *        -# Enable the mask of the corresponding module, for example stimer_set_irq_mask().
 *    - Interrupt service routine
 *        -# Defining interrupt service routine, recommended name see @ref irq_source_index.
 *        -# Register interrupt service routine using the PLIC_ISR_REGISTER macro, for example: PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER).
 *          - stimer_irq_handler - stimer interrupt service routine.
 *          - IRQ_SYSTIMER - stimer interrupt number.
 *        -# In interrupt service routine:
 *          -# Get the interrupt status flag bit and clear it, for example stimer_get_irq_status() determines whether corresponding interrupt occurs, and stimer_clr_irq_status() clears it.
 *          -# Your application code.
 *          -# Return from interrupt.
 *        -# For example:
 *              @code
 *               _attribute_ram_code_sec_ void stimer_irq_handler(void)
 *               {
 *                   if(stimer_get_irq_status(FLD_SYSTEM_IRQ_D25F))
 *                   {
 *                       stimer_clr_irq_status(FLD_SYSTEM_IRQ_D25F);
 *                       stimer_set_irq_capture_d25f(stimer_get_tick() + SYSTEM_TIMER_TICK_1S);
 *                       gpio_toggle(LED2);
 *                   }
 *               }
 *               PLIC_ISR_REGISTER(stimer_irq_handler, IRQ_SYSTIMER)
 *              @endcode
 *    - Saving and disabling global interrupts and restoring global interrupts example.
 *        -# Saving and disabling global interrupts example:
 *            @code
 *            void global_interrupts_save_and_disable(void)
 *            {
 *                g_mstatus_value = core_interrupt_disable();
 *                g_mie_value     = core_mie_disable(FLD_MIE_MSIE | FLD_MIE_MTIE | FLD_MIE_MEIE);
 *                plic_all_interrupt_save_and_disable();
 *            }
 *            @endcode
 *        -# Restoring global interrupts example:
 *            @code
 *            void global_interrupts_restore(void)
 *            {
 *                plic_all_interrupt_restore();
 *                core_mie_restore(g_mie_value);
 *                core_restore_interrupt(g_mstatus_value);
 *            }
 *            @endcode
 *    - WFI Example.
 *      # Before entering WFI, set the wakeup source and turn off unneeded interrupts:
 *          @code
 *          plic_irqs_preprocess_for_wfi(1, FLD_MIE_MEIE); // disable all interrupts except MEIE.
 *          plic_interrupt_enable(IRQ_SYSTIMER); // stimer wakeup.
 *          core_entry_wfi_mode(); // enter wfi.
 *          @endcode
 *      # After WFI wakeup, clear the corresponding interrupt flag bit and restore other interrupts:
 *          @code
 *          core_entry_wfi_mode();
 *          stimer_clr_irq_status(FLD_SYSTEM_IRQ); // clear stimer irq status.
 *          plic_irqs_postprocess_for_wfi(); // restore interrupts.
 *          @endcode
 */
#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "hal/mcu_core.h"
#include "reg/plic_reg.h"

#if defined(MCU_CORE_TL752X_D25F)

/**
 * @brief Interrupt preempt config.
 */
typedef struct
{
    unsigned char preempt_en;
    unsigned char threshold;
} preempt_config_t;

/**
 * @brief Declare the interrupt service routine type.
 */
typedef void (*func_isr_t)(void);

/**
 * @brief The global variable is used to indicate whether interrupt nesting is supported.
 * @note
 *        - To avoid interrupt nesting failures caused by sign extension, the unsigned long type is used here.
 */
extern volatile unsigned long g_plic_preempt_en;
extern volatile unsigned long g_int_dis_cnt;
    /**
 * @defgroup irq_source_index Interrupt source index definition
 * @{
 * @brief Defines the number of each interrupt in the system and its corresponding handler function.
 */
    #define IRQ_CPU_DMA                 1  /* CPU_DMA_IRQHandler                    */
    #define IRQ_AUDIO_DMA               2  /* AUDIO_DMA_IRQHandler                  */
    #define IRQ_CPU2_DMA                3  /* CPU2_DMA_IRQHandler                   */
    #define IRQ_IPCM                    4  /* IPCM_IRQHandler                       */
    #define IRQ_CPU1_DMA                5  /* CPU1_DMA_IRQHandler                   */
    #define IRQ_SYSTIMER                6  /* SYSTIMER_IRQHandler                   */
    #define IRQ_TIMER0_0                7  /* TIMER0_0_IRQHandler                   */
    #define IRQ_TIMER0_1                8  /* TIMER0_1_IRQHandler                   */
    #define IRQ_TIMER0_2                9  /* TIMER0_2_IRQHandler                   */
    #define IRQ_TIMER0_3                10 /* TIMER0_3_IRQHandler                   */
    #define IRQ_TIMER1_0                11 /* TIMER1_0_IRQHandler                   */
    #define IRQ_TIMER1_1                12 /* TIMER1_1_IRQHandler                   */
    #define IRQ_TIMER1_2                13 /* TIMER1_2_IRQHandler                   */
    #define IRQ_TIMER1_3                14 /* TIMER1_3_IRQHandler                   */
    #define IRQ_RTC                     15 /* RTC_IRQHandler                        */
    #define IRQ_GPIO                    16 /* GPIO_IRQHandler                       */
    #define IRQ_CPU_WDT                 17 /* CPU_WDT_IRQHandler                    */
    #define IRQ_UART0                   18 /* UART0_IRQHandler                      */
    #define IRQ_UART1                   19 /* UART1_IRQHandler                      */
    #define IRQ_I2C0                    20 /* I2C0_IRQHandler                       */
    #define IRQ_I2C1                    21 /* I2C1_IRQHandler                       */
    #define IRQ_I2C2                    22 /* I2C2_IRQHandler                       */
    #define IRQ_DW_APB_SSI0_S           23 /* DW_APB_SSI0_S_IRQHandler              */
    #define IRQ_DW_APB_SSI0_M           24 /* DW_APB_SSI0_M_IRQHandler              */
    #define IRQ_DWC_SSI_0               25 /* DWC_SSI_0_IRQHandler                  */
    #define IRQ_DWC_SSI_1               26 /* DWC_SSI_1_IRQHandler                  */
    #define IRQ_SDIO                    27 /* SDIO_IRQHandler                       */
    #define IRQ_USB                     28 /* USB_IRQHandler                        */
    #define IRQ_USB1_RESET_250US        29 /* USB1_RESET_250US_IRQHandler           */
    #define IRQ_USB1_EP0_SETUP          30 /* USB1_EP0_SETUP_IRQHandler             */
    #define IRQ_USB1_EP0_DATA           31 /* USB1_EP0_DATA_IRQHandler              */
    #define IRQ_USB1_EP0_STATUS         32 /* USB1_EP0_STATUS_IRQHandler            */
    #define IRQ_USB1_EP0_SETINF_SETADDR 33 /* USB1_EP0_SETINF_SETADDR_IRQHandler    */
    #define IRQ_USB1_EPN_DATA           34 /* USB1_EPN_DATA_IRQHandler              */
    #define IRQ_USB1_SUSPEND            35 /* USB1_SUSPEND_IRQHandler               */

    #define IRQ_RESERVED_36             36 /* RESERVED_36                           */

    #define IRQ_GPADC                   37 /* GPADC_IRQHandler                      */
    #define IRQ_CHG_START               38 /* CHG_START_IRQHandler                  */
    #define IRQ_BT_SYS_BT               39 /* BT_SYS_BT_IRQHandler                  */
    #define IRQ_BT_SYS_BLE              40 /* BT_SYS_BLE_IRQHandler                 */
    #define IRQ_BT_SYS_BT_DM            41 /* BT_SYS_BT_DM_IRQHandler               */
    #define IRQ_BT_SYS_DBM              42 /* BT_SYS_DBM_IRQHandler                 */
    #define IRQ_BT_SYS_BB               43 /* BT_SYS_BB_IRQHandler                  */
    #define IRQ_TAHDT                     44 /* TAHDT_IRQHandler                        */
    #define IRQ_UART2                   45 /* UART2_IRQHandler                      */
    #define IRQ_UART3                   46 /* UART3_IRQHandler                      */
    #define IRQ_TDM0                    47 /* TDM0_IRQHandler                       */
    #define IRQ_TDM1                    48 /* TDM1_IRQHandler                       */
    #define IRQ_TDM2                    49 /* TDM2_IRQHandler                       */
    #define IRQ_TDM3                    50 /* TDM3_IRQHandler                       */
    #define IRQ_PDM0                    51 /* PDM0_IRQHandler                       */
    #define IRQ_PDM1                    52 /* PDM1_IRQHandler                       */
    #define IRQ_PDMC                    53 /* PDMC_IRQHandler                       */
    #define IRQ_AUDIO_CODEC             54 /* AUDIO_CODEC_IRQHandler                */
    #define IRQ_SPDIF                   55 /* SPDIF_IRQHandler                      */
    #define IRQ_RESAMPLE                56 /* RESAMPLE_IRQHandler                   */
    #define IRQ_OSR_TRNG                57 /* OSR_TRNG_IRQHandler                   */
    #define IRQ_EFUSE                   58 /* EFUSE_IRQHandler                      */
    #define IRQ_UART4                   59 /* UART4_IRQHandler                      */
    /**
 * @}
 */

    /**
 * @brief This macro generates a unique name for an interrupt service routine (ISR) entry point based on the input parameter. \n
 * The generated name is in the form "entry_irq" followed by the value of "irq_num". \n
 * For example, ISR_ENTRY_NAME(1) means entry_irq1.
 * @param[in] irq_num - The number of the interrupt see @ref irq_source_index.
 */
    #define ISR_ENTRY_NAME(irq_num) entry_irq##irq_num

    /**
 * @brief Interrupt service routine register, this macro defines an entry_irq function based on irq_num. \n
 *        The machine attribute was added to the interrupt function, and the compiler saw that it would insert code that modified the protection register, for example:
 *        @code {.c}
 *           _attribute_ram_code_sec_noinline_ entry_irq1(void) __attribute__ ((interrupt ("machine") , aligned(4)));
 *        @endcode
 * @param[in] isr - Interrupt service routine pointer.
 * @param[in] irq_num - The number of the interrupt see @ref irq_source_index.
 * @note
 *      - The same interruption number can only be registered once.
 *      - The code in the interrupt service handler should be as simple as possible, and if you can do it without function calls, you can reduce the number of registers on the stack, \n
 *        thus reducing the code size and speeding up the interrupt response.
 */
    #define PLIC_ISR_REGISTER(isr, irq_num)                                                                                     \
        _attribute_ram_code_sec_noinline_ void ISR_ENTRY_NAME(irq_num)(void) __attribute__((interrupt("machine"), aligned(4))); \
        void                                   ISR_ENTRY_NAME(irq_num)(void)                                                    \
        {                                                                                                                       \
            plic_isr(isr, irq_num);                                                                                             \
        }

/**
 * @brief Interrupt source priority. The larger the value, the higher the priority. The default priority value is 1.
 * @note  An interrupt occurs only when priority is greater than threshold.
 */
typedef enum
{
    IRQ_PRI_LEV0, /**< 0 indicates that no interrupt is generated. */
    IRQ_PRI_LEV1,
    IRQ_PRI_LEV2,
    IRQ_PRI_LEV3,
} irq_priority_e;

/**
 * @brief Target interrupt priority threshold. The larger the value, the higher the threshold. The default threshold value is 0.
 */
typedef enum
{
    IRQ_PRI_NUM0,
    IRQ_PRI_NUM1,
    IRQ_PRI_NUM2,
    IRQ_PRI_NUM3,
} irq_threshold_e;

/**
 * @brief    This function serves to set plic feature.
 * @param[in]   feature - Preemptive priority interrupt feature and the vector mode.
 * @return  none
 */
static _always_inline void plic_set_feature(feature_e feature)
{
    reg_irq_feature = feature; /* set preempt and vector mode */
}

/**
 * @brief    This function serves to enable preemptive priority interrupt feature.
 *              - These three types of interrupts occur simultaneously, they are handled under the following order:M-mode external interrupt(MEI) > M-mode software interrupt(MSI) > M-mode timer interrupt(MTI).
 *              - MEI, MSI and MTI do not occur simultaneously, they can be nested within each other. This function is used to enable interrupt nesting and configure the interrupt nesting priority at which MEI can be interrupted by MSI and MTI.
 *              - The priority of the MEI interrupts is managed by the PLIC and is configured using the plic_set_priority() interface.
 * @param[in]   preempt_pri - MEI, MSI, and MTI interrupt priorities that do not occur simultaneously, configure the interrupt nesting priority at which MEI can be interrupted by MSI and MTI.
 * @return   none
 */
static _always_inline void plic_preempt_feature_en(core_preempt_pri_e preempt_pri)
{
    reg_irq_feature |= FLD_FEATURE_PREEMPT_PRIORITY_INT_EN;
    g_plic_preempt_en = preempt_pri;
}

/**
 * @brief    This function serves to disable preemptive priority interrupt feature.
 * @return  none
 */
static _always_inline void plic_preempt_feature_dis(void)
{
    reg_irq_feature &= (~FLD_FEATURE_PREEMPT_PRIORITY_INT_EN);
    g_plic_preempt_en = 0;
}

/**
 * @brief    This function serves to set plic pending. It provides a way for software to trigger an interrupt without relying on interrupt source from external devices.
 * @param[in]  src - Interrupt source see @ref irq_source_index.
 * @return  none
 */
static _always_inline void plic_set_pending(unsigned int src)
{
    reg_irq_pending(src) = BIT(src % 32);
}

/**
 * @brief    This function serves to set external interrupt priority threshold,only active interrupts with priorities strictly greater than the threshold will cause interrupt, the default threshold value is 0.
 * @param[in]   threshold -  Threshold level.
 * @return  none
 * @note    This interface cannot be called from the interrupt service routine. \n
 *          If this interface is called in an interrupt service routine, the hardware has threshold in-stack and out-stack behaviors, \n
 *          the out-stack overwrites the set threshold value.
 */
static _always_inline void plic_set_threshold(irq_threshold_e threshold)
{
    /*The priority number in the threshold register will be saved to a preempted priority stack and the new priority number of the claimed interrupt will be written to the threshold register.
    when the mcu sends an interrupt completion message to the PLIC (plic_interrupt_complete()), the PLIC will restore(Hardware automatic operation) the highest priority number in the preempted priority stack back to the priority threshold register.
    it is possible that when hardware and software write threshold registers at the same time, there is a risk of software write failure, so turn off the global interrupt before software writes, and resume after writing*/
    unsigned int r    = core_interrupt_disable();
    reg_irq_threshold = threshold;
    fence_iorw; /* Hardware may change this value, fence IO ensures that software changes are valid. */
    core_restore_interrupt(r);
}

/**
 * @brief    This function serves to set external interrupts preemptive priority level. The priority value 0 is reserved to mean "never interrupt".
 * The larger the priority value, the higher the interrupt priority, the default priority value is 1.
 * @param[in]   src - Interrupt source see @ref irq_source_index.
 * @param[in]   priority - Priority level.
 * @return  none
 * @note    This interface cannot be called from the interrupt service routine. \n
 *          If this interface is called in an interrupt service routine, the priority = 0 is changed at this point, and if it is done before the claim, \n
 *          claim accesses the PLIC and gets no value and the interrupt is considered not to have occurred.
 */
static _always_inline void plic_set_priority(unsigned int src, irq_priority_e priority)
{
    reg_irq_src_priority(src) = priority;
}

/**
 * @brief    This function serves to enable plic interrupt source.
 * @param[in]   src - Interrupt source see @ref irq_source_index.
 * @return  none
 * @note    This interface cannot be called from the interrupt service routine.
 */
static _always_inline void plic_interrupt_enable(unsigned int src)
{
    reg_irq_src(src) |= BIT(src % 32);
}

/**
 * @brief    This function serves to disable plic interrupt source.
 * @param[in]   src - Interrupt source see @ref irq_source_index.
 * @return  none
 * @note    This interface cannot be called from the interrupt service routine. \n
 *          If this interface is called in an interrupt service routine, the CPU claims the ID and then closes the interrupt, complete will not be completed and the threshold value will not be updated, \n
 *          all subsequent interrupts of the same priority to be stuck.
 */
static _always_inline void plic_interrupt_disable(unsigned int src)
{
    reg_irq_src(src) &= (~BIT(src % 32));
}

/**
 * @brief    This function serves to send a complete interrupt message(by software) to the gateway to allow a new interrupt request when current interrupt is done.
 * @param[in] src - Interrupt source see @ref irq_source_index.
 * @return  none
 * @note
 *          - plic_interrupt_claim() and plic_interrupt_complete() must be used in pairs.
 */
static _always_inline void plic_interrupt_complete(unsigned int src)
{
    reg_irq_done = src;
}

/**
 * @brief    This function serves to get claimed interrupt id.
 * @return   It returns the claimed interrupt source id see @ref irq_source_index.
 * @note
 *          - For vector interrupt, the hardware will automatically claim an interrupt, in general, the software does not need to claim.
 *          - plic_interrupt_claim() and plic_interrupt_complete() must be used in pairs.
 *          - If the corresponding interrupt has never been enabled, claim does not get the corresponding interrupt ID, and the interface returns 0.
 */
static _always_inline unsigned int plic_interrupt_claim(void)
{
    /**
     *   - Each claim can only claim one IP corresponding to the ID, more than one IP, need to claim multiple times.
     *   - The claim will be successful only after the IP signal reaches the EIP (if IE is closed all the time, the IP will not reach the EIP).
     */
    return reg_irq_done;
}

/**
 * @brief       This function serves to secure code by reconfiguring interrupt threshold or mstatus.MIE to enter the critical section, such as calling some flash interface to enter some function process.
 * @param[in]   preempt_en
 *                - 1 means interrupt priority larger than the given threshold which can disturb function process.
 *                - 0 means it can't be disturbed by interrupt, global interrupt(mstatus.MIE) will be disabled.
 * @param[in]   threshold
 *                - PLIC interrupt threshold. When the interrupt priority is greater than the maximum of the given threshold and the threshold before calling the interface, the function process will be disturbed by interrupt.
 * @return
 *                - When preempt_en = 1 and interrupt nesting is supported, the interrupt threshold before calling the interface is returned.
 *                - Return the value of the mstatus.MIE bit in other cases.
 * @note    plic_enter_critical_sec and plic_exit_critical_sec must be used in pairs.
 */
_attribute_ram_code_sec_noinline_ unsigned int plic_enter_critical_sec(unsigned char preempt_en, unsigned char threshold);

/**
 * @brief    This function serves to restore interrupt threshold or mstatus.MIE to exit the critical section, such as calling some flash interface to exit some function.
 * @param[in]   preempt_en
 *                - 1 means it needs to restore the value of interrupt threshold.
 *                - 0 means it needs to restore mstatus.MIE.It must be the same as the preempt_en value passed by the plic_enter_critical_sec function.
 * @param[in]   r
 *                 - The value of mstatus.MIE or threshold to restore when exit critical section, it must be the value returned by the plic_enter_critical_sec function.
 * @return  none
 */
_attribute_ram_code_sec_noinline_ void plic_exit_critical_sec(unsigned char preempt_en, unsigned int r);

/**
 * @brief       This function serves to execute the interrupt service routine. you can call this function when an interrupt occurs.
 * @param[in]   func - Interrupt service routine.
 * @param[in]   src - Interrupt source see @ref irq_source_index.
 * @return      none
 */
_attribute_ram_code_sec_ void plic_isr(func_isr_t func, unsigned int src);

/**
 * @brief   This function serves to clear all PLIC request When global interrupt is disabled.
 * @return
 *          - 1 indicates that all PLIC interrupt requests were cleared successfully.
 *          - 0 indicates failure to clear all PLIC interrupt requests, failure of interrupt clearing indicates that the interrupt source keeps triggering in one of two ways:
                -# The corresponding interrupt status is not cleared.
                -# The level that triggers the interrupt is always present.
 * @note
 *          - When global interrupt is disabled, the application needs to call this interface to ensure that all PLIC interrupt requests have been processed.
 *          - When global interrupt is enabled, the application does not need to call this interface, the hardware and interrupt service routine handle interrupt requests.
 */
_attribute_ram_code_sec_noinline_ int plic_clr_all_request(void);

/**
 * @brief      This function serves to save and disable all PLIC interrupt sources.
 * @return     none
 * @note       plic_all_interrupt_save_and_disable and plic_all_interrupt_restore must be used in pairs.
 */
void plic_all_interrupt_save_and_disable(void);

/**
 * @brief      This function serves to restore and all PLIC interrupt sources.
 * @return     none
 * @note       plic_all_interrupt_save_and_disable and plic_all_interrupt_restore must be used in pairs.
 */
void plic_all_interrupt_restore(void);

/**
 * @brief      This function serves to save and disable interrupts, including the MIE bit of the MSTATUS register(depends on the first parameter,regardless of whether the global interrupt is enabled or not.), \n
 *             MSIE, MTIE, and MEIE bits of the MIE register, and all PLIC interrupt sources.
 * @param[in]  flag - Global interrupt disable flag, 1: disable, 0: not disable.
 * @param[in]  mie - MSIE, MTIE, and MEIE Which one wakes up WFI.
 * @note
 *  - When the core is awoken by the taken interrupt and global interrupts enable, it will resume and start to execute from the corresponding interrupt service routine.
 *  - When the core is awoken by the pending interrupt and global interrupts disable, it will resume and start to execute from the instruction after the WFI instruction.
 *  - plic_irqs_preprocess_for_wfi and plic_irqs_postprocess_for_wfi must be used in pairs.
 */
void plic_irqs_preprocess_for_wfi(unsigned char flag, mie_e mie);

/**
 * @brief      This function serves to restore interrupts, including the MIE bit of the MSTATUS register, \n
 *             MSIE, MTIE, and MEIE bits of the MIE register, and all PLIC interrupt sources.
 * @return     none
 * @note
 *  - Make sure that the status flag of the corresponding interrupt is cleared before calling this interface.
 *  - This function will enable PLIC interrupt so this interface cannot be called from the interrupt service routine.
 *  - plic_irqs_preprocess_for_wfi and plic_irqs_postprocess_for_wfi must be used in pairs.
 */
void plic_irqs_postprocess_for_wfi(void);

#endif

#endif

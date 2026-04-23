/********************************************************************************************************
 * @file    clic.h
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


/** @page CLIC
 *
 *  Introduction
 *  ===============
 *   The core-local interrupt controller (CLIC)
 *
 *  API Reference
 *  ===============
 *  Header File: clic.h
 */
#ifndef __CLIC_H__
#define __CLIC_H__
#include "hal/mcu_core.h"
#include "reg/clic_reg.h"
#if defined(MCU_CORE_TL752X_N22)

/**
 * @brief Declare the interrupt service routine type.
 */
typedef void (*func_clic_isr_t)(void);

/**
 * @brief The global variable is used to indicate whether interrupt nesting is supported.
 * @note
 *        - To avoid interrupt nesting failures caused by sign extension, the unsigned long type is used here.
 */
extern volatile unsigned long g_clic_preempt_en;
extern volatile unsigned long g_int_dis_cnt;

    /**
 * @defgroup irq_source_index Interrupt source index definition
 * @{
 * @brief Defines the number of each interrupt in the system and its corresponding handler function.
 */
    #define IRQ_MTIMER                  7  /* IRQ_MTIMER machine timer interrupt, - mtime_irq_handler */

    #define IRQ_CPU_DMA                 19 /* CPU_DMA_IRQHandler                    */
    #define IRQ_AUDIO_DMA               20 /* AUDIO_DMA_IRQHandler                  */
    #define IRQ_CPU2_DMA                21 /* CPU2_DMA_IRQHandler                   */
    #define IRQ_IPCM                    22 /* IPCM_IRQHandler                       */
    #define IRQ_CPU1_DMA                23 /* CPU1_DMA_IRQHandler                   */
    #define IRQ_SYSTIMER                24 /* SYSTIMER_IRQHandler                   */
    #define IRQ_TIMER0_0                25 /* TIMER0_0_IRQHandler                   */
    #define IRQ_TIMER0_1                26 /* TIMER0_1_IRQHandler                   */
    #define IRQ_TIMER0_2                27 /* TIMER0_2_IRQHandler                   */
    #define IRQ_TIMER0_3                28 /* TIMER0_3_IRQHandler                   */
    #define IRQ_TIMER1_0                29 /* TIMER1_0_IRQHandler                   */
    #define IRQ_TIMER1_1                30 /* TIMER1_1_IRQHandler                   */
    #define IRQ_TIMER1_2                31 /* TIMER1_2_IRQHandler                   */
    #define IRQ_TIMER1_3                32 /* TIMER1_3_IRQHandler                   */
    #define IRQ_RTC                     33 /* RTC_IRQHandler                        */
    #define IRQ_GPIO                    34 /* GPIO_IRQHandler                       */
    #define IRQ_CPU_WDT                 35 /* CPU_WDT_IRQHandler                    */
    #define IRQ_UART0                   36 /* UART0_IRQHandler                      */
    #define IRQ_UART1                   37 /* UART1_IRQHandler                      */
    #define IRQ_I2C0                    38 /* I2C0_IRQHandler                       */
    #define IRQ_I2C1                    39 /* I2C1_IRQHandler                       */
    #define IRQ_I2C2                    40 /* I2C2_IRQHandler                       */
    #define IRQ_DW_APB_SSI0_S           41 /* DW_APB_SSI0_S_IRQHandler              */
    #define IRQ_DW_APB_SSI0_M           42 /* DW_APB_SSI0_M_IRQHandler              */
    #define IRQ_DWC_SSI_0               43 /* DWC_SSI_0_IRQHandler                  */
    #define IRQ_DWC_SSI_1               44 /* DWC_SSI_1_IRQHandler                  */
    #define IRQ_SDIO                    45 /* SDIO_IRQHandler                       */
    #define IRQ_USB                     46 /* USB_IRQHandler                        */
    #define IRQ_USB1_RESET_250US        47 /* USB1_RESET_250US_IRQHandler           */
    #define IRQ_USB1_EP0_SETUP          48 /* USB1_EP0_SETUP_IRQHandler             */
    #define IRQ_USB1_EP0_DATA           49 /* USB1_EP0_DATA_IRQHandler              */
    #define IRQ_USB1_EP0_STATUS         50 /* USB1_EP0_STATUS_IRQHandler            */
    #define IRQ_USB1_EP0_SETINF_SETADDR 51 /* USB1_EP0_SETINF_SETADDR_IRQHandler    */
    #define IRQ_USB1_EPN_DATA           52 /* USB1_EPN_DATA_IRQHandler              */
    #define IRQ_USB1_SUSPEND            53 /* USB1_SUSPEND_IRQHandler               */

    #define IRQ_RESERVED_36             54 /* RESERVED_36                           */

    #define IRQ_GPADC                   55 /* GPADC_IRQHandler                      */
    #define IRQ_CHG_START               56 /* CHG_START_IRQHandler                  */
    #define IRQ_BT_SYS_BT               57 /* BT_SYS_BT_IRQHandler                  */
    #define IRQ_BT_SYS_BLE              58 /* BT_SYS_BLE_IRQHandler                 */
    #define IRQ_BT_SYS_BT_DM            59 /* BT_SYS_BT_DM_IRQHandler               */
    #define IRQ_BT_SYS_DBM              60 /* BT_SYS_DBM_IRQHandler                 */
    #define IRQ_BT_SYS_BB               61 /* BT_SYS_BB_IRQHandler                  */
    #define IRQ_TAHDT                     62 /* TAHDT_IRQHandler                        */
    #define IRQ_UART2                   63 /* UART2_IRQHandler                      */
    #define IRQ_UART3                   64 /* UART3_IRQHandler                      */
    #define IRQ_TDM0                    65 /* TDM0_IRQHandler                       */
    #define IRQ_TDM1                    66 /* TDM1_IRQHandler                       */
    #define IRQ_TDM2                    67 /* TDM2_IRQHandler                       */
    #define IRQ_TDM3                    68 /* TDM3_IRQHandler                       */
    #define IRQ_PDM0                    69 /* PDM0_IRQHandler                       */
    #define IRQ_PDM1                    70 /* PDM1_IRQHandler                       */
    #define IRQ_PDMC                    71 /* PDMC_IRQHandler                       */
    #define IRQ_AUDIO_CODEC             72 /* AUDIO_CODEC_IRQHandler                */
    #define IRQ_SPDIF                   73 /* SPDIF_IRQHandler                      */
    #define IRQ_RESAMPLE                74 /* RESAMPLE_IRQHandler                   */
    #define IRQ_OSR_TRNG                75 /* OSR_TRNG_IRQHandler                   */
    #define IRQ_EFUSE                   76 /* EFUSE_IRQHandler                      */
    #define IRQ_UART4                   77 /* UART4_IRQHandler                      */
    /**
 * @}
 */

    /**
 * @brief This macro generates a unique name for an interrupt service routine (ISR) entry point based on the input parameter. \n
 * The generated name is in the form "entry_irq" followed by the value of "irq_num". \n
 * For example, ISR_ENTRY_NAME(19) means entry_irq19.
 * @param[in] irq_num - The number of the interrupt see @ref irq_source_index.
 */
    #define ISR_ENTRY_NAME(irq_num) entry_irq##irq_num

    /**
 * @brief Interrupt service routine register, this macro defines an entry_irq function based on irq_num. \n
 *        The machine attribute was added to the interrupt function, and the compiler saw that it would insert code that modified the protection register, for example:
 *        @code {.c}
 *           _attribute_ram_code_sec_noinline_ entry_irq19(void) __attribute__ ((interrupt ("machine") , aligned(4)));
 *        @endcode
 * @param[in] isr - Interrupt service routine pointer.
 * @param[in] irq_num - The number of the interrupt see @ref irq_source_index.
 * @note
 *      - The same interruption number can only be registered once.
 *      - The code in the interrupt service handler should be as simple as possible, and if you can do it without function calls, you can reduce the number of registers on the stack, \n
 *        thus reducing the code size and speeding up the interrupt response.
 */

    #define CLIC_ISR_REGISTER(isr, irq_num)                                                                                     \
        _attribute_ram_code_sec_noinline_ void ISR_ENTRY_NAME(irq_num)(void) __attribute__((interrupt("machine"), aligned(4))); \
        void                                   ISR_ENTRY_NAME(irq_num)(void)                                                    \
        {                                                                                                                       \
            clic_isr(isr);                                                                                                      \
        }

/**
 * @brief Interrupt source level. The larger the value, the higher the level. After the reset the default level value is 0.
 * @note
 *        - An interrupt occurs only when level is greater than threshold.
 *        - The clic_init function sets the level of all interrupts to 1.
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
 * @brief   This function serves to init CLIC.
 * @return  none
 * @note
 *          - The default value of irq level is set to 1 for all interrupts.
 */
void clic_init(void);

/**
 * @brief      This function serves to select vector mode for the associated interrupt.
 * @param[in]  src - Interrupt source see @ref irq_source_index.
 * @return     none
 * @note       In vector mode, the interrupt service routine needs to be registered with CLIC_ISR_REGISTER().
 */
static inline void clic_interrupt_vector_en(unsigned int src)
{
    BM_SET(reg_clic_attribute(src), FLD_CLIC_SHV);
}

/**
 * @brief      This function serves to set CLIC pending. It provides a way for software to trigger an interrupt without relying on interrupt source from external devices.
 * @param[in]  src - Interrupt source see @ref irq_source_index.
 * @return     none
 */
static inline void clic_set_pending(unsigned int src)
{
    reg_clic_pending(src) = 1;
}

/**
 * @brief      This function serves to enable CLIC interrupt source.
 * @param[in]  src - Interrupt source see @ref irq_source_index.
 * @return     none
 */
static inline void clic_interrupt_enable(unsigned int src)
{
    reg_clic_src(src) = 1;
}

/**
 * @brief      This function serves to disable CLIC interrupt source.
 * @param[in]  src - Interrupt source see @ref irq_source_index.
 * @return     none
 */
static inline void clic_interrupt_disable(unsigned int src)
{
    reg_clic_src(src) = 0;
}

/**
 * @brief       This function serves to set external interrupts preemptive priority level. The priority value 0 is reserved to mean never interrupt.\n
 *              The larger the priority value, the higher the interrupt priority, the default priority value is set to 1 by the software.
 * @param[in]   src      - Interrupt source see @ref irq_source_index.
 * @param[in]   priority - Priority level.
 * @return      none
 */
static inline void clic_set_priority(unsigned int src, irq_priority_e priority)
{
    reg_clic_input_ctl(src) = (reg_clic_input_ctl(src) & (~FLD_CLIC_LEVEL)) | MASK_VAL(FLD_CLIC_LEVEL, priority);
}

/**
 * @brief      This function serves to set priority threshold, only active interrupts with interrupt levels(clic_set_priority()) strictly greater than the threshold will cause interrupt.
 * @param[in]  threshold -  Threshold level.
 * @return     none
 */
static inline void clic_set_threshold(irq_threshold_e threshold)
{
    reg_clic_mth = (reg_clic_mth & (~FLD_CLIC_MTH)) | MASK_VAL(FLD_CLIC_MTH, threshold);
}

/**
 * @brief    This function serves to enable preemptive priority interrupt feature.
 * @return   none
 */
static inline void clic_preempt_feature_en(void)
{
    g_clic_preempt_en = 1;
}

/**
 * @brief    This function serves to disable preemptive priority interrupt feature.
 * @return   none
 */
static inline void clic_preempt_feature_dis(void)
{
    g_clic_preempt_en = 0;
}

/**
 * @brief       This function serves to execute the interrupt service routine, you can call this function when an interrupt occurs.
 * @param[in]   func - Interrupt service routine.
 * @return      none
 */
_attribute_ram_code_sec_ void clic_isr(func_clic_isr_t func);

/**
 * @brief      This function serves to disable all CLIC interrupt sources.
 * @return     none
 * @note       none
 */
_attribute_ram_code_sec_optimize_o2_noinline_ void clic_all_interrupt_disable(void);
#endif

#endif

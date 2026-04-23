/*******************************************************************************************************
 *
 * @file    rtc.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//RTC_CCVR offsetaddress : 0x0
#define RTC_CURRENT_COUNTER_VALUE_POS (0U)
#define RTC_CURRENT_COUNTER_VALUE_MSK \
    (0xFFFFFFFFUL                     \
     << RTC_CURRENT_COUNTER_VALUE_POS) /*!< When read, this register is the current value of the internal counter. This value is always read coherently. Bits from RTC_CNT_WIDTH to 31 are read as 0 when RTC_CNT_WIDTH is less than 31. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: RTC_CNT_WIDTH - 1*/
#define RTC_CURRENT_COUNTER_VALUE      RTC_CURRENT_COUNTER_VALUE_MSK
#define RTC_CURRENT_COUNTER_VALUE_W(X) ((X) << RTC_CURRENT_COUNTER_VALUE_POS)

//RTC_CMR offsetaddress : 0x4
#define RTC_COUNTER_MATCH_POS (0U)
#define RTC_COUNTER_MATCH_MSK \
    (0xFFFFFFFFUL             \
     << RTC_COUNTER_MATCH_POS) /*!< Interrupt Match Register. When the internal counter matches this register, an interrupt is generated, provided interrupt generation is enabled. When appropriate, this value is written coherently. Only when all the bytes are written is the register used by the interrupt detection logic. Bits from RTC_CNT_WIDTH and above are read and written as 0 when RTC_CNT_WIDTH is less than 31. Reset Value: 0x0 Exists: Always Range Variable[x]: RTC_CNT_WIDTH - 1*/
#define RTC_COUNTER_MATCH      RTC_COUNTER_MATCH_MSK
#define RTC_COUNTER_MATCH_W(X) ((X) << RTC_COUNTER_MATCH_POS)

//RTC_CLR offsetaddress : 0x8
#define RTC_COUNTER_LOAD_POS (0U)
#define RTC_COUNTER_LOAD_MSK \
    (0xFFFFFFFFUL << RTC_COUNTER_LOAD_POS) /*!< Loaded into the counter as the loaded value, which is written coherently. Bits from RTC_CNT_WIDTH and above are read and written as 0 when RTC_CNT_WIDTH is less than 31. Reset Value: 0x0 Exists: Always Range Variable[x]: RTC_CNT_WIDTH - 1*/
#define RTC_COUNTER_LOAD      RTC_COUNTER_LOAD_MSK
#define RTC_COUNTER_LOAD_W(X) ((X) << RTC_COUNTER_LOAD_POS)

//RTC_CCR offsetaddress : 0xc
#define RTC_RTC_IEN_POS   (0U)
#define RTC_RTC_IEN_MSK   (0x1UL << RTC_RTC_IEN_POS) /*!< Allows the user to disable interrupt generation. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disables the interrupt generation ■ 0x1 (ENABLED): Enables the interrupt generation Exists: Always*/
#define RTC_RTC_IEN       RTC_RTC_IEN_MSK
#define RTC_RTC_IEN_W(X)  ((X) << RTC_RTC_IEN_POS)
#define RTC_RTC_MASK_POS  (1U)
#define RTC_RTC_MASK_MSK  (0x1UL << RTC_RTC_MASK_POS) /*!< Allows the user to mask interrupt generation. Reset Value: 0x0 Values: ■ 0x0 (UNMASKED): Interrupt unmasked ■ 0x1 (MASKED): Interrupt masked Exists: Always*/
#define RTC_RTC_MASK      RTC_RTC_MASK_MSK
#define RTC_RTC_MASK_W(X) ((X) << RTC_RTC_MASK_POS)
#define RTC_RTC_EN_POS    (2U)
#define RTC_RTC_EN_MSK \
    (0x1UL             \
     << RTC_RTC_EN_POS) /*!< Optional. Allows the user to control counting in the counter. This bit does not exist if RTC_EN_MODE = 0. Internally, the counter is always enabled. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disables the counter ■ 0x1 (ENABLED): Enables the counter Exists: Always*/
#define RTC_RTC_EN      RTC_RTC_EN_MSK
#define RTC_RTC_EN_W(X) ((X) << RTC_RTC_EN_POS)
#define RTC_RTC_WEN_POS (3U)
#define RTC_RTC_WEN_MSK \
    (0x1UL              \
     << RTC_RTC_WEN_POS) /*!< Optional. Allows the user to force the counter to wrap when a match occurs instead of waiting until the maximum count is reached. 0 = Wrap disabled, 1 = Wrap enabled, This bit is writable only when RTC_WRAP_MODE = 1 Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disables the WRAP ■ 0x1 (ENABLED): Enables the WRAP Exists: Always Memory Access: "(RTC_WRAP_MODE==1) ? \"read- write\" : \"read-only\""*/
#define RTC_RTC_WEN             RTC_RTC_WEN_MSK
#define RTC_RTC_WEN_W(X)        ((X) << RTC_RTC_WEN_POS)
#define RTC_RTC_PSCLR_EN_POS    (4U)
#define RTC_RTC_PSCLR_EN_MSK    (0x1UL << RTC_RTC_PSCLR_EN_POS) /*!< Optional. Allows user to control the usage of RTC Prescaler feature. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disables the Prescaler counter ■ 0x1 (ENABLED): Enables the Prescaler counter Exists: Always*/
#define RTC_RTC_PSCLR_EN        RTC_RTC_PSCLR_EN_MSK
#define RTC_RTC_PSCLR_EN_W(X)   ((X) << RTC_RTC_PSCLR_EN_POS)
#define RTC_RTC_PROT_LEVEL_POS  (5U)
#define RTC_RTC_PROT_LEVEL_MSK  (0x7UL << RTC_RTC_PROT_LEVEL_POS) /*!< This field holds the protection level value of DW_apb_rtc. Reset Value: PROT_LEVEL_RST Exists: (SLVERR_RESP_EN==1)*/
#define RTC_RTC_PROT_LEVEL      RTC_RTC_PROT_LEVEL_MSK
#define RTC_RTC_PROT_LEVEL_W(X) ((X) << RTC_RTC_PROT_LEVEL_POS)
#define RTC_RSVD_CCR_POS        (8U)
#define RTC_RSVD_CCR_MSK        (0xffffffUL << RTC_RSVD_CCR_POS) /*!< RTC_CCR 31to8 Reserved and read as 0. Exists: Always*/
#define RTC_RSVD_CCR            RTC_RSVD_CCR_MSK
#define RTC_RSVD_CCR_W(X)       ((X) << RTC_RSVD_CCR_POS)

//RTC_STAT offsetaddress : 0x10
#define RTC_RTC_STAT_POS       (0U)
#define RTC_RTC_STAT_MSK       (0x1UL << RTC_RTC_STAT_POS) /*!< This register is the masked raw status. Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): Interrupt is inactive ■ 0x1 (ACTIVE): Interrupt is active (regardless of polarity) Exists: Always Volatile: true*/
#define RTC_RTC_STAT           RTC_RTC_STAT_MSK
#define RTC_RTC_STAT_W(X)      ((X) << RTC_RTC_STAT_POS)
#define RTC_RSVD_RTC_STAT_POS  (1U)
#define RTC_RSVD_RTC_STAT_MSK  (0x7fffffffUL << RTC_RSVD_RTC_STAT_POS) /*!< RTC_STAT 31to1 Reserved and read as 0. Exists: Always Volatile: true*/
#define RTC_RSVD_RTC_STAT      RTC_RSVD_RTC_STAT_MSK
#define RTC_RSVD_RTC_STAT_W(X) ((X) << RTC_RSVD_RTC_STAT_POS)

//RTC_RSTAT offsetaddress : 0x14
#define RTC_RTC_RSTAT_POS       (0U)
#define RTC_RTC_RSTAT_MSK       (0x1UL << RTC_RTC_RSTAT_POS) /*!< Raw Status Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): Interrupt is inactive ■ 0x1 (ACTIVE): Interrupt is active (regardless of polarity) Exists: Always Volatile: true*/
#define RTC_RTC_RSTAT           RTC_RTC_RSTAT_MSK
#define RTC_RTC_RSTAT_W(X)      ((X) << RTC_RTC_RSTAT_POS)
#define RTC_RSVD_RTC_RSTAT_POS  (1U)
#define RTC_RSVD_RTC_RSTAT_MSK  (0x7fffffffUL << RTC_RSVD_RTC_RSTAT_POS) /*!< RTC_RSTAT 31to1 Reserved and read as 0. Exists: Always Volatile: true*/
#define RTC_RSVD_RTC_RSTAT      RTC_RSVD_RTC_RSTAT_MSK
#define RTC_RSVD_RTC_RSTAT_W(X) ((X) << RTC_RSVD_RTC_RSTAT_POS)

//RTC_EOI offsetaddress : 0x18
#define RTC_RTC_EOI_POS       (0U)
#define RTC_RTC_EOI_MSK       (0x1UL << RTC_RTC_EOI_POS) /*!< By reading this location, the match interrupt is cleared. Performing read-to-clear on interrupt, the interrupt is cleared at the end of the read. Reset Value: 0x0 Exists: Always*/
#define RTC_RTC_EOI           RTC_RTC_EOI_MSK
#define RTC_RTC_EOI_W(X)      ((X) << RTC_RTC_EOI_POS)
#define RTC_RSVD_RTC_EOI_POS  (1U)
#define RTC_RSVD_RTC_EOI_MSK  (0x7fffffffUL << RTC_RSVD_RTC_EOI_POS) /*!< RTC_EOI 31to1 Reserved and read as 0. Exists: Always*/
#define RTC_RSVD_RTC_EOI      RTC_RSVD_RTC_EOI_MSK
#define RTC_RSVD_RTC_EOI_W(X) ((X) << RTC_RSVD_RTC_EOI_POS)

//RTC_COMP_VERSION offsetaddress : 0x1c
#define RTC_RTC_COMP_VERSION_POS  (0U)
#define RTC_RTC_COMP_VERSION_MSK  (0xffffffffUL << RTC_RTC_COMP_VERSION_POS) /*!< ASCII value for each number in the version, followed by *. For example, 32_30_31_2A represents the version 2.01*. Reset Value: See the Releases table in the DW_apb_rtc Release Notes. Exists: Always*/
#define RTC_RTC_COMP_VERSION      RTC_RTC_COMP_VERSION_MSK
#define RTC_RTC_COMP_VERSION_W(X) ((X) << RTC_RTC_COMP_VERSION_POS)

//RTC_CPSR offsetaddress : 0x20
#define RTC_COUNTER_PRESCALER_VALUE_POS (0U)
#define RTC_COUNTER_PRESCALER_VALUE_MSK \
    (0x1UL                              \
     << RTC_COUNTER_PRESCALER_VALUE_POS) /*!< Counter Prescaler Register. The RTC counter will be updating at the rate of rtc_clk, rtc_clk_en, or pclk based on the configuration. This register is used to prescale the rate at which the RTC counter updates. When appropriate, this register is written coherently. Only when all the bytes are written, the register used by the prescaler counter logic. Reset Value: RTC_PRESCLR_VAL Exists: Always Range Variable[x]: RTC_PRESCLR_WIDTH - 1*/
#define RTC_COUNTER_PRESCALER_VALUE      RTC_COUNTER_PRESCALER_VALUE_MSK
#define RTC_COUNTER_PRESCALER_VALUE_W(X) ((X) << RTC_COUNTER_PRESCALER_VALUE_POS)
#define RTC_RSVD_CPSR_POS                (32U)
#define RTC_RSVD_CPSR_MSK                (0x1UL << RTC_RSVD_CPSR_POS) /*!< RTC_CPSR 31toRTC_PRESCLR_WIDTH Reserved bits - Read Only Exists: Always Range Variable[y]: RTC_PRESCLR_WIDTH*/
#define RTC_RSVD_CPSR                    RTC_RSVD_CPSR_MSK
#define RTC_RSVD_CPSR_W(X)               ((X) << RTC_RSVD_CPSR_POS)

//RTC_CPCVR offsetaddress : 0x24
#define RTC_CURRENT_PRESCALER_COUNTER_VALUE_POS (0U)
#define RTC_CURRENT_PRESCALER_COUNTER_VALUE_MSK \
    (0xFFFFFFFFUL                               \
     << RTC_CURRENT_PRESCALER_COUNTER_VALUE_POS) /*!< When read, this register provides the current value of the internal prescaler counter. This value always is read coherently. Bits from RTC_PRESCLR_WIDTH to 31 are read as 0 when RTC_PRESCLR_WIDTH is less than 31. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: RTC_PRESCLR_WIDTH - 1*/
#define RTC_CURRENT_PRESCALER_COUNTER_VALUE      RTC_CURRENT_PRESCALER_COUNTER_VALUE_MSK
#define RTC_CURRENT_PRESCALER_COUNTER_VALUE_W(X) ((X) << RTC_CURRENT_PRESCALER_COUNTER_VALUE_POS)

typedef struct {
    volatile uint32_t CCVR;         //offsetaddress : 0x0
    volatile uint32_t CMR;          //offsetaddress : 0x4
    volatile uint32_t CLR;          //offsetaddress : 0x8
    volatile uint32_t CCR;          //offsetaddress : 0xc
    volatile uint32_t STAT;         //offsetaddress : 0x10
    volatile uint32_t RSTAT;        //offsetaddress : 0x14
    volatile uint32_t EOI;          //offsetaddress : 0x18
    volatile uint32_t COMP_VERSION; //offsetaddress : 0x1c
    volatile uint32_t CPSR;         //offsetaddress : 0x20
    volatile uint32_t CPCVR;        //offsetaddress : 0x24
} rtc_reg_t;
#ifdef __cplusplus
}
#endif
#endif
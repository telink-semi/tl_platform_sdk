/*******************************************************************************************************
 *
 * @file    gpio.h
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
#ifndef __GPIO_H__
#define __GPIO_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

//GPIO_SWPORTA_DR offsetaddress : 0x0
#define GPIO_GPIO_SWPORTA_DR_POS (255U)
#define GPIO_GPIO_SWPORTA_DR_MSK \
    (0x1UL                       \
     << GPIO_GPIO_SWPORTA_DR_POS) /*!< Values written to this register are output on the I/O signals for Port A if the corresponding data direction bits for Port A are set to Output mode and the corresponding control bit for Port A is set to Software mode. The value read back is equal to the last value written to this register. Reset Value: GPIO_SWPORTA_RESET Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_SWPORTA_DR          GPIO_GPIO_SWPORTA_DR_MSK
#define GPIO_RSVD_GPIO_SWPORTA_DR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTA_DR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTA_DR_POS) /*!< RSVD_GPIO_SWPORTA_DR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_SWPORTA_DR     GPIO_RSVD_GPIO_SWPORTA_DR_MSK

//GPIO_SWPORTA_DDR offsetaddress : 0x4
#define GPIO_GPIO_SWPORTA_DDR_POS (255U)
#define GPIO_GPIO_SWPORTA_DDR_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTA_DDR_POS) /*!< Values written to this register independently control the direction of the corresponding data bit in Port A. The default direction can be configured as input or output after system reset through the GPIO_DFLT_DIR_A parameter. Values: ■ 0x0 (IN): Input Direction ■ 0x1 (OUT): Output Direction Value After Reset: {(GPIO_DFLT_DIR_A==1) ? (pow (2, GPIO_PWIDTH_A))-1 : 0} Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_SWPORTA_DDR          GPIO_GPIO_SWPORTA_DDR_MSK
#define GPIO_RSVD_GPIO_SWPORTA_DDR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTA_DDR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTA_DDR_POS) /*!< RSVD_GPIO_SWPORTA_DDR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_SWPORTA_DDR     GPIO_RSVD_GPIO_SWPORTA_DDR_MSK

//GPIO_SWPORTA_CTL offsetaddress : 0x8
#define GPIO_GPIO_SWPORTA_CTL_POS (255U)
#define GPIO_GPIO_SWPORTA_CTL_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTA_CTL_POS) /*!< The data and control source for a signal can come from either software or hardware; this bit selects between them. The default source is configurable through the GPIO_DFLT_DIR_A configuration parameter. If GPIO_PORTA_SINGLE_CTL = 0, the register will contain one bit for each bit of the signal. Upon reset in this case, the value of GPIO_DFLT_SRC_A is replicated across all bits of the signal so that all bits power up with the same operating mode. Furthermore, the default source of each bit of the signal can subsequently be changed by writing to the corresponding bit of this register. This register is not available unless GPIO_HW_PORTA = 1. Reset Value: If GPIO_PORTA_SINGLE_CTL = 1, then the reset value is GPIO_DFLT_SRC_A. If GPIO_PORTA_SINGLE_CTL = 0, then the reset value is {GPIO_PWIDTH_A{GPIO_DFLT_SRC_A in each bit}}. Values: ■ 0x0 (SOFTWARE): Software Mode ■ 0x1 (HARDWARE): Hardware Mode Exists: Always Range Variable[x]: GPIO_SWPORTA_CTL_REG_SIZE - 1*/
#define GPIO_GPIO_SWPORTA_CTL          GPIO_GPIO_SWPORTA_CTL_MSK
#define GPIO_RSVD_GPIO_SWPORTA_CTL_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTA_CTL_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTA_CTL_POS) /*!< RSVD_GPIO_SWPORTA_CTL Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_SWPORTA_CTL_REG_SIZE*/
#define GPIO_RSVD_GPIO_SWPORTA_CTL     GPIO_RSVD_GPIO_SWPORTA_CTL_MSK

//GPIO_SWPORTB_DR offsetaddress : 0xc
#define GPIO_GPIO_SWPORTB_DR_POS (255U)
#define GPIO_GPIO_SWPORTB_DR_MSK \
    (0x1UL                       \
     << GPIO_GPIO_SWPORTB_DR_POS) /*!< Values written to this register are output on the I/O signals for Port B if the corresponding data direction bits for Port B are set to Output mode and the corresponding control bit for Port B is set to Software mode. The value read back is equal to the last value written to this register. Reset Value: GPIO_ SWPORTB_ RESET Exists: Always Range Variable[x]: GPIO_PWIDTH_B - 1*/
#define GPIO_GPIO_SWPORTB_DR          GPIO_GPIO_SWPORTB_DR_MSK
#define GPIO_RSVD_GPIO_SWPORTB_DR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTB_DR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTB_DR_POS) /*!< RSVD_GPIO_SWPORTB_DR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_B*/
#define GPIO_RSVD_GPIO_SWPORTB_DR     GPIO_RSVD_GPIO_SWPORTB_DR_MSK

//GPIO_SWPORTB_DDR offsetaddress : 0x10
#define GPIO_GPIO_SWPORTB_DDR_POS (255U)
#define GPIO_GPIO_SWPORTB_DDR_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTB_DDR_POS) /*!< Values written to this register independently control the direction of the corresponding data bit in Port B. The default direction can be configured as input or output after system reset through the GPIO_DFLT_DIR_B parameter. Values: ■ 0x0 (IN): Input Direction (default) ■ 0x1 (OUT): Output Direction Value After Reset: {(GPIO_DFLT_DIR_B==1) ? (pow (2, GPIO_PWIDTH_B))-1 : 0} Exists: Always Range Variable[x]: GPIO_PWIDTH_B - 1*/
#define GPIO_GPIO_SWPORTB_DDR          GPIO_GPIO_SWPORTB_DDR_MSK
#define GPIO_RSVD_GPIO_SWPORTB_DDR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTB_DDR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTB_DDR_POS) /*!< RSVD_GPIO_SWPORTB_DDR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_B*/
#define GPIO_RSVD_GPIO_SWPORTB_DDR     GPIO_RSVD_GPIO_SWPORTB_DDR_MSK

//GPIO_SWPORTB_CTL offsetaddress : 0x14
#define GPIO_GPIO_SWPORTB_CTL_POS (255U)
#define GPIO_GPIO_SWPORTB_CTL_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTB_CTL_POS) /*!< The data and control source for a signal can come from either software or hardware; this bit selects between them. The default source is configurable through the GPIO_DFLT_DIR_B configuration parameter. If GPIO_PORTB_SINGLE_CTL = 0, the register will contain one bit for each bit of the signal. Upon reset in this case, the value of GPIO_DFLT_SRC_B is replicated across all bits of the signal so that all bits power up with the same operating mode. Furthermore, the default source of each bit of the signal can subsequently be changed by writing to the corresponding bit of this register. This register is not available unless GPIO_HW_PORTB = 1. Reset Value: If GPIO_PORTB_SINGLE_CTL = 1, then the reset value is GPIO_DFLT_SRC_B. If GPIO_PORTB_SINGLE_CTL = 0, then the reset value is {GPIO_PWIDTH_B{GPIO_DFLT_SRC_B in each bit}}. Values: ■ 0x0 (SOFTWARE): Software Mode (default) ■ 0x1 (HARDWARE): Hardware Mode Exists: Always Range Variable[x]: GPIO_SWPORTB_CTL_REG_SIZE - 1*/
#define GPIO_GPIO_SWPORTB_CTL          GPIO_GPIO_SWPORTB_CTL_MSK
#define GPIO_RSVD_GPIO_SWPORTB_CTL_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTB_CTL_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTB_CTL_POS) /*!< RSVD_GPIO_SWPORTB_CTL Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_SWPORTB_CTL_REG_SIZE*/
#define GPIO_RSVD_GPIO_SWPORTB_CTL     GPIO_RSVD_GPIO_SWPORTB_CTL_MSK

//GPIO_SWPORTC_DR offsetaddress : 0x18
#define GPIO_GPIO_SWPORTC_DR_POS (255U)
#define GPIO_GPIO_SWPORTC_DR_MSK \
    (0x1UL                       \
     << GPIO_GPIO_SWPORTC_DR_POS) /*!< Values written to this register are output on the I/O signals for Port C if the corresponding data direction bits for Port C are set to Output mode and the corresponding control bit for Port C is set to Software mode. The value read back is equal to the last value written to this register. Reset Value: GPIO_SWPORTC_RESET Exists: Always Range Variable[x]: GPIO_PWIDTH_C - 1*/
#define GPIO_GPIO_SWPORTC_DR          GPIO_GPIO_SWPORTC_DR_MSK
#define GPIO_RSVD_GPIO_SWPORTC_DR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTC_DR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTC_DR_POS) /*!< RSVD_GPIO_SWPORTC_DR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_C*/
#define GPIO_RSVD_GPIO_SWPORTC_DR     GPIO_RSVD_GPIO_SWPORTC_DR_MSK

//GPIO_SWPORTC_DDR offsetaddress : 0x1c
#define GPIO_GPIO_SWPORTC_DDR_POS (255U)
#define GPIO_GPIO_SWPORTC_DDR_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTC_DDR_POS) /*!< Values written to this register independently control the direction of the corresponding data bit in Port C. The default direction can be configured as input or output after system reset through the GPIO_DFLT_DIR_C parameter. Values: ■ 0x0 (IN): Input Direction (default) ■ 0x1 (OUT): Output Direction Value After Reset: {(GPIO_DFLT_DIR_C==1) ? (pow (2, GPIO_PWIDTH_C))-1 : 0} Exists: Always Range Variable[x]: GPIO_PWIDTH_C - 1*/
#define GPIO_GPIO_SWPORTC_DDR          GPIO_GPIO_SWPORTC_DDR_MSK
#define GPIO_RSVD_GPIO_SWPORTC_DDR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTC_DDR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTC_DDR_POS) /*!< RSVD_GPIO_SWPORTC_DDR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_C*/
#define GPIO_RSVD_GPIO_SWPORTC_DDR     GPIO_RSVD_GPIO_SWPORTC_DDR_MSK

//GPIO_SWPORTC_CTL offsetaddress : 0x20
#define GPIO_GPIO_SWPORTC_CTL_POS (255U)
#define GPIO_GPIO_SWPORTC_CTL_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTC_CTL_POS) /*!< The data and control source for a signal can come from either software or hardware; this bit selects between them. The default source is configurable through the GPIO_DFLT_DIR_C configuration parameter. If GPIO_PORTC_SINGLE_CTL = 0, the register will contain one bit for each bit of the signal. Upon reset in this case, the value of GPIO_DFLT_SRC_C is replicated across all bits of the signal so that all bits power up with the same operating mode. Furthermore, the default source of each bit of the signal can subsequently be changed by writing to the corresponding bit of this register. This register is not available unless GPIO_HW_PORTC = 1. Reset Value: If GPIO_PORTC_SINGLE_CTL = 1, then the reset value is GPIO_DFLT_SRC_C. If GPIO_PORTC_SINGLE_CTL = 0, then the reset value is {GPIO_PWIDTH_C{GPIO_DFLT_SRC_C in each bit}}. Values: ■ 0x0 (SOFTWARE): Software Mode (default) ■ 0x1 (HARDWARE): Hardware Mode Exists: Always Range Variable[x]: GPIO_SWPORTC_CTL_REG_SIZE - 1*/
#define GPIO_GPIO_SWPORTC_CTL          GPIO_GPIO_SWPORTC_CTL_MSK
#define GPIO_RSVD_GPIO_SWPORTC_CTL_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTC_CTL_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTC_CTL_POS) /*!< RSVD_GPIO_SWPORTC_CTL Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_SWPORTC_CTL_REG_SIZE*/
#define GPIO_RSVD_GPIO_SWPORTC_CTL     GPIO_RSVD_GPIO_SWPORTC_CTL_MSK

//GPIO_SWPORTD_DR offsetaddress : 0x24
#define GPIO_GPIO_SWPORTD_DR_POS (255U)
#define GPIO_GPIO_SWPORTD_DR_MSK \
    (0x1UL                       \
     << GPIO_GPIO_SWPORTD_DR_POS) /*!< Values written to this register are output on the I/O signals for Port D if the corresponding data direction bits for Port D are set to Output mode and the corresponding control bit for Port D is set to Software mode. The value read back is equal to the last value written to this register. Reset Value: GPIO_SWPORTD_RESET Exists: Always Range Variable[x]: GPIO_PWIDTH_D - 1*/
#define GPIO_GPIO_SWPORTD_DR          GPIO_GPIO_SWPORTD_DR_MSK
#define GPIO_RSVD_GPIO_SWPORTD_DR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTD_DR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTD_DR_POS) /*!< RSVD_GPIO_SWPORTD_DR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_D*/
#define GPIO_RSVD_GPIO_SWPORTD_DR     GPIO_RSVD_GPIO_SWPORTD_DR_MSK

//GPIO_SWPORTD_DDR offsetaddress : 0x28
#define GPIO_GPIO_SWPORTD_DDR_POS (255U)
#define GPIO_GPIO_SWPORTD_DDR_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTD_DDR_POS) /*!< Values written to this register independently control the direction of the corresponding data bit in Port D. The default direction can be configured as input or output after system reset through the GPIO_DFLT_DIR_D parameter. Values: ■ 0x0 (IN): Input Direction (default) ■ 0x1 (OUT): Output Direction Value After Reset: {(GPIO_DFLT_DIR_D==1) ? (pow (2, GPIO_PWIDTH_D))-1 : 0} Exists: Always Range Variable[x]: GPIO_PWIDTH_D - 1*/
#define GPIO_GPIO_SWPORTD_DDR          GPIO_GPIO_SWPORTD_DDR_MSK
#define GPIO_RSVD_GPIO_SWPORTD_DDR_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTD_DDR_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTD_DDR_POS) /*!< RSVD_GPIO_SWPORTD_DDR Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_D*/
#define GPIO_RSVD_GPIO_SWPORTD_DDR     GPIO_RSVD_GPIO_SWPORTD_DDR_MSK

//GPIO_SWPORTD_CTL offsetaddress : 0x2c
#define GPIO_GPIO_SWPORTD_CTL_POS (255U)
#define GPIO_GPIO_SWPORTD_CTL_MSK \
    (0x1UL                        \
     << GPIO_GPIO_SWPORTD_CTL_POS) /*!< The data and control source for a signal can come from either software or hardware; this bit selects between them. The default source is configurable through the GPIO_DFLT_DIR_D configuration parameter. If GPIO_PORTD_SINGLE_CTL = 0, the register will contain one bit for each bit of the signal. Upon reset in this case, the value of GPIO_DFLT_SRC_D is replicated across all bits of the signal so that all bits power up with the same operating mode. Furthermore, the default source of each bit of the signal can subsequently be changed by writing to the corresponding bit of this register. This register is not available unless GPIO_HW_PORTD = 1. Reset Value: If GPIO_PORTD_SINGLE_CTL = 1, then the reset value is GPIO_DFLT_SRC_D. If GPIO_PORTD_SINGLE_CTL = 0, then the reset value is {GPIO_PWIDTH_D{GPIO_DFLT_SRC_D in each bit}}. Values: ■ 0x0 (SOFTWARE): Software Mode (default) ■ 0x1 (HARDWARE): Hardware Mode Exists: Always Range Variable[x]: GPIO_SWPORTD_CTL_REG_SIZE - 1*/
#define GPIO_GPIO_SWPORTD_CTL          GPIO_GPIO_SWPORTD_CTL_MSK
#define GPIO_RSVD_GPIO_SWPORTD_CTL_POS (255U)
#define GPIO_RSVD_GPIO_SWPORTD_CTL_MSK (0x1UL << GPIO_RSVD_GPIO_SWPORTD_CTL_POS) /*!< RSVD_GPIO_SWPORTD_CTL Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_SWPORTD_CTL_REG_SIZE*/
#define GPIO_RSVD_GPIO_SWPORTD_CTL     GPIO_RSVD_GPIO_SWPORTD_CTL_MSK

//GPIO_INTEN offsetaddress : 0x30
#define GPIO_GPIO_INTEN_POS (255U)
#define GPIO_GPIO_INTEN_MSK \
    (0x1UL                  \
     << GPIO_GPIO_INTEN_POS) /*!< Allows each bit of Port A to be configured for interrupts. By default the generation of interrupts is disabled. Whenever a 1 is written to a bit of this register, it configures the corresponding bit on Port A to become an interrupt; otherwise, Port A operates as a normal GPIO signal. Interrupts are disabled on the corresponding bits of Port A if the corresponding data direction register is set to Output or if Port A mode is set to Hardware. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Interrupt is disabled ■ 0x1 (ENABLED): Interrupt is enabled Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INTEN          GPIO_GPIO_INTEN_MSK
#define GPIO_RSVD_GPIO_INTEN_POS (255U)
#define GPIO_RSVD_GPIO_INTEN_MSK (0x1UL << GPIO_RSVD_GPIO_INTEN_POS) /*!< RSVD_GPIO_INTEN Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INTEN     GPIO_RSVD_GPIO_INTEN_MSK

//GPIO_INTMASK offsetaddress : 0x34
#define GPIO_GPIO_INTMASK_POS (255U)
#define GPIO_GPIO_INTMASK_MSK \
    (0x1UL                    \
     << GPIO_GPIO_INTMASK_POS) /*!< Controls whether an interrupt on Port A can create an interrupt for the interrupt controller by not masking it. By default, all interrupts bits are unmasked. Whenever a 1 is written to a bit in this register, it masks the interrupt generation capability for this signal; otherwise interrupts are allowed through. The unmasked status can be read as well as the resultant status after masking. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Interrupt bits are unmasked ■ 0x1 (ENABLED): Mask interrupt Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INTMASK          GPIO_GPIO_INTMASK_MSK
#define GPIO_RSVD_GPIO_INTMASK_POS (255U)
#define GPIO_RSVD_GPIO_INTMASK_MSK (0x1UL << GPIO_RSVD_GPIO_INTMASK_POS) /*!< RSVD_GPIO_INTMASK Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INTMASK     GPIO_RSVD_GPIO_INTMASK_MSK

//GPIO_INTTYPE_LEVEL offsetaddress : 0x38
#define GPIO_GPIO_INTTYPE_LEVEL_POS (255U)
#define GPIO_GPIO_INTTYPE_LEVEL_MSK \
    (0x1UL                          \
     << GPIO_GPIO_INTTYPE_LEVEL_POS) /*!< Controls the type of interrupt that can occur on Port A. Whenever a 0 is written to a bit of this register, it configures the interrupt type to be level-sensitive; otherwise, it is edge- sensitive. Reset Value: 0x0 Values: ■ 0x0 (LEVEL_SENSITIVE): Interrupt is level sensitive ■ 0x1 (EDGE_SENSITIVE): Interrupt is edge sensitive Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INTTYPE_LEVEL          GPIO_GPIO_INTTYPE_LEVEL_MSK
#define GPIO_RSVD_GPIO_INTTYPE_LEVEL_POS (255U)
#define GPIO_RSVD_GPIO_INTTYPE_LEVEL_MSK (0x1UL << GPIO_RSVD_GPIO_INTTYPE_LEVEL_POS) /*!< RSVD_GPIO_INTTYPE_LEVEL Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INTTYPE_LEVEL     GPIO_RSVD_GPIO_INTTYPE_LEVEL_MSK

//GPIO_INT_POLARITY offsetaddress : 0x3c
#define GPIO_GPIO_INT_POLARITY_POS (255U)
#define GPIO_GPIO_INT_POLARITY_MSK \
    (0x1UL                         \
     << GPIO_GPIO_INT_POLARITY_POS) /*!< Controls the polarity of edge or level sensitivity that can occur on input of Port A. Whenever a 0 is written to a bit of this register, it configures the interrupt type to falling-edge or active-low sensitive; otherwise, it is rising-edge or active-high sensitive. Reset Value: 0x0 Values: ■ 0x0 (ACTIVE_LOW): Active Low polarity ■ 0x1 (ACTIVE_HIGH): Active High polarity Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INT_POLARITY          GPIO_GPIO_INT_POLARITY_MSK
#define GPIO_RSVD_GPIO_INT_POLARITY_POS (255U)
#define GPIO_RSVD_GPIO_INT_POLARITY_MSK (0x1UL << GPIO_RSVD_GPIO_INT_POLARITY_POS) /*!< RSVD_GPIO_INT_POLARITY Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INT_POLARITY     GPIO_RSVD_GPIO_INT_POLARITY_MSK

//GPIO_INTSTATUS offsetaddress : 0x40
#define GPIO_GPIO_INTSTATUS_POS      (255U)
#define GPIO_GPIO_INTSTATUS_MSK      (0x1UL << GPIO_GPIO_INTSTATUS_POS) /*!< Interrupt status of Port A. Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): Inactive ■ 0x1 (ACTIVE): Active Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INTSTATUS          GPIO_GPIO_INTSTATUS_MSK
#define GPIO_RSVD_GPIO_INTSTATUS_POS (255U)
#define GPIO_RSVD_GPIO_INTSTATUS_MSK (0x1UL << GPIO_RSVD_GPIO_INTSTATUS_POS) /*!< RSVD_GPIO_INTSTATUS Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INTSTATUS     GPIO_RSVD_GPIO_INTSTATUS_MSK

//GPIO_RAW_INTSTATUS offsetaddress : 0x44
#define GPIO_GPIO_RAW_INTSTATUS_POS    (255U)
#define GPIO_GPIO_RAW_INTSTATUS_MSK    (0x1UL << GPIO_GPIO_RAW_INTSTATUS_POS) /*!< Raw interrupt of status of Port A (premasking bits) Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): Inactive ■ 0x1 (ACTIVE): Active Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_RAW_INTSTATUS        GPIO_GPIO_RAW_INTSTATUS_MSK
#define GPIO_RSVD_GPIO_RAW_INTMASK_POS (255U)
#define GPIO_RSVD_GPIO_RAW_INTMASK_MSK (0x1UL << GPIO_RSVD_GPIO_RAW_INTMASK_POS) /*!< RSVD_GPIO_RAW_INTMASK Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_RAW_INTMASK     GPIO_RSVD_GPIO_RAW_INTMASK_MSK

//GPIO_DEBOUNCE offsetaddress : 0x48
#define GPIO_GPIO_DEBOUNCE_POS (255U)
#define GPIO_GPIO_DEBOUNCE_MSK \
    (0x1UL                     \
     << GPIO_GPIO_DEBOUNCE_POS) /*!< Controls whether an external signal that is the source of an interrupt needs to be debounced to remove any spurious glitches. Writing a 1 to a bit in this register enables the debouncing circuitry. A signal must be valid for two periods of an external clock before it is internally processed. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): No debounce ■ 0x1 (ENABLED): Enable debounce Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_DEBOUNCE          GPIO_GPIO_DEBOUNCE_MSK
#define GPIO_RSVD_GPIO_DEBOUNCE_POS (255U)
#define GPIO_RSVD_GPIO_DEBOUNCE_MSK (0x1UL << GPIO_RSVD_GPIO_DEBOUNCE_POS) /*!< RSVD_GPIO_DEBOUNCE Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_DEBOUNCE     GPIO_RSVD_GPIO_DEBOUNCE_MSK

//GPIO_PORTA_EOI offsetaddress : 0x4c
#define GPIO_GPIO_PORTA_EOI_POS (255U)
#define GPIO_GPIO_PORTA_EOI_MSK \
    (0x1UL                      \
     << GPIO_GPIO_PORTA_EOI_POS) /*!< Controls the clearing of edge type interrupts from Port A. When a 1 is written into a corresponding bit of this register, the interrupt is cleared. All interrupts are cleared when Port A is not configured for interrupts. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): No interrupt clear ■ 0x1 (ENABLED): Clear Interrupt Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_PORTA_EOI          GPIO_GPIO_PORTA_EOI_MSK
#define GPIO_RSVD_GPIO_PORTA_EOI_POS (255U)
#define GPIO_RSVD_GPIO_PORTA_EOI_MSK (0x1UL << GPIO_RSVD_GPIO_PORTA_EOI_POS) /*!< RSVD_GPIO_PORTA_EOI Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_PORTA_EOI     GPIO_RSVD_GPIO_PORTA_EOI_MSK

//GPIO_EXT_PORTA offsetaddress : 0x50
#define GPIO_GPIO_EXT_PORTA_POS      (255U)
#define GPIO_GPIO_EXT_PORTA_MSK      (0x1UL << GPIO_GPIO_EXT_PORTA_POS) /*!< This register always reflects the signals value on the External Port A. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_EXT_PORTA          GPIO_GPIO_EXT_PORTA_MSK
#define GPIO_RSVD_GPIO_EXT_PORTA_POS (255U)
#define GPIO_RSVD_GPIO_EXT_PORTA_MSK (0x1UL << GPIO_RSVD_GPIO_EXT_PORTA_POS) /*!< RSVD_GPIO_EXT_PORTA Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_EXT_PORTA     GPIO_RSVD_GPIO_EXT_PORTA_MSK

//GPIO_EXT_PORTB offsetaddress : 0x54
#define GPIO_GPIO_EXT_PORTB_POS      (255U)
#define GPIO_GPIO_EXT_PORTB_MSK      (0x1UL << GPIO_GPIO_EXT_PORTB_POS) /*!< This register always reflects the signals value on the External Port B. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_B - 1*/
#define GPIO_GPIO_EXT_PORTB          GPIO_GPIO_EXT_PORTB_MSK
#define GPIO_RSVD_GPIO_EXT_PORTB_POS (255U)
#define GPIO_RSVD_GPIO_EXT_PORTB_MSK (0x1UL << GPIO_RSVD_GPIO_EXT_PORTB_POS) /*!< RSVD_GPIO_EXT_PORTB Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_B*/
#define GPIO_RSVD_GPIO_EXT_PORTB     GPIO_RSVD_GPIO_EXT_PORTB_MSK

//GPIO_EXT_PORTC offsetaddress : 0x58
#define GPIO_GPIO_EXT_PORTC_POS      (255U)
#define GPIO_GPIO_EXT_PORTC_MSK      (0x1UL << GPIO_GPIO_EXT_PORTC_POS) /*!< This register always reflects the signals value on the External Port C. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_C - 1*/
#define GPIO_GPIO_EXT_PORTC          GPIO_GPIO_EXT_PORTC_MSK
#define GPIO_RSVD_GPIO_EXT_PORTC_POS (255U)
#define GPIO_RSVD_GPIO_EXT_PORTC_MSK (0x1UL << GPIO_RSVD_GPIO_EXT_PORTC_POS) /*!< RSVD_GPIO_EXT_PORTC Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_C*/
#define GPIO_RSVD_GPIO_EXT_PORTC     GPIO_RSVD_GPIO_EXT_PORTC_MSK

//GPIO_EXT_PORTD offsetaddress : 0x5c
#define GPIO_GPIO_EXT_PORTD_POS      (255U)
#define GPIO_GPIO_EXT_PORTD_MSK      (0x1UL << GPIO_GPIO_EXT_PORTD_POS) /*!< This register always reflects the signals value on the External Port D. Reset Value: 0x0 Exists: Always Volatile: true Range Variable[x]: GPIO_PWIDTH_D - 1*/
#define GPIO_GPIO_EXT_PORTD          GPIO_GPIO_EXT_PORTD_MSK
#define GPIO_RSVD_GPIO_EXT_PORTD_POS (255U)
#define GPIO_RSVD_GPIO_EXT_PORTD_MSK (0x1UL << GPIO_RSVD_GPIO_EXT_PORTD_POS) /*!< RSVD_GPIO_EXT_PORTD Reserved bits - read as zero Exists: Always Volatile: true Range Variable[y]: GPIO_PWIDTH_D*/
#define GPIO_RSVD_GPIO_EXT_PORTD     GPIO_RSVD_GPIO_EXT_PORTD_MSK

//GPIO_LS_SYNC offsetaddress : 0x60
#define GPIO_GPIO_LS_SYNC_POS (0U)
#define GPIO_GPIO_LS_SYNC_MSK \
    (0x1UL                    \
     << GPIO_GPIO_LS_SYNC_POS) /*!< Writing a 1 to this register results in all level-sensitive interrupts being synchronized to pclk_intr. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): No synchronization to pclk_int (default)r ■ 0x1 (ENABLED): Synchronize to pclk_intr Exists: Always Memory Access: "(GPIO_PORTA_INTR==1) ? \"read- write\" : \"read-only\""*/
#define GPIO_GPIO_LS_SYNC          GPIO_GPIO_LS_SYNC_MSK
#define GPIO_RSVD_GPIO_LS_SYNC_POS (1U)
#define GPIO_RSVD_GPIO_LS_SYNC_MSK (0x1UL << GPIO_RSVD_GPIO_LS_SYNC_POS) /*!< RSVD_GPIO_LS_SYNC Reserved bits - read as zero Exists: Always*/
#define GPIO_RSVD_GPIO_LS_SYNC     GPIO_RSVD_GPIO_LS_SYNC_MSK

//GPIO_ID_CODE offsetaddress : 0x64
#define GPIO_GPIO_ID_CODE_POS      (255U)
#define GPIO_GPIO_ID_CODE_MSK      (0x1UL << GPIO_GPIO_ID_CODE_POS) /*!< This is a user-specified code that a system can read. It can be used for chip identification, and so on. Reset Value: GPIO_ID_NUM Exists: Always Range Variable[x]: GPIO_ID_WIDTH - 1*/
#define GPIO_GPIO_ID_CODE          GPIO_GPIO_ID_CODE_MSK
#define GPIO_RSVD_GPIO_ID_CODE_POS (255U)
#define GPIO_RSVD_GPIO_ID_CODE_MSK (0x1UL << GPIO_RSVD_GPIO_ID_CODE_POS) /*!< RSVD_GPIO_ID_CODE Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_ID_WIDTH*/
#define GPIO_RSVD_GPIO_ID_CODE     GPIO_RSVD_GPIO_ID_CODE_MSK

//GPIO_INT_BOTHEDGE offsetaddress : 0x68
#define GPIO_GPIO_INT_BOTHEDGE_POS (255U)
#define GPIO_GPIO_INT_BOTHEDGE_MSK \
    (0x1UL                         \
     << GPIO_GPIO_INT_BOTHEDGE_POS) /*!< Controls the edge type of interrupt that can occur on Port A. -Whenever a particular bit is programmed to 1, it enables the generation of interrupts on both the rising edge and the falling edge of an external input signal corresponding to that bit on port A. - The values programmed in the registers gpio_intype_level and gpio_int_polarity for this particular bit are not considered when the corresponding bit of this register is set to 1. - Whenever a particular bit is programmed to 0, the interrupt type depends on the value of the corresponding bits in the gpio_inttype_level and gpio_int_polarity registers. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): single edge sensitive ■ 0x1 (ENABLED): both edge sensitive Exists: Always Range Variable[x]: GPIO_PWIDTH_A - 1*/
#define GPIO_GPIO_INT_BOTHEDGE          GPIO_GPIO_INT_BOTHEDGE_MSK
#define GPIO_RSVD_GPIO_INT_BOTHEDGE_POS (255U)
#define GPIO_RSVD_GPIO_INT_BOTHEDGE_MSK (0x1UL << GPIO_RSVD_GPIO_INT_BOTHEDGE_POS) /*!< RSVD_GPIO_INT_BOTHEDGE Reserved bits - read as zero Exists: Always Range Variable[y]: GPIO_PWIDTH_A*/
#define GPIO_RSVD_GPIO_INT_BOTHEDGE     GPIO_RSVD_GPIO_INT_BOTHEDGE_MSK

//GPIO_VER_ID_CODE offsetaddress : 0x6c
#define GPIO_GPIO_VER_ID_CODE_POS (0U)
#define GPIO_GPIO_VER_ID_CODE_MSK (0x1UL << GPIO_GPIO_VER_ID_CODE_POS) /*!< ASCII value for each number in the version, followed by *. For example 32_31_32_2A represents the version 2.12*. Reset Value: See the releases table in the Release Notes Exists: Always*/
#define GPIO_GPIO_VER_ID_CODE     GPIO_GPIO_VER_ID_CODE_MSK

//GPIO_CONFIG_REG2 offsetaddress : 0x70
#define GPIO_ENCODED_ID_PWIDTH_A_POS   (0U)
#define GPIO_ENCODED_ID_PWIDTH_A_MSK   (0x1UL << GPIO_ENCODED_ID_PWIDTH_A_POS) /*!< The value of this register is derived from the GPIO_PWIDTH_A configuration parameter. 0x0 = 8 bits 0x1 = 16 bits 0x2 = 32 bits 0x3 = Reserved Exists: Always*/
#define GPIO_ENCODED_ID_PWIDTH_A       GPIO_ENCODED_ID_PWIDTH_A_MSK
#define GPIO_ENCODED_ID_PWIDTH_B_POS   (5U)
#define GPIO_ENCODED_ID_PWIDTH_B_MSK   (0x1UL << GPIO_ENCODED_ID_PWIDTH_B_POS) /*!< The value of this register is derived from the GPIO_PWIDTH_B configuration parameter. 0x0 = 8 bits 0x1 = 16 bits 0x2 = 32 bits 0x3 = Reserved Exists: Always*/
#define GPIO_ENCODED_ID_PWIDTH_B       GPIO_ENCODED_ID_PWIDTH_B_MSK
#define GPIO_ENCODED_ID_PWIDTH_C_POS   (10U)
#define GPIO_ENCODED_ID_PWIDTH_C_MSK   (0x1UL << GPIO_ENCODED_ID_PWIDTH_C_POS) /*!< The value of this register is derived from the GPIO_PWIDTH_C configuration parameter. 0x0 = 8 bits 0x1 = 16 bits 0x2 = 32 bits 0x3 = Reserved Exists: Always*/
#define GPIO_ENCODED_ID_PWIDTH_C       GPIO_ENCODED_ID_PWIDTH_C_MSK
#define GPIO_ENCODED_ID_PWIDTH_D_POS   (15U)
#define GPIO_ENCODED_ID_PWIDTH_D_MSK   (0x1UL << GPIO_ENCODED_ID_PWIDTH_D_POS) /*!< The value of this register is derived from the GPIO_PWIDTH_D configuration parameter. 0x0 = 8 bits 0x1 = 16 bits 0x2 = 32 bits 0x3 = Reserved Exists: Always*/
#define GPIO_ENCODED_ID_PWIDTH_D       GPIO_ENCODED_ID_PWIDTH_D_MSK
#define GPIO_RSVD_GPIO_CONFIG_REG2_POS (20U)
#define GPIO_RSVD_GPIO_CONFIG_REG2_MSK (0x1UL << GPIO_RSVD_GPIO_CONFIG_REG2_POS) /*!< RSVD_GPIO_CONFIG_REG2 Reserved bits - read as zero Exists: Always*/
#define GPIO_RSVD_GPIO_CONFIG_REG2     GPIO_RSVD_GPIO_CONFIG_REG2_MSK

//GPIO_CONFIG_REG1 offsetaddress : 0x74
#define GPIO_APB_DATA_WIDTH_POS (0U)
#define GPIO_APB_DATA_WIDTH_MSK \
    (0x1UL                      \
     << GPIO_APB_DATA_WIDTH_POS) /*!< The value of this register is derived from the GPIO_APB_DATA_WIDTH configuration parameter. Note: 0x3 = Reserved Values: ■ 0x0 (APB_8BITS): APB DATA WIDTH is 8 bits ■ 0x1 (APB_16BITS): APB DATA WIDTH is 16 bits ■ 0x2 (APB_32BITS): APB DATA WIDTH is 32 bits Exists: Always*/
#define GPIO_APB_DATA_WIDTH GPIO_APB_DATA_WIDTH_MSK
#define GPIO_NUM_PORTS_POS  (2U)
#define GPIO_NUM_PORTS_MSK \
    (0x1UL                 \
     << GPIO_NUM_PORTS_POS) /*!< The value of this register is derived from the GPIO_NUM_PORT configuration parameter. Values: ■ 0x0 (NUM_PORTS_1): Number of ports is 1 ■ 0x1 (NUM_PORTS_2): Number of ports is 2 ■ 0x2 (NUM_PORTS_3): Number of ports is 3 ■ 0x3 (NUM_PORTS_4): Number of ports is 4 Exists: Always*/
#define GPIO_NUM_PORTS            GPIO_NUM_PORTS_MSK
#define GPIO_PORTA_SINGLE_CTL_POS (4U)
#define GPIO_PORTA_SINGLE_CTL_MSK \
    (0x1UL << GPIO_PORTA_SINGLE_CTL_POS) /*!< The value of this register is derived from the GPIO_PORTA_SINGLE_CTL configuration parameter. Values: ■ 0x0 (DISABLED): PORTA is not controlled from a single source ■ 0x1 (ENABLED): PORTA is controlled from a single source Exists: Always*/
#define GPIO_PORTA_SINGLE_CTL     GPIO_PORTA_SINGLE_CTL_MSK
#define GPIO_PORTB_SINGLE_CTL_POS (5U)
#define GPIO_PORTB_SINGLE_CTL_MSK \
    (0x1UL << GPIO_PORTB_SINGLE_CTL_POS) /*!< The value of this register is derived from the GPIO_PORTB_SINGLE_CTL configuration parameter. Values: ■ 0x0 (DISABLED): PORTB is not controlled from a single source ■ 0x1 (ENABLED): PORTB is controlled from a single source Exists: Always*/
#define GPIO_PORTB_SINGLE_CTL     GPIO_PORTB_SINGLE_CTL_MSK
#define GPIO_PORTC_SINGLE_CTL_POS (6U)
#define GPIO_PORTC_SINGLE_CTL_MSK \
    (0x1UL << GPIO_PORTC_SINGLE_CTL_POS) /*!< The value of this register is derived from the GPIO_PORTC_SINGLE_CTL configuration parameter. Values: ■ 0x0 (DISABLED): PORTC is not controlled from a single source ■ 0x1 (ENABLED): PORTC is controlled from a single source Exists: Always*/
#define GPIO_PORTC_SINGLE_CTL     GPIO_PORTC_SINGLE_CTL_MSK
#define GPIO_PORTD_SINGLE_CTL_POS (7U)
#define GPIO_PORTD_SINGLE_CTL_MSK \
    (0x1UL << GPIO_PORTD_SINGLE_CTL_POS) /*!< The value of this register is derived from the GPIO_PORTD_SINGLE_CTL configuration parameter. Values: ■ 0x0 (DISABLED): PORTD is not controlled from a single source ■ 0x1 (ENABLED): PORTD is controlled from a single source Exists: Always*/
#define GPIO_PORTD_SINGLE_CTL GPIO_PORTD_SINGLE_CTL_MSK
#define GPIO_HW_PORTA_POS     (8U)
#define GPIO_HW_PORTA_MSK \
    (0x1UL << GPIO_HW_PORTA_POS) /*!< The value of this register is derived from the GPIO_HW_PORTA configuration parameter. Values: ■ 0x0 (DISABLED): Port A has external, auxiliary hardware signals excluded ■ 0x1 (ENABLED): Port A has external, auxiliary hardware signals included Exists: Always*/
#define GPIO_HW_PORTA     GPIO_HW_PORTA_MSK
#define GPIO_HW_PORTB_POS (9U)
#define GPIO_HW_PORTB_MSK \
    (0x1UL << GPIO_HW_PORTB_POS) /*!< The value of this register is derived from the GPIO_HW_PORTB configuration parameter. Values: ■ 0x0 (DISABLED): Port B has external, auxiliary hardware signals excluded ■ 0x1 (ENABLED): Port B has external, auxiliary hardware signals included Exists: Always*/
#define GPIO_HW_PORTB     GPIO_HW_PORTB_MSK
#define GPIO_HW_PORTC_POS (10U)
#define GPIO_HW_PORTC_MSK \
    (0x1UL << GPIO_HW_PORTC_POS) /*!< The value of this register is derived from the GPIO_HW_PORTC configuration parameter. Values: ■ 0x0 (DISABLED): Port C has external, auxiliary hardware signals excluded ■ 0x1 (ENABLED): Port C has external, auxiliary hardware signals included Exists: Always*/
#define GPIO_HW_PORTC     GPIO_HW_PORTC_MSK
#define GPIO_HW_PORTD_POS (11U)
#define GPIO_HW_PORTD_MSK \
    (0x1UL << GPIO_HW_PORTD_POS) /*!< The value of this register is derived from the GPIO_HW_PORTD configuration parameter. Values: ■ 0x0 (DISABLED): Port D has external, auxiliary hardware signals excluded ■ 0x1 (ENABLED): Port D has external, auxiliary hardware signals included Exists: Always*/
#define GPIO_HW_PORTD       GPIO_HW_PORTD_MSK
#define GPIO_PORTA_INTR_POS (12U)
#define GPIO_PORTA_INTR_MSK \
    (0x1UL << GPIO_PORTA_INTR_POS) /*!< The value of this register is derived from the GPIO_PORTA_INTR configuration parameter. Values: ■ 0x0 (DISABLED): PORT A is not used as an interrupt source ■ 0x1 (ENABLED): PORT A is required to be used as an interrupt source Exists: Always*/
#define GPIO_PORTA_INTR                   GPIO_PORTA_INTR_MSK
#define GPIO_DEBOUNCE_POS                 (13U)
#define GPIO_DEBOUNCE_MSK                 (0x1UL << GPIO_DEBOUNCE_POS) /*!< The value of this register is derived from the GPIO_DEBOUNCE configuration parameter. Values: ■ 0x0 (DISABLED): Exclude debounce capability ■ 0x1 (ENABLED): Include debounce capability Exists: Always*/
#define GPIO_DEBOUNCE                     GPIO_DEBOUNCE_MSK
#define GPIO_ADD_ENCODED_PARAMS_POS       (14U)
#define GPIO_ADD_ENCODED_PARAMS_MSK       (0x1UL << GPIO_ADD_ENCODED_PARAMS_POS) /*!< The value of this register is derived from the GPIO_ADD_ENCODED_PARAMS configuration parameter. Values: ■ 0x0 (DISABLED): Encoded parameters not added ■ 0x1 (ENABLED): Encoded parameters added Exists: Always*/
#define GPIO_ADD_ENCODED_PARAMS           GPIO_ADD_ENCODED_PARAMS_MSK
#define GPIO_GPIO_ID_POS                  (15U)
#define GPIO_GPIO_ID_MSK                  (0x1UL << GPIO_GPIO_ID_POS) /*!< The value of this register is derived from the GPIO_ID configuration parameter. Values: ■ 0x0 (DISABLED): GPIO_ID not included ■ 0x1 (ENABLED): GPIO_ID is included Exists: Always*/
#define GPIO_GPIO_ID                      GPIO_GPIO_ID_MSK
#define GPIO_ENCODED_ID_WIDTH_POS         (16U)
#define GPIO_ENCODED_ID_WIDTH_MSK         (0x1UL << GPIO_ENCODED_ID_WIDTH_POS) /*!< The value of this register is derived from the GPIO_ID_WIDTH configuration parameter. Exists: Always*/
#define GPIO_ENCODED_ID_WIDTH             GPIO_ENCODED_ID_WIDTH_MSK
#define GPIO_INTERRUPT_BOTH_EDGE_TYPE_POS (21U)
#define GPIO_INTERRUPT_BOTH_EDGE_TYPE_MSK \
    (0x1UL                                \
     << GPIO_INTERRUPT_BOTH_EDGE_TYPE_POS) /*!< The value of this register is derived from the GPIO_INT_BOTH_EDGE configuration parameter Values: ■ 0x0 (DISABLED): Interrupt generation on rising or falling edge ■ 0x1 (ENABLED): Interrupt generation on both rising and falling edge Exists: Always*/
#define GPIO_INTERRUPT_BOTH_EDGE_TYPE  GPIO_INTERRUPT_BOTH_EDGE_TYPE_MSK
#define GPIO_RSVD_GPIO_CONFIG_REG1_POS (22U)
#define GPIO_RSVD_GPIO_CONFIG_REG1_MSK (0x1UL << GPIO_RSVD_GPIO_CONFIG_REG1_POS) /*!< RSVD_GPIO_CONFIG_REG1 Reserved bits - read as zero Exists: Always*/
#define GPIO_RSVD_GPIO_CONFIG_REG1     GPIO_RSVD_GPIO_CONFIG_REG1_MSK

typedef struct {
    volatile uint32_t SWPORTA_DR;    //offsetaddress : 0x0
    volatile uint32_t SWPORTA_DDR;   //offsetaddress : 0x4
    volatile uint32_t SWPORTA_CTL;   //offsetaddress : 0x8
    volatile uint32_t SWPORTB_DR;    //offsetaddress : 0xc
    volatile uint32_t SWPORTB_DDR;   //offsetaddress : 0x10
    volatile uint32_t SWPORTB_CTL;   //offsetaddress : 0x14
    volatile uint32_t SWPORTC_DR;    //offsetaddress : 0x18
    volatile uint32_t SWPORTC_DDR;   //offsetaddress : 0x1c
    volatile uint32_t SWPORTC_CTL;   //offsetaddress : 0x20
    volatile uint32_t SWPORTD_DR;    //offsetaddress : 0x24
    volatile uint32_t SWPORTD_DDR;   //offsetaddress : 0x28
    volatile uint32_t SWPORTD_CTL;   //offsetaddress : 0x2c
    volatile uint32_t INTEN;         //offsetaddress : 0x30
    volatile uint32_t INTMASK;       //offsetaddress : 0x34
    volatile uint32_t INTTYPE_LEVEL; //offsetaddress : 0x38
    volatile uint32_t INT_POLARITY;  //offsetaddress : 0x3c
    volatile uint32_t INTSTATUS;     //offsetaddress : 0x40
    volatile uint32_t RAW_INTSTATUS; //offsetaddress : 0x44
    volatile uint32_t DEBOUNCE;      //offsetaddress : 0x48
    volatile uint32_t PORTA_EOI;     //offsetaddress : 0x4c
    volatile uint32_t EXT_PORTA;     //offsetaddress : 0x50
    volatile uint32_t EXT_PORTB;     //offsetaddress : 0x54
    volatile uint32_t EXT_PORTC;     //offsetaddress : 0x58
    volatile uint32_t EXT_PORTD;     //offsetaddress : 0x5c
    volatile uint32_t LS_SYNC;       //offsetaddress : 0x60
    volatile uint32_t ID_CODE;       //offsetaddress : 0x64
    volatile uint32_t INT_BOTHEDGE;  //offsetaddress : 0x68
    volatile uint32_t VER_ID_CODE;   //offsetaddress : 0x6c
    volatile uint32_t CONFIG_REG2;   //offsetaddress : 0x70
    volatile uint32_t CONFIG_REG1;   //offsetaddress : 0x74
} gpio_reg_t;
#ifdef __cplusplus
}
#endif
#endif
/*******************************************************************************************************
 *
 * @file    wdt.h
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
#ifndef __WDT_H__
#define __WDT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//WDT_CR offsetaddress : 0x0
#define WDT_WDT_EN_POS (0U)
#define WDT_WDT_EN_MSK \
    (0x1UL             \
     << WDT_WDT_EN_POS) /*!< WDT enable. When the configuration parameter WDT_ALWAYS_EN = 0, this bit can be set; otherwise, it is read-only. This bit is used to enable and disable the DW_apb_wdt. When disabled, the counter does not decrement. Thus, no interrupts or system resets are generated. The DW_apb_wdt is used to prevent system lock-up. To prevent a software bug from disabling the DW_apb_wdt, once this bit has been enabled, it can be cleared only by a system reset. Reset Value: WDT_ALWAYS_EN Values: ■ 0x0 (DISABLED): Watchdog timer disabled ■ 0x1 (ENABLED): Watchdog timer enabled Exists: Always*/
#define WDT_WDT_EN      WDT_WDT_EN_MSK
#define WDT_WDT_EN_W(X) ((X) << WDT_WDT_EN_POS)
#define WDT_RMOD_POS    (1U)
#define WDT_RMOD_MSK \
    (0x1UL           \
     << WDT_RMOD_POS) /*!< Response mode. Writes have no effect when the parameter WDT_HC_RMOD = 1, thus this register becomes read-only. Selects the output response generated to a timeout. Reset Value: WDT_DFLT_RMOD Values: ■ 0x0 (RESET): Generate a system reset ■ 0x1 (INTERRUPT): First generate an interrupt and even if it is cleared by the time a second timeout occurs then generate a system reset Exists: Always*/
#define WDT_RMOD      WDT_RMOD_MSK
#define WDT_RMOD_W(X) ((X) << WDT_RMOD_POS)
#define WDT_RPL_POS   (2U)
#define WDT_RPL_MSK \
    (0x7UL          \
     << WDT_RPL_POS) /*!< Reset pulse length. Writes have no effect when the configuration parameter WDT_HC_RPL is 1, making the register bits read-only. This is used to select the number of pclk cycles for which the system reset stays asserted. The range of values available is 2 to 256 pclk cycles. Reset Value: WDT_DFLT_RPL Note: When WDT_SYNC_CLK_MOPE_ENABLE = 1, the total reset pulse length also includes the reset synchronization delay and the time taken for pclk to be made available. For details, refer to "System Resets" section of DW_apb_wdt Databook. Values: ■ 0x0 (PCLK_CYCLES2): 2 pclk cycles ■ 0x1 (PCLK_CYCLES4): 4 pclk cycles ■ 0x2 (PCLK_CYCLES8): 8 pclk cycles ■ 0x3 (PCLK_CYCLES16): 16 pclk cycles ■ 0x4 (PCLK_CYCLES32): 32 pclk cycles ■ 0x5 (PCLK_CYCLES64): 64 pclk cycles ■ 0x6 (PCLK_CYCLES128): 128 pclk cycles ■ 0x7 (PCLK_CYCLES256): 256 pclk cycles Exists: Always*/
#define WDT_RPL              WDT_RPL_MSK
#define WDT_RPL_W(X)         ((X) << WDT_RPL_POS)
#define WDT_NO_NAME_POS      (5U)
#define WDT_NO_NAME_MSK      (0x1UL << WDT_NO_NAME_POS) /*!< Redundant R/W bit. Included for ping test purposes, as it is the only R/W register bit that is in every configuration of the DW_apb_wdt. Exists: Always*/
#define WDT_NO_NAME          WDT_NO_NAME_MSK
#define WDT_NO_NAME_W(X)     ((X) << WDT_NO_NAME_POS)
#define WDT_RSVD_WDT_CR_POS  (6U)
#define WDT_RSVD_WDT_CR_MSK  (0x3ffffffUL << WDT_RSVD_WDT_CR_POS) /*!< WDT_CR[31:6] Reserved bits and read as zero (0). Exists: Always*/
#define WDT_RSVD_WDT_CR      WDT_RSVD_WDT_CR_MSK
#define WDT_RSVD_WDT_CR_W(X) ((X) << WDT_RSVD_WDT_CR_POS)

//WDT_TORR offsetaddress : 0x4
#define WDT_TOP_POS (0U)
#define WDT_TOP_MSK \
    (0xfUL          \
     << WDT_TOP_POS) /*!< Timeout period. Writes have no effect when the configuration parameter WDT_HC_TOP = 1, thus making this register read-only. This field is used to select the timeout period from which the watchdog counter restarts. A change of the timeout period takes effect only after the next counter restart (kick). The range of values is limited by the WDT_CNT_WIDTH. If TOP is programmed to select a range that is greater than the counter width, the timeout period is truncated to fit to the counter width. This affects only the non-user specified values as users are limited to these boundaries during configuration. The range of values available for a 32-bit watchdog counter are: Where i = TOP and t = timeout period For i = 0 to 15 if WDT_USE_FIX_TOP==1 t = 2(16 + i) else t = WDT_USER_TOP_(i) Reset Value: WDT_DFLT_TOP Values: ■ 0x0 (USER0_OR_64K): Time out of WDT_USER_TOP_0 or 64K Clocks ■ 0x1 (USER1_OR_128K): Time out of WDT_USER_TOP_1 or 128K Clocks ■ 0x2 (USER2_OR_256K): Time out of WDT_USER_TOP_2 or 256K Clocks ■ 0x3 (USER3_OR_512K): Time out of WDT_USER_TOP_3 or 512K Clocks ■ 0x4 (USER4_OR_1M): Time out of WDT_USER_TOP_4 or 1M Clocks ■ 0x5 (USER5_OR_2M): Time out of WDT_USER_TOP_5 or 2M Clocks ■ 0x6 (USER6_OR_4M): Time out of WDT_USER_TOP_6 or 4M Clocks ■ 0x7 (USER7_OR_8M): Time out of WDT_USER_TOP_7 or 8M Clocks ■ 0x8 (USER8_OR_16M): Time out of WDT_USER_TOP_8 or 16M Clocks ■ 0x9 (USER9_OR_32M): Time out of WDT_USER_TOP_9 or 32M Clocks*/
#define WDT_TOP          WDT_TOP_MSK
#define WDT_TOP_W(X)     ((X) << WDT_TOP_POS)
#define WDT_TOP_INIT_POS (4U)
#define WDT_TOP_INIT_MSK \
    (0xfUL               \
     << WDT_TOP_INIT_POS) /*!< Timeout period for initialization. Writes to these register bits have no effect when the configuration parameter WDT_HC_TOP = 1 or WDT_ALWAYS_EN = 1. Used to select the timeout period that the watchdog counter restarts from for the first counter restart (kick). This register should be written after reset and before the WDT is enabled. A change of the TOP_INIT is seen only once the WDT has been enabled, and any change after the first kick is not seen as subsequent kicks use the period specified by the TOP bits. The range of values is limited by the WDT_CNT_WIDTH. If TOP_INIT is programmed to select a range that is greater than the counter width, the timeout period is truncated to fit to the counter width. This affects only the non-user specified values as users are limited to these boundaries during configuration. The range of values available for a 32-bit watchdog counter are: Where i = TOP_INIT and t = timeout period For i = 0 to 15 if WDT_USE_FIX_TOP==1 t = 2(16 + i) else t = WDT_USER_TOP_INIT_(i) Note: These bits exist only when the configuration parameter WDT_DUAL_TOP = 1, otherwise, they are fixed at zero. Reset Value: Configuration parameter WDT_DFLT_TOP_INIT Values: ■ 0x0 (USER0_OR_64K): Time out of WDT_USER_TOP_INIT_0 or 64K Clocks ■ 0x1 (USER1_OR_128K): Time out of WDT_USER_TOP_INIT_1 or 128K Clocks ■ 0x2 (USER2_OR_256K): Time out of WDT_USER_TOP_INIT_2 or 256K Clocks ■ 0x3 (USER3_OR_512K): Time out of WDT_USER_TOP_INIT_3 or 512K Clocks ■ 0x4 (USER4_OR_1M): Time out of WDT_USER_TOP_INIT_4 or 1M Clocks*/
#define WDT_TOP_INIT      WDT_TOP_INIT_MSK
#define WDT_TOP_INIT_W(X) ((X) << WDT_TOP_INIT_POS)
#define WDT_RESERVED_POS  (8U)
#define WDT_RESERVED_MSK  (0xffffffUL << WDT_RESERVED_POS) /*!< WDT_TORR[31:24] Reserved and read as zero (0). Exists: Always*/
#define WDT_RESERVED      WDT_RESERVED_MSK
#define WDT_RESERVED_W(X) ((X) << WDT_RESERVED_POS)

//WDT_CCVR offsetaddress : 0x8
#define WDT_WDT_CCVR_POS (0U)
#define WDT_WDT_CCVR_MSK \
    (0xFFFFFFFFUL        \
     << WDT_WDT_CCVR_POS) /*!< WDT Current Counter Value Register. This register, when read, is the current value of the internal counter. This value is read coherently when ever it is read, which is relevant when the APB_DATA_WIDTH is less than the counter width. Reset Value: WDT_CNT_RST Exists: Always Volatile: true Range Variable[x]: WDT_CNT_WIDTH - 1*/
#define WDT_WDT_CCVR      WDT_WDT_CCVR_MSK
#define WDT_WDT_CCVR_W(X) ((X) << WDT_WDT_CCVR_POS)

//WDT_CRR offsetaddress : 0xc
#define WDT_WDT_CRR_POS (0U)
#define WDT_WDT_CRR_MSK \
    (0xffUL             \
     << WDT_WDT_CRR_POS) /*!< Counter Restart Register. This register is used to restart the WDT counter. As a safety feature to prevent accidental restarts, the value 0x76 must be written. A restart also clears the WDT interrupt. Reading this register returns zero. Reset Value: 0 Values: ■ 0x76 (RESTART): Watchdog timer restart command Exists: Always*/
#define WDT_WDT_CRR           WDT_WDT_CRR_MSK
#define WDT_WDT_CRR_W(X)      ((X) << WDT_WDT_CRR_POS)
#define WDT_RSVD_WDT_CRR_POS  (8U)
#define WDT_RSVD_WDT_CRR_MSK  (0xffffffUL << WDT_RSVD_WDT_CRR_POS) /*!< WDT_CRR[31:24] Reserved bits - Write Only Exists: Always*/
#define WDT_RSVD_WDT_CRR      WDT_RSVD_WDT_CRR_MSK
#define WDT_RSVD_WDT_CRR_W(X) ((X) << WDT_RSVD_WDT_CRR_POS)

//WDT_STAT offsetaddress : 0x10
#define WDT_WDT_STAT_POS       (0U)
#define WDT_WDT_STAT_MSK       (0x1UL << WDT_WDT_STAT_POS) /*!< Interrupt status register This register shows the interrupt status of the WDT. Reset Value 0 Values: ■ 0x0 (INACTIVE): Interrupt is inactive ■ 0x1 (ACTIVE): Interrupt is active regardless of polarity Exists: Always Volatile: true*/
#define WDT_WDT_STAT           WDT_WDT_STAT_MSK
#define WDT_WDT_STAT_W(X)      ((X) << WDT_WDT_STAT_POS)
#define WDT_RSVD_WDT_STAT_POS  (1U)
#define WDT_RSVD_WDT_STAT_MSK  (0x7fffffffUL << WDT_RSVD_WDT_STAT_POS) /*!< WDT_STAT[31] Reserved bits - Read Only Exists: Always Volatile: true*/
#define WDT_RSVD_WDT_STAT      WDT_RSVD_WDT_STAT_MSK
#define WDT_RSVD_WDT_STAT_W(X) ((X) << WDT_RSVD_WDT_STAT_POS)

//WDT_EOI offsetaddress : 0x14
#define WDT_WDT_EOI_POS       (0U)
#define WDT_WDT_EOI_MSK       (0x1UL << WDT_WDT_EOI_POS) /*!< Interrupt Clear Register. Clears the watchdog interrupt. This can be used to clear the interrupt without restarting the watchdog counter. Reset Value: 0 Exists: Always Volatile: true*/
#define WDT_WDT_EOI           WDT_WDT_EOI_MSK
#define WDT_WDT_EOI_W(X)      ((X) << WDT_WDT_EOI_POS)
#define WDT_RSVD_WDT_EOI_POS  (1U)
#define WDT_RSVD_WDT_EOI_MSK  (0x7fffffffUL << WDT_RSVD_WDT_EOI_POS) /*!< RSVD_WDT_EOI[31] Reserved bits and read as zero (0). Exists: Always Volatile: true*/
#define WDT_RSVD_WDT_EOI      WDT_RSVD_WDT_EOI_MSK
#define WDT_RSVD_WDT_EOI_W(X) ((X) << WDT_RSVD_WDT_EOI_POS)

//WDT_PROT_LEVEL offsetaddress : 0x1c
#define WDT_WDT_PROT_LEVEL_POS (0U)
#define WDT_WDT_PROT_LEVEL_MSK \
    (0x7UL                     \
     << WDT_WDT_PROT_LEVEL_POS) /*!< Protection level register. Enabling protection on any of its three bits would require a match on the input PPROT signal to gain access to protected registers of the WDT. R/W if HC_PROT_LEVEL = 0 R if HC_PROT_LEVEL = 1 Reset Value: PROT_LEVEL_RST Exists: Always*/
#define WDT_WDT_PROT_LEVEL           WDT_WDT_PROT_LEVEL_MSK
#define WDT_WDT_PROT_LEVEL_W(X)      ((X) << WDT_WDT_PROT_LEVEL_POS)
#define WDT_RSVD_WDT_PROT_LEVEL_POS  (3U)
#define WDT_RSVD_WDT_PROT_LEVEL_MSK  (0x1fffffffUL << WDT_RSVD_WDT_PROT_LEVEL_POS) /*!< WDT_PROT_LEVEL[31:29]Reserved field- read-only Exists: Always*/
#define WDT_RSVD_WDT_PROT_LEVEL      WDT_RSVD_WDT_PROT_LEVEL_MSK
#define WDT_RSVD_WDT_PROT_LEVEL_W(X) ((X) << WDT_RSVD_WDT_PROT_LEVEL_POS)

//WDT_COMP_PARAM_5 offsetaddress : 0xe4
#define WDT_CP_WDT_USER_TOP_MAX_POS  (0U)
#define WDT_CP_WDT_USER_TOP_MAX_MSK  (0xffffffffUL << WDT_CP_WDT_USER_TOP_MAX_POS) /*!< Upper limit of Timeout Period parameters. The value of this register is derived from the WDT_USER_TOP_* coreConsultant parameters. Value After Reset: WDT_USER_TOP_MAX Exists: Always*/
#define WDT_CP_WDT_USER_TOP_MAX      WDT_CP_WDT_USER_TOP_MAX_MSK
#define WDT_CP_WDT_USER_TOP_MAX_W(X) ((X) << WDT_CP_WDT_USER_TOP_MAX_POS)

//WDT_COMP_PARAM_4 offsetaddress : 0xe8
#define WDT_CP_WDT_USER_TOP_INIT_MAX_POS  (0U)
#define WDT_CP_WDT_USER_TOP_INIT_MAX_MSK  (0xffffffffUL << WDT_CP_WDT_USER_TOP_INIT_MAX_POS) /*!< Upper limit of Initial Timeout Period parameters. The value of this register is derived from the WDT_USER_TOP_INIT_* coreConsultant parameters. Value After Reset: WDT_USER_TOP_INIT_MAX Exists: Always*/
#define WDT_CP_WDT_USER_TOP_INIT_MAX      WDT_CP_WDT_USER_TOP_INIT_MAX_MSK
#define WDT_CP_WDT_USER_TOP_INIT_MAX_W(X) ((X) << WDT_CP_WDT_USER_TOP_INIT_MAX_POS)

//WDT_COMP_PARAM_3 offsetaddress : 0xec
#define WDT_CD_WDT_TOP_RST_POS  (0U)
#define WDT_CD_WDT_TOP_RST_MSK  (0xffffffffUL << WDT_CD_WDT_TOP_RST_POS) /*!< The value of this register is derived from the WDT_TOP_RST coreConsultant parameter. Value After Reset: WDT_TOP_RST Exists: Always*/
#define WDT_CD_WDT_TOP_RST      WDT_CD_WDT_TOP_RST_MSK
#define WDT_CD_WDT_TOP_RST_W(X) ((X) << WDT_CD_WDT_TOP_RST_POS)

//WDT_COMP_PARAM_2 offsetaddress : 0xf0
#define WDT_CP_WDT_CNT_RST_POS  (0U)
#define WDT_CP_WDT_CNT_RST_MSK  (0xffffffffUL << WDT_CP_WDT_CNT_RST_POS) /*!< The value of this register is derived from the WDT_RST_CNT coreConsultant parameter. Value After Reset: WDT_CNT_RST Exists: Always*/
#define WDT_CP_WDT_CNT_RST      WDT_CP_WDT_CNT_RST_MSK
#define WDT_CP_WDT_CNT_RST_W(X) ((X) << WDT_CP_WDT_CNT_RST_POS)

//WDT_COMP_PARAM_1 offsetaddress : 0xf4
#define WDT_WDT_ALWAYS_EN_POS (0U)
#define WDT_WDT_ALWAYS_EN_MSK \
    (0x1UL                    \
     << WDT_WDT_ALWAYS_EN_POS) /*!< Configures the WDT to be enabled from reset. If this setting is 1, the WDT is always enabled and a write to the WDT_EN field (bit 0) of the Watchdog Timer Control Register (WDT_CR) to disable it has no effect. Values: ■ 0x0 (DISABLED): Watchdog timer disabled on reset ■ 0x1 (ENABLED): Watchdog timer enabled on reset Value After Reset: WDT_ALWAYS_EN Exists: Always*/
#define WDT_WDT_ALWAYS_EN      WDT_WDT_ALWAYS_EN_MSK
#define WDT_WDT_ALWAYS_EN_W(X) ((X) << WDT_WDT_ALWAYS_EN_POS)
#define WDT_WDT_DFLT_RMOD_POS  (1U)
#define WDT_WDT_DFLT_RMOD_MSK \
    (0x1UL                    \
     << WDT_WDT_DFLT_RMOD_POS) /*!< Describes the output response mode that is available directly after reset. Indicates the output response the WDT gives if a zero count is reached; that is, a system reset if equals 0 and an interrupt followed by a system reset, if equals 1. If WDT_HC_RMOD is 1, then default response mode is the only possible output response mode. Values: ■ 0x0 (DISABLED): System reset only ■ 0x1 (ENABLED): Interrupt and system reset Value After Reset: WDT_DFLT_RMOD Exists: Always*/
#define WDT_WDT_DFLT_RMOD      WDT_WDT_DFLT_RMOD_MSK
#define WDT_WDT_DFLT_RMOD_W(X) ((X) << WDT_WDT_DFLT_RMOD_POS)
#define WDT_WDT_DUAL_TOP_POS   (2U)
#define WDT_WDT_DUAL_TOP_MSK \
    (0x1UL                   \
     << WDT_WDT_DUAL_TOP_POS) /*!< When set to 1, includes a second timeout period that is used for initialization prior to the first kick. Values: ■ 0x0 (DISABLED): Second timeout period is not present ■ 0x1 (ENABLED): Second timeout period is present Value After Reset: WDT_DUAL_TOP Exists: Always*/
#define WDT_WDT_DUAL_TOP        WDT_WDT_DUAL_TOP_MSK
#define WDT_WDT_DUAL_TOP_W(X)   ((X) << WDT_WDT_DUAL_TOP_POS)
#define WDT_WDT_HC_RMOD_POS     (3U)
#define WDT_WDT_HC_RMOD_MSK     (0x1UL << WDT_WDT_HC_RMOD_POS) /*!< Configures the output response mode to be hard coded. Values: ■ 0x0 (PROGRAMMABLE): Output response mode is programmable ■ 0x1 (HARDCODED): Output response mode is hard coded Value After Reset: WDT_HC_RMOD Exists: Always*/
#define WDT_WDT_HC_RMOD         WDT_WDT_HC_RMOD_MSK
#define WDT_WDT_HC_RMOD_W(X)    ((X) << WDT_WDT_HC_RMOD_POS)
#define WDT_WDT_HC_RPL_POS      (4U)
#define WDT_WDT_HC_RPL_MSK      (0x1UL << WDT_WDT_HC_RPL_POS) /*!< Configures the reset pulse length to be hard coded. Values: ■ 0x0 (PROGRAMMABLE): Reset pulse length is programmable ■ 0x1 (HARDCODED): Reset pulse length is hardcoded Value After Reset: WDT_HC_RPL Exists: Always*/
#define WDT_WDT_HC_RPL          WDT_WDT_HC_RPL_MSK
#define WDT_WDT_HC_RPL_W(X)     ((X) << WDT_WDT_HC_RPL_POS)
#define WDT_WDT_HC_TOP_POS      (5U)
#define WDT_WDT_HC_TOP_MSK      (0x1UL << WDT_WDT_HC_TOP_POS) /*!< When set to 1, the selected timeout period(s) is set to be hard coded. Values: ■ 0x0 (PROGRAMMABLE): Timeout period is programmable ■ 0x1 (HARDCODED): Timeout period is hard coded Value After Reset: WDT_HC_TOP Exists: Always*/
#define WDT_WDT_HC_TOP          WDT_WDT_HC_TOP_MSK
#define WDT_WDT_HC_TOP_W(X)     ((X) << WDT_WDT_HC_TOP_POS)
#define WDT_WDT_USE_FIX_TOP_POS (6U)
#define WDT_WDT_USE_FIX_TOP_MSK \
    (0x1UL                      \
     << WDT_WDT_USE_FIX_TOP_POS) /*!< When this parameter is set to 1, timeout period range is fixed. The range increments by the power of 2 from 2^16 to 2^(WDT_CNT_WIDTH-1). When this parameter is set to 0, the user must define the timeout period range (2^8 to 2^(WDT_CNT_WIDTH)-1) using the WDT_USER_TOP_(i) parameter. Values: ■ 0x0 (USERDEFINED): User must define timeout values ■ 0x1 (PREDEFINED): Use predefined timeout values Value After Reset: WDT_USE_FIX_TOP Exists: Always*/
#define WDT_WDT_USE_FIX_TOP      WDT_WDT_USE_FIX_TOP_MSK
#define WDT_WDT_USE_FIX_TOP_W(X) ((X) << WDT_WDT_USE_FIX_TOP_POS)
#define WDT_WDT_PAUSE_POS        (7U)
#define WDT_WDT_PAUSE_MSK \
    (0x1UL                \
     << WDT_WDT_PAUSE_POS) /*!< Configures the peripheral to have a pause enable signal (pause) on the interface that can be used to freeze the watchdog counter during pause mode. Values: ■ 0x0 (DISABLED): Pause enable signal is non existent ■ 0x1 (ENABLED): Pause enable signal is included Value After Reset: WDT_PAUSE Exists: Always*/
#define WDT_WDT_PAUSE          WDT_WDT_PAUSE_MSK
#define WDT_WDT_PAUSE_W(X)     ((X) << WDT_WDT_PAUSE_POS)
#define WDT_APB_DATA_WIDTH_POS (8U)
#define WDT_APB_DATA_WIDTH_MSK \
    (0x3UL                     \
     << WDT_APB_DATA_WIDTH_POS) /*!< Width of the APB Data Bus to which this component is attached. Values: ■ 0x0 (APB_8BITS): APB data width is 8 bits ■ 0x1 (APB_16BITS): APB data width is 16 bits ■ 0x2 (APB_32BITS): APB data width is 32 bits Value After Reset: "((APB_DATA_WIDTH==8) ? 0 : ((APB_DATA_WIDTH==16) ? 1 :2 ))" Exists: Always*/
#define WDT_APB_DATA_WIDTH      WDT_APB_DATA_WIDTH_MSK
#define WDT_APB_DATA_WIDTH_W(X) ((X) << WDT_APB_DATA_WIDTH_POS)
#define WDT_WDT_DFLT_RPL_POS    (10U)
#define WDT_WDT_DFLT_RPL_MSK    (0x7UL << WDT_WDT_DFLT_RPL_POS) /*!< The reset pulse length that is available directly after reset. Value After Reset: WDT_DFLT_RPL Exists: Always*/
#define WDT_WDT_DFLT_RPL        WDT_WDT_DFLT_RPL_MSK
#define WDT_WDT_DFLT_RPL_W(X)   ((X) << WDT_WDT_DFLT_RPL_POS)
#define WDT_RSVD_15_13_POS      (13U)
#define WDT_RSVD_15_13_MSK      (0x7UL << WDT_RSVD_15_13_POS) /*!< WDT_COMP_PARAM_1[15:13] Reserved bits and read as zero (0). Value After Reset: 0x0 Exists: Always*/
#define WDT_RSVD_15_13          WDT_RSVD_15_13_MSK
#define WDT_RSVD_15_13_W(X)     ((X) << WDT_RSVD_15_13_POS)
#define WDT_WDT_DFLT_TOP_POS    (16U)
#define WDT_WDT_DFLT_TOP_MSK \
    (0xfUL                   \
     << WDT_WDT_DFLT_TOP_POS) /*!< Selects the timeout period that is available directly after reset. It controls the reset value of the register. If WDT_HC_TOP is set to 1, then the default timeout period is the only possible timeout period. Can choose one of 16 values. Value After Reset: WDT_DFLT_TOP Exists: Always*/
#define WDT_WDT_DFLT_TOP          WDT_WDT_DFLT_TOP_MSK
#define WDT_WDT_DFLT_TOP_W(X)     ((X) << WDT_WDT_DFLT_TOP_POS)
#define WDT_WDT_DFLT_TOP_INIT_POS (20U)
#define WDT_WDT_DFLT_TOP_INIT_MSK \
    (0xfUL                        \
     << WDT_WDT_DFLT_TOP_INIT_POS) /*!< Describes the initial timeout period that is available directly after reset. It controls the reset value of the register. If WDT_HC_TOP is 1, then the default initial time period is the only possible period. Value After Reset: WDT_DFLT_TOP_INIT Exists: Always*/
#define WDT_WDT_DFLT_TOP_INIT      WDT_WDT_DFLT_TOP_INIT_MSK
#define WDT_WDT_DFLT_TOP_INIT_W(X) ((X) << WDT_WDT_DFLT_TOP_INIT_POS)
#define WDT_WDT_CNT_WIDTH_POS      (24U)
#define WDT_WDT_CNT_WIDTH_MSK      (0x1fUL << WDT_WDT_CNT_WIDTH_POS) /*!< The Watchdog Timer counter width. Value After Reset: "(WDT_CNT_WIDTH-16)" Exists: Always*/
#define WDT_WDT_CNT_WIDTH          WDT_WDT_CNT_WIDTH_MSK
#define WDT_WDT_CNT_WIDTH_W(X)     ((X) << WDT_WDT_CNT_WIDTH_POS)
#define WDT_RSVD_31_29_POS         (29U)
#define WDT_RSVD_31_29_MSK         (0x7UL << WDT_RSVD_31_29_POS) /*!< WDT_COMP_PARAM_1[31:29]Reserved bits and read as zero (0). Value After Reset: 0x0 Exists: Always*/
#define WDT_RSVD_31_29             WDT_RSVD_31_29_MSK
#define WDT_RSVD_31_29_W(X)        ((X) << WDT_RSVD_31_29_POS)

//WDT_COMP_VERSION offsetaddress : 0xf8
#define WDT_WDT_COMP_VERSION_POS  (0U)
#define WDT_WDT_COMP_VERSION_MSK  (0xffffffffUL << WDT_WDT_COMP_VERSION_POS) /*!< ASCII value for each number in the version, followed by *. For example, 32_30_31_2A represents the version 2.01*. Exists: Always*/
#define WDT_WDT_COMP_VERSION      WDT_WDT_COMP_VERSION_MSK
#define WDT_WDT_COMP_VERSION_W(X) ((X) << WDT_WDT_COMP_VERSION_POS)

//WDT_COMP_TYPE offsetaddress : 0xfc
#define WDT_WDT_COMP_TYPE_POS  (0U)
#define WDT_WDT_COMP_TYPE_MSK  (0xffffffffUL << WDT_WDT_COMP_TYPE_POS) /*!< Designware Component Type number = 0x44_57_01_20. This assigned unique hex value is constant, and is derived from the two ASCII letters "DW" followed by a 16-bit unsigned number. Exists: Always*/
#define WDT_WDT_COMP_TYPE      WDT_WDT_COMP_TYPE_MSK
#define WDT_WDT_COMP_TYPE_W(X) ((X) << WDT_WDT_COMP_TYPE_POS)

typedef struct {
    volatile uint32_t CR;   //offsetaddress : 0x0
    volatile uint32_t TORR; //offsetaddress : 0x4
    volatile uint32_t CCVR; //offsetaddress : 0x8
    volatile uint32_t CRR;  //offsetaddress : 0xc
    volatile uint32_t STAT; //offsetaddress : 0x10
    volatile uint32_t EOI;  //offsetaddress : 0x14
    volatile uint32_t rev_0[(0x1C - 0x14) / 4 - 1];
    volatile uint32_t PROT_LEVEL; /* offset 0x001C */
    volatile uint32_t rev_1[(0xE4 - 0x1C) / 4 - 1];
    volatile uint32_t COMP_PARAM_5; //offsetaddress : 0xe4
    volatile uint32_t COMP_PARAM_4; //offsetaddress : 0xe8
    volatile uint32_t COMP_PARAM_3; //offsetaddress : 0xec
    volatile uint32_t COMP_PARAM_2; //offsetaddress : 0xf0
    volatile uint32_t COMP_PARAM_1; //offsetaddress : 0xf4
    volatile uint32_t COMP_VERSION; //offsetaddress : 0xf8
    volatile uint32_t COMP_TYPE;    //offsetaddress : 0xfc
} wdt_reg_t;
#ifdef __cplusplus
}
#endif
#endif
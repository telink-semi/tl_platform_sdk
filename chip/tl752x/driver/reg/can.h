/*******************************************************************************************************
 *
 * @file    can.h
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
#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint32_t CAN_MCR                   ;//offsetaddress : 0x0
    volatile uint32_t CAN_CTRL1                 ;//offsetaddress : 0x4
    volatile uint32_t CAN_TIMER                 ;//offsetaddress : 0x8
    volatile uint32_t rev_1;                    ;//offsetaddress : 0xc
    volatile uint32_t CANCAN_RXMGMASK           ;//offsetaddress : 0x10
    volatile uint32_t CANCAN_RX14MASK           ;//offsetaddress : 0x14
    volatile uint32_t CANCAN_RX15MASK           ;//offsetaddress : 0x18
    volatile uint32_t CAN_ECR                   ;//offsetaddress : 0x1c
    volatile uint32_t CAN_ESR1                  ;//offsetaddress : 0x20
    volatile uint32_t CAN_IMASK2                ;//offsetaddress : 0x24
    volatile uint32_t CAN_IMASK1                ;//offsetaddress : 0x28
    volatile uint32_t CAN_IFLAG2                ;//offsetaddress : 0x2c
    volatile uint32_t CAN_IFLAG1                ;//offsetaddress : 0x30
    volatile uint32_t CAN_CTRL2                 ;//offsetaddress : 0x34
    volatile uint32_t CAN_ESR2                  ;//offsetaddress : 0x38
    volatile uint32_t rev_2[(0x0044 - 0x0038) / 4 - 1];
    volatile uint32_t CAN_CRCR                  ;//offsetaddress : 0x44
    volatile uint32_t CAN_RXFGMASK              ;//offsetaddress : 0x48
    volatile uint32_t CAN_RXFIR                 ;//offsetaddress : 0x4c
    volatile uint32_t CAN_CBT                   ;//offsetaddress : 0x50
    volatile uint32_t rev_3[(0x0068 - 0x0050) / 4 - 1];
    volatile uint32_t CAN_IMASK4                ;//offsetaddress : 0x68
    volatile uint32_t CAN_IMASK3                ;//offsetaddress : 0x6c
    volatile uint32_t CAN_IFLAG4                ;//offsetaddress : 0x70
    volatile uint32_t CAN_IFLAG3                ;//offsetaddress : 0x74
    volatile uint32_t rev_4[(0x0880 - 0x0074) / 4 - 1];
    volatile uint32_t CAN_RXIMRn[128]           ;//offsetaddress : 0x880 - 0xa7c
    volatile uint32_t rev_5[(0x0ae0 - 0x0a7c) / 4 - 1];
    volatile uint32_t CAN_MECR                  ;//offsetaddress : 0xae0
    volatile uint32_t CAN_ERRIAR                ;//offsetaddress : 0xae4
    volatile uint32_t CAN_ERRIDPR               ;//offsetaddress : 0xae8
    volatile uint32_t CAN_ERRIPPR               ;//offsetaddress : 0xaec
    volatile uint32_t CAN_RERRAR                ;//offsetaddress : 0xaf0
    volatile uint32_t CAN_RERRDR                ;//offsetaddress : 0xaf4
    volatile uint32_t CAN_RERRSYNR              ;//offsetaddress : 0xaf8
    volatile uint32_t CAN_ERCAN_ERRSR           ;//offsetaddress : 0xafc
    volatile uint32_t CAN_CTRL1_PN              ;//offsetaddress : 0xb00
    volatile uint32_t CAN_CTRL2_PN              ;//offsetaddress : 0xb04
    volatile uint32_t CAN_WU_MTC                ;//offsetaddress : 0xb08
    volatile uint32_t CAN_FLT_ID1               ;//offsetaddress : 0xb0c
    volatile uint32_t CAN_FLT_DLC               ;//offsetaddress : 0xb10
    volatile uint32_t CAN_PL1_LO                ;//offsetaddress : 0xb14
    volatile uint32_t CAN_PL1_HI                ;//offsetaddress : 0xb18
    volatile uint32_t CAN_FLT_ID2_IDMASK        ;//offsetaddress : 0xb1c
    volatile uint32_t CAN_PL2_PLMASK_LO         ;//offsetaddress : 0xb20
    volatile uint32_t CAN_PL2_PLMASK_HI         ;//offsetaddress : 0xb24
    volatile uint32_t rev_6[(0x0b40 - 0x0b24) / 4 - 1];
    volatile uint32_t CAN_WMB0_CS               ;//offsetaddress : 0xb40
    volatile uint32_t CAN_WMB0_ID               ;//offsetaddress : 0xb44
    volatile uint32_t CAN_WMB0_D03              ;//offsetaddress : 0xb48
    volatile uint32_t CAN_WMB0_D47              ;//offsetaddress : 0xb4c
    volatile uint32_t CAN_WMB1_CS               ;//offsetaddress : 0xb50
    volatile uint32_t CAN_WMB1_ID               ;//offsetaddress : 0xb54
    volatile uint32_t CAN_WMB1_D03              ;//offsetaddress : 0xb58
    volatile uint32_t CAN_WMB1_D47              ;//offsetaddress : 0xb5c
    volatile uint32_t CAN_WMB2_CS               ;//offsetaddress : 0xb60
    volatile uint32_t CAN_WMB2_ID               ;//offsetaddress : 0xb64
    volatile uint32_t CAN_WMB2_D03              ;//offsetaddress : 0xb68
    volatile uint32_t CAN_WMB2_D47              ;//offsetaddress : 0xb6c
    volatile uint32_t CAN_WMB3_CS               ;//offsetaddress : 0xb70
    volatile uint32_t CAN_WMB3_ID               ;//offsetaddress : 0xb74
    volatile uint32_t CAN_WMB3_D03              ;//offsetaddress : 0xb78
    volatile uint32_t CAN_WMB3_D47              ;//offsetaddress : 0xb7c
    volatile uint32_t rev_7[(0x0bf0 - 0x0b7c) / 4 - 1];
    volatile uint32_t CAN_EPRS                  ;//offsetaddress : 0xbf0
    volatile uint32_t CAN_ENCBT                 ;//offsetaddress : 0xbf4
    volatile uint32_t CAN_ECAN_EDCBT            ;//offsetaddress : 0xbf8
    volatile uint32_t CAN_ETDC                  ;//offsetaddress : 0xbfc
    volatile uint32_t CAN_FDCTRL                ;//offsetaddress : 0xc00
    volatile uint32_t CAN_FDCBT                 ;//offsetaddress : 0xc04
    volatile uint32_t CAN_FDCRC                 ;//offsetaddress : 0xc08
    volatile uint32_t CAN_ERFCR                 ;//offsetaddress : 0xc0c
    volatile uint32_t CAN_ERFIER                ;//offsetaddress : 0xc10
    volatile uint32_t CAN_ERFSR                 ;//offsetaddress : 0xc14
    volatile uint32_t rev_8[(0x0c30 - 0x0c14) / 4 - 1];
    volatile uint32_t CAN_HR_TIME_STAMPn[128]   ;//offsetaddress : 0xc30 - 0xe2c
    volatile uint32_t rev_9[(0x3000 - 0x0e2c) / 4 - 1];
    volatile uint32_t CAN_ERFFELn[128]          ;//offsetaddress : 0x3000 - 0x31fc
} can_reg_t ;

#ifdef __cplusplus
}
#endif
#endif

/*******************************************************************************************************
 *
 * @file    music.h
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
#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//MUSIC_CTRL offsetaddress : 0x000
//MUSIC_CTRL RegResetValue : 0xc000c
#define MUSIC_AL_MUSIC_EN_POS            (0U)
#define MUSIC_AL_MUSIC_EN_MSK            (0x1UL << MUSIC_AL_MUSIC_EN_POS) /*!< */
#define MUSIC_AL_MUSIC_EN                MUSIC_AL_MUSIC_EN_MSK
#define MUSIC_AL_MUSIC_EN_W(X)           ((X) << MUSIC_AL_MUSIC_EN_POS)
#define MUSIC_AL_MUSIC_96K_EN_POS        (1U)
#define MUSIC_AL_MUSIC_96K_EN_MSK        (0x1UL << MUSIC_AL_MUSIC_96K_EN_POS) /*!< */
#define MUSIC_AL_MUSIC_96K_EN            MUSIC_AL_MUSIC_96K_EN_MSK
#define MUSIC_AL_MUSIC_96K_EN_W(X)       ((X) << MUSIC_AL_MUSIC_96K_EN_POS)
#define MUSIC_AL_MUSIC_RATE_POS          (2U)
#define MUSIC_AL_MUSIC_RATE_MSK          (0x3UL << MUSIC_AL_MUSIC_RATE_POS) /*!< */
#define MUSIC_AL_MUSIC_RATE              MUSIC_AL_MUSIC_RATE_MSK
#define MUSIC_AL_MUSIC_RATE_W(X)         ((X) << MUSIC_AL_MUSIC_RATE_POS)
#define MUSIC_AL_MUSIC_FADE_SEL_POS      (4U)
#define MUSIC_AL_MUSIC_FADE_SEL_MSK      (0x1UL << MUSIC_AL_MUSIC_FADE_SEL_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_SEL          MUSIC_AL_MUSIC_FADE_SEL_MSK
#define MUSIC_AL_MUSIC_FADE_SEL_W(X)     ((X) << MUSIC_AL_MUSIC_FADE_SEL_POS)
#define MUSIC_AL_MUSIC_INT_BYPASS_POS    (5U)
#define MUSIC_AL_MUSIC_INT_BYPASS_MSK    (0x1UL << MUSIC_AL_MUSIC_INT_BYPASS_POS) /*!< */
#define MUSIC_AL_MUSIC_INT_BYPASS        MUSIC_AL_MUSIC_INT_BYPASS_MSK
#define MUSIC_AL_MUSIC_INT_BYPASS_W(X)   ((X) << MUSIC_AL_MUSIC_INT_BYPASS_POS)
#define MUSIC_AL_MUSIC_INT_RATE_OW_POS   (6U)
#define MUSIC_AL_MUSIC_INT_RATE_OW_MSK   (0x1UL << MUSIC_AL_MUSIC_INT_RATE_OW_POS) /*!< */
#define MUSIC_AL_MUSIC_INT_RATE_OW       MUSIC_AL_MUSIC_INT_RATE_OW_MSK
#define MUSIC_AL_MUSIC_INT_RATE_OW_W(X)  ((X) << MUSIC_AL_MUSIC_INT_RATE_OW_POS)
#define MUSIC_AL_MUSIC_INT_RATE_VAL_POS  (7U)
#define MUSIC_AL_MUSIC_INT_RATE_VAL_MSK  (0x3UL << MUSIC_AL_MUSIC_INT_RATE_VAL_POS) /*!< */
#define MUSIC_AL_MUSIC_INT_RATE_VAL      MUSIC_AL_MUSIC_INT_RATE_VAL_MSK
#define MUSIC_AL_MUSIC_INT_RATE_VAL_W(X) ((X) << MUSIC_AL_MUSIC_INT_RATE_VAL_POS)
#define MUSIC_AR_MUSIC_EN_POS            (16U)
#define MUSIC_AR_MUSIC_EN_MSK            (0x1UL << MUSIC_AR_MUSIC_EN_POS) /*!< */
#define MUSIC_AR_MUSIC_EN                MUSIC_AR_MUSIC_EN_MSK
#define MUSIC_AR_MUSIC_EN_W(X)           ((X) << MUSIC_AR_MUSIC_EN_POS)
#define MUSIC_AR_MUSIC_96K_EN_POS        (17U)
#define MUSIC_AR_MUSIC_96K_EN_MSK        (0x1UL << MUSIC_AR_MUSIC_96K_EN_POS) /*!< */
#define MUSIC_AR_MUSIC_96K_EN            MUSIC_AR_MUSIC_96K_EN_MSK
#define MUSIC_AR_MUSIC_96K_EN_W(X)       ((X) << MUSIC_AR_MUSIC_96K_EN_POS)
#define MUSIC_AR_MUSIC_RATE_POS          (18U)
#define MUSIC_AR_MUSIC_RATE_MSK          (0x3UL << MUSIC_AR_MUSIC_RATE_POS) /*!< */
#define MUSIC_AR_MUSIC_RATE              MUSIC_AR_MUSIC_RATE_MSK
#define MUSIC_AR_MUSIC_RATE_W(X)         ((X) << MUSIC_AR_MUSIC_RATE_POS)
#define MUSIC_AR_MUSIC_FADE_SEL_POS      (20U)
#define MUSIC_AR_MUSIC_FADE_SEL_MSK      (0x1UL << MUSIC_AR_MUSIC_FADE_SEL_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_SEL          MUSIC_AR_MUSIC_FADE_SEL_MSK
#define MUSIC_AR_MUSIC_FADE_SEL_W(X)     ((X) << MUSIC_AR_MUSIC_FADE_SEL_POS)
#define MUSIC_AR_MUSIC_INT_BYPASS_POS    (21U)
#define MUSIC_AR_MUSIC_INT_BYPASS_MSK    (0x1UL << MUSIC_AR_MUSIC_INT_BYPASS_POS) /*!< */
#define MUSIC_AR_MUSIC_INT_BYPASS        MUSIC_AR_MUSIC_INT_BYPASS_MSK
#define MUSIC_AR_MUSIC_INT_BYPASS_W(X)   ((X) << MUSIC_AR_MUSIC_INT_BYPASS_POS)
#define MUSIC_AR_MUSIC_INT_RATE_OW_POS   (22U)
#define MUSIC_AR_MUSIC_INT_RATE_OW_MSK   (0x1UL << MUSIC_AR_MUSIC_INT_RATE_OW_POS) /*!< */
#define MUSIC_AR_MUSIC_INT_RATE_OW       MUSIC_AR_MUSIC_INT_RATE_OW_MSK
#define MUSIC_AR_MUSIC_INT_RATE_OW_W(X)  ((X) << MUSIC_AR_MUSIC_INT_RATE_OW_POS)
#define MUSIC_AR_MUSIC_INT_RATE_VAL_POS  (23U)
#define MUSIC_AR_MUSIC_INT_RATE_VAL_MSK  (0x3UL << MUSIC_AR_MUSIC_INT_RATE_VAL_POS) /*!< */
#define MUSIC_AR_MUSIC_INT_RATE_VAL      MUSIC_AR_MUSIC_INT_RATE_VAL_MSK
#define MUSIC_AR_MUSIC_INT_RATE_VAL_W(X) ((X) << MUSIC_AR_MUSIC_INT_RATE_VAL_POS)

//ASRC_COMMON offsetaddress : 0x004
//ASRC_COMMON RegResetValue : 0xa02
#define MUSIC_ASRC_ENABLE_POS    (0U)
#define MUSIC_ASRC_ENABLE_MSK    (0x1UL << MUSIC_ASRC_ENABLE_POS) /*!< */
#define MUSIC_ASRC_ENABLE        MUSIC_ASRC_ENABLE_MSK
#define MUSIC_ASRC_ENABLE_W(X)   ((X) << MUSIC_ASRC_ENABLE_POS)
#define MUSIC_ASRC_BYPASS_POS    (1U)
#define MUSIC_ASRC_BYPASS_MSK    (0x1UL << MUSIC_ASRC_BYPASS_POS) /*!< */
#define MUSIC_ASRC_BYPASS        MUSIC_ASRC_BYPASS_MSK
#define MUSIC_ASRC_BYPASS_W(X)   ((X) << MUSIC_ASRC_BYPASS_POS)
#define MUSIC_ASRC_FERR_POS      (2U)
#define MUSIC_ASRC_FERR_MSK      (0x7fUL << MUSIC_ASRC_FERR_POS) /*!< */
#define MUSIC_ASRC_FERR          MUSIC_ASRC_FERR_MSK
#define MUSIC_ASRC_FERR_W(X)     ((X) << MUSIC_ASRC_FERR_POS)
#define MUSIC_ASRC_WAIT_CNT_POS  (9U)
#define MUSIC_ASRC_WAIT_CNT_MSK  (0x3fUL << MUSIC_ASRC_WAIT_CNT_POS) /*!< */
#define MUSIC_ASRC_WAIT_CNT      MUSIC_ASRC_WAIT_CNT_MSK
#define MUSIC_ASRC_WAIT_CNT_W(X) ((X) << MUSIC_ASRC_WAIT_CNT_POS)

//ASRC_L offsetaddress : 0x008
//ASRC_L RegResetValue : 0xc00000
#define MUSIC_AL_FERR_SEL_POS        (0U)
#define MUSIC_AL_FERR_SEL_MSK        (0x1UL << MUSIC_AL_FERR_SEL_POS) /*!< */
#define MUSIC_AL_FERR_SEL            MUSIC_AL_FERR_SEL_MSK
#define MUSIC_AL_FERR_SEL_W(X)       ((X) << MUSIC_AL_FERR_SEL_POS)
#define MUSIC_AL_FERR_EXPAND_POS     (1U)
#define MUSIC_AL_FERR_EXPAND_MSK     (0x7ffUL << MUSIC_AL_FERR_EXPAND_POS) /*!< */
#define MUSIC_AL_FERR_EXPAND         MUSIC_AL_FERR_EXPAND_MSK
#define MUSIC_AL_FERR_EXPAND_W(X)    ((X) << MUSIC_AL_FERR_EXPAND_POS)
#define MUSIC_ASRC_L_FIFO_STATUS_POS (16U)
#define MUSIC_ASRC_L_FIFO_STATUS_MSK \
    (0xffUL << MUSIC_ASRC_L_FIFO_STATUS_POS) /*!< asrc_l_fifo_status[7]=push_empty asrc_l_fifo_status[6]=push_ae asrc_l_fifo_status[5]=push_full asrc_l_fifo_status[4]=push_error asrc_l_fifo_status[3]=pop_hf asrc_l_fifo_status[2]=pop_af asrc_l_fifo_status[1]=pop_full asrc_l_fifo_status[0]=pop_error*/
#define MUSIC_ASRC_L_FIFO_STATUS      MUSIC_ASRC_L_FIFO_STATUS_MSK
#define MUSIC_ASRC_L_FIFO_STATUS_W(X) ((X) << MUSIC_ASRC_L_FIFO_STATUS_POS)

//ASRC_R offsetaddress : 0x00c
//ASRC_R RegResetValue : 0xc00000
#define MUSIC_AR_FERR_SEL_POS        (0U)
#define MUSIC_AR_FERR_SEL_MSK        (0x1UL << MUSIC_AR_FERR_SEL_POS) /*!< */
#define MUSIC_AR_FERR_SEL            MUSIC_AR_FERR_SEL_MSK
#define MUSIC_AR_FERR_SEL_W(X)       ((X) << MUSIC_AR_FERR_SEL_POS)
#define MUSIC_AR_FERR_EXPAND_POS     (1U)
#define MUSIC_AR_FERR_EXPAND_MSK     (0x7ffUL << MUSIC_AR_FERR_EXPAND_POS) /*!< */
#define MUSIC_AR_FERR_EXPAND         MUSIC_AR_FERR_EXPAND_MSK
#define MUSIC_AR_FERR_EXPAND_W(X)    ((X) << MUSIC_AR_FERR_EXPAND_POS)
#define MUSIC_ASRC_R_FIFO_STATUS_POS (16U)
#define MUSIC_ASRC_R_FIFO_STATUS_MSK \
    (0xffUL << MUSIC_ASRC_R_FIFO_STATUS_POS) /*!< asrc_r_fifo_status[7]=push_empty asrc_r_fifo_status[6]=push_ae asrc_r_fifo_status[5]=push_full asrc_r_fifo_status[4]=push_error asrc_r_fifo_status[3]=pop_hf asrc_r_fifo_status[2]=pop_af asrc_r_fifo_status[1]=pop_full asrc_r_fifo_status[0]=pop_error*/
#define MUSIC_ASRC_R_FIFO_STATUS      MUSIC_ASRC_R_FIFO_STATUS_MSK
#define MUSIC_ASRC_R_FIFO_STATUS_W(X) ((X) << MUSIC_ASRC_R_FIFO_STATUS_POS)

//EQ_CTRL offsetaddress : 0x010
//EQ_CTRL RegResetValue : 0x9120912
#define MUSIC_AL_EQ_EN_POS             (0U)
#define MUSIC_AL_EQ_EN_MSK             (0x1UL << MUSIC_AL_EQ_EN_POS) /*!< */
#define MUSIC_AL_EQ_EN                 MUSIC_AL_EQ_EN_MSK
#define MUSIC_AL_EQ_EN_W(X)            ((X) << MUSIC_AL_EQ_EN_POS)
#define MUSIC_AL_EQ_IIR_ORDER_SEL_POS  (1U)
#define MUSIC_AL_EQ_IIR_ORDER_SEL_MSK  (0x1fUL << MUSIC_AL_EQ_IIR_ORDER_SEL_POS) /*!< */
#define MUSIC_AL_EQ_IIR_ORDER_SEL      MUSIC_AL_EQ_IIR_ORDER_SEL_MSK
#define MUSIC_AL_EQ_IIR_ORDER_SEL_W(X) ((X) << MUSIC_AL_EQ_IIR_ORDER_SEL_POS)
#define MUSIC_AL_EQ_IIR_SEL_POS        (6U)
#define MUSIC_AL_EQ_IIR_SEL_MSK        (0x7UL << MUSIC_AL_EQ_IIR_SEL_POS) /*!< */
#define MUSIC_AL_EQ_IIR_SEL            MUSIC_AL_EQ_IIR_SEL_MSK
#define MUSIC_AL_EQ_IIR_SEL_W(X)       ((X) << MUSIC_AL_EQ_IIR_SEL_POS)
#define MUSIC_AL_EQ_IIR_FB_POS         (9U)
#define MUSIC_AL_EQ_IIR_FB_MSK         (0x7UL << MUSIC_AL_EQ_IIR_FB_POS) /*!< */
#define MUSIC_AL_EQ_IIR_FB             MUSIC_AL_EQ_IIR_FB_MSK
#define MUSIC_AL_EQ_IIR_FB_W(X)        ((X) << MUSIC_AL_EQ_IIR_FB_POS)
#define MUSIC_AR_EQ_EN_POS             (16U)
#define MUSIC_AR_EQ_EN_MSK             (0x1UL << MUSIC_AR_EQ_EN_POS) /*!< */
#define MUSIC_AR_EQ_EN                 MUSIC_AR_EQ_EN_MSK
#define MUSIC_AR_EQ_EN_W(X)            ((X) << MUSIC_AR_EQ_EN_POS)
#define MUSIC_AR_EQ_IIR_ORDER_SEL_POS  (17U)
#define MUSIC_AR_EQ_IIR_ORDER_SEL_MSK  (0x1fUL << MUSIC_AR_EQ_IIR_ORDER_SEL_POS) /*!< */
#define MUSIC_AR_EQ_IIR_ORDER_SEL      MUSIC_AR_EQ_IIR_ORDER_SEL_MSK
#define MUSIC_AR_EQ_IIR_ORDER_SEL_W(X) ((X) << MUSIC_AR_EQ_IIR_ORDER_SEL_POS)
#define MUSIC_AR_EQ_IIR_SEL_POS        (22U)
#define MUSIC_AR_EQ_IIR_SEL_MSK        (0x7UL << MUSIC_AR_EQ_IIR_SEL_POS) /*!< */
#define MUSIC_AR_EQ_IIR_SEL            MUSIC_AR_EQ_IIR_SEL_MSK
#define MUSIC_AR_EQ_IIR_SEL_W(X)       ((X) << MUSIC_AR_EQ_IIR_SEL_POS)
#define MUSIC_AR_EQ_IIR_FB_POS         (25U)
#define MUSIC_AR_EQ_IIR_FB_MSK         (0x7UL << MUSIC_AR_EQ_IIR_FB_POS) /*!< */
#define MUSIC_AR_EQ_IIR_FB             MUSIC_AR_EQ_IIR_FB_MSK
#define MUSIC_AR_EQ_IIR_FB_W(X)        ((X) << MUSIC_AR_EQ_IIR_FB_POS)

//EQ_L_S0_B0 offsetaddress : 0x014
//EQ_L_S0_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S0_B0_POS  (0U)
#define MUSIC_AL_EQ_S0_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S0_B0_POS) /*!< */
#define MUSIC_AL_EQ_S0_B0      MUSIC_AL_EQ_S0_B0_MSK
#define MUSIC_AL_EQ_S0_B0_W(X) ((X) << MUSIC_AL_EQ_S0_B0_POS)

//EQ_L_S0_B1 offsetaddress : 0x018
//EQ_L_S0_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S0_B1_POS  (0U)
#define MUSIC_AL_EQ_S0_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S0_B1_POS) /*!< */
#define MUSIC_AL_EQ_S0_B1      MUSIC_AL_EQ_S0_B1_MSK
#define MUSIC_AL_EQ_S0_B1_W(X) ((X) << MUSIC_AL_EQ_S0_B1_POS)

//EQ_L_S0_B2 offsetaddress : 0x01c
//EQ_L_S0_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S0_B2_POS  (0U)
#define MUSIC_AL_EQ_S0_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S0_B2_POS) /*!< */
#define MUSIC_AL_EQ_S0_B2      MUSIC_AL_EQ_S0_B2_MSK
#define MUSIC_AL_EQ_S0_B2_W(X) ((X) << MUSIC_AL_EQ_S0_B2_POS)

//EQ_L_S0_A1 offsetaddress : 0x020
//EQ_L_S0_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S0_A1_POS  (0U)
#define MUSIC_AL_EQ_S0_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S0_A1_POS) /*!< */
#define MUSIC_AL_EQ_S0_A1      MUSIC_AL_EQ_S0_A1_MSK
#define MUSIC_AL_EQ_S0_A1_W(X) ((X) << MUSIC_AL_EQ_S0_A1_POS)

//EQ_L_S0_A2 offsetaddress : 0x024
//EQ_L_S0_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S0_A2_POS  (0U)
#define MUSIC_AL_EQ_S0_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S0_A2_POS) /*!< */
#define MUSIC_AL_EQ_S0_A2      MUSIC_AL_EQ_S0_A2_MSK
#define MUSIC_AL_EQ_S0_A2_W(X) ((X) << MUSIC_AL_EQ_S0_A2_POS)

//EQ_L_S1_B0 offsetaddress : 0x028
//EQ_L_S1_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S1_B0_POS  (0U)
#define MUSIC_AL_EQ_S1_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S1_B0_POS) /*!< */
#define MUSIC_AL_EQ_S1_B0      MUSIC_AL_EQ_S1_B0_MSK
#define MUSIC_AL_EQ_S1_B0_W(X) ((X) << MUSIC_AL_EQ_S1_B0_POS)

//EQ_L_S1_B1 offsetaddress : 0x02c
//EQ_L_S1_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S1_B1_POS  (0U)
#define MUSIC_AL_EQ_S1_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S1_B1_POS) /*!< */
#define MUSIC_AL_EQ_S1_B1      MUSIC_AL_EQ_S1_B1_MSK
#define MUSIC_AL_EQ_S1_B1_W(X) ((X) << MUSIC_AL_EQ_S1_B1_POS)

//EQ_L_S1_B2 offsetaddress : 0x030
//EQ_L_S1_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S1_B2_POS  (0U)
#define MUSIC_AL_EQ_S1_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S1_B2_POS) /*!< */
#define MUSIC_AL_EQ_S1_B2      MUSIC_AL_EQ_S1_B2_MSK
#define MUSIC_AL_EQ_S1_B2_W(X) ((X) << MUSIC_AL_EQ_S1_B2_POS)

//EQ_L_S1_A1 offsetaddress : 0x034
//EQ_L_S1_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S1_A1_POS  (0U)
#define MUSIC_AL_EQ_S1_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S1_A1_POS) /*!< */
#define MUSIC_AL_EQ_S1_A1      MUSIC_AL_EQ_S1_A1_MSK
#define MUSIC_AL_EQ_S1_A1_W(X) ((X) << MUSIC_AL_EQ_S1_A1_POS)

//EQ_L_S1_A2 offsetaddress : 0x038
//EQ_L_S1_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S1_A2_POS  (0U)
#define MUSIC_AL_EQ_S1_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S1_A2_POS) /*!< */
#define MUSIC_AL_EQ_S1_A2      MUSIC_AL_EQ_S1_A2_MSK
#define MUSIC_AL_EQ_S1_A2_W(X) ((X) << MUSIC_AL_EQ_S1_A2_POS)

//EQ_L_S2_B0 offsetaddress : 0x03c
//EQ_L_S2_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S2_B0_POS  (0U)
#define MUSIC_AL_EQ_S2_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S2_B0_POS) /*!< */
#define MUSIC_AL_EQ_S2_B0      MUSIC_AL_EQ_S2_B0_MSK
#define MUSIC_AL_EQ_S2_B0_W(X) ((X) << MUSIC_AL_EQ_S2_B0_POS)

//EQ_L_S2_B1 offsetaddress : 0x040
//EQ_L_S2_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S2_B1_POS  (0U)
#define MUSIC_AL_EQ_S2_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S2_B1_POS) /*!< */
#define MUSIC_AL_EQ_S2_B1      MUSIC_AL_EQ_S2_B1_MSK
#define MUSIC_AL_EQ_S2_B1_W(X) ((X) << MUSIC_AL_EQ_S2_B1_POS)

//EQ_L_S2_B2 offsetaddress : 0x044
//EQ_L_S2_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S2_B2_POS  (0U)
#define MUSIC_AL_EQ_S2_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S2_B2_POS) /*!< */
#define MUSIC_AL_EQ_S2_B2      MUSIC_AL_EQ_S2_B2_MSK
#define MUSIC_AL_EQ_S2_B2_W(X) ((X) << MUSIC_AL_EQ_S2_B2_POS)

//EQ_L_S2_A1 offsetaddress : 0x048
//EQ_L_S2_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S2_A1_POS  (0U)
#define MUSIC_AL_EQ_S2_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S2_A1_POS) /*!< */
#define MUSIC_AL_EQ_S2_A1      MUSIC_AL_EQ_S2_A1_MSK
#define MUSIC_AL_EQ_S2_A1_W(X) ((X) << MUSIC_AL_EQ_S2_A1_POS)

//EQ_L_S2_A2 offsetaddress : 0x04c
//EQ_L_S2_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S2_A2_POS  (0U)
#define MUSIC_AL_EQ_S2_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S2_A2_POS) /*!< */
#define MUSIC_AL_EQ_S2_A2      MUSIC_AL_EQ_S2_A2_MSK
#define MUSIC_AL_EQ_S2_A2_W(X) ((X) << MUSIC_AL_EQ_S2_A2_POS)

//EQ_L_S3_B0 offsetaddress : 0x050
//EQ_L_S3_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S3_B0_POS  (0U)
#define MUSIC_AL_EQ_S3_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S3_B0_POS) /*!< */
#define MUSIC_AL_EQ_S3_B0      MUSIC_AL_EQ_S3_B0_MSK
#define MUSIC_AL_EQ_S3_B0_W(X) ((X) << MUSIC_AL_EQ_S3_B0_POS)

//EQ_L_S3_B1 offsetaddress : 0x054
//EQ_L_S3_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S3_B1_POS  (0U)
#define MUSIC_AL_EQ_S3_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S3_B1_POS) /*!< */
#define MUSIC_AL_EQ_S3_B1      MUSIC_AL_EQ_S3_B1_MSK
#define MUSIC_AL_EQ_S3_B1_W(X) ((X) << MUSIC_AL_EQ_S3_B1_POS)

//EQ_L_S3_B2 offsetaddress : 0x058
//EQ_L_S3_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S3_B2_POS  (0U)
#define MUSIC_AL_EQ_S3_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S3_B2_POS) /*!< */
#define MUSIC_AL_EQ_S3_B2      MUSIC_AL_EQ_S3_B2_MSK
#define MUSIC_AL_EQ_S3_B2_W(X) ((X) << MUSIC_AL_EQ_S3_B2_POS)

//EQ_L_S3_A1 offsetaddress : 0x05c
//EQ_L_S3_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S3_A1_POS  (0U)
#define MUSIC_AL_EQ_S3_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S3_A1_POS) /*!< */
#define MUSIC_AL_EQ_S3_A1      MUSIC_AL_EQ_S3_A1_MSK
#define MUSIC_AL_EQ_S3_A1_W(X) ((X) << MUSIC_AL_EQ_S3_A1_POS)

//EQ_L_S3_A2 offsetaddress : 0x060
//EQ_L_S3_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S3_A2_POS  (0U)
#define MUSIC_AL_EQ_S3_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S3_A2_POS) /*!< */
#define MUSIC_AL_EQ_S3_A2      MUSIC_AL_EQ_S3_A2_MSK
#define MUSIC_AL_EQ_S3_A2_W(X) ((X) << MUSIC_AL_EQ_S3_A2_POS)

//EQ_L_S4_B0 offsetaddress : 0x064
//EQ_L_S4_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S4_B0_POS  (0U)
#define MUSIC_AL_EQ_S4_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S4_B0_POS) /*!< */
#define MUSIC_AL_EQ_S4_B0      MUSIC_AL_EQ_S4_B0_MSK
#define MUSIC_AL_EQ_S4_B0_W(X) ((X) << MUSIC_AL_EQ_S4_B0_POS)

//EQ_L_S4_B1 offsetaddress : 0x068
//EQ_L_S4_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S4_B1_POS  (0U)
#define MUSIC_AL_EQ_S4_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S4_B1_POS) /*!< */
#define MUSIC_AL_EQ_S4_B1      MUSIC_AL_EQ_S4_B1_MSK
#define MUSIC_AL_EQ_S4_B1_W(X) ((X) << MUSIC_AL_EQ_S4_B1_POS)

//EQ_L_S4_B2 offsetaddress : 0x06c
//EQ_L_S4_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S4_B2_POS  (0U)
#define MUSIC_AL_EQ_S4_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S4_B2_POS) /*!< */
#define MUSIC_AL_EQ_S4_B2      MUSIC_AL_EQ_S4_B2_MSK
#define MUSIC_AL_EQ_S4_B2_W(X) ((X) << MUSIC_AL_EQ_S4_B2_POS)

//EQ_L_S4_A1 offsetaddress : 0x070
//EQ_L_S4_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S4_A1_POS  (0U)
#define MUSIC_AL_EQ_S4_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S4_A1_POS) /*!< */
#define MUSIC_AL_EQ_S4_A1      MUSIC_AL_EQ_S4_A1_MSK
#define MUSIC_AL_EQ_S4_A1_W(X) ((X) << MUSIC_AL_EQ_S4_A1_POS)

//EQ_L_S4_A2 offsetaddress : 0x074
//EQ_L_S4_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S4_A2_POS  (0U)
#define MUSIC_AL_EQ_S4_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S4_A2_POS) /*!< */
#define MUSIC_AL_EQ_S4_A2      MUSIC_AL_EQ_S4_A2_MSK
#define MUSIC_AL_EQ_S4_A2_W(X) ((X) << MUSIC_AL_EQ_S4_A2_POS)

//EQ_L_S5_B0 offsetaddress : 0x078
//EQ_L_S5_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S5_B0_POS  (0U)
#define MUSIC_AL_EQ_S5_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S5_B0_POS) /*!< */
#define MUSIC_AL_EQ_S5_B0      MUSIC_AL_EQ_S5_B0_MSK
#define MUSIC_AL_EQ_S5_B0_W(X) ((X) << MUSIC_AL_EQ_S5_B0_POS)

//EQ_L_S5_B1 offsetaddress : 0x07c
//EQ_L_S5_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S5_B1_POS  (0U)
#define MUSIC_AL_EQ_S5_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S5_B1_POS) /*!< */
#define MUSIC_AL_EQ_S5_B1      MUSIC_AL_EQ_S5_B1_MSK
#define MUSIC_AL_EQ_S5_B1_W(X) ((X) << MUSIC_AL_EQ_S5_B1_POS)

//EQ_L_S5_B2 offsetaddress : 0x080
//EQ_L_S5_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S5_B2_POS  (0U)
#define MUSIC_AL_EQ_S5_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S5_B2_POS) /*!< */
#define MUSIC_AL_EQ_S5_B2      MUSIC_AL_EQ_S5_B2_MSK
#define MUSIC_AL_EQ_S5_B2_W(X) ((X) << MUSIC_AL_EQ_S5_B2_POS)

//EQ_L_S5_A1 offsetaddress : 0x084
//EQ_L_S5_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S5_A1_POS  (0U)
#define MUSIC_AL_EQ_S5_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S5_A1_POS) /*!< */
#define MUSIC_AL_EQ_S5_A1      MUSIC_AL_EQ_S5_A1_MSK
#define MUSIC_AL_EQ_S5_A1_W(X) ((X) << MUSIC_AL_EQ_S5_A1_POS)

//EQ_L_S5_A2 offsetaddress : 0x088
//EQ_L_S5_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S5_A2_POS  (0U)
#define MUSIC_AL_EQ_S5_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S5_A2_POS) /*!< */
#define MUSIC_AL_EQ_S5_A2      MUSIC_AL_EQ_S5_A2_MSK
#define MUSIC_AL_EQ_S5_A2_W(X) ((X) << MUSIC_AL_EQ_S5_A2_POS)

//EQ_L_S6_B0 offsetaddress : 0x08c
//EQ_L_S6_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S6_B0_POS  (0U)
#define MUSIC_AL_EQ_S6_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S6_B0_POS) /*!< */
#define MUSIC_AL_EQ_S6_B0      MUSIC_AL_EQ_S6_B0_MSK
#define MUSIC_AL_EQ_S6_B0_W(X) ((X) << MUSIC_AL_EQ_S6_B0_POS)

//EQ_L_S6_B1 offsetaddress : 0x090
//EQ_L_S6_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S6_B1_POS  (0U)
#define MUSIC_AL_EQ_S6_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S6_B1_POS) /*!< */
#define MUSIC_AL_EQ_S6_B1      MUSIC_AL_EQ_S6_B1_MSK
#define MUSIC_AL_EQ_S6_B1_W(X) ((X) << MUSIC_AL_EQ_S6_B1_POS)

//EQ_L_S6_B2 offsetaddress : 0x094
//EQ_L_S6_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S6_B2_POS  (0U)
#define MUSIC_AL_EQ_S6_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S6_B2_POS) /*!< */
#define MUSIC_AL_EQ_S6_B2      MUSIC_AL_EQ_S6_B2_MSK
#define MUSIC_AL_EQ_S6_B2_W(X) ((X) << MUSIC_AL_EQ_S6_B2_POS)

//EQ_L_S6_A1 offsetaddress : 0x098
//EQ_L_S6_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S6_A1_POS  (0U)
#define MUSIC_AL_EQ_S6_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S6_A1_POS) /*!< */
#define MUSIC_AL_EQ_S6_A1      MUSIC_AL_EQ_S6_A1_MSK
#define MUSIC_AL_EQ_S6_A1_W(X) ((X) << MUSIC_AL_EQ_S6_A1_POS)

//EQ_L_S6_A2 offsetaddress : 0x09c
//EQ_L_S6_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S6_A2_POS  (0U)
#define MUSIC_AL_EQ_S6_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S6_A2_POS) /*!< */
#define MUSIC_AL_EQ_S6_A2      MUSIC_AL_EQ_S6_A2_MSK
#define MUSIC_AL_EQ_S6_A2_W(X) ((X) << MUSIC_AL_EQ_S6_A2_POS)

//EQ_L_S7_B0 offsetaddress : 0x0a0
//EQ_L_S7_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S7_B0_POS  (0U)
#define MUSIC_AL_EQ_S7_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S7_B0_POS) /*!< */
#define MUSIC_AL_EQ_S7_B0      MUSIC_AL_EQ_S7_B0_MSK
#define MUSIC_AL_EQ_S7_B0_W(X) ((X) << MUSIC_AL_EQ_S7_B0_POS)

//EQ_L_S7_B1 offsetaddress : 0x0a4
//EQ_L_S7_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S7_B1_POS  (0U)
#define MUSIC_AL_EQ_S7_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S7_B1_POS) /*!< */
#define MUSIC_AL_EQ_S7_B1      MUSIC_AL_EQ_S7_B1_MSK
#define MUSIC_AL_EQ_S7_B1_W(X) ((X) << MUSIC_AL_EQ_S7_B1_POS)

//EQ_L_S7_B2 offsetaddress : 0x0a8
//EQ_L_S7_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S7_B2_POS  (0U)
#define MUSIC_AL_EQ_S7_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S7_B2_POS) /*!< */
#define MUSIC_AL_EQ_S7_B2      MUSIC_AL_EQ_S7_B2_MSK
#define MUSIC_AL_EQ_S7_B2_W(X) ((X) << MUSIC_AL_EQ_S7_B2_POS)

//EQ_L_S7_A1 offsetaddress : 0x0ac
//EQ_L_S7_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S7_A1_POS  (0U)
#define MUSIC_AL_EQ_S7_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S7_A1_POS) /*!< */
#define MUSIC_AL_EQ_S7_A1      MUSIC_AL_EQ_S7_A1_MSK
#define MUSIC_AL_EQ_S7_A1_W(X) ((X) << MUSIC_AL_EQ_S7_A1_POS)

//EQ_L_S7_A2 offsetaddress : 0x0b0
//EQ_L_S7_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S7_A2_POS  (0U)
#define MUSIC_AL_EQ_S7_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S7_A2_POS) /*!< */
#define MUSIC_AL_EQ_S7_A2      MUSIC_AL_EQ_S7_A2_MSK
#define MUSIC_AL_EQ_S7_A2_W(X) ((X) << MUSIC_AL_EQ_S7_A2_POS)

//EQ_L_S8_B0 offsetaddress : 0x0b4
//EQ_L_S8_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S8_B0_POS  (0U)
#define MUSIC_AL_EQ_S8_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S8_B0_POS) /*!< */
#define MUSIC_AL_EQ_S8_B0      MUSIC_AL_EQ_S8_B0_MSK
#define MUSIC_AL_EQ_S8_B0_W(X) ((X) << MUSIC_AL_EQ_S8_B0_POS)

//EQ_L_S8_B1 offsetaddress : 0x0b8
//EQ_L_S8_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S8_B1_POS  (0U)
#define MUSIC_AL_EQ_S8_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S8_B1_POS) /*!< */
#define MUSIC_AL_EQ_S8_B1      MUSIC_AL_EQ_S8_B1_MSK
#define MUSIC_AL_EQ_S8_B1_W(X) ((X) << MUSIC_AL_EQ_S8_B1_POS)

//EQ_L_S8_B2 offsetaddress : 0x0bc
//EQ_L_S8_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S8_B2_POS  (0U)
#define MUSIC_AL_EQ_S8_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S8_B2_POS) /*!< */
#define MUSIC_AL_EQ_S8_B2      MUSIC_AL_EQ_S8_B2_MSK
#define MUSIC_AL_EQ_S8_B2_W(X) ((X) << MUSIC_AL_EQ_S8_B2_POS)

//EQ_L_S8_A1 offsetaddress : 0x0c0
//EQ_L_S8_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S8_A1_POS  (0U)
#define MUSIC_AL_EQ_S8_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S8_A1_POS) /*!< */
#define MUSIC_AL_EQ_S8_A1      MUSIC_AL_EQ_S8_A1_MSK
#define MUSIC_AL_EQ_S8_A1_W(X) ((X) << MUSIC_AL_EQ_S8_A1_POS)

//EQ_L_S8_A2 offsetaddress : 0x0c4
//EQ_L_S8_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S8_A2_POS  (0U)
#define MUSIC_AL_EQ_S8_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S8_A2_POS) /*!< */
#define MUSIC_AL_EQ_S8_A2      MUSIC_AL_EQ_S8_A2_MSK
#define MUSIC_AL_EQ_S8_A2_W(X) ((X) << MUSIC_AL_EQ_S8_A2_POS)

//EQ_L_S9_B0 offsetaddress : 0x0c8
//EQ_L_S9_B0 RegResetValue : 0x0
#define MUSIC_AL_EQ_S9_B0_POS  (0U)
#define MUSIC_AL_EQ_S9_B0_MSK  (0xffffffffUL << MUSIC_AL_EQ_S9_B0_POS) /*!< */
#define MUSIC_AL_EQ_S9_B0      MUSIC_AL_EQ_S9_B0_MSK
#define MUSIC_AL_EQ_S9_B0_W(X) ((X) << MUSIC_AL_EQ_S9_B0_POS)

//EQ_L_S9_B1 offsetaddress : 0x0cc
//EQ_L_S9_B1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S9_B1_POS  (0U)
#define MUSIC_AL_EQ_S9_B1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S9_B1_POS) /*!< */
#define MUSIC_AL_EQ_S9_B1      MUSIC_AL_EQ_S9_B1_MSK
#define MUSIC_AL_EQ_S9_B1_W(X) ((X) << MUSIC_AL_EQ_S9_B1_POS)

//EQ_L_S9_B2 offsetaddress : 0x0d0
//EQ_L_S9_B2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S9_B2_POS  (0U)
#define MUSIC_AL_EQ_S9_B2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S9_B2_POS) /*!< */
#define MUSIC_AL_EQ_S9_B2      MUSIC_AL_EQ_S9_B2_MSK
#define MUSIC_AL_EQ_S9_B2_W(X) ((X) << MUSIC_AL_EQ_S9_B2_POS)

//EQ_L_S9_A1 offsetaddress : 0x0d4
//EQ_L_S9_A1 RegResetValue : 0x0
#define MUSIC_AL_EQ_S9_A1_POS  (0U)
#define MUSIC_AL_EQ_S9_A1_MSK  (0xffffffffUL << MUSIC_AL_EQ_S9_A1_POS) /*!< */
#define MUSIC_AL_EQ_S9_A1      MUSIC_AL_EQ_S9_A1_MSK
#define MUSIC_AL_EQ_S9_A1_W(X) ((X) << MUSIC_AL_EQ_S9_A1_POS)

//EQ_L_S9_A2 offsetaddress : 0x0d8
//EQ_L_S9_A2 RegResetValue : 0x0
#define MUSIC_AL_EQ_S9_A2_POS  (0U)
#define MUSIC_AL_EQ_S9_A2_MSK  (0xffffffffUL << MUSIC_AL_EQ_S9_A2_POS) /*!< */
#define MUSIC_AL_EQ_S9_A2      MUSIC_AL_EQ_S9_A2_MSK
#define MUSIC_AL_EQ_S9_A2_W(X) ((X) << MUSIC_AL_EQ_S9_A2_POS)

//EQ_R_S0_B0 offsetaddress : 0x0dc
//EQ_R_S0_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S0_B0_POS  (0U)
#define MUSIC_AR_EQ_S0_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S0_B0_POS) /*!< */
#define MUSIC_AR_EQ_S0_B0      MUSIC_AR_EQ_S0_B0_MSK
#define MUSIC_AR_EQ_S0_B0_W(X) ((X) << MUSIC_AR_EQ_S0_B0_POS)

//EQ_R_S0_B1 offsetaddress : 0x0e0
//EQ_R_S0_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S0_B1_POS  (0U)
#define MUSIC_AR_EQ_S0_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S0_B1_POS) /*!< */
#define MUSIC_AR_EQ_S0_B1      MUSIC_AR_EQ_S0_B1_MSK
#define MUSIC_AR_EQ_S0_B1_W(X) ((X) << MUSIC_AR_EQ_S0_B1_POS)

//EQ_R_S0_B2 offsetaddress : 0x0e4
//EQ_R_S0_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S0_B2_POS  (0U)
#define MUSIC_AR_EQ_S0_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S0_B2_POS) /*!< */
#define MUSIC_AR_EQ_S0_B2      MUSIC_AR_EQ_S0_B2_MSK
#define MUSIC_AR_EQ_S0_B2_W(X) ((X) << MUSIC_AR_EQ_S0_B2_POS)

//EQ_R_S0_A1 offsetaddress : 0x0e8
//EQ_R_S0_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S0_A1_POS  (0U)
#define MUSIC_AR_EQ_S0_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S0_A1_POS) /*!< */
#define MUSIC_AR_EQ_S0_A1      MUSIC_AR_EQ_S0_A1_MSK
#define MUSIC_AR_EQ_S0_A1_W(X) ((X) << MUSIC_AR_EQ_S0_A1_POS)

//EQ_R_S0_A2 offsetaddress : 0x0ec
//EQ_R_S0_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S0_A2_POS  (0U)
#define MUSIC_AR_EQ_S0_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S0_A2_POS) /*!< */
#define MUSIC_AR_EQ_S0_A2      MUSIC_AR_EQ_S0_A2_MSK
#define MUSIC_AR_EQ_S0_A2_W(X) ((X) << MUSIC_AR_EQ_S0_A2_POS)

//EQ_R_S1_B0 offsetaddress : 0x0f0
//EQ_R_S1_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S1_B0_POS  (0U)
#define MUSIC_AR_EQ_S1_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S1_B0_POS) /*!< */
#define MUSIC_AR_EQ_S1_B0      MUSIC_AR_EQ_S1_B0_MSK
#define MUSIC_AR_EQ_S1_B0_W(X) ((X) << MUSIC_AR_EQ_S1_B0_POS)

//EQ_R_S1_B1 offsetaddress : 0x0f4
//EQ_R_S1_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S1_B1_POS  (0U)
#define MUSIC_AR_EQ_S1_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S1_B1_POS) /*!< */
#define MUSIC_AR_EQ_S1_B1      MUSIC_AR_EQ_S1_B1_MSK
#define MUSIC_AR_EQ_S1_B1_W(X) ((X) << MUSIC_AR_EQ_S1_B1_POS)

//EQ_R_S1_B2 offsetaddress : 0x0f8
//EQ_R_S1_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S1_B2_POS  (0U)
#define MUSIC_AR_EQ_S1_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S1_B2_POS) /*!< */
#define MUSIC_AR_EQ_S1_B2      MUSIC_AR_EQ_S1_B2_MSK
#define MUSIC_AR_EQ_S1_B2_W(X) ((X) << MUSIC_AR_EQ_S1_B2_POS)

//EQ_R_S1_A1 offsetaddress : 0x0fc
//EQ_R_S1_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S1_A1_POS  (0U)
#define MUSIC_AR_EQ_S1_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S1_A1_POS) /*!< */
#define MUSIC_AR_EQ_S1_A1      MUSIC_AR_EQ_S1_A1_MSK
#define MUSIC_AR_EQ_S1_A1_W(X) ((X) << MUSIC_AR_EQ_S1_A1_POS)

//EQ_R_S1_A2 offsetaddress : 0x100
//EQ_R_S1_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S1_A2_POS  (0U)
#define MUSIC_AR_EQ_S1_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S1_A2_POS) /*!< */
#define MUSIC_AR_EQ_S1_A2      MUSIC_AR_EQ_S1_A2_MSK
#define MUSIC_AR_EQ_S1_A2_W(X) ((X) << MUSIC_AR_EQ_S1_A2_POS)

//EQ_R_S2_B0 offsetaddress : 0x104
//EQ_R_S2_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S2_B0_POS  (0U)
#define MUSIC_AR_EQ_S2_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S2_B0_POS) /*!< */
#define MUSIC_AR_EQ_S2_B0      MUSIC_AR_EQ_S2_B0_MSK
#define MUSIC_AR_EQ_S2_B0_W(X) ((X) << MUSIC_AR_EQ_S2_B0_POS)

//EQ_R_S2_B1 offsetaddress : 0x108
//EQ_R_S2_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S2_B1_POS  (0U)
#define MUSIC_AR_EQ_S2_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S2_B1_POS) /*!< */
#define MUSIC_AR_EQ_S2_B1      MUSIC_AR_EQ_S2_B1_MSK
#define MUSIC_AR_EQ_S2_B1_W(X) ((X) << MUSIC_AR_EQ_S2_B1_POS)

//EQ_R_S2_B2 offsetaddress : 0x10c
//EQ_R_S2_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S2_B2_POS  (0U)
#define MUSIC_AR_EQ_S2_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S2_B2_POS) /*!< */
#define MUSIC_AR_EQ_S2_B2      MUSIC_AR_EQ_S2_B2_MSK
#define MUSIC_AR_EQ_S2_B2_W(X) ((X) << MUSIC_AR_EQ_S2_B2_POS)

//EQ_R_S2_A1 offsetaddress : 0x110
//EQ_R_S2_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S2_A1_POS  (0U)
#define MUSIC_AR_EQ_S2_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S2_A1_POS) /*!< */
#define MUSIC_AR_EQ_S2_A1      MUSIC_AR_EQ_S2_A1_MSK
#define MUSIC_AR_EQ_S2_A1_W(X) ((X) << MUSIC_AR_EQ_S2_A1_POS)

//EQ_R_S2_A2 offsetaddress : 0x114
//EQ_R_S2_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S2_A2_POS  (0U)
#define MUSIC_AR_EQ_S2_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S2_A2_POS) /*!< */
#define MUSIC_AR_EQ_S2_A2      MUSIC_AR_EQ_S2_A2_MSK
#define MUSIC_AR_EQ_S2_A2_W(X) ((X) << MUSIC_AR_EQ_S2_A2_POS)

//EQ_R_S3_B0 offsetaddress : 0x118
//EQ_R_S3_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S3_B0_POS  (0U)
#define MUSIC_AR_EQ_S3_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S3_B0_POS) /*!< */
#define MUSIC_AR_EQ_S3_B0      MUSIC_AR_EQ_S3_B0_MSK
#define MUSIC_AR_EQ_S3_B0_W(X) ((X) << MUSIC_AR_EQ_S3_B0_POS)

//EQ_R_S3_B1 offsetaddress : 0x11c
//EQ_R_S3_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S3_B1_POS  (0U)
#define MUSIC_AR_EQ_S3_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S3_B1_POS) /*!< */
#define MUSIC_AR_EQ_S3_B1      MUSIC_AR_EQ_S3_B1_MSK
#define MUSIC_AR_EQ_S3_B1_W(X) ((X) << MUSIC_AR_EQ_S3_B1_POS)

//EQ_R_S3_B2 offsetaddress : 0x120
//EQ_R_S3_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S3_B2_POS  (0U)
#define MUSIC_AR_EQ_S3_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S3_B2_POS) /*!< */
#define MUSIC_AR_EQ_S3_B2      MUSIC_AR_EQ_S3_B2_MSK
#define MUSIC_AR_EQ_S3_B2_W(X) ((X) << MUSIC_AR_EQ_S3_B2_POS)

//EQ_R_S3_A1 offsetaddress : 0x124
//EQ_R_S3_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S3_A1_POS  (0U)
#define MUSIC_AR_EQ_S3_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S3_A1_POS) /*!< */
#define MUSIC_AR_EQ_S3_A1      MUSIC_AR_EQ_S3_A1_MSK
#define MUSIC_AR_EQ_S3_A1_W(X) ((X) << MUSIC_AR_EQ_S3_A1_POS)

//EQ_R_S3_A2 offsetaddress : 0x128
//EQ_R_S3_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S3_A2_POS  (0U)
#define MUSIC_AR_EQ_S3_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S3_A2_POS) /*!< */
#define MUSIC_AR_EQ_S3_A2      MUSIC_AR_EQ_S3_A2_MSK
#define MUSIC_AR_EQ_S3_A2_W(X) ((X) << MUSIC_AR_EQ_S3_A2_POS)

//EQ_R_S4_B0 offsetaddress : 0x12c
//EQ_R_S4_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S4_B0_POS  (0U)
#define MUSIC_AR_EQ_S4_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S4_B0_POS) /*!< */
#define MUSIC_AR_EQ_S4_B0      MUSIC_AR_EQ_S4_B0_MSK
#define MUSIC_AR_EQ_S4_B0_W(X) ((X) << MUSIC_AR_EQ_S4_B0_POS)

//EQ_R_S4_B1 offsetaddress : 0x130
//EQ_R_S4_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S4_B1_POS  (0U)
#define MUSIC_AR_EQ_S4_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S4_B1_POS) /*!< */
#define MUSIC_AR_EQ_S4_B1      MUSIC_AR_EQ_S4_B1_MSK
#define MUSIC_AR_EQ_S4_B1_W(X) ((X) << MUSIC_AR_EQ_S4_B1_POS)

//EQ_R_S4_B2 offsetaddress : 0x134
//EQ_R_S4_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S4_B2_POS  (0U)
#define MUSIC_AR_EQ_S4_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S4_B2_POS) /*!< */
#define MUSIC_AR_EQ_S4_B2      MUSIC_AR_EQ_S4_B2_MSK
#define MUSIC_AR_EQ_S4_B2_W(X) ((X) << MUSIC_AR_EQ_S4_B2_POS)

//EQ_R_S4_A1 offsetaddress : 0x138
//EQ_R_S4_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S4_A1_POS  (0U)
#define MUSIC_AR_EQ_S4_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S4_A1_POS) /*!< */
#define MUSIC_AR_EQ_S4_A1      MUSIC_AR_EQ_S4_A1_MSK
#define MUSIC_AR_EQ_S4_A1_W(X) ((X) << MUSIC_AR_EQ_S4_A1_POS)

//EQ_R_S4_A2 offsetaddress : 0x13c
//EQ_R_S4_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S4_A2_POS  (0U)
#define MUSIC_AR_EQ_S4_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S4_A2_POS) /*!< */
#define MUSIC_AR_EQ_S4_A2      MUSIC_AR_EQ_S4_A2_MSK
#define MUSIC_AR_EQ_S4_A2_W(X) ((X) << MUSIC_AR_EQ_S4_A2_POS)

//EQ_R_S5_B0 offsetaddress : 0x140
//EQ_R_S5_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S5_B0_POS  (0U)
#define MUSIC_AR_EQ_S5_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S5_B0_POS) /*!< */
#define MUSIC_AR_EQ_S5_B0      MUSIC_AR_EQ_S5_B0_MSK
#define MUSIC_AR_EQ_S5_B0_W(X) ((X) << MUSIC_AR_EQ_S5_B0_POS)

//EQ_R_S5_B1 offsetaddress : 0x144
//EQ_R_S5_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S5_B1_POS  (0U)
#define MUSIC_AR_EQ_S5_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S5_B1_POS) /*!< */
#define MUSIC_AR_EQ_S5_B1      MUSIC_AR_EQ_S5_B1_MSK
#define MUSIC_AR_EQ_S5_B1_W(X) ((X) << MUSIC_AR_EQ_S5_B1_POS)

//EQ_R_S5_B2 offsetaddress : 0x148
//EQ_R_S5_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S5_B2_POS  (0U)
#define MUSIC_AR_EQ_S5_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S5_B2_POS) /*!< */
#define MUSIC_AR_EQ_S5_B2      MUSIC_AR_EQ_S5_B2_MSK
#define MUSIC_AR_EQ_S5_B2_W(X) ((X) << MUSIC_AR_EQ_S5_B2_POS)

//EQ_R_S5_A1 offsetaddress : 0x14c
//EQ_R_S5_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S5_A1_POS  (0U)
#define MUSIC_AR_EQ_S5_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S5_A1_POS) /*!< */
#define MUSIC_AR_EQ_S5_A1      MUSIC_AR_EQ_S5_A1_MSK
#define MUSIC_AR_EQ_S5_A1_W(X) ((X) << MUSIC_AR_EQ_S5_A1_POS)

//EQ_R_S5_A2 offsetaddress : 0x150
//EQ_R_S5_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S5_A2_POS  (0U)
#define MUSIC_AR_EQ_S5_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S5_A2_POS) /*!< */
#define MUSIC_AR_EQ_S5_A2      MUSIC_AR_EQ_S5_A2_MSK
#define MUSIC_AR_EQ_S5_A2_W(X) ((X) << MUSIC_AR_EQ_S5_A2_POS)

//EQ_R_S6_B0 offsetaddress : 0x154
//EQ_R_S6_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S6_B0_POS  (0U)
#define MUSIC_AR_EQ_S6_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S6_B0_POS) /*!< */
#define MUSIC_AR_EQ_S6_B0      MUSIC_AR_EQ_S6_B0_MSK
#define MUSIC_AR_EQ_S6_B0_W(X) ((X) << MUSIC_AR_EQ_S6_B0_POS)

//EQ_R_S6_B1 offsetaddress : 0x158
//EQ_R_S6_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S6_B1_POS  (0U)
#define MUSIC_AR_EQ_S6_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S6_B1_POS) /*!< */
#define MUSIC_AR_EQ_S6_B1      MUSIC_AR_EQ_S6_B1_MSK
#define MUSIC_AR_EQ_S6_B1_W(X) ((X) << MUSIC_AR_EQ_S6_B1_POS)

//EQ_R_S6_B2 offsetaddress : 0x15c
//EQ_R_S6_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S6_B2_POS  (0U)
#define MUSIC_AR_EQ_S6_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S6_B2_POS) /*!< */
#define MUSIC_AR_EQ_S6_B2      MUSIC_AR_EQ_S6_B2_MSK
#define MUSIC_AR_EQ_S6_B2_W(X) ((X) << MUSIC_AR_EQ_S6_B2_POS)

//EQ_R_S6_A1 offsetaddress : 0x160
//EQ_R_S6_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S6_A1_POS  (0U)
#define MUSIC_AR_EQ_S6_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S6_A1_POS) /*!< */
#define MUSIC_AR_EQ_S6_A1      MUSIC_AR_EQ_S6_A1_MSK
#define MUSIC_AR_EQ_S6_A1_W(X) ((X) << MUSIC_AR_EQ_S6_A1_POS)

//EQ_R_S6_A2 offsetaddress : 0x164
//EQ_R_S6_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S6_A2_POS  (0U)
#define MUSIC_AR_EQ_S6_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S6_A2_POS) /*!< */
#define MUSIC_AR_EQ_S6_A2      MUSIC_AR_EQ_S6_A2_MSK
#define MUSIC_AR_EQ_S6_A2_W(X) ((X) << MUSIC_AR_EQ_S6_A2_POS)

//EQ_R_S7_B0 offsetaddress : 0x168
//EQ_R_S7_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S7_B0_POS  (0U)
#define MUSIC_AR_EQ_S7_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S7_B0_POS) /*!< */
#define MUSIC_AR_EQ_S7_B0      MUSIC_AR_EQ_S7_B0_MSK
#define MUSIC_AR_EQ_S7_B0_W(X) ((X) << MUSIC_AR_EQ_S7_B0_POS)

//EQ_R_S7_B1 offsetaddress : 0x16c
//EQ_R_S7_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S7_B1_POS  (0U)
#define MUSIC_AR_EQ_S7_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S7_B1_POS) /*!< */
#define MUSIC_AR_EQ_S7_B1      MUSIC_AR_EQ_S7_B1_MSK
#define MUSIC_AR_EQ_S7_B1_W(X) ((X) << MUSIC_AR_EQ_S7_B1_POS)

//EQ_R_S7_B2 offsetaddress : 0x170
//EQ_R_S7_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S7_B2_POS  (0U)
#define MUSIC_AR_EQ_S7_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S7_B2_POS) /*!< */
#define MUSIC_AR_EQ_S7_B2      MUSIC_AR_EQ_S7_B2_MSK
#define MUSIC_AR_EQ_S7_B2_W(X) ((X) << MUSIC_AR_EQ_S7_B2_POS)

//EQ_R_S7_A1 offsetaddress : 0x174
//EQ_R_S7_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S7_A1_POS  (0U)
#define MUSIC_AR_EQ_S7_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S7_A1_POS) /*!< */
#define MUSIC_AR_EQ_S7_A1      MUSIC_AR_EQ_S7_A1_MSK
#define MUSIC_AR_EQ_S7_A1_W(X) ((X) << MUSIC_AR_EQ_S7_A1_POS)

//EQ_R_S7_A2 offsetaddress : 0x178
//EQ_R_S7_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S7_A2_POS  (0U)
#define MUSIC_AR_EQ_S7_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S7_A2_POS) /*!< */
#define MUSIC_AR_EQ_S7_A2      MUSIC_AR_EQ_S7_A2_MSK
#define MUSIC_AR_EQ_S7_A2_W(X) ((X) << MUSIC_AR_EQ_S7_A2_POS)

//EQ_R_S8_B0 offsetaddress : 0x17c
//EQ_R_S8_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S8_B0_POS  (0U)
#define MUSIC_AR_EQ_S8_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S8_B0_POS) /*!< */
#define MUSIC_AR_EQ_S8_B0      MUSIC_AR_EQ_S8_B0_MSK
#define MUSIC_AR_EQ_S8_B0_W(X) ((X) << MUSIC_AR_EQ_S8_B0_POS)

//EQ_R_S8_B1 offsetaddress : 0x180
//EQ_R_S8_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S8_B1_POS  (0U)
#define MUSIC_AR_EQ_S8_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S8_B1_POS) /*!< */
#define MUSIC_AR_EQ_S8_B1      MUSIC_AR_EQ_S8_B1_MSK
#define MUSIC_AR_EQ_S8_B1_W(X) ((X) << MUSIC_AR_EQ_S8_B1_POS)

//EQ_R_S8_B2 offsetaddress : 0x184
//EQ_R_S8_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S8_B2_POS  (0U)
#define MUSIC_AR_EQ_S8_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S8_B2_POS) /*!< */
#define MUSIC_AR_EQ_S8_B2      MUSIC_AR_EQ_S8_B2_MSK
#define MUSIC_AR_EQ_S8_B2_W(X) ((X) << MUSIC_AR_EQ_S8_B2_POS)

//EQ_R_S8_A1 offsetaddress : 0x188
//EQ_R_S8_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S8_A1_POS  (0U)
#define MUSIC_AR_EQ_S8_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S8_A1_POS) /*!< */
#define MUSIC_AR_EQ_S8_A1      MUSIC_AR_EQ_S8_A1_MSK
#define MUSIC_AR_EQ_S8_A1_W(X) ((X) << MUSIC_AR_EQ_S8_A1_POS)

//EQ_R_S8_A2 offsetaddress : 0x18c
//EQ_R_S8_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S8_A2_POS  (0U)
#define MUSIC_AR_EQ_S8_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S8_A2_POS) /*!< */
#define MUSIC_AR_EQ_S8_A2      MUSIC_AR_EQ_S8_A2_MSK
#define MUSIC_AR_EQ_S8_A2_W(X) ((X) << MUSIC_AR_EQ_S8_A2_POS)

//EQ_R_S9_B0 offsetaddress : 0x190
//EQ_R_S9_B0 RegResetValue : 0x0
#define MUSIC_AR_EQ_S9_B0_POS  (0U)
#define MUSIC_AR_EQ_S9_B0_MSK  (0xffffffffUL << MUSIC_AR_EQ_S9_B0_POS) /*!< */
#define MUSIC_AR_EQ_S9_B0      MUSIC_AR_EQ_S9_B0_MSK
#define MUSIC_AR_EQ_S9_B0_W(X) ((X) << MUSIC_AR_EQ_S9_B0_POS)

//EQ_R_S9_B1 offsetaddress : 0x194
//EQ_R_S9_B1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S9_B1_POS  (0U)
#define MUSIC_AR_EQ_S9_B1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S9_B1_POS) /*!< */
#define MUSIC_AR_EQ_S9_B1      MUSIC_AR_EQ_S9_B1_MSK
#define MUSIC_AR_EQ_S9_B1_W(X) ((X) << MUSIC_AR_EQ_S9_B1_POS)

//EQ_R_S9_B2 offsetaddress : 0x198
//EQ_R_S9_B2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S9_B2_POS  (0U)
#define MUSIC_AR_EQ_S9_B2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S9_B2_POS) /*!< */
#define MUSIC_AR_EQ_S9_B2      MUSIC_AR_EQ_S9_B2_MSK
#define MUSIC_AR_EQ_S9_B2_W(X) ((X) << MUSIC_AR_EQ_S9_B2_POS)

//EQ_R_S9_A1 offsetaddress : 0x19c
//EQ_R_S9_A1 RegResetValue : 0x0
#define MUSIC_AR_EQ_S9_A1_POS  (0U)
#define MUSIC_AR_EQ_S9_A1_MSK  (0xffffffffUL << MUSIC_AR_EQ_S9_A1_POS) /*!< */
#define MUSIC_AR_EQ_S9_A1      MUSIC_AR_EQ_S9_A1_MSK
#define MUSIC_AR_EQ_S9_A1_W(X) ((X) << MUSIC_AR_EQ_S9_A1_POS)

//EQ_R_S9_A2 offsetaddress : 0x1a0
//EQ_R_S9_A2 RegResetValue : 0x0
#define MUSIC_AR_EQ_S9_A2_POS  (0U)
#define MUSIC_AR_EQ_S9_A2_MSK  (0xffffffffUL << MUSIC_AR_EQ_S9_A2_POS) /*!< */
#define MUSIC_AR_EQ_S9_A2      MUSIC_AR_EQ_S9_A2_MSK
#define MUSIC_AR_EQ_S9_A2_W(X) ((X) << MUSIC_AR_EQ_S9_A2_POS)

//EQ_GC_L_REG0 offsetaddress : 0x1a4
//EQ_GC_L_REG0 RegResetValue : 0x2
#define MUSIC_AL_EQ_GC_ENABLE_POS       (0U)
#define MUSIC_AL_EQ_GC_ENABLE_MSK       (0x1UL << MUSIC_AL_EQ_GC_ENABLE_POS) /*!< */
#define MUSIC_AL_EQ_GC_ENABLE           MUSIC_AL_EQ_GC_ENABLE_MSK
#define MUSIC_AL_EQ_GC_ENABLE_W(X)      ((X) << MUSIC_AL_EQ_GC_ENABLE_POS)
#define MUSIC_AL_EQ_GC_BYPASS_POS       (1U)
#define MUSIC_AL_EQ_GC_BYPASS_MSK       (0x1UL << MUSIC_AL_EQ_GC_BYPASS_POS) /*!< */
#define MUSIC_AL_EQ_GC_BYPASS           MUSIC_AL_EQ_GC_BYPASS_MSK
#define MUSIC_AL_EQ_GC_BYPASS_W(X)      ((X) << MUSIC_AL_EQ_GC_BYPASS_POS)
#define MUSIC_AL_EQ_GC_DELAY_POINT_POS  (2U)
#define MUSIC_AL_EQ_GC_DELAY_POINT_MSK  (0x1ffUL << MUSIC_AL_EQ_GC_DELAY_POINT_POS) /*!< */
#define MUSIC_AL_EQ_GC_DELAY_POINT      MUSIC_AL_EQ_GC_DELAY_POINT_MSK
#define MUSIC_AL_EQ_GC_DELAY_POINT_W(X) ((X) << MUSIC_AL_EQ_GC_DELAY_POINT_POS)

//EQ_GC_L_REG1 offsetaddress : 0x1a8
//EQ_GC_L_REG1 RegResetValue : 0x0
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_POS       (0U)
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX           MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_MSK
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_W(X)      ((X) << MUSIC_AL_EQ_GC_ENV_SMOOTH_FIX_POS)
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX      MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << MUSIC_AL_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS)

//EQ_GC_L_REG2 offsetaddress : 0x1ac
//EQ_GC_L_REG2 RegResetValue : 0x0
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX           MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//EQ_GC_L_REG3 offsetaddress : 0x1b0
//EQ_GC_L_REG3 RegResetValue : 0x0
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX           MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< */
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << MUSIC_AL_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//EQ_GC_R_REG0 offsetaddress : 0x1b4
//EQ_GC_R_REG0 RegResetValue : 0x2
#define MUSIC_AR_EQ_GC_ENABLE_POS       (0U)
#define MUSIC_AR_EQ_GC_ENABLE_MSK       (0x1UL << MUSIC_AR_EQ_GC_ENABLE_POS) /*!< */
#define MUSIC_AR_EQ_GC_ENABLE           MUSIC_AR_EQ_GC_ENABLE_MSK
#define MUSIC_AR_EQ_GC_ENABLE_W(X)      ((X) << MUSIC_AR_EQ_GC_ENABLE_POS)
#define MUSIC_AR_EQ_GC_BYPASS_POS       (1U)
#define MUSIC_AR_EQ_GC_BYPASS_MSK       (0x1UL << MUSIC_AR_EQ_GC_BYPASS_POS) /*!< */
#define MUSIC_AR_EQ_GC_BYPASS           MUSIC_AR_EQ_GC_BYPASS_MSK
#define MUSIC_AR_EQ_GC_BYPASS_W(X)      ((X) << MUSIC_AR_EQ_GC_BYPASS_POS)
#define MUSIC_AR_EQ_GC_DELAY_POINT_POS  (2U)
#define MUSIC_AR_EQ_GC_DELAY_POINT_MSK  (0x1ffUL << MUSIC_AR_EQ_GC_DELAY_POINT_POS) /*!< */
#define MUSIC_AR_EQ_GC_DELAY_POINT      MUSIC_AR_EQ_GC_DELAY_POINT_MSK
#define MUSIC_AR_EQ_GC_DELAY_POINT_W(X) ((X) << MUSIC_AR_EQ_GC_DELAY_POINT_POS)

//EQ_GC_R_REG1 offsetaddress : 0x1b8
//EQ_GC_R_REG1 RegResetValue : 0x0
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_POS       (0U)
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_MSK       (0xffffUL << MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX           MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_MSK
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_W(X)      ((X) << MUSIC_AR_EQ_GC_ENV_SMOOTH_FIX_POS)
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS  (16U)
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK  (0xffffUL << MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX      MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_MSK
#define MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_W(X) ((X) << MUSIC_AR_EQ_GC_ENV_SMOOTH_CMOP_FIX_POS)

//EQ_GC_R_REG2 offsetaddress : 0x1bc
//EQ_GC_R_REG2 RegResetValue : 0x0
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS       (0U)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK       (0xffffUL << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX           MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_MSK
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_W(X)      ((X) << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_FIX_POS)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS  (16U)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK  (0xffffUL << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX      MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_MSK
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_W(X) ((X) << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_1_COMP_FIX_POS)

//EQ_GC_R_REG3 offsetaddress : 0x1c0
//EQ_GC_R_REG3 RegResetValue : 0x0
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS       (0U)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK       (0xffffUL << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX           MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_MSK
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_W(X)      ((X) << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_FIX_POS)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS  (16U)
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK  (0xffffUL << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS) /*!< */
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX      MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_MSK
#define MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_W(X) ((X) << MUSIC_AR_EQ_GC_OUT_GAIN_SMOOTH_2_COMP_FIX_POS)

//FADE_L_DONE offsetaddress : 0x1c4
//FADE_L_DONE RegResetValue : 0x0
#define MUSIC_AL_MUSIC_FADE_DONE_RC_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_DONE_RC_MSK  (0x1UL << MUSIC_AL_MUSIC_FADE_DONE_RC_POS) /*!< Clear after reading*/
#define MUSIC_AL_MUSIC_FADE_DONE_RC      MUSIC_AL_MUSIC_FADE_DONE_RC_MSK
#define MUSIC_AL_MUSIC_FADE_DONE_RC_W(X) ((X) << MUSIC_AL_MUSIC_FADE_DONE_RC_POS)

//FADE_L_EN offsetaddress : 0x1c8
//FADE_L_EN RegResetValue : 0x0
#define MUSIC_AL_MUSIC_FADE_ENABLE_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_ENABLE_MSK  (0x1UL << MUSIC_AL_MUSIC_FADE_ENABLE_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_ENABLE      MUSIC_AL_MUSIC_FADE_ENABLE_MSK
#define MUSIC_AL_MUSIC_FADE_ENABLE_W(X) ((X) << MUSIC_AL_MUSIC_FADE_ENABLE_POS)

//FADE_L_COEFF offsetaddress : 0x1cc
//FADE_L_COEFF RegResetValue : 0x8000000
#define MUSIC_AL_MUSIC_FADE_COEFF_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_COEFF_MSK  (0xffffffffUL << MUSIC_AL_MUSIC_FADE_COEFF_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_COEFF      MUSIC_AL_MUSIC_FADE_COEFF_MSK
#define MUSIC_AL_MUSIC_FADE_COEFF_W(X) ((X) << MUSIC_AL_MUSIC_FADE_COEFF_POS)

//FADE_L_STEP offsetaddress : 0x1d0
//FADE_L_STEP RegResetValue : 0x0
#define MUSIC_AL_MUSIC_FADE_STEP_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_STEP_MSK  (0xffffffffUL << MUSIC_AL_MUSIC_FADE_STEP_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_STEP      MUSIC_AL_MUSIC_FADE_STEP_MSK
#define MUSIC_AL_MUSIC_FADE_STEP_W(X) ((X) << MUSIC_AL_MUSIC_FADE_STEP_POS)

//FADE_L_INTERVAL offsetaddress : 0x1d4
//FADE_L_INTERVAL RegResetValue : 0x0
#define MUSIC_AL_MUSIC_FADE_INTERVAL_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_INTERVAL_MSK  (0xffffffffUL << MUSIC_AL_MUSIC_FADE_INTERVAL_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_INTERVAL      MUSIC_AL_MUSIC_FADE_INTERVAL_MSK
#define MUSIC_AL_MUSIC_FADE_INTERVAL_W(X) ((X) << MUSIC_AL_MUSIC_FADE_INTERVAL_POS)

//FADE_L_DATA_END_MAX offsetaddress : 0x1d8
//FADE_L_DATA_END_MAX RegResetValue : 0x0
#define MUSIC_AL_MUSIC_FADE_DATA_END_MAX_POS  (0U)
#define MUSIC_AL_MUSIC_FADE_DATA_END_MAX_MSK  (0xffffffffUL << MUSIC_AL_MUSIC_FADE_DATA_END_MAX_POS) /*!< */
#define MUSIC_AL_MUSIC_FADE_DATA_END_MAX      MUSIC_AL_MUSIC_FADE_DATA_END_MAX_MSK
#define MUSIC_AL_MUSIC_FADE_DATA_END_MAX_W(X) ((X) << MUSIC_AL_MUSIC_FADE_DATA_END_MAX_POS)

//FADE_R_DONE offsetaddress : 0x1dc
//FADE_R_DONE RegResetValue : 0x0
#define MUSIC_AR_MUSIC_FADE_DONE_RC_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_DONE_RC_MSK  (0x1UL << MUSIC_AR_MUSIC_FADE_DONE_RC_POS) /*!< Clear after reading*/
#define MUSIC_AR_MUSIC_FADE_DONE_RC      MUSIC_AR_MUSIC_FADE_DONE_RC_MSK
#define MUSIC_AR_MUSIC_FADE_DONE_RC_W(X) ((X) << MUSIC_AR_MUSIC_FADE_DONE_RC_POS)

//FADE_R_EN offsetaddress : 0x1e0
//FADE_R_EN RegResetValue : 0x0
#define MUSIC_AR_MUSIC_FADE_ENABLE_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_ENABLE_MSK  (0x1UL << MUSIC_AR_MUSIC_FADE_ENABLE_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_ENABLE      MUSIC_AR_MUSIC_FADE_ENABLE_MSK
#define MUSIC_AR_MUSIC_FADE_ENABLE_W(X) ((X) << MUSIC_AR_MUSIC_FADE_ENABLE_POS)

//FADE_R_COEFF offsetaddress : 0x1e4
//FADE_R_COEFF RegResetValue : 0x8000000
#define MUSIC_AR_MUSIC_FADE_COEFF_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_COEFF_MSK  (0xffffffffUL << MUSIC_AR_MUSIC_FADE_COEFF_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_COEFF      MUSIC_AR_MUSIC_FADE_COEFF_MSK
#define MUSIC_AR_MUSIC_FADE_COEFF_W(X) ((X) << MUSIC_AR_MUSIC_FADE_COEFF_POS)

//FADE_R_STEP offsetaddress : 0x1e8
//FADE_R_STEP RegResetValue : 0x0
#define MUSIC_AR_MUSIC_FADE_STEP_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_STEP_MSK  (0xffffffffUL << MUSIC_AR_MUSIC_FADE_STEP_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_STEP      MUSIC_AR_MUSIC_FADE_STEP_MSK
#define MUSIC_AR_MUSIC_FADE_STEP_W(X) ((X) << MUSIC_AR_MUSIC_FADE_STEP_POS)

//FADE_R_INTERVAL offsetaddress : 0x1ec
//FADE_R_INTERVAL RegResetValue : 0x0
#define MUSIC_AR_MUSIC_FADE_INTERVAL_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_INTERVAL_MSK  (0xffffffffUL << MUSIC_AR_MUSIC_FADE_INTERVAL_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_INTERVAL      MUSIC_AR_MUSIC_FADE_INTERVAL_MSK
#define MUSIC_AR_MUSIC_FADE_INTERVAL_W(X) ((X) << MUSIC_AR_MUSIC_FADE_INTERVAL_POS)

//FADE_R_DATA_END_MAX offsetaddress : 0x1f0
//FADE_R_DATA_END_MAX RegResetValue : 0x0
#define MUSIC_AR_MUSIC_FADE_DATA_END_MAX_POS  (0U)
#define MUSIC_AR_MUSIC_FADE_DATA_END_MAX_MSK  (0xffffffffUL << MUSIC_AR_MUSIC_FADE_DATA_END_MAX_POS) /*!< */
#define MUSIC_AR_MUSIC_FADE_DATA_END_MAX      MUSIC_AR_MUSIC_FADE_DATA_END_MAX_MSK
#define MUSIC_AR_MUSIC_FADE_DATA_END_MAX_W(X) ((X) << MUSIC_AR_MUSIC_FADE_DATA_END_MAX_POS)

//RSSI_CFG offsetaddress : 0x1f4
//RSSI_CFG RegResetValue : 0x0
#define MUSIC_AL_RSSI0_SIZE_POS             (0U)
#define MUSIC_AL_RSSI0_SIZE_MSK             (0xffUL << MUSIC_AL_RSSI0_SIZE_POS) /*!< */
#define MUSIC_AL_RSSI0_SIZE                 MUSIC_AL_RSSI0_SIZE_MSK
#define MUSIC_AL_RSSI0_SIZE_W(X)            ((X) << MUSIC_AL_RSSI0_SIZE_POS)
#define MUSIC_AL_RSSI0_DB_SW_POS            (8U)
#define MUSIC_AL_RSSI0_DB_SW_MSK            (0x1UL << MUSIC_AL_RSSI0_DB_SW_POS) /*!< */
#define MUSIC_AL_RSSI0_DB_SW                MUSIC_AL_RSSI0_DB_SW_MSK
#define MUSIC_AL_RSSI0_DB_SW_W(X)           ((X) << MUSIC_AL_RSSI0_DB_SW_POS)
#define MUSIC_AL_RSSI0_DB_MASK_POS          (9U)
#define MUSIC_AL_RSSI0_DB_MASK_MSK          (0x1UL << MUSIC_AL_RSSI0_DB_MASK_POS) /*!< */
#define MUSIC_AL_RSSI0_DB_MASK              MUSIC_AL_RSSI0_DB_MASK_MSK
#define MUSIC_AL_RSSI0_DB_MASK_W(X)         ((X) << MUSIC_AL_RSSI0_DB_MASK_POS)
#define MUSIC_AL_RSSI0_VALID_INTR_MASK_POS  (10U)
#define MUSIC_AL_RSSI0_VALID_INTR_MASK_MSK  (0x1UL << MUSIC_AL_RSSI0_VALID_INTR_MASK_POS) /*!< */
#define MUSIC_AL_RSSI0_VALID_INTR_MASK      MUSIC_AL_RSSI0_VALID_INTR_MASK_MSK
#define MUSIC_AL_RSSI0_VALID_INTR_MASK_W(X) ((X) << MUSIC_AL_RSSI0_VALID_INTR_MASK_POS)
#define MUSIC_AR_RSSI0_SIZE_POS             (16U)
#define MUSIC_AR_RSSI0_SIZE_MSK             (0xffUL << MUSIC_AR_RSSI0_SIZE_POS) /*!< */
#define MUSIC_AR_RSSI0_SIZE                 MUSIC_AR_RSSI0_SIZE_MSK
#define MUSIC_AR_RSSI0_SIZE_W(X)            ((X) << MUSIC_AR_RSSI0_SIZE_POS)
#define MUSIC_AR_RSSI0_DB_SW_POS            (24U)
#define MUSIC_AR_RSSI0_DB_SW_MSK            (0x1UL << MUSIC_AR_RSSI0_DB_SW_POS) /*!< */
#define MUSIC_AR_RSSI0_DB_SW                MUSIC_AR_RSSI0_DB_SW_MSK
#define MUSIC_AR_RSSI0_DB_SW_W(X)           ((X) << MUSIC_AR_RSSI0_DB_SW_POS)
#define MUSIC_AR_RSSI0_DB_MASK_POS          (25U)
#define MUSIC_AR_RSSI0_DB_MASK_MSK          (0x1UL << MUSIC_AR_RSSI0_DB_MASK_POS) /*!< */
#define MUSIC_AR_RSSI0_DB_MASK              MUSIC_AR_RSSI0_DB_MASK_MSK
#define MUSIC_AR_RSSI0_DB_MASK_W(X)         ((X) << MUSIC_AR_RSSI0_DB_MASK_POS)
#define MUSIC_AR_RSSI0_VALID_INTR_MASK_POS  (26U)
#define MUSIC_AR_RSSI0_VALID_INTR_MASK_MSK  (0x1UL << MUSIC_AR_RSSI0_VALID_INTR_MASK_POS) /*!< */
#define MUSIC_AR_RSSI0_VALID_INTR_MASK      MUSIC_AR_RSSI0_VALID_INTR_MASK_MSK
#define MUSIC_AR_RSSI0_VALID_INTR_MASK_W(X) ((X) << MUSIC_AR_RSSI0_VALID_INTR_MASK_POS)

//RSSI_THD offsetaddress : 0x1f8
//RSSI_THD RegResetValue : 0x0
#define MUSIC_AL_RSSI0_DB_MAX_POS  (0U)
#define MUSIC_AL_RSSI0_DB_MAX_MSK  (0xffUL << MUSIC_AL_RSSI0_DB_MAX_POS) /*!< */
#define MUSIC_AL_RSSI0_DB_MAX      MUSIC_AL_RSSI0_DB_MAX_MSK
#define MUSIC_AL_RSSI0_DB_MAX_W(X) ((X) << MUSIC_AL_RSSI0_DB_MAX_POS)
#define MUSIC_AL_RSSI0_DB_MIN_POS  (8U)
#define MUSIC_AL_RSSI0_DB_MIN_MSK  (0xffUL << MUSIC_AL_RSSI0_DB_MIN_POS) /*!< */
#define MUSIC_AL_RSSI0_DB_MIN      MUSIC_AL_RSSI0_DB_MIN_MSK
#define MUSIC_AL_RSSI0_DB_MIN_W(X) ((X) << MUSIC_AL_RSSI0_DB_MIN_POS)
#define MUSIC_AR_RSSI0_DB_MAX_POS  (16U)
#define MUSIC_AR_RSSI0_DB_MAX_MSK  (0xffUL << MUSIC_AR_RSSI0_DB_MAX_POS) /*!< */
#define MUSIC_AR_RSSI0_DB_MAX      MUSIC_AR_RSSI0_DB_MAX_MSK
#define MUSIC_AR_RSSI0_DB_MAX_W(X) ((X) << MUSIC_AR_RSSI0_DB_MAX_POS)
#define MUSIC_AR_RSSI0_DB_MIN_POS  (24U)
#define MUSIC_AR_RSSI0_DB_MIN_MSK  (0xffUL << MUSIC_AR_RSSI0_DB_MIN_POS) /*!< */
#define MUSIC_AR_RSSI0_DB_MIN      MUSIC_AR_RSSI0_DB_MIN_MSK
#define MUSIC_AR_RSSI0_DB_MIN_W(X) ((X) << MUSIC_AR_RSSI0_DB_MIN_POS)

//RSSI_CAPT offsetaddress : 0x1fc
//RSSI_CAPT RegResetValue : 0x0
#define MUSIC_AL_RSSI0_DB_LAT_POS          (0U)
#define MUSIC_AL_RSSI0_DB_LAT_MSK          (0xffUL << MUSIC_AL_RSSI0_DB_LAT_POS) /*!< */
#define MUSIC_AL_RSSI0_DB_LAT              MUSIC_AL_RSSI0_DB_LAT_MSK
#define MUSIC_AL_RSSI0_DB_LAT_W(X)         ((X) << MUSIC_AL_RSSI0_DB_LAT_POS)
#define MUSIC_AL_RSSI0_VALID_RC_POS        (8U)
#define MUSIC_AL_RSSI0_VALID_RC_MSK        (0x1UL << MUSIC_AL_RSSI0_VALID_RC_POS) /*!< Clear after reading*/
#define MUSIC_AL_RSSI0_VALID_RC            MUSIC_AL_RSSI0_VALID_RC_MSK
#define MUSIC_AL_RSSI0_VALID_RC_W(X)       ((X) << MUSIC_AL_RSSI0_VALID_RC_POS)
#define MUSIC_AL_RSSI0_VALID_INTR_RAW_POS  (9U)
#define MUSIC_AL_RSSI0_VALID_INTR_RAW_MSK  (0x1UL << MUSIC_AL_RSSI0_VALID_INTR_RAW_POS) /*!< Write RSSI_CAPT[9] to clear zero, write RSSI_CAPT[15] to pull high*/
#define MUSIC_AL_RSSI0_VALID_INTR_RAW      MUSIC_AL_RSSI0_VALID_INTR_RAW_MSK
#define MUSIC_AL_RSSI0_VALID_INTR_RAW_W(X) ((X) << MUSIC_AL_RSSI0_VALID_INTR_RAW_POS)
#define MUSIC_AL_RSSI0_VALID_INTR_ST_POS   (10U)
#define MUSIC_AL_RSSI0_VALID_INTR_ST_MSK   (0x1UL << MUSIC_AL_RSSI0_VALID_INTR_ST_POS) /*!< */
#define MUSIC_AL_RSSI0_VALID_INTR_ST       MUSIC_AL_RSSI0_VALID_INTR_ST_MSK
#define MUSIC_AL_RSSI0_VALID_INTR_ST_W(X)  ((X) << MUSIC_AL_RSSI0_VALID_INTR_ST_POS)
#define MUSIC_AR_RSSI0_DB_LAT_POS          (16U)
#define MUSIC_AR_RSSI0_DB_LAT_MSK          (0xffUL << MUSIC_AR_RSSI0_DB_LAT_POS) /*!< */
#define MUSIC_AR_RSSI0_DB_LAT              MUSIC_AR_RSSI0_DB_LAT_MSK
#define MUSIC_AR_RSSI0_DB_LAT_W(X)         ((X) << MUSIC_AR_RSSI0_DB_LAT_POS)
#define MUSIC_AR_RSSI0_VALID_RC_POS        (24U)
#define MUSIC_AR_RSSI0_VALID_RC_MSK        (0x1UL << MUSIC_AR_RSSI0_VALID_RC_POS) /*!< Clear after reading*/
#define MUSIC_AR_RSSI0_VALID_RC            MUSIC_AR_RSSI0_VALID_RC_MSK
#define MUSIC_AR_RSSI0_VALID_RC_W(X)       ((X) << MUSIC_AR_RSSI0_VALID_RC_POS)
#define MUSIC_AR_RSSI0_VALID_INTR_RAW_POS  (25U)
#define MUSIC_AR_RSSI0_VALID_INTR_RAW_MSK  (0x1UL << MUSIC_AR_RSSI0_VALID_INTR_RAW_POS) /*!< Write RSSI_CAPT[25] to clear zero, write RSSI_CAPT[31] to pull high*/
#define MUSIC_AR_RSSI0_VALID_INTR_RAW      MUSIC_AR_RSSI0_VALID_INTR_RAW_MSK
#define MUSIC_AR_RSSI0_VALID_INTR_RAW_W(X) ((X) << MUSIC_AR_RSSI0_VALID_INTR_RAW_POS)
#define MUSIC_AR_RSSI0_VALID_INTR_ST_POS   (26U)
#define MUSIC_AR_RSSI0_VALID_INTR_ST_MSK   (0x1UL << MUSIC_AR_RSSI0_VALID_INTR_ST_POS) /*!< */
#define MUSIC_AR_RSSI0_VALID_INTR_ST       MUSIC_AR_RSSI0_VALID_INTR_ST_MSK
#define MUSIC_AR_RSSI0_VALID_INTR_ST_W(X)  ((X) << MUSIC_AR_RSSI0_VALID_INTR_ST_POS)

typedef struct {
    volatile uint32_t MUSIC_CTRL;          //offsetaddress : 0x000
    volatile uint32_t ASRC_COMMON;         //offsetaddress : 0x004
    volatile uint32_t ASRC_L;              //offsetaddress : 0x008
    volatile uint32_t ASRC_R;              //offsetaddress : 0x00c
    volatile uint32_t EQ_CTRL;             //offsetaddress : 0x010
    volatile uint32_t EQ_L_S0_B0;          //offsetaddress : 0x014
    volatile uint32_t EQ_L_S0_B1;          //offsetaddress : 0x018
    volatile uint32_t EQ_L_S0_B2;          //offsetaddress : 0x01c
    volatile uint32_t EQ_L_S0_A1;          //offsetaddress : 0x020
    volatile uint32_t EQ_L_S0_A2;          //offsetaddress : 0x024
    volatile uint32_t EQ_L_S1_B0;          //offsetaddress : 0x028
    volatile uint32_t EQ_L_S1_B1;          //offsetaddress : 0x02c
    volatile uint32_t EQ_L_S1_B2;          //offsetaddress : 0x030
    volatile uint32_t EQ_L_S1_A1;          //offsetaddress : 0x034
    volatile uint32_t EQ_L_S1_A2;          //offsetaddress : 0x038
    volatile uint32_t EQ_L_S2_B0;          //offsetaddress : 0x03c
    volatile uint32_t EQ_L_S2_B1;          //offsetaddress : 0x040
    volatile uint32_t EQ_L_S2_B2;          //offsetaddress : 0x044
    volatile uint32_t EQ_L_S2_A1;          //offsetaddress : 0x048
    volatile uint32_t EQ_L_S2_A2;          //offsetaddress : 0x04c
    volatile uint32_t EQ_L_S3_B0;          //offsetaddress : 0x050
    volatile uint32_t EQ_L_S3_B1;          //offsetaddress : 0x054
    volatile uint32_t EQ_L_S3_B2;          //offsetaddress : 0x058
    volatile uint32_t EQ_L_S3_A1;          //offsetaddress : 0x05c
    volatile uint32_t EQ_L_S3_A2;          //offsetaddress : 0x060
    volatile uint32_t EQ_L_S4_B0;          //offsetaddress : 0x064
    volatile uint32_t EQ_L_S4_B1;          //offsetaddress : 0x068
    volatile uint32_t EQ_L_S4_B2;          //offsetaddress : 0x06c
    volatile uint32_t EQ_L_S4_A1;          //offsetaddress : 0x070
    volatile uint32_t EQ_L_S4_A2;          //offsetaddress : 0x074
    volatile uint32_t EQ_L_S5_B0;          //offsetaddress : 0x078
    volatile uint32_t EQ_L_S5_B1;          //offsetaddress : 0x07c
    volatile uint32_t EQ_L_S5_B2;          //offsetaddress : 0x080
    volatile uint32_t EQ_L_S5_A1;          //offsetaddress : 0x084
    volatile uint32_t EQ_L_S5_A2;          //offsetaddress : 0x088
    volatile uint32_t EQ_L_S6_B0;          //offsetaddress : 0x08c
    volatile uint32_t EQ_L_S6_B1;          //offsetaddress : 0x090
    volatile uint32_t EQ_L_S6_B2;          //offsetaddress : 0x094
    volatile uint32_t EQ_L_S6_A1;          //offsetaddress : 0x098
    volatile uint32_t EQ_L_S6_A2;          //offsetaddress : 0x09c
    volatile uint32_t EQ_L_S7_B0;          //offsetaddress : 0x0a0
    volatile uint32_t EQ_L_S7_B1;          //offsetaddress : 0x0a4
    volatile uint32_t EQ_L_S7_B2;          //offsetaddress : 0x0a8
    volatile uint32_t EQ_L_S7_A1;          //offsetaddress : 0x0ac
    volatile uint32_t EQ_L_S7_A2;          //offsetaddress : 0x0b0
    volatile uint32_t EQ_L_S8_B0;          //offsetaddress : 0x0b4
    volatile uint32_t EQ_L_S8_B1;          //offsetaddress : 0x0b8
    volatile uint32_t EQ_L_S8_B2;          //offsetaddress : 0x0bc
    volatile uint32_t EQ_L_S8_A1;          //offsetaddress : 0x0c0
    volatile uint32_t EQ_L_S8_A2;          //offsetaddress : 0x0c4
    volatile uint32_t EQ_L_S9_B0;          //offsetaddress : 0x0c8
    volatile uint32_t EQ_L_S9_B1;          //offsetaddress : 0x0cc
    volatile uint32_t EQ_L_S9_B2;          //offsetaddress : 0x0d0
    volatile uint32_t EQ_L_S9_A1;          //offsetaddress : 0x0d4
    volatile uint32_t EQ_L_S9_A2;          //offsetaddress : 0x0d8
    volatile uint32_t EQ_R_S0_B0;          //offsetaddress : 0x0dc
    volatile uint32_t EQ_R_S0_B1;          //offsetaddress : 0x0e0
    volatile uint32_t EQ_R_S0_B2;          //offsetaddress : 0x0e4
    volatile uint32_t EQ_R_S0_A1;          //offsetaddress : 0x0e8
    volatile uint32_t EQ_R_S0_A2;          //offsetaddress : 0x0ec
    volatile uint32_t EQ_R_S1_B0;          //offsetaddress : 0x0f0
    volatile uint32_t EQ_R_S1_B1;          //offsetaddress : 0x0f4
    volatile uint32_t EQ_R_S1_B2;          //offsetaddress : 0x0f8
    volatile uint32_t EQ_R_S1_A1;          //offsetaddress : 0x0fc
    volatile uint32_t EQ_R_S1_A2;          //offsetaddress : 0x100
    volatile uint32_t EQ_R_S2_B0;          //offsetaddress : 0x104
    volatile uint32_t EQ_R_S2_B1;          //offsetaddress : 0x108
    volatile uint32_t EQ_R_S2_B2;          //offsetaddress : 0x10c
    volatile uint32_t EQ_R_S2_A1;          //offsetaddress : 0x110
    volatile uint32_t EQ_R_S2_A2;          //offsetaddress : 0x114
    volatile uint32_t EQ_R_S3_B0;          //offsetaddress : 0x118
    volatile uint32_t EQ_R_S3_B1;          //offsetaddress : 0x11c
    volatile uint32_t EQ_R_S3_B2;          //offsetaddress : 0x120
    volatile uint32_t EQ_R_S3_A1;          //offsetaddress : 0x124
    volatile uint32_t EQ_R_S3_A2;          //offsetaddress : 0x128
    volatile uint32_t EQ_R_S4_B0;          //offsetaddress : 0x12c
    volatile uint32_t EQ_R_S4_B1;          //offsetaddress : 0x130
    volatile uint32_t EQ_R_S4_B2;          //offsetaddress : 0x134
    volatile uint32_t EQ_R_S4_A1;          //offsetaddress : 0x138
    volatile uint32_t EQ_R_S4_A2;          //offsetaddress : 0x13c
    volatile uint32_t EQ_R_S5_B0;          //offsetaddress : 0x140
    volatile uint32_t EQ_R_S5_B1;          //offsetaddress : 0x144
    volatile uint32_t EQ_R_S5_B2;          //offsetaddress : 0x148
    volatile uint32_t EQ_R_S5_A1;          //offsetaddress : 0x14c
    volatile uint32_t EQ_R_S5_A2;          //offsetaddress : 0x150
    volatile uint32_t EQ_R_S6_B0;          //offsetaddress : 0x154
    volatile uint32_t EQ_R_S6_B1;          //offsetaddress : 0x158
    volatile uint32_t EQ_R_S6_B2;          //offsetaddress : 0x15c
    volatile uint32_t EQ_R_S6_A1;          //offsetaddress : 0x160
    volatile uint32_t EQ_R_S6_A2;          //offsetaddress : 0x164
    volatile uint32_t EQ_R_S7_B0;          //offsetaddress : 0x168
    volatile uint32_t EQ_R_S7_B1;          //offsetaddress : 0x16c
    volatile uint32_t EQ_R_S7_B2;          //offsetaddress : 0x170
    volatile uint32_t EQ_R_S7_A1;          //offsetaddress : 0x174
    volatile uint32_t EQ_R_S7_A2;          //offsetaddress : 0x178
    volatile uint32_t EQ_R_S8_B0;          //offsetaddress : 0x17c
    volatile uint32_t EQ_R_S8_B1;          //offsetaddress : 0x180
    volatile uint32_t EQ_R_S8_B2;          //offsetaddress : 0x184
    volatile uint32_t EQ_R_S8_A1;          //offsetaddress : 0x188
    volatile uint32_t EQ_R_S8_A2;          //offsetaddress : 0x18c
    volatile uint32_t EQ_R_S9_B0;          //offsetaddress : 0x190
    volatile uint32_t EQ_R_S9_B1;          //offsetaddress : 0x194
    volatile uint32_t EQ_R_S9_B2;          //offsetaddress : 0x198
    volatile uint32_t EQ_R_S9_A1;          //offsetaddress : 0x19c
    volatile uint32_t EQ_R_S9_A2;          //offsetaddress : 0x1a0
    volatile uint32_t EQ_GC_L_REG0;        //offsetaddress : 0x1a4
    volatile uint32_t EQ_GC_L_REG1;        //offsetaddress : 0x1a8
    volatile uint32_t EQ_GC_L_REG2;        //offsetaddress : 0x1ac
    volatile uint32_t EQ_GC_L_REG3;        //offsetaddress : 0x1b0
    volatile uint32_t EQ_GC_R_REG0;        //offsetaddress : 0x1b4
    volatile uint32_t EQ_GC_R_REG1;        //offsetaddress : 0x1b8
    volatile uint32_t EQ_GC_R_REG2;        //offsetaddress : 0x1bc
    volatile uint32_t EQ_GC_R_REG3;        //offsetaddress : 0x1c0
    volatile uint32_t FADE_L_DONE;         //offsetaddress : 0x1c4
    volatile uint32_t FADE_L_EN;           //offsetaddress : 0x1c8
    volatile uint32_t FADE_L_COEFF;        //offsetaddress : 0x1cc
    volatile uint32_t FADE_L_STEP;         //offsetaddress : 0x1d0
    volatile uint32_t FADE_L_INTERVAL;     //offsetaddress : 0x1d4
    volatile uint32_t FADE_L_DATA_END_MAX; //offsetaddress : 0x1d8
    volatile uint32_t FADE_R_DONE;         //offsetaddress : 0x1dc
    volatile uint32_t FADE_R_EN;           //offsetaddress : 0x1e0
    volatile uint32_t FADE_R_COEFF;        //offsetaddress : 0x1e4
    volatile uint32_t FADE_R_STEP;         //offsetaddress : 0x1e8
    volatile uint32_t FADE_R_INTERVAL;     //offsetaddress : 0x1ec
    volatile uint32_t FADE_R_DATA_END_MAX; //offsetaddress : 0x1f0
    volatile uint32_t RSSI_CFG;            //offsetaddress : 0x1f4
    volatile uint32_t RSSI_THD;            //offsetaddress : 0x1f8
    volatile uint32_t RSSI_CAPT;           //offsetaddress : 0x1fc
} music_reg_t;
#ifdef __cplusplus
}
#endif
#endif
/*******************************************************************************************************
 *
 * @file    bt_rf.h
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
#ifndef __BT_RF_H__
#define __BT_RF_H__
#ifdef __cplusplus
extern "C" { 
#endif
#include "tl_chip.h"
//bt_rf_0 offsetaddress : 0x00
//bt_rf_0 RegResetValue : 0xNone
#define BT_RF_RCCAL_RUN_SRC_POS        (0U)
#define BT_RF_RCCAL_RUN_SRC_MSK        (0x1UL << BT_RF_RCCAL_RUN_SRC_POS)/*!< Signal source of Rx RC calibration run; 0: hw; 1: sw*/
#define BT_RF_RCCAL_RUN_SRC            BT_RF_RCCAL_RUN_SRC_MSK
#define BT_RF_RCCAL_RUN_SRC_W(X)       ((X) << BT_RF_RCCAL_RUN_SRC_POS)
#define BT_RF_VCOCAL_RUN_SRC_POS       (1U)
#define BT_RF_VCOCAL_RUN_SRC_MSK       (0x1UL << BT_RF_VCOCAL_RUN_SRC_POS)/*!< Signal source of VCO calibration run; 0: hw; 1: sw*/
#define BT_RF_VCOCAL_RUN_SRC           BT_RF_VCOCAL_RUN_SRC_MSK
#define BT_RF_VCOCAL_RUN_SRC_W(X)      ((X) << BT_RF_VCOCAL_RUN_SRC_POS)
#define BT_RF_TPCAL_RUN_SRC_POS        (2U)
#define BT_RF_TPCAL_RUN_SRC_MSK        (0x1UL << BT_RF_TPCAL_RUN_SRC_POS)/*!< Signal source of Tx TP calibration run; 0: hw; 1: sw*/
#define BT_RF_TPCAL_RUN_SRC            BT_RF_TPCAL_RUN_SRC_MSK
#define BT_RF_TPCAL_RUN_SRC_W(X)       ((X) << BT_RF_TPCAL_RUN_SRC_POS)
#define BT_RF_TXDCOC_RUN_SRC_POS       (3U)
#define BT_RF_TXDCOC_RUN_SRC_MSK       (0x1UL << BT_RF_TXDCOC_RUN_SRC_POS)/*!< Signal source of Tx DCOC calibration run; 0: hw; 1: sw*/
#define BT_RF_TXDCOC_RUN_SRC           BT_RF_TXDCOC_RUN_SRC_MSK
#define BT_RF_TXDCOC_RUN_SRC_W(X)      ((X) << BT_RF_TXDCOC_RUN_SRC_POS)
#define BT_RF_RXDCOC_RUN_SRC_POS       (4U)
#define BT_RF_RXDCOC_RUN_SRC_MSK       (0x1UL << BT_RF_RXDCOC_RUN_SRC_POS)/*!< Signal source of Rx DCOC calibration run; 0: hw; 1: sw*/
#define BT_RF_RXDCOC_RUN_SRC           BT_RF_RXDCOC_RUN_SRC_MSK
#define BT_RF_RXDCOC_RUN_SRC_W(X)      ((X) << BT_RF_RXDCOC_RUN_SRC_POS)
#define BT_RF_MMD_EN_SRC_POS           (5U)
#define BT_RF_MMD_EN_SRC_MSK           (0x1UL << BT_RF_MMD_EN_SRC_POS)/*!< Signal source of MMD enable; 0: hw; 1: sw*/
#define BT_RF_MMD_EN_SRC               BT_RF_MMD_EN_SRC_MSK
#define BT_RF_MMD_EN_SRC_W(X)          ((X) << BT_RF_MMD_EN_SRC_POS)
#define BT_RF_TX_TPCAL_EN_SRC_POS      (6U)
#define BT_RF_TX_TPCAL_EN_SRC_MSK      (0x1UL << BT_RF_TX_TPCAL_EN_SRC_POS)/*!< Signal source of Tx TP calibration enable; 0: hw; 1: sw*/
#define BT_RF_TX_TPCAL_EN_SRC          BT_RF_TX_TPCAL_EN_SRC_MSK
#define BT_RF_TX_TPCAL_EN_SRC_W(X)     ((X) << BT_RF_TX_TPCAL_EN_SRC_POS)
#define BT_RF_TX_TPMOD_EN_SRC_POS      (7U)
#define BT_RF_TX_TPMOD_EN_SRC_MSK      (0x1UL << BT_RF_TX_TPMOD_EN_SRC_POS)/*!< Signal source of Tx TP modulation enable; 0: hw; 1: sw*/
#define BT_RF_TX_TPMOD_EN_SRC          BT_RF_TX_TPMOD_EN_SRC_MSK
#define BT_RF_TX_TPMOD_EN_SRC_W(X)     ((X) << BT_RF_TX_TPMOD_EN_SRC_POS)
#define BT_RF_TX_IQMOD_EN_SRC_POS      (8U)
#define BT_RF_TX_IQMOD_EN_SRC_MSK      (0x1UL << BT_RF_TX_IQMOD_EN_SRC_POS)/*!< Signal source of Tx IQ modulation enable; 0: hw; 1: sw*/
#define BT_RF_TX_IQMOD_EN_SRC          BT_RF_TX_IQMOD_EN_SRC_MSK
#define BT_RF_TX_IQMOD_EN_SRC_W(X)     ((X) << BT_RF_TX_IQMOD_EN_SRC_POS)
#define BT_RF_PA_RAMP_SRC_POS          (9U)
#define BT_RF_PA_RAMP_SRC_MSK          (0x1UL << BT_RF_PA_RAMP_SRC_POS)/*!< Signal source of Tx PA ramp; 0: hw; 1: sw*/
#define BT_RF_PA_RAMP_SRC              BT_RF_PA_RAMP_SRC_MSK
#define BT_RF_PA_RAMP_SRC_W(X)         ((X) << BT_RF_PA_RAMP_SRC_POS)
#define BT_RF_RX_ON_SRC_POS            (10U)
#define BT_RF_RX_ON_SRC_MSK            (0x1UL << BT_RF_RX_ON_SRC_POS)/*!< Signal source of rx on; 0: hw; 1: sw*/
#define BT_RF_RX_ON_SRC                BT_RF_RX_ON_SRC_MSK
#define BT_RF_RX_ON_SRC_W(X)           ((X) << BT_RF_RX_ON_SRC_POS)
#define BT_RF_BG_PUP_SRC_POS           (11U)
#define BT_RF_BG_PUP_SRC_MSK           (0x1UL << BT_RF_BG_PUP_SRC_POS)/*!< Signal source of bandgap power up; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_SRC               BT_RF_BG_PUP_SRC_MSK
#define BT_RF_BG_PUP_SRC_W(X)          ((X) << BT_RF_BG_PUP_SRC_POS)
#define BT_RF_BG_FCHG_SRC_POS          (12U)
#define BT_RF_BG_FCHG_SRC_MSK          (0x1UL << BT_RF_BG_FCHG_SRC_POS)/*!< Signal source of bandgap fast charge; 0: hw; 1: sw*/
#define BT_RF_BG_FCHG_SRC              BT_RF_BG_FCHG_SRC_MSK
#define BT_RF_BG_FCHG_SRC_W(X)         ((X) << BT_RF_BG_FCHG_SRC_POS)
#define BT_RF_BG_PUP_IBG_RX_SRC_POS    (13U)
#define BT_RF_BG_PUP_IBG_RX_SRC_MSK    (0x1UL << BT_RF_BG_PUP_IBG_RX_SRC_POS)/*!< Signal source of rx ; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_RX_SRC        BT_RF_BG_PUP_IBG_RX_SRC_MSK
#define BT_RF_BG_PUP_IBG_RX_SRC_W(X)   ((X) << BT_RF_BG_PUP_IBG_RX_SRC_POS)
#define BT_RF_BG_PUP_IBG_TX_SRC_POS    (14U)
#define BT_RF_BG_PUP_IBG_TX_SRC_MSK    (0x1UL << BT_RF_BG_PUP_IBG_TX_SRC_POS)/*!< Signal source of  tx; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_TX_SRC        BT_RF_BG_PUP_IBG_TX_SRC_MSK
#define BT_RF_BG_PUP_IBG_TX_SRC_W(X)   ((X) << BT_RF_BG_PUP_IBG_TX_SRC_POS)
#define BT_RF_BG_PUP_IBG_PLL_SRC_POS   (15U)
#define BT_RF_BG_PUP_IBG_PLL_SRC_MSK   (0x1UL << BT_RF_BG_PUP_IBG_PLL_SRC_POS)/*!< Signal source of pll ; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_PLL_SRC       BT_RF_BG_PUP_IBG_PLL_SRC_MSK
#define BT_RF_BG_PUP_IBG_PLL_SRC_W(X)  ((X) << BT_RF_BG_PUP_IBG_PLL_SRC_POS)
#define BT_RF_LDO_ISO_PUP_SRC_POS      (16U)
#define BT_RF_LDO_ISO_PUP_SRC_MSK      (0x1UL << BT_RF_LDO_ISO_PUP_SRC_POS)/*!< Signal source of iso LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_ISO_PUP_SRC          BT_RF_LDO_ISO_PUP_SRC_MSK
#define BT_RF_LDO_ISO_PUP_SRC_W(X)     ((X) << BT_RF_LDO_ISO_PUP_SRC_POS)
#define BT_RF_LDO_RF_PUP_SRC_POS       (17U)
#define BT_RF_LDO_RF_PUP_SRC_MSK       (0x1UL << BT_RF_LDO_RF_PUP_SRC_POS)/*!< Signal source of RF LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_RF_PUP_SRC           BT_RF_LDO_RF_PUP_SRC_MSK
#define BT_RF_LDO_RF_PUP_SRC_W(X)      ((X) << BT_RF_LDO_RF_PUP_SRC_POS)
#define BT_RF_LDO_RF_FCHG_SRC_POS      (18U)
#define BT_RF_LDO_RF_FCHG_SRC_MSK      (0x1UL << BT_RF_LDO_RF_FCHG_SRC_POS)/*!< Signal source of RF LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_RF_FCHG_SRC          BT_RF_LDO_RF_FCHG_SRC_MSK
#define BT_RF_LDO_RF_FCHG_SRC_W(X)     ((X) << BT_RF_LDO_RF_FCHG_SRC_POS)
#define BT_RF_LDO_BB_PUP_SRC_POS       (19U)
#define BT_RF_LDO_BB_PUP_SRC_MSK       (0x1UL << BT_RF_LDO_BB_PUP_SRC_POS)/*!< Signal source of BB LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_BB_PUP_SRC           BT_RF_LDO_BB_PUP_SRC_MSK
#define BT_RF_LDO_BB_PUP_SRC_W(X)      ((X) << BT_RF_LDO_BB_PUP_SRC_POS)
#define BT_RF_LDO_BB_FCHG_SRC_POS      (20U)
#define BT_RF_LDO_BB_FCHG_SRC_MSK      (0x1UL << BT_RF_LDO_BB_FCHG_SRC_POS)/*!< Signal source of BB LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_BB_FCHG_SRC          BT_RF_LDO_BB_FCHG_SRC_MSK
#define BT_RF_LDO_BB_FCHG_SRC_W(X)     ((X) << BT_RF_LDO_BB_FCHG_SRC_POS)
#define BT_RF_LDO_PLL_PUP_SRC_POS      (21U)
#define BT_RF_LDO_PLL_PUP_SRC_MSK      (0x1UL << BT_RF_LDO_PLL_PUP_SRC_POS)/*!< Signal source of PLL LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PLL_PUP_SRC          BT_RF_LDO_PLL_PUP_SRC_MSK
#define BT_RF_LDO_PLL_PUP_SRC_W(X)     ((X) << BT_RF_LDO_PLL_PUP_SRC_POS)
#define BT_RF_LDO_PLL_FCHG_SRC_POS     (22U)
#define BT_RF_LDO_PLL_FCHG_SRC_MSK     (0x1UL << BT_RF_LDO_PLL_FCHG_SRC_POS)/*!< Signal source of PLL LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_PLL_FCHG_SRC         BT_RF_LDO_PLL_FCHG_SRC_MSK
#define BT_RF_LDO_PLL_FCHG_SRC_W(X)    ((X) << BT_RF_LDO_PLL_FCHG_SRC_POS)
#define BT_RF_LDO_VCO_PUP_SRC_POS      (23U)
#define BT_RF_LDO_VCO_PUP_SRC_MSK      (0x1UL << BT_RF_LDO_VCO_PUP_SRC_POS)/*!< Signal source of VCO LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_VCO_PUP_SRC          BT_RF_LDO_VCO_PUP_SRC_MSK
#define BT_RF_LDO_VCO_PUP_SRC_W(X)     ((X) << BT_RF_LDO_VCO_PUP_SRC_POS)
#define BT_RF_LDO_VCO_FCHG_SRC_POS     (24U)
#define BT_RF_LDO_VCO_FCHG_SRC_MSK     (0x1UL << BT_RF_LDO_VCO_FCHG_SRC_POS)/*!< Signal source of VCO LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_VCO_FCHG_SRC         BT_RF_LDO_VCO_FCHG_SRC_MSK
#define BT_RF_LDO_VCO_FCHG_SRC_W(X)    ((X) << BT_RF_LDO_VCO_FCHG_SRC_POS)
#define BT_RF_LDO_PA_PUP_VBAT_SRC_POS  (25U)
#define BT_RF_LDO_PA_PUP_VBAT_SRC_MSK  (0x1UL << BT_RF_LDO_PA_PUP_VBAT_SRC_POS)/*!< Signal source of Tx PA vbat power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PA_PUP_VBAT_SRC      BT_RF_LDO_PA_PUP_VBAT_SRC_MSK
#define BT_RF_LDO_PA_PUP_VBAT_SRC_W(X) ((X) << BT_RF_LDO_PA_PUP_VBAT_SRC_POS)
#define BT_RF_LDO_PA_PUP_VBUCK_SRC_POS (26U)
#define BT_RF_LDO_PA_PUP_VBUCK_SRC_MSK (0x1UL << BT_RF_LDO_PA_PUP_VBUCK_SRC_POS)/*!< Signal source of Tx PA vbuck power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PA_PUP_VBUCK_SRC     BT_RF_LDO_PA_PUP_VBUCK_SRC_MSK
#define BT_RF_LDO_PA_PUP_VBUCK_SRC_W(X) ((X) << BT_RF_LDO_PA_PUP_VBUCK_SRC_POS)
#define BT_RF_VCO_PUP_SRC_POS          (27U)
#define BT_RF_VCO_PUP_SRC_MSK          (0x1UL << BT_RF_VCO_PUP_SRC_POS)/*!< Signal source of VCO power up; 0: hw; 1: sw*/
#define BT_RF_VCO_PUP_SRC              BT_RF_VCO_PUP_SRC_MSK
#define BT_RF_VCO_PUP_SRC_W(X)         ((X) << BT_RF_VCO_PUP_SRC_POS)
#define BT_RF_VCODIV_PUP_SRC_POS       (28U)
#define BT_RF_VCODIV_PUP_SRC_MSK       (0x1UL << BT_RF_VCODIV_PUP_SRC_POS)/*!< Signal source of VCO divider power up; 0: hw; 1: sw*/
#define BT_RF_VCODIV_PUP_SRC           BT_RF_VCODIV_PUP_SRC_MSK
#define BT_RF_VCODIV_PUP_SRC_W(X)      ((X) << BT_RF_VCODIV_PUP_SRC_POS)
#define BT_RF_DAC_PUP_SRC_POS          (29U)
#define BT_RF_DAC_PUP_SRC_MSK          (0x1UL << BT_RF_DAC_PUP_SRC_POS)/*!< Signal source of Tx TP DAC power up; 0: hw; 1: sw*/
#define BT_RF_DAC_PUP_SRC              BT_RF_DAC_PUP_SRC_MSK
#define BT_RF_DAC_PUP_SRC_W(X)         ((X) << BT_RF_DAC_PUP_SRC_POS)
#define BT_RF_LORX_PUP_SRC_POS         (30U)
#define BT_RF_LORX_PUP_SRC_MSK         (0x1UL << BT_RF_LORX_PUP_SRC_POS)/*!< Signal source of Rx LO power up; 0: hw; 1: sw*/
#define BT_RF_LORX_PUP_SRC             BT_RF_LORX_PUP_SRC_MSK
#define BT_RF_LORX_PUP_SRC_W(X)        ((X) << BT_RF_LORX_PUP_SRC_POS)
#define BT_RF_LORX_PUP_DRV_SRC_POS     (31U)
#define BT_RF_LORX_PUP_DRV_SRC_MSK     (0x1UL << BT_RF_LORX_PUP_DRV_SRC_POS)/*!< Signal source of Rx LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LORX_PUP_DRV_SRC         BT_RF_LORX_PUP_DRV_SRC_MSK
#define BT_RF_LORX_PUP_DRV_SRC_W(X)    ((X) << BT_RF_LORX_PUP_DRV_SRC_POS)


//bt_rf_1 offsetaddress : 0x04
//bt_rf_1 RegResetValue : 0xNone
#define BT_RF_LOTX_PUP_IQ_SRC_POS      (0U)
#define BT_RF_LOTX_PUP_IQ_SRC_MSK      (0x1UL << BT_RF_LOTX_PUP_IQ_SRC_POS)/*!< Signal source of Tx LO power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_IQ_SRC          BT_RF_LOTX_PUP_IQ_SRC_MSK
#define BT_RF_LOTX_PUP_IQ_SRC_W(X)     ((X) << BT_RF_LOTX_PUP_IQ_SRC_POS)
#define BT_RF_LOTX_PUP_IQDRV_SRC_POS   (1U)
#define BT_RF_LOTX_PUP_IQDRV_SRC_MSK   (0x1UL << BT_RF_LOTX_PUP_IQDRV_SRC_POS)/*!< Signal source of Tx LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_IQDRV_SRC       BT_RF_LOTX_PUP_IQDRV_SRC_MSK
#define BT_RF_LOTX_PUP_IQDRV_SRC_W(X)  ((X) << BT_RF_LOTX_PUP_IQDRV_SRC_POS)
#define BT_RF_LOTX_PUP_GFSK_SRC_POS    (2U)
#define BT_RF_LOTX_PUP_GFSK_SRC_MSK    (0x1UL << BT_RF_LOTX_PUP_GFSK_SRC_POS)/*!< Signal source of Tx GFSK LO power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_GFSK_SRC        BT_RF_LOTX_PUP_GFSK_SRC_MSK
#define BT_RF_LOTX_PUP_GFSK_SRC_W(X)   ((X) << BT_RF_LOTX_PUP_GFSK_SRC_POS)
#define BT_RF_LOTX_PUP_GFSKDRV_SRC_POS (3U)
#define BT_RF_LOTX_PUP_GFSKDRV_SRC_MSK (0x1UL << BT_RF_LOTX_PUP_GFSKDRV_SRC_POS)/*!< Signal source of Tx GFSK LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_GFSKDRV_SRC     BT_RF_LOTX_PUP_GFSKDRV_SRC_MSK
#define BT_RF_LOTX_PUP_GFSKDRV_SRC_W(X) ((X) << BT_RF_LOTX_PUP_GFSKDRV_SRC_POS)
#define BT_RF_FCAL_PUP_SRC_POS         (4U)
#define BT_RF_FCAL_PUP_SRC_MSK         (0x1UL << BT_RF_FCAL_PUP_SRC_POS)/*!< Signal source of FCAL power up; 0: hw; 1: sw*/
#define BT_RF_FCAL_PUP_SRC             BT_RF_FCAL_PUP_SRC_MSK
#define BT_RF_FCAL_PUP_SRC_W(X)        ((X) << BT_RF_FCAL_PUP_SRC_POS)
#define BT_RF_DIVN_PUP_SRC_POS         (5U)
#define BT_RF_DIVN_PUP_SRC_MSK         (0x1UL << BT_RF_DIVN_PUP_SRC_POS)/*!< Signal source of PLL loop divider power up; 0: hw; 1: sw*/
#define BT_RF_DIVN_PUP_SRC             BT_RF_DIVN_PUP_SRC_MSK
#define BT_RF_DIVN_PUP_SRC_W(X)        ((X) << BT_RF_DIVN_PUP_SRC_POS)
#define BT_RF_PFDCP_PUP_SRC_POS        (6U)
#define BT_RF_PFDCP_PUP_SRC_MSK        (0x1UL << BT_RF_PFDCP_PUP_SRC_POS)/*!< Signal source of PFD/CP power up; 0: hw; 1: sw*/
#define BT_RF_PFDCP_PUP_SRC            BT_RF_PFDCP_PUP_SRC_MSK
#define BT_RF_PFDCP_PUP_SRC_W(X)       ((X) << BT_RF_PFDCP_PUP_SRC_POS)
#define BT_RF_PLL_OPENLOOP_SRC_POS     (7U)
#define BT_RF_PLL_OPENLOOP_SRC_MSK     (0x1UL << BT_RF_PLL_OPENLOOP_SRC_POS)/*!< Signal source of PLL open loop; 0: hw; 1: sw*/
#define BT_RF_PLL_OPENLOOP_SRC         BT_RF_PLL_OPENLOOP_SRC_MSK
#define BT_RF_PLL_OPENLOOP_SRC_W(X)    ((X) << BT_RF_PLL_OPENLOOP_SRC_POS)
#define BT_RF_RCCAL_PUP_SRC_POS        (8U)
#define BT_RF_RCCAL_PUP_SRC_MSK        (0x1UL << BT_RF_RCCAL_PUP_SRC_POS)/*!< Signal source of Rx RC calibration power up; 0: hw; 1: sw*/
#define BT_RF_RCCAL_PUP_SRC            BT_RF_RCCAL_PUP_SRC_MSK
#define BT_RF_RCCAL_PUP_SRC_W(X)       ((X) << BT_RF_RCCAL_PUP_SRC_POS)
#define BT_RF_LNA_PUP_SRC_POS          (9U)
#define BT_RF_LNA_PUP_SRC_MSK          (0x1UL << BT_RF_LNA_PUP_SRC_POS)/*!< Signal source of LNA power up; 0: hw; 1: sw*/
#define BT_RF_LNA_PUP_SRC              BT_RF_LNA_PUP_SRC_MSK
#define BT_RF_LNA_PUP_SRC_W(X)         ((X) << BT_RF_LNA_PUP_SRC_POS)
#define BT_RF_PKD_PUP_SRC_POS          (10U)
#define BT_RF_PKD_PUP_SRC_MSK          (0x1UL << BT_RF_PKD_PUP_SRC_POS)/*!< Signal source of Peak Detector power up; 0: hw; 1: sw*/
#define BT_RF_PKD_PUP_SRC              BT_RF_PKD_PUP_SRC_MSK
#define BT_RF_PKD_PUP_SRC_W(X)         ((X) << BT_RF_PKD_PUP_SRC_POS)
#define BT_RF_CBPF_ORDER_SRC_POS       (11U)
#define BT_RF_CBPF_ORDER_SRC_MSK       (0x1UL << BT_RF_CBPF_ORDER_SRC_POS)/*!< Signal source of CPBF order; 0: hw; 1: sw*/
#define BT_RF_CBPF_ORDER_SRC           BT_RF_CBPF_ORDER_SRC_MSK
#define BT_RF_CBPF_ORDER_SRC_W(X)      ((X) << BT_RF_CBPF_ORDER_SRC_POS)
#define BT_RF_CBPF1_PUP_SRC_POS        (12U)
#define BT_RF_CBPF1_PUP_SRC_MSK        (0x1UL << BT_RF_CBPF1_PUP_SRC_POS)/*!< Signal source of CBPF1 power up; 0: hw; 1: sw*/
#define BT_RF_CBPF1_PUP_SRC            BT_RF_CBPF1_PUP_SRC_MSK
#define BT_RF_CBPF1_PUP_SRC_W(X)       ((X) << BT_RF_CBPF1_PUP_SRC_POS)
#define BT_RF_PKD_RSTN_SRC_POS         (13U)
#define BT_RF_PKD_RSTN_SRC_MSK         (0x1UL << BT_RF_PKD_RSTN_SRC_POS)/*!< Signal source of Peak Detector rstn; 0: hw; 1: sw*/
#define BT_RF_PKD_RSTN_SRC             BT_RF_PKD_RSTN_SRC_MSK
#define BT_RF_PKD_RSTN_SRC_W(X)        ((X) << BT_RF_PKD_RSTN_SRC_POS)
#define BT_RF_RXDCOC_PUP_SRC_POS       (14U)
#define BT_RF_RXDCOC_PUP_SRC_MSK       (0x1UL << BT_RF_RXDCOC_PUP_SRC_POS)/*!< Signal source of Rx DCOC power up; 0: hw; 1: sw*/
#define BT_RF_RXDCOC_PUP_SRC           BT_RF_RXDCOC_PUP_SRC_MSK
#define BT_RF_RXDCOC_PUP_SRC_W(X)      ((X) << BT_RF_RXDCOC_PUP_SRC_POS)
#define BT_RF_ADC_PUP_SRC_POS          (15U)
#define BT_RF_ADC_PUP_SRC_MSK          (0x1UL << BT_RF_ADC_PUP_SRC_POS)/*!< Signal source of Rx ADC power up; 0: hw; 1: sw*/
#define BT_RF_ADC_PUP_SRC              BT_RF_ADC_PUP_SRC_MSK
#define BT_RF_ADC_PUP_SRC_W(X)         ((X) << BT_RF_ADC_PUP_SRC_POS)
#define BT_RF_TXPA_PUP_SRC_POS         (16U)
#define BT_RF_TXPA_PUP_SRC_MSK         (0x1UL << BT_RF_TXPA_PUP_SRC_POS)/*!< Signal source of Tx PA power up; 0: hw; 1: sw*/
#define BT_RF_TXPA_PUP_SRC             BT_RF_TXPA_PUP_SRC_MSK
#define BT_RF_TXPA_PUP_SRC_W(X)        ((X) << BT_RF_TXPA_PUP_SRC_POS)
#define BT_RF_TXMIX_PUP_SRC_POS        (17U)
#define BT_RF_TXMIX_PUP_SRC_MSK        (0x1UL << BT_RF_TXMIX_PUP_SRC_POS)/*!< Signal source of Tx Mixer power up; 0: hw; 1: sw*/
#define BT_RF_TXMIX_PUP_SRC            BT_RF_TXMIX_PUP_SRC_MSK
#define BT_RF_TXMIX_PUP_SRC_W(X)       ((X) << BT_RF_TXMIX_PUP_SRC_POS)
#define BT_RF_TXLPF_PUP_SRC_POS        (18U)
#define BT_RF_TXLPF_PUP_SRC_MSK        (0x1UL << BT_RF_TXLPF_PUP_SRC_POS)/*!< Signal source of Tx LPF power up; 0: hw; 1: sw*/
#define BT_RF_TXLPF_PUP_SRC            BT_RF_TXLPF_PUP_SRC_MSK
#define BT_RF_TXLPF_PUP_SRC_W(X)       ((X) << BT_RF_TXLPF_PUP_SRC_POS)
#define BT_RF_TXLPF_COMP_PUP_SRC_POS   (19U)
#define BT_RF_TXLPF_COMP_PUP_SRC_MSK   (0x1UL << BT_RF_TXLPF_COMP_PUP_SRC_POS)/*!< Signal source of Tx LPF comparator power up; 0: hw; 1: sw*/
#define BT_RF_TXLPF_COMP_PUP_SRC       BT_RF_TXLPF_COMP_PUP_SRC_MSK
#define BT_RF_TXLPF_COMP_PUP_SRC_W(X)  ((X) << BT_RF_TXLPF_COMP_PUP_SRC_POS)
#define BT_RF_TXDAC_PUP_SRC_POS        (20U)
#define BT_RF_TXDAC_PUP_SRC_MSK        (0x1UL << BT_RF_TXDAC_PUP_SRC_POS)/*!< Signal source of Tx IQ DAC power up; 0: hw; 1: sw*/
#define BT_RF_TXDAC_PUP_SRC            BT_RF_TXDAC_PUP_SRC_MSK
#define BT_RF_TXDAC_PUP_SRC_W(X)       ((X) << BT_RF_TXDAC_PUP_SRC_POS)
#define BT_RF_CBPF_CCODE_SRC_POS       (21U)
#define BT_RF_CBPF_CCODE_SRC_MSK       (0x1UL << BT_RF_CBPF_CCODE_SRC_POS)/*!< Signal source of CBPF cap code; 0: hw; 1: sw*/
#define BT_RF_CBPF_CCODE_SRC           BT_RF_CBPF_CCODE_SRC_MSK
#define BT_RF_CBPF_CCODE_SRC_W(X)      ((X) << BT_RF_CBPF_CCODE_SRC_POS)
#define BT_RF_PA_PWR_SRC_POS           (22U)
#define BT_RF_PA_PWR_SRC_MSK           (0x1UL << BT_RF_PA_PWR_SRC_POS)/*!< Signal source of Tx PA target power; 0: hw; 1: sw*/
#define BT_RF_PA_PWR_SRC               BT_RF_PA_PWR_SRC_MSK
#define BT_RF_PA_PWR_SRC_W(X)          ((X) << BT_RF_PA_PWR_SRC_POS)


//bt_rf_2 offsetaddress : 0x08
//bt_rf_2 RegResetValue : 0xNone
#define BT_RF_RCCAL_RUN_SW_POS         (0U)
#define BT_RF_RCCAL_RUN_SW_MSK         (0x1UL << BT_RF_RCCAL_RUN_SW_POS)/*!< Signal source of Rx RC calibration run; 0: hw; 1: sw*/
#define BT_RF_RCCAL_RUN_SW             BT_RF_RCCAL_RUN_SW_MSK
#define BT_RF_RCCAL_RUN_SW_W(X)        ((X) << BT_RF_RCCAL_RUN_SW_POS)
#define BT_RF_VCOCAL_RUN_SW_POS        (1U)
#define BT_RF_VCOCAL_RUN_SW_MSK        (0x1UL << BT_RF_VCOCAL_RUN_SW_POS)/*!< Signal source of VCO calibration run; 0: hw; 1: sw*/
#define BT_RF_VCOCAL_RUN_SW            BT_RF_VCOCAL_RUN_SW_MSK
#define BT_RF_VCOCAL_RUN_SW_W(X)       ((X) << BT_RF_VCOCAL_RUN_SW_POS)
#define BT_RF_TPCAL_RUN_SW_POS         (2U)
#define BT_RF_TPCAL_RUN_SW_MSK         (0x1UL << BT_RF_TPCAL_RUN_SW_POS)/*!< Signal source of Tx TP calibration run; 0: hw; 1: sw*/
#define BT_RF_TPCAL_RUN_SW             BT_RF_TPCAL_RUN_SW_MSK
#define BT_RF_TPCAL_RUN_SW_W(X)        ((X) << BT_RF_TPCAL_RUN_SW_POS)
#define BT_RF_TXDCOC_RUN_SW_POS        (3U)
#define BT_RF_TXDCOC_RUN_SW_MSK        (0x1UL << BT_RF_TXDCOC_RUN_SW_POS)/*!< Signal source of Tx DCOC calibration run; 0: hw; 1: sw*/
#define BT_RF_TXDCOC_RUN_SW            BT_RF_TXDCOC_RUN_SW_MSK
#define BT_RF_TXDCOC_RUN_SW_W(X)       ((X) << BT_RF_TXDCOC_RUN_SW_POS)
#define BT_RF_RXDCOC_RUN_SW_POS        (4U)
#define BT_RF_RXDCOC_RUN_SW_MSK        (0x1UL << BT_RF_RXDCOC_RUN_SW_POS)/*!< Signal source of Rx DCOC calibration run; 0: hw; 1: sw*/
#define BT_RF_RXDCOC_RUN_SW            BT_RF_RXDCOC_RUN_SW_MSK
#define BT_RF_RXDCOC_RUN_SW_W(X)       ((X) << BT_RF_RXDCOC_RUN_SW_POS)
#define BT_RF_MMD_EN_SW_POS            (5U)
#define BT_RF_MMD_EN_SW_MSK            (0x1UL << BT_RF_MMD_EN_SW_POS)/*!< Signal source of MMD enable; 0: hw; 1: sw*/
#define BT_RF_MMD_EN_SW                BT_RF_MMD_EN_SW_MSK
#define BT_RF_MMD_EN_SW_W(X)           ((X) << BT_RF_MMD_EN_SW_POS)
#define BT_RF_TX_TPCAL_EN_SW_POS       (6U)
#define BT_RF_TX_TPCAL_EN_SW_MSK       (0x1UL << BT_RF_TX_TPCAL_EN_SW_POS)/*!< Signal source of Tx TP calibration enable; 0: hw; 1: sw*/
#define BT_RF_TX_TPCAL_EN_SW           BT_RF_TX_TPCAL_EN_SW_MSK
#define BT_RF_TX_TPCAL_EN_SW_W(X)      ((X) << BT_RF_TX_TPCAL_EN_SW_POS)
#define BT_RF_TX_TPMOD_EN_SW_POS       (7U)
#define BT_RF_TX_TPMOD_EN_SW_MSK       (0x1UL << BT_RF_TX_TPMOD_EN_SW_POS)/*!< Signal source of Tx TP modulation enable; 0: hw; 1: sw*/
#define BT_RF_TX_TPMOD_EN_SW           BT_RF_TX_TPMOD_EN_SW_MSK
#define BT_RF_TX_TPMOD_EN_SW_W(X)      ((X) << BT_RF_TX_TPMOD_EN_SW_POS)
#define BT_RF_TX_IQMOD_EN_SW_POS       (8U)
#define BT_RF_TX_IQMOD_EN_SW_MSK       (0x1UL << BT_RF_TX_IQMOD_EN_SW_POS)/*!< Signal source of Tx IQ modulation enable; 0: hw; 1: sw*/
#define BT_RF_TX_IQMOD_EN_SW           BT_RF_TX_IQMOD_EN_SW_MSK
#define BT_RF_TX_IQMOD_EN_SW_W(X)      ((X) << BT_RF_TX_IQMOD_EN_SW_POS)
#define BT_RF_PA_RAMP_SW_POS           (9U)
#define BT_RF_PA_RAMP_SW_MSK           (0x1UL << BT_RF_PA_RAMP_SW_POS)/*!< Signal source of Tx PA ramp; 0: hw; 1: sw*/
#define BT_RF_PA_RAMP_SW               BT_RF_PA_RAMP_SW_MSK
#define BT_RF_PA_RAMP_SW_W(X)          ((X) << BT_RF_PA_RAMP_SW_POS)
#define BT_RF_RX_ON_SW_POS             (10U)
#define BT_RF_RX_ON_SW_MSK             (0x1UL << BT_RF_RX_ON_SW_POS)/*!< Signal source of rx on; 0: hw; 1: sw*/
#define BT_RF_RX_ON_SW                 BT_RF_RX_ON_SW_MSK
#define BT_RF_RX_ON_SW_W(X)            ((X) << BT_RF_RX_ON_SW_POS)
#define BT_RF_BG_PUP_SW_POS            (11U)
#define BT_RF_BG_PUP_SW_MSK            (0x1UL << BT_RF_BG_PUP_SW_POS)/*!< Signal source of bandgap power up; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_SW                BT_RF_BG_PUP_SW_MSK
#define BT_RF_BG_PUP_SW_W(X)           ((X) << BT_RF_BG_PUP_SW_POS)
#define BT_RF_BG_FCHG_SW_POS           (12U)
#define BT_RF_BG_FCHG_SW_MSK           (0x1UL << BT_RF_BG_FCHG_SW_POS)/*!< Signal source of bandgap fast charge; 0: hw; 1: sw*/
#define BT_RF_BG_FCHG_SW               BT_RF_BG_FCHG_SW_MSK
#define BT_RF_BG_FCHG_SW_W(X)          ((X) << BT_RF_BG_FCHG_SW_POS)
#define BT_RF_BG_PUP_IBG_RX_SW_POS     (13U)
#define BT_RF_BG_PUP_IBG_RX_SW_MSK     (0x1UL << BT_RF_BG_PUP_IBG_RX_SW_POS)/*!< Signal source of rx; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_RX_SW         BT_RF_BG_PUP_IBG_RX_SW_MSK
#define BT_RF_BG_PUP_IBG_RX_SW_W(X)    ((X) << BT_RF_BG_PUP_IBG_RX_SW_POS)
#define BT_RF_BG_PUP_IBG_TX_SW_POS     (14U)
#define BT_RF_BG_PUP_IBG_TX_SW_MSK     (0x1UL << BT_RF_BG_PUP_IBG_TX_SW_POS)/*!< Signal source of tx; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_TX_SW         BT_RF_BG_PUP_IBG_TX_SW_MSK
#define BT_RF_BG_PUP_IBG_TX_SW_W(X)    ((X) << BT_RF_BG_PUP_IBG_TX_SW_POS)
#define BT_RF_BG_PUP_IBG_PLL_SW_POS    (15U)
#define BT_RF_BG_PUP_IBG_PLL_SW_MSK    (0x1UL << BT_RF_BG_PUP_IBG_PLL_SW_POS)/*!< Signal source of pll ; 0: hw; 1: sw*/
#define BT_RF_BG_PUP_IBG_PLL_SW        BT_RF_BG_PUP_IBG_PLL_SW_MSK
#define BT_RF_BG_PUP_IBG_PLL_SW_W(X)   ((X) << BT_RF_BG_PUP_IBG_PLL_SW_POS)
#define BT_RF_LDO_ISO_PUP_SW_POS       (16U)
#define BT_RF_LDO_ISO_PUP_SW_MSK       (0x1UL << BT_RF_LDO_ISO_PUP_SW_POS)/*!< Signal source of iso LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_ISO_PUP_SW           BT_RF_LDO_ISO_PUP_SW_MSK
#define BT_RF_LDO_ISO_PUP_SW_W(X)      ((X) << BT_RF_LDO_ISO_PUP_SW_POS)
#define BT_RF_LDO_RF_PUP_SW_POS        (17U)
#define BT_RF_LDO_RF_PUP_SW_MSK        (0x1UL << BT_RF_LDO_RF_PUP_SW_POS)/*!< Signal source of RF LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_RF_PUP_SW            BT_RF_LDO_RF_PUP_SW_MSK
#define BT_RF_LDO_RF_PUP_SW_W(X)       ((X) << BT_RF_LDO_RF_PUP_SW_POS)
#define BT_RF_LDO_RF_FCHG_SW_POS       (18U)
#define BT_RF_LDO_RF_FCHG_SW_MSK       (0x1UL << BT_RF_LDO_RF_FCHG_SW_POS)/*!< Signal source of RF LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_RF_FCHG_SW           BT_RF_LDO_RF_FCHG_SW_MSK
#define BT_RF_LDO_RF_FCHG_SW_W(X)      ((X) << BT_RF_LDO_RF_FCHG_SW_POS)
#define BT_RF_LDO_BB_PUP_SW_POS        (19U)
#define BT_RF_LDO_BB_PUP_SW_MSK        (0x1UL << BT_RF_LDO_BB_PUP_SW_POS)/*!< Signal source of BB LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_BB_PUP_SW            BT_RF_LDO_BB_PUP_SW_MSK
#define BT_RF_LDO_BB_PUP_SW_W(X)       ((X) << BT_RF_LDO_BB_PUP_SW_POS)
#define BT_RF_LDO_BB_FCHG_SW_POS       (20U)
#define BT_RF_LDO_BB_FCHG_SW_MSK       (0x1UL << BT_RF_LDO_BB_FCHG_SW_POS)/*!< Signal source of BB LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_BB_FCHG_SW           BT_RF_LDO_BB_FCHG_SW_MSK
#define BT_RF_LDO_BB_FCHG_SW_W(X)      ((X) << BT_RF_LDO_BB_FCHG_SW_POS)
#define BT_RF_LDO_PLL_PUP_SW_POS       (21U)
#define BT_RF_LDO_PLL_PUP_SW_MSK       (0x1UL << BT_RF_LDO_PLL_PUP_SW_POS)/*!< Signal source of PLL LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PLL_PUP_SW           BT_RF_LDO_PLL_PUP_SW_MSK
#define BT_RF_LDO_PLL_PUP_SW_W(X)      ((X) << BT_RF_LDO_PLL_PUP_SW_POS)
#define BT_RF_LDO_PLL_FCHG_SW_POS      (22U)
#define BT_RF_LDO_PLL_FCHG_SW_MSK      (0x1UL << BT_RF_LDO_PLL_FCHG_SW_POS)/*!< Signal source of PLL LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_PLL_FCHG_SW          BT_RF_LDO_PLL_FCHG_SW_MSK
#define BT_RF_LDO_PLL_FCHG_SW_W(X)     ((X) << BT_RF_LDO_PLL_FCHG_SW_POS)
#define BT_RF_LDO_VCO_PUP_SW_POS       (23U)
#define BT_RF_LDO_VCO_PUP_SW_MSK       (0x1UL << BT_RF_LDO_VCO_PUP_SW_POS)/*!< Signal source of VCO LDO power up; 0: hw; 1: sw*/
#define BT_RF_LDO_VCO_PUP_SW           BT_RF_LDO_VCO_PUP_SW_MSK
#define BT_RF_LDO_VCO_PUP_SW_W(X)      ((X) << BT_RF_LDO_VCO_PUP_SW_POS)
#define BT_RF_LDO_VCO_FCHG_SW_POS      (24U)
#define BT_RF_LDO_VCO_FCHG_SW_MSK      (0x1UL << BT_RF_LDO_VCO_FCHG_SW_POS)/*!< Signal source of VCO LDO fast charge; 0: hw; 1: sw*/
#define BT_RF_LDO_VCO_FCHG_SW          BT_RF_LDO_VCO_FCHG_SW_MSK
#define BT_RF_LDO_VCO_FCHG_SW_W(X)     ((X) << BT_RF_LDO_VCO_FCHG_SW_POS)
#define BT_RF_LDO_PA_PUP_VBAT_SW_POS   (25U)
#define BT_RF_LDO_PA_PUP_VBAT_SW_MSK   (0x1UL << BT_RF_LDO_PA_PUP_VBAT_SW_POS)/*!< Signal source of Tx PA vbat power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PA_PUP_VBAT_SW       BT_RF_LDO_PA_PUP_VBAT_SW_MSK
#define BT_RF_LDO_PA_PUP_VBAT_SW_W(X)  ((X) << BT_RF_LDO_PA_PUP_VBAT_SW_POS)
#define BT_RF_LDO_PA_PUP_VBUCK_SW_POS  (26U)
#define BT_RF_LDO_PA_PUP_VBUCK_SW_MSK  (0x1UL << BT_RF_LDO_PA_PUP_VBUCK_SW_POS)/*!< Signal source of Tx PA vbuck power up; 0: hw; 1: sw*/
#define BT_RF_LDO_PA_PUP_VBUCK_SW      BT_RF_LDO_PA_PUP_VBUCK_SW_MSK
#define BT_RF_LDO_PA_PUP_VBUCK_SW_W(X) ((X) << BT_RF_LDO_PA_PUP_VBUCK_SW_POS)
#define BT_RF_VCO_PUP_SW_POS           (27U)
#define BT_RF_VCO_PUP_SW_MSK           (0x1UL << BT_RF_VCO_PUP_SW_POS)/*!< Signal source of VCO power up; 0: hw; 1: sw*/
#define BT_RF_VCO_PUP_SW               BT_RF_VCO_PUP_SW_MSK
#define BT_RF_VCO_PUP_SW_W(X)          ((X) << BT_RF_VCO_PUP_SW_POS)
#define BT_RF_VCODIV_PUP_SW_POS        (28U)
#define BT_RF_VCODIV_PUP_SW_MSK        (0x1UL << BT_RF_VCODIV_PUP_SW_POS)/*!< Signal source of VCO divider power up; 0: hw; 1: sw*/
#define BT_RF_VCODIV_PUP_SW            BT_RF_VCODIV_PUP_SW_MSK
#define BT_RF_VCODIV_PUP_SW_W(X)       ((X) << BT_RF_VCODIV_PUP_SW_POS)
#define BT_RF_DAC_PUP_SW_POS           (29U)
#define BT_RF_DAC_PUP_SW_MSK           (0x1UL << BT_RF_DAC_PUP_SW_POS)/*!< Signal source of Tx TP DAC power up; 0: hw; 1: sw*/
#define BT_RF_DAC_PUP_SW               BT_RF_DAC_PUP_SW_MSK
#define BT_RF_DAC_PUP_SW_W(X)          ((X) << BT_RF_DAC_PUP_SW_POS)
#define BT_RF_LORX_PUP_SW_POS          (30U)
#define BT_RF_LORX_PUP_SW_MSK          (0x1UL << BT_RF_LORX_PUP_SW_POS)/*!< Signal source of Rx LO power up; 0: hw; 1: sw*/
#define BT_RF_LORX_PUP_SW              BT_RF_LORX_PUP_SW_MSK
#define BT_RF_LORX_PUP_SW_W(X)         ((X) << BT_RF_LORX_PUP_SW_POS)
#define BT_RF_LORX_PUP_DRV_SW_POS      (31U)
#define BT_RF_LORX_PUP_DRV_SW_MSK      (0x1UL << BT_RF_LORX_PUP_DRV_SW_POS)/*!< Signal source of Rx LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LORX_PUP_DRV_SW          BT_RF_LORX_PUP_DRV_SW_MSK
#define BT_RF_LORX_PUP_DRV_SW_W(X)     ((X) << BT_RF_LORX_PUP_DRV_SW_POS)


//bt_rf_3 offsetaddress : 0x0c
//bt_rf_3 RegResetValue : 0xNone
#define BT_RF_LOTX_PUP_IQ_SW_POS       (0U)
#define BT_RF_LOTX_PUP_IQ_SW_MSK       (0x1UL << BT_RF_LOTX_PUP_IQ_SW_POS)/*!< Signal source of Tx LO power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_IQ_SW           BT_RF_LOTX_PUP_IQ_SW_MSK
#define BT_RF_LOTX_PUP_IQ_SW_W(X)      ((X) << BT_RF_LOTX_PUP_IQ_SW_POS)
#define BT_RF_LOTX_PUP_IQDRV_SW_POS    (1U)
#define BT_RF_LOTX_PUP_IQDRV_SW_MSK    (0x1UL << BT_RF_LOTX_PUP_IQDRV_SW_POS)/*!< Signal source of Tx LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_IQDRV_SW        BT_RF_LOTX_PUP_IQDRV_SW_MSK
#define BT_RF_LOTX_PUP_IQDRV_SW_W(X)   ((X) << BT_RF_LOTX_PUP_IQDRV_SW_POS)
#define BT_RF_LOTX_PUP_GFSK_SW_POS     (2U)
#define BT_RF_LOTX_PUP_GFSK_SW_MSK     (0x1UL << BT_RF_LOTX_PUP_GFSK_SW_POS)/*!< Signal source of Tx GFSK LO power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_GFSK_SW         BT_RF_LOTX_PUP_GFSK_SW_MSK
#define BT_RF_LOTX_PUP_GFSK_SW_W(X)    ((X) << BT_RF_LOTX_PUP_GFSK_SW_POS)
#define BT_RF_LOTX_PUP_GFSKDRV_SW_POS  (3U)
#define BT_RF_LOTX_PUP_GFSKDRV_SW_MSK  (0x1UL << BT_RF_LOTX_PUP_GFSKDRV_SW_POS)/*!< Signal source of Tx GFSK LO driver power up; 0: hw; 1: sw*/
#define BT_RF_LOTX_PUP_GFSKDRV_SW      BT_RF_LOTX_PUP_GFSKDRV_SW_MSK
#define BT_RF_LOTX_PUP_GFSKDRV_SW_W(X) ((X) << BT_RF_LOTX_PUP_GFSKDRV_SW_POS)
#define BT_RF_FCAL_PUP_SW_POS          (4U)
#define BT_RF_FCAL_PUP_SW_MSK          (0x1UL << BT_RF_FCAL_PUP_SW_POS)/*!< Signal source of FCAL power up; 0: hw; 1: sw*/
#define BT_RF_FCAL_PUP_SW              BT_RF_FCAL_PUP_SW_MSK
#define BT_RF_FCAL_PUP_SW_W(X)         ((X) << BT_RF_FCAL_PUP_SW_POS)
#define BT_RF_DIVN_PUP_SW_POS          (5U)
#define BT_RF_DIVN_PUP_SW_MSK          (0x1UL << BT_RF_DIVN_PUP_SW_POS)/*!< Signal source of PLL loop divider power up; 0: hw; 1: sw*/
#define BT_RF_DIVN_PUP_SW              BT_RF_DIVN_PUP_SW_MSK
#define BT_RF_DIVN_PUP_SW_W(X)         ((X) << BT_RF_DIVN_PUP_SW_POS)
#define BT_RF_PFDCP_PUP_SW_POS         (6U)
#define BT_RF_PFDCP_PUP_SW_MSK         (0x1UL << BT_RF_PFDCP_PUP_SW_POS)/*!< Signal source of PFD/CP power up; 0: hw; 1: sw*/
#define BT_RF_PFDCP_PUP_SW             BT_RF_PFDCP_PUP_SW_MSK
#define BT_RF_PFDCP_PUP_SW_W(X)        ((X) << BT_RF_PFDCP_PUP_SW_POS)
#define BT_RF_PLL_OPENLOOP_SW_POS      (7U)
#define BT_RF_PLL_OPENLOOP_SW_MSK      (0x1UL << BT_RF_PLL_OPENLOOP_SW_POS)/*!< Signal source of PLL open loop; 0: hw; 1: sw*/
#define BT_RF_PLL_OPENLOOP_SW          BT_RF_PLL_OPENLOOP_SW_MSK
#define BT_RF_PLL_OPENLOOP_SW_W(X)     ((X) << BT_RF_PLL_OPENLOOP_SW_POS)
#define BT_RF_RCCAL_PUP_SW_POS         (8U)
#define BT_RF_RCCAL_PUP_SW_MSK         (0x1UL << BT_RF_RCCAL_PUP_SW_POS)/*!< Signal source of Rx RC calibration power up; 0: hw; 1: sw*/
#define BT_RF_RCCAL_PUP_SW             BT_RF_RCCAL_PUP_SW_MSK
#define BT_RF_RCCAL_PUP_SW_W(X)        ((X) << BT_RF_RCCAL_PUP_SW_POS)
#define BT_RF_LNA_PUP_SW_POS           (9U)
#define BT_RF_LNA_PUP_SW_MSK           (0x1UL << BT_RF_LNA_PUP_SW_POS)/*!< Signal source of LNA power up; 0: hw; 1: sw*/
#define BT_RF_LNA_PUP_SW               BT_RF_LNA_PUP_SW_MSK
#define BT_RF_LNA_PUP_SW_W(X)          ((X) << BT_RF_LNA_PUP_SW_POS)
#define BT_RF_PKD_PUP_SW_POS           (10U)
#define BT_RF_PKD_PUP_SW_MSK           (0x1UL << BT_RF_PKD_PUP_SW_POS)/*!< Signal source of Peak Detector power up; 0: hw; 1: sw*/
#define BT_RF_PKD_PUP_SW               BT_RF_PKD_PUP_SW_MSK
#define BT_RF_PKD_PUP_SW_W(X)          ((X) << BT_RF_PKD_PUP_SW_POS)
#define BT_RF_CBPF_ORDER_SW_POS        (11U)
#define BT_RF_CBPF_ORDER_SW_MSK        (0x1UL << BT_RF_CBPF_ORDER_SW_POS)/*!< Signal source of CPBF order; 0: hw; 1: sw*/
#define BT_RF_CBPF_ORDER_SW            BT_RF_CBPF_ORDER_SW_MSK
#define BT_RF_CBPF_ORDER_SW_W(X)       ((X) << BT_RF_CBPF_ORDER_SW_POS)
#define BT_RF_CBPF1_PUP_SW_POS         (12U)
#define BT_RF_CBPF1_PUP_SW_MSK         (0x1UL << BT_RF_CBPF1_PUP_SW_POS)/*!< Signal source of CBPF1 power up; 0: hw; 1: sw*/
#define BT_RF_CBPF1_PUP_SW             BT_RF_CBPF1_PUP_SW_MSK
#define BT_RF_CBPF1_PUP_SW_W(X)        ((X) << BT_RF_CBPF1_PUP_SW_POS)
#define BT_RF_PKD_RSTN_SW_POS          (13U)
#define BT_RF_PKD_RSTN_SW_MSK          (0x1UL << BT_RF_PKD_RSTN_SW_POS)/*!< Signal source of Peak Detector rstn; 0: hw; 1: sw*/
#define BT_RF_PKD_RSTN_SW              BT_RF_PKD_RSTN_SW_MSK
#define BT_RF_PKD_RSTN_SW_W(X)         ((X) << BT_RF_PKD_RSTN_SW_POS)
#define BT_RF_RXDCOC_PUP_SW_POS        (14U)
#define BT_RF_RXDCOC_PUP_SW_MSK        (0x1UL << BT_RF_RXDCOC_PUP_SW_POS)/*!< Signal source of Rx DCOC power up; 0: hw; 1: sw*/
#define BT_RF_RXDCOC_PUP_SW            BT_RF_RXDCOC_PUP_SW_MSK
#define BT_RF_RXDCOC_PUP_SW_W(X)       ((X) << BT_RF_RXDCOC_PUP_SW_POS)
#define BT_RF_ADC_PUP_SW_POS           (15U)
#define BT_RF_ADC_PUP_SW_MSK           (0x1UL << BT_RF_ADC_PUP_SW_POS)/*!< Signal source of Rx ADC power up; 0: hw; 1: sw*/
#define BT_RF_ADC_PUP_SW               BT_RF_ADC_PUP_SW_MSK
#define BT_RF_ADC_PUP_SW_W(X)          ((X) << BT_RF_ADC_PUP_SW_POS)
#define BT_RF_TXPA_PUP_SW_POS          (16U)
#define BT_RF_TXPA_PUP_SW_MSK          (0x1UL << BT_RF_TXPA_PUP_SW_POS)/*!< Signal source of Tx PA power up; 0: hw; 1: sw*/
#define BT_RF_TXPA_PUP_SW              BT_RF_TXPA_PUP_SW_MSK
#define BT_RF_TXPA_PUP_SW_W(X)         ((X) << BT_RF_TXPA_PUP_SW_POS)
#define BT_RF_TXMIX_PUP_SW_POS         (17U)
#define BT_RF_TXMIX_PUP_SW_MSK         (0x1UL << BT_RF_TXMIX_PUP_SW_POS)/*!< Signal source of Tx Mixer power up; 0: hw; 1: sw*/
#define BT_RF_TXMIX_PUP_SW             BT_RF_TXMIX_PUP_SW_MSK
#define BT_RF_TXMIX_PUP_SW_W(X)        ((X) << BT_RF_TXMIX_PUP_SW_POS)
#define BT_RF_TXLPF_PUP_SW_POS         (18U)
#define BT_RF_TXLPF_PUP_SW_MSK         (0x1UL << BT_RF_TXLPF_PUP_SW_POS)/*!< Signal source of Tx LPF power up; 0: hw; 1: sw*/
#define BT_RF_TXLPF_PUP_SW             BT_RF_TXLPF_PUP_SW_MSK
#define BT_RF_TXLPF_PUP_SW_W(X)        ((X) << BT_RF_TXLPF_PUP_SW_POS)
#define BT_RF_TXLPF_COMP_PUP_SW_POS    (19U)
#define BT_RF_TXLPF_COMP_PUP_SW_MSK    (0x1UL << BT_RF_TXLPF_COMP_PUP_SW_POS)/*!< Signal source of Tx LPF comparator power up; 0: hw; 1: sw*/
#define BT_RF_TXLPF_COMP_PUP_SW        BT_RF_TXLPF_COMP_PUP_SW_MSK
#define BT_RF_TXLPF_COMP_PUP_SW_W(X)   ((X) << BT_RF_TXLPF_COMP_PUP_SW_POS)
#define BT_RF_TXDAC_PUP_SW_POS         (20U)
#define BT_RF_TXDAC_PUP_SW_MSK         (0x1UL << BT_RF_TXDAC_PUP_SW_POS)/*!< Signal source of Tx IQ DAC power up; 0: hw; 1: sw*/
#define BT_RF_TXDAC_PUP_SW             BT_RF_TXDAC_PUP_SW_MSK
#define BT_RF_TXDAC_PUP_SW_W(X)        ((X) << BT_RF_TXDAC_PUP_SW_POS)
#define BT_RF_CBPF_CCODE_SW_POS        (21U)
#define BT_RF_CBPF_CCODE_SW_MSK        (0x1fUL << BT_RF_CBPF_CCODE_SW_POS)/*!< Signal source of CBPF cap code; 0: hw; 1: sw*/
#define BT_RF_CBPF_CCODE_SW            BT_RF_CBPF_CCODE_SW_MSK
#define BT_RF_CBPF_CCODE_SW_W(X)       ((X) << BT_RF_CBPF_CCODE_SW_POS)
#define BT_RF_PA_PWR_SW_POS            (26U)
#define BT_RF_PA_PWR_SW_MSK            (0x3fUL << BT_RF_PA_PWR_SW_POS)/*!< Signal source of Tx PA target power; 0: hw; 1: sw*/
#define BT_RF_PA_PWR_SW                BT_RF_PA_PWR_SW_MSK
#define BT_RF_PA_PWR_SW_W(X)           ((X) << BT_RF_PA_PWR_SW_POS)


//bt_rf_4 offsetaddress : 0x10
//bt_rf_4 RegResetValue : 0xNone
#define BT_RF_BYPASS_RCCAL_POS         (0U)
#define BT_RF_BYPASS_RCCAL_MSK         (0x1UL << BT_RF_BYPASS_RCCAL_POS)/*!< Rx RC calibration bypass*/
#define BT_RF_BYPASS_RCCAL             BT_RF_BYPASS_RCCAL_MSK
#define BT_RF_BYPASS_RCCAL_W(X)        ((X) << BT_RF_BYPASS_RCCAL_POS)
#define BT_RF_BYPASS_TXVCOCAL_POS      (1U)
#define BT_RF_BYPASS_TXVCOCAL_MSK      (0x1UL << BT_RF_BYPASS_TXVCOCAL_POS)/*!< Tx VCO calibration bypass*/
#define BT_RF_BYPASS_TXVCOCAL          BT_RF_BYPASS_TXVCOCAL_MSK
#define BT_RF_BYPASS_TXVCOCAL_W(X)     ((X) << BT_RF_BYPASS_TXVCOCAL_POS)
#define BT_RF_BYPASS_RXVCOCAL_POS      (2U)
#define BT_RF_BYPASS_RXVCOCAL_MSK      (0x1UL << BT_RF_BYPASS_RXVCOCAL_POS)/*!< Rx VCO calibration bypass*/
#define BT_RF_BYPASS_RXVCOCAL          BT_RF_BYPASS_RXVCOCAL_MSK
#define BT_RF_BYPASS_RXVCOCAL_W(X)     ((X) << BT_RF_BYPASS_RXVCOCAL_POS)
#define BT_RF_BYPASS_TPCAL_POS         (3U)
#define BT_RF_BYPASS_TPCAL_MSK         (0x1UL << BT_RF_BYPASS_TPCAL_POS)/*!< Tx TP calibration bypass*/
#define BT_RF_BYPASS_TPCAL             BT_RF_BYPASS_TPCAL_MSK
#define BT_RF_BYPASS_TPCAL_W(X)        ((X) << BT_RF_BYPASS_TPCAL_POS)
#define BT_RF_BYPASS_TXDCOC_POS        (4U)
#define BT_RF_BYPASS_TXDCOC_MSK        (0x1UL << BT_RF_BYPASS_TXDCOC_POS)/*!< Tx DCOC calibration bypass*/
#define BT_RF_BYPASS_TXDCOC            BT_RF_BYPASS_TXDCOC_MSK
#define BT_RF_BYPASS_TXDCOC_W(X)       ((X) << BT_RF_BYPASS_TXDCOC_POS)
#define BT_RF_BYPASS_RXDCOC1_POS       (5U)
#define BT_RF_BYPASS_RXDCOC1_MSK       (0x1UL << BT_RF_BYPASS_RXDCOC1_POS)/*!< Rx DCOC1 calibration bypass*/
#define BT_RF_BYPASS_RXDCOC1           BT_RF_BYPASS_RXDCOC1_MSK
#define BT_RF_BYPASS_RXDCOC1_W(X)      ((X) << BT_RF_BYPASS_RXDCOC1_POS)
#define BT_RF_BYPASS_RXDCOC2_POS       (6U)
#define BT_RF_BYPASS_RXDCOC2_MSK       (0x1UL << BT_RF_BYPASS_RXDCOC2_POS)/*!< Rx DCOC2 calibration bypass*/
#define BT_RF_BYPASS_RXDCOC2           BT_RF_BYPASS_RXDCOC2_MSK
#define BT_RF_BYPASS_RXDCOC2_W(X)      ((X) << BT_RF_BYPASS_RXDCOC2_POS)
#define BT_RF_RF_PMU_TX_DLY_POS        (7U)
#define BT_RF_RF_PMU_TX_DLY_MSK        (0xfUL << BT_RF_RF_PMU_TX_DLY_POS)/*!< Wait time before bandgap and LDO power up during Tx (unit: 0.5 us)*/
#define BT_RF_RF_PMU_TX_DLY            BT_RF_RF_PMU_TX_DLY_MSK
#define BT_RF_RF_PMU_TX_DLY_W(X)       ((X) << BT_RF_RF_PMU_TX_DLY_POS)
#define BT_RF_RF_PMU_RX_DLY_POS        (11U)
#define BT_RF_RF_PMU_RX_DLY_MSK        (0xfUL << BT_RF_RF_PMU_RX_DLY_POS)/*!< Wait time before bandgap and LDO power up during Rx (unit: 0.5 us)*/
#define BT_RF_RF_PMU_RX_DLY            BT_RF_RF_PMU_RX_DLY_MSK
#define BT_RF_RF_PMU_RX_DLY_W(X)       ((X) << BT_RF_RF_PMU_RX_DLY_POS)
#define BT_RF_RF_RCCAL_DLY_POS         (15U)
#define BT_RF_RF_RCCAL_DLY_MSK         (0x1fUL << BT_RF_RF_RCCAL_DLY_POS)/*!< Wait time before RC calibration power up (unit: 0.5 us)*/
#define BT_RF_RF_RCCAL_DLY             BT_RF_RF_RCCAL_DLY_MSK
#define BT_RF_RF_RCCAL_DLY_W(X)        ((X) << BT_RF_RF_RCCAL_DLY_POS)
#define BT_RF_RF_PLL_TX_DLY_POS        (20U)
#define BT_RF_RF_PLL_TX_DLY_MSK        (0x1fUL << BT_RF_RF_PLL_TX_DLY_POS)/*!< Wait time before PLL power up during Tx (unit: 0.5 us)*/
#define BT_RF_RF_PLL_TX_DLY            BT_RF_RF_PLL_TX_DLY_MSK
#define BT_RF_RF_PLL_TX_DLY_W(X)       ((X) << BT_RF_RF_PLL_TX_DLY_POS)
#define BT_RF_RF_PLL_RX_DLY_POS        (25U)
#define BT_RF_RF_PLL_RX_DLY_MSK        (0x1fUL << BT_RF_RF_PLL_RX_DLY_POS)/*!< Wait time before PLL power up during Rx (unit: 0.5 us)*/
#define BT_RF_RF_PLL_RX_DLY            BT_RF_RF_PLL_RX_DLY_MSK
#define BT_RF_RF_PLL_RX_DLY_W(X)       ((X) << BT_RF_RF_PLL_RX_DLY_POS)
#define BT_RF_TX_ABORT_EN_POS          (30U)
#define BT_RF_TX_ABORT_EN_MSK          (0x1UL << BT_RF_TX_ABORT_EN_POS)/*!< Tx abort enable*/
#define BT_RF_TX_ABORT_EN              BT_RF_TX_ABORT_EN_MSK
#define BT_RF_TX_ABORT_EN_W(X)         ((X) << BT_RF_TX_ABORT_EN_POS)
#define BT_RF_RX_ABORT_EN_POS          (31U)
#define BT_RF_RX_ABORT_EN_MSK          (0x1UL << BT_RF_RX_ABORT_EN_POS)/*!< Rx abort enable*/
#define BT_RF_RX_ABORT_EN              BT_RF_RX_ABORT_EN_MSK
#define BT_RF_RX_ABORT_EN_W(X)         ((X) << BT_RF_RX_ABORT_EN_POS)


//bt_rf_5 offsetaddress : 0x14
//bt_rf_5 RegResetValue : 0xNone
#define BT_RF_RF_DPTH_TX_DLY_IQ_POS    (0U)
#define BT_RF_RF_DPTH_TX_DLY_IQ_MSK    (0xffUL << BT_RF_RF_DPTH_TX_DLY_IQ_POS)/*!< Wait time before Tx datapath power up in IQ mode (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_TX_DLY_IQ        BT_RF_RF_DPTH_TX_DLY_IQ_MSK
#define BT_RF_RF_DPTH_TX_DLY_IQ_W(X)   ((X) << BT_RF_RF_DPTH_TX_DLY_IQ_POS)
#define BT_RF_RF_DPTH_TX_DLY_TP_POS    (8U)
#define BT_RF_RF_DPTH_TX_DLY_TP_MSK    (0xffUL << BT_RF_RF_DPTH_TX_DLY_TP_POS)/*!< Wait time before Tx datapath power up in TP mode (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_TX_DLY_TP        BT_RF_RF_DPTH_TX_DLY_TP_MSK
#define BT_RF_RF_DPTH_TX_DLY_TP_W(X)   ((X) << BT_RF_RF_DPTH_TX_DLY_TP_POS)
#define BT_RF_RF_DPTH_RX_DLY_POS       (16U)
#define BT_RF_RF_DPTH_RX_DLY_MSK       (0xffUL << BT_RF_RF_DPTH_RX_DLY_POS)/*!< Wait time before Rx datapath power up (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_RX_DLY           BT_RF_RF_DPTH_RX_DLY_MSK
#define BT_RF_RF_DPTH_RX_DLY_W(X)      ((X) << BT_RF_RF_DPTH_RX_DLY_POS)
#define BT_RF_RESV_FIX_POS             (24U)
#define BT_RF_RESV_FIX_MSK             (0xffUL << BT_RF_RESV_FIX_POS)/*!< fixed*/
#define BT_RF_RESV_FIX                 BT_RF_RESV_FIX_MSK
#define BT_RF_RESV_FIX_W(X)            ((X) << BT_RF_RESV_FIX_POS)


//bt_rf_6 offsetaddress : 0x18
//bt_rf_6 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_6_POS     (0U)
#define BT_RF_RESV_FIX_BT_RF_6_MSK     (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_6_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_6         BT_RF_RESV_FIX_BT_RF_6_MSK
#define BT_RF_RESV_FIX_BT_RF_6_W(X)    ((X) << BT_RF_RESV_FIX_BT_RF_6_POS)


//bt_rf_7 offsetaddress : 0x1c
//bt_rf_7 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_7_POS     (0U)
#define BT_RF_RESV_FIX_BT_RF_7_MSK     (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_7_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_7         BT_RF_RESV_FIX_BT_RF_7_MSK
#define BT_RF_RESV_FIX_BT_RF_7_W(X)    ((X) << BT_RF_RESV_FIX_BT_RF_7_POS)


//bt_rf_8 offsetaddress : 0x20
//bt_rf_8 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_3_POS           (0U)
#define BT_RF_RESV_FIX_3_MSK           (0xffffffffUL << BT_RF_RESV_FIX_3_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_3               BT_RF_RESV_FIX_3_MSK
#define BT_RF_RESV_FIX_3_W(X)          ((X) << BT_RF_RESV_FIX_3_POS)
#define BT_RF_RESV_FIX_2_POS           (0U)
#define BT_RF_RESV_FIX_2_MSK           (0xfffUL << BT_RF_RESV_FIX_2_POS)/*!< */
#define BT_RF_RESV_FIX_2               BT_RF_RESV_FIX_2_MSK
#define BT_RF_RESV_FIX_2_W(X)          ((X) << BT_RF_RESV_FIX_2_POS)
#define BT_RF_MMD_RSTN_SRC_POS         (12U)
#define BT_RF_MMD_RSTN_SRC_MSK         (0x1UL << BT_RF_MMD_RSTN_SRC_POS)/*!< MMD manual/auto reset select; 0: hw; 1: sw*/
#define BT_RF_MMD_RSTN_SRC             BT_RF_MMD_RSTN_SRC_MSK
#define BT_RF_MMD_RSTN_SRC_W(X)        ((X) << BT_RF_MMD_RSTN_SRC_POS)
#define BT_RF_MMD_RSTN_SW_POS          (13U)
#define BT_RF_MMD_RSTN_SW_MSK          (0x1UL << BT_RF_MMD_RSTN_SW_POS)/*!< MMD manual reset value; 0: reset; 1: normal*/
#define BT_RF_MMD_RSTN_SW              BT_RF_MMD_RSTN_SW_MSK
#define BT_RF_MMD_RSTN_SW_W(X)         ((X) << BT_RF_MMD_RSTN_SW_POS)
#define BT_RF_RESV_FIX_1_POS           (14U)
#define BT_RF_RESV_FIX_1_MSK           (0x3fUL << BT_RF_RESV_FIX_1_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1               BT_RF_RESV_FIX_1_MSK
#define BT_RF_RESV_FIX_1_W(X)          ((X) << BT_RF_RESV_FIX_1_POS)
#define BT_RF_CBPF_MODE_POS            (20U)
#define BT_RF_CBPF_MODE_MSK            (0x1UL << BT_RF_CBPF_MODE_POS)/*!< Rx CBPF mode; 0: CBPF1 only; 1: CBPF1 + CBPF2*/
#define BT_RF_CBPF_MODE                BT_RF_CBPF_MODE_MSK
#define BT_RF_CBPF_MODE_W(X)           ((X) << BT_RF_CBPF_MODE_POS)
#define BT_RF_RESV_FIX_0_POS           (21U)
#define BT_RF_RESV_FIX_0_MSK           (0x7UL << BT_RF_RESV_FIX_0_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0               BT_RF_RESV_FIX_0_MSK
#define BT_RF_RESV_FIX_0_W(X)          ((X) << BT_RF_RESV_FIX_0_POS)
#define BT_RF_TX_IQ_TP_SEL_SRC_POS     (24U)
#define BT_RF_TX_IQ_TP_SEL_SRC_MSK     (0x1UL << BT_RF_TX_IQ_TP_SEL_SRC_POS)/*!< Tx IQ/TP manual select enable; 0: hw; 1: sw*/
#define BT_RF_TX_IQ_TP_SEL_SRC         BT_RF_TX_IQ_TP_SEL_SRC_MSK
#define BT_RF_TX_IQ_TP_SEL_SRC_W(X)    ((X) << BT_RF_TX_IQ_TP_SEL_SRC_POS)
#define BT_RF_TX_IQ_TP_SEL_SW_POS      (25U)
#define BT_RF_TX_IQ_TP_SEL_SW_MSK      (0x1UL << BT_RF_TX_IQ_TP_SEL_SW_POS)/*!< Tx IQ/TP manual select; 0: TP mode; 1: IQ mode*/
#define BT_RF_TX_IQ_TP_SEL_SW          BT_RF_TX_IQ_TP_SEL_SW_MSK
#define BT_RF_TX_IQ_TP_SEL_SW_W(X)     ((X) << BT_RF_TX_IQ_TP_SEL_SW_POS)
#define BT_RF_TX_VBAT_MODE_POS         (26U)
#define BT_RF_TX_VBAT_MODE_MSK         (0x1UL << BT_RF_TX_VBAT_MODE_POS)/*!< Tx VBAT mode; 0: off; 1: on*/
#define BT_RF_TX_VBAT_MODE             BT_RF_TX_VBAT_MODE_MSK
#define BT_RF_TX_VBAT_MODE_W(X)        ((X) << BT_RF_TX_VBAT_MODE_POS)
#define BT_RF_TX_VBUCK_MODE_POS        (27U)
#define BT_RF_TX_VBUCK_MODE_MSK        (0x1UL << BT_RF_TX_VBUCK_MODE_POS)/*!< Tx VBUCK mode; 0: off; 1: on*/
#define BT_RF_TX_VBUCK_MODE            BT_RF_TX_VBUCK_MODE_MSK
#define BT_RF_TX_VBUCK_MODE_W(X)       ((X) << BT_RF_TX_VBUCK_MODE_POS)
#define BT_RF_RESV_FIX_BT_RF_8_POS     (28U)
#define BT_RF_RESV_FIX_BT_RF_8_MSK     (0xfUL << BT_RF_RESV_FIX_BT_RF_8_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_8         BT_RF_RESV_FIX_BT_RF_8_MSK
#define BT_RF_RESV_FIX_BT_RF_8_W(X)    ((X) << BT_RF_RESV_FIX_BT_RF_8_POS)


//bt_rf_9 offsetaddress : 0x24
//bt_rf_9 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_9_POS     (0U)
#define BT_RF_RESV_FIX_BT_RF_9_MSK     (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_9_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_9         BT_RF_RESV_FIX_BT_RF_9_MSK
#define BT_RF_RESV_FIX_BT_RF_9_W(X)    ((X) << BT_RF_RESV_FIX_BT_RF_9_POS)


//bt_rf_10 offsetaddress : 0x28
//bt_rf_10 RegResetValue : 0xNone
#define BT_RF_BG_TRIM_POS              (0U)
#define BT_RF_BG_TRIM_MSK              (0x7UL << BT_RF_BG_TRIM_POS)/*!< Bandgap trim*/
#define BT_RF_BG_TRIM                  BT_RF_BG_TRIM_MSK
#define BT_RF_BG_TRIM_W(X)             ((X) << BT_RF_BG_TRIM_POS)
#define BT_RF_BG_FSTART_POS            (3U)
#define BT_RF_BG_FSTART_MSK            (0x1UL << BT_RF_BG_FSTART_POS)/*!< Force startup of bandgap*/
#define BT_RF_BG_FSTART                BT_RF_BG_FSTART_MSK
#define BT_RF_BG_FSTART_W(X)           ((X) << BT_RF_BG_FSTART_POS)
#define BT_RF_RESV_FIX_2_BT_RF_10_POS  (4U)
#define BT_RF_RESV_FIX_2_BT_RF_10_MSK  (0x1UL << BT_RF_RESV_FIX_2_BT_RF_10_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_2_BT_RF_10      BT_RF_RESV_FIX_2_BT_RF_10_MSK
#define BT_RF_RESV_FIX_2_BT_RF_10_W(X) ((X) << BT_RF_RESV_FIX_2_BT_RF_10_POS)
#define BT_RF_LDO_RF_BYPASS_POS        (5U)
#define BT_RF_LDO_RF_BYPASS_MSK        (0x1UL << BT_RF_LDO_RF_BYPASS_POS)/*!< RF LDO bypass mode; 0: off; 1: on*/
#define BT_RF_LDO_RF_BYPASS            BT_RF_LDO_RF_BYPASS_MSK
#define BT_RF_LDO_RF_BYPASS_W(X)       ((X) << BT_RF_LDO_RF_BYPASS_POS)
#define BT_RF_LDO_RF_TRIM_POS          (6U)
#define BT_RF_LDO_RF_TRIM_MSK          (0x3UL << BT_RF_LDO_RF_TRIM_POS)/*!< RF LDO trim*/
#define BT_RF_LDO_RF_TRIM              BT_RF_LDO_RF_TRIM_MSK
#define BT_RF_LDO_RF_TRIM_W(X)         ((X) << BT_RF_LDO_RF_TRIM_POS)
#define BT_RF_LDO_BB_BYPASS_POS        (8U)
#define BT_RF_LDO_BB_BYPASS_MSK        (0x1UL << BT_RF_LDO_BB_BYPASS_POS)/*!< BB LDO bypass mode; 0: off; 1: on*/
#define BT_RF_LDO_BB_BYPASS            BT_RF_LDO_BB_BYPASS_MSK
#define BT_RF_LDO_BB_BYPASS_W(X)       ((X) << BT_RF_LDO_BB_BYPASS_POS)
#define BT_RF_RESV_FIX_1_BT_RF_10_POS  (9U)
#define BT_RF_RESV_FIX_1_BT_RF_10_MSK  (0x1UL << BT_RF_RESV_FIX_1_BT_RF_10_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1_BT_RF_10      BT_RF_RESV_FIX_1_BT_RF_10_MSK
#define BT_RF_RESV_FIX_1_BT_RF_10_W(X) ((X) << BT_RF_RESV_FIX_1_BT_RF_10_POS)
#define BT_RF_LDO_PLL_BYPASS_POS       (10U)
#define BT_RF_LDO_PLL_BYPASS_MSK       (0x1UL << BT_RF_LDO_PLL_BYPASS_POS)/*!< PLL LDO bypass mode; 0: off; 1: on*/
#define BT_RF_LDO_PLL_BYPASS           BT_RF_LDO_PLL_BYPASS_MSK
#define BT_RF_LDO_PLL_BYPASS_W(X)      ((X) << BT_RF_LDO_PLL_BYPASS_POS)
#define BT_RF_LDO_PLL_TRIM_POS         (11U)
#define BT_RF_LDO_PLL_TRIM_MSK         (0x3UL << BT_RF_LDO_PLL_TRIM_POS)/*!< PLL LDO trim*/
#define BT_RF_LDO_PLL_TRIM             BT_RF_LDO_PLL_TRIM_MSK
#define BT_RF_LDO_PLL_TRIM_W(X)        ((X) << BT_RF_LDO_PLL_TRIM_POS)
#define BT_RF_LDO_VCO_BYPASS_POS       (13U)
#define BT_RF_LDO_VCO_BYPASS_MSK       (0x1UL << BT_RF_LDO_VCO_BYPASS_POS)/*!< VCO LDO bypass mode; 0: off; 1: on*/
#define BT_RF_LDO_VCO_BYPASS           BT_RF_LDO_VCO_BYPASS_MSK
#define BT_RF_LDO_VCO_BYPASS_W(X)      ((X) << BT_RF_LDO_VCO_BYPASS_POS)
#define BT_RF_LDO_VCO_TRIM_POS         (14U)
#define BT_RF_LDO_VCO_TRIM_MSK         (0x3UL << BT_RF_LDO_VCO_TRIM_POS)/*!< VCO LDO trim*/
#define BT_RF_LDO_VCO_TRIM             BT_RF_LDO_VCO_TRIM_MSK
#define BT_RF_LDO_VCO_TRIM_W(X)        ((X) << BT_RF_LDO_VCO_TRIM_POS)
#define BT_RF_RESV_FIX_0_BT_RF_10_POS  (16U)
#define BT_RF_RESV_FIX_0_BT_RF_10_MSK  (0x1UL << BT_RF_RESV_FIX_0_BT_RF_10_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_10      BT_RF_RESV_FIX_0_BT_RF_10_MSK
#define BT_RF_RESV_FIX_0_BT_RF_10_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_10_POS)
#define BT_RF_PKD_HYS_POS              (17U)
#define BT_RF_PKD_HYS_MSK              (0x3UL << BT_RF_PKD_HYS_POS)/*!< Peak Detector hysteresis margin adjust*/
#define BT_RF_PKD_HYS                  BT_RF_PKD_HYS_MSK
#define BT_RF_PKD_HYS_W(X)             ((X) << BT_RF_PKD_HYS_POS)
#define BT_RF_PKD_REF_POS              (19U)
#define BT_RF_PKD_REF_MSK              (0x7fUL << BT_RF_PKD_REF_POS)/*!< Peak Detector reference level adjust*/
#define BT_RF_PKD_REF                  BT_RF_PKD_REF_MSK
#define BT_RF_PKD_REF_W(X)             ((X) << BT_RF_PKD_REF_POS)
#define BT_RF_PKD_LPF_CAP_POS          (26U)
#define BT_RF_PKD_LPF_CAP_MSK          (0x3UL << BT_RF_PKD_LPF_CAP_POS)/*!< Peak Detector output level filter depth adjust*/
#define BT_RF_PKD_LPF_CAP              BT_RF_PKD_LPF_CAP_MSK
#define BT_RF_PKD_LPF_CAP_W(X)         ((X) << BT_RF_PKD_LPF_CAP_POS)
#define BT_RF_PKD_DAC_IBIT_POS         (28U)
#define BT_RF_PKD_DAC_IBIT_MSK         (0x7UL << BT_RF_PKD_DAC_IBIT_POS)/*!< Reference current adjust for Peak Detector’s embedded DAC*/
#define BT_RF_PKD_DAC_IBIT             BT_RF_PKD_DAC_IBIT_MSK
#define BT_RF_PKD_DAC_IBIT_W(X)        ((X) << BT_RF_PKD_DAC_IBIT_POS)
#define BT_RF_RESV_FIX_BT_RF_10_POS    (31U)
#define BT_RF_RESV_FIX_BT_RF_10_MSK    (0x1UL << BT_RF_RESV_FIX_BT_RF_10_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_10        BT_RF_RESV_FIX_BT_RF_10_MSK
#define BT_RF_RESV_FIX_BT_RF_10_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_10_POS)


//bt_rf_11 offsetaddress : 0x2c
//bt_rf_11 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_11_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_11_MSK  (0x1UL << BT_RF_RESV_FIX_0_BT_RF_11_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_11      BT_RF_RESV_FIX_0_BT_RF_11_MSK
#define BT_RF_RESV_FIX_0_BT_RF_11_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_11_POS)
#define BT_RF_PFD_INVERT_CLK_POS       (1U)
#define BT_RF_PFD_INVERT_CLK_MSK       (0x1UL << BT_RF_PFD_INVERT_CLK_POS)/*!< Reference doubler output clock inverter enable*/
#define BT_RF_PFD_INVERT_CLK           BT_RF_PFD_INVERT_CLK_MSK
#define BT_RF_PFD_INVERT_CLK_W(X)      ((X) << BT_RF_PFD_INVERT_CLK_POS)
#define BT_RF_PFD_DNEN_POS             (2U)
#define BT_RF_PFD_DNEN_MSK             (0x1UL << BT_RF_PFD_DNEN_POS)/*!< PFD dn enable*/
#define BT_RF_PFD_DNEN                 BT_RF_PFD_DNEN_MSK
#define BT_RF_PFD_DNEN_W(X)            ((X) << BT_RF_PFD_DNEN_POS)
#define BT_RF_PFD_UPEN_POS             (3U)
#define BT_RF_PFD_UPEN_MSK             (0x1UL << BT_RF_PFD_UPEN_POS)/*!< PFD up enable*/
#define BT_RF_PFD_UPEN                 BT_RF_PFD_UPEN_MSK
#define BT_RF_PFD_UPEN_W(X)            ((X) << BT_RF_PFD_UPEN_POS)
#define BT_RF_CP_IBLEED_POS            (4U)
#define BT_RF_CP_IBLEED_MSK            (0x7UL << BT_RF_CP_IBLEED_POS)/*!< 1: 0.3uA; 2: 0.6uA; 4: 1.2uA*/
#define BT_RF_CP_IBLEED                BT_RF_CP_IBLEED_MSK
#define BT_RF_CP_IBLEED_W(X)           ((X) << BT_RF_CP_IBLEED_POS)
#define BT_RF_CP_IDN_POS               (7U)
#define BT_RF_CP_IDN_MSK               (0x7UL << BT_RF_CP_IDN_POS)/*!< 1: 4uA; 2: 8uA; 4: 16uA; Max: 28uA*/
#define BT_RF_CP_IDN                   BT_RF_CP_IDN_MSK
#define BT_RF_CP_IDN_W(X)              ((X) << BT_RF_CP_IDN_POS)
#define BT_RF_CP_IUP_POS               (10U)
#define BT_RF_CP_IUP_MSK               (0x7UL << BT_RF_CP_IUP_POS)/*!< 1: 4uA; 2: 8uA; 4: 16uA; Max: 28uA*/
#define BT_RF_CP_IUP                   BT_RF_CP_IUP_MSK
#define BT_RF_CP_IUP_W(X)              ((X) << BT_RF_CP_IUP_POS)
#define BT_RF_RESV_FIX_BT_RF_11_POS    (13U)
#define BT_RF_RESV_FIX_BT_RF_11_MSK    (0x1UL << BT_RF_RESV_FIX_BT_RF_11_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_11        BT_RF_RESV_FIX_BT_RF_11_MSK
#define BT_RF_RESV_FIX_BT_RF_11_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_11_POS)
#define BT_RF_LOOPFIT_R0_POS           (14U)
#define BT_RF_LOOPFIT_R0_MSK           (0x3UL << BT_RF_LOOPFIT_R0_POS)/*!< Loop filter R0 option; 0: 750 Ohm; 1: 500 Ohm; 2: 250 Ohm; 3: 0 Ohm*/
#define BT_RF_LOOPFIT_R0               BT_RF_LOOPFIT_R0_MSK
#define BT_RF_LOOPFIT_R0_W(X)          ((X) << BT_RF_LOOPFIT_R0_POS)
#define BT_RF_RESV_NA_POS              (16U)
#define BT_RF_RESV_NA_MSK              (0xffffUL << BT_RF_RESV_NA_POS)/*!< n/a*/
#define BT_RF_RESV_NA                  BT_RF_RESV_NA_MSK
#define BT_RF_RESV_NA_W(X)             ((X) << BT_RF_RESV_NA_POS)


//bt_rf_12 offsetaddress : 0x30
//bt_rf_12 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_1_BT_RF_12_POS  (0U)
#define BT_RF_RESV_FIX_1_BT_RF_12_MSK  (0x7UL << BT_RF_RESV_FIX_1_BT_RF_12_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1_BT_RF_12      BT_RF_RESV_FIX_1_BT_RF_12_MSK
#define BT_RF_RESV_FIX_1_BT_RF_12_W(X) ((X) << BT_RF_RESV_FIX_1_BT_RF_12_POS)
#define BT_RF_VCO_LOCKDET_EN_POS       (3U)
#define BT_RF_VCO_LOCKDET_EN_MSK       (0x1UL << BT_RF_VCO_LOCKDET_EN_POS)/*!< Lock detector enable*/
#define BT_RF_VCO_LOCKDET_EN           BT_RF_VCO_LOCKDET_EN_MSK
#define BT_RF_VCO_LOCKDET_EN_W(X)      ((X) << BT_RF_VCO_LOCKDET_EN_POS)
#define BT_RF_RESV_FIX_0_BT_RF_12_POS  (4U)
#define BT_RF_RESV_FIX_0_BT_RF_12_MSK  (0xfUL << BT_RF_RESV_FIX_0_BT_RF_12_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_12      BT_RF_RESV_FIX_0_BT_RF_12_MSK
#define BT_RF_RESV_FIX_0_BT_RF_12_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_12_POS)
#define BT_RF_DAC_VCM_POS              (8U)
#define BT_RF_DAC_VCM_MSK              (0x3UL << BT_RF_DAC_VCM_POS)/*!< DAC output common voltage adjust; 0: 64uA * 5K = 320mV; 1: 64uA * 6K = 380mV; 2: 64uA * 7K = 450mV; 3: 64uA * 8K = 510mV*/
#define BT_RF_DAC_VCM                  BT_RF_DAC_VCM_MSK
#define BT_RF_DAC_VCM_W(X)             ((X) << BT_RF_DAC_VCM_POS)
#define BT_RF_RESV_FIX_BT_RF_12_POS    (10U)
#define BT_RF_RESV_FIX_BT_RF_12_MSK    (0xfUL << BT_RF_RESV_FIX_BT_RF_12_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_12        BT_RF_RESV_FIX_BT_RF_12_MSK
#define BT_RF_RESV_FIX_BT_RF_12_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_12_POS)
#define BT_RF_DAC_LPF_POS              (14U)
#define BT_RF_DAC_LPF_MSK              (0x3UL << BT_RF_DAC_LPF_POS)/*!< DAC LPF BW adjust; 0: 0.7M; 1: 1M; 2: 2M; 3: 4M*/
#define BT_RF_DAC_LPF                  BT_RF_DAC_LPF_MSK
#define BT_RF_DAC_LPF_W(X)             ((X) << BT_RF_DAC_LPF_POS)
#define BT_RF_DAC_RLOAD_1M_POS         (16U)
#define BT_RF_DAC_RLOAD_1M_MSK         (0x3fUL << BT_RF_DAC_RLOAD_1M_POS)/*!< TP DAC gain adjustment by tuning the load resistors for BR/LE 1Mbps; 0x3f: 200mV; 0x20: 100mV; 0x10: 50mV*/
#define BT_RF_DAC_RLOAD_1M             BT_RF_DAC_RLOAD_1M_MSK
#define BT_RF_DAC_RLOAD_1M_W(X)        ((X) << BT_RF_DAC_RLOAD_1M_POS)
#define BT_RF_DAC_RLOAD_2M_POS         (22U)
#define BT_RF_DAC_RLOAD_2M_MSK         (0x3fUL << BT_RF_DAC_RLOAD_2M_POS)/*!< TP DAC gain adjustment by tuning the load resistors for LE 2Mbps; 0x3f: 200mV; 0x20: 100mV; 0x10: 50mV*/
#define BT_RF_DAC_RLOAD_2M             BT_RF_DAC_RLOAD_2M_MSK
#define BT_RF_DAC_RLOAD_2M_W(X)        ((X) << BT_RF_DAC_RLOAD_2M_POS)
#define BT_RF_RESV_NA_BT_RF_12_POS     (28U)
#define BT_RF_RESV_NA_BT_RF_12_MSK     (0xfUL << BT_RF_RESV_NA_BT_RF_12_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_12         BT_RF_RESV_NA_BT_RF_12_MSK
#define BT_RF_RESV_NA_BT_RF_12_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_12_POS)


//bt_rf_13 offsetaddress :  0x34
//bt_rf_13 RegResetValue : 0xNone
#define BT_RF_PA_CAP_POS               (0U)
#define BT_RF_PA_CAP_MSK               (0xfUL << BT_RF_PA_CAP_POS)/*!< PA Cap*/
#define BT_RF_PA_CAP                   BT_RF_PA_CAP_MSK
#define BT_RF_PA_CAP_W(X)              ((X) << BT_RF_PA_CAP_POS)
#define BT_RF_LNA_CAP_POS              (4U)
#define BT_RF_LNA_CAP_MSK              (0x7UL << BT_RF_LNA_CAP_POS)/*!< LNA Cap*/
#define BT_RF_LNA_CAP                  BT_RF_LNA_CAP_MSK
#define BT_RF_LNA_CAP_W(X)             ((X) << BT_RF_LNA_CAP_POS)
#define BT_RF_LNA_IBIT_POS             (7U)
#define BT_RF_LNA_IBIT_MSK             (0x3UL << BT_RF_LNA_IBIT_POS)/*!< LNA bias current trim*/
#define BT_RF_LNA_IBIT                 BT_RF_LNA_IBIT_MSK
#define BT_RF_LNA_IBIT_W(X)            ((X) << BT_RF_LNA_IBIT_POS)
#define BT_RF_LNA_FSTART_POS           (9U)
#define BT_RF_LNA_FSTART_MSK           (0x1UL << BT_RF_LNA_FSTART_POS)/*!< LNA ptat current force start*/
#define BT_RF_LNA_FSTART               BT_RF_LNA_FSTART_MSK
#define BT_RF_LNA_FSTART_W(X)          ((X) << BT_RF_LNA_FSTART_POS)
#define BT_RF_RESV_FIX_3_BT_RF_13_POS  (10U)
#define BT_RF_RESV_FIX_3_BT_RF_13_MSK  (0x3UL << BT_RF_RESV_FIX_3_BT_RF_13_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_3_BT_RF_13      BT_RF_RESV_FIX_3_BT_RF_13_MSK
#define BT_RF_RESV_FIX_3_BT_RF_13_W(X) ((X) << BT_RF_RESV_FIX_3_BT_RF_13_POS)
#define BT_RF_CBPF_BW_POS              (12U)
#define BT_RF_CBPF_BW_MSK              (0x3UL << BT_RF_CBPF_BW_POS)/*!< Rx CBPF bandwidth select; 0: 1M; 1: 0.85M; 2: 0.75M; 3: 0.65M*/
#define BT_RF_CBPF_BW                  BT_RF_CBPF_BW_MSK
#define BT_RF_CBPF_BW_W(X)             ((X) << BT_RF_CBPF_BW_POS)
#define BT_RF_RESV_FIX_2_BT_RF_13_POS  (14U)
#define BT_RF_RESV_FIX_2_BT_RF_13_MSK  (0x3UL << BT_RF_RESV_FIX_2_BT_RF_13_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_2_BT_RF_13      BT_RF_RESV_FIX_2_BT_RF_13_MSK
#define BT_RF_RESV_FIX_2_BT_RF_13_W(X) ((X) << BT_RF_RESV_FIX_2_BT_RF_13_POS)
#define BT_RF_CBPF_IBIT_POS            (16U)
#define BT_RF_CBPF_IBIT_MSK            (0x7UL << BT_RF_CBPF_IBIT_POS)/*!< Rx CBPF current bias select*/
#define BT_RF_CBPF_IBIT                BT_RF_CBPF_IBIT_MSK
#define BT_RF_CBPF_IBIT_W(X)           ((X) << BT_RF_CBPF_IBIT_POS)
#define BT_RF_RESV_FIX_1_BT_RF_13_POS  (19U)
#define BT_RF_RESV_FIX_1_BT_RF_13_MSK  (0x3UL << BT_RF_RESV_FIX_1_BT_RF_13_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1_BT_RF_13      BT_RF_RESV_FIX_1_BT_RF_13_MSK
#define BT_RF_RESV_FIX_1_BT_RF_13_W(X) ((X) << BT_RF_RESV_FIX_1_BT_RF_13_POS)
#define BT_RF_ADC_IBIT_POS             (21U)
#define BT_RF_ADC_IBIT_MSK             (0x7UL << BT_RF_ADC_IBIT_POS)/*!< Rx ADC bias current select*/
#define BT_RF_ADC_IBIT                 BT_RF_ADC_IBIT_MSK
#define BT_RF_ADC_IBIT_W(X)            ((X) << BT_RF_ADC_IBIT_POS)
#define BT_RF_ADC_REF_TRIM_POS         (24U)
#define BT_RF_ADC_REF_TRIM_MSK         (0x7UL << BT_RF_ADC_REF_TRIM_POS)/*!< Vref voltage select for Rx ADC LDO output*/
#define BT_RF_ADC_REF_TRIM             BT_RF_ADC_REF_TRIM_MSK
#define BT_RF_ADC_REF_TRIM_W(X)        ((X) << BT_RF_ADC_REF_TRIM_POS)
#define BT_RF_RESV_FIX_0_BT_RF_13_POS  (27U)
#define BT_RF_RESV_FIX_0_BT_RF_13_MSK  (0x1UL << BT_RF_RESV_FIX_0_BT_RF_13_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_13      BT_RF_RESV_FIX_0_BT_RF_13_MSK
#define BT_RF_RESV_FIX_0_BT_RF_13_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_13_POS)
#define BT_RF_ADC_FORMAT_SEL_POS       (28U)
#define BT_RF_ADC_FORMAT_SEL_MSK       (0x1UL << BT_RF_ADC_FORMAT_SEL_POS)/*!< Rx ADC output format selection; 0: signed; 1: unsigned*/
#define BT_RF_ADC_FORMAT_SEL           BT_RF_ADC_FORMAT_SEL_MSK
#define BT_RF_ADC_FORMAT_SEL_W(X)      ((X) << BT_RF_ADC_FORMAT_SEL_POS)
#define BT_RF_ADC_DELAY_SEL_POS        (29U)
#define BT_RF_ADC_DELAY_SEL_MSK        (0x1UL << BT_RF_ADC_DELAY_SEL_POS)/*!< Rx ADC delay time selection of comparator*/
#define BT_RF_ADC_DELAY_SEL            BT_RF_ADC_DELAY_SEL_MSK
#define BT_RF_ADC_DELAY_SEL_W(X)       ((X) << BT_RF_ADC_DELAY_SEL_POS)
#define BT_RF_RESV_FIX_BT_RF_13_POS    (30U)
#define BT_RF_RESV_FIX_BT_RF_13_MSK    (0x3UL << BT_RF_RESV_FIX_BT_RF_13_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_13        BT_RF_RESV_FIX_BT_RF_13_MSK
#define BT_RF_RESV_FIX_BT_RF_13_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_13_POS)


//bt_rf_14 offsetaddress : 0x38
//bt_rf_14 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_2_BT_RF_14_POS  (0U)
#define BT_RF_RESV_FIX_2_BT_RF_14_MSK  (0x1UL << BT_RF_RESV_FIX_2_BT_RF_14_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_2_BT_RF_14      BT_RF_RESV_FIX_2_BT_RF_14_MSK
#define BT_RF_RESV_FIX_2_BT_RF_14_W(X) ((X) << BT_RF_RESV_FIX_2_BT_RF_14_POS)
#define BT_RF_PA_VBC_TRIM_POS          (1U)
#define BT_RF_PA_VBC_TRIM_MSK          (0x3UL << BT_RF_PA_VBC_TRIM_POS)/*!< PA cascade bias voltage trim*/
#define BT_RF_PA_VBC_TRIM              BT_RF_PA_VBC_TRIM_MSK
#define BT_RF_PA_VBC_TRIM_W(X)         ((X) << BT_RF_PA_VBC_TRIM_POS)
#define BT_RF_PA_VBCLOW_TRIM_POS       (3U)
#define BT_RF_PA_VBCLOW_TRIM_MSK       (0x3UL << BT_RF_PA_VBCLOW_TRIM_POS)/*!< PA cascade bias low voltage trim*/
#define BT_RF_PA_VBCLOW_TRIM           BT_RF_PA_VBCLOW_TRIM_MSK
#define BT_RF_PA_VBCLOW_TRIM_W(X)      ((X) << BT_RF_PA_VBCLOW_TRIM_POS)
#define BT_RF_PA_FSTART_POS            (5U)
#define BT_RF_PA_FSTART_MSK            (0x1UL << BT_RF_PA_FSTART_POS)/*!< PA  force startup option; 0：default startup; 1：force startup*/
#define BT_RF_PA_FSTART                BT_RF_PA_FSTART_MSK
#define BT_RF_PA_FSTART_W(X)           ((X) << BT_RF_PA_FSTART_POS)
#define BT_RF_PA_IBIT_POS              (6U)
#define BT_RF_PA_IBIT_MSK              (0x3UL << BT_RF_PA_IBIT_POS)/*!< PA bias current trim*/
#define BT_RF_PA_IBIT                  BT_RF_PA_IBIT_MSK
#define BT_RF_PA_IBIT_W(X)             ((X) << BT_RF_PA_IBIT_POS)
#define BT_RF_TXLPF_IBIT_POS           (8U)
#define BT_RF_TXLPF_IBIT_MSK           (0x3UL << BT_RF_TXLPF_IBIT_POS)/*!< Txlpf bias current trim*/
#define BT_RF_TXLPF_IBIT               BT_RF_TXLPF_IBIT_MSK
#define BT_RF_TXLPF_IBIT_W(X)          ((X) << BT_RF_TXLPF_IBIT_POS)
#define BT_RF_RESV_FIX_1_BT_RF_14_POS  (10U)
#define BT_RF_RESV_FIX_1_BT_RF_14_MSK  (0x3UL << BT_RF_RESV_FIX_1_BT_RF_14_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1_BT_RF_14      BT_RF_RESV_FIX_1_BT_RF_14_MSK
#define BT_RF_RESV_FIX_1_BT_RF_14_W(X) ((X) << BT_RF_RESV_FIX_1_BT_RF_14_POS)
#define BT_RF_TXDAC_IBIT_POS           (12U)
#define BT_RF_TXDAC_IBIT_MSK           (0x3UL << BT_RF_TXDAC_IBIT_POS)/*!< Txdac bias current trim*/
#define BT_RF_TXDAC_IBIT               BT_RF_TXDAC_IBIT_MSK
#define BT_RF_TXDAC_IBIT_W(X)          ((X) << BT_RF_TXDAC_IBIT_POS)
#define BT_RF_TXDAC_GAIN_POS           (14U)
#define BT_RF_TXDAC_GAIN_MSK           (0x3UL << BT_RF_TXDAC_GAIN_POS)/*!< Txdac gain trim*/
#define BT_RF_TXDAC_GAIN               BT_RF_TXDAC_GAIN_MSK
#define BT_RF_TXDAC_GAIN_W(X)          ((X) << BT_RF_TXDAC_GAIN_POS)
#define BT_RF_TXDAC_INVERT_CLK_POS     (16U)
#define BT_RF_TXDAC_INVERT_CLK_MSK     (0x1UL << BT_RF_TXDAC_INVERT_CLK_POS)/*!< Tx IQ DAC clock select; 0: xtal clock; 1: xtal clock inverted*/
#define BT_RF_TXDAC_INVERT_CLK         BT_RF_TXDAC_INVERT_CLK_MSK
#define BT_RF_TXDAC_INVERT_CLK_W(X)    ((X) << BT_RF_TXDAC_INVERT_CLK_POS)
#define BT_RF_RESV_FIX_0_BT_RF_14_POS  (17U)
#define BT_RF_RESV_FIX_0_BT_RF_14_MSK  (0x1UL << BT_RF_RESV_FIX_0_BT_RF_14_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_14      BT_RF_RESV_FIX_0_BT_RF_14_MSK
#define BT_RF_RESV_FIX_0_BT_RF_14_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_14_POS)
#define BT_RF_RESV_FIX_BT_RF_14_POS    (18U)
#define BT_RF_RESV_FIX_BT_RF_14_MSK    (0x7fUL << BT_RF_RESV_FIX_BT_RF_14_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_14        BT_RF_RESV_FIX_BT_RF_14_MSK
#define BT_RF_RESV_FIX_BT_RF_14_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_14_POS)
#define BT_RF_PA_VBA_TRIM_POS          (25U)
#define BT_RF_PA_VBA_TRIM_MSK          (0x3UL << BT_RF_PA_VBA_TRIM_POS)/*!< PA bias voltage trim2*/
#define BT_RF_PA_VBA_TRIM              BT_RF_PA_VBA_TRIM_MSK
#define BT_RF_PA_VBA_TRIM_W(X)         ((X) << BT_RF_PA_VBA_TRIM_POS)
#define BT_RF_PA_VBB_TRIM_POS          (27U)
#define BT_RF_PA_VBB_TRIM_MSK          (0x3UL << BT_RF_PA_VBB_TRIM_POS)/*!< PA bias voltage trim1*/
#define BT_RF_PA_VBB_TRIM              BT_RF_PA_VBB_TRIM_MSK
#define BT_RF_PA_VBB_TRIM_W(X)         ((X) << BT_RF_PA_VBB_TRIM_POS)
#define BT_RF_RESV_NA_BT_RF_14_POS     (29U)
#define BT_RF_RESV_NA_BT_RF_14_MSK     (0x7UL << BT_RF_RESV_NA_BT_RF_14_POS)/*!< */
#define BT_RF_RESV_NA_BT_RF_14         BT_RF_RESV_NA_BT_RF_14_MSK
#define BT_RF_RESV_NA_BT_RF_14_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_14_POS)


//bt_rf_15 offsetaddress : 0x3c
//bt_rf_15 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_15_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_15_MSK    (0xfffffUL << BT_RF_RESV_FIX_BT_RF_15_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_15        BT_RF_RESV_FIX_BT_RF_15_MSK
#define BT_RF_RESV_FIX_BT_RF_15_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_15_POS)
#define BT_RF_RO_TXDCOC_I_CODE_POS     (20U)
#define BT_RF_RO_TXDCOC_I_CODE_MSK     (0x3fUL << BT_RF_RO_TXDCOC_I_CODE_POS)/*!< TXDCOC calibration I-path code result*/
#define BT_RF_RO_TXDCOC_I_CODE         BT_RF_RO_TXDCOC_I_CODE_MSK
#define BT_RF_RO_TXDCOC_I_CODE_W(X)    ((X) << BT_RF_RO_TXDCOC_I_CODE_POS)
#define BT_RF_RO_TXDCOC_Q_CODE_POS     (26U)
#define BT_RF_RO_TXDCOC_Q_CODE_MSK     (0x3fUL << BT_RF_RO_TXDCOC_Q_CODE_POS)/*!< TXDCOC calibration Q-path code result*/
#define BT_RF_RO_TXDCOC_Q_CODE         BT_RF_RO_TXDCOC_Q_CODE_MSK
#define BT_RF_RO_TXDCOC_Q_CODE_W(X)    ((X) << BT_RF_RO_TXDCOC_Q_CODE_POS)


//bt_rf_16 offsetaddress : 0x40
//bt_rf_16 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_16_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_16_MSK    (0x3ffffffUL << BT_RF_RESV_FIX_BT_RF_16_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_16        BT_RF_RESV_FIX_BT_RF_16_MSK
#define BT_RF_RESV_FIX_BT_RF_16_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_16_POS)
#define BT_RF_RO_RCCAL_CODE_POS        (26U)
#define BT_RF_RO_RCCAL_CODE_MSK        (0x1fUL << BT_RF_RO_RCCAL_CODE_POS)/*!< RC calibration code result*/
#define BT_RF_RO_RCCAL_CODE            BT_RF_RO_RCCAL_CODE_MSK
#define BT_RF_RO_RCCAL_CODE_W(X)       ((X) << BT_RF_RO_RCCAL_CODE_POS)
#define BT_RF_RESV_NA_BT_RF_16_POS     (31U)
#define BT_RF_RESV_NA_BT_RF_16_MSK     (0x1UL << BT_RF_RESV_NA_BT_RF_16_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_16         BT_RF_RESV_NA_BT_RF_16_MSK
#define BT_RF_RESV_NA_BT_RF_16_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_16_POS)


//bt_rf_17 offsetaddress : 0x44
//bt_rf_17 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_17_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_17_MSK    (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_17_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_17        BT_RF_RESV_FIX_BT_RF_17_MSK
#define BT_RF_RESV_FIX_BT_RF_17_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_17_POS)


//bt_rf_18 offsetaddress : 0x48
//bt_rf_18 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_18_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_18_MSK    (0xffffffUL << BT_RF_RESV_FIX_BT_RF_18_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_18        BT_RF_RESV_FIX_BT_RF_18_MSK
#define BT_RF_RESV_FIX_BT_RF_18_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_18_POS)
#define BT_RF_RESV_NA_BT_RF_18_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_18_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_18_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_18         BT_RF_RESV_NA_BT_RF_18_MSK
#define BT_RF_RESV_NA_BT_RF_18_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_18_POS)


//bt_rf_19 offsetaddress : 0x4c
//bt_rf_19 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_19_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_19_MSK    (0xfffffffUL << BT_RF_RESV_FIX_BT_RF_19_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_19        BT_RF_RESV_FIX_BT_RF_19_MSK
#define BT_RF_RESV_FIX_BT_RF_19_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_19_POS)
#define BT_RF_RESV_NA_BT_RF_19_POS     (28U)
#define BT_RF_RESV_NA_BT_RF_19_MSK     (0xfUL << BT_RF_RESV_NA_BT_RF_19_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_19         BT_RF_RESV_NA_BT_RF_19_MSK
#define BT_RF_RESV_NA_BT_RF_19_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_19_POS)


//bt_rf_20 offsetaddress : 0x50
//bt_rf_20 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_20_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_20_MSK    (0xfffffffUL << BT_RF_RESV_FIX_BT_RF_20_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_20        BT_RF_RESV_FIX_BT_RF_20_MSK
#define BT_RF_RESV_FIX_BT_RF_20_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_20_POS)
#define BT_RF_RESV_NA_BT_RF_20_POS     (28U)
#define BT_RF_RESV_NA_BT_RF_20_MSK     (0xfUL << BT_RF_RESV_NA_BT_RF_20_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_20         BT_RF_RESV_NA_BT_RF_20_MSK
#define BT_RF_RESV_NA_BT_RF_20_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_20_POS)


//bt_rf_21 offsetaddress : 0x54
//bt_rf_21 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_21_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_21_MSK    (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_21_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_21        BT_RF_RESV_FIX_BT_RF_21_MSK
#define BT_RF_RESV_FIX_BT_RF_21_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_21_POS)


//bt_rf_22 offsetaddress : 0x58
//bt_rf_22 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_22_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_22_MSK    (0x7ffffffUL << BT_RF_RESV_FIX_BT_RF_22_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_22        BT_RF_RESV_FIX_BT_RF_22_MSK
#define BT_RF_RESV_FIX_BT_RF_22_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_22_POS)
#define BT_RF_RESV_NA_BT_RF_22_POS     (27U)
#define BT_RF_RESV_NA_BT_RF_22_MSK     (0x1fUL << BT_RF_RESV_NA_BT_RF_22_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_22         BT_RF_RESV_NA_BT_RF_22_MSK
#define BT_RF_RESV_NA_BT_RF_22_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_22_POS)


//bt_rf_23 offsetaddress : 0x5c
//bt_rf_23 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_23_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_23_MSK    (0x7ffffffUL << BT_RF_RESV_FIX_BT_RF_23_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_23        BT_RF_RESV_FIX_BT_RF_23_MSK
#define BT_RF_RESV_FIX_BT_RF_23_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_23_POS)
#define BT_RF_RESV_NA_BT_RF_23_POS     (27U)
#define BT_RF_RESV_NA_BT_RF_23_MSK     (0x1fUL << BT_RF_RESV_NA_BT_RF_23_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_23         BT_RF_RESV_NA_BT_RF_23_MSK
#define BT_RF_RESV_NA_BT_RF_23_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_23_POS)


//bt_rf_24 offsetaddress : 0x60
//bt_rf_24 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_24_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_24_MSK    (0xffffffUL << BT_RF_RESV_FIX_BT_RF_24_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_24        BT_RF_RESV_FIX_BT_RF_24_MSK
#define BT_RF_RESV_FIX_BT_RF_24_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_24_POS)
#define BT_RF_RESV_NA_BT_RF_24_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_24_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_24_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_24         BT_RF_RESV_NA_BT_RF_24_MSK
#define BT_RF_RESV_NA_BT_RF_24_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_24_POS)


//bt_rf_25 offsetaddress : 0x64
//bt_rf_25 RegResetValue : 0xNone
#define BT_RF_FREQ_SW_POS              (0U)
#define BT_RF_FREQ_SW_MSK              (0xfffUL << BT_RF_FREQ_SW_POS)/*!< RF frequency sw value (unit: MHz)*/
#define BT_RF_FREQ_SW                  BT_RF_FREQ_SW_MSK
#define BT_RF_FREQ_SW_W(X)             ((X) << BT_RF_FREQ_SW_POS)
#define BT_RF_FREQ_SRC_POS             (12U)
#define BT_RF_FREQ_SRC_MSK             (0x1UL << BT_RF_FREQ_SRC_POS)/*!< RF frequency source; 0: hw; 1: sw*/
#define BT_RF_FREQ_SRC                 BT_RF_FREQ_SRC_MSK
#define BT_RF_FREQ_SRC_W(X)            ((X) << BT_RF_FREQ_SRC_POS)
#define BT_RF_INT_SW_POS               (13U)
#define BT_RF_INT_SW_MSK               (0xffUL << BT_RF_INT_SW_POS)/*!< PLL divider integer part sw value*/
#define BT_RF_INT_SW                   BT_RF_INT_SW_MSK
#define BT_RF_INT_SW_W(X)              ((X) << BT_RF_INT_SW_POS)
#define BT_RF_INT_SRC_POS              (21U)
#define BT_RF_INT_SRC_MSK              (0x1UL << BT_RF_INT_SRC_POS)/*!< PLL divider integer part source; 0: hw; 1: sw*/
#define BT_RF_INT_SRC                  BT_RF_INT_SRC_MSK
#define BT_RF_INT_SRC_W(X)             ((X) << BT_RF_INT_SRC_POS)
#define BT_RF_INT_SEL_POS              (22U)
#define BT_RF_INT_SEL_MSK              (0x1UL << BT_RF_INT_SEL_POS)/*!< PLL divider integer part select; 0: latched value; 1: pass through value*/
#define BT_RF_INT_SEL                  BT_RF_INT_SEL_MSK
#define BT_RF_INT_SEL_W(X)             ((X) << BT_RF_INT_SEL_POS)
#define BT_RF_RESV_NA_BT_RF_25_POS     (23U)
#define BT_RF_RESV_NA_BT_RF_25_MSK     (0x1ffUL << BT_RF_RESV_NA_BT_RF_25_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_25         BT_RF_RESV_NA_BT_RF_25_MSK
#define BT_RF_RESV_NA_BT_RF_25_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_25_POS)


//bt_rf_26 offsetaddress : 0x68
//bt_rf_26 RegResetValue : 0xNone
#define BT_RF_FRAC_SW_POS              (0U)
#define BT_RF_FRAC_SW_MSK              (0xffffffUL << BT_RF_FRAC_SW_POS)/*!< PLL divider fractional part sw value*/
#define BT_RF_FRAC_SW                  BT_RF_FRAC_SW_MSK
#define BT_RF_FRAC_SW_W(X)             ((X) << BT_RF_FRAC_SW_POS)
#define BT_RF_FRAC_SRC_POS             (24U)
#define BT_RF_FRAC_SRC_MSK             (0x1UL << BT_RF_FRAC_SRC_POS)/*!< PLL divider fractional part source; 0: hw; 1: sw*/
#define BT_RF_FRAC_SRC                 BT_RF_FRAC_SRC_MSK
#define BT_RF_FRAC_SRC_W(X)            ((X) << BT_RF_FRAC_SRC_POS)
#define BT_RF_FRAC_SEL_POS             (25U)
#define BT_RF_FRAC_SEL_MSK             (0x1UL << BT_RF_FRAC_SEL_POS)/*!< PLL divider fractional part select; 0: latched value; 1: pass through value*/
#define BT_RF_FRAC_SEL                 BT_RF_FRAC_SEL_MSK
#define BT_RF_FRAC_SEL_W(X)            ((X) << BT_RF_FRAC_SEL_POS)
#define BT_RF_RESV_NA_BT_RF_26_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_26_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_26_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_26         BT_RF_RESV_NA_BT_RF_26_MSK
#define BT_RF_RESV_NA_BT_RF_26_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_26_POS)


//bt_rf_27 offsetaddress : 0x6c
//bt_rf_27 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_27_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_27_MSK    (0x3ffffUL << BT_RF_RESV_FIX_BT_RF_27_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_27        BT_RF_RESV_FIX_BT_RF_27_MSK
#define BT_RF_RESV_FIX_BT_RF_27_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_27_POS)
#define BT_RF_RO_VCO_CAP_POS           (18U)
#define BT_RF_RO_VCO_CAP_MSK           (0x7fUL << BT_RF_RO_VCO_CAP_POS)/*!< VCO calibration cap value for read in auto mode*/
#define BT_RF_RO_VCO_CAP               BT_RF_RO_VCO_CAP_MSK
#define BT_RF_RO_VCO_CAP_W(X)          ((X) << BT_RF_RO_VCO_CAP_POS)
#define BT_RF_RO_SYN_LOCKDET_POS       (25U)
#define BT_RF_RO_SYN_LOCKDET_MSK       (0x1UL << BT_RF_RO_SYN_LOCKDET_POS)/*!< PLL lock detection indicator*/
#define BT_RF_RO_SYN_LOCKDET           BT_RF_RO_SYN_LOCKDET_MSK
#define BT_RF_RO_SYN_LOCKDET_W(X)      ((X) << BT_RF_RO_SYN_LOCKDET_POS)
#define BT_RF_RESV_NA_BT_RF_27_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_27_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_27_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_27         BT_RF_RESV_NA_BT_RF_27_MSK
#define BT_RF_RESV_NA_BT_RF_27_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_27_POS)


//bt_rf_28 offsetaddress : 0x70
//bt_rf_28 RegResetValue : 0xNone
#define BT_RF_RX_1M_IF_VAL_POS         (0U)
#define BT_RF_RX_1M_IF_VAL_MSK         (0x7fffffUL << BT_RF_RX_1M_IF_VAL_POS)/*!< */
#define BT_RF_RX_1M_IF_VAL             BT_RF_RX_1M_IF_VAL_MSK
#define BT_RF_RX_1M_IF_VAL_W(X)        ((X) << BT_RF_RX_1M_IF_VAL_POS)
#define BT_RF_RX_1M_IF_X2_POS          (23U)
#define BT_RF_RX_1M_IF_X2_MSK          (0xfUL << BT_RF_RX_1M_IF_X2_POS)/*!< */
#define BT_RF_RX_1M_IF_X2              BT_RF_RX_1M_IF_X2_MSK
#define BT_RF_RX_1M_IF_X2_W(X)         ((X) << BT_RF_RX_1M_IF_X2_POS)
#define BT_RF_RESV_NA_BT_RF_28_POS     (23U)
#define BT_RF_RESV_NA_BT_RF_28_MSK     (0x1ffUL << BT_RF_RESV_NA_BT_RF_28_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_28         BT_RF_RESV_NA_BT_RF_28_MSK
#define BT_RF_RESV_NA_BT_RF_28_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_28_POS)


//bt_rf_29 offsetaddress : 0x74
//bt_rf_29 RegResetValue : 0xNone
#define BT_RF_RX_2M_IF_VAL_POS         (0U)
#define BT_RF_RX_2M_IF_VAL_MSK         (0x7fffffUL << BT_RF_RX_2M_IF_VAL_POS)/*!< */
#define BT_RF_RX_2M_IF_VAL             BT_RF_RX_2M_IF_VAL_MSK
#define BT_RF_RX_2M_IF_VAL_W(X)        ((X) << BT_RF_RX_2M_IF_VAL_POS)
#define BT_RF_RX_2M_IF_X2_POS          (23U)
#define BT_RF_RX_2M_IF_X2_MSK          (0xfUL << BT_RF_RX_2M_IF_X2_POS)/*!< */
#define BT_RF_RX_2M_IF_X2              BT_RF_RX_2M_IF_X2_MSK
#define BT_RF_RX_2M_IF_X2_W(X)         ((X) << BT_RF_RX_2M_IF_X2_POS)
#define BT_RF_RESV_NA_BT_RF_29_POS     (27U)
#define BT_RF_RESV_NA_BT_RF_29_MSK     (0x1fUL << BT_RF_RESV_NA_BT_RF_29_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_29         BT_RF_RESV_NA_BT_RF_29_MSK
#define BT_RF_RESV_NA_BT_RF_29_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_29_POS)


//bt_rf_30 offsetaddress : 0x78
//bt_rf_30 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_30_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_30_MSK  (0x7ffffUL << BT_RF_RESV_FIX_0_BT_RF_30_POS)/*!< */
#define BT_RF_RESV_FIX_0_BT_RF_30      BT_RF_RESV_FIX_0_BT_RF_30_MSK
#define BT_RF_RESV_FIX_0_BT_RF_30_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_30_POS)
#define BT_RF_VCO_CAP_SRC_POS          (19U)
#define BT_RF_VCO_CAP_SRC_MSK          (0x1UL << BT_RF_VCO_CAP_SRC_POS)/*!< */
#define BT_RF_VCO_CAP_SRC              BT_RF_VCO_CAP_SRC_MSK
#define BT_RF_VCO_CAP_SRC_W(X)         ((X) << BT_RF_VCO_CAP_SRC_POS)
#define BT_RF_VCO_CAP_SW_POS           (20U)
#define BT_RF_VCO_CAP_SW_MSK           (0x7fUL << BT_RF_VCO_CAP_SW_POS)/*!< */
#define BT_RF_VCO_CAP_SW               BT_RF_VCO_CAP_SW_MSK
#define BT_RF_VCO_CAP_SW_W(X)          ((X) << BT_RF_VCO_CAP_SW_POS)
#define BT_RF_RESV_FIX_BT_RF_30_POS    (27U)
#define BT_RF_RESV_FIX_BT_RF_30_MSK    (0x1fUL << BT_RF_RESV_FIX_BT_RF_30_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_30        BT_RF_RESV_FIX_BT_RF_30_MSK
#define BT_RF_RESV_FIX_BT_RF_30_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_30_POS)


//bt_rf_31 offsetaddress : 0x7c
//bt_rf_31 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_31_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_31_MSK    (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_31_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_31        BT_RF_RESV_FIX_BT_RF_31_MSK
#define BT_RF_RESV_FIX_BT_RF_31_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_31_POS)


//bt_rf_32 offsetaddress : 0x80
//bt_rf_32 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_1_BT_RF_32_POS  (0U)
#define BT_RF_RESV_FIX_1_BT_RF_32_MSK  (0x3ffffUL << BT_RF_RESV_FIX_1_BT_RF_32_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_1_BT_RF_32      BT_RF_RESV_FIX_1_BT_RF_32_MSK
#define BT_RF_RESV_FIX_1_BT_RF_32_W(X) ((X) << BT_RF_RESV_FIX_1_BT_RF_32_POS)
#define BT_RF_TPCAL_GAIN_CODE_SRC_POS  (18U)
#define BT_RF_TPCAL_GAIN_CODE_SRC_MSK  (0x1UL << BT_RF_TPCAL_GAIN_CODE_SRC_POS)/*!< TP calibration gain code source; 0: hw; 1: sw*/
#define BT_RF_TPCAL_GAIN_CODE_SRC      BT_RF_TPCAL_GAIN_CODE_SRC_MSK
#define BT_RF_TPCAL_GAIN_CODE_SRC_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_SRC_POS)
#define BT_RF_RESV_NA_0_POS            (19U)
#define BT_RF_RESV_NA_0_MSK            (0x7ffUL << BT_RF_RESV_NA_0_POS)/*!< n/a*/
#define BT_RF_RESV_NA_0                BT_RF_RESV_NA_0_MSK
#define BT_RF_RESV_NA_0_W(X)           ((X) << BT_RF_RESV_NA_0_POS)
#define BT_RF_RESV_FIX_BT_RF_32_POS    (30U)
#define BT_RF_RESV_FIX_BT_RF_32_MSK    (0x1UL << BT_RF_RESV_FIX_BT_RF_32_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_32        BT_RF_RESV_FIX_BT_RF_32_MSK
#define BT_RF_RESV_FIX_BT_RF_32_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_32_POS)
#define BT_RF_RESV_NA_BT_RF_32_POS     (31U)
#define BT_RF_RESV_NA_BT_RF_32_MSK     (0x1UL << BT_RF_RESV_NA_BT_RF_32_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_32         BT_RF_RESV_NA_BT_RF_32_MSK
#define BT_RF_RESV_NA_BT_RF_32_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_32_POS)


//bt_rf_33 offsetaddress : 0x84
//bt_rf_33 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_33_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_33_MSK    (0x7ffffffUL << BT_RF_RESV_FIX_BT_RF_33_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_33        BT_RF_RESV_FIX_BT_RF_33_MSK
#define BT_RF_RESV_FIX_BT_RF_33_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_33_POS)
#define BT_RF_RESV_NA_BT_RF_33_POS     (27U)
#define BT_RF_RESV_NA_BT_RF_33_MSK     (0x1fUL << BT_RF_RESV_NA_BT_RF_33_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_33         BT_RF_RESV_NA_BT_RF_33_MSK
#define BT_RF_RESV_NA_BT_RF_33_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_33_POS)


//bt_rf_34 offsetaddress : 0x88
//bt_rf_34 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_34_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_34_MSK    (0x3fffffffUL << BT_RF_RESV_FIX_BT_RF_34_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_34        BT_RF_RESV_FIX_BT_RF_34_MSK
#define BT_RF_RESV_FIX_BT_RF_34_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_34_POS)
#define BT_RF_RESV_NA_BT_RF_34_POS     (30U)
#define BT_RF_RESV_NA_BT_RF_34_MSK     (0x3UL << BT_RF_RESV_NA_BT_RF_34_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_34         BT_RF_RESV_NA_BT_RF_34_MSK
#define BT_RF_RESV_NA_BT_RF_34_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_34_POS)


//bt_rf_35 offsetaddress : 0x8c
//bt_rf_35 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_35_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_35_MSK  (0x3fUL << BT_RF_RESV_FIX_0_BT_RF_35_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_35      BT_RF_RESV_FIX_0_BT_RF_35_MSK
#define BT_RF_RESV_FIX_0_BT_RF_35_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_35_POS)
#define BT_RF_RAMP_TGT_SRC_POS         (6U)
#define BT_RF_RAMP_TGT_SRC_MSK         (0x1UL << BT_RF_RAMP_TGT_SRC_POS)/*!< PA target power source; 0: hw; 1: sw*/
#define BT_RF_RAMP_TGT_SRC             BT_RF_RAMP_TGT_SRC_MSK
#define BT_RF_RAMP_TGT_SRC_W(X)        ((X) << BT_RF_RAMP_TGT_SRC_POS)
#define BT_RF_RAMP_TGT_SW_POS          (7U)
#define BT_RF_RAMP_TGT_SW_MSK          (0x3fUL << BT_RF_RAMP_TGT_SW_POS)/*!< PA target power sw value*/
#define BT_RF_RAMP_TGT_SW              BT_RF_RAMP_TGT_SW_MSK
#define BT_RF_RAMP_TGT_SW_W(X)         ((X) << BT_RF_RAMP_TGT_SW_POS)
#define BT_RF_RESV_FIX_BT_RF_35_POS    (13U)
#define BT_RF_RESV_FIX_BT_RF_35_MSK    (0x7ffffUL << BT_RF_RESV_FIX_BT_RF_35_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_35        BT_RF_RESV_FIX_BT_RF_35_MSK
#define BT_RF_RESV_FIX_BT_RF_35_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_35_POS)


//bt_rf_36 offsetaddress : 0x90
//bt_rf_36 RegResetValue : 0xNone
#define BT_RF_TX_RAMP_TGT_4_POS        (0U)
#define BT_RF_TX_RAMP_TGT_4_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_4_POS)/*!< Tx PA ramp target for power index 4*/
#define BT_RF_TX_RAMP_TGT_4            BT_RF_TX_RAMP_TGT_4_MSK
#define BT_RF_TX_RAMP_TGT_4_W(X)       ((X) << BT_RF_TX_RAMP_TGT_4_POS)
#define BT_RF_TX_RAMP_TGT_5_POS        (6U)
#define BT_RF_TX_RAMP_TGT_5_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_5_POS)/*!< Tx PA ramp target for power index 5*/
#define BT_RF_TX_RAMP_TGT_5            BT_RF_TX_RAMP_TGT_5_MSK
#define BT_RF_TX_RAMP_TGT_5_W(X)       ((X) << BT_RF_TX_RAMP_TGT_5_POS)
#define BT_RF_TX_RAMP_TGT_6_POS        (12U)
#define BT_RF_TX_RAMP_TGT_6_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_6_POS)/*!< Tx PA ramp target for power index 6*/
#define BT_RF_TX_RAMP_TGT_6            BT_RF_TX_RAMP_TGT_6_MSK
#define BT_RF_TX_RAMP_TGT_6_W(X)       ((X) << BT_RF_TX_RAMP_TGT_6_POS)
#define BT_RF_TX_RAMP_TGT_7_POS        (18U)
#define BT_RF_TX_RAMP_TGT_7_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_7_POS)/*!< Tx PA ramp target for power index 7*/
#define BT_RF_TX_RAMP_TGT_7            BT_RF_TX_RAMP_TGT_7_MSK
#define BT_RF_TX_RAMP_TGT_7_W(X)       ((X) << BT_RF_TX_RAMP_TGT_7_POS)
#define BT_RF_RESV_NA_BT_RF_36_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_36_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_36_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_36         BT_RF_RESV_NA_BT_RF_36_MSK
#define BT_RF_RESV_NA_BT_RF_36_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_36_POS)


//bt_rf_37 offsetaddress : 0x94
//bt_rf_37 RegResetValue : 0xNone
#define BT_RF_TX_RAMP_TGT_0_POS        (0U)
#define BT_RF_TX_RAMP_TGT_0_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_0_POS)/*!< Tx PA ramp target for power index 0*/
#define BT_RF_TX_RAMP_TGT_0            BT_RF_TX_RAMP_TGT_0_MSK
#define BT_RF_TX_RAMP_TGT_0_W(X)       ((X) << BT_RF_TX_RAMP_TGT_0_POS)
#define BT_RF_TX_RAMP_TGT_1_POS        (6U)
#define BT_RF_TX_RAMP_TGT_1_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_1_POS)/*!< Tx PA ramp target for power index 1*/
#define BT_RF_TX_RAMP_TGT_1            BT_RF_TX_RAMP_TGT_1_MSK
#define BT_RF_TX_RAMP_TGT_1_W(X)       ((X) << BT_RF_TX_RAMP_TGT_1_POS)
#define BT_RF_TX_RAMP_TGT_2_POS        (12U)
#define BT_RF_TX_RAMP_TGT_2_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_2_POS)/*!< Tx PA ramp target for power index 2*/
#define BT_RF_TX_RAMP_TGT_2            BT_RF_TX_RAMP_TGT_2_MSK
#define BT_RF_TX_RAMP_TGT_2_W(X)       ((X) << BT_RF_TX_RAMP_TGT_2_POS)
#define BT_RF_TX_RAMP_TGT_3_POS        (18U)
#define BT_RF_TX_RAMP_TGT_3_MSK        (0x3fUL << BT_RF_TX_RAMP_TGT_3_POS)/*!< Tx PA ramp target for power index 3*/
#define BT_RF_TX_RAMP_TGT_3            BT_RF_TX_RAMP_TGT_3_MSK
#define BT_RF_TX_RAMP_TGT_3_W(X)       ((X) << BT_RF_TX_RAMP_TGT_3_POS)
#define BT_RF_RESV_NA_BT_RF_37_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_37_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_37_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_37         BT_RF_RESV_NA_BT_RF_37_MSK
#define BT_RF_RESV_NA_BT_RF_37_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_37_POS)


//bt_rf_38 offsetaddress : 0x98
//bt_rf_38 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_38_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_38_MSK    (0xffffffUL << BT_RF_RESV_FIX_BT_RF_38_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_38        BT_RF_RESV_FIX_BT_RF_38_MSK
#define BT_RF_RESV_FIX_BT_RF_38_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_38_POS)
#define BT_RF_RESV_NA_BT_RF_38_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_38_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_38_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_38         BT_RF_RESV_NA_BT_RF_38_MSK
#define BT_RF_RESV_NA_BT_RF_38_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_38_POS)


//bt_rf_39 offsetaddress : 0x9c
//bt_rf_39 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_39_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_39_MSK    (0xffffffUL << BT_RF_RESV_FIX_BT_RF_39_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_39        BT_RF_RESV_FIX_BT_RF_39_MSK
#define BT_RF_RESV_FIX_BT_RF_39_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_39_POS)
#define BT_RF_RESV_NA_BT_RF_39_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_39_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_39_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_39         BT_RF_RESV_NA_BT_RF_39_MSK
#define BT_RF_RESV_NA_BT_RF_39_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_39_POS)


//bt_rf_40 offsetaddress : 0xa0
//bt_rf_40 RegResetValue : 0xNone
#define BT_RF_AGC_OFF_POS              (0U)
#define BT_RF_AGC_OFF_MSK              (0x1UL << BT_RF_AGC_OFF_POS)/*!< AGC on/off control; 0: enable agc; 1: disable agc*/
#define BT_RF_AGC_OFF                  BT_RF_AGC_OFF_MSK
#define BT_RF_AGC_OFF_W(X)             ((X) << BT_RF_AGC_OFF_POS)
#define BT_RF_RESV_FIX_BT_RF_40_POS    (1U)
#define BT_RF_RESV_FIX_BT_RF_40_MSK    (0x7fffffffUL << BT_RF_RESV_FIX_BT_RF_40_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_40        BT_RF_RESV_FIX_BT_RF_40_MSK
#define BT_RF_RESV_FIX_BT_RF_40_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_40_POS)


//bt_rf_41 offsetaddress : 0xa4
//bt_rf_41 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_41_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_41_MSK  (0x7ffffUL << BT_RF_RESV_FIX_0_BT_RF_41_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_41      BT_RF_RESV_FIX_0_BT_RF_41_MSK
#define BT_RF_RESV_FIX_0_BT_RF_41_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_41_POS)
#define BT_RF_RESV_NA_BT_RF_41_POS     (19U)
#define BT_RF_RESV_NA_BT_RF_41_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_41_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_41         BT_RF_RESV_NA_BT_RF_41_MSK
#define BT_RF_RESV_NA_BT_RF_41_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_41_POS)
#define BT_RF_RESV_FIX_BT_RF_41_POS    (29U)
#define BT_RF_RESV_FIX_BT_RF_41_MSK    (0x7UL << BT_RF_RESV_FIX_BT_RF_41_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_41        BT_RF_RESV_FIX_BT_RF_41_MSK
#define BT_RF_RESV_FIX_BT_RF_41_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_41_POS)


//bt_rf_42 offsetaddress : 0xa8
//bt_rf_42 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_42_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_42_MSK  (0xffffUL << BT_RF_RESV_FIX_0_BT_RF_42_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_42      BT_RF_RESV_FIX_0_BT_RF_42_MSK
#define BT_RF_RESV_FIX_0_BT_RF_42_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_42_POS)
#define BT_RF_RESV_NA_BT_RF_42_POS     (16U)
#define BT_RF_RESV_NA_BT_RF_42_MSK     (0xfffUL << BT_RF_RESV_NA_BT_RF_42_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_42         BT_RF_RESV_NA_BT_RF_42_MSK
#define BT_RF_RESV_NA_BT_RF_42_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_42_POS)
#define BT_RF_RESV_FIX_BT_RF_42_POS    (28U)
#define BT_RF_RESV_FIX_BT_RF_42_MSK    (0xfUL << BT_RF_RESV_FIX_BT_RF_42_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_42        BT_RF_RESV_FIX_BT_RF_42_MSK
#define BT_RF_RESV_FIX_BT_RF_42_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_42_POS)


//bt_rf_43 offsetaddress : 0xac
//bt_rf_43 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_43_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_43_MSK    (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_43_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_43        BT_RF_RESV_FIX_BT_RF_43_MSK
#define BT_RF_RESV_FIX_BT_RF_43_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_43_POS)


//bt_rf_44 offsetaddress : 0xb0
//bt_rf_44 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_44_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_44_MSK    (0xffffffffUL << BT_RF_RESV_FIX_BT_RF_44_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_44        BT_RF_RESV_FIX_BT_RF_44_MSK
#define BT_RF_RESV_FIX_BT_RF_44_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_44_POS)


//bt_rf_45 offsetaddress : 0xb4
//bt_rf_45 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_B_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_B_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_B_POS)/*!< CBPF gain2 code for AGC index 0xb*/
#define BT_RF_FLT_GAIN2_BIT_B          BT_RF_FLT_GAIN2_BIT_B_MSK
#define BT_RF_FLT_GAIN2_BIT_B_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_B_POS)
#define BT_RF_FLT_GAIN1_BIT_B_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_B_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_B_POS)/*!< CBPF gain1 code for AGC index 0xb*/
#define BT_RF_FLT_GAIN1_BIT_B          BT_RF_FLT_GAIN1_BIT_B_MSK
#define BT_RF_FLT_GAIN1_BIT_B_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_B_POS)
#define BT_RF_LNA_GAIN3_BIT_B_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_B_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_B_POS)/*!< LNA gain3 code for AGC index 0xb*/
#define BT_RF_LNA_GAIN3_BIT_B          BT_RF_LNA_GAIN3_BIT_B_MSK
#define BT_RF_LNA_GAIN3_BIT_B_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_B_POS)
#define BT_RF_LNA_GAIN2_BIT_B_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_B_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_B_POS)/*!< LNA gain2 code for AGC index 0xb*/
#define BT_RF_LNA_GAIN2_BIT_B          BT_RF_LNA_GAIN2_BIT_B_MSK
#define BT_RF_LNA_GAIN2_BIT_B_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_B_POS)
#define BT_RF_LNA_GAIN1_BIT_B_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_B_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_B_POS)/*!< LNA gain1 code for AGC index 0xb*/
#define BT_RF_LNA_GAIN1_BIT_B          BT_RF_LNA_GAIN1_BIT_B_MSK
#define BT_RF_LNA_GAIN1_BIT_B_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_B_POS)
#define BT_RF_LNA_GAIN1_EN_B_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_B_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_B_POS)/*!< LNA gain1 enable for AGC index 0xb*/
#define BT_RF_LNA_GAIN1_EN_B           BT_RF_LNA_GAIN1_EN_B_MSK
#define BT_RF_LNA_GAIN1_EN_B_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_B_POS)
#define BT_RF_FLT_GAIN2_BIT_C_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_C_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_C_POS)/*!< CBPF gain2 code for AGC index 0xc*/
#define BT_RF_FLT_GAIN2_BIT_C          BT_RF_FLT_GAIN2_BIT_C_MSK
#define BT_RF_FLT_GAIN2_BIT_C_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_C_POS)
#define BT_RF_FLT_GAIN1_BIT_C_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_C_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_C_POS)/*!< CBPF gain1 code for AGC index 0xc*/
#define BT_RF_FLT_GAIN1_BIT_C          BT_RF_FLT_GAIN1_BIT_C_MSK
#define BT_RF_FLT_GAIN1_BIT_C_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_C_POS)
#define BT_RF_LNA_GAIN3_BIT_C_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_C_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_C_POS)/*!< LNA gain3 code for AGC index 0xc*/
#define BT_RF_LNA_GAIN3_BIT_C          BT_RF_LNA_GAIN3_BIT_C_MSK
#define BT_RF_LNA_GAIN3_BIT_C_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_C_POS)
#define BT_RF_LNA_GAIN2_BIT_C_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_C_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_C_POS)/*!< LNA gain2 code for AGC index 0xc*/
#define BT_RF_LNA_GAIN2_BIT_C          BT_RF_LNA_GAIN2_BIT_C_MSK
#define BT_RF_LNA_GAIN2_BIT_C_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_C_POS)
#define BT_RF_LNA_GAIN1_BIT_C_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_C_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_C_POS)/*!< LNA gain1 code for AGC index 0xc*/
#define BT_RF_LNA_GAIN1_BIT_C          BT_RF_LNA_GAIN1_BIT_C_MSK
#define BT_RF_LNA_GAIN1_BIT_C_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_C_POS)
#define BT_RF_LNA_GAIN1_EN_C_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_C_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_C_POS)/*!< LNA gain1 enable for AGC index 0xc*/
#define BT_RF_LNA_GAIN1_EN_C           BT_RF_LNA_GAIN1_EN_C_MSK
#define BT_RF_LNA_GAIN1_EN_C_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_C_POS)
#define BT_RF_RESV_NA_BT_RF_45_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_45_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_45_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_45         BT_RF_RESV_NA_BT_RF_45_MSK
#define BT_RF_RESV_NA_BT_RF_45_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_45_POS)


//bt_rf_46 offsetaddress : 0xb8
//bt_rf_46 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_9_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_9_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_9_POS)/*!< CBPF gain2 code for AGC index 0x9*/
#define BT_RF_FLT_GAIN2_BIT_9          BT_RF_FLT_GAIN2_BIT_9_MSK
#define BT_RF_FLT_GAIN2_BIT_9_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_9_POS)
#define BT_RF_FLT_GAIN1_BIT_9_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_9_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_9_POS)/*!< CBPF gain1 code for AGC index 0x9*/
#define BT_RF_FLT_GAIN1_BIT_9          BT_RF_FLT_GAIN1_BIT_9_MSK
#define BT_RF_FLT_GAIN1_BIT_9_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_9_POS)
#define BT_RF_LNA_GAIN3_BIT_9_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_9_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_9_POS)/*!< LNA gain3 code for AGC index 0x9*/
#define BT_RF_LNA_GAIN3_BIT_9          BT_RF_LNA_GAIN3_BIT_9_MSK
#define BT_RF_LNA_GAIN3_BIT_9_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_9_POS)
#define BT_RF_LNA_GAIN2_BIT_9_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_9_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_9_POS)/*!< LNA gain2 code for AGC index 0x9*/
#define BT_RF_LNA_GAIN2_BIT_9          BT_RF_LNA_GAIN2_BIT_9_MSK
#define BT_RF_LNA_GAIN2_BIT_9_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_9_POS)
#define BT_RF_LNA_GAIN1_BIT_9_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_9_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_9_POS)/*!< LNA gain1 code for AGC index 0x9*/
#define BT_RF_LNA_GAIN1_BIT_9          BT_RF_LNA_GAIN1_BIT_9_MSK
#define BT_RF_LNA_GAIN1_BIT_9_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_9_POS)
#define BT_RF_LNA_GAIN1_EN_9_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_9_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_9_POS)/*!< LNA gain1 enable for AGC index 0x9*/
#define BT_RF_LNA_GAIN1_EN_9           BT_RF_LNA_GAIN1_EN_9_MSK
#define BT_RF_LNA_GAIN1_EN_9_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_9_POS)
#define BT_RF_FLT_GAIN2_BIT_A_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_A_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_A_POS)/*!< CBPF gain2 code for AGC index 0xa*/
#define BT_RF_FLT_GAIN2_BIT_A          BT_RF_FLT_GAIN2_BIT_A_MSK
#define BT_RF_FLT_GAIN2_BIT_A_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_A_POS)
#define BT_RF_FLT_GAIN1_BIT_A_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_A_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_A_POS)/*!< CBPF gain1 code for AGC index 0xa*/
#define BT_RF_FLT_GAIN1_BIT_A          BT_RF_FLT_GAIN1_BIT_A_MSK
#define BT_RF_FLT_GAIN1_BIT_A_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_A_POS)
#define BT_RF_LNA_GAIN3_BIT_A_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_A_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_A_POS)/*!< LNA gain3 code for AGC index 0xa*/
#define BT_RF_LNA_GAIN3_BIT_A          BT_RF_LNA_GAIN3_BIT_A_MSK
#define BT_RF_LNA_GAIN3_BIT_A_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_A_POS)
#define BT_RF_LNA_GAIN2_BIT_A_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_A_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_A_POS)/*!< LNA gain2 code for AGC index 0xa*/
#define BT_RF_LNA_GAIN2_BIT_A          BT_RF_LNA_GAIN2_BIT_A_MSK
#define BT_RF_LNA_GAIN2_BIT_A_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_A_POS)
#define BT_RF_LNA_GAIN1_BIT_A_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_A_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_A_POS)/*!< LNA gain1 code for AGC index 0xa*/
#define BT_RF_LNA_GAIN1_BIT_A          BT_RF_LNA_GAIN1_BIT_A_MSK
#define BT_RF_LNA_GAIN1_BIT_A_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_A_POS)
#define BT_RF_LNA_GAIN1_EN_A_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_A_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_A_POS)/*!< LNA gain1 enable for AGC index 0xa*/
#define BT_RF_LNA_GAIN1_EN_A           BT_RF_LNA_GAIN1_EN_A_MSK
#define BT_RF_LNA_GAIN1_EN_A_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_A_POS)
#define BT_RF_RESV_NA_BT_RF_46_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_46_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_46_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_46         BT_RF_RESV_NA_BT_RF_46_MSK
#define BT_RF_RESV_NA_BT_RF_46_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_46_POS)


//bt_rf_47 offsetaddress : 0xbc
//bt_rf_47 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_7_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_7_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_7_POS)/*!< CBPF gain2 code for AGC index 0x7*/
#define BT_RF_FLT_GAIN2_BIT_7          BT_RF_FLT_GAIN2_BIT_7_MSK
#define BT_RF_FLT_GAIN2_BIT_7_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_7_POS)
#define BT_RF_FLT_GAIN1_BIT_7_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_7_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_7_POS)/*!< CBPF gain1 code for AGC index 0x7*/
#define BT_RF_FLT_GAIN1_BIT_7          BT_RF_FLT_GAIN1_BIT_7_MSK
#define BT_RF_FLT_GAIN1_BIT_7_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_7_POS)
#define BT_RF_LNA_GAIN3_BIT_7_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_7_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_7_POS)/*!< LNA gain3 code for AGC index 0x7*/
#define BT_RF_LNA_GAIN3_BIT_7          BT_RF_LNA_GAIN3_BIT_7_MSK
#define BT_RF_LNA_GAIN3_BIT_7_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_7_POS)
#define BT_RF_LNA_GAIN2_BIT_7_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_7_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_7_POS)/*!< LNA gain2 code for AGC index 0x7*/
#define BT_RF_LNA_GAIN2_BIT_7          BT_RF_LNA_GAIN2_BIT_7_MSK
#define BT_RF_LNA_GAIN2_BIT_7_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_7_POS)
#define BT_RF_LNA_GAIN1_BIT_7_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_7_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_7_POS)/*!< LNA gain1 code for AGC index 0x7*/
#define BT_RF_LNA_GAIN1_BIT_7          BT_RF_LNA_GAIN1_BIT_7_MSK
#define BT_RF_LNA_GAIN1_BIT_7_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_7_POS)
#define BT_RF_LNA_GAIN1_EN_7_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_7_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_7_POS)/*!< LNA gain1 enable for AGC index 0x7*/
#define BT_RF_LNA_GAIN1_EN_7           BT_RF_LNA_GAIN1_EN_7_MSK
#define BT_RF_LNA_GAIN1_EN_7_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_7_POS)
#define BT_RF_FLT_GAIN2_BIT_8_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_8_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_8_POS)/*!< CBPF gain2 code for AGC index 0x8*/
#define BT_RF_FLT_GAIN2_BIT_8          BT_RF_FLT_GAIN2_BIT_8_MSK
#define BT_RF_FLT_GAIN2_BIT_8_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_8_POS)
#define BT_RF_FLT_GAIN1_BIT_8_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_8_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_8_POS)/*!< CBPF gain1 code for AGC index 0x8*/
#define BT_RF_FLT_GAIN1_BIT_8          BT_RF_FLT_GAIN1_BIT_8_MSK
#define BT_RF_FLT_GAIN1_BIT_8_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_8_POS)
#define BT_RF_LNA_GAIN3_BIT_8_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_8_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_8_POS)/*!< LNA gain3 code for AGC index 0x8*/
#define BT_RF_LNA_GAIN3_BIT_8          BT_RF_LNA_GAIN3_BIT_8_MSK
#define BT_RF_LNA_GAIN3_BIT_8_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_8_POS)
#define BT_RF_LNA_GAIN2_BIT_8_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_8_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_8_POS)/*!< LNA gain2 code for AGC index 0x8*/
#define BT_RF_LNA_GAIN2_BIT_8          BT_RF_LNA_GAIN2_BIT_8_MSK
#define BT_RF_LNA_GAIN2_BIT_8_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_8_POS)
#define BT_RF_LNA_GAIN1_BIT_8_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_8_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_8_POS)/*!< LNA gain1 code for AGC index 0x8*/
#define BT_RF_LNA_GAIN1_BIT_8          BT_RF_LNA_GAIN1_BIT_8_MSK
#define BT_RF_LNA_GAIN1_BIT_8_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_8_POS)
#define BT_RF_LNA_GAIN1_EN_8_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_8_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_8_POS)/*!< LNA gain1 enable for AGC index 0x8*/
#define BT_RF_LNA_GAIN1_EN_8           BT_RF_LNA_GAIN1_EN_8_MSK
#define BT_RF_LNA_GAIN1_EN_8_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_8_POS)
#define BT_RF_RESV_NA_BT_RF_47_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_47_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_47_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_47         BT_RF_RESV_NA_BT_RF_47_MSK
#define BT_RF_RESV_NA_BT_RF_47_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_47_POS)


//bt_rf_48 offsetaddress : 0xc0
//bt_rf_48 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_5_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_5_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_5_POS)/*!< CBPF gain2 code for AGC index 0x5*/
#define BT_RF_FLT_GAIN2_BIT_5          BT_RF_FLT_GAIN2_BIT_5_MSK
#define BT_RF_FLT_GAIN2_BIT_5_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_5_POS)
#define BT_RF_FLT_GAIN1_BIT_5_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_5_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_5_POS)/*!< CBPF gain1 code for AGC index 0x5*/
#define BT_RF_FLT_GAIN1_BIT_5          BT_RF_FLT_GAIN1_BIT_5_MSK
#define BT_RF_FLT_GAIN1_BIT_5_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_5_POS)
#define BT_RF_LNA_GAIN3_BIT_5_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_5_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_5_POS)/*!< LNA gain3 code for AGC index 0x5*/
#define BT_RF_LNA_GAIN3_BIT_5          BT_RF_LNA_GAIN3_BIT_5_MSK
#define BT_RF_LNA_GAIN3_BIT_5_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_5_POS)
#define BT_RF_LNA_GAIN2_BIT_5_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_5_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_5_POS)/*!< LNA gain2 code for AGC index 0x5*/
#define BT_RF_LNA_GAIN2_BIT_5          BT_RF_LNA_GAIN2_BIT_5_MSK
#define BT_RF_LNA_GAIN2_BIT_5_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_5_POS)
#define BT_RF_LNA_GAIN1_BIT_5_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_5_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_5_POS)/*!< LNA gain1 code for AGC index 0x5*/
#define BT_RF_LNA_GAIN1_BIT_5          BT_RF_LNA_GAIN1_BIT_5_MSK
#define BT_RF_LNA_GAIN1_BIT_5_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_5_POS)
#define BT_RF_LNA_GAIN1_EN_5_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_5_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_5_POS)/*!< LNA gain1 enable for AGC index 0x5*/
#define BT_RF_LNA_GAIN1_EN_5           BT_RF_LNA_GAIN1_EN_5_MSK
#define BT_RF_LNA_GAIN1_EN_5_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_5_POS)
#define BT_RF_FLT_GAIN2_BIT_6_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_6_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_6_POS)/*!< CBPF gain2 code for AGC index 0x6*/
#define BT_RF_FLT_GAIN2_BIT_6          BT_RF_FLT_GAIN2_BIT_6_MSK
#define BT_RF_FLT_GAIN2_BIT_6_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_6_POS)
#define BT_RF_FLT_GAIN1_BIT_6_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_6_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_6_POS)/*!< CBPF gain1 code for AGC index 0x6*/
#define BT_RF_FLT_GAIN1_BIT_6          BT_RF_FLT_GAIN1_BIT_6_MSK
#define BT_RF_FLT_GAIN1_BIT_6_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_6_POS)
#define BT_RF_LNA_GAIN3_BIT_6_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_6_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_6_POS)/*!< LNA gain3 code for AGC index 0x6*/
#define BT_RF_LNA_GAIN3_BIT_6          BT_RF_LNA_GAIN3_BIT_6_MSK
#define BT_RF_LNA_GAIN3_BIT_6_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_6_POS)
#define BT_RF_LNA_GAIN2_BIT_6_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_6_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_6_POS)/*!< LNA gain2 code for AGC index 0x6*/
#define BT_RF_LNA_GAIN2_BIT_6          BT_RF_LNA_GAIN2_BIT_6_MSK
#define BT_RF_LNA_GAIN2_BIT_6_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_6_POS)
#define BT_RF_LNA_GAIN1_BIT_6_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_6_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_6_POS)/*!< LNA gain1 code for AGC index 0x6*/
#define BT_RF_LNA_GAIN1_BIT_6          BT_RF_LNA_GAIN1_BIT_6_MSK
#define BT_RF_LNA_GAIN1_BIT_6_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_6_POS)
#define BT_RF_LNA_GAIN1_EN_6_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_6_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_6_POS)/*!< LNA gain1 enable for AGC index 0x6*/
#define BT_RF_LNA_GAIN1_EN_6           BT_RF_LNA_GAIN1_EN_6_MSK
#define BT_RF_LNA_GAIN1_EN_6_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_6_POS)
#define BT_RF_RESV_NA_BT_RF_48_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_48_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_48_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_48         BT_RF_RESV_NA_BT_RF_48_MSK
#define BT_RF_RESV_NA_BT_RF_48_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_48_POS)


//bt_rf_49 offsetaddress : 0xc4
//bt_rf_49 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_3_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_3_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_3_POS)/*!< CBPF gain2 code for AGC index 0x3*/
#define BT_RF_FLT_GAIN2_BIT_3          BT_RF_FLT_GAIN2_BIT_3_MSK
#define BT_RF_FLT_GAIN2_BIT_3_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_3_POS)
#define BT_RF_FLT_GAIN1_BIT_3_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_3_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_3_POS)/*!< CBPF gain1 code for AGC index 0x3*/
#define BT_RF_FLT_GAIN1_BIT_3          BT_RF_FLT_GAIN1_BIT_3_MSK
#define BT_RF_FLT_GAIN1_BIT_3_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_3_POS)
#define BT_RF_LNA_GAIN3_BIT_3_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_3_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_3_POS)/*!< LNA gain3 code for AGC index 0x3*/
#define BT_RF_LNA_GAIN3_BIT_3          BT_RF_LNA_GAIN3_BIT_3_MSK
#define BT_RF_LNA_GAIN3_BIT_3_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_3_POS)
#define BT_RF_LNA_GAIN2_BIT_3_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_3_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_3_POS)/*!< LNA gain2 code for AGC index 0x3*/
#define BT_RF_LNA_GAIN2_BIT_3          BT_RF_LNA_GAIN2_BIT_3_MSK
#define BT_RF_LNA_GAIN2_BIT_3_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_3_POS)
#define BT_RF_LNA_GAIN1_BIT_3_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_3_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_3_POS)/*!< LNA gain1 code for AGC index 0x3*/
#define BT_RF_LNA_GAIN1_BIT_3          BT_RF_LNA_GAIN1_BIT_3_MSK
#define BT_RF_LNA_GAIN1_BIT_3_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_3_POS)
#define BT_RF_LNA_GAIN1_EN_3_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_3_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_3_POS)/*!< LNA gain1 enable for AGC index 0x3*/
#define BT_RF_LNA_GAIN1_EN_3           BT_RF_LNA_GAIN1_EN_3_MSK
#define BT_RF_LNA_GAIN1_EN_3_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_3_POS)
#define BT_RF_FLT_GAIN2_BIT_4_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_4_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_4_POS)/*!< CBPF gain2 code for AGC index 0x4*/
#define BT_RF_FLT_GAIN2_BIT_4          BT_RF_FLT_GAIN2_BIT_4_MSK
#define BT_RF_FLT_GAIN2_BIT_4_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_4_POS)
#define BT_RF_FLT_GAIN1_BIT_4_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_4_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_4_POS)/*!< CBPF gain1 code for AGC index 0x4*/
#define BT_RF_FLT_GAIN1_BIT_4          BT_RF_FLT_GAIN1_BIT_4_MSK
#define BT_RF_FLT_GAIN1_BIT_4_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_4_POS)
#define BT_RF_LNA_GAIN3_BIT_4_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_4_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_4_POS)/*!< LNA gain3 code for AGC index 0x4*/
#define BT_RF_LNA_GAIN3_BIT_4          BT_RF_LNA_GAIN3_BIT_4_MSK
#define BT_RF_LNA_GAIN3_BIT_4_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_4_POS)
#define BT_RF_LNA_GAIN2_BIT_4_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_4_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_4_POS)/*!< LNA gain2 code for AGC index 0x4*/
#define BT_RF_LNA_GAIN2_BIT_4          BT_RF_LNA_GAIN2_BIT_4_MSK
#define BT_RF_LNA_GAIN2_BIT_4_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_4_POS)
#define BT_RF_LNA_GAIN1_BIT_4_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_4_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_4_POS)/*!< LNA gain1 code for AGC index 0x4*/
#define BT_RF_LNA_GAIN1_BIT_4          BT_RF_LNA_GAIN1_BIT_4_MSK
#define BT_RF_LNA_GAIN1_BIT_4_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_4_POS)
#define BT_RF_LNA_GAIN1_EN_4_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_4_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_4_POS)/*!< LNA gain1 enable for AGC index 0x4*/
#define BT_RF_LNA_GAIN1_EN_4           BT_RF_LNA_GAIN1_EN_4_MSK
#define BT_RF_LNA_GAIN1_EN_4_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_4_POS)
#define BT_RF_RESV_NA_BT_RF_49_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_49_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_49_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_49         BT_RF_RESV_NA_BT_RF_49_MSK
#define BT_RF_RESV_NA_BT_RF_49_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_49_POS)


//bt_rf_50 offsetaddress : 0xc8
//bt_rf_50 RegResetValue : 0xNone
#define BT_RF_FLT_GAIN2_BIT_1_POS      (0U)
#define BT_RF_FLT_GAIN2_BIT_1_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_1_POS)/*!< CBPF gain2 code for AGC index 0x1*/
#define BT_RF_FLT_GAIN2_BIT_1          BT_RF_FLT_GAIN2_BIT_1_MSK
#define BT_RF_FLT_GAIN2_BIT_1_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_1_POS)
#define BT_RF_FLT_GAIN1_BIT_1_POS      (1U)
#define BT_RF_FLT_GAIN1_BIT_1_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_1_POS)/*!< CBPF gain1 code for AGC index 0x1*/
#define BT_RF_FLT_GAIN1_BIT_1          BT_RF_FLT_GAIN1_BIT_1_MSK
#define BT_RF_FLT_GAIN1_BIT_1_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_1_POS)
#define BT_RF_LNA_GAIN3_BIT_1_POS      (2U)
#define BT_RF_LNA_GAIN3_BIT_1_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_1_POS)/*!< LNA gain3 code for AGC index 0x1*/
#define BT_RF_LNA_GAIN3_BIT_1          BT_RF_LNA_GAIN3_BIT_1_MSK
#define BT_RF_LNA_GAIN3_BIT_1_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_1_POS)
#define BT_RF_LNA_GAIN2_BIT_1_POS      (4U)
#define BT_RF_LNA_GAIN2_BIT_1_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_1_POS)/*!< LNA gain2 code for AGC index 0x1*/
#define BT_RF_LNA_GAIN2_BIT_1          BT_RF_LNA_GAIN2_BIT_1_MSK
#define BT_RF_LNA_GAIN2_BIT_1_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_1_POS)
#define BT_RF_LNA_GAIN1_BIT_1_POS      (6U)
#define BT_RF_LNA_GAIN1_BIT_1_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_1_POS)/*!< LNA gain1 code for AGC index 0x1*/
#define BT_RF_LNA_GAIN1_BIT_1          BT_RF_LNA_GAIN1_BIT_1_MSK
#define BT_RF_LNA_GAIN1_BIT_1_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_1_POS)
#define BT_RF_LNA_GAIN1_EN_1_POS       (12U)
#define BT_RF_LNA_GAIN1_EN_1_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_1_POS)/*!< LNA gain1 enable for AGC index 0x1*/
#define BT_RF_LNA_GAIN1_EN_1           BT_RF_LNA_GAIN1_EN_1_MSK
#define BT_RF_LNA_GAIN1_EN_1_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_1_POS)
#define BT_RF_FLT_GAIN2_BIT_2_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_2_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_2_POS)/*!< CBPF gain2 code for AGC index 0x2*/
#define BT_RF_FLT_GAIN2_BIT_2          BT_RF_FLT_GAIN2_BIT_2_MSK
#define BT_RF_FLT_GAIN2_BIT_2_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_2_POS)
#define BT_RF_FLT_GAIN1_BIT_2_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_2_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_2_POS)/*!< CBPF gain1 code for AGC index 0x2*/
#define BT_RF_FLT_GAIN1_BIT_2          BT_RF_FLT_GAIN1_BIT_2_MSK
#define BT_RF_FLT_GAIN1_BIT_2_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_2_POS)
#define BT_RF_LNA_GAIN3_BIT_2_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_2_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_2_POS)/*!< LNA gain3 code for AGC index 0x2*/
#define BT_RF_LNA_GAIN3_BIT_2          BT_RF_LNA_GAIN3_BIT_2_MSK
#define BT_RF_LNA_GAIN3_BIT_2_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_2_POS)
#define BT_RF_LNA_GAIN2_BIT_2_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_2_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_2_POS)/*!< LNA gain2 code for AGC index 0x2*/
#define BT_RF_LNA_GAIN2_BIT_2          BT_RF_LNA_GAIN2_BIT_2_MSK
#define BT_RF_LNA_GAIN2_BIT_2_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_2_POS)
#define BT_RF_LNA_GAIN1_BIT_2_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_2_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_2_POS)/*!< LNA gain1 code for AGC index 0x2*/
#define BT_RF_LNA_GAIN1_BIT_2          BT_RF_LNA_GAIN1_BIT_2_MSK
#define BT_RF_LNA_GAIN1_BIT_2_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_2_POS)
#define BT_RF_LNA_GAIN1_EN_2_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_2_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_2_POS)/*!< LNA gain1 enable for AGC index 0x2*/
#define BT_RF_LNA_GAIN1_EN_2           BT_RF_LNA_GAIN1_EN_2_MSK
#define BT_RF_LNA_GAIN1_EN_2_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_2_POS)
#define BT_RF_RESV_NA_BT_RF_50_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_50_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_50_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_50         BT_RF_RESV_NA_BT_RF_50_MSK
#define BT_RF_RESV_NA_BT_RF_50_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_50_POS)


//bt_rf_51 offsetaddress : 0xcc
//bt_rf_51 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_BT_RF_51_POS    (0U)
#define BT_RF_RESV_FIX_BT_RF_51_MSK    (0x1fffUL << BT_RF_RESV_FIX_BT_RF_51_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_51        BT_RF_RESV_FIX_BT_RF_51_MSK
#define BT_RF_RESV_FIX_BT_RF_51_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_51_POS)
#define BT_RF_FLT_GAIN2_BIT_0_POS      (13U)
#define BT_RF_FLT_GAIN2_BIT_0_MSK      (0x1UL << BT_RF_FLT_GAIN2_BIT_0_POS)/*!< CBPF gain2 code for AGC index 0x0*/
#define BT_RF_FLT_GAIN2_BIT_0          BT_RF_FLT_GAIN2_BIT_0_MSK
#define BT_RF_FLT_GAIN2_BIT_0_W(X)     ((X) << BT_RF_FLT_GAIN2_BIT_0_POS)
#define BT_RF_FLT_GAIN1_BIT_0_POS      (14U)
#define BT_RF_FLT_GAIN1_BIT_0_MSK      (0x1UL << BT_RF_FLT_GAIN1_BIT_0_POS)/*!< CBPF gain1 code for AGC index 0x0*/
#define BT_RF_FLT_GAIN1_BIT_0          BT_RF_FLT_GAIN1_BIT_0_MSK
#define BT_RF_FLT_GAIN1_BIT_0_W(X)     ((X) << BT_RF_FLT_GAIN1_BIT_0_POS)
#define BT_RF_LNA_GAIN3_BIT_0_POS      (15U)
#define BT_RF_LNA_GAIN3_BIT_0_MSK      (0x3UL << BT_RF_LNA_GAIN3_BIT_0_POS)/*!< LNA gain3 code for AGC index 0x0*/
#define BT_RF_LNA_GAIN3_BIT_0          BT_RF_LNA_GAIN3_BIT_0_MSK
#define BT_RF_LNA_GAIN3_BIT_0_W(X)     ((X) << BT_RF_LNA_GAIN3_BIT_0_POS)
#define BT_RF_LNA_GAIN2_BIT_0_POS      (17U)
#define BT_RF_LNA_GAIN2_BIT_0_MSK      (0x3UL << BT_RF_LNA_GAIN2_BIT_0_POS)/*!< LNA gain2 code for AGC index 0x0*/
#define BT_RF_LNA_GAIN2_BIT_0          BT_RF_LNA_GAIN2_BIT_0_MSK
#define BT_RF_LNA_GAIN2_BIT_0_W(X)     ((X) << BT_RF_LNA_GAIN2_BIT_0_POS)
#define BT_RF_LNA_GAIN1_BIT_0_POS      (19U)
#define BT_RF_LNA_GAIN1_BIT_0_MSK      (0x3fUL << BT_RF_LNA_GAIN1_BIT_0_POS)/*!< LNA gain1 code for AGC index 0x0*/
#define BT_RF_LNA_GAIN1_BIT_0          BT_RF_LNA_GAIN1_BIT_0_MSK
#define BT_RF_LNA_GAIN1_BIT_0_W(X)     ((X) << BT_RF_LNA_GAIN1_BIT_0_POS)
#define BT_RF_LNA_GAIN1_EN_0_POS       (25U)
#define BT_RF_LNA_GAIN1_EN_0_MSK       (0x1UL << BT_RF_LNA_GAIN1_EN_0_POS)/*!< LNA gain1 enable for AGC index 0x0*/
#define BT_RF_LNA_GAIN1_EN_0           BT_RF_LNA_GAIN1_EN_0_MSK
#define BT_RF_LNA_GAIN1_EN_0_W(X)      ((X) << BT_RF_LNA_GAIN1_EN_0_POS)
#define BT_RF_RESV_NA_BT_RF_51_POS     (26U)
#define BT_RF_RESV_NA_BT_RF_51_MSK     (0x3fUL << BT_RF_RESV_NA_BT_RF_51_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_51         BT_RF_RESV_NA_BT_RF_51_MSK
#define BT_RF_RESV_NA_BT_RF_51_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_51_POS)


//bt_rf_52 offsetaddress : 0xd0
//bt_rf_52 RegResetValue : 0xNone
#define BT_RF_RX_GAIN_9_POS            (0U)
#define BT_RF_RX_GAIN_9_MSK            (0xffUL << BT_RF_RX_GAIN_9_POS)/*!< Rx gain (dB) for AGC index 0x9*/
#define BT_RF_RX_GAIN_9                BT_RF_RX_GAIN_9_MSK
#define BT_RF_RX_GAIN_9_W(X)           ((X) << BT_RF_RX_GAIN_9_POS)
#define BT_RF_RX_GAIN_A_POS            (8U)
#define BT_RF_RX_GAIN_A_MSK            (0xffUL << BT_RF_RX_GAIN_A_POS)/*!< Rx gain (dB) for AGC index 0xa*/
#define BT_RF_RX_GAIN_A                BT_RF_RX_GAIN_A_MSK
#define BT_RF_RX_GAIN_A_W(X)           ((X) << BT_RF_RX_GAIN_A_POS)
#define BT_RF_RX_GAIN_B_POS            (16U)
#define BT_RF_RX_GAIN_B_MSK            (0xffUL << BT_RF_RX_GAIN_B_POS)/*!< Rx gain (dB) for AGC index 0xb*/
#define BT_RF_RX_GAIN_B                BT_RF_RX_GAIN_B_MSK
#define BT_RF_RX_GAIN_B_W(X)           ((X) << BT_RF_RX_GAIN_B_POS)
#define BT_RF_RX_GAIN_C_POS            (24U)
#define BT_RF_RX_GAIN_C_MSK            (0xffUL << BT_RF_RX_GAIN_C_POS)/*!< Rx gain (dB) for AGC index 0xc*/
#define BT_RF_RX_GAIN_C                BT_RF_RX_GAIN_C_MSK
#define BT_RF_RX_GAIN_C_W(X)           ((X) << BT_RF_RX_GAIN_C_POS)


//bt_rf_53 offsetaddress : 0xd4
//bt_rf_53 RegResetValue : 0xNone
#define BT_RF_RX_GAIN_5_POS            (0U)
#define BT_RF_RX_GAIN_5_MSK            (0xffUL << BT_RF_RX_GAIN_5_POS)/*!< Rx gain (dB) for AGC index 0x5*/
#define BT_RF_RX_GAIN_5                BT_RF_RX_GAIN_5_MSK
#define BT_RF_RX_GAIN_5_W(X)           ((X) << BT_RF_RX_GAIN_5_POS)
#define BT_RF_RX_GAIN_6_POS            (8U)
#define BT_RF_RX_GAIN_6_MSK            (0xffUL << BT_RF_RX_GAIN_6_POS)/*!< Rx gain (dB) for AGC index 0x6*/
#define BT_RF_RX_GAIN_6                BT_RF_RX_GAIN_6_MSK
#define BT_RF_RX_GAIN_6_W(X)           ((X) << BT_RF_RX_GAIN_6_POS)
#define BT_RF_RX_GAIN_7_POS            (16U)
#define BT_RF_RX_GAIN_7_MSK            (0xffUL << BT_RF_RX_GAIN_7_POS)/*!< Rx gain (dB) for AGC index 0x7*/
#define BT_RF_RX_GAIN_7                BT_RF_RX_GAIN_7_MSK
#define BT_RF_RX_GAIN_7_W(X)           ((X) << BT_RF_RX_GAIN_7_POS)
#define BT_RF_RX_GAIN_8_POS            (24U)
#define BT_RF_RX_GAIN_8_MSK            (0xffUL << BT_RF_RX_GAIN_8_POS)/*!< Rx gain (dB) for AGC index 0x8*/
#define BT_RF_RX_GAIN_8                BT_RF_RX_GAIN_8_MSK
#define BT_RF_RX_GAIN_8_W(X)           ((X) << BT_RF_RX_GAIN_8_POS)


//bt_rf_54 offsetaddress : 0xd8
//bt_rf_54 RegResetValue : 0xNone
#define BT_RF_RX_GAIN_1_POS            (0U)
#define BT_RF_RX_GAIN_1_MSK            (0xffUL << BT_RF_RX_GAIN_1_POS)/*!< Rx gain (dB) for AGC index 0x1*/
#define BT_RF_RX_GAIN_1                BT_RF_RX_GAIN_1_MSK
#define BT_RF_RX_GAIN_1_W(X)           ((X) << BT_RF_RX_GAIN_1_POS)
#define BT_RF_RX_GAIN_2_POS            (8U)
#define BT_RF_RX_GAIN_2_MSK            (0xffUL << BT_RF_RX_GAIN_2_POS)/*!< Rx gain (dB) for AGC index 0x2*/
#define BT_RF_RX_GAIN_2                BT_RF_RX_GAIN_2_MSK
#define BT_RF_RX_GAIN_2_W(X)           ((X) << BT_RF_RX_GAIN_2_POS)
#define BT_RF_RX_GAIN_3_POS            (16U)
#define BT_RF_RX_GAIN_3_MSK            (0xffUL << BT_RF_RX_GAIN_3_POS)/*!< Rx gain (dB) for AGC index 0x3*/
#define BT_RF_RX_GAIN_3                BT_RF_RX_GAIN_3_MSK
#define BT_RF_RX_GAIN_3_W(X)           ((X) << BT_RF_RX_GAIN_3_POS)
#define BT_RF_RX_GAIN_4_POS            (24U)
#define BT_RF_RX_GAIN_4_MSK            (0xffUL << BT_RF_RX_GAIN_4_POS)/*!< Rx gain (dB) for AGC index 0x4*/
#define BT_RF_RX_GAIN_4                BT_RF_RX_GAIN_4_MSK
#define BT_RF_RX_GAIN_4_W(X)           ((X) << BT_RF_RX_GAIN_4_POS)


//bt_rf_55 offsetaddress : 0xdc
//bt_rf_55 RegResetValue : 0xNone
#define BT_RF_RX_GAIN_0_POS            (0U)
#define BT_RF_RX_GAIN_0_MSK            (0xffUL << BT_RF_RX_GAIN_0_POS)/*!< Rx gain (dB) for AGC index 0x0*/
#define BT_RF_RX_GAIN_0                BT_RF_RX_GAIN_0_MSK
#define BT_RF_RX_GAIN_0_W(X)           ((X) << BT_RF_RX_GAIN_0_POS)
#define BT_RF_RO_AGC_GAIN_IDX_POS      (8U)
#define BT_RF_RO_AGC_GAIN_IDX_MSK      (0xfUL << BT_RF_RO_AGC_GAIN_IDX_POS)/*!< */
#define BT_RF_RO_AGC_GAIN_IDX          BT_RF_RO_AGC_GAIN_IDX_MSK
#define BT_RF_RO_AGC_GAIN_IDX_W(X)     ((X) << BT_RF_RO_AGC_GAIN_IDX_POS)
#define BT_RF_RO_AGC_GAIN_CODE_POS     (12U)
#define BT_RF_RO_AGC_GAIN_CODE_MSK     (0x1fffUL << BT_RF_RO_AGC_GAIN_CODE_POS)/*!< */
#define BT_RF_RO_AGC_GAIN_CODE         BT_RF_RO_AGC_GAIN_CODE_MSK
#define BT_RF_RO_AGC_GAIN_CODE_W(X)    ((X) << BT_RF_RO_AGC_GAIN_CODE_POS)
#define BT_RF_RO_AGC_DBG_POS           (25U)
#define BT_RF_RO_AGC_DBG_MSK           (0x1fUL << BT_RF_RO_AGC_DBG_POS)/*!< */
#define BT_RF_RO_AGC_DBG               BT_RF_RO_AGC_DBG_MSK
#define BT_RF_RO_AGC_DBG_W(X)          ((X) << BT_RF_RO_AGC_DBG_POS)
#define BT_RF_RESV_NA_BT_RF_55_POS     (30U)
#define BT_RF_RESV_NA_BT_RF_55_MSK     (0x3UL << BT_RF_RESV_NA_BT_RF_55_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_55         BT_RF_RESV_NA_BT_RF_55_MSK
#define BT_RF_RESV_NA_BT_RF_55_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_55_POS)


//bt_rf_56 offsetaddress : 0xe0
//bt_rf_56 RegResetValue : 0xNone
#define BT_RF_BYPASS_RCCAL_FS_POS      (0U)
#define BT_RF_BYPASS_RCCAL_FS_MSK      (0x1UL << BT_RF_BYPASS_RCCAL_FS_POS)/*!< Rx RC calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_RCCAL_FS          BT_RF_BYPASS_RCCAL_FS_MSK
#define BT_RF_BYPASS_RCCAL_FS_W(X)     ((X) << BT_RF_BYPASS_RCCAL_FS_POS)
#define BT_RF_BYPASS_TXVCOCAL_FS_POS   (1U)
#define BT_RF_BYPASS_TXVCOCAL_FS_MSK   (0x1UL << BT_RF_BYPASS_TXVCOCAL_FS_POS)/*!< Tx VCO calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_TXVCOCAL_FS       BT_RF_BYPASS_TXVCOCAL_FS_MSK
#define BT_RF_BYPASS_TXVCOCAL_FS_W(X)  ((X) << BT_RF_BYPASS_TXVCOCAL_FS_POS)
#define BT_RF_BYPASS_RXVCOCAL_FS_POS   (2U)
#define BT_RF_BYPASS_RXVCOCAL_FS_MSK   (0x1UL << BT_RF_BYPASS_RXVCOCAL_FS_POS)/*!< Rx VCO calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_RXVCOCAL_FS       BT_RF_BYPASS_RXVCOCAL_FS_MSK
#define BT_RF_BYPASS_RXVCOCAL_FS_W(X)  ((X) << BT_RF_BYPASS_RXVCOCAL_FS_POS)
#define BT_RF_BYPASS_TPCAL_FS_POS      (3U)
#define BT_RF_BYPASS_TPCAL_FS_MSK      (0x1UL << BT_RF_BYPASS_TPCAL_FS_POS)/*!< Tx TP calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_TPCAL_FS          BT_RF_BYPASS_TPCAL_FS_MSK
#define BT_RF_BYPASS_TPCAL_FS_W(X)     ((X) << BT_RF_BYPASS_TPCAL_FS_POS)
#define BT_RF_BYPASS_TXDCOC_FS_POS     (4U)
#define BT_RF_BYPASS_TXDCOC_FS_MSK     (0x1UL << BT_RF_BYPASS_TXDCOC_FS_POS)/*!< Tx DCOC calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_TXDCOC_FS         BT_RF_BYPASS_TXDCOC_FS_MSK
#define BT_RF_BYPASS_TXDCOC_FS_W(X)    ((X) << BT_RF_BYPASS_TXDCOC_FS_POS)
#define BT_RF_BYPASS_RXDCOC1_FS_POS    (5U)
#define BT_RF_BYPASS_RXDCOC1_FS_MSK    (0x1UL << BT_RF_BYPASS_RXDCOC1_FS_POS)/*!< Rx DCOC1 calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_RXDCOC1_FS        BT_RF_BYPASS_RXDCOC1_FS_MSK
#define BT_RF_BYPASS_RXDCOC1_FS_W(X)   ((X) << BT_RF_BYPASS_RXDCOC1_FS_POS)
#define BT_RF_BYPASS_RXDCOC2_FS_POS    (6U)
#define BT_RF_BYPASS_RXDCOC2_FS_MSK    (0x1UL << BT_RF_BYPASS_RXDCOC2_FS_POS)/*!< Rx DCOC2 calibration bypass for fast settle packets*/
#define BT_RF_BYPASS_RXDCOC2_FS        BT_RF_BYPASS_RXDCOC2_FS_MSK
#define BT_RF_BYPASS_RXDCOC2_FS_W(X)   ((X) << BT_RF_BYPASS_RXDCOC2_FS_POS)
#define BT_RF_RF_PMU_TX_DLY_FS_POS     (7U)
#define BT_RF_RF_PMU_TX_DLY_FS_MSK     (0xfUL << BT_RF_RF_PMU_TX_DLY_FS_POS)/*!< Wait time before bandgap and LDO power up during Tx for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_PMU_TX_DLY_FS         BT_RF_RF_PMU_TX_DLY_FS_MSK
#define BT_RF_RF_PMU_TX_DLY_FS_W(X)    ((X) << BT_RF_RF_PMU_TX_DLY_FS_POS)
#define BT_RF_RF_PMU_RX_DLY_FS_POS     (11U)
#define BT_RF_RF_PMU_RX_DLY_FS_MSK     (0xfUL << BT_RF_RF_PMU_RX_DLY_FS_POS)/*!< Wait time before bandgap and LDO power up during Rx for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_PMU_RX_DLY_FS         BT_RF_RF_PMU_RX_DLY_FS_MSK
#define BT_RF_RF_PMU_RX_DLY_FS_W(X)    ((X) << BT_RF_RF_PMU_RX_DLY_FS_POS)
#define BT_RF_RF_RCCAL_DLY_FS_POS      (15U)
#define BT_RF_RF_RCCAL_DLY_FS_MSK      (0x1fUL << BT_RF_RF_RCCAL_DLY_FS_POS)/*!< Wait time before RC calibration power up for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_RCCAL_DLY_FS          BT_RF_RF_RCCAL_DLY_FS_MSK
#define BT_RF_RF_RCCAL_DLY_FS_W(X)     ((X) << BT_RF_RF_RCCAL_DLY_FS_POS)
#define BT_RF_RF_PLL_TX_DLY_FS_POS     (20U)
#define BT_RF_RF_PLL_TX_DLY_FS_MSK     (0x1fUL << BT_RF_RF_PLL_TX_DLY_FS_POS)/*!< Wait time before PLL power up during Tx for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_PLL_TX_DLY_FS         BT_RF_RF_PLL_TX_DLY_FS_MSK
#define BT_RF_RF_PLL_TX_DLY_FS_W(X)    ((X) << BT_RF_RF_PLL_TX_DLY_FS_POS)
#define BT_RF_RF_PLL_RX_DLY_FS_POS     (25U)
#define BT_RF_RF_PLL_RX_DLY_FS_MSK     (0x1fUL << BT_RF_RF_PLL_RX_DLY_FS_POS)/*!< Wait time before PLL power up during Rx for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_PLL_RX_DLY_FS         BT_RF_RF_PLL_RX_DLY_FS_MSK
#define BT_RF_RF_PLL_RX_DLY_FS_W(X)    ((X) << BT_RF_RF_PLL_RX_DLY_FS_POS)
#define BT_RF_RESV_NA_BT_RF_56_POS     (30U)
#define BT_RF_RESV_NA_BT_RF_56_MSK     (0x3UL << BT_RF_RESV_NA_BT_RF_56_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_56         BT_RF_RESV_NA_BT_RF_56_MSK
#define BT_RF_RESV_NA_BT_RF_56_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_56_POS)


//bt_rf_57 offsetaddress : 0xe4
//bt_rf_57 RegResetValue : 0xNone
#define BT_RF_RF_DPTH_TX_DLY_IQ_FS_POS (0U)
#define BT_RF_RF_DPTH_TX_DLY_IQ_FS_MSK (0xffUL << BT_RF_RF_DPTH_TX_DLY_IQ_FS_POS)/*!< Wait time before Tx datapath power up in IQ mode for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_TX_DLY_IQ_FS     BT_RF_RF_DPTH_TX_DLY_IQ_FS_MSK
#define BT_RF_RF_DPTH_TX_DLY_IQ_FS_W(X) ((X) << BT_RF_RF_DPTH_TX_DLY_IQ_FS_POS)
#define BT_RF_RF_DPTH_TX_DLY_TP_FS_POS (8U)
#define BT_RF_RF_DPTH_TX_DLY_TP_FS_MSK (0xffUL << BT_RF_RF_DPTH_TX_DLY_TP_FS_POS)/*!< Wait time before Tx datapath power up in TP mode for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_TX_DLY_TP_FS     BT_RF_RF_DPTH_TX_DLY_TP_FS_MSK
#define BT_RF_RF_DPTH_TX_DLY_TP_FS_W(X) ((X) << BT_RF_RF_DPTH_TX_DLY_TP_FS_POS)
#define BT_RF_RF_DPTH_RX_DLY_FS_POS    (16U)
#define BT_RF_RF_DPTH_RX_DLY_FS_MSK    (0xffUL << BT_RF_RF_DPTH_RX_DLY_FS_POS)/*!< Wait time before Rx datapath power up for fast settle packets (unit: 0.5 us)*/
#define BT_RF_RF_DPTH_RX_DLY_FS        BT_RF_RF_DPTH_RX_DLY_FS_MSK
#define BT_RF_RF_DPTH_RX_DLY_FS_W(X)   ((X) << BT_RF_RF_DPTH_RX_DLY_FS_POS)
#define BT_RF_RESV_NA_BT_RF_57_POS     (24U)
#define BT_RF_RESV_NA_BT_RF_57_MSK     (0xffUL << BT_RF_RESV_NA_BT_RF_57_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_57         BT_RF_RESV_NA_BT_RF_57_MSK
#define BT_RF_RESV_NA_BT_RF_57_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_57_POS)


//bt_rf_58 offsetaddress : 0xe8
//bt_rf_58 RegResetValue : 0xNone
#define BT_RF_RESV_FIX_0_BT_RF_58_POS  (0U)
#define BT_RF_RESV_FIX_0_BT_RF_58_MSK  (0xfUL << BT_RF_RESV_FIX_0_BT_RF_58_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_0_BT_RF_58      BT_RF_RESV_FIX_0_BT_RF_58_MSK
#define BT_RF_RESV_FIX_0_BT_RF_58_W(X) ((X) << BT_RF_RESV_FIX_0_BT_RF_58_POS)
#define BT_RF_RF_ADC_SIGN_POS          (4U)
#define BT_RF_RF_ADC_SIGN_MSK          (0x1UL << BT_RF_RF_ADC_SIGN_POS)/*!< RF Rx ADC IQ output sign bit selection; 0: signed; 1: unsigned*/
#define BT_RF_RF_ADC_SIGN              BT_RF_RF_ADC_SIGN_MSK
#define BT_RF_RF_ADC_SIGN_W(X)         ((X) << BT_RF_RF_ADC_SIGN_POS)
#define BT_RF_RESV_FIX_BT_RF_58_POS    (5U)
#define BT_RF_RESV_FIX_BT_RF_58_MSK    (0x7ffffffUL << BT_RF_RESV_FIX_BT_RF_58_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_58        BT_RF_RESV_FIX_BT_RF_58_MSK
#define BT_RF_RESV_FIX_BT_RF_58_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_58_POS)


//bt_rf_59 offsetaddress : 0xf4
//bt_rf_59 RegResetValue : 0xNone
#define BT_RF_RO_RXDCOC1_DONE_POS      (0U)
#define BT_RF_RO_RXDCOC1_DONE_MSK      (0x1UL << BT_RF_RO_RXDCOC1_DONE_POS)/*!< RXDCOC1 calibration done indicator*/
#define BT_RF_RO_RXDCOC1_DONE          BT_RF_RO_RXDCOC1_DONE_MSK
#define BT_RF_RO_RXDCOC1_DONE_W(X)     ((X) << BT_RF_RO_RXDCOC1_DONE_POS)
#define BT_RF_RO_RXDCOC2_DONE_POS      (1U)
#define BT_RF_RO_RXDCOC2_DONE_MSK      (0x1UL << BT_RF_RO_RXDCOC2_DONE_POS)/*!< RXDCOC2 calibration done indicator*/
#define BT_RF_RO_RXDCOC2_DONE          BT_RF_RO_RXDCOC2_DONE_MSK
#define BT_RF_RO_RXDCOC2_DONE_W(X)     ((X) << BT_RF_RO_RXDCOC2_DONE_POS)
#define BT_RF_RO_TXDCOC_DONE_POS       (2U)
#define BT_RF_RO_TXDCOC_DONE_MSK       (0x1UL << BT_RF_RO_TXDCOC_DONE_POS)/*!< TXDCOC calibration done indicator*/
#define BT_RF_RO_TXDCOC_DONE           BT_RF_RO_TXDCOC_DONE_MSK
#define BT_RF_RO_TXDCOC_DONE_W(X)      ((X) << BT_RF_RO_TXDCOC_DONE_POS)
#define BT_RF_RO_RCCAL_DONE_POS        (3U)
#define BT_RF_RO_RCCAL_DONE_MSK        (0x1UL << BT_RF_RO_RCCAL_DONE_POS)/*!< RC calibration done indicator*/
#define BT_RF_RO_RCCAL_DONE            BT_RF_RO_RCCAL_DONE_MSK
#define BT_RF_RO_RCCAL_DONE_W(X)       ((X) << BT_RF_RO_RCCAL_DONE_POS)
#define BT_RF_RO_VCOCAL_DONE_POS       (4U)
#define BT_RF_RO_VCOCAL_DONE_MSK       (0x1UL << BT_RF_RO_VCOCAL_DONE_POS)/*!< VCO calibration done indicator*/
#define BT_RF_RO_VCOCAL_DONE           BT_RF_RO_VCOCAL_DONE_MSK
#define BT_RF_RO_VCOCAL_DONE_W(X)      ((X) << BT_RF_RO_VCOCAL_DONE_POS)
#define BT_RF_RO_TPCAL_DONE_POS        (5U)
#define BT_RF_RO_TPCAL_DONE_MSK        (0x1UL << BT_RF_RO_TPCAL_DONE_POS)/*!< TP calibration done indicator*/
#define BT_RF_RO_TPCAL_DONE            BT_RF_RO_TPCAL_DONE_MSK
#define BT_RF_RO_TPCAL_DONE_W(X)       ((X) << BT_RF_RO_TPCAL_DONE_POS)
#define BT_RF_RO_RXDCOC1_I_CODE_POS    (6U)
#define BT_RF_RO_RXDCOC1_I_CODE_MSK    (0x3fUL << BT_RF_RO_RXDCOC1_I_CODE_POS)/*!< RXDCOC1 calibration I-path code result*/
#define BT_RF_RO_RXDCOC1_I_CODE        BT_RF_RO_RXDCOC1_I_CODE_MSK
#define BT_RF_RO_RXDCOC1_I_CODE_W(X)   ((X) << BT_RF_RO_RXDCOC1_I_CODE_POS)
#define BT_RF_RO_RXDCOC1_Q_CODE_POS    (12U)
#define BT_RF_RO_RXDCOC1_Q_CODE_MSK    (0x3fUL << BT_RF_RO_RXDCOC1_Q_CODE_POS)/*!< RXDCOC1 calibration Q-path code result*/
#define BT_RF_RO_RXDCOC1_Q_CODE        BT_RF_RO_RXDCOC1_Q_CODE_MSK
#define BT_RF_RO_RXDCOC1_Q_CODE_W(X)   ((X) << BT_RF_RO_RXDCOC1_Q_CODE_POS)
#define BT_RF_RO_RXDCOC2_I_CODE_POS    (18U)
#define BT_RF_RO_RXDCOC2_I_CODE_MSK    (0x3fUL << BT_RF_RO_RXDCOC2_I_CODE_POS)/*!< RXDCOC2 calibration I-path code result*/
#define BT_RF_RO_RXDCOC2_I_CODE        BT_RF_RO_RXDCOC2_I_CODE_MSK
#define BT_RF_RO_RXDCOC2_I_CODE_W(X)   ((X) << BT_RF_RO_RXDCOC2_I_CODE_POS)
#define BT_RF_RO_RXDCOC2_Q_CODE_POS    (24U)
#define BT_RF_RO_RXDCOC2_Q_CODE_MSK    (0x3fUL << BT_RF_RO_RXDCOC2_Q_CODE_POS)/*!< RXDCOC2 calibration Q-path code result*/
#define BT_RF_RO_RXDCOC2_Q_CODE        BT_RF_RO_RXDCOC2_Q_CODE_MSK
#define BT_RF_RO_RXDCOC2_Q_CODE_W(X)   ((X) << BT_RF_RO_RXDCOC2_Q_CODE_POS)
#define BT_RF_RESV_NA_BT_RF_59_POS     (30U)
#define BT_RF_RESV_NA_BT_RF_59_MSK     (0x3UL << BT_RF_RESV_NA_BT_RF_59_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_59         BT_RF_RESV_NA_BT_RF_59_MSK
#define BT_RF_RESV_NA_BT_RF_59_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_59_POS)


//bt_rf_60 offsetaddress : 0xf8
//bt_rf_60 RegResetValue : 0xNone
#define BT_RF_RO_TPCAL_GAIN_CODE_POS   (0U)
#define BT_RF_RO_TPCAL_GAIN_CODE_MSK   (0x7ffUL << BT_RF_RO_TPCAL_GAIN_CODE_POS)/*!< TP calibration gain code result*/
#define BT_RF_RO_TPCAL_GAIN_CODE       BT_RF_RO_TPCAL_GAIN_CODE_MSK
#define BT_RF_RO_TPCAL_GAIN_CODE_W(X)  ((X) << BT_RF_RO_TPCAL_GAIN_CODE_POS)
#define BT_RF_RO_TPCAL_CNTR_0_POS      (11U)
#define BT_RF_RO_TPCAL_CNTR_0_MSK      (0x7ffffUL << BT_RF_RO_TPCAL_CNTR_0_POS)/*!< TP calibration counter result when DAC set to logic 0*/
#define BT_RF_RO_TPCAL_CNTR_0          BT_RF_RO_TPCAL_CNTR_0_MSK
#define BT_RF_RO_TPCAL_CNTR_0_W(X)     ((X) << BT_RF_RO_TPCAL_CNTR_0_POS)
#define BT_RF_RESV_NA_BT_RF_60_POS     (30U)
#define BT_RF_RESV_NA_BT_RF_60_MSK     (0x3UL << BT_RF_RESV_NA_BT_RF_60_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_60         BT_RF_RESV_NA_BT_RF_60_MSK
#define BT_RF_RESV_NA_BT_RF_60_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_60_POS)


//bt_rf_61 offsetaddress : 0xfc
//bt_rf_61 RegResetValue : 0xNone
#define BT_RF_RO_TPCAL_CNTR_1_POS      (0U)
#define BT_RF_RO_TPCAL_CNTR_1_MSK      (0x7ffffUL << BT_RF_RO_TPCAL_CNTR_1_POS)/*!< TP calibration counter result when DAC set to logic 1*/
#define BT_RF_RO_TPCAL_CNTR_1          BT_RF_RO_TPCAL_CNTR_1_MSK
#define BT_RF_RO_TPCAL_CNTR_1_W(X)     ((X) << BT_RF_RO_TPCAL_CNTR_1_POS)
#define BT_RF_RESV_NA_BT_RF_61_POS     (19U)
#define BT_RF_RESV_NA_BT_RF_61_MSK     (0x1fffUL << BT_RF_RESV_NA_BT_RF_61_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_61         BT_RF_RESV_NA_BT_RF_61_MSK
#define BT_RF_RESV_NA_BT_RF_61_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_61_POS)


//bt_rf_62 offsetaddress : 0x100
//bt_rf_62 RegResetValue : 0xNone
#define BT_RF_CBPF_IFSEL_SR1M_BT_POS   (0U)
#define BT_RF_CBPF_IFSEL_SR1M_BT_MSK   (0x3UL << BT_RF_CBPF_IFSEL_SR1M_BT_POS)/*!< cbpf IF trim for  bt 1M mode*/
#define BT_RF_CBPF_IFSEL_SR1M_BT       BT_RF_CBPF_IFSEL_SR1M_BT_MSK
#define BT_RF_CBPF_IFSEL_SR1M_BT_W(X)  ((X) << BT_RF_CBPF_IFSEL_SR1M_BT_POS)
#define BT_RF_CBPF_IFSEL_SR2M_BT_POS   (2U)
#define BT_RF_CBPF_IFSEL_SR2M_BT_MSK   (0x3UL << BT_RF_CBPF_IFSEL_SR2M_BT_POS)/*!< cbpf IF trim for  bt 2M mode*/
#define BT_RF_CBPF_IFSEL_SR2M_BT       BT_RF_CBPF_IFSEL_SR2M_BT_MSK
#define BT_RF_CBPF_IFSEL_SR2M_BT_W(X)  ((X) << BT_RF_CBPF_IFSEL_SR2M_BT_POS)
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_POS  (4U)
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_MSK  (0x3UL << BT_RF_CBPF_IFSEL_SR1M_TAHDT_POS)/*!< cbpf IF trim for  TAHDT 1M mode*/
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT      BT_RF_CBPF_IFSEL_SR1M_TAHDT_MSK
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_W(X) ((X) << BT_RF_CBPF_IFSEL_SR1M_TAHDT_POS)
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_POS  (6U)
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_MSK  (0x3UL << BT_RF_CBPF_IFSEL_SR2M_TAHDT_POS)/*!< cbpf IF trim for  TAHDT 2M mode*/
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT      BT_RF_CBPF_IFSEL_SR2M_TAHDT_MSK
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_W(X) ((X) << BT_RF_CBPF_IFSEL_SR2M_TAHDT_POS)
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_POS  (8U)
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_MSK  (0x3UL << BT_RF_CBPF_IFSEL_SR4M_TAHDT_POS)/*!< cbpf IF trim for  TAHDT 4M mode*/
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT      BT_RF_CBPF_IFSEL_SR4M_TAHDT_MSK
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_W(X) ((X) << BT_RF_CBPF_IFSEL_SR4M_TAHDT_POS)
#define BT_RF_RESV_FIX_BT_RF_62_POS    (10U)
#define BT_RF_RESV_FIX_BT_RF_62_MSK    (0xffUL << BT_RF_RESV_FIX_BT_RF_62_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_62        BT_RF_RESV_FIX_BT_RF_62_MSK
#define BT_RF_RESV_FIX_BT_RF_62_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_62_POS)
#define BT_RF_RESV_NA_BT_RF_62_POS     (18U)
#define BT_RF_RESV_NA_BT_RF_62_MSK     (0x3fffUL << BT_RF_RESV_NA_BT_RF_62_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_62         BT_RF_RESV_NA_BT_RF_62_MSK
#define BT_RF_RESV_NA_BT_RF_62_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_62_POS)


//bt_rf_63 offsetaddress : 0x104
//bt_rf_63 RegResetValue : 0xNone
#define BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_POS (0U)
#define BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_MSK (0x3UL << BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_POS)/*!< cbpf IF trim for  bt 1M mode*/
#define BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63 BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_MSK
#define BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_W(X) ((X) << BT_RF_CBPF_IFSEL_SR1M_BT_BT_RF_63_POS)
#define BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_POS (2U)
#define BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_MSK (0x3UL << BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_POS)/*!< cbpf IF trim for  bt 2M mode*/
#define BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63 BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_MSK
#define BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_W(X) ((X) << BT_RF_CBPF_IFSEL_SR2M_BT_BT_RF_63_POS)
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_POS (4U)
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_MSK (0x3UL << BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_POS)/*!< cbpf IF trim for  TAHDT 1M mode*/
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63 BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_MSK
#define BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_W(X) ((X) << BT_RF_CBPF_IFSEL_SR1M_TAHDT_BT_RF_63_POS)
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_POS (6U)
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_MSK (0x3UL << BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_POS)/*!< cbpf IF trim for  TAHDT 2M mode*/
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63 BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_MSK
#define BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_W(X) ((X) << BT_RF_CBPF_IFSEL_SR2M_TAHDT_BT_RF_63_POS)
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_POS (8U)
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_MSK (0x3UL << BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_POS)/*!< cbpf IF trim for  TAHDT 4M mode*/
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63 BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_MSK
#define BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_W(X) ((X) << BT_RF_CBPF_IFSEL_SR4M_TAHDT_BT_RF_63_POS)
#define BT_RF_RESV_FIX_BT_RF_63_POS    (10U)
#define BT_RF_RESV_FIX_BT_RF_63_MSK    (0xffUL << BT_RF_RESV_FIX_BT_RF_63_POS)/*!< fixed*/
#define BT_RF_RESV_FIX_BT_RF_63        BT_RF_RESV_FIX_BT_RF_63_MSK
#define BT_RF_RESV_FIX_BT_RF_63_W(X)   ((X) << BT_RF_RESV_FIX_BT_RF_63_POS)
#define BT_RF_RESV_NA_BT_RF_63_POS     (18U)
#define BT_RF_RESV_NA_BT_RF_63_MSK     (0x3fffUL << BT_RF_RESV_NA_BT_RF_63_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_63         BT_RF_RESV_NA_BT_RF_63_MSK
#define BT_RF_RESV_NA_BT_RF_63_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_63_POS)


//bt_rf_64 offsetaddress : 0x108
//bt_rf_64 RegResetValue : 0xNone
#define BT_RF_TXLPF_BW_SR1M_BT_POS     (0U)
#define BT_RF_TXLPF_BW_SR1M_BT_MSK     (0x3UL << BT_RF_TXLPF_BW_SR1M_BT_POS)/*!< txlpf bw trim for bt 1M mode*/
#define BT_RF_TXLPF_BW_SR1M_BT         BT_RF_TXLPF_BW_SR1M_BT_MSK
#define BT_RF_TXLPF_BW_SR1M_BT_W(X)    ((X) << BT_RF_TXLPF_BW_SR1M_BT_POS)
#define BT_RF_TXLPF_BW_SR2M_BT_POS     (2U)
#define BT_RF_TXLPF_BW_SR2M_BT_MSK     (0x3UL << BT_RF_TXLPF_BW_SR2M_BT_POS)/*!< txlpf bw trim for bt 2M mode*/
#define BT_RF_TXLPF_BW_SR2M_BT         BT_RF_TXLPF_BW_SR2M_BT_MSK
#define BT_RF_TXLPF_BW_SR2M_BT_W(X)    ((X) << BT_RF_TXLPF_BW_SR2M_BT_POS)
#define BT_RF_TXLPF_BW_SR1M_TAHDT_POS    (4U)
#define BT_RF_TXLPF_BW_SR1M_TAHDT_MSK    (0x3UL << BT_RF_TXLPF_BW_SR1M_TAHDT_POS)/*!< txlpf bw trim for TAHDT1M mode*/
#define BT_RF_TXLPF_BW_SR1M_TAHDT        BT_RF_TXLPF_BW_SR1M_TAHDT_MSK
#define BT_RF_TXLPF_BW_SR1M_TAHDT_W(X)   ((X) << BT_RF_TXLPF_BW_SR1M_TAHDT_POS)
#define BT_RF_TXLPF_BW_SR2M_TAHDT_POS    (6U)
#define BT_RF_TXLPF_BW_SR2M_TAHDT_MSK    (0x3UL << BT_RF_TXLPF_BW_SR2M_TAHDT_POS)/*!< txlpf bw trim for TAHDT 2M mode*/
#define BT_RF_TXLPF_BW_SR2M_TAHDT        BT_RF_TXLPF_BW_SR2M_TAHDT_MSK
#define BT_RF_TXLPF_BW_SR2M_TAHDT_W(X)   ((X) << BT_RF_TXLPF_BW_SR2M_TAHDT_POS)
#define BT_RF_TXLPF_BW_SR4M_TAHDT_POS    (8U)
#define BT_RF_TXLPF_BW_SR4M_TAHDT_MSK    (0x3UL << BT_RF_TXLPF_BW_SR4M_TAHDT_POS)/*!< txlpf bw trim for TAHDT 4M mode*/
#define BT_RF_TXLPF_BW_SR4M_TAHDT        BT_RF_TXLPF_BW_SR4M_TAHDT_MSK
#define BT_RF_TXLPF_BW_SR4M_TAHDT_W(X)   ((X) << BT_RF_TXLPF_BW_SR4M_TAHDT_POS)
#define BT_RF_TXLPF_GAIN_POS           (10U)
#define BT_RF_TXLPF_GAIN_MSK           (0x3UL << BT_RF_TXLPF_GAIN_POS)/*!< txlpf gain trim*/
#define BT_RF_TXLPF_GAIN               BT_RF_TXLPF_GAIN_MSK
#define BT_RF_TXLPF_GAIN_W(X)          ((X) << BT_RF_TXLPF_GAIN_POS)
#define BT_RF_TXMIX_GAIN_POS           (12U)
#define BT_RF_TXMIX_GAIN_MSK           (0x3UL << BT_RF_TXMIX_GAIN_POS)/*!< tx mixer gain trim*/
#define BT_RF_TXMIX_GAIN               BT_RF_TXMIX_GAIN_MSK
#define BT_RF_TXMIX_GAIN_W(X)          ((X) << BT_RF_TXMIX_GAIN_POS)
#define BT_RF_PA_BC2V_POS              (14U)
#define BT_RF_PA_BC2V_MSK              (0x1UL << BT_RF_PA_BC2V_POS)/*!< PA cascade bias voltage trim for 2v*/
#define BT_RF_PA_BC2V                  BT_RF_PA_BC2V_MSK
#define BT_RF_PA_BC2V_W(X)             ((X) << BT_RF_PA_BC2V_POS)
#define BT_RF_PA_BCLOW2V_POS           (15U)
#define BT_RF_PA_BCLOW2V_MSK           (0x1UL << BT_RF_PA_BCLOW2V_POS)/*!< PA cascade bias low voltage trim for 2v*/
#define BT_RF_PA_BCLOW2V               BT_RF_PA_BCLOW2V_MSK
#define BT_RF_PA_BCLOW2V_W(X)          ((X) << BT_RF_PA_BCLOW2V_POS)
#define BT_RF_RESV_NA_BT_RF_64_POS     (16U)
#define BT_RF_RESV_NA_BT_RF_64_MSK     (0xffffUL << BT_RF_RESV_NA_BT_RF_64_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_64         BT_RF_RESV_NA_BT_RF_64_MSK
#define BT_RF_RESV_NA_BT_RF_64_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_64_POS)


//bt_rf_65 offsetaddress : 0x110
//bt_rf_65 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_0 BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_0_POS)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_1 BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_1_POS)
#define BT_RF_RESV_NA_BT_RF_65_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_65_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_65_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_65         BT_RF_RESV_NA_BT_RF_65_MSK
#define BT_RF_RESV_NA_BT_RF_65_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_65_POS)


//bt_rf_66 offsetaddress : 0x114
//bt_rf_66 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_2 BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_2_POS)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_3 BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_3_POS)
#define BT_RF_RESV_NA_BT_RF_66_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_66_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_66_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_66         BT_RF_RESV_NA_BT_RF_66_MSK
#define BT_RF_RESV_NA_BT_RF_66_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_66_POS)


//bt_rf_67 offsetaddress : 0x118
//bt_rf_67 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_4 BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_4_POS)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_5 BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_5_POS)
#define BT_RF_RESV_NA_BT_RF_67_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_67_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_67_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_67         BT_RF_RESV_NA_BT_RF_67_MSK
#define BT_RF_RESV_NA_BT_RF_67_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_67_POS)


//bt_rf_68 offsetaddress : 0x11c
//bt_rf_68 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_6 BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_6_POS)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_7 BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_MSK
#define BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_1M_VAL_7_POS)
#define BT_RF_RESV_NA_BT_RF_68_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_68_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_68_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_68         BT_RF_RESV_NA_BT_RF_68_MSK
#define BT_RF_RESV_NA_BT_RF_68_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_68_POS)


//bt_rf_69 offsetaddress : 0x120
//bt_rf_69 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_0 BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_0_POS)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_1 BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_1_POS)
#define BT_RF_RESV_NA_BT_RF_69_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_69_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_69_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_69         BT_RF_RESV_NA_BT_RF_69_MSK
#define BT_RF_RESV_NA_BT_RF_69_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_69_POS)


//bt_rf_70 offsetaddress : 0x124
//bt_rf_70 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_2 BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_2_POS)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_3 BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_3_POS)
#define BT_RF_RESV_NA_BT_RF_70_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_70_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_70_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_70         BT_RF_RESV_NA_BT_RF_70_MSK
#define BT_RF_RESV_NA_BT_RF_70_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_70_POS)


//bt_rf_71 offsetaddress : 0x128
//bt_rf_71 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_4 BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_4_POS)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_5 BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_5_POS)
#define BT_RF_RESV_NA_BT_RF_71_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_71_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_71_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_71         BT_RF_RESV_NA_BT_RF_71_MSK
#define BT_RF_RESV_NA_BT_RF_71_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_71_POS)


//bt_rf_72 offsetaddress : 0x12c
//bt_rf_72 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_6 BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_6_POS)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_7 BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_MSK
#define BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_2M_VAL_7_POS)
#define BT_RF_RESV_NA_BT_RF_72_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_72_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_72_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_72         BT_RF_RESV_NA_BT_RF_72_MSK
#define BT_RF_RESV_NA_BT_RF_72_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_72_POS)


//bt_rf_73 offsetaddress : 0x130
//bt_rf_73 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_0 BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_0_POS)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_1 BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_1_POS)
#define BT_RF_RESV_NA_BT_RF_73_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_73_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_73_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_73         BT_RF_RESV_NA_BT_RF_73_MSK
#define BT_RF_RESV_NA_BT_RF_73_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_73_POS)


//bt_rf_74 offsetaddress : 0x134
//bt_rf_74 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_2 BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_2_POS)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_3 BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_3_POS)
#define BT_RF_RESV_NA_BT_RF_74_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_74_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_74_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_74         BT_RF_RESV_NA_BT_RF_74_MSK
#define BT_RF_RESV_NA_BT_RF_74_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_74_POS)


//bt_rf_75 offsetaddress : 0x138
//bt_rf_75 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_4 BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_4_POS)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_5 BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_5_POS)
#define BT_RF_RESV_NA_BT_RF_75_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_75_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_75_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_75         BT_RF_RESV_NA_BT_RF_75_MSK
#define BT_RF_RESV_NA_BT_RF_75_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_75_POS)


//bt_rf_76 offsetaddress : 0x13c
//bt_rf_76 RegResetValue : 0xNone
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_POS (0U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_6 BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_6_POS)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_POS (11U)
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_MSK (0x7ffUL << BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_POS)/*!< */
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_7 BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_MSK
#define BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_W(X) ((X) << BT_RF_TPCAL_GAIN_CODE_BR_VAL_7_POS)
#define BT_RF_RESV_NA_BT_RF_76_POS     (22U)
#define BT_RF_RESV_NA_BT_RF_76_MSK     (0x3ffUL << BT_RF_RESV_NA_BT_RF_76_POS)/*!< n/a*/
#define BT_RF_RESV_NA_BT_RF_76         BT_RF_RESV_NA_BT_RF_76_MSK
#define BT_RF_RESV_NA_BT_RF_76_W(X)    ((X) << BT_RF_RESV_NA_BT_RF_76_POS)


typedef struct {
  DRV_IOM uint32_t bt_rf_0                                 ;//offsetaddress : 0x00
  DRV_IOM uint32_t bt_rf_1                                 ;//offsetaddress : 0x04
  DRV_IOM uint32_t bt_rf_2                                 ;//offsetaddress : 0x08
  DRV_IOM uint32_t bt_rf_3                                 ;//offsetaddress : 0x0c
  DRV_IOM uint32_t bt_rf_4                                 ;//offsetaddress : 0x10
  DRV_IOM uint32_t bt_rf_5                                 ;//offsetaddress : 0x14
  DRV_IOM uint32_t bt_rf_6                                 ;//offsetaddress : 0x18
  DRV_IOM uint32_t bt_rf_7                                 ;//offsetaddress : 0x1c
  DRV_IOM uint32_t bt_rf_8                                 ;//offsetaddress : 0x20
  DRV_IOM uint32_t bt_rf_9                                 ;//offsetaddress : 0x24
  DRV_IOM uint32_t bt_rf_10                                ;//offsetaddress : 0x28
  DRV_IOM uint32_t bt_rf_11                                ;//offsetaddress : 0x2c
  DRV_IOM uint32_t bt_rf_12                                ;//offsetaddress : 0x30
  DRV_IOM uint32_t bt_rf_13                                ;//offsetaddress :  0x34
  DRV_IOM uint32_t bt_rf_14                                ;//offsetaddress : 0x38
  DRV_IOM uint32_t bt_rf_15                                ;//offsetaddress : 0x3c
  DRV_IOM uint32_t bt_rf_16                                ;//offsetaddress : 0x40
  DRV_IOM uint32_t bt_rf_17                                ;//offsetaddress : 0x44
  DRV_IOM uint32_t bt_rf_18                                ;//offsetaddress : 0x48
  DRV_IOM uint32_t bt_rf_19                                ;//offsetaddress : 0x4c
  DRV_IOM uint32_t bt_rf_20                                ;//offsetaddress : 0x50
  DRV_IOM uint32_t bt_rf_21                                ;//offsetaddress : 0x54
  DRV_IOM uint32_t bt_rf_22                                ;//offsetaddress : 0x58
  DRV_IOM uint32_t bt_rf_23                                ;//offsetaddress : 0x5c
  DRV_IOM uint32_t bt_rf_24                                ;//offsetaddress : 0x60
  DRV_IOM uint32_t bt_rf_25                                ;//offsetaddress : 0x64
  DRV_IOM uint32_t bt_rf_26                                ;//offsetaddress : 0x68
  DRV_IOM uint32_t bt_rf_27                                ;//offsetaddress : 0x6c
  DRV_IOM uint32_t bt_rf_28                                ;//offsetaddress : 0x70
  DRV_IOM uint32_t bt_rf_29                                ;//offsetaddress : 0x74
  DRV_IOM uint32_t bt_rf_30                                ;//offsetaddress : 0x78
  DRV_IOM uint32_t bt_rf_31                                ;//offsetaddress : 0x7c
  DRV_IOM uint32_t bt_rf_32                                ;//offsetaddress : 0x80
  DRV_IOM uint32_t bt_rf_33                                ;//offsetaddress : 0x84
  DRV_IOM uint32_t bt_rf_34                                ;//offsetaddress : 0x88
  DRV_IOM uint32_t bt_rf_35                                ;//offsetaddress : 0x8c
  DRV_IOM uint32_t bt_rf_36                                ;//offsetaddress : 0x90
  DRV_IOM uint32_t bt_rf_37                                ;//offsetaddress : 0x94
  DRV_IOM uint32_t bt_rf_38                                ;//offsetaddress : 0x98
  DRV_IOM uint32_t bt_rf_39                                ;//offsetaddress : 0x9c
  DRV_IOM uint32_t bt_rf_40                                ;//offsetaddress : 0xa0
  DRV_IOM uint32_t bt_rf_41                                ;//offsetaddress : 0xa4
  DRV_IOM uint32_t bt_rf_42                                ;//offsetaddress : 0xa8
  DRV_IOM uint32_t bt_rf_43                                ;//offsetaddress : 0xac
  DRV_IOM uint32_t bt_rf_44                                ;//offsetaddress : 0xb0
  DRV_IOM uint32_t bt_rf_45                                ;//offsetaddress : 0xb4
  DRV_IOM uint32_t bt_rf_46                                ;//offsetaddress : 0xb8
  DRV_IOM uint32_t bt_rf_47                                ;//offsetaddress : 0xbc
  DRV_IOM uint32_t bt_rf_48                                ;//offsetaddress : 0xc0
  DRV_IOM uint32_t bt_rf_49                                ;//offsetaddress : 0xc4
  DRV_IOM uint32_t bt_rf_50                                ;//offsetaddress : 0xc8
  DRV_IOM uint32_t bt_rf_51                                ;//offsetaddress : 0xcc
  DRV_IOM uint32_t bt_rf_52                                ;//offsetaddress : 0xd0
  DRV_IOM uint32_t bt_rf_53                                ;//offsetaddress : 0xd4
  DRV_IOM uint32_t bt_rf_54                                ;//offsetaddress : 0xd8
  DRV_IOM uint32_t bt_rf_55                                ;//offsetaddress : 0xdc
  DRV_IOM uint32_t bt_rf_56                                ;//offsetaddress : 0xe0
  DRV_IOM uint32_t bt_rf_57                                ;//offsetaddress : 0xe4
  DRV_IOM uint32_t bt_rf_58                                ;//offsetaddress : 0xe8
  DRV_IOM uint32_t rev_0[(0xf4 - 0xe8) / 4 - 1];
  DRV_IOM uint32_t bt_rf_59                                ;//offsetaddress : 0xf4
  DRV_IOM uint32_t bt_rf_60                                ;//offsetaddress : 0xf8
  DRV_IOM uint32_t bt_rf_61                                ;//offsetaddress : 0xfc
  DRV_IOM uint32_t bt_rf_62                                ;//offsetaddress : 0x100
  DRV_IOM uint32_t bt_rf_63                                ;//offsetaddress : 0x104
  DRV_IOM uint32_t bt_rf_64                                ;//offsetaddress : 0x108
  DRV_IOM uint32_t rev_1[(0x110 - 0x108) / 4 - 1];
  DRV_IOM uint32_t bt_rf_65                                ;//offsetaddress : 0x110
  DRV_IOM uint32_t bt_rf_66                                ;//offsetaddress : 0x114
  DRV_IOM uint32_t bt_rf_67                                ;//offsetaddress : 0x118
  DRV_IOM uint32_t bt_rf_68                                ;//offsetaddress : 0x11c
  DRV_IOM uint32_t bt_rf_69                                ;//offsetaddress : 0x120
  DRV_IOM uint32_t bt_rf_70                                ;//offsetaddress : 0x124
  DRV_IOM uint32_t bt_rf_71                                ;//offsetaddress : 0x128
  DRV_IOM uint32_t bt_rf_72                                ;//offsetaddress : 0x12c
  DRV_IOM uint32_t bt_rf_73                                ;//offsetaddress : 0x130
  DRV_IOM uint32_t bt_rf_74                                ;//offsetaddress : 0x134
  DRV_IOM uint32_t bt_rf_75                                ;//offsetaddress : 0x138
  DRV_IOM uint32_t bt_rf_76                                ;//offsetaddress : 0x13c
} bt_rf_reg_t ;
#ifdef __cplusplus
}
#endif
#endif
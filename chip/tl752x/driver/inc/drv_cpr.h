/*******************************************************************************************************
 *
 * @file    drv_cpr.h
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
#ifndef __DRV_CPR_H__
#define __DRV_CPR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"

typedef struct {
    uint32_t hse_enable;
    uint32_t bbpll_enable;
    uint32_t fracpll_enable;
    uint32_t fracpll_freq;
} cpr_OSC_init_t;

typedef enum {
    CPR_DBG_CLK_SRC_MCLK0_G = 0,
    CPR_DBG_CLK_SRC_RC32K = 1,
    CPR_DBG_CLK_SRC_CODEC_6P144 = 2,
    CPR_DBG_CLK_SRC_USB_PLL_120M = 3,
} cpr_dbg_clk_src_t;

typedef struct {
    uint16_t series;
    uint8_t version;
} cpr_chip_info_t;

#include "modules/drv_cpr_ex.h"

#define __DRV_CPR_TRNG_CLK_ENABLE()                                     \
    do {                                                                \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_OSR_TRNG); \
        SET_PROTECT_BIT(CPR->CLK_EN_MCU_SYSTEM, CPR_OSR_TRNG_CLK_EN);   \
    } while (0U)

#define __DRV_CPR_TRNG_CLK_DISABLE()                                      \
    do {                                                                  \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_OSR_TRNG); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_MCU_SYSTEM, CPR_OSR_TRNG_CLK_EN);   \
    } while (0U)


/********************************** DWC SSI CFG **********************************/
#define __DRV_CPR_DWC_SSI0_CLOCK_ENABLE()                                                      \
    do {                                                                                       \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DWC_SSI_0_MSK);                           \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_DWC_SSI_0_H_MSK);                 \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_DWC_SSI0_PHY_MSK);                \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_DWC_SSI0_HCLK_EN_MSK | CPR_DWC_SSI0_MCLK_EN_MSK); \
    } while (0)

#define __DRV_CPR_DWC_SSI0_CLOCK_DISABLE()                                                       \
    do {                                                                                         \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_DWC_SSI0_HCLK_EN_MSK | CPR_DWC_SSI0_MCLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_DWC_SSI_0_H_MSK);                 \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_DWC_SSI0_PHY_MSK);                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DWC_SSI_0_MSK);                           \
    } while (0)

#define __DRV_CPR_DWC_SSI0_CLOCK_DIV(__DWC_SSI0_DIV__) MODIFY_REG(CPR->CLK_DIV_FUNC0, CPR_DWC_SSI0_M_DIV_VAL_MSK, __DWC_SSI0_DIV__ << CPR_DWC_SSI0_M_DIV_VAL_POS)
#define __DRV_CPR_DWC_SSI0_GET_CLOCK_DIV()             (READ_BIT(CPR->CLK_DIV_FUNC0, CPR_DWC_SSI0_M_DIV_VAL_MSK) >> CPR_DWC_SSI0_M_DIV_VAL_POS)

#define __DRV_CPR_DWC_SSI1_CLOCK_ENABLE()                                                      \
    do {                                                                                       \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_DWC_SSI_1_H_MSK);                 \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_DWC_SSI1_PHY_MSK);                \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_DWC_SSI1_HCLK_EN_MSK | CPR_DWC_SSI1_MCLK_EN_MSK); \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DWC_SSI_1_MSK);                           \
    } while (0)

#define __DRV_CPR_DWC_SSI1_CLOCK_DISABLE()                                                       \
    do {                                                                                         \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_DWC_SSI1_HCLK_EN_MSK | CPR_DWC_SSI1_MCLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_DWC_SSI_1_H_MSK);                 \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_DWC_SSI1_PHY_MSK);                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DWC_SSI_1_MSK);                           \
    } while (0)

#define __DRV_CPR_DWC_SSI1_CLOCK_DIV(__DWC_SSI1_DIV__) MODIFY_REG(CPR->CLK_DIV_FUNC0, CPR_DWC_SSI1_M_DIV_VAL_MSK, __DWC_SSI1_DIV__ << CPR_DWC_SSI1_M_DIV_VAL_POS)
#define __DRV_CPR_DWC_SSI1_GET_CLOCK_DIV()             (READ_BIT(CPR->CLK_DIV_FUNC0, CPR_DWC_SSI1_M_DIV_VAL_MSK) >> CPR_DWC_SSI1_M_DIV_VAL_POS)


extern drv_status_t drv_cpr_osc_init(cpr_OSC_init_t *osc_init);
extern drv_status_t drv_cpr_config_mclk0(cpr_mclk0_init_t *mclk0_init);
extern void drv_cpr_dbg_config(cpr_dbg_clk_src_t src, uint32_t div);
extern uint32_t drv_cpr_get_sdmmc_freq(void);
extern void drv_cpr_system_soft_reset(void);

extern void drv_cpr_get_chip_info(cpr_chip_info_t *info);

#ifdef __cplusplus
}
#endif

#endif

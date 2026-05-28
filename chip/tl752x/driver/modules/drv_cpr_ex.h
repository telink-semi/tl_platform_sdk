/*******************************************************************************************************
 *
 * @file    drv_cpr_ex.h
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
#ifndef __DRV_CPR_EX_H__
#define __DRV_CPR_EX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"
#include "modules/cpr.h"
/**
 * @brief  CPR BB PLL configuration structure definition
 */
typedef struct {
    uint32_t state; /*!< The new state of the PLL.*/
} cpr_bb_pll_init_t;

/**
 * @brief  CPR FRAC PLL configuration structure definition
 */
typedef struct {
    uint32_t state; /*!< The new state of the PLL.*/
    uint32_t freq;  /*he target frequency that needs to be set.
                        This frequency needs to be between FRAC_PLL_MIN_FREQ and FRAC_PLL_MAX_FREQ*/
} cpr_frac_pll_init_t;

/**
 * @brief  CPR Internal/External Oscillator (HSE, HSI, LSI and PLL) configuration structure definition
 */
typedef struct {
    uint32_t source; /*This parameter can be a value of @ref drv_cpr_mclk0_Source_Status*/
    uint32_t freq;
    uint32_t double_clock_sel; /*only valid when the source is selected as double clock
                                    This parameter can be a value of @ref drv_cpr_double_clock_sel_status*/
    uint32_t pll_sel;          /*divided bbpll or frac pll used as mclk0 clock
                                This parameter can be a value of @ref drv_cpr_mclk0_pll_sel_status*/
    cpr_bb_pll_init_t pll;
} cpr_mclk0_init_t;

/**
 * @brief  CPR Internal/External Oscillator (PLL) configuration structure definition
 */
typedef struct {
    uint32_t source; /*This parameter can be a value of @ref drv_cpr_mclk1_Source_Status*/
    uint32_t freq;
    cpr_bb_pll_init_t pll;
} cpr_mclk1_init_t;

/**
 * @brief  CPU clk configuration structure definition
 */
typedef struct {
    uint32_t cpu0_freq;
    uint32_t cpu1_freq;
    uint32_t cpu2_freq;
} cpr_cpu_freq_init_t;

/* ########################## Oscillator Values adaptation ####################*/
/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the CPR HAL module to compute the system frequency
  *        (when HSI is used as system clock source).
  */
#if !defined(HSI_VALUE)
#define HSI_VALUE (48000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif                         /* HSI_VALUE */

/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the CPR HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined(HSE_VALUE)
#define HSE_VALUE (24000000UL) /*!< Value of the External oscillator in Hz */
#endif                         /* HSE_VALUE */

#define HSE_OFF 0x0U
#define HSE_ON  0x1U
/**
  * @brief Adjust the value of double clock used in your application.
  *        This value is used by the CPR HAL module to compute the system frequency
  */
#if !defined(DOUBLE_CLOCK_ORIGINAL_VALUE)
#define DOUBLE_CLOCK_ORIGINAL_VALUE (48000000UL)
#endif
#if !defined(DOUBLE_CLOCK_DIVIDED_VALUE)
#define DOUBLE_CLOCK_DIVIDED_VALUE (32000000UL)
#endif

#if !defined(BBPLL_OUTPUT_CLOCK)
#define BBPLL_OUTPUT_CLOCK (768000000UL)
#endif

#if !defined(FRAC_PLL_MIN_FREQ)
#define FRAC_PLL_MIN_FREQ (150000000UL)
#endif

#if !defined(FRAC_PLL_MAX_FREQ)
#define FRAC_PLL_MAX_FREQ (300000000UL)
#endif
#if !defined(FRAC_PLL_DEFAULT_FREQ)
#define FRAC_PLL_DEFAULT_FREQ (168000000UL)
#endif

#if !defined(CLOCK_IN0_FREQ)
#define CLOCK_IN0_FREQ (48000000UL) /*external clock in */
#endif

#if !defined(FRACPLL_OUT_FREQ)
#define FRACPLL_OUT_FREQ (196608000) /*external clock in */
#endif

/** @defgroup CPR_MCLK0_TYPE Oscillator Type
 * @{
 */

/** @defgroup drv_cpr_mclk0_Source_Status mclk0 Clock Source Status
 * @{
 */
#define DRV_CPR_MCLK0_SOURCE_DIVIDED_PLL (0x0 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_HFRCO       (0x1 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_HFXO        (0x2 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_DOUBLE      (0x3 << CPR_MCLK0_SEL_POS)

/** @defgroup drv_cpr_mclk1_Source_Status mclk1 Clock Source Status
 * @{
 */
#define DRV_CPR_MCLK1_SOURCE_CLKIN0       (0x0 << CPR_MCLK1_SEL_POS)
#define DRV_CPR_MCLK1_SOURCE_CLKIN1       (0x1 << CPR_MCLK1_SEL_POS)
#define DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL0 (0x2 << CPR_MCLK1_SEL_POS)
#define DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL1 (0x3 << CPR_MCLK1_SEL_POS)

/** @defgroup drv_cpr_cpu2_Source_Status cpu2 Clock Source Status
 * @{
 */
#define DRV_CPR_CPU2_SOURCE_MCLK0 (0x0 << CPR_CPU2_CLK_SEL_POS)
#define DRV_CPR_CPU2_SOURCE_CPU0  (0x1 << CPR_CPU2_CLK_SEL_POS)
#define DRV_CPR_CPU2_SOURCE_CPU1  (0x2 << CPR_CPU2_CLK_SEL_POS)
#define DRV_CPR_CPU2_SOURCE_AHB   (0x3 << CPR_CPU2_CLK_SEL_POS)

/**
 * @}
 */

/** @defgroup drv_cpr_double_clock_sel_status double clock sel
 * @{
 */
#define DRV_CPR_MCLK0_DBLR_SET_ORIGINAL (0x0 << CPR_MCLK0_DBLR_SEL_POS) /*double clock is 48MHz*/
#define DRV_CPR_MCLK0_DBLR_SET_DIVIDED  (0x1 << CPR_MCLK0_DBLR_SEL_POS) /*double clock is 32MHz*/
/**
 * @}
 */

/** @defgroup drv_cpr_mclk0_pll_sel_status mclk0 pll sel
 * @{
 */
#define DRV_CPR_MCLK0_PLL_SEL_BBPLL   (0x0 << CPR_MCLK0_PLL_SEL_POS) /*divided BBPLL used as mclk0 */
#define DRV_CPR_MCLK0_PLL_SEL_FRACPLL (0x1 << CPR_MCLK0_PLL_SEL_POS) /*divided FRACPLL used as mclk0 */
                                                                     /**
 * @}
 */

/***********************************CLOCK************************************* */

/** @brief  Macro to get the clock source used as  MCLK0.
 * @retval The clock source used as  MCLK0  clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_MCLK0_SOURCE_DIVIDED_PLL: DIVIDED pll  used as MCLK0 clock.
 *              - DRV_CPR_MCLK0_SOURCE_HFRCO: HSI  used as MCLK0 clock.
 *              - DRV_CPR_MCLK0_SOURCE_HFXO: HSE used as MCLK0 clock.
 *              - DRV_CPR_MCLK0_SOURCE_DOUBLE double clock (original 48M or divided to 32M) as MCLK0 CLOCK
 */
#define __DRV_CPR_GET_MCLK0_SOURCE() READ_BIT(CPR->CLK_SET, CPR_MCLK0_SEL)

/** @brief  Macro to get the clock source used as  MCLK1.
 * @retval The clock source used as  MCLK1  clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_MCLK1_SOURCE_CLKIN0: DIVIDED pll  used as MCLK0 clock.
 *              - DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL0: DIVIDED pll0  used as MCLK1 clock.
 *              - DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL1: DIVIDED pll1  used as MCLK1 clock.
 */
#define __DRV_CPR_GET_MCLK1_SOURCE() READ_BIT(CPR->CLK_MUX, CPR_MCLK1_SEL)

#define __DRV_CPR_SET_MCLK0_SOURCE(__MCLK0_SOURCE__) MODIFY_REG(CPR->CLK_SET, CPR_MCLK0_SEL_MSK, __MCLK0_SOURCE__)
#define __DRV_CPR_SET_MCLK1_SOURCE(__MCLK1_SOURCE__) MODIFY_REG(CPR->CLK_MUX, CPR_MCLK1_SEL_MSK, __MCLK1_SOURCE__)

/** @brief  Macro to get the double sel  used for  MCLK0.
 * @retval The double sel  used for  MCLK0  clock. The returned value can be one
 *         of the following:
 *              - 0:    48M clock as double clock
 *              - 1:    32M clock as double clock
 */
#define __DRV_CPR_GET_MCLK0_DOUBLE_SEL() READ_BIT(CPR->CLK_SET, CPR_MCLK0_DBLR_SEL)

#define __DRV_CPR_SET_MCLK0_DOUBLE_SEL(__DBLR_SEL__) MODIFY_REG(CPR->CLK_SET, CPR_MCLK0_DBLR_SEL, __DBLR_SEL__)

/** @brief  Macro to get the PLL SEL  used for  MCLK0 pll.
 * @retval The PLL sel  used for  MCLK0  PLL. The returned value can be one
 *         of the following:
 *              - 0:    BBPLL
 *              - 1:    FRAC PLL
 */
#define __DRV_CPR_GET_MCLK0_PLL_SEL() READ_BIT(CPR->CLK_SET, CPR_MCLK0_PLL_SEL)

#define __DRV_CPR_SET_MCLK0_PLL_SEL(__MCLK0_PLL_SEL__) MODIFY_REG(CPR->CLK_SET, CPR_MCLK0_PLL_SEL, __MCLK0_PLL_SEL__)

#define __DRV_CPR_GET_PLL_MCLK0_DIV() READ_BIT(CPR->CLK_DIV_PLL, CPR_PLL_SYS_DIV_VAL)

#define __DRV_CPR_SET_PLL_MCLK0_DIV(__PLL_MCLK0_DIV__) MODIFY_REG(CPR->CLK_DIV_PLL, CPR_PLL_SYS_DIV_VAL, __PLL_MCLK0_DIV__)

#define __DRV_CPR_GET_PLL_MCLK1_DIV() READ_BIT(CPR->CLK_DIV_PLL, CPR_PLL_AUDIO_DIV_VAL)

#define __DRV_CPR_SET_PLL_MCLK1_DIV(__PLL_MCLK1_DIV__) MODIFY_REG(CPR->CLK_DIV_PLL, CPR_PLL_AUDIO_DIV_VAL, __PLL_MCLK1_DIV__)

#define __DRV_CPR_GET_FRAC_PLL_FD() READ_BIT(CPR->FRAC_PLL, CPR_FRAC_PLL_DIVF_FRAC)

#define __DRV_CPR_GET_FRAC_PLL_FN() READ_BIT(CPR->FRAC_PLL, CPR_FRAC_PLL_DIVF_INTG)

#define __DRV_CPR_BBPLL_IS_LOCKED()   (READ_BIT(CPR->PLL_STAT, CPR_BBPLL_LOCK_FLAG) != 0)
#define __DRV_CPR_BBPLL_IS_UNLOCKED() (READ_BIT(CPR->PLL_STAT, CPR_BBPLL_LOCK_FLAG) == 0)

#define __DRV_CPR_FRACPLL_IS_LOCKED()   (READ_BIT(CPR->PLL_STAT, CPR_FRAC_PLL_LD) != 0)
#define __DRV_CPR_FRACPLL_IS_UNLOCKED() (READ_BIT(CPR->PLL_STAT, CPR_FRAC_PLL_LD) == 0)

#define __DRV_CPR_SET_AHB_DIV(val) MODIFY_REG(CPR->CLK_DIV_BUS, CPR_AHB_DIV_VAL, CPR_AHB_DIV_VAL_W(val))

#define __DRV_CPR_GET_MCLK0_DIV()    READ_BIT(CPR->CLK_DIV_BUS, CPR_MCLK0_G_DIV_VAL)
#define __DRV_CPR_GET_CPU0_CLK_DIV() READ_BIT(CPR->CLK_DIV_CPU, CPR_CPU0_SYSTEM_CLK_DIV_VAL)
#define __DRV_CPR_GET_CPU1_CLK_DIV() READ_BIT(CPR->CLK_DIV_CPU, CPR_CPU1_SYSTEM_CLK_DIV_VAL)
#define __DRV_CPR_GET_AHB_DIV()      READ_BIT(CPR->CLK_DIV_BUS, CPR_AHB_DIV_VAL)

/** @brief  Macro to get the clock source used as cpu2 clk.
 * @retval The clock source used as  cpu2  clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_CPU2_SOURCE_MCLK0: DIVIDED mclk0 used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_CPU0: cpu0 clk  used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_CPU1: cpu1 clk  used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_AHB: AHB clk used as cpu2 clock.
 */
#define __DRV_CPR_GET_CPU2_SOURCE() READ_BIT(CPR->CLK_MUX, CPR_CPU2_CLK_SEL)
/** @brief  Macro to set the clock source used as cpu2 clk.
 * @retval The clock source used as  cpu2  clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_CPU2_SOURCE_MCLK0: DIVIDED mclk0 used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_CPU0: cpu0 clk  used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_CPU1: cpu1 clk  used as cpu2 clock.
 *              - DRV_CPR_CPU2_SOURCE_AHB: AHB clk used as cpu2 clock.
 */
#define __DRV_CPR_SET_CPU2_SOURCE(__CPU2_SOURCE__) MODIFY_REG(CPR->CLK_MUX, CPR_CPU2_CLK_SEL, __CPU2_SOURCE__)

extern drv_status_t drv_cpr_set_cpu_freq(cpr_cpu_freq_init_t *cpu_freq);

/********************************** SYSTEM **********************************/
//cfg_ahb_bus_clk_en,sys_ctl_clk_en,aon_apb_hclk_en,pmu_pclk_en
#define __DRV_CPR_SYSTEM_CLK_ENABLE()                                                  \
    do {                                                                               \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_CFG_AHB_BUS_CLK_EN | CPR_SYS_CTL_CLK_EN); \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_AON_APB_HCLK_EN | CPR_PMU_PCLK_EN | CPR_RTC_PCLK_EN);      \
    } while (0U)
/********************************** SYSTIMER **********************************/
#define __DRV_CPR_SYSTIEMR_CLK_ENABLE()                                                     \
    do {                                                                                    \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_SYSTIMER_P);                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_SYSTIMER);                             \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_SYSTIMER_PCLK_EN | CPR_SYSTIMER_CLK_EN); \
    } while (0U)

#define __DRV_CPR_SYSTIEMR_CLK_DISABLE()                                                      \
    do {                                                                                      \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_SYSTIMER_P);                        \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_SYSTIMER);                             \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_SYSTIMER_PCLK_EN | CPR_SYSTIMER_CLK_EN); \
    } while (0U)
/********************************** TIMER **********************************/
#define __DRV_CPR_TIMER0_3_PCLK_ENABLE()                          \
    do {                                                          \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_TIMER_P); \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_PCLK_EN);     \
    } while (0U)

#define __DRV_CPR_TIMER0_3_PCLK_DISABLE()                           \
    do {                                                            \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_TIMER_P); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_PCLK_EN);     \
    } while (0U)

#define __DRV_CPR_TIMER4_7_PCLK_ENABLE()                           \
    do {                                                           \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_TIMER1_P); \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_PCLK_EN);     \
    } while (0U)

#define __DRV_CPR_TIMER4_7_PCLK_DISABLE()                            \
    do {                                                             \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_TIMER1_P); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_PCLK_EN);     \
    } while (0U)

#define __DRV_CPR_TIMER0_CLK_ENABLE()                           \
    do {                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER1);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_1_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER0_CLK_DISABLE()                            \
    do {                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER1);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_1_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TIMER1_CLK_ENABLE()                           \
    do {                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER2);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_2_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER1_CLK_DISABLE()                            \
    do {                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER2);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_2_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TIMER2_CLK_ENABLE()                           \
    do {                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER3);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_3_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER2_CLK_DISABLE()                            \
    do {                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER3);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_3_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TIMER3_CLK_ENABLE()                           \
    do {                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER4);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_4_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER3_CLK_DISABLE()                            \
    do {                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_TIMER4);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER_4_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TIMER4_CLK_ENABLE()                            \
    do {                                                         \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_1);  \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_1_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER4_CLK_DISABLE()                             \
    do {                                                           \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_1);  \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_1_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER5_CLK_ENABLE()                            \
    do {                                                         \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_2);  \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_2_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER5_CLK_DISABLE()                             \
    do {                                                           \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_2);  \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_2_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER6_CLK_ENABLE()                            \
    do {                                                         \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_3);  \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_3_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER6_CLK_DISABLE()                             \
    do {                                                           \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_3);  \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_3_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER7_CLK_ENABLE()                            \
    do {                                                         \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_4);  \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_4_MCLK_EN); \
    } while (0U)
#define __DRV_CPR_TIMER7_CLK_DISABLE()                             \
    do {                                                           \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_TIMER1_4);  \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_TIMER1_4_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TIMER0_CLK_SOURCR(SOURCE)                \
    do {                                                   \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER_1_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER_1_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER1_CLK_SOURCR(SOURCE)                \
    do {                                                   \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER_2_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER_2_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER2_CLK_SOURCR(SOURCE)                \
    do {                                                   \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER_3_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER_3_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER3_CLK_SOURCR(SOURCE)                \
    do {                                                   \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER_4_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER_4_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER4_CLK_SOURCR(SOURCE)                 \
    do {                                                    \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER1_1_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER1_1_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER5_CLK_SOURCR(SOURCE)                 \
    do {                                                    \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER1_2_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER1_2_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER6_CLK_SOURCR(SOURCE)                 \
    do {                                                    \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER1_3_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER1_4_SEL_W(SOURCE)); \
    } while (0U)
#define __DRV_CPR_TIMER7_CLK_SOURCR(SOURCE)                 \
    do {                                                    \
        CLEAR_BIT(CPR->CLK_MUX1, CPR_TIMER1_4_SEL);         \
        SET_BIT(CPR->CLK_MUX1, CPR_TIMER1_4_SEL_W(SOURCE)); \
    } while (0U)
/********************************** I2C **********************************/
#define __DRV_CPR_I2C0_CLK_ENABLE()                                           \
    do {                                                                      \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C);                    \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_I2C_MCLK_EN | CPR_I2C_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_I2C0_CLK_DISABLE()                                            \
    do {                                                                        \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C1_P);              \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C);                    \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_I2C_MCLK_EN | CPR_I2C_PCLK_EN); \
    } while (0U)
#define __DRV_CPR_I2C1_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C1_P);                \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C1);                     \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_I2C1_MCLK_EN | CPR_I2C1_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_I2C1_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C_P);                 \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C1);                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_I2C1_MCLK_EN | CPR_I2C1_PCLK_EN); \
    } while (0U)
#define __DRV_CPR_I2C2_CLK_ENABLE()                                                                    \
    do {                                                                                               \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C2_P);                                       \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C2);                                            \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_I2C2_MCLK_EN | CPR_I2C2_PCLK_EN | CPR_CPU1_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_I2C2_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_I2C2_P);                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_I2C2);                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_I2C2_MCLK_EN | CPR_I2C2_PCLK_EN); \
    } while (0U)
/********************************** BT CLOCK **********************************/
#define __DRV_CPR_BT_CLK_ENABLE()                                                                                                         \
    do {                                                                                                                                  \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_HCLK_EN | CPR_BT_SYS_CLK_EN | CPR_BT_RFDIG_CLK_EN);                             \
        SET_BIT(CPR->BT_CFG, CPR_BT_SYS_CPU_BT_GCLKEN | CPR_BT_SYS_CPU_BLE_GCLKEN | CPR_BT_SYS_CPU_DM_GCLKEN | CPR_BT_SYS_CPU_EM_GCLKEN); \
    } while (0U)

#define __DRV_CPR_BT_CLK_DISABLE()                                                                                                          \
    do {                                                                                                                                    \
        CLEAR_BIT(CPR->BT_CFG, CPR_BT_SYS_CPU_BT_GCLKEN | CPR_BT_SYS_CPU_BLE_GCLKEN | CPR_BT_SYS_CPU_DM_GCLKEN | CPR_BT_SYS_CPU_EM_GCLKEN); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_HCLK_EN | CPR_BT_SYS_CLK_EN | CPR_BT_RFDIG_CLK_EN);                             \
    } while (0U)

/********************************** RF CLOCK **********************************/
#define __DRV_CPR_RF_CLK_ENABLE()                                                         \
    do {                                                                                  \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_HCLK_EN | CPR_BT_RFDIG_CLK_EN); \
    } while (0U)

#define __DRV_CPR_RF_CLK_DISABLE()                                                          \
    do {                                                                                    \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_HCLK_EN | CPR_BT_RFDIG_CLK_EN); \
    } while (0U)

/********************************** RTC **********************************/
#define __DRV_CPR_RTC_CLK_ENABLE()                          \
    do {                                                    \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_RTC_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_RTC_CLK_DISABLE()                           \
    do {                                                      \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_RTC_PCLK_EN); \
    } while (0U)

/********************************** GPIO **********************************/
#define __DRV_CPR_GPIO_CLK_ENABLE()                                                          \
    do {                                                                                     \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_GPIO);                               \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_GPIO_PCLK_EN | CPR_GPIO_DEBOUNCE_CLK_EN); \
    } while (0U)

#define __DRV_CPR_GPIO_CLK_DISABLE()                                                           \
    do {                                                                                       \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_GPIO);                               \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_GPIO_PCLK_EN | CPR_GPIO_DEBOUNCE_CLK_EN); \
    } while (0U)

/**
  * @brief  gpioa input enable.
  * @param  pin specifies the port bit to be written.can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  en specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg DRV_RESET: to clear the port pin input disable
  *            @arg DRV_SET: to set the port pin input enable
  * @retval None
  */
extern void drv_cpr_gpio_porta_ie_cfg(uint32_t pin, drv_flag_status_t en);

/**
  * @brief  gpioc input enable.
  * @param  pin specifies the port bit to be written.can be GPIO_PIN_0 - GPIO_PIN_31.
  * @param  en specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg DRV_RESET: to clear the port pin input disable
  *            @arg DRV_SET: to set the port pin input enable
  * @retval None
  */
extern void drv_cpr_gpio_portc_ie_cfg(uint32_t pin, drv_flag_status_t en);

/**
  * @brief  gpioa pull up or down cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  pu_pd specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_NOPULL: gpio no pull
  *            @arg GPIO_PULLUP: gpio pull-up
  *            @arg GPIO_PULLDOWN: gpio pull-down
  * @retval None
  */
extern void drv_cpr_gpio_porta_pupd(uint32_t pin_num, uint32_t pu_pd);

/**
  * @brief  gpioc pull up or down cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  pu_pd specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_NOPULL: gpio no pull
  *            @arg GPIO_PULLUP: gpio pull-up
  *            @arg GPIO_PULLDOWN: gpio pull-down
  * @retval None
  */
extern void drv_cpr_gpio_portc_pupd(uint32_t pin_num, uint32_t pu_pd);

/**
  * @brief  gpioa output electric cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  electric specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_ELECTRIC_2MA: output electric 2mA
  *            @arg GPIO_ELECTRIC_4MA: output electric 4mA
  *            @arg GPIO_ELECTRIC_8MA: output electric 8mA
  *            @arg GPIO_ELECTRIC_12MA: output electric 12mA
  * @retval None
  */
extern void drv_cpr_gpio_porta_electric(uint32_t pin_num, uint32_t electric);

/**
  * @brief  gpioc output electric cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  electric specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_ELECTRIC_2MA: output electric 2mA
  *            @arg GPIO_ELECTRIC_4MA: output electric 4mA
  *            @arg GPIO_ELECTRIC_8MA: output electric 8mA
  *            @arg GPIO_ELECTRIC_12MA: output electric 12mA
  * @retval None
  */
extern void drv_cpr_gpio_portc_electric(uint32_t pin_num, uint32_t electric);

/**
  * @brief  gpioa pinmux cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  mux_val specifies the value to be written to the selected bit.
  *         can be GPIO_ALTERNATE_DEFAULT - GPIO_ALTERNATE_FUNC_15
  * @retval None
  */
extern void drv_cpr_gpio_porta_mux_ctl(uint32_t pin_num, uint32_t mux_val);

/**
  * @brief  gpiob pinmux cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  mux_val specifies the value to be written to the selected bit.
  *         can be GPIO_ALTERNATE_DEFAULT - GPIO_ALTERNATE_FUNC_15
  * @retval None
  */
extern void drv_cpr_gpio_portb_mux_ctl(uint32_t pin_num, uint32_t mux_val);

/**
  * @brief  gpioc pinmux cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  mux_val specifies the value to be written to the selected bit.
  *         can be GPIO_ALTERNATE_DEFAULT - GPIO_ALTERNATE_FUNC_15
  * @retval None
  */
extern void drv_cpr_gpio_portc_mux_ctl(uint32_t pin_num, uint32_t mux_val);
/**
 * @brief  gpioa interrupt enable
 * @param  pin_num specifies the port bit to be written.can be 0 - 31.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: to clear the port pin input disable
 *            @arg DRV_SET: to set the port pin input enable
 * @retval None
 */
extern void drv_cpr_gpio_porta_irq_set(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpioa debounce_clk_enable
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: to clear the port pin input disable
 *            @arg DRV_SET: to set the port pin input enable
 * @retval None
 */
void drv_cpr_gpio_porta_debounce_clk_enable(drv_flag_status_t en);
/**
 * @brief  gpioa interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 31.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: logic high level
 *            @arg DRV_SET: logic low level
 * @retval None
 */
extern void drv_cpr_gpio_porta_irq_type(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpioa interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 31.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: logic high level
 *            @arg DRV_SET: logic low level
 * @retval None
 */
extern void drv_cpr_gpio_porta_irq_debounce(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpioa interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 31.
 * @retval pa irq status
 */
extern uint32_t drv_cpr_gpio_porta_irq_read(void);
/**
 * @brief  gpioa interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 31.
 * @retval None
 */
extern void drv_cpr_gpio_porta_irq_clear(uint32_t pin_num);
/********************************** UART **********************************/
#define DRV_CPR_UART_MCLK_SRC_HFXO    0
#define DRV_CPR_UART_MCLK_SRC_DBLR    1
#define DRV_CPR_UART_MCLK_SRC_MUL_DIV 2

/** @brief  uart select mclk src.
 * @param  src specifies the src to select.
 *        This parameter can be one of the following values:
 *            @arg DRV_CPR_UART_MCLK_SRC_HFXO
 *            @arg DRV_CPR_UART_MCLK_SRC_DBLR
 *            @arg DRV_CPR_UART_MCLK_SRC_MUL_DIV
 */
#define __DRV_CPR_UART0_SELECT_MCLK_SRC(src)                                           \
    do {                                                                               \
        MODIFY_REG(CPR->CLK_MUX, CPR_UART_MCLK_SRC_SEL, CPR_UART_MCLK_SRC_SEL_W(src)); \
    } while (0)

#define __DRV_CPR_UART1_SELECT_MCLK_SRC(src)                                             \
    do {                                                                                 \
        MODIFY_REG(CPR->CLK_MUX, CPR_UART1_MCLK_SRC_SEL, CPR_UART1_MCLK_SRC_SEL_W(src)); \
    } while (0)

#define __DRV_CPR_UART2_SELECT_MCLK_SRC(src)                                             \
    do {                                                                                 \
        MODIFY_REG(CPR->CLK_MUX, CPR_UART2_MCLK_SRC_SEL, CPR_UART2_MCLK_SRC_SEL_W(src)); \
    } while (0)

#define __DRV_CPR_UART3_SELECT_MCLK_SRC(src)                                             \
    do {                                                                                 \
        MODIFY_REG(CPR->CLK_MUX, CPR_UART3_MCLK_SRC_SEL, CPR_UART3_MCLK_SRC_SEL_W(src)); \
    } while (0)

#define __DRV_CPR_UART4_SELECT_MCLK_SRC(src)                                             \
    do {                                                                                 \
        MODIFY_REG(CPR->CLK_MUX, CPR_UART4_MCLK_SRC_SEL, CPR_UART4_MCLK_SRC_SEL_W(src)); \
    } while (0)

#define __DRV_CPR_UART0_CLK_ENABLE()                                                                   \
    do {                                                                                               \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_UART_P);                                       \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_UART);                                            \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_UART_MCLK_EN | CPR_UART_PCLK_EN | CPR_CPU1_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART0_CLK_DISABLE()                                             \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_UART_P);                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_UART);                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_UART_MCLK_EN | CPR_UART_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART1_CLK_ENABLE()                                              \
    do {                                                                          \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_UART1_P);                 \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_UART1);                      \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART1_MCLK_EN | CPR_UART1_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART1_CLK_DISABLE()                                               \
    do {                                                                            \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_UART1_P);                 \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_UART1);                      \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART1_MCLK_EN | CPR_UART1_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART2_CLK_ENABLE()                                              \
    do {                                                                          \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART2 | CPR_RSTN_UART2_P);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART2_MCLK_EN | CPR_UART2_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART2_CLK_DISABLE()                                               \
    do {                                                                            \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART2 | CPR_RSTN_UART2_P);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART2_MCLK_EN | CPR_UART2_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART3_CLK_ENABLE()                                              \
    do {                                                                          \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART3 | CPR_RSTN_UART3_P);   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART3_MCLK_EN | CPR_UART3_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART3_CLK_DISABLE()                                               \
    do {                                                                            \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART3 | CPR_RSTN_UART3_P);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_UART3_MCLK_EN | CPR_UART3_PCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART4_CLK_ENABLE()                                                                     \
    do {                                                                                                 \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART4 | CPR_RSTN_UART4_P);                          \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_UART4_MCLK_EN | CPR_UART4_PCLK_EN | CPR_CPU1_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_UART4_CLK_DISABLE()                                               \
    do {                                                                            \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_UART4 | CPR_RSTN_UART4_P);   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_UART4_MCLK_EN | CPR_UART4_PCLK_EN); \
    } while (0U)

/** @brief  All UART common crossovers. Only the corresponding mclk0_g clock source is valid.
 *  @param  mul Frequency doubling factor. mul <= div
 *  @param  div Frequency division factor.
 */
#define __DRV_CPR_UARTX_CLK_SET_DIV(mul, div)                                                                       \
    do {                                                                                                            \
        MODIFY_REG(CPR->CLK_DIV_FUNC1, (CPR_UART_MUL | CPR_UART_DIV), (CPR_UART_MUL_W(mul) | CPR_UART_DIV_W(div))); \
    } while (0U)

/**
 * @brief  get uart frequency
 * @retval uart freq
 */
extern uint32_t drv_cpr_get_uart0_freq(void);
extern uint32_t drv_cpr_get_uart1_freq(void);
extern uint32_t drv_cpr_get_uart2_freq(void);
extern uint32_t drv_cpr_get_uart3_freq(void);
extern uint32_t drv_cpr_get_uart4_freq(void);

/********************************** MTIME **********************************/
#define __DRV_CPR_MCUA_MTIME_CLK_SRC_32K()               \
    do {                                                 \
        CLEAR_BIT(CPR->CLK_MUX, CPR_CPU0_MTIME_CLK_SEL); \
    } while (0U)

#define __DRV_CPR_MCUA_MTIME_CLK_SRC_HFXO_DIV()        \
    do {                                               \
        SET_BIT(CPR->CLK_MUX, CPR_CPU0_MTIME_CLK_SEL); \
    } while (0U)

#define __DRV_CPR_MCUA_MTIME_CLK_SET_HFXO_DIV(div)                                           \
    do {                                                                                     \
        MODIFY_REG(CPR->CLK_DIV_CPU, CPR_CPU0_MTIME_DIV_VAL, CPR_CPU0_MTIME_DIV_VAL_W(div)); \
    } while (0U)

#define __DRV_CPR_MCUB_MTIME_CLK_SRC_32K()               \
    do {                                                 \
        CLEAR_BIT(CPR->CLK_MUX, CPR_CPU1_MTIME_CLK_SEL); \
    } while (0U)

#define __DRV_CPR_MCUB_MTIME_CLK_SRC_HFXO_DIV()        \
    do {                                               \
        SET_BIT(CPR->CLK_MUX, CPR_CPU1_MTIME_CLK_SEL); \
    } while (0U)

#define __DRV_CPR_MCUB_MTIME_CLK_SET_HFXO_DIV(div)                                           \
    do {                                                                                     \
        MODIFY_REG(CPR->CLK_DIV_CPU, CPR_CPU1_MTIME_DIV_VAL, CPR_CPU1_MTIME_DIV_VAL_W(div)); \
    } while (0U)

/********************************** DMA **********************************/

/** @defgroup audio dma handshake select
 * @{
 */
#define DRV_CPR_CPU2_DMA_SEL0  (CPR_CPU2_DMA_SEL_0_POS)
#define DRV_CPR_CPU2_DMA_SEL1  (CPR_CPU2_DMA_SEL_1_POS)
#define DRV_CPR_CPU2_DMA_SEL2  (CPR_CPU2_DMA_SEL_2_POS)
#define DRV_CPR_CPU2_DMA_SEL3  (CPR_CPU2_DMA_SEL_3_POS)
#define DRV_CPR_CPU2_DMA_SEL4  (CPR_CPU2_DMA_SEL_4_POS)
#define DRV_CPR_CPU2_DMA_SEL5  (CPR_CPU2_DMA_SEL_5_POS)
#define DRV_CPR_CPU2_DMA_SEL6  (CPR_CPU2_DMA_SEL_6_POS)
#define DRV_CPR_CPU2_DMA_SEL7  (CPR_CPU2_DMA_SEL_7_POS)
#define DRV_CPR_CPU2_DMA_SEL8  (CPR_CPU2_DMA_SEL_8_POS)
#define DRV_CPR_CPU2_DMA_SEL9  (CPR_CPU2_DMA_SEL_9_POS)
#define DRV_CPR_CPU2_DMA_SEL10 (CPR_CPU2_DMA_SEL_10_POS)
#define DRV_CPR_CPU2_DMA_SEL11 (CPR_CPU2_DMA_SEL_11_POS)
#define DRV_CPR_CPU2_DMA_SEL12 (CPR_CPU2_DMA_SEL_12_POS)
#define DRV_CPR_CPU2_DMA_SEL13 (CPR_CPU2_DMA_SEL_13_POS)
#define DRV_CPR_CPU2_DMA_SEL14 (CPR_CPU2_DMA_SEL_14_POS)
#define DRV_CPR_CPU2_DMA_SEL15 (CPR_CPU2_DMA_SEL_15_POS)

/** @defgroup audio dma handshake select
 * @{
 */
#define DRV_CPR_SEL0_DUMP_ANC_REQ0        (0)
#define DRV_CPR_SEL0_CODEC_DMA_TX_REQ0    (1)
#define DRV_CPR_SEL1_DUMP_ANC_REQ1        (0)
#define DRV_CPR_SEL1_CODEC_DMA_TX_REQ1    (1)
#define DRV_CPR_SEL2_DUMP_ANC_REQ2        (0)
#define DRV_CPR_SEL2_CODEC_DMA_RX_REQ0    (1)
#define DRV_CPR_SEL3_DUMP_ANC_REQ3        (0)
#define DRV_CPR_SEL3_CODEC_DMA_RX_REQ1    (1)
#define DRV_CPR_SEL4_IIS0_DMA_TX_REQ      (0)
#define DRV_CPR_SEL4_IIS0_DMA_RX_REQ      (1)
#define DRV_CPR_SEL5_IIS1_DMA_TX_REQ      (0)
#define DRV_CPR_SEL5_IIS1_DMA_RX_REQ      (1)
#define DRV_CPR_SEL6_IIS2_DMA_TX_REQ      (0)
#define DRV_CPR_SEL6_IIS2_DMA_RX_REQ      (1)
#define DRV_CPR_SEL7_IIS3_DMA_TX_REQ      (0)
#define DRV_CPR_SEL7_IIS3_DMA_RX_REQ      (1)
#define DRV_CPR_SEL8_SPDIF_DMA_REQ        (0)
#define DRV_CPR_SEL8_IIS0_DMA_RX_REQ      (1)
#define DRV_CPR_SEL9_PDMC_DMA_TX_REQ      (0)
#define DRV_CPR_SEL9_IIS1_DMA_RX_REQ      (1)
#define DRV_CPR_SEL10_RESAMPLE_DMA_TX_REQ (0)
#define DRV_CPR_SEL10_IIS2_DMA_RX_REQ     (1)
#define DRV_CPR_SEL11_RESAMPLE_DMA_RX_REQ (0)
#define DRV_CPR_SEL11_IIS3_DMA_RX_REQ     (1)
#define DRV_CPR_SEL12_PDM0_DMA_REQ        (0)
#define DRV_CPR_SEL12_RESAMPLE_DMA_TX_REQ (1)
#define DRV_CPR_SEL13_PDM1_DMA_REQ        (0)
#define DRV_CPR_SEL13_RESAMPLE_DMA_RX_REQ (1)
#define DRV_CPR_SEL14_SPDIF_DMA_REQ       (0)
#define DRV_CPR_SEL14_PDM0_DMA_REQ        (1)
#define DRV_CPR_SEL15_PDMC_DMA_REQ        (0)
#define DRV_CPR_SEL15_PDM1_DMA_REQ        (1)

#define __DRV_CPR_SET_CPU2_DMA_HS_SEL(__CPU2_DMA_SEL__, __DMA_HS_SEL__) MODIFY_REG(CPR->DMA_CTRL, (0x1UL << __CPU2_DMA_SEL__), (__DMA_HS_SEL__ << __CPU2_DMA_SEL__))

#define __DRV_CPR_CPU_DMA_CLK_ENABLE()                                                        \
    do {                                                                                      \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU_DMA | CPR_RSTN_HWA_AHB_BUS); \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_CPU_DMA_HCLK_EN | CPR_HWA_AHB_BUS_CLK_EN);       \
    } while (0U)

#define __DRV_CPR_CPU_DMA_CLK_DISABLE()                                                         \
    do {                                                                                        \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU_DMA | CPR_RSTN_HWA_AHB_BUS); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_CPU_DMA_HCLK_EN | CPR_HWA_AHB_BUS_CLK_EN);       \
    } while (0U)

#define __DRV_CPR_AUDIO_DMA_CLK_ENABLE()                                                                            \
    do {                                                                                                            \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_HWA_AHB_BUS | CPR_RSTN_HWA2_AHB_BUS);                  \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_HWA_AHB_BUS_CLK_EN | CPR_HWA2_AHB_BUS_CLK_EN | CPR_AUDIO_DMA_HCLK_EN); \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_AUDIO_DMA);                                                \
    } while (0U)

#define __DRV_CPR_AUDIO_DMA_CLK_DISABLE()                                                                             \
    do {                                                                                                              \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_HWA_AHB_BUS | CPR_RSTN_HWA2_AHB_BUS);                  \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_AUDIO_DMA);                                                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_HWA_AHB_BUS_CLK_EN | CPR_HWA2_AHB_BUS_CLK_EN | CPR_AUDIO_DMA_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_CPU2_DMA_CLK_ENABLE()                                                         \
    do {                                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_CPU2_DMA | CPR_RSTN_AUDIO_BUS);        \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_AUDIO_BUS_CLK_EN | CPR_CPU2_DMA_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_CPU2_DMA_CLK_DISABLE()                                                          \
    do {                                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_CPU2_DMA | CPR_RSTN_AUDIO_BUS);        \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_AUDIO_BUS_CLK_EN | CPR_CPU2_DMA_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_CPU1_DMA_CLK_ENABLE()                                 \
    do {                                                                \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU1_DMA); \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_CPU1_DMA_HCLK_EN);   \
    } while (0U)

#define __DRV_CPR_CPU1_DMA_CLK_DISABLE()                                  \
    do {                                                                  \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU1_DMA); \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_CPU1_DMA_HCLK_EN);   \
    } while (0U)

/********************************** SDIO **********************************/
#define __DRV_CPR_SDMMC_CLK_ENABLE()                                                                                                                                \
    do {                                                                                                                                                            \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_HWA2_AHB_BUS);                                                                                         \
        SET_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_HWA2_AHB_BUS_CLK_EN);                                                                                                  \
        SET_BIT(CPR->SDMMC_CLK_CFG, CPR_SDMMC_HCLK_EN | CPR_SDMMC_MCLK_EN | CPR_SDMMC_TXCLK_EN | CPR_SDMMC_RXCLK_EN | CPR_RSTN_SOFT_SDMMC_H | CPR_RSTN_SOFT_SDMMC); \
    } while (0U)

#define __DRV_CPR_SDMMC_CLK_DISABLE()                                                                                                                                 \
    do {                                                                                                                                                              \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_HWA2_AHB_BUS);                                                                                         \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AHB, CPR_HWA2_AHB_BUS_CLK_EN);                                                                                                  \
        CLEAR_BIT(CPR->SDMMC_CLK_CFG, CPR_SDMMC_HCLK_EN | CPR_SDMMC_MCLK_EN | CPR_SDMMC_TXCLK_EN | CPR_SDMMC_RXCLK_EN | CPR_RSTN_SOFT_SDMMC_H | CPR_RSTN_SOFT_SDMMC); \
    } while (0U)

#define __DRV_CPR_SDMMC_CLK_SET_DIV(div)                                               \
    do {                                                                               \
        MODIFY_REG(CPR->SDMMC_CLK_CFG, CPR_SDMMC_MCLK_DIV, CPR_SDMMC_MCLK_DIV_W(div)); \
    } while (0U)

/********************************** MCLK1 **********************************/
#define __DRV_CPR_MCLK1_CLK_ENABLE()                             \
    do {                                                         \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_MCLK1_EN); \
    } while (0U)

#define __DRV_CPR_MCLK1_CLK_DISABLE()                              \
    do {                                                           \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_MCLK1_EN); \
    } while (0U)

/********************************** AUDIO APB **********************************/
#define __DRV_CPR_AUDIO_APB_CLK_ENABLE()                          \
    do {                                                          \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_AUDIO_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_AUDIO_APB_CLK_DISABLE()                           \
    do {                                                            \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_AUDIO_APB_HCLK_EN); \
    } while (0U)

/********************************** PDM **********************************/
#define __DRV_CPR_PDM0_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDM0_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDM0);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDM0_PCLK_EN | CPR_PDM0_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_PDM0_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDM0_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDM0);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDM0_PCLK_EN | CPR_PDM0_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_PDM1_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDM1_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDM1);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDM1_PCLK_EN | CPR_PDM1_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_PDM1_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDM1_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDM1);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDM1_PCLK_EN | CPR_PDM1_MCLK_EN); \
    } while (0U)

/**
  * @brief  pdm0 clk config.
  * @param  div specifies the value of pdm0 mclk divider
  * @retval None
  */
extern void drv_cpr_pdm0_mclk_config(uint32_t div);

/**
  * @brief  pdm1 clk config.
  * @param  div specifies the value of pdm1 mclk divider
  * @retval None
  */
extern void drv_cpr_pdm1_mclk_config(uint32_t div);

/********************************** PDMC **********************************/
#define __DRV_CPR_PDMC_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDMC_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDMC);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDMC_PCLK_EN | CPR_PDMC_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_PDMC_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_PDMC_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_PDMC);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_PDMC_PCLK_EN | CPR_PDMC_MCLK_EN); \
    } while (0U)

/**
  * @brief  pdmc clk config.
  * @param  div specifies the value of pdmc mclk divider
  * @retval None
  */
extern void drv_cpr_pdmc_mclk_config(uint32_t div);

/********************************** I2S/TDM **********************************/
#define __DRV_CPR_CLOCKOUT0_ENABLE()                       \
    do {                                                   \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_CLKOUT0_EN); \
    } while (0U)

#define __DRV_CPR_CLOCKOUT0_DISABLE()                        \
    do {                                                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_CLKOUT0_EN); \
    } while (0U)

#define __DRV_CPR_TDM0_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S0_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S0);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S0_PCLK_EN | CPR_I2S0_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM0_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S0_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S0);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S0_PCLK_EN | CPR_I2S0_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM1_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S1_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S1);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S1_PCLK_EN | CPR_I2S1_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM1_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S1_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S1);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S1_PCLK_EN | CPR_I2S1_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM2_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S2_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S2);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S2_PCLK_EN | CPR_I2S2_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM2_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S2_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S2);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S2_PCLK_EN | CPR_I2S2_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM3_CLK_ENABLE()                                             \
    do {                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S3_P);               \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S3);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S3_PCLK_EN | CPR_I2S3_MCLK_EN); \
    } while (0U)

#define __DRV_CPR_TDM3_CLK_DISABLE()                                              \
    do {                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_I2S3_P);               \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_I2S3);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_I2S3_PCLK_EN | CPR_I2S3_MCLK_EN); \
    } while (0U)

/**
 * @brief  tdm clk clkout0 config.
 * @param  div specifies the value of clkout0 divider
 * @retval None
 */
void drv_cpr_tdm_clkout0_config(uint32_t div);

/**
  * @brief  tdm0 clk config.
  * @param  div specifies the value of tdm0 mclk divider
  * @retval None
  */
extern void drv_cpr_tdm0_mclk_config(uint32_t div);

/**
  * @brief  tdm1 clk config.
  * @param  div specifies the value of tdm1 mclk divider
  * @retval None
  */
extern void drv_cpr_tdm1_mclk_config(uint32_t div);

/**
  * @brief  tdm2 clk config.
  * @param  div specifies the value of tdm2 mclk divider
  * @retval None
  */
extern void drv_cpr_tdm2_mclk_config(uint32_t div);

/**
  * @brief  tdm3 clk config.
  * @param  div specifies the value of tdm3 mclk divider
  * @retval None
  */
extern void drv_cpr_tdm3_mclk_config(uint32_t div);

/********************************** RESAMPLE **********************************/
#define __DRV_CPR_RSM_CLK_ENABLE()                                                              \
    do {                                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_RESAMPLE_P_MSK);                       \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_RESAMPLE_MSK);                        \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_RESAMPLE_PCLK_EN_MSK | CPR_RESAMPLE_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_RSM_CLK_DISABLE()                                                               \
    do {                                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_RESAMPLE_P_MSK);                       \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_RESAMPLE_MSK);                        \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_RESAMPLE_PCLK_EN_MSK | CPR_RESAMPLE_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_RSM_DEINIT()                                                                  \
    do {                                                                                        \
        SET_PROTECT_BIT(CPR->CLK_EN_APB1, CPR_RESAMPLE_PCLK_EN_MSK | CPR_RESAMPLE_MCLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_RESAMPLE_P_MSK);                     \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_RESAMPLE_MSK);                      \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_RESAMPLE_P_MSK);                       \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_RESAMPLE_MSK);                        \
    } while (0U)

/**
 * @brief  resample clk config.
 * @param  div specifies the value of resample mclk divider
 * @retval None
 */
extern void drv_cpr_resample_mclk_set(uint32_t div);

/********************************** SPDIF **********************************/
#define __DRV_CPR_SPDIF_CLK_ENABLE()                                                      \
    do {                                                                                  \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_SPDIF_P_MSK);                    \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_SPDIF_PCLK_EN_MSK | CPR_SPDIF_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPDIF_CLK_DISABLE()                                                       \
    do {                                                                                    \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_SPDIF_P_MSK);                    \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_SPDIF_PCLK_EN_MSK | CPR_SPDIF_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPDIF_DEINIT()                                                          \
    do {                                                                                  \
        SET_PROTECT_BIT(CPR->CLK_EN_APB2, CPR_SPDIF_PCLK_EN_MSK | CPR_SPDIF_MCLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_SPDIF_P_MSK);                  \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_SPDIF_P_MSK);                    \
    } while (0U)

/**
 * @brief  spdif clk config.
 * @param  div specifies the value of spdif mclk divider
 * @retval None
 */
extern void drv_cpr_spdif_mclk_set(uint32_t div);

/********************************** spim **********************************/
#define __DRV_CPR_SPIM_CLK_ENABLE()                                                                   \
    do {                                                                                              \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_M_P_MSK);                          \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_M_MSK);                               \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_M_PCLK_EN_MSK | CPR_DW_APB_SSI_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPIM_CLK_DISABLE()                                                                    \
    do {                                                                                                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_M_PCLK_EN_MSK | CPR_DW_APB_SSI_MCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPIM_DEINIT()                                                                       \
    do {                                                                                              \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_M_PCLK_EN_MSK | CPR_DW_APB_SSI_MCLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_M_P_MSK);                        \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_M_MSK);                             \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_M_P_MSK);                          \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_M_MSK);                               \
    } while (0U)

/**
 * @brief  spi master clk config.
 * @param  div specifies the value of spi mclk divider
 * @retval None
 */
extern void drv_cpr_spim_mclk_set(uint32_t div);

/********************************** spis **********************************/
#define __DRV_CPR_SPIS_CLK_ENABLE()                                                                    \
    do {                                                                                               \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_S_P_MSK);                           \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_S_MSK);                                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_S_PCLK_EN_MSK | CPR_DW_APB_SSI_S_CLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPIS_CLK_DISABLE()                                                                     \
    do {                                                                                                 \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_S_PCLK_EN_MSK | CPR_DW_APB_SSI_S_CLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_SPIS_DEINIT()                                                                        \
    do {                                                                                               \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_DW_APB_SSI_S_PCLK_EN_MSK | CPR_DW_APB_SSI_S_CLK_EN_MSK); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_S_P_MSK);                         \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_S_MSK);                              \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_DW_APB_SSI_S_P_MSK);                           \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_DW_APB_SSI_S_MSK);                                \
    } while (0U)

/**
 * @brief  spi slave clk config.
 * @param  div specifies the value of spi mclk divider
 * @retval None
 */
extern void drv_cpr_spis_mclk_set(uint32_t div);

/********************************** gpadc **********************************/
#define __DRV_CPR_GPADC_CLK_ENABLE()                                                                                             \
    do {                                                                                                                         \
        SET_BIT(PMU->LDO_ANA, PMU_ENP_LDO_ANA_MSK);                                                                              \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_GP_ADC_PCLK_EN_MSK);                                                               \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_GP_ADC_MSK);                                                             \
    } while (0U)

#define __DRV_CPR_GPADC_CLK_DISABLE()                                \
    do {                                                             \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_GP_ADC_PCLK_EN_MSK); \
    } while (0U)

#define __DRV_CPR_GPADC_DEINIT()                                                                                                 \
    do {                                                                                                                         \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_GP_ADC_PCLK_EN_MSK);                                                             \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_GP_ADC_MSK);                                                           \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_GP_ADC_MSK);                                                             \
    } while (0U)

/********************************** AUDIO BUS **********************************/
#define __DRV_CPR_AUDIO_BUS_CLK_ENABLE()                                 \
    do {                                                                 \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_AUDIO_BUS);     \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_AUDIO_BUS_CLK_EN); \
    } while (0U)

#define __DRV_CPR_AUDIO_BUS_CLK_DISABLE()                                  \
    do {                                                                   \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_BUS, CPR_RSTN_AUDIO_BUS);     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_AUDIO_BUS_CLK_EN); \
    } while (0U)

/********************************** CODEC **********************************/
#define __DRV_CPR_CODEC_CLK_ENABLE()                                                                                  \
    do {                                                                                                              \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CODEC | CPR_RSTN_CODEC_6P144);                              \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_APBBRG);                                            \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_PCLK_EN | CPR_CPU2_APB_HCLK_EN | CPR_CODEC_6P144_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_CLK_DISABLE()                                                                                   \
    do {                                                                                                                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CODEC | CPR_RSTN_CODEC_6P144);                              \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_APBBRG);                                            \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_PCLK_EN | CPR_CPU2_APB_HCLK_EN | CPR_CODEC_6P144_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_ADC_CLK_ENABLE()                                 \
    do {                                                                 \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CODEC_ADC);    \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_ADC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_ADC_CLK_DISABLE()                                  \
    do {                                                                   \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CODEC_ADC);    \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_ADC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_DAC_CLK_ENABLE()                                 \
    do {                                                                 \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_DAC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_DAC_CLK_DISABLE()                                  \
    do {                                                                   \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CODEC_DAC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_DAC_OFC_CLK_ENABLE()                 \
    do {                                                     \
        SET_BIT(CPR->DAC_CLK_CFG, CPR_CODEC_DAC_OFC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_CODEC_DAC_OFC_CLK_DISABLE()                  \
    do {                                                       \
        CLEAR_BIT(CPR->DAC_CLK_CFG, CPR_CODEC_DAC_OFC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_ANC_CLK_ENABLE()                                 \
    do {                                                           \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_ANC);         \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_ANC_CLK_EN); \
    } while (0U)

#define __DRV_CPR_ANC_CLK_DISABLE()                                  \
    do {                                                             \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_ANC);         \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_ANC_CLK_EN); \
    } while (0U)

/** @defgroup drv_cpr_codec6144_Source_Status anc Clock Source Status
 * @{
 */
#define DRV_CPR_CODEC_SOURCE_MCLK1 (0x0 << CPR_CODEC_6P144_CLK_SEL_POS)
#define DRV_CPR_CODEC_SOURCE_PLL0  (0x1 << CPR_CODEC_6P144_CLK_SEL_POS)

/** @brief  Macro to get the clock source used as anc clk.
 * @retval The clock source used as anc clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_CODEC_SOURCE_MCLK1: MCLK1 used as codec 6144M clock.
 *              - DRV_CPR_CODEC_SOURCE_PLL0: External low frequency pll0 use as codec 6144M clock.
 */
#define __DRV_CPR_GET_CODEC_SOURCE() READ_BIT(CPR->CLK_DIV_AUDIO8, CPR_CODEC_6P144_CLK_SEL)

#define __DRV_CPR_SET_CODEC_SOURCE(__CODEC_SOURCE__) MODIFY_REG(CPR->CLK_DIV_AUDIO8, CPR_CODEC_6P144_CLK_SEL, __CODEC_SOURCE__)

/** @defgroup drv_cpr_anc_Source_Status anc Clock Source Status
 * @{
 */
#define DRV_CPR_ANC_SOURCE_DOUBLE    (0x0 << CPR_ANC_CLK_SRC_SEL_POS)
#define DRV_CPR_ANC_SOURCE_HFXO      (0x1 << CPR_ANC_CLK_SRC_SEL_POS)
#define DRV_CPR_ANC_SOURCE_MCLK1     (0x2 << CPR_ANC_CLK_SRC_SEL_POS)
#define DRV_CPR_ANC_SOURCE_MCLK1_96M (0x3 << CPR_ANC_CLK_SRC_SEL_POS)

/** @brief  Macro to get the clock source used as anc clk.
 * @retval The clock source used as anc clock. The returned value can be one
 *         of the following:
 *              - DRV_CPR_ANC_SOURCE_DOUBLE: double clock (original 48M)used as anc 48M clock.
 *              - DRV_CPR_ANC_SOURCE_HFXO:   HSE used as anc 48M clock(original 24M).
 *              - DRV_CPR_ANC_SOURCE_MCLK1: DIVIDED mclk1 used as anc clock 48M.
 *              - DRV_CPR_ANC_SOURCE_MCLK1_96M: DIVIDED mclk1 used as anc clock 96M, anc clock 48M from 96M.
 */
#define __DRV_CPR_GET_ANC_SOURCE() READ_BIT(CPR->CLK_MUX, CPR_ANC_CLK_SRC_SEL)

#define __DRV_CPR_SET_ANC_SOURCE(__ANC_SOURCE__) MODIFY_REG(CPR->CLK_MUX, CPR_ANC_CLK_SRC_SEL, __ANC_SOURCE__)

/**
  * @brief  codec dac 6.144M clk config.
  * @param  div specifies the value of codec dac mclk divider
  * @retval None
  */
extern void drv_cpr_codec_dac_mclk_config(uint32_t div);

/**
 * @brief  set dac ofc clock division
 * @param  div specifies the value of codec dac ofc clk divider
 * @return none
 */
extern void drv_cpr_codec_dac_ofc_clk_set(uint32_t div);

/**
  * @brief  codec adc clk config.
  * @param  div specifies the value of codec adc mclk divider
  * @retval None
  */
extern void drv_cpr_codec_adc_clk_config(uint32_t div);

/**
  * @brief  codec anc clk config.
  * @param  div specifies the value of codec anc mclk divider
  * @retval None
  */
extern void drv_cpr_codec_anc_clk_config(uint32_t div);

/**
  * @brief  codec i2c clk config.
  * @param  div specifies the value of codec anc mclk divider
  * @retval None
  */
extern void drv_cpr_i2c_clk_config(uint32_t div);
/**
 * @brief  get codec i2c clk config.
 * @retval i2c clk div value
 */
extern uint32_t drv_cpr_i2c_clk_config_get(void);
/**
  * @brief  codec timer clk config.
  * @param  div specifies the value of codec anc mclk divider
  * @retval None
  */
extern void drv_cpr_timer_clk_config(uint8_t div);
/**
 * @brief  audio system power up.
 * @param  None
 * @retval None
 */
extern void drv_cpr_audio_system_powerup(void);

/**
 * @brief  audio system power down.
 * @param  None
 * @retval None
 */
extern void drv_cpr_audio_system_powerdown(void);

/* Peripheral Control functions  ************************************************/
extern uint32_t drv_cpr_get_cpu0_freq(void);
extern uint32_t drv_cpr_get_cpu1_freq(void);
extern uint32_t drv_cpr_get_cpu2_freq(void);
extern uint32_t drv_cpr_get_mclk0_freq(void);
extern uint32_t drv_cpr_get_mclk1_freq(void);
extern uint32_t drv_cpr_get_fracpll_out_freq(void);
extern drv_status_t drv_cpr_enable_fracpll(uint32_t pll_freq);
extern drv_status_t drv_cpr_fine_adj_fracpll(int fd_div);
extern drv_status_t drv_cpr_enable_bbpll(void);
extern void drv_cpr_audio_apb_clk_div_set(uint8_t div);
extern drv_status_t drv_cpr_config_mclk1(cpr_mclk1_init_t *mclk1_init);
extern void drv_cpr_cpu1_apb_clk_div_set(uint8_t div);

/********************************** usb2.0 **********************************/
#define __DRV_CPR_USB_PHY_RST_SET() SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_PHY_MSK);
#define __DRV_CPR_USB_PHY_RST_CLR() CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_PHY_MSK);

extern void drv_cpr_usb_utmifs_clk48_sel(uint32_t src);
extern void drv_cpr_utmifs_clk48_set(uint32_t div);
extern void drv_cpr_usb_clk_init(void);
extern void drv_cpr_usb_deinit(void);

/********************************** CPU CORE **********************************/
/**
  * @brief  config cpu rst
  * @param  val specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg CPR_RSTN_CPU0_CORE
  *            @arg CPR_RSTN_CPU0_SLV
  *            @arg CPR_RSTN_CPU0_BUS
  *            @arg CPR_RSTN_CPU1_CORE
  *            @arg CPR_RSTN_CPU1_BUS
  *            @arg CPR_RSTN_CPU1_ILM
  *            @arg CPR_RSTN_CPU1_DLM
  *            @arg CPR_RSTN_SHRAM1
  */
#define __DRV_CPR_CPU_SYSTEM_RST_SET(val) CLEAR_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, val);
#define __DRV_CPR_CPU_SYSTEM_RST_CLR(val) SET_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, val);

/********************************** CPU2 CFG **********************************/
/**
  * @brief  config CPU2
  * @param  val specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg CPR_CPU2_TCM_MEM_SEL
  *            @arg CPR_CPU2_STALL
  *            @arg CPR_CPU2_REMAP
  *            @arg CPR_CPU2_OCDHALTONRST
  *            @arg CPR_CPU2_PDEBUGENABLE
  */
#define __DRV_CPR_CPU2_CFG_SET(val)   SET_BIT(CPR->CPU2_CFG, val)
#define __DRV_CPR_CPU2_CFG_CLEAR(val) CLEAR_BIT(CPR->CPU2_CFG, val)

#define __DRV_CPR_CPU2_CLK_ENABLE()                                                        \
    do {                                                                                   \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CPU2_CLK_EN | CPR_CPU2_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_CPU2_CLK_DISABLE()                                                         \
    do {                                                                                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CPU2_CLK_EN | CPR_CPU2_APB_HCLK_EN); \
    } while (0U)

#define __DRV_CPR_CPU2_RESET_ENABLE()                                   \
    do {                                                                \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_H); \
        CLEAR_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CPU2_M);    \
    } while (0U)

#define __DRV_CPR_CPU2_RESET_DISABLE()                                \
    do {                                                              \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_H); \
        SET_PROTECT_BIT(CPR->RST_SET_AUDIO_FUNC, CPR_RSTN_CPU2_M);    \
    } while (0U)

#define __DRV_CPR_CPU2_APB_CLK_ENABLE()                                    \
    do {                                                                   \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_APBBRG); \
    } while (0U)

#define __DRV_CPR_CPU2_APB_CLK_DISABLE()                                     \
    do {                                                                     \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS0, CPR_RSTN_CPU2_APBBRG); \
    } while (0U)

#define __DRV_CPR_CPU0_SOFT_RESET()                                              \
    do {                                                                         \
        CLEAR_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, CPR_CPU0_BUS_PULSE_RST_MASK); \
        SET_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, CPR_RSTN_CPU0_CORE_PULSE);      \
    } while (0U)

#define __DRV_CPR_CPU1_SOFT_RESET()                                              \
    do {                                                                         \
        CLEAR_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, CPR_CPU0_SLV_PULSE_RST_MASK); \
        SET_PROTECT_BIT(CPR->RST_SET_CPU_SYSTEM, CPR_RSTN_CPU1_CORE_PULSE);      \
    } while (0U)

/********************************** WDT **********************************/
#if defined(MCU_CORE_TL752X_D25F)
#define __DRV_CPR_WDT_CLK_ENABLE()                                                      \
    do {                                                                                \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_CPU_WDT);                          \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU_WDT_P);                     \
        SET_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_CPU0_WDT_PCLK_EN | CPR_CPU0_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_CLK_DISABLE()                                                       \
    do {                                                                                  \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_CPU_WDT);                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU_WDT_P);                     \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB0, CPR_CPU0_WDT_PCLK_EN | CPR_CPU0_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_RST()                                   \
    do {                                                      \
        CLEAR_PROTECT_BIT(CPR->RST_CTRL, CPR_RESET_SRC_W(2)); \
    } while (0U)
#elif defined(MCU_CORE_TL752X_N22)
#define __DRV_CPR_WDT_CLK_ENABLE()                                                      \
    do {                                                                                \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_CPU_RF_WDT);                       \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU_CPU1_WDT_P);                \
        SET_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_CPU1_WDT_PCLK_EN | CPR_CPU1_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_CLK_DISABLE()                                                       \
    do {                                                                                  \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC1, CPR_RSTN_CPU_RF_WDT);                       \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU_CPU1_WDT_P);                \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_APB3, CPR_CPU1_WDT_PCLK_EN | CPR_CPU1_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_RST()                                   \
    do {                                                      \
        CLEAR_PROTECT_BIT(CPR->RST_CTRL, CPR_RESET_SRC_W(3)); \
    } while (0U)
#elif defined(MCU_CORE_TL752X_DSP)
#define __DRV_CPR_WDT_CLK_ENABLE()                                                              \
    do {                                                                                        \
        SET_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_CPU2_WDT);                                 \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU2_WDT_P);                            \
        SET_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CPU2_WDT_PCLK_EN | CPR_CPU2_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_CLK_DISABLE()                                                               \
    do {                                                                                          \
        CLEAR_PROTECT_BIT(CPR->RST_SET_FUNC0, CPR_RSTN_CPU2_WDT);                                 \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_APB, CPR_RSTN_CPU2_WDT_P);                            \
        CLEAR_PROTECT_BIT(CPR->CLK_EN_AUDIO_SYSTEM, CPR_CPU2_WDT_PCLK_EN | CPR_CPU2_WDT_TCLK_EN); \
    } while (0U)

#define __DRV_CPR_WDT_RST()                                   \
    do {                                                      \
        CLEAR_PROTECT_BIT(CPR->RST_CTRL, CPR_RESET_SRC_W(4)); \
    } while (0U)
#endif

/********************************** RAY_2G4 **********************************/
#define __DRV_CPR_RAY_2G4_CLK_ENABLE()                                                                              \
    do {                                                                                                            \
        SET_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_BT_SYS_BB | CPR_RSTN_BT_SYS_32K | CPR_RSTN_BT_SYS_RF); \
        SET_PROTECT_BIT(CPR->CLK_EN_RF_SYSTEM, CPR_BT_SYS_CLK_EN | CPR_BT_SYS_HCLK_EN | CPR_BT_RFDIG_CLK_EN);       \
        CLEAR_PROTECT_BIT(CPR->BT_CFG, CPR_BT_SYS_TAHDT_MODE);                                                        \
        SET_PROTECT_BIT(CPR->BT_CFG, CPR_BT_SYS_CPU_BT_GCLKEN);                                                     \
    } while (0)

#define __DRV_CPR_RAY_2G4_CLK_DISABLE()                                    \
    do {                                                                   \
        CLEAR_PROTECT_BIT(CPR->RST_SET_MAIN_AHB_BUS1, CPR_RSTN_BT_SYS_BB); \
    } while (0)

/********************************** RAM CFG **********************************/
/* must be executed when the xip has no cache */
#define __DRV_CPR_RAM_CFG_SET_EMA(__EMA__) MODIFY_REG(CPR->RAM_CFG, CPR_SRSP_EMA_MSK | CPR_RFSP_EMA_MSK, (__EMA__ << CPR_SRSP_EMA_POS) | (__EMA__ << CPR_RFSP_EMA_POS))

#ifdef __cplusplus
}
#endif

#endif

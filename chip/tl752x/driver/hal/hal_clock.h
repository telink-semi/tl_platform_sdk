/********************************************************************************************************
 * @file    hal_clock.h
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

#ifndef __HAL_CLOCK_H__
#define __HAL_CLOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal/hal_clock.h"
#include "hal/hal_flash.h"
#include "inc/inc.h"
#include "modules/modules.h"

#define CLOCK_SOURCE_(n) (n << 8)
#define __DRV_CPR_GET_MSPI_DIV()      READ_BIT(DWC_SSI0->BAUDR, SSI_SCKDV)
#define __DRV_CPR_GET_APB0_DIV()      READ_BIT(CPR->CLK_DIV_APB, CPR_APB0_DIV_VAL_MSK)
#define __DRV_CPR_GET_APB_DIV()       READ_BIT(CPR->CLK_DIV_BUS, CPR_CPU1_APB_DIV_VAL)
#define reg_swire_ctl                 REG_ADDR32(SWIRE_BASE_ADDR)


#define APB0_MAX_FREQUENCY (36000000)
#define APB0_MIN_FREQUENCY (12000000)

#define D25F_EMI_SRSP_RFSP_FREQUENCY (128000000)
#define N22_EMI_SRSP_RFSP_FREQUENCY (128000000)
#define DSP_EMI_SRSP_RFSP_FREQUENCY (64000000)

/**
 * @brief clock division type. clock division to cclk. cclk division to hclk_pclk,clock division to clk_mspi. clock division to clk_lspi. pclk division to clk_wt. clock division to DSP. XTAL48M division to clk_n22.
 */
typedef enum
{
    CLK_DIV1 = 1,
    CLK_DIV2,
    CLK_DIV3,
    CLK_DIV4,
    CLK_DIV5,
    CLK_DIV6,
    CLK_DIV7,
    CLK_DIV8,
    CLK_DIV9,
    CLK_DIV10,
    CLK_DIV11,
    CLK_DIV12,
    CLK_DIV13,
    CLK_DIV14,
    CLK_DIV15,
} clock_div_e;

/**
 * @brief n22 clock division type. The clock source comes from d25.
 */
typedef enum{
    MCLK_DIV1_TO_D25F_CLK = CLK_DIV1,
    MCLK_DIV2_TO_D25F_CLK = CLK_DIV2,
    MCLK_DIV3_TO_D25F_CLK = CLK_DIV3,
    MCLK_DIV4_TO_D25F_CLK = CLK_DIV4,
} sys_mclk_div_to_d25f_clk_e;

/**
 * @brief The N22 clock division has its clock source coming from D25F, while both AHB and APB clock sources are N22, with a default frequency division of 1.
 */
typedef enum{
    D25F_DIV1_TO_N22_AHB_APB_CLK = CLK_DIV1,
    D25F_DIV2_TO_N22_AHB_APB_CLK = CLK_DIV2,
    D25F_DIV3_TO_N22_AHB_APB_CLK = CLK_DIV3,
    D25F_DIV4_TO_N22_AHB_APB_CLK = CLK_DIV4,
} sys_d25f_div_to_n22_ahb_apb_clk_e;

/**
 * @brief DSP clock sources: MCLK, D25F, N22, and AHB.
 */
typedef enum{
    DSP_FROM_MCLK = DRV_CPR_CPU2_SOURCE_MCLK0,
    DSP_FROM_D25F = DRV_CPR_CPU2_SOURCE_CPU0,
    DSP_FROM_N22 = DRV_CPR_CPU2_SOURCE_CPU1,
    DSP_FROM_AHB = DRV_CPR_CPU2_SOURCE_AHB,
} sys_dsp_source_e;

/**
 * @brief dsp clock division type. The clock source can be equipped with four sources: mclk, d25f, n22, and ahb.
 */
typedef enum{

    MCLK_DIV1_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_MCLK0 | CLK_DIV1),
    MCLK_DIV2_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_MCLK0 | CLK_DIV2),
    MCLK_DIV3_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_MCLK0 | CLK_DIV3),
    MCLK_DIV4_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_MCLK0 | CLK_DIV4),
    D25F_DIV1_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_CPU0 | CLK_DIV1),
    N22_DIV1_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_CPU1 | CLK_DIV1),
    AHB_DIV1_TO_DSP_CLK = (DRV_CPR_CPU2_SOURCE_AHB | CLK_DIV1),
} sys_dsp_clk_e;

/**
 * @brief mspi clock division type. The clock source comes from n22.
 * @note  When the d25f chip accesses the flash, the maximum Mspi clock speed is set to 64M. When the n22 chip accesses the flash, the maximum Mspi clock speed is 32M.
 *        The clock frequency of N22 must be twice that of the flash clock.
 */
typedef enum{
    MCLK_DIV2_TO_MSPI_CLK = CLK_DIV2,
    MCLK_DIV4_TO_MSPI_CLK = CLK_DIV4,
    MCLK_DIV8_TO_MSPI_CLK = CLK_DIV8,
} sys_n22_div_to_mspi_clk_e;

#define DRV_CPR_MCLK0_SOURCE_DIVIDED_PLL (0x0 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_HFRCO       (0x1 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_HFXO        (0x2 << CPR_MCLK0_SEL_POS)
#define DRV_CPR_MCLK0_SOURCE_DOUBLE      (0x3 << CPR_MCLK0_SEL_POS)

typedef enum
{
    PLL0_BBPLL = 0,
    RC_OSC_48M = 1,
    XTAL_24M   = 2,
    DOUBLE_48M = 3,
} sys_mclk0_src_config_e;

/**
 * @brief system clock type
 * |                                   |               |
 * | :-------------------------------  | :------------ |
 * |                <0:8>              |     <24:8>    |
 * |               mclk0 src            |      mclk0      |
 */
typedef enum
{
    CLK_SOURCE_XTAL_MCLK0_24M           = XTAL_24M   | (24 << 8),
    CLK_SOURCE_DOUBLE_MCLK0_48M         = DOUBLE_48M | (48 << 8),
    CLK_SOUCE_RC_MCLK0_48M              = RC_OSC_48M | (48 << 8),
    CLK_SOURCE_PLL0_MCLK0_24M           = PLL0_BBPLL | (24 << 8),
    CLK_SOURCE_PLL0_MCLK0_48M           = PLL0_BBPLL | (48 << 8),
    CLK_SOURCE_PLL0_MCLK0_96M           = PLL0_BBPLL | (96 << 8),
    CLK_SOURCE_PLL0_MCLK0_128M          = PLL0_BBPLL | (128 << 8),
    CLK_SOURCE_PLL0_MCLK0_192M          = PLL0_BBPLL | (192 << 8),
    CLK_SOURCE_PLL0_MCLK0_256M          = PLL0_BBPLL | (256 << 8)
} sys_mclk0_config_e;

/**
 *  @brief  Define sys_clk_config_t struct.
 */
typedef struct
{
    unsigned char clk_cpu2_source_cfg;
    unsigned char clk_mclk0_div_cfg;
    unsigned char clk_cpu0_div_cfg;
    unsigned char clk_cpu1_div_cfg;
    unsigned char clk_ahb_div_cfg;
    unsigned char clk_set_cfg;
    unsigned char clk_mspi_div_cfg;
    unsigned char clk_apb0_div_cfg;
    unsigned int clk_div_pll_cfg;

} sys_clk_config_t;

extern sys_clk_config_t sys_clk_config;


/**
 * @brief       This function use to select the system clock source,voltage versus frequency refer to table clock_h_1.
 * @param[in]   src                  - MCLK clock value and clock source configuration.
 * @param[in]   clk_n22_div          - the cclk divide from n22.
 * @param[in]   dsp_clk_config          - the cclk divide from dsp.
 * @param[in]   clk_mspi_div         - the cclk divide from mspi.
 * @note        Since bbpll does not support fractional frequency division, the Core Voltage range of 0.81V to 0.99V can only support up to 256M.
 * @note        Clock Frequency Configuration Table
 * --------------------------------------------------------------
 * | Component Name   | Core Voltage 0.72V ~ 0.8V | Core Voltage 0.81V ~ 0.99V(Internal use is not yet available.) |
 * --------------------------------------------------------------
 * | D25F CPU         |          128 MHz           |          300 MHz            |
 * | N22 CPU          |           64 MHz           |          150 MHz            |
 * | HIFI5 DSP        |          128 MHz           |          300 MHz            |
 * | AHB              |           64 MHz           |          150 MHz            |
 * | MAIN APB         |           64 MHz           |          150 MHz            |
 * | AUDIO APB        |           64 MHz           |          150 MHz            |
 * | DSP APB          |           64 MHz           |          150 MHz            |
 * | N22 APB          |           64 MHz           |          150 MHz            |
 * | ACN APB          |           32 MHz           |           75 MHz            |
 * | DWC SSI          |          128 MHz           |          300 MHz            |
 * | I2C              |           64 MHz           |          150 MHz            |
 * | UART             |           64 MHz           |          150 MHz            |
 * | SPI              |           64 MHz           |          150 MHz            |
 * | SDIO             |           64 MHz           |          150 MHz            |
 * | USB              |           48 MHz           |           48 MHz            |
 * | BT               |           24 MHz           |           24 MHz            |
 * | CODEC            |        6.144 MHz           |        6.144 MHz            |
 * | ANC              |           48 MHz           |           48 MHz            |
 * | I2S              |           50 MHz           |          100 MHz            |
 * | PDM              |           20 MHz           |           20 MHz            |
 * | S/PDIF           |          100 MHz           |          150 MHz            |
 * | RESAMPLE         |           50 MHz           |          100 MHz            |
 * | WDT              |           32 kHz           |           32 kHz            |
 * | RTC              |           32 kHz           |           32 kHz            |
 * | TIMER            |           25 MHz           |           50 MHz            |
 * --------------------------------------------------------------
 * @return      none
 */
_attribute_text_sec_ drv_status_t clock_init(sys_mclk0_config_e src,sys_mclk_div_to_d25f_clk_e clk_d25f_div,sys_d25f_div_to_n22_ahb_apb_clk_e clk_n22_div,sys_dsp_clk_e dsp_clk_config, sys_n22_div_to_mspi_clk_e clk_mspi_div);

/**
 * @brief       This function is used to obtain the APB clock.
 * @return      apb frequency.
 * @note        none.
 */
_attribute_retention_ram_code_sec_ uint32_t clock_get_apb_freq(void);

/**
 * @brief     This function performs to 32K RC calibration.
 * @return    none.
 */
void clock_cal_32k_rc(void);

/**
 * @brief     This function performs to 48m RC calibration.
 * @return    none.
 */
void clock_cal_48m_rc(void);


#if 0 // Internal use is not yet available.
// core 0.81~0.99V
#define PLL0_BBPLL_768M_MCLK_256M_D25F_256M_N22_128M_DSP_256M_MSPI_64M \
   clock_init(CLK_SOURCE_PLL0_MCLK0_256M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV2_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV4_TO_MSPI_CLK);
#define PLL0_BBPLL_768M_MCLK_192M_D25F_192M_N22_96M_DSP_192M_MSPI_48M \
   clock_init(CLK_SOURCE_PLL0_MCLK0_192M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV2_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV4_TO_MSPI_CLK);
#define PLL0_BBPLL_768M_MCLK_128M_D25F_128M_N22_128M_DSP_128M_MSPI_64M \
    clock_init(CLK_SOURCE_PLL0_MCLK0_128M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);
#define PLL0_BBPLL_768M_MCLK_128M_D25F_128M_N22_128M_DSP_128M_MSPI_32M \
    clock_init(CLK_SOURCE_PLL0_MCLK0_128M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV4_TO_MSPI_CLK);
#define PLL0_BBPLL_768M_MCLK_96M_D25F_96M_N22_96M_DSP_96M_MSPI_48M \
    clock_init(CLK_SOURCE_PLL0_MCLK0_96M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);
#endif

// core 0.72~0.8V
#define PLL0_BBPLL_768M_MCLK_128M_D25F_128M_N22_64M_DSP_128M_MSPI_32M \
    clock_init(CLK_SOURCE_PLL0_MCLK0_128M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV2_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV4_TO_MSPI_CLK);
#define PLL0_BBPLL_768M_MCLK_96M_D25F_96M_N22_48M_DSP_48M_MSPI_24M \
    clock_init(CLK_SOURCE_PLL0_MCLK0_96M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV2_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);
#define RC_OSC_48M_MCLK_48M_D25F_48M_N22_48M_DSP_48M_MSPI_24M \
    clock_init(CLK_SOUCE_RC_MCLK0_48M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);
#define XTAL_24M_MCLK_24M_D25F_24M_N22_24M_DSP_24M_MSPI_12M \
    clock_init(CLK_SOURCE_XTAL_MCLK0_24M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);
#define DOUBLE_48M_MCLK_48M_D25F_48M_N22_48M_DSP_48M_MSPI_24M \
    clock_init(CLK_SOURCE_DOUBLE_MCLK0_48M,MCLK_DIV1_TO_D25F_CLK,D25F_DIV1_TO_N22_AHB_APB_CLK, MCLK_DIV1_TO_DSP_CLK,MCLK_DIV2_TO_MSPI_CLK);

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************************************
 *
 * @file    drv_pmu_ex.h
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
#ifndef __DRV_PMU_EX_H__
#define __DRV_PMU_EX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tl_chip.h"
/********************************** RTC **********************************/
#define __DRV_PMU_RTC_CLK_ENABLE()                                                    \
    do {                                                                              \
        SET_PROTECT_BIT(PMU->RST_SET_AO, PMU_RSTN_RTC_P_SET | PMU_RSTN_SOFT_RTC_SET); \
        SET_PROTECT_BIT(PMU->CLK_EN_M_AO, PMU_RTC_CLK_EN);                            \
    } while (0U)

#define __DRV_PMU_RTC_CLK_DISABLE()                                                     \
    do {                                                                                \
        CLEAR_PROTECT_BIT(PMU->RST_SET_AO, PMU_RSTN_RTC_P_SET | PMU_RSTN_SOFT_RTC_SET); \
        CLEAR_PROTECT_BIT(PMU->CLK_EN_M_AO, PMU_RTC_CLK_EN);                            \
    } while (0U)
/********************************** CPU CORE **********************************/
/**
  * @brief  config CPU1 core clk.
  * @param  val specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg PMU_BT_SYS_CLK32K_EN
  *            @arg PMU_GPIO_DEB_CLK_EN
  *            @arg PMU_CHG_DEB_CLK_EN
  *            @arg PMU_RTC_CLK_EN
  *            @arg PMU_SHRAM1_CLK_EN
  *            @arg PMU_CPU1_DLM_CLK_EN
  *            @arg PMU_CPU1_ILM_CLK_EN
  *            @arg PMU_CPU1_CORE_AON_CLK_EN
  *            @arg PMU_CPU1_CORE_CLK_EN
  *            @arg PMU_CPU1_SYSTEM_CLK_EN
  */
#define __DRV_PMU_CLK_EN_M_AO_SET(val) SET_PROTECT_BIT(PMU->CLK_EN_M_AO, val);
#define __DRV_PMU_CLK_EN_M_AO_CLR(val) CLEAR_PROTECT_BIT(PMU->CLK_EN_M_AO, val);

/********************************** GPIO **********************************/
/**
  * @brief  gpiob input enable.
  * @param  pin specifies the port bit to be written.can be GPIO_PIN_0 - GPIO_PIN_13.
  * @param  en specifies the value to be written to the selected bit.
  *          This parameter can be one of the drv_flag_status_t enum values:
  *            @arg DRV_RESET: to clear the port pin input disable
  *            @arg DRV_SET: to set the port pin input enable
  * @retval None
  */
extern void drv_pmu_gpio_portb_ie_cfg(uint32_t pin, drv_flag_status_t en);

/**
  * @brief  gpiob pull up or down cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 13.
  * @param  pu_pd specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_NOPULL: gpio no pull
  *            @arg GPIO_PULLUP: gpio pull-up
  *            @arg GPIO_PULLDOWN: gpio pull-down
  * @retval None
  */
extern void drv_pmu_gpio_portb_pupd(uint32_t pin_num, uint32_t pu_pd);

/**
  * @brief  gpiob output electric cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 13.
  * @param  electric specifies the value to be written to the selected bit.
  *          This parameter can be one of the define values:
  *            @arg GPIO_ELECTRIC_2MA: output electric 2mA
  *            @arg GPIO_ELECTRIC_4MA: output electric 4mA
  *            @arg GPIO_ELECTRIC_8MA: output electric 8mA
  *            @arg GPIO_ELECTRIC_12MA: output electric 12mA
  * @retval None
  */
extern void drv_pmu_gpio_portb_electric(uint32_t pin_num, uint32_t electric);
/**
 * @brief  gpiob interrupt enable
 * @param  pin_num specifies the port bit to be written.can be 0 - 13.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: to clear the port pin input disable
 *            @arg DRV_SET: to set the port pin input enable
 * @retval None
 */
extern void drv_pmu_gpio_portb_irq_set(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpiob interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 13.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: logic high level
 *            @arg DRV_SET: logic low level
 * @retval None
 */
extern void drv_pmu_gpio_portb_irq_type(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpiob interrupt debounce
 * @param  pin_num specifies the port bit to be written.can be 0 - 13.
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: logic high level
 *            @arg DRV_SET: logic low level
 * @retval None
 */
extern void drv_pmu_gpio_portb_irq_debounce(uint32_t pin_num, drv_flag_status_t en);
/**
 * @brief  gpiob debounce clk enable
 * @param  en specifies the value to be written to the selected bit.
 *          This parameter can be one of the drv_flag_status_t enum values:
 *            @arg DRV_RESET: logic high level
 *            @arg DRV_SET: logic low level
 * @retval None
 */
void drv_pmu_gpio_portb_debounce_clk_enable(drv_flag_status_t en);
/**
 * @brief  gpiob interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 13.
 * @retval pb irq status
 */
extern uint32_t drv_pmu_gpio_portb_irq_read(void);
/**
 * @brief  gpiob interrupt polarity
 * @param  pin_num specifies the port bit to be written.can be 0 - 13.
 * @retval None
 */
extern void drv_pmu_gpio_portb_irq_clear(uint32_t pin_num);

/**
  * @brief  gpiob oe manual cfg.
  * @param  pin_num specifies the port bit to be written.can be 0 - 31.
  * @param  value specifies the value to be written to the selected bit.
  * @retval None
  */
extern void drv_pmu_gpio_portb_oe_man(uint32_t pin_num, uint32_t value);
/********************************** usb **********************************/
/**
 * @brief  set usb power switch
 *
 * @param  en /ref drv_flag_status_t
 * @return none
 * @note   none
 */
extern void drv_pmu_set_usb_power_sw(drv_flag_status_t en);

/**
 * @brief  rfpa power on
 *
 * @param  none
 * @return none
 * @note   none
 */
extern void drv_pmu_rfpa_poweron(void);

/**
 * @brief  rfpa power off
 *
 * @param  none
 * @return none
 * @note   none
 */
extern void drv_pmu_rfpa_poweroff(void);

#define __DRV_PMU_CLK_DBLR_ENABLE()             \
    do {                                        \
        SET_BIT(PMU->RF_CFG1, PMU_XO_CLKX2_EN); \
    } while (0)

#define __DRV_PMU_CLK_DBLR_DISABLE()              \
    do {                                          \
        CLEAR_BIT(PMU->RF_CFG1, PMU_XO_CLKX2_EN); \
    } while (0)

/********************************** EFUSE **********************************/
#define __DRV_PMU_SW_EFU_ENABLE()               \
    do {                                        \
        SET_BIT(PMU->LDO_ANA, PMU_ENP_LDO_CDC); \
        SET_BIT(PMU->SW_USB, PMU_ENP_SW_EFU);   \
    } while (0)

#define __DRV_PMU_SW_EFU_DISABLE()              \
    do {                                        \
        CLEAR_BIT(PMU->SW_USB, PMU_ENP_SW_EFU); \
    } while (0)

#define __DRV_PMU_MICBIAS_ENABLE()                \
    do {                                          \
        SET_BIT(PMU->MIC_BIAS, PMU_ENP_MIC_BIAS); \
    } while (0)

#define __DRV_PMU_MICBIAS_DISABLE()                 \
    do {                                            \
        CLEAR_BIT(PMU->MIC_BIAS, PMU_ENP_MIC_BIAS); \
    } while (0)

/**
 * @brief  codec pmu poweron
 *
 * @param  none
 * @return none
 * @note   none
 */
void drv_pmu_codec_poweron(void);

/**
 * @brief  codec pmu poweroff
 *
 * @param  none
 * @return none
 * @note   none
 */
void drv_pmu_codec_poweroff(void);

#ifdef __cplusplus
}
#endif

#endif

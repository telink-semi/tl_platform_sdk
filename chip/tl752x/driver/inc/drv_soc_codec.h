/*******************************************************************************************************
 *
 * @file    drv_soc_codec.h
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
#ifndef __DRV_SOC_CODEC_H__
#define __DRV_SOC_CODEC_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include "tl_chip.h"
#include "inc/drv_anc.h"
#include "inc/drv_codec.h"

#define CONFIG_ANC_CLK_FRE (ANC_RATE_384k)

typedef void (*soc_codec_anc_fade_done_hook)(void *);
typedef void (*soc_codec_anc_rssi_hook)(void *);

/**
 * @brief This function is to config fade complete callback.
 * @param sel is fade module.
 * @param fade_done_cb is fade compelete callback func.
 */
extern drv_status_t drv_soc_codec_anc_fade_done_hook_register(anc_fade_sel_t sel, soc_codec_anc_fade_done_hook fade_done_cb);

/**
 * @brief This function is to unreigister fade complete callback.
 * @param sel is fade module.
 */
extern drv_status_t drv_soc_codec_anc_fade_done_hook_unregister(anc_fade_sel_t sel);

/**
 * @brief This function is to config rssi threhold triggle callback.
 * @param anc_ch is anc path.
 * @param rssi_module is rssi module.
 * @param rssi_cb is rssi threhold trigger callback func.
 */
extern drv_status_t drv_soc_codec_anc_rssi_hook_register(uint8_t anc_ch, anc_rssi_module_t rssi_module, soc_codec_anc_rssi_hook rssi_cb);

/**
 * @brief This function is to unreigister rssi threhold triggle callback.
 * @param anc_ch is anc path.
 * @param rssi_module is rssi module.
 */
extern drv_status_t drv_soc_codec_anc_rssi_hook_unregister(uint8_t anc_ch, anc_rssi_module_t rssi_module);

/**
 * @brief This function is to init audio codec clk.
 */
extern void drv_soc_codec_msp_init(void);

/**
 * @brief This function is to deinit audio codec clk.
 */
extern void drv_soc_codec_msp_deinit(void);
#ifdef __cplusplus
}
#endif

#endif

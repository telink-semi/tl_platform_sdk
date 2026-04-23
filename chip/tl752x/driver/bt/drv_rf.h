/*******************************************************************************************************
 *
 * @file    drv_rf.h
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
#ifndef __DRV_RF_H__
#define __DRV_RF_H__

#ifdef __cplusplus
extern "C" {    /* C declaration in C++ */
#endif /* _cplusplus */

/**************************** include header *********************************/
#include <stdint.h>

// #define RF_TP_MODE
// #define RF_ADC_48M
// #define RF_VBUCK_MODE
// #define TX_IF_1M
 #define RF_VOLT_1V1
/**************************** function declear *******************************/
extern void drv_rf_init(void);
extern void rf_tp_mode_en(void);
extern void rf_tp_mode_dis(void);
extern void rf_vbuck_mode_en(void);
extern void rf_vbuck_mode_dis(void);
extern void rf_adc_48m_en(void);
extern void rf_adc_48m_dis(void);
extern void rf_volt_1v1(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_RF_H__*/

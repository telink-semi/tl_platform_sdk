/*******************************************************************************************************
 *
 * @file    drv_audio_anc.h
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
#ifndef __DRV_AUDIO_ANC_H__
#define __DRV_AUDIO_ANC_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include "tl_chip.h"

#define AUDIO_ANC_FADE_IN_START_VAL  (0)
#define AUDIO_ANC_FADE_IN_END_VAL    (0x8000000)
#define AUDIO_ANC_FADE_STEP_VAL      (134217)
#define AUDIO_ANC_FADE_INTERVAL_VAL  (1)
#define AUDIO_ANC_FADE_OUT_START_VAL (0x8000000)
#define AUDIO_ANC_FADE_OUT_END_VAL   (0)

#define DRV_ANC_STATE_CLOSE                0x0000U /*!< ANC not yet initialized or disabled                */
#define DRV_ANC_STATE_READY                0x0001U /*!< ANC initialized and ready for use                  */
#define DRV_ANC_STATE_START                0x0002U /*!< ANC is aready start                                */
#define DRV_ANC_STATE_BUSY_FADE_IN         0x0003U /*!< ANC fade in process is ongoing                     */
#define DRV_ANC_STATE_BUSY_FADE_OUT        0x0004U /*!< ANC fade out process is ongoing                    */
#define DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT 0x0005U /*!< ANC switch param fade out process is ongoing       */
#define DRV_ANC_STATE_BUSY_SWITCH_FADE_IN  0x0006U /*!< ANC switch param fade in process is ongoing        */

/**@brief audio dac port rate*/
typedef enum {
    AUDIO_ANC_FS_192K,
    AUDIO_ANC_FS_384K,
    AUDIO_ANC_FS_768K,
    AUDIO_ANC_FS_MAX,
} audio_anc_rate_t;

/**@brief audio dac music path coef decimal wide*/
typedef enum {
    AUDIO_ANC_COEF_DECIMAL_23BIT = 0,
    AUDIO_ANC_COEF_DECIMAL_24BIT,
    AUDIO_ANC_COEF_DECIMAL_25BIT,
    AUDIO_ANC_COEF_DECIMAL_26BIT,
    AUDIO_ANC_COEF_DECIMAL_27BIT,
    AUDIO_ANC_COEF_DECIMAL_28BIT,
    AUDIO_ANC_COEF_DECIMAL_29BIT,
    AUDIO_ANC_COEF_DECIMAL_30BIT,
    AUDIO_ANC_COEF_DECIMAL_MAX,
} audio_anc_coef_decimal_wide_t;

/**@brief audio anc adc port sel*/
typedef enum {
    AUDIO_ANC_PORT_FROM_ADC0 = 0,
    AUDIO_ANC_PORT_FROM_ADC1,
    AUDIO_ANC_PORT_FROM_ADC2,
    AUDIO_ANC_PORT_FROM_ADC3,
    AUDIO_ANC_PORT_FROM_ADC4,
    AUDIO_ANC_PORT_FROM_MAX,
} audio_anc_adc_port_sel_t;

typedef enum {
    AUDIO_ANC_SINGLE_L_FF_MODE,
    AUDIO_ANC_SINGLE_L_FB_MODE,
    AUDIO_ANC_SINGLE_L_HYBRID_MODE,
    AUDIO_ANC_SINGLE_R_FF_MODE,
    AUDIO_ANC_SINGLE_R_FB_MODE,
    AUDIO_ANC_SINGLE_R_HYBRID_MODE,
    AUDIO_ANC_STEREO_FF_MODE,
    AUDIO_ANC_STEREO_FB_MODE,
    AUDIO_ANC_STEREO_HYBRID_MODE,
    AUDIO_ANC_CHANNEL_MODE_NUM,
} audio_anc_channel_mode_t;

/**
 * @brief ANC Callback ID structure definition
 */
typedef enum {
    AUDIO_ANC_START_CPLT_CB_ID = 0x00U,  /*!< Start fade in complete     */
    AUDIO_ANC_STOP_CPLT_CB_ID = 0x01U,   /*!< Stop fade out complete     */
    AUDIO_ANC_SWITCH_CPLT_CB_ID = 0x02U, /*!< Coef param sitch complete  */
    AUDIO_ANC_CB_ID_NUM = 0x03U          /*!< cb num                     */
} audio_anc_cb_id_type_t;

/**@brief audio anc coef cfg*/
typedef struct {
    const int *coef;
    uint32_t coeflevel;
    audio_anc_coef_decimal_wide_t decimal_wide;
} audio_anc_coef_t;

/**@brief audio anc ff path cfg*/
typedef struct {
    audio_anc_adc_port_sel_t adc_ch_sel;
    audio_anc_coef_t coef_cfg;
} audio_anc_ff_cfg_t;

/**@brief audio anc fb path cfg*/
typedef struct {
    audio_anc_adc_port_sel_t adc_ch_sel;
    audio_anc_coef_t coef_cfg;
    drv_flag_status_t sb_fb_en;
} audio_anc_fb_cfg_t;

/**@brief audio dac music path cfg*/
typedef struct {
    audio_anc_ff_cfg_t *al_ff_cfg;
    audio_anc_fb_cfg_t *al_fb_cfg;
    audio_anc_ff_cfg_t *ar_ff_cfg;
    audio_anc_fb_cfg_t *ar_fb_cfg;
    audio_anc_rate_t rate;
    audio_anc_channel_mode_t ch_mode;
} audio_anc_cfg_t;

/**@brief audio anc param cfg*/
typedef struct {
    audio_anc_coef_t al_ff_coef;
    audio_anc_coef_t al_fb_coef;
    audio_anc_coef_t ar_ff_coef;
    audio_anc_coef_t ar_fb_coef;
} audio_anc_coef_param_t;

typedef void (*audio_anc_handle_cb_t)(void *arg);

/**
 * @brief This function is to init anc port context.
 *
 * @param null.
 */
extern void drv_audio_anc_init(void);

/**
 * @brief This function is to deinit anc port context.
 *
 * @param null.
 */
extern void drv_audio_anc_deinit(void);

/**
 * @brief This function is to config anc port.
 *
 * @param cfg is anc port config param.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_ANC_STATE_CLOSE: ANC not yet initialized or disabled
 *              - DRV_ANC_STATE_READY: ANC initialized and ready for use
 *              - DRV_ANC_STATE_START: ANC is aready start
 *              - DRV_ANC_STATE_BUSY_FADE_IN: ANC fade in process is ongoing
 *              - DRV_ANC_STATE_BUSY_FADE_OUT: ANC fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT: ANC switch param fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_IN: ANC switch param fade in process is ongoing
 */
extern int drv_audio_anc_open(audio_anc_cfg_t *cfg);

/**
 * @brief This function is to close anc port.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_ANC_STATE_CLOSE: ANC not yet initialized or disabled
 *              - DRV_ANC_STATE_READY: ANC initialized and ready for use
 *              - DRV_ANC_STATE_START: ANC is aready start
 *              - DRV_ANC_STATE_BUSY_FADE_IN: ANC fade in process is ongoing
 *              - DRV_ANC_STATE_BUSY_FADE_OUT: ANC fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT: ANC switch param fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_IN: ANC switch param fade in process is ongoing
 */
extern int drv_audio_anc_close(void);

/**
 * @brief This function is to start anc port.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_ANC_STATE_CLOSE: ANC not yet initialized or disabled
 *              - DRV_ANC_STATE_READY: ANC initialized and ready for use
 *              - DRV_ANC_STATE_START: ANC is aready start
 *              - DRV_ANC_STATE_BUSY_FADE_IN: ANC fade in process is ongoing
 *              - DRV_ANC_STATE_BUSY_FADE_OUT: ANC fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT: ANC switch param fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_IN: ANC switch param fade in process is ongoing
 */
extern int drv_audio_anc_start(void);

/**
 * @brief This function is to stop anc port.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_ANC_STATE_CLOSE: ANC not yet initialized or disabled
 *              - DRV_ANC_STATE_READY: ANC initialized and ready for use
 *              - DRV_ANC_STATE_START: ANC is aready start
 *              - DRV_ANC_STATE_BUSY_FADE_IN: ANC fade in process is ongoing
 *              - DRV_ANC_STATE_BUSY_FADE_OUT: ANC fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT: ANC switch param fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_IN: ANC switch param fade in process is ongoing
 */
extern int drv_audio_anc_stop(void);

/**
 * @brief This function is to set anc param.
 *
 * @param param is coef param pointer.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_ANC_STATE_CLOSE: ANC not yet initialized or disabled
 *              - DRV_ANC_STATE_READY: ANC initialized and ready for use
 *              - DRV_ANC_STATE_START: ANC is aready start
 *              - DRV_ANC_STATE_BUSY_FADE_IN: ANC fade in process is ongoing
 *              - DRV_ANC_STATE_BUSY_FADE_OUT: ANC fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_OUT: ANC switch param fade out process is ongoing
 *              - DRV_ANC_STATE_BUSY_SWITCH_FADE_IN: ANC switch param fade in process is ongoing
 */
extern int drv_audio_anc_coef_param_set(audio_anc_coef_param_t *param);

/**
 * @brief Register callbacks
 * @param cb_id: User Callback identifier
 *                    a audio_anc_cb_id_type_t ENUM as parameter.
 * @param cb: pointer to private callback function
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_anc_register_cb(audio_anc_cb_id_type_t cb_id, audio_anc_handle_cb_t cb);

/**
 * @brief Unregister callbacks
 * @param cb_id: User Callback identifier
 *                    a audio_anc_cb_id_type_t ENUM as parameter.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_anc_unregister_cb(audio_anc_cb_id_type_t cb_id);

#ifdef __cplusplus
}
#endif

#endif

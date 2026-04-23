/*******************************************************************************************************
 *
 * @file    drv_audio_dac.h
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
#ifndef __DRV_AUDIO_DAC_H__
#define __DRV_AUDIO_DAC_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include "tl_chip.h"
#include "inc/drv_dmac.h"

#if defined(AUDIO_CODEC_V1_0)
#define AUDIO_DAC_ANC_PATH_EN 1
#elif defined(AUDIO_CODEC_V1_1)
#define AUDIO_DAC_ANC_PATH_EN 0
#endif

#define AUDIO_DAC_CH_NUM (0x2)

#define AUDIO_DAC_MUSIC_FADE_EN (1)
#define AUDIO_DAC_DMA_LLP_EN    (0)

/*
 dac dig gain step=0.375db
 0x43 --> -45db
 0x86 --> -19.875
 0xA1 --> -9.75db
 0xBB --> 0db
 0xC9 --> 5.25db
 0xFF --> 25.5db
*/
#define AUDIO_DAC_DIG_GAIN_N_69DB (0x03)
#define AUDIO_DAC_DIG_GAIN_N_66DB (0x0B)
#define AUDIO_DAC_DIG_GAIN_N_63DB (0x13)
#define AUDIO_DAC_DIG_GAIN_N_60DB (0x1B)
#define AUDIO_DAC_DIG_GAIN_N_57DB (0x23)
#define AUDIO_DAC_DIG_GAIN_N_54DB (0x2B)
#define AUDIO_DAC_DIG_GAIN_N_51DB (0x33)
#define AUDIO_DAC_DIG_GAIN_N_48DB (0x3B)
#define AUDIO_DAC_DIG_GAIN_N_45DB (0x43)
#define AUDIO_DAC_DIG_GAIN_N_42DB (0x4B)
#define AUDIO_DAC_DIG_GAIN_N_39DB (0x53)
#define AUDIO_DAC_DIG_GAIN_N_36DB (0x5B)
#define AUDIO_DAC_DIG_GAIN_N_33DB (0x63)
#define AUDIO_DAC_DIG_GAIN_N_30DB (0x6B)
#define AUDIO_DAC_DIG_GAIN_N_27DB (0x73)
#define AUDIO_DAC_DIG_GAIN_N_24DB (0x7B)
#define AUDIO_DAC_DIG_GAIN_N_21DB (0x83)
#define AUDIO_DAC_DIG_GAIN_N_18DB (0x8B)
#define AUDIO_DAC_DIG_GAIN_N_15DB (0x93)
#define AUDIO_DAC_DIG_GAIN_N_12DB (0x9B)
#define AUDIO_DAC_DIG_GAIN_N_9DB  (0xA3)
#define AUDIO_DAC_DIG_GAIN_N_6DB  (0xAB)
#define AUDIO_DAC_DIG_GAIN_N_3DB  (0xB3)
#define AUDIO_DAC_DIG_GAIN_0DB    (0xBB)
#define AUDIO_DAC_DIG_GAIN_P_3DB  (0xC3)
#define AUDIO_DAC_DIG_GAIN_P_6DB  (0xCB)
#define AUDIO_DAC_DIG_GAIN_P_9DB  (0xD3)
#define AUDIO_DAC_DIG_GAIN_P_12DB (0xDB)
#define AUDIO_DAC_DIG_GAIN_P_15DB (0xE3)
#define AUDIO_DAC_DIG_GAIN_P_18DB (0xEB)
#define AUDIO_DAC_DIG_GAIN_P_21DB (0xF3)
#define AUDIO_DAC_DIG_GAIN_P_24DB (0xFB)

#define AUDIO_DAC_FADE_IN_START_VAL  (0)
#define AUDIO_DAC_FADE_IN_END_VAL    (0x8000000)
#define AUDIO_DAC_FADE_STEP_VAL      (134217)
#define AUDIO_DAC_FADE_INTERVAL_VAL  (1)
#define AUDIO_DAC_FADE_OUT_START_VAL (0x8000000)
#define AUDIO_DAC_FADE_OUT_END_VAL   (0)

#define DRV_DAC_STATE_CLOSE 0x0000U /*!< DAC not yet initialized or disabled                */
#define DRV_DAC_STATE_READY 0x0001U /*!< DAC initialized and ready for use                  */

#define DRV_DAC_STREAM_IDLE                 0x0000U /*!< DAC stream is idle                                        */
#define DRV_DAC_STREAM_START                0x0001U /*!< DAC stream is aready start                                */
#define DRV_DAC_STREAM_BUSY_FADE_IN         0x0002U /*!< DAC stream fade in process is ongoing                     */
#define DRV_DAC_STREAM_BUSY_FADE_OUT        0x0003U /*!< DAC stream fade out process is ongoing                    */
#define DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUT 0x0004U /*!< DAC stream eq switch param fade out process is ongoing    */
#define DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN  0x0005U /*!< DAC stream eq switch param fade in process is ongoing     */

typedef void (*audio_dac_tx_hook_t)(void *);
typedef void (*audio_dac_music_path_handle_cb_t)(void *arg);

/** @brief audio dac channel id.*/
typedef enum {
    AUDIO_DAC_CH_0 = DRV_BIT(0),
    AUDIO_DAC_CH_1 = DRV_BIT(1),
    AUDIO_DAC_CH_STEREO = AUDIO_DAC_CH_0 | AUDIO_DAC_CH_1,
} audio_dac_ch_t;

/** @brief audio dac src.*/
typedef enum {
    AUDIO_DAC_SRC_PCM,
    AUDIO_DAC_SRC_ANC,
    AUDIO_DAC_SRC_MAX,
} audio_dac_src_sel_t;

/**@brief audio dac channel rate, lower than 192k music path is suggested*/
typedef enum {
    AUDIO_DAC_FS_8K,
    AUDIO_DAC_FS_16K,
    AUDIO_DAC_FS_24K,
    AUDIO_DAC_FS_32K,
    AUDIO_DAC_FS_48K,
    AUDIO_DAC_FS_44_1K,
    AUDIO_DAC_FS_96K,
    AUDIO_DAC_FS_192K,
    AUDIO_DAC_FS_384K,
    AUDIO_DAC_FS_768K,
    AUDIO_DAC_FS_MAX,
} audio_dac_rate_t;

/**@brief audio dac channel mute command*/
typedef enum {
    AUDIO_DAC_MUTE_DSM,
    AUDIO_DAC_MUTE_ANA,
    AUDIO_DAC_MUTE_MAX,
} audio_dac_mute_cmd_t;

/**@brief audio dac music path rate*/
typedef enum {
    AUDIO_DAC_MUSIC_RATE_8K = 0,
    AUDIO_DAC_MUSIC_RATE_16K,
    AUDIO_DAC_MUSIC_RATE_44_1K,
    AUDIO_DAC_MUSIC_RATE_48K,
    AUDIO_DAC_MUSIC_RATE_96K,
    AUDIO_DAC_MUSIC_RATE_MAX,
} audio_dac_music_rate_t;

/**@brief audio dac music path coef decimal wide*/
typedef enum {
    AUDIO_DAC_COEF_DECIMAL_23BIT = 0,
    AUDIO_DAC_COEF_DECIMAL_24BIT,
    AUDIO_DAC_COEF_DECIMAL_25BIT,
    AUDIO_DAC_COEF_DECIMAL_26BIT,
    AUDIO_DAC_COEF_DECIMAL_27BIT,
    AUDIO_DAC_COEF_DECIMAL_28BIT,
    AUDIO_DAC_COEF_DECIMAL_29BIT,
    AUDIO_DAC_COEF_DECIMAL_30BIT,
    AUDIO_DAC_COEF_DECIMAL_MAX,
} audio_dac_coef_decimal_wide_t;

/**@brief audio dac fifo wide*/
typedef enum {
    AUDIO_DAC_24BIT,
    AUDIO_DAC_16BIT,
    AUDIO_DAC_SAMPLEBITS_MAX,
} audio_dac_sample_bits_t;

typedef enum {
    AUDIO_DAC_AUTX_GAIN_0DB,       /*   0db    */
    AUDIO_DAC_AUTX_GAIN_N_1_15DB,  /* -1.15db  */
    AUDIO_DAC_AUTX_GAIN_N_2_49DB,  /* -2.49db  */
    AUDIO_DAC_AUTX_GAIN_N_4_08DB,  /* -4.08db  */
    AUDIO_DAC_AUTX_GAIN_N_6_02DB,  /* -6.02db  */
    AUDIO_DAC_AUTX_GAIN_N_8_51DB,  /* -8.52db  */
    AUDIO_DAC_AUTX_GAIN_N_12_04DB, /* -12.04db */
    AUDIO_DAC_AUTX_GAIN_N_18_06DB, /* -18.06db */
} audio_dac_autx_gain_t;

/**
 * @brief ANC Callback ID structure definition
 */
typedef enum {
    AUDIO_DAC_MUSIC_START_CPLT_CB_ID = 0x00U,  /*!< Start fade in complete     */
    AUDIO_DAC_MUSIC_STOP_CPLT_CB_ID = 0x01U,   /*!< Stop fade out complete     */
    AUDIO_DAC_MUSIC_SWITCH_CPLT_CB_ID = 0x02U, /*!< EQ param sitch complete  */
    AUDIO_DAC_MUSIC_CB_ID_NUM = 0x03U          /*!< cb num                     */
} audio_dac_music_cb_id_type_t;

/**@brief audio dac channel cfg*/
typedef struct {
    audio_dac_rate_t fs;
    audio_dac_src_sel_t src;
    audio_dac_autx_gain_t autx_gain;
    uint8_t dig_gain;
} audio_dac_cfg_t;

/*@brief audio dac music eq cfg */
typedef struct {
    const int *eq_coef;
    uint32_t eq_coef_level; /**max 10 */
    audio_dac_coef_decimal_wide_t eq_coef_decimal_wide;
    const int *sb_coef;
    uint32_t sb_coef_level; /**max 20 */
    audio_dac_coef_decimal_wide_t sb_coef_decimal_wide;
} audio_dac_eq_param_t;

/*@brief audio dac music path cfg */
typedef struct {
    audio_dac_music_rate_t rate;
    audio_dac_eq_param_t eq_param;
    uint32_t asrc_ppm; /**-1024-1023*/
    uint8_t asrc_en;
    uint8_t gain_control_en;
} audio_dac_music_path_cfg_t;

/** @brief audio dac mode.*/
typedef enum {
    AUDIO_DAC_MODE_MONO,
    AUDIO_DAC_MODE_STEREO,
} audio_dac_ch_mode_t;

/**@brief audio dac dma cfg*/
typedef struct {
    audio_dac_ch_mode_t ch_mode;
    audio_dac_sample_bits_t wide;
    uint8_t fifo_en_bitmap;
    dmac_handle_t *hdma;
} audio_dac_data_format_t;

/**
 * @brief This function is to init dac channel context.
 *
 * @param null.
 */
extern void drv_audio_dac_init(void);

/**
 * @brief This function is to deinit dac channel context.
 *
 * @param null.
 */
extern void drv_audio_dac_deinit(void);

/**
 * @brief This function is to config dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param cfg is dac channel config param.
 * @retval The audio dac channel state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STATE_CLOSE: DAC not yet initialized or disabled
 *              - DRV_DAC_STATE_READY:DAC initialized and ready for use
 */
extern int drv_audio_dac_open(uint8_t ch_bitmap, audio_dac_cfg_t *cfg);

/**
 * @brief This function is to close dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @retval The audio dac channel state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STATE_CLOSE: DAC not yet initialized or disabled
 *              - DRV_DAC_STATE_READY:DAC initialized and ready for use
 */
extern int drv_audio_dac_close(uint8_t ch_bitmap);

/**
 * @brief This function is to start dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STREAM_IDLE: DAC stream is idle
 *              - DRV_DAC_STREAM_START:DAC stream is aready start
 *              - DRV_DAC_STREAM_BUSY_FADE_IN:DAC stream fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_FADE_OUT:DAC stream fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUTA:DAC stream eq switch param fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN:DAC stream eq switch param fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 */
extern int drv_audio_dac_start(uint8_t ch_bitmap);

/**
 * @brief This function is to stop dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STREAM_IDLE: DAC stream is idle
 *              - DRV_DAC_STREAM_START:DAC stream is aready start
 *              - DRV_DAC_STREAM_BUSY_FADE_IN:DAC stream fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_FADE_OUT:DAC stream fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUTA:DAC stream eq switch param fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN:DAC stream eq switch param fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 */
extern int drv_audio_dac_stop(uint8_t ch_bitmap);

/**
 * @brief This function is to mute dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param cmd is dac mute command.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_mute(uint8_t ch_bitmap, audio_dac_mute_cmd_t cmd);

/**
 * @brief This function is to unmute dac channel.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param cmd is dac mute command.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_unmute(uint8_t ch_bitmap, audio_dac_mute_cmd_t cmd);

/**
 * @brief This function is to config dac music path.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param cfg is dac music path config param.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_path_open(uint8_t ch_bitmap, audio_dac_music_path_cfg_t *cfg);

/**
 * @brief This function is to close dac music path.
 *
 * @param ch_bitmap is dac channel bit map.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_path_close(uint8_t ch_bitmap);

/**
 * @brief This function is to enable dac music path asrc module.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param flag is enable/disable.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_asrc_enable(uint8_t ch_bitmap, drv_flag_status_t flag);

/**
 * @brief This function is to set dac music path asrc module ppm.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param ppm is asrc ppm(-1024 - 1023).
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_asrc_ppm_set(uint8_t ch_bitmap, int16_t ppm);

/**
 * @brief This function is to set dac music path eq coef.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param coef is coef address.
 * @param level is coef level.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STREAM_IDLE: DAC stream is idle
 *              - DRV_DAC_STREAM_START:DAC stream is aready start
 *              - DRV_DAC_STREAM_BUSY_FADE_IN:DAC stream fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_FADE_OUT:DAC stream fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUTA:DAC stream eq switch param fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN:DAC stream eq switch param fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 */
extern int drv_audio_dac_music_eq_coef_set(uint8_t ch_bitmap, audio_dac_eq_param_t *eq_param);

/**
 * @brief This function is to config dac data format.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param data_format is data format param.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_set_dma_data_format(audio_dac_data_format_t *data_format);

/**
 * @brief This function is to start dac dma transfer.
 *
 * @param buf is data address to transfer, the address must be memory bus address.
 * @param len is data length by word.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STREAM_IDLE: DAC stream is idle
 *              - DRV_DAC_STREAM_START:DAC stream is aready start
 *              - DRV_DAC_STREAM_BUSY_FADE_IN:DAC stream fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_FADE_OUT:DAC stream fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUTA:DAC stream eq switch param fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN:DAC stream eq switch param fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 */
extern int drv_audio_dac_dma_tx(uint32_t *buf, uint32_t len);

/**
 * @brief This function is to config dac dma tx complete callback.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param tx_cb is callback func.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_tx_complete_cb_register(audio_dac_tx_hook_t tx_cb);

/**
 * @brief This function is to unregister codec dac dma tx complete callback.
 *
 * @param ch_bitmap is dac channel bit map.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_tx_complete_cb_unregister(void);

/**
 * @brief This function is to set dac dig gain.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param gain is dac dig gain.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_set_dig_gain(uint8_t ch_bitmap, uint8_t gain);

/**
 * @brief This function is to set dac autx gain.
 *
 * @param ch_bitmap is dac channel bit map.
 * @param gain is dac autx gain.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_set_autx_gain(uint8_t ch_bitmap, audio_dac_autx_gain_t gain);

/**
 * @brief Register callbacks
 * @param cb_id: User Callback identifier
 *                    a audio_dac_music_cb_id_type_t ENUM as parameter.
 * @param cb: pointer to private callback function
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_path_register_cb(audio_dac_music_cb_id_type_t cb_id, audio_dac_music_path_handle_cb_t cb);

/**
 * @brief Unregister callbacks
 * @param cb_id: User Callback identifier
 *                    a audio_dac_music_cb_id_type_t ENUM as parameter.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_music_path_unregister_cb(audio_dac_music_cb_id_type_t cb_id);

/** @brief  Funcction to get the audio dac stream state.
 * @retval The audio dac stream state. The returned value can be one
 *         of the following:
 *              - DRV_DAC_STREAM_IDLE: DAC stream is idle
 *              - DRV_DAC_STREAM_START:DAC stream is aready start
 *              - DRV_DAC_STREAM_BUSY_FADE_IN:DAC stream fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_FADE_OUT:DAC stream fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_OUTA:DAC stream eq switch param fade out process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 *              - DRV_DAC_STREAM_BUSY_SWITCH_FADE_IN:DAC stream eq switch param fade in process is ongoing(music path is open and AUDIO_DAC_MUSIC_FADE_EN == 1)
 */
extern int drv_audio_dac_get_stream_stat(void);

/**
 * @brief Config dac fifo level
 * @param level: fifo level
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_fifo_level_set(uint32_t level);

/**
 * @brief Get dac fifo cnt
 * @retval uint32_t
 */
extern uint32_t drv_audio_dac_get_fifo_cnt(void);

#if AUDIO_DAC_DMA_LLP_EN
/**
 * @brief  Set the DMA llp head node according to the specified
 *         parameters in the node.
 * @param  hdma: Pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_dmac_llp_head_set(dmac_llp_node_t *node);

/**
 * @brief  Add the DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  hdma: Pointer to a dmac_handle_t structure that contains
 *               the configuration information for the specified DMA Channel.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_list: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_dac_dmac_llp_node_add(dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t *buffer, uint32_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************************************
 *
 * @file    drv_audio_adc.h
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
#ifndef __DRV_AUDIO_ADC_H__
#define __DRV_AUDIO_ADC_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

#include <stdbool.h>
#include "tl_chip.h"
#include "inc/drv_dmac.h"

#if defined(AUDIO_CODEC_V1_0)
#define AUDIO_ADC_ANC_PATH_EN 1
#elif defined(AUDIO_CODEC_V1_1)
#define AUDIO_ADC_ANC_PATH_EN 0
#endif

#if AUDIO_ADC_ANC_PATH_EN
#define AUDIO_ADC_DMA_MODULE    (CPU2_DMAC)
#define AUDIO_ADC_DMA_HANDSHAKE (CPU2_DMAC_HS_DUMP_ANC0_OR_CODEC_TX0)
#define AUDIO_ADC_DMA_CH        (CPU2_DMAC_CH1)
#else
#define AUDIO_ADC_DMA_MODULE    (AUDIO_DMAC)
#define AUDIO_ADC_DMA_HANDSHAKE (12)
#define AUDIO_ADC_DMA_CH        (AUDIO_DMAC_CH1)
#endif

#define AUDIO_ADC_CH_NUM (0x5)
#define AUDIO_ADC_DMA_LLP_EN    (0)

/*
adc dig gain step=0.375db
 0x43 --> -45db
 0x86 --> -19.875
 0xA1 --> -9.75db
 0xBB --> 0db
 0xC9 --> 5.25db
 0xFF --> 25.5db
*/
#define AUDIO_ADC_DIG_GAIN_N_69DB (0x03)
#define AUDIO_ADC_DIG_GAIN_N_66DB (0x0B)
#define AUDIO_ADC_DIG_GAIN_N_63DB (0x13)
#define AUDIO_ADC_DIG_GAIN_N_60DB (0x1B)
#define AUDIO_ADC_DIG_GAIN_N_57DB (0x23)
#define AUDIO_ADC_DIG_GAIN_N_54DB (0x2B)
#define AUDIO_ADC_DIG_GAIN_N_51DB (0x33)
#define AUDIO_ADC_DIG_GAIN_N_48DB (0x3B)
#define AUDIO_ADC_DIG_GAIN_N_45DB (0x43)
#define AUDIO_ADC_DIG_GAIN_N_42DB (0x4B)
#define AUDIO_ADC_DIG_GAIN_N_39DB (0x53)
#define AUDIO_ADC_DIG_GAIN_N_36DB (0x5B)
#define AUDIO_ADC_DIG_GAIN_N_33DB (0x63)
#define AUDIO_ADC_DIG_GAIN_N_30DB (0x6B)
#define AUDIO_ADC_DIG_GAIN_N_27DB (0x73)
#define AUDIO_ADC_DIG_GAIN_N_24DB (0x7B)
#define AUDIO_ADC_DIG_GAIN_N_21DB (0x83)
#define AUDIO_ADC_DIG_GAIN_N_18DB (0x8B)
#define AUDIO_ADC_DIG_GAIN_N_15DB (0x93)
#define AUDIO_ADC_DIG_GAIN_N_12DB (0x9B)
#define AUDIO_ADC_DIG_GAIN_N_9DB  (0xA3)
#define AUDIO_ADC_DIG_GAIN_N_6DB  (0xAB)
#define AUDIO_ADC_DIG_GAIN_N_3DB  (0xB3)
#define AUDIO_ADC_DIG_GAIN_0DB    (0xBB)
#define AUDIO_ADC_DIG_GAIN_P_3DB  (0xC3)
#define AUDIO_ADC_DIG_GAIN_P_6DB  (0xCB)
#define AUDIO_ADC_DIG_GAIN_P_9DB  (0xD3)
#define AUDIO_ADC_DIG_GAIN_P_12DB (0xDB)
#define AUDIO_ADC_DIG_GAIN_P_15DB (0xE3)
#define AUDIO_ADC_DIG_GAIN_P_18DB (0xEB)
#define AUDIO_ADC_DIG_GAIN_P_21DB (0xF3)
#define AUDIO_ADC_DIG_GAIN_P_24DB (0xFB)

#define DRV_ADC_STATE_CLOSE 0x0000U /*!< ADC not yet initialized or disabled                */
#define DRV_ADC_STATE_READY 0x0001U /*!< ADC initialized and ready for use                  */

#define DRV_ADC_STREAM_IDLE  0x0000U /*!< ADC stream is idle                                        */
#define DRV_ADC_STREAM_START 0x0001U /*!< ADC stream is aready start                                */

typedef void (*audio_adc_rx_hook_t)(void *);

/** @brief audio adc ch id.*/
typedef enum {
    AUDIO_ADC_CH_0 = DRV_BIT(0),
    AUDIO_ADC_CH_1 = DRV_BIT(1),
    AUDIO_ADC_CH_2 = DRV_BIT(2),
    AUDIO_ADC_CH_3 = DRV_BIT(3),
    AUDIO_ADC_CH_4 = DRV_BIT(4),
    AUDIO_ADC_CH_ALL = 0x1FU,
} audio_adc_ch_t;

/** @brief audio adc fifo src.*/
typedef enum {
    AUDIO_ADC_FIFO_SRC_ADC,
    AUDIO_ADC_FIFO_SRC_PHN,
    AUDIO_ADC_FIFO_SRC_MAX,
} audio_adc_fifo_src_sel_t;

/**@brief audio adc channel rate, lower than 48K phn path is suggested*/
typedef enum {
    AUDIO_ADC_FS_8K,
    AUDIO_ADC_FS_16K,
    AUDIO_ADC_FS_24K,
    AUDIO_ADC_FS_32K,
    AUDIO_ADC_FS_48K,
    AUDIO_ADC_FS_44_1K,
    AUDIO_ADC_FS_96K,
    AUDIO_ADC_FS_192K,
    AUDIO_ADC_FS_384K,
    AUDIO_ADC_FS_768K,
    AUDIO_ADC_FS_MAX,
} audio_adc_rate_t;

#if AUDIO_ADC_ANC_PATH_EN

/** @brief audio adc phn path id.*/
typedef enum {
    AUDIO_ADC_PHN_MN,
    AUDIO_ADC_PHN_SC,
    AUDIO_ADC_PHN_TR,
    AUDIO_ADC_PHN_MAX,
} audio_adc_phn_ch_t;

/**@brief audio adc phn path rate*/
typedef enum {
    AUDIO_ADC_PHN_RATE_8K,
    AUDIO_ADC_PHN_RATE_16K,
    AUDIO_ADC_PHN_RATE_48K,
    AUDIO_ADC_PHN_RATE_MAX,
} audio_adc_phn_rate_t;

/**@brief audio adc phn path coef decimal wide*/
typedef enum {
    AUDIO_ADC_PHN_COEF_DECIMAL_23BIT = 0,
    AUDIO_ADC_PHN_COEF_DECIMAL_24BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_25BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_26BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_27BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_28BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_29BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_30BIT,
    AUDIO_ADC_PHN_COEF_DECIMAL_MAX,
} audio_adc_phn_coef_decimal_wide_t;

/**@brief audio phn adc channel sel*/
typedef enum {
    AUDIO_ADC_PHN_FROM_ADC0 = 0,
    AUDIO_ADC_PHN_FROM_ADC1,
    AUDIO_ADC_PHN_FROM_ADC2,
    AUDIO_ADC_PHN_FROM_ADC3,
    AUDIO_ADC_PHN_FROM_ADC4,
    AUDIO_ADC_PHN_FROM_MAX,
} audio_adc_phn_port_sel_t;

/**@brief audio adc phn path cfg*/
typedef struct {
    audio_adc_phn_port_sel_t adc_port_sel;
    audio_adc_phn_rate_t rate;
    const int *phn_coef;
    uint32_t phn_coef_level; /**max 10 */
    audio_adc_phn_coef_decimal_wide_t phn_coef_decimal_wide;
    uint8_t gain_control_en;
} audio_adc_phn_path_cfg_t;

#endif


/**@brief audio adc fifo wide*/
typedef enum {
    AUDIO_ADC_24BIT,
    AUDIO_ADC_16BIT,
    AUDIO_ADC_SAMPLEBITS_MAX,
} audio_adc_sample_bits_t;

/**@brief audio adc channel mode*/
typedef enum {
    AUDIO_ADC_MODE_MONO = 0,
    AUDIO_ADC_MODE_STEREO,
    AUDIO_ADC_MODE_TRIPLE,
    AUDIO_ADC_MODE_FOUR,
    AUDIO_ADC_MODE_FIVE,
    AUDIO_ADC_MODE_MAX,
} audio_adc_ch_mode_sel_t;

/*
pga gain step=3db
0x0 --> -12db
0x4 --> 0db
0xF --> 33db
*/
typedef enum {
    AUDIO_ADC_PGA_GAIN_N_12DB,
    AUDIO_ADC_PGA_GAIN_N_9DB,
    AUDIO_ADC_PGA_GAIN_N_6DB,
    AUDIO_ADC_PGA_GAIN_N_3DB,
    AUDIO_ADC_PGA_GAIN_0DB,
    AUDIO_ADC_PGA_GAIN_P_3DB,
    AUDIO_ADC_PGA_GAIN_P_6DB,
    AUDIO_ADC_PGA_GAIN_P_9DB,
    AUDIO_ADC_PGA_GAIN_P_12DB,
    AUDIO_ADC_PGA_GAIN_P_15DB,
    AUDIO_ADC_PGA_GAIN_P_18DB,
    AUDIO_ADC_PGA_GAIN_P_21DB,
    AUDIO_ADC_PGA_GAIN_P_24DB,
    AUDIO_ADC_PGA_GAIN_P_27DB,
    AUDIO_ADC_PGA_GAIN_P_30DB,
    AUDIO_ADC_PGA_GAIN_P_33DB,
} audio_adc_pga_gain_t;

/**@brief audio adc channel cfg*/
typedef struct {
    audio_adc_rate_t fs;
    audio_adc_fifo_src_sel_t fifo_src;
    audio_adc_pga_gain_t pga_gain;
    uint8_t dig_gain;
} audio_adc_cfg_t;

/**@brief audio adc data format cfg
    When ADC is configured for 16-bit resolution and set to sample in either 3-channel or 5-channel scan mode, 
    it actually samples 4 or 6 channels respectively (e.g., when set to 3-channel mode, it samples 4 channels; 
    when set to 5-channel mode, it samples 6 channels),with the data from the last channel always reading 0. */
typedef struct {
    audio_adc_sample_bits_t wide;
    audio_adc_ch_mode_sel_t ch_mode;
    uint8_t fifo_en_bitmap;
    dmac_handle_t *hdma;
} audio_adc_data_format_t;
/**
 * @brief This function is to init adc channel context.
 *
 * @param null.
 */
extern void drv_audio_adc_init(void);

/**
 * @brief This function is to deinit adc channel context.
 *
 * @param null.
 */
extern void drv_audio_adc_deinit(void);

/**
 * @brief This function is to config adc channel.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param cfg is adc channel config param.
 * @retval The audio adc channel state. The returned value can be one
 *         of the following:
 *              - DRV_ADC_STATE_CLOSE: ADC not yet initialized or disabled
 *              - DRV_ADC_STATE_READY: ADC initialized and ready for use
 */
extern int drv_audio_adc_open(uint8_t ch_bitmap, audio_adc_cfg_t *cfg);

/**
 * @brief This function is to close adc channel.
 *
 * @param ch_bitmap is adc channel bit map.
 * @retval The audio adc channel state. The returned value can be one
 *         of the following:
 *              - DRV_ADC_STATE_CLOSE: ADC not yet initialized or disabled
 *              - DRV_ADC_STATE_READY: ADC initialized and ready for use
 */
extern int drv_audio_adc_close(uint8_t ch_bitmap);

/**
 * @brief This function is to start adc channel.
 *
 * @param ch_bitmap is adc channel bit map.
 * @retval The audio adc stream state. The returned value can be one
 *         of the following:
 *              - DRV_ADC_STREAM_IDLE: ADC stream is idle
 *              - DRV_ADC_STREAM_START:ADC stream is aready start
 */
extern int drv_audio_adc_start(uint8_t ch_bitmap);

/**
 * @brief This function is to stop adc channel.
 *
 * @param ch_bitmap is adc channel bit map.
 * @retval The audio adc stream state. The returned value can be one
 *         of the following:
 *              - DRV_ADC_STREAM_IDLE: ADC stream is idle
 *              - DRV_ADC_STREAM_START:ADC stream is aready start
 */
extern int drv_audio_adc_stop(uint8_t ch_bitmap);

#if AUDIO_ADC_ANC_PATH_EN
/**
 * @brief This function is to config adc phn path.
 *
 * @param channel is adc phn path channel.
 * @param cfg is adc phn path config param.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_phn_path_open(audio_adc_phn_ch_t channel, audio_adc_phn_path_cfg_t *cfg);

/**
 * @brief This function is to close adc phn path.
 *
 * @param channel is adc phn path channel.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_phn_path_close(audio_adc_phn_ch_t channel);

/**
 * @brief This function is to set adc phn path eq coef.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param coef is coef address.
 * @param level is coef level.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_phn_coef_set(audio_adc_phn_ch_t channel, const int *coef, uint32_t level);
#endif

/**
 * @brief This function is to config adc data format.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param data_format is data format param.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_set_dma_data_format(audio_adc_data_format_t *data_format);

/**
 * @brief This function is to start adc dma transfer.
 *
 * @param buf is data address to transfer, the address must be memory bus address.
 * @param len is data length by word.
 * @retval The audio adc stream state. The returned value can be one
 *         of the following:
 *              - DRV_ADC_STREAM_IDLE: ADC stream is idle
 *              - DRV_ADC_STREAM_START:ADC stream is aready start
 */
extern int drv_audio_adc_dma_rx(uint32_t *buf, uint32_t len);

/**
 * @brief This function is to config adc dma rx complete callback.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param rx_cb is callback func.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_rx_complete_cb_register(audio_adc_rx_hook_t rx_cb);

/**
 * @brief This function is to unregister codec adc dma rx complete callback.
 *
 * @param ch_bitmap is adc channel bit map.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_rx_complete_cb_unregister(void);

/**
 * @brief Config adc fifo level
 * @param level: fifo level
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_fifo_level_set(uint32_t level);

/**
 * @brief This function is to set adc dig gain.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param gain is adc dig gain.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_set_dig_gain(uint8_t ch_bitmap, uint8_t gain);

/**
 * @brief This function is to set adc pga gain.
 *
 * @param ch_bitmap is adc channel bit map.
 * @param gain is adc pga gain.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_set_pga_gain(uint8_t ch_bitmap, audio_adc_pga_gain_t gain);

#if AUDIO_ADC_DMA_LLP_EN
/**
 * @brief  Set the Audio adc DMA llp head node according to the specified
 *         parameters in the node.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_dmac_llp_head_set(dmac_llp_node_t *node);

/**
 * @brief  Add the Audio DMA llp node according to the specified
 *         parameters in the node and node_list.
 * @param  node: Pointer to a dmac_llp_node_t structure that should be configured.
 * @param  node_next: Pointer to a dmac_llp_node_t structure that next node.
 * @retval drv_status_t
 */
extern drv_status_t drv_audio_adc_dmac_llp_node_add(dmac_llp_node_t *node,  dmac_llp_node_t *node_next, uint32_t *buffer, uint32_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif

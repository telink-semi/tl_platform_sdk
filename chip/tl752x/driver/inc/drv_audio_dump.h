/*******************************************************************************************************
 *
 * @file    drv_audio_dump.h
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
#ifndef __DRV_AUDIO_DUMP_H__
#define __DRV_AUDIO_DUMP_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tl_chip.h"
#include "reg/anc_dump.h"
#include "reg/adc_dump.h"

#define ANC_DUMP_TX_CH_QUEUE_OFFSET  (4UL)
#define ANC_DUMP_TX_CH1_QUEUE_OFFSET (0UL)
#define ANC_DUMP_TX_CH2_QUEUE_OFFSET (4UL)
#define ANC_DUMP_TX_CH3_QUEUE_OFFSET (8UL)
#define ANC_DUMP_TX_CH4_QUEUE_OFFSET (12UL)
#define ANC_DUMP_TX_CH5_QUEUE_OFFSET (16UL)
#define ANC_DUMP_TX_CH6_QUEUE_OFFSET (20UL)
#define ANC_DUMP_TX_CH7_QUEUE_OFFSET (24UL)
#define ANC_DUMP_TX_CH8_QUEUE_OFFSET (28UL)
#define ANC_DUMP_TX_CH9_QUEUE_OFFSET (32UL)

#define ANC_DUMP_RX_CH_QUEUE_OFFSET  (4UL)
#define ANC_DUMP_RX_CH1_QUEUE_OFFSET (0UL)
#define ANC_DUMP_RX_CH2_QUEUE_OFFSET (4UL)

#define ADC_DUMP_RX_CH_QUEUE_OFFSET  (4UL)
#define ADC_DUMP_RX_CH1_QUEUE_OFFSET (0UL)
#define ADC_DUMP_RX_CH2_QUEUE_OFFSET (4UL)
#define ADC_DUMP_RX_CH3_QUEUE_OFFSET (8UL)
#define ADC_DUMP_RX_CH4_QUEUE_OFFSET (12UL)
#define ADC_DUMP_RX_CH5_QUEUE_OFFSET (16UL)

#define ANC_DUMP_TX_FIFO_LVL          (32)
#define ANC_DUMP_RX_FIFO_LVL          (32)

typedef void (*anc_dump_trx_hook)(void *);
typedef void (*adc_dump_trx_hook)(void *);

typedef enum {
    ANC_DUMP_TX_AL_MN_OR_ADC0 = 0x1,
    ANC_DUMP_TX_AL_FF_OR_ADC1 = 0x2,
    ANC_DUMP_TX_AL_FB_OR_ADC2 = 0x3,
    ANC_DUMP_TX_AR_FF_OR_ADC3 = 0x4,
    ANC_DUMP_TX_AR_FB_OR_ADC4 = 0x5,
    ANC_DUMP_TX_AL_SC_OR_DAC0 = 0x6,
    ANC_DUMP_TX_AR_TR_OR_DAC1 = 0x7,
    ANC_DUMP_TX_AL_SB = 0x8,
    ANC_DUMP_TX_AR_SB = 0x9,
} anc_dump_tx_queue_t;

typedef enum {
    ANC_DUMP_RX_DAC0 = 1,
    ANC_DUMP_RX_DAC1 = 2,
} anc_dump_rx_queue_t;

typedef enum {
    ADC_LOAD_MODE = 0,
    ADC_DUMP_MODE = 1,
} adc_dump_mode_t;

typedef enum {
    ADC_DUMP_RX_ADC0 = 1,
    ADC_DUMP_RX_ADC1 = 2,
    ADC_DUMP_RX_ADC2 = 3,
    ADC_DUMP_RX_ADC3 = 4,
    ADC_DUMP_RX_ADC4 = 5,
} adc_dump_rx_queue_t;

typedef enum {
    ANC_DUMP_RX_COMPLETE_HOOK_ID = 0,
    ANC_DUMP_TX_COMPLETE_HOOK_ID = 1,
    ANC_DUMP_HOOK_ID_NUM,
} anc_dump_hook_id_t;

typedef enum {
    ADC_DUMP_RX_COMPLETE_HOOK_ID = 0,
    ADC_DUMP_TX_COMPLETE_HOOK_ID = 1,
    ADC_DUMP_HOOK_ID_NUM,
} adc_dump_hook_id_t;

typedef enum {
    ANC_DUMP_TX_24BIT = 0x00,
    ANC_DUMP_TX_16BIT = 0x01
} anc_dump_tx_sample_bits_t;

typedef enum {
    ANC_DUMP_RX_24BIT = 0x00,
    ANC_DUMP_RX_16BIT = 0x01
} anc_dump_rx_sample_bits_t;

typedef enum {
    ADC_DUMP_TX_24BIT = 0x00,
    ADC_DUMP_TX_16BIT = 0x01
} adc_dump_tx_sample_bits_t;

typedef enum {
    ADC_DUMP_RX_4BIT = 0x00,
} adc_dump_rx_sample_bits_t;

extern void drv_audio_dump_anc_phn_adptive_enable(drv_flag_status_t flag);

extern void drv_audio_dump_anc_tx_adc_ch_enable(uint8_t adc_bitmap, drv_flag_status_t flag);

extern void drv_audio_dump_anc_dac_rx_ch_enable(anc_dump_rx_queue_t dump_ch, drv_flag_status_t flag);

extern void drv_audio_dump_anc_tx_ch_enable(anc_dump_tx_queue_t dump_ch, drv_flag_status_t flag);

extern void drv_audio_dump_anc_tx_bit_wide_sel(anc_dump_tx_sample_bits_t bit_sel);

extern void drv_audio_dump_anc_dma_rx_lvl_set(uint8_t lvl);

extern void drv_audio_dump_anc_dma_tx_lvl_set(uint8_t lvl);

extern void drv_audio_dump_anc_adc_config(uint8_t channel_num, uint64_t order);

extern void drv_audio_dump_anc_dac_rx_bit_wide_sel(anc_dump_rx_sample_bits_t bit_sel);

extern void drv_audio_dump_anc_dac_config(uint8_t channel_num, uint8_t order);

extern uint32_t *drv_audio_dump_anc_get_rxfifo_addr(void);

extern uint32_t *drv_audio_dump_anc_get_txfifo_addr(void);

extern uint32_t drv_audio_dump_anc_dac_get_fifo_cnt(void);
#ifdef __cplusplus
}
#endif
#endif

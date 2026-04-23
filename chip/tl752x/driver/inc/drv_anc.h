/*******************************************************************************************************
 *
 * @file    drv_anc.h
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
#ifndef __DRV_ANC_H__
#define __DRV_ANC_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tl_chip.h"
#include "reg/anc.h"

#define ANC_INSTANCE ANC

#define ANC_ASRC_FERR_MIN (-1024)
#define ANC_ASRC_FERR_MAX (1023)

typedef enum {
    ANC_PATH_L = 0x1,
    ANC_PATH_R = 0x2,
} anc_ch_t;

typedef enum {
    ANC_ADC_FB_FF_PH = 0, /*anc adc port0 FB, anc adc port1 FF, anc adc port2 PH*/
    ANC_ADC_FB_PH_FF,     /*anc adc port0 FB, anc adc port1 PH, anc adc port2 FF*/
    ANC_ADC_FF_FB_PH,     /*anc adc port0 FF, anc adc port1 FB, anc adc port2 PH*/
    ANC_ADC_FF_PH_FB,     /*anc adc port0 FF, anc adc port1 PH, anc adc port2 FB*/
    ANC_ADC_PH_FB_FF,     /*anc adc port0 PH, anc adc port1 FB, anc adc port2 FF*/
    ANC_ADC_PH_FF_FB,     /*anc adc port0 PH, anc adc port1 FF, anc adc port2 FB*/
} anc_adc_map_t;

typedef enum {
    ANC_MUSIC_RATE_8K = 0,
    ANC_MUSIC_RATE_16K,
    ANC_MUSIC_RATE_44_1K,
    ANC_MUSIC_RATE_48K,
    ANC_MUSIC_RATE_96K,
} anc_music_rate_t;

typedef enum {
    ANC_RATE_192k = 0,
    ANC_RATE_384k = 1,
    ANC_RATE_768k = 2,
} anc_anc_rate_t;

typedef enum {
    PHN_RATE_8k = 0,
    PHN_RATE_16k = 1,
    PHN_RATE_48k = 2,
} anc_phn_rate_t;

typedef enum {
    ANC_ADC_PORT0_FROM_ADC0 = 0,
    ANC_ADC_PORT0_FROM_ADC3,
    ANC_ADC_PORT0_FROM_ADC1,
    ANC_ADC_PORT0_FROM_ADC2,
    ANC_ADC_PORT0_FROM_ADC4,
} anc_adc_port0_sel_t;

typedef enum {
    ANC_ADC_PORT1_FROM_ADC1 = 0,
    ANC_ADC_PORT1_FROM_ADC4,
    ANC_ADC_PORT1_FROM_ADC0,
    ANC_ADC_PORT1_FROM_ADC3,
} anc_adc_port1_sel_t;

typedef enum {
    ANC_ADC_PORT_FROM_ADC0 = 0,
    ANC_ADC_PORT_FROM_ADC1,
    ANC_ADC_PORT_FROM_ADC2,
    ANC_ADC_PORT_FROM_ADC3,
    ANC_ADC_PORT_FROM_ADC4,
} anc_adc_port_sel_t;

typedef enum {
    AL_CH_FF = 0,
    AL_CH_FB,
    AR_CH_FF,
    AR_CH_FB,
} anc_nc_ch_t;

typedef enum {
    ANC_FF = 0,
    ANC_FB,
} anc_path_ch_t;

typedef enum {
    ANC_RSSI0 = 0,
    ANC_RSSI1,
    ANC_RSSI2,
    ANC_RSSI3,
    ANC_RSSI4,
    ANC_RSSI_NUM,
} anc_rssi_module_t;

typedef enum {
    ANC_SB_IIR = 0,
    ANC_HF_IIR,
    ANC_FF_IIR,
    ANC_FB_IIR,
} anc_rssi_sel_t;

typedef enum {
    ANC_ADC_PORT0 = 0,
    ANC_ADC_PORT1,
    ANC_ADC_PORT2,
} anc_adc_ch_t;

typedef enum {
    ANC_PHN_CH_MN = 0,
    ANC_PHN_CH_SC,
    ANC_PHN_CH_TR,
} anc_phn_ch_t;

typedef enum {
    ANC_DAC_SOURCE_FROM_PCM = 0,
    ANC_DAC_SOURCE_FROM_ANC = 1,
} e_anc_dac_source_t;

typedef enum {
    ANC_ADC_CH_FIFO_SOURCE_FROM_ADC = 0,
    ANC_ADC_CH_FIFO_SOURCE_FROM_ANC = 1,
} e_anc_adc_fifo_source_t;

typedef enum {
    AL_FF_IIR_COEFF = 0,
    AL_FB_IIR_COEFF,
    AL_SB_IIR_COEFF,
    AL_EQ_IIR_COEFF,
    AL_MN_IIR_COEFF,
    AR_FF_IIR_COEFF,
    AR_FB_IIR_COEFF,
    AR_SB_IIR_COEFF,
    AR_EQ_IIR_COEFF,
    AR_TR_IIR_COEFF,
    AL_SC_IIR_COEFF,
    ANC_IIR_COEFF_SEL_NUM,
} anc_iir_coeff_sel_t;

typedef enum {
    AL_FB_FADE,
    AL_SB_FADE,
    AL_FF_FADE,
    AR_FB_FADE,
    AR_SB_FADE,
    AR_FF_FADE,
    ANC_FADE_NUM,
} anc_fade_sel_t;

typedef enum {
    AL_MN_GAIN_CONTROL,
    AL_SC_GAIN_CONTROL,
    AL_EQ_GAIN_CONTROL,
    AR_TR_GAIN_CONTROL,
    AR_EQ_GAIN_CONTROL,
    ANC_GAIN_CONTROL_NUM,
} anc_gain_control_sel_t;

typedef struct {
    uint16_t env_smooth_comp_fix;
    uint16_t env_smooth_fix;
    uint16_t out_gain_smooth_1_comp_fix;
    uint16_t out_gain_smooth_1_fix;
    uint16_t out_gain_smooth_2_comp_fix;
    uint16_t out_gain_smooth_2_fix;
} anc_agin_control_smooth_param_t;

typedef enum {
    IIR_DECIMAL_23BIT = 0,
    IIR_DECIMAL_24BIT,
    IIR_DECIMAL_25BIT,
    IIR_DECIMAL_26BIT,
    IIR_DECIMAL_27BIT,
    IIR_DECIMAL_28BIT,
    IIR_DECIMAL_29BIT,
    IIR_DECIMAL_30BIT,
} anc_iir_decimal_wide_t;

typedef enum {
    ANC_CLK_24M = 0,
    ANC_CLK_48M,
    ANC_CLK_96M,
} anc_clk_cfg_t;

/*@brief audio dac music eq cfg */
typedef struct {
    const int *eq_iir_coef;
    uint32_t eq_iir_level;
    anc_iir_decimal_wide_t eq_iir_decimal_wide;
    const int *sb_iir_coef;
    uint32_t sb_iir_level;
    anc_iir_decimal_wide_t sb_iir_decimal_wide;
} anc_music_eq_param_t;

typedef struct {
    anc_music_rate_t rate;
    anc_music_eq_param_t eq_param;
    uint32_t asrc_ppm;
    uint8_t asrc_en;
    uint8_t gain_control_en;
} anc_music_path_cfg_t;

typedef struct {
    anc_adc_port_sel_t adc_ch_sel;
    anc_phn_rate_t phn_rate;
    const int *iir_coef;
    uint32_t iir_level;
    anc_iir_decimal_wide_t iir_decimal_wide;
    uint8_t gain_control_en;
} anc_phn_cfg_t;

typedef struct {
    const int *coef;
    uint32_t coeflevel;
    anc_iir_decimal_wide_t decimal_wide;
} anc_coef_t;

typedef struct {
    anc_adc_port_sel_t adc_ch_sel;
    anc_coef_t coef_cfg;
} anc_path_ff_cfg_t;

typedef struct {
    anc_adc_port_sel_t adc_ch_sel;
    anc_coef_t coef_cfg;
    drv_flag_status_t sb_fb_en;
} anc_path_fb_cfg_t;

void drv_anc_set_adc_map(uint8_t anc_bitmap, anc_adc_map_t map);
void drv_anc_set_music_rate(uint8_t anc_bitmap, anc_music_rate_t rate);
void drv_anc_set_anc_rate(uint8_t anc_bitmap, anc_anc_rate_t rate);
void drv_anc_set_phn_rate(uint8_t anc_bitmap, anc_phn_rate_t rate);
void drv_anc_adc_port0_ch_sel(uint8_t anc_bitmap, anc_adc_port0_sel_t adc_ch);
void drv_anc_adc_port1_ch_sel(uint8_t anc_bitmap, anc_adc_port1_sel_t adc_ch);
void drv_anc_phn_adc_port_ch_sel(anc_phn_ch_t phn_ch, anc_adc_port_sel_t adc_ch);
void drv_anc_nc_adc_port_ch_sel(anc_nc_ch_t nc_ch, anc_adc_port_sel_t adc_ch);
void drv_anc_phn_ch_enable(anc_phn_ch_t phn_ch, drv_flag_status_t flag);
void drv_anc_dig_eq_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_fb_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_ff_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_bypass_phn_adp_enable(anc_phn_ch_t phn_ch, drv_flag_status_t flag);
void drv_anc_music_96k_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_sb_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_path_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_sb_fb_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_music_sb_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_dwn_fb_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_bypass_wf_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_nc_iir_bypass_enable(anc_nc_ch_t nc_ch, drv_flag_status_t flag);
void drv_anc_nc_iir_enable(anc_nc_ch_t nc_ch, drv_flag_status_t flag);

void drv_anc_rssi_size_set(uint8_t anc_bitmap, anc_rssi_module_t module, uint8_t size);
void drv_anc_rssi_sel(uint8_t anc_bitmap, anc_rssi_sel_t sel, uint8_t flag);
void drv_anc_rssi_intr_mask(uint8_t anc_bitmap, anc_rssi_module_t sel, uint8_t flag);
uint32_t drv_anc_rssi_get_intr_status(void);
void drv_anc_rssi_valid_realtime_update(uint8_t anc_bitmap, anc_rssi_module_t sel, uint8_t flag);
void drv_anc_rssi_threshold_set(uint8_t anc_bitmap, anc_rssi_module_t sel, uint8_t min, uint8_t max);
void drv_anc_rssi_valid_clear(uint8_t anc_bitmap, anc_rssi_module_t sel);

void drv_anc_adc_fifo_source_sel(uint8_t anc_bitmap, anc_adc_ch_t anc_adc_ch, e_anc_adc_fifo_source_t fifo_sel);
void drv_anc_dac_source_sel(uint8_t anc_bitmap, e_anc_dac_source_t source_sel);
void drv_anc_adc_ch_delay_set(uint8_t anc_bitmap, anc_adc_ch_t anc_adc_ch, drv_flag_status_t flag);
void drv_anc_rssi_db_read(uint8_t anc_bitmap, anc_rssi_module_t module, uint8_t *size);
void drv_anc_phn_iir_fb_set(anc_phn_ch_t phn_ch, uint8_t value);
void drv_anc_phn_iir_enable(anc_phn_ch_t phn_ch, drv_flag_status_t flag);
void drv_anc_phn_iir_bypass_enable(anc_phn_ch_t phn_ch, drv_flag_status_t flag);
void drv_anc_phn_iir_fill_set(anc_phn_ch_t phn_ch, uint8_t value);
void drv_anc_clk_48m_enable(drv_flag_status_t flag);
void drv_anc_clk_96m_enable(drv_flag_status_t flag);
void drv_anc_clk_config(anc_clk_cfg_t clk);
void drv_anc_iir_coeff_sel(anc_iir_coeff_sel_t sel);
void drv_anc_iir_coeff_en(drv_flag_status_t flag);
void drv_anc_iir_coeff_decimal_wide_set(anc_iir_coeff_sel_t sel, anc_iir_decimal_wide_t wide);
drv_status_t drv_anc_filter_coef_set(anc_iir_coeff_sel_t coff_sel, const int *buf);
drv_status_t drv_anc_filter_level_coef_set(anc_iir_coeff_sel_t coff_sel, const int *buf, uint32_t level);
drv_status_t drv_anc_filter_level_set(anc_iir_coeff_sel_t coff_sel, uint32_t level);
drv_status_t drv_anc_filter_coef_set_by_levels(anc_iir_coeff_sel_t coff_sel, const int *buf, uint32_t levels);
drv_status_t drv_anc_filter_enable(anc_iir_coeff_sel_t coff_sel, drv_flag_status_t flag);
drv_status_t drv_anc_filter_bypass(anc_iir_coeff_sel_t coff_sel, drv_flag_status_t flag);

void drv_anc_fade_en(anc_fade_sel_t sel, drv_flag_status_t flag);
void drv_anc_fade_coeff_set(anc_fade_sel_t sel, uint32_t coeff);
void drv_anc_fade_step_set(anc_fade_sel_t sel, uint32_t step);
void drv_anc_fade_interval_set(anc_fade_sel_t sel, uint32_t interval);
void drv_anc_fade_target_set(anc_fade_sel_t sel, uint32_t target);
void drv_anc_fade_target_get(anc_fade_sel_t sel, uint32_t *target);

void drv_anc_fade_wait_en_sync(anc_fade_sel_t sel);
uint32_t drv_anc_fade_get_status(anc_fade_sel_t sel);
uint32_t drv_anc_fade_get_intr_status(void);
void drv_anc_fade_wait_done(anc_fade_sel_t sel);
void drv_anc_fade_done_intr_mask(anc_fade_sel_t sel, drv_flag_status_t flag);
void drv_anc_fade_done_intr_clear(anc_fade_sel_t sel);

void drv_anc_gain_control_delay_point_set(anc_gain_control_sel_t sel, uint16_t delay);
void drv_anc_gain_control_bypass_enable(anc_gain_control_sel_t sel, drv_flag_status_t flag);
void drv_anc_gain_control_enable(anc_gain_control_sel_t sel, drv_flag_status_t flag);
void drv_anc_gain_control_smooth_param_set(anc_gain_control_sel_t sel, anc_agin_control_smooth_param_t *param);

void drv_anc_asrc_enable(uint8_t anc_bitmap, drv_flag_status_t flag);
void drv_anc_asrc_set_ferr(uint8_t anc_bitmap, int16_t err);

void drv_anc_music_path_init(uint8_t anc_bitmap, anc_music_path_cfg_t *cfg);
void drv_anc_phn_path_init(anc_phn_ch_t phn_ch, anc_anc_rate_t anc_rate, anc_phn_cfg_t *cfg);
void drv_anc_ff_path_init(uint8_t anc_bitmap, anc_path_ff_cfg_t *cfg);
void drv_anc_fb_path_init(uint8_t anc_bitmap, anc_path_fb_cfg_t *cfg);
void drv_anc_fade(anc_fade_sel_t sel, uint32_t start, uint32_t step, uint32_t interval, uint32_t target);

#ifdef __cplusplus
}
#endif

#endif

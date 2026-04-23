/*******************************************************************************************************
 *
 * @file    drv_codec.h
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
#ifndef __DRV_CODEC_H__
#define __DRV_CODEC_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "tl_chip.h"
#include "reg/codec.h"
/*************************** macro definition ********************************/
//#define CODEC_FPGA_TEST          0
/*******************adc config***********************/
/*****************************************************************************
 pga gain default 0db
 -6db -- 41.25db, step = 0.75db
 st1: |0x00   |0x01   |0x02   |0x03   |0x04   |0x05   |0x06  |0x07  |
      |-6db   |0db    |6db    |12db   |18db   |24db   |30db  |36db  |
 -------------------------------------------------------------------|
 st2: |0x00   |0x01   |0x02   |0x03   |0x04   |0x05   |0x06  |0x07  |
      |0db    |0.75db |1.5db  |2.25db |3db    |3.75db |4.5db |5.25db|
******************************************************************************/

/*******************dac config***********************/
/******************************************************************************
 set digital gain
 0xA1 --> -9.75db
 0x86 --> -19.875
 0x6B --> -30db
 0x43 --> -45db
 0xC9 --> 5.25db
 0xFF --> 25.5db
 ******************************************************************************/
#define INIT_DAC_DIGITAL_GAIN (0xbb)

/* set analog gain */
/* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07 */
/* -18db -15db -12db -9db  -6db  -3db  0db     3db */
#define INIT_DAC_ANA_GAIN (6)

/* 00: 700mVpp;    01: 1050mVpp; 02: 1400mVpp; 03: 1750mVpp default */
/* 04: 2100mVpp; 05: 2450mVpp; 06: 2800mVpp; 07: 3150mVpp */
#define INIT_VPP_RANGE (7)

/*For codec dre test SNR115 dB */
#define DRV_CODEC_DAC_DSS_ENABLE 0

/*For codec nosie gate test SNR 120dB with ldo_cdc_sel:6 in drv_pmu_ex.c*/
#define DRV_CODEC_DAC_NG_ENABLE  0

#ifdef CODEC_FPGA_TEST
/*For codec ofc */
#define DRV_CODEC_DAC_OFC_ENABLE 0
#else 
#define DRV_CODEC_DAC_OFC_ENABLE 1
#endif

#define CODEC_CH_MASK(ch) (1 << (ch))

/**************************** type definition ********************************/

typedef enum {
    CODEC_ADC_CH0 = 0x1,
    CODEC_ADC_CH1 = 0x2,
    CODEC_ADC_CH2 = 0x4,
    CODEC_ADC_CH3 = 0x8,
    CODEC_ADC_CH4 = 0x10,
} codec_adc_ch_t;

typedef enum {
    CODEC_DAC_CH0 = 0x1,
    CODEC_DAC_CH1 = 0x2,
} codec_dac_ch_t;

typedef enum {
    DAC1_SOFT_RESET = 0,
    DAC0_SOFT_RESET,
    ADC3_SOFT_RESET,
    ADC2_SOFT_RESET,
    ADC1_SOFT_RESET,
    ADC0_SOFT_RESET,
    DMIC_SOFT_RESET,
    DAC_SOFT_RESET,
    CLK_6P144_SOFT_RESET = 9,
    ADC4_SOFT_RESET,
    DMIC1_SOFT_RESET,
    DMIC0_SOFT_RESET,
} codec_soft_reset_module_t;

typedef enum e_dac_sample_bits {
    CODEC_DAC_24BIT = 0x00,
    CODEC_DAC_16BIT = 0x01
} dac_sample_bits_t;

typedef enum e_adc_sample_bits {
    CODEC_ADC_24BIT = 0x00,
    CODEC_ADC_16BIT = 0x01
} adc_sample_bits_t;

typedef enum e_adc_dma_ch_sel {
    CODEC_ADC_DMA_CH0 = 0,
    CODEC_ADC_DMA_CH1 = 1,
} adc_dma_ch_sel_t;

typedef enum e_dac_dma_ch_sel {
    CODEC_DAC_DMA_CH0 = 0,
    CODEC_DAC_DMA_CH1 = 1,
} dac_dma_ch_sel_t;

typedef enum {
    CODEC_ADC_CH_MONO = 0,
    CODEC_ADC_CH_STEREO,
    CODEC_ADC_CH_TRIPLE,
    CODEC_ADC_CH_FOUR,
    CODEC_ADC_CH_FIVE,
} adc_ch_mode_sel_t;

typedef enum {
    CODEC_DAC_CH_MONO = 0,
    CODEC_DAC_CH_STEREO,
} dac_ch_mode_sel_t;

typedef enum {
    CODEC_FS_8K,
    CODEC_FS_16K,
    CODEC_FS_24K,
    CODEC_FS_32K,
    CODEC_FS_48K,
    CODEC_FS_44_1K,
    CODEC_FS_96K,
    CODEC_FS_192K,
    CODEC_FS_384K,
    CODEC_FS_768K,
    CODEC_FS_MAX,
} codec_fs_t;

typedef enum {
    CODEC_ADC_FPGA_SRC_SDM = 0,
    CODEC_ADC_FPGA_SRC_ADC0 = 2,
    CODEC_ADC_FPGA_SRC_ADC1 = 3,
} adc_fpga_src_sel_t;

typedef struct {
    uint32_t rate;
    codec_fs_t fs;
    unsigned int mclk;
    unsigned char pwr_mode;
    unsigned char rate_sel;
} codec_fs_config_t;

/*************************** function declear *******************************/
extern void drv_codec_adc_ana_enable(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_dig_enable(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_cg_clkinv_enable(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_hpf_fc_set(uint8_t adc_bitmap, uint8_t hfp_fc);
extern void drv_codec_adc_hpf_en(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_rate_sel_set(uint8_t adc_bitmap, uint8_t pwr_mode, uint8_t rate_sel);
extern void drv_codec_adc_coef_se1(uint8_t adc_bitmap, uint8_t sel);
extern void drv_codec_adc_dig_gain_set(uint8_t adc_bitmap, uint8_t gain);
extern void drv_codec_adc_pga_gain_set(uint8_t adc_bitmap, uint8_t gain);
extern void drv_codec_adc_pga_se_mode_pn_enable(uint8_t adc_bitmap, drv_flag_status_t pflag, drv_flag_status_t nflag);
extern void drv_codec_adc_pga_diff_mode_enable(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_ib_sel(uint8_t adc_bitmap, uint8_t current);
extern void drv_codec_adc_pag_ib_sel(uint8_t adc_bitmap, uint8_t current);
extern void drv_codec_adc_clk_inv(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_int_rst(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_data_sw_enable(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_adc_ch_init(uint8_t adc_bitmap, const codec_fs_config_t *fs_config, uint8_t pga_gain, uint8_t dig_gain);

extern void drv_codec_rec_ldo_vol_trim_set(uint8_t val);
extern void drv_codec_rec_adc_ldo_trim_set(uint8_t val);
extern void drv_codec_rec_lowp_mode_set(drv_flag_status_t flag);
extern void drv_codec_rec_vref_lowp_mode_set(drv_flag_status_t flag);
extern void drv_codec_rec_vrefp18_enp_set(drv_flag_status_t flag);
extern void drv_codec_rec_vcom_enp_set(drv_flag_status_t flag);
extern void drv_codec_rec_test_sel_set(uint8_t val);
extern void drv_codec_rec_ib_sel_set(uint8_t current);
extern void drv_codec_rec_seli_vref1p8_set(uint8_t current);
extern void drv_codec_rec_seli_vcom_set(uint8_t val);
extern void drv_codec_vref_mode_0p8_set(drv_flag_status_t flag);
extern void drv_codec_vref_fast_startup_0p8_set(drv_flag_status_t flag);
extern void drv_codec_vref_0p8_set(drv_flag_status_t flag);
extern void drv_codec_module_soft_reset(codec_soft_reset_module_t module);

extern void drv_codec_dac_dig_enable(uint8_t dac_bitmap, drv_flag_status_t flag);
extern void drv_codec_dac_cg_clkinv_enable(uint8_t dac_bitmap, drv_flag_status_t flag);
extern void drv_codec_dac_rate_sel_set(uint8_t dac_bitmap, uint8_t pwr_mode, uint8_t rate_sel);
extern void drv_codec_dac_dig_gain_set(uint8_t dac_bitmap, uint8_t gain);
extern void drv_codec_dac_mute_thre_set(uint8_t dac_bitmap, uint8_t thre);
extern void drv_codec_dac_coef_se1(uint8_t dac_bitmap, uint8_t sel);
extern void drv_codec_dac_mute_win_set(uint8_t dac_bitmap, uint8_t sel);
extern void drv_codec_dac_dem_mute_set(drv_flag_status_t flag);
extern void drv_codec_dac_autx_ch_disable(uint8_t dac_bitmap, drv_flag_status_t flag);
extern void drv_codec_dac_autx_powerup_set(drv_flag_status_t flag);
extern void drv_codec_dac_ed_dss_thresh_set(uint8_t thre);
extern void drv_codec_dac_ed_dss_rls_time_set(uint8_t time);
extern void drv_codec_dac_dem_ed_enable(drv_flag_status_t flag);
extern void drv_codec_dac_dem_ed_threshlow_set(uint8_t thre);
extern void drv_codec_dac_dem_ed_threshhigh_set(uint8_t thre);
extern void drv_codec_dac_ed_dss_enable(drv_flag_status_t flag);
extern void drv_codec_dac_ed_rls_time_set(uint8_t time);
extern void drv_codec_dac_dem_enable(drv_flag_status_t flag);
extern void drv_codec_dac_dem_dynamic_powerup(drv_flag_status_t flag);
extern void drv_codec_dac_ed_dss_zcd_time_sel(uint8_t time);
extern void drv_codec_dac_ed_dss_zcd_timer_enable(drv_flag_status_t flag);
extern void drv_codec_dac_ed_dss_zcd_enable(drv_flag_status_t flag);
extern void drv_codec_dac_ed_ng_enable(drv_flag_status_t flag);
extern void drv_codec_dac_ed_ng_thresh_set(uint8_t thre);
extern void drv_codec_dac_ed_ng_rls_time_set(uint8_t time);
extern void drv_codec_dac_ed_ng_zcd_time_sel(uint8_t time);
extern void drv_codec_dac_ed_ng_zcd_timer_enable(drv_flag_status_t flag);
extern void drv_codec_dac_ed_ng_zcd_enable(drv_flag_status_t flag);
extern void drv_codec_dac_dsm_enable(drv_flag_status_t flag);
extern void drv_codec_dac_dss_diggain_enable(drv_flag_status_t flag);
extern void drv_codec_dac_dss_multiply_set(uint8_t dac_bitmap, uint8_t val);
extern void drv_codec_dac_dss_divide_set(uint8_t dac_bitmap, uint8_t val);
extern void drv_codec_dac_dss_dout_dly1cycle_set(uint8_t val);
extern void drv_codec_dac_dss_lvl_dly2afe_set(uint8_t val);
extern void drv_codec_dac_ed_dss_lvl_dly2afe_set(uint8_t val);
extern void drv_codec_dac_ed_dss_forcelow(drv_flag_status_t flag);
extern void drv_codec_dac_ed_dss_forcehigh(drv_flag_status_t flag);
extern void drv_codec_dac_autx_gain_user_set(uint8_t dac_bitmap, uint8_t gain);
extern void drv_codec_dac_hpamp_ofc_enable(drv_flag_status_t flag);
extern void drv_codec_dac_autx_ofc_0db_enable(drv_flag_status_t flag);
extern void drv_codec_dac_autx_ofc_neg18db_enable(drv_flag_status_t flag);
extern void drv_codec_dac_autx_iref_pdb_enable(drv_flag_status_t flag);
extern void drv_codec_dac_autx_mute_enable(uint8_t dac_bitmap, drv_flag_status_t flag);
extern void drv_codec_dac_pgood_cdc_set(uint8_t val);
extern void drv_codec_dac_hpf_fc_set(uint8_t dac_bitmap, uint8_t hfp_fc);
extern void drv_codec_dac_hpf_enable(uint8_t dac_bitmap, drv_flag_status_t flag);
extern uint32_t drv_codec_dac_get_hpamp_ofc_status(uint8_t dac_bitmap);
extern uint32_t drv_codec_dac_get_autx_ofc_status(uint8_t dac_bitmap);
extern void drv_codec_dac_limiter_set(uint8_t dac_bitmap, uint32_t thre, uint8_t ratio);
extern void drv_codec_dac_limiter_en(uint8_t dac_bitmap, drv_flag_status_t flag);
extern void drv_codec_intr_enable(drv_flag_status_t flag);
extern void drv_codec_dac_autx_limit_det_intr_enable(drv_flag_status_t flag);
extern uint32_t drv_codec_dac_get_autx_iref_ok_status(void);
extern void drv_codec_dac_ch_init(uint8_t dac_bitmap, const codec_fs_config_t *fs_config, uint8_t ana_gain, uint8_t dig_gain);

#ifdef CODEC_FPGA_TEST
extern void drv_codec_fpga_adc_rd_en(uint8_t adc_bitmap, drv_flag_status_t flag);
extern void drv_codec_fpga_adc_set_pga(uint8_t adc_bitmap, uint8_t gain);
extern void drv_codec_fpga_adc_src_sel(uint8_t adc_bitmap, adc_fpga_src_sel_t sel);
extern void drv_codec_fpga_dac_hpa_sd_en(drv_flag_status_t flag);
extern void drv_codec_fpga_dac_sel(uint8_t dac_bitmap);
#endif
extern const codec_fs_config_t *drv_codec_fs_config_get(codec_fs_t fs);
extern const codec_fs_config_t *drv_codec_fs_config_get_by_rate(uint32_t rate);
#ifdef __cplusplus
}
#endif

#endif

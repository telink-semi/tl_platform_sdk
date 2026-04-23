/*******************************************************************************************************
 *
 * @file    tl752x.h
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
#ifndef __TL752X_H__
#define __TL752X_H__

#include <stdio.h>
#include <stdlib.h>

#if defined(MCU_CORE_TL752X_D25F)
#include "arch/d25f/ecall/ecall.h"
#include "hal/plic.h"
#include "hal/mcu_core.h"
#include <stdint-gcc.h>

#elif defined(MCU_CORE_TL752X_N22)
#include "arch/n22/ecall/ecall.h"
#include "hal/clic.h"
#include "hal/mcu_core.h"
#include <stdint-gcc.h>
#elif defined(MCU_CORE_TL752X_DSP)
#include "syscall.h"
#include "xtensa_intr.h"
#endif

/* IP include */
#include "modules/cpr.h"
#include "modules/gpio.h"
#include "modules/pmu.h"
#include "reg/uart.h"
#include "reg/sdmmc.h"
#include "reg/dma.h"
#include "reg/pdm.h"
#include "reg/pdmc.h"
#include "reg/tdm.h"
#include "reg/codec.h"
#include "reg/ipcm.h"
#include "modules/sys_ctl.h"
#include "reg/efuse.h"
#include "reg/spi.h"
#include "reg/spdif.h"
#include "reg/gpadc.h"
#include "reg/resample.h"
#include "reg/trng.h"
#include "reg/anc.h"
#include "reg/anc_dump.h"
#include "reg/adc_dump.h"
#include "compiler.h"
#include "reg/systimer.h"

/*
 *======================================================================================================
                                ##### tl752x_address_mapping #####
 *======================================================================================================
*/
#define FLASH0_BASE       (0x10000000UL)
#define FLASH1_BASE       (0x18000000UL)
#define MCUA_SYS_BUS_BASE (0x40000000UL)
#define MCUB_SYS_BUS_BASE (0x50000000UL)
#define SHRAM1_BASE       (0x50060000UL)
#define MCUC_SYS_BUS_BASE (0xB0000000UL)
#define CPU1_DMAC_BASE    (0x502F0000UL)
#define CPU1_WDT_BASE     (0x50300000UL)
#define GP_ADC_BASE       (0x50310000UL)
#define I2C2_BASE         (0x50320000UL)
#define UART0_BASE        (0x50330000UL)
#define UART4_BASE        (0x50340000UL)
#define TAHDT_BASEE         (0x50425000UL)
#define DWC_SSI0_BASE     (0x70000000UL)
#define DWC_SSI1_BASE     (0x78000000UL)
#define CPR_BASE          (0xA0000000UL)
#define EFUSE_BASE        (0xA0008000UL)
#define GPIO_BASE         (0xA0020000UL)
#define CPU0_WDT_BASE     (0xA0030000UL)
#define UART3_BASE        (0xA0040000UL)
#define I2C0_BASE         (0xA0050000UL)
#define UART2_BASE        (0xA0060000UL)
#define SPIM_BASE         (0xA0070000UL)
#define SPIS_BASE         (0xA0080000UL)
#define I2C1_BASE         (0xA0090000UL)
#define TIMER0_3_BASE     (0xA00A0000UL)
#define TIMER4_7_BASE     (0xA00C0000UL)
#define UART1_BASE        (0xA00B0000UL)
#define SYS_TIMER_BASE    (0xA00E0000UL)
#define RTC_BASE          (0xA0100000UL)
#define PMU_BASE          (0xA0120000UL)
#define SYS_CTL_BASE      (0xA0200000UL)
#define CPU_DMAC_BASE     (0xA0210000UL)
#define TRNG_BASE         (0xA0250000UL)
#define USB_BASE          (0xA0260000UL)
#define AUDIO_DMAC_BASE   (0xA0290000UL)
#define SDMMC_BASE        (0xA02A0000UL)
#define USB1_BASE         (0xA02C0000UL)
#define SWS_BASE          (0xA02D0000UL)
#define TDM0_BASE         (0xA0300000UL) /* I2S0 */
#define TDM1_BASE         (0xA0310000UL) /* I2S1 */
#define TDM2_BASE         (0xA0320000UL)
#define PDM0_BASE         (0xA0330000UL)
#define PDM1_BASE         (0xA0340000UL)
#define PDMC_BASE         (0xA0350000UL)
#define TDM3_BASE         (0xA0360000UL) /* I2S3 */
#define SPDIF_REG_BASE    (0xA0370000UL)
#define RESAMPLE_REG_BASE (0xA0380000UL)
#define CPU2_DMAC_BASE    (0xB0000000UL)
#define CPU2_DTCM_BASE    (0xB2000000UL)
#define CPU2_ITCM_BASE    (0xB2100000UL)
#define CODEC_BASE        (0xB0500000UL)
#define ANC_BASE          (0xB0510000UL)
#define ANC_DUMP_BASE     (0xB0570000UL)
#define ADC_DUMP_BASE     (0xB0571000UL)
#define CPU2_WDT_BASE     (0xB0580000UL)
#define SWIRE_BASE_ADDR   (0xa02d0000UL)

#if defined(MCU_CORE_TL752X_D25F)
#define CPU_SYS_BUS (MCUA_SYS_BUS_BASE)
#elif defined(MCU_CORE_TL752X_N22)
#define CPU_SYS_BUS (MCUB_SYS_BUS_BASE)
#elif defined(MCU_CORE_TL752X_DSP)
#define CPU_SYS_BUS (MCUC_SYS_BUS_BASE)
#endif

#define CONVERT_SYS_ADDR(x) (((uint32_t)(x) & (0xf0000000UL)) ? (uint32_t)(x) : ((uint32_t)(x) + CPU_SYS_BUS))
#define CONVERT_LM_ADDR(x)  ((((uint32_t)(x) & (0xf0000000UL)) == CPU_SYS_BUS) ? ((uint32_t)x & (~CPU_SYS_BUS)) : (uint32_t)(x))

#define FLASH0         FLASH0_BASE
#define FLASH1         FLASH1_BASE
#define CPU1_DMAC      ((dmac_reg_t *)(CPU1_DMAC_BASE + 0x2C0UL))
#define CPU1_DMAC_CH0  (0UL)
#define CPU1_DMAC_CH1  (1UL)
#define CPU1_DMAC_CH2  (2UL)
#define CPU1_DMAC_CH3  (3UL)
#define CPU1_WDT       ((wdt_reg_t *)CPU1_WDT_BASE)
#define GPADC          ((gpadc_t *)GP_ADC_BASE)
#define I2C2           ((i2c_reg_t *)I2C2_BASE)
#define UART0          ((uart_reg_t *)UART0_BASE)
#define UART4          ((uart_reg_t *)UART4_BASE)
#define TAHDT            TAHDT_BASEE
#define DWC_SSI0       ((ssi_reg_t *)DWC_SSI0_BASE)
#define DWC_SSI1       ((ssi_reg_t *)DWC_SSI1_BASE)
#define CPR            ((cpr_reg_t *)CPR_BASE)
#define IPCM           ((ipcm_reg_t *)(CPR_BASE + 0x240))
#define EFUSE          ((efuse_reg_t *)EFUSE_BASE)
#define GPIO           ((gpio_reg_t *)GPIO_BASE)
#define CPU0_WDT       ((wdt_reg_t *)CPU0_WDT_BASE)
#define UART3          ((uart_reg_t *)UART3_BASE)
#define I2C0           ((i2c_reg_t *)I2C0_BASE)
#define UART2          ((uart_reg_t *)UART2_BASE)
#define SPIM           ((spi_reg_t *)(SPIM_BASE))
#define SPIS           ((spi_reg_t *)(SPIS_BASE))
#define I2C1           ((i2c_reg_t *)I2C1_BASE)
#define TIMER0_3       ((timer_reg_t *)TIMER0_3_BASE)
#define TIMER4_7       ((timer_reg_t *)TIMER4_7_BASE)
#define UART1          ((uart_reg_t *)UART1_BASE)
#define SYS_TIMER      ((systimer_reg_t *)SYS_TIMER_BASE)
#define RTC            ((rtc_reg_t *)RTC_BASE)
#define PMU            ((pmu_reg_t *)PMU_BASE)
#define SYS_CTL        ((sys_ctl_reg_t *)SYS_CTL_BASE)
#define CPU_DMAC       ((dmac_reg_t *)(CPU_DMAC_BASE + 0x2C0UL))
#define CPU_DMAC_CH0   (0UL)
#define CPU_DMAC_CH1   (1UL)
#define CPU_DMAC_CH2   (2UL)
#define CPU_DMAC_CH3   (3UL)
#define CPU_DMAC_CH4   (4UL)
#define CPU_DMAC_CH5   (5UL)
#define TRNG           ((trng_reg_t *)TRNG_BASE)
#define AUDIO_DMAC     ((dmac_reg_t *)(AUDIO_DMAC_BASE + 0x2C0UL))
#define AUDIO_DMAC_CH0 (0UL)
#define AUDIO_DMAC_CH1 (1UL)
#define AUDIO_DMAC_CH2 (2UL)
#define AUDIO_DMAC_CH3 (3UL)
#define SDMMC          ((sdmmc_reg_t *)SDMMC_BASE)
#define USB1           USB1_BASE
#define SWS            SWS_BASE
#define TDM0           ((tdm_reg_t *)TDM0_BASE)
#define TDM1           ((tdm_reg_t *)TDM1_BASE)
#define TDM2           ((tdm_reg_t *)TDM2_BASE)
#define PDM0           ((pdm_reg_t *)PDM0_BASE)
#define PDM1           ((pdm_reg_t *)PDM1_BASE)
#define PDMC           ((pdmc_reg_t *)PDMC_BASE)
#define TDM3           ((tdm_reg_t *)TDM3_BASE)
#define SPDIF          ((spdif_reg_t *)(SPDIF_REG_BASE))
#define RESAMPLE       ((rsm_t *)(RESAMPLE_REG_BASE + 0x748))
#define RESAMPLE_CH0   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0))
#define RESAMPLE_CH1   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x100))
#define RESAMPLE_CH2   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x200))
#define RESAMPLE_CH3   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x300))
#define RESAMPLE_CH4   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x400))
#define RESAMPLE_CH5   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x500))
#define RESAMPLE_CH6   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x600))
#define RESAMPLE_CH7   ((rsm_channel_t *)(RESAMPLE_REG_BASE + 0x700))
#define CPU2_DMAC      ((dmac_reg_t *)(CPU2_DMAC_BASE + 0x2C0UL))
#define CPU2_DMAC_CH0  (0UL)
#define CPU2_DMAC_CH1  (1UL)
#define CPU2_DMAC_CH2  (2UL)
#define CPU2_DMAC_CH3  (3UL)
#define CODEC          ((codec_reg_t *)CODEC_BASE)
#define ANC            ((anc_reg_t *)ANC_BASE)
#define ANC_DUMP       ((anc_dump_reg_t *)ANC_DUMP_BASE)
#define ADC_DUMP       ((adc_dump_reg_t *)ADC_DUMP_BASE)
#define MUSIC          MUSIC_BASE
#define CPU2_WDT       ((wdt_reg_t *)CPU2_WDT_BASE)

/*IP version*/
#define AUDIO_CODEC_V1_0 //{AUDIO_CODEC_V1_0, AUDIO_CODEC_V1_1}
/*
 *======================================================================================================
                                ##### tl752x_dma_handshake_num #####
 *======================================================================================================
*/
typedef enum {
    CPU_DMAC_HS_DWC_SSI_0_TX = 0,
    CPU_DMAC_HS_DWC_SSI_1_TX = 1,
    CPU_DMAC_HS_DW_APB_SSI_S_TX = 2,
    CPU_DMAC_HS_DW_APB_SSI_M_TX = 3,
    CPU_DMAC_HS_UART1_TX = 4,
    CPU_DMAC_HS_UART1_RX = 5,
    CPU_DMAC_HS_I2C_TXRX = 6,
    CPU_DMAC_HS_I2C1_TXRX = 7,
    CPU_DMAC_HS_DWC_SSI_0_RX = 8,
    CPU_DMAC_HS_DWC_SSI_1_RX = 9,
    CPU_DMAC_HS_DW_APB_SSI_S_RX = 10,
    CPU_DMAC_HS_DW_APB_SSI_M_RX = 11,
    CPU_DMAC_HS_UART2_TX = 12,
    CPU_DMAC_HS_UART2_RX = 13,
    CPU_DMAC_HS_UART3_TX = 14,
    CPU_DMAC_HS_UART3_RX = 15,
} cpu_dmac_hs_t;

typedef enum {
    AUDIO_DMAC_HS_I2S0_TX = 0,
    AUDIO_DMAC_HS_I2S1_TX = 1,
    AUDIO_DMAC_HS_I2S2_TX = 2,
    AUDIO_DMAC_HS_I2S3_TX = 3,
    AUDIO_DMAC_HS_I2S0_RX = 4,
    AUDIO_DMAC_HS_I2S1_RX = 5,
    AUDIO_DMAC_HS_I2S2_RX = 6,
    AUDIO_DMAC_HS_I2S3_RX = 7,
    AUDIO_DMAC_HS_RESAMPLE_TX = 8,
    AUDIO_DMAC_HS_RESAMPLE_RX = 9,
    AUDIO_DMAC_HS_PDM0 = 10,
    AUDIO_DMAC_HS_PDM1 = 11,
    AUDIO_DMAC_HS_SPDIF = 12,
    AUDIO_DMAC_HS_PDMC_TX = 13,
} audio_dmac_hs_t;

typedef enum {
    CPU2_DMAC_HS_DUMP_ANC0_OR_CODEC_TX0 = 0,
    CPU2_DMAC_HS_DUMP_ANC1_OR_CODEC_TX1 = 1,
    CPU2_DMAC_HS_DUMP_ANC2_OR_CODEC_RX0 = 2,
    CPU2_DMAC_HS_DUMP_ANC3_OR_CODEC_RX1 = 3,
    CPU2_DMAC_HS_I2S0TX_OR_I2S0RX = 4,
    CPU2_DMAC_HS_I2S1TX_OR_I2S1RX = 5,
    CPU2_DMAC_HS_I2S2TX_OR_I2S2RX = 6,
    CPU2_DMAC_HS_I2S3TX_OR_I2S3RX = 7,
    CPU2_DMAC_HS_SPDIF_OR_I2S0RX = 8,
    CPU2_DMAC_HS_PDMC_TX_OR_I2S1RX = 9,
    CPU2_DMAC_HS_RESAMPLE_TX_OR_I2S2RX = 10,
    CPU2_DMAC_HS_RESAMPLE_RX_OR_I2S3RX = 11,
    CPU2_DMAC_HS_PDM0_OR_RESAMPLE_TX = 12,
    CPU2_DMAC_HS_PDM1_OR_RESAMPLE_RX = 13,
    CPU2_DMAC_HS_SPDIF_OR_PDM0 = 14,
    CPU2_DMAC_HS_PDMC_TX_OR_PDM1 = 15,
} CPU2_dmac_hs_t;

typedef enum {
    CPU1_DMAC_HS_GPADC = 0,
    CPU1_DMAC_HS_I2C2_TX = 1,
    CPU1_DMAC_HS_I2C2_RX = 2,
    CPU1_DMAC_HS_UART_TX = 3,
    CPU1_DMAC_HS_UART_RX = 4,
    CPU1_DMAC_HS_UART4_TX = 5,
    CPU1_DMAC_HS_UART4_RX = 6,
    CPU1_DMAC_HS_I2C1_TX = 7,
    CPU1_DMAC_HS_BT_SYS_DBM_RX = 15,
} CPU1_dmac_hs_t;
/*
 *======================================================================================================
                                ##### tl752x_interrupt_num #####
 *======================================================================================================
*/
#if defined(MCU_CORE_TL752X_D25F) //CPU0
#define CPU_DMA_IRQn                 1
#define AUDIO_DMA_IRQn               2
#define CPU2_DMA_IRQn                3
#define IPCM_IRQn                    4
#define CPU1_DMA_IRQn                5
#define SYSTIMER_IRQn                6
#define TIMER0_0_IRQn                7
#define TIMER0_1_IRQn                8
#define TIMER0_2_IRQn                9
#define TIMER0_3_IRQn                10
#define TIMER1_0_IRQn                11
#define TIMER1_1_IRQn                12
#define TIMER1_2_IRQn                13
#define TIMER1_3_IRQn                14
#define RTC_IRQn                     15
#define GPIO_IRQn                    16
#define CPU_WDT_IRQn                 17
#define UART0_IRQn                   18
#define UART1_IRQn                   19
#define I2C0_IRQn                    20
#define I2C1_IRQn                    21
#define I2C2_IRQn                    22
#define DW_APB_SSI0_S_IRQn           23
#define DW_APB_SSI0_M_IRQn           24
#define DWC_SSI_0_IRQn               25
#define DWC_SSI_1_IRQn               26
#define SDIO_IRQn                    27
#define USB_IRQn                     28
#define USB1_RESET_250US_IRQn        29
#define USB1_EP0_SETUP_IRQn          30
#define USB1_EP0_DATA_IRQn           31
#define USB1_EP0_STATUS_IRQn         32
#define USB1_EP0_SETINF_SETADDR_IRQn 33
#define USB1_EPN_DATA_IRQn           34
#define USB1_SUSPEND_IRQn            35
#define GPADC_IRQn                   37
#define CHG_START_IRQn               38
#define BT_SYS_BT_IRQn               39
#define BT_SYS_BLE_IRQn              40
#define BT_SYS_BT_DM_IRQn            41
#define BT_SYS_DBM_IRQn              42
#define BT_SYS_BB_IRQn               43
#define TAHDT_IRQn                     44
#define UART2_IRQn                   45
#define UART3_IRQn                   46
#define TDM0_IRQn                    47
#define TDM1_IRQn                    48
#define TDM2_IRQn                    49
#define TDM3_IRQn                    50
#define PDM0_IRQn                    51
#define PDM1_IRQn                    52
#define PDMC_IRQn                    53
#define AUDIO_CODEC_IRQn             54
#define SPDIF_IRQn                   55
#define RESAMPLE_IRQn                56
#define OSR_TRNG_IRQn                57
#define EFUSE_IRQn                   58
#define UART4_IRQn                   59
#define SW0_IRQn                     60
#define SW1_IRQn                     61
#define SW2_IRQn                     62
#define SW3_IRQn                     63
#define MAX_IRQ_NUM                  64
#endif

#if defined(MCU_CORE_TL752X_N22)                      //CPU1
#define MTIME_IRQn                   7  /* 1 */
#define CPU_DMA_IRQn                 19 /* 1 */
#define AUDIO_DMA_IRQn               20 /* 2 */
#define CPU2_DMA_IRQn                21 /* 3 */
#define IPCM_IRQn                    22 /* 4 */
#define CPU1_DMA_IRQn                23 /* 5 */
#define SYSTIMER_IRQn                24 /* 6 */
#define TIMER0_0_IRQn                25 /* 7 */
#define TIMER0_1_IRQn                26 /* 8 */
#define TIMER0_2_IRQn                27 /* 9 */
#define TIMER0_3_IRQn                28 /* 10 */
#define TIMER1_0_IRQn                29 /* 11 */
#define TIMER1_1_IRQn                30 /* 12 */
#define TIMER1_2_IRQn                31 /* 13 */
#define TIMER1_3_IRQn                32 /* 14 */
#define RTC_IRQn                     33 /* 15 */
#define GPIO_IRQn                    34 /* 16 */
#define CPU_WDT_IRQn                 35 /* 17 */
#define UART0_IRQn                   36 /* 18 */
#define UART1_IRQn                   37 /* 19 */
#define I2C0_IRQn                    38 /* 20 */
#define I2C1_IRQn                    39 /* 21 */
#define I2C2_IRQn                    40 /* 22 */
#define DW_APB_SSI0_S_IRQn           41 /* 23 */
#define DW_APB_SSI0_M_IRQn           42 /* 24 */
#define DWC_SSI_0_IRQn               43 /* 25 */
#define DWC_SSI_1_IRQn               44 /* 26 */
#define SDIO_IRQn                    45 /* 27 */
#define USB_IRQn                     46 /* 28 */
#define USB1_RESET_250US_IRQn        47 /* 29 */
#define USB1_EP0_SETUP_IRQn          48 /* 30 */
#define USB1_EP0_DATA_IRQn           49 /* 31 */
#define USB1_EP0_STATUS_IRQn         50 /* 32 */
#define USB1_EP0_SETINF_SETADDR_IRQn 51 /* 33 */
#define USB1_EPN_DATA_IRQn           52 /* 34 */
#define USB1_SUSPEND_IRQn            53 /* 35 */
#define GPADC_IRQn                   55 /* 37 */
#define CHG_START_IRQn               56 /* 38 */
#define BT_SYS_BT_IRQn               57 /* 39 */
#define BT_SYS_BLE_IRQn              58 /* 40 */
#define BT_SYS_BT_DM_IRQn            59 /* 41 */
#define BT_SYS_DBM_IRQn              60 /* 42 */
#define BT_SYS_BB_IRQn               61 /* 43 */
#define TAHDT_IRQn                     62 /* 44 */
#define UART2_IRQn                   63 /* 45 */
#define UART3_IRQn                   64 /* 46 */
#define TDM0_IRQn                    65 /* 47 */
#define TDM1_IRQn                    66 /* 48 */
#define TDM2_IRQn                    67 /* 49 */
#define TDM3_IRQn                    68 /* 50 */
#define PDM0_IRQn                    69 /* 51 */
#define PDM1_IRQn                    70 /* 52 */
#define PDMC_IRQn                    71 /* 53 */
#define AUDIO_CODEC_IRQn             72 /* 54 */
#define SPDIF_IRQn                   73 /* 55 */
#define RESAMPLE_IRQn                74 /* 56 */
#define OSR_TRNG_IRQn                75 /* 57 */
#define EFUSE_IRQn                   76 /* 58 */
#define UART4_IRQn                   77 /* 59 */
#define SW0_IRQn                     78
#define SW1_IRQn                     79
#define SW2_IRQn                     80
#define SW3_IRQn                     81
#define MAX_IRQ_NUM                  82 /* 64 */
#endif

#if defined(MCU_CORE_TL752X_DSP) //CPU2
#define CPU2_DMA_IRQn      1
#define AUDIO_DMA_IRQn     2
#define IPCM_IRQn          3
#define SYSTIMER_IRQn      4
#define TIMER0_0_IRQn      5
#define TIMER0_1_IRQn      6
#define TIMER0_2_IRQn      7
#define TIMER0_3_IRQn      8
#define TIMER1_0_1_IRQn    9
#define TIMER1_2_3_IRQn    10
#define RTC_IRQn           11
#define GPIO_IRQn          12
#define CPU_WDT_IRQn       13
#define I2C_IRQn           14
#define UART0_IRQn         15
#define DW_APB_SSI0_S_IRQn 16
#define DW_APB_SSI0_M_IRQn 17
#define AUDIO_CODEC_IRQn   18
#define TDM0_IRQn          19
#define TDM1_IRQn          20
#define TDM2_IRQn          21
#define TDM3_IRQn          22
#define PDM0_IRQn          23
#define PDM1_IRQn          24
#define PDMC_IRQn          25
#define SPDIF_IRQn         26
#define RESAMPLE_IRQn      27
#define XCHAL_TIMER0_IRQn  29
#define XCHAL_TIMER1_IRQn  30
#define SW0_IRQn           31

/* unused, just for build success */
#define CPU_DMA_IRQn 255
#define I2C0_IRQn    255
#define I2C1_IRQn    255
#define I2C2_IRQn    255
#define UART1_IRQn   255
#endif

/*
 *======================================================================================================
                                ##### tl752x_cache_operate #####
 *======================================================================================================
*/
#define drv_hw_cache_disable() \
    __asm("fence.i");          \
    clear_csr(NDS_MCACHE_CTL, 0x03)
#define drv_hw_cache_enable()          \
    set_csr(NDS_MCACHE_CTL, 0x03);     \
    write_csr(NDS_MCCTLCOMMAND, 0x17); \
    __asm("fence.i")

#define INVALID_ICACHE  __asm("fence.i")
#define INVALID_DCACHE  write_csr(NDS_MCCTLCOMMAND, 23)

#define DISABLE_BTB __asm__("csrci mmisc_ctl,8")
#define ENABLE_BTB  __asm__("csrsi mmisc_ctl,8")



/*
 *======================================================================================================
                                ##### tl752x_isr_operate #####
 *======================================================================================================
*/
typedef enum {
    IRQ_PRI_0,
    IRQ_PRI_1,
    IRQ_PRI_2,
    IRQ_PRI_3,
} irq_pri_t;

#if defined(MCU_CORE_TL752X_D25F) || defined(MCU_CORE_TL752X_N22)
#define drv_hw_global_int_disable()              \
    do {                                         \
        clear_csr(NDS_MSTATUS, FLD_MSTATUS_MIE); \
    g_int_dis_cnt++

#define drv_hw_global_int_restore()            \
    g_int_dis_cnt--;                           \
    if (g_int_dis_cnt == 0) {                  \
        set_csr(NDS_MSTATUS, FLD_MSTATUS_MIE); \
    }                                          \
    }                                          \
    while (0)

#elif defined(MCU_CORE_TL752X_DSP)
#define drv_hw_global_int_disable() \
    do {                            \
        xthal_disable_interrupts(); \
    g_int_dis_cnt++

#define drv_hw_global_int_restore() \
    g_int_dis_cnt--;                \
    if (g_int_dis_cnt == 0) {       \
        xthal_enable_interrupts();  \
    }                               \
    }                               \
    while (0)
#endif

#if defined(MCU_CORE_TL752X_D25F)
#define ISR_REGISTER(isr_func, isr_type) PLIC_ISR_REGISTER(isr_func, isr_type)
#define isr_preempt_enable()             plic_preempt_feature_en(CORE_PREEMPT_PRI_MODE0)
#define isr_preempt_disable()            plic_preempt_feature_dis()
#define drv_mtime_int_enable()           core_mie_enable(FLD_MIE_MTIE)
#define drv_mtime_int_disable()          core_mie_disable(FLD_MIE_MTIE)
#define drv_sw_int_trigger(src) \
    do {                        \
        plic_set_pending(src);  \
    } while (0)

#define drv_hw_int_enable(int_num)      \
    do {                                \
        plic_interrupt_enable(int_num); \
    } while (0)

#define drv_hw_int_disable(int_num)      \
    do {                                 \
        plic_interrupt_disable(int_num); \
    } while (0)

/** @brief  Set the intrrupt priority,Preemption mode is enabled by default.
 *  @param  int_num specifies the interrupt num, @ref IRQn_Type.
 *  @param  level specifies the interrupt level, the value range is 1 to 3.The higher the value, the higher the priority.
 *          This parameter can be one of the following values:
 *          @ref IRQ_PRI_LEV1
 *          @ref IRQ_PRI_LEV2
 *          @ref IRQ_PRI_LEV3
 */
#define drv_hw_int_set_priority(int_num, level) plic_set_priority(int_num, level)

#endif
#if defined(MCU_CORE_TL752X_N22)
#define ISR_REGISTER(isr_func, isr_type) CLIC_ISR_REGISTER(isr_func, isr_type)
#define isr_preempt_enable()             clic_interrupt_preempt_en()
#define isr_preempt_disable()            clic_interrupt_preempt_dis()
#define drv_mtime_int_enable()           clic_interrupt_enable(MTIME_IRQn)
#define drv_mtime_int_disable()          clic_interrupt_disable(MTIME_IRQn)
#define drv_sw_int_trigger(src)                                               \
    do {                                                                      \
        clic_interrupt_trigger_type_set(src, IRQ_TRIGGER_TYPE_POSITIVE_EDGE); \
        clic_interrupt_pending_set(src);                                      \
    } while (0)

#define drv_hw_int_enable(int_num)      \
    do {                                \
        clic_interrupt_enable(int_num); \
    } while (0)

#define drv_hw_int_disable(int_num)      \
    do {                                 \
        clic_interrupt_disable(int_num); \
    } while (0)

/** @brief  Set the intrrupt priority,Preemption mode is enabled by default.
 *  @param  int_num specifies the interrupt num, @ref IRQn_Type.
 *  @param  level specifies the interrupt level, the value range is 0 to 3.The higher the value, the higher the priority.
 *          This parameter can be one of the following values:
 *          @ref IRQ_PRI_LEV0
 *          @ref IRQ_PRI_LEV1
 *          @ref IRQ_PRI_LEV2
 *          @ref IRQ_PRI_LEV3
 */
#define drv_hw_int_set_priority(int_num, level_priority) clic_interrupt_priority_level_adjust(int_num, level_priority)

#define drv_hw_int_set_priority_level(int_num, level, priority) clic_interrupt_priority_level_set(int_num, level, priority)

/** @brief  Set the intrrupt priority and level group.
 *  @param  group.
 * GROUP, LEVEL_BITS, PRIORITY_BITS, ACTUAL
 * 0     , None      , [7:0]        ,0 bit level - 2bit priority
 * 1     , [7:7]     , [6:0]        ,1 bit level - 1bit priority
 * 2     , [7:6]     , [5:0]        ,2 bit level - 0bit priority
 * 3     , [7:5]     , [4:0]        ,2 bit level - 0bit priority
 * 4     , [7:4]     , [3:0]        ,2 bit level - 0bit priority
 * 5     , [7:3]     , [2:0]        ,2 bit level - 0bit priority
 * 6     , [7:2]     , [1:0]        ,2 bit level - 0bit priority
 * 7     , [7:1]     , [0:0]        ,2 bit level - 0bit priority
 * 8     , [7:0]     , None         ,2 bit level - 0bit priority
 */
#define drv_hw_int_set_priority_group(group) clic_interrupt_nlbits_set(group)

#endif

#if defined(MCU_CORE_TL752X_DSP)
#define xtensa_isr_register(irq_num, isr_func) xtensa_intr_register(irq_num, isr_func)
#define xtensa_isr_unregister(irq_num)         xtensa_intr_unregister(irq_num)
#define drv_sw_int_trigger(src)                    \
    do {                                           \
        xtos_interrupt_trigger((unsigned int)src); \
    } while (0)
#define drv_hw_int_enable(int_num)                    \
    do {                                              \
        xtos_interrupt_enable((unsigned int)int_num); \
    } while (0)

#define drv_hw_int_disable(int_num)                    \
    do {                                               \
        xtos_interrupt_disable((unsigned int)int_num); \
    } while (0)

#define drv_hw_int_clear(int_num)                    \
    do {                                             \
        xtos_interrupt_clear((unsigned int)int_num); \
    } while (0)
#endif
/*
 *======================================================================================================
                                ##### tl752x_assert_operate #####
 *======================================================================================================
*/
#if defined(MCU_CORE_TL752X_D25F) || defined(MCU_CORE_TL752X_N22)
#define DRV_ASSERT_FAILED(param0, param1) RISCV_ECALL_0(ECALL_ASSERT_ERROR_ID)
#elif defined(MCU_CORE_TL752X_DSP)
#define DRV_ASSERT_FAILED(param0, param1) XTENSA_ECALL_0(SYSCALL_ASSERT_ERROR_ID)
#endif

#define DRV_ASSERT_PARAM(expr) ((expr) ? (void)0U : DRV_ASSERT_FAILED(0, 0))

#define DRV_ASSERT(expr) ((expr) ? (void)0U : DRV_ASSERT_FAILED(0, 0))

#endif

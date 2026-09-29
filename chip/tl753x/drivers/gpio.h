/********************************************************************************************************
 * @file    gpio.h
 *
 * @brief   This is the header file for tl753x
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
/** @page GPIO
 *
 *  Introduction
 *  ===============
 *
 *
 *  API Reference
 *  ===============
 *  Header File: gpio.h
 */
#ifndef DRIVERS_GPIO_H_
#define DRIVERS_GPIO_H_


#include "lib/include/plic.h"
#include "lib/include/analog.h"
#include "reg_include/gpio_reg.h"

/**********************************************************************************************************************
 *                                         global constants                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           global macro                                                             *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                         global data type                                                           *
 *********************************************************************************************************************/
/**
 *  @brief  Define GPIO group types
 */
typedef enum
{
    GPIO_GROUP_A   = 0,
    GPIO_GROUP_B   = 1,
    GPIO_GROUP_C   = 2,
    GPIO_GROUP_D   = 3,
    GPIO_GROUP_E   = 4,
    GPIO_GROUP_F   = 5,
    GPIO_GROUP_G   = 6,
    GPIO_GROUP_H   = 7,
    GPIO_GROUP_I   = 8,
    GPIO_GROUP_J   = 9,
    GPIO_GROUP_K   = 10,
    GPIO_GROUP_ANA = 11,
} gpio_group_e;

/**
 *  @brief  Define GPIO types
 */
typedef enum
{
    GPIO_GROUPA   = 0x000,
    GPIO_GROUPB   = 0x100,
    GPIO_GROUPC   = 0x200,
    GPIO_GROUPD   = 0x300,
    GPIO_GROUPE   = 0x400,
    GPIO_GROUPF   = 0x500,
    GPIO_GROUPG   = 0X600,
    GPIO_GROUPH   = 0X700,
    GPIO_GROUPI   = 0X800,
    GPIO_GROUPJ   = 0X900,
    GPIO_GROUPK   = 0xa00,

    GPIO_ALL      = 0xb00,

    GPIO_PA0    = GPIO_GROUPA | BIT(0),
    GPIO_PA1    = GPIO_GROUPA | BIT(1),
    GPIO_PA2    = GPIO_GROUPA | BIT(2),
    GPIO_PA3    = GPIO_GROUPA | BIT(3),
    GPIO_USB_DM = GPIO_PA3, // default: SSPI_SI
    GPIO_PA4    = GPIO_GROUPA | BIT(4),
    GPIO_USB_DP = GPIO_PA4, // default: SSPI_CN
    GPIO_PA5    = GPIO_GROUPA | BIT(5),
    GPIO_DM     = GPIO_PA5, // default: SSPI_CK
    GPIO_PA6    = GPIO_GROUPA | BIT(6),
    GPIO_DP     = GPIO_PA6, // default: SSPI_SO
    GPIO_PA7    = GPIO_GROUPA | BIT(7),
    GPIO_SWS    = GPIO_PA7, // only support SWS_IO(default)
    GPIOA_ALL   = GPIO_GROUPA | 0x00ff,

    GPIO_PB0  = GPIO_GROUPB | BIT(0),
    GPIO_PB1  = GPIO_GROUPB | BIT(1), // default: TCK
    GPIO_PB2  = GPIO_GROUPB | BIT(2), // default: TMS
    GPIO_PB3  = GPIO_GROUPB | BIT(3), // default: TDO
    GPIO_PB4  = GPIO_GROUPB | BIT(4), // default: TDI
    GPIO_PB5  = GPIO_GROUPB | BIT(5),
    GPIO_PB6  = GPIO_GROUPB | BIT(6),
    GPIO_PB7  = GPIO_GROUPB | BIT(7),
    GPIOB_ALL = GPIO_GROUPB | 0x00ff,

    GPIO_PC0  = GPIO_GROUPC | BIT(0),
    GPIO_PC1  = GPIO_GROUPC | BIT(1),
    GPIO_PC2  = GPIO_GROUPC | BIT(2),
    GPIO_PC3  = GPIO_GROUPC | BIT(3),
    GPIO_PC4  = GPIO_GROUPC | BIT(4),
    GPIO_PC5  = GPIO_GROUPC | BIT(5),
    GPIO_PC6  = GPIO_GROUPC | BIT(6),
    GPIO_PC7  = GPIO_GROUPC | BIT(7),
    GPIOC_ALL = GPIO_GROUPC | 0x00ff,

    GPIO_PD0  = GPIO_GROUPD | BIT(0),
    GPIO_PD1  = GPIO_GROUPD | BIT(1),
    GPIO_PD2  = GPIO_GROUPD | BIT(2),
    GPIO_PD3  = GPIO_GROUPD | BIT(3),
    GPIO_PD4  = GPIO_GROUPD | BIT(4),
    GPIO_PD5  = GPIO_GROUPD | BIT(5),
    GPIO_PD6  = GPIO_GROUPD | BIT(6),
    GPIO_PD7  = GPIO_GROUPD | BIT(7),
    GPIOD_ALL = GPIO_GROUPD | 0x00ff,

    GPIO_PE0  = GPIO_GROUPE | BIT(0),
    GPIO_PE1  = GPIO_GROUPE | BIT(1),
    GPIO_PE2  = GPIO_GROUPE | BIT(2),
    GPIO_PE3  = GPIO_GROUPE | BIT(3),
    GPIO_PE4  = GPIO_GROUPE | BIT(4),
    GPIO_PE5  = GPIO_GROUPE | BIT(5),
    GPIO_PE6  = GPIO_GROUPE | BIT(6),
    GPIO_PE7  = GPIO_GROUPE | BIT(7),
    GPIOE_ALL = GPIO_GROUPE | 0x00ff,

    GPIO_PF0  = GPIO_GROUPF | BIT(0),
    GPIO_PF1  = GPIO_GROUPF | BIT(1),
    GPIO_PF2  = GPIO_GROUPF | BIT(2),
    GPIO_PF3  = GPIO_GROUPF | BIT(3),
    GPIO_PF4  = GPIO_GROUPF | BIT(4),
    GPIO_PF5  = GPIO_GROUPF | BIT(5),
    GPIO_PF6  = GPIO_GROUPF | BIT(6),
    GPIO_PF7  = GPIO_GROUPF | BIT(7),
    GPIOF_ALL = GPIO_GROUPF | 0x00ff,

    GPIO_PG0  = GPIO_GROUPG | BIT(0),
    GPIO_PG1  = GPIO_GROUPG | BIT(1),
    GPIO_PG2  = GPIO_GROUPG | BIT(2),
    GPIO_PG3  = GPIO_GROUPG | BIT(3),
    GPIO_PG4  = GPIO_GROUPG | BIT(4),
    GPIO_PG5  = GPIO_GROUPG | BIT(5),
    GPIO_PG6  = GPIO_GROUPG | BIT(6),
    GPIO_PG7  = GPIO_GROUPG | BIT(7),
    GPIOG_ALL = GPIO_GROUPG | 0x00ff,

    GPIO_PH0  = GPIO_GROUPH | BIT(0),
    GPIO_PH1  = GPIO_GROUPH | BIT(1),
    GPIO_PH2  = GPIO_GROUPH | BIT(2),
    GPIO_PH3  = GPIO_GROUPH | BIT(3),
    GPIO_PH4  = GPIO_GROUPH | BIT(4),
    GPIO_PH5  = GPIO_GROUPH | BIT(5),
    GPIOH_ALL = GPIO_GROUPH | 0x003f,

    GPIO_PI0  = GPIO_GROUPI | BIT(0),      // Only the MSPI_MOSI_IO and gpio functions are supported
    GPIO_PI1  = GPIO_GROUPI | BIT(1),      // Only the MSPI_CK_IO and gpio functions are supported
    GPIO_PI2  = GPIO_GROUPI | BIT(2),      // Only the MSPI_IO3_IO and gpio functions are supported
    GPIO_PI3  = GPIO_GROUPI | BIT(3),      // Only the MSPI_CN_IO and gpio functions are supported
    GPIO_PI4  = GPIO_GROUPI | BIT(4),      // Only the MSPI_MISO_IO and gpio functions are supported
    GPIO_PI5  = GPIO_GROUPI | BIT(5),      // Only the MSPI_IO2_IO and gpio functions are supported
    GPIO_PI6  = GPIO_GROUPI | BIT(6),      // Only the MSPI_IO4_IO and gpio functions are supported
    GPIO_PI7  = GPIO_GROUPI | BIT(7),      // Only the MSPI_IO5_IO and gpio functions are supported
    GPIOI_ALL = GPIO_GROUPI | 0x00ff,

    GPIO_PJ0  = GPIO_GROUPJ | BIT(0),      // Only the MSPI_IO6_IO and gpio functions are supported
    GPIO_PJ1  = GPIO_GROUPJ | BIT(1),      // Only the MSPI_IO7_IO and gpio functions are supported
    GPIO_PJ2  = GPIO_GROUPJ | BIT(2),      // default: MSPI_CN1
    GPIO_PJ3  = GPIO_GROUPJ | BIT(3),      // default: MSPI_CN2
    GPIO_PJ4  = GPIO_GROUPJ | BIT(4),      // default: MSPI_CN3
    GPIO_PJ5  = GPIO_GROUPJ | BIT(5),      // MSPI_DM_IO(0)
    GPIOJ_ALL = GPIO_GROUPJ | 0x003f,


    GPIO_PK0  = GPIO_GROUPK | BIT(0),      // Do not support digit dropdown list
    GPIO_PK1  = GPIO_GROUPK | BIT(1),      // Do not support digit dropdown list
    GPIO_PK2  = GPIO_GROUPK | BIT(2),      // Do not support digit dropdown list
    GPIO_PK3  = GPIO_GROUPK | BIT(3),      // Do not support digit dropdown list
    GPIO_PK4  = GPIO_GROUPK | BIT(4),      // Do not support digit dropdown list
    GPIO_PK5  = GPIO_GROUPK | BIT(5),      // Do not support digit dropdown list
    GPIOK_ALL = GPIO_GROUPK | 0x003f,


} gpio_pin_e;

/**
 *  @brief  Define GPIO function pin types.
 */
typedef enum
{
    GPIO_FC_PA0 = GPIO_PA0,
    GPIO_FC_PA1 = GPIO_PA1,
    GPIO_FC_PA2 = GPIO_PA2,
    GPIO_FC_PA3 = GPIO_PA3,
    GPIO_FC_PA4 = GPIO_PA4,
    GPIO_FC_PA5 = GPIO_PA5,
    GPIO_FC_PA6 = GPIO_PA6,

    GPIO_FC_PB0 = GPIO_PB0,
    GPIO_FC_PB1 = GPIO_PB1,
    GPIO_FC_PB2 = GPIO_PB2,
    GPIO_FC_PB3 = GPIO_PB3,
    GPIO_FC_PB4 = GPIO_PB4,
    GPIO_FC_PB5 = GPIO_PB5,
    GPIO_FC_PB6 = GPIO_PB6,
    GPIO_FC_PB7 = GPIO_PB7,

    GPIO_FC_PC0 = GPIO_PC0,
    GPIO_FC_PC1 = GPIO_PC1,
    GPIO_FC_PC2 = GPIO_PC2,
    GPIO_FC_PC3 = GPIO_PC3,
    GPIO_FC_PC4 = GPIO_PC4,
    GPIO_FC_PC5 = GPIO_PC5,
    GPIO_FC_PC6 = GPIO_PC6,
    GPIO_FC_PC7 = GPIO_PC7,

    GPIO_FC_PD0 = GPIO_PD0,
    GPIO_FC_PD1 = GPIO_PD1,
    GPIO_FC_PD2 = GPIO_PD2,
    GPIO_FC_PD3 = GPIO_PD3,
    GPIO_FC_PD4 = GPIO_PD4,
    GPIO_FC_PD5 = GPIO_PD5,
    GPIO_FC_PD6 = GPIO_PD6,
    GPIO_FC_PD7 = GPIO_PD7,

    GPIO_FC_PE0 = GPIO_PE0,
    GPIO_FC_PE1 = GPIO_PE1,
    GPIO_FC_PE2 = GPIO_PE2,
    GPIO_FC_PE3 = GPIO_PE3,
    GPIO_FC_PE4 = GPIO_PE4,
    GPIO_FC_PE5 = GPIO_PE5,
    GPIO_FC_PE6 = GPIO_PE6,
    GPIO_FC_PE7 = GPIO_PE7,

    GPIO_FC_PF0 = GPIO_PF0,
    GPIO_FC_PF1 = GPIO_PF1,
    GPIO_FC_PF2 = GPIO_PF2,
    GPIO_FC_PF3 = GPIO_PF3,
    GPIO_FC_PF4 = GPIO_PF4,
    GPIO_FC_PF5 = GPIO_PF5,
    GPIO_FC_PF6 = GPIO_PF6,
    GPIO_FC_PF7 = GPIO_PF7,

    GPIO_FC_PG0 = GPIO_PG0,
    GPIO_FC_PG1 = GPIO_PG1,
    GPIO_FC_PG2 = GPIO_PG2,
    GPIO_FC_PG3 = GPIO_PG3,
    GPIO_FC_PG4 = GPIO_PG4,
    GPIO_FC_PG5 = GPIO_PG5,
    GPIO_FC_PG6 = GPIO_PG6,
    GPIO_FC_PG7 = GPIO_PG7,

    GPIO_FC_PH0 = GPIO_PH0,
    GPIO_FC_PH1 = GPIO_PH1,
    GPIO_FC_PH2 = GPIO_PH2,
    GPIO_FC_PH3 = GPIO_PH3,
    GPIO_FC_PH4 = GPIO_PH4,
    GPIO_FC_PH5 = GPIO_PH5,

    GPIO_FC_PI0 = GPIO_PI0,
    GPIO_FC_PI1 = GPIO_PI1,
    GPIO_FC_PI2 = GPIO_PI2,
    GPIO_FC_PI3 = GPIO_PI3,
    GPIO_FC_PI4 = GPIO_PI4,
    GPIO_FC_PI5 = GPIO_PI5,
    GPIO_FC_PI6 = GPIO_PI6,
    GPIO_FC_PI7 = GPIO_PI7,

    GPIO_FC_PJ0 = GPIO_PJ0,
    GPIO_FC_PJ1 = GPIO_PJ1,
    GPIO_FC_PJ2 = GPIO_PJ2,
    GPIO_FC_PJ3 = GPIO_PJ3,
    GPIO_FC_PJ4 = GPIO_PJ4,
    GPIO_FC_PJ5 = GPIO_PJ5,

    GPIO_FC_PK0 = GPIO_PK0,
    GPIO_FC_PK1 = GPIO_PK1,
    GPIO_FC_PK2 = GPIO_PK2,
    GPIO_FC_PK3 = GPIO_PK3,
    GPIO_FC_PK4 = GPIO_PK4,
    GPIO_FC_PK5 = GPIO_PK5,

    GPIO_NONE_PIN = 0x000,
} gpio_func_pin_e;

/**
 *  @brief  select pin as DSP_JTAG
 */
typedef struct
{
    gpio_pin_e tck;
    gpio_pin_e tms;
    gpio_pin_e tdo;
    gpio_pin_e tdi;
} dsp_jtag_pin_st;

/**
 *  @brief  Define GPIO function mux types
 */
typedef enum
{
    SWM_IO          = 1,
    PWM0            = 2,
    PWM1            = 3,
    PWM2            = 4,
    PWM3            = 5,
    PWM4            = 6,
    PWM5            = 7,
    PWM0_N          = 8,
    PWM1_N          = 9,
    PWM2_N          = 10,
    PWM3_N          = 11,
    PWM4_N          = 12,
    PWM5_N          = 13,
    UART0_RTS       = 14,
    UART0_CTS_I     = 15,
    UART0_RTX_IO    = 16,
    UART0_TX        = 17,
    UART1_RTS       = 18,
    UART1_CTS_I     = 19,
    UART1_RTX_IO    = 20,
    UART1_TX        = 21,
    UART2_RTS       = 22,
    UART2_CTS_I     = 23,
    UART2_RTX_IO    = 24,
    UART2_TX        = 25,
    UART3_RTS       = 26,
    UART3_CTS_I     = 27,
    UART3_RTX_IO    = 28,
    UART3_TX        = 29,
    SPDIF_RX        = 30,
    SPDIF_TX        = 31,
    SSPI_SI_IO      = 32,
    SSPI_SO_IO      = 33,
    SSPI_CN_I       = 34,
    SSPI_CK_I       = 35,
    DSP_TDI_I       = 36,
    DSP_TDO_IO      = 37,
    DSP_TMS_I       = 38,
    DSP_TCK_I       = 39,
    CLK_7816        = 40,
    I2S0_DAT1_IO    = 41,
    I2S0_LR1_IO     = 42,
    I2S0_DAT0_IO    = 43,
    I2S0_LR0_IO     = 44,
    I2S0_BCK_IO     = 45,
    I2S0_CLK        = 46,
    I2S1_DAT1_IO    = 47,
    I2S1_LR1_IO     = 48,
    I2S1_DAT0_IO    = 49,
    I2S1_LR0_IO     = 50,
    I2S1_BCK_IO     = 51,
    I2S1_CLK        = 52,
    I2S2_DAT1_IO    = 53,
    I2S2_LR1_IO     = 54,
    I2S2_DAT0_IO    = 55,
    I2S2_LR0_IO     = 56,
    I2S2_BCK_IO     = 57,
    I2S2_CLK        = 58,
    DMIC0_DAT_I     = 59,
    DMIC0_CLK0      = 60,
    DMIC1_DAT_I     = 61,
    DMIC1_CLK0      = 62,
    WIFI_DENY_I     = 63,
    BT_ACTIVITY     = 64,
    BT_STATUS       = 65,
    BT_INBAND       = 66,
    TX_CYC2PA       = 67,
    ATSEL_0         = 68,
    ATSEL_1         = 69,
    ATSEL_2         = 70,
    ATSEL_3         = 71,
    ATSEL_4         = 72,
    ATSEL_5         = 73,
    CAN0_RX_I       = 74,
    CAN0_TX         = 75,
    CAN1_RX_I       = 76,
    CAN1_TX         = 77,
    I3C0_SDA_PULLUP_EN = 78,
    I3C0_SDA_IO     = 79,
    I3C0_SCL_IO     = 80,
    I3C1_SDA_PULLUP_EN = 81,
    I3C1_SDA_IO     = 82,
    I3C1_SCL_IO     = 83,
    RX_CYC2LNA      = 84,
    I2C_SDA_IO      = 85,
    I2C_SCL_IO      = 86,
    I2C1_SDA_IO     = 87,
    I2C1_SCL_IO     = 88,
    CLKXO_EXT_I     = 89,
    DBG_PROBE_CLK   = 90,
    DBG_BB0         = 91,
    DBG_ADC_I_DAT0  = 92,
    DBG_TX_DAT0_I   = 93,
    DBG_OTP_PCLK    = 94,
    DBG_OTP_DR10    = 95,
    DBG_OTP_DW10    = 96,
    EMMC_RSTN       = 97,
    EMMC_CDN_I      = 98,
    EMMC_WP_I       = 99,
    EMMC_DAT7_IO    = 100,
    EMMC_DAT6_IO    = 101,
    EMMC_DAT5_IO    = 102,
    EMMC_DAT4_IO    = 103,
    EMMC_DAT3_IO    = 104,
    EMMC_DAT2_IO    = 105,
    EMMC_DAT1_IO    = 106,
    EMMC_DAT0_IO    = 107,
    EMMC_CMD_IO     = 108,
    EMMC_CK_IO      = 109,
    GSPI_CN3        = 110,
    GSPI_CN2        = 111,
    GSPI_CN1        = 112,
    GSPI_DM_IO      = 113,
    GSPI_CN0_IO     = 114,
    GSPI_IO7_IO     = 115,
    GSPI_IO6_IO     = 116,
    GSPI_IO5_IO     = 117,
    GSPI_IO4_IO     = 118,
    GSPI_IO3_IO     = 119,
    GSPI_IO2_IO     = 120,
    GSPI_MISO_IO    = 121,
    GSPI_MOSI_IO    = 122,
    GSPI_CK_IO      = 123,
    GSPI1_DM_IO     = 124,
    GSPI1_CN0_IO    = 125,
    GSPI1_IO7_IO    = 126,
    GSPI1_IO6_IO    = 127,
    GSPI1_IO5_IO    = 128,
    GSPI1_IO4_IO    = 129,
    GSPI1_IO3_IO    = 130,
    GSPI1_IO2_IO    = 131,
    GSPI1_MISO_IO   = 132,
    GSPI1_MOSI_IO   = 133,
    GSPI1_CK_IO     = 134,
    HSPI_DM_IO      = 135,
    HSPI_CN0_IO     = 136,
    HSPI_IO7_IO     = 137,
    HSPI_IO6_IO     = 138,
    HSPI_IO5_IO     = 139,
    HSPI_IO4_IO     = 140,
    HSPI_IO3_IO     = 141,
    HSPI_IO2_IO     = 142,
    HSPI_MISO_IO    = 143,
    HSPI_MOSI_IO    = 144,
    HSPI_CK_IO      = 145,
    LSPI_DM_IO      = 146,
    LSPI_CN_IO      = 147,
    LSPI_IO7_IO     = 148,
    LSPI_IO6_IO     = 149,
    LSPI_IO5_IO     = 150,
    LSPI_IO4_IO     = 151,
    LSPI_IO3_IO     = 152,
    LSPI_IO2_IO     = 153,
    LSPI_MISO_IO    = 154,
    LSPI_MOSI_IO    = 155,
    LSPI_CK_IO      = 156,
} gpio_func_e;

/**
 *  @brief  Define GPIO mux func
 */
typedef enum
{
    AS_GPIO,
    AS_SSPI_SI,
    AS_SSPI_CN,
    AS_SSPI_CK,
    AS_SSPI_SO,
    AS_SWS,
    AS_TCK,
    AS_TMS,
    AS_TDO,
    AS_TDI,
    AS_MSPI_MOSI,
    AS_MSPI_CK,
    AS_MSPI_IO3,
    AS_MSPI_CN,
    AS_MSPI_MISO,
    AS_MSPI_IO2,
    AS_MSPI_IO4,
    AS_MSPI_IO5,
    AS_MSPI_IO6,
    AS_MSPI_IO7,
    AS_MSPI_CN1,
    AS_MSPI_CN2,
    AS_MSPI_CN3,
    AS_MSPI_DM,
} gpio_fuc_e;

/*                                         global data type                                                           *
 *********************************************************************************************************************/

/*
 * @brief define gpio irq
 */
typedef enum
{
    GPIO_IRQ_IRQ0 = BIT(0),
    GPIO_IRQ_IRQ1 = BIT(1),
    GPIO_IRQ_IRQ2 = BIT(2),
    GPIO_IRQ_IRQ3 = BIT(3),
    GPIO_IRQ_IRQ4 = BIT(4),
    GPIO_IRQ_IRQ5 = BIT(5),
    GPIO_IRQ_IRQ6 = BIT(6),
    GPIO_IRQ_IRQ7 = BIT(7),
} gpio_irq_e;

/**
 *  @brief  Define rising/falling types
 */
typedef enum
{
    POL_RISING  = 0,
    POL_FALLING = 1,
} gpio_pol_e;

/**
 *  @brief  Define interrupt types
 */
typedef enum
{
    INTR_RISING_EDGE = 0,
    INTR_FALLING_EDGE,
    INTR_HIGH_LEVEL,
    INTR_LOW_LEVEL,
} gpio_irq_trigger_type_e;

/**
 *  @brief  Define IRQ types
 */
typedef enum
{
    GPIO_IRQ0 = 0,
    GPIO_IRQ1 = 1,
    GPIO_IRQ2 = 2,
    GPIO_IRQ3 = 3,
    GPIO_IRQ4 = 4,
    GPIO_IRQ5 = 5,
    GPIO_IRQ6 = 6,
    GPIO_IRQ7 = 7,
} gpio_irq_num_e;

/**
 *  @brief  Define pull up or down types
 */
typedef enum
{
    GPIO_PIN_UP_DOWN_FLOAT = 0,
    GPIO_PIN_PULLUP_1M     = 1,
    GPIO_PIN_PULLDOWN_100K = 2,
    GPIO_PIN_PULLUP_10K    = 3,
} gpio_pull_type_e;

/**
 *  @brief  Define pem task signal types
 */
typedef enum
{
    TASK_SIGNAL_SEL0 = 0,
    TASK_SIGNAL_SEL1 = 1,
    TASK_SIGNAL_SEL2 = 2,
    TASK_SIGNAL_SEL3 = 3,
    TASK_SIGNAL_SEL4 = 4,
    TASK_SIGNAL_SEL5 = 5,
    TASK_SIGNAL_SEL6 = 6,
    TASK_SIGNAL_SEL7 = 7,
} pem_task_signal_type_e;

/**
 *  @brief  Define pem gpio group task types, choose which gpio group  as task
 */
typedef enum
{
    TASK_GROUP_GPIO_PA = 0,
    TASK_GROUP_GPIO_PB = 1,
    TASK_GROUP_GPIO_PC = 2,
    TASK_GROUP_GPIO_PD = 3,
    TASK_GROUP_GPIO_PE = 4,
    TASK_GROUP_GPIO_PF = 5,
} pem_gpio_group_task_type_e;

typedef enum
{
    PROBE_CLK32K        = 0,
    PROBE_RC24M         = 1,
    PROBE_PLL0          = 2,
    PROBE_PLL1          = 3,
    PROBE_XTL24M        = 4,
    PROBE_CLK_SAR       = 5,
    PROBE_HCLK          = 6,
    PROBE_PCLK          = 7,
    PROBE_CLK_CCLK_DSP  = 8,
    PROBE_CLK_MSPI      = 9,
    PROBE_CLK_HCLK1_N22 = 0xa,
    PROBE_CLK_LSPI      = 0xb,
    PROBE_CLK_GSPI      = 0xc,
    PROBE_CLK_GSPI1     = 0xd,
    PROBE_CLK_HSPI      = 0xe,
    PROBE_CLK_I3C0      = 0xf,
    PROBE_CLK_I3C1      = 0x10,
    PROBE_CLK_SDIO      = 0x11,
    PROBE_CLK_STIMER    = 0x12,
    PROBE_CLK_USBPHY    = 0x13,
    PROBE_CLK_USBPHY1   = 0x14,
    PROBE_CLK_7816      = 0x15,
    PROBE_CLK_WT        = 0x16,
    PROBE_CLK_ZB_MST    = 0x17,
    PROBE_DBG_CLK       = 0x18,
    PROBE_CLK_ACLK_DBG  = 0x19,
    PROBE_CLK_SPLK      = 0x1a,
    PROBE_CLK_USBPHY_CLK= 0x1b,
    PROBE_CLK_USBUTMI   = 0x1c,
    PROBE_CLK_DIG       = 0x1d,
    PROBE_CLK_X2_48M    = 0x1e,
    PROBE_CLK_DSMX_48M  = 0x1f,
    PROBE_CLK_DSMB_48M  = 0x20,
} probe_clk_sel_e;

/**********************************************************************************************************************
 *                                     global variable declaration                                                    *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                      global function prototype                                                     *
 *********************************************************************************************************************/

/**
 * @brief      This function servers to enable gpio function.
 * @param[in]  pin - the selected pin.
 * @return     none.
 */
static inline void gpio_function_en(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    BM_SET(reg_gpio_func(pin), bit);
}

/**
 * @brief      This function servers to disable gpio function.
 * @param[in]  pin - the selected pin.
 * @return     none.
 */
static inline void gpio_function_dis(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    BM_CLR(reg_gpio_func(pin), bit);
}

/**
 * @brief     This function set the pin's output high level.
 * @param[in] pin - the pin needs to set its output level.
 * @return    none.
 */
static inline void gpio_set_high_level(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;

    reg_gpio_out_set(pin) = bit;

}

/**
 * @brief     This function set the pin's output low level.
 * @param[in] pin - the pin needs to set its output level.
 * @return    none.
 */
static inline void gpio_set_low_level(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    reg_gpio_out_clear(pin) = bit;
}

/**
 * @brief     This function set the pin's output level.
 * @param[in] pin - the pin needs to set its output level
 * @param[in] value - value of the output level(1: high 0: low)
 * @return    none
 */
static inline void gpio_set_level(gpio_pin_e pin, unsigned char value)
{
    if (value) {
        gpio_set_high_level(pin);
    } else {
        gpio_set_low_level(pin);
    }
}

/**
 * @brief     This function read the pin's input level.
 * @param[in] pin - the pin needs to read its input level.
 * @return    1: the pin's input level is high.
 *            0: the pin's input level is low.
 */
static inline _Bool gpio_get_level(gpio_pin_e pin)
{
    return BM_IS_SET(reg_gpio_in(pin), pin & 0xff);
}

/**
 * @brief      This function read all the pins' input level.
 * @param[out] p - the buffer used to store all the pins' input level
 * @return     none
 */
static inline void gpio_get_level_all(unsigned char *p)
{
    p[0]  = reg_gpio_pa_in;
    p[1]  = reg_gpio_pb_in;
    p[2]  = reg_gpio_pc_in;
    p[3]  = reg_gpio_pd_in;
    p[4]  = reg_gpio_pe_in;
    p[5]  = reg_gpio_pf_in;
    p[6]  = reg_gpio_pg_in;
    p[7]  = reg_gpio_ph_in;
    p[8]  = reg_gpio_pi_in;
    p[9]  = reg_gpio_pj_in;
    p[10] = reg_gpio_pk_in;
}

/**
 * @brief     This function set the pin toggle.
 * @param[in] pin - the pin needs to toggle.
 * @return    none.
 */
static inline void gpio_toggle(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    reg_gpio_out_toggle(pin) = bit;
}

/**
 * @brief      This function enable the output function of a pin.
 * @param[in]  pin - the pin needs to set the output function.
 * @return     none.
 */
static inline void gpio_output_en(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    BM_CLR(reg_gpio_oen(pin), bit);
}

/**
 * @brief      This function disable the output function of a pin.
 * @param[in]  pin - the pin needs to set the output function.
 * @return     none.
 */
static inline void gpio_output_dis(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    BM_SET(reg_gpio_oen(pin), bit);
}

/**
 * @brief      This function enable set output function of a pin.
 * @param[in]  pin - the pin needs to set the output function (1: enable,0: disable)
 * @return     none
 */
static inline void gpio_set_output(gpio_pin_e pin, unsigned char value)
{
    if (value) {
        gpio_output_en(pin);
    } else {
        gpio_output_dis(pin);
    }
}

/**
 * @brief      This function determines whether the output function of a pin is enabled.
 * @param[in]  pin - the pin needs to determine whether its output function is enabled.
 * @return     1: the pin's output function is enabled.
 *             0: the pin's output function is disabled.
 */
static inline _Bool gpio_is_output_en(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    return !BM_IS_SET(reg_gpio_oen(pin), bit);
}

/**
 * @brief     This function determines whether the input function of a pin is enabled.
 * @param[in] pin - the pin needs to determine whether its input function is enabled(not include group_pc).
 * @return    1: the pin's input function is enabled.
 *            0: the pin's input function is disabled.
 */
static inline _Bool gpio_is_input_en(gpio_pin_e pin)
{
    unsigned char bit = pin & 0xff;
    return BM_IS_SET(reg_gpio_ie(pin), bit);
}

/**
 * @brief       This function is used to enable the GPIO pin of mspi.
 * @param[in]   none.
 * @return      none.
 * @note        This interface is for internal use only.
 */
static _always_inline void gpio_set_mspi_pin_ie_en(void)
{
    reg_gpio_pj_ie = 0xff;
    reg_gpio_pi_ie = 0x3f;
}

/**
 * @brief       This function is used to disable the GPIO pin of mspi.
 * @param[in]   none.
 * @return      none.
 * @note        This interface is for internal use only.
 */
static _always_inline void gpio_set_mspi_pin_ie_dis(void)
{
    reg_gpio_pj_ie = 0x00;
    reg_gpio_pi_ie = 0x00;
}

/**
 * @brief      This function serves to enable gpio irq0~7 function.
 * @param[in]  pin  - the pin needs to enable its IRQ.
 * @param[in]  irq  - there are 8 types of irq to choose.(irq0/irq1/irq2/irq3/irq4/irq5/irq6/irq7)
 * @return     none.
 */
static inline void gpio_irq_en(gpio_pin_e pin, gpio_irq_num_e irq)
{
    BM_SET(reg_gpio_irq_en(pin, irq), pin & 0xff);
}

/**
 * @brief      This function serves to disable gpio irq0 function.
 * @param[in]  pin  - the pin needs to disable its IRQ.
 * @param[in]  irq  - there are 8 types of irq to choose.(irq0/irq1/irq2/irq3/irq4/irq5/irq6/irq7)
 * @return     none.
 */
static inline void gpio_irq_dis(gpio_pin_e pin, gpio_irq_num_e irq)
{
    BM_CLR(reg_gpio_irq_en(pin, irq), pin & 0xff);
}

/**
 * @brief      This function serves to enable gpio irq mask function.
 * @param[in]  mask  - to select interrupt type.
 * @return     none.
 */
static inline void gpio_set_irq_mask(gpio_irq_e mask)
{
    BM_SET(reg_gpio_irq_src_mask, mask);
}

/**
 * @brief      This function serves to clr gpio irq status.
 * @param[in]  status  - the irq need to clear.
 * @return     none.
 */
static inline void gpio_clr_irq_status(gpio_irq_e status)
{
    reg_gpio_irq_clr = status;
}

/**
 * @brief      This function serves to disable gpio irq mask function.
 *             if disable gpio interrupt,choose disable gpio mask , use interface gpio_clr_irq_mask instead of gpio_irq_dis/gpio_gpio2risc0_irq_dis/gpio_gpio2risc1_irq_dis.
 * @return     none.
 */
static inline void gpio_clr_irq_mask(gpio_irq_e mask)
{
    BM_CLR(reg_gpio_irq_src_mask, mask);
}

/**
 * @brief     This function set a pin's IRQ , here you can choose from 8 interrupts for flexible configuration, each interrupt is independent and equal to each other.
 * @param[in] irq           - there are 8 types of irq to choose.(irq0/irq1/irq2/irq3/irq4/irq5/irq6/irq7)
 * @param[in] pin           - the pin needs to enable its IRQ.
 * @param[in] trigger_type  - gpio interrupt type.
 *                            0: rising edge.
 *                            1: falling edge.
 *                            2: high level.
 *                            3: low level.
 * @return    none.
 */
void gpio_set_irq(gpio_irq_num_e irq, gpio_pin_e pin, gpio_irq_trigger_type_e trigger_type);

/**
 * @brief      This function serves to set the gpio-mux function.
 * @param[in]  pin      - the pin needs to set.
 * @param[in]  function - the function need to set.
 * @return     none.
 */
void gpio_set_mux_function(gpio_func_pin_e pin, gpio_func_e function);

/**
 * @brief      This function set the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function.
 * @return     none.
 */
void gpio_input_en(gpio_pin_e pin);

/**
 * @brief      This function disable the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function.
 * @return     none.
 */
void gpio_input_dis(gpio_pin_e pin);

/**
 * @brief      This function set the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function
 * @param[in]  value - enable or disable the pin's input function(1: enable,0: disable )
 * @return     none
 */
void gpio_set_input(gpio_pin_e pin, unsigned char value);

/**
 * @brief      This function servers to set the specified GPIO into High-impedance state and also enable the pull-down resistor.
 *             To prevent power leakage, you need to call gpio_shutdown(GPIO_ALL) (set all gpio to high resistance, except SWS and MSPI)
 *             as front as possible in the program, and then initialize the corresponding GPIO according to the actual using situation.
 * @param[in]  pin  - select the specified GPIO.Only support GPIO_GROUPA ~GPIO_GROUPI,GPIO_GPOUPANA and GPIO_ALL.
 * @note       The analog pull-up/down registers are configured at group granularity:
 *             when a single pin of GPIO_GROUPA ~ GPIO_GROUPH is passed in, all pins of that group
 *             (including the pins not specified by "pin") are forced to 100K pull-down, overwriting
 *             their existing pull-up/down configurations. If other pins in the same group need a
 *             different pull setting, call gpio_set_up_down_res() afterwards to restore it.
 *             GPIO_GROUPI ~ GPIO_GROUPK have no analog pull-down resistor, so only the digital
 *             registers are modified for them.
 * @return     none.
 */
void gpio_shutdown(gpio_pin_e pin);

/**
 * @brief     This function set a pin's pull-up/down resistor.
 * @param[in] pin - the pin needs to set its pull-up/down resistor.
 * @param[in] up_down_res - the type of the pull-up/down resistor.
 * @return    none.
 */
void gpio_set_up_down_res(gpio_pin_e pin, gpio_pull_type_e up_down_res);

/**
 * @brief     This function set pin's  pull-down register.
 * @param[in] pin - the pin needs to set its pull-down register.
 * @return    none.
 * @attention  This function sets the digital pull-down, it will not work after entering low power consumption.
 */
void gpio_set_digital_pulldown(gpio_pin_e pin);

/**
 * @brief     This function set pin's  pull-up register.
 * @param[in] pin - the pin needs to set its pull-up register.
 * @return    none.
 * @attention  This function sets the digital pull-up, it will not work after entering low power consumption.
 */
void gpio_set_digital_pullup(gpio_pin_e pin);

/**
 * @brief     This function disable pin's  pull-down register.
 * @param[in] pin - the pin needs to disable its pull-down register.
 * @return    none.
 */
void gpio_digital_pulldown_dis(gpio_pin_e pin);

/**
 * @brief     This function disable pin's  pull-up register.
 * @param[in] pin - the pin needs to disable its pull-up register.
 * @return    none.
 */
void gpio_digital_pullup_dis(gpio_pin_e pin);

/**
 * @brief     This function is used to enable the JTAG function of the dsp.
 * @param[in] dsp_jtag_pin - the pin selected as the DSP_JTAG.
 * @return    none.
 */
void dsp_jtag_enable(dsp_jtag_pin_st *dsp_jtag_pin);

/**
 * @brief     This function set probe clk output.
 * @param[in] pin
 * @param[in] sel_clk
 * @return    none.
 */
void gpio_set_probe_clk_function(gpio_func_pin_e pin, probe_clk_sel_e sel_clk);

/**
 * @brief     This function serves to set jtag(4 wires) pin . Where, PD[6]; PD[5]; PD[4]; PD[3] correspond to TDI; TDO; TMS; TCK functions mux respectively.
 * @param[in] none
 * @return    none.
 * @note      Power-on or hardware reset will detect the level of PB6 (reboot will not detect it), detecting a low level is configured as jtag,
               detecting a high level is configured as sdp.  the level of PB6 can not be configured internally by the software, and can only be input externally.
 */
void jtag_set_pin_en(void);

/**
 * @brief     This function serves to set sdp(2 wires) pin . where, PD[4]; PD[3] correspond to TMS and TCK functions mux respectively.
 * @param[in] none
 * @return    none.
 * @note      Power-on or hardware reset will detect the level of PB6 (reboot will not detect it), detecting a low level is configured as jtag,
               detecting a high level is configured as sdp.  the level of PB6 can not be configured internally by the software, and can only be input externally.
 */
void sdp_set_pin_en(void);
#endif
/********************************************************************************************************
 * @file    hal_rf_common.h
 *
 * @brief   This is the header file for tl752x
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#ifndef __HAL_RF_COMMON_H__
#define __HAL_RF_COMMON_H__

#include "bit.h"
#include "compiler.h"
#include "hal/hal_rf_dma.h"
#include "hal/hal_rf_ble.h"
#include "hal/hal_rf_private.h"
#include "hal/hal_systimer.h"

#define rf_set_power_level_index_singletone(power_level) rf_set_power_level_singletone(power_level)
/**********************************************************************************************************************
 *                                         RF  global macro                                                           *
 *********************************************************************************************************************/

/**
 * @brief       This define for ble debug the effect of rx_dly.
 *              when this function turn on the time of rx_dly will shorten 6.3us,
 */
#define RF_RX_SHORT_MODE_EN 1 //In order to debug whether the problem is caused by rx_dly.
/**
 *  @brief This define serve to calculate the DMA length of packet.
 */
#define rf_tx_packet_dma_len(rf_data_len) (((rf_data_len) + 3) / 4) | (((rf_data_len) % 4) << 22)

/**
 *  @brief This macro provides an alternative name for the rf_get_latched_rssi() function to be compatible with older versions of code
 */
#define rf_get_rssi rf_get_latched_rssi

/**********************************************************************************************************************
 *                                       RF global data type                                                          *
 *********************************************************************************************************************/
typedef enum
{
    RF_BT_MODE  = BIT(0),
    RF_TAHDT_MODE = BIT(1),
    RF_BLE_MODE = BIT(2),
} rf_mode_init_e;
typedef enum
{
    RF_MODEM_48M = 0,
    RF_MODEM_24M = 1,
} rf_modem_clk_e;

/**
 * @brief       RF CRC config.
 * @note        init_value - The CRC init value to be set for RF.
 *              poly - The CRC polynomial to be set for RF.
 *              xor_out - XOR mask for CRC result (for no mask, should be 0)
 *              byte_order - CRC output byte order (1:MSByte first,0:LSByte first)
 *              start_cal_pos - CRC start byte position, 0 is the first byte
 *              len - The CRC length to be set for RF
 */
typedef struct
{
    unsigned int  init_value;
    unsigned int  poly;
    unsigned int  xor_out;
    unsigned char byte_order;
    unsigned char start_cal_pos;
    unsigned char len;
} rf_crc_config_t;

/**
 *  @brief  select status of rf.
 */
typedef enum
{
    RF_MODE_TX   = 0, /**<  Tx mode */
    RF_MODE_RX   = 1, /**<  Rx mode */
    RF_MODE_AUTO = 2, /**<  Auto mode */
    RF_MODE_OFF  = 3  /**<  TXRX OFF mode */
} rf_status_e;

/**
 *  @brief   Define power list of RF.
 *  @note    (1)The energy meter is averaged over 3 chips at room temperature and 3.3V supply voltage..
 *           (2)There will be some differences in the energy values tested between different chips.
 *           (3)The power values in comments are the averaged measured data of three calibrated chips.
 *              Test Conditions: VBAT powered at 3.3V, RF PA powered by VBUCK DIG, TP modulation and IQ modulation.
 *              Test Hardware: C1T387A20_V1_1
 *              Test Chips: TL7523AE, THBE2549, MBA900.02(A1)
 */
typedef enum
{
    /*VBAT LDO*/
    RF_VBAT_POWER_LEVEL_MAX = BIT(7)|63,
    /*VBUCK LDO*/           /* VBUCK TP MODE | VBUCK IQ MODE */
    RF_POWER_LEVEL_MAX = 63, /**<  13.73 dbm | 12.32 dbm */  
    RF_POWER_LEVEL_62 = 62,  /**<  13.70 dbm | 12.28 dbm */  
    RF_POWER_LEVEL_61 = 61,  /**<  13.68 dbm | 12.24 dbm */  
    RF_POWER_LEVEL_60 = 60,  /**<  13.65 dbm | 12.20 dbm */  
    RF_POWER_LEVEL_59 = 59,  /**<  13.62 dbm | 12.16 dbm */  
    RF_POWER_LEVEL_58 = 58,  /**<  13.59 dbm | 12.12 dbm */   
    RF_POWER_LEVEL_57 = 57,  /**<  13.56 dbm | 12.07 dbm */   
    RF_POWER_LEVEL_56 = 56,  /**<  13.53 dbm | 12.03 dbm */  
    RF_POWER_LEVEL_55 = 55,  /**<  13.51 dbm | 11.98 dbm */  
    RF_POWER_LEVEL_54 = 54,  /**<  13.48 dbm | 11.93 dbm */  
    RF_POWER_LEVEL_53 = 53,  /**<  13.44 dbm | 11.88 dbm */  
    RF_POWER_LEVEL_52 = 52,  /**<  13.41 dbm | 11.82 dbm */  
    RF_POWER_LEVEL_51 = 51,  /**<  13.37 dbm | 11.77 dbm */  
    RF_POWER_LEVEL_50 = 50,  /**<  13.34 dbm | 11.71 dbm */  
    RF_POWER_LEVEL_49  = 49, /**<  13.30 dbm | 11.63 dbm */  
    RF_POWER_LEVEL_48  = 48, /**<  13.26 dbm | 11.57 dbm */  
    RF_POWER_LEVEL_47  = 47, /**<  13.25 dbm | 11.51 dbm */  
    RF_POWER_LEVEL_46  = 46, /**<  13.21 dbm | 11.44 dbm */  
    RF_POWER_LEVEL_45  = 45, /**<  13.16 dbm | 11.36 dbm */
    RF_POWER_LEVEL_44  = 44, /**<  13.11 dbm | 11.27 dbm */
    RF_POWER_LEVEL_43  = 43, /**<  13.06 dbm | 11.19 dbm */
    RF_POWER_LEVEL_42  = 42, /**<  13.01 dbm | 11.10 dbm */
    RF_POWER_LEVEL_41  = 41, /**<  12.96 dbm | 11.00 dbm */
    RF_POWER_LEVEL_40  = 40, /**<  12.90 dbm | 10.89 dbm */
    RF_POWER_LEVEL_39  = 39, /**<  12.85 dbm | 10.78 dbm */
    RF_POWER_LEVEL_38  = 38, /**<  12.78 dbm | 10.67 dbm */
    RF_POWER_LEVEL_37  = 37, /**<  12.72 dbm | 10.55 dbm */
    RF_POWER_LEVEL_36  = 36, /**<  12.64 dbm | 10.42 dbm */
    RF_POWER_LEVEL_35  = 35, /**<  12.58 dbm | 10.28 dbm */
    RF_POWER_LEVEL_34  = 34, /**<  12.50 dbm | 10.13 dbm */
    RF_POWER_LEVEL_33  = 33, /**<  12.41 dbm | 9.98 dbm */
    RF_POWER_LEVEL_32  = 32, /**<  12.32 dbm | 9.81 dbm */
    RF_POWER_LEVEL_31  = 31, /**<  12.31 dbm | 9.68 dbm */
    RF_POWER_LEVEL_30  = 30, /**<  12.21 dbm | 9.48 dbm */
    RF_POWER_LEVEL_29  = 29, /**<  12.11 dbm | 9.28 dbm */
    RF_POWER_LEVEL_28  = 28, /**<  11.99 dbm | 9.07 dbm */
    RF_POWER_LEVEL_27  = 27, /**<  11.88 dbm | 8.84 dbm */
    RF_POWER_LEVEL_26  = 26, /**<  11.75 dbm | 8.59 dbm */
    RF_POWER_LEVEL_25  = 25, /**<  11.61 dbm | 8.32 dbm */
    RF_POWER_LEVEL_24  = 24, /**<  11.46 dbm | 8.03 dbm */
    RF_POWER_LEVEL_23  = 23, /**<  11.30 dbm | 7.73 dbm */
    RF_POWER_LEVEL_22  = 22, /**<  11.12 dbm | 7.40 dbm */
    RF_POWER_LEVEL_21  = 21, /**<  10.93 dbm | 7.06 dbm */
    RF_POWER_LEVEL_20  = 20, /**<  10.71 dbm | 6.68 dbm */
    RF_POWER_LEVEL_19  = 19, /**<  10.49 dbm | 6.29 dbm */
    RF_POWER_LEVEL_18  = 18, /**<  10.22 dbm | 5.86 dbm */
    RF_POWER_LEVEL_17  = 17, /**<  9.93 dbm | 5.40 dbm */
    RF_POWER_LEVEL_16  = 16, /**<  9.60 dbm | 4.91 dbm */
    RF_POWER_LEVEL_15  = 15, /**<  9.31 dbm | 4.39 dbm */
    RF_POWER_LEVEL_14  = 14, /**<  8.89 dbm | 3.82 dbm */
    RF_POWER_LEVEL_13  = 13, /**<  8.43 dbm | 3.21 dbm */
    RF_POWER_LEVEL_12  = 12, /**<  7.88 dbm | 2.54 dbm */
    RF_POWER_LEVEL_11  = 11, /**<  7.30 dbm | 1.82 dbm */
    RF_POWER_LEVEL_10  = 10, /**<  6.58 dbm | 1.01 dbm */
    RF_POWER_LEVEL_9   = 9,  /**<  5.79 dbm | 0.13 dbm */
    RF_POWER_LEVEL_8   = 8,  /**<  4.85 dbm | -0.87 dbm */
    RF_POWER_LEVEL_7   = 7,  /**<  3.81 dbm | -1.99 dbm */
    RF_POWER_LEVEL_6   = 6,  /**<  2.53 dbm | -3.31 dbm */
    RF_POWER_LEVEL_5   = 5,  /**<  1.05 dbm | -4.84 dbm */
    RF_POWER_LEVEL_4   = 4,  /**<  -0.84 dbm | -6.76 dbm */
    RF_POWER_LEVEL_3   = 3,  /**<  -3.18 dbm | -9.19 dbm */
    RF_POWER_LEVEL_2   = 2,  /**<  -6.65 dbm | -12.64 dbm */
    RF_POWER_LEVEL_1   = 1,  /**<  -12.41 dbm | -18.43 dbm */
    RF_POWER_LEVEL_MIN = 0,  /**<  -42.87 dbm | -43.06 dbm */
} rf_power_level_e;

/**
 *  @brief   Define power list of RF.
 *  @note    (1)The energy meter is averaged over 3 chips at room temperature and 3.3V supply voltage..
 *           (2)There will be some differences in the energy values tested between different chips.
 *           (3)The power values in comments are the averaged measured data of three calibrated chips.
 *              Test Conditions: VBAT powered at 3.3V, RF PA powered by VBUCK DIG, TP modulation and IQ modulation.
 *              Test Hardware: C1T387A20_V1_1
 *              Test Chips: TL7523AE, THBE2549, MBA900.02(A1)
 */
typedef enum
{
    /*VBAT LDO*/
    RF_VBAT_POWER_INDEX_LEVEL_MAX,
    /*VBUCK LDO*/             /* VBUCK TP MODE | VBUCK IQ MODE */
    RF_POWER_INDEX_LEVEL_MAX,  /**<  13.73 dbm | 12.32 dbm */
    RF_POWER_INDEX_LEVEL_62,   /**<  13.70 dbm | 12.28 dbm */
    RF_POWER_INDEX_LEVEL_61,   /**<  13.68 dbm | 12.24 dbm */
    RF_POWER_INDEX_LEVEL_60,   /**<  13.65 dbm | 12.20 dbm */
    RF_POWER_INDEX_LEVEL_59,   /**<  13.62 dbm | 12.16 dbm */
    RF_POWER_INDEX_LEVEL_58,   /**<  13.59 dbm | 12.12 dbm */
    RF_POWER_INDEX_LEVEL_57,   /**<  13.56 dbm | 12.07 dbm */
    RF_POWER_INDEX_LEVEL_56,   /**<  13.53 dbm | 12.03 dbm */
    RF_POWER_INDEX_LEVEL_55,   /**<  13.51 dbm | 11.98 dbm */
    RF_POWER_INDEX_LEVEL_54,   /**<  13.48 dbm | 11.93 dbm */
    RF_POWER_INDEX_LEVEL_53,   /**<  13.44 dbm | 11.88 dbm */
    RF_POWER_INDEX_LEVEL_52,   /**<  13.41 dbm | 11.82 dbm */
    RF_POWER_INDEX_LEVEL_51,   /**<  13.37 dbm | 11.77 dbm */
    RF_POWER_INDEX_LEVEL_50,   /**<  13.34 dbm | 11.71 dbm */
    RF_POWER_INDEX_LEVEL_49,   /**<  13.30 dbm | 11.63 dbm */
    RF_POWER_INDEX_LEVEL_48,   /**<  13.26 dbm | 11.57 dbm */
    RF_POWER_INDEX_LEVEL_47,   /**<  13.25 dbm | 11.51 dbm */
    RF_POWER_INDEX_LEVEL_46,   /**<  13.21 dbm | 11.44 dbm */
    RF_POWER_INDEX_LEVEL_45,   /**<  13.16 dbm | 11.36 dbm */
    RF_POWER_INDEX_LEVEL_44,   /**<  13.11 dbm | 11.27 dbm */
    RF_POWER_INDEX_LEVEL_43,   /**<  13.06 dbm | 11.19 dbm */
    RF_POWER_INDEX_LEVEL_42,   /**<  13.01 dbm | 11.10 dbm */
    RF_POWER_INDEX_LEVEL_41,   /**<  12.96 dbm | 11.00 dbm */
    RF_POWER_INDEX_LEVEL_40,   /**<  12.90 dbm | 10.89 dbm */
    RF_POWER_INDEX_LEVEL_39,   /**<  12.85 dbm | 10.78 dbm */
    RF_POWER_INDEX_LEVEL_38,   /**<  12.78 dbm | 10.67 dbm */
    RF_POWER_INDEX_LEVEL_37,   /**<  12.72 dbm | 10.55 dbm */
    RF_POWER_INDEX_LEVEL_36,   /**<  12.64 dbm | 10.42 dbm */
    RF_POWER_INDEX_LEVEL_35,   /**<  12.58 dbm | 10.28 dbm */
    RF_POWER_INDEX_LEVEL_34,   /**<  12.50 dbm | 10.13 dbm */
    RF_POWER_INDEX_LEVEL_33,   /**<  12.41 dbm | 9.98 dbm  */
    RF_POWER_INDEX_LEVEL_32,   /**<  12.32 dbm | 9.81 dbm  */
    RF_POWER_INDEX_LEVEL_31,   /**<  12.31 dbm | 9.68 dbm  */
    RF_POWER_INDEX_LEVEL_30,   /**<  12.21 dbm | 9.48 dbm  */
    RF_POWER_INDEX_LEVEL_29,   /**<  12.11 dbm | 9.28 dbm  */
    RF_POWER_INDEX_LEVEL_28,   /**<  11.99 dbm | 9.07 dbm  */
    RF_POWER_INDEX_LEVEL_27,   /**<  11.88 dbm | 8.84 dbm  */
    RF_POWER_INDEX_LEVEL_26,   /**<  11.75 dbm | 8.59 dbm  */
    RF_POWER_INDEX_LEVEL_25,   /**<  11.61 dbm | 8.32 dbm  */
    RF_POWER_INDEX_LEVEL_24,   /**<  11.46 dbm | 8.03 dbm  */
    RF_POWER_INDEX_LEVEL_23,   /**<  11.30 dbm | 7.73 dbm  */
    RF_POWER_INDEX_LEVEL_22,   /**<  11.12 dbm | 7.40 dbm  */
    RF_POWER_INDEX_LEVEL_21,   /**<  10.93 dbm | 7.06 dbm  */
    RF_POWER_INDEX_LEVEL_20,   /**<  10.71 dbm | 6.68 dbm  */
    RF_POWER_INDEX_LEVEL_19,   /**<  10.49 dbm | 6.29 dbm  */
    RF_POWER_INDEX_LEVEL_18,   /**<  10.22 dbm | 5.86 dbm  */
    RF_POWER_INDEX_LEVEL_17,   /**<  9.93 dbm  | 5.40 dbm  */
    RF_POWER_INDEX_LEVEL_16,   /**<  9.60 dbm  | 4.91 dbm  */
    RF_POWER_INDEX_LEVEL_15,   /**<  9.31 dbm  | 4.39 dbm  */
    RF_POWER_INDEX_LEVEL_14,   /**<  8.89 dbm  | 3.82 dbm  */
    RF_POWER_INDEX_LEVEL_13,   /**<  8.43 dbm  | 3.21 dbm  */
    RF_POWER_INDEX_LEVEL_12,   /**<  7.88 dbm  | 2.54 dbm  */
    RF_POWER_INDEX_LEVEL_11,   /**<  7.30 dbm  | 1.82 dbm  */
    RF_POWER_INDEX_LEVEL_10,   /**<  6.58 dbm  | 1.01 dbm  */
    RF_POWER_INDEX_LEVEL_9,    /**<  5.79 dbm  | 0.13 dbm  */
    RF_POWER_INDEX_LEVEL_8,    /**<  4.85 dbm  | -0.87 dbm */
    RF_POWER_INDEX_LEVEL_7,    /**<  3.81 dbm  | -1.99 dbm */
    RF_POWER_INDEX_LEVEL_6,    /**<  2.53 dbm  | -3.31 dbm */
    RF_POWER_INDEX_LEVEL_5,    /**<  1.05 dbm  | -4.84 dbm */
    RF_POWER_INDEX_LEVEL_4,    /**<  -0.84 dbm | -6.76 dbm */
    RF_POWER_INDEX_LEVEL_3,    /**<  -3.18 dbm | -9.19 dbm */
    RF_POWER_INDEX_LEVEL_2,    /**<  -6.65 dbm | -12.64 dbm*/
    RF_POWER_INDEX_LEVEL_1,    /**<  -12.41 dbm| -18.43 dbm*/
    RF_POWER_INDEX_LEVEL_MIN,  /**<  -42.87 dbm| -43.06 dbm*/
} rf_power_level_index_e;

/**
 *  @brief  Define RF mode.
 */
typedef enum
{
    RF_MODE_BLE_2M           = BIT(0),        /**< ble 2m mode */
    RF_MODE_BLE_1M           = BIT(1),        /**< ble 1M mode */
    RF_MODE_BLE_1M_NO_PN     = BIT(2),        /**< ble 1M close pn mode */
    RF_MODE_ZIGBEE_250K      = BIT(3),        /**< zigbee 250K mode */
    RF_MODE_LR_S2_500K       = BIT(4),        /**< ble 500K mode */
    RF_MODE_LR_S8_125K       = BIT(5),        /**< ble 125K mode */
    RF_MODE_PRIVATE_250K     = BIT(6),        /**< private 250K mode */
    RF_MODE_PRIVATE_500K     = BIT(7),        /**< private 500K mode */
    RF_MODE_PRIVATE_1M       = BIT(8),        /**< private 1M mode */
    RF_MODE_PRIVATE_2M       = BIT(9),        /**< private 2M mode */
    RF_MODE_ANT              = BIT(10),       /**< ant mode */
    RF_MODE_BLE_2M_NO_PN     = BIT(11),       /**< ble 2M close pn mode */
    RF_MODE_HYBEE_1M         = BIT(12),       /**< hybee 1M mode */
    RF_MODE_HYBEE_2M         = BIT(13),       /**< hybee 2M mode */
    RF_MODE_HYBEE_500K       = BIT(14),       /**< hybee 500K mode */
    RF_MODE_PRI_GENERIC_250K = BIT(17),       /**< private generic 250K mode */
    RF_MODE_PRI_GENERIC_500K = BIT(18),       /**< private generic 500K mode */
    RF_MODE_PRI_GENERIC_1M   = BIT(19),       /**< private generic 1M mode */
    RF_MODE_PRI_GENERIC_2M   = BIT(20),       /**< private generic 2M mode */
    RF_MODE_BLE_4M_NO_PN     = BIT(21),        /**< ble 4M close pn mode */
    RF_MODE_BLE_4M           = BIT(22),        /**< ble 4M pn mode */
#if (0)
    RF_MODE_LOW_RATE_20K           = BIT(19), /**< low rate 20K mode */
    RF_MODE_LOW_RATE_25K           = BIT(20), /**< low rate 25K mode */
    RF_MODE_LOW_RATE_100K          = BIT(21), /**< low rate 100K mode */
    RF_MODE_HYBEE_1M_OLD           = BIT(22), /**< hybee 1M mode old*/
    RF_MODE_HYBEE_2M_OLD           = BIT(23), /**< hybee 2M mode old*/
    RF_MODE_HYBEE_500K_NEW         = BIT(24), /**< hybee 500k mode new*/
    RF_MODE_HYBEE_1M_NEW           = BIT(25), /**< hybee 1M mode new*/
    RF_MODE_HYBEE_2M_NEW           = BIT(26), /**< hybee 2M mode new*/
    RF_MODE_HYBEE_500K_2BYTE_SFD   = BIT(27), /**< hybee 500K 2byte sfd mode*/
    RF_MODE_HYBEE_1M_2BYTE_SFD     = BIT(28), /**< hybee 1M 2byte sfd mode*/
    RF_MODE_HYBEE_2M_2BYTE_SFD     = BIT(29), /**< hybee 2M 2byte sfd mode*/
    RF_MODE_HYBEE_2M_2BYTE_SFD_NEW = BIT(30), /**< hybee 2M 2byte sfd mode new*/
    RF_MODE_HR_2M                  = BIT(31), /**< hr 2M mode*/
#endif

} rf_mode_e;

/**
 *  @brief  Define RF channel.
 */
typedef enum
{
    RF_CHANNEL_0 = BIT(0), /**< RF channel 0 */
    RF_CHANNEL_1 = BIT(1), /**< RF channel 1 */
    RF_CHANNEL_2 = BIT(2), /**< RF channel 2 */
    RF_CHANNEL_3 = BIT(3), /**< RF channel 3 */
    RF_CHANNEL_4 = BIT(4), /**< RF channel 4 */
    RF_CHANNEL_5 = BIT(5), /**< RF channel 5 */
    /**When using PTX,PRX + MultiCeiver function, chn6,7 is not available.**/
    RF_CHANNEL_6    = BIT(6), /**< RF channel 6 */
    RF_CHANNEL_7    = BIT(7), /**< RF channel 7 */
    RF_CHANNEL_NONE = 0x00,   /**< none RF channel*/
    RF_CHANNEL_ALL  = 0xff,   /**< all RF channel */
} rf_channel_e;

/**
 * @brief define rf bb timer clock tick per us/ms/s.
 */
enum
{
    BB_TIMER_TICK_1US = 8,
    BB_TIMER_TICK_1MS = 8000,
    BB_TIMER_TICK_1S  = 8000000,
};

/**
 * @brief Define RX performance modes, RF_RX_LOW_POWER and RF_RX_HIGH_PERFORMANCE
 * @note  Defaults to RF_RX_LOW_POWER for A1.
 *        RF_RX_HIGH_PERFORMANCE mode can improve performance by 1dBm, but the rx power consumption will increase
 */
typedef enum
{
    RF_RX_LOW_POWER        = 0,
    RF_RX_HIGH_PERFORMANCE = 1,
} rf_rx_performance_e;

/**********************************************************************************************************************
 *                                         RF global constants                                                        *
 *********************************************************************************************************************/
extern const rf_power_level_e rf_power_Level_list[65];
extern rf_mode_e              g_rfmode;
extern rf_crc_config_t        rf_crc_config[3];
extern _attribute_data_retention_sec_ unsigned char g_rf_modem_clk48m_flag;
/**********************************************************************************************************************
 *                                         RF function declaration                                                    *
 *********************************************************************************************************************/

/**
 * @brief       This function serves to judge the statue of  RF receive.
 * @return      -#0:idle
 *              -#1:rx_busy
 */
static _always_inline unsigned char rf_receiving_flag(void)
{
    //if the value of [2:0] of the reg_0x50425040 isn't 0 , it means that the RF is in the receiving packet phase.(confirmed by junwen).
    return ((read_reg8(0x50425040) & 0x07) > 1);
}

/**
 * @brief       This function serves to set the which irq enable.
 * @param[in]   mask    - Options that need to be enabled.
 * @return      Yes: 1, NO: 0.
 */
static inline void rf_set_irq_mask(rf_irq_e mask)
{
    BM_SET(reg_rf_irq_mask, mask);
    BM_SET(reg_rf_ll_irq_mask_h, (mask & 0xff0000) >> 16);
    BM_SET(reg_rf_ll_cmd, (mask & 0x5000000) >> 20);
    BM_SET(reg_rf_ll_irq_mask_h1, (mask & 0x2000000) >> 24);
}

/**
 * @brief       This function serves to clear the TX/RX irq mask.
 * @param[in]   mask    - RX/TX irq value.
 * @return      none.
 */
static inline void rf_clr_irq_mask(rf_irq_e mask)
{
    BM_CLR(reg_rf_irq_mask, mask);
    BM_CLR(reg_rf_ll_irq_mask_h, (mask & 0xff0000) >> 16);
    BM_CLR(reg_rf_ll_cmd, (mask & 0x5000000) >> 20);
    BM_CLR(reg_rf_ll_irq_mask_h1, (mask & 0x2000000) >> 24);
}

/**
 *  @brief      This function serves to judge whether it is in a certain state.
 *  @param[in]  mask      - RX/TX irq status.
 * @retval      non-zero      -  the interrupt occurred.
 * @retval      zero  -  the interrupt did not occur.
 */
static inline unsigned int rf_get_irq_status(rf_irq_e status)
{
    return ((unsigned int)(BM_IS_SET(reg_rf_irq_status, status) | BM_IS_SET((reg_rf_irq_status_h << 16), status) | BM_IS_SET((reg_rf_irq_status_h1 << 24), status)));
}

/**
 *@brief    This function serves to clear the Tx/Rx finish flag bit.
 *          After all packet data are sent, corresponding Tx finish flag bit
 *          will be set as 1.By reading this flag bit, it can check whether
 *          packet transmission is finished. After the check, it is needed to
 *          manually clear this flag bit so as to avoid misjudgment.
 *@return   none.
 */
static inline void rf_clr_irq_status(rf_irq_e status)
{
    reg_rf_irq_status    = status;
    reg_rf_irq_status_h  = (status & 0xff0000) >> 16;
    reg_rf_irq_status_h1 = (status & 0x7000000) >> 24;
}

/**
 * @brief       This function serves to set RF access code.
 * @param[in]   acc   - the value of access code.
 * @return      none.
 */
static inline void rf_access_code_comm(unsigned int acc)
{
    reg_rf_access_code = acc;
    //The following two lines of code are for trigger access code in S2,S8 mode.It has no effect on other modes.
    reg_rf_modem_mode_cfg_rx1_0 &= ~FLD_RF_LR_TRIG_MODE;
    write_reg8(0x50425425, read_reg8(0x50425425) | 0x01);
}

/**
 * @brief       this function is to enable/disable each access_code channel for
 *              RF Rx terminal.
 * @param[in]   pipe    - Bit0~bit7 correspond to channel 0~7, respectively.
 *                      - #0:Disable.
 *                      - #1:Enable.
 *                        If "enable" is set as 0xff (i.e. 11111111),
 *                        all access_code channels (0~7) are enabled.
 * @return      none
 */
static inline void rf_rx_acc_code_pipe_en(rf_channel_e pipe)
{
    reg_rf_modem_rx_ctrl_1 = pipe; //rx_access_code_chn_en
}

/**
 * @brief       this function is to select access_code channel for RF tx terminal.
 * @param[in]   pipe    - tx access code channel,The pipe range is from 0 to 7
 *                        And only 1 channel can be selected every time.
 *                        If "enable" is set as 0x7 (i.e. 0111),the access_code channel (7) is enabled.
 * @return      none
 */
static inline void rf_tx_acc_code_pipe_en(rf_channel_e pipe)
{
    write_reg8(0x50425215, ((read_reg8(0x50425215) & 0xf8) | pipe) | BIT(4)); //Tx_Channel_man[2:0]
}

/**
 * @brief     This function serves to reset RF Tx/Rx mode.
 * @return    none.
 */
static _always_inline void rf_set_tx_rx_off(void)
{
    write_reg8(0x50425216, 0x29);
    write_reg8(0x50425028, 0x80); // rx disable
    write_reg8(0x50425202, 0x45); // reset tx/rx state machine
}

/**
 * @brief    This function serves to turn off RF auto mode.
 * @return   none.
 * @note     Attention: When forcibly stopping the state machine through this interface, it must be ensured
 *           that rx is not in the process of receiving packets.Otherwise, an error may be caused.To determine
 *           whether the packet is being received, you can use the function rf_receiving_flag.
 */
static inline void rf_set_tx_rx_off_auto_mode(void)
{
    reg_rf_ll_cmd = FLD_RF_R_CMD_TRIG;
}

/**
 * @brief       This function serve to rx dma fifo size.
 * @param[in]   fifo_byte_size - The length of one dma fifo,the range is 1~0xffff(the corresponding number of fifo bytes is fifo_byte_size).
 * @return      none
 */
static inline void rf_set_rx_dma_fifo_size(unsigned short fifo_byte_size)
{
    reg_rf_bb_rx_size   = fifo_byte_size & 0xff;
    reg_rf_bb_rx_size_h = fifo_byte_size >> 8;
}

/**
 * @brief       This function serve to set rx dma wptr.
 * @param[in]   fifo_num    -This parameter is used to set the mask value for the number of enabled FIFOs. The value of the mask must (0x00,0x01,0x03,0x07,0x0f,0x1f).
 *                           The number of FIFOs enabled is the value of wptr_mask plus 1.(0x01,0x02,0x04,0x08,0x10,0x20)
 * @return      none
 */
static inline void rf_set_rx_dma_fifo_num(unsigned char fifo_num)
{
    reg_rf_rx_wptr_mask = fifo_num;
}

/**
 * @brief       This function serves to DMA rxFIFO address
 *              The function apply to the configuration of one rxFiFO when receiving packets,
 *              In this case,the rxFiFo address can be changed every time a packet is received
 *              Before setting, call the function "rf_set_rx_dma" to clear DMA fifo mask value(set 0)
 * @param[in]   rx_addr   - The address store receive packet.
 * @return      none
 * @note        rx_addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 *              Hardware limitation: RF DMA can only access addresses within the MCU B core's DLM range (0x50080000 ~ 0x5009FFFF).
 *              Caller must ensure 'addr' falls within this range, otherwise a bus error or data corruption may occur.
 */
static inline void rf_set_rx_buffer(unsigned char *rx_addr)
{
    rx_addr += 4;
    rf_dma_set_dst_address(RF_RX_DMA, (0x50080000)|((unsigned int)(rx_addr)));
}

/**
 * @brief       This function serve to set the number of tx dma fifo.
 * @param[in]   fifo_dep - the number of dma fifo is 2 to the power of fifo_dep.
 * @return      none
 */
static inline void rf_set_tx_dma_fifo_num(unsigned char fifo_num)
{
    reg_rf_bb_tx_chn_dep = fifo_num; //tx_chn_dep = 2^2 =4 (have 4 fifo)
}

/**
 * @brief       This function serve to set the number of tx dma fifo.
 * @param[in]   fifo_byte_size - the size of each dma fifo.
 * @return      none
 */
static inline void rf_set_tx_dma_fifo_size(unsigned short fifo_byte_size)
{
    reg_rf_bb_tx_size   = fifo_byte_size & 0xff; //tx_idx_addr = {tx_chn_adr*bb_tx_size,4'b0}// in this setting the max data in one dma buffer is 0x20<<4.And the The product of fifo_dep and bytesize cannot exceed 0xfff.
    reg_rf_bb_tx_size_h = fifo_byte_size >> 8;
}

/**
 * @brief   This function serves to set RF tx settle time.
 * @param[in]  tx_stl_us  tx settle time,the unit is us.The max value of this param is 0xfff;The default settling time value is 150us.
 *             The typical value is 121us (tx_settle time should not be less than this value).
 * @return  none.
 * @note       Attention:It is not necessary to call this function to adjust the settling time in the normal sending state.
 */
static inline void rf_set_tx_settle_time(unsigned short tx_stl_us)
{
    tx_stl_us &= 0x0fff;
    write_reg16(0x50425204, (read_reg16(0x50425204) & 0xf000) | (tx_stl_us - 1));
}

/**
 * @brief   This function serves to set RF tx settle time and rx settle time.
 * @param[in]  rx_stl_us  rx settle time,the unit is us.The max value of this param is 0xfff;The default settling time value is 150us.
 *             The typical value is 93us (rx_settle time should not be less than this value).
 * @return  none.
 * @note       Attention:It is not necessary to call this function to adjust the settling time in the normal packet receiving state.
 */
static inline void rf_set_rx_settle_time(unsigned short rx_stl_us)
{
    rx_stl_us &= 0x0fff;
    write_reg16(0x5042520c, (read_reg16(0x5042520c) & 0xf000) | (rx_stl_us - 1));
}

/**
 * @brief       This function serves to set CRC length for RF.
 * @param[in]   len - The CRC length to be set for RF,the range is 0~4byte.
 * @return      none.
 * @note        Attention:when CRC length is 0,TX need to disable CRC.
 */
static inline void rf_set_crc_len(unsigned char len)
{
    reg_rf_crc_config2 = ((reg_rf_crc_config2 & (~FLD_RF_CRC_LENGTH)) | len);
}

/**
 * @brief       This function serves to set CRC value for RF.
 * @param[in]   init_value - The CRC init value to be set for RF.
 * @return      none.
 */
static inline void rf_set_crc_init_value(unsigned int init_value)
{
    reg_rf_crc_init = init_value;
}

/**
 * @brief       This function serves to set CRC polynomial for RF.
 * @param[in]   poly - The CRC polynomial to be set for RF.
 *              For example, to set CRC polynomial(BLE CRC-24):
 *              crc_poly = x^24 + x^10 + x^9 + x^6 + x^4 + x^3 + x + 1
 *              the crc_poly value would be 0x65b.
 * @return      none.
 */
static inline void rf_set_crc_poly(unsigned int poly)
{
    reg_rf_crc_poly = poly;
}

/**
 * @brief       This function serves to set CRC start byte for RF.
 * @param[in]   byte_pos - CRC start byte position, 0 is the first byte
 *              ble:The starting position of the PDU header.
 *              private:The starting position of the data packet
 *              zigbee:The starting position is the first byte after SHR.
 * @return      none.
 */
static inline void rf_set_crc_start_cal_byte_pos(unsigned char byte_pos)
{
    reg_rf_crc_config1 = (reg_rf_crc_config1 & (~FLD_RF_CRC_START_BYTE)) | byte_pos;
}

/**
 * @brief       This function serves to set the XOR value of the CRC result for RF.
 * @param[in]   xor_value - XOR mask for CRC result (for no mask, should be 0)
 * @return      none.
 */
static inline void rf_set_crc_xor_out(unsigned int xor_value)
{
    reg_rf_crc_xorout = xor_value;
}

/**
 * @brief       This function serves to set the CRC output byte order for RF.
 * @param[in]   order - CRC output byte order (1:MSByte first,0:LSByte first)
 * @return      none.
 */
static inline void rf_set_crc_byte_order(unsigned char order)
{
    reg_rf_crc_config2 = (reg_rf_crc_config2 & 0xf7) | (order << 3);
}

/**
 * @brief       This function serves to set crc for RF.
 * @param[in]   config - crc config address pointer
 * @return      none.
 */
static inline void rf_set_crc_config(const rf_crc_config_t *config)
{
    rf_set_crc_init_value(config->init_value);
    rf_set_crc_poly(config->poly);
    rf_set_crc_xor_out(config->xor_out);
    rf_set_crc_byte_order(config->byte_order);
    rf_set_crc_start_cal_byte_pos(config->start_cal_pos);
    rf_set_crc_len(config->len);
}

/**
 * @brief   This function serve to get tx wptr.
 * @param[in]   pipe_id -   The number of tx fifo.0<= pipe_id <=5.
 * @return      The write pointer of the tx.
 */
static inline unsigned char rf_get_tx_wptr(unsigned char pipe_id)
{
    return reg_rf_dma_tx_wptr(pipe_id);
}

/**
 * @brief   This function serve to update the wptr of tx terminal.
 * @param[in]   pipe_id -   The number of pipe which need to update wptr.
 * @param[in]   wptr    -   The pointer of write in tx terminal.
 * @return      none
 */
static inline void rf_set_tx_wptr(unsigned char pipe_id, unsigned char wptr)
{
    reg_rf_dma_tx_wptr(pipe_id) = wptr;
}

/**
 * @brief   This function serve to clear the writer pointer of tx terminal.
 * @param[in]   pipe_id -   The number of tx DMA.0<= pipe_id <=5.
 * @return  none.
 */
static inline void rf_clr_tx_wptr(unsigned char pipe_id)
{
    reg_rf_dma_tx_wptr(pipe_id) = 0;
}

/**
 * @brief   This function serve to get ptx rptr.
 * @param[in]   pipe_id -The number of tx pipe.0<= pipe_id <=5.
 * @return      The read pointer of the tx.
 */
static inline unsigned char rf_get_tx_rptr(unsigned char pipe_id)
{
    return reg_rf_dma_tx_rptr(pipe_id);
}

/**
 * @brief   This function serve to clear read pointer of tx terminal.
 * @param[in]   pipe_id -   The number of tx DMA.0<= pipe_id <=5.
 * @return  none.
 */
static inline void rf_clr_tx_rptr(unsigned char pipe_id)
{
    reg_rf_dma_tx_rptr(pipe_id) = 0x80;
}

/**
 * @brief   This function serve to get the pointer of read in rx terminal.
 * @return  wptr    -   The pointer of rx_rptr.
 */
static inline unsigned char rf_get_rx_rptr(void)
{
    return reg_rf_dma_rx_rptr;
}

/**
 * @brief   This function serve to clear read pointer of rx terminal.
 * @return  none.
 */
static inline void rf_clr_rx_rptr(void)
{
    write_reg8(0x504258f5, 0x80); //clear rptr
}

/**
 * @brief   This function serve to get the pointer of write in rx terminal.
 * @return  wptr    -   The pointer of rx_wptr.
 */
static inline unsigned char rf_get_rx_wptr(void)
{
    return reg_rf_dma_rx_wptr;
}

/**
 * @brief     This function serves to set RF tx DMA setting.
 * @param[in] none
 * @return    none.
 */
void rf_set_tx_dma_config(void);

/**
 * @brief     This function serves to set RF tx DMA setting.
 * @param[in] fifo_depth        - tx chn deep,fifo_depth range: 0~5,Number of fifo=2^fifo_depth.
 * @param[in] fifo_byte_size    - The length of one dma fifo,the range is 1~0xffff(the corresponding number of fifo bytes is fifo_byte_size).
 * @return    none.
 */
void rf_set_tx_dma(unsigned char fifo_depth, unsigned short fifo_byte_size);

/**
 * @brief      This function serves to rx dma setting.
 * @param[in]  buff - This parameter is the first address of the received data buffer, which must be 4 bytes aligned, otherwise the program will enter an exception.
 * @attention  The first four bytes in the buffer of the received data are the length of the received data.
 *             The actual buffer size that the user needs to set needs to be noted on two points:
 *             -# you need to leave 4bytes of space for the length information.
 *             -# dma is transmitted in accordance with 4bytes, so the length of the buffer needs to be a multiple of 4. Otherwise, there may be an out-of-bounds problem
 *             For example, the actual received data length is 5bytes, the minimum value of the actual buffer size that the user needs to set is 12bytes, and the calculation of 12bytes is explained as follows::
 *             4bytes (length information) + 5bytes (data) + 3bytes (the number of additional bytes to prevent out-of-bounds)
 * @param[in]  wptr_mask       - This parameter is used to set the mask value for the number of enabled FIFOs. The value of the mask must (0x00,0x01,0x03,0x07,0x0f,0x1f).
 *                               The number of FIFOs enabled is the value of wptr_mask plus 1.(0x01,0x02,0x04,0x08,0x10,0x20)
 * @param[in]  fifo_byte_size  - The length of one dma fifo,the range is 1~0xffff(the corresponding number of fifo bytes is fifo_byte_size).
 * @return     none.
 */
void rf_set_rx_dma(unsigned char *buff, unsigned char wptr_mask, unsigned short fifo_byte_size);

/**
 * @brief       This function serve to rx dma config
 * @param[in]   none
 * @return      none
 */
void rf_set_rx_dma_config(void);

/**
 * @brief     This function serves to trigger srx on.
 * @param[in] tick  - Trigger rx receive packet after tick delay.
 * @return    none.
 */
void rf_start_srx(unsigned int tick);

/**
 * @brief       This function serves to get latched rssi.
 * @return      rssi value.
 */
signed char rf_get_latched_rssi(void);

/**
 * @brief       This function serves to set RF Tx mode.
 * @return      none.
 */
void rf_set_txmode(void);


/**
 * @brief       This function serves to set RF Tx packet address to DMA src_addr.
 * @param[in]   addr   - The packet address which to send.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 *              Hardware limitation: RF DMA can only access addresses within the MCU B core's DLM range (0x50080000 ~ 0x5009FFFF).
 *              Caller must ensure 'addr' falls within this range, otherwise a bus error or data corruption may occur.
 */
void rf_tx_pkt(void *addr);


/**
 * @brief       This function serves to set rf channel for all mode.The actual channel set by this function is 2400+chn.
 * @param[in]   chn   - That you want to set the channel as 2400+chn.
 * @return      none.
 */
 void rf_set_chn(signed char chn);

/**
 * @brief       This function serves to get the right fifo packet.
 * @param[in]   fifo_num   - The number of fifo set in dma.
 * @param[in]   fifo_dep   - deepth of each fifo set in dma.
 * @param[in]   addr       - address of rx packet.
 * @return      the next rx_packet address.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 */
unsigned char *rf_get_rx_packet_addr(int fifo_num, int fifo_dep, void *addr);


/**
 * @brief       This function serves to set RF power level.
 * @param[in]   level    - The power level to set.
 * @return      none.
 */
void rf_set_power_level(rf_power_level_e level);


/**
 * @brief       This function serves to set RF power through select the level index.
 * @param[in]   idx      - The index of power level which you want to set.
 * @return      none.
 */
void rf_set_power_level_index(rf_power_level_index_e idx);

/**
 * @brief       This function serves to get RF status.
 * @return      RF Rx/Tx status.
 */
rf_status_e rf_get_trx_state(void);

/**
 * @brief       This function serves to judge RF Tx/Rx state.
 * @param[in]   rf_status   - Tx/Rx status.
 * @param[in]   rf_channel  - This param serve to set frequency channel(2400+rf_channel) .
 * @return      Whether the setting is successful(-1:failed;else success).
 */
int rf_set_trx_state(rf_status_e rf_status, signed char rf_channel);

/**
 * @brief       This function serves to update the value of internal cap.
 * @param[in]   value   - The value of internal cap which you want to set.
 * @return      none.
 */
void rf_update_internal_cap(unsigned char value);

/**
 * @brief       This function serves to close internal cap;
 * @return      none.
 */
void rf_turn_off_internal_cap(void);

/**
 * @brief       This function serve to change the length of preamble.
 * @param[in]   len     -The value of preamble length.Set the register bit<0>~bit<4>.
 * @return      none
 */
void rf_set_preamble_len(unsigned char len);

/**
 * @brief       This function serve to set the length of access code.
 * @param[in]   byte_len    -   The value of access code length,the range is 3~5byte.
 * @return      none
 */
void rf_set_access_code_len(unsigned char byte_len);

/**
 * @brief       This function serves to set RF rx timeout.
 * @param[in]   timeout_us  -   rx_timeout after timeout_us us,The maximum of this param is 0xfff.
 * @return      none.
 */
static inline void rf_set_rx_timeout(unsigned short timeout_us)
{
    reg_rf_rx_timeout = timeout_us - 1;
}

/**
 * @brief   This function serves to disable RF rx timeout.
 * @return  none.
 */
static inline void rf_dis_rx_timeout(void)
{
    reg_rf_ll_ctrl_1 &= ~(FLD_RF_RX_TIMEOUT_EN);
}

/**
 * @brief       This function serves to RF trigger stx
 * @param[in]   addr    - DMA tx buffer.
 * @param[in]   tick    - Send after tick delay.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 *              Hardware limitation: RF DMA can only access addresses within the MCU B core's DLM range (0x50080000 ~ 0x5009FFFF).
 *              Caller must ensure 'addr' falls within this range, otherwise a bus error or data corruption may occur.
 */
 void rf_start_stx(void *addr, unsigned int tick);


/**
 * @brief       This function serves to RF trigger stx2rx.
 * @param[in]   addr  - DMA tx buffer.
 * @param[in]   tick  - Trigger tx send packet after tick delay.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 *              Hardware limitation: RF DMA can only access addresses within the MCU B core's DLM range (0x50080000 ~ 0x5009FFFF).
 *              Caller must ensure 'addr' falls within this range, otherwise a bus error or data corruption may occur.
 */
 void rf_start_stx2rx(void *addr, unsigned int tick);

/**
 * @brief       This function serves to set RF Rx manual on.
 * @return      none.
 */
 void rf_set_rxmode(void);

/**
 * @brief       This function serves to RF trigger srx2rx.
 * @param[in]   addr  - DMA tx buffer.
 * @param[in]   tick  - Trigger rx receive packet after tick delay.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 *              Hardware limitation: RF DMA can only access addresses within the MCU B core's DLM range (0x50080000 ~ 0x5009FFFF).
 *              Caller must ensure 'addr' falls within this range, otherwise a bus error or data corruption may occur.
 */
 void rf_start_srx2tx(void *addr, unsigned int tick);

/**
 * @brief       This function is used to judge whether there is a CRC error in the received packet through hardware.
 *              For the same packet, the value of this bit is consistent with the CRC flag bit in the packet.
 * @param[in]   none.
 * @return      none.
 */
unsigned char rf_get_crc_err(void);

/**
 * @brief      This function serves to set the max length of rx packet.Use byte_len to limit what DMA
 *             moves out will not exceed the buffer size we define.And old chip do this through dma size.
 * @param[in]  byte_len  - The longest of rx packet.
 * @return     none.
 */
static _always_inline void rf_set_rx_maxlen(unsigned int byte_len)
{
    reg_rf_rxtmaxlen0 = byte_len & 0xff;
    reg_rf_rxtmaxlen1 = (byte_len >> 8) & 0xff;
}

/**
 * @brief       This function serves to disable pn of rf mode.
 * @return      none.
 */
void rf_pn_disable(void);

/**
 * @brief      This function serves to set the tx wait time during the rx2tx process
 * @param[in]  tx_wait_us  tx wait time,the unit is us.The max value of this param is 0xfff; The default wait time value is 10us.
 * @return     none.
 * @note       Attention:It is not necessary to call this function to adjust the wait time in the rx2tx process.
 */
static inline void rf_set_tx_wait_time(unsigned short tx_wait_us)
{
    if (tx_wait_us > 0x0fff) {
        tx_wait_us = 0x0fff;
    }
    reg_rf_ll_txwait = (reg_rf_ll_txwait & 0xf000) | (tx_wait_us - 1);
}

/**
 * @brief      This function serves to set the rx wait time during the tx2rx process
 * @param[in]  rx_wait_us  rx wait time,the unit is us.The max value of this param is 0xfff; The default wait time value is 10us.
 * @return     none.
 * @note       Attention:It is not necessary to call this function to adjust the wait time in the tx2rx process.
 */
static inline void rf_set_rx_wait_time(unsigned short rx_wait_us)
{
    if (rx_wait_us > 0x0fff) {
        rx_wait_us = 0x0fff;
    }
    reg_rf_ll_rxwait = (reg_rf_ll_rxwait & 0xf000) | (rx_wait_us - 1);
}

/**
 * @brief       This function serve to set the length of access code.
 * @param[in]   bit_len -   The value of access code match threshold ,the range is 0~40bit.
 * @return      none
 */
void rf_set_acc_match_threshold(unsigned char bit_len);

/**
 * @brief      This function serves to reset RF digital logic states.
 * @return     none
 * @note       This function requires setting reset zb, rstl_bb, and rst_mdm.
 *             It is used to clear RF related state machines, IRQ states, and digital internal logic states.
 */
_attribute_ram_code_sec_noinline_ void rf_clr_dig_logic_state(void);

/**
 * @brief      This function is used to restore the rf related registers to their default values.
 * @return     none
 * @note       (1)After calling this interface, all configured interfaces of rf need to be called again.
 *             (2)After calling this interface, the tick of bb timer will be reset to zero.
 *             (3)After calling this interface, RF DMA configurations need to be reconfigured.
 */
_attribute_ram_code_sec_noinline_ void rf_reset_register_value(void);

/**
 * @brief          This function is mainly used to set the energy when sending a single carrier.
 * @param[in]    level        - The slice corresponding to the energy value.
 * @return         none.
 */
void rf_set_power_level_singletone(rf_power_level_e level);

/**
 * @brief      This interface is used to configure the BLE debug port IO.
 * @return     none.
 * @note       This function is only used for BLE mode debugging and testing.
 *              PA1  - ble_tx_en
 *              PA2  - ble_tx_on
 *              PA3  - ble_rx_en
 *              PA5  - ble_rx_hit_sync
 *              PA8  - ble_rx_data_vld
 */
void rf_set_ble_bb_debugport(void);

/**
 * @brief      This function is used to enable RF clock domain
 * @return     none.
 * @note       The RF clock domain must be enabled prior to invoking any RF-related functionality.
 */
void rf_clock_domain_enable(void);

/**
 * @brief      This function is used for RF submodule initialization
 * @return     none.
 * @note       (1)This function needs to be called before using RF related functions.
 *             (2)This function configures the RF working mode and modem clock.
 *             (3)The RF_TAHDT_MODE only supports a 48 MHz configuration for the rf_modem_clk.
 *             (4)The default configuration sets the RF modulation to IQ modulation.
 */
void rf_subsys_init(rf_mode_init_e rf_mode,rf_modem_clk_e rf_modem_clk);

/**
 * @brief      This function is used to check whether RF is in TP modulation mode.
 * @return     1: TP mode; 0: IQ mode.
 */
unsigned char rf_check_tp_mode(void);

/**
 * @brief      This function is used to get the real-time RSSI value from RF register.
 * @return     real-time RSSI value.
 */
signed char rf_get_real_time_rssi(void);


// Initialization and Configuration Function Declaration
void one_time_setup(void);
void aura_1m(void);
void aura_1m_hs(void);
void aura_2m(void);
void aura_2m_hs(void);
void aura_s2_old(void);
void aura_s2_old_hs(void);
void aura_s8_old(void);
void aura_s8_old_hs(void);
void aura_4m_hs(void);
void ble4m_setup(void);
void rx_cont_mode(void);
void ble1m_setup(void);
void ble2m_setup(void);
void blr125k_setup(void);
void blr500k_setup(void);
void pri1m_setup(void);
void pri2m_setup(void);
void aura_p500k(void);
void aura_p500k_hs(void);
void p500k_setup(void);
void aura_p250k(void);
void aura_p250k_hs(void);
void p250k_setup(void);
void agc_table_1m(void);
void agc_table_2m(void);

// DMA configuration function declaration
// void rx_dma(unsigned int rx_size,unsigned int rx_wptr_mask);
void rx_dma(unsigned char *buff,unsigned int rx_size,unsigned int rx_wptr_mask);
void tx_dma(unsigned char *buff,unsigned int tx_size,unsigned int tx_depth);

#endif

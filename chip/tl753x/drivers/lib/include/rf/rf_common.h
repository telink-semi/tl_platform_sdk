/********************************************************************************************************
 * @file    rf_common.h
 *
 * @brief   This is the header file for tl753x
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef RF_COMMON_H
#define RF_COMMON_H

#include "lib/include/sys.h"
#include "lib/include/rf/rf_dma.h"
#include "lib/include/rf/rf_ble.h"
#if 0  //TODO :Will be developed in future versions; not available in this release.
#include "lib/include/rf/rf_private.h"
#include "lib/include/rf/rf_zigbee.h"
#include "lib/include/rf/rf_sle.h"
#else
#include "reg_include/rf_spl_reg.h"
#include <string.h>
#endif
#include "gpio.h"
#include "lib/include/stimer.h"

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

/**********************************************************************************************************************
 *                                       RF global data type                                                          *
 *********************************************************************************************************************/

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
 *  @brief  RF slice scale config.
 */

typedef struct {
    unsigned char slice;
    unsigned char scale;
} rf_power_level_slice_scale_t;

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
 *           (2)Transmit energy in VBAT mode decreases as the supply voltage drops.
 *           (3)There will be some differences in the energy values tested between different chips.
 */
typedef enum
{
    RF_POWER_N4p92dBm  = 13, /**< -4.92 dBm */
    RF_POWER_N4p36dBm  = 14, /**< -4.36 dBm */
    RF_POWER_N2p80dBm  = 17, /**< -2.80 dBm */
    RF_POWER_N2p00dBm  = 19, /**< -2.00 dBm */
    RF_POWER_N1p22dBm  = 21, /**< -1.22 dBm */
    RF_POWER_P0p08dBm  = 25, /**< +0.08 dBm */
    RF_POWER_P0p91dBm  = 28, /**< +0.91 dBm */
    RF_POWER_P2p03dBm  = 33, /**< +2.03 dBm */
    RF_POWER_P3p03dBm  = 38, /**< +3.03 dBm */
    RF_POWER_P4p13dBm  = 45, /**< +4.13 dBm */
    RF_POWER_P5p00dBm  = 52, /**< +5.00 dBm */
    RF_POWER_P6p05dBm  = 31, /**< +6.05 dBm */
    RF_POWER_P6p97dBm  = 35, /**< +7.00 dBm */
    RF_POWER_P8p03dBm  = 40, /**< +8.03 dBm */
    RF_POWER_P9p10dBm  = 46, /**< +9.10 dBm */
    RF_POWER_P10p00dBm = 52, /**< +10.00 dBm */
} rf_power_level_e;

/**
 *  @brief   Define power list of RF.
 *  @note    (1)The energy meter is averaged over 3 chips at room temperature and 3.3V supply voltage..
 *           (2)Transmit energy in VBAT mode decreases as the supply voltage drops.
 *           (3)There will be some differences in the energy values tested between different chips.
 */
typedef enum
{
    RF_POWER_INDEX_N4p92dBm,  /**< -4.92 dBm */
    RF_POWER_INDEX_N4p36dBm,  /**< -4.36 dBm */
    RF_POWER_INDEX_N2p80dBm,  /**< -2.80 dBm */
    RF_POWER_INDEX_N2p00dBm,  /**< -2.00 dBm */
    RF_POWER_INDEX_N1p22dBm,  /**< -1.22 dBm */
    RF_POWER_INDEX_P0p08dBm,  /**< +0.08 dBm */
    RF_POWER_INDEX_P0p91dBm,  /**< +0.91 dBm */
    RF_POWER_INDEX_P2p03dBm,  /**< +2.03 dBm */
    RF_POWER_INDEX_P3p03dBm,  /**< +3.03 dBm */
    RF_POWER_INDEX_P4p13dBm,  /**< +4.13 dBm */
    RF_POWER_INDEX_P5p00dBm,  /**< +5.00 dBm */
    RF_POWER_INDEX_P6p05dBm,  /**< +6.05 dBm */
    RF_POWER_INDEX_P6p97dBm,  /**< +7.00 dBm */
    RF_POWER_INDEX_P8p03dBm,  /**< +8.03 dBm */
    RF_POWER_INDEX_P9p10dBm,  /**< +9.10 dBm */
    RF_POWER_INDEX_P10p00dBm, /**< +10.00 dBm */  
} rf_power_level_index_e;

/**
 *  @brief   Define power list of RF.
 */
typedef enum
{
    RF_POWER_SLICE_SCALE_INDEX_15  = 15, /**< slice=57, scale=28, 10dBm */
    RF_POWER_SLICE_SCALE_INDEX_14  = 14, /**< slice=49, scale=24,  9dBm */
    RF_POWER_SLICE_SCALE_INDEX_13  = 13, /**< slice=49, scale=20,  8dBm */
    RF_POWER_SLICE_SCALE_INDEX_12  = 12, /**< slice=41, scale=19,  7dBm */
    RF_POWER_SLICE_SCALE_INDEX_11  = 11, /**< slice=41, scale=17,  6dBm */
    RF_POWER_SLICE_SCALE_INDEX_10  = 10, /**< slice=41, scale=15,  5dBm */
    RF_POWER_SLICE_SCALE_INDEX_9   = 9,  /**< slice=33, scale=15,  4dBm */
    RF_POWER_SLICE_SCALE_INDEX_8   = 8,  /**< slice=33, scale=13,  3dBm */
    RF_POWER_SLICE_SCALE_INDEX_7   = 7,  /**< slice=25, scale=15,  2dBm */
    RF_POWER_SLICE_SCALE_INDEX_6   = 6,  /**< slice=15, scale=27,  1dBm */
    RF_POWER_SLICE_SCALE_INDEX_5   = 5,  /**< slice=15, scale=24,  0dBm */
    RF_POWER_SLICE_SCALE_INDEX_4   = 4,  /**< slice=15, scale=21, -1dBm */
    RF_POWER_SLICE_SCALE_INDEX_3   = 3,  /**< slice=15, scale=18, -2dBm */
    RF_POWER_SLICE_SCALE_INDEX_2   = 2,  /**< slice=15, scale=16, -3dBm */
    RF_POWER_SLICE_SCALE_INDEX_1   = 1,  /**< slice=15, scale=14, -4dBm */
    RF_POWER_SLICE_SCALE_INDEX_MIN = 0,  /**< slice=15, scale=12, -5dBm */
} rf_power_slice_scale_index_e;

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
    RF_MODE_BLE_4M_NO_PN,             /**< ble 4M close pn mode */

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
 * @brief define different RF radio modes.
 */
typedef enum
{
    RF_RADIO_MODE_BLE = 1,
    RF_RADIO_MODE_BT  = 2,
    RF_RADIO_MODE_BLE_HDT  = 3,
    RF_RADIO_MODE_SLE  = 4,
} rf_radio_mode_e;

/**********************************************************************************************************************
 *                                         RF global constants                                                        *
 *********************************************************************************************************************/
extern const rf_power_level_e rf_power_Level_list[65];
extern rf_mode_e              g_rfmode;
extern rf_crc_config_t        rf_crc_config[3];

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
    //if the value of [2:0] of the reg_0xd4170040 isn't 0 , it means that the RF is in the receiving packet phase.(confirmed by junwen).
    return ((read_reg8(0xd4170040) & 0x07) > 1);
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
    BM_SET(reg_rf_ll_irq_mask_h1, (mask & 0x7f000000) >> 24);
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
    BM_CLR(reg_rf_ll_irq_mask_h1, (mask & 0x7f000000) >> 24);
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
    reg_rf_irq_status_h1 = (status & 0x7f000000) >> 24;
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
    write_reg8(0xd4170425, read_reg8(0xd4170425) | 0x01);
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
    write_reg8(0xd4170215, ((read_reg8(0xd4170215) & 0xf8) | pipe) | BIT(4)); //Tx_Channel_man[2:0]
}

/**
 * @brief     This function serves to reset RF Tx/Rx mode.
 * @return    none.
 */
static _always_inline void rf_set_tx_rx_off(void)
{
    write_reg8(0xd4170216, 0x29);
    write_reg8(0xd4170028, 0x80); // rx disable
    write_reg8(0xd4170202, 0x45); // reset tx/rx state machine
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
 */
static inline void rf_set_rx_buffer(unsigned char *rx_addr)
{
    rx_addr += 4;
    rf_dma_set_dst_address(RF_RX_DMA, (unsigned int)(rx_addr));
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
    write_reg16(0xd4170204, (read_reg16(0xd4170204) & 0xf000) | (tx_stl_us - 1));
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
    write_reg16(0xd417020c, (read_reg16(0xd417020c) & 0xf000) | (rx_stl_us - 1));
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
    write_reg8(0xd41708f5, 0x80); //clear rptr
}

/**
 * @brief   This function serve to get the pointer of write in rx terminal.
 * @return  wptr    -   The pointer of rx_wptr.
 */
static inline unsigned char rf_get_rx_wptr(void)
{
    return reg_rf_dma_rx_wptr;
}

void rf_adc_48m_en(void);

void rf_adc_48m_dis(void);

void rf_tp_mode_en(void);

void rf_tp_mode_dis(void);

/**
 * @brief      This function is used to enable the RF PA VBUCK ANA power supply mode.
 * @return     none.
 * @note       (1)This function needs to be called before using RF related functions.
 */        
void rf_vbuck_mode_en(void);

/**
 * @brief      This function is used to disable the RF PA VBUCK ANA power supply mode.
 * @return     none.
 * @note       (1)This function needs to be called before using RF related functions.
 *             (2)After calling this function, the transmission power of RF will be increased, and the current consumption will also be increased. It is recommended to call this function in scenarios where high transmission power is required, such as long-distance transmission.
 */
void rf_vbuck_mode_dis(void);

 /**
 * @brief      This function is used to enable RF clock domain
 * @return     none.
 * @note       The RF clock domain must be enabled prior to invoking any RF-related functionality.
 */
void rf_clock_domain_enable(void);

/**
 * @brief    This function is used to initialize the baseband related digital modules for n22
 * @return   none.
 * @note     Attention:
 *           (1)This interface should be called before rf_mode_init.
 *           (2)This interface should be called after sys_n22_init.
 */
void rf_n22_dig_init(void);

/**
 * @brief       This function is used to set the MODEM side to high-performance mode for rx.
 * @param[in]   hp_en - hp mode enable. 1  hp mode enable;0 hp mode disable(aura path);
 * @return      none.
 * @note        Attention:
 *              (1)Must be called before rf mode initialization(e.g. before rf_set_ble_1M_mode)
 *              (2)Zigbee related modes cannot use high-performance mode
 */
void rf_modem_hp_path(unsigned char hp_en);

/**
 * @brief      This function serves to initiate information of RF.
 * @return     none.
 */
void rf_mode_init(void);

/**
 * @brief   Switch between different RF radio modes.
 * @param   radio_mode  Target radio mode.
 */
void rf_change_radio_mode(rf_radio_mode_e radio_mode);

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
 * @brief       This function serves to get the real time rssi.
 * @return      rssi value.
 */
signed char rf_get_real_time_rssi(void);

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
 */
_attribute_ram_code_sec_ void rf_tx_pkt(void *addr);


/**
 * @brief       This function serves to set rf channel for all mode.The actual channel set by this function is 2400+chn.
 * @param[in]   chn   - That you want to set the channel as 2400+chn.
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void rf_set_chn(signed char chn);

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
 */
_attribute_ram_code_sec_noinline_ void rf_start_stx(void *addr, unsigned int tick);


/**
 * @brief       This function serves to RF trigger stx2rx.
 * @param[in]   addr  - DMA tx buffer.
 * @param[in]   tick  - Trigger tx send packet after tick delay.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 */
_attribute_ram_code_sec_noinline_ void rf_start_stx2rx(void *addr, unsigned int tick);

/**
 * @brief       This function serves to set RF Rx manual on.
 * @return      none.
 */
_attribute_ram_code_sec_noinline_ void rf_set_rxmode(void);

/**
 * @brief       This function serves to RF trigger srx2rx.
 * @param[in]   addr  - DMA tx buffer.
 * @param[in]   tick  - Trigger rx receive packet after tick delay.
 * @return      none.
 * @note        addr:must be aligned by word (4 bytes), otherwise the program will enter an exception.
 */
_attribute_ram_code_sec_noinline_ void rf_start_srx2tx(void *addr, unsigned int tick);

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
 * @brief       This function serves to set RF power level slice and scale.
 * @param[in]   level    - The power level to set.
 * @return      none.
 */
void rf_set_power_slice_scale(rf_power_slice_scale_index_e index);
/**
 * @brief          This function is mainly used to set rf channel on FPGA.
 * @param[in]      chn        - The channel you want to set and the real frequency equal to (2402 + chn)MHz.
 * @return         none.
 */
void rf_set_chn_fpga(unsigned char chn);


void rf_enable_bb_debug(rf_radio_mode_e radio_mode);

#endif

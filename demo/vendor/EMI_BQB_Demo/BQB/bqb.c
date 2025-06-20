/********************************************************************************************************
 * @file    bqb.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "bqb.h"

#if (TEST_DEMO == BQB_DEMO)

    /* Set to 1, the program includes a non-standard BQB protocol part, which adds new functions for factory testing (single tone, rssi, sending fixed packets)*/
    #define BQB_PRIVATE_AGREEMENT 0

    /*
 * @brief This macro is defined to turn on the fastsettle function
 * */
    #define RF_FAST_SETTLE 0

    #if SUPPORT_CONFIGURATION
usr_def_t usr_config;
    #endif
uart_num_redef_e uart_using = UART_NONE;

static unsigned short pkt_cnt = 0, cmd_pkt, l, h;
static unsigned char  chn, pkt_type, freq, uart_tx_index, uart_rx_index, para, ctrl;
static unsigned char  bb_mode = 1;
static unsigned int   pkt_interval;
static unsigned int   tick_rx = 0;
volatile unsigned int t0, tick_tx;
Test_Status_e         test_state;
#if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
extern _attribute_data_retention_sec_ rf_fast_settle_t *g_fast_settle_cal_val_ptr;

_attribute_data_retention_sec_ rf_fast_settle_t fs_cv_1m;
_attribute_data_retention_sec_ rf_fast_settle_t fs_cv_2m;
_attribute_data_retention_sec_ rf_fast_settle_t fs_cv_s2;
_attribute_data_retention_sec_ rf_fast_settle_t fs_cv_s8;

void rf_fast_settle_get_val(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us, rf_fast_settle_t *fs_cv);
void rf_fast_settle_set_val(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us, rf_fast_settle_t *fs_cv);
#endif

    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL751X)|| defined(MCU_CORE_TL322X)
    #else
static unsigned char rxpara_flag = 1;
    #endif

unsigned char                             bqbtest_buffer[272] __attribute__((aligned(4)));
unsigned char __attribute__((aligned(4))) bqbtest_pkt[264] = {
    37,
    0,
    0,
    0,
    0,
    37,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7};

static union pkt_length_u
{
    unsigned char len;

    struct len_t
    {
        unsigned char low   : 6;
        unsigned char upper : 2;
    } l;
} pkt_length;

    #if BQB_PRIVATE_AGREEMENT
unsigned char private_agreement_rssi = 0;

static union private_status_u
{
    unsigned int u32Status;

    struct
    {
        unsigned int parameter : 16;
        unsigned int           : 6;
        unsigned int test_mode : 1;
        unsigned int test_flag : 1;
    } tStatus;
} uPrivateStatus;

typedef enum
{
    PRIVATE_TX_CARRIER_MODE = 0x00,
    PRIVATE_TX_BURST_MODE   = 0x01,
} private_status_e;
    #endif

#if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
void fs_get_value(void)
{
    #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    rf_set_ble_500K_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_s2);

    rf_set_ble_125K_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_s8);

    rf_set_ble_1M_NO_PN_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_1m);

    rf_set_ble_2M_NO_PN_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_2m);
    #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    rf_set_ble_500K_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_s2);

    rf_set_ble_125K_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_s8);

    rf_set_ble_1M_NO_PN_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_1m);

    rf_set_ble_2M_NO_PN_mode();
    rf_fast_settle_get_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_2m);
    #endif
}

/**
 *  @brief      This function is used to initialize the calibration value of rf tx/rx fast settle
 *  @param[in]  tx_settle_us    After adjusting the timing sequence, the time required for tx to settle.
 *  @param[in]  rx_settle_us    After adjusting the timing sequence, the time required for rx to settle.
 *  @return     none
 */
void rf_fast_settle_setup(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us)
{
    //tx
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
    rf_set_tx_settle_time(113);        //adjust TX settle time

    for (unsigned char f_chn = 0; f_chn <= 80; f_chn++) {
        rf_set_chn(f_chn);
        rf_set_txmode();
        delay_us(113); //Wait for calibration to stabilize
        rf_tx_fast_settle_update_cal_val(tx_settle_us, f_chn);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
    rf_set_tx_settle_time(113);        //adjust TX settle time

    for (unsigned char f_chn = 4; f_chn <= 80; f_chn+=10) {
        rf_set_chn(f_chn);
        rf_set_txmode();
        delay_us(113); //Wait for calibration to stabilize
        rf_tx_fast_settle_update_cal_val(tx_settle_us, f_chn);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#endif
    //rx
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    rf_set_rx_settle_time(85); //adjust RX settle time
    rf_set_rxmode();
    delay_us(85); //Wait for the rx packetization action to complete
    rf_rx_fast_settle_update_cal_val(rx_settle_us, 0);
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
#elif defined(MCU_CORE_TL721X)
    rf_set_rx_settle_time(85); //adjust RX settle time
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_set_chn(f_chn);
        rf_set_rxmode();
        delay_us(85); //Wait for the rx packetization action to complete
        rf_rx_fast_settle_update_cal_val(rx_settle_us, f_chn);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#elif defined(MCU_CORE_TL321X)
    rf_set_rx_settle_time(93); //adjust RX settle time
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_set_chn(f_chn);
        rf_set_rxmode();
        delay_us(93); //Wait for the rx packetization action to complete
        rf_rx_fast_settle_update_cal_val(rx_settle_us, f_chn);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#endif
}
#endif

/**
 * @brief   This function serves to get ble channel index
 * @param   chn: input channel
 * @return  ble channel index
 */
unsigned char bqbtest_channel(unsigned char channel)
{
    if (channel == 0) {
        return 37;
    } else if (channel < 12) {
        return channel - 1;
    } else if (channel == 12) {
        return 38;
    } else if (channel < 39) {
        return channel - 2;
    } else {
        return 39;
    }
}

/**
 * @brief   This function serves to obtain the pkt interval in different payload lengths and different modes
 * @param   payload_len: payload length
 * @param   mode: tx mode
 *              1:BLE1M
 *              2:BLE2M
 *              3:BLE125K
 *              4:BLE500K
 * @return  the pkt interval
 */
unsigned int get_pkt_interval(unsigned char payload_len, unsigned char mode)
{
    unsigned int  total_len, byte_time = 8;
    unsigned char preamble_len;
    unsigned int  total_time;

    if (mode == 1)                                                                       //1m
    {
        preamble_len = reg_rf_preamble_trail & 0x1f;
        total_len    = preamble_len + 4 + 2 + payload_len + 3;                           // preamble + access_code + header + payload + crc
        byte_time    = 8;
        return (((byte_time * total_len + 249 + 624) / 625) * 625);
    } else if (mode == 2)                                                                //2m
    {
        preamble_len = reg_rf_preamble_trail & 0x1f;
        total_len    = preamble_len + 4 + 2 + payload_len + 3;                           // preamble + access_code + header + payload + crc
        byte_time    = 4;
        return (((byte_time * total_len + 249 + 624) / 625) * 625);
    } else if (mode == 4)                                                                // s=2
    {
        byte_time  = 2;                                                                  //2us/bit
        total_time = (80 + 256 + 16 + 24) + (16 + payload_len * 8 + 24 + 3) * byte_time; // preamble + access_code + coding indicator + TERM1 + header + payload + crc + TERM2
        return (((total_time + 249 + 624) / 625) * 625);
    } else if (mode == 3)                                                                //s=8
    {
        byte_time  = 8;                                                                  //8us/bit
        total_time = (80 + 256 + 16 + 24) + (16 + payload_len * 8 + 24 + 3) * byte_time; // preamble + access_code + coding indicator + TERM1 + header + payload + crc + TERM2
        return (((total_time + 249 + 624) / 625) * 625);
    }
    return 0;
}

/**
 * @brief   This function serves to read the uart data and execute BQB program
 * @param   Pointer to uart data
 * @return  1:  2 bytes data is received.
 *          0:  no data is received.
 */
unsigned short uart_bqbtest_get(unsigned short *cmd)
{
    if (!tick_rx && ((reg_uart_buf_cnt(uart_using) & FLD_UART_RX_BUF_CNT) == 1)) {
        tick_rx = stimer_get_tick();
    } else if ((reg_uart_buf_cnt(uart_using) & FLD_UART_RX_BUF_CNT) == 2) {
        h = reg_uart_data_buf(uart_using, uart_rx_index) & 0xff;
        uart_rx_index++;
        uart_rx_index &= 0x03;
        l = reg_uart_data_buf(uart_using, uart_rx_index) & 0xff;
        uart_rx_index++;
        uart_rx_index &= 0x03;

        *cmd = (l | (h << 8));

        tick_rx = 0;
        return 1;
    } else if (tick_rx && clock_time_exceed(tick_rx, 5000)) {
        tick_rx = 0;
        reg_uart_data_buf(uart_using, uart_rx_index);
        uart_rx_index++;
        uart_rx_index &= 0x03;
    } else if ((reg_uart_buf_cnt(uart_using) & FLD_UART_RX_BUF_CNT) > 2) {
        unsigned char i;

        unsigned char u = REG_ADDR8(0x9c) & 0x0f;
        for (i = 0; i < u; i++) {
            reg_uart_data_buf(uart_using, uart_rx_index);
            uart_rx_index++;
            uart_rx_index &= 0x03;
        }
    }
    return 0;
}

extern void read_bqb_calibration(void);

void bqb_serviceloop(void)
{
    if (uart_bqbtest_get(&cmd_pkt)) {
        unsigned short rsp = 0;
        unsigned char  cmd = cmd_pkt >> 14;
        unsigned char  k;
        unsigned int   transLen = 0;
        tick_tx                 = stimer_get_tick();
        switch (cmd) {
        case CMD_SETUP:
        {
            bqb_pa_set_mode(3);
            ctrl = (cmd_pkt >> 8) & 0x3f;
            para = (cmd_pkt >> 2) & 0x3f;
    #if BQB_PRIVATE_AGREEMENT
            if ((uPrivateStatus.tStatus.test_flag == 1) && (uPrivateStatus.tStatus.test_mode == PRIVATE_TX_CARRIER_MODE)) {
                rf_emi_stop();
            }

            uPrivateStatus.u32Status = 0;
            private_agreement_rssi   = 0;
    #endif
            if (ctrl == 0) {
                if (para == 0) {
                    pkt_length.l.upper = 0;
                    rsp                = 0;
                } else {
                    rsp = BIT(0); //Error
                }
                rf_set_tx_rx_off_auto_mode();
                rf_set_ble_1M_NO_PN_mode();
    #if (RF_FAST_SETTLE)
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
                rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_1m);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
                rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_1m);
        #endif
    #endif
                rf_access_code_comm(ACCESS_CODE);
                rf_pn_disable();
                bb_mode = 1;
            } else if (ctrl == 1) {
                if (para <= 3) {
                    pkt_length.l.upper = para & 0x03;
                } else {
                    rsp = BIT(0); //Error
                }
            } else if (ctrl == 2) {
                rf_set_tx_rx_off_auto_mode();
                if (para == 1) //BLE 1M
                {
                    rf_set_ble_1M_NO_PN_mode();
    #if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_1m);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_1m);
        #endif
    #endif
                    rsp = 0;
                } else if (para == 2) //BLE 2M
                {
                    rf_set_ble_2M_NO_PN_mode();
    #if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_2m);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_2m);
        #endif
    #endif
                    rsp = 0;
                } else if (para == 3) //s=8
                {
                    rf_set_ble_125K_mode();
    #if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_s8);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_s8);
        #endif
    #endif
                    rsp = 0;
                } else if (para == 4) //s=2
                {
                    rf_set_ble_500K_mode();
    #if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_s2);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
                    rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_s2);
        #endif
    #endif
                    rsp = 0;
                } else {
                    rsp = BIT(0);
                }
                rf_access_code_comm(ACCESS_CODE);
                rf_pn_disable();
                bb_mode = para;
            } else if (ctrl == 3) {
                rsp = 0;
            } else if (ctrl == 4) {
                rsp |= BIT(1) | BIT(2);
                rsp = (rsp << 1);
            } else if (ctrl == 5) {
                if (para == 0) {
                    rsp = (251 << 1) & 0x7ffe;
                } else if (para == 1) {
                    rsp = (17040 << 1) & 0x7ffe;
                } else if (para == 2) {
                    rsp = (251 << 1) & 0x7ffe;
                } else if (para == 3) {
                    rsp = (17040 << 1) & 0x7ffe;
                } else {
                    rsp = BIT(0); //status EVENT Error
                }
            }
    #if BQB_PRIVATE_AGREEMENT
            else if (ctrl == 0x30) //private test TX
            {
                uPrivateStatus.tStatus.test_flag = 1;
                uPrivateStatus.tStatus.test_mode = PRIVATE_TX_CARRIER_MODE;
                uPrivateStatus.tStatus.parameter = cmd_pkt & 0xff;
            } else if (ctrl == 0x31) {
                uPrivateStatus.tStatus.test_flag = 1;
                uPrivateStatus.tStatus.test_mode = PRIVATE_TX_BURST_MODE;
                uPrivateStatus.tStatus.parameter = ((cmd_pkt & 0xff) * 100) & 0xffff;
            }
    #endif
            else {
                rsp = BIT(0); //status EVENT Error
            }

            uart_send_byte((uart_num_e)uart_using, (rsp >> 8) & 0x7f);
            uart_send_byte((uart_num_e)uart_using, rsp & 0xff);
            test_state = SETUP_STATE;
            pkt_cnt    = 0;
            break;
        }
        case CMD_RX_TEST:
        {
            bqb_pa_set_mode(0);
            read_bqb_calibration();
            chn              = (cmd_pkt >> 8) & 0x3f; //frequency
            pkt_length.l.low = (cmd_pkt >> 2) & 0x3f;
            pkt_type         = cmd_pkt & 0x03;
            freq             = bqbtest_channel(chn);  //set channel
            rf_set_tx_rx_off_auto_mode();
            rf_set_ble_chn(freq);
            rf_set_rx_dma(bqbtest_buffer, 0, 272);
            rf_start_srx(rf_stimer_get_tick());
            delay_us(30);
    #if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)|| defined(MCU_CORE_TL751X)|| defined(MCU_CORE_TL322X)
    #else
            if (rxpara_flag == 1) {
                rf_set_rxpara();
                rxpara_flag = 0;
            }

            if (freq == 10 || freq == 21 || freq == 33) {
                rf_ldot_ldo_rxtxlf_bypass_en();
            } else {
                rf_ldot_ldo_rxtxlf_bypass_dis();
            }
    #endif
            uart_send_byte((uart_num_e)uart_using, (rsp >> 8) & 0xff);
            uart_send_byte((uart_num_e)uart_using, rsp & 0xff);
            test_state = RX_STATE;
            pkt_cnt    = 0;
            break;
        }
        case CMD_TX_TEST:
        {
            bqb_pa_set_mode(1);
            read_bqb_calibration();
            chn              = (cmd_pkt >> 8) & 0x3f; //frequency
            pkt_length.l.low = (cmd_pkt >> 2) & 0x3f;
            pkt_type         = cmd_pkt & 0x03;
            transLen         = pkt_length.len + 2;
            transLen         = rf_tx_packet_dma_len(transLen);
            bqbtest_pkt[3]   = (transLen >> 24) & 0xff;
            bqbtest_pkt[2]   = (transLen >> 16) & 0xff;
            bqbtest_pkt[1]   = (transLen >> 8) & 0xff;
            bqbtest_pkt[0]   = transLen & 0xff;
            bqbtest_pkt[5]   = pkt_length.len;
            if (pkt_type == 0) {
                rf_phy_test_prbs9(bqbtest_pkt + 6, pkt_length.len);
            } else if (pkt_type == 1) {
                for (k = 0; k < (pkt_length.len); k++) {
                    bqbtest_pkt[k + 6] = 0x0f;
                }


            } else if (pkt_type == 2) {
                for (k = 0; k < (pkt_length.len); k++) {
                    bqbtest_pkt[k + 6] = 0x55;
                }

            } else if (pkt_type == 3) {
                pkt_type = 4;

                //todo if not LE Coded
                for (k = 0; k < (pkt_length.len); k++) {
                    bqbtest_pkt[k + 6] = 0xff;
                }
            } else {
                rsp = BIT(0);
            }
            bqbtest_pkt[4] = pkt_type;
            pkt_interval   = get_pkt_interval(pkt_length.len, bb_mode); //TODO
            freq           = bqbtest_channel(chn);                      //set channel
            rf_set_tx_rx_off_auto_mode();
    #if BQB_PRIVATE_AGREEMENT
            if ((uPrivateStatus.tStatus.test_flag == 1) && (uPrivateStatus.tStatus.test_mode == PRIVATE_TX_CARRIER_MODE)) {
                extern unsigned char g_single_tong_freqoffset;
                g_single_tong_freqoffset = 1;
                rf_set_zigbee_250K_mode();
                rf_set_ble_chn(freq);
                rf_set_power_level_singletone(rf_power_Level_list[uPrivateStatus.tStatus.parameter]);
                rf_set_txmode();
                g_single_tong_freqoffset = 0;
            } else {
                rf_set_ble_chn(freq);
        #if SUPPORT_CONFIGURATION
                rf_set_power_level((usr_config.power == 0) ? BQB_TX_POWER : rf_power_Level_list[usr_config.power - 1]);
        #else
                rf_set_power_level(BQB_TX_POWER);
        #endif
                //                  dma_chn_dis(DMA0);
                rf_set_tx_dma(2, 8);
            }
    #else
            rf_set_ble_chn(freq);
        #if SUPPORT_CONFIGURATION
            rf_set_power_level((usr_config.power == 0) ? BQB_TX_POWER : rf_power_Level_list[usr_config.power - 1]);
        #else
            rf_set_power_level(BQB_TX_POWER);
        #endif
            dma_chn_dis(DMA0);
            rf_set_tx_dma(2, 8);
    #endif
            uart_send_byte((uart_num_e)uart_using, (rsp >> 8) & 0xff);
            uart_send_byte((uart_num_e)uart_using, rsp & 0xff);
            test_state = TX_STATE;
            pkt_cnt    = 0;
            break;
        }
        case CMD_END:
        {
            bqb_pa_set_mode(3);
            ctrl = (cmd_pkt >> 8) & 0x3f;
            para = (cmd_pkt >> 2) & 0x3f;

    #if (!RETURN_TX_LEN_EN)
            if (test_state == TX_STATE) { //The tx quantity does not need to be reported
                pkt_cnt = 0;
            }
    #endif
            if ((ctrl == 0) && (para == 0)) {
                pkt_length.len = 0;
                uart_send_byte((uart_num_e)uart_using, (BIT(7)) | ((pkt_cnt >> 8) & 0x7f));
                uart_send_byte((uart_num_e)uart_using, pkt_cnt & 0xff);
            }
    #if BQB_PRIVATE_AGREEMENT
            else if ((ctrl == 0x33) && ((cmd_pkt & 0xff) == 1)) {
                uart_send_byte((uart_num_e)uart_using, BIT(7));
                uart_send_byte((uart_num_e)uart_using, private_agreement_rssi & 0xff);
            }


            if (uPrivateStatus.tStatus.test_flag == 1) {
                if (uPrivateStatus.tStatus.test_mode == PRIVATE_TX_CARRIER_MODE) {
                    rf_emi_stop();
                }
                uPrivateStatus.u32Status = 0;
            }
    #endif
            test_state = END_STATE;
            break;
        }
        default:
            break;
        }
    }
    if (test_state == RX_STATE) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            if ((reg_rf_dec_err & 0xf0) == 0) {
    #if BQB_PRIVATE_AGREEMENT
                unsigned short rssi_tmp = 0;
                rssi_tmp += private_agreement_rssi;
                if (rssi_tmp != 0) {
                    rssi_tmp += bqbtest_buffer[rf_ble_dma_rx_offset_rssi(bqbtest_buffer)];
                    private_agreement_rssi = rssi_tmp >> 1;
                } else {
                    private_agreement_rssi = bqbtest_buffer[rf_ble_dma_rx_offset_rssi(bqbtest_buffer)];
                }
    #endif
                pkt_cnt++;
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
            rf_set_tx_rx_off_auto_mode();
            rf_start_srx(rf_stimer_get_tick());
        }
    } else if (test_state == TX_STATE) {
    #if BQB_PRIVATE_AGREEMENT
        if (uPrivateStatus.tStatus.test_flag == 1) {
            if ((uPrivateStatus.tStatus.test_mode == PRIVATE_TX_BURST_MODE) && (uPrivateStatus.tStatus.parameter != 0)) {
                if (clock_time_exceed(tick_tx, pkt_interval) || (pkt_cnt == 0)) //pkt_interval
                {
                    pkt_cnt++;
                    tick_tx = stimer_get_tick();
                    rf_set_tx_rx_off_auto_mode();
                    if (pkt_cnt <= uPrivateStatus.tStatus.parameter) {
                        rf_start_stx(bqbtest_pkt, rf_stimer_get_tick());
                    }
                }
            }
        } else {
            if (clock_time_exceed(tick_tx, pkt_interval) || (pkt_cnt == 0)) //pkt_interval
            {
                tick_tx = stimer_get_tick();
                rf_set_tx_rx_off_auto_mode();
                rf_start_stx(bqbtest_pkt, rf_stimer_get_tick());
                pkt_cnt++;
            }
        }
    #else
        if (clock_time_exceed(tick_tx, pkt_interval) || (pkt_cnt == 0)) //pkt_interval
        {
            tick_tx = stimer_get_tick();
            rf_set_tx_rx_off_auto_mode();
            rf_start_stx(bqbtest_pkt, rf_stimer_get_tick());
            pkt_cnt++;
        }
    #endif
    }
}

/**
 * @brief       This function serves to initialize  BQB
 * @param[in]   flash_size - flash size: 0->512K, 1->2M, 2-0xff->1M.
 * @return      none.
 */
void bqbtest_init()
{
    t0 = stimer_get_tick();
    rf_mode_init();
    rf_set_ble_1M_NO_PN_mode();
    rf_phy_test_prbs9(bqbtest_pkt + 6, 37);
    reg_rf_ll_ctrl_1 &= ~FLD_RF_RX_FIRST_TIMEOUT_EN; //disable first timeout

        #if SUPPORT_CONFIGURATION
    rf_set_power_level((usr_config.power == 0) ? BQB_TX_POWER : rf_power_Level_list[usr_config.power - 1]);
        #else
    rf_set_power_level(BQB_TX_POWER);
        #endif
        #if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)

    #if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
            #if 0
    rf_fast_settle_setup(TX_SETTLE_TIME_50US,RX_SETTLE_TIME_45US);
            #else
    fs_get_value();
    rf_fast_settle_set_val(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US, &fs_cv_1m);
            #endif
    rf_fast_settle_config(TX_SETTLE_TIME_50US, RX_SETTLE_TIME_45US);

    rf_tx_fast_settle_en();
    rf_rx_fast_settle_en();

    rf_set_tx_settle_time(50);
    rf_set_rx_settle_time(45);

    rf_set_chn(freq);
        #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)

            #if 0
    rf_fast_settle_setup(TX_SETTLE_TIME_23US,RX_SETTLE_TIME_15US);
            #else
    fs_get_value();
    rf_fast_settle_set_val(TX_SETTLE_TIME_23US, RX_SETTLE_TIME_15US, &fs_cv_1m);
            #endif
    if (-1 == rf_fast_settle_config(TX_SETTLE_TIME_15US, RX_SETTLE_TIME_15US)) {
        //Incorrect configuration.
        gpio_toggle(LED2);
    }
    rf_tx_fast_settle_en();
    rf_rx_fast_settle_en();
    rf_set_tx_settle_time(23);
    rf_set_rx_settle_time(15);

    rf_set_chn(freq);
        #endif
    #endif
    rf_access_code_comm(ACCESS_CODE);
    rf_pn_disable();
    bb_mode       = 1;
    uart_tx_index = 0;
    uart_rx_index = 0;

    #if BQB_PRIVATE_AGREEMENT
    uPrivateStatus.u32Status = 0;
    #endif
}

void bqb_pa_init()
{
    unsigned short tx_pin, rx_pin;
    #if SUPPORT_CONFIGURATION
    tx_pin = get_pin(usr_config.pa_tx);
    rx_pin = get_pin(usr_config.pa_rx);
    #else
    tx_pin = BQB_PA_TX_PORT;
    rx_pin = BQB_PA_RX_PORT;
    #endif
    if (tx_pin == rx_pin) {
        return;
    }
    gpio_function_en(rx_pin);
    gpio_output_en(rx_pin);
    gpio_set_low_level(rx_pin);
    gpio_input_dis(rx_pin);
    gpio_function_en(tx_pin);
    gpio_output_en(tx_pin);
    gpio_input_dis(tx_pin);
    gpio_set_low_level(tx_pin);
}

void bqb_pa_set_mode(unsigned char rtx) //0:rx, 1:tx, other:off
{
    unsigned short tx_pin, rx_pin;
    #if SUPPORT_CONFIGURATION
    tx_pin = get_pin(usr_config.pa_tx);
    rx_pin = get_pin(usr_config.pa_rx);
    #else
    tx_pin = BQB_PA_TX_PORT;
    rx_pin = BQB_PA_RX_PORT;
    #endif
    if (tx_pin == rx_pin) {
        return;
    }
    if (rtx == 0) {
        gpio_set_high_level(rx_pin);
        gpio_set_low_level(tx_pin);
    } else if (rtx == 1) {
        gpio_set_low_level(rx_pin);
        gpio_set_high_level(tx_pin);
    } else {
        gpio_set_low_level(rx_pin);
        gpio_set_low_level(tx_pin);
    }
}
#if (RF_FAST_SETTLE)&&(!defined(MCU_CORE_TL751X))
/**
 *  @brief      This function is used to get the calibration value of rf tx/rx fast settle
 *  @param[in]  tx_settle_us    After adjusting the timing sequence, the time required for tx to settle.
 *  @param[in]  rx_settle_us    After adjusting the timing sequence, the time required for rx to settle.
 *  @param[in]  fs_cv           Fast settle related calibration value storage variable address.
 *  @return     none
 */
void rf_fast_settle_get_val(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us, rf_fast_settle_t *fs_cv)
{
    //tx
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_TL721X)
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
    rf_set_tx_settle_time(113);        //adjust TX settle time

    for (unsigned char f_chn = 0; f_chn <= 80; f_chn++) {
        rf_set_chn(f_chn);
        rf_set_txmode();
        delay_us(113); //Wait for calibration to stabilize
        rf_tx_fast_settle_get_cal_val(tx_settle_us, f_chn, fs_cv);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#elif defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X)
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
    rf_set_tx_settle_time(113);        //adjust TX settle time

    for (unsigned char f_chn = 4; f_chn <= 80; f_chn+=10) {
        rf_set_chn(f_chn);
        rf_set_txmode();
        delay_us(113); //Wait for calibration to stabilize
        rf_tx_fast_settle_get_cal_val(tx_settle_us, f_chn, fs_cv);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#endif

    //rx
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    rf_set_rx_settle_time(85); //adjust RX settle time
    rf_set_rxmode();
    delay_us(85); //Wait for the rx packetization action to complete
    rf_rx_fast_settle_get_cal_val(rx_settle_us, 0, fs_cv);
    rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
#elif defined(MCU_CORE_TL721X)
    rf_set_rx_settle_time(85); //adjust RX settle time
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_set_chn(f_chn);
        rf_set_rxmode();
        delay_us(85); //Wait for the rx packetization action to complete
        rf_rx_fast_settle_get_cal_val(rx_settle_us, f_chn, fs_cv);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#elif defined(MCU_CORE_TL321X)||defined(MCU_CORE_TL322X)
    rf_set_rx_settle_time(93); //adjust RX settle time
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_set_chn(f_chn);
        rf_set_rxmode();
        delay_us(93); //Wait for the rx packetization action to complete
        rf_rx_fast_settle_get_cal_val(rx_settle_us, f_chn, fs_cv);

        rf_set_tx_rx_off(); //STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#endif
}

/**
 *  @brief      This function is used to set the calibration value of rf tx/rx fast settle
 *  @param[in]  tx_settle_us    After adjusting the timing sequence, the time required for tx to settle.
 *  @param[in]  rx_settle_us    After adjusting the timing sequence, the time required for rx to settle.
 *  @param[in]  fs_cv           Fast settle related calibration value storage variable address.
 *  @return     none
 */
void rf_fast_settle_set_val(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us, rf_fast_settle_t *fs_cv)
{
    g_fast_settle_cal_val_ptr = fs_cv;
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
    rf_tx_fast_settle_set_cal_val(tx_settle_us, 0, fs_cv);
    rf_rx_fast_settle_set_cal_val(rx_settle_us, 0, fs_cv);
#elif defined(MCU_CORE_TL721X)
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_tx_fast_settle_set_cal_val(tx_settle_us, f_chn, fs_cv);
        rf_rx_fast_settle_set_cal_val(rx_settle_us, f_chn, fs_cv);
    }
#elif defined(MCU_CORE_TL321X)
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_tx_fast_settle_set_cal_val(tx_settle_us, f_chn, fs_cv);
        rf_rx_fast_settle_set_cal_val(rx_settle_us, f_chn, fs_cv);
    }
#elif defined(MCU_CORE_TL322X)
    for (unsigned char f_chn = 4; f_chn <= 80; f_chn += 10) {
        rf_tx_fast_settle_set_cal_val(tx_settle_us, f_chn, fs_cv);
        rf_rx_fast_settle_set_cal_val(rx_settle_us, f_chn, fs_cv);
    }
    rf_cali_linear_fit(fs_cv);
#endif
}
#endif

#endif

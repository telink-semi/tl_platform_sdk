/********************************************************************************************************
 * @file    app_ble_aes_ccm.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
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
#include "common.h"


#if defined(MCU_CORE_TL522X) && (RF_MODE == TEST_BLE_AES_CCM)

unsigned char sKey[16]
        __attribute__((aligned(4))) = { 0xd6, 0xbe, 0x89, 0x8e, 0xd6, 0xbe, 0x89, 0x8e, 0xd6, 0xbe, 0x89, 0x8e, 0xd6, 0xbe, 0x89, 0x8e };

unsigned char IV[8] __attribute__((aligned(4))) = {
    0xad, 0x7d, 0x13, 0x1d, 0x5a, 0xfb, 0x26, 0x3a,
};

unsigned char Txccmpktcnt[5] __attribute__((aligned(4))) = { 0xd6, 0xbe, 0x89, 0x8e, 0x5e };
unsigned char Rxccmpktcnt[5] __attribute__((aligned(4))) = { 0xd6, 0xbe, 0x89, 0x8e, 0x5e };

unsigned char rx_packet[128 * 4] __attribute__((aligned(4)));
unsigned char ble_tx_packet[48]
        __attribute__((aligned(4))) = { 3, 0, 0, 0, 0, 10, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xc, 0xf };

#define TX          1
#define RX          2
#define RF_TRX_MODE TX

#define RF_FREQ        17
#define ACCESS_CODE    0x29417671 //0xd6be898e// 0x898e898e//
#define RX_FIFO_NUM    4
#define RX_FIFO_DEP    128
#define TX_PKT_PAYLOAD 15

volatile unsigned int rx_cnt = 0;
volatile unsigned int tx_cnt = 0;

void user_init(void)
{
    rf_set_ble_2M_NO_PN_mode();
    rf_set_power_level(RF_POWER);
    rf_set_chn(RF_FREQ);
    rf_access_code_comm(ACCESS_CODE);

#if (RF_TRX_MODE == TX)
    rf_set_tx_dma(2, 128);

    rf_ble_crypt_setup(sKey, IV);
    rf_set_ble_crypt_tx_cnt(Txccmpktcnt);
    rf_ble_crypt_en();
    rf_set_ble_crypt_master_mode();
    rf_ble_crypt_txpktcnt_updata_dis();

#elif (RF_TRX_MODE == RX)
    rf_set_rx_dma(rx_packet, RX_FIFO_NUM - 1, RX_FIFO_DEP);

    rf_ble_crypt_setup(sKey, IV);
    rf_set_ble_crypt_rx_cnt(Rxccmpktcnt);
    rf_ble_crypt_en();
    rf_set_ble_crypt_slave_mode();
    rf_ble_crypt_rxpktcnt_updata_dis();
#endif

    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);
}

void main_loop(void)
{
#if (RF_TRX_MODE == TX)
    unsigned char rf_data_len  = TX_PKT_PAYLOAD + 2;
    ble_tx_packet[4]           = 0;
    ble_tx_packet[5]           = TX_PKT_PAYLOAD + 4;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3]           = (rf_tx_dma_len >> 24) & 0xff;
    ble_tx_packet[2]           = (rf_tx_dma_len >> 16) & 0xff;
    ble_tx_packet[1]           = (rf_tx_dma_len >> 8) & 0xff;
    ble_tx_packet[0]           = rf_tx_dma_len & 0xff;
    rf_start_stx(ble_tx_packet, rf_stimer_get_tick());
    while (1)
    {
        delay_ms(1);
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        delay_us(60);
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        rf_start_stx(ble_tx_packet, rf_stimer_get_tick());
        if (tx_cnt % 40 == 0) {
            gpio_toggle(LED1);
        }
        tx_cnt++;
    }

#elif (RF_TRX_MODE == RX)
    rf_start_srx(rf_stimer_get_tick());
    while (1)
    {
        if (rf_get_irq_status(FLD_RF_IRQ_RX))
        {
            unsigned char *raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM, RX_FIFO_DEP, rx_packet);
            if (rf_ble_packet_crc_ok(raw_pkt))
            {
                gpio_toggle(LED1);
                rx_cnt++;
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
            rf_start_srx(rf_stimer_get_tick());
        }
    }
#endif
}

#endif

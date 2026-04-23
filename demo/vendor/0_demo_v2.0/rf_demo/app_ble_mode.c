/********************************************************************************************************
 * @file    app_ble_mode.c
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
#include "common.h"
#pragma GCC push_options
#pragma GCC optimize ("O0")

#define RXADDR          0x50090000  // channel 1
#define TXADDR          0x50091000  // channel 0

#if (RF_MODE == RF_BLE_1M || RF_MODE == RF_BLE_2M || RF_MODE == RF_LR_S2_500K || RF_MODE == RF_LR_S8_125K || RF_MODE == RF_BLE_1M_NO_PN || RF_MODE == RF_BLE_2M_NO_PN )


// unsigned char rx_packet[128 * 4] __attribute__((aligned(4)));
// unsigned char ble_tx_packet[48] __attribute__((aligned(4))) = {3, 0, 0, 0, 0, 10, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xc, 0xf};
unsigned char *ble_tx_packet  = (unsigned char *)TXADDR;
unsigned char *rx_packet      = (unsigned char *)RXADDR;

//unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) ={3,0,0,0,0,0x21, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x01, 0x05, 0x0D, 0x09, 0x38, 0x35, 0x39, 0x34, 0x46, 0x34, 0x36, 0x34, 0x30, 0x43, 0x42, 0x42, 0x09, 0xFF, 0x11, 0x02, 0x11, 0x02, 0xB2, 0x14, 0x21, 0x38};


    #define TX             1
    #define RX             2
    #define RF_TRX_MODE    TX

    #define AUTO           1
    #define MANUAL         2
    #define RF_AUTO_MODE   AUTO

    #define RF_RX_IRQ_EN   0

    #define TX_PKT_PAYLOAD 15

    #define RX_FIFO_NUM    4
    #define RX_FIFO_DEP    128


    #define RF_FREQ        38
    #define ACCESS_CODE    0xf8118ac9//0x29417671 //0xd6be898e// 0x898e898e//

volatile unsigned int rx_cnt = 0;
volatile unsigned int rx_sync_cnt = 0;
volatile unsigned int tx_cnt = 0;
    #if (RF_RX_IRQ_EN)
_attribute_ram_code_sec_ void rf_irq_handler(void)
{
    if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
        rx_irq_cnt++;
        #if (RF_AUTO_MODE == AUTO)
        unsigned char *raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM, RX_FIFO_DEP, rx_packet);
        if (rf_ble_packet_crc_ok(raw_pkt)) {
            rx_cnt++;
            gpio_toggle(LED2);
        }
        rf_start_srx(rf_stimer_get_tick());
        #else
        if (rf_ble_packet_crc_ok(rx_packet)) {
            rx_cnt++;
            gpio_toggle(LED2);
        }
        #endif

        rf_clr_irq_status(FLD_RF_IRQ_RX);


    } else {
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
}
        #if defined(MCU_CORE_TL752X_N22)
CLIC_ISR_REGISTER(rf_irq_handler, IRQ_TAHDT)
        #else
PLIC_ISR_REGISTER(rf_irq_handler, IRQ_TAHDT)
        #endif
    #endif

    #define LED0  0
    #define LED1  1
    #define LED2  2
    #define LED3  3
    #define LED4  4

    #if (RF_AUTO_MODE == AUTO)
void user_init(void)
{
    rf_set_ble_bb_debugport();
    rf_set_power_level(RF_POWER);
        #if (RF_MODE == RF_BLE_1M_NO_PN || RF_MODE == RF_BLE_2M_NO_PN)
    rf_set_chn(RF_FREQ);
        #else
    rf_set_ble_chn(RF_FREQ);
        #endif
    rf_access_code_comm(ACCESS_CODE);

        #if (RF_TRX_MODE == TX)
    rf_set_tx_dma(2, 128);
        #elif (RF_TRX_MODE == RX)
    rf_set_rx_dma(rx_packet, RX_FIFO_NUM - 1, RX_FIFO_DEP);
            #if (RF_RX_IRQ_EN)
#if defined(MCU_CORE_TL752X_N22)
    clic_init();
    clic_interrupt_enable(IRQ_TAHDT);
#else
    plic_interrupt_enable(IRQ_TAHDT);
#endif

    core_interrupt_enable();
    rf_set_irq_mask(FLD_RF_IRQ_RX);
    rf_start_srx(rf_stimer_get_tick());

            #endif
        #endif
}

void main_loop(void)
{
        #if (RF_TRX_MODE == TX)
    unsigned char rf_data_len  = TX_PKT_PAYLOAD + 2;
    ble_tx_packet[4]           = 0;
    ble_tx_packet[5]           = TX_PKT_PAYLOAD;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3]           = (rf_tx_dma_len >> 24) & 0xff;
    ble_tx_packet[2]           = (rf_tx_dma_len >> 16) & 0xff;
    ble_tx_packet[1]           = (rf_tx_dma_len >> 8) & 0xff;
    ble_tx_packet[0]           = rf_tx_dma_len & 0xff;
    rf_start_stx(ble_tx_packet, rf_stimer_get_tick());
    while (1) {
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        delay_us(100);
        rf_start_stx(ble_tx_packet, rf_stimer_get_tick());
        tx_cnt++;
    }


        #elif (RF_TRX_MODE == RX)
            #if (!RF_RX_IRQ_EN)

    rf_start_srx(rf_stimer_get_tick());
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            rx_sync_cnt++;
            unsigned char *raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM, RX_FIFO_DEP, rx_packet);
            if (rf_ble_packet_crc_ok(raw_pkt)) {
                rx_cnt++;
                //              delay_ms(100);
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
                #if defined(MCU_CORE_TL7518)
            delay_us(5); //Currently, the TL7518 chip also requires a seq delay of at least 5us after the end of the TX and RX EN states.
                #endif
            rf_start_srx(rf_stimer_get_tick());
        }
    }
            #endif
        #endif
    delay_ms(100);
}

    #elif (RF_AUTO_MODE == MANUAL)

void user_init(void)
{
    rf_set_power_level(RF_POWER);
        #if (RF_MODE == RF_BLE_1M_NO_PN || RF_MODE == RF_BLE_2M_NO_PN)
    rf_set_chn(RF_FREQ);
        #else
    rf_set_chn(RF_FREQ);
    // rf_set_ble_chn(RF_FREQ);
        #endif

    rf_access_code_comm(ACCESS_CODE);

        #if (RF_TRX_MODE == TX)
    rf_set_tx_dma(2, 128);
    // tx_dma(ble_tx_packet,200,2);
        #elif (RF_TRX_MODE == RX)
    rf_set_rx_dma(rx_packet, RX_FIFO_NUM - 1, RX_FIFO_DEP);

            #if (RF_RX_IRQ_EN)
#if defined(MCU_CORE_TL752X_N22)
    clic_init();
    clic_interrupt_enable(IRQ_TAHDT);
#else
    plic_interrupt_enable(IRQ_TAHDT);
#endif

    core_interrupt_enable();
    rf_set_irq_mask(FLD_RF_IRQ_RX);
    rf_set_rxmode();
    delay_us(85); //Wait for calibration to stabilize
            #endif
        #endif
}

void main_loop(void)
{
    #if (RF_TRX_MODE == TX)
    unsigned char rf_data_len  = TX_PKT_PAYLOAD + 2;
    ble_tx_packet[4]           = 0;
    ble_tx_packet[5]           = TX_PKT_PAYLOAD;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3]           = (rf_tx_dma_len >> 24) & 0xff;
    ble_tx_packet[2]           = (rf_tx_dma_len >> 16) & 0xff;
    ble_tx_packet[1]           = (rf_tx_dma_len >> 8) & 0xff;
    ble_tx_packet[0]           = rf_tx_dma_len & 0xff;

    rf_set_txmode();
    delay_us(47); //Wait for calibration to stabilize
    while (1) {
        rf_tx_pkt(ble_tx_packet);
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        tx_cnt++;
    }
    #elif (RF_TRX_MODE == RX)
        #if (!RF_RX_IRQ_EN)
    rf_set_rxmode();
    delay_us(47); //Wait for calibration to stabilize
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            if (rf_ble_packet_crc_ok(rx_packet)) {
                rx_cnt++;
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
        }
    }
        #endif
    #endif
    delay_ms(100);

}
    #endif
#endif

#pragma GCC pop_options

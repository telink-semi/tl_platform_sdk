/********************************************************************************************************
 * @file    app_ble_4m_6m_mode.c
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
#if  defined(MCU_CORE_TL322X)&&(RF_MODE == RF_BLE_4M || RF_MODE == RF_BLE_6M ||  RF_MODE == RF_BLE_4M_NO_PN || RF_MODE == RF_BLE_6M_NO_PN)


unsigned char rx_packet[128 * 4] __attribute__((aligned(4)));
unsigned char ble_tx_packet[48] __attribute__((aligned(4))) = {3, 0, 0, 0, 0, 10, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xc, 0xf};

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


    #define RF_FREQ        17
    #define ACCESS_CODE    0x29417671 //0xd6be898e// 0x898e898e//
    #define RF_HIGH_PER_MODE     1

volatile unsigned int rx_cnt = 0;
volatile unsigned int tx_cnt = 0;
    #if (RF_RX_IRQ_EN)
_attribute_ram_code_sec_ void rf_irq_handler(void)
{
    if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
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
        #if defined(MCU_CORE_TL322X_N22)
CLIC_ISR_REGISTER(rf_irq_handler, IRQ_ZB_RT)
        #else
PLIC_ISR_REGISTER(rf_irq_handler, IRQ_ZB_RT)
        #endif
    #endif

    #if (RF_AUTO_MODE == AUTO)
void user_init(void)
{
    // Set modem rate to 48 MHz for 4/6 Mbps operation
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
#if (RF_HIGH_PER_MODE)
    rf_modem_hp_path(1);
#else
    rf_modem_hp_path(0);
#endif
    rf_set_power_level(RF_POWER);
        #if (RF_MODE == RF_BLE_4M_NO_PN || RF_MODE == RF_BLE_6M_NO_PN)
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
    core_interrupt_enable();
                #if defined(MCU_CORE_TL322X_N22)
    clic_init();
    clic_interrupt_enable(IRQ_ZB_RT);
                #else
    plic_interrupt_enable(IRQ_ZB_RT);
                #endif
    rf_set_irq_mask(FLD_RF_IRQ_RX);
    rf_start_srx(rf_stimer_get_tick());

            #endif
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
    ble_tx_packet[5]           = TX_PKT_PAYLOAD;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3]           = (rf_tx_dma_len >> 24) & 0xff;
    ble_tx_packet[2]           = (rf_tx_dma_len >> 16) & 0xff;
    ble_tx_packet[1]           = (rf_tx_dma_len >> 8) & 0xff;
    ble_tx_packet[0]           = rf_tx_dma_len & 0xff;
    rf_start_stx(ble_tx_packet, rf_stimer_get_tick());

    while (1) {
        delay_ms(1);
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        rf_start_stx(ble_tx_packet, rf_stimer_get_tick());
        gpio_toggle(LED1);
        //delay_ms(100);
        tx_cnt++;
    }


        #elif (RF_TRX_MODE == RX)
            #if (!RF_RX_IRQ_EN)

    rf_start_srx(rf_stimer_get_tick());
    gpio_toggle(LED1);
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            unsigned char *raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM, RX_FIFO_DEP, rx_packet);
            if (rf_ble_packet_crc_ok(raw_pkt)) {
                gpio_toggle(LED2);
                rx_cnt++;
                //delay_ms(100);
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
            rf_start_srx(rf_stimer_get_tick());
            gpio_toggle(LED2);
        }
    }
            #endif
        #endif
    gpio_toggle(LED4);
    delay_ms(100);
}

    #elif (RF_AUTO_MODE == MANUAL)

void user_init(void)
{
    // Set modem rate to 48 MHz for 4/6 Mbps operation
    rf_modem_rate_mode(RF_48M_MODEM_RATE);//When using 4 Mbps or 6 Mbps data rates, the 48 MHz modem rate must be applied.
#if (RF_HIGH_PER_MODE)
    rf_modem_hp_path(1);
#else
    rf_modem_hp_path(0);
#endif
    rf_set_power_level(RF_POWER);
        #if (RF_MODE == RF_BLE_4M_NO_PN || RF_MODE == RF_BLE_6M_NO_PN)
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
    core_interrupt_enable();
                #if defined(MCU_CORE_TL322X_N22)
    clic_init();
    clic_interrupt_enable(IRQ_ZB_RT);
                #else
    plic_interrupt_enable(IRQ_ZB_RT);
                #endif
    rf_set_irq_mask(FLD_RF_IRQ_RX);
    rf_set_rxmode();
    delay_us(85); //Wait for calibration to stabilize
            #endif
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
    ble_tx_packet[5]           = TX_PKT_PAYLOAD;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3]           = (rf_tx_dma_len >> 24) & 0xff;
    ble_tx_packet[2]           = (rf_tx_dma_len >> 16) & 0xff;
    ble_tx_packet[1]           = (rf_tx_dma_len >> 8) & 0xff;
    ble_tx_packet[0]           = rf_tx_dma_len & 0xff;
    rf_set_txmode();
    delay_us(113); //Wait for calibration to stabilize

    while (1) {
        delay_ms(1);
        rf_tx_pkt(ble_tx_packet);
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        gpio_toggle(LED1);
        tx_cnt++;
    }

        #elif (RF_TRX_MODE == RX)
            #if (!RF_RX_IRQ_EN)
    rf_set_rxmode();
    delay_us(85); //Wait for calibration to stabilize
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            if (rf_ble_packet_crc_ok(rx_packet)) {
                gpio_toggle(LED1);
                rx_cnt++;
                //delay_ms(100);
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
        }
    }
            #endif
        #endif

    gpio_toggle(LED4);
    delay_ms(100);
}

    #endif

#endif

/********************************************************************************************************
 * @file    app_pri_generic_mode.c
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

#if ((defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)) && (RF_MODE == RF_PRI_GENERIC_1M || RF_MODE == RF_PRI_GENERIC_2M || RF_MODE == RF_PRI_GENERIC_250K || RF_MODE == RF_PRI_GENERIC_500K))


unsigned char rx_packet[128 * 4] __attribute__((aligned(4)));
unsigned char Private_generic_tx_packet[48] __attribute__((aligned(4))) = {3, 0, 0, 0, 0, 0, 20, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    #define TX                      1
    #define RX                      2
    #define RF_TRX_MODE             RX

    #define AUTO                    1
    #define MANUAL                  2
    #define RF_AUTO_MODE            AUTO


    #define PRI_GENERIC_FLT_MODE_EN 0

    #define RF_RX_IRQ_EN            0

    #define TX_PKT_PAYLOAD          32

    #define RX_FIFO_NUM             4
    #define RX_FIFO_DEP             128

    #define RF_FREQ                 17
    #define ACCESS_CODE             0x29417671 // 0xd6be898e//
volatile unsigned int rx_cnt      = 0;
volatile unsigned int math_cnt    = 0;
volatile unsigned int unmath_cnt  = 0;
volatile unsigned int tx_cnt      = 0;
unsigned char         h0_size     = 5;
unsigned char         h1_size     = 4;
unsigned char         length_size = 15;
unsigned short        h0_val      = 26;
unsigned short        h1_val      = 14;

    #if (PRI_GENERIC_FLT_MODE_EN)
/**
 *  @note  The rf_pkt_flt function matches from the high bit,
 *         You need to configure rf_pkt_mask and rf_pkt_match from the high bit when configuring it.
*/
rf_pkt_flt_t rf_pkt_flt = {
    .rf_pkt_flt_start       = 0,
    .rf_pkt_flt_end         = 9,
    .rf_pkt_match_threshold = 16,
    .rf_pkt_match_low       = 0x00000000,
    .rf_pkt_match_high      = 0x44332211,
    .rf_pkt_mask_low        = 0x00000000,
    .rf_pkt_mask_high       = 0xff00ff00,
};
    #endif
    #if (RF_RX_IRQ_EN)
_attribute_ram_code_sec_ void rf_irq_handler(void)
{
    if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
        if (!rf_get_crc_err()) {
            rx_cnt++;
            gpio_toggle(LED2);
        }
        rf_clr_irq_status(FLD_RF_IRQ_RX);
    }
    if (rf_get_irq_status(FLD_RF_IRQ_PKT_MATCH)) {
        math_cnt++;
        rf_clr_irq_status(FLD_RF_IRQ_PKT_MATCH);
    }
    if (rf_get_irq_status(FLD_RF_IRQ_PKT_UNMATCH)) {
        unmath_cnt++;
        rf_clr_irq_status(FLD_RF_IRQ_PKT_UNMATCH);
    } else {
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
        #if (RF_AUTO_MODE == AUTO)
    rf_start_srx(rf_stimer_get_tick());
        #endif
}
PLIC_ISR_REGISTER(rf_irq_handler, IRQ_ZB_RT)
    #endif

    #if (RF_AUTO_MODE == AUTO)
void user_init(void)
{
    rf_set_power_level(RF_POWER);
    rf_set_chn(RF_FREQ);
    rf_access_code_comm(ACCESS_CODE);

    rf_set_pri_generic_header_size(h0_size, length_size, h1_size);
    rf_set_pri_generic_length_adj(2);
        #if (PRI_GENERIC_FLT_MODE_EN)
    rf_set_pkt_filter(rf_pkt_flt);
        #endif

        #if (RF_TRX_MODE == TX)
    rf_set_tx_dma(2, 128);
        #elif (RF_TRX_MODE == RX)
    rf_set_rx_dma(rx_packet, RX_FIFO_NUM - 1, RX_FIFO_DEP);
            #if (RF_RX_IRQ_EN)
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_ZB_RT);
    rf_set_irq_mask(FLD_RF_IRQ_RX | FLD_RF_IRQ_PKT_UNMATCH | FLD_RF_IRQ_PKT_MATCH);
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

    unsigned char      header_len  = (h0_size + h1_size + length_size) >> 3;
    unsigned int       rf_data_len = TX_PKT_PAYLOAD + header_len;
    unsigned long long header      = h0_val | ((unsigned long long)TX_PKT_PAYLOAD << h0_size) | ((unsigned long long)h1_val << (h0_size + length_size));
    for (unsigned char i = 0; i < header_len; i++) {
        Private_generic_tx_packet[4 + i] = (header >> (8 * i)) & 0xff;
    }
    unsigned int rf_tx_dma_len   = rf_tx_packet_dma_len(rf_data_len);
    Private_generic_tx_packet[3] = (rf_tx_dma_len >> 24) & 0xff;
    Private_generic_tx_packet[2] = (rf_tx_dma_len >> 16) & 0xff;
    Private_generic_tx_packet[1] = (rf_tx_dma_len >> 8) & 0xff;
    Private_generic_tx_packet[0] = rf_tx_dma_len & 0xff;
    rf_start_stx(Private_generic_tx_packet, rf_stimer_get_tick());

    while (1) {
        delay_ms(1);
        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)))
            ;
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        rf_start_stx(Private_generic_tx_packet, rf_stimer_get_tick());
        gpio_toggle(LED4);
        //delay_ms(100);
        tx_cnt++;
    }


        #elif (RF_TRX_MODE == RX)
            #if (!RF_RX_IRQ_EN)

    rf_start_srx(rf_stimer_get_tick());
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            if (!rf_get_crc_err()) {
                gpio_toggle(LED4);
                rx_cnt++;
                //              delay_ms(10);
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX);
            rf_start_srx(rf_stimer_get_tick());
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
    rf_set_power_level(RF_POWER);
    rf_set_chn(RF_FREQ);
    rf_access_code_comm(ACCESS_CODE);

    rf_set_pri_generic_header_size(h0_size, length_size, h1_size);
    rf_set_pri_generic_length_adj(2);
        #if (PRI_GENERIC_FLT_MODE_EN)
    rf_set_pkt_filter(rf_pkt_flt);
        #endif

        #if (RF_TRX_MODE == TX)
    rf_set_tx_dma(2, 128);
        #elif (RF_TRX_MODE == RX)
    rf_set_rx_dma(rx_packet, RX_FIFO_NUM - 1, RX_FIFO_DEP);

            #if (RF_RX_IRQ_EN)

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_ZB_RT);
    rf_set_irq_mask(FLD_RF_IRQ_RX);
    rf_set_rxmode();
                #if (defined(MCU_CORE_TL321X))
    delay_us(93); //Wait for calibration to stabilize
                #else
    delay_us(85); //Wait for calibration to stabilize
                #endif

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

    unsigned char      header_len  = (h0_size + h1_size + length_size) >> 3;
    unsigned int       rf_data_len = TX_PKT_PAYLOAD + header_len;
    unsigned long long header      = h0_val | (TX_PKT_PAYLOAD << h0_size) | (h1_val << (h0_size + length_size));
    for (unsigned char i = 0; i < header_len; i++) {
        Private_generic_tx_packet[4 + i] = (header >> (8 * i)) & 0xff;
    }
    unsigned int rf_tx_dma_len   = rf_tx_packet_dma_len(rf_data_len);
    Private_generic_tx_packet[3] = (rf_tx_dma_len >> 24) & 0xff;
    Private_generic_tx_packet[2] = (rf_tx_dma_len >> 16) & 0xff;
    Private_generic_tx_packet[1] = (rf_tx_dma_len >> 8) & 0xff;
    Private_generic_tx_packet[0] = rf_tx_dma_len & 0xff;

    rf_set_txmode();
    delay_us(113); //Wait for calibration to stabilize

    while (1) {
        delay_ms(1);
        rf_tx_pkt(Private_generic_tx_packet);

        while (!(rf_get_irq_status(FLD_RF_IRQ_TX)))
            ;
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        gpio_toggle(LED4);
        //delay_ms(100);
        tx_cnt++;
    }


        #elif (RF_TRX_MODE == RX)
            #if (!RF_RX_IRQ_EN)

    rf_set_rxmode();
                #if (defined(MCU_CORE_TL321X))
    delay_us(93); //Wait for calibration to stabilize
                #else
    delay_us(85); //Wait for calibration to stabilize
                #endif
    while (1) {
        if (rf_get_irq_status(FLD_RF_IRQ_RX)) {
            if (!rf_get_crc_err()) {
                gpio_toggle(LED4);
                rx_cnt++;
                //              delay_ms(100);
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

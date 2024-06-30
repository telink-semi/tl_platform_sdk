/********************************************************************************************************
 * @file    app_fast_settle_test.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "app_config.h"

#if (!defined(MCU_CORE_TL751X)&&(RF_MODE==RF_FAST_SETTLE_TEST))

unsigned char  rx_packet[128*4]  __attribute__ ((aligned (4)));
unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) ={3,0,0,0,0,10,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xc,0xf};

#define TX                  1
#define RX                  2
#define RF_TRX_MODE         TX

#define RF_FREQ             17
#define ACCESS_CODE         0x29417671//0xd6be898e// 0x898e898e//
#define RX_FIFO_NUM         4
#define RX_FIFO_DEP         128
#define TX_PKT_PAYLOAD      15

void rf_fast_settle_setup(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us);

volatile unsigned int rx_cnt=0;
volatile unsigned int tx_cnt=0;

void user_init(void)
{
    rf_set_ble_1M_NO_PN_mode();
    rf_set_power_level(RF_POWER);
    rf_access_code_comm(ACCESS_CODE);

#if(RF_TRX_MODE==TX)
    rf_set_tx_dma(2,128);

#elif(RF_TRX_MODE==RX)
    rf_set_rx_dma(rx_packet,RX_FIFO_NUM-1,RX_FIFO_DEP);

#endif

    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
}

void main_loop (void)
{
    /* Note: The fast settle function call must be rf_fast_settle_setup ->rf_fast_settle_config ->fast_tx/rx_settle_en*/
    /* The channel has been modified in the rf_fast_settle_setup interface, so after setting fast settle, the channel needs to be reset.*/
#if defined(MCU_CORE_B91)||defined(MCU_CORE_B92)

    rf_fast_settle_setup(TX_SETTLE_TIME_50US,RX_SETTLE_TIME_45US);
    rf_fast_settle_config(TX_SETTLE_TIME_50US,RX_SETTLE_TIME_45US);

    rf_tx_fast_settle_en();
    rf_rx_fast_settle_en();

    rf_set_tx_settle_time(50);
    rf_set_rx_settle_time(45);

    rf_set_chn(RF_FREQ);
#elif defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    rf_fast_settle_setup(TX_SETTLE_TIME_15US,RX_SETTLE_TIME_15US);
    if(-1 == rf_fast_settle_config(TX_SETTLE_TIME_15US,RX_SETTLE_TIME_15US))
    {
        //Incorrect configuration.
        gpio_toggle(LED2);
    }
    rf_tx_fast_settle_en();
    rf_rx_fast_settle_en();
    rf_set_tx_settle_time(15);
    rf_set_rx_settle_time(15);

    rf_set_chn(RF_FREQ);
#endif

#if(RF_TRX_MODE==TX)
    unsigned char rf_data_len = TX_PKT_PAYLOAD+2;
    ble_tx_packet[4]=0;
    ble_tx_packet[5]=TX_PKT_PAYLOAD;
    unsigned int rf_tx_dma_len = rf_tx_packet_dma_len(rf_data_len);
    ble_tx_packet[3] = (rf_tx_dma_len >> 24)&0xff;
    ble_tx_packet[2] = (rf_tx_dma_len >> 16)&0xff;
    ble_tx_packet[1] = (rf_tx_dma_len >> 8)&0xff;
    ble_tx_packet[0] = rf_tx_dma_len&0xff;
    rf_start_stx(ble_tx_packet,rf_stimer_get_tick());
    while(1)
    {
        delay_ms(1);
        while(!(rf_get_irq_status(FLD_RF_IRQ_TX)));
        delay_us(60);//At present, the tx path delay of ONCA is at least 55us(TX IRQ flag position 1 to tx transmitter sends packet takes at least 55us)
                     //It will be adjusted in the next version.changed by chenxi,confirmed by xuqiang.
        rf_clr_irq_status(FLD_RF_IRQ_TX);
        ble_tx_packet[4]++;
        rf_start_stx(ble_tx_packet,rf_stimer_get_tick());
        gpio_toggle(LED1);
        tx_cnt++;
    }

#elif(RF_TRX_MODE==RX)

    rf_start_srx(rf_stimer_get_tick());
    while(1)
    {
        if(rf_get_irq_status(FLD_RF_IRQ_RX))
        {
            unsigned char* raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM,RX_FIFO_DEP,rx_packet);
            if(rf_ble_packet_crc_ok(raw_pkt))
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

/**
 *  @brief      This function is used to initialize the calibration value of rf tx/rx fast settle
 *  @param[in]  tx_settle_us    After adjusting the timing sequence, the time required for tx to settle.
 *  @param[in]  rx_settle_us    After adjusting the timing sequence, the time required for rx to settle.
 *  @return     none
 */
void rf_fast_settle_setup(rf_tx_fast_settle_time_e tx_settle_us, rf_rx_fast_settle_time_e rx_settle_us)
{
    //tx
    rf_set_tx_rx_off_auto_mode();//STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);//CLEAR_ALL_RFIRQ_STATUS;

    rf_set_tx_settle_time(115);//adjust TX settle time
    rf_set_tx_dma(2,128);

    for(unsigned char chn=0;chn<=80;chn++)
    {
        rf_set_chn(chn);
        rf_start_stx(ble_tx_packet,rf_stimer_get_tick());
        delay_us(115);//Wait for the tx packetization action to complete, ensuring that the settle time on each channel

        rf_tx_fast_settle_update_cal_val(tx_settle_us,chn);

        rf_set_tx_rx_off_auto_mode();//STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }

    //rx
    rf_set_rx_settle_time(85);//adjust RX settle time
    rf_start_srx(rf_stimer_get_tick());
    delay_us(85);//Wait for the rx packetization action to complete

#if defined(MCU_CORE_B91)||defined(MCU_CORE_B92)
    rf_rx_fast_settle_update_cal_val(rx_settle_us,0);
    rf_set_tx_rx_off_auto_mode();//STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
#elif defined(MCU_CORE_TL721X)||defined(MCU_CORE_TL321X)
    rf_set_tx_rx_off_auto_mode();//STOP_RF_STATE_MACHINE;
    rf_clr_irq_status(FLD_RF_IRQ_ALL);
    for(unsigned char chn=4;chn<=80;chn+=10)
    {
        rf_set_chn(chn);
        rf_start_srx(rf_stimer_get_tick());
        delay_us(85);//Wait for the rx packetization action to complete

        rf_rx_fast_settle_update_cal_val(rx_settle_us,chn);

        rf_set_tx_rx_off_auto_mode();//STOP_RF_STATE_MACHINE;
        rf_clr_irq_status(FLD_RF_IRQ_ALL);
    }
#endif
}

#endif

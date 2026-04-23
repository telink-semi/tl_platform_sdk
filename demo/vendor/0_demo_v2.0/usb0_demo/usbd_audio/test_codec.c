/********************************************************************************************************
 * @file    test_codec.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
/*
 * @FilePath: \epm_driver\demo\usb2.0\usbd_audio_hs_v2\test_codec.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: codec test code
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "common.h"
#if (USB_DEMO_TYPE == USB_MIC_SPK)
#include "math.h"
#include "app_audio.h"

/*************************** macro definition ********************************/
#define RAM_ADDR_OFFSET (0x40000000)

#define SAT_32_24(x) ((x > 8388607) ? 8388607 : ((x < -8388608) ? -8388608 : x))

/**************************** type definition ********************************/

/************************* variable definition *******************************/
volatile uint8_t codec_dac_dma_ready = 1;
uint32_t data_test2[192];
uint16_t data_test3[192];
dmac_handle_t audio_adc_dmac_handle;
dmac_handle_t audio_dac_dmac_handle;

extern uint8_t send_ok_flag;
extern uint8_t PlayFlag;
extern uint8_t recordFlag;
extern uint32_t IsocInBuff[];
extern uint8_t IsocOutBuff[];
extern uint32_t *IsocInRdPtr;
extern uint8_t *IsocOutRdPtr;
extern uint8_t *IsocOutWrPtr;
extern uint32_t ADC_W_Num;
extern uint32_t ADC_R_Num;

/**************************** function declear *******************************/

/********************** function implementation ******************************/
void CPU2_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&audio_adc_dmac_handle);
    drv_dmac_irq_handle(&audio_dac_dmac_handle);
}

ISR_REGISTER(CPU2_DMA_IRQHandler, CPU2_DMA_IRQn)

void audio_codec_adc_buf_clear(void)
{
    ADC_R_Num = 0;
    ADC_W_Num = 0;
}

usb_status_t audio_codec_adc_test(void)
{
    int32_t *p_in;
    uint16_t *p_out;
    static uint8_t adc_en = 0;

    if (recordFlag && !adc_en) {
        adc_en = 1;
        send_ok_flag = 1;
        audio_codec_adc_buf_clear();
        drv_audio_adc_dma_rx((uint32_t *)((uint32_t)IsocInBuff + RAM_ADDR_OFFSET), UAC_IN_PACKET_LEN / 4);
        drv_audio_adc_start(CODEC_ADC_PORT);
        soc_printf("adc enable!\r\n");
    } else if (adc_en && !recordFlag) {
        adc_en = 0;
        drv_audio_adc_stop(CODEC_ADC_PORT);
        audio_codec_adc_buf_clear();
        soc_printf("adc disable!\r\n");
    }

    if (recordFlag == 0) {
        return USB_BUSY;
    }
    if (send_ok_flag == 0) {
        return USB_FAIL;
    }
    if (ADC_R_Num == ADC_W_Num) {
        return USB_FAIL;
    }
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_2, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_2, GPIO_PIN_RESET);

    send_ok_flag = 0;
    p_in = (int32_t *)&IsocInRdPtr[ADC_R_Num];
    p_out = (uint16_t *)data_test3;
    /* codec adc use 24bit 1ch, usb audio use 16bit 2ch*/
    for (uint16_t k = 0; k < UAC_IN_PACKET_LEN / 4; k++) {
        int32_t temp;
        temp = (int)*p_in << 8;
        temp = SAT_32_24((temp >> 8));
        *p_out++ = (uint16_t)((temp >> 8) & 0xffff);
        *p_out++ = (uint16_t)((temp >> 8) & 0xffff);
        p_in++;
    }
    usbd_ep_tx(AUDIO_IN_EP, (uint8_t *)data_test3, UAC_IN_PACKET_LEN);
    drv_hw_global_int_disable();
    if (ADC_R_Num >= (MIC_TOTAL_BUF_SIZE - UAC_IN_PACKET_LEN / 4)) {
        /* Roll back to the start of buffer */
        ADC_R_Num = 0;
    } else {
        /* Increment to the next sub-buffer */
        ADC_R_Num += UAC_IN_PACKET_LEN / 4;
    }
    drv_hw_global_int_restore();
    return USB_OK;
}

void codec_adc_dmac_irq_cb(void *args)
{
    (void)args;
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_1, GPIO_PIN_SET);
    drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_1, GPIO_PIN_RESET);

    if (ADC_W_Num >= (MIC_TOTAL_BUF_SIZE - UAC_IN_PACKET_LEN / 4)) {
        ADC_W_Num = 0;
    } else {
        ADC_W_Num += UAC_IN_PACKET_LEN / 4;
    }
    drv_audio_adc_dma_rx((uint32_t *)((uint32_t)(&IsocInRdPtr[ADC_W_Num]) + RAM_ADDR_OFFSET), UAC_IN_PACKET_LEN / 4);
}

usb_status_t system_audio_play_test(void)
{
    uint32_t *p_in;
    uint32_t *p_out;

    if (PlayFlag == 0) {
        return USB_BUSY;
    }
    if (codec_dac_dma_ready == 0) {
        return USB_BUSY;
    }
    codec_dac_dma_ready = 0;
    /* usb audio use 32bit data */
    p_in = (uint32_t *)&IsocOutRdPtr[0];
    p_out = (uint32_t *)data_test2;
    for (uint16_t k = 0; k < UAC_OUT_PACKET_LEN / 4; k++) {
        *p_out++ = ((int32_t)*p_in >> 8);
        p_in++;
    }
    drv_audio_dac_dma_tx((uint32_t *)((uint32_t)data_test2 + RAM_ADDR_OFFSET), UAC_OUT_PACKET_LEN / 4);
    if (IsocOutRdPtr >= (IsocOutBuff + SPEAKER_TOTAL_BUF_SIZE - UAC_OUT_PACKET_LEN)) /* Roll back to the start of buffer */
    {
        IsocOutRdPtr = IsocOutBuff;
    } else /* Increment to the next sub-buffer */
    {
        IsocOutRdPtr += UAC_OUT_PACKET_LEN;
    }

    /* If all available buffers have been consumed, stop playing */
    if (IsocOutRdPtr == IsocOutWrPtr) {
        /* Stop entering play loop */
        PlayFlag = 0;
    }

    return USB_OK;
}

void codec_dac_dmac_irq_cb(void *args)
{
    (void)args;
    codec_dac_dma_ready = 1;
}

void codec_dac_adc_init(void)
{
    drv_cpr_enable_fracpll(FRACPLL_OUT_FREQ);
    cpr_mclk1_init_t mclk1_init;
    mclk1_init.freq = FRACPLL_OUT_FREQ;
    mclk1_init.source = DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL1;
    drv_cpr_config_mclk1(&mclk1_init);

    drv_cpr_fine_adj_fracpll(57);

    /* Audio system powerup */
    drv_cpr_audio_system_powerup();
    drv_soc_codec_msp_init();

    __DRV_CPR_CPU2_DMA_CLK_ENABLE();
    drv_hw_int_enable(CPU2_DMA_IRQn); //enable hw int

    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();
    drv_hw_int_enable(AUDIO_DMA_IRQn); //enable hw int

    /* ADC cfg */
    drv_audio_adc_init();
    audio_adc_cfg_t adc_cfg;
    adc_cfg.dig_gain = AUDIO_ADC_DIG_GAIN_0DB;
    adc_cfg.pga_gain = 4;
    adc_cfg.fifo_src = AUDIO_ADC_FIFO_SRC_ADC;
    adc_cfg.fs = AUDIO_ADC_FS_48K;
    drv_audio_adc_open(CODEC_ADC_PORT, &adc_cfg);

    audio_adc_data_format_t adc_data_format;
    memset(&adc_data_format, 0, sizeof(audio_adc_data_format_t));
    adc_data_format.hdma = &audio_adc_dmac_handle;
    adc_data_format.ch_mode = AUDIO_ADC_MODE_MONO;
    adc_data_format.wide = AUDIO_ADC_24BIT;
    adc_data_format.fifo_en_bitmap = CODEC_ADC_PORT;
    drv_audio_adc_set_dma_data_format(&adc_data_format);
    drv_audio_adc_rx_complete_cb_register(codec_adc_dmac_irq_cb);
    // drv_audio_adc_dma_rx((uint32_t *)((uint32_t)IsocInBuff + RAM_ADDR_OFFSET), UAC_IN_PACKET_LEN / 4);
    // drv_audio_adc_start(CODEC_ADC_PORT);

    /* DAC cfg */
    drv_audio_dac_init();
    audio_dac_cfg_t cfg;
    cfg.autx_gain = AUDIO_DAC_AUTX_GAIN_0DB;
    cfg.dig_gain = AUDIO_DAC_DIG_GAIN_0DB;
    cfg.fs = AUDIO_DAC_FS_48K;
    cfg.src = AUDIO_DAC_SRC_PCM;
    drv_audio_dac_open(CODEC_DAC_PORT, &cfg);

    audio_dac_data_format_t data_format;
    memset(&data_format, 0, sizeof(audio_dac_data_format_t));
    data_format.hdma = &audio_dac_dmac_handle;
    data_format.ch_mode = AUDIO_DAC_MODE_STEREO;
    data_format.wide = AUDIO_DAC_24BIT;
    data_format.fifo_en_bitmap = CODEC_DAC_PORT;
    drv_audio_dac_set_dma_data_format(&data_format);
    drv_audio_dac_tx_complete_cb_register(codec_dac_dmac_irq_cb);
}
#endif

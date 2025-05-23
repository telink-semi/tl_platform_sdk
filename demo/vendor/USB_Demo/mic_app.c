/********************************************************************************************************
 * @file    mic_app.c
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
#if (USB_DEMO_TYPE == USB_MICROPHONE)
    #include "usb_default.h"
    #include "application/usbstd/usb.h"

    #if defined(MCU_CORE_TL751X) || defined(MCU_CORE_TL7518)
        #define MIC_SAMPLING_RATE (MIC_SAMPLE_RATE == 16000) ? AUDIO_16K : ((MIC_SAMPLE_RATE == 48000) ? AUDIO_48K : ((MIC_SAMPLE_RATE == 96000) ? AUDIO_96K : ((MIC_SAMPLE_RATE == 192000) ? AUDIO_192K : (MIC_SAMPLE_RATE == 384000) ? AUDIO_384K : \
                                                                                                                                                                                                                                         AUDIO_16K)))
    #else
        #define MIC_SAMPLING_RATE ((MIC_SAMPLE_RATE == 16000) ? AUDIO_16K : ((MIC_SAMPLE_RATE == 32000) ? AUDIO_32K : ((MIC_SAMPLE_RATE == 48000) ? AUDIO_48K : AUDIO_16K)))
    #endif

    #define MIC_BUFFER_SIZE 2048


    #if (MIC_RESOLUTION_BIT == 24)
int iso_in_buff[MIC_BUFFER_SIZE];
    #elif (MIC_RESOLUTION_BIT == 16)
short iso_in_buff[MIC_BUFFER_SIZE];
    #endif
    #if defined(MCU_CORE_B92) || defined(MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
extern volatile unsigned int g_vbus_timer_turn_off_start_tick;
extern volatile unsigned int g_vbus_timer_turn_off_flag;
    #endif
    #if defined(MCU_CORE_B91)
        #define AUDIO_LINE_IN   0
        #define AUDIO_AMIC_IN   1
        #define AUDIO_DMIC_IN   2

        #define AUDIO_IN_MODE   AUDIO_AMIC_IN
        #define MIC_MONO_STEREO ((MIC_CHANNEL_COUNT == 1) ? MONO_BIT_16 : STEREO_BIT_16)
        #define MIC_DMA_CHN     DMA2

volatile unsigned int iso_in_w   = 0;
volatile unsigned int iso_in_r   = 0;
unsigned int          num_iso_in = 0;

/**
 * @brief     This function serves to send data to USB. only adaptive mono 16bit
 * @param[in] audio_rate - audio rate. This value is matched with usb_default.h :MIC_SAMPLE_RATE.
 * @return    none.
 */

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned char length = 0;
    iso_in_w             = ((audio_get_rx_dma_wptr(MIC_DMA_CHN) - (unsigned int)iso_in_buff) >> 1);
    usbhw_reset_ep_ptr(USB_EDP_MIC); //reset pointer of Endpoint7's buf
    switch (audio_rate) {
    case AUDIO_8K:
        length = 8 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_16K:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_32K:
        length = 32 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_48K:
        length = 48 * MIC_CHANNEL_COUNT;
        break;
    default:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    }

    if (0 && (iso_in_w - (iso_in_r & (MIC_BUFFER_SIZE - 1))) < length) {
        for (unsigned char i = 0; i < length * 2; i++) {
            reg_usb_ep7_dat = 0;
        }
    }

    else {
        #if (MIC_RESOLUTION_BIT == 24)
        for (unsigned char i = 0; i < length; i++) {
            int md          = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
            reg_usb_ep7_dat = md;
            reg_usb_ep7_dat = md >> 8;
            reg_usb_ep7_dat = md >> 16;
        }
        #elif (MIC_RESOLUTION_BIT == 16)
        for (unsigned char i = 0; i < length && iso_in_r != iso_in_w; i++) {
            short md        = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
            reg_usb_ep7_dat = md;
            reg_usb_ep7_dat = md >> 8;
        }
        #endif
    }
    usbhw_data_ep_ack(USB_EDP_MIC);
}

/**
 * @brief       This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_ void usb_endpoint_irq_handler(void)
{
    if (usbhw_get_eps_irq() & FLD_USB_EDP7_IRQ) {
        usbhw_clr_eps_irq(FLD_USB_EDP7_IRQ);
        ; //clear interrupt flag of endpoint 7
        /////// get MIC input data ///////////////////////////////
        audio_tx_data_to_usb(MIC_SAMPLING_RATE);
        num_iso_in++;
        if ((num_iso_in & 0x7f) == 0) {
            gpio_toggle(LED1);
        }
    }
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)

void user_init(void)
{
        #if (CHIP_VER_A0 == CHIP_VER)
    audio_set_codec_supply(CODEC_2P8V);
        #endif
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);

    usbhw_set_ep_addr(USB_EDP6_OUT, 0x40);
    usbhw_set_ep_addr(USB_EDP7_IN, 0x20); /* 32 */
    usbhw_set_ep_addr(USB_EDP8_IN, 0x00); /* 32 */
    usbhw_set_eps_max_size(192);          /* max 192 */

    //enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
    usb_init();
    /* enable data endpoint USB_EDP7_IN. */
    usbhw_set_eps_en(BIT(USB_EDP7_IN));
    //enable global interrupt
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB_ENDPOINT); // enable usb endpoint interrupt
    usbhw_set_eps_irq_mask(FLD_USB_EDP7_IRQ);
    //enable USB DP pull up 1.5k
    usb_set_pin(1);

        #if (AUDIO_IN_MODE == AUDIO_LINE_IN)
    // set in path digital and analog gain, must be set before audio_init();
    audio_set_codec_in_path_a_d_gain(CODEC_IN_D_GAIN_12_DB, CODEC_IN_A_GAIN_20_DB);
    audio_init(LINE_IN_TO_BUF, MIC_SAMPLING_RATE, MIC_MONO_STEREO);
    audio_rx_dma_chain_init(MIC_DMA_CHN, (unsigned short *)&iso_in_buff, MIC_BUFFER_SIZE * 2);
        #elif (AUDIO_IN_MODE == AUDIO_DMIC_IN)
    audio_set_dmic_pin(DMIC_GROUPD_D4_DAT_D5_D6_CLK);
    // set in path digital gain,analog gain does not work, must be set before audio_init(),;
    audio_set_codec_in_path_a_d_gain(CODEC_IN_D_GAIN_12_DB, CODEC_IN_A_GAIN_0_DB);
    audio_init(DMIC_IN_TO_BUF, MIC_SAMPLING_RATE, MIC_MONO_STEREO);
    audio_rx_dma_chain_init(MIC_DMA_CHN, (unsigned short *)&iso_in_buff, MIC_BUFFER_SIZE * 2);
        #elif (AUDIO_IN_MODE == AUDIO_AMIC_IN)
    // set in path digital and analog gain, must be set before audio_init();
    audio_set_codec_in_path_a_d_gain(CODEC_IN_D_GAIN_12_DB, CODEC_IN_A_GAIN_20_DB);
    audio_init(AMIC_IN_TO_BUF, MIC_SAMPLING_RATE, MIC_MONO_STEREO);
    audio_rx_dma_chain_init(MIC_DMA_CHN, (unsigned short *)&iso_in_buff, MIC_BUFFER_SIZE * 2);
        #endif
}

void main_loop(void)
{
    usb_handle_irq();
}

    #elif defined(MCU_CORE_B92)
        #define AUDIO_LINE_IN     0
        #define AUDIO_AMIC_IN     1
        #define AUDIO_DMIC0_IN    2
        #define DMIC0_DMIC1_IN    3
        #define AUDIO_0581_MIC_IN 4

        #define AUDIO_IN_MODE     AUDIO_DMIC0_IN
        #if (AUDIO_IN_MODE == AUDIO_0581_MIC_IN)
unsigned short audio_i2s_16k_config[5] = {8, 125, 6, 64, 64}; /* sampling rate = 192M * (8 / 125) / (2 * 6) / 64   = 16K */
unsigned short audio_i2s_48k_config[5] = {2, 125, 0, 64, 64}; /* sampling rate = 192M * (2 / 125) / 64             = 48K */
        #endif
        #if (AUDIO_IN_MODE == AUDIO_0581_MIC_IN)
            #define CODEC_ADC_CHNL0    0
            #define CODEC_ADC_CHNL1    1
            #define CODEC_ADC_CHNL2    2

            #define CODEC_ADC_CHNL_SEL CODEC_ADC_CHNL0
        #endif

        #if (AUDIO_IN_MODE == DMIC0_DMIC1_IN)
            #define TX_DATA_FOR_DMIC0 0 //The data of DMIC0 and DMIC1 are stored in one buff,only process DMIC0  data( the second 4bytes in the buff).
            #define TX_DATA_FOR_DMIC1 1 //The data of DMIC0 and DMIC1 are stored in one buff,only process DMIC1 data( the first 4bytes in the buff).

            #define USB_TX_MODE       TX_DATA_FOR_DMIC0
        #endif


volatile unsigned int iso_in_r   = 0;
unsigned int          num_iso_in = 0;
        /**
 * @brief     This function serves to send data to USB. only adaptive mono 16bit
 * @param[in] audio_rate - audio rate. This value is matched with usb_default.h :MIC_SAMPLE_RATE.
 * @return    none.
 */
        #if (USB_MODE == INT)
void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned char length = 0;
    usbhw_reset_ep_ptr(USB_EDP_MIC); //reset pointer of Endpoint7's buf
    switch (audio_rate) {
    case AUDIO_8K:
        length = 8 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_16K:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_32K:
        length = 32 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_48K:
        length = 48 * MIC_CHANNEL_COUNT;
        break;
    default:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    }

            #if ((AUDIO_IN_MODE == DMIC0_DMIC1_IN) && (USB_TX_MODE == TX_DATA_FOR_DMIC1)) //process DMIC1 data
    for (unsigned char i = 0; i < length; i++) {
        short md = 0;
        if (((i & 0x01) == 0)) {
            if (iso_in_r == 0) {
                iso_in_r = 0;
            } else {
                iso_in_r = iso_in_r + 3;
            }

        } else {
            iso_in_r = iso_in_r + 1;
        }
        md              = iso_in_buff[(iso_in_r) & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }

            #elif (AUDIO_IN_MODE == DMIC0_DMIC1_IN && (USB_TX_MODE == TX_DATA_FOR_DMIC0)) //process DMIC0 data

    for (unsigned char i = 0; i < length; i++) {
        short md = 0;
        if (((i & 0x01) == 0)) {
            if (iso_in_r == 0) {
                iso_in_r = 2;
            } else {
                iso_in_r = iso_in_r + 3;
            }

        } else {
            iso_in_r = iso_in_r + 1;
        }
        md = iso_in_buff[(iso_in_r) & (MIC_BUFFER_SIZE - 1)];

        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }


            #else
                #if (MIC_RESOLUTION_BIT == 24)
    for (unsigned char i = 0; i < length; i++) {
        int md          = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
        reg_usb_ep7_dat = md >> 16;
    }
                #elif (MIC_RESOLUTION_BIT == 16)
    for (unsigned char i = 0; i < length; i++) {
        short md        = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }
                #endif
            #endif
    usbhw_data_ep_ack(USB_EDP_MIC);
}

/**
 * @brief       This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_noinline_ void usb_endpoint_irq_handler(void)
{
    if (usbhw_get_eps_irq() & FLD_USB_EDP7_IRQ) {
        usbhw_clr_eps_irq(FLD_USB_EDP7_IRQ);
        ; //clear interrupt flag of endpoint 7
        /////// get MIC input data ///////////////////////////////
        audio_tx_data_to_usb(MIC_SAMPLING_RATE);
        num_iso_in++;
        if ((num_iso_in & 0x7f) == 0) {
            gpio_toggle(LED2);
        }
    }
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)

        #endif


        #define AUDIO_BUFF_SIZE 4096
signed short AUDIO_BUFF[AUDIO_BUFF_SIZE >> 1] __attribute__((aligned(4)));

void user_init(void)
{
    usbhw_set_ep_addr(USB_EDP7_IN, 0x00);
    usbhw_set_eps_max_size(192); /* max 192 */

    gpio_function_en(LED1);
    gpio_output_en(LED1);

    //enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
    usb_init();
    /* enable data endpoint USB_EDP7_IN. */
    usbhw_set_eps_en(BIT(USB_EDP7_IN));
        #if (USB_MODE == INT)
            #define FIFO_NUM    FIFO0
            #define MIC_DMA_CHN DMA2

    //enable global interrupt
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB_ENDPOINT); // enable usb endpoint interrupt
    usbhw_set_eps_irq_mask(FLD_USB_EDP7_IRQ);
    //enable USB DP pull up 1.5k
    usb_set_pin(1);

            #if (AUDIO_IN_MODE == AUDIO_LINE_IN)
    audio_codec_stream0_input_t audio_codec_input =
        {
            .input_src     = LINE_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_init();
    audio_codec_stream0_input_init(&audio_codec_input);
    audio_rx_dma_chain_init(audio_codec_input.fifo_num, audio_codec_input.dma_num, (unsigned short *)audio_codec_input.data_buf, audio_codec_input.data_buf_size);
    audio_rx_dma_en(audio_codec_input.dma_num);
            #elif (AUDIO_IN_MODE == AUDIO_AMIC_IN)
    audio_codec_stream0_input_t audio_codec_input =
        {
            .input_src     = AMIC_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_init();
    audio_codec_stream0_input_init(&audio_codec_input);
    audio_set_stream0_dig_gain1(CODEC_IN_D_GAIN1_30_DB);
    audio_rx_dma_chain_init(audio_codec_input.fifo_num, audio_codec_input.dma_num, (unsigned short *)audio_codec_input.data_buf, audio_codec_input.data_buf_size);
    audio_rx_dma_en(audio_codec_input.dma_num);

            #elif (AUDIO_IN_MODE == AUDIO_DMIC0_IN)
    audio_codec_stream0_input_t audio_codec_dmic0_input =
        {
            .input_src     = DMIC_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO0,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    /****dmic input ****/
    audio_codec_init();
    audio_set_stream0_dmic_pin(GPIO_FC_PD5, GPIO_FC_PD4, GPIO_FC_PD3);
    audio_codec_stream0_input_init(&audio_codec_dmic0_input);
    audio_set_stream0_dig_gain1(CODEC_IN_D_GAIN1_30_DB);
    audio_rx_dma_chain_init(audio_codec_dmic0_input.fifo_num, audio_codec_dmic0_input.dma_num, (unsigned short *)audio_codec_dmic0_input.data_buf, audio_codec_dmic0_input.data_buf_size);
    audio_rx_dma_en(audio_codec_dmic0_input.dma_num);
            #elif (AUDIO_IN_MODE == DMIC0_DMIC1_IN)
    audio_codec_stream0_input_t audio_codec_dmic0_input =
        {
            .input_src     = DMIC_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA, //must 16 bit
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_stream1_input_t audio_codec_dmic1_input =
        {
            .input_src     = DMIC_STREAM0_STREAM1_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA, //must 16 bit
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };

    audio_codec_init();
    audio_set_stream0_dmic_pin(GPIO_FC_PD5, GPIO_FC_PD4, GPIO_FC_PD3);
    audio_set_stream1_dmic_pin(GPIO_FC_PD2, GPIO_FC_PD7, GPIO_FC_PD6);
    audio_codec_stream0_input_init(&audio_codec_dmic0_input);
    audio_codec_stream1_input_init(&audio_codec_dmic1_input);
    audio_set_stream0_dig_gain1(CODEC_IN_D_GAIN1_30_DB);
    audio_set_stream1_dig_gain(CODEC_IN_D_GAIN1_30_DB);
    audio_rx_dma_chain_init(audio_codec_dmic1_input.fifo_num, audio_codec_dmic1_input.dma_num, (unsigned short *)audio_codec_dmic1_input.data_buf, audio_codec_dmic1_input.data_buf_size);
    audio_rx_dma_en(MIC_DMA_CHN);
            #elif (AUDIO_IN_MODE == AUDIO_0581_MIC_IN)
    /* i2s config */
    codec_0581_i2s_init_t i2s_init = {
                #if (MIC_RESOLUTION_BIT == 16)
        .data_width = I2S_BIT_16_DATA,
                #elif (MIC_RESOLUTION_BIT == 24)
        .data_width = I2S_BIT_24_DATA,
                #endif

                #if (MIC_SAMPLE_RATE == 16000)
        .sample_rate = audio_i2s_16k_config,
                #elif (MIC_SAMPLE_RATE == 48000)
        .sample_rate = audio_i2s_48k_config,
                #endif
    };

    /* i2s input config */
    codec_0581_i2s_input_t i2s_input = {
        .i2s_ch_sel     = I2S_MONO,
        .rx_dma_num     = MIC_DMA_CHN,
        .input_data_buf = iso_in_buff,
        .input_buf_size = sizeof(iso_in_buff),
    };

    /* init i2s */
    codec_0581_i2s_init(&i2s_init, &i2s_input, 0);

    /* init codec_0581 */
    if (CODEC_0581_OK != codec_0581_init()) {
        return;
    }

    /**** input path: adc -> asrco -> sap/i2s ****/

    codec_0581_input_adc_config_t codec_0581_adc_config = {
                #if (CODEC_ADC_CHNL_SEL == COEDC_ADC_CHNL0)
        .adc_chnl = CODEC_ADC_CHNL_0,
                #elif (CODEC_ADC_CHNL_SEL == CODEC_ADC_CHNL1)
        .adc_chnl = CODEC_ADC_CHNL_1,
                #elif (CODEC_ADC_CHNL_SEL == CODEC_ADC_CHNL2)
        .adc_chnl = CODEC_ADC_CHNL_2,
                #endif
        .adc_rate = CODEC_ADC_SAMPLE_RATE_48KHz,
    };

    /* asrco */
    codec_0581_input_asrco_config_t codec_0581_asrco_config = {
        .asrco_in_fs = CODEC_ASRC_FS_48K,
        .asrco_chnl  = CODEC_ASRCO_CHNL_0,
                #if (CODEC_ADC_CHNL_SEL == CODEC_ADC_CHNL0)
        .asrco_route_from = CODEC_ASRCO_ROUTE_ADC0,
                #elif (CODEC_ADC_CHNL_SEL == CODEC_ADC_CHNL1)
        .asrco_route_from = CODEC_ASRCO_ROUTE_ADC1,
                #elif (CODEC_ADC_CHNL_SEL == CODEC_ADC_CHNL2)
        .asrco_route_from = CODEC_ASRCO_ROUTE_ADC2,
                #endif
    };

    /* sap */
    codec_0581_input_sap_config_t codec_0581_sap_config = {
        .slot_id        = CODEC_SAP_SLOT1_RIGHT, /* The i2s channel is mono, it must be CODEC_SAP_SLOT1_RIGHT. */
        .sap_route_from = CODEC_SAP_OUT_ROUTE_FROM_ASRCO0,
    };
    /* input config */
    codec_0581_input_t codec_0581_input_config = {
        .adc_config   = &codec_0581_adc_config,
        .asrco_config = &codec_0581_asrco_config,
        .fdec_config  = 0, /* this example fdec not used */
        .sap_config   = &codec_0581_sap_config,
    };

    /**** codec_0581 input path init ****/
    codec_0581_input_init(&codec_0581_input_config);

    /* enable rx dma */
    audio_rx_dma_en(i2s_input.rx_dma_num);
            #endif
        #elif (USB_MODE == AISO)
            #define FIFO_NUM     FIFO0
            #define MIC_DMA_CHN  DMA2
            #define AISO_DMA_CHN DMA3
            #if (AUDIO_IN_MODE == AUDIO_LINE_IN)
    audio_codec_stream0_input_t audio_codec_input =
        {
            .input_src     = LINE_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_init();
    audio_codec_stream0_input_init(&audio_codec_input);
    audio_rx_dma_chain_init(audio_codec_input.fifo_num, audio_codec_input.dma_num, (unsigned short *)audio_codec_input.data_buf, audio_codec_input.data_buf_size);
            #elif (AUDIO_IN_MODE == AUDIO_AMIC_IN)
    audio_codec_stream0_input_t audio_codec_input =
        {
            .input_src     = AMIC_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_init();
    audio_codec_stream0_input_init(&audio_codec_input);
    audio_set_stream0_dig_gain1(CODEC_IN_D_GAIN1_30_DB);
    audio_rx_dma_chain_init(audio_codec_input.fifo_num, audio_codec_input.dma_num, (unsigned short *)audio_codec_input.data_buf, audio_codec_input.data_buf_size);
            #elif (AUDIO_IN_MODE == AUDIO_DMIC0_IN)
    audio_codec_stream0_input_t audio_codec_dmic0_input =
        {
            .input_src     = DMIC_STREAM0_STEREO,
            .sample_rate   = MIC_SAMPLING_RATE,
            .fifo_num      = FIFO_NUM,
            .data_width    = CODEC_BIT_16_DATA,
            .dma_num       = MIC_DMA_CHN,
            .data_buf      = iso_in_buff,
            .data_buf_size = sizeof(iso_in_buff),
        };
    audio_codec_init();
    audio_set_stream0_dmic_pin(GPIO_FC_PD5, GPIO_FC_PD4, GPIO_FC_PD3);
    audio_codec_stream0_input_init(&audio_codec_dmic0_input);
    audio_set_stream0_dig_gain1(CODEC_IN_D_GAIN1_30_DB);
    audio_rx_dma_chain_init(audio_codec_dmic0_input.fifo_num, audio_codec_dmic0_input.dma_num, (unsigned short *)audio_codec_dmic0_input.data_buf, audio_codec_dmic0_input.data_buf_size);
            #endif
    audio_data_fifo_output_path_sel(FIFO_NUM, USB_AISO_OUT_FIFO);
    audio_tx_dma_chain_init(FIFO_NUM, AISO_DMA_CHN, (unsigned short *)iso_in_buff, MIC_BUFFER_SIZE * 2);
    audio_rx_dma_en(MIC_DMA_CHN);
    audio_tx_dma_en(AISO_DMA_CHN);
        #endif
}

unsigned int t1 = 0;

void main_loop(void)
{
        /**
     * @attention   When using the vbus (not vbat) power supply, you must turn off the vbus timer,
     *              otherwise the MCU will be reset after 8s.
    */
        #if (POWER_SUPPLY_MODE == VBUS_POWER_SUPPLY)
    /**
     *When using the vbus (not vbat) power supply, the vbus detect status remains at 1. Conversely, it is 0.
     */
    if (usb_get_vbus_detect_status()) {
        if (clock_time_exceed(g_vbus_timer_turn_off_start_tick, 100 * 1000) && (g_vbus_timer_turn_off_flag == 0)) {
            /**
         * wd_turn_off_vbus_timer() is used to turn off the 8s vbus timer.
         * The vbus detect status will not be clear to 0.
         */
            wd_turn_off_vbus_timer();
            g_vbus_timer_turn_off_flag = 1;
        }
    } else {
        g_vbus_timer_turn_off_start_tick = stimer_get_tick();
        g_vbus_timer_turn_off_flag       = 0;
    }
        #endif
    usb_handle_irq();

    if (clock_time_exceed(t1, 500000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LED1);
    }
}
    #elif defined(MCU_CORE_TL7518)
static volatile unsigned int iso_in_r   = 0;
static volatile unsigned int num_iso_in = 0;

        #if (USB_MODE == INT)

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned char length = 0;
    usbhw_reset_ep_ptr(USB_EDP_MIC); // reset pointer of Endpoint7's buf
    switch (audio_rate) {
    case AUDIO_16K:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_48K:
        length = 48 * MIC_CHANNEL_COUNT;
        break;
    default:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    }

    for (unsigned char i = 0; i < length; i++) {
        short md        = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }

    usbhw_data_ep_ack(USB_EDP_MIC);
}

/**
 * @brief       This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_noinline_ void usb_endpoint_irq_handler(void)
{
    if (usbhw_get_eps_irq() & BIT(USB_EDP_MIC)) {
        /* clear interrupt flag of endpoint 7 */
        usbhw_clr_eps_irq(BIT(USB_EDP_MIC));
        /* get MIC input data */
        audio_tx_data_to_usb(MIC_SAMPLING_RATE);
        num_iso_in++;
        if ((num_iso_in & 0x7f) == 0) {
            gpio_toggle(LED2);
        }
    }
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)
        #endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);

    /* enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device) */
    usb_init();
    /* enable data endpoint USB_EDP_MIC. */
    usbhw_set_eps_en(BIT(USB_EDP_MIC));

    /* enable global interrupt */
    core_interrupt_enable();

    /* set data endpoint buffer size and addr */
    usbhw_set_eps_max_size(192); /* max 192 */
    usbhw_set_ep_addr(USB_EDP_MIC, 0x00);

    /* enable usb endpoint interrupt */
    usbhw_set_eps_irq_mask(BIT(USB_EDP_MIC));
    plic_interrupt_enable(IRQ_USB_ENDPOINT);

    /* enable USB DP pull up 1.5k */
    usb_set_pin(1);
}

static unsigned int t1 = 0;

void main_loop(void)
{
    usb_handle_irq();
    if (clock_time_exceed(t1, 500000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LED1);
    }
}
    #elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
static volatile unsigned int iso_in_r   = 0;
static volatile unsigned int num_iso_in = 0;

        #if (USB_MODE == INT)

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned short length = 0;
    usbhw_reset_ep_ptr(USB_EDP_MIC); // reset pointer of Endpoint7's buf
    switch (audio_rate) {
    case AUDIO_16K:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_32K:
        length = 32 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_48K:
        length = 48 * MIC_CHANNEL_COUNT;
        break;
    default:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    }

    for (unsigned short i = 0; i < length; i++) {
        short md        = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }

    usbhw_data_ep_ack(USB_EDP_MIC);
}

/**
 * @brief       This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_noinline_ void usb_endpoint_irq_handler(void)
{
    if (usbhw_get_eps_irq() & BIT(USB_EDP_MIC)) {
        /* clear interrupt flag of endpoint 7 */
        usbhw_clr_eps_irq(BIT(USB_EDP_MIC));
        /* get MIC input data */
        audio_tx_data_to_usb(MIC_SAMPLING_RATE);
        num_iso_in++;
        if ((num_iso_in & 0x7f) == 0) {
            gpio_toggle(LED2);
        }
    }
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)
        #endif


        #define DATA_WIDTH  CODEC_BIT_16_DATA
        #define RX_FIFO_NUM FIFO0
        #define RX_DMA_CHN  DMA0

        #define INPUT_SRC   (MIC_CHANNEL_COUNT == 2) ? DMIC_STREAM0_STEREO : DMIC_STREAM0_MONO_L

audio_codec_stream0_input_t audio_codec_stream0_input =
    {
        .input_src     = INPUT_SRC,
        .sample_rate   = MIC_SAMPLING_RATE,
        .data_width    = DATA_WIDTH,
        .fifo_chn      = RX_FIFO_NUM,
        .dma_num       = RX_DMA_CHN,
        .data_buf      = iso_in_buff,
        .data_buf_size = sizeof(iso_in_buff),
};

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    /****audio init start****/
    audio_init();
    audio_set_stream0_dmic_pin(GPIO_FC_PA2, GPIO_FC_PA3, GPIO_FC_PA4); //only for dmic input
    audio_codec_stream0_input_init(&audio_codec_stream0_input);
    audio_set_stream0_dig_gain(CODEC_IN_D_GAIN_12_DB);
    /****rx tx dma init****/
    audio_rx_dma_chain_init(audio_codec_stream0_input.fifo_chn, audio_codec_stream0_input.dma_num, (unsigned short *)audio_codec_stream0_input.data_buf, audio_codec_stream0_input.data_buf_size);

    audio_codec_stream0_input_en(audio_codec_stream0_input.dma_num);
    audio_codec_input_path_en(audio_codec_stream0_input.fifo_chn);
    /****audio init end ****/
    /* enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device) */
    usb_init();
    /* enable data endpoint USB_EDP_MIC. */
    usbhw_set_eps_en(BIT(USB_EDP_MIC));

    /* enable global interrupt */
    core_interrupt_enable();

    /* set data endpoint buffer size and addr */
    usbhw_set_eps_max_size(192); /* max 192 */
    usbhw_set_ep_addr(USB_EDP_MIC, 0x00);

    /* enable usb endpoint interrupt */
    usbhw_set_eps_irq_mask(BIT(USB_EDP_MIC));
    plic_interrupt_enable(IRQ_USB_ENDPOINT);

        #if (USB_ENUM_IN_INTERRUPT == 1)
    /* enable set intf irq */
    usbhw_set_irq_mask(USB_IRQ_SETINF_MASK);
    plic_interrupt_enable(IRQ_USB_CTRL_EP_SETINF);
        #endif

    /* enable USB DP pull up 1.5k */
    usb_set_pin(1);
}

static unsigned int t1 = 0;

void main_loop(void)
{
    usb_handle_irq();
    if (clock_time_exceed(t1, 500000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LED1);
    }
}

    #elif (defined(MCU_CORE_TL751X)) || (defined(MCU_CORE_TL7518))
static volatile unsigned int iso_in_r   = 0;
static volatile unsigned int num_iso_in = 0;

        #if (USB_MODE == INT)

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned short length = 0;
    usbhw_reset_ep_ptr(USB_EDP_MIC); // reset pointer of Endpoint7's buf
    switch (audio_rate) {
    case AUDIO_16K:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_48K:
        length = 48 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_96K:
        length = 96 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_192K:
        length = 192 * MIC_CHANNEL_COUNT;
        break;
    case AUDIO_384K:
        length = 384 * MIC_CHANNEL_COUNT; // only support 1 channel because of usb FS bandwidth limit
        break;
    default:
        length = 16 * MIC_CHANNEL_COUNT;
        break;
    }

    for (unsigned short i = 0; i < length; i++) {
        short md        = iso_in_buff[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }

    usbhw_data_ep_ack(USB_EDP_MIC);
}

/**
 * @brief       This function serves to handle  iso in usb endpoint interrupt ,interval is 1 ms
 * @param[in]   none
 * @return      none
 */
_attribute_ram_code_sec_noinline_ void usb_endpoint_irq_handler(void)
{
    if (usbhw_get_eps_irq() & BIT(USB_EDP_MIC)) {
        /* clear interrupt flag of endpoint 7 */
        usbhw_clr_eps_irq(BIT(USB_EDP_MIC));
        /* get MIC input data */
        audio_tx_data_to_usb(MIC_SAMPLING_RATE);
        num_iso_in++;
        if ((num_iso_in & 0x7f) == 0) {
            gpio_toggle(LED2);
        }
    }
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)
        #endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);

    /* enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device) */
    usb_init();
    /* enable data endpoint USB_EDP_MIC. */
    usbhw_set_eps_en(BIT(USB_EDP_MIC));

    /* enable global interrupt */
    core_interrupt_enable();

    /* set data endpoint buffer size and addr */
    usbhw_set_eps_max_size(384 * 2);
    usbhw_set_ep_addr(USB_EDP_MIC, 0x00);

    /* enable usb endpoint interrupt */
    usbhw_set_eps_irq_mask(BIT(USB_EDP_MIC));
    plic_interrupt_enable(IRQ_USB_ENDPOINT);

    clock_pll_audio_init(PLL_AUDIO_CLK_36P864M);
    audio_init(PLL_AUDIO_CLK_36P864M);                               /* must configured first. */

    audio_codec0_power_on(AUDIO_CODEC0_ADC_ONLY, AUDIO_CODEC0_1P8V); /* power on adc and dac. */

    /*********************** input config ****************************/
    audio_codec0_input_config_t codec0_input_config = {
        .input_src   = AUDIO_LINEIN_ADC_A1,
        .data_format = AUDIO_CODEC0_BIT_16_DATA,
        .sample_rate = MIC_SAMPLING_RATE,
    };
    /* matrix input config. */
    audio_matrix_set_rx_fifo_route(FIFO0, FIFO_RX_ROUTE_CODEC0_ADCA, FIFO_RX_CODEC0_ADCA_A1_16BIT);
    audio_codec0_input_init(&codec0_input_config);
    /* rx dma init. */
    audio_rx_dma_chain_init(FIFO0, DMA0, (unsigned short *)iso_in_buff, sizeof(iso_in_buff));
    audio_rx_dma_en(DMA0);
        #if (USB_ENUM_IN_INTERRUPT == 1)
    /* enable set intf irq */
    usbhw_set_irq_mask(USB_IRQ_SETINF_MASK);
    plic_interrupt_enable(IRQ_USB_CTRL_EP_SETINF);
        #endif

    /* enable USB DP pull up 1.5k */
    usb_set_pin(1);
}

static unsigned int t1 = 0;

void main_loop(void)
{
    usb_handle_irq();
    if (clock_time_exceed(t1, 500000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LED1);
    }
}
    #endif
#endif

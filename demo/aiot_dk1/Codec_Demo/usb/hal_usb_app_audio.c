/********************************************************************************************************
 * @file    hal_usb_app_audio.c
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
#include "common.h"
#include "../common/usb_dbg/debug_vcd.h"
#include "../log.h"
#include "bit.h"
#include "hal_usb_app_audio.h"
#include "../i2s/hal_i2s.h"

const signed short volume_relative_table_iphone[67] = {0xa000, 0xa180, 0xa300, 0xa480, 0xa600, 0xa780, 0xa900, 0xaa80, 0xac00, 0xad80, 0xaf00, 0xb080, 0xb200, 0xb380,
                                               0xb500, 0xb680, 0xb800, 0xb980, 0xbb00, 0xbc80, 0xbe00, 0xbf80, 0xc100, 0xc280, 0xc400, 0xc580, 0xc700, 0xc880,
                                               0xca00, 0xcb80, 0xcd00, 0xce80, 0xd000, 0xd180, 0xd300, 0xd480, 0xd600, 0xd780, 0xd900, 0xda80, 0xdc00, 0xdd80,
                                               0xdf00, 0xe080, 0xe200, 0xe380, 0xe500, 0xe680, 0xe800, 0xe980, 0xeb00, 0xec80, 0xee00, 0xef80, 0xf100, 0xf280,
                                               0xf400, 0xf580, 0xf700, 0xf880, 0xfa00, 0xfb80, 0xfd00, 0xfe80, 0x0000, 0x0180, 0x3000};

const signed short volume_relative_value_table[101] = {
    0xa000, 0xbea8, 0xc825, 0xcdf1, 0xd221, 0xd568, 0xd8a1, 0xda64, 0xdc61, 0xde23, 0xdfb7, 0xe124, 0xe273, 0xe3a6, 0xe4c3, 0xe5cd, 0xe6c6, 0xe7af, 0xe88c, 0xe95d, 0xea23,
    0xeadf, 0xeb93, 0xec3f, 0xece3, 0xed81, 0xee19, 0xeeab, 0xef37, 0xefbf, 0xf043, 0xf0c1, 0xf13c, 0xf1b4, 0xf227, 0xf298, 0xf305, 0xf36f, 0xf3d6, 0xf43b, 0xf49d, 0xf4fd,
    0xf55a, 0xf5b5, 0xf60f, 0xf666, 0xf6bb, 0xf70e, 0xf760, 0xf7b0, 0xf7fe, 0xf84b, 0xf897, 0xf8e0, 0xf929, 0xf970, 0xf9b6, 0xf9fb, 0xfa3e, 0xfa81, 0xfac2, 0xfb02, 0xfb41,
    0xfb7f, 0xfbbc, 0xfbf9, 0xfc34, 0xfc6e, 0xfca8, 0xfce0, 0xfd18, 0xfd4f, 0xfd86, 0xfdbb, 0xfdf0, 0xfe24, 0xfe58, 0xfe8a, 0xfebc, 0xfeee, 0xff1f, 0xff4f, 0xff7f, 0xffae,
    0xffdc, 0x0009, 0x0037, 0x0066, 0x0096, 0x00c5, 0x00f6, 0x0127, 0x0159, 0x018b, 0x01be, 0x01f2, 0x0226, 0x025c, 0x0291, 0x02c8, 0x0300};

const unsigned short volume_scale_table[101] = {
    0,    18,   55,   92,   110,  130,  164,   201,   220,   251,   284,   320,   360,   400,   470,   520,   600,   680,   746,   902,   1050,  1270,  1380, 1430, 1486, 1542,
    1590, 1645, 1695, 1752, 1810, 1860, 1905,  1940,  1981,  2083,  2185,  2288,  2390,  2493,  2596,  2697,  2799,  2902,  3009,  3112,  3215,  3385,  3556, 3726, 3896, 4066,
    4237, 4407, 4578, 4748, 4918, 5081, 5268,  5439,  5609,  5780,  5952,  6120,  6281,  6473,  6667,  6860,  7053,  7246,  7439,  7633,  7826,  8020,  8214, 8408, 8600, 8766,
    8923, 9088, 9245, 9421, 9600, 9926, 10253, 10579, 10907, 11213, 11550, 11826, 12153, 12906, 13449, 14109, 14973, 15920, 15966, 16105, 16196, 16278, 16384};

const unsigned short volume_scale_iphone_table[67] = {0,    55,   58,   62,   69,   78,   87,   98,   110,  123,   138,   155,   174,   195,   218,   245,  260,
                                              275,  291,  309,  346,  389,  436,  489,  549,  581,  615,   652,   732,   691,   775,   821,   870,  921,
                                              976,  1034, 1095, 1160, 1229, 1301, 1379, 1460, 1547, 1638,  1756,  2597,  2751,  2913,  3086,  3463, 3841,
                                              4115, 4559, 4918, 5681, 6523, 7318, 7752, 8403, 9213, 10338, 11599, 12428, 13785, 14062, 15467, 16384};



hal_usb_app_audio_ctx_t *usb_app_audio_ctx = NULL;

static void usb_data_reset_handler(void)
{
    usb_app_audio_ctx->iso_out_w  = 0;
    usb_app_audio_ctx->iso_out_r  = 0;
    usb_app_audio_ctx->paly_out_w = 0;
    for (int i = 0; i < usb_app_audio_ctx->spk_buffer_size; i++) {
        usb_app_audio_ctx->codec_buf_spk[i]      = 0;
        usb_app_audio_ctx->codec_play_buf_spk[i] = 0;
    }
}

#if defined(MCU_CORE_TL322X)

#include "tl_usb/class/audio/usbd_audio.h"
#include "../application/usb_app/audio_spk_descriptor.h"

static usbd_driver_t usbd_spk_driver;

typedef struct {
    uint8_t  mute;
    int16_t cur;
    int16_t min;
    int16_t max;
    uint16_t res;
}audio_ctx_t;


#define MIC_VOL_MIN           ((signed short)0x0000) /* Volume Minimum Value */
#define MIC_VOL_MAX           ((signed short)0x1e00) /* Volume Maximum Value */
#define MIC_VOL_RES           0x0180                 /* Volume Resolution */
#define MIC_VOL_DEF           0x1800                 /* Volume default */
#define MIC_MAX_STEP          (MIC_VOL_MAX / MIC_VOL_RES)

#define SPEAKER_VOL_MIN       ((signed short)0xa000) /* Volume Minimum Value */
#define SPEAKER_VOL_MAX       ((signed short)0x0300) /* Volume Maximum Value */
#define SPEAKER_VOL_RES       0x0180                 /* Volume Resolution */
#define SPEAKER_VOL_DEF       0x8000                 /* Volume default */
#define SPEAKER_VOL_STEP      400

static audio_ctx_t audio_speaker = {
    .mute = 0,
    .cur  = 0,
    .min  = SPEAKER_VOL_MIN,
    .max  = SPEAKER_VOL_MAX,
    .res  = SPEAKER_VOL_RES,
};
static audio_ctx_t audio_mic = {
    .mute = 0,
    .cur  = 0,
    .min  = MIC_VOL_MIN,
    .max  = MIC_VOL_MAX,
    .res  = MIC_VOL_RES,
};

static unsigned char  rw_buffer[AUDIO_SPK_OUT_ENDPOINT_SIZE] = {0};
static unsigned char  rw_buffer_mic[AUDIO_MIC_IN_ENDPOINT_SIZE] = {0};

static void set_codec_buf_spk(unsigned int len) {
    for (unsigned int k = 0; k < len; k += 4) {
        unsigned int dw = rw_buffer[k];
        dw |= rw_buffer[k+1] << 8;
        dw |= rw_buffer[k+2] << 16;
        dw |= rw_buffer[k+3] << 24;
        usb_app_audio_ctx->codec_buf_spk[usb_app_audio_ctx->iso_out_w++ & (usb_app_audio_ctx->spk_buffer_size - 1)] = dw;
    }
}

static unsigned int set_codec_buf_mic(unsigned int len) {
    usb_app_audio_ctx->iso_in_w             = ((audio_get_rx_dma_wptr(I2S_MIC_DMA) - (unsigned int)usb_app_audio_ctx->codec_buf_mic) >> 1);
    for (unsigned int i = 0; i < (len >> 1); i++) {
        if (audio_mic.mute) {
            rw_buffer_mic[i*2] = 0;
            rw_buffer_mic[i*2+1] = 0;
            continue;
        }

        short md        = (short)usb_app_audio_ctx->codec_buf_mic[usb_app_audio_ctx->iso_in_r++ & (usb_app_audio_ctx->mic_buffer_size - 1)];
        rw_buffer_mic[i*2] = md;
        rw_buffer_mic[i*2+1] = md >> 8;
    }

    return len;
}

void usbd_audio_open(unsigned char bus, unsigned char intf)
{
    (void)bus;
    (void)intf;
    switch (intf) {
    case 2: // speaker 
        usb_app_audio_ctx->usb_iso_out_en = 1;
        /* receive first spk out data. */
        usb_app_audio_ctx->first_play = 1;
        usbd_ep_read(bus, AUDIO_SPK_OUT_ENDPOINT_ADDRESS, rw_buffer, sizeof(rw_buffer));
        set_codec_buf_spk(sizeof(rw_buffer));
        break;
    case 1: // microphone
        usb_app_audio_ctx->usb_iso_in_en = 1;
        usb_app_audio_ctx->iso_in_r = audio_get_rx_dma_wptr(I2S_MIC_DMA) + 48 * 15;
        /* send first mic in data. */
        usbd_ep_write(bus, AUDIO_MIC_IN_ENDPOINT_ADDRESS, rw_buffer_mic, set_codec_buf_mic(sizeof(rw_buffer_mic)));
        break;
    default:
        break;
    }

}

void usbd_audio_close(unsigned char bus, unsigned char intf)
{
    (void)bus;
    (void)intf;
    switch (intf) {
    case 2: 
        usb_app_audio_ctx->usb_iso_out_en = 0;
        usb_data_reset_handler();
        break;
    case 1: 
        usb_app_audio_ctx->usb_iso_in_en = 0;
        usb_data_reset_handler();
        break;
    default:
        break;
    }

}

void usbd_audio_epout_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    
    /* receive spk out data. */
    usbd_ep_read(bus, ep_addr, rw_buffer, len);
    set_codec_buf_spk(len);
    usb_app_audio_ctx->usb_iso_cfg_tick_out = clock_time();
    
}

void usbd_audio_epin_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    len = set_codec_buf_mic(len);
    usbd_ep_write(bus, ep_addr, rw_buffer_mic, len);
}

bool audio_speaker_interface_proc(unsigned char bus, unsigned char control_selector, usb_control_request_t const *setup) {
    bool ret = true;
    do {
        if (control_selector == USB_AUDIO_FEATURE_UNIT_CTRL_MUTE) {
            switch (setup->bRequest) {
            case 0x81:
                usbd_ep_write(bus, 0, &audio_speaker.mute, setup->wLength);
                break;
            case 0x01:
                usbd_ep_read(bus, 0, (unsigned char *)&audio_speaker.mute, setup->wLength);
                break;
            default:
                ret = false;
                break;
            }
        } else if (control_selector == USB_AUDIO_FEATURE_UNIT_CTRL_VOLUME) {
            /* code */
            switch (setup->bRequest) {
            case 0x81:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_speaker.cur, setup->wLength);
                break;
            case 0x82:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_speaker.min, setup->wLength);
                break;
            case 0x83:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_speaker.max, setup->wLength);
                break;
            case 0x84:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_speaker.res, setup->wLength);
                break;
            case 0x01:
                usbd_ep_read(bus, 0, (unsigned char *)&audio_speaker.cur, setup->wLength);
                break;
            default:
                ret = false;
                break;
            }
        }

    } while(0);

    return ret;
}

bool audio_mic_interface_proc(unsigned char bus, unsigned char control_selector, usb_control_request_t const *setup) {
    bool ret = true;
    do {
        if (control_selector == USB_AUDIO_FEATURE_UNIT_CTRL_MUTE) {
            switch (setup->bRequest) {
            case 0x81:
                usbd_ep_write(bus, 0, &audio_mic.mute, setup->wLength);
                break;
            case 0x01:
                usbd_ep_read(bus, 0, (unsigned char *)&audio_mic.mute, setup->wLength);
                break;
            default:
                ret = false;
                break;
            }
        } else if (control_selector == USB_AUDIO_FEATURE_UNIT_CTRL_VOLUME) {
            /* code */
            switch (setup->bRequest) {
            case 0x81:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_mic.cur, setup->wLength);
                break;
            case 0x82:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_mic.min, setup->wLength);
                break;
            case 0x83:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_mic.max, setup->wLength);
                break;
            case 0x84:
                usbd_ep_write(bus, 0, (unsigned char *)&audio_mic.res, setup->wLength);
                break;
            case 0x01:
                usbd_ep_read(bus, 0, (unsigned char *)&audio_mic.cur, setup->wLength);
                break;
            default:
                ret = false;
                break;
            }
        }

    } while(0);

    return ret;
}

unsigned char usbd_audio_interface_cb(unsigned char bus, usb_control_request_t const *setup)
{
    (void)bus;
    (void)setup;
    unsigned char entity_id;
    unsigned char control_selector;
    unsigned char ret = true;

    control_selector = U16_HIGH_BYTE(setup->wValue);
    entity_id        = U16_HIGH_BYTE(setup->wIndex);
    switch (entity_id) {
    case 2:
        ret = audio_mic_interface_proc(bus, control_selector, setup);
        break;
    case 5:
        ret = audio_speaker_interface_proc(bus, control_selector, setup);
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

void hal_usb_app_audio_init(hal_usb_app_audio_ctx_t *ctx) {
    usb_app_audio_ctx = ctx;
    usbd_spk_driver.driver_num          = 0;
    usbd_spk_driver.usbd_driver_handler = usbd_audio_interface_request_handler;
    usbd_driver_register(0, &usbd_spk_driver, 0, 0xff);
    usbd_driver_register(0, &usbd_spk_driver, 1, AUDIO_MIC_IN_ENDPOINT_ADDRESS);
    usbd_driver_register(0, &usbd_spk_driver, 2, AUDIO_SPK_OUT_ENDPOINT_ADDRESS);
    usbd_endpoint_register(0, AUDIO_SPK_OUT_ENDPOINT_ADDRESS, usbd_audio_epout_callback);
    usbd_endpoint_register(0, AUDIO_MIC_IN_ENDPOINT_ADDRESS, usbd_audio_epin_callback);

    usb_data_reset_handler();

#if USB_HIGH_SPEED_EN
    usb0hw_init(USB0_SPEED_HIGH);
#else
    usb0hw_init(USB0_SPEED_FULL);
#endif
    usb0hw_set_grxfsiz(0x100);
    usb0hw_set_epin_size(USB0_EP0, 0x100, AUDIO_SPK_OUT_ENDPOINT_SIZE);
    usb0hw_set_epin_size(USB0_EP7, 0x100 + AUDIO_SPK_OUT_ENDPOINT_SIZE, AUDIO_MIC_IN_ENDPOINT_SIZE);

    plic_interrupt_enable(IRQ_USB0);
}


void hal_usb_app_audio_handle_loop(void) {

}

int16_t hal_usb_app_audio_get_curvol(void) {
    return audio_speaker.cur;
}

uint8_t hal_usb_app_audio_get_speaker_vol(void) {
    unsigned char vol_step = 0;
    if(audio_speaker.cur >= SPEAKER_VOL_MIN) {
        vol_step = (audio_speaker.cur - SPEAKER_VOL_MIN) / SPEAKER_VOL_RES;
    }
    return (audio_speaker.mute << 7) | (vol_step & 0x7f);
}


#else

#include "../application/usb_default.h"
#include "../application/usbstd/usb.h"
#include "../application/usb_app/usbaud.h"


void hal_usb_app_audio_init(hal_usb_app_audio_ctx_t *ctx)
{
    usb_app_audio_ctx = ctx;
    /* enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device) */
    usb_init();
    /* enable data endpoint USB_EDP_SPEAKER. */
    usbhw_set_eps_en(BIT(USB_EDP_SPEAKER) | BIT(USB_EDP_MIC));

    /* set data endpoint addr */
    usbhw_set_ep_addr(USB_EDP_SPEAKER, 0x00);
    usbhw_set_ep_addr(USB_EDP_MIC, 0xc0);

    usbhw_set_eps_max_size(192);

    /* enable usb endpoint interrupt */
    usbhw_set_eps_irq_mask(BIT(USB_EDP_SPEAKER));
    usbhw_set_eps_irq_mask(BIT(USB_EDP_MIC));
    plic_interrupt_enable(IRQ_USB_ENDPOINT);
    /* enable USB DP pull up 1.5k */
    usb_set_pin(1);

    usb_data_reset_handler();
}

/**
 * @brief     This function servers to set USB Input.
 * @param[in] none
 * @return    none.
 */
void audio_rx_data_from_usb(void)
{
    unsigned short len = reg_usb_ep6_ptr;
    usbhw_reset_ep_ptr(USB_EDP_SPEAKER);
    for (int k = 0; k < len; k += 4) {
        unsigned int dw = reg_usb_ep6_dat;
        dw |= reg_usb_ep6_dat << 8;
        dw |= reg_usb_ep6_dat << 16;
        dw |= reg_usb_ep6_dat << 24;
        usb_app_audio_ctx->codec_buf_spk[usb_app_audio_ctx->iso_out_w++ & (usb_app_audio_ctx->spk_buffer_size - 1)] = dw;
    }
    usbhw_data_ep_ack(USB_EDP_SPEAKER);
    if (len != 192) {
        PRINTK("usb data len error %d \r\n", len);
    }
}

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned char length = 0;
    usb_app_audio_ctx->iso_in_w             = ((audio_get_rx_dma_wptr(I2S_MIC_DMA) - (unsigned int)usb_app_audio_ctx->codec_buf_mic) >> 1);
    usbhw_reset_ep_ptr(USB_EDP_MIC); //reset pointer of Endpoint7's buf

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
    for (unsigned char i = 0; i < length && usb_app_audio_ctx->iso_in_r != usb_app_audio_ctx->iso_in_w; i++) {
        short md        = (short)usb_app_audio_ctx->codec_buf_mic[usb_app_audio_ctx->iso_in_r++ & (usb_app_audio_ctx->mic_buffer_size - 1)];
        reg_usb_ep7_dat = md;
        reg_usb_ep7_dat = md >> 8;
    }
    usbhw_data_ep_ack(USB_EDP_MIC);
}

_attribute_ram_code_sec_ void usb_endpoint_irq_handler(void)
{
    /////////////////////////////////////
    // ISO OUT
    /////////////////////////////////////
    if (usbhw_get_eps_irq() & BIT(USB_EDP_SPEAKER)) {
        usbhw_clr_eps_irq(BIT(USB_EDP_SPEAKER));
        ///////////// output to audio fifo out ////////////////
        audio_rx_data_from_usb();

        usb_app_audio_ctx->usb_iso_cfg_tick_out = clock_time();
    }
    /////////////////////////////////////
    // ISO INT
    /////////////////////////////////////
    if (usbhw_get_eps_irq() & BIT(USB_EDP_MIC)) {
        usbhw_clr_eps_irq(BIT(USB_EDP_MIC));
        ///////////// input to audio fifo int ////////////////
        audio_tx_data_to_usb(AUDIO_48K);
        usb_app_audio_ctx->num_iso_out++;
        if ((usb_app_audio_ctx->num_iso_out & 0x7f) == 0) {
            // gpio_toggle(LEDTEST2);
        }
    }
}

PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)

void app_usb_handle_set_intf(int intf, int alt)
{
    /////////  SPEAKER/////////////////
    if (intf == 1) {
        if (!alt) {
            usb_app_audio_ctx->usb_iso_out_en = 0;
            usb_data_reset_handler();
        } else {
            usb_app_audio_ctx->usb_iso_out_en = 1;
        }
        PRINTK("usb_iso_out_en %d \r\n", usb_app_audio_ctx->usb_iso_out_en);
    }
    /////////  MIC /////////////////
    if (intf == 2) {
        if (!alt) {
            usb_app_audio_ctx->usb_iso_in_en = 0;
        } else {
            usb_app_audio_ctx->usb_iso_in_en = 1;
        }
        PRINTK("usb_iso_in_en %d \r\n", usb_app_audio_ctx->usb_iso_in_en);
    }
}

void hal_usb_app_audio_handle_loop(void)
{
    usb_handle_irq();
}

int16_t hal_usb_app_audio_get_curvol(void) {
    return (int16_t)usbaud_speaker_curvol_get();
}


uint8_t hal_usb_app_audio_get_speaker_vol(void) {
    return usbaud_speaker_vol_get();
}

#endif

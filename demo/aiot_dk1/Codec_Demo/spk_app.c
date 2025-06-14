/********************************************************************************************************
 * @file    spk_app.c
 *
 * @brief   This is the header file for TL7518/TL721X/TL321X
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
#include "i2c/hal_i2c.h"
#include "i2c/hal_es8389.h"
#include "i2c/hal_nau8821.h"
#include "i2s/hal_i2s.h"
#include "log.h"
#include "../common/usb_dbg/debug_vcd.h"

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB || AUDIO_MODE == I2S_TO_EXT_CODEC_MIC_SPK)
#include "usb_default.h"
#include "application/usbstd/usb.h"
#include "application/usb_app/usbaud.h"

#define SPK_BUFFER_SIZE 1024
#define MIC_BUFFER_SIZE 1024

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
static sa_dac_t codec_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));
#endif
static sa_adc_t codec_buf_mic[MIC_BUFFER_SIZE] __attribute__((aligned(4)));
static sa_dac_t codec_play_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));

unsigned int usb_iso_cfg_tick_out = 0;
int          usb_iso_out_en       = 0;
int          usb_iso_in_en        = 0;

static unsigned int          t1        = 0;
static volatile unsigned int iso_out_w = 0;
static volatile unsigned int iso_out_r = 0;

volatile unsigned int iso_in_w = 0;
volatile unsigned int iso_in_r = 0;

volatile unsigned int        paly_out_w  = 0;
volatile unsigned int        paly_in_w   = 0;
static volatile unsigned int num_iso_out = 0;

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
int usb_vol_music = 0;
int gradual_vol   = 0;

signed short  last_speaker_vol  = 0x7fff;
unsigned char last_speaker_step = 0xff;

signed short volume_relative_table_iphone[] = {0xa000, 0xa180, 0xa300, 0xa480, 0xa600, 0xa780, 0xa900, 0xaa80, 0xac00, 0xad80, 0xaf00, 0xb080, 0xb200, 0xb380,
                                               0xb500, 0xb680, 0xb800, 0xb980, 0xbb00, 0xbc80, 0xbe00, 0xbf80, 0xc100, 0xc280, 0xc400, 0xc580, 0xc700, 0xc880,
                                               0xca00, 0xcb80, 0xcd00, 0xce80, 0xd000, 0xd180, 0xd300, 0xd480, 0xd600, 0xd780, 0xd900, 0xda80, 0xdc00, 0xdd80,
                                               0xdf00, 0xe080, 0xe200, 0xe380, 0xe500, 0xe680, 0xe800, 0xe980, 0xeb00, 0xec80, 0xee00, 0xef80, 0xf100, 0xf280,
                                               0xf400, 0xf580, 0xf700, 0xf880, 0xfa00, 0xfb80, 0xfd00, 0xfe80, 0x0000, 0x0180, 0x3000};

const signed short volume_relative_value_table[] = {
    0xa000, 0xbea8, 0xc825, 0xcdf1, 0xd221, 0xd568, 0xd8a1, 0xda64, 0xdc61, 0xde23, 0xdfb7, 0xe124, 0xe273, 0xe3a6, 0xe4c3, 0xe5cd, 0xe6c6, 0xe7af, 0xe88c, 0xe95d, 0xea23,
    0xeadf, 0xeb93, 0xec3f, 0xece3, 0xed81, 0xee19, 0xeeab, 0xef37, 0xefbf, 0xf043, 0xf0c1, 0xf13c, 0xf1b4, 0xf227, 0xf298, 0xf305, 0xf36f, 0xf3d6, 0xf43b, 0xf49d, 0xf4fd,
    0xf55a, 0xf5b5, 0xf60f, 0xf666, 0xf6bb, 0xf70e, 0xf760, 0xf7b0, 0xf7fe, 0xf84b, 0xf897, 0xf8e0, 0xf929, 0xf970, 0xf9b6, 0xf9fb, 0xfa3e, 0xfa81, 0xfac2, 0xfb02, 0xfb41,
    0xfb7f, 0xfbbc, 0xfbf9, 0xfc34, 0xfc6e, 0xfca8, 0xfce0, 0xfd18, 0xfd4f, 0xfd86, 0xfdbb, 0xfdf0, 0xfe24, 0xfe58, 0xfe8a, 0xfebc, 0xfeee, 0xff1f, 0xff4f, 0xff7f, 0xffae,
    0xffdc, 0x0009, 0x0037, 0x0066, 0x0096, 0x00c5, 0x00f6, 0x0127, 0x0159, 0x018b, 0x01be, 0x01f2, 0x0226, 0x025c, 0x0291, 0x02c8, 0x0300};

const unsigned short volume_scale_table[] = {
    0,    18,   55,   92,   110,  130,  164,   201,   220,   251,   284,   320,   360,   400,   470,   520,   600,   680,   746,   902,   1050,  1270,  1380, 1430, 1486, 1542,
    1590, 1645, 1695, 1752, 1810, 1860, 1905,  1940,  1981,  2083,  2185,  2288,  2390,  2493,  2596,  2697,  2799,  2902,  3009,  3112,  3215,  3385,  3556, 3726, 3896, 4066,
    4237, 4407, 4578, 4748, 4918, 5081, 5268,  5439,  5609,  5780,  5952,  6120,  6281,  6473,  6667,  6860,  7053,  7246,  7439,  7633,  7826,  8020,  8214, 8408, 8600, 8766,
    8923, 9088, 9245, 9421, 9600, 9926, 10253, 10579, 10907, 11213, 11550, 11826, 12153, 12906, 13449, 14109, 14973, 15920, 15966, 16105, 16196, 16278, 16384};

unsigned short volume_scale_iphone_table[] = {0,    55,   58,   62,   69,   78,   87,   98,   110,  123,   138,   155,   174,   195,   218,   245,  260,
                                              275,  291,  309,  346,  389,  436,  489,  549,  581,  615,   652,   732,   691,   775,   821,   870,  921,
                                              976,  1034, 1095, 1160, 1229, 1301, 1379, 1460, 1547, 1638,  1756,  2597,  2751,  2913,  3086,  3463, 3841,
                                              4115, 4559, 4918, 5681, 6523, 7318, 7752, 8403, 9213, 10338, 11599, 12428, 13785, 14062, 15467, 16384};
#endif


void user_init(void)
{
    gpio_function_en(LEDTEST1);
    gpio_output_en(LEDTEST1);
    gpio_function_en(LEDTEST2);
    gpio_output_en(LEDTEST2);

#if SERIAL_DBG_EN
    uart0_init();
#endif
    /****audio init start****/


#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    /* enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device) */
    usb_init();
    /* enable data endpoint USB_EDP_SPEAKER. */
    usbhw_set_eps_en(BIT(USB_EDP_SPEAKER) | BIT(USB_EDP_MIC));

    /* enable global interrupt */
    core_interrupt_enable();

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

#endif

    hal_i2s_init(codec_buf_mic, codec_play_buf_spk, sizeof(codec_buf_mic), sizeof(codec_play_buf_spk));

    plic_interrupt_enable(IRQ_TIMER0);
    core_interrupt_enable();
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, 10 * sys_clk.pclk * 1000); //10ms
    timer_set_mode(TIMER0, TIMER_MODE_SYSCLK);
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    timer_start(TIMER0);
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    usb_data_reset_handler();
#endif

#if SERIAL_DBG_EN
    printk_write_callback(IO_PUT_CHAR_UART, trace_write);
    PRINTK("start \r\n");
#endif
}

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
void usb_data_reset_handler(void)
{
    iso_out_w  = 0;
    iso_out_r  = 0;
    paly_out_w = 0;
    for (int i = 0; i < SPK_BUFFER_SIZE; i++) {
        codec_buf_spk[i]      = 0;
        codec_play_buf_spk[i] = 0;
    }
}

unsigned int tcodec_get_speaker_rptr(void *buff)
{
    return ((audio_get_tx_dma_rptr(I2S_SPK_DMA) - (unsigned int)buff) / 4);
}

void app_check_audio_samples(void)
{
    int rptr0 = tcodec_get_speaker_rptr(codec_play_buf_spk);

    int samples_in_fifo0 = (paly_out_w - rptr0) & (SPK_BUFFER_SIZE - 1);

    int ref = 150;

    if ((samples_in_fifo0 < ref - 15 || samples_in_fifo0 > ref + 15)) {
        paly_out_w = (rptr0 + ref) & (SPK_BUFFER_SIZE - 1);

        PRINTK("play_ buff  reset!! ---%d \r\n", paly_out_w);
    }
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
        codec_buf_spk[iso_out_w++ & (SPK_BUFFER_SIZE - 1)] = dw;
    }
    usbhw_data_ep_ack(USB_EDP_SPEAKER);
    if (len != 192) {
        PRINTK("usb data len error %d \r\n", len);
    }
}

void audio_tx_data_to_usb(audio_sample_rate_e audio_rate)
{
    unsigned char length = 0;
    iso_in_w             = ((audio_get_rx_dma_wptr(I2S_MIC_DMA) - (unsigned int)codec_buf_mic) >> 1);
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
    for (unsigned char i = 0; i < length && iso_in_r != iso_in_w; i++) {
        short md        = (short)codec_buf_mic[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
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

        usb_iso_cfg_tick_out = clock_time();
    }
    /////////////////////////////////////
    // ISO INT
    /////////////////////////////////////
    if (usbhw_get_eps_irq() & BIT(USB_EDP_MIC)) {
        usbhw_clr_eps_irq(BIT(USB_EDP_MIC));
        ///////////// input to audio fifo int ////////////////
        audio_tx_data_to_usb(AUDIO_48K);
        num_iso_out++;
        if ((num_iso_out & 0x7f) == 0) {
            gpio_toggle(LEDTEST2);
        }
    }
}

PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)

int abs_ram(signed int i)
{
    return i >= 0 ? i : -i;
}

unsigned int app_usb_audio_samples_check(void)
{
    unsigned int t = 0;
    unsigned int r = core_interrupt_disable();

    t = clock_time() - usb_iso_cfg_tick_out;
    t = t * 48 / (1000 * 24);
    t = t > 48 ? 48 : t;

    int num   = ((iso_out_w - iso_out_r) & (SPK_BUFFER_SIZE - 1)) + t;
    int ndiff = num - (480 + 108);

    if (abs_ram(ndiff) > 60) {
        iso_out_r = iso_out_w - (480 + 108 - t);
    }
    core_restore_interrupt(r);
    return t;
}

unsigned char blc_get_iphone_volume_scale(signed short vol)
{
    unsigned char temp = 0xff;
    int           i;
    for (i = 0; i < 67; i++) {
        if (vol == volume_relative_table_iphone[i]) {
            temp = i;
            break;
        }
    }
    return temp;
}

int my_get_usb_data(void)
{
    unsigned int index;
    int          volume_index;

    // noise cancel for USB voluem changing.
    if (gradual_vol != usb_vol_music) {
        if (gradual_vol > usb_vol_music) {
            usb_vol_music += 100;
            if (usb_vol_music > gradual_vol) {
                usb_vol_music = gradual_vol;
            }
        } else {
            usb_vol_music -= 100;
            if (usb_vol_music < gradual_vol) {
                usb_vol_music = gradual_vol;
            }
        }
    }

    signed short  vol_temp  = (signed short)usbaud_speaker_curvol_get();
    unsigned char step_temp = usbaud_speaker_vol_get();

    if ((last_speaker_vol != vol_temp) || (last_speaker_step != step_temp)) {
        if (step_temp & 0x80) {
            usb_vol_music = 0;
            gradual_vol   = 0;
        } else {
            index = blc_get_iphone_volume_scale(vol_temp);
            if (index >= 67) {
                for (volume_index = 0; volume_index < (int)sizeof(volume_relative_value_table) / 2; volume_index++) {
                    if (vol_temp <= volume_relative_value_table[volume_index]) {
                        break;
                    }
                }
                if (volume_index > 100) {
                    volume_index = 100;
                }
                gradual_vol = volume_scale_table[volume_index];
            } else {
                gradual_vol = volume_scale_iphone_table[index];
            }
        }
        last_speaker_vol  = vol_temp;
        last_speaker_step = step_temp;
    }

    app_usb_audio_samples_check();
    app_check_audio_samples();
    for (int i = 0; i < 480; i++) {
        unsigned int dw = codec_buf_spk[iso_out_r++ & (SPK_BUFFER_SIZE - 1)];
        signed short s0 = dw;
        signed short s1 = dw >> 16;

        s0 = (s0 * usb_vol_music + 0x2000) >> 14;
        s1 = (s1 * usb_vol_music + 0x2000) >> 14;

        codec_play_buf_spk[paly_out_w++ & (SPK_BUFFER_SIZE - 1)] = (unsigned short)s0 | (s1 << 16);
    }
    return 1;
}
#endif

void my_get_mic_data_to_spk(void)
{
    iso_in_w = ((audio_get_rx_dma_wptr(I2S_MIC_DMA) - (unsigned int)codec_buf_mic) >> 1);
    for (int i = 0; i < 480 && iso_in_r != iso_in_w; i++) {
        short          md = (short)codec_buf_mic[iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
        unsigned short s0 = md;
        unsigned short s1 = md;
        unsigned int   dw = s0 | (s1 << 16);

        codec_play_buf_spk[paly_out_w++ & (MIC_BUFFER_SIZE - 1)] = dw;
    }
}

_attribute_ram_code_sec_ void timer0_irq_handler(void)
{
    if (timer_get_irq_status(FLD_TMR0_MODE_IRQ)) {
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ); //clear irq status
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
        if (usb_iso_out_en) {
            my_get_usb_data();
        }
#elif (AUDIO_MODE == I2S_TO_EXT_CODEC_MIC_SPK)
        my_get_mic_data_to_spk();
#endif
    }
}
PLIC_ISR_REGISTER(timer0_irq_handler, IRQ_TIMER0)

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
void app_usb_handle_set_intf(int intf, int alt)
{
    /////////  SPEAKER/////////////////
    if (intf == 1) {
        if (!alt) {
            usb_iso_out_en = 0;
            usb_data_reset_handler();
        } else {
            usb_iso_out_en = 1;
        }
        PRINTK("usb_iso_out_en %d \r\n", usb_iso_out_en);
    }
    /////////  MIC /////////////////
    if (intf == 2) {
        if (!alt) {
            usb_iso_in_en = 0;
        } else {
            usb_iso_in_en = 1;
        }
        PRINTK("usb_iso_in_en %d \r\n", usb_iso_in_en);
    }
}
#endif

void main_loop(void)
{
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    usb_handle_irq();
#endif
    if (clock_time_exceed(t1, 200000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LEDTEST1);
    }
}

#endif

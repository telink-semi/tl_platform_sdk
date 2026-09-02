/********************************************************************************************************
 * @file    spk_app.c
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
#if 1
#include "common.h"
#include "i2c/hal_i2c.h"
#include "i2c/hal_es8389.h"
#include "i2c/hal_nau8821.h"
#include "i2s/hal_i2s.h"
#include "log.h"
#include "../common/usb_dbg/debug_vcd.h"


#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB || AUDIO_MODE == I2S_TO_EXT_CODEC_MIC_SPK)
#include "usb/hal_usb_app_audio.h"


#define SPK_BUFFER_SIZE 1024
#define MIC_BUFFER_SIZE 1024

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
static sa_dac_t codec_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));
#endif
static sa_adc_t codec_buf_mic[MIC_BUFFER_SIZE] __attribute__((aligned(4)));
static sa_dac_t codec_play_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));

static hal_usb_app_audio_ctx_t usb_app_audio_ctx = {
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    .codec_buf_spk = codec_buf_spk,
#else
    .codec_buf_spk = NULL,
#endif
    .codec_buf_mic = codec_buf_mic,
    .codec_play_buf_spk = codec_play_buf_spk,
    .spk_buffer_size = SPK_BUFFER_SIZE,
    .mic_buffer_size = MIC_BUFFER_SIZE,
    .play_buf_spk_size = SPK_BUFFER_SIZE,
    .paly_out_w = 0,
    .paly_in_w = 0,
    .iso_out_w = 0,
    .iso_out_r = 0,
    .iso_in_w = 0,
    .iso_in_r = 0,
    .num_iso_out = 0, 
    .usb_iso_cfg_tick_out = 0,
    .usb_iso_out_en = 0,
    .usb_iso_in_en = 0,
    .first_play = 0,
};

unsigned int  t1;
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
int usb_vol_music = 0;
int gradual_vol   = 0;

signed short  last_speaker_vol  = 0x7fff;
unsigned char last_speaker_step = 0xff;

extern const signed short volume_relative_table_iphone[67];
extern const signed short volume_relative_value_table[101];
extern const unsigned short volume_scale_table[101];
extern const unsigned short volume_scale_iphone_table[67];

#endif


#define TEST_PIN PIN_SW5
unsigned char test_flag = 0;
int test_write_index = 0;
volatile unsigned int test_buffer[480] = {0};

void user_init(void)
{
    gpio_function_en(LEDTEST1);
    gpio_output_en(LEDTEST1);
    gpio_function_en(LEDTEST2);
    gpio_output_en(LEDTEST2);

    gpio_function_en(TEST_PIN);
    gpio_output_en(TEST_PIN);
    gpio_set_level(TEST_PIN, 0);
    
#if defined(MCU_CORE_TL322X)
    /* USB0 digital voltage must be 1.1V and HCLK min's 48M. */
    pm_set_dig_ldo(DIG_VOL_1V1_MODE, 1000);
    PLL_192M_D25F_96M_HCLK_N22_48M_PCLK_48M_MSPI_48M;
#endif

#if SERIAL_DBG_EN
    uart0_init();
#endif

    /****audio init start****/
    hal_i2s_init(codec_buf_mic, codec_play_buf_spk, sizeof(codec_buf_mic), sizeof(codec_play_buf_spk));

#if SERIAL_DBG_EN
    printk_write_callback(IO_PUT_CHAR_UART, trace_write);
    PRINTK("start \r\n");
#endif



#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    hal_usb_app_audio_init(&usb_app_audio_ctx);
#endif

    plic_interrupt_enable(IRQ_TIMER0);
    timer_set_init_tick(TIMER0, 0);
    timer_set_cap_tick(TIMER0, 10 * sys_clk.pclk * 1000); //10ms
    timer_set_mode(TIMER0, TIMER_MODE_SYSCLK);
    timer_set_irq_mask(FLD_TMR0_MODE_IRQ);
    timer_start(TIMER0);

    core_interrupt_enable();
}

#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)

unsigned int tcodec_get_speaker_rptr(void *buff)
{
    return ((audio_get_tx_dma_rptr(I2S_SPK_DMA) - (unsigned int)buff) / 4);
}

void app_check_audio_samples(void)
{
    int rptr0 = tcodec_get_speaker_rptr(usb_app_audio_ctx.codec_play_buf_spk);

    int samples_in_fifo0 = (usb_app_audio_ctx.paly_out_w - rptr0) & (SPK_BUFFER_SIZE - 1);

    int ref = 150;

    if ((samples_in_fifo0 < ref - 15 || samples_in_fifo0 > ref + 15)) {
        usb_app_audio_ctx.paly_out_w = (rptr0 + ref) & (SPK_BUFFER_SIZE - 1);

        PRINTK("play_ buff  reset!! ---%d \r\n", usb_app_audio_ctx.paly_out_w);
    }
}

int abs_ram(signed int i)
{
    return i >= 0 ? i : -i;
}

unsigned int app_usb_audio_samples_check(void)
{
    unsigned int t = 0;
    unsigned int r = core_interrupt_disable();

    t = clock_time() - usb_app_audio_ctx.usb_iso_cfg_tick_out;
    t = t * 48 / SYSTEM_TIMER_TICK_1MS;
    t = t > 48 ? 48 : t;

    int num   = ((usb_app_audio_ctx.iso_out_w - usb_app_audio_ctx.iso_out_r) & (usb_app_audio_ctx.spk_buffer_size - 1)) + t;
    int ndiff = num - (480 + 108);

    if (abs_ram(ndiff) > 60) {
        usb_app_audio_ctx.iso_out_r = usb_app_audio_ctx.iso_out_w - (480 + 108 - t);
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

    signed short  vol_temp  = hal_usb_app_audio_get_curvol();
    unsigned char step_temp = hal_usb_app_audio_get_speaker_vol();

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
    for (int i = 0; i < 480 && usb_app_audio_ctx.iso_out_r != usb_app_audio_ctx.iso_out_w; i++) {
        volatile sa_adc_t *rptr = (volatile sa_adc_t *)usb_app_audio_ctx.codec_buf_spk;
        volatile sa_adc_t *wptr = (volatile sa_adc_t *)usb_app_audio_ctx.codec_play_buf_spk;
        unsigned int dw = rptr[usb_app_audio_ctx.iso_out_r++ & (SPK_BUFFER_SIZE - 1)];
        signed short s0 = dw;
        signed short s1 = dw >> 16;

        s0 = (s0 * usb_vol_music + 0x2000) >> 14;
        s1 = (s1 * usb_vol_music + 0x2000) >> 14;

        wptr[usb_app_audio_ctx.paly_out_w++ & (SPK_BUFFER_SIZE - 1)] = (unsigned short)s0 | (s1 << 16);
    }


    return 1;
}
#endif

void my_get_mic_data_to_spk(void)
{
        usb_app_audio_ctx.iso_in_w = ((audio_get_rx_dma_wptr(I2S_MIC_DMA) - (unsigned int)codec_buf_mic) >> 1);
        for (int i = 0; i < 480 && usb_app_audio_ctx.iso_in_r != usb_app_audio_ctx.iso_in_w; i++) {
            short          md = (short)codec_buf_mic[usb_app_audio_ctx.iso_in_r++ & (MIC_BUFFER_SIZE - 1)];
            unsigned short s0 = md;
            unsigned short s1 = md;
        unsigned int   dw = s0 | (s1 << 16);

        usb_app_audio_ctx.codec_play_buf_spk[usb_app_audio_ctx.paly_out_w++ & (SPK_BUFFER_SIZE - 1)] = dw;
    }
}

_attribute_ram_code_sec_ void timer0_irq_handler(void)
{
    gpio_toggle(TEST_PIN);
    gpio_toggle(TEST_PIN);
    if (timer_get_irq_status(FLD_TMR0_MODE_IRQ)) {
        timer_clr_irq_status(FLD_TMR0_MODE_IRQ); //clear irq status
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
        if (usb_app_audio_ctx.usb_iso_out_en) {
            my_get_usb_data();
        }
#elif (AUDIO_MODE == I2S_TO_EXT_CODEC_MIC_SPK)
        my_get_mic_data_to_spk();
#endif
    }
}
PLIC_ISR_REGISTER(timer0_irq_handler, IRQ_TIMER0)

void main_loop(void)
{
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    hal_usb_app_audio_handle_loop();
#endif
    if (clock_time_exceed(t1, 200000)) {
        t1 = stimer_get_tick() | 1;
        gpio_toggle(LEDTEST1);



    }
}

#endif

#else
#include "common.h"
#include "usb/hal_usb_app_audio.h"

#define SPK_BUFFER_SIZE 1024
#define MIC_BUFFER_SIZE 1024
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
static sa_dac_t codec_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));
#endif
static sa_adc_t codec_buf_mic[MIC_BUFFER_SIZE] __attribute__((aligned(4)));
static sa_dac_t codec_play_buf_spk[SPK_BUFFER_SIZE] __attribute__((aligned(4)));

static hal_usb_app_audio_ctx_t usb_app_audio_ctx = {
#if (AUDIO_MODE == I2S_TO_EXT_CODEC_USB)
    .codec_buf_spk = codec_buf_spk,
#else
    .codec_buf_spk = NULL,
#endif
    .codec_buf_mic = codec_buf_mic,
    .codec_play_buf_spk = codec_play_buf_spk,
    .spk_buffer_size = SPK_BUFFER_SIZE,
    .mic_buffer_size = MIC_BUFFER_SIZE,
    .play_buf_spk_size = SPK_BUFFER_SIZE,
    .paly_out_w = 0,
    .paly_in_w = 0,
    .iso_out_w = 0,
    .iso_out_r = 0,
    .iso_in_w = 0,
    .iso_in_r = 0,
    .num_iso_out = 0, 
    .usb_iso_cfg_tick_out = 0,
    .usb_iso_out_en = 0,
    .usb_iso_in_en = 0,
};


void user_init(void)
{
    hal_usb_app_audio_init(&usb_app_audio_ctx);

    core_interrupt_enable();
}

void main_loop(void)
{
  
}

#endif

/********************************************************************************************************
 * @file    app_codec.c
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
#include "common.h"
#if (AUDIO_MODE == CODEC_DEMO)
#include <string.h>
#include "inc/drv_uart.h"
#include "inc/drv_audio_dac.h"
#include "inc/drv_audio_adc.h"
#include "inc/drv_soc_codec.h"
#include "common.h"
#include "modules/drv_gpio.h"
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "hal/hal_systimer.h"
#include "hal/hal_audio.h"
#include "app_sin_data.h"
#include "hal/hal_dma.h"
#define LINE_IN_TO_LINE_OUT_CASE       (1)
#define LINE_IN_TO_BUFF_CASE           (2)
#define BUFF_TO_LINE_OUT_CASE          (3)

#define CODEC_MODE_SEL                  LINE_IN_TO_LINE_OUT_CASE

#define DLM_BUS_READ_OFFSET 0x40000000

#define DATA_BLOCK_NUM     4
#define DATA_BLOCK_SIZE    480*5
#define DATA_BUFF_LEN     (DATA_BLOCK_NUM * DATA_BLOCK_SIZE)

#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE)
#define MONO                 0
#if (MONO)
#define INPUT0_SRC           AUDIO_ADC_CH_0
#define OUTPUT_SRC           AUDIO_DAC_CH_0
#else
#define INPUT0_SRC           AUDIO_ADC_CH_0
#define INPUT1_SRC           AUDIO_ADC_CH_4
#define OUTPUT_SRC           AUDIO_DAC_CH_STEREO
#endif
#elif (CODEC_MODE_SEL == LINE_IN_TO_BUFF_CASE)
#define CH_NUM              AUDIO_ADC_MODE_FIVE
#define INPUT_SRC           (AUDIO_ADC_CH_0 | AUDIO_ADC_CH_1 | AUDIO_ADC_CH_2 | AUDIO_ADC_CH_3 | AUDIO_ADC_CH_4)
#elif (CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
#define MONO                 0
#define OUTPUT_SRC           AUDIO_DAC_CH_STEREO
#endif

#define ADC_SAMPLE_RATE      AUDIO_ADC_FS_48K
#define DAC_SAMPLE_RATE      AUDIO_DAC_FS_48K
#define ADC_BIT_WIDTH        AUDIO_ADC_24BIT
#define DAC_BIT_WIDTH        AUDIO_DAC_24BIT

typedef enum {
    AUDIO_BUF_EMPTY,
    AUDIO_BUF_FULL,
} e_audio_buf_stat;

typedef struct {
    uint32_t bufAddr;
    e_audio_buf_stat stat;
} block_buf_t;

uint32_t audio_buf[DATA_BUFF_LEN];
uint32_t zero_buf[DATA_BLOCK_SIZE];
uint32_t audio_llp_buf[DATA_BLOCK_SIZE];

block_buf_t audio_block_buf[DATA_BLOCK_NUM];

static volatile uint32_t rx_index = 0;
static volatile uint32_t wx_index = 0;

dmac_handle_t audio_adc_dmac_handle;
dmac_handle_t audio_dac_dmac_handle;

dmac_llp_node_t adc_dmac_llp_config;
dmac_llp_node_t dac_dmac_llp_config;

// log init
uart_handle_t uart_huart;

void CPU2_DMA_IRQHandler(void)
{
#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE || CODEC_MODE_SEL == LINE_IN_TO_BUFF_CASE)
    drv_dmac_irq_handle(&audio_adc_dmac_handle);
#endif
#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE || CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
    drv_dmac_irq_handle(&audio_dac_dmac_handle);
#endif
}
PLIC_ISR_REGISTER(CPU2_DMA_IRQHandler, IRQ_CPU2_DMA)

void audio_buf_init(block_buf_t *block_base, uint32_t buf_base, uint32_t block_size, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        block_base[i].bufAddr = buf_base + block_size * i;
        block_base[i].stat = AUDIO_BUF_EMPTY;
    }
}

void codec_dac_dma_tx_complete_cb(void)
{
#if (CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
    drv_audio_dac_dma_tx((uint32_t *)((unsigned int)sin_48k_stereo_24bit + DLM_BUS_READ_OFFSET), sizeof(sin_48k_stereo_24bit)/4);
#else
    //soc_printf("rx_index %d!\n", rx_index);
    if (audio_block_buf[rx_index].stat == AUDIO_BUF_EMPTY) {
        //soc_printf("audio buff empty!\n");
        drv_audio_dac_dma_tx((uint32_t *)((uint32_t)zero_buf + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
        return;
    }
    drv_audio_dac_dma_tx((uint32_t *)(audio_block_buf[rx_index].bufAddr + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
    audio_block_buf[rx_index].stat = AUDIO_BUF_EMPTY;
    rx_index++;
    if (rx_index == DATA_BLOCK_NUM) {
        rx_index = 0;
    }
#endif
}

void codec_adc_dma_rx_complete_cb(void)
{
    //soc_printf("wx_index %d!\n", wx_index);
    if (audio_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
        //soc_printf("audio buff full!\n");
    }
    audio_block_buf[wx_index].stat = AUDIO_BUF_FULL;
    wx_index++;
    if (wx_index == DATA_BLOCK_NUM) {
        wx_index = 0;
    }
    drv_audio_adc_dma_rx((uint32_t *)(audio_block_buf[wx_index].bufAddr + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
}
#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE)
void audio_ad_da_loop_test(void)
{
    soc_printf("codec adda loop sample start!\n");
    audio_buf_init(audio_block_buf, (uint32_t)audio_buf, DATA_BLOCK_SIZE * sizeof(int), DATA_BLOCK_NUM);

    drv_audio_adc_init();
    audio_adc_cfg_t adc_cfg;
    adc_cfg.dig_gain = AUDIO_ADC_DIG_GAIN_0DB;
    adc_cfg.pga_gain = AUDIO_ADC_PGA_GAIN_0DB;
    adc_cfg.fifo_src = AUDIO_ADC_FIFO_SRC_ADC;
    adc_cfg.fs = ADC_SAMPLE_RATE;
#if (MONO)
    drv_audio_adc_open(INPUT0_SRC, &adc_cfg);
#else
    drv_audio_adc_open(INPUT0_SRC | INPUT1_SRC, &adc_cfg);
#endif
    // adc data format init
    audio_adc_data_format_t adc_data_format;
    memset(&adc_data_format, 0, sizeof(audio_adc_data_format_t));
    adc_data_format.hdma = &audio_adc_dmac_handle;
    adc_data_format.wide = ADC_BIT_WIDTH;
#if (MONO)
    adc_data_format.ch_mode = AUDIO_ADC_MODE_MONO;
    adc_data_format.fifo_en_bitmap = INPUT0_SRC;
#else
    adc_data_format.ch_mode = AUDIO_ADC_MODE_STEREO;
    adc_data_format.fifo_en_bitmap = INPUT0_SRC | INPUT1_SRC;
#endif
    drv_audio_adc_set_dma_data_format(&adc_data_format);

#if AUDIO_ADC_DMA_LLP_EN
    drv_audio_adc_dmac_llp_head_set(&adc_dmac_llp_config);
    drv_audio_adc_dmac_llp_node_add(&adc_dmac_llp_config, &adc_dmac_llp_config, (uint32_t *)((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#else
    drv_audio_adc_rx_complete_cb_register((audio_adc_rx_hook_t)codec_adc_dma_rx_complete_cb);
    drv_audio_adc_dma_rx((uint32_t *)(audio_block_buf[0].bufAddr + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#endif

#if (MONO)
    drv_audio_adc_start(INPUT0_SRC);
#else
    drv_audio_adc_start(INPUT0_SRC | INPUT1_SRC);
#endif

    drv_audio_dac_init();
    audio_dac_cfg_t dac_cfg = {0};
    dac_cfg.autx_gain = AUDIO_DAC_AUTX_GAIN_0DB;
    dac_cfg.dig_gain = AUDIO_DAC_DIG_GAIN_0DB;
    dac_cfg.fs = DAC_SAMPLE_RATE;
    dac_cfg.src = AUDIO_DAC_SRC_PCM;
    drv_audio_dac_open(OUTPUT_SRC, &dac_cfg);

    audio_dac_data_format_t dac_data_format;
    memset(&dac_data_format, 0, sizeof(audio_dac_data_format_t));
    dac_data_format.hdma = &audio_dac_dmac_handle;
#if (MONO)
    dac_data_format.ch_mode = AUDIO_DAC_MODE_MONO;
#else
    dac_data_format.ch_mode = AUDIO_DAC_MODE_STEREO;
#endif
    dac_data_format.wide = DAC_BIT_WIDTH;
    dac_data_format.fifo_en_bitmap = OUTPUT_SRC;
    //dac_data_format.port_fifo_en[AUDIO_DAC_PORT_1] = DRV_SET;
    drv_audio_dac_set_dma_data_format(&dac_data_format);

#if AUDIO_DAC_DMA_LLP_EN
    drv_audio_dac_dmac_llp_head_set(&dac_dmac_llp_config);
    drv_audio_dac_dmac_llp_node_add(&dac_dmac_llp_config, &dac_dmac_llp_config,  (uint32_t *)((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#else
    drv_audio_dac_tx_complete_cb_register((audio_dac_tx_hook_t)codec_dac_dma_tx_complete_cb);
    drv_audio_dac_dma_tx((uint32_t *)(audio_block_buf[0].bufAddr + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#endif
#if !AUDIO_DAC_DMA_LLP_EN
    //wait for adc write half full
    while (wx_index < DATA_BLOCK_NUM / 2){};
#endif
    drv_audio_dac_start(OUTPUT_SRC);
}
#elif (CODEC_MODE_SEL == LINE_IN_TO_BUFF_CASE)
void audio_ad_test(void)
{
    soc_printf("codec ad test start!\n");
    audio_buf_init(audio_block_buf, (uint32_t)audio_buf, DATA_BLOCK_SIZE * sizeof(int), DATA_BLOCK_NUM);

    drv_audio_adc_init();
    audio_adc_cfg_t adc_cfg;
    adc_cfg.dig_gain = AUDIO_ADC_DIG_GAIN_0DB;
    adc_cfg.pga_gain = AUDIO_ADC_PGA_GAIN_0DB;
    adc_cfg.fifo_src = AUDIO_ADC_FIFO_SRC_ADC;
    adc_cfg.fs = ADC_SAMPLE_RATE;
    drv_audio_adc_open(INPUT_SRC, &adc_cfg);

    // adc data format init
    audio_adc_data_format_t adc_data_format;
    memset(&adc_data_format, 0, sizeof(audio_adc_data_format_t));
    adc_data_format.hdma = &audio_adc_dmac_handle;
    adc_data_format.wide = ADC_BIT_WIDTH;
    adc_data_format.ch_mode = CH_NUM;
    adc_data_format.fifo_en_bitmap = INPUT_SRC;
    drv_audio_adc_set_dma_data_format(&adc_data_format);

#if AUDIO_ADC_DMA_LLP_EN
    drv_audio_adc_dmac_llp_head_set(&adc_dmac_llp_config);
    drv_audio_adc_dmac_llp_node_add(&adc_dmac_llp_config, &adc_dmac_llp_config, (uint32_t *)((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#else
    drv_audio_adc_rx_complete_cb_register((audio_adc_rx_hook_t)codec_adc_dma_rx_complete_cb);
    drv_audio_adc_dma_rx((uint32_t *)(audio_block_buf[0].bufAddr + DLM_BUS_READ_OFFSET), DATA_BLOCK_SIZE);
#endif
    drv_audio_adc_start(INPUT_SRC);
}
#elif (CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
void audio_da_test(void)
{
    soc_printf("codec da start!\n");
    audio_buf_init(audio_block_buf, (uint32_t)audio_buf, DATA_BLOCK_SIZE * sizeof(int), DATA_BLOCK_NUM);
    drv_audio_dac_init();
    audio_dac_cfg_t dac_cfg = {0};
    dac_cfg.autx_gain = AUDIO_DAC_AUTX_GAIN_0DB;
    dac_cfg.dig_gain = AUDIO_DAC_DIG_GAIN_0DB;
    dac_cfg.fs = DAC_SAMPLE_RATE;
    dac_cfg.src = AUDIO_DAC_SRC_PCM;
    drv_audio_dac_open(OUTPUT_SRC, &dac_cfg);

    audio_dac_data_format_t dac_data_format;
    memset(&dac_data_format, 0, sizeof(audio_dac_data_format_t));
    dac_data_format.hdma = &audio_dac_dmac_handle;
#if (MONO)
    dac_data_format.ch_mode = AUDIO_DAC_MODE_MONO;
#else
    dac_data_format.ch_mode = AUDIO_DAC_MODE_STEREO;
#endif
    dac_data_format.wide = DAC_BIT_WIDTH;
    dac_data_format.fifo_en_bitmap = OUTPUT_SRC;
    drv_audio_dac_set_dma_data_format(&dac_data_format);

#if AUDIO_DAC_DMA_LLP_EN
    drv_audio_dac_dmac_llp_head_set(&dac_dmac_llp_config);
    drv_audio_dac_dmac_llp_node_add(&dac_dmac_llp_config, &dac_dmac_llp_config, (uint32_t *)((uint32_t)sin_48k_stereo_24bit + DLM_BUS_READ_OFFSET), sizeof(sin_48k_stereo_24bit)/4);
#else
    drv_audio_dac_tx_complete_cb_register((audio_dac_tx_hook_t)codec_dac_dma_tx_complete_cb);
    drv_audio_dac_dma_tx((uint32_t *)((unsigned int)sin_48k_stereo_24bit + DLM_BUS_READ_OFFSET), sizeof(sin_48k_stereo_24bit)/4);
#endif
    drv_audio_dac_start(OUTPUT_SRC);
}
#endif
void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_huart, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    uart_huart.instance = UART1;
    uart_huart.init.baudrate = 500000;
    uart_huart.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_huart.init.parity = UART_PARITY_NONE;
    uart_huart.init.stopbits = UART_STOPBITS_1;
    uart_huart.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_huart);
}

extern unsigned char g_audio_pll_is_used;
extern uint32_t frac_pll_freq;
void bsp_init(void)
{
    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1

    frac_pll_freq = 196608000;
    if((frac_pll_freq != FRACPLL_OUT_FREQ) || (!g_audio_pll_is_used))
    {
        drv_cpr_enable_fracpll(frac_pll_freq);
        g_audio_pll_is_used =1;
    }

    cpr_mclk1_init_t mclk1_init;
    mclk1_init.freq = 6144000;
    mclk1_init.source = DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL1;
    drv_cpr_config_mclk1(&mclk1_init);

    /* Audio system powerup */
    drv_cpr_audio_system_powerup();

    drv_soc_codec_msp_init();
    __DRV_CPR_CPU2_DMA_CLK_ENABLE();

    drv_hw_int_enable(CPU2_DMA_IRQn);
}

volatile unsigned int rx_index0;
volatile unsigned int rx_index1;
volatile unsigned int wx_index0;
volatile unsigned int wx_index1;

void user_init(void)
{
    core_interrupt_enable();
    bsp_init();
#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE)
    audio_ad_da_loop_test();
#elif (CODEC_MODE_SEL == LINE_IN_TO_BUFF_CASE)
    audio_ad_test();
#elif (CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
    audio_da_test();
#endif

#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE) || (CODEC_MODE_SEL == LINE_IN_TO_BUFF_CASE)
#if AUDIO_ADC_DMA_LLP_EN
    rx_index0 = audio_get_rx_dma_wptr(&audio_adc_dmac_handle) - ((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET);
    delay_ms(5);
    rx_index1 = audio_get_rx_dma_wptr(&audio_adc_dmac_handle) - ((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET);
#endif
#endif
#if (CODEC_MODE_SEL == LINE_IN_TO_LINE_OUT_CASE) || (CODEC_MODE_SEL == BUFF_TO_LINE_OUT_CASE)
#if AUDIO_DAC_DMA_LLP_EN
    wx_index0 = audio_get_tx_dma_rptr(&audio_dac_dmac_handle) - ((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET);
    delay_ms(5);
    wx_index1 = audio_get_tx_dma_rptr(&audio_dac_dmac_handle) - ((uint32_t)audio_llp_buf + DLM_BUS_READ_OFFSET);
#endif
#endif
}

void main_loop(void)
{

}
#endif

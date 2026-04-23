/********************************************************************************************************
 * @file    app_mix.c
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
#if (AUDIO_MODE == AUDIO_MIX_DEMO)
#include "inc/drv_audio_adc.h"
#include "inc/drv_audio_dac.h"
#include "inc/drv_soc_codec.h"
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "modules/drv_gpio.h"
#include "inc/drv_tdm.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>

#define LINE_IN_I2S_OUT_CASE       (1)
#define I2S_IN_LINE_OUT_CASE       (2)

#define AUDIO_MODE_SEL             LINE_IN_I2S_OUT_CASE

#define DATA_BLOCK_NUM             4
#define DATA_BLOCK_SIZE            1200
#define DATA_BUFF_LEN                 (DATA_BLOCK_NUM * DATA_BLOCK_SIZE)

#define USE_16BIT                  0//0:24bit;1:16bit
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

block_buf_t audio_block_buf[DATA_BLOCK_NUM];

static volatile uint32_t rx_index = 0;
static volatile uint32_t wx_index = 0;

// log init
uart_handle_t uart_handle;

static tdm_handle_t i2s_tx_handle;
static tdm_handle_t i2s_rx_handle;

dmac_handle_t audio_adc_dmac_handle;
dmac_handle_t audio_dac_dmac_handle;

static void tdm_dma_tx_complete_cb(void *args);
static void tdm_dma_rx_complete_cb(void *args);

static void tdm_tx_msp_init(void *args);
static void tdm_rx_msp_init(void *args);

tdm_handle_cb_t tdm_tx_handle_cb = {
    .tx_cplt_callback = tdm_dma_tx_complete_cb,
    .tx_error_callback = NULL,
    .rx_cplt_callback = NULL,
    .rx_error_callback = NULL,
    .msp_init_callback = tdm_tx_msp_init,
    .msp_deinit_callback = NULL,
};

tdm_handle_cb_t tdm_rx_handle_cb = {
    .tx_cplt_callback = NULL,
    .tx_error_callback = NULL,
    .rx_cplt_callback = tdm_dma_rx_complete_cb,
    .rx_error_callback = NULL,
    .msp_init_callback = tdm_rx_msp_init,
    .msp_deinit_callback = NULL,
};

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
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

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}

void AUDIO_DMA_IRQHandler(void)
{
#if (AUDIO_MODE_SEL == LINE_IN_I2S_OUT_CASE)
    drv_dmac_irq_handle(i2s_tx_handle.hdma_tx);
#elif (AUDIO_MODE_SEL == I2S_IN_LINE_OUT_CASE)
    drv_dmac_irq_handle(i2s_rx_handle.hdma_rx);
#endif
}
PLIC_ISR_REGISTER(AUDIO_DMA_IRQHandler, IRQ_AUDIO_DMA)

void CPU2_DMA_IRQHandler(void)
{
#if (AUDIO_MODE_SEL == LINE_IN_I2S_OUT_CASE)
    drv_dmac_irq_handle(&audio_adc_dmac_handle);
#elif (AUDIO_MODE_SEL == I2S_IN_LINE_OUT_CASE)
    drv_dmac_irq_handle(&audio_dac_dmac_handle);
#endif
}
PLIC_ISR_REGISTER(CPU2_DMA_IRQHandler, IRQ_CPU2_DMA)

void codec_i2s_audio_buf_init(block_buf_t *block_base, uint32_t buf_base, uint32_t block_size, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        block_base[i].bufAddr = buf_base + block_size * i;
        block_base[i].stat = AUDIO_BUF_EMPTY;
    }
}

void tdm_dma_tx_complete_cb(void *args)
{
    (void) args;
    //soc_printf("tdm r:%d\n",rx_index);
    if (audio_block_buf[rx_index].stat == AUDIO_BUF_EMPTY) {
        //soc_printf("audio buff empty!\n");
        drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)((uint32_t)zero_buf + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE*(USE_16BIT+1));
        return;
    }
    drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)((uint32_t)audio_block_buf[rx_index].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE*(USE_16BIT+1));
    audio_block_buf[rx_index].stat = AUDIO_BUF_EMPTY;
    rx_index++;
    if (rx_index == DATA_BLOCK_NUM) {
        rx_index = 0;
    }
}

void codec_adc_dma_rx_complete_cb(void *args)
{
    (void) args;
    // soc_printf("adc w:%d\n",wx_index);
    if (audio_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
        //soc_printf("audio buff full!\n");
    }
    audio_block_buf[wx_index].stat = AUDIO_BUF_FULL;
    wx_index++;
    if (wx_index == DATA_BLOCK_NUM) {
        wx_index = 0;
    }
    drv_audio_adc_dma_rx((uint32_t *)(audio_block_buf[wx_index].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE);
}

void tdm_dma_rx_complete_cb(void *args)
{
    (void) args;
    //soc_printf("tdm w:%d\n", wx_index);
    if (audio_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
        //soc_printf("audio buff full!\n");
    }
    audio_block_buf[wx_index].stat = AUDIO_BUF_FULL;
    wx_index++;
    if (wx_index == DATA_BLOCK_NUM) {
        wx_index = 0;
    }
    drv_tdm_recevie_dma(&i2s_rx_handle, (uint32_t *)(audio_block_buf[wx_index].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE*(USE_16BIT+1));
}

void codec_dac_stereo_tx_complete_cb(void *args)
{
    (void) args;
    // soc_printf("dac r:%d\n",rx_index);
    if (audio_block_buf[rx_index].stat == AUDIO_BUF_EMPTY) {
        //soc_printf("audio buff empty!\n");
        drv_audio_dac_dma_tx((uint32_t *)((uint32_t)zero_buf + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE);
        return;
    }
    drv_audio_dac_dma_tx((uint32_t *)((uint32_t)audio_block_buf[rx_index].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE);
    audio_block_buf[rx_index].stat = AUDIO_BUF_EMPTY;
    rx_index++;
    if (rx_index == DATA_BLOCK_NUM) {
        rx_index = 0;
    }
}

void codec_adc_rx_init(void)
{
    codec_i2s_audio_buf_init(audio_block_buf, (uint32_t)audio_buf, DATA_BLOCK_SIZE * sizeof(int), DATA_BLOCK_NUM);

    drv_audio_adc_init();
    audio_adc_cfg_t adc_cfg;
    adc_cfg.dig_gain = AUDIO_ADC_DIG_GAIN_0DB;
    adc_cfg.pga_gain = AUDIO_ADC_PGA_GAIN_0DB;
    adc_cfg.fifo_src = AUDIO_ADC_FIFO_SRC_ADC;
    adc_cfg.fs = AUDIO_ADC_FS_48K;

    drv_audio_adc_open(AUDIO_ADC_CH_0 | AUDIO_ADC_CH_2, &adc_cfg);

    audio_adc_data_format_t adc_data_format;
    memset(&adc_data_format, 0, sizeof(audio_adc_data_format_t));
    adc_data_format.hdma = &audio_adc_dmac_handle;
    adc_data_format.ch_mode = AUDIO_ADC_MODE_STEREO;
#if (USE_16BIT==1)
    adc_data_format.wide = AUDIO_ADC_16BIT;
#else
    adc_data_format.wide = AUDIO_ADC_24BIT;
#endif
    adc_data_format.fifo_en_bitmap = AUDIO_ADC_CH_0 | AUDIO_ADC_CH_2;
    drv_audio_adc_set_dma_data_format(&adc_data_format);

    drv_audio_adc_rx_complete_cb_register(codec_adc_dma_rx_complete_cb);
    drv_audio_adc_dma_rx((uint32_t *)(audio_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE);

    drv_audio_adc_start(AUDIO_ADC_CH_0 | AUDIO_ADC_CH_2);
   // while (wx_index < DATA_BLOCK_NUM / 2) {};
}

void codec_dac_stereo_tx_init(void)
{
    drv_audio_dac_init();
    audio_dac_cfg_t cfg;
    cfg.autx_gain = AUDIO_DAC_AUTX_GAIN_0DB;
    cfg.dig_gain = AUDIO_DAC_DIG_GAIN_0DB;
    cfg.fs = AUDIO_DAC_FS_48K;
    cfg.src = AUDIO_DAC_SRC_PCM;
    drv_audio_dac_open(AUDIO_DAC_CH_STEREO, &cfg);

    audio_dac_data_format_t data_format;
    memset(&data_format, 0, sizeof(audio_dac_data_format_t));
    data_format.hdma = &audio_dac_dmac_handle;
    data_format.ch_mode = AUDIO_DAC_MODE_STEREO;
#if (USE_16BIT==1)
    data_format.wide = AUDIO_DAC_16BIT;
#else
    data_format.wide = AUDIO_DAC_24BIT;
#endif
    data_format.fifo_en_bitmap = AUDIO_DAC_CH_STEREO;
    drv_audio_dac_set_dma_data_format(&data_format);

    drv_audio_dac_tx_complete_cb_register(codec_dac_stereo_tx_complete_cb);
}

void tdm_i2s_rx_init(void)
{
    codec_i2s_audio_buf_init(audio_block_buf, (uint32_t)audio_buf, DATA_BLOCK_SIZE * sizeof(int), DATA_BLOCK_NUM);
    memset(&i2s_rx_handle, 0, sizeof(i2s_rx_handle));
    i2s_rx_handle.instance = TDM1;
    i2s_rx_handle.init.mode = I2S_MODE;
    i2s_rx_handle.init.master_mode = TDM_SLAVE_MODE;
    i2s_rx_handle.init.sclk_polarity = TDM_SCLK_DRV_DATA_AT_P_EDGE;
#if (USE_16BIT==1)
    i2s_rx_handle.init.slot_resolution = TDM_SLOT_RESOLUTION_16_BITS;
    i2s_rx_handle.init.slot_width = TDM_SLOT_W_16_BITS;
#else
    i2s_rx_handle.init.slot_resolution = TDM_SLOT_RESOLUTION_24_BITS;
    i2s_rx_handle.init.slot_width = TDM_SLOT_W_24_BITS;
#endif
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en = TDM_LINE0_EN;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_RX;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ws_format = TDM_WS_FORMAT_I2S_STANDARD;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ws_polarity = TDM_WS_0_LEFT_CH_WS_1_RIGHT_CH;
    i2s_rx_handle.init.audio_fre = 48000;
    drv_tdm_register_cb(&i2s_rx_handle, &tdm_rx_handle_cb);
    drv_tdm_init(&i2s_rx_handle);
}

void tdm_i2s_tx_init(void)
{
    memset(&i2s_tx_handle, 0, sizeof(i2s_tx_handle));
    i2s_tx_handle.instance = TDM1;
    i2s_tx_handle.init.mode = I2S_MODE;
    i2s_tx_handle.init.master_mode = TDM_SLAVE_MODE;
    i2s_tx_handle.init.sclk_polarity = TDM_SCLK_DRV_DATA_AT_P_EDGE;
#if (USE_16BIT==1)
    i2s_tx_handle.init.slot_resolution = TDM_SLOT_RESOLUTION_16_BITS;
    i2s_tx_handle.init.slot_width = TDM_SLOT_W_16_BITS;
#else
    i2s_tx_handle.init.slot_resolution = TDM_SLOT_RESOLUTION_24_BITS;
    i2s_tx_handle.init.slot_width = TDM_SLOT_W_24_BITS;
#endif
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en = TDM_LINE0_EN;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ws_format = TDM_WS_FORMAT_I2S_STANDARD;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ws_polarity = TDM_WS_0_LEFT_CH_WS_1_RIGHT_CH;
    i2s_tx_handle.init.audio_fre = 48000;
    drv_tdm_register_cb(&i2s_tx_handle, &tdm_tx_handle_cb);
    drv_tdm_init(&i2s_tx_handle);

    drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)(zero_buf[0] + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE*(USE_16BIT+1));
    drv_tdm_start(&i2s_tx_handle);
}

void audio_adc_i2s_log_show(void)
{
    soc_printf("Audio Codec adc path test method.\n");
    soc_printf("\t Analyzer Analog output to ADC0 and ADC4, then send digital data to Analyzer by I2S.\n");
    soc_printf("\t Chip as I2S master, standard mode, %d bit wide, %d bit resolution.\n",USE_16BIT?16:24,USE_16BIT?16:24);
    soc_printf("\t PB0->I2S_SDO.\n");
    soc_printf("\t PB2->I2S_SCLK.\n");
    soc_printf("\t PB3->I2S_WS.\n");
}

void codec_adc_rx_i2s_tx_path_test(void)
{
    audio_adc_i2s_log_show();
    codec_adc_rx_init();
    tdm_i2s_tx_init();
}
void audio_dac_i2s_log_show(void)
{
    soc_printf("Audio Codec dac path test method.\n");
    soc_printf("\t Analyzer I2S output, DAC0 and DAC1 send Analog data to Analyzer by Analog input.\n");
    soc_printf("\t Chip as I2S master, standard mode, %d bit wide, %d bit resolution.\n",USE_16BIT?16:24,USE_16BIT?16:24);
    soc_printf("\t PB0->I2S_SDI.\n");
    soc_printf("\t PB2->I2S_SCLK.\n");
    soc_printf("\t PB3->I2S_WS.\n");
}

static void tdm_tx_msp_init(void *args)
{
    tdm_handle_t *tdm_handle = (tdm_handle_t *)args;
    /* Mclk1 enable */
    __DRV_CPR_MCLK1_CLK_ENABLE();

    /* Audio apb clk enable */
    __DRV_CPR_AUDIO_APB_CLK_ENABLE();

    /* Audio dma clk enable */
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();

    /* config clkout0 from mclk1*/
    drv_cpr_tdm_clkout0_config(0);

    /* config tdm mclk from clkout0, sclk = slot_width * audio_fre * 2channel*/
    uint32_t i2s_sclk_div = drv_cpr_get_mclk1_freq() / ((tdm_handle->init.slot_width + 1) * 4 * 2 * tdm_handle->init.audio_fre) - 1;
    drv_cpr_tdm1_mclk_config(i2s_sclk_div);

    /* config clkout0 enable*/
    __DRV_CPR_CLOCKOUT0_ENABLE();

    /* tdm1 clk enable */
    __DRV_CPR_TDM1_CLK_ENABLE();

    /* Init GPIO pinmux */
    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_B;
    /* PB02: SCLK, PB03: WS, PB00: SDO */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_NOPULL;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
    drv_gpio_init(&gpio_init);

    static dmac_handle_t tdm1_dmac_handle;
    memset(&tdm1_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm1_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm1_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm1_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm1_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT==1)
    tdm1_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_16BITS;
    tdm1_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_16BITS;
#else
    tdm1_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_32BITS;
    tdm1_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_32BITS;
#endif
    tdm1_dmac_handle.init.fifo_mode = DRV_SET;
    tdm1_dmac_handle.init.trans_mode = DMAC_CTL_TT_MEM2PER;
    tdm1_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_HARD;
    tdm1_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    tdm1_dmac_handle.init.dst_hs_num = AUDIO_DMAC_HS_I2S1_TX;

    tdm1_dmac_handle.init.channel = AUDIO_DMAC_CH0;
    tdm1_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm1_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_tx, tdm1_dmac_handle);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
}

static void tdm_rx_msp_init(void *args)
{
    tdm_handle_t *tdm_handle = (tdm_handle_t *)args;
    /* Mclk1 enable */
    __DRV_CPR_MCLK1_CLK_ENABLE();

    /* Audio apb clk enable */
    __DRV_CPR_AUDIO_APB_CLK_ENABLE();

    /* Audio dma clk enable */
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();

    /* config clkout0 from mclk1*/
    drv_cpr_tdm_clkout0_config(0);

    /* config tdm mclk from clkout0, sclk = slot_width * audio_fre * 2channel*/
    uint32_t i2s_sclk_div = drv_cpr_get_mclk1_freq() / ((tdm_handle->init.slot_width + 1) * 4 * 2 * tdm_handle->init.audio_fre) - 1;
    drv_cpr_tdm1_mclk_config(i2s_sclk_div);

    /* config clkout0 enable*/
    __DRV_CPR_CLOCKOUT0_ENABLE();

    /* tdm1 clk enable */
    __DRV_CPR_TDM1_CLK_ENABLE();

    /* Init GPIO pinmux */
    gpio_init_t gpio_init;
    gpio_init.port = GPIO_PORT_B;
    /* PB00: SDO, PB02: SCLK, PB03: WS */
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_NOPULL;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
    drv_gpio_init(&gpio_init);

    static dmac_handle_t tdm_rx_dmac_handle;
    memset(&tdm_rx_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm_rx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm_rx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm_rx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm_rx_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT==1)
    tdm_rx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_16BITS;
    tdm_rx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_16BITS;
#else
    tdm_rx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_32BITS;
    tdm_rx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_32BITS;
#endif
    tdm_rx_dmac_handle.init.fifo_mode = DRV_SET;
    tdm_rx_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    tdm_rx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    tdm_rx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_HARD;
    tdm_rx_dmac_handle.init.src_hs_num = AUDIO_DMAC_HS_I2S1_RX;

    tdm_rx_dmac_handle.init.channel = AUDIO_DMAC_CH0;
    tdm_rx_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm_rx_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_rx, tdm_rx_dmac_handle);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
}

void i2s_rx_codec_dac_stereo_tx_path_test(void)
{
    audio_dac_i2s_log_show();
    tdm_i2s_rx_init();
    codec_dac_stereo_tx_init();
    wx_index++;
    drv_tdm_recevie_dma(&i2s_rx_handle, (uint32_t *)(audio_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE*(USE_16BIT+1));
    drv_tdm_start(&i2s_rx_handle);
   // while (wx_index < DATA_BLOCK_NUM / 2){};
    drv_audio_dac_dma_tx((uint32_t *)(zero_buf[0] + MCUA_SYS_BUS_BASE), DATA_BLOCK_SIZE);
    drv_audio_dac_start(AUDIO_DAC_CH_STEREO);
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
    mclk1_init.freq = frac_pll_freq;
    mclk1_init.source = DRV_CPR_MCLK1_SOURCE_DIVIDED_PLL1;
    drv_cpr_config_mclk1(&mclk1_init);

    /* Audio system powerup */
    drv_cpr_audio_system_powerup();

    drv_soc_codec_msp_init();
    __DRV_CPR_CPU2_DMA_CLK_ENABLE();

    drv_hw_int_enable(CPU2_DMA_IRQn);
}

void user_init(void)
{
    core_interrupt_enable();
    bsp_init();
#if (AUDIO_MODE_SEL == LINE_IN_I2S_OUT_CASE)
    codec_adc_rx_i2s_tx_path_test();
#elif (AUDIO_MODE_SEL == I2S_IN_LINE_OUT_CASE)
    i2s_rx_codec_dac_stereo_tx_path_test();
#endif
    while (1);
}

void main_loop(void)
{

}
#endif

/********************************************************************************************************
 * @file    app_pdm.c
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
#if (AUDIO_MODE == PDM_DEMO)
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "modules/drv_gpio.h"
#include "inc/drv_pdm.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>

#define PDM_BLOCK_LEN  32
#define PDM_BLOCK_SIZE 256
#define PDM_RX_LEN     (PDM_BLOCK_LEN * PDM_BLOCK_SIZE)

typedef enum {
    AUDIO_BUF_EMPTY,
    AUDIO_BUF_FULL,
} e_audio_buf_stat;

typedef struct {
    uint32_t bufAddr;
    e_audio_buf_stat stat;
} block_buf_t;

uint32_t *pdm_rx_buf[PDM_RX_LEN];

volatile uint32_t g_pdm_rx_complete = 0;

block_buf_t pdm_block_buf[PDM_BLOCK_LEN];
uint32_t pdm_tdm_tx_buf[PDM_BLOCK_SIZE * 2];

static volatile uint32_t wx_index = 0;

static pdm_handle_t pdm_handle;

void pdm_msp_init(void *args);
void pdm_msp_deinit(void *args);

static void pdm_rx_complete_cb(void *args);

pdm_handle_cb_t pdm_handle_cb = {
    .rx_cplt_callback = pdm_rx_complete_cb,
    .rx_error_callback = NULL,
    .msp_init_callback = pdm_msp_init,
    .msp_deinit_callback = pdm_msp_deinit,
};

// log init
uart_handle_t uart_handle;

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
    drv_dmac_irq_handle(pdm_handle.hdma_rx);
}
PLIC_ISR_REGISTER(AUDIO_DMA_IRQHandler, IRQ_AUDIO_DMA)

void audio_buf_init(block_buf_t *block_base, uint32_t buf_base, uint32_t block_size, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        block_base[i].bufAddr = buf_base + block_size * i;
        block_base[i].stat = AUDIO_BUF_EMPTY;
    }
}

void pdm_rx_complete_cb(void *args)
{
    (void) args;
    //soc_printf("pdm_dmarx_complete_cb\n");
    if (pdm_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
        soc_printf("audio buff full!\n");
    }
    pdm_block_buf[wx_index].stat = AUDIO_BUF_FULL;
    wx_index++;
    if (wx_index == PDM_BLOCK_LEN) {
        wx_index = 0;
        g_pdm_rx_complete = 1;
        drv_pdm_stop(&pdm_handle);
        drv_pdm_deinit(&pdm_handle);
    }
    drv_pdm_recevie_dma(&pdm_handle, (uint32_t *)(pdm_block_buf[wx_index].bufAddr + MCUA_SYS_BUS_BASE), PDM_BLOCK_SIZE);
}

void pdm_dma_test(void)
{
    audio_buf_init(pdm_block_buf, (uint32_t)pdm_rx_buf, PDM_BLOCK_SIZE * sizeof(int), PDM_BLOCK_LEN);
    pdm_handle.instance = PDM1;
    pdm_handle.init.chl = PDM_MODE_STEREO;
    pdm_handle.init.pcmwidth = PDM_WD_16BIT;
    pdm_handle.init.store_mode = PDM_FIFO_STORE_INTERTWINE;
    pdm_handle.init.sampledge = PDM_SAMPLEDGE_RISE;
    pdm_handle.init.audio_fre = 16000;
    drv_pdm_register_cb(&pdm_handle, &pdm_handle_cb);
    drv_pdm_init(&pdm_handle);
    drv_pdm_recevie_dma(&pdm_handle, (uint32_t *)(pdm_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), PDM_BLOCK_SIZE);
    drv_pdm_start(&pdm_handle);

    while (wx_index < PDM_BLOCK_LEN / 2) {};
}

void pdm_msp_init(void *args)
{
    pdm_handle_t *hpdm = (pdm_handle_t *)args;
    /* Mclk1 enable */
    __DRV_CPR_MCLK1_CLK_ENABLE();

    /* Audio apb clk enable */
    __DRV_CPR_AUDIO_APB_CLK_ENABLE();

    /* Audio dma clk enable */
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();

    static dmac_handle_t pdm_dmac_handle;
    memset(&pdm_dmac_handle, 0, sizeof(dmac_handle_t));
    pdm_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    pdm_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    pdm_dmac_handle.init.dst_burst_size = DMAC_MSIZE_1;
    pdm_dmac_handle.init.src_burst_size = DMAC_MSIZE_1;
    pdm_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_32BITS;
    pdm_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_32BITS;
    pdm_dmac_handle.init.fifo_mode = DRV_SET;
    pdm_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    pdm_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    pdm_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_HARD;

    pdm_dmac_handle.init.channel = AUDIO_DMAC_CH0;
    pdm_dmac_handle.instance = AUDIO_DMAC;

    if (hpdm->instance == PDM0) {
        /* Enable pdm0 mclk and apb clk*/
        __DRV_CPR_PDM0_CLK_ENABLE();

        /* div = mclk1 /(sample_rate * 256) - 1 */
        uint32_t pdm_mclk_div = drv_cpr_get_mclk1_freq() / (hpdm->init.audio_fre * 256) - 1;
        drv_cpr_pdm0_mclk_config(pdm_mclk_div);

        /* Init GPIO pinmux */
        gpio_init_t gpio_init;
        gpio_init.port = GPIO_PORT_B;
        /* PB4: pdm0 clk, PB5: pdm0 data*/
        gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5;
        gpio_init.mode = MODE_AF;
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
        drv_gpio_init(&gpio_init);
        soc_printf("PB4: pdm0 clock, PB5: pdm0 data\n");

        /* Enable soc int */
        drv_hw_int_enable(PDM0_IRQn);

        pdm_dmac_handle.init.src_hs_num = AUDIO_DMAC_HS_PDM0;
    }
    if (hpdm->instance == PDM1) {
        /* Enable pdm1 mclk and apb clk*/
        __DRV_CPR_PDM1_CLK_ENABLE();

        /* div = mclk1 /(sample_rate * 256) - 1 */
        uint32_t pdm_mclk_div = drv_cpr_get_mclk1_freq() / (hpdm->init.audio_fre * 256) - 1;
        drv_cpr_pdm1_mclk_config(pdm_mclk_div);

        /* Init GPIO pinmux */
        gpio_init_t gpio_init;
        gpio_init.port = GPIO_PORT_B;
        /* PB8: pdm1 clk, PB9: pdm1 data*/
        gpio_init.pin = GPIO_PIN_8 | GPIO_PIN_9;
        gpio_init.mode = MODE_AF;
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.alternate = GPIO_ALTERNATE_FUNC_8;
        drv_gpio_init(&gpio_init);
        soc_printf("PB8: pdm1 clock, PB9: pdm1 data!\n");

        /* Enable soc int */
        drv_hw_int_enable(PDM1_IRQn);

        pdm_dmac_handle.init.src_hs_num = AUDIO_DMAC_HS_PDM1;
    }

    drv_dmac_init(&pdm_dmac_handle);

    __DRV_LINKDMA(hpdm, hdma_rx, pdm_dmac_handle);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
}

void pdm_msp_deinit(void *args)
{
    pdm_handle_t *hpdm = (pdm_handle_t *)args;
    if (hpdm->instance == PDM0) {
        /* Deinit GPIO pinmux */
        gpio_init_t gpio_init;
        gpio_init.port = GPIO_PORT_B;
        /* PB4: pdm0 clk, PB5: pdm0 data*/
        gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5;
        gpio_init.mode = MODE_AF;
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
        drv_gpio_init(&gpio_init);

        /* Disable soc int */
        drv_hw_int_disable(PDM0_IRQn);

        /* Disable pdm0 mclk and apb clk */
        __DRV_CPR_PDM0_CLK_DISABLE();
    }
    if (hpdm->instance == PDM1) {
        /* Deinit GPIO pinmux */
        gpio_init_t gpio_init;
        gpio_init.port = GPIO_PORT_B;
        /* PB8: pdm1 clk, PB9: pdm1 data*/
        gpio_init.pin = GPIO_PIN_8 | GPIO_PIN_9;
        gpio_init.mode = MODE_AF;
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.alternate = GPIO_ALTERNATE_DEFAULT;
        drv_gpio_init(&gpio_init);

        /* Disable soc int */
        drv_hw_int_disable(PDM1_IRQn);

        /* Disable pdm1 mclk and apb clk */
        __DRV_CPR_PDM1_CLK_DISABLE();
    }

    /* Audio apb clk disable */
    __DRV_CPR_AUDIO_APB_CLK_DISABLE();

    /* Mclk1 disable */
    __DRV_CPR_MCLK1_CLK_DISABLE();
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
}

void user_init(void)
{
    core_interrupt_enable();
    bsp_init();
    soc_printf("PDM Test!\n");
    pdm_dma_test();
    while (1) {

    }
}
void main_loop(void)
{

}
#endif

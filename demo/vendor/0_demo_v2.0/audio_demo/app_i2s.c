/********************************************************************************************************
 * @file    app_i2s.c
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
#if (AUDIO_MODE == I2S_DEMO)
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "modules/drv_gpio.h"
#include "hal/hal_audio.h"
#include "inc/drv_tdm.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>

#define I2S_MODE_X_DATA_LINE       (1) //Using two I2S port, MASTER send data using x lines, SLAVE receive data from x lines, and check data; (x:1,2,3,4)
                                       //Connect MASTER SCLK,WS,SDIO with SLAVE
#define I2S_MODE_RX_TX_LOOP        (2) //Using one I2S port, RX receive data from AP stored in buff and TX send data to AP from buff

#define I2S_MODE_SEL               I2S_MODE_RX_TX_LOOP

#define USE_16BIT                  0

#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
#define X_DATA_LINE                1
#define TDM_TEST_PORT_TX           0//TDM0
#define TDM_TEST_PORT_RX           2//TDM2
#define USE_TDM_MODE               0//0:I2S mode, 1:TDM mode
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
#define USE_TDM_MODE               0//0:I2S mode, 1:TDM mode
#define TDM_TEST_PORT              1//TDM0
//set TDM_TX_BLOCK_NUM and TDM_TX_BLOCK_NUM to 1 when use TDM_DMA_LLP_EN=1 demo, otherwise, you need update LLP head set and LLP node set code
#define TDM_DMA_LLP_EN             1//0: DMA interrupt mode, 1: DMA chain mode;
#endif

#define TDM_TX_BLOCK_NUM           1
#define TDM_TX_BLOCK_SIZE          768 * 4
#define TDM_TX_LEN                 (TDM_TX_BLOCK_NUM * TDM_TX_BLOCK_SIZE)

#define TDM_RX_BLOCK_NUM           1
#define TDM_RX_BLOCK_SIZE          768 * 4
#define TDM_RX_LEN                 (TDM_RX_BLOCK_NUM * TDM_RX_BLOCK_SIZE)

#define SAMPLE_RATE                48000

/* It is recommended to set the bit width and slot width to the same value.
 * If they are mismatched, for example, if the slot width is set to 28 bits while the bit width is 24 bits, the data format in the buffer will be 0x0FFFFFF0.
 * If both are set to 24 bits, the buffer data format will be 0x00FFFFFF. If using 16 bits, set the macro USE_16BIT to 1, otherwise the data format in the buffer will be 0x0000FFFF.
 */
#define BIT_WIDTH                  TDM_SLOT_RESOLUTION_32_BITS
#define SLOT_WIDTH                 TDM_SLOT_W_32_BITS

#if (USE_TDM_MODE == 1)
#define WS_POLARITY                TDM_WS_ALIG_TO_SCLK_N_EDGE
#define WS_FORMAT                  TDM_WS_FORMAT_STANDARD_DSP
#else
#define WS_POLARITY                TDM_WS_0_LEFT_CH_WS_1_RIGHT_CH
#define WS_FORMAT                  TDM_WS_FORMAT_I2S_STANDARD
#endif

#define SCLK_POLARITY              TDM_SCLK_DRV_DATA_AT_P_EDGE

typedef enum {
    AUDIO_BUF_EMPTY,
    AUDIO_BUF_FULL,
} e_audio_buf_stat;

typedef struct {
    uint32_t bufAddr;
    e_audio_buf_stat stat;
} block_buf_t;

static volatile uint32_t rx_index = 0;
static volatile uint32_t wx_index = 0;

static void tdm_dma_tx_complete_cb(void *args);
static void tdm_dma_rx_complete_cb(void *args);

uint32_t zore_buf[TDM_TX_BLOCK_SIZE] = {0};

#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
uint32_t tdm_tx_buf[TDM_TX_LEN];
uint32_t tdm_rx_buf[TDM_RX_LEN];
block_buf_t tdm_tx_block_buf[TDM_TX_BLOCK_NUM];
block_buf_t tdm_rx_block_buf[TDM_RX_BLOCK_NUM];
static volatile uint32_t g_tdm_rx_complete = 0;
static volatile uint32_t g_tdm_tx_complete = 0;
static tdm_handle_t i2s_rx_handle;
static tdm_handle_t i2s_tx_handle;
static void tdm_rx_msp_init(void *args);
static void tdm_tx_msp_init(void *args);
tdm_handle_cb_t tdm_rx_handle_cb = {
    .tx_cplt_callback = NULL,
    .tx_error_callback = NULL,
    .rx_cplt_callback = tdm_dma_rx_complete_cb,
    .rx_error_callback = NULL,
    .msp_init_callback = tdm_rx_msp_init,
    .msp_deinit_callback = NULL,
};
tdm_handle_cb_t tdm_tx_handle_cb = {
    .tx_cplt_callback = tdm_dma_tx_complete_cb,
    .tx_error_callback = NULL,
    .rx_cplt_callback = NULL,
    .rx_error_callback = NULL,
    .msp_init_callback = tdm_tx_msp_init,
    .msp_deinit_callback = NULL,
};
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
uint32_t tdm_buf[TDM_RX_LEN];
block_buf_t tdm_block_buf[TDM_TX_BLOCK_NUM];
static tdm_handle_t i2s_rx_tx_handle;
static void tdm_rx_tx_msp_init(void *args);
tdm_handle_cb_t tdm_rx_tx_handle_cb = {
    .tx_cplt_callback = tdm_dma_tx_complete_cb,
    .tx_error_callback = NULL,
    .rx_cplt_callback = tdm_dma_rx_complete_cb,
    .rx_error_callback = NULL,
    .msp_init_callback = tdm_rx_tx_msp_init,
    .msp_deinit_callback = NULL,
};
#if TDM_DMA_LLP_EN
/* DMA Linked List Descriptors */
dmac_llp_node_t tdm_rx_dmac_llp_list[TDM_RX_BLOCK_NUM];  /* DMA LLPs for receive */
dmac_llp_node_t tdm_tx_dmac_llp_list[TDM_TX_BLOCK_NUM];  /* DMA LLPs for transmission */
#endif

#endif

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

void tdm_audio_buf_init(block_buf_t *block_base, uint32_t buf_base, uint32_t block_size, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        block_base[i].bufAddr = buf_base + block_size * i;
        block_base[i].stat = AUDIO_BUF_EMPTY;
    }
}

void AUDIO_DMA_IRQHandler(void)
{
#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
    drv_dmac_irq_handle(i2s_tx_handle.hdma_tx);
    drv_dmac_irq_handle(i2s_rx_handle.hdma_rx);
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
    drv_dmac_irq_handle(i2s_rx_tx_handle.hdma_tx);
    drv_dmac_irq_handle(i2s_rx_tx_handle.hdma_rx);
#endif
}
PLIC_ISR_REGISTER(AUDIO_DMA_IRQHandler, IRQ_AUDIO_DMA)

void tdm_dma_tx_complete_cb(void *args)
{
    (void) args;
    //soc_printf("tdm_dma_tx_complete_cb:%d\n", rx_index);
#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
    if (tdm_tx_block_buf[rx_index].stat == AUDIO_BUF_EMPTY) {
        //soc_printf("t*******audio buff empty!\n");
        drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)(zore_buf[0] + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
    }
    tdm_tx_block_buf[rx_index].stat = AUDIO_BUF_EMPTY;
    rx_index++;
    if (rx_index == TDM_TX_BLOCK_NUM) {
        rx_index = 0;
        g_tdm_tx_complete = 1;
        soc_printf("tdm_dmatx_complete_cb!\n");
    }
    else
        drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)(tdm_tx_block_buf[rx_index].bufAddr + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
   if (tdm_block_buf[rx_index].stat == AUDIO_BUF_EMPTY) {
       //soc_printf("t*******audio buff empty!\n");
       drv_tdm_transfer_dma(&i2s_rx_tx_handle, (uint32_t *)(zore_buf[0] + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
   }
   tdm_block_buf[rx_index].stat = AUDIO_BUF_EMPTY;
   rx_index++;
   if (rx_index == TDM_TX_BLOCK_NUM) {
       rx_index = 0;
   }
    drv_tdm_transfer_dma(&i2s_rx_tx_handle, (uint32_t *)(tdm_block_buf[rx_index].bufAddr + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
#endif

}
void tdm_dma_rx_complete_cb(void *args)
{
    (void) args;
    //soc_printf("tdm_dmarx_complete_cb:%d\n", wx_index);
#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
    if (tdm_rx_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
        //soc_printf("r********audio buff full!\n");
    }
    tdm_rx_block_buf[wx_index].stat = AUDIO_BUF_FULL;
    wx_index++;
    if (wx_index == TDM_RX_BLOCK_NUM) {
        wx_index = 0;
        g_tdm_rx_complete = 1;
        soc_printf("tdm_dmarx_complete_cb!\n");
    }
    else
        drv_tdm_recevie_dma(&i2s_rx_handle, (uint32_t *)(tdm_rx_block_buf[wx_index].bufAddr + MCUA_SYS_BUS_BASE), TDM_RX_BLOCK_SIZE);
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
   if (tdm_block_buf[wx_index].stat == AUDIO_BUF_FULL) {
       //soc_printf("r********audio buff full!\n");
   }
   tdm_block_buf[wx_index].stat = AUDIO_BUF_FULL;
   wx_index++;
   if (wx_index == TDM_RX_BLOCK_NUM) {
       wx_index = 0;
   }
    drv_tdm_recevie_dma(&i2s_rx_tx_handle, (uint32_t *)(tdm_block_buf[wx_index].bufAddr + MCUA_SYS_BUS_BASE), TDM_RX_BLOCK_SIZE);
#endif
}
#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
static void tdm_rx_msp_init(void *args)
{
    tdm_handle_t *tdm_handle = (tdm_handle_t *)args;
    /* Mclk1 enable */
    __DRV_CPR_MCLK1_CLK_ENABLE();

    /* Audio apb clk enable */
    __DRV_CPR_AUDIO_APB_CLK_ENABLE();

    /* Audio dma clk enable */
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();

    /* config clkout0 */
    drv_cpr_tdm_clkout0_config(0);

    /* config tdm mclk from clkout0, sclk = slot_width * audio_fre * 2channel*/
    uint32_t i2s_sclk_div = drv_cpr_get_mclk1_freq() / ((tdm_handle->init.slot_width + 1) * 4 * 2 * tdm_handle->init.audio_fre) - 1;
#if (TDM_TEST_PORT_RX == 0)
    drv_cpr_tdm0_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM0_CLK_ENABLE();
#elif (TDM_TEST_PORT_RX == 1)
    drv_cpr_tdm1_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM1_CLK_ENABLE();
#elif (TDM_TEST_PORT_RX == 2)
    drv_cpr_tdm2_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM2_CLK_ENABLE();
#else
    drv_cpr_tdm3_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM3_CLK_ENABLE();
#endif
    /* config clkout0 enable*/
    __DRV_CPR_CLOCKOUT0_ENABLE();

    /* Init GPIO pinmux */
    gpio_init_t gpio_init;
#if (TDM_TEST_PORT_RX == 0)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_6;
#if (X_DATA_LINE == 1)
    /* PA6: sclk, PA7: ws, PA8: ch0 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
#elif (X_DATA_LINE == 2)
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
#elif (X_DATA_LINE == 3)
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 PA17: ch2 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_17;
#else
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 PA17: ch2 PA18: ch3 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_17 | GPIO_PIN_18;
#endif
#elif (TDM_TEST_PORT_RX == 1)
    gpio_init.port = GPIO_PORT_B;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
#if (X_DATA_LINE == 1)
    /* PB2: sclk, PB3: ws, PB0: ch0 */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
#elif (X_DATA_LINE == 2)
    /* PB2: sclk, PB3: ws, PB0: ch0 PB1: ch1 */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1;
#endif
#elif (TDM_TEST_PORT_RX == 2)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_11;
#if (X_DATA_LINE == 1)
    /* PA4: sclk, PA5: ws, PA2: ch0 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2;
#elif (X_DATA_LINE == 2)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#elif (X_DATA_LINE == 3)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA19: ch2 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_19;
#else
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA19: ch2 PA20: ch3 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_19 | GPIO_PIN_20;
#endif
#else
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_4;
#if (X_DATA_LINE == 1)
    /* PA4: sclk, PA5: ws, PA2: ch0 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2;
#elif (X_DATA_LINE == 2)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#elif (X_DATA_LINE == 3)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA0: ch2 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
#else
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA0: ch2 PA1: ch3 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1;
#endif
#endif
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    drv_gpio_init(&gpio_init);

    static dmac_handle_t tdm_rx_dmac_handle;
    memset(&tdm_rx_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm_rx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm_rx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm_rx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm_rx_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT)
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

    tdm_rx_dmac_handle.init.src_hs_num = AUDIO_DMAC_HS_I2S0_RX + TDM_TEST_PORT_RX;

    tdm_rx_dmac_handle.init.channel = AUDIO_DMAC_CH0;
    tdm_rx_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm_rx_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_rx, tdm_rx_dmac_handle);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
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

    /* config clkout0 */
    drv_cpr_tdm_clkout0_config(0);

    /* config tdm mclk from clkout0, sclk = slot_width * audio_fre * 2channel*/
    uint32_t i2s_sclk_div = drv_cpr_get_mclk1_freq() / ((tdm_handle->init.slot_width + 1) * 4 * 2 * tdm_handle->init.audio_fre) - 1;
#if (TDM_TEST_PORT_TX == 0)
    drv_cpr_tdm0_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM0_CLK_ENABLE();
#elif (TDM_TEST_PORT_TX == 1)
    drv_cpr_tdm1_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM1_CLK_ENABLE();
#elif (TDM_TEST_PORT_TX == 2)
    drv_cpr_tdm2_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM2_CLK_ENABLE();
#else
    drv_cpr_tdm3_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM3_CLK_ENABLE();
#endif
    /* config clkout0 enable*/
    __DRV_CPR_CLOCKOUT0_ENABLE();

    /* Init GPIO pinmux */
    gpio_init_t gpio_init;
    gpio_init.pull = GPIO_PULLUP;
#if (TDM_TEST_PORT_TX == 0)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_6;
#if (X_DATA_LINE == 1)
    /* PA6: sclk, PA7: ws, PA8: ch0 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
#elif (X_DATA_LINE == 2)
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
#elif (X_DATA_LINE == 3)
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 PA17: ch2 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_17;
#else
    /* PA6: sclk, PA7: ws, PA8: ch0 PA9: ch1 PA17: ch2 PA18: ch3 */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_17 | GPIO_PIN_18;
#endif
#elif (TDM_TEST_PORT_TX == 1)
    gpio_init.port = GPIO_PORT_B;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
#if (X_DATA_LINE == 1)
    /* PB2: sclk, PB3: ws, PB0: ch0 */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
#elif (X_DATA_LINE == 2)
    /* PB2: sclk, PB3: ws, PB0: ch0 PB1: ch1 */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1;
#endif
#elif (TDM_TEST_PORT_TX == 2)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_11;
#if (X_DATA_LINE == 1)
    /* PA4: sclk, PA5: ws, PA2: ch0 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2;
#elif (X_DATA_LINE == 2)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#elif (X_DATA_LINE == 3)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA19: ch2 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_19;
#else
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA19: ch2 PA20: ch3 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_19 | GPIO_PIN_20;
#endif
#else
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_4;
#if (X_DATA_LINE == 1)
    /* PA4: sclk, PA5: ws, PA2: ch0 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2;
#elif (X_DATA_LINE == 2)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#elif (X_DATA_LINE == 3)
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA0: ch2 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
#else
    /* PA4: sclk, PA5: ws, PA2: ch0 PA3: ch1 PA0: ch2 PA1: ch3 */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1;
#endif
#endif
    drv_gpio_init(&gpio_init);

    static dmac_handle_t tdm_tx_dmac_handle;
    memset(&tdm_tx_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm_tx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm_tx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm_tx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm_tx_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT)
    tdm_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_16BITS;
    tdm_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_16BITS;
#else
    tdm_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_32BITS;
    tdm_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_32BITS;
#endif
    tdm_tx_dmac_handle.init.fifo_mode = DRV_SET;
    tdm_tx_dmac_handle.init.trans_mode = DMAC_CTL_TT_MEM2PER;
    tdm_tx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_HARD;
    tdm_tx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    tdm_tx_dmac_handle.init.dst_hs_num = AUDIO_DMAC_HS_I2S0_TX + TDM_TEST_PORT_TX;

    tdm_tx_dmac_handle.init.channel = AUDIO_DMAC_CH1;
    tdm_tx_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm_tx_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_tx, tdm_tx_dmac_handle);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
}

void tdm_i2s_tx_rx_xline_dma_mode(void)
{
    unsigned int val = 1<<(BIT_WIDTH*4);
    tdm_audio_buf_init(tdm_tx_block_buf, (uint32_t)tdm_tx_buf, TDM_TX_BLOCK_SIZE * sizeof(int), TDM_TX_BLOCK_NUM);
    tdm_audio_buf_init(tdm_rx_block_buf, (uint32_t)tdm_rx_buf, TDM_RX_BLOCK_SIZE * sizeof(int), TDM_RX_BLOCK_NUM);
    for (uint32_t i = 0; i < TDM_TX_LEN; i++)
    {
        tdm_tx_buf[i] = ((val<<(i % X_DATA_LINE)) + i/X_DATA_LINE); /* i+ channel */
        if (BIT_WIDTH == 1) //when BIT_WIDTH is 8bit
            tdm_tx_buf[i] = tdm_tx_buf[i] & 0xFF;
        tdm_rx_buf[i] = 0x5a;                                       /* for test flag */
    }

    memset(&i2s_rx_handle, 0, sizeof(i2s_rx_handle));
#if (TDM_TEST_PORT_RX == 0)
    i2s_rx_handle.instance = TDM0;
#elif (TDM_TEST_PORT_RX == 1)
    i2s_rx_handle.instance = TDM1;
#elif (TDM_TEST_PORT_RX == 2)
    i2s_rx_handle.instance = TDM2;
#else
    i2s_rx_handle.instance = TDM3;
#endif
    i2s_rx_handle.init.mode = I2S_MODE;
    i2s_rx_handle.init.master_mode = TDM_SLAVE_MODE;
    i2s_rx_handle.init.sclk_polarity = SCLK_POLARITY;
    i2s_rx_handle.init.slot_resolution = BIT_WIDTH;
    i2s_rx_handle.init.slot_width = SLOT_WIDTH;
#if (X_DATA_LINE == 1)
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_RX;
#elif (X_DATA_LINE == 2)
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_RX | TDM_LINE1_RX;
#elif (X_DATA_LINE == 3)
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN | TDM_LINE2_EN;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_RX | TDM_LINE1_RX | TDM_LINE2_RX;
#else
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN | TDM_LINE2_EN | TDM_LINE3_EN;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_RX | TDM_LINE1_RX | TDM_LINE2_RX | TDM_LINE3_RX;
#endif
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ws_format = WS_FORMAT;
    i2s_rx_handle.init.mode_cfg.i2s_cfg.ws_polarity = WS_POLARITY;
    i2s_rx_handle.init.audio_fre = SAMPLE_RATE;
    drv_tdm_register_cb(&i2s_rx_handle, &tdm_rx_handle_cb);
    drv_tdm_init(&i2s_rx_handle);
    memset(&i2s_tx_handle, 0, sizeof(i2s_tx_handle));
#if (TDM_TEST_PORT_TX == 0)
    i2s_tx_handle.instance = TDM0;
#elif (TDM_TEST_PORT_TX == 1)
    i2s_tx_handle.instance = TDM1;
#elif (TDM_TEST_PORT_TX == 2)
    i2s_tx_handle.instance = TDM2;
#else
    i2s_tx_handle.instance = TDM3;
#endif
    i2s_tx_handle.init.mode = I2S_MODE;
    i2s_tx_handle.init.master_mode = TDM_MASTER_MODE;
    i2s_tx_handle.init.sclk_polarity = SCLK_POLARITY;
    i2s_tx_handle.init.slot_resolution = BIT_WIDTH;
    i2s_tx_handle.init.slot_width = SLOT_WIDTH;
#if (X_DATA_LINE == 1)
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX;
#elif (X_DATA_LINE == 2)
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX | TDM_LINE1_TX;
#elif (X_DATA_LINE == 3)
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN | TDM_LINE2_EN;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX | TDM_LINE1_TX | TDM_LINE2_TX;
#else
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN | TDM_LINE2_EN | TDM_LINE3_EN;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX | TDM_LINE1_TX | TDM_LINE2_TX | TDM_LINE3_TX;
#endif
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ws_format = WS_FORMAT;
    i2s_tx_handle.init.mode_cfg.i2s_cfg.ws_polarity = WS_POLARITY;
    i2s_tx_handle.init.audio_fre = SAMPLE_RATE;
    drv_tdm_register_cb(&i2s_tx_handle, &tdm_tx_handle_cb);
    drv_tdm_init(&i2s_tx_handle);
    drv_tdm_transfer_dma(&i2s_tx_handle, (uint32_t *)(tdm_tx_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
    drv_tdm_recevie_dma(&i2s_rx_handle, (uint32_t *)(tdm_rx_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), TDM_RX_BLOCK_SIZE);
    drv_tdm_start(&i2s_tx_handle);
    drv_tdm_start(&i2s_rx_handle);
    while (!g_tdm_tx_complete){};
    g_tdm_tx_complete = 0;
    while (!g_tdm_rx_complete){};
    g_tdm_rx_complete = 0;
    uint32_t check_count = 0;
    uint32_t offset = 0;
    while (tdm_tx_buf[offset] != tdm_rx_buf[0])
    {
        offset++;
        if (offset == TDM_TX_LEN)
        {
            break;
        }
    }

    for (uint32_t i = offset; i < TDM_TX_LEN - offset; i++)
    {
        if(tdm_tx_buf[i+offset] != tdm_rx_buf[i]) {
            soc_printf("test err rx_buf[%d]:0x%x, tx_buf[%d]:0x%x, 0x%x\n", i, tdm_rx_buf[i], i, tdm_tx_buf[i], &tdm_rx_buf[i]);
        }
        else
        {
            check_count++;
        }
    }
    if(offset < 8)
        soc_printf("%d line data transfer test ok, offset %d\n", X_DATA_LINE, offset);
    else
        soc_printf("%d line data transfer test err, offset %d\n", X_DATA_LINE, offset);

    drv_tdm_stop(&i2s_tx_handle);
    drv_tdm_stop(&i2s_rx_handle);
}
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
static void tdm_rx_tx_msp_init(void *args)
{
    tdm_handle_t *tdm_handle = (tdm_handle_t *)args;
    uint32_t clkout0 = 6144000;
    uint32_t clkout0_div = drv_cpr_get_mclk1_freq() / clkout0 - 1;

    /* Mclk1 enable */
    __DRV_CPR_MCLK1_CLK_ENABLE();

    /* Audio apb clk enable */
    __DRV_CPR_AUDIO_APB_CLK_ENABLE();

    /* Audio dma clk enable */
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();

    /* config clkout0 */
    drv_cpr_tdm_clkout0_config(clkout0_div);

    /* config tdm mclk from clkout0, sclk = slot_width * audio_fre * 2channel*/
#if (USE_TDM_MODE == 1)
    uint32_t i2s_sclk_div = clkout0 / ((tdm_handle->init.slot_width + 1) * 4 * (tdm_handle->init.mode_cfg.tdm_cfg.slot_num + 1) * tdm_handle->init.audio_fre) - 1;
#else
    uint32_t i2s_sclk_div = clkout0 / ((tdm_handle->init.slot_width + 1) * 4 * 2 * tdm_handle->init.audio_fre) - 1;
#endif
#if (TDM_TEST_PORT == 0)
    drv_cpr_tdm0_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM0_CLK_ENABLE();
#elif (TDM_TEST_PORT == 1)
    drv_cpr_tdm1_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM1_CLK_ENABLE();
#elif (TDM_TEST_PORT == 2)
    drv_cpr_tdm2_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM2_CLK_ENABLE();
#else
    drv_cpr_tdm3_mclk_config(i2s_sclk_div);
    __DRV_CPR_TDM3_CLK_ENABLE();
#endif
    /* config clkout0 enable*/
    __DRV_CPR_CLOCKOUT0_ENABLE();

    /* Init GPIO pinmux */
    gpio_init_t gpio_init;
#if (TDM_TEST_PORT == 0)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_6;
    /* PA6: sclk, PA7: ws, PA8: ch0-tx PA9: ch1-rx */
    gpio_init.pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
#elif (TDM_TEST_PORT == 1)
    gpio_init.port = GPIO_PORT_B;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_5;
    /* PB2: sclk, PB3: ws, PB0: ch0-tx PB1: ch1-rx */
    gpio_init.pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1;
#elif (TDM_TEST_PORT == 2)
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_11;
    /* PA4: sclk, PA5: ws, PA2: ch0-tx PA3: ch1-rx */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#else
    gpio_init.port = GPIO_PORT_A;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_4;
    /* PA4: sclk, PA5: ws, PA2: ch0-tx PA3: ch1-rx */
    gpio_init.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
#endif
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    drv_gpio_init(&gpio_init);

    static dmac_handle_t tdm_rx_dmac_handle;
    memset(&tdm_rx_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm_rx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm_rx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm_rx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm_rx_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT)
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

    tdm_rx_dmac_handle.init.src_hs_num = AUDIO_DMAC_HS_I2S0_RX + TDM_TEST_PORT;

#if TDM_DMA_LLP_EN
    tdm_rx_dmac_handle.init.src_llp_en = DRV_SET;                        /* Enable source linked list */
    tdm_rx_dmac_handle.init.dst_llp_en = DRV_SET;                        /* Enable destination linked list */
#endif

    tdm_rx_dmac_handle.init.channel = AUDIO_DMAC_CH0;
    tdm_rx_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm_rx_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_rx, tdm_rx_dmac_handle);

    static dmac_handle_t tdm_tx_dmac_handle;
    memset(&tdm_tx_dmac_handle, 0, sizeof(dmac_handle_t));
    tdm_tx_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_CONSTANT;
    tdm_tx_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    tdm_tx_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    tdm_tx_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
#if (USE_16BIT)
    tdm_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_16BITS;
    tdm_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_16BITS;
#else
    tdm_tx_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_32BITS;
    tdm_tx_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_32BITS;
#endif
    tdm_tx_dmac_handle.init.fifo_mode = DRV_SET;
    tdm_tx_dmac_handle.init.trans_mode = DMAC_CTL_TT_MEM2PER;
    tdm_tx_dmac_handle.init.dst_hs_mode = DMAC_CFG_HS_SEL_HARD;
    tdm_tx_dmac_handle.init.src_hs_mode = DMAC_CFG_HS_SEL_SOFT;
    tdm_tx_dmac_handle.init.dst_hs_num = AUDIO_DMAC_HS_I2S0_TX + TDM_TEST_PORT;

#if TDM_DMA_LLP_EN
    tdm_tx_dmac_handle.init.src_llp_en = DRV_SET;                        /* Enable source linked list */
    tdm_tx_dmac_handle.init.dst_llp_en = DRV_SET;                        /* Enable destination linked list */
#endif

    tdm_tx_dmac_handle.init.channel = AUDIO_DMAC_CH1;
    tdm_tx_dmac_handle.instance = AUDIO_DMAC;

    drv_dmac_init(&tdm_tx_dmac_handle);

    __DRV_LINKDMA(tdm_handle, hdma_tx, tdm_tx_dmac_handle);

    drv_hw_int_enable(AUDIO_DMA_IRQn);
}

__attribute__((used)) unsigned int rxdma_index0 = 0;
__attribute__((used)) unsigned int rxdma_index1 = 0;
__attribute__((used)) unsigned int txdma_index0 = 0;
__attribute__((used)) unsigned int txdma_index1 = 0;

void tdm_i2s_rx_tx_loop_dma_mode(void)
{
    tdm_audio_buf_init(tdm_block_buf, (uint32_t)tdm_buf, TDM_TX_BLOCK_SIZE * sizeof(int), TDM_TX_BLOCK_NUM);

    memset(&i2s_rx_tx_handle, 0, sizeof(i2s_rx_tx_handle));
#if (TDM_TEST_PORT == 0)
    i2s_rx_tx_handle.instance = TDM0;
#elif (TDM_TEST_PORT == 1)
    i2s_rx_tx_handle.instance = TDM1;
#elif (TDM_TEST_PORT == 2)
    i2s_rx_tx_handle.instance = TDM2;
#else
    i2s_rx_tx_handle.instance = TDM3;
#endif
#if (USE_TDM_MODE == 1)
    i2s_rx_tx_handle.init.mode = TDM_MODE;
#else
    i2s_rx_tx_handle.init.mode = I2S_MODE;
#endif
    i2s_rx_tx_handle.init.master_mode = TDM_MASTER_MODE;
    i2s_rx_tx_handle.init.sclk_polarity = SCLK_POLARITY;
    i2s_rx_tx_handle.init.slot_resolution = BIT_WIDTH;
    i2s_rx_tx_handle.init.slot_width = SLOT_WIDTH;
#if (USE_TDM_MODE == 1)
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.slot_num = TDM_8_SLOT_USED;
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.tx_en = DRV_SET;
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.rx_en = DRV_SET;
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.ws_format = WS_FORMAT;
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.ws_polarity = WS_POLARITY;
    i2s_rx_tx_handle.init.mode_cfg.tdm_cfg.ws_width = TDM_WS_SIGNAL_1_SCLK_CYCLE;
#else
    i2s_rx_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_en  = TDM_LINE0_EN | TDM_LINE1_EN;
    i2s_rx_tx_handle.init.mode_cfg.i2s_cfg.ch_cfg.ch_trx = TDM_LINE0_TX | TDM_LINE1_RX;
    i2s_rx_tx_handle.init.mode_cfg.i2s_cfg.ws_format = WS_FORMAT;
    i2s_rx_tx_handle.init.mode_cfg.i2s_cfg.ws_polarity = WS_POLARITY;
#endif
    i2s_rx_tx_handle.init.audio_fre = SAMPLE_RATE;
    drv_tdm_register_cb(&i2s_rx_tx_handle, &tdm_rx_tx_handle_cb);
    drv_tdm_init(&i2s_rx_tx_handle);

#if TDM_DMA_LLP_EN
    /* Configure DMA linked list for transmission */
    drv_tdm_transfer_dma_llp_head_set(&i2s_rx_tx_handle, &tdm_tx_dmac_llp_list[0]);
    drv_tdm_transfer_dma_llp_node_add(&i2s_rx_tx_handle, &tdm_tx_dmac_llp_list[0],
                                      &tdm_tx_dmac_llp_list[0],
                                      (uint32_t *)CONVERT_SYS_ADDR(tdm_buf),
                                      TDM_TX_BLOCK_SIZE);

    /* Configure DMA linked list for reception */
    drv_tdm_recevie_dma_llp_head_set(&i2s_rx_tx_handle, &tdm_rx_dmac_llp_list[0]);
    drv_tdm_recevie_dma_llp_node_add(&i2s_rx_tx_handle, &tdm_rx_dmac_llp_list[0],
                                     &tdm_rx_dmac_llp_list[0],
                                     (uint32_t *)CONVERT_SYS_ADDR(tdm_buf),
                                     TDM_RX_BLOCK_SIZE);

    /* Start DMA transfers */
    drv_tdm_transfer_dma_llp_start(&i2s_rx_tx_handle, DRV_SET);  /* Start transmitter DMA */
    drv_tdm_recevie_dma_llp_start(&i2s_rx_tx_handle, DRV_SET);   /* Start receiver DMA */
#else
    drv_tdm_recevie_dma(&i2s_rx_tx_handle, (uint32_t *)(tdm_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), TDM_RX_BLOCK_SIZE);
    drv_tdm_transfer_dma(&i2s_rx_tx_handle, (uint32_t *)(tdm_block_buf[0].bufAddr + MCUA_SYS_BUS_BASE), TDM_TX_BLOCK_SIZE);
#endif
    drv_tdm_start(&i2s_rx_tx_handle);
   // while(wx_index<(TDM_RX_BLOCK_NUM/2))

#if 0 //this code used to disable I2S, re-enable I2S again and set DMA pointer back to buff header
    rxdma_index0 = audio_get_rx_dma_wptr(i2s_rx_tx_handle.hdma_rx);
    txdma_index0 = audio_get_tx_dma_rptr(i2s_rx_tx_handle.hdma_tx);

    // stop I2S and DMA
    audio_dma_channel_disable(i2s_rx_tx_handle.hdma_rx);
    audio_dma_channel_disable(i2s_rx_tx_handle.hdma_tx);
    drv_tdm_stop(&i2s_rx_tx_handle);
    // set DMA pointer to buff header
    drv_dmac_set_dst_address(i2s_rx_tx_handle.hdma_rx, CONVERT_SYS_ADDR(tdm_buf));
    drv_dmac_set_src_address(i2s_rx_tx_handle.hdma_tx, CONVERT_SYS_ADDR(tdm_buf));
    // check the DMA pointer, not necessary, only for testing to check DMA pointer
    rxdma_index1 = audio_get_rx_dma_wptr(i2s_rx_tx_handle.hdma_rx);
    txdma_index1 = audio_get_tx_dma_rptr(i2s_rx_tx_handle.hdma_tx);
    //re-enable DMA and start I2S
    audio_dma_channel_enable(i2s_rx_tx_handle.hdma_rx);
    audio_dma_channel_enable(i2s_rx_tx_handle.hdma_tx);
    drv_tdm_start(&i2s_rx_tx_handle);
#endif
}
#endif

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
#if (I2S_MODE_SEL == I2S_MODE_X_DATA_LINE)
    tdm_i2s_tx_rx_xline_dma_mode();
#elif (I2S_MODE_SEL == I2S_MODE_RX_TX_LOOP)
    tdm_i2s_rx_tx_loop_dma_mode();
    /* Give an example for probe clkout0 as I2S mclk.(Only PA2)
     * If PA2 is used as mclk, be careful not to use it as any other function
     */
    audio_probe_clkout0_clk_as_mclk();
#endif
    while (1);
}

void main_loop(void)
{

}
#endif

/********************************************************************************************************
 * @file    dma_polling.c
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
#if (DMA_TEST_MODE == DMA_POLLING_TEST)
#include "reg/dma.h"
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>
#include "modules/drv_gpio.h"

#define BLOCK_SIZE0  (2048)
#define DMA_POLLING_TEST_TIMEOUT    (0xffffffff)

static uint8_t src_array[BLOCK_SIZE0];
static uint8_t dst_array[BLOCK_SIZE0];

static dmac_handle_t dmac_handle1;

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

static void test_data_init(void)
{
    for (uint32_t i = 0; i < BLOCK_SIZE0 / 16; i++) {
        for (uint32_t j = 0; j < 16; j++) {
            src_array[(i * 16) + j] = j;
            dst_array[(i * 16) + j] = 0;
        }
    }
}

static bool test_data_check(void)
{
    uint32_t ok_count = 0;
    for (uint32_t i = 0; i < BLOCK_SIZE0; i++) {
        if (src_array[i] == dst_array[i]) {
            ok_count++;

            if (ok_count == BLOCK_SIZE0) {
                return true;
            }
        } else {
            // return false;
            soc_printf("data_error[%x]:0x%x, src:0x%x\n", i, dst_array[i], src_array[i]);
        }
    }
    return false;
}

void dma_msp_init(void)
{
    __DRV_CPR_CPU_DMA_CLK_ENABLE();
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();
    __DRV_CPR_CPU2_DMA_CLK_ENABLE();
    __DRV_CPR_CPU1_DMA_CLK_ENABLE();
}

void dma_msp_deinit(void)
{
    __DRV_CPR_CPU_DMA_CLK_DISABLE();
    __DRV_CPR_AUDIO_DMA_CLK_DISABLE();
    __DRV_CPR_CPU2_DMA_CLK_DISABLE();
    __DRV_CPR_CPU1_DMA_CLK_DISABLE();
}

void dmac_test(dmac_reg_t *instance, uint32_t channel)
{
    soc_printf("dma module:0x%x,  channel:0x%x\n", instance, channel);
    memset(&dmac_handle1, 0, sizeof(dmac_handle_t));
    dmac_handle1.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    dmac_handle1.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    dmac_handle1.init.dst_burst_size = DMAC_MSIZE_8;
    dmac_handle1.init.src_burst_size = DMAC_MSIZE_8;
    dmac_handle1.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    dmac_handle1.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    dmac_handle1.init.fifo_mode = 1;
    dmac_handle1.init.trans_mode = DMAC_CTL_TT_MEM2MEM;
    dmac_handle1.init.channel = channel;
    dmac_handle1.instance = instance;

    drv_dmac_init(&dmac_handle1);

    test_data_init();
    drv_dmac_start(&dmac_handle1, (uint32_t)src_array + MCUA_SYS_BUS_BASE, (uint32_t)dst_array + MCUA_SYS_BUS_BASE, BLOCK_SIZE0);
    while (drv_dmac_poll_for_transfer(&dmac_handle1, DMA_POLLING_TEST_TIMEOUT) != DRV_OK)
        ;
    if (test_data_check()) {
        soc_printf("data compare is ok!\r\n\n");
    } else {
        soc_printf("data compare is error!\r\n\n");
    }
    drv_dmac_deinit(&dmac_handle1);
}

void dma_test_all_channel(void)
{
    dma_msp_init();

    soc_printf("this is dma test\n");
    dmac_test(CPU_DMAC, CPU_DMAC_CH0);
    dmac_test(CPU_DMAC, CPU_DMAC_CH1);
    dmac_test(CPU_DMAC, CPU_DMAC_CH2);
    dmac_test(CPU_DMAC, CPU_DMAC_CH3);
    dmac_test(CPU_DMAC, CPU_DMAC_CH4);
    dmac_test(CPU_DMAC, CPU_DMAC_CH5);

    dmac_test(AUDIO_DMAC, AUDIO_DMAC_CH0);
    dmac_test(AUDIO_DMAC, AUDIO_DMAC_CH1);
    dmac_test(AUDIO_DMAC, AUDIO_DMAC_CH2);
    dmac_test(AUDIO_DMAC, AUDIO_DMAC_CH3);

    dmac_test(CPU2_DMAC, CPU2_DMAC_CH0);
    dmac_test(CPU2_DMAC, CPU2_DMAC_CH1);
    dmac_test(CPU2_DMAC, CPU2_DMAC_CH2);
    dmac_test(CPU2_DMAC, CPU2_DMAC_CH3);

    dmac_test(CPU1_DMAC, CPU1_DMAC_CH0);
    dmac_test(CPU1_DMAC, CPU1_DMAC_CH1);
    dmac_test(CPU1_DMAC, CPU1_DMAC_CH2);
    dmac_test(CPU1_DMAC, CPU1_DMAC_CH3);
    dma_msp_deinit();
}
void user_init(void)
{
    core_interrupt_enable();

    log_init(); // pa0 and pa1 are used by uart 1

    drv_cpr_audio_system_powerup();

    dma_test_all_channel();
}
void main_loop(void)
{

}
#endif

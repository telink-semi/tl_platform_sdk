/********************************************************************************************************
 * @file    dma_llp.c
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
#if (DMA_TEST_MODE == DMA_LLP_TEST)
#include "reg/dma.h"
#include "inc/drv_cpr.h"
#include "inc/drv_dmac.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>
#include "modules/drv_gpio.h"

#define DMAC_LLP_INT_EN             (1)

#define DMAC_LLP_BLOCK_SIZE         (128)
#define DMAC_LLP_NUM                (4)
#define DMAC_LLP_TEST_LEN      (DMAC_LLP_NUM * DMAC_LLP_BLOCK_SIZE)
#define CUR_CPU_ADDR2_BUS_ADDR(addr) ((uint32_t)addr + MCUA_SYS_BUS_BASE)

uint8_t src_array0[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t dst_array0[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t src_array1[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t dst_array1[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t src_array2[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t dst_array2[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t src_array3[DMAC_LLP_BLOCK_SIZE]  = {0,};
uint8_t dst_array3[DMAC_LLP_BLOCK_SIZE]  = {0,};

dmac_llp_node_t dmac_llp_list[DMAC_LLP_NUM];

static volatile uint32_t finish_flag = 0;
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

static void test_llp_data_init(void)
{
    for (uint32_t i = 0; i < DMAC_LLP_BLOCK_SIZE; i++)
    {
        src_array0[i] = i + 1;
        src_array1[i] = i + 2;
        src_array2[i] = i + 3;
        src_array3[i] = i + 4;

        dst_array0[i] = 0x33;
        dst_array1[i] = 0x33;
        dst_array2[i] = 0x33;
        dst_array3[i] = 0x33;
    }
}

static void test_data(uint8_t *src, uint8_t *dst, uint32_t len, uint32_t *ok_count)
{
    (void)len;
    for (uint32_t i = 0; i < DMAC_LLP_BLOCK_SIZE; i++)
    {
        if (src[i] == dst[i]) {
            (*ok_count)++;
        } else {
            LOG_INF("data_error arr:0x%x [%x]:0x%x, dst:0x%x\n", src, i, src[i], dst[i]);
        }
    }
}

static bool test_llp_data_check(void)
{
    uint32_t ok_count = 0;
    test_data(src_array0, dst_array0, DMAC_LLP_BLOCK_SIZE, &ok_count);
    LOG_INF("ok_count:0x%x\n", ok_count);
    test_data(src_array1, dst_array1, DMAC_LLP_BLOCK_SIZE, &ok_count);
    LOG_INF("ok_count:0x%x\n", ok_count);
    test_data(src_array2, dst_array2, DMAC_LLP_BLOCK_SIZE, &ok_count);
    LOG_INF("ok_count:0x%x\n", ok_count);
    test_data(src_array3, dst_array3, DMAC_LLP_BLOCK_SIZE, &ok_count);
    LOG_INF("ok_count:0x%x\n", ok_count);
    if (ok_count == DMAC_LLP_TEST_LEN) {
        return true;
    }
    return false;
}

#if DMAC_LLP_INT_EN
static void hal_dmac_llp_irq_callback(dmac_handle_t *hdma)
{
    (void)hdma;
    finish_flag = 1;
}

void CPU_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&dmac_handle1);
}

void AUDIO_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&dmac_handle1);
}

void CPU2_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&dmac_handle1);
}

void CPU1_DMA_IRQHandler(void)
{
    drv_dmac_irq_handle(&dmac_handle1);
}

ISR_REGISTER(CPU_DMA_IRQHandler, CPU_DMA_IRQn)
ISR_REGISTER(AUDIO_DMA_IRQHandler, AUDIO_DMA_IRQn)
ISR_REGISTER(CPU2_DMA_IRQHandler, CPU2_DMA_IRQn)
ISR_REGISTER(CPU1_DMA_IRQHandler, CPU1_DMA_IRQn)
#endif

void dma_msp_init(void)
{
    __DRV_CPR_CPU_DMA_CLK_ENABLE();
    __DRV_CPR_AUDIO_DMA_CLK_ENABLE();
    __DRV_CPR_CPU2_DMA_CLK_ENABLE();
    __DRV_CPR_CPU1_DMA_CLK_ENABLE();
    #if DMAC_LLP_INT_EN
    drv_hw_int_enable(CPU_DMA_IRQn);
    drv_hw_int_enable(AUDIO_DMA_IRQn);
    drv_hw_int_enable(CPU2_DMA_IRQn);
    drv_hw_int_enable(CPU1_DMA_IRQn);
    #endif
}

void dma_msp_deinit(void)
{
    __DRV_CPR_CPU_DMA_CLK_DISABLE();
    __DRV_CPR_AUDIO_DMA_CLK_DISABLE();
    __DRV_CPR_CPU2_DMA_CLK_DISABLE();
    __DRV_CPR_CPU1_DMA_CLK_DISABLE();

    #if DMAC_LLP_INT_EN
    drv_hw_int_disable(CPU_DMA_IRQn);
    drv_hw_int_disable(AUDIO_DMA_IRQn);
    drv_hw_int_disable(CPU2_DMA_IRQn);
    drv_hw_int_disable(CPU1_DMA_IRQn);
    #endif
}

void dmac_llp_test(dmac_reg_t *instance, uint32_t channel)
{
    LOG_INF("dma module:0x%x,  channel:0x%x\n", instance, channel);
    memset(&dmac_handle1, 0, sizeof(dmac_handle_t));
    dmac_handle1.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    dmac_handle1.init.src_addr_change_mode = DMAC_ADDR_INCREASE;
    dmac_handle1.init.dst_burst_size = DMAC_MSIZE_8;
    dmac_handle1.init.src_burst_size = DMAC_MSIZE_8;
    dmac_handle1.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    dmac_handle1.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    dmac_handle1.init.fifo_mode = 1;
    dmac_handle1.init.trans_mode = DMAC_CTL_TT_MEM2MEM;
    dmac_handle1.init.src_llp_en = DRV_SET;
    dmac_handle1.init.dst_llp_en = DRV_SET;
    dmac_handle1.init.channel = channel;
    dmac_handle1.instance = instance;

    drv_dmac_init(&dmac_handle1);

    #if DMAC_LLP_INT_EN
    drv_dmac_register_cb(&dmac_handle1, DRV_DMA_XFER_CPLT_CB_ID, hal_dmac_llp_irq_callback);
    #endif
    test_llp_data_init();
    drv_dmac_llp_head_set(&dmac_handle1, &dmac_llp_list[0]);

    drv_dmac_llp_node_add(&dmac_handle1, &dmac_llp_list[0],  &dmac_llp_list[1], \
                         CUR_CPU_ADDR2_BUS_ADDR(src_array0), CUR_CPU_ADDR2_BUS_ADDR(dst_array0), DMAC_LLP_BLOCK_SIZE);

    drv_dmac_llp_node_add(&dmac_handle1, &dmac_llp_list[1], &dmac_llp_list[2], \
                         CUR_CPU_ADDR2_BUS_ADDR(src_array1), CUR_CPU_ADDR2_BUS_ADDR(dst_array1), DMAC_LLP_BLOCK_SIZE);

    drv_dmac_llp_node_add(&dmac_handle1, &dmac_llp_list[2],  &dmac_llp_list[3], \
                         CUR_CPU_ADDR2_BUS_ADDR(src_array2), CUR_CPU_ADDR2_BUS_ADDR(dst_array2), DMAC_LLP_BLOCK_SIZE);

    drv_dmac_llp_node_add(&dmac_handle1, &dmac_llp_list[3],  NULL, \
                         CUR_CPU_ADDR2_BUS_ADDR(src_array3), CUR_CPU_ADDR2_BUS_ADDR(dst_array3), DMAC_LLP_BLOCK_SIZE);

    drv_dmac_llp_start(&dmac_handle1, DRV_RESET, DRV_SET);
    #if DMAC_LLP_INT_EN
    while (0 == finish_flag)
        ;
    finish_flag = 0;
    #else
    for(int i = 0; i < DMAC_LLP_NUM; i++) {
        while(drv_dmac_llp_item_transfer_cplt(&dmac_llp_list[i]) != DRV_OK);
    }
    #endif

    __asm("fence.i");
    if (test_llp_data_check()) {
        LOG_INF("data compare is ok!\r\n\n");
    } else {
        LOG_INF("data compare is error!\r\n\n");
    }
    drv_dmac_unregister_cb(&dmac_handle1, DRV_DMA_XFER_CPLT_CB_ID);
    drv_dmac_deinit(&dmac_handle1);
}

void dma_test_all_channel(void)
{
    dma_msp_init();

    LOG_INF("this is dma test\n");
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH0);
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH1);
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH2);
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH3);
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH4);
    dmac_llp_test(CPU_DMAC, CPU_DMAC_CH5);

    dmac_llp_test(AUDIO_DMAC, AUDIO_DMAC_CH0);
    dmac_llp_test(AUDIO_DMAC, AUDIO_DMAC_CH1);
    dmac_llp_test(AUDIO_DMAC, AUDIO_DMAC_CH2);
    dmac_llp_test(AUDIO_DMAC, AUDIO_DMAC_CH3);

    dmac_llp_test(CPU2_DMAC, CPU2_DMAC_CH0);
    dmac_llp_test(CPU2_DMAC, CPU2_DMAC_CH1);
    dmac_llp_test(CPU2_DMAC, CPU2_DMAC_CH2);
    dmac_llp_test(CPU2_DMAC, CPU2_DMAC_CH3);

    dmac_llp_test(CPU1_DMAC, CPU1_DMAC_CH0);
    dmac_llp_test(CPU1_DMAC, CPU1_DMAC_CH1);
    dmac_llp_test(CPU1_DMAC, CPU1_DMAC_CH2);
    dmac_llp_test(CPU1_DMAC, CPU1_DMAC_CH3);
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

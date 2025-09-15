/********************************************************************************************************
 * @file    app.c
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

volatile unsigned char rz_dma_send_flag = 1;
unsigned int g_ram_data_buffer1[6] = {0x55ac6600, 0x000057ab, 0x00997f09, 0x80095512, 0x77990101, 0x00000000};
unsigned int g_ram_data_buffer2[6] = {0x55ac66aa, 0xbbcc57ab, 0x22000000, 0x80095512, 0x77990101, 0x00888888};

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_input_dis(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_input_dis(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_input_dis(LED4);

#if (RZ_MODE == RZ_DMA_SERIAL_SEQUENTIAL)
    /* gpio config. */
    gpio_function_dis(GPIO_PC0);
    gpio_set_mux_function((gpio_func_pin_e)GPIO_PC0,RZ_TX);

    /* rz protocol config. */
    rz_tx_config_t rz_tx_config = {
        .pola              = POLARITY_NO_INV,
        .addr_mode         = SERIAL_SEQUENTIAL_MODE,
        .bit_msb           = BIT_LSB,
        .big_endian_mode   = BIG_ENDIAN_MODE,
        .global_data_mode  = GLOBAL_DATA_AFTER_EACH_PIXEL_DATA,
        .align_32bits_mode = EACH_PIXEL_DATA_AT_8BITS_BOUNDARY,
        .jitter_l_en       = DISABLE_JITTER_ON_T0L_T1L,
        .jitter_h_en       = DISABLE_JITTER_ON_T0H_T1H,
        .jitter_range      = JITTER_RANGE_FROM_0_TO_1,
    };
    rz_set_tx_config(&rz_tx_config);
    rz_set_t0h_t0l_time(12, 33); //12*1000/sys_clk.pclk=333ns,33*1000/sys_clk.pclk=916ns //default:36M
    rz_set_t1h_t1l_time(23, 23); //23*1000/sys_clk.pclk=625ns,23*1000/sys_clk.pclk=625ns
    rz_set_tsrh_tsrl_time(0, 9000); //0*1000/sys_clk.pclk=0us,9000*1000/sys_clk.pclk=250000ns
    rz_set_pixel_ic_num(8);
    rz_data_bit_num_per_pixel(24);

    /**
     * Series connection is required, parallel connection is not required, this is because the external ic bugs lead to,
     * may be the GPIO on the disturbance pulse as data, in sending data before the need to delay at least a reset time out.
     */
    delay_ms(20);

    /* dam config. */
    rz_set_dma_config(DMA1);
    rz_set_dma(DMA1, (unsigned int*)(g_ram_data_buffer1), sizeof(g_ram_data_buffer1));

    /* interrupt config. */
    rz_set_irq_mask(FLD_RZ_MASK_TXDONE);
    plic_interrupt_enable(IRQ_RZ);
    core_interrupt_enable();

#elif (RZ_MODE == RZ_DMA_PARALLEL_RANDOM)
    /* gpio config. */
    gpio_function_dis(GPIO_PC0);
    gpio_set_mux_function((gpio_func_pin_e)GPIO_PC0,RZ_TX);

    /* rz protocol config. */
    rz_tx_config_t rz_tx_config = {
        .pola              = POLARITY_NO_INV,
        .addr_mode         = PARALLEL_RANDOM_MODE,
        .bit_msb           = BIT_LSB,
        .big_endian_mode   = BIG_ENDIAN_MODE,
        .global_data_mode  = GLOBAL_DATA_AFTER_EACH_PIXEL_DATA,
        .align_32bits_mode = EACH_PIXEL_DATA_AT_32BITS_BOUNDARY,
        .jitter_l_en       = DISABLE_JITTER_ON_T0L_T1L,
        .jitter_h_en       = DISABLE_JITTER_ON_T0H_T1H,
        .jitter_range      = JITTER_RANGE_FROM_0_TO_1,
    };
    rz_set_tx_config(&rz_tx_config);
    rz_set_t0h_t0l_time(8, 22);
    rz_set_t1h_t1l_time(15, 15);
    rz_set_tsrh_tsrl_time(0, 6000);
    rz_set_pixel_ic_num(3);
    rz_data_bit_num_per_pixel(47);

    /* dam config. */
    rz_set_dma_config(DMA1);
    rz_set_dma(DMA1, (unsigned int*)(g_ram_data_buffer1), sizeof(g_ram_data_buffer1));

    /* interrupt config. */
    rz_set_irq_mask(FLD_RZ_MASK_TXDONE);
    plic_interrupt_enable(IRQ_RZ);
    core_interrupt_enable();

#endif
}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
    if(rz_dma_send_flag == 1)
    {
        rz_set_dma_config(DMA1);
        rz_set_dma(DMA1, (unsigned int*)(g_ram_data_buffer2), sizeof(g_ram_data_buffer2));
        rz_dma_send_flag = 0;
    }
    gpio_toggle(LED3);
    delay_ms(500);
}

_attribute_ram_code_sec_ void rz_irq_handler(void)
{
    if(rz_get_irq_status(FLD_RZ_CLR_INT_TXDONE))
    {
        gpio_toggle(LED4);
        rz_clr_irq_status(FLD_RZ_CLR_INT_TXDONE);
        rz_dma_send_flag = 1;
    }
}
PLIC_ISR_REGISTER(rz_irq_handler, IRQ_RZ)


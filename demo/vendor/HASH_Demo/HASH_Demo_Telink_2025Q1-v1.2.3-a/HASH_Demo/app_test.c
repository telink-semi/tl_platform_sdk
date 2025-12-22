/********************************************************************************************************
 * @file    app_test.c
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
#include "hash_hmac_test/app_test.h"

unsigned int hash_app_test(void)
{
    trng_dig_en();
    hash_dig_en();
#ifdef HASH_DMA_FUNCTION
    hash_set_tx_dma_config(DMA0);
    hash_set_rx_dma_config(DMA1, DMA_BURST_1_WORD);
#endif /* HASH_DMA_FUNCTION */

#if 1
    if (ansi_x9_63_kdf_all_test()) {
        return 1;
    }
#endif

#if 1
    if (hash_all_test()) {
        return 1;
    }
#endif

#if 1
    if (hmac_all_test()) {
        return 1;
    }
#endif

#if 1
    if (hash_hmac_sample_test()) {
        return 1;
    }
#endif


    return 0;
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    hash_app_test();
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(50);
}

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
#include "pke_test/app_test.h"

unsigned int pke_app_test(void)
{
    pke_dig_en();

#if defined(SUPPORT_DH)
#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (DH_all_test()) {
        return 1;
    }
#endif
#endif

#if 1
    if (eccp_get_curve_paras_test()) {
        return 1;
    }
#endif

#if 1
    if (eccp_get_key_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (ecdh_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (ecdsa_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng and hash module and must call the trng_dig_en hash_dig_en function interface.*/
    trng_dig_en();
    hash_dig_en();
    if (ecies_all_test()) {
        return 1;
    }
#endif

    printf("\r\n TEST OVER \r\n"); // fflush(stdout);
    return 0;
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    pke_app_test();
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(50);
}

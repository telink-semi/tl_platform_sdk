/********************************************************************************************************
 * @file    app_test.c
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
#include "common.h"
#include "pke_test/app_test.h"

unsigned int pke_app_test(void)
{
#if defined(MCU_CORE_TL751X) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL323X) ||defined(MCU_CORE_W92)
    pke_dig_en();
#endif

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
    if (ECCp_get_curve_paras_test()) {
        return 1;
    }
#endif

#if 1
    if (ECCp_get_key_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (ECDH_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (ECDSA_all_test()) {
        return 1;
    }
#endif

#if 1
    /*This demo uses the trng and hash module and must call the trng_dig_en hash_dig_en function interface.*/
    trng_dig_en();
    hash_dig_en();
    if (ECIES_all_test()) {
        return 1;
    }
#endif

#if defined(SUPPORT_C25519)
#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (Ed25519_all_test()) {
        return 1;
    }
#endif
#endif

#if defined(SUPPORT_RSA)
#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (RSA_all_test()) {
        return 1;
    }
#endif
#endif

#if defined(SUPPORT_C25519)
#if 1
    /*This demo uses the trng module and must call the trng_dig_en function interface.*/
    trng_dig_en();
    if (X25519_all_test()) {
        return 1;
    }
#endif
#endif
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

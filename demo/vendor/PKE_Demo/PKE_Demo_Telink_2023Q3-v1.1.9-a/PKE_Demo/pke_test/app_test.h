/********************************************************************************************************
 * @file    app_test.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#ifndef __APP_TEST__H_
#define __APP_TEST__H_
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C"
{
#endif
#include "driver.h"
#include "common.h"

    unsigned int ECCp_get_key_all_test(void);
    unsigned int ECDH_all_test(void);
    unsigned int ECDSA_all_test(void);
#if defined(SUPPORT_RSA)
    unsigned int RSA_all_test(void);
#endif
#if defined(SUPPORT_C25519)
    unsigned int X25519_all_test(void);
    unsigned int Ed25519_all_test(void);
#endif
#if defined(SUPPORT_DH)
    unsigned int DH_all_test(void);
#endif
    unsigned int ECCp_get_curve_paras_test(void);
    unsigned int ECIES_all_test(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif /* __APP_TEST__H_ */

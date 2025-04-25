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

    /**
     * @brief           Perform all DH tests, including standard data tests and random data tests.
     * @return          0 if all tests are successful, 1 if any test fails.
     */
    unsigned int dh_all_test(void);

    /**
     * @brief           Run all curve parameter retrieval tests
     * @return          0 if all tests pass, 1 if any test fails
     */
    unsigned int eccp_get_curve_paras_test(void);

    /**
     * @brief           Executes all supported elliptic curve public key generation tests.
     * @return          0 if all tests pass, 1 if any test fails.
     */
    unsigned int eccp_get_key_all_test(void);

    /**
     * @brief           Run all ECDH tests
     * @return          0 if all tests passed, 1 if any test failed
     */
    unsigned int ecdh_all_test(void);

    /**
     * @brief           Execute all ECDSA tests
     * @return          0 if all tests pass successfully, 1 if any test fails
     */
    unsigned int ecdsa_all_test(void);

    /**
     * @brief           Runs all ECIES tests (standard and random) for supported curves
     * @return          unsigned int 0 if all tests pass, 1 if any test fails
     */
    unsigned int ecies_all_test(void);

    /**
     * @brief           Comprehensive function to run all RSA tests
     * @return          0 if all tests pass, 1 if any test fails
     */
    unsigned int rsa_all_test(void);

    /**
     * @brief           SM2   all tests
     * @return          0 for success, 1 for failure
     */
    unsigned int sm2_all_test(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif /* __APP_TEST__H_ */

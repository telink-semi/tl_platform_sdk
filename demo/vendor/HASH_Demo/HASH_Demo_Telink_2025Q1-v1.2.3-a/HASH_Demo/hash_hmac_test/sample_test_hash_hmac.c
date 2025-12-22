/********************************************************************************************************
 * @file    sample_test_hash_hmac.c
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
#include <stdio.h>
#include <stdint.h>

#include "lib/include/hash/hash.h"

/**
 * @brief           Perform sample tests for SM3 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sm3(void);

/**
 * @brief           Perform sample tests for HMAC-SM3 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sm3(void);

/**
 * @brief           Perform sample tests for MD5 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_md5(void);

/**
 * @brief           Perform sample tests for HMAC-MD5 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_md5(void);

/**
 * @brief           Perform sample tests for SHA256 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha256(void);

/**
 * @brief           Perform sample tests for HMAC-SHA256 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha256(void);

/**
 * @brief           Perform sample tests for SHA384 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha384(void);

/**
 * @brief           Perform sample tests for HMAC-SHA384 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha384(void);

/**
 * @brief           Perform sample tests for SHA512 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha512(void);

/**
 * @brief           Perform sample tests for HMAC-SHA512 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha512(void);

/**
 * @brief           Perform sample tests for SHA1 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha1(void);

/**
 * @brief           Perform sample tests for HMAC-SHA1 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha1(void);

/**
 * @brief           Perform sample tests for SHA224 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha224(void);

/**
 * @brief           Perform sample tests for HMAC-SHA224 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha224(void);

/**
 * @brief           Perform sample tests for SHA512-224 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha512_224(void);

/**
 * @brief           Perform sample tests for HMAC-SHA512-224 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha512_224(void);

/**
 * @brief           Perform sample tests for SHA512-256 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_sha512_256(void);

/**
 * @brief           Perform sample tests for HMAC-SHA512-256 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha512_256(void);

/**
 * @brief           Perform comprehensive sample tests for all supported hash and HMAC algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_hmac_sample_test(void)
{
    printf("\r\n\r\n\r\n =================== HASH HMAC sample test =================== ");


#ifdef SUPPORT_HASH_SM3
    if (sample_test_sm3()) {
        return 1;
    }

    if (sample_test_hmac_sm3()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_MD5
    if (sample_test_md5()) {
        return 1;
    }

    if (sample_test_hmac_md5()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA256
    if (sample_test_sha256()) {
        return 1;
    }

    if (sample_test_hmac_sha256()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA384
    if (sample_test_sha384()) {
        return 1;
    }

    if (sample_test_hmac_sha384()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512
    if (sample_test_sha512()) {
        return 1;
    }

    if (sample_test_hmac_sha512()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA1
    if (sample_test_sha1()) {
        return 1;
    }

    if (sample_test_hmac_sha1()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA224
    if (sample_test_sha224()) {
        return 1;
    }

    if (sample_test_hmac_sha224()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_224
    if (sample_test_sha512_224()) {
        return 1;
    }

    if (sample_test_hmac_sha512_224()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_256
    if (sample_test_sha512_256()) {
        return 1;
    }

    if (sample_test_hmac_sha512_256()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_224
    if (sample_test_sha3_224()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_256
    if (sample_test_sha3_256()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_384
    if (sample_test_sha3_384()) {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_512
    if (sample_test_sha3_512()) {
        return 1;
    }
#endif

    printf("\r\n\r\n HASH HMAC sample test success \r\n\r\n");
    fflush(stdout);

    return 0;
}

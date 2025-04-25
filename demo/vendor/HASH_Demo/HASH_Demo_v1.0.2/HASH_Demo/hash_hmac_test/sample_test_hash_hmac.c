/********************************************************************************************************
 * @file    sample_test_hash_hmac.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "common.h"
#include "../hash_hmac_test/app_test.h"


unsigned int sample_test_sm3(void);
unsigned int sample_test_hmac_sm3(void);
unsigned int sample_test_md5(void);
unsigned int sample_test_hmac_md5(void);
unsigned int sample_test_sha256(void);
unsigned int sample_test_hmac_sha256(void);
unsigned int sample_test_sha384(void);
unsigned int sample_test_hmac_sha384(void);
unsigned int sample_test_sha512(void);
unsigned int sample_test_hmac_sha512(void);
unsigned int sample_test_sha1(void);
unsigned int sample_test_hmac_sha1(void);
unsigned int sample_test_sha224(void);
unsigned int sample_test_hmac_sha224(void);
unsigned int sample_test_sha512_224(void);
unsigned int sample_test_hmac_sha512_224(void);
unsigned int sample_test_sha512_256(void);
unsigned int sample_test_hmac_sha512_256(void);

unsigned int HASH_HMAC_sample_test(void)
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

    printf("\r\n\r\n HASH HMAC sample test success \r\n\r\n");
    fflush(stdout);

    return 0;
}

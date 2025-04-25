/********************************************************************************************************
 * @file    x25519_test.c
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
#include "../app_config.h"


#ifdef SUPPORT_C25519

    #define X25519_KEY_EXCHANGE_ROUND1 (3)

unsigned int x25519_std_test(void)
{
    //the test vectors are from RFC7748
    unsigned char A_prikey[] = {
        0x77,
        0x07,
        0x6D,
        0x0A,
        0x73,
        0x18,
        0xA5,
        0x7D,
        0x3C,
        0x16,
        0xC1,
        0x72,
        0x51,
        0xB2,
        0x66,
        0x45,
        0xDF,
        0x4C,
        0x2F,
        0x87,
        0xEB,
        0xC0,
        0x99,
        0x2A,
        0xB1,
        0x77,
        0xFB,
        0xA5,
        0x1D,
        0xB9,
        0x2C,
        0x2A};
    unsigned char A_pubkey[] = {
        0x85,
        0x20,
        0xF0,
        0x09,
        0x89,
        0x30,
        0xA7,
        0x54,
        0x74,
        0x8B,
        0x7D,
        0xDC,
        0xB4,
        0x3E,
        0xF7,
        0x5A,
        0x0D,
        0xBF,
        0x3A,
        0x0D,
        0x26,
        0x38,
        0x1A,
        0xF4,
        0xEB,
        0xA4,
        0xA9,
        0x8E,
        0xAA,
        0x9B,
        0x4E,
        0x6A};
    unsigned char B_prikey[] = {
        0x5D,
        0xAB,
        0x08,
        0x7E,
        0x62,
        0x4A,
        0x8A,
        0x4B,
        0x79,
        0xE1,
        0x7F,
        0x8B,
        0x83,
        0x80,
        0x0E,
        0xE6,
        0x6F,
        0x3B,
        0xB1,
        0x29,
        0x26,
        0x18,
        0xB6,
        0xFD,
        0x1C,
        0x2F,
        0x8B,
        0x27,
        0xFF,
        0x88,
        0xE0,
        0xEB};
    unsigned char B_pubkey[] = {
        0xDE,
        0x9E,
        0xDB,
        0x7D,
        0x7B,
        0x7D,
        0xC1,
        0xB4,
        0xD3,
        0x5B,
        0x61,
        0xC2,
        0xEC,
        0xE4,
        0x35,
        0x37,
        0x3F,
        0x83,
        0x43,
        0xC8,
        0x5B,
        0x78,
        0x67,
        0x4D,
        0xAD,
        0xFC,
        0x7E,
        0x14,
        0x6F,
        0x88,
        0x2B,
        0x4F};
    unsigned char std_key[] = {
        0x4A,
        0x5D,
        0x9D,
        0x5B,
        0xA4,
        0xCE,
        0x2D,
        0xE1,
        0x72,
        0x8E,
        0x3B,
        0xF4,
        0x80,
        0x35,
        0x0F,
        0x25,
        0xE0,
        0x7E,
        0x21,
        0xC9,
        0x47,
        0xD1,
        0x9E,
        0x33,
        0x76,
        0xF0,
        0x9B,
        0x3C,
        0x1E,
        0x16,
        0x17,
        0x42};
    unsigned char A_key[32], B_key[32];
    unsigned int  ret;

    printf("\r\n\r\n -------------- X25519 key exchange standard data test -------------- ");

    ret = x25519_get_pubkey_from_prikey(A_prikey, A_key);
    if (X25519_SUCCESS != ret || memcmp_(A_key, A_pubkey, 32)) {
        printf("\r\n X25519 A get key error, ret=%x", ret);
        return 1;
    }

    ret = x25519_get_pubkey_from_prikey(B_prikey, B_key);
    if (X25519_SUCCESS != ret || memcmp_(B_key, B_pubkey, 32)) {
        printf("\r\n X25519 B get key error, ret=%x", ret);
        return 1;
    }

    ret = x25519_compute_key(A_prikey, B_pubkey, A_key, 32, NULL);
    if (X25519_SUCCESS != ret) {
        printf("\r\n X25519 A calc error, ret=%x", ret);
        return 1;
    }

    ret = x25519_compute_key(B_prikey, A_pubkey, B_key, 32, NULL);
    if (X25519_SUCCESS != ret) {
        printf("\r\n X25519 B calc error, ret=%x", ret);
        return 1;
    }

    if (memcmp_(A_key, B_key, 32) || memcmp_(A_key, std_key, 32)) {
        printf("\r\n X25519 key agreement error ");
        return 1;
    } else {
        printf("\r\n X25519 key agreement success ");
        fflush(stdout);
    }

    return 0;
}

unsigned int x25519_get_key_corner_test(void)
{
    //prikey is all 0
    unsigned char const pubkey1[32] = {
        0x2F,
        0xE5,
        0x7D,
        0xA3,
        0x47,
        0xCD,
        0x62,
        0x43,
        0x15,
        0x28,
        0xDA,
        0xAC,
        0x5F,
        0xBB,
        0x29,
        0x07,
        0x30,
        0xFF,
        0xF6,
        0x84,
        0xAF,
        0xC4,
        0xCF,
        0xC2,
        0xED,
        0x90,
        0x99,
        0x5F,
        0x58,
        0xCB,
        0x3B,
        0x74};

    //prikey is all 1
    unsigned char const pubkey2[32] = {
        0x84,
        0x7C,
        0x0D,
        0x2C,
        0x37,
        0x52,
        0x34,
        0xF3,
        0x65,
        0xE6,
        0x60,
        0x95,
        0x51,
        0x87,
        0xA3,
        0x73,
        0x5A,
        0x0F,
        0x76,
        0x13,
        0xD1,
        0x60,
        0x9D,
        0x3A,
        0x6A,
        0x4D,
        0x8C,
        0x53,
        0xAE,
        0xAA,
        0x5A,
        0x22};

    unsigned char prikey[32];
    unsigned char pubkey[32];

    unsigned int ret;

    printf("\r\n\r\n -------------- X25519 get key corner test -------------- ");

    //test 1
    memset_(prikey, 0, 32);
    ret = x25519_get_pubkey_from_prikey(prikey, pubkey);
    if (ret || memcmp_(pubkey, (const unsigned char *)pubkey1, 32)) {
        printf("\r\n X25519 get key corner test 1 error, ret=%x", ret);
        fflush(stdout);
        print_buf_U8(pubkey, 32, "pubkey 1");
        return 1;
    } else {
        printf("\r\n X25519 get key corner test 1 success");
        fflush(stdout);
    }

    //test 2
    memset_(prikey, 0xFF, 32);
    ret = x25519_get_pubkey_from_prikey(prikey, pubkey);
    if (ret || memcmp_(pubkey, (const unsigned char *)pubkey2, 32)) {
        printf("\r\n X25519 get key corner test 2 error, ret=%x", ret);
        fflush(stdout);
        print_buf_U8(pubkey, 32, "pubkey 2");
        return 1;
    } else {
        printf("\r\n X25519 get key corner test 2 success");
        fflush(stdout);
    }

    return 0;
}

unsigned int x25519_corner_test(void)
{
    unsigned char prikey[32];
    unsigned char pubkey[32];
    unsigned char key[10];
    unsigned int  ret;

    printf("\r\n\r\n -------------- X25519 corner test -------------- ");

    memset_(pubkey, 0, 32);
    ret = x25519_compute_key(prikey, pubkey, key, 10, NULL);
    if (X25519_INVALID_INPUT != ret) {
        printf("\r\n X25519 corner case test(pubkey all zero) error, ret=%x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n X25519 corner case test(pubkey all zero) success");
        fflush(stdout);
        return 0;
    }
}

unsigned int x25519_rand_test(void)
{
    unsigned char A_prikey[32];
    unsigned char A_pubkey[32];
    unsigned char B_prikey[32];
    unsigned char B_pubkey[32];
    unsigned char A_key[200], B_key[200];
    unsigned int  i, j;
    unsigned int  keyByteLen, trueKeyByteLen;
    unsigned int  ret;
    KDF_FUNC      kdf = NULL;

    printf("\r\n\r\n -------------- X25519 key exchange rand data test -------------- ");

    for (i = 0; i < X25519_KEY_EXCHANGE_ROUND1; i++) {
        ret = x25519_getkey(A_prikey, A_pubkey);
        if (X25519_SUCCESS != ret) {
            printf("\r\n X25519 A get key error, ret=%x", ret);
            return 1;
        }
        ret = x25519_getkey(B_prikey, B_pubkey);
        if (X25519_SUCCESS != ret) {
            printf("\r\n X25519 B get key error, ret=%x", ret);
            return 1;
        }

        for (j = 0; j < 50; j++) {
            printf("\r\n X25519 round1=%u round2=%u", i + 1, j + 1);

            keyByteLen = A_prikey[0] + B_prikey[0];
            keyByteLen %= 200;
            if (0 == keyByteLen) {
                keyByteLen += 1;
            }
            trueKeyByteLen = keyByteLen;
            if (NULL == kdf) {
                if (keyByteLen > GET_BYTE_LEN(255)) {
                    trueKeyByteLen = GET_BYTE_LEN(255);
                }
            }

            printf(" keyByteLen=%u(%u actually)", keyByteLen, trueKeyByteLen);

            ret = x25519_compute_key(A_prikey, B_pubkey, A_key, keyByteLen, kdf);
            if (X25519_SUCCESS != ret) {
                printf("\r\n X25519 A calc error, ret=%x", ret);
                return 1;
            }

            ret = x25519_compute_key(B_prikey, A_pubkey, B_key, keyByteLen, kdf);
            if (X25519_SUCCESS != ret) {
                printf("\r\n X25519 B calc error, ret=%x", ret);
                return 1;
            }

            if (memcmp_(A_key, B_key, trueKeyByteLen)) {
                printf("\r\n X25519 key agreement error ");
                return 1;
            }
        }
    }

    return 0;
}

unsigned int x25519_speed_test(void)
{
    unsigned int  k[8];
    unsigned char A_prikey[32];
    unsigned char A_pubkey[32];
    unsigned char B_prikey[32];
    unsigned char B_pubkey[32];
    unsigned char A_key[200], B_key[200];
    unsigned int  i, keyByteLen = 32;
    unsigned int  ret;

    printf("\r\n x25519_getkey begin");
    fflush(stdout);
    for (i = 0; i < 1000; i++) {
        ret = x25519_getkey(A_prikey, A_pubkey);
    }
    printf("\r\n finished");
    fflush(stdout);
    if (X25519_SUCCESS != ret) {
        printf("\r\n X25519 A get key error, ret=%x", ret);
        return 1;
    }

    //a small loop for sleeping
    for (i = 0; i < 100; i++) {
        ret = x25519_getkey(B_prikey, B_pubkey);
        if (X25519_SUCCESS != ret) {
            printf("\r\n X25519 B get key error, ret=%x", ret);
            return 1;
        }
    }

    x25519_decode_scalar(A_prikey, (unsigned char *)k, C25519_BYTE_LEN);
    printf("\r\n x25519_pointMul begin");
    fflush(stdout);
    for (i = 0; i < 1000; i++) {
        ret = x25519_pointMul((mont_curve_t *)c25519, k, c25519->u, k);
    }
    printf("\r\n finished");
    fflush(stdout);

    //a small loop for sleeping
    for (i = 0; i < 100; i++) {
        ret = x25519_compute_key(A_prikey, B_pubkey, A_key, 32, NULL);
        if (ret) {
            printf("\r\n X25519 A calc error, ret=%x", ret);
            return 1;
        }
    }
    printf("\r\n x25519_compute_key begin");
    fflush(stdout);
    for (i = 0; i < 1000; i++) {
        ret = x25519_compute_key(B_prikey, A_pubkey, B_key, 32, NULL);
        printf("\r\n finished");
        fflush(stdout);
        if (ret) {
            printf("\r\n X25519 B calc error, ret=%x", ret);
            return 1;
        }

        if (memcmp_(A_key, B_key, keyByteLen)) {
            printf("\r\n X25519 key agreement error ");
            return 1;
        } else {
            printf("\r\n X25519 key agreement success ");
            fflush(stdout);
        }
    }

    return 0;
}

unsigned int X25519_all_test(void)
{
    printf("\r\n\r\n\r\n =================== X25519 test =================== ");

    #if 1
    if (x25519_speed_test()) {
        return 1;
    }
    #endif

    #if 1
    if (x25519_std_test()) {
        return 1;
    }

    if (x25519_get_key_corner_test()) {
        return 1;
    }

    if (x25519_corner_test()) {
        return 1;
    }

    if (x25519_rand_test()) {
        return 1;
    }

    #endif

    return 0;
}

#endif

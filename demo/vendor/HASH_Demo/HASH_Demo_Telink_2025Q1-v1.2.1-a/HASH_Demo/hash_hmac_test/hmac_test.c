/********************************************************************************************************
 * @file    hmac_test.c
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
#include <stdio.h>

#include "lib/include/hash/hmac.h"
#include "lib/include/trng/trng.h"
#include "lib/include/crypto_common/utility.h"
#include "common.h"
#include "hash_hmac_test/app_test.h"

#ifdef HMAC_SPEED_TEST_BY_TIMER
extern unsigned int startp(void);
extern unsigned int endp(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif

extern unsigned int hash_get_rand_number(unsigned int max_number);

extern void hash_call_manage(void);

// extern unsigned int get_rand(unsigned char *rand, unsigned int byteLen);

/**
 * @brief           Test HMAC implementation for a specific hash algorithm
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       std_mac1             - Expected MAC for test case 1
 * @param[in]       std_mac2             - Expected MAC for test case 2
 * @param[in]       std_mac3             - Expected MAC for test case 3
 * @param[in]       std_mac4             - Expected MAC for test case 4
 * @param[in]       std_mac5             - Expected MAC for test case 5
 * @param[in]       std_mac6             - Expected MAC for test case 6
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_test(hash_alg_e alg, unsigned char *std_mac1, unsigned char *std_mac2, unsigned char *std_mac3, unsigned char *std_mac4, unsigned char *std_mac5,
                       unsigned char *std_mac6)
{
    hmac_ctx_t ctx[1];
    unsigned short key_id = 0;
    unsigned char key[250];
    unsigned char message[500];
    unsigned char mac[64];
    unsigned char long_key[4096];
    unsigned int long_key_bytes = 4096;

    unsigned int len[5][15] = // sum of each line is 500
        {
            {4, 91, 173, 23, 56, 79, 2, 11, 61, 0, 0, 0, 0, 0, 0}, // padding with 0 to avoid some bad compiler's error(memset not found)
            {84, 37, 68, 293, 13, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0},
            {33, 20, 208, 3, 7, 67, 33, 88, 19, 22, 0, 0, 0, 0, 0},
            {59, 111, 29, 34, 27, 89, 9, 6, 79, 22, 35, 0, 0, 0, 0},
            {333, 2, 5, 39, 77, 16, 24, 4, 0, 0, 0, 0, 0, 0, 0},
        };

    char *name[] = {"HMAC_SM3", "HMAC_MD5", "HMAC_SHA256", "HMAC_SHA384", "HMAC_SHA512", "HMAC_SHA1", "HMAC_SHA224", "HMAC_SHA512_224", "HMAC_SHA512_256"};
    unsigned char outLen[] = {32, 16, 32, 48, 64, 20, 28, 28, 32};
    unsigned int msg_len;
    unsigned int i, j, total, block_byte_len;
    unsigned int ret;

#ifdef SUPPORT_HASH_NODE
    hash_node_t node[4];
#endif

    memcpy_(message, (unsigned char *)"abc", 3); // to avoid some bad compiler's error(memset not found)

    block_byte_len = hash_get_block_word_len(alg) << 2;

    printf("\r\n\r\n -------------- %s test -------------- ", name[alg]);

    for (i = 0; i < 250; i++)
    {
        key[i] = i;
    }

    /*************************** test1 ***************************/
    ret = hmac_init(ctx, alg, key, key_id, 3);
    ret |= hmac_update(ctx, message, 3); // print_buf_U8(message, 3, "message");
    ret |= hmac_final(ctx, mac);         // print_buf_U8(digest, outLen[alg], "digest");
    if (HASH_SUCCESS != ret || memcmp_(mac, std_mac1, outLen[alg]))
    {
        printf("\r\n %s test 1 failure, ret =%u \r\n", name[alg], ret);
        print_buf_U8(key, 3, "key");
        print_buf_U8(message, 3, "message");
        print_buf_U8(mac, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 1 success ", name[alg]);
    }

    /*************************** test2 ***************************/
    ret = hmac_init(ctx, alg, key, key_id, block_byte_len);
    ret |= hmac_update(ctx, message, 3);
    ret |= hmac_final(ctx, mac);
    if (HASH_SUCCESS != ret || memcmp_(mac, std_mac2, outLen[alg]))
    {
        printf("\r\n %s test 2 failure, ret =%u \r\n", name[alg], ret);
        print_buf_U8(key, block_byte_len, "key");
        print_buf_U8(message, 3, "message");
        print_buf_U8(mac, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 2 success ", name[alg]);
    }

    /*************************** test3 ***************************/
    ret = hmac_init(ctx, alg, key, key_id, 250);
    ret |= hmac_update(ctx, message, 3);
    ret |= hmac_final(ctx, mac);
    if (HASH_SUCCESS != ret || memcmp_(mac, std_mac3, outLen[alg]))
    {
        printf("\r\n %s test 3 failure, ret =%u \r\n", name[alg], ret);
        print_buf_U8(key, 250, "key");
        print_buf_U8(message, 3, "message");
        print_buf_U8(mac, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 3 success ", name[alg]);
    }

    /*************************** test4 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }
    msg_len = 500;

    // test4-1
    ret = hmac(alg, key, key_id, 250, message, msg_len, mac);
    if (HASH_SUCCESS != ret || memcmp_(mac, std_mac4, outLen[alg]))
    {
        printf("\r\n %s test 4-%u failure, ret =%u \r\n", name[alg], 1, ret);
        print_buf_U8(mac, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 4-%u success ", name[alg], 1);
    }

    // test4-2...4-6
    for (i = 0; i < 5; i++)
    {
        j = 0;
        total = 0;
        memset_(mac, 0, sizeof(mac));

        ret = hmac_init(ctx, alg, key, key_id, 250);

        while (len[i][j])
        {
            ret |= hmac_update(ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        ret |= hmac_final(ctx, mac);
        if (HASH_SUCCESS != ret || memcmp_(mac, std_mac4, outLen[alg]))
        {
            printf("\r\n %s test 4-%u failure, ret =%u \r\n", name[alg], i + 2, ret);
            print_buf_U8(mac, outLen[alg], "mac");
            return 1;
        }
        else
        {
            printf("\r\n %s test 4-%u success ", name[alg], i + 2);
        }
    }

    // test4-7...
    printf("\r\n");
    for (i = 0; i < 100; i++)
    {
        total = 0;
        memset_(mac, 0, sizeof(mac));

        ret = hmac_init(ctx, alg, key, key_id, 250);
        while (total < msg_len)
        {
            j = hash_get_rand_number(msg_len);
            if (j % 10 < 3)
            {
                j = j % 10;
            }
            else if (j % 10 < 5)
            {
                j = j % 70;
            }
            else if (j % 10 < 8)
            {
                j = j % 128;
            }

            if (j > total || j > total - j)
            {
                j = msg_len - total;
            }

            ret |= hmac_update(ctx, message + total, j);
            total += j;
        }

        ret |= hmac_final(ctx, mac);
        if (HASH_SUCCESS != ret || memcmp_(mac, std_mac4, outLen[alg]))
        {
            printf("\r\n %s test 4-%u failure, ret =%u \r\n", name[alg], i + 7, ret);
            print_buf_U8(mac, outLen[alg], "mac");
            return 1;
        }
        else
        {
            // printf("\r\n %s test 4-%u success ", name[alg], i+7);
            printf("4-%u ", i + 7);
        }
    }

#ifdef SUPPORT_HASH_NODE
    // test 4-final
    memset_(mac, 0, sizeof(mac));
    node[0].msg_addr = message;
    node[0].msg_len = 100;
    node[1].msg_addr = node[0].msg_addr + node[0].msg_len;
    node[1].msg_len = 19;
    node[2].msg_addr = node[1].msg_addr + node[1].msg_len;
    node[2].msg_len = 17;
    node[3].msg_addr = node[2].msg_addr + node[2].msg_len;
    node[3].msg_len = msg_len - 100 - 19 - 17;
    ret = hmac_node_steps(alg, key, key_id, 250, node, 4, mac);
    if (HASH_SUCCESS != ret || memcmp_(mac, std_mac4, outLen[alg]))
    {
        printf("\r\n %s test 4-final%u(hash node style) failure, ret =%u \r\n", name[alg], i + 2, ret);
        print_buf_U8(mac, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 4-final%u(hash node style) success ", name[alg], i + 2);
    }
#endif

    /*************************** test5 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++)
    {
        ret |= hmac_init(ctx, alg, key, key_id, 250);
        ret |= hmac_update(ctx, message, i);
        ret |= hmac_final(ctx, message);
    }

    if (HASH_SUCCESS != ret || memcmp_(message, std_mac5, outLen[alg]))
    {
        printf("\r\n %s test 5 failure, ret =%u ", name[alg], ret);
        print_buf_U8(message, outLen[alg], "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s test 5 success\r\n", name[alg]);
    }

    /*************************** test6 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }

    // hmac long key input test
    if (long_key_bytes > block_byte_len)
    {
        memset_(long_key, 0, long_key_bytes);
        ret = hmac(alg, long_key, key_id, long_key_bytes, message, msg_len, mac);
        if (HASH_SUCCESS != ret || memcmp_(mac, std_mac6, outLen[alg]))
        {
            printf("\r\n %s test 6-1(long key) failure, ret =%u ", name[alg], ret);
            print_buf_U8(mac, outLen[alg], "mac");
            print_buf_U8(std_mac6, outLen[alg], "std mac");
            print_buf_U8(long_key, long_key_bytes, "long_key");
            return 1;
        }
        else
        {
        }

        get_rand(long_key, long_key_bytes);
        for (i = long_key_bytes - block_byte_len; i < long_key_bytes; i++)
        {
            ret = hmac_init(ctx, alg, long_key, 0, i);
            ret |= hash(alg, long_key, i, mac);

            // recover K0(hash(key)||000..00)
            for (j = 0; j < block_byte_len / 4; j++)
            {
                ctx->K0[j] ^= HMAC_IPAD;
            }

            if (HASH_SUCCESS != ret || memcmp_((unsigned char *)(ctx->K0), mac, outLen[alg]) ||
                !uint8_BigNum_Check_Zero(((unsigned char *)(ctx->K0)) + outLen[alg], block_byte_len - outLen[alg]))
            {
                printf("\r\n %u test 6-%s(long key) failure, ret =%u ", i, name[alg], ret);
                print_buf_U8((unsigned char *)(ctx->K0), outLen[alg], "ctx->K0");
                print_buf_U8(mac, outLen[alg], "mac");
                print_buf_U8(long_key, long_key_bytes, "long_key");
                return 1;
            }
            else
            {
                printf(" 6-%u", i);
            }
        }
        printf("\r\n %s test 6(long key) success \r\n", name[alg]);
    }
    else
    {
    }

    return 0;
}

#define HMAC_SPEED_TEST_ROUND (40960)
#define HMAC_SPEED_TEST_BYTE_LEN (1024)
#define HMAC_DMA_SPEED_TEST_ROUND (5120)
#define HMAC_DMA_SPEED_TEST_BYTE_LEN (1024 * 16) // 16K

/**
 * @brief           Internal function for HMAC speed testing
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       round                - Number of iterations for the test
 * @param[in]       once_bytes           - Number of bytes to process in each iteration
 * @return          0 if test succeeds, non-zero error code if test fails
 */
unsigned int hmac_speed_test_internal(hash_alg_e alg, unsigned int round, unsigned int once_bytes)
{
    char *name_alg[] = {
        "SM3",
        "MD5",
        "SHA256",
        "SHA384",
        "SHA512",
        "SHA1",
        "SHA224",
        "SHA512_224",
        "SHA512_256",
        "SHA3_224",
        "SHA3_256",
        "SHA3_384",
        "SHA3_512",
    };
    unsigned char message[HMAC_SPEED_TEST_BYTE_LEN];
    unsigned short key_id = 0;
    unsigned char key[16];
    unsigned char mac[64];
    unsigned int i;
    unsigned int ret;
    hmac_ctx_t ctx[1];

    uint32_sleep(0xFFFFF, 1);

    printf("\r\n===================== HMAC %s CPU begin =====================", name_alg[alg]);
    fflush(stdout);

#ifdef HMAC_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = hmac_init(ctx, alg, key, key_id, 16);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n init error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++)
    {
        ret = hmac_update(ctx, message, once_bytes);
        if (HASH_SUCCESS != ret)
        {
            printf("\r\n update error ret=%u", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = hmac_final(ctx, mac);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n final error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

#ifdef HMAC_SPEED_TEST_BY_TIMER
    endp(0, once_bytes, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform speed tests for all supported HMAC algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_speed_test(void)
{
    unsigned int bytes = HMAC_SPEED_TEST_BYTE_LEN;
    unsigned int round = HMAC_SPEED_TEST_ROUND;

#ifdef HMAC_SPEED_TEST_BY_TIMER
    round = 1024;
#endif

#ifdef SUPPORT_HASH_SM3
    hmac_speed_test_internal(HASH_SM3, round, bytes);
#endif

#ifdef SUPPORT_HASH_MD5
    hmac_speed_test_internal(HASH_MD5, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA256
    hmac_speed_test_internal(HASH_SHA256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA384
    hmac_speed_test_internal(HASH_SHA384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512
    hmac_speed_test_internal(HASH_SHA512, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA1
    hmac_speed_test_internal(HASH_SHA1, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA224
    hmac_speed_test_internal(HASH_SHA224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_224
    hmac_speed_test_internal(HASH_SHA512_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_256
    hmac_speed_test_internal(HASH_SHA512_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_224
    // hmac_speed_test_internal(HASH_SHA3_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_256
    // hmac_speed_test_internal(HASH_SHA3_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_384
    // hmac_speed_test_internal(HASH_SHA3_384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_512
    // hmac_speed_test_internal(HASH_SHA3_512, round, bytes);
#endif

    return 0;
}

#ifdef HASH_DMA_FUNCTION
/**
 * @brief           Internal function for DMA HMAC speed testing
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       round                - Number of iterations for the test
 * @param[in]       once_bytes           - Number of bytes to process in each iteration
 * @return          0 if test succeeds, non-zero error code if test fails
 */
unsigned int hmac_dma_speed_test_internal(hash_alg_e alg, unsigned int round, unsigned int once_bytes)
{
    char *name_alg[] = {
        "SM3",
        "MD5",
        "SHA256",
        "SHA384",
        "SHA512",
        "SHA1",
        "SHA224",
        "SHA512_224",
        "SHA512_256",
        "SHA3_224",
        "SHA3_256",
        "SHA3_384",
        "SHA3_512",
    };
    unsigned short key_id = 0;
    unsigned char key[16];
    unsigned int i, block_byte_len;
    unsigned int *msg = (unsigned int *)(HASH_DMA_RAM_BASE);
    unsigned int *mac = msg + 512;
    unsigned int ret;
    hmac_dma_ctx_t ctx[1];

    uint32_sleep(0xFFFFF, 1);

    // this is for SHA3, since its block byte length is 72/104/136/144
    block_byte_len = hash_get_block_word_len(alg) * 4;
    once_bytes = (once_bytes / block_byte_len) * block_byte_len;

    printf("\r\n===================== HMAC %s DMA begin =====================", name_alg[alg]);
    fflush(stdout);

#ifdef HMAC_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = hmac_dma_init(ctx, alg, key, key_id, 16, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n dma init error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++)
    {
        ret = hmac_dma_update_blocks(ctx, msg, once_bytes);
        if (HASH_SUCCESS != ret)
        {
            printf("\r\n dma update error ret=%u", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = hmac_dma_final(ctx, msg, 0, mac);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n dma final error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

#ifdef HMAC_SPEED_TEST_BY_TIMER
    endp(0, once_bytes, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform DMA speed tests for all supported HMAC algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_dma_speed_test(void)
{
    unsigned int round = HMAC_DMA_SPEED_TEST_ROUND;
    unsigned int bytes = HMAC_DMA_SPEED_TEST_BYTE_LEN;

#ifdef HMAC_SPEED_TEST_BY_TIMER
    round = 512;
#endif

#ifdef SUPPORT_HASH_SM3
    hmac_dma_speed_test_internal(HASH_SM3, round, bytes);
#endif

#ifdef SUPPORT_HASH_MD5
    hmac_dma_speed_test_internal(HASH_MD5, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA256
    hmac_dma_speed_test_internal(HASH_SHA256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA384
    hmac_dma_speed_test_internal(HASH_SHA384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512
    hmac_dma_speed_test_internal(HASH_SHA512, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA1
    hmac_dma_speed_test_internal(HASH_SHA1, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA224
    hmac_dma_speed_test_internal(HASH_SHA224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_224
    hmac_dma_speed_test_internal(HASH_SHA512_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_256
    hmac_dma_speed_test_internal(HASH_SHA512_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_224
//    hmac_dma_speed_test_internal(HASH_SHA3_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_256
//    hmac_dma_speed_test_internal(HASH_SHA3_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_384
//    hmac_dma_speed_test_internal(HASH_SHA3_384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_512
//    hmac_dma_speed_test_internal(HASH_SHA3_512, round, bytes);
#endif

    return 0;
}

/**
 * @brief           Perform DMA HMAC algorithm tests
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       std_mac1             - Expected MAC for test case 1
 * @param[in]       std_mac2             - Expected MAC for test case 2
 * @param[in]       std_mac3             - Expected MAC for test case 3
 * @param[in]       std_mac4             - Expected MAC for test case 4
 * @param[in]       std_mac5             - Expected MAC for test case 5
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_dma_test(hash_alg_e alg, unsigned char *std_mac1, unsigned char *std_mac2, unsigned char *std_mac3, unsigned char *std_mac4, unsigned char *std_mac5)
{
    hmac_dma_ctx_t ctx[1];
    unsigned short key_id = 0;
    unsigned char key[250];
    unsigned char message[512];
    unsigned char tmp_buf[500];

    unsigned int *msg = (unsigned int *)(HASH_DMA_RAM_BASE);
    unsigned int *mac = msg + 512;
    char *name[] = {"HMAC_SM3", "HMAC_MD5", "HMAC_SHA256", "HMAC_SHA384", "HMAC_SHA512", "HMAC_SHA1", "HMAC_SHA224", "HMAC_SHA512_224", "HMAC_SHA512_256"};
    unsigned int block_byte_len, digest_word_len, digest_byte_len;
    unsigned int key_bytes;
    unsigned int msg_len;
    unsigned int i, j, total;
    unsigned int ret;

#ifdef SUPPORT_HASH_DMA_NODE
    hash_dma_node_t hmac_dma_node[4];
#endif

    memset_(message, 0, sizeof(message));
    memcpy_(message, (unsigned char *)"abc", 3); // to avoid some bad compiler's error(memset not found)

    printf("\r\n ------------ %s DMA test ------------ ", name[alg]);

    digest_word_len = hash_get_digest_word_len(alg);
    block_byte_len = hash_get_block_word_len(alg) << 2;
    digest_byte_len = digest_word_len << 2;

    for (i = 0; i < 250; i++)
    {
        key[i] = i;
    }

    /*************************** test1 ***************************/
    // message: 0x616263, 3 bytes.
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

    // the two styles are equivalent
    uint32_clear(mac, digest_word_len);
    key_bytes = 3;
    msg_len = 3;

    ret = hmac_dma_init(ctx, alg, key, key_id, key_bytes, hash_call_manage);
    ret |= hmac_dma_update_blocks(ctx, msg, 0);
    ret |= hmac_dma_final(ctx, msg, msg_len - block_byte_len * 0, mac);
    if (HASH_SUCCESS != ret || memcmp_(std_mac1, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 1 failure, ret =%u ", name[alg], ret);
        print_buf_U8(key, key_bytes, "key");
        print_buf_U8((unsigned char *)msg, msg_len, "msg");
        print_buf_U8(std_mac1, digest_byte_len, "std_mac1");
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 1 success ", name[alg]);
        fflush(stdout);
    }

    /*************************** test2 ***************************/
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

    // the two styles are equivalent
    uint32_clear(mac, digest_word_len);
    key_bytes = block_byte_len;
    msg_len = 3;

    ret = hmac_dma_init(ctx, alg, key, key_id, key_bytes, hash_call_manage);
    ret |= hmac_dma_update_blocks(ctx, msg, 0);
    ret |= hmac_dma_final(ctx, msg, msg_len - block_byte_len * 0, mac);
    if (HASH_SUCCESS != ret || memcmp_(std_mac2, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 2 failure, ret =%u ", name[alg], ret);
        print_buf_U8(key, key_bytes, "key");
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 2 success ", name[alg]);
        fflush(stdout);
    }

    /*************************** test3 ***************************/
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

    // the two styles are equivalent
    uint32_clear(mac, digest_word_len);
    key_bytes = 250;
    msg_len = 3;

    ret = hmac_dma_init(ctx, alg, key, key_id, key_bytes, hash_call_manage);
    ret |= hmac_dma_update_blocks(ctx, msg, 0);
    ret |= hmac_dma_final(ctx, msg, msg_len - block_byte_len * 0, mac);
    if (HASH_SUCCESS != ret || memcmp_(std_mac3, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 3 failure, ret =%u ", name[alg], ret);
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 3 success ", name[alg]);
        fflush(stdout);
    }

    /*************************** test4 ***************************/
    key_bytes = 250;
    msg_len = 500;

    for (i = 0; i < msg_len; i++)
    {
        message[i] = i;
    }

    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, msg_len / 4);

    // test 4-1
    uint32_clear(mac, digest_word_len);
    ret = hmac_dma(alg, key, key_id, key_bytes, msg, msg_len, mac, hash_call_manage);
    if (HASH_SUCCESS != ret || memcmp_(std_mac4, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 4-1 failure, ret =%u ", name[alg], ret);
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 4-1 success ", name[alg]);
        fflush(stdout);
    }

    // test 4-2
    uint32_clear(mac, digest_word_len);
    ret = hmac_dma_init(ctx, alg, key, key_id, key_bytes, hash_call_manage);
    for (i = 0; i < msg_len / block_byte_len; i++)
    {
        ret |= hmac_dma_update_blocks(ctx, msg + i * block_byte_len / 4, block_byte_len);
    }
    ret |= hmac_dma_final(ctx, msg + i * block_byte_len / 4, msg_len - i * block_byte_len, mac);
    if (HASH_SUCCESS != ret || memcmp_(std_mac4, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 4-2 failure, ret =%u ", name[alg], ret);
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 4-2 success ", name[alg]);
        fflush(stdout);
    }

    // test 4-3...
    printf("\r\n");
    for (i = 0; i < 100; i++)
    {
        total = 0;
        uint32_clear(mac, digest_word_len);

        ret = hmac_dma_init(ctx, alg, key, key_id, key_bytes, hash_call_manage);

        while (total < msg_len)
        {
            j = hash_get_rand_number(500 / block_byte_len);
            j = j * block_byte_len;
            if (j > msg_len - total)
            {
                j = msg_len - total;
            }

            if (hash_get_rand_number(156) & 1)
            {
                if (0 == (j % block_byte_len))
                {
                    if (msg_len - total == j)
                    {
                        ret |= hmac_dma_final(ctx, msg + total / 4, j, mac);
                    }
                    else
                    {
                        ret |= hmac_dma_update_blocks(ctx, msg + total / 4, j);
                    }
                }
                else
                {
                    j = 500 - total;
                    ret |= hmac_dma_final(ctx, msg + total / 4, j, mac);
                }
            }
            else
            {
                j = 500 - total;
                ret |= hmac_dma_final(ctx, msg + total / 4, j, mac);
            }

            total += j;
        }
        if (HASH_SUCCESS != ret || memcmp_(std_mac4, (unsigned char *)mac, digest_byte_len))
        {
            printf("\r\n %s DMA test 4-%u failure, ret =%u ", name[alg], i + 3u, ret);
            print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
            return 1;
        }
        else
        {
            printf(" 4-%u", i + 3u); // fflush(stdout);
        }
    }

#ifdef SUPPORT_HASH_DMA_NODE
    // test 4-final
    uint32_clear(mac, 64 / 4);
    hmac_dma_node[0].msg_addr = msg;
    hmac_dma_node[0].msg_len = block_byte_len;
    hmac_dma_node[1].msg_addr = hmac_dma_node[0].msg_addr + hmac_dma_node[0].msg_len / 4;
    hmac_dma_node[1].msg_len = block_byte_len;
    hmac_dma_node[2].msg_addr = hmac_dma_node[1].msg_addr + hmac_dma_node[1].msg_len / 4;
    hmac_dma_node[2].msg_len = msg_len - 2 * block_byte_len;
    ret = hmac_dma_node_steps(alg, key, key_id, key_bytes, hmac_dma_node, 3, mac, hash_call_manage);
    if (HASH_SUCCESS != ret || memcmp_(std_mac4, (unsigned char *)mac, digest_byte_len))
    {
        printf("\r\n %s DMA test 4-final(hash dma node style) failure, ret =%u ", name[alg], ret);
        print_buf_U8((unsigned char *)mac, digest_byte_len, "mac");
        print_buf_U8(std_mac4, digest_byte_len, "std mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 4-final(hash dma node style) success ", name[alg]);
        fflush(stdout);
    }
#endif

    /*************************** test5 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++)
    {
        memset_(tmp_buf, 0, 500);
        memcpy_(tmp_buf, message, i);

        uint32_clear(msg, 512 / 4);
        uint32_copy(msg, (unsigned int *)tmp_buf, (i + 3) / 4);

        ret |= hmac_dma(alg, key, key_id, 250, msg, i, mac, hash_call_manage);

        memcpy_(message, (unsigned char *)mac, digest_byte_len);
    }

    if (HASH_SUCCESS != ret || memcmp_(message, std_mac5, digest_byte_len))
    {
        printf("\r\n %s DMA test 5 failure, ret =%u ", name[alg], ret);
        print_buf_U8(message, digest_byte_len, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 5 success ", name[alg]);
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_MD5
/**
 * @brief           Perform HMAC-MD5 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_md5_test(void)
{
    unsigned char std_mac1[16] = {
        0x95,
        0x78,
        0x20,
        0xE8,
        0xFC,
        0x07,
        0xC8,
        0xF3,
        0x00,
        0xE9,
        0x41,
        0xDF,
        0x5B,
        0xEE,
        0x04,
        0xD7,
    };
    unsigned char std_mac2[16] = {
        0xA0,
        0xD7,
        0x2B,
        0xDF,
        0xA6,
        0xE9,
        0xCD,
        0x3A,
        0x56,
        0xE6,
        0x60,
        0xEC,
        0xA8,
        0x92,
        0xBF,
        0xB0,
    };
    unsigned char std_mac3[16] = {
        0xBC,
        0x69,
        0xB2,
        0x04,
        0x59,
        0x9A,
        0x41,
        0x04,
        0x38,
        0x2D,
        0x55,
        0x92,
        0xE4,
        0xDF,
        0x9B,
        0xC5,
    };
    unsigned char std_mac4[16] = {
        0x57,
        0xE9,
        0x03,
        0x84,
        0x77,
        0xD2,
        0xAC,
        0x97,
        0x8A,
        0x2A,
        0x07,
        0x3C,
        0xF7,
        0x6A,
        0x62,
        0xFF,
    };
    unsigned char std_mac5[16] = {
        0x47,
        0xAD,
        0x92,
        0xB8,
        0x14,
        0x0D,
        0xBA,
        0x75,
        0x0E,
        0x0F,
        0xE8,
        0x5B,
        0xD5,
        0x7A,
        0x8E,
        0xD6,
    };
    unsigned char std_mac6[16] = {
        0x58,
        0x8C,
        0x28,
        0x9F,
        0x6C,
        0xB6,
        0x8F,
        0x70,
        0x2E,
        0x6B,
        0x1B,
        0x6F,
        0x6E,
        0x6D,
        0x61,
        0xEC,
    };
    unsigned int ret;

    ret = hmac_test(HASH_MD5, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_MD5, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA1
/**
 * @brief           Perform HMAC-SHA1 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha1_test(void)
{
    unsigned char std_mac1[20] = {0x45, 0x7E, 0xA2, 0x58, 0x23, 0x1A, 0x70, 0xE0, 0xBC, 0xDE, 0xE2, 0xC7, 0xAB, 0xA7, 0xA5, 0xA8, 0x40, 0x91, 0xE6, 0xE7};
    unsigned char std_mac2[20] = {0x89, 0xE3, 0x92, 0x85, 0x2D, 0xA6, 0xB6, 0x47, 0x49, 0x0D, 0x3F, 0x28, 0x72, 0x18, 0x82, 0x4A, 0x2E, 0x21, 0x01, 0xB0};
    unsigned char std_mac3[20] = {0xD9, 0xAC, 0xB8, 0xA2, 0x65, 0xA2, 0x3C, 0xB3, 0x51, 0x01, 0xBE, 0x16, 0x74, 0xF2, 0x8F, 0x86, 0x43, 0x3C, 0x5A, 0x71};
    unsigned char std_mac4[20] = {0x20, 0xE6, 0x8C, 0x17, 0xD5, 0x5F, 0x04, 0xFA, 0x05, 0xA5, 0x8B, 0xD0, 0x87, 0x14, 0xCE, 0x72, 0xD5, 0x78, 0x83, 0x32};
    unsigned char std_mac5[20] = {0x62, 0x83, 0x15, 0x6A, 0xAD, 0x36, 0xD6, 0x16, 0xE2, 0x59, 0x45, 0x36, 0xBE, 0x16, 0xA1, 0x91, 0xCD, 0x15, 0x35, 0x99};
    unsigned char std_mac6[20] = {0x3D, 0x1D, 0x95, 0xED, 0x73, 0x8E, 0xB6, 0x2B, 0x80, 0x3B, 0x66, 0x32, 0x33, 0x03, 0x37, 0x3B, 0xF0, 0xB6, 0x20, 0x33};
    unsigned int ret;

    ret = hmac_test(HASH_SHA1, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA1, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SM3
/**
 * @brief           Perform HMAC-SM3 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sm3_test(void)
{
    unsigned char std_mac1[32] = {0xC7, 0x30, 0xD1, 0x1F, 0x7A, 0x09, 0xE1, 0x65, 0xDC, 0x6E, 0xD6, 0x96, 0x4B, 0x49, 0x22, 0x52,
                                  0xB2, 0x5C, 0x07, 0x50, 0x8B, 0x3B, 0xAA, 0xD6, 0x28, 0x42, 0xAF, 0xE9, 0x2A, 0x45, 0x79, 0x0F};
    unsigned char std_mac2[32] = {0x14, 0xCC, 0xAD, 0xBE, 0xE9, 0x2A, 0x9B, 0xE2, 0x79, 0xC8, 0x49, 0xB7, 0x35, 0x9F, 0xAF, 0xAC,
                                  0x65, 0xA9, 0xF0, 0x4B, 0x15, 0x6F, 0xA8, 0x72, 0x3A, 0x72, 0x70, 0x0E, 0x50, 0x69, 0x27, 0xD5};
    unsigned char std_mac3[32] = {0xCC, 0x05, 0x07, 0x7B, 0x6F, 0x37, 0xC7, 0xE5, 0xA1, 0x9D, 0xC4, 0xEF, 0x00, 0x08, 0xD4, 0xEB,
                                  0x6B, 0xCD, 0xA8, 0xD7, 0xD6, 0x61, 0xCE, 0xF2, 0x22, 0x9D, 0xBA, 0xA1, 0x98, 0x8A, 0xE5, 0x50};
    unsigned char std_mac4[32] = {0x8A, 0x8B, 0xB2, 0x17, 0xA6, 0xA0, 0xC6, 0x0C, 0x7E, 0x81, 0x0C, 0x33, 0x9F, 0xBF, 0x82, 0x38,
                                  0x77, 0x54, 0x25, 0x80, 0xCF, 0x54, 0xD1, 0x33, 0x29, 0x02, 0xC4, 0xD7, 0x50, 0x73, 0x49, 0x39};
    unsigned char std_mac5[32] = {0x54, 0xDE, 0x55, 0x11, 0x30, 0x7B, 0xEB, 0x47, 0xA9, 0x62, 0x8C, 0x3B, 0x68, 0x30, 0xCF, 0xBB,
                                  0x55, 0x3F, 0x63, 0x89, 0xB6, 0xC5, 0x9F, 0x48, 0x12, 0x7E, 0x5B, 0xF8, 0xF0, 0xB0, 0x8D, 0x5D};
    unsigned char std_mac6[32] = {0xAE, 0xB2, 0x26, 0x53, 0x67, 0xF5, 0x14, 0x06, 0x4C, 0x57, 0x37, 0xA9, 0x04, 0x71, 0xD5, 0xBA,
                                  0xFC, 0x4F, 0x53, 0xA2, 0x66, 0x4A, 0xBF, 0x45, 0x3E, 0x50, 0xA2, 0xD9, 0x6E, 0x1C, 0xBD, 0xF9};
    unsigned int ret;

    ret = hmac_test(HASH_SM3, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SM3, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }

#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA224
/**
 * @brief           Perform HMAC-SHA224 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha224_test(void)
{
    unsigned char std_mac1[28] = {0xF4, 0x20, 0x89, 0x8A, 0xD4, 0x5F, 0x46, 0x12, 0x8B, 0x1D, 0xFD, 0x2D, 0x7D, 0xF3,
                                  0x11, 0x05, 0x0E, 0x84, 0x95, 0x97, 0x52, 0xA5, 0x35, 0xA0, 0x08, 0x02, 0xDE, 0xCE};
    unsigned char std_mac2[28] = {0xD6, 0x5B, 0x4A, 0x91, 0x6E, 0xD9, 0x98, 0xE7, 0x20, 0xEE, 0xE0, 0xEF, 0xA6, 0xC9,
                                  0x1E, 0x62, 0x3E, 0x96, 0x19, 0xF1, 0x0B, 0x07, 0x4F, 0x9C, 0x8A, 0x7C, 0x2D, 0x35};
    unsigned char std_mac3[28] = {0xFF, 0x6B, 0xCC, 0x17, 0x41, 0x12, 0xFB, 0x71, 0xB7, 0x36, 0x69, 0x07, 0xD5, 0x8A,
                                  0x16, 0x3D, 0x3F, 0x01, 0x7D, 0x30, 0x17, 0x2D, 0x28, 0x93, 0xD6, 0x47, 0xC9, 0xCF};
    unsigned char std_mac4[28] = {0x02, 0xFD, 0x7B, 0xE5, 0x70, 0xA8, 0x8C, 0x9C, 0x23, 0x5B, 0x1E, 0x98, 0xC3, 0x76,
                                  0x29, 0x08, 0x2C, 0x06, 0xE3, 0xC5, 0xAA, 0x31, 0xF5, 0x7D, 0x58, 0x35, 0xE2, 0xE6};
    unsigned char std_mac5[28] = {0xC3, 0x81, 0x12, 0x65, 0x5D, 0x56, 0x2C, 0x11, 0x73, 0xE2, 0xB7, 0x82, 0x36, 0x86,
                                  0x53, 0x29, 0xDC, 0x6E, 0x50, 0x48, 0x54, 0xBA, 0xD0, 0x09, 0xD9, 0x13, 0xE4, 0x11};
    unsigned char std_mac6[28] = {0x0F, 0x7F, 0x6E, 0x14, 0x17, 0xDD, 0x4F, 0xB3, 0x6A, 0x86, 0xF8, 0x4B, 0xC2, 0xF1,
                                  0xA0, 0x4C, 0xB3, 0xF9, 0x72, 0xA0, 0x53, 0x11, 0xBF, 0x6C, 0xC4, 0x9C, 0xBF, 0xA3};
    unsigned int ret;

    ret = hmac_test(HASH_SHA224, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA224, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA256
/**
 * @brief           Perform HMAC-SHA256 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha256_test(void)
{
    unsigned char std_mac1[32] = {0xCA, 0x7B, 0x86, 0xA2, 0xFB, 0xF0, 0x03, 0x1A, 0xCC, 0xFC, 0x5F, 0xD5, 0x8E, 0xD4, 0x60, 0xC3,
                                  0xAB, 0x2A, 0xEB, 0xAF, 0x8E, 0x86, 0xCB, 0xBC, 0x18, 0xC8, 0x38, 0xBC, 0x00, 0xAE, 0x87, 0xFF};
    unsigned char std_mac2[32] = {0x6A, 0xB5, 0x41, 0xB4, 0x86, 0x9D, 0xCA, 0x71, 0xC4, 0xCA, 0x11, 0xD8, 0xBB, 0x1B, 0x02, 0x53,
                                  0x3B, 0x78, 0x9A, 0x55, 0x75, 0x83, 0x16, 0x14, 0x29, 0x29, 0x2C, 0x74, 0x04, 0xBC, 0x21, 0xF6};
    unsigned char std_mac3[32] = {0xFB, 0x2A, 0xB7, 0xB5, 0xF0, 0x77, 0x00, 0x2B, 0x4B, 0x74, 0x71, 0xD0, 0x1B, 0x30, 0x18, 0x02,
                                  0x72, 0x09, 0xBA, 0x37, 0xF4, 0xC1, 0x30, 0x0D, 0x58, 0xA6, 0x7E, 0x2E, 0xB0, 0xCC, 0x15, 0x77};
    unsigned char std_mac4[32] = {0x15, 0xC4, 0xC7, 0x67, 0x68, 0xB8, 0xF5, 0x46, 0xB6, 0x7C, 0x45, 0x5F, 0xC7, 0xA2, 0x62, 0xE6,
                                  0x05, 0x52, 0x7D, 0x7A, 0xE2, 0x33, 0x57, 0x03, 0x39, 0xC5, 0x1E, 0x6E, 0x5B, 0x2E, 0x47, 0x7A};
    unsigned char std_mac5[32] = {0xBA, 0xB3, 0xE1, 0x6A, 0x66, 0x8A, 0x29, 0xAF, 0x19, 0x46, 0x5C, 0x8C, 0x82, 0x03, 0x9E, 0x28,
                                  0x25, 0xAA, 0x06, 0x6C, 0x7C, 0x9C, 0xE0, 0x3C, 0xB4, 0x47, 0x88, 0xC5, 0xF0, 0x0D, 0x1C, 0x7F};
    unsigned char std_mac6[32] = {0xAA, 0xB0, 0x14, 0xF6, 0x93, 0x9D, 0x50, 0x1E, 0x09, 0xF6, 0xB7, 0xC3, 0x86, 0xB3, 0x9C, 0x48,
                                  0xD8, 0x52, 0x48, 0x3A, 0xE6, 0x09, 0x94, 0x6E, 0x6A, 0x7E, 0x0F, 0x23, 0x2D, 0xAB, 0xE0, 0xA4};
    unsigned int ret;

    ret = hmac_test(HASH_SHA256, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA256, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA384
/**
 * @brief           Perform HMAC-SHA384 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha384_test(void)
{
    unsigned char std_mac1[48] = {
        0x33,
        0x7F,
        0xDC,
        0x69,
        0xD3,
        0x4B,
        0x81,
        0x52,
        0x35,
        0x5B,
        0x11,
        0xAF,
        0xA9,
        0x4C,
        0xE9,
        0x26,
        0x3E,
        0x97,
        0xFC,
        0xE0,
        0x64,
        0xB7,
        0x60,
        0xD0,
        0x48,
        0x94,
        0x86,
        0x95,
        0x0A,
        0xF5,
        0xE5,
        0xC9,
        0x36,
        0x45,
        0x88,
        0xF2,
        0x41,
        0x16,
        0x20,
        0xD8,
        0xAA,
        0x55,
        0x44,
        0xDE,
        0x2A,
        0xD7,
        0xEF,
        0xE9,
    };
    unsigned char std_mac2[48] = {
        0x62,
        0x7B,
        0x51,
        0x3F,
        0x45,
        0xBA,
        0x31,
        0xB9,
        0xD7,
        0xE0,
        0x18,
        0x29,
        0x8D,
        0xEE,
        0xF5,
        0x23,
        0xBA,
        0x93,
        0xE0,
        0x26,
        0x8C,
        0x77,
        0xC6,
        0x33,
        0xB5,
        0xCC,
        0xC0,
        0x49,
        0xCE,
        0x41,
        0xEC,
        0x94,
        0x0C,
        0x33,
        0xE5,
        0x08,
        0xF0,
        0x74,
        0x2D,
        0xB2,
        0x3B,
        0x94,
        0xD0,
        0x7E,
        0xC7,
        0xCE,
        0x86,
        0xF0,
    };
    unsigned char std_mac3[48] = {
        0x73,
        0x30,
        0x35,
        0xA1,
        0x60,
        0xEF,
        0xA5,
        0x7F,
        0xBB,
        0x76,
        0x88,
        0x94,
        0x00,
        0x76,
        0xCD,
        0x86,
        0x1E,
        0x61,
        0x56,
        0x22,
        0x8E,
        0xFA,
        0xBA,
        0xFC,
        0x24,
        0xA2,
        0x56,
        0xD2,
        0x0A,
        0x40,
        0x49,
        0x63,
        0x24,
        0xC4,
        0x83,
        0x15,
        0xAC,
        0x5B,
        0x97,
        0xC1,
        0xA1,
        0x77,
        0x11,
        0x8E,
        0x6A,
        0x63,
        0x41,
        0x51,
    };
    unsigned char std_mac4[48] = {
        0x88,
        0x34,
        0xD0,
        0x20,
        0x3D,
        0x61,
        0x95,
        0xFD,
        0x05,
        0x67,
        0x25,
        0xE6,
        0x1C,
        0xA1,
        0x42,
        0xF1,
        0x9B,
        0x27,
        0x88,
        0x89,
        0xDB,
        0x93,
        0x16,
        0x60,
        0x5B,
        0xA1,
        0xD8,
        0x10,
        0xF7,
        0x45,
        0xBE,
        0xDD,
        0x8F,
        0xAE,
        0x04,
        0x86,
        0xE5,
        0xE2,
        0xF5,
        0xF6,
        0x78,
        0x4A,
        0xC8,
        0x60,
        0x7A,
        0xC8,
        0x5A,
        0x65,
    };
    unsigned char std_mac5[48] = {
        0xF3,
        0xAC,
        0x1F,
        0x24,
        0xDF,
        0x89,
        0xE7,
        0x1C,
        0xE6,
        0x9F,
        0x09,
        0xDC,
        0x0B,
        0xA7,
        0x1C,
        0xF0,
        0x34,
        0xD5,
        0x21,
        0x54,
        0xE7,
        0x34,
        0x22,
        0x89,
        0xE3,
        0x07,
        0xEE,
        0x13,
        0x44,
        0xE0,
        0x73,
        0xE1,
        0x30,
        0xEF,
        0xD0,
        0xBE,
        0xC8,
        0x72,
        0xCC,
        0xD6,
        0xFB,
        0x66,
        0xDE,
        0xB3,
        0x06,
        0x9F,
        0x6A,
        0xA7,
    };
    unsigned char std_mac6[48] = {
        0xFA,
        0x84,
        0xF0,
        0x6F,
        0xDC,
        0x96,
        0x09,
        0x04,
        0x7E,
        0xC5,
        0xFC,
        0xCE,
        0x27,
        0xBC,
        0xCA,
        0xDE,
        0x11,
        0x68,
        0x60,
        0xFC,
        0x0E,
        0xEE,
        0x4B,
        0xC5,
        0xA3,
        0x01,
        0xFF,
        0xB7,
        0x7C,
        0xA3,
        0x72,
        0x97,
        0xDD,
        0x19,
        0xC5,
        0x68,
        0x64,
        0x4F,
        0xD6,
        0xBC,
        0x85,
        0x98,
        0xB2,
        0x8F,
        0xF9,
        0xBD,
        0xC0,
        0x4C,
    };
    unsigned int ret;

    ret = hmac_test(HASH_SHA384, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA384, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512
/**
 * @brief           Perform HMAC-SHA512 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha512_test(void)
{
    unsigned char std_mac1[64] = {0xBB, 0xEA, 0xBE, 0xBC, 0xD0, 0xDE, 0x16, 0x29, 0x81, 0x36, 0x22, 0xA2, 0x6C, 0x83, 0x5E, 0x61, 0x91, 0xF9, 0x94, 0x15, 0xE6, 0xEA,
                                  0xE9, 0x2A, 0xF0, 0x56, 0x4F, 0xC6, 0xED, 0x05, 0x36, 0x22, 0x70, 0x7D, 0x1B, 0xFA, 0x99, 0x34, 0xDE, 0x3F, 0x06, 0x85, 0x55, 0xA2,
                                  0x84, 0x56, 0x9A, 0xD7, 0xA2, 0xF9, 0xE0, 0x96, 0xFA, 0x92, 0xE4, 0x75, 0xC7, 0x71, 0xAE, 0x7C, 0x84, 0xED, 0x03, 0xDA};
    unsigned char std_mac2[64] = {0xB6, 0x3D, 0x28, 0xCD, 0x59, 0x3A, 0xD7, 0xE8, 0xF0, 0xE3, 0x16, 0x83, 0x67, 0x47, 0x14, 0x41, 0xD9, 0x66, 0x8B, 0x5F, 0xB9, 0x70,
                                  0xA6, 0x20, 0x99, 0x4E, 0x8E, 0x1C, 0x7B, 0x02, 0xD0, 0xD2, 0xB1, 0x7F, 0x55, 0xEB, 0x1B, 0xF5, 0x91, 0x64, 0x65, 0xAE, 0x8B, 0xFC,
                                  0xAF, 0xAD, 0x70, 0x6E, 0x29, 0xCB, 0xE2, 0x58, 0xAC, 0x4A, 0x2D, 0x40, 0x14, 0x19, 0x0E, 0xC0, 0xB3, 0xAB, 0xE8, 0x27};
    unsigned char std_mac3[64] = {0x39, 0x3B, 0xE5, 0x8E, 0xE8, 0x5F, 0x09, 0x50, 0x23, 0x08, 0x85, 0xE5, 0x2E, 0xAB, 0xCC, 0x6F, 0x88, 0x81, 0xB3, 0x1E, 0x6C, 0x23,
                                  0x3B, 0x28, 0x17, 0x45, 0x46, 0x7C, 0x9A, 0xFF, 0x48, 0xC0, 0x46, 0x2F, 0x86, 0x7A, 0x37, 0x62, 0x5A, 0xC7, 0x31, 0x05, 0x85, 0xAB,
                                  0xFD, 0x02, 0x46, 0xA8, 0xB0, 0x78, 0x1F, 0xA5, 0x3F, 0xC0, 0x88, 0x82, 0x51, 0x66, 0x85, 0x7D, 0x3E, 0xD2, 0x5A, 0xE9};
    unsigned char std_mac4[64] = {0x3E, 0xAD, 0x33, 0x30, 0xF7, 0x29, 0x31, 0xB4, 0x32, 0x6C, 0xD5, 0x43, 0x1E, 0x59, 0xDD, 0x39, 0xBE, 0x83, 0xDD, 0x3D, 0x13, 0x52,
                                  0xD7, 0x2E, 0x0D, 0x46, 0x0F, 0x7F, 0xB9, 0x5D, 0x48, 0x8C, 0x26, 0x06, 0xD5, 0xF8, 0xFB, 0x9A, 0x97, 0x87, 0x1E, 0x9B, 0xCC, 0xA5,
                                  0x23, 0xA8, 0xB7, 0x2D, 0x5B, 0x78, 0x97, 0x63, 0x8D, 0x70, 0xF2, 0x3B, 0x95, 0xF6, 0x5E, 0x68, 0x34, 0xC4, 0x91, 0x26};
    unsigned char std_mac5[64] = {0x26, 0x18, 0x2B, 0x29, 0x50, 0x82, 0x26, 0x34, 0xE9, 0x6B, 0x2C, 0xF0, 0x18, 0x21, 0xD3, 0xDF, 0x3D, 0xCE, 0x2C, 0x46, 0x97, 0xAD,
                                  0x50, 0x01, 0x38, 0x72, 0x7E, 0xD9, 0x8A, 0x8B, 0x50, 0x2C, 0xE4, 0x21, 0x0E, 0x67, 0x9A, 0xC8, 0x5C, 0x76, 0xB4, 0x4B, 0x41, 0x07,
                                  0x0B, 0x5C, 0x43, 0xCA, 0x77, 0xB7, 0xDD, 0x36, 0xE5, 0xE9, 0x30, 0x79, 0xFE, 0xF9, 0x31, 0x95, 0xE9, 0x94, 0x4F, 0xC8};
    unsigned char std_mac6[64] = {0xAF, 0xB6, 0x5E, 0x03, 0x86, 0x74, 0x9A, 0x5D, 0xB0, 0xA9, 0x7E, 0xC7, 0xBE, 0x89, 0x44, 0x90, 0x6D, 0x66, 0x62, 0x62, 0x34, 0x42,
                                  0x44, 0x25, 0x9F, 0x91, 0x60, 0xF9, 0x9B, 0xCB, 0x56, 0x16, 0xDA, 0x7D, 0xF1, 0x85, 0x2E, 0x51, 0x0A, 0x30, 0x9A, 0x73, 0x9D, 0x9B,
                                  0x95, 0xB0, 0x1B, 0x99, 0xBF, 0x5B, 0x07, 0x21, 0x18, 0x4A, 0xA9, 0xF0, 0xEE, 0xA3, 0x59, 0x5B, 0x07, 0x26, 0xFE, 0x65};
    unsigned int ret;

    ret = hmac_test(HASH_SHA512, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA512, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512_224
/**
 * @brief           Perform HMAC-SHA512-224 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha512_224_test(void)
{
    unsigned char std_mac1[28] = {
        0x38,
        0x80,
        0x12,
        0x74,
        0x68,
        0x49,
        0x93,
        0xE0,
        0x9E,
        0xA9,
        0xEF,
        0x53,
        0x55,
        0xC4,
        0xF8,
        0xAD,
        0xC9,
        0x00,
        0x87,
        0xAF,
        0xDF,
        0xCF,
        0x3D,
        0xEC,
        0xF5,
        0x25,
        0xC9,
        0xF6,
    };
    unsigned char std_mac2[28] = {
        0x14,
        0x2D,
        0x9A,
        0x66,
        0x64,
        0x1A,
        0x89,
        0x63,
        0x3D,
        0x84,
        0x19,
        0xB1,
        0x9E,
        0x84,
        0x6D,
        0x33,
        0xE9,
        0x67,
        0x14,
        0x69,
        0xE7,
        0x2F,
        0xB7,
        0x96,
        0x5C,
        0x24,
        0xAD,
        0x47,
    };
    unsigned char std_mac3[28] = {
        0x09,
        0x07,
        0x55,
        0x93,
        0xD2,
        0x7D,
        0x42,
        0x48,
        0xB9,
        0x2B,
        0x66,
        0x08,
        0x5C,
        0x6E,
        0x47,
        0xEC,
        0x50,
        0xDA,
        0x3F,
        0xE9,
        0x5C,
        0x6A,
        0x21,
        0x9D,
        0xCA,
        0x8C,
        0x00,
        0xE1,
    };
    unsigned char std_mac4[28] = {
        0xC3,
        0x25,
        0x31,
        0xC8,
        0xF7,
        0x7D,
        0xD8,
        0xB6,
        0x59,
        0x98,
        0xF9,
        0x72,
        0x8D,
        0x3D,
        0x34,
        0xD3,
        0xFF,
        0xBB,
        0x45,
        0x15,
        0xE3,
        0x0A,
        0x3B,
        0xCD,
        0x17,
        0xA7,
        0xA4,
        0x9D,
    };
    unsigned char std_mac5[28] = {
        0x51,
        0x47,
        0x22,
        0x94,
        0x7A,
        0x70,
        0x8E,
        0xCB,
        0xF8,
        0xDA,
        0x62,
        0xEC,
        0x07,
        0xD9,
        0xD9,
        0x43,
        0x21,
        0x4B,
        0x5A,
        0x65,
        0xD7,
        0xC7,
        0xBD,
        0x58,
        0x5A,
        0x8F,
        0xCF,
        0x65,
    };
    unsigned char std_mac6[28] = {
        0x83,
        0xFB,
        0x45,
        0xAC,
        0x4A,
        0x62,
        0x4C,
        0xB3,
        0x95,
        0x45,
        0x73,
        0xC9,
        0x49,
        0xE0,
        0x5F,
        0x74,
        0x89,
        0x13,
        0x69,
        0xE7,
        0x09,
        0x5F,
        0x13,
        0xEF,
        0x77,
        0xC1,
        0x76,
        0x93,
    };
    unsigned int ret;

    ret = hmac_test(HASH_SHA512_224, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA512_224, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512_256
/**
 * @brief           Perform HMAC-SHA512-256 algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_sha512_256_test(void)
{
    unsigned char std_mac1[32] = {
        0x60,
        0x5B,
        0xD9,
        0x34,
        0xE6,
        0x6E,
        0x6C,
        0xB5,
        0x9A,
        0x04,
        0x9D,
        0x16,
        0xFF,
        0xD3,
        0xD2,
        0x6C,
        0xC3,
        0x5D,
        0x90,
        0x38,
        0xBE,
        0x55,
        0x30,
        0x72,
        0xF5,
        0x1E,
        0xD4,
        0x79,
        0x27,
        0xA7,
        0x3E,
        0x68,
    };
    unsigned char std_mac2[32] = {
        0x99,
        0xCF,
        0xF5,
        0xCD,
        0xC7,
        0xB8,
        0xF8,
        0x5F,
        0x2C,
        0xE5,
        0x01,
        0xDA,
        0x6A,
        0x0D,
        0x1B,
        0xAE,
        0xBD,
        0x7E,
        0xDA,
        0x0F,
        0x19,
        0x34,
        0x16,
        0x66,
        0x11,
        0xD9,
        0xDD,
        0xF6,
        0x44,
        0x4A,
        0xF2,
        0x50,
    };
    unsigned char std_mac3[32] = {
        0x2C,
        0xA2,
        0xB3,
        0xB5,
        0x7A,
        0x9C,
        0xFC,
        0x97,
        0x69,
        0xA7,
        0x4F,
        0x65,
        0x39,
        0x2F,
        0x41,
        0xD4,
        0x9C,
        0x3B,
        0x9A,
        0x00,
        0x88,
        0xFC,
        0x9D,
        0x22,
        0x13,
        0x89,
        0xA4,
        0x9D,
        0x90,
        0x47,
        0x1D,
        0xC3,
    };
    unsigned char std_mac4[32] = {
        0x0C,
        0xD2,
        0xED,
        0x0D,
        0x53,
        0xC0,
        0x4C,
        0x0E,
        0x89,
        0xFB,
        0x05,
        0xC9,
        0x67,
        0x17,
        0xC8,
        0x4A,
        0x2D,
        0xB4,
        0xF8,
        0x5A,
        0xB5,
        0xF7,
        0x55,
        0xBB,
        0x9F,
        0x25,
        0x7C,
        0xA6,
        0x96,
        0x31,
        0x38,
        0x81,
    };
    unsigned char std_mac5[32] = {
        0x07,
        0x90,
        0x58,
        0xEF,
        0xA6,
        0xF1,
        0x1B,
        0x8D,
        0xE4,
        0x1A,
        0xF8,
        0xC8,
        0x63,
        0x6E,
        0xEE,
        0x2D,
        0x05,
        0xE7,
        0x25,
        0x49,
        0xAC,
        0x7C,
        0x4E,
        0x0B,
        0x95,
        0xFD,
        0x2D,
        0x65,
        0x6D,
        0x86,
        0x50,
        0x10,
    };
    unsigned char std_mac6[32] = {
        0xEA,
        0xDD,
        0xF0,
        0x90,
        0x67,
        0x9C,
        0x90,
        0xC9,
        0x08,
        0x65,
        0x6A,
        0xF2,
        0x74,
        0x1E,
        0xBE,
        0xBF,
        0xED,
        0x93,
        0xC4,
        0x8F,
        0x70,
        0xCB,
        0x56,
        0xD0,
        0x6F,
        0xB8,
        0x8C,
        0x05,
        0x52,
        0xAC,
        0x6A,
        0xA0,
    };
    unsigned int ret;

    ret = hmac_test(HASH_SHA512_256, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5, std_mac6);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hmac_dma_test(HASH_SHA512_256, std_mac1, std_mac2, std_mac3, std_mac4, std_mac5);
    if (ret)
    {
        return 1;
    }
#endif

    return ret;
}
#endif

/**
 * @brief           Perform comprehensive tests for all supported HMAC algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hmac_all_test(void)
{
    printf("\r\n\r\n =================== HMAC test =================== ");
    fflush(stdout);

#ifdef SUPPORT_HASH_SM3
    if (hmac_sm3_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_MD5
    if (hmac_md5_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA256
    if (hmac_sha256_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA384
    if (hmac_sha384_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512
    if (hmac_sha512_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA1
    if (hmac_sha1_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA224
    if (hmac_sha224_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_224
    if (hmac_sha512_224_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_256
    if (hmac_sha512_256_test())
    {
        return 1;
    }
#endif

    printf("\r\n\r\n HMAC test success \r\n\r\n");
    fflush(stdout);

    return 0;
}

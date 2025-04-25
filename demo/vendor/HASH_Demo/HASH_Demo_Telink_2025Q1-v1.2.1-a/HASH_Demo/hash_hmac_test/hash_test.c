/********************************************************************************************************
 * @file    hash_test.c
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
#include "common.h"
#include "hash_hmac_test/app_test.h"

#include "lib/include/hash/hash.h"
#include "lib/include/crypto_common/utility.h"
#include "lib/include/trng/trng.h"

#ifdef HASH_SPEED_TEST_BY_TIMER
extern unsigned int startP(void);
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif

#ifdef HASH_SPEED_TEST_BY_TIMER
extern unsigned int startp(void);
extern unsigned int endp(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif

/**
 * @brief           Generate a random number within a specified range
 * @param[in]       max_number           - The upper limit for the random number
 * @return          A random number between 1 and max_number-1
 */
unsigned int hash_get_rand_number(unsigned int max_number)
{
    static unsigned int i = 34;

    get_rand((unsigned char *)&i, 4);

    i = i % max_number;
    if (0 == i)
    {
        i = 1;
    }

    return i;
}

/**
 * @brief           Callback function for hash operations
 */
void hash_call_manage(void)
{
    // printf("call manage???\n");
    // return;
}

/**
 * @brief           Perform hash algorithm tests
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       std_digest1          - Expected digest for test case 1
 * @param[in]       std_digest2          - Expected digest for test case 2
 * @param[in]       std_digest3          - Expected digest for test case 3
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_test(hash_alg_e alg, unsigned char *std_digest1, unsigned char *std_digest2, unsigned char *std_digest3)
{
    unsigned char message[500];
    unsigned char digest[64];
    unsigned int iterator[HASH_ITERATOR_MAX_WORD_LEN];
    unsigned int block_bytes = hash_get_block_word_len(alg) << 2;
    hash_ctx_t hash_ctx[1];

    char *name[] = {"SM3", "MD5", "SHA256", "SHA384", "SHA512", "SHA1", "SHA224", "SHA512_224", "SHA512_256"};
    unsigned char outLen[] = {32, 16, 32, 48, 64, 20, 28, 28, 32};
    unsigned int msg_len;
    unsigned int i, j, total;

    unsigned int len[5][15] = // sum of each line is 500
        {
            {4, 91, 173, 23, 56, 79, 2, 11, 61, 0, 0, 0, 0, 0, 0}, // padding with 0 to avoid some bad compiler's error(memset not found)
            {84, 37, 68, 293, 13, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0},
            {33, 20, 208, 3, 7, 67, 33, 88, 19, 22, 0, 0, 0, 0, 0},
            {59, 111, 29, 34, 27, 89, 9, 6, 79, 22, 35, 0, 0, 0, 0},
            {333, 2, 5, 39, 77, 16, 24, 4, 0, 0, 0, 0, 0, 0, 0},
        };

    unsigned int ret;

#ifdef SUPPORT_HASH_NODE
    hash_node_t node[4];
#endif

    memcpy_(message, (unsigned char *)"abc", 3); // to avoid some bad compiler's error(memset not found)

    printf("\r\n -------------- %s test -------------- ", name[alg]);

    /*************************** test1 ***************************/
    ret = hash_init(hash_ctx, alg);
    ret |= hash_update(hash_ctx, message, 3);
    ret |= hash_final(hash_ctx, digest);

    if (HASH_SUCCESS != ret || memcmp_(digest, std_digest1, outLen[alg]))
    {
        printf("\r\n %s test 1 failure, ret=%u\r\n", name[alg], ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8(digest, outLen[alg], "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s test 1 success ", name[alg]);
    }

    /*************************** test2 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }
    msg_len = 500;

    // test2-1
    ret = hash(alg, message, msg_len, digest);
    if (HASH_SUCCESS != ret || memcmp_(digest, std_digest2, outLen[alg]))
    {
        printf("\r\n %s test 2-%u failure, ret=%u \r\n", name[alg], 1, ret);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8(digest, outLen[alg], "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s test 2-%u success ", name[alg], 1);
    }

    // test2-2...2-6
    for (i = 0; i < 5; i++)
    {
        j = 0;
        total = 0;
        memset_(digest, 0, sizeof(digest));

        ret = hash_init(hash_ctx, alg);

        while (len[i][j])
        {
            ret |= hash_update(hash_ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        ret |= hash_final(hash_ctx, digest);
        if (HASH_SUCCESS != ret || memcmp_(digest, std_digest2, outLen[alg]))
        {
            printf("\r\n %s test 2-%u failure, ret=%u \r\n", name[alg], i + 2, ret);
            print_buf_U8(digest, outLen[alg], "digest");
            return 1;
        }
        else
        {
            printf("\r\n %s test 2-%u success", name[alg], i + 2);
        }
    }

    // test2-7
    memset_(digest, 0, sizeof(digest));
    // step 1. init, input one block and stop, get iterator and backup it.
    ret = hash_init(hash_ctx, alg);
    ret |= hash_update(hash_ctx, message, block_bytes);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n %s test 2-7 init and update failure, ret=%u \r\n", name[alg], ret);
        return 1;
    }
#ifdef CONFIG_HASH_SUPPORT_MUL_THREAD
    memcpy_((unsigned char *)iterator, (unsigned char *)hash_ctx->iterator, (hash_ctx->iterator_word_len) << 2);
#else
    hash_get_iterator((unsigned char *)iterator, hash_ctx->iterator_word_len);
#endif
    // step 2. release resource(clear ctx) and do some other things
    memset_((unsigned char *)hash_ctx, 0, sizeof(hash_ctx));
    //...
    // step 3. continue till end
    ret = hash_init_with_iv_and_updated_length(hash_ctx, alg, iterator, 0, block_bytes); // not hash_ctx->block_byte_len
    ret |= hash_update(hash_ctx, message + block_bytes, msg_len - block_bytes);
    ret |= hash_final(hash_ctx, digest);
    if (HASH_SUCCESS != ret || memcmp_(digest, std_digest2, outLen[alg]))
    {
        printf("\r\n %s test 2-7 failure, ret=%u \r\n", name[alg], ret);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8(digest, outLen[alg], "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s test 2-7 success ", name[alg]);
    }

    // test2-8...
    printf("\r\n");
    for (i = 0; i < 100; i++)
    {
        total = 0;
        memset_(digest, 0, sizeof(digest));

        ret = hash_init(hash_ctx, alg);

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

            if (j > msg_len - total)
            {
                j = msg_len - total;
            }

            ret |= hash_update(hash_ctx, message + total, j);
            total += j;
        }

        ret |= hash_final(hash_ctx, digest);
        if (HASH_SUCCESS != ret || memcmp_(digest, std_digest2, outLen[alg]))
        {
            printf("\r\n %s test 2-%u failure, ret=%u \r\n", name[alg], i + 8, ret); // fflush(stdout);
            print_buf_U8(digest, outLen[alg], "digest");
            return 1;
        }
        else
        {
            // printf("\r\n %s test 2-%u success ", name[alg], i+8);
            printf("2-%u ", i + 8); // fflush(stdout);
        }
    }

#ifdef SUPPORT_HASH_NODE
    // test 2-final
    memset_(digest, 0, sizeof(digest));
    node[0].msg_addr = message;
    node[0].msg_len = 10;
    node[1].msg_addr = node[0].msg_addr + node[0].msg_len;
    node[1].msg_len = 190;
    node[2].msg_addr = node[1].msg_addr + node[1].msg_len;
    node[2].msg_len = 1;
    node[3].msg_addr = node[2].msg_addr + node[2].msg_len;
    node[3].msg_len = msg_len - 10 - 190 - 1;
    ret = hash_node_steps(alg, node, 4, digest);
    if (HASH_SUCCESS != ret || memcmp_(digest, std_digest2, outLen[alg]))
    {
        printf("\r\n %s test 2-final(hash node style) failure, ret=%u \r\n", name[alg], ret);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8(digest, outLen[alg], "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s test 2-final(hash node style) success ", name[alg]);
    }
#endif

    /*************************** test3 ***************************/
    for (i = 0; i < 500; i++)
    {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++)
    {
        j = hash_get_rand_number(2);

        if (j)
        {
            ret |= hash_init(hash_ctx, alg);
            ret |= hash_update(hash_ctx, message, i);
            ret |= hash_final(hash_ctx, message);
        }
        else
        {
            ret |= hash(alg, message, i, message);
        }
    }

    if (HASH_SUCCESS != ret || memcmp_(message, std_digest3, outLen[alg]))
    {
        printf("\r\n %s test 3 failure, ret=%u \r\n", name[alg], ret);
        print_buf_U8(message, outLen[alg], "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s test 3 success", name[alg]);
    }

    printf("\r\n");

    return 0;
}

#define HASH_SPEED_TEST_ROUND (40960)
#define HASH_SPEED_TEST_BYTE_LEN (1024)
#define HASH_DMA_SPEED_TEST_ROUND (5120)
#define HASH_DMA_SPEED_TEST_BYTE_LEN (1024 * 16) // 16K

/**
 * @brief           Internal function for hash speed testing
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       round                - Number of iterations for the test
 * @param[in]       once_bytes           - Number of bytes to process in each iteration
 * @return          0 if test succeeds, non-zero error code if test fails
 */
unsigned int hash_speed_test_internal(hash_alg_e alg, unsigned int round, unsigned int once_bytes)
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
    unsigned char message[8192];
    unsigned char digest[64];
    unsigned int i;
    unsigned int ret;
    hash_ctx_t ctx[1];

    uint32_sleep(0xFFFFF, 1);

    printf("\r\n===================== HASH %s CPU begin =====================", name_alg[alg]);
    fflush(stdout);

#ifdef HASH_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = hash_init(ctx, alg);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n init error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++)
    {
        ret = hash_update(ctx, message, once_bytes);
        if (HASH_SUCCESS != ret)
        {
            printf("\r\n update error ret=%u", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = hash_final(ctx, digest);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n final error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

#ifdef HASH_SPEED_TEST_BY_TIMER
    endp(0, once_bytes, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform speed tests for all supported hash algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_speed_test(void)
{
    unsigned int bytes = HASH_SPEED_TEST_BYTE_LEN;
    unsigned int round = HASH_SPEED_TEST_ROUND;

#ifdef HASH_SPEED_TEST_BY_TIMER
    round = 1024;
#endif

#ifdef SUPPORT_HASH_SM3
    hash_speed_test_internal(HASH_SM3, round, bytes);
#endif

#ifdef SUPPORT_HASH_MD5
    hash_speed_test_internal(HASH_MD5, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA256
    hash_speed_test_internal(HASH_SHA256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA384
    hash_speed_test_internal(HASH_SHA384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512
    hash_speed_test_internal(HASH_SHA512, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA1
    hash_speed_test_internal(HASH_SHA1, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA224
    hash_speed_test_internal(HASH_SHA224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_224
    hash_speed_test_internal(HASH_SHA512_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_256
    hash_speed_test_internal(HASH_SHA512_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_224
    hash_speed_test_internal(HASH_SHA3_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_256
    hash_speed_test_internal(HASH_SHA3_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_384
    hash_speed_test_internal(HASH_SHA3_384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_512
    hash_speed_test_internal(HASH_SHA3_512, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA256
    round = HASH_SPEED_TEST_ROUND;
#ifdef HASH_SPEED_TEST_BY_TIMER
    round = 1024;
#endif
    hash_speed_test_internal(HASH_SHA256, round * 32, 32);
    hash_speed_test_internal(HASH_SHA256, round * 16, 64);
    hash_speed_test_internal(HASH_SHA256, round * 8, 128);
    hash_speed_test_internal(HASH_SHA256, round * 4, 256);
    hash_speed_test_internal(HASH_SHA256, round * 2, 512);
    hash_speed_test_internal(HASH_SHA256, round, 1024);
    hash_speed_test_internal(HASH_SHA256, round / 4, 4096);
    hash_speed_test_internal(HASH_SHA256, round / 8, 8192);
#endif

    return 0;
}

#ifdef HASH_DMA_FUNCTION
/**
 * @brief           Internal function for DMA hash speed testing
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       round                - Number of iterations for the test
 * @param[in]       once_bytes           - Number of bytes to process in each iteration
 * @return          0 if test succeeds, non-zero error code if test fails
 */
unsigned int hash_dma_speed_test_internal(hash_alg_e alg, unsigned int round, unsigned int once_bytes)
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
    unsigned int i, block_byte_len;
    unsigned int *msg = (unsigned int *)(HASH_DMA_RAM_BASE);
    unsigned int *digest = msg + 512;
    unsigned int ret;
    hash_dma_ctx_t ctx[1];

    uint32_sleep(0xFFFFF, 1);

    // this is for SHA3, since its block byte length is 72/104/136/144
    block_byte_len = hash_get_block_word_len(alg) * 4;
    once_bytes = (once_bytes / block_byte_len) * block_byte_len;

    printf("\r\n===================== HASH %s DMA begin =====================", name_alg[alg]);
    fflush(stdout);

#ifdef HASH_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = hash_dma_init(ctx, alg, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n dma init error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++)
    {
        ret = hash_dma_update_blocks(ctx, msg, once_bytes);
        if (HASH_SUCCESS != ret)
        {
            printf("\r\n dma update error ret=%u", ret);
            fflush(stdout);
            return 1;
        }
    }

    //        for(i=0;i<100000;i++)
    //        {
    //            ret = hash_dma_update_blocks(ctx, msg, 3072/4);
    //        }

    ret = hash_dma_final(ctx, msg, 0, digest);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n dma final error ret=%u", ret);
        fflush(stdout);
        return 1;
    }

#ifdef HASH_SPEED_TEST_BY_TIMER
    endp(0, once_bytes, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform DMA speed tests for all supported hash algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_dma_speed_test(void)
{
    unsigned int round = HASH_DMA_SPEED_TEST_ROUND;
    unsigned int bytes = HASH_DMA_SPEED_TEST_BYTE_LEN;

#ifdef HASH_SPEED_TEST_BY_TIMER
    round = 512;
#endif

#ifdef SUPPORT_HASH_SM3
    hash_dma_speed_test_internal(HASH_SM3, round, bytes);
#endif

#ifdef SUPPORT_HASH_MD5
    hash_dma_speed_test_internal(HASH_MD5, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA256
    hash_dma_speed_test_internal(HASH_SHA256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA384
    hash_dma_speed_test_internal(HASH_SHA384, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512
    hash_dma_speed_test_internal(HASH_SHA512, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA1
    hash_dma_speed_test_internal(HASH_SHA1, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA224
    hash_dma_speed_test_internal(HASH_SHA224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_224
    hash_dma_speed_test_internal(HASH_SHA512_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA512_256
    hash_dma_speed_test_internal(HASH_SHA512_256, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_224
    hash_dma_speed_test_internal(HASH_SHA3_224, round, bytes);
#endif

#ifdef SUPPORT_HASH_SHA3_256
//    hash_dma_speed_test_internal(HASH_SHA3_256);
#endif

#ifdef SUPPORT_HASH_SHA3_384
//    hash_dma_speed_test_internal(HASH_SHA3_384);
#endif

#ifdef SUPPORT_HASH_SHA3_512
//    hash_dma_speed_test_internal(HASH_SHA3_512);
#endif

#ifdef SUPPORT_HASH_SHA256
    round = HASH_DMA_SPEED_TEST_ROUND / 2;
#ifdef HASH_SPEED_TEST_BY_TIMER
    round = 512;
#endif
    // hash_dma_speed_test_internal(HASH_SHA256, round*256, 32); //do not use this line, since block is 512bit.
    hash_dma_speed_test_internal(HASH_SHA256, round * 128, 64);
    hash_dma_speed_test_internal(HASH_SHA256, round * 64, 128);
    hash_dma_speed_test_internal(HASH_SHA256, round * 32, 256);
    hash_dma_speed_test_internal(HASH_SHA256, round * 16, 512);
    hash_dma_speed_test_internal(HASH_SHA256, round * 8, 1024);
    hash_dma_speed_test_internal(HASH_SHA256, round * 2, 4096);
    hash_dma_speed_test_internal(HASH_SHA256, round, 8192);
    hash_dma_speed_test_internal(HASH_SHA256, round / 2, 16384);
#endif

    return 0;
}

/**
 * @brief           Perform DMA hash algorithm tests
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       std_digest1          - Expected digest for test case 1
 * @param[in]       std_digest2          - Expected digest for test case 2
 * @param[in]       std_digest3          - Expected digest for test case 3
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_dma_test(hash_alg_e alg, unsigned char *std_digest1, unsigned char *std_digest2, unsigned char *std_digest3)
{
    hash_dma_ctx_t ctx[1];
    unsigned char tmp_buf[500];
    unsigned char message[500];
    unsigned int iterator[HASH_ITERATOR_MAX_WORD_LEN];

    unsigned int block_word_len, block_byte_len, output_word_len, digest_byte_len, iterator_word_len;
    char *name[] = {"SM3", "MD5", "SHA_256", "SHA_384", "SHA_512", "SHA_1", "SHA_224", "SHA_512_224", "SHA_512_256"};
    unsigned int *msg = (unsigned int *)(HASH_DMA_RAM_BASE);
    unsigned int *digest = msg + 512;

    unsigned int msg_len;
    unsigned int i, j, total;
    unsigned int ret;

#ifdef SUPPORT_HASH_DMA_NODE
    hash_dma_node_t hash_dma_node[4];
#endif

    memset_(message, 0, sizeof(message));
    memcpy_(message, (unsigned char *)"abc", 3); // to avoid some bad compiler's error(memset not found)

    printf("\r\n ------------ %s DMA test ------------ ", name[alg]);

    block_word_len = hash_get_block_word_len(alg);
    block_byte_len = block_word_len << 2;
    digest_byte_len = hash_get_digest_word_len(alg) << 2;
    output_word_len = ((digest_byte_len + 15) / 16) * 4; // must be a multiple of 4(namely 128bits)
    iterator_word_len = hash_get_iterator_word_len(alg);

    // test1  message: 0x616263, 3 bytes.
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

    // the two styles are equivalent
    ret = hash_dma(alg, msg, 3, digest, hash_call_manage);
    if (HASH_SUCCESS != ret || memcmp_(std_digest1, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 1 failure, ret=%u \r\n", name[alg], ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
        print_buf_U8(std_digest1, digest_byte_len, "std digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 1 success ", name[alg]); // fflush(stdout);
    }

    // test2  message: 0x000102..., 500 bytes.
    msg_len = 500;
    for (i = 0; i < msg_len; i++)
    {
        message[i] = i;
    }

    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, msg_len / 4);

    // test 2-1
    ret = hash_dma(alg, msg, msg_len, digest, hash_call_manage);
    if (HASH_SUCCESS != ret || memcmp_(std_digest2, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 2-1 failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
        print_buf_U8(std_digest2, digest_byte_len, "std digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 2-1 success ", name[alg]); // fflush(stdout);
    }

    // test 2-2
    uint32_clear(digest, 64 / 4);
    ret = hash_dma_init(ctx, alg, hash_call_manage);
    for (i = 0; i < msg_len / block_byte_len; i++)
    {
        ret |= hash_dma_update_blocks(ctx, msg + i * block_word_len, block_byte_len);
    }
    ret |= hash_dma_final(ctx, msg + i * block_word_len, msg_len - i * block_byte_len, digest);
    if (HASH_SUCCESS != ret || memcmp_(std_digest2, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 2-2 failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
        print_buf_U8(std_digest2, digest_byte_len, "std digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 2-2 success ", name[alg]); // fflush(stdout);
    }

    // test 2-3
    uint32_clear(digest, 64 / 4);
    // step 1. init, input one block and stop, get iterator and backup it.
    ret = hash_dma_init(ctx, alg, hash_call_manage);
    ret |= hash_dma_update_blocks(ctx, msg, 1 * block_byte_len);
    if (HASH_SUCCESS != ret)
    {
        printf("\r\n %s DMA test 2-3 init failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        return 1;
    }
#ifdef CONFIG_HASH_SUPPORT_MUL_THREAD
    memcpy_((unsigned char *)iterator, (unsigned char *)ctx->iterator, iterator_word_len << 2);
#else
    hash_get_iterator((unsigned char *)iterator, iterator_word_len);
#endif
    // step 2. release resource(clear ctx) and do some other things
    memset_((unsigned char *)ctx, 0, sizeof(hash_dma_ctx_t));
    //...
    // step 3. continue till end
    ret = hash_dma_init_with_iv_and_updated_length(ctx, alg, iterator, 0, block_byte_len, hash_call_manage);
    ret |= hash_dma_update_blocks(ctx, msg + block_word_len, 1 * block_byte_len);
    ret |= hash_dma_final(ctx, msg + 2 * block_word_len, msg_len - 2 * block_byte_len, digest);
    if (HASH_SUCCESS != ret || memcmp_(std_digest2, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 2-3 failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
        print_buf_U8(std_digest1, digest_byte_len, "std digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 2-3 success ", name[alg]); // fflush(stdout);
    }

    // test 2-4...
    printf("\r\n");
    for (i = 0; i < 100; i++)
    {
        total = 0;
        uint32_clear(digest, 64 / 4);

        ret = hash_dma_init(ctx, alg, hash_call_manage);

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
                        ret |= hash_dma_final(ctx, msg + total / 4, j, digest);
                    }
                    else
                    {
                        ret |= hash_dma_update_blocks(ctx, msg + total / 4, j);
                    }
                }
                else
                {
                    j = msg_len - total;
                    ret |= hash_dma_final(ctx, msg + total / 4, j, digest);
                }
            }
            else
            {
                j = msg_len - total;
                ret |= hash_dma_final(ctx, msg + total / 4, j, digest);
            }
            total += j;
        }
        if (HASH_SUCCESS != ret || memcmp_(std_digest2, (unsigned char *)digest, digest_byte_len))
        {
            printf("\r\n %s DMA test 2-%u failure, ret=%u \r\n", name[alg], i + 4, ret); // fflush(stdout);
            print_buf_U8(message, msg_len, "message");
            print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
            print_buf_U8(std_digest1, digest_byte_len, "std digest");
            return 1;
        }
        else
        {
            printf(" 2-%u", i + 4); // fflush(stdout);
        }
    }

#ifdef SUPPORT_HASH_DMA_NODE
    // test 2-final
    uint32_clear(digest, 64 / 4);
    hash_dma_node[0].msg_addr = msg;
    hash_dma_node[0].msg_len = block_byte_len;
    hash_dma_node[1].msg_addr = hash_dma_node[0].msg_addr + hash_dma_node[0].msg_len / 4;
    hash_dma_node[1].msg_len = block_byte_len;
    hash_dma_node[2].msg_addr = hash_dma_node[1].msg_addr + hash_dma_node[1].msg_len / 4;
    hash_dma_node[2].msg_len = msg_len - 2 * block_byte_len;
    ret = hash_dma_node_steps(alg, hash_dma_node, 3, digest, hash_call_manage);
    if (HASH_SUCCESS != ret || memcmp_(std_digest2, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 2-final(hash dma node style) failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        print_buf_U8(message, msg_len, "message");
        print_buf_U8((unsigned char *)digest, output_word_len << 2, "digest");
        print_buf_U8(std_digest1, digest_byte_len, "std digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 2-final(hash dma node style)", name[alg]); // fflush(stdout);
    }
#endif

    // test3  message: 0x000102..., 500 bytes.
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

        ret |= hash_dma(alg, msg, i, digest, hash_call_manage);

        uint32_copy((unsigned int *)message, digest, digest_byte_len / 4);
    }

    if (HASH_SUCCESS != ret || memcmp_(std_digest3, (unsigned char *)digest, digest_byte_len))
    {
        printf("\r\n %s DMA test 3 failure, ret=%u \r\n", name[alg], ret); // fflush(stdout);
        print_buf_U8(message, 500, "message");
        print_buf_U8((unsigned char *)digest, digest_byte_len, "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s DMA test 3 success \r\n", name[alg]); // fflush(stdout);
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_MD5
/**
 * @brief           Perform MD5 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int md5_test(void)
{
    unsigned char std_digest1[32] = {
        0x90,
        0x01,
        0x50,
        0x98,
        0x3C,
        0xD2,
        0x4F,
        0xB0,
        0xD6,
        0x96,
        0x3F,
        0x7D,
        0x28,
        0xE1,
        0x7F,
        0x72,
    };
    unsigned char std_digest2[32] = {
        0xDE,
        0xC0,
        0x59,
        0x23,
        0x45,
        0xAC,
        0x3D,
        0xFA,
        0x17,
        0x2C,
        0x9E,
        0xC4,
        0x76,
        0xA2,
        0x4C,
        0x75,
    };
    unsigned char std_digest3[32] = {
        0x1B,
        0x6B,
        0xF6,
        0x9F,
        0x9A,
        0x78,
        0x01,
        0x84,
        0xD8,
        0xF7,
        0x47,
        0x8C,
        0x27,
        0x96,
        0x22,
        0x77,
    };
    unsigned int ret;

    ret = hash_test(HASH_MD5, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_MD5, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SM3

/**
 * @brief           Perform SM3 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sm3_test(void)
{
    unsigned char std_digest1[32] = {0x66, 0xC7, 0xF0, 0xF4, 0x62, 0xEE, 0xED, 0xD9, 0xD1, 0xF2, 0xD4, 0x6B, 0xDC, 0x10, 0xE4, 0xE2,
                                     0x41, 0x67, 0xC4, 0x87, 0x5C, 0xF2, 0xF7, 0xA2, 0x29, 0x7D, 0xA0, 0x2B, 0x8F, 0x4B, 0xA8, 0xE0};
    unsigned char std_digest2[32] = {
        0xda,
        0xd1,
        0x46,
        0x5a,
        0x3f,
        0x51,
        0x12,
        0x8d,
        0x86,
        0xf8,
        0xda,
        0xaa,
        0x4f,
        0x4e,
        0x7e,
        0x1b,
        0x3d,
        0x2e,
        0x70,
        0x4c,
        0x29,
        0x45,
        0x12,
        0x47,
        0xaf,
        0xd4,
        0x9d,
        0x7d,
        0x96,
        0xa5,
        0xac,
        0x31,
    };
    unsigned char std_digest3[32] = {
        0xe8,
        0xb9,
        0x9c,
        0xdf,
        0x8c,
        0x46,
        0xa6,
        0x72,
        0xce,
        0xc9,
        0x9d,
        0x97,
        0x6e,
        0x31,
        0xa1,
        0x5c,
        0x83,
        0x63,
        0x1f,
        0x57,
        0x47,
        0x05,
        0x29,
        0x5f,
        0xd3,
        0x0f,
        0x92,
        0x3a,
        0xe7,
        0xeb,
        0xbd,
        0x5e,
    };
    unsigned int ret;

    ret = hash_test(HASH_SM3, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SM3, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA1
/**
 * @brief           Perform SHA1 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha1_test(void)
{
    unsigned char std_digest1[20] = {
        0xA9,
        0x99,
        0x3E,
        0x36,
        0x47,
        0x06,
        0x81,
        0x6A,
        0xBA,
        0x3E,
        0x25,
        0x71,
        0x78,
        0x50,
        0xC2,
        0x6C,
        0x9C,
        0xD0,
        0xD8,
        0x9D,
    };
    unsigned char std_digest2[20] = {
        0x50,
        0x75,
        0x0F,
        0x6E,
        0xC4,
        0xBD,
        0xAA,
        0x13,
        0x43,
        0x69,
        0x29,
        0x9D,
        0xE5,
        0x3D,
        0x8D,
        0x8B,
        0x87,
        0xD1,
        0xBA,
        0x63,
    };
    unsigned char std_digest3[20] = {
        0x9F,
        0x14,
        0x31,
        0x91,
        0x13,
        0x17,
        0xD7,
        0x4D,
        0x2D,
        0xF1,
        0xBD,
        0xD2,
        0x52,
        0x82,
        0xA4,
        0xD8,
        0x0E,
        0x66,
        0x42,
        0x7F,
    };
    unsigned int ret;

    ret = hash_test(HASH_SHA1, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA1, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA256
/**
 * @brief           Perform SHA256 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha256_test(void)
{
    unsigned char std_digest1[32] = {0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA, 0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23,
                                     0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C, 0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD};
    unsigned char std_digest2[32] = {0x6A, 0x25, 0x9D, 0xA4, 0xDA, 0xCD, 0xFB, 0x0F, 0x51, 0x36, 0x96, 0x49, 0xCB, 0xF8, 0x86, 0x4D,
                                     0x8E, 0x2D, 0x67, 0x54, 0x62, 0xC8, 0x62, 0x5A, 0x70, 0x33, 0x4B, 0xFC, 0x2C, 0x50, 0xD1, 0xAF};
    unsigned char std_digest3[32] = {0xC3, 0xFB, 0x71, 0x00, 0xFE, 0x3F, 0x3F, 0x9F, 0xAF, 0x19, 0xD2, 0x8E, 0xE4, 0x4B, 0x5A, 0x87,
                                     0xCF, 0x6F, 0xB6, 0xD1, 0x55, 0x6C, 0x5A, 0x04, 0x45, 0xE5, 0x84, 0xF6, 0xAE, 0x9D, 0xB8, 0x6A};
    unsigned int ret;

    ret = hash_test(HASH_SHA256, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA256, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA224
/**
 * @brief           Perform SHA224 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha224_test(void)
{
    unsigned char std_digest1[28] = {0x23, 0x09, 0x7D, 0x22, 0x34, 0x05, 0xD8, 0x22, 0x86, 0x42, 0xA4, 0x77, 0xBD, 0xA2,
                                     0x55, 0xB3, 0x2A, 0xAD, 0xBC, 0xE4, 0xBD, 0xA0, 0xB3, 0xF7, 0xE3, 0x6C, 0x9D, 0xA7};
    unsigned char std_digest2[28] = {0xDE, 0xFC, 0x2F, 0x15, 0x71, 0x32, 0x50, 0xE4, 0xEF, 0x6B, 0xCC, 0xEB, 0x4F, 0xAC,
                                     0x74, 0x42, 0xDF, 0x56, 0x51, 0xFC, 0x17, 0xA0, 0xBC, 0x56, 0xA9, 0xEF, 0x67, 0xF2};
    unsigned char std_digest3[28] = {0xFE, 0x56, 0x7D, 0xC1, 0x15, 0xA9, 0xA1, 0x62, 0xA4, 0xB7, 0x92, 0x1A, 0x76, 0x6E,
                                     0x4F, 0x35, 0x67, 0x65, 0x74, 0xE7, 0xCD, 0x00, 0x4E, 0x2E, 0xEA, 0xE2, 0x73, 0x99};
    unsigned int ret;

    ret = hash_test(HASH_SHA224, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA224, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA384
/**
 * @brief           Perform SHA384 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha384_test(void)
{
    unsigned char std_digest1[48] = {0xCB, 0x00, 0x75, 0x3F, 0x45, 0xA3, 0x5E, 0x8B, 0xB5, 0xA0, 0x3D, 0x69, 0x9A, 0xC6, 0x50, 0x07,
                                     0x27, 0x2C, 0x32, 0xAB, 0x0E, 0xDE, 0xD1, 0x63, 0x1A, 0x8B, 0x60, 0x5A, 0x43, 0xFF, 0x5B, 0xED,
                                     0x80, 0x86, 0x07, 0x2B, 0xA1, 0xE7, 0xCC, 0x23, 0x58, 0xBA, 0xEC, 0xA1, 0x34, 0xC8, 0x25, 0xA7};
    unsigned char std_digest2[48] = {0x32, 0x1E, 0x84, 0x33, 0xE8, 0xE1, 0xE4, 0x61, 0xBD, 0xC5, 0xB1, 0x49, 0x58, 0x2F, 0x4A, 0x80,
                                     0xB3, 0xA8, 0x8D, 0x75, 0x10, 0x42, 0x08, 0xA2, 0xC4, 0xF8, 0xA5, 0x35, 0xB4, 0x5D, 0xDB, 0x27,
                                     0x34, 0xEB, 0xAC, 0x7C, 0x89, 0x96, 0xC8, 0x60, 0x4F, 0xF0, 0x3A, 0x5A, 0xEE, 0x3D, 0xA5, 0xCB};
    unsigned char std_digest3[48] = {0xCC, 0x2B, 0x35, 0xE0, 0x00, 0xE8, 0x54, 0x8B, 0x17, 0xAD, 0x89, 0xC1, 0xA9, 0x15, 0xBB, 0x36,
                                     0x5A, 0xE8, 0xBF, 0xFF, 0x89, 0xBA, 0x12, 0xD1, 0x9B, 0x5E, 0x3F, 0xE8, 0x56, 0xC5, 0x1A, 0xAE,
                                     0xC0, 0x45, 0x9B, 0x80, 0x25, 0xD8, 0x99, 0x96, 0xE1, 0x2F, 0x44, 0x8F, 0xD0, 0x2E, 0x46, 0xF9};
    unsigned int ret;

    //    ret = hash_test(HASH_SHA384, std_digest1, std_digest2, std_digest3);
    //    if (ret) {
    //        return 1;
    //    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA384, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512
/**
 * @brief           Perform SHA512 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha512_test(void)
{
    unsigned char std_digest1[64] = {0xDD, 0xAF, 0x35, 0xA1, 0x93, 0x61, 0x7A, 0xBA, 0xCC, 0x41, 0x73, 0x49, 0xAE, 0x20, 0x41, 0x31, 0x12, 0xE6, 0xFA, 0x4E, 0x89, 0xA9,
                                     0x7E, 0xA2, 0x0A, 0x9E, 0xEE, 0xE6, 0x4B, 0x55, 0xD3, 0x9A, 0x21, 0x92, 0x99, 0x2A, 0x27, 0x4F, 0xC1, 0xA8, 0x36, 0xBA, 0x3C, 0x23,
                                     0xA3, 0xFE, 0xEB, 0xBD, 0x45, 0x4D, 0x44, 0x23, 0x64, 0x3C, 0xE8, 0x0E, 0x2A, 0x9A, 0xC9, 0x4F, 0xA5, 0x4C, 0xA4, 0x9F};
    unsigned char std_digest2[64] = {0xF8, 0xD1, 0xC9, 0x17, 0xDA, 0x2E, 0x66, 0xBE, 0x92, 0x02, 0x2D, 0x6A, 0x49, 0xEC, 0xEE, 0x0F, 0x0D, 0x89, 0x7C, 0x6D, 0x97, 0x92,
                                     0x7A, 0xDC, 0x65, 0x4C, 0x73, 0xD7, 0x35, 0xDC, 0xA4, 0x20, 0xDD, 0x80, 0x8B, 0xE0, 0x67, 0x94, 0xF5, 0x14, 0xD5, 0xA8, 0x8F, 0xA2,
                                     0xE2, 0x4C, 0x0C, 0x0F, 0x08, 0x17, 0xC9, 0x5A, 0xD4, 0x48, 0x37, 0x1B, 0x4C, 0xD6, 0xA8, 0xCB, 0x6A, 0xA6, 0x56, 0xB3};
    unsigned char std_digest3[64] = {0xB5, 0xA7, 0xB2, 0x22, 0x2E, 0x91, 0x6B, 0x74, 0xA7, 0xDD, 0x59, 0x3A, 0x07, 0x8A, 0x33, 0xAC, 0xF5, 0x3D, 0xD9, 0x55, 0xF7, 0x66,
                                     0x10, 0x89, 0x80, 0x49, 0xC3, 0xB3, 0x1D, 0x16, 0x50, 0xBB, 0x5D, 0x63, 0x53, 0xC0, 0x35, 0x70, 0xFB, 0x30, 0xBC, 0x1F, 0xBA, 0x0C,
                                     0x02, 0xDF, 0x4E, 0xB9, 0x37, 0x87, 0xED, 0x79, 0x0B, 0x1E, 0x74, 0x8A, 0x3A, 0xA6, 0xA7, 0x15, 0xEC, 0x41, 0x02, 0xFA};
    unsigned int ret;

    ret = hash_test(HASH_SHA512, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA512, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512_224
/**
 * @brief           Perform SHA512_224 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha512_224_test(void)
{
    unsigned char std_digest1[28] = {0x46, 0x34, 0x27, 0x0F, 0x70, 0x7B, 0x6A, 0x54, 0xDA, 0xAE, 0x75, 0x30, 0x46, 0x08,
                                     0x42, 0xE2, 0x0E, 0x37, 0xED, 0x26, 0x5C, 0xEE, 0xE9, 0xA4, 0x3E, 0x89, 0x24, 0xAA};
    unsigned char std_digest2[28] = {0xEB, 0x41, 0x69, 0x3D, 0x78, 0x4B, 0x87, 0x25, 0xC1, 0xFB, 0x06, 0xA6, 0x92, 0x2E,
                                     0x86, 0x9B, 0x1C, 0xF0, 0x34, 0x64, 0x04, 0x8C, 0xCF, 0x72, 0x0F, 0x62, 0x34, 0xFD};
    unsigned char std_digest3[28] = {0x8A, 0x48, 0x1F, 0xBD, 0x48, 0x94, 0xD7, 0x2C, 0x63, 0xA7, 0x3A, 0xF9, 0x5C, 0xB4,
                                     0x4F, 0x34, 0x6E, 0xAF, 0x0E, 0xF0, 0x5E, 0x25, 0x17, 0xBB, 0x47, 0x3A, 0xBE, 0xF4};
    unsigned int ret;

    ret = hash_test(HASH_SHA512_224, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA512_224, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA512_256
/**
 * @brief           Perform SHA512_256 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha512_256_test(void)
{
    unsigned char std_digest1[32] = {0x53, 0x04, 0x8E, 0x26, 0x81, 0x94, 0x1E, 0xF9, 0x9B, 0x2E, 0x29, 0xB7, 0x6B, 0x4C, 0x7D, 0xAB,
                                     0xE4, 0xC2, 0xD0, 0xC6, 0x34, 0xFC, 0x6D, 0x46, 0xE0, 0xE2, 0xF1, 0x31, 0x07, 0xE7, 0xAF, 0x23};
    unsigned char std_digest2[32] = {0x81, 0xDC, 0x4F, 0x56, 0x1A, 0x2A, 0x4C, 0x29, 0x6B, 0xD3, 0xAA, 0x3F, 0x67, 0xC1, 0x73, 0x5F,
                                     0x86, 0xDA, 0xBE, 0xB6, 0x2D, 0xBB, 0xCE, 0xC3, 0x90, 0xBD, 0x58, 0x16, 0xE5, 0x78, 0x10, 0xEA};
    unsigned char std_digest3[32] = {0xFE, 0xB9, 0x98, 0x10, 0xCC, 0xE3, 0xB3, 0x8F, 0x3E, 0x12, 0xC1, 0xF6, 0xA6, 0x5B, 0x5A, 0x1C,
                                     0xE4, 0x9A, 0x5E, 0xBD, 0xD7, 0x35, 0x70, 0x9F, 0x7F, 0x4E, 0xD4, 0x16, 0x34, 0x25, 0x4C, 0x74};
    unsigned int ret;

    ret = hash_test(HASH_SHA512_256, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA512_256, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA3_224
/**
 * @brief           Perform SHA3-224 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha3_224_test(void)
{
    unsigned char std_digest1[28] = {0xE6, 0x42, 0x82, 0x4C, 0x3F, 0x8C, 0xF2, 0x4A, 0xD0, 0x92, 0x34, 0xEE, 0x7D, 0x3C,
                                     0x76, 0x6F, 0xC9, 0xA3, 0xA5, 0x16, 0x8D, 0x0C, 0x94, 0xAD, 0x73, 0xB4, 0x6F, 0xDF};
    unsigned char std_digest2[28] = {0xEB, 0x7D, 0x43, 0xDF, 0xD5, 0x50, 0xEE, 0x5A, 0xFF, 0x61, 0x59, 0xB3, 0xCC, 0xAE,
                                     0xE0, 0x71, 0x5C, 0x9C, 0x36, 0xBB, 0xCE, 0x18, 0x22, 0xAD, 0x7E, 0x26, 0x70, 0x2E};
    unsigned char std_digest3[28] = {0x12, 0xa6, 0x09, 0xd1, 0x1b, 0xee, 0xad, 0x6b, 0xb7, 0xd7, 0xda, 0x31, 0x83, 0x08,
                                     0xad, 0xd4, 0x87, 0x5f, 0x30, 0xa5, 0x87, 0xb0, 0x8e, 0xee, 0x53, 0xb8, 0x9e, 0xdf};
    unsigned int ret;

    ret = hash_test(HASH_SHA3_224, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA3_224, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA3_256
/**
 * @brief           Perform SHA3-256 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha3_256_test(void)
{
    unsigned char std_digest1[32] = {0x3A, 0x98, 0x5D, 0xA7, 0x4F, 0xE2, 0x25, 0xB2, 0x04, 0x5C, 0x17, 0x2D, 0x6B, 0xD3, 0x90, 0xBD,
                                     0x85, 0x5F, 0x08, 0x6E, 0x3E, 0x9D, 0x52, 0x5B, 0x46, 0xBF, 0xE2, 0x45, 0x11, 0x43, 0x15, 0x32};
    unsigned char std_digest2[32] = {0x0F, 0x96, 0x25, 0x9F, 0x82, 0xFB, 0x8C, 0x30, 0xD3, 0xD7, 0x02, 0xE8, 0xA8, 0x9A, 0x47, 0x5D,
                                     0x2E, 0x96, 0x69, 0x0A, 0x5E, 0xE9, 0x89, 0x2A, 0x48, 0x35, 0x18, 0x64, 0xFB, 0x49, 0x2A, 0xA5};
    unsigned char std_digest3[32] = {0x28, 0xcf, 0xc5, 0x5e, 0x9b, 0x31, 0xe5, 0x86, 0xd6, 0x82, 0xb1, 0x5c, 0x90, 0x67, 0xd8, 0x98,
                                     0xfd, 0x50, 0x6c, 0x7f, 0x37, 0x61, 0x00, 0xb1, 0xa0, 0x99, 0x04, 0x11, 0x16, 0x1f, 0x53, 0x53};
    unsigned int ret;

    printf("\r\n -------------- HASH_SHA3_256 -------------- \r\n");

    ret = hash_test(HASH_SHA3_256, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA3_256, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA3_384
/**
 * @brief           Perform SHA3-384 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha3_384_test(void)
{
    unsigned char std_digest1[48] = {0xEC, 0x01, 0x49, 0x82, 0x88, 0x51, 0x6F, 0xC9, 0x26, 0x45, 0x9F, 0x58, 0xE2, 0xC6, 0xAD, 0x8D,
                                     0xF9, 0xB4, 0x73, 0xCB, 0x0F, 0xC0, 0x8C, 0x25, 0x96, 0xDA, 0x7C, 0xF0, 0xE4, 0x9B, 0xE4, 0xB2,
                                     0x98, 0xD8, 0x8C, 0xEA, 0x92, 0x7A, 0xC7, 0xF5, 0x39, 0xF1, 0xED, 0xF2, 0x28, 0x37, 0x6D, 0x25};
    unsigned char std_digest2[48] = {0x88, 0x58, 0x7B, 0x39, 0x6E, 0x42, 0x97, 0xAB, 0x27, 0x90, 0x8F, 0xB4, 0x74, 0x1A, 0x32, 0x59,
                                     0x37, 0x2E, 0x6D, 0xD8, 0xFA, 0x62, 0xB2, 0x29, 0x12, 0xD0, 0xC6, 0x0A, 0xFC, 0x4E, 0xB8, 0x9C,
                                     0xFD, 0x6A, 0x7B, 0xAA, 0x7F, 0x86, 0x90, 0xF6, 0xBE, 0x87, 0x41, 0x40, 0xB1, 0xD5, 0x27, 0x13};
    unsigned char std_digest3[48] = {0xf0, 0xc8, 0x8e, 0x74, 0x20, 0x4d, 0xf2, 0x27, 0x1f, 0xfe, 0x4f, 0xbb, 0x21, 0xbb, 0xdd, 0x7e,
                                     0x29, 0x96, 0xc8, 0xba, 0x4e, 0x46, 0x45, 0x94, 0x1b, 0xea, 0xcb, 0xb6, 0x76, 0x06, 0x2a, 0x93,
                                     0x50, 0xb6, 0x28, 0x57, 0x92, 0x06, 0x7c, 0xfb, 0x05, 0xd0, 0xa3, 0xd9, 0x86, 0x3a, 0x3d, 0xd9};
    unsigned int ret;

    ret = hash_test(HASH_SHA3_384, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA3_384, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

#ifdef SUPPORT_HASH_SHA3_512
/**
 * @brief           Perform SHA3-512 hash algorithm tests
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sha3_512_test(void)
{
    unsigned char std_digest1[64] = {0xB7, 0x51, 0x85, 0x0B, 0x1A, 0x57, 0x16, 0x8A, 0x56, 0x93, 0xCD, 0x92, 0x4B, 0x6B, 0x09, 0x6E, 0x08, 0xF6, 0x21, 0x82, 0x74, 0x44,
                                     0xF7, 0x0D, 0x88, 0x4F, 0x5D, 0x02, 0x40, 0xD2, 0x71, 0x2E, 0x10, 0xE1, 0x16, 0xE9, 0x19, 0x2A, 0xF3, 0xC9, 0x1A, 0x7E, 0xC5, 0x76,
                                     0x47, 0xE3, 0x93, 0x40, 0x57, 0x34, 0x0B, 0x4C, 0xF4, 0x08, 0xD5, 0xA5, 0x65, 0x92, 0xF8, 0x27, 0x4E, 0xEC, 0x53, 0xF0};
    unsigned char std_digest2[64] = {0x5C, 0x37, 0x18, 0x29, 0xF7, 0x74, 0x95, 0x9D, 0x04, 0xAC, 0x4B, 0x4E, 0x49, 0x55, 0x7E, 0x43, 0x55, 0x42, 0x74, 0x07, 0xCA, 0x96,
                                     0x0A, 0x3A, 0xCC, 0x96, 0x43, 0xBB, 0x5B, 0x13, 0xCB, 0x69, 0x2B, 0xBE, 0x28, 0x1F, 0x3F, 0x41, 0x37, 0x78, 0x45, 0x51, 0x09, 0x2B,
                                     0x46, 0x13, 0xE0, 0x16, 0xA4, 0xF1, 0xFF, 0x27, 0x14, 0xF8, 0xF6, 0x7F, 0x97, 0xD1, 0x1E, 0x32, 0x33, 0xA9, 0xB6, 0x62};
    unsigned char std_digest3[64] = {0xed, 0xa3, 0xb5, 0x78, 0xd3, 0x6e, 0x63, 0x10, 0x53, 0x77, 0x02, 0x0b, 0xb4, 0x83, 0x0b, 0xdd, 0x97, 0x4d, 0x65, 0xd9, 0x36, 0xee,
                                     0xc3, 0xe1, 0x6e, 0x78, 0x34, 0x64, 0x44, 0x32, 0x13, 0xee, 0x04, 0x88, 0xf1, 0x94, 0x1d, 0x0b, 0x6b, 0x62, 0x4a, 0x5f, 0x23, 0xc1,
                                     0x5d, 0x7e, 0xba, 0xc2, 0xd2, 0x84, 0x12, 0xa4, 0xe6, 0xa0, 0xd7, 0x58, 0xe0, 0x34, 0x2e, 0x81, 0xaf, 0x13, 0xdb, 0x7b};
    unsigned int ret;

    ret = hash_test(HASH_SHA3_512, std_digest1, std_digest2, std_digest3);
    if (ret)
    {
        return 1;
    }

#ifdef HASH_DMA_FUNCTION
    ret = hash_dma_test(HASH_SHA3_512, std_digest1, std_digest2, std_digest3);
#endif

    return ret;
}
#endif

/**
 * @brief           Perform comprehensive tests for all supported hash algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int hash_all_test(void)
{
    printf("\r\n\r\n =================== HASH test =================== ");
    fflush(stdout);

#ifdef SUPPORT_HASH_SM3
    if (sm3_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_MD5
    if (md5_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA256
    if (sha256_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA384
    if (sha384_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512
    if (sha512_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA1
    if (sha1_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA224
    if (sha224_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_224
    if (sha512_224_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_256
    if (sha512_256_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_224
    if (sha3_224_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_256
    if (sha3_256_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_384
    if (sha3_384_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_512
    if (sha3_512_test())
    {
        return 1;
    }
#endif

    printf("\r\n\r\n HASH test success \r\n\r\n");
    fflush(stdout);

    return 0;
}

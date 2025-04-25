/********************************************************************************************************
 * @file    sample_test_hmac_sha512_256.c
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
#include "lib/include/hash/hmac_sha512_256.h"
#include "lib/include/crypto_common/utility.h"

void hash_call_manage(void);

#ifdef SUPPORT_HASH_SHA512_256
/**
 * @brief           Perform sample tests for HMAC-SHA512-256 algorithm
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int sample_test_hmac_sha512_256(void)
{
    unsigned char msg[80] = {
        0xCB,
        0xAC,
        0x28,
        0x1C,
        0xAC,
        0xD3,
        0x03,
        0x5F,
        0x81,
        0x5A,
        0x0E,
        0x82,
        0xF0,
        0xA5,
        0xEA,
        0x7A,
        0xC5,
        0x3C,
        0x4F,
        0xF7,
        0x0B,
        0xB7,
        0x9F,
        0xA6,
        0x1E,
        0x80,
        0xEA,
        0xF6,
        0xE6,
        0x03,
        0x0F,
        0x7F,
        0xF8,
        0x3E,
        0xF7,
        0x36,
        0x0F,
        0xC4,
        0x10,
        0xB0,
        0x1E,
        0xDC,
        0x20,
        0xD1,
        0xA1,
        0xB2,
        0xBD,
        0xAF,
        0xBE,
        0xC0,
        0x21,
        0xB4,
        0xF3,
        0x68,
        0xE3,
        0x06,
        0x91,
        0x34,
        0xE0,
        0x12,
        0xC2,
        0xB4,
        0x30,
        0x70,
        0x83,
        0xD3,
        0xA9,
        0xBD,
        0xD2,
        0x06,
        0xE2,
        0x4E,
        0x5F,
        0x0D,
        0x86,
        0xE1,
        0x3D,
        0x66,
        0x36,
        0x65,
    };
    unsigned char key[16] = {
        0x92,
        0x8C,
        0x8A,
        0xBE,
        0xCB,
        0xCB,
        0x38,
        0x5B,
        0x8E,
        0xEA,
        0xA0,
        0x05,
        0x9A,
        0xC8,
        0x05,
        0x84,
    };
    unsigned char std_mac[32] = {0xD3, 0x71, 0x1E, 0x06, 0x80, 0x81, 0xF2, 0xC4, 0xA2, 0xB1, 0x1A, 0x35, 0xF7, 0x36, 0xAF, 0xAD,
                                 0x34, 0x40, 0x46, 0xCC, 0x69, 0x93, 0x96, 0x80, 0x4D, 0x4A, 0x4C, 0x4A, 0x0E, 0x0A, 0x2E, 0x34};
    unsigned char mac[32];
    unsigned char msg_byte_len = 80;
    unsigned char key_byte_len = 16;
    unsigned char mac_byte_len = 32; // digest_byte_len
    unsigned char block_byte_len = 128;

    unsigned int ret;

    hmac_sha512_256_ctx_t hmac_sha512_256_ctx[1];
    hmac_ctx_t *hmac_ctx = hmac_sha512_256_ctx;

#ifdef SUPPORT_HASH_NODE
    hash_node_t node[3];
#endif

#ifdef SUPPORT_HASH_DMA_NODE
    hash_dma_node_t dma_node[3];
#endif

#ifdef HASH_DMA_FUNCTION
    unsigned int *msg_buf = (unsigned int *)(HASH_DMA_RAM_BASE);
    unsigned int *mac_buf = msg_buf + 512;
    unsigned int blocks_bytes = msg_byte_len - (msg_byte_len % block_byte_len);
    unsigned int remainder_bytes = msg_byte_len - blocks_bytes;
    hmac_sha512_256_dma_ctx_t hmac_sha512_256_dma_ctx[1];
    hmac_dma_ctx_t *hmac_dma_ctx = hmac_sha512_256_dma_ctx;

    uint32_copy(msg_buf, (unsigned int *)msg, (msg_byte_len + 3) / 4);
#endif

    printf("\r\n\r\n -------------- HMAC-SHA512_256 sample test -------------- ");

    // the following 6 calculations are equivalent

    /**************** test 1 ****************/
    memset_(mac, 0, mac_byte_len);
    ret = hmac_sha512_256_init(hmac_sha512_256_ctx, key, 0, key_byte_len);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_update(hmac_sha512_256_ctx, msg, 4);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_update(hmac_sha512_256_ctx, msg + 4, 44);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_update(hmac_sha512_256_ctx, msg + 48, 32);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_final(hmac_sha512_256_ctx, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 1 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 1 success");
        fflush(stdout);
    }

    /**************** test 2 ****************/
    memset_(mac, 0, mac_byte_len);
    ret = hmac_sha512_256(key, 0, key_byte_len, msg, msg_byte_len, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 2 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 2 success");
        fflush(stdout);
    }

    /**************** test 3 ****************/
#ifdef SUPPORT_HASH_NODE
    memset_(mac, 0, mac_byte_len);

    node[0].msg_addr = msg;
    node[0].msg_len = 4;
    node[1].msg_addr = msg + 4;
    node[1].msg_len = 44;
    node[2].msg_addr = msg + 48;
    node[2].msg_len = 32;
    ret = hmac_sha512_256_node_steps(key, 0, key_byte_len, node, 3, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 3 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 3 success");
        fflush(stdout);
    }
#endif

    /**************** test 4 ****************/
    memset_(mac, 0, mac_byte_len);
    ret = hmac_init(hmac_ctx, HASH_SHA512_256, key, 0, key_byte_len);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_update(hmac_sha512_256_ctx, msg, 4);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_update(hmac_sha512_256_ctx, msg + 4, 44);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_update(hmac_sha512_256_ctx, msg + 48, 32);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_final(hmac_sha512_256_ctx, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 4 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 4 success");
        fflush(stdout);
    }

    /**************** test 5 ****************/
    memset_(mac, 0, mac_byte_len);
    ret = hmac(HASH_SHA512_256, key, 0, key_byte_len, msg, msg_byte_len, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 5 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 5 success");
        fflush(stdout);
    }

    /**************** test 6 ****************/
#ifdef SUPPORT_HASH_NODE
    memset_(mac, 0, mac_byte_len);

    node[0].msg_addr = msg;
    node[0].msg_len = 4;
    node[1].msg_addr = msg + 4;
    node[1].msg_len = 44;
    node[2].msg_addr = msg + 48;
    node[2].msg_len = 32;
    ret = hmac_node_steps(HASH_SHA512_256, key, 0, key_byte_len, node, 3, mac);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, mac, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 sample test 6 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 sample test 6 success");
        fflush(stdout);
    }
#endif

#ifdef HASH_DMA_FUNCTION
    // the following 6 DMA calculations are equivalent

    /**************** dma test 1 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    ret = hmac_sha512_256_dma_init(hmac_sha512_256_dma_ctx, key, 0, key_byte_len, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_dma_update_blocks(hmac_sha512_256_dma_ctx, msg_buf, blocks_bytes);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_sha512_256_dma_final(hmac_sha512_256_dma_ctx, msg_buf + blocks_bytes / 4, remainder_bytes, mac_buf);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 1 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 1 success");
        fflush(stdout);
    }

    /**************** dma test 2 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    ret = hmac_sha512_256_dma(key, 0, key_byte_len, msg_buf, msg_byte_len, mac_buf, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 2 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 2 success");
        fflush(stdout);
    }

    /**************** dma test 3 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    dma_node[0].msg_addr = msg_buf;
    dma_node[0].msg_len = blocks_bytes;
    dma_node[1].msg_addr = dma_node[0].msg_addr + dma_node[0].msg_len / 4;
    dma_node[1].msg_len = remainder_bytes;
    ret = hmac_sha512_256_dma_node_steps(key, 0, key_byte_len, dma_node, 2, mac_buf, hash_call_manage);

    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 3 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 3 success");
        fflush(stdout);
    }

    /**************** dma test 4 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    ret = hmac_dma_init(hmac_dma_ctx, HASH_SHA512_256, key, 0, key_byte_len, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_dma_update_blocks(hmac_dma_ctx, msg_buf, blocks_bytes);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    ret = hmac_dma_final(hmac_dma_ctx, msg_buf + blocks_bytes / 4, remainder_bytes, mac_buf);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 4 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 4 success");
        fflush(stdout);
    }

    /**************** dma test 5 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    ret = hmac_dma(HASH_SHA512_256, key, 0, key_byte_len, msg_buf, msg_byte_len, mac_buf, hash_call_manage);
    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 5 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 5 success");
        fflush(stdout);
    }

    /**************** dma test 6 ****************/
    uint32_clear(mac_buf, mac_byte_len / 4);
    dma_node[0].msg_addr = msg_buf;
    dma_node[0].msg_len = blocks_bytes;
    dma_node[1].msg_addr = dma_node[0].msg_addr + dma_node[0].msg_len / 4;
    dma_node[1].msg_len = remainder_bytes;
    ret = hmac_dma_node_steps(HASH_SHA512_256, key, 0, key_byte_len, dma_node, 2, mac_buf, hash_call_manage);

    if (HASH_SUCCESS != ret)
    {
        return 1;
    }

    if (memcmp_(std_mac, (unsigned char *)mac_buf, mac_byte_len))
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 6 error");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("\r\n HMAC-SHA512_256 dma sample test 6 success");
        fflush(stdout);
    }

#endif

    return 0;
}

#endif

/********************************************************************************************************
 * @file    sample_test_sha384.c
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
#include "lib/include/hash/sha384.h"
#include "lib/include/crypto_common/utility.h"


void hash_call_manage(void);


#ifdef SUPPORT_HASH_SHA384

unsigned int sample_test_sha384(void)
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
    unsigned char std_digest[48] = {
        0x4D,
        0xFF,
        0x72,
        0xC8,
        0xDB,
        0x4B,
        0xAA,
        0x31,
        0x05,
        0x15,
        0x8B,
        0xB3,
        0x6E,
        0x60,
        0x13,
        0x3F,
        0x8A,
        0xEC,
        0xD2,
        0x6F,
        0x16,
        0xD9,
        0x8E,
        0x5C,
        0x23,
        0xC3,
        0x58,
        0x98,
        0x94,
        0x2D,
        0xCB,
        0x53,
        0x09,
        0x7E,
        0xA2,
        0x76,
        0xC7,
        0xE4,
        0xD6,
        0x87,
        0xBF,
        0x4A,
        0x47,
        0xA7,
        0x5A,
        0x02,
        0x5B,
        0x6D};
    unsigned char digest[48];
    unsigned char msg_byte_len    = 80;
    unsigned char digest_byte_len = 48;
    unsigned char block_byte_len  = 128;

    unsigned int ret;

    SHA384_CTX sha384_ctx[1];
    HASH_CTX  *hash_ctx = sha384_ctx;

    #ifdef SUPPORT_HASH_NODE
    HASH_NODE node[3];
    #endif

    #ifdef SUPPORT_HASH_DMA_NODE
    HASH_DMA_NODE dma_node[3];
    #endif

    #ifdef HASH_DMA_FUNCTION
    unsigned int  *msg_buf         = (unsigned int *)(DMA_RAM_BASE);
    unsigned int  *digest_buf      = msg_buf + 512;
    unsigned int   blocks_bytes    = msg_byte_len - (msg_byte_len % block_byte_len);
    unsigned int   remainder_bytes = msg_byte_len - blocks_bytes;
    SHA384_DMA_CTX sha384_dma_ctx[1];
    HASH_DMA_CTX  *hash_dma_ctx = sha384_dma_ctx;
        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    unsigned int addr_h_0 = 0;
        #endif

    uint32_copy(msg_buf, (unsigned int *)msg, (msg_byte_len + 3) / 4);
    #endif

    printf("\r\n\r\n -------------- SHA384 sample test -------------- ");

    //the following 6 calculations are equivalent

    /**************** test 1 ****************/
    memset_(digest, 0, digest_byte_len);
    ret = sha384_init(sha384_ctx);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = sha384_update(sha384_ctx, msg, 4);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = sha384_update(sha384_ctx, msg + 4, 44);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = sha384_update(sha384_ctx, msg + 48, 32);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = sha384_final(sha384_ctx, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 1 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 1 success"); //fflush(stdout);
    }

    /**************** test 2 ****************/
    memset_(digest, 0, digest_byte_len);
    ret = sha384(msg, msg_byte_len, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 2 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 2 success"); //fflush(stdout);
    }

    /**************** test 3 ****************/
    #ifdef SUPPORT_HASH_NODE
    memset_(digest, 0, digest_byte_len);

    node[0].msg_addr  = msg;
    node[0].msg_bytes = 4;
    node[1].msg_addr  = msg + 4;
    node[1].msg_bytes = 44;
    node[2].msg_addr  = msg + 48;
    node[2].msg_bytes = 32;
    ret               = sha384_node_steps(node, 3, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 3 error");
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 3 success");
        fflush(stdout);
    }
    #endif

    /**************** test 4 ****************/
    memset_(digest, 0, digest_byte_len);
    ret = hash_init(hash_ctx, HASH_SHA384);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = hash_update(hash_ctx, msg, 4);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = hash_update(hash_ctx, msg + 4, 44);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = hash_update(hash_ctx, msg + 48, 32);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    ret = hash_final(hash_ctx, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 3 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 3 success"); //fflush(stdout);
    }

    /**************** test 5 ****************/
    memset_(digest, 0, digest_byte_len);
    ret = hash(HASH_SHA384, msg, msg_byte_len, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 5 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 5 success"); //fflush(stdout);
    }

    /**************** test 6 ****************/
    #ifdef SUPPORT_HASH_NODE
    memset_(digest, 0, digest_byte_len);

    node[0].msg_addr  = msg;
    node[0].msg_bytes = 4;
    node[1].msg_addr  = msg + 4;
    node[1].msg_bytes = 44;
    node[2].msg_addr  = msg + 48;
    node[2].msg_bytes = 32;
    ret               = hash_node_steps(HASH_SHA384, node, 3, digest);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (memcmp_(std_digest, digest, digest_byte_len)) {
        printf("\r\n SHA384 sample test 6 error");
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 sample test 6 success");
        fflush(stdout);
    }
    #endif


    #ifdef HASH_DMA_FUNCTION
    //the following 6 DMA calculations are equivalent

    /**************** dma test 1 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
    ret = sha384_dma_init(sha384_dma_ctx, hash_call_manage);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = sha384_dma_update_blocks(sha384_dma_ctx, addr_h_0, (unsigned int)msg_buf, blocks_bytes);
        #else
    ret = sha384_dma_update_blocks(sha384_dma_ctx, msg_buf, blocks_bytes);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = sha384_dma_final(sha384_dma_ctx, addr_h_0, ((unsigned int)msg_buf) + blocks_bytes, remainder_bytes, addr_h_0, (unsigned int)digest_buf);
        #else
    ret = sha384_dma_final(sha384_dma_ctx, msg_buf + blocks_bytes / 4, remainder_bytes, digest_buf);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 1 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 1 success"); //fflush(stdout);
    }

    /**************** dma test 2 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = sha384_dma(addr_h_0, (unsigned int)msg_buf, msg_byte_len, addr_h_0, (unsigned int)digest_buf, hash_call_manage);
        #else
    ret = sha384_dma(msg_buf, msg_byte_len, digest_buf, hash_call_manage);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 2 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 2 success"); //fflush(stdout);
    }

    /**************** dma test 3 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    dma_node[0].msg_addr_h = addr_h_0;
    dma_node[0].msg_addr_l = (unsigned int)msg_buf;
    dma_node[0].msg_bytes  = blocks_bytes;
    dma_node[1].msg_addr_h = addr_h_0;
    dma_node[1].msg_addr_l = dma_node[0].msg_addr_l + dma_node[0].msg_bytes;
    dma_node[1].msg_bytes  = remainder_bytes;
    ret                    = sha384_dma_node_steps(dma_node, 2, addr_h_0, (unsigned int)digest_buf, hash_call_manage);
        #else
    dma_node[0].msg_addr  = msg_buf;
    dma_node[0].msg_bytes = blocks_bytes;
    dma_node[1].msg_addr  = dma_node[0].msg_addr + dma_node[0].msg_bytes / 4;
    dma_node[1].msg_bytes = remainder_bytes;
    ret                   = sha384_dma_node_steps(dma_node, 2, digest_buf, hash_call_manage);
        #endif

    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 3 error");
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 3 success");
        fflush(stdout);
    }

    /**************** dma test 4 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
    ret = hash_dma_init(hash_dma_ctx, HASH_SHA384, hash_call_manage);
    if (HASH_SUCCESS != ret) {
        return 1;
    }

        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = hash_dma_update_blocks(hash_dma_ctx, addr_h_0, (unsigned int)msg_buf, blocks_bytes);
        #else
    ret = hash_dma_update_blocks(hash_dma_ctx, msg_buf, blocks_bytes);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = hash_dma_final(hash_dma_ctx, addr_h_0, ((unsigned int)msg_buf) + blocks_bytes, remainder_bytes, addr_h_0, (unsigned int)digest_buf);
        #else
    ret = hash_dma_final(hash_dma_ctx, msg_buf + blocks_bytes / 4, remainder_bytes, digest_buf);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 4 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 4 success"); //fflush(stdout);
    }

    /**************** dma test 5 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    ret = hash_dma(HASH_SHA384, addr_h_0, (unsigned int)msg_buf, msg_byte_len, addr_h_0, (unsigned int)digest_buf, hash_call_manage);
        #else
    ret = hash_dma(HASH_SHA384, msg_buf, msg_byte_len, digest_buf, hash_call_manage);
        #endif
    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 5 error");   //fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 5 success"); //fflush(stdout);
    }

    /**************** dma test 6 ****************/
    uint32_clear(digest_buf, digest_byte_len / 4);
        #ifdef CONFIG_HASH_SUPPORT_ADDRESS_HIGH_LOW
    dma_node[0].msg_addr_h = addr_h_0;
    dma_node[0].msg_addr_l = (unsigned int)msg_buf;
    dma_node[0].msg_bytes  = blocks_bytes;
    dma_node[1].msg_addr_h = addr_h_0;
    dma_node[1].msg_addr_l = dma_node[0].msg_addr_l + dma_node[0].msg_bytes;
    dma_node[1].msg_bytes  = remainder_bytes;
    ret                    = hash_dma_node_steps(HASH_SHA384, dma_node, 2, addr_h_0, (unsigned int)digest_buf, hash_call_manage);
        #else
    dma_node[0].msg_addr  = msg_buf;
    dma_node[0].msg_bytes = blocks_bytes;
    dma_node[1].msg_addr  = dma_node[0].msg_addr + dma_node[0].msg_bytes / 4;
    dma_node[1].msg_bytes = remainder_bytes;
    ret                   = hash_dma_node_steps(HASH_SHA384, dma_node, 2, digest_buf, hash_call_manage);
        #endif

    if (HASH_SUCCESS != ret) {
        return 1;
    }

    if (uint32_BigNumCmp((unsigned int *)std_digest, digest_byte_len / 4, digest_buf, digest_byte_len / 4)) {
        printf("\r\n SHA384 dma sample test 6 error");
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n SHA384 dma sample test 6 success");
        fflush(stdout);
    }

    #endif

    return 0;
}


#endif

/********************************************************************************************************
 * @file    hmac_sha512_256.h
 *
 * @brief   This is the header file for TL721X
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
#ifndef HMAC_SHA512_256_H
#define HMAC_SHA512_256_H


#include "hmac.h"


#ifdef __cplusplus
extern "C"
{
#endif


#ifdef SUPPORT_HASH_SHA512_256


    typedef HMAC_CTX HMAC_SHA512_256_CTX;

    #ifdef HASH_DMA_FUNCTION
    typedef HMAC_DMA_CTX HMAC_SHA512_256_DMA_CTX;
    #endif


    //APIs
    /**
 * @brief       init hmac-sha512_256
 * @param[in]   ctx                 - HMAC_SHA512_256_CTX context pointer.
 * @param[in]   key                 - key.
 * @param[in]   sp_key_idx          - index of secure port key.
 * @param[in]   key_bytes           - byte length of key, it could be 0.
 * @return      0:success     other:error
 */
    unsigned int hmac_sha512_256_init(HMAC_SHA512_256_CTX *ctx, unsigned char *key, unsigned short sp_key_idx, unsigned int key_bytes);

    /**
 * @brief       hmac-sha512_256 update message
 * @param[in]   ctx                 - HMAC_SHA512_256_CTX context pointer.
 * @param[in]   msg                 - message.
 * @param[in]   msg_bytes           - byte length of the input message.
 * @return      0:success     other:error
 * @note
  @verbatim
      -# 1. please make sure the three parameters are valid, and ctx is initialized.
  @endverbatim
 */
    unsigned int hmac_sha512_256_update(HMAC_SHA512_256_CTX *ctx, const unsigned char *msg, unsigned int msg_bytes);

    /**
 * @brief       message update done, get the hmac
 * @param[in]   ctx                 - HMAC_CTX context pointer.
 * @param[out]  mac                 - hmac.
 * @return      0:success     other:error
 * @note
  @verbatim
      -# 1. please make sure the ctx is valid and initialized.
      -# 2. please make sure the mac buffer is sufficient.
  @endverbatim
 */
    unsigned int hmac_sha512_256_final(HMAC_SHA512_256_CTX *ctx, unsigned char *mac);

    /**
 * @brief       input key and whole message, get the hmac
 * @param[in]   key                 - key.
 * @param[in]   sp_key_idx          - index of secure port key.
 * @param[in]   key_bytes           - byte length of the key.
 * @param[in]   msg                 - message.
 * @param[in]   msg_bytes           - byte length of the input message.
 * @param[out]  mac                 - hmac.
 * @return      0:success     other:error
 * @note
  @verbatim
      -# 1. please make sure the mac buffer is sufficient.s
  @endverbatim
 */
    unsigned int hmac_sha512_256(unsigned char *key, unsigned short sp_key_idx, unsigned int key_bytes, unsigned char *msg, unsigned int msg_bytes, unsigned char *mac);


    #ifdef HASH_DMA_FUNCTION
    /**
 * @brief       init dma hmac-sha512_256
 * @param[in]   ctx                 - HMAC_SHA512_256_CTX context pointer.
 * @param[in]   key                 - key.
 * @param[in]   sp_key_idx          - index of secure port key.
 * @param[in]   key_bytes           - byte length of key, it could be 0.
 * @param[in]   callback            - callback function pointer.
 * @return      0:success     other:error
 */
    unsigned int hmac_sha512_256_dma_init(HMAC_SHA512_256_DMA_CTX *ctx, const unsigned char *key, unsigned short sp_key_idx, unsigned int key_bytes, HASH_CALLBACK callback);

    /**
 * @brief       dma hmac-sha512_256 update message
 * @param[in]   ctx                 - HMAC_SHA512_256_CTX context pointer.
 * @param[in]   msg                 - key.
 * @param[in]   msg_words          - index of secure port key.
 * @return      0:success     other:error
 * @note
  @verbatim
      -# 1. please make sure the four parameters are valid, and ctx is initialized.
  @endverbatim
 */
    unsigned int hmac_sha512_256_dma_update_blocks(HMAC_SHA512_256_DMA_CTX *ctx, unsigned int *msg, unsigned int msg_words);

    /**
 * @brief       dma hmac-sha512_256 message update done, get the hmac
 * @param[in]   ctx                 - HMAC_SHA512_256_DMA_CTX context pointer.
 * @param[in]   remainder_msg       - message.
 * @param[in]   remainder_bytes     - byte length of the last message, must be in [0, BLOCK_BYTE_LEN-1],
 *                                    here BLOCK_BYTE_LEN is block byte length of SHA512_256(128).
 * @param[out]  mac                 - hmac.
 * @return      0:success     other:error
 * @note
  @verbatim
      -# 1. please make sure the three parameters are valid, and ctx is initialized.
  @endverbatim
 */
    unsigned int hmac_sha512_256_dma_final(HMAC_SHA512_256_DMA_CTX *ctx, unsigned int *remainder_msg, unsigned int remainder_bytes, unsigned int *mac);
    /**
 * @brief       dma hmac-sha512_256 message update done, get the hmac
 * @param[in]   key                 - key.
 * @param[in]   sp_key_idx       - index of secure port key.
 * @param[in]   key_bytes        - key byte length.
 * @param[in]   msg              - message.
 * @param[in]   msg_bytes        - byte length of the input message.
 * @param[out]  mac              - hmac.
 * @param[in]   callback         - callback function pointer.
 * @return      0:success     other:error
 */
    unsigned int hmac_sha512_256_dma(unsigned char *key, unsigned short sp_key_idx, unsigned int key_bytes, unsigned int *msg, unsigned int msg_bytes, unsigned int *mac, HASH_CALLBACK callback);
    #endif


#endif


#ifdef __cplusplus
}
#endif


#endif

/********************************************************************************************************
 * @file    hash_kdf.h
 *
 * @brief   This is the header file for tl751x
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
#ifndef HASH_KDF_H
#define HASH_KDF_H

#include "hmac.h"

#ifdef __cplusplus
extern "C"
{
#endif


    //APIs

#ifdef SUPPORT_PBKDF2
    /**
 * @brief       dma md5 digest calculate
 * @param[out]  ctx_bak            - hmac ctx.
 * @param[in]   ctx                - hmac ctx to be backup.
 * @return      0:success     other:error
 */
    void pbkdf2_hmac_backup(HMAC_CTX *ctx_bak, HMAC_CTX *ctx);

    void pbkdf2_hmac_recover(HMAC_CTX *ctx, HMAC_CTX *ctx_bak);
    /**
 * @brief       pbkdf2 function(using hmac as PRF)
 * @param[in]   hash_alg         - specific hash algorithm.
 * @param[in]   pwd              - password, as the key of hmac.
 * @param[in]   sp_key_idx       - index of secure port key(password).
 * @param[in]   pwd_bytes        - byte length of password, it could be 0.
 * @param[in]   salt             - salt.
 * @param[in]   salt_bytes       - byte length of salt, it could be 0.
 * @param[in]   iter             - iteration times.
 * @param[out]  out              - derived key.
 * @param[in]   out_bytes        - byte length of derived key.
 * @return      0:success     other:error
 */
    unsigned int pbkdf2_hmac(HASH_ALG hash_alg, unsigned char *pwd, unsigned short sp_key_idx, unsigned int pwd_bytes, unsigned char *salt, unsigned int salt_bytes, unsigned int iter, unsigned char *out, unsigned int out_bytes);
#endif


#ifdef SUPPORT_ANSI_X9_63_KDF
    #ifdef SUPPORT_HASH_NODE
    unsigned int ansi_x9_63_kdf_node_with_xor_in(HASH_ALG hash_alg, HASH_NODE *node, unsigned int node_num, unsigned char *counter, unsigned char *in, unsigned char *out, unsigned int out_bytes, unsigned int check_whether_zero);

    unsigned int ansi_x9_63_kdf_internal(HASH_ALG hash_alg, HASH_NODE *hash_node, unsigned int node_num, unsigned char *counter, unsigned char *key, unsigned int key_bytes);

    unsigned int ansi_x9_63_kdf_node(HASH_ALG hash_alg, HASH_NODE *hash_node, unsigned int node_num, unsigned char *counter, unsigned char *k1, unsigned int k1_bytes, unsigned char *k2, unsigned int k2_bytes);

    unsigned int ansi_x9_63_kdf(HASH_ALG hash_alg, unsigned char *Z, unsigned int Z_bytes, unsigned char *shared_info, unsigned int shared_info_bytes, unsigned char *k1, unsigned int k1_bytes, unsigned char *k2, unsigned int k2_bytes);
    #endif
#endif


#ifdef __cplusplus
}
#endif


#endif

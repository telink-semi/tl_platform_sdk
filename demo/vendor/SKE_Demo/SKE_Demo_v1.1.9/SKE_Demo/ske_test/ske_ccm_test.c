/********************************************************************************************************
 * @file    ske_ccm_test.c
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
#include "app_test.h"


//#define CCM_SPEED_TEST_BY_TIMER

#ifdef CCM_SPEED_TEST_BY_TIMER
extern unsigned int startP();
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif


static unsigned int speed_get_round_by_alg(SKE_ALG alg)
{
    unsigned int round;

    switch (alg) {
#ifdef SUPPORT_SKE_TDES_128
    case SKE_ALG_TDES_128:
#endif

#ifdef SUPPORT_SKE_TDES_192
    case SKE_ALG_TDES_192:
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
    case SKE_ALG_TDES_EEE_128:
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
    case SKE_ALG_TDES_EEE_192:
#endif

#if (defined(SUPPORT_SKE_TDES_128) || defined(SUPPORT_SKE_TDES_192) || defined(SUPPORT_SKE_TDES_EEE_128) || defined(SUPPORT_SKE_TDES_EEE_192))
        round = 20; //since haredware does not support 3DES.
        break;
#endif

    default: //hardware supports other ske alg
        round = 100;
    }

    return round;
}

static void get_rand_(unsigned char *rand, unsigned int bytes)
{
#if 0
    memset_(rand, 0x43, bytes);
#else
    get_rand(rand, bytes);
#endif
}

//get random value in [1,max_number-1]
static unsigned int ske_get_rand_number(unsigned int max_number)
{
    unsigned int i;

    get_rand_((unsigned char *)&i, 4);

    i = i % max_number;
    if (0 == i) {
        i = 1;
    }

    return i;
}

//CCM mode is only available for AES and SM4(block length is 128bits)

#ifdef SUPPORT_SKE_MODE_CCM

    #ifdef SKE_LP_DMA_FUNCTION
//callback function
static void ske_call_manage(void)
{
    ;
}
    #endif

unsigned int ske_ccm_test(SKE_ALG alg, unsigned char wordAlign, unsigned char *std_plain, unsigned int byteLen, unsigned char *key, unsigned short sp_key_idx, unsigned char *nonce, unsigned char M, unsigned char L, unsigned char *aad, unsigned char aadByteLen, unsigned char *std_cipher, unsigned char *std_mac)
{
    unsigned char  key_buf[32 + 4];
    unsigned char  nonce_buf[64 + 4];
    unsigned char  aad_buf[64 + 4];
    unsigned char  std_plain_buf[256 + 4];
    unsigned char  std_cipher_buf[256 + 4];
    unsigned char  std_mac_buf[16 + 4];
    unsigned char  cipher_buf[256 + 4];
    unsigned char  replain_buf[256 + 4];
    unsigned char  mac_buf[16 + 4];
    unsigned char *cipher_, *replain_, *mac_, *std_plain_, *std_cipher_, *std_mac_, *key_, *nonce_, *aad_;
    unsigned int   i, j;
    unsigned int   block_byteLen, key_byteLen;
    unsigned int   ret;

    char *name[] = {"", "", "", "", "", "AES_128", "AES_192", "AES_256", "SM4"};

    SKE_CCM_CTX ctx[1];

    key_byteLen   = ske_lp_get_key_byte_len(alg);
    block_byteLen = ske_lp_get_block_byte_len(alg); //16;

    printf("\r\n %s CCM test(M=%u bytes(mac bytes),L=%u bytes(nonce bytes is %u),AAD=%u bytes,P/C=%u bytes)",
           name[alg],
           M,
           L,
           15u - L,
           aadByteLen,
           byteLen);

    if (wordAlign) {
        cipher_     = cipher_buf;
        replain_    = replain_buf;
        mac_        = mac_buf;
        std_plain_  = std_plain_buf;
        std_cipher_ = std_cipher_buf;
        std_mac_    = std_mac_buf;
        if (key) {
            key_ = key_buf;
        } else {
            key_ = NULL;
        }
        nonce_ = nonce_buf;
        aad_   = aad_buf;
    } else {
        cipher_     = cipher_buf + 1;
        replain_    = replain_buf + 1;
        mac_        = mac_buf + 1;
        std_plain_  = std_plain_buf + 1;
        std_cipher_ = std_cipher_buf + 1;
        std_mac_    = std_mac_buf + 1;
        if (key) {
            key_ = key_buf + 1;
        } else {
            key_ = NULL;
        }
        nonce_ = nonce_buf + 1;
        aad_   = aad_buf + 1;
    }

    memcpy_(std_plain_, std_plain, byteLen);
    memcpy_(std_cipher_, std_cipher, byteLen);
    memcpy_(std_mac_, std_mac, M);
    if (key) {
        memcpy_(key_, key, key_byteLen);
    }
    memcpy_(nonce_, nonce, 15 - L);
    memcpy_(aad_, aad, aadByteLen);

    /**************** test 1: one-time style ******************/
    #if 1
    //ENCRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 0 error, ret=%u", ret);
        return 1;
    }

    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 0 error");
        return 1;
    }

    ret = ske_lp_ccm_update_blocks(ctx, std_plain_, cipher_, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm encrypt 0 error, ret=%u", ret);
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(cipher_, byteLen, "cipher");
        return 1;
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm final 0 error");
        return 1;
    }

    //DECRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 1 error, ret=%u", ret);
        return 1;
    }

    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 1 error");
        return 1;
    }

    ret = ske_lp_ccm_update_blocks(ctx, cipher_, replain_, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm decrypt 1 error, ret=%u", ret);
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(replain_, byteLen, "replain");
        return 1;
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 1 error");
        return 1;
    }

    #else

    //ENCRYPT
    ret = ske_lp_ccm_crypto(alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, nonce_, M, L, aad_, aadByteLen, std_plain_, cipher_, byteLen, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n encrypt 1 error, ret=%u", ret);
        return 1;
    }

    //DECRYPT
    ret = ske_lp_ccm_crypto(alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, nonce_, M, L, aad_, aadByteLen, cipher_, replain_, byteLen, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n decrypt 1 error, ret=%u", ret);
        return 1;
    }
    #endif

    if (memcmp_(mac_, std_mac_, M) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n one time input test failure!!");
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(std_mac_, M, "std_mac");
        print_buf_U8(std_cipher_, byteLen, "std_cipher");
        print_buf_U8(key_, key_byteLen, "key");
        print_buf_U8(nonce_, 15 - L, "nonce");
        print_buf_U8(aad_, aadByteLen, "aad");
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(mac_, M, "mac");
        print_buf_U8(replain_, byteLen, "replain");
        return 1;
    } else {
        printf("\r\n one time input test success!!");
    } //fflush(stdout);


    /**************** test 2: multiple style(one block every time) ******************/
    memset_(cipher_, 0, byteLen);
    memset_(replain_, 0, byteLen);
    memset_(mac_, 0, 16);

    //ENCRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 2 error");
        return 1;
    }

    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 2 error");
        return 1;
    }

    for (i = 0; i < byteLen; i += block_byteLen) {
        ret = ske_lp_ccm_update_blocks(ctx, std_plain_ + i, cipher_ + i, GET_MIN_LEN(block_byteLen, byteLen - i));
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm encrypt 2 error");
            return 1;
        }
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm final 2 error");
        return 1;
    }

    //DECRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 3 error, ret=%u", ret);
        return 1;
    }

    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 3 error");
        return 1;
    }

    for (i = 0; i < byteLen; i += block_byteLen) {
        ret = ske_lp_ccm_update_blocks(ctx, std_cipher_ + i, replain_ + i, GET_MIN_LEN(block_byteLen, byteLen - i));
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm decrypt 3 error");
            return 1;
        }
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 3 error");
        return 1;
    }

    if (memcmp_(mac_, std_mac_, M) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n multiple input test failure(one block every time)!!");
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(std_mac_, M, "std_mac");
        print_buf_U8(std_cipher_, byteLen, "std_cipher");
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(mac_, M, "mac");
        print_buf_U8(replain_, byteLen, "replain");
        return 1;
    } else {
        printf("\r\n multiple input test success(one block every time)!!");
    }


    /**************** test 3: multiple style(random length every time) ******************/
    memset_(cipher_, 0, byteLen);
    memset_(replain_, 0, byteLen);
    memset_(mac_, 0, 16);

    //ENCRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 5 error");
        return 1;
    }

    //aad
    #ifdef SKE_LP_CCM_CPU_UPDATE_AAD_BY_STEP
    i = 0;
    while (i < aadByteLen) {
        j = ske_get_rand_number(aadByteLen);
        j = GET_MIN_LEN(j, aadByteLen - i);

        ret = ske_lp_ccm_update_aad(ctx, aad_ + i, j);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm aad 5 error");
            return 1;
        }
        i += j;
    }
    #else
    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 5 error");
        return 1;
    }
    #endif

    //plaintext
    i = 0;
    while (i < byteLen) {
        j = ske_get_rand_number(byteLen / block_byteLen);
        j = j * block_byteLen;
        j = GET_MIN_LEN(j, byteLen - i);

        ret = ske_lp_ccm_update_blocks(ctx, std_plain_ + i, cipher_ + i, j);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm encrypt 5 error");
            return 1;
        }
        i += j;
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm final 5 error");
        return 1;
    }

    //DECRYPT
    ret = ske_lp_ccm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, nonce_, M, L, aadByteLen, byteLen);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm init 6 error");
        return 1;
    }

    //aad
    #ifdef SKE_LP_CCM_CPU_UPDATE_AAD_BY_STEP
    i = 0;
    while (i < aadByteLen) {
        j = ske_get_rand_number(aadByteLen);
        j = GET_MIN_LEN(j, aadByteLen - i);

        ret = ske_lp_ccm_update_aad(ctx, aad_ + i, j);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm aad 6 error");
            return 1;
        }
        i += j;
    }
    #else
    ret = ske_lp_ccm_aad(ctx, aad_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm aad 6 error");
        return 1;
    }
    #endif

    //ciphertext
    i = 0;
    while (i < byteLen) {
        j = ske_get_rand_number(byteLen / block_byteLen);
        j = j * block_byteLen;
        j = GET_MIN_LEN(j, byteLen - i);

        ret = ske_lp_ccm_update_blocks(ctx, cipher_ + i, replain_ + i, j);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm encrypt 6 error");
            return 1;
        }
        i += j;
    }

    ret = ske_lp_ccm_final(ctx, mac_);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske ccm final 6 error");
        return 1;
    }

    if (memcmp_(mac_, std_mac_, M) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n multiple input test failure(random blocks every time)!!");
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(std_mac_, M, "std_mac");
        print_buf_U8(std_cipher_, byteLen, "std_cipher");
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(mac_, M, "mac");
        print_buf_U8(replain_, byteLen, "replain");
        return 1;
    } else {
        printf("\r\n multiple input test success(random blocks every time)!!");
    }
    //*/
    fflush(stdout);

    return 0;
}


    #ifdef SKE_LP_DMA_FUNCTION
unsigned int ske_dma_ccm_test(SKE_ALG alg, unsigned char *std_plain, unsigned int byteLen, unsigned char *key, unsigned short sp_key_idx, unsigned char *nonce, unsigned char M, unsigned char L, unsigned char *aad, unsigned char aadByteLen, unsigned char *std_cipher, unsigned char *std_mac)
{
    unsigned char tmp_buf[16];

    unsigned int *std_plain_buf  = (unsigned int *)(DMA_RAM_BASE);
    unsigned int *std_cipher_buf = std_plain_buf + 0x200;
    unsigned int *std_mac_buf    = std_cipher_buf + 0x200;

    unsigned int *in  = std_mac_buf + 0x200;
    unsigned int *out = in + 0x200;
    unsigned int  tmp_len, aad_offset;
    unsigned int  aad_with_prefix_bytes = 0, aad_with_prefix_block_words;
    unsigned int  i, j, ret;

    char *name[] = {"", "", "", "", "", "AES_128", "AES_192", "AES_256", "SM4"};

    unsigned int block_byteLen; //, block_wordLen;    //, dma_block_wordLen=4;
    SKE_CCM_CTX  ctx[1];

    printf("\r\n %s CCM DMA test(M=%u bytes(mac bytes),L=%u bytes(nonce bytes is %u),AAD=%u bytes,P/C=%u bytes)",
           name[alg],
           M,
           L,
           15u - L,
           aadByteLen,
           byteLen);
    fflush(stdout);

    block_byteLen = ske_lp_get_block_byte_len(alg);
    //  block_wordLen = block_byteLen/4;

    //set plain
    uint32_copy(std_plain_buf, (unsigned int *)std_plain, (byteLen & (~0x0F)) / 4);
    if (byteLen & 0x0F) {
        memcpy_(tmp_buf, std_plain + (byteLen & (~0x0F)), byteLen & 0x0F);
        memset_(tmp_buf + (byteLen & 0x0F), 0, 16 - (byteLen & 0x0F));
        uint32_copy(std_plain_buf + (byteLen & (~0x0F)) / 4, (unsigned int *)tmp_buf, 4);
    }

    //set cipher
    uint32_copy(std_cipher_buf, (unsigned int *)std_cipher, (byteLen & (~0x0F)) / 4);
    if (byteLen & 0x0F) {
        memcpy_(tmp_buf, std_cipher + (byteLen & (~0x0F)), byteLen & 0x0F);
        memset_(tmp_buf + (byteLen & 0x0F), 0, 16 - (byteLen & 0x0F));
        uint32_copy(std_cipher_buf + (byteLen & (~0x0F)) / 4, (unsigned int *)tmp_buf, 4);
    }

    //set mac
    memcpy_(tmp_buf, std_mac, M);
    memset_(tmp_buf + M, 0, 16 - M);
    uint32_copy(std_mac_buf, (unsigned int *)tmp_buf, 4);

    //set input(B0 + aad + plaintext)
    ske_lp_ccm_get_B0(nonce, M, L, aadByteLen, byteLen, (unsigned char *)in);
    if (aadByteLen) {
        ske_lp_ccm_get_B1(aad, aadByteLen, &aad_offset, (unsigned char *)(in + 4));
        if (aad_offset == aadByteLen) {
            uint32_copy(in + 8, (unsigned int *)std_plain_buf, ((byteLen + 15) / 16) * 4);
            aad_with_prefix_bytes = 2 + aadByteLen;
        } else {
            tmp_len = aadByteLen - aad_offset;
        #if 0
            memcpy_(in+8, aad+aad_offset, tmp_len);
            if(tmp_len & 0x0F)
            {
                memset_(((unsigned char *)in)+16+16+tmp_len, 0, 16-(tmp_len & 0x0F));
            }
        #else
            for (i = 0; i < (tmp_len / 16); i++) {
                memcpy_(tmp_buf, aad + aad_offset + i * 16, 16);
                uint32_copy(in + 8 + i * 4, (unsigned int *)tmp_buf, 4);
            }
            if (tmp_len % 16) {
                memset_(tmp_buf, 0, 16);
                memcpy_(tmp_buf, aad + aad_offset + i * 16, tmp_len % 16);
                uint32_copy(in + 8 + i * 4, (unsigned int *)tmp_buf, 4);
            }
        #endif
            uint32_copy(in + 4 + 4 + (tmp_len + 15) / 16 * 4, (unsigned int *)std_plain_buf, ((byteLen + 15) / 16) * 4);
            aad_with_prefix_bytes = 16 + tmp_len;
        }
    } else {
        uint32_copy(in + 4, (unsigned int *)std_plain_buf, ((byteLen + 15) / 16) * 4);
    }
    aad_with_prefix_block_words = ((aad_with_prefix_bytes + 15) / 16) * 4;


        //ENCRYPT
        #if 1
    if (aadByteLen && (0 == byteLen)) {
        ret = ske_lp_dma_ccm_crypto(alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, in, out, byteLen, ske_call_manage);
    } else {
        ret = ske_lp_dma_ccm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, byteLen);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm encrypt 1 error, ret=%u", ret);
            fflush(stdout);
            return ret;
        } else {
            ;
        }

        ret = ske_lp_dma_ccm_update_B0_block(ctx, in, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm encrypt 2 error, ret=%u", ret);
            fflush(stdout);
            return ret;
        } else {
            ;
        }

            #if 0 //multiple style(one block every time)
        //input aad
        i=0;
        while(i < aad_with_prefix_bytes)
        {
            j = GET_MIN_LEN(block_byteLen, aad_with_prefix_bytes-i);

            ret = ske_lp_dma_ccm_update_aad_blocks(ctx, in+4+i/4, j, ske_call_manage);
            if(SKE_SUCCESS != ret)
            {
                printf("\r\n ske ccm encrypt 3 error, ret=%u", ret);fflush(stdout);
                return 1;
            }
            i+=j;
        }

        //input plaintext/ciphertext
        i=0;
        while(i < byteLen)
        {
            j = GET_MIN_LEN(block_byteLen, byteLen-i);

            ret = ske_lp_dma_ccm_update_blocks(ctx, in+4+aad_with_prefix_block_words+i/4, out+i/4, j, ske_call_manage);
            if(SKE_SUCCESS != ret)
            {
                printf("\r\n ske ccm encrypt 4 error, ret=%u", ret);fflush(stdout);
                return 1;
            }
            i+=j;
        }
            #else //multiple style(random blocks every time)
        //input aad
        i = 0;
        while (i < aad_with_prefix_bytes) {
            j = ske_get_rand_number(aad_with_prefix_bytes / block_byteLen);
            j = j * block_byteLen;
            j = GET_MIN_LEN(j, aad_with_prefix_bytes - i);

            ret = ske_lp_dma_ccm_update_aad_blocks(ctx, in + 4 + i / 4, j, ske_call_manage);
            if (SKE_SUCCESS != ret) {
                printf("\r\n ske ccm encrypt 3 error, ret=%u", ret);
                fflush(stdout);
                return 1;
            }
            i += j;
        }

        //input plaintext/ciphertext
        i = 0;
        while (i < byteLen) {
            j = ske_get_rand_number(byteLen / block_byteLen);
            j = j * block_byteLen;
            j = GET_MIN_LEN(j, byteLen - i);

            ret = ske_lp_dma_ccm_update_blocks(ctx, in + 4 + aad_with_prefix_block_words + i / 4, out + i / 4, j, ske_call_manage);
            if (SKE_SUCCESS != ret) {
                printf("\r\n ske ccm encrypt 4 error, ret=%u", ret);
                fflush(stdout);
                return 1;
            }
            i += j;
        }
            #endif

        ret = ske_lp_dma_ccm_final(ctx);
    }
        #else
    ret = ske_lp_dma_ccm_crypto(alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, in, out, byteLen, ske_call_manage);
        #endif
    if (SKE_SUCCESS != ret || uint32_BigNumCmp(out, ((byteLen + 15) / 16) * 4, std_cipher_buf, ((byteLen + 15) / 16) * 4) ||
        memcmp_(out + ((byteLen + 15) / 16) * 4, std_mac_buf, M)) {
        printf("\r\n ske ccm encrypt error, ret=%u", ret);

        print_buf_U8((unsigned char *)std_cipher_buf, byteLen, "std_cipher");
        print_buf_U8((unsigned char *)std_mac_buf, M, "std_mac");
        print_buf_U8((unsigned char *)in, 16 + (aadByteLen ? ((aadByteLen + 15) / 16) * 16 : 0) + ((byteLen + 15) / 16) * 16, "in");
        print_buf_U8((unsigned char *)out, 16 + ((byteLen + 15) / 16) * 16, "out");
        return 1;
    }


    //DECRYPT
    //set input(B0 + aad + ciphertext)
    ske_lp_ccm_get_B0(nonce, M, L, aadByteLen, byteLen, (unsigned char *)in);

    if (aadByteLen) {
        ske_lp_ccm_get_B1(aad, aadByteLen, &aad_offset, (unsigned char *)(in + 4));

        if (aad_offset == aadByteLen) {
            uint32_copy(in + 8, (unsigned int *)out, ((byteLen + 15) / 16) * 4);
        } else {
            tmp_len = aadByteLen - aad_offset;
        #if 0
            memcpy_(in+8, aad+aad_offset, tmp_len);
            if(tmp_len & 0x0F)
            {
                memset_(((unsigned char *)in)+16+16+tmp_len, 0, 16-(tmp_len & 0x0F));
            }
        #else
            for (i = 0; i < (tmp_len / 16); i++) {
                memcpy_(tmp_buf, aad + aad_offset + i * 16, 16);
                uint32_copy(in + 8 + i * 4, (unsigned int *)tmp_buf, 4);
            }
            if (tmp_len % 16) {
                memset_(tmp_buf, 0, 16);
                memcpy_(tmp_buf, aad + aad_offset + i * 16, tmp_len % 16);
                uint32_copy(in + 8 + i * 4, (unsigned int *)tmp_buf, 4);
            }
        #endif
            uint32_copy(in + 4 + 4 + (tmp_len + 15) / 16 * 4, (unsigned int *)out, ((byteLen + 15) / 16) * 4);
        }
    } else {
        uint32_copy(in + 4, (unsigned int *)out, ((byteLen + 15) / 16) * 4);
    }

        #if 1
    if (aadByteLen && (0 == byteLen)) {
        ret = ske_lp_dma_ccm_crypto(alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, in, out, byteLen, ske_call_manage);
    } else {
        ret = ske_lp_dma_ccm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, byteLen);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm decrypt 1 error, ret=%u", ret);
            fflush(stdout);
            return ret;
        } else {
            ;
        }

        ret = ske_lp_dma_ccm_update_B0_block(ctx, in, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske ccm decrypt 1 error, ret=%u", ret);
            fflush(stdout);
            return ret;
        } else {
            ;
        }

            #if 0 //multiple style(one block every time)
        //input aad
        i=0;
        while(i < aad_with_prefix_bytes)
        {
            j = GET_MIN_LEN(block_byteLen, aad_with_prefix_bytes-i);

            ret = ske_lp_dma_ccm_update_aad_blocks(ctx, in+4+i/4, j, ske_call_manage);
            if(SKE_SUCCESS != ret)
            {
                printf("\r\n ske ccm decrypt 3 error, ret=%u", ret);fflush(stdout);
                return 1;
            }
            i+=j;
        }

        //input plaintext/ciphertext
        i=0;
        while(i < byteLen)
        {
            j = GET_MIN_LEN(block_byteLen, byteLen-i);

            ret = ske_lp_dma_ccm_update_blocks(ctx, in+4+aad_with_prefix_block_words+i/4, out+i/4, j, ske_call_manage);
            if(SKE_SUCCESS != ret)
            {
                printf("\r\n ske ccm decrypt 4 error, ret=%u", ret);fflush(stdout);
                return 1;
            }
            i+=j;
        }
            #else //multiple style(random blocks every time)
        //input aad
        i = 0;
        while (i < aad_with_prefix_bytes) {
            j = ske_get_rand_number(aad_with_prefix_bytes / block_byteLen);
            j = j * block_byteLen;
            j = GET_MIN_LEN(j, aad_with_prefix_bytes - i);

            ret = ske_lp_dma_ccm_update_aad_blocks(ctx, in + 4 + i / 4, j, ske_call_manage);
            if (SKE_SUCCESS != ret) {
                printf("\r\n ske ccm decrypt 3 error, ret=%u", ret);
                fflush(stdout);
                return 1;
            }
            i += j;
        }

        //input plaintext/ciphertext
        i = 0;
        while (i < byteLen) {
            j = ske_get_rand_number(byteLen / block_byteLen);
            j = j * block_byteLen;
            j = GET_MIN_LEN(j, byteLen - i);

            ret = ske_lp_dma_ccm_update_blocks(ctx, in + 4 + aad_with_prefix_block_words + i / 4, out + i / 4, j, ske_call_manage);
            if (SKE_SUCCESS != ret) {
                printf("\r\n ske ccm decrypt 4 error, ret=%u", ret);
                fflush(stdout);
                return 1;
            }
            i += j;
        }
            #endif

        ret = ske_lp_dma_ccm_final(ctx);
    }
        #else
    ret = ske_lp_dma_ccm_crypto(alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, nonce, M, L, aadByteLen, in, out, byteLen, ske_call_manage);
        #endif

    if (SKE_SUCCESS != ret || uint32_BigNumCmp(out, ((byteLen + 15) / 16) * 4, std_plain_buf, ((byteLen + 15) / 16) * 4) ||
        memcmp_(out + ((byteLen + 15) / 16) * 4, std_mac_buf, M)) {
        printf("\r\n ske ccm decrypt error, ret=%u", ret);
        print_buf_U8((unsigned char *)in, ((aadByteLen + 15) / 16) * 16 + ((byteLen + 15) / 16) * 16, "in");
        print_buf_U8((unsigned char *)out, 16 + ((byteLen + 15) / 16) * 16, "out");
        return 1;
    }

    printf("\r\n CCM DMA test success!!");

    return 0;
}
    #endif


//typedef struct {
//  SKE_ALG alg;
//  const unsigned char *std_plain;
//  unsigned int c_bytes;    //byte length of plaintext or ciphertext
//  const unsigned char *key;
//  unsigned short keyid;
//  const unsigned char *nonce;
//  unsigned int M;
//  unsigned int L;
//  const unsigned char *aad;
//  unsigned int aad_bytes;
//  const unsigned char *std_cipher;
//  const unsigned char *std_mac;
//}SKE_CCM_TEST_VECTOR;


typedef struct
{
    SKE_ALG        alg;
    unsigned char *std_plain;
    unsigned int   c_bytes; //byte length of plaintext or ciphertext
    unsigned char *key;
    unsigned short keyid;
    unsigned char *nonce;
    unsigned int   M;
    unsigned int   L;
    unsigned char *aad;
    unsigned int   aad_bytes;
    unsigned char *std_cipher;
    unsigned char *std_mac;
} SKE_CCM_TEST_VECTOR;

unsigned int ske_ccm_test_internal(SKE_CCM_TEST_VECTOR *vector, unsigned int num)
{
    char        *name[] = {"", "", "", "", "", "AES_128", "AES_192", "AES_256", "SM4"};
    unsigned int i, ret;
    printf("\r\n\r\n  =================== %s CCM test ==================== ", name[vector[0].alg]);

    for (i = 0; i < num; i++) {
        ret = ske_ccm_test(vector[i].alg, 1, (unsigned char *)vector[i].std_plain, vector[i].c_bytes, (unsigned char *)vector[i].key, vector[i].keyid, (unsigned char *)vector[i].nonce, vector[i].M, vector[i].L, (unsigned char *)vector[i].aad, vector[i].aad_bytes, (unsigned char *)vector[i].std_cipher, (unsigned char *)vector[i].std_mac);
        if (ret) {
            return 1;
        }

        ret = ske_ccm_test(vector[i].alg, 0, (unsigned char *)vector[i].std_plain, vector[i].c_bytes, (unsigned char *)vector[i].key, vector[i].keyid, (unsigned char *)vector[i].nonce, vector[i].M, vector[i].L, (unsigned char *)vector[i].aad, vector[i].aad_bytes, (unsigned char *)vector[i].std_cipher, (unsigned char *)vector[i].std_mac);
        if (ret) {
            return 1;
        }

    #ifdef SKE_LP_DMA_FUNCTION
        ret = ske_dma_ccm_test(vector[i].alg, (unsigned char *)vector[i].std_plain, vector[i].c_bytes, (unsigned char *)vector[i].key, vector[i].keyid, (unsigned char *)vector[i].nonce, vector[i].M, vector[i].L, (unsigned char *)vector[i].aad, vector[i].aad_bytes, (unsigned char *)vector[i].std_cipher, (unsigned char *)vector[i].std_mac);
        if (ret) {
            return 1;
        }
    #endif
    }

    return 0;
}

unsigned char std_ccm_plain[] = {
    0x81,
    0x70,
    0x99,
    0x44,
    0xE0,
    0xCB,
    0x2E,
    0x1D,
    0xB5,
    0xB0,
    0xA4,
    0x77,
    0xD1,
    0xA8,
    0x53,
    0x9B,
    0x0A,
    0x87,
    0x86,
    0xE3,
    0x4E,
    0xAA,
    0xED,
    0x99,
    0x30,
    0x3E,
    0xA6,
    0x97,
    0x55,
    0x95,
    0xB2,
    0x45,
    0x4D,
    0x5D,
    0x7F,
    0x91,
    0xEB,
    0xBD,
    0x4A,
    0xCD,
    0x72,
    0x6C,
    0x0E,
    0x0E,
    0x5E,
    0x3E,
    0xB5,
    0x5E,
    0xF6,
    0xB1,
    0x5A,
    0x13,
    0x8E,
    0x22,
    0x6E,
    0xCD,
    0x1B,
    0x23,
    0x5A,
    0xB5,
    0xBB,
    0x52,
    0x51,
    0xC1,
    0x33,
    0x76,
    0xB2,
    0x64,
    0x48,
    0xA9,
    0xAC,
    0x1D,
    0xE8,
    0xBD,
    0x52,
    0x64,
    0x8C,
    0x0B,
    0x5F,
    0xFA,
    0x94,
    0x44,
    0x86,
    0x82,
    0xE3,
    0xCB,
    0x4D,
    0xE9,
    0xCB,
    0x8A,
    0xE7,
    0xF4,
    0xBD,
    0x41,
    0x0E,
    0xD5,
    0x02,
    0xB1,
    0x25,
    0x3A,
    0xD0,
    0x8B,
    0xB2,
    0x79,
    0x69,
    0xB5,
    0xF0,
    0x2B,
    0x10,
    0x02,
    0x9D,
    0x67,
    0xD0,
    0x7E,
    0x18,
    0x64,
    0xD9,
    0x4D,
    0x4F,
    0xCA,
    0x20,
    0x81,
    0x51,
    0xE2,
    0x6F,
    0x5F,
    0xEE,
    0x26,
    0x7B,
    0xC6,
    0x74,
    0x21,
    0x86,
    0xC4,
    0x2E,
    0x28,
    0x3A,
    0xA5,
    0xBA,
    0xD5,
    0x4A,
    0x18,
    0xEC,
    0x14,
    0x3B,
    0xAF,
    0x1E,
    0x6C,
    0x85,
    0x7F,
    0x32,
    0xEC,
    0x5D,
    0x92,
    0xB1,
    0x96,
    0xCF,
    0x7E,
    0x31,
    0x13,
    0x71,
    0xBD,
    0xA2,
    0xEA,
    0xE8,
    0xDF,
    0xD0,
    0x82,
    0xCF,
    0xEB,
    0x58,
    0x3A,
    0x41,
    0xCF,
    0xCE,
    0xAA,
    0x78,
    0x0F,
    0xD1,
    0x7F,
    0xBA,
    0xE9,
    0x31,
    0xDE,
    0xF7,
    0x17,
    0xB4,
    0x5B,
    0xB8,
    0x6F,
    0x15,
    0xD6,
    0x01,
    0xF5,
    0x44,
    0xFB,
    0xCC,
    0xB2,
    0x43,
    0x5F,
    0x80,
    0xE8,
    0x9D,
    0x6F,
    0x21,
    0x87,
    0x06,
    0x37,
    0x86,
    0x01,
    0xEA,
    0x99,
    0x15,
    0x6E,
    0x8A,
    0x88,
    0xAA,
    0xED,
    0x8C,
    0xE6,
    0x14,
    0x2F,
    0xB6,
    0x65,
    0xB6,
    0xEE,
    0xEB,
    0x6F,
    0x06,
    0xEA,
    0x9D,
    0x45,
    0xB0,
    0x14,
    0x04,
    0x00,
    0x59,
    0xB4,
    0x26,
    0x77,
    0x32,
    0xD7,
    0x33,
    0xB2,
    0xF0,
    0x92,
    0xE8,
    0x5E,
    0x40,
    0xF2,
    0x21,
    0x04,
    0xC4,
    0xF0,
    0x9C,
    0x80,
};

unsigned char std_ccm_key[32] = {0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34, 0xB4, 0x42, 0x60, 0xE1, 0x56, 0x8D, 0x9E, 0x85, 0x0A, 0x0C, 0x95, 0x37, 0x44, 0x02, 0xDE, 0x28};

unsigned char std_ccm_nonce[] = {0xC7, 0x2B, 0x65, 0x91, 0xA0, 0xD7, 0xDE, 0x8F, 0x6B, 0x40, 0x72, 0x33, 0xAD, 0x35, 0x81, 0xD6};

unsigned char std_ccm_aad[65] = {
    0xAE,
    0x30,
    0x14,
    0xAA,
    0x4E,
    0x58,
    0xBD,
    0xF9,
    0x03,
    0x23,
    0x87,
    0xED,
    0xBB,
    0x2C,
    0xF8,
    0xA3,
    0xB6,
    0xD8,
    0x39,
    0x87,
    0x0D,
    0x89,
    0x54,
    0x7F,
    0xF7,
    0x68,
    0xFD,
    0x87,
    0x70,
    0x79,
    0x37,
    0x7E,
    0x1B,
    0xAE,
    0x30,
    0x14,
    0xAA,
    0x4E,
    0x58,
    0xBD,
    0xF9,
    0x03,
    0x23,
    0x87,
    0xED,
    0xBB,
    0x2C,
    0xF8,
    0xA3,
    0xB6,
    0xD8,
    0x39,
    0x87,
    0x0D,
    0x89,
    0x54,
    0x7F,
    0xF7,
    0x68,
    0xFD,
    0x87,
    0x70,
    0x79,
    0x37,
    0x7E,
};


    #ifdef SUPPORT_SKE_AES_128
unsigned char std_aes128_ccm_mac_M16_L2_aad0_p256[]  = {0x55, 0xEA, 0x2A, 0x8F, 0x0A, 0x72, 0x1F, 0x7D, 0xFA, 0xD4, 0xB9, 0x77, 0xC1, 0x0D, 0xB3, 0x8A};
unsigned char std_aes128_ccm_mac_M14_L3_aad3_p201[]  = {0x8D, 0x8D, 0x3D, 0xBC, 0xF9, 0x71, 0xB4, 0xDE, 0x3B, 0xE1, 0x13, 0xB1, 0xAD, 0x21};
unsigned char std_aes128_ccm_mac_M12_L4_aad15_p120[] = {0xAD, 0xF4, 0xF9, 0x42, 0x9C, 0x32, 0xCA, 0x51, 0xE2, 0xCD, 0x9D, 0xCB};
unsigned char std_aes128_ccm_mac_M10_L5_aad16_p65[]  = {0xEF, 0x67, 0xD8, 0xE8, 0x7C, 0x4B, 0xA5, 0x72, 0x7A, 0x96};
unsigned char std_aes128_ccm_mac_M8_L6_aad17_p32[]   = {0x02, 0xED, 0x46, 0xC9, 0xF9, 0xF0, 0xF1, 0x47};
unsigned char std_aes128_ccm_mac_M6_L7_aad32_p15[]   = {
    0xCF,
    0x8D,
    0x20,
    0x41,
    0x87,
    0x32,
};
unsigned char std_aes128_ccm_mac_M4_L8_aad33_p0[]    = {0x72, 0xF4, 0xA8, 0x70};
unsigned char std_aes128_ccm_mac_M16_L2_aad65_p256[] = {0x0F, 0x4C, 0xA8, 0x4D, 0x80, 0xA4, 0xE6, 0xB2, 0xD3, 0x3F, 0x2E, 0x2F, 0x61, 0x7A, 0x07, 0xF3};

unsigned char std_aes128_ccm_L2_cipher[256] = {
    0xAC,
    0x5B,
    0xCC,
    0x7B,
    0xE3,
    0x4C,
    0x4A,
    0x1A,
    0x4E,
    0xF2,
    0x34,
    0x8B,
    0x9A,
    0x95,
    0xCE,
    0x6C,
    0xEB,
    0x96,
    0x15,
    0xA0,
    0x96,
    0xE9,
    0xA2,
    0x1F,
    0xEB,
    0xB9,
    0x35,
    0x87,
    0x0C,
    0x77,
    0x53,
    0xC6,
    0xFE,
    0x57,
    0xBD,
    0x48,
    0x49,
    0xD7,
    0xE9,
    0x28,
    0xED,
    0x9D,
    0xA3,
    0x5B,
    0x0A,
    0xE0,
    0x81,
    0x76,
    0x6E,
    0xD9,
    0x71,
    0x6A,
    0x19,
    0x06,
    0xB0,
    0x56,
    0x01,
    0xD6,
    0x66,
    0x70,
    0xFD,
    0xB3,
    0x62,
    0xCB,
    0x65,
    0xEE,
    0x0D,
    0xCC,
    0x25,
    0xEE,
    0x99,
    0x42,
    0x95,
    0x91,
    0x92,
    0x05,
    0x87,
    0x82,
    0x1A,
    0xD9,
    0xF5,
    0x4A,
    0xCB,
    0xD6,
    0x3D,
    0xD5,
    0x43,
    0xFC,
    0x59,
    0x50,
    0xB7,
    0xE2,
    0x6E,
    0x56,
    0xB2,
    0xEF,
    0x4A,
    0xDB,
    0xF2,
    0xE4,
    0x60,
    0xB0,
    0x1E,
    0xFB,
    0x12,
    0x99,
    0xF8,
    0x58,
    0x6C,
    0xE8,
    0x70,
    0xEB,
    0xC9,
    0x11,
    0x2E,
    0xD5,
    0xA7,
    0xCB,
    0x0F,
    0xE4,
    0x53,
    0x31,
    0x89,
    0xAD,
    0xA6,
    0x75,
    0x1E,
    0xA8,
    0x29,
    0xD8,
    0x99,
    0x89,
    0x88,
    0x9C,
    0x8D,
    0x6F,
    0x2C,
    0x11,
    0xE6,
    0x54,
    0x06,
    0x16,
    0x40,
    0xF0,
    0x6C,
    0xC2,
    0x7C,
    0xF6,
    0x83,
    0xBD,
    0xFD,
    0x48,
    0xDB,
    0x15,
    0xB8,
    0x5D,
    0xCD,
    0x2B,
    0x17,
    0xC6,
    0x56,
    0xB4,
    0x76,
    0x02,
    0x50,
    0x68,
    0x85,
    0x60,
    0x59,
    0xB9,
    0x80,
    0x69,
    0x8E,
    0xE5,
    0xB4,
    0xAE,
    0x43,
    0x8E,
    0x63,
    0x2E,
    0xDE,
    0xAC,
    0x0D,
    0x47,
    0xF9,
    0xED,
    0xB0,
    0xEA,
    0x05,
    0xBA,
    0xDB,
    0x96,
    0x2C,
    0xD2,
    0x88,
    0x05,
    0x6C,
    0xF6,
    0xD6,
    0x5D,
    0x50,
    0x73,
    0x0F,
    0x14,
    0xF2,
    0x15,
    0xE8,
    0x25,
    0x43,
    0x6A,
    0x5A,
    0x63,
    0x9C,
    0x50,
    0x4F,
    0x5C,
    0xA3,
    0x2F,
    0x39,
    0x10,
    0x2D,
    0x58,
    0x3A,
    0x01,
    0x92,
    0x6A,
    0xBE,
    0x26,
    0x58,
    0xED,
    0x94,
    0x45,
    0x04,
    0xB3,
    0x99,
    0xB5,
    0x63,
    0x67,
    0x32,
    0x3E,
    0xF7,
    0x7A,
    0x1A,
    0x33,
    0xF2,
    0x7E,
    0xA0,
    0x2E,
    0x5A,
    0xD3,
    0xD1,
    0x32,
    0x95,
    0x3D,
    0x6A,
    0x71,
};

unsigned char std_aes128_ccm_L3_cipher[201] = {
    0x2F,
    0x95,
    0xD2,
    0x46,
    0x2F,
    0x8F,
    0x2E,
    0xCF,
    0xDC,
    0x13,
    0x98,
    0x9F,
    0x87,
    0x0A,
    0x4B,
    0x86,
    0xEB,
    0x1D,
    0x14,
    0x34,
    0xD7,
    0xFB,
    0x5B,
    0x1C,
    0xBB,
    0x26,
    0xF9,
    0x33,
    0xC9,
    0x3A,
    0x23,
    0xE8,
    0x62,
    0xE4,
    0xEB,
    0x68,
    0xFA,
    0x02,
    0xF1,
    0xB9,
    0x49,
    0xF1,
    0x4D,
    0xFD,
    0x82,
    0x7B,
    0x19,
    0x82,
    0x71,
    0x78,
    0x65,
    0x8F,
    0xB6,
    0xED,
    0x33,
    0x53,
    0x02,
    0x5C,
    0xAE,
    0x7A,
    0x18,
    0xC7,
    0xF7,
    0x53,
    0x0B,
    0x3E,
    0x7A,
    0xA1,
    0xA4,
    0xAE,
    0xAA,
    0x68,
    0xC2,
    0x00,
    0xBF,
    0xD5,
    0x47,
    0xF0,
    0x4A,
    0x43,
    0x56,
    0xF9,
    0x85,
    0x40,
    0x19,
    0xEB,
    0xDA,
    0x8D,
    0x4F,
    0x59,
    0x9E,
    0x7F,
    0x1E,
    0x07,
    0xFA,
    0xBA,
    0xB9,
    0x48,
    0x26,
    0xF3,
    0x7F,
    0xA0,
    0xC3,
    0xD1,
    0x41,
    0x6A,
    0xD8,
    0x91,
    0x7F,
    0xB7,
    0x15,
    0x0D,
    0xB1,
    0xB3,
    0xE0,
    0x23,
    0x1E,
    0xE2,
    0x96,
    0xF6,
    0x3F,
    0xB1,
    0xBA,
    0x5E,
    0xBD,
    0x37,
    0xD4,
    0xC3,
    0xBB,
    0x10,
    0x0A,
    0x41,
    0x5E,
    0x04,
    0x65,
    0xE1,
    0x2F,
    0x88,
    0x90,
    0x59,
    0x01,
    0xEE,
    0x20,
    0x36,
    0x9E,
    0xB1,
    0x7A,
    0xE0,
    0xB4,
    0xBF,
    0x9A,
    0xCE,
    0x01,
    0x70,
    0xCF,
    0xF4,
    0xC7,
    0xB1,
    0x72,
    0x9F,
    0xF5,
    0xB4,
    0xA2,
    0x7C,
    0x23,
    0xC1,
    0x1B,
    0x28,
    0xBF,
    0x29,
    0x3F,
    0xDC,
    0xA4,
    0x15,
    0x93,
    0x91,
    0xC2,
    0x4B,
    0x77,
    0xC8,
    0x5D,
    0xF6,
    0xFF,
    0xF1,
    0x83,
    0xB8,
    0x92,
    0xFB,
    0xB6,
    0x2E,
    0xF9,
    0xC0,
    0xF3,
    0x01,
    0x1E,
    0x01,
    0xDB,
    0x36,
    0xFB,
    0x84,
    0x11,
};

unsigned char std_aes128_ccm_L4_cipher[120] = {
    0x1B,
    0xDE,
    0x2B,
    0x30,
    0xF7,
    0x5B,
    0xE8,
    0x08,
    0xB1,
    0xA4,
    0x37,
    0xD2,
    0x7C,
    0x0C,
    0x2D,
    0x80,
    0x5F,
    0x9E,
    0xA5,
    0x82,
    0x0F,
    0x0C,
    0xDE,
    0xAE,
    0x84,
    0x01,
    0x3E,
    0xE8,
    0x88,
    0xB2,
    0x2B,
    0x42,
    0x9B,
    0x27,
    0xC9,
    0x78,
    0x7C,
    0xB5,
    0x82,
    0x9A,
    0x06,
    0xF4,
    0xA6,
    0xFD,
    0xC4,
    0x2A,
    0x7E,
    0x1D,
    0x69,
    0x71,
    0x1C,
    0x54,
    0x2E,
    0x1D,
    0xF1,
    0x30,
    0x68,
    0xD4,
    0x16,
    0x4C,
    0x96,
    0xA2,
    0xDC,
    0xB8,
    0xD1,
    0x04,
    0xF8,
    0x68,
    0xE0,
    0x02,
    0x1E,
    0xA2,
    0xC2,
    0xBC,
    0x2C,
    0x13,
    0xDC,
    0x08,
    0xC3,
    0x19,
    0x4F,
    0x7C,
    0x59,
    0xC2,
    0x8E,
    0xBE,
    0x36,
    0xBF,
    0x09,
    0x7F,
    0x9E,
    0x5E,
    0xFD,
    0xDB,
    0x46,
    0xE7,
    0xA8,
    0xD2,
    0x47,
    0x2C,
    0x7F,
    0x7C,
    0x59,
    0x1F,
    0x78,
    0x55,
    0xC5,
    0x51,
    0x71,
    0x5D,
    0x33,
    0x39,
    0x30,
    0x25,
    0x42,
    0x8A,
    0xDF,
    0xB7,
    0xC9,
    0xF9,
};

unsigned char std_aes128_ccm_L5_cipher[65] = {
    0x67,
    0x33,
    0x4E,
    0xD9,
    0xDE,
    0xDF,
    0x45,
    0xF3,
    0xC4,
    0x0B,
    0xDB,
    0x41,
    0xE6,
    0xF2,
    0x7A,
    0x28,
    0x20,
    0xD1,
    0xBF,
    0xBD,
    0x92,
    0x91,
    0x31,
    0x5F,
    0x75,
    0x8B,
    0xA6,
    0xE8,
    0x38,
    0x79,
    0x01,
    0x54,
    0x5B,
    0xD5,
    0xAA,
    0x94,
    0x2F,
    0xA2,
    0xEC,
    0xDC,
    0xDE,
    0x0B,
    0x2B,
    0xBA,
    0x85,
    0xFC,
    0x13,
    0x3B,
    0x89,
    0x83,
    0x1F,
    0x54,
    0xE5,
    0x0C,
    0x53,
    0x06,
    0xCB,
    0x68,
    0xDF,
    0xA6,
    0x49,
    0x30,
    0x8B,
    0x8E,
    0xB5,
};

unsigned char std_aes128_ccm_L6_cipher[32] = {
    0x31,
    0x66,
    0x94,
    0x79,
    0x7C,
    0x7A,
    0x0E,
    0xB0,
    0xC2,
    0xAF,
    0xCD,
    0x89,
    0x24,
    0xBC,
    0xBD,
    0x3B,
    0x66,
    0x99,
    0x92,
    0xBB,
    0x48,
    0x1E,
    0x05,
    0xE2,
    0x31,
    0xE4,
    0xD9,
    0x8C,
    0xE5,
    0xC8,
    0x26,
    0x74,
};

unsigned char std_aes128_ccm_L7_cipher[15] = {
    0x59,
    0xBE,
    0x56,
    0x1D,
    0x54,
    0x81,
    0x39,
    0x3D,
    0x31,
    0xDD,
    0xBB,
    0x28,
    0x6B,
    0x85,
    0xDB,
};

unsigned int aes_128_ccm_test(void)
{
    SKE_CCM_TEST_VECTOR vector[8] = {
        {SKE_ALG_AES_128, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 0,  std_aes128_ccm_L2_cipher, std_aes128_ccm_mac_M16_L2_aad0_p256 },
        {SKE_ALG_AES_128, std_ccm_plain, 201, std_ccm_key, 0, std_ccm_nonce, 14, 3, std_ccm_aad, 3,  std_aes128_ccm_L3_cipher, std_aes128_ccm_mac_M14_L3_aad3_p201 },
        {SKE_ALG_AES_128, std_ccm_plain, 120, std_ccm_key, 0, std_ccm_nonce, 12, 4, std_ccm_aad, 15, std_aes128_ccm_L4_cipher, std_aes128_ccm_mac_M12_L4_aad15_p120},
        {SKE_ALG_AES_128, std_ccm_plain, 65,  std_ccm_key, 0, std_ccm_nonce, 10, 5, std_ccm_aad, 16, std_aes128_ccm_L5_cipher, std_aes128_ccm_mac_M10_L5_aad16_p65 },
        {SKE_ALG_AES_128, std_ccm_plain, 32,  std_ccm_key, 0, std_ccm_nonce, 8,  6, std_ccm_aad, 17, std_aes128_ccm_L6_cipher, std_aes128_ccm_mac_M8_L6_aad17_p32  },
        {SKE_ALG_AES_128, std_ccm_plain, 15,  std_ccm_key, 0, std_ccm_nonce, 6,  7, std_ccm_aad, 32, std_aes128_ccm_L7_cipher, std_aes128_ccm_mac_M6_L7_aad32_p15  },
        {SKE_ALG_AES_128, std_ccm_plain, 0,   std_ccm_key, 0, std_ccm_nonce, 4,  8, std_ccm_aad, 33, NULL,                     std_aes128_ccm_mac_M4_L8_aad33_p0   },
        {SKE_ALG_AES_128, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 65, std_aes128_ccm_L2_cipher, std_aes128_ccm_mac_M16_L2_aad65_p256},
    };

    return ske_ccm_test_internal(vector, 8);
}
    #endif


    #ifdef SUPPORT_SKE_AES_192
unsigned char std_aes192_ccm_mac_M16_L2_aad0_p256[]  = {0x38, 0x46, 0xF9, 0xCA, 0x7E, 0x38, 0x73, 0x86, 0xB7, 0xB3, 0xF8, 0x27, 0xC0, 0xF5, 0xAE, 0x85};
unsigned char std_aes192_ccm_mac_M14_L3_aad3_p201[]  = {0x17, 0xA2, 0xE6, 0xFC, 0xF9, 0x86, 0xA8, 0x87, 0xE8, 0x03, 0x41, 0x75, 0x56, 0xD5};
unsigned char std_aes192_ccm_mac_M12_L4_aad15_p120[] = {0x98, 0x63, 0x22, 0x56, 0x54, 0x11, 0xED, 0x89, 0x50, 0x84, 0x55, 0x55};
unsigned char std_aes192_ccm_mac_M10_L5_aad16_p65[]  = {0x61, 0x21, 0xA7, 0x6B, 0x4E, 0xEF, 0x54, 0xAC, 0xB7, 0xB5};
unsigned char std_aes192_ccm_mac_M8_L6_aad17_p32[]   = {0x28, 0x40, 0x84, 0x96, 0x2B, 0xE4, 0x08, 0xD6};
unsigned char std_aes192_ccm_mac_M6_L7_aad32_p15[]   = {
    0x3A,
    0x46,
    0x59,
    0x0A,
    0xC3,
    0xFC,
};
unsigned char std_aes192_ccm_mac_M4_L8_aad33_p0[]    = {0x1A, 0x53, 0x07, 0x6F};
unsigned char std_aes192_ccm_mac_M16_L2_aad65_p256[] = {0xF4, 0xED, 0x57, 0x02, 0x61, 0xAA, 0x23, 0x66, 0xA7, 0xDF, 0x8D, 0x49, 0xA9, 0xC2, 0x88, 0xF1};

unsigned char std_aes192_ccm_L2_cipher[256] = {
    0xAF,
    0xB0,
    0x9E,
    0x94,
    0x50,
    0x6F,
    0xAE,
    0x11,
    0xA5,
    0xE2,
    0xA6,
    0x4F,
    0x30,
    0x66,
    0x24,
    0x57,
    0xA4,
    0x45,
    0x7D,
    0x9E,
    0x0E,
    0x78,
    0xC1,
    0xB1,
    0xC9,
    0x79,
    0x28,
    0x4E,
    0x2E,
    0x94,
    0x7C,
    0xEC,
    0x2B,
    0x62,
    0xFB,
    0x24,
    0x01,
    0x9A,
    0x03,
    0x88,
    0x08,
    0xAD,
    0xB8,
    0xE9,
    0xEF,
    0x85,
    0x31,
    0x75,
    0xC8,
    0xCA,
    0x94,
    0x51,
    0x30,
    0xD6,
    0x8F,
    0x6C,
    0x58,
    0xA7,
    0x79,
    0xCB,
    0x10,
    0x1B,
    0x52,
    0x2F,
    0x81,
    0x2D,
    0x49,
    0xAE,
    0x43,
    0xF5,
    0xED,
    0x62,
    0x74,
    0x49,
    0x11,
    0xF7,
    0xE2,
    0xBC,
    0x46,
    0xD4,
    0x0C,
    0x7D,
    0x3C,
    0xF5,
    0x82,
    0x37,
    0xC5,
    0xCB,
    0x30,
    0xE4,
    0xC6,
    0x52,
    0xEA,
    0xF4,
    0x68,
    0x71,
    0x59,
    0xAC,
    0x92,
    0xE9,
    0x8C,
    0x2A,
    0xD7,
    0x82,
    0xF1,
    0x75,
    0x34,
    0xFA,
    0x42,
    0x58,
    0xF3,
    0x8E,
    0x7C,
    0x23,
    0x60,
    0xC7,
    0xEB,
    0xCA,
    0x1F,
    0xD0,
    0xC6,
    0x25,
    0xD9,
    0xCD,
    0x6B,
    0x23,
    0xE0,
    0xCE,
    0x4C,
    0xAB,
    0xA4,
    0x51,
    0xCA,
    0x45,
    0x23,
    0x0C,
    0x73,
    0x45,
    0x2C,
    0x04,
    0x2F,
    0x38,
    0x06,
    0x4A,
    0x10,
    0xB7,
    0x68,
    0x8F,
    0x4F,
    0x2D,
    0x8C,
    0xF4,
    0x04,
    0xA5,
    0x51,
    0x36,
    0xD9,
    0xED,
    0x42,
    0x77,
    0x1F,
    0xF0,
    0x7C,
    0xA2,
    0xE7,
    0x23,
    0xCD,
    0x47,
    0x22,
    0xF8,
    0xA1,
    0x22,
    0xD1,
    0x17,
    0x62,
    0xE7,
    0x31,
    0x5A,
    0xDB,
    0x99,
    0x9F,
    0x75,
    0x1A,
    0xD1,
    0xE4,
    0x79,
    0xED,
    0x58,
    0x80,
    0x54,
    0xB2,
    0xA2,
    0xDA,
    0x89,
    0x71,
    0x4B,
    0x6E,
    0x22,
    0xE5,
    0xF4,
    0x16,
    0x18,
    0xD3,
    0x3C,
    0x6B,
    0xA8,
    0xE9,
    0xA1,
    0xF3,
    0x74,
    0xBD,
    0x71,
    0x96,
    0x89,
    0x6A,
    0x59,
    0x20,
    0x06,
    0xDD,
    0xE5,
    0xD3,
    0xB0,
    0x05,
    0xEB,
    0x92,
    0xCE,
    0xEC,
    0xD2,
    0x0A,
    0xE0,
    0xCC,
    0x3B,
    0x86,
    0x94,
    0x4D,
    0xFD,
    0x72,
    0xAE,
    0x6C,
    0xCE,
    0x16,
    0xD2,
    0xAE,
    0x67,
    0xFD,
    0xE2,
    0x73,
    0x74,
    0x8F,
    0x1D,
    0xDD,
    0xCB,
    0x77,
    0x6A,
    0x45,
    0x0C,
};

unsigned char std_aes192_ccm_L3_cipher[201] = {
    0xFE,
    0xA4,
    0x8A,
    0xA4,
    0x48,
    0x91,
    0x6A,
    0x7F,
    0xEC,
    0x1F,
    0x7B,
    0x79,
    0xD9,
    0x42,
    0x94,
    0x26,
    0x83,
    0x34,
    0x2D,
    0x24,
    0xAD,
    0x00,
    0x17,
    0x93,
    0xDB,
    0xBE,
    0xEE,
    0x13,
    0x1C,
    0x0E,
    0xF4,
    0x2B,
    0x99,
    0xC3,
    0xB5,
    0x98,
    0x25,
    0xA8,
    0x76,
    0x1A,
    0x35,
    0x9E,
    0x36,
    0x2F,
    0xCE,
    0x7E,
    0xE0,
    0xCA,
    0xD9,
    0xF4,
    0x3F,
    0x8A,
    0xFA,
    0x4C,
    0x6C,
    0xDE,
    0x47,
    0x69,
    0x5C,
    0x1E,
    0xC0,
    0x0E,
    0xEB,
    0x73,
    0xD0,
    0xC1,
    0xEE,
    0x68,
    0x0C,
    0x9E,
    0x33,
    0xF0,
    0x5D,
    0xF2,
    0x5C,
    0x69,
    0x09,
    0x93,
    0xEF,
    0x3D,
    0x67,
    0x18,
    0xAF,
    0x02,
    0x2C,
    0x82,
    0xCA,
    0x8F,
    0xFF,
    0xB3,
    0x76,
    0x0D,
    0x0D,
    0x07,
    0xE2,
    0xD4,
    0x02,
    0xA2,
    0xC4,
    0x38,
    0x0F,
    0x2C,
    0x62,
    0xFA,
    0x88,
    0x18,
    0x94,
    0x6A,
    0x07,
    0xA3,
    0xB5,
    0x15,
    0xF1,
    0xBD,
    0x1F,
    0xF4,
    0x29,
    0x75,
    0xC6,
    0x7A,
    0x3D,
    0xD0,
    0x11,
    0x4F,
    0x2A,
    0x0E,
    0x1A,
    0xA6,
    0x72,
    0x76,
    0x10,
    0x68,
    0x04,
    0x89,
    0x35,
    0xB7,
    0xEC,
    0xB2,
    0xE1,
    0xE6,
    0xD9,
    0x05,
    0xCA,
    0x5B,
    0x1C,
    0x60,
    0xF7,
    0x10,
    0x3A,
    0x3E,
    0x96,
    0x2F,
    0xEE,
    0x50,
    0x05,
    0x37,
    0xD8,
    0xE8,
    0xC5,
    0x1F,
    0xA0,
    0xA0,
    0x6C,
    0x7A,
    0x8D,
    0xFC,
    0xE5,
    0xF1,
    0x1C,
    0x15,
    0x89,
    0xCF,
    0x61,
    0x4D,
    0x52,
    0x0D,
    0x61,
    0xF9,
    0x00,
    0xDC,
    0xB6,
    0x31,
    0x80,
    0x9D,
    0x39,
    0xD9,
    0x08,
    0x92,
    0x99,
    0xA8,
    0x10,
    0x3D,
    0xEE,
    0xD4,
    0x04,
    0xF7,
    0x25,
    0x50,
    0x10,
    0x70,
    0xEA,
};

unsigned char std_aes192_ccm_L4_cipher[120] = {
    0x71,
    0xBF,
    0xE7,
    0x42,
    0xAB,
    0xA0,
    0xB2,
    0x45,
    0xF3,
    0xCC,
    0x3C,
    0x3E,
    0xFC,
    0x98,
    0xE2,
    0x05,
    0x17,
    0x97,
    0x0C,
    0xDF,
    0xC0,
    0x63,
    0xD8,
    0xF3,
    0x5A,
    0xE3,
    0xC9,
    0x14,
    0x1F,
    0xE6,
    0x17,
    0x35,
    0xA7,
    0xCA,
    0x95,
    0x3C,
    0x7D,
    0xD0,
    0xB8,
    0x05,
    0x60,
    0xE2,
    0x1C,
    0xF0,
    0xB7,
    0xAF,
    0x69,
    0xB8,
    0x00,
    0x4C,
    0x52,
    0xA0,
    0xC2,
    0xB6,
    0xCC,
    0xAE,
    0x0E,
    0xED,
    0xC3,
    0xFA,
    0x77,
    0x20,
    0x64,
    0x97,
    0x22,
    0x8B,
    0x58,
    0xB4,
    0xBD,
    0xCA,
    0x1C,
    0x3C,
    0x94,
    0x29,
    0x60,
    0x11,
    0x21,
    0xFC,
    0xC9,
    0x1A,
    0xF1,
    0xA1,
    0x05,
    0xC8,
    0xD1,
    0x0D,
    0x3C,
    0xC7,
    0x2B,
    0xB6,
    0x3B,
    0xA6,
    0x9E,
    0xD8,
    0x09,
    0xFD,
    0xB9,
    0x9F,
    0xC4,
    0xA2,
    0xEC,
    0xF9,
    0x9F,
    0x74,
    0x46,
    0x2E,
    0xA2,
    0x85,
    0xA4,
    0x2F,
    0x57,
    0x6C,
    0xFC,
    0x8D,
    0x6E,
    0x54,
    0x9B,
    0x89,
    0x4D,
    0xDC,
};

unsigned char std_aes192_ccm_L5_cipher[65] = {
    0xCD,
    0x5C,
    0xB5,
    0x53,
    0xFB,
    0x7D,
    0x57,
    0xAC,
    0x1F,
    0x06,
    0xBF,
    0x74,
    0x9D,
    0x6E,
    0x14,
    0x4A,
    0x00,
    0x01,
    0xAE,
    0xA7,
    0x87,
    0x60,
    0x6D,
    0x48,
    0xA6,
    0x7B,
    0x0B,
    0xC9,
    0x16,
    0xFD,
    0xE3,
    0xAB,
    0xDF,
    0x7C,
    0x7C,
    0x13,
    0xD8,
    0x68,
    0x73,
    0x18,
    0x4C,
    0x64,
    0x99,
    0x6C,
    0x33,
    0x7F,
    0x46,
    0xCF,
    0x9C,
    0xD3,
    0x1C,
    0xB0,
    0x5C,
    0xAD,
    0x8F,
    0xA6,
    0x85,
    0xE6,
    0x81,
    0x1D,
    0x43,
    0x97,
    0x64,
    0xD8,
    0xEC,
};

unsigned char std_aes192_ccm_L6_cipher[32] = {
    0xD5,
    0xF6,
    0x4B,
    0x51,
    0x6A,
    0xFF,
    0x12,
    0xE5,
    0x07,
    0x11,
    0xD6,
    0x24,
    0x4E,
    0xA7,
    0x90,
    0x95,
    0x42,
    0xE8,
    0x00,
    0xE4,
    0x9F,
    0x48,
    0x58,
    0x41,
    0xBB,
    0x92,
    0x6A,
    0xC2,
    0x36,
    0x54,
    0x20,
    0x95,
};

unsigned char std_aes192_ccm_L7_cipher[15] = {
    0x4A,
    0xAF,
    0xA8,
    0x09,
    0xBD,
    0xA5,
    0x96,
    0x7B,
    0x4A,
    0x59,
    0x8F,
    0x04,
    0x42,
    0xD9,
    0x1F,
};

unsigned int aes_192_ccm_test(void)
{
    SKE_CCM_TEST_VECTOR vector[8] = {
        {SKE_ALG_AES_192, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 0,  std_aes192_ccm_L2_cipher, std_aes192_ccm_mac_M16_L2_aad0_p256 },
        {SKE_ALG_AES_192, std_ccm_plain, 201, std_ccm_key, 0, std_ccm_nonce, 14, 3, std_ccm_aad, 3,  std_aes192_ccm_L3_cipher, std_aes192_ccm_mac_M14_L3_aad3_p201 },
        {SKE_ALG_AES_192, std_ccm_plain, 120, std_ccm_key, 0, std_ccm_nonce, 12, 4, std_ccm_aad, 15, std_aes192_ccm_L4_cipher, std_aes192_ccm_mac_M12_L4_aad15_p120},
        {SKE_ALG_AES_192, std_ccm_plain, 65,  std_ccm_key, 0, std_ccm_nonce, 10, 5, std_ccm_aad, 16, std_aes192_ccm_L5_cipher, std_aes192_ccm_mac_M10_L5_aad16_p65 },
        {SKE_ALG_AES_192, std_ccm_plain, 32,  std_ccm_key, 0, std_ccm_nonce, 8,  6, std_ccm_aad, 17, std_aes192_ccm_L6_cipher, std_aes192_ccm_mac_M8_L6_aad17_p32  },
        {SKE_ALG_AES_192, std_ccm_plain, 15,  std_ccm_key, 0, std_ccm_nonce, 6,  7, std_ccm_aad, 32, std_aes192_ccm_L7_cipher, std_aes192_ccm_mac_M6_L7_aad32_p15  },
        {SKE_ALG_AES_192, std_ccm_plain, 0,   std_ccm_key, 0, std_ccm_nonce, 4,  8, std_ccm_aad, 33, NULL,                     std_aes192_ccm_mac_M4_L8_aad33_p0   },
        {SKE_ALG_AES_192, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 65, std_aes192_ccm_L2_cipher, std_aes192_ccm_mac_M16_L2_aad65_p256},
    };

    return ske_ccm_test_internal(vector, 8);
}
    #endif


    #ifdef SUPPORT_SKE_AES_256
unsigned char std_aes256_ccm_mac_M16_L2_aad0_p256[]  = {0x5B, 0x95, 0x7A, 0x4F, 0xC0, 0x05, 0xD4, 0xA0, 0x75, 0x46, 0xCC, 0xA7, 0xA6, 0x8C, 0x5D, 0xF4};
unsigned char std_aes256_ccm_mac_M14_L3_aad3_p201[]  = {0x0D, 0x0D, 0x80, 0xE1, 0xDB, 0x0C, 0xB9, 0x0C, 0x58, 0x41, 0xF9, 0x04, 0xD0, 0xAD};
unsigned char std_aes256_ccm_mac_M12_L4_aad15_p120[] = {0xDA, 0xA3, 0x68, 0xFF, 0x53, 0xEC, 0x4D, 0xC0, 0x7B, 0xA3, 0xF5, 0xAD};
unsigned char std_aes256_ccm_mac_M10_L5_aad16_p65[]  = {0x5D, 0x7E, 0x79, 0x27, 0xAD, 0x13, 0xED, 0x47, 0x25, 0xCA};
unsigned char std_aes256_ccm_mac_M8_L6_aad17_p32[]   = {0x44, 0x8A, 0x84, 0xC5, 0x5F, 0xB1, 0x88, 0xA6};
unsigned char std_aes256_ccm_mac_M6_L7_aad32_p15[]   = {
    0x05,
    0x8A,
    0x77,
    0xD3,
    0xDA,
    0x37,
};
unsigned char std_aes256_ccm_mac_M4_L8_aad33_p0[]    = {0xBA, 0x44, 0x43, 0x17};
unsigned char std_aes256_ccm_mac_M16_L2_aad65_p256[] = {0xFA, 0x18, 0x05, 0xA8, 0xEE, 0xEC, 0x1A, 0x21, 0x01, 0x0E, 0x2D, 0xE9, 0xCE, 0x82, 0x83, 0xE8};

unsigned char std_aes256_ccm_L2_cipher[256] = {
    0xB3,
    0x5E,
    0x02,
    0xD0,
    0x7D,
    0xCA,
    0x4C,
    0xA4,
    0x57,
    0x0A,
    0x45,
    0x43,
    0xC0,
    0xEF,
    0x4D,
    0xFC,
    0xFA,
    0x33,
    0x68,
    0xDB,
    0x78,
    0xD0,
    0xFF,
    0xD3,
    0xC0,
    0xFC,
    0xDF,
    0xB5,
    0xB3,
    0xF6,
    0x92,
    0x76,
    0xD7,
    0x1C,
    0xE0,
    0xD5,
    0xEA,
    0x6F,
    0xEB,
    0xF0,
    0xA1,
    0xB2,
    0x4B,
    0xE9,
    0xC7,
    0x62,
    0xFE,
    0x76,
    0x0F,
    0x20,
    0x60,
    0xCB,
    0x76,
    0x5D,
    0x8F,
    0x40,
    0xFF,
    0x03,
    0xA8,
    0xB2,
    0xB9,
    0xD7,
    0x1A,
    0xED,
    0x44,
    0x18,
    0x2B,
    0x18,
    0xEC,
    0x4B,
    0xBB,
    0x71,
    0x80,
    0x17,
    0x33,
    0xC0,
    0xAF,
    0xCE,
    0xFC,
    0x21,
    0x8E,
    0xBA,
    0xC7,
    0xB6,
    0xA6,
    0x57,
    0x4F,
    0xA3,
    0x15,
    0xDC,
    0xFA,
    0xF9,
    0x53,
    0x57,
    0x5F,
    0x48,
    0x21,
    0xC1,
    0xA2,
    0x22,
    0x05,
    0xC8,
    0x95,
    0x32,
    0x15,
    0x3B,
    0xB6,
    0xA1,
    0x43,
    0x33,
    0x24,
    0x9A,
    0x1F,
    0x4D,
    0x6A,
    0xA9,
    0x64,
    0xDB,
    0x8D,
    0x4B,
    0xDD,
    0xA0,
    0xD1,
    0xE2,
    0x07,
    0x8D,
    0x1A,
    0x1A,
    0x0C,
    0x34,
    0x2D,
    0xBE,
    0x0B,
    0xD7,
    0xF2,
    0xC8,
    0x7E,
    0x65,
    0x2A,
    0x6A,
    0x0E,
    0xD6,
    0x2F,
    0x91,
    0xE3,
    0xDE,
    0x4A,
    0x8A,
    0x9A,
    0xEB,
    0x31,
    0x44,
    0x23,
    0x5D,
    0xF4,
    0xE8,
    0x10,
    0x85,
    0x25,
    0xBB,
    0x00,
    0x1B,
    0x65,
    0x02,
    0x9C,
    0x1B,
    0x20,
    0xB8,
    0x0C,
    0x5F,
    0xE5,
    0x0E,
    0xAC,
    0xA5,
    0xAE,
    0x72,
    0x6D,
    0xC7,
    0x59,
    0x6D,
    0x55,
    0x8A,
    0x3B,
    0x30,
    0x98,
    0xCE,
    0x62,
    0xBF,
    0x05,
    0x0C,
    0xC7,
    0x88,
    0x99,
    0x35,
    0x5F,
    0xC4,
    0x8A,
    0x58,
    0xBA,
    0x30,
    0x91,
    0xE5,
    0x2E,
    0xEA,
    0x46,
    0x06,
    0x2D,
    0x71,
    0x9F,
    0x08,
    0x59,
    0xDA,
    0xB2,
    0x78,
    0xCD,
    0x98,
    0xAF,
    0x18,
    0xC2,
    0xA7,
    0x2C,
    0x6C,
    0x53,
    0x56,
    0x20,
    0x2B,
    0xD0,
    0x47,
    0x03,
    0x70,
    0x9D,
    0x5C,
    0x02,
    0x53,
    0x9F,
    0xAD,
    0x4F,
    0xF2,
    0x94,
    0x78,
    0x74,
    0x36,
    0x5F,
    0xF1,
    0xDB,
    0xF4,
    0x37,
    0xCF,
    0xFC,
    0xB7,
    0x4A,
    0xCD,
    0xA3,
    0xAB,
    0x3F,
    0xD7,
};

unsigned char std_aes256_ccm_L3_cipher[201] = {
    0x58,
    0xCF,
    0x26,
    0xE1,
    0xD9,
    0x59,
    0x88,
    0xFF,
    0x6E,
    0xC3,
    0x54,
    0x21,
    0x78,
    0x87,
    0x45,
    0xE0,
    0xBD,
    0x0D,
    0x11,
    0x3E,
    0x93,
    0x99,
    0x57,
    0x12,
    0x58,
    0x0F,
    0x85,
    0xDC,
    0xC7,
    0x6A,
    0x2A,
    0x6E,
    0xAE,
    0x70,
    0x8F,
    0x9C,
    0x89,
    0xB1,
    0x4A,
    0xDA,
    0x2A,
    0x95,
    0x85,
    0xE7,
    0x67,
    0x4D,
    0x4E,
    0x24,
    0xAB,
    0x97,
    0x7D,
    0xCC,
    0x99,
    0x9E,
    0xB3,
    0x39,
    0x33,
    0xFA,
    0x99,
    0x11,
    0x40,
    0x6A,
    0x7D,
    0xA8,
    0x20,
    0x05,
    0xB6,
    0xCD,
    0x26,
    0x50,
    0xE4,
    0xE4,
    0xF8,
    0x41,
    0x50,
    0xDE,
    0x3D,
    0x0E,
    0x4E,
    0x4F,
    0x03,
    0xC2,
    0xD5,
    0x72,
    0xB5,
    0x0D,
    0x27,
    0x56,
    0xAD,
    0xEA,
    0x41,
    0x00,
    0x5C,
    0xED,
    0xBF,
    0xC4,
    0xBC,
    0xAD,
    0x32,
    0x38,
    0x1E,
    0x06,
    0xEB,
    0xE7,
    0xED,
    0x52,
    0x04,
    0x24,
    0x9C,
    0x5E,
    0xBF,
    0x5A,
    0xF9,
    0x93,
    0xEA,
    0xB5,
    0x8B,
    0x17,
    0x05,
    0xEF,
    0x98,
    0x80,
    0xF3,
    0x7B,
    0x2B,
    0x57,
    0xD8,
    0xB3,
    0x44,
    0x9F,
    0x07,
    0x2F,
    0xAF,
    0x1B,
    0xC1,
    0xEC,
    0x1A,
    0x26,
    0x6B,
    0x4F,
    0x23,
    0x64,
    0x05,
    0xAE,
    0xA9,
    0x85,
    0x10,
    0x42,
    0x1A,
    0x88,
    0xBA,
    0x67,
    0x4F,
    0x31,
    0xFC,
    0xB5,
    0x9D,
    0x3C,
    0x39,
    0x4D,
    0x29,
    0x46,
    0x53,
    0x1B,
    0xBC,
    0x25,
    0x2B,
    0xEA,
    0x0A,
    0x1E,
    0x14,
    0x9F,
    0x83,
    0x40,
    0xFD,
    0xDD,
    0xF3,
    0x57,
    0x68,
    0x32,
    0x32,
    0x8E,
    0xA9,
    0xD0,
    0x53,
    0x01,
    0xD3,
    0xFA,
    0x08,
    0x89,
    0xE4,
    0x65,
    0x76,
    0x4B,
    0x98,
    0x8E,
    0xA3,
    0xED,
    0x91,
    0x0B,
    0xF9,
};

unsigned char std_aes256_ccm_L4_cipher[120] = {
    0x69,
    0x08,
    0x23,
    0x77,
    0x5B,
    0x69,
    0x58,
    0xAC,
    0x2D,
    0xA6,
    0x1A,
    0xB1,
    0x5C,
    0xE6,
    0x11,
    0x6A,
    0x5D,
    0x03,
    0xB7,
    0xDC,
    0x43,
    0xA4,
    0x98,
    0xC3,
    0x86,
    0x96,
    0xBB,
    0x9C,
    0xE7,
    0x4A,
    0x2B,
    0x48,
    0x0F,
    0xF4,
    0x11,
    0x4C,
    0xA3,
    0x76,
    0x41,
    0x65,
    0x8F,
    0x38,
    0xF5,
    0x58,
    0x69,
    0xE5,
    0x83,
    0xCA,
    0x2D,
    0x56,
    0x39,
    0xD2,
    0x9C,
    0x89,
    0x89,
    0xDD,
    0xB8,
    0xDD,
    0x64,
    0x44,
    0x6F,
    0xDE,
    0xF8,
    0x5B,
    0x51,
    0x72,
    0x8A,
    0x0A,
    0xAA,
    0x1A,
    0xCC,
    0x92,
    0x0F,
    0x59,
    0xDF,
    0x9A,
    0x0E,
    0x87,
    0xEF,
    0x21,
    0x94,
    0x7F,
    0x84,
    0x5A,
    0x98,
    0xC6,
    0x2D,
    0x1B,
    0xE3,
    0xC9,
    0xBA,
    0xA7,
    0x73,
    0x5C,
    0xF3,
    0x12,
    0x28,
    0x4B,
    0xF4,
    0x17,
    0xDC,
    0x29,
    0xED,
    0x3B,
    0x4D,
    0x46,
    0xA6,
    0xDD,
    0x9A,
    0xBD,
    0x7F,
    0x12,
    0x50,
    0xAD,
    0x22,
    0xB9,
    0x66,
    0x13,
    0xD8,
    0x39,
};

unsigned char std_aes256_ccm_L5_cipher[65] = {
    0xF5,
    0xCA,
    0x16,
    0x09,
    0x79,
    0x5E,
    0x7F,
    0x62,
    0x60,
    0x73,
    0x4C,
    0x40,
    0x06,
    0x77,
    0x6E,
    0xDF,
    0xC7,
    0x69,
    0x03,
    0x88,
    0x46,
    0x68,
    0x88,
    0x47,
    0xAF,
    0xD3,
    0x43,
    0xC7,
    0x69,
    0x1B,
    0x1E,
    0xC1,
    0x8E,
    0xAE,
    0xCA,
    0xA7,
    0x06,
    0xD8,
    0xAA,
    0xED,
    0x10,
    0xB3,
    0xE4,
    0xBF,
    0x4A,
    0x72,
    0x87,
    0x1C,
    0xBA,
    0x21,
    0x92,
    0x37,
    0x09,
    0xB9,
    0x8B,
    0xC2,
    0x05,
    0x0F,
    0x34,
    0xA4,
    0xD6,
    0x28,
    0xC5,
    0x3D,
    0xF3,
};

unsigned char std_aes256_ccm_L6_cipher[32] = {
    0xFD,
    0xDD,
    0xF0,
    0x27,
    0x43,
    0x87,
    0xF8,
    0xA1,
    0x20,
    0xE2,
    0x30,
    0xF0,
    0xD3,
    0x68,
    0xCB,
    0xF9,
    0x1F,
    0xF8,
    0x49,
    0x89,
    0xE9,
    0x61,
    0xDB,
    0x85,
    0xBE,
    0x91,
    0x19,
    0xEC,
    0x11,
    0xB1,
    0x6D,
    0x18,
};

unsigned char std_aes256_ccm_L7_cipher[15] = {
    0xC8,
    0xF0,
    0xAB,
    0xC4,
    0x32,
    0x79,
    0xF4,
    0x41,
    0xA1,
    0x3B,
    0x81,
    0x51,
    0x23,
    0xD1,
    0x97,
};

unsigned int aes_256_ccm_test(void)
{
    SKE_CCM_TEST_VECTOR vector[8] = {
        {SKE_ALG_AES_256, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 0,  std_aes256_ccm_L2_cipher, std_aes256_ccm_mac_M16_L2_aad0_p256 },
        {SKE_ALG_AES_256, std_ccm_plain, 201, std_ccm_key, 0, std_ccm_nonce, 14, 3, std_ccm_aad, 3,  std_aes256_ccm_L3_cipher, std_aes256_ccm_mac_M14_L3_aad3_p201 },
        {SKE_ALG_AES_256, std_ccm_plain, 120, std_ccm_key, 0, std_ccm_nonce, 12, 4, std_ccm_aad, 15, std_aes256_ccm_L4_cipher, std_aes256_ccm_mac_M12_L4_aad15_p120},
        {SKE_ALG_AES_256, std_ccm_plain, 65,  std_ccm_key, 0, std_ccm_nonce, 10, 5, std_ccm_aad, 16, std_aes256_ccm_L5_cipher, std_aes256_ccm_mac_M10_L5_aad16_p65 },
        {SKE_ALG_AES_256, std_ccm_plain, 32,  std_ccm_key, 0, std_ccm_nonce, 8,  6, std_ccm_aad, 17, std_aes256_ccm_L6_cipher, std_aes256_ccm_mac_M8_L6_aad17_p32  },
        {SKE_ALG_AES_256, std_ccm_plain, 15,  std_ccm_key, 0, std_ccm_nonce, 6,  7, std_ccm_aad, 32, std_aes256_ccm_L7_cipher, std_aes256_ccm_mac_M6_L7_aad32_p15  },
        {SKE_ALG_AES_256, std_ccm_plain, 0,   std_ccm_key, 0, std_ccm_nonce, 4,  8, std_ccm_aad, 33, NULL,                     std_aes256_ccm_mac_M4_L8_aad33_p0   },
        {SKE_ALG_AES_256, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 65, std_aes256_ccm_L2_cipher, std_aes256_ccm_mac_M16_L2_aad65_p256},
    };

    return ske_ccm_test_internal(vector, 8);
}
    #endif


    #ifdef SUPPORT_SKE_SM4
unsigned char std_sm4_ccm_mac_M16_L2_aad0_p256[]  = {0x11, 0xDE, 0xC4, 0xDD, 0xB4, 0x4B, 0x3E, 0xEC, 0x67, 0xBB, 0x9F, 0x68, 0x0E, 0x67, 0x3F, 0x68};
unsigned char std_sm4_ccm_mac_M14_L3_aad3_p201[]  = {0x22, 0xAB, 0x10, 0xA7, 0x35, 0x96, 0x32, 0xE5, 0x69, 0xA5, 0x01, 0xCA, 0x71, 0x0C};
unsigned char std_sm4_ccm_mac_M12_L4_aad15_p120[] = {0x3F, 0xDF, 0x2B, 0x89, 0xB1, 0xC7, 0x9C, 0xC3, 0x25, 0x49, 0x47, 0x09};
unsigned char std_sm4_ccm_mac_M10_L5_aad16_p65[]  = {0x96, 0x84, 0x8A, 0x88, 0xF5, 0x68, 0x06, 0x99, 0x9E, 0xCD};
unsigned char std_sm4_ccm_mac_M8_L6_aad17_p32[]   = {0x91, 0xE2, 0x0B, 0x03, 0xFD, 0x87, 0xB4, 0x32};
unsigned char std_sm4_ccm_mac_M6_L7_aad32_p15[]   = {
    0x49,
    0xBE,
    0x2F,
    0xD6,
    0x3B,
    0x4F,
};
unsigned char std_sm4_ccm_mac_M4_L8_aad33_p0[]    = {0xB6, 0xD6, 0xD2, 0xD9};
unsigned char std_sm4_ccm_mac_M16_L2_aad65_p256[] = {0xD5, 0x8F, 0xDC, 0x6B, 0xAD, 0xEF, 0x8A, 0xDC, 0x9A, 0x5A, 0x34, 0x37, 0x93, 0xAD, 0xBF, 0xDA};

unsigned char std_sm4_ccm_L2_cipher[256] = {
    0xBA,
    0x5C,
    0x58,
    0xCB,
    0xE2,
    0xD2,
    0x3E,
    0x5D,
    0x99,
    0x30,
    0x0D,
    0x9A,
    0x20,
    0x27,
    0xAB,
    0x42,
    0x90,
    0xF0,
    0xD6,
    0x14,
    0xF1,
    0xDC,
    0x90,
    0x58,
    0xBC,
    0x0A,
    0x3E,
    0x94,
    0xBE,
    0x99,
    0xE8,
    0x6E,
    0x99,
    0x55,
    0x95,
    0x2B,
    0x2B,
    0x6B,
    0x96,
    0xA1,
    0xAB,
    0x43,
    0x1E,
    0xC2,
    0x9B,
    0xA5,
    0x40,
    0x67,
    0xC7,
    0x27,
    0xD8,
    0x83,
    0x58,
    0xEB,
    0x92,
    0x14,
    0x4A,
    0x13,
    0x5B,
    0xD7,
    0x55,
    0x00,
    0xEE,
    0xCA,
    0x45,
    0xFC,
    0xBF,
    0x1B,
    0xBC,
    0xB7,
    0x52,
    0xB7,
    0xED,
    0xFB,
    0x80,
    0x7D,
    0xB6,
    0xB8,
    0xB4,
    0x37,
    0xF8,
    0x1D,
    0x82,
    0x80,
    0xC7,
    0x39,
    0xBA,
    0x4D,
    0x83,
    0x53,
    0x9C,
    0x0E,
    0xA8,
    0xA8,
    0xB5,
    0xD4,
    0x4A,
    0x4F,
    0xDA,
    0x66,
    0xF7,
    0xF3,
    0xA3,
    0x66,
    0x7B,
    0xA9,
    0x02,
    0x88,
    0xA2,
    0xD7,
    0xDD,
    0xDB,
    0xC8,
    0xF3,
    0x5D,
    0x39,
    0x63,
    0x07,
    0xA8,
    0x2C,
    0x54,
    0xE1,
    0x9D,
    0xC7,
    0xE4,
    0x31,
    0x94,
    0x08,
    0x20,
    0x95,
    0x8C,
    0x88,
    0xD9,
    0x1F,
    0xA8,
    0xF3,
    0x5D,
    0xE0,
    0xBA,
    0xDB,
    0xBC,
    0x0D,
    0x92,
    0x68,
    0xAC,
    0xAE,
    0xE8,
    0xB9,
    0xCF,
    0x7A,
    0x43,
    0x03,
    0xEF,
    0xE8,
    0x2C,
    0x9F,
    0xD3,
    0x2F,
    0xFA,
    0xDF,
    0x49,
    0x70,
    0xEF,
    0xA2,
    0x91,
    0x65,
    0x9B,
    0x99,
    0x62,
    0x08,
    0x25,
    0x89,
    0x3D,
    0xD6,
    0x33,
    0xA1,
    0x81,
    0x2A,
    0x4F,
    0x0A,
    0x23,
    0xB1,
    0x3C,
    0x98,
    0x1C,
    0x21,
    0x41,
    0xAF,
    0x2C,
    0xF0,
    0x89,
    0xDB,
    0x14,
    0xD5,
    0xCE,
    0x5A,
    0x9E,
    0x77,
    0xBD,
    0xA4,
    0xED,
    0xE2,
    0x0E,
    0xE2,
    0x92,
    0xEC,
    0xC6,
    0xEB,
    0x04,
    0xA1,
    0x72,
    0x9E,
    0x83,
    0xDB,
    0x8C,
    0x88,
    0xAD,
    0x22,
    0xC5,
    0x18,
    0x36,
    0x41,
    0x04,
    0x86,
    0x6E,
    0x37,
    0x09,
    0xFA,
    0x6F,
    0xDE,
    0x84,
    0xBB,
    0xA4,
    0xB3,
    0xD8,
    0xF9,
    0xB3,
    0x4C,
    0x91,
    0x61,
    0xE2,
    0xC5,
    0x0F,
    0x70,
    0x80,
    0xD7,
    0x8B,
    0x52,
    0x31,
    0xEB,
    0x23,
    0x6D,
    0x75,
    0x9B,
    0x84,
    0x7F,
};

unsigned char std_sm4_ccm_L3_cipher[201] = {
    0x37,
    0xDA,
    0x7B,
    0x2D,
    0xF1,
    0xC0,
    0x27,
    0x1B,
    0xAB,
    0x52,
    0xB1,
    0xCC,
    0x72,
    0x57,
    0x85,
    0xA5,
    0xA9,
    0xC4,
    0x4D,
    0xE9,
    0x74,
    0x2E,
    0x67,
    0xE0,
    0x81,
    0xBA,
    0xEF,
    0x5E,
    0x1B,
    0x8B,
    0x94,
    0x07,
    0x3B,
    0x48,
    0x89,
    0x4D,
    0xFE,
    0x63,
    0x35,
    0xF9,
    0xDE,
    0x7B,
    0xC8,
    0x1B,
    0x84,
    0x27,
    0x32,
    0xFF,
    0x8F,
    0xB4,
    0x74,
    0xFA,
    0x43,
    0x95,
    0x02,
    0x74,
    0x15,
    0x70,
    0xC3,
    0x6B,
    0xC1,
    0x3F,
    0x7E,
    0x67,
    0xA1,
    0xDC,
    0xC7,
    0x89,
    0xE5,
    0x22,
    0xE8,
    0x01,
    0xA6,
    0x1F,
    0xD2,
    0xF4,
    0x6F,
    0x65,
    0xAE,
    0x4F,
    0x28,
    0x08,
    0x2D,
    0x5F,
    0x39,
    0xE6,
    0x43,
    0xD2,
    0x0B,
    0xEE,
    0xEF,
    0x18,
    0x98,
    0xBF,
    0xE1,
    0x12,
    0x16,
    0xA0,
    0x36,
    0xCF,
    0x28,
    0x1A,
    0x67,
    0x2E,
    0x3C,
    0xFD,
    0x5F,
    0x21,
    0xC1,
    0x4A,
    0xF4,
    0x41,
    0x24,
    0xB5,
    0x11,
    0xE8,
    0xB4,
    0x20,
    0x15,
    0x51,
    0x49,
    0x14,
    0x8D,
    0xB8,
    0xFD,
    0x63,
    0x8C,
    0x78,
    0xE3,
    0xFE,
    0x16,
    0xBC,
    0x38,
    0xBD,
    0xE6,
    0xCE,
    0xB4,
    0x9D,
    0x45,
    0x13,
    0x35,
    0x13,
    0x08,
    0xED,
    0xC8,
    0x57,
    0xDD,
    0xC9,
    0x81,
    0x0C,
    0x71,
    0x90,
    0x05,
    0x96,
    0x52,
    0xEF,
    0x39,
    0xB9,
    0xF0,
    0xDD,
    0xCE,
    0x24,
    0x2D,
    0xEC,
    0x20,
    0x83,
    0xAF,
    0x77,
    0x5B,
    0x17,
    0x1B,
    0xFB,
    0x3F,
    0xC4,
    0x44,
    0x27,
    0xBA,
    0x02,
    0x2E,
    0x0C,
    0xAA,
    0x6E,
    0x5C,
    0xC9,
    0x1C,
    0xC1,
    0xFC,
    0x23,
    0xFE,
    0xFF,
    0x39,
    0x94,
    0x45,
    0xAB,
    0x2D,
    0x58,
    0x41,
    0xA5,
    0x4A,
    0xC4,
    0x9B,
};

unsigned char std_sm4_ccm_L4_cipher[120] = {
    0x7A,
    0x88,
    0xBD,
    0xD9,
    0x3E,
    0x62,
    0xAE,
    0x71,
    0x65,
    0x29,
    0x06,
    0x9B,
    0x74,
    0x23,
    0x71,
    0x7B,
    0xAA,
    0xEA,
    0xC4,
    0x86,
    0xAA,
    0xAE,
    0x5C,
    0x45,
    0xDE,
    0xA3,
    0x73,
    0x92,
    0xF7,
    0x8C,
    0xA0,
    0x63,
    0x27,
    0xF8,
    0xF7,
    0x76,
    0x52,
    0xC9,
    0x83,
    0xE4,
    0xE9,
    0xE0,
    0xE1,
    0x95,
    0x9F,
    0xF2,
    0x4C,
    0x3C,
    0x90,
    0xF3,
    0xDE,
    0xF9,
    0x81,
    0x6E,
    0x9D,
    0x51,
    0x52,
    0xE5,
    0x60,
    0x5A,
    0x64,
    0x31,
    0x7F,
    0xB5,
    0x8A,
    0x5A,
    0xA0,
    0x32,
    0x46,
    0xB8,
    0xE1,
    0x1E,
    0xCD,
    0xDF,
    0xB8,
    0xC4,
    0x5D,
    0xE6,
    0xBE,
    0x6F,
    0xF7,
    0x2A,
    0x1E,
    0x1E,
    0xF3,
    0x88,
    0x10,
    0xCA,
    0x24,
    0x03,
    0x61,
    0x6E,
    0xFD,
    0xD9,
    0xEE,
    0x58,
    0x64,
    0x77,
    0x4F,
    0x90,
    0x70,
    0x66,
    0xB8,
    0x76,
    0xD7,
    0xB5,
    0x97,
    0x84,
    0xA7,
    0x43,
    0xE5,
    0x8E,
    0xA3,
    0xA3,
    0xD9,
    0xB5,
    0xBC,
    0x82,
    0x24,
    0xB9,
};

unsigned char std_sm4_ccm_L5_cipher[65] = {
    0x99,
    0xB9,
    0x71,
    0xD0,
    0x16,
    0x87,
    0xE3,
    0x87,
    0xDD,
    0xD5,
    0x08,
    0xC8,
    0xCD,
    0x2F,
    0xA1,
    0xBB,
    0x0A,
    0xD5,
    0x52,
    0xD1,
    0xFA,
    0x19,
    0xAE,
    0x31,
    0x46,
    0x2B,
    0xD0,
    0xAA,
    0x48,
    0x35,
    0xC3,
    0x4D,
    0xFF,
    0x45,
    0x1D,
    0xE9,
    0xB4,
    0x19,
    0x0D,
    0x14,
    0xB9,
    0x74,
    0x84,
    0x61,
    0x87,
    0x30,
    0x05,
    0x8A,
    0xCC,
    0x85,
    0x61,
    0x47,
    0xA0,
    0x52,
    0x17,
    0xB3,
    0xAE,
    0x16,
    0x55,
    0xC1,
    0xF4,
    0x28,
    0x42,
    0x15,
    0xF3,
};

unsigned char std_sm4_ccm_L6_cipher[32] = {
    0xCB,
    0xF3,
    0xC2,
    0x5F,
    0x4C,
    0x3B,
    0x4B,
    0x93,
    0x06,
    0x87,
    0x10,
    0x9D,
    0x5C,
    0x89,
    0xA5,
    0x2E,
    0xDC,
    0x91,
    0xDE,
    0x90,
    0xCC,
    0xD2,
    0x14,
    0x95,
    0xF2,
    0x7C,
    0x63,
    0xAF,
    0xE9,
    0xB8,
    0x47,
    0x38,
};

unsigned char std_sm4_ccm_L7_cipher[15] = {
    0x5B,
    0x0D,
    0x74,
    0xBF,
    0x33,
    0x25,
    0xD8,
    0xF3,
    0x99,
    0x3D,
    0x6B,
    0x1E,
    0x04,
    0x2C,
    0x3C,
};

unsigned int sm4_ccm_test(void)
{
    SKE_CCM_TEST_VECTOR vector[8] = {
        {SKE_ALG_SM4, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 0,  std_sm4_ccm_L2_cipher, std_sm4_ccm_mac_M16_L2_aad0_p256 },
        {SKE_ALG_SM4, std_ccm_plain, 201, std_ccm_key, 0, std_ccm_nonce, 14, 3, std_ccm_aad, 3,  std_sm4_ccm_L3_cipher, std_sm4_ccm_mac_M14_L3_aad3_p201 },
        {SKE_ALG_SM4, std_ccm_plain, 120, std_ccm_key, 0, std_ccm_nonce, 12, 4, std_ccm_aad, 15, std_sm4_ccm_L4_cipher, std_sm4_ccm_mac_M12_L4_aad15_p120},
        {SKE_ALG_SM4, std_ccm_plain, 65,  std_ccm_key, 0, std_ccm_nonce, 10, 5, std_ccm_aad, 16, std_sm4_ccm_L5_cipher, std_sm4_ccm_mac_M10_L5_aad16_p65 },
        {SKE_ALG_SM4, std_ccm_plain, 32,  std_ccm_key, 0, std_ccm_nonce, 8,  6, std_ccm_aad, 17, std_sm4_ccm_L6_cipher, std_sm4_ccm_mac_M8_L6_aad17_p32  },
        {SKE_ALG_SM4, std_ccm_plain, 15,  std_ccm_key, 0, std_ccm_nonce, 6,  7, std_ccm_aad, 32, std_sm4_ccm_L7_cipher, std_sm4_ccm_mac_M6_L7_aad32_p15  },
        {SKE_ALG_SM4, std_ccm_plain, 0,   std_ccm_key, 0, std_ccm_nonce, 4,  8, std_ccm_aad, 33, NULL,                  std_sm4_ccm_mac_M4_L8_aad33_p0   },
        {SKE_ALG_SM4, std_ccm_plain, 256, std_ccm_key, 0, std_ccm_nonce, 16, 2, std_ccm_aad, 65, std_sm4_ccm_L2_cipher, std_sm4_ccm_mac_M16_L2_aad65_p256},
    };

    return ske_ccm_test_internal(vector, 8);
}
    #endif


//*
unsigned int ske_ccm_speed_test_internal(SKE_ALG alg, SKE_CRYPTO crypto, char *info)
{
    unsigned char in[4096];
    unsigned char out[4096];
    unsigned char key[32];
    unsigned char aad[100];
    unsigned char nonce[16];
    unsigned char mac[16];
    unsigned char M         = 8;
    unsigned char L         = 6;
    unsigned int  aad_bytes = 100;
    unsigned int  c_bytes   = 4096;
    unsigned int  i;
    unsigned int  round = 100;
    unsigned int  ret;

    uint32_sleep(0xFFFF, 1);

    round = speed_get_round_by_alg(alg);

    #ifndef CCM_SPEED_TEST_BY_TIMER
    round *= 50;
    #endif

    if (SKE_CRYPTO_DECRYPT == crypto) {
        ret = ske_lp_ccm_crypto(alg, SKE_CRYPTO_ENCRYPT, key, 0, nonce, M, L, aad, aad_bytes, in, out, c_bytes, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n dma ccm crypto error 1, ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    memset_(in, 0, c_bytes);

    printf("\r\n %s begin", info);
    fflush(stdout);

    #ifdef CCM_SPEED_TEST_BY_TIMER
    startP();
    #endif

    for (i = 0; i < round; i++) {
        ret = ske_lp_ccm_crypto(alg, crypto, key, 0, nonce, M, L, aad, aad_bytes, out, in, c_bytes, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n dma ccm crypto error 2, ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    #ifdef CCM_SPEED_TEST_BY_TIMER
    endP(0, c_bytes, round);
    #else
    printf("\r\n finished");
    fflush(stdout);
    #endif

    return 0;
}

unsigned int ske_ccm_speed_test(void)
{
    ske_ccm_speed_test_internal(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_128 CCM ENC");
    ske_ccm_speed_test_internal(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_128 CCM DEC");
#if defined(SUPPORT_SKE_AES_192)
    ske_ccm_speed_test_internal(SKE_ALG_AES_192, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_192 CCM ENC");
    ske_ccm_speed_test_internal(SKE_ALG_AES_192, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_192 CCM DEC");
#endif
#if defined(SUPPORT_SKE_AES_256)
    ske_ccm_speed_test_internal(SKE_ALG_AES_256, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_256 CCM ENC");
    ske_ccm_speed_test_internal(SKE_ALG_AES_256, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_256 CCM DEC");
#endif
    #if defined(MCU_CORE_TL721X)
    ske_ccm_speed_test_internal(SKE_ALG_SM4, SKE_CRYPTO_ENCRYPT, "SKE_ALG_SM4 CCM ENC");
    ske_ccm_speed_test_internal(SKE_ALG_SM4, SKE_CRYPTO_DECRYPT, "SKE_ALG_SM4 CCM DEC");
    #endif
    return 0;
}


    #ifdef SKE_LP_DMA_FUNCTION
unsigned int ske_dma_ccm_speed_test_internal(SKE_ALG alg, SKE_CRYPTO crypto, char *info)
{
    unsigned int *in = (unsigned int *)DMA_RAM_BASE;
    unsigned char key[32];
    unsigned char nonce[16];
    unsigned char M         = 8;
    unsigned char L         = 6;
    unsigned int  aad_bytes = 100;
    unsigned int  c_bytes   = 4096;
    unsigned int  i;
    unsigned int  round = 100;
    unsigned int  ret;

    uint32_sleep(0xFFFF, 1);

    round = speed_get_round_by_alg(alg);

        #ifndef CCM_SPEED_TEST_BY_TIMER
    round *= 100;
        #endif

    printf("\r\n %s begin", info);
    fflush(stdout);

        #ifdef CCM_SPEED_TEST_BY_TIMER
    startP();
        #endif

    for (i = 0; i < round; i++) {
        ret = ske_lp_dma_ccm_crypto(alg, crypto, key, 0, nonce, M, L, aad_bytes, in, in, c_bytes, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n dma ccm crypto error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

        #ifdef CCM_SPEED_TEST_BY_TIMER
    endP(0, c_bytes, round);
        #else
    printf("\r\n finished");
    fflush(stdout);
        #endif

    return 0;
}

unsigned int ske_dma_ccm_speed_test(void)
{
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_128 CCM ENC DMA");
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_128 CCM DEC DMA");
#if defined(SUPPORT_SKE_AES_192)
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_192, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_192 CCM ENC DMA");
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_192, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_192 CCM DEC DMA");
#endif
#if defined(SUPPORT_SKE_AES_256)
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_256, SKE_CRYPTO_ENCRYPT, "SKE_ALG_AES_256 CCM ENC DMA");
    ske_dma_ccm_speed_test_internal(SKE_ALG_AES_256, SKE_CRYPTO_DECRYPT, "SKE_ALG_AES_256 CCM DEC DMA");
#endif
        #if defined(MCU_CORE_TL721X)
    ske_dma_ccm_speed_test_internal(SKE_ALG_SM4, SKE_CRYPTO_ENCRYPT, "SKE_ALG_SM4 CCM ENC DMA");
    ske_dma_ccm_speed_test_internal(SKE_ALG_SM4, SKE_CRYPTO_DECRYPT, "SKE_ALG_SM4 CCM DEC DMA");
        #endif
    return 0;
}
    #endif
//*/


unsigned int SKE_LP_CCM_all_Test(void)
{
    unsigned int ret;

    #if 0
    if(SKE_SUCCESS != ske_ccm_speed_test())
        return 1;
    #endif

    #ifdef SKE_LP_DMA_FUNCTION
        #if 0
    if(SKE_SUCCESS != ske_dma_ccm_speed_test())
        return 1;
        #endif
    #endif

    //*
    #ifdef SUPPORT_SKE_AES_128
    ret = aes_128_ccm_test();
    if (ret) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_SKE_AES_192
    ret = aes_192_ccm_test();
    if (ret) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_SKE_AES_256
    ret = aes_256_ccm_test();
    if (ret) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_SKE_SM4
    ret = sm4_ccm_test();
    if (ret) {
        return 1;
    }
    #endif
    //*/

    return 0;
}

#endif

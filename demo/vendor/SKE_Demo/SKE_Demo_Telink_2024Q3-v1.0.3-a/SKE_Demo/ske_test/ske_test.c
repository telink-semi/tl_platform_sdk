/********************************************************************************************************
 * @file    ske_test.c
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
#include "../ske_test/app_test.h"


//#define SKE_SPEED_TEST_BY_TIMER

#ifdef SKE_SPEED_TEST_BY_TIMER
extern unsigned int startP();
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif

void get_rand_(unsigned char *rand, unsigned int bytes)
{
#if 0
    memset_(rand, 0x43, bytes);
#else
    get_rand(rand, bytes);
#endif
}

//#define SKE_SEC_API


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

//callback function
void ske_call_manage(void)
{
    ;
}

unsigned int SKE_test(SKE_ALG ske_alg, SKE_MODE mode, unsigned char wordAlign, unsigned char *std_plain, unsigned int byteLen, unsigned char *key, unsigned short key_id, unsigned char *iv, unsigned char *std_cipher)
{
    unsigned int   i, j;
    unsigned char  key_buf[64 + 4];
    unsigned char  iv_buf[16 + 4];
    unsigned char  std_plain_buf[128 + 4];
    unsigned char  std_cipher_buf[128 + 4];
    unsigned char  cipher_buf[128 + 4];
    unsigned char  replain_buf[128 + 4];
    unsigned char *cipher_, *replain_, *std_plain_, *std_cipher_, *key_, *iv_;
    int8_t         ret;

    char        *name[]      = {"DES", "TDES_128", "TDES_192", "TDES_EEE_128", "TDES_EEE_192", "AES_128", "AES_192", "AES_256", "SM4"};
    char        *oper_mode[] = {"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
    unsigned int block_byteLen, key_byteLen;


    //printf("\r\n ============== %s test ============== \r\n", name[ske_alg]);

    key_byteLen   = ske_lp_get_key_byte_len(ske_alg);
    block_byteLen = ske_lp_get_block_byte_len(ske_alg);

#ifdef SUPPORT_SKE_MODE_XTS
    if (SKE_MODE_XTS == mode) {
        key_byteLen *= 2;
    }
#endif

    if (wordAlign) {
        memcpy_(std_plain_buf, (unsigned char *)std_plain, byteLen);
        memcpy_(std_cipher_buf, (unsigned char *)std_cipher, byteLen);
        if (key != NULL) {
            memcpy_(key_buf, (unsigned char *)key, key_byteLen);
        }
        if (SKE_MODE_ECB != mode) {
            memcpy_(iv_buf, (unsigned char *)iv, block_byteLen);
        }

        cipher_     = cipher_buf;
        replain_    = replain_buf;
        std_plain_  = std_plain_buf;
        std_cipher_ = std_cipher_buf;
        if (key != NULL) {
            key_ = key_buf;
        } else {
            key_ = NULL;
        }
        iv_ = iv_buf;
    } else {
        memcpy_(std_plain_buf + 1, (unsigned char *)std_plain, byteLen);
        memcpy_(std_cipher_buf + 1, (unsigned char *)std_cipher, byteLen);
        if (key != NULL) {
            memcpy_(key_buf + 1, (unsigned char *)key, key_byteLen);
        }
        if (SKE_MODE_ECB != mode) {
            memcpy_(iv_buf + 1, (unsigned char *)iv, block_byteLen);
        }

        cipher_     = cipher_buf + 1;
        replain_    = replain_buf + 1;
        std_plain_  = std_plain_buf + 1;
        std_cipher_ = std_cipher_buf + 1;
        if (key != NULL) {
            key_ = key_buf + 1;
        } else {
            key_ = NULL;
        }
        iv_ = iv_buf + 1;
    }


    /**************** test 1: one-time style ******************/
#if 1

    //ENCRYPT
    #ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
    #else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 1 error");
        return 1;
    }

    #ifdef SKE_SEC_API
    ret = ske_sec_update_blocks(std_plain_, cipher_, byteLen);
    #else
    ret = ske_lp_update_blocks(std_plain_, cipher_, byteLen);
    #endif
    if (SKE_SUCCESS != ret) {
        //printf("\r\n ske encrypt 1 error");
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(cipher_, byteLen, "cipher");
        return 1;
    }

    #ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 1 error");
        return 1;
    }
    #endif

    //DECRYPT
    #ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
    #else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 2 error");
        return 1;
    }

    #ifdef SKE_SEC_API
    ret = ske_sec_update_blocks(cipher_, replain_, byteLen);
    #else
    ret = ske_lp_update_blocks(cipher_, replain_, byteLen);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske decrypt 2 error");
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(cipher_, byteLen, "cipher");

        return 1;
    }

    #ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 2 error");
        return 1;
    }
    #endif

#else

    //ENCRYPT
    #ifdef SKE_SEC_API
    ret = ske_sec_crypto(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, (unsigned char *)iv, std_plain_, cipher_, byteLen);
    #else
    ret = ske_lp_crypto(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, (unsigned char *)iv, std_plain_, cipher_, byteLen);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske encrypt 1 error, ret=%08x", ret);
        return 1;
    }

    //DECRYPT
    #ifdef SKE_SEC_API
    ret = ske_sec_crypto(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, (unsigned char *)iv, cipher_, replain_, byteLen);
    #else
    ret = ske_lp_crypto(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, (unsigned char *)iv, cipher_, replain_, byteLen);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske decrypt 1 error, ret=%08x", ret);
        return 1;
    }
#endif

    if (memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n %s %s one time input test failure!!", name[ske_alg], oper_mode[mode]);
        print_buf_U8(std_plain_, byteLen, "std_plain");
        print_buf_U8(std_cipher_, byteLen, "std_cipher");
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(replain_, byteLen, "replain");

        return 1;
    } else {
        printf("\r\n %s %s one time input test success!!", name[ske_alg], oper_mode[mode]);
    } //fflush(stdout);


    /**************** test 2: multiple style(one block every time) ******************/
    memset_(cipher_, 0, byteLen);
    memset_(replain_, 0, byteLen);

    //ENCRYPT
#ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
#else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
#endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 3 error");
        return 1;
    }

    for (i = 0; i < (byteLen / block_byteLen) * block_byteLen; i += block_byteLen) {
#ifdef SKE_SEC_API
        ret = ske_sec_update_blocks(std_plain_ + i, cipher_ + i, block_byteLen);
#else
        ret = ske_lp_update_blocks(std_plain_ + i, cipher_ + i, block_byteLen);
#endif
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske encrypt 3 error");
            return 1;
        }
    }

#ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 3 error");
        return 1;
    }
#endif

    //DECRYPT
#ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
#else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
#endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 4 error");
        return 1;
    }

    for (i = 0; i < byteLen; i += block_byteLen) {
#ifdef SKE_SEC_API
        ret = ske_sec_update_blocks(cipher_ + i, replain_ + i, block_byteLen);
#else
        ret = ske_lp_update_blocks(cipher_ + i, replain_ + i, block_byteLen);
#endif
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske decrypt 4 error");
            return 1;
        }
    }

#ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske final 4 error");
        return 1;
    }
#endif

    if (memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n %s %s multiple input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(replain_, byteLen, "replain");
        return 1;
    } else {
        printf("\r\n %s %s multiple input test success(one block every time)!!", name[ske_alg], oper_mode[mode]);
    }


    /**************** test 3: multiple style(random blocks every time) ******************/
    memset_(cipher_, 0, byteLen);
    memset_(replain_, 0, byteLen);

    //ENCRYPT
#ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
#else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);
#endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 5 error");
        return 1;
    }

    i = 0;
    while (i * block_byteLen < byteLen) {
        j = ske_get_rand_number(byteLen / block_byteLen);
        if (j > byteLen / block_byteLen - i) {
            j = byteLen / block_byteLen - i;
        }

#ifdef SKE_SEC_API
        ret = ske_sec_update_blocks(std_plain_ + i * block_byteLen, cipher_ + i * block_byteLen, j * block_byteLen);
#else
        ret = ske_lp_update_blocks(std_plain_ + i * block_byteLen, cipher_ + i * block_byteLen, j * block_byteLen);
#endif
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske encrypt 5 error");
            return 1;
        }
        i += j;
    }

#ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske close 5 error");
        return 1;
    }
#endif

    //DECRYPT
#ifdef SKE_SEC_API
    ret = ske_sec_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
#else
    ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);
#endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske init 6 error");
        return 1;
    }

    i = 0;
    while (i * block_byteLen < byteLen) {
        j = ske_get_rand_number(byteLen / block_byteLen);
        if (j > byteLen / block_byteLen - i) {
            j = byteLen / block_byteLen - i;
        }

#ifdef SKE_SEC_API
        ret = ske_sec_update_blocks(cipher_ + i * block_byteLen, replain_ + i * block_byteLen, j * block_byteLen);
#else
        ret = ske_lp_update_blocks(cipher_ + i * block_byteLen, replain_ + i * block_byteLen, j * block_byteLen);
#endif
        if (SKE_SUCCESS != ret) {
            //printf("\r\n ske decrypt 6 error");
            return 1;
        }
        i += j;
    }

#ifdef SKE_SEC_API
    ret = ske_sec_final();
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske close 6 error");
        return 1;
    }
#endif

    if (memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
        printf("\r\n %s %s multiple input test failure(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U8(cipher_, byteLen, "cipher");
        print_buf_U8(replain_, byteLen, "replain");

        return 1;
    } else {
        printf("\r\n %s %s multiple input test success(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
    }

    fflush(stdout);

    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
unsigned int SKE_DMA_test(SKE_ALG ske_alg, SKE_MODE mode, unsigned char *std_plain, unsigned int wordLen, unsigned char *key, unsigned short key_id, unsigned char *iv, unsigned char *std_cipher)
{
    unsigned int  i, j;
    unsigned int *std_plain_buf  = (unsigned int *)(DMA_RAM_BASE + 0x100); //std_plain_buf[132];
    unsigned int *std_cipher_buf = std_plain_buf + 0x100;                  //std_cipher_buf[132];
    unsigned int *cipher_buf     = std_cipher_buf + 0x100;                 //cipher_buf[132];
    unsigned int *replain_buf    = cipher_buf + 0x100;                     //replain_buf[132];
    unsigned int *cipher_, *replain_, *std_plain_, *std_cipher_;
    unsigned int  ret;

    char *name[] = {"DES", "TDES_128", "TDES_192", "TDES_EEE_128", "TDES_EEE_192", "AES_128", "AES_192", "AES_256", "SM4"};
    //char *oper_mode[]={"ECB", "CBC", "CFB", "OFB", "CTR"};
    char        *oper_mode[] = {"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
    unsigned int block_wordLen, dma_block_wordLen;
    //mode = 1;

    block_wordLen     = ske_lp_get_block_byte_len(ske_alg) / 4;
    dma_block_wordLen = block_wordLen;

    uint32_copy(std_plain_buf, (unsigned int *)std_plain, wordLen);   //memcpy_(std_plain_buf, std_plain, byteLen);
    uint32_copy(std_cipher_buf, (unsigned int *)std_cipher, wordLen); //memcpy_(std_cipher_buf, std_cipher, byteLen);


    cipher_     = cipher_buf;
    replain_    = replain_buf;
    std_plain_  = std_plain_buf;
    std_cipher_ = std_cipher_buf;

    /**************** test 1: one-time style ******************/
    //ENCRYPT
    #if 0
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key, key_id, iv);//print_buf_U8(key, 16, "key");print_buf_U8(iv, 16, "iv");
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n ske dma int 1 error");
        return 1;
    }

    ret = ske_lp_dma_update_blocks(std_plain_, cipher_, wordLen, ske_call_manage);//print_buf_U32(cipher_, byteLen/4, "cipher");
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n ske dma encrypt 1 error");
        return 1;
    }

    //DECRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key, key_id, iv);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n ske dma int 2 error");
        return 1;
    }

    ret = ske_lp_dma_update_blocks(cipher_, replain_, wordLen, ske_call_manage);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n ske dma decrypt 2 error");
        return 1;
    }
    #else
    //ENCRYPT
    ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (unsigned char *)key, key_id, (unsigned char *)iv, std_plain_, cipher_, wordLen, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma encrypt 1 error");
        return 1;
    }

    //DECRYPT
    ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_DECRYPT, (unsigned char *)key, key_id, (unsigned char *)iv, cipher_, replain_, wordLen, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma decrypt 1 error");
        return 1;
    }
    #endif

    if (uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
        printf("\r\n %s %s one time input test failure!!", name[ske_alg], oper_mode[mode]);
        print_buf_U32(std_plain_, wordLen, "std_plain");
        print_buf_U32(std_cipher_, wordLen, "std_cipher");
        print_buf_U32(cipher_, wordLen, "cipher");
        print_buf_U32(replain_, wordLen, "replain");
        return 1;
    } else {
        printf("\r\n %s %s DMA one time input test success!!", name[ske_alg], oper_mode[mode]);
    }


    /**************** test 2: multiple style(one block every time) ******************/
    uint32_clear(cipher_, wordLen);
    uint32_clear(replain_, wordLen);

    //ENCRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (unsigned char *)key, key_id, (unsigned char *)iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma int 3 error");
        return 1;
    }

    for (i = 0; i < wordLen; i += dma_block_wordLen) {
        ret = ske_lp_dma_update_blocks(std_plain_ + (i), cipher_ + (i), GET_MIN_LEN(dma_block_wordLen, wordLen - i), ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske dma encrypt 3 error");
            return 1;
        }
    }

    //DECRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, (unsigned char *)key, key_id, (unsigned char *)iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma int 4 error");
        return 1;
    }

    for (i = 0; i < wordLen; i += dma_block_wordLen) {
        ret = ske_lp_dma_update_blocks(cipher_ + (i), replain_ + (i), GET_MIN_LEN(dma_block_wordLen, wordLen - i), ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske dma decrypt 4 error");
            return 1;
        }
    }

    if (uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
        printf("\r\n %s %s multiple input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U32(std_plain_, wordLen, "std_plain");
        print_buf_U32(cipher_, wordLen, "cipher");
        print_buf_U32(replain_, wordLen, "replain");
        return 1;
    } else {
        printf("\r\n %s %s DMA multiple input test success(one block every time)!!", name[ske_alg], oper_mode[mode]);
    }


    /**************** test 3: multiple style(random block every time) ******************/
    uint32_clear(cipher_, wordLen);
    uint32_clear(replain_, wordLen);

    //ENCRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (unsigned char *)key, key_id, (unsigned char *)iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma int 5 error");
        return 1;
    }

    i = 0;
    while (i < wordLen) {
        j = ske_get_rand_number(wordLen / dma_block_wordLen) * dma_block_wordLen;
        j = GET_MIN_LEN(j, wordLen - i);

        ret = ske_lp_dma_update_blocks(std_plain_ + (i), cipher_ + (i), j, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske dma encrypt 5 error");
            return 1;
        }

        i += j;
    }

    //DECRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, (unsigned char *)key, key_id, (unsigned char *)iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma int 6 error");
        return 1;
    }

    i = 0;
    while (i < wordLen) {
        j = ske_get_rand_number(wordLen / dma_block_wordLen) * dma_block_wordLen;
        j = GET_MIN_LEN(j, wordLen - i);

        ret = ske_lp_dma_update_blocks(cipher_ + (i), replain_ + (i), j, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n ske dma decrypt 6 error");
            return 1;
        }

        i += j;
    }

    if (uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
        printf("\r\n %s %s multiple input test failure(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U32(cipher_, wordLen, "cipher");
        print_buf_U32(replain_, wordLen, "replain");
        return 1;
    } else {
        printf("\r\n %s %s DMA multiple input test success(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
    }

    fflush(stdout);


    #if defined(SUPPORT_SKE_IRQ)

    ske_lp_request_irq();

    cipher_  = (unsigned int *)(DMA_SKE_BASE);
    replain_ = (unsigned int *)(DMA_SKE_BASE + 2048);

    for (i = 0; i < 256; i++) {
        cipher_[i]  = i;
        replain_[i] = 0;
    }

    //ENCRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key, 0, iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma irq decrypt error");
        return 1;
    }

    ske_lp_dma_update_blocks(cipher_, replain_, 256, ske_call_manage);
    while (SKE_SUCCESS != ske_lp_query_irq()) {
        xil_printf("\r\n %s %s irq  start encrypt multiple !!", name[ske_alg], oper_mode[mode]);
    }


    //DECRYPT
    ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key, 0, iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n ske dma irq decrypt error");
        return 1;
    }
    ske_lp_dma_update_blocks(replain_, cipher_, 256, ske_call_manage);

    while (SKE_SUCCESS != ske_lp_query_irq()) {
        xil_printf("\r\n %s %s irq  start decrypt multiple !!", name[ske_alg], oper_mode[mode]);
    }

    for (i = 0; i < 256; i++) {
        replain_[i] = i;
    }

    if (uint32_BigNumCmp(replain_, 256, cipher_, 256)) {
        xil_printf("\r\n %s %s irq multiple input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U32(cipher_, wordLen, "cipher");
        print_buf_U32(replain_, wordLen, "replain");
        return 1;
    } else {
        xil_printf("\r\n %s %s DMA irq multiple input test success(one block every time)!!", name[ske_alg], oper_mode[mode]);
    }


    // ENCRYPT - DECRYPT
    for (i = 0; i < 256; i++) {
        cipher_[i]  = i;
        replain_[i] = 0;
    }

    ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key, 0, iv, cipher_, replain_, wordLen, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        return 1;
    }
    while (SKE_SUCCESS != ske_lp_query_irq()) {
        xil_printf("\r\n %s %s irq  start encrypt one !!", name[ske_alg], oper_mode[mode]);
    }

    ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_DECRYPT, key, 0, iv, cipher_, replain_, wordLen, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        return 1;
    }
    while (SKE_SUCCESS != ske_lp_query_irq()) {
        xil_printf("\r\n %s %s irq  start decrypt one !!", name[ske_alg], oper_mode[mode]);
    }

    for (i = 0; i < 256; i++) {
        replain_[i] = i;
    }

    if (uint32_BigNumCmp(replain_, 256, cipher_, 256)) {
        xil_printf("\r\n %s %s irq one input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
        print_buf_U32(cipher_, wordLen, "cipher");
        print_buf_U32(replain_, wordLen, "replain");
        return 1;
    } else {
        xil_printf("\r\n %s %s DMA irq one input test success(one block every time)!!", name[ske_alg], oper_mode[mode]);
    }

    ske_lp_free_irq();

    #endif

    return 0;
}
#endif


unsigned char std_in[128] = {
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
};
unsigned char std_key[64] = {
    0xE0,
    0x70,
    0x99,
    0xF1,
    0xBF,
    0xAF,
    0xFD,
    0x7F,
    0x24,
    0x0C,
    0xD7,
    0x90,
    0xCA,
    0x4F,
    0xE1,
    0x34,
    0xB4,
    0x42,
    0x60,
    0xE1,
    0x56,
    0x8D,
    0x9E,
    0x85,
    0x0A,
    0x0C,
    0x95,
    0x37,
    0x44,
    0x02,
    0xDE,
    0x28,
    0xF0,
    0x79,
    0xA5,
    0x85,
    0xEC,
    0x84,
    0x36,
    0x90,
    0xC8,
    0x15,
    0x0A,
    0x31,
    0x47,
    0x24,
    0xE4,
    0x88,
    0x5F,
    0xD0,
    0x3B,
    0x37,
    0x9D,
    0xF7,
    0x0C,
    0x8E,
    0x4C,
    0x4F,
    0x77,
    0x26,
    0x17,
    0x4F,
    0x75,
    0xF7,
};
unsigned char std_iv[16] = {
    0xC7,
    0x2B,
    0x65,
    0x91,
    0xA0,
    0xD7,
    0xDE,
    0x8F,
    0x6B,
    0x40,
    0x72,
    0x33,
    0xAD,
    0x35,
    0x81,
    0xD6};


#ifdef SUPPORT_SKE_SM4
unsigned char std_sm4_ecb_out[128] = {
    0xCC,
    0x62,
    0x37,
    0xA6,
    0xA1,
    0x35,
    0x39,
    0x75,
    0xFF,
    0xF5,
    0xEE,
    0x6A,
    0xFD,
    0xD7,
    0x70,
    0x15,
    0xE1,
    0x32,
    0x23,
    0x1F,
    0x18,
    0xB8,
    0xC9,
    0x16,
    0x07,
    0x27,
    0x9C,
    0x6C,
    0x7F,
    0x8F,
    0x7F,
    0xF6,
    0xFD,
    0xF1,
    0xE4,
    0x01,
    0xEC,
    0x7E,
    0xD2,
    0x60,
    0xFD,
    0xE7,
    0x5C,
    0xE5,
    0xCF,
    0x6E,
    0xE7,
    0x87,
    0x97,
    0x13,
    0xCC,
    0x01,
    0x92,
    0x1A,
    0xC5,
    0x62,
    0xB5,
    0x0C,
    0x45,
    0xE4,
    0xDC,
    0x9A,
    0x30,
    0xC2,
    0x35,
    0xED,
    0x7D,
    0x1A,
    0x93,
    0x0D,
    0x33,
    0x96,
    0xD6,
    0xE1,
    0x8B,
    0x77,
    0x64,
    0x40,
    0x25,
    0x3D,
    0x9F,
    0x4B,
    0x8E,
    0xFF,
    0x3F,
    0x11,
    0x41,
    0x58,
    0x3B,
    0x55,
    0x4F,
    0x59,
    0x38,
    0x2E,
    0xAA,
    0xBB,
    0x8B,
    0x42,
    0xFA,
    0x30,
    0x38,
    0x0D,
    0x05,
    0x3B,
    0x86,
    0x7C,
    0xB0,
    0xF2,
    0x77,
    0xCE,
    0xEE,
    0x1B,
    0x78,
    0xE8,
    0x64,
    0x7D,
    0x59,
    0xE3,
    0xDA,
    0x61,
    0x05,
    0x27,
    0x56,
    0x12,
    0x95,
    0x6D,
    0x34,
    0x9C,
};
unsigned char std_sm4_cbc_out[128] = {
    0x60,
    0x7A,
    0xBE,
    0xC9,
    0xDA,
    0xD7,
    0x90,
    0x73,
    0xC7,
    0x96,
    0xDB,
    0x34,
    0x26,
    0xFD,
    0x2C,
    0x2F,
    0x8E,
    0x39,
    0xC7,
    0x0B,
    0x60,
    0xB2,
    0x3D,
    0xBE,
    0xF3,
    0xA9,
    0xA5,
    0x46,
    0x65,
    0x26,
    0x41,
    0xB7,
    0xAE,
    0xC9,
    0xC3,
    0xAD,
    0x8C,
    0x9B,
    0x95,
    0x8D,
    0x17,
    0x53,
    0x15,
    0x35,
    0x40,
    0x2A,
    0x8C,
    0x6B,
    0x02,
    0x5C,
    0xBD,
    0x13,
    0xA6,
    0x7E,
    0xB7,
    0x63,
    0xC0,
    0x3F,
    0xA8,
    0xBC,
    0x73,
    0xDD,
    0x0B,
    0x7A,
    0x88,
    0x0E,
    0xF8,
    0xC5,
    0x5B,
    0x00,
    0x07,
    0xFF,
    0x53,
    0x7B,
    0xF1,
    0x6A,
    0xA0,
    0xFD,
    0x0B,
    0x89,
    0x03,
    0x91,
    0x4D,
    0xD8,
    0xC4,
    0xB3,
    0xC0,
    0x12,
    0x41,
    0xEB,
    0xF7,
    0xCB,
    0x0A,
    0xFB,
    0x68,
    0xE7,
    0x8E,
    0x0C,
    0x14,
    0x33,
    0x1A,
    0x34,
    0x55,
    0xDA,
    0x04,
    0xE2,
    0xA3,
    0xFC,
    0xBE,
    0xB6,
    0xDF,
    0x2B,
    0x61,
    0x33,
    0x05,
    0xBD,
    0xBC,
    0x0A,
    0xB5,
    0x8B,
    0x6D,
    0x0F,
    0x1B,
    0x7D,
    0x5F,
    0x24,
    0x46,
    0x0E,
};
unsigned char std_sm4_cfb_out[128] = {
    0xC1,
    0x27,
    0x47,
    0xC7,
    0x44,
    0x0C,
    0x9A,
    0x5C,
    0x7D,
    0x51,
    0x26,
    0x0D,
    0x1B,
    0xDB,
    0x0D,
    0x9D,
    0x52,
    0x59,
    0xAD,
    0x56,
    0x05,
    0xBE,
    0x92,
    0xD2,
    0xB7,
    0x62,
    0xF5,
    0xD7,
    0x53,
    0xD3,
    0x12,
    0x2A,
    0x3C,
    0x9A,
    0x6E,
    0x75,
    0x80,
    0xAB,
    0x18,
    0xE5,
    0x72,
    0x49,
    0x9A,
    0xD9,
    0x80,
    0x99,
    0xC2,
    0xE7,
    0xCA,
    0xD9,
    0xDC,
    0xD1,
    0x45,
    0x2F,
    0xDD,
    0xFC,
    0x01,
    0x7F,
    0xB8,
    0x01,
    0x51,
    0xCF,
    0x43,
    0x74,
    0xC0,
    0xBA,
    0xFE,
    0xB0,
    0x28,
    0xFE,
    0xA4,
    0xCD,
    0x35,
    0x0E,
    0xEC,
    0xE5,
    0x70,
    0xA2,
    0x7F,
    0x5D,
    0x38,
    0x1B,
    0x50,
    0xEB,
    0x46,
    0xBE,
    0x61,
    0x6E,
    0x6C,
    0x76,
    0xF3,
    0x65,
    0x75,
    0xCD,
    0xA1,
    0xBB,
    0x9F,
    0xFA,
    0x7B,
    0x86,
    0x12,
    0x87,
    0x04,
    0xEB,
    0x00,
    0x24,
    0x81,
    0xE7,
    0x91,
    0xFC,
    0x1B,
    0xC7,
    0xA6,
    0xB2,
    0x67,
    0xE2,
    0x6E,
    0x88,
    0x8F,
    0xB6,
    0x4C,
    0x45,
    0x96,
    0xEF,
    0xBF,
    0x4C,
    0x26,
    0x69,
};
unsigned char std_sm4_ofb_out[128] = {
    0xC1,
    0x27,
    0x47,
    0xC7,
    0x44,
    0x0C,
    0x9A,
    0x5C,
    0x7D,
    0x51,
    0x26,
    0x0D,
    0x1B,
    0xDB,
    0x0D,
    0x9D,
    0x0F,
    0x0C,
    0xAD,
    0xA0,
    0x2D,
    0x18,
    0x0B,
    0x3C,
    0x54,
    0xA9,
    0x87,
    0x86,
    0xBC,
    0x6B,
    0xF9,
    0xFB,
    0x18,
    0x68,
    0x51,
    0x1E,
    0xB2,
    0x53,
    0x1D,
    0xD5,
    0x7F,
    0x4B,
    0xED,
    0xB8,
    0xCA,
    0x8E,
    0x81,
    0xCE,
    0xE1,
    0x16,
    0x7F,
    0x84,
    0x69,
    0xD1,
    0x15,
    0xCE,
    0x84,
    0xF0,
    0xB0,
    0x3A,
    0x21,
    0xF2,
    0x85,
    0xA2,
    0xEB,
    0x2F,
    0xDF,
    0x34,
    0x52,
    0x62,
    0x42,
    0x87,
    0xFA,
    0x7F,
    0x02,
    0x2A,
    0xC2,
    0xD9,
    0xE4,
    0xB0,
    0x8D,
    0xC5,
    0x52,
    0xEC,
    0x3D,
    0x96,
    0x3F,
    0xD3,
    0x8C,
    0x39,
    0x9C,
    0x0F,
    0xD9,
    0x66,
    0xDD,
    0x29,
    0x90,
    0x00,
    0x5D,
    0x4F,
    0x4D,
    0x82,
    0x2A,
    0x47,
    0x9E,
    0x7E,
    0x46,
    0x87,
    0x84,
    0xE8,
    0xDD,
    0xAE,
    0xB3,
    0x03,
    0xF8,
    0xE8,
    0x7B,
    0xA6,
    0xC9,
    0x9A,
    0x56,
    0x9C,
    0xC7,
    0x82,
    0x1E,
    0x9A,
    0x9D,
    0x13,
};
unsigned char std_sm4_ctr_out[128] = {
    0xC1,
    0x27,
    0x47,
    0xC7,
    0x44,
    0x0C,
    0x9A,
    0x5C,
    0x7D,
    0x51,
    0x26,
    0x0D,
    0x1B,
    0xDB,
    0x0D,
    0x9D,
    0xC3,
    0x75,
    0xCE,
    0xBB,
    0x63,
    0x9A,
    0x5B,
    0x0C,
    0xED,
    0x64,
    0x3F,
    0x33,
    0x80,
    0x8F,
    0x97,
    0x40,
    0xB7,
    0x5C,
    0xA7,
    0xFE,
    0x2F,
    0x7F,
    0xFB,
    0x20,
    0x13,
    0xEC,
    0xDC,
    0xBC,
    0x96,
    0xC8,
    0x05,
    0xF0,
    0xA4,
    0x95,
    0xC4,
    0x0A,
    0xB7,
    0x1B,
    0x18,
    0xB4,
    0xDA,
    0x35,
    0xFF,
    0xA5,
    0xB5,
    0x90,
    0x1B,
    0x07,
    0x5C,
    0x5B,
    0x91,
    0x36,
    0xF0,
    0xC9,
    0xFE,
    0xFB,
    0xC4,
    0x71,
    0xD6,
    0x3B,
    0x03,
    0x28,
    0x62,
    0xB9,
    0x22,
    0x7A,
    0x97,
    0xC9,
    0x54,
    0xC0,
    0x8C,
    0x71,
    0xEC,
    0x8F,
    0xE1,
    0xBB,
    0x56,
    0xAE,
    0xAB,
    0x16,
    0xF6,
    0x57,
    0x76,
    0x65,
    0xC2,
    0x4B,
    0xE0,
    0x46,
    0x4E,
    0x13,
    0x77,
    0x50,
    0x91,
    0x24,
    0x76,
    0xD9,
    0xB7,
    0x16,
    0xFF,
    0x9E,
    0xD0,
    0x2E,
    0x14,
    0x23,
    0x27,
    0xF4,
    0x99,
    0x03,
    0xDA,
    0x1C,
    0x52,
    0x04,
};
unsigned char std_sm4_xts_out[128] = {
    0x94,
    0x83,
    0xE9,
    0x1F,
    0x12,
    0xEE,
    0x81,
    0x81,
    0x1A,
    0x3C,
    0x4C,
    0xAB,
    0xAC,
    0xF4,
    0x01,
    0xA3,
    0x9D,
    0xBC,
    0x35,
    0xC2,
    0xE5,
    0x37,
    0x4D,
    0x69,
    0x73,
    0xDB,
    0x4D,
    0x79,
    0x32,
    0x10,
    0xC4,
    0x27,
    0x2A,
    0x54,
    0x17,
    0xE0,
    0x6D,
    0x86,
    0xCD,
    0xED,
    0xF6,
    0xEC,
    0x86,
    0x8E,
    0xDA,
    0x93,
    0xFE,
    0x67,
    0xBC,
    0xA7,
    0x5B,
    0x94,
    0xB0,
    0x7F,
    0x46,
    0x82,
    0xF6,
    0x80,
    0x91,
    0x48,
    0x09,
    0x25,
    0xF6,
    0xE3,
    0x74,
    0x7D,
    0x11,
    0xC3,
    0xFA,
    0x3B,
    0xBC,
    0x46,
    0x40,
    0xCA,
    0xDB,
    0x1A,
    0xD5,
    0xA7,
    0xAF,
    0xC6,
    0x6A,
    0x9F,
    0xD1,
    0xDD,
    0x0E,
    0xE9,
    0x08,
    0xD4,
    0xBA,
    0x10,
    0x5D,
    0xCE,
    0x43,
    0x2D,
    0x1B,
    0x92,
    0x21,
    0xAC,
    0x0C,
    0x86,
    0x30,
    0x7D,
    0x8D,
    0x47,
    0xB1,
    0xA5,
    0x1C,
    0xB9,
    0xB7,
    0xF2,
    0xC9,
    0xFF,
    0x46,
    0x82,
    0x29,
    0x4F,
    0x2F,
    0x04,
    0xE2,
    0xA5,
    0x4D,
    0x55,
    0x64,
    0x58,
    0xD5,
    0x49,
    0x85,
    0x30,
};

unsigned int SM4_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== SM4  test =================== ");
    fflush(stdout);

    printf("\r\n 1. input&output aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_SM4, SKE_MODE_ECB, 1, std_in, 128, (unsigned char *)std_key, 0, NULL, std_sm4_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_sm4_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_sm4_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_sm4_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_sm4_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_XTS, 1, std_in, 128, std_key, 0, std_iv, std_sm4_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_SM4, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_sm4_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_sm4_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_sm4_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_sm4_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_sm4_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_SM4, SKE_MODE_XTS, 0, std_in, 128, std_key, 0, std_iv, std_sm4_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    #ifdef SKE_LP_DMA_FUNCTION
    printf("\r\n\r\n =================== SM4 DMA test ==================== ");
    fflush(stdout);

        #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL, std_sm4_ecb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_sm4_cbc_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_sm4_cfb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_sm4_ofb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_sm4_ctr_out);
        #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_DMA_test(SKE_ALG_SM4, SKE_MODE_XTS, std_in, 32, std_key, 0, std_iv, std_sm4_xts_out);
    //#endif

    if (ret) {
        return 1;
    }
    #endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_AES_128
unsigned char std_aes_128_ecb_out[128] = {
    0x0B,
    0x54,
    0xE5,
    0x9F,
    0x47,
    0x14,
    0x4F,
    0xD8,
    0xEE,
    0x43,
    0x56,
    0xCA,
    0x0B,
    0x2D,
    0x7A,
    0x4B,
    0x84,
    0xD8,
    0x17,
    0x26,
    0xE2,
    0x8F,
    0x59,
    0xAD,
    0x95,
    0x56,
    0x8C,
    0x52,
    0xDA,
    0x98,
    0x3F,
    0x8D,
    0x65,
    0xED,
    0xDD,
    0x87,
    0x58,
    0x90,
    0xEC,
    0xE7,
    0xD8,
    0x03,
    0x66,
    0x9D,
    0xE2,
    0xF3,
    0x57,
    0x95,
    0xB8,
    0x45,
    0x1F,
    0x2A,
    0xD0,
    0xF2,
    0x75,
    0xC9,
    0xF0,
    0x77,
    0x32,
    0x8A,
    0x60,
    0x0B,
    0x17,
    0x07,
    0x30,
    0x37,
    0x35,
    0xED,
    0xF5,
    0x9F,
    0x42,
    0x77,
    0x39,
    0xF6,
    0x6C,
    0x82,
    0x2E,
    0xFD,
    0x23,
    0x28,
    0x5B,
    0x9E,
    0xD4,
    0xC2,
    0x05,
    0xA5,
    0x08,
    0xCB,
    0xFA,
    0x92,
    0x5E,
    0xAD,
    0x7E,
    0xD9,
    0x5B,
    0xA8,
    0x4A,
    0x9A,
    0x15,
    0x4B,
    0x75,
    0x89,
    0xF6,
    0xA4,
    0x89,
    0xF3,
    0x02,
    0x7A,
    0xF1,
    0x73,
    0xA5,
    0xAD,
    0x0D,
    0xD5,
    0xC5,
    0xD2,
    0x17,
    0xD7,
    0xE0,
    0xF1,
    0x35,
    0x05,
    0x74,
    0xE9,
    0xD1,
    0x86,
    0x66,
    0xE0,
};
unsigned char std_aes_128_cbc_out[128] = {
    0x2C,
    0x1E,
    0xD4,
    0x56,
    0x36,
    0x2E,
    0x00,
    0x85,
    0xA8,
    0x1D,
    0x8E,
    0x61,
    0x69,
    0xAD,
    0x38,
    0xB7,
    0xB4,
    0x42,
    0x60,
    0xE1,
    0x56,
    0x8D,
    0x9E,
    0x85,
    0x0A,
    0x0C,
    0x95,
    0x37,
    0x44,
    0x02,
    0xDE,
    0x28,
    0x24,
    0xD5,
    0x05,
    0x61,
    0x30,
    0x42,
    0x42,
    0x86,
    0x0A,
    0xE7,
    0x17,
    0x3D,
    0xDD,
    0x19,
    0xEC,
    0x5B,
    0x93,
    0xD2,
    0x67,
    0x84,
    0xE3,
    0xED,
    0xA0,
    0x21,
    0x22,
    0x78,
    0x8D,
    0xD6,
    0x28,
    0x64,
    0x60,
    0xAA,
    0xDD,
    0x9D,
    0x7E,
    0xA8,
    0xE2,
    0x79,
    0x68,
    0xBE,
    0x82,
    0xA6,
    0xBC,
    0x9F,
    0x5D,
    0xE8,
    0x4E,
    0xA0,
    0xB7,
    0xAA,
    0xDA,
    0xC7,
    0x91,
    0xA5,
    0x15,
    0xD7,
    0x80,
    0xBC,
    0x24,
    0x6A,
    0x90,
    0xB6,
    0x17,
    0xDF,
    0x10,
    0xD8,
    0x7B,
    0x2D,
    0xA2,
    0x35,
    0xCA,
    0xF7,
    0x56,
    0x1D,
    0xD8,
    0x03,
    0x97,
    0x3C,
    0xDE,
    0xAF,
    0x90,
    0xF7,
    0x1B,
    0x4A,
    0x34,
    0x55,
    0xC9,
    0x16,
    0xEA,
    0xA5,
    0xCE,
    0xF8,
    0x4B,
    0x0B,
    0x10,
    0x8A,
};
unsigned char std_aes_128_cfb_out[128] = {
    0x59,
    0x11,
    0x7E,
    0xFA,
    0xA2,
    0x98,
    0x1E,
    0x95,
    0xC2,
    0xD0,
    0x7A,
    0x3E,
    0xF0,
    0x7F,
    0xD3,
    0x17,
    0x76,
    0xC8,
    0x33,
    0xD5,
    0x80,
    0x43,
    0x6D,
    0x79,
    0x67,
    0x0B,
    0x0A,
    0x22,
    0xE8,
    0x9D,
    0xFE,
    0xDA,
    0x45,
    0x4D,
    0x07,
    0xBB,
    0xE4,
    0x38,
    0x11,
    0x6F,
    0x13,
    0xB8,
    0x32,
    0xDD,
    0xF2,
    0xF5,
    0x4A,
    0x0A,
    0x16,
    0x14,
    0xB2,
    0x3E,
    0xC5,
    0xFF,
    0x1E,
    0xA9,
    0xBD,
    0xA1,
    0xA2,
    0xE5,
    0x21,
    0x3C,
    0x38,
    0xC8,
    0x16,
    0x01,
    0x53,
    0xFC,
    0x9B,
    0x62,
    0xE3,
    0xA4,
    0x5B,
    0xD5,
    0x34,
    0xE6,
    0xFA,
    0xB7,
    0x04,
    0x01,
    0xFD,
    0xE9,
    0x8E,
    0x31,
    0xD0,
    0x68,
    0xF0,
    0x9E,
    0xAF,
    0x56,
    0xBE,
    0x0C,
    0x6D,
    0x37,
    0xC7,
    0xD3,
    0xAE,
    0xBF,
    0xE5,
    0xEE,
    0x03,
    0x3B,
    0xA7,
    0x2D,
    0x76,
    0xAA,
    0x4B,
    0x4B,
    0xF6,
    0xEC,
    0xFB,
    0xC3,
    0x0F,
    0x91,
    0x97,
    0xB8,
    0x36,
    0xD6,
    0x32,
    0x93,
    0xAE,
    0x42,
    0x00,
    0x30,
    0xAC,
    0xB3,
    0xDD,
    0xEF,
};
unsigned char std_aes_128_ofb_out[128] = {
    0x59,
    0x11,
    0x7E,
    0xFA,
    0xA2,
    0x98,
    0x1E,
    0x95,
    0xC2,
    0xD0,
    0x7A,
    0x3E,
    0xF0,
    0x7F,
    0xD3,
    0x17,
    0x91,
    0x5A,
    0x7D,
    0x8B,
    0xB2,
    0x2B,
    0xE8,
    0x1C,
    0xCE,
    0x3F,
    0x06,
    0x17,
    0x38,
    0x06,
    0xA9,
    0x88,
    0x7B,
    0x65,
    0x1B,
    0x79,
    0x15,
    0xEE,
    0x6C,
    0x86,
    0xA6,
    0xC3,
    0x65,
    0xEB,
    0xBC,
    0xE4,
    0x38,
    0x2E,
    0x32,
    0x0E,
    0x05,
    0xA8,
    0xDB,
    0x47,
    0xEC,
    0x2F,
    0xAE,
    0x1D,
    0x26,
    0x99,
    0x89,
    0x08,
    0x6C,
    0xFA,
    0x7E,
    0x4C,
    0xF9,
    0x47,
    0xFC,
    0x8E,
    0x69,
    0xB5,
    0x08,
    0x71,
    0x03,
    0xFF,
    0xEF,
    0xD6,
    0x68,
    0xB0,
    0x0E,
    0x96,
    0x0A,
    0x4B,
    0x23,
    0xE8,
    0x42,
    0x26,
    0x49,
    0xFC,
    0xD6,
    0xA9,
    0xE8,
    0xC1,
    0x6C,
    0xBE,
    0x94,
    0xB9,
    0x5E,
    0x4A,
    0x93,
    0x18,
    0xEB,
    0x88,
    0xB3,
    0x54,
    0x1E,
    0xC9,
    0xB2,
    0x2E,
    0x79,
    0x7D,
    0x69,
    0x82,
    0xE2,
    0x4A,
    0xA7,
    0x11,
    0x43,
    0xEC,
    0xF3,
    0xBE,
    0xE8,
    0x2D,
    0x62,
    0x64,
    0x70,
    0xC2,
};
unsigned char std_aes_128_ctr_out[128] = {
    0x59,
    0x11,
    0x7E,
    0xFA,
    0xA2,
    0x98,
    0x1E,
    0x95,
    0xC2,
    0xD0,
    0x7A,
    0x3E,
    0xF0,
    0x7F,
    0xD3,
    0x17,
    0xF4,
    0x9C,
    0x6F,
    0x2D,
    0x3A,
    0x55,
    0x7E,
    0x07,
    0xA8,
    0xB0,
    0x21,
    0xDF,
    0x11,
    0x07,
    0x05,
    0xC4,
    0x9C,
    0xBA,
    0x68,
    0x05,
    0xBD,
    0xB3,
    0xB5,
    0x80,
    0x19,
    0xE1,
    0x2D,
    0x02,
    0xD1,
    0xF7,
    0xFA,
    0x27,
    0xE8,
    0xF5,
    0x24,
    0x6F,
    0x1A,
    0x79,
    0xBA,
    0xA0,
    0x18,
    0xF5,
    0x44,
    0x2E,
    0x79,
    0x7C,
    0x7A,
    0xEE,
    0x78,
    0xA6,
    0x59,
    0xE8,
    0x9A,
    0xD2,
    0x1C,
    0x63,
    0x2C,
    0x3E,
    0x73,
    0x56,
    0xD4,
    0x6A,
    0x1B,
    0xFB,
    0x29,
    0x54,
    0xF0,
    0xB3,
    0x3A,
    0x91,
    0x86,
    0x1F,
    0x29,
    0x9E,
    0x58,
    0x09,
    0x81,
    0x0B,
    0x8C,
    0x79,
    0x5B,
    0x00,
    0xE2,
    0x10,
    0x79,
    0x3B,
    0x5F,
    0xCD,
    0x5A,
    0xCA,
    0xD2,
    0x11,
    0xC9,
    0xFF,
    0xC2,
    0x9C,
    0x75,
    0x68,
    0x33,
    0x64,
    0x37,
    0x44,
    0xC2,
    0x7E,
    0xE1,
    0x90,
    0x64,
    0xCC,
    0x21,
    0xDB,
    0xA9,
    0xF6,
};
unsigned char std_aes_128_xts_out[128] = {
    0x15,
    0xB9,
    0x63,
    0x88,
    0x26,
    0x0B,
    0x79,
    0x7A,
    0xEE,
    0xBD,
    0xD8,
    0xDC,
    0x30,
    0xA3,
    0x9B,
    0x49,
    0xCC,
    0xA5,
    0xF7,
    0x21,
    0x2D,
    0x33,
    0x70,
    0xA1,
    0x92,
    0xD2,
    0x5C,
    0x62,
    0x36,
    0x51,
    0xD9,
    0xB5,
    0x52,
    0x49,
    0xD7,
    0x36,
    0x6C,
    0x18,
    0x62,
    0x1C,
    0x3D,
    0x76,
    0x1A,
    0x85,
    0x2E,
    0xA3,
    0x5D,
    0x73,
    0xF3,
    0xF5,
    0x98,
    0xF2,
    0xD9,
    0xBC,
    0x48,
    0x0C,
    0x1C,
    0x64,
    0xD8,
    0x8C,
    0x30,
    0xAA,
    0x06,
    0xFF,
    0x01,
    0xB6,
    0xF4,
    0xA2,
    0x03,
    0x38,
    0xF3,
    0xCE,
    0xDB,
    0xF8,
    0x90,
    0x41,
    0x1C,
    0x7B,
    0xEA,
    0xC8,
    0x22,
    0x87,
    0x2D,
    0x15,
    0x40,
    0x59,
    0xFE,
    0x2C,
    0x39,
    0x4E,
    0x99,
    0x78,
    0x3C,
    0x8B,
    0x17,
    0x52,
    0x1F,
    0xE7,
    0x2E,
    0x17,
    0xF4,
    0xD8,
    0xC1,
    0x5F,
    0x97,
    0x2E,
    0x66,
    0x7B,
    0xAE,
    0xEF,
    0xCB,
    0x97,
    0xCF,
    0xBC,
    0xF6,
    0xE8,
    0xC0,
    0x96,
    0xD8,
    0x5C,
    0x08,
    0xA4,
    0x40,
    0xF7,
    0xC2,
    0x8C,
    0x28,
    0xAB,
};

unsigned int AES_128_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== AES-128 test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_128, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_aes_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_XTS, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_128, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_aes_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_aes_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_aes_128_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_XTS, 0, std_in, 128, std_key, 0, std_iv, std_aes_128_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    #ifdef SKE_LP_DMA_FUNCTION
    printf("\r\n\r\n =================== AES-128 DMA test ==================== ");
    fflush(stdout);

        #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL, std_aes_128_ecb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_128_cbc_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_aes_128_cfb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_aes_128_ofb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_aes_128_ctr_out);
        #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_XTS, std_in, 32, std_key, 0, std_iv, std_aes_128_xts_out);
    //#endif

    if (ret) {
        return 1;
    }
    #endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_AES_192
unsigned char std_aes_192_ecb_out[128] = {
    0x83,
    0xE0,
    0x20,
    0x04,
    0x0E,
    0xD7,
    0xB3,
    0x26,
    0x8E,
    0x8E,
    0x04,
    0xD0,
    0xAC,
    0x7A,
    0x9C,
    0xDD,
    0x57,
    0x3D,
    0x94,
    0x29,
    0x35,
    0x8F,
    0xC1,
    0xC3,
    0x24,
    0xBA,
    0x41,
    0x8B,
    0x87,
    0xF1,
    0xDD,
    0x63,
    0x10,
    0xEA,
    0x25,
    0x5E,
    0xC6,
    0x62,
    0xDA,
    0x99,
    0x74,
    0x64,
    0xCA,
    0xAC,
    0x00,
    0x0C,
    0x47,
    0xEF,
    0x91,
    0x2F,
    0x31,
    0x71,
    0x97,
    0xF1,
    0x6B,
    0xE9,
    0x3E,
    0x25,
    0xE2,
    0x0A,
    0xA7,
    0x35,
    0xB8,
    0xAB,
    0xB0,
    0x2C,
    0xFB,
    0x4B,
    0xAB,
    0xF5,
    0xE6,
    0x39,
    0xE0,
    0xC9,
    0x41,
    0xF1,
    0x5F,
    0xFC,
    0x43,
    0x7A,
    0x5C,
    0x08,
    0xAC,
    0xD8,
    0xBD,
    0xC1,
    0x82,
    0xC4,
    0x92,
    0x1C,
    0x44,
    0x80,
    0x8B,
    0x48,
    0x5F,
    0x4A,
    0x12,
    0xB5,
    0x5F,
    0x9A,
    0x08,
    0x71,
    0xC2,
    0x33,
    0x99,
    0x05,
    0xF1,
    0x12,
    0x3D,
    0x76,
    0x72,
    0xF8,
    0xE4,
    0x65,
    0xC4,
    0x5B,
    0x9A,
    0xD6,
    0xFA,
    0x3C,
    0xD5,
    0xD2,
    0x7E,
    0xCC,
    0x46,
    0x52,
    0x29,
    0x88,
};
unsigned char std_aes_192_cbc_out[128] = {
    0xB3,
    0x95,
    0x80,
    0xF4,
    0xD8,
    0x83,
    0x49,
    0xB8,
    0x0E,
    0x28,
    0xE6,
    0x78,
    0x98,
    0x46,
    0xD5,
    0x1D,
    0x52,
    0x0B,
    0xEA,
    0xA4,
    0xC2,
    0x5D,
    0xE4,
    0x9E,
    0xC0,
    0xFB,
    0xB1,
    0x48,
    0x59,
    0x91,
    0x17,
    0x73,
    0x4D,
    0x1F,
    0xE6,
    0x30,
    0x8C,
    0x6B,
    0x0A,
    0x29,
    0x95,
    0x3B,
    0x81,
    0x7B,
    0xBD,
    0x99,
    0xB5,
    0x85,
    0xCB,
    0x2D,
    0x26,
    0x90,
    0xB0,
    0xC8,
    0xE3,
    0x13,
    0xCD,
    0x1D,
    0xAC,
    0x02,
    0x14,
    0xD6,
    0xBC,
    0xCB,
    0xD7,
    0xE0,
    0xE3,
    0x62,
    0x4A,
    0x10,
    0x1B,
    0xDE,
    0x26,
    0x8B,
    0xB7,
    0x5A,
    0x34,
    0xB5,
    0x40,
    0xB5,
    0x6B,
    0xBA,
    0x91,
    0x7D,
    0x9F,
    0x39,
    0xF1,
    0x0E,
    0x89,
    0x7E,
    0x19,
    0xE9,
    0x39,
    0x6F,
    0x55,
    0x21,
    0x1F,
    0x93,
    0xCA,
    0x77,
    0x0F,
    0x9C,
    0x57,
    0xA9,
    0xC3,
    0x92,
    0x32,
    0xF6,
    0x54,
    0x1E,
    0xBA,
    0xDD,
    0xF3,
    0xE6,
    0x40,
    0x28,
    0x6A,
    0x59,
    0xB0,
    0xFC,
    0xA8,
    0x0C,
    0xC2,
    0x49,
    0x22,
    0x72,
    0xC8,
    0x9C,
};
unsigned char std_aes_192_cfb_out[128] = {
    0x0F,
    0xD5,
    0x56,
    0xA7,
    0x99,
    0x07,
    0xF3,
    0xF4,
    0x35,
    0xDA,
    0xA6,
    0xE8,
    0x1D,
    0x1E,
    0x69,
    0x02,
    0xAC,
    0x32,
    0xA4,
    0xD1,
    0x42,
    0x34,
    0x23,
    0x4C,
    0x29,
    0x08,
    0x14,
    0xEA,
    0x59,
    0x20,
    0x5E,
    0x01,
    0xCD,
    0x61,
    0xEA,
    0x95,
    0x39,
    0xCC,
    0xF1,
    0xAE,
    0x5F,
    0x13,
    0x65,
    0x69,
    0x13,
    0x8C,
    0x78,
    0x38,
    0x3E,
    0xC0,
    0x69,
    0x8D,
    0xA5,
    0x09,
    0x79,
    0x8C,
    0x28,
    0xA5,
    0x3F,
    0x8A,
    0xCE,
    0xFD,
    0xA7,
    0x7A,
    0xE6,
    0x97,
    0x16,
    0x3B,
    0x5F,
    0xC2,
    0xC6,
    0x6E,
    0xDD,
    0x92,
    0xB2,
    0x3C,
    0x23,
    0x4F,
    0x23,
    0x61,
    0xAD,
    0xEB,
    0xAE,
    0xB6,
    0x18,
    0x59,
    0x23,
    0x2E,
    0xD0,
    0xD4,
    0x9C,
    0x90,
    0xC6,
    0xA7,
    0x8B,
    0x5E,
    0x4F,
    0xF0,
    0x08,
    0x9F,
    0xED,
    0x9B,
    0x1B,
    0xFB,
    0xD3,
    0xB9,
    0x8A,
    0xDA,
    0x57,
    0xE1,
    0x82,
    0xB6,
    0xEF,
    0x0B,
    0x81,
    0x60,
    0xFA,
    0xCA,
    0x70,
    0xD2,
    0x3F,
    0x5A,
    0x9D,
    0xDF,
    0x1D,
    0xA6,
    0x10,
    0x63,
};
unsigned char std_aes_192_ofb_out[128] = {
    0x0F,
    0xD5,
    0x56,
    0xA7,
    0x99,
    0x07,
    0xF3,
    0xF4,
    0x35,
    0xDA,
    0xA6,
    0xE8,
    0x1D,
    0x1E,
    0x69,
    0x02,
    0xBF,
    0x7E,
    0x3B,
    0x94,
    0xF3,
    0xAC,
    0xC4,
    0x08,
    0xBD,
    0xE6,
    0xCF,
    0xB1,
    0x7E,
    0xF6,
    0xA6,
    0xDE,
    0x1A,
    0xB8,
    0xA7,
    0xCC,
    0x09,
    0x06,
    0xC0,
    0xDE,
    0x34,
    0xFE,
    0xA3,
    0xAB,
    0xCF,
    0xB7,
    0x0D,
    0x92,
    0xDC,
    0xFD,
    0xAC,
    0x51,
    0xFD,
    0x54,
    0x61,
    0x28,
    0x4B,
    0xE0,
    0x9E,
    0x78,
    0x68,
    0x38,
    0xCF,
    0xC9,
    0x66,
    0x8D,
    0x51,
    0xFE,
    0xE7,
    0x1F,
    0x38,
    0x33,
    0xB8,
    0xF0,
    0x3A,
    0x17,
    0x8B,
    0x4E,
    0x48,
    0x34,
    0x46,
    0x5C,
    0x54,
    0x9E,
    0xBB,
    0x64,
    0x5F,
    0xB8,
    0xEA,
    0xD7,
    0xC5,
    0x70,
    0x7B,
    0xD8,
    0x11,
    0x5C,
    0xE6,
    0xB4,
    0xAC,
    0x2B,
    0x15,
    0x01,
    0x29,
    0x35,
    0xA2,
    0xCE,
    0x2A,
    0xDF,
    0x37,
    0x18,
    0x78,
    0x43,
    0xCA,
    0xA2,
    0x2A,
    0xB6,
    0x4C,
    0x80,
    0x07,
    0xA2,
    0xF6,
    0xD6,
    0x34,
    0x53,
    0x61,
    0xF9,
    0xE8,
    0xCB,
};
unsigned char std_aes_192_ctr_out[128] = {
    0x0F,
    0xD5,
    0x56,
    0xA7,
    0x99,
    0x07,
    0xF3,
    0xF4,
    0x35,
    0xDA,
    0xA6,
    0xE8,
    0x1D,
    0x1E,
    0x69,
    0x02,
    0x24,
    0x3C,
    0x8F,
    0xD2,
    0xB3,
    0xE0,
    0x33,
    0x68,
    0xCE,
    0x9D,
    0x71,
    0x9C,
    0x38,
    0x39,
    0x6E,
    0x9B,
    0x97,
    0x5D,
    0x9C,
    0x5B,
    0x38,
    0xEE,
    0xAF,
    0x2A,
    0xAD,
    0xF2,
    0x0F,
    0xF2,
    0x48,
    0x1E,
    0x09,
    0x37,
    0xAB,
    0x69,
    0x97,
    0x3E,
    0x5F,
    0x6F,
    0x06,
    0x4A,
    0xCC,
    0x36,
    0x60,
    0x76,
    0xBA,
    0xC2,
    0x82,
    0x02,
    0x20,
    0x25,
    0xBA,
    0xB5,
    0xE9,
    0x14,
    0xD4,
    0x47,
    0xFC,
    0xE2,
    0xFD,
    0x38,
    0xD1,
    0x14,
    0xAF,
    0x38,
    0xB5,
    0xCD,
    0xA1,
    0xB8,
    0x4F,
    0xE9,
    0xD2,
    0x1E,
    0x38,
    0x37,
    0xDA,
    0xBA,
    0xDF,
    0xF8,
    0xE0,
    0xDF,
    0xAB,
    0xF5,
    0xF5,
    0xCD,
    0x6B,
    0x85,
    0xDD,
    0x6B,
    0x30,
    0x29,
    0x64,
    0xFF,
    0xD4,
    0xE2,
    0x6C,
    0xFD,
    0xDF,
    0x52,
    0x44,
    0xE3,
    0x71,
    0x34,
    0x0F,
    0x30,
    0x0E,
    0x95,
    0x13,
    0x60,
    0xF6,
    0x72,
    0x18,
    0x68,
};
unsigned char std_aes_192_xts_out[128] = {
    0xEA,
    0xCC,
    0x76,
    0xA5,
    0x82,
    0xDF,
    0x86,
    0x99,
    0x27,
    0xE1,
    0x1C,
    0x48,
    0x6B,
    0x7C,
    0xA1,
    0xFB,
    0x40,
    0x5E,
    0x76,
    0x75,
    0xBA,
    0x40,
    0xC3,
    0xF4,
    0x59,
    0xEC,
    0x45,
    0xD4,
    0x13,
    0x10,
    0x2B,
    0xE0,
    0xB8,
    0x63,
    0x39,
    0x45,
    0xC8,
    0xD3,
    0x80,
    0x7D,
    0x9D,
    0x06,
    0xEC,
    0xC6,
    0xEA,
    0xDF,
    0x6F,
    0xCC,
    0x2A,
    0xEC,
    0xB3,
    0xCB,
    0x6B,
    0x54,
    0xC3,
    0x37,
    0x50,
    0x25,
    0xF9,
    0xBD,
    0xD1,
    0x61,
    0x9B,
    0xFF,
    0x57,
    0x74,
    0x7E,
    0x1D,
    0x0A,
    0x60,
    0x5F,
    0x5B,
    0xE0,
    0x4D,
    0x64,
    0x88,
    0xD4,
    0x81,
    0x0E,
    0x7A,
    0xBF,
    0x4B,
    0x9C,
    0x69,
    0x0B,
    0x7E,
    0x80,
    0xA2,
    0x2E,
    0xEB,
    0x19,
    0x81,
    0x68,
    0xCC,
    0xF6,
    0x28,
    0x7C,
    0xCA,
    0x09,
    0x33,
    0xFD,
    0xEC,
    0x69,
    0x95,
    0x7F,
    0x6D,
    0x7A,
    0x49,
    0x0F,
    0x2E,
    0x56,
    0x1D,
    0x19,
    0xBC,
    0x98,
    0x0B,
    0x37,
    0xA7,
    0x75,
    0xDB,
    0x43,
    0xCE,
    0x01,
    0x02,
    0x1D,
    0x38,
    0xE3,
    0x24,
};

unsigned int AES_192_Test(void)
{
    unsigned int ret;

    printf("\r\n\r\n =================== AES-192 test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_192, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_aes_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_XTS, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_192, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_aes_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_aes_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_aes_192_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_XTS, 0, std_in, 128, std_key, 0, std_iv, std_aes_192_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    #ifdef SKE_LP_DMA_FUNCTION
    printf("\r\n\r\n =================== AES-192 DMA test ==================== ");
    fflush(stdout);

        #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL, std_aes_192_ecb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_192_cbc_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_aes_192_cfb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_aes_192_ofb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_aes_192_ctr_out);
        #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_XTS, std_in, 32, std_key, 0, std_iv, std_aes_192_xts_out);
    //#endif

    if (ret) {
        return 1;
    }
    #endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_AES_256
unsigned char std_aes_256_ecb_out[128] = {
    0xBD,
    0xE8,
    0x9A,
    0xF4,
    0xC0,
    0x9D,
    0xE4,
    0x51,
    0x34,
    0x04,
    0x7B,
    0x45,
    0xF6,
    0x58,
    0xB2,
    0x51,
    0x75,
    0x71,
    0x45,
    0x7D,
    0xAF,
    0xA0,
    0x81,
    0xCF,
    0x54,
    0x68,
    0xA9,
    0x35,
    0x06,
    0xD9,
    0x6C,
    0xF9,
    0x17,
    0x85,
    0x12,
    0x5F,
    0xA0,
    0xDE,
    0x5B,
    0xF0,
    0x8C,
    0x56,
    0x24,
    0xB8,
    0x29,
    0x4F,
    0xD7,
    0x56,
    0xEC,
    0x0D,
    0x55,
    0x96,
    0xF4,
    0xF4,
    0xC5,
    0xFC,
    0x2A,
    0x86,
    0x78,
    0x8A,
    0x1C,
    0x5D,
    0x74,
    0xFF,
    0x27,
    0x2C,
    0x15,
    0xA2,
    0xDE,
    0x13,
    0x54,
    0x69,
    0x89,
    0x49,
    0x9F,
    0x79,
    0xEE,
    0xED,
    0x6B,
    0xE2,
    0x64,
    0x52,
    0xEE,
    0x96,
    0x69,
    0x8C,
    0x49,
    0x76,
    0xCA,
    0x9B,
    0x62,
    0x26,
    0xC9,
    0xCF,
    0x61,
    0x65,
    0x5E,
    0x3B,
    0x8B,
    0x0C,
    0xE4,
    0x90,
    0xAA,
    0x80,
    0xD4,
    0x78,
    0x8C,
    0x56,
    0x3E,
    0x74,
    0xB3,
    0x83,
    0x83,
    0x61,
    0xB4,
    0x9F,
    0xE6,
    0x0C,
    0x69,
    0xDE,
    0x55,
    0x3D,
    0xB7,
    0xA1,
    0xA9,
    0xE7,
    0xB7,
    0x89,
};
unsigned char std_aes_256_cbc_out[128] = {
    0x7C,
    0xA4,
    0x8E,
    0x82,
    0x99,
    0xFC,
    0x5A,
    0xD3,
    0xE9,
    0x08,
    0xB7,
    0x65,
    0xE3,
    0x0D,
    0x7A,
    0x3B,
    0x63,
    0xE3,
    0x82,
    0xF6,
    0x46,
    0x23,
    0xAC,
    0xE0,
    0x41,
    0xC4,
    0x0B,
    0x29,
    0xF5,
    0x92,
    0x59,
    0x2F,
    0x96,
    0xAD,
    0xBB,
    0xA5,
    0x58,
    0x52,
    0x49,
    0x32,
    0x59,
    0x25,
    0x20,
    0xBA,
    0x17,
    0xDB,
    0x52,
    0xE9,
    0x42,
    0x32,
    0x64,
    0x38,
    0x86,
    0xF2,
    0x02,
    0xA9,
    0x6B,
    0xA2,
    0x58,
    0x76,
    0xC6,
    0x30,
    0x2D,
    0xFC,
    0xE9,
    0x93,
    0x46,
    0x7F,
    0xB1,
    0x38,
    0xE2,
    0x93,
    0x98,
    0xA7,
    0x30,
    0x61,
    0xEC,
    0xCF,
    0xBE,
    0x5A,
    0xA1,
    0xAE,
    0x0E,
    0xDC,
    0x93,
    0x7C,
    0xCA,
    0x4E,
    0x0C,
    0x7A,
    0x60,
    0x87,
    0x14,
    0x82,
    0x9D,
    0x4E,
    0x7E,
    0x47,
    0x16,
    0x77,
    0x06,
    0xA1,
    0x8F,
    0xA7,
    0x45,
    0x59,
    0x16,
    0x1A,
    0x00,
    0xB4,
    0x41,
    0x29,
    0xA9,
    0x5C,
    0x3E,
    0x41,
    0x65,
    0xB8,
    0xC9,
    0x24,
    0xAB,
    0xE0,
    0x4A,
    0x4A,
    0x2D,
    0xC2,
    0xB3,
    0x2D,
};
unsigned char std_aes_256_cfb_out[128] = {
    0xBF,
    0xDE,
    0x14,
    0xD0,
    0xE9,
    0x92,
    0xFA,
    0x6B,
    0xAF,
    0x4B,
    0xF1,
    0x17,
    0xA7,
    0x7C,
    0x16,
    0x6D,
    0xAD,
    0x38,
    0x53,
    0xFA,
    0xFF,
    0x38,
    0xF0,
    0xF2,
    0xD1,
    0xD1,
    0x33,
    0x7B,
    0x56,
    0xE5,
    0xA1,
    0x1B,
    0xF1,
    0x11,
    0xAB,
    0x91,
    0xDA,
    0x05,
    0xBE,
    0x47,
    0xEE,
    0xFD,
    0x3D,
    0x22,
    0xA5,
    0x49,
    0x61,
    0x9A,
    0x27,
    0x19,
    0xEF,
    0xEA,
    0xEE,
    0x3A,
    0x36,
    0xD9,
    0xC8,
    0x96,
    0xA8,
    0xD4,
    0x3B,
    0xBE,
    0x92,
    0xA0,
    0x03,
    0x84,
    0x20,
    0x7E,
    0x45,
    0x1C,
    0x42,
    0x95,
    0x86,
    0xB4,
    0x82,
    0x71,
    0x65,
    0xFB,
    0xC8,
    0x60,
    0x08,
    0x9C,
    0xAB,
    0x2E,
    0x24,
    0xB1,
    0x64,
    0x01,
    0x53,
    0x10,
    0x11,
    0x0C,
    0x1C,
    0xF1,
    0x00,
    0x21,
    0x23,
    0xA8,
    0x8C,
    0xC7,
    0xD6,
    0x78,
    0xE3,
    0xAE,
    0xEA,
    0x3B,
    0xE8,
    0xA1,
    0x6B,
    0x58,
    0x38,
    0x49,
    0x01,
    0x5B,
    0xAC,
    0xA4,
    0xF1,
    0x6D,
    0x93,
    0x96,
    0xAA,
    0x12,
    0x54,
    0x82,
    0x0B,
    0x05,
    0xB7,
    0x8F,
};
unsigned char std_aes_256_ofb_out[128] = {
    0xBF,
    0xDE,
    0x14,
    0xD0,
    0xE9,
    0x92,
    0xFA,
    0x6B,
    0xAF,
    0x4B,
    0xF1,
    0x17,
    0xA7,
    0x7C,
    0x16,
    0x6D,
    0x2A,
    0xE0,
    0x78,
    0x06,
    0x68,
    0x92,
    0xD7,
    0xF5,
    0x2A,
    0x3D,
    0x82,
    0x43,
    0x5A,
    0xEE,
    0xA9,
    0xD6,
    0x07,
    0x68,
    0x8A,
    0x00,
    0x2A,
    0xAF,
    0x45,
    0x52,
    0xF9,
    0x29,
    0x65,
    0x43,
    0xCF,
    0xCA,
    0xD6,
    0x5D,
    0xEB,
    0xF1,
    0xB0,
    0x5D,
    0x1D,
    0xC7,
    0xDA,
    0x6B,
    0x48,
    0x14,
    0x36,
    0xA1,
    0x04,
    0x70,
    0x60,
    0xA0,
    0xD4,
    0xBD,
    0xAD,
    0x40,
    0x77,
    0x6E,
    0x0D,
    0xBA,
    0x87,
    0x06,
    0x9F,
    0x50,
    0x2D,
    0x95,
    0x27,
    0x0A,
    0x39,
    0x51,
    0x44,
    0xFB,
    0x58,
    0x10,
    0x6F,
    0x48,
    0xC0,
    0xB1,
    0x09,
    0xD9,
    0x72,
    0x66,
    0x35,
    0xF8,
    0x8F,
    0xD4,
    0xAB,
    0xB0,
    0x4C,
    0x6E,
    0xFE,
    0xF1,
    0x2B,
    0x97,
    0x8A,
    0xC3,
    0x64,
    0xED,
    0xA9,
    0x7C,
    0xA4,
    0x73,
    0x0C,
    0xA6,
    0xBF,
    0x3E,
    0x41,
    0xB7,
    0xA9,
    0x6F,
    0xD3,
    0x2D,
    0xC9,
    0x56,
    0xCA,
    0x39,
};
unsigned char std_aes_256_ctr_out[128] = {
    0xBF,
    0xDE,
    0x14,
    0xD0,
    0xE9,
    0x92,
    0xFA,
    0x6B,
    0xAF,
    0x4B,
    0xF1,
    0x17,
    0xA7,
    0x7C,
    0x16,
    0x6D,
    0x9B,
    0x34,
    0xDC,
    0xCD,
    0x00,
    0x58,
    0x0A,
    0xBB,
    0xEB,
    0x92,
    0x9A,
    0x67,
    0x8F,
    0xE9,
    0xC4,
    0x9F,
    0x50,
    0x47,
    0x57,
    0x3D,
    0x2A,
    0xBE,
    0xE8,
    0x71,
    0x17,
    0x8B,
    0x39,
    0x0D,
    0xC0,
    0x11,
    0xA6,
    0x10,
    0x71,
    0x15,
    0x64,
    0xB4,
    0xFF,
    0xA5,
    0xAA,
    0x95,
    0xFE,
    0xFA,
    0x2B,
    0xBE,
    0x3C,
    0xB9,
    0xA2,
    0x3D,
    0xA2,
    0x69,
    0x0F,
    0xA2,
    0x56,
    0x59,
    0x7E,
    0x01,
    0x45,
    0x43,
    0x2F,
    0xAC,
    0xB9,
    0xCB,
    0xAB,
    0xA2,
    0x91,
    0xC5,
    0x93,
    0xF9,
    0xC4,
    0x72,
    0xEF,
    0x41,
    0x16,
    0x3B,
    0xC7,
    0x19,
    0x50,
    0x5C,
    0xC7,
    0xD3,
    0x43,
    0x67,
    0xDB,
    0xAD,
    0x8F,
    0xA4,
    0x3E,
    0xFD,
    0x9E,
    0x6E,
    0xEB,
    0xEF,
    0x09,
    0xE4,
    0x9E,
    0x14,
    0x0F,
    0xD2,
    0x36,
    0x2A,
    0x74,
    0xF5,
    0xCE,
    0x6C,
    0xC2,
    0x66,
    0xEA,
    0x71,
    0x1B,
    0x57,
    0xED,
    0xB7,
};
unsigned char std_aes_256_xts_out[128] = {
    0x4E,
    0x2B,
    0xA3,
    0xAD,
    0xA1,
    0xBC,
    0x79,
    0xAF,
    0x26,
    0x04,
    0xFC,
    0x2B,
    0x7D,
    0x71,
    0xC8,
    0xCB,
    0x71,
    0xFB,
    0x82,
    0x3E,
    0x0A,
    0x6B,
    0x34,
    0x31,
    0x77,
    0x37,
    0x05,
    0xD9,
    0xAD,
    0x86,
    0x0F,
    0x29,
    0xFE,
    0x7A,
    0x65,
    0x5A,
    0xCD,
    0x43,
    0x14,
    0xDD,
    0x46,
    0x74,
    0x6C,
    0xEF,
    0x79,
    0xFA,
    0xAE,
    0x71,
    0x38,
    0x8C,
    0x42,
    0x5F,
    0xEF,
    0xEF,
    0x23,
    0x61,
    0x33,
    0x79,
    0x78,
    0xB4,
    0x68,
    0xC8,
    0x54,
    0x99,
    0x5A,
    0x04,
    0xE1,
    0x99,
    0x02,
    0x3C,
    0x15,
    0x56,
    0x86,
    0x42,
    0x2E,
    0x92,
    0x66,
    0x1E,
    0xB9,
    0x90,
    0x5C,
    0xBF,
    0x21,
    0x4B,
    0x56,
    0x8D,
    0x34,
    0x71,
    0x5C,
    0x9E,
    0x16,
    0xDE,
    0xE2,
    0x99,
    0x52,
    0xC9,
    0x52,
    0xEA,
    0xF7,
    0x5B,
    0x90,
    0x6D,
    0x20,
    0xD8,
    0x29,
    0xD6,
    0x1D,
    0x28,
    0xB8,
    0x1D,
    0xBB,
    0x76,
    0x93,
    0x1D,
    0x2C,
    0xA7,
    0x4C,
    0xD0,
    0x71,
    0xB6,
    0x8F,
    0x7D,
    0xBB,
    0xE5,
    0x48,
    0xFC,
    0x96,
    0x6A,
};

unsigned int AES_256_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== AES-256 test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_256, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_aes_256_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_XTS, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_AES_256, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_aes_256_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_aes_256_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_256_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_aes_256_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_aes_256_ctr_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_XTS, 0, std_in, 128, std_key, 0, std_iv, std_aes_256_xts_out);
    //#endif

    if (ret) {
        return 1;
    }


    #ifdef SKE_LP_DMA_FUNCTION
    printf("\r\n\r\n =================== AES-256 DMA test ==================== ");
    fflush(stdout);

        #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL, std_aes_256_ecb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_256_cbc_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_aes_256_cfb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_aes_256_ofb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_aes_256_ctr_out);
        #endif

    //#if defined (SUPPORT_SKE_MODE_XTS)
    //  ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_XTS, std_in, 32, std_key, 0, std_iv, std_aes_256_xts_out);
    //#endif

    if (ret) {
        return 1;
    }
    #endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_DES
unsigned char std_des_ecb_out[128] = {
    0x60,
    0xDF,
    0xC6,
    0xE3,
    0x58,
    0x13,
    0x78,
    0xFB,
    0xB1,
    0x4D,
    0xED,
    0x0A,
    0x20,
    0x80,
    0x53,
    0xE0,
    0x5C,
    0x51,
    0x40,
    0x83,
    0x38,
    0x44,
    0x8B,
    0x8E,
    0x12,
    0x36,
    0xCD,
    0x34,
    0xD2,
    0xAA,
    0x6F,
    0xF7,
    0x8C,
    0x13,
    0xBB,
    0xA8,
    0x6B,
    0x13,
    0x74,
    0x70,
    0x27,
    0x92,
    0xCE,
    0x5B,
    0xD5,
    0xA8,
    0xF8,
    0x53,
    0xC6,
    0xCA,
    0x08,
    0x28,
    0x59,
    0xDD,
    0xF6,
    0x71,
    0x25,
    0x9C,
    0x67,
    0x0A,
    0xA5,
    0xDC,
    0xC8,
    0xFA,
    0x28,
    0x3D,
    0x41,
    0xBA,
    0xDA,
    0xB2,
    0x72,
    0xD3,
    0x81,
    0xDD,
    0x70,
    0xA5,
    0xCF,
    0x22,
    0x4D,
    0x5E,
    0x41,
    0xB2,
    0x68,
    0x69,
    0xA1,
    0x9C,
    0x58,
    0x47,
    0xEA,
    0x0B,
    0xDE,
    0x1C,
    0x5A,
    0x31,
    0x0B,
    0xD2,
    0x3E,
    0xD8,
    0xBF,
    0xA9,
    0x35,
    0x44,
    0x5F,
    0x92,
    0x3D,
    0xC9,
    0x0B,
    0xB9,
    0x9D,
    0xD8,
    0xC9,
    0x63,
    0xC5,
    0x43,
    0x57,
    0x66,
    0xE0,
    0xED,
    0x16,
    0x1A,
    0x88,
    0x07,
    0x48,
    0x9F,
    0x10,
    0xA9,
    0xF9,
    0x97,
};
unsigned char std_des_cbc_out[128] = {
    0x1E,
    0x1C,
    0xC3,
    0x8F,
    0x7D,
    0x64,
    0x29,
    0x80,
    0x04,
    0x7B,
    0x0D,
    0xD5,
    0x83,
    0xDC,
    0xC8,
    0xE2,
    0xE3,
    0x3A,
    0x4D,
    0xA4,
    0xDB,
    0x7A,
    0x06,
    0x41,
    0xA0,
    0x3F,
    0x11,
    0x6E,
    0xBE,
    0xD4,
    0xFF,
    0xBC,
    0xCF,
    0xBE,
    0xFB,
    0xCD,
    0x91,
    0xCB,
    0x31,
    0x76,
    0x25,
    0x5F,
    0x88,
    0x5D,
    0x78,
    0x58,
    0x84,
    0x8F,
    0xB6,
    0x08,
    0x40,
    0xAF,
    0x20,
    0xBB,
    0x7B,
    0xA6,
    0x18,
    0x30,
    0x06,
    0x5E,
    0x8F,
    0xE5,
    0xB2,
    0x0A,
    0xC8,
    0xCE,
    0x8B,
    0x3F,
    0x48,
    0x6D,
    0xFF,
    0xEC,
    0xC5,
    0x38,
    0x4D,
    0xF2,
    0x9E,
    0xC8,
    0xC4,
    0xD2,
    0xB5,
    0xA1,
    0xC5,
    0x66,
    0xA8,
    0xF0,
    0xB1,
    0xCE,
    0x16,
    0xA8,
    0x0C,
    0x92,
    0xA3,
    0xCE,
    0xF3,
    0xDE,
    0x44,
    0x64,
    0xB8,
    0x14,
    0x21,
    0xE1,
    0x2B,
    0x66,
    0x31,
    0x38,
    0xD0,
    0x16,
    0xDE,
    0x3C,
    0x38,
    0xDC,
    0x71,
    0x3D,
    0xDE,
    0x9B,
    0x43,
    0xD3,
    0x2C,
    0xAE,
    0x87,
    0xB1,
    0x84,
    0x91,
    0xC1,
    0xCE,
    0x1D,
    0xEB,
};
unsigned char std_des_cfb_out[128] = {
    0xE2,
    0x26,
    0x12,
    0x57,
    0x6D,
    0xE8,
    0x65,
    0xD0,
    0xD3,
    0xDC,
    0xDE,
    0xFD,
    0x36,
    0x85,
    0xCB,
    0xC5,
    0xC9,
    0x99,
    0x22,
    0xF7,
    0x6F,
    0xA5,
    0xC4,
    0xEA,
    0x67,
    0x93,
    0x3E,
    0xB8,
    0x68,
    0x09,
    0xFD,
    0x8E,
    0xB2,
    0x4A,
    0x77,
    0x7D,
    0xC8,
    0x7E,
    0x75,
    0x2C,
    0xEA,
    0xE0,
    0x5A,
    0x4D,
    0xB5,
    0x45,
    0x42,
    0x67,
    0x79,
    0xC8,
    0xAF,
    0xAB,
    0x63,
    0xC5,
    0xA8,
    0xBB,
    0x70,
    0x3D,
    0x68,
    0x80,
    0x70,
    0x7D,
    0xE5,
    0x47,
    0x92,
    0x6F,
    0x66,
    0x98,
    0xE1,
    0xBC,
    0xD8,
    0xA5,
    0x0F,
    0x7C,
    0x15,
    0x60,
    0x34,
    0x94,
    0xE8,
    0xC9,
    0x40,
    0x63,
    0x91,
    0xB0,
    0x83,
    0xCF,
    0xD7,
    0x14,
    0x21,
    0x81,
    0x88,
    0x69,
    0xAF,
    0x14,
    0x15,
    0x4D,
    0x38,
    0x8B,
    0xE3,
    0xF7,
    0xDD,
    0x18,
    0xAC,
    0xCE,
    0x92,
    0x1A,
    0xE5,
    0xCC,
    0x0C,
    0xCE,
    0x51,
    0x04,
    0xB2,
    0x5A,
    0xBB,
    0x31,
    0x3A,
    0xF2,
    0xCC,
    0x93,
    0xE7,
    0x36,
    0xEE,
    0xC3,
    0xB5,
    0x00,
    0xFD,
    0x6D,
};
unsigned char std_des_ofb_out[128] = {
    0xE2,
    0x26,
    0x12,
    0x57,
    0x6D,
    0xE8,
    0x65,
    0xD0,
    0x1D,
    0x35,
    0x32,
    0x16,
    0xA2,
    0xA6,
    0xD6,
    0x63,
    0xA6,
    0xF3,
    0xA1,
    0x81,
    0xEC,
    0x58,
    0x98,
    0x59,
    0x1E,
    0x5B,
    0xB0,
    0x26,
    0xA9,
    0xAE,
    0x2D,
    0xAE,
    0xBC,
    0x42,
    0xF6,
    0xC6,
    0x0E,
    0xC2,
    0xE0,
    0x9A,
    0x0F,
    0xF2,
    0x3F,
    0xEC,
    0xED,
    0x12,
    0xFA,
    0xA7,
    0x4E,
    0x2A,
    0xB8,
    0x34,
    0xE9,
    0xCA,
    0x5C,
    0xC1,
    0x09,
    0x90,
    0x27,
    0xB4,
    0x29,
    0x92,
    0xBA,
    0x02,
    0xAC,
    0xEC,
    0x0D,
    0x62,
    0x62,
    0x0B,
    0xDF,
    0xB2,
    0x0C,
    0x31,
    0xEB,
    0xC9,
    0x0F,
    0x7E,
    0x14,
    0xC8,
    0x33,
    0xA7,
    0x18,
    0xE9,
    0xBC,
    0xD4,
    0xB9,
    0x71,
    0x0B,
    0x3D,
    0xC5,
    0xF0,
    0x7E,
    0x95,
    0x5D,
    0x4A,
    0x0E,
    0xDD,
    0x43,
    0x77,
    0xE1,
    0x21,
    0x31,
    0xFC,
    0x62,
    0xA0,
    0xED,
    0xC5,
    0xE4,
    0x5B,
    0xE2,
    0x6F,
    0x37,
    0x99,
    0x15,
    0x64,
    0x83,
    0x87,
    0x7E,
    0x90,
    0xFB,
    0xB6,
    0x50,
    0xC4,
    0x6A,
    0x73,
    0x34,
    0xE6,
};
unsigned char std_des_ctr_out[128] = {
    0xE2,
    0x26,
    0x12,
    0x57,
    0x6D,
    0xE8,
    0x65,
    0xD0,
    0x4C,
    0xCC,
    0x82,
    0x62,
    0x69,
    0x2B,
    0x26,
    0x0F,
    0x97,
    0x79,
    0xA3,
    0xB2,
    0x06,
    0xCC,
    0x9C,
    0x32,
    0xE2,
    0x35,
    0xCE,
    0xF0,
    0x01,
    0x32,
    0xE7,
    0x0E,
    0xDD,
    0xB4,
    0xE3,
    0xC9,
    0xC5,
    0xBC,
    0x5E,
    0x49,
    0xBD,
    0x0B,
    0xC4,
    0xC8,
    0xEE,
    0x01,
    0x6C,
    0x29,
    0xCC,
    0x6B,
    0x09,
    0x32,
    0x38,
    0x2E,
    0xEF,
    0x03,
    0xDF,
    0x9D,
    0x4E,
    0xBA,
    0x90,
    0x73,
    0xE0,
    0x1A,
    0x1C,
    0x35,
    0x41,
    0x5B,
    0x7F,
    0x01,
    0x80,
    0x7F,
    0xDA,
    0x62,
    0x51,
    0x94,
    0x2E,
    0x2C,
    0xFA,
    0x1B,
    0x5C,
    0x1E,
    0x7C,
    0x74,
    0x50,
    0xD9,
    0xF1,
    0xDF,
    0x0A,
    0x68,
    0x4D,
    0x33,
    0x79,
    0x75,
    0x30,
    0x9F,
    0x94,
    0xFE,
    0xC4,
    0x4C,
    0x1A,
    0x7E,
    0x16,
    0xFC,
    0x9F,
    0xA1,
    0xB1,
    0xB3,
    0x21,
    0xED,
    0x32,
    0xC7,
    0xFE,
    0xDE,
    0xFC,
    0x39,
    0xCB,
    0x4E,
    0x6F,
    0xEB,
    0x51,
    0xBF,
    0x32,
    0xC1,
    0x16,
    0x5A,
    0x02,
    0x46,
};

unsigned int DES_Test(void)
{
    unsigned int ret;

    printf("\r\n\r\n =================== DES test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_DES, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_des_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_des_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_des_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_des_ofb_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_des_ctr_out);
    //#endif

    if (ret) {
        return 1;
    }

    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_DES, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_des_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_des_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_des_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_DES, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_des_ofb_out);
    #endif

    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_test(SKE_ALG_DES, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_des_ctr_out);
    //#endif

    if (ret) {
        return 1;
    }


    #ifdef SKE_LP_DMA_FUNCTION
    printf("\r\n\r\n =================== DES DMA test ==================== ");
    fflush(stdout);

        #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_DMA_test(SKE_ALG_DES, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL, std_des_ecb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_DMA_test(SKE_ALG_DES, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_des_cbc_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_DMA_test(SKE_ALG_DES, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_des_cfb_out);
        #endif

        #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_DMA_test(SKE_ALG_DES, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_des_ofb_out);
        #endif

    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_DMA_test(SKE_ALG_DES, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_des_ctr_out);
    //#endif

    if (ret) {
        return 1;
    }

    #endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_TDES_128
unsigned char std_tdes_128_ecb_out[128] = {
    0xC0,
    0x07,
    0x27,
    0x76,
    0x1E,
    0xC2,
    0x72,
    0x82,
    0xF9,
    0x37,
    0x97,
    0x20,
    0x32,
    0xEC,
    0x35,
    0x03,
    0x69,
    0x25,
    0x5F,
    0x58,
    0x33,
    0x7B,
    0xED,
    0x68,
    0x59,
    0x71,
    0x93,
    0x5A,
    0x75,
    0x48,
    0x75,
    0xBA,
    0xFB,
    0xC3,
    0x7A,
    0x7A,
    0x84,
    0x63,
    0x13,
    0xFF,
    0x7A,
    0x64,
    0xC6,
    0xCB,
    0xCD,
    0xF8,
    0x0D,
    0xCE,
    0x20,
    0xD7,
    0x05,
    0xC8,
    0x21,
    0x74,
    0x5A,
    0xE2,
    0xC7,
    0x53,
    0xB2,
    0x67,
    0xF6,
    0xB8,
    0x85,
    0x4D,
    0x6C,
    0xF0,
    0x57,
    0xA8,
    0x12,
    0xFB,
    0xA1,
    0xFC,
    0xDA,
    0x02,
    0x80,
    0xBD,
    0x4F,
    0x83,
    0x47,
    0x53,
    0x34,
    0xF6,
    0x79,
    0x99,
    0xBB,
    0xD2,
    0x9E,
    0xFA,
    0xDB,
    0x91,
    0xBB,
    0xAF,
    0x12,
    0x8F,
    0xD2,
    0xA7,
    0x04,
    0x48,
    0x73,
    0x67,
    0x99,
    0xFD,
    0x2B,
    0xCF,
    0x07,
    0x09,
    0x83,
    0x78,
    0x38,
    0xD6,
    0x7C,
    0x79,
    0xE9,
    0xDC,
    0xF0,
    0x46,
    0xC6,
    0x4A,
    0xEC,
    0x93,
    0x7F,
    0x00,
    0xAF,
    0xAB,
    0x21,
    0xBA,
    0x94,
    0xBF,
};
unsigned char std_tdes_128_cbc_out[128] = {
    0xD3,
    0xC6,
    0x6C,
    0xE5,
    0xE8,
    0xFE,
    0x12,
    0x02,
    0xBA,
    0xF4,
    0xC0,
    0x46,
    0x1A,
    0x3C,
    0x76,
    0xA5,
    0x2F,
    0xB1,
    0x5D,
    0x99,
    0xD0,
    0x6B,
    0x90,
    0xDC,
    0x23,
    0x77,
    0xCA,
    0x8E,
    0x0C,
    0x13,
    0x9C,
    0x34,
    0x44,
    0x26,
    0x21,
    0x93,
    0x90,
    0x93,
    0x9A,
    0xB3,
    0xF1,
    0x74,
    0x83,
    0xA8,
    0x11,
    0xEB,
    0x69,
    0xEA,
    0x2E,
    0x3A,
    0x44,
    0xC9,
    0xE6,
    0x98,
    0x62,
    0x06,
    0x1C,
    0xA6,
    0xD5,
    0x7A,
    0xB1,
    0x40,
    0xAF,
    0xEF,
    0x65,
    0x80,
    0x6C,
    0x78,
    0x05,
    0x08,
    0xBD,
    0x65,
    0x39,
    0xC0,
    0x58,
    0x11,
    0x70,
    0x35,
    0xD4,
    0x0C,
    0xC9,
    0x8D,
    0x8E,
    0xE8,
    0x46,
    0x77,
    0xE4,
    0xF5,
    0xE2,
    0x9A,
    0x64,
    0x7F,
    0x2C,
    0xC4,
    0xB5,
    0x61,
    0x52,
    0x24,
    0xFF,
    0x30,
    0x89,
    0xC7,
    0x38,
    0x73,
    0x0C,
    0x11,
    0x8F,
    0x0F,
    0x7B,
    0xE5,
    0xC3,
    0x50,
    0x26,
    0x7F,
    0xC3,
    0x1E,
    0x5F,
    0x85,
    0x16,
    0x13,
    0xD7,
    0xE3,
    0xFA,
    0x76,
    0x1A,
    0x11,
    0xBF,
    0x79,
};
unsigned char std_tdes_128_cfb_out[128] = {
    0xDE,
    0x65,
    0x86,
    0x57,
    0xCE,
    0xC1,
    0xD1,
    0x3A,
    0x4C,
    0x41,
    0x6E,
    0xD7,
    0xE8,
    0x3C,
    0xAB,
    0x85,
    0x23,
    0x82,
    0x15,
    0x69,
    0xB6,
    0x3D,
    0xBE,
    0x0E,
    0xAB,
    0xCD,
    0x44,
    0x72,
    0x65,
    0xD6,
    0x23,
    0x32,
    0x56,
    0x0A,
    0x17,
    0xB5,
    0xA9,
    0x87,
    0x22,
    0x9D,
    0x03,
    0xF0,
    0x5D,
    0x28,
    0x9D,
    0x12,
    0x0F,
    0x6A,
    0xB2,
    0xCD,
    0x70,
    0x66,
    0x6B,
    0xE5,
    0x06,
    0x24,
    0x84,
    0x13,
    0x41,
    0xBF,
    0xEB,
    0x17,
    0x8B,
    0xA1,
    0xEA,
    0xD0,
    0x02,
    0x1B,
    0x8B,
    0xFB,
    0xE7,
    0x89,
    0xC2,
    0xDE,
    0x86,
    0xBA,
    0x06,
    0x50,
    0x86,
    0xDB,
    0x01,
    0x98,
    0x47,
    0x02,
    0x5A,
    0x3A,
    0xE9,
    0xC1,
    0x60,
    0x77,
    0xCE,
    0x34,
    0x08,
    0x73,
    0x33,
    0x90,
    0x27,
    0x41,
    0x69,
    0x94,
    0xFF,
    0xF6,
    0x4A,
    0x55,
    0x8E,
    0x13,
    0x87,
    0x88,
    0x90,
    0x5A,
    0x1A,
    0xB1,
    0xDA,
    0x73,
    0x11,
    0xD0,
    0xFF,
    0x1B,
    0x11,
    0x69,
    0xAB,
    0xC8,
    0xBF,
    0xB7,
    0x8A,
    0x47,
    0xE0,
    0x51,
};
unsigned char std_tdes_128_ofb_out[128] = {
    0xDE,
    0x65,
    0x86,
    0x57,
    0xCE,
    0xC1,
    0xD1,
    0x3A,
    0x2C,
    0xA4,
    0x0F,
    0x4B,
    0x76,
    0xD9,
    0x1E,
    0x08,
    0xB8,
    0x71,
    0x24,
    0xE7,
    0x2F,
    0x96,
    0x55,
    0x07,
    0x42,
    0x1D,
    0x8E,
    0x18,
    0xA5,
    0xAC,
    0x42,
    0x7C,
    0xA4,
    0x46,
    0x78,
    0xA0,
    0xD7,
    0x9F,
    0x1D,
    0x32,
    0x44,
    0x34,
    0x79,
    0x5F,
    0x01,
    0x6C,
    0x15,
    0x0B,
    0x70,
    0xC5,
    0x04,
    0xEB,
    0xD6,
    0x4F,
    0xF9,
    0x00,
    0x9E,
    0xFD,
    0x04,
    0xA5,
    0x09,
    0xB0,
    0x14,
    0xB6,
    0x60,
    0xC3,
    0x41,
    0x94,
    0x9B,
    0x6B,
    0x4D,
    0xB9,
    0x19,
    0x27,
    0x49,
    0xB1,
    0x54,
    0xAF,
    0xF2,
    0x4F,
    0x9E,
    0x3A,
    0xE4,
    0x24,
    0xA2,
    0x37,
    0xE6,
    0xB5,
    0xD4,
    0xB0,
    0x71,
    0x47,
    0x6F,
    0x5D,
    0x13,
    0xCD,
    0x24,
    0xF7,
    0xF4,
    0x0D,
    0x6F,
    0xA3,
    0xDD,
    0xAB,
    0x5D,
    0xD6,
    0x98,
    0xB3,
    0xE2,
    0x73,
    0xD2,
    0xD5,
    0x9E,
    0x65,
    0x82,
    0x51,
    0xF4,
    0x84,
    0x87,
    0x81,
    0xB7,
    0xC1,
    0xAD,
    0xB6,
    0xBB,
    0xCE,
    0x40,
    0xC2,
};
unsigned char std_tdes_128_ctr_out[128] = {
    0xDE,
    0x65,
    0x86,
    0x57,
    0xCE,
    0xC1,
    0xD1,
    0x3A,
    0x9F,
    0xA9,
    0xA7,
    0x03,
    0xCA,
    0x3A,
    0xAA,
    0xA1,
    0x13,
    0x83,
    0x2F,
    0x12,
    0x47,
    0xF2,
    0xB8,
    0x06,
    0x2D,
    0x1E,
    0x0E,
    0x3D,
    0xDB,
    0xE2,
    0x7A,
    0x87,
    0x8B,
    0x0C,
    0xE8,
    0xAA,
    0x92,
    0xDE,
    0x51,
    0x39,
    0x7F,
    0xF4,
    0x2A,
    0xE1,
    0x4F,
    0x84,
    0xDA,
    0x50,
    0x92,
    0x6F,
    0x4D,
    0xD5,
    0xCB,
    0x80,
    0x49,
    0xEF,
    0x04,
    0xF0,
    0xEC,
    0x84,
    0x0A,
    0x8B,
    0x08,
    0x47,
    0x32,
    0x5A,
    0x5D,
    0x21,
    0xB3,
    0x6D,
    0xB2,
    0x66,
    0x12,
    0x5B,
    0xED,
    0x15,
    0x2F,
    0x35,
    0x00,
    0xAF,
    0xDC,
    0xC0,
    0x46,
    0xB7,
    0xCB,
    0x70,
    0x5E,
    0xF9,
    0x4A,
    0x8E,
    0xA7,
    0x8E,
    0xB5,
    0x10,
    0x9B,
    0x49,
    0x12,
    0x60,
    0x00,
    0xFA,
    0x60,
    0xDE,
    0x11,
    0x6E,
    0x9C,
    0x55,
    0xF1,
    0x05,
    0x2C,
    0x81,
    0x9C,
    0x63,
    0x0E,
    0x5D,
    0x6A,
    0xD1,
    0x1D,
    0x44,
    0xA4,
    0x9B,
    0x2B,
    0xB9,
    0x2D,
    0x3F,
    0x45,
    0xD4,
    0xA5,
    0x1D,
};

unsigned int TDES_128_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== 3DES-2key test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_128, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_tdes_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_tdes_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_tdes_128_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_128, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_tdes_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_tdes_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_128, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_tdes_128_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    //#ifdef SKE_LP_DMA_FUNCTION
    //  printf("\r\n\r\n =================== 3DES-2key DMA test ==================== ");fflush(stdout);
    //
    //#if defined (SUPPORT_SKE_MODE_ECB)
    //  ret  = SKE_DMA_test(SKE_ALG_TDES_128, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL,   std_tdes_128_ecb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CBC)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_128, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_tdes_128_cbc_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_128, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_tdes_128_cfb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_OFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_128, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_tdes_128_ofb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_128, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_tdes_128_ctr_out);
    //#endif
    //
    //  if(ret)
    //  {
    //      return 1;
    //  }
    //#endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_TDES_192
unsigned char std_tdes_192_ecb_out[128] = {
    0xB6,
    0xA6,
    0x39,
    0xE6,
    0x5D,
    0x25,
    0x73,
    0xA6,
    0xEF,
    0x96,
    0x1D,
    0xEB,
    0xA8,
    0x7E,
    0x77,
    0x17,
    0x61,
    0x52,
    0x3B,
    0xE6,
    0xD0,
    0xBE,
    0x3D,
    0x1D,
    0x0C,
    0xBF,
    0xDB,
    0x5D,
    0x96,
    0xB7,
    0x9D,
    0xB6,
    0x03,
    0x3E,
    0x3B,
    0xE7,
    0x8B,
    0xF0,
    0x74,
    0x7E,
    0xDF,
    0xD9,
    0x60,
    0xA9,
    0x2A,
    0xD4,
    0x8E,
    0x54,
    0xF8,
    0xFB,
    0x91,
    0x01,
    0x05,
    0xEA,
    0xCC,
    0xE5,
    0x77,
    0x02,
    0x06,
    0x78,
    0x30,
    0xDF,
    0x90,
    0x24,
    0x03,
    0x46,
    0x6F,
    0x33,
    0xB2,
    0x3B,
    0xA0,
    0xF4,
    0x71,
    0x22,
    0x1F,
    0x77,
    0xD7,
    0x7D,
    0xCE,
    0xC2,
    0x52,
    0x96,
    0x74,
    0xD1,
    0x7F,
    0x56,
    0x77,
    0x30,
    0x52,
    0x75,
    0x99,
    0x52,
    0x1D,
    0xA8,
    0x49,
    0x21,
    0x37,
    0x15,
    0xD0,
    0xBB,
    0x94,
    0x05,
    0xC6,
    0xDF,
    0x7B,
    0x3B,
    0xE5,
    0x1C,
    0x71,
    0xEF,
    0xCF,
    0x96,
    0xC0,
    0x9F,
    0xC9,
    0x98,
    0xC5,
    0x72,
    0x3D,
    0xB7,
    0x73,
    0x3A,
    0xB1,
    0xE7,
    0xF1,
    0x84,
    0x1A,
    0x33,
};
unsigned char std_tdes_192_cbc_out[128] = {
    0xD6,
    0x83,
    0xB4,
    0xDC,
    0x06,
    0xF8,
    0xA6,
    0x34,
    0x6E,
    0xEB,
    0xA9,
    0x3A,
    0x95,
    0x3B,
    0x79,
    0x51,
    0x36,
    0xAD,
    0x4F,
    0xD9,
    0x3F,
    0x01,
    0x4A,
    0xA8,
    0x66,
    0xC2,
    0x92,
    0xD9,
    0x1C,
    0x7F,
    0x75,
    0x88,
    0xC8,
    0x05,
    0x8C,
    0x7E,
    0x17,
    0x11,
    0x3E,
    0x00,
    0x9E,
    0x72,
    0x81,
    0xD7,
    0x4D,
    0x33,
    0x1B,
    0x0F,
    0x91,
    0x7A,
    0xBD,
    0x8E,
    0xD4,
    0x07,
    0xFE,
    0x21,
    0x2B,
    0x72,
    0x2E,
    0xC9,
    0xB8,
    0xA9,
    0x00,
    0xCF,
    0x11,
    0x6A,
    0x11,
    0x8E,
    0x27,
    0x8B,
    0x8E,
    0x66,
    0x7E,
    0x7E,
    0x09,
    0xE6,
    0xB2,
    0xE7,
    0xB4,
    0xE1,
    0x22,
    0x60,
    0x18,
    0xC3,
    0xF4,
    0x66,
    0xC7,
    0xC2,
    0x87,
    0x59,
    0x53,
    0x53,
    0x79,
    0x60,
    0x2E,
    0x42,
    0x15,
    0x2E,
    0xA5,
    0x47,
    0x63,
    0xB4,
    0x6C,
    0x59,
    0xC3,
    0xC0,
    0x9C,
    0x5F,
    0xF8,
    0xDE,
    0x61,
    0x5F,
    0x96,
    0x89,
    0x98,
    0x71,
    0x5A,
    0xC6,
    0x09,
    0x46,
    0x56,
    0xD4,
    0xC7,
    0x06,
    0x05,
    0x39,
    0x1C,
    0x0D,
};
unsigned char std_tdes_192_cfb_out[128] = {
    0x11,
    0xA2,
    0x9F,
    0x9C,
    0x09,
    0xC7,
    0xBD,
    0xCA,
    0x9C,
    0x11,
    0xEE,
    0xF9,
    0x35,
    0xC7,
    0xB5,
    0xFC,
    0xAF,
    0xE9,
    0x68,
    0xD1,
    0x4A,
    0xAF,
    0x54,
    0x0B,
    0xC6,
    0x1B,
    0xAC,
    0xFA,
    0x70,
    0x9C,
    0xD0,
    0x21,
    0x9C,
    0x0E,
    0x2C,
    0x9E,
    0x7A,
    0x18,
    0x9E,
    0x88,
    0x0C,
    0x29,
    0x43,
    0xAB,
    0x6C,
    0x8C,
    0xFA,
    0xFB,
    0x34,
    0xE1,
    0x5B,
    0xD4,
    0xB0,
    0x2C,
    0xBF,
    0x95,
    0x91,
    0x63,
    0xE6,
    0x02,
    0x38,
    0xEF,
    0xF4,
    0x4C,
    0xAE,
    0x68,
    0x5D,
    0x9C,
    0x69,
    0xED,
    0xEF,
    0x82,
    0x42,
    0xF8,
    0x95,
    0x1B,
    0x61,
    0xDB,
    0x7E,
    0x36,
    0xB6,
    0x66,
    0x88,
    0x48,
    0xFF,
    0x15,
    0x70,
    0x8B,
    0x23,
    0x74,
    0xFF,
    0xAD,
    0x61,
    0x2A,
    0x47,
    0x8A,
    0xC2,
    0x44,
    0x31,
    0x7D,
    0x9E,
    0x32,
    0x19,
    0x9B,
    0xC5,
    0x5A,
    0xBB,
    0xDD,
    0xC7,
    0xA4,
    0x72,
    0xA2,
    0xAF,
    0xA8,
    0x49,
    0xC1,
    0x9E,
    0xC2,
    0xAC,
    0xBB,
    0x34,
    0x0C,
    0xB6,
    0x2E,
    0xEE,
    0xDD,
    0x18,
    0x22,
};
unsigned char std_tdes_192_ofb_out[128] = {
    0x11,
    0xA2,
    0x9F,
    0x9C,
    0x09,
    0xC7,
    0xBD,
    0xCA,
    0x43,
    0x42,
    0x47,
    0x00,
    0x29,
    0x02,
    0x0F,
    0x89,
    0x05,
    0xC9,
    0x62,
    0x98,
    0x04,
    0x17,
    0x74,
    0x21,
    0x84,
    0xD0,
    0xF6,
    0x33,
    0x29,
    0xEE,
    0x46,
    0xC9,
    0xCA,
    0x07,
    0x23,
    0x21,
    0xC7,
    0xC3,
    0x8C,
    0x3B,
    0x44,
    0x23,
    0x41,
    0xC0,
    0xAE,
    0xF7,
    0x19,
    0xD0,
    0x19,
    0x32,
    0x4B,
    0x24,
    0x62,
    0x3B,
    0x4E,
    0x1B,
    0xB5,
    0x81,
    0x83,
    0x92,
    0x2A,
    0x77,
    0xF2,
    0x96,
    0xE8,
    0xE4,
    0xBE,
    0x8D,
    0x01,
    0x05,
    0x35,
    0x74,
    0x69,
    0x2F,
    0x48,
    0xAD,
    0x98,
    0xA4,
    0xFD,
    0x5D,
    0x68,
    0xEC,
    0xA1,
    0x73,
    0x25,
    0x44,
    0x79,
    0xF0,
    0xBC,
    0xDB,
    0x20,
    0x8B,
    0x12,
    0x84,
    0xAA,
    0xD4,
    0xF3,
    0x1C,
    0xC1,
    0x9E,
    0x3F,
    0x22,
    0x2D,
    0x21,
    0x11,
    0x15,
    0xA7,
    0x5A,
    0x87,
    0x32,
    0x29,
    0x8E,
    0x72,
    0x72,
    0x79,
    0xA3,
    0x68,
    0x4E,
    0xBE,
    0xC7,
    0xFF,
    0x21,
    0x2C,
    0x21,
    0x41,
    0xFF,
    0xD1,
    0x44,
};
unsigned char std_tdes_192_ctr_out[128] = {
    0x11,
    0xA2,
    0x9F,
    0x9C,
    0x09,
    0xC7,
    0xBD,
    0xCA,
    0x48,
    0x37,
    0x4F,
    0x5D,
    0x4C,
    0x2D,
    0xA3,
    0x0F,
    0x06,
    0xC7,
    0x3D,
    0xA4,
    0x91,
    0xEB,
    0x3D,
    0xD6,
    0xC3,
    0x48,
    0x6F,
    0x7B,
    0xD6,
    0x16,
    0x2C,
    0x5A,
    0x2C,
    0x9F,
    0x1B,
    0xA6,
    0x32,
    0xEC,
    0x98,
    0xCA,
    0xD7,
    0x6C,
    0x94,
    0x4B,
    0x32,
    0x63,
    0x41,
    0xCE,
    0x2E,
    0xAB,
    0xBE,
    0x4B,
    0xC9,
    0xF9,
    0x55,
    0xFA,
    0x0F,
    0xD3,
    0x02,
    0x09,
    0xD6,
    0x0F,
    0x20,
    0xA9,
    0xD6,
    0x2C,
    0x79,
    0xB6,
    0x50,
    0xFF,
    0x5B,
    0xFF,
    0xC6,
    0xE9,
    0x58,
    0x44,
    0xDE,
    0x48,
    0x74,
    0x94,
    0xC9,
    0xAA,
    0xF2,
    0x1D,
    0x47,
    0xC8,
    0xDD,
    0x35,
    0x59,
    0x81,
    0xD0,
    0x65,
    0x14,
    0x80,
    0x35,
    0xA4,
    0x0B,
    0x1B,
    0xA4,
    0x21,
    0x02,
    0xA2,
    0x05,
    0xFE,
    0xEA,
    0x89,
    0x5E,
    0x2D,
    0x6F,
    0x2B,
    0x6A,
    0x47,
    0xC4,
    0x02,
    0x56,
    0x1A,
    0xD9,
    0x41,
    0xD9,
    0xBF,
    0xF5,
    0xFE,
    0x6A,
    0x34,
    0xEF,
    0x47,
    0x50,
    0xBA,
};

unsigned int TDES_192_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== 3DES-3key test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_192, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_tdes_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_tdes_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_tdes_192_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    fflush(stdout);
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_192, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_tdes_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_tdes_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_192, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_tdes_192_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    //#ifdef SKE_LP_DMA_FUNCTION
    //  printf("\r\n\r\n =================== 3DES-3key DMA test ==================== ");fflush(stdout);
    //
    //#if defined (SUPPORT_SKE_MODE_ECB)
    //  ret  = SKE_DMA_test(SKE_ALG_TDES_192, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL,   std_tdes_192_ecb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CBC)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_192, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_tdes_192_cbc_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_192, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_tdes_192_cfb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_OFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_192, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_tdes_192_ofb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_192, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_tdes_192_ctr_out);
    //#endif
    //
    //  if(ret)
    //  {
    //      return 1;
    //  }
    //#endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_128
unsigned char std_tdes_eee_128_ecb_out[128] = {
    0x8A,
    0xFB,
    0xFC,
    0x63,
    0x92,
    0x09,
    0x9F,
    0xF0,
    0xB5,
    0xD4,
    0xDD,
    0x33,
    0x9B,
    0x37,
    0xD7,
    0xFD,
    0xAD,
    0x85,
    0x0B,
    0xD6,
    0x97,
    0x11,
    0xE2,
    0x4B,
    0x3A,
    0x61,
    0xBD,
    0x30,
    0x78,
    0x16,
    0x03,
    0x42,
    0x17,
    0xDA,
    0xA4,
    0x47,
    0xC8,
    0x91,
    0x84,
    0xB7,
    0x12,
    0x67,
    0xAD,
    0x6E,
    0xBC,
    0x35,
    0xFC,
    0xF1,
    0x35,
    0x5F,
    0x2C,
    0xA6,
    0x73,
    0x2A,
    0x8F,
    0x97,
    0xF0,
    0x68,
    0x37,
    0x6C,
    0xF6,
    0xD1,
    0xBC,
    0x39,
    0x96,
    0xF9,
    0x01,
    0x2E,
    0xF0,
    0x4D,
    0xBD,
    0x90,
    0x86,
    0xA6,
    0x2A,
    0xA8,
    0xB8,
    0x95,
    0x9B,
    0x41,
    0x98,
    0xEE,
    0xCA,
    0x2E,
    0xFB,
    0xC5,
    0xD4,
    0x4D,
    0x94,
    0xC4,
    0xA0,
    0x2C,
    0x7C,
    0xC2,
    0x1E,
    0xC8,
    0xF8,
    0x6A,
    0x3B,
    0x7E,
    0x9D,
    0x92,
    0x28,
    0x46,
    0x8C,
    0x5B,
    0xF1,
    0x8F,
    0x50,
    0xF9,
    0xDF,
    0x04,
    0xF2,
    0x69,
    0x79,
    0x7D,
    0x14,
    0x05,
    0x9C,
    0x7C,
    0x4C,
    0x28,
    0x78,
    0xEA,
    0xD6,
    0x5A,
    0x46,
    0x5C,
};
unsigned char std_tdes_eee_128_cbc_out[128] = {
    0xEF,
    0xE9,
    0x0F,
    0x1B,
    0xDB,
    0xC8,
    0x97,
    0x06,
    0xEC,
    0xA8,
    0x98,
    0x95,
    0x65,
    0x1C,
    0x75,
    0xD8,
    0xD2,
    0x4D,
    0x80,
    0x99,
    0xCF,
    0xCF,
    0xAF,
    0xB9,
    0x09,
    0x3F,
    0x10,
    0xAA,
    0xBB,
    0x82,
    0xB6,
    0xCD,
    0x3B,
    0xFE,
    0x72,
    0xC6,
    0x91,
    0x7A,
    0xF9,
    0x14,
    0x6C,
    0x66,
    0x1D,
    0x87,
    0x58,
    0xAD,
    0x2E,
    0x36,
    0x28,
    0x80,
    0x49,
    0x77,
    0x83,
    0x2E,
    0x79,
    0x8A,
    0x11,
    0x0E,
    0x1B,
    0x47,
    0x21,
    0xC5,
    0x81,
    0x7A,
    0x74,
    0xA6,
    0x75,
    0xE8,
    0x0E,
    0xE2,
    0x61,
    0x69,
    0x56,
    0xA3,
    0x36,
    0x0E,
    0x76,
    0x43,
    0xEE,
    0xC3,
    0x51,
    0xF5,
    0x21,
    0x6A,
    0x08,
    0x36,
    0x50,
    0x0B,
    0x7F,
    0xDB,
    0xCB,
    0x21,
    0x33,
    0x21,
    0x0D,
    0x77,
    0xB9,
    0x94,
    0xCA,
    0xBD,
    0x06,
    0xA1,
    0x67,
    0xA1,
    0x5D,
    0xB0,
    0xEB,
    0x1D,
    0xB3,
    0xD2,
    0x8B,
    0x0B,
    0xB8,
    0x66,
    0x77,
    0x37,
    0xCA,
    0x3F,
    0xE8,
    0x8D,
    0xDF,
    0x18,
    0x22,
    0x97,
    0x38,
    0x38,
    0x7C,
    0x62,
};
unsigned char std_tdes_eee_128_cfb_out[128] = {
    0x5D,
    0x23,
    0x7A,
    0x92,
    0x62,
    0xF2,
    0xCE,
    0x57,
    0x39,
    0x6E,
    0x48,
    0x29,
    0xDA,
    0x6E,
    0x1A,
    0x37,
    0x17,
    0x4F,
    0x0F,
    0xCA,
    0x25,
    0xE3,
    0xFC,
    0xD9,
    0x74,
    0x48,
    0x38,
    0x1A,
    0x43,
    0x2D,
    0x13,
    0x70,
    0x23,
    0xC3,
    0x03,
    0x30,
    0xC7,
    0x6D,
    0xD4,
    0x77,
    0xF7,
    0xC2,
    0xD9,
    0x0E,
    0x55,
    0x5B,
    0xCE,
    0xBF,
    0xDD,
    0x35,
    0x80,
    0x5A,
    0xC1,
    0x00,
    0x78,
    0x29,
    0xF2,
    0xD0,
    0x95,
    0xA2,
    0x61,
    0xC4,
    0x2E,
    0xDC,
    0x4D,
    0x81,
    0xBE,
    0xC6,
    0xFC,
    0xBB,
    0x3D,
    0xDE,
    0x06,
    0x69,
    0xA2,
    0xDA,
    0x90,
    0x71,
    0x17,
    0x5A,
    0x9D,
    0xB1,
    0x75,
    0x40,
    0xD0,
    0x95,
    0x0A,
    0x2D,
    0x04,
    0xAA,
    0x0E,
    0x11,
    0xB6,
    0x7E,
    0x80,
    0xE0,
    0x3E,
    0xA8,
    0x9A,
    0x1F,
    0x41,
    0x9F,
    0xEC,
    0x55,
    0x14,
    0x16,
    0xEE,
    0xEA,
    0x8D,
    0x28,
    0xF4,
    0x34,
    0x9D,
    0x5C,
    0xF6,
    0x84,
    0x97,
    0x06,
    0x82,
    0xA4,
    0x9B,
    0x76,
    0xE1,
    0x80,
    0x51,
    0x84,
    0xF2,
    0x8A,
};
unsigned char std_tdes_eee_128_ofb_out[128] = {
    0x5D,
    0x23,
    0x7A,
    0x92,
    0x62,
    0xF2,
    0xCE,
    0x57,
    0x97,
    0xDF,
    0x19,
    0x4C,
    0x43,
    0xCE,
    0xF2,
    0x6F,
    0xA4,
    0xA9,
    0x0E,
    0x9F,
    0x8D,
    0xF7,
    0xE2,
    0xF4,
    0xE9,
    0x05,
    0x6C,
    0x6A,
    0x62,
    0xAA,
    0x76,
    0x2C,
    0xB7,
    0xF9,
    0x16,
    0xF2,
    0x93,
    0xBC,
    0x70,
    0xCA,
    0x3F,
    0x5E,
    0x96,
    0xE5,
    0xAA,
    0x3F,
    0xFD,
    0x86,
    0x4C,
    0x29,
    0x3D,
    0x5F,
    0x58,
    0xB0,
    0xCA,
    0x2A,
    0xE1,
    0x9F,
    0x5A,
    0xFC,
    0xF4,
    0x8E,
    0xF8,
    0x84,
    0x9A,
    0xDC,
    0x88,
    0x89,
    0x2E,
    0xA8,
    0x1E,
    0x0E,
    0x1D,
    0x5B,
    0xD6,
    0xD6,
    0x18,
    0xC9,
    0xB4,
    0x02,
    0xF6,
    0xA0,
    0x35,
    0xFB,
    0xED,
    0x04,
    0xBD,
    0x14,
    0x85,
    0x74,
    0x48,
    0x41,
    0xB8,
    0x32,
    0xD0,
    0xD8,
    0x62,
    0xD8,
    0xD2,
    0x02,
    0x48,
    0x9D,
    0x51,
    0x49,
    0xC3,
    0x2B,
    0x66,
    0xF6,
    0xF2,
    0xE6,
    0x8C,
    0x52,
    0xA3,
    0xCB,
    0x10,
    0x61,
    0x02,
    0x7F,
    0x88,
    0x6B,
    0x2C,
    0x7F,
    0x2A,
    0x39,
    0xE4,
    0x4E,
    0x3F,
    0x08,
};
unsigned char std_tdes_eee_128_ctr_out[128] = {
    0x5D,
    0x23,
    0x7A,
    0x92,
    0x62,
    0xF2,
    0xCE,
    0x57,
    0xD0,
    0x6C,
    0xEA,
    0x47,
    0x74,
    0x63,
    0x04,
    0x20,
    0x00,
    0x58,
    0x02,
    0xC7,
    0x69,
    0xE1,
    0xE3,
    0x5A,
    0x35,
    0xB6,
    0xE7,
    0x22,
    0xC9,
    0x48,
    0xA6,
    0x12,
    0x49,
    0xE0,
    0x63,
    0x75,
    0x35,
    0x82,
    0x0F,
    0x46,
    0x9B,
    0x7A,
    0x2B,
    0x7A,
    0xDF,
    0xE0,
    0x8B,
    0x5B,
    0x43,
    0x0C,
    0xDE,
    0x09,
    0xEA,
    0x54,
    0xEB,
    0x17,
    0xD6,
    0x45,
    0x85,
    0x2F,
    0x66,
    0xFC,
    0xB9,
    0x42,
    0x81,
    0xFA,
    0xCF,
    0xB5,
    0xF0,
    0x96,
    0xC4,
    0x4E,
    0xA7,
    0xAC,
    0x3C,
    0x43,
    0xD4,
    0xE1,
    0x05,
    0x3E,
    0x33,
    0x75,
    0xEC,
    0xC1,
    0xF1,
    0xB2,
    0x6C,
    0x91,
    0xC1,
    0x7A,
    0x45,
    0xCF,
    0x40,
    0xC1,
    0x36,
    0x6F,
    0x51,
    0x41,
    0xFB,
    0x8F,
    0x46,
    0xF5,
    0x9E,
    0xC9,
    0x7E,
    0x2E,
    0x26,
    0xAE,
    0xC8,
    0xC7,
    0x9E,
    0x71,
    0x0F,
    0x23,
    0xE1,
    0x3A,
    0xE7,
    0xBF,
    0xCC,
    0xB4,
    0xD7,
    0x23,
    0x63,
    0xCD,
    0xC2,
    0x51,
    0xA3,
    0x01,
};

unsigned int TDES_EEE_128_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== 3DES_EEE-2key test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_tdes_eee_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_tdes_eee_128_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_128_ctr_out);
    #endif

    if (ret) {
        return 1;
    }


    //#ifdef SKE_LP_DMA_FUNCTION
    //  printf("\r\n\r\n =================== 3DES_EEE-2key DMA test ==================== ");fflush(stdout);
    //
    //#if defined (SUPPORT_SKE_MODE_ECB)
    //  ret  = SKE_DMA_test(SKE_ALG_TDES_EEE_128, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL,   std_tdes_eee_128_ecb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CBC)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_tdes_eee_128_cbc_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_tdes_eee_128_cfb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_OFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_128, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_tdes_eee_128_ofb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_128, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_tdes_eee_128_ctr_out);
    //#endif
    //
    //  if(ret)
    //  {
    //      return 1;
    //  }
    //#endif

    return 0;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_192
unsigned char std_tdes_eee_192_ecb_out[128] = {
    0xB8,
    0x36,
    0x6C,
    0x7C,
    0xCE,
    0xF0,
    0x9B,
    0xFC,
    0x3F,
    0x26,
    0xEA,
    0x3F,
    0xF5,
    0x18,
    0x6D,
    0xE7,
    0x81,
    0x91,
    0x93,
    0x56,
    0x4E,
    0x92,
    0x15,
    0xBA,
    0x33,
    0xCB,
    0x20,
    0x1E,
    0x1E,
    0x32,
    0xF1,
    0xA0,
    0x38,
    0x04,
    0x7D,
    0xC5,
    0x8B,
    0xDB,
    0x22,
    0x22,
    0x4E,
    0x1A,
    0x98,
    0x2C,
    0xB4,
    0xBD,
    0x8E,
    0x87,
    0x2C,
    0xC2,
    0xE6,
    0xD4,
    0x90,
    0x4B,
    0x79,
    0xE7,
    0x5D,
    0x54,
    0x32,
    0x92,
    0x27,
    0xA1,
    0x38,
    0x15,
    0xE2,
    0x61,
    0xD3,
    0xA3,
    0xC8,
    0x8F,
    0x7C,
    0xBC,
    0x7B,
    0xEA,
    0xDE,
    0xD3,
    0x7C,
    0x53,
    0xAD,
    0x94,
    0x23,
    0xF1,
    0x8E,
    0x84,
    0xE8,
    0x16,
    0x09,
    0x3C,
    0xF4,
    0x3A,
    0xD5,
    0x7B,
    0x91,
    0x5E,
    0x43,
    0x64,
    0xFD,
    0x8A,
    0x8E,
    0x88,
    0xE5,
    0x2C,
    0xAA,
    0x61,
    0x96,
    0x76,
    0xE8,
    0xC8,
    0x22,
    0x24,
    0x79,
    0x65,
    0x67,
    0xFB,
    0x59,
    0x80,
    0x97,
    0x1E,
    0x03,
    0xA2,
    0x71,
    0x63,
    0xD8,
    0xFA,
    0x4F,
    0x1C,
    0xCA,
    0xFC,
};
unsigned char std_tdes_eee_192_cbc_out[128] = {
    0xE9,
    0xBF,
    0xF6,
    0xCA,
    0xF3,
    0x31,
    0xD0,
    0x92,
    0x18,
    0x84,
    0x0D,
    0x90,
    0xEE,
    0x6C,
    0x93,
    0x00,
    0x72,
    0x05,
    0x4A,
    0x37,
    0x2A,
    0x92,
    0x6A,
    0xE9,
    0x76,
    0xEB,
    0x96,
    0x8E,
    0x57,
    0x33,
    0xE2,
    0x70,
    0x0B,
    0x8F,
    0x69,
    0xFC,
    0x61,
    0xF5,
    0x5A,
    0x4F,
    0x7E,
    0xC9,
    0x45,
    0xDE,
    0xD9,
    0x5E,
    0x15,
    0x32,
    0x89,
    0x9E,
    0xD3,
    0x5C,
    0xB5,
    0x6F,
    0xD3,
    0x6A,
    0x14,
    0xB7,
    0x8E,
    0x3B,
    0x85,
    0x01,
    0x3A,
    0x29,
    0x46,
    0x9B,
    0x61,
    0x33,
    0x08,
    0x73,
    0x14,
    0x81,
    0x08,
    0xD9,
    0xAA,
    0xF4,
    0x45,
    0x48,
    0xBC,
    0xC3,
    0xFB,
    0x37,
    0x54,
    0x28,
    0x55,
    0x80,
    0x99,
    0x64,
    0xCC,
    0x2F,
    0xA8,
    0xE7,
    0x66,
    0x8C,
    0x76,
    0xCB,
    0x72,
    0x80,
    0xB9,
    0x76,
    0x97,
    0x71,
    0xDE,
    0x6A,
    0x9E,
    0xD8,
    0x87,
    0x7F,
    0x9D,
    0xCE,
    0x4C,
    0x3A,
    0x27,
    0x50,
    0xD4,
    0xBC,
    0xA1,
    0xA4,
    0x80,
    0x85,
    0xF0,
    0x14,
    0xC3,
    0x6E,
    0x54,
    0x5A,
    0x9B,
    0x23};
unsigned char std_tdes_eee_192_cfb_out[128] = {
    0xCC,
    0xE6,
    0x89,
    0x62,
    0xE5,
    0x52,
    0xDD,
    0x45,
    0xDA,
    0x84,
    0x9E,
    0x64,
    0x56,
    0xA5,
    0x2C,
    0x08,
    0x64,
    0xE3,
    0x34,
    0x75,
    0xB0,
    0x18,
    0xE2,
    0xBD,
    0xEB,
    0xF1,
    0x7C,
    0xAD,
    0xF3,
    0x8C,
    0x8D,
    0x4C,
    0x18,
    0x94,
    0x85,
    0x2F,
    0xAE,
    0x9A,
    0xD2,
    0x09,
    0x77,
    0xFF,
    0x98,
    0xE1,
    0x3A,
    0xAE,
    0xE5,
    0x9E,
    0xFD,
    0xF8,
    0xC0,
    0xC7,
    0xE4,
    0xAE,
    0x4B,
    0x43,
    0xAF,
    0xAB,
    0x9F,
    0x0F,
    0xFE,
    0x50,
    0x32,
    0x8C,
    0xE5,
    0xDC,
    0x3D,
    0xC0,
    0xFE,
    0x2C,
    0xD3,
    0xD8,
    0x60,
    0x6D,
    0xB2,
    0x64,
    0xF9,
    0x8A,
    0x28,
    0xB7,
    0xE5,
    0xA3,
    0x67,
    0x98,
    0xCE,
    0x33,
    0x58,
    0xE7,
    0x97,
    0xDD,
    0xF5,
    0x23,
    0xA4,
    0x25,
    0x08,
    0x7A,
    0x5D,
    0xFF,
    0xFD,
    0x74,
    0x11,
    0x32,
    0x6A,
    0xE1,
    0xF8,
    0x0A,
    0x17,
    0x57,
    0xD3,
    0x8B,
    0x1C,
    0x7E,
    0xBA,
    0x45,
    0x43,
    0xC5,
    0x50,
    0x23,
    0x39,
    0x1F,
    0x3B,
    0xFA,
    0x22,
    0xB6,
    0x8D,
    0x75,
    0x49,
    0x45};
unsigned char std_tdes_eee_192_ofb_out[128] = {
    0xCC,
    0xE6,
    0x89,
    0x62,
    0xE5,
    0x52,
    0xDD,
    0x45,
    0xC7,
    0x8D,
    0x08,
    0x9A,
    0x58,
    0x3C,
    0x4C,
    0x69,
    0x85,
    0xB2,
    0xBA,
    0x31,
    0x3A,
    0xA6,
    0x0B,
    0xEB,
    0x10,
    0x0F,
    0x9C,
    0x31,
    0x5F,
    0x82,
    0xBF,
    0xE6,
    0xBD,
    0xAE,
    0xC7,
    0xD9,
    0x2F,
    0x64,
    0x5F,
    0xCC,
    0xE5,
    0x08,
    0xC0,
    0xE0,
    0x49,
    0x4E,
    0xA1,
    0xFE,
    0x28,
    0x1E,
    0x01,
    0xE0,
    0x44,
    0x6F,
    0xC1,
    0xFD,
    0xAD,
    0x4E,
    0x8C,
    0x38,
    0x61,
    0xD4,
    0xE7,
    0x54,
    0x8D,
    0xAB,
    0x64,
    0x37,
    0x8F,
    0x74,
    0x75,
    0x36,
    0xC7,
    0x98,
    0xC2,
    0xCD,
    0x51,
    0x81,
    0x57,
    0x8B,
    0x7A,
    0xEF,
    0xF3,
    0x27,
    0xA3,
    0x70,
    0x04,
    0x09,
    0x46,
    0xA9,
    0xC2,
    0xEC,
    0xE9,
    0x75,
    0x46,
    0x56,
    0x6C,
    0xCC,
    0x88,
    0x60,
    0x7F,
    0x4F,
    0xE9,
    0x58,
    0x4D,
    0xB0,
    0xBC,
    0xA5,
    0x53,
    0x1F,
    0xCB,
    0x69,
    0x47,
    0x46,
    0xF4,
    0x80,
    0xB2,
    0xA5,
    0xF9,
    0x9A,
    0x36,
    0xA0,
    0x7A,
    0x1D,
    0x79,
    0xAF,
    0x95,
    0x6D};
unsigned char std_tdes_eee_192_ctr_out[128] = {
    0xCC,
    0xE6,
    0x89,
    0x62,
    0xE5,
    0x52,
    0xDD,
    0x45,
    0xFF,
    0x6C,
    0x40,
    0x73,
    0x37,
    0x11,
    0x21,
    0x46,
    0x3D,
    0xE3,
    0x71,
    0xDC,
    0x98,
    0xCB,
    0x6C,
    0xB5,
    0xD6,
    0xFC,
    0x09,
    0x0B,
    0xA4,
    0xFB,
    0xBE,
    0x82,
    0xE7,
    0xA7,
    0x1E,
    0x52,
    0xFF,
    0x77,
    0xA4,
    0x96,
    0x67,
    0xE8,
    0xEE,
    0x72,
    0xB3,
    0x3C,
    0xE1,
    0xD9,
    0xF5,
    0x8C,
    0xAE,
    0x72,
    0x94,
    0x3C,
    0xF1,
    0xD1,
    0x9E,
    0x7C,
    0x65,
    0x6D,
    0xC1,
    0x9C,
    0x05,
    0xF2,
    0x6D,
    0xC8,
    0xDC,
    0x2E,
    0x67,
    0x67,
    0x27,
    0x12,
    0xA1,
    0x14,
    0x12,
    0x8B,
    0x68,
    0x2D,
    0x61,
    0x1E,
    0xBB,
    0xC3,
    0x84,
    0x8C,
    0x16,
    0x05,
    0xF2,
    0x9E,
    0x19,
    0x33,
    0x1D,
    0x50,
    0x50,
    0x98,
    0x82,
    0x39,
    0x2B,
    0x85,
    0xE7,
    0x3C,
    0x95,
    0xC8,
    0x2E,
    0xB6,
    0xD7,
    0xBA,
    0x28,
    0xDA,
    0xB5,
    0x52,
    0x53,
    0xDD,
    0x0D,
    0xED,
    0x4A,
    0xA2,
    0xEB,
    0x4F,
    0x5B,
    0x02,
    0xD5,
    0xAB,
    0x86,
    0xF6,
    0x9B,
    0xBF,
    0x99,
    0x5E};

unsigned int TDES_EEE_192_Test(void)
{
    unsigned int ret = 0;

    printf("\r\n\r\n =================== 3DES_EEE 3key test ==================== ");

    printf("\r\n 1. input&output aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_ECB, 1, std_in, 128, std_key, 0, NULL, std_tdes_eee_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_OFB, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CTR, 1, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_ctr_out); /**/
    #endif

    if (ret) {
        return 1;
    }


    printf("\r\n\r\n 2. input&output not aligned by word test");
    #if defined(SUPPORT_SKE_MODE_ECB)
    ret = SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_ECB, 0, std_in, 128, std_key, 0, NULL, std_tdes_eee_192_ecb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CBC, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_cbc_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_cfb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_OFB, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_ofb_out);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ret |= SKE_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CTR, 0, std_in, 128, std_key, 0, std_iv, std_tdes_eee_192_ctr_out); /**/
    #endif

    if (ret) {
        return 1;
    }


    //#ifdef SKE_LP_DMA_FUNCTION
    //  printf("\r\n\r\n =================== 3DES_EEE 3key DMA test ==================== ");//fflush(stdout);
    //
    //#if defined (SUPPORT_SKE_MODE_ECB)
    //  ret  = SKE_DMA_test(SKE_ALG_TDES_EEE_192, SKE_MODE_ECB, std_in, 32, std_key, 0, NULL,   std_tdes_eee_192_ecb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CBC)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_tdes_eee_192_cbc_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CFB, std_in, 32, std_key, 0, std_iv, std_tdes_eee_192_cfb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_OFB)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_192, SKE_MODE_OFB, std_in, 32, std_key, 0, std_iv, std_tdes_eee_192_ofb_out);
    //#endif
    //
    //#if defined (SUPPORT_SKE_MODE_CTR)
    //  ret |= SKE_DMA_test(SKE_ALG_TDES_EEE_192, SKE_MODE_CTR, std_in, 32, std_key, 0, std_iv, std_tdes_eee_192_ctr_out);
    //#endif
    //
    //  if(ret)
    //  {
    //      return 1;
    //  }
    //#endif

    return 0;
}
#endif


unsigned int speed_get_round_by_alg(SKE_ALG alg)
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

unsigned int ske_speed_test_internal(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, unsigned int round, unsigned int once_bytes)
{
    char *name_alg[] = {
        "DES",
        "TDES_128",
        "TDES_192",
        "TDES_EEE_128",
        "TDES_EEE_192",
        "AES_128",
        "AES_192",
        "AES_256",
        "SM4",
    };
    char         *name_mode[]   = {"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
    char         *name_crypto[] = {"ENC", "DEC"};
    unsigned char in[8192];
    unsigned char key[64];
    unsigned char iv[16];
    unsigned int  i;
    unsigned int  ret;

    //for hardware ECB/CBC/CFB/OFB/CTR

    uint32_sleep(0xFFFF, 1);

    printf("\r\n===================== %s %s %s begin =====================", name_alg[alg], name_mode[mode], name_crypto[crypto]);

#ifdef SKE_SPEED_TEST_BY_TIMER
    startP();
#endif

    ret = ske_lp_init(alg, mode, crypto, key, 0, iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n init error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_update_blocks(in, in, once_bytes);
        if (SKE_SUCCESS != ret) {
            printf("\r\n update error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

#ifdef SKE_SPEED_TEST_BY_TIMER
    endP(0, once_bytes, round);
#else
    printf("\r\n finished");
#endif

    return 0;
}

unsigned int ske_speed_test_by_alg(SKE_ALG alg)
{
    unsigned int bytes = 4096;
    unsigned int round = speed_get_round_by_alg(alg);

#ifndef SKE_SPEED_TEST_BY_TIMER
    round *= 100;
#endif

#if defined(SUPPORT_SKE_MODE_ECB)
    ske_speed_test_internal(alg, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round, bytes);
    ske_speed_test_internal(alg, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, round, bytes);
#endif

#if defined(SUPPORT_SKE_MODE_CBC)
    ske_speed_test_internal(alg, SKE_MODE_CBC, SKE_CRYPTO_ENCRYPT, round, bytes);
    ske_speed_test_internal(alg, SKE_MODE_CBC, SKE_CRYPTO_DECRYPT, round, bytes);
#endif

#if defined(SUPPORT_SKE_MODE_CFB)
    ske_speed_test_internal(alg, SKE_MODE_CFB, SKE_CRYPTO_ENCRYPT, round, bytes);
    ske_speed_test_internal(alg, SKE_MODE_CFB, SKE_CRYPTO_DECRYPT, round, bytes);
#endif

#if defined(SUPPORT_SKE_MODE_OFB)
    ske_speed_test_internal(alg, SKE_MODE_OFB, SKE_CRYPTO_ENCRYPT, round, bytes);
    ske_speed_test_internal(alg, SKE_MODE_OFB, SKE_CRYPTO_DECRYPT, round, bytes);
#endif

#if defined(SUPPORT_SKE_MODE_CTR)
    ske_speed_test_internal(alg, SKE_MODE_CTR, SKE_CRYPTO_ENCRYPT, round, bytes);
    ske_speed_test_internal(alg, SKE_MODE_CTR, SKE_CRYPTO_DECRYPT, round, bytes);
#endif

    return 0;
}

unsigned int ske_speed_test(void)
{
    unsigned int round;

#if 1
    #ifdef SUPPORT_SKE_DES
    ske_speed_test_by_alg(SKE_ALG_DES);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_TDES_192
    ske_speed_test_by_alg(SKE_ALG_TDES_192);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_AES_128
    ske_speed_test_by_alg(SKE_ALG_AES_128);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_AES_192
    ske_speed_test_by_alg(SKE_ALG_AES_192);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_AES_256
    ske_speed_test_by_alg(SKE_ALG_AES_256);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_SM4
    ske_speed_test_by_alg(SKE_ALG_SM4);
    #endif
#endif

#if 1
    #ifdef SUPPORT_SKE_AES_128
    round = speed_get_round_by_alg(SKE_ALG_AES_128);
        #ifndef SKE_SPEED_TEST_BY_TIMER
    round *= 100;
        #endif

    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 64, 32);
    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 8, 256);
    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 4, 512);
    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 2, 1024);
    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round / 2, 4096);
    ske_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round / 4, 8192);
    #endif
#endif

    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
unsigned int ske_dma_speed_test_internal(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, unsigned int round, unsigned int once_words)
{
    char *name_alg[] = {
        "DES",
        "TDES_128",
        "TDES_192",
        "TDES_EEE_128",
        "TDES_EEE_192",
        "AES_128",
        "AES_192",
        "AES_256",
        "SM4",
    };
    char         *name_mode[]   = {"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
    char         *name_crypto[] = {"ENC", "DEC"};
    unsigned int *in            = (unsigned int *)DMA_RAM_BASE;
    unsigned char key[64];
    unsigned char iv[16];
    unsigned int  i;
    unsigned int  ret;

    //for hardware ECB/CBC/CFB/OFB/CTR

    uint32_sleep(0xFFFF, 1);

    printf("\r\n===================== %s %s %s DMA begin =====================", name_alg[alg], name_mode[mode], name_crypto[crypto]);

    #ifdef SKE_SPEED_TEST_BY_TIMER
    startP();
    #endif

    ret = ske_lp_dma_init(alg, mode, crypto, key, 0, iv);
    if (SKE_SUCCESS != ret) {
        printf("\r\n dma init error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_dma_update_blocks(in, in, once_words, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n dma update error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    #ifdef SKE_SPEED_TEST_BY_TIMER
    endP(0, once_words * 4, round);
    #else
    printf("\r\n finished");
    #endif

    return 0;
}

unsigned int ske_dma_speed_test_by_alg(SKE_ALG alg)
{
    unsigned int words = 16384 / 4;
    unsigned int round = speed_get_round_by_alg(alg);

    #ifndef SKE_SPEED_TEST_BY_TIMER
    round *= 30;
    #endif

    #if defined(SUPPORT_SKE_MODE_ECB)
    ske_dma_speed_test_internal(alg, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round, words);
    ske_dma_speed_test_internal(alg, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, round, words);
    #endif

    #if defined(SUPPORT_SKE_MODE_CBC)
    ske_dma_speed_test_internal(alg, SKE_MODE_CBC, SKE_CRYPTO_ENCRYPT, round, words);
    ske_dma_speed_test_internal(alg, SKE_MODE_CBC, SKE_CRYPTO_DECRYPT, round, words);
    #endif

    #if defined(SUPPORT_SKE_MODE_CFB)
    ske_dma_speed_test_internal(alg, SKE_MODE_CFB, SKE_CRYPTO_ENCRYPT, round, words);
    ske_dma_speed_test_internal(alg, SKE_MODE_CFB, SKE_CRYPTO_DECRYPT, round, words);
    #endif

    #if defined(SUPPORT_SKE_MODE_OFB)
    ske_dma_speed_test_internal(alg, SKE_MODE_OFB, SKE_CRYPTO_ENCRYPT, round, words);
    ske_dma_speed_test_internal(alg, SKE_MODE_OFB, SKE_CRYPTO_DECRYPT, round, words);
    #endif

    #if defined(SUPPORT_SKE_MODE_CTR)
    ske_dma_speed_test_internal(alg, SKE_MODE_CTR, SKE_CRYPTO_ENCRYPT, round, words);
    ske_dma_speed_test_internal(alg, SKE_MODE_CTR, SKE_CRYPTO_DECRYPT, round, words);
    #endif

    return 0;
}

unsigned int ske_dma_speed_test(void)
{
    unsigned int round;

    #if 1
        #ifdef SUPPORT_SKE_DES
    ske_dma_speed_test_by_alg(SKE_ALG_DES);
        #endif
    #endif

    #if 1
        #ifdef SUPPORT_SKE_AES_128
    ske_dma_speed_test_by_alg(SKE_ALG_AES_128);
        #endif
    #endif

    #if 1
        #ifdef SUPPORT_SKE_AES_192
    ske_dma_speed_test_by_alg(SKE_ALG_AES_192);
        #endif
    #endif

    #if 1
        #ifdef SUPPORT_SKE_AES_256
    ske_dma_speed_test_by_alg(SKE_ALG_AES_256);
        #endif
    #endif

    #if 1
        #ifdef SUPPORT_SKE_SM4
    ske_dma_speed_test_by_alg(SKE_ALG_SM4);
        #endif
    #endif

    #if 1
        #ifdef SUPPORT_SKE_AES_128
    round = speed_get_round_by_alg(SKE_ALG_AES_128);
            #ifndef SKE_SPEED_TEST_BY_TIMER
    round *= 100;
            #endif

    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 128, 32 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 16, 256 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 8, 512 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 4, 1024 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round * 1, 4096 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round / 2, 8192 / 4);
    ske_dma_speed_test_internal(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, round / 4, 16384 / 4);
        #endif
    #endif

    return 0;
}
#endif


unsigned int ske_lp_aes128_ecb_sample(void);
unsigned int ske_lp_aes128_cbc_sample(void);
unsigned int ske_lp_aes128_gcm_sample(void);

unsigned int SKE_LP_CBC_MAC_all_test(void);
unsigned int SKE_LP_CMAC_all_test(void);
unsigned int SKE_LP_XTS_all_Test(void);

//unsigned int SKE_LP_GCM_all_test(void);
//unsigned int SKE_LP_GMAC_all_test(void);
//unsigned int SKE_LP_XTS_all_Test(void);
//unsigned int SKE_LP_CCM_all_Test(void);

unsigned int SKE_LP_AES_XCBC_MAC_96_all_test(void);

unsigned int SKE_all_test(void)
{
#if 0
    if(ske_speed_test())
        return 1;
#endif

#ifdef SKE_LP_DMA_FUNCTION
    #if 0
    if(ske_dma_speed_test())
        return 1;
    #endif
#endif

/**/
//#ifdef SUPPORT_SKE_AES_128
//#ifdef SUPPORT_SKE_MODE_ECB
//  if(ske_lp_aes128_ecb_sample())
//      return 1;
//#endif
//
//#ifdef SUPPORT_SKE_MODE_CBC
//  if(ske_lp_aes128_cbc_sample())
//      return 1;
//#endif
//
//#if defined(SUPPORT_SKE_MODE_GCM)
//  if(ske_lp_aes128_gcm_sample())
//      return 1;
//#endif
//#endif

/**/
#ifdef SUPPORT_SKE_MODE_CBC_MAC
    if (SKE_LP_CBC_MAC_all_test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_CMAC
    if (SKE_LP_CMAC_all_test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_XCBC_MAC_96
    if (SKE_LP_AES_XCBC_MAC_96_all_test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_GCM
    if (SKE_LP_GCM_all_test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_GMAC
    if (SKE_LP_GMAC_all_test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_CCM
    if (SKE_LP_CCM_all_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_XTS
    if (SKE_LP_XTS_all_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_SM4
    if (SM4_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_128
    if (AES_128_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_192
    if (AES_192_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_256
    if (AES_256_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_DES
    if (DES_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_128
    if (TDES_128_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_192
    if (TDES_192_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
    if (TDES_EEE_128_Test()) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
    if (TDES_EEE_192_Test()) {
        return 1;
    }
#endif

    /**/
    printf("\r\n\r\n SKE LP test over! \r\n");

    return 0;
}

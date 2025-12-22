/********************************************************************************************************
 * @file    ske_cbc_mac_test.c
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
#include "lib/include/crypto_common/utility.h"
#if defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X) || defined(MCU_CORE_TL323X)
#include "lib/include/ske/ske_cbc_mac.h"
#endif
#include "common.h"
#include "app_test.h"



//#define CBC_MAC_SPEED_TEST_BY_TIMER

#ifdef CBC_MAC_SPEED_TEST_BY_TIMER
extern unsigned int startP();
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif
extern unsigned int speed_get_round_by_alg(SKE_ALG alg);


#ifdef SUPPORT_SKE_MODE_CBC_MAC

//extern unsigned int ske_get_rand_number(unsigned int max_number);
extern void ske_call_manage(void);
static void get_rand_(unsigned char *rand, unsigned int bytes)
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

unsigned int ske_cbc_mac_test_internal(SKE_ALG alg,  unsigned char *std_key, unsigned short sp_key_idx, unsigned char mac_bytes,
         unsigned char *std_mac1,  unsigned char *std_mac2,  unsigned char *std_mac3)
{
    unsigned char message[500];
    unsigned char mac[16];
    SKE_CBC_MAC_CTX ctx[1];
    char *name[]={"DES","TDES_128","TDES_192","TDES_EEE_128","TDES_EEE_192","AES_128","AES_192","AES_256","SM4",};
    unsigned int i, j, total;
    unsigned int len[5][15]=     //sum of each line is 500
    {
        {4,   91,  173, 23,  56, 79, 2,  11, 61, 0,  0,  0,  0,  0,  0},   //padding with 0 to avoid some bad compiler's error(memset not found)
        {84,  37,  68,  293, 13, 1,  4,  0,  0,  0,  0,  0,  0,  0,  0},
        {33,  20,  208, 3,   7,  67, 33, 88, 19, 22, 0,  0,  0,  0,  0},
        {59,  111, 29,  34,  27, 89, 9,  6,  79, 22, 35, 0,  0,  0,  0},
        {333, 2,   5,   39,  77, 16, 24, 4,  0,  0,  0,  0,  0,  0,  0},
    };
    unsigned int ret;
    //unsigned int block_bytes;

    memcpy_(message, "abc", 3);   //to avoid some bad compiler's error(memset not found)

    printf("\r\n ------------ %s CBC_MAC test ------------ ", name[alg]);

    /*************************** test1 ***************************/
    //generate mac
    ret = ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cbc_mac_update(ctx, message, 3);
    ret |= ske_lp_cbc_mac_final(ctx, mac);
#if 0
    print_buf_U8(message, 3, "message");
    print_buf_U8(mac, mac_bytes, "mac");
#endif
    if(SKE_SUCCESS != ret || memcmp_(mac, std_mac1, mac_bytes))
    {
        printf("\r\n %s generate CBC_MAC test 1 failure, ret=%x\r\n", name[alg], ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8(std_key, ske_lp_get_key_byte_len(alg), "key");
        print_buf_U8(mac, mac_bytes, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s generate CBC_MAC test 1 success ", name[alg]);
    }

    //verify mac
    ret = ske_lp_cbc_mac_init(ctx, alg, SKE_VERIFY_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cbc_mac_update(ctx, message, 3);
    ret |= ske_lp_cbc_mac_final(ctx, mac);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n %s verify CBC_MAC test 1 failure, ret=%x\r\n", name[alg], ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8(std_key, ske_lp_get_key_byte_len(alg), "key");
        print_buf_U8(mac, mac_bytes, "mac");
        return 1;
    }
    else
    {
        printf("\r\n %s verify CBC_MAC test 1 success ", name[alg]);
    }

#if 1
    /*************************** test2 ***************************/
    for(i=0;i<500;i++)
        message[i] = i;

    //test2-1
    //generate mac
#if 1
    ret = ske_lp_cbc_mac(alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, message, 500, mac, mac_bytes);
#else
    ret = ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, (unsigned char *)std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cbc_mac_update(ctx, message, 500);
    ret |= ske_lp_cbc_mac_final(ctx, mac);
#endif
    if(SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes))
    {
        printf("\r\n %s generate CBC_MAC test 2-%u failure, ret=%x \r\n", name[alg], 1u, ret);
        print_buf_U8(message, 500, "msg");
        print_buf_U8(mac, mac_bytes, "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s generate CBC_MAC test 2-%u success ", name[alg], 1u);
    }

    //verify mac
#if 1
    ret = ske_lp_cbc_mac(alg, SKE_VERIFY_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, message, 500, mac, mac_bytes);
#else
    ret = ske_lp_cbc_mac_init(ctx, alg, SKE_VERIFY_MAC, SKE_ZERO_PADDING, (unsigned char *)std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cbc_mac_update(ctx, message, 500);
    ret |= ske_lp_cbc_mac_final(ctx, mac);
#endif
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n %s verify CBC_MAC test 2-%u failure, ret=%x \r\n", name[alg], 1u, ret);
        print_buf_U8(message, 500, "msg");
        print_buf_U8(mac, mac_bytes, "digest");
        return 1;
    }
    else
    {
        printf("\r\n %s verify CBC_MAC test 2-%u success ", name[alg], 1u);
    }

    //test2-2...2-6
    for(i=0;i<5;i++)
    {// print_buf_U8(message, 500, "message");
        //generate mac
        ret = ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);

        j=0;
        total=0;
        while(len[i][j])
        {
            ret |= ske_lp_cbc_mac_update(ctx, message+total, len[i][j]);
            total+=len[i][j];
            j++;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_cbc_mac_final(ctx, mac);
        if(SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes))
        {
            printf("\r\n %s generate CBC_MAC test 2-%x failure, ret=%x \r\n", name[alg], i+2, ret);
            print_buf_U8(mac, mac_bytes, "digest");
            return 1;
        }
        else
        {
            printf("\r\n %s generate CBC_MAC test 2-%x success ", name[alg], i+2);
        }

        //verify mac
        ret = ske_lp_cbc_mac_init(ctx, alg, SKE_VERIFY_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);

        j=0;
        total=0;
        while(len[i][j])
        {
            ret |= ske_lp_cbc_mac_update(ctx, message+total, len[i][j]);
            total+=len[i][j];
            j++;
        }

        ret |= ske_lp_cbc_mac_final(ctx, mac);
        if(SKE_SUCCESS != ret)
        {
            printf("\r\n %s verify CBC_MAC test 2-%x failure, ret=%x \r\n", name[alg], i+2, ret);
            print_buf_U8(mac, mac_bytes, "digest");
            return 1;
        }
        else
        {
            printf("\r\n %s verify CBC_MAC test 2-%x success ", name[alg], i+2);
        }
    }

    //test2-7...
    printf("\r\n");
    for(; i<100; i++)
    {
        //generate mac
        ret = ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);

        total = 0;
        while(total < 500)
        {
            j = ske_get_rand_number(500);
            if(j%10 < 3)
                j = j%10;
            else if(j%10 < 5)
                j = j%70;
            else if(j%10 < 8)
                j = j%128;

            if(j > 500-total)
                j = 500-total;

            ret |= ske_lp_cbc_mac_update(ctx, message+total, j);
            total += j;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_cbc_mac_final(ctx, mac);
        if(SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes))
        {
            printf("\r\n %s generate CBC_MAC test 2-%x failure, ret=%x \r\n", name[alg], i+2, ret);
            print_buf_U8(mac, mac_bytes, "mac");
            return 1;
        }
        else
        {
            //printf("\r\n %s test 2-%u success ", name[alg], i+2);
            printf("2-%x ", i+2);
        }

        //verify mac
        ret = ske_lp_cbc_mac_init(ctx, alg, SKE_VERIFY_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);

        total = 0;
        while(total < 500)
        {
            j = ske_get_rand_number(500);
            if(j%10 < 3)
                j = j%10;
            else if(j%10 < 5)
                j = j%70;
            else if(j%10 < 8)
                j = j%128;

            if(j > 500-total)
                j = 500-total;

            ret |= ske_lp_cbc_mac_update(ctx, message+total, j);
            total += j;
        }

        ret |= ske_lp_cbc_mac_final(ctx, mac);
        if(SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes))
        {
            printf("\r\n %s verify CBC_MAC test 2-%x failure, ret=%x \r\n", name[alg], i+2, ret);
            print_buf_U8(mac, mac_bytes, "mac");
            return 1;
        }
        else
        {
            //printf("\r\n %s test 2-%u success ", name[alg], i+2);
            printf("2-%x ", i+2);
        }
    }


    /*************************** test3 ***************************/
    for(i=0;i<500;i++)
        message[i] = i;
    ret = 0;
    for(i=1;i<=500; i++)
    {
        ret |= ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_ZERO_PADDING, std_key, sp_key_idx, mac_bytes);
        ret |= ske_lp_cbc_mac_update(ctx, message, i);
        ret |= ske_lp_cbc_mac_final(ctx, message);
    }
    if(SKE_SUCCESS != ret || memcmp_(message, std_mac3, mac_bytes))
    {
        printf("\r\n %s generate CBC_MAC test 3 failure, ret=%x \r\n", name[alg], ret);
        print_buf_U8(std_mac3, mac_bytes, "std_mac3");
        print_buf_U8(message, mac_bytes, "mac");
        return 1;
    }
    else
    {
        printf("\r\n generate CBC_MAC %s test 3 success ", name[alg]);
    }
#endif

    printf("\r\n");
    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION

unsigned int ske_dma_cbc_mac_test_internal(SKE_ALG alg,  unsigned char *std_key, unsigned short sp_key_idx, unsigned char mac_bytes,
         unsigned char *std_mac1,  unsigned char *std_mac2,  unsigned char *std_mac3)
{
    unsigned char message[500] = {0x61,0x62,0x63,0x00};
    unsigned char tmp_buf[500];
    unsigned int key_byte_len;
    SKE_CBC_MAC_DMA_CTX ctx[1];
    unsigned int i;
    char *name[]={"DES","TDES_128","TDES_192","TDES_EEE_128","TDES_EEE_192","AES_128","AES_192","AES_256","SM4",};
    unsigned int *mac = (unsigned int *)(DMA_RAM_BASE);
    unsigned int *msg = mac + (mac_bytes+3)/4;
    unsigned int *tmp_out_ = msg+256;
    unsigned int ret;

    printf("\r\n ------------ %s CBC_MAC DMA test ------------ ", name[alg]);

    key_byte_len = ske_lp_get_key_byte_len(alg);

    //test1  message: 0x616263, 3 bytes.
    uint32_clear(msg, 512/4);
    uint32_copy(msg, (unsigned int *)message, 1);

//the two styles are equivalent
#if 1
    ret = ske_lp_dma_cbc_mac(alg, std_key, sp_key_idx, msg, 3, tmp_out_, mac, mac_bytes, ske_call_manage);
#else
    ret = ske_lp_dma_cbc_mac_init(ctx, alg, (unsigned char *)std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg, 0, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cbc_mac_update_including_last_block(ctx, msg, 3, tmp_out_, mac, ske_call_manage);
#endif

    if(SKE_SUCCESS != ret || memcmp_(std_mac1, mac, mac_bytes))
    {
        printf("\r\n %s CBC_MAC DMA test 1 failure, ret=%x \r\n", name[alg], ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8(std_key, key_byte_len, "std_key");
        print_buf_U8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_U8(std_mac1, mac_bytes, "std mac");
        return 1;
    }
    else
    {
        printf("\r\n %s CBC_MAC DMA test 1 success ", name[alg]); fflush(stdout);
    }


    //test2  message: 0x000102..., 500 bytes.
    for(i=0;i<500;i++)
    {
        message[i] = i;
    }

    uint32_clear(msg, 512/4);
    uint32_copy(msg, (unsigned int *)message, 500/4);

//the two styles are equivalent
#if 0
    ret = ske_lp_dma_cbc_mac(alg, (unsigned char *)std_key, sp_key_idx, msg, 500, tmp_out_, mac, mac_bytes, ske_call_manage);
#else
    ret = ske_lp_dma_cbc_mac_init(ctx, alg, std_key, sp_key_idx, mac_bytes);

    #if 1
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg, 31*4, tmp_out_, ske_call_manage);
    #else
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg, 2*4, tmp_out_, ske_call_manage);
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg+2*4, 1*4, tmp_out_, ske_call_manage);
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg+3*4, 3*4, tmp_out_, ske_call_manage);
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg+6*4, 24*4, tmp_out_, ske_call_manage);
        ret |= ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, msg+30*4, 1*4, tmp_out_, ske_call_manage);
    #endif

    ret |= ske_lp_dma_cbc_mac_update_including_last_block(ctx, msg+31*4, 4, tmp_out_, mac, ske_call_manage);
#endif

    if(SKE_SUCCESS != ret || memcmp_(std_mac2, mac, mac_bytes))
    {
        printf("\r\n %s CBC_MAC DMA test 2 failure, ret=%x \r\n", name[alg], ret);fflush(stdout);
        print_buf_U8(message, 500, "message");
        print_buf_U8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_U8(std_mac2, mac_bytes, "std mac");
        return 1;
    }
    else
    {
        printf("\r\n %s CBC_MAC DMA test 2 success ", name[alg]);fflush(stdout);
    }


    //test3  message: 0x000102..., 500 bytes.
    for(i=0;i<500;i++)
    {
        message[i] = i;
    }

    ret = 0;
    for(i=1;i<=500;i++)
    {
        memset_(tmp_buf, 0, 500);
        memcpy_(tmp_buf, message, i);

        uint32_clear(msg, 512/4);
        uint32_copy(msg, (unsigned int *)tmp_buf, (i+3)/4);

        ret |= ske_lp_dma_cbc_mac(alg, std_key, sp_key_idx, msg, i, tmp_out_, mac, mac_bytes, ske_call_manage);
        memcpy_(message, mac, mac_bytes);
    }

    if(SKE_SUCCESS != ret || memcmp_(std_mac3, mac, mac_bytes))
    {
        printf("\r\n %s CBC_MAC DMA test 3 failure, ret=%x \r\n", name[alg], ret);fflush(stdout);
        //print_buf_U8(message, 500, "message");
        print_buf_U8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_U8(std_mac3, mac_bytes, "std mac");
        return 1;
    }
    else
    {
        printf("\r\n %s CBC_MAC DMA test 3 success \r\n", name[alg]);fflush(stdout);
    }

    return 0;
}
#endif



#ifdef SUPPORT_SKE_DES
 unsigned char std_des_cbc_mac_key[16]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,};
 unsigned char std_des_cbc_mac_mac1[32] =  {0x5B,0xD6,0x9A,0x24,0xE0,0xBC,0x07,0xCF,};
 unsigned char std_des_cbc_mac_mac2[32] =  {0x4B,0xE2,0xE8,0xBF,0x2D,0xA8,0x94,0xE4,};
 unsigned char std_des_cbc_mac_mac3[32] =  {0x66,0xEC,0x6C,0xEC,0xA0,0x00,0x77,0xB3,};

unsigned int des_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_DES, std_des_cbc_mac_key, 0, 8, std_des_cbc_mac_mac1, 
        std_des_cbc_mac_mac2, std_des_cbc_mac_mac3);
    if(ret)
        return 1;

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_DES, std_des_cbc_mac_key, 0, 8, std_des_cbc_mac_mac1, 
        std_des_cbc_mac_mac2, std_des_cbc_mac_mac3);
    if(ret)
        return 1;
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_TDES_128
 unsigned char std_tdes_128_cbc_mac_key[16]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
 unsigned char std_tdes_128_cbc_mac_mac1[32] =  {0x59,0xFB,0xBF,0x43,0x09,0xDB,0xBD,0xE8,};
 unsigned char std_tdes_128_cbc_mac_mac2[32] =  {0x8E,0x9C,0xF0,0x3E,0x98,0x0A,0x8C,0x72,};
 unsigned char std_tdes_128_cbc_mac_mac3[32] =  {0x88,0x9C,0xA2,0xB4,0x06,0x36,0x14,0x3E,};

unsigned int tdes_128_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_TDES_128, std_tdes_128_cbc_mac_key, 0, 8, std_tdes_128_cbc_mac_mac1, 
        std_tdes_128_cbc_mac_mac2, std_tdes_128_cbc_mac_mac3);
    if(ret)
        return 1;

/*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_TDES_128, std_tdes_128_cbc_mac_key, 0, 8, std_tdes_128_cbc_mac_mac1, 
        std_tdes_128_cbc_mac_mac2, std_tdes_128_cbc_mac_mac3);
    if(ret)
        return 1;
#endif
*/

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_TDES_192
 unsigned char std_tdes_192_cbc_mac_key[24]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,
                                                0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,};
 unsigned char std_tdes_192_cbc_mac_mac1[32] =  {0x6C,0xE5,0x29,0x3A,0xA5,0x83,0x0E,0xE1,};
 unsigned char std_tdes_192_cbc_mac_mac2[32] =  {0x91,0xFD,0x2B,0x62,0x82,0xB0,0x96,0x8B,};
 unsigned char std_tdes_192_cbc_mac_mac3[32] =  {0xD0,0x7D,0xDD,0x33,0x02,0x50,0xE6,0xAB,};

unsigned int tdes_192_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_TDES_192, std_tdes_192_cbc_mac_key, 0, 8, std_tdes_192_cbc_mac_mac1, 
        std_tdes_192_cbc_mac_mac2, std_tdes_192_cbc_mac_mac3);
    if(ret)
        return 1;

/*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_TDES_192, std_tdes_192_cbc_mac_key, 0, 8, std_tdes_192_cbc_mac_mac1, 
        std_tdes_192_cbc_mac_mac2, std_tdes_192_cbc_mac_mac3);
    if(ret)
        return 1;
#endif
*/

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_128
 unsigned char std_tdes_eee_128_cbc_mac_key[16]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
 unsigned char std_tdes_eee_128_cbc_mac_mac1[32] =  {0x2B,0x1B,0x36,0xD7,0x08,0x63,0xA3,0x48,};
 unsigned char std_tdes_eee_128_cbc_mac_mac2[32] =  {0xA5,0x18,0x3D,0xA7,0x66,0x4B,0xB4,0x13,};
 unsigned char std_tdes_eee_128_cbc_mac_mac3[32] =  {0x27,0x9B,0x2F,0x7A,0x7F,0x4B,0x11,0xAD,};

unsigned int tdes_eee_128_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_TDES_EEE_128, std_tdes_eee_128_cbc_mac_key, 0, 8, 
        std_tdes_eee_128_cbc_mac_mac1, std_tdes_eee_128_cbc_mac_mac2, std_tdes_eee_128_cbc_mac_mac3);
    if(ret)
        return 1;

/*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_TDES_EEE_128, std_tdes_eee_128_cbc_mac_key, 0, 8,
        std_tdes_eee_128_cbc_mac_mac1, std_tdes_eee_128_cbc_mac_mac2, std_tdes_eee_128_cbc_mac_mac3);
    if(ret)
        return 1;
#endif
*/

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_192
 unsigned char std_tdes_eee_192_cbc_mac_key[24]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,
                                                    0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,};
 unsigned char std_tdes_eee_192_cbc_mac_mac1[32] =  {0x98,0x36,0xC2,0x2A,0x73,0x4A,0x0F,0xE5,};
 unsigned char std_tdes_eee_192_cbc_mac_mac2[32] =  {0x94,0x0C,0xE5,0x4C,0x91,0x52,0x3D,0x30,};
 unsigned char std_tdes_eee_192_cbc_mac_mac3[32] =  {0xE6,0xF3,0xA6,0x52,0xFE,0x99,0xFC,0x12,};

unsigned int tdes_eee_192_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_TDES_EEE_192, std_tdes_eee_192_cbc_mac_key, 0, 8, 
        std_tdes_eee_192_cbc_mac_mac1, std_tdes_eee_192_cbc_mac_mac2, std_tdes_eee_192_cbc_mac_mac3);
    if(ret)
        return 1;

/*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_TDES_EEE_192, std_tdes_eee_192_cbc_mac_key, 0, 8,
        std_tdes_eee_192_cbc_mac_mac1, std_tdes_eee_192_cbc_mac_mac2, std_tdes_eee_192_cbc_mac_mac3);
    if(ret)
        return 1;
#endif
*/

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_SM4
 unsigned char std_sm4_cbc_mac_key[16]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
 unsigned char std_sm4_cbc_mac_mac1[32] =  {0x9A,0xE4,0xFF,0x00,0xE6,0xD1,0x43,0x32,0xEC,0xA0,0xF8,0x67,0xA8,0xE9,0x48,0xF3,};
 unsigned char std_sm4_cbc_mac_mac2[32] =  {0x6F,0x09,0x74,0x75,0xE4,0xF9,0xAF,0x13,0x8D,0x23,0xD2,0xBA,0xD5,0xA8,0xE1,0x20,};
 unsigned char std_sm4_cbc_mac_mac3[32] =  {0x78,0x6B,0x06,0x7E,0xB5,0x80,0x91,0xBE,0xFB,0xE2,0x57,0x12,0x5F,0xD2,0x7B,0xF0,};

unsigned int sm4_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_SM4, std_sm4_cbc_mac_key, 0, 16, std_sm4_cbc_mac_mac1, 
        std_sm4_cbc_mac_mac2, std_sm4_cbc_mac_mac3);
    if(ret)
        return 1;

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_SM4, std_sm4_cbc_mac_key, 0, 16, std_sm4_cbc_mac_mac1, 
        std_sm4_cbc_mac_mac2, std_sm4_cbc_mac_mac3);
    if(ret)
        return 1;
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_128
 unsigned char std_aes_128_cbc_mac_key[16]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
 unsigned char std_aes_128_cbc_mac_mac1[32] =  {0x65,0xAD,0xFD,0x9E,0xA2,0xA1,0xCF,0x12,0xDB,0x92,0xD4,0x31,0xE3,0xB7,0x43,0xF6,};
 unsigned char std_aes_128_cbc_mac_mac2[32] =  {0x90,0x9B,0x26,0xC0,0x89,0x90,0x91,0x8A,0xD2,0x54,0xAD,0xF8,0x66,0x17,0xF6,0x24,};
 unsigned char std_aes_128_cbc_mac_mac3[32] =  {0xBA,0xF7,0x0D,0x15,0x8A,0xA9,0x3C,0x02,0x10,0xBB,0x4B,0x34,0xC6,0xB4,0xE9,0xE8,};

unsigned int aes128_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_AES_128, std_aes_128_cbc_mac_key, 0, 16, 
        std_aes_128_cbc_mac_mac1, std_aes_128_cbc_mac_mac2, std_aes_128_cbc_mac_mac3);
    if(ret)
        return 1;

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_AES_128, std_aes_128_cbc_mac_key, 0, 16, 
        std_aes_128_cbc_mac_mac1, std_aes_128_cbc_mac_mac2, std_aes_128_cbc_mac_mac3);
    if(ret)
        return 1;
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_192
 unsigned char std_aes_192_cbc_mac_key[24]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,
                                               0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,};
 unsigned char std_aes_192_cbc_mac_mac1[32] =  {0xEB,0x13,0x69,0x2D,0x16,0xAA,0xDA,0xE9,0x05,0x95,0x77,0x91,0x2C,0x88,0x18,0xFD,};
 unsigned char std_aes_192_cbc_mac_mac2[32] =  {0xEB,0x27,0x6A,0x29,0x40,0xB1,0x3D,0xAE,0x1F,0xE7,0x71,0x9E,0x4B,0xB6,0x28,0xBA,};
 unsigned char std_aes_192_cbc_mac_mac3[32] =  {0xE9,0x30,0xE7,0xDF,0x83,0xDA,0xF7,0x97,0x4C,0x66,0xE8,0x24,0xFE,0xBC,0x0D,0x1B,};

unsigned int aes192_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_AES_192, std_aes_192_cbc_mac_key, 0, 16, 
        std_aes_192_cbc_mac_mac1, std_aes_192_cbc_mac_mac2, std_aes_192_cbc_mac_mac3);
    if(ret)
        return 1;

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_AES_192, std_aes_192_cbc_mac_key, 0, 16, 
        std_aes_192_cbc_mac_mac1, std_aes_192_cbc_mac_mac2, std_aes_192_cbc_mac_mac3);
    if(ret)
        return 1;
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_256
 unsigned char std_aes_256_cbc_mac_key[32]  =  {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,
                                                                                             0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,0x0A,0x0C,0x95,0x37,0x44,0x02,0xDE,0x28,};
 unsigned char std_aes_256_cbc_mac_mac1[32] =  {0xF0,0xF0,0x26,0x3F,0x5C,0x21,0x8A,0x51,0x27,0xC8,0x94,0x8F,0x82,0x24,0xB1,0x78,};
 unsigned char std_aes_256_cbc_mac_mac2[32] =  {0xA7,0xAE,0x27,0x71,0xCA,0x6E,0xCF,0x49,0xDF,0x02,0x13,0x86,0xCA,0x62,0xAE,0x7F,};
 unsigned char std_aes_256_cbc_mac_mac3[32] =  {0xC0,0xA4,0x43,0xEB,0xFA,0x7B,0xCE,0xDF,0x18,0xAB,0x1B,0xB6,0x7F,0x70,0xD2,0x5E,};

unsigned int aes256_cbc_mac_test(void)
{
    unsigned int ret;

    ret = ske_cbc_mac_test_internal(SKE_ALG_AES_256, std_aes_256_cbc_mac_key, 0, 16, 
        std_aes_256_cbc_mac_mac1, std_aes_256_cbc_mac_mac2, std_aes_256_cbc_mac_mac3);
    if(ret)
        return 1;

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cbc_mac_test_internal(SKE_ALG_AES_256, std_aes_256_cbc_mac_key, 0, 16, 
        std_aes_256_cbc_mac_mac1, std_aes_256_cbc_mac_mac2, std_aes_256_cbc_mac_mac3);
    if(ret)
        return 1;
#endif

    return 0u;
}
#endif



unsigned int ske_cbc_mac_speed_test_internal(SKE_ALG alg, char *info)
{
    unsigned char in[4096];
    unsigned char key[32];
    unsigned char mac[16];
    unsigned int i;
    unsigned int mac_bytes = 8;
    unsigned int round = 100;
    unsigned int in_bytes = 4096;
    unsigned int ret;
    SKE_CBC_MAC_CTX ctx[1];

    uint32_sleep(0xFFFF, 1);

    round = speed_get_round_by_alg(alg);

#ifndef CBC_MAC_SPEED_TEST_BY_TIMER
    round *= 100;
#endif

    printf("\r\n %s begin", info); fflush(stdout);

#ifdef CBC_MAC_SPEED_TEST_BY_TIMER
    startP();
#endif

    ret = ske_lp_cbc_mac_init(ctx, alg, SKE_GENERATE_MAC, SKE_NO_PADDING, key, 0, mac_bytes);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n cbc_mac init error ret=%x", ret); fflush(stdout);
        return 1;
    }

    for(i=0;i<round;i++)
    {
        ret = ske_lp_cbc_mac_update(ctx, in, in_bytes);
        if(SKE_SUCCESS != ret)
        {
            printf("\r\n cbc_mac crypto error ret=%x", ret); fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_cbc_mac_final(ctx, mac);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n cbc_mac final error ret=%x", ret); fflush(stdout);
        return 1;
    }

#ifdef CBC_MAC_SPEED_TEST_BY_TIMER
    endP(0,in_bytes,round);
#else
    printf("\r\n finished"); fflush(stdout);
#endif

    return 0;
}


unsigned int ske_cbc_mac_speed_test(void)
{
    ske_cbc_mac_speed_test_internal(SKE_ALG_DES, "SKE_ALG_DES CBC_MAC");
    ske_cbc_mac_speed_test_internal(SKE_ALG_TDES_192, "SKE_ALG_TDES_192 CBC_MAC");
    ske_cbc_mac_speed_test_internal(SKE_ALG_AES_128, "SKE_ALG_AES_128 CBC_MAC");
    ske_cbc_mac_speed_test_internal(SKE_ALG_AES_192, "SKE_ALG_AES_192 CBC_MAC");
    ske_cbc_mac_speed_test_internal(SKE_ALG_AES_256, "SKE_ALG_AES_256 CBC_MAC");
//  ske_cbc_mac_speed_test_internal(SKE_ALG_SM4, "SKE_ALG_SM4 CBC_MAC");

    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
unsigned int ske_dma_cbc_mac_speed_test_internal(SKE_ALG alg, char *info)
{
    unsigned int *in = (unsigned int *)DMA_RAM_BASE;
    unsigned char key[32];
    unsigned int i;
    unsigned int mac_bytes = 8;
    unsigned int round = 100;
    unsigned int in_words = 4096;
    unsigned int ret;
    SKE_CBC_MAC_DMA_CTX ctx[1];

    uint32_sleep(0xFFFF, 1);

    round = speed_get_round_by_alg(alg);

#ifndef CBC_MAC_SPEED_TEST_BY_TIMER
    round *= 30;
#endif

    printf("\r\n %s begin", info); fflush(stdout);

#ifdef CBC_MAC_SPEED_TEST_BY_TIMER
    startP();
#endif

    ret = ske_lp_dma_cbc_mac_init(ctx, alg, key, 0, mac_bytes);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n CBC_MAC init dma error ret=%x", ret); fflush(stdout);
        return 1;
    }

    for(i=0;i<round;i++)
    {
        ret = ske_lp_dma_cbc_mac_update_blocks_excluding_last_block(ctx, in, in_words, in, ske_call_manage);
        if(SKE_SUCCESS != ret)
        {
            printf("\r\n CBC_MAC crypto 1 dma error ret=%x", ret); fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_dma_cbc_mac_update_including_last_block(ctx, in, 12, in+12, in, ske_call_manage);
    if(SKE_SUCCESS != ret)
    {
        printf("\r\n CBC_MAC crypto 2 dma error ret=%x", ret); fflush(stdout);
        return 1;
    }

#ifdef CBC_MAC_SPEED_TEST_BY_TIMER
    endP(0,in_words*4,round);
#else
    printf("\r\n finished"); fflush(stdout);
#endif

    return 0;
}


unsigned int ske_dma_cbc_mac_speed_test(void)
{
    ske_dma_cbc_mac_speed_test_internal(SKE_ALG_DES, "SKE_ALG_DES CBC_MAC DMA");
    ske_dma_cbc_mac_speed_test_internal(SKE_ALG_AES_128, "SKE_ALG_AES_128 CBC_MAC DMA");
    ske_dma_cbc_mac_speed_test_internal(SKE_ALG_AES_192, "SKE_ALG_AES_192 CBC_MAC DMA");
    ske_dma_cbc_mac_speed_test_internal(SKE_ALG_AES_256, "SKE_ALG_AES_256 CBC_MAC DMA");
//  ske_dma_cbc_mac_speed_test_internal(SKE_ALG_SM4, "SKE_ALG_SM4 CBC_MAC DMA");

    return 0;
}
#endif


unsigned int SKE_LP_CBC_MAC_all_test(void)
{
    unsigned int ret;

    printf("\r\n ================== SKE_LP CBC_MAC test ================== \r\n");fflush(stdout);

#if 0
    if(SKE_SUCCESS != ske_cbc_mac_speed_test())
        return 1;
#endif

#ifdef SKE_LP_DMA_FUNCTION
#if 0
    if(SKE_SUCCESS != ske_dma_cbc_mac_speed_test())
        return 1;
#endif
#endif



    /**/
#ifdef SUPPORT_SKE_DES
    ret = des_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_TDES_128
    ret = tdes_128_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_TDES_192
    ret = tdes_192_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
    ret = tdes_eee_128_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
    ret = tdes_eee_192_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_SM4
    ret = sm4_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_AES_128
    ret = aes128_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_AES_192
    ret = aes192_cbc_mac_test();
    if(ret)
        return 1;
#endif

#ifdef SUPPORT_SKE_AES_256
    ret = aes256_cbc_mac_test();
    if(ret)
        return 1;
#endif
//*/


    return 0;
}



#endif


/********************************************************************************************************
 * @file    ske_aes_xcbc_mac_96_test.c
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
#include "common.h"
#include "../ske_test/app_test.h"
#include <stdio.h>

//#define AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER

#ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
extern unsigned int startP();
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif


#ifdef SUPPORT_SKE_AES_XCBC_MAC_96

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

extern void ske_call_manage(void);

unsigned int ske_aes_xcbc_mac_96_test_internal(unsigned char *std_key, unsigned short sp_key_idx, unsigned char *std_mac1, unsigned char *std_mac2, unsigned char *std_mac3)
{
    unsigned char           message[500] = {0};
    unsigned char           mac[16];
    SKE_AES_XCBC_MAC_96_CTX ctx[1];
    unsigned char           mac_bytes = 0x0C;
    char                    name[]    = "AES_128";

    unsigned int i, j, total;
    unsigned int len[5][15] =                                       //sum of each line is 500
        {
            {4,   91,  173, 23,  56, 79, 2,  11, 1,  30, 30, 0, 0, 0, 0}, //padding with 0 to avoid some bad compiler's error(memset not found)
            {84,  37,  68,  293, 13, 1,  4,  0,  0,  0,  0,  0, 0, 0, 0},
            {33,  20,  208, 3,   7,  67, 33, 88, 19, 22, 0,  0, 0, 0, 0},
            {59,  111, 29,  34,  27, 89, 9,  6,  79, 22, 34, 1, 0, 0, 0},
            {333, 3,   4,   39,  77, 16, 24, 4,  0,  0,  0,  0, 0, 0, 0},
    };
    unsigned int ret;

    memcpy_(message, "abc", 3); //to avoid some bad compiler's error(memset not found)

    printf("\r\n ------------ %s AES_XCBC_MAC_96 test ------------ ", name);

    /*************************** test1 ***************************/
    //generate mac
    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx);
    ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message, 3);
    ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);

    #if 0
    print_buf_U8(message, 3, "message");
    print_buf_U8(mac, mac_bytes, "mac");
    #endif
    if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_mac1, mac_bytes)) {
        printf("\r\n %s generate AES_XCBC_MAC_96 test 1 failure, ret=%x\r\n", name, ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8((unsigned char *)std_key, ske_lp_get_key_byte_len(SKE_ALG_AES_128), "key");
        print_buf_U8(mac, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n %s generate AES_XCBC_MAC_96 test 1 success ", name);
        //print_buf_U8(mac, mac_bytes, "mac");
    }

    //verify mac
    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_VERIFY_MAC, (unsigned char *)std_key, sp_key_idx);
    ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message, 3);
    ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
    if (SKE_SUCCESS != ret) {
        printf("\r\n %s verify AES_XCBC_MAC_96 test 1 failure, ret=%x\r\n", name, ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8(mac, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n %s verify AES_XCBC_MAC_96 test 1 success ", name);
    }


    /*************************** test2 ***************************/
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    //test2-1
    //generate mac
    #if 1
    ret = ske_lp_aes_xcbc_mac_96(SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx, message, 500, mac);
    #else
    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx);
    ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message, 500);
    ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
    #endif

    if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_mac2, mac_bytes)) {
        printf("\r\n %s generate AES_XCBC_MAC_96 test 2-%d failure, ret=%x \r\n", name, 1, ret);
        print_buf_U8(message, 500, "msg");
        print_buf_U8(mac, mac_bytes, "digest");
        return 1;
    } else {
        printf("\r\n %s generate AES_XCBC_MAC_96 test 2-%d success ", name, 1);
        //print_buf_U8(mac, mac_bytes, "mac");
    }

    //verify mac
    #if 1
    ret = ske_lp_aes_xcbc_mac_96(SKE_VERIFY_MAC, (unsigned char *)std_key, sp_key_idx, message, 500, mac);
    #else
    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_VERIFY_MAC, (unsigned char *)std_key, sp_key_idx);
    ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message, 500);
    ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
    #endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n %s verify AES_XCBC_MAC_96 test 2-%d failure, ret=%x \r\n", name, 1, ret);
        print_buf_U8(message, 500, "msg");
        print_buf_U8(mac, mac_bytes, "digest");
        return 1;
    } else {
        printf("\r\n %s verify AES_XCBC_MAC_96 test 2-%d success ", name, 1);
    }


    //test2-2...2-6
    for (i = 0; i < 5; i++) { // print_buf_U8(message, 500, "message");
        //generate mac
        ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx);

        j     = 0;
        total = 0;
        while (len[i][j]) {
            ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);

        if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_mac2, mac_bytes)) {
            printf("\r\n %s generate AES_XCBC_MAC_96 test 2-%u failure, ret=%x \r\n", name, i + 2, ret);
            print_buf_U8(mac, mac_bytes, "digest");
            return 1;
        } else {
            printf("\r\n %s generate AES_XCBC_MAC_96 test 2-%u success ", name, i + 2);
        }

        //verify mac
        ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_VERIFY_MAC, (unsigned char *)std_key, sp_key_idx);

        j     = 0;
        total = 0;
        while (len[i][j]) {
            ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n %s verify AES_XCBC_MAC_96 test 2-%u failure, ret=%x \r\n", name, i + 2, ret);
            print_buf_U8(mac, mac_bytes, "digest");
            return 1;
        } else {
            printf("\r\n %s verify AES_XCBC_MAC_96 test 2-%u success ", name, i + 2);
        }
    }

    //test2-7...
    printf("\r\n");
    for (; i < 100; i++) {
        //generate mac
        ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx);

        total = 0;
        while (total < 500) {
            j = ske_get_rand_number(500);
            if (j % 10 < 3) {
                j = j % 10;
            } else if (j % 10 < 5) {
                j = j % 70;
            } else if (j % 10 < 8) {
                j = j % 128;
            }

            if (j > 500 - total) {
                j = 500 - total;
            }

            ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message + total, j);
            total += j;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
        if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_mac2, mac_bytes)) {
            printf("\r\n %s generate AES_XCBC_MAC_96 test 2-%u failure, ret=%x \r\n", name, i + 2, ret);
            print_buf_U8(mac, mac_bytes, "mac");
            return 1;
        } else {
            //printf("\r\n %s test 2-%u success ", name, i+2);
            printf("2-%u ", i + 2);
        }

        //verify mac
        ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_VERIFY_MAC, (unsigned char *)std_key, sp_key_idx);

        total = 0;
        while (total < 500) {
            j = ske_get_rand_number(500);
            if (j % 10 < 3) {
                j = j % 10;
            } else if (j % 10 < 5) {
                j = j % 70;
            } else if (j % 10 < 8) {
                j = j % 128;
            }

            if (j > 500 - total) {
                j = 500 - total;
            }

            ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message + total, j);
            total += j;
        }

        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n %s verify AES_XCBC_MAC_96 test 2-%u failure, ret=%x \r\n", name, i + 2, ret);
            print_buf_U8(mac, mac_bytes, "mac");
            return 1;
        } else {
            //printf("\r\n %s test 2-%u success ", name, i+2);
            printf("2-%u ", i + 2);
        }
    }


    /*************************** test3 ***************************/
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++) {
        ret |= ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, (unsigned char *)std_key, sp_key_idx);
        ret |= ske_lp_aes_xcbc_mac_96_update(ctx, message, i);
        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, message);
    }

    if (SKE_SUCCESS != ret || memcmp_(message, (unsigned char *)std_mac3, mac_bytes)) {
        printf("\r\n %s AES_XCBC_MAC_96 test 3 failure, ret=%x \r\n", name, ret);
        print_buf_U8(message, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n %s AES_XCBC_MAC_96 test 3 success ", name);
        //print_buf_U8(message, mac_bytes, "mac");
    }

    printf("\r\n");

    return 0;
}

unsigned int ske_aes_xcbc_mac_96_speed_test(void)
{
    unsigned char           in[4096];
    unsigned char           key[16];
    unsigned int            i;
    unsigned int            round    = 10000;
    unsigned int            in_bytes = 4096;
    unsigned int            ret;
    SKE_AES_XCBC_MAC_96_CTX ctx[1];

    uint32_sleep(0xFFFF, 1);

    #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    round = 100;
    #else
    round = 10000;
    #endif

    printf("\r\n AES_XCBC_MAC_96 begin");
    fflush(stdout);

    #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    startP();
    #endif

    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, key, 0);
    if (SKE_SUCCESS != ret) {
        printf("\r\n AES_XCBC_MAC_96 init error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_aes_xcbc_mac_96_update(ctx, in, in_bytes);
        if (SKE_SUCCESS != ret) {
            printf("\r\n AES_XCBC_MAC_96 crypto error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_aes_xcbc_mac_96_final(ctx, in);
    if (SKE_SUCCESS != ret) {
        printf("\r\n AES_XCBC_MAC_96 final error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    endP(0, in_bytes, round);
    #else
    printf("\r\n finished");
    fflush(stdout);
    #endif

    return 0;
}


    #ifdef SKE_LP_DMA_FUNCTION

unsigned int ske_dma_aes_xcbc_mac_96_test_internal(unsigned char *std_key, unsigned short sp_key_idx, unsigned char *std_mac1, unsigned char *std_mac2, unsigned char *std_mac3, SKE_CALLBACK callback)
{
    (void)callback;
    unsigned char               message[500] = {0x61, 0x62, 0x63, 0x00};
    unsigned char               tmp_buf[500];
    SKE_AES_XCBC_MAC_96_DMA_CTX ctx[1];
    unsigned int                i;
    char                        name[]   = "AES_128";
    unsigned int               *mac      = (unsigned int *)(DMA_RAM_BASE);
    unsigned int               *msg      = mac + 3;
    unsigned int               *tmp_out_ = msg + 256;
    unsigned int                ret;

    printf("\r\n ------------ %s AES-XCBC-MAC-96 DMA test ------------ ", name);

    //test1  message: 0x616263, 3 bytes.
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

        //the two styles are equivalent
        #if 0
    ret = ske_lp_dma_aes_xcbc_mac_96((unsigned char *)std_key, sp_key_idx, msg, 3, tmp_out_, mac, ske_call_manage);
        #else
    ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx, (unsigned char *)std_key, sp_key_idx);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg, 0, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx, msg, 3, tmp_out_, mac, ske_call_manage);
        #endif

    if (SKE_SUCCESS != ret || memcmp_((unsigned char *)std_mac1, mac, 0x0C)) {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 1 failure, ret=%x \r\n", name, ret);
        print_buf_U8(message, 3, "message");
        print_buf_U8((unsigned char *)mac, 0x0C, "mac");
        print_buf_U8((unsigned char *)std_mac1, 0x0C, "std mac");
        return 1;
    } else {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 1 success ", name);
        fflush(stdout);
    }


    //test2  message: 0x000102..., 500 bytes.
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 500 / 4);

        //the two styles are equivalent
        #if 0
    ret = ske_lp_dma_aes_xcbc_mac_96((unsigned char *)std_key, sp_key_idx, msg, 500, tmp_out_, mac, ske_call_manage);
        #else
    ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx, (unsigned char *)std_key, sp_key_idx);

            #if 0
        ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg, 31*4, tmp_out_, ske_call_manage);
            #else
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg, 2 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg + 2 * 4, 1 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg + 3 * 4, 3 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg + 6 * 4, 24 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, msg + 30 * 4, 1 * 4, tmp_out_, ske_call_manage);
            #endif

    ret |= ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx, msg + 31 * 4, 4, tmp_out_, mac, ske_call_manage);
        #endif

    if (SKE_SUCCESS != ret || memcmp_((unsigned char *)std_mac2, mac, 0x0C)) {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 2 failure, ret=%x \r\n", name, ret);
        fflush(stdout);
        print_buf_U8(message, 500, "message");
        print_buf_U8((unsigned char *)mac, 0x0C, "mac");
        print_buf_U8((unsigned char *)std_mac2, 0x0C, "std mac");
        return 1;
    } else {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 2 success ", name);
        fflush(stdout);
    }


    //test3  message: 0x000102..., 500 bytes.
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++) {
        memset_(tmp_buf, 0, 500);
        memcpy_(tmp_buf, message, i);

        uint32_clear(msg, 512 / 4);
        uint32_copy(msg, (unsigned int *)tmp_buf, (i + 3) / 4);

        ret |= ske_lp_dma_aes_xcbc_mac_96((unsigned char *)std_key, sp_key_idx, msg, i, tmp_out_, mac, ske_call_manage);
        memcpy_(message, mac, 0x0C);
    }

    if (SKE_SUCCESS != ret || memcmp_((unsigned char *)std_mac3, mac, 0x0C)) {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 3 failure, ret=%x \r\n", name, ret);
        fflush(stdout);
        //print_buf_U8(message, 500, "message");
        print_buf_U8((unsigned char *)mac, 0x0C, "mac");
        print_buf_U8((unsigned char *)std_mac3, 0x0C, "std mac");
        return 1;
    } else {
        printf("\r\n %s AES_XCBC_MAC_96 DMA test 3 success \r\n", name);
        fflush(stdout);
    }

    return 0;
}

unsigned int ske_dma_aes_xcbc_mac_96_speed_test(void)
{
    unsigned int               *in = (unsigned int *)DMA_RAM_BASE;
    unsigned char               key[16];
    unsigned int                i;
    unsigned int                round    = 100;
    unsigned int                in_words = 16384 / 4;
    unsigned int                ret;
    SKE_AES_XCBC_MAC_96_DMA_CTX ctx[1];

    uint32_sleep(0xFFFF, 1);

        #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    round = 100;
        #else
    round = 3000;
        #endif

    printf("\r\n AES_XCBC_MAC_96 DMA begin");
    fflush(stdout);

        #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    startP();
        #endif

    ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx, key, 0);
    if (SKE_SUCCESS != ret) {
        printf("\r\n AES_XCBC_MAC_96 init dma error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx, in, in_words, in, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n AES_XCBC_MAC_96 crypto dma error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx, in, 12, in + 12, (unsigned int *)key, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        printf("\r\n AES_XCBC_MAC_96 final dma error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

        #ifdef AES_XCBC_MAC_96_SPEED_TEST_BY_TIMER
    endP(0, in_words * 4, round);
        #else
    printf("\r\n finished");
    fflush(stdout);
        #endif

    return 0;
}
    #endif


static unsigned char std_aes_xcbc_mac_96_key_0[16] = {
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
};
unsigned char std_aes_xcbc_mac_96_mac1[12] = {
    0x91,
    0x1D,
    0xCC,
    0xAC,
    0xBA,
    0x0B,
    0x4B,
    0x4C,
    0x29,
    0x84,
    0x32,
    0x8F,
};
unsigned char std_aes_xcbc_mac_96_mac2[12] = {
    0x1B,
    0xAE,
    0x78,
    0xC8,
    0x3A,
    0x93,
    0x13,
    0xD0,
    0x4E,
    0xD0,
    0x03,
    0xB9,
};
unsigned char std_aes_xcbc_mac_96_mac3[12] = {
    0x4B,
    0x97,
    0x99,
    0x36,
    0x70,
    0x28,
    0x58,
    0x8D,
    0x87,
    0x2C,
    0x7A,
    0xCE,
};

unsigned int aes_xcbc_mac_96_test(void)
{
    unsigned int ret;

    ret = ske_aes_xcbc_mac_96_test_internal(std_aes_xcbc_mac_96_key_0, 0, std_aes_xcbc_mac_96_mac1, std_aes_xcbc_mac_96_mac2, std_aes_xcbc_mac_96_mac3);
    if (ret) {
        return 1;
    }

    #ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_aes_xcbc_mac_96_test_internal(std_aes_xcbc_mac_96_key_0, 0, std_aes_xcbc_mac_96_mac1, std_aes_xcbc_mac_96_mac2, std_aes_xcbc_mac_96_mac3, ske_call_manage);
    if (ret) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int aes_xcbc_mac_96_sample_test(void)
{
    //test vector
    unsigned char std_aes_xcbc_mac_96_plain[] = {
        0x00,
        0x01,
        0x02,
        0x03,
        0x04,
        0x05,
        0x06,
        0x07,
        0x08,
        0x09,
        0x0A,
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0x0F,
        0x10,
        0x11,
        0x12,
        0x13,
        0x14,
        0x15,
        0x16,
        0x17,
        0x18,
        0x19,
        0x1A,
        0x1B,
        0x1C,
        0x1D,
        0x1E,
        0x1F,
        0x20,
        0x21,
        0x22,
        0x23,
        0x24,
        0x25,
        0x26,
        0x27,
        0x28,
        0x29,
        0x2A,
        0x2B,
        0x2C,
        0x2D,
        0x2E,
        0x2F,
    };
    static unsigned char std_aes_xcbc_mac_96_key[16] = {
        0x00,
        0x01,
        0x02,
        0x03,
        0x04,
        0x05,
        0x06,
        0x07,
        0x08,
        0x09,
        0x0A,
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0x0F,
    };
    unsigned char vector_bytes[] = {0x00, 0x03, 0x10, 0x14, 0x20, 0x22};
    unsigned char std_aes_xcbc_mac_96_mac[6][12] =
        {
            {0x75, 0xF0, 0x25, 0x1D, 0x52, 0x8A, 0xC0, 0x1C, 0x45, 0x73, 0xDF, 0xD5},
            {0x5B, 0x37, 0x65, 0x80, 0xAE, 0x2F, 0x19, 0xAF, 0xE7, 0x21, 0x9C, 0xEE},
            {0xD2, 0xA2, 0x46, 0xFA, 0x34, 0x9B, 0x68, 0xA7, 0x99, 0x98, 0xA4, 0x39},
            {0x47, 0xF5, 0x1B, 0x45, 0x64, 0x96, 0x62, 0x15, 0xB8, 0x98, 0x5C, 0x63},
            {0xF5, 0x4F, 0x0E, 0xC8, 0xD2, 0xB9, 0xF3, 0xD3, 0x68, 0x07, 0x73, 0x4B},
            {0xBE, 0xCB, 0xB3, 0xBC, 0xCD, 0xB5, 0x18, 0xA3, 0x06, 0x77, 0xD5, 0x48},
    };
    unsigned char std_aes_xcbc_mac_96_plain_large[1000] = {0};
    unsigned char std_aes_xcbc_mac_96_mac_large[12]     = {0xF0, 0xDA, 0xFE, 0xE8, 0x95, 0xDB, 0x30, 0x25, 0x37, 0x61, 0x10, 0x3B};

    unsigned int vector_num = sizeof(vector_bytes) / sizeof(vector_bytes[0]);

    unsigned char  mac[12] = {0};
    unsigned int   ret;
    unsigned int   i;
    unsigned short sp_key_idx = 0;
    #ifdef SKE_LP_DMA_FUNCTION
    unsigned int *std_in_, *tmp_out_, *mac2;
    unsigned int  len_bytes;
    #endif
    SKE_AES_XCBC_MAC_96_CTX ctx[1];
    #ifdef SKE_LP_DMA_FUNCTION
    SKE_AES_XCBC_MAC_96_DMA_CTX ctx2[1];
    #endif
    printf("\r\n\r\n =================== AES_XCBC_MAC_96 sample test(from RFC3566) ==================== ");

    for (i = 0; i < vector_num; i++) {
        ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, std_aes_xcbc_mac_96_key, sp_key_idx);
        ret |= ske_lp_aes_xcbc_mac_96_update(ctx, std_aes_xcbc_mac_96_plain, vector_bytes[i]);
        ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);

        if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_aes_xcbc_mac_96_mac[i], 0x0C)) {
            printf("\r\n generate AES_XCBC_MAC_96 test %u failure, ret=%x \r\n", i + 1, ret);
            print_buf_U8(mac, 0x0C, "mac");
            return 1;
        } else {
            printf("\r\n generate AES_XCBC_MAC_96 test %u success ", i + 1);
        }

        ret = ske_lp_aes_xcbc_mac_96(SKE_VERIFY_MAC, std_aes_xcbc_mac_96_key, sp_key_idx, std_aes_xcbc_mac_96_plain, vector_bytes[i], mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n verify AES_XCBC_MAC_96 test %u failure, ret=%x \r\n", i + 1, ret);
            print_buf_U8(mac, 0x0C, "mac");
            return 1;
        } else {
            printf("\r\n verify AES_XCBC_MAC_96 test %u success ", i + 1);
        }
    }

    //test large vector
    ret = ske_lp_aes_xcbc_mac_96_init(ctx, SKE_GENERATE_MAC, std_aes_xcbc_mac_96_key, sp_key_idx);
    ret |= ske_lp_aes_xcbc_mac_96_update(ctx, std_aes_xcbc_mac_96_plain_large, 1000);
    ret |= ske_lp_aes_xcbc_mac_96_final(ctx, mac);

    if (SKE_SUCCESS != ret || memcmp_(mac, (unsigned char *)std_aes_xcbc_mac_96_mac_large, 0x0C)) {
        printf("\r\n generate AES_XCBC_MAC_96 test %u failure, ret=%x \r\n", i + 1, ret);
        print_buf_U8(mac, 0x0C, "mac");
        return 1;
    } else {
        printf("\r\n generate AES_XCBC_MAC_96 test %u success ", i + 1);
    }

    ret = ske_lp_aes_xcbc_mac_96(SKE_VERIFY_MAC, std_aes_xcbc_mac_96_key, sp_key_idx, std_aes_xcbc_mac_96_plain_large, 1000, mac);
    if (SKE_SUCCESS != ret) {
        printf("\r\n verify AES_XCBC_MAC_96 test %u failure, ret=%x \r\n", i + 1, ret);
        print_buf_U8(mac, 0x0C, "mac");
        return 1;
    } else {
        printf("\r\n verify AES_XCBC_MAC_96 test %u success \r\n", i + 1);
    }

    #ifdef SKE_LP_DMA_FUNCTION

    /************** DMA style ***************/
    mac2     = (unsigned int *)DMA_RAM_BASE;
    std_in_  = mac2 + 3;
    tmp_out_ = std_in_ + 256;

    for (i = 0; i < vector_num; i++) {
        if (vector_bytes[i]) {
            memcpy_(std_in_, std_aes_xcbc_mac_96_plain, vector_bytes[i]);
            memcpy_(std_in_, (unsigned char *)std_aes_xcbc_mac_96_plain, vector_bytes[i]);
            ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx2, std_aes_xcbc_mac_96_key, sp_key_idx);
            ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx2, std_in_, 0, tmp_out_, ske_call_manage);
            ret |= ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx2, std_in_, vector_bytes[i], tmp_out_, mac2, ske_call_manage);
        } else {
            ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx2, std_aes_xcbc_mac_96_key, sp_key_idx);
            ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx2, std_in_, 0, tmp_out_, ske_call_manage);
            ret |= ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx2, std_in_, 0, tmp_out_, mac2, ske_call_manage);
        }

        if (SKE_SUCCESS != ret || memcmp_(mac2, (unsigned char *)std_aes_xcbc_mac_96_mac[i], 0x0C)) {
            printf("\r\n generate AES_XCBC_MAC_96 dma test %u failure, ret=%x \r\n", i + 1, ret);
            print_buf_U8((unsigned char *)mac2, 0x0C, "mac2");
            return 1;
        } else {
            printf("\r\n generate AES_XCBC_MAC_96 dma test %u success ", i + 1);
        }
    }

    //test large vector
    len_bytes = 1000;
    uint32_copy(std_in_, (unsigned int *)std_aes_xcbc_mac_96_plain_large, len_bytes / 4);
        #if 1
    ret = ske_lp_dma_aes_xcbc_mac_96_init(ctx2, std_aes_xcbc_mac_96_key, sp_key_idx);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_blocks_excluding_last_block(ctx2, std_in_, 4 * 19, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_aes_xcbc_mac_96_update_including_last_block(ctx2, std_in_ + 4 * 19, 1000 - 16 * 19, tmp_out_, mac2, ske_call_manage);
        #else
    ret = ske_lp_dma_aes_xcbc_mac_96(std_aes_xcbc_mac_96_key, sp_key_idx, std_in_, 1000, tmp_out_, mac2, ske_call_manage);
        #endif
    if (SKE_SUCCESS != ret || memcmp_(mac2, (unsigned char *)std_aes_xcbc_mac_96_mac_large, 0x0C)) {
        printf("\r\n generate AES_XCBC_MAC_96 dma test %u failure, ret=%x \r\n", i + 1, ret);
        print_buf_U8((unsigned char *)mac2, 0x0C, "mac2");
        return 1;
    } else {
        printf("\r\n generate AES_XCBC_MAC_96 dma test %u success ", i + 1);
    }
    #endif

    return SKE_SUCCESS;
}

unsigned int SKE_LP_AES_XCBC_MAC_96_all_test(void)
{
    unsigned int ret;

    printf("\r\n\r\n =================== SKE_LP AES_XCBC_MAC_96 test =================== \r\n");
    fflush(stdout);

    #if 0
    if(SKE_SUCCESS != ske_aes_xcbc_mac_96_speed_test())
        return 1;
    #endif

    #ifdef SKE_LP_DMA_FUNCTION
        #if 0
    if(SKE_SUCCESS != ske_dma_aes_xcbc_mac_96_speed_test())
        return 1;
        #endif
    #endif

    ret = aes_xcbc_mac_96_sample_test();
    if (ret) {
        return 1;
    }

    ret = aes_xcbc_mac_96_test();
    if (ret) {
        return 1;
    }

    return 0;
}

#endif

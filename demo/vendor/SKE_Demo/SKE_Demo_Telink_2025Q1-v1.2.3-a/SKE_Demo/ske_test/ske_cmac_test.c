/********************************************************************************************************
 * @file    ske_cmac_test.c
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
#include "lib/include/crypto_common/utility.h"
#if defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL322X) || defined(MCU_CORE_TL323X)
#include "lib/include/ske/ske_cmac.h"
#endif

//#define CMAC_SPEED_TEST_BY_TIMER

#ifdef CMAC_SPEED_TEST_BY_TIMER
extern unsigned int startp();
extern unsigned int endp(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif
extern unsigned int speed_get_round_by_alg(ske_alg_e alg);


#ifdef SUPPORT_SKE_MODE_CMAC

extern unsigned int ske_get_rand_number(unsigned int max_number);
extern void         ske_call_manage(void);

/**
 * @brief           Internal function for CMAC testing
 * @param[in]       alg                  - SKE algorithm to test
 * @param[in]       std_key              - Standard key for testing
 * @param[in]       sp_key_idx           - Special key index
 * @param[in]       mac_bytes            - Length of MAC in bytes
 * @param[in]       std_mac1             - Expected MAC for test case 1
 * @param[in]       std_mac2             - Expected MAC for test case 2
 * @param[in]       std_mac3             - Expected MAC for test case 3
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_cmac_test_internal(ske_alg_e alg, const unsigned char *std_key, unsigned short sp_key_idx, unsigned char mac_bytes, const unsigned char *std_mac1,
                                    const unsigned char *std_mac2, const unsigned char *std_mac3)
{
    unsigned char  message[500];
    unsigned char  mac[16];
    ske_cmac_ctx_t ctx[1];
    char          *name[] = {
        "DES", "TDES_128", "TDES_192", "TDES_EEE_128", "TDES_EEE_192", "AES_128", "AES_192", "AES_256", "SM4",
    };

    unsigned int i, j, total;
    unsigned int len[5][15] = //sum of each line is 500
        {
            {4, 91, 173, 23, 56, 79, 2, 11, 61, 0, 0, 0, 0, 0, 0}, //padding with 0 to avoid some bad compiler's error(memset not found)
            {84, 37, 68, 293, 13, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0},     {33, 20, 208, 3, 7, 67, 33, 88, 19, 22, 0, 0, 0, 0, 0},
            {59, 111, 29, 34, 27, 89, 9, 6, 79, 22, 35, 0, 0, 0, 0}, {333, 2, 5, 39, 77, 16, 24, 4, 0, 0, 0, 0, 0, 0, 0},
        };
    unsigned int ret;
    //unsigned int block_bytes;

    memcpy_(message, "abc", 3); //to avoid some bad compiler's error(memset not found)

    printf("\r\n ------------ %s CMAC test ------------ ", name[alg]);

    /*************************** test1 ***************************/
    //generate mac
    ret = ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cmac_update(ctx, message, 3);
    ret |= ske_lp_cmac_final(ctx, mac);
#if 0
    print_buf_u8(message, 3, "message");
    print_buf_u8(mac, mac_bytes, "mac");
#endif
    if (SKE_SUCCESS != ret || memcmp_(mac, std_mac1, mac_bytes)) {
        printf("\r\n %s generate CMAC test 1 failure, ret=%x\r\n", name[alg], ret);
        print_buf_u8(message, 3, "message");
        print_buf_u8(mac, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n %s generate CMAC test 1 success ", name[alg]);
    }

    //verify mac
    ret = ske_lp_cmac_init(ctx, alg, SKE_VERIFY_MAC, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cmac_update(ctx, message, 3);
    ret |= ske_lp_cmac_final(ctx, mac);
    if (SKE_SUCCESS != ret) {
        printf("\r\n %s verify CMAC test 1 failure, ret=%x\r\n", name[alg], ret);
        print_buf_u8(message, 3, "message");
        print_buf_u8(mac, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n %s verify CMAC test 1 success ", name[alg]);
    }


#if 1
    /*************************** test2 ***************************/
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    //test2-1
    //generate mac
#if 1
    ret = ske_lp_cmac(alg, SKE_GENERATE_MAC, std_key, sp_key_idx, message, 500, mac, mac_bytes);
#else
    ret = ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cmac_update(ctx, message, 500);
    ret |= ske_lp_cmac_final(ctx, mac);
#endif
    if (SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes)) {
        printf("\r\n %s generate CMAC test 2-%d failure, ret=%x \r\n", name[alg], 1, ret);
        print_buf_u8(message, 500, "msg");
        print_buf_u8(mac, mac_bytes, "digest");
        return 1;
    } else {
        printf("\r\n %s generate CMAC test 2-%d success ", name[alg], 1);
    }

    //verify mac
#if 1
    ret = ske_lp_cmac(alg, SKE_VERIFY_MAC, std_key, sp_key_idx, message, 500, mac, mac_bytes);
#else
    ret = ske_lp_cmac_init(ctx, alg, SKE_VERIFY_MAC, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_cmac_update(ctx, message, 500);
    ret |= ske_lp_cmac_final(ctx, mac);
#endif
    if (SKE_SUCCESS != ret) {
        printf("\r\n %s verify CMAC test 2-%d failure, ret=%x \r\n", name[alg], 1, ret);
        print_buf_u8(message, 500, "msg");
        print_buf_u8(mac, mac_bytes, "digest");
        return 1;
    } else {
        printf("\r\n %s verify CMAC test 2-%d success ", name[alg], 1);
    }


    //test2-2...2-6
    for (i = 0; i < 5; i++) { //    print_buf_u8(message, 500, "message");
        //generate mac
        ret = ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, std_key, sp_key_idx, mac_bytes);

        j     = 0;
        total = 0;
        while (len[i][j]) {
            ret |= ske_lp_cmac_update(ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_cmac_final(ctx, mac);
        if (SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes)) {
            printf("\r\n %s generate CMAC test 2-%u failure, ret=%x \r\n", name[alg], i + 2, ret);
            print_buf_u8(mac, mac_bytes, "digest");
            return 1;
        } else {
            printf("\r\n %s generate CMAC test 2-%u success ", name[alg], i + 2);
        }

        //verify mac
        ret = ske_lp_cmac_init(ctx, alg, SKE_VERIFY_MAC, std_key, sp_key_idx, mac_bytes);

        j     = 0;
        total = 0;
        while (len[i][j]) {
            ret |= ske_lp_cmac_update(ctx, message + total, len[i][j]);
            total += len[i][j];
            j++;
        }

        ret |= ske_lp_cmac_final(ctx, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n %s verify CMAC test 2-%u failure, ret=%x \r\n", name[alg], i + 2, ret);
            print_buf_u8(mac, mac_bytes, "digest");
            return 1;
        } else {
            printf("\r\n %s verify CMAC test 2-%u success ", name[alg], i + 2);
        }
    }

    //test2-7...
    printf("\r\n");
    for (; i < 100; i++) {
        //generate mac
        ret = ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, std_key, sp_key_idx, mac_bytes);

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

            ret |= ske_lp_cmac_update(ctx, message + total, j);
            total += j;
        }

        memset_(mac, 0, 16);
        ret |= ske_lp_cmac_final(ctx, mac);
        if (SKE_SUCCESS != ret || memcmp_(mac, std_mac2, mac_bytes)) {
            printf("\r\n %s generate CMAC test 2-%u failure, ret=%x \r\n", name[alg], i + 2, ret);
            print_buf_u8(mac, mac_bytes, "mac");
            return 1;
        } else {
            //printf("\r\n %s test 2-%u success ", name[alg], i+2);
            printf("2-%u ", i + 2);
        }

        //verify mac
        ret = ske_lp_cmac_init(ctx, alg, SKE_VERIFY_MAC, std_key, sp_key_idx, mac_bytes);

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

            ret |= ske_lp_cmac_update(ctx, message + total, j);
            total += j;
        }

        ret |= ske_lp_cmac_final(ctx, mac);
        if (SKE_SUCCESS != ret) {
            printf("\r\n %s verify CMAC test 2-%u failure, ret=%x \r\n", name[alg], i + 2, ret);
            print_buf_u8(mac, mac_bytes, "mac");
            return 1;
        } else {
            //printf("\r\n %s test 2-%u success ", name[alg], i+2);
            printf("2-%u ", i + 2);
        }
    }


    /*************************** test3 ***************************/
    for (i = 0; i < 500; i++) {
        message[i] = i;
    }

    ret = 0;
    for (i = 0; i <= 500; i++) {
        ret |= ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, std_key, sp_key_idx, mac_bytes);
        ret |= ske_lp_cmac_update(ctx, message, i);
        ret |= ske_lp_cmac_final(ctx, message);
    }
    if (SKE_SUCCESS != ret || memcmp_(message, std_mac3, mac_bytes)) {
        printf("\r\n %s CMAC test 3 failure, ret=%x \r\n", name[alg], ret);
        print_buf_u8(message, mac_bytes, "mac");
        return 1;
    } else {
        printf("\r\n CMAC %s test 3 success ", name[alg]);
    }

#endif

    printf("\r\n");

    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
/**
 * @brief           Internal function for DMA-based CMAC testing
 * @param[in]       alg                  - SKE algorithm to test
 * @param[in]       std_key              - Standard key for testing
 * @param[in]       sp_key_idx           - Special key index
 * @param[in]       mac_bytes            - Length of MAC in bytes
 * @param[in]       std_mac1             - Expected MAC for test case 1
 * @param[in]       std_mac2             - Expected MAC for test case 2
 * @param[in]       std_mac3             - Expected MAC for test case 3
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_dma_cmac_test_internal(ske_alg_e alg, const unsigned char *std_key, unsigned short sp_key_idx, unsigned char mac_bytes, const unsigned char *std_mac1,
                                        const unsigned char *std_mac2, const unsigned char *std_mac3)
{
    unsigned char      message[500] = {0x61, 0x62, 0x63, 0x00};
    unsigned char      tmp_buf[500];
    ske_cmac_dma_ctx_t ctx[1];
    unsigned int       i;
    char              *name[] = {
        "DES", "TDES_128", "TDES_192", "TDES_EEE_128", "TDES_EEE_192", "AES_128", "AES_192", "AES_256", "SM4",
    };
    unsigned int *msg      = (unsigned int *)(DMA_RAM_BASE);
    unsigned int *mac      = msg + 256;
    unsigned int *tmp_out_ = mac + 4;
    unsigned int  ret;

    printf("\r\n ------------ %s CMAC DMA test ------------ ", name[alg]);

    //test1  message: 0x616263, 3 bytes.
    uint32_clear(msg, 512 / 4);
    uint32_copy(msg, (unsigned int *)message, 1);

//the two styles are equivalent
#if 0
    ret = ske_lp_dma_cmac(alg, std_key, sp_key_idx, msg, 3, tmp_out_, mac, mac_bytes, ske_call_manage);
#else
    ret = ske_lp_dma_cmac_init(ctx, alg, std_key, sp_key_idx, mac_bytes);
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg, 0, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cmac_update_including_last_block(ctx, msg, 3, tmp_out_, mac, ske_call_manage);
#endif

    if (SKE_SUCCESS != ret || memcmp_(std_mac1, mac, mac_bytes)) {
        printf("\r\n %s CMAC DMA test 1 failure, ret=%x \r\n", name[alg], ret);
        print_buf_u8(message, 3, "message");
        print_buf_u8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_u8(std_mac1, mac_bytes, "std mac");
        return 1;
    } else {
        printf("\r\n %s CMAC DMA test 1 success ", name[alg]);
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
    ret = ske_lp_dma_cmac(alg, std_key, sp_key_idx, msg, 500, tmp_out_, mac, mac_bytes, ske_call_manage);
#else
    ret = ske_lp_dma_cmac_init(ctx, alg, std_key, sp_key_idx, mac_bytes);

#if 0
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg, 31*4, tmp_out_, ske_call_manage);
#else
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg, 2 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg + 2 * 4, 1 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg + 3 * 4, 3 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg + 6 * 4, 24 * 4, tmp_out_, ske_call_manage);
    ret |= ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, msg + 30 * 4, 1 * 4, tmp_out_, ske_call_manage);
#endif

    ret |= ske_lp_dma_cmac_update_including_last_block(ctx, msg + 31 * 4, 4, tmp_out_, mac, ske_call_manage);
#endif

    if (SKE_SUCCESS != ret || memcmp_(std_mac2, mac, mac_bytes)) {
        printf("\r\n %s CMAC DMA test 2 failure, ret=%x \r\n", name[alg], ret);
        fflush(stdout);
        print_buf_u8(message, 500, "message");
        print_buf_u8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_u8(std_mac2, mac_bytes, "std mac");
        return 1;
    } else {
        printf("\r\n %s CMAC DMA test 2 success ", name[alg]);
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

        ret |= ske_lp_dma_cmac(alg, std_key, sp_key_idx, msg, i, tmp_out_, mac, mac_bytes, ske_call_manage);

        memcpy_(message, mac, mac_bytes);
    }

    if (SKE_SUCCESS != ret || memcmp_(std_mac3, mac, mac_bytes)) {
        printf("\r\n %s CMAC DMA test 3 failure, ret=%x \r\n", name[alg], ret);
        fflush(stdout);
        //print_buf_u8(message, 500, "message");
        print_buf_u8((unsigned char *)mac, mac_bytes, "mac");
        print_buf_u8(std_mac3, mac_bytes, "std mac");
        return 1;
    } else {
        printf("\r\n %s CMAC DMA test 3 success \r\n", name[alg]);
        fflush(stdout);
    }

    return 0;
}
#endif


#ifdef SUPPORT_SKE_DES
const unsigned char std_des_cmac_key[16] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F,
};
const unsigned char std_des_cmac_mac1[32] = {
    0xEE, 0x3F, 0x70, 0x7F, 0x2C, 0x11, 0xD2, 0x97,
};
const unsigned char std_des_cmac_mac2[32] = {
    0x86, 0xED, 0x2F, 0x12, 0x41, 0xAC, 0xFB, 0x6B,
};
const unsigned char std_des_cmac_mac3[32] = {
    0x76, 0xC2, 0x62, 0x68, 0xEC, 0xC8, 0x3B, 0x46,
};

/**
 * @brief           Test DES CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int des_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_DES, std_des_cmac_key, 0, 8, std_des_cmac_mac1, std_des_cmac_mac2, std_des_cmac_mac3);
    if (ret) {
        return 1;
    }

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_DES, std_des_cmac_key, 0, 8, std_des_cmac_mac1, std_des_cmac_mac2, std_des_cmac_mac3);
    if (ret) {
        return 1;
    }
#endif

    return ret;
}
#endif

//*
#ifdef SUPPORT_SKE_TDES_128
const unsigned char std_tdes_128_cmac_key[16] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34,
};
const unsigned char std_tdes_128_cmac_mac1[32] = {
    0x38, 0xB0, 0xCD, 0xE0, 0x48, 0xEC, 0x42, 0x38,
};
const unsigned char std_tdes_128_cmac_mac2[32] = {
    0xCD, 0x69, 0xB5, 0x7D, 0xFC, 0x59, 0x19, 0xF7,
};
const unsigned char std_tdes_128_cmac_mac3[32] = {
    0x64, 0x94, 0x6D, 0x98, 0xA9, 0xBE, 0xAC, 0x56,
};

/**
 * @brief           Test TDES-128 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int tdes_128_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_TDES_128, std_tdes_128_cmac_key, 0, 8, std_tdes_128_cmac_mac1, std_tdes_128_cmac_mac2, std_tdes_128_cmac_mac3);
    if (ret) {
        return 1;
    }

    /*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_TDES_128, std_tdes_128_cmac_key, 0, 8,
        std_tdes_128_cmac_mac1, std_tdes_128_cmac_mac2, std_tdes_128_cmac_mac3);
    if(ret)
        return 1;
#endif
*/

    return ret;
}
#endif


#ifdef SUPPORT_SKE_TDES_192
const unsigned char std_tdes_192_cmac_key[24] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34, 0xB4, 0x42, 0x60, 0xE1, 0x56, 0x8D, 0x9E, 0x85,
};
const unsigned char std_tdes_192_cmac_mac1[32] = {
    0x11, 0x3A, 0x81, 0xAF, 0x89, 0x94, 0x2E, 0xB6,
};
const unsigned char std_tdes_192_cmac_mac2[32] = {
    0x04, 0x9C, 0x81, 0x2B, 0x10, 0xFA, 0xFC, 0xB6,
};
const unsigned char std_tdes_192_cmac_mac3[32] = {
    0xB7, 0x82, 0x0B, 0x62, 0x22, 0x77, 0xB4, 0xCA,
};

/**
 * @brief           Test TDES-192 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int tdes_192_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_TDES_192, std_tdes_192_cmac_key, 0, 8, std_tdes_192_cmac_mac1, std_tdes_192_cmac_mac2, std_tdes_192_cmac_mac3);
    if (ret) {
        return 1;
    }

    /*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_TDES_192, std_tdes_192_cmac_key, 0, 8,
        std_tdes_192_cmac_mac1, std_tdes_192_cmac_mac2, std_tdes_192_cmac_mac3);
    if(ret)
        return 1;
#endif
*/

    return ret;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_128
const unsigned char std_tdes_eee_128_cmac_key[16] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34,
};
const unsigned char std_tdes_eee_128_cmac_mac1[32] = {
    0xD6, 0x08, 0x2A, 0x8E, 0x6F, 0x2E, 0x76, 0x90,
};
const unsigned char std_tdes_eee_128_cmac_mac2[32] = {
    0xE1, 0x30, 0x43, 0x47, 0x75, 0x1B, 0x9E, 0x7B,
};
const unsigned char std_tdes_eee_128_cmac_mac3[32] = {
    0x58, 0xCA, 0x6C, 0x94, 0x16, 0x0A, 0xB6, 0x76,
};

/**
 * @brief           Test TDES-EEE-128 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int tdes_eee_128_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_TDES_EEE_128, std_tdes_eee_128_cmac_key, 0, 8, std_tdes_eee_128_cmac_mac1, std_tdes_eee_128_cmac_mac2, std_tdes_eee_128_cmac_mac3);
    if (ret) {
        return 1;
    }

    /*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_TDES_EEE_128, std_tdes_eee_128_cmac_key, 0, 8,
        std_tdes_eee_128_cmac_mac1, std_tdes_eee_128_cmac_mac2, std_tdes_eee_128_cmac_mac3);
    if(ret)
        return 1;
#endif
*/

    return ret;
}
#endif


#ifdef SUPPORT_SKE_TDES_EEE_192
const unsigned char std_tdes_eee_192_cmac_key[24] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34, 0xB4, 0x42, 0x60, 0xE1, 0x56, 0x8D, 0x9E, 0x85,
};
const unsigned char std_tdes_eee_192_cmac_mac1[32] = {
    0xB1, 0x35, 0x3C, 0x97, 0xA4, 0x7C, 0x14, 0x2B,
};
const unsigned char std_tdes_eee_192_cmac_mac2[32] = {
    0xC3, 0x8A, 0x12, 0x10, 0x1B, 0xCB, 0x45, 0xBC,
};
const unsigned char std_tdes_eee_192_cmac_mac3[32] = {
    0xA4, 0x55, 0x52, 0x0B, 0xAB, 0xEE, 0x65, 0x7E,
};

/**
 * @brief           Test TDES-EEE-192 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int tdes_eee_192_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_TDES_EEE_192, std_tdes_eee_192_cmac_key, 0, 8, std_tdes_eee_192_cmac_mac1, std_tdes_eee_192_cmac_mac2, std_tdes_eee_192_cmac_mac3);
    if (ret) {
        return 1;
    }

    /*
#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_TDES_EEE_192, std_tdes_eee_192_cmac_key, 0, 8,
        std_tdes_eee_192_cmac_mac1, std_tdes_eee_192_cmac_mac2, std_tdes_eee_192_cmac_mac3);
    if(ret)
        return 1;
#endif
*/

    return ret;
}
#endif
//*/

#ifdef SUPPORT_SKE_SM4
const unsigned char std_sm4_cmac_key[16] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34,
};
const unsigned char std_sm4_cmac_mac1[32] = {
    0xAF, 0xCD, 0xA8, 0xC2, 0x78, 0x0C, 0x13, 0xC0, 0x4E, 0x77, 0x2D, 0x51, 0x55, 0x4A, 0x0E, 0xE7,
};
const unsigned char std_sm4_cmac_mac2[32] = {
    0xA2, 0x78, 0x67, 0x2F, 0x7F, 0xFE, 0xE4, 0x15, 0xBB, 0xA9, 0x03, 0xE7, 0x5F, 0x4D, 0xB4, 0x9E,
};
const unsigned char std_sm4_cmac_mac3[32] = {
    0x4C, 0x44, 0xA4, 0xFE, 0xFF, 0xEE, 0x02, 0x34, 0xE4, 0x34, 0xA6, 0x8E, 0x6D, 0xBC, 0x0C, 0xAE,
};

/**
 * @brief           Test SM4 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int sm4_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_SM4, std_sm4_cmac_key, 0, 16, std_sm4_cmac_mac1, std_sm4_cmac_mac2, std_sm4_cmac_mac3);
    if (ret) {
        return 1;
    }

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_SM4, std_sm4_cmac_key, 0, 16, std_sm4_cmac_mac1, std_sm4_cmac_mac2, std_sm4_cmac_mac3);
    if (ret) {
        return 1;
    }
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_128
const unsigned char std_aes_128_cmac_key[16] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34,
};
const unsigned char std_aes_128_cmac_mac1[32] = {
    0x49, 0xE2, 0x30, 0x8A, 0x22, 0x8C, 0x43, 0xFF, 0xED, 0x99, 0x87, 0xD4, 0x75, 0x8B, 0xAC, 0xDC,
};
const unsigned char std_aes_128_cmac_mac2[32] = {
    0x45, 0x1B, 0xDF, 0x99, 0xD5, 0x00, 0xD5, 0xAF, 0xDE, 0xFE, 0xEE, 0x44, 0x18, 0xC1, 0x32, 0x73,
};
const unsigned char std_aes_128_cmac_mac3[32] = {
    0xEC, 0x5E, 0xEB, 0x22, 0x66, 0xE2, 0x0A, 0x55, 0x34, 0xD4, 0x83, 0xB0, 0x83, 0xF6, 0x70, 0xC4,
};

/**
 * @brief           Test AES-128 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int aes128_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_AES_128, std_aes_128_cmac_key, 0, 16, std_aes_128_cmac_mac1, std_aes_128_cmac_mac2, std_aes_128_cmac_mac3);
    if (ret) {
        return 1;
    }

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_AES_128, std_aes_128_cmac_key, 0, 16, std_aes_128_cmac_mac1, std_aes_128_cmac_mac2, std_aes_128_cmac_mac3);
    if (ret) {
        return 1;
    }
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_192
const unsigned char std_aes_192_cmac_key[24] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34, 0xB4, 0x42, 0x60, 0xE1, 0x56, 0x8D, 0x9E, 0x85,
};
const unsigned char std_aes_192_cmac_mac1[32] = {
    0x98, 0x90, 0x68, 0xAD, 0x5E, 0x5B, 0x14, 0x5E, 0x89, 0xC2, 0x40, 0x1B, 0x3B, 0x44, 0x36, 0x6A,
};
const unsigned char std_aes_192_cmac_mac2[32] = {
    0xBF, 0x83, 0xD7, 0xAA, 0x65, 0x06, 0xFE, 0x44, 0x08, 0x23, 0x9A, 0xD1, 0x6C, 0x2D, 0x1B, 0x44,
};
const unsigned char std_aes_192_cmac_mac3[32] = {
    0x1A, 0x6C, 0x81, 0xC2, 0x2B, 0x13, 0xCA, 0xB7, 0x1A, 0x8C, 0x4C, 0xC6, 0xD4, 0xF4, 0xFC, 0x0D,
};

/**
 * @brief           Test AES-192 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int aes192_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_AES_192, std_aes_192_cmac_key, 0, 16, std_aes_192_cmac_mac1, std_aes_192_cmac_mac2, std_aes_192_cmac_mac3);
    if (ret) {
        return 1;
    }

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_AES_192, std_aes_192_cmac_key, 0, 16, std_aes_192_cmac_mac1, std_aes_192_cmac_mac2, std_aes_192_cmac_mac3);
    if (ret) {
        return 1;
    }
#endif

    return 0u;
}
#endif


#ifdef SUPPORT_SKE_AES_256
const unsigned char std_aes_256_cmac_key[32] = {
    0xE0, 0x70, 0x99, 0xF1, 0xBF, 0xAF, 0xFD, 0x7F, 0x24, 0x0C, 0xD7, 0x90, 0xCA, 0x4F, 0xE1, 0x34,
    0xB4, 0x42, 0x60, 0xE1, 0x56, 0x8D, 0x9E, 0x85, 0x0A, 0x0C, 0x95, 0x37, 0x44, 0x02, 0xDE, 0x28,
};
const unsigned char std_aes_256_cmac_mac1[32] = {
    0x14, 0x7A, 0xD3, 0x82, 0xAC, 0xBD, 0x2D, 0xB4, 0x69, 0x85, 0x87, 0xEF, 0x44, 0xD2, 0xF1, 0x8B,
};
const unsigned char std_aes_256_cmac_mac2[32] = {
    0x87, 0xBA, 0x77, 0xA2, 0xFF, 0x29, 0xC3, 0x69, 0xAC, 0x4D, 0xAF, 0x6B, 0xAA, 0x69, 0xC7, 0x39,
};
const unsigned char std_aes_256_cmac_mac3[32] = {
    0x67, 0x1D, 0x20, 0x4B, 0xCE, 0xE4, 0x42, 0x2B, 0x97, 0xF2, 0xE6, 0xB3, 0x3F, 0x9B, 0x04, 0xDF,
};

/**
 * @brief           Test AES-256 CMAC functionality
 * @return          0 if test passes, 1 if test fails
 */
unsigned int aes256_cmac_test(void)
{
    unsigned int ret;

    ret = ske_cmac_test_internal(SKE_ALG_AES_256, std_aes_256_cmac_key, 0, 16, std_aes_256_cmac_mac1, std_aes_256_cmac_mac2, std_aes_256_cmac_mac3);
    if (ret) {
        return 1;
    }

#ifdef SKE_LP_DMA_FUNCTION
    ret = ske_dma_cmac_test_internal(SKE_ALG_AES_256, std_aes_256_cmac_key, 0, 16, std_aes_256_cmac_mac1, std_aes_256_cmac_mac2, std_aes_256_cmac_mac3);
    if (ret) {
        return 1;
    }
#endif

    return 0u;
}
#endif

/**
 * @brief           Internal function for CMAC speed testing
 * @param[in]       alg                  - SKE algorithm to test
 * @param[in]       info                 - Test information string
 * @return          0 if test passes, 1 if test fails
 */
unsigned int ske_cmac_speed_test_internal(ske_alg_e alg, char *info)
{
    unsigned char  in[4096];
    unsigned char  key[32];
    unsigned int   i;
    unsigned int   mac_bytes = 7;
    unsigned int   ret;
    unsigned int   round    = 100;
    unsigned int   in_bytes = 4096;
    ske_cmac_ctx_t ctx[1];

    uint32_sleep(0xFFFF, 1);

    round = speed_get_round_by_alg(alg);

#ifndef CMAC_SPEED_TEST_BY_TIMER
    round *= 100;
#endif

    printf("\r\n %s begin", info);
    fflush(stdout);

#ifdef CMAC_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = ske_lp_cmac_init(ctx, alg, SKE_GENERATE_MAC, key, 0, mac_bytes);
    if (SKE_SUCCESS != ret) {
        printf("\r\n cmac init error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_cmac_update(ctx, in, in_bytes);
        if (SKE_SUCCESS != ret) {
            printf("\r\n cmac crypto error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_cmac_final(ctx, in);
    if (SKE_SUCCESS != ret) {
        printf("\r\n cmac final error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

#ifdef CMAC_SPEED_TEST_BY_TIMER
    endp(0, in_bytes, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform CMAC speed tests for all supported algorithms
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_cmac_speed_test(void)
{
    //    ske_cmac_speed_test_internal(SKE_ALG_DES, "SKE_ALG_DES CMAC");
    //    ske_cmac_speed_test_internal(SKE_ALG_TDES_192, "SKE_ALG_TDES_192 CMAC");
    ske_cmac_speed_test_internal(SKE_ALG_AES_128, "SKE_ALG_AES_128 CMAC");
    //    ske_cmac_speed_test_internal(SKE_ALG_AES_192,  "SKE_ALG_AES_192 CMAC");
    //    ske_cmac_speed_test_internal(SKE_ALG_AES_256, "SKE_ALG_AES_256 CMAC");
    //    ske_cmac_speed_test_internal(SKE_ALG_SM4, "SKE_ALG_SM4 CMAC");

    return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
/**
 * @brief           Internal function for DMA-based CMAC speed testing
 * @param[in]       alg                  - SKE algorithm to test
 * @param[in]       info                 - Test information string
 * @return          0 if test passes, 1 if test fails
 */
unsigned int ske_dma_cmac_speed_test_internal(ske_alg_e alg, char *info)
{
    unsigned int      *in = (unsigned int *)DMA_RAM_BASE;
    unsigned char      key[32];
    unsigned int       i;
    unsigned int       mac_bytes = 7;
    unsigned int       round     = 100;
    unsigned int       in_words  = 4096;
    unsigned int       ret;
    ske_cmac_dma_ctx_t ctx[1];

    uint32_sleep(0xFFFF, 1);

#ifndef CMAC_SPEED_TEST_BY_TIMER
    round *= 30;
#endif

    printf("\r\n %s begin", info);
    fflush(stdout);

#ifdef CMAC_SPEED_TEST_BY_TIMER
    startp();
#endif

    ret = ske_lp_dma_cmac_init(ctx, alg, key, 0, mac_bytes);
    if (SKE_SUCCESS != ret) {
        printf("\r\n dma cmac init error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

    for (i = 0; i < round; i++) {
        ret = ske_lp_dma_cmac_update_blocks_excluding_last_block(ctx, in, in_words, in, ske_call_manage);
        if (SKE_SUCCESS != ret) {
            printf("\r\n dma cmac crypto 1 error ret=%x", ret);
            fflush(stdout);
            return 1;
        }
    }

    ret = ske_lp_dma_cmac_update_including_last_block(ctx, in, 12, in, (unsigned int *)key, ske_call_manage);
    if (SKE_SUCCESS != ret) {
        printf("\r\n dma cmac crypto 2 error ret=%x", ret);
        fflush(stdout);
        return 1;
    }

#ifdef CMAC_SPEED_TEST_BY_TIMER
    endp(0, in_words * 4, round);
#else
    printf("\r\n finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           Perform DMA-based CMAC speed tests for all supported algorithms
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_dma_cmac_speed_test(void)
{
    //    ske_dma_cmac_speed_test_internal(SKE_ALG_DES, "SKE_ALG_DES CMAC DMA");
    ske_dma_cmac_speed_test_internal(SKE_ALG_AES_128, "SKE_ALG_AES_128 CMAC DMA");
    //    ske_dma_cmac_speed_test_internal(SKE_ALG_AES_192,  "SKE_ALG_AES_192 CMAC DMA");
    //    ske_dma_cmac_speed_test_internal(SKE_ALG_AES_256, "SKE_ALG_AES_256 CMAC DMA");
    //    ske_dma_cmac_speed_test_internal(SKE_ALG_SM4, "SKE_ALG_SM4 CMAC DMA");

    return 0;
}
#endif

/**
 * @brief           Run all CMAC tests for supported algorithms
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_lp_cmac_all_test(void)
{
    unsigned int ret;

    printf("\r\n\r\n =================== SKE_LP CMAC test =================== \r\n");
    fflush(stdout);

#if 0
    if(SKE_SUCCESS != ske_cmac_speed_test())
        return 1;
#endif

#ifdef SKE_LP_DMA_FUNCTION
#if 0
    if(SKE_SUCCESS != ske_dma_cmac_speed_test())
        return 1;
#endif
#endif


#ifdef SUPPORT_SKE_DES
    ret = des_cmac_test();
    if (ret) {
        return 1;
    }
#endif
//*
#ifdef SUPPORT_SKE_TDES_128
    ret = tdes_128_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_192
    ret = tdes_192_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
    ret = tdes_eee_128_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
    ret = tdes_eee_192_cmac_test();
    if (ret) {
        return 1;
    }
#endif
//*/

//*
#ifdef SUPPORT_SKE_SM4
    ret = sm4_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_128
    ret = aes128_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_192
    ret = aes192_cmac_test();
    if (ret) {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_256
    ret = aes256_cmac_test();
    if (ret) {
        return 1;
    }
#endif
    //*/

    return 0;
}


#endif

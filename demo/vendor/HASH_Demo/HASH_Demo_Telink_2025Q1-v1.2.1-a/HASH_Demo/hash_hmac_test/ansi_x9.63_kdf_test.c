/********************************************************************************************************
 * @file    ansi_x9.63_kdf_test.c
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

#include "lib/include/hash/hash_kdf.h"
#include "lib/include/crypto_common/utility.h"

#ifdef SUPPORT_ANSI_X9_63_KDF

extern unsigned int hash_get_rand_number(unsigned int max_number);

#ifdef SUPPORT_HASH_NODE
/**
 * @brief           Internal function to test ANSI X9.63 KDF implementation
 * @param[in]       alg                  - The hash algorithm to test
 * @param[in]       std_Z                - Input Z value
 * @param[in]       Z_bytes              - Length of Z in bytes
 * @param[in]       std_shared_info      - Shared info value
 * @param[in]       shared_info_bytes    - Length of shared info in bytes
 * @param[in]       std_k                - Expected output key
 * @param[in]       k_bytes              - Length of output key in bytes
 * @param[in]       info                 - Test case information
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int ansi_x9_63_kdf_test_internal(hash_alg_e alg, const unsigned char *std_Z, unsigned int Z_bytes, const unsigned char *std_shared_info, unsigned int shared_info_bytes,
                                          unsigned char *std_k, unsigned int k_bytes, char *info)
{
    char *name[] = {"SM3", "MD5", "SHA256", "SHA384", "SHA512", "SHA1", "SHA224", "SHA512_224", "SHA512_256", "SHA3_224", "SHA3_256", "SHA3_384", "SHA3_512"};
    unsigned char k1[1000];
    unsigned char k2[1000];
    unsigned int k1_bytes, k2_bytes;
    unsigned int i, ret;

    printf("\r\n ========= %s ansi_x9_63_kdf test %s ========= \r\n", name[alg], info);

    // test 1
    for (i = 1; i <= k_bytes; i++)
    {
        ret = ansi_x9_63_kdf(alg, std_Z, Z_bytes, std_shared_info, shared_info_bytes, k1, i, NULL, 0);
        if ((HASH_SUCCESS != ret) || memcmp_(k1, (unsigned char *)std_k, i))
        {
            printf("\r\n %s - ansi_x9_63_kdf test 1-%u failure, ret=%u\r\n", name[alg], i, ret);
            print_buf_U8(std_Z, Z_bytes, "input Z");
            if (std_shared_info)
            {
                print_buf_U8(std_shared_info, shared_info_bytes, "std_shared_info");
            }
            print_buf_U8(k1, k_bytes, "output k");
            return 1;
        }
        else
        {
            printf(" 1-%u", i);
            fflush(stdout);
        }
    }
    // printf("\r\n test 1 success \r\n", name[alg], i);fflush(stdout);
    printf("\r\n test 1 success \r\n");
    // test 2
    for (i = 0; i < 100; i++)
    {
        k1_bytes = hash_get_rand_number(k_bytes);
        k2_bytes = k_bytes - k1_bytes;

        ret = ansi_x9_63_kdf(alg, std_Z, Z_bytes, std_shared_info, shared_info_bytes, k1, k1_bytes, k2, k2_bytes);
        if ((HASH_SUCCESS != ret) || memcmp_(k1, (unsigned char *)std_k, k_bytes) || memcmp_(k2, (unsigned char *)std_k + k1_bytes, k2_bytes))
        {
            printf("\r\n %s - ansi_x9_63_kdf test 2-%u failure, ret=%u\r\n", name[alg], i, ret);
            print_buf_U8(std_Z, Z_bytes, "input Z");
            if (std_shared_info)
            {
                print_buf_U8(std_shared_info, shared_info_bytes, "std_shared_info");
            }
            print_buf_U8(k1, k1_bytes, "output k1");
            print_buf_U8(k2, k2_bytes, "output k2");
            return 1;
        }
        else
        {
            printf(" 2-%u(%u,%u)", i, k1_bytes, k2_bytes);
            fflush(stdout);
        }
    }
    // printf("\r\n test 2 success \r\n", name[alg], i);fflush(stdout);
    printf("\r\n test 2 success \r\n");

    return 0;
}

const unsigned char std_z[] = {
    0x0C,
    0x12,
    0x8A,
    0x90,
    0x0B,
    0xD2,
    0xB5,
    0xCA,
    0xE2,
    0x17,
    0x4D,
    0xDC,
    0x12,
    0xE0,
    0x52,
    0x8E,
    0x4A,
    0x55,
    0xE2,
    0x70,
    0xA4,
    0xA6,
    0xA8,
    0xC6,
    0x0C,
    0xA9,
    0x12,
    0x27,
    0x19,
    0x4E,
    0x81,
    0x56,
    0x16,
    0xC2,
    0xCC,
    0x0E,
    0x40,
    0xB4,
    0xBA,
    0x7F,
    0xCC,
    0x2A,
    0xC9,
    0xF7,
    0x63,
    0x19,
    0x98,
    0x9C,
    0x03,
    0xD4,
    0x02,
    0x52,
    0xFF,
    0x5D,
    0x71,
    0x8D,
    0xF2,
    0x5A,
    0xC1,
    0xC9,
    0xB2,
    0x82,
    0x5B,
    0x1A,
    0x84,
    0x2E,
    0xAD,
    0x2C,
    0xE7,
    0x62,
    0x3E,
    0x77,
    0x3E,
    0x6D,
    0xDB,
    0x3E,
    0x3F,
    0x02,
    0x3C,
    0xAE,
};
const unsigned char std_shared_info[] = {
    0xFB,
    0xB2,
    0xA1,
    0xCC,
    0x8D,
    0xA1,
    0xEF,
    0x6A,
    0x92,
    0x38,
    0x2B,
    0x34,
    0x89,
    0x9B,
    0xAD,
    0xF4,
    0x92,
    0xBB,
    0x1A,
    0x5A,
    0xC3,
    0xF1,
    0xB7,
    0x65,
    0xE9,
    0xF9,
    0x13,
    0xCB,
};

#ifdef SUPPORT_HASH_SM3
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SM3 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sm3_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x5A,
        0xE7,
        0x95,
        0x76,
        0x20,
        0x27,
        0x0F,
        0x78,
        0xF4,
        0xC3,
        0x42,
        0xBA,
        0x52,
        0xB6,
        0x39,
        0xE3,
        0x8B,
        0xA6,
        0x15,
        0xF0,
        0xF3,
        0x18,
        0x1A,
        0x79,
        0xB3,
        0x58,
        0x4D,
        0x50,
        0xD7,
        0x26,
        0x40,
        0x64,
        0x8B,
        0xBC,
        0x0E,
        0x3E,
        0x21,
        0x8D,
        0x75,
        0xBA,
        0xB9,
        0x95,
        0x16,
        0x37,
        0x44,
        0x0E,
        0xA5,
        0x30,
        0x9B,
        0x27,
        0x6D,
        0xF9,
        0xC2,
        0x3C,
        0x72,
        0x6F,
        0x57,
        0x63,
        0x3D,
        0x1B,
        0xFF,
        0x19,
        0x6D,
        0xA0,
        0x8F,
        0xEF,
        0xCD,
        0x02,
        0xC8,
        0x22,
        0xC9,
        0x27,
        0x5A,
        0xD6,
        0x97,
        0x8A,
        0x3B,
        0x07,
        0xF3,
        0xAF,
        0x6A,
        0xB6,
        0xC2,
        0xCA,
        0x17,
        0x3C,
        0x05,
        0xA8,
        0x39,
        0xC4,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x10,
        0xD0,
        0x39,
        0x0B,
        0x33,
        0x86,
        0xE7,
        0x63,
        0xB2,
        0x84,
        0x85,
        0x32,
        0x2F,
        0xAC,
        0xDC,
        0x30,
        0x9E,
        0x6A,
        0x4A,
        0x22,
        0x2D,
        0x4E,
        0x92,
        0x28,
        0xC6,
        0xC3,
        0x4E,
        0xC2,
        0x96,
        0x41,
        0x0A,
        0xF0,
        0x70,
        0x1F,
        0x6E,
        0xF5,
        0xB5,
        0xD7,
        0x2A,
        0x04,
        0x86,
        0xE7,
        0x60,
        0xCA,
        0x5F,
        0xF6,
        0x07,
        0x4C,
        0x5D,
        0xB6,
        0x55,
        0x08,
        0x6E,
        0xD0,
        0xD9,
        0xE2,
        0x20,
        0x79,
        0x6E,
        0x6D,
        0xE1,
        0x28,
        0xB0,
        0xBC,
        0x29,
        0x40,
        0x6B,
        0x0E,
        0x66,
        0xDE,
        0x40,
        0xA7,
        0x60,
        0x16,
        0xCE,
        0xA5,
        0x13,
        0x96,
        0x91,
        0x40,
        0x5F,
        0xDA,
        0x14,
        0x2C,
        0x95,
        0x09,
        0xC1,
        0x4A,
        0xA8,
        0x21,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SM3, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SM3, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_MD5
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using MD5 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int md5_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0xF6,
        0xBE,
        0x99,
        0x67,
        0x25,
        0x0D,
        0xA6,
        0xC1,
        0xF3,
        0x2E,
        0xF7,
        0x2E,
        0x9B,
        0x59,
        0x6E,
        0x19,
        0x0A,
        0x61,
        0xB6,
        0x4F,
        0xEB,
        0x62,
        0xC1,
        0xFE,
        0x8B,
        0x34,
        0xEE,
        0x3C,
        0xE1,
        0xC3,
        0x44,
        0xEC,
        0x9D,
        0x28,
        0x67,
        0xE5,
        0x82,
        0x90,
        0x28,
        0x0E,
        0xE1,
        0xD0,
        0x25,
        0x82,
        0xEA,
        0x40,
        0xEF,
        0x07,
        0xD9,
        0xF8,
        0xF3,
        0x54,
        0xE5,
        0xE1,
        0x56,
        0xAC,
        0xA6,
        0x83,
        0xC0,
        0x32,
        0xDA,
        0x03,
        0x10,
        0xE5,
        0xDC,
        0xB4,
        0x05,
        0x5B,
        0x85,
        0x8C,
        0x16,
        0x59,
        0x4A,
        0x15,
        0x8E,
        0xD3,
        0x4D,
        0x9F,
        0xFD,
        0xDC,
        0x15,
        0x0B,
        0xD5,
        0xB0,
        0x91,
        0xDD,
        0x8A,
        0x15,
        0x87,
        0x74,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0xa8,
        0xd7,
        0x08,
        0x44,
        0x48,
        0xb9,
        0xbe,
        0xe6,
        0xe3,
        0x8b,
        0x57,
        0x59,
        0x2d,
        0x46,
        0xda,
        0x65,
        0xd9,
        0x53,
        0x90,
        0x74,
        0x85,
        0x58,
        0x99,
        0x48,
        0xe4,
        0x75,
        0x53,
        0x06,
        0xe9,
        0x1a,
        0x00,
        0xdf,
        0x11,
        0xba,
        0x1c,
        0x75,
        0x58,
        0xd8,
        0x30,
        0x50,
        0x87,
        0xfc,
        0x90,
        0xf2,
        0xad,
        0x25,
        0x52,
        0x70,
        0xcd,
        0xd3,
        0xc1,
        0x6c,
        0x9d,
        0xd0,
        0x13,
        0xd6,
        0xa9,
        0x64,
        0xbf,
        0x23,
        0xc9,
        0x39,
        0x75,
        0x68,
        0xd7,
        0x5a,
        0x7b,
        0x85,
        0x76,
        0xff,
        0x6f,
        0xb2,
        0xaa,
        0x93,
        0xb9,
        0xb2,
        0x79,
        0x0f,
        0xe9,
        0x95,
        0xb3,
        0x0a,
        0x38,
        0x54,
        0x5b,
        0x79,
        0xa1,
        0x98,
        0x01,
        0x38,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_MD5, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_MD5, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA256
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA256 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha256_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x31,
        0x34,
        0xD9,
        0xF6,
        0x76,
        0x9D,
        0x56,
        0x9F,
        0x27,
        0xCD,
        0x4F,
        0xEE,
        0xF3,
        0xBD,
        0x5F,
        0x4C,
        0xDB,
        0x99,
        0x29,
        0x4C,
        0x4E,
        0x6D,
        0xBD,
        0xC7,
        0x53,
        0x5F,
        0xAE,
        0xC9,
        0x6F,
        0x34,
        0x13,
        0x60,
        0x14,
        0x84,
        0xE3,
        0xBC,
        0x05,
        0xDF,
        0x67,
        0xB0,
        0x84,
        0xB9,
        0x99,
        0x3F,
        0x22,
        0x49,
        0x8A,
        0x1D,
        0x35,
        0xCA,
        0x93,
        0xD2,
        0x10,
        0x87,
        0xF4,
        0x1E,
        0x48,
        0xBC,
        0x33,
        0x3F,
        0x49,
        0x77,
        0x65,
        0x12,
        0x50,
        0xB6,
        0xEA,
        0xE1,
        0xFE,
        0xE2,
        0x69,
        0x7E,
        0xA1,
        0x87,
        0x9F,
        0xDD,
        0x32,
        0x1B,
        0x4F,
        0x2F,
        0x61,
        0x23,
        0x2D,
        0x11,
        0xFF,
        0x27,
        0x67,
        0x52,
        0x1D,
        0x00,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x7D,
        0x10,
        0x73,
        0x7D,
        0x5B,
        0xEF,
        0x6E,
        0xA8,
        0x6A,
        0x49,
        0xA5,
        0x7D,
        0x49,
        0xE1,
        0xFC,
        0xF8,
        0x27,
        0xCC,
        0xFD,
        0xC8,
        0x3D,
        0x86,
        0x14,
        0x52,
        0x47,
        0xF6,
        0x15,
        0x51,
        0x5C,
        0xD2,
        0xFC,
        0xC6,
        0xC3,
        0x5F,
        0x39,
        0xD6,
        0x6B,
        0xE5,
        0xDE,
        0x40,
        0x14,
        0x0B,
        0x3E,
        0x6E,
        0x7E,
        0xD5,
        0x1A,
        0x90,
        0x55,
        0x79,
        0xC0,
        0xD3,
        0x6A,
        0x8F,
        0xC0,
        0xFE,
        0x09,
        0xF6,
        0x7F,
        0x27,
        0xB8,
        0x65,
        0xBA,
        0xDA,
        0x3E,
        0x4A,
        0xA7,
        0x9F,
        0xCB,
        0x0B,
        0xAA,
        0x05,
        0x59,
        0xDF,
        0x54,
        0xC2,
        0x23,
        0x40,
        0x4A,
        0xE1,
        0xAD,
        0x9C,
        0x42,
        0x32,
        0xF7,
        0xF5,
        0x40,
        0xE9,
        0xBC,
        0x57,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA256, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA256, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA384
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA384 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha384_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0xD3,
        0x53,
        0x41,
        0x52,
        0x4C,
        0x2E,
        0x70,
        0xB7,
        0xEC,
        0x99,
        0xE1,
        0x92,
        0xC4,
        0xBC,
        0x49,
        0xD2,
        0x1D,
        0x31,
        0xE9,
        0xB0,
        0x59,
        0x88,
        0x3B,
        0x54,
        0xC7,
        0x2E,
        0x51,
        0x21,
        0x4F,
        0x56,
        0xD1,
        0xF0,
        0x75,
        0xF6,
        0x37,
        0x8B,
        0x5F,
        0x81,
        0x54,
        0x5F,
        0x90,
        0xBF,
        0xED,
        0x2B,
        0x72,
        0x35,
        0x39,
        0x20,
        0x64,
        0x4F,
        0xC1,
        0xDA,
        0xCF,
        0x77,
        0x61,
        0xCF,
        0x9C,
        0xA1,
        0x12,
        0xFA,
        0x54,
        0xB8,
        0x4F,
        0x79,
        0x36,
        0xFC,
        0x7E,
        0x93,
        0x8B,
        0xA7,
        0x4F,
        0xCD,
        0x20,
        0x0A,
        0x07,
        0x49,
        0x6C,
        0xE6,
        0xE4,
        0x52,
        0x06,
        0x05,
        0x64,
        0x08,
        0xF7,
        0x00,
        0x11,
        0x96,
        0xAE,
        0xF8,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0xEB,
        0x8D,
        0xCD,
        0xDA,
        0xD7,
        0x52,
        0x1E,
        0x59,
        0x9B,
        0xA6,
        0x77,
        0xC9,
        0xB5,
        0xD8,
        0xDE,
        0xC1,
        0xE1,
        0x22,
        0x8F,
        0xE2,
        0x94,
        0x54,
        0x9F,
        0xC4,
        0xCB,
        0xFA,
        0x63,
        0x7D,
        0x4F,
        0x61,
        0xCD,
        0x44,
        0x2A,
        0x58,
        0x5D,
        0xE8,
        0x25,
        0x7A,
        0x40,
        0x11,
        0xD7,
        0xF9,
        0xFA,
        0x3F,
        0x61,
        0x21,
        0x3E,
        0x4B,
        0xDE,
        0xB2,
        0x3A,
        0x83,
        0xBA,
        0xCA,
        0xFB,
        0x54,
        0x68,
        0x58,
        0xDD,
        0x19,
        0x16,
        0xCD,
        0xC7,
        0x3F,
        0x11,
        0x4D,
        0x37,
        0x82,
        0x5E,
        0xAD,
        0xC7,
        0xEA,
        0x74,
        0xCB,
        0xE6,
        0x1D,
        0x81,
        0x81,
        0x39,
        0x7F,
        0xC2,
        0x1F,
        0xA2,
        0xF9,
        0x86,
        0x0D,
        0xF5,
        0xAB,
        0x74,
        0x07,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA384, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA384, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA512
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA512 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha512_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0xB0,
        0xF5,
        0x2F,
        0x91,
        0xD3,
        0x57,
        0xAF,
        0xB8,
        0xF9,
        0x92,
        0x8E,
        0x42,
        0x84,
        0xC0,
        0x28,
        0x50,
        0xE8,
        0xB0,
        0x06,
        0x55,
        0xB6,
        0xA8,
        0xA9,
        0x76,
        0x59,
        0x0A,
        0x1D,
        0x8E,
        0x6B,
        0x4B,
        0x12,
        0xE3,
        0x0B,
        0xF6,
        0xE4,
        0x06,
        0x43,
        0x4A,
        0xFC,
        0xE6,
        0x4D,
        0x0A,
        0x06,
        0xB4,
        0xF9,
        0x92,
        0xF5,
        0x93,
        0x66,
        0xEA,
        0x2C,
        0x42,
        0xCB,
        0x06,
        0x73,
        0xE0,
        0x7F,
        0x3D,
        0x05,
        0xEE,
        0xFF,
        0xF2,
        0xB0,
        0x07,
        0x93,
        0xF7,
        0x01,
        0x65,
        0xD6,
        0x15,
        0xD9,
        0xCA,
        0x81,
        0x5B,
        0xC2,
        0x6E,
        0xD3,
        0x83,
        0x5E,
        0x3E,
        0xE7,
        0xFB,
        0x9A,
        0x87,
        0xC6,
        0x61,
        0xB6,
        0x7F,
        0xCC,
        0x4F,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x7A,
        0x2E,
        0xFF,
        0x42,
        0xE8,
        0x01,
        0x7D,
        0xFB,
        0x21,
        0x21,
        0x06,
        0xFA,
        0xC6,
        0x41,
        0x54,
        0x6F,
        0x41,
        0x40,
        0x53,
        0x4F,
        0xE9,
        0x90,
        0xBE,
        0x74,
        0xCD,
        0xE3,
        0xCD,
        0x1D,
        0xC5,
        0xB2,
        0x9F,
        0x01,
        0x50,
        0x29,
        0x55,
        0xF8,
        0xDE,
        0xB3,
        0xA8,
        0x95,
        0x48,
        0x14,
        0x0D,
        0xA0,
        0x7A,
        0x63,
        0x50,
        0x04,
        0xEA,
        0xE4,
        0x50,
        0x29,
        0xA2,
        0xBB,
        0xF5,
        0xCA,
        0xDC,
        0x49,
        0xA0,
        0xD5,
        0x84,
        0x80,
        0xF4,
        0xC8,
        0x4B,
        0x47,
        0x6B,
        0x4A,
        0x0B,
        0x0C,
        0x8C,
        0x4F,
        0xF8,
        0xBA,
        0x47,
        0x03,
        0x1D,
        0x5A,
        0x15,
        0xE2,
        0xE7,
        0xE2,
        0x06,
        0x0B,
        0x55,
        0x4E,
        0x95,
        0x14,
        0x67,
        0xBF,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA1
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA1 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha1_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x5D,
        0x72,
        0x8B,
        0xD4,
        0xD6,
        0x3C,
        0x37,
        0xB8,
        0x0F,
        0xFC,
        0x10,
        0x71,
        0x5D,
        0xC1,
        0x11,
        0xAC,
        0x91,
        0xF5,
        0xD4,
        0xEF,
        0xD2,
        0x62,
        0x2A,
        0xA4,
        0x65,
        0x3A,
        0x8E,
        0xD2,
        0x23,
        0xB2,
        0x57,
        0xBC,
        0x9C,
        0xBA,
        0x5F,
        0x5D,
        0x0A,
        0x27,
        0x0D,
        0x63,
        0x96,
        0xE9,
        0x11,
        0x8E,
        0x87,
        0x97,
        0x7F,
        0x1F,
        0x17,
        0xE1,
        0x62,
        0x67,
        0x23,
        0x57,
        0xE6,
        0xA8,
        0xF7,
        0x08,
        0x71,
        0x2A,
        0x56,
        0x22,
        0xBD,
        0x1C,
        0xF0,
        0xCE,
        0x88,
        0x91,
        0x2C,
        0xE2,
        0xB5,
        0x74,
        0xB9,
        0x54,
        0x7D,
        0x08,
        0x4E,
        0xB4,
        0xAE,
        0x49,
        0x01,
        0x50,
        0xA0,
        0x37,
        0x7D,
        0xFC,
        0x58,
        0x98,
        0x0A,
        0x60,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x57,
        0x66,
        0xDF,
        0x2D,
        0x0F,
        0x31,
        0xA6,
        0x0F,
        0xE1,
        0x45,
        0x17,
        0x92,
        0xF9,
        0x4D,
        0x94,
        0x4D,
        0xAC,
        0x4F,
        0x78,
        0xD3,
        0x3B,
        0xB9,
        0x6E,
        0x77,
        0xA6,
        0x62,
        0x4B,
        0xD0,
        0x68,
        0x10,
        0xEF,
        0x78,
        0x36,
        0x55,
        0xCF,
        0x89,
        0x24,
        0x87,
        0xD9,
        0x90,
        0xA7,
        0x7E,
        0x30,
        0x1C,
        0x43,
        0x9A,
        0xA1,
        0xB6,
        0xCC,
        0x3A,
        0x81,
        0x16,
        0xD9,
        0xB2,
        0xEB,
        0xA5,
        0x30,
        0xBA,
        0xB8,
        0x9A,
        0x3B,
        0x16,
        0x4C,
        0xAE,
        0x47,
        0x78,
        0x29,
        0x1B,
        0xCC,
        0x53,
        0xBB,
        0x38,
        0x0C,
        0x3D,
        0x9D,
        0x3D,
        0xDB,
        0x65,
        0x26,
        0x2D,
        0x92,
        0xE3,
        0x88,
        0xAA,
        0xAB,
        0x92,
        0x62,
        0x6C,
        0xB0,
        0x27,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA1, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA1, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA224
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA224 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha224_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x75,
        0x14,
        0x3F,
        0xFC,
        0x42,
        0x33,
        0x2E,
        0x85,
        0x6B,
        0xF6,
        0x13,
        0x3D,
        0x0A,
        0x94,
        0xD1,
        0xC6,
        0x35,
        0x77,
        0xBB,
        0x4B,
        0xFB,
        0xF8,
        0xDE,
        0x89,
        0xF4,
        0x87,
        0x2A,
        0xCF,
        0x52,
        0xA4,
        0xC8,
        0xBF,
        0xA6,
        0xCD,
        0x70,
        0x81,
        0xE9,
        0x06,
        0xB6,
        0x08,
        0x31,
        0xBE,
        0x3F,
        0xBF,
        0xB3,
        0x74,
        0xE7,
        0xF8,
        0xAA,
        0x01,
        0xCB,
        0x3B,
        0x52,
        0x80,
        0x22,
        0x1F,
        0xFE,
        0x02,
        0xEB,
        0xE3,
        0x21,
        0x9A,
        0xAB,
        0x8F,
        0x92,
        0x96,
        0x53,
        0x40,
        0x19,
        0xFC,
        0x9A,
        0x7F,
        0xD1,
        0x55,
        0xE2,
        0x86,
        0x9A,
        0x9A,
        0xC1,
        0x78,
        0x74,
        0xB6,
        0x06,
        0x6C,
        0x49,
        0xA3,
        0x1F,
        0xDA,
        0x17,
        0xC7,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x0F,
        0xF6,
        0x07,
        0xB8,
        0x66,
        0xE2,
        0x44,
        0x10,
        0x32,
        0x47,
        0x35,
        0x81,
        0x15,
        0xCF,
        0x35,
        0x79,
        0x0E,
        0xCA,
        0xD3,
        0xA7,
        0xB9,
        0x41,
        0x82,
        0x73,
        0xE0,
        0xA2,
        0xB4,
        0x14,
        0x75,
        0x02,
        0x2C,
        0x96,
        0x7C,
        0x2D,
        0xC6,
        0xF9,
        0x47,
        0x2F,
        0xD4,
        0x6A,
        0x12,
        0xE5,
        0xF3,
        0xA0,
        0xF0,
        0x47,
        0x6F,
        0xFD,
        0xDE,
        0x20,
        0x42,
        0xF8,
        0x4F,
        0x7B,
        0x0A,
        0x3C,
        0x95,
        0x83,
        0x29,
        0x21,
        0xE5,
        0xF4,
        0x77,
        0x99,
        0x52,
        0xE7,
        0x60,
        0x2E,
        0x36,
        0x36,
        0x42,
        0x07,
        0xED,
        0x26,
        0xC0,
        0x3D,
        0x60,
        0x6F,
        0x45,
        0xB5,
        0x6A,
        0xFB,
        0x06,
        0x5D,
        0x96,
        0xD3,
        0xF5,
        0x96,
        0x80,
        0xEC,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA224, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA224, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA512_224
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA512-224 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha512_224_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x50,
        0x25,
        0x7D,
        0xCF,
        0x7F,
        0xB1,
        0x8C,
        0xC8,
        0x1A,
        0x05,
        0x3D,
        0x47,
        0x31,
        0x2F,
        0x9D,
        0x26,
        0xF3,
        0x55,
        0x93,
        0x98,
        0x9E,
        0xED,
        0xB9,
        0xDA,
        0xC0,
        0x63,
        0x51,
        0x1C,
        0xF0,
        0x3E,
        0xC0,
        0xB2,
        0xF0,
        0x13,
        0x4C,
        0x6C,
        0x94,
        0x76,
        0x01,
        0x98,
        0xD3,
        0xA4,
        0xA3,
        0xFB,
        0xF2,
        0xBC,
        0xF7,
        0xDC,
        0xFE,
        0x8B,
        0x6E,
        0xF0,
        0xA1,
        0x98,
        0x2C,
        0x23,
        0xCA,
        0x93,
        0x28,
        0x55,
        0x9F,
        0x66,
        0xEC,
        0x23,
        0x96,
        0x29,
        0xA2,
        0x30,
        0x2A,
        0x25,
        0x4A,
        0xDB,
        0xC8,
        0x71,
        0xF3,
        0xF7,
        0x86,
        0x44,
        0xC5,
        0x78,
        0xAC,
        0x82,
        0xC0,
        0x4C,
        0x95,
        0xB7,
        0xFD,
        0x63,
        0xA5,
        0x62,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0xF7,
        0xA7,
        0x4D,
        0xB7,
        0xF7,
        0xA0,
        0xA5,
        0x2F,
        0xA1,
        0x65,
        0x4E,
        0x23,
        0x96,
        0x6A,
        0x88,
        0x20,
        0xB2,
        0xEE,
        0x76,
        0x5A,
        0xC1,
        0x9E,
        0xBC,
        0x0A,
        0x1E,
        0x4D,
        0x45,
        0x3B,
        0x3A,
        0x48,
        0x9E,
        0xA7,
        0xFB,
        0x18,
        0x5A,
        0x52,
        0x80,
        0x5D,
        0xE7,
        0xA3,
        0x1B,
        0x18,
        0x66,
        0xC7,
        0x1A,
        0x01,
        0xBC,
        0x74,
        0x7D,
        0xEF,
        0xDC,
        0xB4,
        0x2D,
        0x2F,
        0x5B,
        0x89,
        0xEA,
        0xFC,
        0x86,
        0x5F,
        0x74,
        0xCF,
        0x8F,
        0x59,
        0xF5,
        0x3A,
        0xD5,
        0x97,
        0x42,
        0x3A,
        0x96,
        0xB1,
        0x19,
        0x06,
        0xA4,
        0x0A,
        0x0F,
        0x50,
        0x20,
        0x2B,
        0x5A,
        0xA8,
        0x13,
        0x74,
        0x17,
        0x77,
        0x8E,
        0xD6,
        0xC5,
        0x1B,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512_224, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512_224, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA512_256
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA512-256 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha512_256_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x27,
        0xCF,
        0xA1,
        0x35,
        0xC5,
        0x9B,
        0x83,
        0x47,
        0x2B,
        0x76,
        0x7A,
        0x47,
        0x7D,
        0x4B,
        0x37,
        0x9D,
        0xE8,
        0xF2,
        0xAE,
        0xC9,
        0xE9,
        0xA4,
        0xF2,
        0x38,
        0x07,
        0xA0,
        0x8B,
        0xB7,
        0x8D,
        0x08,
        0x02,
        0x89,
        0x29,
        0xF5,
        0x00,
        0x3E,
        0x86,
        0xC4,
        0x15,
        0x2B,
        0xF7,
        0xBA,
        0x4F,
        0x2C,
        0xB2,
        0x6C,
        0x16,
        0x76,
        0xA4,
        0x5C,
        0x28,
        0x36,
        0xA2,
        0x15,
        0xFC,
        0xCC,
        0x1E,
        0xB3,
        0xBD,
        0xE8,
        0x7D,
        0xE8,
        0x7E,
        0xA2,
        0x8C,
        0x45,
        0x4A,
        0x39,
        0x3C,
        0x7A,
        0x45,
        0x9B,
        0xC1,
        0xC2,
        0x2F,
        0xFD,
        0x3D,
        0xF3,
        0xF6,
        0x41,
        0x10,
        0xA1,
        0xD2,
        0xC1,
        0xA2,
        0x49,
        0xF2,
        0x5A,
        0x5B,
        0xCF,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x7B,
        0x2B,
        0x42,
        0x32,
        0x6A,
        0x94,
        0x8B,
        0x17,
        0x50,
        0xE4,
        0x41,
        0xE3,
        0xB8,
        0x9B,
        0xBF,
        0x08,
        0x83,
        0xDE,
        0x5E,
        0x10,
        0x40,
        0x56,
        0x2C,
        0x31,
        0x95,
        0x48,
        0x6F,
        0xF3,
        0x23,
        0x71,
        0xA7,
        0x83,
        0x8D,
        0xB2,
        0x77,
        0x5B,
        0x6C,
        0x1B,
        0x6E,
        0x3C,
        0x27,
        0x42,
        0x08,
        0x6F,
        0xAA,
        0x40,
        0xC1,
        0xF8,
        0xB1,
        0xBE,
        0x59,
        0x86,
        0x88,
        0x37,
        0x7D,
        0x84,
        0xFD,
        0x54,
        0x1F,
        0x4E,
        0x25,
        0xE9,
        0xC1,
        0x39,
        0x82,
        0x53,
        0x9B,
        0x59,
        0x1C,
        0xB0,
        0x50,
        0x4A,
        0xFF,
        0x63,
        0x45,
        0x9D,
        0xE9,
        0x05,
        0xAE,
        0x96,
        0x60,
        0xF4,
        0x1A,
        0xF4,
        0x8A,
        0x57,
        0x14,
        0x41,
        0xD4,
        0x7D,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512_256, std_z, 50, std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA512_256, std_z, 50, std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA3_224
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA3-224 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha3_224_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0xE3,
        0x5B,
        0x65,
        0xAB,
        0xA2,
        0x00,
        0xFC,
        0xA2,
        0x30,
        0x41,
        0xC0,
        0x1B,
        0x85,
        0xD2,
        0x81,
        0x47,
        0xCA,
        0xDB,
        0x57,
        0x99,
        0xD9,
        0x87,
        0xE8,
        0xFE,
        0xCA,
        0x24,
        0xB0,
        0x3E,
        0x23,
        0x3F,
        0x5D,
        0xAE,
        0xC7,
        0xDC,
        0x72,
        0xF3,
        0x13,
        0xDF,
        0xCB,
        0xA6,
        0x88,
        0x16,
        0x0F,
        0x86,
        0xEB,
        0xB9,
        0x8D,
        0x42,
        0x37,
        0x91,
        0xE7,
        0xED,
        0x63,
        0xF6,
        0x6F,
        0xE6,
        0x9E,
        0x70,
        0xE0,
        0xF2,
        0x51,
        0x17,
        0x89,
        0x3E,
        0xF5,
        0x8C,
        0x75,
        0x25,
        0x4E,
        0xEB,
        0x03,
        0xF1,
        0x90,
        0x3E,
        0x27,
        0x20,
        0x23,
        0xB1,
        0x5D,
        0x00,
        0x3C,
        0x11,
        0x63,
        0x5A,
        0x33,
        0xAD,
        0x34,
        0xA1,
        0xFE,
        0x31,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0xDB,
        0xEA,
        0xB0,
        0x13,
        0xC1,
        0x4E,
        0x76,
        0x20,
        0x10,
        0xA2,
        0x39,
        0x28,
        0xC9,
        0xFC,
        0x1E,
        0x2D,
        0xA7,
        0xF0,
        0x9A,
        0x2D,
        0x1D,
        0xE7,
        0x4D,
        0x60,
        0x32,
        0x8F,
        0x80,
        0x59,
        0x9D,
        0xC7,
        0x97,
        0x1A,
        0x43,
        0x8D,
        0x21,
        0x9E,
        0x94,
        0xBA,
        0xE8,
        0xA0,
        0xAB,
        0xEF,
        0x01,
        0x29,
        0x9C,
        0x77,
        0x1A,
        0xD6,
        0x11,
        0xE9,
        0x7B,
        0x6D,
        0x48,
        0x9E,
        0x0B,
        0xDB,
        0x10,
        0x70,
        0x35,
        0xEE,
        0xE6,
        0xD1,
        0x95,
        0x11,
        0x23,
        0x43,
        0x32,
        0x61,
        0x3F,
        0x80,
        0x34,
        0x78,
        0x05,
        0xCA,
        0xD8,
        0xE9,
        0xAE,
        0xEE,
        0x44,
        0x38,
        0x90,
        0x21,
        0xB6,
        0x68,
        0xEF,
        0x9B,
        0xD9,
        0xED,
        0x1A,
        0x77,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_224, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_224, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA3_256
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA3-256 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha3_256_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0xAA,
        0xF0,
        0x0A,
        0xC3,
        0x17,
        0xAF,
        0xED,
        0x5E,
        0xC0,
        0x96,
        0x28,
        0x17,
        0x5D,
        0xB1,
        0x04,
        0xAE,
        0xDB,
        0x4A,
        0xCD,
        0x1A,
        0x5D,
        0xE2,
        0xFB,
        0x6D,
        0x86,
        0x0E,
        0x69,
        0xA2,
        0x4E,
        0x0F,
        0xB6,
        0xE7,
        0x6B,
        0x2B,
        0x86,
        0x09,
        0x28,
        0xCA,
        0x9F,
        0x89,
        0x30,
        0xB0,
        0x86,
        0x19,
        0xB3,
        0xEF,
        0xEF,
        0x0D,
        0x04,
        0xAB,
        0x37,
        0x66,
        0x54,
        0x9E,
        0x6F,
        0x89,
        0x50,
        0xAF,
        0x4F,
        0xB7,
        0x35,
        0xBB,
        0x59,
        0x9B,
        0xD8,
        0x4E,
        0xD5,
        0xAB,
        0xD0,
        0x67,
        0x31,
        0x5F,
        0x2B,
        0x05,
        0xE4,
        0x1F,
        0x66,
        0x1B,
        0x2A,
        0x0E,
        0xA1,
        0x59,
        0x9E,
        0x30,
        0xB7,
        0x9B,
        0xFD,
        0x7A,
        0x7A,
        0xB5,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0xB6,
        0xA7,
        0xD8,
        0xD5,
        0xBB,
        0x7D,
        0x5F,
        0xDB,
        0x6E,
        0x82,
        0x74,
        0x44,
        0xBF,
        0x37,
        0x2B,
        0x0E,
        0x12,
        0x35,
        0xA6,
        0x6C,
        0x3B,
        0x24,
        0x63,
        0xE9,
        0x84,
        0xDE,
        0x29,
        0x73,
        0x5A,
        0x8B,
        0xF3,
        0xBC,
        0xFD,
        0x24,
        0x23,
        0xC8,
        0xBC,
        0x0B,
        0x16,
        0x34,
        0x43,
        0xB1,
        0xEA,
        0x83,
        0xF4,
        0xC9,
        0xE2,
        0x3A,
        0x04,
        0xFD,
        0x3C,
        0x87,
        0x41,
        0x2E,
        0xBA,
        0xC6,
        0x7F,
        0x47,
        0x93,
        0x62,
        0x68,
        0x6C,
        0x14,
        0x4B,
        0xF8,
        0x60,
        0x70,
        0x54,
        0xF3,
        0xA1,
        0x71,
        0xFC,
        0x3E,
        0x8A,
        0xCD,
        0x9B,
        0xD7,
        0xB4,
        0x76,
        0xBF,
        0xDF,
        0xB2,
        0xE4,
        0x1B,
        0x22,
        0x40,
        0x19,
        0xC1,
        0x87,
        0x71,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_256, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_256, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA3_384
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA3-384 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha3_384_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x55,
        0x83,
        0xC0,
        0x0E,
        0x9E,
        0xAF,
        0x32,
        0xD0,
        0x5F,
        0x20,
        0x9E,
        0xAF,
        0xE5,
        0xED,
        0xA7,
        0x26,
        0x79,
        0xA1,
        0x59,
        0xFC,
        0xDC,
        0xAC,
        0x32,
        0x39,
        0xBE,
        0x36,
        0xF6,
        0x76,
        0xC3,
        0xB8,
        0x60,
        0x83,
        0xA5,
        0xCC,
        0xC5,
        0x45,
        0xBA,
        0xCA,
        0xB3,
        0xC7,
        0xE8,
        0xF6,
        0x93,
        0x36,
        0x2C,
        0x02,
        0x69,
        0xF2,
        0x0C,
        0xE6,
        0x9D,
        0x81,
        0xAE,
        0x34,
        0xD8,
        0x8D,
        0x50,
        0xD9,
        0x11,
        0xD0,
        0xF0,
        0xB3,
        0x8E,
        0x35,
        0x8B,
        0x71,
        0xBB,
        0x7F,
        0xA2,
        0xF1,
        0x53,
        0x06,
        0x7C,
        0xC4,
        0x47,
        0x6F,
        0x86,
        0x7B,
        0xA8,
        0x5D,
        0x20,
        0x4D,
        0xCC,
        0x78,
        0xD7,
        0xDA,
        0x84,
        0xD7,
        0x66,
        0xBD,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x89,
        0x48,
        0xEC,
        0x18,
        0x45,
        0xD4,
        0x5B,
        0xCF,
        0x80,
        0xBA,
        0x65,
        0x57,
        0xFF,
        0x53,
        0x6B,
        0xDF,
        0xF2,
        0xA3,
        0xD5,
        0xD4,
        0xD2,
        0xDA,
        0xBA,
        0x1E,
        0x64,
        0x8B,
        0x9B,
        0x3E,
        0xAF,
        0xAE,
        0x06,
        0xAF,
        0xEE,
        0xA1,
        0xAA,
        0x22,
        0x0E,
        0x9A,
        0x4B,
        0xC7,
        0x53,
        0xD7,
        0xE3,
        0x34,
        0x37,
        0xB0,
        0x1F,
        0xD3,
        0x9D,
        0x1A,
        0x4D,
        0x3A,
        0x32,
        0x33,
        0x12,
        0xF4,
        0x38,
        0x29,
        0xCB,
        0x4F,
        0x9B,
        0x56,
        0x25,
        0x45,
        0xDD,
        0x34,
        0x70,
        0xAF,
        0x56,
        0xA1,
        0xD7,
        0xE9,
        0x4C,
        0x14,
        0xE4,
        0xC9,
        0xB9,
        0x99,
        0x8D,
        0x15,
        0x40,
        0x6B,
        0x96,
        0x23,
        0x41,
        0x6F,
        0x7F,
        0x09,
        0x0E,
        0x0B,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_384, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_384, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

#ifdef SUPPORT_HASH_SHA3_512
/**
 * @brief           Perform self-test for ANSI X9.63 KDF using SHA3-512 algorithm
 * @return          0 if tests pass, non-zero error code if tests fail
 */
unsigned int sha3_512_ansi_x9_63_kdf_test(void)
{
    unsigned char std_z_50_s_0_k[90] = {
        0x4C,
        0x5E,
        0x61,
        0xE0,
        0xED,
        0xC7,
        0x55,
        0xBA,
        0x17,
        0x30,
        0x68,
        0x5C,
        0x88,
        0xE2,
        0x96,
        0x23,
        0xFE,
        0x51,
        0xE2,
        0x82,
        0x27,
        0x67,
        0xAC,
        0x1B,
        0x37,
        0xF7,
        0xF8,
        0x4F,
        0x46,
        0xA3,
        0xC0,
        0x92,
        0x0B,
        0xCB,
        0x89,
        0xFD,
        0xD9,
        0x52,
        0xCD,
        0xD7,
        0xEA,
        0x9E,
        0x2F,
        0xBE,
        0x06,
        0xD8,
        0x20,
        0x45,
        0x5D,
        0x24,
        0x69,
        0x8C,
        0x76,
        0x7C,
        0x2F,
        0x0D,
        0x69,
        0x3E,
        0x44,
        0xB0,
        0xB0,
        0x5E,
        0xEE,
        0xED,
        0xF8,
        0x4D,
        0x74,
        0x49,
        0xE0,
        0xE9,
        0x6E,
        0x90,
        0xEB,
        0xBE,
        0x76,
        0xEA,
        0xD4,
        0x88,
        0xD9,
        0xB4,
        0x02,
        0xDD,
        0xD2,
        0x8C,
        0xEE,
        0x3D,
        0x87,
        0x33,
        0x0A,
        0xD9,
    };

    unsigned char std_z_50_s_28_k[90] = {
        0x1D,
        0x0E,
        0x48,
        0x20,
        0x2E,
        0xFF,
        0x93,
        0xFB,
        0x7B,
        0xB5,
        0x80,
        0x44,
        0x52,
        0xDC,
        0x0B,
        0x99,
        0x8D,
        0xE9,
        0x62,
        0xC5,
        0xBC,
        0x41,
        0xA1,
        0xB0,
        0xD4,
        0x36,
        0x06,
        0x4C,
        0xE9,
        0x18,
        0xF9,
        0xCB,
        0x1E,
        0xD5,
        0x3C,
        0xE0,
        0xC3,
        0xB8,
        0x8D,
        0xEF,
        0xE2,
        0xD5,
        0x2F,
        0x2C,
        0x2C,
        0xE6,
        0x97,
        0x5B,
        0xD2,
        0xEF,
        0x12,
        0xF5,
        0x54,
        0x2E,
        0x90,
        0xB9,
        0x8C,
        0xCB,
        0xBC,
        0x8C,
        0xBF,
        0xAC,
        0x6C,
        0x3C,
        0xE0,
        0x81,
        0xF4,
        0xA0,
        0x63,
        0x56,
        0x76,
        0xBC,
        0x11,
        0x70,
        0x11,
        0x25,
        0xF3,
        0xF7,
        0x3D,
        0x1B,
        0xFE,
        0xD2,
        0x5C,
        0x9A,
        0xEF,
        0xF1,
        0x57,
        0xBD,
        0x40,
        0x09,
    };

    unsigned int ret;

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_512, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 0, std_z_50_s_0_k, 90, "1");
    if (ret)
    {
        return 1;
    }

    ret = ansi_x9_63_kdf_test_internal(HASH_SHA3_512, (unsigned char *)std_z, 50, (unsigned char *)std_shared_info, 28, std_z_50_s_28_k, 90, "2");
    if (ret)
    {
        return 1;
    }

    return 0;
}
#endif

/**
 * @brief           Perform comprehensive self-test for all supported ANSI X9.63 KDF algorithms
 * @return          0 if all tests pass, non-zero error code if any test fails
 */
unsigned int ansi_x9_63_kdf_all_test(void)
{
    unsigned int ret;

/**/
#ifdef SUPPORT_HASH_NODE
#ifdef SUPPORT_HASH_SM3
    ret = sm3_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_MD5
    ret = md5_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA256
    ret = sha256_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA384
    ret = sha384_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512
    ret = sha512_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA1
    ret = sha1_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA224
    ret = sha224_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_224
    ret = sha512_224_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA512_256
    ret = sha512_256_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_224
    ret = sha3_224_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_256
    ret = sha3_256_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_384
    ret = sha3_384_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif

#ifdef SUPPORT_HASH_SHA3_512
    ret = sha3_512_ansi_x9_63_kdf_test();
    if (ret)
    {
        return 1;
    }
#endif
#endif
    /**/
    return 0;
}

#endif

#endif

/********************************************************************************************************
 * @file    ecies_test.c
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

#include "lib/include/pke/pke_config.h"


#ifdef SUPPORT_ECIES

    #include "lib/include/pke/ecies.h"
    #include "lib/include/crypto_common/utility.h"
    #include "lib/include/crypto_common/eccp_curve.h"
    #include "lib/include/trng/trng.h"
    #include "lib/include/hash/hash.h"


//#define ECIES_SPEED_TEST_BY_TIMER

//#define ECIES_SPEED_TEST_POINT_COMPRESS


    #ifdef ECIES_SPEED_TEST_BY_TIMER
extern unsigned int startP(void);
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
    #endif


    #define ECIES_ENC_DEC_ROUND1 (2)


unsigned char msg_1[] = {0x61, 0x62, 0x63, 0x61, 0x62, 0x63}; //6
unsigned char msg_2[] = {
    0x33,
    0x33,
    0x33,
    0x20,
    0x71,
    0x75,
    0x69,
    0x63,
    0x6B,
    0x20,
    0x62,
    0x72,
    0x6F,
    0x77,
    0x6E,
    0x20,
    0x66,
    0x6F,
    0x78,
    0x20,
    0x6A,
    0x75,
    0x6D,
    0x70,
    0x73,
    0x20,
    0x6F,
    0x76,
    0x65,
    0x72,
    0x20,
    0x74,
    0x68,
    0x65,
    0x20,
    0x6C,
    0x61,
    0x7A,
    0x79,
    0x44,
    0x44,
    0x44,
    0x44}; //43

unsigned char msg_s[] = {
    0x33,
    0x33,
    0x33,
    0x20,
    0x71,
    0x75,
    0x69,
    0x63,
    0x6B,
    0x20,
    0x62,
    0x72,
    0x6F,
    0x77,
    0x6E,
    0x20,
    0x66,
    0x6F,
    0x78,
    0x20,
    0x6A,
    0x75,
    0x6D,
    0x70,
    0x73,
    0x20,
    0x6F,
    0x76,
    0x65,
    0x72,
    0x20,
    0x74,
    0x68,
    0x65,
    0x20,
    0x6C,
    0x61,
    0x7A,
    0x79,
    0x44,
    0x44,
    0x44,
    0x44,
    0x72,
    0x6F,
    0x77,
    0x6E,
    0x20,
    0x66,
    0x6F,
    0x78,
    0x20,
    0x6A,
    0x75,
    0x6D,
    0x70,
    0x73,
    0x20,
    0x6F,
    0x76,
    0x65,
    0x72,
    0x20,
    0x74,
}; //64

unsigned char shared_info1_1[] = {0x61, 0x62, 0x63};
unsigned char shared_info1_2[] = {
    0xA7,
    0xF3,
    0x59,
    0xB4,
    0x68,
    0x55,
    0xC4,
    0x8A,
    0x1B,
    0x67,
    0x2F,
    0x1C,
    0x65,
    0xFB,
    0x57,
    0xA8,
    0xF5,
    0x58,
    0x1A,
    0xD4,
    0xA9,
    0x6A,
    0xA0,
    0x63,
    0x7C,
    0x4D,
    0x36,
    0xF4,
    0x4B,
    0xCD,
    0xFB,
    0xA5,
    0xD0,
    0x10,
    0x1E,
    0x5E,
    0xCB,
    0xAF,
    0x6F,
    0x4F,
    0xEA,
    0x3C,
    0xD2,
    0x70,
    0x6B,
    0x45,
    0x96,
    0x50,
    0xD9,
    0x08,
    0x9F,
};

unsigned char shared_info2_1[] = {0x61, 0x62, 0x63, 0x64, 0x65};
unsigned char shared_info2_2[] = {
    0xAF,
    0x48,
    0xA8,
    0x6D,
    0xF8,
    0x72,
    0xF3,
    0x24,
    0x09,
    0xA6,
    0x25,
    0x86,
    0x22,
    0x33,
    0xE6,
    0xCC,
    0xCB,
    0x4F,
    0xC6,
    0x76,
    0xF8,
    0x3A,
    0xE7,
    0x57,
    0xEC,
    0x3D,
    0x37,
    0x17,
    0x4E,
    0x6C,
    0x3D,
    0x29,
    0x56,
    0xF4,
    0x7D,
    0x39,
    0xE3,
    0x19,
    0x99,
    0x51,
    0x28,
    0x0A,
    0x17,
    0x21,
    0x9F,
    0xBC,
    0x96,
    0xDB,
    0x8A,
    0x8E,
    0x9E,
    0xE0,
    0xDC,
    0x05,
    0x88,
    0x59,
    0x32,
    0x9E,
    0xD1,
    0x71,
    0xA9,
    0x47,
    0xCB,
    0xE9,
    0x0A,
    0x0A};

typedef struct
{
    eccp_curve_t  *curve;
    char          *curve_name;
    unsigned char *msg;
    unsigned int   msg_bytes;
    unsigned char *shared_info1;
    unsigned int   shared_info1_bytes;
    unsigned char *shared_info2;
    unsigned int   shared_info2_bytes;
    unsigned char *receiver_pri_key;
    unsigned char *receiver_pub_key;
    EC_POINT_FORM  point_form;
    unsigned char *sender_tmp_pri_key; //ephemeral private key in encrypting
    HASH_ALG       kdf_hash_alg;
    HASH_ALG       mac_hash_alg;
    unsigned int   mac_k_bytes;
    unsigned char *cipher_part1;                     //part1 of cipher, this only depends on local_tmp_pri_key and peer_pub_key
    unsigned char *cipher_part2_part3_without_s1_s2; //part2 and part3 of cipher, here without shared_info1 and shared_info2
    unsigned char *cipher_part2_part3_with_s1;       //part2 and part3 of cipher, here only with shared_info1
    unsigned char *cipher_part2_part3_with_s2;       //part2 and part3 of cipher, here only with shared_info2
    unsigned char *cipher_part2_part3_with_s1_s2;    //part2 and part3 of cipher, here with shared_info1 and shared_info2

} ECIES_STD_TEST_VECTOR;

unsigned int ecies_std_test(ECIES_STD_TEST_VECTOR *vector)
{
    //byte length of ciphertext is (internal cipher byte length) + 1 + 2*curve_p_bytes + mac_bytes, so please
    //be careful about the cipher buffer size.
    unsigned char cipher[500];
    unsigned int  cipher_bytes = 0;
    unsigned char std_cipher[500];
    unsigned char std_cipher_s1[500];
    unsigned char std_cipher_s2[500];
    unsigned char std_cipher_s1_s2[500];
    unsigned int  std_cipher_bytes;
    unsigned int  cipher_part1_bytes, cipher_part2_bytes, cipher_part3_bytes;

    unsigned char *std_cipher_ptr;
    unsigned char *shared_info1_ptr, *shared_info2_ptr;
    unsigned int   shared_info1_bytes, shared_info2_bytes;

    unsigned char replain[400];
    unsigned int  replain_bytes = 0;

    char        *info[] = {"without shared info1 and shared info2", "only with shared inro1", "only with shared inro2", "with shared info1 and shared info2"};
    unsigned int i, ret;

    printf("\r\n\r\n ================= ECIES ANSI-X9.63 %s standard data(%s) test ================= \r\n",
           vector->curve_name,
           (vector->point_form == POINT_COMPRESSED) ? "POINT_COMPRESSED" : "POINT_UNCOMPRESSED");

    //set std_cipher
    switch (vector->point_form) {
    case POINT_UNCOMPRESSED:
        cipher_part1_bytes = 1 + 2 * GET_BYTE_LEN(vector->curve->eccp_p_bitLen);
        break;

    #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    case POINT_COMPRESSED:
        cipher_part1_bytes = 1 + GET_BYTE_LEN(vector->curve->eccp_p_bitLen);
        break;
    #endif

    default:
        return 1;
    }

    cipher_part2_bytes = vector->msg_bytes;
    cipher_part3_bytes = hash_get_digest_word_len(vector->mac_hash_alg) * 4;
    std_cipher_bytes   = cipher_part1_bytes + cipher_part2_bytes + cipher_part3_bytes;

    memcpy_(std_cipher, vector->cipher_part1, cipher_part1_bytes);
    memcpy_(std_cipher_s1, vector->cipher_part1, cipher_part1_bytes);
    memcpy_(std_cipher_s2, vector->cipher_part1, cipher_part1_bytes);
    memcpy_(std_cipher_s1_s2, vector->cipher_part1, cipher_part1_bytes);
    memcpy_(std_cipher + cipher_part1_bytes, vector->cipher_part2_part3_without_s1_s2, cipher_part2_bytes + cipher_part3_bytes);
    memcpy_(std_cipher_s1 + cipher_part1_bytes, vector->cipher_part2_part3_with_s1, cipher_part2_bytes + cipher_part3_bytes);
    memcpy_(std_cipher_s2 + cipher_part1_bytes, vector->cipher_part2_part3_with_s2, cipher_part2_bytes + cipher_part3_bytes);
    memcpy_(std_cipher_s1_s2 + cipher_part1_bytes, vector->cipher_part2_part3_with_s1_s2, cipher_part2_bytes + cipher_part3_bytes);

    //4 cases.
    for (i = 0; i < 4; i++) {
        if (0 == i) {
            shared_info1_ptr   = NULL;
            shared_info2_ptr   = NULL;
            std_cipher_ptr     = std_cipher;
            shared_info1_bytes = 0;
            shared_info2_bytes = 0;
        } else if (1 == i) {
            shared_info1_ptr   = vector->shared_info1;
            shared_info2_ptr   = NULL;
            std_cipher_ptr     = std_cipher_s1;
            shared_info1_bytes = vector->shared_info1_bytes;
            shared_info2_bytes = 0;
        } else if (2 == i) {
            shared_info1_ptr   = NULL;
            shared_info2_ptr   = vector->shared_info2;
            std_cipher_ptr     = std_cipher_s2;
            shared_info1_bytes = 0;
            shared_info2_bytes = vector->shared_info2_bytes;
        } else if (3 == i) {
            shared_info1_ptr   = vector->shared_info1;
            shared_info2_ptr   = vector->shared_info2;
            std_cipher_ptr     = std_cipher_s1_s2;
            shared_info1_bytes = vector->shared_info1_bytes;
            shared_info2_bytes = vector->shared_info2_bytes;
        }

        memset_(cipher, 0, sizeof(cipher));
        ret = ansi_x963_2001_ecies_encrypt(vector->curve, vector->msg, vector->msg_bytes, shared_info1_ptr, shared_info1_bytes, shared_info2_ptr, shared_info2_bytes, vector->sender_tmp_pri_key, vector->receiver_pub_key, vector->point_form, vector->kdf_hash_alg, vector->mac_hash_alg, vector->mac_k_bytes, cipher, &cipher_bytes);
        if ((ECIES_SUCCESS != ret) || (cipher_bytes != std_cipher_bytes) ||
            memcmp_(cipher, std_cipher_ptr, cipher_bytes)) {
            printf("\r\n ECIES AXSI-X9.63 %s enc test(%s) failure! ret = %x", vector->curve_name, info[i], ret);
            print_buf_U8(std_cipher_ptr, cipher_bytes, "std cipher");
            print_buf_U8(cipher, cipher_bytes, "cipher");
            return 1;
        } else {
            printf("\r\n ECIES AXSI-X9.63 %s enc test(%s) success! ", vector->curve_name, info[i]);
        }

        memset_(replain, 0, sizeof(replain));
        ret = ansi_x963_2001_ecies_decrypt(vector->curve, cipher, cipher_bytes, vector->receiver_pri_key, shared_info1_ptr, shared_info1_bytes, shared_info2_ptr, shared_info2_bytes, vector->kdf_hash_alg, vector->mac_hash_alg, vector->mac_k_bytes, replain, &replain_bytes);
        if ((ECIES_SUCCESS != ret) || (replain_bytes != vector->msg_bytes) || memcmp_(replain, vector->msg, vector->msg_bytes)) {
            printf("\r\n ECIES AXSI-X9.63 %s dec test(%s) failure! ret = %x", vector->curve_name, info[i], ret);
            print_buf_U8(cipher, cipher_bytes, "cipher");
            print_buf_U8(replain, replain_bytes, "replain");
            return 1;
        } else {
            printf("\r\n ECIES AXSI-X9.63 %s dec test(%s) success! \r\n", vector->curve_name, info[i]);
        }
    }

    return 0;
}

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))

unsigned int ecies_std_test_secp160k1(void)
{
    unsigned char receiver_pri_key[] = {
        0x00,
        0x6F,
        0x30,
        0x86,
        0x9B,
        0xD7,
        0xD8,
        0x48,
        0xC3,
        0x15,
        0xF7,
        0x6B,
        0xA1,
        0x98,
        0x07,
        0x57,
        0x73,
        0xFC,
        0xCB,
        0x29,
        0x3F,
    };
    unsigned char receiver_pub_key[] = {
        0xDD,
        0x71,
        0xE6,
        0x03,
        0x64,
        0x66,
        0xB0,
        0x82,
        0x71,
        0xCD,
        0xDF,
        0x73,
        0x12,
        0x8B,
        0xC5,
        0x47,
        0xEC,
        0x24,
        0x6A,
        0xFD,
        0x60,
        0xB0,
        0x23,
        0x5A,
        0x9C,
        0x62,
        0xDC,
        0xBC,
        0x77,
        0x4C,
        0x0E,
        0xEE,
        0xFD,
        0xAD,
        0x7B,
        0x38,
        0xB2,
        0xB1,
        0xB1,
        0x66,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x00,
        0x23,
        0x04,
        0x47,
        0xF3,
        0xAB,
        0x84,
        0xB2,
        0x2D,
        0x8A,
        0x3C,
        0xA3,
        0x41,
        0xC2,
        0xFE,
        0x46,
        0xFE,
        0x2B,
        0xF6,
        0xD1,
        0x21,
    };

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 32;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x8B,
        0x60,
        0x25,
        0x63,
        0x3A,
        0xDF,
        0x9A,
        0x86,
        0xD9,
        0x27,
        0xE7,
        0xF1,
        0x03,
        0xD6,
        0x3A,
        0xB6,
        0x3F,
        0x7C,
        0xAE,
        0xD8,
        0x8F,
        0x76,
        0x62,
        0x61,
        0x1A,
        0x39,
        0x95,
        0x29,
        0xC1,
        0x4C,
        0x82,
        0x7C,
        0x17,
        0x93,
        0x98,
        0x73,
        0x45,
        0x5C,
        0xF5,
        0x26,
        //2nd part: cihpher
        0x34,
        0x88,
        0x2D,
        0xF7,
        0x89,
        0x27,
        //3rd part: mac
        0x3F,
        0x6E,
        0x3C,
        0x69,
        0x6C,
        0x5B,
        0xF5,
        0x31,
        0xD5,
        0xC1,
        0x7F,
        0xA4,
        0xA2,
        0x8A,
        0x06,
        0x32,
        0x36,
        0x64,
        0x2C,
        0x23,
        0x0A,
        0x4C,
        0x7A,
        0x35,
        0x8B,
        0x80,
        0x7D,
        0x91,
        0xD2,
        0xA0,
        0x0E,
        0x5F,
        0xD8,
        0x06,
        0x0D,
        0x79,
        0x07,
        0xB7,
        0x82,
        0x8E,
        0x1D,
        0xF8,
        0xED,
        0xF3,
        0xFF,
        0xE8,
        0x3F,
        0xD1,
        0xE3,
        0x15,
        0x52,
        0x75,
        0x86,
        0x03,
        0x07,
        0x55,
        0xE4,
        0x23,
        0x21,
        0x88,
        0xCB,
        0x3F,
        0xAE,
        0x3A,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0x8B,
        0x60,
        0x25,
        0x63,
        0x3A,
        0xDF,
        0x9A,
        0x86,
        0xD9,
        0x27,
        0xE7,
        0xF1,
        0x03,
        0xD6,
        0x3A,
        0xB6,
        0x3F,
        0x7C,
        0xAE,
        0xD8,
        //2nd part: cihpher
        0x34,
        0x88,
        0x2D,
        0xF7,
        0x89,
        0x27,
        //3rd part: mac
        0x3F,
        0x6E,
        0x3C,
        0x69,
        0x6C,
        0x5B,
        0xF5,
        0x31,
        0xD5,
        0xC1,
        0x7F,
        0xA4,
        0xA2,
        0x8A,
        0x06,
        0x32,
        0x36,
        0x64,
        0x2C,
        0x23,
        0x0A,
        0x4C,
        0x7A,
        0x35,
        0x8B,
        0x80,
        0x7D,
        0x91,
        0xD2,
        0xA0,
        0x0E,
        0x5F,
        0xD8,
        0x06,
        0x0D,
        0x79,
        0x07,
        0xB7,
        0x82,
        0x8E,
        0x1D,
        0xF8,
        0xED,
        0xF3,
        0xFF,
        0xE8,
        0x3F,
        0xD1,
        0xE3,
        0x15,
        0x52,
        0x75,
        0x86,
        0x03,
        0x07,
        0x55,
        0xE4,
        0x23,
        0x21,
        0x88,
        0xCB,
        0x3F,
        0xAE,
        0x3A,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xC0,
        0x91,
        0x28,
        0xCD,
        0xE8,
        0x5B,
        //3rd part: mac
        0xAA,
        0xCD,
        0x12,
        0xC5,
        0x3B,
        0x8E,
        0xDA,
        0x10,
        0x4D,
        0xDC,
        0xA6,
        0x6E,
        0xB9,
        0xA5,
        0x84,
        0x38,
        0xDD,
        0xAB,
        0xEA,
        0x11,
        0x9B,
        0x13,
        0xB5,
        0xBE,
        0x32,
        0x93,
        0x9B,
        0x6A,
        0x99,
        0xD3,
        0x11,
        0x2B,
        0x50,
        0x3E,
        0x8F,
        0x44,
        0x56,
        0xC1,
        0x6C,
        0x60,
        0x7D,
        0x5B,
        0x72,
        0xA8,
        0xEB,
        0x08,
        0xE1,
        0x2D,
        0x9F,
        0x24,
        0x01,
        0x70,
        0xC1,
        0xB1,
        0xE7,
        0x01,
        0x55,
        0x02,
        0x9D,
        0xF7,
        0x77,
        0xEA,
        0x53,
        0x74,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x34,
        0x88,
        0x2D,
        0xF7,
        0x89,
        0x27,
        //3rd part: mac
        0x46,
        0xDD,
        0x13,
        0xB8,
        0x8A,
        0xF8,
        0xFC,
        0x7B,
        0xD8,
        0xB8,
        0x4D,
        0x42,
        0x9E,
        0xFE,
        0xE2,
        0x8B,
        0x4A,
        0xA3,
        0x8D,
        0x39,
        0x11,
        0xA9,
        0xB5,
        0xD3,
        0x14,
        0x96,
        0xB8,
        0x42,
        0xE7,
        0x7E,
        0xB5,
        0x18,
        0xBF,
        0x79,
        0x6A,
        0x6D,
        0xC3,
        0xEB,
        0x31,
        0x77,
        0x40,
        0xDE,
        0x7D,
        0x24,
        0x37,
        0x80,
        0x43,
        0x65,
        0xDF,
        0x93,
        0x24,
        0x97,
        0xBF,
        0xAF,
        0x48,
        0x88,
        0x24,
        0xB6,
        0x50,
        0xBC,
        0xF2,
        0x3E,
        0x96,
        0xA5,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xC0,
        0x91,
        0x28,
        0xCD,
        0xE8,
        0x5B,
        //3rd part: mac
        0x9F,
        0x2B,
        0x9D,
        0x9E,
        0x1C,
        0x0C,
        0x94,
        0xE2,
        0x7D,
        0xD9,
        0xDF,
        0x40,
        0xE8,
        0x13,
        0xA9,
        0x19,
        0xA6,
        0x95,
        0xD3,
        0x0C,
        0x14,
        0xDD,
        0x41,
        0x7B,
        0xA4,
        0x92,
        0xF8,
        0xA9,
        0x1A,
        0xF6,
        0x1E,
        0xB6,
        0x63,
        0xFA,
        0x4C,
        0xB4,
        0x78,
        0xD8,
        0xEE,
        0x59,
        0x94,
        0x95,
        0xEE,
        0xDD,
        0x33,
        0x8F,
        0x22,
        0xD5,
        0x4F,
        0x3E,
        0x22,
        0xED,
        0xA3,
        0x76,
        0xFF,
        0xFC,
        0xE9,
        0x7A,
        0x25,
        0xD1,
        0xAD,
        0xD1,
        0x78,
        0xFC,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp160k1;
    char         *curve_name = "secp160k1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
unsigned int ecies_std_test_secp192k1(void)
{
    unsigned char receiver_pri_key[] = {
        0x96,
        0x23,
        0x8C,
        0x7C,
        0xE2,
        0x6E,
        0xB1,
        0xC5,
        0x9C,
        0x04,
        0xF0,
        0xB5,
        0x9C,
        0x62,
        0xF4,
        0x18,
        0xEB,
        0x43,
        0xFE,
        0x22,
        0x3B,
        0x74,
        0x40,
        0x75,
    };
    unsigned char receiver_pub_key[] = {
        0x23,
        0xA3,
        0xD5,
        0xBA,
        0x5C,
        0xEB,
        0x2E,
        0x92,
        0xB1,
        0x61,
        0x85,
        0xFC,
        0x35,
        0x49,
        0x93,
        0x69,
        0x3A,
        0x66,
        0xD9,
        0x2D,
        0x77,
        0x5D,
        0xB2,
        0x8C,
        0x12,
        0x22,
        0x4F,
        0xAB,
        0xE2,
        0x7D,
        0x74,
        0x2F,
        0x29,
        0x1C,
        0xE8,
        0x3E,
        0xF1,
        0x45,
        0x6A,
        0x8F,
        0xA2,
        0xB4,
        0x94,
        0xAC,
        0xF3,
        0x9A,
        0xB7,
        0x70,
    };
    unsigned char sender_tmp_pri_key[] = {
        0xFA,
        0x21,
        0x70,
        0xBB,
        0x23,
        0x5A,
        0x0E,
        0x2D,
        0x84,
        0xCC,
        0x12,
        0x5D,
        0xCC,
        0xF3,
        0xDD,
        0xE2,
        0x9B,
        0xDA,
        0xE8,
        0x86,
        0x56,
        0x40,
        0x08,
        0xB3};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_1;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_1);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 64;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x99,
        0x74,
        0x32,
        0xB3,
        0xBD,
        0x82,
        0xC6,
        0x6D,
        0xBE,
        0x45,
        0x3D,
        0x4F,
        0x38,
        0x16,
        0xE8,
        0x75,
        0xF9,
        0xFF,
        0x04,
        0x11,
        0x62,
        0xD9,
        0x5D,
        0x92,
        0xC1,
        0x45,
        0xA5,
        0xE2,
        0x31,
        0xB0,
        0x37,
        0x00,
        0xD8,
        0xE5,
        0xF5,
        0x1C,
        0x1C,
        0xD8,
        0x54,
        0xEA,
        0xB4,
        0x12,
        0x7F,
        0xE5,
        0xFC,
        0xD0,
        0x21,
        0xA2,
        //2nd part: cihpher
        0xE5,
        0xFF,
        0xD9,
        0xF1,
        0xB5,
        0x74,
        0x6F,
        0x16,
        0xC5,
        0x2A,
        0x99,
        0x8A,
        0x88,
        0x31,
        0x46,
        0x74,
        0x37,
        0xD1,
        0x16,
        0x14,
        0x13,
        0x57,
        0x6E,
        0x8E,
        0x78,
        0x55,
        0x84,
        0x9A,
        0x2E,
        0x80,
        0xDF,
        0xD7,
        0xBA,
        0x06,
        0xBE,
        0x59,
        0xB7,
        0x7B,
        0xAD,
        0x85,
        0x57,
        0x76,
        0xA8,
        //3rd part: mac
        0xE6,
        0x94,
        0x5B,
        0x5B,
        0xE6,
        0x9E,
        0x55,
        0xE0,
        0x7D,
        0xEE,
        0x09,
        0xA5,
        0xE7,
        0x2E,
        0x6F,
        0x53,
        0x51,
        0x0E,
        0x1E,
        0xB9};

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0x99,
        0x74,
        0x32,
        0xB3,
        0xBD,
        0x82,
        0xC6,
        0x6D,
        0xBE,
        0x45,
        0x3D,
        0x4F,
        0x38,
        0x16,
        0xE8,
        0x75,
        0xF9,
        0xFF,
        0x04,
        0x11,
        0x62,
        0xD9,
        0x5D,
        0x92,
        //2nd part: cihpher
        0xE5,
        0xFF,
        0xD9,
        0xF1,
        0xB5,
        0x74,
        0x6F,
        0x16,
        0xC5,
        0x2A,
        0x99,
        0x8A,
        0x88,
        0x31,
        0x46,
        0x74,
        0x37,
        0xD1,
        0x16,
        0x14,
        0x13,
        0x57,
        0x6E,
        0x8E,
        0x78,
        0x55,
        0x84,
        0x9A,
        0x2E,
        0x80,
        0xDF,
        0xD7,
        0xBA,
        0x06,
        0xBE,
        0x59,
        0xB7,
        0x7B,
        0xAD,
        0x85,
        0x57,
        0x76,
        0xA8,
        //3rd part: mac
        0xE6,
        0x94,
        0x5B,
        0x5B,
        0xE6,
        0x9E,
        0x55,
        0xE0,
        0x7D,
        0xEE,
        0x09,
        0xA5,
        0xE7,
        0x2E,
        0x6F,
        0x53,
        0x51,
        0x0E,
        0x1E,
        0xB9};
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xF2,
        0x04,
        0x6B,
        0x91,
        0x87,
        0x11,
        0x67,
        0x20,
        0xE4,
        0xFF,
        0x5C,
        0xAB,
        0xB7,
        0x80,
        0xC4,
        0x1F,
        0x98,
        0xDF,
        0x59,
        0x32,
        0x68,
        0x1A,
        0x26,
        0x99,
        0xD7,
        0x9C,
        0x10,
        0xC3,
        0x6D,
        0xE5,
        0xF9,
        0x6F,
        0x75,
        0x3D,
        0xDC,
        0x29,
        0xC9,
        0x95,
        0xC6,
        0xE5,
        0x6C,
        0x9A,
        0x64,
        //3rd part: mac
        0x69,
        0x4E,
        0xE3,
        0x6F,
        0x32,
        0x7D,
        0x38,
        0x2C,
        0x05,
        0x08,
        0x26,
        0x61,
        0xD9,
        0x06,
        0xE2,
        0x10,
        0x44,
        0x1B,
        0xBF,
        0xDE};
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0xE5,
        0xFF,
        0xD9,
        0xF1,
        0xB5,
        0x74,
        0x6F,
        0x16,
        0xC5,
        0x2A,
        0x99,
        0x8A,
        0x88,
        0x31,
        0x46,
        0x74,
        0x37,
        0xD1,
        0x16,
        0x14,
        0x13,
        0x57,
        0x6E,
        0x8E,
        0x78,
        0x55,
        0x84,
        0x9A,
        0x2E,
        0x80,
        0xDF,
        0xD7,
        0xBA,
        0x06,
        0xBE,
        0x59,
        0xB7,
        0x7B,
        0xAD,
        0x85,
        0x57,
        0x76,
        0xA8,
        //3rd part: mac
        0x06,
        0x20,
        0xEE,
        0x43,
        0x1C,
        0xE7,
        0x8F,
        0xD2,
        0xF1,
        0xDB,
        0x1D,
        0xF5,
        0x6C,
        0x79,
        0x0D,
        0xD3,
        0x28,
        0xC7,
        0xEC,
        0xFD,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xF2,
        0x04,
        0x6B,
        0x91,
        0x87,
        0x11,
        0x67,
        0x20,
        0xE4,
        0xFF,
        0x5C,
        0xAB,
        0xB7,
        0x80,
        0xC4,
        0x1F,
        0x98,
        0xDF,
        0x59,
        0x32,
        0x68,
        0x1A,
        0x26,
        0x99,
        0xD7,
        0x9C,
        0x10,
        0xC3,
        0x6D,
        0xE5,
        0xF9,
        0x6F,
        0x75,
        0x3D,
        0xDC,
        0x29,
        0xC9,
        0x95,
        0xC6,
        0xE5,
        0x6C,
        0x9A,
        0x64,
        //3rd part: mac
        0x93,
        0x8C,
        0xB9,
        0x55,
        0xB1,
        0x51,
        0xD2,
        0x60,
        0x4E,
        0x70,
        0x36,
        0x45,
        0x5F,
        0x2F,
        0x84,
        0xD9,
        0xC0,
        0x8B,
        0x22,
        0x07};

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp192k1;
    char         *curve_name = "secp192k1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
unsigned int ecies_std_test_secp224k1(void)
{
    unsigned char receiver_pri_key[] = {
        0x00,
        0xD3,
        0x49,
        0xB8,
        0x5C,
        0xDB,
        0xB9,
        0x0D,
        0x32,
        0xB9,
        0x69,
        0xAB,
        0xBA,
        0x7A,
        0x2C,
        0xF2,
        0xF6,
        0x2D,
        0x07,
        0x01,
        0xCE,
        0xD6,
        0xBB,
        0xD7,
        0x66,
        0x88,
        0x36,
        0x5E,
        0x60,
    };
    unsigned char receiver_pub_key[] = {
        0x5B,
        0x1B,
        0xD6,
        0x14,
        0xB8,
        0xA6,
        0xBA,
        0xC5,
        0x45,
        0xC3,
        0x59,
        0xDB,
        0x68,
        0x5A,
        0x3F,
        0x77,
        0x36,
        0xB0,
        0x77,
        0x94,
        0x6B,
        0xE2,
        0x82,
        0x05,
        0x3C,
        0xAB,
        0x8B,
        0xBC,
        0x86,
        0x9B,
        0xEA,
        0xFB,
        0xE0,
        0x28,
        0x8F,
        0x18,
        0xC5,
        0xA1,
        0xBD,
        0xAD,
        0x30,
        0x1B,
        0x9B,
        0xD1,
        0xDF,
        0x0E,
        0xE6,
        0xB8,
        0x26,
        0x7F,
        0x34,
        0xFF,
        0x75,
        0xC2,
        0x23,
        0xF2,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x00,
        0x2D,
        0x65,
        0xED,
        0x59,
        0x37,
        0xC6,
        0x33,
        0xF5,
        0x4F,
        0x25,
        0xCB,
        0x88,
        0x86,
        0x3C,
        0x88,
        0x54,
        0x25,
        0x9A,
        0xFC,
        0x56,
        0xB4,
        0x64,
        0xDD,
        0xD7,
        0x0F,
        0x35,
        0xD9,
        0x9E};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 128;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0xA4,
        0x5C,
        0xAF,
        0x3E,
        0xC1,
        0xAC,
        0x9A,
        0xF3,
        0x62,
        0x87,
        0x36,
        0xC7,
        0xCD,
        0x93,
        0x0D,
        0xA1,
        0x2C,
        0xB0,
        0x2C,
        0x6F,
        0x7F,
        0x5F,
        0x9B,
        0x9E,
        0x83,
        0xC1,
        0xA0,
        0xDD,
        0xAD,
        0x8C,
        0xA2,
        0x08,
        0x72,
        0x6B,
        0x5D,
        0x13,
        0x33,
        0x2B,
        0xDA,
        0xF2,
        0x41,
        0x7C,
        0x7B,
        0x4F,
        0xF5,
        0x96,
        0xA6,
        0xD5,
        0x66,
        0x5A,
        0xD8,
        0x2B,
        0x9B,
        0xB6,
        0x43,
        0x6F,
        //2nd part: cihpher
        0x67,
        0x35,
        0x90,
        0x7A,
        0xE4,
        0x4B,
        //3rd part: mac
        0x26,
        0xA5,
        0xD7,
        0xB7,
        0x0F,
        0x84,
        0x47,
        0xFF,
        0x59,
        0x8F,
        0x64,
        0xD2,
        0x0A,
        0x0F,
        0x66,
        0x0C,
        0x95,
        0xE8,
        0xCE,
        0x0F,
        0x09,
        0x4B,
        0xD2,
        0xE6,
        0x0C,
        0x38,
        0xD2,
        0x68,
        0x14,
        0xC3,
        0x26,
        0x85,
        0xFB,
        0x5F,
        0x7A,
        0x77,
        0x0B,
        0xF7,
        0x6D,
        0xEC,
        0xD4,
        0x20,
        0xE0,
        0x65,
        0x75,
        0x06,
        0xCC,
        0x85,
        0x1C,
        0x60,
        0x06,
        0x55,
        0xE5,
        0x25,
        0x33,
        0x79,
        0xAC,
        0xFB,
        0xDF,
        0x82,
        0x70,
        0x3D,
        0x8B,
        0x07,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0xA4,
        0x5C,
        0xAF,
        0x3E,
        0xC1,
        0xAC,
        0x9A,
        0xF3,
        0x62,
        0x87,
        0x36,
        0xC7,
        0xCD,
        0x93,
        0x0D,
        0xA1,
        0x2C,
        0xB0,
        0x2C,
        0x6F,
        0x7F,
        0x5F,
        0x9B,
        0x9E,
        0x83,
        0xC1,
        0xA0,
        0xDD,
        //2nd part: cihpher
        0x67,
        0x35,
        0x90,
        0x7A,
        0xE4,
        0x4B,
        //3rd part: mac
        0x26,
        0xA5,
        0xD7,
        0xB7,
        0x0F,
        0x84,
        0x47,
        0xFF,
        0x59,
        0x8F,
        0x64,
        0xD2,
        0x0A,
        0x0F,
        0x66,
        0x0C,
        0x95,
        0xE8,
        0xCE,
        0x0F,
        0x09,
        0x4B,
        0xD2,
        0xE6,
        0x0C,
        0x38,
        0xD2,
        0x68,
        0x14,
        0xC3,
        0x26,
        0x85,
        0xFB,
        0x5F,
        0x7A,
        0x77,
        0x0B,
        0xF7,
        0x6D,
        0xEC,
        0xD4,
        0x20,
        0xE0,
        0x65,
        0x75,
        0x06,
        0xCC,
        0x85,
        0x1C,
        0x60,
        0x06,
        0x55,
        0xE5,
        0x25,
        0x33,
        0x79,
        0xAC,
        0xFB,
        0xDF,
        0x82,
        0x70,
        0x3D,
        0x8B,
        0x07,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x01,
        0x72,
        0x28,
        0x44,
        0xE3,
        0x41,
        //3rd part: mac
        0x37,
        0x0D,
        0x42,
        0x6C,
        0x1F,
        0x5B,
        0x8B,
        0x1C,
        0xF2,
        0x40,
        0x86,
        0x1B,
        0x71,
        0xCE,
        0x6E,
        0x22,
        0xE9,
        0x86,
        0x75,
        0xD5,
        0x84,
        0x06,
        0x7E,
        0xDF,
        0x8D,
        0xA6,
        0xF0,
        0x62,
        0x28,
        0xC4,
        0xFB,
        0xE2,
        0x8A,
        0x69,
        0x41,
        0xDD,
        0xEB,
        0xF6,
        0x1F,
        0x5A,
        0x9B,
        0xD9,
        0xB2,
        0xDF,
        0xDA,
        0xF5,
        0xC6,
        0x0E,
        0x6A,
        0x68,
        0xEF,
        0x02,
        0x71,
        0x83,
        0x98,
        0x7D,
        0x29,
        0xB4,
        0x4A,
        0xB6,
        0x93,
        0x78,
        0xFE,
        0xB6,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x67,
        0x35,
        0x90,
        0x7A,
        0xE4,
        0x4B,
        //3rd part: mac
        0xB6,
        0xD7,
        0x09,
        0x64,
        0xE8,
        0x00,
        0xF9,
        0x84,
        0x40,
        0x6C,
        0xAF,
        0x54,
        0x13,
        0xDE,
        0x7A,
        0xDF,
        0x50,
        0x2C,
        0x7B,
        0x01,
        0x73,
        0xF3,
        0x07,
        0x27,
        0x67,
        0x55,
        0x23,
        0x4D,
        0x44,
        0x67,
        0xB0,
        0xBF,
        0x41,
        0xE2,
        0x86,
        0x68,
        0x35,
        0x72,
        0x5C,
        0xD3,
        0x32,
        0xD9,
        0x75,
        0x5A,
        0x8C,
        0x12,
        0xD8,
        0x4E,
        0x45,
        0xF3,
        0x01,
        0xA9,
        0xC2,
        0x3C,
        0x43,
        0x79,
        0xDE,
        0x17,
        0x51,
        0x84,
        0xF7,
        0xC7,
        0x33,
        0x39,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x01,
        0x72,
        0x28,
        0x44,
        0xE3,
        0x41,
        //3rd part: mac
        0x63,
        0x3E,
        0xEE,
        0x91,
        0xB9,
        0xF1,
        0xE9,
        0x75,
        0xE9,
        0x1C,
        0xB3,
        0xCA,
        0x49,
        0x99,
        0x51,
        0x22,
        0x0B,
        0x31,
        0x3F,
        0x56,
        0x0D,
        0xCB,
        0x2F,
        0xC9,
        0x44,
        0xBA,
        0xAA,
        0x38,
        0x62,
        0xDD,
        0xEC,
        0xDA,
        0xB6,
        0xCE,
        0x3F,
        0xCE,
        0x3F,
        0x65,
        0xD9,
        0x83,
        0xB9,
        0xEE,
        0xC6,
        0x0D,
        0x0B,
        0x4C,
        0x29,
        0xD8,
        0xA5,
        0x66,
        0xB7,
        0xC0,
        0x14,
        0x15,
        0xB8,
        0xC1,
        0x8B,
        0x37,
        0x09,
        0x47,
        0x2E,
        0x36,
        0xD2,
        0x58,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp224k1;
    char         *curve_name = "secp224k1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif
    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
unsigned int ecies_std_test_secp256k1(void)
{
    unsigned char receiver_pri_key[] = {
        0x23,
        0xCD,
        0xCE,
        0xD0,
        0x66,
        0x09,
        0x5A,
        0xA7,
        0x2D,
        0xE0,
        0x19,
        0x25,
        0x09,
        0xA1,
        0xE5,
        0x40,
        0xDE,
        0x34,
        0x1C,
        0x1D,
        0x4D,
        0xC3,
        0xB1,
        0xDE,
        0xB8,
        0xA2,
        0x58,
        0xA6,
        0xBA,
        0x26,
        0x19,
        0x9C,
    };
    unsigned char receiver_pub_key[] = {
        0xE3,
        0xB2,
        0xEB,
        0xEC,
        0x78,
        0x3B,
        0xB2,
        0x30,
        0xF2,
        0x0F,
        0x33,
        0x6E,
        0x30,
        0xFB,
        0xA3,
        0xBA,
        0xDD,
        0x0A,
        0x34,
        0x53,
        0xB4,
        0xF6,
        0xDC,
        0xB7,
        0x7C,
        0x04,
        0x62,
        0xB5,
        0x16,
        0x6F,
        0x79,
        0x5A,
        0x17,
        0x1C,
        0x91,
        0xD5,
        0x60,
        0x42,
        0x77,
        0x08,
        0xED,
        0x15,
        0xDC,
        0xFF,
        0x24,
        0xE8,
        0x58,
        0x23,
        0x38,
        0x81,
        0xAD,
        0x24,
        0x78,
        0xCB,
        0xA0,
        0x5E,
        0xC9,
        0x14,
        0x58,
        0x36,
        0xB9,
        0xC7,
        0x87,
        0xD9,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x99,
        0x89,
        0x43,
        0xC4,
        0x7E,
        0x19,
        0x59,
        0x6D,
        0x12,
        0x6B,
        0xB3,
        0x3A,
        0xC7,
        0xC6,
        0x56,
        0xF7,
        0x64,
        0xD5,
        0x09,
        0xF2,
        0xF3,
        0x9A,
        0xA9,
        0xC0,
        0xA8,
        0x72,
        0x11,
        0x7B,
        0x9C,
        0xBA,
        0x3D,
        0x8C};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 32;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x38,
        0x2A,
        0x1A,
        0xAB,
        0xFB,
        0xD5,
        0xB5,
        0x01,
        0x91,
        0x71,
        0x45,
        0xD2,
        0x50,
        0x35,
        0x02,
        0x7D,
        0xE9,
        0x77,
        0xF6,
        0x5E,
        0x43,
        0x2F,
        0x0C,
        0x89,
        0xB7,
        0xAD,
        0x58,
        0xA2,
        0x5F,
        0xFF,
        0x91,
        0x03,
        0xEB,
        0x73,
        0xE2,
        0x64,
        0x21,
        0x18,
        0x2E,
        0x2F,
        0x50,
        0x8C,
        0x5C,
        0x0A,
        0x0D,
        0x65,
        0xBB,
        0xDC,
        0xBB,
        0x0C,
        0xD0,
        0x7D,
        0x62,
        0xDC,
        0x62,
        0x8A,
        0x93,
        0xF7,
        0xEE,
        0x2F,
        0x0F,
        0x2B,
        0x9E,
        0x8D,
        //2nd part: cihpher
        0x9C,
        0xF5,
        0x23,
        0x19,
        0x4F,
        0xA9,
        0x55,
        0x86,
        0x73,
        0x9F,
        0xE9,
        0x61,
        0x39,
        0x2C,
        0xE9,
        0x96,
        0xB6,
        0x05,
        0x1F,
        0xA7,
        0x12,
        0x69,
        0x44,
        0x85,
        0x0E,
        0x9C,
        0x51,
        0xCE,
        0x8A,
        0xBD,
        0xE5,
        0x9D,
        0x0B,
        0x26,
        0xAD,
        0x5C,
        0x5E,
        0x47,
        0x4E,
        0xDF,
        0xE4,
        0x09,
        0xE6,
        //3rd part: mac
        0xE4,
        0x8F,
        0xC0,
        0xBB,
        0xFA,
        0xAF,
        0x26,
        0x89,
        0x7C,
        0xE6,
        0x0A,
        0x54,
        0x1B,
        0xAF,
        0xC5,
        0x36,
        0x64,
        0x0C,
        0xED,
        0x52};

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0x38,
        0x2A,
        0x1A,
        0xAB,
        0xFB,
        0xD5,
        0xB5,
        0x01,
        0x91,
        0x71,
        0x45,
        0xD2,
        0x50,
        0x35,
        0x02,
        0x7D,
        0xE9,
        0x77,
        0xF6,
        0x5E,
        0x43,
        0x2F,
        0x0C,
        0x89,
        0xB7,
        0xAD,
        0x58,
        0xA2,
        0x5F,
        0xFF,
        0x91,
        0x03,
        //2nd part: cihpher
        0x9C,
        0xF5,
        0x23,
        0x19,
        0x4F,
        0xA9,
        0x55,
        0x86,
        0x73,
        0x9F,
        0xE9,
        0x61,
        0x39,
        0x2C,
        0xE9,
        0x96,
        0xB6,
        0x05,
        0x1F,
        0xA7,
        0x12,
        0x69,
        0x44,
        0x85,
        0x0E,
        0x9C,
        0x51,
        0xCE,
        0x8A,
        0xBD,
        0xE5,
        0x9D,
        0x0B,
        0x26,
        0xAD,
        0x5C,
        0x5E,
        0x47,
        0x4E,
        0xDF,
        0xE4,
        0x09,
        0xE6,
        //3rd part: mac
        0xE4,
        0x8F,
        0xC0,
        0xBB,
        0xFA,
        0xAF,
        0x26,
        0x89,
        0x7C,
        0xE6,
        0x0A,
        0x54,
        0x1B,
        0xAF,
        0xC5,
        0x36,
        0x64,
        0x0C,
        0xED,
        0x52};
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x37,
        0x77,
        0x76,
        0x4C,
        0x17,
        0xCC,
        0xD7,
        0xC2,
        0x27,
        0xEF,
        0x93,
        0xDE,
        0xB6,
        0x28,
        0xD8,
        0x23,
        0x6D,
        0xE2,
        0x08,
        0xBD,
        0x70,
        0xB3,
        0xCC,
        0xCA,
        0xD5,
        0xC6,
        0x6B,
        0xBB,
        0x04,
        0x0B,
        0x15,
        0x05,
        0x79,
        0xD9,
        0x13,
        0x1A,
        0x90,
        0xFB,
        0x23,
        0x3C,
        0x1B,
        0xDF,
        0xA0,
        //3rd part: mac
        0xCF,
        0x61,
        0xB1,
        0x6D,
        0x20,
        0x9F,
        0xBF,
        0x8C,
        0x7A,
        0x94,
        0xC0,
        0x82,
        0xD3,
        0x6C,
        0xD8,
        0x32,
        0xB3,
        0x76,
        0xC4,
        0x89};
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x9C,
        0xF5,
        0x23,
        0x19,
        0x4F,
        0xA9,
        0x55,
        0x86,
        0x73,
        0x9F,
        0xE9,
        0x61,
        0x39,
        0x2C,
        0xE9,
        0x96,
        0xB6,
        0x05,
        0x1F,
        0xA7,
        0x12,
        0x69,
        0x44,
        0x85,
        0x0E,
        0x9C,
        0x51,
        0xCE,
        0x8A,
        0xBD,
        0xE5,
        0x9D,
        0x0B,
        0x26,
        0xAD,
        0x5C,
        0x5E,
        0x47,
        0x4E,
        0xDF,
        0xE4,
        0x09,
        0xE6,
        //3rd part: mac
        0x6E,
        0x1D,
        0x99,
        0x37,
        0xBF,
        0xF2,
        0xF4,
        0x52,
        0x2D,
        0xBB,
        0xAB,
        0x93,
        0x06,
        0xC1,
        0xBB,
        0xCD,
        0xEF,
        0x20,
        0xD3,
        0x65};
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x37,
        0x77,
        0x76,
        0x4C,
        0x17,
        0xCC,
        0xD7,
        0xC2,
        0x27,
        0xEF,
        0x93,
        0xDE,
        0xB6,
        0x28,
        0xD8,
        0x23,
        0x6D,
        0xE2,
        0x08,
        0xBD,
        0x70,
        0xB3,
        0xCC,
        0xCA,
        0xD5,
        0xC6,
        0x6B,
        0xBB,
        0x04,
        0x0B,
        0x15,
        0x05,
        0x79,
        0xD9,
        0x13,
        0x1A,
        0x90,
        0xFB,
        0x23,
        0x3C,
        0x1B,
        0xDF,
        0xA0,
        //3rd part: mac
        0x91,
        0x1F,
        0x35,
        0x5F,
        0xD0,
        0xF1,
        0x20,
        0xB6,
        0xF7,
        0xC0,
        0xAE,
        0xD0,
        0x7C,
        0x13,
        0x84,
        0x88,
        0x7C,
        0xEB,
        0xDC,
        0x74};

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp256k1;
    char         *curve_name = "secp256k1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif
    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
unsigned int ecies_std_test_secp160r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x00,
        0x2E,
        0x83,
        0x56,
        0x83,
        0x27,
        0xFF,
        0xC9,
        0x08,
        0x81,
        0xCA,
        0xCF,
        0x48,
        0xE3,
        0xA9,
        0xF1,
        0xE4,
        0x96,
        0xCF,
        0x9E,
        0x42,
    };
    unsigned char receiver_pub_key[] = {
        0xDA,
        0xB3,
        0x28,
        0x81,
        0x4D,
        0x24,
        0x0E,
        0xEB,
        0xAA,
        0xDB,
        0x74,
        0x56,
        0x89,
        0xB0,
        0xD5,
        0xAE,
        0x3B,
        0x07,
        0xDA,
        0x6A,
        0xAB,
        0xC6,
        0x9A,
        0x37,
        0x07,
        0x96,
        0xEC,
        0x42,
        0x27,
        0x6C,
        0x50,
        0x87,
        0x6B,
        0xD8,
        0xF8,
        0xFA,
        0x44,
        0x97,
        0xC6,
        0xB5,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x00,
        0xAF,
        0x9D,
        0x42,
        0xA5,
        0x8C,
        0x8C,
        0x29,
        0x7A,
        0xBC,
        0x0E,
        0xB3,
        0xE6,
        0xB3,
        0xE5,
        0xF5,
        0xF5,
        0x72,
        0xAF,
        0x97,
        0xCF};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 128;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x4E,
        0xE8,
        0x77,
        0x9C,
        0x0E,
        0x05,
        0x77,
        0x6F,
        0xAE,
        0xBA,
        0x93,
        0x23,
        0x55,
        0x36,
        0x85,
        0x54,
        0x8A,
        0x5C,
        0x2B,
        0x5E,
        0xB5,
        0xE9,
        0x01,
        0x4E,
        0x0B,
        0x15,
        0x0D,
        0xFD,
        0xC3,
        0x74,
        0x66,
        0x23,
        0x82,
        0x82,
        0xF0,
        0x1C,
        0x0B,
        0xE5,
        0xC9,
        0xCE,
        //2nd part: cihpher
        0x22,
        0xFF,
        0x1B,
        0x77,
        0x2B,
        0xC0,
        0x16,
        0x4F,
        0x75,
        0x1B,
        0x62,
        0x27,
        0xAF,
        0xDE,
        0x6A,
        0xE4,
        0xBC,
        0x63,
        0x38,
        0x4B,
        0x1D,
        0xD4,
        0xEA,
        0x99,
        0x2B,
        0x44,
        0x75,
        0xAB,
        0xFE,
        0xBB,
        0x00,
        0xBD,
        0x40,
        0x6D,
        0xBC,
        0x2E,
        0x3E,
        0x81,
        0x2A,
        0x37,
        0xC4,
        0x41,
        0xC7,
        //3rd part: mac
        0x23,
        0x33,
        0x62,
        0x33,
        0xD2,
        0x75,
        0x56,
        0x1A,
        0x1D,
        0x8A,
        0x32,
        0x21,
        0xCF,
        0xA7,
        0xCD,
        0xE7,
        0x98,
        0x21,
        0xA3,
        0xED,
        0x74,
        0xB6,
        0x56,
        0x0A,
        0x20,
        0x79,
        0x2B,
        0xB0,
        0xCE,
        0xC9,
        0xDB,
        0x3F,
        0x4A,
        0xCF,
        0xB4,
        0x82,
        0x30,
        0xC0,
        0x1D,
        0xE4,
        0x4A,
        0xE9,
        0x91,
        0xB3,
        0xB6,
        0x05,
        0x0C,
        0x8F,
        0x12,
        0xD8,
        0x04,
        0x1A,
        0x48,
        0xE5,
        0x86,
        0xD7,
        0xE4,
        0x1B,
        0x68,
        0xD6,
        0xC5,
        0x56,
        0x58,
        0x2C,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0x4E,
        0xE8,
        0x77,
        0x9C,
        0x0E,
        0x05,
        0x77,
        0x6F,
        0xAE,
        0xBA,
        0x93,
        0x23,
        0x55,
        0x36,
        0x85,
        0x54,
        0x8A,
        0x5C,
        0x2B,
        0x5E,
        //2nd part: cihpher
        0x22,
        0xFF,
        0x1B,
        0x77,
        0x2B,
        0xC0,
        0x16,
        0x4F,
        0x75,
        0x1B,
        0x62,
        0x27,
        0xAF,
        0xDE,
        0x6A,
        0xE4,
        0xBC,
        0x63,
        0x38,
        0x4B,
        0x1D,
        0xD4,
        0xEA,
        0x99,
        0x2B,
        0x44,
        0x75,
        0xAB,
        0xFE,
        0xBB,
        0x00,
        0xBD,
        0x40,
        0x6D,
        0xBC,
        0x2E,
        0x3E,
        0x81,
        0x2A,
        0x37,
        0xC4,
        0x41,
        0xC7,
        //3rd part: mac
        0x23,
        0x33,
        0x62,
        0x33,
        0xD2,
        0x75,
        0x56,
        0x1A,
        0x1D,
        0x8A,
        0x32,
        0x21,
        0xCF,
        0xA7,
        0xCD,
        0xE7,
        0x98,
        0x21,
        0xA3,
        0xED,
        0x74,
        0xB6,
        0x56,
        0x0A,
        0x20,
        0x79,
        0x2B,
        0xB0,
        0xCE,
        0xC9,
        0xDB,
        0x3F,
        0x4A,
        0xCF,
        0xB4,
        0x82,
        0x30,
        0xC0,
        0x1D,
        0xE4,
        0x4A,
        0xE9,
        0x91,
        0xB3,
        0xB6,
        0x05,
        0x0C,
        0x8F,
        0x12,
        0xD8,
        0x04,
        0x1A,
        0x48,
        0xE5,
        0x86,
        0xD7,
        0xE4,
        0x1B,
        0x68,
        0xD6,
        0xC5,
        0x56,
        0x58,
        0x2C,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xAA,
        0x13,
        0x89,
        0xCB,
        0xC9,
        0x7B,
        0x73,
        0xE8,
        0x43,
        0x66,
        0xD9,
        0x23,
        0x34,
        0x45,
        0x7F,
        0x4A,
        0xF6,
        0x4F,
        0xF8,
        0x00,
        0xCC,
        0x1C,
        0xD6,
        0xDA,
        0x48,
        0x69,
        0x11,
        0xE0,
        0x56,
        0x43,
        0xEE,
        0x1A,
        0xF0,
        0x66,
        0xD9,
        0x4E,
        0xFE,
        0xB1,
        0xEA,
        0xB9,
        0xC6,
        0xB3,
        0xBD,
        //3rd part: mac
        0x7A,
        0x52,
        0xD3,
        0xE6,
        0x6D,
        0x5A,
        0x1F,
        0x6D,
        0xD9,
        0xD5,
        0x2F,
        0x39,
        0x29,
        0x2F,
        0x70,
        0x10,
        0x33,
        0x43,
        0x9D,
        0x77,
        0x0F,
        0x5A,
        0x12,
        0x98,
        0x55,
        0xA0,
        0x9C,
        0xCE,
        0x4D,
        0x5F,
        0x86,
        0x8F,
        0x66,
        0x83,
        0x00,
        0xCC,
        0x14,
        0xA6,
        0xFB,
        0x96,
        0x11,
        0x66,
        0x3E,
        0x76,
        0xF2,
        0x57,
        0xA3,
        0x1C,
        0x85,
        0xC9,
        0xB1,
        0xEA,
        0x7A,
        0xCF,
        0x7F,
        0x06,
        0x74,
        0xCD,
        0x79,
        0xA7,
        0xCA,
        0x5F,
        0xD3,
        0x1E,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x22,
        0xFF,
        0x1B,
        0x77,
        0x2B,
        0xC0,
        0x16,
        0x4F,
        0x75,
        0x1B,
        0x62,
        0x27,
        0xAF,
        0xDE,
        0x6A,
        0xE4,
        0xBC,
        0x63,
        0x38,
        0x4B,
        0x1D,
        0xD4,
        0xEA,
        0x99,
        0x2B,
        0x44,
        0x75,
        0xAB,
        0xFE,
        0xBB,
        0x00,
        0xBD,
        0x40,
        0x6D,
        0xBC,
        0x2E,
        0x3E,
        0x81,
        0x2A,
        0x37,
        0xC4,
        0x41,
        0xC7,
        //3rd part: mac
        0xF3,
        0x28,
        0x3E,
        0x76,
        0x99,
        0xAD,
        0x13,
        0x4C,
        0x57,
        0x23,
        0x9D,
        0xFF,
        0x89,
        0xD5,
        0xA5,
        0x79,
        0xEE,
        0x0F,
        0x5D,
        0xC5,
        0x24,
        0xC9,
        0x9A,
        0xFD,
        0xBB,
        0xB1,
        0xAE,
        0x3D,
        0x81,
        0x93,
        0xD0,
        0x48,
        0xA0,
        0x6A,
        0xF9,
        0x8F,
        0x1B,
        0x55,
        0x09,
        0xA4,
        0xAE,
        0xAA,
        0x0F,
        0x2F,
        0x00,
        0xE4,
        0xFD,
        0x1C,
        0xFD,
        0xFF,
        0xBB,
        0x11,
        0x07,
        0xA4,
        0x9E,
        0x4F,
        0xCE,
        0x0A,
        0x66,
        0x42,
        0xC4,
        0xEE,
        0xE6,
        0xF8,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xAA,
        0x13,
        0x89,
        0xCB,
        0xC9,
        0x7B,
        0x73,
        0xE8,
        0x43,
        0x66,
        0xD9,
        0x23,
        0x34,
        0x45,
        0x7F,
        0x4A,
        0xF6,
        0x4F,
        0xF8,
        0x00,
        0xCC,
        0x1C,
        0xD6,
        0xDA,
        0x48,
        0x69,
        0x11,
        0xE0,
        0x56,
        0x43,
        0xEE,
        0x1A,
        0xF0,
        0x66,
        0xD9,
        0x4E,
        0xFE,
        0xB1,
        0xEA,
        0xB9,
        0xC6,
        0xB3,
        0xBD,
        //3rd part: mac
        0x17,
        0x9B,
        0xFE,
        0x9F,
        0x33,
        0x5A,
        0xA2,
        0x1A,
        0xB5,
        0x6A,
        0xB5,
        0x5B,
        0xCA,
        0x31,
        0x53,
        0xE3,
        0x5F,
        0x80,
        0x0E,
        0xFA,
        0xBD,
        0xB2,
        0x9D,
        0x28,
        0xA2,
        0x09,
        0x3E,
        0x9F,
        0x83,
        0xEF,
        0xF4,
        0xF0,
        0x52,
        0x64,
        0x0E,
        0xD5,
        0xB3,
        0x21,
        0x56,
        0xC5,
        0xBC,
        0xF5,
        0x3F,
        0xF0,
        0xC7,
        0xCB,
        0xDE,
        0x11,
        0xD3,
        0x49,
        0xC4,
        0x47,
        0x4F,
        0x03,
        0xA3,
        0x24,
        0x69,
        0xD2,
        0x53,
        0xB9,
        0x0E,
        0x28,
        0x8F,
        0xB2,
    };


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp160r1;
    char         *curve_name = "secp160r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
unsigned int ecies_std_test_secp160r2(void)
{
    unsigned char receiver_pri_key[] = {
        0x00,
        0x7B,
        0x5B,
        0x20,
        0xF7,
        0xF3,
        0xCC,
        0x9B,
        0xA4,
        0x3C,
        0x61,
        0x39,
        0x05,
        0xF8,
        0x2F,
        0x80,
        0xF3,
        0xCF,
        0x5B,
        0x42,
        0xF3,
    };
    unsigned char receiver_pub_key[] = {
        0x43,
        0xFE,
        0x2A,
        0xC8,
        0x81,
        0x1A,
        0x38,
        0x62,
        0xB9,
        0xEF,
        0xE0,
        0xCF,
        0x0C,
        0xE4,
        0xBF,
        0x45,
        0xB9,
        0xF1,
        0xA4,
        0x66,
        0x7A,
        0x9F,
        0x72,
        0xFE,
        0x99,
        0x2C,
        0x48,
        0x9D,
        0x01,
        0xC9,
        0x0D,
        0xCC,
        0xCC,
        0xDA,
        0x03,
        0x42,
        0xE1,
        0x22,
        0x90,
        0x9B,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x00,
        0x07,
        0x5C,
        0x49,
        0xF9,
        0xC2,
        0xA6,
        0x9F,
        0x92,
        0x72,
        0x17,
        0x41,
        0x33,
        0x30,
        0xB8,
        0xF6,
        0x60,
        0xBA,
        0xDB,
        0x80,
        0xF4};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_1;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_1);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 16;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x00,
        0x39,
        0x7C,
        0xA8,
        0x2F,
        0xA4,
        0x4A,
        0x9E,
        0x97,
        0xC6,
        0x39,
        0x1B,
        0xC4,
        0x39,
        0xDE,
        0x88,
        0xB0,
        0x7A,
        0xB1,
        0xB3,
        0x63,
        0x63,
        0xBA,
        0x73,
        0x6C,
        0xA1,
        0x91,
        0x8F,
        0x92,
        0xF4,
        0x6D,
        0x90,
        0x8F,
        0x4F,
        0x4F,
        0x8E,
        0xA6,
        0x46,
        0xB1,
        0x0F,
        //2nd part: cihpher
        0x19,
        0xCF,
        0xCD,
        0x7A,
        0x87,
        0x32,
        //3rd part: mac
        0x75,
        0xCD,
        0xB6,
        0x31,
        0x38,
        0x21,
        0x60,
        0xF2,
        0x1E,
        0xE1,
        0xE9,
        0x59,
        0x1C,
        0x6D,
        0xC1,
        0x92,
        0x6F,
        0x27,
        0xBD,
        0xEF};

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0x00,
        0x39,
        0x7C,
        0xA8,
        0x2F,
        0xA4,
        0x4A,
        0x9E,
        0x97,
        0xC6,
        0x39,
        0x1B,
        0xC4,
        0x39,
        0xDE,
        0x88,
        0xB0,
        0x7A,
        0xB1,
        0xB3,
        //2nd part: cihpher
        0x19,
        0xCF,
        0xCD,
        0x7A,
        0x87,
        0x32,
        //3rd part: mac
        0x75,
        0xCD,
        0xB6,
        0x31,
        0x38,
        0x21,
        0x60,
        0xF2,
        0x1E,
        0xE1,
        0xE9,
        0x59,
        0x1C,
        0x6D,
        0xC1,
        0x92,
        0x6F,
        0x27,
        0xBD,
        0xEF,
    };
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xA5,
        0x87,
        0x42,
        0xDD,
        0xD2,
        0xFC,
        //3rd part: mac
        0xF7,
        0x3A,
        0x37,
        0xB3,
        0xA6,
        0x11,
        0x09,
        0xF0,
        0x26,
        0x6C,
        0x78,
        0xD5,
        0x1F,
        0x47,
        0x12,
        0xA7,
        0x18,
        0x91,
        0xCE,
        0x5F};
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x19,
        0xCF,
        0xCD,
        0x7A,
        0x87,
        0x32,
        //3rd part: mac
        0x47,
        0x8D,
        0x93,
        0x34,
        0x52,
        0xF9,
        0xB6,
        0x1B,
        0x8C,
        0x18,
        0x51,
        0x7D,
        0xE5,
        0x06,
        0x54,
        0x35,
        0xB1,
        0x3C,
        0x93,
        0x9A};
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xA5,
        0x87,
        0x42,
        0xDD,
        0xD2,
        0xFC,
        //3rd part: mac
        0x60,
        0x8F,
        0x85,
        0x0D,
        0x62,
        0x9A,
        0xAC,
        0xFE,
        0x2B,
        0x83,
        0x8D,
        0x51,
        0x35,
        0x0A,
        0x78,
        0x22,
        0xE1,
        0xDD,
        0xE8,
        0xD3};


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp160r2;
    char         *curve_name = "secp160r2";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
unsigned int ecies_std_test_secp192r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x28,
        0x95,
        0xFC,
        0x2E,
        0x5B,
        0x0F,
        0x44,
        0x92,
        0xBD,
        0x14,
        0xE3,
        0xF3,
        0xF1,
        0xBE,
        0x46,
        0xFF,
        0x46,
        0x6E,
        0x51,
        0xB9,
        0xB4,
        0xCA,
        0x36,
        0x1F,
    };
    unsigned char receiver_pub_key[] = {
        0xE2,
        0x35,
        0x0E,
        0x10,
        0x7C,
        0xA8,
        0x14,
        0x25,
        0xA9,
        0xAB,
        0x14,
        0xCB,
        0x6C,
        0x5C,
        0x64,
        0x8C,
        0x0F,
        0x43,
        0x36,
        0x1A,
        0x50,
        0x47,
        0xFE,
        0x05,
        0x3E,
        0x88,
        0x12,
        0x1F,
        0x72,
        0xE6,
        0x9B,
        0x8B,
        0xDA,
        0x0C,
        0xE2,
        0xE7,
        0xBC,
        0xE2,
        0x98,
        0x28,
        0xB2,
        0x36,
        0x2D,
        0xFC,
        0xE0,
        0x46,
        0xD3,
        0xFA,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x9A,
        0xC9,
        0x04,
        0xDE,
        0x0C,
        0xE2,
        0x3A,
        0x68,
        0x8A,
        0x7E,
        0x2C,
        0x80,
        0xA2,
        0x11,
        0xAC,
        0x23,
        0x9C,
        0x3D,
        0x6B,
        0x25,
        0x94,
        0x4B,
        0xD5,
        0xCD};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 32;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0xFC,
        0xED,
        0x6E,
        0x2C,
        0x82,
        0xA0,
        0x0A,
        0xB7,
        0x88,
        0xEE,
        0x88,
        0x6C,
        0x95,
        0x5C,
        0x9F,
        0xD1,
        0x66,
        0x24,
        0x23,
        0xC0,
        0xFA,
        0xA8,
        0xB8,
        0xC8,
        0x4D,
        0xAA,
        0xEC,
        0x43,
        0x1A,
        0x83,
        0xB0,
        0x08,
        0xF3,
        0xAE,
        0xC2,
        0xC3,
        0x16,
        0x44,
        0xF6,
        0x41,
        0x62,
        0xE2,
        0x6F,
        0xE3,
        0xAF,
        0x25,
        0xFE,
        0x24,
        //2nd part: cihpher
        0x3A,
        0x91,
        0x5F,
        0xAB,
        0x20,
        0x0E,
        0xC4,
        0x4C,
        0xCC,
        0x79,
        0x9E,
        0xF0,
        0x08,
        0xF9,
        0x41,
        0xEA,
        0x0A,
        0x15,
        0xD4,
        0xB3,
        0x47,
        0xF2,
        0x1C,
        0x32,
        0x5D,
        0xA6,
        0x35,
        0x42,
        0x4F,
        0x6C,
        0x1D,
        0xF0,
        0xCA,
        0x97,
        0x9C,
        0x01,
        0x4F,
        0xCA,
        0xBA,
        0xE3,
        0x3B,
        0x23,
        0xD9,
        //3rd part: mac
        0x03,
        0x5B,
        0x33,
        0x56,
        0xFC,
        0xD0,
        0xDE,
        0x98,
        0x04,
        0xD7,
        0xA3,
        0xB9,
        0x44,
        0xD3,
        0xA5,
        0x1A,
        0x85,
        0xCB,
        0x42,
        0x24,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0xFC,
        0xED,
        0x6E,
        0x2C,
        0x82,
        0xA0,
        0x0A,
        0xB7,
        0x88,
        0xEE,
        0x88,
        0x6C,
        0x95,
        0x5C,
        0x9F,
        0xD1,
        0x66,
        0x24,
        0x23,
        0xC0,
        0xFA,
        0xA8,
        0xB8,
        0xC8,
        //2nd part: cihpher
        0x3A,
        0x91,
        0x5F,
        0xAB,
        0x20,
        0x0E,
        0xC4,
        0x4C,
        0xCC,
        0x79,
        0x9E,
        0xF0,
        0x08,
        0xF9,
        0x41,
        0xEA,
        0x0A,
        0x15,
        0xD4,
        0xB3,
        0x47,
        0xF2,
        0x1C,
        0x32,
        0x5D,
        0xA6,
        0x35,
        0x42,
        0x4F,
        0x6C,
        0x1D,
        0xF0,
        0xCA,
        0x97,
        0x9C,
        0x01,
        0x4F,
        0xCA,
        0xBA,
        0xE3,
        0x3B,
        0x23,
        0xD9,
        //3rd part: mac
        0x03,
        0x5B,
        0x33,
        0x56,
        0xFC,
        0xD0,
        0xDE,
        0x98,
        0x04,
        0xD7,
        0xA3,
        0xB9,
        0x44,
        0xD3,
        0xA5,
        0x1A,
        0x85,
        0xCB,
        0x42,
        0x24,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x82,
        0xB4,
        0x9F,
        0x12,
        0xEE,
        0x76,
        0xA9,
        0xCF,
        0xD3,
        0x01,
        0x1F,
        0xF8,
        0x9E,
        0x5E,
        0xD5,
        0x0B,
        0xC3,
        0xC2,
        0x72,
        0xA3,
        0x86,
        0x53,
        0x18,
        0xA7,
        0x28,
        0xC6,
        0x21,
        0x33,
        0x38,
        0x82,
        0xB4,
        0x8C,
        0xAF,
        0x1E,
        0x04,
        0xE2,
        0x22,
        0x88,
        0x22,
        0x4F,
        0xC7,
        0x62,
        0x99,
        //3rd part: mac
        0xD7,
        0xFF,
        0x67,
        0x28,
        0x63,
        0x0E,
        0x74,
        0x3C,
        0x60,
        0xD2,
        0xD0,
        0x2D,
        0xC9,
        0xAD,
        0x53,
        0xE0,
        0xF8,
        0xB7,
        0x20,
        0x67};
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x3A,
        0x91,
        0x5F,
        0xAB,
        0x20,
        0x0E,
        0xC4,
        0x4C,
        0xCC,
        0x79,
        0x9E,
        0xF0,
        0x08,
        0xF9,
        0x41,
        0xEA,
        0x0A,
        0x15,
        0xD4,
        0xB3,
        0x47,
        0xF2,
        0x1C,
        0x32,
        0x5D,
        0xA6,
        0x35,
        0x42,
        0x4F,
        0x6C,
        0x1D,
        0xF0,
        0xCA,
        0x97,
        0x9C,
        0x01,
        0x4F,
        0xCA,
        0xBA,
        0xE3,
        0x3B,
        0x23,
        0xD9,
        //3rd part: mac
        0xD5,
        0x35,
        0x68,
        0x8D,
        0x41,
        0xE1,
        0x34,
        0x18,
        0xE1,
        0x8B,
        0xF5,
        0x88,
        0x18,
        0x3C,
        0x30,
        0x07,
        0x3E,
        0xAD,
        0x8C,
        0x28};
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x82,
        0xB4,
        0x9F,
        0x12,
        0xEE,
        0x76,
        0xA9,
        0xCF,
        0xD3,
        0x01,
        0x1F,
        0xF8,
        0x9E,
        0x5E,
        0xD5,
        0x0B,
        0xC3,
        0xC2,
        0x72,
        0xA3,
        0x86,
        0x53,
        0x18,
        0xA7,
        0x28,
        0xC6,
        0x21,
        0x33,
        0x38,
        0x82,
        0xB4,
        0x8C,
        0xAF,
        0x1E,
        0x04,
        0xE2,
        0x22,
        0x88,
        0x22,
        0x4F,
        0xC7,
        0x62,
        0x99,
        //3rd part: mac
        0xEF,
        0x36,
        0x43,
        0xDD,
        0x9C,
        0x62,
        0x7C,
        0x46,
        0x2C,
        0x6C,
        0x71,
        0xA5,
        0xE0,
        0x58,
        0x65,
        0xEA,
        0xD8,
        0x45,
        0x66,
        0xA6};


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp192r1;
    char         *curve_name = "secp192r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
unsigned int ecies_std_test_secp224r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x89,
        0x8E,
        0x68,
        0x88,
        0x8B,
        0x43,
        0xAF,
        0x17,
        0xE9,
        0x0F,
        0x50,
        0x43,
        0xDC,
        0x05,
        0x05,
        0xB5,
        0xFE,
        0x9F,
        0xB6,
        0x15,
        0x23,
        0xC7,
        0x05,
        0xBA,
        0x07,
        0x44,
        0x14,
        0x60,
    };
    unsigned char receiver_pub_key[] = {
        0x2B,
        0x2E,
        0xF0,
        0x69,
        0x4D,
        0xC2,
        0xAF,
        0xB7,
        0x44,
        0x88,
        0x1C,
        0x38,
        0x30,
        0x40,
        0xE8,
        0x67,
        0xD7,
        0x62,
        0xCC,
        0xC8,
        0x3C,
        0xB4,
        0x82,
        0xC6,
        0xA7,
        0x9F,
        0xCF,
        0xCA,
        0x11,
        0xAC,
        0xD5,
        0xF9,
        0x4E,
        0x69,
        0x2C,
        0xCF,
        0x66,
        0xA1,
        0x8E,
        0xAA,
        0x46,
        0xF5,
        0x29,
        0x5C,
        0xAF,
        0xBE,
        0x05,
        0x8F,
        0xDB,
        0xB0,
        0xD7,
        0x01,
        0xC0,
        0x2E,
        0x4A,
        0x17,
    };
    unsigned char sender_tmp_pri_key[] = {
        0xFE,
        0x7D,
        0xCA,
        0xDC,
        0x1D,
        0x18,
        0xE5,
        0xBB,
        0xC7,
        0x82,
        0xED,
        0x0A,
        0x97,
        0x5B,
        0xE4,
        0xB1,
        0x5D,
        0xD1,
        0x66,
        0x3F,
        0x01,
        0x7C,
        0x8B,
        0x08,
        0x29,
        0xFD,
        0x45,
        0x03,
    };

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_1;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_1);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 32;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    //kP.x, also kdf input:
    //478D652E6CBEA6487C9A6B0BAE216875F52CE70E1C8F5FA321278ACA
    //without s1 and s2, then enc_key||mac_key, also kdf output:
    //F481A29A1277 DB84DA6BBE8F344C8DA17B1E0D76C4F41005F1A72A669043CACDD9585B509017

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0xBD,
        0x78,
        0x5F,
        0xC6,
        0x2B,
        0x4F,
        0xD3,
        0x07,
        0x8B,
        0xDE,
        0xD1,
        0xDB,
        0xC0,
        0x38,
        0x4B,
        0x52,
        0x6C,
        0xA3,
        0x97,
        0x1B,
        0xA9,
        0xE9,
        0xE3,
        0xBC,
        0xED,
        0xE1,
        0x27,
        0xFD,
        0xED,
        0x1C,
        0x63,
        0xCB,
        0x67,
        0x36,
        0x03,
        0xC6,
        0x17,
        0x69,
        0xBF,
        0xD5,
        0xB6,
        0xAB,
        0x29,
        0xC7,
        0xFC,
        0x15,
        0x04,
        0x4A,
        0x36,
        0xCA,
        0xBE,
        0x72,
        0x14,
        0x7A,
        0xD1,
        0x7B,
        //2nd part: cihpher
        0x95,
        0xE3,
        0xC1,
        0xFB,
        0x70,
        0x14,
        //3rd part: mac
        0x7B,
        0x36,
        0xF5,
        0x96,
        0x20,
        0xEA,
        0x9B,
        0x36,
        0x1D,
        0xEE,
        0x72,
        0x19,
        0x8F,
        0x8A,
        0x97,
        0x04,
        0x1C,
        0xA6,
        0x02,
        0x99,
    };

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0xBD,
        0x78,
        0x5F,
        0xC6,
        0x2B,
        0x4F,
        0xD3,
        0x07,
        0x8B,
        0xDE,
        0xD1,
        0xDB,
        0xC0,
        0x38,
        0x4B,
        0x52,
        0x6C,
        0xA3,
        0x97,
        0x1B,
        0xA9,
        0xE9,
        0xE3,
        0xBC,
        0xED,
        0xE1,
        0x27,
        0xFD,
        //2nd part: cihpher
        0x95,
        0xE3,
        0xC1,
        0xFB,
        0x70,
        0x14,
        //3rd part: mac
        0x7B,
        0x36,
        0xF5,
        0x96,
        0x20,
        0xEA,
        0x9B,
        0x36,
        0x1D,
        0xEE,
        0x72,
        0x19,
        0x8F,
        0x8A,
        0x97,
        0x04,
        0x1C,
        0xA6,
        0x02,
        0x99,
    };
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xB6,
        0xA1,
        0xF3,
        0x27,
        0xA1,
        0x38,
        //3rd part: mac
        0x50,
        0xAF,
        0x5F,
        0xD3,
        0x42,
        0xC4,
        0x34,
        0x0F,
        0x46,
        0xDD,
        0x76,
        0x64,
        0x54,
        0xB6,
        0x93,
        0xA0,
        0x7D,
        0x3C,
        0x77,
        0x45,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x95,
        0xE3,
        0xC1,
        0xFB,
        0x70,
        0x14,
        //3rd part: mac
        0xBC,
        0x0B,
        0x30,
        0xD8,
        0xD0,
        0x2E,
        0x56,
        0xBD,
        0xBD,
        0xC0,
        0x89,
        0x9B,
        0x76,
        0x85,
        0x7C,
        0x69,
        0x4E,
        0x57,
        0x35,
        0x5F,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xB6,
        0xA1,
        0xF3,
        0x27,
        0xA1,
        0x38,
        //3rd part: mac
        0xD5,
        0xC2,
        0x5A,
        0x6C,
        0xAF,
        0x9A,
        0x3B,
        0x46,
        0x39,
        0x88,
        0xDB,
        0x22,
        0xE8,
        0x85,
        0x43,
        0x83,
        0x72,
        0x28,
        0xCA,
        0x3F,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp224r1;
    char         *curve_name = "secp224r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
unsigned int ecies_std_test_secp256r1(void)
{
    unsigned char receiver_pri_key[] = {
        0xF4,
        0x3B,
        0xAF,
        0xC3,
        0xC7,
        0xB2,
        0xFB,
        0x10,
        0xAF,
        0xEE,
        0xD6,
        0x56,
        0x68,
        0xD3,
        0x63,
        0x4E,
        0x32,
        0x39,
        0xC1,
        0x08,
        0xBB,
        0x6A,
        0xCF,
        0x34,
        0x33,
        0x31,
        0x49,
        0x02,
        0x55,
        0x84,
        0xB3,
        0x0E,
    };
    unsigned char receiver_pub_key[] = {
        0xBD,
        0x2F,
        0xEF,
        0x24,
        0xAC,
        0x63,
        0x6F,
        0x55,
        0xDB,
        0xF1,
        0xF5,
        0x20,
        0x38,
        0x85,
        0x09,
        0x7E,
        0x18,
        0x62,
        0x9E,
        0xDF,
        0xFB,
        0x36,
        0xF4,
        0x03,
        0x89,
        0x61,
        0x27,
        0x44,
        0xA1,
        0x0F,
        0x02,
        0xD0,
        0x6B,
        0x51,
        0x9E,
        0x0F,
        0x82,
        0xBB,
        0x90,
        0xD1,
        0x63,
        0x3D,
        0x07,
        0xE8,
        0x70,
        0x8F,
        0x65,
        0x95,
        0xCE,
        0xBF,
        0xF3,
        0x86,
        0x6C,
        0xFE,
        0x33,
        0xF3,
        0xCB,
        0xE8,
        0xA3,
        0x68,
        0x1E,
        0xB8,
        0x20,
        0xEA,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x9B,
        0x0A,
        0x90,
        0x75,
        0x82,
        0x9E,
        0x6E,
        0xCC,
        0xD5,
        0x12,
        0x8D,
        0xD4,
        0x96,
        0xAE,
        0xC4,
        0x36,
        0xC3,
        0xE1,
        0x8E,
        0x97,
        0xAA,
        0xB9,
        0xD4,
        0xE1,
        0x31,
        0xBA,
        0xA3,
        0xDE,
        0x76,
        0xF4,
        0x84,
        0x3C,
    };

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_1;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_1);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg = HASH_SHA256;
    HASH_ALG mac_hash_alg = HASH_SHA256;

    unsigned int mac_key_bytes = 64;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0xA1,
        0xFF,
        0x07,
        0xDA,
        0xFA,
        0x2A,
        0x25,
        0x55,
        0x71,
        0x68,
        0x5F,
        0x3B,
        0xA7,
        0x83,
        0x10,
        0x5D,
        0xC1,
        0xB5,
        0x99,
        0x57,
        0x6D,
        0xB4,
        0x4A,
        0xB9,
        0x5A,
        0x57,
        0xF1,
        0xBA,
        0x1D,
        0x5A,
        0x3A,
        0x00,
        0xB7,
        0xBC,
        0xEE,
        0x66,
        0xAC,
        0x91,
        0xEC,
        0x1F,
        0x60,
        0x24,
        0xB6,
        0xB3,
        0x71,
        0xB7,
        0x68,
        0x35,
        0x13,
        0xB1,
        0x79,
        0x76,
        0xAD,
        0xA2,
        0xB4,
        0x7D,
        0xF8,
        0x61,
        0x64,
        0x44,
        0x1F,
        0xA2,
        0x53,
        0xD6,
        //2nd part: cihpher
        0x87,
        0xBB,
        0xE8,
        0x8D,
        0xA9,
        0x9B,
        0x11,
        0x6B,
        0xC2,
        0xEC,
        0x34,
        0xDD,
        0xE8,
        0xF7,
        0x40,
        0x02,
        0x2D,
        0x11,
        0xC4,
        0xB2,
        0xD7,
        0xFE,
        0x1D,
        0x15,
        0x31,
        0xB7,
        0x7C,
        0xF6,
        0x9C,
        0x7B,
        0xF6,
        0x13,
        0xFB,
        0xD0,
        0x66,
        0x1A,
        0x3D,
        0xC4,
        0x65,
        0xAB,
        0x8B,
        0x5A,
        0xD8,
        //3rd part: mac
        0x5C,
        0xAF,
        0xC8,
        0xF5,
        0xDB,
        0x4C,
        0xCE,
        0x4C,
        0x5E,
        0x01,
        0x25,
        0x9B,
        0x7C,
        0xC2,
        0xE8,
        0x43,
        0x20,
        0x22,
        0x59,
        0x51,
        0x46,
        0x06,
        0xA0,
        0x69,
        0x9D,
        0xEB,
        0x73,
        0xED,
        0x6E,
        0x66,
        0xA3,
        0x89,
    };

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0xA1,
        0xFF,
        0x07,
        0xDA,
        0xFA,
        0x2A,
        0x25,
        0x55,
        0x71,
        0x68,
        0x5F,
        0x3B,
        0xA7,
        0x83,
        0x10,
        0x5D,
        0xC1,
        0xB5,
        0x99,
        0x57,
        0x6D,
        0xB4,
        0x4A,
        0xB9,
        0x5A,
        0x57,
        0xF1,
        0xBA,
        0x1D,
        0x5A,
        0x3A,
        0x00,
        //2nd part: cihpher
        0x87,
        0xBB,
        0xE8,
        0x8D,
        0xA9,
        0x9B,
        0x11,
        0x6B,
        0xC2,
        0xEC,
        0x34,
        0xDD,
        0xE8,
        0xF7,
        0x40,
        0x02,
        0x2D,
        0x11,
        0xC4,
        0xB2,
        0xD7,
        0xFE,
        0x1D,
        0x15,
        0x31,
        0xB7,
        0x7C,
        0xF6,
        0x9C,
        0x7B,
        0xF6,
        0x13,
        0xFB,
        0xD0,
        0x66,
        0x1A,
        0x3D,
        0xC4,
        0x65,
        0xAB,
        0x8B,
        0x5A,
        0xD8,
        //3rd part: mac
        0x5C,
        0xAF,
        0xC8,
        0xF5,
        0xDB,
        0x4C,
        0xCE,
        0x4C,
        0x5E,
        0x01,
        0x25,
        0x9B,
        0x7C,
        0xC2,
        0xE8,
        0x43,
        0x20,
        0x22,
        0x59,
        0x51,
        0x46,
        0x06,
        0xA0,
        0x69,
        0x9D,
        0xEB,
        0x73,
        0xED,
        0x6E,
        0x66,
        0xA3,
        0x89,
    };
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x2D,
        0x19,
        0xCC,
        0x32,
        0xE7,
        0x15,
        0xAF,
        0x2F,
        0xFD,
        0xC0,
        0xCE,
        0xD6,
        0xA6,
        0x8C,
        0x56,
        0x0F,
        0xB4,
        0x36,
        0x69,
        0x16,
        0x80,
        0x53,
        0xCC,
        0xAD,
        0xCE,
        0xDA,
        0x4E,
        0x58,
        0x58,
        0x6A,
        0x8C,
        0x66,
        0xDB,
        0xE5,
        0x20,
        0xBA,
        0x47,
        0x3C,
        0xE3,
        0xA4,
        0x4B,
        0x6A,
        0x0D,
        //3rd part: mac
        0xE2,
        0x37,
        0x94,
        0x1B,
        0xCE,
        0x35,
        0x3D,
        0x8C,
        0x82,
        0xEE,
        0x51,
        0x99,
        0xB1,
        0xCC,
        0xD5,
        0x23,
        0xFE,
        0x15,
        0x61,
        0xEF,
        0xC2,
        0xCF,
        0xD9,
        0x42,
        0x7A,
        0xE8,
        0xE5,
        0xE9,
        0x1B,
        0x57,
        0xC0,
        0x1F,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x87,
        0xBB,
        0xE8,
        0x8D,
        0xA9,
        0x9B,
        0x11,
        0x6B,
        0xC2,
        0xEC,
        0x34,
        0xDD,
        0xE8,
        0xF7,
        0x40,
        0x02,
        0x2D,
        0x11,
        0xC4,
        0xB2,
        0xD7,
        0xFE,
        0x1D,
        0x15,
        0x31,
        0xB7,
        0x7C,
        0xF6,
        0x9C,
        0x7B,
        0xF6,
        0x13,
        0xFB,
        0xD0,
        0x66,
        0x1A,
        0x3D,
        0xC4,
        0x65,
        0xAB,
        0x8B,
        0x5A,
        0xD8,
        //3rd part: mac
        0xC6,
        0x65,
        0x09,
        0x94,
        0x45,
        0x96,
        0x0D,
        0xBB,
        0x51,
        0xCE,
        0xAD,
        0x24,
        0xF9,
        0xCA,
        0xE0,
        0xAC,
        0x0F,
        0x99,
        0x3B,
        0xA0,
        0x5A,
        0xCA,
        0xBC,
        0xB6,
        0x3A,
        0xCC,
        0x4C,
        0x1F,
        0x95,
        0x19,
        0x8A,
        0x64,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x2D,
        0x19,
        0xCC,
        0x32,
        0xE7,
        0x15,
        0xAF,
        0x2F,
        0xFD,
        0xC0,
        0xCE,
        0xD6,
        0xA6,
        0x8C,
        0x56,
        0x0F,
        0xB4,
        0x36,
        0x69,
        0x16,
        0x80,
        0x53,
        0xCC,
        0xAD,
        0xCE,
        0xDA,
        0x4E,
        0x58,
        0x58,
        0x6A,
        0x8C,
        0x66,
        0xDB,
        0xE5,
        0x20,
        0xBA,
        0x47,
        0x3C,
        0xE3,
        0xA4,
        0x4B,
        0x6A,
        0x0D,
        //3rd part: mac
        0x1D,
        0x7E,
        0x7C,
        0x29,
        0xCE,
        0x0B,
        0x3A,
        0x51,
        0xFE,
        0x5E,
        0x29,
        0x1A,
        0xDB,
        0x90,
        0x54,
        0xB2,
        0xB4,
        0x6A,
        0x93,
        0xFA,
        0x88,
        0x23,
        0xBC,
        0xD1,
        0x85,
        0xCD,
        0xEA,
        0x97,
        0xC5,
        0x54,
        0x96,
        0x1C,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp256r1;
    char         *curve_name = "secp256r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
unsigned int ecies_std_test_secp384r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x8B,
        0x0D,
        0xCC,
        0x7C,
        0xF8,
        0x2C,
        0x49,
        0x54,
        0xF8,
        0x0E,
        0x34,
        0xD5,
        0xD9,
        0x39,
        0x7D,
        0xFA,
        0x5D,
        0x3E,
        0xA5,
        0x4C,
        0xBE,
        0x64,
        0x75,
        0x43,
        0x32,
        0x82,
        0x9F,
        0x60,
        0xDB,
        0xD1,
        0x85,
        0x29,
        0xF9,
        0x35,
        0xD2,
        0x1C,
        0x3D,
        0x74,
        0xDD,
        0xED,
        0xF6,
        0xF8,
        0x83,
        0x27,
        0x11,
        0xC9,
        0xCC,
        0x03,
    };
    unsigned char receiver_pub_key[] = {
        0x4A,
        0xEC,
        0x1F,
        0x90,
        0x98,
        0xFF,
        0xB6,
        0x2F,
        0x1B,
        0x15,
        0x74,
        0xA5,
        0xD7,
        0x5F,
        0x70,
        0x1C,
        0xC3,
        0x46,
        0xF1,
        0xC1,
        0x81,
        0x30,
        0xB0,
        0xDE,
        0x52,
        0x4B,
        0x0D,
        0x55,
        0xA8,
        0x97,
        0xCB,
        0x37,
        0xD2,
        0x80,
        0xD2,
        0xC4,
        0xD8,
        0x5A,
        0x85,
        0xE4,
        0xC6,
        0x5C,
        0xB9,
        0x31,
        0xE3,
        0x82,
        0x78,
        0xC8,
        0x87,
        0xA0,
        0x14,
        0x03,
        0x8C,
        0xA3,
        0xF2,
        0x60,
        0x96,
        0xDA,
        0x30,
        0x45,
        0x7B,
        0x39,
        0xBC,
        0x35,
        0x29,
        0x0D,
        0xF3,
        0x0B,
        0x47,
        0xD9,
        0xB8,
        0x4C,
        0x2E,
        0xED,
        0xB1,
        0x99,
        0x34,
        0xBB,
        0x55,
        0xA8,
        0xA2,
        0x8E,
        0x4C,
        0xD6,
        0x90,
        0x68,
        0x71,
        0xDA,
        0xDC,
        0xC5,
        0x73,
        0xF6,
        0xE2,
        0xC5,
        0xC6,
        0xA0,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x03,
        0x9C,
        0xC0,
        0xF9,
        0x63,
        0x26,
        0x27,
        0xB9,
        0x70,
        0x28,
        0x09,
        0x9C,
        0x88,
        0xED,
        0xDE,
        0x15,
        0x7D,
        0xB9,
        0xAF,
        0x11,
        0x1A,
        0x04,
        0x8A,
        0xF7,
        0xBF,
        0xDA,
        0xAD,
        0x4B,
        0xC8,
        0xF0,
        0xE6,
        0xEF,
        0xA8,
        0x1C,
        0x39,
        0x8C,
        0xB4,
        0x78,
        0x85,
        0x37,
        0x2B,
        0xA2,
        0x82,
        0xAD,
        0xE3,
        0x46,
        0xE7,
        0xF4};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_1;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_1);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 64;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x12,
        0x5F,
        0xCF,
        0x93,
        0x0F,
        0x83,
        0x1E,
        0x9A,
        0x87,
        0x3A,
        0xAF,
        0x52,
        0x1D,
        0xC9,
        0x04,
        0x20,
        0x17,
        0x41,
        0x8C,
        0xFF,
        0x8B,
        0xE8,
        0x8F,
        0x2B,
        0x28,
        0x5F,
        0x5E,
        0x9D,
        0x86,
        0xD1,
        0x44,
        0xD9,
        0x98,
        0x49,
        0xC4,
        0xF0,
        0x30,
        0x58,
        0xEF,
        0xA1,
        0x23,
        0x21,
        0xAD,
        0x47,
        0x48,
        0xF7,
        0x00,
        0x0D,
        0x39,
        0xAF,
        0x96,
        0x01,
        0x82,
        0x6C,
        0x63,
        0x98,
        0x88,
        0x15,
        0xF6,
        0x39,
        0x19,
        0xE3,
        0x3F,
        0xD2,
        0xE5,
        0xC2,
        0x75,
        0x1E,
        0x91,
        0xE3,
        0xED,
        0x5C,
        0xD8,
        0x24,
        0xFF,
        0x67,
        0x38,
        0x87,
        0x76,
        0xF6,
        0x18,
        0x72,
        0x7A,
        0xC0,
        0xF1,
        0xF9,
        0x34,
        0x56,
        0xD9,
        0x9F,
        0x42,
        0x1E,
        0x33,
        0xED,
        0xA0,
        0xB2,
        //2nd part: cihpher
        0xE8,
        0x69,
        0x8B,
        0x63,
        0x3A,
        0x3E,
        //3rd part: mac
        0x8C,
        0xB5,
        0xFA,
        0x44,
        0x33,
        0x7B,
        0x9D,
        0xDB,
        0x47,
        0xDD,
        0x88,
        0xCA,
        0xB1,
        0xAC,
        0xE4,
        0x44,
        0xFD,
        0xD5,
        0x9D,
        0x0C,
        0x7C,
        0xDD,
        0xAC,
        0x2F,
        0x28,
        0x9C,
        0x13,
        0x61,
        0x02,
        0x02,
        0x5C,
        0xBE,
        0x86,
        0xCF,
        0xDE,
        0xDB,
        0xB6,
        0x8F,
        0x2B,
        0x03,
        0x80,
        0xA3,
        0xAF,
        0x41,
        0x81,
        0x87,
        0xD3,
        0x14,
        0x33,
        0x81,
        0x70,
        0x5F,
        0x4E,
        0xD7,
        0xD9,
        0xF2,
        0x00,
        0x0F,
        0x4A,
        0xD6,
        0xF1,
        0xB0,
        0x64,
        0x7C,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x02,
        0x12,
        0x5F,
        0xCF,
        0x93,
        0x0F,
        0x83,
        0x1E,
        0x9A,
        0x87,
        0x3A,
        0xAF,
        0x52,
        0x1D,
        0xC9,
        0x04,
        0x20,
        0x17,
        0x41,
        0x8C,
        0xFF,
        0x8B,
        0xE8,
        0x8F,
        0x2B,
        0x28,
        0x5F,
        0x5E,
        0x9D,
        0x86,
        0xD1,
        0x44,
        0xD9,
        0x98,
        0x49,
        0xC4,
        0xF0,
        0x30,
        0x58,
        0xEF,
        0xA1,
        0x23,
        0x21,
        0xAD,
        0x47,
        0x48,
        0xF7,
        0x00,
        0x0D,
        //2nd part: cihpher
        0xE8,
        0x69,
        0x8B,
        0x63,
        0x3A,
        0x3E,
        //3rd part: mac
        0x8C,
        0xB5,
        0xFA,
        0x44,
        0x33,
        0x7B,
        0x9D,
        0xDB,
        0x47,
        0xDD,
        0x88,
        0xCA,
        0xB1,
        0xAC,
        0xE4,
        0x44,
        0xFD,
        0xD5,
        0x9D,
        0x0C,
        0x7C,
        0xDD,
        0xAC,
        0x2F,
        0x28,
        0x9C,
        0x13,
        0x61,
        0x02,
        0x02,
        0x5C,
        0xBE,
        0x86,
        0xCF,
        0xDE,
        0xDB,
        0xB6,
        0x8F,
        0x2B,
        0x03,
        0x80,
        0xA3,
        0xAF,
        0x41,
        0x81,
        0x87,
        0xD3,
        0x14,
        0x33,
        0x81,
        0x70,
        0x5F,
        0x4E,
        0xD7,
        0xD9,
        0xF2,
        0x00,
        0x0F,
        0x4A,
        0xD6,
        0xF1,
        0xB0,
        0x64,
        0x7C};
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x46,
        0xCD,
        0x3F,
        0x30,
        0x62,
        0x85,
        //3rd part: mac
        0x68,
        0xC0,
        0xE2,
        0xD3,
        0x04,
        0xC4,
        0x33,
        0x21,
        0x04,
        0xB1,
        0x5B,
        0x23,
        0xF8,
        0xB2,
        0x63,
        0xD5,
        0xC1,
        0x24,
        0x5F,
        0xF6,
        0xB4,
        0x06,
        0x19,
        0x02,
        0xDF,
        0x68,
        0x80,
        0x61,
        0xF3,
        0xEF,
        0x06,
        0x1C,
        0xB2,
        0xF2,
        0x42,
        0x95,
        0x35,
        0x20,
        0x98,
        0x64,
        0xA9,
        0x94,
        0x51,
        0x70,
        0x9E,
        0xE5,
        0xF0,
        0xDE,
        0x81,
        0x6D,
        0x4D,
        0xF6,
        0x7F,
        0x8F,
        0xC8,
        0xE1,
        0x48,
        0x1F,
        0x23,
        0x47,
        0x6D,
        0x9F,
        0xDF,
        0xD0,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0xE8,
        0x69,
        0x8B,
        0x63,
        0x3A,
        0x3E,
        //3rd part: mac
        0x3F,
        0x76,
        0xAB,
        0x05,
        0x00,
        0x6E,
        0x76,
        0x32,
        0xD3,
        0x48,
        0xA1,
        0x00,
        0xDE,
        0x36,
        0xFE,
        0x36,
        0x8F,
        0x8F,
        0x62,
        0xFA,
        0xAB,
        0x80,
        0xDB,
        0xAF,
        0xD2,
        0xAF,
        0x9A,
        0x70,
        0x7C,
        0x27,
        0x23,
        0x7B,
        0xC1,
        0x63,
        0x0C,
        0xE2,
        0x3E,
        0x80,
        0xC9,
        0x9D,
        0xA2,
        0xF4,
        0xC1,
        0x49,
        0xAF,
        0x1F,
        0xCC,
        0xCB,
        0x21,
        0xA3,
        0xAA,
        0x36,
        0x95,
        0x42,
        0xD6,
        0x3D,
        0xDB,
        0xA2,
        0x39,
        0x18,
        0x4F,
        0x6C,
        0xAE,
        0x89,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x46,
        0xCD,
        0x3F,
        0x30,
        0x62,
        0x85,
        //3rd part: mac
        0x8D,
        0x58,
        0xE5,
        0xB1,
        0x16,
        0x26,
        0x77,
        0x79,
        0x1E,
        0xD5,
        0x11,
        0x2B,
        0xE0,
        0x28,
        0x43,
        0x5A,
        0x21,
        0x80,
        0x45,
        0x7C,
        0xE4,
        0xF7,
        0x56,
        0x7E,
        0x82,
        0x50,
        0xAD,
        0x02,
        0xEA,
        0xBC,
        0x36,
        0xA8,
        0xE0,
        0x46,
        0x42,
        0x74,
        0xD6,
        0x06,
        0x44,
        0x75,
        0xB0,
        0x38,
        0xF5,
        0xBB,
        0x02,
        0x6D,
        0x1A,
        0x22,
        0xDC,
        0x69,
        0xB2,
        0x7C,
        0x9C,
        0x8A,
        0x61,
        0x1B,
        0xD6,
        0xA4,
        0x58,
        0xAA,
        0xB6,
        0x96,
        0x43,
        0x92,
    };


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = secp384r1;
    char         *curve_name = "secp384r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif
    #if 0
        #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
unsigned int ecies_std_test_secp521r1(void)
{
    unsigned char receiver_pri_key[]= {
        0x01,0xD7,0x21,0x98,0xA8,0x36,0x13,0xDD,0x12,0x50,0xE3,0xB2,0x1C,0xFA,0x9B,0x7A,
        0x74,0x9F,0xE3,0x5D,0x4C,0x29,0x7C,0x01,0xEB,0x86,0x52,0x10,0xE3,0x93,0x27,0x56,
        0xED,0x39,0xB5,0xA1,0x13,0x1E,0x47,0x95,0xE5,0xE4,0x6A,0x90,0x38,0xF9,0x07,0x5B,
        0xB7,0xCA,0x20,0x6F,0x41,0x20,0x9E,0xCB,0xEF,0x58,0x81,0xA7,0x10,0xBE,0x9C,0x45,
        0x60,0xF8,};
    unsigned char receiver_pub_key[]= {
        0x00,0x0B,0xBC,0xE9,0x26,0xE7,0x1B,0x3D,0xDC,0xBB,0x54,0xC3,0x43,0xBA,0x3A,0x7F,
        0x65,0xBB,0x1F,0x11,0x54,0x7E,0xBF,0xA3,0xED,0x09,0x2E,0xD1,0x53,0x65,0xFF,0x56,
        0xCE,0x4D,0xA2,0xEC,0x60,0x6D,0x28,0xB8,0x23,0x31,0x03,0x11,0x2B,0x78,0xAE,0x3A,
        0xA7,0x82,0xE6,0xF4,0x03,0x83,0x55,0xE7,0x9A,0x59,0xF5,0xB5,0x62,0x2D,0x31,0xCD,
        0xCA,0x08,
        0x00,0x0E,0xE2,0x36,0xFF,0x88,0xD2,0x5B,0xF6,0x42,0xF4,0xBD,0xA8,0x69,0x49,0xA2,
        0x97,0x91,0xA2,0x61,0xCB,0xCA,0x1D,0x7E,0x5C,0x70,0xA4,0xBD,0xCD,0xCF,0xC9,0xDF,
        0x75,0x8D,0x3B,0xD7,0x7B,0x2E,0x38,0x91,0x65,0xEB,0x38,0x67,0x0A,0x1F,0x27,0x21,
        0x26,0x92,0xEC,0xA6,0xE9,0xA2,0x9E,0x0E,0x28,0x4B,0x0F,0x3A,0xF7,0x6F,0x81,0x1F,
        0x4D,0x9A,
        };
    unsigned char sender_tmp_pri_key[]= {
        0x00,0x77,0x0A,0xC4,0x2C,0x7D,0x60,0xFA,0xC4,0xC8,0xB2,0x30,0xAE,0x3E,0x26,0xAF,
        0x91,0xCC,0x64,0x9A,0xFF,0x9D,0x87,0xA4,0xF6,0xE0,0xA2,0x16,0x63,0x53,0x7F,0x14,
        0x24,0xD0,0xF9,0xDD,0xD1,0x78,0xF4,0x5A,0x0E,0xB2,0xB3,0x5D,0xDB,0x13,0x0A,0xC8,
        0x5D,0x1A,0x85,0x0C,0xCB,0x43,0x81,0x39,0x52,0xC5,0xA3,0x31,0xC8,0x94,0xBD,0x69,
        0x7A,0x28};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg       = HASH_SHA512;
    HASH_ALG mac_hash_alg       = HASH_SHA512;

    unsigned int mac_key_bytes      = 128;

    unsigned char *msg                = msg_2;
    unsigned int msg_bytes          = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x01,0xC2,0x2E,0x0A,0x0A,0x54,0xCD,0xA6,0x02,0xB6,0x38,0xCF,0x7D,0x39,0xFA,0x74,
        0xA3,0x8B,0x23,0x36,0xC2,0xCE,0x29,0xC1,0x7E,0x12,0xDD,0xF7,0xED,0x06,0x73,0x69,
        0xE4,0x05,0xBC,0x86,0x12,0x37,0x0A,0xA4,0xDC,0x29,0xBD,0x9F,0x0A,0xD1,0xD0,0x4C,
        0x1A,0x24,0x1C,0xF0,0x89,0x85,0x59,0x76,0x0B,0x74,0x69,0xA2,0xB3,0x0E,0xDD,0x8B,
        0x24,0xAF,
        0x00,0xA8,0xF2,0x91,0xE7,0x2D,0xA6,0xF8,0x20,0x93,0x7D,0xDB,0x99,0xB3,0xE4,0xDC,
        0xC1,0x9B,0xEF,0xD3,0xC5,0x29,0x89,0xF7,0x89,0x7D,0x80,0x5A,0xCB,0xC0,0x93,0x09,
        0x25,0x3C,0x87,0xD6,0x88,0x08,0x0F,0xFE,0x64,0xB3,0xF0,0x68,0x67,0x8E,0xAF,0x05,
        0x4F,0xCF,0xFE,0x45,0xB1,0x92,0x74,0x0F,0x32,0x00,0xC2,0x14,0xE7,0x4D,0xE6,0x5E,
        0x3B,0xB3,
        //2nd part: cihpher
        0x80,0x9B,0xC1,0x45,0xB3,0xC8,0x40,0x63,0xF5,0xFE,0xD7,0x4C,0xA2,0xE0,0xA8,0x37,
        0x40,0xD6,0x19,0xB6,0x8A,0x64,0x79,0x71,0xE5,0xCF,0xD0,0x09,0x95,0x97,0x0D,0xAF,
        0xA2,0xB6,0x62,0xE2,0x2C,0x44,0x31,0x2D,0x1A,0xCA,0x0B,
        //3rd part: mac
        0x33,0x77,0xE7,0x0E,0xA8,0xCB,0x30,0x8A,0x48,0xED,0x00,0x44,0x98,0x8E,0x2E,0x6E,
        0x5A,0xC6,0x0A,0x6B,0xD0,0x52,0x2B,0x2E,0xA5,0x00,0x21,0x7A,0xFA,0xE8,0xF7,0x0C,
        0x26,0x93,0x99,0x1A,0x18,0xCE,0x39,0x4C,0x5B,0x72,0x7A,0x11,0x23,0x89,0x19,0xD5,
        0x78,0xB9,0x6B,0xB4,0x5A,0x20,0x2B,0xFE,0x08,0xB8,0xAE,0x1F,0x36,0x5C,0x7D,0x7F,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0x01,0xC2,0x2E,0x0A,0x0A,0x54,0xCD,0xA6,0x02,0xB6,0x38,0xCF,0x7D,0x39,0xFA,0x74,
        0xA3,0x8B,0x23,0x36,0xC2,0xCE,0x29,0xC1,0x7E,0x12,0xDD,0xF7,0xED,0x06,0x73,0x69,
        0xE4,0x05,0xBC,0x86,0x12,0x37,0x0A,0xA4,0xDC,0x29,0xBD,0x9F,0x0A,0xD1,0xD0,0x4C,
        0x1A,0x24,0x1C,0xF0,0x89,0x85,0x59,0x76,0x0B,0x74,0x69,0xA2,0xB3,0x0E,0xDD,0x8B,
        0x24,0xAF,
        //2nd part: cihpher
        0x80,0x9B,0xC1,0x45,0xB3,0xC8,0x40,0x63,0xF5,0xFE,0xD7,0x4C,0xA2,0xE0,0xA8,0x37,
        0x40,0xD6,0x19,0xB6,0x8A,0x64,0x79,0x71,0xE5,0xCF,0xD0,0x09,0x95,0x97,0x0D,0xAF,
        0xA2,0xB6,0x62,0xE2,0x2C,0x44,0x31,0x2D,0x1A,0xCA,0x0B,
        //3rd part: mac
        0x33,0x77,0xE7,0x0E,0xA8,0xCB,0x30,0x8A,0x48,0xED,0x00,0x44,0x98,0x8E,0x2E,0x6E,
        0x5A,0xC6,0x0A,0x6B,0xD0,0x52,0x2B,0x2E,0xA5,0x00,0x21,0x7A,0xFA,0xE8,0xF7,0x0C,
        0x26,0x93,0x99,0x1A,0x18,0xCE,0x39,0x4C,0x5B,0x72,0x7A,0x11,0x23,0x89,0x19,0xD5,
        0x78,0xB9,0x6B,0xB4,0x5A,0x20,0x2B,0xFE,0x08,0xB8,0xAE,0x1F,0x36,0x5C,0x7D,0x7F,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xD5,0x25,0xAF,0x97,0xB1,0x7B,0x0A,0x34,0x5D,0x8C,0x93,0xB0,0x8F,0xAD,0x0C,0xED,
        0x39,0xF0,0x1D,0x08,0xB6,0x85,0xFC,0xC2,0x7D,0x7C,0xC9,0x9A,0xA4,0x5E,0x8F,0xB9,
        0x69,0x5F,0x6E,0x61,0xD3,0x80,0xA7,0x75,0x5B,0x1D,0xEC,
        //3rd part: mac
        0xFB,0xDF,0x9A,0xD3,0x96,0x01,0xB7,0x4A,0xCC,0xA6,0xAD,0xE1,0x69,0x1A,0x8E,0x65,
        0xCA,0x78,0xF6,0x97,0xA5,0x58,0x61,0xD7,0x6D,0x61,0x9D,0x15,0xB0,0x2B,0x3E,0x83,
        0x28,0x56,0x34,0xC3,0xEA,0x54,0x47,0x56,0x2B,0x87,0xD0,0x98,0xFB,0x57,0xF2,0x4E,
        0xA9,0x0C,0xFE,0x23,0x0B,0xEE,0x2E,0xA3,0x49,0x67,0xD4,0x89,0x36,0xA4,0x1A,0x41,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x80,0x9B,0xC1,0x45,0xB3,0xC8,0x40,0x63,0xF5,0xFE,0xD7,0x4C,0xA2,0xE0,0xA8,0x37,
        0x40,0xD6,0x19,0xB6,0x8A,0x64,0x79,0x71,0xE5,0xCF,0xD0,0x09,0x95,0x97,0x0D,0xAF,
        0xA2,0xB6,0x62,0xE2,0x2C,0x44,0x31,0x2D,0x1A,0xCA,0x0B,
        //3rd part: mac
        0xB8,0x35,0x35,0x15,0x20,0x2F,0xEE,0xB9,0xB9,0x52,0x1E,0x86,0xC2,0x3D,0x61,0x16,
        0xE8,0x5D,0xC5,0xCC,0x5C,0xCC,0x59,0xFA,0x60,0xE5,0x95,0xE3,0x19,0xE2,0x95,0xED,
        0xDD,0x6E,0x3E,0xD2,0x93,0xD7,0x86,0x75,0xAD,0xC2,0x5A,0xE5,0x73,0xE9,0x05,0xAE,
        0xA8,0xAD,0xEF,0x62,0xC9,0xB8,0x47,0x34,0xD1,0x36,0xBD,0xE5,0x5F,0xD3,0x26,0x55,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xD5,0x25,0xAF,0x97,0xB1,0x7B,0x0A,0x34,0x5D,0x8C,0x93,0xB0,0x8F,0xAD,0x0C,0xED,
        0x39,0xF0,0x1D,0x08,0xB6,0x85,0xFC,0xC2,0x7D,0x7C,0xC9,0x9A,0xA4,0x5E,0x8F,0xB9,
        0x69,0x5F,0x6E,0x61,0xD3,0x80,0xA7,0x75,0x5B,0x1D,0xEC,
        //3rd part: mac
        0xA2,0xCD,0xCC,0x6F,0x36,0x2A,0xA7,0x18,0xFC,0xA4,0xFA,0xAB,0x4D,0x0D,0x2F,0xD9,
        0x3B,0x7B,0x31,0x29,0x85,0xEC,0x7E,0x6A,0xA5,0xD1,0x04,0x58,0xB3,0x54,0xDE,0x50,
        0xCD,0x13,0x52,0xB8,0xF5,0xBC,0x8B,0xB2,0xB9,0xEB,0xB3,0x0E,0x28,0x18,0xCD,0x79,
        0x8D,0x17,0xA6,0xC5,0x77,0x94,0x00,0x22,0xA9,0x84,0x8F,0x7E,0xB9,0x37,0xE3,0xA0,
    };


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t * curve = secp521r1;
    char * curve_name = "secp521r1";

    unsigned int ret;

    vector->curve                    = curve;
    vector->curve_name               = curve_name;
    vector->msg                      = msg;
    vector->msg_bytes                = msg_bytes;
    vector->shared_info1             = shared_info1;
    vector->shared_info1_bytes       = shared_info1_bytes;
    vector->shared_info2             = shared_info2;
    vector->shared_info2_bytes       = shared_info2_bytes;
    vector->receiver_pri_key         = receiver_pri_key;
    vector->receiver_pub_key         = receiver_pub_key;
    vector->point_form               = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key       = sender_tmp_pri_key;
    vector->kdf_hash_alg             = kdf_hash_alg;
    vector->mac_hash_alg             = mac_hash_alg;
    vector->mac_k_bytes              = mac_key_bytes;
    vector->cipher_part1             = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2*GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if(ret)
        return ret;

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form               = POINT_COMPRESSED;
    vector->cipher_part1             = std_cipher_compressed_without_s1_s2;
    ret = ecies_std_test(vector);
    if(ret)
        return ret;
            #endif

    return ret;

}
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
unsigned int ecies_std_test_brainpoolp160r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x7A,
        0x93,
        0x50,
        0x28,
        0x1D,
        0xFE,
        0x69,
        0x9C,
        0x31,
        0x98,
        0x1F,
        0x73,
        0xCA,
        0x2B,
        0x45,
        0xBF,
        0x4C,
        0x67,
        0x1F,
        0x49,
    };
    unsigned char receiver_pub_key[] = {
        0xC2,
        0xA3,
        0xDE,
        0x48,
        0x0E,
        0x03,
        0xFF,
        0x21,
        0xAA,
        0xCB,
        0x2D,
        0xD1,
        0x26,
        0x5B,
        0xD5,
        0x61,
        0x2E,
        0x00,
        0xB8,
        0xE0,
        0x79,
        0x31,
        0xFF,
        0x0C,
        0x29,
        0x6B,
        0xE9,
        0x15,
        0x4B,
        0x4A,
        0xB3,
        0xBC,
        0xD9,
        0x84,
        0x92,
        0x7A,
        0x28,
        0x98,
        0xDC,
        0x9A,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x0E,
        0x41,
        0x69,
        0x06,
        0xBB,
        0xE3,
        0x94,
        0xC4,
        0xF1,
        0xE7,
        0x49,
        0x88,
        0xCF,
        0xBA,
        0x19,
        0x79,
        0x6F,
        0xA3,
        0xC4,
        0x3D};

    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_2;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_2);

    HASH_ALG kdf_hash_alg = HASH_SHA1;
    HASH_ALG mac_hash_alg = HASH_SHA1;

    unsigned int mac_key_bytes = 64;

    unsigned char *msg       = msg_1;
    unsigned int   msg_bytes = sizeof(msg_1);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x1D,
        0xAB,
        0xF9,
        0x40,
        0xDB,
        0x64,
        0x16,
        0xC0,
        0x66,
        0xF6,
        0xD9,
        0x62,
        0xDA,
        0x53,
        0xC4,
        0x28,
        0x95,
        0x76,
        0x71,
        0x79,
        0x03,
        0xC4,
        0x2E,
        0xB5,
        0x89,
        0x7A,
        0x81,
        0x26,
        0xE5,
        0xE8,
        0x30,
        0x8A,
        0x5C,
        0x59,
        0x53,
        0x52,
        0xCF,
        0x0E,
        0x10,
        0xD1,
        //2nd part: cihpher
        0xFD,
        0xA5,
        0x12,
        0x49,
        0x3A,
        0xC0,
        //3rd part: mac
        0x7B,
        0x45,
        0x7B,
        0x4F,
        0xA5,
        0x5F,
        0xED,
        0x54,
        0xC1,
        0xBD,
        0xFD,
        0x7F,
        0x73,
        0x8F,
        0x51,
        0xE5,
        0x24,
        0xD4,
        0x9F,
        0x56};

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0x1D,
        0xAB,
        0xF9,
        0x40,
        0xDB,
        0x64,
        0x16,
        0xC0,
        0x66,
        0xF6,
        0xD9,
        0x62,
        0xDA,
        0x53,
        0xC4,
        0x28,
        0x95,
        0x76,
        0x71,
        0x79,
        //2nd part: cihpher
        0xFD,
        0xA5,
        0x12,
        0x49,
        0x3A,
        0xC0,
        //3rd part: mac
        0x7B,
        0x45,
        0x7B,
        0x4F,
        0xA5,
        0x5F,
        0xED,
        0x54,
        0xC1,
        0xBD,
        0xFD,
        0x7F,
        0x73,
        0x8F,
        0x51,
        0xE5,
        0x24,
        0xD4,
        0x9F,
        0x56};
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xFC,
        0xB8,
        0xF3,
        0x7D,
        0xFF,
        0xC4,
        //3rd part: mac
        0x0F,
        0x92,
        0x71,
        0xBE,
        0x58,
        0x26,
        0xEE,
        0xC1,
        0xEB,
        0x55,
        0x28,
        0x26,
        0x40,
        0x08,
        0x31,
        0x5B,
        0xA6,
        0xFB,
        0x8D,
        0xBC};
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0xFD,
        0xA5,
        0x12,
        0x49,
        0x3A,
        0xC0,
        //3rd part: mac
        0x5A,
        0xEF,
        0x7F,
        0x47,
        0x3B,
        0xB5,
        0xD3,
        0x2D,
        0x35,
        0x9F,
        0xD8,
        0x71,
        0xBF,
        0xCA,
        0x8F,
        0x4A,
        0xDB,
        0xD7,
        0x99,
        0xC1};
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xFC,
        0xB8,
        0xF3,
        0x7D,
        0xFF,
        0xC4,
        //3rd part: mac
        0x3B,
        0x24,
        0x00,
        0x73,
        0xC1,
        0x15,
        0x57,
        0x7A,
        0xAF,
        0x28,
        0xFC,
        0x9E,
        0xBD,
        0xBA,
        0xBE,
        0x73,
        0x61,
        0xA6,
        0xBB,
        0x62};


    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = brainpoolp160r1;
    char         *curve_name = "brainpoolp160r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
unsigned int ecies_std_test_brainpoolp512r1(void)
{
    unsigned char receiver_pri_key[] = {
        0x15,
        0xFE,
        0xF6,
        0xF9,
        0xD6,
        0x9D,
        0xD2,
        0x6D,
        0xD3,
        0xF7,
        0xD9,
        0xD4,
        0xD8,
        0xBB,
        0x92,
        0x33,
        0x6B,
        0xF9,
        0x37,
        0x05,
        0xD0,
        0x23,
        0xB7,
        0xCB,
        0xA6,
        0xCB,
        0xE4,
        0x2A,
        0x09,
        0x56,
        0x84,
        0xBB,
        0x8C,
        0x05,
        0xD3,
        0x35,
        0xAF,
        0x58,
        0x70,
        0x07,
        0x27,
        0x3C,
        0x55,
        0x7B,
        0xC0,
        0x1B,
        0xA5,
        0x01,
        0x36,
        0xC0,
        0xB5,
        0x1B,
        0x4E,
        0xA5,
        0x40,
        0xFA,
        0xEC,
        0x8A,
        0xB1,
        0x8F,
        0xB0,
        0x05,
        0x1F,
        0x42,
    };
    unsigned char receiver_pub_key[] = {
        0x10,
        0x27,
        0xAA,
        0x4B,
        0x6B,
        0x18,
        0x0D,
        0x7C,
        0xC6,
        0xA4,
        0x4D,
        0x76,
        0x95,
        0x52,
        0x1C,
        0x69,
        0x26,
        0xF9,
        0x47,
        0x66,
        0x48,
        0x35,
        0x3E,
        0x6C,
        0xEB,
        0x41,
        0x44,
        0xB8,
        0x0F,
        0x67,
        0x7D,
        0xFB,
        0xEF,
        0x54,
        0x92,
        0x01,
        0x34,
        0x77,
        0x0E,
        0xEF,
        0xCF,
        0x55,
        0x93,
        0x8D,
        0x78,
        0xB8,
        0xBA,
        0x09,
        0x8C,
        0x8C,
        0x4D,
        0x9F,
        0xC3,
        0x91,
        0xA5,
        0x85,
        0x51,
        0x62,
        0xD9,
        0x9D,
        0x1C,
        0x11,
        0x66,
        0x81,
        0x40,
        0xA3,
        0xD1,
        0x5D,
        0xDD,
        0xE0,
        0x12,
        0xF3,
        0x77,
        0xD0,
        0xE8,
        0x02,
        0xE2,
        0x6C,
        0x64,
        0x5F,
        0xB4,
        0xB6,
        0xE8,
        0x93,
        0x51,
        0xE3,
        0xC8,
        0xE1,
        0x29,
        0x7A,
        0x6C,
        0xB0,
        0x19,
        0x05,
        0x13,
        0x6F,
        0x9A,
        0x91,
        0x1A,
        0x9D,
        0x38,
        0x44,
        0xF5,
        0xC8,
        0x2D,
        0x8B,
        0x1E,
        0x2C,
        0x27,
        0x3C,
        0xD0,
        0x15,
        0xE7,
        0x29,
        0xC1,
        0x95,
        0xE0,
        0x77,
        0x3D,
        0xA8,
        0xF6,
        0x5F,
        0x88,
        0xBD,
        0xCF,
        0x49,
        0xA2,
        0xE8,
    };
    unsigned char sender_tmp_pri_key[] = {
        0x37,
        0xCB,
        0x39,
        0xEB,
        0x5E,
        0xA8,
        0x26,
        0x94,
        0xB3,
        0x5C,
        0x9D,
        0xCE,
        0x95,
        0xDB,
        0x4D,
        0xB4,
        0x8E,
        0x09,
        0xA4,
        0x41,
        0x29,
        0x23,
        0x73,
        0xFE,
        0xF4,
        0xB4,
        0x9B,
        0x24,
        0xF9,
        0xE4,
        0xDA,
        0xC3,
        0x24,
        0xC9,
        0xEA,
        0x9F,
        0xCA,
        0x21,
        0xB3,
        0xD1,
        0x60,
        0x9B,
        0x7C,
        0x6C,
        0xFE,
        0xA8,
        0x0E,
        0x86,
        0x6A,
        0xB6,
        0xCA,
        0x43,
        0x83,
        0x12,
        0x89,
        0xB5,
        0xD2,
        0x9C,
        0x53,
        0x75,
        0xE6,
        0xDD,
        0xBF,
        0x15,
    };


    //shared_info for KDF
    unsigned char *shared_info1       = shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 128;

    unsigned char *msg       = msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0x20,
        0x40,
        0x0C,
        0x73,
        0x1F,
        0xD3,
        0xC4,
        0x84,
        0xF3,
        0x68,
        0xBD,
        0xFC,
        0x44,
        0xA2,
        0x69,
        0xC4,
        0x16,
        0x44,
        0xF3,
        0xE0,
        0xEB,
        0xDA,
        0x25,
        0xFB,
        0xAF,
        0xC8,
        0xD1,
        0x85,
        0xD5,
        0xCE,
        0x06,
        0xD1,
        0x3A,
        0x93,
        0x24,
        0x4F,
        0x88,
        0x4C,
        0xFC,
        0x31,
        0x0B,
        0xF3,
        0xCD,
        0x09,
        0xC1,
        0x7A,
        0xA2,
        0x30,
        0x69,
        0x76,
        0x37,
        0xCB,
        0x20,
        0x7E,
        0x18,
        0x4C,
        0xEE,
        0xEE,
        0x14,
        0xFF,
        0x20,
        0xF8,
        0xB3,
        0x08,
        0x8E,
        0x65,
        0xB7,
        0x91,
        0xF9,
        0x41,
        0x6C,
        0xA6,
        0x40,
        0xBE,
        0xB4,
        0xEB,
        0x19,
        0x53,
        0x0D,
        0xDF,
        0x41,
        0x0A,
        0xD7,
        0x53,
        0x07,
        0x7F,
        0x2B,
        0x91,
        0x2C,
        0xBB,
        0x97,
        0xEA,
        0x41,
        0xDA,
        0x48,
        0xC2,
        0x35,
        0x3A,
        0xA4,
        0xAC,
        0xA7,
        0xFF,
        0xF0,
        0xB1,
        0xA8,
        0x36,
        0x07,
        0x69,
        0xB4,
        0xD6,
        0xA7,
        0x9B,
        0xC4,
        0xD0,
        0x81,
        0x33,
        0x2E,
        0x72,
        0xF2,
        0x8D,
        0x84,
        0xB3,
        0x6D,
        0x48,
        0x43,
        0x87,
        0x0E,
        0xAF,
        //2nd part: cihpher
        0x52,
        0xFB,
        0x89,
        0x85,
        0x0B,
        0x51,
        0xD6,
        0xC4,
        0xC0,
        0xBE,
        0xDC,
        0xCC,
        0x23,
        0xCD,
        0x20,
        0x23,
        0x18,
        0x59,
        0xEF,
        0xA1,
        0x5E,
        0x25,
        0x44,
        0x87,
        0xF8,
        0xAD,
        0x2C,
        0x8A,
        0x8F,
        0x4B,
        0x5D,
        0x17,
        0x69,
        0xFC,
        0x2E,
        0xD8,
        0xEC,
        0xB4,
        0x1A,
        0x7C,
        0x13,
        0xD3,
        0xD9,
        //3rd part: mac
        0x9B,
        0x3C,
        0x83,
        0xCB,
        0x92,
        0x1E,
        0xE1,
        0xBC,
        0x84,
        0x69,
        0x45,
        0xFA,
        0x83,
        0x41,
        0x08,
        0x2C,
        0x44,
        0xAD,
        0xA6,
        0x44,
        0xD6,
        0x20,
        0xF1,
        0x1F,
        0xCE,
        0x34,
        0x2A,
        0xC7,
        0xF6,
        0xED,
        0x3F,
        0x24,
        0xD7,
        0xB2,
        0x1C,
        0x34,
        0x07,
        0x22,
        0x6D,
        0x6E,
        0x79,
        0x59,
        0x27,
        0xEF,
        0x2B,
        0x2B,
        0xBF,
        0x7A,
        0xF3,
        0x9B,
        0xCF,
        0x56,
        0xBE,
        0xDA,
        0x6E,
        0x8B,
        0x0D,
        0xD2,
        0xF8,
        0x5D,
        0xF3,
        0xD6,
        0x4D,
        0x55,
    };

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0x20,
        0x40,
        0x0C,
        0x73,
        0x1F,
        0xD3,
        0xC4,
        0x84,
        0xF3,
        0x68,
        0xBD,
        0xFC,
        0x44,
        0xA2,
        0x69,
        0xC4,
        0x16,
        0x44,
        0xF3,
        0xE0,
        0xEB,
        0xDA,
        0x25,
        0xFB,
        0xAF,
        0xC8,
        0xD1,
        0x85,
        0xD5,
        0xCE,
        0x06,
        0xD1,
        0x3A,
        0x93,
        0x24,
        0x4F,
        0x88,
        0x4C,
        0xFC,
        0x31,
        0x0B,
        0xF3,
        0xCD,
        0x09,
        0xC1,
        0x7A,
        0xA2,
        0x30,
        0x69,
        0x76,
        0x37,
        0xCB,
        0x20,
        0x7E,
        0x18,
        0x4C,
        0xEE,
        0xEE,
        0x14,
        0xFF,
        0x20,
        0xF8,
        0xB3,
        0x08,
        //2nd part: cihpher
        0x52,
        0xFB,
        0x89,
        0x85,
        0x0B,
        0x51,
        0xD6,
        0xC4,
        0xC0,
        0xBE,
        0xDC,
        0xCC,
        0x23,
        0xCD,
        0x20,
        0x23,
        0x18,
        0x59,
        0xEF,
        0xA1,
        0x5E,
        0x25,
        0x44,
        0x87,
        0xF8,
        0xAD,
        0x2C,
        0x8A,
        0x8F,
        0x4B,
        0x5D,
        0x17,
        0x69,
        0xFC,
        0x2E,
        0xD8,
        0xEC,
        0xB4,
        0x1A,
        0x7C,
        0x13,
        0xD3,
        0xD9,
        //3rd part: mac
        0x9B,
        0x3C,
        0x83,
        0xCB,
        0x92,
        0x1E,
        0xE1,
        0xBC,
        0x84,
        0x69,
        0x45,
        0xFA,
        0x83,
        0x41,
        0x08,
        0x2C,
        0x44,
        0xAD,
        0xA6,
        0x44,
        0xD6,
        0x20,
        0xF1,
        0x1F,
        0xCE,
        0x34,
        0x2A,
        0xC7,
        0xF6,
        0xED,
        0x3F,
        0x24,
        0xD7,
        0xB2,
        0x1C,
        0x34,
        0x07,
        0x22,
        0x6D,
        0x6E,
        0x79,
        0x59,
        0x27,
        0xEF,
        0x2B,
        0x2B,
        0xBF,
        0x7A,
        0xF3,
        0x9B,
        0xCF,
        0x56,
        0xBE,
        0xDA,
        0x6E,
        0x8B,
        0x0D,
        0xD2,
        0xF8,
        0x5D,
        0xF3,
        0xD6,
        0x4D,
        0x55,
    };
            #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0x2D,
        0xBF,
        0xE3,
        0x38,
        0xAE,
        0xF3,
        0x52,
        0x17,
        0x54,
        0x2B,
        0x58,
        0x3D,
        0x51,
        0xF2,
        0xCA,
        0x38,
        0xFA,
        0x30,
        0x41,
        0x47,
        0x02,
        0x86,
        0x2B,
        0xB2,
        0xB4,
        0xE3,
        0x36,
        0x79,
        0x29,
        0x53,
        0x51,
        0x7E,
        0x07,
        0xE0,
        0x65,
        0xD0,
        0xA8,
        0x4A,
        0x69,
        0x0B,
        0xA9,
        0x12,
        0xA5,
        //3rd part: mac
        0x9D,
        0xAB,
        0xD0,
        0xDF,
        0xEB,
        0xB2,
        0x44,
        0x50,
        0xA0,
        0xFB,
        0xFC,
        0xC1,
        0x3C,
        0x1F,
        0xC5,
        0x07,
        0x91,
        0xF1,
        0x9A,
        0x12,
        0xCD,
        0x89,
        0xB1,
        0x0F,
        0x50,
        0xE3,
        0xC2,
        0xC2,
        0xD3,
        0xFD,
        0x98,
        0x52,
        0xF1,
        0x82,
        0xA0,
        0x31,
        0x7F,
        0x9B,
        0xB5,
        0x1C,
        0x30,
        0x12,
        0xDC,
        0x80,
        0x91,
        0xCD,
        0xBB,
        0x15,
        0x1A,
        0xA6,
        0xD8,
        0x16,
        0xF2,
        0x5B,
        0x62,
        0xC6,
        0x42,
        0x9C,
        0xF1,
        0x33,
        0x77,
        0xCF,
        0x8A,
        0xE9,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0x52,
        0xFB,
        0x89,
        0x85,
        0x0B,
        0x51,
        0xD6,
        0xC4,
        0xC0,
        0xBE,
        0xDC,
        0xCC,
        0x23,
        0xCD,
        0x20,
        0x23,
        0x18,
        0x59,
        0xEF,
        0xA1,
        0x5E,
        0x25,
        0x44,
        0x87,
        0xF8,
        0xAD,
        0x2C,
        0x8A,
        0x8F,
        0x4B,
        0x5D,
        0x17,
        0x69,
        0xFC,
        0x2E,
        0xD8,
        0xEC,
        0xB4,
        0x1A,
        0x7C,
        0x13,
        0xD3,
        0xD9,
        //3rd part: mac
        0x96,
        0x26,
        0x5C,
        0x90,
        0xCF,
        0xC6,
        0xD9,
        0x6D,
        0x39,
        0x74,
        0x9A,
        0xF5,
        0x02,
        0x47,
        0xBC,
        0xEA,
        0x15,
        0x30,
        0x13,
        0x06,
        0xFF,
        0x1C,
        0x1D,
        0x48,
        0x44,
        0xBC,
        0x35,
        0xA2,
        0xA6,
        0x63,
        0xA6,
        0x24,
        0x66,
        0x1D,
        0x21,
        0xDC,
        0x06,
        0x7B,
        0x52,
        0xEB,
        0x0E,
        0x09,
        0x4B,
        0xD4,
        0xB4,
        0x37,
        0x34,
        0x1D,
        0x45,
        0x3F,
        0xF4,
        0x3F,
        0x10,
        0xEE,
        0xCE,
        0x85,
        0xAC,
        0x94,
        0x67,
        0x3A,
        0x0D,
        0x95,
        0x49,
        0xD4,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0x2D,
        0xBF,
        0xE3,
        0x38,
        0xAE,
        0xF3,
        0x52,
        0x17,
        0x54,
        0x2B,
        0x58,
        0x3D,
        0x51,
        0xF2,
        0xCA,
        0x38,
        0xFA,
        0x30,
        0x41,
        0x47,
        0x02,
        0x86,
        0x2B,
        0xB2,
        0xB4,
        0xE3,
        0x36,
        0x79,
        0x29,
        0x53,
        0x51,
        0x7E,
        0x07,
        0xE0,
        0x65,
        0xD0,
        0xA8,
        0x4A,
        0x69,
        0x0B,
        0xA9,
        0x12,
        0xA5,
        //3rd part: mac
        0x9B,
        0xC4,
        0xDB,
        0x20,
        0xB9,
        0xE7,
        0xD2,
        0xA6,
        0xD2,
        0x09,
        0xD0,
        0xCA,
        0x7F,
        0x52,
        0xB3,
        0xE9,
        0x13,
        0xA5,
        0xB3,
        0x37,
        0x23,
        0x18,
        0xF8,
        0xEB,
        0xF6,
        0xB0,
        0x48,
        0xA6,
        0x87,
        0x80,
        0x85,
        0x17,
        0xD5,
        0x6D,
        0xC5,
        0x43,
        0xE9,
        0x6C,
        0xD8,
        0x62,
        0x8C,
        0xCE,
        0x6F,
        0x47,
        0xD1,
        0x66,
        0xCA,
        0xB6,
        0x9E,
        0x7E,
        0x1B,
        0xB6,
        0x37,
        0xB5,
        0x4A,
        0xD1,
        0xD7,
        0x2F,
        0x0B,
        0x02,
        0x4B,
        0xDE,
        0x1A,
        0x94,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = brainpoolp512r1;
    char         *curve_name = "brainpoolp512r1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

            #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
            #endif

    return ret;
}
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
unsigned int ecies_std_test_anders_1024_1()
{
    unsigned char receiver_pri_key[] = {
        0xAB,
        0x9C,
        0xAD,
        0xEA,
        0xAE,
        0x36,
        0x74,
        0xFC,
        0xE7,
        0x76,
        0x99,
        0x5B,
        0x80,
        0x91,
        0xA2,
        0x95,
        0x71,
        0xEC,
        0x54,
        0x3E,
        0x46,
        0x89,
        0x6E,
        0x25,
        0x6F,
        0x94,
        0x56,
        0xE1,
        0xC0,
        0xC7,
        0xA9,
        0x9E,
        0x7E,
        0xD6,
        0xDD,
        0x15,
        0x07,
        0x4E,
        0xDB,
        0xE6,
        0xA9,
        0x07,
        0xC9,
        0x30,
        0xBB,
        0xAB,
        0xD6,
        0x0E,
        0xD8,
        0x49,
        0x7B,
        0x15,
        0xD7,
        0x04,
        0x70,
        0x9B,
        0x1D,
        0xC3,
        0x54,
        0xC9,
        0x93,
        0xD2,
        0xF3,
        0x97,
        0xF0,
        0xA5,
        0x7A,
        0x4F,
        0x95,
        0x17,
        0xDC,
        0xFB,
        0x7E,
        0xBF,
        0xB8,
        0x2A,
        0x93,
        0xCC,
        0xD2,
        0x2A,
        0x4B,
        0xF8,
        0xA0,
        0x95,
        0x25,
        0x8F,
        0xCA,
        0x0D,
        0xD6,
        0x79,
        0x1C,
        0x96,
        0x3E,
        0x05,
        0x26,
        0x7C,
        0xE1,
        0xD3,
        0x22,
        0xDE,
        0x7F,
        0x34,
        0xC4,
        0x62,
        0x8B,
        0xFF,
        0x43,
        0xFB,
        0xE3,
        0x2D,
        0x43,
        0xA4,
        0x83,
        0x85,
        0x7F,
        0x7A,
        0x64,
        0x3C,
        0x27,
        0xFB,
        0xBE,
        0x7B,
        0xA3,
        0xA1,
        0xA7,
        0x25,
        0x3D,
        0x9B,
    };
    unsigned char receiver_pub_key[] = {
        0xB4,
        0xD2,
        0xBC,
        0x27,
        0xAD,
        0xF5,
        0xA1,
        0x75,
        0x07,
        0x7F,
        0x65,
        0x78,
        0x04,
        0x29,
        0x74,
        0x2F,
        0xB2,
        0xE9,
        0x4A,
        0x4A,
        0x85,
        0xD0,
        0x28,
        0xD9,
        0x1F,
        0xE4,
        0xD4,
        0xFF,
        0x5D,
        0x9C,
        0xEF,
        0x3F,
        0xE9,
        0x7A,
        0x2B,
        0x9F,
        0xEB,
        0x97,
        0x22,
        0xFF,
        0x4F,
        0x19,
        0x18,
        0xB1,
        0xC9,
        0xFD,
        0x21,
        0xD9,
        0x3A,
        0xEA,
        0x04,
        0xDE,
        0xBC,
        0x8C,
        0xA7,
        0x88,
        0x55,
        0x46,
        0xC2,
        0xED,
        0xF9,
        0xDF,
        0x0E,
        0xA2,
        0x15,
        0xC8,
        0xC7,
        0x4E,
        0x83,
        0x9B,
        0xB3,
        0xE1,
        0x37,
        0xF4,
        0xD5,
        0x46,
        0x9A,
        0x92,
        0x97,
        0x94,
        0x04,
        0x8E,
        0x0C,
        0xC5,
        0xC8,
        0x03,
        0x17,
        0x8C,
        0x29,
        0x29,
        0x24,
        0xBA,
        0xC3,
        0xC2,
        0x16,
        0x0D,
        0x4C,
        0xC8,
        0x30,
        0x13,
        0x45,
        0xDF,
        0xE0,
        0x72,
        0xAA,
        0xA1,
        0xF8,
        0x4B,
        0x25,
        0x57,
        0xFC,
        0x7C,
        0x56,
        0x32,
        0x14,
        0xFD,
        0x50,
        0x46,
        0x11,
        0x37,
        0xBC,
        0x28,
        0x5E,
        0x8C,
        0xC4,
        0xF6,
        0xA7,
        0xCC,
        0xF3,
        0x95,
        0xA5,
        0x54,
        0xA9,
        0xC1,
        0x0B,
        0x22,
        0x47,
        0xD4,
        0x68,
        0xDE,
        0xD2,
        0x4C,
        0x1C,
        0x75,
        0x67,
        0x3A,
        0x5F,
        0x3A,
        0x22,
        0x1E,
        0x3D,
        0xED,
        0x3A,
        0xDB,
        0x41,
        0x37,
        0xB6,
        0x33,
        0x04,
        0xF9,
        0x0A,
        0x5A,
        0xC6,
        0x09,
        0x7D,
        0x61,
        0x0E,
        0x3D,
        0x7A,
        0x6A,
        0x9D,
        0xF9,
        0xCC,
        0xA3,
        0xCD,
        0x13,
        0xB1,
        0x2B,
        0xF8,
        0x3B,
        0xD9,
        0x83,
        0xDB,
        0x55,
        0xBF,
        0x59,
        0xEA,
        0x02,
        0x51,
        0x49,
        0x74,
        0xE7,
        0x41,
        0x1B,
        0x37,
        0x8F,
        0xF9,
        0x18,
        0x74,
        0x88,
        0x99,
        0x15,
        0x75,
        0x38,
        0xEF,
        0x33,
        0x95,
        0x4E,
        0x5E,
        0x61,
        0x46,
        0xA1,
        0x82,
        0x28,
        0x3B,
        0x5C,
        0xA5,
        0x2E,
        0xF8,
        0x8D,
        0x21,
        0xA2,
        0x1C,
        0x14,
        0x70,
        0xAF,
        0xA8,
        0x98,
        0x62,
        0xA0,
        0x9D,
        0x7F,
        0xFE,
        0x65,
        0xF5,
        0xEF,
        0xAD,
        0x24,
        0xF3,
        0xAB,
        0x5D,
        0x65,
        0xBE,
        0x0E,
        0x75,
        0x39,
        0xB4,
        0x04,
        0x5D,
        0x19,
        0xB6,
        0xDF,
        0x7F,
        0xE2,
        0xEC,
        0xB7,
    };
    unsigned char sender_tmp_pri_key[] = {
        0xD2,
        0x81,
        0xD9,
        0xF5,
        0x3A,
        0x40,
        0xCC,
        0x22,
        0xD7,
        0xCB,
        0xB0,
        0x3B,
        0x4A,
        0x8C,
        0x46,
        0x4B,
        0xF7,
        0x34,
        0xE1,
        0x57,
        0xAA,
        0x30,
        0x0E,
        0x10,
        0x91,
        0xE0,
        0xD9,
        0xB0,
        0x0C,
        0x55,
        0xB4,
        0x8C,
        0x8B,
        0xC1,
        0x84,
        0xF6,
        0x5A,
        0x3A,
        0x51,
        0x68,
        0x64,
        0x36,
        0x94,
        0x87,
        0xBC,
        0x8F,
        0x1D,
        0x2C,
        0x28,
        0x56,
        0x3B,
        0xDA,
        0x90,
        0x6D,
        0xD5,
        0x02,
        0x69,
        0x32,
        0xE4,
        0xAB,
        0x44,
        0x4D,
        0x7F,
        0x12,
        0x20,
        0xF8,
        0xDA,
        0x39,
        0xCF,
        0x5D,
        0xE0,
        0x9D,
        0xE6,
        0x36,
        0x2F,
        0xF5,
        0xD0,
        0x47,
        0xD7,
        0x22,
        0x15,
        0x03,
        0x74,
        0x2F,
        0xFF,
        0x0F,
        0x0F,
        0x56,
        0xD2,
        0x76,
        0x55,
        0x79,
        0x20,
        0x06,
        0x85,
        0x61,
        0x1F,
        0x31,
        0x7D,
        0x8C,
        0xAC,
        0x61,
        0x13,
        0x4D,
        0xB2,
        0x3D,
        0xC9,
        0xCD,
        0x8F,
        0x92,
        0x52,
        0xE9,
        0x2E,
        0x29,
        0xF6,
        0xBF,
        0x46,
        0xEA,
        0x82,
        0x21,
        0x8E,
        0xA8,
        0x08,
        0x55,
        0x03,
        0x92,
        0x29,
        0x0F,
    };


    //shared_info for KDF
    unsigned char *shared_info1       = (unsigned char *)shared_info1_2;
    unsigned int   shared_info1_bytes = sizeof(shared_info1_2);
    //shared_info for MAC
    unsigned char *shared_info2       = (unsigned char *)shared_info2_1;
    unsigned int   shared_info2_bytes = sizeof(shared_info2_1);

    HASH_ALG kdf_hash_alg = HASH_SHA512;
    HASH_ALG mac_hash_alg = HASH_SHA512;

    unsigned int mac_key_bytes = 128;

    unsigned char *msg       = (unsigned char *)msg_2;
    unsigned int   msg_bytes = sizeof(msg_2);

    unsigned char std_cipher_uncompressed_without_s1_s2[] = {
        //1st part: a point
        0x04,
        0xDD,
        0x09,
        0xD7,
        0x95,
        0x04,
        0xE0,
        0xFE,
        0x26,
        0x0C,
        0x6E,
        0x6F,
        0x03,
        0xC1,
        0x0F,
        0xF6,
        0x50,
        0xC5,
        0x32,
        0xC1,
        0xF4,
        0x09,
        0xA4,
        0x1D,
        0x6E,
        0x62,
        0x17,
        0xCE,
        0xF3,
        0x15,
        0xD1,
        0x09,
        0x31,
        0xD6,
        0xF0,
        0xD7,
        0x78,
        0xCC,
        0xCA,
        0x92,
        0xE9,
        0xCE,
        0xE0,
        0xA3,
        0xCD,
        0xC3,
        0x93,
        0x83,
        0xE6,
        0xCC,
        0xB8,
        0xE2,
        0xF5,
        0xE4,
        0x5C,
        0xC2,
        0x90,
        0xD4,
        0xAC,
        0x01,
        0x76,
        0x6D,
        0x0A,
        0x8E,
        0xF0,
        0x7A,
        0x59,
        0xB1,
        0x11,
        0x49,
        0xE2,
        0x01,
        0x86,
        0x62,
        0x97,
        0xC2,
        0x9E,
        0x2F,
        0x0E,
        0x61,
        0x3B,
        0xDC,
        0xD9,
        0xB6,
        0xD1,
        0x93,
        0x94,
        0xB6,
        0x8A,
        0xA9,
        0xF9,
        0xCE,
        0x67,
        0x8F,
        0x86,
        0x40,
        0xE4,
        0x58,
        0xF9,
        0xCA,
        0x32,
        0xB0,
        0x26,
        0x67,
        0xBD,
        0xF5,
        0x8E,
        0x88,
        0xFD,
        0x91,
        0x10,
        0xF1,
        0xF0,
        0x8B,
        0x8C,
        0xF1,
        0xFE,
        0x98,
        0x54,
        0x1D,
        0xA9,
        0x2F,
        0xD9,
        0xF3,
        0xC6,
        0x82,
        0x36,
        0x57,
        0x56,
        0xA9,
        0xD8,
        0x2F,
        0x71,
        0x03,
        0x48,
        0x3A,
        0x3C,
        0x27,
        0x77,
        0x08,
        0xD4,
        0x02,
        0xC2,
        0xCA,
        0xC9,
        0xD5,
        0xDC,
        0x97,
        0x19,
        0x3C,
        0x90,
        0xA0,
        0x19,
        0x17,
        0x04,
        0x67,
        0xFD,
        0x6D,
        0x72,
        0x94,
        0xD3,
        0x54,
        0x33,
        0x61,
        0x61,
        0xE2,
        0x78,
        0xAE,
        0x00,
        0x40,
        0x82,
        0x48,
        0xAA,
        0x7A,
        0x9E,
        0x1A,
        0x3F,
        0x80,
        0xE4,
        0x8A,
        0x0C,
        0xDA,
        0x2D,
        0xC3,
        0x2F,
        0xBF,
        0x57,
        0xC5,
        0xEE,
        0x8E,
        0xFB,
        0xAF,
        0x2B,
        0x3B,
        0x93,
        0x75,
        0x6B,
        0x05,
        0x7D,
        0x8D,
        0xC8,
        0xD4,
        0x5F,
        0x14,
        0x1A,
        0xD7,
        0x23,
        0xDB,
        0xD9,
        0x44,
        0x14,
        0xDE,
        0xF9,
        0x7A,
        0xC8,
        0x64,
        0xD9,
        0xC5,
        0x5A,
        0xB9,
        0x8D,
        0xEA,
        0x15,
        0x44,
        0x00,
        0x89,
        0x05,
        0x5C,
        0xD5,
        0x1E,
        0x89,
        0x90,
        0xF9,
        0x08,
        0x29,
        0x9F,
        0x81,
        0xA7,
        0xA8,
        0x82,
        0xEA,
        0xAB,
        0xEF,
        0xD7,
        0x2E,
        0xC9,
        0x07,
        0x59,
        0x23,
        0x78,
        0xFF,
        0x88,
        0xE3,
        0xDB,
        0xCD,
        0xED,
        0xCF,
        //2nd part: cihpher
        0xa8,
        0xe5,
        0xed,
        0x47,
        0x43,
        0xac,
        0x3f,
        0x13,
        0x61,
        0x6a,
        0x9d,
        0x30,
        0xc1,
        0x85,
        0x88,
        0xc6,
        0x29,
        0x1d,
        0x59,
        0xf0,
        0x8a,
        0xe6,
        0x94,
        0x5f,
        0x51,
        0x85,
        0x3a,
        0x78,
        0x2f,
        0x38,
        0xb1,
        0xa8,
        0xd5,
        0xf6,
        0xc7,
        0x3a,
        0x9e,
        0x04,
        0xe2,
        0x82,
        0x94,
        0x87,
        0xf8,
        //3rd part: mac
        0x0A,
        0x11,
        0x7C,
        0x70,
        0x80,
        0x22,
        0xE9,
        0x77,
        0xFA,
        0x78,
        0xA0,
        0x11,
        0x0B,
        0xE2,
        0x57,
        0xF1,
        0x5F,
        0xB7,
        0x47,
        0x3A,
        0x15,
        0x91,
        0x63,
        0x81,
        0x32,
        0x88,
        0x54,
        0x56,
        0x6E,
        0xE3,
        0x29,
        0xB6,
        0x91,
        0x5F,
        0xD9,
        0x5C,
        0xD6,
        0xB8,
        0x86,
        0x55,
        0x56,
        0x6D,
        0x4A,
        0xF1,
        0x1F,
        0x9B,
        0x34,
        0x56,
        0xC3,
        0xD4,
        0x5A,
        0x60,
        0x4B,
        0xE5,
        0x84,
        0x6C,
        0x87,
        0xB9,
        0xD8,
        0x23,
        0x1C,
        0x97,
        0xE1,
        0xBE,
    };

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    //compared to the uncompressed one, this only modified 1st part of the whole ciphertext, and saved some memory.
    unsigned char std_cipher_compressed_without_s1_s2[] = {
        //1st part: a point
        0x03,
        0xDD,
        0x09,
        0xD7,
        0x95,
        0x04,
        0xE0,
        0xFE,
        0x26,
        0x0C,
        0x6E,
        0x6F,
        0x03,
        0xC1,
        0x0F,
        0xF6,
        0x50,
        0xC5,
        0x32,
        0xC1,
        0xF4,
        0x09,
        0xA4,
        0x1D,
        0x6E,
        0x62,
        0x17,
        0xCE,
        0xF3,
        0x15,
        0xD1,
        0x09,
        0x31,
        0xD6,
        0xF0,
        0xD7,
        0x78,
        0xCC,
        0xCA,
        0x92,
        0xE9,
        0xCE,
        0xE0,
        0xA3,
        0xCD,
        0xC3,
        0x93,
        0x83,
        0xE6,
        0xCC,
        0xB8,
        0xE2,
        0xF5,
        0xE4,
        0x5C,
        0xC2,
        0x90,
        0xD4,
        0xAC,
        0x01,
        0x76,
        0x6D,
        0x0A,
        0x8E,
        0xF0,
        0x7A,
        0x59,
        0xB1,
        0x11,
        0x49,
        0xE2,
        0x01,
        0x86,
        0x62,
        0x97,
        0xC2,
        0x9E,
        0x2F,
        0x0E,
        0x61,
        0x3B,
        0xDC,
        0xD9,
        0xB6,
        0xD1,
        0x93,
        0x94,
        0xB6,
        0x8A,
        0xA9,
        0xF9,
        0xCE,
        0x67,
        0x8F,
        0x86,
        0x40,
        0xE4,
        0x58,
        0xF9,
        0xCA,
        0x32,
        0xB0,
        0x26,
        0x67,
        0xBD,
        0xF5,
        0x8E,
        0x88,
        0xFD,
        0x91,
        0x10,
        0xF1,
        0xF0,
        0x8B,
        0x8C,
        0xF1,
        0xFE,
        0x98,
        0x54,
        0x1D,
        0xA9,
        0x2F,
        0xD9,
        0xF3,
        0xC6,
        0x82,
        0x36,
        0x57,
        0x56,
        //2nd part: cihpher
        0xa8,
        0xe5,
        0xed,
        0x47,
        0x43,
        0xac,
        0x3f,
        0x13,
        0x61,
        0x6a,
        0x9d,
        0x30,
        0xc1,
        0x85,
        0x88,
        0xc6,
        0x29,
        0x1d,
        0x59,
        0xf0,
        0x8a,
        0xe6,
        0x94,
        0x5f,
        0x51,
        0x85,
        0x3a,
        0x78,
        0x2f,
        0x38,
        0xb1,
        0xa8,
        0xd5,
        0xf6,
        0xc7,
        0x3a,
        0x9e,
        0x04,
        0xe2,
        0x82,
        0x94,
        0x87,
        0xf8,
        //3rd part: mac
        0x0A,
        0x11,
        0x7C,
        0x70,
        0x80,
        0x22,
        0xE9,
        0x77,
        0xFA,
        0x78,
        0xA0,
        0x11,
        0x0B,
        0xE2,
        0x57,
        0xF1,
        0x5F,
        0xB7,
        0x47,
        0x3A,
        0x15,
        0x91,
        0x63,
        0x81,
        0x32,
        0x88,
        0x54,
        0x56,
        0x6E,
        0xE3,
        0x29,
        0xB6,
        0x91,
        0x5F,
        0xD9,
        0x5C,
        0xD6,
        0xB8,
        0x86,
        0x55,
        0x56,
        0x6D,
        0x4A,
        0xF1,
        0x1F,
        0x9B,
        0x34,
        0x56,
        0xC3,
        0xD4,
        0x5A,
        0x60,
        0x4B,
        0xE5,
        0x84,
        0x6C,
        0x87,
        0xB9,
        0xD8,
        0x23,
        0x1C,
        0x97,
        0xE1,
        0xBE,
    };
        #endif

    unsigned char std_cipher_part2_part3_with_s1[] = {
        //2nd part: cihpher
        0xa1,
        0x73,
        0x39,
        0x81,
        0x76,
        0x00,
        0x8a,
        0x85,
        0x7e,
        0x36,
        0xe6,
        0xfd,
        0xee,
        0x1f,
        0x14,
        0x79,
        0x38,
        0x9a,
        0x0a,
        0x61,
        0x69,
        0xfa,
        0xf9,
        0xe5,
        0x30,
        0x03,
        0x57,
        0x9f,
        0xe9,
        0xc4,
        0x44,
        0x11,
        0x6d,
        0x6e,
        0x3e,
        0x4d,
        0x0c,
        0x5d,
        0x5d,
        0x1f,
        0xe1,
        0x85,
        0x63,
        //3rd part: mac
        0x2C,
        0x17,
        0x63,
        0x64,
        0x2A,
        0x61,
        0x73,
        0x57,
        0x21,
        0x4D,
        0xD1,
        0x72,
        0x23,
        0xB5,
        0xAC,
        0xC0,
        0xAF,
        0x46,
        0x72,
        0xDF,
        0x04,
        0x56,
        0x43,
        0x44,
        0xBA,
        0x2E,
        0x00,
        0xFE,
        0x9D,
        0x1D,
        0xBA,
        0x31,
        0x8E,
        0x48,
        0x24,
        0x29,
        0xD4,
        0x51,
        0xA8,
        0xEF,
        0xC2,
        0x2C,
        0x53,
        0x7B,
        0xC1,
        0x45,
        0x84,
        0x37,
        0x7B,
        0x99,
        0xF2,
        0xE0,
        0xF3,
        0xE8,
        0x51,
        0x6A,
        0xC2,
        0x83,
        0x1C,
        0xD9,
        0x31,
        0x4B,
        0xE0,
        0x38,
    };
    unsigned char std_cipher_part2_part3_with_s2[] = {
        //2nd part: cihpher
        0xa8,
        0xe5,
        0xed,
        0x47,
        0x43,
        0xac,
        0x3f,
        0x13,
        0x61,
        0x6a,
        0x9d,
        0x30,
        0xc1,
        0x85,
        0x88,
        0xc6,
        0x29,
        0x1d,
        0x59,
        0xf0,
        0x8a,
        0xe6,
        0x94,
        0x5f,
        0x51,
        0x85,
        0x3a,
        0x78,
        0x2f,
        0x38,
        0xb1,
        0xa8,
        0xd5,
        0xf6,
        0xc7,
        0x3a,
        0x9e,
        0x04,
        0xe2,
        0x82,
        0x94,
        0x87,
        0xf8,
        //3rd part: mac
        0xB1,
        0xDD,
        0xE7,
        0xF7,
        0x4B,
        0x15,
        0x1C,
        0x84,
        0x4E,
        0x8B,
        0x55,
        0x08,
        0xF0,
        0x45,
        0xAC,
        0x5F,
        0xEC,
        0xE8,
        0x1D,
        0xA6,
        0x20,
        0x59,
        0xC8,
        0x8E,
        0xA8,
        0x10,
        0x6A,
        0xFE,
        0x86,
        0x01,
        0x6D,
        0x50,
        0x43,
        0x6A,
        0xA6,
        0xE9,
        0x4A,
        0x42,
        0xFF,
        0xA5,
        0xF4,
        0x49,
        0x3B,
        0x4F,
        0x87,
        0xB7,
        0x27,
        0x69,
        0x24,
        0x9C,
        0x40,
        0x71,
        0xF5,
        0xE1,
        0x11,
        0xAF,
        0x81,
        0x89,
        0x61,
        0x7A,
        0xEC,
        0xFE,
        0x7C,
        0x63,
    };
    unsigned char std_cipher_part2_part3_with_s1_s2[] = {
        //2nd part: cihpher
        0xa1,
        0x73,
        0x39,
        0x81,
        0x76,
        0x00,
        0x8a,
        0x85,
        0x7e,
        0x36,
        0xe6,
        0xfd,
        0xee,
        0x1f,
        0x14,
        0x79,
        0x38,
        0x9a,
        0x0a,
        0x61,
        0x69,
        0xfa,
        0xf9,
        0xe5,
        0x30,
        0x03,
        0x57,
        0x9f,
        0xe9,
        0xc4,
        0x44,
        0x11,
        0x6d,
        0x6e,
        0x3e,
        0x4d,
        0x0c,
        0x5d,
        0x5d,
        0x1f,
        0xe1,
        0x85,
        0x63,
        //3rd part: mac
        0x3C,
        0x31,
        0xBB,
        0x3D,
        0x2F,
        0x2B,
        0x45,
        0x9B,
        0x00,
        0x5D,
        0x61,
        0xE2,
        0xD9,
        0xBB,
        0xAF,
        0xF8,
        0x7E,
        0x0E,
        0x67,
        0x61,
        0xBB,
        0x68,
        0xB8,
        0x50,
        0x0B,
        0xAD,
        0x34,
        0x05,
        0x9C,
        0x35,
        0xD0,
        0x85,
        0x0E,
        0xE6,
        0x8C,
        0x6C,
        0x51,
        0xFD,
        0x62,
        0xF4,
        0x51,
        0xF8,
        0x7A,
        0xDA,
        0xA2,
        0x1C,
        0x5C,
        0x4C,
        0xE5,
        0xEF,
        0x14,
        0xD2,
        0xF9,
        0xE6,
        0x1E,
        0x56,
        0x5E,
        0x0E,
        0x32,
        0xD5,
        0x28,
        0xFD,
        0xD1,
        0xDD,
    };

    ECIES_STD_TEST_VECTOR vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)anders_1024_1;
    char         *curve_name = "anders_1024_1";

    unsigned int ret;

    vector->curve                            = curve;
    vector->curve_name                       = curve_name;
    vector->msg                              = msg;
    vector->msg_bytes                        = msg_bytes;
    vector->shared_info1                     = shared_info1;
    vector->shared_info1_bytes               = shared_info1_bytes;
    vector->shared_info2                     = shared_info2;
    vector->shared_info2_bytes               = shared_info2_bytes;
    vector->receiver_pri_key                 = receiver_pri_key;
    vector->receiver_pub_key                 = receiver_pub_key;
    vector->point_form                       = POINT_UNCOMPRESSED;
    vector->sender_tmp_pri_key               = sender_tmp_pri_key;
    vector->kdf_hash_alg                     = kdf_hash_alg;
    vector->mac_hash_alg                     = mac_hash_alg;
    vector->mac_k_bytes                      = mac_key_bytes;
    vector->cipher_part1                     = std_cipher_uncompressed_without_s1_s2;
    vector->cipher_part2_part3_without_s1_s2 = std_cipher_uncompressed_without_s1_s2 + 1 + 2 * GET_BYTE_LEN(curve->eccp_p_bitLen);
    vector->cipher_part2_part3_with_s1       = std_cipher_part2_part3_with_s1;
    vector->cipher_part2_part3_with_s2       = std_cipher_part2_part3_with_s2;
    vector->cipher_part2_part3_with_s1_s2    = std_cipher_part2_part3_with_s1_s2;

    ret = ecies_std_test(vector);
    if (ret) {
        return ret;
    }

        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    vector->point_form   = POINT_COMPRESSED;
    vector->cipher_part1 = std_cipher_compressed_without_s1_s2;
    ret                  = ecies_std_test(vector);
    if (ret) {
        return ret;
    }
        #endif

    return ret;
}
    #endif

    #ifdef SUPPORT_HASH_SHA512_256
unsigned int ecies_rand_test(eccp_curve_t *curve, char *curve_name)
{
    unsigned char  receiver_pri_key[ECCP_MAX_BYTE_LEN];
    unsigned char  receiver_pub_key[2 * ECCP_MAX_BYTE_LEN];
    unsigned char  sender_tmp_pri_key_buf[ECCP_MAX_BYTE_LEN];
    unsigned char *sender_tmp_pri_key;

    unsigned char msg[200];
    unsigned int  msg_bytes;
    unsigned char shared_info1[200];
    unsigned int  shared_info1_bytes;
    unsigned char shared_info2[200];
    unsigned int  shared_info2_bytes;

    EC_POINT_FORM point_form = POINT_UNCOMPRESSED;
    HASH_ALG      kdf_hash_alg;
    HASH_ALG      mac_hash_alg;

    unsigned int  mac_k_bytes;
    unsigned char cipher[500];
    unsigned int  cipher_bytes;
    unsigned char replain[200];
    unsigned int  replain_bytes;

    unsigned int i, j, pByteLen, nByteLen;
    unsigned int ret;

    pByteLen = GET_BYTE_LEN(curve->eccp_p_bitLen);
    nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);

    printf("\r\n\r\n -------------- %s ECIES rand test --------------", curve_name);

    for (i = 0; i < ECIES_ENC_DEC_ROUND1; i++) {
        ret = get_rand(cipher, 8);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 1, ret = %02x", ret);
            return 1;
        }

        //set rand msg
        msg_bytes = cipher[0] % (sizeof(msg));
        msg_bytes += 1;
        ret = get_rand(msg, msg_bytes);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 2, ret = %02x", ret);
            return 1;
        }

        //set rand shared_info1
        shared_info1_bytes = cipher[1] % (sizeof(shared_info1));
        ret                = get_rand(shared_info1, shared_info1_bytes);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 3, ret = %02x", ret);
            return 1;
        }

        //set rand shared_info2
        shared_info2_bytes = cipher[2] % (sizeof(shared_info2));
        ret                = get_rand(shared_info2, shared_info2_bytes);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 4, ret = %02x", ret);
            return 1;
        }

        //set sender_tmp_pri_key
        if (cipher[3] & 1) {
            sender_tmp_pri_key = NULL;
        } else {
            sender_tmp_pri_key = sender_tmp_pri_key_buf;
            ret                = get_rand(sender_tmp_pri_key, nByteLen);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get rand error 5, ret = %02x", ret);
                return 1;
            }
            sender_tmp_pri_key[0] = 0;
        }

            //set point form
        #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
        if (cipher[3] & 1) {
            point_form = POINT_COMPRESSED;
        }
        #endif

        //set rand kdf_hash_alg and mac_hash_alg;
        kdf_hash_alg = (HASH_ALG)(cipher[4] % (((uint32_t)HASH_SHA512_256) + 1));
        mac_hash_alg = (HASH_ALG)(cipher[5] % (((uint32_t)HASH_SHA512_256) + 1));

        //set rand mac_k_bytes;
        mac_k_bytes = cipher[6] % ECIES_MAC_KEY_MAX_BYTE_LEN;
        mac_k_bytes += 1;
        if (mac_k_bytes < ECIES_MAC_KEY_ANSI_X963_MIN_BYTE_LEN) {
            mac_k_bytes = ECIES_MAC_KEY_ANSI_X963_MIN_BYTE_LEN;
        }

        //get random key pair
        ret = eccp_getkey(curve, receiver_pri_key, receiver_pub_key);
        if (PKE_SUCCESS != ret) {
            printf("\r\n %s ECIES get key error, ret = %02x", curve_name, ret);
            return 1;
        }

        printf("\r\n\r\n point_form=%u, kdf_hash_alg=%u, mac_hash_alg=%u, mac_k_bytes=%u", point_form, (unsigned int)kdf_hash_alg, (unsigned int)mac_hash_alg, mac_k_bytes);

        for (j = 0; j < 50; j++) {
            printf("\r\n %s ECIES round1=%u, round2=%u", curve_name, i + 1, j + 1);

            ret = ansi_x963_2001_ecies_encrypt(curve, msg, msg_bytes, shared_info1, shared_info1_bytes, shared_info2, shared_info2_bytes, sender_tmp_pri_key, receiver_pub_key, point_form, kdf_hash_alg, mac_hash_alg, mac_k_bytes, cipher, &cipher_bytes);
            if (ECIES_SUCCESS != ret) {
                printf("\r\n %s ECIES enc error, ret = %02x", curve_name, ret);
                print_buf_U8(receiver_pri_key, nByteLen, "receiver_pri_key");
                print_buf_U8(receiver_pub_key, pByteLen * 2, "receiver_pub_key");
                if (sender_tmp_pri_key) {
                    print_buf_U8(sender_tmp_pri_key, nByteLen, "sender_tmp_pri_key");
                }
                print_buf_U8(msg, msg_bytes, "msg");
                print_buf_U8(shared_info1, shared_info1_bytes, "shared_info1");
                print_buf_U8(shared_info2, shared_info2_bytes, "shared_info2");
                print_buf_U8(cipher, cipher_bytes, "cipher");

                return 1;
            }

            ret = ansi_x963_2001_ecies_decrypt(curve, cipher, cipher_bytes, receiver_pri_key, shared_info1, shared_info1_bytes, shared_info2, shared_info2_bytes, kdf_hash_alg, mac_hash_alg, mac_k_bytes, replain, &replain_bytes);
            if ((ECIES_SUCCESS != ret) || (msg_bytes != replain_bytes) || (memcmp_(replain, msg, msg_bytes))) {
                printf("\r\n %s ECIES enc error, ret = %02x", curve_name, ret);
                print_buf_U8(receiver_pri_key, nByteLen, "receiver_pri_key");
                print_buf_U8(receiver_pub_key, pByteLen * 2, "receiver_pub_key");
                if (sender_tmp_pri_key) {
                    print_buf_U8(sender_tmp_pri_key, nByteLen, "sender_tmp_pri_key");
                }
                print_buf_U8(cipher, cipher_bytes, "cipher");
                print_buf_U8(shared_info1, shared_info1_bytes, "shared_info1");
                print_buf_U8(shared_info2, shared_info2_bytes, "shared_info2");
                print_buf_U8(replain, replain_bytes, "replain");
                print_buf_U8(msg, msg_bytes, "source msg");

                return 1;
            }
        }
    }

    return 0;
}
    #endif

unsigned int ecies_speed_test(eccp_curve_t *curve, char *curve_name)
{
    unsigned char receiver_pri_key[ECCP_MAX_BYTE_LEN];
    unsigned char receiver_pub_key[2 * ECCP_MAX_BYTE_LEN];

    HASH_ALG       kdf_hash_alg = HASH_SHA256;
    HASH_ALG       mac_hash_alg = HASH_SHA256;
    unsigned int   mac_k_bytes  = 32;
    unsigned char *msg          = msg_s;
    unsigned int   msg_bytes    = sizeof(msg_s);

    unsigned char cipher[500];
    unsigned char replain[500];
    unsigned int  cipher_bytes;
    unsigned int  replain_bytes;

    EC_POINT_FORM point_form = POINT_UNCOMPRESSED;

    char *point_form_info1 = "uncompress point";
    #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    char *point_form_info2 = "compress point";
    #endif
    char *point_form_info = point_form_info1;

    unsigned int i;
    unsigned int round = 0;
    unsigned int ret;

    if (curve->eccp_p_bitLen <= 160) {
        round = 600;
    } else if (curve->eccp_p_bitLen <= 192) {
        round = 500;
    } else if (curve->eccp_p_bitLen <= 224) {
        round = 400;
    } else if (curve->eccp_p_bitLen <= 256) {
        round = 300;
    } else if (curve->eccp_p_bitLen <= 384) {
        round = 80;
    } else if (curve->eccp_p_bitLen <= 521) {
        round = 40;
    } else if (curve->eccp_p_bitLen <= 638) {
        round = 20;
    } else if (curve->eccp_p_bitLen <= 1024) {
        round = 10;
    }

    #ifdef ECIES_SUPPORT_EC_POINT_COMPRESSED
    point_form      = POINT_UNCOMPRESSED;
    point_form_info = point_form_info2;
    #endif


    printf("\r\n\r\n =========== ecies curve = %s encrypt begin (%s) ============== ", curve_name, point_form_info);
    fflush(stdout);

    //get key
    ret = eccp_getkey(curve, receiver_pri_key, receiver_pub_key);
    if (PKE_SUCCESS != ret) {
        printf("\r\n ECIES get key error, ret = %02x", ret);
        return 1;
    }

    uint32_sleep(0x1FFFF, 1);

    #ifdef ECIES_SPEED_TEST_BY_TIMER
    round /= 10;
    startP();
    #endif

    ret = 0;
    for (i = 0; i < round; i++) {
        ret = ansi_x963_2001_ecies_encrypt(curve, msg, msg_bytes, NULL, 0, NULL, 0, NULL, receiver_pub_key, point_form, kdf_hash_alg, mac_hash_alg, mac_k_bytes, cipher, &cipher_bytes);
    }

    #ifdef ECIES_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("finished round = %d \r\n", round);
    fflush(stdout);
    #endif

    if (ECIES_SUCCESS != ret) {
        printf("ecies encry error, ret = %02x \r\n", ret);
        print_buf_U8(cipher, cipher_bytes, "cipher");
        return 1;
    }

    uint32_sleep(0x1FFFF, 1);


    printf("\r\n\r\n =========== ecies curve = %s decrypt begin (%s) ============== ", curve_name, point_form_info);
    fflush(stdout);

    #ifdef ECIES_SPEED_TEST_BY_TIMER
    startP();
    #endif

    ret = 0;
    for (i = 0; i < round; i++) {
        ret |= ansi_x963_2001_ecies_decrypt(curve, cipher, cipher_bytes, receiver_pri_key, NULL, 0, NULL, 0, kdf_hash_alg, mac_hash_alg, mac_k_bytes, replain, &replain_bytes);
    }

    #ifdef ECIES_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("finished round = %d \r\n", round);
    fflush(stdout);
    #endif

    if ((ECIES_SUCCESS != ret) || memcmp_(replain, msg, replain_bytes) != 0) {
        printf("ecies encrypt/decrypt error, ret = %02x \r\n", ret);
        print_buf_U8(replain, replain_bytes, "replain");
        return 1;
    }

    return 0;
}

unsigned int ECIES_all_speed_test(void)
{
    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecies_speed_test(secp160k1, "secp160k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecies_speed_test(secp192k1, "secp192k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecies_speed_test(secp224k1, "secp224k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecies_speed_test(secp256k1, "secp256k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecies_speed_test(secp160r1, "secp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecies_speed_test(secp160r2, "secp160r2")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecies_speed_test(secp192r1, "secp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecies_speed_test(secp224r1, "secp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecies_speed_test(secp256r1, "secp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecies_speed_test(secp384r1, "secp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecies_speed_test(secp521r1, "secp521r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecies_speed_test(brainpoolp160r1, "brainpoolp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_BRAINPOOLP192R1))
    if (ecies_speed_test(brainpoolp192r1, "brainpoolp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_BRAINPOOLP224R1))
    if (ecies_speed_test(brainpoolp224r1, "brainpoolp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecies_speed_test(brainpoolp256r1, "brainpoolp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 320) && defined(SUPPORT_BRAINPOOLP320R1))
    if (ecies_speed_test(brainpoolp320r1, "brainpoolp320r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_BRAINPOOLP384R1))
    if (ecies_speed_test(brainpoolp384r1, "brainpoolp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecies_speed_test(brainpoolp512r1, "brainpoolp512r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BN256))
    if (ecies_speed_test(bn256, "bn256")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 638) && defined(SUPPORT_BN638))
    if (ecies_speed_test(bn638, "bn638")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecies_speed_test(anders_1024_1, "anders_1024_1")) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int ECIES_all_std_test(void)
{
    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecies_std_test_secp160k1()) {
        return 1;
    }
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecies_std_test_secp192k1()) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecies_std_test_secp224k1()) {
        return 1;
    }
        #endif
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecies_std_test_secp256k1()) {
        return 1;
    }
        #endif
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecies_std_test_secp160r1()) {
        return 1;
    }
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecies_std_test_secp160r2()) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecies_std_test_secp192r1()) {
        return 1;
    }
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecies_std_test_secp224r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecies_std_test_secp256r1()) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecies_std_test_secp384r1()) {
        return 1;
    }
        #endif
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecies_std_test_secp521r1()) {
        return 1;
    }
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecies_std_test_brainpoolp160r1()) {
        return 1;
    }
    #endif

    #ifdef SUPPORT_HASH_SHA512
        #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecies_std_test_brainpoolp512r1()) {
        return 1;
    }
        #endif
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecies_std_test_anders_1024_1()) {
        return 1;
    }
    #endif

    return 0;
}

    #ifdef SUPPORT_HASH_SHA512_256
unsigned int ECIES_all_rand_test(void)
{
        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecies_rand_test(secp160k1, "secp160k1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecies_rand_test(secp192k1, "secp192k1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecies_rand_test(secp224k1, "secp224k1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecies_rand_test(secp256k1, "secp256k1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecies_rand_test(secp160r1, "secp160r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecies_rand_test(secp160r2, "secp160r2")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecies_rand_test(secp192r1, "secp192r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecies_rand_test(secp224r1, "secp224r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecies_rand_test(secp256r1, "secp256r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecies_rand_test(secp384r1, "secp384r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecies_rand_test(secp521r1, "secp521r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecies_rand_test(brainpoolp160r1, "brainpoolp160r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_BRAINPOOLP192R1))
    if (ecies_rand_test(brainpoolp192r1, "brainpoolp192r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_BRAINPOOLP224R1))
    if (ecies_rand_test(brainpoolp224r1, "brainpoolp224r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecies_rand_test(brainpoolp256r1, "brainpoolp256r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 320) && defined(SUPPORT_BRAINPOOLP320R1))
    if (ecies_rand_test(brainpoolp320r1, "brainpoolp320r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_BRAINPOOLP384R1))
    if (ecies_rand_test(brainpoolp384r1, "brainpoolp384r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecies_rand_test(brainpoolp512r1, "brainpoolp512r1")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BN256))
    if (ecies_rand_test(bn256, "BN256")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 638) && defined(SUPPORT_BN638))
    if (ecies_rand_test(bn638, "BN638")) {
        return 1;
    }
        #endif

        #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecies_rand_test(anders_1024_1, "anders_1024_1")) {
        return 1;
    }
        #endif

    return 0;
}
    #endif

unsigned int ECIES_all_test(void)
{
    unsigned int ret;

    #if 0
    ret = ECIES_all_speed_test();
    if(ret)
        return 1;
    #endif

    ret = ECIES_all_std_test();
    if (ret) {
        return 1;
    }

    #ifdef SUPPORT_HASH_SHA512_256
    ret = ECIES_all_rand_test();
    if (ret) {
        return 1;
    }
    #endif
    return 0;
}

#endif

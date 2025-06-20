/********************************************************************************************************
 * @file    ed25519_test.c
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


#ifdef SUPPORT_C25519

    #include "lib/include/pke/ed25519.h"
    #include "lib/include/crypto_common/utility.h"
    #include "lib/include/trng/trng.h"
    #include "lib/include/hash/hash.h"

//#define ED25519_SPEED_TEST_BY_TIMER

    #ifdef ED25519_SPEED_TEST_BY_TIMER
extern unsigned int startP(void);
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
    #endif

extern void x25519_decode_scalar(unsigned char *k, unsigned char *out, unsigned int bytes);

    #define Ed25519_SIGN_VERIFY_ROUND1 (2)

unsigned int ed25519_sign_verify_test_internal(Ed25519_MODE mode, unsigned char std_prikey[32], unsigned char std_pubkey[32], unsigned char ctx[], unsigned char ctxByteLen, unsigned char M[], unsigned int MByteLen, unsigned char std_RS[64], unsigned char index, unsigned char print_choice)

{
    unsigned char pubkey[32];
    unsigned char RS[64], RS2[64];
    unsigned char sha512_digest[64];
    char         *mode_name[4] = {"DEFAULT", "CTX", "PH", "PH_WITH_PH_M"};
    unsigned int  ret;

    //get public key
    ret = ed25519_get_pubkey_from_prikey(std_prikey, pubkey);
    if ((EdDSA_SUCCESS != ret) || ((std_pubkey != NULL) && memcmp(pubkey, std_pubkey, 32))) {
        printf("\r\n Ed25519 %s mode test %u get key error, ret = %x", mode_name[mode], index, ret);
        print_buf_U8((unsigned char *)pubkey, 32, "pubkey");
        return 1;
    }

    //sign
    ret = ed25519_sign(mode, std_prikey, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        if (NULL != std_RS) {
            if (0 == memcmp_(RS, std_RS, 64)) {
                if (print_choice) {
                    printf("\r\n Ed25519 %s mode test %u sign success", mode_name[mode], index);
                    fflush(stdout);
                }
            } else {
                printf("\r\n Ed25519 %s mode test %u sign error, ret = %x", mode_name[mode], index, ret);
                fflush(stdout);
                print_buf_U8((unsigned char *)RS, 64, "RS");
                return 1;
            }
        } else {
            if (print_choice) {
                printf("\r\n Ed25519 %s mode test %u sign success", mode_name[mode], index);
                fflush(stdout);
            }
        }
    } else {
        printf("\r\n Ed25519 %s mode test %u sign error, ret = %x", mode_name[mode], index, ret);
        fflush(stdout);
        print_buf_U8((unsigned char *)RS, 64, "RS");
        return 1;
    }

    if (Ed25519_PH == mode) {
        ret = hash(HASH_SHA512, M, MByteLen, sha512_digest);
        if (HASH_SUCCESS != ret) {
            printf("\r\n sha512 error, ret = %x", ret);
            fflush(stdout);
            return 1;
        } else {
            ;
        }

        ret = ed25519_sign(Ed25519_PH_WITH_PH_M, std_prikey, pubkey, ctx, ctxByteLen, sha512_digest, 64, RS2);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n Ed25519 test %u sign error(Ed25519_PH), ret = %x", index, ret);
            fflush(stdout);
            print_buf_U8((unsigned char *)RS2, 64, "RS");
            return 1;
        } else {
            ;
        }

        if (memcmp_(RS, RS2, 64)) {
            printf("\r\n Ed25519 test %u sign error(Ed25519_PH), ret = %x", index, ret);
            fflush(stdout);
            print_buf_U8((unsigned char *)RS2, 64, "RS");
            return 1;
        }
    }

    //verify
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        if (print_choice) {
            printf("  verify success");
            fflush(stdout);
        }
    } else {
        printf("  verify fail, ret = %x", ret);
        fflush(stdout);
        return 1;
    }

    if (Ed25519_PH == mode) {
        ret = ed25519_verify(Ed25519_PH_WITH_PH_M, pubkey, ctx, ctxByteLen, sha512_digest, 64, RS2);
        if (EdDSA_SUCCESS != ret) {
            printf("  verify fail(PH_WITH_PH_M), ret = %x", ret);
            fflush(stdout);
            return 1;
        }
    }

    //*
    //invalid mode
    mode = (Ed25519_MODE)(((unsigned int)mode + 1) % 4);
    ret  = ed25519_verify((Ed25519_MODE)mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 1, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    mode = (Ed25519_MODE)(((unsigned int)mode + 2) % 4);

    //invalid pubkey 1
    pubkey[31] ^= 0x80;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 2, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    pubkey[31] ^= 0x80;

    //invalid pubkey 2
    pubkey[1] += 1;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 3, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    pubkey[1] -= 1;

    //invalid ctx
    if (Ed25519_DEFAULT != mode) {
        ret = ed25519_verify(mode, pubkey, pubkey, ctxByteLen + 2, M, MByteLen, RS);
        if (EdDSA_SUCCESS == ret) {
            printf("\r\n  verify fail 4, ret = %x", ret);
            fflush(stdout);
            return 1;
        }
    }

    //invalid message
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, pubkey, MByteLen + 1, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 5, ret = %x", ret);
        fflush(stdout);
        return 1;
    }

    //invalid signature 1
    RS[31] ^= 0x80;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 6, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    RS[31] ^= 0x80;

    //invalid signature 2
    RS[1] += 1;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 6, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    RS[1] -= 1;

    //invalid signature 3
    RS[63] |= 0x80;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 6, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    RS[63] ^= 0x80;

    //invalid signature 4
    RS[32] += 1;
    ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
    if (EdDSA_SUCCESS == ret) {
        printf("\r\n  verify fail 6, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
    RS[32] -= 1;
    //*/

    return 0;
}

unsigned int ed25519_default_mode_std_test(void)
{
    //test 1
    unsigned char prikey1[32] = {
        0x9D,
        0x61,
        0xB1,
        0x9D,
        0xEF,
        0xFD,
        0x5A,
        0x60,
        0xBA,
        0x84,
        0x4A,
        0xF4,
        0x92,
        0xEC,
        0x2C,
        0xC4,
        0x44,
        0x49,
        0xC5,
        0x69,
        0x7B,
        0x32,
        0x69,
        0x19,
        0x70,
        0x3B,
        0xAC,
        0x03,
        0x1C,
        0xAE,
        0x7F,
        0x60};
    unsigned char pubkey1[32] = {
        0xD7,
        0x5A,
        0x98,
        0x01,
        0x82,
        0xB1,
        0x0A,
        0xB7,
        0xD5,
        0x4B,
        0xFE,
        0xD3,
        0xC9,
        0x64,
        0x07,
        0x3A,
        0x0E,
        0xE1,
        0x72,
        0xF3,
        0xDA,
        0xA6,
        0x23,
        0x25,
        0xAF,
        0x02,
        0x1A,
        0x68,
        0xF7,
        0x07,
        0x51,
        0x1A};
    //no message
    unsigned char RS1[64] = {
        0xE5,
        0x56,
        0x43,
        0x00,
        0xC3,
        0x60,
        0xAC,
        0x72,
        0x90,
        0x86,
        0xE2,
        0xCC,
        0x80,
        0x6E,
        0x82,
        0x8A,
        0x84,
        0x87,
        0x7F,
        0x1E,
        0xB8,
        0xE5,
        0xD9,
        0x74,
        0xD8,
        0x73,
        0xE0,
        0x65,
        0x22,
        0x49,
        0x01,
        0x55,
        0x5F,
        0xB8,
        0x82,
        0x15,
        0x90,
        0xA3,
        0x3B,
        0xAC,
        0xC6,
        0x1E,
        0x39,
        0x70,
        0x1C,
        0xF9,
        0xB4,
        0x6B,
        0xD2,
        0x5B,
        0xF5,
        0xF0,
        0x59,
        0x5B,
        0xBE,
        0x24,
        0x65,
        0x51,
        0x41,
        0x43,
        0x8E,
        0x7A,
        0x10,
        0x0B};

    //test 2
    unsigned char prikey2[32] = {
        0x4C,
        0xCD,
        0x08,
        0x9B,
        0x28,
        0xFF,
        0x96,
        0xDA,
        0x9D,
        0xB6,
        0xC3,
        0x46,
        0xEC,
        0x11,
        0x4E,
        0x0F,
        0x5B,
        0x8A,
        0x31,
        0x9F,
        0x35,
        0xAB,
        0xA6,
        0x24,
        0xDA,
        0x8C,
        0xF6,
        0xED,
        0x4F,
        0xB8,
        0xA6,
        0xFB};
    //    unsigned char  pubkey2[32]={
    //        0x3D,0x40,0x17,0xC3,0xE8,0x43,0x89,0x5A,0x92,0xB7,0x0A,0xA7,0x4D,0x1B,0x7E,0xBC,
    //        0x9C,0x98,0x2C,0xCF,0x2E,0xC4,0x96,0x8C,0xC0,0xCD,0x55,0xF1,0x2A,0xF4,0x66,0x0C
    //    };
    unsigned char M2[1]   = {0x72};
    unsigned char RS2[64] = {
        0x92,
        0xA0,
        0x09,
        0xA9,
        0xF0,
        0xD4,
        0xCA,
        0xB8,
        0x72,
        0x0E,
        0x82,
        0x0B,
        0x5F,
        0x64,
        0x25,
        0x40,
        0xA2,
        0xB2,
        0x7B,
        0x54,
        0x16,
        0x50,
        0x3F,
        0x8F,
        0xB3,
        0x76,
        0x22,
        0x23,
        0xEB,
        0xDB,
        0x69,
        0xDA,
        0x08,
        0x5A,
        0xC1,
        0xE4,
        0x3E,
        0x15,
        0x99,
        0x6E,
        0x45,
        0x8F,
        0x36,
        0x13,
        0xD0,
        0xF1,
        0x1D,
        0x8C,
        0x38,
        0x7B,
        0x2E,
        0xAE,
        0xB4,
        0x30,
        0x2A,
        0xEE,
        0xB0,
        0x0D,
        0x29,
        0x16,
        0x12,
        0xBB,
        0x0C,
        0x00};

    //test 3
    unsigned char prikey3[32] = {
        0xC5,
        0xAA,
        0x8D,
        0xF4,
        0x3F,
        0x9F,
        0x83,
        0x7B,
        0xED,
        0xB7,
        0x44,
        0x2F,
        0x31,
        0xDC,
        0xB7,
        0xB1,
        0x66,
        0xD3,
        0x85,
        0x35,
        0x07,
        0x6F,
        0x09,
        0x4B,
        0x85,
        0xCE,
        0x3A,
        0x2E,
        0x0B,
        0x44,
        0x58,
        0xF7};
    unsigned char pubkey3[32] = {
        0xFC,
        0x51,
        0xCD,
        0x8E,
        0x62,
        0x18,
        0xA1,
        0xA3,
        0x8D,
        0xA4,
        0x7E,
        0xD0,
        0x02,
        0x30,
        0xF0,
        0x58,
        0x08,
        0x16,
        0xED,
        0x13,
        0xBA,
        0x33,
        0x03,
        0xAC,
        0x5D,
        0xEB,
        0x91,
        0x15,
        0x48,
        0x90,
        0x80,
        0x25};
    unsigned char M3[2]   = {0xaf, 0x82};
    unsigned char RS3[64] = {
        0x62,
        0x91,
        0xD6,
        0x57,
        0xDE,
        0xEC,
        0x24,
        0x02,
        0x48,
        0x27,
        0xE6,
        0x9C,
        0x3A,
        0xBE,
        0x01,
        0xA3,
        0x0C,
        0xE5,
        0x48,
        0xA2,
        0x84,
        0x74,
        0x3A,
        0x44,
        0x5E,
        0x36,
        0x80,
        0xD7,
        0xDB,
        0x5A,
        0xC3,
        0xAC,
        0x18,
        0xFF,
        0x9B,
        0x53,
        0x8D,
        0x16,
        0xF2,
        0x90,
        0xAE,
        0x67,
        0xF7,
        0x60,
        0x98,
        0x4D,
        0xC6,
        0x59,
        0x4A,
        0x7C,
        0x15,
        0xE9,
        0x71,
        0x6E,
        0xD2,
        0x8D,
        0xC0,
        0x27,
        0xBE,
        0xCE,
        0xEA,
        0x1E,
        0xC4,
        0x0A};

    //test 4
    unsigned char prikey4[32] = {
        0xF5,
        0xE5,
        0x76,
        0x7C,
        0xF1,
        0x53,
        0x31,
        0x95,
        0x17,
        0x63,
        0x0F,
        0x22,
        0x68,
        0x76,
        0xB8,
        0x6C,
        0x81,
        0x60,
        0xCC,
        0x58,
        0x3B,
        0xC0,
        0x13,
        0x74,
        0x4C,
        0x6B,
        0xF2,
        0x55,
        0xF5,
        0xCC,
        0x0E,
        0xE5};
    unsigned char pubkey4[32] = {
        0x27,
        0x81,
        0x17,
        0xFC,
        0x14,
        0x4C,
        0x72,
        0x34,
        0x0F,
        0x67,
        0xD0,
        0xF2,
        0x31,
        0x6E,
        0x83,
        0x86,
        0xCE,
        0xFF,
        0xBF,
        0x2B,
        0x24,
        0x28,
        0xC9,
        0xC5,
        0x1F,
        0xEF,
        0x7C,
        0x59,
        0x7F,
        0x1D,
        0x42,
        0x6E};
    unsigned char M4[1023] = {
        0x08,
        0xB8,
        0xB2,
        0xB7,
        0x33,
        0x42,
        0x42,
        0x43,
        0x76,
        0x0F,
        0xE4,
        0x26,
        0xA4,
        0xB5,
        0x49,
        0x08,
        0x63,
        0x21,
        0x10,
        0xA6,
        0x6C,
        0x2F,
        0x65,
        0x91,
        0xEA,
        0xBD,
        0x33,
        0x45,
        0xE3,
        0xE4,
        0xEB,
        0x98,
        0xFA,
        0x6E,
        0x26,
        0x4B,
        0xF0,
        0x9E,
        0xFE,
        0x12,
        0xEE,
        0x50,
        0xF8,
        0xF5,
        0x4E,
        0x9F,
        0x77,
        0xB1,
        0xE3,
        0x55,
        0xF6,
        0xC5,
        0x05,
        0x44,
        0xE2,
        0x3F,
        0xB1,
        0x43,
        0x3D,
        0xDF,
        0x73,
        0xBE,
        0x84,
        0xD8,
        0x79,
        0xDE,
        0x7C,
        0x00,
        0x46,
        0xDC,
        0x49,
        0x96,
        0xD9,
        0xE7,
        0x73,
        0xF4,
        0xBC,
        0x9E,
        0xFE,
        0x57,
        0x38,
        0x82,
        0x9A,
        0xDB,
        0x26,
        0xC8,
        0x1B,
        0x37,
        0xC9,
        0x3A,
        0x1B,
        0x27,
        0x0B,
        0x20,
        0x32,
        0x9D,
        0x65,
        0x86,
        0x75,
        0xFC,
        0x6E,
        0xA5,
        0x34,
        0xE0,
        0x81,
        0x0A,
        0x44,
        0x32,
        0x82,
        0x6B,
        0xF5,
        0x8C,
        0x94,
        0x1E,
        0xFB,
        0x65,
        0xD5,
        0x7A,
        0x33,
        0x8B,
        0xBD,
        0x2E,
        0x26,
        0x64,
        0x0F,
        0x89,
        0xFF,
        0xBC,
        0x1A,
        0x85,
        0x8E,
        0xFC,
        0xB8,
        0x55,
        0x0E,
        0xE3,
        0xA5,
        0xE1,
        0x99,
        0x8B,
        0xD1,
        0x77,
        0xE9,
        0x3A,
        0x73,
        0x63,
        0xC3,
        0x44,
        0xFE,
        0x6B,
        0x19,
        0x9E,
        0xE5,
        0xD0,
        0x2E,
        0x82,
        0xD5,
        0x22,
        0xC4,
        0xFE,
        0xBA,
        0x15,
        0x45,
        0x2F,
        0x80,
        0x28,
        0x8A,
        0x82,
        0x1A,
        0x57,
        0x91,
        0x16,
        0xEC,
        0x6D,
        0xAD,
        0x2B,
        0x3B,
        0x31,
        0x0D,
        0xA9,
        0x03,
        0x40,
        0x1A,
        0xA6,
        0x21,
        0x00,
        0xAB,
        0x5D,
        0x1A,
        0x36,
        0x55,
        0x3E,
        0x06,
        0x20,
        0x3B,
        0x33,
        0x89,
        0x0C,
        0xC9,
        0xB8,
        0x32,
        0xF7,
        0x9E,
        0xF8,
        0x05,
        0x60,
        0xCC,
        0xB9,
        0xA3,
        0x9C,
        0xE7,
        0x67,
        0x96,
        0x7E,
        0xD6,
        0x28,
        0xC6,
        0xAD,
        0x57,
        0x3C,
        0xB1,
        0x16,
        0xDB,
        0xEF,
        0xEF,
        0xD7,
        0x54,
        0x99,
        0xDA,
        0x96,
        0xBD,
        0x68,
        0xA8,
        0xA9,
        0x7B,
        0x92,
        0x8A,
        0x8B,
        0xBC,
        0x10,
        0x3B,
        0x66,
        0x21,
        0xFC,
        0xDE,
        0x2B,
        0xEC,
        0xA1,
        0x23,
        0x1D,
        0x20,
        0x6B,
        0xE6,
        0xCD,
        0x9E,
        0xC7,
        0xAF,
        0xF6,
        0xF6,
        0xC9,
        0x4F,
        0xCD,
        0x72,
        0x04,
        0xED,
        0x34,
        0x55,
        0xC6,
        0x8C,
        0x83,
        0xF4,
        0xA4,
        0x1D,
        0xA4,
        0xAF,
        0x2B,
        0x74,
        0xEF,
        0x5C,
        0x53,
        0xF1,
        0xD8,
        0xAC,
        0x70,
        0xBD,
        0xCB,
        0x7E,
        0xD1,
        0x85,
        0xCE,
        0x81,
        0xBD,
        0x84,
        0x35,
        0x9D,
        0x44,
        0x25,
        0x4D,
        0x95,
        0x62,
        0x9E,
        0x98,
        0x55,
        0xA9,
        0x4A,
        0x7C,
        0x19,
        0x58,
        0xD1,
        0xF8,
        0xAD,
        0xA5,
        0xD0,
        0x53,
        0x2E,
        0xD8,
        0xA5,
        0xAA,
        0x3F,
        0xB2,
        0xD1,
        0x7B,
        0xA7,
        0x0E,
        0xB6,
        0x24,
        0x8E,
        0x59,
        0x4E,
        0x1A,
        0x22,
        0x97,
        0xAC,
        0xBB,
        0xB3,
        0x9D,
        0x50,
        0x2F,
        0x1A,
        0x8C,
        0x6E,
        0xB6,
        0xF1,
        0xCE,
        0x22,
        0xB3,
        0xDE,
        0x1A,
        0x1F,
        0x40,
        0xCC,
        0x24,
        0x55,
        0x41,
        0x19,
        0xA8,
        0x31,
        0xA9,
        0xAA,
        0xD6,
        0x07,
        0x9C,
        0xAD,
        0x88,
        0x42,
        0x5D,
        0xE6,
        0xBD,
        0xE1,
        0xA9,
        0x18,
        0x7E,
        0xBB,
        0x60,
        0x92,
        0xCF,
        0x67,
        0xBF,
        0x2B,
        0x13,
        0xFD,
        0x65,
        0xF2,
        0x70,
        0x88,
        0xD7,
        0x8B,
        0x7E,
        0x88,
        0x3C,
        0x87,
        0x59,
        0xD2,
        0xC4,
        0xF5,
        0xC6,
        0x5A,
        0xDB,
        0x75,
        0x53,
        0x87,
        0x8A,
        0xD5,
        0x75,
        0xF9,
        0xFA,
        0xD8,
        0x78,
        0xE8,
        0x0A,
        0x0C,
        0x9B,
        0xA6,
        0x3B,
        0xCB,
        0xCC,
        0x27,
        0x32,
        0xE6,
        0x94,
        0x85,
        0xBB,
        0xC9,
        0xC9,
        0x0B,
        0xFB,
        0xD6,
        0x24,
        0x81,
        0xD9,
        0x08,
        0x9B,
        0xEC,
        0xCF,
        0x80,
        0xCF,
        0xE2,
        0xDF,
        0x16,
        0xA2,
        0xCF,
        0x65,
        0xBD,
        0x92,
        0xDD,
        0x59,
        0x7B,
        0x07,
        0x07,
        0xE0,
        0x91,
        0x7A,
        0xF4,
        0x8B,
        0xBB,
        0x75,
        0xFE,
        0xD4,
        0x13,
        0xD2,
        0x38,
        0xF5,
        0x55,
        0x5A,
        0x7A,
        0x56,
        0x9D,
        0x80,
        0xC3,
        0x41,
        0x4A,
        0x8D,
        0x08,
        0x59,
        0xDC,
        0x65,
        0xA4,
        0x61,
        0x28,
        0xBA,
        0xB2,
        0x7A,
        0xF8,
        0x7A,
        0x71,
        0x31,
        0x4F,
        0x31,
        0x8C,
        0x78,
        0x2B,
        0x23,
        0xEB,
        0xFE,
        0x80,
        0x8B,
        0x82,
        0xB0,
        0xCE,
        0x26,
        0x40,
        0x1D,
        0x2E,
        0x22,
        0xF0,
        0x4D,
        0x83,
        0xD1,
        0x25,
        0x5D,
        0xC5,
        0x1A,
        0xDD,
        0xD3,
        0xB7,
        0x5A,
        0x2B,
        0x1A,
        0xE0,
        0x78,
        0x45,
        0x04,
        0xDF,
        0x54,
        0x3A,
        0xF8,
        0x96,
        0x9B,
        0xE3,
        0xEA,
        0x70,
        0x82,
        0xFF,
        0x7F,
        0xC9,
        0x88,
        0x8C,
        0x14,
        0x4D,
        0xA2,
        0xAF,
        0x58,
        0x42,
        0x9E,
        0xC9,
        0x60,
        0x31,
        0xDB,
        0xCA,
        0xD3,
        0xDA,
        0xD9,
        0xAF,
        0x0D,
        0xCB,
        0xAA,
        0xAF,
        0x26,
        0x8C,
        0xB8,
        0xFC,
        0xFF,
        0xEA,
        0xD9,
        0x4F,
        0x3C,
        0x7C,
        0xA4,
        0x95,
        0xE0,
        0x56,
        0xA9,
        0xB4,
        0x7A,
        0xCD,
        0xB7,
        0x51,
        0xFB,
        0x73,
        0xE6,
        0x66,
        0xC6,
        0xC6,
        0x55,
        0xAD,
        0xE8,
        0x29,
        0x72,
        0x97,
        0xD0,
        0x7A,
        0xD1,
        0xBA,
        0x5E,
        0x43,
        0xF1,
        0xBC,
        0xA3,
        0x23,
        0x01,
        0x65,
        0x13,
        0x39,
        0xE2,
        0x29,
        0x04,
        0xCC,
        0x8C,
        0x42,
        0xF5,
        0x8C,
        0x30,
        0xC0,
        0x4A,
        0xAF,
        0xDB,
        0x03,
        0x8D,
        0xDA,
        0x08,
        0x47,
        0xDD,
        0x98,
        0x8D,
        0xCD,
        0xA6,
        0xF3,
        0xBF,
        0xD1,
        0x5C,
        0x4B,
        0x4C,
        0x45,
        0x25,
        0x00,
        0x4A,
        0xA0,
        0x6E,
        0xEF,
        0xF8,
        0xCA,
        0x61,
        0x78,
        0x3A,
        0xAC,
        0xEC,
        0x57,
        0xFB,
        0x3D,
        0x1F,
        0x92,
        0xB0,
        0xFE,
        0x2F,
        0xD1,
        0xA8,
        0x5F,
        0x67,
        0x24,
        0x51,
        0x7B,
        0x65,
        0xE6,
        0x14,
        0xAD,
        0x68,
        0x08,
        0xD6,
        0xF6,
        0xEE,
        0x34,
        0xDF,
        0xF7,
        0x31,
        0x0F,
        0xDC,
        0x82,
        0xAE,
        0xBF,
        0xD9,
        0x04,
        0xB0,
        0x1E,
        0x1D,
        0xC5,
        0x4B,
        0x29,
        0x27,
        0x09,
        0x4B,
        0x2D,
        0xB6,
        0x8D,
        0x6F,
        0x90,
        0x3B,
        0x68,
        0x40,
        0x1A,
        0xDE,
        0xBF,
        0x5A,
        0x7E,
        0x08,
        0xD7,
        0x8F,
        0xF4,
        0xEF,
        0x5D,
        0x63,
        0x65,
        0x3A,
        0x65,
        0x04,
        0x0C,
        0xF9,
        0xBF,
        0xD4,
        0xAC,
        0xA7,
        0x98,
        0x4A,
        0x74,
        0xD3,
        0x71,
        0x45,
        0x98,
        0x67,
        0x80,
        0xFC,
        0x0B,
        0x16,
        0xAC,
        0x45,
        0x16,
        0x49,
        0xDE,
        0x61,
        0x88,
        0xA7,
        0xDB,
        0xDF,
        0x19,
        0x1F,
        0x64,
        0xB5,
        0xFC,
        0x5E,
        0x2A,
        0xB4,
        0x7B,
        0x57,
        0xF7,
        0xF7,
        0x27,
        0x6C,
        0xD4,
        0x19,
        0xC1,
        0x7A,
        0x3C,
        0xA8,
        0xE1,
        0xB9,
        0x39,
        0xAE,
        0x49,
        0xE4,
        0x88,
        0xAC,
        0xBA,
        0x6B,
        0x96,
        0x56,
        0x10,
        0xB5,
        0x48,
        0x01,
        0x09,
        0xC8,
        0xB1,
        0x7B,
        0x80,
        0xE1,
        0xB7,
        0xB7,
        0x50,
        0xDF,
        0xC7,
        0x59,
        0x8D,
        0x5D,
        0x50,
        0x11,
        0xFD,
        0x2D,
        0xCC,
        0x56,
        0x00,
        0xA3,
        0x2E,
        0xF5,
        0xB5,
        0x2A,
        0x1E,
        0xCC,
        0x82,
        0x0E,
        0x30,
        0x8A,
        0xA3,
        0x42,
        0x72,
        0x1A,
        0xAC,
        0x09,
        0x43,
        0xBF,
        0x66,
        0x86,
        0xB6,
        0x4B,
        0x25,
        0x79,
        0x37,
        0x65,
        0x04,
        0xCC,
        0xC4,
        0x93,
        0xD9,
        0x7E,
        0x6A,
        0xED,
        0x3F,
        0xB0,
        0xF9,
        0xCD,
        0x71,
        0xA4,
        0x3D,
        0xD4,
        0x97,
        0xF0,
        0x1F,
        0x17,
        0xC0,
        0xE2,
        0xCB,
        0x37,
        0x97,
        0xAA,
        0x2A,
        0x2F,
        0x25,
        0x66,
        0x56,
        0x16,
        0x8E,
        0x6C,
        0x49,
        0x6A,
        0xFC,
        0x5F,
        0xB9,
        0x32,
        0x46,
        0xF6,
        0xB1,
        0x11,
        0x63,
        0x98,
        0xA3,
        0x46,
        0xF1,
        0xA6,
        0x41,
        0xF3,
        0xB0,
        0x41,
        0xE9,
        0x89,
        0xF7,
        0x91,
        0x4F,
        0x90,
        0xCC,
        0x2C,
        0x7F,
        0xFF,
        0x35,
        0x78,
        0x76,
        0xE5,
        0x06,
        0xB5,
        0x0D,
        0x33,
        0x4B,
        0xA7,
        0x7C,
        0x22,
        0x5B,
        0xC3,
        0x07,
        0xBA,
        0x53,
        0x71,
        0x52,
        0xF3,
        0xF1,
        0x61,
        0x0E,
        0x4E,
        0xAF,
        0xE5,
        0x95,
        0xF6,
        0xD9,
        0xD9,
        0x0D,
        0x11,
        0xFA,
        0xA9,
        0x33,
        0xA1,
        0x5E,
        0xF1,
        0x36,
        0x95,
        0x46,
        0x86,
        0x8A,
        0x7F,
        0x3A,
        0x45,
        0xA9,
        0x67,
        0x68,
        0xD4,
        0x0F,
        0xD9,
        0xD0,
        0x34,
        0x12,
        0xC0,
        0x91,
        0xC6,
        0x31,
        0x5C,
        0xF4,
        0xFD,
        0xE7,
        0xCB,
        0x68,
        0x60,
        0x69,
        0x37,
        0x38,
        0x0D,
        0xB2,
        0xEA,
        0xAA,
        0x70,
        0x7B,
        0x4C,
        0x41,
        0x85,
        0xC3,
        0x2E,
        0xDD,
        0xCD,
        0xD3,
        0x06,
        0x70,
        0x5E,
        0x4D,
        0xC1,
        0xFF,
        0xC8,
        0x72,
        0xEE,
        0xEE,
        0x47,
        0x5A,
        0x64,
        0xDF,
        0xAC,
        0x86,
        0xAB,
        0xA4,
        0x1C,
        0x06,
        0x18,
        0x98,
        0x3F,
        0x87,
        0x41,
        0xC5,
        0xEF,
        0x68,
        0xD3,
        0xA1,
        0x01,
        0xE8,
        0xA3,
        0xB8,
        0xCA,
        0xC6,
        0x0C,
        0x90,
        0x5C,
        0x15,
        0xFC,
        0x91,
        0x08,
        0x40,
        0xB9,
        0x4C,
        0x00,
        0xA0,
        0xB9,
        0xD0};
    unsigned char RS4[64] = {
        0x0A,
        0xAB,
        0x4C,
        0x90,
        0x05,
        0x01,
        0xB3,
        0xE2,
        0x4D,
        0x7C,
        0xDF,
        0x46,
        0x63,
        0x32,
        0x6A,
        0x3A,
        0x87,
        0xDF,
        0x5E,
        0x48,
        0x43,
        0xB2,
        0xCB,
        0xDB,
        0x67,
        0xCB,
        0xF6,
        0xE4,
        0x60,
        0xFE,
        0xC3,
        0x50,
        0xAA,
        0x53,
        0x71,
        0xB1,
        0x50,
        0x8F,
        0x9F,
        0x45,
        0x28,
        0xEC,
        0xEA,
        0x23,
        0xC4,
        0x36,
        0xD9,
        0x4B,
        0x5E,
        0x8F,
        0xCD,
        0x4F,
        0x68,
        0x1E,
        0x30,
        0xA6,
        0xAC,
        0x00,
        0xA9,
        0x70,
        0x4A,
        0x18,
        0x8A,
        0x03};

    //test 5
    unsigned char prikey5[32] = {
        0x83,
        0x3F,
        0xE6,
        0x24,
        0x09,
        0x23,
        0x7B,
        0x9D,
        0x62,
        0xEC,
        0x77,
        0x58,
        0x75,
        0x20,
        0x91,
        0x1E,
        0x9A,
        0x75,
        0x9C,
        0xEC,
        0x1D,
        0x19,
        0x75,
        0x5B,
        0x7D,
        0xA9,
        0x01,
        0xB9,
        0x6D,
        0xCA,
        0x3D,
        0x42};
    unsigned char pubkey5[32] = {
        0xEC,
        0x17,
        0x2B,
        0x93,
        0xAD,
        0x5E,
        0x56,
        0x3B,
        0xF4,
        0x93,
        0x2C,
        0x70,
        0xE1,
        0x24,
        0x50,
        0x34,
        0xC3,
        0x54,
        0x67,
        0xEF,
        0x2E,
        0xFD,
        0x4D,
        0x64,
        0xEB,
        0xF8,
        0x19,
        0x68,
        0x34,
        0x67,
        0xE2,
        0xBF};
    unsigned char M5[64] = {
        0xDD,
        0xAF,
        0x35,
        0xA1,
        0x93,
        0x61,
        0x7A,
        0xBA,
        0xCC,
        0x41,
        0x73,
        0x49,
        0xAE,
        0x20,
        0x41,
        0x31,
        0x12,
        0xE6,
        0xFA,
        0x4E,
        0x89,
        0xA9,
        0x7E,
        0xA2,
        0x0A,
        0x9E,
        0xEE,
        0xE6,
        0x4B,
        0x55,
        0xD3,
        0x9A,
        0x21,
        0x92,
        0x99,
        0x2A,
        0x27,
        0x4F,
        0xC1,
        0xA8,
        0x36,
        0xBA,
        0x3C,
        0x23,
        0xA3,
        0xFE,
        0xEB,
        0xBD,
        0x45,
        0x4D,
        0x44,
        0x23,
        0x64,
        0x3C,
        0xE8,
        0x0E,
        0x2A,
        0x9A,
        0xC9,
        0x4F,
        0xA5,
        0x4C,
        0xA4,
        0x9F};
    unsigned char RS5[64] = {
        0xDC,
        0x2A,
        0x44,
        0x59,
        0xE7,
        0x36,
        0x96,
        0x33,
        0xA5,
        0x2B,
        0x1B,
        0xF2,
        0x77,
        0x83,
        0x9A,
        0x00,
        0x20,
        0x10,
        0x09,
        0xA3,
        0xEF,
        0xBF,
        0x3E,
        0xCB,
        0x69,
        0xBE,
        0xA2,
        0x18,
        0x6C,
        0x26,
        0xB5,
        0x89,
        0x09,
        0x35,
        0x1F,
        0xC9,
        0xAC,
        0x90,
        0xB3,
        0xEC,
        0xFD,
        0xFB,
        0xC7,
        0xC6,
        0x64,
        0x31,
        0xE0,
        0x30,
        0x3D,
        0xCA,
        0x17,
        0x9C,
        0x13,
        0x8A,
        0xC1,
        0x7A,
        0xD9,
        0xBE,
        0xF1,
        0x17,
        0x73,
        0x31,
        0xA7,
        0x04};

    unsigned int ret;

    //Ed25519 default mode test 1
    ret = ed25519_sign_verify_test_internal(Ed25519_DEFAULT, prikey1, pubkey1, NULL, 0, NULL, 0, RS1, 1, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 default mode test 2
    ret = ed25519_sign_verify_test_internal(Ed25519_DEFAULT, prikey2, NULL, NULL, 0, M2, 1, RS2, 2, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 default mode test 3
    ret = ed25519_sign_verify_test_internal(Ed25519_DEFAULT, prikey3, pubkey3, NULL, 0, M3, 2, RS3, 3, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 default mode test 4
    ret = ed25519_sign_verify_test_internal(Ed25519_DEFAULT, prikey4, pubkey4, NULL, 0, M4, 1023, RS4, 4, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 default mode test 5
    ret = ed25519_sign_verify_test_internal(Ed25519_DEFAULT, prikey5, pubkey5, NULL, 0, M5, 64, RS5, 5, 1);
    if (ret) {
        return ret;
    }

    return 0;
}

unsigned int ed25519_ctx_mode_std_test(void)
{
    //test 1
    unsigned char prikey1[32] = {
        0x03,
        0x05,
        0x33,
        0x4E,
        0x38,
        0x1A,
        0xF7,
        0x8F,
        0x14,
        0x1C,
        0xB6,
        0x66,
        0xF6,
        0x19,
        0x9F,
        0x57,
        0xBC,
        0x34,
        0x95,
        0x33,
        0x5A,
        0x25,
        0x6A,
        0x95,
        0xBD,
        0x2A,
        0x55,
        0xBF,
        0x54,
        0x66,
        0x63,
        0xF6};
    unsigned char pubkey1[32] = {
        0xDF,
        0xC9,
        0x42,
        0x5E,
        0x4F,
        0x96,
        0x8F,
        0x7F,
        0x0C,
        0x29,
        0xF0,
        0x25,
        0x9C,
        0xF5,
        0xF9,
        0xAE,
        0xD6,
        0x85,
        0x1C,
        0x2B,
        0xB4,
        0xAD,
        0x8B,
        0xFB,
        0x86,
        0x0C,
        0xFE,
        0xE0,
        0xAB,
        0x24,
        0x82,
        0x92};
    unsigned char M1[16] = {
        0xF7,
        0x26,
        0x93,
        0x6D,
        0x19,
        0xC8,
        0x00,
        0x49,
        0x4E,
        0x3F,
        0xDA,
        0xFF,
        0x20,
        0xB2,
        0x76,
        0xA8};
    unsigned char ctx1[3] = {
        0x66,
        0x6f,
        0x6f,
    };
    unsigned char RS1[64] = {
        0x55,
        0xA4,
        0xCC,
        0x2F,
        0x70,
        0xA5,
        0x4E,
        0x04,
        0x28,
        0x8C,
        0x5F,
        0x4C,
        0xD1,
        0xE4,
        0x5A,
        0x7B,
        0xB5,
        0x20,
        0xB3,
        0x62,
        0x92,
        0x91,
        0x18,
        0x76,
        0xCA,
        0xDA,
        0x73,
        0x23,
        0x19,
        0x8D,
        0xD8,
        0x7A,
        0x8B,
        0x36,
        0x95,
        0x0B,
        0x95,
        0x13,
        0x00,
        0x22,
        0x90,
        0x7A,
        0x7F,
        0xB7,
        0xC4,
        0xE9,
        0xB2,
        0xD5,
        0xF6,
        0xCC,
        0xA6,
        0x85,
        0xA5,
        0x87,
        0xB4,
        0xB2,
        0x1F,
        0x4B,
        0x88,
        0x8E,
        0x4E,
        0x7E,
        0xDB,
        0x0D};

    //test 2
    //use key pair of test 1
    //use message of test 1
    unsigned char ctx2[3] = {
        0x62,
        0x61,
        0x72,
    };
    unsigned char RS2[64] = {
        0xFC,
        0x60,
        0xD5,
        0x87,
        0x2F,
        0xC4,
        0x6B,
        0x3A,
        0xA6,
        0x9F,
        0x8B,
        0x5B,
        0x43,
        0x51,
        0xD5,
        0x80,
        0x8F,
        0x92,
        0xBC,
        0xC0,
        0x44,
        0x60,
        0x6D,
        0xB0,
        0x97,
        0xAB,
        0xAB,
        0x6D,
        0xBC,
        0xB1,
        0xAE,
        0xE3,
        0x21,
        0x6C,
        0x48,
        0xE8,
        0xB3,
        0xB6,
        0x64,
        0x31,
        0xB5,
        0xB1,
        0x86,
        0xD1,
        0xD2,
        0x8F,
        0x8E,
        0xE1,
        0x5A,
        0x5C,
        0xA2,
        0xDF,
        0x66,
        0x68,
        0x34,
        0x62,
        0x91,
        0xC2,
        0x04,
        0x3D,
        0x4E,
        0xB3,
        0xE9,
        0x0D};

    //test 3
    //use key pair of test 1
    //use ctx of test 1
    unsigned char M3[16] = {
        0x50,
        0x8E,
        0x9E,
        0x68,
        0x82,
        0xB9,
        0x79,
        0xFE,
        0xA9,
        0x00,
        0xF6,
        0x2A,
        0xDC,
        0xEA,
        0xCA,
        0x35,
    };
    unsigned char RS3[64] = {
        0x8B,
        0x70,
        0xC1,
        0xCC,
        0x83,
        0x10,
        0xE1,
        0xDE,
        0x20,
        0xAC,
        0x53,
        0xCE,
        0x28,
        0xAE,
        0x6E,
        0x72,
        0x07,
        0xF3,
        0x3C,
        0x32,
        0x95,
        0xE0,
        0x3B,
        0xB5,
        0xC0,
        0x73,
        0x2A,
        0x1D,
        0x20,
        0xDC,
        0x64,
        0x90,
        0x89,
        0x22,
        0xA8,
        0xB0,
        0x52,
        0xCF,
        0x99,
        0xB7,
        0xC4,
        0xFE,
        0x10,
        0x7A,
        0x5A,
        0xBB,
        0x5B,
        0x2C,
        0x40,
        0x85,
        0xAE,
        0x75,
        0x89,
        0x0D,
        0x02,
        0xDF,
        0x26,
        0x26,
        0x9D,
        0x89,
        0x45,
        0xF8,
        0x4B,
        0x0B};

    //test 4
    //use ctx of test 1
    //use message of test 1
    unsigned char prikey4[32] = {
        0xAB,
        0x9C,
        0x28,
        0x53,
        0xCE,
        0x29,
        0x7D,
        0xDA,
        0xB8,
        0x5C,
        0x99,
        0x3B,
        0x3A,
        0xE1,
        0x4B,
        0xCA,
        0xD3,
        0x9B,
        0x2C,
        0x68,
        0x2B,
        0xEA,
        0xBC,
        0x27,
        0xD6,
        0xD4,
        0xEB,
        0x20,
        0x71,
        0x1D,
        0x65,
        0x60};
    unsigned char pubkey4[32] = {
        0x0F,
        0x1D,
        0x12,
        0x74,
        0x94,
        0x3B,
        0x91,
        0x41,
        0x58,
        0x89,
        0x15,
        0x2E,
        0x89,
        0x3D,
        0x80,
        0xE9,
        0x32,
        0x75,
        0xA1,
        0xFC,
        0x0B,
        0x65,
        0xFD,
        0x71,
        0xB4,
        0xB0,
        0xDD,
        0xA1,
        0x0A,
        0xD7,
        0xD7,
        0x72};
    unsigned char RS4[64] = {
        0x21,
        0x65,
        0x5B,
        0x5F,
        0x1A,
        0xA9,
        0x65,
        0x99,
        0x6B,
        0x3F,
        0x97,
        0xB3,
        0xC8,
        0x49,
        0xEA,
        0xFB,
        0xA9,
        0x22,
        0xA0,
        0xA6,
        0x29,
        0x92,
        0xF7,
        0x3B,
        0x3D,
        0x1B,
        0x73,
        0x10,
        0x6A,
        0x84,
        0xAD,
        0x85,
        0xE9,
        0xB8,
        0x6A,
        0x7B,
        0x60,
        0x05,
        0xEA,
        0x86,
        0x83,
        0x37,
        0xFF,
        0x2D,
        0x20,
        0xA7,
        0xF5,
        0xFB,
        0xD4,
        0xCD,
        0x10,
        0xB0,
        0xBE,
        0x49,
        0xA6,
        0x8D,
        0xA2,
        0xB2,
        0xE0,
        0xDC,
        0x0A,
        0xD8,
        0x96,
        0x0F};

    unsigned int ret;

    //Ed25519 ctx mode test 1
    ret = ed25519_sign_verify_test_internal(Ed25519_CTX, prikey1, NULL, ctx1, 3, M1, 16, RS1, 1, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 ctx mode test 2
    ret = ed25519_sign_verify_test_internal(Ed25519_CTX, prikey1, pubkey1, ctx2, 3, M1, 16, RS2, 2, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 ctx mode test 3
    ret = ed25519_sign_verify_test_internal(Ed25519_CTX, prikey1, pubkey1, ctx1, 3, M3, 16, RS3, 3, 1);
    if (ret) {
        return ret;
    }

    //Ed25519 ctx mode test 4
    ret = ed25519_sign_verify_test_internal(Ed25519_CTX, prikey4, pubkey4, ctx1, 3, M1, 16, RS4, 4, 1);
    if (ret) {
        return ret;
    }

    return 0;
}

unsigned int ed25519_ph_mode_std_test(void)
{
    unsigned char prikey1[32] = {
        0x83,
        0x3F,
        0xE6,
        0x24,
        0x09,
        0x23,
        0x7B,
        0x9D,
        0x62,
        0xEC,
        0x77,
        0x58,
        0x75,
        0x20,
        0x91,
        0x1E,
        0x9A,
        0x75,
        0x9C,
        0xEC,
        0x1D,
        0x19,
        0x75,
        0x5B,
        0x7D,
        0xA9,
        0x01,
        0xB9,
        0x6D,
        0xCA,
        0x3D,
        0x42};
    //    unsigned char  pubkey1[32]={
    //        0xEC,0x17,0x2B,0x93,0xAD,0x5E,0x56,0x3B,0xF4,0x93,0x2C,0x70,0xE1,0x24,0x50,0x34,
    //        0xC3,0x54,0x67,0xEF,0x2E,0xFD,0x4D,0x64,0xEB,0xF8,0x19,0x68,0x34,0x67,0xE2,0xBF
    //    };
    unsigned char M1[3] = {
        0x61,
        0x62,
        0x63};
    unsigned char RS1[64] = {
        0x98,
        0xA7,
        0x02,
        0x22,
        0xF0,
        0xB8,
        0x12,
        0x1A,
        0xA9,
        0xD3,
        0x0F,
        0x81,
        0x3D,
        0x68,
        0x3F,
        0x80,
        0x9E,
        0x46,
        0x2B,
        0x46,
        0x9C,
        0x7F,
        0xF8,
        0x76,
        0x39,
        0x49,
        0x9B,
        0xB9,
        0x4E,
        0x6D,
        0xAE,
        0x41,
        0x31,
        0xF8,
        0x50,
        0x42,
        0x46,
        0x3C,
        0x2A,
        0x35,
        0x5A,
        0x20,
        0x03,
        0xD0,
        0x62,
        0xAD,
        0xF5,
        0xAA,
        0xA1,
        0x0B,
        0x8C,
        0x61,
        0xE6,
        0x36,
        0x06,
        0x2A,
        0xAA,
        0xD1,
        0x1C,
        0x2A,
        0x26,
        0x08,
        0x34,
        0x06};
    unsigned int ret;

    //Ed25519 ph mode test 1
    ret = ed25519_sign_verify_test_internal(Ed25519_PH, prikey1, NULL, NULL, 0, M1, 3, RS1, 1, 1);
    if (ret) {
        return ret;
    }

    return 0;
}

unsigned int ed25519_ph_with_ph_m_mode_std_test(void)
{
    unsigned char prikey1[32] = {
        0x83,
        0x3F,
        0xE6,
        0x24,
        0x09,
        0x23,
        0x7B,
        0x9D,
        0x62,
        0xEC,
        0x77,
        0x58,
        0x75,
        0x20,
        0x91,
        0x1E,
        0x9A,
        0x75,
        0x9C,
        0xEC,
        0x1D,
        0x19,
        0x75,
        0x5B,
        0x7D,
        0xA9,
        0x01,
        0xB9,
        0x6D,
        0xCA,
        0x3D,
        0x42};
    //    unsigned char  pubkey1[32]={
    //        0xEC,0x17,0x2B,0x93,0xAD,0x5E,0x56,0x3B,0xF4,0x93,0x2C,0x70,0xE1,0x24,0x50,0x34,
    //        0xC3,0x54,0x67,0xEF,0x2E,0xFD,0x4D,0x64,0xEB,0xF8,0x19,0x68,0x34,0x67,0xE2,0xBF
    //    };
    //sha512(0x616263)
    unsigned char PH_M1[64] = {
        0xDD,
        0xAF,
        0x35,
        0xA1,
        0x93,
        0x61,
        0x7A,
        0xBA,
        0xCC,
        0x41,
        0x73,
        0x49,
        0xAE,
        0x20,
        0x41,
        0x31,
        0x12,
        0xE6,
        0xFA,
        0x4E,
        0x89,
        0xA9,
        0x7E,
        0xA2,
        0x0A,
        0x9E,
        0xEE,
        0xE6,
        0x4B,
        0x55,
        0xD3,
        0x9A,
        0x21,
        0x92,
        0x99,
        0x2A,
        0x27,
        0x4F,
        0xC1,
        0xA8,
        0x36,
        0xBA,
        0x3C,
        0x23,
        0xA3,
        0xFE,
        0xEB,
        0xBD,
        0x45,
        0x4D,
        0x44,
        0x23,
        0x64,
        0x3C,
        0xE8,
        0x0E,
        0x2A,
        0x9A,
        0xC9,
        0x4F,
        0xA5,
        0x4C,
        0xA4,
        0x9F,
    };
    unsigned char RS1[64] = {
        0x98,
        0xA7,
        0x02,
        0x22,
        0xF0,
        0xB8,
        0x12,
        0x1A,
        0xA9,
        0xD3,
        0x0F,
        0x81,
        0x3D,
        0x68,
        0x3F,
        0x80,
        0x9E,
        0x46,
        0x2B,
        0x46,
        0x9C,
        0x7F,
        0xF8,
        0x76,
        0x39,
        0x49,
        0x9B,
        0xB9,
        0x4E,
        0x6D,
        0xAE,
        0x41,
        0x31,
        0xF8,
        0x50,
        0x42,
        0x46,
        0x3C,
        0x2A,
        0x35,
        0x5A,
        0x20,
        0x03,
        0xD0,
        0x62,
        0xAD,
        0xF5,
        0xAA,
        0xA1,
        0x0B,
        0x8C,
        0x61,
        0xE6,
        0x36,
        0x06,
        0x2A,
        0xAA,
        0xD1,
        0x1C,
        0x2A,
        0x26,
        0x08,
        0x34,
        0x06};
    unsigned int ret;

    //Ed25519 ph_with_ph_m mode test 1
    ret = ed25519_sign_verify_test_internal(Ed25519_PH_WITH_PH_M, prikey1, NULL, NULL, 0, PH_M1, 3, RS1, 1, 1);
    if (ret) {
        return ret;
    }

    return 0;
}

unsigned int ed25519_std_test(void)
{
    printf("\r\n\r\n -------------- Ed25519 sign & verify standard data test -------------- ");

    if (ed25519_default_mode_std_test()) {
        return 1;
    }

    if (ed25519_ctx_mode_std_test()) {
        return 1;
    }

    if (ed25519_ph_mode_std_test()) {
        return 1;
    }

    if (ed25519_ph_with_ph_m_mode_std_test()) {
        return 1;
    }

    return 0;
}

unsigned int ed25519_get_key_corner_test(void)
{
    //prikey is all 0
    unsigned char pubkey1[32] = {
        0x3B,
        0x6A,
        0x27,
        0xBC,
        0xCE,
        0xB6,
        0xA4,
        0x2D,
        0x62,
        0xA3,
        0xA8,
        0xD0,
        0x2A,
        0x6F,
        0x0D,
        0x73,
        0x65,
        0x32,
        0x15,
        0x77,
        0x1D,
        0xE2,
        0x43,
        0xA6,
        0x3A,
        0xC0,
        0x48,
        0xA1,
        0x8B,
        0x59,
        0xDA,
        0x29};

    //prikey is all 1
    unsigned char pubkey2[32] = {
        0x76,
        0xA1,
        0x59,
        0x20,
        0x44,
        0xA6,
        0xE4,
        0xF5,
        0x11,
        0x26,
        0x5B,
        0xCA,
        0x73,
        0xA6,
        0x04,
        0xD9,
        0x0B,
        0x05,
        0x29,
        0xD1,
        0xDF,
        0x60,
        0x2B,
        0xE3,
        0x0A,
        0x19,
        0xA9,
        0x25,
        0x76,
        0x60,
        0xD1,
        0xF5};

    unsigned char prikey[32];
    unsigned char pubkey[32];

    unsigned int ret;

    printf("\r\n\r\n -------------- Ed25519 get key corner test -------------- ");

    //test 1
    memset_(prikey, 0, 32);
    ret = ed25519_get_pubkey_from_prikey(prikey, pubkey);
    if (ret || memcmp_(pubkey, pubkey1, 32)) {
        printf("\r\n Ed25519 get key corner test 1 error, ret=%x", ret);
        fflush(stdout);
        print_buf_U8(pubkey, 32, "pubkey 1");
        return 1;
    } else {
        printf("\r\n Ed25519 get key corner test 1 success");
        fflush(stdout);
    }

    //test 2
    memset_(prikey, 0xFF, 32);
    ret = ed25519_get_pubkey_from_prikey(prikey, pubkey);
    if (ret || memcmp_(pubkey, pubkey2, 32)) {
        printf("\r\n Ed25519 get key corner test 2 error, ret=%x", ret);
        fflush(stdout);
        print_buf_U8(pubkey, 32, "pubkey 2");
        return 1;
    } else {
        printf("\r\n Ed25519 get key corner test 2 success");
        fflush(stdout);
    }

    return 0;
}

unsigned int ed25519_rand_test(void)
{
    unsigned char  prikey[32];
    unsigned char  pubkey[32];
    unsigned char  ctx_buf[256];
    unsigned char *ctx;
    unsigned char  ctxByteLen;
    unsigned char  M[200];
    unsigned int   MByteLen;
    unsigned char  RS[64];
    unsigned int   i, j;
    unsigned int   ret;
    Ed25519_MODE   mode;

    printf("\r\n\r\n -------------- Ed25519 sign & verify rand data test -------------- ");

    for (i = 0; i < Ed25519_SIGN_VERIFY_ROUND1; i++) {
        //rand key pair
        ret = ed25519_getkey(prikey, pubkey);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n Ed25519 get key error, ret = %x", ret);
            return 1;
        }

        for (j = 0; j < 50; j++) {
            printf("\r\n Ed25519 round1=%u, round2=%u", i + 1, j + 1);

            ctx = ctx_buf;

            ret = get_rand(ctx_buf, 4);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get rand error, ret = %x", ret);
                return 1;
            }

            //rand mode
            mode = (Ed25519_MODE)(ctx_buf[0] % 4);

            //rand ctx(rand length)
            if (Ed25519_CTX == mode) {
                ctxByteLen = ctx_buf[1] % 255 + 1;
            } else //traverse case about parameter of ctx and ctxByteLen
            {
                if (ctx_buf[1] & 1) {
                    ctxByteLen = ctx_buf[2];
                } else {
                    ctxByteLen = 0;
                    if (ctx_buf[1] & 0x80) {
                        ctx = NULL;
                    } else {
                        ;
                    }
                }
            }

            if (Ed25519_PH_WITH_PH_M == mode) {
                MByteLen = 64; //sha512 digest length.
            } else {
                MByteLen = ctx_buf[3] % (sizeof(M));
            }

            if (0U != ctxByteLen) {
                ret = get_rand(ctx, ctxByteLen);
                if (TRNG_SUCCESS != ret) {
                    printf("\r\n get ctx error, ret = %x", ret);
                }
            }

            //rand M(rand length)
            ret = get_rand(M, MByteLen);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get M error, ret = %x", ret);
                return 1;
            }

            ret = ed25519_sign_verify_test_internal(mode, prikey, pubkey, ctx, ctxByteLen, M, MByteLen, NULL, j + 1, 0);
            if (ret) {
                printf("\r\n Ed25519 sign error, ret = %x", ret);
                print_buf_U8(prikey, 32, "prikey");
                print_buf_U8(pubkey, 32, "pubkey");
                print_buf_U8(ctx, ctxByteLen, "ctx");
                print_buf_U8(M, MByteLen, "M");
                print_buf_U8(RS, 64, "RS");
                return ret;
            }
        }
    }

    return 0;
}

unsigned int ed25519_speed_test(void)
{
    unsigned int k[8], k2[8];
    //unsigned char prikey[32];
    //unsigned char pubkey[32];
    unsigned char prikey[32] = {
        0x83,
        0x3F,
        0xE6,
        0x24,
        0x09,
        0x23,
        0x7B,
        0x9D,
        0x62,
        0xEC,
        0x77,
        0x58,
        0x75,
        0x20,
        0x91,
        0x1E,
        0x9A,
        0x75,
        0x9C,
        0xEC,
        0x1D,
        0x19,
        0x75,
        0x5B,
        0x7D,
        0xA9,
        0x01,
        0xB9,
        0x6D,
        0xCA,
        0x3D,
        0x42};
    unsigned char pubkey[32] = {
        0xEC,
        0x17,
        0x2B,
        0x93,
        0xAD,
        0x5E,
        0x56,
        0x3B,
        0xF4,
        0x93,
        0x2C,
        0x70,
        0xE1,
        0x24,
        0x50,
        0x34,
        0xC3,
        0x54,
        0x67,
        0xEF,
        0x2E,
        0xFD,
        0x4D,
        0x64,
        0xEB,
        0xF8,
        0x19,
        0x68,
        0x34,
        0x67,
        0xE2,
        0xBF};

    unsigned char ctx[200];
    unsigned int  ctxByteLen = 32;
    unsigned char M[200];
    unsigned int  MByteLen = 32;
    unsigned char RS[64];
    unsigned int  ret  = 0;
    Ed25519_MODE  mode = Ed25519_PH;
    unsigned int  i, round;
    unsigned int  pointMul_round = 2000;
    unsigned int  sign_round     = 1000;
    unsigned int  verify_round   = 500;

    printf("\r\n ============= get key begin =============");
    fflush(stdout);

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    round = pointMul_round / 30;
    startP();
    #else
    round = pointMul_round;
    #endif

    for (i = 0; i < round; i++) {
        ret = ed25519_getkey(prikey, pubkey);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n Ed25519 get key error, ret = %x", ret);
            return 1;
        }
    }

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n get key finished");
    fflush(stdout);
    #endif

    //print_buf_U8(prikey, 32, "prikey");
    //print_buf_U8(pubkey, 32, "pubkey");


    x25519_decode_scalar((unsigned char *)prikey, (unsigned char *)k, Ed25519_BYTE_LEN);
    printf("\r\n ============= point mul begin =============");
    fflush(stdout);

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    startP();
    #endif

    for (i = 0; i < round; i++) {
        ret = ed25519_pointMul(ed25519, k, ed25519->Gx, ed25519->Gy, k, k2);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n point mul error, ret = %x", ret);
            return 1;
        }
    }

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n point mul finished");
    fflush(stdout);
    #endif


    printf("\r\n ============= Ed25519 sign begin =============");
    fflush(stdout);

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    round = sign_round / 30;
    startP();
    #else
    round = sign_round;
    #endif

    for (i = 0; i < round; i++) {
        ret = ed25519_sign(mode, prikey, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n Ed25519 sign error, ret = %x", ret);
            print_buf_U8(prikey, 32, "prikey");
            print_buf_U8(pubkey, 32, "pubkey");
            print_buf_U8(ctx, ctxByteLen, "ctx");
            print_buf_U8(M, MByteLen, "M");
            print_buf_U8(RS, 64, "RS");
            return 1;
        }
    }

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n Ed25519 sign finished");
    fflush(stdout);
    #endif


    printf("\r\n ============= Ed25519 verify begin =============");
    fflush(stdout);

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    round = verify_round / 30;
    startP();
    #else
    round = verify_round;
    #endif

    for (i = 0; i < round; i++) {
        ret = ed25519_verify(mode, pubkey, ctx, ctxByteLen, M, MByteLen, RS);
        if (EdDSA_SUCCESS != ret) {
            printf("\r\n Ed25519 verify error, ret = %x", ret);
            print_buf_U8(prikey, 32, "prikey");
            print_buf_U8(pubkey, 32, "pubkey");
            print_buf_U8(ctx, ctxByteLen, "ctx");
            print_buf_U8(M, MByteLen, "M");
            print_buf_U8(RS, 64, "RS");
            return 1;
        }
    }

    #ifdef ED25519_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n Ed25519 verify finished");
    fflush(stdout);
    #endif

    return 0;
}

unsigned int Ed25519_all_test(void)
{
    printf("\r\n\r\n\r\n =================== EdDSA(Ed25519) test =================== ");

    #if 0

    if(ed25519_speed_test())
        return 1;

    #else

    if (ed25519_std_test()) {
        return 1;
    }

    if (ed25519_get_key_corner_test()) {
        return 1;
    }

    if (ed25519_rand_test()) {
        return 1;
    }

    #endif

    return 0;
}


#endif

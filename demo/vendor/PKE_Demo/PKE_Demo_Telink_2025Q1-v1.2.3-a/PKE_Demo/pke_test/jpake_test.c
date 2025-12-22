/********************************************************************************************************
 * @file    jpake_test.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include <string.h>


#include "lib/include/crypto_common/utility.h"
#include "lib/include/pke/jpake.h"
#include "lib/include/trng/trng.h"


#ifdef SUPPORT_JPAKE

/**
 * @brief           Internal function for J-PAKE sample test
 * @param[in]       jpake_para           - J-PAKE parameters
 * @param[in]       info                 - Test information string
 * @return          0 if test succeeds, 1 if any error occurs
 */
unsigned int jpake_sample_test_internal(jpake_para_t *jpake_para, char *info)
{
    char        *IDA       = "Alice";
    unsigned int IDA_bytes = 5;

    jpake_user_info_t Alice_info[1] = {
        {
            (unsigned char *)IDA,
            IDA_bytes,
            NULL,
            0,
        },
    };

    unsigned int x1[JPAKE_MAX_WORD_LEN], gx1[JPAKE_MAX_WORD_LEN], x1_gv[JPAKE_MAX_WORD_LEN], x1_r[JPAKE_MAX_WORD_LEN];
    unsigned int x2[JPAKE_MAX_WORD_LEN], gx2[JPAKE_MAX_WORD_LEN], x2_gv[JPAKE_MAX_WORD_LEN], x2_r[JPAKE_MAX_WORD_LEN];
    jpake_zkp_t  x1_zkp[1], x2_zkp[1];

    unsigned int gx1x3x4_x2_s[JPAKE_MAX_WORD_LEN], x2_s_gv[JPAKE_MAX_WORD_LEN], x2_s_r[JPAKE_MAX_WORD_LEN];
    jpake_zkp_t  x2_s_zkp[1];

    unsigned int       g1_g3[JPAKE_MAX_WORD_LEN], x2_s[JPAKE_MAX_WORD_LEN];
    jpake_round2_ctx_t alice_round2_ctx[1];

    unsigned int  ka[JPAKE_MAX_WORD_LEN];
    unsigned char h_ka[64], h_h_ka[64];

    char        *IDB       = "B0b";
    unsigned int IDB_bytes = 3;

    jpake_user_info_t Bob_info[1] = {
        {
            (unsigned char *)IDB,
            IDB_bytes,
            NULL,
            0,
        },
    };

    unsigned int x3[JPAKE_MAX_WORD_LEN], gx3[JPAKE_MAX_WORD_LEN], x3_gv[JPAKE_MAX_WORD_LEN], x3_r[JPAKE_MAX_WORD_LEN];
    unsigned int x4[JPAKE_MAX_WORD_LEN], gx4[JPAKE_MAX_WORD_LEN], x4_gv[JPAKE_MAX_WORD_LEN], x4_r[JPAKE_MAX_WORD_LEN];
    jpake_zkp_t  x3_zkp[1], x4_zkp[1];

    unsigned int gx1x2x3_x4_s[JPAKE_MAX_WORD_LEN], x4_s_gv[JPAKE_MAX_WORD_LEN], x4_s_r[JPAKE_MAX_WORD_LEN];
    jpake_zkp_t  x4_s_zkp[1];

    unsigned int       g3_g1[JPAKE_MAX_WORD_LEN], x4_s[JPAKE_MAX_WORD_LEN];
    jpake_round2_ctx_t bob_round2_ctx[1];

    unsigned int  kb[JPAKE_MAX_WORD_LEN];
    unsigned char h_kb[64], h_h_kb[64];

    // shared secret, as a sample, s =
    // 96650DB54943DB68E8ED4CBE54F0CD7C5DA954401EAEED66409748043AF8EAB4 this is no
    // need to be too long, recommend to be not greater than 32 bytes.
    unsigned int s[8] = {
        0x3AF8EAB4, 0x40974804, 0x1EAEED66, 0x5DA95440, 0x54F0CD7C, 0xE8ED4CBE, 0x4943DB68, 0x96650DB5,
    };
    unsigned int s_wlen       = 8;
    unsigned int digest_bytes = hash_get_digest_word_len(jpake_para->hash_alg) << 2;
    unsigned int p_wlen       = get_word_len(jpake_para->p_bitlen);
    unsigned int ret;

    x1_zkp->ga = gx1;
    x1_zkp->gv = x1_gv;
    x1_zkp->r  = x1_r;

    x2_zkp->ga = gx2;
    x2_zkp->gv = x2_gv;
    x2_zkp->r  = x2_r;

    x2_s_zkp->ga = gx1x3x4_x2_s;
    x2_s_zkp->gv = x2_s_gv;
    x2_s_zkp->r  = x2_s_r;

    alice_round2_ctx->gxa_gxc = g1_g3;
    alice_round2_ctx->xb_s    = x2_s;

    x3_zkp->ga = gx3;
    x3_zkp->gv = x3_gv;
    x3_zkp->r  = x3_r;

    x4_zkp->ga = gx4;
    x4_zkp->gv = x4_gv;
    x4_zkp->r  = x4_r;

    x4_s_zkp->ga = gx1x2x3_x4_s;
    x4_s_zkp->gv = x4_s_gv;
    x4_s_zkp->r  = x4_s_r;

    bob_round2_ctx->gxa_gxc = g3_g1;
    bob_round2_ctx->xb_s    = x4_s;

    printf("\r\n J-PAKE test %s", info);
    fflush(stdout);

#if 1
    ret = get_rand((unsigned char *)s, s_wlen << 2);
    if (ret != TRNG_SUCCESS) {
        printf("\r\n get shared secret error, ret = %x", ret);
        fflush(stdout);
        return 1;
    }
#endif

    /***************** round 1 ******************/

    // Alice generate x1, x2, zkp(x1), zkp(x2), and send zkp(x1), zkp(x2) to Bob.
    ret = jpake_round1_generate_xa_xb_and_local_two_zkps(jpake_para, Alice_info, x1, x2, x1_zkp, x2_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 1 Alice generate zkp(x1), zkp(x2) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 1 Alice generate zkp(x1), zkp(x2) success");
        fflush(stdout);
    }

    // Bob generate x3, x4, zkp(x3), zkp(x4), and send zkp(x3), zkp(x4) to Bob.
    ret = jpake_round1_generate_xa_xb_and_local_two_zkps(jpake_para, Bob_info, x3, x4, x3_zkp, x4_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 1 Bob generate zkp(x3), zkp(x4) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 1 Bob generate zkp(x3), zkp(x4) success");
        fflush(stdout);
    }

    // Alice receive zkp(x3), zkp(x4), and verify them
    ret = jpake_round1_verify_peer_two_zkps(jpake_para, Bob_info, x3_zkp, x4_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 1 Alice verify zkp(x3), zkp(x4) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 1 Alice verify zkp(x3), zkp(x4) success");
        fflush(stdout);
    }

    // Bob receive zkp(x1), zkp(x1), and verify them
    ret = jpake_round1_verify_peer_two_zkps(jpake_para, Alice_info, x1_zkp, x1_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 1 Bob verify zkp(x1), zkp(x2) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 1 Bob verify zkp(x1), zkp(x2) success");
        fflush(stdout);
    }

#if 0
    print_bn_buf_u32(x1, p_wlen, "x1");
    print_bn_buf_u32(x1_zkp->ga, p_wlen, "gx1");

    print_bn_buf_u32(x2, p_wlen, "x2");
    print_bn_buf_u32(x2_zkp->ga, p_wlen, "gx2");

    print_bn_buf_u32(x3, p_wlen, "x3");
    print_bn_buf_u32(x3_zkp->ga, p_wlen, "gx3");

    print_bn_buf_u32(x4, p_wlen, "x4");
    print_bn_buf_u32(x4_zkp->ga, p_wlen, "gx4");
#endif

    /***************** round 2 ******************/

    // Alice generate zkp(x2_s), and send it to Bob.
    ret = jpake_round2_generate_local_zkp(jpake_para, Alice_info, alice_round2_ctx, x2, gx1, gx3, gx4, s, s_wlen, x2_s_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 2 Alice generate zkp(x2_s) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 2 Alice generate zkp(x2_s) success");
        fflush(stdout);
    }

    // Bob generate zkp(x4_s), and send it to Alice.
    ret = jpake_round2_generate_local_zkp(jpake_para, Bob_info, bob_round2_ctx, x4, gx3, gx1, gx2, s, s_wlen, x4_s_zkp);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 2 Bob generate zkp(x4_s) error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 2 Bob generate zkp(x4_s) success");
        fflush(stdout);
    }

    // Alice verify zkp(x4_s), and compute key
    ret = jpake_round2_verify_peer_zkp_and_compute_key(jpake_para, Bob_info, alice_round2_ctx, x2, gx2, gx4, x4_s_zkp, ka);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 2 Alice verify zkp(x4_s) and compute key error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 2 Alice verify zkp(x4_s) and compute key success");
        fflush(stdout);
    }

    // Bob verify zkp(x2_s), and compute key
    ret = jpake_round2_verify_peer_zkp_and_compute_key(jpake_para, Alice_info, bob_round2_ctx, x4, gx4, gx2, x2_s_zkp, kb);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 2 Bob verify zkp(x2_s) and compute key error, ret = %x", ret);
        fflush(stdout);
        return 1;
    } else {
        printf("\r\n round 2 Bob verify zkp(x2_s) and compute key success");
        fflush(stdout);
    }

    if (uint32_big_num_cmp(ka, p_wlen, kb, p_wlen) != 0) {
        printf("\r\n round 2 error(ka != kb)!");
        print_bn_buf_u32(ka, p_wlen, "ka");
        print_bn_buf_u32(kb, p_wlen, "kb");
    } else {
        printf("\r\n round 2 success(ka = kb)!");
        fflush(stdout);
    }

    /***************** round 3(optional) ******************/

    // Alice compute H(ka) and H(H(ka)), and send H(H(ka)) to Bob
    ret = jpake_round3_hash_key(jpake_para, ka, h_ka);
    ret |= jpake_round3_hash_hash_key(jpake_para, h_ka, h_h_ka);
    if (ret != JPAKE_SUCCESS) {
        printf("\r\n round 3 Alice compute H(ka) and H(H(ka)) error!, ret = %x", ret);
        fflush(stdout);
        print_buf_u8(h_ka, digest_bytes, "Alice H(ka)");
        print_buf_u8(h_h_ka, digest_bytes, "Alice H(H(ka))");
    } else {
        printf("\r\n round 3 Alice compute H(ka) and H(H(ka)) success");
        fflush(stdout);
    }

    // Bob compute H(kb) and H(H(kb)), compare H(H(ka)) with H(H(kb)), if success,
    // send H(ka) to Alice
    ret = jpake_round3_hash_key(jpake_para, kb, h_kb);
    ret |= jpake_round3_hash_hash_key(jpake_para, h_kb, h_h_kb);
    if ((ret != JPAKE_SUCCESS) || (memcmp_(h_h_kb, h_h_kb, digest_bytes))) {
        printf("\r\n round 3 Bob compute H(kb) and H(H(kb)), or compare H(H(ka)) "
               "with H(H(kb)) error!, ret = %x",
               ret);
        fflush(stdout);
        print_buf_u8(h_ka, digest_bytes, "Alice H(ka)");
        print_buf_u8(h_h_ka, digest_bytes, "Alice H(H(ka))");
        print_buf_u8(h_kb, digest_bytes, "Bob H(kb)");
        print_buf_u8(h_h_kb, digest_bytes, "Bob H(H(kb))");
    } else {
        printf("\r\n round 3 Bob compare H(H(ka)) with H(H(kb)) success ");
        fflush(stdout);
    }

    // Alice compare H(ka) with H(kb)
    if (memcmp_(h_kb, h_kb, digest_bytes)) {
        printf("\r\n round 3 Alice compare H(ka) with H(kb) error!, ret = %x", ret);
        fflush(stdout);
        print_buf_u8(h_ka, digest_bytes, "Alice H(ka)");
        print_buf_u8(h_kb, digest_bytes, "Bob H(kb)");
    } else {
        printf("\r\n round 3 Alice compare H(ka) with H(kb) success");
        fflush(stdout);
    }

    printf("\r\n J-PAKE test %s success finally! \r\n", info);
    fflush(stdout);

    return 0;
}

/**
 * @brief           Main function for J-PAKE sample tests
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int jpake_sample_test(void)
{
    /*********************** parameter group 1 ************************/
    // p = 0xFD7F53811D75122952DF4A9C2EECE4E7F611B7523CEF4400C31E3F80B6512669
    //       455D402251FB593D8D58FABFC5F5BA30F6CB9B556CD7813B801D346FF26660B7
    //       6B9950A5A49F9FE8047B1022C24FBBA9D7FEB7C61BF83B57E7C6A8A6150F04FB
    //       83F6D3C51EC3023554135A169132F675F3AE2B61D72AEFF22203199DD14801C7
    // q = 0x9760508F15230BCCB292B982A2EB840BF0581CF5
    // g = 0xF7E1A085D69B3DDECBBCAB5C36B857B97994AFBBFA3AEA82F9574C0B3D078267
    //       5159578EBAD4594FE67107108180B449167123E84C281613B7CF09328CC8A6E1
    //       3C167A8B547C8D28E0A3AE1E2BB3A675916EA37F0BFA213562F1FB627A01243B
    //       CCA4F1BEA8519089A883DFE15AE59F06928B665E807B552564014C3BFECF492A
    unsigned int p_1[] = {
        0xD14801C7, 0x2203199D, 0xD72AEFF2, 0xF3AE2B61, 0x9132F675, 0x54135A16, 0x1EC30235, 0x83F6D3C5, 0x150F04FB, 0xE7C6A8A6, 0x1BF83B57,
        0xD7FEB7C6, 0xC24FBBA9, 0x047B1022, 0xA49F9FE8, 0x6B9950A5, 0xF26660B7, 0x801D346F, 0x6CD7813B, 0xF6CB9B55, 0xC5F5BA30, 0x8D58FABF,
        0x51FB593D, 0x455D4022, 0xB6512669, 0xC31E3F80, 0x3CEF4400, 0xF611B752, 0x2EECE4E7, 0x52DF4A9C, 0x1D751229, 0xFD7F5381,
    };
    unsigned int p_1_h[] = {
        0x8F228D83, 0x1A7CDCB6, 0x8F254FBF, 0x17B245C1, 0xCE90A905, 0x3AF4AD1B, 0xD9EBE90F, 0x35496DFC, 0x98830FDA, 0x4494D2A3, 0xDCE1D24A,
        0x765D3F6B, 0x91AEF454, 0x1EE1B194, 0x827138BE, 0x98171814, 0x04E5E77C, 0xB09E4E26, 0xE08F9D8D, 0x45B58675, 0xEF3AD133, 0x48FA0124,
        0x713A8AC6, 0x7764C637, 0x9D8822A8, 0x351CD710, 0x90710CE7, 0x307C64B0, 0x8FF37646, 0x797B3117, 0x6FC30450, 0x13E24463,
    };
    unsigned int p_1_n0[1] = {0x40C89009};
    unsigned int q_1[]     = {
        0xF0581CF5, 0xA2EB840B, 0xB292B982, 0x15230BCC, 0x9760508F,
    };
    unsigned int q_1_h[] = {
        0xC9462170, 0xC2A8C1AF, 0x4EC122B7, 0xB81FBA10, 0x54A71A76,
    };
    unsigned int q_1_n0[1] = {0x9BD550A3};
    unsigned int g_1[]     = {
        0xFECF492A, 0x64014C3B, 0x807B5525, 0x928B665E, 0x5AE59F06, 0xA883DFE1, 0xA8519089, 0xCCA4F1BE, 0x7A01243B, 0x62F1FB62, 0x0BFA2135,
        0x916EA37F, 0x2BB3A675, 0xE0A3AE1E, 0x547C8D28, 0x3C167A8B, 0x8CC8A6E1, 0xB7CF0932, 0x4C281613, 0x167123E8, 0x8180B449, 0xE6710710,
        0xBAD4594F, 0x5159578E, 0x3D078267, 0xF9574C0B, 0xFA3AEA82, 0x7994AFBB, 0x36B857B9, 0xCBBCAB5C, 0xD69B3DDE, 0xF7E1A085,
    };
    jpake_para_t para1[1] = {
        {
            p_1,
            q_1,
            g_1,
            p_1_h,
            p_1_n0,
            q_1_h,
            q_1_n0,
            1024,
            160,
            HASH_SM3,
        },
    };

    /*********************** parameter group 2 ************************/
    unsigned int p_2[] = {
        0xF24C3633, 0x7F909719, 0x22BC2A2C, 0x30A34052, 0xD24D96D1, 0x8E48E6C4, 0x2855FE56, 0x26F94FFC, 0x824E6C49, 0xF592EEAF, 0x31B53F33, 0x560357D1,
        0xA25190F2, 0xA576D493, 0xB31925AF, 0x4F5F5F9A, 0x873A7E5A, 0x87F08601, 0xA029472A, 0x7C8E028B, 0xD36893BA, 0x348CD355, 0x5F7333A9, 0x4BE4B9D2,
        0xFD22C7D4, 0x97CF242F, 0xB6E99426, 0xE5E34C4D, 0xCBEFB16A, 0xE9348E70, 0x2C78FCCB, 0x96F5C5DB, 0xFDCF913E, 0x55047C57, 0xB9D80697, 0x0DFE5128,
        0x01DC8365, 0xD0555B08, 0x723342D6, 0x12675AC9, 0x49D7AACB, 0x4639596D, 0xD2924B3E, 0xED78F006, 0x815B0DAB, 0x0B531044, 0x2EC8F060, 0xB93D2636,
    };
    unsigned int p_2_h[] = {
        0xEFD49833, 0xB490814F, 0xAD258973, 0x83A3EE7E, 0x767705AA, 0x9A82B2FE, 0x7D924046, 0xE1274395, 0x9BD107BC, 0xA0BD5219, 0x551FF213, 0x17E2C00E,
        0x334B6138, 0x4815D381, 0xE98F6C08, 0x21C146B1, 0x9508A9A2, 0xF2B7595B, 0xCD5F00F9, 0x9FBC266A, 0x7C8ED3E8, 0x9B153ECE, 0xA681D00B, 0xF8A76E05,
        0x38EF1044, 0x242B7F41, 0x5C5FA3AD, 0x04A0022D, 0xC5046760, 0xE388C654, 0x29D94CCE, 0x80DF67FA, 0x004F1E6C, 0x6F8DB995, 0x27DD6707, 0x58C0F7F1,
        0xBBC009D1, 0x617F54E3, 0x0B4FEF47, 0xE690F651, 0xEF23C3FF, 0x527D8F0E, 0x95D15366, 0x401AAF03, 0xC633E44F, 0x29E9AADD, 0x96F0B4F0, 0x363AF8B3,
    };
    unsigned int p_2_n0[1] = {0xD6D64B05};
    unsigned int q_2[]     = {
        0x9AB9827B, 0xD80C2BE9, 0x515971CF, 0xC4A7CC32, 0x55D6DF2D, 0xB793F3C4, 0x6753A7CA, 0x9D474C14, 0x873D952D, 0x72425BAA, 0x9B32A588, 0x21BB0583,
        0xE13AAD10, 0x272733EB, 0xFCBBEE72, 0x6F318701, 0xD194C864, 0x23EF8404, 0x8B3780C5, 0x9FCCA19C, 0xA8CED145, 0xF999881C, 0x41171866, 0x035C659A,
    };
    unsigned int q_2_h[] = {
        0x6811543A, 0x1F5B17D9, 0x81DC017A, 0x6D677950, 0x3BC5495D, 0xC264C768, 0x775B43A0, 0xF97672DB, 0x73721714, 0x7F6B00E3, 0x9450E9CB, 0x66D9C558,
        0x27BFD4FB, 0xBF9D6150, 0x0E18961F, 0xC75C4987, 0x317D87CF, 0xADFCF35D, 0xD90B448E, 0x13D9DD66, 0xA94C0524, 0x2468ACF7, 0x3C00047C, 0x00AFF285,
    };
    unsigned int q_2_n0[1] = {0xD73BF34D};
    unsigned int g_2[]     = {
        0xC83C5DEA, 0x84235AAE, 0xCD3D3D74, 0x779E4577, 0xF95E93BD, 0xA42DADFC, 0xDDE20B69, 0xF3CE0405, 0x1BF1362E, 0x71AB643C, 0x1762253A, 0xE0B55959,
        0x00B0F9FA, 0x5854E02C, 0x38CEB3B4, 0xD8DAFE96, 0x66C99AB4, 0xE0FEF70F, 0xA6BAA8C6, 0xD3056EEA, 0x60502735, 0x74DA989A, 0xCBFA2850, 0xB2E7B461,
        0xE730092D, 0x953DE6BB, 0x384AB06F, 0x8078C571, 0xD46F6C28, 0x4EDE3414, 0xF2D2EFD3, 0xAB5947FD, 0xB4BCAB7F, 0x76E23998, 0xDAB4E4AD, 0x206F01CD,
        0x5DC12162, 0xD5238FF3, 0xDFD413F2, 0xCD299A07, 0x7E4A8BF0, 0xCA02CC04, 0x4344EDFE, 0x4FDD9B1E, 0x83B17C0C, 0x41265CD7, 0x85B65A21, 0x4383CC55,
    };
    jpake_para_t para2[1] = {
        {
            p_2,
            q_2,
            g_2,
            p_2_h,
            p_2_n0,
            q_2_h,
            q_2_n0,
            1536,
            762,
            HASH_SM3,
        },
    };

    /*********************** parameter group 3 ************************/
    unsigned int p_3[] = {
        0xFA0515AD, 0x5868641F, 0xBD2AC431, 0x01AC5A6D, 0x393F06FF, 0x83802A23, 0xB05C06D1, 0xD3C8D4D9, 0x4DA53C72, 0x71B40FF4, 0xEED55601, 0xD1930210, 0xC677A047,
        0x53D931AA, 0xCFAB0B71, 0x6BD7E8E3, 0x6AAA6B92, 0xD4E12AA7, 0x25DFF5AF, 0x90AB67D2, 0x6AF14FBC, 0x71D33585, 0xA21687EC, 0x0F356C4F, 0xEECA8C07, 0x6BFFD507,
        0xF14014E8, 0x4B9F30EA, 0x27A7242F, 0x4C5B7E94, 0x067C1BAD, 0x8DDD1290, 0x0DCAEF4F, 0x69D6C4C6, 0xC53EEB30, 0x64E2C831, 0xA1F3B2B7, 0x52C6E1FD, 0xCE849B80,
        0xCF924320, 0x18637502, 0x0B4CA6AE, 0x24DBDDDA, 0x2CBFAAA8, 0xE85330F2, 0x63E87161, 0x2125D955, 0xB8231CF1, 0x077E6143, 0x00EC5D4C, 0xF4201196, 0x1E9A95E3,
        0xA04DEE36, 0x57ED6E5C, 0xB5E6DE39, 0xD33370D9, 0xF19CAB11, 0x46EFCD9C, 0x3EC5337D, 0xC317ABBD, 0x75C57739, 0xEE4CC890, 0x683F9FD6, 0xFACA1982,
    };
    unsigned int p_3_h[] = {
        0x0F5722DB, 0x44A9BDF6, 0x9CCEBE44, 0xFD415239, 0xCB01AB2A, 0xC756C165, 0xB01BCCE0, 0x5633095B, 0xA3FCC865, 0xAB26CA4F, 0x0BE2A8A3, 0x1B87224F, 0x8FDB6FF2,
        0x41E25828, 0x429520C0, 0x86428BB9, 0x4CCB102F, 0xDA6EA066, 0x2BFB4FA3, 0x89050BAA, 0x3DB3F2F2, 0xBA307959, 0x48DE62B6, 0x789C9EE1, 0x46A47266, 0xF6D0D49D,
        0x35E062EA, 0x7C1148B4, 0x29A3D7F8, 0x3738B94A, 0xE6D2EA0D, 0xA7461A82, 0x5BE811AC, 0xD5F4585E, 0x6036A017, 0xC6069D17, 0x3E241C54, 0x73611A0E, 0x22E335A6,
        0x289C2DDE, 0x8F6D8E5B, 0xBF65C148, 0xD3E3F037, 0x131CDA41, 0x20096C94, 0x5E4A0634, 0x78ABBDD9, 0x1B8CE1C1, 0xE87ED576, 0xA648CE10, 0x40DB14E7, 0x4ECF9EC6,
        0xEC51DF66, 0xACD99AD7, 0x245D3148, 0xD910AABC, 0x07353923, 0xDF4DD659, 0xD42E5566, 0xB0991CFE, 0x2638FC25, 0xCAAD9307, 0x57F94347, 0xC1B01EC5,
    };
    unsigned int p_3_n0[1] = {0x561CE9DB};
    unsigned int q_3[]     = {
        0xA9ADE5C1, 0x2BEEF28B, 0x31369686, 0x91B17BEC, 0x0D1C91F1, 0x9405BF01, 0x6721162A, 0xB1685ADD, 0xD25930D0, 0xAF87BF84, 0xB580AA05,
        0x23B87FAA, 0xA62519B9, 0x89FFA597, 0xA0A05281, 0x4D392B0B, 0x8496EFD5, 0x24DE3B3A, 0x7347A57E, 0x350C61DC, 0xD9B18737, 0x8B2F6895,
        0xF9548D76, 0xF72A13F7, 0x38BBE138, 0x90B07EC3, 0xA01DE210, 0xEDD1D05A, 0x05D2B2B8, 0x661F5578, 0x3485D6EA, 0x03CEAC8A,
    };
    unsigned int q_3_h[] = {
        0xAAA90DCB, 0x7AA0979D, 0x92340379, 0x247C7AD1, 0x5EF3DDDE, 0x37A492CC, 0xF20F9C0E, 0xE671FEBF, 0xFBDDEC7B, 0x5EEB76CD, 0x9682D3A6,
        0x6E858961, 0x4B411134, 0xBD95F521, 0xB08DBC16, 0xB918445F, 0x77C8A572, 0xA700026A, 0x2DBA1F3E, 0xB7FCF0A6, 0xAADF8186, 0xA691443F,
        0x7D8B8F42, 0xFBD0EA64, 0xDC7B51D6, 0xD0C9039D, 0x4D1BEA1B, 0x43419D13, 0x1E9A8D6A, 0x16424CE6, 0x348C7A2E, 0x027DD47E,
    };
    unsigned int q_3_n0[1] = {0x6D18D5BF};
    unsigned int g_3[]     = {
        0x8B26CAFE, 0xD084BBE5, 0xC40DA5B9, 0x916B1AF3, 0xF7827CA8, 0x54C1B1CB, 0x2B4F8D19, 0x2B212FC8, 0x56B16C5A, 0xA6B76B40, 0xC0C159C5, 0xA0804A34, 0x59D4A3BC,
        0x55CA660A, 0xD9FE9F7F, 0xC8CF2557, 0x800B295A, 0x6CB98240, 0xFDDCC0CE, 0xBBB79DFB, 0xF5C77489, 0x006A1EA3, 0xFBDA5911, 0xADB5D90D, 0xA4408BDF, 0xDDC64879,
        0xE42259EA, 0xEF2AD1D4, 0xCE453E1F, 0x5603A167, 0xB0145945, 0x4B5212CB, 0xDD6AEF8E, 0xDCAB5BD6, 0xE31704C8, 0x90224A78, 0xF00705E7, 0x29D19D3C, 0x30EC1246,
        0xA9E4F1E3, 0x7FF0A0CE, 0x6BCCA1E4, 0x6D38E32B, 0x88156785, 0x26A5BBBF, 0x5E5057D8, 0x826E661E, 0xDC70C330, 0xC0F46329, 0xFE689894, 0xD51CCE4B, 0xE8181996,
        0xFADCF5D1, 0x6C019161, 0xB468EF21, 0xFBC8700F, 0x6726041F, 0x5636DF01, 0x752DA463, 0x35C32E5D, 0x3E1BDC07, 0x6EFB4D40, 0x187C4124, 0x1AE98FD2,
    };
    jpake_para_t para3[1] = {
        {
            p_3,
            q_3,
            g_3,
            p_3_h,
            p_3_n0,
            q_3_h,
            q_3_n0,
            2048,
            1018,
            HASH_SM3,
        },
    };

    if (jpake_sample_test_internal(para1, "1(1024 bits)")) {
        return 1;
    }

    if (jpake_sample_test_internal(para2, "2(1536 bits)")) {
        return 1;
    }

    if (jpake_sample_test_internal(para3, "3(2048 bits)")) {
        return 1;
    }

    return 0;
}

#endif

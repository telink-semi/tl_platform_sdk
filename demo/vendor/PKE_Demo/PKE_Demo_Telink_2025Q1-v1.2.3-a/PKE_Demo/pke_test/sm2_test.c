/********************************************************************************************************
 * @file    sm2_test.c
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

#include "lib/include/pke/pke_config.h"


#ifdef SUPPORT_SM2

#include "lib/include/crypto_common/utility.h"
#include "lib/include/pke/rsa.h"
#include "lib/include/trng/trng.h"

// extern const eccp_curve_t sm2_curve[1];

// #define SM2_SPEED_TEST_BY_TIMER

#ifdef SM2_SPEED_TEST_BY_TIMER
extern unsigned int startp(void);
extern unsigned int endp(unsigned char mode, unsigned int once_bytes, unsigned int round);
#endif

#define SM2_SPEED_TEST_KEYGET_ROUND   (1000)
#define SM2_SPEED_TEST_SIGN_ROUND     (1000)
#define SM2_SPEED_TEST_VERIFY_ROUND   (800)

#define SM2_SPEED_TEST_PLAIN_BYTE_LEN (32) // byte length of plaintext
#define SM2_SPEED_TEST_ENCRYPT_ROUND  (800)
#define SM2_SPEED_TEST_DECRYPT_ROUND  (1000)
#define SM2_SPEED_TEST_EXCHANGE_ROUND (800)

#define SM2_SIGN_VERIFY_ROUND1        4
#define SM2_SIGN_VERIFY_ROUND2        20
#define SM2_ENCRYPT_DECRYPT_ROUND1    3
#define SM2_KEY_EXCHANGE_ROUND1       2

#define SM2_PLAIN_MAX_LEN             (200) // should be greater than 19(the byte length of standard data)
#define SM2_EXCHANGE_MAX_LEN          (200)

// extern const eccp_curve_t sm2_curve[1];

/**
 * @brief           SM2   key generation speed test
 * @return          0 for success, 1 for failure
 */
unsigned int SM2_keyget_speed_test(void)
{
    unsigned char prikey[32];
    unsigned char pubkey[65];
    unsigned int  i     = 0;
    unsigned int  round = SM2_SPEED_TEST_KEYGET_ROUND;
    unsigned int  ret;

    uint32_sleep(0x1FFFF, 1);

    // speed test
    printf("\r\n\r\n ======== sm2 keyget begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 10;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret = sm2_getkey(prikey, pubkey);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2 get key failure, ret=%u", ret);
            return 1;
        }
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n keyget finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           SM2   signature verification speed test
 * @return          0 for success, 1 for failure
 */
unsigned int SM2_sign_verify_speed_test(void)
{
    unsigned char prikey[32];
    unsigned char pubkey[65];
    unsigned char E[32] = {
        0xDD, 0x9E, 0xB8, 0x55, 0xA7, 0x18, 0x37, 0xB3, 0x2F, 0x93, 0x5A, 0x3D, 0x37, 0x81, 0x80, 0xDD,
        0xB9, 0xD2, 0x9C, 0x7F, 0x5A, 0x83, 0x30, 0x36, 0x1F, 0xE8, 0x08, 0xD7, 0xAA, 0x3A, 0x1E, 0x00,
    };
    unsigned char signature[64];
    unsigned int  i            = 0;
    unsigned int  sign_round   = SM2_SPEED_TEST_SIGN_ROUND;
    unsigned int  verify_round = SM2_SPEED_TEST_VERIFY_ROUND;
    unsigned int  round;
    unsigned int  ret;

    // a small loop for sleeping
    for (i = 0; i < 100; i++) {
        ret = sm2_getkey(prikey, pubkey);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2 get key failure, ret=%u", ret);
            return 1;
        }
    }

    // sm2_sign speed test
    round = sign_round;
    printf("\r\n\r\n ======== sm2_sign begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 10;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret = sm2_sign(E, NULL, prikey, signature);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2_sign test failure, ret=%u", ret);
            return 1;
        }
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n sm2_sign finished");
    fflush(stdout);
#endif

    // sm2_verify speed test
    round = verify_round;
    printf("\r\n ======== sm2_verify begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 10;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret = sm2_verify(E, pubkey, signature);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2 verify test failure, ret=%u", ret);
            return 1;
        }
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n sm2_verify finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           SM2   encryption decryption speed test
 * @return          for success, 1 for failure
 */
unsigned int SM2_encrypt_decrypt_speed_test(void)
{
    unsigned char prikey[32];
    unsigned char pubkey[65];
    unsigned char plain[SM2_SPEED_TEST_PLAIN_BYTE_LEN];
    unsigned char cipher[SM2_SPEED_TEST_PLAIN_BYTE_LEN + 97];
    unsigned char replain[SM2_SPEED_TEST_PLAIN_BYTE_LEN];
    unsigned int  bytelen = 0, bytelen2 = 0, i = 0;
    unsigned int  enc_round = SM2_SPEED_TEST_ENCRYPT_ROUND;
    unsigned int  dec_round = SM2_SPEED_TEST_DECRYPT_ROUND;
    unsigned int  round;
    unsigned int  ret;

    // a small loop for sleeping
    for (i = 0; i < 100; i++) {
        ret = sm2_getkey(prikey, pubkey);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2 get key failure, ret=%u", ret);
            return 1;
        }
    }

    // sm2_encrypt speed test
    round = enc_round;
    printf("\r\n\r\n ======== sm2_encrypt begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 20;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret = sm2_encrypt(plain, SM2_SPEED_TEST_PLAIN_BYTE_LEN, NULL, pubkey, SM2_C1C3C2, cipher, &bytelen);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2_encrypt failure");
            return 1;
        }
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n sm2_encrypt finished");
    fflush(stdout);
#endif

    // sm2_decrypt speed test
    round = dec_round;
    printf("\r\n ======== sm2_decrypt begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 20;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret = sm2_decrypt(cipher, bytelen, prikey, SM2_C1C3C2, replain, &bytelen2);
        if (SM2_SUCCESS != ret) {
            printf("\r\n sm2_decrypt failure");
            return 1;
        }
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n sm2_decrypt finished");
    fflush(stdout);
#endif

    return 0;
}

/**
 * @brief           SM2   key exchange speed test
 * @return          0 for success, 1 for failure
 */
unsigned int SM2_exchange_speed_test(void)
{
    unsigned char ZA[32], ZB[32], KA[32], KB[32], S1[32], SA[32], S2[32], SB[32];
    unsigned char PA[65]; // A's permanent public key
    unsigned char RA[65]; // A's temporary public key
    unsigned char dA[32]; // A's permanent private key
    unsigned char rA[32]; // A's temporary private key
    unsigned char PB[65]; // B's permanent public key
    unsigned char RB[65]; // B's temporary public key
    unsigned char dB[32]; // B's permanent private key
    unsigned char rB[32]; // B's temporary private key
    unsigned int  i       = 0u;
    unsigned int  round_1 = SM2_SPEED_TEST_EXCHANGE_ROUND;
    unsigned int  round;
    unsigned int  ret;

    // random key exchange test
    // a small loop for sleeping
    for (i = 0u; i < 5u; i++) {
        ret = sm2_getkey(dA, PA);
        ret |= sm2_getkey(rA, RA);
        ret |= sm2_getkey(dB, PB);
        ret |= sm2_getkey(rB, RB);
        if (SM2_SUCCESS != ret) {
            printf("\r\n get key failure");
            return 1;
        }
    }

    memset_(KA, 0x11, 16);
    memset_(KB, 0x55, 16);
    memset_(S1, 0x11, 32);
    memset_(S2, 0x55, 32);
    memset_(SA, 0x11, 32);
    memset_(SB, 0x55, 32);

    // sm2_exchangekey speed test
    round = round_1 / 2;
    ret   = 0;
    printf("\r\n\r\n ======== sm2_exchangekey begin ======== ");
    fflush(stdout);

#ifdef SM2_SPEED_TEST_BY_TIMER
    round /= 10;
    startp();
#endif

    for (i = 0; i < round; i++) {
        ret |= sm2_exchangekey(SM2_Role_Sponsor, dA, PB, rA, RA, RB, ZA, ZB, 16, KA, S1, SA);
    }

#ifdef SM2_SPEED_TEST_BY_TIMER
    endp(1, 0, round);
#else
    printf("\r\n sm2_exchangekey finished");
    fflush(stdout);
#endif

    if (SM2_SUCCESS != ret) {
        printf("\r\n sm2_exchangekey test error. ret=%u", ret);
    }

    ret |= sm2_exchangekey(SM2_Role_Responsor, dB, PA, rB, RB, RA, ZB, ZA, 16, KB, S2, SB);
    if ((SM2_SUCCESS != ret) || memcmp_(KA, KB, 16) || memcmp_(S1, SB, 32) || memcmp_(S2, SA, 32)) {
        printf("\r\n SM2 key exchange test error. ret=%u", ret);
        print_buf_u8(KA, 16, "KA");
        print_buf_u8(S1, 32, "S1");
        print_buf_u8(SA, 32, "SA");
        print_buf_u8(KB, 16, "KB");
        print_buf_u8(S2, 32, "S2");
        print_buf_u8(SB, 32, "SB");
        return 1;
    }

    return 0;
}

/**
 * @brief           SM2   get key test internal function
 * @param[in]       prikey               - Private key
 * @param[in]       pubkey               - Public key
 * @param[in]       ret_value            - Expected return value
 * @param[in]       info                 - Test information
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_get_key_test_internal(unsigned char *prikey, unsigned char *pubkey, unsigned int ret_value, char *info)
{
    unsigned char buf[65];
    unsigned int  ret;

    ret = sm2_get_pubkey_from_prikey(prikey, buf);
    if ((ret_value != ret)) {
        printf("\r\n SM2 get key %s failure 1, ret=%u", info, ret);
        fflush(stdout);
        return 1;
    }
    if ((SM2_SUCCESS == ret) && memcmp_(buf, pubkey, 65)) {
        printf("\r\n SM2 get key %s failure 2, ret=%u", info, ret);
        fflush(stdout);
        print_buf_u8(prikey, 32, "std prikey");
        print_buf_u8(pubkey, 65, "std pubkey");
        print_buf_u8(buf, 65, "pubkey");
        return 1;
    }

    printf("\r\n SM2 get key %s success", info);
    fflush(stdout);

    return 0;
}

/**
 * @brief           SM2   get key test function
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_get_key_test(void)
{
    // standard private key and public key
    unsigned char prikey[32] = {
        0x39, 0x45, 0x20, 0x8F, 0x7B, 0x21, 0x44, 0xB1, 0x3F, 0x36, 0xE3, 0x8A, 0xC6, 0xD3, 0x9F, 0x95,
        0x88, 0x93, 0x93, 0x69, 0x28, 0x60, 0xB5, 0x1A, 0x42, 0xFB, 0x81, 0xEF, 0x4D, 0xF7, 0xC5, 0xB8,
    };
    unsigned char pubkey[65] = {
        0x04, 0x09, 0xF9, 0xDF, 0x31, 0x1E, 0x54, 0x21, 0xA1, 0x50, 0xDD, 0x7D, 0x16, 0x1E, 0x4B, 0xC5, 0xC6, 0x72, 0x17, 0x9F, 0xAD, 0x18,
        0x33, 0xFC, 0x07, 0x6B, 0xB0, 0x8F, 0xF3, 0x56, 0xF3, 0x50, 0x20, 0xCC, 0xEA, 0x49, 0x0C, 0xE2, 0x67, 0x75, 0xA5, 0x2D, 0xC6, 0xEA,
        0x71, 0x8C, 0xC1, 0xAA, 0x60, 0x0A, 0xED, 0x05, 0xFB, 0xF3, 0x5E, 0x08, 0x4A, 0x66, 0x32, 0xF6, 0x07, 0x2D, 0xA9, 0xAD, 0x13,
    };

    // public key for the case private key is 1
    unsigned char pubkey_1[65] = {
        0x04, 0x32, 0xC4, 0xAE, 0x2C, 0x1F, 0x19, 0x81, 0x19, 0x5F, 0x99, 0x04, 0x46, 0x6A, 0x39, 0xC9, 0x94, 0x8F, 0xE3, 0x0B, 0xBF, 0xF2,
        0x66, 0x0B, 0xE1, 0x71, 0x5A, 0x45, 0x89, 0x33, 0x4C, 0x74, 0xC7, 0xBC, 0x37, 0x36, 0xA2, 0xF4, 0xF6, 0x77, 0x9C, 0x59, 0xBD, 0xCE,
        0xE3, 0x6B, 0x69, 0x21, 0x53, 0xD0, 0xA9, 0x87, 0x7C, 0xC6, 0x2A, 0x47, 0x40, 0x02, 0xDF, 0x32, 0xE5, 0x21, 0x39, 0xF0, 0xA0,
    };

    // public key for the case private key is 2
    unsigned char pubkey_2[65] = {
        0x04, 0x56, 0xCE, 0xFD, 0x60, 0xD7, 0xC8, 0x7C, 0x00, 0x0D, 0x58, 0xEF, 0x57, 0xFA, 0x73, 0xBA, 0x4D, 0x9C, 0x0D, 0xFA, 0x08, 0xC0,
        0x8A, 0x73, 0x31, 0x49, 0x5C, 0x2E, 0x1D, 0xA3, 0xF2, 0xBD, 0x52, 0x31, 0xB7, 0xE7, 0xE6, 0xCC, 0x81, 0x89, 0xF6, 0x68, 0x53, 0x5C,
        0xE0, 0xF8, 0xEA, 0xF1, 0xBD, 0x6D, 0xE8, 0x4C, 0x18, 0x2F, 0x6C, 0x8E, 0x71, 0x6F, 0x78, 0x0D, 0x3A, 0x97, 0x0A, 0x23, 0xC3,
    };

    // public key for the case private key is n-2
    unsigned char pubkey_n_minus_2[65] = {
        0x04, 0x56, 0xCE, 0xFD, 0x60, 0xD7, 0xC8, 0x7C, 0x00, 0x0D, 0x58, 0xEF, 0x57, 0xFA, 0x73, 0xBA, 0x4D, 0x9C, 0x0D, 0xFA, 0x08, 0xC0,
        0x8A, 0x73, 0x31, 0x49, 0x5C, 0x2E, 0x1D, 0xA3, 0xF2, 0xBD, 0x52, 0xCE, 0x48, 0x18, 0x18, 0x33, 0x7E, 0x76, 0x09, 0x97, 0xAC, 0xA3,
        0x1F, 0x07, 0x15, 0x0E, 0x42, 0x92, 0x17, 0xB3, 0xE6, 0xD0, 0x93, 0x71, 0x8F, 0x90, 0x87, 0xF2, 0xC5, 0x68, 0xF5, 0xDC, 0x3C,
    };

    printf("\r\n -------------- SM2 get key test -------------- ");
    fflush(stdout);

    /********** sm2 get key standard data test **********/
    if (sm2_get_key_test_internal(prikey, pubkey, SM2_SUCCESS, "standard data test")) {
        return 1;
    }

    /********** prikey is 0 **********/
    memset_(prikey, 0, 32);
    if (sm2_get_key_test_internal(prikey, NULL, PKE_ZERO_ALL, "test(prikey=0)")) {
        return 1;
    }

    /********** prikey is 1 **********/
    memset_(prikey, 0, 32);
    prikey[31] = 1;
    if (sm2_get_key_test_internal(prikey, pubkey_1, SM2_SUCCESS, "test(prikey=1)")) {
        return 1;
    }

    /********** prikey is 2 **********/
    memset_(prikey, 0, 32);
    prikey[31] = 2;
    if (sm2_get_key_test_internal(prikey, pubkey_2, SM2_SUCCESS, "test(prikey=2)")) {
        return 1;
    }

    /********** prikey is n-2 **********/
    reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), prikey, 32);
    prikey[31] -= 2;
    if (sm2_get_key_test_internal(prikey, pubkey_n_minus_2, SM2_SUCCESS, "test(prikey=n-2)")) {
        return 1;
    }

    /********** prikey is n-1 **********/
    reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), prikey, 32);
    prikey[31] -= 1;
    if (sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n-1)")) {
        return 1;
    }

    /********** prikey is n **********/
    reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), prikey, 32);
    if (sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n)")) {
        return 1;
    }

    /********** prikey is n+1 **********/
    reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), prikey, 32);
    prikey[31] += 1;
    if (sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n+1)")) {
        return 1;
    } else {
        printf("\r\n");
        return 0;
    }
}

/**
 * @brief           SM2   signature verification test internal function
 * @param[in]       E                    - Message hash
 * @param[in]       prikey               - Private key
 * @param[in]       rand_k               - Random number k
 * @param[in]       pubkey               - Public key
 * @param[in]       signature            - Signature
 * @param[in]       sign_ret_value       - Expected return value
 * @param[in]       info                 - Test information
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_sign_verify_test_internal(unsigned char *E, unsigned char *prikey, unsigned char *rand_k, unsigned char *pubkey, unsigned char *signature,
                                           unsigned int sign_ret_value, char *info)
{
    unsigned char buf[64];
    unsigned char buf2[64];
    unsigned char tmp[65];
    unsigned int  ret;
    char         *inf = "";

    if (info) {
        inf = info;
    }

    ret = sm2_sign(E, rand_k, prikey, buf);
    if ((sign_ret_value != ret)) {
        printf("\r\n SM2 sign %s failure, ret=%u", inf, ret);
        return 1;
    }

    if (SM2_SUCCESS == ret) {
        if ((NULL != rand_k) && (NULL != signature)) {
            if (memcmp_(buf, signature, 64)) {
                printf("\r\n SM2 sign %s failure, ret=%u", inf, ret);
                print_buf_u8(buf, 64, "signature");
                return 1;
            }
        }

        ret = sm2_verify(E, pubkey, buf);
        if (SM2_SUCCESS != ret) {
            printf("\r\n SM2 verify %s failure, ret=%u", inf, ret);
            print_buf_u8(buf, 64, "signature");
            return 1;
        }

        // invalid r (conner case:r=0)
        if (rand_k) {
            memcpy_(buf, rand_k, SM2_BYTE_LEN);
        } else {
            ret    = get_rand((unsigned char *)buf, SM2_BYTE_LEN);
            buf[0] = 0x7F;
            if (TRNG_SUCCESS != ret) {
                return 1;
            }
        }

#ifdef PKE_BIG_ENDIAN
        reverse_word_array(buf, tmp, SM2_WORD_LEN);
#else
        reverse_byte_array(buf, tmp, SM2_BYTE_LEN);
#endif
        ret = eccp_pointmul(sm2_curve, (unsigned int *)tmp, sm2_curve->eccp_Gx, sm2_curve->eccp_Gy, (unsigned int *)tmp, NULL);
        ret |= pke_mod((unsigned int *)tmp, SM2_WORD_LEN, sm2_curve->eccp_n, sm2_curve->eccp_n_h, sm2_curve->eccp_n_n0, SM2_WORD_LEN, (unsigned int *)tmp);
        if (0 == uint32_bignum_check_zero((unsigned int *)tmp, SM2_WORD_LEN)) {
            ret |= pke_sub(sm2_curve->eccp_n, (unsigned int *)tmp, (unsigned int *)tmp, SM2_WORD_LEN);
        }
        if (PKE_SUCCESS != ret) {
            printf("\r\n invalid r (conner case:r=0) failure, ret=%u", ret);
            return 1;
        } else {
        }

#ifdef PKE_BIG_ENDIAN
        reverse_word_array(tmp, tmp, SM2_WORD_LEN);
#else
        reverse_byte_array(tmp, tmp, SM2_BYTE_LEN);
#endif

        ret = sm2_sign(tmp, buf, prikey, tmp);
        if (SM2_ZERO_ALL != ret) {
            printf("\r\n SM2 sign %s failure(invalid r 1), ret=%u", inf, ret);
            print_buf_u8(tmp, 64, "signature");
            return 1;
        }

// invalid r (conner case:r+k=n)
#ifdef PKE_BIG_ENDIAN
        reverse_word_array(buf, tmp, SM2_WORD_LEN);
        reverse_word_array(buf, buf, SM2_WORD_LEN);
#else
        reverse_byte_array(buf, tmp, SM2_BYTE_LEN);
        reverse_byte_array(buf, buf, SM2_BYTE_LEN);
#endif

        ret = eccp_pointmul(sm2_curve, (unsigned int *)tmp, sm2_curve->eccp_Gx, sm2_curve->eccp_Gy, (unsigned int *)tmp, NULL);
        ret |= pke_mod((unsigned int *)tmp, SM2_WORD_LEN, sm2_curve->eccp_n, sm2_curve->eccp_n_h, sm2_curve->eccp_n_n0, SM2_WORD_LEN, (unsigned int *)tmp);
        ret |= pke_sub(sm2_curve->eccp_n, (unsigned int *)buf, (unsigned int *)buf2,
                       SM2_WORD_LEN);                                                                                       // buf2 = -k = r
        ret |= pke_modsub(sm2_curve->eccp_n, (unsigned int *)buf2, (unsigned int *)tmp, (unsigned int *)tmp, SM2_WORD_LEN); // tmp = e
        if (PKE_SUCCESS != ret) {
            printf("\r\n invalid r (conner case:r+k=n) failure, ret=%u", ret);
            return 1;
        } else {
        }

#ifdef PKE_BIG_ENDIAN
        reverse_word_array(tmp, tmp, SM2_WORD_LEN);
        reverse_word_array(buf, buf, SM2_WORD_LEN);
#else
        reverse_byte_array(tmp, tmp, SM2_BYTE_LEN);
        reverse_byte_array(buf, buf, SM2_BYTE_LEN);
#endif

        ret = sm2_sign(tmp, buf, prikey, tmp);
        if (SM2_ZERO_ALL != ret) {
            printf("\r\n SM2 sign %s failure(invalid r 2), ret=%u", inf, ret);
            print_buf_u8(tmp, 64, "signature");
            return 1;
        }

// invalid r (conner case:s=0, dA=k*r(-1) mod n)
#ifdef PKE_BIG_ENDIAN
        reverse_word_array(buf, tmp, SM2_WORD_LEN);
        reverse_word_array(buf, buf, SM2_WORD_LEN);
        reverse_word_array(E, buf2, SM2_WORD_LEN);
#else
        reverse_byte_array(buf, tmp, SM2_BYTE_LEN);
        reverse_byte_array(buf, buf, SM2_BYTE_LEN);
        reverse_byte_array(E, buf2, SM2_BYTE_LEN);
#endif

        ret = pke_mod((unsigned int *)buf2, SM2_WORD_LEN, sm2_curve->eccp_n, sm2_curve->eccp_n_h, sm2_curve->eccp_n_n0, SM2_WORD_LEN, (unsigned int *)buf2);
        ret |= eccp_pointmul(sm2_curve, (unsigned int *)tmp, sm2_curve->eccp_Gx, sm2_curve->eccp_Gy, (unsigned int *)tmp, NULL);
        ret |= pke_mod((unsigned int *)tmp, SM2_WORD_LEN, sm2_curve->eccp_n, sm2_curve->eccp_n_h, sm2_curve->eccp_n_n0, SM2_WORD_LEN, (unsigned int *)tmp);
        ret |= pke_modadd(sm2_curve->eccp_n, (unsigned int *)tmp, (unsigned int *)buf2, (unsigned int *)tmp, SM2_WORD_LEN);
        ret |= pke_modinv(sm2_curve->eccp_n, (unsigned int *)tmp, (unsigned int *)tmp, SM2_WORD_LEN, SM2_WORD_LEN);
        ret |= pke_modmul(sm2_curve->eccp_n, (unsigned int *)tmp, (unsigned int *)buf, (unsigned int *)tmp, SM2_WORD_LEN);
        if (PKE_SUCCESS != ret) {
            printf("\r\n invalid r (conner case:s=0) failure, ret=%u", ret);
            return 1;
        } else {
        }

#ifdef PKE_BIG_ENDIAN
        reverse_word_array(tmp, tmp, SM2_WORD_LEN);
        reverse_word_array(buf, buf, SM2_WORD_LEN);
#else
        reverse_byte_array(tmp, tmp, SM2_BYTE_LEN);
        reverse_byte_array(buf, buf, SM2_BYTE_LEN);
#endif

        ret = sm2_sign(E, buf, tmp, buf);
        if (SM2_ZERO_ALL != ret) {
            printf("\r\n SM2 sign %s failure(invalid s), ret=%u", inf, ret);
            print_buf_u8(buf, 64, "signature");
            print_buf_u8(tmp, 32, "dA");
            return 1;
        }

        // invalid E
        memcpy_(tmp, E, 32);
        tmp[0] += 3;
        ret = sm2_verify(tmp, pubkey, buf);
        if (SM2_VERIFY_FAILED != ret) {
            printf("\r\n SM2 verify %s failure(invalid E), ret=%u", inf, ret);
            return 1;
        }

        // invalid pubkey test 1
        memcpy_(tmp, pubkey, 65);
        tmp[0] += 3;
        ret = sm2_verify(E, tmp, buf);
        if (SM2_INPUT_INVALID != ret) {
            printf("\r\n SM2 verify %s failure(invalid public key 1), ret=%u", inf, ret);
            return 1;
        }

        // invalid pubkey test 2
        memcpy_(tmp, pubkey, 65);
        tmp[1] += 3;
        ret = sm2_verify(E, tmp, buf);
        if (SM2_NOT_ON_CURVE != ret) {
            printf("\r\n SM2 verify %s failure(invalid public key 2), ret=%u", inf, ret);
            return 1;
        }

        // invalid pubkey test 3
        memcpy_(tmp, pubkey, 65);
        tmp[64] += 3;
        ret = sm2_verify(E, tmp, buf);
        if (SM2_NOT_ON_CURVE != ret) {
            printf("\r\n SM2 verify %s failure(invalid public key 3), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 1(corrupted r)
        memcpy_(tmp, buf, 64);
        tmp[0] += 3;
        ret = sm2_verify(E, pubkey, tmp);
        if ((SM2_VERIFY_FAILED != ret) && (SM2_INTEGER_TOO_BIG != ret)) {
            printf("\r\n SM2 verify %s failure(invalid signature: corrupted r), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 2(r=0)
        memcpy_(tmp, buf, 64);
        memset_(tmp, 0, 32);
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_ZERO_ALL != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: r=0), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 3(r=n-1)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp, 32);
        tmp[31] -= 1;
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_VERIFY_FAILED != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: r=n-1), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 4(r=n)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp, 32);
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_INTEGER_TOO_BIG != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: r=n), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 5(r=n+1)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp, 32);
        tmp[31] += 1;
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_INTEGER_TOO_BIG != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: r=n+1), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 6(corrupted s)
        memcpy_(tmp, buf, 64);
        tmp[63] += 3;
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_VERIFY_FAILED != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: corrupted s), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 7(s=0)
        memcpy_(tmp, buf, 64);
        memset_(tmp + 32, 0, 32);
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_ZERO_ALL != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: s=0), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 8(s=n-1)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp + 32, 32);
        tmp[63] -= 1;
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_VERIFY_FAILED != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: s=n-1), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 9(s=n)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp + 32, 32);
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_INTEGER_TOO_BIG != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: s=n), ret=%u", inf, ret);
            return 1;
        }

        // invalid signature test 10(s=n+1)
        memcpy_(tmp, buf, 64);
        reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), tmp + 32, 32);
        tmp[63] += 1;
        ret = sm2_verify(E, pubkey, tmp);
        if (SM2_INTEGER_TOO_BIG != ret) {
            printf("\r\n SM2 verify %s failure(invalid signature: r=n+1), ret=%u", inf, ret);
            return 1;
        }
    }

    if (NULL != info) {
        printf("\r\n SM2 sign & verify %s success", inf);
    }

    return 0;
}

/**
 * @brief           SM2   signature verification test
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_sign_verify_test(void)
{
    unsigned char prikey[32] = {
        0x39, 0x45, 0x20, 0x8F, 0x7B, 0x21, 0x44, 0xB1, 0x3F, 0x36, 0xE3, 0x8A, 0xC6, 0xD3, 0x9F, 0x95,
        0x88, 0x93, 0x93, 0x69, 0x28, 0x60, 0xB5, 0x1A, 0x42, 0xFB, 0x81, 0xEF, 0x4D, 0xF7, 0xC5, 0xB8,
    };
    unsigned char pubkey[65] = {
        0x04, 0x09, 0xF9, 0xDF, 0x31, 0x1E, 0x54, 0x21, 0xA1, 0x50, 0xDD, 0x7D, 0x16, 0x1E, 0x4B, 0xC5, 0xC6, 0x72, 0x17, 0x9F, 0xAD, 0x18,
        0x33, 0xFC, 0x07, 0x6B, 0xB0, 0x8F, 0xF3, 0x56, 0xF3, 0x50, 0x20, 0xCC, 0xEA, 0x49, 0x0C, 0xE2, 0x67, 0x75, 0xA5, 0x2D, 0xC6, 0xEA,
        0x71, 0x8C, 0xC1, 0xAA, 0x60, 0x0A, 0xED, 0x05, 0xFB, 0xF3, 0x5E, 0x08, 0x4A, 0x66, 0x32, 0xF6, 0x07, 0x2D, 0xA9, 0xAD, 0x13,
    };
    unsigned char rand_k[32] = {
        0x59, 0x27, 0x6E, 0x27, 0xD5, 0x06, 0x86, 0x1A, 0x16, 0x68, 0x0F, 0x3A, 0xD9, 0xC0, 0x2D, 0xCC,
        0xEF, 0x3C, 0xC1, 0xFA, 0x3C, 0xDB, 0xE4, 0xCE, 0x6D, 0x54, 0xB8, 0x0D, 0xEA, 0xC1, 0xBC, 0x21,
    };
    //"message digest"
    unsigned char msg[100] = {0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x64, 0x69, 0x67, 0x65, 0x73, 0x74};
    //"1234567812345678"
    unsigned char id[16]  = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
    unsigned char std_Z[] = {
        0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B, 0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26,
        0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9, 0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3,
    };
    unsigned char std_E[] = {
        0xF0, 0xB4, 0x3E, 0x94, 0xBA, 0x45, 0xAC, 0xCA, 0xAC, 0xE6, 0x92, 0xED, 0x53, 0x43, 0x82, 0xEB,
        0x17, 0xE6, 0xAB, 0x5A, 0x19, 0xCE, 0x7B, 0x31, 0xF4, 0x48, 0x6F, 0xDF, 0xC0, 0xD2, 0x86, 0x40,
    };
    unsigned char std_signature[64] = {
        0xF5, 0xA0, 0x3B, 0x06, 0x48, 0xD2, 0xC4, 0x63, 0x0E, 0xEA, 0xC5, 0x13, 0xE1, 0xBB, 0x81, 0xA1, 0x59, 0x44, 0xDA, 0x38, 0x27, 0xD5,
        0xB7, 0x41, 0x43, 0xAC, 0x7E, 0xAC, 0xEE, 0xE7, 0x20, 0xB3, 0xB1, 0xB6, 0xAA, 0x29, 0xDF, 0x21, 0x2F, 0xD8, 0x76, 0x31, 0x82, 0xBC,
        0x0D, 0x42, 0x1C, 0xA1, 0xBB, 0x90, 0x38, 0xFD, 0x1F, 0x7F, 0x42, 0xD4, 0x84, 0x0B, 0x69, 0xC4, 0x85, 0xBB, 0xC1, 0xAA,
    };
    unsigned char *k;
    unsigned char  Z[32], E[32];

    // e=0
    unsigned char signature_e_0[64] = {0x04, 0xEB, 0xFC, 0x71, 0x8E, 0x8D, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8E, 0x77, 0xFE, 0xB6, 0x41, 0x5E, 0x2E, 0xDE, 0x0E, 0x07,
                                       0x3C, 0x0F, 0x4F, 0x64, 0x0E, 0xCD, 0x2E, 0x14, 0x9A, 0x73, 0x74, 0x0F, 0x49, 0x4C, 0x6B, 0x9D, 0xCC, 0xA0, 0x75, 0x8F, 0xD4, 0xCF,
                                       0x0E, 0xAA, 0x8B, 0xA8, 0xCD, 0x76, 0xE9, 0xB7, 0xE4, 0xFD, 0x91, 0x6F, 0x7C, 0x48, 0x41, 0x68, 0xF6, 0xA4, 0xB3, 0x8F};

    // e=1
    unsigned char signature_e_1[64] = {0x04, 0xEB, 0xFC, 0x71, 0x8E, 0x8D, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8E, 0x77, 0xFE, 0xB6, 0x41, 0x5E, 0x2E, 0xDE, 0x0E, 0x07,
                                       0x3C, 0x0F, 0x4F, 0x64, 0x0E, 0xCD, 0x2E, 0x14, 0x9A, 0x74, 0xC2, 0x0D, 0xE6, 0xE8, 0x8A, 0xF6, 0xCE, 0x75, 0x5C, 0x85, 0x63, 0x1D,
                                       0xD2, 0x7A, 0xD1, 0x10, 0x4F, 0xA4, 0x0F, 0x08, 0xDE, 0xB6, 0x1F, 0xF1, 0xE9, 0x63, 0x9C, 0xA3, 0xB0, 0x71, 0xC3, 0x6E};

    // e=n
    unsigned char signature_e_n[64] = {0x04, 0xEB, 0xFC, 0x71, 0x8E, 0x8D, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8E, 0x77, 0xFE, 0xB6, 0x41, 0x5E, 0x2E, 0xDE, 0x0E, 0x07,
                                       0x3C, 0x0F, 0x4F, 0x64, 0x0E, 0xCD, 0x2E, 0x14, 0x9A, 0x73, 0x74, 0x0F, 0x49, 0x4C, 0x6B, 0x9D, 0xCC, 0xA0, 0x75, 0x8F, 0xD4, 0xCF,
                                       0x0E, 0xAA, 0x8B, 0xA8, 0xCD, 0x76, 0xE9, 0xB7, 0xE4, 0xFD, 0x91, 0x6F, 0x7C, 0x48, 0x41, 0x68, 0xF6, 0xA4, 0xB3, 0x8F};

    // e=0xFFF...FFF
    unsigned char signature_e_FF[64] = {0x04, 0xEB, 0xFC, 0x72, 0x8E, 0x8D, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8E, 0x77, 0xFE, 0xB6, 0xCF, 0x5A, 0x4F, 0x72, 0xEC, 0x41,
                                        0x36, 0xE3, 0xFB, 0xA8, 0x1A, 0xC3, 0xF4, 0x3F, 0x59, 0x4F, 0xC8, 0x26, 0x83, 0x8A, 0x13, 0x67, 0x62, 0xB3, 0x6B, 0xD9, 0x88, 0xEF,
                                        0xC2, 0xC6, 0x5E, 0x76, 0xEB, 0xE3, 0x77, 0x4C, 0xD3, 0xE8, 0x08, 0x1F, 0xE1, 0xAA, 0x0A, 0x76, 0x14, 0x30, 0xAB, 0x2C};

    unsigned int i, j;
    unsigned int ret;
#ifdef SM2_GETE_BY_STEPS
    hash_ctx_t ctx[1];
#endif

    printf("\r\n -------------- SM2 get Z, E, key, sign and verify test "
           "-------------- ");

    /********** sm2 get Z standard data test **********/
    ret = sm2_getZ(id, 16, pubkey, Z);
    if (SM2_SUCCESS != ret || memcmp_(Z, std_Z, 32)) {
        printf("\r\n SM2 get Z standard data test failure, ret=%u", ret);
        return 1;
    } else {
        printf("\r\n SM2 get Z standard data test success");
    }

    /********** sm2 get E standard data test **********/
    ret = sm2_getE(msg, 14, Z, E);
    if (SM2_SUCCESS != ret || memcmp_(E, std_E, 32)) {
        printf("\r\n SM2 get E standard data test failure, ret=%u", ret);
        return 1;
    } else {
        printf("\r\n SM2 get E standard data test success");
    }
#ifdef SM2_GETE_BY_STEPS
    memset_(E, 0, 32);
    ret = sm2_getE_init(ctx, Z);
    ret |= sm2_getE_update(ctx, msg, 1);
    ret |= sm2_getE_update(ctx, msg + 1, 3);
    ret |= sm2_getE_update(ctx, msg + 4, 5);
    ret |= sm2_getE_update(ctx, msg + 9, 3);
    ret |= sm2_getE_update(ctx, msg + 12, 2);
    ret |= sm2_getE_final(ctx, E);
    if (SM2_SUCCESS != ret || memcmp_(E, std_E, 32)) {
        printf("\r\n SM2 get E standard data stepwise test failure, ret=%u", ret);
        return 1;
    } else {
        printf("\r\n SM2 get E standard data stepwise test success");
    }
#endif

    /********** sm2 sign & verify standard data test **********/
    if (sm2_sign_verify_test_internal(std_E, prikey, rand_k, pubkey, std_signature, SM2_SUCCESS, "standard data test")) {
        return 1;
    }

    /********** e = 0 **********/
    memset_(E, 0, 32);
    if (sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_0, SM2_SUCCESS, "test(e=0)")) {
        return 1;
    }

    /********** e = 1 **********/
    memset_(E, 0, 32);
    E[31] = 1;
    if (sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_1, SM2_SUCCESS, "test(e=1)")) {
        return 1;
    }

    /********** e = n **********/
    reverse_byte_array((const unsigned char *)(sm2_curve->eccp_n), E, 32);
    if (sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_n, SM2_SUCCESS, "test(e=n)")) {
        return 1;
    }

    /********** e = 0xFF...FF **********/
    memset_(E, 0xFF, 32);
    if (sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_FF, SM2_SUCCESS, "test(e=0xFF...FF)")) {
        return 1;
    }

    /********* sm2 get key, sign, verify corner case and random test **********/
    printf("\r\n\r\n SM2 sign & verify random data test: \r\n");

    for (i = 0; i < SM2_SIGN_VERIFY_ROUND1; i++) {
        // random E
        ret = get_rand(E, 32);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 1, ret = %u", ret);
            return 1;
        }

        // set key pair
        if (0 == i) // corner case 1: key pair is (1, G)
        {
            memset_(prikey, 0, 32);
            prikey[32 - 1] = 0x01;
            pubkey[0]      = POINT_UNCOMPRESSED;
            ret            = eccp_get_pubkey_from_prikey(sm2_curve, prikey, pubkey + 1);
            if (PKE_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 1, ret=%u", ret);
                return 1;
            }
        } else if (1 == i) // corner case 2: key pair is (n-2, [n-2]G)   caution:
                           // private key can not be n-1
        {
            reverse_byte_array((const unsigned char *)sm2_curve->eccp_n, prikey, 32);
            prikey[32 - 1] -= 0x02;
            pubkey[0] = POINT_UNCOMPRESSED;
            ret       = eccp_get_pubkey_from_prikey(sm2_curve, prikey, pubkey + 1);
            if (PKE_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 2, ret=%u", ret);
                return 1;
            }
        } else // key pair is random
        {
            memset_(prikey, 0, 32);
            memset_(pubkey, 0, 65);
            ret = sm2_getkey(prikey, pubkey);
            if (SM2_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 3, ret=%u", ret);
                return 1;
            }
        }

        // random k
        if (prikey[0] > 0x80) {
            k = NULL;
        } else {
            k   = rand_k;
            ret = get_rand(k, 32);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get rand error 2, ret = %u", ret);
                return 1;
            }
            k[0] = 0x7F; // make sure k < n
        }

        for (j = 0; j < SM2_SIGN_VERIFY_ROUND2; j++) {
            printf("\r\n SM2 sign & verify round1=%u, round2=%u", i + 1, j + 1);

            if (sm2_sign_verify_test_internal(E, prikey, k, pubkey, NULL, SM2_SUCCESS, NULL)) {
                return 1;
            }
        }
    }
    fflush(stdout);

    return 0;
}

/**
 * @brief           SM2   encryption decryption test
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_encrypt_decrypt_test(void)
{
    unsigned char prikey[32] = {
        0x39, 0x45, 0x20, 0x8F, 0x7B, 0x21, 0x44, 0xB1, 0x3F, 0x36, 0xE3, 0x8A, 0xC6, 0xD3, 0x9F, 0x95,
        0x88, 0x93, 0x93, 0x69, 0x28, 0x60, 0xB5, 0x1A, 0x42, 0xFB, 0x81, 0xEF, 0x4D, 0xF7, 0xC5, 0xB8,
    };
    unsigned char pubkey[65] = {
        0x04, 0x09, 0xF9, 0xDF, 0x31, 0x1E, 0x54, 0x21, 0xA1, 0x50, 0xDD, 0x7D, 0x16, 0x1E, 0x4B, 0xC5, 0xC6, 0x72, 0x17, 0x9F, 0xAD, 0x18,
        0x33, 0xFC, 0x07, 0x6B, 0xB0, 0x8F, 0xF3, 0x56, 0xF3, 0x50, 0x20, 0xCC, 0xEA, 0x49, 0x0C, 0xE2, 0x67, 0x75, 0xA5, 0x2D, 0xC6, 0xEA,
        0x71, 0x8C, 0xC1, 0xAA, 0x60, 0x0A, 0xED, 0x05, 0xFB, 0xF3, 0x5E, 0x08, 0x4A, 0x66, 0x32, 0xF6, 0x07, 0x2D, 0xA9, 0xAD, 0x13,
    };
    unsigned char rand_k[32] = {
        0x59, 0x27, 0x6E, 0x27, 0xD5, 0x06, 0x86, 0x1A, 0x16, 0x68, 0x0F, 0x3A, 0xD9, 0xC0, 0x2D, 0xCC,
        0xEF, 0x3C, 0xC1, 0xFA, 0x3C, 0xDB, 0xE4, 0xCE, 0x6D, 0x54, 0xB8, 0x0D, 0xEA, 0xC1, 0xBC, 0x21,
    };

    unsigned char plain[SM2_PLAIN_MAX_LEN] = {
        0x65, 0x6E, 0x63, 0x72, 0x79, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x73, 0x74, 0x61, 0x6E, 0x64, 0x61, 0x72, 0x64,
    };
    // C1C3C2
    unsigned char      std_cipher[19 + 97] = {0x04, 0x04, 0xEB, 0xFC, 0x71, 0x8E, 0x8D, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8E, 0x77, 0xFE, 0xB6, 0x41, 0x5E, 0x2E,
                                              0xDE, 0x0E, 0x07, 0x3C, 0x0F, 0x4F, 0x64, 0x0E, 0xCD, 0x2E, 0x14, 0x9A, 0x73, 0xE8, 0x58, 0xF9, 0xD8, 0x1E, 0x54, 0x30,
                                              0xA5, 0x7B, 0x36, 0xDA, 0xAB, 0x8F, 0x95, 0x0A, 0x3C, 0x64, 0xE6, 0xEE, 0x6A, 0x63, 0x09, 0x4D, 0x99, 0x28, 0x3A, 0xFF,
                                              0x76, 0x7E, 0x12, 0x4D, 0xF0, 0x59, 0x98, 0x3C, 0x18, 0xF8, 0x09, 0xE2, 0x62, 0x92, 0x3C, 0x53, 0xAE, 0xC2, 0x95, 0xD3,
                                              0x03, 0x83, 0xB5, 0x4E, 0x39, 0xD6, 0x09, 0xD1, 0x60, 0xAF, 0xCB, 0x19, 0x08, 0xD0, 0xBD, 0x87, 0x66, 0x21, 0x88, 0x6C,
                                              0xA9, 0x89, 0xCA, 0x9C, 0x7D, 0x58, 0x08, 0x73, 0x07, 0xCA, 0x93, 0x09, 0x2D, 0x65, 0x1E, 0xFA};
    unsigned char      cipher[SM2_PLAIN_MAX_LEN + 97];
    unsigned char      replain[SM2_PLAIN_MAX_LEN + 97];
    unsigned char     *k;
    unsigned int       i, j, bytelen, bytelen2;
    sm2_cipher_order_e order = SM2_C1C3C2;
    unsigned int       ret;

    printf("\r\n\r\n -------------- SM2 encrypt & decrypt test -------------- ");

    /********** encrypt & decrypt standard data test **********/
    // standard data test 1
    ret = sm2_encrypt(plain, 19, rand_k, pubkey, SM2_C1C3C2, cipher, &bytelen);
    if ((SM2_SUCCESS != ret) || (bytelen != 19 + 97) || memcmp_(cipher, std_cipher, bytelen)) {
        printf("\r\n SM2 encrypt & decrypt standard data test 1 encrypt failure, "
               "ret=%u",
               ret);
        return 1;
    }
    memset_(replain, 0, sizeof(replain));
    ret = sm2_decrypt(cipher, bytelen, prikey, SM2_C1C3C2, replain, &bytelen2);
    if ((SM2_SUCCESS != ret) || (19 != bytelen2) || memcmp_(plain, replain, bytelen2)) {
        printf("\r\n SM2 encrypt & decrypt standard data test 1 failure, ret=%u", ret);
        return 1;
    }

    // transform to C1C2C3
    memcpy_(replain, std_cipher + 65, 32); // store C3
    memcpy_(std_cipher + 65, std_cipher + 65 + 32, 19);
    memcpy_(std_cipher + 65 + 19, replain, 32);

    // standard data test 2
    memset_(cipher, 0x11, sizeof(cipher));
    ret = sm2_encrypt(plain, 19, rand_k, pubkey, SM2_C1C2C3, cipher, &bytelen);
    if ((SM2_SUCCESS != ret) || (bytelen != 19 + 97) || memcmp_(cipher, std_cipher, bytelen)) {
        printf("\r\n SM2 encrypt & decrypt standard data test 2 encrypt failure, "
               "ret=%u",
               ret);
        return 1;
    }
    memset_(replain, 0, sizeof(replain));
    ret = sm2_decrypt(cipher, bytelen, prikey, SM2_C1C2C3, replain, &bytelen2);
    if ((SM2_SUCCESS != ret) || (19 != bytelen2) || memcmp_(plain, replain, bytelen2)) {
        printf("\r\n SM2 encrypt & decrypt standard data test 2 decrypt failure, "
               "ret=%u",
               ret);
        return 1;
    }
    printf("\r\n SM2 encrypt & decrypt standard data test success");

    /********** encrypt & decrypt corner case and random data test **********/
    printf("\r\n\r\n SM2 encrypt & decrypt random data test: \r\n");
    for (i = 0; i < SM2_ENCRYPT_DECRYPT_ROUND1; i++) {
        // set key pair
        if (0 == i) // corner case 1: key pair is (1, G)
        {
            memset_(prikey, 0, 32);
            prikey[32 - 1] = 0x01;
            pubkey[0]      = POINT_UNCOMPRESSED;
            ret            = eccp_get_pubkey_from_prikey(sm2_curve, prikey, pubkey + 1);
            if (PKE_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 1, ret=%u", ret);
                return 1;
            }
        } else if (1 == i) // corner case 2: key pair is (n-2, [n-2]G)   caution:
                           // private key can not be n-1
        {
            reverse_byte_array((const unsigned char *)sm2_curve->eccp_n, prikey, 32);
            prikey[32 - 1] -= 0x02;
            pubkey[0] = POINT_UNCOMPRESSED;
            ret       = eccp_get_pubkey_from_prikey(sm2_curve, prikey, pubkey + 1);
            if (PKE_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 2, ret=%u", ret);
                return 1;
            }
        } else // key pair is random
        {
            memset_(prikey, 0, 32);
            memset_(pubkey, 0, 65);
            ret = sm2_getkey(prikey, pubkey);
            if (SM2_SUCCESS != ret) {
                printf("\r\n sm2 get key failure 3, ret=%u", ret);
                return 1;
            }
        }

        // random plaintext
        ret = get_rand(plain, SM2_PLAIN_MAX_LEN);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error 1, ret = %u", ret);
            return 1;
        }

        // random order
        order ^= (plain[0] + plain[1] + plain[2]) & 1;

        // random k
        if (plain[0] > 0x80) {
            k = NULL;
        } else {
            k   = rand_k;
            ret = get_rand(k, 32);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get rand error 2, ret = %u", ret);
                return 1;
            }
            k[0] = 0x7F; // make sure k < n
        }

        // here plaintext length starts with value 10 bytes, since the encryption
        // would fail if the length is small (the internal stream key is zero, this
        // results in failure). for example, if the plaintext is 1 byte, then the
        // probability that 8 bits are all zero is 1/256 if the internal stream key
        // is uniform random. in practice. if plaintext is short, and the encryption
        // interface return failure(e.g. sm2_encrypt returns SM2_ZERO_ALL), it is
        // normal, try again until it return success.
        for (j = 10; j <= SM2_PLAIN_MAX_LEN; j++) {
            printf("\r\n SM2 encrypt & decrypt round1=%u, plaintext byte "
                   "length=%u, order=%u",
                   i + 1, j, (unsigned int)order);

            if (j & 1) {
                ret = sm2_encrypt(plain, j, k, pubkey, order, cipher, &bytelen);
            } else {
                memcpy_(cipher, plain, j);
                ret = sm2_encrypt(cipher, j, k, pubkey, order, cipher, &bytelen);
            }
            if ((SM2_SUCCESS != ret) || (j + 97 != bytelen)) {
                print_buf_u8(plain, j, "plain");
                print_buf_u8(prikey, 32, "prikey");
                print_buf_u8(pubkey, 65, "pubkey");
                if (k) {
                    print_buf_u8(k, 32, "k");
                }
                print_buf_u8(cipher, bytelen, "cipher");
                printf("\r\n encrypt failure, ret = %u", ret);
                return 1;
            }

            if (j & 1) {
                memset_(replain, 0, sizeof(replain));
                ret = sm2_decrypt(cipher, bytelen, prikey, order, replain, &bytelen2);
            } else {
                memcpy_(replain, cipher, bytelen);
                ret = sm2_decrypt(replain, bytelen, prikey, order, replain, &bytelen2);
            }
            if ((SM2_SUCCESS != ret) || (j != bytelen2) || memcmp_(plain, replain, bytelen2)) {
                print_buf_u8(plain, j, "plain");
                print_buf_u8(cipher, bytelen, "cipher");
                print_buf_u8(prikey, 32, "prikey");
                print_buf_u8(pubkey, 65, "pubkey");
                printf("\r\n decrypt failure, ret = %u", ret);
                return 1;
            } else {
                // printf("\r\n decrypt pass");
            }
        }
    }

    fflush(stdout);

    return 0;
}

/**
 * @brief           SM2   key exchange test
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_key_exchange_test(void)
{
    unsigned char KA[(SM2_EXCHANGE_MAX_LEN > 65) ? SM2_EXCHANGE_MAX_LEN : 65];
    unsigned char KB[(SM2_EXCHANGE_MAX_LEN > 65) ? SM2_EXCHANGE_MAX_LEN : 65];
    unsigned char S1[32], SA[32], S2[32], SB[32];

    unsigned char ZA[32] = {
        0x3B, 0x85, 0xA5, 0x71, 0x79, 0xE1, 0x1E, 0x7E, 0x51, 0x3A, 0xA6, 0x22, 0x99, 0x1F, 0x2C, 0xA7,
        0x4D, 0x18, 0x07, 0xA0, 0xBD, 0x4D, 0x4B, 0x38, 0xF9, 0x09, 0x87, 0xA1, 0x7A, 0xC2, 0x45, 0xB1,
    };
    unsigned char ZB[32] = {
        0x79, 0xC9, 0x88, 0xD6, 0x32, 0x29, 0xD9, 0x7E, 0xF1, 0x9F, 0xE0, 0x2C, 0xA1, 0x05, 0x6E, 0x01,
        0xE6, 0xA7, 0x41, 0x1E, 0xD2, 0x46, 0x94, 0xAA, 0x8F, 0x83, 0x4F, 0x4A, 0x4A, 0xB0, 0x22, 0xF7,
    };

    // A' ID
    unsigned char IDa[16] = {
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    };
    // A' permanent public key
    unsigned char PA[65] = {
        0x04, 0x16, 0x0E, 0x12, 0x89, 0x7D, 0xF4, 0xED, 0xB6, 0x1D, 0xD8, 0x12, 0xFE, 0xB9, 0x67, 0x48, 0xFB, 0xD3, 0xCC, 0xF4, 0xFF, 0xE2,
        0x6A, 0xA6, 0xF6, 0xDB, 0x95, 0x40, 0xAF, 0x49, 0xC9, 0x42, 0x32, 0x4A, 0x7D, 0xAD, 0x08, 0xBB, 0x9A, 0x45, 0x95, 0x31, 0x69, 0x4B,
        0xEB, 0x20, 0xAA, 0x48, 0x9D, 0x66, 0x49, 0x97, 0x5E, 0x1B, 0xFC, 0xF8, 0xC4, 0x74, 0x1B, 0x78, 0xB4, 0xB2, 0x23, 0x00, 0x7F,
    };
    // A's temporary public key
    unsigned char RA[65] = {
        0x04, 0x64, 0xCE, 0xD1, 0xBD, 0xBC, 0x99, 0xD5, 0x90, 0x04, 0x9B, 0x43, 0x4D, 0x0F, 0xD7, 0x34, 0x28, 0xCF, 0x60, 0x8A, 0x5D, 0xB8,
        0xFE, 0x5C, 0xE0, 0x7F, 0x15, 0x02, 0x69, 0x40, 0xBA, 0xE4, 0x0E, 0x37, 0x66, 0x29, 0xC7, 0xAB, 0x21, 0xE7, 0xDB, 0x26, 0x09, 0x22,
        0x49, 0x9D, 0xDB, 0x11, 0x8F, 0x07, 0xCE, 0x8E, 0xAA, 0xE3, 0xE7, 0x72, 0x0A, 0xFE, 0xF6, 0xA5, 0xCC, 0x06, 0x20, 0x70, 0xC0,
    };
    // A's permanent private key
    unsigned char dA[32] = {
        0x81, 0xEB, 0x26, 0xE9, 0x41, 0xBB, 0x5A, 0xF1, 0x6D, 0xF1, 0x16, 0x49, 0x5F, 0x90, 0x69, 0x52,
        0x72, 0xAE, 0x2C, 0xD6, 0x3D, 0x6C, 0x4A, 0xE1, 0x67, 0x84, 0x18, 0xBE, 0x48, 0x23, 0x00, 0x29,
    };
    // A's temporary private key
    unsigned char rA[32] = {
        0xD4, 0xDE, 0x15, 0x47, 0x4D, 0xB7, 0x4D, 0x06, 0x49, 0x1C, 0x44, 0x0D, 0x30, 0x5E, 0x01, 0x24,
        0x00, 0x99, 0x0F, 0x3E, 0x39, 0x0C, 0x7E, 0x87, 0x15, 0x3C, 0x12, 0xDB, 0x2E, 0xA6, 0x0B, 0xB3,
    };
    // B' ID
    unsigned char IDb[16] = {
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    };
    // B' permanent public key
    unsigned char PB[65] = {
        0x04, 0x6A, 0xE8, 0x48, 0xC5, 0x7C, 0x53, 0xC7, 0xB1, 0xB5, 0xFA, 0x99, 0xEB, 0x22, 0x86, 0xAF, 0x07, 0x8B, 0xA6, 0x4C, 0x64, 0x59,
        0x1B, 0x8B, 0x56, 0x6F, 0x73, 0x57, 0xD5, 0x76, 0xF1, 0x6D, 0xFB, 0xEE, 0x48, 0x9D, 0x77, 0x16, 0x21, 0xA2, 0x7B, 0x36, 0xC5, 0xC7,
        0x99, 0x20, 0x62, 0xE9, 0xCD, 0x09, 0xA9, 0x26, 0x43, 0x86, 0xF3, 0xFB, 0xEA, 0x54, 0xDF, 0xF6, 0x93, 0x05, 0x62, 0x1C, 0x4D,
    };
    // B's temporary public key
    unsigned char RB[65] = {
        0x04, 0xAC, 0xC2, 0x76, 0x88, 0xA6, 0xF7, 0xB7, 0x06, 0x09, 0x8B, 0xC9, 0x1F, 0xF3, 0xAD, 0x1B, 0xFF, 0x7D, 0xC2, 0x80, 0x2C, 0xDB,
        0x14, 0xCC, 0xCC, 0xDB, 0x0A, 0x90, 0x47, 0x1F, 0x9B, 0xD7, 0x07, 0x2F, 0xED, 0xAC, 0x04, 0x94, 0xB2, 0xFF, 0xC4, 0xD6, 0x85, 0x38,
        0x76, 0xC7, 0x9B, 0x8F, 0x30, 0x1C, 0x65, 0x73, 0xAD, 0x0A, 0xA5, 0x0F, 0x39, 0xFC, 0x87, 0x18, 0x1E, 0x1A, 0x1B, 0x46, 0xFE,
    };
    // B's permanent private key
    unsigned char dB[32] = {
        0x78, 0x51, 0x29, 0x91, 0x7D, 0x45, 0xA9, 0xEA, 0x54, 0x37, 0xA5, 0x93, 0x56, 0xB8, 0x23, 0x38,
        0xEA, 0xAD, 0xDA, 0x6C, 0xEB, 0x19, 0x90, 0x88, 0xF1, 0x4A, 0xE1, 0x0D, 0xEF, 0xA2, 0x29, 0xB5,
    };
    // B's temporary private key
    unsigned char rB[32] = {
        0x7E, 0x07, 0x12, 0x48, 0x14, 0xB3, 0x09, 0x48, 0x91, 0x25, 0xEA, 0xED, 0x10, 0x11, 0x13, 0x16,
        0x4E, 0xBF, 0x0F, 0x34, 0x58, 0xC5, 0xBD, 0x88, 0x33, 0x5C, 0x1F, 0x9D, 0x59, 0x62, 0x43, 0xD6,
    };
    unsigned char const std_key[16] = {
        0x6C, 0x89, 0x34, 0x73, 0x54, 0xDE, 0x24, 0x84, 0xC6, 0x0B, 0x4A, 0xB1, 0xFD, 0xE4, 0xC6, 0xE5,
    };
    unsigned char const std_S1_SB[32] = {0xD3, 0xA0, 0xFE, 0x15, 0xDE, 0xE1, 0x85, 0xCE, 0xAE, 0x90, 0x7A, 0x6B, 0x59, 0x5C, 0xC3, 0x2A,
                                         0x26, 0x6E, 0xD7, 0xB3, 0x36, 0x7E, 0x99, 0x83, 0xA8, 0x96, 0xDC, 0x32, 0xFA, 0x20, 0xF8, 0xEB};
    unsigned char const std_S2_SA[32] = {0x18, 0xC7, 0x89, 0x4B, 0x38, 0x16, 0xDF, 0x16, 0xCF, 0x07, 0xB0, 0x5C, 0x5E, 0xC0, 0xBE, 0xF5,
                                         0xD6, 0x55, 0xD5, 0x8F, 0x77, 0x9C, 0xC1, 0xB4, 0x00, 0xA4, 0xF3, 0x88, 0x46, 0x44, 0xDB, 0x88};
    unsigned int        i;
    unsigned int        key_len;
    unsigned int        ret;

    printf("\r\n\r\n -------------- SM2 key exchange --------------");

    /********** get key standard data test **********/
    // get key standard data test
    ret = sm2_get_pubkey_from_prikey(dA, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(PA, KA, 65)) {
        printf("\r\n SM2 get key standard data test 1 failure, ret=%u", ret);
        return 1;
    }
    ret = sm2_get_pubkey_from_prikey(rA, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(RA, KA, 65)) {
        printf("\r\n SM2 get key standard data test 2 failure, ret=%u", ret);
        return 1;
    }
    ret = sm2_get_pubkey_from_prikey(dB, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(PB, KA, 65)) {
        printf("\r\n SM2 get key standard data test 3 failure, ret=%u", ret);
        return 1;
    }
    ret = sm2_get_pubkey_from_prikey(rB, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(RB, KA, 65)) {
        printf("\r\n SM2 get key standard data test 4 failure, ret=%u", ret);
        return 1;
    }
    printf("\r\n SM2 get key standard data test success");

    /********** key exchange standard data test **********/
    ret = sm2_getZ(IDa, 16, PA, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(ZA, KA, 32)) {
        print_buf_u8(KA, 32, "ZA");
        printf("\r\n SM2 get Z test 1 failure, ret=%u", ret);
        return 1;
    }
    ret = sm2_getZ(IDb, 16, PB, KA);
    if ((SM2_SUCCESS != ret) || memcmp_(ZB, KA, 32)) {
        print_buf_u8(KA, 32, "ZB");
        printf("\r\n SM2 get Z test 2 failure, ret=%u", ret);
        return 1;
    }
    printf("\r\n SM2 get Z standard data test success");

    ret = sm2_exchangekey(SM2_Role_Sponsor, dA, PB, rA, RA, RB, ZA, ZB, 16, KA, S1, SA);
    ret |= sm2_exchangekey(SM2_Role_Responsor, dB, PA, rB, RB, RA, ZB, ZA, 16, KB, S2, SB);
    if ((SM2_SUCCESS != ret) || memcmp_(std_key, KA, 16) || memcmp_(std_key, KB, 16) || memcmp_(std_S1_SB, S1, 32) || memcmp_(std_S1_SB, SB, 32) || memcmp_(std_S2_SA, S2, 32) ||
        memcmp_(std_S2_SA, SA, 32)) {
        printf("\r\n SM2 key exchange standard data test 1 error. ret=%u", ret);
        print_buf_u8(KA, 16, "KA");
        print_buf_u8(S1, 32, "S1");
        print_buf_u8(SA, 32, "SA");
        print_buf_u8(KB, 16, "KB");
        print_buf_u8(S2, 32, "S2");
        print_buf_u8(SB, 32, "SB");
        return 1;
    } else {
        printf("\r\n SM2 key exchange standard data test 1 success. ");
    }

    // standard data test 2(without SA/S1/SB/S2)
    ret = sm2_exchangekey(SM2_Role_Sponsor, dA, PB, rA, RA, RB, ZA, ZB, 16, KA, NULL, NULL);
    ret |= sm2_exchangekey(SM2_Role_Responsor, dB, PA, rB, RB, RA, ZB, ZA, 16, KB, NULL, NULL);
    if ((SM2_SUCCESS != ret) || memcmp_(std_key, KA, 16) || memcmp_(std_key, KB, 16)) {
        printf("\r\n SM2 key exchange standard data test 2 error(no SA/S1/SB/S2). "
               "ret=%u",
               ret);
        print_buf_u8(KA, 16, "KA");
        print_buf_u8(S1, 32, "S1");
        print_buf_u8(SA, 32, "SA");
        print_buf_u8(KB, 16, "KB");
        print_buf_u8(S2, 32, "S2");
        print_buf_u8(SB, 32, "SB");
        return 1;
    } else {
        printf("\r\n SM2 key exchange standard data test 2 success(no SA/S1/SB/S2). ");
    }

    /********** key exchange random data test **********/
    printf("\r\n\r\n SM2 key exchange random data test: \r\n");
    for (i = 0; i < SM2_KEY_EXCHANGE_ROUND1; i++) {
        // random key pairs
        memset_(dA, 0, 32);
        memset_(PA, 0, 65);
        memset_(rA, 0, 32);
        memset_(RA, 0, 65);
        memset_(dB, 0, 32);
        memset_(PB, 0, 65);
        memset_(rB, 0, 32);
        memset_(RB, 0, 65);
        ret = sm2_getkey(dA, PA);
        ret |= sm2_getkey(rA, RA);
        ret |= sm2_getkey(dB, PB);
        ret |= sm2_getkey(rB, RB);
        if (SM2_SUCCESS != ret) {
            printf("\r\n SM2 key exchange random data test get key failure, ret = %u", ret);
            return 1;
        }

        // random ZA & ZB
        ret = get_rand(ZA, 32);
        ret |= get_rand(ZB, 32);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error, ret = %u", ret);
            return 1;
        }

        // like encryption, if the output key length is small, it would return
        // failure, since the output key is zero. here the output key length starts
        // with value 8 bytes.
        for (key_len = 8; key_len <= SM2_EXCHANGE_MAX_LEN; key_len++) {
            printf("\r\n SM2 key exchange round1=%u, key_len=%u", i + 1, key_len);
            // get random key pairs
            memset_(KA, 0x11, key_len);
            memset_(KB, 0x55, key_len);
            memset_(S1, 0x11, 32);
            memset_(S2, 0x55, 32);
            memset_(SA, 0x11, 32);
            memset_(SB, 0x55, 32);

            ret = sm2_exchangekey(SM2_Role_Sponsor, dA, PB, rA, RA, RB, ZA, ZB, key_len, KA, S1, SA);
            ret |= sm2_exchangekey(SM2_Role_Responsor, dB, PA, rB, RB, RA, ZB, ZA, key_len, KB, S2, SB);
            if ((SM2_SUCCESS != ret) || memcmp_(KA, KB, key_len) || memcmp_(S1, SB, 32) || memcmp_(S2, SA, 32)) {
                printf("\r\n SM2 key exchange random data test 1 error. ret=%u", ret);
                print_buf_u8(KA, key_len, "KA");
                print_buf_u8(S1, 32, "S1");
                print_buf_u8(SA, 32, "SA");
                print_buf_u8(KB, key_len, "KB");
                print_buf_u8(S2, 32, "S2");
                print_buf_u8(SB, 32, "SB");
                return 1;
            }

            // test without SA/S1/SB/S2
            memset_(S1, 0x11, 32);
            memset_(S2, 0x55, 32);
            memset_(SA, 0x11, 32);
            memset_(SB, 0x55, 32);
            ret = sm2_exchangekey(SM2_Role_Sponsor, dA, PB, rA, RA, RB, ZA, ZB, key_len, KA, NULL, NULL);
            ret |= sm2_exchangekey(SM2_Role_Responsor, dB, PA, rB, RB, RA, ZB, ZA, key_len, KB, NULL, NULL);
            if ((SM2_SUCCESS != ret) || memcmp_(KA, KB, key_len)) {
                printf("\r\n SM2 key exchange random data test 2 error(no "
                       "SA/S1/SB/S2). ret=%u",
                       ret);
                print_buf_u8(KA, key_len, "KA");
                print_buf_u8(S1, 32, "S1");
                print_buf_u8(SA, 32, "SA");
                print_buf_u8(KB, key_len, "KB");
                print_buf_u8(S2, 32, "S2");
                print_buf_u8(SB, 32, "SB");
                return 1;
            }
        }
    }

    printf("\r\n ");

    return 0;
}

#ifdef TRNG_POKER_TEST
/**
 * @brief           SM2   random number test
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_rng_test(void)
{
    unsigned char prikey[32];
    unsigned char pubkey[65];
    unsigned char buf1[32];
    unsigned char buf2[164];
    unsigned char buf3[164];
    unsigned int  i, bytelen;
    unsigned int  ret = 0;

    for (i = 0; i < 3000; i++) {
        // get key
        ret |= sm2_getkey(prikey, pubkey);
        if (SM2_SUCCESS != ret) {
            printf("\r\n SM2 get key failure, ret = %u", ret);
            return 1;
        }

        // sign & verify
        ret = sm2_sign(buf1, NULL, prikey, buf2);
        if (SM2_SUCCESS != ret) {
            printf("\r\n SM2 sign failure, ret=%u", ret);
            return 1;
        }
        ret = sm2_verify(buf1, pubkey, buf2);
        if (SM2_SUCCESS != ret) {
            printf("\r\n SM2 verify failure, ret=%u", ret);
            return 1;
        }

        // encrypt & decrypt
        ret = sm2_encrypt(buf1, 32, NULL, pubkey, pubkey[2] & 1, buf2, &bytelen);
        if ((SM2_SUCCESS != ret) || (32 + 97 != bytelen)) {
            printf("\r\n encrypt failure, ret = %u", ret);
            return 1;
        }

        ret = sm2_decrypt(buf2, bytelen, prikey, pubkey[2] & 1, buf3, &bytelen);
        if ((SM2_SUCCESS != ret) || (32 != bytelen) || memcmp_(buf1, buf3, bytelen)) {
            printf("\r\n decrypt failure, ret = %u", ret);
            return 1;
        }
    }

    return 0;
}
#endif


/**
 * @brief           SM2   all tests
 * @return          0 for success, 1 for failure
 */
unsigned int sm2_all_test(void)
{
    unsigned int ret;

    printf("\r\n\r\n =================== SM2 test =================== ");
    fflush(stdout);

// test internal random numbers in sm2 get_key,sign and encrypt
#ifdef TRNG_POKER_TEST
    if (sm2_rng_test()) {
        return 1;
    }
#endif

#if 0
    SM2_keyget_speed_test();
    SM2_sign_verify_speed_test();
    SM2_encrypt_decrypt_speed_test();
    SM2_exchange_speed_test();
#else
    /**/
    ret = sm2_get_key_test();
    if (ret) {
        return 1;
    }

    ret = sm2_sign_verify_test();
    if (ret) {
        return 1;
    }

    ret = sm2_encrypt_decrypt_test();
    if (ret) {
        return 1;
    }

    ret = sm2_key_exchange_test();
    if (ret) {
        return 1;
    }
#endif

    return 0;
}

#endif

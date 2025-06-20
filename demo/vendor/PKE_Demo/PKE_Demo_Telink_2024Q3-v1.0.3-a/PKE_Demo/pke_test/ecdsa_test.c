/********************************************************************************************************
 * @file    ecdsa_test.c
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


#ifdef SUPPORT_ECDSA

    #include "lib/include/pke/ecdsa.h"
    #include "lib/include/crypto_common/utility.h"
    #include "lib/include/crypto_common/eccp_curve.h"
    #include "lib/include/trng/trng.h"


//#define ECDSA_SPEED_TEST_BY_TIMER

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
extern unsigned int startP(void);
extern unsigned int endP(unsigned char mode, unsigned int once_bytes, unsigned int round);
    #endif


    #define ECDSA_SIGN_VERIFY_ROUND1 (8)
    #define ECDSA_SIGN_VERIFY_ROUND2 (10)

//a = a*(2^n), here n is in [1,7]
void uint8_Big_Multiple2n(unsigned char *a, unsigned int aByteLen, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < aByteLen - 1; i++) {
        a[i] <<= n;
        a[i] |= a[i + 1] >> (8 - n);
    }
    a[i] <<= n;
}

//get output r = (x coordinate of [k]G) mod n, m_r = -r mod n.
//if rand_k is NULL, output a random k. otherwise output rand_k itself
//if uint8_r is not NULL, output byte string(big endian)
//if uint32_r is not NULL, output word array(little endian)
//if uint8_m_r is not NULL, output byte string(big endian)
//if uint32_m_r is not NULL, output word array(little endian)
unsigned int ecdsa_test_get_r_by_k(eccp_curve_t *curve, unsigned char *rand_k_in, unsigned char *rand_k_out, unsigned char *uint8_r, unsigned int *uint32_r, unsigned char *uint8_m_r, unsigned int *uint32_m_r)
{
    unsigned int k[ECCP_MAX_WORD_LEN];
    unsigned int tmp[ECCP_MAX_WORD_LEN];
    unsigned int pWordLen, nByteLen, nWordLen;
    unsigned int ret;

    nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);
    pWordLen = GET_WORD_LEN(curve->eccp_p_bitLen);
    nWordLen = GET_WORD_LEN(curve->eccp_n_bitLen);

    uint32_clear(k, nWordLen);
    if (NULL != rand_k_in) {
        memcpy_(rand_k_out, rand_k_in, nByteLen);
        reverse_byte_array(rand_k_in, (unsigned char *)k, nByteLen);
    } else {
        ret = get_rand((unsigned char *)k, (nWordLen - 1) << 2);
        if (TRNG_SUCCESS != ret) {
            return 1;
        }
        reverse_byte_array((unsigned char *)k, rand_k_out, nByteLen);
    }

    //tmp = x coordinate of [k]G mod n
    ret = eccp_pointMul((eccp_curve_t *)curve, k, curve->eccp_Gx, curve->eccp_Gy, tmp, NULL);
    if (PKE_SUCCESS != ret) {
        printf("\r\n ecdsa_test_get_r_by_k eccp_pointMul error, ret = %02x", ret);
        return 1;
    }

    #if (defined(PKE_LP) || defined(PKE_SECURE))
    ret = pke_mod(tmp, pWordLen, curve->eccp_n, curve->eccp_n_h, curve->eccp_n_n0, nWordLen, tmp);
    #else
    ret = pke_mod(tmp, pWordLen, curve->eccp_n, curve->eccp_n_h, nWordLen, tmp);
    #endif
    if (PKE_SUCCESS != ret) {
        printf("\r\n ecdsa_test_get_r_by_k pke_mod error, ret = %02x", ret);
        return 1;
    }

    if (NULL != uint8_r) {
        reverse_byte_array((unsigned char *)tmp, uint8_r, nByteLen);
        if (0u != (curve->eccp_n_bitLen & 7)) //this is for ECDSA E value.
        {
            uint8_Big_Multiple2n(uint8_r, nByteLen, 8u - (curve->eccp_n_bitLen & 7));
        }
    }

    if (NULL != uint32_r) {
        uint32_copy(uint32_r, tmp, nWordLen);
    }

    if ((NULL != uint8_m_r) || (NULL != uint32_m_r)) {
        uint32_clear(k, nWordLen);
        (void)pke_modsub(curve->eccp_n, k, tmp, tmp, nWordLen);

        if (NULL != uint8_m_r) {
            reverse_byte_array((unsigned char *)tmp, uint8_m_r, nByteLen);
            if (0u != (curve->eccp_n_bitLen & 7)) //this is for ECDSA E value.
            {
                uint8_Big_Multiple2n(uint8_m_r, nByteLen, 8u - (curve->eccp_n_bitLen & 7));
            }
        }

        if (NULL != uint32_m_r) {
            uint32_copy(uint32_m_r, tmp, nWordLen);
        }
    }

    return 0;
}

/***************************** standard data E ********************************/

//message: "abc"
//unsigned char msg[3]={0x61,0x62,0x63};

//E(hash digest from md5("abc")):
//0x900150983CD24FB0D6963F7D28E17F72
unsigned char std_E_md5[] = {
    0x90,
    0x01,
    0x50,
    0x98,
    0x3C,
    0xD2,
    0x4F,
    0xB0,
    0xD6,
    0x96,
    0x3F,
    0x7D,
    0x28,
    0xE1,
    0x7F,
    0x72,
};

//E(hash digest from sha1("abc")):
//0xA9993E364706816ABA3E25717850C26C9CD0D89D
unsigned char std_E_sha1[] = {
    0xA9,
    0x99,
    0x3E,
    0x36,
    0x47,
    0x06,
    0x81,
    0x6A,
    0xBA,
    0x3E,
    0x25,
    0x71,
    0x78,
    0x50,
    0xC2,
    0x6C,
    0x9C,
    0xD0,
    0xD8,
    0x9D,
};

//E(random data, 192 bits):
//0xEB3C60084A65169533826A231C5F590D9FDB8EBEF8160FCE
unsigned char std_E_192[] = {
    0xEB,
    0x3C,
    0x60,
    0x08,
    0x4A,
    0x65,
    0x16,
    0x95,
    0x33,
    0x82,
    0x6A,
    0x23,
    0x1C,
    0x5F,
    0x59,
    0x0D,
    0x9F,
    0xDB,
    0x8E,
    0xBE,
    0xF8,
    0x16,
    0x0F,
    0xCE,
};

//E(hash digest from sha224("abc")):
//0x23097D223405D8228642A477BDA255B32AADBCE4BDA0B3F7E36C9DA7
unsigned char std_E_sha224[] = {
    0x23,
    0x09,
    0x7D,
    0x22,
    0x34,
    0x05,
    0xD8,
    0x22,
    0x86,
    0x42,
    0xA4,
    0x77,
    0xBD,
    0xA2,
    0x55,
    0xB3,
    0x2A,
    0xAD,
    0xBC,
    0xE4,
    0xBD,
    0xA0,
    0xB3,
    0xF7,
    0xE3,
    0x6C,
    0x9D,
    0xA7,
};

//E(hash digest from sha256("abc")):
//0xBA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD
unsigned char std_E_sha256[] = {
    0xBA,
    0x78,
    0x16,
    0xBF,
    0x8F,
    0x01,
    0xCF,
    0xEA,
    0x41,
    0x41,
    0x40,
    0xDE,
    0x5D,
    0xAE,
    0x22,
    0x23,
    0xB0,
    0x03,
    0x61,
    0xA3,
    0x96,
    0x17,
    0x7A,
    0x9C,
    0xB4,
    0x10,
    0xFF,
    0x61,
    0xF2,
    0x00,
    0x15,
    0xAD,
};

//E(hash digest from sha384("abc")):
//0xCB00753F45A35E8BB5A03D699AC65007272C32AB0EDED1631A8B605A43FF5BED8086072BA1E7CC2358BAECA134C825A7
unsigned char std_E_sha384[] = {
    0xCB,
    0x00,
    0x75,
    0x3F,
    0x45,
    0xA3,
    0x5E,
    0x8B,
    0xB5,
    0xA0,
    0x3D,
    0x69,
    0x9A,
    0xC6,
    0x50,
    0x07,
    0x27,
    0x2C,
    0x32,
    0xAB,
    0x0E,
    0xDE,
    0xD1,
    0x63,
    0x1A,
    0x8B,
    0x60,
    0x5A,
    0x43,
    0xFF,
    0x5B,
    0xED,
    0x80,
    0x86,
    0x07,
    0x2B,
    0xA1,
    0xE7,
    0xCC,
    0x23,
    0x58,
    0xBA,
    0xEC,
    0xA1,
    0x34,
    0xC8,
    0x25,
    0xA7,
};

//E(hash digest from sha512("abc")):
//0xDDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F
unsigned char std_E_sha512[] = {
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

//E(random data, 544 bits):
//0xD29BFAE2211F962C46AD5515C076A5092EF1B6BE15F2578D02AC001AB841933EA0A28710CCD538EA896E4C19DB29488A5DCEFABA10EC81668808BF39B6BEFD5A7831CD18
unsigned char std_E_544[] = {
    0xD2,
    0x9B,
    0xFA,
    0xE2,
    0x21,
    0x1F,
    0x96,
    0x2C,
    0x46,
    0xAD,
    0x55,
    0x15,
    0xC0,
    0x76,
    0xA5,
    0x09,
    0x2E,
    0xF1,
    0xB6,
    0xBE,
    0x15,
    0xF2,
    0x57,
    0x8D,
    0x02,
    0xAC,
    0x00,
    0x1A,
    0xB8,
    0x41,
    0x93,
    0x3E,
    0xA0,
    0xA2,
    0x87,
    0x10,
    0xCC,
    0xD5,
    0x38,
    0xEA,
    0x89,
    0x6E,
    0x4C,
    0x19,
    0xDB,
    0x29,
    0x48,
    0x8A,
    0x5D,
    0xCE,
    0xFA,
    0xBA,
    0x10,
    0xEC,
    0x81,
    0x66,
    0x88,
    0x08,
    0xBF,
    0x39,
    0xB6,
    0xBE,
    0xFD,
    0x5A,
    0x78,
    0x31,
    0xCD,
    0x18,
};

typedef struct
{
    unsigned char *rand_k;
    unsigned char *priKey;
    unsigned char *pubKey;
    unsigned char *std_signature_r;
    unsigned char *std_E_md5;
    unsigned char *std_signature_s_md5;
    unsigned char *std_E_sha1;
    unsigned char *std_signature_s_sha1;
    unsigned char *std_E_192;
    unsigned char *std_signature_s_192;
    unsigned char *std_E_sha224;
    unsigned char *std_signature_s_sha224;
    unsigned char *std_E_sha256;
    unsigned char *std_signature_s_sha256;
    unsigned char *std_E_sha384;
    unsigned char *std_signature_s_sha384;
    unsigned char *std_E_sha512;
    unsigned char *std_signature_s_sha512;
    unsigned char *std_E_544;
    unsigned char *std_signature_s_544;
    unsigned char *std_signature_s_zero;
    unsigned char *std_signature_s_1;
    unsigned char *std_signature_s_FF;
} ecdsa_test_vector_t;

unsigned int ecdsa_std_sign_verify_test_internal(eccp_curve_t *curve, char *curve_name, unsigned char *E, unsigned int EByteLen, unsigned char *rand_k, unsigned char *prikey, unsigned char *pubkey, unsigned char *signature_r, unsigned char *signature_s, unsigned int sign_ret_value, char *info)
{
    unsigned char k[ECCP_MAX_BYTE_LEN];
    unsigned char signature[2 * ECCP_MAX_BYTE_LEN];
    unsigned char buf[2 * ECCP_MAX_BYTE_LEN];
    unsigned char tmp[2 * ECCP_MAX_BYTE_LEN + 1];
    unsigned int  buf2[ECCP_MAX_WORD_LEN];
    unsigned int  buf3[ECCP_MAX_WORD_LEN];
    unsigned int  tmp2[ECCP_MAX_WORD_LEN];
    unsigned int  pByteLen, nByteLen, nWordLen;
    unsigned int  pubkeyByteLen, signatureByteLen;
    unsigned int  ret;
    char         *inf = "";

    if (info) {
        inf = info;
    }

    pByteLen         = GET_BYTE_LEN(curve->eccp_p_bitLen);
    nByteLen         = GET_BYTE_LEN(curve->eccp_n_bitLen);
    nWordLen         = GET_WORD_LEN(curve->eccp_n_bitLen);
    pubkeyByteLen    = 2 * pByteLen;
    signatureByteLen = 2 * nByteLen;

    ret = ecdsa_sign(curve, E, EByteLen, rand_k, prikey, buf);
    if ((sign_ret_value != ret)) {
        printf("\r\n %s ECDSA sign %s failure, ret=%08x", curve_name, inf, ret);
        return 1;
    }

    if (ECDSA_SUCCESS == ret) {
        if ((NULL != rand_k) && (NULL != signature_r) && (NULL != signature_s)) {
            memcpy_(signature, signature_r, nByteLen);
            memcpy_(signature + nByteLen, signature_s, nByteLen);
            if (memcmp_(buf, signature, signatureByteLen)) {
                printf("\r\n %s ECDSA sign %s error, ret = %02x", curve_name, inf, ret);
                print_buf_U8(E, EByteLen, "E");
                print_buf_U8(rand_k, nByteLen, "rand_k");
                print_buf_U8(prikey, nByteLen, "prikey");
                print_buf_U8(buf, signatureByteLen, "signature");
                return 1;
            }
        }

        ret = ecdsa_verify(curve, E, EByteLen, pubkey, buf);
        if (ECDSA_SUCCESS != ret) {
            printf("\r\n %s ECDSA verify %s error, ret = %02x", curve_name, inf, ret);
            return 1;
        }

        /********** valid signature test (s=-s). **********/
        //since [k]G = [e*s^(-1)]G + [r*s^(-1)]PA, and only compare x coordinate
        //of result point in verifying.
        tmp2[nWordLen - 1] = 0;
        reverse_byte_array(buf + nByteLen, (unsigned char *)tmp2, nByteLen);
        ret = pke_sub(curve->eccp_n, tmp2, tmp2, nWordLen);
        if (PKE_SUCCESS != ret) {
            printf("\r\n valid signature test (s=-s) failure, ret=%x", ret);
            return 1;
        } else {
            ;
        }
        memcpy_(tmp, buf, nByteLen);
        reverse_byte_array((unsigned char *)tmp2, tmp + nByteLen, nByteLen);

        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_SUCCESS != ret) {
            printf("\r\n ECDSA verify %s failure(valid: s=-s), ret=%x", inf, ret);
            print_buf_U8(tmp, signatureByteLen, "tmp");
            return 1;
        }

        /********** valid signature test (r = 0). **********/
        //it is infeasible to get r=0, since [k]G = (0,sqrt(b)), you are unable to get k.

        /********** invalid signature test (s = k^(-1)(e+r*dA) = 0 mod n) with 2 cases. **********/
        //get k and buf2 = r = (x coordinate of [k]G or [k](-G)) mod n
        ret = ecdsa_test_get_r_by_k((eccp_curve_t *)curve, rand_k, k, NULL, buf2, NULL, NULL);
        if (0 != ret) {
            return 1;
        }

        //case 1: dA = -e*r^(-1) mod n or dA=0(when e=0)
        //get tmp2 = -e mod n
        uint32_clear(tmp2, nWordLen);
        if (curve->eccp_n_bitLen >= (EByteLen << 3)) {
            reverse_byte_array(E, (unsigned char *)tmp2, EByteLen);
        } else {
            reverse_byte_array(E, (unsigned char *)tmp2, nByteLen);
            if ((curve->eccp_n_bitLen) & 7) {
                Big_Div2n(tmp2, nWordLen, 8 - ((curve->eccp_n_bitLen) & 7));
            } else {
                ;
            }
        }

        ret = pke_mod(tmp2, nWordLen, curve->eccp_n, curve->eccp_n_h, curve->eccp_n_n0, nWordLen, tmp2);
        uint32_clear(buf3, nWordLen);
        ret |= pke_modsub(curve->eccp_n, buf3, tmp2, tmp2, nWordLen);

        //get tmp2 = -e*r^(-1) mod n or dA=0(when e=0)
        ret |= pke_modinv(curve->eccp_n, buf2, buf3, nWordLen, nWordLen);
        ret |= pke_modmul(curve->eccp_n, tmp2, buf3, tmp2, nWordLen);
        if (PKE_SUCCESS != ret) {
            printf("\r\n invalid signature test (s=0 case 1) failure, ret=%x", ret);
            return 1;
        } else {
            ;
        }
        reverse_byte_array((unsigned char *)tmp2, (unsigned char *)tmp2, nByteLen);

        ret = ecdsa_sign(curve, E, EByteLen, k, (unsigned char *)tmp2, buf);
        if (ECDSA_ZERO_ALL != ret) {
            printf("\r\n ECDSA sign %s failure(invalid: s=0 case 2), ret=%x", inf, ret);
            print_buf_U8(buf, signatureByteLen, "signature");
            print_buf_U8((unsigned char *)tmp2, nByteLen, "dA");
            return 1;
        }

        //case 2: e = -r*dA mod n
        uint32_clear(buf3, nWordLen);
        reverse_byte_array(prikey, (unsigned char *)buf3, nByteLen);
        ret = pke_modmul(curve->eccp_n, buf2, buf3, tmp2, nWordLen);
        uint32_clear(buf3, nWordLen);
        ret |= pke_modsub(curve->eccp_n, buf3, tmp2, tmp2, nWordLen);
        reverse_byte_array((unsigned char *)tmp2, (unsigned char *)tmp2, nByteLen);
        if (curve->eccp_n_bitLen & 7) {
            uint8_Big_Multiple2n((unsigned char *)tmp2, nByteLen, 8 - (curve->eccp_n_bitLen & 7));
        }

        ret = ecdsa_sign(curve, (unsigned char *)tmp2, nByteLen, k, prikey, buf);
        if (ECDSA_ZERO_ALL != ret) {
            printf("\r\n ECDSA sign %s failure(invalid: s=0 case 2), ret=%x", inf, ret);
            print_buf_U8(buf, signatureByteLen, "signature");
            print_buf_U8((unsigned char *)tmp2, nByteLen, "E");
            return 1;
        }
        /********** invalid signature test (s=0) end. **********/

        //invalid E
        memcpy_(tmp, E, EByteLen);
        tmp[0] += 3;
        ret = ecdsa_verify(curve, tmp, EByteLen, pubkey, buf);
        if (ECDSA_VERIFY_FAILED != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid E), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid pubkey test 1
        memcpy_(tmp, pubkey, pubkeyByteLen);
        tmp[0] += 3;
        ret = ecdsa_verify(curve, E, EByteLen, tmp, buf);
        if (PKE_NOT_ON_CURVE != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid public key 1), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid pubkey test 2
        memcpy_(tmp, pubkey, pubkeyByteLen);
        tmp[1] += 3;
        ret = ecdsa_verify(curve, E, EByteLen, tmp, buf);
        if (PKE_NOT_ON_CURVE != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid public key 2), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid pubkey test 3
        memcpy_(tmp, pubkey, pubkeyByteLen);
        tmp[pubkeyByteLen - 1] += 3;
        ret = ecdsa_verify(curve, E, EByteLen, tmp, buf);
        if (PKE_NOT_ON_CURVE != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid public key 3), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 1(corrupted r)
        memcpy_(tmp, buf, signatureByteLen);
        tmp[2] += 3;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if ((ECDSA_VERIFY_FAILED != ret) && (ECDSA_INTEGER_TOO_BIG != ret)) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: corrupted r), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 2(r=0)
        memcpy_(tmp, buf, signatureByteLen);
        memset_(tmp, 0, nByteLen);
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_ZERO_ALL != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: r=0), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 3(r=n-1)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp, nByteLen);
        tmp[nByteLen - 1] -= 1;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_VERIFY_FAILED != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: r=n-1), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 4(r=n)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp, nByteLen);
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_INTEGER_TOO_BIG != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: r=n), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 5(r=n+1)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp, nByteLen);
        tmp[nByteLen - 1] += 1;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_INTEGER_TOO_BIG != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: r=n+1), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 6(corrupted s)
        memcpy_(tmp, buf, signatureByteLen);
        tmp[signatureByteLen - 1] += 3;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_VERIFY_FAILED != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: corrupted s), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 7(s=0)
        memcpy_(tmp, buf, signatureByteLen);
        memset_(tmp + nByteLen, 0, nByteLen);
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_ZERO_ALL != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: s=0), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 8(s=n-1)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp + nByteLen, nByteLen);
        tmp[signatureByteLen - 1] -= 1;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_VERIFY_FAILED != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: s=n-1), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 9(s=n)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp + nByteLen, nByteLen);
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_INTEGER_TOO_BIG != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: s=n), ret=%x", curve_name, inf, ret);
            return 1;
        }

        //invalid signature test 10(s=n+1)
        memcpy_(tmp, buf, signatureByteLen);
        reverse_byte_array((unsigned char *)(curve->eccp_n), tmp + nByteLen, nByteLen);
        tmp[signatureByteLen - 1] += 1;
        ret = ecdsa_verify(curve, E, EByteLen, pubkey, tmp);
        if (ECDSA_INTEGER_TOO_BIG != ret) {
            printf("\r\n %s ECDSA verify %s failure(invalid signature: r=n+1), ret=%x", curve_name, inf, ret);
            return 1;
        }
    }

    if (NULL != info) {
        printf("\r\n %s ECDSA sign & verify %s success", curve_name, inf);
    }

    return 0;
}

unsigned int ecdsa_std_sign_verify_test(eccp_curve_t *curve, char *curve_name, ecdsa_test_vector_t *vector)
{
    unsigned char E[ECCP_MAX_BYTE_LEN];
    unsigned int  tmpLen, nByteLen;

    nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);

    printf("\r\n -------------- %s ECDSA sign & verify test -------------- ", curve_name);

    //E(hash digest) 128 bits, actually here E is md5("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_md5, 16, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_md5, ECDSA_SUCCESS, "standard data test(E-128bits)")) {
        return 1;
    }

    //E(hash digest) 160 bits, actually here E is sha1("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_sha1, 20, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_sha1, ECDSA_SUCCESS, "standard data test(E-160bits)")) {
        return 1;
    }

    //E(hash digest) 192 bits, here E is random data
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_192, 24, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_192, ECDSA_SUCCESS, "standard data test(E-192bits)")) {
        return 1;
    }

    //E(hash digest) 224 bits, actually here E is sha224("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_sha224, 28, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_sha224, ECDSA_SUCCESS, "standard data test(E-224bits)")) {
        return 1;
    }

    //E(hash digest) 256 bit, actually here E is sha256("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_sha256, 32, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_sha256, ECDSA_SUCCESS, "standard data test(E-256bits)")) {
        return 1;
    }

    //E(hash digest) 384 bit, actually here E is sha384("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_sha384, 48, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_sha384, ECDSA_SUCCESS, "standard data test(E-384bits)")) {
        return 1;
    }

    //E(hash digest) 512 bit, actually here E is sha512("abc")
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_sha512, 64, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_sha512, ECDSA_SUCCESS, "standard data test(E-512bits)")) {
        return 1;
    }

    //E(hash digest) 544 bit, here E is random data
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, vector->std_E_544, 68, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_544, ECDSA_SUCCESS, "standard data test(E-544bits)")) {
        return 1;
    }

    /********** e = 0 **********/
    memset_(E, 0, ECCP_MAX_BYTE_LEN);
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, E, nByteLen, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_zero, ECDSA_SUCCESS, "test(E=0)")) {
        return 1;
    }

    /********** e = 1 **********/
    memset_(E, 0, ECCP_MAX_BYTE_LEN);
    E[nByteLen - 1] = 1;
    tmpLen          = (curve->eccp_n_bitLen) & 7;
    if (tmpLen) {
        uint8_Big_Multiple2n(E, nByteLen, (8u - tmpLen)); //E[nByteLen-1] <<= (8-((curve->eccp_n_bitLen)&7));//
    }
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, E, nByteLen, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_1, ECDSA_SUCCESS, "test(E=1)")) {
        return 1;
    }

    /********** e = n **********/
    reverse_byte_array((unsigned char *)(curve->eccp_n), E, nByteLen);
    //make sure the MSB nBitLen is n
    tmpLen = (curve->eccp_n_bitLen) & 7;
    if (tmpLen) {
        uint8_Big_Multiple2n(E, nByteLen, (8u - tmpLen));
    }
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, E, nByteLen, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_zero, ECDSA_SUCCESS, "test(E=n)")) {
        return 1;
    }

    /********** e = 0xFF...FF **********/
    memset_(E, 0xFF, nByteLen);
    if (ecdsa_std_sign_verify_test_internal(curve, curve_name, E, nByteLen, vector->rand_k, vector->priKey, vector->pubKey, vector->std_signature_r, vector->std_signature_s_FF, ECDSA_SUCCESS, "test(E=0xFF..FF)")) {
        return 1;
    }

    printf("\r\n");

    return 0;
}


    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
unsigned int ecdsa_std_test_secp160k1(void)
{
    //k:
    //0x004E84E769224A5A775A7B927DCA1C42E98298A752
    unsigned char rand_k[21] = {
        0x00,
        0x4E,
        0x84,
        0xE7,
        0x69,
        0x22,
        0x4A,
        0x5A,
        0x77,
        0x5A,
        0x7B,
        0x92,
        0x7D,
        0xCA,
        0x1C,
        0x42,
        0xE9,
        0x82,
        0x98,
        0xA7,
        0x52,
    };

    //private key:
    //0x006F30869BD7D848C315F76BA198075773FCCB293F
    unsigned char priKey[21] = {
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

    //public key:
    //x coordinate:
    //0xDD71E6036466B08271CDDF73128BC547EC246AFD
    //y coordinate:
    //0x60B0235A9C62DCBC774C0EEEFDAD7B38B2B1B166
    unsigned char pubKey[40] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x005E2FCE3B4F9996A75370E581291006E0753C7EDF
    unsigned char std_signature_r[] = {
        0x00,
        0x5E,
        0x2F,
        0xCE,
        0x3B,
        0x4F,
        0x99,
        0x96,
        0xA7,
        0x53,
        0x70,
        0xE5,
        0x81,
        0x29,
        0x10,
        0x06,
        0xE0,
        0x75,
        0x3C,
        0x7E,
        0xDF,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x00E8E1F288E9F427D7B578E26065262191E4988807
    unsigned char std_signature_s_zero[] = {
        0x00,
        0xE8,
        0xE1,
        0xF2,
        0x88,
        0xE9,
        0xF4,
        0x27,
        0xD7,
        0xB5,
        0x78,
        0xE2,
        0x60,
        0x65,
        0x26,
        0x21,
        0x91,
        0xE4,
        0x98,
        0x88,
        0x07,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x00DA5910DC53712FD14B7FE116038A70E4A6E12A0A
    unsigned char std_signature_s_1[] = {
        0x00,
        0xDA,
        0x59,
        0x10,
        0xDC,
        0x53,
        0x71,
        0x2F,
        0xD1,
        0x4B,
        0x7F,
        0xE1,
        0x16,
        0x03,
        0x8A,
        0x70,
        0xE4,
        0xA6,
        0xE1,
        0x2A,
        0x0A,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x00EDBB861EDD8A825996ABC885722F22D1BC0DD8F8
    unsigned char std_signature_s_FF[] = {
        0x00,
        0xED,
        0xBB,
        0x86,
        0x1E,
        0xDD,
        0x8A,
        0x82,
        0x59,
        0x96,
        0xAB,
        0xC8,
        0x85,
        0x72,
        0x2F,
        0x22,
        0xD1,
        0xBC,
        0x0D,
        0xD8,
        0xF8,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x0043C3B0E75FB4562EB19AC940CF132AE11AF0A447
    unsigned char std_signature_s_md5[] = {
        0x00,
        0x43,
        0xC3,
        0xB0,
        0xE7,
        0x5F,
        0xB4,
        0x56,
        0x2E,
        0xB1,
        0x9A,
        0xC9,
        0x40,
        0xCF,
        0x13,
        0x2A,
        0xE1,
        0x1A,
        0xF0,
        0xA4,
        0x47,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x00D3322EFB435D4C851F1F08F6C1AB1D1EBFDF8D7F
    unsigned char std_signature_s_sha1[] = {
        0x00,
        0xD3,
        0x32,
        0x2E,
        0xFB,
        0x43,
        0x5D,
        0x4C,
        0x85,
        0x1F,
        0x1F,
        0x08,
        0xF6,
        0xC1,
        0xAB,
        0x1D,
        0x1E,
        0xBF,
        0xDF,
        0x8D,
        0x7F,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x0079118C0B3BEE4FE49EBFB13FFC9C7DD730B332AB
    unsigned char std_signature_s_192[] = {
        0x00,
        0x79,
        0x11,
        0x8C,
        0x0B,
        0x3B,
        0xEE,
        0x4F,
        0xE4,
        0x9E,
        0xBF,
        0xB1,
        0x3F,
        0xFC,
        0x9C,
        0x7D,
        0xD7,
        0x30,
        0xB3,
        0x32,
        0xAB,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x0091ADBA504D5D526DF0E52CC35E94BA019D5EF6C0
    unsigned char std_signature_s_sha224[] = {
        0x00,
        0x91,
        0xAD,
        0xBA,
        0x50,
        0x4D,
        0x5D,
        0x52,
        0x6D,
        0xF0,
        0xE5,
        0x2C,
        0xC3,
        0x5E,
        0x94,
        0xBA,
        0x01,
        0x9D,
        0x5E,
        0xF6,
        0xC0,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x002A17A06210B29A3E8A3AF9A21F32192011435CB7
    unsigned char std_signature_s_sha256[] = {
        0x00,
        0x2A,
        0x17,
        0xA0,
        0x62,
        0x10,
        0xB2,
        0x9A,
        0x3E,
        0x8A,
        0x3A,
        0xF9,
        0xA2,
        0x1F,
        0x32,
        0x19,
        0x20,
        0x11,
        0x43,
        0x5C,
        0xB7,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x00F8AFEF429DE50D1BBAA74A3380AF961F6186DB0B
    unsigned char std_signature_s_sha384[] = {
        0x00,
        0xF8,
        0xAF,
        0xEF,
        0x42,
        0x9D,
        0xE5,
        0x0D,
        0x1B,
        0xBA,
        0xA7,
        0x4A,
        0x33,
        0x80,
        0xAF,
        0x96,
        0x1F,
        0x61,
        0x86,
        0xDB,
        0x0B,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x00553FC6A0E6B14B90239D929FE8391C599E37C473
    unsigned char std_signature_s_sha512[] = {
        0x00,
        0x55,
        0x3F,
        0xC6,
        0xA0,
        0xE6,
        0xB1,
        0x4B,
        0x90,
        0x23,
        0x9D,
        0x92,
        0x9F,
        0xE8,
        0x39,
        0x1C,
        0x59,
        0x9E,
        0x37,
        0xC4,
        0x73,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x00827D678129829377922DFE6E64CD66A74F3AD75E
    unsigned char std_signature_s_544[] = {
        0x00,
        0x82,
        0x7D,
        0x67,
        0x81,
        0x29,
        0x82,
        0x93,
        0x77,
        0x92,
        0x2D,
        0xFE,
        0x6E,
        0x64,
        0xCD,
        0x66,
        0xA7,
        0x4F,
        0x3A,
        0xD7,
        0x5E,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp160k1;
    char         *curve_name = "secp160k1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
unsigned int ecdsa_std_test_secp192k1(void)
{
    //k:
    //0x9DE1A064C62E2E841E88310E2FDE074115C40CC61203971E
    unsigned char rand_k[24] = {
        0x9D,
        0xE1,
        0xA0,
        0x64,
        0xC6,
        0x2E,
        0x2E,
        0x84,
        0x1E,
        0x88,
        0x31,
        0x0E,
        0x2F,
        0xDE,
        0x07,
        0x41,
        0x15,
        0xC4,
        0x0C,
        0xC6,
        0x12,
        0x03,
        0x97,
        0x1E,
    };

    //private key:
    //0x96238C7CE26EB1C59C04F0B59C62F418EB43FE223B744075
    unsigned char priKey[24] = {
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

    //public key:
    //x coordinate:
    //0x23A3D5BA5CEB2E92B16185FC354993693A66D92D775DB28C
    //y coordinate:
    //0x12224FABE27D742F291CE83EF1456A8FA2B494ACF39AB770
    unsigned char pubKey[48] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x40C0FEA9D0219769FB462F366FB0BB42B5441ED895EB7DCF
    unsigned char std_signature_r[] = {
        0x40,
        0xC0,
        0xFE,
        0xA9,
        0xD0,
        0x21,
        0x97,
        0x69,
        0xFB,
        0x46,
        0x2F,
        0x36,
        0x6F,
        0xB0,
        0xBB,
        0x42,
        0xB5,
        0x44,
        0x1E,
        0xD8,
        0x95,
        0xEB,
        0x7D,
        0xCF,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xD37ED2078C9FDA1787C96384A257C04C511B90E8B792138E
    unsigned char std_signature_s_zero[] = {
        0xD3,
        0x7E,
        0xD2,
        0x07,
        0x8C,
        0x9F,
        0xDA,
        0x17,
        0x87,
        0xC9,
        0x63,
        0x84,
        0xA2,
        0x57,
        0xC0,
        0x4C,
        0x51,
        0x1B,
        0x90,
        0xE8,
        0xB7,
        0x92,
        0x13,
        0x8E,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0xBBAB165C86AB4EF2C440716BCDF4496246E91D993E32B3A2
    unsigned char std_signature_s_1[] = {
        0xBB,
        0xAB,
        0x16,
        0x5C,
        0x86,
        0xAB,
        0x4E,
        0xF2,
        0xC4,
        0x40,
        0x71,
        0x6B,
        0xCD,
        0xF4,
        0x49,
        0x62,
        0x46,
        0xE9,
        0x1D,
        0x99,
        0x3E,
        0x32,
        0xB3,
        0xA2,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x07BCA6BEB3EF043D678C8C81C52B549D9AE2F59105DA0D49
    unsigned char std_signature_s_FF[] = {
        0x07,
        0xBC,
        0xA6,
        0xBE,
        0xB3,
        0xEF,
        0x04,
        0x3D,
        0x67,
        0x8C,
        0x8C,
        0x81,
        0xC5,
        0x2B,
        0x54,
        0x9D,
        0x9A,
        0xE2,
        0xF5,
        0x91,
        0x05,
        0xDA,
        0x0D,
        0x49,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0xB2610A7AC3C1A7CD88BF916DC86A53B591F77880200EA083
    unsigned char std_signature_s_md5[] = {
        0xB2,
        0x61,
        0x0A,
        0x7A,
        0xC3,
        0xC1,
        0xA7,
        0xCD,
        0x88,
        0xBF,
        0x91,
        0x6D,
        0xC8,
        0x6A,
        0x53,
        0xB5,
        0x91,
        0xF7,
        0x78,
        0x80,
        0x20,
        0x0E,
        0xA0,
        0x83,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x6F9BF817FAC2E7C99BFF3F8C4773220E41ECE39C0FDC425E
    unsigned char std_signature_s_sha1[] = {
        0x6F,
        0x9B,
        0xF8,
        0x17,
        0xFA,
        0xC2,
        0xE7,
        0xC9,
        0x9B,
        0xFF,
        0x3F,
        0x8C,
        0x47,
        0x73,
        0x22,
        0x0E,
        0x41,
        0xEC,
        0xE3,
        0x9C,
        0x0F,
        0xDC,
        0x42,
        0x5E,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xF0D83B8A0C11E6ACF05A651F0F9A15CA14D1CFBBAB48B822
    unsigned char std_signature_s_192[] = {
        0xF0,
        0xD8,
        0x3B,
        0x8A,
        0x0C,
        0x11,
        0xE6,
        0xAC,
        0xF0,
        0x5A,
        0x65,
        0x1F,
        0x0F,
        0x9A,
        0x15,
        0xCA,
        0x14,
        0xD1,
        0xCF,
        0xBB,
        0xAB,
        0x48,
        0xB8,
        0x22,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0xD0FFBBD10A001EDB2215B19FBB0B153C9F61D8E1526FDC04
    unsigned char std_signature_s_sha224[] = {
        0xD0,
        0xFF,
        0xBB,
        0xD1,
        0x0A,
        0x00,
        0x1E,
        0xDB,
        0x22,
        0x15,
        0xB1,
        0x9F,
        0xBB,
        0x0B,
        0x15,
        0x3C,
        0x9F,
        0x61,
        0xD8,
        0xE1,
        0x52,
        0x6F,
        0xDC,
        0x04,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0xBA56BCA2BF9AD2B7B50019614441FB0CB911E666B7C6C577
    unsigned char std_signature_s_sha256[] = {
        0xBA,
        0x56,
        0xBC,
        0xA2,
        0xBF,
        0x9A,
        0xD2,
        0xB7,
        0xB5,
        0x00,
        0x19,
        0x61,
        0x44,
        0x41,
        0xFB,
        0x0C,
        0xB9,
        0x11,
        0xE6,
        0x66,
        0xB7,
        0xC6,
        0xC5,
        0x77,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x4404BA3A6739FC55A507C69BB381E17E5EECB15AFD8E6C8E
    unsigned char std_signature_s_sha384[] = {
        0x44,
        0x04,
        0xBA,
        0x3A,
        0x67,
        0x39,
        0xFC,
        0x55,
        0xA5,
        0x07,
        0xC6,
        0x9B,
        0xB3,
        0x81,
        0xE1,
        0x7E,
        0x5E,
        0xEC,
        0xB1,
        0x5A,
        0xFD,
        0x8E,
        0x6C,
        0x8E,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0xD45A8DB3C00A4E3EF2C44BB3535CE32C63CF36A0EC288BF4
    unsigned char std_signature_s_sha512[] = {
        0xD4,
        0x5A,
        0x8D,
        0xB3,
        0xC0,
        0x0A,
        0x4E,
        0x3E,
        0xF2,
        0xC4,
        0x4B,
        0xB3,
        0x53,
        0x5C,
        0xE3,
        0x2C,
        0x63,
        0xCF,
        0x36,
        0xA0,
        0xEC,
        0x28,
        0x8B,
        0xF4,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x3388F850D176D70C10A747722B4169A8E10957C7B9F91368
    unsigned char std_signature_s_544[] = {
        0x33,
        0x88,
        0xF8,
        0x50,
        0xD1,
        0x76,
        0xD7,
        0x0C,
        0x10,
        0xA7,
        0x47,
        0x72,
        0x2B,
        0x41,
        0x69,
        0xA8,
        0xE1,
        0x09,
        0x57,
        0xC7,
        0xB9,
        0xF9,
        0x13,
        0x68,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp192k1;
    char         *curve_name = "secp192k1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
unsigned int ecdsa_std_test_secp224k1(void)
{
    //k:
    //0x00BA5D8927A40B7E6583FCAA030F36362B89FB08935BB5A91B5F6F414B
    unsigned char rand_k[29] = {
        0x00,
        0xBA,
        0x5D,
        0x89,
        0x27,
        0xA4,
        0x0B,
        0x7E,
        0x65,
        0x83,
        0xFC,
        0xAA,
        0x03,
        0x0F,
        0x36,
        0x36,
        0x2B,
        0x89,
        0xFB,
        0x08,
        0x93,
        0x5B,
        0xB5,
        0xA9,
        0x1B,
        0x5F,
        0x6F,
        0x41,
        0x4B,
    };

    //private key:
    //0x00D349B85CDBB90D32B969ABBA7A2CF2F62D0701CED6BBD76688365E60
    unsigned char priKey[29] = {
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

    //public key:
    //x coordinate:
    //0x5B1BD614B8A6BAC545C359DB685A3F7736B077946BE282053CAB8BBC
    //y coordinate:
    //0x869BEAFBE0288F18C5A1BDAD301B9BD1DF0EE6B8267F34FF75C223F2
    unsigned char pubKey[56] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x00E15B44E94FDCFA62756F6416925F4795A108B43826A66CEBEA2AC19B
    unsigned char std_signature_r[] = {
        0x00,
        0xE1,
        0x5B,
        0x44,
        0xE9,
        0x4F,
        0xDC,
        0xFA,
        0x62,
        0x75,
        0x6F,
        0x64,
        0x16,
        0x92,
        0x5F,
        0x47,
        0x95,
        0xA1,
        0x08,
        0xB4,
        0x38,
        0x26,
        0xA6,
        0x6C,
        0xEB,
        0xEA,
        0x2A,
        0xC1,
        0x9B,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x000CC70EA869CD9C50A5915A24141C210578E246F5138DEB5E0E389BA5
    unsigned char std_signature_s_zero[] = {
        0x00,
        0x0C,
        0xC7,
        0x0E,
        0xA8,
        0x69,
        0xCD,
        0x9C,
        0x50,
        0xA5,
        0x91,
        0x5A,
        0x24,
        0x14,
        0x1C,
        0x21,
        0x05,
        0x78,
        0xE2,
        0x46,
        0xF5,
        0x13,
        0x8D,
        0xEB,
        0x5E,
        0x0E,
        0x38,
        0x9B,
        0xA5,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x00A136D9B13CA7F7B885439F1FEDA1C95EBA23775819348F5706D51DC8
    unsigned char std_signature_s_1[] = {
        0x00,
        0xA1,
        0x36,
        0xD9,
        0xB1,
        0x3C,
        0xA7,
        0xF7,
        0xB8,
        0x85,
        0x43,
        0x9F,
        0x1F,
        0xED,
        0xA1,
        0xC9,
        0x5E,
        0xBA,
        0x23,
        0x77,
        0x58,
        0x19,
        0x34,
        0x8F,
        0x57,
        0x06,
        0xD5,
        0x1D,
        0xC8,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x00E9F09428C580461E27D53C9A8FE2F60A21FFDF7985FF1A1A38A5CAA2
    unsigned char std_signature_s_FF[] = {
        0x00,
        0xE9,
        0xF0,
        0x94,
        0x28,
        0xC5,
        0x80,
        0x46,
        0x1E,
        0x27,
        0xD5,
        0x3C,
        0x9A,
        0x8F,
        0xE2,
        0xF6,
        0x0A,
        0x21,
        0xFF,
        0xDF,
        0x79,
        0x85,
        0xFF,
        0x1A,
        0x1A,
        0x38,
        0xA5,
        0xCA,
        0xA2,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x00717024A2B6B118541D117BDF257005263EA50EF6CB00B72FE75E1F4F
    unsigned char std_signature_s_md5[] = {
        0x00,
        0x71,
        0x70,
        0x24,
        0xA2,
        0xB6,
        0xB1,
        0x18,
        0x54,
        0x1D,
        0x11,
        0x7B,
        0xDF,
        0x25,
        0x70,
        0x05,
        0x26,
        0x3E,
        0xA5,
        0x0E,
        0xF6,
        0xCB,
        0x00,
        0xB7,
        0x2F,
        0xE7,
        0x5E,
        0x1F,
        0x4F,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x002A8470EBC7EF1FB3B04190EACCC71960B065B0137D3C39EDADC1B6CA
    unsigned char std_signature_s_sha1[] = {
        0x00,
        0x2A,
        0x84,
        0x70,
        0xEB,
        0xC7,
        0xEF,
        0x1F,
        0xB3,
        0xB0,
        0x41,
        0x90,
        0xEA,
        0xCC,
        0xC7,
        0x19,
        0x60,
        0xB0,
        0x65,
        0xB0,
        0x13,
        0x7D,
        0x3C,
        0x39,
        0xED,
        0xAD,
        0xC1,
        0xB6,
        0xCA,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x005225C23A700A8054FCFC4612A0F7BA6D2ABBF380D16936DEC3B8A2EB
    unsigned char std_signature_s_192[] = {
        0x00,
        0x52,
        0x25,
        0xC2,
        0x3A,
        0x70,
        0x0A,
        0x80,
        0x54,
        0xFC,
        0xFC,
        0x46,
        0x12,
        0xA0,
        0xF7,
        0xBA,
        0x6D,
        0x2A,
        0xBB,
        0xF3,
        0x80,
        0xD1,
        0x69,
        0x36,
        0xDE,
        0xC3,
        0xB8,
        0xA2,
        0xEB,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x004B62B187B8E50CCDA384546F5D07194C8338A32B783B5B6CD48DA27C
    unsigned char std_signature_s_sha224[] = {
        0x00,
        0x4B,
        0x62,
        0xB1,
        0x87,
        0xB8,
        0xE5,
        0x0C,
        0xCD,
        0xA3,
        0x84,
        0x54,
        0x6F,
        0x5D,
        0x07,
        0x19,
        0x4C,
        0x83,
        0x38,
        0xA3,
        0x2B,
        0x78,
        0x3B,
        0x5B,
        0x6C,
        0xD4,
        0x8D,
        0xA2,
        0x7C,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x005333DF8CF14D0FC63B2594A8F5BAB62F1F536D04B97CACC3BF3A2205
    unsigned char std_signature_s_sha256[] = {
        0x00,
        0x53,
        0x33,
        0xDF,
        0x8C,
        0xF1,
        0x4D,
        0x0F,
        0xC6,
        0x3B,
        0x25,
        0x94,
        0xA8,
        0xF5,
        0xBA,
        0xB6,
        0x2F,
        0x1F,
        0x53,
        0x6D,
        0x04,
        0xB9,
        0x7C,
        0xAC,
        0xC3,
        0xBF,
        0x3A,
        0x22,
        0x05,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x006A43DB1AA99521E8228BDDF3656EBA9253A21F89D2B91DC32679DD1C
    unsigned char std_signature_s_sha384[] = {
        0x00,
        0x6A,
        0x43,
        0xDB,
        0x1A,
        0xA9,
        0x95,
        0x21,
        0xE8,
        0x22,
        0x8B,
        0xDD,
        0xF3,
        0x65,
        0x6E,
        0xBA,
        0x92,
        0x53,
        0xA2,
        0x1F,
        0x89,
        0xD2,
        0xB9,
        0x1D,
        0xC3,
        0x26,
        0x79,
        0xDD,
        0x1C,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x00F9E02D85BDDE49F1C5D18031F69D11CFA0A89ED0CC17DCFBF19F5699
    unsigned char std_signature_s_sha512[] = {
        0x00,
        0xF9,
        0xE0,
        0x2D,
        0x85,
        0xBD,
        0xDE,
        0x49,
        0xF1,
        0xC5,
        0xD1,
        0x80,
        0x31,
        0xF6,
        0x9D,
        0x11,
        0xCF,
        0xA0,
        0xA8,
        0x9E,
        0xD0,
        0xCC,
        0x17,
        0xDC,
        0xFB,
        0xF1,
        0x9F,
        0x56,
        0x99,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x009D4CCC878FF71A14559B4F0AD18A6F1BB17F0B201F06B59BEFB7723D
    unsigned char std_signature_s_544[] = {
        0x00,
        0x9D,
        0x4C,
        0xCC,
        0x87,
        0x8F,
        0xF7,
        0x1A,
        0x14,
        0x55,
        0x9B,
        0x4F,
        0x0A,
        0xD1,
        0x8A,
        0x6F,
        0x1B,
        0xB1,
        0x7F,
        0x0B,
        0x20,
        0x1F,
        0x06,
        0xB5,
        0x9B,
        0xEF,
        0xB7,
        0x72,
        0x3D,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp224k1;
    char         *curve_name = "secp224k1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
unsigned int ecdsa_std_test_secp256k1(void)
{
    //k:
    //0x1A3C9B2A61274E7D7FB051D3B4FB42411A8D6DB09B064606574E741AC909F448
    unsigned char rand_k[32] = {
        0x1A,
        0x3C,
        0x9B,
        0x2A,
        0x61,
        0x27,
        0x4E,
        0x7D,
        0x7F,
        0xB0,
        0x51,
        0xD3,
        0xB4,
        0xFB,
        0x42,
        0x41,
        0x1A,
        0x8D,
        0x6D,
        0xB0,
        0x9B,
        0x06,
        0x46,
        0x06,
        0x57,
        0x4E,
        0x74,
        0x1A,
        0xC9,
        0x09,
        0xF4,
        0x48,
    };

    //private key:
    //0x23CDCED066095AA72DE0192509A1E540DE341C1D4DC3B1DEB8A258A6BA26199C
    unsigned char priKey[32] = {
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

    //public key:
    //x coordinate:
    //0xE3B2EBEC783BB230F20F336E30FBA3BADD0A3453B4F6DCB77C0462B5166F795A
    //y coordinate:
    //0x171C91D560427708ED15DCFF24E858233881AD2478CBA05EC9145836B9C787D9
    unsigned char pubKey[64] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x7B256B5C40A2DF183C31EB8225DFCF4D34E1FE8C1E965EC99B59B2F21B4CB9D3
    unsigned char std_signature_r[] = {
        0x7B,
        0x25,
        0x6B,
        0x5C,
        0x40,
        0xA2,
        0xDF,
        0x18,
        0x3C,
        0x31,
        0xEB,
        0x82,
        0x25,
        0xDF,
        0xCF,
        0x4D,
        0x34,
        0xE1,
        0xFE,
        0x8C,
        0x1E,
        0x96,
        0x5E,
        0xC9,
        0x9B,
        0x59,
        0xB2,
        0xF2,
        0x1B,
        0x4C,
        0xB9,
        0xD3,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xFCB76138F28B3891BFF5DD5B6C658F1FCF9520B7BE8AAF498889FE0F69FE541E
    unsigned char std_signature_s_zero[] = {
        0xFC,
        0xB7,
        0x61,
        0x38,
        0xF2,
        0x8B,
        0x38,
        0x91,
        0xBF,
        0xF5,
        0xDD,
        0x5B,
        0x6C,
        0x65,
        0x8F,
        0x1F,
        0xCF,
        0x95,
        0x20,
        0xB7,
        0xBE,
        0x8A,
        0xAF,
        0x49,
        0x88,
        0x89,
        0xFE,
        0x0F,
        0x69,
        0xFE,
        0x54,
        0x1E,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0xE7E22A4570FDB5FEB3C8BE16B20CFC1E555D7331AEA9158440BC576EFD6B07D6
    unsigned char std_signature_s_1[] = {
        0xE7,
        0xE2,
        0x2A,
        0x45,
        0x70,
        0xFD,
        0xB5,
        0xFE,
        0xB3,
        0xC8,
        0xBE,
        0x16,
        0xB2,
        0x0C,
        0xFC,
        0x1E,
        0x55,
        0x5D,
        0x73,
        0x31,
        0xAE,
        0xA9,
        0x15,
        0x84,
        0x40,
        0xBC,
        0x57,
        0x6E,
        0xFD,
        0x6B,
        0x07,
        0xD6,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0xCB9A0039570135D35105E2C5F9838A9DC3E8AFDA465D4C8028062AD159F9BBCD
    unsigned char std_signature_s_FF[] = {
        0xCB,
        0x9A,
        0x00,
        0x39,
        0x57,
        0x01,
        0x35,
        0xD3,
        0x51,
        0x05,
        0xE2,
        0xC5,
        0xF9,
        0x83,
        0x8A,
        0x9D,
        0xC3,
        0xE8,
        0xAF,
        0xDA,
        0x46,
        0x5D,
        0x4C,
        0x80,
        0x28,
        0x06,
        0x2A,
        0xD1,
        0x59,
        0xF9,
        0xBB,
        0xCD,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x3CC71AAF75C4CBF33FB4E59E02A47A762A4E9DB2807D695478B97498B07AE9C7
    unsigned char std_signature_s_md5[] = {
        0x3C,
        0xC7,
        0x1A,
        0xAF,
        0x75,
        0xC4,
        0xCB,
        0xF3,
        0x3F,
        0xB4,
        0xE5,
        0x9E,
        0x02,
        0xA4,
        0x7A,
        0x76,
        0x2A,
        0x4E,
        0x9D,
        0xB2,
        0x80,
        0x7D,
        0x69,
        0x54,
        0x78,
        0xB9,
        0x74,
        0x98,
        0xB0,
        0x7A,
        0xE9,
        0xC7,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0xC58B0E3B01864101D11AC2E93293C79E65F824AD3473D31AB383696A59AA9B12
    unsigned char std_signature_s_sha1[] = {
        0xC5,
        0x8B,
        0x0E,
        0x3B,
        0x01,
        0x86,
        0x41,
        0x01,
        0xD1,
        0x1A,
        0xC2,
        0xE9,
        0x32,
        0x93,
        0xC7,
        0x9E,
        0x65,
        0xF8,
        0x24,
        0xAD,
        0x34,
        0x73,
        0xD3,
        0x1A,
        0xB3,
        0x83,
        0x69,
        0x6A,
        0x59,
        0xAA,
        0x9B,
        0x12,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x9B842E07BD999C674D7A8696C639B7940B2FAF56AE4576DB0B6B42EFDCBD87C3
    unsigned char std_signature_s_192[] = {
        0x9B,
        0x84,
        0x2E,
        0x07,
        0xBD,
        0x99,
        0x9C,
        0x67,
        0x4D,
        0x7A,
        0x86,
        0x96,
        0xC6,
        0x39,
        0xB7,
        0x94,
        0x0B,
        0x2F,
        0xAF,
        0x56,
        0xAE,
        0x45,
        0x76,
        0xDB,
        0x0B,
        0x6B,
        0x42,
        0xEF,
        0xDC,
        0xBD,
        0x87,
        0xC3,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x2FCD44BBB0C25DA0A0274A3BE3D0DD059F6CC0A79702A4CC2929A5429F63EA28
    unsigned char std_signature_s_sha224[] = {
        0x2F,
        0xCD,
        0x44,
        0xBB,
        0xB0,
        0xC2,
        0x5D,
        0xA0,
        0xA0,
        0x27,
        0x4A,
        0x3B,
        0xE3,
        0xD0,
        0xDD,
        0x05,
        0x9F,
        0x6C,
        0xC0,
        0xA7,
        0x97,
        0x02,
        0xA4,
        0xCC,
        0x29,
        0x29,
        0xA5,
        0x42,
        0x9F,
        0x63,
        0xEA,
        0x28,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x7DC5A714BC9B257EF61E4EC9A0B756E4060FA390E7BD049CCDBCEA77D7E52892
    unsigned char std_signature_s_sha256[] = {
        0x7D,
        0xC5,
        0xA7,
        0x14,
        0xBC,
        0x9B,
        0x25,
        0x7E,
        0xF6,
        0x1E,
        0x4E,
        0xC9,
        0xA0,
        0xB7,
        0x56,
        0xE4,
        0x06,
        0x0F,
        0xA3,
        0x90,
        0xE7,
        0xBD,
        0x04,
        0x9C,
        0xCD,
        0xBC,
        0xEA,
        0x77,
        0xD7,
        0xE5,
        0x28,
        0x92,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0xF7F74CF692E00FC6B441B6A26D98BF38D24D1FF1CE5C10447BB6FEB9AE230B22
    unsigned char std_signature_s_sha384[] = {
        0xF7,
        0xF7,
        0x4C,
        0xF6,
        0x92,
        0xE0,
        0x0F,
        0xC6,
        0xB4,
        0x41,
        0xB6,
        0xA2,
        0x6D,
        0x98,
        0xBF,
        0x38,
        0xD2,
        0x4D,
        0x1F,
        0xF1,
        0xCE,
        0x5C,
        0x10,
        0x44,
        0x7B,
        0xB6,
        0xFE,
        0xB9,
        0xAE,
        0x23,
        0x0B,
        0x22,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x1AE4EE4ED79CEFC41BEDAD8F840ACB04812D218BC2BD72EBA3117CF10AF01824
    unsigned char std_signature_s_sha512[] = {
        0x1A,
        0xE4,
        0xEE,
        0x4E,
        0xD7,
        0x9C,
        0xEF,
        0xC4,
        0x1B,
        0xED,
        0xAD,
        0x8F,
        0x84,
        0x0A,
        0xCB,
        0x04,
        0x81,
        0x2D,
        0x21,
        0x8B,
        0xC2,
        0xBD,
        0x72,
        0xEB,
        0xA3,
        0x11,
        0x7C,
        0xF1,
        0x0A,
        0xF0,
        0x18,
        0x24,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0xB156B35087E695F34CFF862C95508F56706D2737B052CDA51CCC4D91BDFA958A
    unsigned char std_signature_s_544[] = {
        0xB1,
        0x56,
        0xB3,
        0x50,
        0x87,
        0xE6,
        0x95,
        0xF3,
        0x4C,
        0xFF,
        0x86,
        0x2C,
        0x95,
        0x50,
        0x8F,
        0x56,
        0x70,
        0x6D,
        0x27,
        0x37,
        0xB0,
        0x52,
        0xCD,
        0xA5,
        0x1C,
        0xCC,
        0x4D,
        0x91,
        0xBD,
        0xFA,
        0x95,
        0x8A,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp256k1;
    char         *curve_name = "secp256k1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
unsigned int ecdsa_std_test_brainpoolp160r1(void)
{
    //k:
    //0xAC740C4BA74A2822E17FD7B46C0EDB2FD3203B5B
    unsigned char rand_k[20] = {
        0xAC,
        0x74,
        0x0C,
        0x4B,
        0xA7,
        0x4A,
        0x28,
        0x22,
        0xE1,
        0x7F,
        0xD7,
        0xB4,
        0x6C,
        0x0E,
        0xDB,
        0x2F,
        0xD3,
        0x20,
        0x3B,
        0x5B,
    };

    //private key:
    //0x7A9350281DFE699C31981F73CA2B45BF4C671F49
    unsigned char priKey[20] = {
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

    //public key:
    //x coordinate:
    //0xC2A3DE480E03FF21AACB2DD1265BD5612E00B8E0
    //y coordinate:
    //0x7931FF0C296BE9154B4AB3BCD984927A2898DC9A
    unsigned char pubKey[40] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x88AA4223B200E547B54C0BC5A739601FFE4D6DDA
    unsigned char std_signature_r[] = {
        0x88,
        0xAA,
        0x42,
        0x23,
        0xB2,
        0x00,
        0xE5,
        0x47,
        0xB5,
        0x4C,
        0x0B,
        0xC5,
        0xA7,
        0x39,
        0x60,
        0x1F,
        0xFE,
        0x4D,
        0x6D,
        0xDA,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x35DA7ADA4FD35D92A1EF4DF71436D34AF75F5AF6
    unsigned char std_signature_s_zero[] = {
        0x35,
        0xDA,
        0x7A,
        0xDA,
        0x4F,
        0xD3,
        0x5D,
        0x92,
        0xA1,
        0xEF,
        0x4D,
        0xF7,
        0x14,
        0x36,
        0xD3,
        0x4A,
        0xF7,
        0x5F,
        0x5A,
        0xF6,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x6AD6B14A503BC3091378DB102A0161A1334D669E
    unsigned char std_signature_s_1[] = {
        0x6A,
        0xD6,
        0xB1,
        0x4A,
        0x50,
        0x3B,
        0xC3,
        0x09,
        0x13,
        0x78,
        0xDB,
        0x10,
        0x2A,
        0x01,
        0x61,
        0xA1,
        0x33,
        0x4D,
        0x66,
        0x9E,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x65D9D8888064403260B0690AC9B7F6D8DD6383D3
    unsigned char std_signature_s_FF[] = {
        0x65,
        0xD9,
        0xD8,
        0x88,
        0x80,
        0x64,
        0x40,
        0x32,
        0x60,
        0xB0,
        0x69,
        0x0A,
        0xC9,
        0xB7,
        0xF6,
        0xD8,
        0xDD,
        0x63,
        0x83,
        0xD3,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x2BB2CF18BA4E105C5CFF57E5A9E6AA1129DC7A18
    unsigned char std_signature_s_md5[] = {
        0x2B,
        0xB2,
        0xCF,
        0x18,
        0xBA,
        0x4E,
        0x10,
        0x5C,
        0x5C,
        0xFF,
        0x57,
        0xE5,
        0xA9,
        0xE6,
        0xAA,
        0x11,
        0x29,
        0xDC,
        0x7A,
        0x18,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x0532AD96407D9261D4FAC0D540771AE4F115E6C0
    unsigned char std_signature_s_sha1[] = {
        0x05,
        0x32,
        0xAD,
        0x96,
        0x40,
        0x7D,
        0x92,
        0x61,
        0xD4,
        0xFA,
        0xC0,
        0xD5,
        0x40,
        0x77,
        0x1A,
        0xE4,
        0xF1,
        0x15,
        0xE6,
        0xC0,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xE59A7636E2FF3E771E6466A8B1BC6D0059111CB4
    unsigned char std_signature_s_192[] = {
        0xE5,
        0x9A,
        0x76,
        0x36,
        0xE2,
        0xFF,
        0x3E,
        0x77,
        0x1E,
        0x64,
        0x66,
        0xA8,
        0xB1,
        0xBC,
        0x6D,
        0x00,
        0x59,
        0x11,
        0x1C,
        0xB4,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x6B2B131F6390988178CC61BBCC7E27A4C6DEC79D
    unsigned char std_signature_s_sha224[] = {
        0x6B,
        0x2B,
        0x13,
        0x1F,
        0x63,
        0x90,
        0x98,
        0x81,
        0x78,
        0xCC,
        0x61,
        0xBB,
        0xCC,
        0x7E,
        0x27,
        0xA4,
        0xC6,
        0xDE,
        0xC7,
        0x9D,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0xD9806DA74F8162E3358FA05AF97FDB2CCEDC19E4
    unsigned char std_signature_s_sha256[] = {
        0xD9,
        0x80,
        0x6D,
        0xA7,
        0x4F,
        0x81,
        0x62,
        0xE3,
        0x35,
        0x8F,
        0xA0,
        0x5A,
        0xF9,
        0x7F,
        0xDB,
        0x2C,
        0xCE,
        0xDC,
        0x19,
        0xE4,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0xA472E5E2E974BDF20B8B9FA2A24FDADF94AC5555
    unsigned char std_signature_s_sha384[] = {
        0xA4,
        0x72,
        0xE5,
        0xE2,
        0xE9,
        0x74,
        0xBD,
        0xF2,
        0x0B,
        0x8B,
        0x9F,
        0xA2,
        0xA2,
        0x4F,
        0xDA,
        0xDF,
        0x94,
        0xAC,
        0x55,
        0x55,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x6C7ED52DBD533EFB29C09CCD8D1009E1E885EE53
    unsigned char std_signature_s_sha512[] = {
        0x6C,
        0x7E,
        0xD5,
        0x2D,
        0xBD,
        0x53,
        0x3E,
        0xFB,
        0x29,
        0xC0,
        0x9C,
        0xCD,
        0x8D,
        0x10,
        0x09,
        0xE1,
        0xE8,
        0x85,
        0xEE,
        0x53,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x1B03991FA6B15AE0A2EC038A59FC8721ACC4DB0D
    unsigned char std_signature_s_544[] = {
        0x1B,
        0x03,
        0x99,
        0x1F,
        0xA6,
        0xB1,
        0x5A,
        0xE0,
        0xA2,
        0xEC,
        0x03,
        0x8A,
        0x59,
        0xFC,
        0x87,
        0x21,
        0xAC,
        0xC4,
        0xDB,
        0x0D,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)brainpoolp160r1;
    char         *curve_name = "brainpoolp160r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
unsigned int ecdsa_std_test_secp160r1(void)
{
    //k:
    //0x00A90A2273723397ACAA963E8FA7FDD13CA84FA7BF
    unsigned char rand_k[21] = {
        0x00,
        0xA9,
        0x0A,
        0x22,
        0x73,
        0x72,
        0x33,
        0x97,
        0xAC,
        0xAA,
        0x96,
        0x3E,
        0x8F,
        0xA7,
        0xFD,
        0xD1,
        0x3C,
        0xA8,
        0x4F,
        0xA7,
        0xBF,
    };

    //private key:
    //0x002E83568327FFC90881CACF48E3A9F1E496CF9E42
    unsigned char priKey[21] = {
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

    //public key:
    //x coordinate:
    //0xDAB328814D240EEBAADB745689B0D5AE3B07DA6A
    //y coordinate:
    //0xABC69A370796EC42276C50876BD8F8FA4497C6B5
    unsigned char pubKey[40] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x00B27B810EAD0FD85ADE2AE2E54C78A6819B7987D2
    unsigned char std_signature_r[] = {
        0x00,
        0xB2,
        0x7B,
        0x81,
        0x0E,
        0xAD,
        0x0F,
        0xD8,
        0x5A,
        0xDE,
        0x2A,
        0xE2,
        0xE5,
        0x4C,
        0x78,
        0xA6,
        0x81,
        0x9B,
        0x79,
        0x87,
        0xD2,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x002ECEA81983B0611F20EF48737C2BE42C13CA9E0A
    unsigned char std_signature_s_zero[] = {
        0x00,
        0x2E,
        0xCE,
        0xA8,
        0x19,
        0x83,
        0xB0,
        0x61,
        0x1F,
        0x20,
        0xEF,
        0x48,
        0x73,
        0x7C,
        0x2B,
        0xE4,
        0x2C,
        0x13,
        0xCA,
        0x9E,
        0x0A,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x008AB9EE0BD1E5A04A64D746CD93FB09488F50C90D
    unsigned char std_signature_s_1[] = {
        0x00,
        0x8A,
        0xB9,
        0xEE,
        0x0B,
        0xD1,
        0xE5,
        0xA0,
        0x4A,
        0x64,
        0xD7,
        0x46,
        0xCD,
        0x93,
        0xFB,
        0x09,
        0x48,
        0x8F,
        0x50,
        0xC9,
        0x0D,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x003C013F2DAA8F52C505045A7332AC63B025BACB51
    unsigned char std_signature_s_FF[] = {
        0x00,
        0x3C,
        0x01,
        0x3F,
        0x2D,
        0xAA,
        0x8F,
        0x52,
        0xC5,
        0x05,
        0x04,
        0x5A,
        0x73,
        0x32,
        0xAC,
        0x63,
        0xB0,
        0x25,
        0xBA,
        0xCB,
        0x51,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x0090866F3129E806BB382CD6DFA6F51E17D94AF8E9
    unsigned char std_signature_s_md5[] = {
        0x00,
        0x90,
        0x86,
        0x6F,
        0x31,
        0x29,
        0xE8,
        0x06,
        0xBB,
        0x38,
        0x2C,
        0xD6,
        0xDF,
        0xA6,
        0xF5,
        0x1E,
        0x17,
        0xD9,
        0x4A,
        0xF8,
        0xE9,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x005084B11A9DB63FA509C8C5A42628DC1A7D440209
    unsigned char std_signature_s_sha1[] = {
        0x00,
        0x50,
        0x84,
        0xB1,
        0x1A,
        0x9D,
        0xB6,
        0x3F,
        0xA5,
        0x09,
        0xC8,
        0xC5,
        0xA4,
        0x26,
        0x28,
        0xDC,
        0x1A,
        0x7D,
        0x44,
        0x02,
        0x09,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x0071A9A7439ADE48D631CCCD0961D79AA59097FB9A
    unsigned char std_signature_s_192[] = {
        0x00,
        0x71,
        0xA9,
        0xA7,
        0x43,
        0x9A,
        0xDE,
        0x48,
        0xD6,
        0x31,
        0xCC,
        0xCD,
        0x09,
        0x61,
        0xD7,
        0x9A,
        0xA5,
        0x90,
        0x97,
        0xFB,
        0x9A,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x0047ED1909699DA03790C5731709E44C615B6B6478
    unsigned char std_signature_s_sha224[] = {
        0x00,
        0x47,
        0xED,
        0x19,
        0x09,
        0x69,
        0x9D,
        0xA0,
        0x37,
        0x90,
        0xC5,
        0x73,
        0x17,
        0x09,
        0xE4,
        0x4C,
        0x61,
        0x5B,
        0x6B,
        0x64,
        0x78,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x009C767B676040D8087DAA8615503242DFAB35AB97
    unsigned char std_signature_s_sha256[] = {
        0x00,
        0x9C,
        0x76,
        0x7B,
        0x67,
        0x60,
        0x40,
        0xD8,
        0x08,
        0x7D,
        0xAA,
        0x86,
        0x15,
        0x50,
        0x32,
        0x42,
        0xDF,
        0xAB,
        0x35,
        0xAB,
        0x97,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x008B569FE5AD514DB94FFC61C03EF7AC036ED5505E
    unsigned char std_signature_s_sha384[] = {
        0x00,
        0x8B,
        0x56,
        0x9F,
        0xE5,
        0xAD,
        0x51,
        0x4D,
        0xB9,
        0x4F,
        0xFC,
        0x61,
        0xC0,
        0x3E,
        0xF7,
        0xAC,
        0x03,
        0x6E,
        0xD5,
        0x50,
        0x5E,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x004975DA6624847BA196AB103969172C82C5F35A3F
    unsigned char std_signature_s_sha512[] = {
        0x00,
        0x49,
        0x75,
        0xDA,
        0x66,
        0x24,
        0x84,
        0x7B,
        0xA1,
        0x96,
        0xAB,
        0x10,
        0x39,
        0x69,
        0x17,
        0x2C,
        0x82,
        0xC5,
        0xF3,
        0x5A,
        0x3F,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x0086FFB81C48C9B300FD5F9A117DE910B900CDF7FB
    unsigned char std_signature_s_544[] = {
        0x00,
        0x86,
        0xFF,
        0xB8,
        0x1C,
        0x48,
        0xC9,
        0xB3,
        0x00,
        0xFD,
        0x5F,
        0x9A,
        0x11,
        0x7D,
        0xE9,
        0x10,
        0xB9,
        0x00,
        0xCD,
        0xF7,
        0xFB,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp160r1;
    char         *curve_name = "secp160r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
unsigned int ecdsa_std_test_secp160r2(void)
{
    //k:
    //0x0074FBB617A69CAA7CC3213E8E91EE3A0BD825B675
    unsigned char rand_k[21] = {
        0x00,
        0x74,
        0xFB,
        0xB6,
        0x17,
        0xA6,
        0x9C,
        0xAA,
        0x7C,
        0xC3,
        0x21,
        0x3E,
        0x8E,
        0x91,
        0xEE,
        0x3A,
        0x0B,
        0xD8,
        0x25,
        0xB6,
        0x75,
    };

    //private key:
    //0x007B5B20F7F3CC9BA43C613905F82F80F3CF5B42F3
    unsigned char priKey[21] = {
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

    //public key:
    //x coordinate:
    //0x43FE2AC8811A3862B9EFE0CF0CE4BF45B9F1A466
    //y coordinate:
    //0x7A9F72FE992C489D01C90DCCCCDA0342E122909B
    unsigned char pubKey[40] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x00D4A6DD49243C8036F3A4ABB8F2F3019456978AA4
    unsigned char std_signature_r[] = {
        0x00,
        0xD4,
        0xA6,
        0xDD,
        0x49,
        0x24,
        0x3C,
        0x80,
        0x36,
        0xF3,
        0xA4,
        0xAB,
        0xB8,
        0xF2,
        0xF3,
        0x01,
        0x94,
        0x56,
        0x97,
        0x8A,
        0xA4,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x002CC3A4FF936856CD1E0695926A42535436115471
    unsigned char std_signature_s_zero[] = {
        0x00,
        0x2C,
        0xC3,
        0xA4,
        0xFF,
        0x93,
        0x68,
        0x56,
        0xCD,
        0x1E,
        0x06,
        0x95,
        0x92,
        0x6A,
        0x42,
        0x53,
        0x54,
        0x36,
        0x11,
        0x54,
        0x71,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x009098BEFF362406385EFA37452AB738A1152767A0
    unsigned char std_signature_s_1[] = {
        0x00,
        0x90,
        0x98,
        0xBE,
        0xFF,
        0x36,
        0x24,
        0x06,
        0x38,
        0x5E,
        0xFA,
        0x37,
        0x45,
        0x2A,
        0xB7,
        0x38,
        0xA1,
        0x15,
        0x27,
        0x67,
        0xA0,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x002939DE2F10A1C4C60D8AA0F55194914CD2D801F0
    unsigned char std_signature_s_FF[] = {
        0x00,
        0x29,
        0x39,
        0xDE,
        0x2F,
        0x10,
        0xA1,
        0xC4,
        0xC6,
        0x0D,
        0x8A,
        0xA0,
        0xF5,
        0x51,
        0x94,
        0x91,
        0x4C,
        0xD2,
        0xD8,
        0x01,
        0xF0,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x00B99E6B6606898B2C8EB5CE602F33614708C7A2D8
    unsigned char std_signature_s_md5[] = {
        0x00,
        0xB9,
        0x9E,
        0x6B,
        0x66,
        0x06,
        0x89,
        0x8B,
        0x2C,
        0x8E,
        0xB5,
        0xCE,
        0x60,
        0x2F,
        0x33,
        0x61,
        0x47,
        0x08,
        0xC7,
        0xA2,
        0xD8,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x00F68CB3C5ED2FEE3CB1BEDDA0C29219AF9B238B80
    unsigned char std_signature_s_sha1[] = {
        0x00,
        0xF6,
        0x8C,
        0xB3,
        0xC5,
        0xED,
        0x2F,
        0xEE,
        0x3C,
        0xB1,
        0xBE,
        0xDD,
        0xA0,
        0xC2,
        0x92,
        0x19,
        0xAF,
        0x9B,
        0x23,
        0x8B,
        0x80,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x00B02C96C23F19F50A793364376EC84FD80F16EC02
    unsigned char std_signature_s_192[] = {
        0x00,
        0xB0,
        0x2C,
        0x96,
        0xC2,
        0x3F,
        0x19,
        0xF5,
        0x0A,
        0x79,
        0x33,
        0x64,
        0x37,
        0x6E,
        0xC8,
        0x4F,
        0xD8,
        0x0F,
        0x16,
        0xEC,
        0x02,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x00E32FA06DC55BC8EEA969D3D66A5EF9496B16816C
    unsigned char std_signature_s_sha224[] = {
        0x00,
        0xE3,
        0x2F,
        0xA0,
        0x6D,
        0xC5,
        0x5B,
        0xC8,
        0xEE,
        0xA9,
        0x69,
        0xD3,
        0xD6,
        0x6A,
        0x5E,
        0xF9,
        0x49,
        0x6B,
        0x16,
        0x81,
        0x6C,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x00CE1612370C7C07A34C31DB80D6F527AB7A43C879
    unsigned char std_signature_s_sha256[] = {
        0x00,
        0xCE,
        0x16,
        0x12,
        0x37,
        0x0C,
        0x7C,
        0x07,
        0xA3,
        0x4C,
        0x31,
        0xDB,
        0x80,
        0xD6,
        0xF5,
        0x27,
        0xAB,
        0x7A,
        0x43,
        0xC8,
        0x79,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x00E686B4116615089DA78F5D48BC0BB5523C7AC165
    unsigned char std_signature_s_sha384[] = {
        0x00,
        0xE6,
        0x86,
        0xB4,
        0x11,
        0x66,
        0x15,
        0x08,
        0x9D,
        0xA7,
        0x8F,
        0x5D,
        0x48,
        0xBC,
        0x0B,
        0xB5,
        0x52,
        0x3C,
        0x7A,
        0xC1,
        0x65,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x0000317D36DF9D508E4273D038EE23D27608BF1DAF
    unsigned char std_signature_s_sha512[] = {
        0x00,
        0x00,
        0x31,
        0x7D,
        0x36,
        0xDF,
        0x9D,
        0x50,
        0x8E,
        0x42,
        0x73,
        0xD0,
        0x38,
        0xEE,
        0x23,
        0xD2,
        0x76,
        0x08,
        0xBF,
        0x1D,
        0xAF,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x00CDE9E4B50AF12983A005F4BE70FDC0666CE0A10E
    unsigned char std_signature_s_544[] = {
        0x00,
        0xCD,
        0xE9,
        0xE4,
        0xB5,
        0x0A,
        0xF1,
        0x29,
        0x83,
        0xA0,
        0x05,
        0xF4,
        0xBE,
        0x70,
        0xFD,
        0xC0,
        0x66,
        0x6C,
        0xE0,
        0xA1,
        0x0E,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp160r2;
    char         *curve_name = "secp160r2";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
unsigned int ecdsa_std_test_secp192r1(void)
{
    //k:
    //0xEBEA2ADF39B6CB622D65DEB26DD19B086D8D11320BC420FE
    unsigned char rand_k[24] = {
        0xEB,
        0xEA,
        0x2A,
        0xDF,
        0x39,
        0xB6,
        0xCB,
        0x62,
        0x2D,
        0x65,
        0xDE,
        0xB2,
        0x6D,
        0xD1,
        0x9B,
        0x08,
        0x6D,
        0x8D,
        0x11,
        0x32,
        0x0B,
        0xC4,
        0x20,
        0xFE,
    };

    //private key:
    //0x2895FC2E5B0F4492BD14E3F3F1BE46FF466E51B9B4CA361F
    unsigned char priKey[24] = {
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

    //public key:
    //x coordinate:
    //0xE2350E107CA81425A9AB14CB6C5C648C0F43361A5047FE05
    //y coordinate:
    //0x3E88121F72E69B8BDA0CE2E7BCE29828B2362DFCE046D3FA
    unsigned char pubKey[48] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x1B17A8469AF9620FE5254D5CBC41B4C75E9D005302981ADE
    unsigned char std_signature_r[] = {
        0x1B,
        0x17,
        0xA8,
        0x46,
        0x9A,
        0xF9,
        0x62,
        0x0F,
        0xE5,
        0x25,
        0x4D,
        0x5C,
        0xBC,
        0x41,
        0xB4,
        0xC7,
        0x5E,
        0x9D,
        0x00,
        0x53,
        0x02,
        0x98,
        0x1A,
        0xDE,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x8129F3D681FAECAAD5900FC0874DF5DA198A3DB5590D5C0C
    unsigned char std_signature_s_zero[] = {
        0x81,
        0x29,
        0xF3,
        0xD6,
        0x81,
        0xFA,
        0xEC,
        0xAA,
        0xD5,
        0x90,
        0x0F,
        0xC0,
        0x87,
        0x4D,
        0xF5,
        0xDA,
        0x19,
        0x8A,
        0x3D,
        0xB5,
        0x59,
        0x0D,
        0x5C,
        0x0C,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x0E6D6832380B1ABB16CAC46FF187CD8B242B458DF6EDE2CC
    unsigned char std_signature_s_1[] = {
        0x0E,
        0x6D,
        0x68,
        0x32,
        0x38,
        0x0B,
        0x1A,
        0xBB,
        0x16,
        0xCA,
        0xC4,
        0x6F,
        0xF1,
        0x87,
        0xCD,
        0x8B,
        0x24,
        0x2B,
        0x45,
        0x8D,
        0xF6,
        0xED,
        0xE2,
        0xCC,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x85420CEA230555D4C95AC6C38BCC1077C13630517D834B0B
    unsigned char std_signature_s_FF[] = {
        0x85,
        0x42,
        0x0C,
        0xEA,
        0x23,
        0x05,
        0x55,
        0xD4,
        0xC9,
        0x5A,
        0xC6,
        0xC3,
        0x8B,
        0xCC,
        0x10,
        0x77,
        0xC1,
        0x36,
        0x30,
        0x51,
        0x7D,
        0x83,
        0x4B,
        0x0B,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x4C36C230A25DDD74D6A3DD620EFDAE4A59B40D63A168B3E8
    unsigned char std_signature_s_md5[] = {
        0x4C,
        0x36,
        0xC2,
        0x30,
        0xA2,
        0x5D,
        0xDD,
        0x74,
        0xD6,
        0xA3,
        0xDD,
        0x62,
        0x0E,
        0xFD,
        0xAE,
        0x4A,
        0x59,
        0xB4,
        0x0D,
        0x63,
        0xA1,
        0x68,
        0xB3,
        0xE8,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0xF8D0EFD2643DDBE0001686E0260D58FB195C1C9507DD0B8E
    unsigned char std_signature_s_sha1[] = {
        0xF8,
        0xD0,
        0xEF,
        0xD2,
        0x64,
        0x3D,
        0xDB,
        0xE0,
        0x00,
        0x16,
        0x86,
        0xE0,
        0x26,
        0x0D,
        0x58,
        0xFB,
        0x19,
        0x5C,
        0x1C,
        0x95,
        0x07,
        0xDD,
        0x0B,
        0x8E,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xEBA311307276E509E22D9149C22EE3A9479AD33235078C3F
    unsigned char std_signature_s_192[] = {
        0xEB,
        0xA3,
        0x11,
        0x30,
        0x72,
        0x76,
        0xE5,
        0x09,
        0xE2,
        0x2D,
        0x91,
        0x49,
        0xC2,
        0x2E,
        0xE3,
        0xA9,
        0x47,
        0x9A,
        0xD3,
        0x32,
        0x35,
        0x07,
        0x8C,
        0x3F,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x34F8D50229A34DA5EEC51A4BDA11553FAAC024985F6B39AA
    unsigned char std_signature_s_sha224[] = {
        0x34,
        0xF8,
        0xD5,
        0x02,
        0x29,
        0xA3,
        0x4D,
        0xA5,
        0xEE,
        0xC5,
        0x1A,
        0x4B,
        0xDA,
        0x11,
        0x55,
        0x3F,
        0xAA,
        0xC0,
        0x24,
        0x98,
        0x5F,
        0x6B,
        0x39,
        0xAA,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x467A26F1358E74904554F83A2EC6B6620B98C9F7A7D1B459
    unsigned char std_signature_s_sha256[] = {
        0x46,
        0x7A,
        0x26,
        0xF1,
        0x35,
        0x8E,
        0x74,
        0x90,
        0x45,
        0x54,
        0xF8,
        0x3A,
        0x2E,
        0xC6,
        0xB6,
        0x62,
        0x0B,
        0x98,
        0xC9,
        0xF7,
        0xA7,
        0xD1,
        0xB4,
        0x59,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x44C833DB58077004D96005B87F22F1EDB1EF6EE6EA2277D9
    unsigned char std_signature_s_sha384[] = {
        0x44,
        0xC8,
        0x33,
        0xDB,
        0x58,
        0x07,
        0x70,
        0x04,
        0xD9,
        0x60,
        0x05,
        0xB8,
        0x7F,
        0x22,
        0xF1,
        0xED,
        0xB1,
        0xEF,
        0x6E,
        0xE6,
        0xEA,
        0x22,
        0x77,
        0xD9,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0xC616D3F2312DB7DBF0DD54680066FB482A8B1DEE22F0BE52
    unsigned char std_signature_s_sha512[] = {
        0xC6,
        0x16,
        0xD3,
        0xF2,
        0x31,
        0x2D,
        0xB7,
        0xDB,
        0xF0,
        0xDD,
        0x54,
        0x68,
        0x00,
        0x66,
        0xFB,
        0x48,
        0x2A,
        0x8B,
        0x1D,
        0xEE,
        0x22,
        0xF0,
        0xBE,
        0x52,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0xCE73750EAD76B87FAB11D0917108C15115A9D863B8BF7D97
    unsigned char std_signature_s_544[] = {
        0xCE,
        0x73,
        0x75,
        0x0E,
        0xAD,
        0x76,
        0xB8,
        0x7F,
        0xAB,
        0x11,
        0xD0,
        0x91,
        0x71,
        0x08,
        0xC1,
        0x51,
        0x15,
        0xA9,
        0xD8,
        0x63,
        0xB8,
        0xBF,
        0x7D,
        0x97,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp192r1;
    char         *curve_name = "secp192r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
unsigned int ecdsa_std_test_secp224r1(void)
{
    //k:
    //0x7DCA720556BED86B94D8DE70FBDAF9B36B4464082157DC8DB4B68142
    unsigned char rand_k[28] = {
        0x7D,
        0xCA,
        0x72,
        0x05,
        0x56,
        0xBE,
        0xD8,
        0x6B,
        0x94,
        0xD8,
        0xDE,
        0x70,
        0xFB,
        0xDA,
        0xF9,
        0xB3,
        0x6B,
        0x44,
        0x64,
        0x08,
        0x21,
        0x57,
        0xDC,
        0x8D,
        0xB4,
        0xB6,
        0x81,
        0x42,
    };

    //private key:
    //0x6C98463D4FD3E88D11BD61C8A189AB97B831339C7B144C8F7BE241C4
    unsigned char priKey[28] = {
        0x6C,
        0x98,
        0x46,
        0x3D,
        0x4F,
        0xD3,
        0xE8,
        0x8D,
        0x11,
        0xBD,
        0x61,
        0xC8,
        0xA1,
        0x89,
        0xAB,
        0x97,
        0xB8,
        0x31,
        0x33,
        0x9C,
        0x7B,
        0x14,
        0x4C,
        0x8F,
        0x7B,
        0xE2,
        0x41,
        0xC4,
    };

    //public key:
    //x coordinate:
    //0x45A5F36E4E65C5C1F0194FED1F89F743FDE9008027C5D7981A0AA659
    //y coordinate:
    //0x5ED4AED9DEF447297B984AB844AC7E0D8FC76202767ABE825AE43036
    unsigned char pubKey[56] = {
        0x45,
        0xA5,
        0xF3,
        0x6E,
        0x4E,
        0x65,
        0xC5,
        0xC1,
        0xF0,
        0x19,
        0x4F,
        0xED,
        0x1F,
        0x89,
        0xF7,
        0x43,
        0xFD,
        0xE9,
        0x00,
        0x80,
        0x27,
        0xC5,
        0xD7,
        0x98,
        0x1A,
        0x0A,
        0xA6,
        0x59,
        0x5E,
        0xD4,
        0xAE,
        0xD9,
        0xDE,
        0xF4,
        0x47,
        0x29,
        0x7B,
        0x98,
        0x4A,
        0xB8,
        0x44,
        0xAC,
        0x7E,
        0x0D,
        0x8F,
        0xC7,
        0x62,
        0x02,
        0x76,
        0x7A,
        0xBE,
        0x82,
        0x5A,
        0xE4,
        0x30,
        0x36,
    };

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x206ABC1874FDF4001BAD8C842812897869CB1C84338E4961C3DE23EC
    unsigned char std_signature_r[] = {
        0x20,
        0x6A,
        0xBC,
        0x18,
        0x74,
        0xFD,
        0xF4,
        0x00,
        0x1B,
        0xAD,
        0x8C,
        0x84,
        0x28,
        0x12,
        0x89,
        0x78,
        0x69,
        0xCB,
        0x1C,
        0x84,
        0x33,
        0x8E,
        0x49,
        0x61,
        0xC3,
        0xDE,
        0x23,
        0xEC,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xF20C6BB7957F9960A585313F6746B47753C50FAC958454634AE70C11
    unsigned char std_signature_s_zero[] = {
        0xF2,
        0x0C,
        0x6B,
        0xB7,
        0x95,
        0x7F,
        0x99,
        0x60,
        0xA5,
        0x85,
        0x31,
        0x3F,
        0x67,
        0x46,
        0xB4,
        0x77,
        0x53,
        0xC5,
        0x0F,
        0xAC,
        0x95,
        0x84,
        0x54,
        0x63,
        0x4A,
        0xE7,
        0x0C,
        0x11,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x42B8E8305E8D673BB92428D2ACEC4CF8D097BD325020BD79BA5CEB0D
    unsigned char std_signature_s_1[] = {
        0x42,
        0xB8,
        0xE8,
        0x30,
        0x5E,
        0x8D,
        0x67,
        0x3B,
        0xB9,
        0x24,
        0x28,
        0xD2,
        0xAC,
        0xEC,
        0x4C,
        0xF8,
        0xD0,
        0x97,
        0xBD,
        0x32,
        0x50,
        0x20,
        0xBD,
        0x79,
        0xBA,
        0x5C,
        0xEB,
        0x0D,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0xBA71D1FF31A7D8C99711329B0FCDF588D15A10D509BF02F47E17D572
    unsigned char std_signature_s_FF[] = {
        0xBA,
        0x71,
        0xD1,
        0xFF,
        0x31,
        0xA7,
        0xD8,
        0xC9,
        0x97,
        0x11,
        0x32,
        0x9B,
        0x0F,
        0xCD,
        0xF5,
        0x88,
        0xD1,
        0x5A,
        0x10,
        0xD5,
        0x09,
        0xBF,
        0x02,
        0xF4,
        0x7E,
        0x17,
        0xD5,
        0x72,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x54677FF6F874ABCDCFEDDF33B2FB509777C7419504FF49649040D777
    unsigned char std_signature_s_md5[] = {
        0x54,
        0x67,
        0x7F,
        0xF6,
        0xF8,
        0x74,
        0xAB,
        0xCD,
        0xCF,
        0xED,
        0xDF,
        0x33,
        0xB2,
        0xFB,
        0x50,
        0x97,
        0x77,
        0xC7,
        0x41,
        0x95,
        0x04,
        0xFF,
        0x49,
        0x64,
        0x90,
        0x40,
        0xD7,
        0x77,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x4ADAFE59ABA60A3F64ECFC6C5BDD234848F21C2EA388B7CDBBB34DC2
    unsigned char std_signature_s_sha1[] = {
        0x4A,
        0xDA,
        0xFE,
        0x59,
        0xAB,
        0xA6,
        0x0A,
        0x3F,
        0x64,
        0xEC,
        0xFC,
        0x6C,
        0x5B,
        0xDD,
        0x23,
        0x48,
        0x48,
        0xF2,
        0x1C,
        0x2E,
        0xA3,
        0x88,
        0xB7,
        0xCD,
        0xBB,
        0xB3,
        0x4D,
        0xC2,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xF8075A08C333760D1A2843BD9937E8086CD1C3611F7B697FA1DA6792
    unsigned char std_signature_s_192[] = {
        0xF8,
        0x07,
        0x5A,
        0x08,
        0xC3,
        0x33,
        0x76,
        0x0D,
        0x1A,
        0x28,
        0x43,
        0xBD,
        0x99,
        0x37,
        0xE8,
        0x08,
        0x6C,
        0xD1,
        0xC3,
        0x61,
        0x1F,
        0x7B,
        0x69,
        0x7F,
        0xA1,
        0xDA,
        0x67,
        0x92,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0xC109886E551288328DA88BE8DC085DD806F56B38E3E7EE2557CC0C24
    unsigned char std_signature_s_sha224[] = {
        0xC1,
        0x09,
        0x88,
        0x6E,
        0x55,
        0x12,
        0x88,
        0x32,
        0x8D,
        0xA8,
        0x8B,
        0xE8,
        0xDC,
        0x08,
        0x5D,
        0xD8,
        0x06,
        0xF5,
        0x6B,
        0x38,
        0xE3,
        0xE7,
        0xEE,
        0x25,
        0x57,
        0xCC,
        0x0C,
        0x24,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x587034F1158E98E23B32535748E5B3A9D7E7D850CD27DB8391C4FE5B
    unsigned char std_signature_s_sha256[] = {
        0x58,
        0x70,
        0x34,
        0xF1,
        0x15,
        0x8E,
        0x98,
        0xE2,
        0x3B,
        0x32,
        0x53,
        0x57,
        0x48,
        0xE5,
        0xB3,
        0xA9,
        0xD7,
        0xE7,
        0xD8,
        0x50,
        0xCD,
        0x27,
        0xDB,
        0x83,
        0x91,
        0xC4,
        0xFE,
        0x5B,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x53B48C56BA9E7CF74993B0EA238E19B3C9A7610D400F5769D4B61378
    unsigned char std_signature_s_sha384[] = {
        0x53,
        0xB4,
        0x8C,
        0x56,
        0xBA,
        0x9E,
        0x7C,
        0xF7,
        0x49,
        0x93,
        0xB0,
        0xEA,
        0x23,
        0x8E,
        0x19,
        0xB3,
        0xC9,
        0xA7,
        0x61,
        0x0D,
        0x40,
        0x0F,
        0x57,
        0x69,
        0xD4,
        0xB6,
        0x13,
        0x78,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0xB29E0E647F1B250A67CE71F1CC6DBFB2ED10C1E05ABD6CA20F7CB5D4
    unsigned char std_signature_s_sha512[] = {
        0xB2,
        0x9E,
        0x0E,
        0x64,
        0x7F,
        0x1B,
        0x25,
        0x0A,
        0x67,
        0xCE,
        0x71,
        0xF1,
        0xCC,
        0x6D,
        0xBF,
        0xB2,
        0xED,
        0x10,
        0xC1,
        0xE0,
        0x5A,
        0xBD,
        0x6C,
        0xA2,
        0x0F,
        0x7C,
        0xB5,
        0xD4,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0xA0624483A9BE503A1CB8032B35307528C5477A10CEE6CFAAB0D50F1B
    unsigned char std_signature_s_544[] = {
        0xA0,
        0x62,
        0x44,
        0x83,
        0xA9,
        0xBE,
        0x50,
        0x3A,
        0x1C,
        0xB8,
        0x03,
        0x2B,
        0x35,
        0x30,
        0x75,
        0x28,
        0xC5,
        0x47,
        0x7A,
        0x10,
        0xCE,
        0xE6,
        0xCF,
        0xAA,
        0xB0,
        0xD5,
        0x0F,
        0x1B,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp224r1;
    char         *curve_name = "secp224r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
unsigned int ecdsa_std_test_brainpoolp256r1(void)
{
    //k:
    //0x18C6007914412883E3BB26DD2E3C6277E145A2222830635E2720BC4232DA6B14
    unsigned char rand_k[32] = {
        0x18,
        0xC6,
        0x00,
        0x79,
        0x14,
        0x41,
        0x28,
        0x83,
        0xE3,
        0xBB,
        0x26,
        0xDD,
        0x2E,
        0x3C,
        0x62,
        0x77,
        0xE1,
        0x45,
        0xA2,
        0x22,
        0x28,
        0x30,
        0x63,
        0x5E,
        0x27,
        0x20,
        0xBC,
        0x42,
        0x32,
        0xDA,
        0x6B,
        0x14,
    };

    //private key:
    //0x805966F7674CE4BD08694EC0AB638B9AFBD990275E0FF6C140BF82D87939A15A
    unsigned char priKey[32] = {
        0x80,
        0x59,
        0x66,
        0xF7,
        0x67,
        0x4C,
        0xE4,
        0xBD,
        0x08,
        0x69,
        0x4E,
        0xC0,
        0xAB,
        0x63,
        0x8B,
        0x9A,
        0xFB,
        0xD9,
        0x90,
        0x27,
        0x5E,
        0x0F,
        0xF6,
        0xC1,
        0x40,
        0xBF,
        0x82,
        0xD8,
        0x79,
        0x39,
        0xA1,
        0x5A,
    };

    //public key:
    //x coordinate:
    //0x1183D93BA073F0F2ADE73221C06B22526AC7A732369B39001DA5073E2B2F3CAA
    //y coordinate:
    //0x1B5F929246EF62A16D78837E4E5BF0C146AB99C1E665B3BD4C4FAD8F067794FE
    unsigned char pubKey[64] = {
        0x11,
        0x83,
        0xD9,
        0x3B,
        0xA0,
        0x73,
        0xF0,
        0xF2,
        0xAD,
        0xE7,
        0x32,
        0x21,
        0xC0,
        0x6B,
        0x22,
        0x52,
        0x6A,
        0xC7,
        0xA7,
        0x32,
        0x36,
        0x9B,
        0x39,
        0x00,
        0x1D,
        0xA5,
        0x07,
        0x3E,
        0x2B,
        0x2F,
        0x3C,
        0xAA,
        0x1B,
        0x5F,
        0x92,
        0x92,
        0x46,
        0xEF,
        0x62,
        0xA1,
        0x6D,
        0x78,
        0x83,
        0x7E,
        0x4E,
        0x5B,
        0xF0,
        0xC1,
        0x46,
        0xAB,
        0x99,
        0xC1,
        0xE6,
        0x65,
        0xB3,
        0xBD,
        0x4C,
        0x4F,
        0xAD,
        0x8F,
        0x06,
        0x77,
        0x94,
        0xFE,
    };

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x6D79BD2DEAE80412D74062F41F0EC67F2A611FFB52DBB0378341CC90215B04ED
    unsigned char std_signature_r[] = {
        0x6D,
        0x79,
        0xBD,
        0x2D,
        0xEA,
        0xE8,
        0x04,
        0x12,
        0xD7,
        0x40,
        0x62,
        0xF4,
        0x1F,
        0x0E,
        0xC6,
        0x7F,
        0x2A,
        0x61,
        0x1F,
        0xFB,
        0x52,
        0xDB,
        0xB0,
        0x37,
        0x83,
        0x41,
        0xCC,
        0x90,
        0x21,
        0x5B,
        0x04,
        0xED,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x6676809450171C289E7E2579EE7B54061430A2712E0FC3FAE389B284E6A2E576
    unsigned char std_signature_s_zero[] = {
        0x66,
        0x76,
        0x80,
        0x94,
        0x50,
        0x17,
        0x1C,
        0x28,
        0x9E,
        0x7E,
        0x25,
        0x79,
        0xEE,
        0x7B,
        0x54,
        0x06,
        0x14,
        0x30,
        0xA2,
        0x71,
        0x2E,
        0x0F,
        0xC3,
        0xFA,
        0xE3,
        0x89,
        0xB2,
        0x84,
        0xE6,
        0xA2,
        0xE5,
        0x76,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x2C51BD8B594E27E914E2621F448ABC18B4F2D397A77BE60286089015D23C90ED
    unsigned char std_signature_s_1[] = {
        0x2C,
        0x51,
        0xBD,
        0x8B,
        0x59,
        0x4E,
        0x27,
        0xE9,
        0x14,
        0xE2,
        0x62,
        0x1F,
        0x44,
        0x8A,
        0xBC,
        0x18,
        0xB4,
        0xF2,
        0xD3,
        0x97,
        0xA7,
        0x7B,
        0xE6,
        0x02,
        0x86,
        0x08,
        0x90,
        0x15,
        0xD2,
        0x3C,
        0x90,
        0xED};

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x52ACF9E5A48C30D1C6C1A4F3D038F2A9E8B1A7278E3E34C99361375E67DFC3A4
    unsigned char std_signature_s_FF[] = {
        0x52,
        0xAC,
        0xF9,
        0xE5,
        0xA4,
        0x8C,
        0x30,
        0xD1,
        0xC6,
        0xC1,
        0xA4,
        0xF3,
        0xD0,
        0x38,
        0xF2,
        0xA9,
        0xE8,
        0xB1,
        0xA7,
        0x27,
        0x8E,
        0x3E,
        0x34,
        0xC9,
        0x93,
        0x61,
        0x37,
        0x5E,
        0x67,
        0xDF,
        0xC3,
        0xA4};


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x13EFB4F7722567554EA130039F25C97447Aadd8E339998D93A6395EAB896FC09
    unsigned char std_signature_s_md5[] = {
        0x13,
        0xEF,
        0xB4,
        0xF7,
        0x72,
        0x25,
        0x67,
        0x55,
        0x4E,
        0xA1,
        0x30,
        0x03,
        0x9F,
        0x25,
        0xC9,
        0x74,
        0x47,
        0xAA,
        0xDD,
        0x8E,
        0x33,
        0x99,
        0x98,
        0xD9,
        0x3A,
        0x63,
        0x95,
        0xEA,
        0xB8,
        0x96,
        0xFC,
        0x09,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x549A6AFB49C07FF385DC4BE867279A6559DCFC57AB5845F6AD9469C83DB1E785
    unsigned char std_signature_s_sha1[] = {
        0x54,
        0x9A,
        0x6A,
        0xFB,
        0x49,
        0xC0,
        0x7F,
        0xF3,
        0x85,
        0xDC,
        0x4B,
        0xE8,
        0x67,
        0x27,
        0x9A,
        0x65,
        0x59,
        0xDC,
        0xFC,
        0x57,
        0xAB,
        0x58,
        0x45,
        0xF6,
        0xAD,
        0x94,
        0x69,
        0xC8,
        0x3D,
        0xB1,
        0xE7,
        0x85,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xA383EA0C763A8E96E45FFC3C30A2548427D819ECFB8551A03DAB34F35BD495EB
    unsigned char std_signature_s_192[] = {
        0xA3,
        0x83,
        0xEA,
        0x0C,
        0x76,
        0x3A,
        0x8E,
        0x96,
        0xE4,
        0x5F,
        0xFC,
        0x3C,
        0x30,
        0xA2,
        0x54,
        0x84,
        0x27,
        0xD8,
        0x19,
        0xEC,
        0xFB,
        0x85,
        0x51,
        0xA0,
        0x3D,
        0xAB,
        0x34,
        0xF3,
        0x5B,
        0xD4,
        0x95,
        0xEB,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x0E3E70BE866D9C039C428751998914A6886B7F1ECC70E7C2CBBCE84DA546C488
    unsigned char std_signature_s_sha224[] = {
        0x0E,
        0x3E,
        0x70,
        0xBE,
        0x86,
        0x6D,
        0x9C,
        0x03,
        0x9C,
        0x42,
        0x87,
        0x51,
        0x99,
        0x89,
        0x14,
        0xA6,
        0x88,
        0x6B,
        0x7F,
        0x1E,
        0xCC,
        0x70,
        0xE7,
        0xC2,
        0xCB,
        0xBC,
        0xE8,
        0x4D,
        0xA5,
        0x46,
        0xC4,
        0x88,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x30DDF4F820FFB909DA2EE3E290473D846488B3AE06953508454123F074ECC52D
    unsigned char std_signature_s_sha256[] = {
        0x30,
        0xDD,
        0xF4,
        0xF8,
        0x20,
        0xFF,
        0xB9,
        0x09,
        0xDA,
        0x2E,
        0xE3,
        0xE2,
        0x90,
        0x47,
        0x3D,
        0x84,
        0x64,
        0x88,
        0xB3,
        0xAE,
        0x06,
        0x95,
        0x35,
        0x08,
        0x45,
        0x41,
        0x23,
        0xF0,
        0x74,
        0xEC,
        0xC5,
        0x2D,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x57569C393FAA37338D01DF0878ED736DF6BEE6752C7BBC6F13F14D3F922F9FD3
    unsigned char std_signature_s_sha384[] = {
        0x57,
        0x56,
        0x9C,
        0x39,
        0x3F,
        0xAA,
        0x37,
        0x33,
        0x8D,
        0x01,
        0xDF,
        0x08,
        0x78,
        0xED,
        0x73,
        0x6D,
        0xF6,
        0xBE,
        0xE6,
        0x75,
        0x2C,
        0x7B,
        0xBC,
        0x6F,
        0x13,
        0xF1,
        0x4D,
        0x3F,
        0x92,
        0x2F,
        0x9F,
        0xD3,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x76F11EF88F85BF382BEC4118D4B592593696F491579B2625E322FF536EC8CC91
    unsigned char std_signature_s_sha512[] = {
        0x76,
        0xF1,
        0x1E,
        0xF8,
        0x8F,
        0x85,
        0xBF,
        0x38,
        0x2B,
        0xEC,
        0x41,
        0x18,
        0xD4,
        0xB5,
        0x92,
        0x59,
        0x36,
        0x96,
        0xF4,
        0x91,
        0x57,
        0x9B,
        0x26,
        0x25,
        0xE3,
        0x22,
        0xFF,
        0x53,
        0x6E,
        0xC8,
        0xCC,
        0x91,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x7B85CCC3C12DC7D566945229E528BAB53567224116BE43E31BB3C0B4FC3CCD8A
    unsigned char std_signature_s_544[] = {
        0x7B,
        0x85,
        0xCC,
        0xC3,
        0xC1,
        0x2D,
        0xC7,
        0xD5,
        0x66,
        0x94,
        0x52,
        0x29,
        0xE5,
        0x28,
        0xBA,
        0xB5,
        0x35,
        0x67,
        0x22,
        0x41,
        0x16,
        0xBE,
        0x43,
        0xE3,
        0x1B,
        0xB3,
        0xC0,
        0xB4,
        0xFC,
        0x3C,
        0xCD,
        0x8A,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)brainpoolp256r1;
    char         *curve_name = "brainpoolp256r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
unsigned int ecdsa_std_test_secp256r1(void)
{
    //k:
    //0x05B2FAC1D8E526D8B6DBC634EBEEDFF98C8B0F246E7FFFA0D972D8FF8E58F288
    unsigned char rand_k[32] = {
        0x05,
        0xB2,
        0xFA,
        0xC1,
        0xD8,
        0xE5,
        0x26,
        0xD8,
        0xB6,
        0xDB,
        0xC6,
        0x34,
        0xEB,
        0xEE,
        0xDF,
        0xF9,
        0x8C,
        0x8B,
        0x0F,
        0x24,
        0x6E,
        0x7F,
        0xFF,
        0xA0,
        0xD9,
        0x72,
        0xD8,
        0xFF,
        0x8E,
        0x58,
        0xF2,
        0x88,
    };

    //private key:
    //0xF43BAFC3C7B2FB10AFEED65668D3634E3239C108BB6ACF34333149025584B30E
    unsigned char priKey[32] = {
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

    //public key:
    //x coordinate:
    //0xBD2FEF24AC636F55DBF1F5203885097E18629EDFFB36F40389612744A10F02D0
    //y coordinate:
    //0x6B519E0F82BB90D1633D07E8708F6595CEBFF3866CFE33F3CBE8A3681EB820EA
    unsigned char pubKey[64] = {
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

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0xE53135AC20D40A1F2388A9C53D723C906B4366FCFAD5BC8F4987F7D60EA64B1C
    unsigned char std_signature_r[] = {
        0xE5,
        0x31,
        0x35,
        0xAC,
        0x20,
        0xD4,
        0x0A,
        0x1F,
        0x23,
        0x88,
        0xA9,
        0xC5,
        0x3D,
        0x72,
        0x3C,
        0x90,
        0x6B,
        0x43,
        0x66,
        0xFC,
        0xFA,
        0xD5,
        0xBC,
        0x8F,
        0x49,
        0x87,
        0xF7,
        0xD6,
        0x0E,
        0xA6,
        0x4B,
        0x1C,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xB76EF4B0E5A683F374BF90D0B90A3A1B15087C1EBAA154FD3EBC8A7B8F02B20D
    unsigned char std_signature_s_zero[] = {
        0xB7,
        0x6E,
        0xF4,
        0xB0,
        0xE5,
        0xA6,
        0x83,
        0xF3,
        0x74,
        0xBF,
        0x90,
        0xD0,
        0xB9,
        0x0A,
        0x3A,
        0x1B,
        0x15,
        0x08,
        0x7C,
        0x1E,
        0xBA,
        0xA1,
        0x54,
        0xFD,
        0x3E,
        0xBC,
        0x8A,
        0x7B,
        0x8F,
        0x02,
        0xB2,
        0x0D,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0xC3C9ADD415CB37268B1FC1CD656508EBE592528FA251AFA9F9E1E0F700242B0A
    unsigned char std_signature_s_1[] = {
        0xC3,
        0xC9,
        0xAD,
        0xD4,
        0x15,
        0xCB,
        0x37,
        0x26,
        0x8B,
        0x1F,
        0xC1,
        0xCD,
        0x65,
        0x65,
        0x08,
        0xEB,
        0xE5,
        0x92,
        0x52,
        0x8F,
        0xA2,
        0x51,
        0xAF,
        0xA9,
        0xF9,
        0xE1,
        0xE0,
        0xF7,
        0x00,
        0x24,
        0x2B,
        0x0A,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x560FEF78F603AEA04BC9DBA467279D6A9CFB406EA21E8A6F8DC643EE56A419DC
    unsigned char std_signature_s_FF[] = {
        0x56,
        0x0F,
        0xEF,
        0x78,
        0xF6,
        0x03,
        0xAE,
        0xA0,
        0x4B,
        0xC9,
        0xDB,
        0xA4,
        0x67,
        0x27,
        0x9D,
        0x6A,
        0x9C,
        0xFB,
        0x40,
        0x6E,
        0xA2,
        0x1E,
        0x8A,
        0x6F,
        0x8D,
        0xC6,
        0x43,
        0xEE,
        0x56,
        0xA4,
        0x19,
        0xDC,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x3A19ECEC89A48943070B12ACF2C6874DFF4685A7E31805047B6300C9AE156160
    unsigned char std_signature_s_md5[] = {
        0x3A,
        0x19,
        0xEC,
        0xEC,
        0x89,
        0xA4,
        0x89,
        0x43,
        0x07,
        0x0B,
        0x12,
        0xAC,
        0xF2,
        0xC6,
        0x87,
        0x4D,
        0xFF,
        0x46,
        0x85,
        0xA7,
        0xE3,
        0x18,
        0x05,
        0x04,
        0x7B,
        0x63,
        0x00,
        0xC9,
        0xAE,
        0x15,
        0x61,
        0x60,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x46D96A779797568B552FE77A721EC4F6D575FA924AADE918D27372A603160B5F
    unsigned char std_signature_s_sha1[] = {
        0x46,
        0xD9,
        0x6A,
        0x77,
        0x97,
        0x97,
        0x56,
        0x8B,
        0x55,
        0x2F,
        0xE7,
        0x7A,
        0x72,
        0x1E,
        0xC4,
        0xF6,
        0xD5,
        0x75,
        0xFA,
        0x92,
        0x4A,
        0xAD,
        0xE9,
        0x18,
        0xD2,
        0x73,
        0x72,
        0xA6,
        0x03,
        0x16,
        0x0B,
        0x5F,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x8F38365A9C7375E6517C786760B1D5CD050481CA8A8AD0D4D4BC1F390E4CE4C3
    unsigned char std_signature_s_192[] = {
        0x8F,
        0x38,
        0x36,
        0x5A,
        0x9C,
        0x73,
        0x75,
        0xE6,
        0x51,
        0x7C,
        0x78,
        0x67,
        0x60,
        0xB1,
        0xD5,
        0xCD,
        0x05,
        0x04,
        0x81,
        0xCA,
        0x8A,
        0x8A,
        0xD0,
        0xD4,
        0xD4,
        0xBC,
        0x1F,
        0x39,
        0x0E,
        0x4C,
        0xE4,
        0xC3,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x79759E92B853474D7CE512F4B24D0408350BBB34A5E1B893F742967D67A266FE
    unsigned char std_signature_s_sha224[] = {
        0x79,
        0x75,
        0x9E,
        0x92,
        0xB8,
        0x53,
        0x47,
        0x4D,
        0x7C,
        0xE5,
        0x12,
        0xF4,
        0xB2,
        0x4D,
        0x04,
        0x08,
        0x35,
        0x0B,
        0xBB,
        0x34,
        0xA5,
        0xE1,
        0xB8,
        0x93,
        0xF7,
        0x42,
        0x96,
        0x7D,
        0x67,
        0xA2,
        0x66,
        0xFE,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0xC988BF9FC414AD7B1227BE793B5F27242E1A4CA952275F4CF20DD401FB547CF5
    unsigned char std_signature_s_sha256[] = {
        0xC9,
        0x88,
        0xBF,
        0x9F,
        0xC4,
        0x14,
        0xAD,
        0x7B,
        0x12,
        0x27,
        0xBE,
        0x79,
        0x3B,
        0x5F,
        0x27,
        0x24,
        0x2E,
        0x1A,
        0x4C,
        0xA9,
        0x52,
        0x27,
        0x5F,
        0x4C,
        0xF2,
        0x0D,
        0xD4,
        0x01,
        0xFB,
        0x54,
        0x7C,
        0xF5,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x9846A7A7759E76E92B39105DECF8FAB1BD18FB67A44300583413BDE34E8EB6AB
    unsigned char std_signature_s_sha384[] = {
        0x98,
        0x46,
        0xA7,
        0xA7,
        0x75,
        0x9E,
        0x76,
        0xE9,
        0x2B,
        0x39,
        0x10,
        0x5D,
        0xEC,
        0xF8,
        0xFA,
        0xB1,
        0xBD,
        0x18,
        0xFB,
        0x67,
        0xA4,
        0x43,
        0x00,
        0x58,
        0x34,
        0x13,
        0xBD,
        0xE3,
        0x4E,
        0x8E,
        0xB6,
        0xAB,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0xF679EFB89D01F6250ECABA041BF9FEE7284FD955FF3D2A62AF395F76F11DFA77
    unsigned char std_signature_s_sha512[] = {
        0xF6,
        0x79,
        0xEF,
        0xB8,
        0x9D,
        0x01,
        0xF6,
        0x25,
        0x0E,
        0xCA,
        0xBA,
        0x04,
        0x1B,
        0xF9,
        0xFE,
        0xE7,
        0x28,
        0x4F,
        0xD9,
        0x55,
        0xFF,
        0x3D,
        0x2A,
        0x62,
        0xAF,
        0x39,
        0x5F,
        0x76,
        0xF1,
        0x1D,
        0xFA,
        0x77,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0xE102ED6183A2A2F3322FE5D5421C226000CFA6B90AF7A1451C5820D6DC446DD7
    unsigned char std_signature_s_544[] = {
        0xE1,
        0x02,
        0xED,
        0x61,
        0x83,
        0xA2,
        0xA2,
        0xF3,
        0x32,
        0x2F,
        0xE5,
        0xD5,
        0x42,
        0x1C,
        0x22,
        0x60,
        0x00,
        0xCF,
        0xA6,
        0xB9,
        0x0A,
        0xF7,
        0xA1,
        0x45,
        0x1C,
        0x58,
        0x20,
        0xD6,
        0xDC,
        0x44,
        0x6D,
        0xD7,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp256r1;
    char         *curve_name = "secp256r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
unsigned int ecdsa_std_test_secp384r1(void)
{
    //k:
    //0xC8BC1020C20C7F67ED6195B345A703F50FE50202AA2FF7C0E776FE6C528CB3391467BCF5CD3317E5A947B3297074F038
    unsigned char rand_k[48] = {
        0xC8,
        0xBC,
        0x10,
        0x20,
        0xC2,
        0x0C,
        0x7F,
        0x67,
        0xED,
        0x61,
        0x95,
        0xB3,
        0x45,
        0xA7,
        0x03,
        0xF5,
        0x0F,
        0xE5,
        0x02,
        0x02,
        0xAA,
        0x2F,
        0xF7,
        0xC0,
        0xE7,
        0x76,
        0xFE,
        0x6C,
        0x52,
        0x8C,
        0xB3,
        0x39,
        0x14,
        0x67,
        0xBC,
        0xF5,
        0xCD,
        0x33,
        0x17,
        0xE5,
        0xA9,
        0x47,
        0xB3,
        0x29,
        0x70,
        0x74,
        0xF0,
        0x38,
    };

    //private key:
    //0x8B0DCC7CF82C4954F80E34D5D9397DFA5D3EA54CBE64754332829F60DBD18529F935D21C3D74DDEDF6F8832711C9CC03
    unsigned char priKey[48] = {
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

    //public key:
    //x coordinate:
    //0x4AEC1F9098FFB62F1B1574A5D75F701CC346F1C18130B0DE524B0D55A897CB37D280D2C4D85A85E4C65CB931E38278C8
    //y coordinate:
    //0x87A014038CA3F26096DA30457B39BC35290DF30B47D9B84C2EEDB19934BB55A8A28E4CD6906871DADCC573F6E2C5C6A0
    unsigned char pubKey[96] = {
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


    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x8415EC98D16E6D024ED85064BFCB20DE7221663C1916BDA8730DAAAB27A9F93414064B58E7C32680B3124515B435E37D
    unsigned char std_signature_r[] = {
        0x84,
        0x15,
        0xEC,
        0x98,
        0xD1,
        0x6E,
        0x6D,
        0x02,
        0x4E,
        0xD8,
        0x50,
        0x64,
        0xBF,
        0xCB,
        0x20,
        0xDE,
        0x72,
        0x21,
        0x66,
        0x3C,
        0x19,
        0x16,
        0xBD,
        0xA8,
        0x73,
        0x0D,
        0xAA,
        0xAB,
        0x27,
        0xA9,
        0xF9,
        0x34,
        0x14,
        0x06,
        0x4B,
        0x58,
        0xE7,
        0xC3,
        0x26,
        0x80,
        0xB3,
        0x12,
        0x45,
        0x15,
        0xB4,
        0x35,
        0xE3,
        0x7D,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xCED59F2F06375C2751BC8A5433BA49FABCCC9C25854162469F4B35F23B7FE1C7B3ED9B0FBCAEC2B8A68E1A66C8895AA7
    unsigned char std_signature_s_zero[] = {
        0xCE,
        0xD5,
        0x9F,
        0x2F,
        0x06,
        0x37,
        0x5C,
        0x27,
        0x51,
        0xBC,
        0x8A,
        0x54,
        0x33,
        0xBA,
        0x49,
        0xFA,
        0xBC,
        0xCC,
        0x9C,
        0x25,
        0x85,
        0x41,
        0x62,
        0x46,
        0x9F,
        0x4B,
        0x35,
        0xF2,
        0x3B,
        0x7F,
        0xE1,
        0xC7,
        0xB3,
        0xED,
        0x9B,
        0x0F,
        0xBC,
        0xAE,
        0xC2,
        0xB8,
        0xA6,
        0x8E,
        0x1A,
        0x66,
        0xC8,
        0x89,
        0x5A,
        0xA7,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x308464B0FD64DFDC1F440BE0BBFEB830C9BDCE00A32ECF6D0531FD817F2AEB2471B8DAA9C3EAD4BFA34BF7AA76D00359
    unsigned char std_signature_s_1[] = {
        0x30,
        0x84,
        0x64,
        0xB0,
        0xFD,
        0x64,
        0xDF,
        0xDC,
        0x1F,
        0x44,
        0x0B,
        0xE0,
        0xBB,
        0xFE,
        0xB8,
        0x30,
        0xC9,
        0xBD,
        0xCE,
        0x00,
        0xA3,
        0x2E,
        0xCF,
        0x6D,
        0x05,
        0x31,
        0xFD,
        0x81,
        0x7F,
        0x2A,
        0xEB,
        0x24,
        0x71,
        0xB8,
        0xDA,
        0xA9,
        0xC3,
        0xEA,
        0xD4,
        0xBF,
        0xA3,
        0x4B,
        0xF7,
        0xAA,
        0x76,
        0xD0,
        0x03,
        0x59,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0xC52F0ADC9AB3F426BF5CD35336A2942E634C60AFB0D12DFEFA0024F65C6EFD066C9DC5A5018F37399FDFF6EE30840AF2
    unsigned char std_signature_s_FF[] = {
        0xC5,
        0x2F,
        0x0A,
        0xDC,
        0x9A,
        0xB3,
        0xF4,
        0x26,
        0xBF,
        0x5C,
        0xD3,
        0x53,
        0x36,
        0xA2,
        0x94,
        0x2E,
        0x63,
        0x4C,
        0x60,
        0xAF,
        0xB0,
        0xD1,
        0x2D,
        0xFE,
        0xFA,
        0x00,
        0x24,
        0xF6,
        0x5C,
        0x6E,
        0xFD,
        0x06,
        0x6C,
        0x9D,
        0xC5,
        0xA5,
        0x01,
        0x8F,
        0x37,
        0x39,
        0x9F,
        0xDF,
        0xF6,
        0xEE,
        0x30,
        0x84,
        0x0A,
        0xF2,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x90CC3793270DBFD18500274F8FFB838F57E11561CF12946DDFD43AD0ADC7BDB317F3A06E76AA521B10E91F5EAA348911
    unsigned char std_signature_s_md5[] = {
        0x90,
        0xCC,
        0x37,
        0x93,
        0x27,
        0x0D,
        0xBF,
        0xD1,
        0x85,
        0x00,
        0x27,
        0x4F,
        0x8F,
        0xFB,
        0x83,
        0x8F,
        0x57,
        0xE1,
        0x15,
        0x61,
        0xCF,
        0x12,
        0x94,
        0x6D,
        0xDF,
        0xD4,
        0x3A,
        0xD0,
        0xAD,
        0xC7,
        0xBD,
        0xB3,
        0x17,
        0xF3,
        0xA0,
        0x6E,
        0x76,
        0xAA,
        0x52,
        0x1B,
        0x10,
        0xE9,
        0x1F,
        0x5E,
        0xAA,
        0x34,
        0x89,
        0x11,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x63B5CAF71B225C7322634AF94FED816B341F218FAAA6A9B14F873B2C44B9346C849F6F5DF2FA6FEBC28DA13D1BF04B6F
    unsigned char std_signature_s_sha1[] = {
        0x63,
        0xB5,
        0xCA,
        0xF7,
        0x1B,
        0x22,
        0x5C,
        0x73,
        0x22,
        0x63,
        0x4A,
        0xF9,
        0x4F,
        0xED,
        0x81,
        0x6B,
        0x34,
        0x1F,
        0x21,
        0x8F,
        0xAA,
        0xA6,
        0xA9,
        0xB1,
        0x4F,
        0x87,
        0x3B,
        0x2C,
        0x44,
        0xB9,
        0x34,
        0x6C,
        0x84,
        0x9F,
        0x6F,
        0x5D,
        0xF2,
        0xFA,
        0x6F,
        0xEB,
        0xC2,
        0x8D,
        0xA1,
        0x3D,
        0x1B,
        0xF0,
        0x4B,
        0x6F,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0xD44E3431FEA61101CB69BD5D06C3FFB911658251BF751956283AA533280A2BABCCD7FC3DB83806665E9859EF975CCC36
    unsigned char std_signature_s_192[] = {
        0xD4,
        0x4E,
        0x34,
        0x31,
        0xFE,
        0xA6,
        0x11,
        0x01,
        0xCB,
        0x69,
        0xBD,
        0x5D,
        0x06,
        0xC3,
        0xFF,
        0xB9,
        0x11,
        0x65,
        0x82,
        0x51,
        0xBF,
        0x75,
        0x19,
        0x56,
        0x28,
        0x3A,
        0xA5,
        0x33,
        0x28,
        0x0A,
        0x2B,
        0xAB,
        0xCC,
        0xD7,
        0xFC,
        0x3D,
        0xB8,
        0x38,
        0x06,
        0x66,
        0x5E,
        0x98,
        0x59,
        0xEF,
        0x97,
        0x5C,
        0xCC,
        0x36,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x8C572F66507F4FC63381096ABAACB5714909E5431804CF4BECB4C6F050509C8FC3821B8710500D534C47F0349B290F54
    unsigned char std_signature_s_sha224[] = {
        0x8C,
        0x57,
        0x2F,
        0x66,
        0x50,
        0x7F,
        0x4F,
        0xC6,
        0x33,
        0x81,
        0x09,
        0x6A,
        0xBA,
        0xAC,
        0xB5,
        0x71,
        0x49,
        0x09,
        0xE5,
        0x43,
        0x18,
        0x04,
        0xCF,
        0x4B,
        0xEC,
        0xB4,
        0xC6,
        0xF0,
        0x50,
        0x50,
        0x9C,
        0x8F,
        0xC3,
        0x82,
        0x1B,
        0x87,
        0x10,
        0x50,
        0x0D,
        0x53,
        0x4C,
        0x47,
        0xF0,
        0x34,
        0x9B,
        0x29,
        0x0F,
        0x54,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x7D463313C4F8DBEC544D74D0B102CA69B8B97BB5B098CD86CE9149F9FFD3F2FEC3365B06042180795BED180DC190E3F3
    unsigned char std_signature_s_sha256[] = {
        0x7D,
        0x46,
        0x33,
        0x13,
        0xC4,
        0xF8,
        0xDB,
        0xEC,
        0x54,
        0x4D,
        0x74,
        0xD0,
        0xB1,
        0x02,
        0xCA,
        0x69,
        0xB8,
        0xB9,
        0x7B,
        0xB5,
        0xB0,
        0x98,
        0xCD,
        0x86,
        0xCE,
        0x91,
        0x49,
        0xF9,
        0xFF,
        0xD3,
        0xF2,
        0xFE,
        0xC3,
        0x36,
        0x5B,
        0x06,
        0x04,
        0x21,
        0x80,
        0x79,
        0x5B,
        0xED,
        0x18,
        0x0D,
        0xC1,
        0x90,
        0xE3,
        0xF3,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x61BD72B445D8C634773FF407AF609E20B8A8BD714E9E39DD825AEE380B81C6DD70F82D8F28459FEA82314D6D19980C15
    unsigned char std_signature_s_sha384[] = {
        0x61,
        0xBD,
        0x72,
        0xB4,
        0x45,
        0xD8,
        0xC6,
        0x34,
        0x77,
        0x3F,
        0xF4,
        0x07,
        0xAF,
        0x60,
        0x9E,
        0x20,
        0xB8,
        0xA8,
        0xBD,
        0x71,
        0x4E,
        0x9E,
        0x39,
        0xDD,
        0x82,
        0x5A,
        0xEE,
        0x38,
        0x0B,
        0x81,
        0xC6,
        0xDD,
        0x70,
        0xF8,
        0x2D,
        0x8F,
        0x28,
        0x45,
        0x9F,
        0xEA,
        0x82,
        0x31,
        0x4D,
        0x6D,
        0x19,
        0x98,
        0x0C,
        0x15,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0xD94E703BFB54C05EE45198D28A7B277487AE5D27A55D186F137FD7638CB9ADC76397BED7D7B3BD4A17EF6169CEEE44E5
    unsigned char std_signature_s_sha512[] = {
        0xD9,
        0x4E,
        0x70,
        0x3B,
        0xFB,
        0x54,
        0xC0,
        0x5E,
        0xE4,
        0x51,
        0x98,
        0xD2,
        0x8A,
        0x7B,
        0x27,
        0x74,
        0x87,
        0xAE,
        0x5D,
        0x27,
        0xA5,
        0x5D,
        0x18,
        0x6F,
        0x13,
        0x7F,
        0xD7,
        0x63,
        0x8C,
        0xB9,
        0xAD,
        0xC7,
        0x63,
        0x97,
        0xBE,
        0xD7,
        0xD7,
        0xB3,
        0xBD,
        0x4A,
        0x17,
        0xEF,
        0x61,
        0x69,
        0xCE,
        0xEE,
        0x44,
        0xE5,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x95455A585946A3E824E5ED3493425384BC873312DC837D4CBC56A9F18291C715F53E59B553B8E3A18C2E7086C178844E
    unsigned char std_signature_s_544[] = {
        0x95,
        0x45,
        0x5A,
        0x58,
        0x59,
        0x46,
        0xA3,
        0xE8,
        0x24,
        0xE5,
        0xED,
        0x34,
        0x93,
        0x42,
        0x53,
        0x84,
        0xBC,
        0x87,
        0x33,
        0x12,
        0xDC,
        0x83,
        0x7D,
        0x4C,
        0xBC,
        0x56,
        0xA9,
        0xF1,
        0x82,
        0x91,
        0xC7,
        0x15,
        0xF5,
        0x3E,
        0x59,
        0xB5,
        0x53,
        0xB8,
        0xE3,
        0xA1,
        0x8C,
        0x2E,
        0x70,
        0x86,
        0xC1,
        0x78,
        0x84,
        0x4E,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp384r1;
    char         *curve_name = "secp384r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
unsigned int ecdsa_std_test_brainpoolp512r1(void)
{
    //k:
    //0x8A304A63EBC8085424E8975A86DC516E23CA85A66FADCF53A94855E812E0614E8F6045D4DE6EDC21D14580491A93164357F7CB389D8AA32CACDD62C7C4D83E37
    unsigned char rand_k[64] = {
        0x8A,
        0x30,
        0x4A,
        0x63,
        0xEB,
        0xC8,
        0x08,
        0x54,
        0x24,
        0xE8,
        0x97,
        0x5A,
        0x86,
        0xDC,
        0x51,
        0x6E,
        0x23,
        0xCA,
        0x85,
        0xA6,
        0x6F,
        0xAD,
        0xCF,
        0x53,
        0xA9,
        0x48,
        0x55,
        0xE8,
        0x12,
        0xE0,
        0x61,
        0x4E,
        0x8F,
        0x60,
        0x45,
        0xD4,
        0xDE,
        0x6E,
        0xDC,
        0x21,
        0xD1,
        0x45,
        0x80,
        0x49,
        0x1A,
        0x93,
        0x16,
        0x43,
        0x57,
        0xF7,
        0xCB,
        0x38,
        0x9D,
        0x8A,
        0xA3,
        0x2C,
        0xAC,
        0xDD,
        0x62,
        0xC7,
        0xC4,
        0xD8,
        0x3E,
        0x37,
    };

    //private key:
    //0x3A9263563CD6335840B84D4034A885C33AB92612B9FE1E5AE22954F6355F4D8D35783035A1E10BA67914306A8C06B193C71D5C3C4FD2868C32FE4CC951094088
    unsigned char priKey[64] = {
        0x3A,
        0x92,
        0x63,
        0x56,
        0x3C,
        0xD6,
        0x33,
        0x58,
        0x40,
        0xB8,
        0x4D,
        0x40,
        0x34,
        0xA8,
        0x85,
        0xC3,
        0x3A,
        0xB9,
        0x26,
        0x12,
        0xB9,
        0xFE,
        0x1E,
        0x5A,
        0xE2,
        0x29,
        0x54,
        0xF6,
        0x35,
        0x5F,
        0x4D,
        0x8D,
        0x35,
        0x78,
        0x30,
        0x35,
        0xA1,
        0xE1,
        0x0B,
        0xA6,
        0x79,
        0x14,
        0x30,
        0x6A,
        0x8C,
        0x06,
        0xB1,
        0x93,
        0xC7,
        0x1D,
        0x5C,
        0x3C,
        0x4F,
        0xD2,
        0x86,
        0x8C,
        0x32,
        0xFE,
        0x4C,
        0xC9,
        0x51,
        0x09,
        0x40,
        0x88,
    };

    //public key:
    //x coordinate:
    //0x38ABF3B16BB7F9253F4BD4EA07353300E70531BD81D00D09FF21703FDE2ECFCF8ED4123D5B5895695C9F819A99A714F338C89DA43E0154900BE6FDC0091234A7
    //y coordinate:
    //0x1170D5F8926EF37B700CC27731BF3662351FE2DF4244225E98F7CC20AD29609CE6C8D11E3A192BABD1F7008D287C45AACCEEAD937764007EF0737965DDEDE5D0
    unsigned char pubKey[128] = {
        0x38,
        0xAB,
        0xF3,
        0xB1,
        0x6B,
        0xB7,
        0xF9,
        0x25,
        0x3F,
        0x4B,
        0xD4,
        0xEA,
        0x07,
        0x35,
        0x33,
        0x00,
        0xE7,
        0x05,
        0x31,
        0xBD,
        0x81,
        0xD0,
        0x0D,
        0x09,
        0xFF,
        0x21,
        0x70,
        0x3F,
        0xDE,
        0x2E,
        0xCF,
        0xCF,
        0x8E,
        0xD4,
        0x12,
        0x3D,
        0x5B,
        0x58,
        0x95,
        0x69,
        0x5C,
        0x9F,
        0x81,
        0x9A,
        0x99,
        0xA7,
        0x14,
        0xF3,
        0x38,
        0xC8,
        0x9D,
        0xA4,
        0x3E,
        0x01,
        0x54,
        0x90,
        0x0B,
        0xE6,
        0xFD,
        0xC0,
        0x09,
        0x12,
        0x34,
        0xA7,
        0x11,
        0x70,
        0xD5,
        0xF8,
        0x92,
        0x6E,
        0xF3,
        0x7B,
        0x70,
        0x0C,
        0xC2,
        0x77,
        0x31,
        0xBF,
        0x36,
        0x62,
        0x35,
        0x1F,
        0xE2,
        0xDF,
        0x42,
        0x44,
        0x22,
        0x5E,
        0x98,
        0xF7,
        0xCC,
        0x20,
        0xAD,
        0x29,
        0x60,
        0x9C,
        0xE6,
        0xC8,
        0xD1,
        0x1E,
        0x3A,
        0x19,
        0x2B,
        0xAB,
        0xD1,
        0xF7,
        0x00,
        0x8D,
        0x28,
        0x7C,
        0x45,
        0xAA,
        0xCC,
        0xEE,
        0xAD,
        0x93,
        0x77,
        0x64,
        0x00,
        0x7E,
        0xF0,
        0x73,
        0x79,
        0x65,
        0xDD,
        0xED,
        0xE5,
        0xD0,
    };


    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x87E2186832BCCA9EF7F2F24DB48FA32A76F10EAF88E3C98D1B829B77FF6AA385F16C0A9558E6CAD87D0E4B5B7C7F588EED42A985A888A0A78131C6B0449BCC5D
    unsigned char std_signature_r[128] = {
        0x87,
        0xE2,
        0x18,
        0x68,
        0x32,
        0xBC,
        0xCA,
        0x9E,
        0xF7,
        0xF2,
        0xF2,
        0x4D,
        0xB4,
        0x8F,
        0xA3,
        0x2A,
        0x76,
        0xF1,
        0x0E,
        0xAF,
        0x88,
        0xE3,
        0xC9,
        0x8D,
        0x1B,
        0x82,
        0x9B,
        0x77,
        0xFF,
        0x6A,
        0xA3,
        0x85,
        0xF1,
        0x6C,
        0x0A,
        0x95,
        0x58,
        0xE6,
        0xCA,
        0xD8,
        0x7D,
        0x0E,
        0x4B,
        0x5B,
        0x7C,
        0x7F,
        0x58,
        0x8E,
        0xED,
        0x42,
        0xA9,
        0x85,
        0xA8,
        0x88,
        0xA0,
        0xA7,
        0x81,
        0x31,
        0xC6,
        0xB0,
        0x44,
        0x9B,
        0xCC,
        0x5D,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xA69A28A44C2962F16C071BCB544B9BE3C5C622C4AC8920B3400451889487DD839463108C1AE21AE31C2F4B52E1FF193E4286FF4F36FAA348930DD7BE2EBB6620
    unsigned char std_signature_s_zero[] = {
        0xA6,
        0x9A,
        0x28,
        0xA4,
        0x4C,
        0x29,
        0x62,
        0xF1,
        0x6C,
        0x07,
        0x1B,
        0xCB,
        0x54,
        0x4B,
        0x9B,
        0xE3,
        0xC5,
        0xC6,
        0x22,
        0xC4,
        0xAC,
        0x89,
        0x20,
        0xB3,
        0x40,
        0x04,
        0x51,
        0x88,
        0x94,
        0x87,
        0xDD,
        0x83,
        0x94,
        0x63,
        0x10,
        0x8C,
        0x1A,
        0xE2,
        0x1A,
        0xE3,
        0x1C,
        0x2F,
        0x4B,
        0x52,
        0xE1,
        0xFF,
        0x19,
        0x3E,
        0x42,
        0x86,
        0xFF,
        0x4F,
        0x36,
        0xFA,
        0xA3,
        0x48,
        0x93,
        0x0D,
        0xD7,
        0xBE,
        0x2E,
        0xBB,
        0x66,
        0x20,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x2778C4CA83AF5D950024B9C853B652490C3E320A6855F5909030515360921C4485E5D81B63178CB9AC3191BBF7A314E70584698BB9290D23FC40E3F64E7ECFCE
    unsigned char std_signature_s_1[] = {
        0x27,
        0x78,
        0xC4,
        0xCA,
        0x83,
        0xAF,
        0x5D,
        0x95,
        0x00,
        0x24,
        0xB9,
        0xC8,
        0x53,
        0xB6,
        0x52,
        0x49,
        0x0C,
        0x3E,
        0x32,
        0x0A,
        0x68,
        0x55,
        0xF5,
        0x90,
        0x90,
        0x30,
        0x51,
        0x53,
        0x60,
        0x92,
        0x1C,
        0x44,
        0x85,
        0xE5,
        0xD8,
        0x1B,
        0x63,
        0x17,
        0x8C,
        0xB9,
        0xAC,
        0x31,
        0x91,
        0xBB,
        0xF7,
        0xA3,
        0x14,
        0xE7,
        0x05,
        0x84,
        0x69,
        0x8B,
        0xB9,
        0x29,
        0x0D,
        0x23,
        0xFC,
        0x40,
        0xE3,
        0xF6,
        0x4E,
        0x7E,
        0xCF,
        0xCE,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x45A5A8B9A4B600A4C7817E4AA56AA5AA1B9070F0AAAC1BA16CCBE4E43EF8F28928DD1F57AACC4199E2FBA1318B9FDDD63813EA9EA4D33806CCEBA1F4D6BF49C9
    unsigned char std_signature_s_FF[] = {
        0x45,
        0xA5,
        0xA8,
        0xB9,
        0xA4,
        0xB6,
        0x00,
        0xA4,
        0xC7,
        0x81,
        0x7E,
        0x4A,
        0xA5,
        0x6A,
        0xA5,
        0xAA,
        0x1B,
        0x90,
        0x70,
        0xF0,
        0xAA,
        0xAC,
        0x1B,
        0xA1,
        0x6C,
        0xCB,
        0xE4,
        0xE4,
        0x3E,
        0xF8,
        0xF2,
        0x89,
        0x28,
        0xDD,
        0x1F,
        0x57,
        0xAA,
        0xCC,
        0x41,
        0x99,
        0xE2,
        0xFB,
        0xA1,
        0x31,
        0x8B,
        0x9F,
        0xDD,
        0xD6,
        0x38,
        0x13,
        0xEA,
        0x9E,
        0xA4,
        0xD3,
        0x38,
        0x06,
        0xCC,
        0xEB,
        0xA1,
        0xF4,
        0xD6,
        0xBF,
        0x49,
        0xC9,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x21EA9B79E56CE888DBE1A9611DCF63063070EFC4AAF9F2A53AB3EB3F1F3CAB9062D694D84AEEFEF7AED231C7935150879B3250316F024CB01B1BBF74EA902931
    unsigned char std_signature_s_md5[] = {
        0x21,
        0xEA,
        0x9B,
        0x79,
        0xE5,
        0x6C,
        0xE8,
        0x88,
        0xDB,
        0xE1,
        0xA9,
        0x61,
        0x1D,
        0xCF,
        0x63,
        0x06,
        0x30,
        0x70,
        0xEF,
        0xC4,
        0xAA,
        0xF9,
        0xF2,
        0xA5,
        0x3A,
        0xB3,
        0xEB,
        0x3F,
        0x1F,
        0x3C,
        0xAB,
        0x90,
        0x62,
        0xD6,
        0x94,
        0xD8,
        0x4A,
        0xEE,
        0xFE,
        0xF7,
        0xAE,
        0xD2,
        0x31,
        0xC7,
        0x93,
        0x51,
        0x50,
        0x87,
        0x9B,
        0x32,
        0x50,
        0x31,
        0x6F,
        0x02,
        0x4C,
        0xB0,
        0x1B,
        0x1B,
        0xBF,
        0x74,
        0xEA,
        0x90,
        0x29,
        0x31,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0xAAAA2093B1C89D739FCCD2AAEEF06A1B6BB6AEB859337A13003A829F85B1A24FE407E0A238617CCD9F3BCD6740CEB4C35048F2D72D163A1D8C7C1426B93BE3C7
    unsigned char std_signature_s_sha1[] = {
        0xAA,
        0xAA,
        0x20,
        0x93,
        0xB1,
        0xC8,
        0x9D,
        0x73,
        0x9F,
        0xCC,
        0xD2,
        0xAA,
        0xEE,
        0xF0,
        0x6A,
        0x1B,
        0x6B,
        0xB6,
        0xAE,
        0xB8,
        0x59,
        0x33,
        0x7A,
        0x13,
        0x00,
        0x3A,
        0x82,
        0x9F,
        0x85,
        0xB1,
        0xA2,
        0x4F,
        0xE4,
        0x07,
        0xE0,
        0xA2,
        0x38,
        0x61,
        0x7C,
        0xCD,
        0x9F,
        0x3B,
        0xCD,
        0x67,
        0x40,
        0xCE,
        0xB4,
        0xC3,
        0x50,
        0x48,
        0xF2,
        0xD7,
        0x2D,
        0x16,
        0x3A,
        0x1D,
        0x8C,
        0x7C,
        0x14,
        0x26,
        0xB9,
        0x3B,
        0xE3,
        0xC7,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x8BD6A0F6BC2DB3D32B3B6D0920577951E173D035E451282C2D5F4B969E75E7B0C6F41864E1CE495F69F0782525F6A8921F8156746860EC7D2A62AB2C6FD23AF7
    unsigned char std_signature_s_192[] = {
        0x8B,
        0xD6,
        0xA0,
        0xF6,
        0xBC,
        0x2D,
        0xB3,
        0xD3,
        0x2B,
        0x3B,
        0x6D,
        0x09,
        0x20,
        0x57,
        0x79,
        0x51,
        0xE1,
        0x73,
        0xD0,
        0x35,
        0xE4,
        0x51,
        0x28,
        0x2C,
        0x2D,
        0x5F,
        0x4B,
        0x96,
        0x9E,
        0x75,
        0xE7,
        0xB0,
        0xC6,
        0xF4,
        0x18,
        0x64,
        0xE1,
        0xCE,
        0x49,
        0x5F,
        0x69,
        0xF0,
        0x78,
        0x25,
        0x25,
        0xF6,
        0xA8,
        0x92,
        0x1F,
        0x81,
        0x56,
        0x74,
        0x68,
        0x60,
        0xEC,
        0x7D,
        0x2A,
        0x62,
        0xAB,
        0x2C,
        0x6F,
        0xD2,
        0x3A,
        0xF7,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x8D49353D8E4C75A8EFDD35F808851D7F67B84B7800F25FBD50701E916656CFC1C49DAE5C4C684DC9286F3A1D0EB0F4DB930082CE83C6A2CF7E6218D49A094C77
    unsigned char std_signature_s_sha224[] = {
        0x8D,
        0x49,
        0x35,
        0x3D,
        0x8E,
        0x4C,
        0x75,
        0xA8,
        0xEF,
        0xDD,
        0x35,
        0xF8,
        0x08,
        0x85,
        0x1D,
        0x7F,
        0x67,
        0xB8,
        0x4B,
        0x78,
        0x00,
        0xF2,
        0x5F,
        0xBD,
        0x50,
        0x70,
        0x1E,
        0x91,
        0x66,
        0x56,
        0xCF,
        0xC1,
        0xC4,
        0x9D,
        0xAE,
        0x5C,
        0x4C,
        0x68,
        0x4D,
        0xC9,
        0x28,
        0x6F,
        0x3A,
        0x1D,
        0x0E,
        0xB0,
        0xF4,
        0xDB,
        0x93,
        0x00,
        0x82,
        0xCE,
        0x83,
        0xC6,
        0xA2,
        0xCF,
        0x7E,
        0x62,
        0x18,
        0xD4,
        0x9A,
        0x09,
        0x4C,
        0x77,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x343658A849523827E28128E659AB2123F3DBE32376D68EDECBC188EBA41B6CF5D6FFF6D134D6B28CF40A7F562E36341ABAB8E781AA006F6BD75A494DFDC44B78
    unsigned char std_signature_s_sha256[] = {
        0x34,
        0x36,
        0x58,
        0xA8,
        0x49,
        0x52,
        0x38,
        0x27,
        0xE2,
        0x81,
        0x28,
        0xE6,
        0x59,
        0xAB,
        0x21,
        0x23,
        0xF3,
        0xDB,
        0xE3,
        0x23,
        0x76,
        0xD6,
        0x8E,
        0xDE,
        0xCB,
        0xC1,
        0x88,
        0xEB,
        0xA4,
        0x1B,
        0x6C,
        0xF5,
        0xD6,
        0xFF,
        0xF6,
        0xD1,
        0x34,
        0xD6,
        0xB2,
        0x8C,
        0xF4,
        0x0A,
        0x7F,
        0x56,
        0x2E,
        0x36,
        0x34,
        0x1A,
        0xBA,
        0xB8,
        0xE7,
        0x81,
        0xAA,
        0x00,
        0x6F,
        0x6B,
        0xD7,
        0x5A,
        0x49,
        0x4D,
        0xFD,
        0xC4,
        0x4B,
        0x78,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x994887253A2D148BB325A2EF2091C15814AE9651DB8DAA0E894485514E714ABAF89948EBCE73D59529FCFBBAE1E7762696A61D635B7211770CEA64576ED3B1D0
    unsigned char std_signature_s_sha384[] = {
        0x99,
        0x48,
        0x87,
        0x25,
        0x3A,
        0x2D,
        0x14,
        0x8B,
        0xB3,
        0x25,
        0xA2,
        0xEF,
        0x20,
        0x91,
        0xC1,
        0x58,
        0x14,
        0xAE,
        0x96,
        0x51,
        0xDB,
        0x8D,
        0xAA,
        0x0E,
        0x89,
        0x44,
        0x85,
        0x51,
        0x4E,
        0x71,
        0x4A,
        0xBA,
        0xF8,
        0x99,
        0x48,
        0xEB,
        0xCE,
        0x73,
        0xD5,
        0x95,
        0x29,
        0xFC,
        0xFB,
        0xBA,
        0xE1,
        0xE7,
        0x76,
        0x26,
        0x96,
        0xA6,
        0x1D,
        0x63,
        0x5B,
        0x72,
        0x11,
        0x77,
        0x0C,
        0xEA,
        0x64,
        0x57,
        0x6E,
        0xD3,
        0xB1,
        0xD0,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x9B5BE7564DE16886E461B0EAE2AAA2ABDB1B02BA301F8B69092120FD32B1DCDB8BB69908B35E2457D4E1CC98B7901CABB56F7B0000D23996267EB6CBDF2FCE49
    unsigned char std_signature_s_sha512[] = {
        0x9B,
        0x5B,
        0xE7,
        0x56,
        0x4D,
        0xE1,
        0x68,
        0x86,
        0xE4,
        0x61,
        0xB0,
        0xEA,
        0xE2,
        0xAA,
        0xA2,
        0xAB,
        0xDB,
        0x1B,
        0x02,
        0xBA,
        0x30,
        0x1F,
        0x8B,
        0x69,
        0x09,
        0x21,
        0x20,
        0xFD,
        0x32,
        0xB1,
        0xDC,
        0xDB,
        0x8B,
        0xB6,
        0x99,
        0x08,
        0xB3,
        0x5E,
        0x24,
        0x57,
        0xD4,
        0xE1,
        0xCC,
        0x98,
        0xB7,
        0x90,
        0x1C,
        0xAB,
        0xB5,
        0x6F,
        0x7B,
        0x00,
        0x00,
        0xD2,
        0x39,
        0x96,
        0x26,
        0x7E,
        0xB6,
        0xCB,
        0xDF,
        0x2F,
        0xCE,
        0x49,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x84E705AC3B65D1C734DC3FA4BE1112D1153E563BF9D83645DE2B3BF2210494261C27DFE2118B755974141504FABFAE4B6FE4486D3E097181050533C7BF08EF18
    unsigned char std_signature_s_544[] = {
        0x84,
        0xE7,
        0x05,
        0xAC,
        0x3B,
        0x65,
        0xD1,
        0xC7,
        0x34,
        0xDC,
        0x3F,
        0xA4,
        0xBE,
        0x11,
        0x12,
        0xD1,
        0x15,
        0x3E,
        0x56,
        0x3B,
        0xF9,
        0xD8,
        0x36,
        0x45,
        0xDE,
        0x2B,
        0x3B,
        0xF2,
        0x21,
        0x04,
        0x94,
        0x26,
        0x1C,
        0x27,
        0xDF,
        0xE2,
        0x11,
        0x8B,
        0x75,
        0x59,
        0x74,
        0x14,
        0x15,
        0x04,
        0xFA,
        0xBF,
        0xAE,
        0x4B,
        0x6F,
        0xE4,
        0x48,
        0x6D,
        0x3E,
        0x09,
        0x71,
        0x81,
        0x05,
        0x05,
        0x33,
        0xC7,
        0xBF,
        0x08,
        0xEF,
        0x18,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)brainpoolp512r1;
    char         *curve_name = "brainpoolp512r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
unsigned int ecdsa_std_test_secp521r1(void)
{
    //k:
    //0x010BEA09D334E3F4CAA2C543595A2BE763A3C3CA11C7F87E8F24F16F371F5B111834361622C6D1F571D6910E1AFDBBF84C96510484ED4F2427FA7FC2B06C9CB12498
    unsigned char rand_k[66] = {
        0x01,
        0x0B,
        0xEA,
        0x09,
        0xD3,
        0x34,
        0xE3,
        0xF4,
        0xCA,
        0xA2,
        0xC5,
        0x43,
        0x59,
        0x5A,
        0x2B,
        0xE7,
        0x63,
        0xA3,
        0xC3,
        0xCA,
        0x11,
        0xC7,
        0xF8,
        0x7E,
        0x8F,
        0x24,
        0xF1,
        0x6F,
        0x37,
        0x1F,
        0x5B,
        0x11,
        0x18,
        0x34,
        0x36,
        0x16,
        0x22,
        0xC6,
        0xD1,
        0xF5,
        0x71,
        0xD6,
        0x91,
        0x0E,
        0x1A,
        0xFD,
        0xBB,
        0xF8,
        0x4C,
        0x96,
        0x51,
        0x04,
        0x84,
        0xED,
        0x4F,
        0x24,
        0x27,
        0xFA,
        0x7F,
        0xC2,
        0xB0,
        0x6C,
        0x9C,
        0xB1,
        0x24,
        0x98,
    };

    //private key:
    //0x01D72198A83613DD1250E3B21CFA9B7A749FE35D4C297C01EB865210E3932756ED39B5A1131E4795E5E46A9038F9075BB7CA206F41209ECBEF5881A710BE9C4560F8
    unsigned char priKey[66] = {
        0x01,
        0xD7,
        0x21,
        0x98,
        0xA8,
        0x36,
        0x13,
        0xDD,
        0x12,
        0x50,
        0xE3,
        0xB2,
        0x1C,
        0xFA,
        0x9B,
        0x7A,
        0x74,
        0x9F,
        0xE3,
        0x5D,
        0x4C,
        0x29,
        0x7C,
        0x01,
        0xEB,
        0x86,
        0x52,
        0x10,
        0xE3,
        0x93,
        0x27,
        0x56,
        0xED,
        0x39,
        0xB5,
        0xA1,
        0x13,
        0x1E,
        0x47,
        0x95,
        0xE5,
        0xE4,
        0x6A,
        0x90,
        0x38,
        0xF9,
        0x07,
        0x5B,
        0xB7,
        0xCA,
        0x20,
        0x6F,
        0x41,
        0x20,
        0x9E,
        0xCB,
        0xEF,
        0x58,
        0x81,
        0xA7,
        0x10,
        0xBE,
        0x9C,
        0x45,
        0x60,
        0xF8,
    };

    //public key:
    //x coordinate:
    //0x000BBCE926E71B3DDCBB54C343BA3A7F65BB1F11547EBFA3ED092ED15365FF56CE4DA2EC606D28B8233103112B78AE3AA782E6F4038355E79A59F5B5622D31CDCA08
    //y coordinate:
    //0x000EE236FF88D25BF642F4BDA86949A29791A261CBCA1D7E5C70A4BDCDCFC9DF758D3BD77B2E389165EB38670A1F27212692ECA6E9A29E0E284B0F3AF76F811F4D9A
    unsigned char pubKey[132] = {
        0x00,
        0x0B,
        0xBC,
        0xE9,
        0x26,
        0xE7,
        0x1B,
        0x3D,
        0xDC,
        0xBB,
        0x54,
        0xC3,
        0x43,
        0xBA,
        0x3A,
        0x7F,
        0x65,
        0xBB,
        0x1F,
        0x11,
        0x54,
        0x7E,
        0xBF,
        0xA3,
        0xED,
        0x09,
        0x2E,
        0xD1,
        0x53,
        0x65,
        0xFF,
        0x56,
        0xCE,
        0x4D,
        0xA2,
        0xEC,
        0x60,
        0x6D,
        0x28,
        0xB8,
        0x23,
        0x31,
        0x03,
        0x11,
        0x2B,
        0x78,
        0xAE,
        0x3A,
        0xA7,
        0x82,
        0xE6,
        0xF4,
        0x03,
        0x83,
        0x55,
        0xE7,
        0x9A,
        0x59,
        0xF5,
        0xB5,
        0x62,
        0x2D,
        0x31,
        0xCD,
        0xCA,
        0x08,
        0x00,
        0x0E,
        0xE2,
        0x36,
        0xFF,
        0x88,
        0xD2,
        0x5B,
        0xF6,
        0x42,
        0xF4,
        0xBD,
        0xA8,
        0x69,
        0x49,
        0xA2,
        0x97,
        0x91,
        0xA2,
        0x61,
        0xCB,
        0xCA,
        0x1D,
        0x7E,
        0x5C,
        0x70,
        0xA4,
        0xBD,
        0xCD,
        0xCF,
        0xC9,
        0xDF,
        0x75,
        0x8D,
        0x3B,
        0xD7,
        0x7B,
        0x2E,
        0x38,
        0x91,
        0x65,
        0xEB,
        0x38,
        0x67,
        0x0A,
        0x1F,
        0x27,
        0x21,
        0x26,
        0x92,
        0xEC,
        0xA6,
        0xE9,
        0xA2,
        0x9E,
        0x0E,
        0x28,
        0x4B,
        0x0F,
        0x3A,
        0xF7,
        0x6F,
        0x81,
        0x1F,
        0x4D,
        0x9A,
    };

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //r:0x000AFE8511D60C270B6CF805FC164B1A95323A3CACDE41238D4A63F10E645CBFB722500AE7AC0DC931B9EEDD1DFA28FEF32DD65ED239F36B0E6894AE1755567E3A10
    unsigned char std_signature_r[] = {
        0x00,
        0x0A,
        0xFE,
        0x85,
        0x11,
        0xD6,
        0x0C,
        0x27,
        0x0B,
        0x6C,
        0xF8,
        0x05,
        0xFC,
        0x16,
        0x4B,
        0x1A,
        0x95,
        0x32,
        0x3A,
        0x3C,
        0xAC,
        0xDE,
        0x41,
        0x23,
        0x8D,
        0x4A,
        0x63,
        0xF1,
        0x0E,
        0x64,
        0x5C,
        0xBF,
        0xB7,
        0x22,
        0x50,
        0x0A,
        0xE7,
        0xAC,
        0x0D,
        0xC9,
        0x31,
        0xB9,
        0xEE,
        0xDD,
        0x1D,
        0xFA,
        0x28,
        0xFE,
        0xF3,
        0x2D,
        0xD6,
        0x5E,
        0xD2,
        0x39,
        0xF3,
        0x6B,
        0x0E,
        0x68,
        0x94,
        0xAE,
        0x17,
        0x55,
        0x56,
        0x7E,
        0x3A,
        0x10,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0x00DCD411A4AB7B58B15A5B4702DB1E618F3F85D82671B6AA54B4AE093BD021DDD21B9C4F8EF2988F6CB02A7060584CD5E78CF0193923D97FE97783B0F3F8516C3F37
    unsigned char std_signature_s_zero[] = {
        0x00,
        0xDC,
        0xD4,
        0x11,
        0xA4,
        0xAB,
        0x7B,
        0x58,
        0xB1,
        0x5A,
        0x5B,
        0x47,
        0x02,
        0xDB,
        0x1E,
        0x61,
        0x8F,
        0x3F,
        0x85,
        0xD8,
        0x26,
        0x71,
        0xB6,
        0xAA,
        0x54,
        0xB4,
        0xAE,
        0x09,
        0x3B,
        0xD0,
        0x21,
        0xDD,
        0xD2,
        0x1B,
        0x9C,
        0x4F,
        0x8E,
        0xF2,
        0x98,
        0x8F,
        0x6C,
        0xB0,
        0x2A,
        0x70,
        0x60,
        0x58,
        0x4C,
        0xD5,
        0xE7,
        0x8C,
        0xF0,
        0x19,
        0x39,
        0x23,
        0xD9,
        0x7F,
        0xE9,
        0x77,
        0x83,
        0xB0,
        0xF3,
        0xF8,
        0x51,
        0x6C,
        0x3F,
        0x37,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0x016F80A230281934F325B705A49B5051268AE99107FEA56C04542857EBB83177F6FFBC240091A04C5667AE124CE17018F913EC58E31E2DA18FD346EE7C4CBECBFE4D
    unsigned char std_signature_s_1[] = {
        0x01,
        0x6F,
        0x80,
        0xA2,
        0x30,
        0x28,
        0x19,
        0x34,
        0xF3,
        0x25,
        0xB7,
        0x05,
        0xA4,
        0x9B,
        0x50,
        0x51,
        0x26,
        0x8A,
        0xE9,
        0x91,
        0x07,
        0xFE,
        0xA5,
        0x6C,
        0x04,
        0x54,
        0x28,
        0x57,
        0xEB,
        0xB8,
        0x31,
        0x77,
        0xF6,
        0xFF,
        0xBC,
        0x24,
        0x00,
        0x91,
        0xA0,
        0x4C,
        0x56,
        0x67,
        0xAE,
        0x12,
        0x4C,
        0xE1,
        0x70,
        0x18,
        0xF9,
        0x13,
        0xEC,
        0x58,
        0xE3,
        0x1E,
        0x2D,
        0xA1,
        0x8F,
        0xD3,
        0x46,
        0xEE,
        0x7C,
        0x4C,
        0xBE,
        0xCB,
        0xFE,
        0x4D,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0x016E021EA3734D96615266183DB3D9DB49ACCA075C1987E9B87892797080B57F6A5DBE16BD40B9437FEAA0608B225C6F4364FA4C992B3187DAFE2C917A2E72399046
    unsigned char std_signature_s_FF[] = {
        0x01,
        0x6E,
        0x02,
        0x1E,
        0xA3,
        0x73,
        0x4D,
        0x96,
        0x61,
        0x52,
        0x66,
        0x18,
        0x3D,
        0xB3,
        0xD9,
        0xDB,
        0x49,
        0xAC,
        0xCA,
        0x07,
        0x5C,
        0x19,
        0x87,
        0xE9,
        0xB8,
        0x78,
        0x92,
        0x79,
        0x70,
        0x80,
        0xB5,
        0x7F,
        0x6A,
        0x5D,
        0xBE,
        0x16,
        0xBD,
        0x40,
        0xB9,
        0x43,
        0x7F,
        0xEA,
        0xA0,
        0x60,
        0x8B,
        0x22,
        0x5C,
        0x6F,
        0x43,
        0x64,
        0xFA,
        0x4C,
        0x99,
        0x2B,
        0x31,
        0x87,
        0xDA,
        0xFE,
        0x2C,
        0x91,
        0x7A,
        0x2E,
        0x72,
        0x39,
        0x90,
        0x46,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x018B6EAD6E30FC1D60335678C770EB21F2133D5997F075625AF64AD6BC54D4779163037C64A58C39999CA5D18AD1DD19A531D4BE7EC0AB7928AF9ABDDA36BC71EC8F
    unsigned char std_signature_s_md5[] = {
        0x01,
        0x8B,
        0x6E,
        0xAD,
        0x6E,
        0x30,
        0xFC,
        0x1D,
        0x60,
        0x33,
        0x56,
        0x78,
        0xC7,
        0x70,
        0xEB,
        0x21,
        0xF2,
        0x13,
        0x3D,
        0x59,
        0x97,
        0xF0,
        0x75,
        0x62,
        0x5A,
        0xF6,
        0x4A,
        0xD6,
        0xBC,
        0x54,
        0xD4,
        0x77,
        0x91,
        0x63,
        0x03,
        0x7C,
        0x64,
        0xA5,
        0x8C,
        0x39,
        0x99,
        0x9C,
        0xA5,
        0xD1,
        0x8A,
        0xD1,
        0xDD,
        0x19,
        0xA5,
        0x31,
        0xD4,
        0xBE,
        0x7E,
        0xC0,
        0xAB,
        0x79,
        0x28,
        0xAF,
        0x9A,
        0xBD,
        0xDA,
        0x36,
        0xBC,
        0x71,
        0xEC,
        0x8F,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x0136A9E191A8C00DBA5202A55F556611C2DB91D1D2DBC50E4CA29AE4227F7B0A73AE42A4F1040561BB5062F5D5025E4715CDE7CF303DB15AD9487DC327C16ABAC426
    unsigned char std_signature_s_sha1[] = {
        0x01,
        0x36,
        0xA9,
        0xE1,
        0x91,
        0xA8,
        0xC0,
        0x0D,
        0xBA,
        0x52,
        0x02,
        0xA5,
        0x5F,
        0x55,
        0x66,
        0x11,
        0xC2,
        0xDB,
        0x91,
        0xD1,
        0xD2,
        0xDB,
        0xC5,
        0x0E,
        0x4C,
        0xA2,
        0x9A,
        0xE4,
        0x22,
        0x7F,
        0x7B,
        0x0A,
        0x73,
        0xAE,
        0x42,
        0xA4,
        0xF1,
        0x04,
        0x05,
        0x61,
        0xBB,
        0x50,
        0x62,
        0xF5,
        0xD5,
        0x02,
        0x5E,
        0x47,
        0x15,
        0xCD,
        0xE7,
        0xCF,
        0x30,
        0x3D,
        0xB1,
        0x5A,
        0xD9,
        0x48,
        0x7D,
        0xC3,
        0x27,
        0xC1,
        0x6A,
        0xBA,
        0xC4,
        0x26,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x0171F5878CB7401D094B2D2C750830CB7454C626ECD58EB928429E414344FB4EC97279DD87C4BA73A39D8E2AAC7873E0DF3A5FDD3876F094D35111D6363E234C70F6
    unsigned char std_signature_s_192[] = {
        0x01,
        0x71,
        0xF5,
        0x87,
        0x8C,
        0xB7,
        0x40,
        0x1D,
        0x09,
        0x4B,
        0x2D,
        0x2C,
        0x75,
        0x08,
        0x30,
        0xCB,
        0x74,
        0x54,
        0xC6,
        0x26,
        0xEC,
        0xD5,
        0x8E,
        0xB9,
        0x28,
        0x42,
        0x9E,
        0x41,
        0x43,
        0x44,
        0xFB,
        0x4E,
        0xC9,
        0x72,
        0x79,
        0xDD,
        0x87,
        0xC4,
        0xBA,
        0x73,
        0xA3,
        0x9D,
        0x8E,
        0x2A,
        0xAC,
        0x78,
        0x73,
        0xE0,
        0xDF,
        0x3A,
        0x5F,
        0xDD,
        0x38,
        0x76,
        0xF0,
        0x94,
        0xD3,
        0x51,
        0x11,
        0xD6,
        0x36,
        0x3E,
        0x23,
        0x4C,
        0x70,
        0xF6,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0x0005A0C803C06C17980E1B2496AFB8291151E90ED01F6DA73399E5476326F7C400B776A901328B0282226475A2F10C30AE20D8096DBA1CFE1C4C3DBBD3AB09FA7B6F
    unsigned char std_signature_s_sha224[] = {
        0x00,
        0x05,
        0xA0,
        0xC8,
        0x03,
        0xC0,
        0x6C,
        0x17,
        0x98,
        0x0E,
        0x1B,
        0x24,
        0x96,
        0xAF,
        0xB8,
        0x29,
        0x11,
        0x51,
        0xE9,
        0x0E,
        0xD0,
        0x1F,
        0x6D,
        0xA7,
        0x33,
        0x99,
        0xE5,
        0x47,
        0x63,
        0x26,
        0xF7,
        0xC4,
        0x00,
        0xB7,
        0x76,
        0xA9,
        0x01,
        0x32,
        0x8B,
        0x02,
        0x82,
        0x22,
        0x64,
        0x75,
        0xA2,
        0xF1,
        0x0C,
        0x30,
        0xAE,
        0x20,
        0xD8,
        0x09,
        0x6D,
        0xBA,
        0x1C,
        0xFE,
        0x1C,
        0x4C,
        0x3D,
        0xBB,
        0xD3,
        0xAB,
        0x09,
        0xFA,
        0x7B,
        0x6F,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0x01C1966BCD41A937859A4E6B719ACB50D85185D7B91231A3C5B02AA715F9CC7DE654E724E6FEC386EF665007BCC7EC381A76D0CC4E53A0E8BA91D8926549CE1D62C3
    unsigned char std_signature_s_sha256[] = {
        0x01,
        0xC1,
        0x96,
        0x6B,
        0xCD,
        0x41,
        0xA9,
        0x37,
        0x85,
        0x9A,
        0x4E,
        0x6B,
        0x71,
        0x9A,
        0xCB,
        0x50,
        0xD8,
        0x51,
        0x85,
        0xD7,
        0xB9,
        0x12,
        0x31,
        0xA3,
        0xC5,
        0xB0,
        0x2A,
        0xA7,
        0x15,
        0xF9,
        0xCC,
        0x7D,
        0xE6,
        0x54,
        0xE7,
        0x24,
        0xE6,
        0xFE,
        0xC3,
        0x86,
        0xEF,
        0x66,
        0x50,
        0x07,
        0xBC,
        0xC7,
        0xEC,
        0x38,
        0x1A,
        0x76,
        0xD0,
        0xCC,
        0x4E,
        0x53,
        0xA0,
        0xE8,
        0xBA,
        0x91,
        0xD8,
        0x92,
        0x65,
        0x49,
        0xCE,
        0x1D,
        0x62,
        0xC3,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x010F0873010B262D1BC6285799FD42BE2D5AB46164835C1630DD41B2409455EDA6D8ADF117B3AA6AB11613D0E2C938E3C46636DA9CEEAF34EB930E0DB42379B7CCA9
    unsigned char std_signature_s_sha384[] = {
        0x01,
        0x0F,
        0x08,
        0x73,
        0x01,
        0x0B,
        0x26,
        0x2D,
        0x1B,
        0xC6,
        0x28,
        0x57,
        0x99,
        0xFD,
        0x42,
        0xBE,
        0x2D,
        0x5A,
        0xB4,
        0x61,
        0x64,
        0x83,
        0x5C,
        0x16,
        0x30,
        0xDD,
        0x41,
        0xB2,
        0x40,
        0x94,
        0x55,
        0xED,
        0xA6,
        0xD8,
        0xAD,
        0xF1,
        0x17,
        0xB3,
        0xAA,
        0x6A,
        0xB1,
        0x16,
        0x13,
        0xD0,
        0xE2,
        0xC9,
        0x38,
        0xE3,
        0xC4,
        0x66,
        0x36,
        0xDA,
        0x9C,
        0xEE,
        0xAF,
        0x34,
        0xEB,
        0x93,
        0x0E,
        0x0D,
        0xB4,
        0x23,
        0x79,
        0xB7,
        0xCC,
        0xA9,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x01B554E7B5F4935AFB7829A83AC8FEA660C86B943E4C29BE875EE5431FDE602C73548990A0CDA89BFEF25D76C7D77108DC3F77A3C6F516853A65D3B1F7EE632DF314
    unsigned char std_signature_s_sha512[] = {
        0x01,
        0xB5,
        0x54,
        0xE7,
        0xB5,
        0xF4,
        0x93,
        0x5A,
        0xFB,
        0x78,
        0x29,
        0xA8,
        0x3A,
        0xC8,
        0xFE,
        0xA6,
        0x60,
        0xC8,
        0x6B,
        0x94,
        0x3E,
        0x4C,
        0x29,
        0xBE,
        0x87,
        0x5E,
        0xE5,
        0x43,
        0x1F,
        0xDE,
        0x60,
        0x2C,
        0x73,
        0x54,
        0x89,
        0x90,
        0xA0,
        0xCD,
        0xA8,
        0x9B,
        0xFE,
        0xF2,
        0x5D,
        0x76,
        0xC7,
        0xD7,
        0x71,
        0x08,
        0xDC,
        0x3F,
        0x77,
        0xA3,
        0xC6,
        0xF5,
        0x16,
        0x85,
        0x3A,
        0x65,
        0xD3,
        0xB1,
        0xF7,
        0xEE,
        0x63,
        0x2D,
        0xF3,
        0x14,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0x001D8A7A850733705E2DDAE412CB919790AF3811EBA0C28D74C81DA7C56EB93CE98249AA970EB9AEA23F5E8241CAC41BD7B6A01021CD1C4F91519423ABA7DDE80B57
    unsigned char std_signature_s_544[] = {
        0x00,
        0x1D,
        0x8A,
        0x7A,
        0x85,
        0x07,
        0x33,
        0x70,
        0x5E,
        0x2D,
        0xDA,
        0xE4,
        0x12,
        0xCB,
        0x91,
        0x97,
        0x90,
        0xAF,
        0x38,
        0x11,
        0xEB,
        0xA0,
        0xC2,
        0x8D,
        0x74,
        0xC8,
        0x1D,
        0xA7,
        0xC5,
        0x6E,
        0xB9,
        0x3C,
        0xE9,
        0x82,
        0x49,
        0xAA,
        0x97,
        0x0E,
        0xB9,
        0xAE,
        0xA2,
        0x3F,
        0x5E,
        0x82,
        0x41,
        0xCA,
        0xC4,
        0x1B,
        0xD7,
        0xB6,
        0xA0,
        0x10,
        0x21,
        0xCD,
        0x1C,
        0x4F,
        0x91,
        0x51,
        0x94,
        0x23,
        0xAB,
        0xA7,
        0xDD,
        0xE8,
        0x0B,
        0x57,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)secp521r1;
    char         *curve_name = "secp521r1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
unsigned int ecdsa_std_test_anders_1024_1(void)
{
    //k:
    //0xCCBDEBCAE1E5DDBA316A8B4EA14DE83C9F8DA481702B69EA6073BCDE2AA3FD8769839E6DA51030E2C9436BF11B77E20765A59CACBB578E5A1A5608DFD319D008
    //0xFFFED02D5AF552BCA3FAED1DA78EDDCADAD0F8A54729EEEB3DB03AED6EC805C0EE3AE6B014F26D158A1685CF047D440EEA576EDAF22606880153D414146118A4
    unsigned char rand_k[128] = {
        0xCC,
        0xBD,
        0xEB,
        0xCA,
        0xE1,
        0xE5,
        0xDD,
        0xBA,
        0x31,
        0x6A,
        0x8B,
        0x4E,
        0xA1,
        0x4D,
        0xE8,
        0x3C,
        0x9F,
        0x8D,
        0xA4,
        0x81,
        0x70,
        0x2B,
        0x69,
        0xEA,
        0x60,
        0x73,
        0xBC,
        0xDE,
        0x2A,
        0xA3,
        0xFD,
        0x87,
        0x69,
        0x83,
        0x9E,
        0x6D,
        0xA5,
        0x10,
        0x30,
        0xE2,
        0xC9,
        0x43,
        0x6B,
        0xF1,
        0x1B,
        0x77,
        0xE2,
        0x07,
        0x65,
        0xA5,
        0x9C,
        0xAC,
        0xBB,
        0x57,
        0x8E,
        0x5A,
        0x1A,
        0x56,
        0x08,
        0xDF,
        0xD3,
        0x19,
        0xD0,
        0x08,
        0xFF,
        0xFE,
        0xD0,
        0x2D,
        0x5A,
        0xF5,
        0x52,
        0xBC,
        0xA3,
        0xFA,
        0xED,
        0x1D,
        0xA7,
        0x8E,
        0xDD,
        0xCA,
        0xDA,
        0xD0,
        0xF8,
        0xA5,
        0x47,
        0x29,
        0xEE,
        0xEB,
        0x3D,
        0xB0,
        0x3A,
        0xED,
        0x6E,
        0xC8,
        0x05,
        0xC0,
        0xEE,
        0x3A,
        0xE6,
        0xB0,
        0x14,
        0xF2,
        0x6D,
        0x15,
        0x8A,
        0x16,
        0x85,
        0xCF,
        0x04,
        0x7D,
        0x44,
        0x0E,
        0xEA,
        0x57,
        0x6E,
        0xDA,
        0xF2,
        0x26,
        0x06,
        0x88,
        0x01,
        0x53,
        0xD4,
        0x14,
        0x14,
        0x61,
        0x18,
        0xA4,
    };

    //private key:
    //0xF8A9BBA6799FF00171D4B33AA71B31BC6BBEB91820CCDFD71624324080273106ED6B21EEF6346B6EEEF059DD5ABCAC38A14EC298B322B02D5B7EBABB63B6ED96
    //0xAA10D17598903184FA696D7111593ABAF0238610FE49BDF019A8B25DA2BD18403D0DB5879C91F5134F279E5D9DBC96547333C3B5B8517EB641B7A4BEB35A362C
    unsigned char priKey[128] = {
        0xF8,
        0xA9,
        0xBB,
        0xA6,
        0x79,
        0x9F,
        0xF0,
        0x01,
        0x71,
        0xD4,
        0xB3,
        0x3A,
        0xA7,
        0x1B,
        0x31,
        0xBC,
        0x6B,
        0xBE,
        0xB9,
        0x18,
        0x20,
        0xCC,
        0xDF,
        0xD7,
        0x16,
        0x24,
        0x32,
        0x40,
        0x80,
        0x27,
        0x31,
        0x06,
        0xED,
        0x6B,
        0x21,
        0xEE,
        0xF6,
        0x34,
        0x6B,
        0x6E,
        0xEE,
        0xF0,
        0x59,
        0xDD,
        0x5A,
        0xBC,
        0xAC,
        0x38,
        0xA1,
        0x4E,
        0xC2,
        0x98,
        0xB3,
        0x22,
        0xB0,
        0x2D,
        0x5B,
        0x7E,
        0xBA,
        0xBB,
        0x63,
        0xB6,
        0xED,
        0x96,
        0xAA,
        0x10,
        0xD1,
        0x75,
        0x98,
        0x90,
        0x31,
        0x84,
        0xFA,
        0x69,
        0x6D,
        0x71,
        0x11,
        0x59,
        0x3A,
        0xBA,
        0xF0,
        0x23,
        0x86,
        0x10,
        0xFE,
        0x49,
        0xBD,
        0xF0,
        0x19,
        0xA8,
        0xB2,
        0x5D,
        0xA2,
        0xBD,
        0x18,
        0x40,
        0x3D,
        0x0D,
        0xB5,
        0x87,
        0x9C,
        0x91,
        0xF5,
        0x13,
        0x4F,
        0x27,
        0x9E,
        0x5D,
        0x9D,
        0xBC,
        0x96,
        0x54,
        0x73,
        0x33,
        0xC3,
        0xB5,
        0xB8,
        0x51,
        0x7E,
        0xB6,
        0x41,
        0xB7,
        0xA4,
        0xBE,
        0xB3,
        0x5A,
        0x36,
        0x2C,
    };

    //public key:
    //x coordinate:
    //0xA5D50F9D4CF64C761D0920D4BD767C5997CD5CF50C243D84E8BD14AD7BB295206BCA8C862EBFF35F7A97ADAF4A4538070B836BF4B1A3F11CBB36DC428BFAE948
    //0x8C1EFD84E6ADF017834A8C16DF18B5D716784456B7F0E438CD0201DD46EB794EEA11B3DFFB333C366247A8186B6433E1A6E4EE4D06772CE4C21BD55ECB281932
    //y coordinate:
    //0x2240CCCF32CE86EF4A93A81FE5862036D249FDD9E1D06E395ED32A4AF5512A1B52DCB0D7B48EACA479646DB821B5ACA27AE9CE3B6B1EA9683A201AC458E15C3F
    //0x2AFD9E1405DDCA33543CA5BAC35D43CF0425515745F491178219F4F3B0EB66D643728B3C8E8E7FFE20B9376C4999E5005AED71EBA380CF1858381E52982BDA67
    unsigned char pubKey[256] = {
        0xA5,
        0xD5,
        0x0F,
        0x9D,
        0x4C,
        0xF6,
        0x4C,
        0x76,
        0x1D,
        0x09,
        0x20,
        0xD4,
        0xBD,
        0x76,
        0x7C,
        0x59,
        0x97,
        0xCD,
        0x5C,
        0xF5,
        0x0C,
        0x24,
        0x3D,
        0x84,
        0xE8,
        0xBD,
        0x14,
        0xAD,
        0x7B,
        0xB2,
        0x95,
        0x20,
        0x6B,
        0xCA,
        0x8C,
        0x86,
        0x2E,
        0xBF,
        0xF3,
        0x5F,
        0x7A,
        0x97,
        0xAD,
        0xAF,
        0x4A,
        0x45,
        0x38,
        0x07,
        0x0B,
        0x83,
        0x6B,
        0xF4,
        0xB1,
        0xA3,
        0xF1,
        0x1C,
        0xBB,
        0x36,
        0xDC,
        0x42,
        0x8B,
        0xFA,
        0xE9,
        0x48,
        0x8C,
        0x1E,
        0xFD,
        0x84,
        0xE6,
        0xAD,
        0xF0,
        0x17,
        0x83,
        0x4A,
        0x8C,
        0x16,
        0xDF,
        0x18,
        0xB5,
        0xD7,
        0x16,
        0x78,
        0x44,
        0x56,
        0xB7,
        0xF0,
        0xE4,
        0x38,
        0xCD,
        0x02,
        0x01,
        0xDD,
        0x46,
        0xEB,
        0x79,
        0x4E,
        0xEA,
        0x11,
        0xB3,
        0xDF,
        0xFB,
        0x33,
        0x3C,
        0x36,
        0x62,
        0x47,
        0xA8,
        0x18,
        0x6B,
        0x64,
        0x33,
        0xE1,
        0xA6,
        0xE4,
        0xEE,
        0x4D,
        0x06,
        0x77,
        0x2C,
        0xE4,
        0xC2,
        0x1B,
        0xD5,
        0x5E,
        0xCB,
        0x28,
        0x19,
        0x32,
        0x22,
        0x40,
        0xCC,
        0xCF,
        0x32,
        0xCE,
        0x86,
        0xEF,
        0x4A,
        0x93,
        0xA8,
        0x1F,
        0xE5,
        0x86,
        0x20,
        0x36,
        0xD2,
        0x49,
        0xFD,
        0xD9,
        0xE1,
        0xD0,
        0x6E,
        0x39,
        0x5E,
        0xD3,
        0x2A,
        0x4A,
        0xF5,
        0x51,
        0x2A,
        0x1B,
        0x52,
        0xDC,
        0xB0,
        0xD7,
        0xB4,
        0x8E,
        0xAC,
        0xA4,
        0x79,
        0x64,
        0x6D,
        0xB8,
        0x21,
        0xB5,
        0xAC,
        0xA2,
        0x7A,
        0xE9,
        0xCE,
        0x3B,
        0x6B,
        0x1E,
        0xA9,
        0x68,
        0x3A,
        0x20,
        0x1A,
        0xC4,
        0x58,
        0xE1,
        0x5C,
        0x3F,
        0x2A,
        0xFD,
        0x9E,
        0x14,
        0x05,
        0xDD,
        0xCA,
        0x33,
        0x54,
        0x3C,
        0xA5,
        0xBA,
        0xC3,
        0x5D,
        0x43,
        0xCF,
        0x04,
        0x25,
        0x51,
        0x57,
        0x45,
        0xF4,
        0x91,
        0x17,
        0x82,
        0x19,
        0xF4,
        0xF3,
        0xB0,
        0xEB,
        0x66,
        0xD6,
        0x43,
        0x72,
        0x8B,
        0x3C,
        0x8E,
        0x8E,
        0x7F,
        0xFE,
        0x20,
        0xB9,
        0x37,
        0x6C,
        0x49,
        0x99,
        0xE5,
        0x00,
        0x5A,
        0xED,
        0x71,
        0xEB,
        0xA3,
        0x80,
        0xCF,
        0x18,
        0x58,
        0x38,
        0x1E,
        0x52,
        0x98,
        0x2B,
        0xDA,
        0x67,
    };

    //standard signature(the default data is r, it is fixed for the curve and rand_k)
    //signature r:
    //0x979CC1E009FC6D2EEBDFA5363D11E80D23A450ED2F1BE68A60DFC96641ADE5302DA7A037CC5D93397E0BBD216524487D1F21E368A203B7B05AE10C7DF458713F
    //0x6CEFE23D687DD56BF2586A6B21BABF8EDCA76310995E37206E5CF31EA8318C6C08054BAD4364D716EDB2115DA7229738D6754BF894E57C73BAFCDFEB13B6BACB
    unsigned char std_signature_r[] = {
        0x97,
        0x9C,
        0xC1,
        0xE0,
        0x09,
        0xFC,
        0x6D,
        0x2E,
        0xEB,
        0xDF,
        0xA5,
        0x36,
        0x3D,
        0x11,
        0xE8,
        0x0D,
        0x23,
        0xA4,
        0x50,
        0xED,
        0x2F,
        0x1B,
        0xE6,
        0x8A,
        0x60,
        0xDF,
        0xC9,
        0x66,
        0x41,
        0xAD,
        0xE5,
        0x30,
        0x2D,
        0xA7,
        0xA0,
        0x37,
        0xCC,
        0x5D,
        0x93,
        0x39,
        0x7E,
        0x0B,
        0xBD,
        0x21,
        0x65,
        0x24,
        0x48,
        0x7D,
        0x1F,
        0x21,
        0xE3,
        0x68,
        0xA2,
        0x03,
        0xB7,
        0xB0,
        0x5A,
        0xE1,
        0x0C,
        0x7D,
        0xF4,
        0x58,
        0x71,
        0x3F,
        0x6C,
        0xEF,
        0xE2,
        0x3D,
        0x68,
        0x7D,
        0xD5,
        0x6B,
        0xF2,
        0x58,
        0x6A,
        0x6B,
        0x21,
        0xBA,
        0xBF,
        0x8E,
        0xDC,
        0xA7,
        0x63,
        0x10,
        0x99,
        0x5E,
        0x37,
        0x20,
        0x6E,
        0x5C,
        0xF3,
        0x1E,
        0xA8,
        0x31,
        0x8C,
        0x6C,
        0x08,
        0x05,
        0x4B,
        0xAD,
        0x43,
        0x64,
        0xD7,
        0x16,
        0xED,
        0xB2,
        0x11,
        0x5D,
        0xA7,
        0x22,
        0x97,
        0x38,
        0xD6,
        0x75,
        0x4B,
        0xF8,
        0x94,
        0xE5,
        0x7C,
        0x73,
        0xBA,
        0xFC,
        0xDF,
        0xEB,
        0x13,
        0xB6,
        0xBA,
        0xCB,
    };

    /********************* standard data test(E=0) **********************/
    //signature s:
    //0xE09E8278FA3084DEC5E1FB37FE0DA3414054A0E12133B910CF080CC95D36DF1318952139B48E3714C709200F76AB9D5F259A080D6A9D85A780CE692E23C6EBC2
    //0xC0CD1E4F5C27DA2FD1D4A5AFFCDF1E74F1C416EFF0277713765CAC801DA0B923AC8712F0E6E07235D9193BD98A5131DC1719B0016A9DD3FE9EB0C9663A3AEF7C
    unsigned char std_signature_s_zero[] = {
        0xE0,
        0x9E,
        0x82,
        0x78,
        0xFA,
        0x30,
        0x84,
        0xDE,
        0xC5,
        0xE1,
        0xFB,
        0x37,
        0xFE,
        0x0D,
        0xA3,
        0x41,
        0x40,
        0x54,
        0xA0,
        0xE1,
        0x21,
        0x33,
        0xB9,
        0x10,
        0xCF,
        0x08,
        0x0C,
        0xC9,
        0x5D,
        0x36,
        0xDF,
        0x13,
        0x18,
        0x95,
        0x21,
        0x39,
        0xB4,
        0x8E,
        0x37,
        0x14,
        0xC7,
        0x09,
        0x20,
        0x0F,
        0x76,
        0xAB,
        0x9D,
        0x5F,
        0x25,
        0x9A,
        0x08,
        0x0D,
        0x6A,
        0x9D,
        0x85,
        0xA7,
        0x80,
        0xCE,
        0x69,
        0x2E,
        0x23,
        0xC6,
        0xEB,
        0xC2,
        0xC0,
        0xCD,
        0x1E,
        0x4F,
        0x5C,
        0x27,
        0xDA,
        0x2F,
        0xD1,
        0xD4,
        0xA5,
        0xAF,
        0xFC,
        0xDF,
        0x1E,
        0x74,
        0xF1,
        0xC4,
        0x16,
        0xEF,
        0xF0,
        0x27,
        0x77,
        0x13,
        0x76,
        0x5C,
        0xAC,
        0x80,
        0x1D,
        0xA0,
        0xB9,
        0x23,
        0xAC,
        0x87,
        0x12,
        0xF0,
        0xE6,
        0xE0,
        0x72,
        0x35,
        0xD9,
        0x19,
        0x3B,
        0xD9,
        0x8A,
        0x51,
        0x31,
        0xDC,
        0x17,
        0x19,
        0xB0,
        0x01,
        0x6A,
        0x9D,
        0xD3,
        0xFE,
        0x9E,
        0xB0,
        0xC9,
        0x66,
        0x3A,
        0x3A,
        0xEF,
        0x7C,
    };

    /********************* standard data test(E=1) **********************/
    //signature s:
    //0X0001773C18D20EEA70BB230AA068321D1A9BF0ACE1D707E03A27B38D7CDC29EC2A951DA8EF4E82390FC99C99469A6758D6C54A30D6DA5C769E1999664B110E46
    //0X1BF2A21CE8983B2AA0EBE8CA103A8D39E4511CCCA3EF352E4DF4257DD84B40A32CFC2F44870A5B398E3A94657F56BF8291CC5FD25D367862A25691CEEE4EE25B
    unsigned char std_signature_s_1[] = {
        0x00,
        0x01,
        0x77,
        0x3C,
        0x18,
        0xD2,
        0x0E,
        0xEA,
        0x70,
        0xBB,
        0x23,
        0x0A,
        0xA0,
        0x68,
        0x32,
        0x1D,
        0x1A,
        0x9B,
        0xF0,
        0xAC,
        0xE1,
        0xD7,
        0x07,
        0xE0,
        0x3A,
        0x27,
        0xB3,
        0x8D,
        0x7C,
        0xDC,
        0x29,
        0xEC,
        0x2A,
        0x95,
        0x1D,
        0xA8,
        0xEF,
        0x4E,
        0x82,
        0x39,
        0x0F,
        0xC9,
        0x9C,
        0x99,
        0x46,
        0x9A,
        0x67,
        0x58,
        0xD6,
        0xC5,
        0x4A,
        0x30,
        0xD6,
        0xDA,
        0x5C,
        0x76,
        0x9E,
        0x19,
        0x99,
        0x66,
        0x4B,
        0x11,
        0x0E,
        0x46,
        0x1B,
        0xF2,
        0xA2,
        0x1C,
        0xE8,
        0x98,
        0x3B,
        0x2A,
        0xA0,
        0xEB,
        0xE8,
        0xCA,
        0x10,
        0x3A,
        0x8D,
        0x39,
        0xE4,
        0x51,
        0x1C,
        0xCC,
        0xA3,
        0xEF,
        0x35,
        0x2E,
        0x4D,
        0xF4,
        0x25,
        0x7D,
        0xD8,
        0x4B,
        0x40,
        0xA3,
        0x2C,
        0xFC,
        0x2F,
        0x44,
        0x87,
        0x0A,
        0x5B,
        0x39,
        0x8E,
        0x3A,
        0x94,
        0x65,
        0x7F,
        0x56,
        0xBF,
        0x82,
        0x91,
        0xCC,
        0x5F,
        0xD2,
        0x5D,
        0x36,
        0x78,
        0x62,
        0xA2,
        0x56,
        0x91,
        0xCE,
        0xEE,
        0x4E,
        0xE2,
        0x5B,
    };

    /********************* standard data test(E=0xFF..FF) **********************/
    //signature s:
    //0X9A5C5B5CFC17BADAEAC9D1CC20CBEFDFA977B9BFBBBFDFF4448633C05E580CCCCCCBD53389519969F1AC94C3C528C6A45D61267444CC29EB53E1BE6DF21E8F8F
    //0X87C2060BBA00BA379210D26318BF31B7FB26AAE84EB5C1D01A080900B24FD2CDA967B5D4A5221F7E83683FE58B218703506EEABCEA01546E0F8CB519D457C854
    unsigned char std_signature_s_FF[] = {
        0x9A,
        0x5C,
        0x5B,
        0x5C,
        0xFC,
        0x17,
        0xBA,
        0xDA,
        0xEA,
        0xC9,
        0xD1,
        0xCC,
        0x20,
        0xCB,
        0xEF,
        0xDF,
        0xA9,
        0x77,
        0xB9,
        0xBF,
        0xBB,
        0xBF,
        0xDF,
        0xF4,
        0x44,
        0x86,
        0x33,
        0xC0,
        0x5E,
        0x58,
        0x0C,
        0xCC,
        0xCC,
        0xCB,
        0xD5,
        0x33,
        0x89,
        0x51,
        0x99,
        0x69,
        0xF1,
        0xAC,
        0x94,
        0xC3,
        0xC5,
        0x28,
        0xC6,
        0xA4,
        0x5D,
        0x61,
        0x26,
        0x74,
        0x44,
        0xCC,
        0x29,
        0xEB,
        0x53,
        0xE1,
        0xBE,
        0x6D,
        0xF2,
        0x1E,
        0x8F,
        0x8F,
        0x87,
        0xC2,
        0x06,
        0x0B,
        0xBA,
        0x00,
        0xBA,
        0x37,
        0x92,
        0x10,
        0xD2,
        0x63,
        0x18,
        0xBF,
        0x31,
        0xB7,
        0xFB,
        0x26,
        0xAA,
        0xE8,
        0x4E,
        0xB5,
        0xC1,
        0xD0,
        0x1A,
        0x08,
        0x09,
        0x00,
        0xB2,
        0x4F,
        0xD2,
        0xCD,
        0xA9,
        0x67,
        0xB5,
        0xD4,
        0xA5,
        0x22,
        0x1F,
        0x7E,
        0x83,
        0x68,
        0x3F,
        0xE5,
        0x8B,
        0x21,
        0x87,
        0x03,
        0x50,
        0x6E,
        0xEA,
        0xBC,
        0xEA,
        0x01,
        0x54,
        0x6E,
        0x0F,
        0x8C,
        0xB5,
        0x19,
        0xD4,
        0x57,
        0xC8,
        0x54,
    };


    /********************* standard data test(E-128bits) **********************/
    //signature s:
    //0x195DA6F845CF7A0B39194A8CE6C9B1D8A31908DBA34E77C9112A664310DD4D2FEB4A3849C9253C6E59F82DB92CE378B0F4EE2D3AF290F2D07C19B783F44215AA
    //0x46F97C93BD701E21F7AB97C413DDA2B0AE5B67FD5ACED48A66D9E01FB81C641A3A0411BC7FCF0715BA3269B7CB2A2A61E0ACE0A3E42F1A04595617F3E179C510
    unsigned char std_signature_s_md5[] = {
        0x19,
        0x5D,
        0xA6,
        0xF8,
        0x45,
        0xCF,
        0x7A,
        0x0B,
        0x39,
        0x19,
        0x4A,
        0x8C,
        0xE6,
        0xC9,
        0xB1,
        0xD8,
        0xA3,
        0x19,
        0x08,
        0xDB,
        0xA3,
        0x4E,
        0x77,
        0xC9,
        0x11,
        0x2A,
        0x66,
        0x43,
        0x10,
        0xDD,
        0x4D,
        0x2F,
        0xEB,
        0x4A,
        0x38,
        0x49,
        0xC9,
        0x25,
        0x3C,
        0x6E,
        0x59,
        0xF8,
        0x2D,
        0xB9,
        0x2C,
        0xE3,
        0x78,
        0xB0,
        0xF4,
        0xEE,
        0x2D,
        0x3A,
        0xF2,
        0x90,
        0xF2,
        0xD0,
        0x7C,
        0x19,
        0xB7,
        0x83,
        0xF4,
        0x42,
        0x15,
        0xAA,
        0x46,
        0xF9,
        0x7C,
        0x93,
        0xBD,
        0x70,
        0x1E,
        0x21,
        0xF7,
        0xAB,
        0x97,
        0xC4,
        0x13,
        0xDD,
        0xA2,
        0xB0,
        0xAE,
        0x5B,
        0x67,
        0xFD,
        0x5A,
        0xCE,
        0xD4,
        0x8A,
        0x66,
        0xD9,
        0xE0,
        0x1F,
        0xB8,
        0x1C,
        0x64,
        0x1A,
        0x3A,
        0x04,
        0x11,
        0xBC,
        0x7F,
        0xCF,
        0x07,
        0x15,
        0xBA,
        0x32,
        0x69,
        0xB7,
        0xCB,
        0x2A,
        0x2A,
        0x61,
        0xE0,
        0xAC,
        0xE0,
        0xA3,
        0xE4,
        0x2F,
        0x1A,
        0x04,
        0x59,
        0x56,
        0x17,
        0xF3,
        0xE1,
        0x79,
        0xC5,
        0x10,
    };

    /********************* standard data test(E-160bits) **********************/
    //signature s:
    //0x4B96EC8826A894B6289DDD8D5BF6A82F5A2E03937482F8D14A866C2FB8E25825661298590FAD0C21400B156E5D690C11E5B44AC930143970357015E2D0FE9F9A
    //0xBEDDE9E8047A4D18C3C7665961BAE8E95166A32B0E274E0296F858A3730D2D2762D3AF71DA736AECEF3DA2C0953449C6F5B5C97704C2489BCA0ADF5617F293AB
    unsigned char std_signature_s_sha1[] = {
        0x4B,
        0x96,
        0xEC,
        0x88,
        0x26,
        0xA8,
        0x94,
        0xB6,
        0x28,
        0x9D,
        0xDD,
        0x8D,
        0x5B,
        0xF6,
        0xA8,
        0x2F,
        0x5A,
        0x2E,
        0x03,
        0x93,
        0x74,
        0x82,
        0xF8,
        0xD1,
        0x4A,
        0x86,
        0x6C,
        0x2F,
        0xB8,
        0xE2,
        0x58,
        0x25,
        0x66,
        0x12,
        0x98,
        0x59,
        0x0F,
        0xAD,
        0x0C,
        0x21,
        0x40,
        0x0B,
        0x15,
        0x6E,
        0x5D,
        0x69,
        0x0C,
        0x11,
        0xE5,
        0xB4,
        0x4A,
        0xC9,
        0x30,
        0x14,
        0x39,
        0x70,
        0x35,
        0x70,
        0x15,
        0xE2,
        0xD0,
        0xFE,
        0x9F,
        0x9A,
        0xBE,
        0xDD,
        0xE9,
        0xE8,
        0x04,
        0x7A,
        0x4D,
        0x18,
        0xC3,
        0xC7,
        0x66,
        0x59,
        0x61,
        0xBA,
        0xE8,
        0xE9,
        0x51,
        0x66,
        0xA3,
        0x2B,
        0x0E,
        0x27,
        0x4E,
        0x02,
        0x96,
        0xF8,
        0x58,
        0xA3,
        0x73,
        0x0D,
        0x2D,
        0x27,
        0x62,
        0xD3,
        0xAF,
        0x71,
        0xDA,
        0x73,
        0x6A,
        0xEC,
        0xEF,
        0x3D,
        0xA2,
        0xC0,
        0x95,
        0x34,
        0x49,
        0xC6,
        0xF5,
        0xB5,
        0xC9,
        0x77,
        0x04,
        0xC2,
        0x48,
        0x9B,
        0xCA,
        0x0A,
        0xDF,
        0x56,
        0x17,
        0xF2,
        0x93,
        0xAB,
    };

    /********************* standard data test(E-192bits) **********************/
    //signature s:
    //0x8F169141379700A75906C6BE4C96530D02AC0EA65B85D08874366918D5D5D02A75CBFEC82C36DF3257EEDE7E11D9FC998ACE7D5C388EE0B3419E2B09E956C3D0
    //0x5F3B2CA9CB4462FB5ECE6FFF46CA05137E3EE31E88C97BD822A0A2B88F56E4D78CACF8CAFF885607D1FA7B699B4E5A3D5EE9472FCDF454E11493C7D52D120D63
    unsigned char std_signature_s_192[] = {
        0x8F,
        0x16,
        0x91,
        0x41,
        0x37,
        0x97,
        0x00,
        0xA7,
        0x59,
        0x06,
        0xC6,
        0xBE,
        0x4C,
        0x96,
        0x53,
        0x0D,
        0x02,
        0xAC,
        0x0E,
        0xA6,
        0x5B,
        0x85,
        0xD0,
        0x88,
        0x74,
        0x36,
        0x69,
        0x18,
        0xD5,
        0xD5,
        0xD0,
        0x2A,
        0x75,
        0xCB,
        0xFE,
        0xC8,
        0x2C,
        0x36,
        0xDF,
        0x32,
        0x57,
        0xEE,
        0xDE,
        0x7E,
        0x11,
        0xD9,
        0xFC,
        0x99,
        0x8A,
        0xCE,
        0x7D,
        0x5C,
        0x38,
        0x8E,
        0xE0,
        0xB3,
        0x41,
        0x9E,
        0x2B,
        0x09,
        0xE9,
        0x56,
        0xC3,
        0xD0,
        0x5F,
        0x3B,
        0x2C,
        0xA9,
        0xCB,
        0x44,
        0x62,
        0xFB,
        0x5E,
        0xCE,
        0x6F,
        0xFF,
        0x46,
        0xCA,
        0x05,
        0x13,
        0x7E,
        0x3E,
        0xE3,
        0x1E,
        0x88,
        0xC9,
        0x7B,
        0xD8,
        0x22,
        0xA0,
        0xA2,
        0xB8,
        0x8F,
        0x56,
        0xE4,
        0xD7,
        0x8C,
        0xAC,
        0xF8,
        0xCA,
        0xFF,
        0x88,
        0x56,
        0x07,
        0xD1,
        0xFA,
        0x7B,
        0x69,
        0x9B,
        0x4E,
        0x5A,
        0x3D,
        0x5E,
        0xE9,
        0x47,
        0x2F,
        0xCD,
        0xF4,
        0x54,
        0xE1,
        0x14,
        0x93,
        0xC7,
        0xD5,
        0x2D,
        0x12,
        0x0D,
        0x63,
    };

    /********************* standard data test(E-224bits) **********************/
    //signature s:
    //0xE2B53C15EDB249270198D84BAAF7EDA1BBA34201A6E83892967C7EED2869BAB9364E6AA4E63E945BFB0C87E8B57D278975C4DDCD08513363C54273E04B03A7AE
    //0x19869717B18F93DF12C7CB35B5DCD06FBBDEAFB76C486067DA3A7498024E553A80AB5E6382BBEB5E91058F9272F16163A1E3A2935AB9E5A93F707A1CE739234F
    unsigned char std_signature_s_sha224[] = {
        0xE2,
        0xB5,
        0x3C,
        0x15,
        0xED,
        0xB2,
        0x49,
        0x27,
        0x01,
        0x98,
        0xD8,
        0x4B,
        0xAA,
        0xF7,
        0xED,
        0xA1,
        0xBB,
        0xA3,
        0x42,
        0x01,
        0xA6,
        0xE8,
        0x38,
        0x92,
        0x96,
        0x7C,
        0x7E,
        0xED,
        0x28,
        0x69,
        0xBA,
        0xB9,
        0x36,
        0x4E,
        0x6A,
        0xA4,
        0xE6,
        0x3E,
        0x94,
        0x5B,
        0xFB,
        0x0C,
        0x87,
        0xE8,
        0xB5,
        0x7D,
        0x27,
        0x89,
        0x75,
        0xC4,
        0xDD,
        0xCD,
        0x08,
        0x51,
        0x33,
        0x63,
        0xC5,
        0x42,
        0x73,
        0xE0,
        0x4B,
        0x03,
        0xA7,
        0xAE,
        0x19,
        0x86,
        0x97,
        0x17,
        0xB1,
        0x8F,
        0x93,
        0xDF,
        0x12,
        0xC7,
        0xCB,
        0x35,
        0xB5,
        0xDC,
        0xD0,
        0x6F,
        0xBB,
        0xDE,
        0xAF,
        0xB7,
        0x6C,
        0x48,
        0x60,
        0x67,
        0xDA,
        0x3A,
        0x74,
        0x98,
        0x02,
        0x4E,
        0x55,
        0x3A,
        0x80,
        0xAB,
        0x5E,
        0x63,
        0x82,
        0xBB,
        0xEB,
        0x5E,
        0x91,
        0x05,
        0x8F,
        0x92,
        0x72,
        0xF1,
        0x61,
        0x63,
        0xA1,
        0xE3,
        0xA2,
        0x93,
        0x5A,
        0xB9,
        0xE5,
        0xA9,
        0x3F,
        0x70,
        0x7A,
        0x1C,
        0xE7,
        0x39,
        0x23,
        0x4F,
    };

    /********************* standard data test(E-256bits) **********************/
    //signature s:
    //0xB7B320C9F283F76BD6F3CD09CF0B88A1EB98B426C79F244017573B27F7A027D3409D5E943C17EB4128D9F14D939B331DFFF7D645C4EF2FEDBCCAEF1D7C4C3728
    //0x4E6D8E3663EC82C4D1FEE4C6F46938D25B71C8C670EB79EBD459B6E1D5C7C20F1E67269263EFF3E6988FF5F999F2DC68268F82AA74BDAEB2A39D622FA62924AB
    unsigned char std_signature_s_sha256[] = {
        0xB7,
        0xB3,
        0x20,
        0xC9,
        0xF2,
        0x83,
        0xF7,
        0x6B,
        0xD6,
        0xF3,
        0xCD,
        0x09,
        0xCF,
        0x0B,
        0x88,
        0xA1,
        0xEB,
        0x98,
        0xB4,
        0x26,
        0xC7,
        0x9F,
        0x24,
        0x40,
        0x17,
        0x57,
        0x3B,
        0x27,
        0xF7,
        0xA0,
        0x27,
        0xD3,
        0x40,
        0x9D,
        0x5E,
        0x94,
        0x3C,
        0x17,
        0xEB,
        0x41,
        0x28,
        0xD9,
        0xF1,
        0x4D,
        0x93,
        0x9B,
        0x33,
        0x1D,
        0xFF,
        0xF7,
        0xD6,
        0x45,
        0xC4,
        0xEF,
        0x2F,
        0xED,
        0xBC,
        0xCA,
        0xEF,
        0x1D,
        0x7C,
        0x4C,
        0x37,
        0x28,
        0x4E,
        0x6D,
        0x8E,
        0x36,
        0x63,
        0xEC,
        0x82,
        0xC4,
        0xD1,
        0xFE,
        0xE4,
        0xC6,
        0xF4,
        0x69,
        0x38,
        0xD2,
        0x5B,
        0x71,
        0xC8,
        0xC6,
        0x70,
        0xEB,
        0x79,
        0xEB,
        0xD4,
        0x59,
        0xB6,
        0xE1,
        0xD5,
        0xC7,
        0xC2,
        0x0F,
        0x1E,
        0x67,
        0x26,
        0x92,
        0x63,
        0xEF,
        0xF3,
        0xE6,
        0x98,
        0x8F,
        0xF5,
        0xF9,
        0x99,
        0xF2,
        0xDC,
        0x68,
        0x26,
        0x8F,
        0x82,
        0xAA,
        0x74,
        0xBD,
        0xAE,
        0xB2,
        0xA3,
        0x9D,
        0x62,
        0x2F,
        0xA6,
        0x29,
        0x24,
        0xAB,
    };

    /********************* standard data test(E-384bits) **********************/
    //signature s:
    //0x48716BB659E82D2CA7B93942FA737EA4C606B175459173E0AC93609B49E4CCE3AC89241A0AAD74A85F5646EED7128234AB1D7FF76405122813B80F552B765668
    //0xAB88C1DC4A5457ADC617719E8A5AE3FE561A347B4F849DD9E599F870448FB347C478CFE9BD2F567437C7EDC3B82D5281309C94A65E5BA508F9DA5BD4D84ED7BE
    unsigned char std_signature_s_sha384[] = {
        0x48,
        0x71,
        0x6B,
        0xB6,
        0x59,
        0xE8,
        0x2D,
        0x2C,
        0xA7,
        0xB9,
        0x39,
        0x42,
        0xFA,
        0x73,
        0x7E,
        0xA4,
        0xC6,
        0x06,
        0xB1,
        0x75,
        0x45,
        0x91,
        0x73,
        0xE0,
        0xAC,
        0x93,
        0x60,
        0x9B,
        0x49,
        0xE4,
        0xCC,
        0xE3,
        0xAC,
        0x89,
        0x24,
        0x1A,
        0x0A,
        0xAD,
        0x74,
        0xA8,
        0x5F,
        0x56,
        0x46,
        0xEE,
        0xD7,
        0x12,
        0x82,
        0x34,
        0xAB,
        0x1D,
        0x7F,
        0xF7,
        0x64,
        0x05,
        0x12,
        0x28,
        0x13,
        0xB8,
        0x0F,
        0x55,
        0x2B,
        0x76,
        0x56,
        0x68,
        0xAB,
        0x88,
        0xC1,
        0xDC,
        0x4A,
        0x54,
        0x57,
        0xAD,
        0xC6,
        0x17,
        0x71,
        0x9E,
        0x8A,
        0x5A,
        0xE3,
        0xFE,
        0x56,
        0x1A,
        0x34,
        0x7B,
        0x4F,
        0x84,
        0x9D,
        0xD9,
        0xE5,
        0x99,
        0xF8,
        0x70,
        0x44,
        0x8F,
        0xB3,
        0x47,
        0xC4,
        0x78,
        0xCF,
        0xE9,
        0xBD,
        0x2F,
        0x56,
        0x74,
        0x37,
        0xC7,
        0xED,
        0xC3,
        0xB8,
        0x2D,
        0x52,
        0x81,
        0x30,
        0x9C,
        0x94,
        0xA6,
        0x5E,
        0x5B,
        0xA5,
        0x08,
        0xF9,
        0xDA,
        0x5B,
        0xD4,
        0xD8,
        0x4E,
        0xD7,
        0xBE,
    };

    /********************* standard data test(E-512bits) **********************/
    //signature s:
    //0x5BBE2C7AE24A5B6DC44F773711F362B86A6C958A774D27F8953A65D9F3D6055ADD7CA8128E3E62BACE0218EAA98D01D1AAB8009D2AA975CD162FB1BF43168005
    //0xAE95B3B9C569899B202649F080FA8AB7E0295875D125C8871EA481203DB14D3840EF8C967CD73DA92A3AEE42F82AFF25FED47C9392C3A5082535530BF5A55611
    unsigned char std_signature_s_sha512[] = {
        0x5B,
        0xBE,
        0x2C,
        0x7A,
        0xE2,
        0x4A,
        0x5B,
        0x6D,
        0xC4,
        0x4F,
        0x77,
        0x37,
        0x11,
        0xF3,
        0x62,
        0xB8,
        0x6A,
        0x6C,
        0x95,
        0x8A,
        0x77,
        0x4D,
        0x27,
        0xF8,
        0x95,
        0x3A,
        0x65,
        0xD9,
        0xF3,
        0xD6,
        0x05,
        0x5A,
        0xDD,
        0x7C,
        0xA8,
        0x12,
        0x8E,
        0x3E,
        0x62,
        0xBA,
        0xCE,
        0x02,
        0x18,
        0xEA,
        0xA9,
        0x8D,
        0x01,
        0xD1,
        0xAA,
        0xB8,
        0x00,
        0x9D,
        0x2A,
        0xA9,
        0x75,
        0xCD,
        0x16,
        0x2F,
        0xB1,
        0xBF,
        0x43,
        0x16,
        0x80,
        0x05,
        0xAE,
        0x95,
        0xB3,
        0xB9,
        0xC5,
        0x69,
        0x89,
        0x9B,
        0x20,
        0x26,
        0x49,
        0xF0,
        0x80,
        0xFA,
        0x8A,
        0xB7,
        0xE0,
        0x29,
        0x58,
        0x75,
        0xD1,
        0x25,
        0xC8,
        0x87,
        0x1E,
        0xA4,
        0x81,
        0x20,
        0x3D,
        0xB1,
        0x4D,
        0x38,
        0x40,
        0xEF,
        0x8C,
        0x96,
        0x7C,
        0xD7,
        0x3D,
        0xA9,
        0x2A,
        0x3A,
        0xEE,
        0x42,
        0xF8,
        0x2A,
        0xFF,
        0x25,
        0xFE,
        0xD4,
        0x7C,
        0x93,
        0x92,
        0xC3,
        0xA5,
        0x08,
        0x25,
        0x35,
        0x53,
        0x0B,
        0xF5,
        0xA5,
        0x56,
        0x11,
    };

    /********************* standard data test(E-544bits) **********************/
    //signature s:
    //0xEDF0D6FE52B1984CD6CDB80EF5A2AB0C7B034EF5B00AC22ADF4CA8982B6824A06E2BDA75A1F04AEF2F773C83EAD9E92B03A2FF8D0AC8946D133D713F625348F0
    //0x772BD4C46E5EB27EEC7EE206B0F767354E85C8ED0ED2A05DBD68C114C2808FBCD7B2B7E24A9055B9AA43FCFE1EA8352F4D24886154DDDEB23605F8D68B9DC083
    unsigned char std_signature_s_544[] = {
        0xED,
        0xF0,
        0xD6,
        0xFE,
        0x52,
        0xB1,
        0x98,
        0x4C,
        0xD6,
        0xCD,
        0xB8,
        0x0E,
        0xF5,
        0xA2,
        0xAB,
        0x0C,
        0x7B,
        0x03,
        0x4E,
        0xF5,
        0xB0,
        0x0A,
        0xC2,
        0x2A,
        0xDF,
        0x4C,
        0xA8,
        0x98,
        0x2B,
        0x68,
        0x24,
        0xA0,
        0x6E,
        0x2B,
        0xDA,
        0x75,
        0xA1,
        0xF0,
        0x4A,
        0xEF,
        0x2F,
        0x77,
        0x3C,
        0x83,
        0xEA,
        0xD9,
        0xE9,
        0x2B,
        0x03,
        0xA2,
        0xFF,
        0x8D,
        0x0A,
        0xC8,
        0x94,
        0x6D,
        0x13,
        0x3D,
        0x71,
        0x3F,
        0x62,
        0x53,
        0x48,
        0xF0,
        0x77,
        0x2B,
        0xD4,
        0xC4,
        0x6E,
        0x5E,
        0xB2,
        0x7E,
        0xEC,
        0x7E,
        0xE2,
        0x06,
        0xB0,
        0xF7,
        0x67,
        0x35,
        0x4E,
        0x85,
        0xC8,
        0xED,
        0x0E,
        0xD2,
        0xA0,
        0x5D,
        0xBD,
        0x68,
        0xC1,
        0x14,
        0xC2,
        0x80,
        0x8F,
        0xBC,
        0xD7,
        0xB2,
        0xB7,
        0xE2,
        0x4A,
        0x90,
        0x55,
        0xB9,
        0xAA,
        0x43,
        0xFC,
        0xFE,
        0x1E,
        0xA8,
        0x35,
        0x2F,
        0x4D,
        0x24,
        0x88,
        0x61,
        0x54,
        0xDD,
        0xDE,
        0xB2,
        0x36,
        0x05,
        0xF8,
        0xD6,
        0x8B,
        0x9D,
        0xC0,
        0x83,
    };

    ecdsa_test_vector_t vector[1];

    eccp_curve_t *curve      = (eccp_curve_t *)anders_1024_1;
    char         *curve_name = "anders_1024_1";

    vector->rand_k                 = rand_k;
    vector->priKey                 = priKey;
    vector->pubKey                 = pubKey;
    vector->std_signature_r        = std_signature_r;
    vector->std_E_md5              = std_E_md5;
    vector->std_signature_s_md5    = std_signature_s_md5;
    vector->std_E_sha1             = std_E_sha1;
    vector->std_signature_s_sha1   = std_signature_s_sha1;
    vector->std_E_192              = std_E_192;
    vector->std_signature_s_192    = std_signature_s_192;
    vector->std_E_sha224           = std_E_sha224;
    vector->std_signature_s_sha224 = std_signature_s_sha224;
    vector->std_E_sha256           = std_E_sha256;
    vector->std_signature_s_sha256 = std_signature_s_sha256;
    vector->std_E_sha384           = std_E_sha384;
    vector->std_signature_s_sha384 = std_signature_s_sha384;
    vector->std_E_sha512           = std_E_sha512;
    vector->std_signature_s_sha512 = std_signature_s_sha512;
    vector->std_E_544              = std_E_544;
    vector->std_signature_s_544    = std_signature_s_544;
    vector->std_signature_s_zero   = std_signature_s_zero;
    vector->std_signature_s_1      = std_signature_s_1;
    vector->std_signature_s_FF     = std_signature_s_FF;

    return ecdsa_std_sign_verify_test(curve, curve_name, vector);
}
    #endif


unsigned int ecdsa_corner_case_test(eccp_curve_t *curve, char *curve_name)
{
    unsigned char k[ECCP_MAX_BYTE_LEN];
    unsigned char priKey[ECCP_MAX_BYTE_LEN];
    unsigned char pubKey[2 * ECCP_MAX_BYTE_LEN];

    unsigned char e_0[ECCP_MAX_BYTE_LEN];
    unsigned char e_n[ECCP_MAX_BYTE_LEN];
    unsigned char e_r[ECCP_MAX_BYTE_LEN];
    unsigned char e_m_r[ECCP_MAX_BYTE_LEN];

    unsigned int i, m, nByteLen; //, nWordLen;
    unsigned int ret;

    nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);
    //nWordLen = GET_WORD_LEN(curve->eccp_n_bitLen);

    printf("\r\n\r\n -------------- %s ECDSA sign & verify corner test -------------- ", curve_name);

    //e_0 = 0
    memset_(e_0, 0, nByteLen);

    //e_n = n
    reverse_byte_array((unsigned char *)curve->eccp_n, e_n, nByteLen);
    m = (curve->eccp_n_bitLen) & 7;
    if (0u != m) {
        uint8_Big_Multiple2n(e_n, nByteLen, 8u - m);
    }

    //get k, e_r = r = (x coordinate of [k]G or [k](-G)) mod n, and e_m_r = -r mod n
    ret = ecdsa_test_get_r_by_k((eccp_curve_t *)curve, NULL, k, e_r, NULL, e_m_r, NULL);
    if (0 != ret) {
        return 1;
    }

    for (i = 0; i < 2; i++) {
        if (0 == i) //key pair is (1, [1]G)
        {
            printf("\r\n corner case test: key pair is (1, [1]G))");
            memset_(priKey, 0, nByteLen);
            priKey[nByteLen - 1] = 0x01;
            ret                  = eccp_get_pubkey_from_prikey((eccp_curve_t *)curve, priKey, pubKey);
        } else if (1 == i) //key pair is (n-1, [n-1]G)
        {
            printf("\r\n corner case test: key pair is (n-1, [n-1]G)");
            reverse_byte_array((unsigned char *)curve->eccp_n, priKey, nByteLen);
            priKey[nByteLen - 1] -= 0x01;
            ret = eccp_get_pubkey_from_prikey((eccp_curve_t *)curve, priKey, pubKey);
        }
        if (PKE_SUCCESS != ret) {
            printf("\r\n %s ECDSA eccp_get_pubkey_from_prikey error, ret = %02x", curve_name, ret);
            return 1;
        }

        //E = 0
        if (ecdsa_std_sign_verify_test_internal((eccp_curve_t *)curve, curve_name, e_0, nByteLen, k, priKey, pubKey, NULL, NULL, ECDSA_SUCCESS, "corner case test(E = 0)")) {
            return 1;
        }

        //E = n
        if (ecdsa_std_sign_verify_test_internal((eccp_curve_t *)curve, curve_name, e_n, nByteLen, k, priKey, pubKey, NULL, NULL, ECDSA_SUCCESS, "corner case test(E = n)")) {
            return 1;
        }

        //E = r mod n
        //s = k^(-1)(e+r*dA) mod n
        //[k]G = [e*s^(-1)]G + [r*s^(-1)]G
        if (0 == i)        //key pair is (1, [1]G)
        {
            ret = ECDSA_SUCCESS;
        } else if (1 == i) //key pair is (n-1, [n-1]G)
        {
            ret = ECDSA_ZERO_ALL;
        }

        if (ecdsa_std_sign_verify_test_internal((eccp_curve_t *)curve, curve_name, e_r, nByteLen, k, priKey, pubKey, NULL, NULL, ret, "corner case test(E = r)")) {
            return 1;
        }

        //E = -r mod n
        //s = k^(-1)(e+r*dA) mod n
        //[k]G = [e*s^(-1)]G + [r*s^(-1)]G
        if (0 == i)        //key pair is (1, [1]G)
        {
            ret = ECDSA_ZERO_ALL;
        } else if (1 == i) //key pair is (n-1, [n-1]G)
        {
            ret = ECDSA_SUCCESS;
        }

        if (ecdsa_std_sign_verify_test_internal((eccp_curve_t *)curve, curve_name, e_m_r, nByteLen, k, priKey, pubKey, NULL, NULL, ret, "corner case test(E = -r)")) {
            return 1;
        }
    }

    return 0;
}

unsigned int ecdsa_rand_test(eccp_curve_t *curve, char *curve_name)
{
    unsigned char  priKey[ECCP_MAX_BYTE_LEN];
    unsigned char  pubKey[2 * ECCP_MAX_BYTE_LEN];
    unsigned char  rand_k[ECCP_MAX_BYTE_LEN];
    unsigned char *k;
    unsigned char  E[2 * ECCP_MAX_BYTE_LEN];
    unsigned char  signature[2 * ECCP_MAX_BYTE_LEN];
    unsigned int   i, j, EByteLen, pByteLen, nByteLen, signatureByteLen;
    unsigned int   ret;

    pByteLen         = GET_BYTE_LEN(curve->eccp_p_bitLen);
    nByteLen         = GET_BYTE_LEN(curve->eccp_n_bitLen);
    signatureByteLen = nByteLen * 2;

    printf("\r\n\r\n -------------- %s ECDSA rand test --------------", curve_name);

    /****************************************
    //s = k^(-1)(e+r*dA) mod n
    //[k]G = [e*s^(-1)]G + [r*s^(-1)]G
    i=0: key pair is (1, G), e = 0 mod n, to check [0]G + [r*s^(-1)]G
    i=1: key pair is (1, G), k is random but fixed, e = r mod n, to check [e*s^(-1)]G + [r*s^(-1)]G
    i=2: key pair is (1, G), e and k are random.
    i=3: key pair is (n-1, [n-1]G = -G), e = 0 mod n, to check [0]G + [r*s^(-1)](-G)
    i=4: key pair is (n-1, [n-1]G = -G), k is random but fixed, e = -r mod n, to check [e*s^(-1)]G + [r*s^(-1)](-G)
    i=5: key pair is (n-1, [n-1]G = -G), e and k are random
    i=6: all random
    i=7: all random
    *****************************************/
    for (i = 0; i < ECDSA_SIGN_VERIFY_ROUND1; i++) {
        ret = get_rand(signature, 4);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error, ret = %02x", ret);
            return 1;
        }

        //random E of random length
        EByteLen = signature[0] % (sizeof(E)) + 1;
        ret      = get_rand(E, EByteLen);
        if (TRNG_SUCCESS != ret) {
            printf("\r\n get rand error, ret = %02x", ret);
            return 1;
        }

        //internal k
        if ((signature[1] & 1) || (1 == i) || (4 == i)) {
            k   = rand_k;
            ret = get_rand(k, nByteLen);
            if (TRNG_SUCCESS != ret) {
                printf("\r\n get rand error, ret = %02x", ret);
                return 1;
            }
            k[0] = 0; //make sure k < n
        } else {
            k = NULL;
        }

        //set key pair
        if (i <= 2) //corner case 1/2/3: key pair is (1, G)
        {
            if (0 == i) {
                //corner case 1: set e = 0 mod n, to check [0]G + [r*s^(-1)]G
                memset_(E, 0, 32);
                EByteLen = 32;
            } else if (1 == i) {
                //corner case 2: set e = r mod n, to check [e*s^(-1)]G + [r*s^(-1)]G
                ret = ecdsa_test_get_r_by_k((eccp_curve_t *)curve, k, k, E, NULL, NULL, NULL);
                if (0 != ret) {
                    return 1;
                }
            } else //corner case 3
            {
                ;
            }

            memset_(priKey, 0, nByteLen);
            priKey[nByteLen - 1] = 0x01;
            ret                  = eccp_get_pubkey_from_prikey((eccp_curve_t *)curve, priKey, pubKey);
        } else if (i <= 5) //corner case 4/5/6: key pair is (n-1, [n-1]G)
        {
            if (3 == i) {
                //corner case 4: set e = 0 mod n, to check [0]G + [r*s^(-1)](-G)
                memset_(E, 0, 32);
                EByteLen = 32;
            } else if (4 == i) {
                //corner case 5: set e = -r mod n, to check [e*s^(-1)]G + [r*s^(-1)](-G)
                ret = ecdsa_test_get_r_by_k((eccp_curve_t *)curve, k, k, NULL, NULL, E, NULL);
                if (0 != ret) {
                    return 1;
                }
            } else //corner case 6
            {
                ;
            }

            reverse_byte_array((unsigned char *)curve->eccp_n, priKey, nByteLen);
            priKey[nByteLen - 1] -= 0x01;
            ret = eccp_get_pubkey_from_prikey((eccp_curve_t *)curve, priKey, pubKey);
        } else //key pair is random
        {
            ret = eccp_getkey((eccp_curve_t *)curve, priKey, pubKey);
        }
        if (PKE_SUCCESS != ret) {
            printf("\r\n %s ECDSA get key error, ret = %02x", curve_name, ret);
            return 1;
        }

        for (j = 0; j < ECDSA_SIGN_VERIFY_ROUND2; j++) {
            printf("\r\n %s ECDSA round1=%u, round2=%u", curve_name, i + 1, j + 1);

            ret = ecdsa_sign((eccp_curve_t *)curve, E, EByteLen, k, priKey, signature);
            if (ECDSA_SUCCESS != ret) {
                printf("\r\n %s ECDSA sign error, ret = %02x", curve_name, ret);
                print_buf_U8(priKey, nByteLen, "prikey");
                print_buf_U8(pubKey, pByteLen * 2, "pubkey");
                if (k) {
                    print_buf_U8(k, nByteLen, "k");
                }
                print_buf_U8(E, EByteLen, "E");
                print_buf_U8(signature, signatureByteLen, "signature");
                return 1;
            }

            ret = ecdsa_verify((eccp_curve_t *)curve, E, EByteLen, pubKey, signature);
            if (ECDSA_SUCCESS != ret) {
                printf("\r\n %s ECDSA verify error, ret = %02x", curve_name, ret);
                print_buf_U8(priKey, nByteLen, "prikey");
                print_buf_U8(pubKey, pByteLen * 2, "pubkey");
                if (k) {
                    print_buf_U8(k, nByteLen, "k");
                }
                print_buf_U8(E, EByteLen, "E");
                print_buf_U8(signature, signatureByteLen, "signature");
                return 1;
            }
        }
    }

    return 0;
}

unsigned int ecdsa_speed_test(eccp_curve_t *curve, char *curve_name)
{
    unsigned char priKey[ECCP_MAX_BYTE_LEN];
    unsigned char pubKey[2 * ECCP_MAX_BYTE_LEN];
    unsigned char E[ECCP_MAX_BYTE_LEN];
    unsigned char signature[2 * ECCP_MAX_BYTE_LEN];
    unsigned int  i, EByteLen, pByteLen, nByteLen, signatureByteLen;
    unsigned int  round;
    unsigned int  ret;

    printf("\r\n\r\n *************************** %s *************************** \r\n", curve_name);

    pByteLen         = (curve->eccp_p_bitLen + 7) / 8;
    nByteLen         = (curve->eccp_n_bitLen + 7) / 8;
    signatureByteLen = nByteLen * 2;
    EByteLen         = 32;

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

    uint32_sleep(0x1FFFF, 1);

    #if 0
    //get random E
    ret = get_rand(E, EByteLen);
    if(TRNG_SUCCESS != ret)
    {
        printf("\r\n get rand error, ret = %02x", ret);
        return 1;
    }
    #else
    memset_(E, 0x5a, EByteLen);
    #endif


    //test eccp_getkey
    ret = 0;
    printf("\r\n ======== eccp_getkey begin ======== ");
    fflush(stdout);

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    round /= 10;
    startP();
    #endif

    for (i = 0; i < round; i++) {
        ret |= eccp_getkey(curve, priKey, pubKey);
    }

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n finished");
    fflush(stdout);
    #endif

    if (PKE_SUCCESS != ret) {
        printf("\r\n ECDSA get key error, ret = %02x", ret);
        print_buf_U8(priKey, nByteLen, "prikey");
        print_buf_U8(pubKey, 2 * pByteLen, "pubkey");
        return 1;
    }


    //test ecdsa_sign
    ret = 0;
    printf("\r\n ======== ecdsa_sign begin ======== ");
    fflush(stdout);

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    startP();
    #endif

    for (i = 0; i < round; i++) {
        ret |= ecdsa_sign(curve, E, EByteLen, NULL, priKey, signature);
    }

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n finished");
    fflush(stdout);
    #endif

    if (ECDSA_SUCCESS != ret) {
        printf("\r\n ecdsa_sign error, ret = %02x", ret);
        print_buf_U8(E, EByteLen, "E");
        print_buf_U8(signature, signatureByteLen, "signature");
        return 1;
    }


    //test ecdsa_verify
    ret = 0;
    printf("\r\n ======== ecdsa_verify begin ======== ");
    fflush(stdout);

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    startP();
    #endif

    for (i = 0; i < round; i++) {
        ret |= ecdsa_verify(curve, E, EByteLen, pubKey, signature);
    }

    #ifdef ECDSA_SPEED_TEST_BY_TIMER
    endP(1, 0, round);
    #else
    printf("\r\n finished");
    fflush(stdout);
    #endif

    if (ECDSA_SUCCESS != ret) {
        printf("\r\n ecdsa_verify error, ret = %02x", ret);
        return 1;
    }

    return 0;
}


    #ifdef TRNG_POKER_TEST
unsigned int ecdsa_rng_test(void)
{
    unsigned char priKey[ECCP_MAX_BYTE_LEN];
    unsigned char pubKey[2 * ECCP_MAX_BYTE_LEN + 1];
    unsigned char signature[2 * ECCP_MAX_BYTE_LEN];
    unsigned char E[256];
    unsigned int  EByteLen;
    unsigned int  i, modulus = 5;
    eccp_curve_t *curve = NULL;
    unsigned int  ret   = 0;

        #if (ECCP_MAX_BIT_LEN >= 521)
    modulus = 6;
        #endif

    for (i = 0; i < 3000; i++) {
        switch (priKey[3] % modulus) {
        case 0:
            curve = (eccp_curve_t *)brainpoolp160r1;
            break;

        case 1:
            curve = (eccp_curve_t *)secp192r1;
            break;

        case 2:
            curve = (eccp_curve_t *)secp256r1;
            break;

        case 3:
            curve = (eccp_curve_t *)secp384r1;
            break;

        case 4:
            curve = (eccp_curve_t *)brainpoolp512r1;
            break;

        case 5:
            curve = (eccp_curve_t *)secp521r1;
            break;

        default:
            curve = (eccp_curve_t *)brainpoolp160r1;
            break;
        }

        //get key
        ret = eccp_getkey(curve, priKey, pubKey);
        if (PKE_SUCCESS != ret) {
            printf("\r\n ECDSA get key error, ret = %02x", ret);
            return 1;
        }

        //sign & verify
        EByteLen = priKey[4];
        if (0 == EByteLen) {
            EByteLen += 1;
        }
        ret = ecdsa_sign(curve, E, EByteLen, NULL, priKey, signature);
        if (ECDSA_SUCCESS != ret) {
            printf("\r\n ECDSA sign error, ret = %02x", ret);
            print_buf_U8(E, EByteLen, "E");
            print_buf_U8(signature, 2 * GET_BYTE_LEN(curve->eccp_n_bitLen), "signature");
            return 1;
        }
        ret = ecdsa_verify(curve, E, EByteLen, pubKey, signature);
        if (ECDSA_SUCCESS != ret) {
            printf("\r\n ECDSA verify error, ret = %02x", ret);
            return 1;
        }
    }

    return 0;
}
    #endif

unsigned int ecdsa_speed_all_test(void)
{
    /**/
    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecdsa_speed_test((eccp_curve_t *)secp160k1, "secp160k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecdsa_speed_test((eccp_curve_t *)secp192k1, "secp192k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecdsa_speed_test((eccp_curve_t *)secp224k1, "secp224k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecdsa_speed_test((eccp_curve_t *)secp256k1, "secp256k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp160r1, "secp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecdsa_speed_test((eccp_curve_t *)secp160r2, "secp160r2")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp192r1, "secp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp224r1, "secp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp256r1, "secp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp384r1, "secp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecdsa_speed_test((eccp_curve_t *)secp521r1, "secp521r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp160r1, "brainpoolp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_BRAINPOOLP192R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp192r1, "brainpoolp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_BRAINPOOLP224R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp224r1, "brainpoolp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp256r1, "brainpoolp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 320) && defined(SUPPORT_BRAINPOOLP320R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp320r1, "brainpoolp320r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_BRAINPOOLP384R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp384r1, "brainpoolp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecdsa_speed_test((eccp_curve_t *)brainpoolp512r1, "brainpoolp512r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BN256))
    if (ecdsa_speed_test((eccp_curve_t *)bn256, "bn256")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 638) && defined(SUPPORT_BN638))
    if (ecdsa_speed_test((eccp_curve_t *)bn638, "bn638")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecdsa_speed_test((eccp_curve_t *)anders_1024_1, "anders_1024_1")) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int ecdsa_standard_data_all_test(void)
{
    /**/
    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecdsa_std_test_secp160k1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecdsa_std_test_secp192k1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecdsa_std_test_secp224k1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecdsa_std_test_secp256k1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecdsa_std_test_secp160r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecdsa_std_test_secp160r2()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecdsa_std_test_secp192r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecdsa_std_test_secp224r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecdsa_std_test_secp256r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecdsa_std_test_secp384r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecdsa_std_test_secp521r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecdsa_std_test_brainpoolp160r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecdsa_std_test_brainpoolp256r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecdsa_std_test_brainpoolp512r1()) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecdsa_std_test_anders_1024_1()) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int ecdsa_corner_case_all_test(void)
{
    /**/
    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecdsa_corner_case_test(secp160k1, "secp160k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecdsa_corner_case_test(secp192k1, "secp192k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecdsa_corner_case_test(secp224k1, "secp224k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecdsa_corner_case_test(secp256k1, "secp256k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecdsa_corner_case_test(secp160r1, "secp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecdsa_corner_case_test(secp160r2, "secp160r2")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecdsa_corner_case_test(secp192r1, "secp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecdsa_corner_case_test(secp224r1, "secp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecdsa_corner_case_test(secp256r1, "secp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecdsa_corner_case_test(secp384r1, "secp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecdsa_corner_case_test(secp521r1, "secp521r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecdsa_corner_case_test(brainpoolp160r1, "brainpoolp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_BRAINPOOLP192R1))
    if (ecdsa_corner_case_test(brainpoolp192r1, "brainpoolp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_BRAINPOOLP224R1))
    if (ecdsa_corner_case_test(brainpoolp224r1, "brainpoolp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecdsa_corner_case_test(brainpoolp256r1, "brainpoolp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 320) && defined(SUPPORT_BRAINPOOLP320R1))
    if (ecdsa_corner_case_test(brainpoolp320r1, "brainpoolp320r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_BRAINPOOLP384R1))
    if (ecdsa_corner_case_test(brainpoolp384r1, "brainpoolp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecdsa_corner_case_test(brainpoolp512r1, "brainpoolp512r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BN256))
    if (ecdsa_corner_case_test(bn256, "bn256")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 638) && defined(SUPPORT_BN638))
    if (ecdsa_corner_case_test(bn638, "bn638")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecdsa_corner_case_test((eccp_curve_t *)anders_1024_1, "anders_1024_1")) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int ecdsa_rand_all_test(void)
{
    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160K1))
    if (ecdsa_rand_test(secp160k1, "secp160k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192K1))
    if (ecdsa_rand_test(secp192k1, "secp192k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224K1))
    if (ecdsa_rand_test(secp224k1, "secp224k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256K1))
    if (ecdsa_rand_test(secp256k1, "secp256k1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R1))
    if (ecdsa_rand_test(secp160r1, "secp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_SECP160R2))
    if (ecdsa_rand_test(secp160r2, "secp160r2")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_SECP192R1))
    if (ecdsa_rand_test(secp192r1, "secp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_SECP224R1))
    if (ecdsa_rand_test(secp224r1, "secp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_SECP256R1))
    if (ecdsa_rand_test(secp256r1, "secp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_SECP384R1))
    if (ecdsa_rand_test(secp384r1, "secp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 521) && defined(SUPPORT_SECP521R1))
    if (ecdsa_rand_test(secp521r1, "secp521r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 160) && defined(SUPPORT_BRAINPOOLP160R1))
    if (ecdsa_rand_test(brainpoolp160r1, "brainpoolp160r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 192) && defined(SUPPORT_BRAINPOOLP192R1))
    if (ecdsa_rand_test(brainpoolp192r1, "brainpoolp192r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 224) && defined(SUPPORT_BRAINPOOLP224R1))
    if (ecdsa_rand_test(brainpoolp224r1, "brainpoolp224r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BRAINPOOLP256R1))
    if (ecdsa_rand_test(brainpoolp256r1, "brainpoolp256r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 320) && defined(SUPPORT_BRAINPOOLP320R1))
    if (ecdsa_rand_test(brainpoolp320r1, "brainpoolp320r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 384) && defined(SUPPORT_BRAINPOOLP384R1))
    if (ecdsa_rand_test(brainpoolp384r1, "brainpoolp384r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 512) && defined(SUPPORT_BRAINPOOLP512R1))
    if (ecdsa_rand_test(brainpoolp512r1, "brainpoolp512r1")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 256) && defined(SUPPORT_BN256))
    if (ecdsa_rand_test(bn256, "bn256")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 638) && defined(SUPPORT_BN638))
    if (ecdsa_rand_test(bn638, "bn638")) {
        return 1;
    }
    #endif

    #if ((ECCP_MAX_BIT_LEN >= 1024) && defined(SUPPORT_ANDERS_1024_1))
    if (ecdsa_rand_test(anders_1024_1, "anders_1024_1")) {
        return 1;
    }
    #endif

    return 0;
}

unsigned int ECDSA_all_test(void)
{
    printf("\r\n\r\n =================== ECDSA test =================== \r\n");

    #if 0

    if(ecdsa_speed_all_test())
        return 1;

    #else

        #ifdef TRNG_POKER_TEST
    if (ecdsa_rng_test()) {
        return 1;
    }
        #endif
    /**/
    if (ecdsa_standard_data_all_test()) {
        return 1;
    }

    if (ecdsa_corner_case_all_test()) {
        return 1;
    }

    if (ecdsa_rand_all_test()) {
        return 1;
    }

    #endif

    return 0;
}

#endif

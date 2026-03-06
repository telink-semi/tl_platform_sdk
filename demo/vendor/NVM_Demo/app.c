/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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


#define NVM_OTP_WRITE           0 //The OTP can only be written once.

#define NVM_ADDR                0x010080
#define NVM_CR_OTP_ADDR         0x085080
#define NVM_CC_OTP_ADDR         0x086080

#define NVM_BUFF_LEN            256

unsigned char nvm_read_buff[NVM_BUFF_LEN]  = {0};
unsigned char nvm_write_buff[NVM_BUFF_LEN] =
{
    0x88,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
    0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
    0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,

    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
    0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,
    0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,
    0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,
    0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,

    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
    0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
    0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,
    0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
    0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
    0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,

    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
    0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
    0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
    0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
    0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
    0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
    0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
    0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
};

unsigned int nvm_read_buff4[NVM_BUFF_LEN / 4]  = {0};
unsigned int nvm_write_buff4[NVM_BUFF_LEN / 4] =
{
    0x70010203,0x04050607,0x08090a0b,0x0c0d0e0f,
    0x10111213,0x14151617,0x18191a1b,0x1c1d1e1f,
    0x20212223,0x24252627,0x28292a2b,0x2c2d2e2f,
    0x30313233,0x34353637,0x38393a3b,0x3c3d3e3f,

    0x40414243,0x44454647,0x48494a4b,0x4c4d4e4f,
    0x50515253,0x54555657,0x58595a5b,0x5c5d5e5f,
    0x60616263,0x64656667,0x68696a6b,0x6c6d6e6f,
    0x70717273,0x74757677,0x78797a7b,0x7c7d7e7f,

    0x80818283,0x84858687,0x88898a8b,0x8c8d8e8f,
    0x90919293,0x94959697,0x98999a9b,0x9c9d9e9f,
    0xa0a1a2a3,0xa4a5a6a7,0xa8a9aaab,0xacadaeaf,
    0xb0b1b2b3,0xb4b5b6b7,0xb8b9babb,0xbcbdbebf,

    0xc0c1c2c3,0xc4c5c6c7,0xc8c9cacb,0xcccdcecf,
    0xd0d1d2d3,0xd4d5d6d7,0xd8d9dadb,0xdcdddedf,
    0xe0e1e2e3,0xe4e5e6e7,0xe8e9eaeb,0xecedeeef,
    0xf0f1f2f3,0xf4f5f6f7,0xf8f9fafb,0xfcfdfeff,
};

typedef struct
{
    unsigned char reg_write_err                : 1;
    unsigned char ahb_read_word_err            : 1;
    unsigned char ahb_read_byte_err            : 1;
    unsigned char ahb_bypass_cache_read_err    : 1;
    unsigned char cr_otp_err                   : 1;
    unsigned char cr_ahb_read_err              : 1;
    unsigned char cr_ahb_bypass_cache_read_err : 1;
    unsigned char cc_otp_err                   : 1;
    unsigned char cc_ahb_read_err              : 1;
    unsigned char cc_ahb_bypass_cache_read_err : 1;
} err_status_t;
volatile err_status_t    err_status;

typedef struct
{
    unsigned char reg_write_check                : 1;
    unsigned char ahb_read_word_check            : 1;
    unsigned char ahb_read_byte_check            : 1;
    unsigned char ahb_bypass_cache_read_check    : 1;
    unsigned char cr_otp_check                   : 1;
    unsigned char cr_ahb_read_check              : 1;
    unsigned char cr_ahb_bypass_cache_read_check : 1;
    unsigned char cc_otp_check                   : 1;
    unsigned char cc_ahb_read_check              : 1;
    unsigned char cc_ahb_bypass_cache_read_check : 1;
} check_status_t;
volatile check_status_t  check_status;


unsigned char nvm_compare(unsigned int *a, unsigned int *b, unsigned char len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (a[i] != b[i])
        {
            return 1;
        }
    }
    return 0;
}

void nvm_reg_wr(void)
{
    int i;

    while (reg_nvm_state & BIT(1))
    {
    }

    nvm_reg_write(NVM_ADDR, NVM_BUFF_LEN, nvm_write_buff4);
    nvm_reg_read(NVM_ADDR, NVM_BUFF_LEN, nvm_read_buff4);
    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        if (nvm_read_buff4[i] != nvm_write_buff4[i])
        {
            err_status.reg_write_err = 1;
            while(1)
            {
            }
        }
    }
    check_status.reg_write_check = 1;

#if NVM_OTP_WRITE
    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }
    for (i = 0; i < NVM_BUFF_LEN / 16; i++)
    {
        nvm_reg_write(NVM_CR_OTP_ADDR + i * 16, 16, &nvm_write_buff4[i * 4]);
    }
    nvm_reg_read(NVM_CR_OTP_ADDR, NVM_BUFF_LEN, nvm_read_buff4);
    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        if (nvm_read_buff4[i] != nvm_write_buff4[i])
        {
            err_status.cr_otp_err = 1;
            while(1)
            {
            }
        }
    }
    check_status.cr_otp_check = 1;

    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }
    for (i = 0; i < NVM_BUFF_LEN / 32; i++)
    {
        nvm_reg_write(NVM_CC_OTP_ADDR + i * 16, 16, &nvm_write_buff4[i * 4]);
    }
    nvm_reg_read(NVM_CC_OTP_ADDR, NVM_BUFF_LEN / 2, nvm_read_buff4);
    for (i = 0; i < NVM_BUFF_LEN / 8; i++)
    {
        if (nvm_read_buff4[i] != nvm_write_buff4[i])
        {
            err_status.cc_otp_err = 1;
            while(1)
            {
            }
        }
    }
    check_status.cc_otp_check = 1;
#endif
}

void nvm_ahb_read(void)
{
    int i;

    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }

    nvm_ahb0_read_word(NVM_ADDR, NVM_BUFF_LEN, nvm_read_buff4);

    if (nvm_compare(nvm_read_buff4, nvm_write_buff4, NVM_BUFF_LEN / 4))
    {
        err_status.ahb_read_word_err = 1;
        while (1)
        {
        }
    }
    check_status.ahb_read_word_check = 1;

    for (i = 0; i < NVM_BUFF_LEN; i++)
    {
        nvm_read_buff[i] = 0x00;
    }
    nvm_ahb0_read_byte(NVM_ADDR, 1, nvm_read_buff);
    nvm_ahb0_read_byte(NVM_ADDR + 1, NVM_BUFF_LEN - 1, &nvm_read_buff[1]);
    if (nvm_compare((unsigned int *)nvm_read_buff, nvm_write_buff4, NVM_BUFF_LEN / 4))
    {
        err_status.ahb_read_byte_err = 1;
        while (1)
        {
        }
    }
    check_status.ahb_read_byte_check = 1;

    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }
    nvm_reg_bypass_cache();
    nvm_ahb0_read_word(NVM_ADDR, NVM_BUFF_LEN, nvm_read_buff4);
    if (nvm_compare(nvm_read_buff4, nvm_write_buff4, NVM_BUFF_LEN / 4))
    {
        err_status.ahb_bypass_cache_read_err = 1;
        while(1)
        {
        }
    }
    check_status.ahb_bypass_cache_read_check = 1;

#if NVM_OTP_WRITE
    for (i = 0; i < NVM_BUFF_LEN; i++)
    {
        nvm_read_buff[i] = 0x00000000;
    }
    nvm_ahb0_read_byte(NVM_CR_OTP_ADDR, 1, nvm_read_buff);
    nvm_ahb0_read_byte(NVM_CR_OTP_ADDR + 1, NVM_BUFF_LEN - 1, &nvm_read_buff[1]);
    if (nvm_compare((unsigned int *)nvm_read_buff, nvm_write_buff4, NVM_BUFF_LEN / 4))
    {
        err_status.cr_ahb_read_err = 1;
        while(1)
        {
        }
    }
    check_status.cr_ahb_read_check = 1;

    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }
    nvm_reg_bypass_cache();
    nvm_ahb0_read_word(NVM_CR_OTP_ADDR, NVM_BUFF_LEN, nvm_read_buff4);
    if (nvm_compare(nvm_read_buff4, nvm_write_buff4, NVM_BUFF_LEN / 4))
    {
        err_status.cr_ahb_bypass_cache_read_err = 1;
        while(1)
        {
        }
    }
    check_status.cr_ahb_bypass_cache_read_check = 1;

    for (i = 0; i < NVM_BUFF_LEN; i++)
    {
        nvm_read_buff[i] = 0x00000000;
    }
    nvm_ahb0_read_byte(NVM_CC_OTP_ADDR, 1, nvm_read_buff);
    nvm_ahb0_read_byte(NVM_CC_OTP_ADDR + 1, NVM_BUFF_LEN / 2 - 1, &nvm_read_buff[1]);
    if (nvm_compare((unsigned int *)nvm_read_buff, nvm_write_buff4, NVM_BUFF_LEN / 8))
    {
        err_status.cc_ahb_read_err = 1;
        while(1)
        {
        }
    }
    check_status.cc_ahb_read_check = 1;

    for (i = 0; i < NVM_BUFF_LEN / 4; i++)
    {
        nvm_read_buff4[i] = 0x00000000;
    }
    nvm_reg_bypass_cache();
    nvm_ahb0_read_word(NVM_CC_OTP_ADDR, NVM_BUFF_LEN / 2, nvm_read_buff4);
    if (nvm_compare(nvm_read_buff4, nvm_write_buff4, NVM_BUFF_LEN / 8))
    {
        err_status.cc_ahb_bypass_cache_read_err = 1;
        while(1)
        {
        }
    }
    check_status.cc_ahb_bypass_cache_read_check = 1;
#endif
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_set_high_level(LED1);
    gpio_function_en(LED2);
    gpio_output_en(LED2);
    gpio_set_low_level(LED2);
    gpio_function_en(LED3);
    gpio_output_en(LED3);
    gpio_set_low_level(LED3);
    gpio_function_en(LED4);
    gpio_output_en(LED4);
    gpio_set_low_level(LED4);

#if N22_TEST
    sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
    sys_n22_start();
#endif

    //Two cores cannot use the REG mode to read or write the NVM simultaneously.
    nvm_reg_wr();

    nvm_ahb_read();
}

void main_loop(void)
{
    delay_ms(500);
    gpio_toggle(LED1);
}


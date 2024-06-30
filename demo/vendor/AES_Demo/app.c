/********************************************************************************************************
 * @file    app.c
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
#include "app_config.h"

#define BLOCKING_MODE   0//get encrypt/decrypt result by blocking
#define INTERRUPT_MODE  1//get encrypt/decrypt result by interrupt

#define WORK_MODE       BLOCKING_MODE

#if(AES_MODE == AES_ECB_MODE)   //Electronic Codebook mode
unsigned char sKey[16] __attribute__((aligned(4))) = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
unsigned char plaintext[16] __attribute__((aligned(4))) = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

unsigned char ciphertext[16] __attribute__((aligned(4))) = {0};
unsigned char deciphertext[16] __attribute__((aligned(4))) = {0};

unsigned char cipher[16] __attribute__((aligned(4))) = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

#elif(AES_MODE == AES_CBC_MODE) //Cipher Block Chaining mode
unsigned char encrypt_result1[16] __attribute__((aligned(4))) = {};
unsigned char encrypt_result2[16] __attribute__((aligned(4))) = {};
unsigned char decrypt_result1[16] __attribute__((aligned(4))) = {};
unsigned char decrypt_result2[16] __attribute__((aligned(4))) = {};

unsigned char temp[16] __attribute__((aligned(4))) = {};

unsigned char encrypt_std1[16] __attribute__((aligned(4))) = {0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d};
unsigned char encrypt_std2[16] __attribute__((aligned(4))) = {0x50,0x86,0xcb,0x9b,0x50,0x72,0x19,0xee,0x95,0xdb,0x11,0x3a,0x91,0x76,0x78,0xb2};

unsigned char init[16] __attribute__((aligned(4))) = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

unsigned char plaintext1[16] __attribute__((aligned(4))) = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
unsigned char plaintext2[16] __attribute__((aligned(4))) = {0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51};
unsigned char sKey[16] __attribute__((aligned(4))) = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
#endif

volatile unsigned char irq_flag = 0;

void user_init(void)
{
    /*initialize LEDs*/
    gpio_function_en(LED1 | LED2);
    gpio_output_en(LED1 | LED2);
    gpio_input_dis(LED1 | LED2);
    gpio_set_low_level(LED1 | LED2);

    gpio_function_en(LED3 | LED4);
    gpio_output_en(LED3 | LED4);
    gpio_input_dis(LED3 | LED4);
    gpio_set_low_level(LED3 | LED4);

#if(WORK_MODE == INTERRUPT_MODE)

#if defined(MCU_CORE_B91)
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_ZB_DM);
    aes_set_irq_mask(FLD_CRYPT_IRQ);
#elif defined(MCU_CORE_B92)
    core_interrupt_enable();
    plic_interrupt_enable(IRQ_ZB_BT);
    aes_set_irq_mask(FLD_CRYPT_IRQ);
#endif

#endif

}

/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
#if(AES_MODE == AES_ECB_MODE)
#if(WORK_MODE == BLOCKING_MODE)
    aes_encrypt(sKey, plaintext, ciphertext);//encrypt

    for(unsigned char i = 0; i < 16; i++)
    {
        if(ciphertext[i] != cipher[i])//check cipher result
        {
            gpio_set_high_level(LED1);//if error, LED1 on
            while(1);
        }
    }

    aes_decrypt(sKey, ciphertext, deciphertext);//decrypt

    for(unsigned char i = 0; i < 16; i++)
    {
        if(plaintext[i] != deciphertext[i])//check decipher result
        {
            gpio_set_high_level(LED2);//if error, LED2 on
            while(1);
        }
    }

    gpio_toggle(LED1 | LED2);//if all pass, LED1 & LED2 blink
    delay_ms(500);
#elif(WORK_MODE == INTERRUPT_MODE)
    aes_set_key_data(sKey, plaintext);//set key and data

    aes_set_mode(AES_ENCRYPT_MODE);//start cipher

    while(0 == irq_flag);

    aes_get_result(ciphertext);//get cipher result
    irq_flag = 0;

    for(unsigned char i = 0; i < 16; i++)
    {
        if(ciphertext[i] != cipher[i])//check cipher result
        {
            gpio_set_high_level(LED1);//if error, LED1 on
            while(1);
        }
    }

    delay_ms(500);

    aes_set_key_data(sKey, ciphertext);//set key and data

    aes_set_mode(AES_DECRYPT_MODE);//start decipher

    while(0 == irq_flag);
    aes_get_result(deciphertext);//get decipher result
    irq_flag = 0;

    for(unsigned char i = 0; i < 16; i++)
    {
        if(plaintext[i] != deciphertext[i])//check decipher result
        {
            gpio_set_high_level(LED2);//if error, LED2 on
            while(1);
        }
    }

    gpio_toggle(LED1 | LED2);//if all pass, LED1 & LED2 blink
    delay_ms(500);
#endif

#elif(AES_MODE == AES_CBC_MODE)
    for(int i = 0;i<16;i++)
    {
        temp[i] = plaintext1[i] ^ init[i];
    }
    aes_encrypt(sKey, temp, encrypt_result1);//first time encrypt


    for(int i = 0;i<16;i++)
    {
        if(encrypt_result1[i] != encrypt_std1[i])//check result
        {
            gpio_set_high_level(LED1);//if error, LED1 on
            while(1);
        }
    }

    for(int i = 0;i<16;i++)
    {
        temp[i] = plaintext2[i] ^ encrypt_result1[i];
    }
    aes_encrypt(sKey, temp, encrypt_result2);//second time encrypt

    for(int i = 0;i<16;i++)
    {
        if(encrypt_result2[i] != encrypt_std2[i])//check result
        {
            gpio_set_high_level(LED2);//if error, LED2 on
            while(1);
        }
    }

    aes_decrypt(sKey, encrypt_result1, decrypt_result1);//first time decrypt
    for(int i = 0;i<16;i++)
    {
        decrypt_result1[i] = decrypt_result1[i] ^ init[i];
    }

    for(int i = 0;i<16;i++)
    {
        if(decrypt_result1[i] != plaintext1[i])//check result
        {
            gpio_set_high_level(LED3);//if error, LED3 on
            while(1);
        }
    }

    aes_decrypt(sKey, encrypt_result2, decrypt_result2);//second time decrypt
    for(int i = 0;i<16;i++)
    {
        decrypt_result2[i] = decrypt_result2[i] ^ encrypt_result1[i];
    }

    for(int i = 0;i<16;i++)
    {
        if(decrypt_result2[i] != plaintext2[i])//check result
        {
            gpio_toggle(LED4);//if error, LED4 on
            while(1);
        }
    }

    gpio_toggle(LED1 | LED2);//if all pass, LED1 & LED2 blink
    gpio_toggle(LED3 | LED4);//if all pass, LED3 & LED4 blink
    delay_ms(500);
#endif
}

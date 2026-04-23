/********************************************************************************************************
 * @file    hal_aes.h
 *
 * @brief   This is the header file for tl752x
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



#ifndef __HAL_AES_H__
#define __HAL_AES_H__
#include "inc/drv_bt_aes.h"

#ifdef __cplusplus
extern "C" {
#endif

int aes_encrypt(unsigned char *key, unsigned char *plaintext, unsigned char *result);
int aes_decrypt(unsigned char *key, unsigned char *decrypttext, unsigned char *result);
void aes_set_key_data(unsigned char *key, unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_AES_H__ */

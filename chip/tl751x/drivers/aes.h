/********************************************************************************************************
 * @file    aes.h
 *
 * @brief   This is the header file for tl751x
 *
 * @author  Driver Group
 * @date    2023
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
/** @page AES
 *
 *  Introduction
 *  ===============
 *  tl751x supports hardware AES function.
 *
 *  API Reference
 *  ===============
 *  Header File: aes.h
 */
#ifndef _AES_H_
#define _AES_H_

#include "compiler.h"
#include "./reg_include/aes_reg.h"

/**********************************************************************************************************************
 *                                         global constants                                                           *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           global macro                                                             *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         global data type                                                           *
 *********************************************************************************************************************/
/**
 * @brief AES mode.
 */
typedef enum
{
    AES_ENCRYPT_MODE = 0,
    AES_DECRYPT_MODE = 2,
} aes_mode_e;

/**********************************************************************************************************************
 *                                     global variable declaration                                                    *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                      global function prototype                                                     *
 *********************************************************************************************************************/
/* @brief     This function refer to encrypt. AES module register must be used by word. , all data need big endian.
 * @param[in] key       - the key of encrypt.
 * @param[in] plaintext - the plaintext of encrypt.
 * @param[in] result    - the result of encrypt.
 * @return    none
 */
int aes_encrypt(unsigned char *key, unsigned char *plaintext, unsigned char *result);

/**
 * @brief     This function refer to decrypt. AES module register must be used by word., all data need big endian.
 * @param[in] key         - the key of decrypt.
 * @param[in] decrypttext - the decrypttext of decrypt.
 * @param[in] result      - the result of decrypt.
 * @return    none.
 */
int aes_decrypt(unsigned char *key, unsigned char *decrypttext, unsigned char *result);

/**
 * @brief     This function refer to set the base addr of data which use in CEVA module
 * @param[in] addr - the base addr of CEVA data.
 * @return    none.
 */
void aes_set_em_base_addr(unsigned int addr);

/**
 * @brief     This function refer to encrypt/decrypt to set key and data. AES module register must be used by word.
 *              All data need Little endian.
 * @param[in] key  - the key of encrypt/decrypt.
 * @param[in] data - the data which to do encrypt/decrypt. The address is 32 bits, but only the lower 16 bits are used.
 * @return    none.
 * @note      reg_embase_addr (32bit) +reg_aes_ptr (16bit) is the actual access address.
 *            reg_aes_ptr is only 16bit, so access space is only 64K. Adjusting reg_embase_addr changes the initial address of 64K.
 */
void aes_set_key_data(unsigned char *key, unsigned char *data);

/**
 * @brief     This function refer to encrypt/decrypt to get result. AES module register must be used by word.
 * @param[in] result - the result of encrypt/decrypt. Little endian
 * @return    none.
 */
void aes_get_result(unsigned char *result);

/**
 * @brief     This function refer to match the rpa.
 * @param[in] irk         - the irk sequence, max 16 group(16byte a group). The address is 32 bits, but only the lower 16 bits are used.
 * @param[in] irk_len     - the irk group num.
 * @param[in] rpa         - the rpa which want to match.
 * @return    0xff-not matched, (0x0-0x0f)-the match group index.
 * @note      reg_embase_addr (32bit) +reg_aes_irk_ptr (16bit) is the actual access address.
 *            reg_aes_irk_ptr is only 16bit, so access space is only 64K. Adjusting reg_embase_addr changes the initial address of 64K.
 */
unsigned char aes_rpa_match(unsigned char *irk, unsigned char irk_len, unsigned char *rpa);

/**
 * @brief     This function refer to set aes mode.
 * @param[in] mode - the irq mask.
 * @return    none.
 */
static inline void aes_set_mode(aes_mode_e mode)
{
    reg_aes_mode = (FLD_AES_START | mode);
}

/**
 * @brief     This function refer to set aes irq mask.
 * @param[in] mask - the irq mask.
 * @return    none.
 */
static inline void aes_set_irq_mask(aes_irq_e mask)
{
    reg_aes_irq_mask |= mask;
}

/**
 * @brief     This function refer to clr aes irq mask.
 * @param[in] mask - the irq mask.
 * @return    none.
 */
static inline void aes_clr_irq_mask(aes_irq_e mask)
{
    reg_aes_irq_mask &= (~mask);
}

/**
 * @brief     This function refer to get aes irq status.
 * @param[in] status - the irq status to get.
  * @retval   non-zero   -  the interrupt occurred.
  * @retval   zero  -  the interrupt did not occur.
 */
static inline int aes_get_irq_status(aes_irq_e status)
{
    return (reg_aes_irq_status & status);
}

/**
 * @brief     This function refer to clr aes irq status.
 * @param[in] status - the irq status to clear.
 * @return    none.
 */
static inline void aes_clr_irq_status(aes_irq_e status)
{
    reg_aes_clr_irq_status = (status);
}

#endif /* _AES_H_ */

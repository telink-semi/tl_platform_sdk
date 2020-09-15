/********************************************************************************************************
 * @file	app_pke.h
 *
 * @brief	This is the header file for B91
 *
 * @author	Z.W.H
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#pragma once

#include "../app_config.h"


#define GET_MAX_LEN(a,b)         (((a)>(b))?(a):(b))

typedef enum
{
	TRNG_SUCCESS = 0,
	TRNG_ERROR,
}pke_trng_ret_code_e;

//KDF define
typedef void *(*KDF_FUNC)(const void *input, unsigned int byteLen, unsigned char *key, unsigned int keyByteLen);

/**
 * @brief		get ECCP key pair(the key pair could be used in ECDSA/ECDH).
 * @param[in]	curve	- eccp curve struct pointer.
 * @param[out]	priKey	- private key, big-endian.
 * @param[out]	pubKey	- public key, big-endian.
 * @return		PKE_SUCCESS(success), other(error).
 */
unsigned char eccp_getkey(eccp_curve_t *curve, unsigned char *priKey, unsigned char *pubKey);

/**
 * @brief		get rand.
 * @param[in] 	rand	- the buffer rand.
 * @param[in] 	byteLen	- the length of rand.
 * @return		0:TRNG_SUCCESS,   1:TRNG_ERROR.
 */
unsigned char rand_get(unsigned char *rand, unsigned int byteLen);

/**
 * @brief		This function is used to determine whether the array is all 0s.
 * @param[in]	data	- the buffer data.
 * @param[in]	len		- the length of data.
 * @return		1: all 0, 0: not all 0.
 */
int ismemzero4(void *data, unsigned int len);
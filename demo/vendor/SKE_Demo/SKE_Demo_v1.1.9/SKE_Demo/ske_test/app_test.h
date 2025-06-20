/********************************************************************************************************
 * @file    app_test.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#ifndef __APP_TEST__H_
#define __APP_TEST__H_
/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C"
{
#endif
#include "common.h"

    unsigned int  SKE_LP_CCM_all_Test(void);
    unsigned int  SKE_LP_GCM_all_test(void);
    unsigned int  SKE_LP_GMAC_all_test(void);
    unsigned char SKE_sample_all_test(void);
    unsigned int  SKE_all_test(void);
    unsigned int SKE_LP_XTS_all_Test(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif /* __APP_TEST__H_ */

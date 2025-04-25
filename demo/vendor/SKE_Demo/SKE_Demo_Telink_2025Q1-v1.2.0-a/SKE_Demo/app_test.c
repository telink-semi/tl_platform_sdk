/********************************************************************************************************
 * @file    app_test.c
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
#include "common.h"
#include "ske_test/app_test.h"

/**
 * @brief           Test AES-128 ECB mode with multiple blocks
 * @return          0 if test passes, 1 if test fails
 */
extern unsigned int ske_lp_aes128_ecb_sample(void);

/**
 * @brief           Test AES-128 CBC mode
 * @return          0 if test passes, 1 if test fails
 */
extern unsigned int ske_lp_aes128_cbc_sample(void);

/**
 * @brief           Test AES-128 GCM mode
 * @return          0 if test passes, 1 if test fails
 */
extern unsigned int ske_lp_aes128_gcm_sample(void);

/**
 * @brief           Run all CMAC tests for supported algorithms
 * @return          0 if all tests pass, 1 if any test fails
 */
extern unsigned int ske_lp_cmac_all_test(void);

/**
 * @brief           Comprehensive test function for all supported GMAC implementations
 * @return          0 if all tests pass, 1 if any test fails
 */
extern unsigned int ske_lp_gmac_all_test(void);

/**
 * @brief           Runs all CCM mode tests for supported algorithms.
 * @return          SKE_SUCCESS if all tests pass, otherwise error code.
 */
extern unsigned int ske_lp_ccm_all_test(void);

/**
 * @brief           Test function for AES-128 cryptographic operations
 * @return          0 if all tests pass, 1 if any test fails
 */
extern unsigned int aes_128_test(void);

/**
 * @brief           Comprehensive test function for all supported GCM implementations
 * @return          0 if all tests pass, 1 if any test fails
 */
unsigned int ske_lp_gcm_all_test(void);

unsigned int ske_app_test(void)
{
    trng_dig_en();
    ske_dig_en();
#ifdef SKE_LP_DMA_FUNCTION
    ske_set_tx_dma_config(DMA0);
    ske_set_rx_dma_config(DMA1, DMA_BURST_1_WORD);
#endif /* SKE_LP_DMA_FUNCTION */

#if 0
    if(ske_speed_test())
        return 1;
#endif

#ifdef SKE_LP_DMA_FUNCTION
#if 0
    if(ske_dma_speed_test())
        return 1;
#endif
#endif

/**/
#ifdef SUPPORT_SKE_AES_128
#ifdef SUPPORT_SKE_MODE_ECB
    if (ske_lp_aes128_ecb_sample())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_CBC
    if (ske_lp_aes128_cbc_sample())
    {
        return 1;
    }
#endif

#if defined(SUPPORT_SKE_MODE_GCM)
    if (ske_lp_aes128_gcm_sample())
    {
        return 1;
    }
#endif
#endif

/**/
#ifdef SUPPORT_SKE_MODE_CBC_MAC
    if (ske_lp_cbc_mac_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_CMAC
    if (ske_lp_cmac_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_XCBC_MAC_96
    if (ske_lp_aes_xcbc_mac_96_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_GCM
    if (ske_lp_gcm_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_GMAC
    if (ske_lp_gmac_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_CCM
    if (ske_lp_ccm_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_MODE_XTS
    if (ske_lp_xts_all_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_SM4
    if (sm4_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_128
    if (aes_128_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_192
    if (aes_192_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_AES_256
    if (aes_256_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_DES
    if (des_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_128
    if (tdes_128_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_192
    if (tdes_192_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
    if (tdes_eee_128_test())
    {
        return 1;
    }
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
    if (tdes_eee_192_test())
    {
        return 1;
    }
#endif

    /**/
    printf("\r\n\r\n SKE LP test over! \r\n");

    return 0;

    return 0;
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);
    ske_app_test();
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(50);
}

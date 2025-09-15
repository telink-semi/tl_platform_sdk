/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    /*
 * In this demo, the program of DSP was burned in flash, and D25F will use DMA to transport the program of DSP from flash to DSP 's RAM, and let DSP start from IRAM.
 * 1. DSP_DLM_BIN_SIZE, DSP_ILM_BIN_SIZE and DSP_ILM_START_ADDR all are configurable.
 * 2. Compile MULTI_CORE_Demo, burn to flash address 0.
 * 3. burn to DSP_FW_DOWNLOAD_FLASH_ADDR address.
 */
    #define DSP_BOOTLOADER_BY_DMA 0
    /*
 * In this demo, D25F will not transport code. The DSP program will start from the address it is burned to.
 */
    #define DSP_BOOTLOADER_BY_MCU 1
    #define DSP_BOOTLOADER_MODE   DSP_BOOTLOADER_BY_MCU

    #if (DSP_BOOTLOADER_MODE == DSP_BOOTLOADER_BY_DMA)
    #if defined(MCU_CORE_TL753X)
        #define DSP_DLM_BIN_SIZE   0x80000        /* Note:  Can be adjusted according to the actual amount of DRAM space used by the dsp. */
        #define DSP_ILM_BIN_SIZE   0x40000        /* Note:  Can be adjusted according to the actual amount of IRAM space used by the dsp. */
        #define DSP_DLM_LMA_START  0x02000000     /* Note:  This address is the starting address of the dsp's DRAM space and cannot be modified */
        #define DSP_ILM_LMA_START  0x02200000     /* Note:  This address is the starting address of the dsp's IRAM space and cannot be modified */
        #define DSP_ILM_START_ADDR 0x02200660     /* Note:  This address is the startup address of the IRAM of the dsp which can be changed by modifying the LSP file. */
    #else
        #define DSP_DLM_BIN_SIZE   0x40000        /* Note:  Can be adjusted according to the actual amount of DRAM space used by the dsp. */
        #define DSP_ILM_BIN_SIZE   0x40000        /* Note:  Can be adjusted according to the actual amount of IRAM space used by the dsp. */
        #define DSP_DLM_LMA_START  0x02000000     /* Note:  This address is the starting address of the dsp's DRAM space and cannot be modified */
        #define DSP_ILM_LMA_START  0x02100000     /* Note:  This address is the starting address of the dsp's IRAM space and cannot be modified */
        #define DSP_ILM_START_ADDR 0x02100660     /* Note:  This address is the startup address of the IRAM of the dsp which can be changed by modifying the LSP file. */
    #endif
    #endif

    #define DSP_FW_DOWNLOAD_FLASH_ADDR 0x20040000 /* Note:  If modified, please make sure this value is within the address range of Flash. */

    #if (TEST_MAILBOX)
unsigned int           val_d25f_to_dsp_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_dsp_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_dsp_to_d25_irq_flag = 0;
    #endif
#endif

#if (ENABLE_N22)
    /*
 * In this demo, the program of N22 was burned in flash, and D25F will use DMA to transport the program of N22 from flash to N22's RAM, and let N22 start from IRAM.
 * 1. N22_ISRAM_STARTUP_ADDR, N22_DRAM_STARTUP_ADDR and N22_FW_DOWNLOAD_FLASH_ADDR all are configurable.
 * 2. Compile MULTI_CORE_Demo, burn to flash address 0.
 * 3. Compile N22_TEST_DEMO (boot (cstartup_ram. S)/link (ram_boot. link)) and burn to N22_FW_DOWNLOAD_FLASH_ADDR address.
 */
    #define N22_BOOTLOADER_BY_DMA 0

    /*
 * In this demo, D25F will not transport code. The N22 program will start from the address it is burned to.
 * You can configure the corresponding s and link files according to the scene.
 */
    #define N22_BOOTLOADER_BY_MCU 1
#if defined(MCU_CORE_TL322X)
    #define N22_BOOTLOADER_BY_RRAM_MCU 2
#endif

    #define N22_BOOTLOADER_MODE   N22_BOOTLOADER_BY_DMA

    #if (N22_BOOTLOADER_MODE == N22_BOOTLOADER_BY_DMA)
        #if defined(MCU_CORE_TL7518)
            #define N22_IRAM_STARTUP_ADDR 0x50068000 /* Note:  If modified, please make sure this value is within the IRAM address range of N22.
                                                            The corresponding link file need to modify in the same time. */
        #elif defined(MCU_CORE_TL322X) || defined(MCU_CORE_TL753X)
            #define N22_IRAM_STARTUP_ADDR 0x50000000 /* Note:  If modified, please make sure this value is within the IRAM address range of N22.
                                                            The corresponding link file need to modify in the same time. */
        #elif defined(MCU_CORE_TL751X)
            #define N22_IRAM_STARTUP_ADDR 0x50020000 /* Note:  If modified, please make sure this value is within the IRAM address range of N22.
                                                            The corresponding link file need to modify in the same time. */
        #endif

        #if defined(MCU_CORE_TL753X)
            #define N22_DRAM_ADDR 0x51000000             /* Note:  If modified, please make sure this value is within the DRAM address range of N22.
                                                           The corresponding link file need to modify in the same time. */
        #else
            #define N22_DRAM_ADDR 0x50080000             /* Note:  If modified, please make sure this value is within the DRAM address range of N22.
                                                           The corresponding link file need to modify in the same time. */
        #endif

    #endif

    #define N22_FW_DOWNLOAD_FLASH_ADDR 0x20080000 /* Note:  If modified, please make sure this value is within the address range of Flash. 
                                                            The corresponding link file need to modify in the same time. */

#define N22_FW_DOWNLOAD_RRAM_ADDR   0x00540000

    #if (TEST_MAILBOX)
unsigned int           val_d25f_to_n22_word[2]     = {0x01234567, 0x89abcdef};
unsigned int           val_n22_to_d25f_word[2]     = {0};
volatile unsigned char mailbox_n22_to_d25_irq_flag = 0;
volatile unsigned char mailbox_n22_to_d25_cnt      = 0;
    #endif

    #if (N22_BOOTLOADER_MODE == N22_BOOTLOADER_BY_DMA)
unsigned int n22_ilm_bin_size  = 0;
unsigned int n22_dlm_bin_size  = 0;
unsigned int n22_dlm_lma_start = 0;
    #endif

#endif

#if (!defined(MCU_CORE_TL322X) && ENABLE_DSP) || (ENABLE_N22)
dma_config_t flash_sram_dma_config = {
    .dst_req_sel    = 0,
    .src_req_sel    = 0,
    .dst_addr_ctrl  = DMA_ADDR_INCREMENT,
    .src_addr_ctrl  = DMA_ADDR_INCREMENT,
    .dstmode        = DMA_NORMAL_MODE,
    .srcmode        = DMA_NORMAL_MODE,
    .dstwidth       = DMA_CTR_WORD_WIDTH, //must word
    .srcwidth       = DMA_CTR_WORD_WIDTH, ////must word
    .src_burst_size = 0,
    .read_num_en    = 0,
    .priority       = 0,
    .write_num_en   = 0,
    .auto_en        = 0, //must 0
};
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);

#if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    #if (DSP_BOOTLOADER_MODE == DSP_BOOTLOADER_BY_MCU)
    sys_dsp_init(DSP_FW_DOWNLOAD_FLASH_ADDR);
    sys_dsp_start();
    #elif (DSP_BOOTLOADER_MODE == DSP_BOOTLOADER_BY_DMA)
    sys_dsp_init(DSP_ILM_START_ADDR);
    dma_config(DMA0, &flash_sram_dma_config);
    dma_config(DMA1, &flash_sram_dma_config);

    dma_set_address(DMA0, DSP_FW_DOWNLOAD_FLASH_ADDR, DSP_DLM_LMA_START);
    dma_set_size(DMA0, DSP_DLM_BIN_SIZE, DMA_WORD_WIDTH);
    dma_chn_en(DMA0);

    dma_set_address(DMA1, DSP_FW_DOWNLOAD_FLASH_ADDR + 0x100000, DSP_ILM_LMA_START);
    dma_set_size(DMA1, DSP_ILM_BIN_SIZE, DMA_WORD_WIDTH);
    dma_chn_en(DMA1);

    while (reg_dma_ctr0(DMA0) & 1)
        ;
    while (reg_dma_ctr0(DMA1) & 1)
        ;
    sys_dsp_start();
    #endif
#endif

#if (ENABLE_N22)
    #if (N22_BOOTLOADER_MODE == N22_BOOTLOADER_BY_DMA)
    sys_n22_init(N22_IRAM_STARTUP_ADDR);

    n22_ilm_bin_size  = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x08);
    n22_dlm_bin_size  = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x0c);
    n22_dlm_lma_start = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x10) + N22_FW_DOWNLOAD_FLASH_ADDR;
    dma_config(DMA2, &flash_sram_dma_config);
    dma_config(DMA3, &flash_sram_dma_config);

    dma_set_address(DMA2, N22_FW_DOWNLOAD_FLASH_ADDR, N22_IRAM_STARTUP_ADDR);
    dma_set_size(DMA2, n22_ilm_bin_size, DMA_WORD_WIDTH);
    dma_chn_en(DMA2);

    dma_set_address(DMA3, n22_dlm_lma_start, N22_DRAM_ADDR);
    dma_set_size(DMA3, n22_dlm_bin_size, DMA_WORD_WIDTH);
    dma_chn_en(DMA3);

    while (reg_dma_ctr0(DMA2) & 1)
        ;
    while (reg_dma_ctr0(DMA3) & 1)
        ;

    sys_n22_start();
    #elif (N22_BOOTLOADER_MODE == N22_BOOTLOADER_BY_MCU)
    sys_n22_init(N22_FW_DOWNLOAD_FLASH_ADDR);
    sys_n22_start();
#elif(N22_BOOTLOADER_MODE == N22_BOOTLOADER_BY_RRAM_MCU)
    sys_n22_init(N22_FW_DOWNLOAD_RRAM_ADDR);
    sys_n22_start();
    #endif

#endif

#if (TEST_MAILBOX)

    #if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    mailbox_set_irq_mask(FLD_MAILBOX_DSP_TO_D25F_IRQ);
    plic_interrupt_enable(IRQ_MAILBOX_DSP_TO_D25);
    core_interrupt_enable();
        #if (!TEST_STALL)
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
        #endif
    #endif

    #if (ENABLE_N22)
    #if defined(MCU_CORE_TL322X)
    mailbox_set_irq_mask_d25f();
    #else
    mailbox_set_irq_mask(FLD_MAILBOX_N22_TO_D25F_IRQ);
    #endif
    plic_interrupt_enable(IRQ_MAILBOX_N22_TO_D25);
    core_interrupt_enable();
        #if (!TEST_STALL)
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
        #endif
    #endif

#endif
}

void main_loop(void)
{
#if (TEST_MAILBOX)
    #if (TEST_STALL)

    delay_ms(1000);

        #if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    val_d25f_to_dsp_word[0] = 0x01234567;
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
    while (mailbox_dsp_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_dsp_to_d25_irq_flag = 0;
        #endif

        #if (ENABLE_N22)
    val_d25f_to_n22_word[0] = 0x01234567;
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
    while (mailbox_n22_to_d25_irq_flag == 0) {
        delay_us(1);
    }
    mailbox_n22_to_d25_irq_flag = 0;
        #endif

    delay_ms(1000);

        #if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    val_d25f_to_dsp_word[0] = 0x11111111;
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
        #endif

        #if (ENABLE_N22)
    val_d25f_to_n22_word[0] = 0x11111111;
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
        #endif

    #else
        #if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
    if (mailbox_dsp_to_d25_irq_flag == 1) {
        mailbox_dsp_to_d25_irq_flag = 0;
        if ((val_dsp_to_d25f_word[0] == val_d25f_to_dsp_word[0]) && (val_dsp_to_d25f_word[1] == val_d25f_to_dsp_word[1])) {
            gpio_toggle(LED1);
        }
    }
    delay_ms(1000);
    mailbox_d25f_set_dsp_msg(val_d25f_to_dsp_word);
        #endif

        #if (ENABLE_N22)
    if (mailbox_n22_to_d25_irq_flag == 1) {
        mailbox_n22_to_d25_irq_flag = 0;
        if ((val_n22_to_d25f_word[0] == val_d25f_to_n22_word[0]) && (val_n22_to_d25f_word[1] == val_d25f_to_n22_word[1])) {
            gpio_toggle(LED1);
        }
    }
    delay_ms(1000);
    mailbox_d25f_set_n22_msg(val_d25f_to_n22_word);
        #endif
    #endif

#else
    gpio_toggle(LED1);
    delay_ms(200);
#endif
}

#if (TEST_MAILBOX)
    #if !defined(MCU_CORE_TL322X) && (ENABLE_DSP)
_attribute_ram_code_sec_noinline_ void mailbox_dsp_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_DSP_TO_D25F_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_DSP_TO_D25F_IRQ);
        mailbox_d25f_get_dsp_msg(val_dsp_to_d25f_word);
        mailbox_dsp_to_d25_irq_flag = 1;
    }
}
PLIC_ISR_REGISTER(mailbox_dsp_to_d25_irq_handler, IRQ_MAILBOX_DSP_TO_D25)
    #endif

    #if !defined(MCU_CORE_TL322X) && (ENABLE_N22)
_attribute_ram_code_sec_noinline_ void mailbox_n22_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status() & FLD_MAILBOX_N22_TO_D25F_IRQ) {
        mailbox_clr_irq_status(FLD_MAILBOX_N22_TO_D25F_IRQ);
        mailbox_d25f_get_n22_msg(val_n22_to_d25f_word);
        mailbox_n22_to_d25_irq_flag = 1;
        mailbox_n22_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_n22_to_d25_irq_handler, IRQ_MAILBOX_N22_TO_D25)
    #endif

    #if defined(MCU_CORE_TL322X) && (ENABLE_N22)
_attribute_ram_code_sec_noinline_ void mailbox_n22_to_d25_irq_handler(void)
{
    if (mailbox_get_irq_status_d25f()) {
        mailbox_clr_irq_status_d25f();
        mailbox_d25f_get_n22_msg(val_n22_to_d25f_word);
        mailbox_n22_to_d25_irq_flag = 1;
        mailbox_n22_to_d25_cnt++;
    }
}
PLIC_ISR_REGISTER(mailbox_n22_to_d25_irq_handler, IRQ_MAILBOX_N22_TO_D25)
    #endif
#endif

/********************************************************************************************************
 * @file    app.c
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
#if defined(MCU_CORE_TL752X)

#define  BOOTLOADER_DEMO    0
#define  APP_DEMO           1
#define  DEMO_MODE          BOOTLOADER_DEMO

#include "common.h"
#include "driver.h"
#define APP_CODE_ADDR 0x10008000
#define JUMP_ILM_ADDR 0x0
#define IDENTIFIER    (0x59485857)

static dmac_handle_t boot_flash_dmac_handle;
uart_handle_t uart_handle;
dwc_ssi_handle_t boot_dwc_ssi_handle;
nor_flash_dev_t flash_dev;
typedef struct {
    unsigned int rev_val;
    unsigned int app_identify;
    unsigned int ilm_start;
    unsigned int ilm_end;
} app_code_info_t;

/**
 * @brief: Redefined usr_puts
 * @param {char} *ptr
 * @param {int} len
 * @retval: none
 */
void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}
gpio_init_t gpio_init1;

/**
 * @brief: uart init
 * @retval: none
 */
void bootloader_uart_init(void)
{

    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init1.port = GPIO_PORT_A;
    gpio_init1.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init1.mode = MODE_AF;
    gpio_init1.pull = GPIO_PULLUP;
    gpio_init1.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init1);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}

void bootloader_uart_deinit(void)
{
    drv_uart_transmitter_empty_waiting(&uart_handle, DRV_MAX_DELAY);
    drv_uart_deinit(&uart_handle);
    __DRV_CPR_UART1_CLK_DISABLE();
}

/**
 * @brief: dwc_ssi init
 * @retval: none
 */
void bootloader_dwc_ssi_init(void)
{
    /*dwc ssi init*/
    memset(&boot_dwc_ssi_handle, 0, sizeof(dwc_ssi_handle_t));
    __DRV_CPR_DWC_SSI0_CLOCK_ENABLE();
    __DRV_CPR_DWC_SSI0_CLOCK_DIV(0);

    memset(&boot_flash_dmac_handle, 0, sizeof(dmac_handle_t));

    __DRV_CPR_CPU_DMA_CLK_ENABLE();
    boot_flash_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    boot_flash_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    boot_flash_dmac_handle.init.dst_burst_size = DMAC_MSIZE_8;
    boot_flash_dmac_handle.init.src_burst_size = DMAC_MSIZE_8;
    boot_flash_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    boot_flash_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    boot_flash_dmac_handle.init.fifo_mode = 1;
    boot_flash_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    boot_flash_dmac_handle.init.channel = CPU_DMAC_CH5;
    boot_flash_dmac_handle.init.src_hs_num = CPU_DMAC_HS_DWC_SSI_0_RX;
    boot_flash_dmac_handle.init.dst_hs_num = CPU_DMAC_HS_DWC_SSI_0_TX;
    boot_flash_dmac_handle.instance = CPU_DMAC;
    drv_dmac_init(&boot_flash_dmac_handle);

    /*dwc ssi init*/
    memset(&boot_dwc_ssi_handle, 0, sizeof(dwc_ssi_handle_t));
    __DRV_CPR_DWC_SSI0_CLOCK_ENABLE();
    __DRV_CPR_DWC_SSI0_CLOCK_DIV(0);
    boot_dwc_ssi_handle.init.baud =  6000000;
    boot_dwc_ssi_handle.init.m_mclk = drv_cpr_get_mclk0_freq() / (__DRV_CPR_DWC_SSI0_GET_CLOCK_DIV() + 1);

    /*When the digital voltage of the chip is high or low, the mclk frequency is 96M or below, rx_sample_delay set to 1.
        When the mclk is low and greater than or equal to 128M, rx_sample_delay use  2.
        It is recommended to avoid using the critical state
    */
    boot_dwc_ssi_handle.init.rx_sample_delay = 1; //todo


    boot_dwc_ssi_handle.xip_init.frf = DWC_SSI_XIP_CTRL_FRF_SPI_QUAL;
    boot_dwc_ssi_handle.instance = (ssi_reg_t *)DWC_SSI0;

    drv_dwc_ssi_init(&boot_dwc_ssi_handle);
    __DRV_LINKDMA(&boot_dwc_ssi_handle, hdma, boot_flash_dmac_handle);
    flash_dev.dwc_ssi = &boot_dwc_ssi_handle;
    flash_dev.init.wrap_param = NOR_WARP_LENGTH_32BIT;
    drv_nor_init(&flash_dev);


    drv_hw_cache_disable();
    drv_hw_cache_enable();
    drv_dwc_ssi_xip_enable(&boot_dwc_ssi_handle);
}

/**
 * @brief: jump func
 * @param {unsigned int} addr
 * @retval: none
 */
void bootloader_jump_fw(unsigned int addr)
{
    __asm__ __volatile__("jr\t%0\n\t"
                        :
                        :"r"(addr)
                        );
}
volatile unsigned int debug_flag=0;
void user_init(void)
{
#if(DEMO_MODE   ==       BOOTLOADER_DEMO)
    unsigned char *p = (unsigned char *)JUMP_ILM_ADDR;
    app_code_info_t app_info;

    bootloader_uart_init();
    bootloader_dwc_ssi_init();

    soc_printf("this is bootloader test\n");

    memcpy((unsigned char *)&app_info, (unsigned char *)APP_CODE_ADDR, sizeof(app_code_info_t));

    if (app_info.app_identify == IDENTIFIER) {
        memcpy((unsigned char *)p, (unsigned char *)APP_CODE_ADDR, app_info.ilm_end - app_info.ilm_start);
        soc_printf("jump to app:0x%08x\n", JUMP_ILM_ADDR);
        bootloader_uart_deinit();
        gpio_init1.port = GPIO_PORT_A;
        gpio_init1.pin = GPIO_PIN_0 | GPIO_PIN_1;
        gpio_init1.mode = MODE_AF;
        gpio_init1.pull = GPIO_PULLUP;
        gpio_init1.alternate = GPIO_ALTERNATE_DEFAULT;
        drv_gpio_init(&gpio_init1);
        bootloader_jump_fw(JUMP_ILM_ADDR);
    }

    while (1) {
        soc_printf("this is bootloader test\n");
        for (int i = 0; i < 0xfffff; i++) {
            __NOP();
        }
    }
#elif(DEMO_MODE     ==     APP_DEMO)
    bootloader_uart_init(); // pa0 and pa1 are used by uart 1
    soc_printf("Debug Demo!\n");
    while(1){
        debug_flag++;
    }
#endif
//    return 0;
}

#else
/*
 * @FilePath: \tx232_driver_src\demo\bootloader\main.c
 * @Version: V1.0.1
 * @Date: 2025-08-21 15:55:27
 * @Author: driver group
 * @Description:
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */
#include <string.h>
#include "drv_uart.h"
#include "drv_cpr.h"
#include "drv_pmu.h"
#include "drv_dmac.h"
#include "../epm_log/epm_log.h"
#include "drv_gpio.h"
#include "drv_dwc_ssi.h"
#include "drv_nor_flash.h"
#include "../soc_memcpy/soc_memcpy.h"


#define UNUSED_VAL              ((unsigned int) (-1))
#define APP_CODE_ADDR           (0x10020000)
#define JUMP_ILM_ADDR           (0x0)
#define IDENTIFIER              (0x59485857)
#define BOOTLOADER_VERSION_V2   2

static dmac_handle_t flash_dmac_handle;
uart_handle_t uart_handle;
dwc_ssi_handle_t dwc_ssi_handle;
nor_flash_dev_t flash_dev;
typedef struct {
    unsigned int rev_val;
    unsigned int app_identify;
    unsigned int ilm_start;
    unsigned int ilm_end;
#if (defined(MCU_CORE_TL651X))
    unsigned int jump_addr;
    unsigned int tcm_mode;
#endif
} app_code_info_t;

/**
 * @brief: Redefined usr_puts
 * @param {char} *ptr
 * @param {int} len
 * @retval: none
 */
void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

/**
 * @brief: uart init
 * @retval: none
 */
void bootloader_uart_init(void)
{
    gpio_init_t gpio_init;

    __DRV_CPR_UART1_CLK_ENABLE();

    gpio_init.port = GPIO_PORT_A;
    gpio_init.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_init.mode = MODE_AF;
    gpio_init.pull = GPIO_PULLUP;
    gpio_init.alternate = GPIO_ALTERNATE_FUNC_2;
    drv_gpio_init(&gpio_init);

    uart_handle.instance = UART1;
    uart_handle.init.baudrate = 500000;
    uart_handle.init.hwflowctl = UART_HWCONTROL_NONE;
    uart_handle.init.parity = UART_PARITY_NONE;
    uart_handle.init.stopbits = UART_STOPBITS_1;
    uart_handle.init.wordlength = UART_WORDLENGTH_8B;
    drv_uart_init(&uart_handle);
}

void bootloader_uart_deinit(void)
{
    drv_uart_transmitter_empty_waiting(&uart_handle, DRV_MAX_DELAY);
    drv_uart_deinit(&uart_handle);
    __DRV_CPR_UART1_CLK_DISABLE();
    drv_gpio_set_alternate(GPIO_PORT_A, GPIO_PIN_0, GPIO_ALTERNATE_DEFAULT);
    drv_gpio_set_alternate(GPIO_PORT_A, GPIO_PIN_1, GPIO_ALTERNATE_DEFAULT);
}

/**
 * @brief: dwc_ssi init
 * @retval: none
 */
void bootloader_dwc_ssi_init(void)
{
    /*dwc ssi init*/
    memset(&dwc_ssi_handle, 0, sizeof(dwc_ssi_handle_t));
    __DRV_CPR_DWC_SSI0_CLOCK_ENABLE();
    __DRV_CPR_DWC_SSI0_CLOCK_DIV(0);
    dwc_ssi_handle.init.baud = 6000000;
    dwc_ssi_handle.xip_init.frf = DWC_SSI_XIP_CTRL_FRF_SPI_QUAL;
    dwc_ssi_handle.init.m_mclk = drv_cpr_get_mclk0_freq() / (__DRV_CPR_DWC_SSI0_GET_CLOCK_DIV() + 1);
    dwc_ssi_handle.init.rx_sample_delay = 1;
    dwc_ssi_handle.instance = (ssi_reg_t *)DWC_SSI0;
    drv_dwc_ssi_init(&dwc_ssi_handle);

    /*dma init*/
    memset(&flash_dmac_handle, 0, sizeof(dmac_handle_t));
    __DRV_CPR_CPU_DMA_CLK_ENABLE();
    flash_dmac_handle.init.dst_addr_change_mode = DMAC_ADDR_INCREASE;
    flash_dmac_handle.init.src_addr_change_mode = DMAC_ADDR_CONSTANT;
    flash_dmac_handle.init.dst_burst_size = DMAC_MSIZE_4;
    flash_dmac_handle.init.src_burst_size = DMAC_MSIZE_4;
    flash_dmac_handle.init.dst_bus_width = DMAC_TR_WIDTH_8BITS;
    flash_dmac_handle.init.src_bus_width = DMAC_TR_WIDTH_8BITS;
    flash_dmac_handle.init.fifo_mode = 1;
    flash_dmac_handle.init.trans_mode = DMAC_CTL_TT_PER2MEM;
    flash_dmac_handle.init.channel = CPU_DMAC_CH5;
    flash_dmac_handle.init.src_hs_num = CPU_DMAC_HS_DWC_SSI_0_RX;
    flash_dmac_handle.instance = CPU_DMAC;
    drv_dmac_init(&flash_dmac_handle);

    __DRV_LINKDMA(&dwc_ssi_handle, hdma, flash_dmac_handle);
    drv_hw_int_enable(CPU_DMA_IRQn);

    flash_dev.dwc_ssi = &dwc_ssi_handle;
    flash_dev.init.wrap_param = NOR_WARP_LENGTH_32BIT;
    drv_nor_init(&flash_dev);

    drv_hw_cache_disable();
    drv_hw_cache_enable();
    drv_dwc_ssi_xip_enable(&dwc_ssi_handle);
}

/**
 * @brief: jump func
 * @param {unsigned int} addr
 * @retval: none
 */
void bootloader_jump_fw(unsigned int addr)
{
    __asm__ __volatile__("jr\t%0\n\t"
                        :
                        :"r"(addr)
                        );
}

int user_init(void)
{
    uint32_t jump_addr = UNUSED_VAL;

    app_code_info_t app_info;

    bootloader_uart_init();
    bootloader_dwc_ssi_init();

    LOG_INF("this is bootloader test\n");

    memcpy(&app_info, (unsigned char *)APP_CODE_ADDR, sizeof(app_code_info_t));

    if (IDENTIFIER == app_info.app_identify) {
    #if (defined(MCU_CORE_TL651X))
        jump_addr = app_info.jump_addr;
        __DRV_PMU_CPU_TCM_MODE(app_info.tcm_mode);
    #else
        jump_addr = JUMP_ILM_ADDR;
    #endif
    }

    if (jump_addr != UNUSED_VAL) {
        soc_memcpy((void *)jump_addr, (unsigned char *)APP_CODE_ADDR, app_info.ilm_end - app_info.ilm_start);
        LOG_INF("jump to app:0x%08x\n", jump_addr);
        bootloader_uart_deinit();
        bootloader_jump_fw(jump_addr);
    }

    while (1) {
        LOG_INF("this is bootloader test\n");
        for (int i = 0; i < 0xfffff; i++) {
            __NOP();
        }
    }
    return 0;
}
#endif

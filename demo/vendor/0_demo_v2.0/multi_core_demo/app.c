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
/*
 * @FilePath: \tx232_driver_src\demo\boot_cpu1\main.c
 * @Version: V1.0.0
 * @Date: 2025-05-20 10:19:47
 * @Author: driver group
 * @Description: This is the source file for 9062
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */
#include "common.h"
#include "inc/drv_cpr.h"
#include "modules/drv_gpio.h"
#include "inc/drv_uart.h"
#include "common.h"
#include <string.h>

#if (ENABLE_N22)
#define  START_UP_BY_MCUA    1
#if START_UP_BY_MCUA
#define N22_FW_DOWNLOAD_FLASH_ADDR         0x10100000
#define N22_IRAM_STARTUP_ADDR              0x50000000
#define N22_DRAM_ADDR                      0x50080000

unsigned int n22_ilm_bin_size  = 0;
unsigned int n22_dlm_bin_size  = 0;
unsigned int n22_dlm_lma_start = 0;

#else
#define N22_FW_DOWNLOAD_FLASH_ADDR         0x100000
#define N22_FW_BIN_SIZE                    0x60000
#endif

#endif

#if (ENABLE_DSP)
#define DSP_IRAM_FW_DOWNLOAD_FLASH_ADDR    0x180000
#define DSP_DRAM_FW_DOWNLOAD_FLASH_ADDR    0x200000
#endif

uart_handle_t uart_handle;

#if (TEST_MAILBOX)
ipcm_handle_t hipcm;
void IPCM_IRQHandler(void)
{
    drv_ipcm_irqhandler(&hipcm);
}
PLIC_ISR_REGISTER(IPCM_IRQHandler, IPCM_IRQn);

void ipcm_callback(ipcm_cpu_id_t cpux, uint32_t msg_addr)
{
    (void) cpux;
    soc_printf("ipcm cpu0 inter %x\n", msg_addr);
}
#endif

void usr_puts(char *ptr, int len)
{
    drv_uart_transmit(&uart_handle, (uint8_t *)ptr, len, DRV_MAX_DELAY);
}

void log_init(void)
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

void user_init(void)
{
    log_init();
    soc_printf("\n Multi core test!\n");
#if (ENABLE_N22)
#if(START_UP_BY_MCUA)
    sys_n22_init(N22_IRAM_STARTUP_ADDR);

    n22_ilm_bin_size  = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x08);
    n22_dlm_bin_size  = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x0c);
    n22_dlm_lma_start = REG_ADDR32(N22_FW_DOWNLOAD_FLASH_ADDR + 0x10) + N22_FW_DOWNLOAD_FLASH_ADDR;

    memcpy((unsigned int*)N22_IRAM_STARTUP_ADDR, (unsigned int*)N22_FW_DOWNLOAD_FLASH_ADDR, n22_ilm_bin_size);
    memcpy((unsigned int*)N22_DRAM_ADDR, (unsigned int*)n22_dlm_lma_start, n22_dlm_bin_size);
    sys_n22_start();
    while(1);
#else
    boot_cpu1(N22_FW_DOWNLOAD_FLASH_ADDR, N22_FW_BIN_SIZE);
#endif
   // soc_printf("Boot N22!");
#endif
#if (ENABLE_DSP)
    boot_cpu2(DSP_IRAM_FW_DOWNLOAD_FLASH_ADDR, DSP_DRAM_FW_DOWNLOAD_FLASH_ADDR);
    soc_printf("Boot DSP!");
#endif

#if (TEST_MAILBOX)
    core_interrupt_enable();

    hipcm.instance = IPCM;
    drv_ipcm_init(&hipcm);
    drv_ipcm_register_cb(&hipcm, ipcm_callback);
    drv_hw_int_enable(IPCM_IRQn);

    soc_printf("cpu0 ipcm init ok!\r\n");
    drv_ipcm_send_msg(&hipcm, IPCM_CPU_1, 0x5a5a5a5a);
#endif

    while (1) {
    }
}

/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
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

#if DEMO_MODE == NORMAL_MODE
uint8_t data[256];
uint8_t write_data[256];
uint8_t testdata[256] __attribute__((aligned(4)));
// log init
uart_handle_t uart_handle;


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
volatile uint32_t demo_test_addr = 0x100000;
void user_init(void)
{
#if defined(MCU_CORE_TL752X_D25F)
    flash_init(CPU_DMAC_CH5);
#else
    flash_init_n22_dsp(CPU_DMAC_CH5);
#endif
//    uint8_t sr[3];

    /* init uart */
    log_init(); // pa0 and pa1 are used by uart 1

    LOG_INF("nor flash demo%s\n", __TIME__);

   // LOG_INF("read csr mcache =0x%x\n", read_csr(NDS_MCACHE_CTL));

#if defined(MCU_CORE_TL752X_D25F)
    LOG_INF("enable xip\n");
    demo_test_addr += 0x8;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));
    demo_test_addr -= 0x8;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));
#endif
    LOG_INF("\nstart read flash jedec id\n");

    LOG_INF("jedec id =0x%x\n", flash_read_mid());

//    drv_nor_read_sr0(&driver_flash_dev, &sr[0]);
//    drv_nor_read_sr1(&driver_flash_dev, &sr[1]);
//    LOG_INF("sr[0]=0x%x sr[1]=0x%x\n", sr[0], sr[1]);

    // drv_nor_enable_quad(&driver_flash_dev);
    // drv_nor_read_sr0(&driver_flash_dev, &sr[0]);
    // drv_nor_read_sr1(&driver_flash_dev, &sr[1]);
    // LOG_INF("sr[0]=0x%x sr[1]=0x%x\n", sr[0], sr[1]);

    for (uint32_t index = 0; index < sizeof(testdata); index++) {
        testdata[index] = 0xa5;
    }
    flash_read_page(demo_test_addr, sizeof(testdata), testdata);

    for (uint32_t index = 0; index < sizeof(testdata); index++) {
        LOG_INF("%x ", testdata[index]);
    }
    LOG_INF("\n");

    LOG_INF("start flash sectore erase addr=0x%x\n", demo_test_addr);
    flash_erase_sector(demo_test_addr);

    LOG_INF("stad  read\n");
    flash_read_page(demo_test_addr, sizeof(testdata), testdata);

    for (uint32_t index = 0; index < sizeof(testdata); index++) {
        LOG_INF("%x ", testdata[index]);
    }
    LOG_INF("\n");

    for (uint32_t index = 0; index < sizeof(write_data); index++) {
        //        write_data[index] = rand();
        write_data[index] = index;
    }
    LOG_INF("write page\n");
    flash_page_program(demo_test_addr, sizeof(write_data), write_data);
#if defined(MCU_CORE_TL752X_D25F)
    demo_test_addr += 0x88;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));
    demo_test_addr -= 0x88;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));
#endif
    flash_read_page(demo_test_addr, sizeof(testdata), testdata);

    for (uint32_t index = 0; index < sizeof(testdata); index++) {
        LOG_INF("%x ", testdata[index]);
    }
    LOG_INF("\n");
    LOG_INF("disable xip \n");


//    drv_hw_cache_disable();
//    drv_dwc_ssi_xip_disable(&driver_dwc_ssi_handle);
    LOG_INF("quad  read\n");

//    drv_nor_fast_read_quad_output(&flash_dev, demo_test_addr, (uint8_t *)((uint32_t)data + MCUA_SYS_BUS_BASE), sizeof(data));
    flash_read_page(demo_test_addr, sizeof(data), data);

    LOG_INF("read from flash addr =0x%x \n", demo_test_addr);
    for (uint32_t index = 0; index < sizeof(data); index++) {
        LOG_INF("%x ", data[index]);
    }
    LOG_INF("\n");
    LOG_INF("enable xip\n");

//    drv_hw_cache_enable();
//    drv_dwc_ssi_xip_enable(&dwc_ssi_handle);
#if defined(MCU_CORE_TL752X_D25F)
    demo_test_addr += 0x8;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));
    demo_test_addr -= 0x8;
    LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE, *((uint32_t *)(demo_test_addr + FLASH0_BASE)));

    for (uint32_t index = 0; index < sizeof(data);) {
        LOG_INF("xip read addr =0x%x data=0x%x\n", demo_test_addr + FLASH0_BASE + index, *((uint32_t *)(demo_test_addr + FLASH0_BASE + index)));
        index += 4;
    }
#endif
}

void main_loop(void)
{

}

#endif


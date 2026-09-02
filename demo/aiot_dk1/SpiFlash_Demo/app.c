/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2026
 *
 * @par     Copyright (c) 2026, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "external_flash/FlashDevice_Driver.h"
#define EXPECT_CHIP_ID 0x8515
#define BUFFER_SIZE 4096

uint8_t buffer[BUFFER_SIZE] = {0};
uint8_t buffer1[BUFFER_SIZE] = {0};

typedef struct {
    const char *name;
    int (*func)(void);
}test_unit_t;

static int test_chip_id(void)
{
    uint16_t chip_id = flash_device_chip_id_get();
    if(chip_id != EXPECT_CHIP_ID){
        printf("chip_id error: 0x%04x != 0x%04x\n", chip_id, EXPECT_CHIP_ID);
        return -1;
    }
    return 0;
}

static int test_erase_sector(void)
{
    flash_device_erase_sector(0x10000);
    memset(buffer1, 0xff, sizeof(buffer1));
    flash_device_read_data(0x10000, buffer, sizeof(buffer));
    if(memcmp(buffer, buffer1, sizeof(buffer)) != 0){
        printf("erase sector error\n");
        return -1;
    }
    return 0;
}

static int test_write_data(void)
{
    for(uint32_t i = 0; i < sizeof(buffer); i++){
        buffer[i] = i;
    }
    flash_device_write_data(0x10000, buffer, sizeof(buffer));
    flash_device_read_data(0x10000, buffer1, sizeof(buffer1));
    if(memcmp(buffer, buffer1, sizeof(buffer)) != 0){
        printf("write data error\n");
        return -1;
    }
    return 0;
}


static const test_unit_t test_units[] = {
    {"chip_id", test_chip_id},
    {"erase_sector", test_erase_sector},
    {"write_data", test_write_data},
};

#define TEST_PASS_LED   PIN_D2
#define TEST_FAIL_LED   PIN_D1

void user_init(void)
{
    gpio_function_en(TEST_PASS_LED);
    gpio_function_en(TEST_FAIL_LED);
    gpio_output_en(TEST_PASS_LED);
    gpio_output_en(TEST_FAIL_LED);
    gpio_set_low_level(TEST_PASS_LED);
    gpio_set_low_level(TEST_FAIL_LED);


    FlashDevice_Config_t config = {
        .speed = FLASH_SPI_SPEED,
    };
    flash_device_interface_init(&config);
    
    uint32_t total_case = sizeof(test_units)/sizeof(test_units[0]);
    uint32_t passed_case = 0;
    uint32_t failed_case = 0;
    uint32_t start_time = stimer_get_tick();

    for(uint32_t i = 0; i < total_case; i++){
        printf(">> Test<%ld> %s...", i, test_units[i].name);
        uint32_t case_start_time = stimer_get_tick();
        int ret = test_units[i].func();
        printf("[%ld us]", (stimer_get_tick() - case_start_time) / SYSTEM_TIMER_TICK_1US);
        if(ret != 0){
            printf("[Fail]\n");
            failed_case++;
        } else {
            printf("[Pass]\n");
            passed_case++;
        }
    }

    if(failed_case > 0) {
        gpio_set_high_level(TEST_FAIL_LED);
    } else {
        gpio_set_high_level(TEST_PASS_LED);
    }
    printf("Summary: %ld passed, %ld failed, total time: %ld us\n", passed_case, failed_case, (stimer_get_tick() - start_time) / SYSTEM_TIMER_TICK_1US);
}


void main_loop(void)
{
   
}


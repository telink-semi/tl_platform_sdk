/********************************************************************************************************
 * @file    FlashDevice_Driver.h
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#ifndef __FLASH_DEVICE_DRIVER_H__
#define __FLASH_DEVICE_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "FlashDevice_Interface.h"
typedef enum{
        FlashDeviceCmd_WriteStatusReg   = 0x01,
        FlashDeviceCmd_PageProgram      = 0x02,
        FlashDeviceCmd_ReadData         = 0x03,
        FlashDeviceCmd_WriteDisable     = 0x04,
        FlashDeviceCmd_ReadStatusReg    = 0x05,
        FlashDeviceCmd_WriteEnable      = 0x06,
        FlashDeviceCmd_FastReadData     = 0x0B,
        FlashDeviceCmd_SectorErase      = 0x20,
        FlashDeviceCmd_ManufactDeviceID = 0x90,
        FlashDeviceCmd_JedecDeviceID    = 0x9F,
        FlashDeviceCmd_ReleasePowerDown = 0xAB,
        FlashDeviceCmd_PowerDown        = 0xB9,
        FlashDeviceCmd_ChipErase        = 0xC7,
}FlashDeviceCmd_Type;

#define FLASH_DEVICE_PAGE_SIZE           (256)
#define FLASH_DEVICE_SECTOR_SIZE         (4096)
#define FLASH_DEVICE_SECTOR_COUNT        (FLASH_DEVICE_TOTAL_SIZE / FLASH_DEVICE_SECTOR_SIZE)
#define FLASH_DEVICE_TOTAL_SIZE          (16 * 1024 * 1024)
#define FLASH_DEVICE_BUSY_TIMEOUT_VALUE   (0x50000)

typedef struct {
    uint32_t speed;
}FlashDevice_Config_t;


void    flash_device_interface_init(FlashDevice_Config_t *config);
uint16_t     flash_device_chip_id_get(void);
uint32_t     flash_device_jedec_id_get(void);
void    flash_device_erase_sector(uint32_t addr);
void    flash_device_erase_chip(void);
void    flash_device_power_state_set(bool state);
uint32_t     flash_device_write_data(uint32_t addr, uint8_t *pdata, uint32_t length);
uint32_t     flash_device_read_data(uint32_t addr, uint8_t *pdata, uint32_t length);


#endif


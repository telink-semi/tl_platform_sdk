/********************************************************************************************************
 * @file    FlashDevice_Driver.c
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

#include "FlashDevice_Driver.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * flash device driver apis
 */
void flash_device_interface_init(FlashDevice_Config_t *config){
    FlashDevice_Interface_Init(0, config->speed);
     
}

void flash_device_interface_write(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length){
    FlashDevice_Interface_Write(cmd_data, cmd_length, pdata, length);
}

void flash_device_interface_read(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length){
    FlashDevice_Interface_Read(cmd_data, cmd_length, pdata, length);
}

/*
 * flash device apis
 */
uint8_t   flash_device_status_get(void){
    uint8_t status;
    uint8_t command = FlashDeviceCmd_ReadStatusReg;
    flash_device_interface_read(&command, sizeof(command), &status, sizeof(status));
    return status;
}
volatile unsigned char  a_ret=0xff,a_ret1=0xff;;
bool flash_device_busy_wait(void){
    for(int index = 0; index < FLASH_DEVICE_BUSY_TIMEOUT_VALUE; index ++)
    {
        a_ret++;
        if( !(flash_device_status_get() & 0x01) )

            //a_ret1=flash_device_status_get();
            return true;
        }
    return false;
}

void flash_device_write_command(uint8_t command){
    flash_device_interface_write(&command, sizeof(command), NULL, 0);
    flash_device_busy_wait();
}

void flash_device_write_enable(void){
    flash_device_write_command(FlashDeviceCmd_WriteEnable);
}

void flash_device_write_disable(void){
    flash_device_write_command(FlashDeviceCmd_WriteDisable);
}

uint16_t  flash_device_chip_id_get(void){
    uint8_t cmd_data[] = {
            FlashDeviceCmd_ManufactDeviceID,
            0x00,
            0x00,
            0x00,
    };
    uint8_t chip_id[2] = {0x55, 0x55}; // [0] manufacturer_id  [1] device_id
    flash_device_interface_read(cmd_data, sizeof(cmd_data), chip_id, sizeof(chip_id));
    return (uint16_t)((chip_id[0] << 8) | chip_id[1]);
}

uint32_t  flash_device_jedec_id_get(void){
     uint8_t cmd_data[] = {
             FlashDeviceCmd_JedecDeviceID,
             0x00,
             0x00,
             0x00,
     };
     uint8_t jedec_id[3]; // [0] manufacturer_id  [1] memory_type_id  [2] capacity_id
     flash_device_interface_read(cmd_data, sizeof(cmd_data), jedec_id, sizeof(jedec_id));
     return (uint32_t)((jedec_id[0] << 16) | (jedec_id[1] << 8) | jedec_id[2]);
}

void flash_device_erase_sector(uint32_t addr){
     flash_device_write_enable();

     uint8_t cmd_data[] = {
             FlashDeviceCmd_SectorErase,
             addr >> 16,
             addr >> 8,
             addr >> 0,
     };
     flash_device_interface_write(cmd_data, sizeof(cmd_data), NULL , 0);

     flash_device_busy_wait();
}

void flash_device_erase_chip(void){
     flash_device_write_enable();
     flash_device_write_command(FlashDeviceCmd_ChipErase);
     while( flash_device_status_get() & 0x01 );
}

void flash_device_power_state_set(bool state){
     if( state == true ){
         flash_device_write_command(FlashDeviceCmd_ReleasePowerDown);
     }else{
         flash_device_write_command(FlashDeviceCmd_PowerDown);
     }
}

bool flash_device_write_page(uint32_t addr, uint8_t *pdata, uint32_t length){
     flash_device_write_enable();

     uint8_t cmd_data[] = {
             FlashDeviceCmd_PageProgram,
             addr >> 16,
             addr >> 8,
             addr >> 0,
     };
     flash_device_interface_write(cmd_data, sizeof(cmd_data), pdata, length);

     return flash_device_busy_wait();
}

uint32_t  flash_device_write_data(uint32_t addr, uint8_t *pdata, uint32_t length){
     uint32_t feasible_size    = length;
     uint32_t currentAddress   = addr;
     uint32_t currentEndOfPage = (currentAddress / FLASH_DEVICE_PAGE_SIZE + 1) * FLASH_DEVICE_PAGE_SIZE - 1;

     if(length > (FLASH_DEVICE_TOTAL_SIZE - addr)) feasible_size = FLASH_DEVICE_TOTAL_SIZE - addr;

     uint32_t bytes_left_to_send = feasible_size;
     uint32_t bytes_written      = 0;

     while(bytes_written < feasible_size){
        if(currentAddress + bytes_left_to_send > currentEndOfPage) bytes_left_to_send = currentEndOfPage - currentAddress + 1;

        if(flash_device_write_page(currentAddress, pdata + bytes_written, bytes_left_to_send) == false) return false;

        bytes_written     += bytes_left_to_send;
        currentAddress     = currentEndOfPage + 1;
        currentEndOfPage  += FLASH_DEVICE_PAGE_SIZE;
        bytes_left_to_send = feasible_size - bytes_written;
     }

     return bytes_written;
}

uint32_t  flash_device_read_data(uint32_t addr, uint8_t *pdata, uint32_t length){
     uint8_t cmd_data[] = {
             FlashDeviceCmd_ReadData,
             addr >> 16,
             addr >> 8,
             addr >> 0,
     };
     flash_device_interface_read(cmd_data, sizeof(cmd_data), pdata, length);
     return length;
}




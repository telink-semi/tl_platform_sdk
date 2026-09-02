/********************************************************************************************************
 * @file    FlashDevice_Interface.h
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
#ifndef FLASHDEVICE_INTERFACE_H_
#define FLASHDEVICE_INTERFACE_H_

#include <inttypes.h>

void FlashDevice_Interface_Init(uint8_t mode, uint32_t speed);
void FlashDevice_Interface_Write(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length);
void FlashDevice_Interface_Read(uint8_t *cmd_data, uint32_t cmd_length, uint8_t *pdata, uint32_t length);

#endif /* FLASHDEVICE_INTERFACE_H_ */


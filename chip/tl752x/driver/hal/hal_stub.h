/********************************************************************************************************
 * @file    hal_stub.h
 *
 * @brief   This is the header file for tl752x
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

#ifndef _HAL_STUB_H_
#define _HAL_STUB_H_

#include "bit.h"
#include "compiler.h"
#include "tl_chip.h"

/* ANA API stub */
_always_inline unsigned char analog_read_reg8(unsigned int addr){ (void)addr; return 0;}
_always_inline void analog_write_reg8(unsigned int addr, unsigned char data){(void)addr; (void)data; }
_always_inline unsigned short analog_read_reg16(unsigned int addr){(void)addr; return 0;}
_always_inline void analog_write_reg16(unsigned int addr, unsigned short data){(void)addr;(void)data; }
_always_inline unsigned int analog_read_reg32(unsigned int addr){(void)addr; return 0;}
_always_inline void analog_write_reg32(unsigned int addr, unsigned int data){(void)addr; (void)data;}
_always_inline void analog_read_buff(unsigned int addr, unsigned char *buff, unsigned char len){(void)addr; (void)buff;(void)len;}
_always_inline void analog_write_buff(unsigned int addr, unsigned char *buff, unsigned char len){(void)addr; (void)buff;(void)len;}

/* PM API stub */
_always_inline void pm_set_dig_module_power_switch(unsigned int module, unsigned int power_sel){(void)module;(void)power_sel;}

/* WDT API stub */
_always_inline void wd_start(void){}
_always_inline void wd_stop(void){}


#endif

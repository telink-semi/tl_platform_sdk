/********************************************************************************************************
 * @file    usb1_port.h
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

#ifndef __USB1_PORT_H__
#define __USB1_PORT_H__

#if 0
#include "mtime.h"
#endif
#include <wchar.h>

#define USB_PORT_GPIO_DEBUG_EN                 1

#include "modules/drv_gpio.h"
#include "inc/drv_cpr.h"

#define usb1_port_power_on_en(en)

//dp dm pinmux ,input config
void usb1_port_pin_func_config(void);
void usb1_port_dp_pullup_en(int en);

#if 0
#define stimer_get_tick()                      ((unsigned int)mtime_get_value())
#define clock_time_exceed(ref_tick, val)       ((unsigned int)(mtime_get_value() - ref_tick) > (val * 32/1000))
#define delay_us(val)                          {\
                                                unsigned int t = stimer_get_tick();\
                                                while(!clock_time_exceed(t, val)) {\
                                                    __NOP();\
                                                }}
#endif
#endif

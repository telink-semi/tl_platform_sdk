/*******************************************************************************************************
 *
 * @file    driver.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "driver.h"

#include "tl_chip.h"
#include "boot_core/boot_cpu1.h"
#include "boot_core/boot_cpu2.h"
#include "bt/bt_rf.h"
#include "bt/drv_rf.h"
#include "hal/clic.h"
#include "hal/hal_aes.h"
#include "hal/hal_audio.h"
#include "hal/hal_charger.h"
#include "hal/hal_clock.h"
#include "hal/hal_emi.h"
#include "hal/hal_dma.h"
#include "hal/hal_drv_tahdt.h"
#include "hal/hal_flash.h"
#include "hal/hal_gpio.h"
#include "hal/hal_mailbox.h"
#include "hal/hal_plic.h"
#include "hal/hal_pm.h"
#include "hal/hal_rf_ble.h"
#include "hal/hal_rf_common.h"
#include "hal/hal_rf_dma.h"
#include "hal/hal_rf_private.h"
#include "hal/hal_rf_reg.h"
#include "hal/hal_rf_tahdt.h"
#include "hal/hal_tahdt_reg.h"
#include "hal/hal_stub.h"
#include "hal/hal_sys.h"
#include "hal/hal_systimer.h"
#include "hal/hal_timer.h"
#include "hal/hal_trng.h"
#include "hal/hal_uart.h"
#include "hal/hal_wdt.h"
#include "hal/hal_rtc.h"
#include "hal/mcu_core.h"
#include "hal/mtime.h"
#include "hal/plic.h"
#include "hal/plic_sw.h"
#include "hal/usb1hw.h"
#include "hal/usb1_port.h"
#include "hal/hal_efuse.h"
#include "hal/hal_adc.h"

#include "reg/register.h"
#include "arch/arch.h"
#include "modules/modules.h"
#include "inc/inc.h"

#endif

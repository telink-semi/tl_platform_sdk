/********************************************************************************************************
 * @file    print_app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "app_config.h"
#if(USB_DEMO_TYPE==USB_PRINT)
#include "application/usbstd/usb.h"

#if defined(MCU_CORE_B92)||defined (MCU_CORE_TL7518) || defined(MCU_CORE_TL751X)
extern volatile unsigned int g_vbus_timer_turn_off_start_tick;
extern volatile unsigned int g_vbus_timer_turn_off_flag;
#endif
static unsigned int t1 = 0;
void user_init(void)
{
    //enable USB manual interrupt(in auto interrupt mode,USB device would be USB printer device)
    usb_init();
    //enable USB endpoint 8 FIFO mode
    usbhw_set_printer_threshold(1);
    usbhw_set_ep8_fifo_mode();
    //enable USB DP pull up 1.5k
    usb_set_pin(1);
}

/* enum to USB input device and simulate the left click and right click of mouse */
void main_loop (void)
{
/**
 * @attention   When using the vbus (not vbat) power supply, you must turn off the vbus timer,
 *              otherwise the MCU will be reset after 8s.
*/
#if( (defined(MCU_CORE_B92)||defined(MCU_CORE_TL7518)||defined(MCU_CORE_TL751X))&& (POWER_SUPPLY_MODE == VBUS_POWER_SUPPLY))
    /**
     *When using the vbus (not vbat) power supply, the vbus detect status remains at 1. Conversely, it is 0.
     */
if(usb_get_vbus_detect_status())
{
    if(clock_time_exceed(g_vbus_timer_turn_off_start_tick, 100*1000) && (g_vbus_timer_turn_off_flag == 0))
    {
        /**
         * wd_turn_off_vbus_timer() is used to turn off the 8s vbus timer.
         * The vbus detect status will not be clear to 0.
         */
        wd_turn_off_vbus_timer();
        g_vbus_timer_turn_off_flag = 1;
    }
}
else
{
    g_vbus_timer_turn_off_start_tick = stimer_get_tick();
    g_vbus_timer_turn_off_flag = 0;
}
#endif

    usb_handle_irq();
    if(g_usb_config != 0)
    {
        if (clock_time_exceed(t1, 500000))
        {
            t1 = stimer_get_tick() | 1;
            printf(" Hello World! \n");
        }
    }
}

#endif

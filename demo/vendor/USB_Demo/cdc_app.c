/********************************************************************************************************
 * @file    cdc_app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2019
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
#include "app_config.h"
#if (USB_DEMO_TYPE == USB_CDC)
#include "application/usb_app/usbcdc.h"
#include "application/usbstd/usb.h"

#if defined(MCU_CORE_B92)||defined (MCU_CORE_TL751X) || defined(MCU_CORE_B931)
extern volatile unsigned int g_vbus_timer_turn_off_start_tick;
extern volatile unsigned int g_vbus_timer_turn_off_flag;
#endif

void user_init(void)
{
    usb_init();

    /* set data endpoint buffer size and addr */
    usbhw_set_eps_max_size(CDC_TXRX_EPSIZE); /* max 64 */
    usbhw_set_ep_addr(CDC_NOTIFICATION_EPNUM, 0x00);
    usbhw_set_ep_addr(USB_PHYSICAL_EDP_CDC_IN, CDC_NOTIFICATION_EPSIZE);
    usbhw_set_ep_addr(USB_PHYSICAL_EDP_CDC_OUT, CDC_NOTIFICATION_EPSIZE + CDC_TXRX_EPSIZE);

#if ( !defined(MCU_CORE_B91) && !defined(MCU_CORE_B92) && (USB_MAP_EN == 1) )
    /* When map enable, for the device side, there are three physical endpoints: notify endpoint 2, IN endpoint 4 and OUT endpoint 5. */
    usbhw_ep_map_en(EP_MAP_AUTO_EN);
    usbhw_set_eps_map_en(BIT(USB_PHYSICAL_EDP_CDC_OUT));
    /* enable data endpoint CDC_NOTIFICATION_EPNUM and USB_PHYSICAL_EDP_CDC_OUT. */
    usbhw_set_eps_en(BIT(CDC_NOTIFICATION_EPNUM) | BIT(USB_PHYSICAL_EDP_CDC_OUT));
    /* host sends data to logical endpoint 5, because our physical endpoint supports OUT, the physical endpoint and logical endpoint are the same, no mapping is needed. \n
     * host get data from logical endpoint 5, because our physical endpoints only support OUT, then you need to logical endpoint 5 mapping to any physical endpoint that supports IN,
     * the software only needs to configure the mapping relationship, the hardware will parse itself!
     */
    usbhw_set_ep_map(USB_PHYSICAL_EDP_CDC_OUT, USB_PHYSICAL_EDP_CDC_IN);
#else
    /* enable data endpoint CDC_NOTIFICATION_EPNUM, USB_PHYSICAL_EDP_CDC_IN and USB_PHYSICAL_EDP_CDC_OUT. */
    usbhw_set_eps_en(BIT(CDC_NOTIFICATION_EPNUM) | BIT(USB_PHYSICAL_EDP_CDC_IN) | BIT(USB_PHYSICAL_EDP_CDC_OUT));
#endif

#if (USB_ENUM_IN_INTERRUPT == 1)
    /* enable global interrupt */
    core_interrupt_enable();
    /* enable sof irq */
    usbhw_set_irq_mask(USB_IRQ_SOF_MASK);
    plic_interrupt_enable(IRQ_USB_250US_OR_SOF);
#endif

    // enable USB DP pull up 1.5k
    usb_set_pin_en();
}

void main_loop(void)
{
    /**
     * @attention   When using the vbus (not vbat) power supply, you must turn off the vbus timer,
     *              otherwise the MCU will be reset after 8s.
     */
#if (defined(MCU_CORE_B92)||defined (MCU_CORE_TL751X) || defined(MCU_CORE_B931) && (POWER_SUPPLY_MODE == VBUS_POWER_SUPPLY))
    /**
     *When using the vbus (not vbat) power supply, the vbus detect status remains at 1. Conversely, it is 0.
     */
    if (usb_get_vbus_detect_status())
    {
        if (clock_time_exceed(g_vbus_timer_turn_off_start_tick, 100 * 1000) && (g_vbus_timer_turn_off_flag == 0))
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
    
    if (usb_cdc_data_len != 0)
    {
        usb_cdc_tx_data_to_host(usb_cdc_data, usb_cdc_data_len);
        usb_cdc_data_len = 0;
    }
}

#endif

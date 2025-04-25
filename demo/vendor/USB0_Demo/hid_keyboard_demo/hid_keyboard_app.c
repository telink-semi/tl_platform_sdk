/********************************************************************************************************
 * @file    hid_keyboard_app.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
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
#include "common.h"
#if (USB_DEMO_TYPE == USB_KEYBOARD)
#include "tl_usb/class/hid/usbd_hid.h"
#include "hid_keyboard_descriptor.h"

volatile char a_send_flag = 0;
unsigned char data[8];

static usbd_driver_t usbd_keyboard_driver;

void usbd_hid_int_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    usb_log("usbd keyboard send complete callback ep_addr = %d, len = %d\r\n", ep_addr, len);
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    usbd_keyboard_driver.driver_num          = 0;
    usbd_keyboard_driver.usbd_driver_handler = usbd_hid_interface_request_handler;
    usbd_driver_register(0, &usbd_keyboard_driver, 0, HID_KEYBOARD_IN_ENDPOINT_ADDRESS);
    usbd_endpoint_register(0, HID_KEYBOARD_IN_ENDPOINT_ADDRESS, usbd_hid_int_callback);

    usb0hw_init(USB0_SPEED_HIGH);
    usb0hw_set_grxfsiz(0x100);
    usb0hw_set_epin_size(USB0_EP0, 0x100, 64);
    usb0hw_set_epin_size(USB0_EP1, 0x100 + 64, 64);

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB0);
}

void main_loop(void)
{
    gpio_toggle(LED1);
    delay_ms(500);

    if (a_send_flag == 1) {
        a_send_flag = 0;
        data[0]     = 0;
        data[1]     = 0;
        data[2]     = 0;
        data[3]     = 0;
        data[4]     = 0x59; // number key: 1
        data[5]     = 0;    // number key: 2
        data[6]     = 0;
        data[7]     = 0;
        usb0hw_remote_wakeup();
        usbd_ep_write(0, HID_KEYBOARD_IN_ENDPOINT_ADDRESS, data, 8);
        delay_ms(1000);
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
        data[4] = 0; // number key: 1
        data[5] = 0; // number key: 2
        data[6] = 0;
        data[7] = 0;
        usb0hw_remote_wakeup();
        usbd_ep_write(0, HID_KEYBOARD_IN_ENDPOINT_ADDRESS, data, 8);
    }
}

#endif

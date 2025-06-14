/********************************************************************************************************
 * @file    hid_mouse_app.c
 *
 * @brief   This is the header file for Telink RISC-V MCU
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
#if (USB_DEMO_TYPE == USB_MOUSE)
#define USB_MOUSE_DRAW_SQUARE 1
#include "tl_usb/class/hid/usbd_hid.h"
#include "hid_mouse_descriptor.h"

static usbd_driver_t usbd_mouse_driver;
static volatile char g_send_flag = 0;
static unsigned char hid_report_data[5];

static void led_toggle(void);

#if USB_MOUSE_DRAW_SQUARE
#define SQUARE_SIDE_LENGTH 200
#define SIDE_STEPS         200
_attribute_ram_code_sec_ void usbd_hid_int_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    usb_log("usbd mouse send complete callback ep_addr = %d, len = %d\r\n", ep_addr, len);

    static int step = 0;
    static int side = 0;
    int        dx   = 0;
    int        dy   = 0;
    switch (side) {
    case 0:
        dx = 1;
        break;
    case 1:
        dy = 1;
        break;
    case 2:
        dx = -1;
        break;
    case 3:
        dy = -1;
        break;
    }

    hid_report_data[2] = dx;
    hid_report_data[3] = dy;
    usbd_ep_write(0, HID_MOUSE_IN_ENDPOINT_ADDRESS, hid_report_data, 5);
    step++;
    if (step > SIDE_STEPS) {
        step = 0;
        side = (side + 1) % 4;
    }
}
#else
_attribute_ram_code_sec_ void usbd_hid_int_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    usb_log("usbd mouse send complete callback ep_addr = %d, len = %d\r\n", ep_addr, len);
}
#endif

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    usbd_mouse_driver.driver_num          = 0;
    usbd_mouse_driver.usbd_driver_handler = usbd_hid_interface_request_handler;
    usbd_driver_register(0, &usbd_mouse_driver, 0, HID_MOUSE_IN_ENDPOINT_ADDRESS);
    usbd_endpoint_register(0, HID_MOUSE_IN_ENDPOINT_ADDRESS, usbd_hid_int_callback);

    /* USB0 digital voltage must be 1.1V and HCLK min's 48M. */
    pm_set_dig_ldo(DIG_VOL_1V1_MODE, 1000);
    PLL_192M_D25F_96M_HCLK_N22_48M_PCLK_48M_MSPI_48M;

#if USB_HIGH_SPEED_EN
    usb0hw_init(USB0_SPEED_HIGH);
#else
    usb0hw_init(USB0_SPEED_FULL);
#endif
    usb0hw_set_grxfsiz(0x100);
    usb0hw_set_epin_size(USB0_EP0, 0x100, 64);
    usb0hw_set_epin_size(USB0_EP2, 0x100 + 64, 64);

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB0);
}

void main_loop(void)
{
    led_toggle();

#if USB_MOUSE_DRAW_SQUARE
    if (g_send_flag == 1) {
        g_send_flag = 0;
        delay_ms(5000); // prepare capture
        hid_report_data[0] = 1;
        hid_report_data[1] = 0;
        hid_report_data[2] = 0;
        hid_report_data[3] = 0;
        hid_report_data[4] = 0;
        usb0hw_remote_wakeup();
        usbd_ep_write(0, HID_MOUSE_IN_ENDPOINT_ADDRESS, hid_report_data, 5);
    }
#else
    if (g_send_flag == 1) {
        g_send_flag        = 0;
        hid_report_data[0] = 1;
        hid_report_data[1] = 2;
        hid_report_data[2] = 0;
        hid_report_data[3] = 0;
        hid_report_data[4] = 0;
        usb0hw_remote_wakeup();
        usbd_ep_write(0, HID_MOUSE_IN_ENDPOINT_ADDRESS, hid_report_data, 5);
        delay_ms(1000);
        hid_report_data[0] = 1;
        hid_report_data[1] = 0;
        hid_report_data[2] = 0;
        hid_report_data[3] = 0;
        hid_report_data[4] = 0;
        usb0hw_remote_wakeup();
        usbd_ep_write(0, HID_MOUSE_IN_ENDPOINT_ADDRESS, hid_report_data, 5);
    }
#endif
}

static void led_toggle(void)
{
    static unsigned int start_time = 0;

    if (stimer_get_tick() - start_time < 500 * SYSTEM_TIMER_TICK_1MS) {
        return;
    }

    start_time += 500 * SYSTEM_TIMER_TICK_1MS;
    gpio_toggle(LED1);
}
#endif

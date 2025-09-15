/********************************************************************************************************
 * @file    cdc_app_app.c
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
#if (USB_DEMO_TYPE == USB_CDC)
#include "tl_usb/class/cdc/usbd_cdc.h"
#include "cdc_descriptor.h"

static usbd_driver_t           usbd_cdc_driver;
static volatile char           g_send_flag = 0;
static unsigned char           cdc_in_buffer[CDC_DATA_IN_ENDPOINT_SIZE + 1];
static unsigned char           cdc_out_buffer[CDC_DATA_OUT_ENDPOINT_SIZE];
static volatile unsigned char  cdc_epin_busy = false;
static volatile unsigned short cdc_out_data_len;

static void led_toggle(void);

static void usbd_cdc_epin_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    cdc_epin_busy = false;
    usb_log("usbd cdc in complete callback ep_addr = %d, len = %d\r\n", ep_addr, len);
}

static void usbd_cdc_epout_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
    usb_log("usbd cdc out complete callback ep_addr = %d, len = %d\r\n", ep_addr, len);
    cdc_out_data_len = len;
}

static void usbd_cdc_ep_notify_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;
}

void usbd_set_configuration_callback(unsigned char bus, unsigned char config_num)
{
    (void)bus;
    (void)config_num;
    usb_log("usb set config callback\r\n");

    /* receive first cdc out cdc_in_buffer. */
    usbd_ep_read(bus, CDC_DATA_OUT_ENDPOINT_ADDRESS, cdc_out_buffer, sizeof(cdc_out_buffer));
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    usbd_cdc_driver.driver_num          = 0;
    usbd_cdc_driver.usbd_driver_handler = usbd_cdc_interface_request_handler;
    usbd_driver_register(0, &usbd_cdc_driver, 0, CDC_NOTIFICATION_IN_ENDPOINT_ADDRESS);
    usbd_driver_register(0, &usbd_cdc_driver, 1, CDC_DATA_OUT_ENDPOINT_ADDRESS);
    usbd_driver_register(0, &usbd_cdc_driver, 1, CDC_DATA_IN_ENDPOINT_ADDRESS);
    usbd_endpoint_register(0, CDC_DATA_IN_ENDPOINT_ADDRESS, usbd_cdc_epin_callback);
    usbd_endpoint_register(0, CDC_DATA_OUT_ENDPOINT_ADDRESS, usbd_cdc_epout_callback);
    usbd_endpoint_register(0, CDC_NOTIFICATION_IN_ENDPOINT_ADDRESS, usbd_cdc_ep_notify_callback);

    for (unsigned int i = 0; i < sizeof(cdc_in_buffer) / sizeof(cdc_in_buffer[0]); i++)
    {
        cdc_in_buffer[i] = i & 0xff;
    }

    /* USB0 digital voltage must be 1.1V and HCLK min's 48M. */
    pm_set_dig_ldo(DIG_VOL_1V1_MODE, 1000);
    PLL_192M_D25F_96M_HCLK_N22_48M_PCLK_48M_MSPI_48M;

#if USB_HIGH_SPEED_EN
    usb0hw_init(USB0_SPEED_HIGH);
#else
    usb0hw_init(USB0_SPEED_FULL);
#endif
    usb0hw_set_grxfsiz(0x100);
    usb0hw_set_epin_size(USB0_EP0, 0x100, 16);
    usb0hw_set_epin_size(CDC_NOTIFICATION_IN_ENDPOINT_ADDRESS & 0x7f, 0x100 + 16, 16);
    usb0hw_set_epin_size(CDC_DATA_IN_ENDPOINT_ADDRESS & 0x7f, 0x100 + 16 + 16, 64);

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB0);

}

void main_loop(void)
{
    led_toggle();

    /* echo */
    if (cdc_out_data_len) {
        cdc_epin_busy = true;
        usbd_ep_write(0, CDC_DATA_IN_ENDPOINT_ADDRESS, cdc_out_buffer, cdc_out_data_len);
        while (cdc_epin_busy) {
        }
        /* receive next cdc out cdc_in_buffer. */
        cdc_out_data_len = 0;
        usbd_ep_read(0, CDC_DATA_OUT_ENDPOINT_ADDRESS, cdc_out_buffer, sizeof(cdc_out_buffer));
    }

    /* only in */
    if (g_send_flag == 1) {
        g_send_flag   = 0;
        cdc_epin_busy = true;
        usbd_ep_write(0, CDC_DATA_IN_ENDPOINT_ADDRESS, cdc_in_buffer, CDC_DATA_IN_ENDPOINT_SIZE);
        while (cdc_epin_busy) {
        }
        cdc_epin_busy = true;
        usbd_ep_write(0, CDC_DATA_IN_ENDPOINT_ADDRESS, cdc_in_buffer, CDC_DATA_IN_ENDPOINT_SIZE);
        while (cdc_epin_busy) {
        }
    }
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

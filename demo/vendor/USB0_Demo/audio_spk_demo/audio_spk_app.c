/********************************************************************************************************
 * @file    audio_spk_app.c
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
#if (USB_DEMO_TYPE == USB_SPEAKER)

    #include "tl_usb/class/audio/usbd_audio.h"
    #include "audio_spk_descriptor.h"

static usbd_driver_t usbd_spk_driver;

    #define AUDIO_FREQ       16000
    #define IN_CHANNEL_NUM   2
    #define AUDIO_OUT_PACKET ((uint32_t)((AUDIO_FREQ * 2 * IN_CHANNEL_NUM) / 1000))

__attribute__((aligned(8))) unsigned char audio_buffer[AUDIO_OUT_PACKET];
static void led_toggle(void);

void usbd_audio_open(unsigned char bus, unsigned char intf)
{
    (void)bus;
    (void)intf;

    /* receive first cdc out data. */
    usbd_ep_read(0, AUDIO_SPK_OUT_ENDPOINT_ADDRESS, audio_buffer, sizeof(audio_buffer));
}

void usbd_audio_close(unsigned char bus, unsigned char intf)
{
    (void)bus;
    (void)intf;
}

void usbd_audio_epout_callback(unsigned char bus, unsigned char ep_addr, unsigned int len)
{
    (void)bus;
    (void)ep_addr;
    (void)len;

    /* receive cdc out data. */
    usbd_ep_read(0, AUDIO_SPK_OUT_ENDPOINT_ADDRESS, audio_buffer, sizeof(audio_buffer));
}

unsigned char  mute;
unsigned short cur;
unsigned short min;
unsigned short max       = 0x1e00;
unsigned short res       = 0x0180;
unsigned char  send_data = 1;

unsigned char usbd_audio_interface_cb(unsigned char bus, usb_control_request_t const *setup)
{
    (void)bus;
    (void)setup;
    unsigned char entity_id;
    unsigned char control_selector;

    control_selector = U16_HIGH_BYTE(setup->wValue);
    entity_id        = U16_HIGH_BYTE(setup->wIndex);

    switch (entity_id) {
    case 2:
    {
        if (control_selector == AUDIO_FU_CTRL_MUTE) {
            usbd_ep_write(bus, 0, &mute, setup->wLength);
        } else if (control_selector == AUDIO_FU_CTRL_VOLUME) {
            /* code */
            switch (setup->bRequest) {
            case 0x81:
                usbd_ep_write(bus, 0, (unsigned char *)&cur, setup->wLength);
                break;
            case 0x82:
                usbd_ep_write(bus, 0, (unsigned char *)&min, setup->wLength);
                break;
            case 0x83:
                usbd_ep_write(bus, 0, (unsigned char *)&max, setup->wLength);
                break;
            case 0x84:
                usbd_ep_write(bus, 0, (unsigned char *)&res, setup->wLength);
                break;
            case 0x01:
                usbd_ep_read(bus, 0, (unsigned char *)&cur, setup->wLength);
                break;
            default:
                return false;
                break;
            }
        }

        break;
    }
    default:
        return false;
        break;
    }

    return true;
}

void user_init(void)
{
    gpio_function_en(LED1);
    gpio_output_en(LED1);
    gpio_input_dis(LED1);

    usbd_spk_driver.driver_num          = 0;
    usbd_spk_driver.usbd_driver_handler = usbd_audio_interface_request_handler;
    usbd_driver_register(0, &usbd_spk_driver, 0, 0xff);
    usbd_driver_register(0, &usbd_spk_driver, 1, AUDIO_SPK_OUT_ENDPOINT_ADDRESS);
    usbd_endpoint_register(0, AUDIO_SPK_OUT_ENDPOINT_ADDRESS, usbd_audio_epout_callback);

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

    core_interrupt_enable();
    plic_interrupt_enable(IRQ_USB0);
}

void main_loop(void)
{
    led_toggle();
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

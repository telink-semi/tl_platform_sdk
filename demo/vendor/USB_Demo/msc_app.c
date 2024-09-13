/********************************************************************************************************
 * @file    msc_app.c
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
#if defined(MCU_CORE_B91)
#if((USB_DEMO_TYPE==USB_MASS_STORAGE))
#include "usb_default.h"
#include "application/usbstd/usb.h"
#include "../3rd-party/tiny_usb/tusb.h"
#include "application/mass_storage/spi_sdnand_driver/sdcard.h"

extern void dcd_int_handler(unsigned char rhport);
_attribute_ram_code_sec_ void  usb_endpoint_irq_handler (void)
{
    dcd_int_handler(0);
}
PLIC_ISR_REGISTER(usb_endpoint_irq_handler, IRQ_USB_ENDPOINT)

extern   unsigned int  sdcardblocknum;

void user_init(void)
{
#if (SD_NAND_FLASH_SUPPORT)
            while(sd_nand_flash_init())
            {
                delay_ms(500);
            }
            sdcardblocknum=SD_GetSectorCount();
#endif


            tusb_init();
            usb_init();
            /* enable data endpoint USB_EDP_MS_IN and USB_EDP_MS_OUT. */
            usbhw_set_eps_en(BIT(USB_EDP_MS_IN & 7) | BIT(USB_EDP_MS_OUT));

            usbhw_set_eps_max_size(64); /* max 64 */

            usbhw_set_ep_addr(USB_EDP_MS_IN, 0x00);
            usbhw_set_ep_addr(USB_EDP_MS_OUT, 0x40);

            usbhw_set_eps_irq_mask(BIT(USB_EDP_MS_IN & 7)|BIT(USB_EDP_MS_OUT));

            plic_interrupt_enable(IRQ_USB_ENDPOINT);
            core_interrupt_enable();
            usb_set_pin(1);


}
void main_loop (void)
{
    usb_handle_irq();
    tud_task();
}

#endif
#endif

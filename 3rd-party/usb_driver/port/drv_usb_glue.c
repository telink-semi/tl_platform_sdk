/*******************************************************************************************************
 *
 * @file    drv_usb_glue.c
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
/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\drv_usb_glue.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "drv_usb_glue.h"
#include "inc/drv_cpr.h"
#include "inc/drv_pmu.h"
#include "inc/drv_sys_ctl.h"
#include "modules/drv_gpio.h"
#include "usb_conf.h"
#include "usb_regs.h"
#include "usb_defines.h"

gpio_init_t usb_gpio;
volatile uint32_t usb_sys_clk = 48000000;
#ifdef USB_CFG_DEBUG_ENABLE
USB_MEM_ALIGNX usb_core_regs_t usb_core_regs;
#endif

/**
* @brief  get mclk0 freq
*
* @param  none
* @return freq
* @note   none
*/
uint32_t usb_mclk0_g_freq(void)
{
    return drv_cpr_get_mclk0_freq();
}

/**
* @brief  This function provides delay time in milli sec
*
* @param  usec: Value of delay required in microsecond
* @return none
* @note   none
*/
void usb_delay_us(uint32_t usec)
{
    volatile uint32_t count = 0;
    volatile uint32_t utime = ((usb_sys_clk / 1000000) * usec / 7);
    do {
        if (++count > utime) {
            return;
        }
    } while (1);
}

/**
* @brief  This function provides delay time in milli sec
*
* @param  msec: Value of delay required in milli sec
* @return none
* @note   none
*/
void usb_delay_ms(uint32_t msec)
{
    usb_delay_us(msec * 1000);
}

/**
* @brief  usb init
*
* @param  none
* @return none
* @note   none
*/
void usb_low_level_init(void)
{
    cpr_chip_info_t chip_info;
#if USB_CFG_USE_USB
#ifdef USB_CFG_USE_OTG_MODE
#ifdef USB_CFG_IP_CONIDSTS_ENABLE
    drv_sysctl_usb_idpad_set();
#endif
#ifdef USB_CFG_SOFTWARE_CONIDSTS_ENABLE
    usb_gpio.port = GPIO_PORT_B;
    usb_gpio.pin = GPIO_PIN_6;
    usb_gpio.mode = MODE_INPUT;
    usb_gpio.pull = GPIO_PULLUP;
    usb_gpio.alternate = GPIO_ALTERNATE_DEFAULT;
    drv_gpio_init(&usb_gpio);
#endif
#endif

#if (defined USB_CFG_USE_OTG_MODE) || (defined USB_CFG_USE_HOST_MODE)
    usb_gpio.port = GPIO_PORT_B;
    usb_gpio.pin = GPIO_PIN_7;
    usb_gpio.mode = MODE_OUTPUT;
    usb_gpio.pull = GPIO_PULLUP;
    usb_gpio.alternate = GPIO_ALTERNATE_DEFAULT;
    drv_gpio_init(&usb_gpio);
#endif
#endif

    __DRV_CPR_USB_PHY_RST_CLR(); /* reset phy */
    drv_pmu_set_usb_power_sw(DRV_SET);
    drv_cpr_get_chip_info(&chip_info);
    // USB_LOG_INFO("series: 0x%x\r\n", chip_info.series);
    // USB_LOG_INFO("version: 0x%x\r\n", chip_info.version);
    if ((chip_info.series == 0x9062) && (chip_info.version == 0)) {
        drv_pmu_rfpa_poweron(); /* 9062 a0 use rfpa power. turn on usb 3.3v volatage */
    }

    drv_cpr_usb_utmifs_clk48_sel(0); /* 0:double clk48M 1:mclk0 */
    drv_cpr_utmifs_clk48_set(0);     /* usb utmifs = 48M */
    drv_cpr_usb_clk_init();

    drv_sysctl_usb_cfg_set();

    usb_sys_clk = usb_mclk0_g_freq();

    drv_hw_int_enable(USB_IRQn);
}

/**
* @brief  usb deinit
*
* @param  none
* @return none
* @note   none
*/
void usb_low_level_deinit(void)
{
    drv_hw_int_disable(USB_IRQn);
    drv_cpr_usb_deinit();
}

/**
  * @brief  usb_drive_vbus
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */
void usb_drive_vbus(uint8_t state)
{
    /*
    On-chip 5 V VBUS generation is not supported. For this reason, a charge pump
    or, if 5 V are available on the application board, a basic power switch, must
    be added externally to drive the 5 V VBUS line. The external charge pump can
    be driven by any GPIO output. When the application decides to power on VBUS
    using the chosen GPIO, it must also set the port power bit in the host port
    control and status register (PPWR bit in OTG_FS_HPRT).

    Bit 12 PPWR: Port power
    The application uses this field to control power to this port, and the core
    clears this bit on an overcurrent condition.
    */
    if (state) {
        USB_LOG_INFO("vbus turn on\r\n");
        drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_5, GPIO_PIN_RESET);
    } else {
        USB_LOG_INFO("vbus turn off\r\n");
        drv_gpio_writepin(GPIO_PORT_B, GPIO_PIN_5, GPIO_PIN_SET);
    }
}

/**
* @brief  Read the Connector status of ConID through software
* @param  none
* @retval conidsts. USB_MODEA or USB_MODEB
*/
uint8_t usb_get_conidsts(void)
{
    if (drv_gpio_readpin(GPIO_PORT_B, GPIO_PIN_6) == 0) {
        return USB_MODEA;
    } else {
        return USB_MODEB;
    }
}

/**
* @brief  This function handles usb Handler.
*
* @param  none
* @return none
* @note   none
*/
void USB_IRQHandler(void)
{
#ifdef USB_CFG_USE_DEVICE_MODE
    extern void usbd_isr_handler(void);
    usbd_isr_handler();
#endif
#ifdef USB_CFG_USE_HOST_MODE
    extern void usbh_isr_handler(void);
    usbh_isr_handler();
#endif
#ifdef USB_CFG_USE_OTG_MODE
    extern void usb_otg_isr_handler(void);
    extern void usbd_isr_handler(void);
    extern void usbh_isr_handler(void);
    extern usb_otg_core_t usb_otg_core;
    switch (usb_otg_core.mode) {
    case USB_OTG_MODE:
        usb_otg_isr_handler();
        break;

    case USB_DEVICE_MODE:
        usbd_isr_handler();
        break;

    case USB_HOST_MODE:
        usbh_isr_handler();
        break;
    }
#endif
}

#ifdef USB_CFG_DEBUG_ENABLE
/**
* @brief  Initialize core registers address.
* @param  None
* @retval None
*/
void usb_regs_init(void)
{
    uint32_t i = 0;

    /* initialize device cfg following its address */
    usb_core_regs.GREGS = (usb_otg_gregs_t *)(USB_BASE + USB_GLOBAL_REGS_BASE);
    usb_core_regs.DREGS = (usb_otg_dregs_t *)(USB_BASE + USB_DEVICE_REGS_BASE);

    for (i = 0; i < (USB_CFG_DEVICE_EP_NUM - 1); i++) {
        usb_core_regs.INEP_REGS[i] = (usb_otg_inepregs_t *)(USB_BASE + USB_IN_ENDPOINT_REGS_BASE + (i * USB_EP_REGS_SIZE));
        usb_core_regs.OUTEP_REGS[i] = (usb_otg_outepregs_t *)(USB_BASE + USB_OUT_ENDPOINT_REGS_BASE + (i * USB_EP_REGS_SIZE));
    }

    usb_core_regs.HREGS = (usb_otg_hregs_t *)(USB_BASE + USB_HOST_REGS_BASE);
    usb_core_regs.HPRT0 = (uint32_t *)(USB_BASE + USB_HOST_PORT_REGS_BASE);

    for (i = 0; i < (USB_CFG_HOST_CHANNELS - 1); i++) {
        usb_core_regs.HC_REGS[i] = (usb_otg_hc_regs_t *)(USB_BASE + USB_HOST_CHANNEL_REGS_BASE + (i * USB_HOST_CHANNEL_REGS_SIZE));
    }

    for (i = 0; i < 15; i++) {
        usb_core_regs.DFIFO[i] = (uint32_t *)(USB_BASE + USB_FIFO_REGS_BASE + (i * USB_FIFO_REGS_SIZE));
    }

    usb_core_regs.PCGCCTL = (uint32_t *)(USB_BASE + USB_PCGCCTL_REGS_BASE);
}
#endif

ISR_REGISTER(USB_IRQHandler, USB_IRQn)

/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\drv_otg.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "drv_otg.h"
#include "drv_usb_glue.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE)

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/************************* variable definition *******************************/
USB_MEM_ALIGNX usb_otg_dev_t g_usb_otg_dev;

/**************************** function declear *******************************/

/********************** function implementation ******************************/
/**
* @brief  usb_set_currentmode : Set ID line
* @param  mode :  (Host/device)
* @retval None
*/
void usb_otg_set_currentmode(uint8_t mode)
{
    USB_GREGS->GUSBCFG &= ~(USB_GUSBCFG_FHMOD_Msk | USB_GUSBCFG_FDMOD_Msk);

    if (mode == USB_HOST_MODE) {
        USB_GREGS->GUSBCFG |= USB_GUSBCFG_FHMOD_Msk;
    } else if (mode == USB_DEVICE_MODE) {
        USB_GREGS->GUSBCFG |= USB_GUSBCFG_FDMOD_Msk;
    } else if (mode == USB_OTG_MODE) {
    }
    usb_delay_ms(50);
}

/**
* @brief  enable otg int
*
* @param  none
* @return none
* @note   none
*/
void usb_otg_enable_int(void)
{
#ifdef USB_CFG_IP_CONIDSTS_ENABLE
    USB_GREGS->GINTMSK |= USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_CIDSCHGM_Msk | USB_GINTMSK_DISCINT_Msk | USB_GINTMSK_SRQIM_Msk;
#else
    USB_GREGS->GINTMSK |= USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_DISCINT_Msk | USB_GINTMSK_SRQIM_Msk;
#endif
    /* Enable USB Global interrupt */
    USB_GREGS->GAHBCFG |= USB_GAHBCFG_GINT_Msk;
}

/**
* @brief  usb_otg_getconidsts : Get Connector ID Status
* @param  none
* @retval conidsts
*/
uint8_t usb_otg_getconidsts(void)
{
#ifndef USB_CFG_IP_CONIDSTS_ENABLE
    g_usb_otg_dev.conidsts = usb_get_conidsts();
#else
    //g_usb_otg_dev.conidsts = (USB_GREGS->GOTGCTL & USB_GOTGCTL_CIDSTS_Msk) >> USB_GOTGCTL_CIDSTS_Pos;
#endif
    return g_usb_otg_dev.conidsts;
}

/**
  * @brief  usb_otg_read_itr
  *         returns the Core Interrupt register
  * @param  None
  * @retval status
  */
static uint32_t usb_otg_read_itr(void)
{
    uint32_t gintsts = 0;
    uint32_t gintmsk = 0;
    uint32_t gintmsk_common = 0;

    /* OTG interrupts */
    gintmsk_common = USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_CIDSCHGM_Msk | USB_GINTMSK_SRQIM_Msk;

    gintsts = USB_GREGS->GINTSTS;
    gintmsk = (USB_GREGS->GINTMSK);
    return ((gintsts & gintmsk) & gintmsk_common);
}

/**
  * @brief  usb_otg_handleotg_isr
  *         handles the OTG Interrupts
  * @param  None
  * status  None
  */
static void usb_otg_handleotg_isr(void)
{
    uint32_t gotgint = USB_GREGS->GOTGINT;

    if (gotgint & USB_GOTGINT_SEDET_Msk) {
    }

    /* ----> SRP SUCCESS or FAILURE INTERRUPT <---- */
    if (gotgint & USB_GOTGINT_SRSSCHG_Msk) {
        if (USB_GREGS->GOTGCTL & USB_GOTGCTL_SRQSCS_Msk) /* Session request success */
        {
            /* Clear Session Request */
            USB_GREGS->GOTGCTL &= ~USB_GOTGCTL_SRQ_Msk;
        } else /* Session request failure */
        {
        }
    }
    /* ----> HNP SUCCESS or FAILURE INTERRUPT <---- */
    if (gotgint & USB_GOTGINT_HNSSCHG_Msk) {
        if (USB_GREGS->GOTGCTL & USB_GOTGCTL_HNGSCS_Msk) /* Host negotiation success */
        {
        } else /* Host negotiation failure */
        {
        }
        gotgint |= USB_GOTGINT_HNSSCHG_Msk; /* Ack "Host Negotiation Success Status Change" interrupt. */
    }
    /* ----> HOST NEGOTIATION DETECTED INTERRUPT <---- */
    if (gotgint & USB_GOTGINT_HNGDET_Msk) {
    }
    if (gotgint & USB_GOTGINT_ADTOCHG_Msk) {
    }
    if (gotgint & USB_GOTGINT_DBCDNE_Msk) {
        usbh_reset_port();
    }
    /* Clear OTG INT */
    USB_GREGS->GOTGINT = gotgint;
}

#ifdef USB_CFG_IP_CONIDSTS_ENABLE
/**
  * @brief  usb_otg_conidsts_change_isr
  *         handles the Connector ID Status Change Interrupt
  * @param  None
  * status
  */
static void usb_otg_conidsts_change_isr(void)
{
    USB_GREGS->GINTMSK &= ~USB_GINTMSK_SOFM_Msk;

    /* B-Device connector (Device Mode) */
    if (USB_GREGS->GOTGCTL & USB_GOTGCTL_CIDSTS_Msk) {
        USB_LOG_INFO("B_Device \r\n");
        g_usb_otg_dev.conidsts = USB_MODEB;
    } else {
        USB_LOG_INFO("A_HOST \r\n");
        g_usb_otg_dev.conidsts = USB_MODEA;
    }
    /* Set flag and clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_CIDSCHG_Msk;
}
#endif

/**
  * @brief  usb_otg_sessionrequest_isr
  *           Initiating the Session Request Protocol
  * @param  None
  * @retval status
  */
static uint32_t usb_otg_sessionrequest_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_SRQINT_Msk;
    return 1;
}

/**
  * @brief  usbd_otg_isr_handlerusb_otg_dev
  *
  * @param  None
  * @retval None
  */
void usb_otg_isr_handler(void)
{
    uint32_t gintsts = 0;

    gintsts = usb_otg_read_itr();
    if (gintsts == 0) {
        return;
    }
    if (gintsts & USB_GINTSTS_OTGINT_Msk) {
        usb_otg_handleotg_isr();
    }
#ifdef USB_CFG_IP_CONIDSTS_ENABLE
    if (gintsts & USB_GINTSTS_CIDSCHG_Msk) {
        usb_otg_conidsts_change_isr();
    }
#endif
    if (gintsts & USB_GINTSTS_SRQINT_Msk) {
        usb_otg_sessionrequest_isr();
    }
}

#endif
#endif

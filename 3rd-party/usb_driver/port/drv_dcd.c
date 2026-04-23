/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\drv_dcd.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: usb module driver.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header *********************************/
#include "drv_dcd.h"
#include "drv_usb_glue.h"

#if USB_CFG_USE_USB

#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/
#define USBD_DRIVER_VERSION_STR "v0.3.0"

#if (!defined(USB_CFG_FS_CORE_ENABLE)) && (!defined(USB_CFG_HS_CORE_ENABLE))
#warning "no enable USB_CFG_FS_CORE_ENABLE or USB_CFG_HS_CORE_ENABLE!"
#endif
#if (!defined(USB_CFG_USE_OTG_MODE)) && (!defined(USB_CFG_USE_HOST_MODE)) && (!defined(USB_CFG_USE_DEVICE_MODE))
#warning "no enable USB_CFG_USE_OTG_MODE or USB_CFG_USE_DEVICE_MODE or USB_CFG_USE_HOST_MODE!"
#endif

/**************************** type definition ********************************/
USB_MEM_ALIGNX usb_dcd_t gusb_dcd;
USB_MEM_ALIGNX usb_dcd_int_cb_t usbd_int_fops;
usb_dcd_token_t usbd_token;

/************************* variable definition *******************************/

/**************************** function declear *******************************/
static void usbd_ep0_read_setup(uint8_t *psetup);

/********************** function implementation ******************************/
/**
* @brief  Soft reset of the core
* @param  None
* @retval usb_status_t : status
*/
static usb_status_t usbd_core_reset(void)
{
    volatile uint32_t count = 0U;

    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_AHBIDL_Msk) == 0U) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    count = 0U;
    USB_GREGS->GRSTCTL |= USB_GRSTCTL_CSRST_Msk;
    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_CSRST_Msk) == USB_GRSTCTL_CSRST_Msk) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    return USB_OK;
}

/**
* @brief  Initializes the phy registers and prepares the core
*         device mode or host mode operation.
* @param  none
* @retval None
*/
static void usbd_phy_init(void)
{
    /* Init The ULPI Interface */
    USB_GREGS->GUSBCFG &= ~(USB_GUSBCFG_PHYIF_Msk | USB_GUSBCFG_ULPI_UTMI_SEL_Msk | USB_GUSBCFG_PHYINTF_Msk | USB_GUSBCFG_PHYSEL_Msk | USB_GUSBCFG_ULPIFSLS_Msk | USB_GUSBCFG_ULPICSM_Msk | USB_GUSBCFG_TSDPS_Msk);

    /* Select vbus source */
    USB_GREGS->GUSBCFG &= ~(USB_GUSBCFG_ULPIEVBUSD_Msk | USB_GUSBCFG_ULPIEVBUSI_Msk);

    /* Reset after a PHY select */
    usbd_core_reset();

    /* initialize OTG features */
    USB_GREGS->GUSBCFG &= (USB_GUSBCFG_SRPCAP_Msk | USB_GUSBCFG_HNPCAP_Msk);
}

/**
* @brief  returns the Core Interrupt register
* @param  None
* @retval Status
*/
static inline uint32_t usbd_read_coreitr(void)
{
    uint32_t v = 0;
    v = USB_GREGS->GINTSTS;
    v &= USB_GREGS->GINTMSK;
    return v;
}

/**
* @brief  Flush a Rx FIFO
* @param  None
* @retval status
*/
static inline usb_status_t usbd_flush_rxfifo(void)
{
    volatile uint32_t count = 0U;

    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_AHBIDL_Msk) == 0U) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    count = 0;
    USB_GREGS->GRSTCTL = USB_GRSTCTL_RXFFLSH_Msk;
    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_RXFFLSH_Msk) == USB_GRSTCTL_RXFFLSH_Msk) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    return USB_OK;
}

/**
* @brief  Flush a Tx FIFO
* @param  num : FIFO num
* @retval status
*/
static inline usb_status_t usbd_flush_txfifo(uint32_t num)
{
    volatile uint32_t count = 0U;

    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_AHBIDL_Msk) == 0U) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    count = 0;
    USB_GREGS->GRSTCTL = (USB_GRSTCTL_TXFFLSH_Msk | (num << 6));
    while ((USB_GREGS->GRSTCTL & USB_GRSTCTL_TXFFLSH_Msk) == USB_GRSTCTL_TXFFLSH_Msk) {
        if (++count > 200000U) {
            return USB_ERROR;
        }
    }

    return USB_OK;
}

/**
* @brief  usb_set_currentmode : Set ID line
* @param  mode :  (Host/device)
* @retval None
*/
static void usbd_set_currentmode(uint8_t mode)
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
* @brief  Writes a packet into the Tx FIFO associated with the EP
* @param  src : source pointer
* @param  epnum : end point number
* @param  bytes : No. of bytes
* @retval None
*/
static void usbd_write_packet(uint8_t *src, uint8_t epnum, uint16_t len)
{
    uint32_t count32b = 0;
    uint32_t i = 0;

    count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++) {
        USB_DFIFO(epnum) = *((uint32_t *)src);
        src += 4;
    }
}

#ifndef USB_CFG_INTERNAL_DMA_ENABLE
/**
* @brief  Reads a packet from the Rx FIFO
* @param  dest : Destination Pointer
* @param  bytes : No. of bytes
* @retval None
*/
static void usbd_read_packet(uint8_t *dest, uint16_t len)
{
    uint32_t i = 0;
    uint32_t count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++) {
        *(uint32_t *)dest = USB_DFIFO(0U);
        dest += 4;
    }
}
#endif

/**
* @brief  usbd_init_speed :Initializes the DevSpd field of DCFG register
*         depending the PHY type and the enumeration speed of the device.
* @param  speed : speed
* @retval None
*/
static void usbd_init_speed(uint8_t speed)
{
    USB_DREGS->DCFG &= ~USB_DCFG_DSPD_Msk;
    USB_DREGS->DCFG |= speed;
}

/**
* @brief  usbd_enable_int : Enables the Device mode interrupts
* @param  None
* @retval status
*/
static void usbd_enable_int(void)
{
    /* Clear all pending Device Interrupts */
    USB_DREGS->DIEPMSK = 0U;
    USB_DREGS->DOEPMSK = 0U;
    USB_DREGS->DAINTMSK = 0U;

    /* Disable all interrupts. */
    USB_GREGS->GINTMSK = 0U;

    /* Clear any pending interrupts */
    USB_GREGS->GINTSTS = 0xBFFFFFFFU;

    /* Enable interrupts matching to the Device mode ONLY */
    USB_GREGS->GINTMSK = USB_GINTMSK_USBSUSPM_Msk | USB_GINTMSK_USBRST_Msk | USB_GINTMSK_ENUMDNEM_Msk | USB_GINTMSK_IEPINT_Msk | USB_GINTMSK_OEPINT_Msk | USB_GINTMSK_IISOIXFRM_Msk | USB_GINTMSK_PXFRM_IISOOXFRM_Msk | USB_GINTMSK_WUIM_Msk;
#ifndef USB_CFG_INTERNAL_DMA_ENABLE
    USB_GREGS->GINTMSK |= USB_GINTMSK_RXFLVLM_Msk;
#endif
#ifdef USB_CFG_VBUS_SENSING_ENABLE
    USB_GREGS->GINTMSK |= USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_SRQIM_Msk;
#endif
#ifdef USB_CFG_SOF_OUTPUT_ENABLE
    USB_GREGS->GINTMSK |= USB_GINTMSK_SOFM_Msk;
#endif

#ifdef USB_CFG_USE_OTG_MODE
#ifdef USB_CFG_IP_CONIDSTS_ENABLE
    USB_GREGS->GINTMSK |= USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_CIDSCHGM_Msk | USB_GINTMSK_DISCINT_Msk | USB_GINTMSK_SRQIM_Msk;
#else
    USB_GREGS->GINTMSK |= USB_GINTMSK_OTGINT_Msk | USB_GINTMSK_DISCINT_Msk | USB_GINTMSK_SRQIM_Msk;
#endif
#endif
}

/**
 * @brief  usb endpoint register
 * @param  ep_addr : endpoint addr
 * @param  cb : \ref ep_callback_t
 * @retval None
 */
void usbd_endpoint_register(uint8_t ep_addr, ep_callback_t cb)
{
    if (ep_addr & 0x80) {
        gusb_dcd.in_ep[ep_addr & 0x7f].cb = cb;
    } else {
        gusb_dcd.out_ep[ep_addr & 0x7f].cb = cb;
    }
}

/**
 * @brief  usb endpoint unregister
 * @param  ep_addr : endpoint addr
 * @retval None
 */
void usbd_endpoint_unregister(uint8_t ep_addr)
{
    if (ep_addr & 0x80) {
        gusb_dcd.in_ep[ep_addr & 0x7f].cb = NULL;
    } else {
        gusb_dcd.out_ep[ep_addr & 0x7f].cb = NULL;
    }
}

/**
* @brief  usbd_core_init: Initializes the USB_OTG controller registers
*         for device mode
* @param  None
* @retval status
*/
void usbd_core_init(void)
{
    uint16_t startaddr = 0;
    uint16_t depth = 0;

    for (uint8_t i = 0U; i < 15U; i++) {
        USB_GREGS->DIEPTXF[i] = 0U;
    }

    /* Restart the Phy Clock */
    USB_PCGCCTL = 0U;

    /* Device configuration register */
    USB_DREGS->DCFG &= ~(USB_DCFG_PFIVL_Msk | USB_DCFG_DESCDMA_Msk); /* disable Descriptor DMA */
    USB_DREGS->DCFG |= DCFG_FRAME_INTERVAL_80 << USB_DCFG_PFIVL_Pos;

    /* Device speed configuration */
#ifdef USB_CFG_FS_CORE_ENABLE
    /* Set Full speed phy */
    usbd_init_speed(USB_SPEED_PARAM_HIGH_IN_FULL);
    USB_LOG_INFO("Set Full speed phy\r\n");
#endif
#ifdef USB_CFG_HS_CORE_ENABLE
    /* Set High speed phy */
    usbd_init_speed(USB_SPEED_PARAM_HIGH);
    USB_LOG_INFO("Set High speed phy\r\n");
#endif

    usbd_enable_int();

#ifdef USB_CFG_INTERNAL_DMA_ENABLE
    USB_LOG_INFO("usb device use dma\r\n");
    USB_ASSERT_MSG(((USB_GREGS->GHWCFG2 & (0x3U << 3)) >> 3) == 2, "usb does not support dma mode, so stop working");
    USB_GREGS->GAHBCFG &= ~USB_GAHBCFG_HBSTLEN_Msk;
    USB_GREGS->GAHBCFG |= (USB_GAHBCFG_DMAEN_Msk | USB_GAHBCFG_HBSTLEN_4);
#endif

    /* set Rx FIFO size */
    USB_GREGS->GRXFSIZ = USB_CFG_DEVICE_RX_FIFO_SIZE;

    startaddr = USB_CFG_DEVICE_RX_FIFO_SIZE;
    depth = USB_CFG_DEVICE_TX0_FIFO_SIZE;
    USB_GREGS->GNPTXFSIZ = startaddr | (depth << 16);

#if USB_CFG_DEVICE_EP_NUM > 1
    startaddr = startaddr + depth;
    depth = USB_CFG_DEVICE_TX1_FIFO_SIZE;
    USB_GREGS->DIEPTXF[0] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 2
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX2_FIFO_SIZE;
    USB_GREGS->DIEPTXF[1] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 3
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX3_FIFO_SIZE;
    USB_GREGS->DIEPTXF[2] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 4
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX4_FIFO_SIZE;
    USB_GREGS->DIEPTXF[3] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 5
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX5_FIFO_SIZE;
    USB_GREGS->DIEPTXF[4] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 6
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX6_FIFO_SIZE;
    USB_GREGS->DIEPTXF[5] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 7
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX7_FIFO_SIZE;
    USB_GREGS->DIEPTXF[6] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 8
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX8_FIFO_SIZE;
    USB_GREGS->DIEPTXF[7] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 9
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX9_FIFO_SIZE;
    USB_GREGS->DIEPTXF[8] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 10
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX10_FIFO_SIZE;
    USB_GREGS->DIEPTXF[9] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 11
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX11_FIFO_SIZE;
    USB_GREGS->DIEPTXF[10] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 12
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX12_FIFO_SIZE;
    USB_GREGS->DIEPTXF[11] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 13
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX13_FIFO_SIZE;
    USB_GREGS->DIEPTXF[12] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 14
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX14_FIFO_SIZE;
    USB_GREGS->DIEPTXF[13] = startaddr | (depth << 16);
#endif
#if USB_CFG_DEVICE_EP_NUM > 15
    startaddr += depth;
    depth = USB_CFG_DEVICE_TX15_FIFO_SIZE;
    USB_GREGS->DIEPTXF[14] = startaddr | (depth << 16);
#endif

    startaddr += depth;
    USB_ASSERT_MSG(startaddr <= (USB_GREGS->GHWCFG3 >> 16), "fifo config is overflow");

    /* Flush the FIFOs */
    usbd_flush_txfifo(0x10);
    usbd_flush_rxfifo();
}

/**
* @brief  usbd_get_speed
*         Get the device speed from the device status register
* @param  None
* @retval status
*/
static uint8_t usbd_get_speed(void)
{
    uint8_t speed = USB_SPEED_UNKNOWN;
    uint32_t DevEnumSpeed = (USB_DREGS->DSTS & USB_DSTS_ENUMSPD_Msk) >> USB_DSTS_ENUMSPD_Pos;

    switch (DevEnumSpeed) {
    case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
        speed = USB_SPEED_HIGH;
        break;

    case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
    case DSTS_ENUMSPD_FS_PHY_48MHZ:
        speed = USB_SPEED_FULL;
        break;

    case DSTS_ENUMSPD_LS_PHY_6MHZ:
        speed = USB_SPEED_LOW;
        break;

    default:
        speed = USB_SPEED_FULL;
        break;
    }

    return speed;
}

/**
* @brief  Transmit data over USB
* @param : device instance
* @param epnum: endpoint address
* @param pbuf: pointer to Tx buffer
* @param buf_len: data length
* status
*/
usb_status_t usbd_ep_tx(uint8_t epnum, uint8_t *pbuf, uint32_t len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    usb_otg_ep_t *ep = &(gusb_dcd.in_ep[ep_idx]);
    uint32_t pktcnt = 0;

    USB_ASSERT_MSG(!((uint32_t)pbuf % 0x04), "The buff must be 4-byte aligned");
    if (!pbuf && len) {
        USB_LOG_ERR("fifo is NULL\r\n");
        return USB_ERROR;
    }
    if (ep_idx && !(USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_MPSIZ_Msk)) {
        USB_LOG_ERR("tx ep %02x not init\r\n", epnum);
        return USB_ERROR;
    }

    /* Setup and start the Transfer */
    ep->xfer_buff = (uint8_t *)pbuf;
    ep->xfer_len = len;
    ep->actual_xfer_len = 0;

    USB_INEP_REGS(ep_idx)->DIEPTSIZ &= ~(USB_DIEPTSIZ_XFRSIZ_Msk | USB_DIEPTSIZ_PKTCNT_Msk);

    /* Zero Length Packet? */
    if (ep->xfer_len == 0) {
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_PKTCNT_Msk & (1U << USB_DIEPTSIZ_PKTCNT_Pos));
        /* EP enable, IN data in FIFO */
        USB_INEP_REGS(ep_idx)->DIEPCTL |= (USB_DIEPCTL_CNAK_Msk | USB_DIEPCTL_EPENA_Msk);
        return USB_OK;
    }

    if (ep_idx == 0) {
        if (ep->xfer_len > ep->maxpacket) {
            ep->xfer_len = ep->maxpacket;
        }
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_PKTCNT_Msk & (1U << USB_DIEPTSIZ_PKTCNT_Pos));
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_XFRSIZ_Msk & ep->xfer_len);
    } else {
        /* IN endpoint */
        /* Program the transfer size and packet count
        * as follows: xfersize = N * maxpacket +
        * short_packet pktcnt = N + (short_packet
        * exist ? 1 : 0)
        */
        pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_PKTCNT_Msk & (pktcnt << USB_DIEPTSIZ_PKTCNT_Pos));
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_XFRSIZ_Msk & ep->xfer_len);
    }

    if (ep->type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        if ((USB_DREGS->DSTS & (0x1U << 8)) == 0U) {
            USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SODDFRM_Msk;
        } else {
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
            USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SODDFRM_Msk;
        }
        USB_INEP_REGS(ep_idx)->DIEPTSIZ &= ~(USB_DIEPTSIZ_MULCNT_Msk);
        USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_MULCNT_Msk & (1U << USB_DIEPTSIZ_MULCNT_Pos));
    }

#ifdef USB_CFG_INTERNAL_DMA_ENABLE
    if ((uint32_t)pbuf & USB_DMA_BUFF_ADDR_MASK) {
        USB_INEP_REGS(ep_idx)->DIEPDMA = (uint32_t)pbuf;
    } else {
        USB_INEP_REGS(ep_idx)->DIEPDMA = (uint32_t)pbuf + USB_DMA_ADDR_OFFSET;
    }
    USB_INEP_REGS(ep_idx)->DIEPCTL |= (USB_DIEPCTL_CNAK_Msk | USB_DIEPCTL_EPENA_Msk);
#else
    USB_INEP_REGS(ep_idx)->DIEPCTL |= (USB_DIEPCTL_CNAK_Msk | USB_DIEPCTL_EPENA_Msk);
    if (ep->xfer_len > 0U) {
        USB_DREGS->DIEPEMPMSK |= 1UL << ep_idx;
    }
#endif
    return USB_OK;
}

/**
* @brief  usbd_ep_preparerx
* @param epnum: endpoint address
* @param pbuf: pointer to Rx buffer
* @param buf_len: data length
* status
*/
usb_status_t usbd_ep_preparerx(uint8_t epnum, uint8_t *pbuf, uint32_t len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    usb_otg_ep_t *ep = &(gusb_dcd.out_ep[ep_idx]);
    uint32_t pktcnt = 0;

    USB_ASSERT_MSG(!((uint32_t)pbuf % 0x04), "The buff must be 4-byte aligned");
    if (!pbuf && len) {
        USB_LOG_ERR("fifo is NULL\r\n");
        return USB_ERROR;
    }
    if (ep_idx && !(USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_MPSIZ_Msk)) {
        USB_LOG_ERR("rx ep %02x not init\r\n", epnum);
        return USB_ERROR;
    }

    /*setup and start the Xfer */
    ep->xfer_buff = (uint8_t *)pbuf;
    ep->xfer_len = len;
    ep->actual_xfer_len = 0;

    /* Program the transfer size and packet count as follows:
     * pktcnt = N
     * xfersize = N * maxpacket
     */
    if (ep_idx == 0) {
        USB_OUTEP_REGS(ep_idx)->DOEPTSIZ &= ~(USB_DOEPTSIZ_PKTCNT_Msk);
        USB_OUTEP_REGS(ep_idx)->DOEPTSIZ &= ~(USB_DOEPTSIZ_XFRSIZ_Msk);
        /* Program the transfer size and packet count as follows:
         * xfersize = N * (maxpacket + 4 - (maxpacket % 4))
         * pktcnt = N */
        if (ep->xfer_len == 0) {
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_PKTCNT_Msk & (1 << USB_DOEPTSIZ_PKTCNT_Pos));
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_XFRSIZ_Msk & ep->maxpacket);
            /* EP enable */
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_CNAK_Msk | USB_DOEPCTL_EPENA_Msk;
            return USB_OK;
        } else {
            if (ep->xfer_len > ep->maxpacket) {
                ep->xfer_len = ep->maxpacket;
            }
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_PKTCNT_Msk & (1U << USB_DOEPTSIZ_PKTCNT_Pos));
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_XFRSIZ_Msk & ep->xfer_len);
        }
    } else {
        USB_OUTEP_REGS(ep_idx)->DOEPTSIZ &= ~(USB_DOEPTSIZ_PKTCNT_Msk);
        USB_OUTEP_REGS(ep_idx)->DOEPTSIZ &= ~(USB_DOEPTSIZ_XFRSIZ_Msk);
        if (ep->xfer_len == 0) {
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_PKTCNT_Msk & (1 << USB_DOEPTSIZ_PKTCNT_Pos));
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_XFRSIZ_Msk & ep->maxpacket);
            /* EP enable */
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= (USB_DOEPCTL_CNAK_Msk | USB_DOEPCTL_EPENA_Msk);
            return USB_OK;
        } else {
            pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_PKTCNT_Msk & (pktcnt << USB_DOEPTSIZ_PKTCNT_Pos));
            USB_OUTEP_REGS(ep_idx)->DOEPTSIZ |= (USB_DOEPTSIZ_XFRSIZ_Msk & ep->xfer_len);
        }
    }

#ifdef USB_CFG_INTERNAL_DMA_ENABLE
    if ((uint32_t)pbuf & USB_DMA_BUFF_ADDR_MASK) {
        USB_OUTEP_REGS(ep_idx)->DOEPDMA = (uint32_t)pbuf;
    } else {
        USB_OUTEP_REGS(ep_idx)->DOEPDMA = (uint32_t)pbuf + USB_DMA_ADDR_OFFSET;
    }
#endif

    if (ep->type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        if ((USB_DREGS->DSTS & (0x1U << 8)) == 0U) {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~USB_DOEPCTL_SD0PID_SEVNFRM_Msk;
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_SODDFRM_Msk;
        } else {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_SD0PID_SEVNFRM_Msk;
            USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~USB_DOEPCTL_SODDFRM_Msk;
        }
    }
    /* EP enable */
    USB_OUTEP_REGS(ep_idx)->DOEPCTL |= (USB_DOEPCTL_CNAK_Msk | USB_DOEPCTL_EPENA_Msk);
    return USB_OK;
}

/**
* @brief  usbd_set_ep_stall : Set the EP STALL
* @param  epnum : endpoint address
* @retval status
*/
void usbd_set_ep_stall(uint8_t epnum)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);

    if (USB_EP_DIR_IS_OUT(epnum)) {
        /* set the stall bit */
        if (((USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_EPENA_Msk) == 0U) && (ep_idx != 0U)) {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~(USB_DOEPCTL_EPDIS_Msk);
        }
        gusb_dcd.stall_flag |= (1 << ep_idx);
        USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_STALL_Msk;
    } else {
        /* set the disable and stall bits */
        if (((USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_EPENA_Msk) == 0U) && (ep_idx != 0U)) {
            USB_INEP_REGS(ep_idx)->DIEPCTL &= ~(USB_DIEPCTL_EPDIS_Msk);
        }
        gusb_dcd.stall_flag |= ((1 << ep_idx) << 16);
        USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_STALL_Msk;
    }
}

/**
* @brief  Clear the EP STALL
* @param   : device instance
* @param  epnum : endpoint address
* @retval status
*/
void usbd_clear_ep_stall(uint8_t epnum)
{
    usb_otg_ep_t *ep;
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);

    if (USB_EP_DIR_IS_OUT(epnum)) {
        ep = &(gusb_dcd.out_ep[ep_idx]);
        gusb_dcd.stall_flag &= ~(1 << ep_idx);
        USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~USB_DOEPCTL_STALL_Msk;
        /* clear the stall bits */
        if ((ep->type == USB_ENDPOINT_TYPE_INTERRUPT) || (ep->type == USB_ENDPOINT_TYPE_BULK)) {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_SD0PID_SEVNFRM_Msk; /* DATA0 */
        }
    } else {
        ep = &(gusb_dcd.in_ep[ep_idx]);
        gusb_dcd.stall_flag &= ~((1 << ep_idx) << 16);
        USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_STALL_Msk;
        /* clear the stall bits */
        if ((ep->type == USB_ENDPOINT_TYPE_INTERRUPT) || (ep->type == USB_ENDPOINT_TYPE_BULK)) {
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SD0PID_SEVNFRM_Msk; /* DATA0 */
        }
    }
}

/**
* @brief  get the EP stall status
* @param  epnum : endpoint address
* @retval status
*/
usb_status_t usbd_ep_is_stalled(uint8_t epnum)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);

    if (USB_EP_DIR_IS_OUT(epnum)) {
        //if (USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_STALL_Msk) {
        if (gusb_dcd.stall_flag & (1 << ep_idx)) {
            return USB_OK;
        } else {
            return USB_ERROR;
        }
    } else {
        //if (USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_STALL_Msk) {
        if (gusb_dcd.stall_flag & ((1 << ep_idx) << 16)) {
            return USB_OK;
        } else {
            return USB_ERROR;
        }
    }
}

/**
* @brief  This Function set USB device address
* @param address: new device address
* status
*/
void usbd_set_device_address(uint8_t addr)
{
    USB_DREGS->DCFG &= ~USB_DCFG_DAD_Msk;
    USB_DREGS->DCFG |= ((uint32_t)addr << USB_DCFG_DAD_Pos) & USB_DCFG_DAD_Msk;
}

/**
* @brief  Connect device (enable internal pull-up)
* @param None
* @retval None
*/
static void usbd_connect(void)
{
    USB_DREGS->DCTL &= ~USB_DCTL_SDIS_Msk;
}

/**
* @brief  Disconnect device (disable internal pull-up)
* @param None
* @retval None
*/
void usbd_disconnect(void)
{
    USB_DREGS->DCTL |= USB_DCTL_SDIS_Msk;
}

/**
* @brief  set an EP
* @param  epnum : Endpoint
* status
*/
usb_status_t usbd_enable_ep(uint8_t epnum)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    USB_DREGS->DAINTMSK |= USB_DAINTMSK_OEPM_Msk & (uint32_t)(1UL << (16 + ep_idx));
    USB_OUTEP_REGS(ep_idx)->DOEPCTL |= (USB_DOEPCTL_EPENA_Msk);
    return USB_OK;
}

/**
* @brief  Configure an EP
* @param  epnum : Endpoint
* @param  ep_mps : Endpoint maxpacket
* @param  ep_type : Endpoint type
* status
*/
usb_status_t usbd_open_endpoint(uint8_t epnum, uint16_t ep_mps, uint8_t ep_type)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    usb_otg_ep_t *ep;

    USB_ASSERT_MSG(ep_idx < USB_CFG_DEVICE_EP_NUM, "Ep addr %02x overflow", epnum);

    if (USB_EP_DIR_IS_OUT(epnum)) {
        ep = &(gusb_dcd.out_ep[ep_idx]);
        ep->maxpacket = ep_mps;
        ep->type = ep_type;
        USB_DREGS->DAINTMSK |= USB_DAINTMSK_OEPM_Msk & (uint32_t)(1UL << (16 + ep_idx));
        if ((USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_USBAEP_Msk) == 0) {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= (USB_GET_MAXPACKETSIZE(ep->maxpacket) & USB_DOEPCTL_MPSIZ_Msk) | ((uint32_t)USB_GET_ENDPOINT_TYPE(ep->type) << 18) | (ep_idx << USB_DIEPCTL_TXFNUM_Pos) | USB_DIEPCTL_SD0PID_SEVNFRM_Msk | USB_DOEPCTL_USBAEP_Msk;
        }
    } else {
        uint16_t txfifosize = 0;
        ep = &(gusb_dcd.in_ep[ep_idx]);
        ep->maxpacket = ep_mps;
        ep->type = ep_type;

        if (ep_idx == 0) {
            txfifosize = USB_GREGS->GNPTXFSIZ >> 16;
        } else {
            txfifosize = USB_GREGS->DIEPTXF[ep_idx - 1] >> 16;
        }
        USB_ASSERT_MSG((txfifosize * 4) >= USB_GET_MAXPACKETSIZE(ep->maxpacket), "Ep addr %02x fifo overflow", epnum);
        USB_DREGS->DAINTMSK |= USB_DAINTMSK_IEPM_Msk & (uint32_t)(1UL << ep_idx);
        if ((USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_USBAEP_Msk) == 0) {
            USB_INEP_REGS(ep_idx)->DIEPCTL |= (USB_GET_MAXPACKETSIZE(ep->maxpacket) & USB_DIEPCTL_MPSIZ_Msk) | ((uint32_t)USB_GET_ENDPOINT_TYPE(ep->type) << 18) | (ep_idx << 22) | (ep_idx << USB_DIEPCTL_TXFNUM_Pos) | USB_DIEPCTL_SD0PID_SEVNFRM_Msk | USB_DIEPCTL_USBAEP_Msk;
        }
        usbd_flush_txfifo(ep_idx);
    }
    return USB_OK;
}

/**
* @brief  called when an EP is disabled
* @param epnum: endpoint address
* status
*/
usb_status_t usbd_close_endpoint(uint8_t epnum)
{
    volatile uint32_t count = 0U;
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    if (USB_EP_DIR_IS_OUT(epnum)) {
        if (USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_EPENA_Msk) {
            USB_DREGS->DCTL |= USB_DCTL_SGONAK_Msk;
            // while ((USB_GREGS->GINTSTS & USB_GINTSTS_GOUTNAKEFF_Msk) == 0)
            //     ;
            // Ditto here disable the endpoint.
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_EPDIS_Msk | USB_DOEPCTL_SNAK_Msk;
            while ((USB_OUTEP_REGS(ep_idx)->DOEPINT |= USB_DOEPINT_EPDISD_Msk) == 0)
                ;
            USB_OUTEP_REGS(ep_idx)->DOEPINT = USB_DOEPINT_EPDISD_Msk;
            while (++count < 20000)
                ;
            // Allow other OUT endpoints to keep receiving.
            USB_DREGS->DCTL |= USB_DCTL_CGONAK_Msk;
            USB_DREGS->DCTL &= ~USB_DCTL_SGONAK_Msk;
        }
    } else {
        if (USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_EPENA_Msk) {
            // Stop transmitting packets and NAK IN xfers.
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SNAK_Msk;
            while ((USB_INEP_REGS(ep_idx)->DIEPINT & USB_DIEPINT_INEPNE_Msk) == 0)
                ;
            // Disable the endpoint.
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_EPDIS_Msk;
            while ((USB_INEP_REGS(ep_idx)->DIEPINT & USB_DIEPINT_EPDISD_Msk) == 0)
                ;
            USB_INEP_REGS(ep_idx)->DIEPINT |= USB_DIEPINT_EPDISD_Msk;
        } else {
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SNAK_Msk;
        }
    }
    return USB_OK;
}

static void usbd_stallstage_init(void)
{
    usbd_token.token_flag = 0;
    usbd_token.stall_flag = 0;
    usbd_token.cnt = 0;
}

static void usbd_stallstage_enable(usb_setup_req_t *preq)
{
    if (preq->bmRequestType == 0x80 && preq->bRequest == 0x06 && preq->wValue == 0x0100 && preq->wLength == 0x0012) {
        usbd_token.token_flag = 1;
        usbd_token.stall_flag = 0;
        usbd_token.cnt = 0;
    }
}

static void usbd_stallstage_timeout(void)
{
    if (usbd_token.token_flag) {
        usbd_token.stall_flag = 1;
#ifndef USB_CFG_SOF_OUTPUT_ENABLE
        USB_GREGS->GINTMSK |= USB_GINTMSK_SOFM_Msk;
#endif
    }
}

static void usbd_stallstage_disable(void)
{
#ifndef USB_CFG_SOF_OUTPUT_ENABLE
    if (usbd_token.token_flag > 0) {
        USB_GREGS->GINTMSK &= ~USB_GINTMSK_SOFM_Msk;
    }
#endif
    usbd_stallstage_init();
}

static void usbd_stallstage_isr(void)
{
    if (usbd_token.token_flag && usbd_token.stall_flag) {
        usbd_token.cnt++;
        if (usbd_token.cnt >= 20) {
            usbd_stallstage_init();
#ifndef USB_CFG_SOF_OUTPUT_ENABLE
            USB_GREGS->GINTMSK &= ~USB_GINTMSK_SOFM_Msk;
#endif
            usbd_set_ep_stall(USB_CTL_OUT_EP0);
            // USB_LOG_INFO("stall\r\n");
        }
    }
}

/**
* @brief  usb device init
*         Initializes the device stack and load the class driver
* @param  None
* @retval None
*/
void usb_dc_init(void)
{
    uint8_t fsphy_type;
    uint8_t hsphy_type;
    uint8_t dma_support;
    uint8_t endpoints;

    /* Hardware Init */
    usb_low_level_init();
#ifdef USB_CFG_DEBUG_ENABLE
    usb_regs_init();
#endif

    usbd_stallstage_init();

    /*
        Full-Speed PHY Interface Type (FSPhyType)
        2'b00: Full-speed interface not supported
        2'b01: Dedicated full-speed interface
        2'b10: FS pins shared with UTMI+ pins
        2'b11: FS pins shared with ULPI pins

        High-Speed PHY Interface Type (HSPhyType)
        2'b00: High-Speed interface not supported
        2'b01: UTMI+
        2'b10: ULPI
        2'b11: UTMI+ and ULPI

        Architecture (OtgArch)
        2'b00: Slave-Only
        2'b01: External DMA
        2'b10: Internal DMA
        Others: Reserved
    */
    fsphy_type = ((USB_GREGS->GHWCFG2 & (0x03 << 8)) >> 8);
    hsphy_type = ((USB_GREGS->GHWCFG2 & (0x03 << 6)) >> 6);
    dma_support = ((USB_GREGS->GHWCFG2 & (0x03 << 3)) >> 3);
    endpoints = ((USB_GREGS->GHWCFG2 & (0x0f << 10)) >> 10) + 1;

    USB_LOG_INFO("usb device driver Version %s\r\n", USBD_DRIVER_VERSION_STR);
    USB_LOG_INFO("usb fsphy type:%d, hsphy type:%d, dma support:%d\r\n", fsphy_type, hsphy_type, dma_support);
    USB_LOG_INFO("usb has %d endpoints and dfifo depth(32-bit words) is %d, default config: %d endpoints\r\n", endpoints, (USB_GREGS->GHWCFG3 >> 16), USB_CFG_DEVICE_EP_NUM);
    USB_ASSERT_MSG(endpoints >= USB_CFG_DEVICE_EP_NUM, "usb has less endpoints than config");

    usbd_disconnect();

    USB_GREGS->GAHBCFG &= ~USB_GAHBCFG_GINT_Msk;

    /* This is vendor register */
    USB_GREGS->GGPIO = ((1 << 16) | (1 << 21));

    /*Init the phy */
    usbd_phy_init();

    /* Force Device Mode*/
    usbd_set_currentmode(USB_DEVICE_MODE);

    /* Init Device */
    usbd_core_init();

    /* Enable USB Global interrupt */
    USB_GREGS->GAHBCFG |= USB_GAHBCFG_GINT_Msk;

    usbd_connect();
}

/**
* @brief  usb device deinit
*         Initializes the device stack and load the class driver
* @param  None
* @retval None
*/
void usb_dc_deinit(void)
{
    usbd_stallstage_init();
    memset(&gusb_dcd, 0, sizeof(usb_dcd_t));

    USB_GREGS->GAHBCFG |= USB_GAHBCFG_GINT_Msk;
    USB_DREGS->DCTL |= USB_DCTL_SDIS_Msk;

    /* Clear Pending interrupt */
    for (uint8_t i = 0U; i < 15U; i++) {
        USB_INEP_REGS(i)->DIEPINT = 0xFB7FU;
        USB_OUTEP_REGS(i)->DOEPINT = 0xFB7FU;
    }

    /* Clear interrupt masks */
    USB_DREGS->DIEPMSK = 0U;
    USB_DREGS->DOEPMSK = 0U;
    USB_DREGS->DAINTMSK = 0U;

    /* Flush the FIFO */
    usbd_flush_txfifo(0x10U);
    usbd_flush_rxfifo();

    usb_low_level_deinit();
}

/**
* @brief  usbd_read_alloutep_itr : returns OUT endpoint interrupt bits
* @param  None
* @retval OUT endpoint interrupt bits
*/
static inline uint32_t usbd_read_alloutep_itr(void)
{
    uint32_t v = 0;
    v = USB_DREGS->DAINT;
    v &= USB_DREGS->DAINTMSK;
    return ((v & 0xffff0000U) >> 16);
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
static inline uint32_t usbd_read_outep_itr(uint8_t epnum)
{
    uint32_t v = 0;
    v = USB_OUTEP_REGS(epnum)->DOEPINT;
    /* Clear the bit in DOEPINTn for interrupt */
    USB_OUTEP_REGS(epnum)->DOEPINT = v;
    v &= USB_DREGS->DOEPMSK;
    return v;
}

/**
* @brief  Get int status register
* @param  None
* @retval int status register
*/
static inline uint32_t usbd_read_allinep_itr(void)
{
    uint32_t v = 0;
    v = USB_DREGS->DAINT;
    v &= USB_DREGS->DAINTMSK;
    return (v & 0xFFFFU);
}

/**
* @brief  usbd_read_inep_itr
*         Reads ep flags
* @param  epnum: endpoint number
* @retval status
*/
static inline uint32_t usbd_read_inep_itr(uint8_t epnum)
{
    uint32_t v = 0;
    uint32_t msk = 0;
    uint32_t emp = 0;

    msk = USB_DREGS->DIEPMSK;
    emp = USB_DREGS->DIEPEMPMSK;
    msk |= ((emp >> (epnum & 0x7f)) & 0x1U) << 7;
    v = USB_INEP_REGS((epnum & 0x7f))->DIEPINT;
    USB_INEP_REGS((epnum & 0x7f))->DIEPINT = v;
    v = v & msk;
    return v;
}

/**
* @brief  configures EPO to receive SETUP packets
* @param  psetup: device instance
* @retval None
*/
static void usbd_ep0_read_setup(uint8_t *psetup)
{
    USB_OUTEP_REGS(0U)->DOEPTSIZ = 0U;
    USB_OUTEP_REGS(0U)->DOEPTSIZ |= (USB_DOEPTSIZ_PKTCNT_Msk & (1U << 19));
    USB_OUTEP_REGS(0U)->DOEPTSIZ |= USB_DOEPTSIZ_STUPCNT_Msk;
    USB_OUTEP_REGS(0U)->DOEPTSIZ |= (3U * 8U);

#ifdef USB_CFG_INTERNAL_DMA_ENABLE
    if ((uint32_t)psetup & USB_DMA_BUFF_ADDR_MASK) {
        USB_OUTEP_REGS(0U)->DOEPDMA = (uint32_t)psetup;
    } else {
        USB_OUTEP_REGS(0U)->DOEPDMA = (uint32_t)psetup + USB_DMA_ADDR_OFFSET;
    }
    /* EP enable */
    USB_OUTEP_REGS(0U)->DOEPCTL |= USB_DOEPCTL_EPENA_Msk | USB_DOEPCTL_USBAEP_Msk;
#endif
}

/**
* @brief  usbd_write_emptytxfifo
*         check FIFO for the next packet to be loaded
* @param  epnum: device instance
* @retval None
*/
static void usbd_write_emptytxfifo(uint8_t epnum)
{
    uint8_t ep_idx = USB_EP_GET_IDX(epnum);
    uint32_t len = 0;
    uint32_t len32b;
    uint32_t fifoemptymsk;
    usb_otg_ep_t *ep;

    ep = &(gusb_dcd.in_ep[ep_idx]);
    len = ep->xfer_len - ep->actual_xfer_len;
    if (len > ep->maxpacket) {
        len = ep->maxpacket;
    }

    len32b = (len + 3U) / 4U;

    /* While there is space in the queue and space in the FIFO and More data to transfer, Write packets to the Tx FIFO */
    while (((USB_INEP_REGS(ep_idx)->DTXFSTS & USB_DTXFSTS_INEPTFSAV_Msk) >= len32b) && (ep->actual_xfer_len < ep->xfer_len) && (ep->xfer_len != 0U)) {
        /* Write the FIFO */
        len = ep->xfer_len - ep->actual_xfer_len;
        if (len > ep->maxpacket) {
            len = ep->maxpacket;
        }

        if (ep->type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
            if ((USB_DREGS->DSTS & (1U << 8)) == 0U) {
                USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
                USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SODDFRM_Msk;
            } else {
                USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
                USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SODDFRM_Msk;
            }
            USB_INEP_REGS(ep_idx)->DIEPTSIZ &= ~(USB_DIEPTSIZ_MULCNT_Msk);
            USB_INEP_REGS(ep_idx)->DIEPTSIZ |= (USB_DIEPTSIZ_MULCNT_Msk & (1U << 29));
        }

        usbd_write_packet(ep->xfer_buff, ep_idx, len);
        ep->xfer_buff += len;
        ep->actual_xfer_len += len;
    }

    /* Mask the TxFIFOEmpty interrupt  */
    if (ep->xfer_len <= ep->actual_xfer_len) {
        fifoemptymsk = 0x1UL << ep_idx;
        USB_DREGS->DIEPEMPMSK &= ~fifoemptymsk;
    }
}

/**
* @brief  usbd_sessionrequest_isr
*         Indicates that the USB_OTG controller has detected a connection
* @param  None
* @retval None
*/
static void usbd_sessionrequest_isr(void)
{
    if (usbd_int_fops.dev_connected) {
        usbd_int_fops.dev_connected();
    }

    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_SRQINT_Msk;
}

/**
* @brief  usbd_otg_isr
*         Indicates that the USB_OTG controller has detected an OTG event:
*                 used to detect the end of session i.e. disconnection
* @param  None
* @retval None
*/
static void usbd_otg_isr(void)
{
    uint32_t temp = 0;
    temp = USB_GREGS->GOTGINT;
    if (temp & USB_GOTGINT_SEDET_Msk) {
        if (usbd_int_fops.dev_disconnected) {
            usbd_int_fops.dev_disconnected();
        }
    }
    /* Clear OTG interrupt */
    USB_GREGS->GOTGINT |= temp;
}

/**
* @brief  usbd_resume_isr
*         Indicates that the USB_OTG controller has detected a resume or
*                 remote Wake-up sequence
* @param  None
* @retval None
*/
static void usbd_resume_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_WKUINT_Msk;
    /* Inform upper layer by the Resume Event */
    if (usbd_int_fops.resume) {
        usbd_int_fops.resume();
    }
}

/**
* @brief  usbd_suspend_isr
*         Indicates that SUSPEND state has been detected on the USB
* @param  None
* @retval None
*/
static void usbd_suspend_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_USBSUSP_Msk;

    if (usbd_int_fops.suspend) {
        usbd_int_fops.suspend();
    }
}

/**
* @brief  usbd_inep_isr
*         Indicates that an IN EP has a pending Interrupt
* @param  None
* @retval None
*/
static inline void usbd_inep_isr(void)
{
    uint32_t ep_intr = 0;
    uint32_t epnum = 0;
    uint32_t diepint = 0;
    usb_setup_req_t *req = &(gusb_dcd.rx_setup_packet);
    usb_otg_ep_t *ep;

    ep_intr = usbd_read_allinep_itr();
    while (ep_intr) {
        if (ep_intr & 0x1U) {
            diepint = usbd_read_inep_itr(epnum);
            if ((diepint & USB_DIEPINT_XFRC_Msk) == USB_DIEPINT_XFRC_Msk) {
                ep = &(gusb_dcd.in_ep[epnum & 0x7f]);
                if (epnum == 0) {
                    ep->actual_xfer_len = ep->xfer_len - (USB_INEP_REGS(epnum & 0x7f)->DIEPTSIZ & USB_DIEPTSIZ_XFRSIZ_Msk);
                    ep->xfer_len = 0;
                    usbd_stallstage_timeout();
                    if (usbd_int_fops.datain_stage) {
                        usbd_int_fops.datain_stage(&(gusb_dcd.rx_setup_packet), ep->actual_xfer_len);
                    }
                    if ((req->wLength && ((req->bmRequestType & USB_REQ_DIR_MASK) == USB_REQ_DIR_OUT)) || (req->wLength == 0)) {
                        usbd_ep0_read_setup((uint8_t *)req);
                    }
                } else {
                    ep->actual_xfer_len = ep->xfer_len - ((USB_INEP_REGS(epnum & 0x7f)->DIEPTSIZ & USB_DIEPTSIZ_XFRSIZ_Msk) >> USB_DIEPTSIZ_XFRSIZ_Pos);
                    ep->xfer_len = 0;
                    if (ep->cb != NULL) {
                        ep->cb((epnum | 0x80), ep->actual_xfer_len);
                    }
                }
            }
            if ((diepint & USB_DIEPINT_TXFE_Msk) == USB_DIEPINT_TXFE_Msk) {
                usbd_write_emptytxfifo((epnum | 0x80));
            }
        }
        epnum++;
        ep_intr >>= 1U;
    }
}

/**
* @brief  usbd_outep_isr
*         Indicates that an OUT EP has a pending Interrupt
* @param  None
* @retval None
*/
static inline void usbd_outep_isr(void)
{
    uint32_t ep_intr = 0;
    uint32_t epnum = 0;
    uint32_t doepint = 0;
    usb_otg_ep_t *ep;

    ep_intr = usbd_read_alloutep_itr();
    while (ep_intr) {
        if (ep_intr & 0x1U) {
            doepint = usbd_read_outep_itr(epnum & 0x7f);
            if ((doepint & USB_DOEPINT_XFRC_Msk) == USB_DOEPINT_XFRC_Msk) {
                ep = &(gusb_dcd.out_ep[epnum & 0x7f]);
                if (epnum == 0) {
                    if (ep->xfer_len == 0) {
                        usbd_stallstage_disable();
                        usbd_ep0_read_setup((uint8_t *)&(gusb_dcd.rx_setup_packet));
                    } else {
                        ep->actual_xfer_len = ep->xfer_len - (USB_OUTEP_REGS(epnum & 0x7f)->DOEPTSIZ & USB_DOEPTSIZ_XFRSIZ_Msk);
                        ep->xfer_len = 0;
                        if (usbd_int_fops.dataout_stage) {
                            usbd_int_fops.dataout_stage(&(gusb_dcd.rx_setup_packet), ep->actual_xfer_len);
                        }
                    }
                } else {
                    ep->actual_xfer_len = ep->xfer_len - (USB_OUTEP_REGS(epnum & 0x7f)->DOEPTSIZ & USB_DOEPTSIZ_XFRSIZ_Msk);
                    ep->xfer_len = 0;
                    if (ep->cb) {
                        ep->cb((epnum & 0x7f), ep->actual_xfer_len);
                    }
                }
            }
            if ((doepint & USB_DOEPINT_STUP_Msk) == USB_DOEPINT_STUP_Msk) {
                usbd_stallstage_enable(&(gusb_dcd.rx_setup_packet));
                if (usbd_int_fops.setup_stage) {
                    usbd_int_fops.setup_stage(&(gusb_dcd.rx_setup_packet));
                }
            }
        }
        epnum++;
        ep_intr >>= 1U;
    }
}

/**
* @brief  usbd_sof_isr
*         Handles the sof Interrupts
* @param  None
* @retval None
*/
static void usbd_sof_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_SOF_Msk;
    usbd_stallstage_isr();
    if (usbd_int_fops.sof) {
        usbd_int_fops.sof();
    }
}

#ifndef USB_CFG_INTERNAL_DMA_ENABLE
/**
* @brief  usbd_rxstatusqueueLevel_isr
*         Handles the Rx Status Queue Level Interrupt
* @param  None
* @retval None
*/
static inline void usbd_rxstatusqueueLevel_isr(void)
{
    uint32_t epnum = 0;
    uint32_t status = 0;
    uint32_t read_count = 0;

    /* Disable the Rx Status Queue Level interrupt */
    USB_GREGS->GINTMSK &= ~(USB_GINTSTS_RXFLVL_Msk);

    /* Get the Status from the top of the FIFO */
    status = USB_GREGS->GRXSTSP;
    epnum = status & USB_GRXSTSP_EPNUM_Msk;

    switch ((status & USB_GRXSTSP_PKTSTS_Msk) >> USB_GRXSTSP_PKTSTS_Pos) {
    case STS_DATA_UPDT:
        read_count = (status & USB_GRXSTSP_BCNT_Msk) >> USB_GRXSTSP_BCNT_Pos;
        if (read_count) {
            usbd_read_packet(gusb_dcd.out_ep[epnum & 0x7f].xfer_buff, read_count);
            gusb_dcd.out_ep[epnum & 0x7f].xfer_buff += read_count;
        }
        break;

    case STS_SETUP_UPDT:
        /* Copy the setup packet received in FIFO into the setup buffer in RAM */
        read_count = (status & USB_GRXSTSP_BCNT_Msk) >> USB_GRXSTSP_BCNT_Pos;
        usbd_read_packet((uint8_t *)(&(gusb_dcd.rx_setup_packet)), read_count);
        break;
    }

    /* Enable the Rx Status Queue Level interrupt */
    USB_GREGS->GINTMSK |= (USB_GINTSTS_RXFLVL_Msk);
}
#endif

/**
* @brief  usbd_reset_isr
*         This interrupt occurs when a USB Reset is detected
* @param  None
* @retval None
*/
static void usbd_reset_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_USBRST_Msk;

    /* Clear the Remote Wake-up Signaling */
    USB_DREGS->DCTL &= ~USB_DCTL_RWUSIG_Msk;

    /* Flush the Tx FIFO */
    usbd_flush_txfifo(0x10U);
    usbd_flush_rxfifo();

    for (uint8_t i = 0U; i < (USB_CFG_DEVICE_EP_NUM - 1); i++) {
        if (i == 0U) {
            USB_INEP_REGS(i)->DIEPCTL = USB_DIEPCTL_SNAK_Msk;
            USB_OUTEP_REGS(i)->DOEPCTL = USB_DOEPCTL_SNAK_Msk;
        } else {
            if (USB_INEP_REGS(i)->DIEPCTL & USB_DIEPCTL_EPENA_Msk) {
                USB_INEP_REGS(i)->DIEPCTL = (USB_DIEPCTL_EPDIS_Msk | USB_DIEPCTL_SNAK_Msk);
            } else {
                USB_INEP_REGS(i)->DIEPCTL = 0;
            }
            if (USB_OUTEP_REGS(i)->DOEPCTL & USB_DOEPCTL_EPENA_Msk) {
                USB_OUTEP_REGS(i)->DOEPCTL = (USB_DOEPCTL_EPDIS_Msk | USB_DOEPCTL_SNAK_Msk);
            } else {
                USB_OUTEP_REGS(i)->DOEPCTL = 0;
            }
        }
        USB_INEP_REGS(i)->DIEPTSIZ = 0U;
        USB_INEP_REGS(i)->DIEPINT = 0xFBFFU;
        USB_OUTEP_REGS(i)->DOEPTSIZ = 0U;
        USB_OUTEP_REGS(i)->DOEPINT = 0xFBFFU;
    }

    USB_DREGS->DAINTMSK |= 0x10001U;
    USB_DREGS->DOEPMSK = USB_DOEPMSK_XFRCM_Msk | USB_DOEPMSK_STUPM_Msk;
    USB_DREGS->DIEPMSK = USB_DIEPMSK_XFRCM_Msk;

    /*Reset internal state machine */
    if (usbd_int_fops.reset) {
        usbd_int_fops.reset();
    }

    /* setup EP0 to receive SETUP packets */
    usbd_ep0_read_setup((uint8_t *)&(gusb_dcd.rx_setup_packet));
}

static void usbd_set_turnaroundtime(uint32_t hclk, uint8_t speed)
{
    uint32_t UsbTrd;

    if (speed == USB_SPEED_FULL) {
        if ((hclk >= 14200000U) && (hclk < 15000000U)) {
            UsbTrd = 0xFU;
        } else if ((hclk >= 15000000U) && (hclk < 16000000U)) {
            UsbTrd = 0xEU;
        } else if ((hclk >= 16000000U) && (hclk < 17200000U)) {
            UsbTrd = 0xDU;
        } else if ((hclk >= 17200000U) && (hclk < 18500000U)) {
            UsbTrd = 0xCU;
        } else if ((hclk >= 18500000U) && (hclk < 20000000U)) {
            UsbTrd = 0xBU;
        } else if ((hclk >= 20000000U) && (hclk < 21800000U)) {
            UsbTrd = 0xAU;
        } else if ((hclk >= 21800000U) && (hclk < 24000000U)) {
            UsbTrd = 0x9U;
        } else if ((hclk >= 24000000U) && (hclk < 27700000U)) {
            UsbTrd = 0x8U;
        } else if ((hclk >= 27700000U) && (hclk < 32000000U)) {
            UsbTrd = 0x7U;
        } else {
            UsbTrd = 0x6U;
        }
    } else if (speed == USB_SPEED_HIGH) {
        UsbTrd = USBD_HS_TRDT_VALUE;
    } else {
        UsbTrd = USBD_DEFAULT_TRDT_VALUE;
    }

    /* Set USB turn-around time based on device speed and PHY interface. */
    USB_GREGS->GUSBCFG |= USB_GUSBCFG_TOCAL_Msk;
    USB_GREGS->GUSBCFG &= ~USB_GUSBCFG_TRDT_Msk;
    USB_GREGS->GUSBCFG |= (uint32_t)((UsbTrd << USB_GUSBCFG_TRDT_Pos) & USB_GUSBCFG_TRDT_Msk);
}

/**
* @brief  usbd_enumdone_isr
*         Read the device status register and set the device speed
* @param  None
* @retval None
*/
static void usbd_enumdone_isr(void)
{
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_ENUMDNE_Msk;
    usbd_set_turnaroundtime(usb_mclk0_g_freq(), usbd_get_speed());
    USB_DREGS->DCTL |= USB_DCTL_CGINAK_Msk;
}

/**
* @brief  usbd_isoin_incomplete_isr
*         handle the ISO IN incomplete interrupt
* @param  None
* @retval None
*/
static void usbd_isoin_incomplete_isr(void)
{
    uint32_t ep_idx = 0;
    uint32_t daintmask = 0;
    /**/
    daintmask = USB_DREGS->DAINTMSK;
    daintmask >>= 16;

    for (ep_idx = 1; ep_idx < (USB_CFG_DEVICE_EP_NUM - 1); ep_idx++) {
        if ((USB_BIT(ep_idx) & ~daintmask) || (gusb_dcd.in_ep[ep_idx].type != USB_ENDPOINT_TYPE_ISOCHRONOUS)) {
            continue;
        }

        if (!(USB_INEP_REGS(ep_idx)->DIEPCTL & USB_DIEPCTL_USBAEP_Msk)) {
            continue;
        }

        if ((USB_DREGS->DSTS & (1U << 8)) != 0U) {
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
            USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SODDFRM_Msk;
        } else {
            USB_INEP_REGS(ep_idx)->DIEPCTL &= ~USB_DIEPCTL_SD0PID_SEVNFRM_Msk;
            USB_INEP_REGS(ep_idx)->DIEPCTL |= USB_DIEPCTL_SODDFRM_Msk;
        }
    }
    /**/
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_IISOIXFR_Msk;
}

/**
* @brief  usbd_isoout_incomplete_isr
*         handle the ISO OUT incomplete interrupt
* @param  None
* @retval None
*/
static void usbd_isoout_incomplete_isr(void)
{
    uint32_t ep_idx = 0;
    uint32_t daintmask = 0;
    /**/
    daintmask = USB_DREGS->DAINTMSK;
    daintmask >>= 16;

    for (ep_idx = 1; ep_idx < (USB_CFG_DEVICE_EP_NUM - 1); ep_idx++) {
        if ((USB_BIT(ep_idx) & ~daintmask) || (gusb_dcd.out_ep[ep_idx].type != USB_ENDPOINT_TYPE_ISOCHRONOUS))
            continue;
        if (!(USB_OUTEP_REGS(ep_idx)->DOEPCTL & USB_DOEPCTL_USBAEP_Msk))
            continue;

        if ((USB_DREGS->DSTS & (1U << 8)) != 0U) {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_SD0PID_SEVNFRM_Msk;
            USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~USB_DOEPCTL_SODDFRM_Msk;
        } else {
            USB_OUTEP_REGS(ep_idx)->DOEPCTL &= ~USB_DOEPCTL_SD0PID_SEVNFRM_Msk;
            USB_OUTEP_REGS(ep_idx)->DOEPCTL |= USB_DOEPCTL_SODDFRM_Msk;
        }
    }
    /**/
    /* Clear interrupt */
    USB_GREGS->GINTSTS = USB_GINTSTS_PXFR_INCOMPISOOUT_Msk;
}

/**
* @brief  usbd_isr_handler
*         handles all USB Interrupts
* @param  None
* @retval None
*/
void usbd_isr_handler(void)
{
    uint32_t gintr_status = 0;
    gintr_status = usbd_read_coreitr();

    /* avoid spurious interrupt */
    if (gintr_status == 0) {
        return;
    }

#ifndef USB_CFG_INTERNAL_DMA_ENABLE
    /* Handle RxQLevel Interrupt */
    if (gintr_status & USB_GINTSTS_RXFLVL_Msk) {
        usbd_rxstatusqueueLevel_isr();
    }
#endif
    if (gintr_status & USB_GINTSTS_OEPINT_Msk) {
        usbd_outep_isr();
    }
    if (gintr_status & USB_GINTSTS_IEPINT_Msk) {
        usbd_inep_isr();
    }
    if (gintr_status & USB_GINTSTS_MMIS_Msk) {
        /* Clear interrupt */
        USB_GREGS->GINTSTS = USB_GINTSTS_MMIS_Msk;
    }
    if (gintr_status & USB_GINTSTS_WKUINT_Msk) {
        usbd_resume_isr();
    }
    if (gintr_status & USB_GINTSTS_USBSUSP_Msk) {
        usbd_suspend_isr();
    }
    if (gintr_status & USB_GINTSTS_SOF_Msk) {
        usbd_sof_isr();
    }
    if (gintr_status & USB_GINTSTS_USBRST_Msk) {
        usbd_reset_isr();
    }
    if (gintr_status & USB_GINTSTS_ENUMDNE_Msk) {
        usbd_enumdone_isr();
    }
    if (gintr_status & USB_GINTSTS_IISOIXFR_Msk) {
        usbd_isoin_incomplete_isr();
    }
    if (gintr_status & USB_GINTSTS_PXFR_INCOMPISOOUT_Msk) {
        usbd_isoout_incomplete_isr();
    }
    if (gintr_status & USB_GINTSTS_SRQINT_Msk) {
        usbd_sessionrequest_isr();
    }
    if (gintr_status & USB_GINTSTS_OTGINT_Msk) {
        usbd_otg_isr();
    }
}

/**
* @brief  active remote wakeup signalling
* @param  low_power
* @retval None
*/
void usbd_active_remotewakeup(uint8_t low_power)
{
    if (USB_DREGS->DSTS & USB_DSTS_SUSPSTS_Msk) {
        if (low_power) {
            /* un-gate USB Core clock */
            USB_PCGCCTL &= ~(USB_PCGCCTL_STOPCLK_Msk | USB_PCGCCTL_GATECLK_Msk);
        }
        /* active Remote wakeup signaling */
        USB_DREGS->DCTL |= USB_DCTL_RWUSIG_Msk;
        usb_delay_ms(5);
        USB_DREGS->DCTL &= ~USB_DCTL_RWUSIG_Msk;
    }
}

#ifdef USB_CFG_DEVICE_TEST_ENABLE
/**
 * @brief Usb execute test mode
 * @param  test_mode: usb test mode
 * @retval None
 */
void usbd_set_test_mode(uint8_t test_mode)
{
    uint32_t regval = 0;

    regval = USB_DREGS->DCTL;
    regval &= ~USB_DCTL_TCTL_Msk;

    switch (test_mode) {
    case 1: /* Test_J */
        //USB_LOG_INFO("Test_J\r\n");
        regval |= (1 << USB_DCTL_TCTL_Pos);
        break;

    case 2: /* Test_K */
        //USB_LOG_INFO("Test_K\r\n");
        regval |= (2 << USB_DCTL_TCTL_Pos);
        break;

    case 3: /* TEST_SE0_NAK */
        //USB_LOG_INFO("TEST_SE0_NAK\r\n");
        regval |= (3 << USB_DCTL_TCTL_Pos);
        break;

    case 4: /* Test_Packet */
        //USB_LOG_INFO("Test_Packet\r\n");
        regval |= (4 << USB_DCTL_TCTL_Pos);
        break;

    case 5: /* Test_Force_Enable */
        //USB_LOG_INFO("Test_Force_Enable\r\n");
        regval |= (5 << USB_DCTL_TCTL_Pos);
        break;

    default:
        break;
    }

    USB_DREGS->DCTL = regval;
}
#endif

/**
* @brief  get endpoint maxpacket
* @param  epnum : end point number
* @retval maxpacket
*/
uint16_t usbd_get_ep_mps(uint8_t epnum)
{
    if (epnum & 0x80) {
        return gusb_dcd.in_ep[epnum & 0x7f].maxpacket;
    } else {
        return gusb_dcd.out_ep[epnum & 0x7f].maxpacket;
    }
}

/**
* @brief  last packet is MPS multiple, so send ZLP packet
* @param  epnum : end point number
* @param  len : data length
* @retval tx status
*/
usb_status_t usbd_bulk_send_zlp(uint8_t epnum, uint32_t len)
{
    usb_otg_ep_t *ep = &(gusb_dcd.in_ep[epnum & 0x7f]);

    if (ep->type == USB_ENDPOINT_TYPE_BULK) {
        if ((len % usbd_get_ep_mps(epnum)) == 0 && len) {
            /* send zlp */
            usbd_ep_tx(epnum, NULL, 0);
            return USB_BUSY;
        } else {
            return USB_OK;
        }
    } else {
        return USB_OK;
    }
}

/**
 * @brief  get usbd interface callback
 * @param  None
 * @retval address of usbd_int_fops
 */
usb_dcd_int_cb_t *usbd_get_int_fops(void)
{
    return &usbd_int_fops;
}

/**
* @brief  configures EPO to receive SETUP packets
* @param  psetup: device instance
* @retval None
*/
void usbd_read_setup_packet(void)
{
    usbd_ep0_read_setup((uint8_t *)&(gusb_dcd.rx_setup_packet));
}

/**
* @brief  get the Transfer Completed Interrupt (XferCompl)
* @param  None
* @retval status
*/
uint8_t usbd_get_ep0_XferCompl(void)
{
    return ((USB_INEP_REGS(0)->DIEPINT & USB_DIEPINT_XFRC_Msk) >> USB_DIEPINT_XFRC_Pos);
}

#endif
#endif

/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\bluetooth\usbd_bluetooth.c
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: bluetooth adapter code
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

/**************************** include header ********************************/
#include "usbd_bluetooth.h"

#if USB_CFG_USE_USB
#if defined(USB_CFG_USE_OTG_MODE) || defined(USB_CFG_USE_DEVICE_MODE)

/*************************** macro definition ********************************/

/**************************** type definition ********************************/

/**************************** function declear *******************************/
static usb_status_t usbd_bt_class_interface_request(usb_setup_req_t *req, uint8_t **data, uint32_t *len);

/************************* variable definition *******************************/
extern usbd_core_t usb_dev_core;

static usbd_bt_class_t usbd_bt_handle = {
    /* bluetooth handle */
    .hci_cb = NULL,
    .intf_cb = {
        usbd_bt_class_interface_request,
        NULL,
        NULL,
    },
};

/********************** function implementation ******************************/
/**
 * @brief  get usb wireless class interface callback
 * @param  None
 * @retval None
 */
usbd_intf_cb_t *usbd_bt_get_inf_cb(void)
{
    return &(usbd_bt_handle.intf_cb);
}

/**
 * @brief  usbd_bt_class_interface_request
 *         Handles the wireless control request parsing.
 * @param  req: usb requests
 * @param  data: data
 * @param  len: data Length
 * @retval status
 */
static usb_status_t usbd_bt_class_interface_request(usb_setup_req_t *req, uint8_t **data, uint32_t *len)
{
    (void)data;
    (void)len;
    if (req->wLength) {
        if (req->bmRequestType & 0x80) /* bit7 = 0,data to device; bit7 = 1,data to host */
        {
        } else {
            usbd_pkt_header_t pkt;
            pkt.buff = usb_dev_core.data_buff;
            pkt.len = req->wLength;
            pkt.epnum = USB_CTL_OUT_EP0;
            if (usbd_bt_handle.hci_cb && usbd_bt_handle.hci_cb->cmd.cb != NULL) {
                usbd_bt_handle.hci_cb->cmd.cb(USB_EVT_NEW_DATA, &pkt);
            }
            pkt.buff = NULL;
        }
    }
    return USB_OK;
}

/**
 * @brief  usbd_hci_event_handle
 *         Handles the hci event IN data stage.pkt
 * @param  epnum: endpoint number
 * @param  len: data len
 * @retval status
 */
static usb_status_t usbd_hci_event_handle(uint8_t epnum, uint32_t len)
{
    (void)len;
    usbd_pkt_header_t *pkt;

    if (usbd_bt_handle.hci_cb) {
        USB_ASSERT_MSG(epnum == usbd_bt_handle.hci_cb->event.pkt.epnum, "Ep addr %02x error", epnum);

        pkt = &(usbd_bt_handle.hci_cb->event.pkt);
        if (usbd_bt_handle.hci_cb->event.cb != NULL) {
            usbd_bt_handle.hci_cb->event.cb(USB_EVT_SENT_OK, pkt);
        }
        if (usbd_bt_handle.hci_cb->free_ram != NULL) {
            usbd_bt_handle.hci_cb->free_ram(pkt->buff);
        }

#if USB_HCI_MALLOC_ENABLE
        pkt->buff = NULL;
#endif

        return USB_OK;
    } else {
        return USB_ERROR;
    }
}

/**
 * @brief  usbd_acl_in_handle
 *         Handles the IN data stage.
 * @param  epnum: endpoint number
 * @param  len: data len
 * @retval status
 */
static usb_status_t usbd_acl_in_handle(uint8_t epnum, uint32_t len)
{
    (void)len;
    usbd_pkt_header_t *pkt;

    if (usbd_bt_handle.hci_cb) {
        USB_ASSERT_MSG(epnum == usbd_bt_handle.hci_cb->acl_in.pkt.epnum, "Ep addr %02x error", epnum);

        pkt = &(usbd_bt_handle.hci_cb->acl_in.pkt);

        if (usbd_bt_handle.hci_cb->acl_in.cb != NULL) {
            usbd_bt_handle.hci_cb->acl_in.cb(USB_EVT_SENT_OK, pkt);
        }
        if (usbd_bt_handle.hci_cb->free_ram != NULL) {
            usbd_bt_handle.hci_cb->free_ram(pkt->buff);
        }

#if USB_HCI_MALLOC_ENABLE
        pkt->buff = NULL;
#endif
        return USB_OK;
    } else {
        return USB_ERROR;
    }
}

/**
 * @brief  usbd_acl_out_handle
 *         Handles the hci acl Out data handle.
 * @param  epnum: endpoint number
 * @param  len: data len
 * @retval status
 */
static usb_status_t usbd_acl_out_handle(uint8_t epnum, uint32_t len)
{
    usbd_pkt_header_t *rx_pkt = NULL;
    usbd_pkt_header_t *new_rx_pkt = NULL;

    if (usbd_bt_handle.hci_cb) {
        USB_ASSERT_MSG(epnum == usbd_bt_handle.hci_cb->acl_out.pkt.epnum, "Ep addr %02x error", epnum);

        rx_pkt = &(usbd_bt_handle.hci_cb->acl_out.pkt);

        if (rx_pkt != NULL) {
            /* notify bt a new packet from USB. */
            rx_pkt->len = len;
            rx_pkt->epnum = epnum;
            if (usbd_bt_handle.hci_cb->acl_out.cb != NULL) {
                usbd_bt_handle.hci_cb->acl_out.cb(USB_EVT_NEW_DATA, rx_pkt);
            }
        }
        if (usbd_bt_handle.hci_cb->free_ram != NULL) {
            usbd_bt_handle.hci_cb->free_ram(rx_pkt->buff);
        }

        rx_pkt->buff = NULL;

        /* alloc new memory for next packet. */
        new_rx_pkt = usbd_bt_get_ram(USB_HCI_EP_ACL_OUT);
        if (new_rx_pkt != NULL) {
            usbd_ep_preparerx(new_rx_pkt->epnum, new_rx_pkt->buff, new_rx_pkt->len);
        } else {
            USB_LOG_ERR("error:pkt == NULL\r\n");
        }
        return USB_OK;
    } else {
        return USB_ERROR;
    }
}

/**
 * @brief  usbd_isoch_in_handle
 *         Handles the IN data stage.
 * @param  epnum: endpoint number
 * @param  len: data len
 * @retval status
 */
static usb_status_t usbd_isoch_in_handle(uint8_t epnum, uint32_t len)
{
    (void)len;
    usbd_pkt_header_t *pkt;

    if (usbd_bt_handle.hci_cb) {
        USB_ASSERT_MSG(epnum == usbd_bt_handle.hci_cb->isoch_in.pkt.epnum, "Ep addr %02x error", epnum);

        pkt = &(usbd_bt_handle.hci_cb->isoch_in.pkt);
        if (usbd_bt_handle.hci_cb->isoch_in.cb != NULL) {
            usbd_bt_handle.hci_cb->isoch_in.cb(USB_EVT_SENT_OK, pkt);
        }

        if (usbd_bt_handle.hci_cb->free_ram) {
            usbd_bt_handle.hci_cb->free_ram(pkt->buff);
        }

#if USB_HCI_MALLOC_ENABLE
        pkt->buff = NULL;
#endif
        return USB_OK;
    } else {
        return USB_ERROR;
    }
}

/**
 * @brief  usbd_isoch_out_handle
 *         Handles the usb Out data handle.
 * @param  epnum: endpoint number
 * @param  len: data len
 * @retval status
 */
static usb_status_t usbd_isoch_out_handle(uint8_t epnum, uint32_t len)
{
    usbd_pkt_header_t *rx_pkt = NULL;
    usbd_pkt_header_t *new_rx_pkt = NULL;

    if (usbd_bt_handle.hci_cb) {
        USB_ASSERT_MSG(epnum == usbd_bt_handle.hci_cb->isoch_out.pkt.epnum, "Ep addr %02x error", epnum);

        rx_pkt = &(usbd_bt_handle.hci_cb->isoch_out.pkt);
        if (rx_pkt != NULL) {
            /* notify bt a new packet from USB. */
            rx_pkt->len = len;
            rx_pkt->epnum = epnum;
            if (usbd_bt_handle.hci_cb->isoch_out.cb != NULL) {
                usbd_bt_handle.hci_cb->isoch_out.cb(USB_EVT_NEW_DATA, rx_pkt);
            }
        }
        if (usbd_bt_handle.hci_cb->free_ram != NULL) {
            usbd_bt_handle.hci_cb->free_ram(rx_pkt->buff);
        }
        rx_pkt->buff = NULL;

        /* alloc new memory for next packet. */
        new_rx_pkt = usbd_bt_get_ram(USB_HCI_EP_ISOCH_OUT);
        if (new_rx_pkt != NULL) {
            usbd_ep_preparerx(new_rx_pkt->epnum, new_rx_pkt->buff, new_rx_pkt->len);
        } else {
            USB_LOG_ERR("error:pkt == NULL\r\n");
        }
        return USB_OK;
    } else {
        return USB_ERROR;
    }
}

/**
* @brief  usb bluetooth callback register
*
* @param  cb: \ref usbd_hci_cb_info_t
* @return none
* @note   none
*/
void usbd_bt_cb_register(usbd_hci_cb_info_t *cb)
{
    usbd_bt_handle.hci_cb = cb;

    usbd_endpoint_register(cb->event.pkt.epnum, usbd_hci_event_handle);
    usbd_endpoint_register(cb->acl_in.pkt.epnum, usbd_acl_in_handle);
    usbd_endpoint_register(cb->acl_out.pkt.epnum, usbd_acl_out_handle);
    usbd_endpoint_register(cb->isoch_in.pkt.epnum, usbd_isoch_in_handle);
    usbd_endpoint_register(cb->isoch_out.pkt.epnum, usbd_isoch_out_handle);
}

/**
* @brief  usb bluetooth callback function unregistration
*
* @param  none
* @return none
* @note   none
*/
void usbd_bt_cb_unregister(void)
{
    usbd_bt_handle.hci_cb = NULL;

    usbd_endpoint_unregister(usbd_bt_handle.hci_cb->event.pkt.epnum);
    usbd_endpoint_unregister(usbd_bt_handle.hci_cb->acl_in.pkt.epnum);
    usbd_endpoint_unregister(usbd_bt_handle.hci_cb->acl_out.pkt.epnum);
    usbd_endpoint_unregister(usbd_bt_handle.hci_cb->isoch_in.pkt.epnum);
    usbd_endpoint_unregister(usbd_bt_handle.hci_cb->isoch_out.pkt.epnum);
}

/**
* @brief  get ram
*
* @param  type: \ref usbd_hci_ep_type_t
* @return usbd_pkt_header_t
* @note   none
*/
usbd_pkt_header_t *usbd_bt_get_ram(usbd_hci_ep_type_t type)
{
    uint16_t len = 0;
    usbd_pkt_header_t *pkt = NULL;

    if (usbd_bt_handle.hci_cb) {
        switch ((uint8_t)type) {
        case USB_HCI_EP_CMD:
            pkt = &(usbd_bt_handle.hci_cb->cmd.pkt);
            len = usbd_bt_handle.hci_cb->cmd.pkt.buf_size;
            break;

        case USB_HCI_EP_EVENT:
            pkt = &(usbd_bt_handle.hci_cb->event.pkt);
            len = usbd_bt_handle.hci_cb->event.pkt.buf_size;
            break;

        case USB_HCI_EP_ACL_IN:
            pkt = &(usbd_bt_handle.hci_cb->acl_in.pkt);
            len = usbd_bt_handle.hci_cb->acl_in.pkt.buf_size;
            break;

        case USB_HCI_EP_ACL_OUT:
            pkt = &(usbd_bt_handle.hci_cb->acl_out.pkt);
            len = usbd_bt_handle.hci_cb->acl_out.pkt.buf_size;
            break;

        case USB_HCI_EP_ISOCH_IN:
            pkt = &(usbd_bt_handle.hci_cb->isoch_in.pkt);
            len = usbd_bt_handle.hci_cb->isoch_in.pkt.buf_size;
            break;

        case USB_HCI_EP_ISOCH_OUT:
            pkt = &(usbd_bt_handle.hci_cb->isoch_out.pkt);
            len = usbd_bt_handle.hci_cb->isoch_in.pkt.buf_size;
            break;
        }

        if (pkt != NULL && usbd_bt_handle.hci_cb->get_ram) {
            pkt->buff = usbd_bt_handle.hci_cb->get_ram(type, len);
            return pkt;
        }
    } else {
        USB_LOG_ERR("error:usbd_bt_handle.hci_cb == NULL\r\n");
    }
    USB_LOG_ERR("error:pbuff == NULL\r\n");
    return NULL;
}

/**
* @brief  set buff size
*
* @param  type: \ref usbd_hci_ep_type_t
* @param  len: buff size
* @return none
* @note   none
*/
void usbd_bt_set_buff_size(usbd_hci_ep_type_t type, uint16_t len)
{
    if (usbd_bt_handle.hci_cb) {
        switch ((uint8_t)type) {
        case USB_HCI_EP_CMD:
            usbd_bt_handle.hci_cb->cmd.pkt.buf_size = len;
            break;

        case USB_HCI_EP_EVENT:
            usbd_bt_handle.hci_cb->event.pkt.buf_size = len;
            break;

        case USB_HCI_EP_ACL_IN:
            usbd_bt_handle.hci_cb->acl_in.pkt.buf_size = len;
            break;

        case USB_HCI_EP_ACL_OUT:
            usbd_bt_handle.hci_cb->acl_out.pkt.buf_size = len;
            break;

        case USB_HCI_EP_ISOCH_IN:
            usbd_bt_handle.hci_cb->isoch_in.pkt.buf_size = len;
            break;

        case USB_HCI_EP_ISOCH_OUT:
            usbd_bt_handle.hci_cb->isoch_in.pkt.buf_size = len;
            break;
        }
    } else {
        USB_LOG_ERR("error:usbd_bt_handle.hci_cb == NULL\r\n");
    }
}

/**
* @brief  usb send data
*
* @param  pkt: \ref usbd_pkt_header_t
* @return type: \ref usbd_hci_ep_type_t
* @note   none
*/
usb_status_t usbd_bt_send_pkt(uint8_t *buff, uint16_t len, usbd_hci_ep_type_t type)
{
    usbd_pkt_header_t *pkt = NULL;

    if (usb_device_is_init() != 1) {
        return USB_UNINIT;
    }

    if (usbd_bt_handle.hci_cb) {
        switch ((uint8_t)type) {
        case USB_HCI_EP_EVENT:
            pkt = &(usbd_bt_handle.hci_cb->event.pkt);
            break;

        case USB_HCI_EP_ACL_IN:
            pkt = &(usbd_bt_handle.hci_cb->acl_in.pkt);
            break;

        case USB_HCI_EP_ISOCH_IN:
            pkt = &(usbd_bt_handle.hci_cb->isoch_in.pkt);
            break;
        }

        pkt->buff = usbd_bt_handle.hci_cb->get_ram(type, len);
#if USB_HCI_MEMCPY_ENABLE
        USB_ASSERT_MSG(pkt->buff != NULL, "Pbuff == NULL");
        memcpy(pkt->buff, buff, len);
#else
        pkt->buff = buff;
#endif
        pkt->len = len;

        /* usb tx data */
        if (usbd_ep_tx(pkt->epnum, pkt->buff, pkt->len) != USB_OK) {
            USB_LOG_ERR("error:pkt == NULL\r\n");
            return USB_FAIL;
        }

        return USB_OK;
    } else {
        USB_LOG_ERR("error:usbd_bt_handle.hci_cb == NULL\r\n");
        return USB_ERROR;
    }
}

#endif
#endif

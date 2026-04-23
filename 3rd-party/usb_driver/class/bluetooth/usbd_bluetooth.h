/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\bluetooth\usbd_bluetooth.h
 * @Version: V1.0.0
 * @Date: 2025-05-23 10:42:15
 * @Author: driver group
 * @Description: bluetooth adapter code
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USBD_BLUETOOTH_H__
#define __USBD_BLUETOOTH_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header ********************************/
#include "usbd_core.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define USB_HCI_MALLOC_ENABLE 0
#define USB_HCI_MEMCPY_ENABLE 0

#define USB_HCI_CMD_PACKET_SIZE       1024
#define USB_HCI_EVENT_PACKET_SIZE     1024
#define USB_HCI_ACL_IN_PACKET_SIZE    1024
#define USB_HCI_ACL_OUT_PACKET_SIZE   1024
#define USB_HCI_ISOCH_IN_PACKET_SIZE  1024
#define USB_HCI_ISOCH_OUT_PACKET_SIZE 1024

/**************************** type definition ********************************/
/**
 * @brief the events type of user callback which registered by usbd_cb_register()
 */
typedef enum {
    USB_EVT_SENT_OK,  ///< notify user a packet is send out. Memory can be freed
    USB_EVT_NEW_DATA, ///< notify user a rx packet is ready for used.
} usbd_notify_evt_t;

typedef enum {
    USB_HCI_EP_CMD,
    USB_HCI_EP_EVENT,
    USB_HCI_EP_ACL_IN,
    USB_HCI_EP_ACL_OUT,
    USB_HCI_EP_ISOCH_IN,
    USB_HCI_EP_ISOCH_OUT,
} usbd_hci_ep_type_t;

/**
 * @brief the usbd packet header info.
 */
typedef struct {
    uint16_t buf_size;
    uint16_t len;  ///< the packet length
    uint8_t epnum; ///< endpoint address
    uint8_t *buff; ///< data buff
} usbd_pkt_header_t;

/**
 * @brief the usb user callback type
 *
 * @param evt: the notify events
 * @param param: \ref usbd_pkt_header_t
 * @return USB_OK
 */
typedef void (*usbd_hci_cb_t)(usbd_notify_evt_t evt, usbd_pkt_header_t *pkt);

typedef struct {
    usbd_pkt_header_t pkt;
    usbd_hci_cb_t cb;
} hci_cb_t;

typedef struct {
    void *(*get_ram)(usbd_hci_ep_type_t type, uint32_t len);
    void (*free_ram)(void *addr);
    hci_cb_t cmd;
    hci_cb_t event;
    hci_cb_t acl_in;
    hci_cb_t acl_out;
    hci_cb_t isoch_in;
    hci_cb_t isoch_out;
} usbd_hci_cb_info_t;

typedef struct {
    usbd_hci_cb_info_t *hci_cb;
    usbd_intf_cb_t intf_cb;
} usbd_bt_class_t;

/************************* variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  get usb wireless class interface callback
 * @param  None
 * @retval None
 */
extern usbd_intf_cb_t *usbd_bt_get_inf_cb(void);
/**
* @brief  usb bluetooth callback register
*
* @param  cb: \ref usbd_hci_cb_info_t
* @return none
* @note   none
*/
extern void usbd_bt_cb_register(usbd_hci_cb_info_t *cb);
/**
* @brief  usb bluetooth callback function unregistration
*
* @param  none
* @return none
* @note   none
*/
extern void usbd_bt_cb_unregister(void);
/**
* @brief  get ram
*
* @param  type: \ref usbd_hci_ep_type_t
* @return usbd_pkt_header_t
* @note   none
*/
extern usbd_pkt_header_t *usbd_bt_get_ram(usbd_hci_ep_type_t type);
/**
* @brief  set buff size
*
* @param  type: \ref usbd_hci_ep_type_t
* @param  len: buff size
* @return none
* @note   none
*/
extern void usbd_bt_set_buff_size(usbd_hci_ep_type_t type, uint16_t len);
/**
* @brief  usb send data
*
* @param  pkt: \ref usbd_pkt_header_t
* @return type: \ref usbd_hci_ep_type_t
* @note   none
*/
extern usb_status_t usbd_bt_send_pkt(uint8_t *buff, uint16_t len, usbd_hci_ep_type_t type);

#endif

#ifdef __cplusplus
}
#endif

#endif

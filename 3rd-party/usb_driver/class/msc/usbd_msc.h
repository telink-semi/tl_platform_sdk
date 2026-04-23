/*
 * @FilePath: \epm_driver\third_party\usb_driver\class\msc\usbd_msc.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header for usbd_msc.c file.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */
#ifndef __USBD_MSC_H__
#define __USBD_MSC_H__

#ifdef __cplusplus
extern "C" {
#endif

/**************************** include header *********************************/
#include "usbd_core.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define MSC_MAX_CDB_LEN (16) /* Max length of SCSI Command Data Block */

#define USBD_STD_INQUIRY_LENGTH 36

/**************************** type definition ********************************/
typedef enum {
    MSC_READ_CBW = 0, /* Command Block Wrapper */
    MSC_DATA_OUT = 1, /* Data Out Phase */
    MSC_DATA_IN = 2,  /* Data In Phase */
    MSC_SEND_CSW = 3, /* Command Status Wrapper */
    MSC_WAIT_CSW = 4, /* Command Status Wrapper */
} usbd_msc_state_t;

typedef struct {
    uint8_t ep_addr;
    ep_callback_t cb;
} usb_msc_ep_t;

typedef struct {
    usb_status_t (*init)(uint8_t lun);
    usb_status_t (*get_capacity)(uint8_t lun, uint32_t *block_num, uint32_t *block_size);
    usb_status_t (*is_writeprotected)(uint8_t lun);
    usb_status_t (*read)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint32_t length);
    usb_status_t (*write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint32_t length);
    uint8_t (*get_maxlun)(void);
    uint8_t *pinquiry;
} usbd_msc_cb_t;

typedef struct {
    usb_msc_ep_t ep[2];
    const usbd_msc_cb_t *cb;
    usbd_intf_cb_t intf_cb;
} usbd_msc_class_t;

/** MSC Bulk-Only Command Block Wrapper (CBW) */
struct bot_cbw {
    uint32_t dSignature;         /* 'USBC' = 0x43425355 */
    uint32_t dTag;               /* Depends on command id */
    uint32_t dDataLength;        /* Number of bytes that host expects to transfer */
    uint8_t bmFlags;             /* Bit 7: Direction=IN (other obsolete or reserved) */
    uint8_t bLUN;                /* LUN (normally 0) */
    uint8_t bCBLength;           /* len of cdb[] */
    uint8_t cb[MSC_MAX_CDB_LEN]; /* Command Data Block */
} __PACKED;

/** MSC Bulk-Only Command Status Wrapper (CSW) */
struct bot_csw {
    uint32_t dSignature;   /* 'USBS' = 0x53425355 */
    uint32_t dTag;         /* Same tag as original command */
    uint32_t dDataResidue; /* Amount not transferred */
    uint8_t bStatus;       /* Status of transfer */
} __PACKED;

typedef struct {
    usbd_msc_state_t status;
    uint8_t sKey;
    uint8_t ASC;
    uint8_t ASQ;
    uint8_t maxlun;
    uint32_t blk_addr;
    uint32_t blk_len;
    uint32_t blk_size[USB_CFG_MSC_MAX_LUN];
    uint32_t blk_nbr[USB_CFG_MSC_MAX_LUN];
    USB_MEM_ALIGNX uint8_t buffer[USB_CFG_MSC_BUF_SIZE];
} usbd_msc_t;

/**************************** variable declear *******************************/

/**************************** function declear *******************************/
/**
 * @brief  usb msc callback register
 * @param  out_ep out endpoint
 * @param  in_ep in endpoint
 * @retval None
 */
extern void usbd_msc_class_init(uint8_t out_ep, uint8_t in_ep);

/**
 * @brief  usb msc callback register
 * @param  cb \ref usbd_msc_cb_t
 * @retval None
 */
extern void usbd_msc_cb_register(usbd_msc_cb_t *cb);
/**
 * @brief  usb msc callback unregister
 * @param  None
 * @retval None
 */
extern void usbd_msc_cb_unregister(void);

/**
 * @brief  get usb msc class interface callback
 * @param  None
 * @retval None
 */
extern usbd_intf_cb_t *usbd_msc_get_inf_cb(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* USBD_MSC_H */

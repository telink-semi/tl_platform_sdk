/*
 * @FilePath: \epm_driver\third_party\usb_driver\port\usb_conf.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header file for usb.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USB_CONF_H__
#define __USB_CONF_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "tl_chip.h"
#include "common.h"

/*************************** macro definition ********************************/
#define USB_CFG_PRINTF(...) LOG_INF(__VA_ARGS__)

/****************** USB CONFIGURATION ********************************/
//#define USB_CFG_USE_USB (1)

/* Enable test mode */
#ifndef USB_CFG_DEBUG_ENABLE
#define USB_CFG_DEBUG_ENABLE
#endif

#ifndef USB_CFG_DEVICE_TEST_ENABLE
#define USB_CFG_DEVICE_TEST_ENABLE
#endif

#ifndef USB_CFG_FS_CORE_ENABLE
//#define USB_CFG_FS_CORE_ENABLE
#endif
#ifndef USB_CFG_HS_CORE_ENABLE
//#define USB_CFG_HS_CORE_ENABLE
#endif

#ifndef USB_CFG_VBUS_SENSING_ENABLE
//#define USB_CFG_VBUS_SENSING_ENABLE
#endif
#ifndef USB_CFG_IP_CONIDSTS_ENABLE
//#define USB_CFG_IP_CONIDSTS_ENABLE
#endif
#ifndef USB_CFG_SOFTWARE_CONIDSTS_ENABLE
//#define USB_CFG_SOFTWARE_CONIDSTS_ENABLE
#endif
#ifndef USB_CFG_INTERNAL_DMA_ENABLE
//#define USB_CFG_INTERNAL_DMA_ENABLE
#endif
#ifndef USB_CFG_SOF_OUTPUT_ENABLE
//#define USB_CFG_SOF_OUTPUT_ENABLE
#endif
#ifndef USB_CFG_LOW_PWR_MGMT_SUPPORT
//#define USB_CFG_LOW_PWR_MGMT_SUPPORT
#endif

/****************** USB OTG MODE CONFIGURATION ********************************/
#ifndef USB_CFG_USE_HOST_MODE
//#define USB_CFG_USE_HOST_MODE
#endif
#ifndef USB_CFG_USE_DEVICE_MODE
//#define USB_CFG_USE_DEVICE_MODE
#endif
#ifndef USB_CFG_USE_OTG_MODE
//#define USB_CFG_USE_OTG_MODE
#endif

/****************** USB FIFO SIZE CONFIGURATION **********************************/
#define USB_CFG_DEVICE_RX_FIFO_SIZE   (512)
#define USB_CFG_DEVICE_TX0_FIFO_SIZE  (64)
#define USB_CFG_DEVICE_TX1_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX2_FIFO_SIZE  (256) /* cdc demo use 256*4 bytes  */
#define USB_CFG_DEVICE_TX3_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX4_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX5_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX6_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX7_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX8_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX9_FIFO_SIZE  (128)
#define USB_CFG_DEVICE_TX10_FIFO_SIZE (128)
#define USB_CFG_DEVICE_TX11_FIFO_SIZE (128)
#define USB_CFG_DEVICE_TX12_FIFO_SIZE (128)
#define USB_CFG_DEVICE_TX13_FIFO_SIZE (128)
#define USB_CFG_DEVICE_TX14_FIFO_SIZE (128)
#define USB_CFG_DEVICE_TX15_FIFO_SIZE (128)

#define USB_CFG_HOST_NPTX_FIFO_SIZE (128)
#define USB_CFG_HOST_PTX_FIFO_SIZE  (256)
#define USB_CFG_HOST_RX_FIFO_SIZE   ((1012 - USB_CFG_HOST_NPTX_FIFO_SIZE - USB_CFG_HOST_PTX_FIFO_SIZE))

/* ================ USB Device Configuration ================*/
#ifndef USB_CFG_DEVICE_REQ_BUF_LEN
#define USB_CFG_DEVICE_REQ_BUF_LEN 2048
#endif

#ifndef USB_CFG_DEVICE_EP_NUM
#define USB_CFG_DEVICE_EP_NUM 16
#endif

#ifdef USB_CFG_FS_CORE_ENABLE
#define USB_MAX_PACKET_SIZE 0x40
#else
#define USB_MAX_PACKET_SIZE 0x200
#endif

#ifndef USB_CFG_MSC_MAX_LUN
#define USB_CFG_MSC_MAX_LUN 1
#endif
#define USB_CFG_MSC_BUF_SIZE 16 * 1024

/* ================ USB Host Configuration ==================*/
#ifndef USB_CFG_HOST_CHANNELS
#define USB_CFG_HOST_CHANNELS 16
#endif

#ifndef USB_CFG_HOST_CLASS_NUM
#define USB_CFG_HOST_CLASS_NUM 4
#endif

#define USBH_MAX_NUM_INTERFACES 6
#define USBH_MAX_NUM_ALTERNATES 4
#define USBH_MAX_NUM_ENDPOINTS  6

#define USBH_MAX_DATA_BUFFER 0x400

/**************************** type definition ********************************/

/**************************** variable declear *******************************/

/**************************** function declear *******************************/

#ifdef __cplusplus
}
#endif

#endif

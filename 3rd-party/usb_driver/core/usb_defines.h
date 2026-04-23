/*
 * @FilePath: \epm_driver\third_party\usb_driver\core\usb_defines.h
 * @Version: V1.0.0
 * @Date: 2025-05-13 18:33:50
 * @Author: driver group
 * @Description: Header file for usb.
 * Copyright (C) 2025-2035 Expanse Micro, All Rights Reserved.
 */

#ifndef __USB_DEFINES_H__
#define __USB_DEFINES_H__

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

/**************************** include header *********************************/
#include "usb_conf.h"

#if USB_CFG_USE_USB

/*************************** macro definition ********************************/
#define usb_dbg_log_line(lvl, fmt, ...)     \
    do {                                    \
        USB_CFG_PRINTF("[" lvl "/"          \
                       "USB] ");            \
        USB_CFG_PRINTF(fmt, ##__VA_ARGS__); \
    } while (0)

#define USB_LOG_INFO(fmt, ...) usb_dbg_log_line("I", fmt, ##__VA_ARGS__)
#define USB_LOG_ERR(fmt, ...)  usb_dbg_log_line("E", fmt, ##__VA_ARGS__)

#define USB_ASSERT(f)                                                            \
    do {                                                                         \
        if (!(f)) {                                                              \
            USB_LOG_ERR("ASSERT FAIL [%s] @ %s:%d\r\n", #f, __FILE__, __LINE__); \
            while (1) {                                                          \
            }                                                                    \
        }                                                                        \
    } while (false)

#define USB_ASSERT_MSG(f, fmt, ...)                                              \
    do {                                                                         \
        if (!(f)) {                                                              \
            USB_LOG_ERR("ASSERT FAIL [%s] @ %s:%d\r\n", #f, __FILE__, __LINE__); \
            USB_LOG_ERR(fmt "\r\n", ##__VA_ARGS__);                              \
            while (1) {                                                          \
            }                                                                    \
        }                                                                        \
    } while (false)

#if defined(__CC_ARM)

#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif

#elif defined(__GNUC__)

#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif

#elif defined(__ICCARM__) || defined(__ICCRX__) || defined(__ICCRISCV__)

#ifndef __PACKED
#if defined(__ICCARM_V8) || defined(__ICCRISCV__)
#define __PACKED __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED __packed
#endif
#endif

#endif

#ifndef NULL
#define NULL (0)
#endif

#ifndef USB_LOBYTE
#define USB_LOBYTE(x) ((uint8_t)(x & 0x00FF))
#endif

#ifndef USB_HIBYTE
#define USB_HIBYTE(x) ((uint8_t)((x & 0xFF00) >> 8))
#endif

#ifndef USB_MAX
#define USB_MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef USB_MIN
#define USB_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef USB_BCD
#define USB_BCD(x) ((((x) / 10) << 4) | ((x) % 10))
#endif

#ifndef USB_BIT
#define USB_BIT(n) (1UL << (n))
#endif

#define USB_LE16(addr)      (((uint16_t)(*((uint8_t *)(addr)))) + (((uint16_t)(*(((uint8_t *)(addr)) + 1))) << 8))
#define USB_GET_BE16(field) (((uint16_t)(field)[0] << 8) | ((uint16_t)(field)[1]))
#define USB_GET_BE32(field) (((uint32_t)(field)[0] << 24) | ((uint32_t)(field)[1] << 16) | ((uint32_t)(field)[2] << 8) | ((uint32_t)(field)[3] << 0))

#ifndef USB_WBVAL
#define USB_WBVAL(x) (x & 0xFF), ((x >> 8) & 0xFF)
#endif
#ifndef USB_DBVAL
#define USB_DBVAL(x) (x & 0xFF), ((x >> 8) & 0xFF), ((x >> 16) & 0xFF), ((x >> 24) & 0xFF)
#endif

#define USB_MEM_ALIGNX __attribute__((aligned(4)))

#define USB_SAMPLE_FREQ(frq) (uint8_t)(frq), (uint8_t)((frq >> 8)), (uint8_t)((frq >> 16))
#define USB_PACKET_SZE(val)  (uint8_t)((val) & 0xFF), (uint8_t)(((val) >> 8) & 0xFF)

/** @defgroup USB_LL_Turnaround_Timeout Turnaround Timeout Value
  * @{
  */
#ifndef USBD_HS_TRDT_VALUE
#define USBD_HS_TRDT_VALUE 9U
#endif /* USBD_HS_TRDT_VALUE */
#ifndef USBD_FS_TRDT_VALUE
#define USBD_FS_TRDT_VALUE      5U
#define USBD_DEFAULT_TRDT_VALUE 9U
#endif /* USBD_HS_TRDT_VALUE */

/* Default USB control EP, always 0 and 0x80 */
#define USB_CTL_OUT_EP0 0
#define USB_CTL_IN_EP0  0x80

/**< maximum packet size (MPS) for EP 0 */
#define USB_CTL_EP_MPS 64

/* general descriptor field offsets */
#define DESC_bLength            0 /** Length offset */
#define DESC_bDescriptorType    1 /** Descriptor type offset */
#define DESC_bDescriptorSubType 2 /** Descriptor subtype offset */
#define DESC_bTerminalType      4 /** Descriptor terminal offset */

/* config descriptor field offsets */
#define CONF_DESC_wTotalLength        2 /** Total length offset */
#define CONF_DESC_bConfigurationValue 5 /** Configuration value offset */
#define CONF_DESC_bmAttributes        7 /** configuration characteristics */

/* interface descriptor field offsets */
#define INTF_DESC_bInterfaceNumber  2 /** Interface number offset */
#define INTF_DESC_bAlternateSetting 3 /** Alternate setting offset */

/* Device speeds */
#define USB_SPEED_UNKNOWN      0U /* Transfer rate not yet set */
#define USB_SPEED_LOW          1U /* USB 1.1 */
#define USB_SPEED_FULL         2U /* USB 1.1 */
#define USB_SPEED_HIGH         3U /* USB 2.0 */
#define USB_SPEED_WIRELESS     4U /* Wireless USB 2.5 */
#define USB_SPEED_SUPER        5U /* USB 3.0 */
#define USB_SPEED_SUPER_PLUS   6U /* USB 3.1 */
#define USB_SPEED_HIGH_IN_FULL 7U

#define USB_SPEED_PARAM_HIGH         (0)
#define USB_SPEED_PARAM_HIGH_IN_FULL (1)
#define USB_SPEED_PARAM_FULL         (3)

#define GAHBCFG_TXFEMPTYLVL_EMPTY     (1)
#define GAHBCFG_TXFEMPTYLVL_HALFEMPTY (0)
#define GAHBCFG_GLBINT_ENABLE         (1)
#define GAHBCFG_INT_DMA_BURST_SINGLE  (0)
#define GAHBCFG_INT_DMA_BURST_INCR    (1)
#define GAHBCFG_INT_DMA_BURST_INCR4   (3)
#define GAHBCFG_INT_DMA_BURST_INCR8   (5)
#define GAHBCFG_INT_DMA_BURST_INCR16  (7)
#define GAHBCFG_DMAENABLE             (1)

#define GRXSTS_PKTSTS_IN              (2)
#define GRXSTS_PKTSTS_IN_XFER_COMP    (3)
#define GRXSTS_PKTSTS_DATA_TOGGLE_ERR (5)
#define GRXSTS_PKTSTS_CH_HALTED       (7)

#define MODE_HNP_SRP_CAPABLE       (0)
#define MODE_SRP_ONLY_CAPABLE      (1)
#define MODE_NO_HNP_SRP_CAPABLE    (2)
#define MODE_SRP_CAPABLE_DEVICE    (3)
#define MODE_NO_SRP_CAPABLE_DEVICE (4)
#define MODE_SRP_CAPABLE_HOST      (5)
#define MODE_NO_SRP_CAPABLE_HOST   (6)

#define USB_DEVICE_MODE (0)
#define USB_HOST_MODE   (1)
#define USB_OTG_MODE    (2)

#define USB_MODEA (0)
#define USB_MODEB (1)

#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ (0)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ (1)
#define DSTS_ENUMSPD_LS_PHY_6MHZ           (2)
#define DSTS_ENUMSPD_FS_PHY_48MHZ          (3)

#define DCFG_FRAME_INTERVAL_80 (0)
#define DCFG_FRAME_INTERVAL_85 (1)
#define DCFG_FRAME_INTERVAL_90 (2)
#define DCFG_FRAME_INTERVAL_95 (3)

#define DEP0CTL_MPS_64 (0)
#define DEP0CTL_MPS_32 (1)
#define DEP0CTL_MPS_16 (2)
#define DEP0CTL_MPS_8  (3)

#define EP_SPEED_LOW  (0)
#define EP_SPEED_FULL (1)
#define EP_SPEED_HIGH (2)

#define STS_GOUT_NAK   (1)
#define STS_DATA_UPDT  (2)
#define STS_XFER_COMP  (3)
#define STS_SETUP_COMP (4)
#define STS_SETUP_UPDT (6)

#define HC_PID_DATA0 (0)
#define HC_PID_DATA2 (1)
#define HC_PID_DATA1 (2)
#define HC_PID_SETUP (3)

#define HPRT0_PRTSPD_HIGH_SPEED (0)
#define HPRT0_PRTSPD_FULL_SPEED (1)
#define HPRT0_PRTSPD_LOW_SPEED  (2)

#define HCFG_30_60_MHZ (0)
#define HCFG_48_MHZ    (1)
#define HCFG_6_MHZ     (2)

#define HCCHAR_CTRL (0)
#define HCCHAR_ISOC (1)
#define HCCHAR_BULK (2)
#define HCCHAR_INTR (3)

/* bmRequestType :D7 Data Phase Transfer Direction  */
#define USB_H2D           (0x00)
#define USB_D2H           (0x80)
#define USB_REQ_DIR_SHIFT 7U                        /* Bits 7: Request dir */
#define USB_REQ_DIR_OUT   (0U << USB_REQ_DIR_SHIFT) /* Bit 7=0: Host-to-device */
#define USB_REQ_DIR_IN    (1U << USB_REQ_DIR_SHIFT) /* Bit 7=1: Device-to-host */
#define USB_REQ_DIR_MASK  (1U << USB_REQ_DIR_SHIFT) /* Bit 7=1: Direction bit */

/* bmRequestType D6..5 Type */
#define USB_REQ_TYPE_SHIFT 5U /* Bits 5:6: Request type */
#define USB_REQ_STANDARD   (0U << USB_REQ_TYPE_SHIFT)
#define USB_REQ_CLASS      (1U << USB_REQ_TYPE_SHIFT)
#define USB_REQ_VENDOR     (2U << USB_REQ_TYPE_SHIFT)
#define USB_REQ_RESERVED   (3U << USB_REQ_TYPE_SHIFT)
#define USB_REQ_TYPE_MASK  (3U << USB_REQ_TYPE_SHIFT)

/* bmRequestType D4..0 Recipient */
#define USB_REQ_RECIPIENT_SHIFT     0U /* Bits 0:4: Recipient */
#define USB_REQ_RECIPIENT_DEVICE    (0U << USB_REQ_RECIPIENT_SHIFT)
#define USB_REQ_RECIPIENT_INTERFACE (1U << USB_REQ_RECIPIENT_SHIFT)
#define USB_REQ_RECIPIENT_ENDPOINT  (2U << USB_REQ_RECIPIENT_SHIFT)
#define USB_REQ_RECIPIENT_OTHER     (3U << USB_REQ_RECIPIENT_SHIFT)
#define USB_REQ_RECIPIENT_MASK      (3U << USB_REQ_RECIPIENT_SHIFT)

/* USB Standard Request Codes */
#define USB_REQ_TYPE_STANDARD 0x00
#define USB_REQ_TYPE_CLASS    0x20

#define USB_REQ_GET_STATUS          0x00
#define USB_REQ_CLEAR_FEATURE       0x01
#define USB_REQ_SET_FEATURE         0x03
#define USB_REQ_SET_ADDRESS         0x05
#define USB_REQ_GET_DESCRIPTOR      0x06
#define USB_REQ_SET_DESCRIPTOR      0x07
#define USB_REQ_GET_CONFIGURATION   0x08
#define USB_REQ_SET_CONFIGURATION   0x09
#define USB_REQ_GET_INTERFACE       0x0A
#define USB_REQ_SET_INTERFACE       0x0B
#define USB_REQ_SYNCH_FRAME         0x0C
#define USB_REQ_SET_ENCRYPTION      0x0D
#define USB_REQ_GET_ENCRYPTION      0x0E
#define USB_REQ_RPIPE_ABORT         0x0E
#define USB_REQ_SET_HANDSHAKE       0x0F
#define USB_REQ_RPIPE_RESET         0x0F
#define USB_REQ_GET_HANDSHAKE       0x10
#define USB_REQ_SET_CONNECTION      0x11
#define USB_REQ_SET_SECURITY_DATA   0x12
#define USB_REQ_GET_SECURITY_DATA   0x13
#define USB_REQ_SET_WUSB_DATA       0x14
#define USB_REQ_LOOPBACK_DATA_WRITE 0x15
#define USB_REQ_LOOPBACK_DATA_READ  0x16
#define USB_REQ_SET_INTERFACE_DS    0x17

#define USB_REQ_CLASS_RECIPIENT_DEVICE    (0x20)
#define USB_REQ_CLASS_RECIPIENT_INTERFACE (0x21)
#define USB_REQ_CLASS_RECIPIENT_ENDPOINT  (0x22)
#define USB_REQ_CLASS_RECIPIENT_OTHER     (0x23)

#define USB_REQ_VENDOR_RECIPIENT_DEVICE    (0x40)
#define USB_REQ_VENDOR_RECIPIENT_INTERFACE (0x41)
#define USB_REQ_VENDOR_RECIPIENT_ENDPOINT  (0x42)
#define USB_REQ_VENDOR_RECIPIENT_OTHER     (0x43)

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_HALT  0
#define USB_FEATURE_SELF_POWERED   0
#define USB_FEATURE_REMOTE_WAKEUP  1
#define USB_FEATURE_TEST_MODE      2
#define USB_FEATURE_BATTERY        2
#define USB_FEATURE_BHNPENABLE     3
#define USB_FEATURE_WUSBDEVICE     3
#define USB_FEATURE_AHNPSUPPORT    4
#define USB_FEATURE_AALTHNPSUPPORT 5
#define USB_FEATURE_DEBUGMODE      6

/* USB GET_STATUS Bit Values */
#define USB_GET_STS_ENDPOINT_HALT 0x01
#define USB_GET_STS_SELF_POWERED  0x01
#define USB_GET_STS_REMOTE_WAKEUP 0x02

/* USB Descriptor Types */
#define USB_DESC_TYPE_DEVICE                    (0x01U)
#define USB_DESC_TYPE_CONFIGURATION             (0x02U)
#define USB_DESC_TYPE_STRING                    (0x03U)
#define USB_DESC_TYPE_INTERFACE                 (0x04U)
#define USB_DESC_TYPE_ENDPOINT                  (0x05U)
#define USB_DESC_TYPE_DEVICE_QUALIFIER          (0x06U)
#define USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION (0x07U)
#define USB_DESC_TYPE_INTERFACE_POWER           (0x08U)
#define USB_DESC_TYPE_OTG                       (0x09U)
#define USB_DESC_TYPE_DEBUG                     (0x0AU)
#define USB_DESC_TYPE_INTERFACE_ASSOCIATION     (0x0BU)
#define USB_DESC_TYPE_BINARY_OBJECT_STORE       (0x0FU)
#define USB_DESC_TYPE_DEVICE_CAPABILITY         (0x10U)
#define USB_DESC_TYPE_WIRELESS_ENDPOINTCOMP     (0x11U)

#define USB_DESC_TYPE_HID        (0x21)
#define USB_DESC_TYPE_HID_REPORT (0x22)

/* Descriptor Type and Descriptor Index  */
/* Use the following values when calling the function usbh_get_descriptor  */
#define USB_DESC_DEVICE                    ((USB_DESC_TYPE_DEVICE << 8) & 0xFF00)
#define USB_DESC_CONFIGURATION             ((USB_DESC_TYPE_CONFIGURATION << 8) & 0xFF00)
#define USB_DESC_STRING                    ((USB_DESC_TYPE_STRING << 8) & 0xFF00)
#define USB_DESC_INTERFACE                 ((USB_DESC_TYPE_INTERFACE << 8) & 0xFF00)
#define USB_DESC_ENDPOINT                  ((USB_DESC_TYPE_INTERFACE << 8) & 0xFF00)
#define USB_DESC_DEVICE_QUALIFIER          ((USB_DESC_TYPE_DEVICE_QUALIFIER << 8) & 0xFF00)
#define USB_DESC_OTHER_SPEED_CONFIGURATION ((USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION << 8) & 0xFF00)
#define USB_DESC_INTERFACE_POWER           ((USB_DESC_TYPE_INTERFACE_POWER << 8) & 0xFF00)
#define USB_DESC_HID_REPORT                ((USB_DESC_TYPE_HID_REPORT << 8) & 0xFF00)
#define USB_DESC_HID                       ((USB_DESC_TYPE_HID << 8) & 0xFF00)

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED      0x00
#define USB_DEVICE_CLASS_AUDIO         0x01
#define USB_DEVICE_CLASS_CDC           0x02
#define USB_DEVICE_CLASS_HID           0x03
#define USB_DEVICE_CLASS_MONITOR       0x04
#define USB_DEVICE_CLASS_PHYSICAL      0x05
#define USB_DEVICE_CLASS_IMAGE         0x06
#define USB_DEVICE_CLASS_PRINTER       0x07
#define USB_DEVICE_CLASS_MASS_STORAGE  0x08
#define USB_DEVICE_CLASS_HUB           0x09
#define USB_DEVICE_CLASS_CDC_DATA      0x0a
#define USB_DEVICE_CLASS_SMART_CARD    0x0b
#define USB_DEVICE_CLASS_SECURITY      0x0d
#define USB_DEVICE_CLASS_VIDEO         0x0e
#define USB_DEVICE_CLASS_HEALTHCARE    0x0f
#define USB_DEVICE_CLASS_DIAG_DEVICE   0xdc
#define USB_DEVICE_CLASS_WIRELESS      0xe0
#define USB_DEVICE_CLASS_MISC          0xef
#define USB_DEVICE_CLASS_APP_SPECIFIC  0xfe
#define USB_DEVICE_CLASS_VEND_SPECIFIC 0xff

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_REMOTE_WAKEUP 0x20
#define USB_CONFIG_POWERED_MASK  0x40
#define USB_CONFIG_BUS_POWERED   0x80
#define USB_CONFIG_SELF_POWERED  0xC0

/**
 * USB endpoint direction and number.
 */
#define USB_EP_DIR_MASK 0x80U
#define USB_EP_DIR_IN   0x80U
#define USB_EP_DIR_OUT  0x00U

/** Get endpoint index (number) from endpoint address */
#define USB_EP_GET_IDX(ep) ((ep) & ~USB_EP_DIR_MASK)
/** Get direction from endpoint address */
#define USB_EP_GET_DIR(ep) ((ep) & USB_EP_DIR_MASK)
/** Get endpoint address from endpoint index and direction */
#define USB_EP_GET_ADDR(idx, dir) ((idx) | ((dir) & USB_EP_DIR_MASK))
/** True if the endpoint is an IN endpoint */
#define USB_EP_DIR_IS_IN(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_IN)
/** True if the endpoint is an OUT endpoint */
#define USB_EP_DIR_IS_OUT(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_OUT)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_SHIFT       0
#define USB_ENDPOINT_TYPE_CONTROL     (0)
#define USB_ENDPOINT_TYPE_ISOCHRONOUS (1)
#define USB_ENDPOINT_TYPE_BULK        (2)
#define USB_ENDPOINT_TYPE_INTERRUPT   (3)
#define USB_ENDPOINT_TYPE_MASK        (3)
#define USB_GET_ENDPOINT_TYPE(x)      ((x & USB_ENDPOINT_TYPE_MASK) >> USB_ENDPOINT_TYPE_SHIFT)

/* wMaxPacketSize in Endpoint Descriptor */
#define USB_MAXPACKETSIZE_SHIFT                        0
#define USB_MAXPACKETSIZE_MASK                         (0x7ff << USB_MAXPACKETSIZE_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT 11
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_NONE  (0 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_ONE   (1 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_TWO   (2 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK  (3 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_GET_MAXPACKETSIZE(x)                       ((x & USB_MAXPACKETSIZE_MASK) >> USB_MAXPACKETSIZE_SHIFT)
#define USB_GET_MULT(x)                                ((x & USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK) >> USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)

/* Table 9-5. Descriptor Types of USB Specifications */
#define USB_SETUP_PACKET_SIZE          8
#define USB_DEVICE_DESC_SIZE           18
#define USB_CONFIGURATION_DESC_SIZE    9
#define USB_INTERFACE_DESC_SIZE        9
#define USB_ENDPOINT_DESC_SIZE         7
#define USB_STRING_LANGID_DESC_SIZE    4
#define USB_IAD_DESC_SIZE              8
#define USB_DEVICE_QUALIFIER_DESC_SIZE 10
#define USB_HID_DESC_SIZE              (9)

/* Interface Descriptor field values for HID Boot Protocol */
#define HID_BOOT_CODE        0x01
#define HID_KEYBRD_BOOT_CODE 0x01
#define HID_MOUSE_BOOT_CODE  0x02

/* As per USB specs 9.2.6.4 :Standard request with data request timeout: 5sec
   Standard request with no data stage timeout : 50ms */
#define DATA_STAGE_TIMEOUT   5000
#define NODATA_STAGE_TIMEOUT 50

/**************************** type definition ********************************/
typedef enum {
    USB_ERROR = -1,
    USB_OK = 0,
    USB_BUSY,
    USB_FAIL,
    USB_UNINIT,
    USB_NOT_SUPPORTED,
    USB_UNRECOVERED_ERROR,
    USB_ERROR_SPEED_UNKNOWN,
    USB_APPLY_DEINIT,
    USB_PHASE_ERROR,
    USB_FIFO_EMPTY
} usb_status_t;

typedef union {
    uint16_t w;
    struct BW {
        uint8_t msb;
        uint8_t lsb;
    } bw;
} uint16_t_uint8_t;

typedef union {
    uint8_t d8[8];

    struct _SetupPkt_Struc {
        uint8_t bmRequestType;
        uint8_t bRequest;
        uint16_t_uint8_t wValue;
        uint16_t_uint8_t wIndex;
        uint16_t_uint8_t wLength;
    } b;
} usb_setup_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
} usb_descheader_t;

/* Setup packet definition used to read raw data from USB line */
typedef struct {
    /** Request type. Bits 0:4 determine recipient, see
     * \ref usb_request_recipient. Bits 5:6 determine type, see
     * \ref usb_request_type. Bit 7 determines data transfer direction, see
     * \ref usb_endpoint_direction.
     */
    uint8_t bmRequestType;

    /** Request. If the type bits of bmRequestType are equal to
     * \ref usb_request_type::LIBUSB_REQ_TYPE_STANDARD
     * "USB_REQ_TYPE_STANDARD" then this field refers to
     * \ref usb_standard_request. For other cases, use of this field is
     * application-specific. */
    uint8_t bRequest;

    /** Value. Varies according to request */
    uint16_t wValue;

    /** Index. Varies according to request, typically used to pass an index
     * or offset */
    uint16_t wIndex;

    /** Number of bytes to transfer */
    uint16_t wLength;
} usb_setup_req_t;

/** Standard Device Descriptor */
typedef struct {
    uint8_t bLength;            /* Descriptor size in bytes = 18 */
    uint8_t bDescriptorType;    /* DEVICE descriptor type = 1 */
    uint16_t bcdUSB;            /* USB spec in BCD, e.g. 0x0200 */
    uint8_t bDeviceClass;       /* Class code, if 0 see interface */
    uint8_t bDeviceSubClass;    /* Sub-Class code, 0 if class = 0 */
    uint8_t bDeviceProtocol;    /* Protocol, if 0 see interface */
    uint8_t bMaxPacketSize;     /* Endpoint 0 max. size */
    uint16_t idVendor;          /* Vendor ID per USB-IF */
    uint16_t idProduct;         /* Product ID per manufacturer */
    uint16_t bcdDevice;         /* Device release # in BCD */
    uint8_t iManufacturer;      /* Index to manufacturer string */
    uint8_t iProduct;           /* Index to product string */
    uint8_t iSerialNumber;      /* Index to serial number string */
    uint8_t bNumConfigurations; /* Number of possible configurations */
} usb_devdesc_t;

/** Standard Configuration Descriptor */
typedef struct {
    uint8_t bLength;             /* Descriptor size in bytes = 9 */
    uint8_t bDescriptorType;     /* CONFIGURATION type = 2 or 7 */
    uint16_t wTotalLength;       /* Length of concatenated descriptors */
    uint8_t bNumInterfaces;      /* Number of interfaces, this config. */
    uint8_t bConfigurationValue; /* Value to set this config. */
    uint8_t iConfiguration;      /* Index to configuration string */
    uint8_t bmAttributes;        /* Config. characteristics */
    uint8_t bMaxPower;           /* Max.power from bus, 2mA units */
} usb_cfgdesc_t;

/** Standard Interface Descriptor */
typedef struct {
    uint8_t bLength;            /* Descriptor size in bytes = 9 */
    uint8_t bDescriptorType;    /* INTERFACE descriptor type = 4 */
    uint8_t bInterfaceNumber;   /* Interface no.*/
    uint8_t bAlternateSetting;  /* Value to select this IF */
    uint8_t bNumEndpoints;      /* Number of endpoints excluding 0 */
    uint8_t bInterfaceClass;    /* Class code, 0xFF = vendor */
    uint8_t bInterfaceSubClass; /* Sub-Class code, 0 if class = 0 */
    uint8_t bInterfaceProtocol; /* Protocol, 0xFF = vendor */
    uint8_t iInterface;         /* Index to interface string */
} usb_infdesc_t;

/** Standard Endpoint Descriptor */
typedef struct {
    uint8_t bLength;          /* Descriptor size in bytes = 7 */
    uint8_t bDescriptorType;  /* ENDPOINT descriptor type = 5 */
    uint8_t bEndpointAddress; /* Endpoint # 0 - 15 | IN/OUT */
    uint8_t bmAttributes;     /* Transfer type */
    uint16_t wMaxPacketSize;  /* Bits 10:0 = max. packet size */
    uint8_t bInterval;        /* Polling interval in (micro) frames */
} usb_epdesc_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdHID;               /* indicates what endpoint this descriptor is describing */
    uint8_t bCountryCode;          /* specifies the transfer type. */
    uint8_t bNumDescriptors;       /* specifies the transfer type. */
    uint8_t bReportDescriptorType; /* Maximum Packet Size this endpoint is capable of sending or receiving */
    uint16_t wItemLength;          /* is used to specify the polling interval of certain transfers. */
} usb_hid_desc_t;

#define USB_LANGID_INIT(id)                         \
    0x04,                     /* bLength */         \
        USB_DESC_TYPE_STRING, /* bDescriptorType */ \
        USB_WBVAL(id)         /* wLangID0 */

/**************************** variable declear *******************************/

/**************************** function declear *******************************/

#endif

#ifdef __cplusplus
}
#endif

#endif //__USB_DEFINES__H__

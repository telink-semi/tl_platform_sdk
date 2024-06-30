/********************************************************************************************************
 * @file    myudb_usbdesc.c
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
#if(1)

//#include "../../drivers.h"
#include "myudb.h"
#include "myudb_usbdesc.h"

// request parameters
/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
static const USB_Descriptor_String_t language_desc = { {
        sizeof(USB_Descriptor_Header_t) + 2, DTYPE_String },
        { LANGUAGE_ID_ENG } };

static const USB_Descriptor_Device_t device_desc = { {
        sizeof(USB_Descriptor_Device_t), DTYPE_Device }, // Header
        0x0200, // USBSpecification, USB 2.0
        USB_CSCP_NoDeviceClass, // Class
        USB_CSCP_NoDeviceSubclass, // SubClass
        USB_CSCP_NoDeviceProtocol, // Protocol
        8, // Endpoint0Size, Maximum Packet Size for Zero Endpoint. Valid Sizes are 8, 16, 32, 64
        MYUDB_ID_VENDOR, // VendorID
        MYUDB_ID_PRODUCT, // ProductID
        MYUDB_ID_VERSION/*0x0100*/, // .ReleaseNumber
        MYUDB_USB_STRING_VENDOR,    // .ManufacturerStrIndex
        MYUDB_USB_STRING_PRODUCT, // .ProductStrIndex
        0,  // .SerialNumStrIndex, iSerialNumber
        1 };

static const MYUDB_USB_Descriptor_Configuration_t
        configuration_desc = {
                {
                    {sizeof(USB_Descriptor_Configuration_Header_t),
                    DTYPE_Configuration }, // Length, type
                    sizeof(MYUDB_USB_Descriptor_Configuration_t), // TotalLength: variable
                    2, // NumInterfaces
                    1, // Configuration index
                    NO_DESCRIPTOR, // Configuration String
                    USB_CONFIG_ATTR_RESERVED, // Attributes
                    USB_CONFIG_POWER_MA(100) // MaxPower = 100mA
                },
                // printer_interface
                { { sizeof(USB_Descriptor_Interface_t), DTYPE_Interface },
                        0, 0, // AlternateSetting
                        2, // bNumEndpoints
                        PRNT_CSCP_PrinterClass, // bInterfaceclass ->Printer
                        PRNT_CSCP_PrinterSubclass, // bInterfaceSubClass -> Control
                        PRNT_CSCP_BidirectionalProtocol,// bInterfaceProtocol
                        NO_DESCRIPTOR // iInterface,  same as iProduct in USB_Descriptor_Device_t, or else not working
                },
                // printer_in_endpoint
                { { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint }, // length, bDescriptorType
                        ENDPOINT_DIR_IN | MYUDB_EDP_IN_HCI, // endpoint id
                        EP_TYPE_BULK, // endpoint type
                        0x0040, // wMaxPacketSize
                        0 // bInterval
                },
                // printer_out_endpoint
                { { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint }, // length, bDescriptorType
                        MYUDB_EDP_OUT_HCI, // endpoint id
                        EP_TYPE_BULK, // endpoint type
                        0x0040, // wMaxPacketSize
                        0 // polling bInterval. valid for iso or interrupt type
                },

                // printer_interface
                { { sizeof(USB_Descriptor_Interface_t), DTYPE_Interface },
                        1, 0, // AlternateSetting
                        2, // bNumEndpoints
                        PRNT_CSCP_PrinterClass, // bInterfaceclass ->Printer
                        PRNT_CSCP_PrinterSubclass, // bInterfaceSubClass -> Control
                        PRNT_CSCP_BidirectionalProtocol,// bInterfaceProtocol
                        NO_DESCRIPTOR // iInterface,  same as iProduct in USB_Descriptor_Device_t, or else not working
                },
                // printer_in_endpoint
                { { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint }, // length, bDescriptorType
                        ENDPOINT_DIR_IN | MYUDB_EDP_IN_VCD, // endpoint id
                        EP_TYPE_BULK, // endpoint type
                        0x0040, // wMaxPacketSize
                        0 // bInterval
                },
                // printer_out_endpoint
                { { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint }, // length, bDescriptorType
                        MYUDB_EDP_OUT_VCD, // endpoint id
                        EP_TYPE_BULK, // endpoint type
                        0x0040, // wMaxPacketSize
                        0 // polling bInterval. valid for iso or interrupt type
                },
        };

unsigned char* myudb_usbdesc_get_language(void) {
    return (unsigned char*)(unsigned int)(&language_desc);
}


static unsigned short myudb_desc_str[32 + 1];

/**
 * @brief     This function servers to get usb string descriptor.
 * @param[in] src - usb string.
 * @return    usb string descriptor pointer.
 */
static unsigned short *myudb_usbdesc_get_str(const char *src)
{
    unsigned int char_count;

    char_count = strlen(src);
    unsigned int max_count = sizeof(myudb_desc_str) / sizeof(myudb_desc_str[0]) - 1; // -1 for string type
    if (char_count > max_count)
    {
        char_count = max_count;
    }

    /* convert ASCII string into UTF-16. */
    for (unsigned int i = 0; i < char_count; i++)
    {
        myudb_desc_str[1 + i] = src[i];
    }

    /* first byte is length (including header), second byte is string type. */
    myudb_desc_str[0] = (unsigned short)((DTYPE_String << 8) | (sizeof(USB_Descriptor_Header_t) + char_count * 2));

    return myudb_desc_str;
}

unsigned char* myudb_usbdesc_get_vendor(void) {
    return (unsigned char *)myudb_usbdesc_get_str(MYUDB_STRING_VENDOR);
}

unsigned char* myudb_usbdesc_get_product(void) {
    return (unsigned char *)myudb_usbdesc_get_str(MYUDB_STRING_PRODUCT);
}

unsigned char* myudb_usbdesc_get_serial(void) {
    return (unsigned char *)myudb_usbdesc_get_str(MYUDB_STRING_SERIAL);
}

unsigned char* myudb_usbdesc_get_device(void) {
    return (unsigned char*)(unsigned int)(&device_desc);
}

unsigned char* myudb_usbdesc_get_configuration(void) {
    return (unsigned char*)(unsigned int)(&configuration_desc);
}

#endif



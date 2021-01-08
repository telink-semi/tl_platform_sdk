/********************************************************************************************************
 * @file	StdDescriptors.h
 *
 * @brief	This is the header file for B91
 *
 * @author	Driver Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	extern "C" {
#endif

#define NO_DESCRIPTOR                     (0)
#define USB_CONFIG_POWER_MA(mA)           ((mA) >> 1)
#define USB_STRING_LEN(UnicodeChars)      (sizeof(USB_Descriptor_Hdr_t) + ((UnicodeChars) << 1))
#define LANGUAGE_ID_ENG                   (0x0409)
#define USB_CONFIG_ATTR_REMOTEWAKEUP      (0x20)
#define USB_CONFIG_ATTR_SELFPOWERED       (0x40)
#define USB_CONFIG_ATTR_RESERVED          (0x80)
#define ENDPOINT_ATTR_NO_SYNC             (0<<2)
#define ENDPOINT_ATTR_ASYNC               (1<<2)
#define ENDPOINT_ATTR_ADAPTIVE            (2<<2)
#define ENDPOINT_ATTR_SYNC                (3<<2)
#define ENDPOINT_USAGE_DATA               (0<<4)
#define ENDPOINT_USAGE_FEEDBACK           (1<<4)
#define ENDPOINT_USAGE_IMPLICIT_FEEDBACK  (2<<4)

enum USB_DescriptorTypes_t
{
	DTYPE_Device = 0x01,
	DTYPE_Configuration,
	DTYPE_String,
	DTYPE_Interface,
	DTYPE_Endpoint,
	DTYPE_DeviceQualifier,
	DTYPE_Other,
	DTYPE_InterfacePower,
	DTYPE_InterfaceAssociation = 0x0B,
	DTYPE_CSInterface = 0x24,
	DTYPE_CSEndpoint = 0x25,
};

enum USB_Descriptor_ClassSubclassProtocol_t
{
	USB_CSCP_NoDeviceClass = 0x00,
	USB_CSCP_NoDeviceSubclass = 0x00,
	USB_CSCP_NoDeviceProtocol = 0x00,
	USB_CSCP_IADDeviceProtocol = 0x01,
	USB_CSCP_IADDeviceSubclass = 0x02,
	USB_CSCP_IADDeviceClass = 0xEF,
	USB_CSCP_VendorSpecificClass = 0xFF,
	USB_CSCP_VendorSpecificSubclass = 0xFF,
	USB_CSCP_VendorSpecificProtocol = 0xFF,
};



typedef  struct USB_Descriptor_Hdr_t
{
    unsigned char Size;
    unsigned char Type;
}USB_Descriptor_Hdr_t;


typedef struct
{
    unsigned char Length;
    unsigned char DescriptorType;
}USB_StdDescriptor_Hdr_t;

typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned short USBSpecification;
	unsigned char Class;
	unsigned char SubClass;
	unsigned char Protocol;
	unsigned char Endpoint0Size;
	unsigned short VendorID;
	unsigned short ProductID;
	unsigned short ReleaseNumber;
	unsigned char ManufacturerStrIndex;
	unsigned char ProductStrIndex;
	unsigned char SerialNumStrIndex;
	unsigned char NumberOfConfigurations;
}__attribute__((packed)) USB_Descriptor_Device_t;

typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned short BcdUSB;
	unsigned char DeviceClass;
	unsigned char DeviceSubClass;
	unsigned char DeviceProtocol;
	unsigned char MaxPacketSize0;
	unsigned short IdVendor;
	unsigned short IdProduct;
	unsigned short BcdDevice;
	unsigned char Manufacturer;
	unsigned char Product;
	unsigned char SerialNumber;
	unsigned char NumConfigurations;
}__attribute__((packed)) USB_StdDescriptor_Device_t;

typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned short USBSpecification;
	unsigned char Class;
	unsigned char SubClass;
	unsigned char Protocol;
	unsigned char Endpoint0Size;
	unsigned char NumberOfConfigurations;
	unsigned char Reserved;
}__attribute__((packed)) USB_Descriptor_DeviceQualifier_t;

typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned short BcdUSB;
	unsigned char DeviceClass;
	unsigned char DeviceSubClass;
	unsigned char DeviceProtocol;
	unsigned char MaxPacketSize0;
	unsigned char NumConfigurations;
	unsigned char Reserved;
}__attribute__((packed)) USB_StdDescriptor_DeviceQualifier_t;

typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned short TotalConfigurationSize;
	unsigned char TotalInterfaces;
	unsigned char ConfigurationNumber;
	unsigned char ConfigurationStrIndex;
	unsigned char ConfigAttributes;
	unsigned char MaxPowerConsumption;
}__attribute__((packed)) USB_Descriptor_Configuration_Hdr_t;

typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned short TotalLength;
	unsigned char NumInterfaces;
	unsigned char ConfigurationValue;
	unsigned char Configuration;
	unsigned char MAttributes;
	unsigned char MaxPower;
}__attribute__((packed)) USB_StdDescriptor_Configuration_Hdr_t;

typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned char InterfaceNumber;
	unsigned char AlternateSetting;
	unsigned char TotalEndpoints;
	unsigned char Class;
	unsigned char SubClass;
	unsigned char Protocol;
	unsigned char InterfaceStrIndex;
}__attribute__((packed)) USB_Descriptor_Interface_t;

typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned char InterfaceNum;
	unsigned char AlternateSetting;
	unsigned char NumberEndpoints;
	unsigned char InterfaceClass;
	unsigned char InterfaceSubclass;
	unsigned char InterfaceProtocol;
	unsigned char Interface;
}__attribute__((packed)) USB_StdDescriptor_Interface_t;


typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned char FirstInterfaceIndex;
	unsigned char TotalInterfaces;
	unsigned char Class;
	unsigned char SubClass;
	unsigned char Protocol;
	unsigned char IADStrIndex;
}__attribute__((packed)) USB_Descriptor_Interface_Association_t;


typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned char FirstInterface;
	unsigned char InterfaceCount;
	unsigned char FunctionClass;
	unsigned char FunctionSubClass;
	unsigned char FunctionProtocol;
	unsigned char Function;
}__attribute__((packed)) USB_StdDescriptor_Interface_Association_t;


typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned char EndpointAddress;
	unsigned char Attributes;
	unsigned short EndpointSize;
	unsigned char PollingIntervalMS;
}__attribute__((packed)) USB_Descriptor_Endpoint_t;

typedef struct
{
	unsigned char  Length;
	unsigned char  DescriptorType;
	unsigned char  EndpointAddress;
	unsigned char  MAttributes;
	unsigned short MaxPacketSize;
	unsigned char  Interval;
}__attribute__((packed)) USB_StdDescriptor_Endpoint_t;


#ifndef __GNUC__
#pragma warning(push)
#pragma warning(disable:4200)	// none standard zero length array
#endif

typedef struct
{
	USB_Descriptor_Hdr_t Header;
	unsigned short UnicodeString[100];//If don't set the length here, will get an error. set the length based on the actual situation
}USB_Descriptor_String_t;

typedef struct
{
	unsigned char Length;
	unsigned char DescriptorType;
	unsigned short bString[];
}USB_StdDescriptor_String_t;

#ifndef __GNUC__
#pragma warning(pop)
#endif


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	}
#endif


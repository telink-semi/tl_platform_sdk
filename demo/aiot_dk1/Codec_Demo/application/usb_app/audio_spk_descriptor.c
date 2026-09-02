/********************************************************************************************************
 * @file    audio_spk_descriptor.c
 *
 * @brief   This is the source file for Telink RISC-V MCU
 *
 * @author  Driver Group
 * @date    2025
 *
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "common.h"
#if defined(MCU_CORE_TL322X)
#if (USB_DEMO_TYPE == USB_MIC_SPEAKER)
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tl_usb/core/usbd_core.h"
#include "audio_spk_descriptor.h"
#include "../usb_default.h"

unsigned char device_desc[] = {
    0x12,
    USB_DESC_DEVICE,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    U16_LOW_BYTE(ID_VENDOR),
    U16_HIGH_BYTE(ID_VENDOR),
    U16_LOW_BYTE(ID_PRODUCT),
    U16_HIGH_BYTE(ID_PRODUCT),
    U16_LOW_BYTE(ID_VERSION),
    U16_HIGH_BYTE(ID_VERSION),
    0x01,
    0x02,
    0x03,
    0x01,
};

unsigned char *usbd_get_device_descriptor(unsigned char bus)
{
    (void)bus;
    return (unsigned char *)&device_desc;
}

#if 0
unsigned char config_desc[] = {
// ==========================
// 1. Configuration Descriptor
// ==========================
    0x09,
    USB_DESC_CONFIGURATION,
    0x6D,
    0x00,
    0x02,
    0x01,
    0x00,
    0xA0,
    0x19,
// ==========================
// 2. Audio Control Interface (Interface 0)
// ==========================  
    0x09,
    USB_DESC_INTERFACE,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,

    0x09,
    0x24,
    0x01,
    0x00,
    0x01,
    0x27,
    0x00,
    0x01,
    0x01,

    0x0C,
    0x24,
    0x02,
    0x04,
    0x01,0x02,
    0x00,
    0x01,
    0x01,0x00, 
    0x00,
    0x00,

    0x09,
    0x24,
    0x06,
    0x05,
    0x04,
    0x01,
    0x03,
    0x00,
    0x00,

    0x09,
    0x24,
    0x03,
    0x06,
    0x01,
    0x01,
    0x00,
    0x05,
    0x00,

    0x09,
    0x04,
    0x01,
    0x00,
    0x00,
    0x01,
    0x02,
    0x00,
    0x00,

    0x09,
    0x04,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x00,
    0x00,

    0x07,
    0x24,
    0x01,
    0x06,
    0x01,
    0x01,
    0x00,

    0x0B,
    0x24,
    0x02,
    0x01,
    0x02,
    0x02,
    0x10,
    0x01,
    0x80,
    0x3E,
    0x00,
    0x09,
    USB_DESC_ENDPOINT,
    AUDIO_MIC_IN_ENDPOINT_ADDRESS,
    0x0D,
    U16_LOW_BYTE(AUDIO_MIC_IN_ENDPOIRT_SIZE),
    U16_HIGH_BYTE(AUDIO_MIC_IN_ENDPOIRT_SIZE),
#if USB_HIGH_SPEED_EN
    0x04,
#else
    0x01,
#endif
    0x00,
    0x00,
    0x07,
    0x25,
    0x01,
    0x01,
    0x00,
    0x00,
    0x00,
};
#endif

#if 1
unsigned char config_desc[] = {
    // ==========================
    // 1. Configuration Descriptor
    // ==========================
    0x09,                   // bLength: 9
    USB_DESC_CONFIGURATION, // bDescriptorType: Configuration
    0xC1, 0x00,             // wTotalLength:  (Total length of configuration descriptor)
    0x03,                   // bNumInterfaces: 3
    0x01,                   // bConfigurationValue: 1
    0x00,                   // iConfiguration: 0
    0x80,                   // bmAttributes: Self Powered
    0x19,                   // MaxPower: 50mA (0x19 * 2mA)

    // ==========================
    // 2. (Interface: 0) Audio Control Interface
    // ==========================
    /* Standard AC Interface Descriptor */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x00,                   // bInterfaceNumber: 0
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x01,                   // bInterfaceSubClass: Control
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Class-Specific AC Interface Header Descriptor */
    0x0A,                   // bLength: 10
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: Header
    0x00, 0x01,             // bcdADC: UAC 1.0           
    0x50, 0x00,             // wTotalLength: 71 bytes (Total length of AC interface)
    0x02,                   // bInCollection: 2 stream interface (Mic + Spk)
    0x01,                   // baInterfaceNr: 1 (Mic)
    0x02,                   // baInterfaceNr: 2 (Spk)

    /* (ID: 1) Microphone Input Terminal */
    0x0C,                   // bLength: 12
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Input Terminal
    0x01,                   // bTerminalID: 1
    0x01, 0x02,             // wTerminalType: 0x0201 (Microphone)
    0x00,                   // bAssocTerminal: 0
    0x01,                   // bNrChannels: 1 
    0x00, 0x00,             // wChannelConfig: 0
    0x00,                   // iChannelName: 0
    0x00,                   // iTerminal: 0

    /* (ID: 2) Microphone Feature Unit */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x06,                   // bDescriptorSubType: Feature Unit
    0x02,                   // bUnitID: 2
    0x01,                   // bSourceID: 1 (Mic Input)
    0x01,                   // bControlSize: 1
    0x03,                   // bmaControls(0): Mute + Volume
    0x00,                   // bmaControls(1): Channel 1
    0x00,                   // iFeature: 0

    /* (ID: 3) Microphone Output Terminal */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x03,                   // bDescriptorSubType: Output Terminal
    0x03,                   // bTerminalID: 3
    0x01, 0x01,             // wTerminalType: 0x0101 (USB Streaming)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bSourceID: 2 (Feature Unit)
    0x00,                   // iTerminal: 0

    /* (ID: 4) Speaker Input Terminal */
    0x0C,                   // bLength: 12
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Input Terminal
    0x04,                   // bTerminalID: 4
    0x01, 0x01,             // wTerminalType: 0x0101 (USB Streaming)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bNrChannels: 2 
    0x03, 0x00,             // wChannelConfig
    0x00,                   // iChannelName: 0
    0x00,                   // iTerminalName: 0

    /* (ID: 5) Feature Unit Descriptor (Speaker Volume/Mute) */
    0x0A,                   // bLength: 10 
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x06,                   // bDescriptorSubType: Feature Unit
    0x05,                   // bUnitID: 5
    0x04,                   // bSourceID: 4 (Input Terminal)
    0x01,                   // bControlSize: 1 byte
    0x03,                   // bmaControls(0): Master (Mute + Volume)
    0x00,                   // bmaControls(1): Channel 1
    0x00,                   // bmaControls(2): Channel 2
    0x00,                   // iFeature: 0

    /* (ID: 6) Output Terminal Descriptor (Speaker) */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x03,                   // bDescriptorSubType: Output Terminal
    0x06,                   // bTerminalID: 6
    0x01, 0x03,             // wTerminalType: 0x0301 (Speaker)
    0x00,                   // bAssocTerminal: 0
    0x05,                   // bSourceID: 5 (Feature Unit)
    0x00,                   // iTerminal: 0

    // ==========================
    // 3. (Interface: 1) Audio Streaming  (Microphone In)
    // ==========================
    // Alt Setting 0: Zero Bandwidth
    0x09,                       // bLength
    USB_DESC_INTERFACE,         // bDescriptorType
    0x01,                       // bInterfaceNumber: 1
    0x00,                       // bAlternateSetting: 0
    0x00,                       // bNumEndpoints: 0
    0x01,                       // bInterfaceClass: Audio
    0x02,                       // bInterfaceSubClass: Streaming
    0x00,                       // bInterfaceProtocol
    0x00,                       // iInterface

    // Alt Setting 1: Operational
    0x09,                   // bLength: Size of this descriptor (9 bytes)
    USB_DESC_INTERFACE,     // bDescriptorType: INTERFACE
    0x01,                   // bInterfaceNumber: Index of this interface (1)
    0x01,                   // bAlternateSetting: Alternate setting 1 (Active streaming)
    0x01,                   // bNumEndpoints: One endpoint used for audio data
    0x01,                   // bInterfaceClass: AUDIO
    0x02,                   // bInterfaceSubClass: AUDIO_STREAMING
    0x00,                   // bInterfaceProtocol: PR_PROTOCOL_UNDEFINED
    0x00,                   // iInterface: String descriptor index (None)

    // Class-specific AS Interface Descriptor
    0x07,                   // bLength: Size of this descriptor (7 bytes)
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS_INTERFACE
    0x01,                   // bDescriptorSubtype: AS_GENERAL
    0x03,                   // bTerminalLink: ID of the output Terminal
    0x01,                   // bDelay: 1ms
    0x01,                   // wFormatTag: PCM format (Low byte)
    0x00,                   // wFormatTag: PCM format (High byte)

    //Type I Format Type Descriptor
    0x0B,                   // bLength: Size of this descriptor (11 bytes)
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS_INTERFACE
    0x02,                   // bDescriptorSubtype: FORMAT_TYPE
    0x01,                   // bFormatType: FORMAT_TYPE_I
    0x01,                   // bNrChannels: Number of channels (1 - mono)
    0x02,                   // bSubframeSize: Bytes per subframe (2 bytes = 16-bit)
    0x10,                   // bBitResolution: Bits per sample (16 bits)
    0x01,                   // bSamFreqType: Number of supported sampling frequencies (1 discrete freq)
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,                   // tSamFreq[2]: 

    // --- Standard AS Isochronous Audio Data Endpoint Descriptor ---
    0x09,                   // bLength: Size of this descriptor (9 bytes)
    USB_DESC_ENDPOINT,      // bDescriptorType: ENDPOINT
    AUDIO_MIC_IN_ENDPOINT_ADDRESS, // bEndpointAddress: IN Endpoint (e.g., 0x81)
    0x0D,                   // bmAttributes: Isochronous transfer, Asynchronous synchronization
    U16_LOW_BYTE(AUDIO_MIC_IN_ENDPOINT_SIZE),  // wMaxPacketSize: Max packet size (Low byte)
    U16_HIGH_BYTE(AUDIO_MIC_IN_ENDPOINT_SIZE), // wMaxPacketSize: Max packet size (High byte)
#if USB_HIGH_SPEED_EN
    0x04,                   // bInterval: Polling interval for High-Speed (4ms / 125us * 2^(4-1))
#else
    0x01,                   // bInterval: Polling interval for Full-Speed (1ms)
#endif
    0x00,                   // bRefresh: Reset endpoint (unused)
    0x00,                   // bSynchAddress: Address of sync endpoint (0x00 for Asynchronous)

    // --- Class-specific AS Isochronous Audio Data Endpoint Descriptor ---
    0x07,                   // bLength: Size of this descriptor (7 bytes)
    0x25,                   // bDescriptorType: CS_ENDPOINT
    0x01,                   // bDescriptorSubtype: EP_GENERAL
    0x01,                   // bmAttributes: Sampling frequency control supported
    0x00,                   // bLockDelayUnits: Undefined
    0x00,                   // wLockDelay: No lock delay (Low byte)
    0x00,                   // wLockDelay: No lock delay (High byte)

    // ==========================
    // 4. (Interface: 2) Audio Streaming (Speaker Out)
    // ==========================
    /* Alt Setting 0: Zero Bandwidth */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x02,                   // bInterfaceNumber: 2
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Alt Setting 1: Operational */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x02,                   // bInterfaceNumber: 2
    0x01,                   // bAlternateSetting: 1
    0x01,                   // bNumEndpoints: 1 (OUT)
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* AS General Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: AS General
    0x04,                   // bTerminalLink: 4 (Input Terminal)
    0x01,                   // bDelay: 1ms
    0x01, 0x00,             // wFormatTag: PCM

    /* Format Type Descriptor */
    0x0B,                   // bLength: 11
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Format Type
    0x01,                   // bFormatType: FORMAT_TYPE_I
    AUDIO_SPK_OUT_CHANNEL_NUM, 
    0x02,                   // bSubFrameSize: 2 bytes (16-bit)
    0x10,                   // bBitResolution: 16 bits
    0x01,                   // bSamFreqType: 1 frequency
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,

    /* Standard Endpoint Descriptor (OUT) */
    0x09,                   // bLength: 9
    USB_DESC_ENDPOINT,      // bDescriptorType: Endpoint
    AUDIO_SPK_OUT_ENDPOINT_ADDRESS, // bEndpointAddress (e.g., 0x01)
    0x09,                   // bmAttributes: Isochronous
    U16_LOW_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
#if USB_HIGH_SPEED_EN
    0x04,                   // bInterval: 4 (HS)
#else
    0x01,                   // bInterval: 1 (FS)
#endif
    0x00,                   // bRefresh
    0x00,                   // bSynchAddress

    /* Class-Specific Endpoint Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_ENDPOINT,   // bDescriptorType: CS Endpoint
    0x01,                   // bDescriptorSubType: EP General
    0x01,                   // bmAttributes: Sampling Freq Control
    0x00,                   // bLockDelayUnits
    0x00, 0x00              // wLockDelay
};

#else
unsigned char config_desc[] = {
    // ==========================
    // 1. Configuration Descriptor
    // ==========================
    0x09,                   // bLength: 9
    USB_DESC_CONFIGURATION, // bDescriptorType: Configuration
    0x6E, 0x00,             // wTotalLength
    0x02,                   // bNumInterfaces: 2
    0x01,                   // bConfigurationValue: 1
    0x00,                   // iConfiguration: 0
    0x80,                   // bmAttributes: Self Powered
    0x19,                   // MaxPower: 50mA (0x19 * 2mA)

    // ==========================
    // 2. Audio Control Interface
    // ==========================
    /* Standard AC Interface Descriptor */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x00,                   // bInterfaceNumber: 0
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x01,                   // bInterfaceSubClass: Control
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Class-Specific AC Interface Header Descriptor */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: Header
    0x00, 0x01,             // bcdADC: UAC 1.0           
    0x28, 0x00,             // wTotalLength: 40 bytes (Total length of AC interface)
    0x01,                   // bInCollection: 1 stream interface
    0x01,                   // baInterfaceNr: 1

    /* Input Terminal Descriptor (USB Streaming) */
    0x0C,                   // bLength: 12
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Input Terminal
    0x01,                   // bTerminalID: 1
    0x01, 0x01,             // wTerminalType: 0x0101 (USB Streaming)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bNrChannels: 2 
    0x03, 0x00,             // wChannelConfig
    0x00,                   // iChannelName: 0
    0x00,                   // iTerminalName: 0

    /* Feature Unit Descriptor (Mic Volume/Mute) */
    0x0A,                   // bLength: 10 
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x06,                   // bDescriptorSubType: Feature Unit
    0x02,                   // bUnitID: 2
    0x01,                   // bSourceID: 1 (Input Terminal)
    0x01,                   // bControlSize: 1 byte
    0x03,                   // bmaControls(0): Master (Mute + Volume)
    0x00,                   // bmaControls(1): Channel 1
    0x00,                   // iFeature: 0
    0x00,

    /* Output Terminal Descriptor (Speaker) */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x03,                   // bDescriptorSubType: Output Terminal
    0x03,                   // bTerminalID: 3
    0x01, 0x03,             // wTerminalType: 0x0301 (Speaker)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bSourceID: 2 (Feature Unit)
    0x00,                   // iTerminal: 0

    // ==========================
    // 3. Audio Streaming Interface (Speaker Out)
    // ==========================
    /* Alt Setting 0: Zero Bandwidth */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x01,                   // bInterfaceNumber: 1
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Alt Setting 1: Operational */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x01,                   // bInterfaceNumber: 1
    0x01,                   // bAlternateSetting: 1
    0x01,                   // bNumEndpoints: 1 (OUT)
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* AS General Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: AS General
    0x01,                   // bTerminalLink: 1 (Output Terminal)
    0x01,                   // bDelay: 1ms
    0x01, 0x00,             // wFormatTag: PCM

    /* Format Type Descriptor */
    0x0B,                   // bLength: 11
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Format Type
    0x01,                   // bFormatType: FORMAT_TYPE_I
    AUDIO_SPK_OUT_CHANNEL_NUM, 
    0x02,                   // bSubFrameSize: 2 bytes (16-bit)
    0x10,                   // bBitResolution: 16 bits
    0x01,                   // bSamFreqType: 1 frequency
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,

    /* Standard Endpoint Descriptor (OUT) */
    0x09,                   // bLength: 9
    USB_DESC_ENDPOINT,      // bDescriptorType: Endpoint
    AUDIO_SPK_OUT_ENDPOINT_ADDRESS, // bEndpointAddress (e.g., 0x01)
    0x09,                   // bmAttributes: Isochronous
    U16_LOW_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
#if USB_HIGH_SPEED_EN
    0x04,                   // bInterval: 4 (HS)
#else
    0x01,                   // bInterval: 1 (FS)
#endif
    0x00,                   // bRefresh
    0x00,                   // bSynchAddress

    /* Class-Specific Endpoint Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_ENDPOINT,   // bDescriptorType: CS Endpoint
    0x01,                   // bDescriptorSubType: EP General
    0x01,                   // bmAttributes: Sampling Freq Control
    0x00,                   // bLockDelayUnits
    0x00, 0x00              // wLockDelay
};
#endif
unsigned char *usbd_get_config_descriptor(unsigned char bus)
{
    (void)bus;
    return (unsigned char *)&config_desc;
}

unsigned char device_qualifier[] = {
    0x0a,
    USB_DESC_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
};

unsigned char *usbd_get_device_qualifier_descriptor(unsigned char bus)
{
    (void)bus;
#if USB_HIGH_SPEED_EN
    return device_qualifier;
#else
    return NULL;
#endif
}
#if 1
unsigned char other_speed_config[] = {
    // ==========================
    // 1. Configuration Descriptor
    // ==========================
    0x09,                   // bLength: 9
    USB_DESC_CONFIGURATION, // bDescriptorType: Configuration
    0xC1, 0x00,             // wTotalLength:  (Total length of configuration descriptor)
    0x03,                   // bNumInterfaces: 3
    0x01,                   // bConfigurationValue: 1
    0x00,                   // iConfiguration: 0
    0x80,                   // bmAttributes: Self Powered
    0x19,                   // MaxPower: 50mA (0x19 * 2mA)

    // ==========================
    // 2. (Interface: 0) Audio Control Interface
    // ==========================
    /* Standard AC Interface Descriptor */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x00,                   // bInterfaceNumber: 0
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x01,                   // bInterfaceSubClass: Control
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Class-Specific AC Interface Header Descriptor */
    0x0A,                   // bLength: 10
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: Header
    0x00, 0x01,             // bcdADC: UAC 1.0           
    0x50, 0x00,             // wTotalLength: 71 bytes (Total length of AC interface)
    0x02,                   // bInCollection: 2 stream interface (Mic + Spk)
    0x01,                   // baInterfaceNr: 1 (Mic)
    0x02,                   // baInterfaceNr: 2 (Spk)

    /* (ID: 1) Microphone Input Terminal */
    0x0C,                   // bLength: 12
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Input Terminal
    0x01,                   // bTerminalID: 1
    0x01, 0x02,             // wTerminalType: 0x0201 (Microphone)
    0x00,                   // bAssocTerminal: 0
    0x01,                   // bNrChannels: 1 
    0x00, 0x00,             // wChannelConfig: 0
    0x00,                   // iChannelName: 0
    0x00,                   // iTerminal: 0

    /* (ID: 2) Microphone Feature Unit */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x06,                   // bDescriptorSubType: Feature Unit
    0x02,                   // bUnitID: 2
    0x01,                   // bSourceID: 1 (Mic Input)
    0x01,                   // bControlSize: 1
    0x03,                   // bmaControls(0): Mute + Volume
    0x00,                   // bmaControls(1): Channel 1
    0x00,                   // iFeature: 0

    /* (ID: 3) Microphone Output Terminal */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x03,                   // bDescriptorSubType: Output Terminal
    0x03,                   // bTerminalID: 3
    0x01, 0x01,             // wTerminalType: 0x0101 (USB Streaming)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bSourceID: 2 (Feature Unit)
    0x00,                   // iTerminal: 0

    /* (ID: 4) Speaker Input Terminal */
    0x0C,                   // bLength: 12
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Input Terminal
    0x04,                   // bTerminalID: 4
    0x01, 0x01,             // wTerminalType: 0x0101 (USB Streaming)
    0x00,                   // bAssocTerminal: 0
    0x02,                   // bNrChannels: 2 
    0x03, 0x00,             // wChannelConfig
    0x00,                   // iChannelName: 0
    0x00,                   // iTerminalName: 0

    /* (ID: 5) Feature Unit Descriptor (Speaker Volume/Mute) */
    0x0A,                   // bLength: 10 
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x06,                   // bDescriptorSubType: Feature Unit
    0x05,                   // bUnitID: 5
    0x04,                   // bSourceID: 4 (Input Terminal)
    0x01,                   // bControlSize: 1 byte
    0x03,                   // bmaControls(0): Master (Mute + Volume)
    0x00,                   // bmaControls(1): Channel 1
    0x00,                   // bmaControls(2): Channel 2
    0x00,                   // iFeature: 0

    /* (ID: 6) Output Terminal Descriptor (Speaker) */
    0x09,                   // bLength: 9
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x03,                   // bDescriptorSubType: Output Terminal
    0x06,                   // bTerminalID: 6
    0x01, 0x03,             // wTerminalType: 0x0301 (Speaker)
    0x00,                   // bAssocTerminal: 0
    0x05,                   // bSourceID: 5 (Feature Unit)
    0x00,                   // iTerminal: 0

    // ==========================
    // 3. (Interface: 1) Audio Streaming  (Microphone In)
    // ==========================
    // Alt Setting 0: Zero Bandwidth
    0x09,                       // bLength
    USB_DESC_INTERFACE,         // bDescriptorType
    0x01,                       // bInterfaceNumber: 1
    0x00,                       // bAlternateSetting: 0
    0x00,                       // bNumEndpoints: 0
    0x01,                       // bInterfaceClass: Audio
    0x02,                       // bInterfaceSubClass: Streaming
    0x00,                       // bInterfaceProtocol
    0x00,                       // iInterface

    // Alt Setting 1: Operational
    0x09,                   // bLength: Size of this descriptor (9 bytes)
    USB_DESC_INTERFACE,     // bDescriptorType: INTERFACE
    0x01,                   // bInterfaceNumber: Index of this interface (1)
    0x01,                   // bAlternateSetting: Alternate setting 1 (Active streaming)
    0x01,                   // bNumEndpoints: One endpoint used for audio data
    0x01,                   // bInterfaceClass: AUDIO
    0x02,                   // bInterfaceSubClass: AUDIO_STREAMING
    0x00,                   // bInterfaceProtocol: PR_PROTOCOL_UNDEFINED
    0x00,                   // iInterface: String descriptor index (None)

    // Class-specific AS Interface Descriptor
    0x07,                   // bLength: Size of this descriptor (7 bytes)
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS_INTERFACE
    0x01,                   // bDescriptorSubtype: AS_GENERAL
    0x03,                   // bTerminalLink: ID of the output Terminal
    0x01,                   // bDelay: 1ms
    0x01,                   // wFormatTag: PCM format (Low byte)
    0x00,                   // wFormatTag: PCM format (High byte)

    //Type I Format Type Descriptor
    0x0B,                   // bLength: Size of this descriptor (11 bytes)
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS_INTERFACE
    0x02,                   // bDescriptorSubtype: FORMAT_TYPE
    0x01,                   // bFormatType: FORMAT_TYPE_I
    0x01,                   // bNrChannels: Number of channels (1 - mono)
    0x02,                   // bSubframeSize: Bytes per subframe (2 bytes = 16-bit)
    0x10,                   // bBitResolution: Bits per sample (16 bits)
    0x01,                   // bSamFreqType: Number of supported sampling frequencies (1 discrete freq)
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,                   // tSamFreq[2]: 

    // --- Standard AS Isochronous Audio Data Endpoint Descriptor ---
    0x09,                   // bLength: Size of this descriptor (9 bytes)
    USB_DESC_ENDPOINT,      // bDescriptorType: ENDPOINT
    AUDIO_MIC_IN_ENDPOINT_ADDRESS, // bEndpointAddress: IN Endpoint (e.g., 0x81)
    0x0D,                   // bmAttributes: Isochronous transfer, Asynchronous synchronization
    U16_LOW_BYTE(AUDIO_MIC_IN_ENDPOINT_SIZE),  // wMaxPacketSize: Max packet size (Low byte)
    U16_HIGH_BYTE(AUDIO_MIC_IN_ENDPOINT_SIZE), // wMaxPacketSize: Max packet size (High byte)
    0x01,                   // bInterval: Polling interval for Full-Speed (1ms)
    0x00,                   // bRefresh: Reset endpoint (unused)
    0x00,                   // bSynchAddress: Address of sync endpoint (0x00 for Asynchronous)

    // --- Class-specific AS Isochronous Audio Data Endpoint Descriptor ---
    0x07,                   // bLength: Size of this descriptor (7 bytes)
    0x25,                   // bDescriptorType: CS_ENDPOINT
    0x01,                   // bDescriptorSubtype: EP_GENERAL
    0x01,                   // bmAttributes: Sampling frequency control supported
    0x00,                   // bLockDelayUnits: Undefined
    0x00,                   // wLockDelay: No lock delay (Low byte)
    0x00,                   // wLockDelay: No lock delay (High byte)

    // ==========================
    // 4. (Interface: 2) Audio Streaming (Speaker Out)
    // ==========================
    /* Alt Setting 0: Zero Bandwidth */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x02,                   // bInterfaceNumber: 2
    0x00,                   // bAlternateSetting: 0
    0x00,                   // bNumEndpoints: 0
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* Alt Setting 1: Operational */
    0x09,                   // bLength: 9
    USB_DESC_INTERFACE,     // bDescriptorType: Interface
    0x02,                   // bInterfaceNumber: 2
    0x01,                   // bAlternateSetting: 1
    0x01,                   // bNumEndpoints: 1 (OUT)
    0x01,                   // bInterfaceClass: Audio
    0x02,                   // bInterfaceSubClass: Streaming
    0x00,                   // bInterfaceProtocol: None
    0x00,                   // iInterface: 0

    /* AS General Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x01,                   // bDescriptorSubType: AS General
    0x04,                   // bTerminalLink: 4 (Input Terminal)
    0x01,                   // bDelay: 1ms
    0x01, 0x00,             // wFormatTag: PCM

    /* Format Type Descriptor */
    0x0B,                   // bLength: 11
    USB_DESC_CS_INTERFACE,  // bDescriptorType: CS Interface
    0x02,                   // bDescriptorSubType: Format Type
    0x01,                   // bFormatType: FORMAT_TYPE_I
    AUDIO_SPK_OUT_CHANNEL_NUM, 
    0x02,                   // bSubFrameSize: 2 bytes (16-bit)
    0x10,                   // bBitResolution: 16 bits
    0x01,                   // bSamFreqType: 1 frequency
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,

    /* Standard Endpoint Descriptor (OUT) */
    0x09,                   // bLength: 9
    USB_DESC_ENDPOINT,      // bDescriptorType: Endpoint
    AUDIO_SPK_OUT_ENDPOINT_ADDRESS, // bEndpointAddress (e.g., 0x01)
    0x09,                   // bmAttributes: Isochronous
    U16_LOW_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    0x01,                   // bInterval: 1 (FS)
    0x00,                   // bRefresh
    0x00,                   // bSynchAddress

    /* Class-Specific Endpoint Descriptor */
    0x07,                   // bLength: 7
    USB_DESC_CS_ENDPOINT,   // bDescriptorType: CS Endpoint
    0x01,                   // bDescriptorSubType: EP General
    0x01,                   // bmAttributes: Sampling Freq Control
    0x00,                   // bLockDelayUnits
    0x00, 0x00              // wLockDelay
};

#else
// this example use the same configuration for both high and full speed mode
unsigned char other_speed_config[] = {
    0x09,
    USB_DESC_CONFIGURATION,
    0x6E,
    0x00,
    0x02,
    0x01,
    0x00,
    0x80,
    0x19,
    0x09,
    USB_DESC_INTERFACE,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,
    0x09,
    0x24,
    0x01,
    0x00,
    0x01,
    0x28,
    0x00,
    0x01,
    0x01,
    0x0C,
    0x24,
    0x02,
    0x01,
    0x01,
    0x01,
    0x00,
    0x02,
    0x03,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x24,
    0x06,
    0x02,
    0x01,
    0x01,
    0x03,
    0x00,
    0x00,
    0x00,
    0x09,
    0x24,
    0x03,
    0x03,
    0x01,
    0x03,
    0x00,
    0x02,
    0x00,
    0x09,
    0x04,
    0x01,
    0x00,
    0x00,
    0x01,
    0x02,
    0x00,
    0x00,
    0x09,
    0x04,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x00,
    0x00,
    0x07,
    0x24,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x0B,
    0x24,
    0x02,
    0x01,
    AUDIO_SPK_OUT_CHANNEL_NUM,
    0x02,
    0x10,
    0x01,
    U16_LOW_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_SAMPLE_RATE),
    0x00,
    0x09,
    USB_DESC_ENDPOINT,
    AUDIO_SPK_OUT_ENDPOINT_ADDRESS,
    0x09,
    U16_LOW_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    U16_HIGH_BYTE(AUDIO_SPK_OUT_ENDPOINT_SIZE),
    0x01,
    0x00,
    0x00,
    0x07,
    0x25,
    0x01,
    0x81,
    0x00,
    0x00,
    0x00,
};
#endif
unsigned char *usbd_get_other_speed_configuration_descriptor(unsigned char bus, unsigned char index)
{
    (void)bus;
    (void)index;
#if USB_HIGH_SPEED_EN
    other_speed_config[1] = USB_DESC_OTHER_SPEED_CONFIG;
    return other_speed_config;
#else
    return NULL;
#endif

   
}

char const *string_desc_arr[] = {
    (const char[]){0x09, 0x04},
    STRING_VENDOR,
    STRING_PRODUCT,
    STRING_SERIAL,
};

static unsigned short _desc_str[64 + 1];

unsigned char *usbd_get_string_descriptor(unsigned char bus, unsigned char index)
{
    (void)bus;
    (void)index;
    unsigned short chr_count;

    switch (index) {
    case 0:
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
        break;

    default:
        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) {
            return NULL;
        }

        const char *str = string_desc_arr[index];

        // Cap at max char
        chr_count              = strlen(str);
        size_t const max_count = sizeof(_desc_str) / sizeof(_desc_str[0]) - 1; // -1 for string type
        if (chr_count > max_count) {
            chr_count = max_count;
        }

        // Convert ASCII string into UTF-16
        for (size_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
        break;
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t)((USB_DESC_STRING << 8) | (2 * chr_count + 2));

    return (unsigned char *)_desc_str;
}
#endif
#endif
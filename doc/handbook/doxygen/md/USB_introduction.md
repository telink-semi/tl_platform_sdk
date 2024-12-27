@page USB_Example USB

USB  (Universal Serial Bus) is an external bus standard used to standardize the connection and communication between computers and external devices. It is an interface technology applied in PC area. USB interface supports plug-and-play and hot-plug functions of devices. USB was jointly proposed by Intel, Compaq, IBM, Microsoft and many other companies at the end of 1994. As shown in the figure below, USB consists of four wires, namely VCC, GND, D- (DM), and D+ (DP). USB can choose to be powered through the host computer or self-powered, and most USB devices are currently powered through the host computer.

![USB interface](pic/usbinterface.png "USB interface")

The USB communication is the communication between the controller and the device, the computer host is the controller, Telink USB is the device, and the host referenced later is the controller by default. USB bus is a one-way bus, communication can only be initiated by the controller, the device receives a request from the controller, the data is sent to the controller. The controller is sending requests to the device every n units of time, and n is the user configuration parameter.

The USB has four operating speeds: Super Speed (5.0Gbit/s), High Speed (480Mbit/s), Full Speed (12Mbit/s) and Low Speed (1.5Mbit/s), where the communication frame period (the interval between sending two consecutive frames of data) of the Full Speed and Low Speed USB buses is 1ms, and the communication frame period of the High Speed USB bus is 125us. USB1.1 only supports full speed and low speed, USB2.0 supports high speed, full speed and low speed, and super speed is only supported in USB3.0.

# USB packet format and transfer process

Packet is the most basic unit of USB data transmission, that is, each data transmission is in the form of a packet. And packets have to be composed into transactions for effective communication. There are various packets for composing various transactions (IN, OUT, SETUP) according to the communication needs. One or more transactions make up a transmission (control transmission, bulk transmission, terminal transmission, and isochronous transmission).

Packets are the smallest unit of data transfer on the USB bus and cannot be interrupted or interfered with, otherwise it will raise an error. Several packets form a single transaction, and a single transaction cannot be interrupted either, that is, several packets belonging to a single transaction.

## USB packet structure

Packet is the basic unit of information transmission in the USB system, all data is packaged and transmitted on the bus.

As shown in the figure below, a USB packet consists of seven parts, namely the synchronization field (SYNC), packet identification (PID), address field (ADDR), endpoint field (ENDP), frame number field (FRAM), data field (DATA), and checksum field (CRC). Note that not every USB packet contains all seven of these fields, meaning that some packets contain only a few of them.

![Common format of USB packet](pic/commonformatofusbpacket.png "Common format of USB packet")

(1) Synchronization field

The sync field is mainly to notify each other of the start of data transfer and to provide a synchronous clock. For low-speed and full-speed devices, the synchronization field uses 0000 0001 (binary number); for high-speed devices it uses 000000 00000000 00000000 00000001.

(2) Packet ID (PID)

The packet ID is mainly used to identify the type of the packet and consists of 8 bits: the lower 4 bits are the PID code, and the upper 4 bits are the checksum field, which is obtained by inverting the lower 4 bits. Various packets in USB are distinguished by the PID field.

(3) Address field

Since there may be more than one device accessing the USB bus, the address field needs to be introduced to make it easier to distinguish which device is the one currently communicating. The address field contains 7 data bits and up to 128 addresses can be specified. Address 0 is used as the default address and is not assigned to a USB device. For each device on the USB bus, the address is unique.

(4) Endpoint field

The endpoint field is used to specify an endpoint number of a device on the USB bus, containing 4 data bits; full-speed/high-speed devices can contain up to 16 endpoints, and low-speed devices can contain up to 3 endpoints. All USB devices must contain an endpoint with endpoint number 0, which is used to exchange basic information between the host and the device. All endpoints except for endpoint 0 are specific to the specific USB device. The address field and endpoint field combination specifies the channel for communication between the host and the device.

(5) Frame number field

The frame number field is used to indicate the frame number of the current frame, which is sent only in the SOF token packet at the beginning of each frame/microframe. Its data bits are 11 bits long and are incremented by 1 for each frame transmitted by the host and zeroed when the maximum value of 7FFH is reached.

(6) Data field

The data field contains the data to be transferred between the host and the USB device in bytes, with a maximum length of 1024, while the actual length depends on the specifics of the transfer.

(7) Checksum field

The checksum field is primarily used to verify the correctness of the communication data. The CRC is used in both USB token packets and data packets. However, the CRC is generated by the sender prior to bit padding, which requires the receiver to decode the CRC field after removing the bit padding. The PID field in the message packet itself contains the checksum, so the CRC calculation does not contain a PID part. The CRC for the token packet uses a 5-bit CRC, and the data field in the data packet uses a 16-bit CRC.

### Token packets

The SOF packets are sent from the host to the device: every 1.00 ms ± 0.0005 ms for the full-speed bus and every 125us ± 0.0625us for the high-speed bus.

The SOF packet format is as below.

![SOF packet format](pic/sofpacketformat.png "SOF packet format")

The IN, OUT, SETUP packet format is as below.

![IN OUT SETUP packet format](pic/inoutsetuppacketformat.png "IN OUT SETUP packet format")

### Data packets

Data packets (DATA0, DATA1, DATA2, MDATA)

![Data packets](pic/datapackets.png "Data packets")

### Handshake packets

PRE, ACK, NAK, STALL, NYET packet format.

![PRE ACK NAK STALL NYET packet format](pic/preacknakstallnyetpacketformat.png "PRE ACK NAK STALL NYET packet format")

## USB transfer process

### USB transaction

The process of receiving or sending data at one time in USB is called Transaction, and the transaction is usually composed of a series of packets. For different transactions, the packets composed of transactions are different. In the USB data transfer, common transactions include IN transaction, OUT transaction, and SETUP transaction. Note that SOF is only an indication of the beginning of a frame with no valid data and is not a transaction; EOF is a level state at the end of a frame transmission and is not a transaction.

The transaction usually consists of two or three packets: a token packet, a data packet, and a handshake packet. The token packet initiates the transaction, the data packet transmits the data, the sender of the handshake packet is usually the data receiver. When the data is correctly received, the handshake packet is sent, and the device can also use NACK to indicate that the data is not ready.

### Input transaction

An input (IN) transaction is the process of a host getting data from one of the endpoints of a USB device. As shown in the figure below, an input transaction has three states, namely, a normal input transaction (figure (a)), an input transaction when the device is busy or has no data (figure (b)), and an input transaction when the device is in error (figure (c)). A correct input transaction includes three phases: token packet, data packet, and handshake packet.

**Input transaction processing flow**

![(a) Normal input transaction](pic/normalinputtransaction.png "Normal input transaction")

![(b) Input transaction when device is busy or no data](pic/inputtransactionwhendeviceisbusy.png "Input transaction when device is busy or no data")

![(c) Input transaction when device is in error](pic/inputtransactionwhendeviceiserror.png "Input transaction when device is in error")

The normal input transaction is introduced and analyzed with the normal input transaction example. As shown in the following figure, a normal input transaction contains three interaction processes: (1) Host sends an IN token packet to Device; (2) Device receives the IN token packet and sends the data to be sent to the host; (3) Host receives the packet and replies with an ACK packet to confirm the packet is received correctly.

![Example of a normal input transaction](pic/examplenormalinputtransaction.png "Example of a normal input transaction")

### Output transaction

An output (OUT) transaction is the process of sending data from a host to one of the endpoints of a USB device. As shown in the figure below, an output transaction has three states, namely, a normal output transaction (figure (a)), an output transaction when the device is busy (figure (b)), and an output transaction when the device is in error (figure (c)). The correct output transaction includes three phases: token, data and handshake.

**Output transaction processing flow**

![(a) Normal output transaction](pic/normaloutputtransaction.png "Normal output transaction")

![(b) Output transaction when device is busy](pic/outputtransactionwhendeviceisbusy.png "Output transaction when device is busy")

![(c) Output transaction when device is in error](pic/outputtransactionwhendeviceiserror.png "Output transaction when device is in error")

The following is an introduction and analysis of a normal output transaction with an example of a normal output transaction. As shown in the following figure, a normal output transaction contains three interaction processes: (1) Host sends an OUT token packet to Device; (2) Host sends a data packet to Device; (3) Device receives the data packet and replies with an ACK packet to confirm that the data packet was correctly received.

![Example of a normal output transaction](pic/examplenormaloutputtransaction.png "Example of a normal output transaction")

### Setup transaction

The SETUP transaction handles and defines the special data transfer between Host and Device, which is only applicable to the establishment phase of USB control transfer. As shown in the figure below, the setup transaction usually has three states, namely, normal setup transaction (figure (a)), device busy setup transaction (figure (b)) and device error setup transaction (figure (c)), and the correct setup transaction includes three phases: token, data and handshake.

**SETUP transaction process**

![(a) Normal setup transaction](pic/normalsetuptransaction.png "Normal output transaction")

![(b) Setup transaction processing when device is busy](pic/setuptransactionwhendeviceisbusy.png "Setup transaction processing when device is busy")

![(c) Setup transaction processing when device is in error](pic/setuptransactionwhendeviceiserror.png "Setup transaction processing when device is in error")

The following is an introduction and analysis of a normal SETUP transaction with an example of a normal SETUP transaction. As shown in the figure below, a normal setup transaction consists of three interaction processes: (1) Host sends a SETUP token packet to Device; (2) Host sends a DATA0 packet to Device; (3) Device receives the packet and replies with an ACK packet to confirm that the packet was received correctly.

![Example of a normal setup transaction](pic/examplenormalsetuptransaction.png "Example of a normal setup transaction")

## USB transfer

The USB transfer consists of transactions such as OUT, IN or SETUP. The USB standard protocol defines four types of transfers: Control Transfer, Bulk Transfer, Interrupt Transfer and Isochronous Transfer. The priority of the four types of transfers from high to low is: Isochronous Transfer, Interrupt Transfer, Control Transfer, and Bulk Transfer.

### Control transfer

The Control Transfer is the most basic and important transfer method in USB, and is the default transfer method for port 0. Control Transfer is typically used for transfers between the host and USB peripherals on Endpoint 0, but vendor-specific Control Transfer may be used on other endpoints. Control Transfer is primarily used to query, configure, and send generic commands to USB devices. Control transfers are unidirectional (except for Endpoint 0, which is bidirectional) and the amount of data is usually small. The maximum packet length of the control transfer depends on its operating speed, with a fixed maximum packet length of 8 bytes for low-speed mode, 64 bytes for high-speed mode, and a choice of 8, 16, 32, and 64 bytes for full-speed mode.

**Note:**

> - The packet length of Telink USB's endpoint 0 is a fixed length of 8 bytes, and no other value can be configured.
> - The control transfer is composed of three stages, namely the setup stage, the data stage (optional) and the status stage, each consisting of one or more (data stage) transactions.
> - Setup stage: The setup stage consists of the SETUP transaction as shown in the figure below. The data stage of the SETLUP transaction always uses DATA0 and has a fixed length of 8 bytes.

![Flowchart for creating a transaction](pic/flowchartforcreatingtransaction.png "Flowchart for creating a transaction")

> - Data stage: The data stage is optional. If a data stage is available, it includes one or more IN/OUT transactions, which are used to transfer data in the USB defined format as required by the setup stage. The transactions in the data stage have the same direction, that is, either all IN or all OUT. if the data to be transferred is larger than the length of a packet, the controller divides it into multiple packets for transfer. Once the data transfer direction is changed, it is considered to enter the status process. The first packet of the data process must be a DATA1 packet, and then each time it seeks to transfer a packet it is exchanged between DATA0 and DATA1. If the last packet size is equal to the maximum packet size, then another packet of size 0 should be transferred to determine the end. According to the direction of data transfer the data stage, control transmission can be further divided into three types, namely Control Write, Control Read and No-data Control, as shown in the following figure.

![Control transfer sequence diagram](pic/controltransfersequence.png "Control transfer sequence diagram")

> - Status stage: The status stage is the last stage of control transaction processing and consists of an IN or OUT transaction, always composed using DATA1 packets. The status stage is transferred in the opposite direction to the data stage, that is, if the data stage is IN, the status stage is OUT, and vice versa. It is used to report the results of the setup stage and data stage transfers.

### Interrupt transfer

The Interrupt Transfer is the same as bulk transfer except that it does not support PING and NYET packets, so its sequence diagram can refer to bulk transfer. The main difference between interrupt transfer and bulk transfer is reflected in two points: First, the priority is different, interrupt transfer has a higher priority than bulk transfer, second only to isochronous transfer; Second, the maximum packet length supported is different, the maximum packet length of interrupt transfer low-speed mode is capped at 8 bytes, the maximum packet length of full-speed mode is capped at 64 bytes, and the maximum packet length of high-speed mode is capped at 1024 bytes.

It is important to note that the interrupt described here is not the same as interrupt on hardware. Since USB does not support hardware interrupt, the host must be polled periodically to know if a device needs to transmit data to the host. It can be seen that interrupt transfer is also a polling process, polling period determined by the user device (polling interval of full-speed device is 1ms \~ 255ms, low-speed device is 10ms \~ 255ms), the host only needs to ensure that schedule a transfer in no greater than the interval. The polling period is very important, if it is too fast, it will occupy too much bus bandwidth; if it is too low, the data may be lost, so the user needs to set it according to the condition of their data.

Interrupt transfers are typically used in devices that do not have a large amount of data, but are time-critical, such as keyboard and mouse in human interface devices (HIDs). Interrupt transfer can also be used to continuously check the status of the device and then use bulk transfer to transfer large amounts of data when the conditions are met. The endpoint type of interrupt transfer is generally IN endpoint, that is, from Device to Host (IN transaction), rarely used in OUT endpoint, some computers do not even support interrupt transfer OUT transaction.

![Interrupt transfer flow chart](pic/interrupttransferflowchart.png "Interrupt transfer flow chart")

### Isochronous transfer

The Isochronous Transfer is an unreliable transfer. Isochronous transfer has only two stages, token packet (IN/OUT token packet) and data packet (DATAx), it has no handshake packet and does not support PID inverse, host has the highest priority when scheduling the transfer. The maximum length of isochronous transfer packet is capped at 1023 bytes for full-speed mode, 1024 bytes for high-speed mode, and isochronous transfer is not supported for low-speed mode.

![Isochronous transfer flow chart](pic/isochronoustransferflowchart.png "Isochronous transfer flow chart")

Isochronous transfer is suitable for data that must arrive at a fixed rate or at a specified moment in time, where occasional errors can be tolerated. USB reserves bus bandwidth for it, ensuring that it can be served within each frame/small frame. The rate is accurate and the transfer time is predictable. However, error control and retransfer mechanisms are not used, and success is not guaranteed for every transfer, it is suitable for audio and video devices.

### Bulk transfer

The Bulk Transfer, also known as block transfer, is a one-way reliable transfer consisting of one or more IN/OUT transactions in which the packets in the transaction are inverted according to DATA0-DATA1-DATA0-... to ensure synchronization between the transmitting end and the receiving end, as shown in the figure below.

![Bulk transfer flow chart](pic/bulktransferflowchart.png "Bulk transfer flow chart")

The error detection and retransfer mechanism in USB is done by hardware. If this transfer has error, the DATA packet will not be inverted and the packet will be retransferred. At the same time, the receiving end receives consecutive DATA packets with the same PID, which will be considered as retransfer packets. USB allows less than 3 consecutive transfer errors, if more than 3 times, the host considers the endpoint function error (STALL) and abandons the transfer task of the endpoint.

# USB applications

This chapter is not about the real USB applications, but about the design of the application layer that lies above the USB driver layer. This chapter will explain in detail the basic concepts and working principles of USB from the user's point of view, in order to facilitate the user's familiarity and mastery of the basics and usage of USB.

## Basic concept

The relationship between USB hardware devices and software devices is that a USB hardware device can correspond to one or more software devices, depending on the user's enumeration information (configuration descriptor information). A software device is a virtual device in which the PC abstracts the interface of a hardware device, a class that implements the same function, and can be operated in a uniform manner. A software device contains one or more interfaces, an interface contains one or more endpoints (endpoints will be explained below), and interfaces and endpoints are all concepts in a hardware device.

An Endpoint is the smallest unit in a USB device that can send and receive data. Except for Endpoint 0 (which is fixed for bidirectional control transfer), all other endpoints support only unidirectional communication, that is, input endpoints (data flow from device to host) or output endpoints (data flow from host to device). The number of endpoints supported by the device is limited to a maximum of 2 groups of endpoints (2 inputs, 2 outputs) for low-speed devices and a maximum of 15 groups of endpoints for high-speed and full-speed devices, in addition to the default endpoint 0.

The Interface is a collection of endpoints that make up a basic function in a USB device, and is the object controlled by the USB device driver (the host will virtualize a USB device that can be operated directly on the PC according to the interface, the virtual device is a USB device class). From the host, a USB device can consist of one or more interfaces, such as a USB device with an integrated mouse and keyboard, they have two Interfaces, one for the keyboard and the other for the mouse; for example, an audio device is composed of an interface for command transmission and an interface for data transmission.

The summary is as follows:

Endpoint: An endpoint is the only identifiable part of a USB device that is the end point of the communication flow between the host and the device, and is a data buffer on a USB device or host that is used to store and send various data from the USB.

Interface: can be understood as a function.

Configuration: For the combination of interfaces, select which combination during the connection.

![USB applications](pic/usbapplications.png "USB applications")

# Standard descriptor

The Descriptor is data knot used to describe the attributes of a device and it is divided into standard descriptor and proprietary descriptor. Standard descriptor is common to all USB device classes, including device descriptor, configuration descriptor, interface descriptor, endpoint descriptor, and string descriptor, among which string descriptor is divided into serial number descriptor, product descriptor, vendor descriptor, and language ID descriptor. Proprietary descriptor is unique to each device class, such as HID class unique descriptor has HID descriptor, report descriptor and entity descriptor, and so on. The following figure shows the standard device request structure specified by the USB protocol.

![Data structure of a standard device request](pic/datastructureofstandarddevicerequest.png "Data structure of a standard device request")

## Device descriptor

A device descriptor describes the basic information of a USB device, which has only one device descriptor. The following diagram presents the structure of a standard device descriptor. The first 8 bytes summarize the basic properties of USB, which is the first information the host has to obtain in the USB enumeration.

| Offset | Field              | Size | Value    | Description                                                                                           |
| ------ | ------------------ | ---- | -------- | ----------------------------------------------------------------------------------------------------- |
| 0      | bLength            | 1    | Digital  | Number of bytes in this description table                                                             |
| 1      | bDecriptorType     | 1    | Constant | Type of descriptor (here it should be 0x01, which is device descriptor)                               |
| 2      | bcdUSB             | 2    | BCD code | USB device description version number (BCD code) of this device compatible with the description table |
| 4      | bDeviceClass       | 1    | Class    | Equipment class code.                                                                                 |
| 5      | bDeviceSubClass    | 1    | Subclass | Subclass mask                                                                                         |
| 6      | bDevicePortocol    | 1    | Protocol | Protocol code                                                                                         |
| 7      | bMaxPacketSize0    | 1    | Digital  | Maximum packet size for endpoint 0 (only 8,16,32,64 are legal values)                                 |
| 8      | idVendor           | 2    | ID       | Vendor id (assigned by the USB-IF organization)                                                       |
| 10     | idProduct          | 2    | ID       | Product id (assigned by the manufacturer)                                                             |
| 12     | bcdDevice          | 2    | BCD code | Device issue number (BCD code)                                                                        |
| 14     | iManufacturer      | 1    | Index    | The index value of the string descriptor describing the vendor information.                           |
| 15     | iProduct           | 1    | Index    | The index value of the string descriptor describing the product information.                          |
| 16     | iSerialNumber      | 1    | Index    | The index value of the string descriptor describing the device serial number information.             |
| 17     | bNumConfigurations | 1    | Digital  | Number of possible configuration descriptors                                                          |

**Note:**

> - idVendor(VID) and idProduct(PID) are used to uniquely identify a device, but for the Windows system, given only the VID and PID, it does not uniquely identify the device, which behaves as a non-stop installation of new drivers. At this point, you also need to consider the serial number string, that is, only when the VID, PID and serial number are consistent, Windows only need to install the driver once.
> - The index values of the three string descriptors should be different values (except 0).

## Configuration descriptor

A configuration descriptor defines the configuration information of a device. A device can have multiple configuration descriptors.

| Offset | Field                | Size | Value    | Description                                                                                                           |
| ------ | -------------------- | ---- | -------- | --------------------------------------------------------------------------------------------------------------------- |
| 0      | bLength              | 1    | Digital  | The length of the byte count of this description table.                                                               |
| 1      | bDescriptorType      | 1    | Constant | Configure description table type (0x02 here)                                                                          |
| 2      | wTotalLength         | 2    | Digital  | Total length of this configuration information (including configuration, interface, endpoint descriptors)             |
| 4      | bNumInterfaces       | 1    | Digital  | Number of interfaces supported by this configuration                                                                  |
| 5      | bCongfigurationValue | 1    | Digital  | Use as a parameter in the SetConfiguration(x) request to select this configuration                                    |
| 6      | iConfiguration       | 1    | Index    | Description of the string description table index for this configuration (0 - none)                                   |
| 7      | bmAttributes         | 1    | Bitmap   | Configuration features: \n  &nbsp;&nbsp;&nbsp;&nbsp;D7: Reserved (set to one); \n  &nbsp;&nbsp;&nbsp;&nbsp;D6: Self-powered; \n  &nbsp;&nbsp;&nbsp;&nbsp;D5: Remote wake-up; \n  &nbsp;&nbsp;&nbsp;&nbsp;D4..0: Reserved (set to one) |
| 8      | MaxPower             | 1    | mA       | Bus power consumption in this configuration, in units of 2mA                                                          |

## Interface descriptor

The interface descriptor describes the configuration provided by the interface. The number of interfaces owned by a configuration is determined by the bNumInterfaces of the configuration descriptor.

| Offset | Field              | Size | Value    | Description                                                                                                         |
| ------ | ------------------ | ---- | -------- | ------------------------------------------------------------------------------------------------------------------- |
| 0      | bLength            | 1    | Digital  | Number of bytes of this table                                                                                       |
| 1      | bDescriptorType    | 1    | Constant | Interface description table class (should be 0x04 here)                                                             |
| 2      | bInterfaceNumber   | 1    | Digital  | Interface number, the index of the array of interfaces supported by the current configuration (starting from zero). |
| 3      | bAlternateSetting  | 1    | Digital  | The index value of the optional setting.                                                                            |
| 4      | bNumEndpoints      | 1    | Digital  | Number of endpoints for this interface, except endpoint 0                                                           |
| 5      | bInterfaceClass    | 1    | Class    | The value of the class to which the interface belongs                                                               |
| 6      | bInterfaceSubClass | 1    | Subclass | Subclass code .                                                                                                     |
| 7      | bInterfaceProtocol | 1    | Protocol | Protocol code: bInterfaceClass and bInterfaceSubClass fields depending on the value.                                |
| 8      | iInterface         | 1    | Index    | The index value of the string description table describing this interface.                                          |

## Endpoint descriptor

Each endpoint in a USB device has its own endpoint descriptor, the number of which is determined by the bNumEndpoint in the interface descriptor.

| Offset | Field            | Size | Value    | Description |
| ------ | ---------------- | ---- | -------- | ----------- |
| 0      | bLength          | 1    | Digital  | Length of bytes of this description table |
| 1      | bDescriptorType  | 1    | Constant | Endpoint description table class (should be 0x05 here) |
| 2      | bEndpointAddress | 1    | Endpoint | Address and direction of the endpoints described in this description table: \n Bit 3..0 : Endpoint number. The endpoint number cannot be repeated in the change configuration; \n Bit 6..4 : Reserved, zero; \n Bit 7: Direction, omitted if the control endpoint. \n &nbsp;&nbsp;&nbsp;&nbsp;0: Output endpoint (host to device). \n &nbsp;&nbsp;&nbsp;&nbsp;1: Input endpoint (device to host). |
| 3      | bmAttributes     | 1    | Bitmap   | The characteristics of the endpoint. Bit 1..0 :Transfer type \n &nbsp;&nbsp;&nbsp;&nbsp;00=Control transfer \n &nbsp;&nbsp;&nbsp;&nbsp;01=Isochronous transfer \n &nbsp;&nbsp;&nbsp;&nbsp;10=Bulk transfer \n &nbsp;&nbsp;&nbsp;&nbsp;11=Interrupt transfer |
| 4      | wMaxPacketSize   | 2    | Digital  | The maximum packet size that this endpoint can receive or send in the current configuration. For interrupt transfer, bulk transfer and control transfer, endpoints may send packets shorter than this. |
| 6      | bInterval        | 1    | Digital  | The interval at which the host polls this endpoint, is ignored for bulk and control transfer endpoints; \n  &nbsp;&nbsp;&nbsp;&nbsp;for isochronous transfer endpoints, it must be 1; \n  &nbsp;&nbsp;&nbsp;&nbsp;for interrupt transfer, it is 10 to 255 (ms) here for low-speed mode and 1 to 255 (ms) for full-speed mode.                                                              |

## String descriptor

The String descriptor is optional. If string descriptor is not supported, all string descriptors within their device, configuration, and interface descriptors must have an index of 0. Language string descriptors have an index of 0.

| Offset | Field           | Size | Value    | Description                                                                    |
| ------ | --------------- | ---- | -------- | ------------------------------------------------------------------------------ |
| 0      | bLength         | 1    | Digital  | Number of bytes for this description table (value N + 2 for the bString field) |
| 1      | bDescriptorType | 1    | Constant | String description table type (here should be 0x03)                            |
| 2      | bString         | N    | Digital  | UNICODE encoded strings                                                        |

# USB enumeration

The Enumeration is that the host reads some information from the device side to know what kind of device it is and how it communicates, so that the host can load the appropriate driver based on this information. When debugging USB devices, it is important to check the USB enumeration, as long as the enumeration is successful, it has been mostly successful. The following USB enumeration sequence diagram (figure (a) below) and the Telink mouse class USB enumeration example (figure (b) below) are to introduce the USB enumeration process in detail.

## USB enumeration sequence

The USB enumeration sequence diagram is given in the figure below, from which we can see that the USB enumeration process is divided into 8 steps to complete, where Step 1 to 7 is the standard USB enumeration process, and Step 8 is the USB device class proprietary enumeration process.

![(a) USB enumeration sequence diagram](pic/usbenumerationsequence.png "USB enumeration sequence diagram")

- Step 1	After the host detects a device access: first, the host determines whether the device is a low-speed device or a full-speed device based on the level status on the differential signal line (high-speed devices are considered to be full-speed devices by default at the initial power-up); then the host waits for the device power to stabilize (>=100ms) and sends a reset signal to the device (D+ and D- all low for >=10ms); finally, if it is a high-speed device and the host (Hub) supports high-speed mode, the device can switch to high-speed mode after the host and the device perform high-speed detection and handshake, otherwise it still maintains full-speed mode.

- Step 2	After Step 1, the host will use endpoint 0 (default endpoint, control transfer) and send a GetDescriptor request (device address is 0). After the device receives the request, it will send its own device descriptor to the host, and the host will take the next action based on this device descriptor (bMaxPacketSize0 field). It should be noted that: (1) only the device receives the reset signal in Step 1 to respond to the host; (2) the device that has completed the enumeration does not respond to the request; (3) the length of the descriptor is at least 8 bytes (bMaxPacketSize0 field is in the 8th byte); (4) if the device timeout without respond or responds incorrectly, the host will start again and try three times, and if still cannot get the correct response for three times, the host will consider the device as an unrecognizable device (the same below).

- Step 3	After the host correctly completes Step 2 and obtains the maximum packet length for endpoint 0, it resets the device, after which the packets will be unpacked and grouped according to that length.

- Step 4	The host assigns a non-zero address to the device that is different from the other devices on the hub and is used to ensure the stability of directed communication. After the host completes addressing the device, communication between the host and the device will continue at the new address until the device is reset or removed.

- Step 5	The host gets the standard descriptors (device descriptor, configuration descriptor, interface descriptor, endpoint descriptor and string descriptor) of the device in order according to the new address of the device in Step 4. Note: (1) the host has already obtained the length of the device descriptor in Step 2, so the host specifies the length (the maximum length is the length of the device descriptor) to get the device descriptor, other descriptors are obtained by finding the maximum length 255, the device end only needs to send according to the actual length; (2) the interface descriptor and endpoint descriptor of the device may be included in the configuration descriptor. The host will retrieve all the data for the configuration based on the wTotalLength field in the configuration descriptor. (3) If the device has more than one configuration, the host will divide it into multiple times to request the configuration descriptors; (4) The host will request the string descriptors according to the number of string descriptors contained in the descriptors of the device, configuration, interface and endpoint, according to their index values. And the index value of 0 is special string descriptor (voice information descriptor).

- Step 6	After completing Step 5, the host obtains the actual length of the configuration descriptor, and in turn obtains the configuration descriptor information and other information contained in the configuration descriptor (such as interface descriptor and endpoint descriptor, and so on).

- Step 7	Step 1\~6 is the standard USB enumeration process. Only when Step 1\~6 are all correct, the host issues the SetConfiguration command to activate and use a configuration of the device, and then the device is truly available. After the device is configured, the host will split the device into one or more virtual devices based on the standard descriptor of the device.

- Step 8	After Step 7 is completed, one or more virtual devices are generated on the host, and each virtual device has its class identification. The host will look up the corresponding driver according to its VID, PID and serial number, and install the driver (if it has backup on the host, it will be used directly and not installed anymore). Then, the host loads the corresponding class-exclusive description information according to the driver. The standard HID device is given here, and the host comes with the driver.

## USB enumeration example

The following figure (b) is the enumeration process when Telink Dongle is used as a mouse device, Step x in the figure corresponds to Step x in the above figure (a). Step 8 is the HID device class proprietary enumeration process, that is, to obtain the report descriptor, the structure of the report descriptor can be referred to the USB HID protocol Universal Serial Bus (USB)-Device Class Definition for Human Interface Devices (HID).

![(b) Enumeration flow when Telink Dongle is a mouse device](pic/enumerationflowwhentelinkdongleisamouse.png "Enumeration flow when Telink Dongle is a mouse device")

# USB hardware introduction

The Telink USB hardware module internally solidifies the processing of raw packets and transactions, automatically completes the saving of IN endpoint data and the sending of OUT endpoint data, and packages the data of endpoint 0 into standard user packets, which not only improves the efficiency of USB execution but also minimizes the difficulty of USB development.

# USB endpoint

## Endpoint configuration

Telink USB supports USB1.1 protocol and adopts external power supply mode. The DP pin has a 1.5k pull-up resistor (optional for users), users can set the analog register to enable (set to 1) or disable (set to 0) the USB function, and the default is off. Telink USB has 9 endpoints, i.e. endpoint 0 and endpoints 1\~8, the endpoints 1, 2, 3, 4, 7 and 8 can be configured as input endpoints, while endpoints 5 and 6 are configured as output endpoints. Endpoint 0 can only use control transfer, endpoints 1\~8 support three other transfer modes except control transfer. In audio applications, endpoints 6 and 7 are isochronous transfer endpoints by default (users can turn off the isochronous transfer function of endpoints 6 and 7 by clearing bit6 and bit7 of digital register 0x38). The endpoint 6 supports synchronous output and endpoint 7 supports synchronous input.

| Configurable endpoint type                  | Endpoint number     |
| ------------------------------------------- | ------------------- |
| Control endpoints (both inputs and outputs) | 0                   |
| Output endpoint                             | 5, 6                |
| Input endpoint                              | 1, 2, 3, 4, 7 and 8 |

## Endpoint memory allocation

Telink USB uses 8+256 bytes USB exclusive RAM to cache the data of each endpoint, the RAM address of endpoint 0 is fixed and the size is 8 bytes, the rest of the endpoints share 256 bytes. The user can configure the address registers as needed to set the starting location of each endpoint data. The cache size of the endpoint is the starting address of the next endpoint minus the starting address of this endpoint. The USB endpoint resource allocation chart is calculated based on the default configuration in the table below (USB Endpoint Register Default Allocation Table). The hardware will store the received data into the corresponding buffer or take data from the corresponding buffer and send it to the host according to the user's configuration. It should be noted that the user should calculate the address of each endpoint when configuring the address register, otherwise it may trigger data overwriting problems.

<center>
| Endpoint starting address | Meaning                     |
| ------------------------- | --------------------------- |
| 0x00                      | Endpoint 1 starting address |
| 0x08                      | Endpoint 2 starting address |
| 0x10                      | Endpoint 3 starting address |
| 0x20                      | Endpoint 6 starting address |
| 0x30                      | Endpoint 7 starting address |
| 0x40                      | Endpoint 4 starting address |
| 0x80                      | Endpoint 8 starting address |
| 0xc0                      | Endpoint 5 starting address |
</center>

![USB endpoint resource allocation chart](pic/usbendpointresourceallocation.png "USB endpoint resource allocation chart")

**Note:**

> - The endpoint cache size is determined by the following two conditions:

    a) At the starting point of each endpoint, the cache size of the endpoint is the starting address of the next endpoint minus the starting address of this endpoint. For example, if endpoint 1 starts at 0x00 and endpoint 2 starts at 0x08, the endpoint 1 has a cache size of 0x08 bytes. The default endpoint addresses are not ordered by endpoint 1-8, but by the starting address of the endpoint.
    b) The endpoint cache maximum is determined by the max register (except for endpoint 7, which can be allocated to all cache space) and defaults to 64 bytes, so the cache size for each endpoint should not exceed 64 bytes maximum.

> - The endpoint starting address only works for endpoint cache allocation if it is used in an enumerated device. For example, usb audio only uses endpoints 6 and 7, the other default starting addresses, do not work for cache allocation.

# Interrupt

The USB interrupts can be divided into three types, endpoint 0 interrupt, endpoints 1-8 interrupts and suspend/250us/reset interrupts, shown as below.

| Interrupt                          | Generation conditions                   | Automatic or manual clearing |
| ---------------------------------- | --------------------------------------- | ---------------------------- |
| CTRL_EP_SETUP(IRQ7)                | Endpoint 0 control transfer setup phase | Clear status manually        |
| CTRL_EP_DATA (IRQ8)                | Endpoint 0 control transfer data phase  | Clear status manually        |
| CTRL_EP_STATUS (IRQ9)              | Endpoint 0 control transfer state phase | Clear status manually        |
| Endpoint(1-8) interrupts(IRQ11) \n FLD_USB_EDP8_IRQ (in)  \n FLD_USB_EDP1_IRQ (in)  \n FLD_USB_EDP2_IRQ (in)  \n FLD_USB_EDP3_IRQ (in)  \n FLD_USB_EDP4_IRQ (in)  \n FLD_USB_EDP5_IRQ (out) \n FLD_USB_EDP6_IRQ (out) \n FLD_USB_EDP7_IRQ (in) \n | 1. Except for synchronous endpoints \n &nbsp;&nbsp;&nbsp;&nbsp;Output endpoint: host out transaction, the corresponding position 1 of the status register, generating interrupt, after receiving return ACK. \n  &nbsp;&nbsp;&nbsp;&nbsp;Input endpoint: After the data is filled, configure ACK, notifies the hardware and generates an interrupt, and the hardware sends the data to the host upon receipt of the host in transaction. \n 2. Synchronous endpoints Endpoints 6, 7 can be set as synchronous endpoints and timed at 1ms to generate an interrupt.| Clear status manually |
|USB_IRQ_USB_SUSPEND (IRQ24)       |USB bus idle, for example, unplug USB port, host hibernate                |Clear status manually|
|USB_IRQ_250us (IRQ34)             |250us timed interrupt                                                     |Clear status manually|
|USB_IRQ_RESET (IRQ35)             |Host sends reset timings                                                  |Clear status manually|

**Note:**

> - Driver enumeration process transfers are handled by polling and no interrupts are used.

# Automatic and manual modes

Telink USB has two modes, namely automatic mode and manual mode:

Users can set the configuration register of endpoint 0 to control whether to choose automatic mode or manual mode. The default configuration register of Endpoint 0 is 0xFF, which is auto mode, when all codecs related to USB endpoint 0 are automatically driven by Telink hardware, and Telink comes with a driver for Print device. Use endpoint 8 as the endpoint of the control interface, from which printer data is sent to endpoint 0.

The Manual mode requires the user to modify the EDP0CFG register (as below), typically by setting bit[7] and bit[5] to 0, that is, the user is to complete the enumeration of the standard USB and use the user-defined descriptors.

![Endpoint0 configuration register](pic/endpoint0configurationregister.png "Endpoint0 configuration register")

# USB software fundamental

# USB operation flow

The software operation flow of Telink USB can be divided into two phases, namely the initialization phase and the cyclic detection phase, as shown in the figure below.

![Telink USB operation flow chart](pic/telinkusboperationflowchart.png "Telink USB operation flow chart")

During the initialization phase it mainly completes the USB-related configuration and enables USB. The USB configuration options include mode switching (auto mode and manual mode), setting USB data buffer and setting other configuration items; mode switching is mainly to switch the USB working mode to manual mode, at this time the related enumeration process and descriptors are controlled by the user, and the device will report the enumeration information prepared by the user to the host; setting USB buffer is to assign a buffer to the related endpoints (total buffer size 256 Bytes, endpoints not used do not need to be specified) according to the usage of their endpoints (except endpoint 0); setting other configurations is used for other configuration operations, users can choose to configure themselves if they do not want to use the system default configuration items, such as interrupt form transferring data, and so on.

The main purpose of the loop detection is to constantly check whether there is data in the data receive and send buffers, and if there is data, then the relevant operation will be performed, and usb_handle_irq will be executed repeatedly during the program run. The operation process of endpoint 0 can be divided into three stages, as shown in the figure below, which correspond to the SETUP stage, DATA stage and STATUS stage of the control transfer, mainly to complete the USB identification and configuration, such as USB enumeration which is completed in the main loop; SETUP parses the commands sent by the host and prepares the corresponding data according to the host's commands; DATA sends the data prepared in the data stage to the host or receives the data sent by the host; STATUS is the handshake process between the two sides.

![Endpoint0 data operation flow](pic/endpoint0dataoperationflow.png "Endpoint0 data operation flow")

# Data receiving and sending

## Data receiving

Telink USB data receiving is done by the hardware, which will save the received data into RAM, and the hardware will generate an interrupt to notify the user after the receiving is completed, and the user only needs to read the data after the interrupt is detected. Data detection and receiving should be performed in the usb_handle_irq function in usb.c. Combined with the following diagram, the processing flow of Telink USB data receiving is analyzed in detail:

(1) The user needs to check if the relevant interrupt identification bit (reg_usb_irq) is set to 1. If it is set to 1, the data reception stage is entered.

(2) Once the data has been detected, the user needs to clear the interrupt identification bit, that is reg_usb_irq = BIT((USB_EDP_CUSTUM_OUT & 0x07)).

(3) Before the user can read the data, he needs to use reg_usb_ep_ptr(USB_EDP_CUSTUM_OUT) to get the length of the received data.

(4) After the user gets the data length, he can get all the data received this time by repeatedly reading usbhw_read_ep_data(USB_EDP_CUSTUM_OUT).

(5) After the user receives the data, he needs to set the call to usbhw_data_ep_ack(USB_EDP_CUSTUM _OUT). (Note that this step is important, only when the ACK of the OUT endpoint is set up, the hardware will go to receive the data sent down to that endpoint by the host and generate an interrupt when the receiving is complete.)

![Telink USB data receiving ](pic/telinkusbdatareceiving.png "Telink USB data receiving ")

## Data sending

Telink USB data sending is done by hardware just like data receiving, user only needs to fill the data into the corresponding USB RAM and set the data ACK bit to 1. Before filling the data, user needs to first detect if there is pending data in the USB RAM, if there is pending data, you need to wait for the completion of sending before filling the new data, otherwise the data overwrite will occur.

The following figure gives an example of sending data in the Telink SDK. The following is a detailed analysis of the USB data sending process with this example:

(1) Before sending data, the user needs to detect if the operating endpoint is busy, and if it is busy (data to be sent), it needs to wait until the sending is completed before filling the data.

(2) If the endpoint is idle, the endpoint counter needs to be reset first, that is reg_usb_ep_ptr(USB_EDP _CUSTUM_CMISC_IN) = 0.

(3) After resetting the endpoint counter, the user can fill the endpoint with data. Note that reg_usb_ep_dat(USB_EDP_CUSTUM_CMISC_IN) = data[i] puts the data into the USB RAM (hardware operation).

(4) After the user fills the data, he needs to call reg_usb_ep_ctrl(USB_EDP_CUSTUM_CMISC_IN) = FLD_EP_DAT_ACK to inform the hardware that the data is ready and the hardware will send the data to the next host when it requests it after receiving this command.

![Telink USB data sending ](pic/telinkusbdatasending.png "Telink USB data sending ")

# USB demo

The USB application mainly introduces the USB standard device class HID (Human Interface Device) device, Audio device, CDC (Communication Device Class) device simple application, customers can freely combine according to the needs.

The HID class devices are common types of USB devices, which are USB devices that interact directly with people, such as USB mouse, USB keyboard.

The most common USB Audio devices are microphones and speakers.

The CDC class of USB is the abbreviation for the USB communication device class, and the virtual serial device is a type of CDC class device.

In the header USB_DEMO/app_config.h you can choose to configure it as different devices.

```C
#define 	USB_MOUSE 			1
#define 	USB_KEYBOARD		2
#define 	USB_MICROPHONE		3
#define 	USB_SPEAKER		 	4
#define 	USB_CDC 			5
#define 	USB_MIC_SPEAKER 	6

#define 	USB_DEMO_TYPE		USB_MOUSE
```

## USB mouse

### Mouse processing flow

The USB HID devices transfer data via report. A report descriptor can describe multiple reports, and different reports are identified by their ID, which is the first byte of the report. When no report ID is specified, the report has no ID field and starts with data. Detailed information on the report descriptors can be found in the USB HID protocol and in the HID Usage Tables.

First the host identifies the Telink USB as a mouse device, which needs to go through an enumeration stage, and after the device is successfully enumerated, it enters the data sending and receiving stage. According to the content of mouse report descriptor, there are 4 bytes in the descriptor with report ID USB_HID_MOUSE. The low 5 bits of the 1st byte word indicate whether the key is pressed or not, and the high 3 bits are constant and useless; the 2nd byte is the amount of X-axis change; the 3rd byte is the amount of Y-axis change; and the 4th byte is the amount of scroll wheel change. The report is returned by the function usbmouse_hid_report( USB_HID_MOUSE ,mouse,4).

In the Demo program, the array unsigned char mouse[4] is defined, where mouse[0]: BIT(0) - left key; BIT(1) - right key; BIT(2) - middle key; BIT(3) - side key; BIT(4) - external key. The corresponding bit is set to 1, which means the corresponding mouse button is pressed; mouse[1]: the amount of change relative to the x coordinate; mouse[2]: the amount of change relative to the y coordinate; mouse[3]: the amount of change of the scroll wheel.

### Mouse test

**Press test**

In the demo program, report ID: USB_HID_MOUSE=1,

Assignment of the array mouse: mouse[0]=BIT(1), mouse[1]= -2 (code complement), mouse [2]=2, mouse[3]=2.

Ground pin PD1 on the development board and then unplug it, the function usbmouse_hid_report(USB_HID_ MOUSE,mouse,4) will be executed.

You can observe that the on the desktop right mouse button is pressed and the mouse cursor is moved down to the left, as in the figure below, and also from the USB packet capture tool Input Report[1]: x:-2,Y:2,wheel:0,Btns=[2].

![Mouse Input Report packet capture screenshot](pic/mouseinputreportpacketcapture.png "Mouse Input Report packet capture screenshot")

**Release test** 

The same operation as PD1 is performed on pin PD2, the mouse array is cleared to zero and the key is released.

## USB keyboard

### Keyboard processing process

According to the contents of the keyboard report descriptor, there are input and output reports, where the input report specifies 8 bytes and the 8 bits of the first byte indicate whether the special key is pressed or not.

BYTE0 : BIT(0) - Left Ctl ; BIT(1) - Left Shift ; BIT(2) - Left Alt ; BIT(3) - Left GUI 

BIT(4) - Right Ctl; BIT(5) - Right Shift; BIT(6) - Right Alt; BIT(7) - Right GUI 

The second byte is a reserved value, both are 0. 

BYTE1: 0

Bytes 3 to 8 are common key value. When no key is pressed, all 6 bytes are 0. The first byte value of these 6 bytes is the key value of the key, and when more than one key is pressed at the same time, the key values are returned at the same time, and the order of the keys in the array is irrelevant. Please refer to the HID Usage Table document for specific key values. For example, 0x59 corresponds to numeric keypad 1; 0x5a corresponds to numeric keypad 2; 0x5b corresponds to numeric keypad 3; 0x39 corresponds to case-switching key.

### Keyboard test

**Press test**

In the demo program, define the array kb_data[6] and assign the values kb_data[0] = 0; kb_data[1] = 0; kb_data[2] = 0x59; kb_data[3] = 0x5a; kb_data[4] = 0x39; kb_data[5] = 0;

Ground pin PC1 on the development board and then unplug it, the function usbkb_hid_report_normal(0x10, kb_data ) will be executed, where parameter 1 corresponds to the first byte and parameter 2 is an array corresponding to 3~8 bytes.

It can be observed that in the edit window input screen, the numbers 1 and 2 will be entered and the right Ctrl key and capslock key pressed.

As shown in the figure below, you can also see from the USB packet capture tool Input Report: Keys=[Rctrl 1 2 CapsLk]

![Keyboard Input Report packet capture screenshot](pic/keyboardinputreportpacketcapture.png "Keyboard Input Report packet capture screenshot")

**Release test**

Perform the same operation on GPIO_PC2 as GPIO_PC1, special keys and kb_data array are cleared to zero and keys are released.

## USB MIC

### MIC processing flow

Take AMIC for example, the USB microphone device is the device's AMIC data through the USB transfer to the host, you need to ensure that the entire data channel sampling rate and channel number match. In Demo program, the main data upload to the USB part is different, Mic endpoint interrupt is 1ms timing interrupt, also 1ms into an interrupt. According to the different sampling rate, 1ms generate different amounts of data, for example, 16K sampling rate receive sounds, mono data, 1 sample for 2 bytes, 1ms data for 32bytes, correspond to the audio buff will be filled into the USB SRAM.

### Mic demo test

In Audio-related tests, we use the help of Audacity software, as shown in the figure below microphone choosing Telink Audio16, speaker choosing PC speaker.

Device Mic receive sounds, PC speaker playback, if recorded vocals can be played through the speaker without distortion, indicating that the Mic works properly.

![Audacity software setup (Mic)](pic/audacitysoftwaresetupmic.png "Audacity software setup")

## USB speaker

### Speaker handling process

The USB speaker device is transferring the audio data from the host to the device via USB, and this process is also done in a 1ms interrupt, reading the length of the USB SRAM data and filling the corresponding data to the audio buff.

### Speaker demo test

In Audacity software, select PC Microphone for microphone and Telink Audio16 for speaker. We use the output audio interface (3.5mm headphone jack). If the recorded vocals can be played out through the headphones without distortion, it means that the speaker is working properly.

![Audacity software setup (Spk)](pic/audacitysoftwaresetupspk.png "Audacity software setup")

## USB CDC

The CDC device has two interfaces, a CDC control interface and a CDC data interface. The control interface allocates endpoint 2, as an interrupt input endpoint transfer. The data interface allocates endpoint 5 (out), endpoint 4 (out), and must first set the ACK of endpoint 5 up before the endpoint can receive data from the USB host.

### CDC processing flow

USB Installation of CDC Device

The first time the host is recognized as a CDC device, the .inf file needs to be installed manually, as shown in the following figure under the 8278_USB_Demo path.

![.inf file path](pic/inffilepath.png ".inf file path")

**Data receiving (host to device)**

In Demo program, in function void usb_cdc_irq_data_process(void) host send data to device, endpoint 5 generates interrupt, function usb_cdc_rx_data_from_host(usb_cdc_data) is for data receiving.

**Data sending (device to host)**

As shown in the figure below, in main_loop, when the received buff data length is judged to be non-zero, the received data is sent to host by the function usb_cdc_rx_data_from_host(usb_cdc_data).

![Data sending](pic/datasending.png "Data sending")

### CDC demo test

The test phenomenon is shown in the figure below, which returns the data sent by the serial tool.

![CDC data transceiver test](pic/cdcdatatransceivertest.png "CDC data transceiver test")

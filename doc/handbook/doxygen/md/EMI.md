@page EMI_Example EMI

EMI samples are used with "EMI_Tool" and "Non_Signaling_Test_Tool" tools. This document mainly introduces related functions and considerations in the EMI test samples.

# Protocol

Please refer to the _Telink SoC EMI Test User Guide_ for the communication protocol.

# Program description

EMI testing in Eagle supports carrieronly mode, continue mode, burst mode, and packet-receiving mode.

The supported wireless communication methods include Ble1M, Ble2M, Ble125K, Ble500K, and Zigbee250K.

## CarrierOnly mode

Function: The CarrierOnly mode is used to generate a single-pass signal. In this mode, you can set the channel, power value and the communication mode (rf mode) for the single-pass signal.

**Example:**

Test tool: select EMI_Tool

Wireless communication mode setting: Ble1M/Ble2M/Ble125K/Ble500K/Zigbee250K

Power setting: XXdB

Channel setting: 2402~2480MHz

![CarrierOnly mode](pic/carrieronlymode.png "CarrierOnly mode")

## Continue mode

Function: The continue mode is used to generate a continuous signal, in which the channel, power value as well as the communication mode (rf mode) can be set.

The continue mode sending packet (Payload) data includes Prbs9, 0x0f, and 0x55, and can set frequency hop.

**Example:**

Test tool: select EMI_Tool

Wireless communication mode setting: Ble1M/Ble2M/Ble125K/Ble500K/Zigbee250K

Power setting: XXdB

Channel setting: 2402~2480MHz

**Note:**

> - Currently EMI_Tool only supports sending prbs9 packets in continue mode.

![Continue mode](pic/continuemode.png "Continue mode")

## Burst mode

Function: The burst mode allows you to set the channel, power value and the communication mode (rf mode) for the Burst signal.

The burst mode sending packet (Payload) data includes Prbs9, 0x0f, and 0x55.

**Example:**

Test tool: select Non_Signaling_Test_Tool

Wireless communication mode setting: Ble1M/Ble2M/Ble125K/Ble500K/Zigbee250K

Power setting: XXdB

Channel setting: 2402~2480MHz

**Note:**

> - Due to the discontinuous signal in Burst mode, the Single Sweep and MaxHold settings of the spectrum analyzer can be used to capture the signal.

The first three pictures below are the results of the Single Sweep setting, and the fourth picture is the result of the MaxHold setting.

![Burst mode 1](pic/burstmode1.png "Burst mode 1")

![Burst mode 2](pic/burstmode2.png "Burst mode 2")

![Burst mode 3](pic/burstmode3.png "Burst mode 3")

![Burst mode 4](pic/burstmode4.png "Burst mode 4")

## RX Mode

Function: In the packet-receiving mode, communication mode can be set to receive packets, specifically with the non-signaling test tool "Non_Signaling_Test_Tool" to obtain the number of packets received and RSSI.

**Example:**

Test tool: select Non_Signaling_Test_Tool

Wireless communication mode setting: Ble1M/Ble2M/Ble125K/Ble500K/Zigbee250K

Channel setting: 2402~2480MHz

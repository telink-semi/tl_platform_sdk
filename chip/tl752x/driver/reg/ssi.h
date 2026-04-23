/*******************************************************************************************************
 *
 * @file    ssi.h
 *
 * @brief   This is the source file for tl752x
 *
 * @author  ExpanseMicro BSP Team
 * @par     Copyright (C) 2025-2035 Expanse Microelectronics (Shanghai) Co., Ltd
 *
 * @author  Telink Driver Group
 * @par     Copyright (c) 2025, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 * @date   2025
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
#ifndef __SSI_H__
#define __SSI_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//CTRLR0 offsetaddress : 0x0
#define SSI_DFS_POS (0U)
#define SSI_DFS_MSK \
    (0x1fUL         \
     << SSI_DFS_POS) /*!< Data Frame Size. Selects the data frame length. When the data frame size is programmed to be less than 32 bits, the receive data is automatically right-justified by the receive logic, with the upper bits of the receive FIFO zero-padded. You must right-justify transmit data before writing into the transmit FIFO. The transmit logic ignores the upper unused bits when transmitting the data. Note: When SSIC_SPI_MODE is set to "Dual", "Quad" or "Octal" mode and SPI_FRF is not set to 2'b00: ■ DFS value must be a multiple of 2 if SPI_FRF = 01 ■ DFS value must be multiple of 4 if SPI_FRF = 10 ■ DFS value must be multiple of 8 if SPI_FRF = 11 Values: ■ 0x0 (DFS_01_BIT): Reserved ■ 0x1 (DFS_02_BIT): Reserved ■ 0x2 (DFS_03_BIT): Reserved ■ 0x3 (DFS_04_BIT): 04-bit serial data transfer ■ 0x4 (DFS_05_BIT): 05-bit serial data transfer ■ 0x5 (DFS_06_BIT): 06-bit serial data transfer ■ 0x6 (DFS_07_BIT): 07-bit serial data transfer ■ 0x7 (DFS_08_BIT): 08-bit serial data transfer ■ 0x8 (DFS_09_BIT): 09-bit serial data transfer ■ 0x9 (DFS_10_BIT): 10-bit serial data transfer ■ 0xa (DFS_11_BIT): 11-bit serial data transfer ■ 0xb (DFS_12_BIT): 12-bit serial data transfer ■ 0xc (DFS_13_BIT): 13-bit serial data transfer ■ 0xd (DFS_14_BIT): 14-bit serial data transfer ■ 0xe (DFS_15_BIT): 15-bit serial data transfer ■ 0xf (DFS_16_BIT): 16-bit serial data transfer ■ 0x10 (DFS_17_BIT): 17-bit serial data transfer■ 0x11 (DFS_18_BIT): 18-bit serial data transfer ■ 0x12 (DFS_19_BIT): 19-bit serial data transfer ■ 0x13 (DFS_20_BIT): 20-bit serial data transfer ■ 0x14 (DFS_21_BIT): 21-bit serial data transfer ■ 0x15 (DFS_22_BIT): 22-bit serial data transfer ■ 0x16 (DFS_23_BIT): 23-bit serial data transfer ■ 0x17 (DFS_24_BIT): 24-bit serial data transfer ■ 0x18 (DFS_25_BIT): 25-bit serial data transfer ■ 0x19 (DFS_26_BIT): 26-bit serial data transfer ■ 0x1a (DFS_27_BIT): 27-bit serial data transfer ■ 0x1b (DFS_28_BIT): 28-bit serial data transfer ■ 0x1c (DFS_29_BIT): 29-bit serial data transfer ■ 0x1d (DFS_30_BIT): 30-bit serial data transfer ■ 0x1e (DFS_31_BIT): 31-bit serial data transfer ■ 0x1f (DFS_32_BIT): 32-bit serial data transfer Value After Reset: SSIC_DFLT_DFS Exists: Always*/
#define SSI_DFS                SSI_DFS_MSK
#define SSI_DFS_W(X)           ((X) << SSI_DFS_POS)
#define SSI_RSVD_CTRLR0_5_POS  (5U)
#define SSI_RSVD_CTRLR0_5_MSK  (0x1UL << SSI_RSVD_CTRLR0_5_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_CTRLR0_5      SSI_RSVD_CTRLR0_5_MSK
#define SSI_RSVD_CTRLR0_5_W(X) ((X) << SSI_RSVD_CTRLR0_5_POS)
#define SSI_FRF_POS            (6U)
#define SSI_FRF_MSK \
    (0x3UL          \
     << SSI_FRF_POS) /*!< Frame Format. Selects which serial protocol transfers the data. Values: ■ 0x0 (SPI): Motorola SPI Frame Format ■ 0x1 (SSP): Texas Instruments SSP Frame Format ■ 0x2 (MICROWIRE): National Semiconductors Microwire Frame Format ■ 0x3 (RESERVED): Reserved Value After Reset: SSIC_DFLT_FRF Exists: Always Memory Access: "(SSIC_HC_FRF==0) ? \"read-write\" : \"read-only\""*/
#define SSI_FRF      SSI_FRF_MSK
#define SSI_FRF_W(X) ((X) << SSI_FRF_POS)
#define SSI_SCPH_POS (8U)
#define SSI_SCPH_MSK \
    (0x1UL           \
     << SSI_SCPH_POS) /*!< Serial Clock Phase. Valid when the frame format (FRF) is set to Motorola SPI. The serial clock phase selects the relationship of the serial clock with the slave select signal. When SCPH = 0, data are captured on the first edge of the serial clock. When SCPH = 1, the serial clock starts toggling one cycle after the slave select line is activated, and data are captured on the second edge of the serial clock. Values: ■ 0x1 (START_BIT): Serial clock toggles at start of first bit ■ 0x0 (MIDDLE_BIT): Serial clock toggles in middle of first bit Value After Reset: SSIC_DFLT_SCPH Exists: Always Memory Access: "(SSIC_HC_FRF==0) ? \"read-write\" : \"read-only\""*/
#define SSI_SCPH      SSI_SCPH_MSK
#define SSI_SCPH_W(X) ((X) << SSI_SCPH_POS)
#define SSI_SCPOL_POS (9U)
#define SSI_SCPOL_MSK \
    (0x1UL            \
     << SSI_SCPOL_POS) /*!< Serial Clock Polarity. Valid when the frame format (FRF) is set to Motorola SPI. Used to select the polarity of the inactive serial clock, which is held inactive when the DWC_ssi master is not actively transferring data on the serial bus. Values: ■ 0x0 (INACTIVE_HIGH): Inactive state of serial clock is low ■ 0x1 (INACTIVE_LOW): Inactive state of serial clock is high Value After Reset: SSIC_DFLT_SCPOL Exists: Always Memory Access: "(SSIC_HC_FRF==0) ? \"read-write\" : \"read-only\""*/
#define SSI_SCPOL      SSI_SCPOL_MSK
#define SSI_SCPOL_W(X) ((X) << SSI_SCPOL_POS)
#define SSI_TMOD_POS   (10U)
#define SSI_TMOD_MSK \
    (0x3UL           \
     << SSI_TMOD_POS) /*!< Transfer Mode. Selects the mode of transfer for serial communication. This field does not affect the transfer duplicity. Only indicates whether the receive or transmit data are valid. In transmit-only mode, data received from the external device is not valid and is not stored in the receive FIFO memory; it is overwritten on the next transfer. In receive-only mode, transmitted data are not valid. After the first write to the transmit FIFO, the same word is retransmitted for the duration of the transfer. In transmit-and-receive mode, both transmit and receive data are valid. The transfer continues until the transmit FIFO is empty. Data received from the external device are stored into the receive FIFO memory, where it can be accessed by the host processor. Values: ■ 0x0 (TX_AND_RX): Transmit & Receive; Not Applicable in enhanced SPI operating mode ■ 0x1 (TX_ONLY): Transmit only mode; Or Write in enhanced SPI operating mode ■ 0x2 (RX_ONLY): Receive only mode; Or Read in enhanced SPI operating mode ■ 0x3 (EEPROM_READ): EEPROM Read mode; Not Applicable in enhanced SPI operating mode Value After Reset: SSIC_DFLT_TMOD Exists: Always*/
#define SSI_TMOD       SSI_TMOD_MSK
#define SSI_TMOD_W(X)  ((X) << SSI_TMOD_POS)
#define SSI_SLV_OE_POS (12U)
#define SSI_SLV_OE_MSK \
    (0x1UL             \
     << SSI_SLV_OE_POS) /*!< Slave Output Enable. Relevant only when the DWC_ssi is configured as a serial- slave device. When configured as a serial master, this bit field has no functionality. This bit enables or disables the setting of the ssi_oe_n output from the DWC_ssi serial slave. When SLV_OE = 1, the ssi_oe_n output can never be active. When the ssi_oe_n output controls the tri-state buffer on the txd output from the slave, a high impedance state is always present on the slave txd output when SLV_OE = 1. This is useful when the master transmits in broadcast mode (master transmits data to all slave devices). Only one slave may respond with data on the master rxd line. This bit is enabled after reset and must be disabled by software (when broadcast mode is used), if you do not want this device to respond with data. Values: ■ 0x1 (DISABLED): Slave Output is disabled ■ 0x0 (ENABLED): Slave Output is enabled Value After Reset: 0x0 Exists: Always*/
#define SSI_SLV_OE      SSI_SLV_OE_MSK
#define SSI_SLV_OE_W(X) ((X) << SSI_SLV_OE_POS)
#define SSI_SRL_POS     (13U)
#define SSI_SRL_MSK \
    (0x1UL          \
     << SSI_SRL_POS) /*!< Shift Register Loop. Used for testing purposes only. When internally active, connects the transmit shift register output to the receive shift register input. Can be used in both serial-slave and serial- master modes. When the DWC_ssi is configured as a slave in loopback mode, the ss_in_n and ssi_clk signals must be provided by an external source. In this mode, the slave cannot generate these signals because there is nothing to which to loop back. Values: ■ 0x1 (TESTING_MODE): Test Mode Operation ■ 0x0 (NORMAL_MODE): Normal mode operation Value After Reset: 0x0 Exists: Always*/
#define SSI_SRL      SSI_SRL_MSK
#define SSI_SRL_W(X) ((X) << SSI_SRL_POS)
#define SSI_SSTE_POS (14U)
#define SSI_SSTE_MSK \
    (0x1UL           \
     << SSI_SSTE_POS) /*!< Slave Select Toggle Enable. While operating in SPI mode with clock phase (SCPH) set to 0, this register controls the behavior of the slave select line (ss_*_n) between data frames. Values: ■ 0x1 (TOGGLE_EN): ss_*_n line will toggle between consecutive data frames, with the serial clock (sclk) being held to its default value while ss_*_n is high ■ 0x0 (TOGGLE_DISABLE): ss_*_n will stay low and sclk will run continuously for the duration of the transfer Value After Reset: 0x1 Exists: Always*/
#define SSI_SSTE                SSI_SSTE_MSK
#define SSI_SSTE_W(X)           ((X) << SSI_SSTE_POS)
#define SSI_RSVD_CTRLR0_15_POS  (15U)
#define SSI_RSVD_CTRLR0_15_MSK  (0x1UL << SSI_RSVD_CTRLR0_15_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_CTRLR0_15      SSI_RSVD_CTRLR0_15_MSK
#define SSI_RSVD_CTRLR0_15_W(X) ((X) << SSI_RSVD_CTRLR0_15_POS)
#define SSI_CFS_POS             (16U)
#define SSI_CFS_MSK \
    (0xfUL          \
     << SSI_CFS_POS) /*!< Control Frame Size. Selects the length of the control word for the Microwire frame format. Values: ■ 0x0 (SIZE_01_BIT): 01-bit Control Word ■ 0x1 (SIZE_02_BIT): 02-bit Control Word ■ 0x2 (SIZE_03_BIT): 03-bit Control Word ■ 0x3 (SIZE_04_BIT): 04-bit Control Word ■ 0x4 (SIZE_05_BIT): 05-bit Control Word ■ 0x5 (SIZE_06_BIT): 06-bit Control Word ■ 0x6 (SIZE_07_BIT): 07-bit Control Word ■ 0x7 (SIZE_08_BIT): 08-bit Control Word ■ 0x8 (SIZE_09_BIT): 09-bit Control Word ■ 0x9 (SIZE_10_BIT): 10-bit Control Word ■ 0xa (SIZE_11_BIT): 11-bit Control Word ■ 0xb (SIZE_12_BIT): 12-bit Control Word ■ 0xc (SIZE_13_BIT): 13-bit Control Word ■ 0xd (SIZE_14_BIT): 14-bit Control Word ■ 0xe (SIZE_15_BIT): 15-bit Control Word ■ 0xf (SIZE_16_BIT): 16-bit Control Word Value After Reset: SSIC_DFLT_CFS Exists: Always*/
#define SSI_CFS                    SSI_CFS_MSK
#define SSI_CFS_W(X)               ((X) << SSI_CFS_POS)
#define SSI_RSVD_CTRLR0_20_21_POS  (20U)
#define SSI_RSVD_CTRLR0_20_21_MSK  (0x3UL << SSI_RSVD_CTRLR0_20_21_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_CTRLR0_20_21      SSI_RSVD_CTRLR0_20_21_MSK
#define SSI_RSVD_CTRLR0_20_21_W(X) ((X) << SSI_RSVD_CTRLR0_20_21_POS)
#define SSI_SPI_FRF_POS            (22U)
#define SSI_SPI_FRF_MSK \
    (0x3UL              \
     << SSI_SPI_FRF_POS) /*!< SPI Frame Format Selects data frame format for Transmitting/Receiving the data. Bits only valid when SSIC_SPI_MODE is either set to "Dual" or "Quad" or "Octal" mode. Values: ■ 0x0 (SPI_STANDARD): Standard SPI Format ■ 0x1 (SPI_DUAL): Dual SPI Format ■ 0x2 (SPI_QUAD): Quad SPI Format ■ 0x3 (SPI_OCTAL): Octal SPI Format Value After Reset: SSIC_DFLT_SPI_FRF Exists: Always Memory Access: "(SSIC_SPI_MODE==0) ? \"read-only\": \"read-write\""*/
#define SSI_SPI_FRF             SSI_SPI_FRF_MSK
#define SSI_SPI_FRF_W(X)        ((X) << SSI_SPI_FRF_POS)
#define SSI_SPI_HYPERBUS_EN_POS (24U)
#define SSI_SPI_HYPERBUS_EN_MSK \
    (0x1UL                      \
     << SSI_SPI_HYPERBUS_EN_POS) /*!< SPI Hyperbus Frame format enable. Selects if data frame format for Transmitting/Receiving the data is in Hyperbus mode. This field is effective only when CTRLRO.FRF is set to SPI frame format. Values: ■ 0x0 (DISABLE): Disable Hyperbus Format ■ 0x1 (ENABLE): Enable Hyperbus Format Value After Reset: SSIC_DFLT_HYPERBUS_EN Exists: Always Memory Access: "(SSIC_HYPERBUS_EN==0) ? \"read- only\": \"read-write\""*/
#define SSI_SPI_HYPERBUS_EN        SSI_SPI_HYPERBUS_EN_MSK
#define SSI_SPI_HYPERBUS_EN_W(X)   ((X) << SSI_SPI_HYPERBUS_EN_POS)
#define SSI_RSVD_CTRLR0_25_31_POS  (25U)
#define SSI_RSVD_CTRLR0_25_31_MSK  (0x7fUL << SSI_RSVD_CTRLR0_25_31_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_CTRLR0_25_31      SSI_RSVD_CTRLR0_25_31_MSK
#define SSI_RSVD_CTRLR0_25_31_W(X) ((X) << SSI_RSVD_CTRLR0_25_31_POS)

//CTRLR1 offsetaddress : 0x4
#define SSI_NDF_POS (0U)
#define SSI_NDF_MSK \
    (0xffffUL       \
     << SSI_NDF_POS) /*!< Number of Data Frames. When TMOD = 10 or TMOD = 11, this register field sets the number of data frames to be continuously received by the DWC_ssi. The DWC_ssi continues to receive serial data until the number of data frames received is equal to this register value plus 1, which enables you to receive up to 64 KB of data in a continuous transfer. When the DWC_ssi is configured as a serial slave, the transfer continues for as long as the slave is selected. Therefore, this register serves no purpose and is not present when the DWC_ssi is configured as a serial slave. Value After Reset: SSIC_DFLT_NDF Exists: Always*/
#define SSI_NDF              SSI_NDF_MSK
#define SSI_NDF_W(X)         ((X) << SSI_NDF_POS)
#define SSI_RSVD_CTRLR1_POS  (16U)
#define SSI_RSVD_CTRLR1_MSK  (0xffffUL << SSI_RSVD_CTRLR1_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_CTRLR1      SSI_RSVD_CTRLR1_MSK
#define SSI_RSVD_CTRLR1_W(X) ((X) << SSI_RSVD_CTRLR1_POS)

//SSIENR offsetaddress : 0x8
#define SSI_SSIC_EN_POS (0U)
#define SSI_SSIC_EN_MSK \
    (0x1UL              \
     << SSI_SSIC_EN_POS) /*!< SSI Enable. Enables and disables all DWC_ssi operations. When disabled, all serial transfers are halted immediately. Transmit and receive FIFO buffers are cleared when the device is disabled. It is impossible to program some of the DWC_ssi control registers when enabled. When disabled, the ssi sleep output is set (after delay) to inform the system that it is safe to remove the ssi_clk, thus saving power consumption in the system. Values: ■ 0x1 (ENABLED): Enables DWC_ssi ■ 0x0 (DISABLE): Disables DWC_ssi Value After Reset: SSIC_BOOT_MODE_EN Exists: Always*/
#define SSI_SSIC_EN          SSI_SSIC_EN_MSK
#define SSI_SSIC_EN_W(X)     ((X) << SSI_SSIC_EN_POS)
#define SSI_RSVD_SSIENR_POS  (1U)
#define SSI_RSVD_SSIENR_MSK  (0x7fffffffUL << SSI_RSVD_SSIENR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SSIENR      SSI_RSVD_SSIENR_MSK
#define SSI_RSVD_SSIENR_W(X) ((X) << SSI_RSVD_SSIENR_POS)

//MWCR offsetaddress : 0xc
#define SSI_MWMOD_POS (0U)
#define SSI_MWMOD_MSK \
    (0x1UL            \
     << SSI_MWMOD_POS) /*!< Microwire Transfer Mode. Defines whether the Microwire transfer is sequential or non- sequential. When sequential mode is used, only one control word is needed to transmit or receive a block of data words. When non-sequential mode is used, there must be a control word for each data word that is transmitted or received. Values: ■ 0x1 (SEQUENTIAL): Sequential Transfer ■ 0x0 (NON_SEQUENTIAL): Non-Sequential Transfer Value After Reset: 0x0 Exists: Always*/
#define SSI_MWMOD      SSI_MWMOD_MSK
#define SSI_MWMOD_W(X) ((X) << SSI_MWMOD_POS)
#define SSI_MDD_POS    (1U)
#define SSI_MDD_MSK \
    (0x1UL          \
     << SSI_MDD_POS) /*!< Microwire Control. Defines the direction of the data word when the Microwire serial protocol is used. When this bit is set to 0, the data word is received by the DWC_ssi MacroCell from the external serial device. When this bit is set to 1, the data word is transmitted from the DWC_ssi MacroCell to the external serial device. Values: ■ 0x1 (TRANSMIT): SSI transmits data ■ 0x0 (RECEIVE): SSI receives data Value After Reset: 0x0 Exists: Always*/
#define SSI_MDD      SSI_MDD_MSK
#define SSI_MDD_W(X) ((X) << SSI_MDD_POS)
#define SSI_MHS_POS  (2U)
#define SSI_MHS_MSK \
    (0x1UL          \
     << SSI_MHS_POS) /*!< Microwire Handshaking. Relevant only when the DWC_ssi is configured as a serial- master device. When configured as a serial slave, this bit field has no functionality. Used to enable and disable the busy/ready handshaking interface for the Microwire protocol. When enabled, the DWC_ssi checks for a ready status from the target slave, after the transfer of the last data/control bit, before clearing the BUSY status in the SR register. Values: ■ 0x1 (ENABLED): handshaking interface is enabled ■ 0x0 (DISABLE): handshaking interface is disabled Value After Reset: 0x0 Exists: Always Memory Access: {(SSIC_IS_MASTER == 1) ? "read-write" : "read-only"}*/
#define SSI_MHS            SSI_MHS_MSK
#define SSI_MHS_W(X)       ((X) << SSI_MHS_POS)
#define SSI_RSVD_MWCR_POS  (3U)
#define SSI_RSVD_MWCR_MSK  (0x1fffffffUL << SSI_RSVD_MWCR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_MWCR      SSI_RSVD_MWCR_MSK
#define SSI_RSVD_MWCR_W(X) ((X) << SSI_RSVD_MWCR_POS)

//SER offsetaddress : 0x10
#define SSI_SER_POS (0U)
#define SSI_SER_MSK \
    (0x1UL          \
     << SSI_SER_POS) /*!< Slave Select Enable Flag. Each bit in this register corresponds to a slave select line (ss_x_n) from the DWC_ssi master. When a bit in this register is set (1), the corresponding slave select line from the master is activated when a serial transfer begins. It should be noted that setting or clearing bits in this register have no effect on the corresponding slave select outputs until a transfer is started. Before beginning a transfer, you should enable the bit in this register that corresponds to the slave device with which the master wants to communicate. When not operating in broadcast mode, only one bit in this field should be set. ■ 1: Selected ■ 0: Not Selected Value After Reset: SSIC_DFLT_SLV Exists: Always Range Variable[x]: SSIC_NUM_SLAVES - 1*/
#define SSI_SER           SSI_SER_MSK
#define SSI_SER_W(X)      ((X) << SSI_SER_POS)
#define SSI_RSVD_SER_POS  (1U)
#define SSI_RSVD_SER_MSK  (0x7fffffffUL << SSI_RSVD_SER_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: SSIC_NUM_SLAVES*/
#define SSI_RSVD_SER      SSI_RSVD_SER_MSK
#define SSI_RSVD_SER_W(X) ((X) << SSI_RSVD_SER_POS)

//BAUDR offsetaddress : 0x14
#define SSI_SCKDV_POS (0U)
#define SSI_SCKDV_MSK \
    (0xffffUL         \
     << SSI_SCKDV_POS) /*!< SSI Clock Divider. The LSB for this field is always set to 0 and is unaffected by a write operation, which ensures an even value is held in this register. If the value is 0, the serial output clock (sclk_out) is disabled. The frequency of the sclk_out is derived from the following equation: Fsclk_out = Fssi_clk/SCKDV where SCKDV is any even value between 2 and 65534. For example: for Fssi_clk = 3.6864MHz and SCKDV =2 Fsclk_out = 3.6864/2 = 1.8432MHz Value After Reset: SSIC_DFLT_BAUDR Exists: Always*/
#define SSI_SCKDV           SSI_SCKDV_MSK
#define SSI_SCKDV_W(X)      ((X) << SSI_SCKDV_POS)
#define SSI_RSVD_BAUDR_POS  (16U)
#define SSI_RSVD_BAUDR_MSK  (0xffffUL << SSI_RSVD_BAUDR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_BAUDR      SSI_RSVD_BAUDR_MSK
#define SSI_RSVD_BAUDR_W(X) ((X) << SSI_RSVD_BAUDR_POS)

//TXFTLR offsetaddress : 0x18
#define SSI_TFT_POS (0U)
#define SSI_TFT_MSK \
    (0x1fUL         \
     << SSI_TFT_POS) /*!< Transmit FIFO Threshold. Controls the level of entries (or below) at which the transmit FIFO controller triggers an interrupt. The FIFO depth is configurable in the range 8-256; this register is sized to the number of address bits needed to access the FIFO. If you attempt to set this value greater than or equal to the depth of the FIFO, this field is not written and retains its current value. When the number of transmit FIFO entries is less than or equal to this value, the transmit FIFO empty interrupt is triggered. Value After Reset: 0x0 Exists: Always Range Variable[x]: TX_ABW - 1*/
#define SSI_TFT              SSI_TFT_MSK
#define SSI_TFT_W(X)         ((X) << SSI_TFT_POS)
#define SSI_RSVD_TXFTLR_POS  (5U)
#define SSI_RSVD_TXFTLR_MSK  (0x7ffUL << SSI_RSVD_TXFTLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: TX_ABW*/
#define SSI_RSVD_TXFTLR      SSI_RSVD_TXFTLR_MSK
#define SSI_RSVD_TXFTLR_W(X) ((X) << SSI_RSVD_TXFTLR_POS)
#define SSI_TXFTHR_POS       (16U)
#define SSI_TXFTHR_MSK \
    (0x1fUL            \
     << SSI_TXFTHR_POS) /*!< Transfer start FIFO level. Used to control the level of entries in transmit FIFO above which transfer will start on serial line. This register can be used to ensure that sufficient data is present in transmit FIFO before starting a write operation on serial line. These field is valid only for Master mode of operation. Value After Reset: 0x0 Exists: Always Range Variable[x]: TX_ABW + 15 Memory Access: "(SSIC_IS_MASTER==1) ? \"read-write\" : \"read-only\""*/
#define SSI_TXFTHR           SSI_TXFTHR_MSK
#define SSI_TXFTHR_W(X)      ((X) << SSI_TXFTHR_POS)
#define SSI_RSVD_TXFTHR_POS  (21U)
#define SSI_RSVD_TXFTHR_MSK  (0x7ffUL << SSI_RSVD_TXFTHR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: TX_ABW + 16*/
#define SSI_RSVD_TXFTHR      SSI_RSVD_TXFTHR_MSK
#define SSI_RSVD_TXFTHR_W(X) ((X) << SSI_RSVD_TXFTHR_POS)

//RXFTLR offsetaddress : 0x1c
#define SSI_RFT_POS (0U)
#define SSI_RFT_MSK \
    (0x1fUL         \
     << SSI_RFT_POS) /*!< Receive FIFO Threshold. Controls the level of entries (or above) at which the receive FIFO controller triggers an interrupt. The FIFO depth is configurable in the range 8-256. This register is sized to the number of address bits needed to access the FIFO. If you attempt to set this value greater than the depth of the FIFO, this field is not written and retains its current value. When the number of receive FIFO entries is greater than or equal to this value + 1, the receive FIFO full interrupt is triggered. Value After Reset: 0x0 Exists: Always Range Variable[x]: RX_ABW - 1*/
#define SSI_RFT              SSI_RFT_MSK
#define SSI_RFT_W(X)         ((X) << SSI_RFT_POS)
#define SSI_RSVD_RXFTLR_POS  (5U)
#define SSI_RSVD_RXFTLR_MSK  (0x7ffffffUL << SSI_RSVD_RXFTLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: RX_ABW*/
#define SSI_RSVD_RXFTLR      SSI_RSVD_RXFTLR_MSK
#define SSI_RSVD_RXFTLR_W(X) ((X) << SSI_RSVD_RXFTLR_POS)

//TXFLR offsetaddress : 0x20
#define SSI_TXTFL_POS       (0U)
#define SSI_TXTFL_MSK       (0x3fUL << SSI_TXTFL_POS) /*!< Transmit FIFO Level. Contains the number of valid data entries in the transmit FIFO. Value After Reset: 0x0 Exists: Always Volatile: true Range Variable[x]: TX_ABW*/
#define SSI_TXTFL           SSI_TXTFL_MSK
#define SSI_TXTFL_W(X)      ((X) << SSI_TXTFL_POS)
#define SSI_RSVD_TXFLR_POS  (6U)
#define SSI_RSVD_TXFLR_MSK  (0x3ffffffUL << SSI_RSVD_TXFLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true Range Variable[y]: TX_ABW + 1*/
#define SSI_RSVD_TXFLR      SSI_RSVD_TXFLR_MSK
#define SSI_RSVD_TXFLR_W(X) ((X) << SSI_RSVD_TXFLR_POS)

//RXFLR offsetaddress : 0x24
#define SSI_RXTFL_POS       (0U)
#define SSI_RXTFL_MSK       (0x3fUL << SSI_RXTFL_POS) /*!< Receive FIFO Level. Contains the number of valid data entries in the receive FIFO. Value After Reset: 0x0 Exists: Always Volatile: true Range Variable[x]: RX_ABW*/
#define SSI_RXTFL           SSI_RXTFL_MSK
#define SSI_RXTFL_W(X)      ((X) << SSI_RXTFL_POS)
#define SSI_RSVD_RXFLR_POS  (6U)
#define SSI_RSVD_RXFLR_MSK  (0x3ffffffUL << SSI_RSVD_RXFLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true Range Variable[y]: RX_ABW + 1*/
#define SSI_RSVD_RXFLR      SSI_RSVD_RXFLR_MSK
#define SSI_RSVD_RXFLR_W(X) ((X) << SSI_RSVD_RXFLR_POS)

//SR offsetaddress : 0x28
#define SSI_BUSY_POS (0U)
#define SSI_BUSY_MSK \
    (0x1UL           \
     << SSI_BUSY_POS) /*!< SSI Busy Flag. When set, indicates that a serial transfer is in progress; when cleared indicates that the DWC_ssi is idle or disabled. Values: ■ 0x1 (ACTIVE): DWC_ssi is actively transferring data ■ 0x0 (INACTIVE): DWC_ssi is idle or disabled Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_BUSY      SSI_BUSY_MSK
#define SSI_BUSY_W(X) ((X) << SSI_BUSY_POS)
#define SSI_TFNF_POS  (1U)
#define SSI_TFNF_MSK \
    (0x1UL << SSI_TFNF_POS) /*!< Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty locations, and is cleared when the FIFO is full. Values: ■ 0x1 (NOT_FULL): Tx FIFO is not Full ■ 0x0 (FULL): Tx FIFO is full Value After Reset: 0x1 Exists: Always Volatile: true*/
#define SSI_TFNF      SSI_TFNF_MSK
#define SSI_TFNF_W(X) ((X) << SSI_TFNF_POS)
#define SSI_TFE_POS   (2U)
#define SSI_TFE_MSK \
    (0x1UL          \
     << SSI_TFE_POS) /*!< Transmit FIFO Empty. When the transmit FIFO is completely empty, this bit is set. When the transmit FIFO contains one or more valid entries, this bit is cleared. This bit field does not request an interrupt. Values: ■ 0x1 (EMPTY): Transmit FIFO is empty ■ 0x0 (NOT_EMPTY): Transmit FIFO is not empty Value After Reset: 0x1 Exists: Always Volatile: true*/
#define SSI_TFE      SSI_TFE_MSK
#define SSI_TFE_W(X) ((X) << SSI_TFE_POS)
#define SSI_RFNE_POS (3U)
#define SSI_RFNE_MSK \
    (0x1UL           \
     << SSI_RFNE_POS) /*!< Receive FIFO Not Empty. Set when the receive FIFO contains one or more entries and is cleared when the receive FIFO is empty. This bit can be polled by software to completely empty the receive FIFO. Values: ■ 0x1 (NOT_EMPTY): Receive FIFO is not empty ■ 0x0 (EMPTY): Receive FIFO is empty Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RFNE      SSI_RFNE_MSK
#define SSI_RFNE_W(X) ((X) << SSI_RFNE_POS)
#define SSI_RFF_POS   (4U)
#define SSI_RFF_MSK \
    (0x1UL          \
     << SSI_RFF_POS) /*!< Receive FIFO Full. When the receive FIFO is completely full, this bit is set. When the receive FIFO contains one or more empty location, this bit is cleared. Values: ■ 0x1 (FULL): Receive FIFO is full ■ 0x0 (NOT_FULL): Receive FIFO is not full Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RFF      SSI_RFF_MSK
#define SSI_RFF_W(X) ((X) << SSI_RFF_POS)
#define SSI_TXE_POS  (5U)
#define SSI_TXE_MSK \
    (0x1UL          \
     << SSI_TXE_POS) /*!< Transmission Error. Set if the transmit FIFO is empty when a transfer is started. This bit can be set only when the DWC_ssi is configured as a slave device. Data from the previous transmission is resent on the txd line. This bit is cleared when read. Values: ■ 0x1 (TX_ERROR): Transmission Error ■ 0x0 (NO_ERROR): No Error Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_TXE      SSI_TXE_MSK
#define SSI_TXE_W(X) ((X) << SSI_TXE_POS)
#define SSI_DCOL_POS (6U)
#define SSI_DCOL_MSK \
    (0x1UL           \
     << SSI_DCOL_POS) /*!< Data Collision Error. Relevant only when the DWC_ssi is configured as a master device. This bit will be set if ss_in_n input is asserted by other master, when the DWC_ssi master is in the middle of the transfer. This informs the processor that the last data transfer was halted before completion. This bit is cleared when read. Values: ■ 0x1 (TX_COLLISION_ERROR): Transmit Data Collision Error ■ 0x0 (NO_ERROR_CONDITION): No Error Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_DCOL         SSI_DCOL_MSK
#define SSI_DCOL_W(X)    ((X) << SSI_DCOL_POS)
#define SSI_RSVD_SR_POS  (7U)
#define SSI_RSVD_SR_MSK  (0x1ffffffUL << SSI_RSVD_SR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_SR      SSI_RSVD_SR_MSK
#define SSI_RSVD_SR_W(X) ((X) << SSI_RSVD_SR_POS)

//IMR offsetaddress : 0x2c
#define SSI_TXEIM_POS  (0U)
#define SSI_TXEIM_MSK  (0x1UL << SSI_TXEIM_POS) /*!< Transmit FIFO Empty Interrupt Mask Values: ■ 0x1 (UNMASKED): ssi_txe_intr interrupt is not masked ■ 0x0 (MASKED): ssi_txe_intr interrupt is masked Value After Reset: 0x1 Exists: Always*/
#define SSI_TXEIM      SSI_TXEIM_MSK
#define SSI_TXEIM_W(X) ((X) << SSI_TXEIM_POS)
#define SSI_TXOIM_POS  (1U)
#define SSI_TXOIM_MSK  (0x1UL << SSI_TXOIM_POS) /*!< Transmit FIFO Overflow Interrupt Mask Values: ■ 0x1 (UNMASKED): ssi_txo_intr interrupt is not masked ■ 0x0 (MASKED): ssi_txo_intr interrupt is masked Value After Reset: 0x1 Exists: Always*/
#define SSI_TXOIM      SSI_TXOIM_MSK
#define SSI_TXOIM_W(X) ((X) << SSI_TXOIM_POS)
#define SSI_RXUIM_POS  (2U)
#define SSI_RXUIM_MSK  (0x1UL << SSI_RXUIM_POS) /*!< Receive FIFO Underflow Interrupt Mask Values: ■ 0x1 (UNMASKED): ssi_rxu_intr interrupt is not masked ■ 0x0 (MASKED): ssi_rxu_intr interrupt is masked Value After Reset: 0x1 Exists: Always*/
#define SSI_RXUIM      SSI_RXUIM_MSK
#define SSI_RXUIM_W(X) ((X) << SSI_RXUIM_POS)
#define SSI_RXOIM_POS  (3U)
#define SSI_RXOIM_MSK  (0x1UL << SSI_RXOIM_POS) /*!< Receive FIFO Overflow Interrupt Mask Values: ■ 0x1 (UNMASKED): ssi_rxo_intr interrupt is not masked ■ 0x0 (MASKED): ssi_rxo_intr interrupt is masked Value After Reset: 0x1 Exists: Always*/
#define SSI_RXOIM      SSI_RXOIM_MSK
#define SSI_RXOIM_W(X) ((X) << SSI_RXOIM_POS)
#define SSI_RXFIM_POS  (4U)
#define SSI_RXFIM_MSK \
    (0x1UL << SSI_RXFIM_POS) /*!< Receive FIFO Full Interrupt Mask 0 - ssi_rxf_intr interrupt is masked 1 - ssi_rxf_intr interrupt is not masked Values: ■ 0x1 (UNMASKED): ssi_rxf_intr interrupt is not masked ■ 0x0 (MASKED): ssi_rxf_intr interrupt is masked Value After Reset: 0x1 Exists: Always*/
#define SSI_RXFIM      SSI_RXFIM_MSK
#define SSI_RXFIM_W(X) ((X) << SSI_RXFIM_POS)
#define SSI_MSTIM_POS  (5U)
#define SSI_MSTIM_MSK \
    (0x1UL            \
     << SSI_MSTIM_POS) /*!< Multi-Master Contention Interrupt Mask. This bit field is not present if the DWC_ssi is configured as a serial-master device. Values: ■ 0x1 (UNMASKED): ssi_mst_intr interrupt is not masked ■ 0x0 (MASKED): ssi_mst_intr interrupt is masked Value After Reset: {(SSIC_IS_MASTER==1) ? 1 : 0} Exists: Always Memory Access: "(SSIC_IS_MASTER==1) ? \"read-write\" : \"read-only\""*/
#define SSI_MSTIM      SSI_MSTIM_MSK
#define SSI_MSTIM_W(X) ((X) << SSI_MSTIM_POS)
#define SSI_XRXOIM_POS (6U)
#define SSI_XRXOIM_MSK \
    (0x1UL             \
     << SSI_XRXOIM_POS) /*!< XIP Receive FIFO Overflow Interrupt Mask Values: ■ 0x1 (UNMASKED): ssi_xrxo_intr interrupt is not masked ■ 0x0 (MASKED): ssi_xrxo_intr interrupt is masked Value After Reset: {(SSIC_CONCURRENT_XIP_EN==1) ? 1 : 0} Exists: Always Memory Access: "(SSIC_CONCURRENT_XIP_EN==1) ? \"read-write\" : \"read-only\""*/
#define SSI_XRXOIM        SSI_XRXOIM_MSK
#define SSI_XRXOIM_W(X)   ((X) << SSI_XRXOIM_POS)
#define SSI_RSVD_IMR_POS  (7U)
#define SSI_RSVD_IMR_MSK  (0x1ffffffUL << SSI_RSVD_IMR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_IMR      SSI_RSVD_IMR_MSK
#define SSI_RSVD_IMR_W(X) ((X) << SSI_RSVD_IMR_POS)

//ISR offsetaddress : 0x30
#define SSI_TXEIS_POS  (0U)
#define SSI_TXEIS_MSK  (0x1UL << SSI_TXEIS_POS) /*!< Transmit FIFO Empty Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_txe_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_txe_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_TXEIS      SSI_TXEIS_MSK
#define SSI_TXEIS_W(X) ((X) << SSI_TXEIS_POS)
#define SSI_TXOIS_POS  (1U)
#define SSI_TXOIS_MSK  (0x1UL << SSI_TXOIS_POS) /*!< Transmit FIFO Overflow Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_txo_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_txo_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_TXOIS      SSI_TXOIS_MSK
#define SSI_TXOIS_W(X) ((X) << SSI_TXOIS_POS)
#define SSI_RXUIS_POS  (2U)
#define SSI_RXUIS_MSK  (0x1UL << SSI_RXUIS_POS) /*!< Receive FIFO Underflow Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxu_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_rxu_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXUIS      SSI_RXUIS_MSK
#define SSI_RXUIS_W(X) ((X) << SSI_RXUIS_POS)
#define SSI_RXOIS_POS  (3U)
#define SSI_RXOIS_MSK  (0x1UL << SSI_RXOIS_POS) /*!< Receive FIFO Overflow Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxo_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_rxo_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXOIS      SSI_RXOIS_MSK
#define SSI_RXOIS_W(X) ((X) << SSI_RXOIS_POS)
#define SSI_RXFIS_POS  (4U)
#define SSI_RXFIS_MSK  (0x1UL << SSI_RXFIS_POS) /*!< Receive FIFO Full Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxf_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_rxf_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXFIS      SSI_RXFIS_MSK
#define SSI_RXFIS_W(X) ((X) << SSI_RXFIS_POS)
#define SSI_MSTIS_POS  (5U)
#define SSI_MSTIS_MSK \
    (0x1UL            \
     << SSI_MSTIS_POS) /*!< Multi-Master Contention Interrupt Status. This bit field is not present if the DWC_ssi is configured as a serial-slave device. Values: ■ 0x1 (ACTIVE): ssi_mst_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_mst_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_MSTIS         SSI_MSTIS_MSK
#define SSI_MSTIS_W(X)    ((X) << SSI_MSTIS_POS)
#define SSI_XRXOIS_POS    (6U)
#define SSI_XRXOIS_MSK    (0x1UL << SSI_XRXOIS_POS) /*!< XIP Receive FIFO Overflow Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_xrxo_intr interrupt is active after masking ■ 0x0 (INACTIVE): ssi_xrxo_intr interrupt is not active after masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_XRXOIS        SSI_XRXOIS_MSK
#define SSI_XRXOIS_W(X)   ((X) << SSI_XRXOIS_POS)
#define SSI_RSVD_ISR_POS  (7U)
#define SSI_RSVD_ISR_MSK  (0x1ffffffUL << SSI_RSVD_ISR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_ISR      SSI_RSVD_ISR_MSK
#define SSI_RSVD_ISR_W(X) ((X) << SSI_RSVD_ISR_POS)

//RISR offsetaddress : 0x34
#define SSI_TXEIR_POS  (0U)
#define SSI_TXEIR_MSK  (0x1UL << SSI_TXEIR_POS) /*!< Transmit FIFO Empty Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_txe_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_txe_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_TXEIR      SSI_TXEIR_MSK
#define SSI_TXEIR_W(X) ((X) << SSI_TXEIR_POS)
#define SSI_TXOIR_POS  (1U)
#define SSI_TXOIR_MSK  (0x1UL << SSI_TXOIR_POS) /*!< Transmit FIFO Overflow Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_txo_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_txo_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_TXOIR      SSI_TXOIR_MSK
#define SSI_TXOIR_W(X) ((X) << SSI_TXOIR_POS)
#define SSI_RXUIR_POS  (2U)
#define SSI_RXUIR_MSK  (0x1UL << SSI_RXUIR_POS) /*!< Receive FIFO Underflow Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxu_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_rxu_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXUIR      SSI_RXUIR_MSK
#define SSI_RXUIR_W(X) ((X) << SSI_RXUIR_POS)
#define SSI_RXOIR_POS  (3U)
#define SSI_RXOIR_MSK  (0x1UL << SSI_RXOIR_POS) /*!< Receive FIFO Overflow Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxo_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_rxo_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXOIR      SSI_RXOIR_MSK
#define SSI_RXOIR_W(X) ((X) << SSI_RXOIR_POS)
#define SSI_RXFIR_POS  (4U)
#define SSI_RXFIR_MSK  (0x1UL << SSI_RXFIR_POS) /*!< Receive FIFO Full Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_rxf_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_rxf_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXFIR      SSI_RXFIR_MSK
#define SSI_RXFIR_W(X) ((X) << SSI_RXFIR_POS)
#define SSI_MSTIR_POS  (5U)
#define SSI_MSTIR_MSK \
    (0x1UL            \
     << SSI_MSTIR_POS) /*!< Multi-Master Contention Raw Interrupt Status. This bit field is not present if the DWC_ssi is configured as a serial-slave device. Values: ■ 0x1 (ACTIVE): ssi_mst_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_mst_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_MSTIR          SSI_MSTIR_MSK
#define SSI_MSTIR_W(X)     ((X) << SSI_MSTIR_POS)
#define SSI_XRXOIR_POS     (6U)
#define SSI_XRXOIR_MSK     (0x1UL << SSI_XRXOIR_POS) /*!< XIP Receive FIFO Overflow Raw Interrupt Status Values: ■ 0x1 (ACTIVE): ssi_xrxo_intr interrupt is active prior to masking ■ 0x0 (INACTIVE): ssi_xrxo_intr interrupt is not active prior masking Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_XRXOIR         SSI_XRXOIR_MSK
#define SSI_XRXOIR_W(X)    ((X) << SSI_XRXOIR_POS)
#define SSI_RSVD_RISR_POS  (7U)
#define SSI_RSVD_RISR_MSK  (0x1ffffffUL << SSI_RSVD_RISR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_RISR      SSI_RSVD_RISR_MSK
#define SSI_RSVD_RISR_W(X) ((X) << SSI_RSVD_RISR_POS)

//TXOICR offsetaddress : 0x38
#define SSI_TXOICR_POS       (0U)
#define SSI_TXOICR_MSK       (0x1UL << SSI_TXOICR_POS) /*!< Clear Transmit FIFO Overflow Interrupt. This register reflects the status of the interrupt. A read from this register clears the ssi_txo_intr interrupt; writing has no effect. Exists: Always Volatile: true*/
#define SSI_TXOICR           SSI_TXOICR_MSK
#define SSI_TXOICR_W(X)      ((X) << SSI_TXOICR_POS)
#define SSI_RSVD_TXOICR_POS  (1U)
#define SSI_RSVD_TXOICR_MSK  (0x7fffffffUL << SSI_RSVD_TXOICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_TXOICR      SSI_RSVD_TXOICR_MSK
#define SSI_RSVD_TXOICR_W(X) ((X) << SSI_RSVD_TXOICR_POS)

//RXOICR offsetaddress : 0x3c
#define SSI_RXOICR_POS       (0U)
#define SSI_RXOICR_MSK       (0x1UL << SSI_RXOICR_POS) /*!< Clear Receive FIFO Overflow Interrupt. This register reflects the status of the interrupt. A read from this register clears the ssi_rxo_intr interrupt; writing has no effect. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXOICR           SSI_RXOICR_MSK
#define SSI_RXOICR_W(X)      ((X) << SSI_RXOICR_POS)
#define SSI_RSVD_RXOICR_POS  (1U)
#define SSI_RSVD_RXOICR_MSK  (0x7fffffffUL << SSI_RSVD_RXOICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_RXOICR      SSI_RSVD_RXOICR_MSK
#define SSI_RSVD_RXOICR_W(X) ((X) << SSI_RSVD_RXOICR_POS)

//RXUICR offsetaddress : 0x40
#define SSI_RXUICR_POS       (0U)
#define SSI_RXUICR_MSK       (0x1UL << SSI_RXUICR_POS) /*!< Clear Receive FIFO Underflow Interrupt. This register reflects the status of the interrupt. A read from this register clears the ssi_rxu_intr interrupt; writing has no effect. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RXUICR           SSI_RXUICR_MSK
#define SSI_RXUICR_W(X)      ((X) << SSI_RXUICR_POS)
#define SSI_RSVD_RXUICR_POS  (1U)
#define SSI_RSVD_RXUICR_MSK  (0x7fffffffUL << SSI_RSVD_RXUICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_RXUICR      SSI_RSVD_RXUICR_MSK
#define SSI_RSVD_RXUICR_W(X) ((X) << SSI_RSVD_RXUICR_POS)

//MSTICR offsetaddress : 0x44
#define SSI_MSTICR_POS       (0U)
#define SSI_MSTICR_MSK       (0x1UL << SSI_MSTICR_POS) /*!< Clear Multi-Master Contention Interrupt. This register reflects the status of the interrupt. A read from this register clears the ssi_mst_intr interrupt; writing has no effect. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_MSTICR           SSI_MSTICR_MSK
#define SSI_MSTICR_W(X)      ((X) << SSI_MSTICR_POS)
#define SSI_RSVD_MSTICR_POS  (1U)
#define SSI_RSVD_MSTICR_MSK  (0x7fffffffUL << SSI_RSVD_MSTICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_MSTICR      SSI_RSVD_MSTICR_MSK
#define SSI_RSVD_MSTICR_W(X) ((X) << SSI_RSVD_MSTICR_POS)

//ICR offsetaddress : 0x48
#define SSI_ICR_POS (0U)
#define SSI_ICR_MSK \
    (0x1UL          \
     << SSI_ICR_POS) /*!< Clear Interrupts. This register is set if any of the interrupts below are active. A read clears the ssi_txo_intr, ssi_rxu_intr, ssi_rxo_intr, and the ssi_mst_intr interrupts. Writing to this register has no effect. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_ICR           SSI_ICR_MSK
#define SSI_ICR_W(X)      ((X) << SSI_ICR_POS)
#define SSI_RSVD_ICR_POS  (1U)
#define SSI_RSVD_ICR_MSK  (0x7fffffffUL << SSI_RSVD_ICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_ICR      SSI_RSVD_ICR_MSK
#define SSI_RSVD_ICR_W(X) ((X) << SSI_RSVD_ICR_POS)

//DMACR offsetaddress : 0x4c
#define SSI_RDMAE_POS       (0U)
#define SSI_RDMAE_MSK       (0x1UL << SSI_RDMAE_POS) /*!< Receive DMA Enable. This bit enables/disables the receive FIFO DMA channel. Values: ■ 0x1 (ENABLED): Receive DMA enabled ■ 0x0 (DISABLE): Receive DMA disabled Value After Reset: 0x0 Exists: Always*/
#define SSI_RDMAE           SSI_RDMAE_MSK
#define SSI_RDMAE_W(X)      ((X) << SSI_RDMAE_POS)
#define SSI_TDMAE_POS       (1U)
#define SSI_TDMAE_MSK       (0x1UL << SSI_TDMAE_POS) /*!< Transmit DMA Enable. This bit enables/disables the transmit FIFO DMA channel. Values: ■ 0x1 (ENABLED): Transmit DMA enabled ■ 0x0 (DISABLE): Transmit DMA disabled Value After Reset: 0x0 Exists: Always*/
#define SSI_TDMAE           SSI_TDMAE_MSK
#define SSI_TDMAE_W(X)      ((X) << SSI_TDMAE_POS)
#define SSI_RSVD_DMACR_POS  (2U)
#define SSI_RSVD_DMACR_MSK  (0x3fffffffUL << SSI_RSVD_DMACR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_DMACR      SSI_RSVD_DMACR_MSK
#define SSI_RSVD_DMACR_W(X) ((X) << SSI_RSVD_DMACR_POS)

//DMATDLR offsetaddress : 0x50
#define SSI_DMATDL_POS (0U)
#define SSI_DMATDL_MSK \
    (0x1fUL            \
     << SSI_DMATDL_POS) /*!< Transmit Data Level. This bit field controls the level at which a DMA request is made by the transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to or below this field value, and TDMAE = 1. Value After Reset: 0x0 Exists: Always Range Variable[x]: TX_ABW - 1*/
#define SSI_DMATDL            SSI_DMATDL_MSK
#define SSI_DMATDL_W(X)       ((X) << SSI_DMATDL_POS)
#define SSI_RSVD_DMATDLR_POS  (5U)
#define SSI_RSVD_DMATDLR_MSK  (0x7ffffffUL << SSI_RSVD_DMATDLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: TX_ABW*/
#define SSI_RSVD_DMATDLR      SSI_RSVD_DMATDLR_MSK
#define SSI_RSVD_DMATDLR_W(X) ((X) << SSI_RSVD_DMATDLR_POS)

//DMARDLR offsetaddress : 0x54
#define SSI_DMARDL_POS (0U)
#define SSI_DMARDL_MSK \
    (0x1fUL            \
     << SSI_DMARDL_POS) /*!< Receive Data Level. This bit field controls the level at which a DMA request is made by the receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal to or above this field value + 1, and RDMAE=1. Value After Reset: 0x0 Exists: Always Range Variable[x]: RX_ABW - 1*/
#define SSI_DMARDL            SSI_DMARDL_MSK
#define SSI_DMARDL_W(X)       ((X) << SSI_DMARDL_POS)
#define SSI_RSVD_DMARDLR_POS  (5U)
#define SSI_RSVD_DMARDLR_MSK  (0x7ffffffUL << SSI_RSVD_DMARDLR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Range Variable[y]: RX_ABW*/
#define SSI_RSVD_DMARDLR      SSI_RSVD_DMARDLR_MSK
#define SSI_RSVD_DMARDLR_W(X) ((X) << SSI_RSVD_DMARDLR_POS)

//IDR offsetaddress : 0x58
#define SSI_IDCODE_POS  (0U)
#define SSI_IDCODE_MSK  (0xffffffffUL << SSI_IDCODE_POS) /*!< Identification code. The register contains the peripheral's identification code, which is written into the register at configuration time using CoreConsultant. Value After Reset: SSIC_ID Exists: Always*/
#define SSI_IDCODE      SSI_IDCODE_MSK
#define SSI_IDCODE_W(X) ((X) << SSI_IDCODE_POS)

//SSIC_VERSION_ID offsetaddress : 0x5c
#define SSI_SSIC_COMP_VERSION_POS (0U)
#define SSI_SSIC_COMP_VERSION_MSK \
    (0xffffffffUL << SSI_SSIC_COMP_VERSION_POS) /*!< Contains the hex representation of the Synopsys component version. Consists of ASCII value for each number in the version, followed by *. For example 32_30_31_2A represents the version 2.01*. Value After Reset: SSIC_VERSION_ID Exists: Always*/
#define SSI_SSIC_COMP_VERSION      SSI_SSIC_COMP_VERSION_MSK
#define SSI_SSIC_COMP_VERSION_W(X) ((X) << SSI_SSIC_COMP_VERSION_POS)

//DRx offsetaddress : 0x60 +i*0x4
#define SSI_DR_POS  (0U)
#define SSI_DR_MSK  (0xffffffffUL << SSI_DR_POS) /*!< Data Register. When writing to this register, you must right- justify the data. Read data are automatically right-justified. Read = Receive FIFO buffer Write = Transmit FIFO buffer. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_DR      SSI_DR_MSK
#define SSI_DR_W(X) ((X) << SSI_DR_POS)

//RX_SAMPLE_DELAY offsetaddress : 0xf0
#define SSI_RSD_POS (0U)
#define SSI_RSD_MSK \
    (0xffUL         \
     << SSI_RSD_POS) /*!< Receive Data (rxd) Sample Delay. This register is used to delay the sample of the rxd input port. Each value represents a single ssi_clk delay on the sample of rxd. Note; If this register is programmed with a value that exceeds the depth of the internal shift registers (SSIC_RX_DLY_SR_DEPTH) zero delay will be applied to the rxd sample. Value After Reset: 0x0 Exists: Always*/
#define SSI_RSD                      SSI_RSD_MSK
#define SSI_RSD_W(X)                 ((X) << SSI_RSD_POS)
#define SSI_RSVD0_RX_SAMPLE_DLY_POS  (8U)
#define SSI_RSVD0_RX_SAMPLE_DLY_MSK  (0xffUL << SSI_RSVD0_RX_SAMPLE_DLY_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD0_RX_SAMPLE_DLY      SSI_RSVD0_RX_SAMPLE_DLY_MSK
#define SSI_RSVD0_RX_SAMPLE_DLY_W(X) ((X) << SSI_RSVD0_RX_SAMPLE_DLY_POS)
#define SSI_SE_POS                   (16U)
#define SSI_SE_MSK \
    (0x1UL         \
     << SSI_SE_POS) /*!< Receive Data (rxd) Sampling Edge. This register is used to decide the sampling edge for RXD signal with ssi_clk. Then this bit is set to 1 then negative edge of ssi_clk will be used to sample the incoming data, otherwise positive edge will be used for sampling. Value After Reset: 0x0 Exists: Always Memory Access: "(SSIC_HAS_RX_SAMPLE_DELAY==2) ? \"read-write\" : \"read-only\""*/
#define SSI_SE                       SSI_SE_MSK
#define SSI_SE_W(X)                  ((X) << SSI_SE_POS)
#define SSI_RSVD1_RX_SAMPLE_DLY_POS  (17U)
#define SSI_RSVD1_RX_SAMPLE_DLY_MSK  (0x7fffUL << SSI_RSVD1_RX_SAMPLE_DLY_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD1_RX_SAMPLE_DLY      SSI_RSVD1_RX_SAMPLE_DLY_MSK
#define SSI_RSVD1_RX_SAMPLE_DLY_W(X) ((X) << SSI_RSVD1_RX_SAMPLE_DLY_POS)

//SPI_CTRLR0 offsetaddress : 0xf4
#define SSI_TRANS_TYPE_POS (0U)
#define SSI_TRANS_TYPE_MSK \
    (0x3UL                 \
     << SSI_TRANS_TYPE_POS) /*!< Address and instruction transfer format. Selects whether DWC_ssi will transmit instruction/address either in Standard SPI mode or the SPI mode selected in CTRLR0.SPI_FRF field. Values: ■ 0x0 (TT0): Instruction and Address will be sent in Standard SPI Mode. ■ 0x1 (TT1): Instruction will be sent in Standard SPI Mode and Address will be sent in the mode specified by CTRLR0.SPI_FRF. ■ 0x2 (TT2): Both Instruction and Address will be sent in the mode specified by SPI_FRF. ■ 0x3 (TT3): Reserved. Value After Reset: SSIC_DFLT_TRANS_TYPE Exists: Always*/
#define SSI_TRANS_TYPE      SSI_TRANS_TYPE_MSK
#define SSI_TRANS_TYPE_W(X) ((X) << SSI_TRANS_TYPE_POS)
#define SSI_ADDR_L_POS      (2U)
#define SSI_ADDR_L_MSK \
    (0xfUL             \
     << SSI_ADDR_L_POS) /*!< This bit defines Length of Address to be transmitted. Only after this much bits are programmed in to the FIFO the transfer can begin. Values: ■ 0x0 (ADDR_L0): No Address ■ 0x1 (ADDR_L4): 4 bit Address length ■ 0x2 (ADDR_L8): 8 bit Address length ■ 0x3 (ADDR_L12): 12 bit Address length ■ 0x4 (ADDR_L16): 16 bit Address length ■ 0x5 (ADDR_L20): 20 bit Address length ■ 0x6 (ADDR_L24): 24 bit Address length ■ 0x7 (ADDR_L28): 28 bit Address length ■ 0x8 (ADDR_L32): 32 bit Address length ■ 0x9 (ADDR_L36): 36 bit Address length ■ 0xa (ADDR_L40): 40 bit Address length ■ 0xb (ADDR_L44): 44 bit Address length ■ 0xc (ADDR_L48): 48 bit Address length ■ 0xd (ADDR_L52): 52 bit Address length ■ 0xe (ADDR_L56): 56 bit Address length ■ 0xf (ADDR_L60): 60 bit Address length Value After Reset: SSIC_DFLT_ADDR_L Exists: Always*/
#define SSI_ADDR_L                 SSI_ADDR_L_MSK
#define SSI_ADDR_L_W(X)            ((X) << SSI_ADDR_L_POS)
#define SSI_RSVD_SPI_CTRLR0_6_POS  (6U)
#define SSI_RSVD_SPI_CTRLR0_6_MSK  (0x1UL << SSI_RSVD_SPI_CTRLR0_6_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0_6      SSI_RSVD_SPI_CTRLR0_6_MSK
#define SSI_RSVD_SPI_CTRLR0_6_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_6_POS)
#define SSI_XIP_MD_BIT_EN_POS      (7U)
#define SSI_XIP_MD_BIT_EN_MSK \
    (0x1UL                    \
     << SSI_XIP_MD_BIT_EN_POS) /*!< Mode bits enable in XIP mode. If this bit is set to 1, then in XIP mode of operation DWC_ssi will insert mode bits after the address phase. These bits are set in register XIP_MODE_BITS register. The length of mode bits is always set to 8 bits. Value After Reset: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_MD_BITS_EN\"" Exists: Always Memory Access: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_XIP_MD_BIT_EN      SSI_XIP_MD_BIT_EN_MSK
#define SSI_XIP_MD_BIT_EN_W(X) ((X) << SSI_XIP_MD_BIT_EN_POS)
#define SSI_INST_L_POS         (8U)
#define SSI_INST_L_MSK \
    (0x3UL             \
     << SSI_INST_L_POS) /*!< Dual/Quad/Octal mode instruction length in bits. Values: ■ 0x0 (INST_L0): No Instruction ■ 0x1 (INST_L4): 4 bit Instruction length ■ 0x2 (INST_L8): 8 bit Instruction length ■ 0x3 (INST_L16): 16 bit Instruction length Value After Reset: SSIC_DFLT_INST_L Exists: Always*/
#define SSI_INST_L                  SSI_INST_L_MSK
#define SSI_INST_L_W(X)             ((X) << SSI_INST_L_POS)
#define SSI_RSVD_SPI_CTRLR0_10_POS  (10U)
#define SSI_RSVD_SPI_CTRLR0_10_MSK  (0x1UL << SSI_RSVD_SPI_CTRLR0_10_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0_10      SSI_RSVD_SPI_CTRLR0_10_MSK
#define SSI_RSVD_SPI_CTRLR0_10_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_10_POS)
#define SSI_WAIT_CYCLES_POS         (11U)
#define SSI_WAIT_CYCLES_MSK         (0x1fUL << SSI_WAIT_CYCLES_POS) /*!< Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles. Value After Reset: SSIC_DFLT_WAIT_CYCLES Exists: Always*/
#define SSI_WAIT_CYCLES             SSI_WAIT_CYCLES_MSK
#define SSI_WAIT_CYCLES_W(X)        ((X) << SSI_WAIT_CYCLES_POS)
#define SSI_SPI_DDR_EN_POS          (16U)
#define SSI_SPI_DDR_EN_MSK          (0x1UL << SSI_SPI_DDR_EN_POS) /*!< SPI DDR Enable bit. This will enable Dual-data rate transfers in Dual/Quad/Octal frame formats of SPI. Value After Reset: SSIC_DFLT_DDR_EN Exists: Always Memory Access: "(SSIC_HAS_DDR==0) ? \"read-only\": \"read-write\""*/
#define SSI_SPI_DDR_EN              SSI_SPI_DDR_EN_MSK
#define SSI_SPI_DDR_EN_W(X)         ((X) << SSI_SPI_DDR_EN_POS)
#define SSI_INST_DDR_EN_POS         (17U)
#define SSI_INST_DDR_EN_MSK         (0x1UL << SSI_INST_DDR_EN_POS) /*!< Instruction DDR Enable bit. This will enable Dual-data rate transfer for Instruction phase. Value After Reset: SSIC_DFLT_INST_DDR_EN Exists: Always Memory Access: "(SSIC_HAS_DDR==0) ? \"read-only\": \"read-write\""*/
#define SSI_INST_DDR_EN             SSI_INST_DDR_EN_MSK
#define SSI_INST_DDR_EN_W(X)        ((X) << SSI_INST_DDR_EN_POS)
#define SSI_SPI_RXDS_EN_POS         (18U)
#define SSI_SPI_RXDS_EN_MSK \
    (0x1UL << SSI_SPI_RXDS_EN_POS) /*!< Read data strobe enable bit. Once this bit is set to 1 DWC_ssi will use Read data strobe (rxds) to capture read data in DDR mode. Value After Reset: SSIC_DFLT_RXDS_EN Exists: Always Memory Access: "(SSIC_HAS_RXDS==0) ? \"read-only\": \"read-write\""*/
#define SSI_SPI_RXDS_EN      SSI_SPI_RXDS_EN_MSK
#define SSI_SPI_RXDS_EN_W(X) ((X) << SSI_SPI_RXDS_EN_POS)
#define SSI_XIP_DFS_HC_POS   (19U)
#define SSI_XIP_DFS_HC_MSK \
    (0x1UL                 \
     << SSI_XIP_DFS_HC_POS) /*!< Fix DFS for XIP transfers. If this bit is set to 1 then data frame size for XIP transfers will be fixed to the programmed value in CTRLR0.DFS. The number of data frames to fetch will be determined by HSIZE and HBURST signals. If this bit is set to 0 then data frame size and number of data frames to fetch will be determined by HSIZE and HBURST signals Value After Reset: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_DFS_HC\"" Exists: Always Memory Access: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_XIP_DFS_HC      SSI_XIP_DFS_HC_MSK
#define SSI_XIP_DFS_HC_W(X) ((X) << SSI_XIP_DFS_HC_POS)
#define SSI_XIP_INST_EN_POS (20U)
#define SSI_XIP_INST_EN_MSK \
    (0x1UL                  \
     << SSI_XIP_INST_EN_POS) /*!< XIP instruction enable bit. If this bit is set to 1 then XIP transfers will also have instruction phase. The instruction op- codes will be chosen from XIP_INCR_INST or XIP_WRAP_INST registers bases on AHB transfer type. Value After Reset: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_XIP_INST_EN\"" Exists: Always Memory Access: "(SSIC_XIP_INST_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_XIP_INST_EN               SSI_XIP_INST_EN_MSK
#define SSI_XIP_INST_EN_W(X)          ((X) << SSI_XIP_INST_EN_POS)
#define SSI_SSIC_XIP_CONT_XFER_EN_POS (21U)
#define SSI_SSIC_XIP_CONT_XFER_EN_MSK \
    (0x1UL                            \
     << SSI_SSIC_XIP_CONT_XFER_EN_POS) /*!< Enable continuous transfer in XIP mode. If this bit is set to 1 then continuous transfer mode in XIP will be enabled, in this mode DWC_ssi will keep slave selected until a non-XIP transfer is detected on the AHB interface. Value After Reset: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_XIP_CONT_XFER_EN\"" Exists: Always Memory Access: "(SSIC_XIP_CONT_XFER_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_SSIC_XIP_CONT_XFER_EN      SSI_SSIC_XIP_CONT_XFER_EN_MSK
#define SSI_SSIC_XIP_CONT_XFER_EN_W(X) ((X) << SSI_SSIC_XIP_CONT_XFER_EN_POS)
#define SSI_RSVD_SPI_CTRLR0_22_23_POS  (22U)
#define SSI_RSVD_SPI_CTRLR0_22_23_MSK  (0x3UL << SSI_RSVD_SPI_CTRLR0_22_23_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0_22_23      SSI_RSVD_SPI_CTRLR0_22_23_MSK
#define SSI_RSVD_SPI_CTRLR0_22_23_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_22_23_POS)
#define SSI_SPI_DM_EN_POS              (24U)
#define SSI_SPI_DM_EN_MSK \
    (0x1UL                \
     << SSI_SPI_DM_EN_POS) /*!< SPI data mask enable bit. When this bit is enabled, the txd_dm signal is used to mask the data on the txd data line. This bit is enabled only when the SSIC_DM_EN parameter is set to 1. Value After Reset: SSIC_DFLT_DM_EN Exists: Always Memory Access: "(SSIC_SPI_DM_EN==0) ? \"read-only\": \"read-write\""*/
#define SSI_SPI_DM_EN           SSI_SPI_DM_EN_MSK
#define SSI_SPI_DM_EN_W(X)      ((X) << SSI_SPI_DM_EN_POS)
#define SSI_SPI_RXDS_SIG_EN_POS (25U)
#define SSI_SPI_RXDS_SIG_EN_MSK \
    (0x1UL                      \
     << SSI_SPI_RXDS_SIG_EN_POS) /*!< Enable rxds signaling during address and command phase of Hypebus transfer. This bit enables rxds signaling by Hyperbus slave devices during Command-Address (CA) phase. If the rxds signal is set to 1 during the CA phase of transfer, DWC_ssi transmits (2*SPI_CTRLR0.WAIT_CYCLES-1) wait cycles after the address phase is complete. Value After Reset: SSIC_DFLT_RXDS_SIG_EN Exists: Always Memory Access: "(SSIC_HYPERBUS_EN==0) ? \"read- only\": \"read-write\""*/
#define SSI_SPI_RXDS_SIG_EN      SSI_SPI_RXDS_SIG_EN_MSK
#define SSI_SPI_RXDS_SIG_EN_W(X) ((X) << SSI_SPI_RXDS_SIG_EN_POS)
#define SSI_XIP_MBL_POS          (26U)
#define SSI_XIP_MBL_MSK \
    (0x3UL              \
     << SSI_XIP_MBL_POS) /*!< XIP Mode bits length. Sets the length of mode bits in XIP mode of operation. These bits are valid only when SPI_CTRLR0.XIP_MD_BIT_EN is set to 1. Values: ■ 0x0 (MBL_2): Mode bits length equal to 2 ■ 0x1 (MBL_4): Mode bits length equal to 4 ■ 0x2 (MBL_8): Mode bits length equal to 8 ■ 0x3 (MBL_16): Mode bits length equal to 16 Value After Reset: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_XIP_MBL\"" Exists: Always Memory Access: "(SSIC_XIP_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_XIP_MBL                 SSI_XIP_MBL_MSK
#define SSI_XIP_MBL_W(X)            ((X) << SSI_XIP_MBL_POS)
#define SSI_RSVD_SPI_CTRLR0_28_POS  (28U)
#define SSI_RSVD_SPI_CTRLR0_28_MSK  (0x1UL << SSI_RSVD_SPI_CTRLR0_28_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0_28      SSI_RSVD_SPI_CTRLR0_28_MSK
#define SSI_RSVD_SPI_CTRLR0_28_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_28_POS)
#define SSI_XIP_PREFETCH_EN_POS     (29U)
#define SSI_XIP_PREFETCH_EN_MSK \
    (0x1UL                      \
     << SSI_XIP_PREFETCH_EN_POS) /*!< Enables XIP pre-fetch functionality in DWC_ssi. Once enabled DWC_ssi will pre-fetch data frames from next contigous location, to reduce the latency for the upcoming contiguous transfer. If the next XIP request is not contigous then pre-fetched bits will be discarded. Value After Reset: "(SSIC_XIP_PREFETCH_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"0x0\": \"SSIC_DFLT_XIP_PREFETCH\"" Exists: Always Memory Access: "(SSIC_XIP_PREFETCH_EN==0 || SSIC_CONCURRENT_XIP_EN==1) ? \"read-only\": \"read- write\""*/
#define SSI_XIP_PREFETCH_EN      SSI_XIP_PREFETCH_EN_MSK
#define SSI_XIP_PREFETCH_EN_W(X) ((X) << SSI_XIP_PREFETCH_EN_POS)
#define SSI_CLK_STRETCH_EN_POS   (30U)
#define SSI_CLK_STRETCH_EN_MSK \
    (0x1UL                     \
     << SSI_CLK_STRETCH_EN_POS) /*!< Enables clock stretching capability in SPI transfers. In case of write, if the FIFO becomes empty DWC_ssi will stretch the clock until FIFO has enough data to continue the transfer. In case of read, if the receive FIFO becomes full DWC_ssi will stop the clock until data has been read from the FIFO. Value After Reset: "(SSIC_CLK_STRETCH_EN==0) ? \"0x0\": \"SSIC_DFLT_CLK_STRETCH\"" Exists: Always Memory Access: "(SSIC_CLK_STRETCH_EN==0) ? \"read-only\": \"read-write\""*/
#define SSI_CLK_STRETCH_EN       SSI_CLK_STRETCH_EN_MSK
#define SSI_CLK_STRETCH_EN_W(X)  ((X) << SSI_CLK_STRETCH_EN_POS)
#define SSI_RSVD_SPI_CTRLR0_POS  (31U)
#define SSI_RSVD_SPI_CTRLR0_MSK  (0x1UL << SSI_RSVD_SPI_CTRLR0_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0      SSI_RSVD_SPI_CTRLR0_MSK
#define SSI_RSVD_SPI_CTRLR0_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_POS)

//DDR_DRIVE_EDGE offsetaddress : 0xf8
#define SSI_TDE_POS                  (0U)
#define SSI_TDE_MSK                  (0xffUL << SSI_TDE_POS) /*!< TXD Drive edge register which decided the driving edge of transmit data. The maximum value of this register is = (BAUDR/2) -1. Value After Reset: 0x0 Exists: Always*/
#define SSI_TDE                      SSI_TDE_MSK
#define SSI_TDE_W(X)                 ((X) << SSI_TDE_POS)
#define SSI_RSVD_DDR_DRIVE_EDGE_POS  (8U)
#define SSI_RSVD_DDR_DRIVE_EDGE_MSK  (0xffffffUL << SSI_RSVD_DDR_DRIVE_EDGE_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_DDR_DRIVE_EDGE      SSI_RSVD_DDR_DRIVE_EDGE_MSK
#define SSI_RSVD_DDR_DRIVE_EDGE_W(X) ((X) << SSI_RSVD_DDR_DRIVE_EDGE_POS)

//XIP_MODE_BITS offsetaddress : 0xfc
#define SSI_XIP_MD_BITS_POS       (0U)
#define SSI_XIP_MD_BITS_MSK       (0xffffUL << SSI_XIP_MD_BITS_POS) /*!< XIP mode bits to be sent after address phase of XIP transfer. Value After Reset: SSIC_DFLT_MD_BITS Exists: Always Volatile: true*/
#define SSI_XIP_MD_BITS           SSI_XIP_MD_BITS_MSK
#define SSI_XIP_MD_BITS_W(X)      ((X) << SSI_XIP_MD_BITS_POS)
#define SSI_RSVD_XIP_MD_BITS_POS  (16U)
#define SSI_RSVD_XIP_MD_BITS_MSK  (0xffffUL << SSI_RSVD_XIP_MD_BITS_POS) /*!< Reserved bits Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_XIP_MD_BITS      SSI_RSVD_XIP_MD_BITS_MSK
#define SSI_RSVD_XIP_MD_BITS_W(X) ((X) << SSI_RSVD_XIP_MD_BITS_POS)

//XIP_INCR_INST offsetaddress : 0x100
#define SSI_INCR_INST_POS (0U)
#define SSI_INCR_INST_MSK \
    (0xffffUL             \
     << SSI_INCR_INST_POS) /*!< XIP INCR transfer opcode. When SPI_CTRLR0.XIP_INST_EN bit is set to 1, DWC_ssi sends instruction for all XIP transfers, this register field stores the instruction op-code to be sent when an INCR type transfer is requested on AHB bus. The number of bits to be send in instruction phase is determined by SPI_CTRL0.INST_L field. Value After Reset: SSIC_DFLT_INCR_INST Exists: Always*/
#define SSI_INCR_INST           SSI_INCR_INST_MSK
#define SSI_INCR_INST_W(X)      ((X) << SSI_INCR_INST_POS)
#define SSI_RSVD_INCR_INST_POS  (16U)
#define SSI_RSVD_INCR_INST_MSK  (0xffffUL << SSI_RSVD_INCR_INST_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_INCR_INST      SSI_RSVD_INCR_INST_MSK
#define SSI_RSVD_INCR_INST_W(X) ((X) << SSI_RSVD_INCR_INST_POS)

//XIP_WRAP_INST offsetaddress : 0x104
#define SSI_WRAP_INST_POS (0U)
#define SSI_WRAP_INST_MSK \
    (0xffffUL             \
     << SSI_WRAP_INST_POS) /*!< XIP WRAP transfer opcode. When SPI_CTRLR0.XIP_INST_EN bit is set to 1, DWC_ssi sends instruction for all XIP transfers, this register field stores the instruction op-code to be sent when an WRAP type transfer is requested on AHB bus. The number of bits to be send in instruction phase is determined by SPI_CTRL0.INST_L field. Value After Reset: SSIC_DFLT_WRAP_INST Exists: Always*/
#define SSI_WRAP_INST           SSI_WRAP_INST_MSK
#define SSI_WRAP_INST_W(X)      ((X) << SSI_WRAP_INST_POS)
#define SSI_RSVD_WRAP_INST_POS  (16U)
#define SSI_RSVD_WRAP_INST_MSK  (0xffffUL << SSI_RSVD_WRAP_INST_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_WRAP_INST      SSI_RSVD_WRAP_INST_MSK
#define SSI_RSVD_WRAP_INST_W(X) ((X) << SSI_RSVD_WRAP_INST_POS)

//XIP_CTRL offsetaddress : 0x108
#define SSI_FRF_XIP_CTRL_POS (0U)
#define SSI_FRF_XIP_CTRL_MSK \
    (0x3UL                   \
     << SSI_FRF_XIP_CTRL_POS) /*!< SPI Frame Format Selects data frame format for Transmitting/Receiving the data. Values: ■ 0x0 (RSVD): Reserved ■ 0x1 (SPI_DUAL): Dual SPI Format ■ 0x2 (SPI_QUAD): Quad SPI Format ■ 0x3 (SPI_OCTAL): Octal SPI Format Value After Reset: SSIC_DFLT_XIP_SPI_FRF Exists: Always*/
#define SSI_FRF_XIP_CTRL            SSI_FRF_XIP_CTRL_MSK
#define SSI_FRF_XIP_CTRL_W(X)       ((X) << SSI_FRF_XIP_CTRL_POS)
#define SSI_TRANS_TYPE_XIP_CTRL_POS (2U)
#define SSI_TRANS_TYPE_XIP_CTRL_MSK \
    (0x3UL                          \
     << SSI_TRANS_TYPE_XIP_CTRL_POS) /*!< Address and instruction transfer format. Selects whether DWC_ssi will transmit instruction/address either in Standard SPI mode or the SPI mode selected in CTRLR0.SPI_FRF field. Values: ■ 0x0 (TT0): Instruction and Address will be sent in Standard SPI Mode. ■ 0x1 (TT1): Instruction will be sent in Standard SPI Mode and Address will be sent in the mode specified by XIP_CTRL.SPI_FRF. ■ 0x2 (TT2): Both Instruction and Address will be sent in the mode specified by XIP_CTRL.SPI_FRF. ■ 0x3 (TT3): Reserved. Value After Reset: SSIC_DFLT_XIP_TRANS_TYPE Exists: Always*/
#define SSI_TRANS_TYPE_XIP_CTRL      SSI_TRANS_TYPE_XIP_CTRL_MSK
#define SSI_TRANS_TYPE_XIP_CTRL_W(X) ((X) << SSI_TRANS_TYPE_XIP_CTRL_POS)
#define SSI_ADDR_L_XIP_CTRL_POS      (4U)
#define SSI_ADDR_L_XIP_CTRL_MSK \
    (0xfUL                      \
     << SSI_ADDR_L_XIP_CTRL_POS) /*!< This bit defines Length of Address to be transmitted. Only after this much bits are programmed in to the FIFO the transfer can begin. Values: ■ 0x0 (ADDR_L0): No Address ■ 0x1 (ADDR_L4): 4 bit Address length ■ 0x2 (ADDR_L8): 8 bit Address length ■ 0x3 (ADDR_L12): 12 bit Address length ■ 0x4 (ADDR_L16): 16 bit Address length ■ 0x5 (ADDR_L20): 20 bit Address length ■ 0x6 (ADDR_L24): 24 bit Address length ■ 0x7 (ADDR_L28): 28 bit Address length ■ 0x8 (ADDR_L32): 32 bit Address length ■ 0x9 (ADDR_L36): 36 bit Address length ■ 0xa (ADDR_L40): 40 bit Address length ■ 0xb (ADDR_L44): 44 bit Address length ■ 0xc (ADDR_L48): 48 bit Address length ■ 0xd (ADDR_L52): 52 bit Address length ■ 0xe (ADDR_L56): 56 bit Address length ■ 0xf (ADDR_L60): 60 bit Address length Value After Reset: SSIC_DFLT_XIP_ADDR_L Exists: Always*/
#define SSI_ADDR_L_XIP_CTRL      SSI_ADDR_L_XIP_CTRL_MSK
#define SSI_ADDR_L_XIP_CTRL_W(X) ((X) << SSI_ADDR_L_XIP_CTRL_POS)
#define SSI_RSVD_XIP_CTRL_8_POS  (8U)
#define SSI_RSVD_XIP_CTRL_8_MSK  (0x1UL << SSI_RSVD_XIP_CTRL_8_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_XIP_CTRL_8      SSI_RSVD_XIP_CTRL_8_MSK
#define SSI_RSVD_XIP_CTRL_8_W(X) ((X) << SSI_RSVD_XIP_CTRL_8_POS)
#define SSI_INST_L_XIP_CTRL_POS  (9U)
#define SSI_INST_L_XIP_CTRL_MSK \
    (0x3UL                      \
     << SSI_INST_L_XIP_CTRL_POS) /*!< Dual/Quad/Octal mode instruction length in bits. Values: ■ 0x0 (INST_L0): No Instruction ■ 0x1 (INST_L4): 4 bit Instruction length ■ 0x2 (INST_L8): 8 bit Instruction length ■ 0x3 (INST_L16): 16 bit Instruction length Value After Reset: SSIC_DFLT_XIP_INST_L Exists: Always*/
#define SSI_INST_L_XIP_CTRL         SSI_INST_L_XIP_CTRL_MSK
#define SSI_INST_L_XIP_CTRL_W(X)    ((X) << SSI_INST_L_XIP_CTRL_POS)
#define SSI_RSVD_SPI_CTRLR0_11_POS  (11U)
#define SSI_RSVD_SPI_CTRLR0_11_MSK  (0x1UL << SSI_RSVD_SPI_CTRLR0_11_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_SPI_CTRLR0_11      SSI_RSVD_SPI_CTRLR0_11_MSK
#define SSI_RSVD_SPI_CTRLR0_11_W(X) ((X) << SSI_RSVD_SPI_CTRLR0_11_POS)
#define SSI_MD_BITS_EN_POS          (12U)
#define SSI_MD_BITS_EN_MSK \
    (0x1UL                 \
     << SSI_MD_BITS_EN_POS) /*!< Mode bits enable in XIP mode. If this bit is set to 1, then in XIP mode of operation DWC_ssi will insert mode bits after the address phase. These bits are set in register XIP_MODE_BITS register. The length of mode bits is always set to 8 bits. Value After Reset: SSIC_DFLT_MD_BITS_EN Exists: Always*/
#define SSI_MD_BITS_EN                SSI_MD_BITS_EN_MSK
#define SSI_MD_BITS_EN_W(X)           ((X) << SSI_MD_BITS_EN_POS)
#define SSI_WAIT_CYCLES_XIP_CTRL_POS  (13U)
#define SSI_WAIT_CYCLES_XIP_CTRL_MSK  (0x1fUL << SSI_WAIT_CYCLES_XIP_CTRL_POS) /*!< Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles. Value After Reset: SSIC_DFLT_XIP_WAIT_CYCLES Exists: Always*/
#define SSI_WAIT_CYCLES_XIP_CTRL      SSI_WAIT_CYCLES_XIP_CTRL_MSK
#define SSI_WAIT_CYCLES_XIP_CTRL_W(X) ((X) << SSI_WAIT_CYCLES_XIP_CTRL_POS)
#define SSI_DFS_HC_POS                (18U)
#define SSI_DFS_HC_MSK \
    (0x1UL             \
     << SSI_DFS_HC_POS) /*!< Fix DFS for XIP transfers. If this bit is set to 1 then data frame size for XIP transfers will be fixed to the programmed value in CTRLR0.DFS. The number of data frames to fetch will be determined by HSIZE and HBURST signals. If this bit is set to 0 then data frame size and number of data frames to fetch will be determined by HSIZE and HBURST signals Value After Reset: SSIC_DFLT_DFS_HC Exists: Always Memory Access: "(SSIC_XIP_EN==0) ? \"read-only\": \"read-write\""*/
#define SSI_DFS_HC                   SSI_DFS_HC_MSK
#define SSI_DFS_HC_W(X)              ((X) << SSI_DFS_HC_POS)
#define SSI_DDR_EN_POS               (19U)
#define SSI_DDR_EN_MSK               (0x1UL << SSI_DDR_EN_POS) /*!< SPI DDR Enable bit. This will enable Dual-data rate transfers in Dual/Quad/Octal frame formats of SPI. Value After Reset: SSIC_DFLT_XIP_DDR_EN Exists: Always Memory Access: "(SSIC_HAS_DDR==0) ? \"read-only\": \"read-write\""*/
#define SSI_DDR_EN                   SSI_DDR_EN_MSK
#define SSI_DDR_EN_W(X)              ((X) << SSI_DDR_EN_POS)
#define SSI_INST_DDR_EN_XIP_CTRL_POS (20U)
#define SSI_INST_DDR_EN_XIP_CTRL_MSK \
    (0x1UL << SSI_INST_DDR_EN_XIP_CTRL_POS) /*!< Instruction DDR Enable bit. This will enable Dual-data rate transfer for Instruction phase. Value After Reset: SSIC_DFLT_XIP_INST_DDR_EN Exists: Always Memory Access: "(SSIC_HAS_DDR==0) ? \"read-only\": \"read-write\""*/
#define SSI_INST_DDR_EN_XIP_CTRL      SSI_INST_DDR_EN_XIP_CTRL_MSK
#define SSI_INST_DDR_EN_XIP_CTRL_W(X) ((X) << SSI_INST_DDR_EN_XIP_CTRL_POS)
#define SSI_RXDS_EN_POS               (21U)
#define SSI_RXDS_EN_MSK \
    (0x1UL << SSI_RXDS_EN_POS) /*!< Read data strobe enable bit. Once this bit is set to 1 DWC_ssi will use Read data strobe (rxds) to capture read data in DDR mode. Value After Reset: SSIC_DFLT_XIP_RXDS_EN Exists: Always Memory Access: "(SSIC_HAS_RXDS==0) ? \"read-only\": \"read-write\""*/
#define SSI_RXDS_EN      SSI_RXDS_EN_MSK
#define SSI_RXDS_EN_W(X) ((X) << SSI_RXDS_EN_POS)
#define SSI_INST_EN_POS  (22U)
#define SSI_INST_EN_MSK \
    (0x1UL              \
     << SSI_INST_EN_POS) /*!< XIP instruction enable bit. If this bit is set to 1 then XIP transfers will also have instruction phase. The instruction op- codes will be chosen from XIP_INCR_INST or XIP_WRAP_INST registers bases on AHB transfer type. Value After Reset: SSIC_DFLT_XIP_INST_EN Exists: Always Memory Access: "(SSIC_XIP_INST_EN==0) ? \"read- only\": \"read-write\""*/
#define SSI_INST_EN          SSI_INST_EN_MSK
#define SSI_INST_EN_W(X)     ((X) << SSI_INST_EN_POS)
#define SSI_CONT_XFER_EN_POS (23U)
#define SSI_CONT_XFER_EN_MSK \
    (0x1UL                   \
     << SSI_CONT_XFER_EN_POS) /*!< Enable continuous transfer in XIP mode. If this bit is set to 1 then continuous transfer mode in XIP will be enabled, in this mode DWC_ssi will keep slave selected until a non-XIP transfer is detected on the AHB interface. Value After Reset: SSIC_DFLT_XIP_CONT_XFER_EN Exists: Always Memory Access: "(SSIC_XIP_CONT_XFER_EN==0) ? \"read-only\": \"read-write\""*/
#define SSI_CONT_XFER_EN        SSI_CONT_XFER_EN_MSK
#define SSI_CONT_XFER_EN_W(X)   ((X) << SSI_CONT_XFER_EN_POS)
#define SSI_XIP_HYPERBUS_EN_POS (24U)
#define SSI_XIP_HYPERBUS_EN_MSK \
    (0x1UL                      \
     << SSI_XIP_HYPERBUS_EN_POS) /*!< SPI Hyperbus Frame format enable for XIP transfers. Selects if data frame format for XIP transfers is in Hyperbus mode. This field is effective only when CTRLRO.FRF is set to SPI frame format. Value After Reset: SSIC_DFLT_XIP_HYPERBUS_EN Exists: Always Memory Access: "(SSIC_HYPERBUS_EN==0) ? \"read- only\": \"read-write\""*/
#define SSI_XIP_HYPERBUS_EN      SSI_XIP_HYPERBUS_EN_MSK
#define SSI_XIP_HYPERBUS_EN_W(X) ((X) << SSI_XIP_HYPERBUS_EN_POS)
#define SSI_RXDS_SIG_EN_POS      (25U)
#define SSI_RXDS_SIG_EN_MSK \
    (0x1UL                  \
     << SSI_RXDS_SIG_EN_POS) /*!< Enable rxds signaling during address and command phase of Hypebus transfer. This bit enables rxds signaling by Hyperbus slave devices during Command-Address (CA) phase. If the rxds signal is set to 1 during the CA phase of transfer, DWC_ssi transmits (2*SPI_CTRLR0.WAIT_CYCLES-1) wait cycles after the address phase is complete. Value After Reset: SSIC_DFLT_XIP_RXDS_SIG_EN Exists: Always Memory Access: "(SSIC_HYPERBUS_EN==0) ? \"read- only\": \"read-write\""*/
#define SSI_RXDS_SIG_EN          SSI_RXDS_SIG_EN_MSK
#define SSI_RXDS_SIG_EN_W(X)     ((X) << SSI_RXDS_SIG_EN_POS)
#define SSI_XIP_MBL_XIP_CTRL_POS (26U)
#define SSI_XIP_MBL_XIP_CTRL_MSK \
    (0x3UL                       \
     << SSI_XIP_MBL_XIP_CTRL_POS) /*!< XIP Mode bits length. Sets the length of mode bits in XIP mode of operation. These bits are valid only when XIP_CTRL.XIP_MD_BIT_EN is set to 1. Values: ■ 0x0 (MBL_2): Mode bits length equal to 2 ■ 0x1 (MBL_4): Mode bits length equal to 4 ■ 0x2 (MBL_8): Mode bits length equal to 8 ■ 0x3 (MBL_16): Mode bits length equal to 16 Value After Reset: SSIC_DFLT_XIP_MBL Exists: Always*/
#define SSI_XIP_MBL_XIP_CTRL             SSI_XIP_MBL_XIP_CTRL_MSK
#define SSI_XIP_MBL_XIP_CTRL_W(X)        ((X) << SSI_XIP_MBL_XIP_CTRL_POS)
#define SSI_RSVD_XIP_CTRL_28_POS         (28U)
#define SSI_RSVD_XIP_CTRL_28_MSK         (0x1UL << SSI_RSVD_XIP_CTRL_28_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_XIP_CTRL_28             SSI_RSVD_XIP_CTRL_28_MSK
#define SSI_RSVD_XIP_CTRL_28_W(X)        ((X) << SSI_RSVD_XIP_CTRL_28_POS)
#define SSI_XIP_PREFETCH_EN_XIP_CTRL_POS (29U)
#define SSI_XIP_PREFETCH_EN_XIP_CTRL_MSK \
    (0x1UL                               \
     << SSI_XIP_PREFETCH_EN_XIP_CTRL_POS) /*!< Enables XIP pre-fetch functionality in DWC_ssi. Once enabled DWC_ssi will pre-fetch data frames from next contigous location, to reduce the latency for the upcoming contiguous transfer. If the next XIP request is not contigous then pre-fetched bits will be discarded. Value After Reset: SSIC_DFLT_XIP_PREFETCH Exists: Always*/
#define SSI_XIP_PREFETCH_EN_XIP_CTRL      SSI_XIP_PREFETCH_EN_XIP_CTRL_MSK
#define SSI_XIP_PREFETCH_EN_XIP_CTRL_W(X) ((X) << SSI_XIP_PREFETCH_EN_XIP_CTRL_POS)
#define SSI_RSVD_XIP_CTRL_POS             (30U)
#define SSI_RSVD_XIP_CTRL_MSK             (0x3UL << SSI_RSVD_XIP_CTRL_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always*/
#define SSI_RSVD_XIP_CTRL                 SSI_RSVD_XIP_CTRL_MSK
#define SSI_RSVD_XIP_CTRL_W(X)            ((X) << SSI_RSVD_XIP_CTRL_POS)

//XIP_SER offsetaddress : 0x10c
#define SSI_SER_XIP_SER_POS (0U)
#define SSI_SER_XIP_SER_MSK \
    (0x1UL                  \
     << SSI_SER_XIP_SER_POS) /*!< Slave Select Enable Flag. Each bit in this register corresponds to a slave select line (ss_x_n) from the DWC_ssi master. When a bit in this register is set (1), the corresponding slave select line from the master is activated when a XIP transfer begins. It should be noted that setting or clearing bits in this register have no effect on the corresponding slave select outputs until a XIP transfer is started. Before beginning a transfer, you should enable the bit in this register that corresponds to the slave device with which the master wants to communicate. When not operating in broadcast mode, only one bit in this field should be set. ■ 1: Selected ■ 0: Not Selected Value After Reset: SSIC_DFLT_XIP_SLV Exists: Always Range Variable[x]: SSIC_NUM_SLAVES - 1*/
#define SSI_SER_XIP_SER      SSI_SER_XIP_SER_MSK
#define SSI_SER_XIP_SER_W(X) ((X) << SSI_SER_XIP_SER_POS)

//XRXOICR offsetaddress : 0x110
#define SSI_XRXOICR_POS       (0U)
#define SSI_XRXOICR_MSK       (0x1UL << SSI_XRXOICR_POS) /*!< Clear XIP Receive FIFO Overflow Interrupt. This register reflects the status of the interrupt. A read from this register clears the ssi_xrxo_intr(_n) interrupt; writing has no effect. Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_XRXOICR           SSI_XRXOICR_MSK
#define SSI_XRXOICR_W(X)      ((X) << SSI_XRXOICR_POS)
#define SSI_RSVD_XRXOICR_POS  (1U)
#define SSI_RSVD_XRXOICR_MSK  (0x7fffffffUL << SSI_RSVD_XRXOICR_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_XRXOICR      SSI_RSVD_XRXOICR_MSK
#define SSI_RSVD_XRXOICR_W(X) ((X) << SSI_RSVD_XRXOICR_POS)

//XIP_CNT_TIME_OUT offsetaddress : 0x114
#define SSI_XTOC_POS (0U)
#define SSI_XTOC_MSK \
    (0xffUL << SSI_XTOC_POS) /*!< XIP time out value in terms of hclk. Once slave is selected in continuous XIP mode this counter will be used to de-select the slave if there is no request for the time specified in the counter. Value After Reset: SSIC_DFLT_XIP_TOCNT Exists: Always Volatile: true*/
#define SSI_XTOC           SSI_XTOC_MSK
#define SSI_XTOC_W(X)      ((X) << SSI_XTOC_POS)
#define SSI_RSVD_XTOC_POS  (8U)
#define SSI_RSVD_XTOC_MSK  (0xffffffUL << SSI_RSVD_XTOC_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_XTOC      SSI_RSVD_XTOC_MSK
#define SSI_RSVD_XTOC_W(X) ((X) << SSI_RSVD_XTOC_POS)

//XIP_CNT_TIME_OUT offsetaddress : 0x114
#define SSI_XTOC_XIP_CNT_TIME_OUT_POS (0U)
#define SSI_XTOC_XIP_CNT_TIME_OUT_MSK \
    (0xffUL                           \
     << SSI_XTOC_XIP_CNT_TIME_OUT_POS) /*!< XIP time out value in terms of hclk. Once slave is selected in continuous XIP mode this counter will be used to de-select the slave if there is no request for the time specified in the counter. Value After Reset: SSIC_DFLT_XIP_TOCNT Exists: Always Volatile: true*/
#define SSI_XTOC_XIP_CNT_TIME_OUT           SSI_XTOC_XIP_CNT_TIME_OUT_MSK
#define SSI_XTOC_XIP_CNT_TIME_OUT_W(X)      ((X) << SSI_XTOC_XIP_CNT_TIME_OUT_POS)
#define SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_POS  (8U)
#define SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_MSK  (0xffffffUL << SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_POS) /*!< Reserved bits - Read Only Value After Reset: 0x0 Exists: Always Volatile: true*/
#define SSI_RSVD_XTOC_XIP_CNT_TIME_OUT      SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_MSK
#define SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_W(X) ((X) << SSI_RSVD_XTOC_XIP_CNT_TIME_OUT_POS)

typedef struct {
    volatile uint32_t CTRLR0;          //offsetaddress : 0x0
    volatile uint32_t CTRLR1;          //offsetaddress : 0x4
    volatile uint32_t SSIENR;          //offsetaddress : 0x8
    volatile uint32_t MWCR;            //offsetaddress : 0xc
    volatile uint32_t SER;             //offsetaddress : 0x10
    volatile uint32_t BAUDR;           //offsetaddress : 0x14
    volatile uint32_t TXFTLR;          //offsetaddress : 0x18
    volatile uint32_t RXFTLR;          //offsetaddress : 0x1c
    volatile uint32_t TXFLR;           //offsetaddress : 0x20
    volatile uint32_t RXFLR;           //offsetaddress : 0x24
    volatile uint32_t SR;              //offsetaddress : 0x28
    volatile uint32_t IMR;             //offsetaddress : 0x2c
    volatile uint32_t ISR;             //offsetaddress : 0x30
    volatile uint32_t RISR;            //offsetaddress : 0x34
    volatile uint32_t TXOICR;          //offsetaddress : 0x38
    volatile uint32_t RXOICR;          //offsetaddress : 0x3c
    volatile uint32_t RXUICR;          //offsetaddress : 0x40
    volatile uint32_t MSTICR;          //offsetaddress : 0x44
    volatile uint32_t ICR;             //offsetaddress : 0x48
    volatile uint32_t DMACR;           //offsetaddress : 0x4c
    volatile uint32_t DMATDLR;         //offsetaddress : 0x50
    volatile uint32_t DMARDLR;         //offsetaddress : 0x54
    volatile uint32_t IDR;             //offsetaddress : 0x58
    volatile uint32_t SSIC_VERSION_ID; //offsetaddress : 0x5c
    volatile uint32_t DRx;             //offsetaddress : 0x60 +i*0x4
    volatile uint32_t res[35];
    volatile uint32_t RX_SAMPLE_DELAY;  //offsetaddress : 0xf0
    volatile uint32_t SPI_CTRLR0;       //offsetaddress : 0xf4
    volatile uint32_t DDR_DRIVE_EDGE;   //offsetaddress : 0xf8
    volatile uint32_t XIP_MODE_BITS;    //offsetaddress : 0xfc
    volatile uint32_t XIP_INCR_INST;    //offsetaddress : 0x100
    volatile uint32_t XIP_WRAP_INST;    //offsetaddress : 0x104
    volatile uint32_t XIP_CTRL;         //offsetaddress : 0x108
    volatile uint32_t XIP_SER;          //offsetaddress : 0x10c
    volatile uint32_t XRXOICR;          //offsetaddress : 0x110
    volatile uint32_t XIP_CNT_TIME_OUT; //offsetaddress : 0x114
} ssi_reg_t;
#ifdef __cplusplus
}
#endif
#endif
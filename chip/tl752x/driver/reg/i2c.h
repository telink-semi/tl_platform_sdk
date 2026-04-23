/*******************************************************************************************************
 *
 * @file    i2c.h
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
#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//I2C_CON offsetaddress : 0x0
#define I2C_MASTER_MODE_POS                  (0U)
#define I2C_MASTER_MODE_MSK                  (0x1UL << I2C_MASTER_MODE_POS) /*!< This bit controls whether the DW_apb_i2c master is enabled.Reset value: I2C_MASTER_MODE configuration parameter NOTE: Software should ensure that if this bit is written with '1' then bit 6 should also be written with a '1'. Values: ■ 0x1 (ENABLED): Master mode is enabled ■ 0x0 (DISABLED): Master mode is disabled Exists: Always*/
#define I2C_MASTER_MODE                      I2C_MASTER_MODE_MSK
#define I2C_SPEED_POS                        (1U)
#define I2C_SPEED_MSK                        (0x1UL << I2C_SPEED_POS) /*!< These bits control at which speed the DW_apb_i2c operates; its setting is relevant only if one is operating the DW_apb_i2c in master mode. Hardware protects against illegal values being programmed by software. These bits must be programmed appropriately for slave mode also, as it is used to capture correct value of spike filter as per the speed mode. This register should be programmed only with a value in the range of 1 to I2C_MAX_SPEED_MODE; otherwise, hardware updates this register with the value of I2C_MAX_SPEED_MODE. 1: standard mode (100 kbit/s) 2: fast mode (<=400 kbit/s) or fast mode plus (<=1000Kbit/s) 3: high speed mode (3.4 Mbit/s) Note: This field is not applicable when I2C_ULTRA_FAST_MODE=1 Reset value: I2C_MAX_SPEED_MODE configuration Values: ■ 0x1 (STANDARD): Standard Speed mode of operation ■ 0x2 (FAST): Fast or Fast Plus mode of operation ■ 0x3 (HIGH): High Speed mode of operation Exists: Always*/
#define I2C_SPEED                            I2C_SPEED_MSK
#define I2C_I2C_10BITADDR_SLAVE_POS          (3U)
#define I2C_I2C_10BITADDR_SLAVE_MSK          (0x1UL << I2C_I2C_10BITADDR_SLAVE_POS) /*!< When acting as a slave, this bit controls whether the DW_apb_i2c responds to 7- or 10-bit addresses. ■ 0: 7-bit addressing. The DW_apb_i2c ignores transactions that involve 10-bit addressing; for 7-bit addressing, only the lower 7 bits of the I2C_SAR register are compared. ■ 1: 10-bit addressing. The DW_apb_i2c responds to only 10-bit addressing transfers that match the full 10 bits of the I2C_SAR register. Reset value: I2C_10BITADDR_SLAVE configuration parameter Values: ■ 0x1 (ADDR_10BITS): Slave 10Bit addressing ■ 0x0 (ADDR_7BITS): Slave 7Bit addressing Exists: Always*/
#define I2C_I2C_10BITADDR_SLAVE              I2C_I2C_10BITADDR_SLAVE_MSK
#define I2C_I2C_10BITADDR_MASTER_POS         (4U)
#define I2C_I2C_10BITADDR_MASTER_MSK         (0x1UL << I2C_I2C_10BITADDR_MASTER_POS) /*!< If the I2C_DYNAMI2C_TAR_UPDATE configuration parameter is set to 'No' (0), this bit is named I2C_10BITADDR_MASTER and controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit addressing mode when acting as a master. If I2C_DYNAMI2C_TAR_UPDATE is set to 'Yes' (1), the function of this bit is handled by bit 12 of I2C_TAR register, and becomes a read-only copy called I2C_10BITADDR_MASTER_rd_only. ■ 0: 7-bit addressing ■ 1: 10-bit addressing Reset value: I2C_10BITADDR_MASTER configuration parameter Values: ■ 0x1 (ADDR_10BITS): Master 10Bit addressing mode ■ 0x0 (ADDR_7BITS): Master 7Bit addressing mode Exists: I2C_DYNAMI2C_TAR_UPDATE == 0*/
#define I2C_I2C_10BITADDR_MASTER             I2C_I2C_10BITADDR_MASTER_MSK
#define I2C_I2C_RESTART_EN_POS               (5U)
#define I2C_I2C_RESTART_EN_MSK               (0x1UL << I2C_I2C_RESTART_EN_POS) /*!< Determines whether RESTART conditions may be sent when acting as a master. Some older slaves do not support handling RESTART conditions; however, RESTART conditions are used in several DW_apb_i2c operations. When RESTART is disabled, the master is prohibited from performing the following functions: ■ Sending a START BYTE ■ Performing any high-speed mode operation ■ High-speed mode operation ■ Performing direction changes in combined format mode ■ Performing a read operation with a 10-bit address By replacing RESTART condition followed by a STOP and a subsequent START condition, split operations are broken down into multiple DW_apb_i2c transfers. If the above operations are performed, it will result in setting bit 6 (TX_ABRT) of the I2C_RAW_INTR_STAT register. Reset value: I2C_RESTART_EN configuration parameter Values: ■ 0x1 (ENABLED): Master restart enabled ■ 0x0 (DISABLED): Master restart disabled Exists: Always*/
#define I2C_I2C_RESTART_EN                   I2C_I2C_RESTART_EN_MSK
#define I2C_I2C_SLAVE_DISABLE_POS            (6U)
#define I2C_I2C_SLAVE_DISABLE_MSK            (0x1UL << I2C_I2C_SLAVE_DISABLE_POS) /*!< This bit controls whether I2C has its slave disabled, which means once the presetn signal is applied, then this bit takes on the value of the configuration parameter I2C_SLAVE_DISABLE. You have the choice of having the slave enabled or disabled after reset is applied, which means software does not have to configure the slave. By default, the slave is always enabled (in reset state as well). If you need to disable it after reset, set this bit to 1. If this bit is set (slave is disabled), DW_apb_i2c functions only as a master and does not perform any action that requires a slave.Reset value: I2C_SLAVE_DISABLE configuration parameter NOTE: Software should ensure that if this bit is written with 0, then bit 0 should also be written with a 0. Values: ■ 0x1 (SLAVE_DISABLED): Slave mode is disabled ■ 0x0 (SLAVE_ENABLED): Slave mode is enabled Exists: Always*/
#define I2C_I2C_SLAVE_DISABLE                I2C_I2C_SLAVE_DISABLE_MSK
#define I2C_STOP_DET_IFADDRESSED_POS         (7U)
#define I2C_STOP_DET_IFADDRESSED_MSK         (0x1UL << I2C_STOP_DET_IFADDRESSED_POS) /*!< In slave mode: ■ 1'b1: issues the STOP_DET interrrupt only when it is addressed. ■ 0'b0: issues the STOP_DET irrespective of whether it's addressed or not. Reset value: 0x0 NOTE: During a general call address, this slave does not issue the STOP_DET interrupt if STOP_DET_IF_ADDRESSED = 1'b1, even if the slave responds to the general call address by generating ACK. The STOP_DET interrupt is generated only when the transmitted address matches the slave address (SAR). Values: ■ 0x1 (ENABLED): slave issues STOP_DET intr only if addressed ■ 0x0 (DISABLED): slave issues STOP_DET intr always Exists: Always*/
#define I2C_STOP_DET_IFADDRESSED             I2C_STOP_DET_IFADDRESSED_MSK
#define I2C_TX_EMPTY_CTRL_POS                (8U)
#define I2C_TX_EMPTY_CTRL_MSK                (0x1UL << I2C_TX_EMPTY_CTRL_POS) /*!< This bit controls the generation of the TX_EMPTY interrupt, as described in the I2C_RAW_INTR_STAT register. Reset value: 0x0. Values: ■ 0x1 (ENABLED): Controlled generation of TX_EMPTY interrupt ■ 0x0 (DISABLED): Default behaviour of TX_EMPTY interrupt Exists: Always*/
#define I2C_TX_EMPTY_CTRL                    I2C_TX_EMPTY_CTRL_MSK
#define I2C_RX_FIFO_FULL_HLD_CTRL_POS        (9U)
#define I2C_RX_FIFO_FULL_HLD_CTRL_MSK        (0x1UL << I2C_RX_FIFO_FULL_HLD_CTRL_POS) /*!< This bit controls whether DW_apb_i2c should hold the bus when the Rx FIFO is physically full to its RX_BUFFER_DEPTH, as described in the I2C_RX_FULL_HLD_BUS_EN parameter. Reset value: 0x0. Values: ■ 0x1 (ENABLED): Hold bus when RX_FIFO is full ■ 0x0 (DISABLED): Overflow when RX_FIFO is full Exists: Always Memory Access: "(I2C_RX_FULL_HLD_BUS_EN==1) ? \"read-write\" : \"read-only\""*/
#define I2C_RX_FIFO_FULL_HLD_CTRL            I2C_RX_FIFO_FULL_HLD_CTRL_MSK
#define I2C_STOP_DET_IF_MASTER_ACTIVE_POS    (10U)
#define I2C_STOP_DET_IF_MASTER_ACTIVE_MSK    (0x1UL << I2C_STOP_DET_IF_MASTER_ACTIVE_POS) /*!< In Master mode: ■ 1'b1: issues the STOP_DET interrupt only when master is active. ■ 1'b0: issues the STOP_DET irrespective of whether master is active or not. Reset value: 0x0. Values: ■ 0x1 (ENABLED): Master issues the STOP_DET interrupt only when master is active ■ 0x0 (DISABLED): Master issues the STOP_DET interrupt irrespective of whether master is active or not Exists: Always Memory Access: "(I2C_STOP_DET_IF_MASTER_ACTIVE==1) ? \"read-write\" : \"read-only\""*/
#define I2C_STOP_DET_IF_MASTER_ACTIVE        I2C_STOP_DET_IF_MASTER_ACTIVE_MSK
#define I2C_BUS_CLEAR_FEATURE_CTRL_POS       (11U)
#define I2C_BUS_CLEAR_FEATURE_CTRL_MSK       (0x1UL << I2C_BUS_CLEAR_FEATURE_CTRL_POS) /*!< In Master mode: ■ 1'b1: Bus Clear Feature is enabled. ■ 1'b0: Bus Clear Feature is Disabled. In Slave mode, this register bit is not applicable. Reset value: 0x0. Values: ■ 0x1 (ENABLED): Bus Clear Feature ois enabled. ■ 0x0 (DISABLED): Bus Clear Feature is disabled. Exists: I2C_BUS_CLEAR_FEATURE==1*/
#define I2C_BUS_CLEAR_FEATURE_CTRL           I2C_BUS_CLEAR_FEATURE_CTRL_MSK
#define I2C_RSVD_I2C_CON_1_POS               (12U)
#define I2C_RSVD_I2C_CON_1_MSK               (0x1UL << I2C_RSVD_I2C_CON_1_POS) /*!< I2C_CON_1 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_CON_1                   I2C_RSVD_I2C_CON_1_MSK
#define I2C_OPTIONAL_SAR_CTRL_POS            (16U)
#define I2C_OPTIONAL_SAR_CTRL_MSK            (0x1UL << I2C_OPTIONAL_SAR_CTRL_POS) /*!< Enables the usage of I2C_OPTIONAL_SAR register. If I2C_OPTIONAL_SAR =1, I2C_OPTIONAL_SAR value is used as additional slave address. User must program a valid address in I2C_OPTIONAL_SAR before writing 1 to this field. If I2C_OPTIONAL_SAR =0, I2C_OPTIONAL_SAR value is not used as additional slave address. In this mode only one I2C slave address is used. Reset value: I2C_OPTIONAL_SAR_DEFAULT. Values: ■ 0x1 (ENABLED): Optional SAR Address Register is enabled. ■ 0x0 (DISABLED): Optional SAR Address Register is disabled. Exists: I2C_OPTIONAL_SAR==1*/
#define I2C_OPTIONAL_SAR_CTRL                I2C_OPTIONAL_SAR_CTRL_MSK
#define I2C_SMBUS_SLAVE_QUI2CK_EN_POS        (17U)
#define I2C_SMBUS_SLAVE_QUI2CK_EN_MSK        (0x1UL << I2C_SMBUS_SLAVE_QUI2CK_EN_POS) /*!< If this bit is set to 1, DW_apb_i2c slave only receives Quick commands in SMBus Mode. If this bit is set to 0, DW_apb_i2c slave receives all bus protocols but not Quick commands. This bit is applicable only in slave mode. Reset value: 0x0. Values: ■ 0x1 (ENABLED): SMBus SLave is enabled to receive Quick command. ■ 0x0 (DISABLED): SMBus SLave is disabled to receive Quick command. Exists: I2C_SMBUS==1*/
#define I2C_SMBUS_SLAVE_QUI2CK_EN            I2C_SMBUS_SLAVE_QUI2CK_EN_MSK
#define I2C_SMBUS_ARP_EN_POS                 (18U)
#define I2C_SMBUS_ARP_EN_MSK                 (0x1UL << I2C_SMBUS_ARP_EN_POS) /*!< This bit controls whether DW_apb_i2c should enable Address Resolution Logic in SMBus Mode. The Slave mode will decode the Address Resolution Protocol commands and respond to it. The DW_apb_i2c slave also includes the generation/validity of PEC byte for Address Resolution Protocol commands. This bit is applicable only in Slave mode. Reset Value: 0x0. Values: ■ 0x1 (ENABLED): SMBus ARP control is enabled. ■ 0x0 (DISABLED): SMBus ARP control is disabled. Exists: I2C_SMBUS_ARP==1*/
#define I2C_SMBUS_ARP_EN                     I2C_SMBUS_ARP_EN_MSK
#define I2C_SMBUS_PERSISTENT_SLV_ADDR_EN_POS (19U)
#define I2C_SMBUS_PERSISTENT_SLV_ADDR_EN_MSK (0x1UL << I2C_SMBUS_PERSISTENT_SLV_ADDR_EN_POS) /*!< The bit controls to enable DW_apb_i2c slave as persistent or non persistent slave. If the slave is non-PSA then DW_apb_i2c slave device clears the Address valid flag for both General and Directed Reset ARP command else the address valid flag will always set to 1. This bit is applicable only in Slave mode. Reset Value :I2C_PERSISTANT_SLV_ADDR_DEFAULT. Values: ■ 0x1 (ENABLED): SMBus Persistent Slave address control is enabled. ■ 0x0 (DISABLED): SMBus Persistent Slave address control is disabled. Exists: I2C_SMBUS_ARP==1*/
#define I2C_SMBUS_PERSISTENT_SLV_ADDR_EN     I2C_SMBUS_PERSISTENT_SLV_AD DR_EN_MSK
#define I2C_RSVD_I2C_CON_2_POS               (20U)
#define I2C_RSVD_I2C_CON_2_MSK               (0x1UL << I2C_RSVD_I2C_CON_2_POS) /*!< I2C_CON_2 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_CON_2                   I2C_RSVD_I2C_CON_2_MSK

//I2C_TAR offsetaddress : 0x4
#define I2C_I2C_TAR_POS                  (0U)
#define I2C_I2C_TAR_MSK                  (0x1UL << I2C_I2C_TAR_POS) /*!< This is the target address for any master transaction. When transmitting a General Call, these bits are ignored. To generate a START BYTE, the CPU needs to write only once into these bits. If the I2C_TAR and I2C_SAR are the same, loopback exists but the FIFOs are shared between master and slave, so full loopback is not feasible. Only one direction loopback mode is supported (simplex), not duplex. A master cannot transmit to itself; it can transmit to only a slave. Reset value: I2C_DEFAULT_TAR_SLAVE_ADDR configuration parameter Exists: Always*/
#define I2C_I2C_TAR                      I2C_I2C_TAR_MSK
#define I2C_GC_OR_START_POS              (10U)
#define I2C_GC_OR_START_MSK              (0x1UL << I2C_GC_OR_START_POS) /*!< If bit 11 (SPECIAL) is set to 1 and bit 13(Device-ID) is set to 0, then this bit indicates whether a General Call or START byte command is to be performed by the DW_apb_i2c. ■ 0: General Call Address - after issuing a General Call, only writes may be performed. Attempting to issue a read command results in setting bit 6 (TX_ABRT) of the I2C_RAW_INTR_STAT register. The DW_apb_i2c remains in General Call mode until the SPECIAL bit value (bit 11) is cleared. ■ 1: START BYTE Reset value: 0x0 Values: ■ 0x1 (START_BYTE): START byte transmission ■ 0x0 (GENERAL_CALL): GENERAL_CALL byte transmission Exists: Always*/
#define I2C_GC_OR_START                  I2C_GC_OR_START_MSK
#define I2C_SPECIAL_POS                  (11U)
#define I2C_SPECIAL_MSK                  (0x1UL << I2C_SPECIAL_POS) /*!< This bit indicates whether software performs a Device-ID or General Call or START BYTE command. ■ 0: ignore bit 10 GC_OR_START and use I2C_TAR normally ■ 1: perform special I2C command as specified in Device_ID or GC_OR_START bit Reset value: 0x0 Values: ■ 0x1 (ENABLED): Enables programming of GENERAL_CALL or START_BYTE transmission ■ 0x0 (DISABLED): Disables programming of GENERAL_CALL or START_BYTE transmission Exists: Always*/
#define I2C_SPECIAL                      I2C_SPECIAL_MSK
#define I2C_TAR_I2C_10BITADDR_MASTER_POS (12U)
#define I2C_TAR_I2C_10BITADDR_MASTER_MSK (0x1UL << I2C_TAR_I2C_10BITADDR_MASTER_POS) /*!< This bit controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit addressing mode when acting as a master. ■ 0: 7-bit addressing ■ 1: 10-bit addressing Reset value: I2C_10BITADDR_MASTER configuration parameter Values: ■ 0x1 (ADDR_10BITS): Address 10Bit transmission format ■ 0x0 (ADDR_7BITS): Address 7Bit transmission format Exists: I2C_DYNAMI2C_TAR_UPDATE*/
#define I2C_TAR_I2C_10BITADDR_MASTER     I2C_TAR_I2C_10BITADDR_MASTER_MSK
#define I2C_DEVI2CE_ID_POS               (13U)
#define I2C_DEVI2CE_ID_MSK               (0x1UL << I2C_DEVI2CE_ID_POS) /*!< If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a Device-ID of a particular slave mentioned in I2C_TAR[9:0] is to be performed by the DW_apb_i2c Master. ■ 0: Device-ID is not performed and checks ic_tar[10] to perform either general call or START byte command ■ 1: Device-ID transfer is performed and bytes based on the number of read commands in the Tx-FIFO are received from the targeted slave and put in the Rx-FIFO. Reset value: 0x0 Values: ■ 0x1 (ENABLED): Enables programming of DEVI2CE-ID transmission ■ 0x0 (DISABLED): Disables programming of DEVI2CE-ID transmission Exists: I2C_DEVI2CE_ID == 1*/
#define I2C_DEVI2CE_ID                   I2C_DEVI2CE_ID_MSK
#define I2C_RSVD_I2C_TAR_1_POS           (14U)
#define I2C_RSVD_I2C_TAR_1_MSK           (0x1UL << I2C_RSVD_I2C_TAR_1_POS) /*!< I2C_TAR_1 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_TAR_1               I2C_RSVD_I2C_TAR_1_MSK
#define I2C_SMBUS_QUI2CK_CMD_POS         (16U)
#define I2C_SMBUS_QUI2CK_CMD_MSK         (0x1UL << I2C_SMBUS_QUI2CK_CMD_POS) /*!< If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a Quick command is to be performed by the DW_apb_i2c. Reset value: 0x0 Values: ■ 0x1 (ENABLED): Enables programming of QUI2CK-CMD transmission ■ 0x0 (DISABLED): Disables programming of QUI2CK-CMD transmission Exists: I2C_SMBUS == 1*/
#define I2C_SMBUS_QUI2CK_CMD             I2C_SMBUS_QUI2CK_CMD_MSK
#define I2C_RSVD_I2C_TAR_2_POS           (17U)
#define I2C_RSVD_I2C_TAR_2_MSK           (0x1UL << I2C_RSVD_I2C_TAR_2_POS) /*!< I2C_TAR_2 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_TAR_2               I2C_RSVD_I2C_TAR_2_MSK

//I2C_SAR offsetaddress : 0x8
#define I2C_I2C_SAR_POS      (0U)
#define I2C_I2C_SAR_MSK      (0x1UL << I2C_I2C_SAR_POS) /*!< The I2C_SAR holds the slave address when the I2C is operating as a slave. For 7-bit addressing, only I2C_SAR[6:0] is used. This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. Note: The default values cannot be any of the reserved address locations: that is, 0x00 to 0x07, or 0x78 to 0x7f. The correct operation of the device is not guaranteed if you program the I2C_SAR or I2C_TAR to a reserved value. Refer to Table "I2C/SMBus Definition of Bits in First Byte" for a complete list of these reserved values. Reset value: I2C_DEFAULT_SLAVE_ADDR configuration parameter Exists: Always*/
#define I2C_I2C_SAR          I2C_I2C_SAR_MSK
#define I2C_RSVD_I2C_SAR_POS (10U)
#define I2C_RSVD_I2C_SAR_MSK (0x1UL << I2C_RSVD_I2C_SAR_POS) /*!< I2C_SAR Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SAR     I2C_RSVD_I2C_SAR_MSK

//I2C_HS_MADDR offsetaddress : 0xc
#define I2C_I2C_HS_MAR_POS      (0U)
#define I2C_I2C_HS_MAR_MSK      (0x1UL << I2C_I2C_HS_MAR_POS) /*!< This bit field holds the value of the I2C HS mode master code. HS-mode master codes are reserved 8-bit codes (00001xxx) that are not used for slave addressing or other purposes. Each master has its unique master code; up to eight high-speed mode masters can be present on the same I2C bus system. Valid values are from 0 to 7. This register goes away and becomes read-only returning 0's if the I2C_MAX_SPEED_MODE configuration parameter is set to either Standard (1) or Fast (2). This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. Reset value: I2C_HS_MASTER_CODE configuration parameter Exists: Always*/
#define I2C_I2C_HS_MAR          I2C_I2C_HS_MAR_MSK
#define I2C_RSVD_I2C_HS_MAR_POS (3U)
#define I2C_RSVD_I2C_HS_MAR_MSK (0x1UL << I2C_RSVD_I2C_HS_MAR_POS) /*!< I2C_HS_MAR Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_HS_MAR     I2C_RSVD_I2C_HS_MAR_MSK

//I2C_DATA_CMD offsetaddress : 0x10
#define I2C_DAT_POS               (0U)
#define I2C_DAT_MSK               (0x1UL << I2C_DAT_POS) /*!< This register contains the data to be transmitted or received on the I2C bus. If you are writing to this register and want to perform a read, bits 7:0 (DAT) are ignored by the DW_apb_i2c. However, when you read this register, these bits return the value of data received on the DW_apb_i2c interface. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_DAT                   I2C_DAT_MSK
#define I2C_CMD_POS               (8U)
#define I2C_CMD_MSK               (0x1UL << I2C_CMD_POS) /*!< This bit controls whether a read or a write is performed. This bit does not control the direction when the DW_apb_i2c acts as a slave. It controls only the direction when it acts as a master. When a command is entered in the TX FIFO, this bit distinguishes the write and read commands. In slave- receiver mode, this bit is a "don't care" because writes to this register are not required. In slave-transmitter mode, a "0" indicates that the data in I2C_DATA_CMD is to be transmitted. When programming this bit, you should remember the following: attempting to perform a read operation after a General Call command has been sent results in a TX_ABRT interrupt (bit 6 of the I2C_RAW_INTR_STAT register), unless bit 11 (SPECIAL) in the I2C_TAR register has been cleared. If a "1" is written to this bit after receiving a RD_REQ interrupt, then a TX_ABRT interrupt occurs. Reset value: 0x0 Values: ■ 0x1 (READ): Master Read Command ■ 0x0 (WRITE): Master Write Command Exists: Always Volatile: true*/
#define I2C_CMD                   I2C_CMD_MSK
#define I2C_STOP_POS              (9U)
#define I2C_STOP_MSK              (0x1UL << I2C_STOP_POS) /*!< This bit controls whether a STOP is issued after the byte is sent or received. This bit is available only if I2C_EMPTYFIFO_HOLD_MASTER_EN is configured to 1. ■ 1 - STOP is issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master immediately tries to start a new transfer by issuing a START and arbitrating for the bus. ■ 0 - STOP is not issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master continues the current transfer by sending/receiving data bytes according to the value of the CMD bit. If the Tx FIFO is empty, the master holds the SCL line low and stalls the bus until a new command is available in the Tx FIFO. Reset value: 0x0 Values: ■ 0x1 (ENABLE): Issue STOP after this command ■ 0x0 (DISABLE): Donot Issue STOP after this command Exists: I2C_EMPTYFIFO_HOLD_MASTER_EN Volatile: true*/
#define I2C_STOP                  I2C_STOP_MSK
#define I2C_RESTART_POS           (10U)
#define I2C_RESTART_MSK           (0x1UL << I2C_RESTART_POS) /*!< This bit controls whether a RESTART is issued before the byte is sent or received. This bit is available only if I2C_EMPTYFIFO_HOLD_MASTER_EN is configured to 1. 1 - If I2C_RESTART_EN is 1, a RESTART is issued before the data is sent/received (according to the value of CMD), regardless of whether or not the transfer direction is changing from the previous command; if I2C_RESTART_EN is 0, a STOP followed by a START is issued instead. 0 - If I2C_RESTART_EN is 1, a RESTART is issued only if the transfer direction is changing from the previous command; if I2C_RESTART_EN is 0, a STOP followed by a START is issued instead. Reset value: 0x0 Values: ■ 0x1 (ENABLE): Issue RESTART before this command ■ 0x0 (DISABLE): Donot Issue RESTART before this command Exists: I2C_EMPTYFIFO_HOLD_MASTER_EN Volatile: true*/
#define I2C_RESTART               I2C_RESTART_MSK
#define I2C_FIRST_DATA_BYTE_POS   (11U)
#define I2C_FIRST_DATA_BYTE_MSK   (0x1UL << I2C_FIRST_DATA_BYTE_POS) /*!< Indicates the first data byte received after the address phase for receive transfer in Master receiver or Slave receiver mode. Reset value : 0x0 NOTE: In case of APB_DATA_WIDTH=8, 1. The user has to perform two APB Reads to I2C_DATA_CMD in order to get status on 11 bit. 2. Inorder to read the 11 bit, the user has to perform the first data byte read [7:0] (offset 0x10) and then perform the second read[15:8](offset 0x11) in order to know the status of 11 bit (whether the data received in previous read is a first data byte or not). 3. The 11th bit is an optional read field, user can ignore 2nd byte read [15:8] (offset 0x11) if not interested in FIRST_DATA_BYTE status. Values: ■ 0x1 (ACTIVE): Non sequential data byte received ■ 0x0 (INACTIVE): Sequential data byte received Exists: I2C_FIRST_DATA_BYTE_STATUS == 1 Volatile: true*/
#define I2C_FIRST_DATA_BYTE       I2C_FIRST_DATA_BYTE_MSK
#define I2C_RSVD_I2C_DATA_CMD_POS (12U)
#define I2C_RSVD_I2C_DATA_CMD_MSK (0x1UL << I2C_RSVD_I2C_DATA_CMD_POS) /*!< I2C_DATA_CMD Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_DATA_CMD     I2C_RSVD_I2C_DATA_CMD_MSK

//I2C_SS_SCL_HCNT offsetaddress : 0x14
#define I2C_I2C_SS_SCL_HCNT_POS            (0U)
#define I2C_I2C_SS_SCL_HCNT_MSK            (0x1UL << I2C_I2C_SS_SCL_HCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for standard speed. For more information, refer to "I2C_CLK Frequency Configuration". This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. When the configuration parameter I2C_HC_COUNT_VALUES is set to 1, this register is read only. NOTE: This register must not be programmed to a value higher than 65525, because DW_apb_i2c uses a 16-bit counter to flag an I2C bus idle condition when this counter reaches a value of I2C_SS_SCL_HCNT + 10. Reset value: I2C_SS_SCL_HIGH_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_SS_SCL_HCNT                I2C_I2C_SS_SCL_HCNT_MSK
#define I2C_RSVD_I2C_SS_SCL_HIGH_COUNT_POS (16U)
#define I2C_RSVD_I2C_SS_SCL_HIGH_COUNT_MSK (0x1UL << I2C_RSVD_I2C_SS_SCL_HIGH_COUNT_POS) /*!< I2C_SS_SCL_HCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SS_SCL_HIGH_COUNT     I2C_RSVD_I2C_SS_SCL_HIGH_COUNT_MSK
//I2C_UFM_SCL_HCNT offsetaddress : 0x14
#define I2C_I2C_UFM_SCL_HCNT_POS      (0U)
#define I2C_I2C_UFM_SCL_HCNT_MSK      (0x1UL << I2C_I2C_UFM_SCL_HCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for Ultra-Fast speed. For more information, refer to "I2C_CLK Frequency Configuration". This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 3; hardware prevents values less than this being written, and if attempted results in 3 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. When the configuration parameter I2C_HC_COUNT_VALUES is set to 1, this register is read only. Reset value: I2C_UFM_SCL_HIGH_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_UFM_SCL_HCNT          I2C_I2C_UFM_SCL_HCNT_MSK
#define I2C_RSVD_I2C_UFM_SCL_HCNT_POS (16U)
#define I2C_RSVD_I2C_UFM_SCL_HCNT_MSK (0x1UL << I2C_RSVD_I2C_UFM_SCL_HCNT_POS) /*!< I2C_UFM_SCL_HCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_UFM_SCL_HCNT     I2C_RSVD_I2C_UFM_SCL_HCNT_MSK

//I2C_SS_SCL_LCNT offsetaddress : 0x18
#define I2C_I2C_SS_SCL_LCNT_POS           (0U)
#define I2C_I2C_SS_SCL_LCNT_MSK           (0x1UL << I2C_I2C_SS_SCL_LCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for standard speed. For more information, refer to "I2C_CLK Frequency Configuration" This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 8; hardware prevents values less than this being written, and if attempted, results in 8 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of DW_apb_i2c. The lower byte must be programmed first, and then the upper byte is programmed. When the configuration parameter I2C_HC_COUNT_VALUES is set to 1, this register is read only. Reset value: I2C_SS_SCL_LOW_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_SS_SCL_LCNT               I2C_I2C_SS_SCL_LCNT_MSK
#define I2C_RSVD_I2C_SS_SCL_LOW_COUNT_POS (16U)
#define I2C_RSVD_I2C_SS_SCL_LOW_COUNT_MSK (0x1UL << I2C_RSVD_I2C_SS_SCL_LOW_COUNT_POS) /*!< RSVD_I2C_SS_SCL_LOW_COUNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SS_SCL_LOW_COUNT     I2C_RSVD_I2C_SS_SCL_LOW_COUNT_MSK

//I2C_UFM_SCL_LCNT offsetaddress : 0x18
#define I2C_I2C_UFM_SCL_LCNT_POS      (0U)
#define I2C_I2C_UFM_SCL_LCNT_MSK      (0x1UL << I2C_I2C_UFM_SCL_LCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for Ultra-Fast speed. This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 5; hardware prevents values less than this being written, and if attempted, results in 5 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of DW_apb_i2c. The lower byte must be programmed first, and then the upper byte is programmed. When the configuration parameter I2C_HC_COUNT_VALUES is set to 1, this register is read only. Reset value: I2C_UFM_SCL_LOW_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_UFM_SCL_LCNT          I2C_I2C_UFM_SCL_LCNT_MSK
#define I2C_RSVD_I2C_UFM_SCL_LCNT_POS (16U)
#define I2C_RSVD_I2C_UFM_SCL_LCNT_MSK (0x1UL << I2C_RSVD_I2C_UFM_SCL_LCNT_POS) /*!< I2C_UFM_SCL_LCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_UFM_SCL_LCNT     I2C_RSVD_I2C_UFM_SCL_LCNT_MSK

//I2C_FS_SCL_HCNT offsetaddress : 0x1c
#define I2C_I2C_FS_SCL_HCNT_POS      (0U)
#define I2C_I2C_FS_SCL_HCNT_MSK      (0x1UL << I2C_I2C_FS_SCL_HCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for fast mode or fast mode plus. It is used in high-speed mode to send the Master Code and START BYTE or General CALL. For more information, refer to "I2C_CLK Frequency Configuration". This register goes away and becomes read-only returning 0s if I2C_MAX_SPEED_MODE = standard. This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH == 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. Reset value: I2C_FS_SCL_HIGH_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_FS_SCL_HCNT          I2C_I2C_FS_SCL_HCNT_MSK
#define I2C_RSVD_I2C_FS_SCL_HCNT_POS (16U)
#define I2C_RSVD_I2C_FS_SCL_HCNT_MSK (0x1UL << I2C_RSVD_I2C_FS_SCL_HCNT_POS) /*!< I2C_FS_SCL_HCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_FS_SCL_HCNT     I2C_RSVD_I2C_FS_SCL_HCNT_MSK

//I2C_UFM_TBUF_CNT offsetaddress : 0x1c
#define I2C_I2C_UFM_TBUF_CNT_POS      (0U)
#define I2C_I2C_UFM_TBUF_CNT_MSK      (0x1UL << I2C_I2C_UFM_TBUF_CNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the Bus-Free time between a STOP and STOP condition count for Ultra-Fast speed. This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first and then the upper byte is programmed. When the configuration parameter. NOTE: The DW_apb_i2c will add 9 ic_clks after tBuf time is expired to generate START on the Bus. Reset value: I2C_UFM_TBUF_CNT_DEFAULT configuration parameter Exists: Always*/
#define I2C_I2C_UFM_TBUF_CNT          I2C_I2C_UFM_TBUF_CNT_MSK
#define I2C_RSVD_I2C_UFM_TBUF_CNT_POS (16U)
#define I2C_RSVD_I2C_UFM_TBUF_CNT_MSK (0x1UL << I2C_RSVD_I2C_UFM_TBUF_CNT_POS) /*!< I2C_UFM_TBUF_CNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_UFM_TBUF_CNT     I2C_RSVD_I2C_UFM_TBUF_CNT_MSK

//I2C_FS_SCL_LCNT offsetaddress : 0x20
#define I2C_I2C_FS_SCL_LCNT_POS      (0U)
#define I2C_I2C_FS_SCL_LCNT_MSK      (0x1UL << I2C_I2C_FS_SCL_LCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for fast speed. It is used in high- speed mode to send the Master Code and START BYTE or General CALL. For more information, refer to "I2C_CLK Frequency Configuration". This register goes away and becomes read-only returning 0s if I2C_MAX_SPEED_MODE = standard. This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 8; hardware prevents values less than this being written, and if attempted results in 8 being set. For designs with APB_DATA_WIDTH = 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. If the value is less than 8 then the count value gets changed to 8. When the configuration parameter I2C_HC_COUNT_VALUES is set to 1, this register is read only. Reset value: I2C_FS_SCL_LOW_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_FS_SCL_LCNT          I2C_I2C_FS_SCL_LCNT_MSK
#define I2C_RSVD_I2C_FS_SCL_LCNT_POS (16U)
#define I2C_RSVD_I2C_FS_SCL_LCNT_MSK (0x1UL << I2C_RSVD_I2C_FS_SCL_LCNT_POS) /*!< I2C_FS_SCL_LCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_FS_SCL_LCNT     I2C_RSVD_I2C_FS_SCL_LCNT_MSK

//I2C_HS_SCL_HCNT offsetaddress : 0x24
#define I2C_I2C_HS_SCL_HCNT_POS      (0U)
#define I2C_I2C_HS_SCL_HCNT_MSK      (0x1UL << I2C_I2C_HS_SCL_HCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high period count for high speed.refer to "I2C_CLK Frequency Configuration". The SCL High time depends on the loading of the bus. For 100pF loading, the SCL High time is 60ns; for 400pF loading, the SCL High time is 120ns. This register goes away and becomes read-only returning 0s if I2C_MAX_SPEED_MODE != high. This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH = 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. Reset value: I2C_HS_SCL_HIGH_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_HS_SCL_HCNT          I2C_I2C_HS_SCL_HCNT_MSK
#define I2C_RSVD_I2C_HS_SCL_HCNT_POS (16U)
#define I2C_RSVD_I2C_HS_SCL_HCNT_MSK (0x1UL << I2C_RSVD_I2C_HS_SCL_HCNT_POS) /*!< I2C_HS_SCL_HCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_HS_SCL_HCNT     I2C_RSVD_I2C_HS_SCL_HCNT_MSK

//I2C_HS_SCL_LCNT offsetaddress : 0x28
#define I2C_I2C_HS_SCL_LCNT_POS         (0U)
#define I2C_I2C_HS_SCL_LCNT_MSK         (0x1UL << I2C_I2C_HS_SCL_LCNT_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for high speed. For more information, refer to "I2C_CLK Frequency Configuration". The SCL low time depends on the loading of the bus. For 100pF loading, the SCL low time is 160ns; for 400pF loading, the SCL low time is 320ns. This register goes away and becomes read-only returning 0s if I2C_MAX_SPEED_MODE != high. This register can be written only when the I2C interface is disabled, which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 8; hardware prevents values less than this being written, and if attempted results in 8 being set. For designs with APB_DATA_WIDTH == 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. If the value is less than 8 then the count value gets changed to 8. Reset value: I2C_HS_SCL_LOW_COUNT configuration parameter Exists: Always Memory Access: "(I2C_HC_COUNT_VALUES==1) ? \"read- only\" : \"read-write\""*/
#define I2C_I2C_HS_SCL_LCNT             I2C_I2C_HS_SCL_LCNT_MSK
#define I2C_RSVD_I2C_HS_SCL_LOW_CNT_POS (16U)
#define I2C_RSVD_I2C_HS_SCL_LOW_CNT_MSK (0x1UL << I2C_RSVD_I2C_HS_SCL_LOW_CNT_POS) /*!< I2C_HS_SCL_LCNT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_HS_SCL_LOW_CNT     I2C_RSVD_I2C_HS_SCL_LOW_CNT_MSK

//I2C_INTR_STAT offsetaddress : 0x2c
#define I2C_R_RX_UNDER_POS         (0U)
#define I2C_R_RX_UNDER_MSK         (0x1UL << I2C_R_RX_UNDER_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RX_UNDER bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RX_UNDER interrupt is active ■ 0x0 (INACTIVE): RX_UNDER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_RX_UNDER             I2C_R_RX_UNDER_MSK
#define I2C_R_RX_OVER_POS          (1U)
#define I2C_R_RX_OVER_MSK          (0x1UL << I2C_R_RX_OVER_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RX_OVER bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_RX_OVER interrupt is active ■ 0x0 (INACTIVE): R_RX_OVER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_RX_OVER              I2C_R_RX_OVER_MSK
#define I2C_R_RX_FULL_POS          (2U)
#define I2C_R_RX_FULL_MSK          (0x1UL << I2C_R_RX_FULL_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RX_FULL bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_RX_FULL interrupt is active ■ 0x0 (INACTIVE): R_RX_FULL interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_RX_FULL              I2C_R_RX_FULL_MSK
#define I2C_R_TX_OVER_POS          (3U)
#define I2C_R_TX_OVER_MSK          (0x1UL << I2C_R_TX_OVER_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_TX_OVER bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_TX_OVER interrupt is active ■ 0x0 (INACTIVE): R_TX_OVER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_TX_OVER              I2C_R_TX_OVER_MSK
#define I2C_R_TX_EMPTY_POS         (4U)
#define I2C_R_TX_EMPTY_MSK         (0x1UL << I2C_R_TX_EMPTY_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_TX_EMPTY bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_TX_EMPTY interrupt is active ■ 0x0 (INACTIVE): R_TX_EMPTY interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_TX_EMPTY             I2C_R_TX_EMPTY_MSK
#define I2C_R_RD_REQ_POS           (5U)
#define I2C_R_RD_REQ_MSK           (0x1UL << I2C_R_RD_REQ_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RD_REQ bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_RD_REQ interrupt is active ■ 0x0 (INACTIVE): R_RD_REQ interrupt is inactive Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_R_RD_REQ               I2C_R_RD_REQ_MSK
#define I2C_R_TX_ABRT_POS          (6U)
#define I2C_R_TX_ABRT_MSK          (0x1UL << I2C_R_TX_ABRT_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_TX_ABRT bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_TX_ABRT interrupt is active ■ 0x0 (INACTIVE): R_TX_ABRT interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_TX_ABRT              I2C_R_TX_ABRT_MSK
#define I2C_R_RX_DONE_POS          (7U)
#define I2C_R_RX_DONE_MSK          (0x1UL << I2C_R_RX_DONE_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RX_DONE bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_RX_DONE interrupt is active ■ 0x0 (INACTIVE): R_RX_DONE interrupt is inactive Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_R_RX_DONE              I2C_R_RX_DONE_MSK
#define I2C_R_ACTIVITY_POS         (8U)
#define I2C_R_ACTIVITY_MSK         (0x1UL << I2C_R_ACTIVITY_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_ACTIVITY bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_ACTIVITY interrupt is active ■ 0x0 (INACTIVE): R_ACTIVITY interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_ACTIVITY             I2C_R_ACTIVITY_MSK
#define I2C_R_STOP_DET_POS         (9U)
#define I2C_R_STOP_DET_MSK         (0x1UL << I2C_R_STOP_DET_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_STOP_DET bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_STOP_DET interrupt is active ■ 0x0 (INACTIVE): R_STOP_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_STOP_DET             I2C_R_STOP_DET_MSK
#define I2C_R_START_DET_POS        (10U)
#define I2C_R_START_DET_MSK        (0x1UL << I2C_R_START_DET_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_START_DET bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_START_DET interrupt is active ■ 0x0 (INACTIVE): R_START_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_START_DET            I2C_R_START_DET_MSK
#define I2C_R_GEN_CALL_POS         (11U)
#define I2C_R_GEN_CALL_MSK         (0x1UL << I2C_R_GEN_CALL_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_GEN_CALL bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_GEN_CALL interrupt is active ■ 0x0 (INACTIVE): R_GEN_CALL interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_GEN_CALL             I2C_R_GEN_CALL_MSK
#define I2C_R_RESTART_DET_POS      (12U)
#define I2C_R_RESTART_DET_MSK      (0x1UL << I2C_R_RESTART_DET_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_RESTART_DET bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_RESTART_DET interrupt is active ■ 0x0 (INACTIVE): R_RESTART_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_RESTART_DET          I2C_R_RESTART_DET_MSK
#define I2C_R_MASTER_ON_HOLD_POS   (13U)
#define I2C_R_MASTER_ON_HOLD_MSK   (0x1UL << I2C_R_MASTER_ON_HOLD_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_MASTER_ON_HOLD bit. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): R_MASTER_ON_HOLD interrupt is active ■ 0x0 (INACTIVE): R_MASTER_ON_HOLD interrupt is inactive Exists: Always Volatile: true*/
#define I2C_R_MASTER_ON_HOLD       I2C_R_MASTER_ON_HOLD_MSK
#define I2C_R_SCL_STUCK_AT_LOW_POS (14U)
#define I2C_R_SCL_STUCK_AT_LOW_MSK (0x1UL << I2C_R_SCL_STUCK_AT_LOW_POS) /*!< See I2C_RAW_INTR_STAT for a detailed description of R_SCL_STUCK_AT_LOW bit. Reset Value: 0x0 Values: ■ 0x1 (ACTIVE): R_SCL_STUCK_AT_LOW interrupt is active ■ 0x0 (INACTIVE): R_SCL_STUCK_AT_LOW interrupt is inactive Exists: I2C_BUS_CLEAR_FEATURE==1 Volatile: true*/
#define I2C_R_SCL_STUCK_AT_LOW     I2C_R_SCL_STUCK_AT_LOW_MSK
#define I2C_RSVD_I2C_INTR_STAT_POS (15U)
#define I2C_RSVD_I2C_INTR_STAT_MSK (0x1UL << I2C_RSVD_I2C_INTR_STAT_POS) /*!< I2C_INTR_STAT Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_INTR_STAT     I2C_RSVD_I2C_INTR_STAT_MSK

//I2C_INTR_MASK offsetaddress : 0x30
#define I2C_M_RX_UNDER_POS         (0U)
#define I2C_M_RX_UNDER_MSK         (0x1UL << I2C_M_RX_UNDER_POS) /*!< This bit masks the R_RX_UNDER interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): RX_UNDER interrupt is unmasked ■ 0x0 (ENABLED): RX_UNDER interrupt is masked Exists: Always*/
#define I2C_M_RX_UNDER             I2C_M_RX_UNDER_MSK
#define I2C_M_RX_OVER_POS          (1U)
#define I2C_M_RX_OVER_MSK          (0x1UL << I2C_M_RX_OVER_POS) /*!< This bit masks the R_RX_OVER interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): RX_OVER interrupt is unmasked ■ 0x0 (ENABLED): RX_OVER interrupt is masked Exists: Always*/
#define I2C_M_RX_OVER              I2C_M_RX_OVER_MSK
#define I2C_M_RX_FULL_POS          (2U)
#define I2C_M_RX_FULL_MSK          (0x1UL << I2C_M_RX_FULL_POS) /*!< This bit masks the R_RX_FULL interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): RX_FULL interrupt is unmasked ■ 0x0 (ENABLED): RX_FULL interrupt is masked Exists: Always*/
#define I2C_M_RX_FULL              I2C_M_RX_FULL_MSK
#define I2C_M_TX_OVER_POS          (3U)
#define I2C_M_TX_OVER_MSK          (0x1UL << I2C_M_TX_OVER_POS) /*!< This bit masks the R_TX_OVER interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): TX_OVER interrupt is unmasked ■ 0x0 (ENABLED): TX_OVER interrupt is masked Exists: Always*/
#define I2C_M_TX_OVER              I2C_M_TX_OVER_MSK
#define I2C_M_TX_EMPTY_POS         (4U)
#define I2C_M_TX_EMPTY_MSK         (0x1UL << I2C_M_TX_EMPTY_POS) /*!< This bit masks the R_TX_EMPTY interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): TX_EMPTY interrupt is unmasked ■ 0x0 (ENABLED): TX_EMPTY interrupt is masked Exists: Always*/
#define I2C_M_TX_EMPTY             I2C_M_TX_EMPTY_MSK
#define I2C_M_RD_REQ_POS           (5U)
#define I2C_M_RD_REQ_MSK           (0x1UL << I2C_M_RD_REQ_POS) /*!< This bit masks the R_RD_REQ interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): RD_REQ interrupt is unmasked ■ 0x0 (ENABLED): RD_REQ interrupt is masked Exists: I2C_ULTRA_FAST_MODE==0*/
#define I2C_M_RD_REQ               I2C_M_RD_REQ_MSK
#define I2C_M_TX_ABRT_POS          (6U)
#define I2C_M_TX_ABRT_MSK          (0x1UL << I2C_M_TX_ABRT_POS) /*!< This bit masks the R_TX_ABRT interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): TX_ABORT interrupt is unmasked ■ 0x0 (ENABLED): TX_ABORT interrupt is masked Exists: Always*/
#define I2C_M_TX_ABRT              I2C_M_TX_ABRT_MSK
#define I2C_M_RX_DONE_POS          (7U)
#define I2C_M_RX_DONE_MSK          (0x1UL << I2C_M_RX_DONE_POS) /*!< This bit masks the R_RX_DONE interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): RX_DONE interrupt is unmasked ■ 0x0 (ENABLED): RX_DONE interrupt is masked Exists: I2C_ULTRA_FAST_MODE==0*/
#define I2C_M_RX_DONE              I2C_M_RX_DONE_MSK
#define I2C_M_ACTIVITY_POS         (8U)
#define I2C_M_ACTIVITY_MSK         (0x1UL << I2C_M_ACTIVITY_POS) /*!< This bit masks the R_ACTIVITY interrupt in I2C_INTR_STAT register. Reset value: 0x0 Values: ■ 0x1 (DISABLED): ACTIVITY interrupt is unmasked ■ 0x0 (ENABLED): ACTIVITY interrupt is masked Exists: Always*/
#define I2C_M_ACTIVITY             I2C_M_ACTIVITY_MSK
#define I2C_M_STOP_DET_POS         (9U)
#define I2C_M_STOP_DET_MSK         (0x1UL << I2C_M_STOP_DET_POS) /*!< This bit masks the R_STOP_DET interrupt in I2C_INTR_STAT register. Reset value: 0x0 Values: ■ 0x1 (DISABLED): STOP_DET interrupt is unmasked ■ 0x0 (ENABLED): STOP_DET interrupt is masked Exists: Always*/
#define I2C_M_STOP_DET             I2C_M_STOP_DET_MSK
#define I2C_M_START_DET_POS        (10U)
#define I2C_M_START_DET_MSK        (0x1UL << I2C_M_START_DET_POS) /*!< This bit masks the R_START_DET interrupt in I2C_INTR_STAT register. Reset value: 0x0 Values: ■ 0x1 (DISABLED): START_DET interrupt is unmasked ■ 0x0 (ENABLED): START_DET interrupt is masked Exists: Always*/
#define I2C_M_START_DET            I2C_M_START_DET_MSK
#define I2C_M_GEN_CALL_POS         (11U)
#define I2C_M_GEN_CALL_MSK         (0x1UL << I2C_M_GEN_CALL_POS) /*!< This bit masks the R_GEN_CALL interrupt in I2C_INTR_STAT register. Reset value: 0x1 Values: ■ 0x1 (DISABLED): GEN_CALL interrupt is unmasked ■ 0x0 (ENABLED): GEN_CALL interrupt is masked Exists: Always*/
#define I2C_M_GEN_CALL             I2C_M_GEN_CALL_MSK
#define I2C_M_RESTART_DET_POS      (12U)
#define I2C_M_RESTART_DET_MSK      (0x1UL << I2C_M_RESTART_DET_POS) /*!< This bit masks the R_RESTART_DET interrupt in I2C_INTR_STAT register. Reset value: 0x0 Values: ■ 0x1 (DISABLED): RESTART_DET interrupt is unmasked ■ 0x0 (ENABLED): RESTART_DET interrupt is masked Exists: I2C_SLV_RESTART_DET_EN == 1*/
#define I2C_M_RESTART_DET          I2C_M_RESTART_DET_MSK
#define I2C_M_MASTER_ON_HOLD_POS   (13U)
#define I2C_M_MASTER_ON_HOLD_MSK   (0x1UL << I2C_M_MASTER_ON_HOLD_POS) /*!< This bit masks the R_MASTER_ON_HOLD interrupt in I2C_INTR_STAT register. Reset value: 0x0 Values: ■ 0x1 (DISABLED): MASTER_ON_HOLD interrupt is unmasked ■ 0x0 (ENABLED): MASTER_ON_HOLD interrupt is masked Exists: I2C_DYNAMI2C_TAR_UPDATE == 1 && I2C_EMPTYFIFO_HOLD_MASTER_EN == 1*/
#define I2C_M_MASTER_ON_HOLD       I2C_M_MASTER_ON_HOLD_MSK
#define I2C_M_SCL_STUCK_AT_LOW_POS (14U)
#define I2C_M_SCL_STUCK_AT_LOW_MSK (0x1UL << I2C_M_SCL_STUCK_AT_LOW_POS) /*!< This bit masks the R_SCL_STUCK_AT_LOW interrupt in I2C_INTR_STAT register. Reset Value: 0x0 Values: ■ 0x1 (DISABLED): SCL_STUCK_AT_LOW interrupt is unmasked ■ 0x0 (ENABLED): SCL_STUCK_AT_LOW interrupt is masked Exists: I2C_BUS_CLEAR_FEATURE==1*/
#define I2C_M_SCL_STUCK_AT_LOW     I2C_M_SCL_STUCK_AT_LOW_MSK
#define I2C_RSVD_I2C_INTR_STAT_POS (15U)
#define I2C_RSVD_I2C_INTR_STAT_MSK (0x1UL << I2C_RSVD_I2C_INTR_STAT_POS) /*!< I2C_INTR_STAT Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_INTR_STAT     I2C_RSVD_I2C_INTR_STAT_MSK

//I2C_RAW_INTR_STAT offsetaddress : 0x34
#define I2C_RX_UNDER_POS                   (0U)
#define I2C_RX_UNDER_MSK                   (0x1UL << I2C_RX_UNDER_POS) /*!< Set if the processor attempts to read the receive buffer when it is empty by reading from the I2C_DATA_CMD register. If the module is disabled (I2C_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RX_UNDER interrupt is active ■ 0x0 (INACTIVE): RX_UNDER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_RX_UNDER                       I2C_RX_UNDER_MSK
#define I2C_RX_OVER_POS                    (1U)
#define I2C_RX_OVER_MSK                    (0x1UL << I2C_RX_OVER_POS) /*!< Set if the receive buffer is completely filled to I2C_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device. The DW_apb_i2c acknowledges this, but any data bytes received after the FIFO is full are lost. If the module is disabled (I2C_ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared. Note: If the configuration parameter I2C_RX_FULL_HLD_BUS_EN is enabled and bit 9 of the I2C_CON register (RX_FIFO_FULL_HLD_CTRL) is programmed to HIGH, then the RX_OVER interrupt never occurs, because the Rx FIFO never overflows. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RX_OVER interrupt is active ■ 0x0 (INACTIVE): RX_OVER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_RX_OVER                        I2C_RX_OVER_MSK
#define I2C_RX_FULL_POS                    (2U)
#define I2C_RX_FULL_MSK                    (0x1UL << I2C_RX_FULL_POS) /*!< Set when the receive buffer reaches or goes above the RX_TL threshold in the I2C_RX_TL register. It is automatically cleared by hardware when buffer level goes below the threshold. If the module is disabled (I2C_ENABLE[0]=0), the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. So this bit is cleared once the I2C_ENABLE bit 0 is programmed with a 0, regardless of the activity that continues. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RX_FULL interrupt is active ■ 0x0 (INACTIVE): RX_FULL interrupt is inactive Exists: Always Volatile: true*/
#define I2C_RX_FULL                        I2C_RX_FULL_MSK
#define I2C_TX_OVER_POS                    (3U)
#define I2C_TX_OVER_MSK                    (0x1UL << I2C_TX_OVER_POS) /*!< Set during transmit if the transmit buffer is filled to I2C_TX_BUFFER_DEPTH and the processor attempts to issue another I2C command by writing to the I2C_DATA_CMD register. When the module is disabled, this bit keeps its level until the master or slave state machines go into idle, and when ic_en goes to 0, this interrupt is cleared. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): TX_OVER interrupt is active ■ 0x0 (INACTIVE): TX_OVER interrupt is inactive Exists: Always Volatile: true*/
#define I2C_TX_OVER                        I2C_TX_OVER_MSK
#define I2C_TX_EMPTY_POS                   (4U)
#define I2C_TX_EMPTY_MSK                   (0x1UL << I2C_TX_EMPTY_POS) /*!< The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL selection in the I2C_CON register. ■ When TX_EMPTY_CTRL = 0: This bit is set to 1 when the transmit buffer is at or below the threshold value set in the I2C_TX_TL register. ■ When TX_EMPTY_CTRL = 1: This bit is set to 1 when the transmit buffer is at or below the threshold value set in the I2C_TX_TL register and the transmission of the address/data from the internal shift register for the most recently popped command is completed. It is automatically cleared by hardware when the buffer level goes above the threshold. When I2C_ENABLE[0] is set to 0, the TX FIFO is flushed and held in reset. There the TX FIFO looks like it has no data within it, so this bit is set to 1, provided there is activity in the master or slave state machines. When there is no longer any activity, then with ic_en=0, this bit is set to 0. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): TX_EMPTY interrupt is active ■ 0x0 (INACTIVE): TX_EMPTY interrupt is inactive Exists: Always Volatile: true*/
#define I2C_TX_EMPTY                       I2C_TX_EMPTY_MSK
#define I2C_RD_REQ_POS                     (5U)
#define I2C_RD_REQ_MSK                     (0x1UL << I2C_RD_REQ_POS) /*!< This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C master is attempting to read data from DW_apb_i2c. The DW_apb_i2c holds the I2C bus in a wait state (SCL=0) until this interrupt is serviced, which means that the slave has been addressed by a remote master that is asking for data to be transferred. The processor must respond to this interrupt and then write the requested data to the I2C_DATA_CMD register. This bit is set to 0 just after the processor reads the I2C_CLR_RD_REQ register. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RD_REQ interrupt is active ■ 0x0 (INACTIVE): RD_REQ interrupt is inactive Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_RD_REQ                         I2C_RD_REQ_MSK
#define I2C_TX_ABRT_POS                    (6U)
#define I2C_TX_ABRT_MSK                    (0x1UL << I2C_TX_ABRT_POS) /*!< This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete the intended actions on the contents of the transmit FIFO. This situation can occur both as an I2C master or an I2C slave, and is referred to as a 'transmit abort'. When this bit is set to 1, the I2C_TX_ABRT_SOURCE register indicates the reason why the transmit abort takes places. Note: The DW_apb_i2c flushes/resets/empties only the TX_FIFO whenever there is a transmit abort caused by any of the events tracked by the I2C_TX_ABRT_SOURCE register. The Tx FIFO remains in this flushed state until the register I2C_CLR_TX_ABRT is read. Once this read is performed, the Tx FIFO is then ready to accept more data bytes from the APB interface. RX FIFO flush because of TX_ABRT is controlled by the coreConsultant parameter I2C_AVOID_RX_FIFO_FLUSH_ON_TX_ABRT. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): TX_ABRT interrupt is active ■ 0x0 (INACTIVE): TX_ABRT interrupt is inactive Exists: Always Volatile: true*/
#define I2C_TX_ABRT                        I2C_TX_ABRT_MSK
#define I2C_RX_DONE_POS                    (7U)
#define I2C_RX_DONE_MSK                    (0x1UL << I2C_RX_DONE_POS) /*!< When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a transmitted byte. This occurs on the last byte of the transmission, indicating that the transmission is done. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RX_DONE interrupt is active ■ 0x0 (INACTIVE): RX_DONE interrupt is inactive Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_RX_DONE                        I2C_RX_DONE_MSK
#define I2C_RAW_INTR_STAT_I2C_ACTIVITY_POS (8U)
#define I2C_RAW_INTR_STAT_I2C_ACTIVITY_MSK (0x1UL << I2C_RAW_INTR_STAT_I2C_ACTIVITY_POS) /*!< This bit captures DW_apb_i2c activity and stays set until it is cleared. There are four ways to clear it: ■ Disabling the DW_apb_i2c ■ Reading the I2C_CLR_ACTIVITY register ■ Reading the I2C_CLR_INTR register ■ System reset Once this bit is set, it stays set unless one of the four methods is used to clear it. Even if the DW_apb_i2c module is idle, this bit remains set until cleared, indicating that there was activity on the bus. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RAW_INTR_ACTIVITY interrupt is active ■ 0x0 (INACTIVE): RAW_INTR_ACTIVITY interrupt is inactive Exists: Always Volatile: true*/
#define I2C_RAW_INTR_STAT_I2C_ACTIVITY     I2C_RAW_INTR_STAT_I2C_ACTIVITY_MSK
#define I2C_STOP_DET_POS                   (9U)
#define I2C_STOP_DET_MSK                   (0x1UL << I2C_STOP_DET_POS) /*!< Indicates whether a STOP condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode. In Slave Mode: ■ If I2C_CON[7]=1'b1 (STOP_DET_IFADDRESSED), the STOP_DET interrupt will be issued only if slave is addressed. Note: During a general call address, this slave does not issue a STOP_DET interrupt if STOP_DET_IF_ADDRESSED=1'b1, even if the slave responds to the general call address by generating ACK. The STOP_DET interrupt is generated only when the transmitted address matches the slave address (SAR). ■ If I2C_CON[7]=1'b0 (STOP_DET_IFADDRESSED), the STOP_DET interrupt is issued irrespective of whether it is being addressed. In Master Mode: ■ If I2C_CON[10]=1'b1 (STOP_DET_IF_MASTER_ACTIVE),the STOP_DET interrupt will be issued only if Master is active. ■ If I2C_CON[10]=1'b0 (STOP_DET_IFADDRESSED),the STOP_DET interrupt will be issued irrespective of whether master is active or not. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): STOP_DET interrupt is active ■ 0x0 (INACTIVE): STOP_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_STOP_DET                       I2C_STOP_DET_MSK
#define I2C_START_DET_POS                  (10U)
#define I2C_START_DET_MSK                  (0x1UL << I2C_START_DET_POS) /*!< Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether DW_apb_i2c is operating in slave or master mode. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): START_DET interrupt is active ■ 0x0 (INACTIVE): START_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_START_DET                      I2C_START_DET_MSK
#define I2C_GEN_CALL_POS                   (11U)
#define I2C_GEN_CALL_MSK                   (0x1UL << I2C_GEN_CALL_POS) /*!< Set only when a General Call address is received and it is acknowledged. It stays set until it is cleared either by disabling DW_apb_i2c or when the CPU reads bit 0 of the I2C_CLR_GEN_CALL register. DW_apb_i2c stores the received data in the Rx buffer. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): GEN_CALL interrupt is active ■ 0x0 (INACTIVE): GEN_CALL interrupt is inactive Exists: Always Volatile: true*/
#define I2C_GEN_CALL                       I2C_GEN_CALL_MSK
#define I2C_RESTART_DET_POS                (12U)
#define I2C_RESTART_DET_MSK                (0x1UL << I2C_RESTART_DET_POS) /*!< Indicates whether a RESTART condition has occurred on the I2C interface when DW_apb_i2c is operating in Slave mode and the slave is being addressed. Enabled only when I2C_SLV_RESTART_DET_EN=1. Note: However, in high-speed mode or during a START BYTE transfer, the RESTART comes before the address field as per the I2C protocol. In this case, the slave is not the addressed slave when the RESTART is issued, therefore DW_apb_i2c does not generate the RESTART_DET interrupt. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): RESTART_DET interrupt is active ■ 0x0 (INACTIVE): RESTART_DET interrupt is inactive Exists: Always Volatile: true*/
#define I2C_RESTART_DET                    I2C_RESTART_DET_MSK
#define I2C_MASTER_ON_HOLD_POS             (13U)
#define I2C_MASTER_ON_HOLD_MSK             (0x1UL << I2C_MASTER_ON_HOLD_POS) /*!< Indicates whether master is holding the bus and TX FIFO is empty. Enabled only when I2C_DYNAMI2C_TAR_UPDATE=1 and I2C_EMPTYFIFO_HOLD_MASTER_EN=1. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): MASTER_ON_HOLD interrupt is active ■ 0x0 (INACTIVE): MASTER_ON_HOLD interrupt is inactive Exists: Always Volatile: true*/
#define I2C_MASTER_ON_HOLD                 I2C_MASTER_ON_HOLD_MSK
#define I2C_SCL_STUCK_AT_LOW_POS           (14U)
#define I2C_SCL_STUCK_AT_LOW_MSK           (0x1UL << I2C_SCL_STUCK_AT_LOW_POS) /*!< Indicates whether the SCL Line is stuck at low for the I2C_SCL_STUCK_LOW_TIMEOUT number of ic_clk periods. Enabled only when I2C_BUS_CLEAR_FEATURE=1 and I2C_ULTRA_FAST_MODE=0. Reset Value: 0x0 Values: ■ 0x1 (ACTIVE): SCL_STUCK_AT_LOW interrupt is active ■ 0x0 (INACTIVE): SCL_STUCK_AT_LOW interrupt is inactive. Exists: I2C_BUS_CLEAR_FEATURE==1 Volatile: true*/
#define I2C_SCL_STUCK_AT_LOW               I2C_SCL_STUCK_AT_LOW_MSK
#define I2C_RSVD_I2C_RAW_INTR_STAT_POS     (15U)
#define I2C_RSVD_I2C_RAW_INTR_STAT_MSK     (0x1UL << I2C_RSVD_I2C_RAW_INTR_STAT_POS) /*!< I2C_RAW_INTR_STAT Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_RAW_INTR_STAT         I2C_RSVD_I2C_RAW_INTR_STAT_MSK

//I2C_RX_TL offsetaddress : 0x38
#define I2C_RX_TL_POS          (0U)
#define I2C_RX_TL_MSK          (0x1UL << I2C_RX_TL_POS) /*!< Receive FIFO Threshold Level. Controls the level of entries (or above) that triggers the RX_FULL interrupt (bit 2 in I2C_RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that hardware does not allow this value to be set to a value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer. A value of 0 sets the threshold for 1 entry, and a value of 255 sets the threshold for 256 entries. Reset value: I2C_RX_TL configuration parameter Exists: Always*/
#define I2C_RX_TL              I2C_RX_TL_MSK
#define I2C_RSVD_I2C_RX_TL_POS (8U)
#define I2C_RSVD_I2C_RX_TL_MSK (0x1UL << I2C_RSVD_I2C_RX_TL_POS) /*!< I2C_RX_TL Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_RX_TL     I2C_RSVD_I2C_RX_TL_MSK

//I2C_TX_TL offsetaddress : 0x3c
#define I2C_TX_TL_POS          (0U)
#define I2C_TX_TL_MSK          (0x1UL << I2C_TX_TL_POS) /*!< Transmit FIFO Threshold Level. Controls the level of entries (or below) that trigger the TX_EMPTY interrupt (bit 4 in I2C_RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that it may not be set to value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer. A value of 0 sets the threshold for 0 entries, and a value of 255 sets the threshold for 255 entries. Reset value: I2C_TX_TL configuration parameter Exists: Always*/
#define I2C_TX_TL              I2C_TX_TL_MSK
#define I2C_RSVD_I2C_TX_TL_POS (8U)
#define I2C_RSVD_I2C_TX_TL_MSK (0x1UL << I2C_RSVD_I2C_TX_TL_POS) /*!< I2C_TX_TL Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_TX_TL     I2C_RSVD_I2C_TX_TL_MSK

//I2C_CLR_INTR offsetaddress : 0x40
#define I2C_CLR_INTR_POS          (0U)
#define I2C_CLR_INTR_MSK          (0x1UL << I2C_CLR_INTR_POS) /*!< Read this register to clear the combined interrupt, all individual interrupts, and the I2C_TX_ABRT_SOURCE register. This bit does not clear hardware clearable interrupts but software clearable interrupts. Refer to Bit 9 of the I2C_TX_ABRT_SOURCE register for an exception to clearing I2C_TX_ABRT_SOURCE. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_INTR              I2C_CLR_INTR_MSK
#define I2C_RSVD_I2C_CLR_INTR_POS (1U)
#define I2C_RSVD_I2C_CLR_INTR_MSK (0x1UL << I2C_RSVD_I2C_CLR_INTR_POS) /*!< CLR_INTR Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_INTR     I2C_RSVD_I2C_CLR_INTR_MSK

//I2C_CLR_RX_UNDER offsetaddress : 0x44
#define I2C_CLR_RX_UNDER_POS          (0U)
#define I2C_CLR_RX_UNDER_MSK          (0x1UL << I2C_CLR_RX_UNDER_POS) /*!< Read this register to clear the RX_UNDER interrupt (bit 0) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_RX_UNDER              I2C_CLR_RX_UNDER_MSK
#define I2C_RSVD_I2C_CLR_RX_UNDER_POS (1U)
#define I2C_RSVD_I2C_CLR_RX_UNDER_MSK (0x1UL << I2C_RSVD_I2C_CLR_RX_UNDER_POS) /*!< I2C_CLR_RX_UNDER Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_RX_UNDER     I2C_RSVD_I2C_CLR_RX_UNDER_MSK

//I2C_CLR_RX_OVER offsetaddress : 0x48
#define I2C_CLR_RX_OVER_POS          (0U)
#define I2C_CLR_RX_OVER_MSK          (0x1UL << I2C_CLR_RX_OVER_POS) /*!< Read this register to clear the RX_OVER interrupt (bit 1) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_RX_OVER              I2C_CLR_RX_OVER_MSK
#define I2C_RSVD_I2C_CLR_RX_OVER_POS (1U)
#define I2C_RSVD_I2C_CLR_RX_OVER_MSK (0x1UL << I2C_RSVD_I2C_CLR_RX_OVER_POS) /*!< I2C_CLR_RX_OVER Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_RX_OVER     I2C_RSVD_I2C_CLR_RX_OVER_MSK

//I2C_CLR_TX_OVER offsetaddress : 0x4c
#define I2C_CLR_TX_OVER_POS          (0U)
#define I2C_CLR_TX_OVER_MSK          (0x1UL << I2C_CLR_TX_OVER_POS) /*!< Read this register to clear the TX_OVER interrupt (bit 3) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_TX_OVER              I2C_CLR_TX_OVER_MSK
#define I2C_RSVD_I2C_CLR_TX_OVER_POS (1U)
#define I2C_RSVD_I2C_CLR_TX_OVER_MSK (0x1UL << I2C_RSVD_I2C_CLR_TX_OVER_POS) /*!< I2C_CLR_TX_OVER Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_TX_OVER     I2C_RSVD_I2C_CLR_TX_OVER_MSK

//I2C_CLR_RD_REQ offsetaddress : 0x50
#define I2C_CLR_RD_REQ_POS          (0U)
#define I2C_CLR_RD_REQ_MSK          (0x1UL << I2C_CLR_RD_REQ_POS) /*!< Read this register to clear the RD_REQ interrupt (bit 5) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_RD_REQ              I2C_CLR_RD_REQ_MSK
#define I2C_RSVD_I2C_CLR_RD_REQ_POS (1U)
#define I2C_RSVD_I2C_CLR_RD_REQ_MSK (0x1UL << I2C_RSVD_I2C_CLR_RD_REQ_POS) /*!< I2C_CLR_RD_REQ Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_RD_REQ     I2C_RSVD_I2C_CLR_RD_REQ_MSK

//I2C_CLR_TX_ABRT offsetaddress : 0x54
#define I2C_CLR_TX_ABRT_POS          (0U)
#define I2C_CLR_TX_ABRT_MSK          (0x1UL << I2C_CLR_TX_ABRT_POS) /*!< Read this register to clear the TX_ABRT interrupt (bit 6) of the I2C_RAW_INTR_STAT register, and the I2C_TX_ABRT_SOURCE register. This also releases the TX FIFO from the flushed/reset state, allowing more writes to the TX FIFO. Refer to Bit 9 of the I2C_TX_ABRT_SOURCE register for an exception to clearing I2C_TX_ABRT_SOURCE. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_TX_ABRT              I2C_CLR_TX_ABRT_MSK
#define I2C_RSVD_I2C_CLR_TX_ABRT_POS (1U)
#define I2C_RSVD_I2C_CLR_TX_ABRT_MSK (0x1UL << I2C_RSVD_I2C_CLR_TX_ABRT_POS) /*!< I2C_CLR_TX_ABRT Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_TX_ABRT     I2C_RSVD_I2C_CLR_TX_ABRT_MSK

//I2C_CLR_RX_DONE offsetaddress : 0x58
#define I2C_CLR_RX_DONE_POS          (0U)
#define I2C_CLR_RX_DONE_MSK          (0x1UL << I2C_CLR_RX_DONE_POS) /*!< Read this register to clear the RX_DONE interrupt (bit 7) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_RX_DONE              I2C_CLR_RX_DONE_MSK
#define I2C_RSVD_I2C_CLR_RX_DONE_POS (1U)
#define I2C_RSVD_I2C_CLR_RX_DONE_MSK (0x1UL << I2C_RSVD_I2C_CLR_RX_DONE_POS) /*!< I2C_CLR_RX_DONE Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_RX_DONE     I2C_RSVD_I2C_CLR_RX_DONE_MSK

//I2C_CLR_ACTIVITY offsetaddress : 0x5c
#define I2C_CLR_ACTIVITY_POS          (0U)
#define I2C_CLR_ACTIVITY_MSK          (0x1UL << I2C_CLR_ACTIVITY_POS) /*!< Reading this register clears the ACTIVITY interrupt if the I2C is not active anymore. If the I2C module is still active on the bus, the ACTIVITY interrupt bit continues to be set. It is automatically cleared by hardware if the module is disabled and if there is no further activity on the bus. The value read from this register to get status of the ACTIVITY interrupt (bit 8) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_ACTIVITY              I2C_CLR_ACTIVITY_MSK
#define I2C_RSVD_I2C_CLR_ACTIVITY_POS (1U)
#define I2C_RSVD_I2C_CLR_ACTIVITY_MSK (0x1UL << I2C_RSVD_I2C_CLR_ACTIVITY_POS) /*!< I2C_CLR_ACTIVITY Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_ACTIVITY     I2C_RSVD_I2C_CLR_ACTIVITY_MSK

//I2C_CLR_STOP_DET offsetaddress : 0x60
#define I2C_CLR_STOP_DET_POS          (0U)
#define I2C_CLR_STOP_DET_MSK          (0x1UL << I2C_CLR_STOP_DET_POS) /*!< Read this register to clear the STOP_DET interrupt (bit 9) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_STOP_DET              I2C_CLR_STOP_DET_MSK
#define I2C_RSVD_I2C_CLR_STOP_DET_POS (1U)
#define I2C_RSVD_I2C_CLR_STOP_DET_MSK (0x1UL << I2C_RSVD_I2C_CLR_STOP_DET_POS) /*!< I2C_CLR_STOP_DET Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_STOP_DET     I2C_RSVD_I2C_CLR_STOP_DET_MSK

//I2C_CLR_START_DET offsetaddress : 0x64
#define I2C_CLR_START_DET_POS          (0U)
#define I2C_CLR_START_DET_MSK          (0x1UL << I2C_CLR_START_DET_POS) /*!< Read this register to clear the START_DET interrupt (bit 10) of the I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_START_DET              I2C_CLR_START_DET_MSK
#define I2C_RSVD_I2C_CLR_START_DET_POS (1U)
#define I2C_RSVD_I2C_CLR_START_DET_MSK (0x1UL << I2C_RSVD_I2C_CLR_START_DET_POS) /*!< I2C_CLR_START_DET Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_START_DET     I2C_RSVD_I2C_CLR_START_DET_MSK

//I2C_CLR_GEN_CALL offsetaddress : 0x68
#define I2C_CLR_GEN_CALL_POS          (0U)
#define I2C_CLR_GEN_CALL_MSK          (0x1UL << I2C_CLR_GEN_CALL_POS) /*!< Read this register to clear the GEN_CALL interrupt (bit 11) of I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_GEN_CALL              I2C_CLR_GEN_CALL_MSK
#define I2C_RSVD_I2C_CLR_GEN_CALL_POS (1U)
#define I2C_RSVD_I2C_CLR_GEN_CALL_MSK (0x1UL << I2C_RSVD_I2C_CLR_GEN_CALL_POS) /*!< I2C_CLR_GEN_CALL Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_GEN_CALL     I2C_RSVD_I2C_CLR_GEN_CALL_MSK

//I2C_ENABLE offsetaddress : 0x6c
#define I2C_ENABLE_POS                    (0U)
#define I2C_ENABLE_MSK                    (0x1UL << I2C_ENABLE_POS) /*!< Controls whether the DW_apb_i2c is enabled. ■ 0: Disables DW_apb_i2c (TX and RX FIFOs are held in an erased state) ■ 1: Enables DW_apb_i2c Software can disable DW_apb_i2c while it is active. However, it is important that care be taken to ensure that DW_apb_i2c is disabled properly. A recommended procedure is described in "Disabling DW_apb_i2c". When DW_apb_i2c is disabled, the following occurs: ■ The TX FIFO and RX FIFO get flushed. ■ Status bits in the I2C_INTR_STAT register are still active until DW_apb_i2c goes into IDLE state. If the module is transmitting, it stops as well as deletes the contents of the transmit buffer after the current transfer is complete. If the module is receiving, the DW_apb_i2c stops the current transfer at the end of the current byte and does not acknowledge the transfer. In systems with asynchronous pclk and ic_clk when I2C_CLK_TYPE parameter set to asynchronous (1), there is a two ic_clk delay when enabling or disabling the DW_apb_i2c. For a detailed description on how to disable DW_apb_i2c, refer to "Disabling DW_apb_i2c" Reset value: 0x0 Values: ■ 0x1 (ENABLED): I2C is enabled ■ 0x0 (DISABLED): I2C is disabled Exists: Always*/
#define I2C_ENABLE                        I2C_ENABLE_MSK
#define I2C_ABORT_POS                     (1U)
#define I2C_ABORT_MSK                     (0x1UL << I2C_ABORT_POS) /*!< When set, the controller initiates the transfer abort. ■ 0: ABORT not initiated or ABORT done ■ 1: ABORT operation in progress The software can abort the I2C transfer in master mode by setting this bit. The software can set this bit only when ENABLE is already set; otherwise, the controller ignores any write to ABORT bit. The software cannot clear the ABORT bit once set. In response to an ABORT, the controller issues a STOP and flushes the Tx FIFO after completing the current transfer, then sets the TX_ABORT interrupt after the abort operation. The ABORT bit is cleared automatically after the abort operation. For a detailed description on how to abort I2C transfers, refer to "Aborting I2C Transfers". Reset value: 0x0 Values: ■ 0x1 (ENABLED): ABORT operation in progress ■ 0x0 (DISABLE): ABORT operation not in progress Exists: Always*/
#define I2C_ABORT                         I2C_ABORT_MSK
#define I2C_TX_CMD_BLOCK_POS              (2U)
#define I2C_TX_CMD_BLOCK_MSK              (0x1UL << I2C_TX_CMD_BLOCK_POS) /*!< In Master mode: ■ 1'b1: Blocks the transmission of data on I2C bus even if Tx FIFO has data to transmit. ■ 1'b0: The transmission of data starts on I2C bus automatically, as soon as the first data is available in the Tx FIFO. Note: To block the execution of Master commands, set the TX_CMD_BLOCK bit only when Tx FIFO is empty (I2C_STATUS[2]==1) and Master is in Idle state (I2C_STATUS[5] == 0). Any further commands put in the Tx FIFO are not executed until TX_CMD_BLOCK bit is unset.Reset value: I2C_TX_CMD_BLOCK_DEFAULT Values: ■ 0x1 (BLOCKED): Tx Command execution blocked ■ 0x0 (NOT_BLOCKED): Tx Command execution not blocked Exists: Always*/
#define I2C_TX_CMD_BLOCK                  I2C_TX_CMD_BLOCK_MSK
#define I2C_SDA_STUCK_RECOVERY_ENABLE_POS (3U)
#define I2C_SDA_STUCK_RECOVERY_ENABLE_MSK (0x1UL << I2C_SDA_STUCK_RECOVERY_ENABLE_POS) /*!< If SDA is stuck at low indicated through the TX_ABORT interrupt (I2C_TX_ABRT_SOURCE[17]), then this bit is used as a control knob to initiate the SDA Recovery Mechanism (that is, send at most 9 SCL clocks and STOP to release the SDA line) and then this bit gets auto clear. Reset value: 0x0. Values: ■ 0x1 (SDA_STUCK_RECOVERY_ENABLED): Master initates the SDA stuck at low recovery mechanism. ■ 0x0 (SDA_STUCK_RECOVERY_DISABLED): Master disabled the SDA stuck at low recovery mechanism. Exists: I2C_BUS_CLEAR_FEATURE==1*/
#define I2C_SDA_STUCK_RECOVERY_ENA        BLE I2C_SDA_STUCK_RECOVERY_ENABLE_MSK
#define I2C_RSVD_I2C_ENABLE_1_POS         (4U)
#define I2C_RSVD_I2C_ENABLE_1_MSK         (0x1UL << I2C_RSVD_I2C_ENABLE_1_POS) /*!< RSVD_I2C_ENABLE_1 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_ENABLE_1             I2C_RSVD_I2C_ENABLE_1_MSK
#define I2C_SMBUS_CLK_RESET_POS           (16U)
#define I2C_SMBUS_CLK_RESET_MSK           (0x1UL << I2C_SMBUS_CLK_RESET_POS) /*!< This bit is used in SMBus Host mode to initiate the SMBus Master Clock Reset. This bit should be enabled only when Master is in idle. Whenever this bit is enabled, the SMBCLK is held low for the I2C_SCL_STUCK_TIMEOUT ic_clk cycles to reset the SMBus slave devices. Reset value: 0x0. Values: ■ 0x1 (ENABLED): Master initates the SMBUS Clock Reset Mechanism. ■ 0x0 (DISABLED): Master will not initates SMBUS Clock Reset Mechanism. Exists: I2C_SMBUS==1*/
#define I2C_SMBUS_CLK_RESET               I2C_SMBUS_CLK_RESET_MSK
#define I2C_SMBUS_SUSPEND_EN_POS          (17U)
#define I2C_SMBUS_SUSPEND_EN_MSK          (0x1UL << I2C_SMBUS_SUSPEND_EN_POS) /*!< The SMBUS_SUSPEND_EN register bit is used to control assertion and de-assertion of SMBSUS signal. ■ 0: De-assert SMBSUS signal ■ 1: Assert SMBSUS signal Reset value: 0x0. Values: ■ 0x1 (ENABLED): Host/Master initates the SMBUS system to enter Suspend Mode. ■ 0x0 (DISABLED): Host/Master will not initates the SMBUS system to enter Suspend Mode. Exists: I2C_SMBUS_SUSPEND_ALERT==1*/
#define I2C_SMBUS_SUSPEND_EN              I2C_SMBUS_SUSPEND_EN_MSK
#define I2C_SMBUS_ALERT_EN_POS            (18U)
#define I2C_SMBUS_ALERT_EN_MSK            (0x1UL << I2C_SMBUS_ALERT_EN_POS) /*!< The SMBUS_ALERT_CTRL register bit is used to control assertion of SMBALERT signal. - 1: Assert SMBALERT signal This register bit is auto-cleared after detection of Acknowledgement from master for Alert Response address. Reset value: 0x0. Values: ■ 0x1 (ALERT_ENABLED): Slave initates the Alert signal to indicate SMBus Host ■ 0x0 (SUSPEND_DISABLED): Slave will not initates the Alert signal to indicate SMBus Host. Exists: I2C_SMBUS_SUSPEND_ALERT==1*/
#define I2C_SMBUS_ALERT_EN                I2C_SMBUS_ALERT_EN_MSK
#define I2C_RSVD_I2C_ENABLE_2_POS         (19U)
#define I2C_RSVD_I2C_ENABLE_2_MSK         (0x1UL << I2C_RSVD_I2C_ENABLE_2_POS) /*!< I2C_ENABLE Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_ENABLE_2             I2C_RSVD_I2C_ENABLE_2_MSK

//I2C_STATUS offsetaddress : 0x70
#define I2C_ACTIVITY_POS                  (0U)
#define I2C_ACTIVITY_MSK                  (0x1UL << I2C_ACTIVITY_POS) /*!< I2C Activity Status.Reset value: 0x0 Values: ■ 0x1 (ACTIVE): I2C is active ■ 0x0 (INACTIVE): I2C is idle Exists: Always Volatile: true*/
#define I2C_ACTIVITY                      I2C_ACTIVITY_MSK
#define I2C_TFNF_POS                      (1U)
#define I2C_TFNF_MSK                      (0x1UL << I2C_TFNF_POS) /*!< Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty locations, and is cleared when the FIFO is full. ■ 0: Transmit FIFO is full ■ 1: Transmit FIFO is not full Reset value: 0x1 Values: ■ 0x1 (NOT_FULL): Tx FIFO not full ■ 0x0 (FULL): Tx FIFO is full Exists: Always Volatile: true*/
#define I2C_TFNF                          I2C_TFNF_MSK
#define I2C_TFE_POS                       (2U)
#define I2C_TFE_MSK                       (0x1UL << I2C_TFE_POS) /*!< Transmit FIFO Completely Empty. When the transmit FIFO is completely empty, this bit is set. When it contains one or more valid entries, this bit is cleared. This bit field does not request an interrupt. ■ 0: Transmit FIFO is not empty ■ 1: Transmit FIFO is empty Reset value: 0x1 Values: ■ 0x1 (EMPTY): Tx FIFO is empty ■ 0x0 (NON_EMPTY): Tx FIFO not empty Exists: Always Volatile: true*/
#define I2C_TFE                           I2C_TFE_MSK
#define I2C_RFNE_POS                      (3U)
#define I2C_RFNE_MSK                      (0x1UL << I2C_RFNE_POS) /*!< Receive FIFO Not Empty. This bit is set when the receive FIFO contains one or more entries; it is cleared when the receive FIFO is empty. ■ 0: Receive FIFO is empty ■ 1: Receive FIFO is not empty Reset value: 0x0 Values: ■ 0x1 (NOT_EMPTY): Rx FIFO not empty ■ 0x0 (EMPTY): Rx FIFO is empty Exists: Always Volatile: true*/
#define I2C_RFNE                          I2C_RFNE_MSK
#define I2C_RFF_POS                       (4U)
#define I2C_RFF_MSK                       (0x1UL << I2C_RFF_POS) /*!< Receive FIFO Completely Full. When the receive FIFO is completely full, this bit is set. When the receive FIFO contains one or more empty location, this bit is cleared. ■ 0: Receive FIFO is not full ■ 1: Receive FIFO is full Reset value: 0x0 Values: ■ 0x1 (FULL): Rx FIFO is full ■ 0x0 (NOT_FULL): Rx FIFO not full Exists: Always Volatile: true*/
#define I2C_RFF                           I2C_RFF_MSK
#define I2C_MST_ACTIVITY_POS              (5U)
#define I2C_MST_ACTIVITY_MSK              (0x1UL << I2C_MST_ACTIVITY_POS) /*!< Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in the IDLE state, this bit is set. ■ 0: Master FSM is in IDLE state so the Master part of DW_apb_i2c is not Active ■ 1: Master FSM is not in IDLE state so the Master part of DW_apb_i2c is Active Note: I2C_STATUS[0]-that is, ACTIVITY bit-is the OR of SLV_ACTIVITY and MST_ACTIVITY bits. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Master not idle ■ 0x0 (IDLE): Master is idle Exists: Always Volatile: true*/
#define I2C_MST_ACTIVITY                  I2C_MST_ACTIVITY_MSK
#define I2C_SLV_ACTIVITY_POS              (6U)
#define I2C_SLV_ACTIVITY_MSK              (0x1UL << I2C_SLV_ACTIVITY_POS) /*!< Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in the IDLE state, this bit is set. ■ 0: Slave FSM is in IDLE state so the Slave part of DW_apb_i2c is not Active ■ 1: Slave FSM is not in IDLE state so the Slave part of DW_apb_i2c is Active Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Slave not idle ■ 0x0 (IDLE): Slave is idle Exists: Always Volatile: true*/
#define I2C_SLV_ACTIVITY                  I2C_SLV_ACTIVITY_MSK
#define I2C_MST_HOLD_TX_FIFO_EMPTY_POS    (7U)
#define I2C_MST_HOLD_TX_FIFO_EMPTY_MSK    (0x1UL << I2C_MST_HOLD_TX_FIFO_EMPTY_POS) /*!< If the I2C_EMPTYFIFO_HOLD_MASTER_EN parameter is set to 1, the DW_apb_i2c master stalls the write transfer when Tx FIFO is empty, and the the last byte does not have the Stop bit set. This bit indicates the BUS hold when the master holds the bus because of the Tx FIFO being empty, and the the previous transferred command does not have the Stop bit set. (This kind of Bus hold is applicable if I2C_EMPTYFIFO_HOLD_MASTER_EN is set to 1). Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Master holds the bus due to Tx FIFO is empty ■ 0x0 (INACTIVE): Master is not holding the bus or Bus hold is not due to Tx FIFO is empty Exists: I2C_STAT_FOR_CLK_STRETCH == 1 Volatile: true*/
#define I2C_MST_HOLD_TX_FIFO_EMPTY        I2C_MST_HOLD_TX_FIFO_EMPTY_MSK
#define I2C_MST_HOLD_RX_FIFO_FULL_POS     (8U)
#define I2C_MST_HOLD_RX_FIFO_FULL_MSK     (0x1UL << I2C_MST_HOLD_RX_FIFO_FULL_POS) /*!< This bit indicates the BUS Hold in Master mode due to Rx FIFO is Full and additional byte has been received (This kind of Bus hold is applicable if I2C_RX_FULL_HLD_BUS_EN is set to 1). Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Master holds the bus due to Rx FIFO is full ■ 0x0 (INACTIVE): Master is not holding the bus or Bus hold is not due to Rx FIFO is full Exists: I2C_STAT_FOR_CLK_STRETCH == 1 Volatile: true*/
#define I2C_MST_HOLD_RX_FIFO_FULL         I2C_MST_HOLD_RX_FIFO_FULL_MSK
#define I2C_SLV_HOLD_TX_FIFO_EMPTY_POS    (9U)
#define I2C_SLV_HOLD_TX_FIFO_EMPTY_MSK    (0x1UL << I2C_SLV_HOLD_TX_FIFO_EMPTY_POS) /*!< This bit indicates the BUS Hold in Slave mode for the Read request when the Tx FIFO is empty. The Bus is in hold until the Tx FIFO has data to Transmit for the read request. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Slave holds the bus due to Tx FIFO is empty ■ 0x0 (INACTIVE): Slave is not holding the bus or Bus hold is not due to Tx FIFO is empty Exists: I2C_STAT_FOR_CLK_STRETCH == 1 Volatile: true*/
#define I2C_SLV_HOLD_TX_FIFO_EMPTY        I2C_SLV_HOLD_TX_FIFO_EMPTY_MSK
#define I2C_SLV_HOLD_RX_FIFO_FULL_POS     (10U)
#define I2C_SLV_HOLD_RX_FIFO_FULL_MSK     (0x1UL << I2C_SLV_HOLD_RX_FIFO_FULL_POS) /*!< This bit indicates the BUS Hold in Slave mode due to Rx FIFO is Full and an additional byte has been received (This kind of Bus hold is applicable if I2C_RX_FULL_HLD_BUS_EN is set to 1). Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Slave holds the bus due to Rx FIFO is full ■ 0x0 (INACTIVE): Slave is not holding the bus or Bus hold is not due to Rx FIFO is full Exists: I2C_STAT_FOR_CLK_STRETCH == 1 Volatile: true*/
#define I2C_SLV_HOLD_RX_FIFO_FULL         I2C_SLV_HOLD_RX_FIFO_FULL_MSK
#define I2C_SDA_STUCK_NOT_RECOVERED_POS   (11U)
#define I2C_SDA_STUCK_NOT_RECOVERED_MSK   (0x1UL << I2C_SDA_STUCK_NOT_RECOVERED_POS) /*!< This bit indicates that SDA stuck at low is not recovered after the recovery mechanism. In Slave mode, this register bit is not applicable. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): SDA Stuck at low is recovered after recovery mechanism. ■ 0x0 (INACTIVE): SDA Stuck at low is not recovered after recovery mechanism. Exists: I2C_BUS_CLEAR_FEATURE==1 Volatile: true*/
#define I2C_SDA_STUCK_NOT_RECOVERED       I2C_SDA_STUCK_NOT_RECOVERED_MSK
#define I2C_RSVD_I2C_STATUS_1_POS         (12U)
#define I2C_RSVD_I2C_STATUS_1_MSK         (0x1UL << I2C_RSVD_I2C_STATUS_1_POS) /*!< RSVD_I2C_STATUS_1 Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_STATUS_1             I2C_RSVD_I2C_STATUS_1_MSK
#define I2C_SMBUS_QUI2CK_CMD_BIT_POS      (16U)
#define I2C_SMBUS_QUI2CK_CMD_BIT_MSK      (0x1UL << I2C_SMBUS_QUI2CK_CMD_BIT_POS) /*!< This bit indicates the R/W bit of the Quick command received. This bit will be cleared after the user has read this bit. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): SMBUS QUI2CK CMD Read/write is set to 1. ■ 0x0 (INACTIVE): SMBUS QUI2CK CMD Read/write is set to 0. Exists: I2C_SMBUS==1 Volatile: true*/
#define I2C_SMBUS_QUI2CK_CMD_BIT          I2C_SMBUS_QUI2CK_CMD_BIT_MSK
#define I2C_SMBUS_SLAVE_ADDR_VALID_POS    (17U)
#define I2C_SMBUS_SLAVE_ADDR_VALID_MSK    (0x1UL << I2C_SMBUS_SLAVE_ADDR_VALID_POS) /*!< This bit indicates whether the slave address (ic_sar) is valid or not. Reset value: I2C_PERSISTANT_SLV_ADDR_DEFAULT Values: ■ 0x1 (ACTIVE): SMBUS Slave Address is Valid. ■ 0x0 (INACTIVE): SMBUS SLave Address is not valid. Exists: I2C_SMBUS_ARP==1 Volatile: true*/
#define I2C_SMBUS_SLAVE_ADDR_VALID        I2C_SMBUS_SLAVE_ADDR_VALID_MSK
#define I2C_SMBUS_SLAVE_ADDR_RESOLVED_POS (18U)
#define I2C_SMBUS_SLAVE_ADDR_RESOLVED_MSK (0x1UL << I2C_SMBUS_SLAVE_ADDR_RESOLVED_POS) /*!< This bit indicates whether the slave address (ic_sar) is resolved by the ARP Master. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): SMBUS Slave Address is Resolved. ■ 0x0 (INACTIVE): SMBUS Slave Address is not Resolved. Exists: I2C_SMBUS_ARP==1 Volatile: true*/
#define I2C_SMBUS_SLAVE_ADDR_RESOLVED     I2C_SMBUS_SLAVE_ADDR_RESOLV ED_MSK
#define I2C_SMBUS_SUSPEND_STATUS_POS      (19U)
#define I2C_SMBUS_SUSPEND_STATUS_MSK      (0x1UL << I2C_SMBUS_SUSPEND_STATUS_POS) /*!< This bit indicates the status of the SMBus Suspend signal (ic_smbsus_in_n). This signal is asserted when the SMBus Suspend signal is asserted by the SMBus Host. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): SMBUS System is in Suspended mode. ■ 0x0 (INACTIVE): SMBUS System is not in Suspended mode. Exists: I2C_SMBUS_SUSPEND_ALERT==1 Volatile: true*/
#define I2C_SMBUS_SUSPEND_STATUS          I2C_SMBUS_SUSPEND_STATUS_MSK
#define I2C_SMBUS_ALERT_STATUS_POS        (20U)
#define I2C_SMBUS_ALERT_STATUS_MSK        (0x1UL << I2C_SMBUS_ALERT_STATUS_POS) /*!< This bit indicates the status of the SMBus Alert signal (ic_smbalert_in_n). This signal is asserted when the SMBus Alert signal is asserted by the SMBus Device. Reset value: 0x0. Values: ■ 0x1 (ACTIVE): SMBUS Alert is asserted. ■ 0x0 (INACTIVE): SMBUS Alert is not asserted. Exists: I2C_SMBUS_SUSPEND_ALERT==1 Volatile: true*/
#define I2C_SMBUS_ALERT_STATUS            I2C_SMBUS_ALERT_STATUS_MSK
#define I2C_RSVD_I2C_STATUS_2_POS         (21U)
#define I2C_RSVD_I2C_STATUS_2_MSK         (0x1UL << I2C_RSVD_I2C_STATUS_2_POS) /*!< I2C_STATUS Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_STATUS_2             I2C_RSVD_I2C_STATUS_2_MSK

//I2C_TXFLR offsetaddress : 0x74
#define I2C_TXFLR_POS      (0U)
#define I2C_TXFLR_MSK      (0x1UL << I2C_TXFLR_POS) /*!< Transmit FIFO Level. Contains the number of valid data entries in the transmit FIFO. Reset value: 0x0 Exists: Always Volatile: true Range Variable[x]: TX_ABW_P1 - 1*/
#define I2C_TXFLR          I2C_TXFLR_MSK
#define I2C_RSVD_TXFLR_POS (yU)
#define I2C_RSVD_TXFLR_MSK (0x1UL << I2C_RSVD_TXFLR_POS) /*!< TXFLR Register field Reserved bits - Read Only Exists: Always Volatile: true Range Variable[y]: TX_ABW_P1*/
#define I2C_RSVD_TXFLR     I2C_RSVD_TXFLR_MSK

//I2C_RXFLR offsetaddress : 0x78
#define I2C_RXFLR_POS      (0U)
#define I2C_RXFLR_MSK      (0x1UL << I2C_RXFLR_POS) /*!< Receive FIFO Level. Contains the number of valid data entries in the receive FIFO. Reset value: 0x0 Exists: Always Volatile: true Range Variable[x]: RX_ABW_P1 - 1*/
#define I2C_RXFLR          I2C_RXFLR_MSK
#define I2C_RSVD_RXFLR_POS (yU)
#define I2C_RSVD_RXFLR_MSK (0x1UL << I2C_RSVD_RXFLR_POS) /*!< RXFLR Reserved bits - Read Only Exists: Always Volatile: true Range Variable[y]: RX_ABW_P1*/
#define I2C_RSVD_RXFLR     I2C_RSVD_RXFLR_MSK

//I2C_SDA_HOLD offsetaddress : 0x7c
#define I2C_I2C_SDA_TX_HOLD_POS   (0U)
#define I2C_I2C_SDA_TX_HOLD_MSK   (0x1UL << I2C_I2C_SDA_TX_HOLD_POS) /*!< Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a transmitter. Reset value: I2C_DEFAULT_SDA_HOLD[15:0]. Exists: Always*/
#define I2C_I2C_SDA_TX_HOLD       I2C_I2C_SDA_TX_HOLD_MSK
#define I2C_I2C_SDA_RX_HOLD_POS   (16U)
#define I2C_I2C_SDA_RX_HOLD_MSK   (0x1UL << I2C_I2C_SDA_RX_HOLD_POS) /*!< Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a receiver. Reset value: I2C_DEFAULT_SDA_HOLD[23:16]. Exists: Always*/
#define I2C_I2C_SDA_RX_HOLD       I2C_I2C_SDA_RX_HOLD_MSK
#define I2C_RSVD_I2C_SDA_HOLD_POS (24U)
#define I2C_RSVD_I2C_SDA_HOLD_MSK (0x1UL << I2C_RSVD_I2C_SDA_HOLD_POS) /*!< I2C_SDA_HOLD Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SDA_HOLD     I2C_RSVD_I2C_SDA_HOLD_MSK

//I2C_TX_ABRT_SOURCE offsetaddress : 0x80
#define I2C_ABRT_7B_ADDR_NOACK_POS         (0U)
#define I2C_ABRT_7B_ADDR_NOACK_MSK         (0x1UL << I2C_ABRT_7B_ADDR_NOACK_POS) /*!< This field indicates that the Master is in 7-bit addressing mode and the address sent was not acknowledged by any slave. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Master- Receiver Values: ■ 0x1 (ACTIVE): This abort is generated because of NOACK for 7-bit address ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_7B_ADDR_NOACK             I2C_ABRT_7B_ADDR_NOACK_MSK
#define I2C_ABRT_10ADDR1_NOACK_POS         (1U)
#define I2C_ABRT_10ADDR1_NOACK_MSK         (0x1UL << I2C_ABRT_10ADDR1_NOACK_POS) /*!< This field indicates that the Master is in 10-bit address mode and the first 10-bit address byte was not acknowledged by any slave. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Master- Receiver Values: ■ 0x1 (ACTIVE): Byte 1 of 10Bit Address not ACKed by any slave ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_10ADDR1_NOACK             I2C_ABRT_10ADDR1_NOACK_MSK
#define I2C_ABRT_10ADDR2_NOACK_POS         (2U)
#define I2C_ABRT_10ADDR2_NOACK_MSK         (0x1UL << I2C_ABRT_10ADDR2_NOACK_POS) /*!< This field indicates that the Master is in 10-bit address mode and that the second address byte of the 10-bit address was not acknowledged by any slave. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Master- Receiver Values: ■ 0x1 (ACTIVE): Byte 2 of 10Bit Address not ACKed by any slave ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_10ADDR2_NOACK             I2C_ABRT_10ADDR2_NOACK_MSK
#define I2C_ABRT_TXDATA_NOACK_POS          (3U)
#define I2C_ABRT_TXDATA_NOACK_MSK          (0x1UL << I2C_ABRT_TXDATA_NOACK_POS) /*!< This field indicates the master-mode only bit. When the master receives an acknowledgement for the address, but when it sends data byte(s) following the address, it did not receive an acknowledge from the remote slave(s). Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter Values: ■ 0x1 (ABRT_TXDATA_NOACK_GENERATED): Transmitted data not ACKed by addressed slave ■ 0x0 (ABRT_TXDATA_NOACK_VOID): Transmitted data non-ACKed by addressed slave-scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_TXDATA_NOACK              I2C_ABRT_TXDATA_NOACK_MSK
#define I2C_ABRT_GCALL_NOACK_POS           (4U)
#define I2C_ABRT_GCALL_NOACK_MSK           (0x1UL << I2C_ABRT_GCALL_NOACK_POS) /*!< This field indicates that DW_apb_i2c in master mode has sent a General Call and no slave on the bus acknowledged the General Call. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter Values: ■ 0x1 (ABRT_GCALL_NOACK_GENERATED): GCALL not ACKed by any slave ■ 0x0 (ABRT_GCALL_NOACK_VOID): GCALL not ACKed by any slave-scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_GCALL_NOACK               I2C_ABRT_GCALL_NOACK_MSK
#define I2C_ABRT_GCALL_READ_POS            (5U)
#define I2C_ABRT_GCALL_READ_MSK            (0x1UL << I2C_ABRT_GCALL_READ_POS) /*!< This field indicates that DW_apb_i2c in the master mode has sent a General Call but the user programmed the byte following the General Call to be a read from the bus (I2C_DATA_CMD[9] is set to 1). Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter Values: ■ 0x1 (ABRT_GCALL_READ_GENERATED): GCALL is followed by read from bus ■ 0x0 (ABRT_GCALL_READ_VOID): GCALL is followed by read from bus-scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_GCALL_READ                I2C_ABRT_GCALL_READ_MSK
#define I2C_ABRT_HS_ACKDET_POS             (6U)
#define I2C_ABRT_HS_ACKDET_MSK             (0x1UL << I2C_ABRT_HS_ACKDET_POS) /*!< This field indicates that the Master is in High Speed mode and the High Speed Master code was acknowledged (wrong behavior). Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ABRT_HS_ACK_GENERATED): HS Master code ACKed in HS Mode ■ 0x0 (ABRT_HS_ACK_VOID): HS Master code ACKed in HS Mode- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_HS_ACKDET                 I2C_ABRT_HS_ACKDET_MSK
#define I2C_ABRT_SBYTE_ACKDET_POS          (7U)
#define I2C_ABRT_SBYTE_ACKDET_MSK          (0x1UL << I2C_ABRT_SBYTE_ACKDET_POS) /*!< This field indicates that the Master has sent a START Byte and the START Byte was acknowledged (wrong behavior). Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ABRT_SBYTE_ACKDET_GENERATED): ACK detected for START byte ■ 0x0 (ABRT_SBYTE_ACKDET_VOID): ACK detected for START byte- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_SBYTE_ACKDET              I2C_ABRT_SBYTE_ACKDET_MSK
#define I2C_ABRT_HS_NORSTRT_POS            (8U)
#define I2C_ABRT_HS_NORSTRT_MSK            (0x1UL << I2C_ABRT_HS_NORSTRT_POS) /*!< This field indicates that the restart is disabled (I2C_RESTART_EN bit (I2C_CON[5]) =0) and the user is trying to use the master to transfer data in High Speed mode. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Master- Receiver Values: ■ 0x1 (ABRT_HS_NORSTRT_GENERATED): User trying to switch Master to HS mode when RESTART disabled ■ 0x0 (ABRT_HS_NORSTRT_VOID): User trying to switch Master to HS mode when RESTART disabled- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_HS_NORSTRT                I2C_ABRT_HS_NORSTRT_MSK
#define I2C_ABRT_SBYTE_NORSTRT_POS         (9U)
#define I2C_ABRT_SBYTE_NORSTRT_MSK         (0x1UL << I2C_ABRT_SBYTE_NORSTRT_POS) /*!< To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed first; restart must be enabled (I2C_CON[5]=1), the SPECIAL bit must be cleared (I2C_TAR[11]), or the GC_OR_START bit must be cleared (I2C_TAR[10]). Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be cleared in the same manner as other bits in this register. If the source of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this bit, bit 9 clears for one cycle and then gets reasserted. When this field is set to 1, the restart is disabled (I2C_RESTART_EN bit (I2C_CON[5]) =0) and the user is trying to send a START Byte. Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ABRT_SBYTE_NORSTRT_GENERATED): User trying to send START byte when RESTART disabled ■ 0x0 (ABRT_SBYTE_NORSTRT_VOID): User trying to send START byte when RESTART disabled- scenario not present Exists: Always Volatile: true*/
#define I2C_ABRT_SBYTE_NORSTRT             I2C_ABRT_SBYTE_NORSTRT_MSK
#define I2C_ABRT_10B_RD_NORSTRT_POS        (10U)
#define I2C_ABRT_10B_RD_NORSTRT_MSK        (0x1UL << I2C_ABRT_10B_RD_NORSTRT_POS) /*!< This field indicates that the restart is disabled (I2C_RESTART_EN bit (I2C_CON[5]) =0) and the master sends a read command in 10-bit addressing mode. Reset value: 0x0 Role of DW_apb_i2c: Master-Receiver Values: ■ 0x1 (ABRT_10B_RD_GENERATED): Master trying to read in 10Bit addressing mode when RESTART disabled ■ 0x0 (ABRT_10B_RD_VOID): Master not trying to read in 10Bit addressing mode when RESTART disabled Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_10B_RD_NORSTRT            I2C_ABRT_10B_RD_NORSTRT_MSK
#define I2C_ABRT_MASTER_DIS_POS            (11U)
#define I2C_ABRT_MASTER_DIS_MSK            (0x1UL << I2C_ABRT_MASTER_DIS_POS) /*!< This field indicates that the User tries to initiate a Master operation with the Master mode disabled. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Master- Receiver Values: ■ 0x1 (ABRT_MASTER_DIS_GENERATED): User intitating master operation when MASTER disabled ■ 0x0 (ABRT_MASTER_DIS_VOID): User initiating master operation when MASTER disabled- scenario not present Exists: Always Volatile: true*/
#define I2C_ABRT_MASTER_DIS                I2C_ABRT_MASTER_DIS_MSK
#define I2C_ARB_LOST_POS                   (12U)
#define I2C_ARB_LOST_MSK                   (0x1UL << I2C_ARB_LOST_POS) /*!< This field specifies that the Master has lost arbitration, or if I2C_TX_ABRT_SOURCE[14] is also set, then the slave transmitter has lost arbitration. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Slave- Transmitter Values: ■ 0x1 (ABRT_LOST_GENERATED): Master or Slave- Transmitter lost arbitration ■ 0x0 (ABRT_LOST_VOID): Master or Slave-Transmitter lost arbitration- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ARB_LOST                       I2C_ARB_LOST_MSK
#define I2C_ABRT_SLVFLUSH_TXFIFO_POS       (13U)
#define I2C_ABRT_SLVFLUSH_TXFIFO_MSK       (0x1UL << I2C_ABRT_SLVFLUSH_TXFIFO_POS) /*!< This field specifies that the Slave has received a read command and some data exists in the TX FIFO, so the slave issues a TX_ABRT interrupt to flush old data in TX FIFO. Reset value: 0x0 Role of DW_apb_i2c: Slave-Transmitter Values: ■ 0x1 (ABRT_SLVFLUSH_TXFIFO_GENERATED): Slave flushes existing data in TX-FIFO upon getting read command ■ 0x0 (ABRT_SLVFLUSH_TXFIFO_VOID): Slave flushes existing data in TX-FIFO upon getting read command- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_SLVFLUSH_TXFIFO           I2C_ABRT_SLVFLUSH_TXFIFO_MSK
#define I2C_ABRT_SLV_ARBLOST_POS           (14U)
#define I2C_ABRT_SLV_ARBLOST_MSK           (0x1UL << I2C_ABRT_SLV_ARBLOST_POS) /*!< This field indicates that a Slave has lost the bus while transmitting data to a remote master. I2C_TX_ABRT_SOURCE[12] is set at the same time. Note: Even though the slave never 'owns' the bus, something could go wrong on the bus. This is a fail safe check. For instance, during a data transmission at the low-to- high transition of SCL, if what is on the data bus is not what is supposed to be transmitted, then DW_apb_i2c no longer own the bus. Reset value: 0x0 Role of DW_apb_i2c: Slave-Transmitter Values: ■ 0x1 (ABRT_SLV_ARBLOST_GENERATED): Slave lost arbitration to remote master ■ 0x0 (ABRT_SLV_ARBLOST_VOID): Slave lost arbitration to remote master- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_SLV_ARBLOST               I2C_ABRT_SLV_ARBLOST_MSK
#define I2C_ABRT_SLVRD_INTX_POS            (15U)
#define I2C_ABRT_SLVRD_INTX_MSK            (0x1UL << I2C_ABRT_SLVRD_INTX_POS) /*!< 1: When the processor side responds to a slave mode request for data to be transmitted to a remote master and user writes a 1 in CMD (bit 8) of I2C_DATA_CMD register. Reset value: 0x0 Role of DW_apb_i2c: Slave-Transmitter Values: ■ 0x1 (ABRT_SLVRD_INTX_GENERATED): Slave trying to transmit to remote master in read mode ■ 0x0 (ABRT_SLVRD_INTX_VOID): Slave trying to transmit to remote master in read mode- scenario not present Exists: I2C_ULTRA_FAST_MODE==0 Volatile: true*/
#define I2C_ABRT_SLVRD_INTX                I2C_ABRT_SLVRD_INTX_MSK
#define I2C_ABRT_USER_ABRT_POS             (16U)
#define I2C_ABRT_USER_ABRT_MSK             (0x1UL << I2C_ABRT_USER_ABRT_POS) /*!< This is a master-mode-only bit. Master has detected the transfer abort (I2C_ENABLE[1]) Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter Values: ■ 0x1 (ABRT_USER_ABRT_GENERATED): Transfer abort detected by master ■ 0x0 (ABRT_USER_ABRT_VOID): Transfer abort detected by master- scenario not present Exists: Always Volatile: true*/
#define I2C_ABRT_USER_ABRT                 I2C_ABRT_USER_ABRT_MSK
#define I2C_ABRT_SDA_STUCK_AT_LOW_POS      (17U)
#define I2C_ABRT_SDA_STUCK_AT_LOW_MSK      (0x1UL << I2C_ABRT_SDA_STUCK_AT_LOW_POS) /*!< This is a master-mode-only bit. Master detects the SDA Stuck at low for the I2C_SDA_STUCK_AT_LOW_TIMEOUT value of ic_clks. Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ACTIVE): This abort is generated because of Sda stuck at low for I2C_SDA_STUCK_AT_LOW_TIMEOUT value of ic_clks ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_BUS_CLEAR_FEATURE == 1 Volatile: true*/
#define I2C_ABRT_SDA_STUCK_AT_LOW          I2C_ABRT_SDA_STUCK_AT_LOW_MSK
#define I2C_ABRT_DEVI2CE_NOACK_POS         (18U)
#define I2C_ABRT_DEVI2CE_NOACK_MSK         (0x1UL << I2C_ABRT_DEVI2CE_NOACK_POS) /*!< This is a master-mode-only bit. Master is initiating the DEVI2CE_ID transfer and the device id sent was not acknowledged by any slave. Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ACTIVE): This abort is generated because of NOACK for DEVI2CE-ID ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_DEVI2CE_ID == 1 Volatile: true*/
#define I2C_ABRT_DEVI2CE_NOACK             I2C_ABRT_DEVI2CE_NOACK_MSK
#define I2C_ABRT_DEVI2CE_SLVADDR_NOACK_POS (19U)
#define I2C_ABRT_DEVI2CE_SLVADDR_NOACK_MSK (0x1UL << I2C_ABRT_DEVI2CE_SLVADDR_NOACK_POS) /*!< This is a master-mode-only bit. Master is initiating the DEVI2CE_ID transfer and the slave address sent was not acknowledged by any slave. Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ACTIVE): This abort is generated because of NOACK for Slave address ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_DEVI2CE_ID == 1 Volatile: true*/
#define I2C_ABRT_DEVI2CE_SLVADDR_NOACK     I2C_ABRT_DEVI2CE_SLVADDR_NOA CK_MSK
#define I2C_ABRT_DEVI2CE_WRITE_POS         (20U)
#define I2C_ABRT_DEVI2CE_WRITE_MSK         (0x1UL << I2C_ABRT_DEVI2CE_WRITE_POS) /*!< This is a master-mode-only bit. Master is initiating the DEVI2CE_ID transfer and the Tx-FIFO consists of write commands. Reset value: 0x0 Role of DW_apb_i2c: Master Values: ■ 0x1 (ACTIVE): This abort is generated because of NOACK for Slave address ■ 0x0 (INACTIVE): This abort is not generated Exists: I2C_DEVI2CE_ID == 1 Volatile: true*/
#define I2C_ABRT_DEVI2CE_WRITE             I2C_ABRT_DEVI2CE_WRITE_MSK
#define I2C_RSVD_I2C_TX_ABRT_SOURCE_POS    (21U)
#define I2C_RSVD_I2C_TX_ABRT_SOURCE_MSK    (0x1UL << I2C_RSVD_I2C_TX_ABRT_SOURCE_POS) /*!< I2C_TX_ABRT_SOURCE Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_TX_ABRT_SOURCE        I2C_RSVD_I2C_TX_ABRT_SOURCE_MSK
#define I2C_TX_FLUSH_CNT_POS               (23U)
#define I2C_TX_FLUSH_CNT_MSK               (0x1UL << I2C_TX_FLUSH_CNT_POS) /*!< This field indicates the number of Tx FIFO Data Commands which are flushed due to TX_ABRT interrupt. It is cleared whenever I2C is disabled. Reset value: 0x0 Role of DW_apb_i2c: Master-Transmitter or Slave- Transmitter Exists: Always Volatile: true*/
#define I2C_TX_FLUSH_CNT                   I2C_TX_FLUSH_CNT_MSK

//I2C_SLV_DATA_NACK_ONLY offsetaddress : 0x84
#define I2C_NACK_POS                        (0U)
#define I2C_NACK_MSK                        (0x1UL << I2C_NACK_POS) /*!< Generate NACK. This NACK generation only occurs when DW_apb_i2c is a slave-receiver. If this register is set to a value of 1, it can only generate a NACK after a data byte is received; hence, the data transfer is aborted and the data received is not pushed to the receive buffer. When the register is set to a value of 0, it generates NACK/ACK, depending on normal criteria. ■ 1: generate NACK after data byte received ■ 0: generate NACK/ACK normally Reset value: 0x0 Values: ■ 0x1 (ENABLED): Slave reciever generates NACK upon data reception only ■ 0x0 (DISABLED): Slave reciever generates NACK normally Exists: Always*/
#define I2C_NACK                            I2C_NACK_MSK
#define I2C_RSVD_I2C_SLV_DATA_NACK_ONLY_POS (1U)
#define I2C_RSVD_I2C_SLV_DATA_NACK_ONLY_MSK (0x1UL << I2C_RSVD_I2C_SLV_DATA_NACK_ONLY_POS) /*!< I2C_SLV_DATA_NACK_ONLY Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SLV_DATA_NACK_ONLY     I2C_RSVD_I2C_SLV_DATA_NACK_ON LY_MSK

//I2C_DMA_CR offsetaddress : 0x88
#define I2C_RDMAE_POS                (0U)
#define I2C_RDMAE_MSK                (0x1UL << I2C_RDMAE_POS) /*!< Receive DMA Enable. This bit enables/disables the receive FIFO DMA channel.Reset value: 0x0 Values: ■ 0x1 (ENABLED): Receive FIFO DMA channel enabled ■ 0x0 (DISABLED): Receive FIFO DMA channel disabled Exists: Always*/
#define I2C_RDMAE                    I2C_RDMAE_MSK
#define I2C_TDMAE_POS                (1U)
#define I2C_TDMAE_MSK                (0x1UL << I2C_TDMAE_POS) /*!< Transmit DMA Enable. This bit enables/disables the transmit FIFO DMA channel.Reset value: 0x0 Values: ■ 0x1 (ENABLED): Transmit FIFO DMA channel enabled ■ 0x0 (DISABLED): transmit FIFO DMA channel disabled Exists: Always*/
#define I2C_TDMAE                    I2C_TDMAE_MSK
#define I2C_RSVD_I2C_DMA_CR_2_31_POS (2U)
#define I2C_RSVD_I2C_DMA_CR_2_31_MSK (0x1UL << I2C_RSVD_I2C_DMA_CR_2_31_POS) /*!< RSVD_I2C_DMA_CR_2_31 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_DMA_CR_2_31     I2C_RSVD_I2C_DMA_CR_2_31_MSK

//I2C_DMA_TDLR offsetaddress : 0x8c
#define I2C_DMATDL_POS        (0U)
#define I2C_DMATDL_MSK        (0x1UL << I2C_DMATDL_POS) /*!< Transmit Data Level. This bit field controls the level at which a DMA request is made by the transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to or below this field value, and TDMAE = 1. Reset value: 0x0 Exists: Always Range Variable[x]: TX_ABW - 1*/
#define I2C_DMATDL            I2C_DMATDL_MSK
#define I2C_RSVD_DMA_TDLR_POS (yU)
#define I2C_RSVD_DMA_TDLR_MSK (0x1UL << I2C_RSVD_DMA_TDLR_POS) /*!< DMA_TDLR Reserved bits - Read Only Exists: Always Range Variable[y]: TX_ABW*/
#define I2C_RSVD_DMA_TDLR     I2C_RSVD_DMA_TDLR_MSK

//I2C_DMA_RDLR offsetaddress : 0x90
#define I2C_DMARDL_POS        (0U)
#define I2C_DMARDL_MSK        (0x1UL << I2C_DMARDL_POS) /*!< Receive Data Level. This bit field controls the level at which a DMA request is made by the receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal to or more than this field value + 1, and RDMAE =1. For instance, when DMARDL is 0, then dma_rx_req is asserted when 1 or more data entries are present in the receive FIFO. Reset value: 0x0 Exists: Always Range Variable[x]: RX_ABW - 1*/
#define I2C_DMARDL            I2C_DMARDL_MSK
#define I2C_RSVD_DMA_RDLR_POS (0U)
#define I2C_RSVD_DMA_RDLR_MSK (0x1UL << I2C_RSVD_DMA_RDLR_POS) /*!< DMA_RDLR Reserved bits - Read Only Exists: Always Range Variable[y]: RX_ABW*/
#define I2C_RSVD_DMA_RDLR     I2C_RSVD_DMA_RDLR_MSK

//I2C_SDA_SETUP offsetaddress : 0x94
#define I2C_SDA_SETUP_POS          (0U)
#define I2C_SDA_SETUP_MSK          (0x1UL << I2C_SDA_SETUP_POS) /*!< SDA Setup. It is recommended that if the required delay is 1000ns, then for an ic_clk frequency of 10 MHz, I2C_SDA_SETUP should be programmed to a value of 11. I2C_SDA_SETUP must be programmed with a minimum value of 2. Reset value: 0x64, but can be hardcoded by setting the I2C_DEFAULT_SDA_SETUP configuration parameter. Exists: Always*/
#define I2C_SDA_SETUP              I2C_SDA_SETUP_MSK
#define I2C_RSVD_I2C_SDA_SETUP_POS (8U)
#define I2C_RSVD_I2C_SDA_SETUP_MSK (0x1UL << I2C_RSVD_I2C_SDA_SETUP_POS) /*!< I2C_SDA_SETUP Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_SDA_SETUP     I2C_RSVD_I2C_SDA_SETUP_MSK

//I2C_ACK_GENERAL_CALL offsetaddress : 0x98
#define I2C_ACK_GEN_CALL_POS          (0U)
#define I2C_ACK_GEN_CALL_MSK          (0x1UL << I2C_ACK_GEN_CALL_POS) /*!< ACK General Call. When set to 1, DW_apb_i2c responds with a ACK (by asserting ic_data_oe) when it receives a General Call. Otherwise, DW_apb_i2c responds with a NACK (by negating ic_data_oe). Reset value: 0x1, but can be hardcoded by setting the I2C_DEFAULT_ACK_GENERAL_CALL configuration parameter. Values: ■ 0x1 (ENABLED): Generate ACK for a General Call ■ 0x0 (DISABLED): Generate NACK for General Call Exists: Always*/
#define I2C_ACK_GEN_CALL              I2C_ACK_GEN_CALL_MSK
#define I2C_RSVD_I2C_ACK_GEN_1_31_POS (1U)
#define I2C_RSVD_I2C_ACK_GEN_1_31_MSK (0x1UL << I2C_RSVD_I2C_ACK_GEN_1_31_POS) /*!< RSVD_I2C_ACK_GEN_1_31 Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_ACK_GEN_1_31     I2C_RSVD_I2C_ACK_GEN_1_31_MSK

//I2C_ENABLE_STATUS offsetaddress : 0x9c
#define I2C_I2C_EN_POS                  (0U)
#define I2C_I2C_EN_MSK                  (0x1UL << I2C_I2C_EN_POS) /*!< ic_en Status. This bit always reflects the value driven on the output port ic_en. ■ When read as 1, DW_apb_i2c is deemed to be in an enabled state. ■ When read as 0, DW_apb_i2c is deemed completely inactive. Note: The CPU can safely read this bit anytime. When this bit is read as 0, the CPU can safely read SLV_RX_DATA_LOST (bit 2) and SLV_DISABLED_WHILE_BUSY (bit 1). Reset value: 0x0 Values: ■ 0x1 (ENABLED): I2C enabled ■ 0x0 (DISABLED): I2C disabled Exists: Always Volatile: true*/
#define I2C_I2C_EN                      I2C_I2C_EN_MSK
#define I2C_SLV_DISABLED_WHILE_BUSY_POS (1U)
#define I2C_SLV_DISABLED_WHILE_BUSY_MSK (0x1UL << I2C_SLV_DISABLED_WHILE_BUSY_POS) /*!< Slave Disabled While Busy (Transmit, Receive). This bit indicates if a potential or active Slave operation has been aborted due to the setting bit 0 of the I2C_ENABLE register from 1 to 0. This bit is set when the CPU writes a 0 to the I2C_ENABLE register while: (a) DW_apb_i2c is receiving the address byte of the Slave- Transmitter operation from a remote master; OR, (b) address and data bytes of the Slave-Receiver operation from a remote master. When read as 1, DW_apb_i2c is deemed to have forced a NACK during any part of an I2C transfer, irrespective of whether the I2C address matches the slave address set in DW_apb_i2c (I2C_SAR register) OR if the transfer is completed before I2C_ENABLE is set to 0 but has not taken effect. Note: If the remote I2C master terminates the transfer with a STOP condition before the DW_apb_i2c has a chance to NACK a transfer, and I2C_ENABLE[0] has been set to 0, then this bit will also be set to 1. When read as 0, DW_apb_i2c is deemed to have been disabled when there is master activity, or when the I2C bus is idle. Note: The CPU can safely read this bit when I2C_EN (bit 0) is read as 0. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Slave is disabled when it is active ■ 0x0 (INACTIVE): Slave is disabled when it is idle Exists: Always Volatile: true*/
#define I2C_SLV_DISABLED_WHILE_BUSY     I2C_SLV_DISABLED_WHILE_BUSY_MSK
#define I2C_SLV_RX_DATA_LOST_POS        (2U)
#define I2C_SLV_RX_DATA_LOST_MSK        (0x1UL << I2C_SLV_RX_DATA_LOST_POS) /*!< Slave Received Data Lost. This bit indicates if a Slave- Receiver operation has been aborted with at least one data byte received from an I2C transfer due to the setting bit 0 of I2C_ENABLE from 1 to 0. When read as 1, DW_apb_i2c is deemed to have been actively engaged in an aborted I2C transfer (with matching address) and the data phase of the I2C transfer has been entered, even though a data byte has been responded with a NACK. Note: If the remote I2C master terminates the transfer with a STOP condition before the DW_apb_i2c has a chance to NACK a transfer, and I2C_ENABLE[0] has been set to 0, then this bit is also set to 1. When read as 0, DW_apb_i2c is deemed to have been disabled without being actively involved in the data phase of a Slave-Receiver transfer. Note: The CPU can safely read this bit when I2C_EN (bit 0) is read as 0. Reset value: 0x0 Values: ■ 0x1 (ACTIVE): Slave RX Data is lost ■ 0x0 (INACTIVE): Slave RX Data is not lost Exists: Always Volatile: true*/
#define I2C_SLV_RX_DATA_LOST            I2C_SLV_RX_DATA_LOST_MSK
#define I2C_RSVD_I2C_ENABLE_STATUS_POS  (3U)
#define I2C_RSVD_I2C_ENABLE_STATUS_MSK  (0x1UL << I2C_RSVD_I2C_ENABLE_STATUS_POS) /*!< I2C_ENABLE_STATUS Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_ENABLE_STATUS      I2C_RSVD_I2C_ENABLE_STATUS_MSK

//I2C_FS_SPKLEN offsetaddress : 0xa0
#define I2C_I2C_FS_SPKLEN_POS      (0U)
#define I2C_I2C_FS_SPKLEN_MSK      (0x1UL << I2C_I2C_FS_SPKLEN_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure stable operation. This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic. This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 1; hardware prevents values less than this being written, and if attempted results in 1 being set. or more information, refer to "Spike Suppression". Reset value: I2C_DEFAULT_FS_SPKLEN configuration parameter. Exists: Always*/
#define I2C_I2C_FS_SPKLEN          I2C_I2C_FS_SPKLEN_MSK
#define I2C_RSVD_I2C_FS_SPKLEN_POS (8U)
#define I2C_RSVD_I2C_FS_SPKLEN_MSK (0x1UL << I2C_RSVD_I2C_FS_SPKLEN_POS) /*!< I2C_FS_SPKLEN Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_FS_SPKLEN     I2C_RSVD_I2C_FS_SPKLEN_MSK

//I2C_UFM_SPKLEN offsetaddress : 0xa0
#define I2C_I2C_UFM_SPKLEN_POS      (0U)
#define I2C_I2C_UFM_SPKLEN_MSK      (0x1UL << I2C_I2C_UFM_SPKLEN_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure stable operation. This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic. This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 1; hardware prevents values less than this being written, and if attempted results in 1 being set. Reset value: I2C_DEFAULT_UFM_SPKLEN configuration parameter. Exists: Always*/
#define I2C_I2C_UFM_SPKLEN          I2C_I2C_UFM_SPKLEN_MSK
#define I2C_RSVD_I2C_UFM_SPKLEN_POS (8U)
#define I2C_RSVD_I2C_UFM_SPKLEN_MSK (0x1UL << I2C_RSVD_I2C_UFM_SPKLEN_POS) /*!< I2C_UFM_SPKLEN Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_UFM_SPKLEN     I2C_RSVD_I2C_UFM_SPKLEN_MSK

//I2C_HS_SPKLEN offsetaddress : 0xa4
#define I2C_I2C_HS_SPKLEN_POS      (0U)
#define I2C_I2C_HS_SPKLEN_MSK      (0x1UL << I2C_I2C_HS_SPKLEN_POS) /*!< This register must be set before any I2C bus transaction can take place to ensure stable operation. This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic; for more information, refer to "Spike Suppression" This register can be written only when the I2C interface is disabled which corresponds to the I2C_ENABLE[0] register being set to 0. Writes at other times have no effect. The minimum valid value is 1; hardware prevents values less than this being written, and if attempted results in 1 being set. Reset value: I2C_DEFAULT_HS_SPKLEN configuration parameter. Exists: Always*/
#define I2C_I2C_HS_SPKLEN          I2C_I2C_HS_SPKLEN_MSK
#define I2C_RSVD_I2C_HS_SPKLEN_POS (8U)
#define I2C_RSVD_I2C_HS_SPKLEN_MSK (0x1UL << I2C_RSVD_I2C_HS_SPKLEN_POS) /*!< I2C_HS_SPKLEN Reserved bits - Read Only Exists: Always*/
#define I2C_RSVD_I2C_HS_SPKLEN     I2C_RSVD_I2C_HS_SPKLEN_MSK

//I2C_CLR_RESTART_DET offsetaddress : 0xa8
#define I2C_CLR_RESTART_DET_POS          (0U)
#define I2C_CLR_RESTART_DET_MSK          (0x1UL << I2C_CLR_RESTART_DET_POS) /*!< Read this register to clear the RESTART_DET interrupt (bit 12) of I2C_RAW_INTR_STAT register. Reset value: 0x0 Exists: Always Volatile: true*/
#define I2C_CLR_RESTART_DET              I2C_CLR_RESTART_DET_MSK
#define I2C_RSVD_I2C_CLR_RESTART_DET_POS (1U)
#define I2C_RSVD_I2C_CLR_RESTART_DET_MSK (0x1UL << I2C_RSVD_I2C_CLR_RESTART_DET_POS) /*!< I2C_CLR_RESTART_DET Reserved bits - Read Only Exists: Always Volatile: true*/
#define I2C_RSVD_I2C_CLR_RESTART_DET     I2C_RSVD_I2C_CLR_RESTART_DET_MSK

typedef struct {
    volatile uint32_t IC_CON;                        //offsetaddress : 0x0
    volatile uint32_t IC_TAR;                        //offsetaddress : 0x4
    volatile uint32_t IC_SAR;                        //offsetaddress : 0x8
    volatile uint32_t IC_HS_MADDR;                   //offsetaddress : 0xc
    volatile uint32_t IC_DATA_CMD;                   //offsetaddress : 0x10
    volatile uint32_t IC_SS_SCL_HCNT;                //offsetaddress : 0x14
    volatile uint32_t IC_SS_SCL_LCNT;                //offsetaddress : 0x18
    volatile uint32_t IC_FS_SCL_HCNT;                //offsetaddress : 0x1c
    volatile uint32_t IC_FS_SCL_LCNT;                //offsetaddress : 0x20
    volatile uint32_t IC_HS_SCL_HCNT;                //offsetaddress : 0x24
    volatile uint32_t IC_HS_SCL_LCNT;                //offsetaddress : 0x28
    volatile uint32_t IC_INTR_STAT;                  //offsetaddress : 0x2c
    volatile uint32_t IC_INTR_MASK;                  //offsetaddress : 0x30
    volatile uint32_t IC_RAW_INTR_STAT;              //offsetaddress : 0x34
    volatile uint32_t IC_RX_TL;                      //offsetaddress : 0x38
    volatile uint32_t IC_TX_TL;                      //offsetaddress : 0x3c
    volatile uint32_t IC_CLR_INTR;                   //offsetaddress : 0x40
    volatile uint32_t IC_CLR_RX_UNDER;               //offsetaddress : 0x44
    volatile uint32_t IC_CLR_RX_OVER;                //offsetaddress : 0x48
    volatile uint32_t IC_CLR_TX_OVER;                //offsetaddress : 0x4c
    volatile uint32_t IC_CLR_RD_REQ;                 //offsetaddress : 0x50
    volatile uint32_t IC_CLR_TX_ABRT;                //offsetaddress : 0x54
    volatile uint32_t IC_CLR_RX_DONE;                //offsetaddress : 0x58
    volatile uint32_t IC_CLR_ACTIVITY;               //offsetaddress : 0x5c
    volatile uint32_t IC_CLR_STOP_DET;               //offsetaddress : 0x60
    volatile uint32_t IC_CLR_START_DET;              //offsetaddress : 0x64
    volatile uint32_t IC_CLR_GEN_CALL;               //offsetaddress : 0x68
    volatile uint32_t IC_ENABLE;                     //offsetaddress : 0x6c
    volatile uint32_t IC_STATUS;                     //offsetaddress : 0x70
    volatile uint32_t IC_TXFLR;                      //offsetaddress : 0x74
    volatile uint32_t IC_RXFLR;                      //offsetaddress : 0x78
    volatile uint32_t IC_SDA_HOLD;                   //offsetaddress : 0x7c
    volatile uint32_t IC_TX_ABRT_SOURCE;             //offsetaddress : 0x80
    volatile uint32_t IC_SLV_DATA_NACK_ONLY;         //offsetaddress : 0x84
    volatile uint32_t IC_DMA_CR;                     //offsetaddress : 0x88
    volatile uint32_t IC_DMA_TDLR;                   //offsetaddress : 0x8c
    volatile uint32_t IC_DMA_RDLR;                   //offsetaddress : 0x90
    volatile uint32_t IC_SDA_SETUP;                  //offsetaddress : 0x94
    volatile uint32_t IC_ACK_GENERAL_CALL;           //offsetaddress : 0x98
    volatile uint32_t IC_ENABLE_STATUS;              //offsetaddress : 0x9c
    volatile uint32_t IC_FS_UFM_SPKLEN;              //offsetaddress : 0xa0
    volatile uint32_t IC_HS_SPKLEN;                  //offsetaddress : 0xa4
    volatile uint32_t IC_CLR_RESTART_DET;            //offsetaddress : 0xa8
    volatile uint32_t IC_SCL_STUCK_AT_LOW_TIMEOUT;   //offsetaddress : 0xac
    volatile uint32_t IC_SDA_STUCK_AT_LOW_TIMEOUT;   //offsetaddress : 0xb0
    volatile uint32_t IC_CLR_SCL_STUCK_DET;          //offsetaddress : 0xb4
    volatile uint32_t IC_DEVICE_ID;                  //offsetaddress : 0xb8
    volatile uint32_t IC_SMBUS_CLK_LOW_SEXT;         //offsetaddress : 0xbc
    volatile uint32_t IC_SMBUS_CLK_LOW_MEXT;         //offsetaddress : 0xc0
    volatile uint32_t IC_SMBUS_THIGH_MAX_IDLE_COUNT; //offsetaddress : 0xc4
    volatile uint32_t IC_SMBUS_INTR_STAT;            //offsetaddress : 0xc8
    volatile uint32_t IC_SMBUS_INTR_MASK;            //offsetaddress : 0xcc
    volatile uint32_t IC_SMBUS_RAW_INTR_STAT;        //offsetaddress : 0xd0
    volatile uint32_t IC_CLR_SMBUS_INTR;             //offsetaddress : 0xd4
    volatile uint32_t IC_OPTIONAL_SAR;               //offsetaddress : 0xd8
    volatile uint32_t IC_SMBUS_UDID_LSB;             //offsetaddress : 0xdc
    volatile uint32_t IC_COMP_PARAM_1;               //offsetaddress : 0xf4
    volatile uint32_t IC_COMP_VERSION;               //offsetaddress : 0xf8
    volatile uint32_t IC_COMP_TYPE;                  //offsetaddress : 0xfc
} i2c_reg_t;
#ifdef __cplusplus
}
#endif
#endif
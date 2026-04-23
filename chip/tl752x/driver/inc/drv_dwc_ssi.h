/*******************************************************************************************************
 *
 * @file    drv_dwc_ssi.h
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
#ifndef __DRV_DWC_SSI_H__
#define __DRV_DWC_SSI_H__
#include <stdint.h>
#include <stdbool.h>
#include "tl_chip.h"
#include "reg/ssi.h"
#include "inc/drv_dmac.h"
#ifdef __cplusplus
extern "C" {
#endif

#define DWC_SSI_USE_DMA
#ifdef DWC_SSI_USE_DMA
#define IS_DMA_INTERRUPT 0
#endif

typedef enum {
    DWC_SSI_CTRLR0_SPI_FRF_STANDARD_SPI = 0,
    DWC_SSI_CTRLR0_SPI_FRF_DUAL_SPI = 1,
    DWC_SSI_CTRLR0_SPI_FRF_QUAD_SPI = 2,
    DWC_SSI_CTRLR0_SPI_FRF_OCTAL_SPI = 3,
} dwc_ssi_ctrlr0_spi_frf_t;

typedef enum {
    DWC_SSI_SPI_CTRLR0_ADDR_L_00_BIT = 0, // no Address
    DWC_SSI_SPI_CTRLR0_ADDR_L_24_BIT = 6,
    DWC_SSI_SPI_CTRLR0_ADDR_L_32_BIT = 8,
} dwc_ssi_spi_ctrlr0_addr_l_t;

typedef enum {
    DWC_SSI_SPI_CTRLR0_TRANS_TYPE_TT0 = 0, // Instruction and address will be sent in standard SPI mode
    DWC_SSI_SPI_CTRLR0_TRANS_TYPE_TT1,     // Instruction will be sent in standard SPI mode and address will be sent in the mode specified by CTRLR0.SPI_FRF
    DWC_SSI_SPI_CTRLR0_TRANS_TYPE_TT2,     // Both instruction and address will be sent in the mode specified by CTRLR0.SPI_FRF
    DWC_SSI_SPI_CTRLR0_TRANS_TYPE_TT3,     // reserved
} dwc_ssi_spi_ctrlr0_trans_type_t;

typedef enum {
    DWC_SSI_SPI_INSTRUCTION_MODE_NONE,
    DWC_SSI_SPI_INSTRUCTION_MODE_1_LINE,
    DWC_SSI_SPI_INSTRUCTION_MODE_2_LINE,
    DWC_SSI_SPI_INSTRUCTION_MODE_4_LINE,
} dwc_ssi_instruction_mode_t;
typedef enum {
    DWC_SSI_SPI_ADDR_MODE_NONE,
    DWC_SSI_SPI_ADDR_MODE_1_LINE,
    DWC_SSI_SPI_ADDR_MODE_2_LINE,
    DWC_SSI_SPI_ADDR_MODE_4_LINE,
} dwc_ssi_addr_mode_t;

typedef enum {
    DWC_SSI_TMOD_TX_AND_RX,
    DWC_SSI_TMOD_TX_ONLY,
    DWC_SSI_TMOD_RX_ONLY,
    DWC_SSI_TMOD_EEPROM_READ
} dwc_ssi_tmod_t;

typedef enum {
    DWC_SSI_XIP_CTRL_FRF_SPI_DUAL = 1,
    DWC_SSI_XIP_CTRL_FRF_SPI_QUAL = 2,
} dwc_ssi_xip_ctrl_frf_t;
typedef struct
{
    uint8_t frf;
} dwc_ssi_xip_init_t;

typedef struct {
    uint32_t baud;           //The LSB for this field is always set to 0 and is unaffected by a write operation, which ensures an even value is held in this register. If the value is 0, the serial output clock (sclk_out) is disabled.
    uint32_t m_mclk;         //The frequency of mclk0 after dwc ssi frequency division
    uint8_t rx_sample_delay; /*Receive Data (rxd) Sample Delay.
                                This register is used to delay the sample of the rxd input port.
                                Each value represents a single ssi_clk delay on the sample of rxd.
                                */
} dwc_ssi_init_t;

typedef struct {
    uint8_t Instruction;      // Specifies the Instruction to be sent
    uint8_t instruction_mode; // Specifies the Instruction Mode,
    uint8_t addr_mode;        // Specifies the Address Mode
    uint8_t addr_length;      // defines bits of Address to be transmitted.This value multiplied by 4 represents the selected bit count
    //    uint32_t addr;                              //Specifies the Address to be sent (Size from 1 to 4 bytes according addr_length)
    uint32_t dummy_cycles; // Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles
    uint8_t tmod;          // Transfer Mode.0x0 (TX_AND_RX): Transmit & Receive; Not Applicable in enhanced SPI operating mode
                           //               0x1 (TX_ONLY): Transmit only mode; Or Write in enhanced SPI operating mode
                           //               0x2 (RX_ONLY): Receive only mode; Or Read in enhanced SPI operating mode
                           //               0x3 (EEPROM_READ): EEPROM Read mode; Not Applicable in enhanced SPI operating mode
    uint8_t spi_frf;       // 0x0 (SPI_STANDARD): Standard SPI Format
                           // 0x1 (SPI_DUAL): Dual SPI Format
                           // 0x2 (SPI_QUAD): Quad SPI Format
                           // 0x3 (SPI_OCTAL): Octal SPI Format
} dwc_ssi_cmd_t;

typedef struct __dwc_ssi_handle_t {
    ssi_reg_t *instance;         /*!< dwc ssi registers base address        */
    dwc_ssi_init_t init;         /*!< dwc ssi communication parameters      */
    dwc_ssi_xip_init_t xip_init; /*!<init if use XIP                        */
    void *parent;
    dwc_ssi_cmd_t cmd;
    volatile uint32_t dma_busy;
#ifdef DWC_SSI_USE_DMA
    dmac_handle_t *hdma;
#endif
} dwc_ssi_handle_t;

extern void drv_dwc_ssi_init(dwc_ssi_handle_t *hdwc_ssi);
extern void drv_dwc_ssi_deinit(dwc_ssi_handle_t *hdwc_ssi);
extern void drv_dwc_ssi_xip_enable(dwc_ssi_handle_t *hdwc_ssi);
extern void drv_dwc_ssi_xip_disable(dwc_ssi_handle_t *hdwc_ssi);
extern drv_status_t drv_dwc_ssi_cmd(dwc_ssi_handle_t *hdwc_ssi, dwc_ssi_cmd_t *cmd, uint32_t Timeout);
extern drv_status_t drv_dwc_ssi_tx(dwc_ssi_handle_t *hdwc_ssi, uint32_t addr, uint8_t *tx_ptr, uint16_t tx_size);
extern drv_status_t drv_dwc_ssi_tx_short(dwc_ssi_handle_t *hdwc_ssi, uint32_t addr, uint32_t *static_tx_ptr, uint32_t tx_size);
extern drv_status_t drv_dwc_ssi_rx(dwc_ssi_handle_t *hdwc_ssi, uint32_t addr, uint8_t *rx_ptr, uint16_t rx_size);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DWC_SSI_H__ */

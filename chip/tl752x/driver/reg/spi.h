/*******************************************************************************************************
 *
 * @file    spi.h
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
#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" { /* C declaration in C++ */
#endif       /* _cplusplus */

//CTRLR0 offsetaddress : 0x0
#define SPI_DFS_Pos     (0U)
#define SPI_DFS_Msk     (0xfUL << SPI_DFS_Pos) /*!< Data Frame Size. */
#define SPI_FRF_Pos     (4U)
#define SPI_FRF_Msk     (0x3UL << SPI_FRF_Pos) /*!< Frame Format. */
#define SPI_SCPH_Pos    (6U)
#define SPI_SCPH_Msk    (0x1UL << SPI_SCPH_Pos) /*!< Serial Clock Phase. */
#define SPI_SCPOL_Pos   (7U)
#define SPI_SCPOL_Msk   (0x1UL << SPI_SCPOL_Pos) /*!< Serial Clock Polarity. */
#define SPI_TMOD_Pos    (8U)
#define SPI_TMOD_Msk    (0x3UL << SPI_TMOD_Pos) /*!< Transfer Mode. */
#define SPI_SLV_OE_Pos  (10U)
#define SPI_SLV_OE_Msk  (0x1UL << SPI_SLV_OE_Pos) /*!< Slave Output Enable. */
#define SPI_SRL_Pos     (11U)
#define SPI_SRL_Msk     (0x1UL << SPI_SRL_Pos) /*!< Shift Register Loop. */
#define SPI_CFS_Pos     (12U)
#define SPI_CFS_Msk     (0xfUL << SPI_CFS_Pos) /*!< Control Frame Size. */
#define SPI_DFS_32_Pos  (16U)
#define SPI_DFS_32_Msk  (0x1fUL << SPI_DFS_32_Pos) /*!< Data Frame Size in 32-bit transfer size mode. */
#define SPI_SPI_FRF_Pos (21U)
#define SPI_SPI_FRF_Msk (0x3UL << SPI_SPI_FRF_Pos) /*!< SPI Frame Format*/
#define SPI_SSTE_Pos    (24U)
#define SPI_SSTE_Msk    (0x1UL << SPI_SSTE_Pos) /*!< Slave Select Toggle Enable. */

//CTRLR1 offsetaddress : 0x4
#define SPI_NDF_Pos (0U)
#define SPI_NDF_Msk (0xffffUL << SPI_NDF_Pos) /*!< Number of Data Frames. */

//SSIENR offsetaddress : 0x8
#define SPI_SSI_EN_Pos (0U)
#define SPI_SSI_EN_Msk (0x1UL << SPI_SSI_EN_Pos) /*!< SSI Enable. */

//MWCR offsetaddress : 0xc
#define SPI_MWMOD_Pos (0U)
#define SPI_MWMOD_Msk (0x1UL << SPI_MWMOD_Pos) /*!< Microwire Transfer Mode. */
#define SPI_MDD_Pos   (1U)
#define SPI_MDD_Msk   (0x1UL << SPI_MDD_Pos) /*!< Microwire Control. */
#define SPI_MHS_Pos   (2U)
#define SPI_MHS_Msk   (0x1UL << SPI_MHS_Pos) /*!< Microwire Handshaking. */

//SER offsetaddress : 0x10
#define SPI_SER_Pos (0U)
#define SPI_SER_Msk (0xfUL << SPI_SER_Pos) /*!< Slave Select Enable Flag. */

//BAUDR offsetaddress : 0x14
#define SPI_SCKDV_Pos (0U)
#define SPI_SCKDV_Msk (0xffffUL << SPI_SCKDV_Pos) /*!< SSI Clock Divider. */

//TXFTLR offsetaddress : 0x18
#define SPI_TFT_Pos (0U)
#define SPI_TFT_Msk (0xfUL << SPI_TFT_Pos) /*!< Transmit FIFO Threshold. */

//RXFTLR offsetaddress : 0x1c
#define SPI_RFT_Pos (0U)
#define SPI_RFT_Msk (0xfUL << SPI_RFT_Pos) /*!< Receive FIFO Threshold. */

//TXFLR offsetaddress : 0x20
#define SPI_TXTFL_Pos (0U)
#define SPI_TXTFL_Msk (0xffUL << SPI_TXTFL_Pos) /*!< Transmit FIFO Level. */

//RXFLR offsetaddress : 0x24
#define SPI_RXTFL_Pos (0U)
#define SPI_RXTFL_Msk (0xffUL << SPI_RXTFL_Pos) /*!< Receive FIFO Level. */

//SR offsetaddress : 0x28
#define SPI_BUSY_Pos (0U)
#define SPI_BUSY_Msk (0x1UL << SPI_BUSY_Pos) /*!< SSI Busy Flag. */
#define SPI_TFNF_Pos (1U)
#define SPI_TFNF_Msk (0x1UL << SPI_TFNF_Pos) /*!< Transmit FIFO Not Full. */
#define SPI_TFE_Pos  (2U)
#define SPI_TFE_Msk  (0x1UL << SPI_TFE_Pos) /*!< Transmit FIFO Empty. */
#define SPI_RFNE_Pos (3U)
#define SPI_RFNE_Msk (0x1UL << SPI_RFNE_Pos) /*!< Receive FIFO Not Empty. */
#define SPI_RFF_Pos  (4U)
#define SPI_RFF_Msk  (0x1UL << SPI_RFF_Pos) /*!< Receive FIFO Full. */
#define SPI_TXE_Pos  (5U)
#define SPI_TXE_Msk  (0x1UL << SPI_TXE_Pos) /*!< Transmission Error. */
#define SPI_DCOL_Pos (6U)
#define SPI_DCOL_Msk (0x1UL << SPI_DCOL_Pos) /*!< Data Collision Error. */

//IMR offsetaddress : 0x2c
#define SPI_TXEIM_Pos (0U)
#define SPI_TXEIM_Msk (0x1UL << SPI_TXEIM_Pos) /*!< Transmit FIFO Empty Interrupt Mask */
#define SPI_TXOIM_Pos (1U)
#define SPI_TXOIM_Msk (0x1UL << SPI_TXOIM_Pos) /*!< Transmit FIFO Overflow Interrupt Mask */
#define SPI_RXUIM_Pos (2U)
#define SPI_RXUIM_Msk (0x1UL << SPI_RXUIM_Pos) /*!< Receive FIFO Underflow Interrupt Mask */
#define SPI_RXOIM_Pos (3U)
#define SPI_RXOIM_Msk (0x1UL << SPI_RXOIM_Pos) /*!< Receive FIFO Overflow Interrupt Mask */
#define SPI_RXFIM_Pos (4U)
#define SPI_RXFIM_Msk (0x1UL << SPI_RXFIM_Pos) /*!< Receive FIFO Full Interrupt Mask */
#define SPI_MSTIM_Pos (5U)
#define SPI_MSTIM_Msk (0x1UL << SPI_MSTIM_Pos) /*!< Multi-Master Contention Interrupt Mask. */

//ISR offsetaddress : 0x30
#define SPI_TXEIS_Pos (0U)
#define SPI_TXEIS_Msk (0x1UL << SPI_TXEIS_Pos) /*!< Transmit FIFO Empty Interrupt Status */
#define SPI_TXOIS_Pos (1U)
#define SPI_TXOIS_Msk (0x1UL << SPI_TXOIS_Pos) /*!< Transmit FIFO Overflow Interrupt Status */
#define SPI_RXUIS_Pos (2U)
#define SPI_RXUIS_Msk (0x1UL << SPI_RXUIS_Pos) /*!< Receive FIFO Underflow Interrupt Status */
#define SPI_RXOIS_Pos (3U)
#define SPI_RXOIS_Msk (0x1UL << SPI_RXOIS_Pos) /*!< Receive FIFO Overflow Interrupt Status */
#define SPI_RXFIS_Pos (4U)
#define SPI_RXFIS_Msk (0x1UL << SPI_RXFIS_Pos) /*!< Receive FIFO Full Interrupt Status */
#define SPI_MSTIS_Pos (5U)
#define SPI_MSTIS_Msk (0x1UL << SPI_MSTIS_Pos) /*!< Multi-Master Contention Interrupt Status. */

//RISR offsetaddress : 0x34
#define SPI_TXEIR_Pos (0U)
#define SPI_TXEIR_Msk (0x1UL << SPI_TXEIR_Pos) /*!< Transmit FIFO Empty Raw Interrupt Status */
#define SPI_TXOIR_Pos (1U)
#define SPI_TXOIR_Msk (0x1UL << SPI_TXOIR_Pos) /*!< Transmit FIFO Overflow Raw Interrupt Status */
#define SPI_RXUIR_Pos (2U)
#define SPI_RXUIR_Msk (0x1UL << SPI_RXUIR_Pos) /*!< Receive FIFO Underflow Raw Interrupt Status */
#define SPI_RXOIR_Pos (3U)
#define SPI_RXOIR_Msk (0x1UL << SPI_RXOIR_Pos) /*!< Receive FIFO Overflow Raw Interrupt Status */
#define SPI_RXFIR_Pos (4U)
#define SPI_RXFIR_Msk (0x1UL << SPI_RXFIR_Pos) /*!< Receive FIFO Full Raw Interrupt Status */
#define SPI_MSTIR_Pos (5U)
#define SPI_MSTIR_Msk (0x1UL << SPI_MSTIR_Pos) /*!< Multi-Master Contention Raw Interrupt Status. */

//TXOICR offsetaddress : 0x38
#define SPI_TXOICR_Pos (0U)
#define SPI_TXOICR_Msk (0x1UL << SPI_TXOICR_Pos) /*!< Clear Transmit FIFO Overflow Interrupt. */

//RXOICR offsetaddress : 0x3c
#define SPI_RXOICR_Pos (0U)
#define SPI_RXOICR_Msk (0x1UL << SPI_RXOICR_Pos) /*!< Clear Receive FIFO Overflow Interrupt. */

//RXUICR offsetaddress : 0x40
#define SPI_RXUICR_Pos (0U)
#define SPI_RXUICR_Msk (0x1UL << SPI_RXUICR_Pos) /*!< Clear Receive FIFO Underflow Interrupt. */

//MSTICR offsetaddress : 0x44
#define SPI_MSTICR_Pos (0U)
#define SPI_MSTICR_Msk (0x1UL << SPI_MSTICR_Pos) /*!< Clear Multi-Master Contention Interrupt. */

//ICR offsetaddress : 0x48
#define SPI_ICR_Pos (0U)
#define SPI_ICR_Msk (0x1UL << SPI_ICR_Pos) /*!< Clear Interrupts. */

//DMACR offsetaddress : 0x4c
#define SPI_RDMAE_Pos (0U)
#define SPI_RDMAE_Msk (0x1UL << SPI_RDMAE_Pos) /*!< Receive DMA Enable. */
#define SPI_TDMAE_Pos (1U)
#define SPI_TDMAE_Msk (0x1UL << SPI_TDMAE_Pos) /*!< Transmit DMA Enable. */

//DMATDLR offsetaddress : 0x50
#define SPI_DMATDL_Pos (0U)
#define SPI_DMATDL_Msk (0xfUL << SPI_DMATDL_Pos) /*!< Transmit Data Level. */

//DMARDLR offsetaddress : 0x54
#define SPI_DMARDL_Pos (0U)
#define SPI_DMARDL_Msk (0xfUL << SPI_DMARDL_Pos) /*!< Receive Data Level. */

//IDR offsetaddress : 0x58
#define SPI_IDCODE_Pos (0U)
#define SPI_IDCODE_Msk (0xffffffffUL << SPI_IDCODE_Pos) /*!< Identification code. */

//SPI_VERSION_ID offsetaddress : 0x5c
#define SPI_SSI_COMP_VERSION_Pos (0U)
#define SPI_SSI_COMP_VERSION_Msk (0xffffffffUL << SPI_SSI_COMP_VERSION_Pos) /*!< Contains the hex representation of the Synopsys component version. */

//DRx offsetaddress : 0x60
#define SPI_DR_Pos (0U)
#define SPI_DR_Msk (0xffffffffUL << SPI_DR_Pos) /*!< Data Register. */

//RX_SAMPLE_DLY offsetaddress : 0xf0
#define SPI_RSD_Pos (0U)
#define SPI_RSD_Msk (0xffUL << SPI_RSD_Pos) /*!< Rxd Sample Delay. */

//SPI_CTRLR0 offsetaddress : 0xf4
#define SPI_TRANS_TYPE_Pos (0U)
#define SPI_TRANS_TYPE_Msk (0x3UL << SPI_TRANS_TYPE_Pos) /*!< Address and instruction transfer format. */
#define SPI_ADDR_L_Pos     (2U)
#define SPI_ADDR_L_Msk     (0xfUL << SPI_ADDR_L_Pos) /*!< Address Length. */

#define SPI_INST_L_Pos (8U)
#define SPI_INST_L_Msk (0x3UL << SPI_INST_L_Pos) /*!< Instruction Length Dual/Quad/Octal mode instruction length in bits. */

#define SPI_WAIT_CYCLES_Pos (11U)
#define SPI_WAIT_CYCLES_Msk (0x1fUL << SPI_WAIT_CYCLES_Pos) /*!< Wait cycles Number of wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. */
#define SPI_SPI_DDR_EN_Pos  (16U)
#define SPI_SPI_DDR_EN_Msk  (0x1UL << SPI_SPI_DDR_EN_Pos) /*!< SPI DDR Enable bit. */
#define SPI_INST_DDR_EN_Pos (17U)
#define SPI_INST_DDR_EN_Msk (0x1UL << SPI_INST_DDR_EN_Pos) /*!< Instruction DDR Enable bit. */
#define SPI_SPI_RXDS_EN_Pos (18U)
#define SPI_SPI_RXDS_EN_Msk (0x1UL << SPI_SPI_RXDS_EN_Pos) /*!< Read data strobe enable bit. */

//TXD_DRIVE_EDGE offsetaddress : 0xf8
#define SPI_TDE_Pos (0U)
#define SPI_TDE_Msk (0xffUL << SPI_TDE_Pos) /*!< TXD Drive edge - value of which decides the driving edge of tramit data. */

typedef struct {
    volatile uint32_t SPI_CTRLR0;     /* offset 0x0000 */
    volatile uint32_t SPI_CTRLR1;     /* offset 0x0004 */
    volatile uint32_t SPI_ENR;        /* offset 0x0008 */
    volatile uint32_t SPI_MWCR;       /* offset 0x000c */
    volatile uint32_t SPI_SER;        /* offset 0x0010 */
    volatile uint32_t SPI_BAUDR;      /* offset 0x0014 */
    volatile uint32_t SPI_TXFTLR;     /* offset 0x0018 */
    volatile uint32_t SPI_RXFTLR;     /* offset 0x001C */
    volatile uint32_t SPI_TXFLR;      /* offset 0x0020 */
    volatile uint32_t SPI_RXFLR;      /* offset 0x0024 */
    volatile uint32_t SPI_SR;         /* offset 0x0028 */
    volatile uint32_t SPI_IMR;        /* offset 0x002C */
    volatile uint32_t SPI_ISR;        /* offset 0x0030 */
    volatile uint32_t SPI_RISR;       /* offset 0x0034 */
    volatile uint32_t SPI_TXOICR;     /* offset 0x0038 */
    volatile uint32_t SPI_RXOICR;     /* offset 0x003c */
    volatile uint32_t SPI_RXUICR;     /* offset 0x0040 */
    volatile uint32_t SPI_MSTICR;     /* offset 0x0044 */
    volatile uint32_t SPI_ICR;        /* offset 0x0048 */
    volatile uint32_t SPI_DMACR;      /* offset 0x004c */
    volatile uint32_t SPI_DMATDLR;    /* offset 0x0050 */
    volatile uint32_t SPI_DMARDLR;    /* offset 0x0054 */
    volatile uint32_t SPI_IDR;        /* offset 0x0058 */
    volatile uint32_t SPI_VERSION_ID; /* offset 0x005C */
    volatile uint32_t SPI_DATA;       /* offset 0x0060 */
    volatile uint32_t rev_1[(0xF0 - 0x0060) / 4 - 1];
    volatile uint32_t SPI_RSD; /* offset 0xF0 */
} spi_reg_t;

#ifdef __cplusplus
}
#endif

#endif

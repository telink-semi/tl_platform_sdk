/********************************************************************************************************
 * @file    spi_reg.h
 *
 * @brief   This is the header file for tl322x
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef SPI_REG_H
#define SPI_REG_H
#include "soc.h"

/*******************************  gspi/lspi registers ******************************/
#define LSPI_BASE_ADDR  0x87FFFF00
#define GSPI_BASE_ADDR  0x8BFFFF00
#define BASE_ADDR_DIFF0 0x4000000
#define BASE_ADDR_DIFF1 0x8000000


/*******************************  gspi/lspi normal spi registers ******************************/
#define reg_spi_data_buf_adr(i) LSPI_BASE_ADDR + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0))

/**
 * BIT[0:7]   data0[7:0] to transmit or received.
 */
#define reg_spi_wr_rd_data0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x00 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   data1[7:0] to transmit or received.
 */
#define reg_spi_wr_rd_data1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x01 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   data2[7:0] to transmit or received.
 */
#define reg_spi_wr_rd_data2(i) REG_ADDR8(LSPI_BASE_ADDR + 0x02 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   data3[7:0] to transmit or received.
 */
#define reg_spi_wr_rd_data3(i)     REG_ADDR8(LSPI_BASE_ADDR + 0x03 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_wr_rd_data(i, j)   REG_ADDR8(LSPI_BASE_ADDR + 0x00 + (j) + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_wr_rd_data_word(i) REG_ADDR32(LSPI_BASE_ADDR + 0x00 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  SPI Command.
 */
#define reg_spi_cmd(i) REG_ADDR8(LSPI_BASE_ADDR + 0x04 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * When only Telink RISC-V MCU spi slave is used as slave, the command read from SPI Command is parsed by bit.
 */
enum
{
    FLD_SPI_CMD_RESERVED           = BIT(0),
    FLD_SPI_CMD_TRANS_HWORD        = BIT(1), //1  hword transfer.
    FLD_SPI_CMD_TRANS_WORD         = BIT(2), //1  word transfer.
    FLD_SPI_CMD_RD_DUMMY_4CYCLE    = BIT(3), // 0 8cycle 1 4cycle.
    FLD_SPI_CMD_ADDR_AUTO_INCREASE = BIT(4), // 0 AUTO incease.
    FLD_SPI_CMD_DATA_DUAL          = BIT(5), // 0 Single 1 DuaL.
    FLD_SPI_CMD_ADDR_DUAL          = BIT(6), // 0 Single 1 DuaL.
    FLD_SPI_CMD_RD_EN              = BIT(7), // 0  write 1 read.
};

/**
 * BIT[0] enable the SPI Receive FIFO Overrun interrupt. slave only.
 * BIT[1] enable the SPI Transmit FIFO Underrun interrupt. slave only.
 * BIT[2] enable the SPI Receive FIFO Threshold interrupt.master/slave.
 * BIT[3] enable the SPI Transmit FIFO Threshold interrupt.master/slave.
 * BIT[4] enable the SPI Transmit end interrupt.master/slave.
 * BIT[5] enable slvCmdint.The slave command interrupt is triggered each byte command received (starting 8 bit) .slave only.
 * BIT[6] enable RX DMA.
 * BIT[7] enable TX DMA.
 */
#define reg_spi_ctrl0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x05 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_RXFIFO_OR_INT_EN = BIT(0),
    FLD_SPI_TXFIFO_UR_INT_EN = BIT(1),
    FLD_SPI_RXFIFO_INT_EN    = BIT(2),
    FLD_SPI_TXFIFO_INT_EN    = BIT(3),
    FLD_SPI_END_INT_EN       = BIT(4),
    FLD_SPI_SLV_CMD_EN       = BIT(5),
    FLD_SPI_RX_DMA_EN        = BIT(6),
    FLD_SPI_TX_DMA_EN        = BIT(7),
};

/**
 * BIT[0:7] The second cmd of SPI. It will only be used when the slave supports two cmd modes. The cmd must be configured first, and then the first cmd must be configured.
 */
#define reg_spi_cmd1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x06 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:2]  the minimum time between the edge of SPI_CS and  the edges of SPI_CLK.the actual duration is (SPI_CLK period*(cs2sclk+1)),default=1, MASTER ONLY.
 * BIT[3:7]  the minimum time that SPI CS should stay HIGH.the actual duration is (SPI_CLK period*(csht+1)),default=1,MASTER ONLY.
 *           actual_csht[6:0] = {FLD_SPI_CSHT_HIGH, FLD_SPI_CSHT}.
 */
#define reg_spi_timing(i) REG_ADDR8(LSPI_BASE_ADDR + 0x07 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_CS2SCLK = BIT_RNG(0, 2),
    FLD_SPI_CSHT    = BIT_RNG(3, 7),

};

/**
 * BIT[0:1] data I/O MODE, 2'b00:single  2'b01:dual  2'b10:quad.MASTER ONLY.
 * BIT[2:3] address length.2'b00:1byte  2'b01:2bytes  2'b10:3bytes  2'b11:4bytes.MASTER ONLY.
 * BIT[4]  set address format 0:single mode  1:the format of addr phase is the same as the data phase(Dual/Quad),MASTER ONLY.
 * BIT[5]  1:enable addr phase, MASTER ONLY.
 * BIT[6]  set cmd format 0: single mode  1: the format of the cmd phase is the same as the data phase(Dual/Quad),MASTER ONLY.
 * BIT[7]  the spi command phase enable,MASTER ONLY.
 */
#define reg_spi_ctrl1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x08 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_DATA_LANE = BIT_RNG(0, 1),
    FLD_SPI_ADDR_LEN  = BIT_RNG(2, 3),
    FLD_SPI_ADDR_FMT  = BIT(4),
    FLD_SPI_ADDR_EN   = BIT(5),
    FLD_SPI_CMD_FMT   = BIT(6),
    FLD_SPI_CMD_EN    = BIT(7),
};

/**
 * BIT[0:3]  dummy data cnt, dummy is always single wire mode, dummy number = {dummy_cnt_add, dummy_cnt} + 1.default 7,master/slave.
 * BIT[4:7]  the transfer mode.master only.
 * the transfer sequence could be:
 * 0x0:write and read at the same time(must enable CmdEn).
 * 0x1:write only.
 * 0x2:read only(must enable CmdEn).
 * 0x3:write,read.
 * 0x4:read,write.
 * 0x5:write,dummy,read.
 * 0x6:read,dummy,write(must enable CmdEn).
 * 0x7:None Data(must enable CmdEn).
 * 0x8:Dummy,write.
 * 0x9:Dummy,read.
 * 0xa:Dummy,write and read.
 * 0xb~0xf:reserved.
 */
#define reg_spi_ctrl2(i) REG_ADDR8(LSPI_BASE_ADDR + 0x09 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_DUMMY_CNT = BIT_RNG(0, 3),
    FLD_SPI_TRANSMODE = BIT_RNG(4, 7),
};

/**
 * BIT[0]       enable spi second cmd.
 * BIT[2]       enable token mode.
 * BIT[4:5]     the minimum time that SPI CS should stay HIGH.the actual duration is (SPI_CLK period*(csht+1)),default=1,MASTER ONLY.
 *              actual_csht[6:0] = {FLD_SPI_CSHT_HIGH, FLD_SPI_CSHT}.
 * BIT[6]       set dummy hold.
 */
#define reg_spi_reg_ctrl0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x0a + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_CMD1_EN   = BIT(0),
    FLD_SPI_TOKEN_EN  = BIT(2),
    FLD_SPI_CSHT_HIGH = BIT_RNG(4, 5),
    FLD_DUMMY_HOLD    = BIT(6),
};

/**
 * BIT[0:7]  the tcem time that needs to be met for xip access to read psram.
 */
#define reg_xip_wr_tcem_set(i) REG_ADDR8(LSPI_BASE_ADDR + 0x0b + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  spi address byte0/lcd_porch_line_time[7:0].
 */
#define reg_spi_addr0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x0c + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  spi address byte1/lcd_porch_line_time[15:8].
 */
#define reg_spi_addr1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x0d + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  spi address byte2/lcd_display_line_time[7:0].
 */
#define reg_spi_addr2(i) REG_ADDR8(LSPI_BASE_ADDR + 0x0e + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  spi address byte3/lcd_display_line_time[15:8].
 */
#define reg_spi_addr3(i)     REG_ADDR8(LSPI_BASE_ADDR + 0x0f + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_addr(i, j)   REG_ADDR8(LSPI_BASE_ADDR + 0x0c + j + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_addr_word(i) REG_ADDR32(LSPI_BASE_ADDR + 0x0c + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   transfer count0 for write data, byte0/lcd_pixel_per_line[7:0].
 */
#define reg_spi_tx_cnt0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x10 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   transfer count1 for write data, byte1/{lcd_line_per_frame[5:0]lcd_pixel_per_line[9:8]}.
 */
#define reg_spi_tx_cnt1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x11 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]   transfer count2 for write data, byte2/{4'h0, lcd_line_per_frame[9:6]}.
 */
#define reg_spi_tx_cnt2(i) REG_ADDR8(LSPI_BASE_ADDR + 0x12 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_tx_cnt(i)  REG_ADDR32(LSPI_BASE_ADDR + 0x10 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  transfer count0 for read data, byte0.
 */
#define reg_spi_rx_cnt0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x14 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  transfer count1 for read data, byte1.
 */

#define reg_spi_rx_cnt1(i) REG_ADDR8(LSPI_BASE_ADDR + 0x15 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
/**
 * BIT[0:7]  transfer count2 for read data, byte2.
 */
#define reg_spi_rx_cnt2(i) REG_ADDR8(LSPI_BASE_ADDR + 0x16 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))
#define reg_spi_rx_cnt(i)  REG_ADDR32(LSPI_BASE_ADDR + 0x14 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0]  transfer data with least significant bit first.1: LSB  0: MSB default. master/slave.
 * BIT[1]  set 3line mode ,MOSI is bi-directional signal in regular mode.master only.
 * BIT[2:3] set spi 4 mode. master/slave.
 *  *  *      bit2: CPHA-SPI_CLK Phase,bit3: CPOL-SPI_CLK Polarity
 *            MODE0:  CPOL = 0 , CPHA = 0;
 *            MODE1:  CPOL = 0 , CPHA = 1;
 *            MODE2:  CPOL = 1 , CPHA = 0;
 *            MODE3:  CPOL = 1 , CPHA = 1;
 * BIT[4]  set master/slave mode. 0 slave 1 master default 1.master/slave.
 * BIT[5]  auto clr rxfifo when rxdma end.
 * BIT[6]  auto clr txfifo when txdma start.
 * BIT[7]  auto control hready while access data register.
 */
#define reg_spi_ctrl3(i) REG_ADDR8(LSPI_BASE_ADDR + 0x18 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_LSB                 = BIT(0),
    FLD_SPI_3LINE               = BIT(1),
    FLD_SPI_WORK_MODE           = BIT_RNG(2, 3),
    FLD_SPI_MASTER_MODE         = BIT(4),
    FLD_SPI_DMARX_EOF_CLRRXF_EN = BIT(5),
    FLD_SPI_DMATX_SOF_CLRTXF_EN = BIT(6),
    FLD_SPI_AUTO_HREADY_EN      = BIT(7),
};

/**
 * BIT[0:5]  txfifo threshold.
 */
#define reg_spi_txfifo_thres(i) REG_ADDR8(LSPI_BASE_ADDR + 0x19 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_TXF_THRES = BIT_RNG(0, 5),
};

/**
 * BIT[0:5]  rxfifo threshold.
 */
#define reg_spi_rxfifo_thres(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1a + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_RXF_THRES = BIT_RNG(0, 5),
};

/**
 * BIT[0]   pem event enable.
 * BIT[1]   pem task enable.
 * BIT[2]   pem event select.
 */
#define reg_spi_pem_ctrl0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1b + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_EVENT_EN      = BIT(0),
    FLD_TASK_EN       = BIT(1),
    FLD_PEM_EVENT_SEL = BIT(2),
};

/**
 * BIT[0]  0:disable trig spi dma signal  1:enable trig spi dma signal.
 * BIT[1]  1:receive cmd and then send request to dma.
 * BIT[2]  stop xip.
 * BIT[3]  enable xip.
 * BIT[4:7]  dummy_cnt_add, dummy is always single wire mode, dummy number = {dummy_cnt_add, dummy_cnt} + 1.master/slave.
 */
#define reg_spi_ctrl4(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1c + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_DMA_TRIG_SPI_EN = BIT(0),
    FLD_TXDMA_REQ_AF_CMD    = BIT(1),
    FLD_SPI_XIP_STOP        = BIT(2),
    FLD_SPI_XIP_ENABLE      = BIT(3),
    FLD_SPI_DUMMY_CNT_ADD   = BIT_RNG(4, 7),
};

/**
 * BIT[0:7]  use this combined with xip_mode being xip page mode.default page boundary size is 0, 2^page_size.
 */
#define reg_spi_xip_page_size(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1d + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  when XIP_TIMEOUT_MODE enable,timeout period=hclk period*timeout_cnt.
 */
#define reg_spi_xip_timeout_cnt(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1e + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  set The tcem time that needs to be met for xip access to read psram.
 */
#define reg_spi_xip_rd_tcem_set(i) REG_ADDR8(LSPI_BASE_ADDR + 0x1f + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:7]  xip address offset = xip_addr_offset << 24.
 */
#define reg_spi_xip_addr_offset(i) REG_ADDR8(LSPI_BASE_ADDR + 0x22 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

/**
 * BIT[0:6]  txfifo_entries.
 * BIT[7]    1:txfifo_full, default 0.
 */
#define reg_spi_txfifo_status(i) REG_ADDR8(LSPI_BASE_ADDR + 0x24 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_TXF_ENTRIES = BIT_RNG(0, 6),
    FLD_SPI_TXF_FULL    = BIT(7),
};

/**
 * BIT[0:6]  rxfifo_entries.
 * BIT[7]    1:rxfifo_empty,default 1.
 */
#define reg_spi_rxfifo_status(i) REG_ADDR8(LSPI_BASE_ADDR + 0x25 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_RXF_ENTRIES = BIT_RNG(0, 6),
    FLD_SPI_RXF_EMPTY   = BIT(7),
};

/**
 * BIT[0]  set this bit to indicate that spi as salve is ready for data transaction.
 * BIT[1]  clear spi slave ready.
 * BIT[2]  spi soft reset.high valid.
 * BIT[3]  xip mode and reg mode conflict flag.
 * BIT[4]  rxfifo is in clear status.
 * BIT[5]  txfifo is in clear status.
 * BIT[6]  osd ahbmster is in busy status.
 * BIT[7]  SPI transfer status.1 is busy, 0 not busy.
 */
#define reg_spi_status(i) REG_ADDR8(LSPI_BASE_ADDR + 0x28 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_SET_SLAVE_READY = BIT(0),
    FLD_SPI_CLR_SLAVE_READY = BIT(1),
    FLD_SPI_SOFT_RESET      = BIT(2),
    FLD_SPI_REG_ARB_ERR     = BIT(3),
    FLD_SPI_RXF_CLR_LEVEL   = BIT(4),
    FLD_SPI_TXF_CLR_LEVEL   = BIT(5),
    FLD_SPI_OSD_AHBMST_BUSY = BIT(6),
    FLD_SPI_BUSY            = BIT(7),
};

/**
 * BIT[0:3]  the transfer mode.slave only.
 * the transfer sequence could be:
 * 0x0:write and read at the same time(must enable CmdEn).
 * 0x1:write only.
 * 0x2:read only(must enable CmdEn).
 * 0x3:write,read.
 * 0x4:read,write.
 * 0x5:write,dummy,read.
 * 0x6:read,dummy,write(must enable CmdEn).
 * 0x7:None Data(must enable CmdEn).
 * 0x8:Dummy,write.
 * 0x9:Dummy,read.
 * 0xa:Dummy,write and read.
 * 0xb~0xf:reserved.
 */
#define reg_spi_slv_trans_mode(i) REG_ADDR8(LSPI_BASE_ADDR + 0x29 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_SLV_TRANS_MODE = BIT_RNG(0, 3),
};

/**
 * BIT[0]  RX FIFO Overrun interrupt status.set 1 to clear. slave only.
 * BIT[1]  TX FIFO Underrun interrupt status.set 1 to clear. slave only.
 * BIT[2]  RX FIFO Threshold interrupt status.set 1 to clear. master/slave.
 * BIT[3]  TX FIFO Threshold interrupt status.set 1 to clear. master/slave.
 * BIT[4]  End of SPI Transfer interrupt status.set 1 to clear.master/slave.
 * BIT[5]  Slave Command Interrupt status.set 1 to clear.slave only.
 */
#define reg_spi_int_status0(i) REG_ADDR8(LSPI_BASE_ADDR + 0x2a + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_RXF_OR_INT  = BIT(0),
    FLD_SPI_TXF_UR_INT  = BIT(1),
    FLD_SPI_RXF_INT     = BIT(2),
    FLD_SPI_TXF_INT     = BIT(3),
    FLD_SPI_END_INT     = BIT(4),
    FLD_SPI_SLV_CMD_INT = BIT(5),
};

/*******************************  gspi/lspi normal xip mode registers ******************************/
/**
 * BIT[0:1]  spi xip read I/O mode, 2'b00 single,2'b01 dual, 2'b10 quad. XIP ONLY.
 * BIT[2:3]  xip read address length.2'b00:1bye  2'b01:2bytes  2'b10:3bytes  2'b11:4bytes.XIP ONLY.
 * BIT[4]  set xip read address format 0:single mode  1:the format of addr phase is the same as the data phase(Dual/Quad),XIP ONLY.
 * BIT[5]  1:enable xip read addr phase, XIP ONLY.
 * BIT[6]  xip read cmd format 0: single mode  1: the format of the cmd phase is the same as the data phase(Dual/Quad),XIP ONLY.
 * BIT[7]  xip read spi command phase enable,XIP ONLY
 * BIT[8:11]   xip read dummy data cnt, dummy is always single wire mode, dummy number = (dummy_cnt_add,dummy_cnt) + 1.XIP ONLY.
 * BIT[12:15]   xip read transmode/lcd display transmode.
 *              the transfer sequence could be:
 *              0x0:write and read at the same time(must enable CmdEn).
 *              0x1:write only.
 *              0x2:read only(must enable CmdEn).
 *              0x3:write,read.
 *              0x4:read,write.
 *              0x5:write,dummy,read.
 *              0x6:read,dummy,write(must enable CmdEn).
 *              0x7:None Data(must enable CmdEn).
 *              0x8:Dummy,write.
 *              0x9:Dummy,read.
 *              0xa:Dummy,write and read.
 *              0xb~0xf:reserved.
 * BIT[16]      enable spi second cmd.
 * BIT[17]      select token val.0:0x00,1:0x69.
 * BIT[18]      enable token mode.
 * BIT[19]      bit[4] dummy_cnt_add.
 * BIT[21]      enable page mode.
 * BIT[22]      enable timeout mode(after the set time, the slice selection is pulled up).
 * BIT[23]      enable tcem mode(the chip selection pin is pulled low for more than a set amount of time and then pulled up).
 * BIT[24:31]   read command used for xip.
 */
#define reg_lspi_rd_config    REG_ADDR32(LSPI_BASE_ADDR + 0x90)
#define reg_gspi_rd_config(i) REG_ADDR32(GSPI_BASE_ADDR + 0x90 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

typedef enum
{
    FLD_SPI_XIP_RD_DATA_LANE_MODE = BIT_RNG(0, 1),
    FLD_SPI_XIP_RD_ADDR_LEN       = BIT_RNG(2, 3),
    FLD_SPI_XIP_RD_ADDR_FMT       = BIT(4),
    FLD_SPI_XIP_RD_ADDR_EN        = BIT(5),
    FLD_SPI_XIP_RD_CMD_FMT        = BIT(6),
    FLD_SPI_XIP_RD_CMD_EN         = BIT(7),
    FLD_SPI_XIP_RD_DUMMY_CNT      = BIT_RNG(8, 11),
    FLD_SPI_XIP_RD_TRANSMODE      = BIT_RNG(12, 15),
    FLD_SPI_XIP_RD_CMD1_EN        = BIT(16),
    FLD_SPI_XIP_RD_TOKEN_VAL_SEL  = BIT(17),
    FLD_SPI_XIP_RD_TOKEN_EN       = BIT(18),
    FLD_SPI_XIP_RD_DUMMY_CNT_ADD  = BIT(19),
    FLD_SPI_XIP_RD_PAGE_MODE      = BIT(21),
    FLD_SPI_XIP_RD_TIMEOUT_MODE   = BIT(22),
    FLD_SPI_XIP_RD_TCEM_MODE      = BIT(23),
    FLD_SPI_XIP_RD_CMD            = BIT_RNG(24, 31),
} spi_xip_rd_fmt_e;

/**
 * BIT[0:1]  spi xip write I/O mode, 2'b00 single,2'b01 dual, 2'b10 quad. XIP ONLY
 * BIT[2:3]  xip write address length.2'b00:1byte  2'b01:2bytes  2'b10:3bytes  2'b11:4bytes.XIP ONLY.
 * BIT[4]  set xip write address format 0:single mode  1:the format of addr phase is the same as the data phase(Dual/Quad),XIP ONLY.
 * BIT[5]  1:enable xip write addr phase, XIP ONLY.
 * BIT[6]  xip write cmd format 0: single mode  1: the format of the cmd phase is the same as the data phase(Dual/Quad),XIP ONLY.
 * BIT[7]  xip write spi command phase enable,XIP ONLY.
 * BIT[8:11]   xip read dummy data cnt, dummy is always single wire mode, dummy number = (dummy_cnt_add,dummy_cnt) + 1.XIP ONLY.
 * BIT[12:15]   xip write transmode/lcd display transmode.
 *              the transfer sequence could be:
 *              0x0:write and read at the same time(must enable CmdEn).
 *              0x1:write only.
 *              0x2:read only(must enable CmdEn).
 *              0x3:write,read.
 *              0x4:read,write.
 *              0x5:write,dummy,read.
 *              0x6:read,dummy,write(must enable CmdEn).
 *              0x7:None Data(must enable CmdEn).
 *              0x8:Dummy,write.
 *              0x9:Dummy,read.
 *              0xa:Dummy,write and read.
 *              0xb~0xf:reserved.
 * BIT[16]      enable spi second cmd.
 * BIT[24:31]   write command used for xip.
 */
#define reg_lspi_wr_config    REG_ADDR32(LSPI_BASE_ADDR + 0x94)
#define reg_gspi_wr_config(i) REG_ADDR32(GSPI_BASE_ADDR + 0x94 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

typedef enum
{
    FLD_SPI_XIP_WR_DATA_LANE_MODE = BIT_RNG(0, 1),
    FLD_SPI_XIP_WR_ADDR_LEN       = BIT_RNG(2, 3),
    FLD_SPI_XIP_WR_ADDR_FMT       = BIT(4),
    FLD_SPI_XIP_WR_ADDR_EN        = BIT(5),
    FLD_SPI_XIP_WR_CMD_FMT        = BIT(6),
    FLD_SPI_XIP_WR_CMD_EN         = BIT(7),
    FLD_SPI_XIP_WR_DUMMY_CNT      = BIT_RNG(8, 11),
    FLD_SPI_XIP_WR_TRANSMODE      = BIT_RNG(12, 15),
    FLD_SPI_XIP_WR_CMD1_EN        = BIT(16),
    FLD_SPI_XIP_WR_CMD            = BIT_RNG(24, 31),
} spi_xip_wr_fmt_e;

/**
 * BIT[0:7]  Setting the token value for xip mode.
 */
#define reg_spi_xip_token_val(i) REG_ADDR8(LSPI_BASE_ADDR + 0xe2 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_XIP_TOKEN_VAL = BIT_RNG(0, 7),
};

/**
 * BIT[0:7]  Setting the token value for reg mode.
 */
#define reg_spi_reg_token_val(i) REG_ADDR8(LSPI_BASE_ADDR + 0xe2 + (((i) >= 1) ? (BASE_ADDR_DIFF0) : (0)) + (((i) > 1) ? (BASE_ADDR_DIFF1 + BASE_ADDR_DIFF0 * ((i) - 2)) : (0)))

enum
{
    FLD_SPI_REG_TOKEN_VAL = BIT_RNG(0, 7),
};

/******************************* lspi lcd mode registers ******************************/
/**
 * BIT[0:15]  spi_clk number between porch line and next line.
 */
#define reg_lspi_lcd_porch_line_time REG_ADDR16(LSPI_BASE_ADDR + 0x0c)
/**
 * BIT[0:15]  spi_clk number between display line and next line.
 */
#define reg_lspi_lcd_display_line_time REG_ADDR16(LSPI_BASE_ADDR + 0x0e)
/**
 * BIT[0:9]     lcd row resolution.
 * BIT[10:19]   lcd line resolution.
 */
#define reg_lspi_lcd_frame_res REG_ADDR32(LSPI_BASE_ADDR + 0x10)

enum
{
    FLD_LSPI_LCD_PIXEL_PER_LINE = BIT_RNG(0, 9),
    FLD_LSPI_LCD_LINE_PER_FRAME = BIT_RNG(10, 19),
};

/**
 * BIT[0]  lcd line interrupt status.set 1 to clear.
 * BIT[1]  lcd line level interrupt status.set 1 to clear.
 * BIT[2]  lcd frame interrupt status.set 1 to clear.
 */
#define reg_lspi_int_status1 REG_ADDR8(LSPI_BASE_ADDR + 0x2b)

typedef enum
{
    FLD_LSPI_LCD_LINE_INT_STA  = BIT(0),
    FLD_LSPI_LCD_LVL_INT_STA   = BIT(1),
    FLD_LSPI_LCD_FRAME_INT_STA = BIT(2),
} lspi_lcd_irq_status_e;

/**
 * BIT[0] 1: single color mode, use lut1.
 * BIT[1] 1:big endian mode;  0:little endian mode.
 * BIT[2] 1:enable 4bit_mode.
 * BIT[3] lcd_line_irq_mask  1: every line send complete would trigger interrupt.
 * BIT[4] lcd_line_lvl_irq_mask 1: The number of send line reached trigger level would trigger interrupt.
 * BIT[5] lcd_frame_irq_mask 1: every frame send complete would trigger interrupt.
 */
#define reg_lspi_lcd_ctrl2 REG_ADDR8(LSPI_BASE_ADDR + 0x2f)

enum
{
    FLD_LSPI_LCD_SINGLE_COLOR_MODE   = BIT(0),
    FLD_LSPI_LCD_RGB_BIG_ENDIAN_MODE = BIT(1),
    FLD_LSPI_LCD_RAM_4BIT_MODE       = BIT(2),
};

typedef enum
{
    FLD_LSPI_LCD_LINE_INT_EN  = BIT(3),
    FLD_LSPI_LCD_LVL_INT_EN   = BIT(4),
    FLD_LSPI_LCD_FRAME_INT_EN = BIT(5),
} lspi_lcd_irq_mask;

/**
 * BIT[0] 1: enable lspi lcd scan.
 * BIT[1] 1:big endian mode;  0:little endian mode.
 * BIT[2] 1:enable 4bit_mode.
 * BIT[3] lcd_line_irq_mask.
 * BIT[4] lcd_line_lvl_irq_mask.
 * BIT[5] lcd_frame_irq_mask.
 */
#define reg_lspi_lcd_ctrl REG_ADDR8(LSPI_BASE_ADDR + 0x30)

enum
{
    FLD_LSPI_LCD_SCAN_EN      = BIT(0),
    FLD_LSPI_LCD_RGB_MODE     = BIT_RNG(1, 2),
    FLD_LSPI_LCD_2LANE_EN     = BIT(3),
    FLD_LSPI_LCD_3LINE_DCX_EN = BIT(6),
    FLD_LSPI_LCD_DCX          = BIT(7),
};

/**
 * BIT[0:7]  lcd vertical porch line number.
 */
#define reg_lspi_lcd_vbp_line_cnt REG_ADDR8(LSPI_BASE_ADDR + 0x31)
/**
 * BIT[0:7]  lcd front porch line number.
 */
#define reg_lspi_lcd_vfp_line_cnt REG_ADDR8(LSPI_BASE_ADDR + 0x32)
/**
 * BIT[0:7]  lcd line threshold to trig interrupt.trigger level = reg_lspi_lcd_line_lvl<<2.
 */
#define reg_lspi_lcd_line_trig_lvl REG_ADDR8(LSPI_BASE_ADDR + 0x33)
/**
 * BIT[0:31]  background image data start address.
 */
#define reg_lspi_lcd_bimage_start_addr32 REG_ADDR32(LSPI_BASE_ADDR + 0x34)
/**
 * BIT[0:31]  front image data start address.
 */
#define reg_lspi_lcd_fimage_start_addr32 REG_ADDR32(LSPI_BASE_ADDR + 0x38)
/**
 * BIT[0:9]  lcd send line count.
 */
#define reg_lspi_lcd_line_cnt16 REG_ADDR16(LSPI_BASE_ADDR + 0x3e)

enum
{
    FLD_LSPI_LCD_SEND_LINE_COUNT = BIT_RNG(0, 9),
};

/**
 * BIT[0:7]   lcd lut address data byte0.
 * BIT[8:15]  lcd lut address data byte1.
 * BIT[16:24] lcd lut address data byte2.
 * i = [0, 15],j = [0, 2].
 */
#define reg_lspi_lcd_lut_data32(i) REG_ADDR32(LSPI_BASE_ADDR + 0x40 + (i << 2))

/**
* BIT[4:7]  lcd display transfer mode.
*           the transfer sequence could be:
*           0x0:write and read at the same time(must enable CmdEn).
*           0x1:write only.
*           0x2:read only(must enable CmdEn).
*           0x3:write,read.
*           0x4:read,write.
*           0x5:write,dummy,read.
*           0x6:read,dummy,write(must enable CmdEn).
*           0x7:None Data(must enable CmdEn).
*           0x8:Dummy,write.
*           0x9:Dummy,read.
*           0xa~0xf:reserved.
*/
#define reg_lspi_lcd_display_transmode REG_ADDR8(LSPI_BASE_ADDR + 0x91)

enum
{
    FLD_LSPI_LCD_DISPLAY_TRANSMODE = BIT_RNG(4, 7),
};

/**
* BIT[4:7]  lcd porch transfer mode.
*           the transfer sequence could be:
*           0x0:write and read at the same time(must enable CmdEn).
*           0x1:write only.
*           0x2:read only(must enable CmdEn).
*           0x3:write,read.
*           0x4:read,write.
*           0x5:write,dummy,read.
*           0x6:read,dummy,write(must enable CmdEn).
*           0x7:None Data(must enable CmdEn).
*           0x8:Dummy,write.
*           0x9:Dummy,read.
*           0xa~0xf:reserved.
*/
#define reg_lspi_lcd_porch_transmode REG_ADDR8(LSPI_BASE_ADDR + 0x95)

enum
{
    FLD_LSPI_LCD_PORCH_TRANSMODE = BIT_RNG(4, 7),
};

/**
* BIT[0:7]  lcd porch cmd.
*/
#define reg_lspi_lcd_cmd REG_ADDR8(LSPI_BASE_ADDR + 0x97)

/**
 * BIT[0:7] The second cmd of SPI. It will only be used when the slave supports two cmd modes. The cmd must be configured first, and then the first cmd must be configured.
 */
#define reg_lspi_xip_rd_cmd1 REG_ADDR8(LSPI_BASE_ADDR + 0xb4)

/**
 * BIT[0:7] The second cmd of SPI. It will only be used when the slave supports two cmd modes. The cmd must be configured first, and then the first cmd must be configured.
 */
#define reg_lspi_xip_wr_cmd1 REG_ADDR8(LSPI_BASE_ADDR + 0xb5)
#endif

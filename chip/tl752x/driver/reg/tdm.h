/*******************************************************************************************************
 *
 * @file    tdm.h
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
#ifndef __TDM_H__
#define __TDM_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//TDM_TRANS_EN offsetaddress : 0x0000
//TDM_TRANS_EN RegResetValue : 0x00000000
#define TDM_TDM_ENABLE_POS (0U)
#define TDM_TDM_ENABLE_MSK (0x1UL << TDM_TDM_ENABLE_POS) /*!< 1: Enable Transfer 0: Disalbe Transfer*/
#define TDM_TDM_ENABLE     TDM_TDM_ENABLE_MSK

//TDM_CONFIG offsetaddress : 0x0004
//TDM_CONFIG RegResetValue : 0x30000000
#define TDM_MODE_SEL_POS        (0U)
#define TDM_MODE_SEL_MSK        (0x1UL << TDM_MODE_SEL_POS) /*!< TDM/I2S mode select 0: TDM mode 1: I2S mode*/
#define TDM_MODE_SEL            TDM_MODE_SEL_MSK
#define TDM_SLOT_WIDTH_POS      (4U)
#define TDM_SLOT_WIDTH_MSK      (0x7UL << TDM_SLOT_WIDTH_POS) /*!< Each Slot Width Configure 1: 8 bits 2: 12 bits  3: 16 bits 4: 20 bits 5: 24 bits 6: 28 bits 7: 32 bits 0: NA*/
#define TDM_SLOT_WIDTH          TDM_SLOT_WIDTH_MSK
#define TDM_SLOT_NUM_POS        (8U)
#define TDM_SLOT_NUM_MSK        (0xfUL << TDM_SLOT_NUM_POS) /*!< Slot number, only use for TDM 0: 1 slot 1: 2 slots ...7: 8 slots*/
#define TDM_SLOT_NUM            TDM_SLOT_NUM_MSK
#define TDM_SLOT_RESOLUTION_POS (12U)
#define TDM_SLOT_RESOLUTION_MSK (0x7UL << TDM_SLOT_RESOLUTION_POS) /*!< Data resolution in each slot 1: 8 bits 2: 12 bits 3: 16 bits 4: 20 bits 5: 24 bits 6: 28 bits 7: 32 bits 0: NA*/
#define TDM_SLOT_RESOLUTION     TDM_SLOT_RESOLUTION_MSK
#define TDM_I2S_CHEN_POS        (16U)
#define TDM_I2S_CHEN_MSK        (0xfUL << TDM_I2S_CHEN_POS) /*!< I2S Channel Enable each bit enable each channel  0001: enable ch0  0011: enable ch0 and ch1 0101: enable ch0 and ch2*/
#define TDM_I2S_CHEN            TDM_I2S_CHEN_MSK
#define TDM_I2S_CHTXRX_POS      (20U)
#define TDM_I2S_CHTXRX_MSK      (0xfUL << TDM_I2S_CHTXRX_POS) /*!< I2S each Channel Transmit Receive Select 0: TX 1: RX*/
#define TDM_I2S_CHTXRX          TDM_I2S_CHTXRX_MSK
#define TDM_DATA_EXTENTION_POS  (24U)
#define TDM_DATA_EXTENTION_MSK  (0x1UL << TDM_DATA_EXTENTION_POS) /*!< 0: 0 padding at LSB 1: Sign extension at MSB*/
#define TDM_DATA_EXTENTION      TDM_DATA_EXTENTION_MSK
#define TDM_EDGE_TRANSFER_POS   (25U)
#define TDM_EDGE_TRANSFER_MSK   (0x1UL << TDM_EDGE_TRANSFER_POS) /*!< 0: SDOOUT and SDIN drive data at the same SCLK edge 1: SDOOUT and SDIN drive data at the same SCLK edge*/
#define TDM_EDGE_TRANSFER       TDM_EDGE_TRANSFER_MSK
#define TDM_LOOP_TEST_POS       (26U)
#define TDM_LOOP_TEST_MSK       (0x1UL << TDM_LOOP_TEST_POS) /*!< Loop Test 1: connect TDM SDOUT to SDIN internal*/
#define TDM_LOOP_TEST           TDM_LOOP_TEST_MSK
#define TDM_OUT_MUTE_POS        (27U)
#define TDM_OUT_MUTE_MSK        (0x1UL << TDM_OUT_MUTE_POS) /*!< SDOUT mute to 0  1: mute enable  0: mute disable*/
#define TDM_OUT_MUTE            TDM_OUT_MUTE_MSK
#define TDM_TDM_TXEN_POS        (28U)
#define TDM_TDM_TXEN_MSK        (0x1UL << TDM_TDM_TXEN_POS) /*!< TDM Transmit channel Enable 1: enable 0: disable*/
#define TDM_TDM_TXEN            TDM_TDM_TXEN_MSK
#define TDM_TDM_RXEN_POS        (29U)
#define TDM_TDM_RXEN_MSK        (0x1UL << TDM_TDM_RXEN_POS) /*!< TDM Receive channel Enable 1: enable 0: disable*/
#define TDM_TDM_RXEN            TDM_TDM_RXEN_MSK

//TDM_CLOCK_GEN offsetaddress : 0x0008
//TDM_CLOCK_GEN RegResetValue : 0x00000000
#define TDM_MASTEREN_POS        (0U)
#define TDM_MASTEREN_MSK        (0x1UL << TDM_MASTEREN_POS) /*!< 1: SCLK and WS as output 0: SCLK and WS as input*/
#define TDM_MASTEREN            TDM_MASTEREN_MSK
#define TDM_SCLK_POLARITY_POS   (1U)
#define TDM_SCLK_POLARITY_MSK   (0x1UL << TDM_SCLK_POLARITY_POS) /*!< SCLK polarity 0: drive data at negative edge and sample data at posedge edge 1: drive data at posedge edge and sample data at negative edge*/
#define TDM_SCLK_POLARITY       TDM_SCLK_POLARITY_MSK
#define TDM_WS_FORMAT_POS       (2U)
#define TDM_WS_FORMAT_MSK       (0x3UL << TDM_WS_FORMAT_POS) /*!< For TDM WS signal mode: 1: Left-justified 0: Standard CPU2 Mode For I2S WS signal mode: 3: NA 2: Right-justifed 1: Left-justified 0: Standard I2S Mode*/
#define TDM_WS_FORMAT           TDM_WS_FORMAT_MSK
#define TDM_WS_POLARITY_I2S_POS (4U)
#define TDM_WS_POLARITY_I2S_MSK (0x1UL << TDM_WS_POLARITY_I2S_POS) /*!< For I2S mode 0: WS 0 left channel, 1 right channel 1: WS 1 left channel, 0 right channel For TDM mode 0: WS aligned to SCLK negedge edge 1: WS aligned to SCLK posedge edge*/
#define TDM_WS_POLARITY_I2S     TDM_WS_POLARITY_I2S_MSK
#define TDM_WS_WIDTH_TDM_POS    (5U)
#define TDM_WS_WIDTH_TDM_MSK    (0x1UL << TDM_WS_WIDTH_TDM_POS) /*!< WS signal width: 0: 1 SCLK cycle 1: 2 SCLK cycle*/
#define TDM_WS_WIDTH_TDM        TDM_WS_WIDTH_TDM_MSK
#define TDM_SCLK_ENABLE_POS     (8U)
#define TDM_SCLK_ENABLE_MSK     (0x1UL << TDM_SCLK_ENABLE_POS) /*!< "Enable final SCLK 0: disable 1: enable"*/
#define TDM_SCLK_ENABLE         TDM_SCLK_ENABLE_MSK

//TDM_RXFIFO_DATA offsetaddress : 0x000C
//TDM_RXFIFO_DATA RegResetValue : 0x00000000
#define TDM_RXFIFO_DATA_POS (0U)
#define TDM_RXFIFO_DATA_MSK (0xffffffffUL << TDM_RXFIFO_DATA_POS) /*!< RX FIFO Received Data Each read pop one 32bit data from RX FIFO*/

//TDM_TXFIFO_DATA offsetaddress : 0x0010
//TDM_TXFIFO_DATA RegResetValue : 0x00000000
#define TDM_TXFIFO_DATA_POS (0U)
#define TDM_TXFIFO_DATA_MSK (0xffffffffUL << TDM_TXFIFO_DATA_POS) /*!< TX FIFO transmit Data Each read pop one 32bit data from TX FIFO*/

//TDM_FIFO_STATUS offsetaddress : 0x0014
//TDM_FIFO_STATUS RegResetValue : 0x00000303
#define TDM_RXFIFO_AEMPTY_POS     (0U)
#define TDM_RXFIFO_AEMPTY_MSK     (0x1UL << TDM_RXFIFO_AEMPTY_POS) /*!< RX FIFO almost empty status*/
#define TDM_RXFIFO_AEMPTY         TDM_RXFIFO_AEMPTY_MSK
#define TDM_RXFIFO_EMPTY_POS      (1U)
#define TDM_RXFIFO_EMPTY_MSK      (0x1UL << TDM_RXFIFO_EMPTY_POS) /*!< RX FIFO empty status*/
#define TDM_RXFIFO_EMPTY          TDM_RXFIFO_EMPTY_MSK
#define TDM_RXFIFO_AFULL_POS      (2U)
#define TDM_RXFIFO_AFULL_MSK      (0x1UL << TDM_RXFIFO_AFULL_POS) /*!< RX FIFO almost full status*/
#define TDM_RXFIFO_AFULL          TDM_RXFIFO_AFULL_MSK
#define TDM_RXFIFO_FULL_POS       (3U)
#define TDM_RXFIFO_FULL_MSK       (0x1UL << TDM_RXFIFO_FULL_POS) /*!< RX FIFO full status*/
#define TDM_RXFIFO_FULL           TDM_RXFIFO_FULL_MSK
#define TDM_RXFIFO_RXLVL_TRIG_POS (4U)
#define TDM_RXFIFO_RXLVL_TRIG_MSK (0x1UL << TDM_RXFIFO_RXLVL_TRIG_POS) /*!< RXFIFO level trigger status 1: Data in RXFIFO  more than number in DMA_RXLVL 0: Data in RXFIFO  less than number in DMA_RXLVL*/
#define TDM_RXFIFO_RXLVL_TRIG     TDM_RXFIFO_RXLVL_TRIG_MSK
#define TDM_RXFIFO_POP_ERROR_POS  (5U)
#define TDM_RXFIFO_POP_ERROR_MSK  (0x1UL << TDM_RXFIFO_POP_ERROR_POS) /*!< RXFIFO pop error status*/
#define TDM_RXFIFO_POP_ERROR      TDM_RXFIFO_POP_ERROR_MSK
#define TDM_RXFIFO_PUSH_ERROR_POS (6U)
#define TDM_RXFIFO_PUSH_ERROR_MSK (0x1UL << TDM_RXFIFO_PUSH_ERROR_POS) /*!< RXFIFO push error status*/
#define TDM_RXFIFO_PUSH_ERROR     TDM_RXFIFO_PUSH_ERROR_MSK
#define TDM_RXFIFO_FLUSH_POS      (7U)
#define TDM_RXFIFO_FLUSH_MSK      (0x1UL << TDM_RXFIFO_FLUSH_POS) /*!< RX FIFO flush: 1: flush RX FIFO 0: no action*/
#define TDM_RXFIFO_FLUSH          TDM_RXFIFO_FLUSH_MSK
#define TDM_TXFIFO_AEMPTY_POS     (8U)
#define TDM_TXFIFO_AEMPTY_MSK     (0x1UL << TDM_TXFIFO_AEMPTY_POS) /*!< TX FIFO almost empty status*/
#define TDM_TXFIFO_AEMPTY         TDM_TXFIFO_AEMPTY_MSK
#define TDM_TXFIFO_EMPTY_POS      (9U)
#define TDM_TXFIFO_EMPTY_MSK      (0x1UL << TDM_TXFIFO_EMPTY_POS) /*!< TX FIFO empty status*/
#define TDM_TXFIFO_EMPTY          TDM_TXFIFO_EMPTY_MSK
#define TDM_TXFIFO_AFULL_POS      (10U)
#define TDM_TXFIFO_AFULL_MSK      (0x1UL << TDM_TXFIFO_AFULL_POS) /*!< TX FIFO almost full status*/
#define TDM_TXFIFO_AFULL          TDM_TXFIFO_AFULL_MSK
#define TDM_TXFIFO_FULL_POS       (11U)
#define TDM_TXFIFO_FULL_MSK       (0x1UL << TDM_TXFIFO_FULL_POS) /*!< TX FIFO full status*/
#define TDM_TXFIFO_FULL           TDM_TXFIFO_FULL_MSK
#define TDM_TXFIFO_TXLVL_TRIG_POS (12U)
#define TDM_TXFIFO_TXLVL_TRIG_MSK (0x1UL << TDM_TXFIFO_TXLVL_TRIG_POS) /*!< TXFIFO level trigger status 1: Data in TXFIFO  less or equal than number in DMA_TXLVL 0: Data in TXFIFO  more than number in DMA_TXLVL*/
#define TDM_TXFIFO_TXLVL_TRIG     TDM_TXFIFO_TXLVL_TRIG_MSK
#define TDM_TXFIFO_POP_ERROR_POS  (13U)
#define TDM_TXFIFO_POP_ERROR_MSK  (0x1UL << TDM_TXFIFO_POP_ERROR_POS) /*!< TXFIFO pop error status*/
#define TDM_TXFIFO_POP_ERROR      TDM_TXFIFO_POP_ERROR_MSK
#define TDM_TXFIFO_PUSH_ERROR_POS (14U)
#define TDM_TXFIFO_PUSH_ERROR_MSK (0x1UL << TDM_TXFIFO_PUSH_ERROR_POS) /*!< TXFIFO push error status*/
#define TDM_TXFIFO_PUSH_ERROR     TDM_TXFIFO_PUSH_ERROR_MSK
#define TDM_TXFIFO_FLUSH_POS      (15U)
#define TDM_TXFIFO_FLUSH_MSK      (0x1UL << TDM_TXFIFO_FLUSH_POS) /*!< TX FIFO flush: 1: flush TX FIFO 0: no action*/
#define TDM_TXFIFO_FLUSH          TDM_TXFIFO_FLUSH_MSK

//TDM_DMA_CONFIG offsetaddress : 0x0018
//TDM_DMA_CONFIG RegResetValue : 0x00000000
#define TDM_DMA_RXLVL_POS (0U)
#define TDM_DMA_RXLVL_MSK (0xffUL << TDM_DMA_RXLVL_POS) /*!< RXFIFO DMA trigger level Configure the RX DMA trigger level to generate one DMA transfer*/
#define TDM_DMA_RXLVL     TDM_DMA_RXLVL_MSK
#define TDM_DMA_TXLVL_POS (8U)
#define TDM_DMA_TXLVL_MSK (0xffUL << TDM_DMA_TXLVL_POS) /*!< TXFIFO DMA trigger level Configure the TX DMA trigger level to generate one DMA transfer*/
#define TDM_DMA_TXLVL     TDM_DMA_TXLVL_MSK
#define TDM_DMA_RX_EN_POS (16U)
#define TDM_DMA_RX_EN_MSK (0x1UL << TDM_DMA_RX_EN_POS) /*!< RX DMA enabe 1: enable RX DMA 0: disable RX DMA*/
#define TDM_DMA_RX_EN     TDM_DMA_RX_EN_MSK
#define TDM_DMA_TX_EN_POS (17U)
#define TDM_DMA_TX_EN_MSK (0x1UL << TDM_DMA_TX_EN_POS) /*!< TX DMA enabe 1: enable TX DMA 0: disable TX DMA*/
#define TDM_DMA_TX_EN     TDM_DMA_TX_EN_MSK

//TDM_INT offsetaddress : 0x0020
//TDM_INT RegResetValue : 0x00000000
#define TDM_RXFIFO_DATA_READY_POS (0U)
#define TDM_RXFIFO_DATA_READY_MSK (0x1UL << TDM_RXFIFO_DATA_READY_POS) /*!< RX FIFO data number are more than DMA_RXLVL setting*/
#define TDM_RXFIFO_DATA_READY     TDM_RXFIFO_DATA_READY_MSK
#define TDM_RXFIFO_OVERFLOW_POS   (1U)
#define TDM_RXFIFO_OVERFLOW_MSK   (0x1UL << TDM_RXFIFO_OVERFLOW_POS) /*!< RX FIFO is overflow*/
#define TDM_RXFIFO_OVERFLOW       TDM_RXFIFO_OVERFLOW_MSK
#define TDM_RXFIFO_UNDERFLOW_POS  (2U)
#define TDM_RXFIFO_UNDERFLOW_MSK  (0x1UL << TDM_RXFIFO_UNDERFLOW_POS) /*!< RX FIFO is underflow*/
#define TDM_RXFIFO_UNDERFLOW      TDM_RXFIFO_UNDERFLOW_MSK
#define TDM_TXFIFO_DATA_READY_POS (4U)
#define TDM_TXFIFO_DATA_READY_MSK (0x1UL << TDM_TXFIFO_DATA_READY_POS) /*!< TX FIFO data number are more than DMA_TXLVL setting*/
#define TDM_TXFIFO_DATA_READY     TDM_TXFIFO_DATA_READY_MSK
#define TDM_TXFIFO_OVERFLOW_POS   (5U)
#define TDM_TXFIFO_OVERFLOW_MSK   (0x1UL << TDM_TXFIFO_OVERFLOW_POS) /*!< TX FIFO is overflow*/
#define TDM_TXFIFO_OVERFLOW       TDM_TXFIFO_OVERFLOW_MSK
#define TDM_TXFIFO_UNDERFLOW_POS  (6U)
#define TDM_TXFIFO_UNDERFLOW_MSK  (0x1UL << TDM_TXFIFO_UNDERFLOW_POS) /*!< TX FIFO is underflow*/
#define TDM_TXFIFO_UNDERFLOW      TDM_TXFIFO_UNDERFLOW_MSK

//TDM_INT_RAW offsetaddress : 0x0024
//TDM_INT_RAW RegResetValue : 0x00000000
#define TDM_RXFIFO_DATA_READY_RAW_POS (0U)
#define TDM_RXFIFO_DATA_READY_RAW_MSK (0x1UL << TDM_RXFIFO_DATA_READY_RAW_POS) /*!< Raw status of the interrupt RXFIFO_DATA_READY*/
#define TDM_RXFIFO_DATA_READY_RAW     TDM_RXFIFO_DATA_READY_RAW_MSK
#define TDM_RXFIFO_OVERFLOW_RAW_POS   (1U)
#define TDM_RXFIFO_OVERFLOW_RAW_MSK   (0x1UL << TDM_RXFIFO_OVERFLOW_RAW_POS) /*!< Raw status of the interrupt RXFIFO_OVERFLOW*/
#define TDM_RXFIFO_OVERFLOW_RAW       TDM_RXFIFO_OVERFLOW_RAW_MSK
#define TDM_RXFIFO_UNDERFLOW_RAW_POS  (2U)
#define TDM_RXFIFO_UNDERFLOW_RAW_MSK  (0x1UL << TDM_RXFIFO_UNDERFLOW_RAW_POS) /*!< Raw status of the interrupt RXFIFO_UNDERFLOW*/
#define TDM_RXFIFO_UNDERFLOW_RAW      TDM_RXFIFO_UNDERFLOW_RAW_MSK
#define TDM_TXFIFO_DATA_READY_RAW_POS (4U)
#define TDM_TXFIFO_DATA_READY_RAW_MSK (0x1UL << TDM_TXFIFO_DATA_READY_RAW_POS) /*!< Raw status of the interrupt TXFIFO_DATA_READY*/
#define TDM_TXFIFO_DATA_READY_RAW     TDM_TXFIFO_DATA_READY_RAW_MSK
#define TDM_TXFIFO_OVERFLOW_RAW_POS   (5U)
#define TDM_TXFIFO_OVERFLOW_RAW_MSK   (0x1UL << TDM_TXFIFO_OVERFLOW_RAW_POS) /*!< Raw status of the interrupt TXFIFO_OVERFLOW*/
#define TDM_TXFIFO_OVERFLOW_RAW       TDM_TXFIFO_OVERFLOW_RAW_MSK
#define TDM_TXFIFO_UNDERFLOW_RAW_POS  (6U)
#define TDM_TXFIFO_UNDERFLOW_RAW_MSK  (0x1UL << TDM_TXFIFO_UNDERFLOW_RAW_POS) /*!< Raw status of the interrupt TXFIFO_UNDERFLOW*/
#define TDM_TXFIFO_UNDERFLOW_RAW      TDM_TXFIFO_UNDERFLOW_RAW_MSK

//TDM_INT_EN offsetaddress : 0x002C
//TDM_INT_EN RegResetValue : 0x00000000
#define TDM_RXFIFO_DATA_READY_EN_POS (0U)
#define TDM_RXFIFO_DATA_READY_EN_MSK (0x1UL << TDM_RXFIFO_DATA_READY_EN_POS) /*!< Enable of the interrupt RXFIFO_DATA_READY*/
#define TDM_RXFIFO_DATA_READY_EN     TDM_RXFIFO_DATA_READY_EN_MSK
#define TDM_RXFIFO_OVERFLOW_EN_POS   (1U)
#define TDM_RXFIFO_OVERFLOW_EN_MSK   (0x1UL << TDM_RXFIFO_OVERFLOW_EN_POS) /*!< Enable of the interrupt RXFIFO_OVERFLOW*/
#define TDM_RXFIFO_OVERFLOW_EN       TDM_RXFIFO_OVERFLOW_EN_MSK
#define TDM_RXFIFO_UNDERFLOW_EN_POS  (2U)
#define TDM_RXFIFO_UNDERFLOW_EN_MSK  (0x1UL << TDM_RXFIFO_UNDERFLOW_EN_POS) /*!< Enable of the interrupt RXFIFO_UNDERFLOW*/
#define TDM_RXFIFO_UNDERFLOW_EN      TDM_RXFIFO_UNDERFLOW_EN_MSK
#define TDM_TXFIFO_DATA_READY_EN_POS (4U)
#define TDM_TXFIFO_DATA_READY_EN_MSK (0x1UL << TDM_TXFIFO_DATA_READY_EN_POS) /*!< Enable of the interrupt TXFIFO_DATA_READY*/
#define TDM_TXFIFO_DATA_READY_EN     TDM_TXFIFO_DATA_READY_EN_MSK
#define TDM_TXFIFO_OVERFLOW_EN_POS   (5U)
#define TDM_TXFIFO_OVERFLOW_EN_MSK   (0x1UL << TDM_TXFIFO_OVERFLOW_EN_POS) /*!< Enable of the interrupt TXFIFO_OVERFLOW*/
#define TDM_TXFIFO_OVERFLOW_EN       TDM_TXFIFO_OVERFLOW_EN_MSK
#define TDM_TXFIFO_UNDERFLOW_EN_POS  (6U)
#define TDM_TXFIFO_UNDERFLOW_EN_MSK  (0x1UL << TDM_TXFIFO_UNDERFLOW_EN_POS) /*!< Enable of the interrupt TXFIFO_UNDERFLOW*/
#define TDM_TXFIFO_UNDERFLOW_EN      TDM_TXFIFO_UNDERFLOW_EN_MSK

typedef struct {
    volatile uint32_t TDM_TRANS_EN;    //offsetaddress : 0x0000
    volatile uint32_t TDM_CONFIG;      //offsetaddress : 0x0004
    volatile uint32_t TDM_CLOCK_GEN;   //offsetaddress : 0x0008
    volatile uint32_t TDM_RXFIFO_DATA; //offsetaddress : 0x000C
    volatile uint32_t TDM_TXFIFO_DATA; //offsetaddress : 0x0010
    volatile uint32_t TDM_FIFO_STATUS; //offsetaddress : 0x0014
    volatile uint32_t TDM_DMA_CONFIG;  //offsetaddress : 0x0018
    volatile uint32_t rev_0[(0x0020 - 0x0018) / 4 - 1];
    volatile uint32_t TDM_INT;     //offsetaddress : 0x0020
    volatile uint32_t TDM_INT_RAW; //offsetaddress : 0x0024
    volatile uint32_t rev_1[(0x002C - 0x0024) / 4 - 1];
    volatile uint32_t TDM_INT_EN; //offsetaddress : 0x002C
} tdm_reg_t;

#ifdef __cplusplus
}
#endif

#endif

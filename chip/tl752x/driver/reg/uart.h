/*******************************************************************************************************
 *
 * @file    uart.h
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
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//RBR offsetaddress : 0x0
#define UART_RBR_POS                   (255U)
#define UART_RBR_MSK                   (0x1UL << UART_RBR_POS)/*!< Receive Buffer Register. This register contains the data byte received on the serial input port (sin) in UART mode or the serial infrared input (sir_in) in infrared mode. The data in this register is valid only if the Data Ready (DR) bit in the Line status Register (LSR) is set. If in non-FIFO mode (FIFO_MODE == NONE) or FIFOs are disabled (FCR[0] set to 0), the data in the RBR must be read before the next data arrives, otherwise it will be overwritten, resulting in an over-run error. If in FIFO mode (FIFO_MODE != NONE) and FIFOs are enabled (FCR[0] set to 1), this register accesses the head of the receive FIFO. If the receive FIFO is full and this register is not read before the next data character arrives, then the data already in the FIFO will be preserved but any incoming data will be lost and an over-run error occurs. Note: When UART_9BIT_DATA_EN=0, this field width is 8. When UART_9BIT_DATA_EN=1, this field width is 9. Reset Value: 0x0 Exists: Always Range Variable[x]: "(UART_9BIT_DATA_EN==1) ? \"9\" : \"8\"" - 1*/
#define UART_RBR                       UART_RBR_MSK
#define UART_RSVD_RBR_POS              (255U)
#define UART_RSVD_RBR_MSK              (0x1UL << UART_RSVD_RBR_POS)/*!< RBR 31to9or8 Reserved bits and read as zero (0). Exists: Always Range Variable[x]: "(UART_9BIT_DATA_EN==1) ? \"23\" : \"24\"" + "(UART_9BIT_DATA_EN==1) ? \"0x9\" : \"0x8\"" - 1 Range Variable[y]: "(UART_9BIT_DATA_EN==1) ? \"0x9\" : \"0x8\""*/
#define UART_RSVD_RBR                  UART_RSVD_RBR_MSK


//DLL offsetaddress : 0x0
#define UART_DLL_POS                   (0U)
#define UART_DLL_MSK                   (0xffUL << UART_DLL_POS)/*!< Divisor Latch (Low). This register makes up the lower 8-bits of a 16-bit, read/ write, Divisor Latch register that contains the baud rate divisor for the UART. The output baud rate is equal to the serial clock (pclk if one clock design, sclk if two clock design (CLOCK_MODE == Enabled)) frequency divided by sixteen times the value of the baud rate divisor, as follows: baud rate = (serial clock freq) / (16 * divisor). Note that with the Divisor Latch Registers (DLL and DLH) set to zero, the baud clock is disabled and no serial communications will occur. Also, once the DLL is set, at least 8 clock cycles of the slowest DW_apb_uart clock should be allowed to pass before transmitting or receiving data. Reset Value: 0x0 Exists: Always*/
#define UART_DLL                       UART_DLL_MSK
#define UART_RSVD_DLL_31TO8_POS        (8U)
#define UART_RSVD_DLL_31TO8_MSK        (0xffffffUL << UART_RSVD_DLL_31TO8_POS)/*!< DLL 31to8 Reserved bits and read as zero (0). Exists: Always*/
#define UART_RSVD_DLL_31TO8            UART_RSVD_DLL_31TO8_MSK


//THR offsetaddress : 0x0
#define UART_THR_POS                   (255U)
#define UART_THR_MSK                   (0x1UL << UART_THR_POS)/*!< Transmit Holding Register. This register contains data to be transmitted on the serial output port (sout) in UART mode or the serial infrared output (sir_out_n) in infrared mode. Data should only be written to the THR when the THR Empty (THRE) bit (LSR[5]) is set. If in non-FIFO mode or FIFO's are disabled (FCR[0] set to zero) and THRE is set, writing a single character to the THR clears the THRE. Any additional writes to the THR before the THRE is set again causes the THR data to be overwritten. If in FIFO mode and FIFO's are enabled (FCR[0] set to one) and THRE is set, x number of characters of data may be written to the THR before the FIFO is full. The number x (default=16) is determined by the value of FIFO Depth that is set during configuration. Any attempt to write data when the FIFO is full results in the write data being lost. Note: When UART_9BIT_DATA_EN=0, this field width is 8. When UART_9BIT_DATA_EN=1, this field width is 9. The 9th bit is applicable only when LCR_EXT[3]=1. Reset Value: 0x0 Exists: Always Range Variable[x]: "(UART_9BIT_DATA_EN==1) ? \"9\" : \"8\"" - 1*/
#define UART_THR                       UART_THR_MSK
#define UART_RSVD_THR_POS              (255U)
#define UART_RSVD_THR_MSK              (0x1UL << UART_RSVD_THR_POS)/*!< THR 31to9or8 Reserved bits and read as zero (0). Exists: Always Range Variable[x]: "(UART_9BIT_DATA_EN==1) ? \"23\" : \"24\"" + "(UART_9BIT_DATA_EN==1) ? \"0x9\" : \"0x8\"" - 1 Range Variable[y]: "(UART_9BIT_DATA_EN==1) ? \"0x9\" : \"0x8\""*/
#define UART_RSVD_THR                  UART_RSVD_THR_MSK


//DLH offsetaddress : 0x4
#define UART_DLH_POS                   (0U)
#define UART_DLH_MSK                   (0xffUL << UART_DLH_POS)/*!< Upper 8-bits of a 16-bit, read/write, Divisor Latch register that contains the baud rate divisor for the UART. The output baud rate is equal to the serial clock (pclk if one clock design, sclk if two clock design (CLOCK_MODE == Enabled)) frequency divided by sixteen times the value of the baud rate divisor, as follows: baud rate = (serial clock freq) / (16 * divisor). Note that with the Divisor Latch Registers (DLL and DLH) set to zero, the baud clock is disabled and no serial communications will occur. Also, once the DLH is set, at least 8 clock cycles of the slowest DW_apb_uart clock should be allowed to pass before transmitting or receiving data. Exists: Always*/
#define UART_DLH                       UART_DLH_MSK
#define UART_RSVD_DLH_POS              (8U)
#define UART_RSVD_DLH_MSK              (0xffffffUL << UART_RSVD_DLH_POS)/*!< DLH 31to8 Reserved bits and read as zero (0). Exists: Always*/
#define UART_RSVD_DLH                  UART_RSVD_DLH_MSK


//IER offsetaddress : 0x4
#define UART_ERBFI_POS                 (0U)
#define UART_ERBFI_MSK                 (0x1UL << UART_ERBFI_POS)/*!< Enable Received Data Available Interrupt. This is used to enable/disable the generation of Received Data Available Interrupt and the Character Timeout Interrupt (if in FIFO mode and FIFO's enabled). These are the second highest priority interrupts. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disable Receive data Interrupt ■ 0x1 (ENABLED): Enable Receive data Interrupt Exists: Always*/
#define UART_ERBFI                     UART_ERBFI_MSK
#define UART_ETBEI_POS                 (1U)
#define UART_ETBEI_MSK                 (0x1UL << UART_ETBEI_POS)/*!< Enable Transmit Holding Register Empty Interrupt. This is used to enable/disable the generation of Transmitter Holding Register Empty Interrupt. This is the third highest priority interrupt. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disable Transmit empty interrupt ■ 0x1 (ENABLED): Enable Transmit empty interrupt Exists: Always*/
#define UART_ETBEI                     UART_ETBEI_MSK
#define UART_ELSI_POS                  (2U)
#define UART_ELSI_MSK                  (0x1UL << UART_ELSI_POS)/*!< Enable Receiver Line Status Interrupt. This is used to enable/disable the generation of Receiver Line Status Interrupt. This is the highest priority interrupt. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disable Receiver Line Status Interrupt ■ 0x1 (ENABLED): Enable Receiver Line Status Interrupt Exists: Always*/
#define UART_ELSI                      UART_ELSI_MSK
#define UART_EDSSI_POS                 (3U)
#define UART_EDSSI_MSK                 (0x1UL << UART_EDSSI_POS)/*!< Enable Modem Status Interrupt. This is used to enable/ disable the generation of Modem Status Interrupt. This is the fourth highest priority interrupt. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disable Modem Status Interrupt ■ 0x1 (ENABLED): Enable Modem Status Interrupt Exists: Always*/
#define UART_EDSSI                     UART_EDSSI_MSK
#define UART_ELCOLR_POS                (4U)
#define UART_ELCOLR_MSK                (0x1UL << UART_ELCOLR_POS)/*!< Interrupt Enable Register: ELCOLR, this bit controls the method for clearing the status in the LSR register. This is applicable only for Overrun Error, Parity Error, Framing Error, and Break Interrupt status bits. 0 = LSR status bits are cleared either on reading Rx FIFO (RBR Read) or On reading LSR register. 1 = LSR status bits are cleared only on reading LSR register. Writeable only when LSR_STATUS_CLEAR == Enabled, always readable. Values: ■ 0x0 (DISABLED): Disable ALC ■ 0x1 (ENABLED): Enable ALC Exists: Always Memory Access: "(LSR_STATUS_CLEAR==1) ? \"read- write\" : \"read-only\""*/
#define UART_ELCOLR                    UART_ELCOLR_MSK
#define UART_RSVD_IER_6TO5_POS         (5U)
#define UART_RSVD_IER_6TO5_MSK         (0x3UL << UART_RSVD_IER_6TO5_POS)/*!< IER 6to5 Reserved bits read as zero (0). Exists: Always*/
#define UART_RSVD_IER_6TO5             UART_RSVD_IER_6TO5_MSK
#define UART_PTIME_POS                 (7U)
#define UART_PTIME_MSK                 (0x1UL << UART_PTIME_POS)/*!< Programmable THRE Interrupt Mode Enable. Writeable only when THRE_MODE_USER == Enabled, always readable. This is used to enable/disable the generation of THRE Interrupt. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Disable Programmable THRE Interrupt Mode ■ 0x1 (ENABLED): Enable Programmable THRE Interrupt Mode Exists: Always Memory Access: "(THRE_MODE_USER==1 && FIFO_MODE!=0) ? \"read-write\" : \"read-only\""*/
#define UART_PTIME                     UART_PTIME_MSK
#define UART_RSVD_IER_31TO8_POS        (8U)
#define UART_RSVD_IER_31TO8_MSK        (0xffffffUL << UART_RSVD_IER_31TO8_POS)/*!< IER 31to8 Reserved bits and read as zero (0). Exists: Always*/
#define UART_RSVD_IER_31TO8            UART_RSVD_IER_31TO8_MSK


//FCR offsetaddress : 0x8
#define UART_FIFOE_POS                 (0U)
#define UART_FIFOE_MSK                 (0x1UL << UART_FIFOE_POS)/*!< FIFO Enable (or FIFOE). This enables/disables the transmit (XMIT) and receive (RCVR) FIFOs. Whenever the value of this bit is changed both the XMIT and RCVR controller portion of FIFOs is reset. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): FIFO disabled ■ 0x1 (ENABLED): FIFO enabled Exists: Always*/
#define UART_FIFOE                     UART_FIFOE_MSK
#define UART_RFIFOR_POS                (1U)
#define UART_RFIFOR_MSK                (0x1UL << UART_RFIFOR_POS)/*!< RCVR FIFO Reset (or RFIFOR). This resets the control portion of the receive FIFO and treats the FIFO as empty. This will also de-assert the DMA RX request and single signals when additional DMA handshaking signals are selected (DMA_EXTRA == YES). Note that this bit is 'self- clearing' and it is not necessary to clear this bit. Reset Value: 0x0 Values: ■ 0x1 (RESET): Receive FIFO reset Exists: Always*/
#define UART_RFIFOR                    UART_RFIFOR_MSK
#define UART_XFIFOR_POS                (2U)
#define UART_XFIFOR_MSK                (0x1UL << UART_XFIFOR_POS)/*!< XMIT FIFO Reset (or XFIFOR). This resets the control portion of the transmit FIFO and treats the FIFO as empty. This will also de-assert the DMA TX request and single signals when additional DMA handshaking signals are selected (DMA_EXTRA == YES). Note that this bit is 'self- clearing' and it is not necessary to clear this bit. Reset Value: 0x0 Values: ■ 0x1 (RESET): Transmit FIFO reset Exists: Always*/
#define UART_XFIFOR                    UART_XFIFOR_MSK
#define UART_DMAM_POS                  (3U)
#define UART_DMAM_MSK                  (0x1UL << UART_DMAM_POS)/*!< DMA Mode (or DMAM). This determines the DMA signalling mode used for the dma_tx_req_n and dma_rx_req_n output signals when additional DMA handshaking signals are not selected (DMA_EXTRA == NO). For details on DMA support, refer to 'DMA Support' section of data book. Reset Value: 0x0 Values: ■ 0x0 (MODE0): Mode 0 ■ 0x1 (MODE1): Mode 1 Exists: Always*/
#define UART_DMAM                      UART_DMAM_MSK
#define UART_TET_POS                   (4U)
#define UART_TET_MSK                   (0x3UL << UART_TET_POS)/*!< TX Empty Trigger (or TET). Writes will have no effect when THRE_MODE_USER == Disabled. This is used to select the empty threshold level at which the THRE Interrupts will be generated when the mode is active. It also determines when the dma_tx_req_n signal will be asserted when in certain modes of operation. For details on DMA support, refer to 'DMA Support' section of data book. Reset Value: 0x0 Values: ■ 0x0 (FIFO_EMPTY): FIFO Empty ■ 0x1 (FIFO_CHAR_2): 2 characters in FIFO ■ 0x2 (FIFO_QUARTER_FULL): FIFO 1/4 full ■ 0x3 (FIFO_HALF_FULL): FIFO 1/2 full Exists: Always Memory Access: "(THRE_MODE_USER==1) ? \"write- only\" : \"read-only\""*/
#define UART_TET                       UART_TET_MSK
#define UART_RT_POS                    (6U)
#define UART_RT_MSK                    (0x3UL << UART_RT_POS)/*!< RCVR Trigger (or RT). This is used to select the trigger level in the receiver FIFO at which the Received Data Available Interrupt will be generated. In auto flow control mode, it is used to determine when the rts_n signal will be de-asserted only when RTC_FCT is disabled. It also determines when the dma_rx_req_n signal will be asserted when in certain modes of operation. For details on DMA support, refer to 'DMA Support' section of data book. Reset Value: 0x0 Values: ■ 0x0 (FIFO_CHAR_1): 1 character in FIFO ■ 0x1 (FIFO_QUARTER_FULL): FIFO 1/4 full ■ 0x2 (FIFO_HALF_FULL): FIFO 1/2 full ■ 0x3 (FIFO_FULL_2): FIFO 2 less than full Exists: Always*/
#define UART_RT                        UART_RT_MSK
#define UART_RSVD_FCR_31TO8_POS        (8U)
#define UART_RSVD_FCR_31TO8_MSK        (0xffffffUL << UART_RSVD_FCR_31TO8_POS)/*!< FCR 31to8 Reserved bits and read as 0. Exists: Always*/
#define UART_RSVD_FCR_31TO8            UART_RSVD_FCR_31TO8_MSK


//IIR offsetaddress : 0x8
#define UART_IID_POS                   (0U)
#define UART_IID_MSK                   (0xfUL << UART_IID_POS)/*!< Interrupt ID (or IID). This indicates the highest priority pending interrupt which can be one of the following types specified in Values. For information on several levels into which the interrupt priorities are split into, see the 'Interrupts' section in the DW_apb_uart Databook. Note: an interrupt of type 0111 (busy detect) will never get indicated if UART_16550_COMPATIBLE == YES in coreConsultant. Reset Value: 0x1 Bit 3 indicates an interrupt can only occur when the FIFOs are enabled and used to distinguish a Character Timeout condition interrupt. Values: ■ 0x0 (MODEM_STATUS): modem status ■ 0x1 (NO_INTERRUPT_PENDING): no interrupt pending ■ 0x2 (THR_EMPTY): THR empty ■ 0x4 (RECEIVED_DATA_AVAILABLE): received data available ■ 0x6 (RECEIVER_LINE_STATUS): receiver line status ■ 0x7 (BUSY_DETECT): busy detect ■ 0xc (CHARACTER_TIMEOUT): character timeout Exists: Always*/
#define UART_IID                       UART_IID_MSK
#define UART_RSVD_IIR_5TO4_POS         (4U)
#define UART_RSVD_IIR_5TO4_MSK         (0x3UL << UART_RSVD_IIR_5TO4_POS)/*!< IIR 5to4 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_IIR_5TO4             UART_RSVD_IIR_5TO4_MSK
#define UART_FIFOSE_POS                (6U)
#define UART_FIFOSE_MSK                (0x3UL << UART_FIFOSE_POS)/*!< FIFOs Enabled (or FIFOSE). This is used to indicate whether the FIFOs are enabled or disabled. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): FIFOs are disabled ■ 0x3 (ENABLED): FIFOs are enabled Exists: Always*/
#define UART_FIFOSE                    UART_FIFOSE_MSK
#define UART_RSVD_IIR_31TO8_POS        (8U)
#define UART_RSVD_IIR_31TO8_MSK        (0xffffffUL << UART_RSVD_IIR_31TO8_POS)/*!< IIR 31to8 Reserved bits and read as 0. Exists: Always*/
#define UART_RSVD_IIR_31TO8            UART_RSVD_IIR_31TO8_MSK


//LCR offsetaddress : 0xc
#define UART_DLS_POS                   (0U)
#define UART_DLS_MSK                   (0x3UL << UART_DLS_POS)/*!< Data Length Select (or CLS as used in legacy). If UART_16550_COMPATIBLE == NO then, writeable only when UART is not busy (USR[0] is zero), otherwise always writable and always readable. When DLS_E in LCR_EXT is set to 0, this register is used to select the number of data bits per character that the peripheral will transmit and receive. Reset Value: 0x0 Values: ■ 0x0 (CHAR_5BITS): 5 data bits per character ■ 0x1 (CHAR_6BITS): 6 data bits per character ■ 0x2 (CHAR_7BITS): 7 data bits per character ■ 0x3 (CHAR_8BITS): 8 data bits per character Exists: Always*/
#define UART_DLS                       UART_DLS_MSK
#define UART_STOP_POS                  (2U)
#define UART_STOP_MSK                  (0x1UL << UART_STOP_POS)/*!< Number of stop bits. If UART_16550_COMPATIBLE == NO then, writeable only when UART is not busy (USR[0] is zero), otherwise always writable and always readable. This is used to select the number of stop bits per character that the peripheral will transmit and receive. If set to zero, one stop bit is transmitted in the serial data. If set to one and the data bits are set to 5 (LCR[1:0] set to zero) one and a half stop bits is transmitted. Otherwise, two stop bits are transmitted. Note that regardless of the number of stop bits selected the receiver will only check the first stop bit. Note: NOTE: The STOP bit duration implemented by DW_apb_uart may appear longer due to idle time inserted between characters for some configurations and baud clock divisor values in the transmit direction; for details on idle time between transmitted transfers, refer to 'Back-to-Back Character Stream Transmission' section in data book. Reset Value: 0x0 Values: ■ 0x0 (STOP_1BIT): 1 stop bit ■ 0x1 (STOP_1_5BIT_OR_2BIT): 1.5 stop bits when DLS (LCR[1:0]) is zero, else 2 stop bit Exists: Always*/
#define UART_STOP                      UART_STOP_MSK
#define UART_PEN_POS                   (3U)
#define UART_PEN_MSK                   (0x1UL << UART_PEN_POS)/*!< Parity Enable . If UART_16550_COMPATIBLE == NO then, writeable only when UART is not busy (USR[0] is zero), otherwise always writable and always readable. This bit is used to enable and disable parity generation and detection in transmitted and received serial character respectively. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): disable parity ■ 0x1 (ENABLED): enable parity Exists: Always*/
#define UART_PEN                       UART_PEN_MSK
#define UART_EPS_POS                   (4U)
#define UART_EPS_MSK                   (0x1UL << UART_EPS_POS)/*!< Even Parity Select. If UART_16550_COMPATIBLE == NO then, writeable only when UART is not busy (USR[0] is zero), otherwise always writable and always readable. This is used to select between even and odd parity, when parity is enabled (PEN set to one). If set to one, an even number of logic '1's is transmitted or checked. If set to zero, an odd number of logic '1's is transmitted or checked. Reset Value: 0x0 Values: ■ 0x0 (ODD_PARITY): an odd parity is transmitted or checked ■ 0x1 (EVEN_PARITY): an even parity is transmitted or checked Exists: Always*/
#define UART_EPS                       UART_EPS_MSK
#define UART_SP_POS                    (5U)
#define UART_SP_MSK                    (0x1UL << UART_SP_POS)/*!< Stick Parity. If UART_16550_COMPATIBLE = NO, then writeable only when UART is not busy (USR[0] is 0); otherwise always writable and always readable. This bit is used to force parity value. When PEN, EPS and Stick Parity are set to 1, the parity bit is transmitted and checked as logic 0. If PEN and Stick Parity are set to 1 and EPS is a logic 0, then parity bit is transmitted and checked as a logic 1. If this bit is set to 0, Stick Parity is disabled. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Stick parity disabled ■ 0x1 (ENABLED): Stick parity enabled Exists: Always*/
#define UART_SP                        UART_SP_MSK
#define UART_BC_POS                    (6U)
#define UART_BC_MSK                    (0x1UL << UART_BC_POS)/*!< Break Control Bit. This is used to cause a break condition to be transmitted to the receiving device. If set to one the serial output is forced to the spacing (logic 0) state. When not in Loopback Mode, as determined by MCR[4], the sout line is forced low until the Break bit is cleared. If SIR_MODE == Enabled and active (MCR[6] set to one) the sir_out_n line is continuously pulsed. When in Loopback Mode, the break condition is internally looped back to the receiver and the sir_out_n line is forced low. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Serial output is released for data transmission ■ 0x1 (ENABLED): Serial output is forced to spacing state Exists: Always*/
#define UART_BC                        UART_BC_MSK
#define UART_DLAB_POS                  (7U)
#define UART_DLAB_MSK                  (0x1UL << UART_DLAB_POS)/*!< Divisor Latch Access Bit. If UART_16550_COMPATIBLE == NO then, writeable only when UART is not busy (USR[0] is zero), otherwise always writable and always readable. This bit is used to enable reading and writing of the Divisor Latch register (DLL and DLH/LPDLL and LPDLH) to set the baud rate of the UART. This bit must be cleared after initial baud rate setup in order to access other registers. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Divisor Latch register is writable only when UART Not BUSY ■ 0x1 (ENABLED): Divisor Latch register is always readable and writable Exists: Always*/
#define UART_DLAB                      UART_DLAB_MSK
#define UART_RSVD_LCR_31TO8_POS        (8U)
#define UART_RSVD_LCR_31TO8_MSK        (0xffffffUL << UART_RSVD_LCR_31TO8_POS)/*!< LCR 31to8 Reserved bits and read as 0. Exists: Always*/
#define UART_RSVD_LCR_31TO8            UART_RSVD_LCR_31TO8_MSK


//MCR offsetaddress : 0x10
#define UART_DTR_POS                   (0U)
#define UART_DTR_MSK                   (0x1UL << UART_DTR_POS)/*!< Data Terminal Ready. This is used to directly control the Data Terminal Ready (dtr_n) output. The value written to this location is inverted and driven out on dtr_n. The Data Terminal Ready output is used to inform the modem or data set that the UART is ready to establish communications. Note that in Loopback mode (MCR[4] set to one), the dtr_n output is held inactive high while the value of this location is internally looped back to an input. Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): dtr_n de-asserted (logic1) ■ 0x1 (ACTIVE): dtr_n asserted (logic 0) Exists: Always*/
#define UART_DTR                       UART_DTR_MSK
#define UART_RTS_POS                   (1U)
#define UART_RTS_MSK                   (0x1UL << UART_RTS_POS)/*!< Request to Send. This is used to directly control the Request to Send (rts_n) output. The Request To Send (rts_n) output is used to inform the modem or data set that the UART is ready to exchange data. When Auto RTS Flow Control is not enabled (MCR[5] set to zero), the rts_n signal is set low by programming MCR[1] (RTS) to a high. In Auto Flow Control, AFCE_MODE == Enabled and active (MCR[5] set to one) and FIFO's enable (FCR[0] set to one), the rts_n output is controlled in the same way, but is also gated with the receiver FIFO threshold trigger (rts_n is inactive high when above the threshold). The rts_n signal will be de-asserted when MCR[1] is set low. Note that in Loopback mode (MCR[4] set to one), the rts_n output is held inactive high while the value of this location is internally looped back to an input. Reset Value: 0x0 Values: ■ 0x0 (INACTIVE): Request to Send rts_n de-asserted (logic 1) ■ 0x1 (ACTIVE): Request to Send rts_n asserted (logic 0) Exists: Always*/
#define UART_RTS                       UART_RTS_MSK
#define UART_OUT1_POS                  (2U)
#define UART_OUT1_MSK                  (0x1UL << UART_OUT1_POS)/*!< OUT1 . This is used to directly control the user-designated Output1 (out1_n) output. The value written to this location is inverted and driven out on out1_n. Note that in Loopback mode (MCR[4] set to one), the out1_n output is held inactive high while the value of this location is internally looped back to an input. Reset Value: 0x0 Values: ■ 0x0 (OUT1_0): out1_n de-asserted (logic 1) ■ 0x1 (OUT1_1): out1_n asserted (logic 0) Exists: Always*/
#define UART_OUT1                      UART_OUT1_MSK
#define UART_OUT2_POS                  (3U)
#define UART_OUT2_MSK                  (0x1UL << UART_OUT2_POS)/*!< OUT2 . This is used to directly control the user-designated Output2 (out2_n) output. The value written to this location is inverted and driven out on out2_n. Note that in Loopback mode (MCR[4] set to one), the out2_n output is held inactive high while the value of this location is internally looped back to an input. Reset Value: 0x0 Values: ■ 0x0 (OUT2_0): out2_n de-asserted (logic 1) ■ 0x1 (OUT2_1): out2_n asserted (logic 0) Exists: Always*/
#define UART_OUT2                      UART_OUT2_MSK
#define UART_LOOPBACK_POS              (4U)
#define UART_LOOPBACK_MSK              (0x1UL << UART_LOOPBACK_POS)/*!< LoopBack Bit . This is used to put the UART into a diagnostic mode for test purposes. If operating in UART mode (SIR_MODE != Enabled OR NOT active, MCR[6] set to zero), data on the sout line is held high, while serial data output is looped back to the sin line, internally. In this mode all the interrupts are fully functional. Also, in loopback mode, the modem control inputs (dsr_n, cts_n, ri_n, dcd_n) are disconnected and the modem control outputs (dtr_n, rts_n, out1_n, out2_n) are looped back to the inputs, internally. If operating in infrared mode (SIR_MODE == Enabled AND active, MCR[6] set to one), data on the sir_out_n line is held low, while serial data output is inverted and looped back to the sir_in line. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Loopback mode disabled ■ 0x1 (ENABLED): Loopback mode enabled Exists: Always*/
#define UART_LOOPBACK                  UART_LOOPBACK_MSK
#define UART_AFCE_POS                  (5U)
#define UART_AFCE_MSK                  (0x1UL << UART_AFCE_POS)/*!< Auto Flow Control Enable . Writeable only when AFCE_MODE == Enabled, always readable. When FIFOs are enabled and the Auto Flow Control Enable (AFCE) bit is set, Auto Flow Control features are enabled as described in section 'Auto Flow Control' in data book. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Auto Flow Control Mode disabled ■ 0x1 (ENABLED): Auto Flow Control Mode enabled Exists: Always Memory Access: "(AFCE_MODE==1) ? \"read-write\" : \"read-only\""*/
#define UART_AFCE                      UART_AFCE_MSK
#define UART_SIRE_POS                  (6U)
#define UART_SIRE_MSK                  (0x1UL << UART_SIRE_POS)/*!< SIR Mode Enable . Writeable only when SIR_MODE == Enabled, always readable. This is used to enable/ disable the IrDA SIR Mode features as described in section 'IrDA 1.0 SIR Protocol' in the databook. Note: To enable SIR mode, write the appropriate value to the MCR register before writing to the LCR register. For details of the recommended programming sequence, refer to 'Programing Examples' section of data book. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): IrDA SIR Mode disabled ■ 0x1 (ENABLED): IrDA SIR Mode enabled Exists: Always Memory Access: "(SIR_MODE==1) ? \"read-write\" : \"read- only\""*/
#define UART_SIRE                      UART_SIRE_MSK
#define UART_RSVD_MCR_31TO7_POS        (7U)
#define UART_RSVD_MCR_31TO7_MSK        (0x1ffffffUL << UART_RSVD_MCR_31TO7_POS)/*!< MCR 31to7 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_MCR_31TO7            UART_RSVD_MCR_31TO7_MSK


//LSR offsetaddress : 0x14
#define UART_DR_POS                    (0U)
#define UART_DR_MSK                    (0x1UL << UART_DR_POS)/*!< Data Ready bit. This is used to indicate that the receiver contains at least one character in the RBR or the receiver FIFO. This bit is cleared when the RBR is read in the non-FIFO mode, or when the receiver FIFO is empty, in the FIFO mode. Reset Value: 0x0 Values: ■ 0x0 (NOT_READY): data not ready ■ 0x1 (READY): data ready Exists: Always*/
#define UART_DR                        UART_DR_MSK
#define UART_OE_POS                    (1U)
#define UART_OE_MSK                    (0x1UL << UART_OE_POS)/*!< Overrun error bit. This is used to indicate the occurrence of an overrun error. This occurs if a new data character was received before the previous data was read. In the non-FIFO mode, the OE bit is set when a new character arrives in the receiver before the previous character was read from the RBR. When this happens, the data in the RBR is overwritten. In the FIFO mode, an overrun error occurs when the FIFO is full and a new character arrives at the receiver. The data in the FIFO is retained and the data in the receive shift register is lost. Reading the LSR clears the OE bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the OE bit (if LSR_STATUS_CLEAR==0). Reset Value: 0x0 Values: ■ 0x0 (NO_OVER_RUN_ERROR): no overrun error ■ 0x1 (OVER_RUN_ERROR): overrun error Exists: Always*/
#define UART_OE                        UART_OE_MSK
#define UART_PE_POS                    (2U)
#define UART_PE_MSK                    (0x1UL << UART_PE_POS)/*!< Parity Error bit. This is used to indicate the occurrence of a parity error in the receiver if the Parity Enable (PEN) bit (LCR[3]) is set. In the FIFO mode, since the parity error is associated with a character received, it is revealed when the character with the parity error arrives at the top of the FIFO. It should be noted that the Parity Error (PE) bit (LSR[2]) will be set if a break interrupt has occurred, as indicated by Break Interrupt (BI) bit (LSR[4]). In this situation, the Parity Error bit is set if parity generation and detection is enabled (LCR[3]=1) and the parity is set to odd (LCR[4]=0). Reading the LSR clears the PE bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the PE bit (if LSR_STATUS_CLEAR==0). Reset Value: 0x0 Values: ■ 0x0 (NO_PARITY_ERROR): no parity error ■ 0x1 (PARITY_ERROR): parity error Exists: Always*/
#define UART_PE                        UART_PE_MSK
#define UART_FE_POS                    (3U)
#define UART_FE_MSK                    (0x1UL << UART_FE_POS)/*!< Framing Error bit. This is used to indicate the occurrence of a framing error in the receiver. A framing error occurs when the receiver does not detect a valid STOP bit in the received data. In the FIFO mode, since the framing error is associated with a character received, it is revealed when the character with the framing error is at the top of the FIFO. When a framing error occurs the UART will try resynchronize. It does this by assuming that the error was due to the start bit of the next character and then continues receiving the other bit i.e. data, and/or parity and stop. It should be noted that the Framing Error (FE) bit (LSR[3]) will be set if a break interrupt has occurred, as indicated by Break Interrupt (BI) bit (LSR[4]). This happens because the break character implicitly generates a framing error by holding the sin input to logic 0 for longer than the duration of a character. Reading the LSR clears the FE bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the FE bit (if LSR_STATUS_CLEAR==0). Reset Value: 0x0 Values: ■ 0x0 (NO_FRAMING_ERROR): no framing error ■ 0x1 (FRAMING_ERROR): framing error Exists: Always*/
#define UART_FE                        UART_FE_MSK
#define UART_BI_POS                    (4U)
#define UART_BI_MSK                    (0x1UL << UART_BI_POS)/*!< Break Interrupt bit. This is used to indicate the detection of a break sequence on the serial input data. If in UART mode it is set whenever the serial input, sin, is held in a logic '0' state for longer than the sum of start time + data bits + parity + stop bits. If in infrared mode it is set whenever the serial input, sir_in, is continuously pulsed to logic '0' for longer than the sum of start time + data bits + parity + stop bits. A break condition on serial input causes one and only one character, consisting of all zeros, to be received by the UART. In the FIFO mode, the character associated with the break condition is carried through the FIFO and is revealed when the character is at the top of the FIFO. Reading the LSR clears the BI bit (if LSR_STATUS_CLEAR==1) Or Reading the LSR or RBR clears the BI bit (if LSR_STATUS_CLEAR==0). In the non-FIFO mode, the BI indication occurs immediately and persists until the LSR is read. Note: If a FIFO is full when a break condition is received, a FIFO overrun occurs. The break condition and all the information associated with it-parity and framing errors-is discarded; any information that a break character was received is lost. Reset Value: 0x0 Values: ■ 0x0 (NO_BREAK): No break sequence detected ■ 0x1 (BREAK): Break sequence detected Exists: Always*/
#define UART_BI                        UART_BI_MSK
#define UART_THRE_POS                  (5U)
#define UART_THRE_MSK                  (0x1UL << UART_THRE_POS)/*!< Transmit Holding Register Empty bit. If THRE_MODE_USER = Disabled or THRE mode is disabled (IER[7] set to zero) and regardless of FIFO's being implemented/enabled or not, this bit indicates that the THR or TX FIFO is empty. This bit is set whenever data is transferred from the THR or TX FIFO to the transmitter shift register and no new data has been written to the THR or TX FIFO. This also causes a THRE Interrupt to occur, if the THRE Interrupt is enabled. If THRE_MODE_USER == Enabled AND FIFO_MODE != NONE and both modes are active (IER[7] set to one and FCR[0] set to one respectively), the functionality is switched to indicate the transmitter FIFO is full, and no longer controls THRE interrupts, which are then controlled by the FCR[5:4] threshold setting. Programmable THRE interrupt mode operation is described in detail in section 'Programmable THRE Interrupt' in data book. Reset Value: 0x1 Values: ■ 0x0 (DISABLED): THRE interrupt control is disabled ■ 0x1 (ENABLED): THRE interrupt control is enabled Exists: Always*/
#define UART_THRE                      UART_THRE_MSK
#define UART_TEMT_POS                  (6U)
#define UART_TEMT_MSK                  (0x1UL << UART_TEMT_POS)/*!< Transmitter Empty bit. If in FIFO mode (FIFO_MODE != NONE) and FIFO's enabled (FCR[0] set to one), this bit is set whenever the Transmitter Shift Register and the FIFO are both empty. If in the non-FIFO mode or FIFO's are disabled, this bit is set whenever the Transmitter Holding Register and the Transmitter Shift Register are both empty. Reset Value: 0x1 Values: ■ 0x0 (DISABLED): Transmitter not empty ■ 0x1 (ENABLED): Transmitter empty Exists: Always*/
#define UART_TEMT                      UART_TEMT_MSK
#define UART_RFE_POS                   (7U)
#define UART_RFE_MSK                   (0x1UL << UART_RFE_POS)/*!< Receiver FIFO Error bit. This bit is only relevant when FIFO_MODE != NONE AND FIFO's are enabled (FCR[0] set to one). This is used to indicate if there is at least one parity error, framing error, or break indication in the FIFO. This bit is cleared when the LSR is read and the character with the error is at the top of the receiver FIFO and there are no subsequent errors in the FIFO. Reset Value: 0x0 Values: ■ 0x0 (NO_RX_FIFO_ERROR): No error in RX FIFO ■ 0x1 (RX_FIFO_ERROR): Error in RX FIFO Exists: FIFO_MODE != 0*/
#define UART_RFE                       UART_RFE_MSK
#define UART_ADDR_RCVD_POS             (8U)
#define UART_ADDR_RCVD_MSK             (0x1UL << UART_ADDR_RCVD_POS)/*!< Address Received Bit. If 9Bit data mode (LCR_EXT[0]=1) is enabled, this bit is used to indicate the 9th bit of the receive data is set to 1. This bit can also be used to indicate whether the incoming character is address or data. ■ 1 = Indicates the character is address. ■ 0 = Indicates the character is data. In the FIFO mode, since the 9th bit is associated with a character received, it is revealed when the character with the 9th bit set to 1 is at the top of the FIFO. Reading the LSR clears the 9BIT. Note: User needs to ensure that interrupt gets cleared (reading LSR register) before the next address byte arrives. If there is a delay in clearing the interrupt, then Software will not be able to distinguish between multiple address related interrupt. Reset Value: 0x0 Exists: UART_9BIT_DATA_EN == 1*/
#define UART_ADDR_RCVD                 UART_ADDR_RCVD_MSK
#define UART_RSVD_LSR_31TO9_POS        (9U)
#define UART_RSVD_LSR_31TO9_MSK        (0x7fffffUL << UART_RSVD_LSR_31TO9_POS)/*!< LSR 31to9 Reserved bits read as zero. Exists: Always*/
#define UART_RSVD_LSR_31TO9            UART_RSVD_LSR_31TO9_MSK


//MSR offsetaddress : 0x18
#define UART_DCTS_POS                  (0U)
#define UART_DCTS_MSK                  (0x1UL << UART_DCTS_POS)/*!< Delta Clear to Send. This is used to indicate that the modem control line cts_n has changed since the last time the MSR was read. Reading the MSR clears the DCTS bit. In Loopback Mode (MCR[4] set to one), DCTS reflects changes on MCR[1] (RTS). Note, if the DCTS bit is not set and the cts_n signal is asserted (low) and a reset occurs (software or otherwise), then the DCTS bit will get set when the reset is removed if the cts_n signal remains asserted. Reset Value: 0x0 Values: ■ 0x0 (NO_CHANGE): no change on cts_n since last read of MSR ■ 0x1 (CHANGE): change on cts_n since last read of MSR Exists: Always*/
#define UART_DCTS                      UART_DCTS_MSK
#define UART_DDSR_POS                  (1U)
#define UART_DDSR_MSK                  (0x1UL << UART_DDSR_POS)/*!< Delta Data Set Ready. This is used to indicate that the modem control line dsr_n has changed since the last time the MSR was read. Reading the MSR clears the DDSR bit. In Loopback Mode (MCR[4] set to one), DDSR reflects changes on MCR[0] (DTR). Note, if the DDSR bit is not set and the dsr_n signal is asserted (low) and a reset occurs (software or otherwise), then the DDSR bit will get set when the reset is removed if the dsr_n signal remains asserted. Reset Value: 0x0 Values: ■ 0x0 (NO_CHANGE): no change on dsr_n since last read of MSR ■ 0x1 (CHANGE): change on dsr_n since last read of MSR Exists: Always*/
#define UART_DDSR                      UART_DDSR_MSK
#define UART_TERI_POS                  (2U)
#define UART_TERI_MSK                  (0x1UL << UART_TERI_POS)/*!< Trailing Edge of Ring Indicator. This is used to indicate that a change on the input ri_n (from an active low, to an inactive high state) has occurred since the last time the MSR was read. Reading the MSR clears the TERI bit. In Loopback Mode (MCR[4] set to one), TERI reflects when MCR[2] (Out1) has changed state from a high to a low. Reset Value: 0x0 Values: ■ 0x0 (NO_CHANGE): no change on ri_n since last read of MSR ■ 0x1 (CHANGE): change on ri_n since last read of MSR Exists: Always*/
#define UART_TERI                      UART_TERI_MSK
#define UART_DDCD_POS                  (3U)
#define UART_DDCD_MSK                  (0x1UL << UART_DDCD_POS)/*!< Delta Data Carrier Detect. This is used to indicate that the modem control line dcd_n has changed since the last time the MSR was read. Reading the MSR clears the DDCD bit. In Loopback Mode (MCR[4] set to one), DDCD reflects changes on MCR[3] (Out2). Note, if the DDCD bit is not set and the dcd_n signal is asserted (low) and a reset occurs (software or otherwise), then the DDCD bit will get set when the reset is removed if the dcd_n signal remains asserted. Reset Value: 0x0 Values: ■ 0x0 (NO_CHANGE): No change on dcd_n since last read of MSR ■ 0x1 (CHANGE): change on dcd_n since last read of MSR Exists: Always*/
#define UART_DDCD                      UART_DDCD_MSK
#define UART_CTS_POS                   (4U)
#define UART_CTS_MSK                   (0x1UL << UART_CTS_POS)/*!< Clear to Send. This is used to indicate the current state of the modem control line cts_n. That is, this bit is the complement cts_n. When the Clear to Send input (cts_n) is asserted it is an indication that the modem or data set is ready to exchange data with the DW_apb_uart. In Loopback Mode (MCR[4] set to one), CTS is the same as MCR[1] (RTS). Reset Value: 0x0 Values: ■ 0x0 (DEASSERTED): cts_n input is de-asserted (logic 1) ■ 0x1 (ASSERTED): cts_n input is asserted (logic 0) Exists: Always*/
#define UART_CTS                       UART_CTS_MSK
#define UART_DSR_POS                   (5U)
#define UART_DSR_MSK                   (0x1UL << UART_DSR_POS)/*!< Data Set Ready. This is used to indicate the current state of the modem control line dsr_n. That is this bit is the complement dsr_n. When the Data Set Ready input (dsr_n) is asserted it is an indication that the modem or data set is ready to establish communications with the DW_apb_uart. In Loopback Mode (MCR[4] set to one), DSR is the same as MCR[0] (DTR). Reset Value: 0x0 Values: ■ 0x0 (DEASSERTED): dsr_n input is de-asserted (logic 1) ■ 0x1 (ASSERTED): dsr_n input is asserted (logic 0) Exists: Always*/
#define UART_DSR                       UART_DSR_MSK
#define UART_RI_POS                    (6U)
#define UART_RI_MSK                    (0x1UL << UART_RI_POS)/*!< Ring Indicator. This is used to indicate the current state of the modem control line ri_n. That is this bit is the complement ri_n. When the Ring Indicator input (ri_n) is asserted it is an indication that a telephone ringing signal has been received by the modem or data set. In Loopback Mode (MCR[4] set to one), RI is the same as MCR[2] (Out1). Reset Value: 0x0 Values: ■ 0x0 (DEASSERTED): ri_n input is de-asserted (logic 1) ■ 0x1 (ASSERTED): ri_n input is asserted (logic 0) Exists: Always*/
#define UART_RI                        UART_RI_MSK
#define UART_DCD_POS                   (7U)
#define UART_DCD_MSK                   (0x1UL << UART_DCD_POS)/*!< Data Carrier Detect. This is used to indicate the current state of the modem control line dcd_n. That is this bit is the complement dcd_n. When the Data Carrier Detect input (dcd_n) is asserted it is an indication that the carrier has been detected by the modem or data set. In Loopback Mode (MCR[4] set to one), DCD is the same as MCR[3] (Out2). Reset Value: 0x0 Values: ■ 0x0 (DEASSERTED): dcd_n input is de-asserted (logic 1) ■ 0x1 (ASSERTED): dcd_n input is asserted (logic 0) Exists: Always*/
#define UART_DCD                       UART_DCD_MSK
#define UART_RSVD_MSR_31TO8_POS        (8U)
#define UART_RSVD_MSR_31TO8_MSK        (0xffffffUL << UART_RSVD_MSR_31TO8_POS)/*!< MSR 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_MSR_31TO8            UART_RSVD_MSR_31TO8_MSK


//SCR offsetaddress : 0x1c
#define UART_SCR_POS                   (0U)
#define UART_SCR_MSK                   (0xffUL << UART_SCR_POS)/*!< This register is for programmers to use as a temporary storage space. It has no defined purpose in the DW_apb_uart. Reset Value: 0x0 Exists: Always*/
#define UART_SCR                       UART_SCR_MSK
#define UART_RSVD_SCR_31TO8_POS        (8U)
#define UART_RSVD_SCR_31TO8_MSK        (0xffffffUL << UART_RSVD_SCR_31TO8_POS)/*!< SCR 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SCR_31TO8            UART_RSVD_SCR_31TO8_MSK


//LPDLL offsetaddress : 0x20
#define UART_LPDLL_POS                 (0U)
#define UART_LPDLL_MSK                 (0xffUL << UART_LPDLL_POS)/*!< This register makes up the lower 8-bits of a 16-bit, read/ write, Low Power Divisor Latch register that contains the baud rate divisor for the UART which must give a baud rate of 115.2K. This is required for SIR Low Power (minimum pulse width) detection at the receiver. The output low power baud rate is equal to the serial clock (sclk) frequency divided by sixteen times the value of the baud rate divisor, as follows: Low power baud rate = (serial clock freq) / (16 * divisor) Therefore a divisor must be selected to give a baud rate of 115.2K. Note: When the Low Power Divisor Latch Registers (LPDLL and LPDLH) are set to zero, the low power baud clock is disabled and no low power pulse detection (or any pulse detection for that matter) will occur at the receiver. Also, once the LPDLL is set at least 8 clock cycles of the slowest DW_apb_uart clock should be allowed to pass before transmitting or receiving data. Reset Value: 0x0 Exists: Always*/
#define UART_LPDLL                     UART_LPDLL_MSK
#define UART_RSVD_LPDLL_31TO8_POS      (8U)
#define UART_RSVD_LPDLL_31TO8_MSK      (0xffffffUL << UART_RSVD_LPDLL_31TO8_POS)/*!< LPDLL 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_LPDLL_31TO8          UART_RSVD_LPDLL_31TO8_MSK


//LPDLH offsetaddress : 0x24
#define UART_LPDLH_POS                 (0U)
#define UART_LPDLH_MSK                 (0xffUL << UART_LPDLH_POS)/*!< This register makes up the upper 8-bits of a 16-bit, read/ write, Low Power Divisor Latch register that contains the baud rate divisor for the UART which must give a baud rate of 115.2K. This is required for SIR Low Power (minimum pulse width) detection at the receiver. The output low power baud rate is equal to the serial clock (sclk) frequency divided by sixteen times the value of the baud rate divisor, as follows: Low power baud rate = (serial clock freq) / (16 * divisor) Therefore a divisor must be selected to give a baud rate of 115.2K. Note: When the Low Power Divisor Latch Registers (LPDLL and LPDLH) are set to zero, the low power baud clock is disabled and no low power pulse detection (or any pulse detection for that matter) will occur at the receiver. Also, once the LPDLH is set, at least 8 clock cycles of the slowest DW_apb_uart clock should be allowed to pass before transmitting or receiving data. Reset Value: 0x0 Exists: Always*/
#define UART_LPDLH                     UART_LPDLH_MSK
#define UART_RSVD_LPDLH_31TO8_POS      (8U)
#define UART_RSVD_LPDLH_31TO8_MSK      (0xffffffUL << UART_RSVD_LPDLH_31TO8_POS)/*!< LPDLH 31to8 Reserved and read as 0. Exists: Always*/
#define UART_RSVD_LPDLH_31TO8          UART_RSVD_LPDLH_31TO8_MSK


//SRBRn offsetaddress : 0x30 + n*0x4
#define UART_SRBRN_POS                 (255U)
#define UART_SRBRN_MSK                 (0x1UL << UART_SRBRN_POS)/*!< Shadow Receive Buffer Register n. This is a shadow register for the RBR and has been allocated sixteen 32-bit locations so as to accommodate burst accesses from the master. This register contains the data byte received on the serial input port (sin) in UART mode or the serial infrared input (sir_in) in infrared mode. The data in this register is valid only if the Data Ready (DR) bit in the Line status Register (LSR) is set. If in non-FIFO mode (FIFO_MODE == NONE) or FIFOs are disabled (FCR[0] set to zero), the data in the RBR must be read before the next data arrives, otherwise it will be overwritten, resulting in an overrun error. If in FIFO mode (FIFO_MODE != NONE) and FIFOs are enabled (FCR[0] set to one), this register accesses the head of the receive FIFO. If the receive FIFO is full and this register is not read before the next data character arrives, then the data already in the FIFO will be preserved but any incoming data will be lost. An overrun error will also occur. Note: ■ When UART_9BIT_DATA_EN=0, this field width is 8. ■ When UART_9BIT_DATA_EN=1, this field width is 9. Exists: Always Range Variable[x]: SRBRN_REG_SIZE - 1*/
#define UART_SRBRN                     UART_SRBRN_MSK
#define UART_RSVD_SRBRN_POS            (255U)
#define UART_RSVD_SRBRN_MSK            (0x1UL << UART_RSVD_SRBRN_POS)/*!< SRBR0 31 to SRBRN_REG_SIZE Reserved bits read read as 0. Exists: Always Range Variable[y]: SRBRN_REG_SIZE*/
#define UART_RSVD_SRBRN                UART_RSVD_SRBRN_MSK


//STHRn offsetaddress : 0x30 + n*0x4
#define UART_STHRN_POS                 (255U)
#define UART_STHRN_MSK                 (0x1UL << UART_STHRN_POS)/*!< Shadow Transmit Holding Register n. This is a shadow register for the THR and has been allocated sixteen 32-bit locations so as to accommodate burst accesses from the master. This register contains data to be transmitted on the serial output port (sout) in UART mode or the serial infrared output (sir_out_n) in infrared mode. Data should only be written to the THR when the THR Empty (THRE) bit (LSR[5]) is set. If in non-FIFO mode or FIFO's are disabled (FCR[0] set to zero) and THRE is set, writing a single character to the THR clears the THRE. Any additional writes to the THR before the THRE is set again causes the THR data to be overwritten. If in FIFO mode and FIFO's are enabled (FCR[0] set to one) and THRE is set, x number of characters of data may be written to the THR before the FIFO is full. The number x (default=16) is determined by the value of FIFO Depth that you set during configuration. Any attempt to write data when the FIFO is full results in the write data being lost. Note: ■ When UART_9BIT_DATA_EN=0, this field width is 8. ■ When UART_9BIT_DATA_EN=1, this field width is 9. The 9th bit is applicable only when LCR_EXT[3]=1. Reset Value: 0x0 Exists: Always Range Variable[x]: STHRN_REG_SIZE - 1*/
#define UART_STHRN                     UART_STHRN_MSK
#define UART_RSVD_STHRN_POS            (255U)
#define UART_RSVD_STHRN_MSK            (0x1UL << UART_RSVD_STHRN_POS)/*!< STHR0 31 to STHRN_REG_SIZE Reserved bits read as 0. Exists: Always Range Variable[y]: STHRN_REG_SIZE*/
#define UART_RSVD_STHRN                UART_RSVD_STHRN_MSK


//FAR offsetaddress : 0x70
#define UART_FAR_POS                   (0U)
#define UART_FAR_MSK                   (0x1UL << UART_FAR_POS)/*!< Writes will have no effect when FIFO_ACCESS == No, always readable. This register is use to enable a FIFO access mode for testing, so that the receive FIFO can be written by the master and the transmit FIFO can be read by the master when FIFO's are implemented and enabled. When FIFOs are not implemented or not enabled it allows the RBR to be written by the master and the THR to be read by the master. Note, that when the FIFO access mode is enabled/disabled, the control portion of the receive FIFO and transmit FIFO is reset and the FIFO's are treated as empty. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): FIFO access mode disabled ■ 0x1 (ENABLED): FIFO access mode enabled Exists: Always Memory Access: "(FIFO_ACCESS==1) ? \"read-write\" : \"read-only\""*/
#define UART_FAR                       UART_FAR_MSK
#define UART_RSVD_FAR_31TO1_POS        (1U)
#define UART_RSVD_FAR_31TO1_MSK        (0x7fffffffUL << UART_RSVD_FAR_31TO1_POS)/*!< FAR 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_FAR_31TO1            UART_RSVD_FAR_31TO1_MSK


//TFR offsetaddress : 0x74
#define UART_TFR_POS                   (0U)
#define UART_TFR_MSK                   (0xffUL << UART_TFR_POS)/*!< Transmit FIFO Read. These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one). When FIFO's are implemented and enabled, reading this register gives the data at the top of the transmit FIFO. Each consecutive read pops the transmit FIFO and gives the next data value that is currently at the top of the FIFO. When FIFO's are not implemented or not enabled, reading this register gives the data in the THR. Reset Value: 0x0 Exists: Always*/
#define UART_TFR                       UART_TFR_MSK
#define UART_RSVD_TFR_31TO8_POS        (8U)
#define UART_RSVD_TFR_31TO8_MSK        (0xffffffUL << UART_RSVD_TFR_31TO8_POS)/*!< TFR 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_TFR_31TO8            UART_RSVD_TFR_31TO8_MSK


//RFW offsetaddress : 0x78
#define UART_RFWD_POS                  (0U)
#define UART_RFWD_MSK                  (0xffUL << UART_RFWD_POS)/*!< Receive FIFO Write Data. These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one). When FIFO's are implemented and enabled, the data that is written to the RFWD is pushed into the receive FIFO. Each consecutive write pushes the new data to the next write location in the receive FIFO. When FIFO's are not implemented or not enabled, the data that is written to the RFWD is pushed into the RBR. Reset Value: 0x0 Exists: Always*/
#define UART_RFWD                      UART_RFWD_MSK
#define UART_RFPE_POS                  (8U)
#define UART_RFPE_MSK                  (0x1UL << UART_RFPE_POS)/*!< Receive FIFO Parity Error. These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one). When FIFO's are implemented and enabled, this bit is used to write parity error detection information to the receive FIFO. When FIFO's are not implemented or not enabled, this bit is used to write parity error detection information to the RBR. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Parity error disabled ■ 0x1 (ENABLED): Parity error enabled Exists: Always*/
#define UART_RFPE                      UART_RFPE_MSK
#define UART_RFFE_POS                  (9U)
#define UART_RFFE_MSK                  (0x1UL << UART_RFFE_POS)/*!< Receive FIFO Framing Error. These bits are only valid when FIFO access mode is enabled (FAR[0] is set to one). When FIFO's are implemented and enabled, this bit is used to write framing error detection information to the receive FIFO. When FIFO's are not implemented or not enabled, this bit is used to write framing error detection information to the RBR. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Frame error disabled ■ 0x1 (ENABLED): Frame error enabled Exists: Always*/
#define UART_RFFE                      UART_RFFE_MSK
#define UART_RSVD_RFW_31TO10_POS       (10U)
#define UART_RSVD_RFW_31TO10_MSK       (0x3fffffUL << UART_RSVD_RFW_31TO10_POS)/*!< RFW 31to10 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_RFW_31TO10           UART_RSVD_RFW_31TO10_MSK


//USR offsetaddress : 0x7c
#define UART_BUSY_POS                  (0U)
#define UART_BUSY_MSK                  (0x1UL << UART_BUSY_POS)/*!< UART Busy. This bit is only valid when UART_16550_COMPATIBLE == NO. This indicates that a serial transfer is in progress, when cleared indicates that the DW_apb_uart is idle or inactive. This bit will be set to 1 (busy) under any of the following conditions: - Transmission in progress on serial interface - Transmit data present in THR, when FIFO access mode is not being used (FAR = 0) and the baud divisor is non-zero ({DLH,DLL} does not equal 0) when the divisor latch access bit is 0 (LCR.DLAB = 0) - Reception in progress on the interface - Receive data present in RBR, when FIFO access mode is not being used (FAR = 0) Note: It is possible for the UART Busy bit to be cleared even though a new character may have been sent from another device. That is, if the DW_apb_uart has no data in the THR and RBR and there is no transmission in progress and a start bit of a new character has just reached the DW_apb_uart. This is due to the fact that a valid start is not seen until the middle of the bit period and this duration is dependent on the baud divisor that has been programmed. If a second system clock has been implemented (CLOCK_MODE == Enabled), the assertion of this bit will also be delayed by several cycles of the slower clock. Reset Value: 0x0 Values: ■ 0x0 (IDLE): DW_apb_uart is idle or inactive ■ 0x1 (BUSY): DW_apb_uart is busy (actively transferring data) Exists: UART_16550_COMPATIBLE == 0 Volatile: true*/
#define UART_BUSY                      UART_BUSY_MSK
#define UART_TFNF_POS                  (1U)
#define UART_TFNF_MSK                  (0x1UL << UART_TFNF_POS)/*!< Transmit FIFO Not Full. This bit is only valid when FIFO_STAT == YES. This is used to indicate that the transmit FIFO in not full. This bit is cleared when the TX FIFO is full. Reset Value: 0x1 Values: ■ 0x0 (FULL): Transmit FIFO is full ■ 0x1 (NOT_FULL): Transmit FIFO is not full Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1) Volatile: true*/
#define UART_TFNF                      UART_TFNF_MSK
#define UART_TFE_POS                   (2U)
#define UART_TFE_MSK                   (0x1UL << UART_TFE_POS)/*!< Transmit FIFO Empty. This bit is only valid when FIFO_STAT == YES. This is used to indicate that the transmit FIFO is completely empty. This bit is cleared when the TX FIFO is no longer empty. Reset Value: 0x1 Values: ■ 0x0 (NOT_EMPTY): Transmit FIFO is not empty ■ 0x1 (EMPTY): Transmit FIFO is empty Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1) Volatile: true*/
#define UART_TFE                       UART_TFE_MSK
#define UART_RFNE_POS                  (3U)
#define UART_RFNE_MSK                  (0x1UL << UART_RFNE_POS)/*!< Receive FIFO Not Empty. This bit is only valid when FIFO_STAT == YES. This is used to indicate that the receive FIFO contains one or more entries. This bit is cleared when the RX FIFO is empty. Reset Value: 0x0 Values: ■ 0x0 (EMPTY): Receive FIFO is empty ■ 0x1 (NOT_EMPTY): Receive FIFO is not empty Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1) Volatile: true*/
#define UART_RFNE                      UART_RFNE_MSK
#define UART_RFF_POS                   (4U)
#define UART_RFF_MSK                   (0x1UL << UART_RFF_POS)/*!< Receive FIFO Full. This bit is only valid when FIFO_STAT == YES. This is used to indicate that the receive FIFO is completely full. That is: This bit is cleared when the RX FIFO is no longer full. Reset Value: 0x0 Values: ■ 0x0 (NOT_FULL): Receive FIFO not full ■ 0x1 (FULL): Receive FIFO full Exists: (FIFO_STAT == 1) && (FIFO_MODE != 0) && (ADDITIONAL_FEATURES == 1) Volatile: true*/
#define UART_RFF                       UART_RFF_MSK
#define UART_RSVD_USR_31TO5_POS        (5U)
#define UART_RSVD_USR_31TO5_MSK        (0x7ffffffUL << UART_RSVD_USR_31TO5_POS)/*!< USR 31to5 Reserved bits read as 0. Exists: Always Volatile: true*/
#define UART_RSVD_USR_31TO5            UART_RSVD_USR_31TO5_MSK


//TFL offsetaddress : 0x80
#define UART_TFL_POS                   (255U)
#define UART_TFL_MSK                   (0x1UL << UART_TFL_POS)/*!< Transmit FIFO Level. This indicates the number of data entries in the transmit FIFO. Reset Value: 0x0 Exists: Always Range Variable[x]: FIFO_ADDR_WIDTH*/
#define UART_TFL                       UART_TFL_MSK
#define UART_RSVD_TFL_31TOADDR_WIDTH_POS (255U)
#define UART_RSVD_TFL_31TOADDR_WIDTH_MSK (0x1UL << UART_RSVD_TFL_31TOADDR_WIDTH_POS)/*!< TFL 31 to ADDR_WIDTH Reserved bits read as 0. Exists: Always Range Variable[y]: FIFO_ADDR_WIDTH + 1*/
#define UART_RSVD_TFL_31TOADDR_WIDTH   UART_RSVD_TFL_31TOADDR_WIDTH_MSK


//RFL offsetaddress : 0x84
#define UART_RFL_POS                   (255U)
#define UART_RFL_MSK                   (0x1UL << UART_RFL_POS)/*!< Receive FIFO Level. This is indicates the number of data entries in the receive FIFO. Reset Value: 0x0 Exists: Always Range Variable[x]: FIFO_ADDR_WIDTH*/
#define UART_RFL                       UART_RFL_MSK
#define UART_RSVD_RFL_31TOADDR_WIDTH_POS (255U)
#define UART_RSVD_RFL_31TOADDR_WIDTH_MSK (0x1UL << UART_RSVD_RFL_31TOADDR_WIDTH_POS)/*!< RFL 31 to ADDR_WIDTH Reserved bits read as 0. Exists: Always Range Variable[y]: FIFO_ADDR_WIDTH + 1*/
#define UART_RSVD_RFL_31TOADDR_WIDTH   UART_RSVD_RFL_31TOADDR_WIDTH_MSK


//SRR offsetaddress : 0x88
#define UART_UR_POS                    (0U)
#define UART_UR_MSK                    (0x1UL << UART_UR_POS)/*!< UART Reset. This asynchronously resets the DW_apb_uart and synchronously removes the reset assertion. For a two clock implementation both pclk and sclk domains will be reset. Reset Value: 0x0 Values: ■ 0x0 (NO_RESET): No Uart Reset ■ 0x1 (RESET): Uart reset Exists: Always*/
#define UART_UR                        UART_UR_MSK
#define UART_RFR_POS                   (1U)
#define UART_RFR_MSK                   (0x1UL << UART_RFR_POS)/*!< RCVR FIFO Reset. Writes will have no effect when FIFO_MODE == NONE. This is a shadow register for the RCVR FIFO Reset bit (FCR[1]). This can be used to remove the burden on software having to store previously written FCR values (which are pretty static) just to reset the reeive FIFO. This resets the control portion of the receive FIFO and treats the FIFO as empty. This will also de-assert the DMA RX request and single signals when additional DMA handshaking signals are selected (DMA_EXTRA == YES). Note that this bit is 'self- clearing' and it is not necessary to clear this bit. Reset Value: 0x0 Exists: Always Memory Access: "(FIFO_MODE !=0) ? \"write-only\" : \"read-only\""*/
#define UART_RFR                       UART_RFR_MSK
#define UART_XFR_POS                   (2U)
#define UART_XFR_MSK                   (0x1UL << UART_XFR_POS)/*!< XMIT FIFO Reset . Writes will have no effect when FIFO_MODE == NONE. This is a shadow register for the XMIT FIFO Reset bit (FCR[2]). This can be used to remove the burden on software having to store previously written FCR values (which are pretty static) just to reset the transmit FIFO. This resets the control portion of the transmit FIFO and treats the FIFO as empty. This will also de-assert the DMA TX request and single signals when additional DMA handshaking signals are selected (DMA_EXTRA = YES). Note that this bit is 'self-clearing'. It is not necessary to clear this bit. Reset Value: 0x0 Exists: Always Memory Access: "(FIFO_MODE !=0) ? \"write-only\" : \"read-only\""*/
#define UART_XFR                       UART_XFR_MSK
#define UART_RSVD_SRR_31TO3_POS        (3U)
#define UART_RSVD_SRR_31TO3_MSK        (0x1fffffffUL << UART_RSVD_SRR_31TO3_POS)/*!< SRR 31to3 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SRR_31TO3            UART_RSVD_SRR_31TO3_MSK


//SRTS offsetaddress : 0x8c
#define UART_SRTS_POS                  (0U)
#define UART_SRTS_MSK                  (0x1UL << UART_SRTS_POS)/*!< Shadow Request to Send. This is a shadow register for the RTS bit (MCR[1]), this can be used to remove the burden of having to performing a read modify write on the MCR. This is used to directly control the Request to Send (rts_n) output. The Request To Send (rts_n) output is used to inform the modem or data set that the UART is ready to exchange data. When Auto RTS Flow Control is not enabled (MCR[5] set to zero), the rts_n signal is set low by programming MCR[1] (RTS) to a high. In Auto Flow Control, AFCE_MODE == Enabled and active (MCR[5] set to one) and FIFO's enable (FCR[0] set to one), the rts_n output is controlled in the same way, but is also gated with the receiver FIFO threshold trigger (rts_n is inactive high when above the threshold) only when RTC Flow Trigger is disabled; otherwise it is gated by the receiver FIFO almost-full trigger, where 'almost full' refers to two available slots in the FIFO (rts_n is inactive high when above the threshold). Note that in Loopback mode (MCR[4] set to one), the rts_n output is held inactive high while the value of this location is internally looped back to an input. Reset Value: 0x0 Values: ■ 0x0 (DEASSERTED): Shadow Request to Send uart_rts_n logic1 ■ 0x1 (ASSERTED): Shadow Request to Send uart_rts_n logic0 Exists: Always*/
#define UART_SRTS                      UART_SRTS_MSK
#define UART_RSVD_SRTS_31TO1_POS       (1U)
#define UART_RSVD_SRTS_31TO1_MSK       (0x7fffffffUL << UART_RSVD_SRTS_31TO1_POS)/*!< SRTS 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SRTS_31TO1           UART_RSVD_SRTS_31TO1_MSK


//SBCR offsetaddress : 0x90
#define UART_SBCB_POS                  (0U)
#define UART_SBCB_MSK                  (0x1UL << UART_SBCB_POS)/*!< Shadow Break Control Bit. This is a shadow register for the Break bit (LCR[6]), this can be used to remove the burden of having to performing a read modify write on the LCR. This is used to cause a break condition to be transmitted to the receiving device. If set to one the serial output is forced to the spacing (logic 0) state. When not in Loopback Mode, as determined by MCR[4], the sout line is forced low until the Break bit is cleared. If SIR_MODE == Enabled and active (MCR[6] set to one) the sir_out_n line is continuously pulsed. When in Loopback Mode, the break condition is internally looped back to the receiver. Reset Value: 0x0 Values: ■ 0x0 (NO_BREAK): No spacing on serial output ■ 0x1 (BREAK): Serial output forced to the spacing Exists: Always*/
#define UART_SBCB                      UART_SBCB_MSK
#define UART_RSVD_SBCR_31TO1_POS       (1U)
#define UART_RSVD_SBCR_31TO1_MSK       (0x7fffffffUL << UART_RSVD_SBCR_31TO1_POS)/*!< SBCR 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SBCR_31TO1           UART_RSVD_SBCR_31TO1_MSK


//SDMAM offsetaddress : 0x94
#define UART_SDMAM_POS                 (0U)
#define UART_SDMAM_MSK                 (0x1UL << UART_SDMAM_POS)/*!< Shadow DMA Mode. This is a shadow register for the DMA mode bit (FCR[3]). This can be used to remove the burden of having to store the previously written value to the FCR in memory and having to mask this value so that only the DMA Mode bit gets updated. This determines the DMA signalling mode used for the dma_tx_req_n and dma_rx_req_n output signals when additional DMA handshaking signals are not selected (DMA_EXTRA == NO). See section 5.9 on page 54 for details on DMA support. Reset Value: 0x0 Values: ■ 0x0 (MODE_0): Mode 0 ■ 0x1 (MODE_1): Mode 1 Exists: Always*/
#define UART_SDMAM                     UART_SDMAM_MSK
#define UART_RSVD_SDMAM_31TO1_POS      (1U)
#define UART_RSVD_SDMAM_31TO1_MSK      (0x7fffffffUL << UART_RSVD_SDMAM_31TO1_POS)/*!< SDMAM 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SDMAM_31TO1          UART_RSVD_SDMAM_31TO1_MSK


//SFE offsetaddress : 0x98
#define UART_SFE_POS                   (0U)
#define UART_SFE_MSK                   (0x1UL << UART_SFE_POS)/*!< Shadow FIFO Enable. This is a shadow register for the FIFO enable bit (FCR[0]). This can be used to remove the burden of having to store the previously written value to the FCR in memory and having to mask this value so that only the FIFO enable bit gets updated. This enables/disables the transmit (XMIT) and receive (RCVR) FIFO's. If this bit is set to zero (disabled) after being enabled then both the XMIT and RCVR controller portion of FIFO's will be reset. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): FIFOs are disabled ■ 0x1 (ENABLED): FIFOs are enabled Exists: Always*/
#define UART_SFE                       UART_SFE_MSK
#define UART_RSVD_SFE_31TO1_POS        (1U)
#define UART_RSVD_SFE_31TO1_MSK        (0x7fffffffUL << UART_RSVD_SFE_31TO1_POS)/*!< SFE 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SFE_31TO1            UART_RSVD_SFE_31TO1_MSK


//SRT offsetaddress : 0x9c
#define UART_SRT_POS                   (0U)
#define UART_SRT_MSK                   (0x3UL << UART_SRT_POS)/*!< Shadow RCVR Trigger. This is a shadow register for the RCVR trigger bits (FCR[7:6]). This can be used to remove the burden of having to store the previously written value to the FCR in memory and having to mask this value so that only the RCVR trigger bit gets updated. This is used to select the trigger level in the receiver FIFO at which the Received Data Available Interrupt will be generated. It also determines when the dma_rx_req_n signal will be asserted when DMA Mode (FCR[3]) is set to one. Reset Value: 0x0 Values: ■ 0x0 (FIFO_CHAR_1): 1 character in FIFO ■ 0x1 (FIFO_QUARTER_FULL): FIFO 1/4 full ■ 0x2 (FIFO_HALF_FULL): FIFO 1/2 full ■ 0x3 (FIFO_FULL_2): FIFO 2 less than full Exists: Always*/
#define UART_SRT                       UART_SRT_MSK
#define UART_RSVD_SRT_31TO2_POS        (2U)
#define UART_RSVD_SRT_31TO2_MSK        (0x3fffffffUL << UART_RSVD_SRT_31TO2_POS)/*!< SRT 31to2 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_SRT_31TO2            UART_RSVD_SRT_31TO2_MSK


//STET offsetaddress : 0xa0
#define UART_STET_POS                  (0U)
#define UART_STET_MSK                  (0x3UL << UART_STET_POS)/*!< Shadow TX Empty Trigger. This is a shadow register for the TX empty trigger bits (FCR[5:4]). This can be used to remove the burden of having to store the previously written value to the FCR in memory and having to mask this value so that only the TX empty trigger bit gets updated. Writes will have no effect when THRE_MODE_USER == Disabled. This is used to select the empty threshold level at which the THRE Interrupts will be generated when the mode is active. Reset Value: 0x0 Values: ■ 0x0 (FIFO_EMPTY): FIFO empty ■ 0x1 (FIFO_CHAR_2): 2 characters in FIFO ■ 0x2 (FIFO_QUARTER_FULL): FIFO 1/4 full ■ 0x3 (FIFO_HALF_FULL): FIFO 1/2 full Exists: Always*/
#define UART_STET                      UART_STET_MSK
#define UART_RSVD_STET_31TO2_POS       (2U)
#define UART_RSVD_STET_31TO2_MSK       (0x3fffffffUL << UART_RSVD_STET_31TO2_POS)/*!< STET 31to2 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_STET_31TO2           UART_RSVD_STET_31TO2_MSK


//HTX offsetaddress : 0xa4
#define UART_HTX_POS                   (0U)
#define UART_HTX_MSK                   (0x1UL << UART_HTX_POS)/*!< Halt TX. Writes will have no effect when FIFO_MODE == NONE, always readable. This register is use to halt transmissions for testing, so that the transmit FIFO can be filled by the master when FIFO's are implemented and enabled. Note, if FIFO's are implemented and not enabled the setting of the halt TX register will have no effect on operation. Reset Value: 0x0 Values: ■ 0x0 (DISABLED): Halt Transmission disabled ■ 0x1 (ENABLED): Halt Transmission enabled Exists: Always Memory Access: "(FIFO_MODE==0) ? \"read-only\" : \"read-write\""*/
#define UART_HTX                       UART_HTX_MSK
#define UART_RSVD_HTX_31TO1_POS        (1U)
#define UART_RSVD_HTX_31TO1_MSK        (0x7fffffffUL << UART_RSVD_HTX_31TO1_POS)/*!< HTX 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_HTX_31TO1            UART_RSVD_HTX_31TO1_MSK


//DMASA offsetaddress : 0xa8
#define UART_DMASA_POS                 (0U)
#define UART_DMASA_MSK                 (0x1UL << UART_DMASA_POS)/*!< DMA Software Acknowledge. Writes will have no effect when DMA_EXTRA == No. This register is use to perform DMA software acknowledge if a transfer needs to be terminated due to an error condition. For example, if the DMA disables the channel, then the DW_apb_uart should clear its request. This will cause the TX request, TX single, RX request and RX single signals to de- assert. Note that this bit is 'self-clearing' and it is not necessary to clear this bit. Reset Value: 0x0 Values: ■ 0x1 (SOFT_ACK): DMA software acknowledge Exists: Always Memory Access: "(DMA_EXTRA==1) ? \"write-only\" : \"read-only\""*/
#define UART_DMASA                     UART_DMASA_MSK
#define UART_RSVD_DMASA_31TO1_POS      (1U)
#define UART_RSVD_DMASA_31TO1_MSK      (0x7fffffffUL << UART_RSVD_DMASA_31TO1_POS)/*!< DMASA 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_DMASA_31TO1          UART_RSVD_DMASA_31TO1_MSK


//TCR offsetaddress : 0xac
#define UART_RS485_EN_POS              (0U)
#define UART_RS485_EN_MSK              (0x1UL << UART_RS485_EN_POS)/*!< RS485 Transfer Enable. ■ 0 : In this mode, the transfers are still in the RS232 mode. All other fields in this register are reserved and register DE_EN/RE_EN/TAT are also reserved. ■ 1 : In this mode, the transfers will happen in RS485 mode. All other fields of this register are applicable. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_RS485_EN                  UART_RS485_EN_MSK
#define UART_RE_POL_POS                (1U)
#define UART_RE_POL_MSK                (0x1UL << UART_RE_POL_POS)/*!< Receiver Enable Polarity. ■ 1: RE signal is active high ■ 0: RE signal is active low Reset Value: UART_RE_POL Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_RE_POL                    UART_RE_POL_MSK
#define UART_DE_POL_POS                (2U)
#define UART_DE_POL_MSK                (0x1UL << UART_DE_POL_POS)/*!< Driver Enable Polarity. ■ 1: DE signal is active high ■ 0: DE signal is active low Reset Value: UART_DE_POL Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DE_POL                    UART_DE_POL_MSK
#define UART_XFER_MODE_POS             (3U)
#define UART_XFER_MODE_MSK             (0x3UL << UART_XFER_MODE_POS)/*!< Transfer Mode. ■ 0: In this mode, transmit and receive can happen simultaneously. The user can enable DE_EN, RE_EN at any point of time. Turn around timing as programmed in the TAT register is not applicable in this mode. ■ 1: In this mode, DE and RE are mutually exclusive. Either DE or RE only one of them is expected to be enabled through programming. Hardware will consider the Turn Around timings which are programmed in the TAT register while switching from RE to DE or DE to RE. For transmission Hardware will wait if it is in middle of receiving any transfer, before it starts transmitting. ■ 2: In this mode, DE and RE are mutually exclusive. Once DE_EN/RE_EN is programed - by default 're' will be enabled and DW_apb_uart controller will be ready to receive. If the user programs the TX FIFO with the data then DW_apb_uart, after ensuring no receive is in progress, disable 're' and enable 'de' signal. Once the TX FIFO becomes empty, 're' signal gets enabled and 'de' signal will be disabled. In this mode of operation hardware will consider the Turn Around timings which are programmed in the TAT register while switching from RE to DE or DE to RE. In this mode, 'de' and 're' signals are strictly complementary to each other. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_XFER_MODE                 UART_XFER_MODE_MSK
#define UART_RSVD_TCR_31TO5_POS        (5U)
#define UART_RSVD_TCR_31TO5_MSK        (0x7ffffffUL << UART_RSVD_TCR_31TO5_POS)/*!< TCR 31to5 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_TCR_31TO5            UART_RSVD_TCR_31TO5_MSK


//DE_EN offsetaddress : 0xb0
#define UART_DE_ENABLE_POS             (0U)
#define UART_DE_ENABLE_MSK             (0x1UL << UART_DE_ENABLE_POS)/*!< DE Enable control. The 'DE Enable' register bit is used to control assertion and de-assertion of 'de' signal. - 0: De-assert 'de' signal - 1: Assert 'de' signal Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DE_ENABLE                 UART_DE_ENABLE_MSK
#define UART_RSVD_DE_EN_31TO1_POS      (1U)
#define UART_RSVD_DE_EN_31TO1_MSK      (0x7fffffffUL << UART_RSVD_DE_EN_31TO1_POS)/*!< DE_EN 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_DE_EN_31TO1          UART_RSVD_DE_EN_31TO1_MSK


//RE_EN offsetaddress : 0xb4
#define UART_RE_ENABLE_POS             (0U)
#define UART_RE_ENABLE_MSK             (0x1UL << UART_RE_ENABLE_POS)/*!< RE Enable control. The 'RE Enable' register bit is used to control assertion and de-assertion of 're' signal. ■ 0: De-assert 're' signal ■ 1: Assert 're' signal Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_RE_ENABLE                 UART_RE_ENABLE_MSK
#define UART_RSVD_RE_EN_31TO1_POS      (1U)
#define UART_RSVD_RE_EN_31TO1_MSK      (0x7fffffffUL << UART_RSVD_RE_EN_31TO1_POS)/*!< RE_EN 31to1 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_RE_EN_31TO1          UART_RSVD_RE_EN_31TO1_MSK


//DET offsetaddress : 0xb8
#define UART_DE_ASSERTION_TIME_POS     (0U)
#define UART_DE_ASSERTION_TIME_MSK     (0xffUL << UART_DE_ASSERTION_TIME_POS)/*!< Driver Enable assertion time. This field controls the amount of time (in terms of number of serial clock periods) between the assertion of rising edge of Driver output enable signal to serial transmit enable. Any data in transmit buffer, will start on serial output (sout) after the transmit enable. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DE_ASSERTION_TIME         UART_DE_ASSERTION_TIME_MSK
#define UART_RSVD_DE_AT_15TO8_POS      (8U)
#define UART_RSVD_DE_AT_15TO8_MSK      (0xffUL << UART_RSVD_DE_AT_15TO8_POS)/*!< DET 15to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_DE_AT_15TO8          UART_RSVD_DE_AT_15TO8_MSK
#define UART_DE_DE_ASSERTION_TIME_POS  (16U)
#define UART_DE_DE_ASSERTION_TIME_MSK  (0xffUL << UART_DE_DE_ASSERTION_TIME_POS)/*!< Driver Enable de-assertion time. This field controls the amount of time (in terms of number of serial clock periods) between the end of stop bit on the sout to the falling edge of Driver output enable signal. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DE_DE_ASSERTION_TIME      UART_DE_DE_ASSERTION_TIME_MSK
#define UART_RSVD_DE_DEAT_31TO24_POS   (24U)
#define UART_RSVD_DE_DEAT_31TO24_MSK   (0xffUL << UART_RSVD_DE_DEAT_31TO24_POS)/*!< DET 31to24 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_DE_DEAT_31TO24       UART_RSVD_DE_DEAT_31TO24_MSK


//TAT offsetaddress : 0xbc
#define UART_DE_TO_RE_POS              (0U)
#define UART_DE_TO_RE_MSK              (0xffffUL << UART_DE_TO_RE_POS)/*!< Driver Enable to Receiver Enable TurnAround time. Turnaround time (in terms of serial clock) for DE De- assertion to RE assertion. Note: The actual time is the programmed value + 1. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DE_TO_RE                  UART_DE_TO_RE_MSK
#define UART_RE_TO_DE_POS              (16U)
#define UART_RE_TO_DE_MSK              (0xffffUL << UART_RE_TO_DE_POS)/*!< Receiver Enable to Driver Enable TurnAround time. Turnaround time (in terms of serial clock) for RE De- assertion to DE assertion. Note: - If the DE assertion time in the DET register is 0, then the actual value is the programmed value + 3. - If the DE assertion time in the DET register is 1, then the actual value is the programmed value + 2. - If the DE assertion time in the DET register is greater than 1, then the actual value is the programmed value + 1. Reset Value: 0x0 Exists: Always Memory Access: "(UART_RS485_INTERFACE_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_RE_TO_DE                  UART_RE_TO_DE_MSK


//DLF offsetaddress : 0xc0
#define UART_DLF_POS                   (255U)
#define UART_DLF_MSK                   (0x1UL << UART_DLF_POS)/*!< Fractional part of divisor. The fractional value is added to integer value set by DLH, DLL. Fractional value is determined by (Divisor Fraction value)/(2^DLF_SIZE). For information on DLF values to be programmed for DLF_SIZE=4, see the 'Fractional Baud Rate Support' section in the DW_apb_uart Databook. Reset Value: 0x0 Exists: Always Range Variable[x]: DLF_SIZE - 1 Memory Access: "(FRACTIONAL_BAUD_DIVISOR_EN==1) ? \"read-write\" : \"read-only\""*/
#define UART_DLF                       UART_DLF_MSK
#define UART_RSVD_DLF_POS              (255U)
#define UART_RSVD_DLF_MSK              (0x1UL << UART_RSVD_DLF_POS)/*!< DLF 31 to DLF_SIZE Reserved bits read as 0. Exists: Always Range Variable[y]: DLF_SIZE*/
#define UART_RSVD_DLF                  UART_RSVD_DLF_MSK


//RAR offsetaddress : 0xc4
#define UART_RAR_POS                   (0U)
#define UART_RAR_MSK                   (0xffUL << UART_RAR_POS)/*!< This is an address matching register during receive mode. If the 9-th bit is set in the incoming character then the remaining 8-bits will be checked against this register value. If the match happens then sub-sequent characters with 9-th bit set to 0 will be treated as data byte until the next address byte is received. Note: - This register is applicable only when 'ADDR_MATCH'(LCR_EXT[1] and 'DLS_E' (LCR_EXT[0]) bits are set to 1. - If UART_16550_COMPATIBLE is configured to 0, then RAR should be programmed only when UART is not busy. - If UART_16550_COMPATIBLE is configured to 0, then RAR can be programmed at any point of the time. However, user must not change this register value when any receive is in progress. Reset Value: 0x0 Exists: Always Memory Access: "(UART_9BIT_DATA_EN==1) ? \"read- write\" : \"read-only\""*/
#define UART_RAR                       UART_RAR_MSK
#define UART_RSVD_RAR_31TO8_POS        (8U)
#define UART_RSVD_RAR_31TO8_MSK        (0xffffffUL << UART_RSVD_RAR_31TO8_POS)/*!< RAR 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_RAR_31TO8            UART_RSVD_RAR_31TO8_MSK


//TAR offsetaddress : 0xc8
#define UART_TAR_POS                   (0U)
#define UART_TAR_MSK                   (0xffUL << UART_TAR_POS)/*!< This is an address matching register during transmit mode. If DLS_E (LCR_EXT[0]) bit is enabled, then DW_apb_uart will send the 9-bit character with 9-th bit set to 1 and remaining 8-bit address will be sent from this register provided 'SEND_ADDR' (LCR_EXT[2]) bit is set to 1. Note: - This register is used only to send the address. The normal data should be sent by programming THR register. - Once the address is started to send on the DW_apb_uart serial lane, then 'SEND_ADDR' bit will be auto-cleared by the hardware. Reset Value: 0x0 Exists: Always Memory Access: "(UART_9BIT_DATA_EN==1) ? \"read- write\" : \"read-only\""*/
#define UART_TAR                       UART_TAR_MSK
#define UART_RSVD_TAR_31TO8_POS        (8U)
#define UART_RSVD_TAR_31TO8_MSK        (0xffffffUL << UART_RSVD_TAR_31TO8_POS)/*!< TAR 31to8 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_TAR_31TO8            UART_RSVD_TAR_31TO8_MSK


//LCR_EXT offsetaddress : 0xcc
#define UART_DLS_E_POS                 (0U)
#define UART_DLS_E_MSK                 (0x1UL << UART_DLS_E_POS)/*!< Extension for DLS. This bit is used to enable 9-bit data for transmit and receive transfers. Reset Value: 0x0 Exists: Always Volatile: true*/
#define UART_DLS_E                     UART_DLS_E_MSK
#define UART_ADDR_MATCH_POS            (1U)
#define UART_ADDR_MATCH_MSK            (0x1UL << UART_ADDR_MATCH_POS)/*!< Address Match Mode.This bit is used to enable the address match feature during receive. ■ 1 = Address match mode; DW_apb_uart will wait until the incoming character with 9-th bit set to 1. And further checks to see if the address matches with what is programmed in 'Receive Address Match Register'. If match is found, then sub-sequent characters will be treated as valid data and DW_apb_uart starts receiving data. ■ 0 = Normal mode; DW_apb_uart will start to receive the data and 9-bit character will be formed and written into the receive RXFIFO. User is responsible to read the data and differentiate b/n address and data. Note: This field is applicable only when DLS_E is set to 1. Exists: Always Volatile: true*/
#define UART_ADDR_MATCH                UART_ADDR_MATCH_MSK
#define UART_SEND_ADDR_POS             (2U)
#define UART_SEND_ADDR_MSK             (0x1UL << UART_SEND_ADDR_POS)/*!< Send address control bit. This bit is used as a control knob for the user to determine when to send the address during transmit mode. ■ 1 = 9-bit character will be transmitted with 9-th bit set to 1 and the remaining 8-bits will match to what is being programmed in 'Transmit Address Register'. ■ 0 = 9-bit character will be transmitted with 9-th bit set to 0 and the remaining 8-bits will be taken from the TXFIFO which is programmed through 8-bit wide THR/STHR register. Note: ■ 1. This bit is auto-cleared by the hardware, after sending out the address character. User is not expected to program this bit to 0. ■ 2. This field is applicable only when DLS_E bit is set to 1 and TRANSMIT_MODE is set to 0. Reset Value: 0x0 Exists: UART_9BIT_DATA_EN == 1 Volatile: true*/
#define UART_SEND_ADDR                 UART_SEND_ADDR_MSK
#define UART_TRANSMIT_MODE_POS         (3U)
#define UART_TRANSMIT_MODE_MSK         (0x1UL << UART_TRANSMIT_MODE_POS)/*!< Transmit mode control bit. This bit is used to control the type of transmit mode during 9-bit data transfers. ■ 1: In this mode of operation, Transmit Holding Register (THR) and Shadow Transmit Holding Register (STHR) are 9-bit wide. The user needs to ensure that the THR/ STHR register is written correctly for address/data. Address: 9th bit is set to 1, Data : 9th bit is set to 0. Note: Transmit address register (TAR) is not applicable in this mode of operation. ■ 0: In this mode of operation, Transmit Holding Register (THR) and Shadow Transmit Holding register (STHR) are 8-bit wide. The user needs to program the address into Transmit Address Register (TAR) and data into the THR/ STHR register. SEND_ADDR bit is used as a control knob to indicate the DW_apb_uart on when to send the address. Reset Value: 0x0 Exists: Always Volatile: true*/
#define UART_TRANSMIT_MODE             UART_TRANSMIT_MODE_MSK
#define UART_RSVD_LCR_EXT_POS          (4U)
#define UART_RSVD_LCR_EXT_MSK          (0xfffffffUL << UART_RSVD_LCR_EXT_POS)/*!< LCR_EXT 31to4 Reserved bits read as 0. Exists: Always Volatile: true*/
#define UART_RSVD_LCR_EXT              UART_RSVD_LCR_EXT_MSK


//CPR offsetaddress : 0xf4
#define UART_APB_DATA_WIDTH_POS        (0U)
#define UART_APB_DATA_WIDTH_MSK        (0x3UL << UART_APB_DATA_WIDTH_POS)/*!< Encoding of APB_DATA_WIDTH configuration parameter value. Values: ■ 0x0 (APB_8BITS): APB data width is 8 bits ■ 0x1 (APB_16BITS): APB data width is 16 bits ■ 0x2 (APB_32BITS): APB data width is 32 bits Exists: Always*/
#define UART_APB_DATA_WIDTH            UART_APB_DATA_WIDTH_MSK
#define UART_RSVD_CPR_3TO2_POS         (2U)
#define UART_RSVD_CPR_3TO2_MSK         (0x3UL << UART_RSVD_CPR_3TO2_POS)/*!< CPR 3to2 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_CPR_3TO2             UART_RSVD_CPR_3TO2_MSK
#define UART_AFCE_MODE_POS             (4U)
#define UART_AFCE_MODE_MSK             (0x1UL << UART_AFCE_MODE_POS)/*!< Encoding of AFCE_MODE configuration parameter value. Values: ■ 0x0 (DISABLED): AFCE mode disabled ■ 0x1 (ENABLED): AFCE mode enabled Exists: Always*/
#define UART_AFCE_MODE                 UART_AFCE_MODE_MSK
#define UART_THRE_MODE_POS             (5U)
#define UART_THRE_MODE_MSK             (0x1UL << UART_THRE_MODE_POS)/*!< Encoding of THRE_MODE configuration parameter value. Values: ■ 0x0 (DISABLED): THRE mode disabled ■ 0x1 (ENABLED): THRE mode enabled Exists: Always*/
#define UART_THRE_MODE                 UART_THRE_MODE_MSK
#define UART_SIR_MODE_POS              (6U)
#define UART_SIR_MODE_MSK              (0x1UL << UART_SIR_MODE_POS)/*!< Encoding of SIR_MODE configuration parameter value. Values: ■ 0x0 (DISABLED): SIR mode disabled ■ 0x1 (ENABLED): SIR mode enabled Exists: Always*/
#define UART_SIR_MODE                  UART_SIR_MODE_MSK
#define UART_SIR_LP_MODE_POS           (7U)
#define UART_SIR_LP_MODE_MSK           (0x1UL << UART_SIR_LP_MODE_POS)/*!< Encoding of SIR_LP_MODE configuration parameter value. Values: ■ 0x0 (DISABLED): SIR_LP mode disabled ■ 0x1 (ENABLED): SIR_LP mode enabled Exists: Always*/
#define UART_SIR_LP_MODE               UART_SIR_LP_MODE_MSK
#define UART_ADDITIONAL_FEAT_POS       (8U)
#define UART_ADDITIONAL_FEAT_MSK       (0x1UL << UART_ADDITIONAL_FEAT_POS)/*!< Encoding of ADDITIONAL_FEATURES configuration parameter value. Values: ■ 0x0 (DISABLED): Additional features disabled ■ 0x1 (ENABLED): Additional features enabled Exists: Always*/
#define UART_ADDITIONAL_FEAT           UART_ADDITIONAL_FEAT_MSK
#define UART_FIFO_ACCESS_POS           (9U)
#define UART_FIFO_ACCESS_MSK           (0x1UL << UART_FIFO_ACCESS_POS)/*!< Encoding of FIFO_ACCESS configuration parameter value. Values: ■ 0x0 (DISABLED): FIFO_ACCESS disabled ■ 0x1 (ENABLED): FIFO ACCESS enabled Exists: Always*/
#define UART_FIFO_ACCESS               UART_FIFO_ACCESS_MSK
#define UART_FIFO_STAT_POS             (10U)
#define UART_FIFO_STAT_MSK             (0x1UL << UART_FIFO_STAT_POS)/*!< Encoding of FIFO_STAT configuration parameter value. Values: ■ 0x0 (DISABLED): FIFO_STAT disabled ■ 0x1 (ENABLED): FIFO_STAT enabled Exists: Always*/
#define UART_FIFO_STAT                 UART_FIFO_STAT_MSK
#define UART_SHADOW_POS                (11U)
#define UART_SHADOW_MSK                (0x1UL << UART_SHADOW_POS)/*!< Encoding of SHADOW configuration parameter value. Values: ■ 0x0 (DISABLED): SHADOW disabled ■ 0x1 (ENABLED): SHADOW enabled Exists: Always*/
#define UART_SHADOW                    UART_SHADOW_MSK
#define UART_UART_ADD_ENCODED_PARAMS_POS (12U)
#define UART_UART_ADD_ENCODED_PARAMS_MSK (0x1UL << UART_UART_ADD_ENCODED_PARAMS_POS)/*!< Encoding of UART_ADD_ENCODED_PARAMS configuration parameter value. Values: ■ 0x0 (DISABLED): UART_ADD_ENCODED_PARAMS disabled ■ 0x1 (ENABLED): UART_ADD_ENCODED_PARAMS enabled Exists: Always*/
#define UART_UART_ADD_ENCODED_PARAMS  UART_UART_ADD_ENCODED_PARAMS_MSK
#define UART_DMA_EXTRA_POS             (13U)
#define UART_DMA_EXTRA_MSK             (0x1UL << UART_DMA_EXTRA_POS)/*!< Encoding of DMA_EXTRA configuration parameter value. Values: ■ 0x0 (DISABLED): DMA_EXTRA disabled ■ 0x1 (ENABLED): DMA_EXTRA enabled Exists: Always*/
#define UART_DMA_EXTRA                 UART_DMA_EXTRA_MSK
#define UART_RSVD_CPR_15TO14_POS       (14U)
#define UART_RSVD_CPR_15TO14_MSK       (0x3UL << UART_RSVD_CPR_15TO14_POS)/*!< CPR 15to14 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_CPR_15TO14           UART_RSVD_CPR_15TO14_MSK
#define UART_FIFO_MODE_POS             (16U)
#define UART_FIFO_MODE_MSK             (0xffUL << UART_FIFO_MODE_POS)/*!< Encoding of FIFO_MODE configuration parameter value. Values: ■ 0x0 (FIFO_MODE_0): FIFO mode is 0 ■ 0x1 (FIFO_MODE_16): FIFO mode is 16 ■ 0x2 (FIFO_MODE_32): FIFO mode is 32 ■ 0x4 (FIFO_MODE_64): FIFO mode is 64 ■ 0x8 (FIFO_MODE_128): FIFO mode is 128 ■ 0x10 (FIFO_MODE_256): FIFO mode is 256 ■ 0x20 (FIFO_MODE_512): FIFO mode is 512 ■ 0x40 (FIFO_MODE_1024): FIFO mode is 1024 ■ 0x80 (FIFO_MODE_2048): FIFO mode is 2048 Exists: Always*/
#define UART_FIFO_MODE                 UART_FIFO_MODE_MSK
#define UART_RSVD_CPR_31TO24_POS       (24U)
#define UART_RSVD_CPR_31TO24_MSK       (0xffUL << UART_RSVD_CPR_31TO24_POS)/*!< CPR 31to24 Reserved bits read as 0. Exists: Always*/
#define UART_RSVD_CPR_31TO24           UART_RSVD_CPR_31TO24_MSK


//UCV offsetaddress : 0xf8
#define UART_UART_COMPONENT_VERSION_POS (0U)
#define UART_UART_COMPONENT_VERSION_MSK (0xffffffffUL << UART_UART_COMPONENT_VERSION_POS)/*!< ASCII value for each number in the version, followed by *. For example 32_30_31_2A represents the version 2.01* Exists: Always*/
#define UART_UART_COMPONENT_VERSION    UART_UART_COMPONENT_VERSION_MSK


//CTR offsetaddress : 0xfc
#define UART_PERIPHERAL_ID_POS         (0U)
#define UART_PERIPHERAL_ID_MSK         (0xffffffffUL << UART_PERIPHERAL_ID_POS)/*!< This register contains the peripherals identification code. Reset Value: 0x44570110 Exists: Always*/
#define UART_PERIPHERAL_ID             UART_PERIPHERAL_ID_MSK


typedef struct {
    volatile uint32_t RBR_DLL_THR         ;//offsetaddress : 0x0
    volatile uint32_t DLH_IER             ;//offsetaddress : 0x4
    volatile uint32_t FCR_IIR             ;//offsetaddress : 0x8
    volatile uint32_t LCR                 ;//offsetaddress : 0xc
    volatile uint32_t MCR                 ;//offsetaddress : 0x10
    volatile uint32_t LSR                 ;//offsetaddress : 0x14
    volatile uint32_t MSR                 ;//offsetaddress : 0x18
    volatile uint32_t SCR                 ;//offsetaddress : 0x1c
    volatile uint32_t LPDLL               ;//offsetaddress : 0x20
    volatile uint32_t LPDLH               ;//offsetaddress : 0x24
    volatile uint32_t rev_1[(0x0030 - 0x0024) / 4 - 1];
    volatile uint32_t SRBR_STHR[16]; // offsetaddress : 0x30 - 0x6c
    volatile uint32_t FAR                 ;//offsetaddress : 0x70
    volatile uint32_t TFR                 ;//offsetaddress : 0x74
    volatile uint32_t RFW                 ;//offsetaddress : 0x78
    volatile uint32_t USR                 ;//offsetaddress : 0x7c
    volatile uint32_t TFL                 ;//offsetaddress : 0x80
    volatile uint32_t RFL                 ;//offsetaddress : 0x84
    volatile uint32_t SRR                 ;//offsetaddress : 0x88
    volatile uint32_t SRTS                ;//offsetaddress : 0x8c
    volatile uint32_t SBCR                ;//offsetaddress : 0x90
    volatile uint32_t SDMAM               ;//offsetaddress : 0x94
    volatile uint32_t SFE                 ;//offsetaddress : 0x98
    volatile uint32_t SRT                 ;//offsetaddress : 0x9c
    volatile uint32_t STET                ;//offsetaddress : 0xa0
    volatile uint32_t HTX                 ;//offsetaddress : 0xa4
    volatile uint32_t DMASA               ;//offsetaddress : 0xa8
    volatile uint32_t TCR                 ;//offsetaddress : 0xac
    volatile uint32_t DE_EN               ;//offsetaddress : 0xb0
    volatile uint32_t RE_EN               ;//offsetaddress : 0xb4
    volatile uint32_t DET                 ;//offsetaddress : 0xb8
    volatile uint32_t TAT                 ;//offsetaddress : 0xbc
    volatile uint32_t DLF                 ;//offsetaddress : 0xc0
    volatile uint32_t RAR                 ;//offsetaddress : 0xc4
    volatile uint32_t TAR                 ;//offsetaddress : 0xc8
    volatile uint32_t LCR_EXT             ;//offsetaddress : 0xcc
    volatile uint32_t  rev_2[(0x00f4 - 0x00cc) / 4 - 1];
    volatile uint32_t UART_CPR            ;//offsetaddress : 0xf4
    volatile uint32_t UCV                 ;//offsetaddress : 0xf8
    volatile uint32_t CTR                 ;//offsetaddress : 0xfc
} uart_reg_t ;
#ifdef __cplusplus
}
#endif
#endif

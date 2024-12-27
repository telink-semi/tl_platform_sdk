@page UART_Example UART


# Introduction

UART is an asynchronous full-duplex serial communication protocol consisting of two data lines, Tx and Rx. Since there is no clock reference signal, the two communicating parties using UART must agree on configuration parameters such as serial port baud rate, data bit width, parity bit, stop bit, and so on. Therefore they can communicate at the same rate.

Usually, asynchronous communication takes one character as the transmission unit, and the time interval between two characters in communication is not fixed, but the time interval between two adjacent bits in the same character is fixed. When the baud rate is 9600 bps, the time interval for transmitting one bit is about 104.16 us, and when the baud rate is 115200 bps, the time interval for transmitting one bit is about 8 us.

The data transmission rate is expressed in terms of baud rate, which is the number of binary bits transmitted per second. Each character consists of 11 bits (1 start bit, 8 data bits, 1 parity bit, and 1 end bit). For example, if the data transmission rate is 120 characters per second, the baud rate is 11 x 120 = 1320 characters per second = 1320 baud.

# Data communication timing

![Data communication timing](pic/datacommunicationtiming.png "Data communication timing")

The meaning of each bit is as follows:

Start bit: A logical "0" is issued first to indicate the start of the transmitted character.

Data bits: can be 5-8 bits of logic "0" or "1", such as ASCII code (7 bits), extended BCD code (8 bits), the transmission method is small-end transmission, that is, LSB first, MSB second.

Parity bit: The data bit is added with this parity to make the number of "1" bit even (even parity) or odd (odd parity).

Stop bit: it is a character data end flag, can be 1 bit, 1.5 bits, 2 bits high-level (used to synchronize both ends, the longer the stop bit time, the more fault tolerance).

Idle bit: in the state of logic "1", indicating that there is no data transmission on the current line.

![Asynchronous communication timing](pic/asynchronouscommunicationtiming.png "Asynchronous communication timing")

As shown above, it is worth noting that asynchronous communication is transmitted by character, and the receiving device receives the start signal correctly as long as it is synchronized with the transmitting device for the transmission time of one character. After the next character start bit arrives it needs to be synchronized and recalibrated again (relying on the detection of the start bit to achieve self-synchronization of the clocks of the sender and receiver).

# Communication principle

![UART communication principle](pic/uartcommunicationprinciple.png "UART communication principle")

Take the UART module in Telink SoC as an example, the data to be sent is first written to the TX buffer by the MCU or DMA of the chip, and then the UART module sends the data in the TX buffer to other devices through the TX pin. In the receiving device, the data is first written to the RX buffer through the RX pin of the UART module, and then the data is read by the MCU or DMA of the receiving device.

If the chip's RX buffer is close to overflowing, the chip will send a signal (either configured high or low) to its connected device via its RTS pin, indicating that the device should stop sending data. Similarly, if the chip receives a signal via its CTS pin that the RX buffer of another device is close to overflowing, the chip should stop sending data.

# Function introduction

## Initialization

The caveats are as follows:

(1) Whenever you use UART port, it is better to call uart_reset() function to reset first, so that the effect of the previous operation of using UART can be avoided on this use. (for example, UART related register legacy setting)

    ```C
    uart_reset(uart_num_e uart_num)
    ```

(2) Use uart_set_pin() to set TX/RX pins in UART

    ```C
    uart_set_pin(uart_tx_pin_e tx_pin,uart_rx_pin_e rx_pin)
    ```

    **Wiring Note:** The TX/RX of the current device is connected to the TX/RX of other devices with the rule TX-RX, RX-TX.

(3) In DMA mode, pay attention to choose the DMA channels that are not occupied by other modules

(4) In NDMA mode, if using interrupts, the following configuration are needed:

    (a) uart_rx_irq_trig_level(): it is used to set the number of interrupt triggering level for receiving characters. If set to 1, it will enter interrupt once for receiving one character. (Recommended setting is 1)

    (b) uart_tx_irq_trig_level(): it is used to set the interrupt trigger level for sending characters. When the number of characters in the sending buffer reaches this level, it will enter the sending interrupt. A setting of 0 indicates that there is data in the buffer to send.

**Note:**

> - When NDMA mode is used to receive data using interrupts, it is recommended to set level=1 during initialization (more general) for the following reasons:
       (1) When receiving data in NDMA mode, you can manually set the receive data interrupt level during initialization, the level value can be 1-4. We set the level to 1 by default. If the level is set to 2, 3, 4, the length of the received data needs to meet certain conditions to complete the data reception normally. For example, if the level is set to 2, and the actual length of received data is a multiple of 2, the data can be received normally. But if the actual received data length is not a multiple of 2, such as 3, the first two data can be received normally, but the third data will be lost. (NDMA mode takes data from buffer according to the length of level, if the last time to obatin data, the length can not reach this level, the data will not be taken out). The situation of level setting as 3 and 4 is similar, it needs to receive data length of times of 3, 4, in order to complete the data reception normally.
       (2) When level is set to 1, it should be noted that: because the receive interrupt is triggered too frequently, if the receiving data is too fast (baud rate is too high), it may appear that the next data has arrived before the previous one is not fully received. If this situation occurs, it can be solved by appropriately reducing the baud rate.

## Baud rate

### Function calls

Two functions are used to calculate the baud rate:

(1) uart_cal_div_and_bwpc() function will calculate the optimal clock division number div and bit width bwpc based on the input baud rate and system clock.

    ```C
    uart_cal_div_and_bwpc(unsigned int baudrate, unsigned int sysclk, unsigned short* div, unsigned char *bwpc)
    ```

(2) uart_init() passes the above calculated clock division div and bit width bwpc into the function to really set the baud rate, while the function also sets the UART port, the stop bit, parity bit, and so on.

    ```C
    uart_init(uart_num_e uart_num, unsigned short div, unsigned char bwpc, uart_parity_e parity, uart_stop_bit_e stop_bit)
    ```

There are some applications with high timing requirements, you can calculate the clock division number div and bit width bwpc first, and then call uart_init directly, which saves the execution time of uart_cal_div_and_bwpc function.

### Tested data

We tested the effect of different baud rates on data transfer accuracy in DMA and NDMA modes, respectively.

Test data: 0x00, 0x11, 0x22 ...... 0xff, 16 data in total.

Test conditions: two B91 development board TX/RX interconnected, communication every one second (experiments show that the phenomenon of no time interval and with time interval consistent, here for more stable phenomenon, we use 1s time interval), clock settings of 16MHZ-PCLK, 16MHZ-HCLK, 16MHZ-CCLK.

Test chip: B91 80pin-EVK

Test program: UART-DEMO.

**NDMA mode:**

|Baud rate |Receive| Send |
|:---------|:--------|:-------|
|2000000 |  Fail | Fail |
|1500000 |  Pass | Pass |
|1000000 |  Pass | Pass |
|500000  |  Pass | Pass |
|256000  |  Pass | Pass |
|115200  |  Pass | Pass |
|57600   |  Pass | Pass |
|38400   |  Pass | Pass |
|19200   |  Pass | Pass |
|9600    |  Pass | Pass |
|4800    |  Pass | Pass |
|2400    |  Pass | Pass |
|1200    |  Pass | Pass |
|600     |  Pass | Pass |
|300     |  Pass | Pass |

**DMA mode:**

|Baud rate |Receive| Send |
|:---------|:--------|:-------|
|2000000 |  Pass | Pass |
|1500000 |  Pass | Pass |
|1000000 |  Pass | Pass |
|500000  |  Pass | Pass |
|256000  |  Pass | Pass |
|115200  |  Pass | Pass |
|57600   |  Pass | Pass |
|38400   |  Pass | Pass |
|19200   |  Pass | Pass |
|9600    |  Pass | Pass |
|4800    |  Pass | Pass |
|2400    |  Pass | Pass |
|1200    |  Pass | Pass |
|600     |  Pass | Pass |
|300     |  Pass | Pass |

From the test, it can be seen that from 300bps to 1.5Mbps baud rate, it can communicate normally in both NDMA and DMA mode. At 2Mbps baud rate, in DMA mode it can still communicate normally, but in NDMA mode it has shown an error (sent and received garbled data).

**Note:**

> - Further tests show that the DMA limit baud rate can reach 5Mbps at 16MHZ-PCLK.
> - When PCLK is raised to 24MHZ, HCLK and CCLK are raised to 48MHZ, NDMA mode limit baud rate can reach 5Mbps, DMA limit baud rate can reach 8Mbps, PCLK is the main influencing factor of UART baud rate limit.

## Interrupt

--------------------------------------------------------------------------------------------------------------------------------------------
Interrupt                   Generation condition                                                Automatic or manual clearing 
--------------------------- ------------------------------------------------------------------- --------------------------------------------
TX DMA TC 					Interrupts are generated every time a frame of data is received		It needs to be cleared manually.

UART_TXDONE 				Shared by NDMA and DMA. The default value is 1. It will be set to 	It needs to be cleared manually.
							0 when it starts to send data and will be automatically set to 1 
							by the hardware when the data transmission is finished.

UART_RXDONE (need to check 	This interrupt can only be used in DMA mode, the default value is 	It needs to be cleared manually.
the chip difference if it 	0, and will be set to 1 after receiving a packet of data.
can be used)

UART_RXBUF_ IRQ_STATUS		When the amount of data in the receiving BUFF buffer reaches the 	This flag bit is cleared automatically when 
							level set during initialization, an interrupt is generated.			the buffer data is read.

UART_TXBUF_ IRQ_STATUS		When the amount of data in the transmitting BUFF buffer reaches 	This flag bit is cleared automatically when 
							the level set during initialization, an interrupt is generated.		the buffer data is sent out.

UART_RX_ERR (need to check 	UART receive error flag. When the UART receives data with error    	This flag bit needs to be cleared manually.
the chip difference if it 	(such as parity error or stop bit error), an interrupt will be
can be used)				generated, and the data reception will be stopped after the
							interrupt.
--------------------------------------------------------------------------------------------------------------------------------------------

## DMA mode

### Sending data

Using this function to send data, the function only triggers the send action, and does not actually send all data, you need to use a query or interrupt to determine whether it sent all data.

```C
unsigned char uart_send_dma(uart_num_e uart_num,unsigned char * addr,unsigned char len)
```

**Query**

```C
uart_send_dma(UART0, (unsigned char*)tx_byte_buff, 16);
while(uart_tx_is_busy(UART0));
```

You need to use uart_tx_is_busy interface to query the current status, if this flag bit is 0, it indicates that the last frame data transmission is finished and you can enter into the current frame data transmission.

**Interrupt**

To use the TX_DONE interrupt, you need to set the corresponding mask:

```C
uart_set_irq_mask(UART0, UART_TXDONE_MASK);
```

In addition to the normal use of interrupt-related function calls, the following matters need to be noted:

When initializing, the following function needs to be called (to set the TX_DONE signal to 0, otherwise it will keep going into interruptions):

```C
uart_clr_tx_done(UART0);
```

The interrupt handler function needs to be handled in the following manner:

```C
_attribute_ram_code_sec_noinline_ void uart0_irq_handler(void)
{
     if(uart_get_irq_status(UART0,UART_TXDONE))//judge the interrupt flag bit
     {
         .........
         uart_clr_tx_done(UART0); //set TX_DONE signal to 0
     }
 }
```

Flag bit: UART_TXDONE

When using the interrupt method, the UART_TXDONE interrupt is generated to indicate that the previous frame of data transmission is finished and can move to the next frame of data transmission.

**Note:**

> - When DMA mode uses interrupt method to send data, we need to use the status of UART_TXDONE. Since the initial default value of UART_TXDONE is 1, in order to generate interrupt normally, we use uart_clr_tx_done(UART0) function to set UART_TXDONE to 0 during initialization, so that when the sending is finished UART_TXDONE will be set to 1 automatically, then enter UART_TXDONE interrupt, then use uart_clr_tx_done(UART0) function to pull down UART_TXDONE again in the interrupt handler program.

### Receiving data

When using DMA to receive data, the initialization has a packet reception end judgment rx_timeout.

```C
uart_set_dma_rx_timeout(uart_num_e uart_num, unsigned char bwpc, unsigned char bit_cnt, uart_timeout_mul_e mul)
```

Where bwpc and bit_cnt set the time used to transmit a byte, and the time required to transmit a byte is (bwpc+1)\*bit_cnt. We use mul to set the timeout time, which can be set to 0, 1, 2, or 3. The mul set to 0 means that if no data is received for more than 1 byte, the packet receiving is considered to be finished. The mul set to 1 means that if no data is received for more than 2 bytes, the packet receiving is considered to be finished.

There are two ways to receive data using DMA mode:

(1) RX_DONE interrupt

    Using RX_DONE interrupt to receive data is a more general way, this way allows us to receive packets of unknown length, but some chips do not support this way. Please check the chip difference chapter of UART if the chip supports this way.

(2) DMA interrupt

    If the chip does not support the RX_DONE interrupt, you can use the DMA interrupt to receive data. However, this method has a usage limitation and can only receive packets of known length.

**RX_DONE interrupt**

To use RX_DONE interrupt, you need to set the corresponding mask.

```C
uart_set_irq_mask(UART0, UART_RXDONE_MASK);
```

Flag bit: UART_RXDONE

When data is received using the interrupt method, the RX_DONE interrupt is generated to indicate that data has been received, and this flag bit needs to be cleared manually.

**Note:**

> - When using the DMA-RX_DONE interrupt, the interrupt handler function has the calculation of the received data length rec_data_len, so that we can clearly know the received data length when using the RX_DONE method to receive data.

**DMA interrupt**

With the interrupt flag bit DMA_TC_IRQ, this flag bit needs to be cleared manually when there is an interrupt request, indicating that data has been received.

```C
void uart_receive_dma(uart_num_e uart_num, unsigned char * addr,unsigned char rev_size)
```

**Note:**

> - The length of the data must be known in order to generate an interrupt. The parameter rev_size needs to meet a certain relationship with the actual length of the received data, len, so that no data will be missed and the interrupt will be generated accurately. (For example, if 4*(n-1)<len≤4*n, then rev_size needs to meet 4*(n-1)<rev_size≤4*n, where n is the same value). (For example: rev_size is set to 8, the received data length is 5/6/7/8 to generate an interrupt).

**Attentions:**

(1) The size of the rec_buff receiving array should be reserved for more areas. The reason is: DMA transfers data in a unit of 4byte, for example, the actual length of the received data is 5, rev_size can be set to 5 - 8, DMA will transfer data twice, although the second transfer only left one valid data, DMA will still transfer 4 data, the last three of which are useless data.

(2) The length len of the received data meets a certain relationship, for example, when 4*(n-1)<len≤4*n, the rec_buff size is set to greater than or equal to 4n. This way the first len data of the rec_buff is valid data, and the later ones are invalid data, which we need to distinguish accurately.

(3) When actually using DMA to receive data, it is better to set rec_buff=rev_size=4n when the received data length len is at 4*(n-1)<len≤4*n.

Example: rec_buff length is set to 8, rev_size is set to 8, and 4, 5, 6, 7, 8 data are sent to compare.

The program sets the DMA to receive mode and initializes rec_buff to all 0. Check the rec_buff value by BDT.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Sending data                  Receiving data                                    Whether the interrupt is generated   Number of invalid data    DMA transferring times
----------------------------- ------------------------------------------------- ------------------------------------ ------------------------- -----------------------
0x11, 0x22, 0x33, 0x44        0x11, 0x22, 0x33, 0x44                            No                                   0                         1

0x11, 0x22, 0x33, 0x44,       0x11, 0x22, 0x33, 0x44, 0x55, 0xXX, 0xXX, 0xXX    Yes                                  3                         2
0x55

0x11, 0x22, 0x33, 0x44,       0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0xXX, 0xXX    Yes                                  2                         2
0x55, 0x66

0x11, 0x22, 0x33, 0x44,       0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0xXX    Yes                                  1                         2
0x55, 0x66, 0x77

0x11, 0x22, 0x33, 0x44,       0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88    Yes                                  0                         2
0x55, 0x66, 0x77, 0x88

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Note:**

> - 0xXX means invalid data value, usually displayed as garbled code

## NDMA mode

### Sending data

```C
void uart_send_byte(uart_num_e uart_num, unsigned char tx_data)
```

**Note:**

> - NDMA mode also provides us to send data as hword (2byte) and word (4byte). It should be noted that when sending data, the low byte data is sent first, then the high byte data is sent. For example, if a string of data is 0x11223344, if we want to receive data at the receiver end, the order of sending data in hword form is 0x2211, 0x4433, and in word form is 0x44332211.

**Query**

```C
uart_send_byte(UART0, uart0_tx_buff_byte[i]);
while(uart_tx_is_busy(UART0));
```

You need to use uart_tx_is_busy interface to query the current status, if this flag bit is 0, it indicates that the last frame data transmission is finished and you can enter into the current frame data transmission.

**Interrupt**

Flag bit: UART_TXBUF_IRQ_STATUS

In the initialization, the interrupt trigger number level of TX is set by uart_tx_irq_trig_level(), when the send buffer data reaches this level, the sending will start. At this time it will enter the sending interrupt.

**Note:**

> - The DEMO gives the TX interrupt trigger level as 0, that is, the buffer has data to send. At this time, if we use TX interrupt, the program will be in TX interrupt state all the time, which is not good for practical use. Therefore, the DEMO does not give the judgment and processing of TX interrupt, so that it is more in line with our actual use habits (send directly if there is a demand for sending), if you really need to judge the sending status, it is recommended to use the query method.

### Receiving data

```C
unsigned char uart_read_byte(uart_num_e uart_num)
```

Flag bit: UART_RXBUF_IRQ_STATUS

In the initialization, the trigger number level of receiving interrupts is set. When the number of received characters reaches the level, the flag bit will be set to 1, and then the interrupt will be entered and the buffer data will be moved to our pre-defined receive array.

## Flow Control

Because of the difference in processing speed between the two sides of the UART, there is a large gap between the receiving rate and the sending rate when data is transmitted, so that the receiving end may not be able to receive the data in time during the process of sending and receiving. In order to prevent data loss, it is necessary for the sender to control, which is called flow control.

CTS (clear to send) allows sending

RTS (request to send) request to send

If UART0 is communicating with UART1, the RTS pin of UART0 is connected to the CTS pin of UART1, and the CTS pin of UART0 is connected to the RTS pin of UART1.

### CTS

```C
uart_cts_config(uart_num_e uart_num,uart_cts_pin_e cts_pin,u8 cts_parity)
```

The uart_cts_config() function is used to configure the port number to use CTS flow control with the CTS pin. When the input level of CTS pin is equal to cts_parity, UART will stop transmitting.

### RTS

```C
uart_rts_config(uart_num_e uart_num,uart_rts_pin_e rts_pin,u8 rts_parity,u8 auto_mode_en)
uart_rts_trig_level_auto_mode(uart_num_e uart_num,u8 level)
```

The uart_rts_config() function is used to configure the UART port number, RTS pin.

The rts_parity is valid only in auto mode, it indicates the jump direction of the RTS pin when the received data amount reaches the level value, the level jumps from low to high when it is 1, and from high to low when it is 0.

**Note:**

> - RTS has two modes to choose when configuring, UART_RTS_MODE_AUTO/UART_RTS_MODE_MANUAL which are Auto mode and Manual mode. In auto mode, the RTS pin automatically performs the RTS_INVERT related jumps when receiving RTS-THRESH data. In manual mode, we need to calculate the received data length, and when the data length reaches the expected value, we need to pull down or pull up the RTS pin manually using the uart_set_rts_level() function.

The uart_rts_trig_level_auto_mode() function is the RTS jump trigger setting, level indicates the trigger threshold, if set to 5, the RTS pin will be jumped upon receiving 5 data.

# DEMO introduction

You can choose to configure the UART working mode (DMA and NDMA) in the header UART_DEMO/app_config.h, as shown below, corresponding to the contents in app_dma.c and app.c respectively.

```C
#define UART_DMA      1 //uart use dma
#define UART_NDMA     2 //uart not use dma
#define UART_MODE     2
```

Among them, you can specifically select flow control mode in NDMA and DMA mode as follows

```C
#define BASE_TX      0 //just for NDMA
#define NORMAL       1
#define USE_CTS      2
#define USE_RTS      3
#define FLOW_CTR     1
```

## DMA Mode

The UART module keeps sending the received data via DMA, and the initial rec_buff[] is all 0.

Verification via serial port tool is as below:

![DMA serial port verification](pic/dmaserialportverification.png "DMA serial port verification")

## NDMA Mode

When the number of received characters reaches the preset acceptance length (which is UART0_RX_IRQ_LEN), uart0_rx_flag will be 1, and then the interrupt service program will process the received characters and send them out.

Verification via serial port tool is as below:

![NDMA serial port verification](pic/ndmaserialportverification.png "NDMA serial port verification")

## RTS and CTS

Take NDMA as an example, due to hardware constraints, only a single demonstration of RTS or CTS is available.

CTS: Set STOP_VOLT=1, which means stop sending TX when in high level.

When the CTS pin is 0, continuous transmission, using the serial port tool to view:

![CTS pins is 0](pic/ctspinsis0.png "CTS pins is 0")

Set CTS high to stop transmitting.

RTS: In auto mode, set RTS_THRESH=5,RTS_INVERT=1, which means the RTS pin jumps from low to high when 5 data are received cumulatively.

To make the phenomenon more significant, the logic analyzer was used to view the jump results.

Use the serial port tool to send 4 data:

![Sending 4 data using the serial port tool](pic/sending4datausingtheserialporttool.png "Sending 4 data using the serial port tool")

RTS jump did not occur.

Send 5 data:

![Sending 5 data using the serial port tool](pic/sending5datausingtheserialporttool.png "Sending 5 data using the serial port tool")

The RTS pin completes the jump from low to high.

![Level jump](pic/leveljump.png "Level jump")

**Note:**

> - When actually using the flow control of UART, we need to pay attention to the reasonable configuration of CTS and RTS jumping method. For example, if the RTS pin of one device is set to jump from low to high when triggered, then the CTS pin of the other device connected to it needs to be set to high to stop transmitting. Thereafter, the UART flow control can work properly.

# Chip Differences

## UART_RXDONE interrupt

The use of this interrupt is supported in order to effectively determine the end of a packet (even if the length of the packet is unknown).

| Chip |DMA mode RX_DONE interrupt|
|------|--------------------------|
|B91 A0|     Not supported        |
|Other |     Supported            |

## UART_RX_ERR interrupt

**B91 A0 chip:**

(1) DMA mode: UART_RX_ERR interrupt is not available. (Reason: Hardware detects this interrupt and clears it automatically, software does not detect it.)

(2) NDMA mode: UART_RX_ERR interrupt can be used.

Recommended usage: clear interrupt status, clear RX-FIFO, zero in on hardware pointer and software pointer.

Reason: when receiving errors, there may be wrong data in the FIFO, in order not to affect the subsequent reception of correct data, the RX-FIFO needs to be cleared (that means the pointer is zeroed, uart_reset() makes the hardware pointer zeroed, while the software pointer is kept consistent also needs to be cleared).

Summarize: after the UART_RX_ERR interrupt is detected in this mode, the following actions need to be performed:

```C
uart_clr_irq_status (UART0,UART_CLR_RX); //NDMA mode will clear RX-FIFO and RX_ERR_IRQ, RX_BUFF_IRQ (Note: if it enters RX_ERR interrupt, it means there is an error in receiving data, clearing RX will clear RX_BUFF interrupt at the same time)
uart_reset()；//clear to zero on hardware pointer
uart_clr_rx_index();//clear to zero on the software pointer
```

**Other chip:**

(1) DMA mode: UART_RX_ERR interrupt can be used.

Recommended usage: clear interrupt status only.

Reason: DMA mode receiving data occurs error, when enter to RX_DONE interrupt, DMA will finish transferring data in RX-FIFO, FIFO pointer will be zeroed automatically, no need uart_reset(), the error data will not affect the subsequent reception of correct data. (Note: If UART_RX_ERR interrupt occurs, the data in the receive array will be the wrong data and cannot be used.)

Summarize: after the UART_RX_ERR interrupt is detected in this mode, the following actions need to be performed:

```C
uart_clr_irq_status(UART0,UART_CLR_RX); //In DMA mode it will clear RX_FIFO, RX_DONE_IRQ, and RX_ERR status
```

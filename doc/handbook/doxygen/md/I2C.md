@page I2C_Example I2C

# Introduction

I2C, a serial bus consisting of the data SDA and the clock SCL, can send and receive data and is a half-duplex communication method. The clock is controlled by the master end and the I2C communication protocol is as follows:

![I2C communication protocol](pic/i2ccommunicationprotocol.png "I2C communication protocol")

The I2C communication protocol is described in detail as follows:

-------------------------------------------------------------------------------
Status              Process
------------------- ---------------------------------------------------------------
Idle state          When both the SDA and SCL signal of the I2C bus are high at the same time, it is specified as the idle state of the bus.

Start signal        The SDA jumps from high to low during SCL is high.

Stop signal         The SDA jumps from low to high during SCL is high.

Responding signal   The requirement for the feedback valid responding bit ACK is that the receiver pulls the SDA signal low during the low period before the 9th clock pulse and ensures a steady low level during the high period of that clock. If the receiver is the master, it sends a NACK signal after it receives the last byte to notify the controlled transmitter to end data transmission and release the SDA signal so that the master receiver can send a stop signal P.

Validity of data     When the I2C bus is used for data transfer, the data on the data line must remain stable during the period when the clock signal is high. Only during the period when the signal on the clock line is low, the high or low state on the data line is allowed to change. That is, the data needs to be ready before the rising edge of SCL arrives, and must be stable before the falling edge arrives.

Data transfer        Each bit of data transmitted on the I2C bus has a corresponding clock pulse (or synchronization control), that is, each bit of data is transmitted serially on SDA bit by bit in cooperation with the SCL serial clock.

-------------------------------------------------------------------------------

# Interrupt

Interrupt-related introduction in I2C mode is as follows:

**I2C no-DMA mode:**

Related interrupts:

a) I2C_RX_BUF_MASK: Related to rx_irq_trig_lev setting, when fifo_data_cnt>=rx_irq_trig_lev , it generates an interrupt.

b) I2C_RX_DONE_MASK: Generate an interrupt after receiving the sent data.

Whether to clear the interrupt flag bit manually:

I2C_RX_BUF_MASK and I2C_RX_DONE_MASK do not need to clear the interrupt flag bits manually, they will be cleared automatically when the conditions are not met.

**I2C DMA mode:**

Related interrupts:

a) TC_MASK: TC interrupt of DMA will be up when DMA has finished transferring the received data.

b) I2C_TX_DONE_MASK: Generate an interrupt when finished sending data.

Whether to manually clear the interrupt flag bit:

TC_MASK, I2C_TX_DONE_MASK need to clear the interrupt flag bit manually, otherwise it will keep going in and out of interrupts.

**Note:**

> - In non-DMA mode, when the slave end uses interrupts to receive data, the slave end must use both I2C_RX_BUF_MASK and I2C_RX_DONE_MASK to determine the completion of a frame in order to be compatible with all possible data lengths. the reason is as follows:
        (1) I2C_RX_DONE_MASK cannot be captured if the data length is a multiple of trigger level;
        (2) I2C_RX_BUF_MASK is not detected by the tail packet interrupt when the data length is not a multiple of trigger level.
> - In DMA mode, the I2C_RX_DONE_MASK interrupt flag bit is not captured. Use the TC_MASK interrupt of DMA instead.
> - All interrupt MASKs of DMA are turned on by default, you need to turn off other unused MASKs to avoid affecting the results of the experiment.
> - Before using the I2C_TX_DONE_MASK interrupt, you need to clear the I2C_TX_DONE_CLR state manually. If not, it will keep going into the interrupt.
> - I2C_TX_DONE_MASK interrupt does not mean that a frame is sent (it just means that the data part is sent, without waiting for the stop signal), after generating the I2C_TX_DONE_MASK interrupt, then query the BUSY signal until IDLE represents the end.

# I2C mode

The chip supports both as master and as slave. If acting as master, you need to do master initialization and set the clock signal, the interface is as follows:

```C
void i2c_master_init(void);
void i2c_set_master_clk(unsigned char clock);
```

If acting as a slave, the following interface is invoked for initialization, with a unique address (id) for each device:

```C
void i2c_slave_init(unsigned char id).
```

## I2C no-DMA mode

### Master

The relevant interfaces for the master to send and receive data are configured as follows:

```C
unsigned char i2c_master_write(unsigned char id, unsigned char *data, unsigned char len);
unsigned char i2c_master_read(unsigned char id, unsigned char *data, unsigned char len);
```

The functions of i2c_master_write and i2c_master_read are as follows:

In the case that the master reads and writes, and the slave is normally responding (responds with ACK), the result is as follows:

![During master reads and writes, the slave normal responding results](pic/duringmasterreadsandwrites1.png "During master reads and writes, the slave normal responding results")

![During master reads and writes, the slave normal responding results](pic/duringmasterreadsandwrites2.png "During master reads and writes, the slave normal responding results")

After the master sends the address frame, if the slave responds with NACK, the master will send a stop to stop the transmission, and the result is as follows:

![The result of the slave responds with NACK after the master has sent the address frame](pic/afterthemasterhassenttheaddressframe1.png "The result of the slave responds with NACK after the master has sent the address frame")

![The result of the slave responds with NACK after the master has sent the address frame](pic/afterthemasterhassenttheaddressframe2.png "The result of the slave responds with NACK after the master has sent the address frame")

If during the data phase, the slave responds with NAK, the master will still send the remaining data normally. The result is shown as follows:

![During data phase, results of slave responds with NAK](pic/duringdataphase.png "During data phase, results of slave responds with NAK")

**Note:**

> - At present, only MCUmode supports the function of stopping when NACK is detected after sending the address frame, DMA mode does not support it. The DMA mode will send the whole frame of data regardless of whether the slave end responds with NAK or not.

### Slave

The relevant interfaces for the slave to receive and send data are configured as follows:

```C
void i2c_slave_write(unsigned char* data , unsigned char len ).
void i2c_slave_read(unsigned char* data , unsigned char len ).
```

Slave end receiving data: you can use interrupts to enable the rx (I2C_RX_BUF_MASK) interrupt and rx_done (I2C_RX_DONE_MASK) interrupt when in non-DMA mode to determine if a frame of data has been received.

The specific configuration of interrupts on the Slave end is as follows:

```C
i2c_set_irq_mask(FLD_I2C_MASK_RX|FLD_I2C_MASK_RX_DONE);
i2c_rx_irq_trig_cnt(SLAVE_RX_IRQ_TRIG_LEVEL);
core_interrupt_enable();
plic_interrupt_enable(IRQ21_I2C);
```

**Note:**

> - Current problem: When I2C is used as a slave, the software cannot distinguish whether the master sends a read or a write command. The Slave end does not know whether to read or write, so the slave needs to write the data to the FIFO in advance before the maste end sends the read command. However, from the application point of view, it is difficult to control the time of writing data in advance because we don't know when the master end will read the data.  
    This can lead to the following problem: In non-DMA mode, the slave end needs to put the sent data in the fifo in advance before the master sends the read command. The size of the fifo is only 8 bytes, and if the master does not read it away, it will be stuck in the i2c_slave_write function, so to use this function, you need to control the timing at the software level.

## I2C DMA mode

### Master

The relevant interfaces for the master to send and receive data are configured as follows:

```C
void i2c_master_write_dma(unsigned char id, unsigned char *data, unsigned char len);
void i2c_master_read_dma(unsigned char id, unsigned char *rx_data, unsigned char len);
```

The relevant interfaces used to determine whether the master end has finished sending and receiving data are as follows:

```C
static inline bool i2c_master_busy(void).
```

**Note:**

> - TX_DONE interrupt does not mean that a frame is sent (it just means that the data part is sent, without waiting for the stop signal), after generating the TX_DONE interrupt, then querying the busy signal until idle represents the end.

### Slave

The relevant interfaces for the slave to send and receive data are configured as follows:

```C
void i2c_slave_read_dma(unsigned char *data, unsigned char len);
void i2c_slave_write_dma(unsigned char *data, unsigned char len);
```

The DMA TC_MASK needs to be configured for receiving interrupts on the slave end, as follows:

```C
i2c_clr_txdone_irq_status (I2C_TX_DONE_CLR);
i2c_set_irq_mask(I2C_TX_DONE_MASK);
core_interrupt_enable();
plic_interrupt_enable(IRQ21_I2C);
```

To send interrupts on the slave end, you need to configure I2C_TX_DONE_MASK, as follows:

```C
dma_set_irq_mask(I2C_RX_DMA_CHN, TC_MASK);
```

**Note:**

> - The master end sends a read command to the slave end, and the slave end needs to use i2c_slave_write_dma before the master end sends a read command.
> - The function puts the sent data in the DMA in advance. (Note, you need to ensure that this fill is the data that needs to be responded, because after calling this function, the DMA will put the specified buffer data in the fifo, and wait for the master's clock to come to read the data out.)

# I2C demo description

Choose which mode to use via the macros I2C_MASTER_WRITE_READ_MODE in app.c and app_dma.c.

```C
#define I2C_MASTER_WRITE_READ_NO_DMA            1

#define I2C_MASTER_WRITE_READ_DMA               2

#define I2C_MASTER_WRITE_READ_MODE              I2C_MASTER_WRITE_READ_NO_DMA
```

Select master and slave mode via macro I2C_DEVICE.

```C
#define I2C_MASTER_DEVICE             1

#define I2C_SLAVE_DEVICE              2

#define I2C_DEVICE                    I2C_MASTER_WRITE_READ_NO_DMA
```

**Note：**

> When testing I2C communication through two boards, when the code of the master end and the salve end are burned to the board, after both boards are powered off, power on the slave end first, and then the master (to avoid data errors), and there is a common ground between the two boards.

## Function description

|   Node     |   Function description                                                   |
|------------|-----------------------------------------------------------------|
| master     | Keep sending write operations, read operations, and then compare the sent data with the read data, if the comparison result differs, LED2 status will change.  |
| slave      | Return the received data to the master. |

## Example results

Using a logic analyzer to capture the timing sequence of the I2C sent data and received data, the following results were executed:

Channel 0: represents the SCL signal of I2C.

Channel 1: represents the SDA signal of I2C.

Channel 2: LED2 represents the flag bit on the master side to determine whether the sent data and received data are the same, and will be flipped if the compared data is not the same.

Master end sends data:

![Master end is sending data](pic/masterendissendingdata.png "Master end is sending data")

Master end receives data:

![Master end is receiving data](pic/masterendisreceivingdata.png "Master end is receiving data")

**Special notes:**

(1) When i2c writes, the slave will respond with ACK after the master completes writing the last byte, and then the master will send stop signal to end the communication.

(2) When i2c reads, after the master receives the last byte sent by the slave, the slave end sends the NACK signal and releases the SDA signal so that the master receiver can send a stop signal P.

@page RF_Example RF

The RF driver supported transceiver modes include BLE1M, BLE2M, BLE125K, BLE500K, Zigbee250K, Hybee1M, Hybee2M, Hybee500K, Private1M, Private2M, Private250K, Private500K, and ANT mode. Where BLE1M, 2M also contains two modes of turning on PN and turning off PN.

The BLE mode works in standard compliant 1Mbps BLE mode, 2Mbps enhanced BLE mode, 125Kbps BLE remote mode (S8), and 500kbps BLE remote mode (S2). The Zigbee mode works in IEEE 802.15.4 compliant 250Kbps mode.

# Initialization

The RF module initialization is as follows:

```C
rf_mode_init(); //RF initialization
rf_set_ble_1M_mode(); //different modes call different mode initialization, here take BLE_1M mode as an example
rf_set_power_level(RF_POWER); //Set the transmit energy
rf_access_code_comm(ACCESS_CODE);// Zigbee, hybee mode has no access code concept, so this step is not needed
rf_set_tx_dma(0,128);//1 FIFO, each FIFO size is 128bytes
rf_set_rx_dma(rx_packet,RX_FIFO_NUM-1,RX_FIFO_DEP);
rf_set_ble_chn(17);//for BLE open PN 2440MHz
```

If you want to send and receive packets, there are two usage options:

(1) Manual Mode: all the use process for tx and rx are controlled by the software process, for example, set tx mode, wait for stable PLL before sending packets, and so on.

(2) Auto Mode: as long as the corresponding state machine mode is triggered, the subsequent actions are automatically controlled by the hardware and do not require software control.

# Energy setting

Currently there are two interfaces to set energy:

```C
void rf_set_power_level (rf_power_level_e level)
```

------------------------------------------------------------------------------------------
Applicable mode   Parameter chn_num
----------------- ------------------------------------------------------------------------
All modes         Set the value of the enumeration variable corresponding to the energy.

------------------------------------------------------------------------------------------

```C
void rf_set_power_level_index (rf_power_level_index_e idx)
```

------------------------------------------------------------------------------------------
Applicable mode   Parameter chn
----------------- ------------------------------------------------------------------------
All modes         The passed in index value of the enumeration variable in the corresponding array for the energy.

------------------------------------------------------------------------------------------

**Note:**

> - The only difference between the two is the inconsistency in the way the parameters are passed, and in the application you can choose whichever to use as needed.

# Frequency setting

Currently there are two interfaces to set the frequency point:

```C
void rf_set_ble_chn(signed char chn_num)
```

|Applicable mode|Parameter chn_num|
|:-----------------------------------|:-------------------------------------------------------|
|ble_1M, ble_2M, ble_250K, ble_500K|The actual frequency point is set to (chn_num+2400) MHz|

```C
void rf_set_chn(signed char chn)//all modes can be used
```

------------------------------------------------------------------------------------------
Applicable mode   Parameter chn
----------------- ------------------------------------------------------------------------
All modes         The index value of the frequency point is passed in. It is set to the corresponding frequency point by the transformation of index, and the index relationship is as follows.

------------------------------------------------------------------------------------------

The correspondence between the rf_set_ble_chn function parameter chn_num and the frequency points is shown in the following table.

|Corresponding frequency point (MHz)|chn_num|
|:--------:|:--------:|
|2402|37|
|2404|0|
|2406|1|
|2408|2|
|2410|3|
|2412|4|
|2414|5|
|2416|6|
|2418|7|
|2420|8|
|2422|9|
|2424|10|
|2426|38|
|2428|11|
|2430|12|
|2432|13|
|2434|14|
|2436|15|
|2438|16|
|2440|17|
|2442|18|
|2444|19|
|2446|20|
|2448|21|
|2450|22|
|2452|23|
|2454|24|
|2456|25|
|2458|26|
|2460|27|
|2462|28|
|2464|29|
|2466|30|
|2468|31|
|2470|32|
|2472|33|
|2474|34|
|2476|35|
|2478|36|
|2480|39|

# Interrupt

All interrupts below need to be cleared manually by the software.

--------------------------------------------------------------------------------------------------------------------
Mode           Related interrupts
-------------- -----------------------------------------------------------------------------------------------------
Auto           **FLD_RF_IRQ_RX_TIMEOU:** If the packet is still not received within the time set from trigger to timeout, an interrupt is generated and the state machine returns to idle state. The timeout time is set by void rf_set_rx_timeout(); and the timeout starts from the trigger RX.

Auto           **FLD_RF_IRQ_CMD_DONE:** After completing a normal packet receiving or sending operation, the state machine returns to the IDLE state normally and generates an interrupt.

Auto           **FLD_RF_IRQ_RX_CRC_2:** BTX,BRX,PTX,PRX will generate interrupt if CRC error is detected twice in a row during packet receiving (continuous packet receiving).

Auto           **FLD_RF_IRQ_FSM_TIMEOUT:** It contains the state machine used for switching from receive to send, specifying the time of the entire state machine, and determining whether the specified time is exceeded in the TX_WAIT state.

Auto           **FLD_RF_IRQ_TX_RETRYCNT:** Generate an interrupt when the number of ptx retry exceeds the set r_max_retry_cnt.

Auto           **FLD_RF_IRQ_TX_DS:** Length of payload (sent by PTX, PRX) ! = 0, generate tx_ds interrupt.

Auto           **FLD_RF_IRQ_RX_DR:** PRX, PTX, SRX received packets detect the packet payload length ! = 0, generate rx_dr interrupt.

Auto           **FLD_RF_IRQ_STX_TIMEOUT:** The STX state does not wait for tx_done in the specified time, thus timeout, generating an interrupt.

Auto           **FLD_RF_IRQ_INVALID_PID:** PTX or PRX receives invalid pid and generates interrupt.

Auto           **FLD_RF_IRQ_FIRST_TIMEOUT:** BRX, PRX, SRX, SRT first RX timeout, when the first packet receive timeout it will generate an interrupt.

Auto           **FLD_RF_IRQ_WIFI_DENY:** After the Bluetooth chip receives the wifi_deny signal from the WiFi chip when it is connected to the WiFi chip, the Bluetooth chip generates an interrupt

Auto/Manual    **FLD_RF_IRQ_RX:** an interrupt is generated after each packet is received.

Auto/Manual    **FLD_RF_IRQ_TX:** an interrupt is generated after each packet is sent.

Auto/Manual    **FLD_RF_IRQ_SUPP_OF:** The interrupt is mainly used for AOA and AOD. If iq sampling frequency is too high the hardware FIFO will overflow error, generate interrupt iq sample and synchronize fifo overflow.

--------------------------------------------------------------------------------------------------------------------

# Packet format

The format of the packet contents of sending and receiving packets in ram differs for each mode. The following describes the format of the packet contents in ram for each mode according to the sending and receiving packets.

The first four bytes of the outgoing packet format in all modes are DMA_LEN_INFO, which can be obtained and filled in by calling the following function:

```C
DMA_LEN_INFO = rf_tx_packet_dma_len (data_len).
```

**Note:**

> - The receiving/sending buffer must be four-byte aligned. For example:
     unsigned char rx_packet[128*4] \_\_attribute\_\_ ((aligned (4)));

## BLE packet format

### BLE packet sending format

The format of the packet sending in RAM is shown below (where payload length is the data length and data is the data to be sent):

**BLE TX Packet:**

--------------------------------------------------------------------------------------------------------------------
Address                               Content
------------------------------------- ------------------------------------------------------------------------------
addr, addr + 1, addr + 2, addr + 3    DMA_LEN_INFO <br>rf_tx_packet_dma_len(payload length+2).

addr + 4                              header0

addr + 5                              header (payload length)

addr + 6                              data(0)

addr + 7                              data(1)

addr + 8                              data(1)

.....                                 .....

addr +6+(length-1)                    data(length-1)

--------------------------------------------------------------------------------------------------------------------

### BLE packet receiving format

When the SoC is in BLE mode for packet receiving, the received packet data is stored in ram in the following format:

**BLE packet receiving format:**

--------------------------------------------------------------------------------------------------------------------
Address                       Content                                                  Description
----------------------------- -------------------------------------------------------- -----------------------------
rba-4, rba-3, rba-2, rba-1    -                                                        -

rba                           header0                                                  refer to Bluetooth low energy spec

rba+1                         header1 (payload length)                                 indicate length of payload only, do not include 3 crc bytes

rba+2                         data(0)                                                  payload

rba+3                         data(1)                                                  payload

rba+4                         data(2)                                                  payload

.....                         .....                                                    payload

rba+2+(length-1)              data(length-1)                                           payload

rba+2+(length)                crc(0)                                                   crc byte0

rba+2+(length+1)              crc(1)                                                   crc byte1

rba+2+(length+2)              crc(2)                                                   crc byte2

rba+2+(length+3)              r_tstamp[7:0]                                            time stamp byte0

rba+2+(length+4)              r_tstamp[15:8]                                           time stamp byte1

rba+2+(length+5)              r_tstamp[23:16]                                          time stamp byte2

rba+2+(length+6)              r_tstamp[31:24]                                          time stamp byte3

rba+2+(length+7)              pkt_fdc[7:0]                                             low byte of recorded frequency offset after demodulation

rba+2+(length+8)              {1'b0,rx_packet_chn_efuse[2:0]}, {1'b0,pkt_fdc[10:8]}    high byte of recorded frequency offset after demodulation

rba+2+(length+9)              pkt_rssi                                                 recorded packet RSSI

\-                             [0]                                                     crc error

\-                             [1]                                                     sfd error

\-                             [2]                                                     link layer error

\-                             [3]                                                     power error

\-                             [4]                                                     long range 125K indicator

\-                             [6:5]                                                   N/A

\-                             [7]                                                     NoACK indicator

--------------------------------------------------------------------------------------------------------------------

### BLE packet receiving data parsing

According to the receiving packet format introduced in the previous sections, the information commonly used in the receiving packet can be obtained through the interface, which has been encapsulated with the relevant functions:

------------------------------------------------------------------------------------------------------------
Function                                   Description
------------------------------------------ ----------------------------------------------------------------
rf_ble_packet_crc_ok(p)                    Determine whether the receiving packet CRC is correct

rf_ble_dma_rx_offset_crc24(p)              Get the index of the CRC location in the packet

rf_ble_dma_rx_offset_time_stamp(p)         Get the index value of time_stamp in the packet

rf_ble_dma_rx_offset_freq_offset(p)        Get the index value of the frequency offset in the packet

rf_ble_dma_rx_offset_rssi(p)               Get the index value of rssi in the packet

------------------------------------------------------------------------------------------------------------

### Packet parsing example

![Example of packet parsing](pic/exampleofpacketparsing.png "Example of packet parsing")

## Zigbee/hybee packet format

### Zigbee/hybee packet sending format  

Zigbee 250K and hybee mode sending packet data are stored in ram in the following format:

**Zigbee/Hybee TX Packet:**

----------------------------------------------------------------------------------
Address                           Content
--------------------------------- ------------------------------------------------
tba, tba + 1, tba + 2, tba + 3    DMA_LEN_INFO: rf_tx_packet_dma_len(payload length-1)

tba + 4                           Payload length

tba + 5                           data(0)

tba + 6                           data(1)

tba + 7                           data(1)

.....                             .....

tba+5+(length-3)                  data(length-3)

----------------------------------------------------------------------------------

### Zigbee/hybee packet receiving format

When the SoC is in zigbee 250K or hybee mode to receive packets, the received packet data is stored in ram in the format shown in the table below:

**Zigbee/hybee packet receiving format:**

------------------------------------------------------------------------------------------------------------------------
Address                           Content                                  Description
--------------------------------- ---------------------------------------- ---------------------------------------------
rba-4, rba-3, rba-2, rba-1        -                                          -

rba                               length (payload+crc)                       indicate length of payload and 2 crc bytes

rba+1                             data(0)                                    payload

rba+2                             data(1)                                    payload

rba+3                             data(2)                                    payload

.....                             .....                                      payload

rba+1+(length-3)                  data(length-3)                             payload

rba+1+(length-2)                  crc(0)                                     crc byte0

rba+1+(length-1)                  crc(1)                                     crc byte1

rba+1+(length)                    r_tstamp[7:0]                              time stamp byte0

rba+1+(length+1)                  r_tstamp[15:8]                             time stamp byte1

rba+1+(length+2)                  r_tstamp[23:16]                            time stamp byte2

rba+1+(length+3)                  r_tstamp[31:24]                            time stamp byte3

rba+1+(length+4)                  pkt_fdc[7:0]                               low byte of recorded frequency offset after demodulation

rba+1+(length+5)                  {1'b0,rx_packet_chn_efuse[2:0]}            high byte of recorded frequency offset after demodulation
                                  {1'b0,pkt_fdc[10:8]}

rba+1+(length+6)                  pkt_rssi                                   recorded packet RSSI

rba+1+(length+7)                  [0]                                        crc error

rba+1+(length+7)                  [1]                                        sfd error

rba+1+(length+7)                  [2]                                        link layer error

rba+1+(length+7)                  [3]                                        power error

rba+1+(length+7)                  [4]                                        long range 125K indicator

rba+1+(length+7)                  [6:5]                                       N/A

rba+1+(length+7)                  [7]                                         NoACK indicator

-----------------------------------------------------------------------------------------------------------------------

### Packet data parsing

Obtain the index of the received packet information according to the packet format.

-------------------------------------------------------------------------------------------------
Function                                   Description
------------------------------------------ ------------------------------------------------------
rf_zigbee_packet_crc_ok(p)                 Determine whether the CRC of the packet is correct

rf_zigbee_dma_rx_offset_crc(p)             Obtain the index of the CRC in the packet

rf_zigbee_dma_rx_offset_time_stamp(p)      Obtain the index of time_stamp in the packet

rf_zigbee_dma_rx_offset_freq_offset(p)     Obtain the index of frequency offset in the packet

rf_zigbee_dma_rx_offset_rssi(p)            Obatin the index of rssi in the packet

--------------------------------------------------------------------------------------------------

### Packet parsing example

The received data can be parsed according to the storage format of the received packets in zigbee/hybee mode in the previous sections, as shown in the following example:

![Example of packet parsing](pic/exampleofpacketparsing1.png "Example of packet parsing")

# Private packet format

The Private mode can be divided into two types of SB and TPLL(Telink Proprietary Link Layer), and this section introduces the sending and receiving packet formats for each of them.

## Private TPLL packet sending format

When the SoC sends packets in private mode using the TPLL, the packet data is stored in the following format:

**Private TPLL TX Packet:**

-------------------------------------------------------------------------------------------
Address                             Content
----------------------------------- -------------------------------------------------------
tba, tba + 1, tba + 2, tba + 3      DMA_LEN_INFO: rf_tx_packet_dma_len(payload length).

tba + 4                             Payload length

tba + 5                             data(0)

tba + 6                             data(1)

.....                               .....

tba+5+(length-1)                    data(length-1)

-------------------------------------------------------------------------------------------

## Private TPLL packet receiving format

When the SoC is in private TPLL mode to receive packets, the format of the received packets in RAM is shown below:

**Private TPLL mode receiving packet format:**

------------------------------------------------------------------------------------------------------------------------------
Address             Content                                                 Description|
------------------- ------------------------------------------------------- --------------------------------------------------
rba-4, rba-3        0                                                       -

rba-2               -                                                       -

rba-1               -                                                       -

rba                 payload length                                          indicate length of payload only, do not include 2 crc bytes

rba+1               data(0)                                                 payload

rba+2               data(1)                                                 payload

rba+3               data(2)                                                 payload

.....               .....                                                   payload

rba+1+(length-1)    data(length-1)                                          payload

rba+1+(length)      crc(0)                                                  crc byte0

rba+1+(length+1)    crc(1)                                                  crc byte1

rba+1+(length+2)    r_tstamp[7:0]                                           time stamp byte0

rba+1+(length+3)    r_tstamp[15:8]                                          time stamp byte1

rba+1+(length+4)    r_tstamp[23:16]                                         time stamp byte2

rba+1+(length+5)    r_tstamp[31:24]                                         time stamp byte3

rba+1+(length+6)    pkt_fdc[7:0]                                            low byte of recorded frequency offset after demodulation

rba+1+(length+7)    {1'b0,rx_packet_chn_efuse[2:0]} {1'b0,pkt_fdc[10:8]}    high byte of recorded frequency offset after demodulation

rba+1+(length+8)    pkt_rssi                                                recorded packet RSSI

rba+1+(length+9)    [0]                                                     crc error

rba+1+(length+9)    [1]                                                     sfd error

rba+1+(length+9)    [2]                                                     link layer error

rba+1+(length+9)    [3]                                                     power error

rba+1+(length+9)    [4]                                                     long range 125K indicator

rba+1+(length+9)    [6:5]                                                   N/A

rba+1+(length+9)    [7]                                                     NoACK indicator

------------------------------------------------------------------------------------------------------------------------------

## TPLL receiving packet parsing

Get the index of the information received in the packet according to the packet format.

------------------------------------------------------------------------------------------------------
Function                                     Description
-------------------------------------------- ---------------------------------------------------------
rf_pri_tpll_packet_crc_ok(p)                  Determine whether the receiving packet CRC is correct

rf_pri_tpll_dma_rx_offset_crc(p)              Get the index of the CRC location in the packet

rf_pri_tpll_dma_rx_offset_time_stamp(p)       Get the index value of time_stamp in the packet

rf_pri_tpll_dma_rx_offset_freq_offset(p)      Get the index value of the frequency offset in the packet

rf_pri_tpll_dma_rx_offset_rssi(p)             Get the index value of rssi in the packet

------------------------------------------------------------------------------------------------------

## Example of TPLL receiving packet parsing

![Example of TPLL receiving packet parsing](pic/exampleoftpllreceivingpacketparsing.png "Example of TPLL receiving packet parsing")

## Private SB packet format

When the SoC is in private SB mode for packet sending, the data is stored in ram in the following table:

**Private SB TX Packet:**

---------------------------------------------------------------------------------
Address                           Content
--------------------------------- -----------------------------------------------
tba, tba + 1, tba + 2, tba + 3    DMA_LEN_INFO: rf_tx_packet_dma_len(payload length).

tba + 4                           Payload length

tba + 7                           data(1)

---------------------------------------------------------------------------------

**Note:**

> - In private SB mode, the payload length information is not included in the packet format, so the packet format is different, and the payload length can be set by the function void rf_set_private_sb_len().

## Private SB packet receiving format

When the SoC is in private SB mode for packet receiving, the received packet data is stored in the ram as shown in the following table:

**Private SB packet receiving format:**

----------------------------------------------------------------------------------------------------------------------------------
Address                 Content                                             Description
----------------------- --------------------------------------------------- ------------------------------------------------------
rba-4, rba-3            0                                                    -

rba-2                   -                                                    -

rba-1                   -                                                    -

rba                     data(0)                                              payload

rba+1                   data(1)                                              payload

rba+2                   data(2)                                              payload

.....                   .....                                                payload

rba+1+(length-1)        data(length-1)                                       payload

rba+1+(length)          crc(0)                                               crc byte0

rba+1+(length+1)        crc(1)                                               crc byte1

rba+1+(length+2)        r_tstamp[7:0]                                        time stamp byte0

rba+1+(length+3)        r_tstamp[15:8]                                       time stamp byte1

rba+1+(length+4)        r_tstamp[23:16]                                      time stamp byte2

rba+1+(length+5)        r_tstamp[31:24]                                      time stamp byte3

rba+1+(length+6)        pkt_fdc[7:0]                                         low byte of recorded frequency offset after demodulation

rba+1+(length+7)        {1'b0,rx_packet_chn_efuse[2:0]}                      high byte of recorded frequency offset after demodulation
                        {1'b0,pkt_fdc[10:8]}

rba+1+(length+8)        pkt_rssi                                             recorded packet RSSI

rba+1+(length+9)        [0]                                                  crc error

rba+1+(length+9)        [1]                                                  sfd error

rba+1+(length+9)        [2]                                                  link layer error

rba+1+(length+9)        [3]                                                  power error

rba+1+(length+9)        [4]                                                  long range 125K indicator

rba+1+(length+9)        [6:5]                                                N/A

rba+1+(length+9)        [7]                                                  NoACK indicator

------------------------------------------------------------------------------------------------------------------------------------

## Example of SB receiving packet parsing

![Example of SB receiving packet parsing](pic/exampleofsbreceivingpacketparsing.png "Example of SB receiving packet parsing")

**Note:**

> - The demo framework of all modes is basically the same, but in private mode there is a need to distinguish between TPLL and SB; when using TPLL mode the operation is basically the same as other modes, but when using SB mode to send and receive packets you need to configure the corresponding registers to turn on the SB mode corresponding interface void rf_private_sb_en(void), and because SB mode packet format does not contain payload length information, you need to set the payload length of the receiving and sending end, corresponding to the interface void rf_set_private_sb_len(int pay_len).

# Manual mode

## Manual TX

### Single-frequency sending

For single frequency point sending in manual TX mode, the setup steps are as follows:

```C
rf_set_txmode(); //enter tx mode and wait for the trigger to send packets
delay_us(113); //wait for PLL to stabilize
while(1)
{
    rf_tx_pkt(ble_tx_packet); //trigger the packet sending
    while(! (rf_get_irq_status(FLD_RF_IRQ_TX))); //wait for the end of packet sending
    rf_clr_irq_status(FLD_RF_IRQ_TX); //clear the interrupt flag
}
```

**Note:**

> - In manual mode, the tx_settle time needs to be controlled manually to wait for the PLL to stabilize during the settle phase. 112.5us is the minimum settle time, and since the PLL is always working after rf_set_txmode() is set in manual mode, this action only needs to be done once when the manual tx is turned on.

### Frequency-hopping sending

If you need to switch frequencies during data sending, you need to wait for a packet to be sent before you can switch frequencies and send the next packet, set up as the following steps:

```C
//first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_set_txmode();
delay_us(113);//wait for PLL to stabilize
rf_tx_pkt(ble_tx_packet);//trigger the packet sending
while(! (rf_get_irq_status(FLD_RF_IRQ_TX))); //wait for packet sending to finish
rf_clr_irq_status(FLD_RF_IRQ_TX); //clear interrupt status
//Frequency-hopping sending usually requires waiting for the previous packet to be sent before switching the frequency and then triggering the next packet sending.
rf_set_ble_chn(37); //Switch the frequency to 2402MHz
rf_tx_pkt(ble_tx_packet); //trigger again to send packet
```

## Manual RX

### Single frequency receiving

If you need to use manual mode to send packets after completing the initialization settings, you can set the rf_set_rxmode() interface to enter the packet receiving state. The setting steps are as follows:

```C
rf_set_rxmode();//enter packet receiving mode, no packets are received at this stage, need to wait for stable PLL
    delay_us(85); //Wait for the PLL to stabilize and then enter the real packet receiving stage, if not switch the state, it will always be in the RX state and can always receive packets
    while(1)
    {
        if(rf_get_irq_status(FLD_RF_IRQ_RX)) //determine whether packet receiving is completed
        {
            if(rf_ble_packet_crc_ok(rx_packet)) //determine whether the received packet CRC is correct
            {
                rx_cnt++; //count the received packet
            }
            rf_clr_irq_status(FLD_RF_IRQ_RX); //clear packet receiving interrupt status
        }
    }
```

**Note:**

> - In manual mode, the rx_settle time needs to be controlled manually to wait for the PLL to stabilize during the settle phase. The minimum settle time is 85us, and since the PLL is always working after setting rf_set_rxmode() in manual mode, this action only needs to be done once when the manual rx is turned on.
> - The PLL stays on in manual mode when a packet is received, so clearing the interrupt flag after a packet is received moves to the next packet receiving state.

```C
void rf_set_rx_dma (unsigned char *buff,unsigned char wptr_mask, unsigned short fifo_byte_size) 
```

function description:

-------------------------------------------------------------------------------------
Parameters        Description
----------------- -------------------------------------------------------------------
buff              Receiving packet address

wptr_mask         Receive packet with dma write pointer mask = number of FIFOs - 1

fifo_byte_size    FIFO size

-------------------------------------------------------------------------------------

**Note:**

> - In manual mode, because the hardware will not maintain reading and writing pointers, only one FIFO will be used for receiving, the number of FIFOs is usually set to 1 when setting the dma. An example of setting: rf_set_rx_dma(rx_packet,0,128) one FIFO, FIFO size of 128bytes.

![Example of manual mode setting](pic/exampleofmanualmodesetting.png "Example of manual mode setting")

### Frequency-hopping receiving

If frequency hopping is required during packet receiving, the setting example is as follows:

```C
// first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_set_rxmode();//enter packet receiving mode
delay_us(85);//wait for the PLL to stabilize and enter the actual packet receiving phase after stabilization
if(rf_get_irq_status(FLD_RF_IRQ_RX))
{
    if(rf_ble_packet_crc_ok(rx_packet))
    {
                rx_cnt++;
    }
    rf_clr_irq_status(FLD_RF_IRQ_RX);
}
while(rf_receiving_flag());//wait for the end of the packet receiving (currently it waits for the completion of the packet receiving, whether there is a problem in the packet receiving status is directly interrupted is still being confirmed)
rf_set_ble_chn(37);//Switch the frequency to 2402MHz and wait for the next packet receiving
```

### Send-receive switching

If you need to switch between sending and receiving modes during operation, code example is as follows:

```C
// first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_set_txmode();//enter packet receiving mode
delay_us(113);//wait for the PLL to stabilize and enter the actual packet receiving phase after stabilization
while(! (rf_get_irq_status(FLD_RF_IRQ_TX))); //wait until the end of packet sending
rf_clr_irq_status(FLD_RF_IRQ_TX); //clear interrupt status
//Switching states requires waiting for the previous state to end before switching states
rf_tx_rx_off();//turn off tx,rx
rf_set_rx_mode(); //enter rx state
delay_us(85);//wait for PLL to stabilize
```

# Auto mode

## STX

The workflow of the state machine in auto mode is as follows:

![Workflow of the state machine in auto mode](pic/workflowofthestatemachineinautomode.png "Workflow of the state machine in auto mode")

Call function void rf_start_stx (void* addr, unsigned int tick) to trigger STX, enter tx settle, settle ends and enters actual tx state.

```C
void rf_start_stx (void* addr, unsigned int tick)
```

function description:

-------------------------------------------------------------------------------------
Parameters    Description
------------- -----------------------------------------------------------------------
addr          Packet sending address

tick          Trigger immediately when the current tick value is greater than the set tick

-------------------------------------------------------------------------------------

**Note:**

> - The default value of TX_SETTLE time is 150us. You can call interface void rf_tx_settle_us(unsigned short txstl_us) to adjust the settle time, but the tx settle time should not be less than 112.5us.

### Single-frequency sending

Calling the **rf_start_stx** function will trigger the state machine to enter the TX state (including tx settle), complete the packet sending and return to the IDLE state. The setting steps are as follows.

```C
// first complete the initialization action
rf_start_stx(ble_tx_packet,clock_time());//trigger the first packet sending, and the state machine automatically returns to IDLE state after the packet is sent.
    while(1)
    {
        while(! (rf_get_irq_status(FLD_RF_IRQ_TX))); //determine whether the packet sending is completed
        rf_clr_irq_status(FLD_RF_IRQ_TX);//
        rf_start_stx(ble_tx_packet,clock_time());
    }
```

### Frequency-hopping sending

If you need to switch the frequency point during packet sending, the setting steps are as follows:

```C
// first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_start_stx(ble_tx_packet,clock_time());//trigger the first packet sending, and the state machine automatically returns to IDLE state after the packet is sent.
while(! (rf_get_irq_status(FLD_RF_IRQ_TX)));//determine whether the packet sending is completed
rf_clr_irq_status(FLD_RF_IRQ_TX);// clear the packet sending interrupt status 
rf_set_ble_chn(37);// 2402MHz switch frequency
rf_start_stx(ble_tx_packet,clock_time());//trigger packet sending again
```

## SRX

The working process of the state machine when receiving packets in auto mode is as follows:

![The working process of the state machine when receiving packets in auto mode](pic/theworkingprocessofthestatemachinewhenreceivingpacketsinautomode.png "The working process of the state machine when receiving packets in auto mode")

The auto mode use function void rf_start_srx(unsigned int tick); to trigger SRX, enter rx settle, after settle ends and enter actual rx, when packet receiving is completed it automatically returns to idle state. In the specified time, if the data is not synchronized to the packet, it triggers FLD_RF_IRQ_RX_TIMEOUT interrupt.

```C
void rf_start_srx (unsigned int tick)
```

function description:

-------------------------------------------------------------------------------------
Parameters    Description|
------------- -----------------------------------------------------------------------
tick          Trigger immediately when the current tick value is greater than the set tick

-------------------------------------------------------------------------------------

**Note:**

> - The default value of rx_settle time is 150us, you can call the interface void rf_rx_settle_us(unsigned short txstl_us) to adjust the settle time, but the tx settle time should not be less than 85us.

### Single-frequency receiving

If single frequency point receiving is performed in auto mode, the setting steps are as follows:

```C
// first complete the initialization action
rf_start_srx(clock_time());//after triggering the state machine will enter the synchronous state from IDLE state, while timeout starts timing.
    while(1)
    {
        if(rf_get_irq_status(FLD_RF_IRQ_RX))//determine if packet receiving is finished
        {
            u8* raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM,RX_FIFO_DEP,rx_packet);//find the current packet receiving address, only needed in auto mode.
            if(rf_ble_packet_crc_ok(raw_pkt))//determine whether the CRC of the packet is correct
            {
                rx_cnt++;//record the number of packets received
                rf_clr_irq_status(FLD_RF_IRQ_RX);//clear the interrupt status
                rf_start_srx(clock_time());//trigger the next packet receiving
        }
     }
```

**Note:**

> - In auto mode, DMA will automatically offset the data when carrying data to the ram address based on the number of FIFOs and FIFO depth. Therefore, after each packet is received, you need to find the address of this packet in ram for crc check by rf_get_rx_packet_addr(int fifo_num,int fifo_dep,void* addr) function.

The rf_get_rx_packet_addr function is described as follows:

-------------------------------------------------------------------------------------
Parameters   Description
------------ ------------------------------------------------------------------------
fifo_num     Number of FIFOs

fifo_dep     Size of each FIFO

addr         Receiving packet address

-------------------------------------------------------------------------------------

When using the function rf_set_rx_dma(rx_packet,3,128); to set DMA, it will have 4 FIFOs for packet receiving.

![Before receiving the first packet](pic/beforereceivingthefirstpacket.png "Before receiving the first packet")

![Before receiving the second packet](pic/beforereceivingthesecondpacket.png "Before receiving the second packet")

Until the four FIFOs are received, it returns to the first FIFO. The following figure shows the result of packet receiving in auto mode, where the number of FIFOs is 4 and the FIFO size is 128 bytes.

![Packet receiving results in auto mode](pic/packetreceivingresultsinautomode.png "Packet receiving results in auto mode")

### Frequency-hopping receiving

If you need to switch the frequency point during packet receiving, the setting steps are as follows:

```C
// first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_start_srx(clock_time());//trigger packet receiving, and the state machine will automatically return to IDLE state after packet receiving is completed
if(rf_get_irq_status(FLD_RF_IRQ_RX))//determine the end of packet receiving
{
    u8* raw_pkt = rf_get_rx_packet_addr(RX_FIFO_NUM,RX_FIFO_DEP,rx_packet);//find the address of the packet receiving
    if(rf_ble_packet_crc_ok(raw_pkt))
    {
            rx_cnt++;
    }
    rf_clr_irq_status(FLD_RF_IRQ_RX);
}
while(rf_receiving_flag());//determine whether packet sending is completed
rf_clr_irq_status(FLD_RF_IRQ_RX);//clear packet receiving interrupt status
rf_set_ble_chn(37);// 2402MHz switching frequency
rf_start_srx(clock_time());//trigger packet receiving again
```

### Automatic mode switching

If you switch between sending and receiving in auto mode, the code example is as follows:

```C
// first complete the initialization action
rf_set_ble_chn(17);// 2440MHz
rf_set_stx(ble_tx_packet,clock_time());
while(! (rf_get_irq_status(FLD_RF_IRQ_TX))); //wait for the end of packet sending
rf_clr_irq_status(FLD_RF_IRQ_TX); //clear the interrupt status
// Wait for the previous state to end before switching states
rf_set_tx_rx_off_auto_mode();//turn off tx,rx
rf_start_srx(clock_time());//trigger packet receiving
```

**Note:**

> - Currently, when switching states we usually wait until the previous state is finished before stopping the state machine, and then switch to the next state.

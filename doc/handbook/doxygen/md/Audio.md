@page AUDIO_Example AUDIO

# Audio introduction

## Sound basic

Sound is an acoustic wave produced by the vibration of an object and is a mechanical wave. The audio recording process is an analog-to-digital conversion process and the playback process is the opposite.

![Analog to digital conversion process](pic/Analogtodigitalconversionprocess.png "Analog to digital conversion process模数转换过程")

- Sampling: Taking a point at regular intervals for an analog signal.

- Quantization: scales the vertical coordinates and takes integer values according to an approximation so that the values of the points sampled are integers.

- Encoding: Encode the integer values obtained by quantization in binary.

- Digital signal: Transform the sequence of 0's and 1's obtained by encoding into a high and low level signal.

The whole analog-to-digital conversion process is called Pulse Code Modulation (PCM for short), and as can be seen from the above analog-to-digital conversion, the contents of the PCM format file are actually the encoded sequence.

## Basic concepts of sampled audio

**Sampling frequency:** Sampling is the digitization of an analog signal on a time axis, which is sampled (AD-converted) at a frequency more than twice the highest frequency of the sound according to Nyquist's Theorem (sampling theorem). Sounds with frequencies between 20 Hz and 20 kHz are recognizable to the human ear. This is why the sampling frequency is generally around 40 kHz, commonly used for music at 44.1 kHz (44,100 samples/second), 48 kHz, etc. The sampling rate for telephones is 8 kHz.

**Sampling bits:** The range of data that each sample point can represent. The number of sampling bits is usually either 8 bits or 16 bits, the greater the number of bits, the more detailed the variation in sound that can be recorded and the greater the corresponding amount of data. The 16-bit is the most common sampling accuracy.

**Number of channels:** The number of channels refers to the number of audio channels that can support different sound generation, commonly used are mono, stereo (left and right channel).

For example, the relevant parameters for CD sound quality are, sample bit width of 16 bits, sample rate of 44100, number of channels is 2, which is used to measure the volume size of the audio data per unit time, the data bit rate of CD sound quality is: 44100 \* 16 \* 2 = 1411.2 kbps.

**PCM audio data:** PCM is sampled and quantized uncompressed audio data, converted from analog signals into standard digital audio data by sampling, quantizing and encoding. In the case of mono audio files, the sampled data is stored sequentially in chronological order (in the case of dual channels it is stored in LRLR mode, the storage is also related to the big/small-endian of the machine). The big-endian mode is shown in the figure below.

![PCM data format](pic/PCMdataformat.png "PCM data format")

## I2S protocol

The I2S (Inter-IC Sound) bus, also known as the integrated circuit built-in audio bus, is a bus standard developed by Philips Semiconductors (now NXP Semiconductors) for the transmission of audio data between digital audio devices, which is used exclusively for data transmission between audio devices.

### I2S signals

(1) Serial clock BCLK

The serial clock, BCLK, has a pulse for each bit of data corresponding to the digital audio.

(2) Frame clock LRCK

The frame clock LRCK is for switching data between left and right channels. LRCLK (Left/Right CLOCK), frequency of LRCK = sampling frequency.

(3) Serial data SDATA

It is the audio data expressed in binary complement, (MSB ---> LSB: the data is transmitted sequentially from high to low bits).

### I2S data format

Depending on the position of the data relative to the LRCLK and BCLK, it is divided into I2S standard format (I2S), left-justified (LJ) and right-justified (RJ), and the same data format must be used on both the transmitter and receiver end.

**Note:**

> - The driver defaults to the I2S format.

(1) I2S format

The highest bit of the data is always at the 2nd BCLK pulse after the LRCLK change (i.e. the start of a frame) and the timing sequence is shown as below.

![I2S format](pic/I2Sformat.png "I2S format")

(2) LJ format

Data transmission starts at the same time as the LRCLK is flipped. Note that at this point when LRCLK is 1, the left channel data is transmitted, which is just the opposite of the I2S Philips standard. The left-aligned (MSB) standard timing sequence is shown as below.

![LJ format](pic/LJformat.png "LJ format")

(3) RJ format

While the sound data LSB transmission is completed, the LRCLK completes its second flip (it just happens that the LSB and LRCLK are right-justified, hence called right-justified standard). Note that at this point when LRCLK is 1, the left channel data is transmitted.

![RJ format](pic/RJformat.png "RJ format")

(4) DSP/PCM mode

The DSP/PCM mode is divided into two modes, Mode-A and Mode-B. Some of the datasheets for different chips write PCM mode and some write DSP mode. The I2S left and right channels are high and low respectively, PCM has only one start signal and the left channel data follows the right channel. In figure A below, the Mode-A data is at the first BCLK pulse. In figure B below, the Mode-B data is at the 2nd BCLK pulse.

![DSP format (Mode-A)](pic/DSPformatModeA.png "DSP format (Mode-A)")

![DSP format (Mode-B)](pic/DSPformatModeB.png "DSP format (Mode-B)")

# Audio structure

## CODEC introduction

As shown in the diagram below, the audio CODEC has an analog-to-digital converter (ADC). The CODEC converts the analog signal from the AMIC and Line-in inputs into an A/D conversion, turning the analog signal into a digital signal that the CPU can process; the digital-to-analog converter (DAC) converts signals such as PCM into a D/A conversion, converts the digital audio signal into an analog signal.

![CODEC framework](pic/CODECframe.png "CODEC framework")

## Audio framework

As shown in the figure below, the audio module consists of 3 parts: the data input and output interfaces, which may vary from SoC to SoC, the I2S RX interface and the audio CODEC ADC interface at Input_Path, the I2S TX interface and the CODEC DAC interface at Output_Path; the FIFO and DMA that make up the data interaction interface (blue box); BUFF for storing PCM data (orange box).

- Input_Path：The CODEC passes the A/D converted digital signal into the BUFF or directly passes the data into the BUFF via the I2S RX interface.

- Output_Path：D/A conversion of signals such as PCM from BUFF, converting digital audio signals to analog signals or direct output via I2S TX.

![Audio framework](pic/Audioframediagram.png "Audio framework")

## Audio I2S clock

As shown in the figure below, when the SoC as master to accommodate different sampling rates (LRCLK), supporting 8K/16K/32K/48K/44.1K, it is necessary to set different dividing factors to calculate the corresponding sampling rate, where the Audio module clock source of MCLK clock and I2S_CLK are directly from PLL = 192M, then I2S_CLK is divided to BCLK and LRCLK.

![SoC audio clock source](pic/socaudioclocksource.png "SoC audio clock source")

In which, MCLK=PLL/diver1, LRCLK=PLL/divder2/divider3/divider4.

# Audio driver

## DMA transfer

The audio data transfer is via DMA (Direct Memory Access). The working mechanism of DMA and Audio BUFF are introduced below.

### DMA transfer mechanism

The DMA transfer is the direct sending of data from a peripheral device to internal memory without CPU, or, from internal memory to an external device without CPU. The transfer action itself is implemented and completed by the DMA controller, and the transfer process does not require the involvement of the CPU. As shown in the following figure, the audio FIFO and BUFF data interaction is transferred via DMA, with the source address of the recording (Rx) DMA being the first address of Rx_FIFO with a depth of 8 words and the destination address being the first address of Rx_BUFF with a depth that can be configured. The playback (Tx) DMA has a destination address of the first address of Tx_FIFO with a depth of 8 word and a source address of the first address of Tx_Buff with a depth that can be configured. If Rx_BUFF and Tx_BUFF share a common BUFF, then the destination address of Rx and the source address of Tx are the same.

![DMA and Audio FIFO interaction](pic/DMAandAudioFIFOinteractiondiagram.png "DMA and Audio FIFO interaction")

### DMA link transfer

The audio data streams are generated without interruption. DMA transfers are completed once and then the next transfer requires configuration of the relevant control registers and DMA length to trigger the DMA transfer again. The DMA linked list can solve this problem, using the linked list method can complete the function of continuous transfer without CPU involvement. The DMA linked list includes the following contents: DMA control, src_addr, dst_addr, DMA length and LLP_ptr (the address of the next linked list). After the DMA has completed the first transfer, set the head of the linked list (Head_of_list) and the DMA will be transferred according to the contents of the linked list configuration and then linked to the next  linked list for transfer, and the cycle repeats.

(1) DMA ping-pong buff link transfer

The following figure shows the link transfer of a ping-pong buff with Tx as an example. Create the header node Head_of_list first, and then add two linked lists to the circular linked list, Tx_dma_list[0] and Tx_dma_list[1], with Tx_dma_list[0] corresponding to the source address Tx_BUFF[1], Tx_dma_list[1] corresponding to Tx_BUFF[0]. According to its flow, the data of Tx_BUFF[0] is carried first, then the data of Tx_BUFF[1] is carried according to the linked list header LLP pointing to Tx_dma_list[0], the data of Tx_BUFF[0] is carried according to the LLP in Tx_dma_list[0] pointing to the Tx_dma_list[1], then LLP in turn points to Tx_dma_ list[0], which closes to form a ping-pong buff.

![ping-pong buff link transfer](pic/pingpongBUFFchain.png "ping-pong buff link transfer")

(2) DMA single buff link transfer

As shown in the figure below, in the case of Tx, the ping-pong buff is used to make the LLP of the Tx_dma_list point to itself, and to send a DMA is to carry the data of a single Tx_BUFF all the time.

![Single BUFF link transfer](pic/SingleBUFFchain.png "Single BUFF link transfer")

## Audio buff working mechanism

Audio uses a ring buff, Rx for recording and Tx for playback. Data is transferred via DMA, with the source address of DMA for Rx being the audio peripheral FIFO address and the destination address being the RX_BUFF first address, and the source address of DMA for Tx being Tx_BUFF and the destination address being the audio peripheral FIFO address.

### Rx Path

As shown in the figure below, Rx_BUFF with BUFF_size length set , the recording data is moved into Rx_BUFF by DMA to obtain rx_wptr which is maintained by hardware (the way it is obtained varies from chip to chip). Record rx_rptr according to the software fetch data operation from Rx_BUFF, maintained by the software. The red line part is the readable data length read_len which has below conditions:

- rx_wptr > rx_rptr, read_len = rx_wptr - rx_rptr;

- rx_wptr < rx_rptr, read_len = buff_size - (rx_rptr - rx_wptr).

![Rx_BUFF](pic/RxBUFF.png "Rx_BUFF")

### Tx Path

As shown in the figure below, Tx_BUFF with BUFF_size length is set, and the playback is to move the BUFF data out of BUFF by DMA to obtain tx_rptr maintained by hardware (the way it is obtained varies from chip to chip). Record tx_wptr according to the software fill data operation to Tx_BUFF, maintained by the software. The red line is the length of the writable data write_len which has below conditions:

- tx_rptr > tx_wptr, write_len = tx_rptr - tx_wptr;

- tx_rptr < tx_wptr, write_len = buff_size - (tx_wptr - tx_rptr).

![Tx_BUFF](pic/TxBUFF.png "Tx_BUFF")

## Audio_Demo

In the header of audio demo, configure the macro AUDIO_MODE in app_config.h to select the different audio modes.

--------------------------------------------------------------------------------------------------------------------------
Demo                                  Function
------------------------------------- ------------------------------------------------------------------------------------
LINEIN_TO_LINEOUT                     The analog audio is fed in at the input jack, with speakers or headphones connected at the output jack to hear the CODEC-processed audio in real time.

AMIC_TO_LINEOUT                       AMIC recording, with CODEC-processed audio heard in real time by connecting speakers or headphones to the output jack.

DMIC_TO_LINEOUT                       DMIC recording, with a speaker or headphone connected to the output jack to hear the CODEC-processed audio in real time.

BUFFER_TO_LINEOUT                     The PCM data from the BUFF will be output through CODEC processing, and the audio from the BUFF (usually 1K sine wave) can be heard by connecting speakers or headphones to the output jack.

FLASH_TO_LINEOUT                      The PCM data in the flash is read out according to a certain way to fill in the AUDIO BUFF, and then output after CODEC processing, the audio in the flash can be heard in the output jack connected to the speaker or headphones.

EXT_CODEC_LINEIN_LINEOUT              The SoC's I2S interface interacts with an external CODEC (WM8731 for example), which is LINE_IN to LINE_OUT in external CODEC.
--------------------------------------------------------------------------------------------------------------------------

# Chip difference

## Difference between Input Path and Output Path

### B91 Audio Input Path

Referring to Input_Path in the [Audio framework diagram](#audio-framework), as shown below, there are 2 types of audio input: I2S signals (AMIC/DMIC/LINE-IN) processed by the internal CODEC (all CODECs refer to the internal CODEC unless otherwise stated); and I2S signals input from the external CODEC.

**I2S input:**

The IO of the I2S interface is connected to an internal CODEC or an external CODEC via Mux selection. I2S supports I2S, LJ, RJ and DSP formats; the bit width supports 16bit, 20bit, 24bit and 32bit data formats. When transferring data I2S_Rx will convert the received serial I2S data into parallel data and write it to Rx_BUFF.

![Audio input path](pic/Audioinputpath.png "Audio input path")

### B91 Audio output Path

Referring to Output_Path in the [Audio framework diagram](#audio-framework), as shown below, there are 2 ways to output audio: audio data in Tx_BUFF, which is output to the internal CODEC or external CODEC via the I2S interface.

**I2S output:**

The audio data in Tx_BUFF is converted to serial I2S format by I2S_Tx and fed to an internal CODEC or an external CODEC.

![Audio output path](pic/Audiooutputpath.png "Audio output path")

## Audio Demo difference

### B91 LINEIN_TO_LINEOUT

![LINEIN_TO_LINEOUT](pic/LINEINTOLINEOUT.png "LINEIN_TO_LINEOUT")

**Note:**

> - The ADC input supports single-ended and differential, the default is differential mode, while the DAC only supports differential output.
> - In MONO mode, you can select single left channel output or left and right channel output at the same time, when the data of both channels are the same, the default is the latter.
> - In STEREO mode, the left input corresponds to the left output and the right input corresponds to the right output.

### AMIC_TO_LINEOUT

![AMIC_TO_LINEOUT](pic/AMICTOLINEOUT.png "AMIC_TO_LINEOUT")

**Note:**

> - The ADC input supports single-ended and differential, the default is differential mode, while the DAC only supports differential output.
> - In MONO mode, for the input channel: the default is left channel as AMIC input, you can call audio_set_mono_chn interface to set it to right channel as AMIC input. For the output channel: you can choose single left channel output or left and right channel output at the same time, at this time the data of both channels is the same, the default is the latter.
> - In STEREO mode, the left input corresponds to the left output and the right input corresponds to the right output.

### DMIC_TO_LINEOUT

![DMIC_TO_LINEOUT](pic/DMICTOLINEOUT.png "DMIC_TO_LINEOUT")

**Note:**

> - In MONO mode, single DMIC only need 2 signal lines of data and clk, the clk frequency is fixed at 3 MHz.
> - In STEREO mode, the left input corresponds to the left output, the right input corresponds to the right output, the dual DMIC has 1 signal line of data and 2 clks, the dual DMICs share data, the timing of the 2 clks is the same, the data of one DMIC is collected on the upper edge of the clk, the data of the other DMIC is collected on the lower edge of the clk.

### BUFFER_TO_LINEOUT

The demo provides mono audio data at a frequency of 1KHz with a sample rate of 44.1Kbps, and mono audio data at a frequency of 1KHz with a sample rate of 48Kbps.

**Note:**

> - The first address of BUFF here is the source address of the DMA, using BUFFER as audio_buff.
> - Whether in MONO or STEREO mode, the output dual channel output will have a sample phase difference. Calling audio_invert_i2s_lr_clk to invert the i2s clk will eliminate the phase difference.

### EXT_CODEC_LINEIN_LINEOUT

The demo implementation: the SoC's I2S interface interacts with an external CODEC (WM8731 for example), external CODEC LINE_IN to LINE_OUT.

![EXT_CODEC_LINEIN_LINEOUT](pic/EXTCODECLINEINLINEOUT.png "EXT_CODEC_LINEIN_LINEOUT")

**Note:**

> - MCLK (12M) is provided using PWM0.
> - The default sample rate is 32Kbps, MONO, BIT_16.

### FLASH_TO_LINEOUT

The demo function: the PCM data in the flash is read out in accordance with the fixed length filled into the AUDIO_BUFF, and then through the LINE_OUT output. Refer to [AUDIO BUFF working mechanism](#audio-buff-working-mechanism), the length of the BUFF is 4K (AUDIO_BUFF_SIZE), the flash data is very large and needs to be filled into the BUFF in batches.

**B91 audio module has no valid interrupts to fill and fetch audio data:**

- The recording data is moved into Rx_BUFF by the DMA in the unit of word, and the destination address of the DMA is self-adding by 4 each time, returning to 0 after self-adding to BUFF_size-4. The offset of the destination address relative to the first address of Rx_BUFF is noted as rx_wptr.

- The playback is to move the BUFF data out of the BUFF by the DMA in the unit of word, and the DMA source address is self-added by 4 each time, returning to 0 after self-adding to BUFF_size-4. The offset of the source address relative to the first address of Tx_BUFF is noted as tx_rptr.

The function interface is introduced first:

```C
u32 audio_get_tx_dma_rptr (dma_chn_e chn) //The parameter chn is configured as a tx dma channel to obtain the corresponding channel dma source address
```

The source address of the initialization DMA is configured as the first address of audio_buff. The size of audio_buff is 4K, the playback is to move the buff data out of the buff by DMA in the unit of word, the source address of DMA will add 4 at each move, returning to 0 after the addition to buff_size-4. The source address of DMA minus the first address of audio_buff address, which characterizes the state of the hardware read at audio_buff, noted as the read pointer tx_rptr:

```C
tx_rptr= ((audio_get_tx_dma_rptr (DMA3)-(u32)audio_buff));
```

And the write state of audio_buff_buff, maintained by software, is noted as tx_wptr, referring to the formula for calculating [Tx Path](#tx-path) in the AUDIO BUFF working mechanism, the remaining writable space of audio_buff is coded as below:

```C
if((tx_wptr&(AUDIO_BUFF_SIZE - 1))>tx_rptr)
    {
        unused_buff=AUDIO_BUFF_SIZE-(tx_wptr&(AUDIO_BUFF_SIZE-1))+tx_rptr;
    }
    else
    {
        unused_buff=tx_rptr-tx_wptr;
    }
```

For example, if the BUFF is filled by fixed length of data (AUDIO_THD_SIZE), its flow in while (1) is as follows.

![Flow](pic/Flow.png "Flow")

**Note:**

> - The ADC input supports single-ended and differential, the default is differential mode, while the DAC only supports differential output.
> - In MONO mode, you can select single left channel output or left and right channel output at the same time, when the data of both channels are the same, the default is the latter.
> - In STEREO mode, the left input corresponds to the left output and the right input corresponds to the right output.

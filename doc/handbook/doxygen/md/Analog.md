@page ALG_REG_Example ANALOG

The analog driver is used to read and write analog registers, supporting the function test of single Byte/Hword/Word, data buffer, DMA channel read and write.

# Attentions

When using DMA to read data from analog registers to buffer, the buffer size of the corresponding destination address must be a multiple of 4.

The reason: Each DMA sends 4 bytes to buffer. 4 bytes will be written to the destination address even if the configured read length is less than 4.

For example: if you define an array buffer of size 5 bytes and configure the DMA to read 5 bytes from the analog register to buffer, the DMA actually transfers twice and 8 bytes in total to buffer, and the extra 3 bytes data will overflow from the array, and the overflowed data will overwrite other variables. At this time, if the array size is configured to 8 bytes, the extra 3 bytes data will be stored in the array and will not be overflowed, avoiding the potential risk.

# Speed Test

Under the condition that cclk, pclk and hclk are set to 24MHz, each interface function is loaded into RAM and the time spent on reading and writing 4 bytes and 8 bytes in each mode is tested as follows:

|Mode|Time of writing 4 bytes|Time of reading 4 bytes|
|:------------------------|:-----------------|:-----------------|
|ALG_WORD_MODE|6us|12.9us|
|ALG_DMA_WORD_MODE|8.4us|10.2us|
|ALG_DMA_BUFF_MODE|8.4us|12.4us|
|ALG_BUFF_MODE|10us|12us|
|ALG_HWORD_MODE|12.8us|17.6us|
|ALG_DMA_ADDR_DATA_MODE|13.1us|Not supported|
|ALG_BYTE_MODE|22.6us|26.8us|

|Mode|Time of writing 8 bytes|Time of reading 8 bytes|
|:----------------------|:---------------|:------------------|
|ALG_DMA_BUFF_MODE|11.2us|15.5us|
|ALG_BUFF_MODE|12.8us|16.6us|
|ALG_WORD_MODE|15.8us|19.3us|
|ALG_DMA_ADDR_DATA_MODE|18.9us|Not supported|
|ALG_DMA_WORD_MODE|23.5us|20.1us|
|ALG_HWORD_MODE|24.8us|32.9us|
|ALG_BYTE_MODE|44.1us|53.9us|


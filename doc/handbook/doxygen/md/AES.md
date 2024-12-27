@page AES_Example AES

It supports hardware AES128 encryption, all buffer data used in the interface are using the small endian mode.

**Note:**

> - This is because there is a restriction on the address where the data used in AES calculations can be stored: it must be in the address space of base_address+64K.
> - It is currently handled in the driver as follows: Define the base_address as 0xc0000000 (that is the starting address of IRAM) in the first 64K of the IRAM range aes_data segment (which can be seen in the link file), and the data that needs to be processed during AES calculation are put into the aes_data segment for processing.
> - If you do not change the location of the aes_data segment in the link file, you can use it directly without concerning the above process.
> - If it does not meet the demand, you can also adjust it by yourself according to the demand. The driver provides aes_set_em_base_addr interface to modify the base_address.
> - In addition, this address is shared with BT, and modifying it also requires ensuring that the data used by BT is also in this address space.

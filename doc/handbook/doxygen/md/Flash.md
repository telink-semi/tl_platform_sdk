@page Flash_Example FLASH

The flash is a Non-Volatile memory that can retain data for a long time without current supply and has storage characteristics equivalent to a hard disk. The flash can erase and reprogram memory cells called blocks. The write operation of any flash device can only be performed in an empty or erased cell, so an erase must be performed before a write operation can be performed.

# Read operation

**Note:**

> - When the read address exceeds the maximum address of flash, the value can still be read, but the read address is calculated according to the valid address bits. (If the flash size is 1M bytes, the maximum address is 0xfffff, that is, the lower 20 bits is the valid address bit; if the value of 0x100000 address is read, the value of 0x0 address is read.)

# Write operation

**Note:**

> - You should erase before write. The latest flash_write_page function supports cross-page writing.


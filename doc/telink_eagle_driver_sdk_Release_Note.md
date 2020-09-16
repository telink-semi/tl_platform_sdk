## V1.0.0-Beta

### Version
* SDK version : telink_b91_driver_sdk V1.0.0-Beta.
* This version sdk support B91 A0 chip.
### Features
* AES/AUDIO/FLASH/LPC/MDEC/PKE/PM/PWM/RF/STIMER/TIMER/TRNG
* Interface:GPIO/I2C/SPI/UART/USB
### Known issues
* **pm** 
  - The suspend mode can't be used on the A0 version chip
  - In order to avoid the problem of abnormal overwrite sram in the A0 chip, a special treatment is added to the sys_init function 
    (if it is the A0 chip and it is the first power-on, it will enter deep, wake up after 100ms, and the program will be executed normally after wake-up)
* **gpio** 
  - GPIO_PD can't be used on the A0 version chip
* **uart** 
  - It is recommended to use the non-DMA mode. In the A0 version, the function of the DMA mode is defective. When receiving, the interrupt can be generated normally 
    only when the received data length is known.
* **clock**
  - The use of clock_init function needs to pay attention to two points:
   - CCLK_DIV2_TO_HCLK and HCLK_DIV4_TO_PCLK can’t be set at the same time
   - If the pm or reboot function is used, the parameter hclk_div cannot be set to CCLK_DIV2_TO_HCLK
* **other**
  - Precautions for the use of the development board (A0 version chip):
  If USB power supply, you need to unplug the USBVBUS-VBUS jumper (that is, you can't use +5V directly to the Vbus of the chip), otherwise it will cause USB/Audio 
  instability.
### BREAKING CHANGES
* N/A

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### 版本
* SDK版本: telink_b91_driver_sdk v1.0.0-Beta.
* 此版本SDK支持B91 A0芯片.
### Features
* AES/AUDIO/FLASH/LPC/MDEC/PKE/PM/PWM/RF/STIMER/TIMER/TRNG
* Interface:GPIO/I2C/SPI/UART/USB
### 注意事项
* **pm** 
   - suspend模式在A0版本芯片上不可以使用
   - 为了规避A0芯片存在的异常改写sram问题，在sys_init函数中加了一段特殊处理（如果是A0芯片，并且是第一次上电，则会进入deep，100ms后唤醒，唤醒后会正常执行程序）
* **gpio** 
  - GPIO_PD在A0版本芯片上不能使用
* **uart** 
  - 建议使用非DMA模式，在A0版本，DMA模式的功能有缺陷，接收时，只有已知接收数据长度时，才能正常的产生中断。
* **clock**
  - clock_init函数的使用需要注意一下两点:
   - CCLK_DIV2_TO_HCLK和HCLK_DIV4_TO_PCLK不能同时设置 
   - 如果有使用pm或者reboot功能，则参数hclk_div不能设置为CCLK_DIV2_TO_HCLK
* **其他**
  - 开发板使用注意事项（A0版本芯片）：如果USB供电时，需要拔掉USBVBUS-VBUS跳帽（即不能用+5V直接给芯片的Vbus），否则会导致USB/Audio不稳定

### BREAKING CHANGES
* N/A
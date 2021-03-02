
## V1.5.0-Beta

### Version

* SDK version : telink_b91_driver_sdk v1.5.0-Beta.
* This version sdk support B91 A0，A1 and A2 chip.

### Bug Fixes

* **usb**
  * Fix the problem that usb_spk could not work when only USB_SPEAKER_ENABLE is turned on in USB_SPK Demo.
* **audio**
  * Corrct spelling errors in "audio_buff" in AUDIO Demo.
  * Correct the data type definition error in the app_sin_data.h file in AUDIO_Demo.
* **spi**
  * Interface hspi_change_csn_pin()/pspi_change_csn_pin() have logic error, would configure the unused csn pin, the error has been fixed.And hspi_change_csn_pin()/pspi_change_csn_pin() has been deleted from the driver and moved to SPI_Demo.
  * Interface spi_slave_set_pin() have a pin configuration bug, the bug has been fixed.
  * Fixed the comment error of the hspi address length of the hspi_set_addr_len function.
* **rf**
  * Fixed the following problem: When using the function rf_clr_irq_status () to clear a certain rf interrupt status, other rf interrupts may  be cleared by mistake.
* **uart** 
  * add parameter of uart_num in function "uart_get_dma_rev_data_len() to distinguish UART0 and UART1".

### Features

* **freertos**
  * add freertos Demo

### Known issues

* N/A

### BREAKING CHANGES

* **flash**
  * In order to be compatible with other sdk, the flash_read_mid function used to pass in a buf pointer, and instead returns an unsigned int variable.
  * Mid is changed from 3byte to 4byte, and the highest byte is used to distinguish flashes with the same mid but different functions.

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">


### 版本

* SDK版本: telink_b91_driver_sdk v1.5.0-Beta。
* 此版本SDK支持B91 A0、A1和A2芯片。

### Bug Fixes

* **usb**
  * 修复在USB_SPK Demo中仅打开USB_SPEAKER_ENABLE时，usb_spk无法工作的问题。
* **audio**
  * 更正在AUDIO_DEMO中“audio_buff”中的拼写错误。
  * 更正在AUDIO_DEMO中app_sin_data.h文件中数据类型定义不符的错误。
* **spi**
  * Hspi_change_csn_pin()/Pspi_change_csn_pin() 接口有逻辑错误，会配置没有用到的csn引脚，该问题已经修复。并且Hspi_change_csn_pin()/Pspi_change_csn_pin()接口已经从Drvier中删除并移到了SPI_Demo中。
  * spi_slave_set_pin()接口引脚配置有错误，该问题已经修复。
  * 修复了hspi_set_addr_len函数的hspi地址长度的注释错误。
* **rf**
  * 修复了如下问题：在使用函数rf_clr_irq_status ()清除rf某个中断状态时，有可能会误清除其他rf中断。
* **uart**
  * 函数uart_get_dma_rev_data_len()增加参数uart_num区分UART0和UART1。

### Features

* **freertos**
  * 增加 freertos Demo

### Known issues

* N/A

### BREAKING CHANGES

* **flash**
  * 为了兼容其他sdk，flash_read_mid函数以前是传入一个buf指针，改为返回unsigned int型变量。
  * mid由3byte改为4byte,最高byte用于区分mid相同但是功能存在差异的flash。

---
## V1.4.0-Beta

### Version
* SDK version : telink_b91_driver_sdk v1.4.0-Beta.
* This version sdk support B91 A0，A1 and A2 chip.

### Bug Fixes

* **pm**
  * solve the problem that pragrem can not run when VBAT power supply is greater than 4.1V,and sys_int configer power mode as DCDC mode.
  * During the stability test, the program freezes after running for a period of time.
* **spi** 
  * spi enum SPI_MODE1、SPI_MODE2 definition as error value, fixed as correct value.
* **uart**
  * when close the irq in dma mode,the receive buffer maybe overflow if dma receive data continuous.

### Features

* **pwm**
  * add function interface "pwm_32k_chn_dis".
* **audio** 
  * Add the interface for selecting DAC output channel (audio_set_output_chn).
* **usb**
  * Add software to handle set_configuration control transmission.
  * Support usb cdc to send wMaxPacketSize (64bytes) length data.
* **uart** 
  * Add function uart_get_dma_rev_data_len() in DMA mode.
    

### Refactoring

* **spi** 
  * adjusted the initial process of LED in SPI_Demo.
* **audio**
  * Adjust the calls of i2c (control codec) and pwm (provide external clock) interfaces in audio applications.
* **usb/audio**
  * set the sampling rate of the DAC to 16k by default,In the mic_spk demo.

### Known issues

* N/A
### BREAKING CHANGES
* **audio**
  * Modify the audio_i2s_config function parameters, add audio_i2s_invert_config structure parameters to select i2s_lr_clk_invert and i2s_data_invert.

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### 版本

* SDK版本: telink_b91_driver_sdk v1.4.0-Beta。
* 此版本SDK支持B91 A0、A1和A2芯片。

### Bug Fixes

* **pm**
  * 解决VBAT供电高于4.1V且sys_int配置供电模式为DCDC时程序不能运行的问题。
  * 稳定性测试时，运行一段时间程序卡死的问题。
* **spi**
  * spi 的SPI_MODE1、SPI_MODE2枚举值定义错了，修复为了正确值。
* **uart**
  * DMA模式下关闭总中断时，如果UART仍在接收数据，有可能导致接收数组溢出。

### Features

* **pwm**
  * 添加函数接口pwm_32k_chn_dis。
* **audio**
  * 增加invert I2S CLK接口（audio_invert_i2s_lr_clk）。
* **usb**
  * 添加软件处理set_configuration控制传输。
  * 支持USB CDC发送wMaxPacketSize（64bytes）长度数据。
* **uart**
  * DMA模式增加函数uart_get_dma_rev_data_len()。


### Refactoring

* **spi** 
  * 调整了SPI_Demo中LED的初始化过程。
* **audio**
  * 调整AUDIO应用中i2c（控制codec）和pwm(提供外部时钟)接口的调用。
* **usb/audio**
  * 在mic_spk demo中将DAC的采样率默认设为16k。

### Known issues

* N/A

### BREAKING CHANGES

* **audio**
  * 修改audio_i2s_config function函数参数，新增audio_i2s_invert_config 结构体形参，设置i2s_lr_clk_invert 和i2s_data_invert。


---
## V1.3.1-Beta

### Version
* SDK version : telink_b91_driver_sdk V1.3.1-Beta.
* This version sdk support B91 A0，A1 and A2 chip.

### Bug Fixes
* **pm**:

 * Use digital register way to get 32k tick may read error tick,cause the wakeup time is incorrect with the setting time,the sleep time will very little or very big,will not wakeup ontime.

  + The previous configuration will cause the voltage on the VDD1V8 pin to be generally high during normal operation, about 3.0V~3.1V (the reason is that the previous configuration will cause the two power supplies to be powered at the same time), which may cause abnormal phenomena. The version is modified to the correct configuration. In the default configuration, the voltage on the VDD1V8 pin will be about 2.8V.

* **USB**:
  + The header file "stdDescriptors.h" is not case sensitive when included, so it is uniformly changed to "StdDescriptors.h"

* **AUDIO**:
      + In the function audio_set_dmic_pin(), fix the problem of possible errors in setting the dmic pin

### Known issues
* N/A
### BREAKING CHANGES
* **pwm**
   + Detailed description: add 32k clock calibration,the interface function(pwm_32k_chn_en) changes" =" to |=，to prevent reset other channels.

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### 版本

* SDK版本: telink_b91_driver_sdk V1.3.1-Beta。
* 此版本SDK支持B91 A0、A1和A2芯片。

### Bug Fixes

* **pm**:
  * 使用数字方式获取32k tick出错会导致设置的唤醒tick与预期不符，从而导致唤醒时间与设置的不相符，睡眠时间可能过小或者过大，可能会表现为不唤醒。
 + 之前的配置会导致正常工作时，VDD1V8引脚上的电压会普遍偏高，大概为3.0V~3.1V（原因是之前的配置会导致两个电源会同时供电），可能会造成异常现象，此版本修改为正确配置，默认配置下，VDD1V8引脚上的电压会是2.8V左右。

* **USB**:
    + 头文件"stdDescriptors.h",include时没有区分大小写，统一改成"StdDescriptors.h"


* **AUDIO**:
      + 在函数audio_set_dmic_pin()中，修复设置dmic pin可能出错问题

### Known issues
* N/A

### BREAKING CHANGES
* **pwm**
 + 添加32k时钟源校准，接口函数pwm_32k_chn_en修改，=改为|=，防止重置其他通道.

---

### Version



## V1.3.0-Beta

### Version
* SDK version : telink_b91_driver_sdk V1.3.0-Beta.
* This version sdk support B91 A0，A1 and A2 chip.

### Bug Fixes

* **pm**:
  * Solved the problem that the reboot state cannot be read after the reboot comes back, and the deep state is read only. The solution is to add a status "MCU_STATUS_REBOOT_DEEP_BACK" to the enumeration type "pm_mcu_status".
  * Solved the problem that the timer could not wake up after waking up several times when the function clock_cal_32k_rc() was not called.
  * Solved the problem that when the flash is configured with four wires, it cannot work normally after waking up from suspend mode.
* **clock**: 
  * Solved the problem of invalid kick with PD0 port when 32k xtal starts to vibrate.
* **adc**: 
  * Fix the sort bug of function adc_sort_and_get_average_code() in ADC_Demo.
  * Fix the problem that the adc_get_temperature()/adc_get_voltage() function in ADC_Demo may not get data for the first time.

### Features

* **swire**
  * add swire driver and demo.
* **cproject**: 
  * delete B91 keyword.
* **adc**
  * Added the 1/4 pre_scale parameter enum of the adc_set_scale_factor() function, and deleted the 1, 1/2, 1/8 pre_scale parameter enum.
* **pm** 
  * change the variable name g_pm_multi_addr ->g_pm_mspi_cfg.
    
  * Improved the problem of incorrect LED configuration during the suspend sleep current test in pm_demo.
* **audio** 
  * add audio_set_codec_wnf api.
  * add input_mode_select at line_in.
  * set all gain to 0db default in audio.c.
* **flash** 
  * add flash_set_xip_config function.
* **usb** 
  * add host speaker stop playback detection function in spk demo.
* **pwm**
  * add function interface pwm_32k_chn_update_duty_cycle.


### Known issues
* N/A
### BREAKING CHANGES
* **s7816**
  * modify the s7816_set_time(),delete the atr wait time in the function of coldreset and warmreset.

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### 版本

* SDK版本: telink_b91_driver_sdk V1.3.0-Beta。
* 此版本SDK支持B91 A0、A1和A2芯片。

### Bug Fixes

* **pm**:
  * 解决了reboot回来后不能读到reboot状态，只读到deep状态的问题。解决方案是在枚举类型"pm_mcu_status"中新增一种状态"MCU_STATUS_REBOOT_DEEP_BACK"。 
  * 解决了不调用函数clock_cal_32k_rc()时，timer唤醒几次后不能再唤醒的问题。
  * 解决了设置flash四线时，suspend唤醒后flash不能正常工作的问题。
* **clock**:
  * 解决了32k xtal起振时用PD0口kick无效的问题。
* **adc**:
  * 修复了ADC_Demo中的adc_sort_and_get_average_code()函数的排序问题。
  * 修复了ADC_Demo中的adc_get_temperature()/adc_get_voltage()函数第一次可能会采不到数据的问题。

### Features

* **swire**
  * 增加swire的驱动和demo。
* **cproject**:
  * 删除关键字B91。
* **adc**
  * 添加了adc_set_scale_factor（）函数的1/4 pre_scale参数枚举，并删除了1、1 / 2、1 / 8 pre_scale参数枚举。


* **pm**

  * 更改变量名称g_pm_multi_addr-> g_pm_mspi_cfg。
  * 改进了在pm_demo中的suspend睡眠电流测试过程中，指示灯配置错误的问题。

* **audio** 
  * 添加接口audio_set_codec_wnf。
  * 在line_in添加input_mode_select。
  * 在audio.c中将所有增益设置为0db默认值。

* **flash** 

  * 添加函数flash_set_xip_config 。

* **usb** 

  * 在spk_demo中添加主机扬声器停止播放的检测功能。

* **pwm**

  * 添加功能接口pwm_32k_chn_update_duty_cycle。




### Known issues
* N/A

### BREAKING CHANGES
* **s7816**

  * 修改函数s7816_set_time()，在coldreset和warmreset函数中删除atr等待时间。


---
## V1.2.0-Beta

### Version
* SDK version : telink_b91_driver_sdk V1.2.0-Beta.
* This version sdk support B91 A0 and A1 chip.

### Bug Fixes

* **uart** 

  * Fix the problem that the configuration function uart\_receive_dma cannot continue to receive data after UART suspend or reset UART

### Features
* **sys**
  * Modify the member name of the parameter enumeration vbat\_type\_e variable in the sys\_init function
* **watchdog**
	* Simplify the parameters of the wd\_set\_interval\_ms function, and no longer retain the parameter tick\_per\_ms
* **timer**
   * In the timer\_set\_mode function, the initial tick and capture tick are no longer configured and are encapsulated into two interfaces (timer\_set\_init\_tick, timer\_set\_cap_tick)
* **gpio** 
  * Modify default macro definition in gpio_default.h 
  * The corresponding enable function gpio\_irq\_en,gpio\_gpio2risc0\_irq\_en,gpio\_gpio2risc1\_irq\_en is no longer called in the gpio\_set\_irq,gpio\_set\_gpio2risc0\_irq,gpio\_set\_gpio2risc1\_irq function, which is flexibly called in the application layer
* **plic**
  * Delete the parameter of the function plic\_interrupt\_claim
* **other**  
  * Optimize the include structure of the header file, add Include paths in the project configuration options

### Known issues
* **32k xtal** 
  - 32k xtal can't be used on the A1 version chip
* **gpio** 
  - GPIO_PD0 can't be used on the A1 version chip
* **other**
  - Note (A1 version chip): Use 2.8V voltage to power the chip. When the power supply voltage is higher than 2.8V, the program may not run.
### BREAKING CHANGES
* N/A

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### Bug Fixes

* **uart** 

  * 修复UART suspend起来或reset UART后，配置函数uart\_receive\_dma不能继续接收数据问题

### 版本
* SDK版本: telink_b91_driver_sdk v1.2.0-Beta.
* 此版本SDK支持B91 A0和A1芯片.
### Features
* **sys**
  * 在sys\_init函数中修改枚举vbat\_type\_e类型的成员名称。
* **watchdog**
	* 简化wd\_set\_interval_ms函数的参数,参数period\_ms为间隔时间，不再保留参数tick\_per\_ms
* **timer**
  * 在timer\_set\_mode函数中,不再配置初始tick和capture tick，分别封装成两个接口（timer\_set\_init_tick,timer\_set\_cap\_tick）
* **gpio** 
  * 修改gpio_default.h默认宏定义
  * 在gpio\_set\_irq,gpio\_set\_gpio2risc0_irq/gpio\_set\_gpio2risc1\_irq函数中不再调用对应使能函数gpio\_irq\_en,gpio\_gpio2risc0\_irq\_en,gpio\_gpio2risc1\_irq\_en,在应用层里灵活调用
* **plic**
  * 删去函数plic\_interrupt\_claim的参数
* **other**  
  * 优化头文件包含结构，在工程配置选项里添加Include paths
### Known issues
* **32k xtal** 
   - 32k xtal 在A1版本芯片上不能使用。
* **gpio** 
  - GPIO_PD0在A1版本芯片上不能使用
* **其他**
  - 注意事项（A1版本芯片）：使用2.8V电压给芯片供电，供电电压高于2.8V时，程序有可能会跑不起来。

### BREAKING CHANGES
* N/A

---
## V1.1.0-Beta
### Version

* SDK version : telink_b91_driver_sdk v1.1.0-Beta.
* This version sdk support B91 A0 and A1 chip.

### Bug Fixes

* **pm**

  * Solved the problem of not being able to wake up when the sleep time is less than 950us.

  * Solved the problem that the sleep function cannot be awakened when the sleep function is called immediately within 500us after power on.

* **mdec**: 

  * Solved the problem of first interruption after initialization.

* **clock**: 

  * Solve the problem that the program sometimes stops in the clock initialization function (clock_init).

* **lpc**: 

  * Solved the problem of abnormal operation of lpc.

* **flash**: 

  * Remove the declaration of the function flash_read_mid_uid_with_check_ram. Added declaration of function flash_read_mid_uid_with_check.

  * Solved the problem of not being able to cross pages when writing flash across pages.

* **bqb:** 

  * fix the issue that could not send packets through instructions in initialization state.

* **rf:** 

  * Fixed an abnormal function of rf_set_rffe_pin function.

  * Modify the function rf_set_rx_dma and rf_set_tx_dma to adapt to sending and receiving long packets(up to 255 byte)

  * Modified the usage example of rx　interrupt. 

  * fix the issue that rf_set_pipe_access_code can not set 5-byte access code.

  * Fix the register setting error in the rf_set_preamble_len function.

  * Modify the access code of S2 and S8 mode to manual trigger.

* **emi** 

  * Fix the problem of zigbee mode 2480Mhz band edge can not pass the spec.
  * Fixed single carrier frequency offset in emi.

* **.s** 

  * Modified cstartup_b91_flash.S and cstartup_b91_ram.S file to reserve space. 

* **reboot&clock**

  * fix the issue that reboot will crash when hclk is half of cclk in pll_clk and pad24M_clk,need add a 

* **analog** 

  * fix a compile error in analog demo

* **spi** 

  * Simplify structure and macro definition naming, optimize SPI slave demo structure，fix compilation error

* **uart** 

  * Fix the issue that the mask might be overwritten by the set of bit width when the uart-init.

### Features
* **sys**

  * Add parameters vbat_v in the sys_init function.

* **sys_time**

  * Change CLOCK_16M_SYS_TIMER_CLK_XXX to SYSTEM_TIMER_TICK_XX.

* **pm** 

  * Increase the convergence calibration function of sleep time.

  * Increase USB wake-up function.

  * Increase the suspend sleep function.
  * add long sleep wakeup api.

* **bqb** 

  * add a macro to switch new/old setting ways to configure uart/cap/flash.

* **license** 

  * change the author to "Driver Group" and modify the license template to meet the requiements CI checking.

* **rf** 

  * Add ANT mode to rf demo.

  * update the function rf_set_chn and rf_set_ble_chn to support out-of-band frequency point setting

  * In order to facilitate the development of SDK, the DMA setting function related to RF is divided into several functions with single function, and added to the driver.

* **AES** 

  * optimize AES_set_mode apiuart:add Single line transceiver function

* **uart**

  * add UART-TXDONE/RXDONE interrupt in DMA mode in the chip version of A1 .

  * data of variable length is acceptable in uart-dma mode in the chip version of A1, the length of receive-date can be work out.

* **s7816**

  * add s7816 demo, can communicate with the equipment that support IS07816 protocol.

* **gpio**

  * add 30k-digital pull-up。

* **plic**

  * Optimized interrupt handling function structure in PLIC

* **i2c**

  * add function that the master sends a stop after detecting a NACK in the ID phase，then stops reading and writing。

  * Add tx_done interrupt in dma demo

* **audio**

  * In MONO mode, the input channel (left/right) can be selected

  * Add input channel acquisition mode selection (single-ended/differential)

  * Add configuration for ADC and DAC to work at different sampling rates（ADC=16K，DAC=48K）

* **spi**

  * Add 3line mode and master to multiple-slave function

* **adc**

  * Add ADC module  in the chip version of A1 which support DMA sampling mode and manual sampling mode, support Vbat\GPIO\Temperature sensor sampling

### Known issues
* **32k xtal** 
  - 32k xtal can't be used on the A1 version chip
* **gpio** 
  - GPIO_PD0 can't be used on the A1 version chip
* **other**
  - Note (A1 version chip): Use 2.8V voltage to power the chip. When the power supply voltage is higher than 2.8V, the program may not run.
### BREAKING CHANGES
* N/A

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### Bug Fixes

* **pm**  

  * 解决了睡眠时间小于950us时，不能唤醒的问题。 

  * 解决了上电500us内立即调用睡眠函数时无法唤醒的问题。

* **mdec**  

  * 解决了初始化后先进一次中断的问题。

* **clock**  

  * 解决了程序有时会停在时钟初始化函数（clock_init）中的问题。

* **lpc**  

  * 解决了lpc工作异常的问题。

* **flash**  

  * 去掉函数flash_read_mid_uid_with_check_ram的声明。新增函数flash_read_mid_uid_with_check的声明。

  * 解决了跨页写flash时，不能跨页的问题。

* **bqb** 

  * 修复了在初始化状态下，不能通过指令发包的问题。

* **rf** 

  * 修复了函数rf_set_rffe_pin功能异常 。

  * 修改函数参数rf_set_rx_dma ,rf_set_tx_dma以适应长包（最大长度255byte）

  * 修改rx interrupt使用示例

  * 修复了rf_set_pipe_access_code不能设置5byte长度的access code

  * 修复了rf_set_preamble_len函数中的寄存器设置错误

  *  修改S2,S8模式access code为手动触发

* **emi** 

  * 修复zigbee 2480Mhz边带不能过spec的问题
  * 修复单通频偏的问题

* **.s** 

  * 更新s文件以预留空间

* **reboot&clock** 

  * 修复当hclk等于1/2cclk时reboot出现宕机的问题。

* **analog** 

  * 修复analog_demo中的错误

* **spi** 

  * 精简结构体和宏定义命名，优化SPI slave demo结构，修复编译错误

* **uart** 

  * 修复UART初始化设置位宽时可能会覆盖掉mask的问题

### 版本
* SDK版本: telink_b91_driver_sdk v1.0.0-Beta.
* 此版本SDK支持B91 A0和A1芯片.
### Features
* **sys**

  * 在sys_init函数中添加参数vbat_v。

* **sys_time**

  * 将CLOCK_16M_SYS_TIMER_CLK_XXX更改为SYSTEM_TIMER_TICK_XX。

* **pm**

  * 增加睡眠时间的收敛校准功能。

  * 增加USB唤醒功能。 

  * 增加suspend睡眠功能。    
  * 新增长睡眠接口。

* **bqb** 

  * 增加了一个宏，用来选择新的或旧的方式来配置串口、CAP值以及适配的Flash大小。

* **license** 

  * 将License的作者统一改成了“Driver Group”以及统一调整了License的模板。    

* **rf** 

  * 添加ANT模式到rf demo中.

  * 更新设置channel的函数rf_set_chn和rf_set_ble_chn以支持带外频点设置

  * 为了方便SDK的开发将DMA设置函数拆分成几个功能单一的函数并添加到驱动中。

* **AES** 

  * 优化AES_set_mode接口uart:新增单线收发模式

* **uart**

  * A1版本芯片新增DMA模式UART-TXDONE/RXDONE中断。

  * A1版本芯片UART-DMA模式可以接收不定长的数据，并能计算出接收数据的长度

* **s7816**

  * 新增s7816模块，可与支持ISO7816协议的设备进行单线半双工通信。

* **gpio**

  * 新增30k数字上拉。

* **plic**

  * 在PLIC中优化了中断处理函数结构

* **i2c**

  * 增加了master在发ID阶段检测到NACK后发stop，并停止读写动作

  * 在dma demo中增加了tx_done中断。

* **audio**

  * MONO模式下，可选择输入通道（左/右)，默认只有左通道输出；

  * 增加了输入通道采集模式选择（单端/差分）

  * 新增ADC和DAC在不同采样率工作的配置（ADC=16K，DAC=48K）。

* **spi**

  * 新增3line模式和master对多slave功能。

* **adc**

  * A1版本芯片新增ADC模块，支持DMA采样模式和手动采样模式，支持Vbat\GPIO\Temperature sensor采样


### Known issues
* **32k xtal** 
   - 32k xtal 在A1版本芯片上不能使用。
* **gpio** 
  - GPIO_PD0在A1版本芯片上不能使用
* **其他**
  - 注意事项（A1版本芯片）：使用2.8V电压给芯片供电，供电电压高于2.8V时，程序有可能会跑不起来。

### BREAKING CHANGES
* N/A

---
## V1.0.0-Beta
### Version
* SDK version : telink_b91_driver_sdk v1.0.0-Beta.
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
### Known issues
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
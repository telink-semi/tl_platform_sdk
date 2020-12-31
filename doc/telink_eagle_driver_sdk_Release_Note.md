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
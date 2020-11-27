
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
@page TRAP_Example TRAP

The PLIC (Platform-Level Interrupt Controller) is compatible with RISC-V PLIC and has two major functions: interrupt vector and interrupt priority.

# Interrupt overview

In the interrupt mechanism, the processor is suddenly interrupted by another request during the sequential execution of the program command stream and aborts the execution of the current program to deal with something else. After it has finished processing something else, it then reverts to the point where the program was interrupted to continue executing the previous program command stream. The "other request" is called an interrupt request, and the other "request source" is called the interrupt source, which usually comes from a peripheral device. The processor turns to perform "something else", which is called an interrupt processing program.

# Interrupt type

The RISV-V architecture has three modes of operation: Machine Mode, User Mode and Supervisor Mode. We are using Machine Mode, and there are three types of interrupts in Machine Mode: Software Interrupt, Timer Interrupt, and External Interrupt. The external interrupt refers to CPU external interrupts, such as from UART, GPIO, and so on; the timer interrupt refers to interrupts from timers; the software interrupt is an interrupt triggered by the software itself.

**Note:**

> - There are two modes of interrupt, vector and regular mode, and the driver defaults to vector mode.

# External interrupt

## Interrupt enable

For the use of the driver interrupt interface, if you want to open the interrupt, it has the following three levels:

**The first layer**

```C
core_enable_interrupt()
```

It enables the corresponding BIT in the CSR register of the RISC-V core, which is the general interrupt switch.

**Second layer**

```C
plic_interrupt_enable()
```

It enables the BIT of the corresponding module in the plic module, which is the module interrupt control switch.

**Third layer**

```C
rf_set_irq_mask(FLD_ZB_RX_IRQ)
```

It enables the mask of the corresponding module, take the rf module as an example, set which one you need to use.

## External interrupt handler function in vector mode

The corresponding interrupt handler functions have been defined in the plic driver and correspond to the following:

@if MCU_CORE_B91
| Interrup vectors         | Interrupt handler functions    |
| ------------------------ | ------------------------------ |
| IRQ0_EXCEPTION           | except_handler                 |
| IRQ1_SYSTIMER            | stimer_irq_handler             |
| IRQ2_ALG                 | analog_irq_handler             |
| IRQ3_TIMER1              | timer1_irq_handler             |
| IRQ4_TIMER0              | timer0_irq_handler             |
| IRQ5_DMA                 | dma_irq_handler                |
| IRQ6_BMC                 | bmc_irq_handler                |
| IRQ7_USB_CTRL_EP_SETUP   | usb_ctrl_ep_setup_irq_handler  |
| IRQ8_USB_CTRL_EP_DATA    | usb_ctrl_ep_data_irq_handler   |
| IRQ9_USB_CTRL_EP_STATUS  | usb_ctrl_ep_status_irq_handler |
| IRQ10_USB_CTRL_EP_SETINF | usb_ctrl_ep_setinf_irq_handler |
| IRQ11_USB_ENDPOINT       | usb_endpoint_irq_handler       |
| IRQ12_ZB_DM              | rf_dm_irq_handler              |
| IRQ13_ZB_BLE             | rf_ble_irq_handler             |
| IRQ14_ZB_BT              | rf_bt_irq_handler              |
| IRQ15_ZB_RT              | rf_irq_handler                 |
| IRQ16_PWM                | pwm_irq_handler                |
| IRQ17_PKE                | pke_irq_handler                |
| IRQ18_UART1              | uart1_irq_handler              |
| IRQ19_UART0              | uart0_irq_handler              |
| IRQ20_DFIFO              | audio_irq_handler              |
| IRQ21_I2C                | i2c_irq_handler                |
| IRQ22_SPI_AHB            | hspi_irq_handler               |
| IRQ23_SPI_APB            | pspi_irq_handler               |
| IRQ24_USB_PWDN           | usb_pwdn_irq_handler           |
| IRQ25_GPIO               | gpio_irq_handler               |
| IRQ26_GPIO2RISC0         | gpio_risc0_irq_handler         |
| IRQ27_GPIO2RISC1         | gpio_risc1_irq_handler         |
| IRQ28_SOFT               | soft_irq_handler               |
| IRQ29_NPE_BUS0           | npe_bus0_irq_handler           |
| IRQ30_NPE_BUS1           | npe_bus1_irq_handler           |
| IRQ31_NPE_BUS2           | npe_bus2_irq_handler           |
| IRQ32_NPE_BUS3           | npe_bus3_irq_handler           |
| IRQ33_NPE_BUS4           | npe_bus4_irq_handler           |
| IRQ35_USB_RESET          | usb_reset_irq_handler          |
| IRQ36_NPE_BUS7           | npe_bus7_irq_handler           |
| IRQ37_NPE_BUS8           | npe_bus8_irq_handler           |
| IRQ42_NPE_BUS13          | npe_bus13_irq_handler          |
| IRQ43_NPE_BUS14          | npe_bus14_irq_handler          |
| IRQ44_NPE_BUS15          | npe_bus15_irq_handler          |
| IRQ46_NPE_BUS17          | npe_bus17_irq_handler          |
| IRQ50_NPE_BUS21          | npe_bus21_irq_handler          |
| IRQ51_NPE_BUS22          | npe_bus22_irq_handler          |
| IRQ52_NPE_BUS23          | npe_bus23_irq_handler          |
| IRQ53_NPE_BUS24          | npe_bus24_irq_handler          |
| IRQ54_NPE_BUS25          | npe_bus25_irq_handler          |
| IRQ55_NPE_BUS26          | npe_bus26_irq_handler          |
| IRQ56_NPE_BUS27          | npe_bus27_irq_handler          |
| IRQ57_NPE_BUS28          | npe_bus28_irq_handler          |
| IRQ58_NPE_BUS29          | npe_bus29_irq_handler          |
| IRQ59_NPE_BUS30          | npe_bus30_irq_handler          |
| IRQ60_NPE_BUS31          | npe_bus31_irq_handler          |
| IRQ61_NPE_COMB           | npe_comb_irq_handler           |
| IRQ62_PM_TM              | pm_irq_handler                 |
| IRQ63_EOC                | eoc_irq_handler                |
@endif

@if MCU_CORE_B92
| Interrup vectors         | Interrupt handler functions    |
| ------------------------ | ------------------------------ |
| IRQ1_SYSTIMER            | stimer_irq_handler             |
| IRQ2_ALG                 | analog_irq_handler             |
| IRQ3_TIMER1              | timer1_irq_handler             |
| IRQ4_TIMER0              | timer0_irq_handler             |
| IRQ5_DMA                 | dma_irq_handler                |
| IRQ6_BMC                 | bmc_irq_handler                |
| IRQ7_USB_CTRL_EP_SETUP   | usb_ctrl_ep_setup_irq_handler  |
| IRQ8_USB_CTRL_EP_DATA    | usb_ctrl_ep_data_irq_handler   |
| IRQ9_USB_CTRL_EP_STATUS  | usb_ctrl_ep_status_irq_handler |
| IRQ10_USB_CTRL_EP_SETINF | usb_ctrl_ep_setinf_irq_handler |
| IRQ11_USB_ENDPOINT       | usb_endpoint_irq_handler       |
| IRQ14_ZB_BT              | rf_bt_irq_handler              |
| IRQ15_ZB_RT              | rf_irq_handler                 |
| IRQ16_PWM                | pwm_irq_handler                |
| IRQ17_PKE                | pke_irq_handler                |
| IRQ18_UART1              | uart1_irq_handler              |
| IRQ19_UART0              | uart0_irq_handler              |
| IRQ20_DFIFO              | audio_irq_handler              |
| IRQ21_I2C                | i2c_irq_handler                |
| IRQ22_LSPI               | lspi_irq_handler               |
| IRQ23_GSPI               | gspi_irq_handler               |
| IRQ24_USB_PWDN           | usb_pwdn_irq_handler           |
| IRQ25_GPIO               | gpio_irq_handler               |
| IRQ26_GPIO2RISC0         | gpio_risc0_irq_handler         |
| IRQ27_GPIO2RISC1         | gpio_risc1_irq_handler         |
| IRQ28_SOFT               | soft_irq_handler               |
| IRQ29_MSPI               | mspi_irq_handler               |
| IRQ30_USB_RESET          | usb_reset_irq_handler          |
| IRQ31_USB_250US          | usb_250us_irq_handler          |
| IRQ33_QDEC               | qdec_irq_handler               |
| IRQ34_GPIO_SRC0          | gpio_src0_irq_handler          |
| IRQ35_GPIO_SRC1          | gpio_src1_irq_handler          |
| IRQ36_GPIO_SRC2          | gpio_src2_irq_handler          |
| IRQ37_GPIO_SRC3          | gpio_src3_irq_handler          |
| IRQ38_GPIO_SRC4          | gpio_src4_irq_handler          |
| IRQ39_GPIO_SRC5          | gpio_src5_irq_handler          |
| IRQ40_GPIO_SRC6          | gpio_src6_irq_handler          |
| IRQ41_GPIO_SRC7          | gpio_src7_irq_handler          |
| IRQ44_PM_WKUP            | pm_wkup_irq_handler            |
| IRQ45_PM_IRQ             | pm_irq_handler                 |
| IRQ46_DPR_IRQ            | dpr_irq_handler                |
@endif


```C
__attribute__((section(".ram_code"))) void default_irq_handler(void)
{

}
void stimer_irq_handler(void) __attribute__((weak, alias("default_irq_handler")));
```

By default, all interrupt handler functions are weakly defined as default_irq_handler, an empty function.

**Weak function**

In theory, a project is not allowed to have two functions with the same name. Here it is OK to use _weak to specify that one of them is a weak function.

When the program is compiled, if two functions with the same name are found and one of them is a weak function, the weak function will be ignored and the normal function will be used for compilation; if only one weak function is found, then the weak function will still be used to participate in the compilation.

When the upper layer uses it, just define another function which is the same, without specifying the weak function, and then add some user code to the function.

**Interrupt site save and resume**

No interrupt save and resume are found in the interrupt processing, but the function is normal for the following reasons:
```c
_attribute_ ((interrupt ("machine"), aligned(4)));
```
There are interrupt declarations in attribute, and the compiler sees that it will insert code that modifies the protection registers.

## Priority in external interrupt

When multiple interrupt sources initiate requests to the processor at the same time, the concept of interrupt priority exists when these interrupt sources need to be arbitrated and which interrupt sources are prioritized. When interrupt priority is not enabled, a new interrupt will not interrupt the interrupt being processed and will wait until the interrupt service function is completed before a new interrupt request can be responded accordingly. The default interrupt preemption function is not turned on, and if you need to use the interrupt preemption function, you need the following three steps:

- 1. Set plic_set_threshold(). Only interrupts with priority> threshold can be generated, threshold defaults to 0 and priority defaults to 1.

- 2. plic_preempt_feature_en(CORE_PREEMPT_PRI_MODE0);   //enable interrupt preemption function and config MEI, MSI, and MTI nest priority.

- 3. plic_set_priority();  //set the interrupt priority

**Note:**

> - The SoC has 4 interrupt priority 0-3. The interrupt source with no setting of interrupt priority, the default priority is 1, the larger the number the higher the priority. Setting to 0 priority will not generate interrupts (threshold default 0, do not meet the condition: priority> threshold). The high priority interrupt source can interrupt the interrupt source with lower priority, can not interrupt the interrupt with the same level priority.

There are 3 interrupts configured in the demo, stimer interrupt, timer0 interrupt and rf_tx interrupt.

- 1. Enable interrupt

```C
core_interrupt_enable();
```

- 2. Enable interrupt preemption, set priority, default threshold is 0

```C
plic_preempt_feature_en(CORE_PREEMPT_PRI_MODE0);                      //enable interrupt preemption and config MEI, MSI, and MTI nest priority.
plic_set_priority(IRQ1_SYSTIMER,IRQ_PRI_LEV3);  //set the stimer priority
plic_set_priority(IRQ4_TIMER0, IRQ_PRI_LEV2);   //set timer0 priority
plic_set_priority(IRQ15_ZB_RT, IRQ_PRI_LEV1);   //set rf priority
```

Before and after the delay of the interrupt handler function, the observation IO is set to pull up before the delay and pull down after the delay. In the demo, the stimer is delayed for 250us, the timer0 is delayed for 600us, and the rf_tx is delayed for 800us.

```C
_attribute_ram_code_sec_noinline_ void irq_handler(void)
{
    ...
    gpio_set_high_level(LED3);
    delay_us();
    gpio_set_low_level(LED3);
}
```

## Results observation

In the following figure, the interrupt nesting is enabled, rf_tx is interrupted by the high priority timer0, and so forth, Time0 interrupt handler function is interrupted by the higher priority stimer.

![Interrupt nesting is enabled](pic/interruptnestingisenabled.png "Interrupt nesting is enabled")

In the figure below, the interrupt nesting is not enabled, and the default priority of all three interrupt sources is 1. After the previous interrupt handler function is executed, the next interrupt handler function is processed without interrupts.

![Interrupt nesting not enabled](pic/interruptnestingnotenabled.png "Interrupt nesting not enabled")
